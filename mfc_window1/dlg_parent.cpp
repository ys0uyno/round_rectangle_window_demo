// dlg_parent.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_window1.h"
#include "dlg_parent.h"
#include "afxdialogex.h"


// dlg_parent dialog

IMPLEMENT_DYNAMIC(dlg_parent, CDialogEx)

dlg_parent::dlg_parent(CWnd* pParent /*=NULL*/)
	: CDialogEx(dlg_parent::IDD, pParent)
{

}

dlg_parent::~dlg_parent()
{
}

void dlg_parent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dlg_parent, CDialogEx)
END_MESSAGE_MAP()


// dlg_parent message handlers
