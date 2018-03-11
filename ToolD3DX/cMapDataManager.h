#pragma once

#define g_pMapDataManager cMapDataManager::GetInstance()

class cMapDataManager
{
	SINGLETON(cMapDataManager);

    // == 현재 탭 정보 ==
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_TAB_TYPE, m_eTabType, TabType);                         // 탭 타입
    SYNTHESIZE_PASS_BY_REF_NO_SET(int, m_nDlgWidth, DlgWidth);                              // 다이얼로그 가로 사이즈

	// == 기본 맵 생성 시 필요한 정보 ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_MAP_SIZE, m_eMapSize, MapSize);							// 맵사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eDefGroundType, DefGroundType);			// 기본 지형 타입
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fDefHeight, DefHeight);							// 맵 기본 높이 값
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isDefWalkable, DefWalkable);						// 걸을 수 있는지 여부 기본 값
    SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isCreateMap, CreateMap);                          // 맵 생성 여부

	// == 지형 정보 ==
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_UP_DOWN, m_eUpDown, TerUpDown);                         // 지형맵 편집 업다운 여부
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_TERRAIN_EDIT_TYPE, m_eTerEditType, TerEditType);		// 지형맵 편집 타입
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerEditPower, TerEditPower);                    // 지형맵 편집 강도
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerEditHeight, TerEditHeight);                  // 지형맵 편집 높이
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_TER_BRUSH_TYPE, m_eTerBrushType, TerBrushType);         // 지형맵 브러쉬 타입
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTerBrushSize, TerBrushSize);					// 지형맵 브러쉬 사이즈

	// == 텍스쳐 정보 ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(E_GROUND_TYPE, m_eCurrTexType, CurrTexType);				// 현재 선택된 텍스쳐 타입
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fDrawDensity, DrawDensity);						// 텍스쳐맵 브러쉬 농도 값
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexBrushSize, TexBrushSize);					// 텍스쳐맵 브러쉬 사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexBrushDenSize, TexBrushDenSize);				// 텍스쳐맵 브러쉬 농도 사이즈
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTexBrushDensity, TexBrushDensity);				// 텍스쳐맵 브러쉬 농도 값
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_DRAW_TYPE, m_eDrawType, DrawType);				        // 텍스쳐맵 그리기 타입
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTex1Density, Tex1Density);
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTex2Density, Tex2Density);
    SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fTex3Density, Tex3Density);

	// == 물 정보 ==
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterHeight, WaterHeight);						// 물 기본 높이
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterUVSpeed, WaterUVSpeed);					// 물 UV 스피드
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterWaveHeight, WaterWaveHeight)				// 물 진폭
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterHeightSpeed, WaterHeightSpeed);			// 물 상하 스피드
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterFrequency, WaterFrequency);				// 물 물결 간격
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fWaterTransparent, WaterTransparent);			// 물 투명값

	// == 오브젝트 정보 ==
	// 오브젝트 파일리스트
	// 현재 오브젝트 리스트
	// 현재 선택한 오브젝트 파일
	// 현재 선택한 오브젝트 리스트
	// 오브젝트 복제
	// 오브젝트 삭제
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isCollision, ObjCollision);						// 오브젝트 충돌 여부
	SYNTHESIZE_PASS_BY_REF_NO_SET(bool, m_isDestruction, ObjDestruction);					// 오브젝트 파괴 여부
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjSize, ObjSize);								// 오브젝트 사이즈
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjPosX, ObjPosX);								// 오브젝트 X축 위치
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjPosY, ObjPosY);								// 오브젝트 Y축 위치
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjPosZ, ObjPosZ);								// 오브젝트 Z축 위치
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjRotX, ObjRotX);								// 오브젝트 X축 회전
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjRotY, ObjRotY);								// 오브젝트 Y축 회전
	SYNTHESIZE_PASS_BY_REF_NO_SET(float, m_fObjRotZ, ObjRotZ);								// 오브젝트 Z축 회전

private:

};

