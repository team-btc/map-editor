// cTextureTab.cpp: 구현 파일
//

#include "stdafx.h"
#include "cTextureTab.h"
#include "afxdialogex.h"
#include "Resource.h"

// cTextureTab 대화 상자

IMPLEMENT_DYNAMIC(cTextureTab, CDialogEx)

cTextureTab::cTextureTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEXTURE_TAB, pParent)
	, m_pTextureDensitySliderCtl(NULL)
	, m_pTextureDensityEditCtl(NULL)
	, m_pBrushSizeSliderCtl(NULL)	
	, m_pBrushSizeEditCtl(NULL)
    , m_pBrushDenSizeSliderCtl(NULL)
    , m_pBrushDenSizeEditCtl(NULL)
	, m_pBrushDensitySliderCtl(NULL)
	, m_pBrushDensityEditCtl(NULL)
	, m_pWalkableCheck(NULL)
    , m_eTextureIndex(g_pMapDataManager->GetCurrTexType())
    , m_isWalkable(g_pMapDataManager->GetWalkable())
    , m_fTextureDensity(g_pMapDataManager->GetTexDensity())
    , m_fBrushSize(g_pMapDataManager->GetTexBrushSize())
    , m_fBrushDenSize(g_pMapDataManager->GetTexBrushDenSize())
    , m_fBrushDensity(g_pMapDataManager->GetTexBrushDensity())
{

}

cTextureTab::~cTextureTab()
{
}

BOOL cTextureTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

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

	// == 텍스쳐 밀도값 설정 초기화 ==
	m_pTextureDensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_TEXTURE_DENSITY_SLI);
	m_pTextureDensityEditCtl = (CEdit*)GetDlgItem(IDC_TEXTURE_DENSITY_EDI);

	// 텍스쳐 밀도값 슬라이더 기본 설정
	m_pTextureDensitySliderCtl->SetRange(1, 100);		// 사용영역 값 설정
	m_pTextureDensitySliderCtl->SetRangeMin(10);		// 최소 값 설정
	m_pTextureDensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
	m_pTextureDensitySliderCtl->SetPos(m_fTextureDensity);	// 위치 설정
	m_pTextureDensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pTextureDensitySliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pTextureDensitySliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 텍스쳐 밀도값 출력
	SetDlgItemInt(IDC_TEXTURE_DENSITY_EDI, m_fTextureDensity);

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
	
    // == 브러쉬 밀도 사이즈 설정 초기화 ==
    m_pBrushDenSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_DENSITY_SIZE_SLI);
    m_pBrushDenSizeEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_DENSITY_SIZE_EDI);

    // 브러쉬 사이즈 슬라이더 기본 설정
    m_pBrushDenSizeSliderCtl->SetRange(0, 100);		// 사용영역 값 설정
    m_pBrushDenSizeSliderCtl->SetRangeMin(10);		// 최소 값 설정
    m_pBrushDenSizeSliderCtl->SetRangeMax(100);		// 최대 값 설정
    m_pBrushDenSizeSliderCtl->SetPos(m_fBrushDenSize);	// 위치 설정
    m_pBrushDenSizeSliderCtl->SetTicFreq(10);			// 눈금 간격 설정
    m_pBrushDenSizeSliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pBrushDenSizeSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

    // 브러쉬 사이즈 출력
    SetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI, m_fBrushDenSize);

	// == 브러쉬 밀도값 설정 초기화 ==
	m_pBrushDensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_DENSITY_SLI);
	m_pBrushDensityEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_DENSITY_EDI);

	// 브러쉬 밀도값 슬라이더 기본 설정
	m_pBrushDensitySliderCtl->SetRange(0, 100);		// 사용영역 값 설정
	m_pBrushDensitySliderCtl->SetRangeMin(10);		// 최소 값 설정
	m_pBrushDensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
	m_pBrushDensitySliderCtl->SetPos(m_fBrushDensity);	// 위치 설정
	m_pBrushDensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pBrushDensitySliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pBrushDensitySliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 브러쉬 밀도값 출력
	SetDlgItemInt(IDC_BRUSH_DENSITY_EDI, m_fBrushDensity);

	// == 걸을 수 있는지형 체크박스 초기화 ==
	m_pWalkableCheck = (CButton*)GetDlgItem(IDC_WALKABLE_CHE);
	m_pWalkableCheck->SetCheck(m_isWalkable);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cTextureTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// == 텍스쳐 선택 라디오 버튼 초기화 및 연결 ==
	DDX_Radio(pDX, ID_TERRAIN1_RAD, (int&)m_eTextureIndex); // 텍스쳐1번으로 라디오박스 설정
}

void cTextureTab::OnPaint()
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


BEGIN_MESSAGE_MAP(cTextureTab, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_TERRAIN1_RAD, &cTextureTab::OnClickTerrainRadio)
	ON_EN_CHANGE(IDC_TEXTURE_DENSITY_EDI, &cTextureTab::OnChangeTextureDensityEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TEXTURE_DENSITY_SPI, &cTextureTab::OnDeltaposTextureDensitySpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TEXTURE_DENSITY_SLI, &cTextureTab::OnCustomDrawTextureDensitySlider)
	ON_EN_CHANGE(IDC_BRUSH_SIZE_EDI, &cTextureTab::OnChangeBrushSizeEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BRUSH_SIZE_SPI, &cTextureTab::OnDeltaposBrushSizeSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRUSH_SIZE_SLI, &cTextureTab::OnCustomDrawBrushSizeSlider)
    ON_EN_CHANGE(IDC_BRUSH_DENSITY_SIZE_EDI, &cTextureTab::OnChangeBrushDenSizeEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_BRUSH_DENSITY_SIZE_SPI, &cTextureTab::OnDeltaposBrushDenSizeSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRUSH_DENSITY_SIZE_SLI, &cTextureTab::OnCustomDrawBrushDenSizeSlider)
	ON_EN_CHANGE(IDC_BRUSH_DENSITY_EDI, &cTextureTab::OnChangeBrushDensityEditer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BRUSH_DENSITY_SPI, &cTextureTab::OnDeltaposBrushDensitySpin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRUSH_DENSITY_SLI, &cTextureTab::OnCustomDrawBrushDensitySlider)
	ON_BN_CLICKED(IDC_WALKABLE_CHE, &cTextureTab::OnClickWalkableCheck)
END_MESSAGE_MAP()


// cTextureTab 메시지 처리기

// 텍스쳐 선택
void cTextureTab::OnClickTerrainRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 변경사항이 있을 때 사용하는 함수! -> 알아서 m_unTextureIndex값이 변경됨
	UpdateData();
}

// == 텍스쳐 밀도값 ==================================================================================================
// 텍스쳐 밀도값 설정 (에디터)
void cTextureTab::OnChangeTextureDensityEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fTextureDensity = GetDlgItemInt(IDC_TEXTURE_DENSITY_EDI);

	// 슬라이더 위치 설정
	m_pTextureDensitySliderCtl->SetPos(m_fTextureDensity);		// 위치 설정

															// 커서를 맨 뒤로 셋팅
	m_pTextureDensityEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
	m_pTextureDensityEditCtl->SetFocus();			// 포커스를 맞춤
	m_pTextureDensityEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 텍스쳐 밀도값 설정 (스핀)
void cTextureTab::OnDeltaposTextureDensitySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fTextureDensity >= 100)
		{
			return;
		}
		++m_fTextureDensity;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fTextureDensity <= 1)
		{
			return;
		}
		--m_fTextureDensity;
	}

	// 텍스쳐 밀도값 출력
	SetDlgItemInt(IDC_TEXTURE_DENSITY_EDI, m_fTextureDensity);

	// 슬라이더 위치 설정
	m_pTextureDensitySliderCtl->SetPos(m_fTextureDensity);		// 위치 설정

	*pResult = 0;
}

// 텍스쳐 밀도값 설정 (슬라이더)
void cTextureTab::OnCustomDrawTextureDensitySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 텍스쳐 밀도값 넣기
	m_fTextureDensity = m_pTextureDensitySliderCtl->GetPos();

	// 텍스쳐 밀도값 출력
	SetDlgItemInt(IDC_TEXTURE_DENSITY_EDI, m_fTextureDensity);

	*pResult = 0;
}

// == 브러쉬 사이즈 ==================================================================================================
// 브러쉬 사이즈 설정 (에디터)
void cTextureTab::OnChangeBrushSizeEditer()
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
void cTextureTab::OnDeltaposBrushSizeSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fBrushSize >= 500)
		{
			return;
		}
		++m_fBrushSize;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fBrushSize <= 100)
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

// 브러쉬 사이즈 설정 (슬라이더)
void cTextureTab::OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 브러쉬 사이즈 넣기
	m_fBrushSize = m_pBrushSizeSliderCtl->GetPos();

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, m_fBrushSize);

	*pResult = 0;
}

// == 브러쉬 밀도 사이즈 ==================================================================================================
// 브러쉬 밀도 사이즈 설정 (에디터)
void cTextureTab::OnChangeBrushDenSizeEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    m_fBrushDenSize = GetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI);

    // 슬라이더 위치 설정
    m_pBrushDenSizeSliderCtl->SetPos(m_fBrushDenSize);		// 위치 설정

    // 커서를 맨 뒤로 셋팅
    m_pBrushDenSizeEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
    m_pBrushDenSizeEditCtl->SetFocus();			// 포커스를 맞춤
    m_pBrushDenSizeEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 브러쉬 밀도 사이즈 설정 (스핀)
void cTextureTab::OnDeltaposBrushDenSizeSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fBrushDenSize >= 100)
        {
            return;
        }
        ++m_fBrushDenSize;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fBrushDenSize <= 1)
        {
            return;
        }
        --m_fBrushDenSize;
    }

    // 텍스쳐 밀도값 출력
    SetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI, m_fBrushDenSize);

    // 슬라이더 위치 설정
    m_pBrushDenSizeSliderCtl->SetPos(m_fBrushDenSize);		// 위치 설정

    *pResult = 0;
}

// 브러쉬 밀도 사이즈 설정 (슬라이더)
void cTextureTab::OnCustomDrawBrushDenSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 브러쉬 밀도 사이즈 넣기
    m_fBrushDenSize = m_pBrushDenSizeSliderCtl->GetPos();

    // 브러쉬 밀도 사이즈 출력
    SetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI, m_fBrushDenSize);

    *pResult = 0;
}

// == 브러쉬 밀도값 ==================================================================================================
// 브러쉬 밀도값 설정 (에디터)
void cTextureTab::OnChangeBrushDensityEditer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 에디터에 입력 된 값  가져오기
	m_fBrushDensity = GetDlgItemInt(IDC_BRUSH_DENSITY_EDI);

	// 슬라이더 위치 설정
	m_pBrushDensitySliderCtl->SetPos(m_fBrushDensity);		// 위치 설정

	// 커서를 맨 뒤로 셋팅
	m_pBrushDensityEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
	m_pBrushDensityEditCtl->SetFocus();			// 포커스를 맞춤
	m_pBrushDensityEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 브러쉬 밀도값 설정 (스핀)
void cTextureTab::OnDeltaposBrushDensitySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Up 버튼 눌렀을 경우
	if (pNMUpDown->iDelta < 0)
	{
		if (m_fBrushDensity >= 100)
		{
			return;
		}
		++m_fBrushDensity;
	}
	// Down 버튼 눌렀을 경우
	else
	{
		if (m_fBrushDensity <= 1)
		{
			return;
		}
		--m_fBrushDensity;
	}

	// 텍스쳐 밀도값 출력
	SetDlgItemInt(IDC_BRUSH_DENSITY_EDI, m_fBrushDensity);

	// 슬라이더 위치 설정
	m_pBrushDensitySliderCtl->SetPos(m_fBrushDensity);		// 위치 설정

	*pResult = 0;
}

// 브러쉬 밀도값 설정 (슬라이더)
void cTextureTab::OnCustomDrawBrushDensitySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 브러쉬 텍스쳐 넣기
	m_fBrushDensity = m_pBrushDensitySliderCtl->GetPos();

	// 브러쉬 텍스쳐 출력
	SetDlgItemInt(IDC_BRUSH_DENSITY_EDI, m_fBrushDensity);

	*pResult = 0;
}

// 걸을 수 있는 지형 설정
void cTextureTab::OnClickWalkableCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_isWalkable =  m_pWalkableCheck->GetCheck();
}
