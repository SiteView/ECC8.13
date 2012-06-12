// SMSIT39TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMSIT39Test.h"
#include "SMSIT39TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39TestDlg dialog

CSMSIT39TestDlg::CSMSIT39TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMSIT39TestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSMSIT39TestDlg)
	m_strDes = _T("13800000007");
	m_strMsg = _T("Test ²âÊÔ 123");
//	m_strSrc = _T("UID=abcdefgh; PWD=12345678; ServiceID=SIDSID; DisplayPhone=11608851; ServerName=127.0.0.1; ServerPort=1608");
	m_strSrc = _T("URL=http://127.0.0.1/SMSTest.asp;smallCode=TEST;srcMobile=13973100000;linkId=20050301030450001;workFlage=0;user=Test;password=123456");
//	m_strDllFile =  _T("../../SMSIT39/Release/SMSIT39.dll");
	m_strDllFile =  _T("../../SMSIT31/DEBUG/SMSIT31.dll");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMSIT39TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSMSIT39TestDlg)
	DDX_Text(pDX, IDC_ED_DES, m_strDes);
	DDX_Text(pDX, IDC_ED_MSG, m_strMsg);
	DDX_Text(pDX, IDC_ED_SRC, m_strSrc);
	DDX_Text(pDX, IDC_ED_DLLFILE, m_strDllFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSMSIT39TestDlg, CDialog)
	//{{AFX_MSG_MAP(CSMSIT39TestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_SEND, OnBtSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39TestDlg message handlers

BOOL CSMSIT39TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

void CSMSIT39TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMSIT39TestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSMSIT39TestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

typedef int (*RUN_FUNC)(LPCSTR source, LPCSTR destination, LPCSTR content);

void CSMSIT39TestDlg::OnBtSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	HMODULE hDll = ::LoadLibrary(m_strDllFile);
	if (NULL != hDll)
	{
		RUN_FUNC run = NULL;
		run = RUN_FUNC(::GetProcAddress(hDll, _T("run")));
		if (NULL != run)
		{
			DWORD uTick = ::GetTickCount();
			if (run(m_strSrc, m_strDes, m_strMsg))
			{
				CString strMsg;
				strMsg.Format("Succeeded. time(%d)", ::GetTickCount() - uTick);
				MessageBox(strMsg);
			}
			else
			{
				MessageBox(_T("Send failed."));
			}
		}
		else
		{
			MessageBox(_T("Can't find func 'run'."));
		}
		::FreeLibrary(hDll);
	}
	else
	{
		MessageBox(_T("Can't load .dll file."));
	}
}
