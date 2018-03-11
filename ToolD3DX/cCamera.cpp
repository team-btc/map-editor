#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
    : m_fDistance(250)
    , m_vEye(0, LOOKAT_POS, -m_fDistance)
    , m_vLookAt(0, LOOKAT_POS, 0)
    , m_vUp(0, 1, 0)
    , m_fRotX(0.9)
    , m_fRotY(0)
    , m_isRButtonDown(false)
    , m_isFocus(false)
	, m_vPosition(0, 0, 0)
{
}


cCamera::~cCamera()
{
}

void cCamera::Setup(HWND hWnd)
{
    m_hWnd = hWnd;
    RECT rect;
    D3DVIEWPORT9 vp;
    GetClientRect(m_hWnd, &rect);

    vp.X = 0;
    vp.Y = 0;
    vp.Width = rect.right - rect.left;  // 좌표개념이 아니라 크기 개념 800, 600 계산됨
    vp.Height = rect.bottom - rect.top;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;

    D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, (float)vp.Width / (float)vp.Height, 1.0f, 1000.0f);
    g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    g_pDevice->SetViewport(&vp);

    //RECT rc;
    //GetClientRect(g_hWnd, &rc);

    //Matrix4 matProj;
    //D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
    //g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Setup(bool focus)
{
    m_isFocus = focus;
    RECT rc;
    GetClientRect(g_hWnd, &rc);

    float fovy = 45.0f;
    if (m_isFocus)
    {
        fovy = 10.0f;
    }

    Matrix4 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(fovy), rc.right / (float)rc.bottom, 1, 1000);
    g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update(Vector3* pTarget)
{
	m_vEye = D3DXVECTOR3(0, LOOKAT_POS, -m_fDistance);

	// == 마우스 컨트롤 =======
	if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
	{
		m_isRButtonDown = true;
        m_ptPrevMouse = g_ptMouse;
	}
	if (g_pKeyManager->isOnceKeyUp(VK_RBUTTON))
	{
		m_isRButtonDown = false;
	}
	if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
	{
		if (m_isRButtonDown)
		{
			POINT ptCurrMouse;
            ptCurrMouse = g_ptMouse;

			m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 100.0f;
			m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 100.0f;

			// x축 회전은 0 ~ 90 으로 고정
            if (m_fRotX < 0)//-D3DX_PI * LIMITED_ROT + D3DX_16F_EPSILON)
            {
                m_fRotX = 0;// -D3DX_PI * LIMITED_ROT + D3DX_16F_EPSILON;
            }
            else if (m_fRotX > D3DX_PI * LIMITED_ROT - D3DX_16F_EPSILON)
            {
                m_fRotX = D3DX_PI * LIMITED_ROT - D3DX_16F_EPSILON;
            }

			m_ptPrevMouse = ptCurrMouse;
		}
	}
	if (g_nWheelDelta != 0)
	{
		m_fDistance -= g_nWheelDelta * 0.1f;
		g_nWheelDelta = 0;

        if (m_fDistance < 5.0f)
        {
            m_fDistance = 5.0f;
        }
	}

	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fRotX);
	D3DXMatrixRotationY(&matRotY, m_fRotY);

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &(matRotX * matRotY));

	// 카메라가 고정으로 봐야하는 타겟이 있다면
	if (pTarget)
	{
		m_vLookAt = *pTarget;
		m_vLookAt.y += LOOKAT_POS;
		m_vPosition = *pTarget;
	}
    

	// 카메라를 컨트롤 해야 한다면
    else
    {
        if (g_pKeyManager->isStayKeyDown('A')
            || g_pKeyManager->isStayKeyDown('D')
            || g_pKeyManager->isStayKeyDown('W')
            || g_pKeyManager->isStayKeyDown('S'))
        {
            D3DXVECTOR3 dirX, dirZ;
            D3DXVec3Normalize(&dirZ, &m_vEye);
            D3DXVec3Cross(&dirX, &m_vEye, &D3DXVECTOR3(0, 1, 0));
            D3DXVec3Cross(&dirZ, &dirX, &D3DXVECTOR3(0, 1, 0));
            float fMovePower = m_fDistance * 0.0001f;

            // == 키보드 컨트롤 ======= 
            if (g_pKeyManager->isStayKeyDown('A'))
            {
                m_vPosition -= dirX * fMovePower;
                m_vLookAt -= dirX * fMovePower;
            }
            if (g_pKeyManager->isStayKeyDown('D'))
            {
                m_vPosition += dirX * fMovePower;
                m_vLookAt += dirX * fMovePower;
            }
            if (g_pKeyManager->isStayKeyDown('W'))
            {
                m_vPosition += dirZ * fMovePower;
                m_vLookAt += dirZ * fMovePower;
            }
            if (g_pKeyManager->isStayKeyDown('S'))
            {
                m_vPosition -= dirZ * fMovePower;
                m_vLookAt -= dirZ * fMovePower;
            }
        }
    }

	m_vEye += m_vPosition;

	// 뷰 메트릭스 셋팅
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &D3DXVECTOR3(0, 1, 0));
	g_pDevice->SetTransform(D3DTS_VIEW, &matView);

    g_vCameraPos = m_vEye;

    //// x축 회전은 -90 ~ 90 으로 고정
    //if (m_fRotX < -LIMITED_ROT + D3DX_16F_EPSILON)
    //{
    //    m_fRotX = -LIMITED_ROT + D3DX_16F_EPSILON;
    //}
    //else if (m_fRotX > LIMITED_ROT - D3DX_16F_EPSILON)
    //{
    //    m_fRotX = LIMITED_ROT - D3DX_16F_EPSILON;
    //}

    //if (m_fRotY >= 360.0f)
    //{
    //    m_fRotY -= 360.0f;
    //}
    //// 뷰 매트릭스 셋팅 - 타겟 == 큐브의 포지션
    //m_vEye = Vector3(0, 0, -m_fDistance);

    //Matrix4 matRotX, matRotY;
    //D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fRotX));
    //D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fRotY));

    //D3DXVec3TransformCoord(&m_vEye, &m_vEye, &(matRotX * matRotY));

    //Vector3 vDirZ, vDirX;
    //D3DXVec3Normalize(&vDirZ, &m_vEye);
    //D3DXVec3Cross(&vDirX, &vDirZ, &Vector3(0, 1, 0));
    //D3DXVec3Cross(&vDirZ, &vDirX, &Vector3(0, 1, 0));

    //if (pTarget)
    //{
    //    m_vLookAt = *pTarget;
    //    m_vLookAt.y += LOOKAT_POS;
    //    m_vEye = m_vEye + *pTarget;
    //}

    //Matrix4 matView;
    //D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &Vector3(0, 1, 0));
    //g_pDevice->SetTransform(D3DTS_VIEW, &matView);
}