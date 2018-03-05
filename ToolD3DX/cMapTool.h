#pragma once

#include "cObject.h"

class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256											// 기본 맵 크기
#define DEFAULT_G_TYPE			E_SOIL_GROUND										// 기본 지형 타입

class cMapTool : public cObject
{
private:
	cMapTerrainTool*			m_pTerrainTool;
	cMapObjectTool*				m_pObjectTool;

	E_MAP_SIZE					m_eMapSize;											// 맵 사이즈
	E_GROUND_TYPE				m_eDefaultGroundType;								// 기본 지형 타입
	int							m_nDefaultHeight;									// 맵 기본 높이 값
	bool						m_isDefaultWalkable;								// 걸을 수 있는지 여부 기본 값

private:

public:
    cMapTool();
    ~cMapTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	HRESULT SetMapSize(IN E_MAP_SIZE eMapSize);										// 맵 사이즈 셋팅
	HRESULT SetDefaultTextureType(IN E_GROUND_TYPE eGroundType);					// 기본 지형 텍스쳐 셋팅

	HRESULT CreateMap();															// Create버튼을 눌렀을 때 발동
};

