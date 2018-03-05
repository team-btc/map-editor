#pragma once


// cTextureTab 대화 상자

class cTextureTab : public CDialogEx
{
	DECLARE_DYNAMIC(cTextureTab)

private:
	// == 텍스쳐 선택 ==
	UINT				m_unTextureIndex;			// 기본 텍스쳐 인덱스

	CStatic*			m_pPictureController[5];	// 픽쳐 컨트롤러
	CBitmap				m_Bitmap[5];				// 텍스쳐 비트맵

	// == 텍스쳐 밀도값 ==
	CSliderCtrl*		m_pTextureDensitySliderCtl;	// 슬라이더 컨트롤러
	CEdit*				m_pTextureDensityEditCtl;	// 에디터 컨트롤러
	int					m_nTextureDensity;			// 텍스쳐 밀도값(%)

	// == 브러쉬 크기 ==
	CSliderCtrl*		m_pBrushSizeSliderCtl;		// 슬라이더 컨트롤러
	CEdit*				m_pBrushSizeEditCtl;		// 에디터 컨트롤러
	int					m_nBrushSize;				// 브러쉬 사이즈

	// == 브러쉬 밀도값 ==
	CSliderCtrl*		m_pBrushDensitySliderCtl;	// 슬라이더 컨트롤러
	CEdit*				m_pBrushDensityEditCtl;		// 에디터 컨트롤러
	int					m_nBrushDensity;			// 브러쉬 밀도값(%)

	// == 걸을 수 있는 지형 값 ==
	CButton*			m_pWalkAbleCheck;			// 걸을 수 있는지 여부 체크박스
	bool				m_isWalkAble;				// 걸을 수 있는지 여부

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
	afx_msg void OnClickTerrainRadio();
	afx_msg void OnChangeTextureDensityEditer();
	afx_msg void OnDeltaposTextureDensitySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawTextureDensitySlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeBrushSizeEditer();
	afx_msg void OnDeltaposBrushSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeBrushDensityEditer();
	afx_msg void OnDeltaposBrushDensitySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawBrushDensitySlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickWalkableCheck();
};
