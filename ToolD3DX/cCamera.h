#pragma once

#define LOOKAT_POS 1.0f
#define LIMITED_ROT 0.49f

class cCamera
{
private:
    float           m_fDistance;    // 큐브 기준 카메라 거리
    Vector3         m_vEye;         // 카메라 위치
    Vector3         m_vLookAt;      // 바라보는 위치
    Vector3         m_vUp;          // 임의의 업 벡터

	Vector3			m_vPosition;	// 카메라 포지션


    Matrix4         m_matView;
    Matrix4         m_matProj;

    float           m_fRotX;
    float           m_fRotY;
    POINT           m_ptPrevMouse;
    bool            m_isRButtonDown;
    bool            m_isFocus;
    HWND            m_hWnd;
public:
    cCamera();
    ~cCamera();

    void Setup(HWND hWnd);
    void Setup(bool focus);

    void Update(Vector3* pTarget = NULL);

    Matrix4 GetViewProjMatrix() { return m_matView * m_matProj; }
    
    // 세터
    void SetCameraPos(Vector3& vPos) { m_vPosition = vPos; }
};

