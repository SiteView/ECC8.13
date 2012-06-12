// showhtm.cpp : �������̨Ӧ�ó������ڵ㡣
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
{//���ַ�������(IDS_)�滻Ϊ��ص�����

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
		AddNodeAttrib(ResNode,"IDS_NamePWDError","�û������������");
		AddNodeAttrib(ResNode,"IDS_Login_Name","�û���");
		AddNodeAttrib(ResNode,"IDS_Password1","�� ��");
		AddNodeAttrib(ResNode,"IDS_SystemLimit","ϵͳ���ڣ����볧����ϵ��");
		AddNodeAttrib(ResNode,"IDS_Help","����");
		AddNodeAttrib(ResNode,"IDS_LogoutAffirmInfo","ȷ���˳�SiteView ��");
		AddNodeAttrib(ResNode,"IDS_ConfirmCancel","ȡ��");
		AddNodeAttrib(ResNode,"IDS_Affirm","ȷ��");
		AddNodeAttrib(ResNode,"IDS_Logout","�ǳ�");
		AddNodeAttrib(ResNode,"IDS_UserAffirm","�û�ȷ���˳�");


		return ResNode;

}

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[4096];

	DWORD tm = GetTickCount();
	//��������ܻ�ʱ�䣬resource.data's size is 378kb, Ӧ����compile time������loading�����⣬����ֻҪloadһ�Ρ�
	//if need auto-switch to the IE' language, need load and process at runtime
	OBJECT objRes=LoadResource("default", "localhost");  
	DWORD tm1 = GetTickCount();

	std::string szPath = GetSiteViewRootPath();
	szPath += "\\data\\svdbconfig.ini";

	INIFile theINI = LoadIni(szPath.c_str());

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
		
		if( objRes !=INVALID_VALUE )
		{			
			MAPNODE ResNode=GetResourceNode(objRes);

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
		}
		
		
		int intertime1 = tm1 - tm;
		char tbuf[256];
		sprintf(tbuf, "run time:%d\n", intertime1);
		OutputDebugString(tbuf);
	}
	CloseResource(objRes);	
		
	return 0;
}

