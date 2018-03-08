﻿#pragma once


// cObjectTab 대화 상자

struct ST_OBJ_FILE
{
	CString			strRoot;
	vector<CString> vecChild;
};

class cObjectTab : public CDialogEx
{
	DECLARE_DYNAMIC(cObjectTab)

private:
	// == 오브젝트 파일 ==
	vector<ST_OBJ_FILE>		m_vecObjectFile;		// 오브젝트 파일 목록
	CTreeCtrl*				m_pObjFileTreeCtrl;		// 오브젝트 파일 트리 컨트롤러
	CString					m_SelectObjFile;		// 현재 선택된 오브젝트 파일

	// == 오브젝트 리스트 ==
	CListBox*				m_pObjListBox;			// 만들어진 오브젝트 리스트
	CString					m_CurrSelectObj;		// 현재 선택한 오브젝트

	// == 오브젝트 충돌 파괴 체크박스 ==
	CButton*				m_pCollisionCheck;		// 충돌 체크박스
    bool&                   m_isCollision;          // 충돌 여부
	CButton*				m_pDestructionCheck;	// 파괴 체크박스
    bool&                   m_isDestruction;        // 파괴 여부

	// == 오브젝트 크기 ==
	CSliderCtrl*			m_pObjSizeSliderCtl;	// 슬라이더 컨트롤러
	CEdit*					m_pObjSizeEditCtl;		// 에디터 컨트롤러
	float&					m_fObjSize;				// 오브젝트 사이즈

	// == 오브젝트 위치 ==
	CStatic*				m_pObjPosXStatic;		// 스태틱
	CStatic*				m_pObjPosYStatic;		// 스태틱
	CStatic*				m_pObjPosZStatic;		// 스태틱
	float&					m_fObjPosX;				// 오브젝트 위치 X;
	float&					m_fObjPosY;				// 오브젝트 위치 Y;
	float&					m_fObjPosZ;				// 오브젝트 위치 Z;

	// == 오브젝트 X축 회전값 ==
	CSliderCtrl*			m_pObjRotXSliderCtl;	// 슬라이더 컨트롤러
	CEdit*					m_pObjRotXEditCtl;		// 에디터 컨트롤러
    float&					m_fObjRotX;				// 오브젝트 X축 회전값

	// == 오브젝트 Y축 회전값 ==
	CSliderCtrl*			m_pObjRotYSliderCtl;	// 슬라이더 컨트롤러
	CEdit*					m_pObjRotYEditCtl;		// 에디터 컨트롤러
    float&					m_fObjRotY;				// 오브젝트 Y축 회전값

	// == 오브젝트 Z축 회전값 ==
	CSliderCtrl*			m_pObjRotZSliderCtl;	// 슬라이더 컨트롤러
	CEdit*					m_pObjRotZEditCtl;		// 에디터 컨트롤러
    float&					m_fObjRotZ;				// 오브젝트 Z축 회전값

	// == X 파일 경로
	string					m_strFileName;          // 현재 사용 파일 이름
	string                  m_strFileKey;           // 현재 사용 키
	string                  m_strFilePath;          // 현재 사용 패스

	// == 오브젝트 배치하기
	bool&					m_isLocation;			// 오브젝트 배치하기 버튼과 연동

    E_OBJECT_TAB_BUTTON_STATE&  m_eObjectTabButtonState;

public:
	cObjectTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~cObjectTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECT_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SetTreeController();	// 오브젝트 파일 리스트 셋팅
	void SetListController();	// 오프젝트 리스트 셋팅

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectChangeObjectFileTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelectChangeObjectList();
	afx_msg void OnClickCollisionCheck();
	afx_msg void OnChangeObjectSizeEditer();
	afx_msg void OnDeltaposObjectSizeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawObjectSizeSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeObjectRotXEditer();
	afx_msg void OnDeltaposObjectRotXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawObjectRotXSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeObjectRotYEditer();
	afx_msg void OnDeltaposObjectRotYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawObjectRotYSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeObjectRotZEditer();
	afx_msg void OnDeltaposObjectRotZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomDrawObjectRotZSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickObjectDuplcationBtn();
	afx_msg void OnClickObjectDeleteBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton4();
};
