#pragma once
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
#include "cCreateMapDlg.h"
#include "cTerrainTab.h"
#include "cTextureTab.h"
#include "cObjectTab.h"
#include "cWaterTab.h"
#include "Resource.h"

// CMenuFormView 폼 뷰입니다.

class CMenuFormView : public CFormView
{
    DECLARE_DYNCREATE(CMenuFormView)

protected:
    CMenuFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
    virtual ~CMenuFormView();

public:
    enum { IDD = IDD_MENUFORMVIEW };
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();

public:
	cCreateMapDlg*	m_pCreateMapDlg;		// 맵 생성 새창

	CTabCtrl*		m_pTabController;		// 탭 컨트롤러
	CWnd*			m_pWndShow;				// 현재 보여지고 있는 탭의 윈도우

    E_TAB_TYPE&     m_eCurrTabType;         // 현재 탭 타입

	cTerrainTab*	m_pTerrainTab;			// 지형 탭
	cTextureTab*	m_pTextureTab;			// 텍스쳐 탭
	cWaterTab*		m_pWaterTab;			// 물 탭
	cObjectTab*		m_pObjectTab;			// 오브젝트 탭

    int&            m_nDlgWidth;            // 다이얼로그 가로 사이즈

public:
	afx_msg void OnSelectChangeTab(NMHDR *pNMHDR, LRESULT *pResult);

public:
    void Update();
	cWaterTab** GetcWaterTab() { return &m_pWaterTab; }
};


