#pragma once

#include "gdi_image_render.h"

// dlg_child dialog

class dlg_child : public CDialogEx
{
	DECLARE_DYNAMIC(dlg_child)

public:
	dlg_child(CWnd* pParent = NULL);   // standard constructor
	virtual ~dlg_child();

// Dialog Data
	enum { IDD = IDD_DIALOG_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void SetDrawRect(CRect & crt){ m_DrawRect = crt; }
	void SetParentDlg(CWnd * dlg){ parentDlg = dlg; }

private:
	CRect m_DrawRect;
	CWnd* parentDlg;
	CDC *m_pMemDC;
	CBitmap* m_pBitmap;
	int m_nScreenX;
	int m_nScreenY;
	gdi_image_render m_BK;
	CBrush m_brush;
	HICON m_hIcon;

	void DrawSomething();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};
