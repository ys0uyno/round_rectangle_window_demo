
// mfc_window0Dlg.h : header file
//

#pragma once


// Cmfc_window0Dlg dialog
class Cmfc_window0Dlg : public CDialogEx
{
// Construction
public:
	Cmfc_window0Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFC_WINDOW0_DIALOG };

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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	Gdiplus::Image *m_pgdi_image;
	HDC m_memory_hdc;
	int m_image_width;
	int m_image_height;
	BLENDFUNCTION m_blend;
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
