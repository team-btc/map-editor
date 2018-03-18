// cCreateMapDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "cCreateMapDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

// cCreateMapDlg 대화 상자
//  encode
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(cCreateMapDlg, CDialogEx)

cCreateMapDlg::cCreateMapDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CREATEMAP_VIEW, pParent)
    , m_pComboController(NULL)
    , m_pSliderController(NULL)
    , m_pEditController(NULL)
    , m_eMapSize(g_pMapDataManager->GetMapSize())
    , m_fDefaultHeight(g_pMapDataManager->GetDefHeight())
    , m_isCreateMap(g_pMapDataManager->GetCreateMap())
    , m_isTex1Load(g_pMapDataManager->GetIsTex1Load())
    , m_isTex2Load(g_pMapDataManager->GetIsTex2Load())
    , m_isTex3Load(g_pMapDataManager->GetIsTex3Load())
    , m_strTex1FileName(g_pMapDataManager->GetTex1FileName())
    , m_strTex1FilePath(g_pMapDataManager->GetTex1FilePath())
    , m_strTex2FileName(g_pMapDataManager->GetTex2FileName())
    , m_strTex2FilePath(g_pMapDataManager->GetTex2FilePath())
    , m_strTex3FileName(g_pMapDataManager->GetTex3FileName())
    , m_strTex3FilePath(g_pMapDataManager->GetTex3FilePath())
{
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
    // == 파일 이름 출력 ==
    SetDlgItemText(IDC_TEX1_FILE_NAME_STA, m_strTex1FileName.c_str());
    SetDlgItemText(IDC_TEX2_FILE_NAME_STA, m_strTex2FileName.c_str());
    SetDlgItemText(IDC_TEX3_FILE_NAME_STA, m_strTex3FileName.c_str());

    // 콤보박스에 텍스트 추가
    for (int i = 0; i < E_MAP_SIZE_MAX; ++i)
    {
        int nValue = (i + 1) * 64;
        //char str[20];
        //sprintf(str, "%d * %d", nValue, nValue);
        string str = to_string(nValue) + " * " + to_string(nValue);
        m_pComboController->AddString(str.c_str());
    }

    // 맵 사이즈 선택
    m_pComboController->SetCurSel(m_eMapSize);

    // 슬라이더 기본 설정
    m_pSliderController->SetRange(0, 256);	// 사용영역 값 설정
    m_pSliderController->SetRangeMin(0);	// 최소 값 설정
    m_pSliderController->SetRangeMax(255);	// 최대 값 설정
    m_pSliderController->SetPos((int)m_fDefaultHeight);		// 위치 설정
    m_pSliderController->SetTicFreq(32);	// 눈금 간격 설정
    m_pSliderController->SetLineSize(4);	// 증가 크기(키보드로 컨트롤 할 때)
    m_pSliderController->SetPageSize(12);	// 증가 크기(PgUP,Dn 키나 슬라이더 몸동을 클릭하여 움직일 때)

                                            // 기본 높이 값 출력
    SetDlgItemInt(ID_DEFAULT_HEIGHT_EDI, (UINT)m_fDefaultHeight);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void cCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(cCreateMapDlg, CDialogEx)
    ON_CBN_SELCHANGE(ID_MAP_SIZE_COM, &cCreateMapDlg::OnMapSizeSelectchange)
    ON_EN_CHANGE(ID_DEFAULT_HEIGHT_EDI, &cCreateMapDlg::OnDefaultHeightChange)
    ON_NOTIFY(NM_CUSTOMDRAW, ID_DEFAULT_HEIGHT_SLI, &cCreateMapDlg::OnDefaultHeightCustomdrawDefaultHeight)
    ON_NOTIFY(UDN_DELTAPOS, ID_DEFAULT_HEIGHT_SPI, &cCreateMapDlg::OnDeltaposDefaultHeightSpin)
    ON_BN_CLICKED(ID_CREATE_MAP_BNT, &cCreateMapDlg::OnClickCreateMapBnt)
    ON_BN_CLICKED(IDC_TEX1_LOAD_BUT, &cCreateMapDlg::OnClickedTex1LoadButton)
    ON_BN_CLICKED(IDC_TEX2_LOAD_BUT, &cCreateMapDlg::OnClickedTex2LoadButton)
    ON_BN_CLICKED(IDC_TEX3_LOAD_BUT, &cCreateMapDlg::OnClickedTex3LoadButton)
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
    m_fDefaultHeight = (float)GetDlgItemInt(ID_DEFAULT_HEIGHT_EDI);

    // 슬라이더 위치 설정
    m_pSliderController->SetPos((int)m_fDefaultHeight);		// 위치 설정

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
    SetDlgItemInt(ID_DEFAULT_HEIGHT_EDI, (UINT)m_fDefaultHeight);

    // 슬라이더 위치 설정
    m_pSliderController->SetPos((int)m_fDefaultHeight);		// 위치 설정

    *pResult = 0;
}

// 지형 기본 높이 셋팅 (Slider로 설정)
void cCreateMapDlg::OnDefaultHeightCustomdrawDefaultHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 높이 값 넣기
    m_fDefaultHeight = (float)m_pSliderController->GetPos();

    // 높이 값 출력
    SetDlgItemInt(ID_DEFAULT_HEIGHT_EDI, (UINT)m_fDefaultHeight);

    *pResult = 0;
}

// 맵 만들기
void cCreateMapDlg::OnClickCreateMapBnt()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    m_isCreateMap = true;

    // 메모리 관리!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}

// 기본 텍스쳐 1 파일 오픈
void cCreateMapDlg::OnClickedTex1LoadButton()
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
void cCreateMapDlg::OnClickedTex2LoadButton()
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
void cCreateMapDlg::OnClickedTex3LoadButton()
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

