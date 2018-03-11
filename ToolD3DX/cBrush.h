#pragma once
class cBrush
{
public:
    //==============      ����ϰ� ĥ���� �귯���� ����     ===================

    int                     m_nNearMaxX;  
    int                     m_nNearMinX;
    int                     m_nNearMaxZ;
    int                     m_nNearMinZ;

    //==============      ������ ����� �귯���� ����     ===================

    int                     m_nFarMaxX;
    int                     m_nFarMinX;
    int                     m_nFarMaxZ;
    int                     m_nFarMinZ;

    //==============      �귯�� ����     ===================
    
    Vector4                 m_pPick;                                                // ��ŷ ��ġ ( 0 ~ 1)
    float                   m_fDrawDensity;                                             // �е�
    E_GROUND_TYPE           m_eGroundType;                                          // Ÿ��
    E_DRAW_TYPE             m_eDrawType;                                            // �׸��� Ÿ��
    float                   m_fSprayRadius;                                         // �������� ������ ( 0 ~ 1)
    float                   m_fBrushRadius;                                         // �귯�� ������ ( 0 ~ 1 )
    float                   m_fTex1Density;                                         // �ؽ���1 �е�
    float                   m_fTex2Density;                                         // �ؽ���2 �е�
    float                   m_fTex3Density;                                         // �ؽ���3 �е�

    //==============      ������ ����� ���� =================
    float                   m_fPickX;                                               // ��ŷ ��ġ (0 ~ 256)    
    float                   m_fPickZ;                                               // ��ŷ ��ġ (0 ~ 256)
    float                   m_fFR;                                                   // �������� ������ (0 ~ 256�̻�)    
    float                   m_fNR;                                                  // �귯�� ������ (0 ~ 256 �̻�)
    float                   m_fdR;                                                  // ������ ��

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

