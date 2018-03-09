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
    , m_eUpDown(g_pMapDataManager->GetTerUpDown())
    , m_eEditType(g_pMapDataManager->GetTerEditType())
    , m_eBrushType(g_pMapDataManager->GetTerBrushType())
    , m_fPower(g_pMapDataManager->GetTerEditPower())
    , m_fEditHeight(g_pMapDataManager->GetTerEditHeight())
    , m_fBrushSize(g_pMapDataManager->GetTerBrushSize())
	, m_pPowerSliderCtl(NULL)
	, m_pPowerEditCtl(NULL)
	, m_pEditHeightSliderCtl(NULL)
	, m_pEditHeightEditCtl(NULL)
	, m_pBrushSizeSliderCtl(NULL)
	, m_pBrushSizeEditCtl(NULL)
{

}

cTerrainTab::~cTerrainTab()
{
}

BOOL cTerrainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// == 편집 파워 값 설정 초기화 ==
	m_pPowerSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_POWER_SLI);
	m_pPowerEditCtl = (CEdit*)GetDlgItem(IDC_POWER_EDI);

	// 높이 증가율 슬라이더 기본 설정
	m_pPowerSliderCtl->SetRange(1, 100);			// 사용영역 값 설정
	m_pPowerSliderCtl->SetRangeMin(1);				// 최소 값 설정
	m_pPowerSliderCtl->SetRangeMax(100);			// 최대 값 설정
	m_pPowerSliderCtl->SetPos(m_fPower * 10.0f);		// 위치 설정
	m_pPowerSliderCtl->SetTicFreq(10);				// 눈금 간격 설정
	m_pPowerSliderCtl->SetLineSize(1);				// 증가 크기(키보드로 컨트롤 할 때)
	m_pPowerSliderCtl->SetPageSize(5);				// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 높이 증가율 출력
    char str[10];
    sprintf(str, "%0.1f", m_fPower);
    SetDlgItemTextA(IDC_POWER_EDI, str);

    // == 편집 높이 설정 초기화 ==
    m_pEditHeightSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_EDIT_HEIGHT_SLI);
    m_pEditHeightEditCtl = (CEdit*)GetDlgItem(IDC_EDIT_HEIGHT_EDI);

    // 편집 높이 슬라이더 기본 설정
    m_pEditHeightSliderCtl->SetRange(0, 255);		    // 사용영역 값 설정
    m_pEditHeightSliderCtl->SetRangeMin(0);			    // 최소 값 설정
    m_pEditHeightSliderCtl->SetRangeMax(255);			// 최대 값 설정
    m_pEditHeightSliderCtl->SetPos(m_fEditHeight);		// 위치 설정
    m_pEditHeightSliderCtl->SetTicFreq(16);			    // 눈금 간격 설정
    m_pEditHeightSliderCtl->SetLineSize(1);			    // 증가 크기(키보드로 컨트롤 할 때)
    m_pEditHeightSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

    // 편집 높이 출력
    SetDlgItemInt(IDC_EDIT_HEIGHT_EDI, m_fEditHeight);

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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cTerrainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// == 라디오 버튼 초기화 및 연결 == -> 첫번째 라디오 ID, 변수
	DDX_Radio(pDX, IDC_UP_RAD, (int&)m_eUpDown); 
    DDX_Radio(pDX, IDC_EDIT_RAD, (int&)m_eEditType);
    DDX_Radio(pDX, IDC_SMOOTH_RAD, (int&)m_eBrushType);
}


BEGIN_MESSAGE_MAP(cTerrainTab, CDialogEx)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_UP_RAD, IDC_DOWN_RAD, &cTerrainTab::OnSelectUpDownRadio)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_EDIT_RAD, IDC_RESET_RAD, &cTerrainTab::OnSelectEditTypeRadio)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_SMOOTH_RAD, IDC_SHARP_RAD, &cTerrainTab::OnSelectBrushTypeRadio)
    ON_EN_CHANGE(IDC_POWER_EDI, &cTerrainTab::OnChangePowerEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_POWER_SPI, &cTerrainTab::OnDeltaposPowerSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_POWER_SLI, &cTerrainTab::OnCustomDrawPowerSlider)
	ON_EN_CHANGE(IDC_BRUSH_SIZE_EDI, &cTerrainTab::OnChangeBrushSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BRUSH_SIZE_SPI, &cTerrainTab::OnDeltaposBrushSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRUSH_SIZE_SLI, &cTerrainTab::OnCustomDrawBrushSizeSlider)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT_EDI, &cTerrainTab::OnChangeEditHeightEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_EDIT_HEIGHT_SPI, &cTerrainTab::OnDeltaposEditHeightSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_EDIT_HEIGHT_SLI, &cTerrainTab::OnCustomDrawEditHeightSlider)
	
END_MESSAGE_MAP()


// cTerrainTab 메시지 처리기

// 업다운 선택
void cTerrainTab::OnSelectUpDownRadio(UINT ID)
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 변경사항이 있을 때 사용하는 함수! -> 알아서 연결된 값이 변경됨
    UpdateData();
}

// 편집 높이 선택
void cTerrainTab::OnSelectEditTypeRadio(UINT ID)
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 변경사항이 있을 때 사용하는 함수! -> 알아서 연결된 값이 변경됨
    UpdateData();
}

// 브러쉬 타입 선택
void cTerrainTab::OnSelectBrushTypeRadio(UINT ID)
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 변경사항이 있을 때 사용하는 함수! -> 알아서 연결된 값이 변경됨
    UpdateData();
}

// == 편집 파워 ==================================================================================================
// 편집 파워 설정 (컨트롤 에티더)
void cTerrainTab::OnChangePowerEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
    CString str = "";
    GetDlgItemText(IDC_POWER_EDI, str);
    m_fPower = atof(str);

	// 슬라이더 위치 설정
	m_pPowerSliderCtl->SetPos(m_fPower * 10.0f);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pPowerEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pPowerEditCtl->SetFocus();		// 포커스를 맞춤
	m_pPowerEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 편집 파워 설정 (스핀)
void cTerrainTab::OnDeltaposPowerSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fPower >= 100)
		{
			return;
		}
		m_fPower += 0.1f;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fPower <= 0)
		{
			return;
		}
		m_fPower -= 0.1f;
	}

	// 높이 값 출력
    char str[10];
    sprintf(str, "%0.1f", m_fPower);
    SetDlgItemTextA(IDC_POWER_EDI, str);

	// 슬라이더 위치 설정
	m_pPowerSliderCtl->SetPos(m_fPower * 10.0f);		// 위치 설정

	*pResult = 0;
}

// 편집 파워 설정 (슬라이더)
void cTerrainTab::OnCustomDrawPowerSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 높이 값 넣기
	m_fPower = m_pPowerSliderCtl->GetPos() * 0.1f;

	// 높이 값 출력
    char str[10];
    sprintf(str, "%0.1f", m_fPower);
    SetDlgItemTextA(IDC_POWER_EDI, str);

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

// == 편집 높이 ==================================================================================================
// 편집 높이 설정 (에디터)
void cTerrainTab::OnChangeEditHeightEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fEditHeight = GetDlgItemInt(IDC_EDIT_HEIGHT_EDI);

	// 슬라이더 위치 설정
	m_pEditHeightSliderCtl->SetPos(m_fEditHeight);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pEditHeightEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
	m_pEditHeightEditCtl->SetFocus();			// 포커스를 맞춤
	m_pEditHeightEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 편집 높이 설정 (스핀)
void cTerrainTab::OnDeltaposEditHeightSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fEditHeight >= 255)
		{
			return;
		}
		++m_fEditHeight;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fEditHeight <= 0)
		{
			return;
		}
		--m_fEditHeight;
	}

	// 편집 높이 출력
	SetDlgItemInt(IDC_EDIT_HEIGHT_EDI, m_fEditHeight);

	// 슬라이더 위치 설정
	m_pEditHeightSliderCtl->SetPos(m_fEditHeight);		// 위치 설정

	*pResult = 0;
}

// 편집 높이 설정 (슬라이더)
void cTerrainTab::OnCustomDrawEditHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 편집 높이 넣기
	m_fEditHeight = m_pEditHeightSliderCtl->GetPos();

	// 편집 높이 출력
	SetDlgItemInt(IDC_EDIT_HEIGHT_EDI, m_fEditHeight);

	*pResult = 0;
}
