#include "stdafx.h"
#include "cMapTerrainTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
}

HRESULT cMapTerrainTool::Setup()
{
    // 메인 라이트
    D3DXVECTOR3 dir(1.0f, -1.0f, 0.0f);
    D3DXVec3Normalize(&dir, &dir);
    D3DLIGHT9 stLight = InitDirectional(&dir, &WHITE);
    g_pDevice->SetLight(0, &stLight);

    m_pBrush = new cBrush;
    m_pTextureShader = new cTextureShader;
    m_pWaveShader = new cWaveShader;
    m_pSkyBoxShader = new cSkyBoxShader;

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
    Vector4 v(m_vPickPos->x / m_ptMapSize.x, 0, m_vPickPos->z / m_ptMapSize.y, 1);

    // 텍스쳐 파일변경 하기
    if (m_isTex1Load)
    {
        m_pTextureShader->SetTexture1();
    }
    if (m_isTex2Load)
    {
        m_pTextureShader->SetTexture2();
    }
    if (m_isTex3Load)
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

        // 물 파일을 새로 셋팅해야 하면
        if (m_isSetWaterFile)
        {
            // 다시 변경해줌
            m_isSetWaterFile = false;
            m_pWaveShader->SetWaveTexture(g_pMapDataManager->GetWaterFilePath(), m_strWaterFileName);
        }

        // 하늘 파일을 새로 셋팅해야 하면
        if (m_isSetSkyFile)
        {
            // 다시 변경해줌
            m_isSetSkyFile = false;
            m_pSkyBoxShader->SetBox(m_strSkyFileName, g_pMapDataManager->GetSkyFilePath() + "//" + m_strSkyFileName);
        }
    }

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
        //D3DXSaveMeshToX("Map.x", m_pMesh, NULL, NULL, NULL, NULL, NULL);
        //m_pTextureShader->SaveTexture();
    }
    // 로드
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

    

    if (m_isWaterEnable)
    {
        m_pWaveShader->Render(vP);
    }

    return S_OK;
}

HRESULT cMapTerrainTool::RenderSkyBox()
{
    if (!m_pMesh)
    {
        return E_FAIL;
    }
    Vector4 vP(g_vCameraPos.x, g_vCameraPos.y, g_vCameraPos.z, 1.0f);

    m_pSkyBoxShader->Render(vP);
    return S_OK;
}

HRESULT cMapTerrainTool::RenderTextureShader()
{
    Matrix4 matW, matV, matP;
    D3DXMatrixIdentity(&matW);
   // g_pDevice->SetTransform(D3DTS_WORLD, &matW);
   // g_pDevice->SetMaterial(&WHITE_MTRL);
   // g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
   // g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
   // g_pDevice->LightEnable(0, true);
   // g_pDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
    if (!m_pMesh)
    {
        return E_FAIL;
    }
    m_pTextureShader->Render();
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
    // 지형탭
    if (eTabType == E_TERRAIN_TAB)
    {
        // 마우스 위치에 따른 버텍스 정보 가져오기
        if (m_vPickPos)
        {
            // 선택된 버텍스정보 인덱스
            m_vecSelVertex.clear();
            m_vecSelVertex = GetVertexInBrush(*m_vPickPos, m_stTerrainBrushInfo.fBrushSize);

            // 지형 편집하기
            EditTerrain();
        }
    }

    // 텍스쳐탭
    else if (eTabType == E_TEXTURE_TAB)
    {
        m_pBrush->SetType(m_stTextureBrushInfo.m_nCurrTextureIndex, m_stTextureBrushInfo.m_eDrawType);
        m_pTextureShader->Update();
    }
}

// 크기 설정한 맵 생성 (x사이즈, z사이즈, 지형 타입)
HRESULT cMapTerrainTool::CreateMap(IN E_MAP_SIZE eMapSize, IN float fHeight)
{
    // 가로 세로 사이즈 계산 후 맵 만들기
    m_ptMapSize.x = m_ptMapSize.y = (eMapSize + 1) * 64;
    m_pTextureShader->SetMapSize();
    int nSizeX = m_ptMapSize.x;
    int nSizeZ = m_ptMapSize.y;

    // ex) 512 * 512
    //   ofstream c;
    //   c.open("NewMap.raw");
    //c << (char)vec.y;

    // 버텍스 벡터
    vector<ST_PNT_VERTEX> vecPNTVertex;
    for (int n = 0; n < (nSizeX + 1) * (nSizeZ + 1); ++n)
    {
        Vector3 vec = Vector3((float)(n % (nSizeZ + 1)), fHeight, (float)(n / (nSizeZ + 1)));
        vecPNTVertex.push_back(
            ST_PNT_VERTEX(
                vec,
                Vector3(0, 1, 0),
                Vector2((float)(n % (nSizeZ + 1)) / (float)nSizeX, (n / (nSizeZ + 1) / (float)nSizeZ))));
    }

    // 인덱스 벡터
    //   1 3
    //   0 2
    //  0 , 1 , 2,  // 2 , 1 , 3 순서!!
    vector<DWORD> vecVertexIndex;
    for (DWORD z = 0; z < (DWORD)nSizeZ; ++z)
    {
        for (DWORD x = 0; x < (DWORD)nSizeX; ++x)
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

    // 매쉬 정보 셋팅
    // == 매쉬 생성, 기록, 최적화
    // 생성
    D3DXCreateMeshFVF((DWORD)vecVertexIndex.size() / 3, (DWORD)vecPNTVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
        ST_PNT_VERTEX::FVF, g_pDevice, &m_pMesh);

    // 버텍스 버퍼 기록
    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);
    memcpy(pV, &vecPNTVertex[0], vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));
    m_pMesh->UnlockVertexBuffer();

    // 인덱스 버퍼 기록
    DWORD* pI = NULL;
    m_pMesh->LockIndexBuffer(NULL, (LPVOID*)&pI);
    memcpy(pI, &vecVertexIndex[0], vecVertexIndex.size() * sizeof(DWORD));
    m_pMesh->UnlockIndexBuffer();

    // 속성 버퍼 기록
    DWORD* pA = NULL;
    m_pMesh->LockAttributeBuffer(NULL, &pA);
    for (int i = 0; i < vecVertexIndex.size() / 3; ++i) // 페이스별로 하나씩 기록
        pA[i] = (DWORD)0;
    m_pMesh->UnlockAttributeBuffer();

    // 메쉬 최적화 : 버텍스 개수 만큼 인접정보를 담을 공간을 확보
    vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);

    m_pMesh->GenerateAdjacency(D3DX_16F_EPSILON, &vecAdjBuf[0]);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
        &vecAdjBuf[0], 0, 0, 0);

    m_pTextureShader->SetMesh(m_pMesh);

    m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), g_pDevice, &m_pWMesh);

    m_pWaveShader->SetMesh(m_pWMesh);

    return S_OK;
}

// 맵 데이터 저장
void cMapTerrainTool::SaveMapData(string strFilePath, string strFileTitle)
{
    string str = strFilePath + "/" + strFileTitle + ".x";
    // 지형 매쉬 저장
    D3DXSaveMeshToX(str.c_str(), m_pMesh, NULL, NULL, NULL, NULL, D3DXF_FILEFORMAT_COMPRESSED);
    // 물 매쉬 저장
    str = strFilePath + "/" + strFileTitle + "-water.x";
    D3DXSaveMeshToX(str.c_str(), m_pWMesh, NULL, NULL, NULL, NULL, D3DXF_FILEFORMAT_COMPRESSED);
    // 택스처 png 저장
    m_pTextureShader->SaveTexture(strFilePath, strFileTitle);
}

// 맵 데이터 로드
void cMapTerrainTool::LoadMapData(string sFilePath, string sFileTitle)
{
    // 매쉬 지우기
    SAFE_RELEASE(m_pMesh);

    // 매쉬 로드
    string sFullPath = sFilePath + "\\" + sFileTitle + ".x";
    D3DXLoadMeshFromX(sFullPath.c_str(), D3DXMESH_VB_MANAGED, g_pDevice, NULL, NULL, NULL, NULL, &m_pMesh);

    // 택스처 png 로드
    string sFullPathPng = sFilePath + "\\" + sFileTitle;
    m_pTextureShader->SetMapSize(&sFullPathPng);
    // 텍스쳐 매쉬 세팅
    m_pTextureShader->SetMesh(m_pMesh);
    // 물 셋팅
    m_pWaveShader->SetWaveTexture("Shader/Texture", m_strWaterFileName);
    m_pWaveShader->SetShader(m_stWaterInfo.fHeight, m_stWaterInfo.fWaveHeight, m_stWaterInfo.fHeightSpeed, m_stWaterInfo.fUVSpeed, m_stWaterInfo.fFrequency, m_stWaterInfo.fTransparent);
    // 하늘 셋팅
    m_pSkyBoxShader->SetBox(m_strSkyFileName, "Shader/Texture/" + m_strSkyFileName);
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
                fHeightResult = fBaseHeight + (fHeightDiff * ((cosf(fRatio * D3DX_PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
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
                fHeightResult = fCenterHeight + (fHeightDiff * ((cosf(fRatio * D3DX_PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
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
                fHeightResult = fDefaultPlusHeight * ((cosf(fRatio * D3DX_PI) + 1.0f) * 0.5f); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
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
                fHeightResult = fDefaultPlusHeight * ((cosf(fRatio * D3DX_PI) + 1.0f) * 0.5f); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
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
                fHeightResult = fBaseHeight + (fHeightDiff * ((cosf(fRatio * D3DX_PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
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
                fHeightResult = fCenterHeight + (fHeightDiff * ((cosf(fRatio * D3DX_PI) + 1.0f) * 0.5f)); //cosf()값이  -1 ~ 1 사이의 숫자가 나옴 0 ~ 1 사이값으로 변경 후 계산!
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

// 지형 다듬기(경사면 부드럽게)
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

    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);

    for (int i = 0; i < vecSelVertex.size(); ++i)
    {
        // 버텍스와 픽킹 지점과의 거리(y값은 제외)
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

// 브러쉬 안에 있는 버텍스 인덱스 벡터
vector<int> cMapTerrainTool::GetVertexInBrush(Vector3 vPickPos, float fRadius)
{
    // 브러쉬 영역을 임의로 구분 한다. (정사각형 모양으로)
    int nMinX = (int)(vPickPos.x - fRadius);
    if (nMinX < 0)
    {
        nMinX = 0;
    }

    int nMaxX = (int)(vPickPos.x + fRadius) + 1;
    if (nMaxX > m_ptMapSize.x)
    {
        nMaxX = m_ptMapSize.x;
    }

    int nMinZ = (int)(vPickPos.z - fRadius);
    if (nMinZ < 0)
    {
        nMinZ = 0;
    }

    int nMaxZ = (int)(vPickPos.z + fRadius + 1);
    if (nMaxZ > m_ptMapSize.y)
    {
        nMaxZ = m_ptMapSize.y;
    }

    ST_PNT_VERTEX* pV = NULL;
    m_pMesh->LockVertexBuffer(NULL, (LPVOID*)&pV);

    vector<int> vecSelVertex;
    // 브러쉬(원) 안에 위치하는 버텍스의 인덱스를 벡터에 담는다.
    for (int z = nMinZ; z < nMaxZ; ++z)
    {
        for (int x = nMinX; x < nMaxX; ++x)
        {
            int nIndex = (z * (m_ptMapSize.y + 1)) + x;
            float fLength = GetLength(Vector2(pV[nIndex].p.x, pV[nIndex].p.z),
                Vector2(vPickPos.x, vPickPos.z));

            // 픽킹위치와 점 위치의 거리가 반지름보다 짧으면
            if (fLength < fRadius)
            {
                vecSelVertex.push_back(nIndex);
            }
        }
    }

    m_pMesh->UnlockVertexBuffer();

    return vecSelVertex;
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