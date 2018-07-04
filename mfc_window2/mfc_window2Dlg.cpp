
// mfc_window2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_window2.h"
#include "mfc_window2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_window2Dlg dialog




Cmfc_window2Dlg::Cmfc_window2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_window2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_window2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_window2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// Cmfc_window2Dlg message handlers

BOOL Cmfc_window2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// from mfc_window1Dlg
	COLORREF transColor = RGB(0, 255, 0);
	m_brush.CreateSolidBrush(transColor);

	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	::SetWindowLong(m_hWnd, GWL_STYLE, dwExStyle | 0x80000);

	::SetLayeredWindowAttributes(m_hWnd, transColor, 0, 1);

	// from mfc_window1's dlg_parent
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);

	VERIFY((dwStyle & WS_POPUP) != 0);
	VERIFY((dwStyle & WS_CHILD) == 0);

	m_blend.BlendOp = 0;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = 1;
	m_blend.SourceConstantAlpha = 255;

	setImage();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cmfc_window2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cmfc_window2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// from mfc_window1Dlg
		CDC *pDC = GetDC();
		CRect rect;
		GetClientRect(rect);
		CBitmap *oldBitmap = m_pMemDC->SelectObject(m_pBitmap);
		pDC->BitBlt(rect.left, rect.top, m_nScreenX, m_nScreenY, m_pMemDC, rect.left, rect.top, SRCCOPY);
		m_pMemDC->SelectObject(oldBitmap);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cmfc_window2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH Cmfc_window2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return m_brush;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void Cmfc_window2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	::SendMessage(parentDlg->GetSafeHwnd(), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}


int Cmfc_window2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	// from mfc_window1Dlg
	CDC *pDC = GetDC();
	m_pMemDC = new CDC();
	m_pBitmap = new CBitmap();
	m_nScreenX = 556;
	m_nScreenY = 397;
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC, m_nScreenX, m_nScreenY);
	CBitmap *oldBitmap = m_pMemDC->SelectObject(m_pBitmap);
	CBrush brush(RGB(255, 255, 255));
	CRect rect;
	GetClientRect(&rect);
	m_pMemDC->FillRect(CRect(rect.left, rect.top, m_nScreenX, m_nScreenY), &brush);
	m_pMemDC->SelectObject(oldBitmap);
	ReleaseDC(pDC);

	// from mfc_window1's dlg_parent
	m_pMainDlg = new dlg_test0(this);
	if (m_pMainDlg)
	{
		m_pMainDlg->Create(IDD_DIALOG_TEST0, this);
		m_pMainDlg->ShowWindow(SW_SHOW);
		m_pMainDlg->SetParentDlg(this);
	}

	return 0;
}


void Cmfc_window2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

	// from mfc_window1Dlg
	if (m_pMemDC)
	{
		delete m_pMemDC;
		m_pMemDC = NULL;
	}

	if (m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

	// from mfc_window1's dlg_parent
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

void Cmfc_window2Dlg::setImage()
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

void Cmfc_window2Dlg::ReSetChildDlg()
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

void Cmfc_window2Dlg::DrawTXBar()
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

void Cmfc_window2Dlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	ReSetChildDlg();
}
