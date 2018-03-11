// cCreateMapDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "cCreateMapDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

// cCreateMapDlg 대화 상자
//  encode

IMPLEMENT_DYNAMIC(cCreateMapDlg, CDialogEx)

cCreateMapDlg::cCreateMapDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CREATEMAP_VIEW, pParent)
    , m_pComboController(NULL)
    , m_pSliderController(NULL)
    , m_pEditController(NULL)
    , m_pWalkableCheck(NULL)
    , m_eMapSize(g_pMapDataManager->GetMapSize())
    , m_fDefaultHeight(g_pMapDataManager->GetDefHeight())
    , m_eDefGroundType(g_pMapDataManager->GetDefGroundType())
    , m_isDefWalkable(g_pMapDataManager->GetDefWalkable())
    , m_isCreateMap(g_pMapDataManager->GetCreateMap())
{
    for (int i = 0; i < 5; ++i)
    {
        m_pPictureController[i] = NULL;
    }
}

cCreateMapDlg::~cCreateMapDlg()
{
}

BOOL cCreateMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// == 콤보박스 초기화 == 
	m_pComboController = (CComboBox*)GetDlgItem(ID_MAP_SIZE_COM);
	// == 슬라이더 초기화 ==
	m_pSliderController = (CSliderCtrl*)GetDlgItem(ID_DEFAULT_HEIGHT_SLI);
	// == 에디터 컨트롤러 초기화 ==
	m_pEditController = (CEdit*)GetDlgItem(ID_DEFAULT_HEIGHT_EDI);
	// == Walkable 체크박스 초기화 ==
	m_pWalkableCheck = (CButton*)GetDlgItem(IDC_WALKABLE_CHE);
	m_pWalkableCheck->SetCheck(m_isDefWalkable);
	// == 텍스쳐 이미지 컨트롤러 초기화 ==
	m_pPictureController[0] = (CStatic*)GetDlgItem(ID_TERRAIN1_PIC);
	m_pPictureController[1] = (CStatic*)GetDlgItem(ID_TERRAIN2_PIC);
	m_pPictureController[2] = (CStatic*)GetDlgItem(ID_TERRAIN3_PIC);
	m_pPictureController[3] = (CStatic*)GetDlgItem(ID_TERRAIN4_PIC);
	m_pPictureController[4] = (CStatic*)GetDlgItem(ID_TERRAIN5_PIC);
	// == 텍스쳐 비트맵 초기화 ==
	m_Bitmap[0].LoadBitmapA(IDB_TERRAIN1);
	m_Bitmap[1].LoadBitmapA(IDB_TERRAIN2);
	m_Bitmap[2].LoadBitmapA(IDB_TERRAIN3);
	m_Bitmap[3].LoadBitmapA(IDB_TERRAIN4);
	m_Bitmap[4].LoadBitmapA(IDB_TERRAIN5);

	// 콤보박스에 텍스트 추가
    for (int i = 0; i < E_MAP_SIZE_MAX; ++i)
    {
        char str[20];
        int nValue = (i + 1) * 64;
        sprintf(str, "%d * %d", nValue, nValue);
        m_pComboController->AddString(str);
    }

	// 맵 사이즈 선택
	m_pComboController->SetCurSel(m_eMapSize);

	// 슬라이더 기본 설정
	m_pSliderController->SetRange(0, 256);	// 사용영역 값 설정
	m_pSliderController->SetRangeMin(0);	// 최소 값 설정
	m_pSliderController->SetRangeMax(255);	// 최대 값 설정
	m_pSliderController->SetPos(m_fDefaultHeight);		// 위치 설정
	m_pSliderController->SetTicFreq(32);	// 눈금 간격 설정
	m_pSliderController->SetLineSize(4);	// 증가 크기(키보드로 컨트롤 할 때)
	m_pSliderController->SetPageSize(12);	// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 기본 높이 값 출력
	SetDlgItemInt(ID_DEFAULT_HEIGHT_EDI, m_fDefaultHeight);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// == 텍스쳐 선택 라디오 버튼 초기화 및 연결 ==
	DDX_Radio(pDX, ID_TERRAIN1_RAD, (int&)m_eDefGroundType); // 텍스쳐1번으로 라디오박스 설정
}

void cCreateMapDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	// == 지형 텍스쳐 파일 그리기 ==
	for (int i = 0; i < 5; ++i)
	{
		// 화면과 호환이 되는 메모리 DC를 생성
		CDC memDC;
		memDC.CreateCompatibleDC(m_pPictureController[i]->GetDC());

		// 비트맵 리소스를 로딩
		CBitmap* pOldBmp = NULL;
		BITMAP bmpInfo;

		// 로딩된 비트맵의 정보를 알아본다.
		m_Bitmap[i].GetBitmap(&bmpInfo);

		// 메모리 DC에 선택한다.
		pOldBmp = memDC.SelectObject(&m_Bitmap[i]);

		// 크기조절
		//CRect rect;
		//m_pPictureController[i]->GetClientRect(rect);
		m_pPictureController[i]->GetDC()->StretchBlt(0, 0, 120, 30,
			&memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

		memDC.SelectObject(pOldBmp);
	}
}

BEGIN_MESSAGE_MAP(cCreateMapDlg, CDialogEx)
	ON_CBN_SELCHANGE(ID_MAP_SIZE_COM, &cCreateMapDlg::OnMapSizeSelectchange)
	ON_EN_CHANGE(ID_DEFAULT_HEIGHT_EDI, &cCreateMapDlg::OnDefaultHeightChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_DEFAULT_HEIGHT_SLI, &cCreateMapDlg::OnDefaultHeightCustomdrawDefaultHeight)
	ON_NOTIFY(UDN_DELTAPOS, ID_DEFAULT_HEIGHT_SPI, &cCreateMapDlg::OnDeltaposDefaultHeightSpin)
	ON_CONTROL_RANGE(BN_CLICKED, ID_TERRAIN1_RAD, ID_TERRAIN5_RAD, &cCreateMapDlg::OnSelectTextureRadio)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CREATE_MAP_BNT, &cCreateMapDlg::OnClickCreateMapBnt)
	ON_BN_CLICKED(IDC_WALKABLE_CHE, &cCreateMapDlg::OnClickWalkableCheck)
END_MESSAGE_MAP()


// cCreateMapDlg 메시지 처리기

// 콤보박스에서 맵 사이즈 선택
void cCreateMapDlg::OnMapSizeSelectchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 현재 인덱스 가져옴
	m_eMapSize = (E_MAP_SIZE)m_pComboController->GetCurSel();
}

// 지형 기본 높이 셋팅 (키보드 입력으로 설정)
void cCreateMapDlg::OnDefaultHeightChange()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fDefaultHeight = GetDlgItemInt(ID_DEFAULT_HEIGHT_EDI);

	// 슬라이더 위치 설정
	m_pSliderController->SetPos(m_fDefaultHeight);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pEditController->SetSel(0, -1);	// 모든 영역을 드레그
	m_pEditController->SetFocus();		// 포커스를 맞춤
	m_pEditController->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 지형 기본 높이 셋팅 (Spin으로 설정)
void cCreateMapDlg::OnDeltaposDefaultHeightSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fDefaultHeight >= 255)
		{
			return;
		}
		++m_fDefaultHeight;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fDefaultHeight <= 0)
		{
			return;
		}
		--m_fDefaultHeight;
	}

	// 높이 값 출력
	SetDlgItemInt(ID_DEFAULT_HEIGHT_EDI, m_fDefaultHeight);
	
	// 슬라이더 위치 설정
	m_pSliderController->SetPos(m_fDefaultHeight);		// 위치 설정

	*pResult = 0;
}

// 지형 기본 높이 셋팅 (Slider로 설정)
void cCreateMapDlg::OnDefaultHeightCustomdrawDefaultHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 높이 값 넣기
    m_fDefaultHeight = m_pSliderController->GetPos();

	// 높이 값 출력
	SetDlgItemInt(ID_DEFAULT_HEIGHT_EDI, m_fDefaultHeight);

	*pResult = 0;
}

// 기본 텍스쳐 값 셋팅 (라디오 버튼으로 설정)
void cCreateMapDlg::OnSelectTextureRadio(UINT ID)
{
	// 변경사항이 있을 때 사용하는 함수! -> 알아서 m_unTextureIndex값이 변경됨
	UpdateData();
}

// 걸을 수 있는지 여부 체크박스 클릭 했을 때
void cCreateMapDlg::OnClickWalkableCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_isDefWalkable = m_pWalkableCheck->GetCheck();
}

// 맵 만들기
void cCreateMapDlg::OnClickCreateMapBnt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    m_isCreateMap = true;

	// 메모리 관리!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}
