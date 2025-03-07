
// AAADlg.h : header file
//

#pragma once


// CAAADlg dialog
class CAAADlg : public CDialogEx
{
// Construction
public:
	CAAADlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AAA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
  
	CToolBar m_wndToolBar; 
	CMenu m_Menu;
	CStatusBarCtrl m_SBar;

	CSplitterWnd m_wndSplitter;

	bool initdlg;

public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnFileExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTreeCtrl m_Tree;
	CStatic m_Static_tree;
	void SetPosTreePanel(void);
};
