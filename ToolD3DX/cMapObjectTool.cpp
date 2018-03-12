#include "stdafx.h"
#include "cMapObjectTool.h"
#include "cMapObject.h"
#include "cRay.h"
#include "resource.h"

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
	
	// ��� ���� 
	, m_eBlockButtonState(g_pMapDataManager->GetBlockButtonState())
	, m_SelectedBlockGroupName(g_pMapDataManager->GetSelectedBlockGroupName())
	, m_nCurWorkingBlockGroupIndex(INVALIDE_VALUE)
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

    // ��� ���� �����
    if (!m_vecBlockGroups.empty())
    {
        for (int i = 0; i < m_vecBlockGroups.size(); i++)
        {
            SAFE_DELETE(m_vecBlockGroups[i]);
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

    // ��� ��ġ 
    switch (g_pMapDataManager->GetBlockButtonState())
    {
    case E_BLOCK_BTN_START:
    {
        ST_BLOCK_GROUP* blockGroup = new ST_BLOCK_GROUP;

        int red = rand() % 256;
        int green = rand() % 256;
        int blue = rand() % 256;

        blockGroup->GroupColor = D3DCOLOR_XRGB(red, green, blue);

        blockGroup->GroupName = g_pMapDataManager->GetSelectedBlockGroupName();
        m_vecBlockGroups.push_back(blockGroup);
        m_nCurWorkingBlockGroupIndex = (int)(m_vecBlockGroups.size() - 1);
        m_eBlockButtonState = E_BLOCK_BTN_PROGRESS;
    }
    break;
    case E_BLOCK_BTN_MODIFY:
    {
        int index = GetBlockGroupByName(g_pMapDataManager->GetSelectedBlockGroupName());

        if (index != INVALIDE_VALUE)
        {
            m_nCurWorkingBlockGroupIndex = index;
        }

        m_eBlockButtonState = E_BLOCK_BTN_PROGRESS;
    }
    break;
    case E_BLOCK_BTN_DELETE :
    {
        int index = GetBlockGroupByName(g_pMapDataManager->GetSelectedBlockGroupName());

		if (index != INVALIDE_VALUE)
		{
			SAFE_DELETE(m_vecBlockGroups[index]);
			m_vecBlockGroups.erase(m_vecBlockGroups.begin() + index);
		}

		m_SelectedBlockGroupName = NO_NAME;
        m_eBlockButtonState = E_BLOCK_BTN_MAX;
    }
    case E_BLOCK_BTN_END:
    {
        if (m_nCurWorkingBlockGroupIndex != INVALIDE_VALUE)
        {
            m_nCurWorkingBlockGroupIndex = INVALIDE_VALUE;
        }

        m_eBlockButtonState = E_BLOCK_BTN_MAX;
    }
    break;
    }

   return S_OK;
}

HRESULT cMapObjectTool::Render()
{
    // ������Ʈ�� �׸���
    if (!m_vecObjects.empty())  
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

    // ��� �׸��� 
    if (!m_vecBlockGroups.empty())
    {
        for (int i = 0; i < m_vecBlockGroups.size(); i++)
        {
            if (!m_vecBlockGroups[i]->vecPoints.empty())
            {
           
                for(int j = 0; j < m_vecBlockGroups[i]->vecPoints.size(); j++)
                {
                    g_pDevice->LightEnable(0, true);
                    // Sphere mesh �׸��� �κ� 
                    Vector3 pos = m_vecBlockGroups[i]->vecPoints[j].p;
                    Matrix4 matS, matT, matW;
                    D3DXMatrixScaling(&matS, BLOCK_RADIUS, BLOCK_RADIUS, BLOCK_RADIUS);
                    D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

                    matW = matS * matT;
                    g_pDevice->SetTransform(D3DTS_WORLD, &matW);

                    if (j == 0)
                    {
                        g_pDevice->SetMaterial(&RED_MTRL);
                    }
                    else if( j == m_vecBlockGroups[i]->vecPoints.size() -1)
                    {
                        g_pDevice->SetMaterial(&GREEN_MTRL);
                    }
                    else
                    {
                        g_pDevice->SetMaterial(&BLUE_MTRL);
                    }
                    m_SphereMesh->DrawSubset(0);
                    g_pDevice->LightEnable(0, false);
                }

                // ���� �� �׸��� 
                D3DXMATRIXA16 matW;
                D3DXMatrixIdentity(&matW);
                g_pDevice->SetFVF(ST_PC_VERTEX::FVF);
                g_pDevice->SetTransform(D3DTS_WORLD, &matW);
                
                int LineNum = (int)(m_vecBlockGroups[i]->vecPoints.size() - 1);
                if (LineNum < 0)
                {
                    LineNum = 0;
                }

                g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, LineNum,
                    &m_vecBlockGroups[i]->vecPoints[0], sizeof(ST_PC_VERTEX));
            }
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
        m_pFollowObject = new cMapObject(g_pMapDataManager->GetFileName(), g_pMapDataManager->GetFilePath(), g_pMapDataManager->GetFileName());
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
    string filePath = g_pMapDataManager->GetFilePath();
    string fileName = g_pMapDataManager->GetFileName();

    // ������Ʈ ����
    cMapObject* pMapObject = new cMapObject(fileName, filePath, fileName);
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
                    // ���� �������� �ش�Ǵ� �༮�� ������ �ٲ��
                    Vector3 RotXYZ = m_vecObjects[m_nSelectedIndex]->GetRotationXYZ();
                    m_fObjSize = m_vecObjects[m_nSelectedIndex]->GetScale().x;
                    m_fObjRotX = RotXYZ.x;
                    m_fObjRotY = RotXYZ.y;
                    m_fObjRotZ = RotXYZ.z;
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

    // BLOCK_EDIT_BUTTON
    switch (g_pMapDataManager->GetBlockButtonState())
    {
    case E_BLOCK_BTN_PROGRESS:
    {
        cRay ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);
        bool collision = false;
        int index = -1;

        for (int i = 0; i < m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints.size(); i++)
        {
            if (CollideRayNCircle(ray, m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints[i].p, BLOCK_RADIUS))
            {
                collision = true;
                index = i;
            }
        }
        if (collision)
        {
            m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints.erase(m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints.begin() + index);
        }
        else
        {
            m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints.push_back(ST_PC_VERTEX(*m_pPickPos, m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->GroupColor));
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
            float radius = m_vecObjects[i]->GetScale().x; // �׳� �������� ���������� ��� ���� 
            if (CollideRayNCircle(ray, m_vecObjects[i]->GetPositon(), radius))
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

bool cMapObjectTool::CollideRayNCircle(cRay ray, Vector3 vTargetPos, float fTargetRadius)
{
    Vector3 vLocalOrg = ray.m_vOrg - vTargetPos;

    float qv = D3DXVec3Dot(&vLocalOrg, &ray.m_vDir);
    float vv = D3DXVec3Dot(&ray.m_vDir, &ray.m_vDir);
    float qq = D3DXVec3Dot(&vLocalOrg, &vLocalOrg);
    float rr = fTargetRadius * fTargetRadius;

    float result = qv * qv - vv * (qq - rr);

    if (result >= 0)
    {
        return true;
    }
    return false;
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

    rt = { 0, 250, 100, 300 };

    s = g_pMapDataManager->GetSelectedBlockGroupName();
    
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));
}

int cMapObjectTool::GetBlockGroupByName(string BlockName)
{
    for (int i = 0; i < m_vecBlockGroups.size(); i++)
    {
        if (m_vecBlockGroups[i]->GroupName == BlockName)
        {
            return i;
        }
    }
    return INVALIDE_VALUE;
}
