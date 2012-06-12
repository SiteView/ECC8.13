// SQLServer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "SQLServer.h"
#include "DBPool.h"
#include "funcgeneral.h"
//#include "..\..\base\funcgeneral.h"
#include <fstream>

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

/////////////////////////////////////////////////////////////////////////////
// CSQLServerApp

BEGIN_MESSAGE_MAP(CSQLServerApp, CWinApp)
	//{{AFX_MSG_MAP(CSQLServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLServerApp construction

CSQLServerApp::CSQLServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSQLServerApp object

CSQLServerApp theApp;

#define MAX_BUFF_LEN 256

const LPCSTR DBDrive = _T("Provider=SQLOLEDB.1;Persist Security Info=False; " \
						"Initial Catalog=");


void WriteLogFile(char* chMsg)
{
    FILE *stream;
    char chTime[50] = {0};
    //打开文件
#if _DEBUG
    stream=fopen(FuncGetInstallRootPath() + "\\Temp\\SQLMonitor.log","a");
#else
    stream=fopen(FuncGetInstallRootPath() + "\\Monitormanager\\Temp\\SQLMonitor.log","a");
#endif
    if(stream == NULL)
        return;//打开文件失败，直接返回
   	SYSTEMTIME time;
	//取系统当前时间
	GetLocalTime(&time);
    //sprintf(chTime ,"%02d年-%02d月-%02d日 %02d时-%02d分-%02d秒 ",
    sprintf(chTime ,"%dY-%dM-%d D %dH-%dM-%dS ",
				//time.wYear - 2000,
                time.wYear,
				time.wMonth,
				time.wDay,
				time.wHour,
				time.wMinute,
				time.wSecond
			);
    fputs(chTime , stream);
	fputs(chMsg,stream);
    fputs("\n",stream);
	fclose(stream);
}

int PrintLog(const char * strReceive)
{
//#ifndef __DEBUG
//	return 0;
//#endif
	char timebuf[128]={0},datebuf[128]={0},tempbuf[4096]={0};
	_strtime(timebuf);
	_strdate(datebuf);
	sprintf(tempbuf,"%s-%s",datebuf,timebuf);
	ofstream filestream;
	filestream.open("SQLServerMonigor.log",ios::app);
	filestream<<tempbuf<<"\t"<<strReceive<<endl;
	filestream.close();
	return 0;
}
extern "C" __declspec(dllexport)
BOOL SQLBufferMonitr(const char * strParas, char * szReturn, int& nSize)
//(CStringList& paramList, char *szReturn )
{
	CStringList paramList;

	MakeStringListByChar(paramList,strParas);

	
	BOOL bRet= SQLMonitr(paramList,szReturn,211);
	CString strInput;
	strInput =szReturn;
	MakeCharByString(szReturn,nSize,strInput);
	return bRet;
}

extern "C" __declspec(dllexport)
BOOL SQLMemoryMonitr(const char * strParas, char * szReturn, int& nSize)
//(CStringList& paramList, char *szReturn )
{
	CStringList paramList;

	MakeStringListByChar(paramList,strParas);

	
	BOOL bRet= SQLMonitr(paramList,szReturn,212);
	CString strInput;
	strInput =szReturn;
	MakeCharByString(szReturn,nSize,strInput);
	return bRet;

	//return	SQLMonitr(paramList,szReturn,212);
}
extern "C" __declspec(dllexport)
BOOL SQLGeneralStatisticsMonitr(const char * strParas, char * szReturn, int& nSize)
//(CStringList& paramList, char *szReturn )
{

	//return SQLMonitr(paramList,szReturn,213);
	CStringList paramList;

	MakeStringListByChar(paramList,strParas);

	
	BOOL bRet= SQLMonitr(paramList,szReturn,213);
	CString strInput;
	strInput =szReturn;
	MakeCharByString(szReturn,nSize,strInput);
	return bRet;
}
extern "C" __declspec(dllexport)
BOOL SQLCacheMonitr(const char * strParas, char * szReturn, int& nSize)
{
	CStringList paramList;

	MakeStringListByChar(paramList,strParas);

	
	BOOL bRet= SQLMonitr(paramList,szReturn,214);
	CString strInput;
	strInput =szReturn;
	MakeCharByString(szReturn,nSize,strInput);
	return bRet;

//	return SQLMonitr(paramList,szReturn,214);
}
extern "C" __declspec(dllexport)
BOOL SQLStatisticsMonitr(const char * strParas, char * szReturn, int& nSize)
{
	CStringList paramList;

	MakeStringListByChar(paramList,strParas);

	
	BOOL bRet= SQLMonitr(paramList,szReturn,215);
	CString strInput;
	strInput =szReturn;
	MakeCharByString(szReturn,nSize,strInput);
	return bRet;
	//return SQLMonitr(paramList,szReturn,215);
}


BOOL SQLMonitr(CStringList& paramList, char *szReturn,int tplid )
{
    BOOL bRet = TRUE;
    CString strHost = _T(""), strUser = (""), strPwd = _T("");
	CString sql;
	
    char chConnect[MAX_BUFF_LEN] = {0};
	POSITION pos = paramList.GetHeadPosition();
	while(pos)
	{
		
		CString strTemp = paramList.GetNext(pos);
		puts(strTemp );

		if(strTemp.Find(__MACHINENAME__) == 0)
		{
			strHost = strTemp.Right(strTemp.GetLength() - (int)strlen(__MACHINENAME__));
		}
		else if(strTemp.Find(__USERACCOUNT__) == 0)
		{
			strUser = strTemp.Right(strTemp.GetLength() - (int)strlen(__USERACCOUNT__));
		}
		else if(strTemp.Find(__PASSWORD__) == 0)
		{
			strPwd = strTemp.Right(strTemp.GetLength() - (int)strlen(__PASSWORD__));
		}
		else if(strTemp.Find(__SQL__) == 0)
		{
			sql = strTemp.Right(strTemp.GetLength() - (int)strlen(__SQL__));
		}
		/*
		else if(strTemp.Find(__GROUPID__)==0)
		{
			
		}
		else if(strTemp.Find(__MID__)==0)
		{
		}*/

	}
	

	if (strHost == _T(""))
	{
        sprintf(szReturn, "error=%s$", FuncGetStringFromIDS("SV_SQL_SERVER", 
            "SQL_SERVER_IP_NULL"));
		return FALSE;
	}
    //sprintf(chConnect , "%s%s;Data Source=master;UID=%s;PWD=%s", DBDrive, 
	     //strHost, strUser, strPwd);
	sprintf(chConnect , "UID=%s;PWD=%s;DSN=%s", strUser, strPwd,strHost);

	
	switch(tplid)
	{
	case 211:
		sql="select * from sysperfinfo where object_name like  '%Buffer Manager%' and instance_name='' ";
			break;
	case 212:
		sql="select * from sysperfinfo where object_name like  '%Memory Manager%'   and instance_name=''";
		break;
	case 213:
		sql="select * from sysperfinfo where object_name like  '%General Statistics%'";
		break;
	case 214:
		sql="select * from sysperfinfo where object_name like  '%Cache Manager%'   and instance_name='_Total'";
		break;
	case 215:
		sql="select * from sysperfinfo where object_name like '%SQL Statistics%'   and instance_name=''";
		break;
	case 216:
		sql="select * from sys.dm_os_performance_counters where object_name like '%Plan Cache%' and instance_name='_Total'";
		break;
	}
	
	DBPool db;
	CString strRootPath;
	strcpy(db.dsn,strHost.GetBuffer(strHost.GetLength()));
	strRootPath =FuncGetInstallRootPath();
	strcpy(db.szRootPath,strRootPath.GetBuffer(strRootPath.GetLength()));

	int iConnect = db.ConnectToDB(chConnect);
//	if(db.ConnectToDB(chConnect))
	if(iConnect!=0)
	{
		sprintf(szReturn,"error=%s$",FuncGetStringFromIDS("SV_SQLSERVER",
            "SQLSERVER_CONNECT_FAILED"));
		return FALSE;
	}
	
	
	//db.QueryDB(sql.GetBuffer(sql.GetLength()));
	puts(sql);
	if(db.QueryDB(sql.GetBuffer(sql.GetLength()))<0)
	{
		sprintf(szReturn,"error=%s$",FuncGetStringFromIDS("SV_SQLSERVER",
            "SQLSERVER_QUERY_FAILED"));
		return FALSE;
	}


	//if(sql.Find("SQLServer:Buffer Manager")>0)
	//	db.CalBufferManager(szReturn);
	//else if(sql.Find("SQLServer:Memory Manager")>0)
	//	db.CalMemoryManager(szReturn);
	//else if(sql.Find("SQLServer:General Statistics")>0)
	//	db.CalGeneralStatistics(szReturn);
	//else if (sql.Find("SQLServer:Cache Manager")>0)
	//	db.CalCacheStatistics(szReturn);
	//else if (sql.Find("SQLServer:SQL Statistics")>0)
	//	db.CalStaticManager(szReturn);

	
	switch(tplid)
	{
	case 211:
		db.CalBufferManager(szReturn);
		break;
	case 212:
		db.CalMemoryManager(szReturn);
		break;
	case 213:
		db.CalGeneralStatistics(szReturn);
		break;
	case 214:
		db.CalCacheStatistics(szReturn);
		break;
	case 215:
		db.CalStaticManager(szReturn);
		break;
	case 216:
		db.CalCacheStatistics_2005(szReturn);
	}
	//dbGetItem()
	
	
	//
	
	


    return bRet;
	
}

/****************************************************************************
	Export Function Of DatabaseSourceNames (Fetch DSN)
****************************************************************************/
extern "C" __declspec(dllexport) 
BOOL SYSTEMDSN(const char * strParas, char * strReturn, int& nSize, char *strFlag )
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HKEY hKey = NULL;
	LONG lRet = NULL;	
	lRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources", 0, KEY_QUERY_VALUE , &hKey);
	char *p =strReturn;
	if (lRet == ERROR_SUCCESS) {
		// TODO: 
		DWORD dwIndex = 0;
		while (1) {
			char szValueName[512] = {0};
			DWORD dwSizeValue = sizeof(szValueName) - 1;
			
			char szVal[512] = {0};
			DWORD len = 512;

			//lRet = RegEnumValue(hKey, dwIndex, szValueName, &dwSizeValue, NULL, NULL, NULL, NULL);				
			lRet = RegEnumValue(hKey, dwIndex, szValueName, &dwSizeValue, NULL, NULL, (LPBYTE)szVal, &len);

			if (lRet != ERROR_SUCCESS)
				break;

			if(strstr(szVal, "Oracle") ==NULL)
			{			
				sprintf(p,"%s=%s",szValueName,szValueName);
				p+= 2* strlen(szValueName)+2;
				
			}
			
			//lstTexts.AddTail(szValueName);
			//lstValues.AddTail(szValueName);
			dwIndex++;
		}
		RegCloseKey(hKey);
	}

	return TRUE;
	
}

/****************************************************************************
	SQL Server 2005的CacheMonitor
****************************************************************************/
extern "C" __declspec(dllexport)
BOOL SQLCacheMonitr_2005(const char * strParas, char * szReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CStringList paramList;

	MakeStringListByChar(paramList,strParas);

	
	BOOL bRet= SQLMonitr(paramList,szReturn,216);
	CString strInput;
	strInput =szReturn;
	MakeCharByString(szReturn,nSize,strInput);
	return bRet;
}