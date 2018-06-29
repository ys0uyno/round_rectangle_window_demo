
// mfc_window0Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_window0.h"
#include "mfc_window0Dlg.h"
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


// Cmfc_window0Dlg dialog




Cmfc_window0Dlg::Cmfc_window0Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_window0Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_window0Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_window0Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Cmfc_window0Dlg message handlers

BOOL Cmfc_window0Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cmfc_window0Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmfc_window0Dlg::OnPaint()
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
		CDialogEx::OnPaint();

		HDC temp_hdc = GetDC()->m_hDC;
		m_memory_hdc = CreateCompatibleDC(temp_hdc);
		HBITMAP hbitmap = CreateCompatibleBitmap(temp_hdc, m_image_width, m_image_height);
		SelectObject(m_memory_hdc, hbitmap);

		RECT temp_rect;
		GetWindowRect(&temp_rect);
		POINT pt_dst = { temp_rect.left, temp_rect.top };

		Gdiplus::Point points[] =
		{
			Gdiplus::Point(0, 0),
			Gdiplus::Point(m_image_width, 0),
			Gdiplus::Point(0, m_image_height)
		};

		Gdiplus::Graphics g(m_memory_hdc);
		g.DrawImage(m_pgdi_image, points, 3);

		DWORD dw_style = GetWindowLong(m_hWnd, GWL_EXSTYLE);
		if ((dw_style & 0x80000) != 0x80000)
			SetWindowLong(m_hWnd, GWL_EXSTYLE, dw_style ^ 0x80000);

		SIZE window_size = { m_image_width, m_image_height };
		POINT pt_src = { 0, 0 };
		HDC screen_hdc = ::GetDC(m_hWnd);

		::UpdateLayeredWindow(
			m_hWnd,
			screen_hdc,
			&pt_dst,
			&window_size,
			m_memory_hdc,
			&pt_src,
			0,
			&m_blend,
			ULW_ALPHA
			);

		g.ReleaseHDC(m_memory_hdc);

		::ReleaseDC(m_hWnd, screen_hdc);
		screen_hdc = NULL;
		::ReleaseDC(m_hWnd, temp_hdc);
		temp_hdc = NULL;
		DeleteObject(hbitmap);
		DeleteDC(m_memory_hdc);
		m_memory_hdc = NULL;
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cmfc_window0Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// http://www.cnblogs.com/buffer/archive/2009/03/13/1410326.html
int Cmfc_window0Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_blend.BlendOp = 0;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = 1;
	m_blend.SourceConstantAlpha = 255;

	m_pgdi_image = Gdiplus::Image::FromFile(L".\\res\\bk.png");
	m_image_width = m_pgdi_image->GetWidth();
	m_image_height = m_pgdi_image->GetHeight();

	// 窗口置顶
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, m_image_width, m_image_height, SWP_NOSIZE | SWP_NOMOVE);

	return 0;
}

void Cmfc_window0Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	delete m_pgdi_image;
	m_pgdi_image = NULL;
}

void Cmfc_window0Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 禁止显示移动矩形窗体框
	::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
	// 非标题栏移动整个窗口
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);
	// PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialogEx::OnLButtonDown(nFlags, point);
}
