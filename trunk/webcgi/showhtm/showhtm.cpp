// showhtm.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"


#include "stdio.h"
#include "fcgi_config_x86.h"
#include "fcgi_stdio.h"


#include <string>
#include "svdbapi.h"
#include "svapi.h"
#include <io.h>
#include <windows.h>

#include "../../base/stlini.h"

using namespace std;

void WriteLogFile(const char *pszFile, const char *pszMsg)
{
    FILE *pFile = fopen(pszFile, "a+");
    if (pFile)
    {
        fputs(pszMsg, pFile);
        fputs("\n", pFile);
        fclose(pFile);
    }
}

string& replace_all_str(string& str,
							 const string& old_value,
							 const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

string& replace_all_distinct(MAPNODE ResNode, string& str,
							 const string& old_value)
{//把字符串代号(IDS_)替换为相关的语言

	string::size_type pos1 = 0;
	string strRes = "";
	int nRes = 1;

	bool bChange = false;
	for(string::size_type pos(0); pos!=string::npos; pos+=nRes) 
	{
		if( (pos=str.find(old_value,pos))!=string::npos )
		{
			if((pos1 = str.find("!", pos)) != string::npos)
			{				
				string ostr = str.substr(pos, pos1 - pos );								
				
				if(FindNodeValue(ResNode, ostr, strRes))
				{
					str.replace(pos, pos1 - pos + 1, strRes);
					nRes = strRes.length();
					bChange = true;
					//WriteLogFile("log1.txt", str.c_str());
				}
				else
				{
					nRes = 1;
					break;
				}
				
			}
			
		}
		else 
		{
			
			break;
		}
	}
	if(bChange)
	{
		//WriteLogFile("log.txt", str.c_str());
		bChange = false;
	}


	return str;
}

MAPNODE createResource() 
{
		MAPNODE ResNode = CreateNewMapNode();
		AddNodeAttrib(ResNode,"IDS_ProductName","SiteView ECC 7.0");
		AddNodeAttrib(ResNode,"IDS_NamePWDError","用户名或密码错误");
		AddNodeAttrib(ResNode,"IDS_Login_Name","用户名");
		AddNodeAttrib(ResNode,"IDS_Password1","密 码");
		AddNodeAttrib(ResNode,"IDS_SystemLimit","系统过期，请与厂商联系。");
		AddNodeAttrib(ResNode,"IDS_Help","帮助");
		AddNodeAttrib(ResNode,"IDS_LogoutAffirmInfo","确认退出SiteView ？");
		AddNodeAttrib(ResNode,"IDS_ConfirmCancel","取消");
		AddNodeAttrib(ResNode,"IDS_Affirm","确认");
		AddNodeAttrib(ResNode,"IDS_Logout","登出");
		AddNodeAttrib(ResNode,"IDS_UserAffirm","用户确认退出");


		return ResNode;

}

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[4096];

	DWORD tm = GetTickCount();
	//这个操作很花时间，resource.data's size is 378kb, 应该在compile time解决这个loading的问题，或者只要load一次。
	//if need auto-switch to the IE' language, need load and process at runtime
	//ZZJ SPEEDUP: OBJECT objRes=LoadResource("default", "localhost");  
	DWORD tm1 = GetTickCount();

	std::string szPath = GetSiteViewRootPath();
	szPath += "\\data\\svdbconfig.ini";

	INIFile theINI = LoadIni(szPath.c_str());
	MAPNODE ResNode = createResource();

	std::string szTSec = GetIniSetting(theINI, "svdb", "DefaultLanguage");
	szTSec += "_code";
	std::string m_code = GetIniSetting(theINI, "svdb", szTSec.c_str());

	OutputDebugString("-------------------showhtm program code--------------\n");
	OutputDebugString(m_code.c_str());
	OutputDebugString("\n");

	while(FCGI_Accept()>=0)
	{			
		char ** myenviron;
		myenviron =FCGI_GetEnv();
	
		char myenviron1[4096]={0};

		
		for(int i=0 ;myenviron[i];++i)
		{
			strcpy(myenviron1,myenviron[i]);
			putenv(myenviron[i]);
		}
		
	

		char *httpheader;
		httpheader =getenv("HTTP_COOKIE");
		int nSvsid = 0;
		int nUserId =0;
		if(httpheader)
		{
			//OutputDebugString(httpheader);
			///OutputDebugString("\n");
			char * p;
			p=strstr(httpheader,"svsid=");
			if(p)
			{
				p=p+6;
				nSvsid =atoi(p);
			}
			p=strstr(httpheader,"userid=");
			if(p)
			{
				p=p+7;
				nUserId =atoi(p);
			}
			
		}

		//svsid=4580; userid=1;
		
		


		printf("Content-type: text/html\r\n");
		printf("Set-Cookie: svsid=%d\r\n" ,nSvsid );
		printf("Set-Cookie: userid=%d\r\n" ,nUserId );
		printf("\r\n");

		httpheader =getenv("QUERY_STRING");		

		string 	qrystr;
		if(httpheader)
				qrystr=httpheader;
		string	szRootPath = GetSiteViewRootPath();
		string szHtmlPath = szRootPath;
		szHtmlPath += "\\htdocs\\";
		szHtmlPath += qrystr;	
		
		string str = "";
		
		//ZZJ SPEEDUP: if( objRes !=INVALID_VALUE )
		//ZZJ SPEEDUP: {	
			//ZZJ SPEEDUP: MAPNODE ResNode=GetResourceNode(objRes);

			if( ResNode != INVALID_VALUE )
			{

				FCGI_FILE* pf ;
				pf= FCGI_fopen(szHtmlPath.c_str(), "read");
				if( pf!= NULL)
				{					
					int len = 0;
					
					int nsize = _filelength( FCGI_fileno(pf) ); 					
					char tempBuffer[4096] = {0};
					//while ((len = fread(tempBuffer, 1, 4095, pf)) > 0) 
					while( fgets(tempBuffer,4095, pf)!=NULL)
					{
						str = tempBuffer;						
						str = replace_all_str(str, "GB2312", m_code);
						str = replace_all_str(str, "gB2312", m_code);
						str = replace_all_str(str, "Gb2312", m_code);
						str = replace_all_str(str, "gb2312", m_code);
						//used to replace all IDS_ string in htm files
						str = replace_all_distinct(ResNode, str, "IDS_");
						FCGI_printf(str.c_str());
						memset(tempBuffer, 0, 4096);
					}
					
					FCGI_pclose(pf);
				}
			}
		//ZZJ SPEEDUP: }
		
		
		int intertime1 = tm1 - tm;
		char tbuf[256];
		sprintf(tbuf, "run time:%d\n", intertime1);
		OutputDebugString(tbuf);
	}
	//ZZJ SPEEDUP: CloseResource(objRes);	
		
	return 0;
}

