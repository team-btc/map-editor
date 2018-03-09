#include "stdafx.h"
#include "cMapTerrainTool.h"


cMapTerrainTool::cMapTerrainTool()
    : m_stTerrainBrushInfo(g_pMapDataManager->GetTerUpDown()
        , g_pMapDataManager->GetTerEditType()
        , g_pMapDataManager->GetTerBrushType()
        , g_pMapDataManager->GetTerEditPower()
        , g_pMapDataManager->GetTerEditHeight()
        , g_pMapDataManager->GetTerBrushSize())
    , m_stTextureBrushInfo(g_pMapDataManager->GetCurrTexType()
        , g_pMapDataManager->GetWalkable()
        , g_pMapDataManager->GetTexDensity()
        , g_pMapDataManager->GetTexBrushSize()
        , g_pMapDataManager->GetTexBrushDenSize()
        , g_pMapDataManager->GetTexBrushDensity())
    , m_stWaterInfo(g_pMapDataManager->GetWaterHeight()
        , g_pMapDataManager->GetWaterUVSpeed()
        , g_pMapDataManager->GetWaterWaveHeight()
        , g_pMapDataManager->GetWaterHeightSpeed()
        , g_pMapDataManager->GetWaterFrequency()
        , g_pMapDataManager->GetWaterTransparent())
    , m_pMesh(NULL)
    , m_vPickPos(NULL)
    , m_pTextureShader(NULL)
    //, m_pWaveShader(NULL)
    , m_fPassedEditTime(0.0f)
{
}


cMapTerrainTool::~cMapTerrainTool()
{
	SAFE_RELEASE(m_pMesh);
    SAFE_DELETE(m_pTextureShader);
    //SAFE_DELETE(m_pWaveShader);
}

HRESULT cMapTerrainTool::Setup()
{
    //// 메인 라이트
    //D3DXVECTOR3 dir(1.0f, -1.0f, 0.0f);
    //D3DXVec3Normalize(&dir, &dir);
    //D3DLIGHT9 stLight = InitDirectional(&dir, &WHITE);
    //g_pDevice->SetLight(0, &stLight);

    m_pTextureShader = new cTextureShader;
    m_pTextureShader->SetTexture();

    m_stTerrainBrushInfo.eUpDown = E_UP;
    m_stTerrainBrushInfo.eEditType = E_TER_EDIT_BEGIN;
    m_stTerrainBrushInfo.eBrushType = E_TER_BRUSH_SMOOTH;
    m_stTerrainBrushInfo.fPower = 3.0f;
    m_stTerrainBrushInfo.fEditHeight = g_pMapDataManager->GetDefHeight();
    m_stTerrainBrushInfo.fBrushSize = 30.0f;

    //m_pWaveShader = new cWaveShader;
    //m_pWaveShader->SetMesh(m_pMesh);
    //m_eTerraingEditType = E_TER_EDIT_BEGIN;

    m_stTextureBrushInfo.m_eCurrTextureType = g_pMapDataManager->GetDefGroundType();
    m_stTextureBrushInfo.m_isWalkable = g_pMapDataManager->GetDefWalkable();
    m_stTextureBrushInfo.fTextureDensity = 50.0f;
    m_stTextureBrushInfo.fTextureBrushSize = 5.0f;
    m_stTextureBrushInfo.fTextureBrushSpraySize = 10.0f;
    //m_stTextureBrushInfo.fTexturBrushDensity = 1.0f;

    m_stWaterInfo.fHeight = g_pMapDataManager->GetDefHeight();

    m_stWaterInfo.fUVSpeed = 0.01f;
    m_stWaterInfo.fWaveHeight = 0.6f;
    m_stWaterInfo.fHeightSpeed = 2.4f;
    m_stWaterInfo.fFrequency = 7.0f;
    m_stWaterInfo.fTransparent = 0.6f;
    
	return S_OK;
}

HRESULT cMapTerrainTool::Update()
{
    Vector4 v(m_vPickPos->x / m_ptMapSize.x , 0, m_vPickPos->z / m_ptMapSize.y, 1);

    if (g_pMapDataManager->GetTabType() == E_TERRAIN_TAB)
    {
        m_pTextureShader->SetBrush(v, m_stTerrainBrushInfo.fBrushSize / m_ptMapSize.x,
            m_stTerrainBrushInfo.fBrushSize / m_ptMapSize.x,
            0.1f);
    }
    else if (g_pMapDataManager->GetTabType() == E_TEXTURE_TAB)
    {
        m_pTextureShader->SetBrush(v, m_stTextureBrushInfo.fTextureBrushSize / m_ptMapSize.x,
            m_stTextureBrushInfo.fTextureBrushSpraySize / m_ptMapSize.x,
            m_stTextureBrushInfo.fTextureDensity * 0.01f);
    }
    //m_pWaveShader->SetShader(m_stWaterInfo.fHeight, m_stWaterInfo.fWaveHeight, m_stWaterInfo.fHeightSpeed, m_stWaterInfo.fUVSpeed, m_stWaterInfo.fFrequency, m_stWaterInfo.fTransparent);
	// 지형 높이 증가
	if (g_pKeyManager->isOnceKeyDown('U'))
	{

	}
	// 지형 높이 감소
	else if (g_pKeyManager->isOnceKeyDown('D'))
	{

	}
	// 텍스쳐 입히기
	else if (g_pKeyManager->isOnceKeyDown('T'))
	{

	}
	// 기본 텍스쳐로 변경 
	else if (g_pKeyManager->isOnceKeyDown('E'))
	{

	}
	// 와이어 프레임 출력
	else if (g_pKeyManager->isOnceKeyDown('W'))
	{

	}
	// 저장
	else if (g_pKeyManager->isOnceKeyDown('S'))
	{

	}
	// 로드
	else if (g_pKeyManager->isOnceKeyDown('L'))
	{
		
	}
	// 파일 경로
	else if (g_pKeyManager->isOnceKeyDown('1'))
	{

	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{

	}
	else if (g_pKeyManager->isOnceKeyDown('3'))
	{

	}

	return S_OK;
}

HRESULT cMapTerrainTool::Render()
{
	Matrix4 matW;
	D3DXMatrixIdentity(&matW);

	g_pDevice->SetTransform(D3DTS_WORLD, &matW);
	g_pDevice->SetMaterial(&WHITE_MTRL);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
    //g_pDevice->LightEnable(0, true);
    g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); 
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	// 메쉬로 그리기
	g_pDevice->SetTexture(0, (LPTEXTURE9)g_pTextureManager->GetTexture("default"));
    m_pMesh->DrawSubset(0);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

    RendBrush();
    //m_pTextureShader->Render();

	return S_OK;
}

// 마우스 왼쪽 버튼 클릭 했을 때 발동
void cMapTerrainTool::OnceLButtonDown(E_TAB_TYPE eTabType)
{
    // 지형탭
    if (eTabType == E_TERRAIN_TAB)
    {
        // 초기화
        m_fPassedEditTime = 0.0f;
    }

    // 텍스쳐탭
    else if (eTabType == E_TEXTURE_TAB)
    {

    }
}

// 마우스 왼쪽 버튼 계속 누를 때 발동
void cMapTerrainTool::StayLButtonDown(E_TAB_TYPE eTabType)
{
    m_pTextureShader->SetType(m_stTextureBrushInfo.m_eCurrTextureType);
    // 지형탭
    if (eTabType == E_TERRAIN_TAB)
    {
        // 마우스 위치에 따른 면정보 가져오기
        if (m_vPickPos)
        {
            // 선택된 면정보 인덱스
            m_vecSelVertex.clear();
            m_vecSelVertex = GetVertexInBrush(*m_vPickPos, m_stTerrainBrushInfo.fBrushSize);

            // 지형 편집하기
            EditTerrain();
        }
    }

    // 텍스쳐탭
    else if (eTabType == E_TEXTURE_TAB)
    {
        m_pTextureShader->Update();
       // DrawAlphaMap();
    }
}

// 크기 설정한 맵 생성 (x사이즈, z사이즈, 지형 타입)
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType, IN float fHeight, IN float isWalkable)
{
    // 가로 세로 사이즈 계산 후 맵 만들기
    m_ptMapSize.x = m_ptMapSize.y = (eMapSize + 1) * 64;

    int nSizeX = m_ptMapSize.x;
    int nSizeZ = m_ptMapSize.y;

	// 예외처리
	if (nSizeX <= 0 || nSizeZ < 0 || eGroundType < E_GROUND_TYPE_BEGIN || eGroundType >= E_GROUND_TYPE_MAX)
	{
		return E_INVALIDARG;
	}

    // ex) 512 * 512
	//   ofstream c;
	//   c.open("NewMap.raw");
	//c << (char)vec.y;

	// 버텍스 벡터
	for (int n = 0; n < (nSizeX + 1) * (nSizeZ + 1); ++n)
	{
		Vector3 vec = Vector3(n % (nSizeZ + 1), fHeight, n / (nSizeZ + 1));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vec, Vector3(0, 1, 0), Vector2((n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
	}

    // 인덱스 벡터, 면정보 벡터
    //   1 3
    //   0 2
    //  0 , 1 , 2,  // 2 , 1 , 3 순서!!
    for (DWORD z = 0; z < nSizeZ; ++z)
    {
        for (DWORD x = 0; x < nSizeX; ++x)
        {
			// == 인덱스 벡터 ==
            DWORD _0 = (z * (nSizeZ + 1)) + x;
            DWORD _1 = ((z + 1) * (nSizeZ + 1)) + x;
			DWORD _2 = (z * (nSizeZ + 1)) + (x + 1);
            DWORD _3 = (z + 1) * (nSizeZ + 1) + (x + 1);

            m_vecVertexIndex.push_back(_0);
            m_vecVertexIndex.push_back(_1);
            m_vecVertexIndex.push_back(_2);
            m_vecVertexIndex.push_back(_2);
            m_vecVertexIndex.push_back(_1);
            m_vecVertexIndex.push_back(_3);

			// == 면정보 벡터 ==
			// 하단 삼각형
			ST_TERRAIN_FACE_INFO stFace1;

			stFace1.eGroundType[0] = eGroundType;
			stFace1.fBlending[0] = 1.0f;
			stFace1.isWalkable = true;
			stFace1.eObjProp = E_OBJ_NONE;

			// 면에 포함되는 삼각형 버텍스 정보 연결하기
			stFace1.dVertexIndedArr[0] = _0;
			stFace1.dVertexIndedArr[1] = _1;
			stFace1.dVertexIndedArr[2] = _2;

			m_vecFaceInfo.push_back(stFace1);

			// 상단 삼각형
			ST_TERRAIN_FACE_INFO stFace2;

			stFace2.eGroundType[0] = eGroundType;
			stFace2.fBlending[0] = 1.0f;
			stFace2.isWalkable = true;
			stFace2.eObjProp = E_OBJ_NONE;

			// 면에 포함되는 삼각형 버텍스 정보 연결하기
			stFace2.dVertexIndedArr[0] = _2;
			stFace2.dVertexIndedArr[1] = _1;
			stFace2.dVertexIndedArr[2] = _3;

			m_vecFaceInfo.push_back(stFace2);
        }
    }

    // 매쉬 정보 셋팅
    // == 매쉬 생성, 기록, 최적화
    // 생성
    D3DXCreateMeshFVF(m_vecVertexIndex.size() / 3, m_vecPNTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PNT_VERTEX::FVF, g_pDevice, &m_pMesh);

    // 버텍스 버퍼 기록
    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);
    memcpy(pV, &m_vecPNTVertex[0], m_vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
    m_pMesh->UnlockVertexBuffer();

    // 인덱스 버퍼 기록
    DWORD* pI = NULL;
    m_pMesh->LockIndexBuffer(NULL, (LPVOID*)&pI);
    memcpy(pI, &m_vecVertexIndex[0], m_vecVertexIndex.size() * sizeof(DWORD));
    m_pMesh->UnlockIndexBuffer();

    // 속성 버퍼 기록
    DWORD* pA = NULL;
    m_pMesh->LockAttributeBuffer(NULL, &pA);
    for (int i = 0; i < m_vecVertexIndex.size() / 3; ++i) // 페이스별로 하나씩 기록
        pA[i] = (DWORD) 0;
    m_pMesh->UnlockAttributeBuffer();

    // 메쉬 최적화 : 버텍스 개수 만큼 인접정보를 담을 공간을 확보
    vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);

    m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
        &vecAdjBuf[0], 0, 0, 0);
   

    m_pTextureShader->SetMesh(m_pMesh);

	return S_OK;

}

// 지형 편집
void cMapTerrainTool::EditTerrain()
{
    switch (m_stTerrainBrushInfo.eEditType)
    {
    case E_TER_EDIT_HEIGHT:
    {
        m_fPassedEditTime += g_pTimerManager->GetDeltaTime();

        // 편집 시간이 되었을 때 함수 발동
        if (m_fPassedEditTime >= EDIT_DURATION_TIME)
        {
            m_fPassedEditTime = 0.0f;
            EditHeight();
        }
    }
        break;
    case E_TER_EDIT_RETURN:
    {
        m_fPassedEditTime += g_pTimerManager->GetDeltaTime();

        // 편집 시간이 되었을 때 함수 발동
        if (m_fPassedEditTime >= EDIT_DURATION_TIME)
        {
            m_fPassedEditTime = 0.0f;
            ReturnHeight();
        }
    }
        break;
    case E_TER_EDIT_FIXED_HEIGHT:
    {
        m_fPassedEditTime += g_pTimerManager->GetDeltaTime();

        // 편집 시간이 되었을 때 함수 발동
        if (m_fPassedEditTime >= EDIT_DURATION_TIME)
        {
            m_fPassedEditTime = 0.0f;
            FixedHeight();
        }
    }
        break;
    case E_TER_EDIT_FLAT:
    {
        SetFlat();
    }
        break;
    case E_TER_EDIT_TRIM:
    {
        m_fPassedEditTime += g_pTimerManager->GetDeltaTime();

        // 편집 시간이 되었을 때 함수 발동
        if (m_fPassedEditTime >= EDIT_DURATION_TIME)
        {
            m_fPassedEditTime = 0.0f;
            TrimHeight();
        }
    }
    break;
    case E_TER_EDIT_RESET:
    {
        ResetHeight();
    }
    break;
    }
}

// 지형 높이 편집
void cMapTerrainTool::EditHeight()
{
    switch (m_stTerrainBrushInfo.eUpDown)
    {
    case E_UP:
    {
        // 편집할 버텍스 로드
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // 픽킹 지점과 가장 가까운거리에 있는 버텍스 인덱스 찾아오기
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // 센터높이 셋팅
        float fCenterHeight = pEditV[nNearIndex].p.y + m_stTerrainBrushInfo.fPower;

        // 255보다 크면 고정
        if (fCenterHeight > 255)
        {
            fCenterHeight = 255;
        }

        // 기준 높이
        float fBaseHeight;
        // 센터 높이가 기본 높이보다 높으면
        if (fCenterHeight > g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // 평지의높이가 기본 높이보다 낮으면
        else
        {
            fBaseHeight = 0;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // 버텍스와 픽킹 지점과의 거리(y값은 제외)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // 기준높이와 센터높이의 차이값
            float fHeightDiff = fCenterHeight - fBaseHeight;

            float fRatio;           // 비율
            float fHeightResult;    // 설정되어야 할 높이값

            // == 부드러운 타입의 브러쉬면 ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fBaseHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
            }
            // == 날카로운 타입의 브러쉬면 ==
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fBaseHeight + (fHeightDiff * fRatio);
            }

            // 설정될 높이가 기존의 높이보다 높을 때만 높이 갱신
            if (pEditV[m_vecSelVertex[i]].p.y < fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // 갱신 했을 때만 노말(법선)값 바꾸기
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // 높이가 255를 넘으면 고정
                if (pEditV[m_vecSelVertex[i]].p.y > 255)
                {
                    pEditV[m_vecSelVertex[i]].p.y = 255;
                }
            }
        }

        m_pMesh->UnlockVertexBuffer();
    }
    break;

    case E_DOWN:
    {
        // 편집할 버텍스 로드
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // 픽킹 지점과 가장 가까운거리에 있는 버텍스 인덱스 찾아오기
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // 센터높이 설정 (y값 낮추기)
        float fCenterHeight = pEditV[nNearIndex].p.y - m_stTerrainBrushInfo.fPower;

        // 기준 높이
        float fBaseHeight;
        // 센터 높이가 기본 높이보다 낮으면
        if (fCenterHeight < g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // 평지의높이가 기본 높이보다 높으면
        else
        {
            fBaseHeight = 255;
        }

        // 0보다 크면 고정
        if (fCenterHeight < 0)
        {
            fCenterHeight = 0;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // 버텍스와 픽킹 지점과의 거리(y값은 제외)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // 기준높이와 센터높이의 차이값
            float fHeightDiff = fBaseHeight - fCenterHeight;

            float fRatio;           // 비율
            float fHeightResult;    // 설정되어야 할 높이값

            // == 부드러운 타입의 브러쉬면 ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fCenterHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
            }
            // == 날카로운 타입의 브러쉬면 ==
            else
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fCenterHeight + (fHeightDiff * fRatio);
            }

            // 설정될 높이가 기존의 높이보다 낮을 때만 높이 갱신
            if (pEditV[m_vecSelVertex[i]].p.y > fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // 갱신 했을 때만 노말(법선)값 바꾸기
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // 높이가 0을 넘으면 고정
                if (pEditV[m_vecSelVertex[i]].p.y < 0)
                {
                    pEditV[m_vecSelVertex[i]].p.y = 0;
                }
            }
        }

        m_pMesh->UnlockVertexBuffer();
    }
    break;
    }
}

// 지형 높이 되돌리기
void cMapTerrainTool::ReturnHeight()
{
    switch (m_stTerrainBrushInfo.eUpDown)
    {
    case E_UP:
    {
        // 편집할 버텍스 로드
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // 픽킹 지점과 가장 가까운거리에 있는 버텍스 인덱스 찾아오기
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // 센터높이 셋팅
        float fCenterHeight = pEditV[nNearIndex].p.y - m_stTerrainBrushInfo.fPower;

        // 센터 높이가 기본 높이보다 낮으면 리턴
        if (fCenterHeight < g_pMapDataManager->GetDefHeight())
        {
            return;
        }

        // 기준 높이
        float fBaseHeight = g_pMapDataManager->GetDefHeight();

        // 기본 조정 높이
        float fDefaultPlusHeight = m_stTerrainBrushInfo.fPower;

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // 버텍스와 픽킹 지점과의 거리(y값은 제외)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));

            float fRatio;               // 비율
            float fHeightResult;        // 조정되어야 할 높이값

            // == 부드러운 타입의 브러쉬면 ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fDefaultPlusHeight * ((cosf(fRatio * PI) + 1.0f) * 0.5f); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
            }
            // == 날카로운 타입 브러쉬면 == 
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fDefaultPlusHeight * fRatio;
            }

            // 높이 갱신
            pEditV[m_vecSelVertex[i]].p.y -= fHeightResult;

            // 노말(법선)값 바꾸기
            ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                
            // 설정된 높이가 기준 높이보다 낮으면 고정
            if (pEditV[m_vecSelVertex[i]].p.y < fBaseHeight)
            {
                pEditV[m_vecSelVertex[i]].p.y = fBaseHeight;
            }
        }

        m_pMesh->UnlockVertexBuffer();
    }
    break;

    case E_DOWN:
    {
        // 편집할 버텍스 로드
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // 픽킹 지점과 가장 가까운거리에 있는 버텍스 인덱스 찾아오기
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // 센터높이 셋팅
        float fCenterHeight = pEditV[nNearIndex].p.y + m_stTerrainBrushInfo.fPower;

        // 센터 높이가 기본 높이보다 높으면 리턴
        if (fCenterHeight > g_pMapDataManager->GetDefHeight())
        {
            return;
        }

        // 기준 높이
        float fBaseHeight = g_pMapDataManager->GetDefHeight();

        // 기본 조정 높이
        float fDefaultPlusHeight = m_stTerrainBrushInfo.fPower;

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // 버텍스와 픽킹 지점과의 거리(y값은 제외)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));

            float fRatio;           // 비율
            float fHeightResult;    // 조정되어야 할 높이값

            // == 부드러운 타입 브러쉬면 == 
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fDefaultPlusHeight * ((cosf(fRatio * PI) + 1.0f) * 0.5f); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
            }

            // == 날카로운 타입 브러쉬면 ==
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fDefaultPlusHeight * fRatio;
            }

            // 높이 갱신
            pEditV[m_vecSelVertex[i]].p.y += fHeightResult;

            // 노말(법선)값 바꾸기
            ChangeNormalValue(m_vecSelVertex[i], &pEditV);

            // 설정된 높이가 기준 높이보다 높으면 고정
            if (pEditV[m_vecSelVertex[i]].p.y > fBaseHeight)
            {
                pEditV[m_vecSelVertex[i]].p.y = fBaseHeight;
            }
        }

        m_pMesh->UnlockVertexBuffer();
    }
    break;
    }
}

// 고정 지형 만들기
void cMapTerrainTool::FixedHeight()
{
    switch (m_stTerrainBrushInfo.eUpDown)
    {
    case E_UP:
    {
        // 편집할 버텍스 로드
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // 센터높이 셋팅
        float fCenterHeight = m_stTerrainBrushInfo.fEditHeight;
        
        // 기준 높이
        float fBaseHeight;
        // 센터 높이가 기본 높이보다 높으면
        if (fCenterHeight > g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // 평지의높이가 기본 높이보다 낮으면
        else
        {
            fBaseHeight = 0;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // 버텍스와 픽킹 지점과의 거리(y값은 제외)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // 기준높이와 센터높이의 차이값
            float fHeightDiff = fCenterHeight - fBaseHeight;

            float fRatio;           // 비율
            float fHeightResult;    // 설정되어야 할 높이값

            // == 부드러운 타입의 브러쉬면 ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fBaseHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
            }
            // == 날카로운 타입의 브러쉬면 ==
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fBaseHeight + (fHeightDiff * fRatio);
            }

            // 설정될 높이가 기존의 높이보다 높을 때만 높이 갱신
            if (pEditV[m_vecSelVertex[i]].p.y < fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // 갱신 했을 때만 노말(법선)값 바꾸기
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // 높이가 255를 넘으면 고정
                if (pEditV[m_vecSelVertex[i]].p.y > 255)
                {
                    pEditV[m_vecSelVertex[i]].p.y = 255;
                }
            }
        }

        m_pMesh->UnlockVertexBuffer();
    }
    break;

    case E_DOWN:
    {
        // 편집할 버텍스 로드
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // 센터높이 설정
        float fCenterHeight = m_stTerrainBrushInfo.fEditHeight;

        // 기준 높이
        float fBaseHeight;
        // 센터 높이가 기본 높이보다 낮으면
        if (fCenterHeight < g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // 평지의높이가 기본 높이보다 높으면
        else
        {
            fBaseHeight = 255;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // 버텍스와 픽킹 지점과의 거리(y값은 제외)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // 기준높이와 센터높이의 차이값
            float fHeightDiff = fBaseHeight - fCenterHeight;

            float fRatio;           // 비율
            float fHeightResult;    // 설정되어야 할 높이값

            // == 부드러운 타입의 브러쉬면 ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fCenterHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
            }
            // == 날카로운 타입의 브러쉬면 ==
            else
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fCenterHeight + (fHeightDiff * fRatio);
            }

            // 설정될 높이가 기존의 높이보다 낮을 때만 높이 갱신
            if (pEditV[m_vecSelVertex[i]].p.y > fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // 갱신 했을 때만 노말(법선)값 바꾸기
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // 높이가 0을 넘으면 고정
                if (pEditV[m_vecSelVertex[i]].p.y < 0)
                {
                    pEditV[m_vecSelVertex[i]].p.y = 0;
                }
            }
        }

        m_pMesh->UnlockVertexBuffer();
    }
    break;
    }
}

// 평지 셋팅하기
void cMapTerrainTool::SetFlat()
{
    // 편집할 버텍스 로드
    ST_PNT_VERTEX* pEditV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

    for (int i = 0; i < m_vecSelVertex.size(); ++i)
    {
        // Up 모드 일 때 (올리는 평지 만들 때)
        if (m_stTerrainBrushInfo.eUpDown == E_UP)
        {
            // 설정될 높이가 기존의 높이보다 높을 때만 높이 갱신
            if (pEditV[m_vecSelVertex[i]].p.y < m_stTerrainBrushInfo.fEditHeight)
            {
                pEditV[m_vecSelVertex[i]].p.y = m_stTerrainBrushInfo.fEditHeight;
                // 갱신 했을 때만 노말(법선)값 바꾸기
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
            }
        }
        // Down 모드 일 때 (내리는 평지 만들 때)
        else
        {
            // 설정될 높이가 기존의 높이보다 낮을 때만 높이 갱신
            if (pEditV[m_vecSelVertex[i]].p.y > m_stTerrainBrushInfo.fEditHeight)
            {
                pEditV[m_vecSelVertex[i]].p.y = m_stTerrainBrushInfo.fEditHeight;
                // 갱신 했을 때만 노말(법선)값 바꾸기
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
            }
        }
    }

    m_pMesh->UnlockVertexBuffer();
}

// 지형 다듬기
void cMapTerrainTool::TrimHeight()
{
    // 편집할 버텍스 로드
    ST_PNT_VERTEX* pEditV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

    for (int i = 0; i < m_vecSelVertex.size(); ++i)
    {
        int nCount = 0;
        float fSumY = 0;

        /* 검사 순서 : 숫자대로
        2 === 3 === 4
        | \   | \   |
        |  \  |   \ |
        1 === @ === 5
        | \   | \   |
        |  \  |   \ |
        8 === 7 === 6
        */

        // 좌측 버텍스 검사
        if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) > 0)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] - 1].p.y;
            // 상단 버텍스 검사
            if (m_vecSelVertex[i] < (m_ptMapSize.x + 1) * m_ptMapSize.y)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] + (m_ptMapSize.x + 1) - 1].p.y;
            }
        }
        // 상단 버텍스 검사
        if (m_vecSelVertex[i] < (m_ptMapSize.x + 1) * m_ptMapSize.y)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] + (m_ptMapSize.x + 1)].p.y;
            // 우측 버텍스 검사
            if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) != m_ptMapSize.x)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] + (m_ptMapSize.x + 1) + 1].p.y;
            }
        }
        // 우측 버텍스 검사
        if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) != m_ptMapSize.x)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] + 1].p.y;
            // 하단 버텍스 검사
            if (m_vecSelVertex[i] / (m_ptMapSize.x + 1) > 0)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] - (m_ptMapSize.x + 1) + 1].p.y;
            }
        }
        // 하단 버텍스 검사
        if (m_vecSelVertex[i] / (m_ptMapSize.x + 1) > 0)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] - (m_ptMapSize.x + 1)].p.y;
            // 좌측 버텍스 검사
            if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) > 0)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] - (m_ptMapSize.x + 1) - 1].p.y;
            }
        }

        // 평균 값으로 Y값 셋팅
        if (nCount != 0)
        {
            pEditV[m_vecSelVertex[i]].p.y = fSumY / nCount;
            // 노말값 다시 셋팅
            ChangeNormalValue(m_vecSelVertex[i], &pEditV);
        }
    }

    m_pMesh->UnlockVertexBuffer();
}

// 지형 높이 리셋
void cMapTerrainTool::ResetHeight()
{
    // 편집할 버텍스 로드
    ST_PNT_VERTEX* pEditV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

    float fDefHeight = g_pMapDataManager->GetDefHeight();

    for (int i = 0; i < m_vecSelVertex.size(); ++i)
    {
        pEditV[m_vecSelVertex[i]].p.y = fDefHeight;
        ChangeNormalValue(m_vecSelVertex[i], &pEditV);
    }

    m_pMesh->UnlockVertexBuffer();
}

// 변경된 버텍스와 주변 버텍스 노말값 변경
void cMapTerrainTool::ChangeNormalValue(int nIndex, ST_PNT_VERTEX** vEditV)
{
    // 변경 버텍스 노말값 셋팅
    SetNormal(nIndex, vEditV);

    /* 검사 순서 : 숫자대로
    2 === 3 === o
    | \   | \   |
    |  \  |   \ |
    1 === @ === 4
    | \   | \   |
    |  \  |   \ |
    o === 6 === 5
    */

    // 좌측 버텍스 검사
    if (nIndex % (m_ptMapSize.x + 1) > 0)
    {
        // 1
        SetNormal(nIndex - 1, vEditV);
        // 상단 버텍스 검사
        if (nIndex < (m_ptMapSize.x + 1) * m_ptMapSize.y)
        {
            // 2
            SetNormal(nIndex + (m_ptMapSize.x + 1) - 1, vEditV);
        }
    }
    // 상단 버텍스 검사
    if (nIndex < (m_ptMapSize.x + 1) * m_ptMapSize.y)
    {
        // 3
        SetNormal(nIndex + (m_ptMapSize.x + 1), vEditV);
    }
    // 우측 버텍스 검사
    if (nIndex % (m_ptMapSize.x + 1) != m_ptMapSize.x)
    {
        // 4
        SetNormal(nIndex + 1, vEditV);
        // 하단 버텍스 검사
        if (nIndex / (m_ptMapSize.x + 1) > 0)
        {
            // 5
            SetNormal(nIndex - (m_ptMapSize.x + 1) + 1, vEditV);
        }
    }
    // 하단 버텍스 검사
    if (nIndex / (m_ptMapSize.x + 1) > 0)
    {
        // 6
        SetNormal(nIndex - (m_ptMapSize.x + 1), vEditV);
    }
}

// 버텍스 노말 계산, 셋팅
void cMapTerrainTool::SetNormal(int nIndex, ST_PNT_VERTEX** vEditV)
{
    Vector3 vBottom;
    Vector3 vTop;
    Vector3 vLeft;
    Vector3 vRight;

    // 하단 버텍스 셋팅
    if (nIndex / (m_ptMapSize.x + 1) > 0)
    {
        vBottom = (*vEditV)[nIndex - (m_ptMapSize.x + 1)].p;
    }
    else
    {
        vBottom = (*vEditV)[nIndex].p;
    }

    // 상단 버텍스 검사
    if (nIndex < (m_ptMapSize.x + 1) * m_ptMapSize.y)
    {
        vTop = (*vEditV)[nIndex + (m_ptMapSize.x + 1)].p;
    }
    else
    {
        vTop = (*vEditV)[nIndex].p;
    }

    // 좌측 버텍스 검사
    if (nIndex % (m_ptMapSize.x + 1) > 0)
    {
        vLeft = (*vEditV)[nIndex - 1].p;
    }
    else
    {
        vLeft = (*vEditV)[nIndex].p;
    }

    // 우측 버텍스 검사
    if (nIndex % (m_ptMapSize.x + 1) != m_ptMapSize.x)
    {
        vRight = (*vEditV)[nIndex + 1].p;
    }
    else
    {
        vRight = (*vEditV)[nIndex].p;
    }

    Vector3 vBT = vTop - vBottom;
    D3DXVec3Normalize(&vBT, &vBT);
    Vector3 vLR = vRight - vLeft;
    D3DXVec3Normalize(&vLR, &vLR);
    Vector3 vNormal;
    D3DXVec3Cross(&vNormal, &vBT, &vLR);
    D3DXVec3Normalize(&vNormal, &vNormal);

    (*vEditV)[nIndex].n = vNormal;
}

// 픽킹 지점에서 가장 가까운 버텍스 인덱스 가져오기
int cMapTerrainTool::GetNearVertexIndex(Vector3 vPickPos, vector<int> vecSelVertex)
{
    int nNearIndex = 0;
    float fNearLenght = FLT_MAX;
    for (int i = 0; i < vecSelVertex.size(); ++i)
    {
        // 버텍스와 픽킹 지점과의 거리(y값은 제외)
        float fLength = GetLength(Vector2(m_vecPNTVertex[vecSelVertex[i]].p.x, m_vecPNTVertex[vecSelVertex[i]].p.z), Vector2(vPickPos.x, vPickPos.z));

        if (fLength < fNearLenght)
        {
            nNearIndex = vecSelVertex[i];
            fNearLenght = fLength;
        }
    }
    return nNearIndex;
}

// 브러쉬 안에 있는 버텍스 인덱스 벡터
vector<int> cMapTerrainTool::GetVertexInBrush(Vector3 vPickPos, float fRadius)
{
    // 브러쉬 영역을 임의로 구분 한다. (정사각형 모양으로)
    int nMinX = vPickPos.x - fRadius;
    if (nMinX < 0)
    {
        nMinX = 0;
    }

    int nMaxX = vPickPos.x + fRadius + 1;
    if (nMaxX > m_ptMapSize.x)
    {
        nMaxX = m_ptMapSize.x;
    }

    int nMinZ = vPickPos.z - fRadius;
    if (nMinZ < 0)
    {
        nMinZ = 0;
    }

    int nMaxZ = vPickPos.z + fRadius + 1;
    if (nMaxZ > m_ptMapSize.y)
    {
        nMaxZ = m_ptMapSize.y;
    }

    vector<int> vecSelVertex;
    // 브러쉬(원) 안에 위치하는 버텍스의 인덱스를 벡터에 담는다.
    for (int z = nMinZ; z < nMaxZ; ++z)
    {
        for (int x = nMinX; x < nMaxX; ++x)
        {
            int nIndex = (z * (m_ptMapSize.y + 1)) + x;
            float fLength = GetLength(Vector2(m_vecPNTVertex[nIndex].p.x, m_vecPNTVertex[nIndex].p.z),
                Vector2(vPickPos.x, vPickPos.z));

            // 픽킹위치와 점 위치의 거리가 반지름보다 짧으면
            if (fLength < fRadius)
            {
                vecSelVertex.push_back(nIndex);
            }
        }
    }
    
    return vecSelVertex;
}

void cMapTerrainTool::DrawAlphaMap()
{
    auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("test");

    D3DLOCKED_RECT      AlphaMap_Locked;
    memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));
    t->LockRect(0, &AlphaMap_Locked, NULL, NULL);
    LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;

    for (int i = 0; i < 50; i++)
    {
        LPDWORD pDWordDST = (LPDWORD)(pDataDST + i * AlphaMap_Locked.Pitch);
        for (int y = 0; y < 50; y++)
        {
            *(pDWordDST + y) = 0xffffffff;
        }
    }

    t->UnlockRect(0);

    HRESULT hr = D3DXSaveTextureToFileA("test.png",
        D3DXIFF_PNG,
        t,
        NULL);
}

void cMapTerrainTool::RendBrush()
{
    Matrix4 matRotY;
    ST_PC_VERTEX InitBrush[2];
    InitBrush[0].c = D3DCOLOR_XRGB(255, 255, 255);
    InitBrush[1].c = D3DCOLOR_XRGB(255, 255, 255);
   
   
    Vector3 vCenter ;                                      // vCenter : 원의 중점, InitBrush 선을 그을 두 점
    vCenter = *m_vPickPos;
   
    float f;
    if (g_pMapDataManager->GetTabType() == E_TERRAIN_TAB)
    {
        f = g_pMapDataManager->GetTerBrushSize();
    }
    else if (g_pMapDataManager->GetTabType() == E_TEXTURE_TAB)
    {
        f = g_pMapDataManager->GetTexBrushSize();
    }
   
    InitBrush[0].p = *m_vPickPos;
    InitBrush[0].p.x += f;
   
    float RotY = 2.0 * D3DX_PI / 60.0f;                                 // 60번 회전할 각도. 한 회당 6도
    
    for (int i = 0; i < 60; ++i)
    {
        InitBrush[1].p.x = vCenter.x + f * cosf(RotY * (i + 1));
        InitBrush[1].p.z = vCenter.z + f * sinf(RotY * (i + 1));
        InitBrush[1].p.y = g_pMapDataManager->GetDefHeight() + 0.0001f;
   
        g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, InitBrush, sizeof(ST_PC_VERTEX));
   
        //배열의 1번값을 0번으로 돌려준다
        InitBrush[0] = InitBrush[1];
    }
}


// 지형맵 파일 저장하기
HRESULT cMapTerrainTool::SaveFile(IN string sFolderName, IN string sFileName)
{
	return S_OK;
}

// 지형맵 파일 로드하기
HRESULT cMapTerrainTool::LoadFile(IN string sFolderName, IN string sFileName)
{
	return S_OK;
}
