#include "stdafx.h"
#include "cMapTerrainTool.h"


cMapTerrainTool::cMapTerrainTool()
    : m_eTerraingEditType(g_pMapDataManager->GetTerEditType())
    , m_stTerrainBrushInfo(g_pMapDataManager->GetTerBrushSize()
        , g_pMapDataManager->GetTerFlatSize()
        , g_pMapDataManager->GetTerIncrement()
        , g_pMapDataManager->GetTerGradient())
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
{
}


cMapTerrainTool::~cMapTerrainTool()
{
	SAFE_RELEASE(m_pMesh);
}

HRESULT cMapTerrainTool::Setup()
{
    m_eTerraingEditType = E_TER_EDIT_BEGIN;

    m_stTerrainBrushInfo.fIncrementHeight = 3.0f;
    m_stTerrainBrushInfo.fGradient = 45.0f;
    m_stTerrainBrushInfo.fTerrainBrushSize = 5.0f;
    m_stTerrainBrushInfo.fTerrainFlatSize = 2.0f;

    m_stTextureBrushInfo.m_eCurrTextureType = g_pMapDataManager->GetDefGroundType();
    m_stTextureBrushInfo.m_isWalkable = g_pMapDataManager->GetDefWalkable();
    m_stTextureBrushInfo.fTextureDensity = 1.0f;
    m_stTextureBrushInfo.fTextureBrushSize = 5.0f;
    m_stTextureBrushInfo.fTextureBrushDenSize = 2.0f;
    m_stTextureBrushInfo.fTexturBrushDensity = 1.0f;

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
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	// 메쉬로 그리기
	for (int i = 0; i < E_GROUND_TYPE_MAX; ++i)
	{
		g_pDevice->SetTexture(0, (LPTEXTURE9)g_pTextureManager->GetTexture("Grass"));
    	m_pMesh->DrawSubset(i);
	}

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

	return S_OK;
}

// 크기 설정한 맵 생성 (x사이즈, z사이즈, 지형 타입)
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType, IN float fHeight, IN float isWalkable)
{
    // 가로 세로 사이즈 계산 후 맵 만들기
    m_ptSize.x = m_ptSize.y = (eMapSize + 1) * 64;

    int nSizeX = m_ptSize.x;
    int nSizeZ = m_ptSize.y;

    // 텍스쳐 셋팅
    g_pTextureManager->AddTexture("Grass", "Texture/Grass.jpg");

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
		m_vecPTVertex.push_back(ST_PT_VERTEX(vec, Vector2((n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
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
    D3DXCreateMeshFVF(m_vecVertexIndex.size() / 3, m_vecPTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PT_VERTEX::FVF, g_pDevice, &m_pMesh);

    // 버텍스 버퍼 기록
    ST_PT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);
    memcpy(pV, &m_vecPTVertex[0], m_vecPTVertex.size() * sizeof(ST_PT_VERTEX));
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
        pA[i] = (DWORD) eGroundType;
    m_pMesh->UnlockAttributeBuffer();

    // 메쉬 최적화 : 버텍스 개수 만큼 인접정보를 담을 공간을 확보
    vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);

    m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
        &vecAdjBuf[0], 0, 0, 0);

	return S_OK;

}

// 브러쉬 사이즈 설정 (브러쉬 사이즈)
HRESULT cMapTerrainTool::SetBrushSize(IN float fSize)
{
	//// 예외처리
	//if (fSize < 0 || fSize < m_BrushInfo.fBrushDensitySize)
	//{
	//	return E_INVALIDARG;
	//}

	//m_BrushInfo.fBrushSize = fSize;

	return S_OK;
}

// 브러쉬 농도 사이즈 설정(농도 사이즈)
HRESULT cMapTerrainTool::SetBrushDensity(IN float fSize)
{
	//// 예외처리
	//if (fSize < 0 || fSize > m_BrushInfo.fBrushSize)
	//{
	//	return E_INVALIDARG;
	//}

	//m_BrushInfo.fBrushDensitySize = fSize;

	return S_OK;
}

// 지형 높이 설정 (센터 포지션, 증감될 높이 값)
HRESULT cMapTerrainTool::SetHeight(IN Vector2 vPosition, IN float fHeight)
{
	return S_OK;
}

// 텍스쳐의 밀도 설정 (증감될 밀도 값) : 이는 브러쉬의 속성을 설정해줌
HRESULT cMapTerrainTool::SetTextureDensity(IN float& fDensity)
{
	return S_OK;
}

// 텍스쳐 타입 설정 (변경될 텍스쳐 타입)
HRESULT cMapTerrainTool::SetTextureType(IN E_GROUND_TYPE eGroundType)
{
	return S_OK;
}

// 물 브러쉬 사이즈 설정 (물 브러쉬 사이즈)
HRESULT cMapTerrainTool::SetWaterBrushSize(IN float fSize)
{
	return S_OK;
}

// 물의 유속 설정 (증감될 유속 값) : 물의 밀도와 움직임 값을 계산 및 설정
HRESULT cMapTerrainTool::SetWaterSpeed(IN float fSpeed)
{
	return S_OK;
}

// 지형에 텍스쳐 입히기 (센터 포지션, 지형 타입)
HRESULT cMapTerrainTool::SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType)
{
	return S_OK;
}

// 지형 높이 복제 (센터 포지션, 복제될 면 정보)
HRESULT cMapTerrainTool::SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo)
{
	return S_OK;
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
