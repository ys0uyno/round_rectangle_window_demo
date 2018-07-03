// dlg_parent.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_window1.h"
#include "dlg_parent.h"
#include "afxdialogex.h"
#include "util.h"

// dlg_parent dialog

IMPLEMENT_DYNAMIC(dlg_parent, CDialogEx)

dlg_parent::dlg_parent(CWnd* pParent /*=NULL*/)
	: CDialogEx(dlg_parent::IDD, pParent)
	, m_pMainDlg(NULL)
	, m_pImage(NULL)
{

}

dlg_parent::~dlg_parent()
{
}

void dlg_parent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BOOL dlg_parent::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);

	VERIFY((dwStyle & WS_POPUP) != 0);
	VERIFY((dwStyle & WS_CHILD) == 0);

	m_blend.BlendOp = 0;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = 1;
	m_blend.SourceConstantAlpha = 255;

	setImage();
	return TRUE;
}

void dlg_parent::setImage()
{
	GdiImageFromResource(&m_pImage, IDB_PNG_BK, L"PNG");
	if (m_pImage)
	{
		MoveWindow(CRect(0, 0, m_pImage->GetWidth(), m_pImage->GetHeight()));
		this->CenterWindow();
		m_CenterArea = CRect(31, 24, m_pImage->GetWidth() - 27, m_pImage->GetHeight() - 23);
		ReSetChildDlg();
		m_pMainDlg->SetDrawRect(m_CenterArea);
		DrawTXBar();
	}
}

void dlg_parent::ReSetChildDlg()
{
	CRect rcWin;
	GetWindowRect(&rcWin);
	rcWin.left += m_CenterArea.left;
	rcWin.top += m_CenterArea.top;
	rcWin.right = rcWin.left + m_CenterArea.Width();
	rcWin.bottom = rcWin.top + m_CenterArea.Height();
	if (m_pMainDlg)
	{
		m_pMainDlg->MoveWindow(rcWin);
	}
}

void dlg_parent::DrawTXBar()
{
	RECT rct;
	GetWindowRect(&rct);

	HDC hdcTemp = GetDC()->m_hDC;
	HDC m_hdcMemory = CreateCompatibleDC(hdcTemp);
	HBITMAP hBitMap = CreateCompatibleBitmap(hdcTemp, rct.right, rct.bottom);
	SelectObject(m_hdcMemory, hBitMap);

	POINT ptWinPos = { rct.left, rct.top };

	Gdiplus::Graphics graphics(m_hdcMemory);
	RECT rcClient;
	GetClientRect(&rcClient);

	graphics.DrawImage(m_pImage, Gdiplus::Rect(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom));

	SIZE sizeWindow = { rct.right, rct.bottom };
	POINT ptSrc = { 0, 0 };

	DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle & 0x80000) != 0x80000)
		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);

	HDC hdcScreen = ::GetDC(m_hWnd);
	::UpdateLayeredWindow(m_hWnd, hdcScreen, &ptWinPos, &sizeWindow, m_hdcMemory, &ptSrc, 0, &m_blend, 2);
	graphics.ReleaseHDC(m_hdcMemory);
	::ReleaseDC(m_hWnd, hdcScreen);
	hdcScreen = NULL;
	::ReleaseDC(m_hWnd, hdcTemp);
	hdcTemp = NULL;
	DeleteObject(hBitMap);
	DeleteDC(m_hdcMemory);
	m_hdcMemory = NULL;
}

BEGIN_MESSAGE_MAP(dlg_parent, CDialogEx)
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_DISPLAYCHANGE, OnDisplayChange)
END_MESSAGE_MAP()


// dlg_parent message handlers


void dlg_parent::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	ReSetChildDlg();
}


void dlg_parent::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	::SendMessage(GetSafeHwnd(), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}


int dlg_parent::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_pMainDlg = new dlg_child(this);
	if (m_pMainDlg)
	{
		m_pMainDlg->Create(IDD_DIALOG_CHILD, this);
		m_pMainDlg->ShowWindow(SW_SHOW);
		m_pMainDlg->SetParentDlg(this);
	}

	return 0;
}


void dlg_parent::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_pMainDlg)
	{
		delete m_pMainDlg;
		m_pMainDlg = NULL;
	}

	if (m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}
