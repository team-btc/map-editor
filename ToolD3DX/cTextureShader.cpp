#include "stdafx.h"
#include "cTextureShader.h"


cTextureShader::cTextureShader()
{
    g_pShaderManager->AddEffect("rendtex", "Shader/FX/TextureShader.fx");
    m_pTextureShader = g_pShaderManager->GetEffect("rendtex");
    ZeroMemory(m_pTexture, 4);
}
cTextureShader::~cTextureShader()
{

}

void cTextureShader::SetTexture()
{
    g_pTextureManager->AddTexture("default", "Shader/Texture/Default.jpg");
    m_pTexture[0] = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture("default");
}


void cTextureShader::SetBrush(Vector4 v, float br, float sr, float density)
{
    m_pPick = v;
    m_fBrushRadius = br;
    m_fSprayRadius = sr;
    m_fDensity = density;
}

void cTextureShader::Render()
{
    m_pTextureShader->SetTexture("DiffuseMap_Tex", m_pTexture[0]);
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
