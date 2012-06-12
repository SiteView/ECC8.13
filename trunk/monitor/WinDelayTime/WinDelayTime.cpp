// WinDelayTime.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "WinDelayTime.h"
//#include "QueryWMI.h"
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "../../kennel/svdb/svapi/svapi.h"
#import "progid:WbemScripting.SWbemLocator" named_guids
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	std::string  gRoot_path="";
}

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CWinDelayTimeApp

BEGIN_MESSAGE_MAP(CWinDelayTimeApp, CWinApp)
END_MESSAGE_MAP()


// CWinDelayTimeApp 构造

CWinDelayTimeApp::CWinDelayTimeApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CWinDelayTimeApp 对象

CWinDelayTimeApp theApp;


// CWinDelayTimeApp 初始化

BOOL CWinDelayTimeApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

int findTimeInStr(time_t & t, string & strT, string const & message)  //返回星级几，范围[0,6]
{
	basic_string <char>::size_type i = 0;
	while(!isdigit(message[i])) i++;
	strT = message.substr(i, 8);
	string tmp = message.substr(i, 2);
	tm m;
	m.tm_hour = atoi(tmp.c_str());
	tmp = message.substr(i+3, 2);
	m.tm_min = atoi(tmp.c_str());
	tmp = message.substr(i+6, 2);
	m.tm_sec = atoi(tmp.c_str());

	i = i + 8;
	while(!isdigit(message[i])) i++;
	tmp = message.substr(i, 10);
	strT = tmp + " " + strT;
	tmp = message.substr(i, 4);
	m.tm_year = atoi(tmp.c_str()) - 1900;
	tmp = message.substr(i+5, 2);
	m.tm_mon = atoi(tmp.c_str()) - 1;
	tmp = message.substr(i+8, 2);
	m.tm_mday = atoi(tmp.c_str());

	t = mktime(&m);
	return m.tm_wday;
}

inline int durTime(time_t t1, time_t t2)
{
	return int(t1 - t2);
}

CString FuncGetInstallPath()
{
	CString strRet = _T("");
	strRet= GetSiteViewRootPath().c_str();
	return strRet;
}

//下面三个函数 hou ren m m n
inline time_t str2time(string const & str)
{
	istringstream iss(str);
	tm t;
	iss >> t.tm_year >> t.tm_mon >> t.tm_mday >> t.tm_hour >> t.tm_min >> t.tm_sec;	
	return mktime(&t);
}

inline void time2str(char* buf, time_t t)
{
	tm * ptm = gmtime(&t);
	sprintf(buf, "%d %d %d %d %d %d", ptm->tm_year, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	OutputDebugString(buf);
}

inline void changeStr(string & to, string const &from)
{
	int ayear = 100;
	int amon = 1;
	int aday = 1;
	int ahour = 0;
	int amin = 0;
	int asec = 0;
	string tmpStr = from.substr(0, 4);
	ayear = atoi(tmpStr.c_str());
	ayear -= 1900;            //从1900年开始
	char tmp[5] = {0};
	itoa(ayear, tmp, 10);
	to = tmp;
	tmpStr = from.substr(4, 2);
	amon = atoi(tmpStr.c_str());
	amon--;                  //月份从0开始
	itoa(amon, tmp, 10);
	to = to + " " + tmp;
	tmpStr = from.substr(6, 2);
	to += " ";
	to += tmpStr;
	tmpStr = from.substr(8, 2);
	to += " ";
	to += tmpStr;
	tmpStr = from.substr(10, 2);
	to += " ";
	to += tmpStr;
	tmpStr = from.substr(12, 2);
	to += " ";
	to += tmpStr;
}

bool MakeStringListByChar(std::list<string>& pList, const char * pInput )
{
	const char * p;
	int nSize;
	p=pInput;
	while(*p!='\0')
	{
		nSize = static_cast<int>(strlen(p));
		if( nSize>0 )
		{	
			pList.push_back((string)p);
			//	printf(p);
		}
		p=p+nSize+1;
		OutputDebugString(p);
	}

	return true;
}


bool MakeCharByString(char *pOut, int & nOutSize, char const * strInput)
{
	char *p;

	int nSize=(int)strlen(strInput);
	if(nSize < nOutSize)
	{
		strcpy(pOut, strInput);
	}else return false;
	OutputDebugString("size ok1");
	p=pOut;
	for(int i=0; i<nSize; i++)
	{
		if(*p=='$') *p='\0';
		p++;
	}
	*p='\0';
	OutputDebugString("size ok2");
	nOutSize=nSize+1;
	return true;
}

string GetValueFromList(const char * strName,list<string>& strList)
{
	list<string>::iterator it = strList.begin();
	basic_string <char>::size_type pos;
	static const basic_string <char>::size_type npos = -1;
	while(it != strList.end())
	{
		if (((pos=(*it).find("=")) != npos) && ((*it).substr(0, pos) == strName))
		{
			return (*it).substr(pos+1);
		}
		it++;
	}
	return "";	
}

BOOL GetMachineInfo(list<string>& lstParas,string &strMachineName,
										string& strUserAccount,string& strPassWord)
{
	OutputDebugString("i am in");
	strMachineName=GetValueFromList("_MachineName",lstParas);
	OutputDebugString("i am out");
	OutputDebugString(strMachineName.c_str());
	if (strMachineName=="")
		return FALSE;

	strUserAccount=GetValueFromList("_UserAccount",lstParas);
	OutputDebugString(strUserAccount.c_str());

	strPassWord=GetValueFromList("_PassWord",lstParas);
	OutputDebugString(strPassWord.c_str());

	return TRUE;
}

BOOL DFN_WritePrivateProfileString(
																	 LPCTSTR lpAppName,  // section name
																	 LPCTSTR lpKeyName,  // key name
																	 LPCTSTR lpString,   // string to add
																	 LPCTSTR lpFileName  // initialization file
																	 )
{  
	BOOL Result = TRUE;

	std::string dfn_Section;
	std::string dfn_Key;
	std::string dfn_Default;
	std::string dfn_File;
	dfn_Section =lpAppName;
	dfn_Key   = lpKeyName;
	dfn_File = lpFileName;
	dfn_Default = lpString;

	std::string dfn_Val;
	std::string strInt ;
	if(gRoot_path=="")
		gRoot_path =FuncGetInstallPath();
	char szPath[1024]={0};
	sprintf(szPath,"%s\\data\\TmpIniFile\\%s",gRoot_path.c_str(),dfn_File.c_str());
	//puts(szPath);
	WritePrivateProfileString(lpAppName,lpKeyName,lpString,szPath);
	return Result;
}

CString GetStringListIndex(int nIndex ,CStringList& strList)
{
	POSITION pos;
	pos=strList.GetHeadPosition();
	for(int i=0;i<nIndex;i++)
		strList.GetNext(pos);
	return strList.GetAt(pos);

}


DWORD DFN_GetPrivateProfileString(
																	LPCTSTR lpAppName,        // section name
																	LPCTSTR lpKeyName,        // key name
																	LPCTSTR lpDefault,        // default string
																	LPTSTR lpReturnedString,  // destination buffer
																	DWORD nSize,              // size of destination buffer
																	LPCTSTR lpFileName        // initialization file name
																	)
{
	std::string dfn_Section;
	std::string dfn_Key;
	std::string dfn_Default;
	std::string dfn_File;
	dfn_Section =lpAppName;
	dfn_Key   = lpKeyName;
	dfn_Default= lpDefault;
	dfn_File = lpFileName;

	std::string dfn_Val;

	if(gRoot_path=="")
		gRoot_path =FuncGetInstallPath();

	//dfn_Val=GetIniFileString(dfn_Section, dfn_Key,dfn_Default,dfn_File);

	char configpath[1024]={0};

	sprintf(configpath,"%s\\data\\TmpIniFile\\%s",gRoot_path.c_str(),dfn_File.c_str());
	OutputDebugString(configpath);

	//puts(configpath);
	return GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,configpath);

}

extern "C" _declspec(dllexport) BOOL DieTime(const char * strParas, char * szRet, int& nSize)
{
	CoInitialize(NULL);       //初始化COM
	{


		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		string strMachineName="";
		string strUserAccount="";
		string strPassWord="";
		list<string> lstParas ;
		MakeStringListByChar(lstParas,strParas);

		GetMachineInfo( lstParas,strMachineName,strUserAccount,strPassWord);

		string strGroupID = "", strMonitorID = "", strCustomer = "";

		strGroupID = GetValueFromList("_GroupID",lstParas);
		strMonitorID = GetValueFromList("_MonitorID",lstParas);
		//	strCustomer = GetValueFromList("_CustomerPath",lstParas);

		WbemScripting::ISWbemServicesPtr i_services;
		WbemScripting::ISWbemObjectSetPtr i_objSet;
		std::string i_queryLang;
		IEnumVARIANTPtr i_enum;

		WbemScripting::ISWbemObjectPtr tmpObj;
		WbemScripting::ISWbemPropertySetPtr tmpProperties;
		WbemScripting::ISWbemPropertyPtr prop;

		WbemScripting::ISWbemLocatorPtr locator;

		try
		{

			locator.CreateInstance(WbemScripting::CLSID_SWbemLocator);

			BSTR bSvrName = _com_util::ConvertStringToBSTR(strMachineName.c_str());
			BSTR bName = _com_util::ConvertStringToBSTR("");
			BSTR bPassword = _com_util::ConvertStringToBSTR("");
			string strTmp = strMachineName;
			transform(strTmp.begin(), strTmp.end(), strTmp.begin(), tolower);  //将服务器名转化为小写以进行比较，确定是否为远程机器
			if (("localhost" != strTmp) && ("127.0.0.1" != strTmp))     //是远程机器，则使用用户名和密码验证
			{
				bName = _com_util::ConvertStringToBSTR(strUserAccount.c_str());
				bPassword = _com_util::ConvertStringToBSTR(strPassWord.c_str());
			}	
			BSTR bNameSp = _com_util::ConvertStringToBSTR("root\\cimv2");

			if (locator != NULL)
			{
				i_services = locator->ConnectServer(bSvrName, bNameSp, bName, bPassword, "", "", 0, NULL);
			}
		}
		catch (_com_error err)
		{
			char buf[200] = {0};
			IErrorInfo * ei = err.ErrorInfo();
			BSTR strDesEI;
			ei->GetDescription(&strDesEI);
			sprintf(buf, "error code: 0x%x. %s.", (unsigned)err.Error(), _com_util::ConvertBSTRToString(strDesEI));
			OutputDebugString(buf);
			sprintf(szRet, "error=获取数据失败，可能是宕机了");
			nSize = strlen(szRet) + 2;
			return FALSE;
		}
		OutputDebugString("i am wmi right");

		string q = "select * from Win32_NTLogEvent where Logfile= 'System' and EventCode = 6008 and TimeWritten>= '";
		OutputDebugString(q.c_str());

		string strTempFile = "Software\\Siteview\\SiteviewECC\\fordie\\" + strMonitorID;

		DWORD regTime = 0;
		DWORD monTotleTime = 0;
		DWORD monTotleNum = 0;
		string showTime = "没宕机";
		char startTime[50] = {0};
		//	::DFN_GetPrivateProfileString(strMonitorID.c_str(), "lasttime", "", buffer, 0, strTempFile);

		HKEY hKey;
		if (RegOpenKey(HKEY_LOCAL_MACHINE, strTempFile.c_str(), &hKey) == ERROR_SUCCESS)
		{
			DWORD dwValue;
			DWORD dwType;
			RegQueryValueEx(hKey, "beginTime", 0, &dwType, (LPBYTE)&regTime, &dwValue);
			RegQueryValueEx(hKey, "totleTime", 0, &dwType, (LPBYTE)&monTotleTime, &dwValue);
			RegQueryValueEx(hKey, "totleNumber", 0, &dwType, (LPBYTE)&monTotleNum, &dwValue);
			LONG lValue;
			RegQueryValue(hKey, NULL, NULL, &lValue);
			char *pBuf=new char[lValue];
			RegQueryValue(hKey, NULL, pBuf, &lValue);
			showTime = pBuf;
			delete [] pBuf;
		}
		else OutputDebugString("read reg error");
		RegCloseKey(hKey);

		time_t curTime = time(0);
		time_t tmpTime, monBeginTime;
		int total = 1;              //免得除0

		tm * mm = localtime(&curTime);

		mm->tm_mday = 1;
		mm->tm_hour = mm->tm_min = mm->tm_sec = 0;
		monBeginTime = mktime(mm);

		if (regTime == 0) 
		{
			tmpTime = monBeginTime;
			monTotleTime = 0;     //总计时间清零
			monTotleNum = 0;
		}
		else
		{
			//先保留当前年和月，以免被后面调用localtime时被覆盖
			int y = mm->tm_year;
			int m = mm->tm_mon;
			tmpTime = (time_t)regTime;
			mm = localtime(&tmpTime);

			//上次检测的时间和当前时间如果不同则记录月宕机总时间的注册表信息清零
			if ((y != mm->tm_year) || (m != mm->tm_mon))
			{
				monTotleTime = 0;
				monTotleNum = 0;
			}
		}
		total = durTime(curTime, monBeginTime);
		char buf1[100] = {0};
		sprintf(buf1, "tmpTime=%d", tmpTime);
		OutputDebugString(buf1);
		tm * m = gmtime(&tmpTime);
		sprintf(startTime, "%d%02d%02d%02d%02d%02d.000000+480", m->tm_year + 1900, m->tm_mon + 1, m->tm_mday, m->tm_hour, m->tm_min, m->tm_sec);

		q = q + startTime + "'";

		OutputDebugString(q.c_str());

		unsigned int nCount = -1;

		try
		{
			BSTR bQueryLang = _com_util::ConvertStringToBSTR("WQL");
			BSTR bStrQuery = _com_util::ConvertStringToBSTR(q.c_str());
			i_objSet = i_services->ExecQuery(bStrQuery, bQueryLang, 0x10, NULL);
			nCount = (unsigned int)(i_objSet->Count);
		}
		catch (_com_error err)
		{
			char buf[200] = {0};
			IErrorInfo * ei = err.ErrorInfo();
			BSTR strDesEI;
			ei->GetDescription(&strDesEI);
			sprintf(buf, "error code: 0x%x. %s.", (unsigned)err.Error(), _com_util::ConvertBSTRToString(strDesEI));
			OutputDebugString(buf);
			sprintf(szRet, "error=获取数据失败，可能是宕机了");
			nSize = strlen(szRet) + 2;
			return FALSE;
		}

		char ff[100];
		sprintf(ff, "ff = %d", nCount);
		OutputDebugString(ff);
		if (-1 == nCount)
		{
			sprintf(szRet,"error=error");
			OutputDebugString("err");
			return FALSE;
		}


		time_t lastDieTime = 0;
		time_t beginTime;
		time_t endTime;
		
		unsigned long durance = 0;

		i_enum = i_objSet->Get_NewEnum();

		ULONG fetched;
		VARIANT var;
		while (i_enum->Next(1, &var, &fetched) == S_OK)
		{
			string strMessage = "error value";
			string strWriteTime = "error value";
			tmpObj = var;
			tmpProperties = tmpObj->Properties_;

			BSTR bTmp;
			try
			{
				bTmp = _com_util::ConvertStringToBSTR("message");
				prop = tmpProperties->Item(bTmp, 0);
				strMessage = (const char*)_bstr_t(prop->GetValue());
				bTmp = _com_util::ConvertStringToBSTR("TimeWritten");
				prop = tmpProperties->Item(bTmp, 0);
				strWriteTime = (const char*)_bstr_t(prop->GetValue());

				if ((strWriteTime != "error value") && (strMessage != "error value")) 
				{
					string rt;
					if (0 != findTimeInStr(beginTime, rt, strMessage)) //不是星期天
					{
						if (beginTime > lastDieTime)
						{
							lastDieTime = beginTime;
							showTime = rt;
						}
						strWriteTime.erase(strWriteTime.begin()+14, strWriteTime.end());
						changeStr(rt, strWriteTime);
						endTime = str2time(rt);
						durance += durTime(endTime,beginTime);
					}
					else
					{
						--nCount;    //减去星期天宕机的次数
					}
				}
				else
				{
					sprintf(szRet,"error=read error");
					return FALSE;
				}
			}
			catch (_com_error err)
			{
				char buf[200] = {0};
				IErrorInfo * ei = err.ErrorInfo();
				BSTR strDesEI;
				ei->GetDescription(&strDesEI);
				sprintf(buf, "error code: 0x%x. %s.", (unsigned)err.Error(), _com_util::ConvertBSTRToString(strDesEI));
				OutputDebugString(buf);
				sprintf(szRet, "error=获取数据失败，可能是宕机了");
				nSize = strlen(szRet) + 2;
				return FALSE;
			}
		}

		monTotleNum += nCount;
		monTotleTime += durance;
		double perc = 100.00*monTotleTime/total;
		
		char buffer[200] = {0};
		sprintf(buffer, "dieNum=%u$dieTime=%u$diePerc=%f$dieLast=%s$totleNum=%u$" ,nCount, durance, perc, showTime.c_str(), monTotleNum);
		OutputDebugString(buffer);
		//	ss << "dieNum=" << nCount << "$dieTime=" << durance << "$diePerc=" << perc << "$dieLast=" << showTime << "$";
		//	OutputDebugString(ss.str().c_str());
		MakeCharByString(szRet, nSize, buffer);


		//	OutputDebugString(forSaveStr.c_str());
		//	::DFN_WritePrivateProfileString(strMonitorID.c_str(), "lasttime", forSaveStr.c_str(), strTempFile);
		HKEY hKey1;
		RegCreateKey(HKEY_LOCAL_MACHINE, strTempFile.c_str(), &hKey1);
		if ((ERROR_SUCCESS != RegSetValueEx(hKey1, "beginTime", 0, REG_DWORD, (CONST BYTE*)&curTime, 4))
			|| (ERROR_SUCCESS != RegSetValueEx(hKey1, "totleTime", 0, REG_DWORD, (CONST BYTE*)&monTotleTime, 4))
			|| (ERROR_SUCCESS != RegSetValueEx(hKey1, "totleNumber", 0, REG_DWORD, (CONST BYTE*)&monTotleNum, 4))
			|| (ERROR_SUCCESS != RegSetValue(hKey1, NULL, REG_SZ, showTime.c_str(), showTime.size())))
		{
			OutputDebugString("write reg error");
		}
		RegCloseKey(hKey1);
		//CoUninitialize();
		OutputDebugString("i am closereg");
	}
	CoUninitialize();
	return TRUE;
}
