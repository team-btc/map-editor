#pragma once
class cSkyBoxShader
{
private:
    LPD3DXMESH				m_pMesh; 
    LPD3DXEFFECT			m_pSkyBoxShader;            // 셰이더
    LPD3DXBUFFER            m_pMaterial;                // x파일 불러오기 위해 필요함
    LPDIRECT3DTEXTURE9	    m_pSkyBoxTexture;           // 
    LPDIRECT3DCUBETEXTURE9  m_pCubeTexture;             // dds 파일 입힐때 필요함
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

