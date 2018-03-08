#pragma once

#include "cObject.h"
namespace objectTool
{
	struct ST_OBJECT_MESH
	{
		LPD3DXMESH					Mesh;		  // 매쉬
		D3DMATERIAL9*				Materials;    // 매쉬에 대한 재질
		LPDIRECT3DTEXTURE9*			Textures;	  // 매쉬에 대한 텍스쳐
		DWORD						NumMaterials; // 재질의 수
		
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
	// 이름 바꾸기 
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

	// 벡터에 맵 오브젝트 추가 
	void SetupFollowObject();
	void UpdateFollowObject();
	void RenderFollowObject();
	void InitDefaultFollowObject();

    // 맵에서 메쉬 가져오기
	ST_OBJECT_MESH* GetMesh(string key);
	ST_OBJECT_MESH* GetMesh(string key, string filePath, string fileName);

    // MapTool에서 픽킹된 위치의 벡터를 연결 시킴
	void SetPickPos(Vector3* pos) { m_pPickPos = pos; }
	
    void AddObject(Vector3 vCollisonPos);
 
	void OnceLButtonDown();                    // 마우스 왼쪽 버튼을 클릭 했을 때 발동
    void StayLButtonDown();                    // 마우스 왼쪽 버튼을 계속 누르고 있을 때 발동
};

