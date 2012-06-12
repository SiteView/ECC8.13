/*
 * echo.c --
 *
 *	Produce a page containing all FastCGI inputs
 *
 *
 * Copyright (c) 1996 Open Market, Inc.
 *
 * See the file "LICENSE.TERMS" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */
#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

//#include "fcgi_config.h"
#include "fcgi_config_x86.h"

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
//#include <time.h>
#include <string.h>
#include <windows.h>

#include "../../Base/SVQueryString.h"
#include <iostream>
#include <string>
//#include <svapi.h>
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../../base/des.h"
#include "../base/OperateLog.h"

#include "algorithm"
#include "functional"
#include "ctype.h"

using namespace std;

#include "../../kennel/svdb/libutil/time.h"
using namespace svutil;

#include "../../tools/usbdog/doglib/safedog.h"

//#define ShanTou

#define IDC_Version

//#ifdef ShanTou
string strIsEipVlaue = "";
//#endif

#include "MD5.h"

#include "../../base/stlini.h"

void WriteLog(const char *app)
{
	//FILE *fp;
	//fp=fopen("c:\\echo.txt","a+");
	//fprintf(fp,app);
	//fclose(fp);
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

//验证用户
bool IsLogin(string strAccount, string strPwd,char* strUserId)
{
	OutputDebugString("IsLogin");
	OutputDebugString("\n");

	WriteLog("IsLogin");
	WriteLog("\n");
	//去空格
	strAccount.erase(strAccount.begin(),strAccount.begin() + strAccount.find_first_not_of('+'));
	strAccount.erase(strAccount.begin(),strAccount.begin() + strAccount.find_first_not_of(' '));
	strAccount.erase(strAccount.begin() + strAccount.find_last_not_of('+') + 1,strAccount.end());
	strAccount.erase(strAccount.begin() + strAccount.find_last_not_of(' ') + 1,strAccount.end());
	
	//转换成小写
	transform(strAccount.begin(),strAccount.end(),strAccount.begin(),(int(*)(int))tolower);	

	if(strAccount == "" && strPwd == "")
		return false;

	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName, strUserPwd;
	bool bExist = false;
	//从ini获取用户列表
	#ifdef IDC_Version
		if(GetIniFileSections(keylist, "idcuser.ini"))
	#else
		if(GetIniFileSections(keylist, "user.ini"))
	#endif
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据			
			#ifdef IDC_Version
				strUserName = GetIniFileString((*keyitem), "LoginName", "", "idcuser.ini");
			#else
				strUserName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");
			#endif

			
			//转换成小写
			transform(strUserName.begin(),strUserName.end(),strUserName.begin(),(int(*)(int))tolower);
			#ifdef IDC_Version
				strUserPwd = GetIniFileString((*keyitem), "Password", "", "idcuser.ini");	
			#else
				strUserPwd = GetIniFileString((*keyitem), "Password", "", "user.ini");	
			#endif
			
			Des mydes;
			char dechar[1024]={0};
			if(strPwd.size()>0)
			{
				mydes.Decrypt(strUserPwd.c_str(),dechar);
				strUserPwd =  dechar;
			}
			
		//汕头版本 用MD5解密strUserPwd
		#ifdef ShanTou
			if(strIsEipVlaue == "true")
			{

				//OutputDebugString(strUserPwd.c_str());	
				//OutputDebugString("\n");
				
				WriteLog(strUserPwd.c_str());	
				WriteLog("\n");
				
				string strTmpPwd = strUserPwd;
				//strTmpPwd = "test";

				int ilen = strTmpPwd.length();
				unsigned char output[16];
				MD5(output, (const unsigned char *)strTmpPwd.c_str(), ilen);
				
				strUserPwd = "";

				//strPwd = output;			
				//strUserPwd.append((char*)output);
				//OutputDebugString((char*)output);

				char tmpbuf[2];
				for(int i =0; i< 16;i++)
				{
					sprintf(tmpbuf, "%02x", output[i]);										
					//WriteLog((char*)tmpbuf);
					strUserPwd.append((char*)tmpbuf);
				}			
				
				for(int i=0;i<strUserPwd.length();i++)
				{
					strUserPwd[i]=toupper(strUserPwd[i]);
				}
				//OutputDebugString(strUserPwd.c_str());
				//OutputDebugString("\n");
				WriteLog(strUserPwd.c_str());	
				WriteLog("\n");

			}
			else
			{
			
			}				
			if(strUserName == strAccount && strUserPwd == strPwd)
		#else
			if(strUserName == strAccount && strUserPwd == strPwd)
		#endif
			{
				//是否禁用？...
			#ifdef IDC_Version
				int nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, "idcuser.ini");
			#else
				int nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, "user.ini");
			#endif
				
				if(nIsUse == -1)
				{
					//禁用
					bExist = false;
				}
				else
				{
					//可用
					bExist = true;
					sprintf(strUserId,"%s",keyitem->c_str());
					//strUserId=keyitem->c_str();
				}

				//bExist = true;
				break;
			}
		}
	}

	return bExist;	
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

string& replace_all_distinct(MAPNODE ResNode, string& str,
							 const string& old_value)
{
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
					nRes = static_cast<int>(strRes.length());
					bChange = true;
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
		bChange = false;
	}

	FCGI_printf(str.c_str());
	return str;
}

string& replace_all_error(MAPNODE ResNode, string& str,
							 const string ids_name)
{
	string strRes = "";
	int nRes = 1;

	bool bChange = false;
	for(string::size_type pos(0); pos!=string::npos; pos+=nRes) 
	{
		if( (pos=str.find("&nbsp;&nbsp;",pos))!=string::npos )
		{
			if(FindNodeValue(ResNode, ids_name, strRes))
			{
				str.replace(pos, pos + 12, strRes);
				nRes = static_cast<int>(strRes.length());
				bChange = true;
			}
			else
			{
				nRes = 1;
				break;
			}
		}
		else 
		{
			nRes = 1;
			break;
		}
	}
	if(bChange)
	{
		bChange = false;
	}

//	FCGI_printf(str.c_str());
	return str;
}

int count = 0;
BOOL AcceptPrintf(char * pidEventName)
{
	char **initialEnv = environ;
	SYSTEMTIME mytime;

	//read from register to obtain ECC web root path, usually:  c:\siteview\siteview ecc\fcg-bin
	std::string szPath = GetSiteViewRootPath();
	szPath += "\\data\\svdbconfig.ini";

	INIFile theINI = LoadIni(szPath.c_str());

	//set language code (English or Chinese)
	std::string szTSec = GetIniSetting(theINI, "svdb", "DefaultLanguage");
	szTSec += "_code";
	std::string m_code = GetIniSetting(theINI, "svdb", szTSec.c_str());

	//WriteLog("before accept");
	if(FCGI_Accept()>=0)
	{

		char  wcookie[256];
		char *qrystr;
		char  *p;
		int   nSvsid;
		

		//char szWrite[256];

		char ** myenviron;
		myenviron =FCGI_GetEnv();
	
		char myenviron1[4096]={0};

		
		for(int i=0 ;myenviron[i];++i)
		{
			strcpy(myenviron1,myenviron[i]);
			putenv(myenviron[i]);
		}

		//check if the remoteIP is allowed to log into the system
		std::string strAcceptIp;
		strAcceptIp = GetIniFileString("IPCheck","IPAddress","", "general.ini");
		int nIsChecked;
		nIsChecked = GetIniFileInt("IPCheck","isCheck",0, "general.ini");
		char *ca,*cb,*cc;
		char *szAcceptIp;
		int nSize;
		

		char *remoteip=NULL;
		remoteip = getenv("REMOTE_ADDR");
		OutputDebugString(remoteip);
		OutputDebugString("\n");
		
		bool bAccept =false;
		nSize = static_cast<int>(strAcceptIp.size());

		if( (nIsChecked==1)&&(nSize>0)&&(remoteip!=NULL) )
		{
			
			szAcceptIp = new char[nSize+1];
			memset(szAcceptIp,0,nSize);
			strcpy(szAcceptIp,strAcceptIp.c_str());
			
			//remoteip = "192.168.5.6";
			//remoteip = "127.0.0.1";
			if(strcmp(remoteip,"127.0.0.1")!=0)
			{
				ca =szAcceptIp;
				//cb =szAcceptIp;
				//cc =szAcceptIp;
				while(ca)
				{
					cb= strchr(ca,',');
					if(cb)
							*cb=0;
					cc= strchr(ca,'*');
					if(cc)
							*cc=0;
					if(strstr(remoteip,ca) !=NULL)
					{
						bAccept= true;
					}
					if(!cb||bAccept==true)
						break;
					if(cb)
						ca=cb+1;
				}

			}else bAccept= true;
			delete(szAcceptIp);
		}
		else bAccept =true;//no need to check IP

			
		//Get方式
		qrystr=getenv("HTTP_COOKIE");
		nSvsid =0;
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
			}
		}

		if(nSvsid==0)
			nSvsid =GetCurrentProcessId();
		//Post方式
		string strPost = FuncGetDataByPostMethod();
		
		WriteLog("poststring:\n");
		WriteLog(strPost.c_str());

		//取值 
#if 1
		CSVQueryString strQuery(strPost.c_str());
		string strAccountVlaue;
		string strPwdVlaue ;
		
		#ifdef ShanTou
			strAccountVlaue= strQuery.Get_KeyValue("Account");
			strPwdVlaue = strQuery.Get_KeyValue("Password");
			strIsEipVlaue = strQuery.Get_KeyValue("IsEip");
		#else
			strAccountVlaue= strQuery.Get_KeyValue("Account");
			strPwdVlaue = strQuery.Get_KeyValue("Password");
		#endif

#else
		string strAccountVlaue="admin";
		string strPwdVlaue  ="1111" ;
#endif
		
		string str = "";
		//验证
		char strUserId[20];
		if((bAccept==false) || !IsLogin(strAccountVlaue.c_str(), strPwdVlaue.c_str(),strUserId))
		{//用户名/密码认证失败
			//标准头
			printf("Content-type: text/html charset=gb2312 \r\n");
			printf("Content-Language: zh-CN\r\n");
			printf("Set-Cookie: svsid=%d\r\n" ,nSvsid   );
			printf("\r\n");			
			if(strIsEipVlaue == "true")
			{
				printf("User Account Or Passsword is Error!");
			}
			else
			{
				printf("nameerror");
			}

			return FALSE;

		}
		else //用户名/密码登陆成功
		{
			SafeDog pSafeDog;

			bool IsDogExit=false;
			if(pSafeDog.DogOnUsb(IsDogExit) == 0)
			{
				if(IsDogExit == true)
				{//加密狗认证失败
					TTime mStopTime;
					if(pSafeDog.GetStopTime(mStopTime) == 0 )
					{
						TTime mNowTime;
						mNowTime = TTime::GetCurrentTimeEx();	
						
						if(mStopTime < mNowTime)
						{//过期了
							//标准头
							printf("Content-type: text/html charset=gb2312 \r\n");
							printf("Content-Language: zh-CN\r\n");
							printf("Set-Cookie: svsid=%d\r\n" ,nSvsid   );
							printf("\r\n");

							if(strIsEipVlaue == "true")
							{
								printf("System Is OverDue!");
							}
							else
							{
								printf("sysout");
							}
							
							return FALSE;
						}
					}
					else
					{
						Des OneDes;
						char strDes[1024]={0};
						std::string strDataNum = GetIniFileString("license", "starttime", "",  "general.ini");
						if(strDataNum.size()>0)
						{
							if( OneDes.Decrypt(strDataNum.c_str(),strDes) )
							{
								strDataNum=strDes;
								if(!strDataNum.empty())
								{
									std::string LastData = GetIniFileString("license", "lasttime", "",  "general.ini");
									if(!LastData.empty())
									{
										if( OneDes.Decrypt(LastData.c_str(),strDes) )
										{
											LastData=strDes;
											TTime mStopTime(atoi(strDataNum.substr(0,4).c_str()),atoi(strDataNum.substr(5,2).c_str()),atoi(strDataNum.substr(8,2).c_str()),0,0,0);
											TTimeSpan AddData(atoi(LastData.c_str()),0,0,0);
											mStopTime += AddData;

											TTime mNowTime;
											mNowTime = TTime::GetCurrentTimeEx();	
											
											if(mStopTime < mNowTime)
											{
												//标准头
												printf("Content-type: text/html charset=gb2312 \r\n");
												printf("Content-Language: zh-CN\r\n");
												printf("Set-Cookie: svsid=%d\r\n" ,nSvsid   );
												printf("\r\n");
												if(strIsEipVlaue == "true")
												{
													printf("System Is OverDue!");
												}
												else
												{
													printf("sysout");
												}
												return FALSE;
											}
										}
									}
								}
							}		
						}
					}		
				}
				IsDogExit=false;
			}
			else
			{
				Des OneDes;
				char strDes[1024]={0};
				std::string strDataNum = GetIniFileString("license", "starttime", "",  "general.ini");

				if(strDataNum.size()>0)
				{
					if( OneDes.Decrypt(strDataNum.c_str(),strDes) )
					{
						strDataNum=strDes;
						if(!strDataNum.empty())
						{
							std::string LastData = GetIniFileString("license", "lasttime", "",  "general.ini");

							if(!LastData.empty())
							{
								if( OneDes.Decrypt(LastData.c_str(),strDes) )
								{
									LastData=strDes;
                                    int nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMin = 0, nSec = 0;
									sscanf(strDataNum.c_str(), "%d-%d-%d", &nYear, &nMonth, &nDay);
									char buf[100]={0};
									sprintf(buf,"year:%d,mouth:%d,day:%d\n",nYear,nMonth,nDay);

									TTime mStopTime(nYear, nMonth, nDay, 0,0,0);
								   
    							    TTimeSpan AddData(atoi(LastData.c_str()),0,0,0);
									mStopTime += AddData;

									TTime mNowTime;
									mNowTime = TTime::GetCurrentTimeEx();	
									
									if(mStopTime < mNowTime)
									{
										//标准头
										printf("Content-type: text/html charset=gb2312 \r\n");
										printf("Content-Language: zh-CN\r\n");
										printf("Set-Cookie: svsid=%d\r\n" ,nSvsid   );
										printf("\r\n");
										if(strIsEipVlaue == "true")
										{
											printf("System Is OverDue!");
										}
										else
										{
											printf("sysout");
										}
										return FALSE;
									}
								}
							}
						}
					}
				}
			}
			
			//登陆成功
			printf("Content-type: text/html\r\n");
			printf("Set-Cookie: svsid=%d\r\n" ,nSvsid );
			#ifdef IDC_Version			
				string strIdcUserId = GetIniFileString(strUserId, "IdcUserId", "", "idcuser.ini");	
				printf("Set-Cookie: idcuserid=%s\r\n" ,strIdcUserId.c_str());
			#endif	
			printf("Set-Cookie: userid=%s\r\n" ,strUserId);

			printf("\r\n");

			if(strIsEipVlaue == "true")
			{
				printf("<script type='text/javascript'>");
				printf("location.replace(\"/fcgi-bin/showhtm.cgi?nav.htm\")");
				printf("</script>");		
			}
			else
			{
				printf("true");
			}
			
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
/*
	HANDLE hevnt;
	sprintf(pidEventName,"SiteView-Cgi-Event-%d",GetCurrentProcessId());	
	hevnt= CreateEvent(NULL,TRUE,FALSE,pidEventName);

	DWORD ret=WaitForSingleObject(hevnt,10000);
	ResetEvent(hevnt);
*/

	AcceptPrintf(pidEventName);
#else

	
#endif		
		
    return 0;
}

//尚未完成...
//1、写Cookie