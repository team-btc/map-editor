#include "StdAfx.h"
#include "cMainGame.h"
#include <D3dx9math.h>
#include <stdio.h>

cMainGame::cMainGame(void)
    : m_szText("")
    , m_pCamera(NULL)
    , m_vRot(0, 0, 0)
	, m_pMapTool(NULL)
{
}


cMainGame::~cMainGame(void)
{
}

void cMainGame::OnInit()
{
    g_pKeyManager->Setup();

    m_pCamera = new cCamera;
    m_pCamera->Setup(m_hWnd);

	m_pMapTool = new cMapTool;
	m_pMapTool->Setup();
	m_pMapTool->CreateMap();

}

void cMainGame::OnUpdate()
{
    g_pTimerManager->Update(60.0f);

    if (m_pCamera)
    {
        m_pCamera->Update();
    }

    if (g_pKeyManager->isStayKeyDown('A'))
    {
        m_vRot.y -= 1.0f;
    }
    else if (g_pKeyManager->isStayKeyDown('D'))
    {
        m_vRot.y += 1.0f;
    }

    if (g_pKeyManager->isStayKeyDown('W'))
    {
        m_vRot.x += 1.0f;
    }
    else if (g_pKeyManager->isStayKeyDown('S'))
    {
        m_vRot.x -= 1.0f;
    }
	
	if (m_pMapTool)
	{
		m_pMapTool->Update();
	}
}

void cMainGame::OnRender()
{
    g_pTimerManager->Render();

    Matrix4 matI;
    D3DXMatrixIdentity(&matI);
    g_pDevice->SetTransform(D3DTS_WORLD, &matI);
    
	if (m_pMapTool)
	{
		m_pMapTool->Render();
	}
}

void cMainGame::OnRelease()
{
    SAFE_DELETE(m_pCamera);
	SAFE_RELEASE(m_pMapTool);
}