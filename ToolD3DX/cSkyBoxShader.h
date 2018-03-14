#pragma once
class cSkyBoxShader
{
private:
    LPD3DXMESH				m_pMesh; 
    LPD3DXEFFECT			m_pSkyBoxShader;            // ���̴�
    LPD3DXBUFFER            m_pMaterial;                // x���� �ҷ����� ���� �ʿ���
    LPDIRECT3DTEXTURE9	    m_pSkyBoxTexture;           // 
    LPDIRECT3DCUBETEXTURE9  m_pCubeTexture;             // dds ���� ������ �ʿ���
public:
   

    cSkyBoxShader();
    ~cSkyBoxShader();

    void SetBox(string sTexFileKey, string sTexFilePath);
    void Render(D3DXVECTOR4 vCameraPosition);
    void SetSkyBoxTexture()
    {
        m_pSkyBoxTexture = (LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture(g_pMapDataManager->GetSkyFileName());
    }
};

