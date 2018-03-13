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
<<<<<<< HEAD
=======

>>>>>>> 22e64a31adffb9bd22e42808af3f4cab6c7117e9
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
<<<<<<< HEAD
    void SaveTexture();
=======
    void SaveTexture(string strFileTitle);
>>>>>>> 22e64a31adffb9bd22e42808af3f4cab6c7117e9
    void SetMapSize(string MapKey = "Alpha");

    void Update();
    void Render();
};

