#pragma once
class cFogShader
{
private:
    LPMESH				    m_pMesh;
    LPD3DXEFFECT			m_pFogShader;

    D3DXVECTOR4             m_vFogColor;
    D3DXVECTOR4             m_vFog;

public:
    cFogShader();
    ~cFogShader();
    void SetMesh(LPMESH mesh) 
    {
        mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pDevice, &m_pMesh);
    }
    void Render();
};

