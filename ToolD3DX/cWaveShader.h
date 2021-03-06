#pragma once

class cWaveShader
{
private:
    LPMESH				    m_pMesh;
    LPD3DXEFFECT			m_pWaveShader;
    LPDIRECT3DTEXTURE9      m_pTexture;

    D3DXVECTOR4             gWorldLightPosition;
    D3DXVECTOR4             gLightColor;
    // Wave 변수
    float m_pHeight;                  // 물의 지형에서의 높이
    float m_pWaveHeight;              // 진폭
    float m_pSpeed;                   // 진동속도
    float m_pUVSpeed;                 // 텍스쳐가 지나가는 속도
    float m_pWaveFrequency;           // 물결의 간격
    float m_pTransparent;             // 물의 투명도
    float m_pDensity;                 // 물의 밀도
public:
    cWaveShader();
    ~cWaveShader();

    // Height : 물의 지형에서의 높이, WaveHeight : 진폭 , Speed : 진동속도, UVSpeed : 텍스쳐가 지나가는 속도, WaveFrequency : 물결의 간격, Transparent : 물의 투명도
    void SetShader(/* char * sTexFile, char * sTexFileKey, */float fHeight = 0.0f, float fWaveHeight = 0.6f, float fSpeed = 2.4f,
        float fUVSpeed = 7.0f, float fWaveFrequency = 0.01f, float fTransparent = 0.6f, float fDensity = 1.0f);
    void SetMesh(LPMESH mesh);
    void SetWaveTexture(string strFilePath, string strFileName);

    void Render(D3DXVECTOR4 vCameraPosition);
};

