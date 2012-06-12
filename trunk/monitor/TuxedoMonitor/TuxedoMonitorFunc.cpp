#include "stdafx.h"
#include <list>
#include <stdio.h>
#include <string.h>           
#include "TuxedoGet.h"
#include "TuxedoMonitorFunc.h"
#include <fstream>

using namespace std;
typedef struct std::list<char*> StringList;

bool MakeStringListByChar(StringList& pList, const char * pInput )
{
	const char * p;
	int nSize;
	p=pInput;
	while(*p!='\0')
	{
		nSize =strlen(p);
		if( nSize>0 )
		{	
			//pList.AddHead(p);
			pList.push_back((char*)p);

		}
		p=p+nSize+1;
	}

	return true;
}

int GetCharLength(const char * pInput)
{
	const char * p;
	int nSize = 0;
	p=pInput;
	while(*p!='\0')
	{
		nSize += strlen(p) + 1;
		p += strlen(p)+1;
	}

	 return nSize;
}

bool MakeCharByString(char *pOut,int &nOutSize,CString strInput )
{
	 char *p;
	
	int nSize=strInput.GetLength();
	if(nSize+2 <nOutSize)
	{
		strcpy(pOut,strInput.GetBuffer(strInput.GetLength()));
	}else return false;
	p=pOut;
	//printf("%d\n",nSize);23028830 13602067678 王波
	for(int i=0;i<nSize;i++)
	{
		if(*p=='$') 	
			*p='\0';
		p++;
	}
	nOutSize=nSize+1;
	return true;
	
}

char *FindStrValue(const char *strParas, CString str)
{
	char *pValue = NULL;
	string m_TempStr;

	std::list<char*> strList;
	MakeStringListByChar(strList, strParas);
	std::list<char *>::iterator pos = strList.begin();

	 while(pos != strList.end())
	{
		//CString strTemp = strList.GetNext(pos);
		char * strTemp = *pos;
		std::string strTemp1 = *pos;
		int m_Fpos = 0;
		
		if((m_Fpos = strTemp1.find(str, 0)) >= 0)
		{
			m_TempStr = strTemp1.substr( m_Fpos + strlen(str)+1, strTemp1.size() - strlen(str) - 1); 
			pValue=(char*)malloc(m_TempStr.size()+1);
			strcpy(pValue, m_TempStr.c_str());
			
		}
		pos++;
	}

	return pValue;
	
}


extern "C" __declspec(dllexport) 
BOOL TuxedoList(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");

	int nMTID = 0;
	nMTID = atoi(FindStrValue(strParas, "_TemplateID"));
	BOOL bRet = FALSE;
	switch(nMTID)
    {
    case 310:
        bRet = GetMachineList(strParas, strReturn, nSize);
		break;
    case 311:
        bRet = GetServerList(strParas, strReturn, nSize);
        break;
    case 312:
        bRet = GetMsgList(strParas, strReturn, nSize);
        break;
    case 313:
        bRet = GetClientList(strParas, strReturn, nSize);
        break;
    case 314:
        bRet = GetServiceList(strParas, strReturn, nSize);
        break;
    case 315:
        bRet = GetWSHList(strParas, strReturn, nSize);
        break;
    default:
        return FALSE;
    }
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	 
	return bRet;
}

extern "C" __declspec(dllexport) 
BOOL TuxedoMachine(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");

	BOOL bRet = GetMachine(strParas, strReturn, nSize);
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	 
	return bRet;
}

extern "C" __declspec(dllexport) 
BOOL TuxedoServer(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");
	
	BOOL bRet = GetServer(strParas, strReturn, nSize);
	/*写调试日志
	CString sFilename;
	if(!bRet)
		sFilename = "tuxfailed.log";
	else
		sFilename = "tuxsuccessed.log";
	
	//std::list<char*> paramList;
	//MakeStringListByChar(paramList, strParas);
	//std::list<char *>::iterator pos = paramList.begin();

	CString str, sTime;
	sTime = COleDateTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	//while(pos != paramList.end())
	//{
	//	char * strTemp = *pos;
	//	str = strTemp;
	//	str += " for debug zjw";
	//	ofstream fout(sFilename,ios::app);
	//	fout << sTime << ":" <<str <<"\r\n"; 
	//	fout << flush; 
	//	fout.close(); 
	//	pos++;
	//}
	ofstream fout(sFilename,ios::app);
	fout << sTime << ":" <<strReturn <<"\r\n"; 
	fout <<"\r\n"; 
	fout << flush; 
	fout.close(); 
	*/
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	
	return bRet;
}

extern "C" __declspec(dllexport) 
BOOL TuxedoMsg(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");

	BOOL bRet = GetMsg(strParas, strReturn, nSize);
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	 
	return bRet;
}

extern "C" __declspec(dllexport) 
BOOL TuxedoClient(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");

	BOOL bRet = GetClient(strParas, strReturn, nSize);
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	 
	return bRet;
}

extern "C" __declspec(dllexport) 
BOOL TuxedoService(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");

	BOOL bRet = GetService(strParas, strReturn, nSize);
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	 
	return bRet;
}

extern "C" __declspec(dllexport) 
BOOL TuxedoWSH(const char *strParas, char * strReturn, int & nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString		strServIp = FindStrValue(strParas, "_ServerIp");
	CString		strServPort = FindStrValue(strParas, "_ServerPort");
	CString strServerip = "WSNADDR=//"+strServIp+":"+strServPort;

	//设置机器环境
	tuxputenv((LPTSTR)(LPCTSTR)strServerip);
	tuxputenv("WSENVFILE=");

	BOOL bRet = GetWSH(strParas, strReturn, nSize);
	
	CString strOutRet;
	strOutRet =strReturn;
	nSize = 2048;
	MakeCharByString(strReturn,nSize,strOutRet);	 
	return bRet;
}