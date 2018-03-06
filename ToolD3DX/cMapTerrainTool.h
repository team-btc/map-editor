﻿#pragma once

#include "cObject.h"

#define GT_MAX_NUM			4														// 지형 타입 개수
#define DEFAULT_BLD			1.0f													// 블렌딩 기본 값
#define DEFAULT_OBJ_PROP	E_OBJ_NONE												// 오브젝트 성질 기본 값
#define DEFAULT_BR_SZ		10.0f													// 브러쉬 기본 사이즈
#define DEFAULT_BRD_SZ		5.0f													// 브러쉬 농도 기본 사이즈
#define DEFAULT_BRD			0.5f													// 브러쉬 기본 농도 값
#define DEFAULT_TXD			1.0f													// 텍스쳐 기본 농도값
#define WATER_BRUSH_SIZE	8.0f													// 물 브러쉬 기본 사이즈
#define DEFAULT_FLUID_SPEED 0.5f													// 물 기본 유속
#define DEFAULT_FOLDER		"*/Map/"												// 기본 파일 폴더
#define DEFAULT_FILE_NAME	"MapData"												// 기본 파일명


// 면 정보
struct ST_TERRAIN_FACE_INFO {
	DWORD							dVertexIndedArr[3];								// 면이 가지고 있는 삼 각형 인덱스
	E_GROUND_TYPE                   eGroundType[GT_MAX_NUM];
    float                           fBlending[GT_MAX_NUM];
    bool                            isWalkable;                                     // true 면 지나갈 수있음
	E_OBJECT_PROPERTY               eObjProp;                                       // 오브젝트 성질 (파괴여부, 충돌여부)

	ST_TERRAIN_FACE_INFO() {
		for (int i = 0; i < GT_MAX_NUM; ++i)
		{
			eGroundType[i] = E_SOIL_GROUND;
		}
		for (int i = 0; i < GT_MAX_NUM; ++i)
		{
			fBlending[i] = 0.0f;
		}
	}
};

// 지형 브러쉬 정보
struct ST_TER_BRUSH_INFO {
	float&							fTerrainBrushSize;								// 지형 브러쉬 사이즈
	float&							fTerrainFlatSize;							    // 지형 평지 사이즈
    float&							fIncrementHeight;								// 높이 증가값(정해진 간격마다 올라가는 높이값)
    float&							fGradient;									    // 경사값

    ST_TER_BRUSH_INFO(float& _fBS, float& _fFS, float& _fI, float& _fG)
        : fTerrainBrushSize(_fBS), fTerrainFlatSize(_fFS), fIncrementHeight(_fI), fGradient(_fG) {}
};

// 텍스쳐 브러쉬 정보
struct ST_TEX_BRUSH_INFO {
    E_GROUND_TYPE&                  m_eCurrTextureType;								// 현재 선택된 텍스쳐
    bool&                           m_isWalkable;                                   // 걸을 수 있는지 여부
    float&							fTextureDensity;								// 텍스쳐 농도 값
    float&							fTextureBrushSize;								// 텍스쳐 브러쉬 사이즈
    float&							fTextureBrushDenSize;							// 텍스쳐 브러쉬 농도 사이즈
    float&							fTexturBrushDensity;							// 텍스쳐 브러쉬 농도 값

    ST_TEX_BRUSH_INFO(E_GROUND_TYPE& _eCTT, bool& _isW, float& _fTD, float& _fBS, float& _fBDS, float& _fBD)
        : m_eCurrTextureType(_eCTT), m_isWalkable(_isW), fTextureDensity(_fTD)
        , fTextureBrushSize(_fBS), fTextureBrushDenSize(_fBDS), fTexturBrushDensity(_fBD) {}

};

// 물 정보
struct ST_WATER_INFO {
	//Vector2							vPosition;									// 물의 중앙 위치
	float&						    fHeight;										// 물의 높이
	float&						    fUVSpeed;										// UV 스피드
    float&                          fWaveHeight;                                    // 물의 진폭
    float&                          fHeightSpeed;                                   // 물의 상하 스피드
    float&                          fFrequency;                                     // 물결 간격
	float&						    fTransparent;									// 물의 투명값

    ST_WATER_INFO(float& _fH, float& _fUVS, float& _fWH, float& _fHS, float& _fF, float& _fT)
        : fHeight(_fH), fUVSpeed(_fUVS), fWaveHeight(_fWH)
        , fHeightSpeed(_fHS), fFrequency(_fF), fTransparent(_fT) {}
};

class cMapTerrainTool : public cObject
{
private:
    POINT                           m_ptSize;                                       // 맵 크기

	vector<ST_PT_VERTEX>            m_vecPTVertex;                                  // 맵에 사용할 점 벡터
	vector<DWORD>                   m_vecVertexIndex;                               // Height맵 좌표 인덱스 벡터

	vector<ST_TERRAIN_FACE_INFO>    m_vecFaceInfo;                                  // 면정보 (순차적)

	ST_WATER_INFO			        m_stWaterInfo;									// 물정보

	E_TERRAIN_EDIT_TYPE&			m_eTerraingEditType;							// 지형맵 편집 타입

	ST_TER_BRUSH_INFO				m_stTerrainBrushInfo;								// 지형 브러쉬 정보
    ST_TEX_BRUSH_INFO				m_stTextureBrushInfo;								// 텍스쳐 브러쉬 정보

    vector<string>                  m_vecTextureKey;                                // 텍스쳐 키값 벡터

	string                          m_sFileName;                                    // 파일 이름

	LPD3DXMESH						m_pMesh;										// 매쉬

private:
	HRESULT SetBrushSize(IN float fSize);													// 브러쉬 사이즈 설정
	HRESULT SetBrushDensity(IN float fSize);												// 브러쉬 농도 사이즈 설정
	HRESULT SetHeight(IN Vector2 vPosition, IN float fHeight);								// 지형 높이 설정
	HRESULT SetTextureDensity(IN float& fDensity);											// 텍스쳐의 밀도 설정 (이는 브러쉬의 속성을 설정해줌)
	HRESULT SetTextureType(IN E_GROUND_TYPE eGroundType);									// 텍스쳐 타입 설정
	HRESULT SetWaterBrushSize(IN float fSize);												// 물 브러쉬 사이즈 설정
	HRESULT SetWaterSpeed(IN float fSpeed);													// 물의 유속 설정 (물의 밀도와 움직임 값을 계산 및 설정)
	HRESULT SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType);				// 지형에 텍스쳐 입히기
	HRESULT SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo);	// 지형 높이 복제
	// 브러쉬가 지정한 지형 겟터 -> vector<ST_PT_VERTEX> Get~~~~();

	HRESULT SaveFile(IN string sFolderName, IN string sFileName);							// 지형맵 파일 저장하기
	HRESULT LoadFile(IN string sFolderName, IN string sFileName);							// 지형맵 파일 로드하기

public:

    cMapTerrainTool();
    ~cMapTerrainTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

    HRESULT CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType, IN float fHeight, IN float isWalkable);		// 크기 설정한 맵 생성
};

