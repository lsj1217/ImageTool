
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList â

class COutputList : public CListBox
{
// �����Դϴ�.
public:
	COutputList();

// �����Դϴ�.
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
public:
	COutputWnd();

	void UpdateFonts();

	// Ư���Դϴ�.
protected:
	COutputList m_wndOutputInfo;

protected:
	void AdjustHorzScroll(CListBox& wndListBox);

	// �����Դϴ�.
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

public:
	void AddString(CString message);
};
