#include "stdafx.h"
#include "cMapTool.h"
#include "cMapTerrainTool.h"
#include "cMapObjectTool.h"

cMapTool::cMapTool()
	: m_pTerrainTool(NULL)
	, m_pObjectTool(NULL)
    , m_eMapSize(g_pMapDataManager->GetMapSize())
    , m_eDefaultGroundType(g_pMapDataManager->GetDefGroundType())
    , m_fDefaultHeight(g_pMapDataManager->GetDefHeight())
    , m_isDefaultWalkable(g_pMapDataManager->GetDefWalkable())
    , m_isCreateMap(g_pMapDataManager->GetCreateMap())
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
