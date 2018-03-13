#include "StdAfx.h"
#include "D3DApp.h"


CD3DApp::CD3DApp(void)
{
}


CD3DApp::~CD3DApp(void)
{
}


HRESULT CD3DApp::InitD3D(HWND hWnd)
{
    m_hWnd = hWnd;

    if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // ��� �ø���, �⺻�� D3D�� �ø��� ������ ����

    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                    &d3dpp, &m_pd3dDevice)))
    {
        return E_FAIL;
    }

    g_pDeviceManager->SetDevice(m_pd3dDevice);
    
    OnInit();

    return S_OK;
}

void CD3DApp::Render()
{
    if (NULL == m_pd3dDevice)
        return;

    // Clear the backbuffer to a blue color
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 50, 170), 1.0f, 0);

    // Begin the scene
    if (SUCCEEDED(m_pd3dDevice->BeginScene()))
    {
        OnRender();

        // End the scene
        m_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

}

void CD3DApp::Update()
{
    OnUpdate();
}

void CD3DApp::Cleanup()
{
    OnRelease();

    if (m_pd3dDevice != NULL)
        m_pd3dDevice->Release();

    if (m_pD3D != NULL)
        m_pD3D->Release();
}