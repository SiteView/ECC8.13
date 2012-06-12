// TimeoutSocket.cpp : implementation file
//

#include "stdafx.h"
#include "TimeoutSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeoutSocket

CTimeoutSocket::CTimeoutSocket()
{
	m_uRecvCrackTimeout = 10;
	m_nRecvRetry = 0;
}

CTimeoutSocket::~CTimeoutSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CTimeoutSocket, CSocket)
	//{{AFX_MSG_MAP(CTimeoutSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CTimeoutSocket member functions
int CTimeoutSocket::_Receive(void *lpBuf, int nBufLen, DWORD uWaitTimeout, int nFlags)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}
	int nResult;
	DWORD uTick = ::GetTickCount();

	while ((nResult = CAsyncSocket::Receive(lpBuf, nBufLen, nFlags)) == SOCKET_ERROR)
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			if (::GetTickCount() - uTick >= uWaitTimeout)
				return SOCKET_RECV_TIMEOUT;

			if (!PumpMessages(FD_READ))
				return SOCKET_ERROR;
		}
		else
			return SOCKET_ERROR;
	}

	return nResult;
}

int CTimeoutSocket::Receive(void *lpBuf, int nBufLen, DWORD uTimeout, int nFlags)
{
	int nResult = _Receive(lpBuf, nBufLen, uTimeout, nFlags);

	if (nResult > 0 && nResult < nBufLen && m_nRecvRetry > 0)
	{// 收到数据但是没有达到目标数量

		int nRecvRetry = m_nRecvRetry;
		LPBYTE pBuff = LPBYTE(lpBuf);
		pBuff += nResult;
		nBufLen -= nResult;
		--nRecvRetry;
		int nRecv = _Receive(lpBuf, nBufLen, m_uRecvCrackTimeout, nFlags);
		while(nRecv > 0)
		{
			nResult += nRecv;
			pBuff += nRecv;
			nBufLen -= nRecv;
			if (nBufLen < 1 || nRecvRetry < 1)
				break;
			nRecv = _Receive(lpBuf, nBufLen, m_uRecvCrackTimeout, nFlags);
		}
	}

	return nResult;
}
