
// ImageTool1View.cpp : CImageTool1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool1.h"
#endif

#include "MainFrm.h"
#include "ImageTool1Doc.h"
#include "ImageTool1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageTool1View

IMPLEMENT_DYNCREATE(CImageTool1View, CScrollView)

BEGIN_MESSAGE_MAP(CImageTool1View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageTool1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, &CImageTool1View::OnViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CImageTool1View::OnUpdateViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CImageTool1View::OnViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CImageTool1View::OnUpdateViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CImageTool1View::OnViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CImageTool1View::OnUpdateViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, &CImageTool1View::OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CImageTool1View::OnUpdateViewZoom4)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CImageTool1View 생성/소멸

CImageTool1View::CImageTool1View()
	: m_nZoom(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageTool1View::~CImageTool1View()
{
}

BOOL CImageTool1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageTool1View 그리기

void CImageTool1View::OnDraw(CDC* pDC)
{
	CImageTool1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w * m_nZoom, h * m_nZoom);
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CImageTool1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizeToFit();
	
}

void CImageTool1View::SetScrollSizeToFit()
{
	CSize sizeTotal;
	CImageTool1Doc* pDoc = GetDocument();
	//비트맵 객체가 존재할 경우 해당 비트맵 높이와 너비에 맞춘다.
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		sizeTotal.cx = w * m_nZoom;
		sizeTotal.cy = h * m_nZoom;
	}
	//비트맵 객체가 없을 시 100 by 100으로 초기화
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}
	SetScrollSizes(MM_TEXT, sizeTotal);
	ResizeParentToFit(TRUE);
}


// CImageTool1View 인쇄


void CImageTool1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageTool1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageTool1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageTool1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageTool1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageTool1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageTool1View 진단

#ifdef _DEBUG
void CImageTool1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageTool1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageTool1Doc* CImageTool1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageTool1Doc)));
	return (CImageTool1Doc*)m_pDocument;
}
#endif //_DEBUGx


// CImageTool1View 메시지 처리기

//영상에서 프레임을 제외한 나머지 부분을 빗금으로 처리하고 ersebkgnd를 비활성화
BOOL CImageTool1View::OnEraseBkgnd(CDC* pDC)
{
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);


	return TRUE;
}


void CImageTool1View::OnViewZoom1()
{
	m_nZoom = 1;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageTool1View::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 1);
}


void CImageTool1View::OnViewZoom2()
{
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageTool1View::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 2);
}


void CImageTool1View::OnViewZoom3()
{
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageTool1View::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 3);
}


void CImageTool1View::OnViewZoom4()
{
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageTool1View::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 4);
}


void CImageTool1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// 상태바에 마우스 좌표 및 이미지 정보 표시
	CPoint pt = point + GetScrollPosition();
	pt.x /= m_nZoom;
	pt.y /= m_nZoom;
	ShowImageInfo(pt);

	CScrollView::OnMouseMove(nFlags, point);
}

void CImageTool1View::ShowImageInfo(CPoint point)
{
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CImageTool1Doc* pDoc = GetDocument();
	int w = pDoc->m_Dib.GetWidth();
	int h = pDoc->m_Dib.GetHeight();
	int c = pDoc->m_Dib.GetPaletteNums();

	CString strText;

	// 상태바에 마우스 좌표 표시

	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
	{
		strText.Format(_T("(%d, %d)"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}

	// 상태바에 이미지 정보 표시

	if (c == 0)
	{
		strText.Format(_T("w:%d h:%d c:16M"), w, h);
	}
	else
	{
		strText.Format(_T("w:%d h:%d c:%d"), w, h, c);
	}
	pFrame->m_wndStatusBar.SetPaneText(1, strText);
}
