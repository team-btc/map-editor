#pragma once
#include "cObject.h"

#define INVALIDE_VALUE (-1)
#define DEBUG_RENDER (true)

class cMapObject;
class cRay;

class cMapObjectTool : public cObject
{
private:
	vector<cMapObject*>          m_vecObjects;                // Object Storage Vector
	string                       m_strCurrentMeshName;        // Current Selected MeshName
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

    // �̸� �ٲٱ� 
    int                          m_nObjectMakeTotalNum; // ���ݱ��� ������Ʈ�� ���� �� ����(����� �ٽ� ���� ��� ������ ����, �������̰� �긦 �� ������Ʈ���� ���̵�� ������)
    int                          m_nSelectedIndex;     // ���ġ, ���� �Ҷ� �� �뵵
    Matrix4                      m_matScale;    
    Matrix4                      m_matRotation;
    Matrix4                      m_matTrans;
	Vector3*				     m_pPickPos;            // MainTool ��ŷ �����ǰ� ����� ������ 
	cMapObject*			         m_pFollowObject;       // ���� �ٴϴ� �༮�� �ּ� 
  
    float                        m_fRadius;
public:
    cMapObjectTool();
    ~cMapObjectTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	// ��ġ �� ���� ���ġ �Ҷ� ����ٴϴ� �༮ ���� 
	void SetFollowObject();
	void UpdateFollowObject();
	void RenderFollowObject();
	void DeleteFollowObject();

    void UpdateMatrix();        // Tool�� ��Ʈ���� ���� 

	void SetPickPos(Vector3* pos) { m_pPickPos = pos; } // MapTool���� ��ŷ�� ��ġ�� ���͸� ���� ��Ŵ
    void AddObject(Vector3 vPickPos);
 
	void OnceLButtonDown();     // ���콺 ���� ��ư�� Ŭ�� ���� �� �ߵ�
    void StayLButtonDown();     // ���콺 ���� ��ư�� ��� ������ ���� �� �ߵ�

    int PickObject();           // ������Ʈ ��ŷ
    int FindObject(int nId);    // ���̵� ������ ������Ʈ ã�� 

    bool CollideRound(Vector3 vMyPos, float fMyRadius, Vector3 vTargetPos, float fTargetRadius);
    void DebugTestRender();
};

