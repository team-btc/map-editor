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
	
	// 블록 관련 
	, m_eBlockButtonState(g_pMapDataManager->GetBlockButtonState())
	, m_SelectedBlockGroupName(g_pMapDataManager->GetSelectedBlockGroupName())
	, m_nCurWorkingBlockGroupIndex(INVALIDE_VALUE)
{}

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

    // 블록 벡터 지우기
    if (!m_vecBlockGroups.empty())
    {
        for (int i = 0; i < m_vecBlockGroups.size(); i++)
        {
            SAFE_DELETE(m_vecBlockGroups[i]);
        }
    }

    // 테스트 메쉬 해제
	SAFE_RELEASE(m_SphereMesh);
}

HRESULT cMapObjectTool::Setup()
{
    // 매쉬 초기화 
	D3DXCreateSphere(g_pDevice, 1, 10, 10, &m_SphereMesh, NULL);
    
    // 매트릭스 초기화 
    D3DXMatrixIdentity(&m_matScale);
    D3DXMatrixIdentity(&m_matRotation);
    D3DXMatrixIdentity(&m_matTrans);
	return S_OK;
}

HRESULT cMapObjectTool::Update()
{
    // 오브젝트 탭 버튼 상태에 따른 업데이트 분기
    switch (g_pMapDataManager->GetObjectTabButtonState())
    {
        case E_OBJ_TAB_BTN_LOCATE: // 오브젝트 배치
        {
            if (!m_pFollowObject)  // 마우스 따라다니는 으보젝트가 NULL 일 때 
            {
                SetFollowObject(); // 마우스 따라다니는 오브젝트 세팅
            }
            else  // 마우스 따라다니는 오브젝트가 있을 때
            {
                UpdateFollowObject();  // 마우스 따라다니는 오브젝트 매트릭스 갱신 
            }
        } 
        break;
        case E_OBJ_TAB_BTN_RELOCATE: // 오브젝트 재배치
        {
            if (m_nSelectedIndex != INVALIDE_VALUE)  // 재배치 할 오브젝트가 선택되었을때
            {
                UpdateFollowObject();  // 마우스 따라다니는 재배치할 오브젝트 매트릭스 갱신 
            }
        }
        break;
    }

    // 오브젝트 탭 버튼 상태가 배치가 아닐 때 다른 버튼을 누르면 따라다니는 녀석 없애기
    if (g_pMapDataManager->GetObjectTabButtonState() != E_OBJ_TAB_BTN_LOCATE)
    {
        if (m_pFollowObject)       // 따라다니는 오브젝트가 있을 경우  
        {
            DeleteFollowObject();  // 오브젝트 지우기 
        }
    }

    // 블록 배치 
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
    // 오브젝트들 그리기
    if (!m_vecObjects.empty())  
	{
		for (int i = 0; i < m_vecObjects.size(); i++)
		{			
            // 재배치 || 삭제 모드일 때만 피킹 충돌 범위 보여주기 
            if (g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_RELOCATE
                || g_pMapDataManager->GetObjectTabButtonState() == E_OBJ_TAB_BTN_REMOVE)
            {
                g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
                g_pDevice->SetTransform(D3DTS_WORLD, &m_vecObjects[i]->GetWorldMatrix());
                m_SphereMesh->DrawSubset(0);
                g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            }
            // 오브젝트 그리기 
            m_vecObjects[i]->Render();
		}
	}

    // 블록 그리기 
    if (!m_vecBlockGroups.empty())
    {
        for (int i = 0; i < m_vecBlockGroups.size(); i++)
        {
            if (!m_vecBlockGroups[i]->vecPoints.empty())
            {
           
                for(int j = 0; j < m_vecBlockGroups[i]->vecPoints.size(); j++)
                {
                    g_pDevice->LightEnable(0, true);
                    // Sphere mesh 그리는 부분 
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

                // 연결 선 그리기 
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

    if (m_pFollowObject) // 마우스 따라다니는 오브젝트 그리기
    {
        RenderFollowObject();
    }

    if (DEBUG_RENDER)   // 디버그 랜더 
    {
        DebugTestRender();
    }

	return S_OK;
}

// 마우스 따라다니는 오브젝트 생성
void cMapObjectTool::SetFollowObject()
{
    // NULL이 아닐때만 생성 되게 
    if (!m_pFollowObject)
    {
        m_pFollowObject = new cMapObject(g_pMapDataManager->GetFileName(), g_pMapDataManager->GetFilePath(), g_pMapDataManager->GetFileName());
        m_pFollowObject->Setup(Vector3(m_fObjSize, m_fObjSize, m_fObjSize), Vector3(m_fObjRotX, m_fObjRotY, m_fObjRotZ), *m_pPickPos);    
    }
}

// 마우스 따라다니는 오브젝트 갱신
void cMapObjectTool::UpdateFollowObject()
{
    // 내부 메트릭스 갱신
    UpdateMatrix();

    if (m_pFollowObject)  // 배치 모드 일때
    {
        m_pFollowObject->SetWorldMatrix(m_matScale* m_matRotation * m_matTrans);
    }
    else  // 재배치 모드 일때
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

// 마우스 따라니는 오브젝트 그리기
void cMapObjectTool::RenderFollowObject()
{
    // 포인터가 값이 있을때 
    if (m_pFollowObject)
    {
        g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        m_pFollowObject->Render();

        g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    }
}

// 마우스 따라다니는 오브젝트 삭제 
void cMapObjectTool::DeleteFollowObject()
{
	SAFE_DELETE(m_pFollowObject);
}

// 내부 매트릭스 갱신
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

// 오브젝트 생성(피킹 된 지점에 생성됨)
void cMapObjectTool::AddObject(Vector3 vPickPos)
{
    string filePath = g_pMapDataManager->GetFilePath();
    string fileName = g_pMapDataManager->GetFileName();

    // 오브젝트 생성
    cMapObject* pMapObject = new cMapObject(fileName, filePath, fileName);
    // 오브젝트 세팅(내부에서 월드매트릭스가 세팅됨)
    pMapObject->Setup(Vector3(m_fObjSize, m_fObjSize, m_fObjSize), Vector3(m_fObjRotX, m_fObjRotY, m_fObjRotZ), (*m_pPickPos));
    // 오브젝트 아이디 세팅 
    pMapObject->SetId(m_nObjectMakeTotalNum++);
    m_vecObjects.push_back(pMapObject);
}

// 마우스 왼쪽 버튼을 클릭 했을 때 발동
void cMapObjectTool::OnceLButtonDown()
{
    // 오브젝트 탭 버튼 상태에 따른 업데이트 분기
    switch (g_pMapDataManager->GetObjectTabButtonState())
    {
    case E_OBJ_TAB_BTN_LOCATE:       // 오브젝트 배치
    {
        if (m_pPickPos)              // 피킹 위치의 주소가 있을때만 
        {
            AddObject(*m_pPickPos);  // 오브젝트 추가하기 
        }
    }
    break;
    case E_OBJ_TAB_BTN_RELOCATE:     // 오브젝트 재배치
    {
        if (!m_vecObjects.empty())   // 벡터가 비워있으면 굳이 재배치 검사를 할 필요가 없음
        {
            if (m_nSelectedIndex == INVALIDE_VALUE)
            {
                int nId = PickObject();    // 오브젝트와 피킹 검사를 하여 오브젝트의 아이디 가져오기
                if (nId != INVALIDE_VALUE) // INVALIDE_VALUE (-1)일 경우는 피킹 된 오브젝트가 없는 것
                {
                    m_nSelectedIndex = FindObject(nId);  // id를 통해 오브젝트 벡터에서 해당 인덱스를 가져오기 
                    // 탭의 설정들이 해당되는 녀석의 정보로 바뀌게
                    Vector3 RotXYZ = m_vecObjects[m_nSelectedIndex]->GetRotationXYZ();
                    m_fObjSize = m_vecObjects[m_nSelectedIndex]->GetScale().x;
                    m_fObjRotX = RotXYZ.x;
                    m_fObjRotY = RotXYZ.y;
                    m_fObjRotZ = RotXYZ.z;
                }
            }
            else
            {
                m_nSelectedIndex = INVALIDE_VALUE;     // 배치가 끝나면 선택한 오브젝트를 해제 
            }
        }
    }
    break;
    case E_OBJ_TAB_BTN_REMOVE:    // 오브젝트 삭제 
    {
        if (!m_vecObjects.empty())    //벡터에 오브젝트가 있을때만 작동하게 
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

// 마우스 왼쪽 버튼을 계속 누르고 있을 때 발동
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
            //Ray 구 충돌 일때 
            float radius = m_vecObjects[i]->GetScale().x; // 그냥 스케일을 반지름으로 잡고 하자 
            if (CollideRayNCircle(ray, m_vecObjects[i]->GetPositon(), radius))
            {
                return m_vecObjects[i]->GetId();
            }
        }
    }
    return INVALIDE_VALUE;
}

// 오브젝트 아이디로 
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

// 구 충돌 안씀
bool cMapObjectTool::CollideRound(Vector3 vMyPos, float fMyRadius, Vector3 vTargetPos, float fTargetRadius)
{
    D3DXVECTOR3 v = vTargetPos - vMyPos;
    float length = D3DXVec3Length(&v);

    if (length <= fTargetRadius + fMyRadius) // 충돌
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 디버그 랜더
void cMapObjectTool::DebugTestRender()
{
    RECT rt = { 0, 100, 100, 150};
    string s;

    rt = { 0, 150, 100, 200 };
    s = "선택된 인덱스 : ";
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
        s = "로케이션 버튼 눌림";
        break;
    case E_OBJ_TAB_BTN_RELOCATE:
        s = "리로케이션 버튼 눌림";
        break;
    case E_OBJ_TAB_BTN_REMOVE:
        s = "리무브 버튼 눌림";
        break;
    case E_OBJ_TAB_BTN_MAX:
        s = "캔슬 버튼 눌림";
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
