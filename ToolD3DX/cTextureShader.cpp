#include "stdafx.h"
#include "cTextureShader.h"


cTextureShader::cTextureShader()
{
    g_pTextureManager->AddTexture("null", "Shader/Texture/Null.png");
    g_pShaderManager->AddEffect("rendtex", "Shader/FX/TextureShader.fx");
    m_pTextureShader = g_pShaderManager->GetEffect("rendtex");
    ZeroMemory(m_pTexture, 4);
    ZeroMemory(m_TexDensity, 4);
    g_pTextureManager->AddTexture("alpha", 256);
    m_pAlpha = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");
    m_nMaxX = 0;
    m_nMinX = 0;
    m_nMaxZ = 0;
    m_nMinZ = 0;
}
cTextureShader::~cTextureShader()
{

}

void cTextureShader::SetTexture()
{
    g_pTextureManager->AddTexture("default", "Shader/Texture/Default.jpg");
    g_pTextureManager->AddTexture("Soil", "Texture/soil.bmp");
    g_pTextureManager->AddTexture("Grass", "Texture/Grass.jpg");
    g_pTextureManager->AddTexture("Stone", "Texture/Ston.jpg");

    //g_pTextureManager->AddTexture("al", "test.png");

    
    m_pTexture[0] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("default");
    m_pTexture[1] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("Soil");
    m_pTexture[2] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("Grass");
    m_pTexture[3] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("Stone");
   
    
    for (int i = 1; i < 4; ++i)
    {
        m_TexDensity[i] = 0.0f;
    }
}


void cTextureShader::SetBrush(Vector4 v, float br, float sr, float density)
{
    m_pPick = v;
    m_fBrushRadius = br;
    m_fSprayRadius = sr;
    m_fDensity = density;
}

void cTextureShader::GetRect()
{
    int nMinX = (m_pPick.x - m_fBrushRadius) * 256;
    if (nMinX < 0)
    {
        nMinX = 0;
    }

    int nMaxX = (m_pPick.x + m_fBrushRadius) * 256 + 1;
    if (nMaxX > 256)
    {
        nMaxX = 256;
    }

    int nMinZ = (m_pPick.z - m_fBrushRadius) * 256;
    if (nMinZ < 0)
    {
        nMinZ = 0;
    }

    int nMaxZ = (m_pPick.z + m_fBrushRadius) * 256 + 1;
    if (nMaxZ > 256)
    {
        nMaxZ = 256;
    }

    m_nMaxX = nMaxX;
    m_nMaxZ = nMaxZ;
    m_nMinX = nMinX;
    m_nMinZ = nMinZ;
}

void cTextureShader::Update()
{
    if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
    {
        GetRect();

        switch (m_eGroundType)
        {
        case E_SOIL_GROUND:
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            t->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;

            for (int i = m_nMinZ; i < m_nMaxZ; i++)
            {   
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_nMinX; y < m_nMaxX; y++)
                {
                    *(pDWordDST + y) = 0xffffffff;
                }
            }

            t->UnlockRect(0);

            HRESULT hr = D3DXSaveTextureToFileA("test.png",
                D3DXIFF_PNG,
                t,
                NULL);
            g_pTextureManager->SaveTexture("alpha", "test.png");
            m_pAlpha = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("alpha");
        }
        break;

        case E_GRASS_GROUND:

        break;

        case E_STONE_GROUND:

        break;
        }
    }
}

void cTextureShader::Render()
{
    m_pTextureShader->SetTexture("texture0", m_pTexture[0]);
    m_pTextureShader->SetTexture("texture1", m_pTexture[1]);
    m_pTextureShader->SetTexture("texture2", m_pTexture[2]);
    m_pTextureShader->SetTexture("texture3", m_pTexture[3]);

    
    m_pTextureShader->SetTexture("AlphaMap", m_pAlpha);

    m_pTextureShader->SetVector("gUV", &m_pPick);
    m_pTextureShader->SetFloat("Brush_Radius", m_fBrushRadius);
    m_pTextureShader->SetFloat("Spray_Radius", m_fSprayRadius);
    m_pTextureShader->SetFloat("Density", m_fDensity);

   

    UINT numPasses = 0;
    m_pTextureShader->Begin(&numPasses, NULL);
    {
        for (UINT i = 0; i < numPasses; ++i)
        {
            m_pTextureShader->BeginPass(i);
            {
                m_pMesh->DrawSubset(0);
            }
            m_pTextureShader->EndPass();
        }
    }
    m_pTextureShader->End();
}
