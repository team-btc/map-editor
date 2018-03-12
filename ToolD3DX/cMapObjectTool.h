#pragma once
#include "cObject.h"

#define INVALIDE_VALUE (-1)
#define DEBUG_RENDER (true)
#define BLOCK_RADIUS  (2.0f)
#define NO_NAME ("None")

class cMapObject;
class cRay;

class cMapObjectTool : public cObject
{
private:
    struct ST_BLOCK_GROUP
    {
        vector<ST_PC_VERTEX>    vecPoints;
        string                  GroupName;
        Color                   GroupColor;
    };

private:
	// 오브젝트 관련
	vector<cMapObject*>          m_vecObjects;          // Object Storage Vector
	string                       m_strCurrentMeshName;  // Current Selected MeshName
	LPMESH                       m_SphereMesh;					
	bool&                        m_isObjCollison;
	bool&                        m_isObjDestruction;
	float&                       m_fObjPosX;
	float&                       m_fObjPosY;
	float&                       m_fObjPosZ;
	float&                       m_fObjSize;
	float&                       m_fObjRotX;
	float&                       m_fObjRotY;
	float&                       m_fObjRotZ;

    // 이름 바꾸기 
    int                          m_nObjectMakeTotalNum; // 지금까지 오브젝트를 만든 총 갯수(지우고 다시 만들어도 얘는 변함이 없음, 누적값이고 얘를 각 오브젝트들의 아이디로 쓸꺼임)
    int                          m_nSelectedIndex;      // 재배치, 삭제 할때 쓸 용도
    Matrix4                      m_matScale;    
    Matrix4                      m_matRotation;
    Matrix4                      m_matTrans;
	Vector3*				     m_pPickPos;            // MainTool 피킹 포지션과 연결된 포인터 
	cMapObject*			         m_pFollowObject;       // 따라 다니는 녀석의 주소 
  
    // 블록 관련
    vector<ST_BLOCK_GROUP*>      m_vecBlockGroups;
    E_BLOCK_BUTTON_STATE&        m_eBlockButtonState;
	string&					     m_SelectedBlockGroupName;
    int                          m_nCurWorkingBlockGroupIndex;
   
public:
    cMapObjectTool();
    ~cMapObjectTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	// 배치 할 때랑 재배치 할때 따라다니는 녀석 설정 
	void SetFollowObject();
	void UpdateFollowObject();
	void RenderFollowObject();
	void DeleteFollowObject();

    void UpdateMatrix();        // Tool의 매트릭스 갱신 

	void SetPickPos(Vector3* pos) { m_pPickPos = pos; } // MapTool에서 픽킹된 위치의 벡터를 연결 시킴
    void AddObject(Vector3 vPickPos);
 
	void OnceLButtonDown();     // 마우스 왼쪽 버튼을 클릭 했을 때 발동
    void StayLButtonDown();     // 마우스 왼쪽 버튼을 계속 누르고 있을 때 발동

    int PickObject();           // 오브젝트 피킹
    int FindObject(int nId);    // 아이디 값으로 오브젝트 찾기 

    bool CollideRayNCircle(cRay ray, Vector3 vTargetPos, float fTargetRadius);

    bool CollideRound(Vector3 vMyPos, float fMyRadius, Vector3 vTargetPos, float fTargetRadius);
    void DebugTestRender();

    int GetBlockGroupByName(string BlockName);
};

