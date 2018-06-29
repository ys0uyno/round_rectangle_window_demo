#pragma once

#include <GdiPlus.h>
#include "dlg_child.h"

// dlg_parent dialog

class dlg_parent : public CDialogEx
{
	DECLARE_DYNAMIC(dlg_parent)

public:
	dlg_parent(CWnd* pParent = NULL);   // standard constructor
	virtual ~dlg_parent();

// Dialog Data
	enum { IDD = IDD_DIALOG_PARENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void setImage();
	void ReSetChildDlg();
	void DrawTXBar();

private:
	BLENDFUNCTION m_blend;
	Gdiplus::Image *m_pImage;
	CRect m_CenterArea;
	dlg_child *m_pMainDlg;
public:
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};
