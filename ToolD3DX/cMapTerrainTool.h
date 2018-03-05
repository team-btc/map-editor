#pragma once

#include "cObject.h"

#define GT_MAX_NUM			5														// 지형 타입 개수
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
//

// ÁöÇü ¸é(»ï°¢Çü)Á¤º¸
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

// 브러쉬 정보
struct ST_BRUSH_INFO {
	float							fBrushSize;										// 브러쉬 사이즈
	float							fBrushDensitySize;								// 브러쉬 농도 사이즈
	float							fBrushDensity;									// 브러쉬 농도 값
	float							fTextureDensity;								// 텍스쳐 농도 값
	float							fWaterSpeed;									// 물의 유속
};

// 물 지형 정보
struct ST_WATER_INFO {
	Vector2							vPosition;										// 물의 중앙 위치
	float							fHeight;										// 물의 높이
	float							fSpeed;											// 물의 유속
	float							fDensity;										// 물의 농도
};

class cMapTerrainTool : public cObject
{
private:
    POINT                           m_ptSize;                                       // 맵 크기

	vector<ST_PT_VERTEX>            m_vecPTVertex;                                  // 맵에 사용할 점 벡터
	vector<DWORD>                   m_vecVertexIndex;                               // Height맵 좌표 인덱스 벡터

	vector<ST_WATER_INFO>			m_vecWaterInfo;									// 물정보(기본 8*8사이즈로 나눔)

	E_GROUND_TYPE                   m_eCurrTextureType;								// 현재 텍스쳐 인덱스
	vector<string>                  m_vecTextureKey;                                // 텍스쳐 키값 벡터

	vector<ST_TERRAIN_FACE_INFO>    m_vecFaceInfo;                                  // 면정보 (순차적)

	string                          m_sFileName;                                    // 파일 이름

	ST_BRUSH_INFO					m_BrushInfo;									// 브러쉬 정보

	LPD3DXMESH						m_pMesh;										// 매쉬

private:
    HRESULT CreateNewMap(IN int nSizeX, IN int nSizeZ, IN E_GROUND_TYPE eGroundType);		// 크기 설정한 맵 생성
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

	HRESULT Setup(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType);
	HRESULT Update();
	HRESULT Render();
};

