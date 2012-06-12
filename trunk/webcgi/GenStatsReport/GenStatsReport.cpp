#include ".\genstatsreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"
#include "svdbapi.h"
#include "..\..\base\stlini.h"

#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
#include "WFont"
#include "WPushButton"

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"

#define WTGET

std::string RetRepHrefStr(std::string szRepStr)
{
	std::string szValue = szRepStr;

    int nPos = szValue.find("%26", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "&" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%26", nPos);
    }

    nPos = szValue.find("%24", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "$" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%24", nPos);
    }

    nPos = szValue.find("%23", 0);
    while (nPos >= 0)
    {
		szValue = szValue.substr(0, nPos ) + "#" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%23", nPos);
    }

    nPos = szValue.find("%20", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + " " + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%20", nPos);
    }

	return szValue;
}
string& replace_all_distinct(string& str,
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

CGenStatsReport::CGenStatsReport(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Create_Immediately",szCreateTitle);
			FindNodeValue(ResNode,"IDS_Report_Day",szReportDay);
			FindNodeValue(ResNode,"IDS_Report_Week",szReportWeek);
			FindNodeValue(ResNode,"IDS_Report_Month",szReportMonth);
			FindNodeValue(ResNode,"IDS_Start_Time1",strBeginTime);
			FindNodeValue(ResNode,"IDS_End_Time1",strEndTime);			
			FindNodeValue(ResNode,"IDS_General",strGeneral);			
			FindNodeValue(ResNode,"IDS_Return",strReturn);			
		}
		CloseResource(objRes);
	}
	ShowMainTable();
}

CGenStatsReport::~CGenStatsReport(void)
{
}

void CGenStatsReport::ShowMainTable()
{

	char buf_tmp[4096]={0};
    int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
	querystr = buf_tmp;

	OutputDebugString("querystr:");
	OutputDebugString(querystr.c_str());

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	

	char cFile[1024]={0};
	sprintf(cFile,"%s\\data\\svdbconfig.ini",GetSiteViewRootPath().c_str());
	INIFile ini2 = LoadIni(cFile);
	std::string strLan= GetIniSetting(ini2,"svdb", "DefaultLanguage","chinese");

	string strJs;
	strJs ="<SCRIPT language='JavaScript' src='/"+strLan;
	strJs +="/Calendar.js'></SCRIPT>";
	new WText(strJs,this);


	
	pMainTable = new WSVMainTable(this, "", false);
	
	
	pFlexTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(1,0), Query, szCreateTitle);

	if (pFlexTable->GetContentTable() != NULL)
	{
		TTime curTime = TTime::GetCurrentTimeEx();

		pFlexTable->AppendRows();
		starttimeedit = new WLineEdit("", pFlexTable->AppendRowsContent(0, 0, 1, strBeginTime, "", ""));
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		starttimeedit->setText(curTime.Format());
		starttimeedit->resize(WLength(150,WLength::Pixel),0);
		starttimeedit->setStyleClass("input_text");
		strcpy(starttimeedit->contextmenu_ , "onClick=\"calendar()\"");

		pFlexTable->AppendRows();
		endtimeedit = new WLineEdit("", pFlexTable->AppendRowsContent(1, 0, 1, strEndTime, "", ""));
		curTime = TTime::GetCurrentTimeEx();
		endtimeedit->setText(curTime.Format());
		endtimeedit->resize(WLength(150,WLength::Pixel),0);
		endtimeedit->setStyleClass("input_text");
		strcpy(endtimeedit->contextmenu_ , "onFocus=\"calendar()\"");

	}

	if (pFlexTable->GetActionTable() != NULL)
	{
		WSVButton * pfastgen;
		//pFlexTable->GetActionTable()->elementAt(0, 0)->setContentAlignment(AlignCenter);
		pfastgen = new WSVButton(pFlexTable->GetActionTable()->elementAt(0, 0), strGeneral, "button_bg_m_black.png", strGeneral, true);
		if(pfastgen)
		{
			connect(pfastgen, SIGNAL(clicked()),"showbar();", this, SLOT(FastGenReport()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
			//connect(pfastgen, SIGNAL(clicked()), this, SLOT(FastGenReport()));
		}

		//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", pFlexTable->GetActionTable()->elementAt(0, 1));

		WSVButton * pclose;
		pclose = new WSVButton(pFlexTable->GetActionTable()->elementAt(0, 1), strReturn, "button_bg_m.png", strReturn, false);
		if(pclose)
		{
			WObject::connect(pclose, SIGNAL(clicked()), "showbar();", SLOT(Close()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}
	}
	
}



//手工生成报告
void CGenStatsReport::FastGenReport()
{		
	OutputDebugString("----------------CGenStatsReport FastGenReport 1--------------------\n");
	std::string szdaystarttime; std::string szdayendtime;
	std::string szReportName;

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
	si.wShowWindow =SW_HIDE;
	
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	std::string ret = "error";
	if(!querystr.empty())
	{
		OutputDebugString("----------------CGenStatsReport FastGenReport 11--------------------\n");
		std::string szPeriod = GetIniFileString(querystr, "Period", ret, "reportset.ini");
		svutil::TTime dayendtime = svutil::TTime::GetCurrentTimeEx();
		svutil::TTime daystarttime;

		//是否列出阀值
		std::string szBClicket = GetIniFileString(querystr, "ListClicket", ret, "reportset.ini");
		if(strcmp(szBClicket.c_str(), "error") == 0)
		{

		}

		//是否列出错误
		std::string szBListError = GetIniFileString(querystr, "ListError", ret, "reportset.ini");
		if(strcmp(szBListError.c_str(), "error") == 0)
		{
		}

		//是否列出危险
		std::string szBListDanger = GetIniFileString(querystr, "ListDanger", ret, "reportset.ini");
		if(strcmp(szBListDanger.c_str(), "error") == 0)
		{
		}
		//是否禁止生成报告
		std::string szDeny = GetIniFileString(querystr, "Deny", ret, "reportset.ini");
		if(strcmp(szDeny.c_str(), "error") == 0)
		{
		}

		std::string szStatsResult = GetIniFileString(querystr, "StatusResult", ret, "reportset.ini");

		if(strcmp(szStatsResult.c_str(), "error") == 0)
		{
		}

		std::string szListImage = GetIniFileString(querystr, "Graphic", ret, "reportset.ini");
		if(strcmp(szListImage.c_str(), "error") == 0)
		{
		}

		std::string szComboGraphic = GetIniFileString(querystr, "ComboGraphic", ret, "reportset.ini");
		if(strcmp(szComboGraphic.c_str(), "error") == 0)
		{
		}

		
		OutputDebugString("----------------CGenStatsReport FastGenReport 2--------------------\n");
		if(strcmp(szPeriod.c_str(), "error") != 0)
		{
			if(strcmp(szPeriod.c_str(), szReportDay.c_str()) == 0)
			{				
				daystarttime = dayendtime - svutil::TTimeSpan(1, 0, 0, 0);				
			}
			else if(strcmp(szPeriod.c_str(), szReportWeek.c_str()) == 0)
			{
				daystarttime = dayendtime - svutil::TTimeSpan(7, 0, 0, 0);
			}
			else if(strcmp(szPeriod.c_str(), szReportMonth.c_str()) == 0)
			{
				if(dayendtime.GetMonth() == 1)
				{
					daystarttime = svutil::TTime(dayendtime.GetYear() - 1, 12, \
						dayendtime.GetDay() , dayendtime.GetHour(), \
						dayendtime.GetMinute(), dayendtime.GetSecond());
				}
				else
				{
					daystarttime = svutil::TTime(dayendtime.GetYear(), \
						dayendtime.GetMonth() - 1, dayendtime.GetDay() , \
						dayendtime.GetHour(), dayendtime.GetMinute(), dayendtime.GetSecond());
				}
				
			}

			std::string szRootPath = GetSiteViewRootPath();
			strCmdLine = szRootPath;
			strCmdLine += "\\fcgi-bin\\statsreport.exe ";
				
			//szdaystarttime = daystarttime.Format();
			szdaystarttime = starttimeedit->text();
			szdaystarttime = replace_all_distinct(szdaystarttime, " ", "_");
			szdaystarttime = replace_all_distinct(szdaystarttime, ":", "_");
			strCmdLine += szdaystarttime;
			strCmdLine += " ";

			//szdayendtime = dayendtime.Format();
			szdayendtime = endtimeedit->text();
			szdayendtime = replace_all_distinct(szdayendtime, " ", "_");
			szdayendtime = replace_all_distinct(szdayendtime, ":", "_");
			strCmdLine += szdayendtime;
			strCmdLine += " ";

			replace_all_distinct(querystr, " ", "%20");				
			strCmdLine += querystr;
			
			strCmdLine += " ";

			szReportName = szdaystarttime;
			szReportName += szdayendtime;
			szReportName += querystr;
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
			replace_all_distinct(szReportName, "#", "_");
			

			strCmdLine += szReportName;
			strCmdLine += " ";
			strCmdLine += szBClicket;
			strCmdLine += " ";
			strCmdLine += szBListError;
			strCmdLine += " ";
			strCmdLine += szBListDanger;
			strCmdLine += " ";
			strCmdLine += szStatsResult;
			strCmdLine += " ";
			strCmdLine += szListImage;	
			strCmdLine += " ";
			strCmdLine += szComboGraphic;

			OutputDebugString("----------------CGenStatsReport FastGenReport 21--------------------\n");			
			if (CreateProcess(NULL,(LPSTR) strCmdLine.c_str(), \
				&sa, &sa, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) 
			{					
			}
			else
			{						
			}
			WaitForSingleObject( pi.hProcess, INFINITE );

			CloseHandle( pi.hProcess );
			CloseHandle( pi.hThread );
			OutputDebugString("----------------CGenStatsReport FastGenReport 22--------------------\n");						
			//std::string openurl = "hiddenbar();window.open('../report/";
			//openurl += szReportName;
			//openurl += "')";				
			//WebSession::js_af_up = openurl;			

			std::string openurl = "hiddenbar();location.href='../report/";
			openurl += szReportName;
			openurl += "'";				
			WebSession::js_af_up = openurl;	



			std::string tempsection = szReportName;
			tempsection += "$";
			tempsection += szdaystarttime;
			tempsection += "$";
			tempsection += szdayendtime;
			tempsection += "$";
		}
		OutputDebugString("----------------CGenStatsReport FastGenReport 3--------------------\n");			
	}
}

void CGenStatsReport::refresh()
{
	char buf_tmp[4096]={0};
    int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
	querystr = buf_tmp;
	OutputDebugString("querystr:");
	OutputDebugString(querystr.c_str());
	string ret = "error";
	string szPeriod = "";
	TTime daystarttime  ;
	TTime dayendtime = TTime::GetCurrentTimeEx();

	szPeriod = GetIniFileString(querystr, "Period", ret, "reportset.ini");
	if(strcmp(szPeriod.c_str(), "error") == 0)
	{
	}

	
	if(strcmp(szPeriod.c_str(), "error") != 0)
	{
		if(strcmp(szPeriod.c_str(), szReportDay.c_str()) == 0)
		{				
			daystarttime = dayendtime - svutil::TTimeSpan(1, 0, 0, 0);				
		}
		else if(strcmp(szPeriod.c_str(), szReportWeek.c_str()) == 0)
		{
			daystarttime = dayendtime - svutil::TTimeSpan(7, 0, 0, 0);
		}
		else if(strcmp(szPeriod.c_str(), szReportMonth.c_str()) == 0)
		{
			if(dayendtime.GetMonth() == 1)
			{
				daystarttime = svutil::TTime(dayendtime.GetYear() - 1, 12, \
					dayendtime.GetDay() , dayendtime.GetHour(), \
					dayendtime.GetMinute(), dayendtime.GetSecond());
			}
			else
			{
				daystarttime = svutil::TTime(dayendtime.GetYear(), \
					dayendtime.GetMonth() - 1, dayendtime.GetDay() , \
					dayendtime.GetHour(), dayendtime.GetMinute(), dayendtime.GetSecond());
			}
			
		}		
		starttimeedit->setText(daystarttime.Format());
		endtimeedit->setText(dayendtime.Format());
		char aaa[200];
		sprintf(aaa, "%s-----------%s--------\n", daystarttime.Format().c_str(), dayendtime.Format().c_str());
		OutputDebugString(aaa);
	}
}

void CGenStatsReport::Close()
{
	std::string openurl = "hiddenbar();location.href ='/fcgi-bin/statsreportlist.exe?";
	openurl += querystr;
	openurl += "'";
	WebSession::js_af_up = openurl;
}


typedef void(*func)(int , char **);

void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_GeneralTotalReport",title);
		}
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
	
    CGenStatsReport setform(app.root());
//	setform.appSelf = &app;
    app.exec();
}


int main(int argc, char *argv[])
{
    func p = usermain;
	if (argc == 1) 
    {
        char buf[256];
		
		WebSession s(buf, false);
        s.start(p);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }
    return 0;
}


