#pragma once

#include "cObject.h"

class cRay;


class cMapTerrainTool;
class cMapObjectTool;

#define DEFAULT_MAP_SIZE		E_SIZE_256											// 기본 맵 크기
#define DEFAULT_G_TYPE			E_SOIL_GROUND										// 기본 지형 타입
#define DEFAULT_HEIGHT          128.0f                                              // 기본 맵 높이

class cMapTool : public cObject
{
private:
    E_TAB_TYPE & m_eCurrTabType;                                     // 탭 상태                

    cRay*                       m_pRay;
    Vector3                     m_vPickPos;                                                  // 마우스 픽킹 좌표

    cMapTerrainTool*			m_pTerrainTool;
    cMapObjectTool*				m_pObjectTool;

    E_MAP_SIZE&					m_eMapSize;											// 맵 사이즈
    float&						m_fDefaultHeight;									// 맵 기본 높이 값
    bool&                       m_isTex1Load;                                       // 기본 텍스쳐1 로드 여부
    bool&                       m_isTex2Load;                                       // 기본 텍스쳐2 로드 여부
    bool&                       m_isTex3Load;                                       // 기본 텍스쳐3 로드 여부

    string&                     m_strTex1FilePath;                                  // 기본 텍스쳐1 경로
    string&                     m_strTex1FileName;                                  // 기본 텍스쳐1 이름
    string&                     m_strTex2FilePath;                                  // 기본 텍스쳐2 경로
    string&                     m_strTex2FileName;                                  // 기본 텍스쳐2 이름
    string&                     m_strTex3FilePath;                                  // 기본 텍스쳐3 경로
    string&                     m_strTex3FileName;                                  // 기본 텍스쳐3 이름
    bool&                       m_isCreateMap;                                      // 맵을 새로 생성

private:

public:
    cMapTool();
    ~cMapTool();

    HRESULT Setup();
    HRESULT Update();
    HRESULT Render();

    HRESULT CreateMap();						                                    // Create버튼을 눌렀을 때 발동
    json SaveByJson(string strFilePath, string strFileTitle);
    void LoadByJson(string sFilePath, string sFileTitle);
    HRESULT GetPtMouse();                                                           // 마우스 위치 가져오기
    void RendPtMouse();                                                             // 마우스 위치 출력
    bool IsPickMap();                                                               // 마우스가 클라이언트 영역 안에서 맵을 클릭 했는지 체크
};

