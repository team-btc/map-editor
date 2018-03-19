#pragma once
#include "cObject.h"

#define INVALIDE_VALUE (-1)
#define DEBUG_RENDER (true)
#define BLOCK_RADIUS  (2.0f)
#define NO_NAME ("None")
#define SCALE_FIX	 (20.0f)
#define EVENT_RADIUS  (10.0f)

// OBJECT_TAB 관련
#define OBJ_SET       ("object-tab-setting")
#define OBJ_OBJ_NUM   ("object-tab-object-make-num")
#define OBJ_BLOCK_NUM ("object-tab-block-make-num")

// OBJECT 관련
#define OBJ         ("object")
#define OBJ_KEY     ("object-file-key")
#define OBJ_PATH    ("object-filepath")
#define OBJ_NAME    ("object-filename")
#define OBJ_COL     ("object-collision")
#define OBJ_DES     ("object-destruction")
#define OBJ_ENE     ("object-enemy")
#define OBJ_SCALE   ("object-scale")
#define OBJ_ROTX    ("object-rotation-x")
#define OBJ_ROTY    ("object-rotation-y")
#define OBJ_ROTZ    ("object-rotation-z")
#define OBJ_POSX    ("object-position-x")
#define OBJ_POSY    ("object-position-y")
#define OBJ_POSZ    ("object-position-z")

// BLOCK 관련
#define BG          ("block-group")         // array
#define BG_NAME     ("block-group-name")    // string
#define BG_COLOR    ("block-group-color")   // DWORD
#define BG_POINT    ("block-group-point")   // array
#define BG_PO_X     ("block-point-x")       // float
#define BG_PO_Y     ("block-point-y")       // float 
#define BG_PO_Z     ("block-point-z")       // float

// EVENT 관련
#define EVE         ("event")
#define EVE_NAME    ("event-name")  
#define EVE_POSX    ("event-position-x")
#define EVE_POSY    ("event-position-y")
#define EVE_POSZ    ("event-position-z")

class cRay;
class cMapObject;
class cMapTerrainTool;
class cMapObjectTool : public cObject
{
private:
    struct ST_BLOCK_GROUP
    {
        vector<ST_PC_VERTEX>    vecPoints;
        string                  GroupName;
        Color                   GroupColor;
    };

    struct ST_EVENT_TRIGGER
    {
        string                  EventName;
        Vector3                 EventPosition;
        Color                   EventColor;
    };
private:
    // 오브젝트 관련
    vector<cMapObject*>          m_vecObjects;          // Object Storage Vector
    string                       m_strCurrentMeshName;  // Current Selected MeshName
    LPMESH                       m_SphereMesh;
    bool&                        m_isObjCollison;
    bool&                        m_isObjDestruction;
    bool&                        m_isObjEnemy;
    float&                       m_fObjPosX;
    float&                       m_fObjPosY;
    float&                       m_fObjPosZ;
    float&                       m_fObjSize;
    float&                       m_fObjRotX;
    float&                       m_fObjRotY;
    float&                       m_fObjRotZ;

    // 이름 바꾸기 
    int                          m_nObjectMakeTotalNum;     // 지금까지 오브젝트를 만든 총 갯수(지우고 다시 만들어도 얘는 변함이 없음, 누적값이고 얘를 각 오브젝트들의 아이디로 쓸꺼임)
    int                          m_nSelectedIndex;          // 재배치, 삭제 할때 쓸 용도
    Matrix4                      m_matScale;
    Matrix4                      m_matRotation;
    Matrix4                      m_matTrans;
    Vector3*				     m_pPickPos;                // MainTool 피킹 포지션과 연결된 포인터 
    cMapObject*			         m_pFollowObject;           // 따라 다니는 녀석의 주소 

                                                            // 블록 관련
    vector<ST_BLOCK_GROUP*>      m_vecBlockGroups;
    E_OBJECT_BUTTON_STATE&       m_eObjectButtonState;
    E_BLOCK_BUTTON_STATE&        m_eBlockButtonState;
    string&					     m_SelectedBlockGroupName;
    int                          m_nCurWorkingBlockGroupIndex;
    // 참조용 
    cMapTerrainTool*             m_pTerrainTool;

    // 이벤트 
    vector<ST_EVENT_TRIGGER*>    m_vecEventTrrigers;        // 이벤트 트리거 
    E_EVENT_BUTTON_STATE&        m_eEventButtonState;       // 이벤트 버튼 상태 
public:
    cMapObjectTool();
    ~cMapObjectTool();

    HRESULT Setup();
    HRESULT Update();
    HRESULT Render();

    void SetTerrainTool(cMapTerrainTool* terrain) { m_pTerrainTool = terrain; } // object의 높이 체크를 위한 녀석 

                                                                                // 배치 할 때랑 재배치 할때 따라다니는 녀석 설정 
    void SetFollowObject();
    void UpdateFollowObject();
    void RenderFollowObject();
    void DeleteFollowObject();

    void UpdateMatrix();        // Tool의 매트릭스 갱신 

    void SetPickPos(Vector3* pos) { m_pPickPos = pos; } // MapTool에서 픽킹된 위치의 벡터를 연결 시킴
    void AddObject(Vector3 vPickPos);

    void OnceLButtonDown(E_TAB_TYPE eTabType);     // 마우스 왼쪽 버튼을 클릭 했을 때 발동
    void StayLButtonDown();     // 마우스 왼쪽 버튼을 계속 누르고 있을 때 발동

    int  PickObject();           // 오브젝트 피킹
    int  FindObject(int nId);    // 아이디 값으로 오브젝트 찾기 

    bool CollideRayNCircle(cRay ray, Vector3 vTargetPos, float fTargetRadius);
    bool CollideRound(Vector3 vMyPos, float fMyRadius, Vector3 vTargetPos, float fTargetRadius);
    void DebugTestRender();

    int  GetBlockGroupByName(string BlockName);
    void RenderSignPost(Vector3 pos, int size, Color color, string text);


    void ClearObjectNBlock();			    // object, block_group 두개의 백터 비우기 
    void SaveByJson(json& jSave);           // Json 으로 저장
    void LoadByJson(string sFilePath, string sFileTitle);  // Json 으로 로드 

    //  이벤트 관련
    int  GetEventByName(string sName);
};

