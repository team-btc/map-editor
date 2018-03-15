#include "stdafx.h"
#include "cMapTool.h"
#include "cMapTerrainTool.h"
#include "cMapObjectTool.h"
#include "cRay.h"
#include "MenuFormView.h"
#include "MainFrm.h"
#include "cWaterTab.h"

cMapTool::cMapTool()
    : m_pTerrainTool(NULL)
    , m_pObjectTool(NULL)
    , m_eCurrTabType(g_pMapDataManager->GetTabType())
    , m_eMapSize(g_pMapDataManager->GetMapSize())
    , m_fDefaultHeight(g_pMapDataManager->GetDefHeight())
    , m_isCreateMap(g_pMapDataManager->GetCreateMap())
    , m_isTex1Load(g_pMapDataManager->GetIsTex1Load())
    , m_isTex2Load(g_pMapDataManager->GetIsTex2Load())
    , m_isTex3Load(g_pMapDataManager->GetIsTex3Load())
    , m_strTex1FilePath(g_pMapDataManager->GetTex1FilePath())
    , m_strTex1FileName(g_pMapDataManager->GetTex1FileName())
    , m_strTex2FilePath(g_pMapDataManager->GetTex2FilePath())
    , m_strTex2FileName(g_pMapDataManager->GetTex2FileName())
    , m_strTex3FilePath(g_pMapDataManager->GetTex3FilePath())
    , m_strTex3FileName(g_pMapDataManager->GetTex3FileName())
    , m_pRay(NULL)
    , m_vPickPos(0, 0, 0)
{
    g_pMapDataManager->SetMapTool(this);
}
cMapTool::~cMapTool()
{
    // �޸� ���� �����ϸ� �̺κ��� ���� 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    SAFE_RELEASE(m_pTerrainTool);
    SAFE_RELEASE(m_pObjectTool);
}

HRESULT cMapTool::Setup()
{
    m_pRay = new cRay;

    m_eCurrTabType = E_CREATE_TAB;
    m_eMapSize = DEFAULT_MAP_SIZE;
    m_fDefaultHeight = DEFAULT_HEIGHT;
    m_isTex1Load = false;
    m_isTex2Load = false;
    m_isTex3Load = false;
    m_strTex1FilePath = "Texture";
    m_strTex1FileName = "Soil.jpg";
    m_strTex2FilePath = "Texture";
    m_strTex2FileName = "Grass.jpg";
    m_strTex3FilePath = "Texture";
    m_strTex3FileName = "Stone.jpg";

    m_pTerrainTool = new cMapTerrainTool;
    m_pTerrainTool->Setup();
    m_pTerrainTool->SetPickPos(&m_vPickPos);

    m_pObjectTool = new cMapObjectTool;
    m_pObjectTool->Setup();
    m_pObjectTool->SetPickPos(&m_vPickPos);
    m_pObjectTool->SetTerrainTool(m_pTerrainTool);

    return S_OK;
}

HRESULT cMapTool::Update()
{
    GetPtMouse();

    if (m_isCreateMap)
    {
        CreateMap();
    }
    if (m_pTerrainTool)
    {
        m_pTerrainTool->Update();
    }
    if (m_pObjectTool)
    {
        m_pObjectTool->Update();
    }

    // ���� ���콺�� Ŭ�� �߰�, Ŭ���̾�Ʈ ���� �ȿ� �ִ� ���� Ŭ��������
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && IsPickMap())
    {
        if (m_pTerrainTool && (m_eCurrTabType == E_TERRAIN_TAB || m_eCurrTabType == E_TEXTURE_TAB))
        {
            m_pTerrainTool->OnceLButtonDown(m_eCurrTabType);
        }
        else if (m_pObjectTool && m_eCurrTabType == E_OBJECT_TAB)
        {
            m_pObjectTool->OnceLButtonDown(m_eCurrTabType);
        }
    }

    // ���� ���콺�� ��� ������ �ְ�, ���콺�� Ŭ���̾�Ʈ ���� �ȿ� ������
    if (g_pKeyManager->isStayKeyDown(VK_LBUTTON) && IsPickMap())
    {
        if (m_pTerrainTool && (m_eCurrTabType == E_TERRAIN_TAB || m_eCurrTabType == E_TEXTURE_TAB))
        {
            m_pTerrainTool->StayLButtonDown(m_eCurrTabType);
        }
        else if (m_pObjectTool && m_eCurrTabType == E_OBJECT_TAB)
        {
            m_pObjectTool->StayLButtonDown();
        }
    }

    return S_OK;
}

HRESULT cMapTool::Render()
{
    if (m_pTerrainTool)
    {
        m_pTerrainTool->RenderSkyBox();
    }

    if (m_pObjectTool)
    {
        m_pObjectTool->Render();
    }

    if (m_pTerrainTool)
    {
        m_pTerrainTool->Render();
    }



    RendPtMouse();
    return S_OK;
}

// ������ �⺻ �������� �� �����
HRESULT cMapTool::CreateMap()
{
    m_isCreateMap = false;

    if (m_pTerrainTool)
    {
        m_pTerrainTool->CreateMap(m_eMapSize, m_fDefaultHeight);

    }

    return S_OK;
}

json cMapTool::SaveByJson(string strFilePath, string strFileTitle)
{
    json save;
    ofstream o;
    o.open(strFilePath + "/" + strFileTitle + ".json");

    // �ʻ����� ����
    save["map"]["size"] = (int)g_pMapDataManager->GetMapSize();

    save["texture"]["tex1"]["key"] = g_pMapDataManager->GetTex1FileName();
    save["texture"]["tex1"]["density"] = g_pMapDataManager->GetTex1Density();
    save["texture"]["tex2"]["key"] = g_pMapDataManager->GetTex2FileName();
    save["texture"]["tex2"]["density"] = g_pMapDataManager->GetTex2Density();
    save["texture"]["tex3"]["key"] = g_pMapDataManager->GetTex3FileName();
    save["texture"]["tex3"]["density"] = g_pMapDataManager->GetTex3Density();

    save["water"]["enable"] = g_pMapDataManager->GetIsMakeWater();
    save["water"]["file_name"] = g_pMapDataManager->GetWaterFileName();
    save["water"]["file_path"] = g_pMapDataManager->GetWaterFilePath();
    save["water"]["height"] = g_pMapDataManager->GetWaterHeight();
    save["water"]["uvspeed"] = g_pMapDataManager->GetWaterUVSpeed();
    save["water"]["waveheight"] = g_pMapDataManager->GetWaterWaveHeight();
    save["water"]["heightspeed"] = g_pMapDataManager->GetWaterHeightSpeed();
    save["water"]["frequency"] = g_pMapDataManager->GetWaterFrequency();
    save["water"]["transparent"] = g_pMapDataManager->GetWaterTransparent();
    save["water"]["density"] = g_pMapDataManager->GetWaterDensity();


    save["skybox"]["key"] = g_pMapDataManager->GetSkyFileName();

    // ������Ʈ ����
    m_pObjectTool->SaveByJson(save);

    // �Ž�x, �ؽ���png ����
    m_pTerrainTool->SaveMapData(strFilePath, strFileTitle);

    string c;
    c = save.dump(4);
    o << c;
    o.close();

    return save;
}

void cMapTool::LoadByJson(string sFilePath, string sFileTitle)
{
    // ���̽� ������ �ҷ��ͼ� ������ ����!!!
    json jLoad;
    ifstream i;
    i.open(sFilePath + "\\" + sFileTitle + ".json");
    i >> jLoad;
    i.close();

    //======= �ʻ�����
    E_MAP_SIZE size = (E_MAP_SIZE)jLoad["map"]["size"];
    g_pMapDataManager->GetMapSize() = size;
    CreateMap();

    //======== �ؽ��� 1, 2, 3 ���� ===========//
    // �ؽ���1
    string tex1 = jLoad["texture"]["tex1"]["key"];
    float den1 = jLoad["texture"]["tex1"]["density"];
    g_pMapDataManager->SetTex1FileName(tex1);
    g_pMapDataManager->SetTex1Density(den1);
    g_pMapDataManager->GetTex1DensitySliderCtl()->SetPos((int)den1);
    g_pMapDataManager->GetTex1DensityEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetTex1DensityEditCtl()->SetFocus();
    g_pMapDataManager->GetTex1DensityEditCtl()->SetSel(-1, -1);

    // �ؽ���2
    string tex2 = jLoad["texture"]["tex2"]["key"];
    float den2 = jLoad["texture"]["tex2"]["density"];
    g_pMapDataManager->SetTex2FileName(tex2);
    g_pMapDataManager->SetTex2Density(den2);
    g_pMapDataManager->GetTex2DensitySliderCtl()->SetPos((int)den2);
    g_pMapDataManager->GetTex2DensityEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetTex2DensityEditCtl()->SetFocus();
    g_pMapDataManager->GetTex2DensityEditCtl()->SetSel(-1, -1);

    // �ؽ���3
    string tex3 = jLoad["texture"]["tex3"]["key"];
    float den3 = jLoad["texture"]["tex3"]["density"];
    g_pMapDataManager->SetTex3FileName(tex3);
    g_pMapDataManager->SetTex3Density(den3);
    g_pMapDataManager->GetTex3DensitySliderCtl()->SetPos((int)den3);
    g_pMapDataManager->GetTex3DensityEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetTex3DensityEditCtl()->SetFocus();
    g_pMapDataManager->GetTex3DensityEditCtl()->SetSel(-1, -1);
    m_pTerrainTool->SetTerrainTexture();

    //============ �� ���� =============//
    bool bMakeWater = jLoad["water"]["enable"];
    g_pMapDataManager->SetIsMakeWater(bMakeWater);
    g_pMapDataManager->GetWaterMakeCheck()->SetCheck(bMakeWater);

    string str = jLoad["water"]["file_name"];
    g_pMapDataManager->SetWaterFileName(str);
    string str2 = jLoad["water"]["file_path"];
    g_pMapDataManager->SetWaterFilePath(str2);
    // ���� �ؽ��� ����
    m_pTerrainTool->SetWave(g_pMapDataManager->GetWaterFileName(), g_pMapDataManager->GetWaterFilePath());

    // ������
    float wHeight = jLoad["water"]["height"];
    g_pMapDataManager->SetWaterHeight(wHeight);
    g_pMapDataManager->GetWaterHeightSliderCtl()->SetPos((int)wHeight);
    g_pMapDataManager->GetWaterHeightEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetWaterHeightEditCtl()->SetFocus();
    g_pMapDataManager->GetWaterHeightEditCtl()->SetSel(-1, -1);

    // �� UV
    float fUV = jLoad["water"]["uvspeed"];
    g_pMapDataManager->SetWaterUVSpeed(fUV);
    g_pMapDataManager->GetWaterUVSpeedSliderCtl()->SetPos((int)fUV);
    char uv[10];
    sprintf_s(uv, -1, "%.2f", fUV);
    g_pMapDataManager->GetWaterUVSpeedEditCtl()->SetWindowTextA(uv);
    g_pMapDataManager->GetWaterUVSpeedEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetWaterUVSpeedEditCtl()->SetFocus();
    g_pMapDataManager->GetWaterUVSpeedEditCtl()->SetSel(-1, -1);

    // �� �ĵ� ����
    float fWave = jLoad["water"]["waveheight"];
    g_pMapDataManager->SetWaterWaveHeight(fWave);
    g_pMapDataManager->GetWaveHeightSliderCtl()->SetPos((int)(fWave * 10.0f));
    char wave[10];
    sprintf_s(wave, -1, "%.1f", fWave);
    g_pMapDataManager->GetWaveHeightEditCtl()->SetWindowTextA(wave);
    g_pMapDataManager->GetWaveHeightEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetWaveHeightEditCtl()->SetFocus();
    g_pMapDataManager->GetWaveHeightEditCtl()->SetSel(-1, -1);

    // �� �ĵ� ���ǵ� 
    float fWaveSpeed = jLoad["water"]["heightspeed"];
    g_pMapDataManager->SetWaterHeightSpeed(fWaveSpeed);
    g_pMapDataManager->GetHeightSpeedSliderCtl()->SetPos((int)(fWaveSpeed * 10.0f));
    char waveHeight[10];
    sprintf_s(waveHeight, -1, "%.1f", fWaveSpeed);
    g_pMapDataManager->GetHeightSpeedEditCtl()->SetWindowTextA(waveHeight);
    g_pMapDataManager->GetHeightSpeedEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetHeightSpeedEditCtl()->SetFocus();
    g_pMapDataManager->GetHeightSpeedEditCtl()->SetSel(-1, -1);

    // �� ���� ���� 
    float fFreq = jLoad["water"]["frequency"];
    g_pMapDataManager->SetWaterFrequency(fFreq);
    g_pMapDataManager->GetFrequencySliderCtl()->SetPos((int)(fFreq * 10.0f));
    char freq[10];
    sprintf_s(freq, -1, "%.1f", fFreq);
    g_pMapDataManager->GetFrequencyEditCtl()->SetWindowTextA(freq);
    g_pMapDataManager->GetFrequencyEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetFrequencyEditCtl()->SetFocus();
    g_pMapDataManager->GetFrequencyEditCtl()->SetSel(-1, -1);

    // �� ����
    float fTrans = jLoad["water"]["transparent"];
    g_pMapDataManager->SetWaterTransparent(fTrans);
    g_pMapDataManager->GetTransparentSliderCtl()->SetPos((int)(fTrans * 10.0f));
    char trans[10];
    sprintf_s(trans, -1, "%.1f", fTrans);
    g_pMapDataManager->GetTransparentEditCtl()->SetWindowTextA(trans);
    g_pMapDataManager->GetTransparentEditCtl()->SetSel(0, -1);
    g_pMapDataManager->GetTransparentEditCtl()->SetFocus();
    g_pMapDataManager->GetTransparentEditCtl()->SetSel(-1, -1);
    //=======================================================

    string skyText = jLoad["skybox"]["key"];
    g_pMapDataManager->SetSkyFileName(skyText);
    m_pTerrainTool->SetSkyBoxTexture();

    // �ɵ�����, �Ž�x, �ؽ���png �ε�

    // ��ī�� �ڽ� �κ� �����ϱ� 
    m_pTerrainTool->LoadMapData(sFilePath, sFileTitle);
    m_pObjectTool->LoadByJson(sFilePath, sFileTitle);
}

// ���콺 ��ġ ��������
HRESULT cMapTool::GetPtMouse()
{
    if (m_pTerrainTool->GetMesh() == NULL)
    {
        return E_FAIL;
    }

    *m_pRay = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

    BOOL isHit = false;
    float fDist;
    D3DXIntersectSubset(m_pTerrainTool->GetMesh(), 0, &m_pRay->m_vOrg, &m_pRay->m_vDir, &isHit, NULL, NULL, NULL, &fDist, NULL, NULL);
    if (isHit)
    {
        m_vPickPos = m_pRay->m_vOrg + m_pRay->m_vDir * fDist;
    }

    return S_OK;
}

// ���콺 ��ġ ���
void cMapTool::RendPtMouse()
{
    RECT rt = { 0, 30, W_WIDTH, W_HEIGHT };
    string s = "MousePos : ";
    s = s + to_string((int)g_ptMouse.x) + " , " + to_string((int)g_ptMouse.y);
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));

    rt = { 0, 45, W_WIDTH, W_HEIGHT };
    s = "PickPos : ";
    s = s + to_string((int)m_vPickPos.x) + " , " + to_string((int)m_vPickPos.y) + " , " + to_string((int)m_vPickPos.z);
    g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
        s.c_str(),
        -1,
        &rt,
        DT_LEFT | DT_NOCLIP,
        D3DCOLOR_XRGB(128, 128, 128));
}

// ���콺�� Ŭ���̾�Ʈ ���� �ȿ��� ���� Ŭ�� �ߴ��� üũ
bool cMapTool::IsPickMap()
{
    RECT rtClient;
    GetClientRect(g_hWnd, &rtClient);

    POINT ptCurrMouse;
    GetCursorPos(&ptCurrMouse); // ������ ���� ���콺 ��ǥ�� �Ѱ���

    ScreenToClient(g_hWnd, &ptCurrMouse); // ������ ���� ���콺 ��ǥ�� Ŭ���̾�Ʈ ���� ��ǥ�� �ٲ���!

                                          // MFC���� �۾�ǥ���� ũ�� ���ϴ� ���! (�۾�ǥ���� ������ �ڵ�, ũ�� ����)
    HWND hWndTrayWnd = ::FindWindow("Shell_TrayWnd", "");
    RECT rt;
    int nTrayHeight = 0;
    if (hWndTrayWnd)
    {
        ::GetWindowRect(hWndTrayWnd, &rt);
        nTrayHeight = rt.bottom - rt.top;
    }

    // �۾�ǥ���� ���� ��ŭ ���콺��ġ�� �ű��, Ŭ���̾�Ʈ ������ ���δ�.
    ptCurrMouse.y -= nTrayHeight;
    rtClient.bottom -= nTrayHeight;

    // ���̾�α� �ʺ�ŭ Ŭ���̾�Ʈ ������ ���δ�.
    int nDlgWidth = g_pMapDataManager->GetDlgWidth();
    rtClient.right -= nDlgWidth;

    bool isPick = false;

    // ���콺�� Ŭ���̾�Ʈ ���� �ȿ� �ִ��� üũ
    if (ptCurrMouse.x > rtClient.left && ptCurrMouse.x < rtClient.right
        && ptCurrMouse.y > rtClient.top && ptCurrMouse.y < rtClient.bottom)
    {
        // ���� Ŭ�� �ߴ��� üũ
        BOOL isHit = false;
        float fDist = 0;
        D3DXIntersectSubset(m_pTerrainTool->GetMesh(), 0, &m_pRay->m_vOrg, &m_pRay->m_vDir, &isHit, NULL, NULL, NULL, &fDist, NULL, NULL);
        if (isHit)
        {
            m_vPickPos = m_pRay->m_vOrg + m_pRay->m_vDir * fDist;
            isPick = true;
        }
    }

    return isPick;
}
