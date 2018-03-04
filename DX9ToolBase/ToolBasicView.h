
// ToolBasic00View.h : CToolBasic00View Ŭ������ �������̽�
//

#pragma once
#include "ToolBasicDoc.h"
#include "cMainGame.h"

class CToolBasicView : public CView
{
protected: // serialization������ ��������ϴ�.
    CToolBasicView();
    DECLARE_DYNCREATE(CToolBasicView)

    // Ư���Դϴ�.
public:
    CToolBasicDoc * GetDocument() const;
    cMainGame* m_pMainGame;

    // �۾��Դϴ�.
public:

    // �������Դϴ�.
public:
    virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

    // �����Դϴ�.
public:
    virtual ~CToolBasicView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // ������ �޽��� �� �Լ�
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // ToolBasic00View.cpp�� ����� ����
inline CToolBasic00Doc* CToolBasic00View::GetDocument() const
{
    return reinterpret_cast<CToolBasic00Doc*>(m_pDocument);
}
#endif

