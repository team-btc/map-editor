#include "StdAfx.h"
#include "cMainGame.h"
#include <D3dx9math.h>
#include <stdio.h>

cMainGame::cMainGame(void)
    : m_szText("")
    , m_pCamera(NULL)
    , m_pSkinMesh(NULL)
    , m_vRot(0, 0, 0)
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

    m_pSkinMesh = new cSkinnedMesh("zealot", "unit/zealot", "zealot.x");
    g_pAutoReleasePool->AddObject(m_pSkinMesh);
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
}

void cMainGame::OnRender()
{
    g_pTimerManager->Render();

    Matrix4 matI;
    D3DXMatrixIdentity(&matI);
    g_pDevice->SetTransform(D3DTS_WORLD, &matI);
    
    if (m_pSkinMesh)
    {
        m_pSkinMesh->UpdateAndRender();
    }
}

void cMainGame::OnRelease()
{
    SAFE_DELETE(m_pCamera);
}