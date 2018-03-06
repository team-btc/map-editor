
// ToolBasic00View.cpp : CToolBasic00View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ToolBasic.h"
#endif

#include "ToolBasicDoc.h"
#include "ToolBasicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToolBasic00View

IMPLEMENT_DYNCREATE(CToolBasicView, CView)

BEGIN_MESSAGE_MAP(CToolBasicView, CView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_ERASEBKGND()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()

// CToolBasic00View ����/�Ҹ�

CToolBasicView::CToolBasicView()
{
    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.


}

CToolBasicView::~CToolBasicView()
{
    m_pMainGame->Cleanup();
}

BOOL CToolBasicView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
    //  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

    return CView::PreCreateWindow(cs);
}

// CToolBasic00View �׸���

void CToolBasicView::OnDraw(CDC* /*pDC*/)
{
    CToolBasicDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CToolBasicView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
     // ClientToScreen(&point);
     // OnContextMenu(this, point);
}

void CToolBasicView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CToolBasic00View ����

#ifdef _DEBUG
void CToolBasicView::AssertValid() const
{
    CView::AssertValid();
}

void CToolBasicView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CToolBasicDoc* CToolBasicView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBasicDoc)));
    return (CToolBasicDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolBasic00View �޽��� ó����


void CToolBasicView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    m_pMainGame = new cMainGame;
    m_pMainGame->InitD3D(m_hWnd);
}


BOOL CToolBasicView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    return FALSE;
}

void CToolBasicView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

    g_ptMouse = point;

    //RECT rtClient, rtWindow;
    //GetWindowRect(&rtWindow);
    ////GetClientRect(&rtClient);
    //
    //
    //CPoint pos = { rtWindow.left, rtWindow.top };
    //
    //g_ptMouse.x = (rtWindow.right - rtWindow.left) - rtClient.right;
    //g_ptMouse.y = (rtWindow.bottom - rtWindow.top) - rtClient.bottom;

    CView::OnMouseMove(nFlags, point);
}


void CToolBasicView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // �� ����� ����Ϸ��� Windows Vista �̻��� �־�� �մϴ�.
    // _WIN32_WINNT ��ȣ�� 0x0600���� ũ�ų� ���ƾ� �մϴ�.
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

    g_nWheelDelta = (int)zDelta;

    CView::OnMouseHWheel(nFlags, zDelta, pt);
}
