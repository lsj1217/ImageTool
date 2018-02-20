
// ImageTool1Doc.cpp : CImageTool1Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageTool1.h"
#endif

#include ".\IppDib\IppImage.h"
#include ".\IppDib\IppConvert.h"
#include "IppEnhance.h"

#include "ImageTool1Doc.h"
#include "FileNewDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageTool1Doc

IMPLEMENT_DYNCREATE(CImageTool1Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageTool1Doc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageTool1Doc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CImageTool1Doc::OnEditCopy)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageTool1Doc::OnImageInverse)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_INVERSE, &CImageTool1Doc::OnUpdateImageInverse)
END_MESSAGE_MAP()


// CImageTool1Doc ����/�Ҹ�

CImageTool1Doc::CImageTool1Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageTool1Doc::~CImageTool1Doc()
{
}

BOOL CImageTool1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL ret = TRUE;

	if (theApp.m_pNewDib == NULL) {


		CFileNewDlg dlg;

		if (dlg.DoModal() == IDOK) {
			if (dlg.m_nType == 0) { //�׷��̽����� ��Ʈ��
				ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
			}
			else { //Ʈ���÷� ��Ʈ��
				ret = m_Dib.CreateRgbBitmap(dlg.m_nWidth, dlg.m_nHeight);
			}
		}
		else {
			ret = FALSE;
		}
	}
	else {
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;void AfxNewBitmap(IppDib& dib);
	}
	return ret;
}




// CImageTool1Doc serialization

void CImageTool1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageTool1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CImageTool1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageTool1Doc::SetSearchContent(const CString& value)
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

// CImageTool1Doc ����

#ifdef _DEBUG
void CImageTool1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageTool1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageTool1Doc ���


BOOL CImageTool1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	/*if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return m_Dib.Load(CT2A(lpszPathName));
	*/
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	BOOL res = m_Dib.Load(CT2A(lpszPathName));
	if (res)
		AfxPrintInfo(_T("[���� ����] ���� ���: %s\n ���� ũ��: %d�ȼ�\n ���� ũ��: %d�ȼ�\n �����: %d"),
			lpszPathName, m_Dib.GetWidth(), m_Dib.GetHeight(), 0x01 << m_Dib.GetBitCount());

	return res;
}


BOOL CImageTool1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_Dib.Save(CT2A(lpszPathName));
}


void CImageTool1Doc::OnWindowDuplicate()
{
	AfxNewBitmap(m_Dib);
}


void CImageTool1Doc::OnEditCopy()
{
	if (m_Dib.IsValid()) {
		m_Dib.CopyToClipboard();
	}
}

#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img) \
IppByteImage img; \
IppDibToImage(m_Dib, img);

#define CONVERT_BYTEIMAGE_TO_DIB(img, m_Dib) \
IppDib dib; \
IppImageToDib(img, dib);

void CImageTool1Doc::OnImageInverse()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img);
	IppInverse(img);

	CONVERT_BYTEIMAGE_TO_DIB(img, m_Dib);

	AfxPrintInfo(_T("[����] �Է� ���� :%s"), GetTitle());
	AfxNewBitmap(dib);
}


void CImageTool1Doc::OnUpdateImageInverse(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 8);
}
