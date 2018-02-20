#pragma once


// CFileNewDlg dialog

class CFileNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileNewDlg)

public:
	CFileNewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileNewDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_NEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//�̹��� ���� ����
	int m_nWidth;
	int m_nHeight;
	//�̹��� ���� Ÿ��(0 : �׷��̽�����, 1: Ʈ���÷�)
	int m_nType;


	afx_msg void OnEnChangeHeight();
	afx_msg void OnEnChangeWidth();
};
