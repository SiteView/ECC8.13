// FindWord.h : main header file for the FINDWORD application
//

#if !defined(AFX_FINDWORD_H__226B2B6D_6A36_444D_BE41_E113A19CC19F__INCLUDED_)
#define AFX_FINDWORD_H__226B2B6D_6A36_444D_BE41_E113A19CC19F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFindWordApp:
// See FindWord.cpp for the implementation of this class
//

class CFindWordApp : public CWinApp
{
public:
	CFindWordApp();
	void CFindWordApp::ProcessIdleMsg();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindWordApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFindWordApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDWORD_H__226B2B6D_6A36_444D_BE41_E113A19CC19F__INCLUDED_)
