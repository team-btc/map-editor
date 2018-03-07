#pragma once
class cTextureShader
{
    LPD3DXMESH				m_pMesh;
    LPD3DXEFFECT            m_pTextureShader;
    Vector4                 m_vPickPos;
    LPDIRECT3DTEXTURE9      m_pTexture[4];
    Vector4                 m_pPick;
    float                   m_fBrushRadius;
    float                   m_fSprayRadius;
    float                   m_fDensity;
public:
    cTextureShader();
    ~cTextureShader();

    void SetTexture();
    void SetMesh(LPD3DXMESH mesh) { m_pMesh = mesh; }
    void SetBrush(Vector4 v, float br, float sr, float density);
    
    void Render();
};

