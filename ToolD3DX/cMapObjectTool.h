#pragma once
#include "cObject.h"

#define INVALIDE_VALUE (-1)
#define DEBUG_RENDER (true)
#define BLOCK_RADIUS  (2.0f)
#define NO_NAME ("None")
#define SCALE_FIX	 (20.0f)
#define EVENT_RADIUS  (10.0f)

// OBJECT_TAB ����
#define OBJ_SET       ("object-tab-setting")
#define OBJ_OBJ_NUM   ("object-tab-object-make-num")
#define OBJ_BLOCK_NUM ("object-tab-block-make-num")

// OBJECT ����
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

// BLOCK ����
#define BG          ("block-group")         // array
#define BG_NAME     ("block-group-name")    // string
#define BG_COLOR    ("block-group-color")   // DWORD
#define BG_POINT    ("block-group-point")   // array
#define BG_PO_X     ("block-point-x")       // float
#define BG_PO_Y     ("block-point-y")       // float 
#define BG_PO_Z     ("block-point-z")       // float

// EVENT ����
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
    // ������Ʈ ����
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

    // �̸� �ٲٱ� 
    int                          m_nObjectMakeTotalNum;     // ���ݱ��� ������Ʈ�� ���� �� ����(����� �ٽ� ���� ��� ������ ����, �������̰� �긦 �� ������Ʈ���� ���̵�� ������)
    int                          m_nSelectedIndex;          // ���ġ, ���� �Ҷ� �� �뵵
    Matrix4                      m_matScale;
    Matrix4                      m_matRotation;
    Matrix4                      m_matTrans;
    Vector3*				     m_pPickPos;                // MainTool ��ŷ �����ǰ� ����� ������ 
    cMapObject*			         m_pFollowObject;           // ���� �ٴϴ� �༮�� �ּ� 

                                                            // ��� ����
    vector<ST_BLOCK_GROUP*>      m_vecBlockGroups;
    E_OBJECT_BUTTON_STATE&       m_eObjectButtonState;
    E_BLOCK_BUTTON_STATE&        m_eBlockButtonState;
    string&					     m_SelectedBlockGroupName;
    int                          m_nCurWorkingBlockGroupIndex;
    // ������ 
    cMapTerrainTool*             m_pTerrainTool;

    // �̺�Ʈ 
    vector<ST_EVENT_TRIGGER*>    m_vecEventTrrigers;        // �̺�Ʈ Ʈ���� 
    E_EVENT_BUTTON_STATE&        m_eEventButtonState;       // �̺�Ʈ ��ư ���� 
public:
    cMapObjectTool();
    ~cMapObjectTool();

    HRESULT Setup();
    HRESULT Update();
    HRESULT Render();

    void SetTerrainTool(cMapTerrainTool* terrain) { m_pTerrainTool = terrain; } // object�� ���� üũ�� ���� �༮ 

                                                                                // ��ġ �� ���� ���ġ �Ҷ� ����ٴϴ� �༮ ���� 
    void SetFollowObject();
    void UpdateFollowObject();
    void RenderFollowObject();
    void DeleteFollowObject();

    void UpdateMatrix();        // Tool�� ��Ʈ���� ���� 

    void SetPickPos(Vector3* pos) { m_pPickPos = pos; } // MapTool���� ��ŷ�� ��ġ�� ���͸� ���� ��Ŵ
    void AddObject(Vector3 vPickPos);

    void OnceLButtonDown(E_TAB_TYPE eTabType);     // ���콺 ���� ��ư�� Ŭ�� ���� �� �ߵ�
    void StayLButtonDown();     // ���콺 ���� ��ư�� ��� ������ ���� �� �ߵ�

    int  PickObject();           // ������Ʈ ��ŷ
    int  FindObject(int nId);    // ���̵� ������ ������Ʈ ã�� 

    bool CollideRayNCircle(cRay ray, Vector3 vTargetPos, float fTargetRadius);
    bool CollideRound(Vector3 vMyPos, float fMyRadius, Vector3 vTargetPos, float fTargetRadius);
    void DebugTestRender();

    int  GetBlockGroupByName(string BlockName);
    void RenderSignPost(Vector3 pos, int size, Color color, string text);


    void ClearObjectNBlock();			    // object, block_group �ΰ��� ���� ���� 
    void SaveByJson(json& jSave);           // Json ���� ����
    void LoadByJson(string sFilePath, string sFileTitle);  // Json ���� �ε� 

    //  �̺�Ʈ ����
    int  GetEventByName(string sName);
};

