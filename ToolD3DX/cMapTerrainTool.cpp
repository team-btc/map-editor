#include "stdafx.h"
#include "cMapTerrainTool.h"

cMapTerrainTool::cMapTerrainTool()
    : m_stTerrainBrushInfo(g_pMapDataManager->GetTerUpDown()
        , g_pMapDataManager->GetTerEditType()
        , g_pMapDataManager->GetTerBrushType()
        , g_pMapDataManager->GetTerEditPower()
        , g_pMapDataManager->GetTerEditHeight()
        , g_pMapDataManager->GetTerBrushSize())
    , m_stTextureBrushInfo(g_pMapDataManager->GetCurrTexIndex()
        , g_pMapDataManager->GetDrawDensity()
        , g_pMapDataManager->GetTexBrushSize()
        , g_pMapDataManager->GetTexBrushDenSize()
        , g_pMapDataManager->GetDrawType()
        , g_pMapDataManager->GetTex1Density()
        , g_pMapDataManager->GetTex2Density()
        , g_pMapDataManager->GetTex3Density())
    , m_stWaterInfo(g_pMapDataManager->GetWaterHeight()
        , g_pMapDataManager->GetWaterUVSpeed()
        , g_pMapDataManager->GetWaterWaveHeight()
        , g_pMapDataManager->GetWaterHeightSpeed()
        , g_pMapDataManager->GetWaterFrequency()
        , g_pMapDataManager->GetWaterTransparent()
        , g_pMapDataManager->GetWaterDensity())
    , m_isTex1Load(g_pMapDataManager->GetIsTex1Load())
    , m_isTex2Load(g_pMapDataManager->GetIsTex2Load())
    , m_isTex3Load(g_pMapDataManager->GetIsTex3Load())
    , m_isWaterEnable(g_pMapDataManager->GetIsMakeWater())
    , m_isSetWaterFile(g_pMapDataManager->GetIsSetWaterFile())
    , m_strWaterFileName(g_pMapDataManager->GetWaterFileName())
    , m_isSetSkyFile(g_pMapDataManager->GetIsSetSkyFile())
    , m_strSkyFileName(g_pMapDataManager->GetSkyFileName())
    , m_pMesh(NULL)
    , m_vPickPos(NULL)
    , m_pTextureShader(NULL)
    , m_pBrush(NULL)
    , m_pWaveShader(NULL)
    , m_pSkyBoxShader(NULL)
    , m_pFogShader(NULL)
    , m_fPassedEditTime(0.0f)
    , m_fillMode(D3DFILL_SOLID)
{
}


cMapTerrainTool::~cMapTerrainTool()
{
	SAFE_RELEASE(m_pMesh);
    SAFE_DELETE(m_pBrush);
    SAFE_DELETE(m_pTextureShader);
    SAFE_DELETE(m_pWaveShader);
    SAFE_DELETE(m_pSkyBoxShader);
    SAFE_DELETE(m_pFogShader);
}

HRESULT cMapTerrainTool::Setup()
{
    // ���� ����Ʈ
    D3DXVECTOR3 dir(1.0f, -1.0f, 0.0f);
    D3DXVec3Normalize(&dir, &dir);
    D3DLIGHT9 stLight = InitDirectional(&dir, &WHITE);
    g_pDevice->SetLight(0, &stLight);

    m_pBrush = new cBrush;
    m_pTextureShader = new cTextureShader;
    m_pWaveShader = new cWaveShader;
    m_pSkyBoxShader = new cSkyBoxShader;
    m_pFogShader = new cFogShader;

    m_stTerrainBrushInfo.eUpDown = E_UP;
    m_stTerrainBrushInfo.eEditType = E_TER_EDIT_BEGIN;
    m_stTerrainBrushInfo.eBrushType = E_TER_BRUSH_SMOOTH;
    m_stTerrainBrushInfo.fPower = 3.0f;
    m_stTerrainBrushInfo.fEditHeight = g_pMapDataManager->GetDefHeight();
    m_stTerrainBrushInfo.fBrushSize = 30.0f;

    m_stTextureBrushInfo.m_nCurrTextureIndex = 0;
    m_stTextureBrushInfo.fDrawDensity = 100.0f;
    m_stTextureBrushInfo.fTextureBrushSize = 5.0f;
    m_stTextureBrushInfo.fTextureBrushSpraySize = 10.0f;
    m_stTextureBrushInfo.m_eDrawType = E_DRAW_ERASE;
    m_stTextureBrushInfo.m_fTex1Density = 10.0f;
    m_stTextureBrushInfo.m_fTex2Density = 10.0f;
    m_stTextureBrushInfo.m_fTex3Density = 10.0f;

    m_stWaterInfo.fHeight = g_pMapDataManager->GetDefHeight();

    m_stWaterInfo.fUVSpeed = 0.01f;
    m_stWaterInfo.fWaveHeight = 0.6f;
    m_stWaterInfo.fHeightSpeed = 2.4f;
    m_stWaterInfo.fFrequency = 7.0f;
    m_stWaterInfo.fTransparent = 0.6f;
    m_stWaterInfo.fDensity = 1.0f;


    m_isWaterEnable = false;
    m_isSetWaterFile = false;
    m_isSetSkyFile = false;
    m_strWaterFileName = "NONE";
    m_strSkyFileName = "MidNight.dds";
    m_pSkyBoxShader->SetBox("MidNight.dds", "Shader/Texture/MidNight.dds");
    m_pTextureShader->SetTexture();
    m_pTextureShader->SetBrush(m_pBrush);
    m_pWaveShader->SetShader(m_stWaterInfo.fHeight, m_stWaterInfo.fWaveHeight, m_stWaterInfo.fHeightSpeed, m_stWaterInfo.fUVSpeed, m_stWaterInfo.fFrequency, m_stWaterInfo.fTransparent);

	return S_OK;
}

HRESULT cMapTerrainTool::Update()
{
    Vector4 v(m_vPickPos->x / m_ptMapSize.x , 0, m_vPickPos->z / m_ptMapSize.y, 1);

    // �ؽ��� ���Ϻ��� �ϱ�
    if (m_isTex1Load)
    {
        m_pTextureShader->SetTexture1();
    }
    if (m_isTex2Load)
    {
        m_pTextureShader->SetTexture2();
    }
    if (m_isTex2Load)
    {
        m_pTextureShader->SetTexture3();
    }
    // �ؽ��� ���Ϻ��� �ϱ�
    if (m_isTex1Load)
    {
        m_pTextureShader->SetTexture1();
    }
    if (m_isTex2Load)
    {
        m_pTextureShader->SetTexture2();
    }
    if (m_isTex2Load)
    {
        m_pTextureShader->SetTexture3();
    }

    if (g_pMapDataManager->GetTabType() == E_TERRAIN_TAB)
    {
        m_pBrush->SetBrush(v, m_stTerrainBrushInfo.fBrushSize / m_ptMapSize.x,
            m_stTerrainBrushInfo.fBrushSize / m_ptMapSize.x,
            m_stTextureBrushInfo.fDrawDensity * 0.1f, m_stTextureBrushInfo.m_fTex1Density * 0.1f, 
            m_stTextureBrushInfo.m_fTex2Density * 0.1f, m_stTextureBrushInfo.m_fTex3Density * 0.1f);
    }
    else if (g_pMapDataManager->GetTabType() == E_TEXTURE_TAB)
    {
        m_pBrush->SetBrush(v, m_stTextureBrushInfo.fTextureBrushSize / m_ptMapSize.x,
            m_stTextureBrushInfo.fTextureBrushSpraySize / m_ptMapSize.x,
            m_stTextureBrushInfo.fDrawDensity * 0.1f, m_stTextureBrushInfo.m_fTex1Density * 0.1f, 
            m_stTextureBrushInfo.m_fTex2Density * 0.1f, m_stTextureBrushInfo.m_fTex3Density * 0.1f);
    }
    else if (g_pMapDataManager->GetTabType() == E_WATER_TAB)
    {
        m_pWaveShader->SetShader(m_stWaterInfo.fHeight, m_stWaterInfo.fWaveHeight, m_stWaterInfo.fHeightSpeed, m_stWaterInfo.fUVSpeed, m_stWaterInfo.fFrequency, m_stWaterInfo.fTransparent, m_stWaterInfo.fDensity);
        
        // �� ������ ���� �����ؾ� �ϸ�
        if (m_isSetWaterFile)
        {
            // �ٽ� ��������
            m_isSetWaterFile = false;
            m_pWaveShader->SetWaveTexture(g_pMapDataManager->GetWaterFilePath(), m_strWaterFileName);
        }

        // �ϴ� ������ ���� �����ؾ� �ϸ�
        if (m_isSetSkyFile)
        {
            // �ٽ� ��������
            m_isSetSkyFile = false;
            m_pSkyBoxShader->SetBox(m_strSkyFileName, g_pMapDataManager->GetSkyFilePath() + "//" + m_strSkyFileName);
        }
    }
	
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
        //D3DXSaveMeshToX("Map.x", m_pMesh, NULL, NULL, NULL, NULL, NULL);
        //m_pTextureShader->SaveTexture();
	}
	// �ε�
	else if (g_pKeyManager->isOnceKeyDown('L'))
	{
        //D3DXLoadMeshFromX("Map.x", NULL, g_pDevice, NULL, NULL, NULL, NULL, &m_pMesh);
        //m_pTextureShader->SetMesh(m_pMesh);
	}
    else if (g_pKeyManager->isStayKeyDown('Z'))
    {
        m_stWaterInfo.fDensity += 0.2f;
        if (m_stWaterInfo.fDensity >= 120)
        {
            m_stWaterInfo.fDensity = 120.0f;
        }
    }
    else if (g_pKeyManager->isStayKeyDown('X'))
    {
        m_stWaterInfo.fDensity -= 0.2f;
        if (m_stWaterInfo.fDensity <= 0.2f)
        {
            m_stWaterInfo.fDensity = 0.2f;
        }
    }
	return S_OK;
}

HRESULT cMapTerrainTool::Render()
{
    if (!m_pMesh)
    {
        return E_FAIL;
    }

	Matrix4 matW, matV, matP;
	D3DXMatrixIdentity(&matW);

	g_pDevice->SetTransform(D3DTS_WORLD, &matW);
	g_pDevice->SetMaterial(&WHITE_MTRL);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
    g_pDevice->LightEnable(0, true);
    g_pDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
   
    Vector4 vP(g_vCameraPos.x, g_vCameraPos.y, g_vCameraPos.z, 1.0f);

    m_pTextureShader->Render();

    if (m_isWaterEnable)
    {
        m_pWaveShader->Render(vP);
    }
    
    m_pFogShader->Render();
    g_pDevice->SetRenderState(D3DRS_ZENABLE, true);

   
	return S_OK;
}

HRESULT cMapTerrainTool::RenderSkyBox()
{
    Vector4 vP(g_vCameraPos.x, g_vCameraPos.y, g_vCameraPos.z, 1.0f);

    m_pSkyBoxShader->Render(vP);
    return S_OK;
}

// ���콺 ���� ��ư Ŭ�� ���� �� �ߵ�
void cMapTerrainTool::OnceLButtonDown(E_TAB_TYPE eTabType)
{
    // ������
    if (eTabType == E_TERRAIN_TAB)
    {
        // �ʱ�ȭ
        m_fPassedEditTime = 0.0f;
    }

    // �ؽ�����
    else if (eTabType == E_TEXTURE_TAB)
    {
    }
}

// ���콺 ���� ��ư ��� ���� �� �ߵ�
void cMapTerrainTool::StayLButtonDown(E_TAB_TYPE eTabType)
{
    // ������
    if (eTabType == E_TERRAIN_TAB)
    {
        // ���콺 ��ġ�� ���� ���ؽ� ���� ��������
        if (m_vPickPos)
        {
            // ���õ� ���ؽ����� �ε���
            m_vecSelVertex.clear();
            m_vecSelVertex = GetVertexInBrush(*m_vPickPos, m_stTerrainBrushInfo.fBrushSize);

            // ���� �����ϱ�
            EditTerrain();
        }
    }

    // �ؽ�����
    else if (eTabType == E_TEXTURE_TAB)
    {
        m_pBrush->SetType(m_stTextureBrushInfo.m_nCurrTextureIndex, m_stTextureBrushInfo.m_eDrawType);
        m_pTextureShader->Update();
    }
}

// ũ�� ������ �� ���� (x������, z������, ���� Ÿ��)
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN float fHeight)
{
    // ���� ���� ������ ��� �� �� �����
    m_ptMapSize.x = m_ptMapSize.y = (eMapSize + 1) * 64;
    m_pTextureShader->SetMapSize();
    int nSizeX = m_ptMapSize.x;
    int nSizeZ = m_ptMapSize.y;

    // ex) 512 * 512
    //   ofstream c;
    //   c.open("NewMap.raw");
    //c << (char)vec.y;

    // ���ؽ� ����
    vector<ST_PNT_VERTEX> vecPNTVertex;
    for (int n = 0; n < (nSizeX + 1) * (nSizeZ + 1); ++n)
    {
        Vector3 vec = Vector3(n % (nSizeZ + 1), fHeight, n / (nSizeZ + 1));
        vecPNTVertex.push_back(ST_PNT_VERTEX(vec, Vector3(0, 1, 0), Vector2((n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
    }

    // �ε��� ����
    //   1 3
    //   0 2
    //  0 , 1 , 2,  // 2 , 1 , 3 ����!!
    vector<DWORD> vecVertexIndex;
    for (DWORD z = 0; z < nSizeZ; ++z)
    {
        for (DWORD x = 0; x < nSizeX; ++x)
        {
            DWORD _0 = (z * (nSizeZ + 1)) + x;
            DWORD _1 = ((z + 1) * (nSizeZ + 1)) + x;
            DWORD _2 = (z * (nSizeZ + 1)) + (x + 1);
            DWORD _3 = (z + 1) * (nSizeZ + 1) + (x + 1);

            vecVertexIndex.push_back(_0);
            vecVertexIndex.push_back(_1);
            vecVertexIndex.push_back(_2);
            vecVertexIndex.push_back(_2);
            vecVertexIndex.push_back(_1);
            vecVertexIndex.push_back(_3);
        }
    }

    // �Ž� ���� ����
    // == �Ž� ����, ���, ����ȭ
    // ����
    D3DXCreateMeshFVF(vecVertexIndex.size() / 3, vecPNTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PNT_VERTEX::FVF, g_pDevice, &m_pMesh);

    // ���ؽ� ���� ���
    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);
    memcpy(pV, &vecPNTVertex[0], vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
    m_pMesh->UnlockVertexBuffer();

    // �ε��� ���� ���
    DWORD* pI = NULL;
    m_pMesh->LockIndexBuffer(NULL, (LPVOID*)&pI);
    memcpy(pI, &vecVertexIndex[0], vecVertexIndex.size() * sizeof(DWORD));
    m_pMesh->UnlockIndexBuffer();

    // �Ӽ� ���� ���
    DWORD* pA = NULL;
    m_pMesh->LockAttributeBuffer(NULL, &pA);
    for (int i = 0; i < vecVertexIndex.size() / 3; ++i) // ���̽����� �ϳ��� ���
        pA[i] = (DWORD) 0;
    m_pMesh->UnlockAttributeBuffer();

    // �޽� ����ȭ : ���ؽ� ���� ��ŭ ���������� ���� ������ Ȯ��
    vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);

    m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
        &vecAdjBuf[0], 0, 0, 0);

    m_pTextureShader->SetMesh(m_pMesh);


    // ���ؽ� ����
    for (int n = 0; n < (1 + 1) * (1 + 1); ++n)
    {
        Vector3 vec = Vector3(n % (1 + 1) * nSizeX, fHeight, n / (1 + 1) * nSizeZ);
        m_vecWPNTVertex.push_back(ST_PNT_VERTEX(vec, Vector3(0, 1, 0), Vector2((n % (1 + 1)) / (float)1, (n / (1 + 1) / (float)1))));
    }

    // �ε��� ����
    //   1 3
    //   0 2
    //  0 , 1 , 2,  // 2 , 1 , 3 ����!!
    for (DWORD z = 0; z < 1; ++z)
    {
        for (DWORD x = 0; x < 1; ++x)
        {
            DWORD _0 = (z * (1 + 1)) + x;
            DWORD _1 = ((z + 1) * (1 + 1)) + x;
            DWORD _2 = (z * (1 + 1)) + (x + 1);
            DWORD _3 = (z + 1) * (1 + 1) + (x + 1);

            m_vecWVertexIndex.push_back(_0);
            m_vecWVertexIndex.push_back(_1);
            m_vecWVertexIndex.push_back(_2);
            m_vecWVertexIndex.push_back(_2);
            m_vecWVertexIndex.push_back(_1);
            m_vecWVertexIndex.push_back(_3);
        }
    }
    // �Ž� ���� ����
    // == �Ž� ����, ���, ����ȭ
    // ����
    D3DXCreateMeshFVF(m_vecWVertexIndex.size() / 3, m_vecWPNTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PNT_VERTEX::FVF, g_pDevice, &m_pWMesh);

    // ���ؽ� ���� ���
    ST_PNT_VERTEX* pWV = NULL;
    m_pWMesh->LockVertexBuffer(NULL, (LPVOID*)&pWV);
    memcpy(pWV, &m_vecWPNTVertex[0], m_vecWPNTVertex.size() * sizeof(ST_PNT_VERTEX));
    m_pWMesh->UnlockVertexBuffer();

    // �ε��� ���� ���
    DWORD* pWI = NULL;
    m_pWMesh->LockIndexBuffer(NULL, (LPVOID*)&pWI);
    memcpy(pWI, &m_vecWVertexIndex[0], m_vecWVertexIndex.size() * sizeof(DWORD));
    m_pWMesh->UnlockIndexBuffer();

    // �Ӽ� ���� ���
    DWORD* pWA = NULL;
    m_pWMesh->LockAttributeBuffer(NULL, &pWA);
    for (int i = 0; i < m_vecWVertexIndex.size() / 3; ++i) // ���̽����� �ϳ��� ���
        pWA[i] = (DWORD)0;
    m_pWMesh->UnlockAttributeBuffer();

    // �޽� ����ȭ : ���ؽ� ���� ��ŭ ���������� ���� ������ Ȯ��
    vector<DWORD> vecAdjBuf2(m_pWMesh->GetNumFaces() * 3);

    m_pWMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf2[0]);

    m_pWMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
        &vecAdjBuf2[0], 0, 0, 0);

    m_pWaveShader->SetMesh(m_pMesh);
    m_pFogShader->SetMesh(m_pMesh);

	return S_OK;
}

// �� ������ ����
void cMapTerrainTool::SaveMapData(string strFilePath, string strFileTitle)
{
    string str = strFilePath + "/" + strFileTitle + ".x";
    // ���� �Ž� ����
    D3DXSaveMeshToX(str.c_str(), m_pMesh, NULL, NULL, NULL, NULL, NULL);
    // �� �Ž� ����
    str = strFilePath + "/" + strFileTitle + "Water.x";
    D3DXSaveMeshToX(str.c_str(), m_pWMesh, NULL, NULL, NULL, NULL, NULL);
    // �ý�ó png ����
    m_pTextureShader->SaveTexture(strFilePath, strFileTitle);
}

// �� ������ �ε�
void cMapTerrainTool::LoadMapData(string sFilePath, string sFileTitle)
{
    // �Ž� �����
    SAFE_RELEASE(m_pMesh);
    
    // �Ž� �ε�
    string sFullPath = sFilePath + "\\" + sFileTitle + ".x";
    D3DXLoadMeshFromX(sFullPath.c_str(), D3DXMESH_VB_MANAGED, g_pDevice, NULL, NULL, NULL, NULL, &m_pMesh);

    // �ý�ó png �ε�
    string sFullPathPng = sFilePath + "\\" + sFileTitle;
    m_pTextureShader->SetMapSize(&sFullPathPng);
    // �ؽ��� �Ž� ����
    m_pTextureShader->SetMesh(m_pMesh);
    // �� ����
    m_pWaveShader->SetWaveTexture("Shader/Texture", m_strWaterFileName);
    m_pWaveShader->SetShader(m_stWaterInfo.fHeight, m_stWaterInfo.fWaveHeight, m_stWaterInfo.fHeightSpeed, m_stWaterInfo.fUVSpeed, m_stWaterInfo.fFrequency, m_stWaterInfo.fTransparent);
    // �ϴ� ����
    m_pSkyBoxShader->SetBox(m_strSkyFileName, "Shader/Texture/" + m_strSkyFileName);
}

// ���� ����
void cMapTerrainTool::EditTerrain()
{
    switch (m_stTerrainBrushInfo.eEditType)
    {
    case E_TER_EDIT_HEIGHT:
    {
        m_fPassedEditTime += g_pTimerManager->GetDeltaTime();

        // ���� �ð��� �Ǿ��� �� �Լ� �ߵ�
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

        // ���� �ð��� �Ǿ��� �� �Լ� �ߵ�
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

        // ���� �ð��� �Ǿ��� �� �Լ� �ߵ�
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

        // ���� �ð��� �Ǿ��� �� �Լ� �ߵ�
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

// ���� ���� ����
void cMapTerrainTool::EditHeight()
{
    switch (m_stTerrainBrushInfo.eUpDown)
    {
    case E_UP:
    {
        // ������ ���ؽ� �ε�
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // ��ŷ ������ ���� �����Ÿ��� �ִ� ���ؽ� �ε��� ã�ƿ���
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // ���ͳ��� ����
        float fCenterHeight = pEditV[nNearIndex].p.y + m_stTerrainBrushInfo.fPower;

        // 255���� ũ�� ����
        if (fCenterHeight > 255)
        {
            fCenterHeight = 255;
        }

        // ���� ����
        float fBaseHeight;
        // ���� ���̰� �⺻ ���̺��� ������
        if (fCenterHeight > g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // �����ǳ��̰� �⺻ ���̺��� ������
        else
        {
            fBaseHeight = 0;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // ���س��̿� ���ͳ����� ���̰�
            float fHeightDiff = fCenterHeight - fBaseHeight;

            float fRatio;           // ����
            float fHeightResult;    // �����Ǿ�� �� ���̰�

            // == �ε巯�� Ÿ���� �귯���� ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fBaseHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()����  -1 ~ 1 ������ ���ڰ� ���� 0 ~ 1 ���̰����� ���� �� ���!
            }
            // == ��ī�ο� Ÿ���� �귯���� ==
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fBaseHeight + (fHeightDiff * fRatio);
            }

            // ������ ���̰� ������ ���̺��� ���� ���� ���� ����
            if (pEditV[m_vecSelVertex[i]].p.y < fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // ���� ���� ���� �븻(����)�� �ٲٱ�
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // ���̰� 255�� ������ ����
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
        // ������ ���ؽ� �ε�
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // ��ŷ ������ ���� �����Ÿ��� �ִ� ���ؽ� �ε��� ã�ƿ���
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // ���ͳ��� ���� (y�� ���߱�)
        float fCenterHeight = pEditV[nNearIndex].p.y - m_stTerrainBrushInfo.fPower;

        // ���� ����
        float fBaseHeight;
        // ���� ���̰� �⺻ ���̺��� ������
        if (fCenterHeight < g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // �����ǳ��̰� �⺻ ���̺��� ������
        else
        {
            fBaseHeight = 255;
        }

        // 0���� ũ�� ����
        if (fCenterHeight < 0)
        {
            fCenterHeight = 0;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // ���س��̿� ���ͳ����� ���̰�
            float fHeightDiff = fBaseHeight - fCenterHeight;

            float fRatio;           // ����
            float fHeightResult;    // �����Ǿ�� �� ���̰�

            // == �ε巯�� Ÿ���� �귯���� ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fCenterHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()����  -1 ~ 1 ������ ���ڰ� ���� 0 ~ 1 ���̰����� ���� �� ���!
            }
            // == ��ī�ο� Ÿ���� �귯���� ==
            else
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fCenterHeight + (fHeightDiff * fRatio);
            }

            // ������ ���̰� ������ ���̺��� ���� ���� ���� ����
            if (pEditV[m_vecSelVertex[i]].p.y > fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // ���� ���� ���� �븻(����)�� �ٲٱ�
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // ���̰� 0�� ������ ����
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

// ���� ���� �ǵ�����
void cMapTerrainTool::ReturnHeight()
{
switch (m_stTerrainBrushInfo.eUpDown)
    {
    case E_UP:
    {
        // ������ ���ؽ� �ε�
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // ��ŷ ������ ���� �����Ÿ��� �ִ� ���ؽ� �ε��� ã�ƿ���
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // ���ͳ��� ����
        float fCenterHeight = pEditV[nNearIndex].p.y - m_stTerrainBrushInfo.fPower;

        // ���� ���̰� �⺻ ���̺��� ������ ����
        if (fCenterHeight < g_pMapDataManager->GetDefHeight())
        {
            return;
        }

        // ���� ����
        float fBaseHeight = g_pMapDataManager->GetDefHeight();

        // �⺻ ���� ����
        float fDefaultPlusHeight = m_stTerrainBrushInfo.fPower;

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));

            float fRatio;               // ����
            float fHeightResult;        // �����Ǿ�� �� ���̰�

            // == �ε巯�� Ÿ���� �귯���� ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fDefaultPlusHeight * ((cosf(fRatio * PI) + 1.0f) * 0.5f); //cosf()����  -1 ~ 1 ������ ���ڰ� ���� 0 ~ 1 ���̰����� ���� �� ���!
            }
            // == ��ī�ο� Ÿ�� �귯���� == 
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fDefaultPlusHeight * fRatio;
            }

            // ���� ����
            pEditV[m_vecSelVertex[i]].p.y -= fHeightResult;

            // �븻(����)�� �ٲٱ�
            ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                
            // ������ ���̰� ���� ���̺��� ������ ����
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
        // ������ ���ؽ� �ε�
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // ��ŷ ������ ���� �����Ÿ��� �ִ� ���ؽ� �ε��� ã�ƿ���
        int nNearIndex = GetNearVertexIndex(*m_vPickPos, m_vecSelVertex);

        // ���ͳ��� ����
        float fCenterHeight = pEditV[nNearIndex].p.y + m_stTerrainBrushInfo.fPower;

        // ���� ���̰� �⺻ ���̺��� ������ ����
        if (fCenterHeight > g_pMapDataManager->GetDefHeight())
        {
            return;
        }

        // ���� ����
        float fBaseHeight = g_pMapDataManager->GetDefHeight();

        // �⺻ ���� ����
        float fDefaultPlusHeight = m_stTerrainBrushInfo.fPower;

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));

            float fRatio;           // ����
            float fHeightResult;    // �����Ǿ�� �� ���̰�

            // == �ε巯�� Ÿ�� �귯���� == 
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fDefaultPlusHeight * ((cosf(fRatio * PI) + 1.0f) * 0.5f); //cosf()����  -1 ~ 1 ������ ���ڰ� ���� 0 ~ 1 ���̰����� ���� �� ���!
            }

            // == ��ī�ο� Ÿ�� �귯���� ==
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fDefaultPlusHeight * fRatio;
            }

            // ���� ����
            pEditV[m_vecSelVertex[i]].p.y += fHeightResult;

            // �븻(����)�� �ٲٱ�
            ChangeNormalValue(m_vecSelVertex[i], &pEditV);

            // ������ ���̰� ���� ���̺��� ������ ����
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

// ���� ���� �����
void cMapTerrainTool::FixedHeight()
{
    switch (m_stTerrainBrushInfo.eUpDown)
    {
    case E_UP:
    {
        // ������ ���ؽ� �ε�
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // ���ͳ��� ����
        float fCenterHeight = m_stTerrainBrushInfo.fEditHeight;
        
        // ���� ����
        float fBaseHeight;
        // ���� ���̰� �⺻ ���̺��� ������
        if (fCenterHeight > g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // �����ǳ��̰� �⺻ ���̺��� ������
        else
        {
            fBaseHeight = 0;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // ���س��̿� ���ͳ����� ���̰�
            float fHeightDiff = fCenterHeight - fBaseHeight;

            float fRatio;           // ����
            float fHeightResult;    // �����Ǿ�� �� ���̰�

            // == �ε巯�� Ÿ���� �귯���� ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fBaseHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()����  -1 ~ 1 ������ ���ڰ� ���� 0 ~ 1 ���̰����� ���� �� ���!
            }
            // == ��ī�ο� Ÿ���� �귯���� ==
            else
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fBaseHeight + (fHeightDiff * fRatio);
            }

            // ������ ���̰� ������ ���̺��� ���� ���� ���� ����
            if (pEditV[m_vecSelVertex[i]].p.y < fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // ���� ���� ���� �븻(����)�� �ٲٱ�
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // ���̰� 255�� ������ ����
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
        // ������ ���ؽ� �ε�
        ST_PNT_VERTEX* pEditV = NULL;
        m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

        // ���ͳ��� ����
        float fCenterHeight = m_stTerrainBrushInfo.fEditHeight;

        // ���� ����
        float fBaseHeight;
        // ���� ���̰� �⺻ ���̺��� ������
        if (fCenterHeight < g_pMapDataManager->GetDefHeight())
        {
            fBaseHeight = g_pMapDataManager->GetDefHeight();
        }
        // �����ǳ��̰� �⺻ ���̺��� ������
        else
        {
            fBaseHeight = 255;
        }

        for (int i = 0; i < m_vecSelVertex.size(); ++i)
        {
            // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
            float fLength = GetLength(Vector2(pEditV[m_vecSelVertex[i]].p.x, pEditV[m_vecSelVertex[i]].p.z), Vector2(m_vPickPos->x, m_vPickPos->z));
            // ���س��̿� ���ͳ����� ���̰�
            float fHeightDiff = fBaseHeight - fCenterHeight;

            float fRatio;           // ����
            float fHeightResult;    // �����Ǿ�� �� ���̰�

            // == �ε巯�� Ÿ���� �귯���� ==
            if (m_stTerrainBrushInfo.eBrushType == E_TER_BRUSH_SMOOTH)
            {
                fRatio = 1.0f - (fLength / m_stTerrainBrushInfo.fBrushSize);
                fHeightResult = fCenterHeight + (fHeightDiff * ((cosf(fRatio * PI) + 1.0f) * 0.5f)); //cosf()����  -1 ~ 1 ������ ���ڰ� ���� 0 ~ 1 ���̰����� ���� �� ���!
            }
            // == ��ī�ο� Ÿ���� �귯���� ==
            else
            {
                fRatio = fLength / m_stTerrainBrushInfo.fBrushSize;
                fHeightResult = fCenterHeight + (fHeightDiff * fRatio);
            }

            // ������ ���̰� ������ ���̺��� ���� ���� ���� ����
            if (pEditV[m_vecSelVertex[i]].p.y > fHeightResult)
            {
                pEditV[m_vecSelVertex[i]].p.y = fHeightResult;
                // ���� ���� ���� �븻(����)�� �ٲٱ�
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
                // ���̰� 0�� ������ ����
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

// ���� �����ϱ�
void cMapTerrainTool::SetFlat()
{
   // ������ ���ؽ� �ε�
    ST_PNT_VERTEX* pEditV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

    for (int i = 0; i < m_vecSelVertex.size(); ++i)
    {
        // Up ��� �� �� (�ø��� ���� ���� ��)
        if (m_stTerrainBrushInfo.eUpDown == E_UP)
        {
            // ������ ���̰� ������ ���̺��� ���� ���� ���� ����
            if (pEditV[m_vecSelVertex[i]].p.y < m_stTerrainBrushInfo.fEditHeight)
            {
                pEditV[m_vecSelVertex[i]].p.y = m_stTerrainBrushInfo.fEditHeight;
                // ���� ���� ���� �븻(����)�� �ٲٱ�
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
            }
        }
        // Down ��� �� �� (������ ���� ���� ��)
        else
        {
            // ������ ���̰� ������ ���̺��� ���� ���� ���� ����
            if (pEditV[m_vecSelVertex[i]].p.y > m_stTerrainBrushInfo.fEditHeight)
            {
                pEditV[m_vecSelVertex[i]].p.y = m_stTerrainBrushInfo.fEditHeight;
                // ���� ���� ���� �븻(����)�� �ٲٱ�
                ChangeNormalValue(m_vecSelVertex[i], &pEditV);
            }
        }
    }

    m_pMesh->UnlockVertexBuffer();
}

// ���� �ٵ��(���� �ε巴��)
void cMapTerrainTool::TrimHeight()
{
    // ������ ���ؽ� �ε�
    ST_PNT_VERTEX* pEditV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pEditV);

    for (int i = 0; i < m_vecSelVertex.size(); ++i)
    {
        int nCount = 0;
        float fSumY = 0;

        /* �˻� ���� : ���ڴ��
        2 === 3 === 4
        | \   | \   |
        |  \  |   \ |
        1 === @ === 5
        | \   | \   |
        |  \  |   \ |
        8 === 7 === 6
        */

        // ���� ���ؽ� �˻�
        if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) > 0)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] - 1].p.y;
            // ��� ���ؽ� �˻�
            if (m_vecSelVertex[i] < (m_ptMapSize.x + 1) * m_ptMapSize.y)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] + (m_ptMapSize.x + 1) - 1].p.y;
            }
        }
        // ��� ���ؽ� �˻�
        if (m_vecSelVertex[i] < (m_ptMapSize.x + 1) * m_ptMapSize.y)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] + (m_ptMapSize.x + 1)].p.y;
            // ���� ���ؽ� �˻�
            if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) != m_ptMapSize.x)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] + (m_ptMapSize.x + 1) + 1].p.y;
            }
        }
        // ���� ���ؽ� �˻�
        if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) != m_ptMapSize.x)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] + 1].p.y;
            // �ϴ� ���ؽ� �˻�
            if (m_vecSelVertex[i] / (m_ptMapSize.x + 1) > 0)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] - (m_ptMapSize.x + 1) + 1].p.y;
            }
        }
        // �ϴ� ���ؽ� �˻�
        if (m_vecSelVertex[i] / (m_ptMapSize.x + 1) > 0)
        {
            ++nCount;
            fSumY += pEditV[m_vecSelVertex[i] - (m_ptMapSize.x + 1)].p.y;
            // ���� ���ؽ� �˻�
            if (m_vecSelVertex[i] % (m_ptMapSize.x + 1) > 0)
            {
                ++nCount;
                fSumY += pEditV[m_vecSelVertex[i] - (m_ptMapSize.x + 1) - 1].p.y;
            }
        }

        // ��� ������ Y�� ����
        if (nCount != 0)
        {
            pEditV[m_vecSelVertex[i]].p.y = fSumY / nCount;
            // �븻�� �ٽ� ����
            ChangeNormalValue(m_vecSelVertex[i], &pEditV);
        }
    }

    m_pMesh->UnlockVertexBuffer();
}

// ���� ���� ����
void cMapTerrainTool::ResetHeight()
{
    // ������ ���ؽ� �ε�
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

// ����� ���ؽ��� �ֺ� ���ؽ� �븻�� ����
void cMapTerrainTool::ChangeNormalValue(int nIndex, ST_PNT_VERTEX** vEditV)
{
    // ���� ���ؽ� �븻�� ����
    SetNormal(nIndex, vEditV);

    /* �˻� ���� : ���ڴ��
    2 === 3 === o
    | \   | \   |
    |  \  |   \ |
    1 === @ === 4
    | \   | \   |
    |  \  |   \ |
    o === 6 === 5
    */

    // ���� ���ؽ� �˻�
    if (nIndex % (m_ptMapSize.x + 1) > 0)
    {
        // 1
        SetNormal(nIndex - 1, vEditV);
        // ��� ���ؽ� �˻�
        if (nIndex < (m_ptMapSize.x + 1) * m_ptMapSize.y)
        {
            // 2
            SetNormal(nIndex + (m_ptMapSize.x + 1) - 1, vEditV);
        }
    }
    // ��� ���ؽ� �˻�
    if (nIndex < (m_ptMapSize.x + 1) * m_ptMapSize.y)
    {
        // 3
        SetNormal(nIndex + (m_ptMapSize.x + 1), vEditV);
    }
    // ���� ���ؽ� �˻�
    if (nIndex % (m_ptMapSize.x + 1) != m_ptMapSize.x)
    {
        // 4
        SetNormal(nIndex + 1, vEditV);
        // �ϴ� ���ؽ� �˻�
        if (nIndex / (m_ptMapSize.x + 1) > 0)
        {
            // 5
            SetNormal(nIndex - (m_ptMapSize.x + 1) + 1, vEditV);
        }
    }
    // �ϴ� ���ؽ� �˻�
    if (nIndex / (m_ptMapSize.x + 1) > 0)
    {
        // 6
        SetNormal(nIndex - (m_ptMapSize.x + 1), vEditV);
    }
}

// ���ؽ� �븻 ���, ����
void cMapTerrainTool::SetNormal(int nIndex, ST_PNT_VERTEX** vEditV)
{
    Vector3 vBottom;
    Vector3 vTop;
    Vector3 vLeft;
    Vector3 vRight;

    // �ϴ� ���ؽ� ����
    if (nIndex / (m_ptMapSize.x + 1) > 0)
    {
        vBottom = (*vEditV)[nIndex - (m_ptMapSize.x + 1)].p;
    }
    else
    {
        vBottom = (*vEditV)[nIndex].p;
    }

    // ��� ���ؽ� �˻�
    if (nIndex < (m_ptMapSize.x + 1) * m_ptMapSize.y)
    {
        vTop = (*vEditV)[nIndex + (m_ptMapSize.x + 1)].p;
    }
    else
    {
        vTop = (*vEditV)[nIndex].p;
    }

    // ���� ���ؽ� �˻�
    if (nIndex % (m_ptMapSize.x + 1) > 0)
    {
        vLeft = (*vEditV)[nIndex - 1].p;
    }
    else
    {
        vLeft = (*vEditV)[nIndex].p;
    }

    // ���� ���ؽ� �˻�
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

// ��ŷ �������� ���� ����� ���ؽ� �ε��� ��������
int cMapTerrainTool::GetNearVertexIndex(Vector3 vPickPos, vector<int> vecSelVertex)
{
    int nNearIndex = 0;
    float fNearLenght = FLT_MAX;

    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);

    for (int i = 0; i < vecSelVertex.size(); ++i)
    {
        // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
        float fLength = GetLength(Vector2(pV[vecSelVertex[i]].p.x, pV[vecSelVertex[i]].p.z), Vector2(vPickPos.x, vPickPos.z));

        if (fLength < fNearLenght)
        {
            nNearIndex = vecSelVertex[i];
            fNearLenght = fLength;
        }
    }

    m_pMesh->UnlockVertexBuffer();

    return nNearIndex;
}

// �귯�� �ȿ� �ִ� ���ؽ� �ε��� ����
vector<int> cMapTerrainTool::GetVertexInBrush(Vector3 vPickPos, float fRadius)
{
    // �귯�� ������ ���Ƿ� ���� �Ѵ�. (���簢�� �������)
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

    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);

    vector<int> vecSelVertex;
    // �귯��(��) �ȿ� ��ġ�ϴ� ���ؽ��� �ε����� ���Ϳ� ��´�.
    for (int z = nMinZ; z < nMaxZ; ++z)
    {
        for (int x = nMinX; x < nMaxX; ++x)
        {
            int nIndex = (z * (m_ptMapSize.y + 1)) + x;
            float fLength = GetLength(Vector2(pV[nIndex].p.x, pV[nIndex].p.z),
                Vector2(vPickPos.x, vPickPos.z));

            // ��ŷ��ġ�� �� ��ġ�� �Ÿ��� ���������� ª����
            if (fLength < fRadius)
            {
                vecSelVertex.push_back(nIndex);
            }
        }
    }

    m_pMesh->UnlockVertexBuffer();

    return vecSelVertex;
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