#include "stdafx.h"
#include "cMapTool.h"
#include "cMapTerrainTool.h"
#include "cMapObjectTool.h"
#include "cRay.h"
cMapTool::cMapTool()
	: m_pTerrainTool(NULL)
	, m_pObjectTool(NULL)
    , m_eMapSize(g_pMapDataManager->GetMapSize())
    , m_eDefaultGroundType(g_pMapDataManager->GetDefGroundType())
    , m_fDefaultHeight(g_pMapDataManager->GetDefHeight())
    , m_isDefaultWalkable(g_pMapDataManager->GetDefWalkable())
    , m_isCreateMap(g_pMapDataManager->GetCreateMap())
    , m_pRay(NULL)
    , v(0,0,0)
{
}
cMapTool::~cMapTool()
{
	// 메모리 관리 설정하면 이부분은 삭제 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	SAFE_RELEASE(m_pTerrainTool);
	SAFE_RELEASE(m_pObjectTool);
}

HRESULT cMapTool::GetPtMouse()
{
    if (m_pTerrainTool->GetMesh() == NULL)
    {
        return E_FAIL;
    }
    POINT   ptMouse;
    GetCursorPos(&ptMouse);
    m_pRay->m_vOrg = Vector3(ptMouse.x, ptMouse.y, 0);
    m_pRay->m_vDir = Vector3(0, 0, 1);
    *m_pRay = cRay::RayAtWorldSpace(ptMouse.x, ptMouse.y);
    BOOL isHit = false;
    float fDist;
    
    D3DXIntersectSubset(m_pTerrainTool->GetMesh(), 0, &m_pRay->m_vOrg, &m_pRay->m_vDir, &isHit, NULL, NULL, NULL, &fDist, NULL, NULL);
    if (isHit)
    {
        v = m_pRay->m_vOrg + m_pRay->m_vDir * fDist;
    }

    return S_OK;
}

void cMapTool::RendPtMouse()
{
   
    RECT rt = { 0, 30, W_WIDTH, W_HEIGHT };
    string s = "Mouse : ";
    s = s + to_string((int)v.x) + " , " + to_string((int)v.y) + " , " + to_string((int)v.z);
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));
}

HRESULT cMapTool::Setup()
{
    m_pRay = new cRay;
    m_eMapSize = DEFAULT_MAP_SIZE;
    m_eDefaultGroundType = E_SOIL_GROUND;
    m_fDefaultHeight = DEFAULT_HEIGHT;
    m_isDefaultWalkable = true;

    m_pTerrainTool = new cMapTerrainTool;
    m_pTerrainTool->Setup();

    m_pObjectTool = new cMapObjectTool;
    m_pObjectTool->Setup();
   
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
