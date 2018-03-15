#pragma once
#include "cBrush.h"

class cTotalShader
{
    LPD3DXMESH				m_pMesh1;                                                    // �޽�
    LPD3DXMESH				m_pMesh2;                                                    // �޽�
    LPD3DXEFFECT            m_pTotalShader;

    // Texture Shader //
    Vector4                 m_vPickPos;
    LPDIRECT3DTEXTURE9      m_pTexture[4];
    LPDIRECT3DTEXTURE9      m_pAlphaDraw;
    LPDIRECT3DTEXTURE9      m_pAlpha;

    cBrush*                 m_pBrush;

    float                   m_TexDensity[4];                                            // Ÿ���� �е�
    int                     m_nTimer;

    // Wave Shader // 
    LPDIRECT3DTEXTURE9      m_pWaterTexture;

    D3DXVECTOR4             gWorldLightPosition;
    D3DXVECTOR4             gLightColor;

    float m_pHeight;                  // ���� ���������� ����
    float m_pWaveHeight;              // ����
    float m_pSpeed;                   // �����ӵ�
    float m_pUVSpeed;                 // �ؽ��İ� �������� �ӵ�
    float m_pWaveFrequency;           // ������ ����
    float m_pTransparent;             // ���� ����
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
    // Height : ���� ���������� ����, WaveHeight : ���� , Speed : �����ӵ�, UVSpeed : �ؽ��İ� �������� �ӵ�, WaveFrequency : ������ ����, Transparent : ���� ����
    void SetShader(/* char * sTexFile, char * sTexFileKey, */float fHeight = 0.0f, float fWaveHeight = 0.6f, float fSpeed = 2.4f,
        float fUVSpeed = 7.0f, float fWaveFrequency = 0.01f, float fTransparent = 0.6f);


    void SetMesh(LPMESH mesh1, LPMESH mesh2) { m_pMesh1 = mesh1; m_pMesh2 = mesh2; }
    void Render();
};

