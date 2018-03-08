#include "stdafx.h"
#include "cMapTool.h"
#include "cMapTerrainTool.h"
#include "cMapObjectTool.h"
#include "cRay.h"

cMapTool::cMapTool()
	: m_pTerrainTool(NULL)
	, m_pObjectTool(NULL)
    , m_eCurrTabType(g_pMapDataManager->GetTabType())
    , m_eMapSize(g_pMapDataManager->GetMapSize())
    , m_eDefaultGroundType(g_pMapDataManager->GetDefGroundType())
    , m_fDefaultHeight(g_pMapDataManager->GetDefHeight())
    , m_isDefaultWalkable(g_pMapDataManager->GetDefWalkable())
    , m_isCreateMap(g_pMapDataManager->GetCreateMap())
    , m_pRay(NULL)
    , m_vPickPos(0, 0, 0)
{
}
cMapTool::~cMapTool()
{
	// 메모리 관리 설정하면 이부분은 삭제 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	SAFE_RELEASE(m_pTerrainTool);
	SAFE_RELEASE(m_pObjectTool);
}

HRESULT cMapTool::Setup()
{
    m_pRay = new cRay;

    m_eCurrTabType = E_CREATE_TAB;
    m_eMapSize = DEFAULT_MAP_SIZE;
    m_eDefaultGroundType = E_SOIL_GROUND;
    m_fDefaultHeight = DEFAULT_HEIGHT;
    m_isDefaultWalkable = true;

    m_pTerrainTool = new cMapTerrainTool;
    m_pTerrainTool->Setup();
    m_pTerrainTool->SetPickPos(&m_vPickPos);

    m_pObjectTool = new cMapObjectTool;
    m_pObjectTool->Setup();
	m_pObjectTool->SetPickPos(&m_vPickPos);
	return S_OK;
}

HRESULT cMapTool::Update()
{
    GetPtMouse();

    if (m_isCreateMap)
    {
        CreateMap();
    }
	if (m_pTerrainTool)
	{
		m_pTerrainTool->Update();
	}
	if (m_pObjectTool)
	{
		m_pObjectTool->Update();
	}

    // 왼쪽 마우스를 클릭 했고, 클라이언트 영역 안에 있는 맵을 클릭했으면
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && IsPickMap())
    {
        if (m_pTerrainTool && (m_eCurrTabType == E_TERRAIN_TAB || m_eCurrTabType == E_TEXTURE_TAB))
        {
            m_pTerrainTool->OnceLButtonDown(m_eCurrTabType);
        }
        else if (m_pObjectTool && m_eCurrTabType == E_OBJECT_TAB)
        {
            m_pObjectTool->OnceLButtonDown();
        }
    }

    // 왼쪽 마우스를 계속 누르고 있고, 마우스가 클라이언트 영역 안에 있으면
    if (g_pKeyManager->isStayKeyDown(VK_LBUTTON) && IsPickMap())
    {
        if (m_pTerrainTool && (m_eCurrTabType == E_TERRAIN_TAB || m_eCurrTabType == E_TEXTURE_TAB))
        {
            m_pTerrainTool->StayLButtonDown(m_eCurrTabType);
        }
        else if (m_pObjectTool && m_eCurrTabType == E_OBJECT_TAB)
        {
            m_pObjectTool->StayLButtonDown();
        }
    }
  
	return S_OK;
}

HRESULT cMapTool::Render()
{
   
	if (m_pTerrainTool)
	{
		m_pTerrainTool->Render();
	}
	if (m_pObjectTool)
	{
		m_pObjectTool->Render();
	}

    RendPtMouse();
    return S_OK;
}

// 셋팅한 기본 설정으로 맵 만들기
HRESULT cMapTool::CreateMap()
{
    m_isCreateMap = false;

    if (m_pTerrainTool)
    {
        m_pTerrainTool->CreateMap(m_eMapSize, m_eDefaultGroundType, m_fDefaultHeight, m_isDefaultWalkable);
    }
    
	return S_OK;
}

// 마우스 위치 가져오기
HRESULT cMapTool::GetPtMouse()
{
    if (m_pTerrainTool->GetMesh() == NULL)
    {
        return E_FAIL;
    }

    *m_pRay = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

    BOOL isHit = false;
    float fDist;
    D3DXIntersectSubset(m_pTerrainTool->GetMesh(), 0, &m_pRay->m_vOrg, &m_pRay->m_vDir, &isHit, NULL, NULL, NULL, &fDist, NULL, NULL);
    if (isHit)
    {
        m_vPickPos = m_pRay->m_vOrg + m_pRay->m_vDir * fDist;
    }

    return S_OK;
}

// 마우스 위치 출력
void cMapTool::RendPtMouse()
{
    RECT rt = { 0, 30, W_WIDTH, W_HEIGHT };
    string s = "MousePos : ";
    s = s + to_string((int)g_ptMouse.x) + " , " + to_string((int)g_ptMouse.y);
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));

    rt = { 0, 45, W_WIDTH, W_HEIGHT };
    s = "PickPos : ";
    s = s + to_string((int)m_vPickPos.x) + " , " + to_string((int)m_vPickPos.y) + " , " + to_string((int)m_vPickPos.z);
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));
}

// 마우스가 클라이언트 영역 안에서 맵을 클릭 했는지 체크
bool cMapTool::IsPickMap()
{
    RECT rtClient;
    GetClientRect(g_hWnd, &rtClient);
    
    POINT ptCurrMouse;
    GetCursorPos(&ptCurrMouse); // 윈도우 상의 마우스 좌표를 넘겨줌

    ScreenToClient(g_hWnd, &ptCurrMouse); // 윈도우 상의 마우스 좌표를 클라이언트 상의 좌표로 바꿔줌!

    // MFC에서 작업표시줄 크기 구하는 방법! (작업표시줄 윈도우 핸들, 크기 구함)
    HWND hWndTrayWnd = ::FindWindow("Shell_TrayWnd", "");
    RECT rt;
    int nTrayHeight = 0;
    if (hWndTrayWnd)
    {
        ::GetWindowRect(hWndTrayWnd, &rt);
        nTrayHeight = rt.bottom - rt.top;
    }

    // 작업표시줄 높이 만큼 마우스위치를 옮기고, 클라이언트 영역을 줄인다.
    ptCurrMouse.y -= nTrayHeight;
    rtClient.bottom -= nTrayHeight;

    // 다이얼로그 너비만큼 클라이언트 영역을 줄인다.
    int nDlgWidth = g_pMapDataManager->GetDlgWidth();
    rtClient.right -= nDlgWidth;

    bool isPick = false;

    // 마우스가 클라이언트 영역 안에 있는지 체크
    if (ptCurrMouse.x > rtClient.left && ptCurrMouse.x < rtClient.right
        && ptCurrMouse.y > rtClient.top && ptCurrMouse.y < rtClient.bottom)
    {
        // 맵을 클릭 했는지 체크
        BOOL isHit = false;
        float fDist = 0;
        D3DXIntersectSubset(m_pTerrainTool->GetMesh(), 0, &m_pRay->m_vOrg, &m_pRay->m_vDir, &isHit, NULL, NULL, NULL, &fDist, NULL, NULL);
        if (isHit)
        {
            m_vPickPos = m_pRay->m_vOrg + m_pRay->m_vDir * fDist;
            isPick = true;
        }
    }
    return isPick;
}
