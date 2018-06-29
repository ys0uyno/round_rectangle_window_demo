
// mfc_window1Dlg.h : header file
//

#pragma once


// Cmfc_window1Dlg dialog
class Cmfc_window1Dlg : public CDialogEx
{
// Construction
public:
	Cmfc_window1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFC_WINDOW1_DIALOG };

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
	void SetParentDlg(CWnd *dlg){ parentDlg = dlg; }

private:
	CWnd *parentDlg;
	CBrush m_brush;
	CDC *m_pMemDC;
	CBitmap *m_pBitmap;
	int m_nScreenX;
	int m_nScreenY;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};
