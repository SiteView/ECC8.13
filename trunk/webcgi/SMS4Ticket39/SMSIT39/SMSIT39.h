// SMSIT39.h : main header file for the SMSIT39 DLL
//

#if !defined(AFX_SMSIT39_H__44AEB8D4_43C4_484E_A30F_A1B4FE8EBED8__INCLUDED_)
#define AFX_SMSIT39_H__44AEB8D4_43C4_484E_A30F_A1B4FE8EBED8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39App
// See SMSIT39.cpp for the implementation of this class
//

class CSMSIT39App : public CWinApp
{
public:
	CSMSIT39App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMSIT39App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSMSIT39App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMSIT39_H__44AEB8D4_43C4_484E_A30F_A1B4FE8EBED8__INCLUDED_)
