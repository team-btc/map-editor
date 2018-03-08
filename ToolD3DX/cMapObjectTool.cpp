#include "stdafx.h"
#include "cMapObjectTool.h"
#include "cMapObject.h"
#include "cRay.h"

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
    , m_nSelectObjectId(-1)
    , m_pPickPos(NULL)
	, m_pFollowObject(NULL)
    , m_isRelocation(false)
{
}

cMapObjectTool::~cMapObjectTool()
{
    // vector ���� 
	if (!m_vecObjects.empty())
	{
		for (int i = 0; i < m_vecObjects.size(); i++)
		{
			SAFE_DELETE(m_vecObjects[i]);
		}
	}

    // �׽�Ʈ �޽� ����
	SAFE_RELEASE(m_pTestBox);
}

HRESULT cMapObjectTool::Setup()
{
	// �׽�Ʈ�� �޽� ����
	D3DXCreateSphere(g_pDevice, 1, 10, 10, &m_pTestBox, NULL);
    // �Ž� �ʱ�ȭ 
    D3DXMatrixIdentity(&m_matScale);
    D3DXMatrixIdentity(&m_matRotation);
    D3DXMatrixIdentity(&m_matTrans);
	return S_OK;
}

HRESULT cMapObjectTool::Update()
{
    // ������Ʈ �� ��ư ���¿� ���� ������Ʈ �б�
    switch (g_pMapDataManager->GetObjectTabButtonState())
    {
        // ������Ʈ ��ġ
        case E_OBJ_TAB_BTN_LOCATE:
        {
            // ��Ʈ���� ����
            UpdateMatrix();
            // ���� �߰��ϴ� ������Ʈ�϶�
            if (!m_pFollowObject)
            {
            	SetupFollowObject();
            }
            else
            {
                UpdateFollowObject();
            }
        } 
        break;
        // ������Ʈ ���ġ
        case E_OBJ_TAB_BTN_RELOCATE:
        {
            if (m_isRelocation)
            {
                UpdateMatrix();
                
                if (m_nSelectObjectId != -1)
                {
                    m_vecObjects[m_nSelectObjectId]->Setup(m_matScale, m_matRotation, m_matTrans);
                }
            }
        }
        break;
        // ������Ʈ ���� 
        case E_OBJ_TAB_BTN_REMOVE:
        {

        }
        break;
        case E_OBJ_TAB_BTN_MAX:
        {
            if (m_pFollowObject)
                InitDefaultFollowObject();
        }
        break;
    }
	return S_OK;
}

HRESULT cMapObjectTool::Render()
{
    g_pDevice->LightEnable(D3DRS_LIGHTING, true);
    // ������Ʈ�� �׸���
	if (!m_vecObjects.empty())
	{
		for (int i = 0; i < m_vecObjects.size(); i++)
		{			
            // ��ŷ �׽�Ʈ��
            g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
           
            D3DXMATRIXA16 matWorld = m_vecObjects[i]->GetWorldMatrix();
            matWorld._42 += (matWorld._22 / 2);

            g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
            m_pTestBox->DrawSubset(0);
            g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

            // ������Ʈ �׸��� 
            m_vecObjects[i]->Render();
		}
	}

    // ���콺 ����ٴϴ� ģ�� �׸���
    if (m_pFollowObject)
        RenderFollowObject();

    g_pDevice->LightEnable(D3DRS_LIGHTING, false);
	return S_OK;
}

void cMapObjectTool::SetupFollowObject()
{
	m_pFollowObject = new cMapObject(g_pMapDataManager->GetMeshKey(), g_pMapDataManager->GetMeshFilePath(), g_pMapDataManager->GetMeshFileName());
    m_pFollowObject->Setup(m_matScale, m_matRotation, m_matTrans);
}

void cMapObjectTool::UpdateFollowObject()
{
    m_pFollowObject->Setup(m_matScale, m_matRotation, m_matTrans);
}

void cMapObjectTool::RenderFollowObject()
{
    if (m_pFollowObject)
    {
        g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        m_pFollowObject->Render();

        g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    }
}

void cMapObjectTool::InitDefaultFollowObject()
{
	SAFE_DELETE(m_pFollowObject);
}

// ���� ��Ʈ���� ����
void cMapObjectTool::UpdateMatrix()
{
    D3DXMATRIXA16 rotX, rotY, rotZ;
    D3DXMatrixScaling(&m_matScale, m_fObjSize, m_fObjSize, m_fObjSize);
    D3DXMatrixRotationX(&rotX, m_fObjRotX);
    D3DXMatrixRotationY(&rotY, m_fObjRotY);
    D3DXMatrixRotationZ(&rotZ, m_fObjRotZ);
    m_matRotation = rotX * rotY * rotZ;
    D3DXMatrixTranslation(&m_matTrans, m_pPickPos->x, m_pPickPos->y, m_pPickPos->z);
}

void cMapObjectTool::AddObject(Vector3 vCollisonPos)
{
    string key = g_pMapDataManager->GetMeshKey();
    string path = g_pMapDataManager->GetMeshFilePath();
    string name = g_pMapDataManager->GetMeshFileName();

    cMapObject* pMapObject = new cMapObject(key, path, name);
    pMapObject->Setup(m_matScale, m_matRotation, m_matTrans);
    pMapObject->SetId(m_nObjId++);
    m_vecObjects.push_back(pMapObject);
}

// ���콺 ���� ��ư�� Ŭ�� ���� �� �ߵ�
void cMapObjectTool::OnceLButtonDown()
{
    // ������Ʈ �� ��ư ���¿� ���� ������Ʈ �б�
    switch (g_pMapDataManager->GetObjectTabButtonState())
    {
    // ������Ʈ ��ġ
    case E_OBJ_TAB_BTN_LOCATE:
    {
        if (m_pPickPos)
        {
            AddObject(*m_pPickPos);
        }
    }
    break;
    // ������Ʈ ���ġ
    case E_OBJ_TAB_BTN_RELOCATE:
    {
        if (m_pFollowObject)
            InitDefaultFollowObject();

        if (!m_isRelocation)
        {
            if (!m_vecObjects.empty())
            {
                int nId = PickObject();
                if (nId != -1)
                {
                    m_nSelectObjectId = FindObject(nId);
                    m_isRelocation = true;
            
                }
            }
        }
        else
        {
            m_isRelocation = false;
            m_nSelectObjectId = -1;
        }
    }
    break;
    // ������Ʈ ���� 
    case E_OBJ_TAB_BTN_REMOVE:
    {
        if (m_pFollowObject)
            InitDefaultFollowObject();
        
        // ���Ϳ� ������Ʈ�� �������� �۵��ϰ� 
        if (!m_vecObjects.empty())
        {
            int nId = PickObject();
            if (nId != -1)
            {
                int index = FindObject(nId);

                if (index != -1)
                {
                    SAFE_DELETE(m_vecObjects[index]);
                    m_vecObjects.erase(m_vecObjects.begin() + index);
                }
            }
        }
    }
    break;
    }
}

// ���콺 ���� ��ư�� ��� ������ ���� �� �ߵ�
void cMapObjectTool::StayLButtonDown()
{
}

int cMapObjectTool::PickObject()
{
    if (!m_vecObjects.empty())
    {
        cRay ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

        for (int i = 0; i < m_vecObjects.size(); i++)
        {
            Matrix4 mat = m_vecObjects[i]->GetWorldMatrix();
            float radius = mat._11;

            Vector3 vObjCenter(mat._41, mat._42, mat._43);
            Vector3 vLocalOrg = ray.m_vOrg - vObjCenter;

            float qv = D3DXVec3Dot(&vLocalOrg, &ray.m_vDir);
            float vv = D3DXVec3Dot(&ray.m_vDir, &ray.m_vDir);
            float qq = D3DXVec3Dot(&vLocalOrg, &vLocalOrg);
            float rr = mat._11 *mat._11;

            if (qv * qv - vv * (qq - rr) >= 0)
            {
                return m_vecObjects[i]->GetId();
            }
        }
    }

    return -1;
}

int cMapObjectTool::FindObject(int nId)
{
    if (!m_vecObjects.empty())
    {
        for (int i = 0; i < m_vecObjects.size(); i++)
        {
            if (m_vecObjects[i]->GetId() == nId)
            {
                return i;
            }
        }
    }
    return -1;
}
