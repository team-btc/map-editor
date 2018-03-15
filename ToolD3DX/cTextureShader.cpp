#include "stdafx.h"
#include "cTextureShader.h"


cTextureShader::cTextureShader()
    :m_pBrush(NULL)
{
    g_pShaderManager->AddEffect("rendtex", "Shader/FX/TextureShader.fx");
    m_pTextureShader = g_pShaderManager->GetEffect("rendtex");
    ZeroMemory(m_pTexture, 3);

    for (int i = 1; i < 3; ++i)
    {
        m_TexDensity[i] = 0.0f;
    }

    m_nTimer = 0;
}

cTextureShader::~cTextureShader()
{

}

void cTextureShader::SetTexture()
{
    SetTexture1();
    SetTexture2();
    SetTexture3();
}

void cTextureShader::SetTexture1()
{
    //g_pTextureManager->AddTexture(g_pMapDataManager->GetTex1FileName(), g_pMapDataManager->GetTex1FilePath() + "//" + g_pMapDataManager->GetTex1FileName());
    m_pTexture[0] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture(g_pMapDataManager->GetTex1FileName());
}

void cTextureShader::SetTexture2()
{
    //g_pTextureManager->AddTexture(g_pMapDataManager->GetTex2FileName(), g_pMapDataManager->GetTex2FilePath() + "//" + g_pMapDataManager->GetTex2FileName());
    m_pTexture[1] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture(g_pMapDataManager->GetTex2FileName());
}

void cTextureShader::SetTexture3()
{
    //g_pTextureManager->AddTexture(g_pMapDataManager->GetTex3FileName(), g_pMapDataManager->GetTex3FilePath() + "//" + g_pMapDataManager->GetTex3FileName());
    m_pTexture[2] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture(g_pMapDataManager->GetTex3FileName());

}

void cTextureShader::DrawTexture()
{
    int Density = 0;
    switch (m_pBrush->m_eDrawType)
    {
    case E_DRAW_BRUSH:
        if (m_pBrush->m_nGroundIndex == 0)
        {
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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
                    DWORD x = (DWORD)((1.0f - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255.0f);

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
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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
                    DWORD x = (DWORD)((1.0f - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255.0f);

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
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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
                    DWORD x = (DWORD)((1.0f - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255.0f * m_pBrush->m_fDrawDensity * 0.05f);
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
                    DWORD x = (DWORD)(255.0f * m_pBrush->m_fDrawDensity * 0.05f);
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
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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
                    DWORD x = (DWORD)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f);
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
                    DWORD x = (DWORD)(255 * m_pBrush->m_fDrawDensity * 0.05f);
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
            auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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
                    DWORD x = (DWORD)((1 - (length - m_pBrush->m_fNR) / m_pBrush->m_fdR) * 255 * m_pBrush->m_fDrawDensity * 0.05f);
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
                    DWORD x = (DWORD)(255 * m_pBrush->m_fDrawDensity * 0.05f);
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
        auto t = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);

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

void cTextureShader::SaveTexture(string strFilePath, string strFileTitle)
{
    g_pTextureManager->SaveTexture(m_pAlphaDraw, strFilePath + "/" + strFileTitle + ".png", D3DXIFF_BMP);
}

void cTextureShader::SetMapSize(string* MapKey)
{
    if (MapKey)
    {
        m_sMapKey = *MapKey;
        string sFullPath = *MapKey + ".png";
        g_pTextureManager->AddTexture(m_sMapKey, sFullPath);
        m_pAlphaDraw = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);
    }
    else
    {
        D3DCOLOR c = D3DCOLOR_ARGB(0, 255, 0, 0);
        g_pTextureManager->AddTexture(m_sMapKey, (g_pMapDataManager->GetMapSize() + 1) * 64, c);
        m_pAlphaDraw = (LPTEXTURE9)g_pTextureManager->GetTexture(m_sMapKey);
    }
}

void cTextureShader::Update()
{
    m_nTimer++;
    if (m_nTimer >= 6)
    {
        DrawTexture();
        m_nTimer = 0;
    }
}

void cTextureShader::Render()
{
    D3DXMATRIXA16 matW, matView, matProjection;
    D3DXMatrixIdentity(&matW);

    g_pDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

    m_pTextureShader->SetMatrix("gWorldMatrix", &matW);
    m_pTextureShader->SetMatrix("gViewMatrix", &matView);
    m_pTextureShader->SetMatrix("gProjectionMatrix", &matProjection);

    m_pTextureShader->SetTexture("texture0", m_pTexture[0]);
    m_pTextureShader->SetTexture("texture1", m_pTexture[0]);
    m_pTextureShader->SetTexture("texture2", m_pTexture[1]);
    m_pTextureShader->SetTexture("texture3", m_pTexture[2]);

    m_pTextureShader->SetTexture("AlphaMap", m_pAlphaDraw);

    m_pTextureShader->SetVector("gUV", &m_pBrush->m_pPick);

    m_pTextureShader->SetFloat("Brush_Radius", m_pBrush->m_fBrushRadius);
    m_pTextureShader->SetFloat("Spray_Radius", m_pBrush->m_fSprayRadius);
    m_pTextureShader->SetFloat("Density", m_pBrush->m_fDrawDensity);

    m_pTextureShader->SetFloat("Tex1Density", m_pBrush->m_fTex1Density);
    m_pTextureShader->SetFloat("Tex2Density", m_pBrush->m_fTex2Density);
    m_pTextureShader->SetFloat("Tex3Density", m_pBrush->m_fTex3Density);

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
