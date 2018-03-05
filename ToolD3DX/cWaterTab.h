#pragma once


// cWaterTab 대화 상자

class cWaterTab : public CDialogEx
{
	DECLARE_DYNAMIC(cWaterTab)

private:
	// == 물 Y축 위치 ==
	CSliderCtrl*			m_pWaterPosYSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pWaterPosYEditCtl;		// 에디터 컨트롤러
	int						m_nWaterPosY;				// 물 Y축 위치

	// == 물 유속 ==
	CSliderCtrl*			m_pFlowRateSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pFlowRateEditCtl;			// 에디터 컨트롤러
	int						m_nFlowRate;				// 물 유속 값

	// == 물 진폭 ==
	CSliderCtrl*			m_pAmplitudeSliderCtl;		// 슬라이더 컨트롤러
	CEdit*					m_pAmplitudeEditCtl;		// 에디터 컨트롤러
	int						m_nAmplitude;				// 물 진폭 값

public:
	cWaterTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~cWaterTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WATER_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeWaterPosYEditer();
	afx_msg void OnDeltaposWaterPosYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawWaterPosYSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeWaterFlowRateEditer();
	afx_msg void OnDeltaposWaterFlowRateSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawWaterFlowRateSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeWaterAmplitudeEditer();
	afx_msg void OnDeltaposWaterAmplitudeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawWaterAmplitudeSlider(NMHDR *pNMHDR, LRESULT *pResult);
};
