#pragma once
#include "cBrush.h"

class cTotalShader
{
    LPD3DXMESH				m_pMesh1;                                                    // 메쉬
    LPD3DXMESH				m_pMesh2;                                                    // 메쉬
    LPD3DXEFFECT            m_pTotalShader;

    // Texture Shader //
    Vector4                 m_vPickPos;
    LPDIRECT3DTEXTURE9      m_pTexture[4];
    LPDIRECT3DTEXTURE9      m_pAlphaDraw;
    LPDIRECT3DTEXTURE9      m_pAlpha;

    cBrush*                 m_pBrush;

    float                   m_TexDensity[4];                                            // 타일의 밀도
    int                     m_nTimer;

    // Wave Shader // 
    LPDIRECT3DTEXTURE9      m_pWaterTexture;

    D3DXVECTOR4             gWorldLightPosition;
    D3DXVECTOR4             gLightColor;

    float m_pHeight;                  // 물의 지형에서의 높이
    float m_pWaveHeight;              // 진폭
    float m_pSpeed;                   // 진동속도
    float m_pUVSpeed;                 // 텍스쳐가 지나가는 속도
    float m_pWaveFrequency;           // 물결의 간격
    float m_pTransparent;             // 물의 투명도
public:
    cTotalShader();
    ~cTotalShader();

    // Texture Shader //
    void SetBrush(cBrush* brush) { m_pBrush = brush; }
    void SetTexture();
    void DrawTexture();
    void SaveTexture();
    void SetMapSize();

    void Update();

    // Wave Shader // 
    // Height : 물의 지형에서의 높이, WaveHeight : 진폭 , Speed : 진동속도, UVSpeed : 텍스쳐가 지나가는 속도, WaveFrequency : 물결의 간격, Transparent : 물의 투명도
    void SetShader(/* char * sTexFile, char * sTexFileKey, */float fHeight = 0.0f, float fWaveHeight = 0.6f, float fSpeed = 2.4f,
        float fUVSpeed = 7.0f, float fWaveFrequency = 0.01f, float fTransparent = 0.6f);


    void SetMesh(LPMESH mesh1, LPMESH mesh2) { m_pMesh1 = mesh1; m_pMesh2 = mesh2; }
    void Render();
};

