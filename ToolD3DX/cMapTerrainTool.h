#pragma once
#include "cTextureShader.h"
#include "cBrush.h"
#include "cWaveShader.h"
#include "cTotalShader.h"
#include "cSkyBoxShader.h"
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
#define EDIT_DURATION_TIME  0.0f                                                    // 편집 지속 기준 시간

// 지형 브러쉬 정보
struct ST_TER_BRUSH_INFO {
    E_UP_DOWN&                      eUpDown;                                        // 편집 업다운
    E_TERRAIN_EDIT_TYPE&	        eEditType;                                      // 편집 타입
    E_TER_BRUSH_TYPE&               eBrushType;                                     // 브러쉬 타입
    float&                          fPower;                                         // 편집 파워
    float&                          fEditHeight;                                    // 편집 높이
    float&							fBrushSize;								        // 지형 브러쉬 사이즈

    ST_TER_BRUSH_INFO(E_UP_DOWN& _eUD, E_TERRAIN_EDIT_TYPE& _eET,
        E_TER_BRUSH_TYPE& _eBT, float& _fP, float& _fEH, float& _fBS)
        : eUpDown(_eUD), eEditType(_eET), eBrushType(_eBT), fPower(_fP), fEditHeight(_fEH), fBrushSize(_fBS) {}
};

// 텍스쳐 브러쉬 정보
struct ST_TEX_BRUSH_INFO {
    int&                            m_nCurrTextureIndex;							// 현재 선택된 텍스쳐
    float&							fDrawDensity;								    // 텍스쳐 농도 값
    float&							fTextureBrushSize;								// 텍스쳐 안쪽 브러쉬 사이즈
    float&							fTextureBrushSpraySize;							// 텍스쳐 바깥쪽 브러쉬 사이즈
    E_DRAW_TYPE&                    m_eDrawType;                                    // 그리기 타입
    float&                          m_fTex1Density;                                 // 텍스쳐1 밀도
    float&                          m_fTex2Density;                                 // 텍스쳐2 밀도
    float&                          m_fTex3Density;                                 // 텍스쳐3 밀도
    ST_TEX_BRUSH_INFO(int& _iCTI, float& _fDD, float& _fBS, float& _fBDS, E_DRAW_TYPE& _eDT, float& _fTD1, float& _fTD2, float& _fTD3)
        : m_nCurrTextureIndex(_iCTI), fDrawDensity(_fDD)
        , fTextureBrushSize(_fBS), fTextureBrushSpraySize(_fBDS), m_eDrawType(_eDT), m_fTex1Density(_fTD1), m_fTex2Density(_fTD2), m_fTex3Density(_fTD3) {}

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
    float&                          fDensity;                                       // 물의 밀도
    ST_WATER_INFO(float& _fH, float& _fUVS, float& _fWH, float& _fHS, float& _fF, float& _fT, float& _fD)
        : fHeight(_fH), fUVSpeed(_fUVS), fWaveHeight(_fWH)
        , fHeightSpeed(_fHS), fFrequency(_fF), fTransparent(_fT), fDensity(_fD) {}
};

class cMapTerrainTool : public cObject
{
private:
    POINT                           m_ptMapSize;                                    // 맵 크기

    vector<ST_PNT_VERTEX>           m_vecPNTVertex;                                 // 맵에 사용할 점 벡터
    vector<DWORD>                   m_vecVertexIndex;                               // Height맵 좌표 인덱스 벡터

    vector<ST_PNT_VERTEX>           m_vecWPNTVertex;                                 // 물 맵에 사용할 점 벡터
    vector<DWORD>                   m_vecWVertexIndex;                               // 물 Height맵 좌표 인덱스 벡터

    ST_WATER_INFO			        m_stWaterInfo;									// 물정보

    ST_TER_BRUSH_INFO				m_stTerrainBrushInfo;							// 지형 브러쉬 정보
    ST_TEX_BRUSH_INFO				m_stTextureBrushInfo;							// 텍스쳐 브러쉬 정보

    vector<string>                  m_vecTextureKey;                                // 텍스쳐 키값 벡터

    string                          m_sFileName;                                    // 파일 이름

    LPD3DXMESH						m_pMesh;										// 매쉬
    LPD3DXMESH						m_pWMesh;										// 물 매쉬

    Vector3*                        m_vPickPos;                                     // 픽킹 위치

    vector<int>                     m_vecSelVertex;                                 // 브러쉬 안에 있는 버텍스 인덱스
    cTextureShader*                 m_pTextureShader;

    D3DFILLMODE                     m_fillMode;

    bool&                           m_isTex1Load;                                   // 기본 텍스쳐1 로드 여부
    bool&                           m_isTex2Load;                                   // 기본 텍스쳐2 로드 여부
    bool&                           m_isTex3Load;                                   // 기본 텍스쳐3 로드 여부

    bool&                           m_isWaterEnable;                                // 물 보여주기 여부
    bool&                           m_isSetWaterFile;                               // 물 파일 셋팅 여부
    string&                         m_strWaterFileName;                             // 물 파일 이름


    bool&                           m_isSetSkyFile;                                 // 하늘 파일 셋팅 여부
    string&                         m_strSkyFileName;                               // 하늘 파일 이름

    cBrush*                         m_pBrush;                                       // 브러쉬 클래스
    cWaveShader*                    m_pWaveShader;
    cSkyBoxShader*                  m_pSkyBoxShader;
    float                           m_fPassedEditTime;                              // 편집 경과 시간

private:
    HRESULT SaveFile(IN string sFolderName, IN string sFileName);							 // 지형맵 파일 저장하기
    HRESULT LoadFile(IN string sFolderName, IN string sFileName);							 // 지형맵 파일 로드하기

    void EditTerrain();                                                                      // 지형 편집 메인 함수
    void EditHeight();                                                                       // 지형 높이 편집
    void ReturnHeight();                                                                     // 지형 높이 되돌리기
    void FixedHeight();                                                                      // 고정 지형 만들기
    void SetFlat();                                                                          // 평지 셋팅하기
    void TrimHeight();                                                                       // 지형 다듬기
    void ResetHeight();                                                                      // 리셋
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
    HRESULT RenderSkyBox();
    HRESULT RenderTextureShader();

    void OnceLButtonDown(E_TAB_TYPE eTabType);                                                                          // 마우스 왼쪽 버튼 클릭 했을 때 발동
    void StayLButtonDown(E_TAB_TYPE eTabType);                                                                          // 마우스 왼쪽 버튼 계속 누를 때 발동

    HRESULT CreateMap(IN E_MAP_SIZE eMapSize, IN float fHeight);		                                                // 크기 설정한 맵 생성

    void SaveMapData(string strFilePath, string strFileTitle);                                                                              // 맵데이터 저장
    void LoadMapData(string sFilePath, string sFileTitle);                                                                              // 맵데이터 로드

                                                                                                                                        // == 겟터 ==
    LPD3DXMESH GetMesh() { return m_pMesh; }
    // == 셋터 ==
    void SetPickPos(Vector3* vPos) { m_vPickPos = vPos; }

    void SetWave(string fileName, string filePath)
    {
        if (m_pWaveShader)
        {
            m_pWaveShader->SetWaveTexture(filePath, fileName);
        }
    }

    void SetTerrainTexture()
    {
        m_pTextureShader->SetTexture();
    }
    void SetSkyBoxTexture()
    {
        m_pSkyBoxShader->SetSkyBoxTexture();
    }
};

