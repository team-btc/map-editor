#include "stdafx.h"
#include "cMapObjectTool.h"
#include "cSkinnedMesh.h"

cMapObjectTool::cMapObjectTool()
	: m_pTestBox(NULL)
	, m_nObjId(0)
	, m_isObjCollison(g_pMapDataManager->GetObjCollision())
	, m_isObjDestruction(g_pMapDataManager->GetObjDestruction())
	, m_fObjPosX(g_pMapDataManager->GetObjPosX())
	, m_fObjPosY(g_pMapDataManager->GetObjPosY())
	, m_fObjPosZ(g_pMapDataManager->GetObjPosZ())
	, m_fObjSize(g_pMapDataManager->GetObjSize())
	, m_fObjRotX(g_pMapDataManager->GetObjRotX())
	, m_fObjRotY(g_pMapDataManager->GetObjRotY())
	, m_fObjRotZ(g_pMapDataManager->GetObjRotZ())
	, m_pPickPos(NULL)
	, m_pFollowObject(NULL)
{
}

cMapObjectTool::~cMapObjectTool()
{
    // vector 비우기 
	if (!m_vecObjects.empty())
	{
		for (int i = 0; i < m_vecObjects.size(); i++)
		{
			SAFE_DELETE(m_vecObjects[i]);
		}
	}

    // map 비우기
	if (!m_mapMesh.empty())
	{
		for (auto iter = m_mapMesh.begin(); iter != m_mapMesh.end(); iter++)
		{
			SAFE_RELEASE(iter->second->Mesh);
			SAFE_DELETE_ARRAY(iter->second->Materials);

			for (int i = 0; i < iter->second->NumMaterials; i++)
			{
				SAFE_RELEASE(iter->second->Textures[i]);
			}
		
		}
	}

    // 테스트 메쉬 해제
	SAFE_RELEASE(m_pTestBox);
}

HRESULT cMapObjectTool::Setup()
{
	// 테스트용 메쉬 생성
	D3DXCreateBox(g_pDevice, 5, 5, 5, &m_pTestBox, NULL);
	return S_OK;
}

HRESULT cMapObjectTool::Update()
{
	//if (g_pMapDataManager->GetObjLocation())
	//{
	//	if (!m_pFollowObject)
	//	{
	//		SetupFollowObject();
	//	}
	//	else
	//	{
	//		UpdateFollowObject();
	//	}
	//}
	//else
	//{
	//	if (m_pFollowObject)
	//	{
	//		InitDefaultFollowObject();
	//	}
	//}

	return S_OK;
}

HRESULT cMapObjectTool::Render()
{
    g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    g_pDevice->LightEnable(D3DRS_LIGHTING, false);

	if (!m_vecObjects.empty())
	{
		for (int i = 0; i < m_vecObjects.size(); i++)
		{			
			g_pDevice->SetTransform(D3DTS_WORLD, &m_vecObjects[i]->World);
			// 테스트용
			if (m_pTestBox)
			{
				//g_pDevice->SetMaterial(&BLUE_MTRL);
				//m_pTestBox->DrawSubset(0);
                //g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

            // 메쉬로 그리기 
			if (m_vecObjects[i]->Mesh)
			{
				/*for (DWORD j = 0; j < (m_vecObjects[i]->Mesh->NumMaterials); j++)
				{
					g_pDevice->SetMaterial(&m_vecObjects[i]->Mesh->Materials[j]);
					g_pDevice->SetTexture(0, m_vecObjects[i]->Mesh->Textures[j]);
					m_vecObjects[i]->Mesh->Mesh->DrawSubset(j);
				}*/

                g_pDevice->SetMaterial(&m_vecObjects[i]->Mesh->Materials[0]);
                g_pDevice->SetTexture(0, m_vecObjects[i]->Mesh->Textures[0]);
                m_vecObjects[i]->Mesh->Mesh->DrawSubset(0);
				//g_pDevice->SetTexture(0, NULL);
			}
		}
	}

    //g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (m_pFollowObject)
	{
		RenderFollowObject();
	}

	return S_OK;
}

void cMapObjectTool::SetupFollowObject()
{
	m_pFollowObject = new ST_MAP_OBJECT;
	
	m_pFollowObject->PosX = m_pPickPos->x;
	m_pFollowObject->PosY = m_pPickPos->y;
	m_pFollowObject->PosZ = m_pPickPos->z;

	m_pFollowObject->Size = m_fObjSize;

	m_pFollowObject->RotX = m_fObjRotX;
	m_pFollowObject->RotY = m_fObjRotY;
	m_pFollowObject->RotZ = m_fObjRotZ;

	m_pFollowObject->Collision = m_isObjCollison;
	m_pFollowObject->Destruction = m_isObjDestruction;

	D3DXMATRIXA16 scale, rotX, rotY, rotZ, trans;
	D3DXMatrixScaling(&scale, m_pFollowObject->Size, m_pFollowObject->Size, m_pFollowObject->Size);
	D3DXMatrixRotationX(&rotX, m_pFollowObject->RotX);
	D3DXMatrixRotationY(&rotY, m_pFollowObject->RotY);
	D3DXMatrixRotationZ(&rotZ, m_pFollowObject->RotZ);
	D3DXMatrixTranslation(&trans, m_pFollowObject->PosX, m_pFollowObject->PosY, m_pFollowObject->PosZ);

	m_pFollowObject->World = (scale * rotX * rotY * rotZ* trans);
}

void cMapObjectTool::UpdateFollowObject()
{
	if (m_pFollowObject)
	{
		m_pFollowObject->PosX = m_pPickPos->x;
		m_pFollowObject->PosY = m_pPickPos->y;
		m_pFollowObject->PosZ = m_pPickPos->z;

		m_pFollowObject->Size = m_fObjSize;

		m_pFollowObject->RotX = m_fObjRotX;
		m_pFollowObject->RotY = m_fObjRotY;
		m_pFollowObject->RotZ = m_fObjRotZ;

		m_pFollowObject->Collision = m_isObjCollison;
		m_pFollowObject->Destruction = m_isObjDestruction;

		D3DXMATRIXA16 scale, rotX, rotY, rotZ, trans;
		D3DXMatrixScaling(&scale, m_pFollowObject->Size, m_pFollowObject->Size, m_pFollowObject->Size);
		D3DXMatrixRotationX(&rotX, m_pFollowObject->RotX);
		D3DXMatrixRotationY(&rotY, m_pFollowObject->RotY);
		D3DXMatrixRotationZ(&rotZ, m_pFollowObject->RotZ);
		D3DXMatrixTranslation(&trans, m_pFollowObject->PosX, m_pFollowObject->PosY, m_pFollowObject->PosZ);

		m_pFollowObject->World = (scale * rotX * rotY * rotZ* trans);
	}
}

void cMapObjectTool::RenderFollowObject()
{
	g_pDevice->LightEnable(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetMaterial(&WHITE_MTRL);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_pFollowObject->World);
	m_pTestBox->DrawSubset(0);

	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pDevice->LightEnable(D3DRS_LIGHTING, false);
}

void cMapObjectTool::InitDefaultFollowObject()
{
	SAFE_DELETE(m_pFollowObject);
}

ST_OBJECT_MESH * cMapObjectTool::GetMesh(string key)
{
	auto iter = m_mapMesh.find(key);

	if (iter != m_mapMesh.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

ST_OBJECT_MESH * cMapObjectTool::GetMesh(string key, string filePath, string fileName)
{
	auto iter = m_mapMesh.find(key);

	if (iter == m_mapMesh.end())
	{
		ST_OBJECT_MESH* objMesh = new ST_OBJECT_MESH;
		string fullPath = filePath +"\\"+ fileName;
		LPD3DXBUFFER pD3DXMtrlBuffer;

		if (FAILED(D3DXLoadMeshFromX(fullPath.c_str(), D3DXMESH_MANAGED, g_pDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &objMesh->NumMaterials, &objMesh->Mesh)))
		{
			MessageBox(NULL, "X파일 로드 실패", "메쉬 로드 실패", MB_OK);
		}

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		objMesh->Materials = new D3DMATERIAL9[objMesh->NumMaterials];
		objMesh->Textures = new LPDIRECT3DTEXTURE9[objMesh->NumMaterials];

		for (DWORD i = 0; i < objMesh->NumMaterials; i++)
		{
			objMesh->Materials[i] = d3dxMaterials[i].MatD3D;
			objMesh->Materials[i].Ambient = objMesh->Materials[i].Diffuse;
			objMesh->Textures[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				string texturePath = filePath +"\\"+ d3dxMaterials[i].pTextureFilename;
				
				if (FAILED(D3DXCreateTextureFromFile(g_pDevice, texturePath.c_str(), &objMesh->Textures[i])))
				{
					MessageBox(NULL, "X파일 로드 실패", "텍스쳐 로드 실패", MB_OK);
				}
			}
		}
		pD3DXMtrlBuffer->Release();

        objMesh->Mesh->Optimize(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, 0, 0, 0, 0, 0);
		m_mapMesh.insert(make_pair(key, objMesh));

		return m_mapMesh[key];

	}
	else
	{
		return NULL;
	}
}

void cMapObjectTool::AddObject(Vector3 vCollisonPos)
{
	ST_MAP_OBJECT* object = new ST_MAP_OBJECT;

	object->Id = m_nObjId++;
	object->MeshName = g_pMapDataManager->GetMeshKey();

	object->PosX = vCollisonPos.x;
	object->PosY = vCollisonPos.y;
	object->PosZ = vCollisonPos.z;

	object->Size = m_fObjSize;

	object->RotX = m_fObjRotX;
	object->RotY = m_fObjRotY;
	object->RotZ = m_fObjRotZ;

	object->Collision = m_isObjCollison;
	object->Destruction = m_isObjDestruction;

	D3DXMATRIXA16 scale, rotX, rotY, rotZ, trans;
	D3DXMatrixScaling(&scale, object->Size, object->Size, object->Size);
	D3DXMatrixRotationX(&rotX, object->RotX);
	D3DXMatrixRotationY(&rotY, object->RotY);
	D3DXMatrixRotationZ(&rotZ, object->RotZ);
	D3DXMatrixTranslation(&trans, object->PosX, object->PosY, object->PosZ);

	object->World = (scale * rotX * rotY * rotZ * trans);

	if (!g_pMapDataManager->GetMeshKey().empty())
	{
		string key = g_pMapDataManager->GetMeshKey();
		string path = g_pMapDataManager->GetMeshFilePath();
		string name = g_pMapDataManager->GetMeshFileName();

		object->Mesh = GetMesh(key, path, name);

		if (object->Mesh == NULL)
		{
			object->Mesh = GetMesh(object->MeshName);
		}
	}

	m_vecObjects.push_back(object);
}

// 마우스 왼쪽 버튼을 클릭 했을 때 발동
void cMapObjectTool::OnceLButtonDown()
{
	if (g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_LOCATE)
	{
		if (m_pPickPos)
		{
			AddObject(*m_pPickPos);
		}
	}
    else if (g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_RELOCATE)
    {

    }
    else if (g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_REMOVE)
    {

    }
    else  //
    {

    }
}

// 마우스 왼쪽 버튼을 계속 누르고 있을 때 발동
void cMapObjectTool::StayLButtonDown()
{
}
