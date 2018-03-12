#include "stdafx.h"
#include "cSkyBoxShader.h"


cSkyBoxShader::cSkyBoxShader()
    :m_pMesh(NULL)
{
}


cSkyBoxShader::~cSkyBoxShader()
{
}

void cSkyBoxShader::SetBox(string sTexFileKey, string sTexFilePath)
{
    // �����Ҷ� ��� �ؽ��� ���ϰ� ����Ʈ �ڵ� �߰� �ҵ� ���߿�
    g_pShaderManager->AddEffect(sTexFileKey, "Shader/FX/SkyBox.fx");
    m_pSkyBoxShader = g_pShaderManager->GetEffect(sTexFileKey);
   
    // Ű ������ ��ī�̹ڽ� �ؽ��ĸ� ���� 
    m_pCubeTexture = (LPCUBETEXTURE9)g_pTextureManager->GetTexture(sTexFileKey);

    DWORD numMaterial;
    D3DXLoadMeshFromX("Shader/Model/Box.x", NULL, g_pDevice, NULL, &m_pMaterial, NULL, &numMaterial, &m_pMesh);
    D3DXCreateCubeTextureFromFile(g_pDevice, sTexFilePath.c_str(), &m_pCubeTexture);
}

void cSkyBoxShader::Render(D3DXVECTOR4 vCameraPosition)
{
    D3DXMATRIXA16 matW, matView, matProjection, matViewProjection;
    D3DXMatrixIdentity(&matW);
   
    D3DXVECTOR4 gWorldCameraPosition = vCameraPosition;

    g_pDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
    matViewProjection = matView * matProjection;

    m_pSkyBoxShader->SetMatrix("ViewProjection", &matViewProjection);
    m_pSkyBoxShader->SetVector("ViewPosition", &gWorldCameraPosition);
    m_pSkyBoxShader->SetTexture("Sky_Tex", m_pCubeTexture);

    UINT numPasses = 0;
    m_pSkyBoxShader->Begin(&numPasses, NULL);
    {
        for (UINT i = 0; i < numPasses; ++i)
        {
            m_pSkyBoxShader->BeginPass(i);
            {
                m_pMesh->DrawSubset(0);
            }
            m_pSkyBoxShader->EndPass();
        }
    }
    m_pSkyBoxShader->End();
}



