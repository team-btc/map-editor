
// ToolBasic00Doc.cpp : CToolBasic00Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ToolBasic.h"
#endif

#include "ToolBasicDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToolBasic00Doc

IMPLEMENT_DYNCREATE(CToolBasicDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolBasicDoc, CDocument)
    ON_COMMAND(ID_FILE_SAVE, &CToolBasicDoc::OnFileSave)
    ON_COMMAND(ID_FILE_OPEN, &CToolBasicDoc::OnFileOpen)
END_MESSAGE_MAP()


// CToolBasic00Doc 생성/소멸

CToolBasicDoc::CToolBasicDoc()
{
    // TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CToolBasicDoc::~CToolBasicDoc()
{
}

BOOL CToolBasicDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: 여기에 재초기화 코드를 추가합니다.
    // SDI 문서는 이 문서를 다시 사용합니다.

    return TRUE;
}




// CToolBasic00Doc serialization

//void CToolBasicDoc::Serialize(CArchive& ar)
//{
//    if (ar.IsStoring())
//    {
//        // TODO: 여기에 저장 코드를 추가합니다.
//
//        json jData = g_pMapDataManager->SaveMapData((string)ar.GetFile()->GetFileTitle());
//        ar.WriteString((CString)jData.dump().c_str());
//    }
//    else
//    {
//        g_pMapDataManager->LoadMapData((string)ar.GetFile()->GetFileTitle());
//    }
//}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CToolBasic00Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // 문서의 데이터를 그리려면 이 코드를 수정하십시오.
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CToolBasic00Doc::InitializeSearchContent()
{
    CString strSearchContent;
    // 문서의 데이터에서 검색 콘텐츠를 설정합니다.
    // 콘텐츠 부분은 ";"로 구분되어야 합니다.

    // 예: strSearchContent = _T("point;rectangle;circle;ole object;");
    SetSearchContent(strSearchContent);
}

void CToolBasic00Doc::SetSearchContent(const CString& value)
{
    if (value.IsEmpty())
    {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    }
    else
    {
        CMFCFilterChunkValueImpl *pChunk = NULL;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != NULL)
        {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif // SHARED_HANDLERS

// CToolBasic00Doc 진단

#ifdef _DEBUG
void CToolBasicDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CToolBasicDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CToolBasic00Doc 명령

// 파일 저장
void CToolBasicDoc::OnFileSave()
{
    // TODO: 여기에 명령 처리기 코드를 추가합니다.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "JSON Files (*.json) |*.JSON|";
    CFileDialog FileDialog(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    string caption = "JSON 파일 저장하기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();

        // 확장자가 jpg인지 체크 
        if (check == "JSON" || check == "json")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> 확장자를 제외한 파일 이름을 불러옴
            string strFileTitle = FileDialog.GetFileTitle().GetString();
            g_pMapDataManager->SaveMapData(strFileTitle);
        }
        else
        {
            MessageBox(g_hWnd, "파일 저장 실패", caption.c_str(), MB_ICONERROR);
        }
    }
}

// 파일 오픈
void CToolBasicDoc::OnFileOpen()
{
    // TODO: 여기에 명령 처리기 코드를 추가합니다.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // 확장자 필터
    LPSTR szFilter = "JSON Files (*.json) |*.JSON|";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    string caption = "JSON 파일 불러오기";

    if (FileDialog.DoModal() == IDOK)
    {
        //파일 확장자 가져오기 
        CString check = FileDialog.GetFileExt();

        // 확장자가 jpg인지 체크 
        if (check == "JSON" || check == "json")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> 확장자를 제외한 파일 이름을 불러옴
            string strFileTitle = FileDialog.GetFileTitle().GetString();
            g_pMapDataManager->LoadMapData(strFileTitle);
        }
        else
        {
            MessageBox(g_hWnd, "파일 읽기 실패", caption.c_str(), MB_ICONERROR);
        }
    }
}
