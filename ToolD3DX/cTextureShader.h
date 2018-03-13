#include "cBrush.h"
#pragma once
class cTextureShader
{
    LPD3DXMESH				m_pMesh;
    LPD3DXEFFECT            m_pTextureShader;
    Vector4                 m_vPickPos;
    LPDIRECT3DTEXTURE9      m_pTexture[3];
    LPDIRECT3DTEXTURE9      m_pAlphaDraw;
    LPDIRECT3DTEXTURE9      m_pAlpha;
    
    cBrush*                 m_pBrush;

    float                   m_TexDensity[3];                                            // 타일의 밀도
    int                     m_nTimer;

    string                  m_sMapKey;
public:
    cTextureShader();
    ~cTextureShader();

    
    void SetBrush(cBrush* brush) { m_pBrush = brush; }
    void SetTexture();
    void SetTexture1();
    void SetTexture2();
    void SetTexture3();
    void SetMesh(LPD3DXMESH mesh) { m_pMesh = mesh; }
    void DrawTexture();
    void SaveTexture(string strFileTitle);
    void SetMapSize(string* MapKey = NULL);

    void Update();
    void Render();
};

