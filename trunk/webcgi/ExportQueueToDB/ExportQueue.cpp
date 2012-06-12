// ExportQueue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "winsock2.h"
#include "svdbapi.h"
#include "windows.h"

#include "winsvc.h"

#define MAJOR_VERSION 1
#define MINOR_VERSION 2

SERVICE_STATUS          SVS_ServiceStatus; 
SERVICE_STATUS_HANDLE   SVS_ServiceStatusHandle;

DWORD SVS_ServiceInitialization(DWORD argc, LPTSTR *argv, DWORD *specificError);

void ServiceStart( DWORD dwArgc, LPTSTR *lpszArgv);

void  WINAPI SVS_ServiceCtrlHandler(DWORD opcode)
{
	switch(opcode)
	{
        case SERVICE_CONTROL_PAUSE: 
           SVS_ServiceStatus.dwCurrentState=SERVICE_PAUSED;
             break; 
 
        case SERVICE_CONTROL_CONTINUE: 
           SVS_ServiceStatus.dwCurrentState=SERVICE_RUNNING;
            break; 
 
        case SERVICE_CONTROL_STOP: 
		case SERVICE_CONTROL_SHUTDOWN:
            SVS_ServiceStatus.dwWin32ExitCode = 0; 
            SVS_ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
            SVS_ServiceStatus.dwCheckPoint    = 0; 
            SVS_ServiceStatus.dwWaitHint      = 0; 

            SetServiceStatus(SVS_ServiceStatusHandle, &SVS_ServiceStatus);
           
			
            return; 
 
        case SERVICE_CONTROL_INTERROGATE: 
        // Fall through to send current status. 
//			AddToErrorLog("Service Control Interrogate\r\n");
            break; 
 
        default:
			break;
    } 

    if (!SetServiceStatus (SVS_ServiceStatusHandle,  &SVS_ServiceStatus)) 
    { 
            return; 

    } 


}
void WINAPI SVS_ServiceStart(DWORD argc, LPTSTR *argv) 
{
	
	DWORD status=0;
	DWORD specificError=0;

    SVS_ServiceStatus.dwServiceType        = SERVICE_WIN32; 
    SVS_ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    SVS_ServiceStatus.dwControlsAccepted   =	SERVICE_ACCEPT_SHUTDOWN | 
												SERVICE_ACCEPT_STOP | 
												SERVICE_ACCEPT_PAUSE_CONTINUE; 
    SVS_ServiceStatus.dwWin32ExitCode      = 0; 
    SVS_ServiceStatus.dwServiceSpecificExitCode = 0; 
    SVS_ServiceStatus.dwCheckPoint         = 0; 
    SVS_ServiceStatus.dwWaitHint           = 0; 

	SVS_ServiceStatusHandle=::RegisterServiceCtrlHandler("VALIDATESERVER",SVS_ServiceCtrlHandler);
    if (SVS_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0) 
    { 
		return; 
    } 

    status = SVS_ServiceInitialization(argc,argv, &specificError); 
 
    // Handle error condition 
    if (status != NO_ERROR) 
    { 
        SVS_ServiceStatus.dwCurrentState       = SERVICE_STOPPED; 
        SVS_ServiceStatus.dwCheckPoint         = 0; 
        SVS_ServiceStatus.dwWaitHint           = 0; 
        SVS_ServiceStatus.dwWin32ExitCode      = status; 
        SVS_ServiceStatus.dwServiceSpecificExitCode = specificError; 
 
        SetServiceStatus (SVS_ServiceStatusHandle, &SVS_ServiceStatus); 

        return; 
    } 


    SVS_ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
    SVS_ServiceStatus.dwCheckPoint         = 0; 
    SVS_ServiceStatus.dwWaitHint           = 0; 
 
    if (!SetServiceStatus (SVS_ServiceStatusHandle, &SVS_ServiceStatus)) 
    { 
		return;
    }

	HANDLE m_handle=GetCurrentProcess();
	DWORD iPriority=GetPriorityClass(m_handle);
    SetPriorityClass(m_handle,HIGH_PRIORITY_CLASS);
    HANDLE m_thread=GetCurrentThread();
	SetThreadPriority(m_thread,THREAD_PRIORITY_ABOVE_NORMAL);

	ServiceStart(NULL, NULL);	
}
DWORD SVS_ServiceInitialization(DWORD argc, LPTSTR *argv, DWORD *specificError) 
{ 
    argv; 
    argc; 
    specificError; 
    return(0); 
}


BOOL InitSock()
{
	int Status;
	WORD wMajorVersion,wMinorVersion;
	WORD wVersionReqd;
	WSADATA lpmyWSAData;
	
	wMajorVersion = MAJOR_VERSION;
	wMinorVersion = MINOR_VERSION;
	wVersionReqd = MAKEWORD(wMajorVersion,wMinorVersion);

	Status = WSAStartup(wVersionReqd,&lpmyWSAData);	
	if (Status != 0)
		return FALSE;
	 
	return TRUE;
}

BOOL ConnectSock(char * strAddr)
{
	struct sockaddr_in addr;
	addr.sin_family=PF_INET;
	addr.sin_port=htons(8600);
	addr.sin_addr.s_addr=inet_addr(strAddr);

	SOCKET clientSock=socket(AF_INET,SOCK_STREAM,0);
	int msg=connect(clientSock,(struct sockaddr*)&addr,sizeof(addr));
	if(msg!=0)
	{
		return false;
	}
	closesocket(clientSock);
	return true;

}
void ServiceStart( DWORD dwArgc, LPTSTR *lpszArgv)
{
	bool bStop = false;

	InitSock();

	OutputDebugString("--------------receive queue message servicestart call-----------\n");
	while(!bStop)
	{
		//::Sleep(50);

		MQRECORD mrd;

		//获取ExportQueue队列中的
		mrd=::BlockPopMessage("SiteView70-DBRecordTrack");

		
		if(mrd!=INVALID_VALUE)
		{
			string label;
			svutil::TTime ct;
			unsigned int len=0;

			if(!::GetMessageData(mrd, label, ct, NULL, len))
			{
				OutputDebugString("Get message data failed");
			}

			char * buf = NULL;
			buf = new char[len];

			if(!::GetMessageData(mrd, label, ct, buf, len))
			{
				OutputDebugString("Get message data failed");
			}			
			
			::CloseMQRecord(mrd);
						
			if(!label.empty())
			{				
				bool bRet = true;
				string strAddr = GetMasterAddress();
				int i = 0;
				if(!(bRet = AppendRecord(label, buf, len, "default", strAddr)))				
				{
					bool bRet1 = false;
					while(!(bRet1 = ConnectSock((char*)strAddr.c_str())))
					{
						OutputDebugString("-------------connect failure-------------------\n");
						puts("-------------connect failure-------------------\n");
						Sleep(60000);
					}

					if(bRet1)
					{
						bRet = AppendRecord(label, buf, len, "default", strAddr);						
					}										
				}
				if(bRet)
				{
					OutputDebugString("------------Append Record To Master Database-------------\n");
					OutputDebugString(label.c_str());
					OutputDebugString("\n");

					puts("--------------Append Record To Master Database--------------\n");
					puts(label.c_str());
					puts("\n");
				}
				else
				{
					OutputDebugString("--------------connect success and Append Record To Master Database failure--------------\n");					
					OutputDebugString(label.c_str());
					OutputDebugString("\n");

					puts("--------------connect success and Append Record To Master Database failure--------------\n");					
				}
				
								
			}
			
			
			if(buf != NULL)
				delete buf;
		}
		else
		{			
			Sleep(60000);			
			continue;
		}

	}
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
    	return nRetCode;
	}


    SERVICE_TABLE_ENTRY ste[] = 
	{
		{"MonitorContrl",	SVS_ServiceStart}, 
		{ NULL,			NULL			} 
	}; 

	::StartServiceCtrlDispatcher(ste);


	return nRetCode;
}

