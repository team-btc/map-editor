// MenuFormView.cpp : ���� �����Դϴ�.
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


// CMenuFormView �����Դϴ�.

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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

    // ���� ���ӿ� ���� �並 �������ش�.

    g_pView->m_pMainGame->SetMainFormView(this);

	// �� ũ�� ���� â ����
	m_pCreateMapDlg = new cCreateMapDlg;
	m_pCreateMapDlg->DoModal();

	//  ��Ʈ�ѵ鿡 ���� �߰� �������� �Է��ϴ� �κ�.

	// == �� ��Ʈ�ѷ� �ʱ�ȭ ==
	m_pTabController = (CTabCtrl*)GetDlgItem(IDC_MAPTOOL_TAB);
	// == �� �ʱ�ȭ ==
	m_pTerrainTab = new cTerrainTab;
	m_pTextureTab = new cTextureTab;
	m_pWaterTab = new cWaterTab;
	m_pObjectTab = new cObjectTab;

	// �� �̸� ����
	m_pTabController->InsertItem(1, "Terrain");
	m_pTabController->InsertItem(2, "Texture");
	m_pTabController->InsertItem(3, "Water/Sky");
	m_pTabController->InsertItem(4, "Object");

	// �� ũ�� ����
	CRect rect;
	m_pTabController->GetClientRect(&rect);
	
	// ù��°��
	m_pTerrainTab->Create(IDD_TERRAIN_TAB, m_pTabController);
	m_pTerrainTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	// �ι�°��
	m_pTextureTab->Create(IDD_TEXTURE_TAB, m_pTabController);
	m_pTextureTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_NOZORDER);
	// ����°��
	m_pWaterTab->Create(IDD_WATER_TAB, m_pTabController);
	m_pWaterTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_NOZORDER);
	// �׹�°��
	m_pObjectTab->Create(IDD_OBJECT_TAB, m_pTabController);
	m_pObjectTab->SetWindowPos(NULL, 5, 25, rect.Width(), rect.Height(), SWP_NOZORDER);
	// �⺻�� ù��°������ ����
	m_pWndShow = m_pTerrainTab;
    m_eCurrTabType = E_TERRAIN_TAB;
}


// CMenuFormView �޽��� ó�����Դϴ�.

// ���� Ŭ�� ���� ��
void CMenuFormView::OnSelectChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (m_pWndShow)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}

	// ���� �� �ε����� ���� �����ֱ� ����
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

// ��� ���� ������Ʈ�� (���ΰ��ӿ��� ������ ���� �Ф�)
void CMenuFormView::Update()
{
    // ���̾�α� ������ ��� ������Ʈ ��Ű��
    RECT rt;
    this->GetWindowRect(&rt);
    m_nDlgWidth = rt.right - rt.left; // �޴����� ����Ǿ� ����

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // �ٸ��͵� ������Ʈ ������!

    rand();
	m_pWaterTab->Update();
    m_pTextureTab->Update();
    m_pObjectTab->Update();
}

