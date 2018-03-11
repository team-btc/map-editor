#include "cBrush.h"
#pragma once
class cTextureShader
{
    LPD3DXMESH				m_pMesh;
    LPD3DXEFFECT            m_pTextureShader;
    Vector4                 m_vPickPos;
    LPDIRECT3DTEXTURE9      m_pTexture[4];
    LPDIRECT3DTEXTURE9      m_pAlphaDraw;
    LPDIRECT3DTEXTURE9      m_pAlpha;
    
    cBrush*                 m_pBrush;

    float                   m_TexDensity[4];                                            // 타일의 밀도
    int                     m_nTimer;
public:
    cTextureShader();
    ~cTextureShader();

    
    void SetBrush(cBrush* brush) { m_pBrush = brush; }
    void SetTexture();
    void SetMesh(LPD3DXMESH mesh) { m_pMesh = mesh; }
    void DrawTexture();
    void SaveTexture();
    void SetMapSize();

    void Update();
    void Render();
};

