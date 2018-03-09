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

	// �޽��� �׸���
	g_pDevice->SetTexture(0, (LPTEXTURE9)g_pTextureManager->GetTexture("default"));
    m_pMesh->DrawSubset(0);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

    RendBrush();
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
            // ���õ� ������ �ε���
            m_vecSelVertex.clear();
            m_vecSelVertex = GetVertexInBrush(*m_vPickPos, m_stTerrainBrushInfo.fBrushSize);

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
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN E_GROUND_TYPE eGroundType, IN float fHeight, IN float isWalkable)
{
    // ���� ���� ������ ��� �� �� �����
    m_ptMapSize.x = m_ptMapSize.y = (eMapSize + 1) * 64;

    int nSizeX = m_ptMapSize.x;
    int nSizeZ = m_ptMapSize.y;

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
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vec, Vector3(0, 1, 0), Vector2((n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
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

// ���� �ٵ��
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
    for (int i = 0; i < vecSelVertex.size(); ++i)
    {
        // ���ؽ��� ��ŷ �������� �Ÿ�(y���� ����)
        float fLength = GetLength(Vector2(m_vecPNTVertex[vecSelVertex[i]].p.x, m_vecPNTVertex[vecSelVertex[i]].p.z), Vector2(vPickPos.x, vPickPos.z));

        if (fLength < fNearLenght)
        {
            nNearIndex = vecSelVertex[i];
            fNearLenght = fLength;
        }
    }
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

    vector<int> vecSelVertex;
    // �귯��(��) �ȿ� ��ġ�ϴ� ���ؽ��� �ε����� ���Ϳ� ��´�.
    for (int z = nMinZ; z < nMaxZ; ++z)
    {
        for (int x = nMinX; x < nMaxX; ++x)
        {
            int nIndex = (z * (m_ptMapSize.y + 1)) + x;
            float fLength = GetLength(Vector2(m_vecPNTVertex[nIndex].p.x, m_vecPNTVertex[nIndex].p.z),
                Vector2(vPickPos.x, vPickPos.z));

            // ��ŷ��ġ�� �� ��ġ�� �Ÿ��� ���������� ª����
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
