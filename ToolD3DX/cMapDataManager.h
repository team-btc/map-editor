#pragma once

#define g_pMapDataManager cMapDataManager::GetInstance()

class cMapTool;
class cWaterTap;
class cMapDataManager
{
	SINGLETON(cMapDataManager);

    // == 현재 탭 정보 ==
    SYNTHESIZE_PASS_BY_REF(E_TAB_TYPE, m_eTabType, TabType);                         // 탭 타입
    SYNTHESIZE_PASS_BY_REF(int, m_nDlgWidth, DlgWidth);                              // 다이얼로그 가로 사이즈

	// == 기본 맵 생성 시 필요한 정보 ==
	SYNTHESIZE_PASS_BY_REF(E_MAP_SIZE, m_eMapSize, MapSize);							// 맵사이즈
	SYNTHESIZE_PASS_BY_REF(float, m_fDefHeight, DefHeight);							// 맵 기본 높이 값
    SYNTHESIZE_PASS_BY_REF(bool, m_isCreateMap, CreateMap);                          // 맵 생성 여부
    SYNTHESIZE_PASS_BY_REF(bool, m_isTex1Load, IsTex1Load);                          // 기본 텍스쳐1 파일 로드 여부
    SYNTHESIZE_PASS_BY_REF(string, m_strTex1FilePath, Tex1FilePath);                 // 기본 텍스쳐1 파일 경로
    SYNTHESIZE_PASS_BY_REF(string, m_strTex1FileName, Tex1FileName);                 // 기본 텍스쳐1 파일 이름
    SYNTHESIZE_PASS_BY_REF(bool, m_isTex2Load, IsTex2Load);                          // 기본 텍스쳐2 파일 로드 여부
    SYNTHESIZE_PASS_BY_REF(string, m_strTex2FilePath, Tex2FilePath);                 // 기본 텍스쳐2 파일 경로
    SYNTHESIZE_PASS_BY_REF(string, m_strTex2FileName, Tex2FileName);                 // 기본 텍스쳐2 파일 이름
    SYNTHESIZE_PASS_BY_REF(bool, m_isTex3Load, IsTex3Load);                          // 기본 텍스쳐3 파일 로드 여부
    SYNTHESIZE_PASS_BY_REF(string, m_strTex3FilePath, Tex3FilePath);                 // 기본 텍스쳐3 파일 경로
    SYNTHESIZE_PASS_BY_REF(string, m_strTex3FileName, Tex3FileName);                 // 기본 텍스쳐3 파일 이름

	// == 지형 정보 ==
    SYNTHESIZE_PASS_BY_REF(E_UP_DOWN, m_eUpDown, TerUpDown);                         // 지형맵 편집 업다운 여부
	SYNTHESIZE_PASS_BY_REF(E_TERRAIN_EDIT_TYPE, m_eTerEditType, TerEditType);		// 지형맵 편집 타입
    SYNTHESIZE_PASS_BY_REF(float, m_fTerEditPower, TerEditPower);                    // 지형맵 편집 강도
    SYNTHESIZE_PASS_BY_REF(float, m_fTerEditHeight, TerEditHeight);                  // 지형맵 편집 높이
    SYNTHESIZE_PASS_BY_REF(E_TER_BRUSH_TYPE, m_eTerBrushType, TerBrushType);         // 지형맵 브러쉬 타입
	SYNTHESIZE_PASS_BY_REF(float, m_fTerBrushSize, TerBrushSize);					// 지형맵 브러쉬 사이즈

	// == 텍스쳐 정보 ==
	SYNTHESIZE_PASS_BY_REF(int, m_nCurrTexIndex, CurrTexIndex);				        // 현재 선택된 텍스쳐 인덱스
	SYNTHESIZE_PASS_BY_REF(float, m_fDrawDensity, DrawDensity);						// 텍스쳐맵 브러쉬 농도 값
	SYNTHESIZE_PASS_BY_REF(float, m_fTexBrushSize, TexBrushSize);					// 텍스쳐맵 브러쉬 사이즈
	SYNTHESIZE_PASS_BY_REF(float, m_fTexBrushDenSize, TexBrushDenSize);				// 텍스쳐맵 브러쉬 농도 사이즈
    SYNTHESIZE_PASS_BY_REF(float, m_fTexBrushDensity, TexBrushDensity);				// 텍스쳐맵 브러쉬 농도 값
    SYNTHESIZE_PASS_BY_REF(E_DRAW_TYPE, m_eDrawType, DrawType);				        // 텍스쳐맵 그리기 타입
    SYNTHESIZE_PASS_BY_REF(float, m_fTex1Density, Tex1Density);
    SYNTHESIZE_PASS_BY_REF(float, m_fTex2Density, Tex2Density);
    SYNTHESIZE_PASS_BY_REF(float, m_fTex3Density, Tex3Density);

	// == 물 정보 ==
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterHeight, WaterHeight);						// 물 기본 높이
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterUVSpeed, WaterUVSpeed);					// 물 UV 스피드
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterWaveHeight, WaterWaveHeight)				// 물 진폭
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterHeightSpeed, WaterHeightSpeed);			// 물 상하 스피드
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterFrequency, WaterFrequency);				// 물 물결 간격
	SYNTHESIZE_PASS_BY_REF(float, m_fWaterTransparent, WaterTransparent);			// 물 투명값
    SYNTHESIZE_PASS_BY_REF(float, m_fWaterDensity, WaterDensity);			// 물 밀도
    SYNTHESIZE_PASS_BY_REF(bool, m_isMakeWater, IsMakeWater);                        // 물 만들지 여부
    SYNTHESIZE_PASS_BY_REF(bool, m_isSetWaterFile, IsSetWaterFile);				    // 물 파일이 셋팅 되었을 때(클릭순간)
    SYNTHESIZE_PASS_BY_REF(string, m_strWaterFilePath, WaterFilePath);				// 물 파일경로
    SYNTHESIZE_PASS_BY_REF(string, m_strWaterFileName, WaterFileName);				// 물 파일 이름

    // == 하늘 정보 ==
    SYNTHESIZE_PASS_BY_REF(bool, m_isSetSkyFile, IsSetSkyFile);				        // 하늘 파일이 셋팅 되었을 때(클릭순간)
    SYNTHESIZE_PASS_BY_REF(string, m_strSkyFilePath, SkyFilePath);					// 하늘 파일경로
    SYNTHESIZE_PASS_BY_REF(string, m_strSkyFileName, SkyFileName);					// 하늘 파일이름

	// == 오브젝트 정보 ==
	// 오브젝트 파일리스트
	// 현재 오브젝트 리스트
	// 현재 선택한 오브젝트 파일
	// 현재 선택한 오브젝트 리스트
	// 오브젝트 복제
	// 오브젝트 삭제
	SYNTHESIZE_PASS_BY_REF(bool, m_isCollision, ObjCollision);						// 오브젝트 충돌 여부
	SYNTHESIZE_PASS_BY_REF(bool, m_isDestruction, ObjDestruction);					// 오브젝트 파괴 여부
	SYNTHESIZE_PASS_BY_REF(bool, m_isObjEnemy, ObjEnemy);							// 오브젝트 에너미
	SYNTHESIZE_PASS_BY_REF(float, m_fObjSize, ObjSize);								// 오브젝트 사이즈
	SYNTHESIZE_PASS_BY_REF(float, m_fObjPosX, ObjPosX);								// 오브젝트 X축 위치
	SYNTHESIZE_PASS_BY_REF(float, m_fObjPosY, ObjPosY);								// 오브젝트 Y축 위치
	SYNTHESIZE_PASS_BY_REF(float, m_fObjPosZ, ObjPosZ);								// 오브젝트 Z축 위치
	SYNTHESIZE_PASS_BY_REF(float, m_fObjRotX, ObjRotX);								// 오브젝트 X축 회전
	SYNTHESIZE_PASS_BY_REF(float, m_fObjRotY, ObjRotY);								// 오브젝트 Y축 회전
	SYNTHESIZE_PASS_BY_REF(float, m_fObjRotZ, ObjRotZ);								// 오브젝트 Z축 회전
    SYNTHESIZE_PASS_BY_REF(E_OBJECT_BUTTON_STATE, m_eObjectButtonState, ObjectButtonState);  // 오브젝트 만들기 버튼 클릭 상태 
    SYNTHESIZE_PASS_BY_REF(E_BLOCK_BUTTON_STATE, m_eBlockButtonState, BlockButtonState);     // 블록 그룹 만들기 버튼 클릭 상태 
	SYNTHESIZE_PASS_BY_REF(string, m_SelectBlockGroupName, SelectedBlockGroupName);          // 최근 선택한 블록 그룹 
	SYNTHESIZE_PASS_BY_REF(string, m_strFilePath, FilePath);							// x파일 파일경로
	SYNTHESIZE_PASS_BY_REF(string, m_strFileName, FileName);							// x파일 이름 .x 로 끝남
	SYNTHESIZE_PASS_BY_REF(string, m_sFileKey,  FileKey);								// x파일 파일경로에서 읽었던 파일의 키값
    // 리스트 포인터 
    SYNTHESIZE_PASS_BY_REF_NO_SET(CListBox*, m_pObjListBox, ObjListBox);                 // 오브젝트 리스트 박스
    SYNTHESIZE_PASS_BY_REF_NO_SET(CListBox*, m_pBlockGroupListBox, BlockGroupListBox);   // 블록그룹 리스트 박스 
	// 파일 경로 (불러오는)
	SYNTHESIZE_PASS_BY_REF(string, m_sFolderPath, FolderPath);
    // 블록그룹 만든 숫자
    SYNTHESIZE_PASS_BY_REF(int, m_nBlockMakeNum, BlockMakeNum);

	//==================텍스쳐 탭============================================================//
	// 텍스쳐1 
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTex1DensitySliderCtl, Tex1DensitySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTex1DensityEditCtl, Tex1DensityEditCtl);
	// 텍스쳐2
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTex2DensitySliderCtl, Tex2DensitySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTex2DensityEditCtl, Tex2DensityEditCtl);
	// 텍스쳐3
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTex3DensitySliderCtl, Tex3DensitySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTex3DensityEditCtl, Tex3DensityEditCtl);
	//==================워터 탭==============================================================//
	// 물 선택 체크
	SYNTHESIZE_PASS_BY_REF_NO_SET(CButton*, m_pWaterMakeCheck, WaterMakeCheck);
	// 물높이
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pWaterHeightSliderCtl, WaterHeightSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pWaterHeightEditCtl, WaterHeightEditCtl);
	// 물UV 스피드
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pUVSpeedSliderCtl, WaterUVSpeedSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pUVSpeedEditCtl, WaterUVSpeedEditCtl);
	// 물 파도 높이
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pWaveHeightSliderCtl, WaveHeightSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pWaveHeightEditCtl, WaveHeightEditCtl);
	// 물 파도 스피드
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pHeightSpeedSliderCtl, HeightSpeedSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pHeightSpeedEditCtl, HeightSpeedEditCtl);
	// 물 물결 간격
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pFrequencySliderCtl, FrequencySliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pFrequencyEditCtl, FrequencyEditCtl);
	// 물 투명값
	SYNTHESIZE_PASS_BY_REF_NO_SET(CSliderCtrl*, m_pTransparentSliderCtl, TransparentSliderCtl);
	SYNTHESIZE_PASS_BY_REF_NO_SET(CEdit*, m_pTransparentEditCtl, TransparentEditCtl);
    //======================이벤트=============================================================//
    SYNTHESIZE_PASS_BY_REF_NO_SET(E_EVENT_BUTTON_STATE, m_eEventButtonState, EventButtonState)
    SYNTHESIZE_PASS_BY_REF_NO_SET(string, m_sEventName, EventName);
    //SYNTHESIZE_PASS_BY_REF_NO_SET(CListBox*, m_pEventListBox, EventListBox);
    //SYNTHESIZE_PASS_BY_REF_NO_SET(string, m_sEventSelectName, EventSelectName);
private:
    cMapTool*       m_pMapTool;
public:
    void SetMapData();	// 기본 파일들 로드 해놓기
    void SetMapTool(cMapTool* maptool) { m_pMapTool = maptool; }
    json SaveMapData(string strFilePath, string strFileTitle);
    void LoadMapData(string sFilePath, string sFileTitle);
};