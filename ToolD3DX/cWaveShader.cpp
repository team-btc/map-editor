#include "stdafx.h"
#include "cWaveShader.h"


cWaveShader::cWaveShader()
    : gWorldLightPosition(10.0f, 100.0f, 0.0, 1.0f)
    , gLightColor(0.7f, 0.7f, 1.0f, 1.0f)
    , m_pWaterMap(NULL)
{
    g_pAutoReleasePool->AddObject(m_pWaterMap);
}


cWaveShader::~cWaveShader()
{
}

void cWaveShader::SetShader(char * sTexFile, char * sTexFileKey, float fHeight, float fWaveHeight, float fSpeed, float fUVSpeed, float fWaveFrequency, float fTransparent)
{
    m_pWaterMap = new cHeightMap;
    m_pWaterMap->Load("HeightMapData/WaterMap.raw", sTexFileKey, sTexFile, m_pMesh);   // 툴에서는 다르게 만들거라 생각댐
    m_pHeight = fHeight;
    m_pWaveHeight = fWaveHeight;
    m_pSpeed = fSpeed;
    m_pUVSpeed = fUVSpeed;
    m_pWaveFrequency = fWaveFrequency;
    m_pTransparent = fTransparent;

    g_pShaderManager->AddEffect("Wave", "WaveShader.fx");                    // 툴이 시작할때 기본적으로 Add 해주므로 나중에 고치면 댐
    m_pWaveShader = g_pShaderManager->GetEffect("Wave");                     // 툴이 시작할때 기본적으로 Add 해주므로 나중에 고치면 댐
    g_pTextureManager->AddTexture("Water", "HeightMapData/water.jpg");       // 툴이 시작할때 기본적으로 Add 해주므로 나중에 고치면 댐
    m_pTexture = g_pTextureManager->GetTexture("Water");                     // 툴이 시작할때 기본적으로 Add 해주므로 나중에 고치면 댐
}

void cWaveShader::Render(D3DXVECTOR4 vCameraPosition)
{
    D3DXMATRIXA16 matW, matView, matProjection;
    D3DXMatrixIdentity(&matW);
    matW._42 += m_pHeight;

    D3DXVECTOR4 gWorldCameraPosition = vCameraPosition;
  
    
    g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
    
    m_pWaveShader->SetMatrix("gWorldMatrix", &matW);
    m_pWaveShader->SetMatrix("gViewMatrix", &matView);
    m_pWaveShader->SetMatrix("gProjectionMatrix", &matProjection);
    m_pWaveShader->SetTexture("DiffuseMap_Tex", m_pTexture);

    m_pWaveShader->SetVector("gWorldLightPosition", &gWorldLightPosition);
    m_pWaveShader->SetVector("gWorldCameraPosition", &gWorldCameraPosition);
    m_pWaveShader->SetVector("gLightColor", &gLightColor);

    m_pWaveShader->SetFloat("gWaveHeight", m_pWaveHeight); // 올라가는 정도(진폭)
    m_pWaveShader->SetFloat("gSpeed", m_pSpeed); //  오르락내리락하는 속도
    m_pWaveShader->SetFloat("gWaveFrequency", m_pUVSpeed); // 출렁이는 빈도
    m_pWaveShader->SetFloat("gUVSpeed", m_pWaveFrequency); // 텍스쳐가 움직이는 속도
    m_pWaveShader->SetFloat("gTransparent", m_pTransparent); // 텍스쳐가 움직이는 속도

                                                       // 시스템 시간을 구함
    ULONGLONG tick = GetTickCount64();
    m_pWaveShader->SetFloat("gTime", tick / 1000.0f);

    // 쉐이더를 시작한다.
    UINT numPasses = 0;
    m_pWaveShader->Begin(&numPasses, NULL);
    {
        for (UINT i = 0; i < numPasses; ++i)
        {
            m_pWaveShader->BeginPass(i);
            {
                m_pMesh->DrawSubset(0);
            }
            m_pWaveShader->EndPass();
        }
    }
    m_pWaveShader->End();
}
