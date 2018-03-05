#pragma once

#define g_pMapDataManager cMapDataManager::GetInstance()

class cMapDataManager
{
	SINGLETON(cMapDataManager);

	// == 기본 맵 생성 시 필요한 정보 ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_MAP_SIZE, m_eMapSize, MapSize);							// 맵사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eDefaultGroundType, DefaultGroundType);	// 기본 지형 타입
	SYNTHESIZE_PASS_BY_REF_NO_SET(int, m_nDefaultHeight, DefaultHeight);					// 맵 기본 높이 값
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isDefaultWalkable, DefaultWalkable);				// 걸을 수 있는지 여부 기본 값

	// == 지형 정보 ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_TERRAIN_EDIT_TYPE, m_eTerrainEditType, TerrainEditType);// 지형맵 편집 타입
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fIncrementHeight, IncrementHeight);				// 높이 증가값(정해진 간격마다 올라가는 높이값)
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fGradient, Gradient);							// 경사 값
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerrainBrushSize, TrrainBrushSize);				// 지형맵 브러쉬 사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerrainFlatSize, TrrainFlatSize);				// 지형맵 평지 사이즈

	// == 텍스쳐 정보 ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eCurrTextureType, CurrTextureType);		// 현재 선택된 텍스쳐 타입
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isWalkable, Walkable);
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTextureBrushSize, TextureBrushSize);			// 텍스쳐맵 브러쉬 사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTextureBrushDenSize, TextureBrushDenSize);		// 텍스쳐맵 브러쉬 농도 사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTextureDensity, TextureDensity);				// 텍스쳐맵 브러쉬 농도 값

	// == 물 정보 ==


	// == 오브젝트 정보 ==


public:
	cMapDataManager();
	~cMapDataManager();
};

