#include "stdafx.h"
#include "cMapTool.h"
#include "cMapTerrainTool.h"
#include "cMapObjectTool.h"

cMapTool::cMapTool()
	: m_pTerrainTool(NULL)
	, m_pObjectTool(NULL)
	, m_eMapSize(DEFAULT_MAP_SIZE)
	, m_eDefaultGroundType(E_SOIL_GROUND)
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
	return S_OK;
}

HRESULT cMapTool::Update()
{
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

HRESULT cMapTool::SetMapSize(IN E_MAP_SIZE eMapSize)
{
	// 예외처리
	if (eMapSize < E_MAP_SIZE_BEGIN || eMapSize >= E_MAP_SIZE_MAX)
	{
		return E_INVALIDARG;
	}

	m_eMapSize = eMapSize;

	return S_OK;
}

HRESULT cMapTool::SetDefaultTextureType(IN E_GROUND_TYPE eGroundType)
{
	// 예외처리
	if (eGroundType < E_GROUND_TYPE_BEGIN || eGroundType >= E_GROUND_TYPE_MAX)
	{
		return E_INVALIDARG;
	}

	m_eDefaultGroundType = eGroundType;

	return S_OK;
}

// 셋팅한 기본 설정으로 맵 만들기
HRESULT cMapTool::CreateMap()
{
	m_pTerrainTool = new cMapTerrainTool;
	m_pTerrainTool->Setup(m_eMapSize, m_eDefaultGroundType);

	m_pObjectTool = new cMapObjectTool;
	m_pObjectTool->Setup();

	return S_OK;
}
