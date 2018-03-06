#include "stdafx.h"
#include "cSkyBoxShader.h"


cSkyBoxShader::cSkyBoxShader()
{
}


cSkyBoxShader::~cSkyBoxShader()
{
}

void cSkyBoxShader::SetBox(string sTexFileKey)
{
    // �����Ҷ� ��� �ؽ��� ���ϰ� ����Ʈ �ڵ� �߰�
    // g_pShaderManager->AddEffect("SkyBox", "SkyBox.fx");
    m_pSkyBoxShader = g_pShaderManager->GetEffect("SkyBox");

    // Ű ������ ��ī�̹ڽ� �ؽ��ĸ� ���� 
    // D3DXCreateCubeTextureFromFile(g_pD3DDevice, sTexFilePath.c_str(), &m_pCubeTexture);
    m_pCubeTexture = g_pTextureManager->GetCubeTexture(sTexFileKey);

    DWORD numMaterial;
    D3DXLoadMeshFromX("HeightMapData/Box.x", NULL, g_pD3DDevice, NULL, &m_pMaterial, NULL, &numMaterial, &m_pMesh);
}

void cSkyBoxShader::Render(D3DXVECTOR4 vCameraPosition)
{
    D3DXMATRIXA16 matW, matView, matProjection, matViewProjection;
    D3DXMatrixIdentity(&matW);
    D3DXVECTOR4 gWorldCameraPosition = vCameraPosition;

    g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
    matViewProjection = matView * matProjection;

    m_pSkyBoxShader->SetMatrix("ViewProjection", &matViewProjection);
    m_pSkyBoxShader->SetVector("ViewPosition", &gWorldCameraPosition);
    m_pSkyBoxShader->SetTexture("Snow_Tex", m_pCubeTexture);

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
}


