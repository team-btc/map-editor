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
    , m_pTex1DensitySliderCtl(NULL)
    , m_pTex1DensityEditCtl(NULL)
    , m_pTex2DensitySliderCtl(NULL)
    , m_pTex2DensityEditCtl(NULL)
    , m_pTex3DensitySliderCtl(NULL)
    , m_pTex3DensityEditCtl(NULL)
    , m_isTex1Load(g_pMapDataManager->GetIsTex1Load())
    , m_isTex2Load(g_pMapDataManager->GetIsTex2Load())
    , m_isTex3Load(g_pMapDataManager->GetIsTex3Load())
    , m_strTex1FileName(g_pMapDataManager->GetTex1FileName())
    , m_strTex1FilePath(g_pMapDataManager->GetTex1FilePath())
    , m_strTex2FileName(g_pMapDataManager->GetTex2FileName())
    , m_strTex2FilePath(g_pMapDataManager->GetTex2FilePath())
    , m_strTex3FileName(g_pMapDataManager->GetTex3FileName())
    , m_strTex3FilePath(g_pMapDataManager->GetTex3FilePath())
    , m_fTex1Density(g_pMapDataManager->GetTex1Density())
    , m_fTex2Density(g_pMapDataManager->GetTex2Density())
    , m_fTex3Density(g_pMapDataManager->GetTex3Density())
    , m_nTextureIndex(g_pMapDataManager->GetCurrTexIndex())
    , m_eDrawType(g_pMapDataManager->GetDrawType())
    , m_fTextureDensity(g_pMapDataManager->GetDrawDensity())
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

    // == 파일 이름 출력 ==
    SetDlgItemText(IDC_TEX1_FILE_NAME_STA, m_strTex1FileName.c_str());
    SetDlgItemText(IDC_TEX2_FILE_NAME_STA, m_strTex2FileName.c_str());
    SetDlgItemText(IDC_TEX3_FILE_NAME_STA, m_strTex3FileName.c_str());

	// == 텍스쳐 밀도값 설정 초기화 ==
	m_pTextureDensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_TEXTURE_DENSITY_SLI);
	m_pTextureDensityEditCtl = (CEdit*)GetDlgItem(IDC_TEXTURE_DENSITY_EDI);

	// 텍스쳐 밀도값 슬라이더 기본 설정
	m_pTextureDensitySliderCtl->SetRange(1, 100);		// 사용영역 값 설정
	m_pTextureDensitySliderCtl->SetRangeMin(10);		// 최소 값 설정
	m_pTextureDensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
	m_pTextureDensitySliderCtl->SetPos((int)m_fTextureDensity);	// 위치 설정
	m_pTextureDensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pTextureDensitySliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pTextureDensitySliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 텍스쳐 밀도값 출력
	SetDlgItemInt(IDC_TEXTURE_DENSITY_EDI, (UINT)m_fTextureDensity);

	// == 브러쉬 사이즈 설정 초기화 ==
	m_pBrushSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_SIZE_SLI);
	m_pBrushSizeEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_SIZE_EDI);

	// 브러쉬 사이즈 슬라이더 기본 설정
	m_pBrushSizeSliderCtl->SetRange(1, 100);		// 사용영역 값 설정
	m_pBrushSizeSliderCtl->SetRangeMin(1);		// 최소 값 설정
	m_pBrushSizeSliderCtl->SetRangeMax(100);		// 최대 값 설정
	m_pBrushSizeSliderCtl->SetPos((int)m_fBrushSize);	// 위치 설정
	m_pBrushSizeSliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pBrushSizeSliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pBrushSizeSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, (UINT)m_fBrushSize);
	
    // == 브러쉬 밀도 사이즈 설정 초기화 ==
    m_pBrushDenSizeSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_DENSITY_SIZE_SLI);
    m_pBrushDenSizeEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_DENSITY_SIZE_EDI);

    // 브러쉬 사이즈 슬라이더 기본 설정
    m_pBrushDenSizeSliderCtl->SetRange(0, 100);		// 사용영역 값 설정
    m_pBrushDenSizeSliderCtl->SetRangeMin(2);		// 최소 값 설정
    m_pBrushDenSizeSliderCtl->SetRangeMax(100);		// 최대 값 설정
    m_pBrushDenSizeSliderCtl->SetPos((int)m_fBrushDenSize);	// 위치 설정
    m_pBrushDenSizeSliderCtl->SetTicFreq(10);			// 눈금 간격 설정
    m_pBrushDenSizeSliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pBrushDenSizeSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

    // 브러쉬 사이즈 출력
    SetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI, (UINT)m_fBrushDenSize);

	// == 브러쉬 밀도값 설정 초기화 ==
	m_pBrushDensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_BRUSH_DENSITY_SLI);
	m_pBrushDensityEditCtl = (CEdit*)GetDlgItem(IDC_BRUSH_DENSITY_EDI);

	// 브러쉬 밀도값 슬라이더 기본 설정
	m_pBrushDensitySliderCtl->SetRange(0, 100);		// 사용영역 값 설정
	m_pBrushDensitySliderCtl->SetRangeMin(10);		// 최소 값 설정
	m_pBrushDensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
	m_pBrushDensitySliderCtl->SetPos((int)m_fBrushDensity);	// 위치 설정
	m_pBrushDensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
	m_pBrushDensitySliderCtl->SetLineSize(5);			// 증가 크기(키보드로 컨트롤 할 때)
	m_pBrushDensitySliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

	// 브러쉬 밀도값 출력
	SetDlgItemInt(IDC_BRUSH_DENSITY_EDI, (UINT)m_fBrushDensity);

    // == 텍스쳐 1 밀도 설정 초기화 ==
    m_pTex1DensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_TEX1_DSIZE_SLI);
    m_pTex1DensityEditCtl = (CEdit*)GetDlgItem(IDC_TEX1_DSIZE_EDI);

    // 텍스쳐 1 밀도 슬라이더 기본 설정
    m_pTex1DensitySliderCtl->SetRange(1, 100);		// 사용영역 값 설정
    m_pTex1DensitySliderCtl->SetRangeMin(1);		// 최소 값 설정
    m_pTex1DensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
    m_pTex1DensitySliderCtl->SetPos((int)m_fTex1Density);	// 위치 설정
    m_pTex1DensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
    m_pTex1DensitySliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pTex1DensitySliderCtl->SetPageSize(5);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

    // 텍스쳐 1 사이즈 출력
    SetDlgItemInt(IDC_TEX1_DSIZE_EDI, (UINT)m_fTex1Density);

    // == 텍스쳐 2 밀도 설정 초기화 ==
    m_pTex2DensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_TEX2_DSIZE_SLI);
    m_pTex2DensityEditCtl = (CEdit*)GetDlgItem(IDC_TEX2_DSIZE_EDI);

    // 텍스쳐 2 밀도 슬라이더 기본 설정
    m_pTex2DensitySliderCtl->SetRange(1, 100);		// 사용영역 값 설정
    m_pTex2DensitySliderCtl->SetRangeMin(1);		// 최소 값 설정
    m_pTex2DensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
    m_pTex2DensitySliderCtl->SetPos((int)m_fTex2Density);	// 위치 설정
    m_pTex2DensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
    m_pTex2DensitySliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pTex2DensitySliderCtl->SetPageSize(5);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

    // 텍스쳐 2 사이즈 출력
    SetDlgItemInt(IDC_TEX2_DSIZE_EDI, (UINT)m_fTex2Density);

    // == 텍스쳐 3 밀도 설정 초기화 ==
    m_pTex3DensitySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_TEX3_DSIZE_SLI);
    m_pTex3DensityEditCtl = (CEdit*)GetDlgItem(IDC_TEX3_DSIZE_EDI);

    // 텍스쳐 3 밀도 슬라이더 기본 설정
    m_pTex3DensitySliderCtl->SetRange(1, 100);		// 사용영역 값 설정
    m_pTex3DensitySliderCtl->SetRangeMin(1);		// 최소 값 설정
    m_pTex3DensitySliderCtl->SetRangeMax(100);		// 최대 값 설정
    m_pTex3DensitySliderCtl->SetPos((int)m_fTex3Density);	// 위치 설정
    m_pTex3DensitySliderCtl->SetTicFreq(10);			// 눈금 간격 설정
    m_pTex3DensitySliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pTex3DensitySliderCtl->SetPageSize(5);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

    // 텍스쳐 3 사이즈 출력
    SetDlgItemInt(IDC_TEX3_DSIZE_EDI, (UINT)m_fTex3Density);

	// == 걸을 수 있는지형 체크박스 초기화 ==
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cTextureTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// == 텍스쳐 선택 라디오 버튼 초기화 및 연결 ==
	DDX_Radio(pDX, ID_TERRAIN1_RAD, (int&)m_nTextureIndex); // 텍스쳐1번으로 라디오박스 설정

    // == 텍스쳐 선택 라디오 버튼 초기화 및 연결 ==
    DDX_Radio(pDX, IDC_BRUSH_RAD, (int&)m_eDrawType); // BRUSH로 그리기 설정
}

BEGIN_MESSAGE_MAP(cTextureTab, CDialogEx)
    ON_CONTROL_RANGE(BN_CLICKED, ID_TERRAIN1_RAD, ID_TERRAIN3_RAD, &cTextureTab::OnSelectTextureRadio)
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
    ON_CONTROL_RANGE(BN_CLICKED, IDC_BRUSH_RAD, IDC_ERASE_RAD, &cTextureTab::OnSelectDrawModeRadio)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_TEX1_DSIZE_SLI, &cTextureTab::OnNMCustomdrawTex1DsizeSli)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_TEX2_DSIZE_SLI, &cTextureTab::OnNMCustomdrawTex2DsizeSli)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_TEX3_DSIZE_SLI, &cTextureTab::OnNMCustomdrawTex3DsizeSli)
    ON_EN_CHANGE(IDC_TEX1_DSIZE_EDI, &cTextureTab::OnEnChangeTex1DsizeEdi)
    ON_EN_CHANGE(IDC_TEX2_DSIZE_EDI, &cTextureTab::OnEnChangeTex2DsizeEdi)
    ON_EN_CHANGE(IDC_TEX3_DSIZE_EDI, &cTextureTab::OnEnChangeTex3DsizeEdi)
    ON_NOTIFY(UDN_DELTAPOS, IDC_Tex1_DSIZE_SPI, &cTextureTab::OnDeltaposTex1DsizeSpi)
    ON_NOTIFY(UDN_DELTAPOS, IDC_TEX2_DSIZE_SPI, &cTextureTab::OnDeltaposTex2DsizeSpi)
    ON_NOTIFY(UDN_DELTAPOS, IDIDC_TEX3_DSIZE_SPI, &cTextureTab::OnDeltaposTex3DsizeSpi)
    ON_BN_CLICKED(IDC_TEX1_LOAD_BUT, &cTextureTab::OnClickedTex1LoadButton)
    ON_BN_CLICKED(IDC_TEX2_LOAD_BUT, &cTextureTab::OnClickedTex2LoadButton)
    ON_BN_CLICKED(IDC_TEX3_LOAD_BUT, &cTextureTab::OnClickedTex3LoadButton)
END_MESSAGE_MAP()


// cTextureTab 메시지 처리기

// 텍스쳐 선택
void cTextureTab::OnSelectTextureRadio(UINT ID)
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
	m_fTextureDensity = (float)GetDlgItemInt(IDC_TEXTURE_DENSITY_EDI);

	// 슬라이더 위치 설정
	m_pTextureDensitySliderCtl->SetPos((int)m_fTextureDensity);		// 위치 설정

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
	SetDlgItemInt(IDC_TEXTURE_DENSITY_EDI, (UINT)m_fTextureDensity);

	// 슬라이더 위치 설정
	m_pTextureDensitySliderCtl->SetPos((int)m_fTextureDensity);		// 위치 설정

	*pResult = 0;
}

// 텍스쳐 밀도값 설정 (슬라이더)
void cTextureTab::OnCustomDrawTextureDensitySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 텍스쳐 밀도값 넣기
	m_fTextureDensity = (float)m_pTextureDensitySliderCtl->GetPos();

	// 텍스쳐 밀도값 출력
	SetDlgItemInt(IDC_TEXTURE_DENSITY_EDI, (UINT)m_fTextureDensity);

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
	m_fBrushSize = (float)GetDlgItemInt(IDC_BRUSH_SIZE_EDI);

	// 슬라이더 위치 설정
	m_pBrushSizeSliderCtl->SetPos((int)m_fBrushSize);		// 위치 설정

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
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, (UINT)m_fBrushSize);

	// 슬라이더 위치 설정
	m_pBrushSizeSliderCtl->SetPos((int)m_fBrushSize);		// 위치 설정

	*pResult = 0;
}

// 브러쉬 사이즈 설정 (슬라이더)
void cTextureTab::OnCustomDrawBrushSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 브러쉬 사이즈 넣기
	m_fBrushSize = (float)m_pBrushSizeSliderCtl->GetPos();

	// 브러쉬 사이즈 출력
	SetDlgItemInt(IDC_BRUSH_SIZE_EDI, (UINT)m_fBrushSize);

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
    m_fBrushDenSize = (float)GetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI);

    // 슬라이더 위치 설정
    m_pBrushDenSizeSliderCtl->SetPos((int)m_fBrushDenSize);		// 위치 설정

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
    SetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI, (UINT)m_fBrushDenSize);

    // 슬라이더 위치 설정
    m_pBrushDenSizeSliderCtl->SetPos((int)m_fBrushDenSize);		// 위치 설정

    *pResult = 0;
}

// 브러쉬 밀도 사이즈 설정 (슬라이더)
void cTextureTab::OnCustomDrawBrushDenSizeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 브러쉬 밀도 사이즈 넣기
    m_fBrushDenSize = (float)m_pBrushDenSizeSliderCtl->GetPos();

    // 브러쉬 밀도 사이즈 출력
    SetDlgItemInt(IDC_BRUSH_DENSITY_SIZE_EDI, (UINT)m_fBrushDenSize);

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
	m_fBrushDensity = (float)GetDlgItemInt(IDC_BRUSH_DENSITY_EDI);

	// 슬라이더 위치 설정
	m_pBrushDensitySliderCtl->SetPos((int)m_fBrushDensity);		// 위치 설정

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
	SetDlgItemInt(IDC_BRUSH_DENSITY_EDI, (UINT)m_fBrushDensity);

	// 슬라이더 위치 설정
	m_pBrushDensitySliderCtl->SetPos((int)m_fBrushDensity);		// 위치 설정

	*pResult = 0;
}

// 브러쉬 밀도값 설정 (슬라이더)
void cTextureTab::OnCustomDrawBrushDensitySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 브러쉬 텍스쳐 넣기
	m_fBrushDensity = (float)m_pBrushDensitySliderCtl->GetPos();

	// 브러쉬 텍스쳐 출력
	SetDlgItemInt(IDC_BRUSH_DENSITY_EDI, (UINT)m_fBrushDensity);

	*pResult = 0;
}

// 드로우 모드
void cTextureTab::OnSelectDrawModeRadio(UINT ID)
{
    UpdateData();
}
// 텍스쳐 1 슬라이더
void cTextureTab::OnNMCustomdrawTex1DsizeSli(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    m_fTex1Density = (float)m_pTex1DensitySliderCtl->GetPos();

    SetDlgItemInt(IDC_TEX1_DSIZE_EDI, (UINT)m_fTex1Density);

    *pResult = 0;
}

// 텍스쳐 2 슬라이더
void cTextureTab::OnNMCustomdrawTex2DsizeSli(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    m_fTex2Density = (float)m_pTex2DensitySliderCtl->GetPos();

    SetDlgItemInt(IDC_TEX2_DSIZE_EDI, (UINT)m_fTex2Density);

    *pResult = 0;
}

// 텍스쳐 3 슬라이더
void cTextureTab::OnNMCustomdrawTex3DsizeSli(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    m_fTex3Density = (float)m_pTex3DensitySliderCtl->GetPos();

    SetDlgItemInt(IDC_TEX3_DSIZE_EDI, (UINT)m_fTex3Density);

    *pResult = 0;
}

// 텍스쳐 1 에디터
void cTextureTab::OnEnChangeTex1DsizeEdi()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    m_fTex1Density = (float)GetDlgItemInt(IDC_TEX1_DSIZE_EDI);

    // 슬라이더 위치 설정
    m_pTex1DensitySliderCtl->SetPos((int)m_fTex1Density);		// 위치 설정
       
    m_pTex1DensityEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
    m_pTex1DensityEditCtl->SetFocus();			// 포커스를 맞춤
    m_pTex1DensityEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 텍스쳐 2 에디터
void cTextureTab::OnEnChangeTex2DsizeEdi()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    m_fTex2Density = (float)GetDlgItemInt(IDC_TEX2_DSIZE_EDI);

    // 슬라이더 위치 설정
    m_pTex2DensitySliderCtl->SetPos((int)m_fTex2Density);		// 위치 설정

    m_pTex2DensityEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
    m_pTex2DensityEditCtl->SetFocus();			// 포커스를 맞춤
    m_pTex2DensityEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄
}

// 텍스쳐 3 에디터
void cTextureTab::OnEnChangeTex3DsizeEdi()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // 에디터에 입력 된 값  가져오기
    m_fTex3Density = (float)GetDlgItemInt(IDC_TEX3_DSIZE_EDI);

    // 슬라이더 위치 설정
    m_pTex3DensitySliderCtl->SetPos((int)m_fTex3Density);		// 위치 설정

    m_pTex3DensityEditCtl->SetSel(0, -1);		// 모든 영역을 드레그
    m_pTex3DensityEditCtl->SetFocus();			// 포커스를 맞춤
    m_pTex3DensityEditCtl->SetSel(-1, -1);		// 커서를 맨 뒤로 보냄

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

// 텍스쳐 1 스핀
void cTextureTab::OnDeltaposTex1DsizeSpi(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fTex1Density >= 100)
        {
            return;
        }
        ++m_fTex1Density;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fTex1Density <= 1)
        {
            return;
        }
        --m_fTex1Density;
    }

    // 텍스쳐 밀도값 출력
    SetDlgItemInt(IDC_TEX1_DSIZE_EDI, (UINT)m_fTex1Density);

    // 슬라이더 위치 설정
    m_pTex1DensitySliderCtl->SetPos((int)m_fTex1Density);		// 위치 설정

    *pResult = 0;
}

// 텍스쳐 2 스핀
void cTextureTab::OnDeltaposTex2DsizeSpi(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fTex2Density >= 100)
        {
            return;
        }
        ++m_fTex2Density;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fTex2Density <= 1)
        {
            return;
        }
        --m_fTex2Density;
    }

    // 텍스쳐 밀도값 출력
    SetDlgItemInt(IDC_TEX2_DSIZE_EDI, (UINT)m_fTex2Density);

    // 슬라이더 위치 설정
    m_pTex2DensitySliderCtl->SetPos((int)m_fTex2Density);		// 위치 설정

    *pResult = 0;
}

// 텍스쳐 3 스핀
void cTextureTab::OnDeltaposTex3DsizeSpi(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fTex3Density >= 100)
        {
            return;
        }
        ++m_fTex3Density;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fTex3Density <= 1)
        {
            return;
        }
        --m_fTex3Density;
    }

    // 텍스쳐 밀도값 출력
    SetDlgItemInt(IDC_TEX3_DSIZE_EDI, (UINT)m_fTex3Density);

    // 슬라이더 위치 설정
    m_pTex3DensitySliderCtl->SetPos((int)m_fTex3Density);		// 위치 설정

    *pResult = 0;
}

void cTextureTab::OnClickedTex1LoadButton()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "JPG Files (*.jpg) |*.JPG|";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    string caption = "JPG 파일 불러오기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();

        // 확장자가 jpg인지 체크 
        if (check == "JPG" || check == "jpg")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> 확장자를 제외한 파일 이름을 불러옴
            m_strTex1FilePath = FileDialog.GetFolderPath().GetString();
            m_strTex1FileName = FileDialog.GetFileName().GetString();

            m_isTex1Load = true;

            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_TEX1_FILE_NAME_STA, m_strTex1FileName.c_str());
        }
        else
        {
            m_strTex1FileName = "NONE";
            MessageBox("파일 읽기 실패", caption.c_str(), MB_ICONERROR);
            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_TEX1_FILE_NAME_STA, m_strTex1FileName.c_str());
        }
    }
}

// 기본 텍스쳐 2 파일 오픈
void cTextureTab::OnClickedTex2LoadButton()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "JPG Files (*.jpg) |*.JPG|";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    string caption = "JPG 파일 불러오기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();

        // 확장자가 jpg인지 체크 
        if (check == "JPG" || check == "jpg")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> 확장자를 제외한 파일 이름을 불러옴
            m_strTex2FilePath = FileDialog.GetFolderPath().GetString();
            m_strTex2FileName = FileDialog.GetFileName().GetString();

            m_isTex2Load = true;

            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_TEX2_FILE_NAME_STA, m_strTex2FileName.c_str());
        }
        else
        {
            m_strTex2FileName = "NONE";
            MessageBox("파일 읽기 실패", caption.c_str(), MB_ICONERROR);
            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_TEX2_FILE_NAME_STA, m_strTex2FileName.c_str());
        }
    }
}


// 기본 텍스쳐 3 파일 오픈
void cTextureTab::OnClickedTex3LoadButton()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "JPG Files (*.jpg) |*.JPG|";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    string caption = "JPG 파일 불러오기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();

        // 확장자가 jpg인지 체크 
        if (check == "JPG" || check == "jpg")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> 확장자를 제외한 파일 이름을 불러옴
            m_strTex3FilePath = FileDialog.GetFolderPath().GetString();
            m_strTex3FileName = FileDialog.GetFileName().GetString();

            m_isTex3Load = true;

            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_TEX3_FILE_NAME_STA, m_strTex3FileName.c_str());
        }
        else
        {
            m_strTex3FileName = "NONE";
            MessageBox("파일 읽기 실패", caption.c_str(), MB_ICONERROR);
            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_TEX3_FILE_NAME_STA, m_strTex3FileName.c_str());
        }
    }
}

void cTextureTab::Update()
{
    m_fTex1Density = g_pMapDataManager->GetTex1Density();
}
