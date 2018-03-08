#pragma once

#include "cObject.h"
namespace objectTool
{
	struct ST_OBJECT_MESH
	{
		LPD3DXMESH					Mesh;		  // �Ž�
		D3DMATERIAL9*				Materials;    // �Ž��� ���� ����
		LPDIRECT3DTEXTURE9*			Textures;	  // �Ž��� ���� �ؽ���
		DWORD						NumMaterials; // ������ ��
		
        ST_OBJECT_MESH()
		{
			Mesh = NULL;
			Materials = NULL;
			Textures = NULL;
			NumMaterials = NULL;
		}
	};

	struct ST_MAP_OBJECT
	{
		int                 Id;
		string              MeshName;
		float               Size;
		float               PosX;
		float               PosY;
		float               PosZ;
		float               RotX;
		float               RotY;
		float               RotZ;
		bool                Collision;
		bool                Destruction;
		D3DXMATRIXA16       World;
		ST_OBJECT_MESH*		Mesh;

		// ST_MAP_OBJECT Default Constructor!!
		ST_MAP_OBJECT()
		{
			Id = -1;
			Size = 0.0f;
			PosX = 0.0f;
			PosY = 0.0f;
			PosZ = 0.0f;
			RotX = 0.0f;
			RotY = 0.0f;
			RotZ = 0.0f;
			Collision = false;
			Destruction = false;
			D3DXMatrixIdentity(&World);
			Mesh = NULL;
		}
	};
}

using namespace objectTool;
class cMapObjectTool : public cObject
{
private:
	map<string, ST_OBJECT_MESH*> m_mapMesh;
	vector<ST_MAP_OBJECT*>       m_vecObjects;                // Object Storage Vector
	string                       m_strCurrentMeshName;        // Current Selected MeshName
	// �̸� �ٲٱ� 
	int                          m_nObjId;
	LPMESH                       m_pTestBox;					// Test mesh!!
	bool&                        m_isObjCollison;
	bool&                        m_isObjDestruction;
	float&                       m_fObjPosX;
	float&                       m_fObjPosY;
	float&                       m_fObjPosZ;
	float&                       m_fObjSize;
	float&                       m_fObjRotX;
	float&                       m_fObjRotY;
	float&                       m_fObjRotZ;

	Vector3*				     m_pPickPos;
	ST_MAP_OBJECT*			     m_pFollowObject;
public:
    cMapObjectTool();
    ~cMapObjectTool();

	HRESULT Setup();
	HRESULT Update();
	HRESULT Render();

	// ���Ϳ� �� ������Ʈ �߰� 
	void SetupFollowObject();
	void UpdateFollowObject();
	void RenderFollowObject();
	void InitDefaultFollowObject();

    // �ʿ��� �޽� ��������
	ST_OBJECT_MESH* GetMesh(string key);
	ST_OBJECT_MESH* GetMesh(string key, string filePath, string fileName);

    // MapTool���� ��ŷ�� ��ġ�� ���͸� ���� ��Ŵ
	void SetPickPos(Vector3* pos) { m_pPickPos = pos; }
	
    void AddObject(Vector3 vCollisonPos);
 
	void OnceLButtonDown();                    // ���콺 ���� ��ư�� Ŭ�� ���� �� �ߵ�
    void StayLButtonDown();                    // ���콺 ���� ��ư�� ��� ������ ���� �� �ߵ�
};

