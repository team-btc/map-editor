#pragma once
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
#include "cCreateMapDlg.h"
#include "cTerrainTab.h"
#include "cTextureTab.h"
#include "cObjectTab.h"
#include "cWaterTab.h"
#include "Resource.h"

// CMenuFormView �� ���Դϴ�.

class CMenuFormView : public CFormView
{
    DECLARE_DYNCREATE(CMenuFormView)

protected:
    CMenuFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();

public:
	cCreateMapDlg*	m_pCreateMapDlg;		// �� ���� ��â

	CTabCtrl*		m_pTabController;		// �� ��Ʈ�ѷ�
	CWnd*			m_pWndShow;				// ���� �������� �ִ� ���� ������

    E_TAB_TYPE&     m_eCurrTabType;         // ���� �� Ÿ��

	cTerrainTab*	m_pTerrainTab;			// ���� ��
	cTextureTab*	m_pTextureTab;			// �ؽ��� ��
	cWaterTab*		m_pWaterTab;			// �� ��
	cObjectTab*		m_pObjectTab;			// ������Ʈ ��

    int&            m_nDlgWidth;            // ���̾�α� ���� ������

public:
	afx_msg void OnSelectChangeTab(NMHDR *pNMHDR, LRESULT *pResult);

public:
    void Update();
	cWaterTab** GetcWaterTab() { return &m_pWaterTab; }
};


