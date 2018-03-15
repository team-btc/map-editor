#pragma once


// cTextureTab 대화 상자

class cTextureTab : public CDialogEx
{
	DECLARE_DYNAMIC(cTextureTab)

private:
	// == 텍스쳐 선택 ==
	int&		        m_nTextureIndex;			// 기본 텍스쳐 인덱스
    E_DRAW_TYPE&        m_eDrawType;                // 그리기 타입

    // == 텍스쳐 파일 ==
    bool&               m_isTex1Load;               // 기본 텍스쳐1 로드 여부
    bool&               m_isTex2Load;               // 기본 텍스쳐2 로드 여부
    bool&               m_isTex3Load;               // 기본 텍스쳐3 로드 여부
    string&             m_strTex1FilePath;          // 기본 텍스쳐1 파일 패스
    string&				m_strTex1FileName;          // 기본 텍스쳐1 파일 이름
    string&             m_strTex2FilePath;          // 기본 텍스쳐2 파일 패스
    string&				m_strTex2FileName;          // 기본 텍스쳐2 파일 이름
    string&             m_strTex3FilePath;          // 기본 텍스쳐3 파일 패스
    string&				m_strTex3FileName;          // 기본 텍스쳐3 파일 이름

	// == 텍스쳐 밀도값 ==
	CSliderCtrl*		m_pTextureDensitySliderCtl;	// 슬라이더 컨트롤러
	CEdit*				m_pTextureDensityEditCtl;	// 에디터 컨트롤러
	float&				m_fTextureDensity;			// 텍스쳐 밀도값

	// == 브러쉬 크기 ==
	CSliderCtrl*		m_pBrushSizeSliderCtl;		// 슬라이더 컨트롤러
	CEdit*				m_pBrushSizeEditCtl;		// 에디터 컨트롤러
    float&				m_fBrushSize;				// 브러쉬 사이즈

    // == 브러쉬 밀도 사이즈 ==
    CSliderCtrl*		m_pBrushDenSizeSliderCtl;	// 슬라이더 컨트롤러
    CEdit*				m_pBrushDenSizeEditCtl;		// 에디터 컨트롤러
    float&				m_fBrushDenSize;			// 브러쉬 밀도 사이즈

	// == 브러쉬 밀도값 ==
	CSliderCtrl*		m_pBrushDensitySliderCtl;	// 슬라이더 컨트롤러
	CEdit*				m_pBrushDensityEditCtl;		// 에디터 컨트롤러
    float&				m_fBrushDensity;			// 브러쉬 밀도값

    // == 텍스쳐 1 밀도값 ==
    CSliderCtrl*&		m_pTex1DensitySliderCtl;	// 슬라이더 컨트롤러
    CEdit*&				m_pTex1DensityEditCtl;		// 에디터 컨트롤러
    float&				m_fTex1Density;			    // 텍스쳐 2 밀도값

    // == 텍스쳐 2 밀도값 ==
    CSliderCtrl*&		m_pTex2DensitySliderCtl;	// 슬라이더 컨트롤러
    CEdit*&				m_pTex2DensityEditCtl;		// 에디터 컨트롤러
    float&				m_fTex2Density;			    // 텍스쳐 2 밀도값

    // == 텍스쳐 3 밀도값 ==
    CSliderCtrl*&		m_pTex3DensitySliderCtl;	// 슬라이더 컨트롤러
    CEdit*&				m_pTex3DensityEditCtl;		// 에디터 컨트롤러
    float&				m_fTex3Density;			    // 텍스쳐 3 밀도값

public:
	cTextureTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~cTextureTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTURE_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectTextureRadio(UINT ID);
	afx_msg void OnChangeTextureDensityEditer();
	afx_msg void OnDeltaposTextureDensitySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawTextureDensitySlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeBrushSizeEditer();
	afx_msg void OnDeltaposBrushSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnChangeBrushDenSizeEditer();
    afx_msg void OnDeltaposBrushDenSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCustomDrawBrushDenSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeBrushDensityEditer();
	afx_msg void OnDeltaposBrushDensitySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawBrushDensitySlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnSelectDrawModeRadio(UINT ID);

    afx_msg void OnNMCustomdrawTex1DsizeSli(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawTex2DsizeSli(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawTex3DsizeSli(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnChangeTex1DsizeEdi();
    afx_msg void OnEnChangeTex2DsizeEdi();
    afx_msg void OnEnChangeTex3DsizeEdi();
    afx_msg void OnDeltaposTex1DsizeSpi(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposTex2DsizeSpi(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposTex3DsizeSpi(NMHDR *pNMHDR, LRESULT *pResult);

    afx_msg void OnClickedTex1LoadButton();
    afx_msg void OnClickedTex2LoadButton();
    afx_msg void OnClickedTex3LoadButton();

    void Update();
};
