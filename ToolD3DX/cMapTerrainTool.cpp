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
	// ���� ���� ����
	if (g_pKeyManager->isOnceKeyDown('U'))
	{

	}
	// ���� ���� ����
	else if (g_pKeyManager->isOnceKeyDown('D'))
	{

	}
	// �ؽ��� ������
	else if (g_pKeyManager->isOnceKeyDown('T'))
	{

	}
	// �⺻ �ؽ��ķ� ���� 
	else if (g_pKeyManager->isOnceKeyDown('E'))
	{

	}
	// ���̾� ������ ���
	else if (g_pKeyManager->isOnceKeyDown('W'))
	{

	}
	// ����
	else if (g_pKeyManager->isOnceKeyDown('S'))
	{

	}
	// �ε�
	else if (g_pKeyManager->isOnceKeyDown('L'))
	{
		
	}
	// ���� ���
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
	
	// �޽��� �׸���
	for (int i = 0; i < E_GROUND_TYPE_MAX; ++i)
	{
		g_pDevice->SetTexture(0, (LPTEXTURE9)g_pTextureManager->GetTexture("Grass"));
    	m_pMesh->DrawSubset(i);
	}

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

	return S_OK;
}

// ũ�� ������ �� ���� (x������, z������, ���� Ÿ��)
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType, IN float fHeight, IN float isWalkable)
{
    // ���� ���� ������ ��� �� �� �����
    m_ptSize.x = m_ptSize.y = (eMapSize + 1) * 64;

    int nSizeX = m_ptSize.x;
    int nSizeZ = m_ptSize.y;

    // �ؽ��� ����
    g_pTextureManager->AddTexture("Grass", "Texture/Grass.jpg");

	// ����ó��
	if (nSizeX <= 0 || nSizeZ < 0 || eGroundType < E_GROUND_TYPE_BEGIN || eGroundType >= E_GROUND_TYPE_MAX)
	{
		return E_INVALIDARG;
	}

    // ex) 512 * 512
	//   ofstream c;
	//   c.open("NewMap.raw");
	//c << (char)vec.y;

	// ���ؽ� ����
	for (int n = 0; n < (nSizeX + 1) * (nSizeZ + 1); ++n)
	{
		Vector3 vec = Vector3(n % (nSizeZ + 1), fHeight, n / (nSizeZ + 1));
		m_vecPTVertex.push_back(ST_PT_VERTEX(vec, Vector2((n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
	}

    // �ε��� ����, ������ ����
    //   1 3
    //   0 2
    //  0 , 1 , 2,  // 2 , 1 , 3 ����!!
    for (DWORD z = 0; z < nSizeZ; ++z)
    {
        for (DWORD x = 0; x < nSizeX; ++x)
        {
			// == �ε��� ���� ==
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

			// == ������ ���� ==
			// �ϴ� �ﰢ��
			ST_TERRAIN_FACE_INFO stFace1;

			stFace1.eGroundType[0] = eGroundType;
			stFace1.fBlending[0] = 1.0f;
			stFace1.isWalkable = true;
			stFace1.eObjProp = E_OBJ_NONE;

			// �鿡 ���ԵǴ� �ﰢ�� ���ؽ� ���� �����ϱ�
			stFace1.dVertexIndedArr[0] = _0;
			stFace1.dVertexIndedArr[1] = _1;
			stFace1.dVertexIndedArr[2] = _2;

			m_vecFaceInfo.push_back(stFace1);

			// ��� �ﰢ��
			ST_TERRAIN_FACE_INFO stFace2;

			stFace2.eGroundType[0] = eGroundType;
			stFace2.fBlending[0] = 1.0f;
			stFace2.isWalkable = true;
			stFace2.eObjProp = E_OBJ_NONE;

			// �鿡 ���ԵǴ� �ﰢ�� ���ؽ� ���� �����ϱ�
			stFace2.dVertexIndedArr[0] = _2;
			stFace2.dVertexIndedArr[1] = _1;
			stFace2.dVertexIndedArr[2] = _3;

			m_vecFaceInfo.push_back(stFace2);
        }
    }

    // �Ž� ���� ����
    // == �Ž� ����, ���, ����ȭ
    // ����
    D3DXCreateMeshFVF(m_vecVertexIndex.size() / 3, m_vecPTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PT_VERTEX::FVF, g_pDevice, &m_pMesh);

    // ���ؽ� ���� ���
    ST_PT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);
    memcpy(pV, &m_vecPTVertex[0], m_vecPTVertex.size() * sizeof(ST_PT_VERTEX));
    m_pMesh->UnlockVertexBuffer();

    // �ε��� ���� ���
    DWORD* pI = NULL;
    m_pMesh->LockIndexBuffer(NULL, (LPVOID*)&pI);
    memcpy(pI, &m_vecVertexIndex[0], m_vecVertexIndex.size() * sizeof(DWORD));
    m_pMesh->UnlockIndexBuffer();

    // �Ӽ� ���� ���
    DWORD* pA = NULL;
    m_pMesh->LockAttributeBuffer(NULL, &pA);
    for (int i = 0; i < m_vecVertexIndex.size() / 3; ++i) // ���̽����� �ϳ��� ���
        pA[i] = (DWORD) eGroundType;
    m_pMesh->UnlockAttributeBuffer();

    // �޽� ����ȭ : ���ؽ� ���� ��ŭ ���������� ���� ������ Ȯ��
    vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);

    m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
        &vecAdjBuf[0], 0, 0, 0);

	return S_OK;

}

// �귯�� ������ ���� (�귯�� ������)
HRESULT cMapTerrainTool::SetBrushSize(IN float fSize)
{
	//// ����ó��
	//if (fSize < 0 || fSize < m_BrushInfo.fBrushDensitySize)
	//{
	//	return E_INVALIDARG;
	//}

	//m_BrushInfo.fBrushSize = fSize;

	return S_OK;
}

// �귯�� �� ������ ����(�� ������)
HRESULT cMapTerrainTool::SetBrushDensity(IN float fSize)
{
	//// ����ó��
	//if (fSize < 0 || fSize > m_BrushInfo.fBrushSize)
	//{
	//	return E_INVALIDARG;
	//}

	//m_BrushInfo.fBrushDensitySize = fSize;

	return S_OK;
}

// ���� ���� ���� (���� ������, ������ ���� ��)
HRESULT cMapTerrainTool::SetHeight(IN Vector2 vPosition, IN float fHeight)
{
	return S_OK;
}

// �ؽ����� �е� ���� (������ �е� ��) : �̴� �귯���� �Ӽ��� ��������
HRESULT cMapTerrainTool::SetTextureDensity(IN float& fDensity)
{
	return S_OK;
}

// �ؽ��� Ÿ�� ���� (����� �ؽ��� Ÿ��)
HRESULT cMapTerrainTool::SetTextureType(IN E_GROUND_TYPE eGroundType)
{
	return S_OK;
}

// �� �귯�� ������ ���� (�� �귯�� ������)
HRESULT cMapTerrainTool::SetWaterBrushSize(IN float fSize)
{
	return S_OK;
}

// ���� ���� ���� (������ ���� ��) : ���� �е��� ������ ���� ��� �� ����
HRESULT cMapTerrainTool::SetWaterSpeed(IN float fSpeed)
{
	return S_OK;
}

// ������ �ؽ��� ������ (���� ������, ���� Ÿ��)
HRESULT cMapTerrainTool::SetDrawTexture(IN Vector2 vPosition, IN E_GROUND_TYPE eGroundType)
{
	return S_OK;
}

// ���� ���� ���� (���� ������, ������ �� ����)
HRESULT cMapTerrainTool::SetDuplicateHeight(IN Vector2 vPosition, IN ST_TERRAIN_FACE_INFO stFaceInfo)
{
	return S_OK;
}

// ������ ���� �����ϱ�
HRESULT cMapTerrainTool::SaveFile(IN string sFolderName, IN string sFileName)
{
	return S_OK;
}

// ������ ���� �ε��ϱ�
HRESULT cMapTerrainTool::LoadFile(IN string sFolderName, IN string sFileName)
{
	return S_OK;
}
