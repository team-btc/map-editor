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

    float                   m_TexDensity[3];                        // Ÿ���� �е�
    int                     m_nTimer;

    string                  m_sMapKey;

    // Relate to Character Picking ======================================================================

    bool                    m_isSelectPlayer;                         // ĳ���͸� �����ߴ°�(�ʿ��չ̲�?)                    
    bool                    m_isSelectEnemy;                          // ���� �����ߴ°�
    bool                    m_isSelectNPC;                          // ���� �����ߴ°�


    Vector4                 m_vPlayerPos;                           // �÷��̾� ��ġ (�� ũ��� �볪�����)
    Vector4                 m_vTargetPos;                            // �� ��ġ (�� ũ��� �볪�����)

    float                   m_fPlayerScale;                         // �÷��̾� ũ��
    float                   m_fTargetScale;                          // ���� ũ��

    Vector4                 m_vPlayerColor;                         // �÷��̾� �� ��
    Vector4                 m_vEnemyColor;                          // Circle Color of Enemy's Bottom
    Vector4                 m_vNPCColor;                            // NPC �عٴ� �� Ÿ�� ����


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
    void SaveTexture(string strFilePath, string strFileTitle);
    void SetMapSize(string* MapKey = NULL);

    void Update();
    void Render();
};

