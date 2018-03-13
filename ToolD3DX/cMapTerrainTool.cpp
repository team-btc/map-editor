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
    , m_pHeightShader(NULL)
    , m_pDiffuseTex(NULL)
    , m_pHeightMapTex(NULL)
    , m_fillMode(D3DFILL_SOLID)
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
    //// ���� ����Ʈ
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

    if (m_pHeightShader)
    {
        m_pHeightShader->Release();
    }
    g_pShaderManager->AddEffect("height-map", "Shader/FX/HeightMap.fx");
    m_pHeightShader = g_pShaderManager->GetEffect("height-map");
    
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
        m_fillMode = D3DFILL_SOLID;
	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{
        m_fillMode = D3DFILL_WIREFRAME;
	}
	else if (g_pKeyManager->isOnceKeyDown('3'))
	{
        HRESULT hr = D3DXSaveTextureToFileA("heightmap.bmp",
            D3DXIFF_BMP,
            m_pHeightMapTex,
            NULL);

        hr = D3DXSaveTextureToFileA("normalmap.bmp",
            D3DXIFF_BMP,
            m_pNormalMapTex,
            NULL);
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
    //g_pDevice->LightEnable(0, true);
    g_pDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	// �޽��� �׸���
	//g_pDevice->SetTexture(0, (LPTEXTURE9)g_pTextureManager->GetTexture("default"));
    g_pDevice->GetTransform(D3DTS_VIEW, &matV);
    g_pDevice->GetTransform(D3DTS_PROJECTION, &matP);

    m_pHeightShader->SetMatrix("gWorldMatrix", &matW);
    m_pHeightShader->SetMatrix("gViewMatrix", &matV);
    m_pHeightShader->SetMatrix("gProjectionMatrix", &matP);

    m_pHeightShader->SetTexture("DiffuseMap_Tex", m_pHeightMapTex);
    m_pHeightShader->SetTexture("Heightmap_Tex", m_pHeightMapTex);

    UINT numPasses = 0;
    m_pHeightShader->Begin(&numPasses, NULL);
    {
        for (UINT i = 0; i < numPasses; ++i)
        {
            m_pHeightShader->BeginPass(i);
            {
                m_pMesh->DrawSubset(0);
            }
            m_pHeightShader->EndPass();
        }
    }
    m_pHeightShader->End();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

    //RendBrush();
    //m_pTextureShader->Render();

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
    m_pTextureShader->SetType(m_stTextureBrushInfo.m_eCurrTextureType);
    // ������
    if (eTabType == E_TERRAIN_TAB)
    {
        // ���콺 ��ġ�� ���� ������ ��������
        if (m_vPickPos)
        {
            // ���� �����ϱ�
            EditTerrain();
        }
    }

    // �ؽ�����
    else if (eTabType == E_TEXTURE_TAB)
    {
        m_pTextureShader->Update();
       // DrawAlphaMap();
    }
}

// ũ�� ������ �� ���� (x������, z������, ���� Ÿ��)
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType,
    IN float fHeight, IN float isWalkable)
{
    if (!m_pDiffuseTex)
    {
        auto tex = g_pTextureManager->GetTexture("default");
        if (tex)
        {
            m_pDiffuseTex = (LPTEXTURE9)tex;
        }
        else
        {
            g_pTextureManager->AddTexture("default", "Shader/Texture/Default.jpg");
        }
    }


    // ���� ���� ������ ��� �� �� �����
    m_ptMapSize.x = m_ptMapSize.y = (eMapSize + 1) * 64;

    int nSizeX = m_ptMapSize.x;
    int nSizeZ = m_ptMapSize.y;

    int nHeight = (int)fHeight;
    g_pTextureManager->AddTexture("height-map", nSizeX, D3DCOLOR_XRGB(nHeight, nHeight, nHeight));
    m_pHeightMapTex = (LPTEXTURE9)g_pTextureManager->GetTexture("height-map");

    g_pTextureManager->AddTexture("normal-map", nSizeX, D3DCOLOR_XRGB(0, 255, 0));
    m_pNormalMapTex = (LPTEXTURE9)g_pTextureManager->GetTexture("normal-map");

	// ����ó��
	if (nSizeX <= 0 || nSizeZ < 0 ||
        eGroundType < E_GROUND_TYPE_BEGIN || eGroundType >= E_GROUND_TYPE_MAX)
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
		m_vecPNTVertex.push_back(
            ST_PNT_VERTEX(vec,
                Vector3(0, 1, 0),
                Vector2((n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
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
    D3DXCreateMeshFVF(m_vecVertexIndex.size() / 3, m_vecPNTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PNT_VERTEX::FVF, g_pDevice, &m_pMesh);

    // ���ؽ� ���� ���
    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);
    memcpy(pV, &m_vecPNTVertex[0], m_vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
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
        pA[i] = (DWORD) 0;
    m_pMesh->UnlockAttributeBuffer();

    // �޽� ����ȭ : ���ؽ� ���� ��ŭ ���������� ���� ������ Ȯ��
    vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);

    m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
        &vecAdjBuf[0], 0, 0, 0);

    m_pTextureShader->SetMesh(m_pMesh);

    vecPNTQuad.push_back(VertexPNT(Vector3(0, fHeight, m_ptMapSize.y),
        Vector3(0, 1, 0), Vector2(0, 0)));
    vecPNTQuad.push_back(VertexPNT(Vector3(m_ptMapSize.x, fHeight, m_ptMapSize.y),
        Vector3(0, 1, 0), Vector2(1, 0)));
    vecPNTQuad.push_back(VertexPNT(Vector3(m_ptMapSize.x, fHeight, 0),
        Vector3(0, 1, 0), Vector2(1, 1)));

    vecPNTQuad.push_back(VertexPNT(Vector3(0, fHeight, m_ptMapSize.y),
        Vector3(0, 1, 0), Vector2(0, 0)));
    vecPNTQuad.push_back(VertexPNT(Vector3(m_ptMapSize.x, fHeight, 0),
        Vector3(0, 1, 0), Vector2(1, 1)));
    vecPNTQuad.push_back(VertexPNT(Vector3(0, fHeight, 0),
        Vector3(0, 1, 0), Vector2(0, 1)));

	return S_OK;

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
        DrawHeight(5);
    }
    break;

    case E_DOWN:
    {
        DrawHeight(-5);
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
        
    }
    break;

    case E_DOWN:
    {
        
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
        
    }
    break;

    case E_DOWN:
    {
        
    }
    break;
    }
}

// ���� �����ϱ�
void cMapTerrainTool::SetFlat()
{
    DrawFlat();
}

// ���� �ٵ��(���� �ε巴��)
void cMapTerrainTool::TrimHeight()
{
    
}

// ���� ���� ����
void cMapTerrainTool::ResetHeight()
{
    
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

void cMapTerrainTool::DrawHeight(int nHeight)
{
    POINT lt, rb;
    Vector2 vPick(m_vPickPos->x, m_vPickPos->z);

    lt.x = (int)(m_vPickPos->x - 20.0f);
    rb.x = (int)(m_vPickPos->x + 20.0f);

    lt.y = (int)(m_vPickPos->z - 10.0f);
    rb.y = (int)(m_vPickPos->z + 10.0f);

    lt.x = max(0, lt.x);
    lt.y = max(0, lt.y);
    rb.x = min(m_ptMapSize.x, rb.x);
    rb.y = min(m_ptMapSize.y, rb.y);

    D3DLOCKED_RECT heightMapLocked;
    memset(&heightMapLocked, 0, sizeof(D3DLOCKED_RECT));
    m_pHeightMapTex->LockRect(0, &heightMapLocked, NULL, NULL);
    LPBYTE pHeightDest = (LPBYTE)heightMapLocked.pBits;

    for (int y = lt.y; y < rb.y; y++)
    {
        LPDWORD pDWHeightDest = (LPDWORD)(pHeightDest + y * heightMapLocked.Pitch);
        for (int x = lt.x; x < rb.x; x++)
        {
            Color c = *(pDWHeightDest + x);
            int r, g, b;
            r = (c >> 16) & 255;
            g = (c >> 8) & 255;
            b = (c >> 0) & 255;

            Vector2 v1(x, y);
            Vector2 vLen = vPick - v1;
            float dist = D3DXVec2Length(&vLen);
            if (dist < 10.0f)
            {
                float ratio = 1.0f - (dist / 10.0f);

                r += (int)(nHeight * ratio);
                g += (int)(nHeight * ratio);
                b += (int)(nHeight * ratio);

                r = min(255, r);
                g = min(255, g);
                b = min(255, b);

                r = max(0, r);
                g = max(0, g);
                b = max(0, b);

                c = D3DCOLOR_XRGB(r, g, b);
                *(pDWHeightDest + x) = c;
            }
        }
    }
    m_pHeightMapTex->UnlockRect(0);

    memset(&heightMapLocked, 0, sizeof(D3DLOCKED_RECT));
    m_pHeightMapTex->LockRect(0, &heightMapLocked, NULL, NULL);
    pHeightDest = (LPBYTE)heightMapLocked.pBits;

    D3DLOCKED_RECT normalMapLocked;
    memset(&normalMapLocked, 0, sizeof(D3DLOCKED_RECT));
    m_pNormalMapTex->LockRect(0, &normalMapLocked, NULL, NULL);
    LPBYTE pNormalDest = (LPBYTE)normalMapLocked.pBits;

    for (int y = lt.y; y < rb.y; y++)
    {
        LPDWORD pDWHeightDest = (LPDWORD)(pHeightDest + y * heightMapLocked.Pitch);
        LPDWORD pDWNormalDest = (LPDWORD)(pNormalDest + y * normalMapLocked.Pitch);

        for (int x = lt.x; x < rb.x; x++)
        {
            Vector2 v1(x, y);
            Vector2 vLen = vPick - v1;
            float dist = D3DXVec2Length(&vLen);
            if (dist < 10.0f)
            {
                Color c;     //  normal
                LPDWORD l = pDWHeightDest + x - 1;
                LPDWORD t = pDWHeightDest + x - m_ptMapSize.x;
                LPDWORD r = pDWHeightDest + x + 1;
                LPDWORD b = pDWHeightDest + x + m_ptMapSize.x;

                Color lc = *l;
                Color tc = *t;
                Color rc = *r;
                Color bc = *b;

                Vector3 lv, tv, rv, bv;
                lv = Vector3(-1, AvgColor(lc),  0);
                tv = Vector3( 0, AvgColor(tc),  1);
                rv = Vector3( 1, AvgColor(rc),  0);
                bv = Vector3( 0, AvgColor(bc), -1);

                Vector3 ltor = rv - lv;
                Vector3 btot = tv - bv;
                Vector3 vn;
                D3DXVec3Cross(&vn, &ltor, &btot);
                D3DXVec3Normalize(&vn, &vn);

                c = NormalToColor(vn);
                *(pDWNormalDest + x) = c;
            }
        }
    }

    m_pNormalMapTex->UnlockRect(0);
    m_pHeightMapTex->UnlockRect(0);
}

void cMapTerrainTool::DrawFlat()
{
    POINT lt, rb;
    lt.x = (int)(m_vPickPos->x - 10.0f);
    rb.x = (int)(m_vPickPos->x + 10.0f);

    lt.y = (int)(m_vPickPos->z - 10.0f);
    rb.y = (int)(m_vPickPos->z + 10.0f);

    lt.x = max(0, lt.x);
    lt.y = max(0, lt.y);
    rb.x = min(m_ptMapSize.x, rb.x);
    rb.y = min(m_ptMapSize.y, rb.y);

    D3DLOCKED_RECT heightMapLocked, normalMapLocked;
    memset(&heightMapLocked, 0, sizeof(D3DLOCKED_RECT));
    memset(&normalMapLocked, 0, sizeof(D3DLOCKED_RECT));
    m_pHeightMapTex->LockRect(0, &heightMapLocked, NULL, NULL);
    m_pNormalMapTex->LockRect(0, &normalMapLocked, NULL, NULL);
    LPBYTE pHeightDest = (LPBYTE)heightMapLocked.pBits;
    LPBYTE pNormalDest = (LPBYTE)normalMapLocked.pBits;

    for (int y = lt.y; y < rb.y; y++)
    {
        LPDWORD pDWHeightDest = (LPDWORD)(pHeightDest + y * heightMapLocked.Pitch);
        LPDWORD pDWNormalDest = (LPDWORD)(pNormalDest + y * heightMapLocked.Pitch);
        bool isInCircle = false;
        for (int x = lt.x; x < rb.x; x++)
        {
            int val;
            val = 128;

            *(pDWHeightDest + x) = D3DCOLOR_XRGB(val, val, val);
            *(pDWNormalDest + x) = D3DCOLOR_XRGB(0, 255, 0);
        }
    }

    m_pNormalMapTex->UnlockRect(0);
    m_pHeightMapTex->UnlockRect(0);
}

void cMapTerrainTool::DrawAlphaMap()
{
    auto t = (LPTEXTURE9)g_pTextureManager->GetTexture("height-map");

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

    //HRESULT hr = D3DXSaveTextureToFileA("test.png",
    //    D3DXIFF_PNG,
    //    t,
    //    NULL);
}

void cMapTerrainTool::RendBrush()
{
    Matrix4 matRotY;
    ST_PC_VERTEX InitBrush[2];
    InitBrush[0].c = D3DCOLOR_XRGB(255, 255, 255);
    InitBrush[1].c = D3DCOLOR_XRGB(255, 255, 255);
   
   
    Vector3 vCenter ;                                      // vCenter : ���� ����, InitBrush ���� ���� �� ��
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
   
    float RotY = 2.0 * D3DX_PI / 60.0f;                                 // 60�� ȸ���� ����. �� ȸ�� 6��
    
    for (int i = 0; i < 60; ++i)
    {
        InitBrush[1].p.x = vCenter.x + f * cosf(RotY * (i + 1));
        InitBrush[1].p.z = vCenter.z + f * sinf(RotY * (i + 1));
        InitBrush[1].p.y = g_pMapDataManager->GetDefHeight() + 0.0001f;
   
        g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, InitBrush, sizeof(ST_PC_VERTEX));
   
        //�迭�� 1������ 0������ �����ش�
        InitBrush[0] = InitBrush[1];
    }
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
