#pragma once


// cCreateMapDlg 대화 상자

class cCreateMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(cCreateMapDlg)

private:
	CComboBox*			m_pComboController;			// 콤보박스 컨트롤러
	E_MAP_SIZE&			m_eMapSize;			        // 맵 사이즈 인덱스

	CSliderCtrl*		m_pSliderController;		// 슬라이더 컨트롤러
	CEdit*				m_pEditController;			// 에디터 컨트롤러
	float&				m_fDefaultHeight;			// 기본 높이 값

	E_GROUND_TYPE&		m_eDefGroundType;			// 기본 텍스쳐 인덱스

	CStatic*			m_pPictureController[5];	// 픽쳐 컨트롤러
	CBitmap				m_Bitmap[5];				// 텍스쳐 비트맵

	CButton*			m_pWalkableCheck;			// 걸을 수 있는지 여부 체크박스
	bool&				m_isDefWalkable;			// 걸을 수 있는지 여부 기본값

    bool&               m_isCreateMap;              // 맵 생성 여부

public:
	cCreateMapDlg(CWnd* pParent = nullptr);			// 표준 생성자입니다.
	virtual ~cCreateMapDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDefaultHeightChange();
	afx_msg void OnMapSizeSelectchange();
	afx_msg void OnDefaultHeightCustomdrawDefaultHeight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposDefaultHeightSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelectTextureRadio(UINT ID);
	afx_msg void OnClickCreateMapBnt();
	afx_msg void OnClickWalkableCheck();
};
