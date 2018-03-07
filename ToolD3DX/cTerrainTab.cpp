// cTerrainTab.cpp: 구현 파일
//

#include "stdafx.h"
#include "cTerrainTab.h"
#include "afxdialogex.h"
#include "Resource.h"

// cTerrainTab 대화 상자

IMPLEMENT_DYNAMIC(cTerrainTab, CDialogEx)

cTerrainTab::cTerrainTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TERRAIN_TAB, pParent)
	, m_pIncrementSliderCtl(NULL)
	, m_pIncrementEditCtl(NULL)
	, m_pBrushSizeSliderCtl(NULL)
	, m_pBrushSizeEditCtl(NULL)
	, m_pFlatSizeSliderCtl(NULL)
	, m_pFlatSizeEditCtl(NULL)
    , m_eEditType(g_pMapDataManager->GetTerEditType())
    , m_fIncrement(g_pMapDataManager->GetTerIncrement())
    , m_fBrushSize(g_pMapDataManager->GetTerBrushSize())
    , m_fFlatSize(g_pMapDataManager->GetTerFlatSize())
{

}

cTerrainTab::~cTerrainTab()
{
}

BOOL cTerrainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// == 지형 높이 증가 값 설정 초기화 ==
	m_pIncrementSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_INCREMENT_SLI);
	m_pIncrementEditCtl = (CEdit*)GetDlgItem(IDC_INCREMENT_EDI);

	// 높이 증가율 슬라이더 기본 설정
	m_pIncrementSliderCtl->SetRange(1, 100);			// 사용영역 값 설정
	m_pIncrementSliderCtl->SetRangeMin(1);				// 최소 값 설정
	m_pIncrementSliderCtl->SetRangeMax(100);			// 최대 값 설정
	m_pIncrementSliderCtl->SetPos(m_fIncrement * 10.0f);		// 위치 설정
	m_pIncrementSliderCtl->SetTicFreq(10);				// 눈금 간격 설정
	m_pIncrementSliderCtl->SetLineSize(1);				// 증가 크기(키보드로 컨트롤 할 때)
	m_pIncrementSliderCtl->SetPageSize(5);				// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 높이 증가율 출력
    char str[10];
    sprintf(str, "%0.1f", m_fIncrement);
    SetDlgItemTextA(IDC_INCREMENT_EDI, str);

	// == 브러쉬 사이즈 설정 초기화 ==
	m_pBrushSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_SIZE_SLI);
	m_pBrushSizeEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_SIZE_EDI);

	// 브러쉬 사이즈 슬라이더 기본 설정
	m_pBrushSizeSliderCtl->SetRange(1, 100);		// 사용영역 값 설정
	m_pBrushSizeSliderCtl->SetRangeMin(1);		// 최소 값 설정
	m_pBrushSizeSliderCtl->SetRangeMax(100);		// 최대 값 설정
	m_pBrushSizeSliderCtl->SetPos(m_fBrushSize);	// 위치 설정
	m_pBrushSizeSliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pBrushSizeSliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pBrushSizeSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_fBrushSize);

	// == 평지 사이즈 설정 초기화 ==
	m_pFlatSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_FLAT_SIZE_SLI);
	m_pFlatSizeEditCtl = (CEdit*)GetDlgItem(IDC_FLAT_SIZE_EDI);

	// 평지 사이즈 슬라이더 기본 설정
	m_pFlatSizeSliderCtl->SetRange(0, 100);		// 사용영역 값 설정
	m_pFlatSizeSliderCtl->SetRangeMin(0);			// 최소 값 설정
	m_pFlatSizeSliderCtl->SetRangeMax(100);			// 최대 값 설정
	m_pFlatSizeSliderCtl->SetPos(m_fFlatSize);		// 위치 설정
	m_pFlatSizeSliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pFlatSizeSliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pFlatSizeSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 평지 사이즈 출력
	SetDlgItemInt(IDC_FLAT_SIZE_EDI, m_fFlatSize);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cTerrainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// == 텍스쳐 선택 라디오 버튼 초기화 및 연결 ==
	DDX_Radio(pDX, IDC_INCREASE_RAD, (int&)m_eEditType); // 지형 높이기 타입으로 기본 설정

}


BEGIN_MESSAGE_MAP(cTerrainTab, CDialogEx)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_INCREASE_RAD, IDC_RESET_RAD, &cTerrainTab::OnSelectTextureRadio)
	ON_EN_CHANGE(IDC_INCREMENT_EDI, &cTerrainTab::OnChangeIncrementEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_INCREMENT_SPI, &cTerrainTab::OnDeltaposIncrementSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_INCREMENT_SLI, &cTerrainTab::OnCustomDrawIncrementSlider)
	ON_EN_CHANGE(IDC_BRUSH_SIZE_EDI, &cTerrainTab::OnChangeBrushSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BRUSH_SIZE_SPI, &cTerrainTab::OnDeltaposBrushSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRUSH_SIZE_SLI, &cTerrainTab::OnCustomDrawBrushSizeSlider)
	ON_EN_CHANGE(IDC_FLAT_SIZE_EDI, &cTerrainTab::OnChangeFlatSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FLAT_SIZE_SPI, &cTerrainTab::OnDeltaposFlatSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FLAT_SIZE_SLI, &cTerrainTab::OnCustomDrawFlatSizeSlider)
END_MESSAGE_MAP()


// cTerrainTab 메시지 처리기

// 지형 편집 타입 설정 (라디오 버튼으로 셋팅)
void cTerrainTab::OnSelectTextureRadio(UINT ID)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 변경사항이 있을 때 사용하는 함수! -> 알아서 m_unEditType값이 변경됨
	UpdateData();
}

// == 지형 높이 증가율 ==================================================================================================
// 지형 높이 증가율 설정 (컨트롤 에티더)
void cTerrainTab::OnChangeIncrementEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
    CString str = "";
    GetDlgItemText(IDC_INCREMENT_EDI, str);
    m_fIncrement = atof(str);

	// 슬라이더 위치 설정
	m_pIncrementSliderCtl->SetPos(m_fIncrement * 10.0f);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pIncrementEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pIncrementEditCtl->SetFocus();		// 포커스를 맞춤
	m_pIncrementEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 지형 높이 증가율 설정 (스핀)
void cTerrainTab::OnDeltaposIncrementSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fIncrement >= 100)
		{
			return;
		}
		m_fIncrement += 0.1f;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fIncrement <= 0)
		{
			return;
		}
		m_fIncrement -= 0.1f;
	}

	// 높이 값 출력
    char str[10];
    sprintf(str, "%0.1f", m_fIncrement);
    SetDlgItemTextA(IDC_INCREMENT_EDI, str);

	// 슬라이더 위치 설정
	m_pIncrementSliderCtl->SetPos(m_fIncrement * 10.0f);		// 위치 설정

	*pResult = 0;
}

// 지형 높이 증가율 설정 (슬라이더)
void cTerrainTab::OnCustomDrawIncrementSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 높이 값 넣기
	m_fIncrement = m_pIncrementSliderCtl->GetPos() * 0.1f;

	// 높이 값 출력
    char str[10];
    sprintf(str, "%0.1f", m_fIncrement);
    SetDlgItemTextA(IDC_INCREMENT_EDI, str);

	*pResult = 0;
}

// == 브러쉬 사이즈 ==================================================================================================
// 브러쉬 사이즈 설정 (에디터)
void cTerrainTab::OnChangeBrushSizeEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fBrushSize = GetDlgItemInt(IDC_BRUSH_SIZE_EDI);

	// 슬라이더 위치 설정
	m_pBrushSizeSliderCtl->SetPos(m_fBrushSize);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pBrushSizeEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
	m_pBrushSizeEditCtl->SetFocus();		// 포커스를 맞춤
	m_pBrushSizeEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 브러쉬 사이즈 설정 (스핀)
void cTerrainTab::OnDeltaposBrushSizeSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fBrushSize >= 100)
		{
			return;
		}
		++m_fBrushSize;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fBrushSize <= 1)
		{
			return;
		}
		--m_fBrushSize;
	}

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_fBrushSize);

	// 슬라이더 위치 설정
	m_pBrushSizeSliderCtl->SetPos(m_fBrushSize);		// 위치 설정

	*pResult = 0;
}

//브러쉬 사이즈 설정 (슬라이더)
void cTerrainTab::OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 브러쉬 사이즈 넣기
	m_fBrushSize = m_pBrushSizeSliderCtl->GetPos();

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_fBrushSize);

	*pResult = 0;
}

// == 평지 사이즈 ==================================================================================================
// 평지 사이즈 설정 (에디터)
void cTerrainTab::OnChangeFlatSizeEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fFlatSize = GetDlgItemInt(IDC_FLAT_SIZE_EDI);

	// 슬라이더 위치 설정
	m_pFlatSizeSliderCtl->SetPos(m_fFlatSize);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pFlatSizeEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
	m_pFlatSizeEditCtl->SetFocus();			// 포커스를 맞춤
	m_pFlatSizeEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 평지 사이즈 설정 (스핀)
void cTerrainTab::OnDeltaposFlatSizeSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fFlatSize >= 100)
		{
			return;
		}
		++m_fFlatSize;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fFlatSize <= 0)
		{
			return;
		}
		--m_fFlatSize;
	}

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_FLAT_SIZE_EDI, m_fFlatSize);

	// 슬라이더 위치 설정
	m_pFlatSizeSliderCtl->SetPos(m_fFlatSize);		// 위치 설정

	*pResult = 0;
}

// 평지 사이즈 설정 (슬라이더)
void cTerrainTab::OnCustomDrawFlatSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 평지 사이즈 넣기
	m_fFlatSize = m_pFlatSizeSliderCtl->GetPos();

	// 평지 사이즈 출력
	SetDlgItemInt(IDC_FLAT_SIZE_EDI, m_fFlatSize);

	*pResult = 0;
}
