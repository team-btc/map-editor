#pragma once


// cTerrainTab 대화 상자

class cTerrainTab : public CDialogEx
{
	DECLARE_DYNAMIC(cTerrainTab)

private:
    E_UP_DOWN&              m_eUpDown;                  // 편집 업다운 여부
	E_TERRAIN_EDIT_TYPE&	m_eEditType;				// 편집 타입
    E_TER_BRUSH_TYPE&       m_eBrushType;               // 브러쉬 타입

	// == 편집 파워 ==
	CSliderCtrl*			m_pPowerSliderCtl;		    // 슬라이더 컨트롤러
	CEdit*					m_pPowerEditCtl;			// 에디터 컨트롤러
	float&					m_fPower;				    // 파워 사이즈

	// == 편집 지형 높이 ==
	CSliderCtrl*			m_pEditHeightSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pEditHeightEditCtl;		// 에디터 컨트롤러
	float&					m_fEditHeight;				// 편집 높이값

	// == 브러쉬 크기 ==
	CSliderCtrl*			m_pBrushSizeSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pBrushSizeEditCtl;		// 에디터 컨트롤러
	float&					m_fBrushSize;				// 브러쉬 사이즈

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
    afx_msg void OnSelectUpDownRadio(UINT ID);
    afx_msg void OnSelectEditTypeRadio(UINT ID);
    afx_msg void OnSelectBrushTypeRadio(UINT ID);
    afx_msg void OnChangePowerEditer();
    afx_msg void OnDeltaposPowerSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawPowerSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeBrushSizeEditer();
	afx_msg void OnDeltaposBrushSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeEditHeightEditer();
	afx_msg void OnDeltaposEditHeightSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawEditHeightSlider(NMHDR *pNMHDR, LRESULT *pResult);

};
