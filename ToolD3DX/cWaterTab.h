#pragma once

// cWaterTab 대화 상자

class cWaterTab : public CDialogEx
{
    DECLARE_DYNAMIC(cWaterTab)

private:
	// == 물 선택 체크 박스
	CButton*&				m_pWaterMakeCheck;
    // == 물 높이 ==
    CSliderCtrl*&           m_pWaterHeightSliderCtl;	// 슬라이더 컨트롤러
    CEdit*&					m_pWaterHeightEditCtl;		// 에디터 컨트롤러
    float&					m_fWaterHeight;				// 물 높이

    // == 물 UV 스피드 ==
    CSliderCtrl*&			m_pUVSpeedSliderCtl;		// 슬라이더 컨트롤러
    CEdit*&					m_pUVSpeedEditCtl;			// 에디터 컨트롤러
    float&					m_fUVSpeed;					// 물 UV 스피드 값

    // == 물 진폭 ==
    CSliderCtrl*&			m_pWaveHeightSliderCtl;		// 슬라이더 컨트롤러
    CEdit*&					m_pWaveHeightEditCtl;		// 에디터 컨트롤러
    float&					m_fWaveHeight;				// 물 진폭 값

    // == 물 상하 스피드 ==
    CSliderCtrl*&			m_pHeightSpeedSliderCtl;	// 슬라이더 컨트롤러
    CEdit*&					m_pHeightSpeedEditCtl;		// 에디터 컨트롤러
    float&					m_fHeightSpeed;				// 물 상하 스피드 값

    // == 물 물결 간격 ==
    CSliderCtrl*&			m_pFrequencySliderCtl;		// 슬라이더 컨트롤러
    CEdit*&					m_pFrequencyEditCtl;		// 에디터 컨트롤러
    float&					m_fFrequency;				// 물결 간격

    // == 물 투명값 ==
    CSliderCtrl*&			m_pTransparentSliderCtl;	// 슬라이더 컨트롤러
    CEdit*&					m_pTransparentEditCtl;		// 에디터 컨트롤러
    float&					m_fTransparent;				// 물 투명값

    // == 물 파일 경로 ==
    bool&                   m_isMakeWater;              // 물 만들지 여부
    bool&                   m_isSetWaterFile;           // 물 파일 셋팅 여부
    string&					m_strWaterFileName;         // 물 파일 이름
    string&                 m_strWaterFilePath;         // 물 패스

    // == 하늘 파일 경로 ==
    bool&                   m_isSetSkyFile;             // 하늘 파일 셋팅 여부
    string&					m_strSkyFileName;           // 하늘 파일 이름
    string&                 m_strSkyFilePath;           // 하늘 패스

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
    afx_msg void OnChangeWaterHeightEditer();
    afx_msg void OnDeltaposWaterHeightSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawWaterHeightSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeWaterUVSpeedEditer();
    afx_msg void OnDeltaposWaterUVSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawWaterUVSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeWaveHeightEditer();
    afx_msg void OnDeltaposWaveHeightSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawWaveHeightSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeHeightSpeedEditer();
    afx_msg void OnDeltaposHeightSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawHeightSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeFrequencyEditer();
    afx_msg void OnDeltaposFrequencySpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawFrequencySlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeTransparentEditer();
    afx_msg void OnDeltaposTransparentSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawTransparentSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClickedWaterFileLoadButton();
    afx_msg void OnClickedSkyFileLoadButton();
    afx_msg void OnClickedWaterMakeCheck();
	void Update();
};
