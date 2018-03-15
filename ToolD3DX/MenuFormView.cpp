// MenuFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToolBasic.h"
#include "MenuFormView.h"

#include "ToolBasicView.h"

// CMenuFormView

extern CToolBasicView *g_pView;

IMPLEMENT_DYNCREATE(CMenuFormView, CFormView)

CMenuFormView::CMenuFormView()
    : CFormView(CMenuFormView::IDD)
    , m_pCreateMapDlg(NULL)
    , m_pTabController(NULL)
    , m_pWndShow(NULL)
    , m_pTerrainTab(NULL)
    , m_pTextureTab(NULL)
    , m_pWaterTab(NULL)
    , m_pObjectTab(NULL)
    , m_eCurrTabType(g_pMapDataManager->GetTabType())
    , m_nDlgWidth(g_pMapDataManager->GetDlgWidth())
{

}

CMenuFormView::~CMenuFormView()
{
}

void CMenuFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMenuFormView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAPTOOL_TAB, &CMenuFormView::OnSelectChangeTab)
END_MESSAGE_MAP()


// CMenuFormView 진단입니다.

#ifdef _DEBUG
void CMenuFormView::AssertValid() const
{
    CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMenuFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CMenuFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

    // 메인 게임에 메인 뷰를 연결해준다.

    g_pView->m_pMainGame->SetMainFormView(this);

	// 맵 크기 설정 창 띄우기
	m_pCreateMapDlg = new cCreateMapDlg;
	m_pCreateMapDlg->DoModal();

	//  컨트롤들에 대한 추가 설정값을 입력하는 부분.

	// == 탭 컨트롤러 초기화 ==
	m_pTabController = (CTabCtrl*)GetDlgItem(IDC_MAPTOOL_TAB);
	// == 탭 초기화 ==
	m_pTerrainTab = new cTerrainTab;
	m_pTextureTab = new cTextureTab;
	m_pWaterTab = new cWaterTab;
	m_pObjectTab = new cObjectTab;

	// 탭 이름 셋팅
	m_pTabController->InsertItem(1, "Terrain");
	m_pTabController->InsertItem(2, "Texture");
	m_pTabController->InsertItem(3, "Water/Sky");
	m_pTabController->InsertItem(4, "Object");

	// 탭 크기 셋팅
	CRect rect;
	m_pTabController->GetClientRect(&rect);
	
	// 첫번째탭
	m_pTerrainTab->Create(IDD_TERRAIN_TAB, m_pTabController);
	m_pTerrainTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	// 두번째탭
	m_pTextureTab->Create(IDD_TEXTURE_TAB, m_pTabController);
	m_pTextureTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_NOZORDER);
	// 세번째탭
	m_pWaterTab->Create(IDD_WATER_TAB, m_pTabController);
	m_pWaterTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_NOZORDER);
	// 네번째탭
	m_pObjectTab->Create(IDD_OBJECT_TAB, m_pTabController);
	m_pObjectTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_NOZORDER);
	// 기본은 첫번째탭으로 설정
	m_pWndShow = m_pTerrainTab;
    m_eCurrTabType = E_TERRAIN_TAB;
}


// CMenuFormView 메시지 처리기입니다.

// 탭을 클릭 했을 때
void CMenuFormView::OnSelectChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_pWndShow)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}

	// 현재 탭 인덱스에 따라 보여주기 변경
	switch (m_pTabController->GetCurSel())
	{
	case 0:
		m_pTerrainTab->ShowWindow(SW_SHOW);
		m_pWndShow = m_pTerrainTab;
        m_eCurrTabType = E_TERRAIN_TAB;
		break;
	case 1:
		m_pTextureTab->ShowWindow(SW_SHOW);
		m_pWndShow = m_pTextureTab;
        m_eCurrTabType = E_TEXTURE_TAB;
		break;
	case 2:
		m_pWaterTab->ShowWindow(SW_SHOW);
		m_pWndShow = m_pWaterTab;
        m_eCurrTabType = E_WATER_TAB;
		break;
	case 3:
		m_pObjectTab->ShowWindow(SW_SHOW);
		m_pWndShow = m_pObjectTab;
        m_eCurrTabType = E_OBJECT_TAB;
		break;
	default:
		break;
	}

	*pResult = 0;
}

// 계속 도는 업데이트문 (메인게임에서 돌리고 있음 ㅠㅠ)
void CMenuFormView::Update()
{
    // 다이얼로그 사이즈 계속 업데이트 시키기
    RECT rt;
    this->GetWindowRect(&rt);
    m_nDlgWidth = rt.right - rt.left; // 메니져와 연결되어 있음

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 다른것도 업데이트 돌리기!

    rand();
	m_pWaterTab->Update();
    m_pTextureTab->Update();
    m_pObjectTab->Update();
}

