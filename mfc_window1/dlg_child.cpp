// dlg_child.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_window1.h"
#include "dlg_child.h"
#include "afxdialogex.h"


// dlg_child dialog

IMPLEMENT_DYNAMIC(dlg_child, CDialogEx)

dlg_child::dlg_child(CWnd* pParent /*=NULL*/)
	: CDialogEx(dlg_child::IDD, pParent)
{

}

dlg_child::~dlg_child()
{
}

void dlg_child::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dlg_child, CDialogEx)
END_MESSAGE_MAP()


// dlg_child message handlers
