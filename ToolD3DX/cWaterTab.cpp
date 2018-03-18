// cWaterTab.cpp: 구현 파일
//

#include "stdafx.h"
#include "cWaterTab.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// cWaterTab 대화 상자

IMPLEMENT_DYNAMIC(cWaterTab, CDialogEx)

cWaterTab::cWaterTab(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_WATER_TAB, pParent)
    // 물체크
    , m_pWaterMakeCheck(g_pMapDataManager->GetWaterMakeCheck())
    // 물높이
    , m_pWaterHeightSliderCtl(g_pMapDataManager->GetWaterHeightSliderCtl())
    , m_pWaterHeightEditCtl(g_pMapDataManager->GetWaterHeightEditCtl())
    , m_fWaterHeight(g_pMapDataManager->GetWaterHeight())
    // 물UV
    , m_pUVSpeedSliderCtl(g_pMapDataManager->GetWaterUVSpeedSliderCtl())
    , m_pUVSpeedEditCtl(g_pMapDataManager->GetWaterUVSpeedEditCtl())
    , m_fUVSpeed(g_pMapDataManager->GetWaterUVSpeed())
    // 물 파도 높이
    , m_pWaveHeightSliderCtl(g_pMapDataManager->GetWaveHeightSliderCtl())
    , m_pWaveHeightEditCtl(g_pMapDataManager->GetWaveHeightEditCtl())
    , m_fWaveHeight(g_pMapDataManager->GetWaterWaveHeight())
    // 물 파도 스피드
    , m_pHeightSpeedSliderCtl(g_pMapDataManager->GetHeightSpeedSliderCtl())
    , m_pHeightSpeedEditCtl(g_pMapDataManager->GetHeightSpeedEditCtl())
    , m_fHeightSpeed(g_pMapDataManager->GetWaterHeightSpeed())
    // 물 물결 간격
    , m_pFrequencySliderCtl(g_pMapDataManager->GetFrequencySliderCtl())
    , m_pFrequencyEditCtl(g_pMapDataManager->GetFrequencyEditCtl())
    , m_fFrequency(g_pMapDataManager->GetWaterFrequency())
    // 물 투명
    , m_pTransparentSliderCtl(g_pMapDataManager->GetTransparentSliderCtl())
    , m_pTransparentEditCtl(g_pMapDataManager->GetTransparentEditCtl())
    , m_fTransparent(g_pMapDataManager->GetWaterTransparent())
    , m_isMakeWater(g_pMapDataManager->GetIsMakeWater())
    , m_isSetWaterFile(g_pMapDataManager->GetIsSetWaterFile())
    , m_strWaterFileName(g_pMapDataManager->GetWaterFileName())
    , m_strWaterFilePath(g_pMapDataManager->GetWaterFilePath())
    , m_isSetSkyFile(g_pMapDataManager->GetIsSetSkyFile())
    , m_strSkyFileName(g_pMapDataManager->GetSkyFileName())
    , m_strSkyFilePath(g_pMapDataManager->GetSkyFilePath())
{

}

cWaterTab::~cWaterTab()
{
}

BOOL cWaterTab::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.
    m_pWaterMakeCheck = (CButton*)GetDlgItem(IDC_WATER_MAKE_CHE);
    m_pWaterMakeCheck->SetCheck(m_isMakeWater);

    // == 물 Y축 위치 설정 초기화 ==
    m_pWaterHeightSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_HEIGHT_SLI);
    m_pWaterHeightEditCtl = (CEdit*)GetDlgItem(IDC_WATER_HEIGHT_EDI);

    // 물 Y축 위치값 슬라이더 기본 설정
    m_pWaterHeightSliderCtl->SetRange(0, 256);		    // 사용영역 값 설정
    m_pWaterHeightSliderCtl->SetRangeMin(0);			// 최소 값 설정
    m_pWaterHeightSliderCtl->SetRangeMax(255);		    // 최대 값 설정
    m_pWaterHeightSliderCtl->SetPos((int)m_fWaterHeight);	// 위치 설정
    m_pWaterHeightSliderCtl->SetTicFreq(64);			// 눈금 간격 설정
    m_pWaterHeightSliderCtl->SetLineSize(16);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pWaterHeightSliderCtl->SetPageSize(64);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                                        // 물 Y축 위치값 출력
    SetDlgItemInt(IDC_WATER_HEIGHT_EDI, (UINT)m_fWaterHeight);

    // == 물 UV 스피드 설정 초기화 ==
    m_pUVSpeedSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_UV_SPEED_SLI);
    m_pUVSpeedEditCtl = (CEdit*)GetDlgItem(IDC_WATER_UV_SPEED_EDI);

    // 물 UV 스피드 슬라이더 기본 설정
    m_pUVSpeedSliderCtl->SetRange(0, 30);			// 사용영역 값 설정
    m_pUVSpeedSliderCtl->SetRangeMin(0);			// 최소 값 설정
    m_pUVSpeedSliderCtl->SetRangeMax(30);			// 최대 값 설정
    m_pUVSpeedSliderCtl->SetPos((int)(m_fUVSpeed * 100.0f));		// 위치 설정
    m_pUVSpeedSliderCtl->SetTicFreq(5);			    // 눈금 간격 설정
    m_pUVSpeedSliderCtl->SetLineSize(1);			// 증가 크기(키보드로 컨트롤 할 때)
    m_pUVSpeedSliderCtl->SetPageSize(5);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                                    // 물 UV 스피드 출력
    char str[10];
    sprintf_s(str, -1, "%0.2f", m_fUVSpeed);
    SetDlgItemTextA(IDC_WATER_UV_SPEED_EDI, str);

    // == 물 진폭 설정 초기화 ==
    m_pWaveHeightSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_WAVE_HEIGHT_SLI);
    m_pWaveHeightEditCtl = (CEdit*)GetDlgItem(IDC_WATER_WAVE_HEIGHT_EDI);

    // 물 진폭값 슬라이더 기본 설정
    m_pWaveHeightSliderCtl->SetRange(0, 100);			// 사용영역 값 설정
    m_pWaveHeightSliderCtl->SetRangeMin(0);			    // 최소 값 설정
    m_pWaveHeightSliderCtl->SetRangeMax(100);			// 최대 값 설정
    m_pWaveHeightSliderCtl->SetPos((int)(m_fWaveHeight * 10.0f));		// 위치 설정
    m_pWaveHeightSliderCtl->SetTicFreq(20);			    // 눈금 간격 설정
    m_pWaveHeightSliderCtl->SetLineSize(1);			    // 증가 크기(키보드로 컨트롤 할 때)
    m_pWaveHeightSliderCtl->SetPageSize(10);			// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                                        // 물 진폭값 출력
    sprintf_s(str, -1, "%0.1f", m_fWaveHeight);
    SetDlgItemTextA(IDC_WATER_WAVE_HEIGHT_EDI, str);

    // == 물 상하 스피드 설정 초기화 ==
    m_pHeightSpeedSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_HEIGHT_SPEED_SLI);
    m_pHeightSpeedEditCtl = (CEdit*)GetDlgItem(IDC_WATER_HEIGHT_SPEED_EDI);

    // 물 상하 스피드 슬라이더 기본 설정
    m_pHeightSpeedSliderCtl->SetRange(0, 100);			    // 사용영역 값 설정
    m_pHeightSpeedSliderCtl->SetRangeMin(0);			    // 최소 값 설정
    m_pHeightSpeedSliderCtl->SetRangeMax(100);			    // 최대 값 설정
    m_pHeightSpeedSliderCtl->SetPos((int)(m_fHeightSpeed * 10.0f));		// 위치 설정
    m_pHeightSpeedSliderCtl->SetTicFreq(20);			    // 눈금 간격 설정
    m_pHeightSpeedSliderCtl->SetLineSize(1);			    // 증가 크기(키보드로 컨트롤 할 때)
    m_pHeightSpeedSliderCtl->SetPageSize(10);			    // 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                                            // 물 상하 스피드 출력
    sprintf_s(str, -1, "%0.1f", m_fHeightSpeed);
    SetDlgItemTextA(IDC_WATER_HEIGHT_SPEED_EDI, str);

    // == 물결 간격 설정 초기화 ==
    m_pFrequencySliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_WAVE_FREQUENCY_SLI);
    m_pFrequencyEditCtl = (CEdit*)GetDlgItem(IDC_WATER_WAVE_FREQUENCY_EDI);

    // 물결 간격 슬라이더 기본 설정
    m_pFrequencySliderCtl->SetRange(0, 500);			    // 사용영역 값 설정
    m_pFrequencySliderCtl->SetRangeMin(0);			    // 최소 값 설정
    m_pFrequencySliderCtl->SetRangeMax(500);			    // 최대 값 설정
    m_pFrequencySliderCtl->SetPos((int)(m_fFrequency * 10.0f));	// 위치 설정
    m_pFrequencySliderCtl->SetTicFreq(50);			    // 눈금 간격 설정
    m_pFrequencySliderCtl->SetLineSize(5);			    // 증가 크기(키보드로 컨트롤 할 때)
    m_pFrequencySliderCtl->SetPageSize(10);			    // 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                                        // 물결 간격 스피드 출력
    sprintf_s(str, -1, "%0.1f", m_fFrequency);
    SetDlgItemTextA(IDC_WATER_WAVE_FREQUENCY_EDI, str);

    // == 물 투명값 설정 초기화 ==
    m_pTransparentSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_WATER_TRANSPARENT_SLI);
    m_pTransparentEditCtl = (CEdit*)GetDlgItem(IDC_WATER_TRANSPARENT_EDI);

    // 물 투명값 슬라이더 기본 설정
    m_pTransparentSliderCtl->SetRange(0, 10);			    // 사용영역 값 설정
    m_pTransparentSliderCtl->SetRangeMin(0);			    // 최소 값 설정
    m_pTransparentSliderCtl->SetRangeMax(10);			    // 최대 값 설정
    m_pTransparentSliderCtl->SetPos((int)(m_fTransparent * 10.0f));		// 위치 설정
    m_pTransparentSliderCtl->SetTicFreq(1);			        // 눈금 간격 설정
    m_pTransparentSliderCtl->SetLineSize(1);			    // 증가 크기(키보드로 컨트롤 할 때)
    m_pTransparentSliderCtl->SetPageSize(1);			    // 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                                            // 물 투명값 스피드 출력
    sprintf_s(str, -1, "%0.1f", m_fTransparent);
    SetDlgItemTextA(IDC_WATER_TRANSPARENT_EDI, str);

    // 체크박스 초기화 (물 안만듬)
    ((CButton*)GetDlgItem(IDC_WATER_MAKE_CHE))->SetCheck(m_isMakeWater);

    // 파일 이름 출력
    SetDlgItemText(IDC_WATER_FILE_NAME_STA, m_strWaterFileName.c_str());
    SetDlgItemText(IDC_SKY_FILE_NAME_STA, m_strSkyFileName.c_str());

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cWaterTab::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cWaterTab, CDialogEx)
    ON_EN_CHANGE(IDC_WATER_HEIGHT_EDI, &cWaterTab::OnChangeWaterHeightEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_HEIGHT_SPI, &cWaterTab::OnDeltaposWaterHeightSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_HEIGHT_SLI, &cWaterTab::OnCustomDrawWaterHeightSlider)
    ON_EN_CHANGE(IDC_WATER_UV_SPEED_EDI, &cWaterTab::OnChangeWaterUVSpeedEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_UV_SPEED_SPI, &cWaterTab::OnDeltaposWaterUVSpeedSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_UV_SPEED_SLI, &cWaterTab::OnCustomDrawWaterUVSpeedSlider)
    ON_EN_CHANGE(IDC_WATER_WAVE_HEIGHT_EDI, &cWaterTab::OnChangeWaveHeightEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_WAVE_HEIGHT_SPI, &cWaterTab::OnDeltaposWaveHeightSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_WAVE_HEIGHT_SLI, &cWaterTab::OnCustomDrawWaveHeightSlider)
    ON_EN_CHANGE(IDC_WATER_HEIGHT_SPEED_EDI, &cWaterTab::OnChangeHeightSpeedEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_HEIGHT_SPEED_SPI, &cWaterTab::OnDeltaposHeightSpeedSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_HEIGHT_SPEED_SLI, &cWaterTab::OnCustomDrawHeightSpeedSlider)
    ON_EN_CHANGE(IDC_WATER_WAVE_FREQUENCY_EDI, &cWaterTab::OnChangeFrequencyEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_WAVE_FREQUENCY_SPI, &cWaterTab::OnDeltaposFrequencySpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_WAVE_FREQUENCY_SLI, &cWaterTab::OnCustomDrawFrequencySlider)
    ON_EN_CHANGE(IDC_WATER_TRANSPARENT_EDI, &cWaterTab::OnChangeTransparentEditer)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WATER_TRANSPARENT_SPI, &cWaterTab::OnDeltaposTransparentSpin)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_WATER_TRANSPARENT_SLI, &cWaterTab::OnCustomDrawTransparentSlider)
    ON_BN_CLICKED(IDC_WATER_LOAD_BUT, &cWaterTab::OnClickedWaterFileLoadButton)
    ON_BN_CLICKED(IDC_SKY_LOAD_BUT, &cWaterTab::OnClickedSkyFileLoadButton)
    ON_BN_CLICKED(IDC_WATER_MAKE_CHE, &cWaterTab::OnClickedWaterMakeCheck)
END_MESSAGE_MAP()


// cWaterTab 메시지 처리기

// == 물 Y축 값 ==================================================================================================
// 물 Y축 값 설정 (에디터)
void cWaterTab::OnChangeWaterHeightEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    m_fWaterHeight = (float)GetDlgItemInt(IDC_WATER_HEIGHT_EDI);

    // 슬라이더 위치 설정
    m_pWaterHeightSliderCtl->SetPos((int)m_fWaterHeight);		// 위치 설정

                                                                // 커서를 맨 뒤로 셋팅
    m_pWaterHeightEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
    m_pWaterHeightEditCtl->SetFocus();		// 포커스를 맞춤
    m_pWaterHeightEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 물 Y축 값 설정 (스핀)
void cWaterTab::OnDeltaposWaterHeightSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fWaterHeight >= 255)
        {
            return;
        }
        ++m_fWaterHeight;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fWaterHeight <= 0)
        {
            return;
        }
        --m_fWaterHeight;
    }

    // 물 Y축 위치값 출력
    SetDlgItemInt(IDC_WATER_HEIGHT_EDI, (int)m_fWaterHeight);

    // 슬라이더 위치 설정
    m_pWaterHeightSliderCtl->SetPos((int)m_fWaterHeight);		// 위치 설정

    *pResult = 0;
}

// 물 Y축 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawWaterHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 물 Y축 값 넣기
    m_fWaterHeight = (float)m_pWaterHeightSliderCtl->GetPos();

    // 물 Y축 값 출력
    SetDlgItemInt(IDC_WATER_HEIGHT_EDI, (int)m_fWaterHeight);

    *pResult = 0;
}

// == 물 유속 값 ==================================================================================================
// 물 유속 값 설정 (에디터)
void cWaterTab::OnChangeWaterUVSpeedEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    CString str = "";
    GetDlgItemText(IDC_WATER_UV_SPEED_EDI, str);
    m_fUVSpeed = (float)atof(str);

    // 슬라이더 위치 설정
    m_pUVSpeedSliderCtl->SetPos((int)(m_fUVSpeed * 100.0f));    // 위치 설정

                                                                // 커서를 맨 뒤로 셋팅
    m_pUVSpeedEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
    m_pUVSpeedEditCtl->SetFocus();		// 포커스를 맞춤
    m_pUVSpeedEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 물 유속 값 설정 (스핀)
void cWaterTab::OnDeltaposWaterUVSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fUVSpeed >= 30)
        {
            return;
        }
        m_fUVSpeed += 0.01f;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fUVSpeed <= 0)
        {
            return;
        }
        m_fUVSpeed -= 0.01f;
    }

    // 물 유속값 출력
    char str[10];
    sprintf_s(str, -1, "%0.2f", m_fUVSpeed);
    SetDlgItemTextA(IDC_WATER_UV_SPEED_EDI, str);

    // 슬라이더 위치 설정
    m_pUVSpeedSliderCtl->SetPos((int)(m_fUVSpeed * 100.0f));        // 위치 설정

    *pResult = 0;
}

// 물 유속 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawWaterUVSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 물 유속값 넣기
    m_fUVSpeed = m_pUVSpeedSliderCtl->GetPos() * 0.01f;

    // 물 유속값 출력
    char str[10];
    sprintf_s(str, -1, "%0.2f", m_fUVSpeed);
    SetDlgItemTextA(IDC_WATER_UV_SPEED_EDI, str);

    *pResult = 0;
}

// == 물 진폭 값 ==================================================================================================
// 물 진폭 값 설정 (에디터)
void cWaterTab::OnChangeWaveHeightEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    CString str = "";
    GetDlgItemText(IDC_WATER_WAVE_HEIGHT_EDI, str);
    m_fWaveHeight = (float)atof(str);

    // 슬라이더 위치 설정
    m_pWaveHeightSliderCtl->SetPos((int)(m_fWaveHeight * 10.0f));       // 위치 설정

                                                                        // 커서를 맨 뒤로 셋팅
    m_pWaveHeightEditCtl->SetSel(0, -1);        // 모든 영역을 드레그
    m_pWaveHeightEditCtl->SetFocus();           // 포커스를 맞춤
    m_pWaveHeightEditCtl->SetSel(-1, -1);       // 커서를 맨 뒤로 보냄
}

// 물 진폭 값 설정 (스핀)
void cWaterTab::OnDeltaposWaveHeightSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fWaveHeight >= 100)
        {
            return;
        }
        m_fWaveHeight += 0.1f;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fWaveHeight <= 0)
        {
            return;
        }
        m_fWaveHeight -= 0.1f;
    }

    // 물 진폭값 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fWaveHeight);
    SetDlgItemTextA(IDC_WATER_WAVE_HEIGHT_EDI, str);

    // 슬라이더 위치 설정
    m_pWaveHeightSliderCtl->SetPos((int)(m_fWaveHeight * 10.0f));       // 위치 설정

    *pResult = 0;
}

// 물 진폭 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawWaveHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 물 진폭값 넣기
    m_fWaveHeight = m_pWaveHeightSliderCtl->GetPos() * 0.1f;

    // 물 진폭값 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fWaveHeight);
    SetDlgItemTextA(IDC_WATER_WAVE_HEIGHT_EDI, str);

    *pResult = 0;
}

// == 물 상하 스피드 값 ==================================================================================================
// 물 상하 스피드 값 설정 (에디터)
void cWaterTab::OnChangeHeightSpeedEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    CString str = "";
    GetDlgItemText(IDC_WATER_HEIGHT_SPEED_EDI, str);
    m_fHeightSpeed = (float)atof(str);

    // 슬라이더 위치 설정
    m_pWaveHeightSliderCtl->SetPos((int)(m_fWaveHeight * 10.0f));		// 위치 설정

                                                                        // 커서를 맨 뒤로 셋팅
    m_pHeightSpeedEditCtl->SetSel(0, -1);	// 모든 영역을 드레그
    m_pHeightSpeedEditCtl->SetFocus();		// 포커스를 맞춤
    m_pHeightSpeedEditCtl->SetSel(-1, -1);	// 커서를 맨 뒤로 보냄
}

// 물 상하 스피드 값 설정 (스핀)
void cWaterTab::OnDeltaposHeightSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fHeightSpeed >= 100)
        {
            return;
        }
        m_fHeightSpeed += 0.1f;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fHeightSpeed <= 0)
        {
            return;
        }
        m_fHeightSpeed -= 0.1f;
    }

    // 물 상하 스피드값 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fHeightSpeed);
    SetDlgItemTextA(IDC_WATER_HEIGHT_SPEED_EDI, str);

    // 슬라이더 위치 설정
    m_pHeightSpeedSliderCtl->SetPos((int)(m_fHeightSpeed * 10.0f));		// 위치 설정

    *pResult = 0;
}

// 물 상하 스피드 설정 (슬라이더)
void cWaterTab::OnCustomDrawHeightSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 물 상하 스피드 넣기
    m_fHeightSpeed = m_pHeightSpeedSliderCtl->GetPos() * 0.1f;

    // 물 상하 스피드 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fHeightSpeed);
    SetDlgItemTextA(IDC_WATER_HEIGHT_SPEED_EDI, str);

    *pResult = 0;
}

// == 물결 간격 값 ==================================================================================================
// 물결 간격 값 설정 (에디터)
void cWaterTab::OnChangeFrequencyEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    /*  CString str = "";
    GetDlgItemText(IDC_WATER_WAVE_FREQUENCY_EDI, str);
    m_fFrequency = (float)atof(str);
    m_fFrequency = atof(str);*/

    // 슬라이더 위치 설정
    m_pFrequencySliderCtl->SetPos((int)(m_fFrequency * 10.0f));     // 위치 설정
                                                                    // 커서를 맨 뒤로 셋팅
    m_pFrequencyEditCtl->SetSel(0, -1);	    // 모든 영역을 드레그
    m_pFrequencyEditCtl->SetFocus();        // 포커스를 맞춤
    m_pFrequencyEditCtl->SetSel(-1, -1);    // 커서를 맨 뒤로 보냄
}

// 물결 간격 값 설정 (스핀)
void cWaterTab::OnDeltaposFrequencySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fFrequency >= 500)
        {
            return;
        }
        m_fFrequency += 0.5f;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fFrequency <= 0)
        {
            return;
        }
        m_fFrequency -= 0.5f;
    }

    // 물결 간격 값 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fFrequency);
    SetDlgItemTextA(IDC_WATER_WAVE_FREQUENCY_EDI, str);

    // 슬라이더 위치 설정
    m_pFrequencySliderCtl->SetPos((int)(m_fFrequency * 10.0f));		// 위치 설정

    *pResult = 0;
}

// 물결 간격 값 설정 (슬라이더)
void cWaterTab::OnCustomDrawFrequencySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 물결 간격 넣기
    m_fFrequency = m_pFrequencySliderCtl->GetPos() * 0.1f;

    // 물결 간격 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fFrequency);
    SetDlgItemTextA(IDC_WATER_WAVE_FREQUENCY_EDI, str);

    *pResult = 0;
}

// == 물 투명값 ==================================================================================================
// 물 투명값 설정 (에디터)
void cWaterTab::OnChangeTransparentEditer()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 에디터에 입력 된 값  가져오기
    CString str = "";
    GetDlgItemText(IDC_WATER_TRANSPARENT_EDI, str);
    m_fTransparent = (float)atof(str);

    // 슬라이더 위치 설정
    m_pTransparentSliderCtl->SetPos((int)(m_fTransparent * 10.0f));		// 위치 설정

                                                                        // 커서를 맨 뒤로 셋팅
    m_pTransparentEditCtl->SetSel(0, -1);	    // 모든 영역을 드레그
    m_pTransparentEditCtl->SetFocus();		    // 포커스를 맞춤
    m_pTransparentEditCtl->SetSel(-1, -1);	    // 커서를 맨 뒤로 보냄
}

// 물 투명값 설정 (스핀)
void cWaterTab::OnDeltaposTransparentSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // Up 버튼 눌렀을 경우
    if (pNMUpDown->iDelta < 0)
    {
        if (m_fTransparent >= 10)
        {
            return;
        }
        m_fTransparent += 0.1f;
    }
    // Down 버튼 눌렀을 경우
    else
    {
        if (m_fTransparent <= 0)
        {
            return;
        }
        m_fTransparent -= 0.1f;
    }

    // 물 투명값 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fTransparent);
    SetDlgItemTextA(IDC_WATER_TRANSPARENT_EDI, str);

    // 슬라이더 위치 설정
    m_pTransparentSliderCtl->SetPos((int)(m_fTransparent * 10.0f));		// 위치 설정

    *pResult = 0;
}

// 물 투명값 설정 (슬라이더)
void cWaterTab::OnCustomDrawTransparentSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 물 투명값 넣기
    m_fTransparent = m_pTransparentSliderCtl->GetPos() * 0.1f;

    // 물 투명값 출력
    char str[10];
    sprintf_s(str, -1, "%0.1f", m_fTransparent);
    SetDlgItemTextA(IDC_WATER_TRANSPARENT_EDI, str);

    *pResult = 0;
}

// 물 파일 로드 버튼
void cWaterTab::OnClickedWaterFileLoadButton()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "Image (*.jpg, *.bmp, *png) |*.JPG; *.BMP; *.PNG |";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    string caption = "Image 파일 불러오기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();
        m_strWaterFilePath = FileDialog.GetFolderPath().GetString();
        m_strWaterFileName = FileDialog.GetFileName().GetString();
        m_isSetWaterFile = true;
        // 파일 이름을 표시해줌
    }
    else
    {
        m_strWaterFileName = "NONE";
        MessageBox("파일 읽기 실패", caption.c_str(), MB_ICONERROR);
    }
    SetDlgItemText(IDC_WATER_FILE_NAME_STA, m_strWaterFileName.c_str());
}

// 하늘 파일 로드 버튼
void cWaterTab::OnClickedSkyFileLoadButton()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "DDS Files (*.dds) |*.DDS|";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    string caption = "DDS 파일 불러오기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();

        // 확장자가 jpg인지 체크 
        if (check == "DDS" || check == "dds")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> 확장자를 제외한 파일 이름을 불러옴
            m_strSkyFilePath = FileDialog.GetFolderPath().GetString();
            m_strSkyFileName = FileDialog.GetFileName().GetString();

            m_isSetSkyFile = true;

            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_SKY_FILE_NAME_STA, m_strSkyFileName.c_str());
        }
        else
        {
            m_strSkyFileName = "NONE";
            MessageBox("파일 읽기 실패", caption.c_str(), MB_ICONERROR);
            // 파일 이름을 표시해줌
            SetDlgItemText(IDC_SKY_FILE_NAME_STA, m_strSkyFileName.c_str());
        }
    }
}

// 물 생성 여부
void cWaterTab::OnClickedWaterMakeCheck()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 체크박스 값 받아오기
    m_isMakeWater = ((CButton*)GetDlgItem(IDC_WATER_MAKE_CHE))->GetCheck();
}

void cWaterTab::Update()
{
    CString tex1;
    GetDlgItemText(IDC_WATER_FILE_NAME_STA, tex1);
    if (tex1.GetString() != m_strWaterFileName)
    {
        SetDlgItemText(IDC_WATER_FILE_NAME_STA, m_strWaterFileName.c_str());
    }

    CString tex2;
    GetDlgItemText(IDC_SKY_FILE_NAME_STA, tex2);
    if (tex2.GetString() != m_strSkyFileName)
    {
        SetDlgItemText(IDC_SKY_FILE_NAME_STA, m_strSkyFileName.c_str());
    }
}
