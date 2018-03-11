﻿// cObjectTab.cpp: 구현 파일
//

#include "stdafx.h"
#include "cObjectTab.h"
#include "afxdialogex.h"
#include "Resource.h"

// cObjectTab 대화 상자

IMPLEMENT_DYNAMIC(cObjectTab, CDialogEx)

cObjectTab::cObjectTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OBJECT_TAB, pParent)
	, m_pObjFileTreeCtrl(NULL)
	, m_pObjListBox(NULL)
	, m_pCollisionCheck(NULL)
	, m_pDestructionCheck(NULL)
	, m_pObjSizeSliderCtl(NULL)
	, m_pObjSizeEditCtl(NULL)
	, m_pObjPosXStatic(NULL)
	, m_pObjPosYStatic(NULL)
	, m_pObjPosZStatic(NULL)
	, m_pObjRotXSliderCtl(NULL)
	, m_pObjRotXEditCtl(NULL)
	, m_pObjRotYSliderCtl(NULL)
	, m_pObjRotYEditCtl(NULL)
	, m_pObjRotZSliderCtl(NULL)
	, m_pObjRotZEditCtl(NULL)
    , m_isCollision(g_pMapDataManager->GetObjCollision())
    , m_isDestruction(g_pMapDataManager->GetObjDestruction())
	, m_fObjSize(g_pMapDataManager->GetObjSize())
	, m_fObjPosX(g_pMapDataManager->GetObjPosX())
	, m_fObjPosY(g_pMapDataManager->GetObjPosY())
	, m_fObjPosZ(g_pMapDataManager->GetObjPosZ())
	, m_fObjRotX(g_pMapDataManager->GetObjRotX())
	, m_fObjRotY(g_pMapDataManager->GetObjRotY())
	, m_fObjRotZ(g_pMapDataManager->GetObjRotZ())
    , m_eObjectTabButtonState(g_pMapDataManager->GetObjectTabButtonState())
    , m_eBlockButtonState(g_pMapDataManager->GetBlockButtonState())
    , m_pBlockGroupListBox(NULL)
	, m_SelectBlockGroupName(g_pMapDataManager->GetSelectedBlockGroupName())
    , m_nBlockGroupMakeNum(-1)
{
	ST_OBJ_FILE stObjHouse;
	stObjHouse.strRoot = "HOUSE";
	stObjHouse.vecChild.push_back("Red Hosue");
	stObjHouse.vecChild.push_back("Blue Hosue");
	ST_OBJ_FILE stObjTree;
	stObjTree.strRoot = "TREE";
	stObjTree.vecChild.push_back("Red Tree");
	stObjTree.vecChild.push_back("Blue Tree");
	ST_OBJ_FILE stObjStone;
	stObjStone.strRoot = "STONE";
	stObjStone.vecChild.push_back("Red Stone");
	stObjStone.vecChild.push_back("Blue Stone");

    m_eObjectTabButtonState = E_OBJ_TAB_BTN_MAX;
    m_eBlockButtonState = E_BLOCK_BTN_MAX;
	m_SelectBlockGroupName = NO_NAME;

	m_vecObjectFile.push_back(stObjHouse);
	m_vecObjectFile.push_back(stObjTree);
	m_vecObjectFile.push_back(stObjStone);
}

cObjectTab::~cObjectTab()
{
}

BOOL cObjectTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// == 오브젝트 파일 트리 컨트롤러 초기화 ==
	m_pObjFileTreeCtrl = (CTreeCtrl*)GetDlgItem(IDC_OBJECT_FILE_TRE);
	// == 오브젝트 리스트 컨트롤러 초기화 ==
	m_pObjListBox = (CListBox*)GetDlgItem(IDC_OBJECT_LIST_LIS);
	// 오브젝트 파일 트리 셋팅
	SetTreeController();
	// 오브젝트 리스트 셋팅
	SetListController();

	// == 충돌 체크박스 초기화 ==
	m_pCollisionCheck = (CButton*)GetDlgItem(IDC_COLLISION_CHE);
	m_pCollisionCheck->SetCheck(m_isCollision);
	// == 파괴 체크박스 초기화 ==
	m_pDestructionCheck = (CButton*)GetDlgItem(IDC_DESTRUCTION_CHE);
	m_pDestructionCheck->SetCheck(m_isDestruction);

	// == 오브젝트 사이즈 설정 초기화 ==
	m_pObjSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_OBJECT_SIZE_SLI);
	m_pObjSizeEditCtl = (CEdit*)GetDlgItem(IDC_OBJECT_SIZE_EDI);
	
	// 오브젝트 사이즈 슬라이더 기본 설정
	m_pObjSizeSliderCtl->SetRange(1, 20);		// 사용영역 값 설정
	m_pObjSizeSliderCtl->SetRangeMin(1);		// 최소 값 설정
	m_pObjSizeSliderCtl->SetRangeMax(20);		// 최대 값 설정
	m_pObjSizeSliderCtl->SetPos((int)m_fObjSize);	// 위치 설정
	m_pObjSizeSliderCtl->SetTicFreq(1);		// 눈금 간격 설정
	m_pObjSizeSliderCtl->SetLineSize((int)0.5);		// 증가 크기(키보드로 컨트롤 할 때)
	m_pObjSizeSliderCtl->SetPageSize((int)0.5);		// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 오브젝트 사이즈 출력
	SetDlgItemInt(IDC_OBJECT_SIZE_EDI, (UINT)m_fObjSize);

	// == 오브젝트 위치 설정 초기화 ==
	m_pObjPosXStatic = (CStatic*)GetDlgItem(IDC_POS_X_TEXT);
	m_pObjPosYStatic = (CStatic*)GetDlgItem(IDC_POS_Y_TEXT);
	m_pObjPosZStatic = (CStatic*)GetDlgItem(IDC_POS_Z_TEXT);
	char strPosX[10];
	sprintf_s(strPosX, "%0.3f", m_fObjPosX);
	SetDlgItemTextA(IDC_POS_X_TEXT, (CString)strPosX);
	char strPosY[10];
    sprintf_s(strPosY, "%0.3f", m_fObjPosY);
	SetDlgItemTextA(IDC_POS_Y_TEXT, (CString)strPosY);
	char strPosZ[10];
    sprintf_s(strPosZ, "%0.3f", m_fObjPosZ);
	SetDlgItemTextA(IDC_POS_Z_TEXT, (CString)strPosZ);

	// == 오브젝트 X축 회전값 설정 초기화 ==
	m_pObjRotXSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_OBJECT_ROT_X_SLI);
	m_pObjRotXEditCtl = (CEdit*)GetDlgItem(IDC_OBJECT_ROT_X_EDI);

	// 오브젝트 X축 회전값 슬라이더 기본 설정
	m_pObjRotXSliderCtl->SetRange(0, 360);		// 사용영역 값 설정
	m_pObjRotXSliderCtl->SetRangeMin(0);		// 최소 값 설정
	m_pObjRotXSliderCtl->SetRangeMax(360);		// 최대 값 설정
	m_pObjRotXSliderCtl->SetPos((int)m_fObjRotX);	// 위치 설정
	m_pObjRotXSliderCtl->SetTicFreq(45);		// 눈금 간격 설정
	m_pObjRotXSliderCtl->SetLineSize(15);		// 증가 크기(키보드로 컨트롤 할 때)
	m_pObjRotXSliderCtl->SetPageSize(45);		// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 오브젝트 X축 회전값 출력
	SetDlgItemInt(IDC_OBJECT_ROT_X_EDI, (UINT)m_fObjRotX);

	// == 오브젝트 Y축 회전값 설정 초기화 ==
	m_pObjRotYSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_OBJECT_ROT_Y_SLI);
	m_pObjRotYEditCtl = (CEdit*)GetDlgItem(IDC_OBJECT_ROT_Y_EDI);

	// 오브젝트 Y축 회전값 슬라이더 기본 설정
	m_pObjRotYSliderCtl->SetRange(0, 360);		// 사용영역 값 설정
	m_pObjRotYSliderCtl->SetRangeMin(0);		// 최소 값 설정
	m_pObjRotYSliderCtl->SetRangeMax(360);		// 최대 값 설정
	m_pObjRotYSliderCtl->SetPos((int)m_fObjRotY);	// 위치 설정
	m_pObjRotYSliderCtl->SetTicFreq(45);		// 눈금 간격 설정
	m_pObjRotYSliderCtl->SetLineSize(15);		// 증가 크기(키보드로 컨트롤 할 때)
	m_pObjRotYSliderCtl->SetPageSize(45);		// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 오브젝트 Y축 회전값 출력
	SetDlgItemInt(IDC_OBJECT_ROT_Y_EDI, (UINT)m_fObjRotY);

	// == 오브젝트 Z축 회전값 설정 초기화 ==
	m_pObjRotZSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_OBJECT_ROT_Z_SLI);
	m_pObjRotZEditCtl = (CEdit*)GetDlgItem(IDC_OBJECT_ROT_Z_EDI);

	// 오브젝트 Z축 회전값 슬라이더 기본 설정
	m_pObjRotZSliderCtl->SetRange(0, 360);		// 사용영역 값 설정
	m_pObjRotZSliderCtl->SetRangeMin(0);		// 최소 값 설정
	m_pObjRotZSliderCtl->SetRangeMax(360);		// 최대 값 설정
	m_pObjRotZSliderCtl->SetPos((int)m_fObjRotZ);	// 위치 설정
	m_pObjRotZSliderCtl->SetTicFreq(45);		// 눈금 간격 설정
	m_pObjRotZSliderCtl->SetLineSize(15);		// 증가 크기(키보드로 컨트롤 할 때)
	m_pObjRotZSliderCtl->SetPageSize(45);		// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 오브젝트 Z축 회전값 출력
	SetDlgItemInt(IDC_OBJECT_ROT_Z_EDI, (UINT)m_fObjRotZ);

    // 블록 그룹 리스트 
    m_pBlockGroupListBox = (CListBox*)GetDlgItem(IDC_BLOCK_GROUP_LIST_LIS);
    
    // 현재 작업중인 블록 그룹
    SetDlgItemText(IDC_BLOCK_GROUP_TEXT, "None");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// 오브젝트 파일 리스트 셋팅
void cObjectTab::SetTreeController()
{
	for (int i = 0; i < m_vecObjectFile.size(); ++i)
	{
		// 루트 설정
		HTREEITEM hRoot;
		hRoot = m_pObjFileTreeCtrl->InsertItem(m_vecObjectFile[i].strRoot, TVI_ROOT, TVI_LAST);
		// 자식 설정
		for (int j = 0; j < m_vecObjectFile[i].vecChild.size(); ++j)
		{
			HTREEITEM  hChild;
			hChild = m_pObjFileTreeCtrl->InsertItem(m_vecObjectFile[i].vecChild[j], hRoot, TVI_LAST);
		}
		//// 리스트 열기
		//m_pObjFileTreeCtrl->Expand(hRoot, TVE_EXPAND);
	}
}

// 오브젝트 리스트 셋팅
void cObjectTab::SetListController()
{
	// 초기화
	//m_pObjListBox->AddString("HOUSE1"); // 가나다 순으로 자동정렬 됨
	//m_pObjListBox->AddString("HOUSE2");
	//m_pObjListBox->AddString("HOUSE3");
	//// 마지막에 추가한다는 의미
	//int index = m_pObjListBox->InsertString(-1, "HOUSE0");
	//// 리스트에 커서를 생성
	//m_pObjListBox->SetCurSel(index);

	// 해당 문자열을 지우는 함수
	//m_pObjListBox->DeleteString(위치값);
	// 모든 문자열을 지우는 함수.
	//m_pObjListBox->ResetContent();
}

void cObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cObjectTab, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_OBJECT_FILE_TRE, &cObjectTab::OnSelectChangeObjectFileTree)
	ON_LBN_SELCHANGE(IDC_OBJECT_LIST_LIS, &cObjectTab::OnSelectChangeObjectList)
	ON_BN_CLICKED(IDC_COLLISION_CHE, &cObjectTab::OnClickCollisionCheck)
	ON_EN_CHANGE(IDC_OBJECT_SIZE_EDI, &cObjectTab::OnChangeObjectSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OBJECT_SIZE_SPI, &cObjectTab::OnDeltaposObjectSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_OBJECT_SIZE_SLI, &cObjectTab::OnCustomDrawObjectSizeSlider)
	ON_EN_CHANGE(IDC_OBJECT_ROT_X_EDI, &cObjectTab::OnChangeObjectRotXEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OBJECT_ROT_X_SPI, &cObjectTab::OnDeltaposObjectRotXSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_OBJECT_ROT_X_SLI, &cObjectTab::OnCustomDrawObjectRotXSlider)
	ON_EN_CHANGE(IDC_OBJECT_ROT_Y_EDI, &cObjectTab::OnChangeObjectRotYEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OBJECT_ROT_Y_SPI, &cObjectTab::OnDeltaposObjectRotYSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_OBJECT_ROT_Y_SLI, &cObjectTab::OnCustomDrawObjectRotYSlider)
	ON_EN_CHANGE(IDC_OBJECT_ROT_Z_EDI, &cObjectTab::OnChangeObjectRotZEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OBJECT_ROT_Z_SPI, &cObjectTab::OnDeltaposObjectRotZSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_OBJECT_ROT_Z_SLI, &cObjectTab::OnCustomDrawObjectRotZSlider)
	ON_BN_CLICKED(IDC_DUPLCATION_BTN, &cObjectTab::OnClickObjectDuplcationBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, &cObjectTab::OnClickObjectDeleteBtn)
	ON_BN_CLICKED(IDC_BUTTON1, &cObjectTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &cObjectTab::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &cObjectTab::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON5, &cObjectTab::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON4, &cObjectTab::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON8, &cObjectTab::OnBnClickedButton8)
    ON_BN_CLICKED(IDC_BUTTON7, &cObjectTab::OnBnClickedButton7)
    ON_LBN_SELCHANGE(IDC_BLOCK_GROUP_LIST_LIS, &cObjectTab::OnLbnSelchangeBlockGroupListLis)
    ON_BN_CLICKED(IDC_BUTTON9, &cObjectTab::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON10, &cObjectTab::OnBnClickedButton10)
END_MESSAGE_MAP()


// cObjectTab 메시지 처리기

// 오브젝트 파일 트리 선택했을 때
void cObjectTab::OnSelectChangeObjectFileTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HTREEITEM hItem;
	CString strName;

	// 현재 선택된 아이템의 핸들을 가져온다.
	hItem = m_pObjFileTreeCtrl->GetSelectedItem();
	// 현재 선택된 아이템의 이름을 가져온다.
	strName = m_pObjFileTreeCtrl->GetItemText(hItem);

	// 무슨 아이템인지 찾는다
	for (int i = 0; i < m_vecObjectFile.size(); ++i)
	{
		// 자식 설정
		for (int j = 0; j < m_vecObjectFile[i].vecChild.size(); ++j)
		{
			// 아이템명이 일치하면
			if (strName == m_vecObjectFile[i].vecChild[j])
			{
				m_SelectObjFile = strName; // 아이템 이름 설정
			}
		}
	}

	*pResult = 0;
}

// 오브젝트 리스트에서 오브젝트가 클릭되었을 때
void cObjectTab::OnSelectChangeObjectList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 선택한 인덱스 가져오기
	int nIndex = m_pObjListBox->GetCurSel();

	// 문자열 가져오기
	CString strName;
	m_pObjListBox->GetText(nIndex, strName);

	// 문자열 저장
	m_CurrSelectObj = strName;
}

// 충돌 체크가 클릭 되었을 때
void cObjectTab::OnClickCollisionCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 체크를 했으면
	if (m_pCollisionCheck->GetCheck() == BST_CHECKED)
	{

	}
	// 체크를 풀었으면
	else
	{

	}
}

// == 오브젝트 사이즈 ==================================================================================================
// 오브젝트 사이즈 설정 (에디터)
void cObjectTab::OnChangeObjectSizeEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fObjSize = (float)GetDlgItemInt(IDC_OBJECT_SIZE_EDI);

	// 슬라이더 위치 설정
	m_pObjSizeSliderCtl->SetPos((int)m_fObjSize);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pObjSizeEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pObjSizeEditCtl->SetFocus();		// 포커스를 맞춤
	m_pObjSizeEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 오브젝트 사이즈 설정 (스핀)
void cObjectTab::OnDeltaposObjectSizeSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fObjSize >= 100)
		{
			return;
		}
		++m_fObjSize;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fObjSize <= 1)
		{
			return;
		}
		--m_fObjSize;
	}

	// 오브젝트 사이즈 출력
	SetDlgItemInt(IDC_OBJECT_SIZE_EDI, m_fObjSize);

	// 슬라이더 위치 설정
	m_pObjSizeSliderCtl->SetPos(m_fObjSize);		// 위치 설정

	*pResult = 0;
}

// 오브젝트 사이즈 설정 (슬라이더)
void cObjectTab::OnCustomDrawObjectSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 오브젝트 사이즈 넣기
	m_fObjSize = m_pObjSizeSliderCtl->GetPos();

	// 오브젝트 사이즈 출력
	SetDlgItemInt(IDC_OBJECT_SIZE_EDI, m_fObjSize);

	*pResult = 0;
}

// == 오브젝트 X축 회전값 ==================================================================================================
// 오브젝트 X축 회전값 설정 (에디터)
void cObjectTab::OnChangeObjectRotXEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fObjRotX = GetDlgItemInt(IDC_OBJECT_ROT_X_EDI);

	// 슬라이더 위치 설정
	m_pObjRotXSliderCtl->SetPos(m_fObjRotX);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pObjRotXEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pObjRotXEditCtl->SetFocus();		// 포커스를 맞춤
	m_pObjRotXEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 오브젝트 X축 회전값 설정 (스핀)
void cObjectTab::OnDeltaposObjectRotXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fObjRotX >= 360)
		{
			return;
		}
		++m_fObjRotX;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fObjRotX <= 0)
		{
			return;
		}
		--m_fObjRotX;
	}

	// 오브젝트 X축 회전값 출력
	SetDlgItemInt(IDC_OBJECT_ROT_X_EDI, m_fObjRotX);

	// 슬라이더 위치 설정
	m_pObjRotXSliderCtl->SetPos(m_fObjRotX);		// 위치 설정

	*pResult = 0;
}

// 오브젝트 X축 회전값 설정 (슬라이더)
void cObjectTab::OnCustomDrawObjectRotXSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 오브젝트 사이즈 넣기
	m_fObjRotX = m_pObjRotXSliderCtl->GetPos();

	// 오브젝트 사이즈 출력
	SetDlgItemInt(IDC_OBJECT_ROT_X_EDI, m_fObjRotX);

	*pResult = 0;
}

// == 오브젝트 Y축 회전값 ==================================================================================================
// 오브젝트 Y축 회전값 설정 (에디터)
void cObjectTab::OnChangeObjectRotYEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fObjRotY = GetDlgItemInt(IDC_OBJECT_ROT_Y_EDI);

	// 슬라이더 위치 설정
	m_pObjRotYSliderCtl->SetPos(m_fObjRotY);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pObjRotYEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pObjRotYEditCtl->SetFocus();		// 포커스를 맞춤
	m_pObjRotYEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 오브젝트 Y축 회전값 설정 (스핀)
void cObjectTab::OnDeltaposObjectRotYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fObjRotY >= 360)
		{
			return;
		}
		++m_fObjRotY;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fObjRotY <= 0)
		{
			return;
		}
		--m_fObjRotY;
	}

	// 오브젝트 X축 회전값 출력
	SetDlgItemInt(IDC_OBJECT_ROT_Y_EDI, m_fObjRotY);

	// 슬라이더 위치 설정
	m_pObjRotYSliderCtl->SetPos((int)m_fObjRotY);		// 위치 설정

	*pResult = 0;
}

// 오브젝트 Y축 회전값 설정 (슬라이더)
void cObjectTab::OnCustomDrawObjectRotYSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 오브젝트 사이즈 넣기
	m_fObjRotY = (int)m_pObjRotYSliderCtl->GetPos();

	// 오브젝트 사이즈 출력
	SetDlgItemInt(IDC_OBJECT_ROT_Y_EDI, m_fObjRotY);

	*pResult = 0;
}

// == 오브젝트 Z축 회전값 ==================================================================================================
// 오브젝트 Z축 회전값 설정 (에디터)
void cObjectTab::OnChangeObjectRotZEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fObjRotZ = GetDlgItemInt(IDC_OBJECT_ROT_Z_EDI);

	// 슬라이더 위치 설정
	m_pObjRotZSliderCtl->SetPos(m_fObjRotZ);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pObjRotZEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pObjRotZEditCtl->SetFocus();		// 포커스를 맞춤
	m_pObjRotZEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 오브젝트 Z축 회전값 설정 (스핀)
void cObjectTab::OnDeltaposObjectRotZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fObjRotZ >= 360)
		{
			return;
		}
		++m_fObjRotZ;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fObjRotZ <= 0)
		{
			return;
		}
		--m_fObjRotZ;
	}

	// 오브젝트 X축 회전값 출력
	SetDlgItemInt(IDC_OBJECT_ROT_Z_EDI, m_fObjRotZ);

	// 슬라이더 위치 설정
	m_pObjRotZSliderCtl->SetPos(m_fObjRotZ);		// 위치 설정

	*pResult = 0;
}

// 오브젝트 Z축 회전값 설정 (슬라이더)
void cObjectTab::OnCustomDrawObjectRotZSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 오브젝트 사이즈 넣기
	m_fObjRotZ = (float)(m_pObjRotZSliderCtl->GetPos());

	// 오브젝트 사이즈 출력
	SetDlgItemInt(IDC_OBJECT_ROT_Z_EDI, (UINT)m_fObjRotZ);

	*pResult = 0;
}

// 오브젝트 복사 버튼
void cObjectTab::OnClickObjectDuplcationBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    m_strFileName = m_CurrSelectObj;

    string caption;
    string text;

    if (!m_strFileName.empty())
    {
        // 파일 이름을 표시해줌
        caption = "성공";
        text = m_strFileName + "파일이 선택되었습니다.";        
   
        SetDlgItemText(IDC_FILE_NAME_TEXT, m_strFileName.c_str());
        g_pMapDataManager->SetFileName(m_strFileName);
    }
    else
    {
        caption = "실패";
        text = "현재까지 읽은 파일이 없습니다.";

        SetDlgItemText(IDC_FILE_NAME_TEXT, "None");
    }

    MessageBox(text.c_str(), caption.c_str(), MB_ICONMASK);
    m_eObjectTabButtonState = E_OBJ_TAB_BTN_MAX;
}

// 오브젝트 삭제 버튼
void cObjectTab::OnClickObjectDeleteBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// 삭제 처리 하기!!/////////////////////////////////////////////////////////////////////////
}

// File Open 버튼 
void cObjectTab::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char current_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, current_path);

	// 확장자 필터
	LPSTR szFilter = "X Files (*.x) |*.X|";

	CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	string text;
	string caption = "X파일 불러오기";

	if (FileDialog.DoModal() == IDOK)
	{
		//파일 확장자 가져오기 
		CString check = FileDialog.GetFileExt();

		// 확장자가 x인지 체크 
		if (check == "X" || check == "x")
		{
			//m_strFileKey = FileDialog.GetFileTitle();
			m_strFilePath = FileDialog.GetFolderPath().GetString();
			m_strFileName = FileDialog.GetFileName().GetString();

			// 맵 데이터 매니져에 정보 세팅하기		
			g_pMapDataManager->SetFilePath(m_strFilePath);
			g_pMapDataManager->SetFileName(m_strFileName);

			text = m_strFileName + " 파일 읽기 성공";
			MessageBox(text.c_str(), caption.c_str());

            int index = m_pObjListBox->FindString(-1, m_strFileName.c_str());

            if (index == LB_ERR)
            {
                m_pObjListBox->AddString(m_strFileName.c_str());
            }
            
            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_FILE_NAME_TEXT, m_strFileName.c_str());
		}
		else
		{
			text = "파일 읽기 실패";
			MessageBox(text.c_str(), caption.c_str(), MB_ICONERROR);

            string str = NO_NAME;
            
            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_FILE_NAME_TEXT, str.c_str());
		}
	}
}
// Locate 버튼
void cObjectTab::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_eObjectTabButtonState = E_OBJ_TAB_BTN_LOCATE;
}
// Cancel 버튼
void cObjectTab::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_eObjectTabButtonState = E_OBJ_TAB_BTN_MAX;
}
// Relocate 버튼
void cObjectTab::OnBnClickedButton4()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_eObjectTabButtonState = E_OBJ_TAB_BTN_RELOCATE;
}
void cObjectTab::Update()
{
    m_pObjSizeSliderCtl->SetPos((int)m_fObjSize);    // Scale 위치 설정 
    m_pObjRotXSliderCtl->SetPos((int)m_fObjRotX);	// RotX 위치 설정
    m_pObjRotYSliderCtl->SetPos((int)m_fObjRotY);    // RotY 위치 설정
    m_pObjRotZSliderCtl->SetPos((int)m_fObjRotZ);    // RotZ 위치 설정


	// 블록그룹 텍스트 갱신 


    SetDlgItemText(IDC_BLOCK_GROUP_TEXT, m_SelectBlockGroupName.c_str());



}
// Remove 버튼
void cObjectTab::OnBnClickedButton5()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_eObjectTabButtonState = E_OBJ_TAB_BTN_REMOVE;
}

#pragma region "Block Group Edit 부분"
// Block Group New 버튼
void cObjectTab::OnBnClickedButton8()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 두가지 액션을 하지 못하게 처리 
	if (m_eObjectTabButtonState != E_OBJ_TAB_BTN_MAX)
	{
		m_eObjectTabButtonState = E_OBJ_TAB_BTN_MAX;
	}

	if (m_eBlockButtonState != E_BLOCK_BTN_PROGRESS)
	{
		m_eBlockButtonState = E_BLOCK_BTN_START;
		m_nBlockGroupMakeNum += 1;

		m_SelectBlockGroupName = BLOCK_GROUP_NAME;
		m_SelectBlockGroupName += to_string(m_nBlockGroupMakeNum);
	}
}

//  Block Group End 버튼
void cObjectTab::OnBnClickedButton7()
{
	if (m_eBlockButtonState == E_BLOCK_BTN_PROGRESS)
	{
		if (m_SelectBlockGroupName != NO_NAME)
		{
			// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
			m_eBlockButtonState = E_BLOCK_BTN_END;

			int index = m_pBlockGroupListBox->FindString(-1, m_SelectBlockGroupName.c_str());

			if (index == LB_ERR)
			{
				m_pBlockGroupListBox->AddString(m_SelectBlockGroupName.c_str());
			}

			string caption = "Block Gruop";
			string text = m_SelectBlockGroupName + " 이(가) 저장되었습니다.";

			// 메세지 표시 
			MessageBox(text.c_str(), caption.c_str(), MB_ICONMASK);

			// 블록 그룹 이름을 표시해줌
			m_SelectBlockGroupName = NO_NAME;
		}
	}
}

// Block Group 리스트가 눌렸을때 
void cObjectTab::OnLbnSelchangeBlockGroupListLis()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
   
    // 선택한 인덱스 가져오기
    int nIndex = m_pBlockGroupListBox->GetCurSel();

    // 문자열 가져오기
    CString strName;
    m_pBlockGroupListBox->GetText(nIndex, strName);

    // 문자열 저장
	m_SelectBlockGroupName = strName;
}
#pragma endregion

// Block Group Delete 버튼이 눌렸을때 
void cObjectTab::OnBnClickedButton9()
{
	if (m_eBlockButtonState != E_BLOCK_BTN_PROGRESS)
	{
		if (m_SelectBlockGroupName != NO_NAME)
		{
			// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
			int nSel = m_pBlockGroupListBox->GetCurSel();  // 선택한 문자의 인덱스 얻어옴

			if (nSel >= 0)
			{
				m_pBlockGroupListBox->DeleteString(nSel);  // 해당 인덱스의 문자열을 삭제
			}

			// 메세지 표시 
			string caption = "Block Gruop";
			string text = m_SelectBlockGroupName + " 이(가) 삭제되었습니다.";
			MessageBox(text.c_str(), caption.c_str(), MB_ICONMASK);

			// 블록 그룹 이름을 표시
			// m_CurrSelectBlockGroup = NONE_NAME;
			// SetDlgItemText(IDC_BLOCK_GROUP_TEXT, m_CurrSelectBlockGroup.c_str());

			// 버튼 상태 변경 
			m_eBlockButtonState = E_BLOCK_BTN_DELETE;
		}
	}
}

// Block Group Modify 버튼이 눌렸을때 
void cObjectTab::OnBnClickedButton10()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 버튼 상태가 진행 중일땐 저장 상태로 돌아가게 
    if (m_eBlockButtonState == E_BLOCK_BTN_PROGRESS)
    {
        // 메세지 표시 
        string caption = "Block Gruop";
        string text = m_SelectBlockGroupName + " 이(가) 저장되었습니다.";
        MessageBox(text.c_str(), caption.c_str(), MB_ICONMASK);

        m_eBlockButtonState = E_BLOCK_BTN_END;

        int index = m_pBlockGroupListBox->FindString(-1, m_SelectBlockGroupName.c_str());

        if (index == LB_ERR)
        {
            m_pBlockGroupListBox->AddString(m_SelectBlockGroupName.c_str());
        }
        // 블록 그룹 이름을 표시해줌
		m_SelectBlockGroupName = NO_NAME;
        
        return;
    }
    else
    {
		if (m_SelectBlockGroupName != NO_NAME)
		{
			// 메세지 표시
			string caption = "Block Gruop";
			string text = m_SelectBlockGroupName + " 이(가) 선택되었습니다.";
			MessageBox(text.c_str(), caption.c_str(), MB_ICONMASK);

			// 버튼 상태 변경 
			m_eBlockButtonState = E_BLOCK_BTN_MODIFY;
		}
		else
		{
			// 메세지 표시 
			string caption = "Block Gruop";
			string text = "잘못된 접근입니다.";
			MessageBox(text.c_str(), caption.c_str(), MB_ICONMASK);

			//m_eBlockButtonState = E_B
		}
      
    }
}
