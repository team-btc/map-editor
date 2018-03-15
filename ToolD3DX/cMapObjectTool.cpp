#include "stdafx.h"
#include "cMapObjectTool.h"
#include "cMapObject.h"
#include "cRay.h"
#include "resource.h"
#include "cMapTerrainTool.h"

cMapObjectTool::cMapObjectTool()
    : m_SphereMesh(NULL)
    , m_isObjCollison(g_pMapDataManager->GetObjCollision())
    , m_isObjDestruction(g_pMapDataManager->GetObjDestruction())
    , m_isObjEnemy(g_pMapDataManager->GetObjEnemy())
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
    , m_eObjectButtonState(g_pMapDataManager->GetObjectButtonState())
    , m_SelectedBlockGroupName(g_pMapDataManager->GetSelectedBlockGroupName())
    , m_nCurWorkingBlockGroupIndex(INVALIDE_VALUE)
    , m_pTerrainTool(NULL)
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
    switch (g_pMapDataManager->GetObjectButtonState())
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
    if (g_pMapDataManager->GetObjectButtonState() != E_OBJ_TAB_BTN_LOCATE)
    {
        if (m_pFollowObject)       // ����ٴϴ� ������Ʈ�� ���� ���  
        {
            DeleteFollowObject();  // ������Ʈ ����� 
        }
    }


    // �����ϱ� 
    if (!m_vecObjects.empty())
    {
        if (m_pTerrainTool != NULL)
        {
            if (m_pTerrainTool->GetMesh() != NULL)
            {
                for (int i = 0; i < m_vecObjects.size(); i++)
                {
                    BOOL isHit = false;
                    float fDist;
                    Vector3 pos = m_vecObjects[i]->GetPositon();
                    pos.y += 300.0f;
                    Vector3 dir(0, -1, 0);

                    D3DXIntersectSubset(m_pTerrainTool->GetMesh(), 0, &pos, &dir, &isHit, NULL, NULL, NULL, &fDist, NULL, NULL);

                    if (isHit)
                    {
                        pos.y -= fDist;

                        //m_vecObjects[i]->SetPosition(pos2);
                        m_vecObjects[i]->UpdateMatrix(pos);
                    }
                }
            }
        }
    }

    // ��� ��ġ 
    switch (g_pMapDataManager->GetBlockButtonState())
    {
    case E_BLOCK_BTN_NEW:
    {
        ST_BLOCK_GROUP* blockGroup = new ST_BLOCK_GROUP;

        int red = rand() % 256;
        int green = rand() % 256;
        int blue = rand() % 256;

        blockGroup->GroupColor = D3DCOLOR_ARGB(255, red, green, blue);

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
    case E_BLOCK_BTN_LATEST_DELETE:
    {
        if (m_nCurWorkingBlockGroupIndex != INVALIDE_VALUE)
        {
            if (m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints.size() > 0)
            {
                m_vecBlockGroups[m_nCurWorkingBlockGroupIndex]->vecPoints.pop_back();
            }
        }

        m_eBlockButtonState = E_BLOCK_BTN_PROGRESS;
    }
    break;
    case E_BLOCK_BTN_DELETE:
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
            if (g_pMapDataManager->GetObjectButtonState() == E_OBJ_TAB_BTN_RELOCATE ||
                g_pMapDataManager->GetObjectButtonState() == E_OBJ_TAB_BTN_REMOVE)
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
                for (int j = 0; j < m_vecBlockGroups[i]->vecPoints.size(); j++)
                {
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
                    else if (j == m_vecBlockGroups[i]->vecPoints.size() - 1)
                    {
                        g_pDevice->SetMaterial(&GREEN_MTRL);
                    }
                    else
                    {
                        g_pDevice->SetMaterial(&BLUE_MTRL);
                    }
                    m_SphereMesh->DrawSubset(0);

                    // ǥ���� ����
                    string text = to_string(j);
                    RenderSignPost(pos, 22, m_vecBlockGroups[i]->GroupColor, text);

                }

                // ���� �� �׸��� 
                D3DXMATRIXA16 matW;
                D3DXMatrixIdentity(&matW);
                g_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_NORMAL);
                g_pDevice->SetTransform(D3DTS_WORLD, &matW);

                int LineNum = (int)(m_vecBlockGroups[i]->vecPoints.size() - 1);
                if (LineNum > 0)
                {
                    g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, LineNum,
                        &m_vecBlockGroups[i]->vecPoints[0], sizeof(ST_PC_VERTEX));
                    //LineNum = 0;
                }

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
            Matrix4 world = m_matScale * m_matRotation*m_matTrans;
            m_vecObjects[m_nSelectedIndex]->SetCollision(m_isObjCollison);
            m_vecObjects[m_nSelectedIndex]->SetDestruction(m_isObjDestruction);
            m_vecObjects[m_nSelectedIndex]->SetEnemy(m_isObjEnemy);
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
    string fileKey = g_pMapDataManager->GetFileKey();
    string filePath = g_pMapDataManager->GetFilePath();
    string fileName = g_pMapDataManager->GetFileName();

    // ������Ʈ ����
    cMapObject* pMapObject = new cMapObject(fileName, filePath, fileName);
    // ������Ʈ ����(���ο��� �����Ʈ������ ���õ�)
    pMapObject->Setup(Vector3(m_fObjSize, m_fObjSize, m_fObjSize), Vector3(m_fObjRotX, m_fObjRotY, m_fObjRotZ), (*m_pPickPos));
    // ������Ʈ ���̵� ���� 
    pMapObject->SetId(m_nObjectMakeTotalNum++);
    pMapObject->SetKey(fileKey);
    pMapObject->SetFilePath(filePath);
    pMapObject->SetFileName(fileName);
    pMapObject->SetCollision(m_isObjCollison);
    pMapObject->SetDestruction(m_isObjDestruction);
    pMapObject->SetEnemy(m_isObjEnemy);
    m_vecObjects.push_back(pMapObject);
}

// ���콺 ���� ��ư�� Ŭ�� ���� �� �ߵ�
void cMapObjectTool::OnceLButtonDown(E_TAB_TYPE eTabType)
{
    if (eTabType == E_OBJECT_TAB)
    {
        // ������Ʈ �� ��ư ���¿� ���� ������Ʈ �б�
        switch (g_pMapDataManager->GetObjectButtonState())
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
                        m_isObjCollison = m_vecObjects[m_nSelectedIndex]->GetCollision();
                        m_isObjDestruction = m_vecObjects[m_nSelectedIndex]->GetDestruction();
                        m_isObjEnemy = m_vecObjects[m_nSelectedIndex]->GetEnemy();
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
    else
    {
        if (g_pMapDataManager->GetObjectButtonState() != E_OBJ_TAB_BTN_MAX)
        {

        }

        if (g_pMapDataManager->GetBlockButtonState() != E_BLOCK_BTN_MAX)
        {
            m_eBlockButtonState = E_BLOCK_BTN_END;
        }
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
    RECT rt = { 0, 100, 100, 150 };
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

    switch (g_pMapDataManager->GetObjectButtonState())
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

void cMapObjectTool::RenderSignPost(Vector3 pos, int size, Color color, string text)
{
    D3DXVECTOR3 screenPos = pos;
    D3DXMATRIXA16 matView, matProj, matVP;

    g_pDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

    D3DVIEWPORT9 vp;
    g_pDevice->GetViewport(&vp);
    D3DXMatrixIdentity(&matVP);
    matVP._11 = vp.Width / 2.0f;
    matVP._22 = -(vp.Height / 2.0f);
    matVP._33 = vp.MaxZ - vp.MinZ;
    matVP._41 = vp.X + vp.Width / 2.0f;
    matVP._42 = vp.Y + vp.Height / 2.0f;
    matVP._43 = vp.MinZ;

    D3DXVec3TransformCoord(&screenPos, &screenPos, &(matView * matProj * matVP));

    RECT rc;
    rc.left = (long)(screenPos.x - size / 2);
    rc.top = (long)(screenPos.y - 20.0f);
    rc.right = (long)(rc.left + size);
    rc.bottom = (long)(rc.top + size);

    vector<VertexRHWC> vecVertex;
    vecVertex.reserve(6);
    D3DXCOLOR innerColor = color;

    vecVertex.push_back(VertexRHWC(Vector4((float)rc.left, (float)rc.bottom, 0, 1), innerColor));
    vecVertex.push_back(VertexRHWC(Vector4((float)rc.left, (float)rc.top, 0, 1), innerColor));
    vecVertex.push_back(VertexRHWC(Vector4((float)rc.right, (float)rc.top, 0, 1), innerColor));
    vecVertex.push_back(VertexRHWC(Vector4((float)rc.left, (float)rc.bottom, 0, 1), innerColor));
    vecVertex.push_back(VertexRHWC(Vector4((float)rc.right, (float)rc.top, 0, 1), innerColor));
    vecVertex.push_back(VertexRHWC(Vector4((float)rc.right, (float)rc.bottom, 0, 1), innerColor));

    g_pDevice->SetFVF(VertexRHWC::FVF);
    g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &vecVertex[0], sizeof(VertexRHWC));

    // ��Ʈ��ġ����
    rc.left += 3;
    rc.top -= 4;

    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        text.c_str(),
        -1,
        &rc,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(255, 255, 255));
}

void cMapObjectTool::SaveByJson(json& jSave)
{
    json& innerRoot = jSave;
    for (int i = 0; i < m_vecObjects.size(); i++)
    {
        Vector3 rotXYZ = m_vecObjects[i]->GetRotationXYZ();
        Vector3 pos = m_vecObjects[i]->GetPositon();
        json object;
        object[OBJ_KEY] = m_vecObjects[i]->GetKey();
        object[OBJ_PATH] = m_vecObjects[i]->GetFilePath();
        object[OBJ_NAME] = m_vecObjects[i]->GetFileName();
        object[OBJ_COL] = (bool)m_vecObjects[i]->GetCollision();
        object[OBJ_DES] = (bool)m_vecObjects[i]->GetDestruction();
        object[OBJ_ENE] = (bool)m_vecObjects[i]->GetEnemy();
        object[OBJ_SCALE] = (float)m_vecObjects[i]->GetScale().x;
        object[OBJ_ROTX] = (float)rotXYZ.x;
        object[OBJ_ROTY] = (float)rotXYZ.y;
        object[OBJ_ROTZ] = (float)rotXYZ.z;
        object[OBJ_POSX] = (float)pos.x;
        object[OBJ_POSY] = (float)pos.y;
        object[OBJ_POSZ] = (float)pos.z;

        innerRoot[OBJ].push_back(object);
    }
    // BLOCK_GROUP
    for (int i = 0; i < m_vecBlockGroups.size(); i++)
    {
        json block_group;
        block_group[BG_NAME] = m_vecBlockGroups[i]->GroupName;
        block_group[BG_COLOR] = m_vecBlockGroups[i]->GroupColor;

        for (int j = 0; j < m_vecBlockGroups[i]->vecPoints.size(); j++)
        {
            json block;
            Vector3 pos = m_vecBlockGroups[i]->vecPoints[j].p;
            block[BG_PO_X] = pos.x;
            block[BG_PO_Y] = pos.y;
            block[BG_PO_Z] = pos.z;
            block_group[BG_POINT].push_back(block);
        }
        innerRoot[BG].push_back(block_group);
    }

    innerRoot[OBJ_SET][OBJ_OBJ_NUM] = (int)m_nObjectMakeTotalNum;
    innerRoot[OBJ_SET][OBJ_BLOCK_NUM] = (int)g_pMapDataManager->GetBlockMakeNum();

}

void cMapObjectTool::LoadByJson(string sFilePath, string sFileTitle)
{
    json json;
    ifstream i;
    string fullPath = sFilePath + "\\" + sFileTitle + ".json";
    i.open(fullPath.c_str());

    i >> json;
    i.close();

    // ���� �� ����Ʈ �ʱ�ȭ 
    ClearObjectNBlock();

    // Object
    for (int i = 0; i < json[OBJ].size(); i++)
    {
        string key = json[OBJ][i][OBJ_KEY];
        string path = json[OBJ][i][OBJ_PATH];
        string name = json[OBJ][i][OBJ_NAME];

        Vector3 scale;
        scale.z = scale.y = scale.x = (float)json[OBJ][i][OBJ_SCALE];

        Vector3 rot;
        rot.x = (float)json[OBJ][i][OBJ_ROTX];
        rot.y = (float)json[OBJ][i][OBJ_ROTY];
        rot.z = (float)json[OBJ][i][OBJ_ROTZ];

        Vector3 pos;
        pos.x = (float)json[OBJ][i][OBJ_POSX];
        pos.y = (float)json[OBJ][i][OBJ_POSY];
        pos.z = (float)json[OBJ][i][OBJ_POSZ];

        cMapObject* object = new cMapObject(key, path, name);

        object->Setup(scale, rot, pos);
        object->SetCollision((bool)json[OBJ][i][OBJ_COL]);
        object->SetDestruction((bool)json[OBJ][i][OBJ_DES]);
        object->SetEnemy((bool)json[OBJ][i][OBJ_ENE]);
        object->SetId(i);

        m_vecObjects.push_back(object);
    }

    // Block
    for (int i = 0; i < json[BG].size(); i++)
    {
        ST_BLOCK_GROUP* bgroup = new ST_BLOCK_GROUP;
        string name = json[BG][i][BG_NAME];
        bgroup->GroupName = name;
        g_pMapDataManager->GetBlockGroupListBox()->AddString(bgroup->GroupName.c_str());

        int red = rand() % 256;
        int green = rand() % 256;
        int blue = rand() % 256;

        bgroup->GroupColor = D3DCOLOR_ARGB(255, red, green, blue);

        for (int j = 0; j < json[BG][i][BG_POINT].size(); j++)
        {
            Vector3 pos;
            pos.x = (float)json[BG][i][BG_POINT][j][BG_PO_X];
            pos.y = (float)json[BG][i][BG_POINT][j][BG_PO_Y];
            pos.z = (float)json[BG][i][BG_POINT][j][BG_PO_Z];
            bgroup->vecPoints.push_back(ST_PC_VERTEX(pos, bgroup->GroupColor));
        }
        m_vecBlockGroups.push_back(bgroup);
    }

    int num = (int)json[OBJ_SET].size();

    if (num > 0)
    {
        // ���� ���� ���� �����ϱ� 
        int objectNum = (int)json[OBJ_SET][OBJ_OBJ_NUM];
        m_nObjectMakeTotalNum = objectNum;
        int blockNum = (int)json[OBJ_SET][OBJ_BLOCK_NUM];
        g_pMapDataManager->SetBlockMakeNum(blockNum);
    }
    else
    {
        int interval = 100;
        m_nObjectMakeTotalNum = interval;
        g_pMapDataManager->SetBlockMakeNum(interval);
    }
}

void cMapObjectTool::ClearObjectNBlock()
{
    // Object Vector ���� 
    if (!m_vecObjects.empty())
    {
        for (int i = 0; i < m_vecObjects.size(); i++)
        {
            SAFE_DELETE(m_vecObjects[i]);
        }
        m_vecObjects.clear();
    }
    g_pMapDataManager->GetObjListBox()->ResetContent();			 // Object list �ڽ��� �ִ� ������ ���� �����.

                                                                 // Block Group Vector ���� 
    if (!m_vecBlockGroups.empty())
    {
        for (int i = 0; i < m_vecBlockGroups.size(); i++)
        {
            SAFE_DELETE(m_vecBlockGroups[i]);
        }
        m_vecBlockGroups.clear();
    }
    g_pMapDataManager->GetBlockGroupListBox()->ResetContent();    // Object list �ڽ��� �ִ� ������ ���� �����.
}
