#pragma once


// cCreateMapDlg 대화 상자

class cCreateMapDlg : public CDialogEx
{
    DECLARE_DYNAMIC(cCreateMapDlg)

private:
    CComboBox * m_pComboController;			// 콤보박스 컨트롤러
    E_MAP_SIZE&			m_eMapSize;			        // 맵 사이즈 인덱스

    CSliderCtrl*		m_pSliderController;		// 슬라이더 컨트롤러
    CEdit*				m_pEditController;			// 에디터 컨트롤러
    float&				m_fDefaultHeight;			// 기본 높이 값

    bool&               m_isCreateMap;              // 맵 생성 여부

    bool&               m_isTex1Load;               // 기본 텍스쳐1 로드 여부
    bool&               m_isTex2Load;               // 기본 텍스쳐2 로드 여부
    bool&               m_isTex3Load;               // 기본 텍스쳐3 로드 여부

    string&             m_strTex1FilePath;          // 기본 텍스쳐1 파일 패스
    string&				m_strTex1FileName;          // 기본 텍스쳐1 파일 이름
    string&             m_strTex2FilePath;          // 기본 텍스쳐2 파일 패스
    string&				m_strTex2FileName;          // 기본 텍스쳐2 파일 이름
    string&             m_strTex3FilePath;          // 기본 텍스쳐3 파일 패스
    string&				m_strTex3FileName;          // 기본 텍스쳐3 파일 이름

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
    afx_msg void OnDefaultHeightChange();
    afx_msg void OnMapSizeSelectchange();
    afx_msg void OnDefaultHeightCustomdrawDefaultHeight(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposDefaultHeightSpin(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClickCreateMapBnt();
    afx_msg void OnClickedTex1LoadButton();
    afx_msg void OnClickedTex2LoadButton();
    afx_msg void OnClickedTex3LoadButton();
};
