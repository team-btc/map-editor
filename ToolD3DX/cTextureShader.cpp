#include "stdafx.h"
#include "cTextureShader.h"


cTextureShader::cTextureShader()
    :m_pBrush(NULL)
{
    g_pTextureManager->AddTexture("null", "Shader/Texture/Null.png");
    g_pShaderManager->AddEffect("rendtex", "Shader/FX/TextureShader.fx");
    m_pTextureShader = g_pShaderManager->GetEffect("rendtex");
    ZeroMemory(m_pTexture, 4);
    ZeroMemory(m_TexDensity, 4);
    g_pTextureManager->AddTexture("alpha", 256);
    m_pAlpha = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");
}
cTextureShader::~cTextureShader()
{
  
}

void cTextureShader::SetTexture()
{
    g_pTextureManager->AddTexture("default", "Shader/Texture/Default.jpg");
    g_pTextureManager->AddTexture("Soil", "Texture/Soil.jpg");
    g_pTextureManager->AddTexture("Grass", "Texture/Grass.jpg");
    g_pTextureManager->AddTexture("Stone", "Texture/Ston.jpg");

    m_pTexture[0] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("null");
    m_pTexture[1] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("Soil");
    m_pTexture[2] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("Grass");
    m_pTexture[3] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("Stone");

    for (int i = 1; i < 4; ++i)
    {
        m_TexDensity[i] = 0.0f;
    }
}

void cTextureShader::DrawTexture()
{
    int Density = 0;

    if (m_pBrush->m_eGroundType == E_SOIL_GROUND)
    {
        auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

        D3DLOCKED_RECT AlphaMap_Locked;
        memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
        t->LockRect(0, &AlphaMap_Locked, NULL, NULL);
        LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


        for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
        {
            LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
            for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
            {
                float lx = m_pBrush->m_fPickX - (float)y;
                float ly = m_pBrush->m_fPickZ - (float)i;
                float length = sqrt(lx * lx + ly * ly);

                if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                {
                    continue;
                }
                int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255;
                DWORD lSour = *(pDWordDST + y) >> 16;
                lSour = lSour & 0x00ff;
                lSour += x;
                lSour = min(255, lSour);
                lSour = lSour << 16;

                *(pDWordDST + y) = *(pDWordDST + y) & 0xff00ffff;
                *(pDWordDST + y) = *(pDWordDST + y) | lSour;
            }
        }
        for (int i = m_pBrush->m_nNearMinZ; i < m_pBrush->m_nNearMaxZ; i++)
        {
            LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
            for (int y = m_pBrush->m_nNearMinX; y < m_pBrush->m_nNearMaxX; y++)
            {
                float lx = m_pBrush->m_fPickX - (float)y;
                float ly = m_pBrush->m_fPickZ - (float)i;
                float length = sqrt(lx * lx + ly * ly);
                if (length > m_pBrush->m_fNR)
                    continue;
                *(pDWordDST + y) = 0x00ff0000;
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
    else if (m_pBrush->m_eGroundType == E_GRASS_GROUND)
    {
        auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

        D3DLOCKED_RECT AlphaMap_Locked;
        memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
        t->LockRect(0, &AlphaMap_Locked, NULL, NULL);
        LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


        for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
        {
            LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
            for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
            {
                float lx = m_pBrush->m_fPickX - (float)y;
                float ly = m_pBrush->m_fPickZ - (float)i;
                float length = sqrt(lx * lx + ly * ly);

                if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                {
                    continue;
                }
                int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255;
                DWORD lSour = *(pDWordDST + y) >> 16;
                lSour = lSour & 0x00ff;
                lSour += x;
                lSour = min(255, lSour);
                lSour = lSour << 16;

                *(pDWordDST + y) = *(pDWordDST + y) & 0xff00ffff;
                *(pDWordDST + y) = *(pDWordDST + y) | lSour;
            }
        }
        for (int i = m_pBrush->m_nNearMinZ; i < m_pBrush->m_nNearMaxZ; i++)
        {
            LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
            for (int y = m_pBrush->m_nNearMinX; y < m_pBrush->m_nNearMaxX; y++)
            {
                float lx = m_pBrush->m_fPickX - (float)y;
                float ly = m_pBrush->m_fPickZ - (float)i;
                float length = sqrt(lx * lx + ly * ly);
                if (length > m_pBrush->m_fFR)
                    continue;
                *(pDWordDST + y) = 0x00ff0000;
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

    else if (m_pBrush->m_eGroundType == E_STONE_GROUND)
    {
        auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

        D3DLOCKED_RECT AlphaMap_Locked;
        memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
        t->LockRect(0, &AlphaMap_Locked, NULL, NULL);
        LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


        for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
        {
            LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
            for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
            {
                float lx = m_pBrush->m_fPickX - (float)y;
                float ly = m_pBrush->m_fPickZ - (float)i;
                float length = sqrt(lx * lx + ly * ly);

                if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                {
                    continue;
                }
                int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255;
                DWORD lSour = *(pDWordDST + y) >> 16;
                lSour = lSour & 0x00ff;
                lSour += x;
                lSour = min(255, lSour);
                lSour = lSour << 16;

                *(pDWordDST + y) = *(pDWordDST + y) & 0xff00ffff;
                *(pDWordDST + y) = *(pDWordDST + y) | lSour;
            }
        }
        for (int i = m_pBrush->m_nNearMinZ; i < m_pBrush->m_nNearMaxZ; i++)
        {
            LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
            for (int y = m_pBrush->m_nNearMinX; y < m_pBrush->m_nNearMaxX; y++)
            {
                float lx = m_pBrush->m_fPickX - (float)y;
                float ly = m_pBrush->m_fPickZ - (float)i;
                float length = sqrt(lx * lx + ly * ly);
                if (length > m_pBrush->m_fFR)
                    continue;
                *(pDWordDST + y) = 0x00ff0000;
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
}

void cTextureShader::Update()
{
    DrawTexture();
}

void cTextureShader::Render()
{
    m_pTextureShader->SetTexture("texture0", m_pTexture[0]);
    m_pTextureShader->SetTexture("texture1", m_pTexture[1]);
    m_pTextureShader->SetTexture("texture2", m_pTexture[2]);
    m_pTextureShader->SetTexture("texture3", m_pTexture[3]);

    
    m_pTextureShader->SetTexture("AlphaMap", m_pAlpha);

    m_pTextureShader->SetVector("gUV", &m_pBrush->m_pPick);
    m_pTextureShader->SetFloat("Brush_Radius", m_pBrush->m_fBrushRadius);
    m_pTextureShader->SetFloat("Spray_Radius", m_pBrush->m_fSprayRadius);
    m_pTextureShader->SetFloat("Density", m_pBrush->m_fDensity);

   

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
