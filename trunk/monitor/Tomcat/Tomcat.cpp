// Tomcat.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Tomcat.h"
#include "..\..\base\Base64.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

//--------------------------------------------------written by chenxingang
#define ERROR_WINHTTP_AUTO_PROXY_SERVICE_ERROR					12178
#define ERROR_WINHTTP_AUTODETECTION_FAILED						12180
#define ERROR_WINHTTP_BAD_AUTO_PROXY_SCRIPT						12166
#define ERROR_WINHTTP_CANNOT_CALL_AFTER_OPEN					12103
#define ERROR_WINHTTP_CANNOT_CALL_AFTER_SEND					12102
#define ERROR_WINHTTP_CANNOT_CALL_BEFORE_OPEN					12100
#define ERROR_WINHTTP_CANNOT_CALL_BEFORE_SEND					12101
#define ERROR_WINHTTP_CANNOT_CONNECT							12029
#define ERROR_WINHTTP_CHUNKED_ENCODING_HEADER_SIZE_OVERFLOW		12183
#define ERROR_WINHTTP_CLIENT_AUTH_CERT_NEEDED					12044
#define ERROR_WINHTTP_CONNECTION_ERROR							12030
#define ERROR_WINHTTP_HEADER_ALREADY_EXISTS						12155
#define ERROR_WINHTTP_HEADER_COUNT_EXCEEDED						12181
#define ERROR_WINHTTP_HEADER_NOT_FOUND							12150
#define ERROR_WINHTTP_HEADER_SIZE_OVERFLOW						12182
#define ERROR_WINHTTP_INCORRECT_HANDLE_STATE					12019
#define ERROR_WINHTTP_INCORRECT_HANDLE_TYPE						12018
#define ERROR_WINHTTP_INTERNAL_ERROR							12004
#define ERROR_WINHTTP_INVALID_OPTION							12009
#define ERROR_WINHTTP_INVALID_QUERY_REQUEST						12154
#define ERROR_WINHTTP_INVALID_SERVER_RESPONSE					12152
#define ERROR_WINHTTP_INVALID_URL								12005
#define ERROR_WINHTTP_LOGIN_FAILURE								12015
#define ERROR_WINHTTP_NAME_NOT_RESOLVED							12007
#define ERROR_WINHTTP_NOT_INITIALIZED							12172
#define ERROR_WINHTTP_OPERATION_CANCELLED						12017
#define ERROR_WINHTTP_OPTION_NOT_SETTABLE						12011
#define ERROR_WINHTTP_OUT_OF_HANDLES							12001
#define ERROR_WINHTTP_REDIRECT_FAILED							12156
#define ERROR_WINHTTP_RESEND_REQUEST							12032
#define ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW					12184
#define ERROR_WINHTTP_SECURE_CERT_CN_INVALID					12038
#define ERROR_WINHTTP_SECURE_CERT_DATE_INVALID					12037
#define ERROR_WINHTTP_SECURE_CERT_REV_FAILED					12057
#define ERROR_WINHTTP_SECURE_CERT_REVOKED						12170
#define ERROR_WINHTTP_SECURE_CERT_WRONG_USAGE					12179
#define ERROR_WINHTTP_SECURE_CHANNEL_ERROR						12157
#define ERROR_WINHTTP_SECURE_FAILURE							12175
#define ERROR_WINHTTP_SECURE_INVALID_CA							12045
#define ERROR_WINHTTP_SECURE_INVALID_CERT						12169
#define ERROR_WINHTTP_SHUTDOWN									12012
#define ERROR_WINHTTP_TIMEOUT									12002
#define ERROR_WINHTTP_UNABLE_TO_DOWNLOAD_SCRIPT					12167
#define ERROR_WINHTTP_UNRECOGNIZED_SCHEME						12006
//--------------------------------------------------written by chenxingang

#define		__MACHINETYPE__					"_MachineType="
#define		__OSTYPE__						"_OsType="
#define		__MACHINENAME__					"_MachineName="
#define		__USERACCOUNT__					"_URLUserAccount="
#define		__PASSWORD__					"_URLPassWord="
#define		__PROMPT__						"_Prompt="
#define		__LOGINPROMPT__					"_LoginPrompt="
#define		__PASSWORDPROMPT__				"_PWPrompt="
#define		__PROTOCOLTYPE__				"_ProtocolType="
#define		__SERVERPORT__					"_ServerPort="
#define		__DOWNLOADFILE__				"_DownLoadFile="
#define		__TIMEOUT__						"_TimeOut="
#define		__PORT__						"_Port="
#define		__SENDSTR__						"_SendStr="
#define		__MATCHSTR__					"_MatchStr="
#define		__DSNNAME__						"_DsnName="
#define		__SQLSTR__						"_SqlStr="
#define		__REQUIREID__					"_RequireID="
#define		__COMMUNITY__					"_Community="
#define		__DOMAINNAME__					"_DomName="
#define		__MATCHIP__						"_MatchIP="
#define		__DIRECTORY__					"_Directory="
#define		__ISSUBDIR__					"_IsSubDir="
#define		__FILEPATH__					"_FilePath="
#define		__SERVICE__						"_Service="
#define		__DISK__						"_Disk="
#define		__SERVERMANURL__				"_ServerManUrl="
#define		__SENDBYTES__					"_SendBytes="
#define		__CPUNUM__						"_CpuNum="
#define		__DETAIL__						"_Detail="
#define		__TRACE__						"_Trace="

#define		__PROXYSERVERPORT__				"_ProxyServerPort="
#define		__PROXYUSERNAME__				"_ProxyUser="
#define		__PROXYPASSWORD__				"_ProxyPass="
#define		__RETRYDELAY__					"_RetryDelay="
#define		__CONNECTTIMEOUT__				"_ConnTimeout="
#define		__QUERYTIMEOUT__				"_QueryTimeout="
#define		__PASSIVEMODE__					"_PassiveMode="
#define		__PROVIDER__					"_Provider="
#define		__PRINCIPAL__					"_Principal="
#define		__CREDENTIALS__					"_Credentials="
#define		__QUERY__						"_Query="
#define		__FILTER__						"_Filter="
#define		__SMTPSERVERPORT__				"_SmtpServPort="
#define		__RCPTSERVERPORT__				"_RcptServPort="
#define		__MAILTYPE__					"_MailType="
#define		__MAILPROTOCOLTYPE__			"_MailProtocolType="
#define		__RCPTADDRESS__					"_RcptAddress="
#define		__CHECKDELAY__					"_CheckDelay="
#define		__ATTACHMENT__					"_Attachment="
#define		__SECRET__						"_Secret="
#define		__INDEX__						"_Index="
#define		__INTERFACEINDEX__				"_InterfaceIndex="
#define		__GROUP__						"_Group="
#define		__CONNECTADDRESS__				"_ConnAddr="
#define		__URL__							"_URL="
#define		__STOPTIME__					"_StopTime="
#define		__PROXYTYPE__					"_ProxyType="
#define		__POSTDATA__					"_PostData="

#define		__GROUPID__						"_GroupID="  // xiao quan
#define		__MONITORID__					"_MonitorID="// xiao quan
#define		__CUSTOMER__					"_CustomerPath="// xiao quan
/////////////////////////////////////////////////////////////////////////////
// CTomcatApp

BEGIN_MESSAGE_MAP(CTomcatApp, CWinApp)
	//{{AFX_MSG_MAP(CTomcatApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTomcatApp construction

CTomcatApp::CTomcatApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTomcatApp object

CTomcatApp theApp;


typedef struct 
{
   CString strServerName;
   CString strUser;
   CString strPass;
   CString strContentType;
   CString strPost;
   CString strProxyUsername;
   CString strProxyPassword;
   CString strObject;
   int nPort;
   BOOL bResult;
   HINTERNET   hConn;
   HINTERNET   hInet;
   HINTERNET	hHttpReq;

} PARM;
//////////////////////////////////////////////////////////////////////////////////
int GetSessionCount(CString strContent);
CString GetErrorMessage(DWORD dwError);
DWORD WINAPI WorkerConnectFunction( LPVOID ); 
DWORD WINAPI WorkerSendRequstFunction( LPVOID ); 
//////////////////////////////////////////////////////////////////////////////////
//extern "C" __declspec(dllexport) BOOL INET(CStringList &paramList, char *szReturn)
extern "C" __declspec(dllexport) BOOL INET(char *param, char *szReturn, int & nSize)
{
	CStringList paramList;
	MakeStringListByChar(paramList, param);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bRet = FALSE;
	CString strPath = ::FuncGetInstallRootPath();//Siteview安装路径
	if (strPath.IsEmpty())//注册表被损坏或者没有安装Siteview
		return bRet;//函数掉用失败

	CString	strURL = _T(""),				// URL
			strPostData = _T(""),			// Post Data
			strUsername = _T(""),			// Authorization User Name
			strPassword = _T(""),			// Authorization Password
			strProxyServer = _T(""),		// HTTP代理服务器
			strProxyUsername = _T(""),		// 代理服务器用户
			strProxyPassword = _T(""),		// 代理服务器访问密码
			strMatchContent = _T("");		// Match Content
	CString strProxyPort = _T("");//代理端口
	CString strCustomer = _T("");

	DWORD dwError=0;
	CString strError=_T("");
	DWORD dwStart = ::GetTickCount();

	int		nTimeout = 60, 
			nGID = 0, 
			nMID = 0;

	POSITION pos = paramList.FindIndex(0);
    //得到各个参数
	while(pos)
	{
		CString strTemp = paramList.GetNext(pos);
		if(strTemp.Find(__URL__, 0) == 0)
		{//URL
			strURL = strTemp.Right(strTemp.GetLength() - strlen(__URL__));
		}
		else if(strTemp.Find(__POSTDATA__, 0) == 0)
		{//Post Data
			strPostData = strTemp.Right(strTemp.GetLength() - strlen(__POSTDATA__));
		}
		else if(strTemp.Find(__USERACCOUNT__, 0) == 0)
		{//Authorization User Name
			strUsername = strTemp.Right(strTemp.GetLength() - strlen(__USERACCOUNT__));
		}
		else if(strTemp.Find(__PASSWORD__, 0) == 0)
		{//Authorization Password
			strPassword = strTemp.Right(strTemp.GetLength() - strlen(__PASSWORD__));
		}
		else if(strTemp.Find(__PROXYSERVERPORT__, 0) == 0)
		{//Proxy Server Port
			strTemp.Delete(0, strlen(__PROXYSERVERPORT__));
			int index = strTemp.Find(':', 0);
			if(index >= 0)
			{
				strProxyServer = strTemp.Left(index);//Proxy Server
				strTemp.Delete(0, index + 1);
				strProxyPort = strTemp;//Proxy Port			
			}
			else
			{
				strProxyServer = strTemp;//Proxy Server
			}
		}
		else if(strTemp.Find(__PROXYUSERNAME__, 0) == 0)
		{//Proxy User Name
			strProxyUsername = strTemp.Right(strTemp.GetLength() - strlen(__PROXYUSERNAME__));
		}
		else if(strTemp.Find(__PROXYPASSWORD__, 0) == 0)
		{//Proxy User Pwd
			strProxyPassword = strTemp.Right(strTemp.GetLength() - strlen(__PROXYPASSWORD__));
		}
		else if(strTemp.Find(__TIMEOUT__, 0) == 0)
		{//Time Out
			nTimeout = atoi(strTemp.Right(strTemp.GetLength() - strlen(__TIMEOUT__)));
		}
		else if(strTemp.Find(__MATCHSTR__, 0) == 0)
		{//Match String
			strMatchContent = strTemp.Right(strTemp.GetLength() - strlen(__MATCHSTR__));
		}
		else if(strTemp.Find(__GROUPID__, 0) == 0)
		{//Group ID
			nGID = atoi(strTemp.Right(strTemp.GetLength() - strlen(__GROUPID__)));
		}
		else if(strTemp.Find(__MONITORID__, 0) == 0)
		{//Monitor ID
			nMID = atoi(strTemp.Right(strTemp.GetLength() - strlen(__MONITORID__)));
		}
		else if(strTemp.Find(__CUSTOMER__, 0) == 0)
		{//Customer
			strCustomer = strTemp.Right(strTemp.GetLength() - strlen(__CUSTOMER__));
		}
	}



	if(strURL.IsEmpty()) 
    {//Url is Empty
		sprintf(szReturn, "error=%s$", FuncGetStringFromIDS("SV_URL",
            "URL_LOST_ADDRESS"));	//<%IDS_UrlMonitor_1%>"error=缺少URL$"
		return bRet;//Return False
	}

	CString strServerName;
	CString strObject;
	INTERNET_PORT nPort;
	DWORD dwServiceType;
    //分割URL
	if (!AfxParseURL(strURL, dwServiceType, strServerName, strObject, nPort) ||
		dwServiceType != INTERNET_SERVICE_HTTP)
	{//分割失败
		sprintf(szReturn,"error=Parse URL failed$");
		return FALSE;
	}

	HINTERNET	hInet;
	HINTERNET	hConn;//Http Connect Handle
	HINTERNET	hHttpReq;//Http Request Handle     

	CString strProxy = _T("");
	if (!strProxyServer.IsEmpty())//Proxy Server Is Not Empty
    {
		if (!strProxyPort.IsEmpty())//Proxy Server Port Is Not Empty
			strProxy.Format("%s:%s", strProxyServer, strProxyPort);
        else//Proxy Server Port Is Empty
	        strProxy.Format("%s",strProxyServer);
    }

	if(!strProxy.IsEmpty())
    { 
        //Proxy Server String is Not Empty ,Then Open InterNet By Generic 
        //Mode whith Proxy
		hInet = InternetOpen("http generic", INTERNET_OPEN_TYPE_PROXY , strProxy, 
							"<local>", 1);
    }
    else
    {
        //Proxy Server String is Empty ,Then Open InterNet By Generic 
        //Mode whithout Proxy
		hInet = InternetOpen("http generic", 0, NULL, NULL, 1);
    }

	if(!hInet)
	{//Open Internet Faild
		sprintf(szReturn,"error=Internet Open failed$");
		return FALSE;//Return Faild
	}

   PARM    threadParm;	
   HANDLE   hThread; 
   DWORD    dwThreadID;
   threadParm.strServerName = strServerName;
   threadParm.strUser = strUsername;
   threadParm.strPass = strPassword;
   threadParm.nPort = nPort;
   threadParm.hInet=hInet;
   threadParm.strPost=  strPostData;
   threadParm.strProxyPassword=strProxyPassword;
   threadParm.strProxyUsername=strProxyUsername;
   threadParm.strObject =strObject;

   hThread = CreateThread(
         NULL,            // Pointer to thread security attributes 
         0,               // Initial thread stack size, in bytes 
         WorkerConnectFunction,  // Pointer to thread function 
         &threadParm,     // The argument for the new thread
         0,               // Creation flags 
         &dwThreadID      // Pointer to returned thread identifier 
     );    

   // Wait for the call to InternetConnect in worker function to complete
   int dwTimeout = 5000; // in milliseconds
   if ( WaitForSingleObject ( hThread, dwTimeout ) == WAIT_TIMEOUT )
   {       
       if ( threadParm.hInet )
			InternetCloseHandle ( threadParm.hInet );
		TerminateThread(hThread, 0);       
       return FALSE;
   }

   // The state of the specified object (thread) is signaled
	unsigned long dwExitCode = 0;
	if ( !GetExitCodeThread( hThread, &dwExitCode ) )
	{
	   return FALSE;
	}
	TerminateThread(hThread, 0);
	if ( dwExitCode )
	  return FALSE;

	hConn=threadParm.hConn;
	if(!hConn)
	{//连接失败
		dwError=::GetLastError();//得到最后一次错误
        strError=::GetErrorMessage(dwError);//得到错误信息
		sprintf(szReturn,"error=InternetConnect:%s$",strError);
		InternetCloseHandle(hInet);//关闭句柄
		return FALSE;//Faild
	}

	CString strPost = strPostData;
	if(strPost.IsEmpty())//Post Data is Empty, Open Request By Get Mode
		hHttpReq = HttpOpenRequest(hConn, "GET", strObject, "HTTP/1.0", NULL, 0, 
								INTERNET_FLAG_RELOAD, 0);
	else//Post Data is not Empty , Open Request By POST Mode
		hHttpReq = HttpOpenRequest(hConn, "POST", strObject, "HTTP/1.0", NULL, 0, 
								INTERNET_FLAG_RELOAD, 0);

	

	if(hHttpReq)
	{//Open HTTP Request Successed
		
		DWORD ms;
		DWORD mslength;
		ms =120000;
		mslength=4;
		::InternetQueryOption(hHttpReq,INTERNET_OPTION_RECEIVE_TIMEOUT,&ms,&mslength);
		ms =2000;
		::InternetSetOption(hHttpReq,INTERNET_OPTION_RECEIVE_TIMEOUT,&ms,sizeof(ms));
		::InternetQueryOption(hHttpReq,INTERNET_OPTION_RECEIVE_TIMEOUT,&ms,&mslength);

		::InternetQueryOption(hHttpReq,INTERNET_OPTION_SEND_TIMEOUT,&ms,&mslength);
		ms =120000;
		::InternetSetOption(hHttpReq,INTERNET_OPTION_SEND_TIMEOUT,&ms,sizeof(ms));
		::InternetQueryOption(hHttpReq,INTERNET_OPTION_SEND_TIMEOUT,&ms,&mslength);

		BOOL bResult = FALSE;
		CString strContentType = _T("Content-Type: application/x-www-form-urlencoded");

		CString strProxyUser = strProxyUsername;//代理用户名
		CString strProxyPass = strProxyPassword;//代理密码
		if(!strProxyUser.IsEmpty())
		{//代理用户名不为空
			CString	strUserPass = _T("");
			strUserPass.Format("%s:%s", strProxyUser, strProxyPass);
			CString	strOutput = _T("Proxy-Authorization: Basic ");//代理服务器验证
			CBase64	*pBase64 = new CBase64();
            //加密用户名和密码
			strOutput.Insert(strOutput.GetLength(), pBase64->Encode(strUserPass, strUserPass.GetLength()));
			delete pBase64;
			pBase64 = NULL;			
			strOutput += _T("\r\n");
            //增加Http头内容
			if(!HttpAddRequestHeaders(hHttpReq, strOutput, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE))
			{//失败
				dwError=::GetLastError();//Get Last Error
				strError=::GetErrorMessage(dwError);//Get Error Message
				sprintf(szReturn,"error=InternetConnect:%s$",strError);
				InternetCloseHandle(hHttpReq);//Close Request Handle
				InternetCloseHandle(hConn);//Close Connection Handle
				InternetCloseHandle(hInet);//Close Internet Handle
				return FALSE;//Failed
			}				
		}
		int nTime=0;
LOOP://循环调用
#if 0
		InternetCloseHandle(hHttpReq);
		bResult=SendInetReqeust(threadParm,szReturn );
		hHttpReq =threadParm.hHttpReq;
#else
		if(strPost.IsEmpty())//Post Data Is Empty
			bResult = HttpSendRequest(hHttpReq, NULL, 0, NULL, 0);
		else
			bResult = HttpSendRequest(hHttpReq, strContentType, strContentType.GetLength(), 
									(void *)(LPCTSTR)strPost, strPost.GetLength());
#endif 
		
		if(bResult)
		{
			char	sBuffer[1024]={0};
			DWORD	lBuffer = 1024;
			int nStatusCode = 0;
			int nPageSize = 0;
            //Query Request Information(状态码)
			if(!HttpQueryInfo(hHttpReq, HTTP_QUERY_STATUS_CODE, &sBuffer, &lBuffer, 
							NULL))
			{//Failed
				dwError=::GetLastError();//Get Last Error
				strError=::GetErrorMessage(dwError);//Get Error Message
				sprintf(szReturn,"error=HttpQueryInfo:%s$",strError);
				InternetCloseHandle(hHttpReq);//Close Request Handle
				InternetCloseHandle(hConn);//Close Connection Handle
				InternetCloseHandle(hInet);//Close Internet handle
				return FALSE;//Failed
			}
			else
			{
				nStatusCode = atoi(sBuffer);//状态码
			}

			memset(sBuffer, 0, 1024);//Set Memory Data
			lBuffer = 1023;
			BOOL bRead = FALSE;
			DWORD lbegin = 0;
            CString strRecv = _T("");
            //Read Http Content Form Request
			bRead =InternetReadFile(hHttpReq,  sBuffer, lBuffer, &lbegin);
			while(TRUE == bRead) 
            {//Read All Http Request File
				if((0 == lbegin)&&(TRUE == bRead)) 
					break;					
				sBuffer[lbegin] = '\0';
                strRecv += sBuffer;
				nPageSize += lbegin;					
				bRead = InternetReadFile(hHttpReq, sBuffer, lBuffer, &lbegin);
			}			
			CString str = _T("");			
			DWORD dwEnd = ::GetTickCount();	
            nStatusCode = GetSessionCount(strRecv);
			str.Format("rootNum=%d$totaltime=%.2f$downloadsize=%d$", nStatusCode, (dwEnd - dwStart)*1.0/1000, nPageSize);
			
            if (strMatchContent.IsEmpty()) 
            {//Match String is Empty
				strcpy(szReturn, (LPCTSTR)str);
			}
			else 
            {
                if(strRecv.Find(strMatchContent,0) >= -1)
                {//Match Content Successed
                    sprintf(szReturn, "error=%s$", FuncGetStringFromIDS("<%IDS_UrlMonitor_2%>"));//<%IDS_UrlMonitor_2%>"error=匹配失败$"
                }
                else
                {//Match Content Failed
                    sprintf(szReturn, (LPCTSTR)str);
                }
			}            
		}
		else
		{
			dwError=::GetLastError();//Get Last Error
			if(nTime<5)
			{//循环次数小于5
				nTime++;//增加次数
                Sleep(3000);//休眠3秒
				goto LOOP;//循环
			}
            strError=::GetErrorMessage(dwError);
			sprintf(szReturn,"error=HttpSendRequest:%s$",strError);
			InternetCloseHandle(hHttpReq);//Close Requst Handle
			InternetCloseHandle(hConn);//Close Connection Handle
			InternetCloseHandle(hInet);//Close Internet Handle
			hHttpReq = NULL;//Set Request Handle as NULL
			hConn = NULL;//Set Connction Handle as NULL
			hInet = NULL;//Set Internet Handle as NULL
			return FALSE;// Return Failed
		}
	}
	else
	{
		dwError=::GetLastError();
        strError=::GetErrorMessage(dwError);
		sprintf(szReturn,"error=HttpOpenRequest:%s$",strError);
		InternetCloseHandle(hConn);//Close Connection Handle
		InternetCloseHandle(hInet);//Close Internet Handle
		return FALSE;
	}
	InternetCloseHandle(hHttpReq);//Close Requst Handle
	InternetCloseHandle(hConn);//Close Connection Handle
	InternetCloseHandle(hInet);//Close Internet Handle

	CString tempstr = szReturn;
	MakeCharByString(szReturn, nSize, tempstr);
    return TRUE;
}

DWORD WINAPI WorkerConnectFunction(IN LPVOID vThreadParm)
{
	PARM* pThreadParm;
    // Initialize local pointer to void pointer passed to thread
    pThreadParm = (PARM*)vThreadParm;
	if(!(pThreadParm->strUser.IsEmpty()))
		pThreadParm->hConn = InternetConnect(pThreadParm->hInet, 
				pThreadParm->strServerName, pThreadParm->nPort, 
				pThreadParm->strUser, pThreadParm->strPass, 
				INTERNET_SERVICE_HTTP , 0, 0);
	else
		pThreadParm->hConn = InternetConnect(pThreadParm->hInet, 
								pThreadParm->strServerName, pThreadParm->nPort,
								NULL, NULL, 
								INTERNET_SERVICE_HTTP , 0, 0);

	char buf[256];

	sprintf(buf, "server name:%s port:%d user:%s passward:%s", pThreadParm->strServerName, pThreadParm->nPort,
		pThreadParm->strUser, pThreadParm->strPass);
	

	//::ExitThread(0);
	return 0;
}

CString GetErrorMessage(DWORD dwError)
{
	CString strError=_T("");

	switch(dwError)
	{
	case    ERROR_WINHTTP_AUTO_PROXY_SERVICE_ERROR:
		return "ERROR_WINHTTP_AUTO_PROXY_SERVICE_ERROR";
	case	ERROR_WINHTTP_AUTODETECTION_FAILED:
		return "ERROR_WINHTTP_AUTODETECTION_FAILED";
	case	ERROR_WINHTTP_BAD_AUTO_PROXY_SCRIPT:
		return "ERROR_WINHTTP_BAD_AUTO_PROXY_SCRIPT";
	case	ERROR_WINHTTP_CANNOT_CALL_AFTER_OPEN:				
		return "ERROR_WINHTTP_CANNOT_CALL_AFTER_OPEN";
	case	ERROR_WINHTTP_CANNOT_CALL_AFTER_SEND:				
		return "ERROR_WINHTTP_CANNOT_CALL_AFTER_SEND";
	case	ERROR_WINHTTP_CANNOT_CALL_BEFORE_OPEN:				
		return "ERROR_WINHTTP_CANNOT_CALL_BEFORE_OPEN";
	case	ERROR_WINHTTP_CANNOT_CALL_BEFORE_SEND:				
		return "ERROR_WINHTTP_CANNOT_CALL_BEFORE_SEND";
	case	ERROR_WINHTTP_CANNOT_CONNECT:					
		return "ERROR_WINHTTP_CANNOT_CONNECT";
	case	ERROR_WINHTTP_CHUNKED_ENCODING_HEADER_SIZE_OVERFLOW:
		return "ERROR_WINHTTP_CHUNKED_ENCODING_HEADER_SIZE_OVERFLOW";
	case	ERROR_WINHTTP_CLIENT_AUTH_CERT_NEEDED:	
		return "ERROR_WINHTTP_CLIENT_AUTH_CERT_NEEDED";
	case	ERROR_WINHTTP_CONNECTION_ERROR:					
		return "ERROR_WINHTTP_CONNECTION_ERROR";
	case	ERROR_WINHTTP_HEADER_ALREADY_EXISTS:
		return "ERROR_WINHTTP_HEADER_ALREADY_EXISTS";
	case	ERROR_WINHTTP_HEADER_COUNT_EXCEEDED:					
		return "ERROR_WINHTTP_HEADER_COUNT_EXCEEDED";
	case	ERROR_WINHTTP_HEADER_NOT_FOUND:					
		return "ERROR_WINHTTP_HEADER_NOT_FOUND";
	case	ERROR_WINHTTP_HEADER_SIZE_OVERFLOW:
		return "ERROR_WINHTTP_HEADER_SIZE_OVERFLOW";
	case	ERROR_WINHTTP_INCORRECT_HANDLE_STATE:
		return "ERROR_WINHTTP_INCORRECT_HANDLE_STATE";
	case	ERROR_WINHTTP_INCORRECT_HANDLE_TYPE:					
		return "ERROR_WINHTTP_INCORRECT_HANDLE_TYPE";
	case	ERROR_WINHTTP_INTERNAL_ERROR:					
		return "ERROR_WINHTTP_INTERNAL_ERROR";
	case	ERROR_WINHTTP_INVALID_OPTION:
		return "ERROR_WINHTTP_INVALID_OPTION";
	case	ERROR_WINHTTP_INVALID_QUERY_REQUEST:
		return "ERROR_WINHTTP_INVALID_QUERY_REQUEST";
	case	ERROR_WINHTTP_INVALID_SERVER_RESPONSE:
		return "ERROR_WINHTTP_INVALID_SERVER_RESPONSE";
	case	ERROR_WINHTTP_INVALID_URL:					
		return "ERROR_WINHTTP_INVALID_URL";
	case	ERROR_WINHTTP_LOGIN_FAILURE:							
		return "ERROR_WINHTTP_LOGIN_FAILURE";
	case	ERROR_WINHTTP_NAME_NOT_RESOLVED:
		return "ERROR_WINHTTP_NAME_NOT_RESOLVED";
	case	ERROR_WINHTTP_NOT_INITIALIZED:
		return "ERROR_WINHTTP_NOT_INITIALIZED";
	case	ERROR_WINHTTP_OPERATION_CANCELLED:
		return "ERROR_WINHTTP_OPERATION_CANCELLED";
	case	ERROR_WINHTTP_OPTION_NOT_SETTABLE:
		return "ERROR_WINHTTP_OPTION_NOT_SETTABLE";
	case	ERROR_WINHTTP_OUT_OF_HANDLES:						
		return "ERROR_WINHTTP_OUT_OF_HANDLES";
	case	ERROR_WINHTTP_REDIRECT_FAILED:
		return "ERROR_WINHTTP_REDIRECT_FAILED";
	case	ERROR_WINHTTP_RESEND_REQUEST:
		return "ERROR_WINHTTP_RESEND_REQUEST";
	case	ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW:
		return "ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW";
	case	ERROR_WINHTTP_SECURE_CERT_CN_INVALID:				
		return "ERROR_WINHTTP_SECURE_CERT_CN_INVALID";
	case	ERROR_WINHTTP_SECURE_CERT_DATE_INVALID:				
		return "ERROR_WINHTTP_SECURE_CERT_DATE_INVALID";
	case	ERROR_WINHTTP_SECURE_CERT_REV_FAILED:				
		return "ERROR_WINHTTP_SECURE_CERT_REV_FAILED";
	case	ERROR_WINHTTP_SECURE_CERT_REVOKED:					
		return "ERROR_WINHTTP_SECURE_CERT_REVOKED";
	case	ERROR_WINHTTP_SECURE_CERT_WRONG_USAGE:				
		return "ERROR_WINHTTP_SECURE_CERT_WRONG_USAGE";
	case	ERROR_WINHTTP_SECURE_CHANNEL_ERROR:					
		return "ERROR_WINHTTP_SECURE_CHANNEL_ERROR";
	case	ERROR_WINHTTP_SECURE_FAILURE:						
		return "ERROR_WINHTTP_SECURE_FAILURE";
	case	ERROR_WINHTTP_SECURE_INVALID_CA:						
		return "ERROR_WINHTTP_SECURE_INVALID_CA";
	case	ERROR_WINHTTP_SECURE_INVALID_CERT:					
		return "ERROR_WINHTTP_SECURE_INVALID_CERT";
	case	ERROR_WINHTTP_SHUTDOWN:						
		return "ERROR_WINHTTP_SHUTDOWN";
	case	ERROR_WINHTTP_TIMEOUT:								
		return "ERROR_WINHTTP_TIMEOUT";
	case	ERROR_WINHTTP_UNABLE_TO_DOWNLOAD_SCRIPT:
		return "ERROR_WINHTTP_UNABLE_TO_DOWNLOAD_SCRIPT";
	case	ERROR_WINHTTP_UNRECOGNIZED_SCHEME:				
		return "ERROR_WINHTTP_UNRECOGNIZED_SCHEME";
	default:
		return "ERROR_OTHERERROR";
	}
	return strError;	
}

int GetSessionCount(CString strContent)
{
    int nIndex = 0;
    int nCount = 0;
    CString strFind = "<a href=\"/manager/html/sessions?path=/";
    while (nIndex != -1)
    {
        nIndex = strContent.Find(strFind , nIndex);

        if(nIndex != -1)
        {
            nIndex = strContent.Find(">", nIndex) + 1;
            CString strTemp = strContent.Right(strContent.GetLength()-nIndex);
            int nIndexTemp = strTemp.Find("<");
            nCount += atoi(strTemp.Left(nIndexTemp));
            nIndex += nIndexTemp;
        }
        else
        {
            break;
        }
    }
    return nCount;
}

//extern "C" __declspec(dllexport) BOOL WTC(CStringList &paramList, char *szReturn)
extern "C" __declspec(dllexport) BOOL WTC(char *param, char *szReturn, int & nSize)
{
	CStringList paramList;
	MakeStringListByChar(paramList, param);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bRet = FALSE;
	CString strPath = ::FuncGetInstallRootPath();//Siteview安装路径
	if (strPath.IsEmpty())//注册表被损坏或者没有安装Siteview
		return bRet;//函数掉用失败

	CString	strURL = _T(""),				// URL
			strPostData = _T(""),			// Post Data
			strUsername = _T(""),			// Authorization User Name
			strPassword = _T(""),			// Authorization Password
			strProxyServer = _T(""),		// HTTP代理服务器
			strProxyUsername = _T(""),		// 代理服务器用户
			strProxyPassword = _T(""),		// 代理服务器访问密码
			strMatchContent = _T("");		// Match Content
	CString strProxyPort = _T("");//代理端口
	CString strCustomer = _T("");

	DWORD dwError=0;
	CString strError=_T("");
	DWORD dwStart = ::GetTickCount();

	int		nTimeout = 60, 
			nGID = 0, 
			nMID = 0;

	POSITION pos = paramList.FindIndex(0);
    //得到各个参数
	while(pos)
	{
		CString strTemp = paramList.GetNext(pos);
		if(strTemp.Find(__URL__, 0) == 0)
		{//URL
			strURL = strTemp.Right(strTemp.GetLength() - strlen(__URL__));
		}
		else if(strTemp.Find(__POSTDATA__, 0) == 0)
		{//Post Data
			strPostData = strTemp.Right(strTemp.GetLength() - strlen(__POSTDATA__));
		}
		else if(strTemp.Find(__USERACCOUNT__, 0) == 0)
		{//Authorization User Name
			strUsername = strTemp.Right(strTemp.GetLength() - strlen(__USERACCOUNT__));
		}
		else if(strTemp.Find(__PASSWORD__, 0) == 0)
		{//Authorization Password
			strPassword = strTemp.Right(strTemp.GetLength() - strlen(__PASSWORD__));
		}
		else if(strTemp.Find(__PROXYSERVERPORT__, 0) == 0)
		{//Proxy Server Port
			strTemp.Delete(0, strlen(__PROXYSERVERPORT__));
			int index = strTemp.Find(':', 0);
			if(index >= 0)
			{
				strProxyServer = strTemp.Left(index);//Proxy Server
				strTemp.Delete(0, index + 1);
				strProxyPort = strTemp;//Proxy Port			
			}
			else
			{
				strProxyServer = strTemp;//Proxy Server
			}
		}
		else if(strTemp.Find(__PROXYUSERNAME__, 0) == 0)
		{//Proxy User Name
			strProxyUsername = strTemp.Right(strTemp.GetLength() - strlen(__PROXYUSERNAME__));
		}
		else if(strTemp.Find(__PROXYPASSWORD__, 0) == 0)
		{//Proxy User Pwd
			strProxyPassword = strTemp.Right(strTemp.GetLength() - strlen(__PROXYPASSWORD__));
		}
		else if(strTemp.Find(__TIMEOUT__, 0) == 0)
		{//Time Out
			nTimeout = atoi(strTemp.Right(strTemp.GetLength() - strlen(__TIMEOUT__)));
		}
		else if(strTemp.Find(__MATCHSTR__, 0) == 0)
		{//Match String
			strMatchContent = strTemp.Right(strTemp.GetLength() - strlen(__MATCHSTR__));
		}
		else if(strTemp.Find(__GROUPID__, 0) == 0)
		{//Group ID
			nGID = atoi(strTemp.Right(strTemp.GetLength() - strlen(__GROUPID__)));
		}
		else if(strTemp.Find(__MONITORID__, 0) == 0)
		{//Monitor ID
			nMID = atoi(strTemp.Right(strTemp.GetLength() - strlen(__MONITORID__)));
		}
		else if(strTemp.Find(__CUSTOMER__, 0) == 0)
		{//Customer
			strCustomer = strTemp.Right(strTemp.GetLength() - strlen(__CUSTOMER__));
		}
	}

	if(strURL.IsEmpty()) 
    {//Url is Empty
		sprintf(szReturn, "error=%s$", FuncGetStringFromIDS("SV_URL",
            "URL_LOST_ADDRESS"));	//<%IDS_UrlMonitor_1%>"error=缺少URL$"
		return bRet;//Return False
	}

	CString strServerName;
	CString strObject;
	INTERNET_PORT nPort;
	DWORD dwServiceType;
    //分割URL
	if (!AfxParseURL(strURL, dwServiceType, strServerName, strObject, nPort) ||
		dwServiceType != INTERNET_SERVICE_HTTP)
	{//分割失败
		sprintf(szReturn,"error=Parse URL failed$");
		return FALSE;
	}

	HINTERNET	hInet;
	HINTERNET	hConn;//Http Connect Handle
	HINTERNET	hHttpReq;//Http Request Handle     

	CString strProxy = _T("");
	if (!strProxyServer.IsEmpty())//Proxy Server Is Not Empty
    {
		if (!strProxyPort.IsEmpty())//Proxy Server Port Is Not Empty
			strProxy.Format("%s:%s", strProxyServer, strProxyPort);
        else//Proxy Server Port Is Empty
	        strProxy.Format("%s",strProxyServer);
    }

	if(!strProxy.IsEmpty())
    { 
        //Proxy Server String is Not Empty ,Then Open InterNet By Generic 
        //Mode whith Proxy
		hInet = InternetOpen("http generic", INTERNET_OPEN_TYPE_PROXY , strProxy, 
							"<local>", 1);
    }
    else
    {
        //Proxy Server String is Empty ,Then Open InterNet By Generic 
        //Mode whithout Proxy
		hInet = InternetOpen("http generic", 0, NULL, NULL, 1);
    }

	if(!hInet)
	{//Open Internet Faild
		sprintf(szReturn,"error=Internet Open failed$");
		return FALSE;//Return Faild
	}

   PARM    threadParm;	
   HANDLE   hThread; 
   DWORD    dwThreadID;
   threadParm.strServerName = strServerName;
   threadParm.strUser = strUsername;
   threadParm.strPass = strPassword;
   threadParm.nPort = nPort;
   threadParm.hInet=hInet;
   threadParm.strPost=  strPostData;
   threadParm.strProxyPassword=strProxyPassword;
   threadParm.strProxyUsername=strProxyUsername;
   threadParm.strObject =strObject;

   hThread = CreateThread(
         NULL,            // Pointer to thread security attributes 
         0,               // Initial thread stack size, in bytes 
         WorkerConnectFunction,  // Pointer to thread function 
         &threadParm,     // The argument for the new thread
         0,               // Creation flags 
         &dwThreadID      // Pointer to returned thread identifier 
     );    

   // Wait for the call to InternetConnect in worker function to complete
   int dwTimeout = 5000; // in milliseconds
   if ( WaitForSingleObject ( hThread, dwTimeout ) == WAIT_TIMEOUT )
   {       
       if ( threadParm.hInet )
			InternetCloseHandle ( threadParm.hInet );
		TerminateThread(hThread, 0);       
       return FALSE;
   }

   // The state of the specified object (thread) is signaled
	unsigned long dwExitCode = 0;
	if ( !GetExitCodeThread( hThread, &dwExitCode ) )
	{
	   return FALSE;
	}
	TerminateThread(hThread, 0);
	if ( dwExitCode )
	  return FALSE;

	hConn=threadParm.hConn;
	if(!hConn)
	{//连接失败
		dwError=::GetLastError();//得到最后一次错误
        strError=::GetErrorMessage(dwError);//得到错误信息
		sprintf(szReturn,"error=InternetConnect:%s$",strError);
		InternetCloseHandle(hInet);//关闭句柄
		return FALSE;//Faild
	}

	CString strPost = strPostData;
	if(strPost.IsEmpty())//Post Data is Empty, Open Request By Get Mode
		hHttpReq = HttpOpenRequest(hConn, "GET", strObject, "HTTP/1.0", NULL, 0, 
								INTERNET_FLAG_RELOAD, 0);
	else//Post Data is not Empty , Open Request By POST Mode
		hHttpReq = HttpOpenRequest(hConn, "POST", strObject, "HTTP/1.0", NULL, 0, 
								INTERNET_FLAG_RELOAD, 0);


	if(hHttpReq)
	{//Open HTTP Request Successed
		DWORD ms;
		DWORD mslength;
		ms =120000;
		mslength=4;
		::InternetQueryOption(hHttpReq,INTERNET_OPTION_RECEIVE_TIMEOUT,&ms,&mslength);
		ms =2000;
		::InternetSetOption(hHttpReq,INTERNET_OPTION_RECEIVE_TIMEOUT,&ms,sizeof(ms));
		::InternetQueryOption(hHttpReq,INTERNET_OPTION_RECEIVE_TIMEOUT,&ms,&mslength);

		::InternetQueryOption(hHttpReq,INTERNET_OPTION_SEND_TIMEOUT,&ms,&mslength);
		ms =120000;
		::InternetSetOption(hHttpReq,INTERNET_OPTION_SEND_TIMEOUT,&ms,sizeof(ms));
		::InternetQueryOption(hHttpReq,INTERNET_OPTION_SEND_TIMEOUT,&ms,&mslength);

		BOOL bResult = FALSE;
		CString strContentType = _T("Content-Type: application/x-www-form-urlencoded");

		CString strProxyUser = strProxyUsername;//代理用户名
		CString strProxyPass = strProxyPassword;//代理密码
		if(!strProxyUser.IsEmpty())
		{//代理用户名不为空
			CString	strUserPass = _T("");
			strUserPass.Format("%s:%s", strProxyUser, strProxyPass);
			CString	strOutput = _T("Proxy-Authorization: Basic ");//代理服务器验证
			CBase64	*pBase64 = new CBase64();
            //加密用户名和密码
			strOutput.Insert(strOutput.GetLength(), pBase64->Encode(strUserPass, strUserPass.GetLength()));
			delete pBase64;
			pBase64 = NULL;			
			strOutput += _T("\r\n");
            //增加Http头内容
			if(!HttpAddRequestHeaders(hHttpReq, strOutput, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE))
			{//失败
				dwError=::GetLastError();//Get Last Error
				strError=::GetErrorMessage(dwError);//Get Error Message
				sprintf(szReturn,"error=InternetConnect:%s$",strError);
				InternetCloseHandle(hHttpReq);//Close Request Handle
				InternetCloseHandle(hConn);//Close Connection Handle
				InternetCloseHandle(hInet);//Close Internet Handle
				return FALSE;//Failed
			}				
		}
		int nTime=0;
LOOP://循环调用
#if 0
		InternetCloseHandle(hHttpReq);
		bResult=SendInetReqeust(threadParm,szReturn );
		hHttpReq =threadParm.hHttpReq;
#else
		if(strPost.IsEmpty())//Post Data Is Empty
			bResult = HttpSendRequest(hHttpReq, NULL, 0, NULL, 0);
		else
			bResult = HttpSendRequest(hHttpReq, strContentType, strContentType.GetLength(), 
									(void *)(LPCTSTR)strPost, strPost.GetLength());
#endif 
		
		if(bResult)
		{
			char	sBuffer[1024]={0};
			DWORD	lBuffer = 1024;
			int nStatusCode = 0;
			int nPageSize = 0;
            //Query Request Information(状态码)
			if(!HttpQueryInfo(hHttpReq, HTTP_QUERY_STATUS_CODE, &sBuffer, &lBuffer, 
							NULL))
			{//Failed
				dwError=::GetLastError();//Get Last Error
				strError=::GetErrorMessage(dwError);//Get Error Message
				sprintf(szReturn,"error=HttpQueryInfo:%s$",strError);
				InternetCloseHandle(hHttpReq);//Close Request Handle
				InternetCloseHandle(hConn);//Close Connection Handle
				InternetCloseHandle(hInet);//Close Internet handle
				return FALSE;//Failed
			}
			else
			{
				nStatusCode = atoi(sBuffer);//状态码
			}

			memset(sBuffer, 0, 1024);//Set Memory Data
			lBuffer = 1023;
			BOOL bRead = FALSE;
			DWORD lbegin = 0;
            CString strRecv = _T("");
            //Read Http Content Form Request
			bRead =InternetReadFile(hHttpReq,  sBuffer, lBuffer, &lbegin);
			while(bRead) 
            {//Read All Http Request File
				if((0 == lbegin)&&(TRUE == bRead)) 
					break;					
				sBuffer[lbegin] = '\0';
                strRecv += sBuffer;
				nPageSize += lbegin;					
				bRead = InternetReadFile(hHttpReq, sBuffer, lBuffer, &lbegin);
			}		
			
			
			//取得WTC相关信息
			CString str = _T("");			
			DWORD dwEnd = ::GetTickCount();	
            nStatusCode = GetSessionCount(strRecv);
			str.Format("rootNum=%d$totaltime=%.2f$downloadsize=%d$", nStatusCode, (dwEnd - dwStart)*1.0/1000, nPageSize);
			
            if (strMatchContent.IsEmpty()) 
            {//Match String is Empty
				strcpy(szReturn, (LPCTSTR)str);
			}
			else 
            {
                if(strRecv.Find(strMatchContent,0) >= -1)
                {//Match Content Successed
                    sprintf(szReturn, "error=%s$", FuncGetStringFromIDS("<%IDS_UrlMonitor_2%>"));//<%IDS_UrlMonitor_2%>"error=匹配失败$"
                }
                else
                {//Match Content Failed
                    strcpy(szReturn, (LPCTSTR)str);
                }
			}            
		}
		else
		{
			dwError=::GetLastError();//Get Last Error
			if(nTime<5)
			{//循环次数小于5
				nTime++;//增加次数
                Sleep(3000);//休眠3秒
				goto LOOP;//循环
			}
            strError=::GetErrorMessage(dwError);
			sprintf(szReturn,"error=HttpSendRequest:%s$",strError);
			InternetCloseHandle(hHttpReq);//Close Requst Handle
			InternetCloseHandle(hConn);//Close Connection Handle
			InternetCloseHandle(hInet);//Close Internet Handle
			hHttpReq = NULL;//Set Request Handle as NULL
			hConn = NULL;//Set Connction Handle as NULL
			hInet = NULL;//Set Internet Handle as NULL
			return FALSE;// Return Failed
		}
	}
	else
	{
		dwError=::GetLastError();
        strError=::GetErrorMessage(dwError);
		sprintf(szReturn,"error=HttpOpenRequest:%s$",strError);
		InternetCloseHandle(hConn);//Close Connection Handle
		InternetCloseHandle(hInet);//Close Internet Handle
		return FALSE;
	}
	InternetCloseHandle(hHttpReq);//Close Requst Handle
	InternetCloseHandle(hConn);//Close Connection Handle
	InternetCloseHandle(hInet);//Close Internet Handle

	CString tempstr = szReturn;
	MakeCharByString(szReturn, nSize, tempstr);

    return TRUE;
}