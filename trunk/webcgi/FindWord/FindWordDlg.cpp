// FindWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindWord.h"
#include "FindWordDlg.h"
#include "DirDialog.h"
#include ".\findworddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFindWordApp theApp;
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
// CFindWordDlg dialog

CFindWordDlg::CFindWordDlg(CWnd* pParent /*=NULL*/)
	: CResizeDlg(CFindWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindWordDlg)
	m_edit1 = _T("");
	m_edit2 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizeDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindWordDlg)
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindWordDlg, CResizeDlg)
	//{{AFX_MSG_MAP(CFindWordDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST2, OnGetdispinfoList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnColumnclickList2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_NO_CASE, OnNoCase)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_BN_CLICKED(IDC_LOG_FILE, OnLogFile)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOG_FILE2, OnBnClickedLogFile2)
END_MESSAGE_MAP()

CHeaderCtrl *pgHeaderCtrl = NULL;
/////////////////////////////////////////////////////////////////////////////
// CFindWordDlg message handlers

BOOL CFindWordDlg::OnInitDialog()
{
	CResizeDlg::OnInitDialog();

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
	bClick = FALSE;
	bNoCase = FALSE;
	bStop = FALSE;
	bLogFile = FALSE;	
	bConfig =  FALSE;
	bSearch = FALSE;
	m_strFile = "C:\\";
	m_edit1 = m_strFile;
	UpdateData(FALSE);
	nCount = 0;

	// Buttons
	AddControl(IDOK, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 0);
	AddControl(IDCANCEL, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 0);
	AddControl(IDC_BROWSE, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 0);
	AddControl(IDC_SEARCH, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 0);

	// Edit Controls
	AddControl(IDC_EDIT1, CST_RESIZE, CST_RESIZE, CST_NONE, CST_NONE, 1);
	AddControl(IDC_EDIT2, CST_RESIZE, CST_RESIZE, CST_NONE, CST_NONE, 1);

	// Check Box
	AddControl(IDC_NO_CASE, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 1);
	AddControl(IDC_LOG_FILE, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 1);

	// List Box
	AddControl(IDC_LIST2, CST_RESIZE, CST_RESIZE, CST_NONE, CST_RESIZE, 1);

	// Combo Box
	AddControl(IDC_COMBO1, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 1);

	// Static Control
	AddControl(IDC_STATIC_SEARCH, CST_NONE, CST_NONE, CST_NONE, CST_REPOS, 1);
	AddControl(IDC_SEARCH_STRING, CST_NONE, CST_NONE, CST_NONE, CST_NONE, 1);
	AddControl(IDC_SELECT_EXT, CST_REPOS, CST_REPOS, CST_NONE, CST_NONE, 1);

	m_combo1.AddString("*.*");
	m_combo1.AddString("*.cpp");
	m_combo1.AddString("*.h");
	m_combo1.AddString("*.log");
	m_combo1.AddString("*.txt");
	m_combo1.SetCurSel(0);
	// Set the sort icons
    COLORMAP cm = {RGB(0, 0, 0), RGB(255, 165, 0)};	// Set to orange
    m_imglstSortIcons.Create(9, 5, ILC_COLOR24 | ILC_MASK, 2, 0);
    m_bmpUpArrow.LoadMappedBitmap(IDB_HDRUP, 0, &cm, 1);
    m_nUpArrow = m_imglstSortIcons.Add(&m_bmpUpArrow, RGB(255, 255, 255));
    m_bmpDownArrow.LoadMappedBitmap(IDB_HDRDOWN, 0, &cm, 1);
    m_nDownArrow = m_imglstSortIcons.Add(&m_bmpDownArrow, RGB(255, 255, 255));

	DWORD dwExStyle;
	dwExStyle = m_list2.GetExtendedStyle();
	dwExStyle |= LVS_EX_GRIDLINES;
	dwExStyle |= LVS_EX_FULLROWSELECT;

	m_list2.SetExtendedStyle(dwExStyle);

	m_list2.SetBkColor(RGB(0, 0, 0));
	m_list2.SetTextBkColor(RGB(0, 0, 0));
	m_list2.SetTextColor(RGB(255, 255, 255));

	m_list2.InsertColumn(0, _T("File Name / Text String:"), LVCFMT_LEFT, 544);
	m_list2.InsertColumn(1, _T("Line Num."), LVCFMT_LEFT, 84);

	pHeaderCtrl = m_list2.GetHeaderCtrl();
	pgHeaderCtrl = pHeaderCtrl;
	pHeaderCtrl->SetImageList(&m_imglstSortIcons); // Sort Icon

	m_szaFiles.RemoveAll();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFindWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CResizeDlg::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFindWordDlg::OnPaint() 
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
		CResizeDlg::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFindWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFindWordDlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	CDirDialog dlg; 
	dlg.m_strTitle = _T("Choose directory");
	dlg.m_strSelDir = m_strFile;

	if (dlg.DoBrowse()) 
	{
		m_strFile = dlg.m_strPath;
		m_edit1 = m_strFile;
		UpdateData(FALSE);
	}		
}

void CFindWordDlg::OnSearch() 
{
	// TODO: Add your control notification handler code here
	bSearch ^= TRUE;
	if (bSearch)
	{
		GetDlgItem(IDC_SEARCH)->SetWindowText("Abort");
		bStop = FALSE;	
	}
	else
	{
		GetDlgItem(IDC_SEARCH)->SetWindowText("Search");
		bStop = TRUE;
	}
	GetDlgItem(IDC_COMBO1)->GetWindowText(m_strExt);
	if(m_strExt.Left(1) == "*")
		m_strExt.Delete(0, 1);
	UpdateData(TRUE);
	m_strSearch = m_edit2;
	if(m_strSearch.IsEmpty())
	{
		AfxMessageBox("Search string was Empty,\nplease try again.");
		return;
	}
	if(bNoCase)
		m_strSearch.MakeLower();
	nCount = 0;
	FreeItemMemory();
	m_list2.DeleteAllItems();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	RecurseDirectories(m_strFile);
	if(bLogFile)
		LogFiles();
	if(bConfig)
		MakeConfigFile();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("");
	m_list2.SetFocus();	
	GetDlgItem(IDC_SEARCH)->SetWindowText("Search");
	bSearch = FALSE;
	m_szaFiles.RemoveAll();
}

void CFindWordDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_combo1.GetCurSel();	
	CString str;
	int n;
	n = m_combo1.GetLBTextLen( nIndex );
	m_combo1.GetLBText( nIndex, str.GetBuffer(n) );
	str.ReleaseBuffer();

	m_strExt = str;
	if(m_strExt.Left(1) == "*")
		m_strExt.Delete(0, 1);
}

void CFindWordDlg::OnNoCase() 
{
	// TODO: Add your control notification handler code here
	bNoCase = TRUE;
}

void CFindWordDlg::RecurseDirectories(CString& strDir)
{
    CString strFilter = strDir;
    if (strFilter.Right (1) != _T ("\\"))
        strFilter += _T ("\\");
    strFilter += _T ("*.*");

	CString szFileName;
    CFileFind finder;
    BOOL bWorking = finder.FindFile(strFilter);
    while (bWorking)
    {
		theApp.ProcessIdleMsg();
		if(bStop)
		{
			finder.Close();
			Sleep(100);
			return;
		}
		CWaitCursor wait;

        bWorking = finder.FindNextFile();
        
        if (!finder.IsDots())
        {
            if (finder.IsDirectory())
                RecurseDirectories(finder.GetFilePath());
            else
			{
				szFileName = finder.GetFileName();
				szFullPath = finder.GetFilePath();
				
				int len = szFileName.GetLength();
				int pos = szFileName.ReverseFind('.');
				CString szExt = szFileName.Right(len - pos);
				if (szExt.CompareNoCase(m_strExt) == 0)
				{
					CompareFileDate(finder.GetFilePath());
					Sleep(10);	// Wait for List Control
				}
				if ((m_strExt == ".*") && (szExt != ".exe") &&
					(szExt != ".bmp"))
				{
					CompareFileDate(finder.GetFilePath());
					Sleep(10);	// Wait for List Control
				}
			}
        }
    }
	finder.Close();
}

BOOL CFindWordDlg::CompareFileDate(CString szFile)
{
	BOOL bRes = TRUE;
	CString szStr;
	CString szStrFormat;
	int len = 0;
	int line = 0;
	TRY
	{
		CStdioFile fd(szFile, CFile::modeRead);
		len = m_strFile.GetLength();
		szFile.Delete(0, len);
		GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText(szFile);
		while (fd.ReadString(szStr))
		{
			line++;
			if (bNoCase)
				szStr.MakeLower();
			if (szStr.Find(m_strSearch, 0) > 0)
			{
				nCount++;
				m_nLineNumber = line;
				szStrFormat.Format("File: %s", szFile);
				AddItem(szStrFormat);
				m_szaFiles.Add(szFullPath);
				Sleep(1);
				nCount++;
				szStrFormat.Format("Text: %s", szStr);
				szStrFormat.Replace("\t", "        ");
				AddItem(szStrFormat);
				szStrFormat.Format("Ln# %.4d %s", line, szStr);
				m_szaFiles.Add(szStrFormat);
			}
		}
		fd.Close();
	}
	CATCH(CFileException, pEx)
	{
		if (pEx->m_cause == CFileException::sharingViolation)
		{
			bRes = FALSE;
		}
		else
		{
			pEx->ReportError();
			bRes = FALSE;
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();
		bRes = FALSE;
	}
	END_CATCH_ALL
	return bRes;
}

BOOL CFindWordDlg::IsCfgItemExist(CString strItemName)
{
	if(m_szFilterFiles.GetSize() <= 0)
	{
		return FALSE;
	}
	else
	{
		for(int i = 0; i < m_szFilterFiles.GetSize(); i++)
		{
			if(m_szFilterFiles.GetAt(i) == strItemName)
				return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CFindWordDlg::AddItem(CString szFile)
{
	ITEMINFO *pItem;
	try {
		pItem = new ITEMINFO;
	}
	catch(CMemoryException* e) {
		e->Delete();
		return FALSE;
	}

	pItem->szFilename = szFile;
	pItem->nLineNumber = m_nLineNumber;

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.iItem = nCount;
	lvi.iSubItem = 0;
	lvi.iImage = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = (LPARAM) pItem;

	if(m_list2.InsertItem(&lvi) == -1)
		return FALSE;

	return TRUE;
}

void CFindWordDlg::OnGetdispinfoList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		ITEMINFO* pItem = (ITEMINFO*) pDispInfo->item.lParam;

		switch(pDispInfo->item.iSubItem)
		{
		case 0:	//My Documents
			lstrcpy(pDispInfo->item.pszText, pItem->szFilename);
			break;

		case 1:	//Line Number
			{
				CString szLineNumber;
				szLineNumber.Format("%.6d", pItem->nLineNumber);
				lstrcpy(pDispInfo->item.pszText, szLineNumber);
			}
			break;

		default:
			AfxMessageBox("Error in Display Info!");
			break;
		}

	}	
	
	*pResult = 0;
}

void CFindWordDlg::OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int nSubItem = pNMListView->iSubItem;
	int nCol = nSubItem;
	nSubItem += 1;	// because of -0 = +0
	if(bClick)
	{
		m_nSortColumn = nSubItem;
		SetSortIcon(nCol);
		m_list2.SortItems(CompareFunc, nSubItem);
		bClick = FALSE;
	}
	else
	{
		m_nSortColumn = -nSubItem;
		SetSortIcon(nCol);
		m_list2.SortItems(CompareFunc, -nSubItem);
		bClick = TRUE;
	}
	
	*pResult = 0;
}

int CALLBACK CFindWordDlg::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ITEMINFO* pItem1;
	ITEMINFO* pItem2;

	if (lParamSort > 0)
	{
		pItem1 =(ITEMINFO*) lParam1;
		pItem2 =(ITEMINFO*) lParam2;
		lParamSort -= 1;	// if positive
	}
	else
	{
		pItem2 =(ITEMINFO*) lParam1;
		pItem1 =(ITEMINFO*) lParam2;
		lParamSort += 1;	// if negative
	}

	int nResult;

	switch(abs(lParamSort))
	{
	case 0:	//My Documents
		nResult = pItem1->szFilename.CompareNoCase(pItem2->szFilename);
		break;

	case 1:	//Line Number
		nResult = pItem1->nLineNumber > pItem2->nLineNumber;
		break;

	default:
		AfxMessageBox("Error in Compare!");
		break;
	}
	return nResult;
}

void CFindWordDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	DWORD dwPos = ::GetMessagePos();
	CPoint pt((int) LOWORD(dwPos), (int) HIWORD(dwPos));
	m_list2.ScreenToClient(&pt);
	int nItem = m_list2.HitTest(pt);
	CString szFullPath = m_strFile;
	szFullPath += m_list2.GetItemText(nItem, 0);
	ShellExecute(m_hWnd, "open", szFullPath, NULL, NULL, SW_SHOWNORMAL);
	
	*pResult = 0;
}

// Display or hide sort icon on column to be sorted
void CFindWordDlg::SetSortIcon(int nCol)
{
	ASSERT(m_list2);
	CHeaderCtrl* pHeaderCtrl = m_list2.GetHeaderCtrl();
	ASSERT(pHeaderCtrl);
	
	HDITEM hdrItem;
	int    nPhysicalCol = nCol;
	int col;
	for (col = pHeaderCtrl->GetItemCount(); col >= 0; col--)
    {
		hdrItem.mask = HDI_FORMAT | HDI_IMAGE;
		pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
		if (m_nSortColumn     != 0 &&
			m_nSortColumn - 1 == col)
		{
			hdrItem.iImage = m_nUpArrow;
			hdrItem.fmt    = hdrItem.fmt & HDF_JUSTIFYMASK |
				HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
		}
		else if (m_nSortColumn     != 0 &&
			    -m_nSortColumn - 1 == col)
		{
			hdrItem.iImage = m_nDownArrow;
			hdrItem.fmt    = hdrItem.fmt & HDF_JUSTIFYMASK |
				HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
		}
		else
			hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
		pHeaderCtrl->SetItem(col, &hdrItem);
    }
}

void CFindWordDlg::FreeItemMemory()
{
	int nItemCount = m_list2.GetItemCount();
	if(nItemCount)
	{
		for(int i = 0; i < nItemCount; i++)
			delete(ITEMINFO*)m_list2.GetItemData(i);
	}
}

void CFindWordDlg::OnDestroy() 
{
	// TODO: Add your message handler code here
	if(bLogFile)
		LogFiles();
	FreeItemMemory();

	CResizeDlg::OnDestroy();
}

HBRUSH CFindWordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizeDlg::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		// Set the text color to blue
		pDC->SetTextColor(RGB(0, 0, 255));
		// Set the background mode for text to transparent 
		// so background will show thru.
		pDC->SetBkMode(TRANSPARENT);
	}
		
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFindWordDlg::OnLogFile() 
{
	// TODO: Add your control notification handler code here
	bLogFile = TRUE;	
}

void CFindWordDlg::LogFiles()
{
	CStdioFile fd;
	CString szFile;
	
	fd.Open("Log.txt", CFile::modeCreate | CFile::modeWrite);
	if(!fd)
	{
		AfxMessageBox("Couldn't open output file!");
			return;
	}
	for(int index = 0; index < m_szaFiles.GetSize(); index++)
	{
		szFile = m_szaFiles.GetAt(index);
		szFile += "\n";
		fd.WriteString(szFile);
	}
	fd.Close();
}


void CFindWordDlg::OnBnClickedLogFile2()
{
	bConfig =  TRUE;
	m_edit2 = "FindNodeValue(ResNode,\"IDS_";
	m_combo1.SelectString(0, "*.cpp");
	UpdateData(FALSE);

}

void CFindWordDlg::MakeConfigFile()
{
	CStdioFile fd;
	CString szFile;
	CString szFilePath,szTemp;
	int index = 0;
	UpdateData(TRUE);

	index = m_edit1.ReverseFind('\\');
	szTemp = m_edit1.Right(m_edit1.GetLength() - index);
	szTemp += "Res.txt";
	szFilePath = m_edit1 + szTemp;
	
	try
	{
		CFile::Remove(szFilePath);
	}
	catch (CFileException* pEx)
	{
		#ifdef _DEBUG
			afxDump << "File " << pFileName << " cannot be removed\n";
		#endif
		pEx->Delete();
	}

	fd.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);

	if(!fd)
	{
		AfxMessageBox("Couldn't open output file!");
			return;
	}

	for(int i = 0; i < m_szaFiles.GetSize(); i++)
	{
		szFile = m_szaFiles.GetAt(i);
		index = szFile.Find("FindNodeValue(ResNode,\"IDS_");
		if(index != -1)
		{
			szTemp = szFile.Right(szFile.GetLength() - index);
			index = szTemp.ReverseFind('\"');
			szFile = szTemp.Left(index);
			szTemp = szFile.Mid(23);
			szFile = szTemp;
			
			if(!IsCfgItemExist(szTemp))
			{
				m_szFilterFiles.Add(szTemp);
				szFile += "\n";
				fd.WriteString(szFile);				
			}
		}
	}
	fd.Close();
}