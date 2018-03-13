
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

void CToolBasicDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
        json jData = g_pMapDataManager->SaveMapData();
        ar.WriteString((CString)jData.dump().c_str());
    }
    else
    {
        // TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
        g_pMapDataManager->LoadMapData((string)ar.GetFile()->GetFilePath(), (string)ar.GetFile()->GetFileName()); //path�� �̸��� Ȯ���ڸ��� �����ϰ� ����
    }
}

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
