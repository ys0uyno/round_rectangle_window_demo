#pragma once


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
};
