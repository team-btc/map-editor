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

    float                   m_TexDensity[3];                        // 타일의 밀도
    int                     m_nTimer;

    string                  m_sMapKey;

    // Relate to Character Picking ======================================================================

    bool                    m_isSelectPlayer;                         // 캐릭터를 선택했는가(필요합미꽈?)                    
    bool                    m_isSelectEnemy;                          // 적을 선택했는감
    bool                    m_isSelectNPC;                          // 적을 선택했는감


    Vector4                 m_vPlayerPos;                           // 플레이어 위치 (맵 크기로 노나줘야함)
    Vector4                 m_vTargetPos;                            // 적 위치 (맵 크기로 노나줘야함)

    float                   m_fPlayerScale;                         // 플레이어 크기
    float                   m_fTargetScale;                          // 적군 크기

    Vector4                 m_vPlayerColor;                         // 플레이어 원 색
    Vector4                 m_vEnemyColor;                          // Circle Color of Enemy's Bottom
    Vector4                 m_vNPCColor;                            // NPC 밑바닥 원 타일 색상


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

