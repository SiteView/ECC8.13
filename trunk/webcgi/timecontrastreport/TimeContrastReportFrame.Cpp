/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
#include <boost/lexical_cast.hpp>
#include <fcgi_stdio.h>
//#include <cgi-util.h>

#include <WApplication>
#include <WText>
#include <WImage>
#include <WPushButton>
#include <WTable>
#include <WTableCell>
#include <WContainerWidget>
#include <WScrollArea>
#include <WLineEdit>

#include "TimeContrastReportFrame.h"
#include "WTreeNode.h"
#include "WStateIcon.h"
#include "websession.h"
#include "WLength"
#include "WComboBox"
#include "WBreak"

#include <stdlib.h>
#include <stdio.h>
#include "../../kennel/svdb/libutil/time.h"

#include <iostream>
#include <Algorithm>

#include "../../kennel/svdb/svapi/svapi.h"
#include "..\svtable\MainTable.h"

//new ui 
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"
#include "../svtable/WSTreeAndPanTable.h"

#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>
#include <WSVLinkText>

#include <WSlotInstance_>

#include "../group/basefunc.h"


WApplication *pTreeApp = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddTaskList(WComboBox * pTask = NULL)
{
    if(pTask)
    {
        list<string> lsTaskName;
        list<string>::iterator lsItem;

        if(GetAllTaskName(lsTaskName))
        {
            for(lsItem = lsTaskName.begin(); lsItem != lsTaskName.end(); lsItem ++)
            {
                string szName = (*lsItem);
                pTask->addItem(szName);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const string & szMsg)
{
 //   PrintDebugString(szMsg.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const char * szMsg)
{
#ifdef WIN32
    OutputDebugString(szMsg);
    OutputDebugString("\n");
#endif
}

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

//
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

//
void CTimeContrastReportFrame::loadString()
{ 
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Start_Time1",strStartTimeLabel);
			FindNodeValue(ResNode,"IDS_Start_Time1",strStartTimeDes);
			FindNodeValue(ResNode,"IDS_End_Time2",strEndTimeLabel);
			FindNodeValue(ResNode,"IDS_End_Time2",strEndTimeDes);
			FindNodeValue(ResNode,"IDS_Query",strQueryBtn);
			FindNodeValue(ResNode,"IDS_Trend_Report",strTrendTitle);
			FindNodeValue(ResNode,"IDS_The_Week",strWeek);
			FindNodeValue(ResNode,"IDS_The_Day",strDay);

			FindNodeValue(ResNode,"IDS_TimeContrastReport",strTimeReport);
			FindNodeValue(ResNode,"IDS_CONTRAST_BYDAY",strByDay);
			FindNodeValue(ResNode,"IDS_CONTRAST_BYWEEK",strByWeek);
			FindNodeValue(ResNode,"IDS_CONTRAST_BYMONTH",strByMonth);
			FindNodeValue(ResNode,"IDS_Contrast_TimePoint1",strTimePoint1);
			FindNodeValue(ResNode,"IDS_Contrast_TimePoint2",strTimePoint2);
			FindNodeValue(ResNode,"IDS_Contrast_Type",strContrastType);
		}
		CloseResource(objRes);
	}
}

void CTimeContrastReportFrame::initTreeTable()
{
	strListHeights = "";
	strListPans = "";
	strListTitles = "";
	//
	m_treePanelTable = new WSTreeAndPanTable(this);
	AddJsParam("treeviewPanel", m_treePanelTable->formName());

	//TreeTable
	new WText("<div id='tree_panel' name='tree_panel' class='panel_tree'>", m_treePanelTable->elementAt(0, 0));
	WTable * pTreeTable = new WTable(m_treePanelTable->elementAt(0, 0));
	new WText("&nbsp; ",pTreeTable->elementAt(0,0));
	pTreeTable->elementAt(0,0)->resize(WLength(0,WLength::Percentage),WLength(10,WLength::Pixel));
	pTreeTable->elementAt(1,0)->setContentAlignment(AlignCenter | AlignTop);
	m_pTrendReportTree = new CCheckBoxTreeView((WTableCell*)pTreeTable->elementAt(1,0));
	if(m_pTrendReportTree)
	{
		string strSection = GetWebUserID();
		m_pTrendReportTree->InitTree("", false, false, false, strSection);
		WObject::connect(m_pTrendReportTree, SIGNAL(ReportQueryRequest()), this, SLOT(ReportQueryResponse()));
	}
	m_pTrendReportTree->setStyleClass("viewtreebody");
	new WText("</div>", pTreeTable->elementAt(1, 0));

	//DragTable
	AddJsParam("drag_tree", m_treePanelTable->elementAt(0, 1)->formName());

	//PanTable
	new WText("<div id='view_panel' class='panel_view'>", m_treePanelTable->elementAt(0, 2));

	m_pMainTable = new WSVMainTable(m_treePanelTable->elementAt(0, 2), strTimeReport, true);

	if (m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg,SIGNAL(click()),this,SLOT(ShowHelp()));
	}

	initQueryTable(&m_pQueryTable, 1, "", m_pMainTable);

	new WText("</div>", m_treePanelTable->elementAt(0, 2));
}

//
void CTimeContrastReportFrame::initQueryTable(WSVFlexTable **pFlexTable_Add ,int nRow,std::string strTitle, WSVMainTable * pUserTable)
{
	*pFlexTable_Add = new WSVFlexTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(nRow,0), AlertSel, strTitle); 

	WSVFlexTable *pFlexTable = *pFlexTable_Add;

	if(pFlexTable->GetContentTable() != NULL)
	{
		pFlexTable->InitTable();
		pFlexTable->AppendRows();
		//用户
		m_cUserName = new WComboBox(pFlexTable->AppendRowsContent(0 ,0, 1, strContrastType, "", ""));
		m_cUserName->setStyleClass("input_text");
		m_cUserName->addItem(strByDay);
		m_cUserName->addItem(strByWeek);
		m_cUserName->addItem(strByMonth);

		pFlexTable->AppendRows();

		strStartTimeLabel = strTimePoint1;
		strEndTimeLabel   = strTimePoint2;
		//开始时间
		pAlertStartTime = new WLineEdit("", pFlexTable->AppendRowsContent(1, 0, 2, strStartTimeLabel, "", ""));	
		pAlertStartTime->setStyleClass("input_text");
		TTime curTime = TTime::GetCurrentTimeEx();
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		pAlertStartTime->setText(curTime.Format());
		strcpy(pAlertStartTime->contextmenu_ , "onFocus=\"calendar()\"");

		pAlertEndTime = new WLineEdit("", pFlexTable->AppendRowsContent(1, 1, 2 , strEndTimeLabel, "", ""));	
		pAlertEndTime->setStyleClass("input_text");
		curTime = TTime::GetCurrentTimeEx();
		pAlertEndTime->setText(curTime.Format());
		strcpy(pAlertEndTime->contextmenu_ , "onFocus=\"calendar()\"");
		pFlexTable->ShowOrHideHelp();
		pFlexTable->HideAllErrorMsg();
	}	

	if(pFlexTable->GetActionTable()!=NULL)
	{
		WTable *pTbl;
		pTbl = new WTable(pFlexTable->GetActionTable()->elementAt(0, 1));

		WSVButton * pQueryBtn = new WSVButton(pTbl->elementAt(0,0), strQueryBtn, "button_bg_m_black.png", "", true);
		connect(pQueryBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(TrendReportQuery()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	}
}

//
CTimeContrastReportFrame::CTimeContrastReportFrame(WContainerWidget *parent)
: WContainerWidget(parent)
{
    loadString();

	new WText("<SCRIPT language='JavaScript' src='/menu.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>", this);

	initTreeTable();

	m_trendReport = NULL;


	//翻译 & 刷新 Button
	pTranslateBtn = new WPushButton("Translate",this);
	pExChangeBtn = new WPushButton("Refresh",this);

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}


	AddJsParam("listheight", strListHeights);
	AddJsParam("listtitle", strListTitles);
	AddJsParam("listpan", strListPans);
	AddJsParam("bGeneral","true");
	AddJsParam("uistyle", "treepan");
	AddJsParam("fullstyle", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", this);
	new WText("<Script language='javascript'>SetTreeViewPanel();</script>",this);
}

//
CTimeContrastReportFrame::~CTimeContrastReportFrame()
{

}

//
void CTimeContrastReportFrame::refresh()
{
	//刷新树
	string strSection = GetWebUserID();
	m_pTrendReportTree->InitTree("", false, false, false, strSection);

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}


}
void CTimeContrastReportFrame::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/trendreport.exe?'\",1250);  ";
	appSelf->quit();
}
void CTimeContrastReportFrame::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "trendreportRes";
	WebSession::js_af_up += "')";
}

//
void CTimeContrastReportFrame::TrendReportQuery()
{
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	m_startTime = MakeTTime(pAlertStartTime->text());
	m_endTime = MakeTTime(pAlertEndTime->text());
	m_strMonitortemplate = "";
	strSelectType = m_cUserName->currentIndex();

	OBJECT hMon = GetMonitor(m_strMonitorid);		
	MAPNODE ma=GetMonitorMainAttribNode(hMon);
	FindNodeValue( ma,"sv_monitortype",m_strMonitortemplate);
	CloseMonitor(hMon);

	char tmp[100];
	sprintf(tmp, "value = %d\n" , strSelectType);
	OutputDebugString(tmp);

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate, m_startTime, m_endTime, strSelectType);
	WebSession::js_af_up = "hiddenbar()";
}

//添加客户端脚本变量
void CTimeContrastReportFrame::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp = "";
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    new WText(strTmp, this);
}

//
void CTimeContrastReportFrame::ReportQueryResponse()
{
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	m_startTime = MakeTTime(pAlertStartTime->text());
	m_endTime = MakeTTime(pAlertEndTime->text());
	m_strMonitortemplate = "";
	strSelectType = m_cUserName->currentIndex();

	OBJECT hMon = GetMonitor(m_strMonitorid);		
	MAPNODE ma=GetMonitorMainAttribNode(hMon);
	//monitortemplet ID
	FindNodeValue( ma,"sv_monitortype",m_strMonitortemplate);

	CloseMonitor(hMon);

	char tmp[100];
	sprintf(tmp, "value = %d\n" , strSelectType);
	OutputDebugString(tmp);

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate, m_startTime, m_endTime, strSelectType);
}

//
void CTimeContrastReportFrame::Query2HourText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0,2,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query4HourText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0,4,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate,m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query8HourText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	TTimeSpan ts(0,8,0,0);
	m_startTime = m_endTime - ts;

	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query1DayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(1,0,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate,m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query3DayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(3,0,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query5DayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(5,0,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query1WeekText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(7, 0,0,0);
	m_startTime = m_endTime - ts;

	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::QueryCurWeekText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	int nDay = m_endTime.GetWeekDay();
	TTimeSpan ts(nDay, m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());

	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query1MonthText()
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
	
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate,m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query3MonthText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	if(m_endTime.GetMonth() <= 3)
	{
		TTime tmpTime(m_endTime.GetYear() - 1, 13 - m_endTime.GetMonth(), m_endTime.GetDay(), m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
		m_startTime = tmpTime;
	}
	else
	{
		TTime tmpTime(m_endTime.GetYear() , m_endTime.GetMonth() - 3, m_endTime.GetDay(), m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
		m_startTime = tmpTime;
	}
	
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate,m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::Query6MonthText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	if(m_endTime.GetMonth() <= 6)
	{
		TTime tmpTime(m_endTime.GetYear() - 1, 13 - m_endTime.GetMonth(), m_endTime.GetDay(), m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
		m_startTime = tmpTime;
	}
	else
	{
		TTime tmpTime(m_endTime.GetYear() , m_endTime.GetMonth() - 6, m_endTime.GetDay(), m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
		m_startTime = tmpTime;
	}
	
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_strMonitortemplate,m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::QueryCurDayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0, m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
	m_startTime = m_endTime - ts;

	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid,m_strMonitortemplate, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void CTimeContrastReportFrame::ChangeTrendReport(string strMonitorid,string strMonitorTemplate, TTime startTime, TTime endTime, int selectType)
{

	if(m_trendReport == NULL)
	{
		m_trendReport = new CTimeContrastReport(startTime, endTime, strMonitorid, strMonitorTemplate, selectType ,true, true, true, true, true, (WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1, 0));
	}
	else
	{
		m_trendReport->clear();
		delete m_trendReport;
		m_trendReport = new CTimeContrastReport(startTime, endTime, strMonitorid, strMonitorTemplate,selectType, true, true, true, true, true, (WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1, 0));
	}
}

////////////////////////////////////////////////////////////////////////////////////
typedef void( *func)(int , char **);

void wmain1(int argc, char *argv[])
{
  WApplication app(argc, argv);
  pTreeApp = &app;
  app.setTitle("Siteview 7.0");

  string strTmp = "";
  CTimeContrastReportFrame firsttest(app.root());
  firsttest.appSelf = &app;

  app.setBodyAttribute(" class='workbody'");

  app.exec();
}

//
int main(int argc, char * argv[])
{
    func p = wmain1;
    if (argc == 1) 
    {
        srand((unsigned)time( NULL ));
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
        WebSession s(buf, false);
        //s.setRefreshTime(1);
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

//////////////////////////////////////////////////////////////////////////////////

