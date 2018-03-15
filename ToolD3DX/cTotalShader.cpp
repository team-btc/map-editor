#include "stdafx.h"
#include "cTotalShader.h"


cTotalShader::cTotalShader()
    :m_pBrush(NULL)
    , gWorldLightPosition(10.0f, 1500.0f, 0.0, 1.0f)
    , gLightColor(0.7f, 0.7f, 1.0f, 1.0f)
    , m_pMesh1(NULL)
    , m_pMesh2(NULL)
{
    g_pTextureManager->AddTexture("null", "Shader/Texture/Null.png");
    g_pShaderManager->AddEffect("Total", "Shader/FX/TotalShader.fx");
    m_pTotalShader = g_pShaderManager->GetEffect("Total");
    ZeroMemory(m_pTexture, 4);
    ZeroMemory(m_TexDensity, 4);
    m_nTimer = 0;
}


cTotalShader::~cTotalShader()
{
}

void cTotalShader::SetShader(/* char * sTexFile, char * sTexFileKey, */float fHeight, float fWaveHeight, float fSpeed, float fUVSpeed, float fWaveFrequency, float fTransparent)
{
    //  m_pWaterMap = new cHeightMap;
    // m_pWaterMap->Load("Shader/Model/WaterMap.raw", Water, "Shader/Texture/water.jpg", m_pMesh);   // 툴에서는 다르게 만들거라 생각댐
    m_pHeight = fHeight;
    m_pWaveHeight = fWaveHeight;
    m_pSpeed = fSpeed;
    m_pUVSpeed = fUVSpeed;
    m_pWaveFrequency = fWaveFrequency;
    m_pTransparent = fTransparent;

    g_pTextureManager->AddTexture("Water", "Shader/Texture/water.jpg");
    m_pWaterTexture = (LPTEXTURE9)g_pTextureManager->GetTexture("Water");                     // 툴이 시작할때 기본적으로 Add 해주므로 나중에 고치면 댐
}

void cTotalShader::SetTexture()
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

void cTotalShader::DrawTexture()
{
    int Density = 0;
    switch (m_pBrush->m_eDrawType)
    {
    case E_DRAW_BRUSH:
        if (m_pBrush->m_nGroundIndex == 0)
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

                    if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                    {
                        continue;
                    }
                    DWORD x = (DWORD)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255);

                    DWORD lSour = *(pDWordDST + y) >> 16;
                    lSour = lSour & 0x00ff;
                    x = max(lSour, x);

                    *(pDWordDST + y) = 0x00010000 * x;
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

            m_pAlphaDraw->UnlockRect(0);
        }
        else if (m_pBrush->m_nGroundIndex == 1)
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

                    if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                    {
                        continue;
                    }
                    DWORD x = (DWORD)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255);

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
        else if (m_pBrush->m_nGroundIndex == 2)
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

                    if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                    {
                        continue;
                    }
                    DWORD x = (DWORD)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255);

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

    case E_DRAW_SPRAY:
        if (m_pBrush->m_nGroundIndex == 0)
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

                    if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                    {
                        continue;
                    }
                    int x = (int)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f);
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
                    int x = (int)(255 * m_pBrush->m_fDrawDensity * 0.05f);
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
        else if (m_pBrush->m_nGroundIndex == 1)
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

                    if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                    {
                        continue;
                    }
                    int x = (int)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f);
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
                    int x = (int)(255 * m_pBrush->m_fDrawDensity * 0.05f);
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
        else if (m_pBrush->m_nGroundIndex == 2)
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

                    if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
                    {
                        continue;
                    }
                    int x = (int)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f);
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
                    int x = (int)(255.0f * m_pBrush->m_fDrawDensity * 0.05f);
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

    case E_DRAW_ERASE:
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

                if (length >= m_pBrush->m_fFR)    // 원 바깥은 무시
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

void cTotalShader::SaveTexture()
{
    //auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");
    g_pTextureManager->SaveTexture(m_pAlphaDraw, "Save.png", D3DXIFF_BMP);

}

void cTotalShader::SetMapSize()
{
    g_pTextureManager->AddTexture("alpha", (g_pMapDataManager->GetMapSize() + 1) * 64);
    m_pAlphaDraw = (LPTEXTURE9)g_pTextureManager->GetTexture("alpha");
}

void cTotalShader::Update()
{
    DrawTexture();
}

void cTotalShader::Render()
{
    D3DXMATRIXA16 matW, matView, matProjection;
    D3DXMatrixIdentity(&matW);

    g_pDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pDevice->GetTransform(D3DTS_PROJECTION, &matProjection);


    m_pTotalShader->SetMatrix("gWorldMatrix", &matW);
    m_pTotalShader->SetMatrix("gViewMatrix", &matView);
    m_pTotalShader->SetMatrix("gProjectionMatrix", &matProjection);

    m_pTotalShader->SetTexture("texture0", m_pTexture[0]);
    m_pTotalShader->SetTexture("texture1", m_pTexture[1]);
    m_pTotalShader->SetTexture("texture2", m_pTexture[2]);
    m_pTotalShader->SetTexture("texture3", m_pTexture[3]);

    m_pTotalShader->SetTexture("AlphaMap", m_pAlphaDraw);

    m_pTotalShader->SetVector("gUV", &m_pBrush->m_pPick);
    m_pTotalShader->SetFloat("Brush_Radius", m_pBrush->m_fBrushRadius);
    m_pTotalShader->SetFloat("Spray_Radius", m_pBrush->m_fSprayRadius);
    m_pTotalShader->SetFloat("Density", m_pBrush->m_fDrawDensity);
    m_pTotalShader->SetFloat("Tex1Density", m_pBrush->m_fTex1Density);
    m_pTotalShader->SetFloat("Tex2Density", m_pBrush->m_fTex2Density);
    m_pTotalShader->SetFloat("Tex3Density", m_pBrush->m_fTex3Density);

    // 물===============================================================================

    D3DXMatrixIdentity(&matW);
    //g_pDevice->GetTransform(D3DTS_WORLD, &matW);
    matW._42 += m_pHeight - 128;


    D3DXVECTOR4 gWorldCameraPosition;


    m_pTotalShader->SetMatrix("gWorldMatrix", &matW);
    m_pTotalShader->SetTexture("DiffuseMap_Tex", m_pWaterTexture);

    m_pTotalShader->SetVector("gWorldLightPosition", &gWorldLightPosition);
    m_pTotalShader->SetVector("gWorldCameraPosition", &gWorldCameraPosition);
    m_pTotalShader->SetVector("gLightColor", &gLightColor);

    m_pTotalShader->SetFloat("gWaveHeight", m_pWaveHeight);              // 올라가는 정도(진폭)
    m_pTotalShader->SetFloat("gSpeed", m_pSpeed);                        // 오르락내리락하는 속도
    m_pTotalShader->SetFloat("gWaveFrequency", m_pWaveFrequency);        // 출렁이는 빈도
    m_pTotalShader->SetFloat("gUVSpeed", m_pUVSpeed);                    // 텍스쳐가 움직이는 속도
    m_pTotalShader->SetFloat("gTransparent", m_pTransparent);            // 텍스쳐가 움직이는 속도


    ULONGLONG tick = GetTickCount64();              // 시스템 시간을 구함
    m_pTotalShader->SetFloat("gTime", tick / 1000.0f);
    UINT numPasses = 0;
    m_pTotalShader->Begin(&numPasses, NULL);
    {
        for (UINT i = 0; i < numPasses; ++i)
        {
            m_pTotalShader->BeginPass(i);
            {
                m_pMesh1->DrawSubset(0);
            }
            m_pTotalShader->EndPass();
        }
    }
    m_pTotalShader->End();
}