#include ".\GenHZDLReport.h"
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

//分解字符串
bool ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps)
{
	char * token = NULL;
	// duplicate string
	char * cp = ::strdup(pQueryString);
	if (cp)
	{
		char * pTmp = cp;
		if (pSVSeps) // using separators
			token = strtok( pTmp , pSVSeps);
		else // using separators
			return false;
		//token = strtok( pTmp, chDefSeps);
		// every field
		while( token != NULL )
		{
			//triml(token);
			//AddListItem(token);
			pTokenList.push_back(token);
			// next field
			if (pSVSeps)
				token = strtok( NULL , pSVSeps);
			else
				return false;
			//token = strtok( NULL, chDefSeps);
		}
		// free memory
		free(cp);
	}
	return true;
}

TTime MakeTTime(string strTime)
{
	if(strTime.empty())
	{
		TTime time;
		return time;
	}

	std::list<string> pTmpList;	
	ParserToken(pTmpList, strTime.c_str(), " ");

	string strYear, strMonth, strDay;
	std::list<string> pTmpList1;
	ParserToken(pTmpList1, pTmpList.front().c_str(), "-");

	strYear = pTmpList1.front();
	pTmpList1.pop_front();
	strMonth = pTmpList1.front();
	pTmpList1.pop_front();
	strDay = pTmpList1.front();
	pTmpList1.pop_front();

	string strHour, strMinute, strSecond;
	std::list<string> pTmpList2;
	ParserToken(pTmpList2, pTmpList.back().c_str(), ":");

	strHour = pTmpList2.front();
	pTmpList2.pop_front();
	strMinute = pTmpList2.front();
	pTmpList2.pop_front();
	strSecond = pTmpList2.front();
	pTmpList2.pop_front();

	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	sscanf(strYear.c_str(), "%d", &nYear);
	sscanf(strMonth.c_str(), "%d", &nMonth);
	sscanf(strDay.c_str(), "%d", &nDay);
	sscanf(strHour.c_str(), "%d", &nHour);
	sscanf(strMinute.c_str(), "%d", &nMinute);
	sscanf(strSecond.c_str(), "%d", &nSecond);	

	TTime time(nYear, nMonth, nDay, nHour, nMinute, nSecond);

	return time;
}

CGenHZDLReport::CGenHZDLReport(WContainerWidget *parent ):
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
			FindNodeValue(ResNode,"IDS_Start_Time1",strBeginTime);
			FindNodeValue(ResNode,"IDS_End_Time1",strEndTime);			
			FindNodeValue(ResNode,"IDS_General",strGeneral);		
		}
		CloseResource(objRes);
	}
	m_reportFrame = NULL;
	ShowMainTable();
}

CGenHZDLReport::~CGenHZDLReport(void)
{
}

void CGenHZDLReport::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	

	char cFile[1024]={0};
	sprintf(cFile,"%s\\data\\svdbconfig.ini",GetSiteViewRootPath().c_str());
	INIFile ini2 = LoadIni(cFile);
	std::string strLan= GetIniSetting(ini2,"svdb", "DefaultLanguage","chinese");

	string strJs;
	strJs ="<SCRIPT language='JavaScript' src='/"+strLan;
	strJs +="/Calendar.js'></SCRIPT>";
	new WText(strJs,this);
	new WText("<div id='view_panel' class='panel_view'>", this);

	pMainTable = new WSVMainTable(this, "", false);
			
	pFlexTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(0,0), Query, szCreateTitle);

	if (pFlexTable->GetContentTable() != NULL)
	{
		m_endTime = TTime::GetCurrentTimeEx();
		if(m_endTime.GetMonth() <= 1)
		{
			TTime tmpTime(m_endTime.GetYear() - 1, 13 - m_endTime.GetMonth(), m_endTime.GetDay(), m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
			m_startTime = tmpTime;
		}
		else
		{
			TTime tmpTime(m_endTime.GetYear() , m_endTime.GetMonth() - 1, m_endTime.GetDay(), m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
			m_startTime = tmpTime;
		}

		pFlexTable->AppendRows();
		starttimeedit = new WLineEdit("", pFlexTable->AppendRowsContent(0, 0, 1, strBeginTime, "", ""));
		starttimeedit->setText(m_startTime.Format());
		starttimeedit->resize(WLength(150,WLength::Pixel),0);
		starttimeedit->setStyleClass("input_text");
		strcpy(starttimeedit->contextmenu_ , "onClick=\"calendar()\"");

		pFlexTable->AppendRows();
		endtimeedit = new WLineEdit("", pFlexTable->AppendRowsContent(1, 0, 1, strEndTime, "", ""));
		endtimeedit->setText(m_endTime.Format());
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
	}

	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);
	new WText("</div>", this);
}

void CGenHZDLReport::ChangeTrendReport(TTime startTime, TTime endTime)
{
	if(m_reportFrame == NULL)
	{
		m_reportFrame = new CHZDLReport(startTime, endTime, (WContainerWidget *)pMainTable->GetContentTable()->elementAt(1, 0));
	}
	else
	{
		m_reportFrame->clear();
		delete m_reportFrame;

		m_reportFrame = new CHZDLReport(startTime, endTime, (WContainerWidget *)pMainTable->GetContentTable()->elementAt(1, 0));
	}
}

//生成报告
void CGenHZDLReport::FastGenReport()
{
	m_startTime = MakeTTime(starttimeedit->text());
	m_endTime = MakeTTime(endtimeedit->text());

	ChangeTrendReport(m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

typedef void (*wtmain)(int, char**);

void showMain(int argc, char *argv[])
{
	WApplication app(argc, argv);
	app.setTitle("生成定制报表");

	CGenHZDLReport setform(app.root());
	app.exec();
}

void CGenHZDLReport::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp = "";
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

/*
主函数 程序入口
*/
int main(int argc, char *argv[])
{
	wtmain pMain = showMain;
	if (argc == 1) 
	{
		srand((unsigned)time( NULL ));
		int rand1 = rand();
		char buf[256];
		itoa(rand1, buf, 10);
		WebSession s(buf, false);
		s.start(pMain);
		return 1;
	}
	else
	{
		FCGI_Accept();
		WebSession s("DEBUG", true);
		s.start(pMain);

		return 1;
	}
}