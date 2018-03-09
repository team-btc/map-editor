#include "stdafx.h"
#include "cMapObjectTool.h"
#include "cMapObject.h"
#include "cRay.h"

cMapObjectTool::cMapObjectTool()
	: m_SphereMesh(NULL)
	, m_isObjCollison(g_pMapDataManager->GetObjCollision())
	, m_isObjDestruction(g_pMapDataManager->GetObjDestruction())
	, m_fObjPosX(g_pMapDataManager->GetObjPosX())
	, m_fObjPosY(g_pMapDataManager->GetObjPosY())
	, m_fObjPosZ(g_pMapDataManager->GetObjPosZ())
	, m_fObjSize(g_pMapDataManager->GetObjSize())
	, m_fObjRotX(g_pMapDataManager->GetObjRotX())
	, m_fObjRotY(g_pMapDataManager->GetObjRotY())
	, m_fObjRotZ(g_pMapDataManager->GetObjRotZ())
    , m_nObjectMakeTotalNum(0)
    , m_nSelectedIndex(INVALIDE_VALUE)
    , m_pPickPos(NULL)
	, m_pFollowObject(NULL)
    , m_fRadius(5.0f)
{}

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
	SAFE_RELEASE(m_SphereMesh);
}

HRESULT cMapObjectTool::Setup()
{
    // �Ž� �ʱ�ȭ 
	D3DXCreateSphere(g_pDevice, 1, 10, 10, &m_SphereMesh, NULL);
    
    // ��Ʈ���� �ʱ�ȭ 
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
        case E_OBJ_TAB_BTN_LOCATE: // ������Ʈ ��ġ
        {
            if (!m_pFollowObject)  // ���콺 ����ٴϴ� ������Ʈ�� NULL �� �� 
            {
                SetFollowObject(); // ���콺 ����ٴϴ� ������Ʈ ����
            }
            else  // ���콺 ����ٴϴ� ������Ʈ�� ���� ��
            {
                UpdateFollowObject();  // ���콺 ����ٴϴ� ������Ʈ ��Ʈ���� ���� 
            }
        } 
        break;
        case E_OBJ_TAB_BTN_RELOCATE: // ������Ʈ ���ġ
        {
            if (m_nSelectedIndex != INVALIDE_VALUE)  // ���ġ �� ������Ʈ�� ���õǾ�����
            {
                UpdateFollowObject();  // ���콺 ����ٴϴ� ���ġ�� ������Ʈ ��Ʈ���� ���� 
            }
        }
        break;
    }

    // ������Ʈ �� ��ư ���°� ��ġ�� �ƴ� �� �ٸ� ��ư�� ������ ����ٴϴ� �༮ ���ֱ�
    if (g_pMapDataManager->GetObjectTabButtonState() != E_OBJ_TAB_BTN_LOCATE)
    {
        if (m_pFollowObject)       // ����ٴϴ� ������Ʈ�� ���� ���  
        {
            DeleteFollowObject();  // ������Ʈ ����� 
        }
    }

	return S_OK;
}

HRESULT cMapObjectTool::Render()
{
    if (!m_vecObjects.empty())  // ������Ʈ�� �׸���
	{
		for (int i = 0; i < m_vecObjects.size(); i++)
		{			
            // ���ġ || ���� ����� ���� ��ŷ �浹 ���� �����ֱ� 
            if (g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_RELOCATE
                || g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_REMOVE)
            {
                g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
                g_pDevice->SetTransform(D3DTS_WORLD, &m_vecObjects[i]->GetWorldMatrix());
                m_SphereMesh->DrawSubset(0);
                g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            }
            // ������Ʈ �׸��� 
            m_vecObjects[i]->Render();
		}
	}

    if (m_pFollowObject) // ���콺 ����ٴϴ� ������Ʈ �׸���
    {
        RenderFollowObject();
    }

    if (DEBUG_RENDER)   // ����� ���� 
    {
        DebugTestRender();
    }

	return S_OK;
}

// ���콺 ����ٴϴ� ������Ʈ ����
void cMapObjectTool::SetFollowObject()
{
    // NULL�� �ƴҶ��� ���� �ǰ� 
    if (!m_pFollowObject)
    {
        m_pFollowObject = new cMapObject(g_pMapDataManager->GetMeshKey(), g_pMapDataManager->GetMeshFilePath(), g_pMapDataManager->GetMeshFileName());
        m_pFollowObject->Setup(Vector3(m_fObjSize, m_fObjSize, m_fObjSize), Vector3(m_fObjRotX, m_fObjRotY, m_fObjRotZ), *m_pPickPos);    
    }
}

// ���콺 ����ٴϴ� ������Ʈ ����
void cMapObjectTool::UpdateFollowObject()
{
    // ���� ��Ʈ���� ����
    UpdateMatrix();

    if (m_pFollowObject)  // ��ġ ��� �϶�
    {
        m_pFollowObject->SetWorldMatrix(m_matScale* m_matRotation * m_matTrans);
    }
    else  // ���ġ ��� �϶�
    {
        if (m_nSelectedIndex != INVALIDE_VALUE)
        {
            Matrix4 world = m_matScale*m_matRotation*m_matTrans;
            m_vecObjects[m_nSelectedIndex]->SetScale(Vector3(m_fObjSize, m_fObjSize, m_fObjSize));
            m_vecObjects[m_nSelectedIndex]->SetRotationXYZ(Vector3(m_fObjRotX, m_fObjRotY, m_fObjRotZ));
            m_vecObjects[m_nSelectedIndex]->SetPosition(*m_pPickPos);
            m_vecObjects[m_nSelectedIndex]->UpdateMatrix();
        }
    }
}

// ���콺 ����ϴ� ������Ʈ �׸���
void cMapObjectTool::RenderFollowObject()
{
    // �����Ͱ� ���� ������ 
    if (m_pFollowObject)
    {
        g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        m_pFollowObject->Render();

        g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    }
}

// ���콺 ����ٴϴ� ������Ʈ ���� 
void cMapObjectTool::DeleteFollowObject()
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

// ������Ʈ ����(��ŷ �� ������ ������)
void cMapObjectTool::AddObject(Vector3 vPickPos)
{
    string key = g_pMapDataManager->GetMeshKey();
    string path = g_pMapDataManager->GetMeshFilePath();
    string name = g_pMapDataManager->GetMeshFileName();

    // ������Ʈ ����
    cMapObject* pMapObject = new cMapObject(key, path, name);
    // ������Ʈ ����(���ο��� �����Ʈ������ ���õ�)
    pMapObject->Setup(Vector3(m_fObjSize, m_fObjSize, m_fObjSize), Vector3(m_fObjRotX, m_fObjRotY, m_fObjRotZ), (*m_pPickPos));
    // ������Ʈ ���̵� ���� 
    pMapObject->SetId(m_nObjectMakeTotalNum++);
    m_vecObjects.push_back(pMapObject);
}

// ���콺 ���� ��ư�� Ŭ�� ���� �� �ߵ�
void cMapObjectTool::OnceLButtonDown()
{
    // ������Ʈ �� ��ư ���¿� ���� ������Ʈ �б�
    switch (g_pMapDataManager->GetObjectTabButtonState())
    {
    case E_OBJ_TAB_BTN_LOCATE:       // ������Ʈ ��ġ
    {
        if (m_pPickPos)              // ��ŷ ��ġ�� �ּҰ� �������� 
        {
            AddObject(*m_pPickPos);  // ������Ʈ �߰��ϱ� 
        }
    }
    break;
    case E_OBJ_TAB_BTN_RELOCATE:     // ������Ʈ ���ġ
    {
        if (!m_vecObjects.empty())   // ���Ͱ� ��������� ���� ���ġ �˻縦 �� �ʿ䰡 ����
        {
            if (m_nSelectedIndex == INVALIDE_VALUE)
            {
                int nId = PickObject();    // ������Ʈ�� ��ŷ �˻縦 �Ͽ� ������Ʈ�� ���̵� �������� 

                if (nId != INVALIDE_VALUE) // INVALIDE_VALUE (-1)�� ���� ��ŷ �� ������Ʈ�� ���� ��
                {
                    m_nSelectedIndex = FindObject(nId);  // id�� ���� ������Ʈ ���Ϳ��� �ش� �ε����� �������� 

                    // ���� �������� �ش�Ǵ� �༮�� ������ �ٲ�� ������ ������?
                    // Vector3 RotXYZ = m_vecObjects[m_nSelectObjectId]->GetRotationXYZ();
                    // m_fObjSize = m_vecObjects[m_nSelectObjectId]->GetScale().x;
                    // m_fObjRotX = RotXYZ.x;
                    // m_fObjRotY = RotXYZ.y;
                    // m_fObjRotZ = RotXYZ.z;
                }
            }
            else
            {
                m_nSelectedIndex = INVALIDE_VALUE;     // ��ġ�� ������ ������ ������Ʈ�� ���� 
            }
        }
    }
    break;
    case E_OBJ_TAB_BTN_REMOVE:    // ������Ʈ ���� 
    {
        if (!m_vecObjects.empty())    //���Ϳ� ������Ʈ�� �������� �۵��ϰ� 
        {
            int nId = PickObject();

            if (nId != INVALIDE_VALUE)
            {
                int index = FindObject(nId);

                if (index != INVALIDE_VALUE)
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
    ;
}

int cMapObjectTool::PickObject()
{
    if (!m_vecObjects.empty())
    {
        cRay ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

        for (int i = 0; i < m_vecObjects.size(); i++)
        {
            //Ray �� �浹 �϶� 
            Vector3 scale = m_vecObjects[i]->GetScale();
            float radius = scale.x; // �׳� �������� ���������� ��� ���� 

            Vector3 vObjCenter = m_vecObjects[i]->GetPositon();
            Vector3 vLocalOrg = ray.m_vOrg - vObjCenter;

            float qv = D3DXVec3Dot(&vLocalOrg, &ray.m_vDir);
            float vv = D3DXVec3Dot(&ray.m_vDir, &ray.m_vDir);
            float qq = D3DXVec3Dot(&vLocalOrg, &vLocalOrg);
            float rr = radius * radius;

            float result = qv * qv - vv * (qq - rr);

            if (result >= 0)
            {
                return m_vecObjects[i]->GetId();
            }
        }
    }

    return INVALIDE_VALUE;
}

// ������Ʈ ���̵�� 
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
    return INVALIDE_VALUE;
}

// �� �浹 �Ⱦ�
bool cMapObjectTool::CollideRound(Vector3 vMyPos, float fMyRadius, Vector3 vTargetPos, float fTargetRadius)
{
    D3DXVECTOR3 v = vTargetPos - vMyPos;
    float length = D3DXVec3Length(&v);

    if (length <= fTargetRadius + fMyRadius) // �浹
    {
        return true;
    }
    else
    {
        return false;
    }
}

// ����� ����
void cMapObjectTool::DebugTestRender()
{
    RECT rt = { 0, 100, 100, 150};
    string s;

    rt = { 0, 150, 100, 200 };
    s = "���õ� �ε��� : ";
    s = s + to_string((int)m_nSelectedIndex);
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));


    rt = { 0, 200, 100, 250 };
    
    switch (g_pMapDataManager->GetObjectTabButtonState())
    {
    case E_OBJ_TAB_BTN_LOCATE:
        s = "�����̼� ��ư ����";
        break;
    case E_OBJ_TAB_BTN_RELOCATE:
        s = "�������̼� ��ư ����";
        break;
    case E_OBJ_TAB_BTN_REMOVE:
        s = "������ ��ư ����";
        break;
    case E_OBJ_TAB_BTN_MAX:
        s = "ĵ�� ��ư ����";
        break;
    }

    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));
}
