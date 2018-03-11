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
  // int                    m_nNearMaxX;
  // int                    m_nNearMinX;
  // int                    m_nNearMaxZ;
  // int                    m_nNearMinZ;
  //
  // int                    m_nFarMaxX;
  // int                    m_nFarMinX;
  // int                    m_nFarMaxZ;
  // int                    m_nFarMinZ;
  //
  // Vector4                m_pPick;
  // float                  m_fBrushRadius;
  // float                  m_fSprayRadius;
  // float                  m_fDensity;
  // E_GROUND_TYPE          m_eGroundType;

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

