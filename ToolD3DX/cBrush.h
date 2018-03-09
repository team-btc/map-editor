#pragma once
class cBrush
{
public:
    //==============      깔끔하게 칠해질 브러쉬의 범위     ===================

    int                     m_nNearMaxX;  
    int                     m_nNearMinX;
    int                     m_nNearMaxZ;
    int                     m_nNearMinZ;

    //==============      보간을 사용할 브러쉬의 범위     ===================

    int                     m_nFarMaxX;
    int                     m_nFarMinX;
    int                     m_nFarMaxZ;
    int                     m_nFarMinZ;

    //==============      브러쉬 정보     ===================
    
    Vector4                 m_pPick;                                                // 픽킹 위치 ( 0 ~ 1)
    float                   m_fDrawDensity;                                             // 밀도
    E_GROUND_TYPE           m_eGroundType;                                          // 타일
    E_DRAW_TYPE             m_eDrawType;                                            // 그리기 타입
    float                   m_fSprayRadius;                                         // 스프레이 반지름 ( 0 ~ 1)
    float                   m_fBrushRadius;                                         // 브러쉬 반지름 ( 0 ~ 1 )
    float                   m_fTex1Density;                                         // 텍스쳐1 밀도
    float                   m_fTex2Density;                                         // 텍스쳐2 밀도
    float                   m_fTex3Density;                                         // 텍스쳐3 밀도

    //==============      보간때 사용할 정보 =================
    float                   m_fPickX;                                               // 픽킹 위치 (0 ~ 256)    
    float                   m_fPickZ;                                               // 픽킹 위치 (0 ~ 256)
    float                   m_fFR;                                                   // 스프레이 반지름 (0 ~ 256이상)    
    float                   m_fNR;                                                  // 브러쉬 반지름 (0 ~ 256 이상)
    float                   m_fdR;                                                  // 반지름 차

    //float fCX = m_pPick.x * 256.0f;
    //float fCY = m_pPick.z * 256.0f;
    //float r = m_fSprayRadius * 256.0f;
    //float nr = m_fBrushRadius * 256.0f;
    //float R = r - nr;

public:
    void SetBrush(Vector4 v, float br, float sr, float drawdensity, float tex1density, float tex2density, float tex3density);
    void GetRect();
    void SetType(E_GROUND_TYPE G_Type, E_DRAW_TYPE D_Type) { m_eGroundType = G_Type; m_eDrawType = D_Type; }
    cBrush();
    ~cBrush();
};

