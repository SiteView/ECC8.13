// SMST39VS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SMST39VS.h"
#include <conio.h>
#include "../SMSIT39/TimeoutSocket.h"
#include "../SMSIT39/MsgObjs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;


#define SMST39_SERVER_PORT			UINT(1608)

int _Receive(CTimeoutSocket & Socket, LPBYTE pBuff, int nMaxBuff)
{
	int nRecvBytes = 0;
	int nRecv = Socket.Receive(pBuff, nMaxBuff);
	while (nRecv > 0)
	{
		nRecvBytes += nRecv;
		pBuff += nRecv;
		nMaxBuff -= nRecv;
		if (nMaxBuff > 0)
			nRecv = Socket.Receive(pBuff, nMaxBuff, 50);
		else
			break;
	}
	return nRecvBytes;
}

void Process(CTimeoutSocket & Socket)
{
	const int MAX_RECV_BUFF = 1024;
	BYTE szRecvBuff[MAX_RECV_BUFF] = {0};
	const int MAX_SEND_BUFF = 1024;
	BYTE szSendBuff[MAX_SEND_BUFF] = {0};

	int nRecvTO = 1;
	BOOL b = Socket.SetSockOpt(SO_RCVTIMEO, &nRecvTO, sizeof(nRecvTO));
	int nRecved = _Receive(Socket, szRecvBuff, MAX_SEND_BUFF);
	bool bLogon = false;
	while(nRecved > 0)
	{
		printf("Recv: %s\n", szRecvBuff);
		if (nRecved == 26)
		{// 可能是登录命令
			CMsgLogon MsgLogon;
			if (MsgLogon.SetString(CString(LPCSTR(szRecvBuff))))
			{
				printf(" Str: %s\n", LPCSTR(MsgLogon.GetString()));
				CMsgLogonRes MsgLogonRes;
				MsgLogonRes.m_strResult = "1";
				CString strRes = MsgLogonRes.GetString();
				Socket.Send(LPCSTR(strRes), strlen(strRes));
				printf("Send: %s\n", LPCSTR(strRes));
				bLogon = true;
			}
			else
			{
				printf(" Err: Invalid logon msg format.\n");
				CMsgLogonRes MsgLogonRes;
				MsgLogonRes.m_strResult = "0";
				CString strRes = MsgLogonRes.GetString();
				Socket.Send(LPCSTR(strRes), strlen(strRes));
				printf("Send: %s\n", LPCSTR(strRes));
			}
		}
		else if (nRecved > 26)
		{// 可能是短信数据包

			if (bLogon)
			{
				CMsgSMData MsgData;
				if (MsgData.SetString(CString(LPCSTR(szRecvBuff))))
				{// 数据包符合基本包格式

					printf(" Str: %s\n", LPCSTR(MsgData.GetString()));
					printf("Data:\n");
					printf("  DataContent -> %s\n", LPCTSTR(MsgData.m_strDataContent));
					printf("   DataFormat -> %s\n", LPCTSTR(MsgData.m_strDataFormat));
					printf("   DataLength -> %s\n", LPCTSTR(MsgData.m_strDataLength));
					printf("DisplaySPhone -> %s\n", LPCTSTR(MsgData.m_strDisplaySPhone));
					printf("     FeePhone -> %s\n", LPCTSTR(MsgData.m_strFeePhone));
					printf("      FeeUser -> %s\n", LPCTSTR(MsgData.m_strFeeUser));
					printf("       LinkID -> %s\n", LPCTSTR(MsgData.m_strLinkID));
					printf("     MsgCause -> %s\n", LPCTSTR(MsgData.m_strMsgCause));
					printf("       MsgLen -> %s\n", LPCTSTR(MsgData.m_strMsgLen));
					printf("      MsgType -> %s\n", LPCTSTR(MsgData.m_strMsgType));
					printf(" PhonesLength -> %s\n", LPCTSTR(MsgData.m_strPhonesLength));
					printf("       Phones -> %s\n", LPCTSTR(MsgData.m_strPhones));
					printf("     SendType -> %s\n", LPCTSTR(MsgData.m_strSendType));
					printf("     Sequence -> %s\n", LPCTSTR(MsgData.m_strSequence));
					printf("    ServiceID -> %s\n", LPCTSTR(MsgData.m_strServiceID));
					printf("         Time -> %s\n", LPCTSTR(MsgData.m_strTime));
					printf("     UserName -> %s\n", LPCTSTR(MsgData.m_strUserName));
					printf("       DataTP -> %s\n", LPCTSTR(MsgData.m_strDataTP));

					CMsgSMDataRes MsgSMDataRes;
					MsgSMDataRes.m_strResult = "1";
					CString strRes = MsgSMDataRes.GetString();
					Socket.Send(LPCSTR(strRes), strlen(strRes));
					printf("Send: %s\n", LPCSTR(strRes));
				}
				else
				{
					printf(" Err: Invalid SM data msg format.\n");
					CMsgSMDataRes MsgSMDataRes;
					MsgSMDataRes.m_strResult = "3";
					CString strRes = MsgSMDataRes.GetString();
					Socket.Send(LPCSTR(strRes), strlen(strRes));
					printf("Send: %s\n", LPCSTR(strRes));
				}
			}
			else
			{
				printf(" Err: Invalid user or not logon.\n");
				CMsgSMDataRes MsgSMDataRes;
				MsgSMDataRes.m_strResult = "4";
				CString strRes = MsgSMDataRes.GetString();
				Socket.Send(LPCSTR(strRes), strlen(strRes));
				printf("Send: %s\n", LPCSTR(strRes));
			}
		}
		else
		{
			printf(" Err: Invalid recv data. bytes(%d)\n", nRecved);
		}
		::memset(szRecvBuff, 0, MAX_SEND_BUFF);
		nRecved = _Receive(Socket, szRecvBuff, MAX_SEND_BUFF);
		puts("");
	}
}

void Service(void)
{
	if (!AfxSocketInit())
	{
		printf("Socket init failed.\n");
		return;
	}
	CSocket socketServer;
	CTimeoutSocket socketAccept;
	if (!socketServer.Create(SMST39_SERVER_PORT))
	{
		printf("CSocket create failed.\n");
		return;
	}
	if (!socketServer.Listen())
	{
		printf("CSocket listen failed.\n");
		return;
	}
	while(!::kbhit())
	{
		if (!socketServer.Accept(socketAccept))
		{
			printf("CSocket accept failed.\n");
			return;
		}
		printf("Accept a connection.\n");
		Process(socketAccept);
		socketAccept.Close();
	}
	getch();
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = ::atoi("1");

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		Service();
	}

	return nRetCode;
}


