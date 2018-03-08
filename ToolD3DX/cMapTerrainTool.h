#pragma once
#include "cTextureShader.h"
//#include "cWaveShader.h"
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
#define EDIT_DURATION_TIME  0.1f                                                    // 편집 지속 기준 시간

// 면 정보
struct ST_TERRAIN_FACE_INFO {
	DWORD							dVertexIndedArr[3];								// 면이 가지고 있는 삼각형 버텍스 인덱스
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

    ST_TER_BRUSH_INFO(float& _fBS, float& _fFS, float& _fI)
        : fTerrainBrushSize(_fBS), fTerrainFlatSize(_fFS), fIncrementHeight(_fI) {}
};

// 텍스쳐 브러쉬 정보
struct ST_TEX_BRUSH_INFO {
    E_GROUND_TYPE&                  m_eCurrTextureType;								// 현재 선택된 텍스쳐
    bool&                           m_isWalkable;                                   // 걸을 수 있는지 여부
    float&							fTextureDensity;								// 텍스쳐 농도 값
    float&							fTextureBrushSize;								// 텍스쳐 안쪽 브러쉬 사이즈
    float&							fTextureBrushSpraySize;							// 텍스쳐 바깥쪽 브러쉬 사이즈
    //float&							fTexturBrushDensity;							// 텍스쳐 브러쉬 농도 값
    
    ST_TEX_BRUSH_INFO(E_GROUND_TYPE& _eCTT, bool& _isW, float& _fTD, float& _fBS, float& _fBDS, float& _fBD)
        : m_eCurrTextureType(_eCTT), m_isWalkable(_isW), fTextureDensity(_fTD)
        , fTextureBrushSize(_fBS), fTextureBrushSpraySize(_fBDS) {}

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
    POINT                           m_ptMapSize;                                    // 맵 크기

	vector<ST_PNT_VERTEX>           m_vecPNTVertex;                                 // 맵에 사용할 점 벡터
	vector<DWORD>                   m_vecVertexIndex;                               // Height맵 좌표 인덱스 벡터

	vector<ST_TERRAIN_FACE_INFO>    m_vecFaceInfo;                                  // 면정보 (순차적)

	ST_WATER_INFO			        m_stWaterInfo;									// 물정보

	E_TERRAIN_EDIT_TYPE&			m_eTerrainEditType;							    // 지형맵 편집 타입

	ST_TER_BRUSH_INFO				m_stTerrainBrushInfo;							// 지형 브러쉬 정보
    ST_TEX_BRUSH_INFO				m_stTextureBrushInfo;							// 텍스쳐 브러쉬 정보

    vector<string>                  m_vecTextureKey;                                // 텍스쳐 키값 벡터

	string                          m_sFileName;                                    // 파일 이름

	LPD3DXMESH						m_pMesh;										// 매쉬

    
    Vector3*                        m_vPickPos;                                     // 픽킹 위치

    vector<int>                     m_vecSelVertex;                                 // 브러쉬 안에 있는 버텍스 인덱스
    cTextureShader*                 m_pTextureShader;
    //cWaveShader*                  m_pWaveShader;
    float                           m_fPassedEditTime;                              // 편집 경과 시간

private:
	HRESULT SaveFile(IN string sFolderName, IN string sFileName);							 // 지형맵 파일 저장하기
	HRESULT LoadFile(IN string sFolderName, IN string sFileName);							 // 지형맵 파일 로드하기

    void EditTerrain();                                                                      // 지형 편집 함수
    void IncrementHeight();                                                                  // 지형 높이 높이기
    void DecreaseHeight();                                                                   // 지형 높이 낮추기
    void ResetHeight();                                                                      // 지형 높이 리셋
    void ChangeNormalValue(int nIndex, ST_PNT_VERTEX** vEditV);                              // 변경된 버텍스와 주변 버텍스 노말값 변경
    void SetNormal(int nIndex, ST_PNT_VERTEX** vEditV);                                      // 버텍스 노말 계산, 셋팅
    int GetNearVertexIndex(Vector3 vPickPos, vector<int> vecSelVertex);                      // 픽킹 지점에서 가장 가까운 버텍스 인덱스 가져오기
    vector<int> GetVertexInBrush(Vector3 vPickPos, float fRadius);                           // 브러쉬 안에 있는 버텍스 인덱스 벡터 가져오기

public:
    cMapTerrainTool();
    ~cMapTerrainTool();

	HRESULT Setup();
    HRESULT Update();
	HRESULT Render();

    void DrawAlphaMap();
	void RendBrush();                                                            										// 픽킹 위치 세팅

    void OnceLButtonDown(E_TAB_TYPE eTabType);                                                                          // 마우스 왼쪽 버튼 클릭 했을 때 발동
    void StayLButtonDown(E_TAB_TYPE eTabType);                                                                          // 마우스 왼쪽 버튼 계속 누를 때 발동

    HRESULT CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType, IN float fHeight, IN float isWalkable);		// 크기 설정한 맵 생성

    // == 겟터 ==
    LPD3DXMESH GetMesh() { return m_pMesh; }
    // == 셋터 ==
    void SetPickPos(Vector3* vPos) { m_vPickPos = vPos; }   
    
};

