#include "stdafx.h"
#include "svapi.h"
#include "../../kennel/svdb/libutil/Time.h"
#include <stdio.h>
#include <fstream>
#include "windows.h"
#include "reportgenerate.h"
//#include "jwsmtp/jwsmtp.h"

typedef bool(SendEmail)(const char *pszServer, const char *pszMailfrom, 
						const char *pszMailTo, const char *pszSubject,
						const char *pszMailContent, const char *pszUser, 
						const char *pszPassword, const char* pszAttachName);

//重写了邮件发送代码，对此工程进行相应修改
//苏合 2007-07-24
//注释下面一行 苏合 2007-07-24
//#include "../../opens/jwsmtp-1.32.13/jwsmtp/jwsmtp/jwsmtp.h"

using namespace chen;

int month[12] = {31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};

UINT hTime;

bool bSet = true;

static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent,DWORD dwTime );

void stringReplace(string & strBig, const string & strsrc, const string & strdst) {
	string::size_type pos=0;
	string::size_type srclen=strsrc.size();
	string::size_type dstlen=strdst.size();
	while( (pos=strBig.find(strsrc, pos)) != string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}

string& replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}


bool hasrun()

{

#ifdef WIN32

    HANDLE
hInstance=::CreateEvent(NULL,TRUE,FALSE,"Global\\SiteView-name-instance");

 

    if(hInstance==NULL)

    {

        puts("Create event of instance  failed");

        return false;

    }

    if(::GetLastError()==ERROR_ALREADY_EXISTS)

    {

        puts("Instance has exist");
		exit(1);
        return true;

    }

    ::SetLastError(0);

 

    return false;

#endif

 

}



int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	MSG msg;

	OUT_DEBUG("CmdLine", lpCmdLine);

	hasrun();
	//图片目录不存在则创建
	WIN32_FIND_DATA fd;
	string	szRootPath = GetSiteViewRootPath();
	string szReportPath = szRootPath;
	szReportPath += "\\htdocs\\report";

	HANDLE fr=::FindFirstFile(szReportPath.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szReportPath.c_str(), NULL);
	}

	WIN32_FIND_DATA	fd1;
	string szPath = "..\\htdocs\\report\\Images";
	HANDLE hFile=::FindFirstFile(szPath.c_str(), &fd1);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		CreateDirectory(szPath.c_str(), NULL);
	}
	::FindClose(hFile);
	string szFileFrom = "..\\htdocs\\Images\\";
	string szFileTo = "..\\htdocs\\report\\Images\\";
	string szFileFrom1, szFileTo1;
	string szIcon1 = "table_head_space.png";
	szFileFrom1 = szFileFrom + szIcon1;
	szFileTo1 = szFileTo + szIcon1;
	CopyFile(szFileFrom1.c_str(), szFileTo1.c_str(), TRUE);

	string szIcon2 = "table_shadow_left_bom.png";
	szFileFrom1 = szFileFrom + szIcon2;
	szFileTo1 = szFileTo + szIcon2;
	CopyFile(szFileFrom1.c_str(), szFileTo1.c_str(), TRUE);

	string szIcon3 = "table_shadow_right_bom.png";
	szFileFrom1 = szFileFrom + szIcon3;
	szFileTo1 = szFileTo + szIcon3;
	CopyFile(szFileFrom1.c_str(), szFileTo1.c_str(), TRUE);

	WIN32_FIND_DATA	fd2;
	string szPath2 = "..\\htdocs\\topnreport\\Images";
	HANDLE hFile2=::FindFirstFile(szPath2.c_str(), &fd2);
	if(hFile2 == INVALID_HANDLE_VALUE)
	{
		CreateDirectory(szPath2.c_str(), NULL);
	}
	::FindClose(hFile2);
	string szFileFrom2 = "..\\htdocs\\Images\\";
	string szFileTo2 = "..\\htdocs\\topnreport\\Images\\";
	string szFileFrom12, szFileTo12;
	szFileFrom12 = szFileFrom2 + szIcon1;
	szFileTo12 = szFileTo2 + szIcon1;
	CopyFile(szFileFrom12.c_str(), szFileTo12.c_str(), TRUE);

	szFileFrom12 = szFileFrom2 + szIcon2;
	szFileTo12 = szFileTo2 + szIcon2;
	CopyFile(szFileFrom12.c_str(), szFileTo12.c_str(), TRUE);

	szFileFrom12 = szFileFrom2 + szIcon3;
	szFileTo12 = szFileTo2 + szIcon3;
	CopyFile(szFileFrom12.c_str(), szFileTo12.c_str(), TRUE);

	//设定定时刷新频率:1小时
	chen::TTime time = TTime::GetCurrentTimeEx();
	int nMinuteInter = 60 - time.GetMinute();

	hTime = SetTimer(NULL,NULL,nMinuteInter*60*1000,TimerProc);
	//hTime = SetTimer(NULL, NULL, 30*1000, TimerProc);

	HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)1);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			switch(msg.message )
			{
				case WM_QUIT:
					exit(1);
				default:
					break;
			}
		}
	}

	return msg.wParam;
}


VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent,DWORD dwTime )
{
	std::list<string> sectionlist;	
	std::list<string>::iterator m_sItem;
	std::list<string> topnsectionlist;
	std::list<string>::iterator m_tItem;

	GetIniFileSections(sectionlist, "reportset.ini");//取报告名称列表
	GetIniFileSections(topnsectionlist, "topnreportset.ini");

	TTime time = TTime::GetCurrentTimeEx();
	std::string szdaystarttime; std::string szdayendtime;
	std::string szReportName;
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
	std::string szExcelName;
    //为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
	std::string szWeek;
	std::string ret = "error";

	//报告设置INI文件中取值
	std::string szListStatusResult;
	std::string szListClicket;
	std::string szListError;
	std::string szListDanger;

	//重写了邮件发送代码，对此工程进行相应修改
	//苏合 2007-07-24
	//增加一行代码，用于获取邮件发送的情况
	bool bRet = false;

	// 校验用户
	std::string strUserID = GetIniFileString("email_config", "user", ret, "email.ini");

	// 校验密码
	std::string strUserPwd = GetIniFileString("email_config", "password", ret,  "email.ini");

	//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++
	//if (strcmp(ret.c_str(), "error") == 0)
	if (strcmp(strUserPwd.c_str(), "error") == 0)
	//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++

	{// 发生了读取错误

		strUserPwd = "";
	}
	else
	{
		Des mydes;
		char deschar[1024] = {0};
		if (strUserPwd.size() > 0)
		{
			mydes.Decrypt(strUserPwd.c_str(),deschar);
			strUserPwd = deschar;
		}
	}
	
	std::string strCmdLine;
	SECURITY_ATTRIBUTES sa;	
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	
	HANDLE hRead, hWrite;

	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	si.hStdOutput = hWrite;
	si.hStdError = hWrite;
	si.wShowWindow =SW_HIDE;
	
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	int nLength=0;

	string dayReport,weekReport,monthReport;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Report_Day",dayReport);
			FindNodeValue(ResNode,"IDS_Report_Week",weekReport);
			FindNodeValue(ResNode,"IDS_Report_Month",monthReport);
		}
		CloseResource(objRes);
	}
	
	if(bSet)
	{
		KillTimer(NULL, hTime);
		SetTimer(NULL,NULL,60*60*1000,TimerProc);
		bSet = false;
	}

	for(m_tItem = topnsectionlist.begin(); m_tItem != topnsectionlist.end(); m_tItem++)
	{
		bool bGen = false;

		std::string tsection = *m_tItem;
		std::string sztGenerate = GetIniFileString(tsection, "Generate", ret, "topnreportset.ini");
		if(strcmp(sztGenerate.c_str(), "error") != 0)
		{			
			int nHour = time.GetHour();
			if(nHour == atoi(sztGenerate.c_str()))
			{
				bGen = true;
			}
		}


		std::string sztPeriod = GetIniFileString(tsection, "Period", ret, "topnreportset.ini");
		if(strcmp(sztPeriod.c_str(), "error") != 0)
		{

		}

		std::string sztDeny = GetIniFileString(tsection, "Deny", ret, "topnreportset.ini");
		if(strcmp(sztDeny.c_str(), "error") != 0)
		{
			
		}

		std::string szEmailSend = GetIniFileString(tsection, "EmailSend", ret, "topnreportset.ini");
		if(strcmp(szEmailSend.c_str(), "error") == 0)
		{
		}

		std::string szGenNum = GetIniFileString(tsection, "Count", ret, "topnreportset.ini");

		bool bReportGen = false;
		TTime dayendtime;
		TTime daystarttime;

		if(strcmp(sztDeny.c_str(), "Yes") != 0)
		{
			if(bGen)
			{
				std::string szPeriod = GetIniFileString(tsection, "Period", ret, "topnreportset.ini");
				if(strcmp(szPeriod.c_str(), dayReport.c_str()) == 0)
				{
					//往日报中写定时生成记录
					std::string szEndTime = GetIniFileString(tsection, "EndTime", ret, "topnreportset.ini");

					int pos = szEndTime.find(":", 0);
					std::string szHour = szEndTime.substr(0, pos);
					std::string szMinute = szEndTime.substr(pos + 1, szEndTime.size() - pos - 1);

					dayendtime = TTime(time.GetYear(), time.GetMonth(), time.GetDay(), atoi(szHour.c_str()), atoi(szMinute.c_str()), 0);
					daystarttime = dayendtime - TTimeSpan(1, 0, 0, 0);
					
					bReportGen = true;
				}
				
				
				else if(strcmp(szPeriod.c_str(), weekReport.c_str()) == 0)
				{
					int nret = -1;
					int nWeekDay;
					std::string sWeekDay = GetIniFileString(tsection, "WeekEndTime", ret, "topnreportset.ini");												
					
					CTime time1(CTime::GetCurrentTime());   				
					
					nWeekDay = atoi(sWeekDay.c_str());
					if((time1.GetDayOfWeek() - 1) == nWeekDay)
					{
						dayendtime = TTime(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
						daystarttime = dayendtime - TTimeSpan(7, 0, 0, 0);

						bReportGen = true;
					}
				}
				
				
				else if(strcmp(szPeriod.c_str(), monthReport.c_str()) == 0)
				{
					if(time.GetDay() == 1)
					{
						/* 2007/7/12 龚超 该段代码导致月报起始时间错误因此被注释
						TTime dayendtime;
						TTime daystarttime;
						*/

						if(time.GetMonth() == 1)
						{
							daystarttime = TTime(time.GetYear() - 1, 12, 1, 0, 0, 0);
							dayendtime = TTime(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
						}
						else
						{
							daystarttime = TTime(time.GetYear(), time.GetMonth() - 1, 1, 0, 0, 0);
							dayendtime = TTime(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
						}	
						
						bReportGen = true;
					}
				}

				if(bReportGen)
				{
					string	szRootPath = GetSiteViewRootPath();
					strCmdLine = szRootPath;
					strCmdLine += "\\fcgi-bin\\topnreport.exe ";
					//strCmdLine = "C:\\Program Files\\apache group\\apache2\\fcgi-bin\\statsreport.exe ";
				
					szdaystarttime = daystarttime.Format();
					szdaystarttime = replace_all_distinct(szdaystarttime, " ", "_");
					szdaystarttime = replace_all_distinct(szdaystarttime, ":", "_");
					strCmdLine += szdaystarttime;
					strCmdLine += " ";

					szdayendtime = dayendtime.Format();
					szdayendtime = replace_all_distinct(szdayendtime, " ", "_");
					szdayendtime = replace_all_distinct(szdayendtime, ":", "_");
					strCmdLine += szdayendtime;
					strCmdLine += " ";

					replace_all_distinct(tsection, " ", "%20");
					strCmdLine += tsection;
					strCmdLine += " ";

					szReportName = szdaystarttime;
					szReportName += szdayendtime;
					szReportName += tsection;

					std::string iconspath = szReportName;

					szReportName += ".html";
					replace_all_distinct(szReportName, "*", "_");
					replace_all_distinct(szReportName, "/", "_");
					replace_all_distinct(szReportName, "\\", "_");
					replace_all_distinct(szReportName,"?", "_");
					replace_all_distinct(szReportName,  "|", "_");
					replace_all_distinct(szReportName,  "<", "_");
					replace_all_distinct(szReportName,  ">", "_");
					replace_all_distinct(szReportName,  ":", "_");
					replace_all_distinct(szReportName,  "\"", "_");
					replace_all_distinct(szReportName,  " ", "_");
					replace_all_distinct(szReportName,  "%20", "_");

					strCmdLine += szReportName;

					strCmdLine += " ";
					strCmdLine += szGenNum;

					OutputDebugString("---------------report generate topn output----------------------\n");
					OutputDebugString(strCmdLine.c_str());
					OutputDebugString("\n");
					
					
					if (CreateProcess(NULL,(LPSTR) strCmdLine.c_str(),  &sa, &sa, TRUE, CREATE_NEW_CONSOLE/*CREATE_NO_WINDOW*/, NULL, NULL, &si, &pi)) 
					{
						
					}
					WaitForSingleObject( pi.hProcess, INFINITE );

					// Close process and thread handles. 
					CloseHandle( pi.hProcess );
					CloseHandle( pi.hThread );

					//	修改html中image路径
					WIN32_FIND_DATA	fd;
					string szPath = "..\\htdocs\\topnreport\\CopyHtml";
					HANDLE hFile=::FindFirstFile(szPath.c_str(), &fd);
					if(hFile == INVALID_HANDLE_VALUE)
					{
						CreateDirectory(szPath.c_str(), NULL);
					}
					::FindClose(hFile);
					string szFileFrom = "..\\htdocs\\topnreport\\";
					szFileFrom += szReportName;
					string szFileTo = "..\\htdocs\\topnreport\\CopyHtml\\";
					szFileTo += szReportName;
					CopyFile(szFileFrom.c_str(), szFileTo.c_str(), FALSE);

					//打开文件并获取其中的数据
					ifstream iFile;
					iFile.open(szFileFrom.c_str(),ios::in,0);
					string FileData;
					list<string> FileDataList;
					list<string>::iterator FileDataListRecord;
					while(getline(iFile,FileData))
					{
						FileDataList.push_back(FileData);
					}
					iFile.close();

					//替换
					string strSrc = "src='/Images";

//					string strReplace = "src='Images"; 
					// ++++++ #52、#45 ++++++
					// 2007/6/29 龚超 
					// 以上原代码行替换报告html文件中图片文件夹路径导致报告页面直接在本地用IE
					// 查看时部分图片显示不正常。以下代码明确指定图片文件夹位于页面当前目录。
					string strReplace = "src='./Images";
					// ------ #52、#45 ------

					for( FileDataListRecord = FileDataList.begin();FileDataListRecord != FileDataList.end(); FileDataListRecord++ )
					{	
						string m_pMid;
						m_pMid = *FileDataListRecord;
						size_t pos = m_pMid.find(strSrc);
						if(pos != m_pMid.npos)
						{
							stringReplace(*FileDataListRecord,strSrc,strReplace);
						}
					}

					//写入文件
					ofstream oFile;
					oFile.open(szFileFrom.c_str(),ios::out,0);
					for( FileDataListRecord = FileDataList.begin(); FileDataListRecord != FileDataList.end(); FileDataListRecord++)
					{	
						string m_pMid;
						m_pMid = * FileDataListRecord;
						cout<<m_pMid<<endl;
						const char * ptr = m_pMid.c_str();
						char charWriteFile;
						while((*ptr != '\0'))
						{
							charWriteFile = * ptr;
							oFile.put(charWriteFile);
							ptr++;
						}
						oFile.put('\n');
					}
					FileDataList.clear();
					oFile.close();

					char * argv[10];

					std::string ziptempstr;

					argv[0] = "zipfile";
					ziptempstr = argv[0];
					ziptempstr += " ";

					argv[1] = "-f";
					ziptempstr += argv[1];
					ziptempstr += " ";

					argv[2] = (char*)malloc(160);
					memset(argv[2], 0, 160);					
					string szReportPath ;
					string szCssIconPath1 = "..\\htdocs\\topnreport\\Images\\table_head_space.png";
					string szCssIconPath2 = "..\\htdocs\\topnreport\\Images\\table_shadow_left_bom.png";
					string szCssIconPath3 = "..\\htdocs\\topnreport\\Images\\table_shadow_right_bom.png";
					string szCssPath = "..\\htdocs\\css.css";

					szReportPath += "..\\htdocs\\topnreport\\";
					strcpy(argv[2], szReportPath.c_str());
					strcat(argv[2], "siteviewtopnreport");
					strcat(argv[2], ".zip");
					ziptempstr += argv[2];
					ziptempstr += " ";

					argv[3] = "-a";
					ziptempstr += argv[3];
					ziptempstr += " ";

					argv[4] = (char*)malloc(160);
					memset(argv[4], 0, 160);
					string szReportIconPath = szReportPath;
					szReportIconPath +="images\\";

					strcpy(argv[4], szReportIconPath.c_str());
					strcat(argv[4], iconspath.c_str());
					strcat(argv[4], "\\*.*");
					ziptempstr += argv[4];
					ziptempstr += " ";
					
					argv[5] = (char*)malloc(160);
					memset(argv[5], 0, 160);
					strcpy(argv[5], szReportPath.c_str());
					strcat(argv[5], szReportName.c_str());
					ziptempstr += argv[5];
					ziptempstr += " ";

					argv[6] = (char*)malloc(64);
					memset(argv[6], 0, 64);
					strcpy(argv[6], szCssIconPath1.c_str());
					ziptempstr += argv[6];
					ziptempstr += " ";

					argv[7] = (char*)malloc(64);
					memset(argv[7], 0, 64);
					strcpy(argv[7], szCssIconPath2.c_str());
					ziptempstr += argv[7];
					ziptempstr += " ";

					argv[8] = (char*)malloc(64);
					memset(argv[8], 0, 64);
					strcpy(argv[8], szCssIconPath3.c_str());
					ziptempstr += argv[8];
					ziptempstr += " ";

					argv[9] = (char*)malloc(64);
					memset(argv[9], 0, 64);
					strcpy(argv[9], szCssPath.c_str());
					ziptempstr += argv[9];
					ziptempstr += " ";


					main1(10, argv);

													
					//
					std::string ret = "error";
					std::string emailaddr = GetIniFileString("email_config", "from", ret, "email.ini");
					if(strcmp(ret.c_str(), "error") == 0)
					{
					}

					std::string emailserver = GetIniFileString("email_config", "server", ret, "email.ini");
					if(strcmp(ret.c_str(), "error") == 0)
					{
					}

					int pos = 0;
					int pos1 = 0;
					while((pos1 = szEmailSend.find(",", pos)) >= 0)
					{
						std::string temp = szEmailSend.substr(pos , pos1 - pos);						
						if(!temp.empty())
						{
							//jwsmtp::mailer m(temp.c_str(), "xian.jiang@dragonflow.com",  "test mail send", "test mail send",
							//"mail.dragonflow.com", 25, false);

							//重写了邮件发送代码，对此工程进行相应修改
							//苏合 2007-07-24
							//+++++++++++++修改开始 苏合 2007-07-24+++++++++++++
							/*
							jwsmtp::mailer m(temp.c_str(), emailaddr.c_str(),  "SiteView-Topn-Report", "SiteView-Topn-Report",
							emailserver.c_str(), 25, false);
							std::string emailfile = szReportPath;
							emailfile += "siteviewtopnreport.zip";
							
							OutputDebugString("-----------------email attach path---------------------\n");
							OutputDebugString(emailfile.c_str());
							OutputDebugString("\n");

							m.attach(emailfile);					
							m.send(); // send the mail
							*/
							//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++
							/*
							std::string emailfile = szReportPath;
							emailfile += "siteviewtopnreport.zip";
							*/
							//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++

							HINSTANCE hDll = LoadLibrary("emailalert.dll");						
							if (hDll)
							{
								SendEmail * func = (SendEmail*)::GetProcAddress(hDll, "SendEmail");
								if (func)
								{									
									std::string emailfile = szReportPath;
									emailfile += "siteviewtopnreport.zip";
									
									bRet = (*func)(emailserver.c_str(), emailaddr.c_str(),
										           temp.c_str(), "SiteView-Topn-Report",
										           "SiteView-Topn-Report", strUserID.c_str(),
										           strUserPwd.c_str(), emailfile.c_str());
								}
								FreeLibrary(hDll);
							}
							//+++++++++++++修改结束 苏合 2007-07-24+++++++++++++ 
						}
						pos = pos1 + 1;
					}
					
					std::string temp = szEmailSend.substr(pos , szEmailSend.size() - pos);
					if(!temp.empty())
					{
						//重写了邮件发送代码，对此工程进行相应修改
						//苏合 2007-07-24
						//+++++++++++++修改开始 苏合 2007-07-24+++++++++++++
						/*
						jwsmtp::mailer m(temp.c_str(), emailaddr.c_str(),  "SiteView-Topn-Report", "SiteView-Topn-Report",
						emailserver.c_str(), 25, false);
						m.attach(argv[2]);

						OutputDebugString("-----------------email attach path---------------------\n");
						OutputDebugString(emailaddr.c_str());
						OutputDebugString("\n");
						OutputDebugString(temp.c_str());
						OutputDebugString("\n");
						OutputDebugString(argv[2]);
						OutputDebugString("\n");
						m.send(); // send the mail
						*/
						
						HINSTANCE hDll = LoadLibrary("emailalert.dll");						
						if (hDll)
						{
							SendEmail * func = (SendEmail*)::GetProcAddress(hDll, "SendEmail");
							if (func)
							{
								//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++
								/*
								std::string emailfile = szReportPath;
								emailfile += "siteviewtopnreport.zip";
								*/
								//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++

								bRet = (*func)(emailserver.c_str(), emailaddr.c_str(),
									           temp.c_str(), "SiteView-Topn-Report",
									           "SiteView-Topn-Report", strUserID.c_str(),
									           strUserPwd.c_str(), argv[2]);
							}
							FreeLibrary(hDll);
						}
						//+++++++++++++修改结束 苏合 2007-07-24+++++++++++++						
					}

	
					free(argv[2]);
					free(argv[4]);
					free(argv[5]);
					free(argv[6]);
					free(argv[7]);
					free(argv[8]);
					free(argv[9]);

					CopyFile(szFileTo.c_str(), szFileFrom.c_str(), FALSE);
					DeleteFile(szFileTo.c_str());
				}

			}
		}

	}


	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{		
		std::string section = *m_sItem;	
		
		bool bGen = false;

		//判断是否到生成时间
		std::string szGenerate = GetIniFileString(section, "Generate", ret, "reportset.ini");
		if(strcmp(szGenerate.c_str(), "error") != 0)
		{			
			int nHour = time.GetHour();
			if(nHour == atoi(szGenerate.c_str()))
			{
				bGen = true;
			}
		}

		//是否列出阀值
		std::string szBClicket = GetIniFileString(section, "ListClicket", ret, "reportset.ini");
		if(strcmp(szBClicket.c_str(), "error") == 0)
		{
			
		}

		//是否列出错误
		std::string szBListError = GetIniFileString(section, "ListError", ret, "reportset.ini");
		if(strcmp(szBListError.c_str(), "error") == 0)
		{
		}

		//是否列出危险
		std::string szBListDanger = GetIniFileString(section, "ListDanger", ret, "reportset.ini");
		if(strcmp(szBListDanger.c_str(), "error") == 0)
		{
		}

		std::string szDeny = GetIniFileString(section, "Deny", ret, "reportset.ini");
		if(strcmp(szDeny.c_str(), "error") == 0)
		{
		}

		std::string szStatusResult = GetIniFileString(section, "StatusResult", ret, "reportset.ini");
		if(strcmp(szStatusResult.c_str(), "error") == 0)
		{
		}

		std::string szEmailSend = GetIniFileString(section, "EmailSend", ret, "reportset.ini");
		if(strcmp(szEmailSend.c_str(), "error") == 0)
		{
		}

		std::string szListImage = GetIniFileString(section, "Graphic", ret, "reportset.ini");
		if(strcmp(szListImage.c_str(), "error") == 0)
		{
		}

		std::string szComboGraphic = GetIniFileString(section, "ComboGraphic", ret, "reportset.ini");
		if(strcmp(szComboGraphic.c_str(), "error") == 0)
		{
		}

		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
		std::string szExcel = GetIniFileString(section, "GenExcel", ret, "reportset.ini");
		if(strcmp(szExcel.c_str(), "error") == 0)
		{
		}
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23


		//get email send address

		TTime dayendtime;
		TTime daystarttime;

		bool bReportGen = false;

		if(strcmp(szDeny.c_str(), "Yes") != 0)
		{
			
			if(bGen)
			{			
				//根据报告类型以确定是否生成报告
				std::string szPeriod = GetIniFileString(section, "Period", ret, "reportset.ini");
				if(strcmp(szPeriod.c_str(), dayReport.c_str()) == 0)
				{
					//往日报中写定时生成记录
					std::string szEndTime = GetIniFileString(section, "EndTime", ret, "reportset.ini");

					int pos = szEndTime.find(":", 0);
					std::string szHour = szEndTime.substr(0, pos);
					std::string szMinute = szEndTime.substr(pos + 1, szEndTime.size() - pos - 1);

					dayendtime = TTime(time.GetYear(), time.GetMonth(), time.GetDay(), atoi(szHour.c_str()), atoi(szMinute.c_str()), 0);
					daystarttime = dayendtime - TTimeSpan(1, 0, 0, 0);
					
					bReportGen = true;
				}
				
				
				else if(strcmp(szPeriod.c_str(), weekReport.c_str()) == 0)
				{
					int nret = -1;
					int nWeekDay = GetIniFileInt(section, "WeekEndTime", nret, "reportset.ini");												
					
					CTime time1(CTime::GetCurrentTime());   // Initialize CTime with current time
					//::GetLocaleInfo(LOCALE_USER_DEFAULT,   // Get string for day of the week from system
					//DayOfWeek[time.GetDayOfWeek()-1],   // Get day of week from CTime
					//strWeekday, sizeof(strWeekday));
					
					if((time1.GetDayOfWeek() - 1) == nWeekDay)
					{
						dayendtime = TTime(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
						daystarttime = dayendtime - TTimeSpan(7, 0, 0, 0);

						bReportGen = true;
					}
				}
				
				
				else if(strcmp(szPeriod.c_str(), monthReport.c_str()) == 0)
				{
					if(time.GetDay() == 1)
					{
						/* 2007/7/12 龚超 该段代码导致月报起始时间错误因此被注释
						TTime dayendtime;
						TTime daystarttime;
						*/

						if(time.GetMonth() == 1)
						{
							daystarttime = TTime(time.GetYear() - 1, 12, 1, 0, 0, 0);
							dayendtime = TTime(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
						}
						else
						{
							daystarttime = TTime(time.GetYear(), time.GetMonth() - 1, 1, 0, 0, 0);
							dayendtime = TTime(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
						}	
						
						bReportGen = true;
					}
				}

				if(bReportGen)
				{
					string	szRootPath = GetSiteViewRootPath();
					strCmdLine = szRootPath;
					strCmdLine += "\\fcgi-bin\\statsreport.exe ";
					//strCmdLine = "C:\\Program Files\\apache group\\apache2\\fcgi-bin\\statsreport.exe ";
				
					szdaystarttime = daystarttime.Format();
					szdaystarttime = replace_all_distinct(szdaystarttime, " ", "_");
					szdaystarttime = replace_all_distinct(szdaystarttime, ":", "_");
					strCmdLine += szdaystarttime;
					strCmdLine += " ";

					szdayendtime = dayendtime.Format();
					szdayendtime = replace_all_distinct(szdayendtime, " ", "_");
					szdayendtime = replace_all_distinct(szdayendtime, ":", "_");
					strCmdLine += szdayendtime;
					strCmdLine += " ";

					replace_all_distinct(section, " ", "%20");
					strCmdLine += section;
					strCmdLine += " ";

					
					szReportName = szdaystarttime;
					szReportName += szdayendtime;
					szReportName += section;

					replace_all_distinct(szReportName, "*", "_");
					replace_all_distinct(szReportName, "/", "_");
					replace_all_distinct(szReportName, "\\", "_");
					replace_all_distinct(szReportName,"?", "_");
					replace_all_distinct(szReportName,  "|", "_");
					replace_all_distinct(szReportName,  "<", "_");
					replace_all_distinct(szReportName,  ">", "_");
					replace_all_distinct(szReportName,  ":", "_");
					replace_all_distinct(szReportName,  "\"", "_");
					replace_all_distinct(szReportName,  " ", "_");
					replace_all_distinct(szReportName,  "%20", "_");
					std::string iconspath = szReportName;
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
					szExcelName = szReportName + ".xls";
                    //为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

					szReportName += ".html";
					strCmdLine += szReportName;
					strCmdLine += " ";
					strCmdLine += szBClicket;
					strCmdLine += " ";
					strCmdLine += szBListError;
					strCmdLine += " ";
					strCmdLine += szBListDanger;
					strCmdLine += " ";
					strCmdLine += szStatusResult;
					strCmdLine += " ";
					strCmdLine += szListImage;
					strCmdLine += " ";
					strCmdLine += szComboGraphic;
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
					strCmdLine += " ";
					strCmdLine += szExcel;
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
					
					
					OutputDebugString("--------------create process statsreport.exe-----------------\n");
					OutputDebugString(strCmdLine.c_str());
					OutputDebugString("\n");

					if (CreateProcess(NULL,(LPSTR) strCmdLine.c_str(),  &sa, &sa, TRUE, CREATE_NEW_CONSOLE/*CREATE_NO_WINDOW*/, NULL, NULL, &si, &pi)) 
					{
						
					}
					WaitForSingleObject( pi.hProcess, INFINITE );

					// Close process and thread handles. 
					CloseHandle( pi.hProcess );
					CloseHandle( pi.hThread );

					//	修改html中image路径
					WIN32_FIND_DATA	fd;
					string szPath = "..\\htdocs\\report\\CopyHtml";
					HANDLE hFile=::FindFirstFile(szPath.c_str(), &fd);
					if(hFile == INVALID_HANDLE_VALUE)
					{
						CreateDirectory(szPath.c_str(), NULL);
					}
					::FindClose(hFile);
					string szFileFrom = "..\\htdocs\\report\\";
					szFileFrom += szReportName;
					string szFileTo = "..\\htdocs\\report\\CopyHtml\\";
					szFileTo += szReportName;
					CopyFile(szFileFrom.c_str(), szFileTo.c_str(), FALSE);

					//打开文件并获取其中的数据
					ifstream iFile;
					iFile.open(szFileFrom.c_str(),ios::in,0);
					string FileData;
					list<string> FileDataList;
					list<string>::iterator FileDataListRecord;
					while(getline(iFile,FileData))
					{
						FileDataList.push_back(FileData);
					}
					iFile.close();

					//替换
					string strSrc = "src='/Images";
					string strReplace = "src='Images";
					for( FileDataListRecord = FileDataList.begin();FileDataListRecord != FileDataList.end(); FileDataListRecord++ )
					{	
						string m_pMid;
						m_pMid = *FileDataListRecord;
						size_t pos = m_pMid.find(strSrc);
						if(pos != m_pMid.npos)
						{
							stringReplace(*FileDataListRecord,strSrc,strReplace);
						}
					}

					//写入文件
					ofstream oFile;
					oFile.open(szFileFrom.c_str(),ios::out,0);
					for( FileDataListRecord = FileDataList.begin(); FileDataListRecord != FileDataList.end(); FileDataListRecord++)
					{	
						string m_pMid;
						m_pMid = * FileDataListRecord;
						cout<<m_pMid<<endl;
						const char * ptr = m_pMid.c_str();
						char charWriteFile;
						while((*ptr != '\0'))
						{
							charWriteFile = * ptr;
							oFile.put(charWriteFile);
							ptr++;
						}
						oFile.put('\n');
					}
					FileDataList.clear();
					oFile.close();

					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
					/*char * argv[10];*/
					char * argv[11];
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
					std::string ziptempstr;

					argv[0] = "zipfile";
					ziptempstr = argv[0];
					ziptempstr += " ";

					argv[1] = "-f";
					ziptempstr += argv[1];
					ziptempstr += " ";

					argv[2] = (char*)malloc(160);
					memset(argv[2], 0, 160);					
					string szReportPath ;//GetSiteViewRootPath();
					string szCssIconPath1 = "..\\htdocs\\report\\Images\\table_head_space.png";
					string szCssIconPath2 = "..\\htdocs\\report\\Images\\table_shadow_left_bom.png";
					string szCssIconPath3 = "..\\htdocs\\report\\Images\\table_shadow_right_bom.png";
					string szCssPath = "..\\htdocs\\css.css";

					szReportPath += "..\\htdocs\\report\\";
					//strcpy(argv[2], "C:\\Program Files\\apache group\\apache2\\htdocs\\report\\");
					strcpy(argv[2], szReportPath.c_str());
					//strcat(argv[2], iconspath.c_str());
					strcat(argv[2], "siteviewstatreport");
					strcat(argv[2], ".zip");
					ziptempstr += argv[2];
					ziptempstr += " ";

					//argv[2] = "c:\\file.zip";
					argv[3] = "-a";
					ziptempstr += argv[3];
					ziptempstr += " ";


					argv[4] = (char*)malloc(160);
					memset(argv[4], 0, 160);
					string szReportIconPath = szReportPath;
					szReportIconPath +="images\\";
					//strcpy(argv[4], "C:\\Program Files\\apache group\\apache2\\htdocs\\report\\icons\\");

					strcpy(argv[4], szReportIconPath.c_str());
					strcat(argv[4], iconspath.c_str());
					strcat(argv[4], "\\*.*");
					ziptempstr += argv[4];
					ziptempstr += " ";

					//argv[4] = "C:\\Program Files\\apache group\\apache2\\htdocs\\report\\icons\\*.*";
					argv[5] = (char*)malloc(160);
					memset(argv[5], 0, 160);
					//strcpy(argv[5], "C:\\Program Files\\apache group\\apache2\\htdocs\\report\\");
					strcpy(argv[5], szReportPath.c_str());
					strcat(argv[5], szReportName.c_str());
					ziptempstr += argv[5];
					ziptempstr += " ";

					argv[6] = (char*)malloc(64);
					memset(argv[6], 0, 64);
					strcpy(argv[6], szCssIconPath1.c_str());
					ziptempstr += argv[6];
					ziptempstr += " ";

					argv[7] = (char*)malloc(64);
					memset(argv[7], 0, 64);
					strcpy(argv[7], szCssIconPath2.c_str());
					ziptempstr += argv[7];
					ziptempstr += " ";

					argv[8] = (char*)malloc(64);
					memset(argv[8], 0, 64);
					strcpy(argv[8], szCssIconPath3.c_str());
					ziptempstr += argv[8];
					ziptempstr += " ";

					argv[9] = (char*)malloc(64);
					memset(argv[9], 0, 64);
					strcpy(argv[9], szCssPath.c_str());
					ziptempstr += argv[9];
					ziptempstr += " ";

					OutputDebugString("--------------report generate-------------------\n");
					OutputDebugString(ziptempstr.c_str());
					OutputDebugString("-------------gen end----------------------\n");

					//argv[5] = "C:\\Program Files\\apache group\\apache2\\htdocs\\report\\szReportName";

					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
					/*main1(10, argv);*/

					argv[10] = (char*)malloc(160);
					memset(argv[10], 0, 160);
					strcpy(argv[10], szReportPath.c_str());
					strcat(argv[10], szExcelName.c_str());
					ziptempstr += argv[10];
					ziptempstr += " ";

					main1(11, argv);
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23					
					
					//
					std::string ret = "error";
					std::string emailaddr = GetIniFileString("email_config", "from", ret, "email.ini");
					if(strcmp(ret.c_str(), "error") == 0)
					{
					}

					std::string emailserver = GetIniFileString("email_config", "server", ret, "email.ini");
					if(strcmp(ret.c_str(), "error") == 0)
					{
					}

					//重写了邮件发送代码，对此工程进行相应修改
					//苏合 2007-07-24
					//此段代码移动到前面，所以将此处注释
					//+++++++++++++++++++注释开始 苏合 2007-07-24++++++++++++++++++++++
					/*
					// ++++++ 取邮件发送服务器校验用户和密码 ++++++
					// 2007/6/29 龚超
					// 原版本没有该功能导致采用如163邮箱不能正确发送邮件的问题

					// 校验用户
					std::string strUserID = GetIniFileString("email_config", "user", ret, "email.ini");

					// 校验密码
					std::string strUserPwd = GetIniFileString("email_config", "password", ret,  "email.ini");
					if (strcmp(ret.c_str(), "error") == 0)
					{// 发生了读取错误

						strUserPwd = "";
					}
					else
					{
						Des mydes;
						char deschar[1024] = {0};
						if (strUserPwd.size() > 0)
						{
							mydes.Decrypt(strUserPwd.c_str(),deschar);
							strUserPwd = deschar;
						}
					}
					// ------ 取邮件发送服务器校验用户和密码 ------
					*/
					//+++++++++++++++++++注释结束 苏合 2007-07-24++++++++++++++++++++++

					int pos = 0;
					int pos1 = 0;
					while((pos1 = szEmailSend.find(",", pos)) >= 0)
					{
						std::string temp = szEmailSend.substr(pos , pos1 - pos);						
						if(!temp.empty())
						{
							//重写了邮件发送代码，对此工程进行相应修改
							//苏合 2007-07-24
							//+++++++++++++修改开始 苏合 2007-07-24+++++++++++++

//							//jwsmtp::mailer m(temp.c_str(), "xian.jiang@dragonflow.com",  "test mail send", "test mail send",
//							//"mail.dragonflow.com", 25, false);							
//							jwsmtp::mailer m(temp.c_str(), emailaddr.c_str(),  "SiteView-Stat-Report", "SiteView-Stat-Report",
//							emailserver.c_str(), 25, false);
//
//							//解决江苏省工行报表邮件发送不发附件的错误 苏合 2007-07-20
//							//代码修改开始 苏合 2007-07-20
//							/*
//							std::string emailfile = szReportPath;
//							emailfile += "siteviewreport.zip";
//							m.attach(emailfile);
//							*/
//							m.attach(argv[2]);
//							//代码修改结束 苏合 2007-07-20
//
//							m.send(); // send the mail

							HINSTANCE hDll = LoadLibrary("emailalert.dll");						
							if (hDll)
							{
								SendEmail * func = (SendEmail*)::GetProcAddress(hDll, "SendEmail");
								if (func)
								{
									//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++
									/*
									std::string emailfile = szReportPath;
									emailfile += "siteviewtopnreport.zip";
									*/
									//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++

									bRet = (*func)(emailserver.c_str(), emailaddr.c_str(),
										           temp.c_str(), "SiteView-Stat-Report",
										           "SiteView-Stat-Report", strUserID.c_str(),
										           strUserPwd.c_str(), argv[2]);
								}
								FreeLibrary(hDll);
							}
							//+++++++++++++修改结束 苏合 2007-07-24+++++++++++++
							
						}
						pos = pos1 + 1;
					}
					
					std::string temp = szEmailSend.substr(pos , szEmailSend.size() - pos);
					if(!temp.empty())
					{
						//重写了邮件发送代码，对此工程进行相应修改
						//苏合 2007-07-24
						//+++++++++++++修改开始 苏合 2007-07-24+++++++++++++
						/*
						jwsmtp::mailer m(temp.c_str(), emailaddr.c_str(),  "SiteView-Stat-Report", "SiteView-Stat-Report",
						emailserver.c_str(), jwsmtp::mailer::SMTP_PORT, false);

						// 2007/6/29 龚超
						// jwsmtp对于SMTP用户验证似乎有问题？？？
						// m.username(strUserID);
						// m.password(strUserPwd);
						m.attach(argv[2]);					
						m.send(); // send the mail
//						OUT_DEBUG("send.4", temp.c_str(), emailaddr.c_str(), emailserver.c_str(), argv[2]);
						*/

						HINSTANCE hDll = LoadLibrary("emailalert.dll");						
						if (hDll)
						{
							SendEmail * func = (SendEmail*)::GetProcAddress(hDll, "SendEmail");
							if (func)
							{
								//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++
								/*
								std::string emailfile = szReportPath;
								emailfile += "siteviewtopnreport.zip";
								*/
								//+++++++++++++++修改bug，完善邮件发送功能 苏合 2007-07-25++++++++++++++++

								bRet = (*func)(emailserver.c_str(), emailaddr.c_str(),
									           temp.c_str(), "SiteView-Stat-Report",
									           "SiteView-Stat-Report", strUserID.c_str(),
									           strUserPwd.c_str(), argv[2]);
							}
							FreeLibrary(hDll);
						}
						//+++++++++++++修改结束 苏合 2007-07-24+++++++++++++
						
					}

					OutputDebugString("-----------------email server and address---------------\n");
					OutputDebugString(emailaddr.c_str());
					OutputDebugString("\n");
					OutputDebugString(emailserver.c_str());
					OutputDebugString("\n");
					OutputDebugString(temp.c_str());
					OutputDebugString("\n");
					OutputDebugString("-----------------end email output---------------\n");
					

					free(argv[2]);
					free(argv[4]);
					free(argv[5]);
					free(argv[6]);
					free(argv[7]);
					free(argv[8]);
					free(argv[9]);
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
					free(argv[10]);
					//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
		
					CopyFile(szFileTo.c_str(), szFileFrom.c_str(), FALSE);
					DeleteFile(szFileTo.c_str());
				}
			}	
		}				
	}	
}
