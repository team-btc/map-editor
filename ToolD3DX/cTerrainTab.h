#pragma once


// cTerrainTab 대화 상자

class cTerrainTab : public CDialogEx
{
	DECLARE_DYNAMIC(cTerrainTab)

private:
	E_TERRAIN_EDIT_TYPE&	m_eEditType;				// 편집 타입

	// == 지형 높이 증가 값 ==
	CSliderCtrl*			m_pIncrementSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pIncrementEditCtl;		// 에디터 컨트롤러
	float&					m_fIncrement;				// 높이 증가 값

	// == 브러쉬 크기 ==
	CSliderCtrl*			m_pBrushSizeSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pBrushSizeEditCtl;		// 에디터 컨트롤러
	float&					m_fBrushSize;				// 브러쉬 사이즈

	// == 평지 크기 ==
	CSliderCtrl*			m_pFlatSizeSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pFlatSizeEditCtl;			// 에디터 컨트롤러
	float&					m_fFlatSize;				// 평지 사이즈

public:
	cTerrainTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~cTerrainTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAIN_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickIncreaseRadio();
	afx_msg void OnChangeIncrementEditer();
	afx_msg void OnDeltaposIncrementSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawIncrementSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeBrushSizeEditer();
	afx_msg void OnDeltaposBrushSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeFlatSizeEditer();
	afx_msg void OnDeltaposFlatSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawFlatSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
};
