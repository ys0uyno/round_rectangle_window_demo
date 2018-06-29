#pragma once


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
};
