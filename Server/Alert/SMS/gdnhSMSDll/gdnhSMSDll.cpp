// gdnhSMSDll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

//#include "Winsock2.h"
#include "shlwapi.h"

#define OTL_ODBC
#include "otlv4.h"

#pragma comment(lib,"odbc32.lib")


//#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"shlwapi.lib")

struct app_init
{
public:
    app_init()
    {
		otl_connect::otl_initialize();
    }
    ~app_init()
    {
    }
};

struct app_init _init;

void error_log(char *s,...)
{
	va_list argptr;
	char tcBuf[1024];

	va_start(argptr, s);

	vsprintf(tcBuf,s,argptr);
	printf(_T("%s"),tcBuf);

	va_end(argptr);

	char tFileName[MAX_PATH];
	::GetModuleFileName(NULL,tFileName,MAX_PATH);

	PathRemoveFileSpec(tFileName);
	
	SYSTEMTIME syTm;
	::GetLocalTime(&syTm);

	sprintf(tFileName,"%s\\SmsLog.txt",tFileName);


	FILE *f = fopen(tFileName,_T("a+"));


	if (NULL != f)
	{

		fprintf(f,"%02d-%02d %02d:%02d:%02d %u %s\n",syTm.wMonth,syTm.wDay,syTm.wHour,syTm.wMinute,syTm.wSecond,GetTickCount(),tcBuf);

		fclose(f);
	}

	
}


#define ERR_LOG error_log
#define DEBUG_LOG

string	g_strIP = "10.151.178.29";
int		g_iPort = 1521;
string	g_strDbName = "swydyx1";
string  g_strDbUser = "SMS";
string	g_strDBPwd = "SMS";
//string  g_strConn = "SMS/SMS@swydyx1";
string  g_strConn = "system/manager@sms";
int		g_msglen = 40;


void String2Array(std::vector<std::string> &vOut,string strIn,string strDiv)
{
	int pos1= 0,pos2 = 0;

	while(1)
	{
		pos2 = strIn.find(strDiv, pos1);

		if (pos2 < 0)
		{
			vOut.push_back(strIn.substr(pos1, strIn.length() -pos1));
			break;
		}
		
		vOut.push_back(strIn.substr(pos1, pos2 -pos1));
		
		pos1 = pos2 +1;
		pos2 = pos1;

	}
	
}

int process_msg(std::vector<std::string> &vOut,string strIn,string strFmt)
{
	string strMsg = strIn;

	std::vector<std::string> vTmp;

	if (strMsg.size() > g_msglen+4)
	{
		
		int i = 1;
		while(strMsg.size() > 0)
		{

			int count = 0;
			bool split = false;
			string strtmp;

			while(count < strMsg.size())
			{
				unsigned char c = strMsg[count];

				strtmp.push_back(c);

				if (c > 128)
					split = !split;

				++count;

				if ((count==g_msglen-1))
				{
					if (!split)
						break;
					else
					{
						strtmp.push_back(strMsg[count]);
						++count;
						break;
					}
				}

			}

			strMsg.erase(0,strtmp.size());
			vTmp.push_back(strtmp);
		}
		
		for(int i=0; i < vTmp.size(); i++)
		{
			char szTmp[512];

			if (strFmt.size() > 0)
			{
				sprintf(szTmp, strFmt.c_str(), vTmp.size(),i+1,vTmp[i].c_str());
				vOut.push_back(szTmp);
			}else
			{
				vOut.push_back(vTmp[i]);
			}
		}
		vTmp.clear();

	}else
	{
		vOut.push_back(strIn);
	}
	return 1;
}


int read_config()
{
    char szPath[MAX_PATH];
	char szConn[128];

    ::GetModuleFileName(NULL, szPath, MAX_PATH);

    PathRemoveFileSpec(szPath);

    strcat(szPath,"\\smsconfig.ini");

    //DEBUG_LOG("读取配置文件:%s", szPath);

    ::GetPrivateProfileString("SMS","conn_string","",szConn,127,szPath);
    g_msglen = ::GetPrivateProfileInt("SMS","sms_length",0,szPath);

	g_strConn = szConn;

    
    return 0;
}

int SendSms(char *szSMTo, char *szContent)
{
	int ret = -1;

	if (!szSMTo || !szContent)
		return -1;

	string strMsg = szContent;
	string strTo = szSMTo;
	std::vector<std::string> vMobiles;
	std::vector<std::string> msgs;

	String2Array(vMobiles,strTo,std::string(","));

	process_msg(msgs, strMsg,"");

	otl_connect db;

	try
	{
		db.rlogon(g_strConn.c_str());

		for (std::vector<std::string>::iterator i = vMobiles.begin(); i != vMobiles.end(); i++)
		{
			for(std::vector<std::string>::iterator j = msgs.begin(); j != msgs.end(); j++)
			{
				
				
				otl_stream s(1,"insert into Italarm(smscode,context) values(:mobile<varchar,in>,:msg<varchar,in>)",db);

				s.set_commit(0);

				otl_long_string mobile(i->c_str(),0,i->size());
				otl_long_string msg(j->c_str(), 0,j->size());

				s<<mobile<<msg;

				/*
				int iTry = 0;
				while(iTry++<5)
				{
					Sleep(1000);

					otl_stream r(1,"begin SWYD.KF_P_SMS_RESULT_FOR_DYH(:sendid<varchar,in>,:result<varchar,out>);end;",db);
					r.set_commit(0);
					
					otl_long_string result;
					string strtmp;

					r<<sendid;
					r>>result;

					strtmp = (const char *)result.v;

					if (strtmp.size() <= 0)
						continue;

					if (strtmp.compare("0") == 0)
					{
						break;
					}
					else
					{
						otl_exception e;
						e.init((const char*)result.v,-99);
						throw e;
					}
				}
				*/
			}
		}


		ret = 0;

	}catch(otl_exception& p) 
    {  
        // intercept OTL exceptions  
		ERR_LOG("%s",p.msg); // print out error message  
        ERR_LOG("%s",p.stm_text); // print out SQL that caused the error  
		db.rollback();
		ret = -2;
    } 

	db.logoff();

	vMobiles.clear();
	msgs.clear();


	return ret;
}

extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "SQLServer短信发送DLL";
	return 1;
}

//动态链接库的入口
//funname,调用的发送短信的函数
//szSMTo，短信发送给谁
//szContent,短信内容
//返回为1表示成功
extern "C" __declspec(dllexport) int run(char * szFunName, char * szSMTo, char *szContent)   
{	

    DEBUG_LOG("=====发送短信报警开始:%s",szSMTo);

	read_config();

	if (0 == SendSms(szSMTo,szContent))
		return 1;
	else
		return 0;
	return 0;
}


