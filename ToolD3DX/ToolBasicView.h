
// ToolBasic00View.h : CToolBasic00View 클래스의 인터페이스
//

#pragma once
#include "ToolBasicDoc.h"
#include "cMainGame.h"

class CToolBasicView : public CView
{
protected: // serialization에서만 만들어집니다.
    CToolBasicView();
    DECLARE_DYNCREATE(CToolBasicView)

    // 특성입니다.
public:
    CToolBasicDoc * GetDocument() const;
    cMainGame* m_pMainGame;

    // 작업입니다.
public:

    // 재정의입니다.
public:
    virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

    // 구현입니다.
public:
    virtual ~CToolBasicView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // 생성된 메시지 맵 함수
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // ToolBasic00View.cpp의 디버그 버전
inline CToolBasic00Doc* CToolBasic00View::GetDocument() const
{
    return reinterpret_cast<CToolBasic00Doc*>(m_pDocument);
}
#endif

