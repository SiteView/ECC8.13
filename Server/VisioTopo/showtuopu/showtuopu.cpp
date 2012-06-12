///////////////////////////////////////////////////////////////////////////////////////////////////
//
//1��ȡGet����pageid��version��ֵ
//2��ִ��maketuopu.exe pageid.files\data.xml version ����Ҫ��ȷ��htm�������ļ�
//3������pageid.files\main2.html����ʾ
//4������.bak\�µ�*.js��*.htm�ȵ�pagid.files\Ŀ¼��
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

//#include "fcgi_config.h"
#include "fcgi_config_x86.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <Windows.h>
//#undef _WIN32

#ifdef _WIN32
#include <process.h>
#else
extern char **environ;
#endif


#include "fcgi_stdio.h"
#include <time.h>
#include <string.h>
#include <windows.h>

#include "../../Base/SVQueryString.h"
#include <iostream>
#include <string>
//#include <svapi.h>
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../base/des.h"

#include "ChineseCodeLib.h"

//#include "../../base/GetInstallPath.h"

//�Ƿ������˷���
#define Tuopu


using namespace std;

//�ַ����滻(�ݹ��滻)
string ReplaceStdString(string strIn, string strFrom, string strTo)
{
	string strTmp = strIn;
	int nPos = strIn.find(strFrom, 0);
	int nLength = strFrom.length();

	if(nPos != -1)
	{
		strTmp = strIn.replace(nPos, nLength, strTo);
		strIn = strTmp;
		strTmp = ReplaceStdString(strIn, strFrom, strTo);
		//strTmp = ReplaceStdString(strTmp, strFrom, strTo);
	}
	
	return strTmp;
}

string FuncGetDataByPostMethod()
{
	char *cl;
	int sum;
	
	cl=getenv("CONTENT_LENGTH");
	string strGet = "";	
	
	if (cl)
	{
		sum = atoi(cl) + 1;
		
		char * buffer = NULL;
		buffer = (char *)malloc(sum);
		
		if(!buffer)
			return strGet;
		memset(buffer, 0, sum);
		
		fgets(buffer, sum, stdin);

		strGet = buffer;		
		
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
	}

	return strGet;
}

void WriteLog(char *app)
{
	//FILE *fp;
	//fp=fopen("c:\\echo.txt","a+");
	//fprintf(fp,app);
	//fclose(fp);
}

static void PrintEnv(char *label, char **envp)
{
	int i;
    FCGI_printf("%s:<br>\n<pre>\n", label);
 
	for ( i = 0; envp[i]; ++i)
	{
		//putenv(envp[i]);
		FCGI_printf("%s\n", envp[i]);
	
    }
    FCGI_printf("</pre><p>\n");
}

int count = 0;
BOOL AcceptPrintf(char * pidEventName)
{
	char **initialEnv = environ;
	SYSTEMTIME mytime;

	WriteLog("befor accept");
	if(FCGI_Accept()>=0)
	{

		char  wcookie[256];
		char *qrystr;
		char  *p;
		char  *p1;
		int   nSvsid;
		int   nUserid = 0;
		
		char ** myenviron;
		myenviron =FCGI_GetEnv();
	
		char myenviron1[4096]={0};

		
		for(int i=0 ;myenviron[i];++i)
		{
			strcpy(myenviron1,myenviron[i]);
			putenv(myenviron[i]);
		}

		//Get��ʽ
		qrystr=getenv("HTTP_COOKIE");

		if(qrystr)
		{
			if(strlen(qrystr)>0)
			{
				sprintf(wcookie,"%s",qrystr);
				p=strstr(wcookie,"svsid=");
				if(p!=NULL)
				{
					sscanf(p,"svsid=%d",&nSvsid);
				}

				p1=strstr(wcookie,"userid=");
				if(p1!=NULL)
				{
					sscanf(p1,"userid=%d",&nUserid);
				}

			}
		}
		
		char *cgetstr;
		cgetstr=getenv("QUERY_STRING");
		if(cgetstr)
		{
			//Ϊʲô��...
			//if(strlen(cgetstr)>0)
			//	Sleep(5000);
		}

		//OutputDebugString("--------------FuncGetDataByPostMethod-------------------\n");
		//Post��ʽ
		//string strPost = FuncGetDataByPostMethod();
		//Get��ʽ
		string strGet = cgetstr;
		//OutputDebugString("qrystr: ");
		//OutputDebugString(strGet.c_str());
		//OutputDebugString("\n");
		
		string strPageid;
		string strVersion;
		string strMode = "Tuopu";
		string strUsrleader = "1";		
		string strSVFlag = "", strIsWeixiu = "0";

	//ȡ����ֵ pageid version
#if 1		
		CSVQueryString strQuery(strGet.c_str());
		strPageid = strQuery.Get_KeyValue("pageid");
		strVersion = strQuery.Get_KeyValue("version");
#else
		string strPageid;
		strPageid = "11";
#endif		

	 //ȡ����ֵ maintain usrleader svflag isweixiu
#ifdef	 Tuopu
	
#else
	strMode = strQuery.Get_KeyValue("maintain");
	strUsrleader = strQuery.Get_KeyValue("usrleader");
	strSVFlag = strQuery.Get_KeyValue("svflag");
	strIsWeixiu = strQuery.Get_KeyValue("isweixiu");
	//strMode = "1";
	//if(nUserid != 0)
	//	strUser = "0";
	//else
	//	strUser = "1";
#endif			

	//�޸�maintain.ini, �Լ�¼�޸ĵ�shape
	//OutputDebugString(strSVFlag.c_str());
	//OutputDebugString(strUsrleader.c_str());
	if(strSVFlag != "")
	{
		string strSvflagTmp;
		CChineseCodeLib::UTF_8ToGB2312(strSvflagTmp,(char *) strSVFlag.c_str(),  strSVFlag.length());
		WriteIniFileString(strPageid, strSvflagTmp, strIsWeixiu, "maintain.ini");
	}

	//OutputDebugString(strPageid.c_str());
	string strDataXmlPath = "";
	string strMakaDataPath = "";
	string strParam = "";
	
	//ִ�и������ݵ�exe������Ҫ��ʾ��htm�ĳ���
	strDataXmlPath = "\"";
	strDataXmlPath += GetSiteViewRootPath();
#ifdef	 Tuopu
		strDataXmlPath += "\\htdocs\\tuoplist";
#else
		if(strUsrleader != "1")
		{
			strDataXmlPath += "\\htdocs\\maintainlist";
		}
		else
		{
			strDataXmlPath += "\\htdocs\\maintainleaderlist";
		}
#endif	

		strDataXmlPath += "\\" ;
		strDataXmlPath += strPageid.c_str();
		strDataXmlPath += ".files";
		strDataXmlPath += "\\data.xml\"";
		
#ifdef	 Tuopu
		strParam += strDataXmlPath;
		strParam+= " \"";
		strParam+= strVersion;
		strParam+= "\" \"";
		strParam+= strPageid.c_str();
		strParam+= "\"";		
#else
		strParam += strDataXmlPath;
		strParam+= " \"";
		strParam+= strVersion;
		strParam+= "\" \"";
		strParam+= strPageid.c_str();
		strParam+= "\" \"";

		//IsMaintain
		strParam+= strMode.c_str();
		strParam+= "\" \"";
		
		//IsLeader
		strParam+= strUsrleader.c_str();
		strParam+= "\"";
#endif	

		strMakaDataPath =  GetSiteViewRootPath() + "\\fcgi-bin\\maketuopudata.exe ";
		//strMakaDataPath =  "C:\\Program Files\\Apache Group\\apache2\\cgi-bin\\maketuopudata.exe ";

		strMakaDataPath	+= strParam;

		//strMakaDataPath	+= " 1";

		//OutputDebugString("strDataXmlPath\n");
		//OutputDebugString(strDataXmlPath.c_str());
		//OutputDebugString("\n");

		//OutputDebugString("strMakaDataPath\n");
		//OutputDebugString(strMakaDataPath.c_str());
		//OutputDebugString("\n");

		//system("C:\\Program Files\\Apache Group\\apache2\\cgi-bin\\maketuopudata.exe");
		//system(strMakaDataPath.c_str());
		
		//����Ҫ�õ�js��htm��
		DWORD dwAttr ;
		string strSource, strDest;
		
	//������frameset.js��main_2.htm��widgets.htm���ļ���tuopu �ļ�Ŀ¼
	#ifdef	 Tuopu
		strSource = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\bak\\frameset.js";
		strDest = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\";
	#else
		if(strUsrleader != "1")
		{
			strSource = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\bak\\frameset.js";
			strDest = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\";
		}
		else
		{
			strSource = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\bak\\frameset.js";
			strDest = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\";
		}
	#endif

		strDest += strPageid.c_str();
		strDest += ".files";
		strDest += "\\frameset.js";
		CopyFile(strSource.c_str(), strDest.c_str(), FALSE);

	#ifdef	 Tuopu
		strSource = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\bak\\main_2.htm";
		strDest = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\";
	#else
		if(strUsrleader != "1")
		{
			strSource = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\bak\\main_2.htm";
			strDest = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\";
		}
		else
		{
			strSource = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\bak\\main_2.htm";
			strDest = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\";
		}
	#endif

		strDest += strPageid.c_str();
		strDest += ".files";
		strDest += "\\main_2.htm";


		CopyFile(strSource.c_str(), strDest.c_str(), FALSE);

	
	//����Ҫ�ٿ���widgets.htm��../tuoplist/strPageid.files�£� ��Ϊԭ����Ϊ�˻ر��˶�ҳ����ſ����Ѿ����ƺõ�widgets.htm�ġ�
	//��ԭ����widgets.htm��load�����ToggleNav()����������ߵĹ������� ����û�����أ� Ҳû��̫��Ӱ�죬 ��ʱ�����޸ġ�...
	//#ifdef	 Tuopu
	//	strSource = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\bak\\widgets.htm";
	//	strDest =  GetSiteViewRootPath() + "\\htdocs\\tuoplist\\";
	//#else
	//	if(strUsrleader != "1")
	//	{
	//		strSource = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\bak\\widgets.htm";
	//		strDest =  GetSiteViewRootPath() + "\\htdocs\\maintainlist\\";
	//	}
	//	else
	//	{
	//		strSource = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\bak\\widgets.htm";
	//		strDest =  GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\";
	//	}
	//#endif								

	//	strDest += strPageid.c_str();
	//	strDest += ".files";
	//	strDest += "\\widgets.htm";
	//	CopyFile(strSource.c_str(), strDest.c_str(), FALSE);

		//ִ��maketuopu�Ը���data.cml �� vm_%s.html
		STARTUPINFO  si;  
		ZeroMemory(&si,  sizeof(si));  
		si.cb  =  sizeof  STARTUPINFO;  		 
		PROCESS_INFORMATION  pi;  

		BOOL res = CreateProcess(NULL,  			
			(LPSTR)strMakaDataPath.c_str(),  //  ִ�����  dos  ����  
			NULL,  
			NULL,  
			NULL,  
			NORMAL_PRIORITY_CLASS  |  CREATE_NO_WINDOW,  
			NULL,  
			NULL,  
			&si,  
			&pi);
		 
		DWORD rc = WaitForSingleObject(pi.hProcess, INFINITE); 

		if(rc != WAIT_FAILED)
		{		
			if(true  ==  res)  
			{  
				CloseHandle(pi.hProcess);  
				CloseHandle(pi.hThread);  
			}
		}

		//������Ϣ
		string strMsg;
		printf("Content-type: text/html\r\n");
		printf("Set-Cookie: svsid=%d\r\n" ,nSvsid );
		printf("Set-Cookie: userid=%d\r\n" ,nUserid);
		//OutputDebugString("strLocationPath\n");
		//printf("Set-Cookie:svsid=%d&userid=%s;\r\n" ,nSvsid,"");
		printf("\r\n");

		string strHtmlPath = "";
		string strTuopufilePath = "";

	#ifdef	 Tuopu
		string strLocationPath = "location.href=\"/tuoplist/";		
		strHtmlPath = "..\\htdocs\\tuoplist\\";
		strTuopufilePath = "..\\htdocs\\tuoplist\\";
	#else
		string strLocationPath = "";
		if(strUsrleader != "1")
		{		
			strLocationPath = "location.href=\"/maintainlist/";
			strHtmlPath = "..\\htdocs\\maintainlist\\";
			strTuopufilePath = "..\\htdocs\\maintainlist\\";
		}
		else
		{
			strLocationPath = "location.href=\"/maintainleaderlist/";
			strHtmlPath = "..\\htdocs\\maintainleaderlist\\";
			strTuopufilePath = "..\\htdocs\\maintainleaderlist\\";
		}
	#endif	
		
		strLocationPath += strPageid.c_str();
		strLocationPath += ".files/main_2.htm\"";

		strHtmlPath += strPageid.c_str();
		strHtmlPath += ".files\\main_2.htm";

		strTuopufilePath += strPageid.c_str();
		strTuopufilePath += ".htm";

		//OutputDebugString("strLocationPath\n");
		//OutputDebugString(strLocationPath.c_str());
		//OutputDebugString("\n");

		//��ת(��ʱ�����ˣ�����Ϊ��ת֮���޷��ֶ�ˢ�£������Ը�Ϊ��main_2.htmֱ��printf�����������Ƶ�½ҳ�������)
		//printf("<script>");		
		//printf(strLocationPath.c_str());
		//printf("</script>");
		
		string strReplaceId = "";		
		string strContent = "";		
		string strContentTmp = "";	

		string strGfileList = "";

		//��ȡ../tuoplist/�µ�strPageid.htm���var g_FileList  �����滻../tuoplist/strPageid.files/main_2.htm���var g_FileList��ֵ��
		FCGI_FILE * tuopufile = FCGI_fopen(strTuopufilePath.c_str(), "read");
		if(tuopufile != NULL)
		{
			//html����
			int len = 0;
			char tempBuffer[2048] = {0};
			if((len = fread(tempBuffer, 1, 2047, tuopufile)) > 0) 
			{
				strContent = tempBuffer;

				//��ȡ../tuoplist/�µ�strPageid.htm���var g_FileList
				//"new FileEntry" Ϊ��ʼ  ");" Ϊ����
				int nStartPos = strContent.find("new FileEntry");
				int nEndPos = strContent.find(");");

				strGfileList = strContent.substr(nStartPos, nEndPos - nStartPos);

				//OutputDebugString("strGfileList\n");
				//OutputDebugString(strGfileList.c_str());
				//OutputDebugString("\n");

				memset(tempBuffer, 0, 2048);
			}
			
			FCGI_pclose(tuopufile);
		}

		strReplaceId = "";		
		strContent = "";		
		strContentTmp = "";	

		FCGI_FILE * loginfile = FCGI_fopen(strHtmlPath.c_str(), "read");
		if(loginfile != NULL)
		{
			//html����
			int len = 0;
			char tempBuffer[1024] = {0};
			while ((len = fread(tempBuffer, 1, 1023, loginfile)) > 0) 
			{
				strContent = tempBuffer;
				
				//����main_2.html�е�mulu.filesΪָ�����˵���ȷ�ļ�·�����ݹ��滻��
				#ifdef	 Tuopu
					strReplaceId = "../tuoplist/";
					strReplaceId += strPageid.c_str();
					strReplaceId += ".files/";
					strContentTmp = ReplaceStdString(strContent, "../tuoplist/mulu.files/", strReplaceId);
					
					//��strPageid.htm���var g_FileList���滻../tuoplist/strPageid.files/main_2.htm���var g_FileList��ֵ��
					strContent = ReplaceStdString(strContentTmp, "ReplaceFileEntry", strGfileList);
					strContentTmp = strContent;
				#else
					if(strUsrleader != "1")
					{
						strReplaceId = "../maintainlist/";
						strReplaceId += strPageid.c_str();
						strReplaceId += ".files/";
						strContentTmp = ReplaceStdString(strContent, "../maintainlist/mulu.files/", strReplaceId);
						
						//��strPageid.htm���var g_FileList���滻../tuoplist/strPageid.files/main_2.htm���var g_FileList��ֵ��
						strContent = ReplaceStdString(strContentTmp, "ReplaceFileEntry", strGfileList);
						strContentTmp = strContent;
					}
					else
					{
						strReplaceId = "../maintainleaderlist/";
						strReplaceId += strPageid.c_str();
						strReplaceId += ".files/";
						strContentTmp = ReplaceStdString(strContent, "../maintainleaderlist/mulu.files/", strReplaceId);
						
						//��strPageid.htm���var g_FileList���滻../tuoplist/strPageid.files/main_2.htm���var g_FileList��ֵ��
						strContent = ReplaceStdString(strContentTmp, "ReplaceFileEntry", strGfileList);
						strContentTmp = strContent;
					}
				#endif	
			
				printf(strContentTmp.c_str());					
				
				memset(tempBuffer, 0, 1024);
			}			

			FCGI_pclose(loginfile);
		}

		FCGI_Finish();
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#define  SITEVIEW

int main (int argc,char *argv[])
{
#ifdef SITEVIEW
	char pidEventName[256];

	HANDLE hevnt;
	sprintf(pidEventName,"SiteView-Cgi-Event-%d",GetCurrentProcessId());	
	hevnt= CreateEvent(NULL,TRUE,FALSE,pidEventName);
	//ResetEvent(hevnt);
/*	
	while(1)
	{
		if(argc==1)
		{
			//WaitForSingleObject(hevnt,10000);
			//ResetEvent(hevnt);
			WriteLog("  wait hevent success\n");		
		}

		if(!AcceptPrintf(pidEventName)) 
			break;
	}*/

	DWORD ret=WaitForSingleObject(hevnt,10000);
	ResetEvent(hevnt);
	AcceptPrintf(pidEventName);
#else

	
#endif		
		
    return 0;
}

//��δ���...
//1��дCookie