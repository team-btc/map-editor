
// ToolBasic00Doc.cpp : CToolBasic00Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CToolBasic00Doc ����/�Ҹ�

CToolBasicDoc::CToolBasicDoc()
{
    // TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CToolBasicDoc::~CToolBasicDoc()
{
}

BOOL CToolBasicDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
    // SDI ������ �� ������ �ٽ� ����մϴ�.

    return TRUE;
}




// CToolBasic00Doc serialization

//void CToolBasicDoc::Serialize(CArchive& ar)
//{
//    if (ar.IsStoring())
//    {
//        // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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

// ����� �׸��� �����մϴ�.
void CToolBasic00Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CToolBasic00Doc::InitializeSearchContent()
{
    CString strSearchContent;
    // ������ �����Ϳ��� �˻� �������� �����մϴ�.
    // ������ �κ��� ";"�� ���еǾ�� �մϴ�.

    // ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CToolBasic00Doc ����

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


// CToolBasic00Doc ���

// ���� ����
void CToolBasicDoc::OnFileSave()
{
    // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // Ȯ���� ����
    LPSTR szFilter = "JSON Files (*.json) |*.JSON|";
    CFileDialog FileDialog(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    string caption = "JSON ���� �����ϱ�";

    if (FileDialog.DoModal() == IDOK)
    {
        //���� Ȯ���� �������� 
        CString check = FileDialog.GetFileExt();

        // Ȯ���ڰ� jpg���� üũ 
        if (check == "JSON" || check == "json")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> Ȯ���ڸ� ������ ���� �̸��� �ҷ���
            string strFileTitle = FileDialog.GetFileTitle().GetString();
            g_pMapDataManager->SaveMapData(strFileTitle);
        }
        else
        {
            MessageBox(g_hWnd, "���� ���� ����", caption.c_str(), MB_ICONERROR);
        }
    }
}

// ���� ����
void CToolBasicDoc::OnFileOpen()
{
    // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    // Ȯ���� ����
    LPSTR szFilter = "JSON Files (*.json) |*.JSON|";
    CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    string caption = "JSON ���� �ҷ�����";

    if (FileDialog.DoModal() == IDOK)
    {
        //���� Ȯ���� �������� 
        CString check = FileDialog.GetFileExt();

        // Ȯ���ڰ� jpg���� üũ 
        if (check == "JSON" || check == "json")
        {
            //m_strFileKey = FileDialog.GetFileTitle(); -> Ȯ���ڸ� ������ ���� �̸��� �ҷ���
            string strFileTitle = FileDialog.GetFileTitle().GetString();
            g_pMapDataManager->LoadMapData(strFileTitle);
        }
        else
        {
            MessageBox(g_hWnd, "���� �б� ����", caption.c_str(), MB_ICONERROR);
        }
    }
}
