#if !defined(AFX_TIMEOUTSOCKET_H__F9A36913_18F5_4DDE_AA27_9BAFE498EC66__INCLUDED_)
#define AFX_TIMEOUTSOCKET_H__F9A36913_18F5_4DDE_AA27_9BAFE498EC66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeoutSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CTimeoutSocket command target

#define SOCKET_RECV_TIMEOUT					int(-100)

class CTimeoutSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CTimeoutSocket();
	virtual ~CTimeoutSocket();

// Overrides
public:
	int Receive(void* lpBuf, int nBufLen, DWORD uTimeout = 0xFFFFFFFF, int nFlags = 0);
	DWORD m_uRecvCrackTimeout; // 接收数据时数据裂缝超时
	int m_nRecvRetry; // 在接收数据时的重试次数
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeoutSocket)
	public:
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CTimeoutSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	int _Receive(void *lpBuf, int nBufLen, DWORD uWaitTimeout, int nFlags);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEOUTSOCKET_H__F9A36913_18F5_4DDE_AA27_9BAFE498EC66__INCLUDED_)
