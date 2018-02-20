
// ImageTool1Doc.cpp : CImageTool1Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CImageTool1Doc 생성/소멸

CImageTool1Doc::CImageTool1Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

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
			if (dlg.m_nType == 0) { //그레이스케일 비트맵
				ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
			}
			else { //트루컬러 비트맵
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
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageTool1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CImageTool1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageTool1Doc 진단

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


// CImageTool1Doc 명령


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
		AfxPrintInfo(_T("[파일 열기] 파일 경로: %s\n 가로 크기: %d픽셀\n 세로 크기: %d픽셀\n 색상수: %d"),
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

	AfxPrintInfo(_T("[반전] 입력 영상 :%s"), GetTitle());
	AfxNewBitmap(dib);
}


void CImageTool1Doc::OnUpdateImageInverse(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 8);
}
