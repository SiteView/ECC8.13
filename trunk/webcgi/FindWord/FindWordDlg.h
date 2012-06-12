// FindWordDlg.h : header file
//

#if !defined(AFX_FINDWORDDLG_H__F3F122C7_308D_4205_BE84_ED458663F1B1__INCLUDED_)
#define AFX_FINDWORDDLG_H__F3F122C7_308D_4205_BE84_ED458663F1B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagITEMINFO {
	CString szFilename;
	int     nLineNumber;
} ITEMINFO;

#include "ResizeDlg.h"		// Added to resize Dialog

/////////////////////////////////////////////////////////////////////////////
// CFindWordDlg dialog

class CFindWordDlg : public CResizeDlg
{
// Construction
public:
	CFindWordDlg(CWnd* pParent = NULL);	// standard constructor
	void RecurseDirectories(CString& strDir);
	BOOL CompareFileDate(CString szFile);
	BOOL AddItem(CString szFile);
	void SetSortIcon(int nCol);
	void FreeItemMemory();
	void LogFiles();
	void MakeConfigFile();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	BOOL IsCfgItemExist(CString strItemName);
// Dialog Data
	//{{AFX_DATA(CFindWordDlg)
	enum { IDD = IDD_FINDWORD_DIALOG };
	CComboBox	m_combo1;
	CListCtrl	m_list2;
	CString	m_edit1;
	CString	m_edit2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindWordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL bClick;
	BOOL bLogFile;
	BOOL bNoCase;
	BOOL bConfig;
	BOOL bStop;
	BOOL bSearch;
	CString m_strFile;
	CString m_strExt;
	CString m_strSearch;
	CString szFullPath;
	CStringArray m_szaFiles;
	CStringArray m_szFilterFiles;
	CHeaderCtrl *pHeaderCtrl;
	CImageList m_imglstSortIcons;
	CBitmap m_bmpUpArrow;
	CBitmap m_bmpDownArrow;
	int m_nUpArrow;
	int m_nDownArrow;
	int m_nLineNumber;
	int nCount;
	int m_nSortColumn;
	// Generated message map functions
	//{{AFX_MSG(CFindWordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnSearch();
	afx_msg void OnDestroy();
	afx_msg void OnGetdispinfoList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNoCase();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLogFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogFile2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDWORDDLG_H__F3F122C7_308D_4205_BE84_ED458663F1B1__INCLUDED_)
