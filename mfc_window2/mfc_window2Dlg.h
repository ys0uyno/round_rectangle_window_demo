
// mfc_window2Dlg.h : header file
//

#pragma once

#include "dlg_test0.h"

// Cmfc_window2Dlg dialog
class Cmfc_window2Dlg : public CDialogEx
{
// Construction
public:
	Cmfc_window2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFC_WINDOW2_DIALOG };

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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMove(int x, int y);

public:
	// from mfc_window1Dlg
	void SetParentDlg(CWnd *dlg){ parentDlg = dlg; }

	// from mfc_window1's dlg_parent
	void setImage();
	void ReSetChildDlg();
	void DrawTXBar();

private:
	// form mfc_window1Dlg
	CWnd *parentDlg;
	CBrush m_brush;
	CDC *m_pMemDC;
	CBitmap *m_pBitmap;
	int m_nScreenX;
	int m_nScreenY;

	// from mfc_window1's dlg_parent
	BLENDFUNCTION m_blend;
	Gdiplus::Image *m_pImage;
	CRect m_CenterArea;
	dlg_test0 *m_pMainDlg;
};
