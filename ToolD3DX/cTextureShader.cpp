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
    m_nTimer = 0;
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
    switch (m_pBrush->m_eDrawType)
    {
    case E_DRAW_BRUSH:
        if (m_pBrush->m_eGroundType == E_SOIL_GROUND)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255;
                    
                    DWORD lSour = *(pDWordDST + y) >> 16;
                    lSour = lSour & 0x00ff;
                    x = max(lSour, x);
                  
                    *(pDWordDST + y) =  0x00010000 * x;
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
                    *(pDWordDST + y) =  0x00ff0000;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
        }
        else if (m_pBrush->m_eGroundType == E_GRASS_GROUND)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255;

                    DWORD lSour = *(pDWordDST + y) >> 8;
                    lSour = lSour & 0x0000ff;
                    x = max(lSour, x);

                    *(pDWordDST + y) = 0x00000100 * x;
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
                    *(pDWordDST + y) = 0x0000ff00;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
        }
        else if (m_pBrush->m_eGroundType == E_STONE_GROUND)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255;

                    DWORD lSour = *(pDWordDST + y);
                    lSour = lSour & 0x000000ff;
                    x = max(lSour, x);

                    *(pDWordDST + y) = 0x00000001 * x;
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
                    *(pDWordDST + y) = 0x000000ff;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
        }
        break;

    case E_DRAW_SPRAY :
        if (m_pBrush->m_eGroundType == E_SOIL_GROUND)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f;
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
                    int x = 255 * m_pBrush->m_fDrawDensity * 0.05f;
                    DWORD lSour = *(pDWordDST + y) >> 16;
                    lSour = lSour & 0x00ff;
                    lSour += x;
                    lSour = min(255, lSour);
                    lSour = lSour << 16;

                    *(pDWordDST + y) = *(pDWordDST + y) & 0xff00ffff;
                    *(pDWordDST + y) = *(pDWordDST + y) | lSour;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
        }
        else if (m_pBrush->m_eGroundType == E_GRASS_GROUND)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f;
                    DWORD lSour = *(pDWordDST + y) >> 8;
                    lSour = lSour & 0x0000ff;
                    lSour += x;
                    lSour = min(255, lSour);
                    lSour = lSour << 8;

                    *(pDWordDST + y) = *(pDWordDST + y) & 0xffff00ff;
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
                    int x = 255 * m_pBrush->m_fDrawDensity * 0.05f;
                    DWORD lSour = *(pDWordDST + y) >> 8;
                    lSour = lSour & 0x0000ff;
                    lSour += x;
                    lSour = min(255, lSour);
                    lSour = lSour << 8;

                    *(pDWordDST + y) = *(pDWordDST + y) & 0xffff00ff;
                    *(pDWordDST + y) = *(pDWordDST + y) | lSour;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
        }
        else if (m_pBrush->m_eGroundType == E_STONE_GROUND)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    int x = (1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f;
                    DWORD lSour = *(pDWordDST + y);
                    lSour = lSour & 0x000000ff;
                    lSour += x;
                    lSour = min(255, lSour);


                    *(pDWordDST + y) = *(pDWordDST + y) & 0xffffff00;
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
                    int x = 255 * m_pBrush->m_fDrawDensity * 0.05f;
                    DWORD lSour = *(pDWordDST + y);
                    lSour = lSour & 0x000000ff;
                    lSour += x;
                    lSour = min(255, lSour);
                    *(pDWordDST + y) = *(pDWordDST + y) & 0xffffff00;
                    *(pDWordDST + y) = *(pDWordDST + y) | lSour;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
        }
        break; 

        case E_DRAW_ERASE :
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");

            D3DLOCKED_RECT AlphaMap_Locked;
            memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
            m_pAlphaDraw->LockRect(0, &AlphaMap_Locked, NULL, NULL);
            LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;


            for (int i = m_pBrush->m_nFarMinZ; i < m_pBrush->m_nFarMaxZ; i++)
            {
                LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
                for (int y = m_pBrush->m_nFarMinX; y < m_pBrush->m_nFarMaxX; y++)
                {
                    float lx = m_pBrush->m_fPickX - (float)y;
                    float ly = m_pBrush->m_fPickZ - (float)i;
                    float length = sqrt(lx * lx + ly * ly);

                    if (length >= m_pBrush->m_fFR)    // �� �ٱ��� ����
                    {
                        continue;
                    }
                    *(pDWordDST + y) = 0x00000000;
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
                    *(pDWordDST + y) = 0x00000000;
                }
            }

            m_pAlphaDraw->UnlockRect(0);
            break;
    }
}

void cTextureShader::SaveTexture()
{
    //auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");
    g_pTextureManager->SaveTexture(m_pAlphaDraw, "Save.png", D3DXIFF_BMP);

}

void cTextureShader::SetMapSize()
{
    g_pTextureManager->AddTexture("alpha", (g_pMapDataManager->GetMapSize() + 1) * 64);
    m_pAlphaDraw = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");
}

void cTextureShader::Update()
{
   // m_nTimer++;
   // if (m_nTimer >= 3)
   // {
        DrawTexture();
   //     m_nTimer = 0;
   // }
}

void cTextureShader::Render()
{
    m_pTextureShader->SetTexture("texture0", m_pTexture[0]);
    m_pTextureShader->SetTexture("texture1", m_pTexture[1]);
    m_pTextureShader->SetTexture("texture2", m_pTexture[2]);
    m_pTextureShader->SetTexture("texture3", m_pTexture[3]);
    
    m_pTextureShader->SetTexture("AlphaMap", m_pAlphaDraw);

    m_pTextureShader->SetVector("gUV", &m_pBrush->m_pPick);
    m_pTextureShader->SetFloat("Brush_Radius", m_pBrush->m_fBrushRadius);
    m_pTextureShader->SetFloat("Spray_Radius", m_pBrush->m_fSprayRadius);
    m_pTextureShader->SetFloat("Density", m_pBrush->m_fDrawDensity);
    m_pTextureShader->SetFloat("Tex1Density", m_pBrush->m_fTex1Density);
    m_pTextureShader->SetFloat("Tex2Density", m_pBrush->m_fTex2Density);
    m_pTextureShader->SetFloat("Tex3Density", m_pBrush->m_fTex3Density);

   
  // ST_PNT_VERTEX* pEditV = NULL;
  // m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);
  // ST_PNT_VERTEX* pEditI = NULL;
  // m_pMesh->LockIndexBuffer(NULL, (LPVOID*)&pEditI);
  //
  // // ���̴��� �����Ѵ�.
  //g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, m_pMesh->GetNumVertices(), m_pMesh->GetNumFaces(), &pEditI[0], D3DFMT_INDEX32, &pEditV[0], sizeof(m_pMesh->GetFVF()));// ; 

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
