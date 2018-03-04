// cWaterTab.cpp: 구현 파일
//

#include "stdafx.h"
#include "cWaterTab.h"
#include "afxdialogex.h"
#include "Resource.h"

// cWaterTab 대화 상자

IMPLEMENT_DYNAMIC(cWaterTab, CDialogEx)

cWaterTab::cWaterTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WATER_TAB, pParent)
	, m_pWaterPosYSliderCtl(NULL)
	, m_pWaterPosYEditCtl(NULL)
	, m_nWaterPosY(0)
	, m_pFlowRateSliderCtl(NULL)
	, m_pFlowRateEditCtl(NULL)
	, m_nFlowRate(5)
	, m_pAmplitudeSliderCtl(NULL)
	, m_pAmplitudeEditCtl(NULL)
	, m_nAmplitude(5)
{
}

cWaterTab::~cWaterTab()
{
}

BOOL cWaterTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// == 물 Y축 위치 설정 초기화 ==
	m_pWaterPosYSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_POS_Y_SLI);
	m_pWaterPosYEditCtl = (CEdit*)GetDlgItem(IDC_WATER_POS_Y_EDI);

	// 물 Y축 위치값 슬라이더 기본 설정
	m_pWaterPosYSliderCtl->SetRange(0, 256);		// 사용영역 값 설정
	m_pWaterPosYSliderCtl->SetRangeMin(0);			// 최소 값 설정
	m_pWaterPosYSliderCtl->SetRangeMax(255);		// 최대 값 설정
	m_pWaterPosYSliderCtl->SetPos(m_nWaterPosY);	// 위치 설정
	m_pWaterPosYSliderCtl->SetTicFreq(64);			// 눈금 간격 설정
	m_pWaterPosYSliderCtl->SetLineSize(16);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pWaterPosYSliderCtl->SetPageSize(64);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 물 Y축 위치값 출력
	SetDlgItemInt(IDC_WATER_POS_Y_EDI, m_nWaterPosY);

	// == 물 유속 설정 초기화 ==
	m_pFlowRateSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_FLOW_RATE_SLI);
	m_pFlowRateEditCtl = (CEdit*)GetDlgItem(IDC_WATER_FLOW_RATE_EDI);

	// 물 유속값 슬라이더 기본 설정
	m_pFlowRateSliderCtl->SetRange(0, 10);			// 사용영역 값 설정
	m_pFlowRateSliderCtl->SetRangeMin(0);			// 최소 값 설정
	m_pFlowRateSliderCtl->SetRangeMax(10);			// 최대 값 설정
	m_pFlowRateSliderCtl->SetPos(m_nFlowRate);		// 위치 설정
	m_pFlowRateSliderCtl->SetTicFreq(1);			// 눈금 간격 설정
	m_pFlowRateSliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pFlowRateSliderCtl->SetPageSize(1);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 물 유속값 출력
	SetDlgItemInt(IDC_WATER_FLOW_RATE_EDI, m_nFlowRate);

	// == 물 진폭 설정 초기화 ==
	m_pAmplitudeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_AMPLITUDE_SLI);
	m_pAmplitudeEditCtl = (CEdit*)GetDlgItem(IDC_WATER_AMPLITUDE_EDI);

	// 물 진폭값 슬라이더 기본 설정
	m_pAmplitudeSliderCtl->SetRange(0, 10);			// 사용영역 값 설정
	m_pAmplitudeSliderCtl->SetRangeMin(0);			// 최소 값 설정
	m_pAmplitudeSliderCtl->SetRangeMax(10);			// 최대 값 설정
	m_pAmplitudeSliderCtl->SetPos(m_nAmplitude);		// 위치 설정
	m_pAmplitudeSliderCtl->SetTicFreq(1);			// 눈금 간격 설정
	m_pAmplitudeSliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pAmplitudeSliderCtl->SetPageSize(1);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 물 진폭값 출력
	SetDlgItemInt(IDC_WATER_AMPLITUDE_EDI, m_nAmplitude);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cWaterTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cWaterTab, CDialogEx)
	ON_EN_CHANGE(IDC_WATER_POS_Y_EDI, &cWaterTab::OnChangeWaterPosYEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_POS_Y_SPI, &cWaterTab::OnDeltaposWaterPosYSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_POS_Y_SLI, &cWaterTab::OnCustomDrawWaterPosYSlider)
	ON_EN_CHANGE(IDC_WATER_FLOW_RATE_EDI, &cWaterTab::OnChangeWaterFlowRateEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_FLOW_RATE_SPI, &cWaterTab::OnDeltaposWaterFlowRateSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_FLOW_RATE_SLI, &cWaterTab::OnCustomDrawWaterFlowRateSlider)
	ON_EN_CHANGE(IDC_WATER_AMPLITUDE_EDI, &cWaterTab::OnChangeWaterAmplitudeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_AMPLITUDE_SPI, &cWaterTab::OnDeltaposWaterAmplitudeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_AMPLITUDE_SLI, &cWaterTab::OnCustomDrawWaterAmplitudeSlider)
END_MESSAGE_MAP()


// cWaterTab 메시지 처리기

// == 물 Y축 값 ==================================================================================================
// 물 Y축 값 설정 (에디터)
void cWaterTab::OnChangeWaterPosYEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_nWaterPosY = GetDlgItemInt(IDC_WATER_POS_Y_EDI);

	// 슬라이더 위치 설정
	m_pWaterPosYSliderCtl->SetPos(m_nWaterPosY);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pWaterPosYEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pWaterPosYEditCtl->SetFocus();		// 포커스를 맞춤
	m_pWaterPosYEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 물 Y축 값 설정 (스핀)
void cWaterTab::OnDeltaposWaterPosYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_nWaterPosY >= 255)
		{
			return;
		}
		++m_nWaterPosY;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nWaterPosY <= 0)
		{
			return;
		}
		--m_nWaterPosY;
	}

	// 물 Y축 위치값 출력
	SetDlgItemInt(IDC_WATER_POS_Y_EDI, m_nWaterPosY);

	// 슬라이더 위치 설정
	m_pWaterPosYSliderCtl->SetPos(m_nWaterPosY);		// 위치 설정

	*pResult = 0;
}

// 물 Y축 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawWaterPosYSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 물 Y축 값 넣기
	m_nWaterPosY = m_pWaterPosYSliderCtl->GetPos();

	// 물 Y축 값 출력
	SetDlgItemInt(IDC_WATER_POS_Y_EDI, m_nWaterPosY);

	*pResult = 0;
}

// == 물 유속 값 ==================================================================================================
// 물 유속 값 설정 (에디터)
void cWaterTab::OnChangeWaterFlowRateEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_nFlowRate = GetDlgItemInt(IDC_WATER_FLOW_RATE_EDI);

	// 슬라이더 위치 설정
	m_pFlowRateSliderCtl->SetPos(m_nFlowRate);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pFlowRateEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pFlowRateEditCtl->SetFocus();		// 포커스를 맞춤
	m_pFlowRateEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 물 유속 값 설정 (스핀)
void cWaterTab::OnDeltaposWaterFlowRateSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_nFlowRate >= 10)
		{
			return;
		}
		++m_nFlowRate;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nFlowRate <= 0)
		{
			return;
		}
		--m_nFlowRate;
	}

	// 물 유속값 출력
	SetDlgItemInt(IDC_WATER_FLOW_RATE_EDI, m_nFlowRate);

	// 슬라이더 위치 설정
	m_pFlowRateSliderCtl->SetPos(m_nFlowRate);		// 위치 설정

	*pResult = 0;
}

// 물 유속 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawWaterFlowRateSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 물 유속값 넣기
	m_nFlowRate = m_pFlowRateSliderCtl->GetPos();

	// 물 유속값 출력
	SetDlgItemInt(IDC_WATER_FLOW_RATE_EDI, m_nFlowRate);

	*pResult = 0;
}

// == 물 진폭 값 ==================================================================================================
// 물 진폭 값 설정 (에디터)
void cWaterTab::OnChangeWaterAmplitudeEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_nAmplitude = GetDlgItemInt(IDC_WATER_AMPLITUDE_EDI);

	// 슬라이더 위치 설정
	m_pAmplitudeSliderCtl->SetPos(m_nAmplitude);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pAmplitudeEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
	m_pAmplitudeEditCtl->SetFocus();		// 포커스를 맞춤
	m_pAmplitudeEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 물 진폭 값 설정 (스핀)
void cWaterTab::OnDeltaposWaterAmplitudeSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_nAmplitude >= 10)
		{
			return;
		}
		++m_nAmplitude;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nAmplitude <= 0)
		{
			return;
		}
		--m_nAmplitude;
	}

	// 물 진폭값 출력
	SetDlgItemInt(IDC_WATER_AMPLITUDE_EDI, m_nAmplitude);

	// 슬라이더 위치 설정
	m_pAmplitudeSliderCtl->SetPos(m_nAmplitude);		// 위치 설정

	*pResult = 0;
}

// 물 진폭 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawWaterAmplitudeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 물 진폭값 넣기
	m_nAmplitude = m_pAmplitudeSliderCtl->GetPos();

	// 물 진폭값 출력
	SetDlgItemInt(IDC_WATER_AMPLITUDE_EDI, m_nAmplitude);

	*pResult = 0;
}