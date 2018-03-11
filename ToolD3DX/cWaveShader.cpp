#include "stdafx.h"
#include "cWaveShader.h"


cWaveShader::cWaveShader()
    : gWorldLightPosition(10.0f, 1500.0f, 0.0, 1.0f)
    , gLightColor(0.7f, 0.7f, 1.0f, 1.0f)
    , m_pMesh(NULL)
{
                     // ���� �����Ҷ� �⺻������ Add ���ֹǷ� ���߿� ��ġ�� ��

}


cWaveShader::~cWaveShader()
{

}

void cWaveShader::SetShader(/* char * sTexFile, char * sTexFileKey, */float fHeight, float fWaveHeight, float fSpeed, float fUVSpeed, float fWaveFrequency, float fTransparent)
{
  //  m_pWaterMap = new cHeightMap;
   // m_pWaterMap->Load("Shader/Model/WaterMap.raw", Water, "Shader/Texture/water.jpg", m_pMesh);   // �������� �ٸ��� ����Ŷ� ������
    m_pHeight = fHeight;
    m_pWaveHeight = fWaveHeight;
    m_pSpeed = fSpeed;
    m_pUVSpeed = fUVSpeed;
    m_pWaveFrequency = fWaveFrequency;
    m_pTransparent = fTransparent;

    g_pTextureManager->AddTexture("Water", "Shader/Texture/water.jpg");
    g_pShaderManager->AddEffect("Wave", "Shader/FX/WaveShader.fx");
    m_pWaveShader = g_pShaderManager->GetEffect("Wave");                     // ���� �����Ҷ� �⺻������ Add ���ֹǷ� ���߿� ��ġ�� ��
    //g_pTextureManager->AddTexture("Water", "Shader/Texture/water.jpg");       // ���� �����Ҷ� �⺻������ Add ���ֹǷ� ���߿� ��ġ�� ��
    m_pTexture = (LPTEXTURE9)g_pTextureManager->GetTexture("Water");                     // ���� �����Ҷ� �⺻������ Add ���ֹǷ� ���߿� ��ġ�� ��
}

void cWaveShader::Render(D3DXVECTOR4 vCameraPosition)
{
  
    D3DXMATRIXA16 matW, matView, matProjection;
    D3DXMatrixIdentity(&matW);
    //g_pDevice->GetTransform(D3DTS_WORLD, &matW);
    matW._42 += m_pHeight - 128;

   
    D3DXVECTOR4 gWorldCameraPosition = vCameraPosition;
    g_pDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
    

    m_pWaveShader->SetMatrix("gWorldMatrix", &matW);
    m_pWaveShader->SetMatrix("gViewMatrix", &matView);
    m_pWaveShader->SetMatrix("gProjectionMatrix", &matProjection);
    m_pWaveShader->SetTexture("DiffuseMap_Tex", m_pTexture);

    m_pWaveShader->SetVector("gWorldLightPosition", &gWorldLightPosition);
    m_pWaveShader->SetVector("gWorldCameraPosition", &gWorldCameraPosition);
    m_pWaveShader->SetVector("gLightColor", &gLightColor);

    m_pWaveShader->SetFloat("gWaveHeight", m_pWaveHeight); // �ö󰡴� ����(����)
    m_pWaveShader->SetFloat("gSpeed", m_pSpeed); //  �������������ϴ� �ӵ�
    m_pWaveShader->SetFloat("gWaveFrequency", m_pWaveFrequency); // �ⷷ�̴� ��
    m_pWaveShader->SetFloat("gUVSpeed", m_pUVSpeed); // �ؽ��İ� �����̴� �ӵ�
    m_pWaveShader->SetFloat("gTransparent", m_pTransparent); // �ؽ��İ� �����̴� �ӵ�

                                                       // �ý��� �ð��� ����
    ULONGLONG tick = GetTickCount64();
    m_pWaveShader->SetFloat("gTime", tick / 1000.0f);

  /*  ST_PNT_VERTEX* pEditV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);
    ST_PNT_VERTEX* pEditI = NULL;
    m_pMesh->LockIndexBuffer(NULL, (LPVOID*)&pEditI);*/

    // ���̴��� �����Ѵ�.
   //g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, m_pMesh->GetNumVertices(), m_pMesh->GetNumFaces(), &pEditI[0], D3DFMT_INDEX32, &pEditV[0], sizeof(m_pMesh->GetFVF()));// ; 
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
