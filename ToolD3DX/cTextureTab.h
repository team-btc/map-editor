#pragma once


// cTextureTab 대화 상자

class cTextureTab : public CDialogEx
{
	DECLARE_DYNAMIC(cTextureTab)

private:
	// == 텍스쳐 선택 ==
	E_GROUND_TYPE&		m_eTextureIndex;			// 기본 텍스쳐 인덱스
    E_DRAW_TYPE&        m_eDrawType;                // 그리기 타입

	CStatic*			m_pPictureController[5];	// 픽쳐 컨트롤러
	CBitmap				m_Bitmap[5];				// 텍스쳐 비트맵

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
	afx_msg void OnPaint();
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
};
