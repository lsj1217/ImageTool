// FileNewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageTool1.h"
#include "FileNewDlg.h"
#include "afxdialogex.h"


// CFileNewDlg dialog

IMPLEMENT_DYNAMIC(CFileNewDlg, CDialogEx)

CFileNewDlg::CFileNewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILE_NEW, pParent)
	, m_nWidth(256)
	, m_nHeight(256)
	, m_nType(0)
{

}

CFileNewDlg::~CFileNewDlg()
{
}

void CFileNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 4096);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 1, 4096);
	DDX_CBIndex(pDX, IDC_IMAGE_TYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDlg, CDialogEx)
	ON_EN_CHANGE(IDC_HEIGHT, &CFileNewDlg::OnEnChangeHeight)
	ON_EN_CHANGE(IDC_WIDTH, &CFileNewDlg::OnEnChangeWidth)
END_MESSAGE_MAP()


// CFileNewDlg message handlers


void CFileNewDlg::OnEnChangeHeight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CFileNewDlg::OnEnChangeWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
