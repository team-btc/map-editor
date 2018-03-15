#include "stdafx.h"
#include "cFogShader.h"


cFogShader::cFogShader()
    :m_pMesh(NULL)
    , m_vFogColor(0.4f, 0.4f, 0.4f, 1.0f)
    , m_vFog(0.33f, 1000.0f, 0, 0)
{
    g_pShaderManager->AddEffect("Fog", "Shader/FX/FogShader.fx");
    m_pFogShader = g_pShaderManager->GetEffect("Fog");
}


cFogShader::~cFogShader()
{
}

void cFogShader::Render()
{
    D3DXMATRIXA16 matW, matV;
    D3DXMatrixIdentity(&matW);
    g_pDevice->GetTransform(D3DTS_VIEW, &matV);

    m_pFogShader->SetMatrix("gWorldMatrix", &matW);
    m_pFogShader->SetMatrix("gViewMatrix", &matV);
    m_pFogShader->SetVector("g_fog", &m_vFog);
    m_pFogShader->SetVector("Fog_Color", &m_vFogColor);


    UINT numPasses = 0;
    m_pFogShader->Begin(&numPasses, NULL);
    {
        for (UINT i = 0; i < numPasses; ++i)
        {
            m_pFogShader->BeginPass(i);
            {
                m_pMesh->DrawSubset(0);
            }
            m_pFogShader->EndPass();
        }
    }
    m_pFogShader->End();
}
