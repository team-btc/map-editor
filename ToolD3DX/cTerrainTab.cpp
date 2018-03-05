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
	, m_unEditType(0)
	, m_pGrowthSliderCtl(NULL)
	, m_pGrowthEditCtl(NULL)
	, m_nGrowthRate(3)
	, m_pInclinationSliderCtl(NULL)
	, m_pInclinationEditCtl(NULL)
	, m_nInclinationRate(45)
	, m_pBrushSizeSliderCtl(NULL)
	, m_pBrushSizeEditCtl(NULL)
	, m_nBrushSize(100)
	, m_pFlatSizeSliderCtl(NULL)
	, m_pFlatSizeEditCtl(NULL)
	, m_nFlatSize(100)
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
	m_pGrowthSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_GROTH_SLI);
	m_pGrowthEditCtl = (CEdit*)GetDlgItem(IDC_GROWTH_EDI);

	// 높이 증가율 슬라이더 기본 설정
	m_pGrowthSliderCtl->SetRange(0, 256);			// 사용영역 값 설정
	m_pGrowthSliderCtl->SetRangeMin(0);				// 최소 값 설정
	m_pGrowthSliderCtl->SetRangeMax(255);			// 최대 값 설정
	m_pGrowthSliderCtl->SetPos(m_nGrowthRate);		// 위치 설정
	m_pGrowthSliderCtl->SetTicFreq(32);				// 눈금 간격 설정
	m_pGrowthSliderCtl->SetLineSize(4);				// 증가 크기(키보드로 컨트롤 할 때)
	m_pGrowthSliderCtl->SetPageSize(12);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 높이 증가율 출력
	SetDlgItemInt(IDC_GROWTH_EDI, m_nGrowthRate);

	// == 지형 경사율 설정 초기화 ==
	m_pInclinationSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_INCLINATION_SLI);
	m_pInclinationEditCtl = (CEdit*)GetDlgItem(IDC_INCLINATION_EDI);

	// 높이 증가율 슬라이더 기본 설정
	m_pInclinationSliderCtl->SetRange(0, 90);			// 사용영역 값 설정
	m_pInclinationSliderCtl->SetRangeMin(45);			// 최소 값 설정
	m_pInclinationSliderCtl->SetRangeMax(90);			// 최대 값 설정
	m_pInclinationSliderCtl->SetPos(m_nInclinationRate);// 위치 설정
	m_pInclinationSliderCtl->SetTicFreq(5);				// 눈금 간격 설정
	m_pInclinationSliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pInclinationSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 경사율 출력
	SetDlgItemInt(IDC_INCLINATION_EDI, m_nInclinationRate);

	// == 브러쉬 사이즈 설정 초기화 ==
	m_pBrushSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_SIZE_SLI);
	m_pBrushSizeEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_SIZE_EDI);

	// 브러쉬 사이즈 슬라이더 기본 설정
	m_pBrushSizeSliderCtl->SetRange(100, 500);		// 사용영역 값 설정
	m_pBrushSizeSliderCtl->SetRangeMin(100);		// 최소 값 설정
	m_pBrushSizeSliderCtl->SetRangeMax(500);		// 최대 값 설정
	m_pBrushSizeSliderCtl->SetPos(m_nBrushSize);	// 위치 설정
	m_pBrushSizeSliderCtl->SetTicFreq(50);			// 눈금 간격 설정
	m_pBrushSizeSliderCtl->SetLineSize(20);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pBrushSizeSliderCtl->SetPageSize(50);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_nBrushSize);

	// == 평지 사이즈 설정 초기화 ==
	m_pFlatSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_FLAT_SIZE_SLI);
	m_pFlatSizeEditCtl = (CEdit*)GetDlgItem(IDC_FLAT_SIZE_EDI);

	// 브러쉬 사이즈 슬라이더 기본 설정
	m_pFlatSizeSliderCtl->SetRange(100, 500);		// 사용영역 값 설정
	m_pFlatSizeSliderCtl->SetRangeMin(100);			// 최소 값 설정
	m_pFlatSizeSliderCtl->SetRangeMax(500);			// 최대 값 설정
	m_pFlatSizeSliderCtl->SetPos(m_nFlatSize);		// 위치 설정
	m_pFlatSizeSliderCtl->SetTicFreq(50);			// 눈금 간격 설정
	m_pFlatSizeSliderCtl->SetLineSize(20);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pFlatSizeSliderCtl->SetPageSize(50);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 평지 사이즈 출력
	SetDlgItemInt(IDC_FLAT_SIZE_EDI, m_nFlatSize);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cTerrainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// == 텍스쳐 선택 라디오 버튼 초기화 및 연결 ==
	DDX_Radio(pDX, IDC_INCREASE_RAD, (int&)m_unEditType); // 지형 높이기 타입으로 기본 설정

}


BEGIN_MESSAGE_MAP(cTerrainTab, CDialogEx)
	ON_BN_CLICKED(IDC_INCREASE_RAD, &cTerrainTab::OnClickIncreaseRadio)
	ON_EN_CHANGE(IDC_GROWTH_EDI, &cTerrainTab::OnChangeGrowthEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GROWTH_SPI, &cTerrainTab::OnDeltaposGrowthSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GROTH_SLI, &cTerrainTab::OnCustomDrawGrothSlider)
	ON_EN_CHANGE(IDC_INCLINATION_EDI, &cTerrainTab::OnChangeInclinationEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_INCLINATION_SPI, &cTerrainTab::OnDeltaposInclinationSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_INCLINATION_SLI, &cTerrainTab::OnCustomDrawInclinationSlider)
	ON_EN_CHANGE(IDC_BRUSH_SIZE_EDI, &cTerrainTab::OnChangeBrushSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BRUSH_SIZE_SPI, &cTerrainTab::OnDeltaposBrushSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRUSH_SIZE_SLI, &cTerrainTab::OnCustomDrawBrushSizeSlider)
	ON_EN_CHANGE(IDC_FLAT_SIZE_EDI, &cTerrainTab::OnChangeFlatSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FLAT_SIZE_SPI, &cTerrainTab::OnDeltaposFlatSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FLAT_SIZE_SLI, &cTerrainTab::OnCustomDrawFlatSizeSlider)
END_MESSAGE_MAP()


// cTerrainTab 메시지 처리기

// 지형 편집 타입 설정 (라디오 버튼으로 셋팅)
void cTerrainTab::OnClickIncreaseRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 변경사항이 있을 때 사용하는 함수! -> 알아서 m_unEditType값이 변경됨
	UpdateData();
}

// == 지형 높이 증가율 ==================================================================================================
// 지형 높이 증가율 설정 (컨트롤 에티더)
void cTerrainTab::OnChangeGrowthEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_nGrowthRate = GetDlgItemInt(IDC_GROWTH_EDI);

	// 슬라이더 위치 설정
	m_pGrowthSliderCtl->SetPos(m_nGrowthRate);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pGrowthEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pGrowthEditCtl->SetFocus();		// 포커스를 맞춤
	m_pGrowthEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 지형 높이 증가율 설정 (스핀)
void cTerrainTab::OnDeltaposGrowthSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_nGrowthRate >= 255)
		{
			return;
		}
		++m_nGrowthRate;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nGrowthRate <= 0)
		{
			return;
		}
		--m_nGrowthRate;
	}

	// 높이 값 출력
	SetDlgItemInt(IDC_GROWTH_EDI, m_nGrowthRate);

	// 슬라이더 위치 설정
	m_pGrowthSliderCtl->SetPos(m_nGrowthRate);		// 위치 설정

	*pResult = 0;
}

// 지형 높이 증가율 설정 (슬라이더)
void cTerrainTab::OnCustomDrawGrothSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 높이 값 넣기
	m_nGrowthRate = m_pGrowthSliderCtl->GetPos();

	// 높이 값 출력
	SetDlgItemInt(IDC_GROWTH_EDI, m_nGrowthRate);

	*pResult = 0;
}

// == 지형 경사율 ==================================================================================================
// 지형 경사율 설정 (에디터)
void cTerrainTab::OnChangeInclinationEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_nInclinationRate = GetDlgItemInt(IDC_INCLINATION_EDI);

	// 슬라이더 위치 설정
	m_pInclinationSliderCtl->SetPos(m_nInclinationRate);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pInclinationEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
	m_pInclinationEditCtl->SetFocus();		// 포커스를 맞춤
	m_pInclinationEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 지형 경사율 설정 (스핀)
void cTerrainTab::OnDeltaposInclinationSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_nInclinationRate >= 90)
		{
			return;
		}
		++m_nInclinationRate;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nInclinationRate <= 45)
		{
			return;
		}
		--m_nInclinationRate;
	}

	// 경사 값 출력
	SetDlgItemInt(IDC_INCLINATION_EDI, m_nInclinationRate);

	// 슬라이더 위치 설정
	m_pInclinationSliderCtl->SetPos(m_nInclinationRate);		// 위치 설정

	*pResult = 0;
}

// 지형 경사율 설정 (슬라이더)
void cTerrainTab::OnCustomDrawInclinationSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 경사 값 넣기
	m_nInclinationRate = m_pInclinationSliderCtl->GetPos();

	// 경사 값 출력
	SetDlgItemInt(IDC_INCLINATION_EDI, m_nInclinationRate);

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
	m_nBrushSize = GetDlgItemInt(IDC_BRUSH_SIZE_EDI);

	// 슬라이더 위치 설정
	m_pBrushSizeSliderCtl->SetPos(m_nBrushSize);		// 위치 설정

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
		if (m_nBrushSize >= 500)
		{
			return;
		}
		++m_nBrushSize;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nBrushSize <= 100)
		{
			return;
		}
		--m_nBrushSize;
	}

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_nBrushSize);

	// 슬라이더 위치 설정
	m_pBrushSizeSliderCtl->SetPos(m_nBrushSize);		// 위치 설정

	*pResult = 0;
}

//브러쉬 사이즈 설정 (슬라이더)
void cTerrainTab::OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 브러쉬 사이즈 넣기
	m_nBrushSize = m_pBrushSizeSliderCtl->GetPos();

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_nBrushSize);

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
	m_nFlatSize = GetDlgItemInt(IDC_FLAT_SIZE_EDI);

	// 슬라이더 위치 설정
	m_pFlatSizeSliderCtl->SetPos(m_nFlatSize);		// 위치 설정

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
		if (m_nFlatSize >= 500)
		{
			return;
		}
		++m_nFlatSize;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_nFlatSize <= 100)
		{
			return;
		}
		--m_nFlatSize;
	}

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_FLAT_SIZE_EDI, m_nFlatSize);

	// 슬라이더 위치 설정
	m_pFlatSizeSliderCtl->SetPos(m_nFlatSize);		// 위치 설정

	*pResult = 0;
}

// 평지 사이즈 설정 (슬라이더)
void cTerrainTab::OnCustomDrawFlatSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 평지 사이즈 넣기
	m_nFlatSize = m_pFlatSizeSliderCtl->GetPos();

	// 평지 사이즈 출력
	SetDlgItemInt(IDC_FLAT_SIZE_EDI, m_nFlatSize);

	*pResult = 0;
}
