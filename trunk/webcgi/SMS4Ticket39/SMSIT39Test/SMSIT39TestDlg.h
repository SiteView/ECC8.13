// SMSIT39TestDlg.h : header file
//

#if !defined(AFX_SMSIT39TESTDLG_H__1BE46F33_E0B2_40D8_95FA_CA38123BB38B__INCLUDED_)
#define AFX_SMSIT39TESTDLG_H__1BE46F33_E0B2_40D8_95FA_CA38123BB38B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39TestDlg dialog

class CSMSIT39TestDlg : public CDialog
{
// Construction
public:
	CSMSIT39TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSMSIT39TestDlg)
	enum { IDD = IDD_SMSIT39TEST_DIALOG };
	CString	m_strDes;
	CString	m_strMsg;
	CString	m_strSrc;
	CString	m_strDllFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMSIT39TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSMSIT39TestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMSIT39TESTDLG_H__1BE46F33_E0B2_40D8_95FA_CA38123BB38B__INCLUDED_)
