#pragma once

#include "cObject.h"

class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256											// 기본 맵 크기
#define DEFAULT_G_TYPE			E_SOIL_GROUND										// 기본 지형 타입
#define DEFAULT_HEIGHT          128.0f                                              // 기본 맵 높이

class cMapTool : public cObject
{
private:
	cMapTerrainTool*			m_pTerrainTool;
	cMapObjectTool*				m_pObjectTool;

	E_MAP_SIZE&					m_eMapSize;											// 맵 사이즈
	E_GROUND_TYPE&				m_eDefaultGroundType;								// 기본 지형 타입
	float&						m_fDefaultHeight;									// 맵 기본 높이 값
	bool&						m_isDefaultWalkable;								// 걸을 수 있는지 여부 기본 값

    bool&                       m_isCreateMap;                                      // 맵을 새로 생성

private:

public:
    cMapTool();
    ~cMapTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	HRESULT CreateMap();						                                    // Create버튼을 눌렀을 때 발동
};

