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

#include "TrendReportFrame.h"
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

#include "TrendReportFrame.h"


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
#include "../base/OperateLog.h"

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
   // PrintDebugString(szMsg.c_str());
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
void TrendReportFrame::loadString()
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
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
		}
		CloseResource(objRes);
	}
/*
	strStartTimeLabel = "开始时间：";
	strStartTimeDes = "开始时间";
	strEndTimeLabel = "结束时间：";
	strEndTimeDes = "结束时间";
	strQueryBtn = "查  询";
	strTrendTitle = "趋势报告";
	*/
}

void TrendReportFrame::initTreeTable()
{
	strListHeights = "";
	strListPans = "";
	strListTitles = "";
	//
	m_treePanelTable = new WSTreeAndPanTable(this);
	//AddJsParamToTable("treeviewPanel", m_treePanelTable->formName());
	AddJsParam("treeviewPanel", m_treePanelTable->formName());

	//TreeTable
	new WText("<div id='tree_panel' name='tree_panel' class='panel_tree'>", m_treePanelTable->elementAt(0, 0));
	WTable * pTreeTable = new WTable(m_treePanelTable->elementAt(0, 0));
	new WText(" &nbsp;",pTreeTable->elementAt(0,0));
	pTreeTable->elementAt(0,0)->setContentAlignment(AlignCenter | AlignTop);
	m_pTrendReportTree = new CCheckBoxTreeView((WTableCell*)pTreeTable->elementAt(0,0));
	//new WText("<br>", m_pTrendReportTree->elementAt(0, 0));
	if(m_pTrendReportTree)
	{
		string strSection = GetWebUserID();
		m_pTrendReportTree->InitTree("", false, false, false, strSection);
		WObject::connect(m_pTrendReportTree, SIGNAL(ReportQueryRequest()), this, SLOT(ReportQueryResponse()));
	}
	m_pTrendReportTree->setStyleClass("viewtreebody");
	new WText("</div>", pTreeTable->elementAt(0, 0));

	//DragTable
	AddJsParam("drag_tree", m_treePanelTable->elementAt(0, 1)->formName());
	//AddJsParamToTable("drag_tree", m_treePanelTable->elementAt(0, 1)->formName());

	//PanTable
	new WText("<div id='view_panel' class='panel_view'>", m_treePanelTable->elementAt(0, 2));

	m_pMainTable = new WSVMainTable(m_treePanelTable->elementAt(0, 2), strTrendTitle, true);

	if (m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg,SIGNAL(click()),this,SLOT(ShowHelp()));
	}

	initQueryTable(&m_pQueryTable, 1, "", m_pMainTable);

	new WText("</div>", m_treePanelTable->elementAt(0, 2));
}

//
void TrendReportFrame::initQueryTable(WSVFlexTable **pFlexTable_Add ,int nRow,std::string strTitle, WSVMainTable * pUserTable)
{
	*pFlexTable_Add = new WSVFlexTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(nRow,0), Blank, strTitle); 

	WSVFlexTable *pFlexTable = *pFlexTable_Add;



	if(pFlexTable->GetContentTable() != NULL)
	{
		//标题链接
		WTable *QueryTitleTable1 = new WTable(pFlexTable->GetContentTable()->elementAt(0,0));

		QueryTitleTable1->elementAt(0, 1)->resize(WLength(8,WLength::Percentage),0);
		WText * p2HourText = new WText("2h", QueryTitleTable1->elementAt(0, 1));
		p2HourText->setStyleClass("linktext");
		connect(p2HourText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query2HourText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 2)->resize(WLength(8,WLength::Percentage),0);
		WText * p4HourText = new WText("4h", QueryTitleTable1->elementAt(0, 2));
		p4HourText->setStyleClass("linktext");
		connect(p4HourText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query4HourText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 3)->resize(WLength(8,WLength::Percentage),0);
		WText * p8HourText = new WText("8h", QueryTitleTable1->elementAt(0, 3));
		p8HourText->setStyleClass("linktext");
		connect(p8HourText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query8HourText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 4)->resize(WLength(8,WLength::Percentage),0);
		WText * p1DayText = new WText("1d", QueryTitleTable1->elementAt(0, 4));
		p1DayText->setStyleClass("linktext");
		connect(p1DayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query1DayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 5)->resize(WLength(8,WLength::Percentage),0);
		WText * p3DayText = new WText("3d", QueryTitleTable1->elementAt(0, 5));
		p3DayText->setStyleClass("linktext");
		connect(p3DayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query3DayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 6)->resize(WLength(8,WLength::Percentage),0);
		WText * p5DayText = new WText("5d", QueryTitleTable1->elementAt(0, 6));
		p5DayText->setStyleClass("linktext");
		connect(p5DayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query5DayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 7)->resize(WLength(8,WLength::Percentage),0);
		WText * p1WeekText = new WText("1w", QueryTitleTable1->elementAt(0, 7));
		p1WeekText->setStyleClass("linktext");
		connect(p1WeekText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query1WeekText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 8)->resize(WLength(12,WLength::Percentage),0);
		WText * pCurWeekText = new WText(strWeek, QueryTitleTable1->elementAt(0, 8));
		pCurWeekText->setStyleClass("linktext");
		connect(pCurWeekText, SIGNAL(clicked()), "showbar();" ,this, SLOT(QueryCurWeekText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 9)->resize(WLength(8,WLength::Percentage),0);
		WText * p1MonthText = new WText("1m", QueryTitleTable1->elementAt(0, 9));
		p1MonthText->setStyleClass("linktext");
		connect(p1MonthText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query1MonthText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 10)->resize(WLength(8,WLength::Percentage),0);
		WText * p3MonthText = new WText("3m", QueryTitleTable1->elementAt(0, 10));
		p3MonthText->setStyleClass("linktext");
		connect(p3MonthText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query3MonthText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 11)->resize(WLength(8,WLength::Percentage),0);
		WText * p6MonthText = new WText("6m", QueryTitleTable1->elementAt(0, 11));
		p6MonthText->setStyleClass("linktext");
		connect(p6MonthText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query6MonthText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		QueryTitleTable1->elementAt(0, 12)->resize(WLength(12,WLength::Percentage),0);
		WText * pCurDayText = new WText(strDay, QueryTitleTable1->elementAt(0, 12));
		pCurDayText->setStyleClass("linktext");
		connect(pCurDayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(QueryCurDayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

		//时间
		WTable * QueryTitleTable2 = new WTable((WContainerWidget *)pFlexTable->GetContentTable()->elementAt(1,0));
		pFlexTable->GetContentTable()->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);

		QueryTitleTable2->resize(WLength(100,WLength::Percentage),WLength(30,WLength::Pixel));
		TTime curTime = TTime::GetCurrentTimeEx();
		new WText(strStartTimeLabel, QueryTitleTable2->elementAt(0, 0));
		pAlertStartTime = new WLineEdit("", QueryTitleTable2->elementAt(0, 1));
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		pAlertStartTime->setText(curTime.Format());
		pAlertStartTime->setStyleClass("input_text");
		strcpy(pAlertStartTime->contextmenu_ , "onFocus=\"calendar()\"");

		curTime = TTime::GetCurrentTimeEx();
		new WText(strEndTimeLabel, QueryTitleTable2->elementAt(0, 3));
		pAlertEndTime = new WLineEdit("", QueryTitleTable2->elementAt(0, 4));
		pAlertEndTime->setText(curTime.Format());
		pAlertEndTime->setStyleClass("input_text");
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
TrendReportFrame::TrendReportFrame(WContainerWidget *parent)
: WContainerWidget(parent)
{
    loadString();

	new WText("<SCRIPT language='JavaScript' src='/menu.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>", this);

	initTreeTable();

	m_trendReport = NULL;

	//pMainTable = new CMainTable(this, strTrendTitle);
 //   
	//pMainTable->setStyleClass("t5");
	//pMainTable->elementAt(3, 0)->setStyleClass("t5"); 

	//WTable * wholetable = new WTable(pMainTable->elementAt(3, 0));

	////WTable * wholetable = new WTable(this);
 //   wholetable->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
 //   wholetable->elementAt(0, 0)->resize(WLength(200), WLength(100,WLength::Percentage));

 //   WTable * MenuWholetable = new WTable(wholetable->elementAt(0, 0));
 //   MenuWholetable->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
	//
	//m_pTrendReportTree = new CCheckBoxTreeView((WTableCell*)MenuWholetable->elementAt(0,0));
	////PrintDebugString("----------------* CCheckBoxTreeView *----------------");
 //   if(m_pTrendReportTree)
	//{
 //       string strSection = GetWebUserID();
	//	m_pTrendReportTree->InitTree("", false, false, false, strSection);
	//	WObject::connect(m_pTrendReportTree, SIGNAL(ReportQueryRequest()), this, SLOT(ReportQueryResponse()));
	//}
	//m_pTrendReportTree->setStyleClass("viewtreebody");

 //   WScrollArea * table = new WScrollArea(MenuWholetable->elementAt(0,0));
 //   table->resize(WLength(200,WLength::Pixel), WLength(100,WLength::Percentage));
 //   table->setWidget(m_pTrendReportTree);
 //   table->setStyleClass("treebackgroup"); 
	//m_szObjID = table->formName();	

 //   WImage * spaceImage = new WImage("../Images/space.gif", (WContainerWidget *)wholetable->elementAt(0, 1));
 //   wholetable->elementAt(0, 1)->setStyleClass("menuresize");
 //   strcpy(wholetable->elementAt(0, 1)->contextmenu_, 
 //       "onmousedown='_canResize=true;this.setCapture(true)' onmouseup='this.releaseCapture();_canResize=false;'");

	//WTable *rightTable = new WTable((WContainerWidget *)wholetable->elementAt(0, 2));

 //   rightTable->setStyleClass("t5");
 //   rightTable->elementAt(0, 0)->setContentAlignment(AlignTop);
 //   rightTable->elementAt(0, 0)->setStyleClass("t5");

	//WTable * rightContentTble = new WTable((WContainerWidget *)rightTable->elementAt(0, 0));
	//rightContentTble->setStyleClass("t5");
	//
	//WTable * QueryTitleTable = new WTable((WContainerWidget *)rightContentTble->elementAt(0, 0));
	//QueryTitleTable->setStyleClass("t6");
	//rightTable->elementAt(0, 0)->setContentAlignment(AlignCenter);

	//WTable * QueryTitleTable1 = new WTable((WContainerWidget *)QueryTitleTable->elementAt(0, 0));
	//QueryTitleTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	//
	//WText * p2HourText = new WText("&nbsp;&nbsp;2h&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 1));
	//p2HourText->setStyleClass("nullLink");
	//connect(p2HourText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query2HourText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 1));

	//WText * p4HourText = new WText("&nbsp;&nbsp;4h&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 2));
	//p4HourText->setStyleClass("nullLink");
	//connect(p4HourText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query4HourText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 2));

	//WText * p8HourText = new WText("&nbsp;&nbsp;8h&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 3));
	//p8HourText->setStyleClass("nullLink");
	//connect(p8HourText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query8HourText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 3));

	//WText * p1DayText = new WText("&nbsp;&nbsp;1d&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 4));
	//p1DayText->setStyleClass("nullLink");
	//connect(p1DayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query1DayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 4));

	//WText * p3DayText = new WText("&nbsp;&nbsp;3d&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 5));
	//p3DayText->setStyleClass("nullLink");
	//connect(p3DayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query3DayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 5));

	//WText * p5DayText = new WText("&nbsp;&nbsp;5d&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 6));
	//p5DayText->setStyleClass("nullLink");
	//connect(p5DayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query5DayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 6));

	//WText * p1WeekText = new WText("&nbsp;&nbsp;1w&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 7));
	//p1WeekText->setStyleClass("nullLink");
	//connect(p1WeekText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query1WeekText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 7));

	//WText * pCurWeekText = new WText(strWeek, QueryTitleTable1->elementAt(0, 8));
	//pCurWeekText->setStyleClass("nullLink");
	//connect(pCurWeekText, SIGNAL(clicked()), "showbar();" ,this, SLOT(QueryCurWeekText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 8));

	//WText * p1MonthText = new WText("&nbsp;&nbsp;1m&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 9));
	//p1MonthText->setStyleClass("nullLink");
	//connect(p1MonthText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query1MonthText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 9));

	//WText * p3MonthText = new WText("&nbsp;&nbsp;3m&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 10));
	//p3MonthText->setStyleClass("nullLink");
	//connect(p3MonthText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query3MonthText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 10));

	//WText * p6MonthText = new WText("&nbsp;&nbsp;6m&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 11));
	//p6MonthText->setStyleClass("nullLink");
	//connect(p6MonthText, SIGNAL(clicked()), "showbar();" ,this, SLOT(Query6MonthText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 11));

	//WText * pCurDayText = new WText(strDay, QueryTitleTable1->elementAt(0, 12));
	//pCurDayText->setStyleClass("nullLink");
	//connect(pCurDayText, SIGNAL(clicked()), "showbar();" ,this, SLOT(QueryCurDayText()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//new WText("&nbsp;&nbsp;", QueryTitleTable1->elementAt(0, 12));

	//WTable * QueryTitleTable2 = new WTable((WContainerWidget *)QueryTitleTable->elementAt(1, 0));
	//QueryTitleTable->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);

	//WTable * leftQueryTable = new WTable(QueryTitleTable2->elementAt(0, 0));
	//WTable * rightQueryTable = new WTable(QueryTitleTable2->elementAt(0, 1));

	//QueryTitleTable2->elementAt(0, 0)->setStyleClass("tleft");
	//QueryTitleTable2->elementAt(0, 1)->setStyleClass("trigtht");

	//TTime curTime = TTime::GetCurrentTimeEx();
	//new WText(strStartTimeLabel, leftQueryTable->elementAt(2, 0));
	//new WText("&nbsp;&nbsp;", leftQueryTable->elementAt(2, 0));
	//pAlertStartTime = new WLineEdit("", leftQueryTable->elementAt(2, 1));
	//TTimeSpan ts(0,24,0,0);
	//curTime -= ts;
	//pAlertStartTime->setText(curTime.Format());
	//pAlertStartTime->setStyleClass("ttext");
 //   //strcpy(pAlertStartTime->contextmenu_ , "onkeyDown=\"validate(this,3)\"");
	//strcpy(pAlertStartTime->contextmenu_ , "onFocus=\"calendar()\"");
	////pMainTable->AddHelpText(leftTable, strStartTimeDes, 3, 1);

	//curTime = TTime::GetCurrentTimeEx();
	//new WText(strEndTimeLabel, rightQueryTable->elementAt(2, 0));
	//new WText("&nbsp;&nbsp;", rightQueryTable->elementAt(2, 0));
	//pAlertEndTime = new WLineEdit("", rightQueryTable->elementAt(2, 1));
	//pAlertEndTime->setText(curTime.Format());
	//pAlertEndTime->setStyleClass("ttext");
	//strcpy(pAlertEndTime->contextmenu_ , "onFocus=\"calendar()\"");
	////pMainTable->AddHelpText(rightTable, strEndTimeDes, 3, 1);

	//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)rightQueryTable->elementAt(2, 2));
	//WPushButton * pQueryBtn = new WPushButton(strQueryBtn, (WContainerWidget *)rightQueryTable->elementAt(2, 2));
	//rightQueryTable->elementAt(2, 2)->setContentAlignment(AlignCenter);
	//pQueryBtn->setStyleClass("wizardbutton");	
	//connect(pQueryBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(TrendReportQuery()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

	//reportTable = new WTable((WContainerWidget *)rightContentTble->elementAt(1, 0));
	//rightContentTble->elementAt(1, 0)->setStyleClass("t5");
	//reportTable->setStyleClass("t5");

	//WScrollArea * scrollarea = new WScrollArea(rightContentTble->elementAt(1,0));
	//scrollarea->setStyleClass("t5");	
	//scrollarea->setWidget(reportTable);

	//AddJsParam("tableName", wholetable->formName());


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
//	new WText("<Script language='javascript'>SetTreeViewPanel();</script>",this); // 该行代码因为主动刷新页面引起AJAX自动刷新机制偶尔出现页面不能完整显示而被注释
}

//
TrendReportFrame::~TrendReportFrame()
{

}


//
void TrendReportFrame::refresh()
{
	OutputDebugString("----------TrendReportFrame Refresh------------\n");
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//刷新树
	string strSection = GetWebUserID();
	m_pTrendReportTree->InitTree("", false, false, false, strSection);

	//if(m_treePanelTable != NULL)
	//{
	//	m_treePanelTable->clear();
	//	delete m_treePanelTable;
	//	m_treePanelTable = NULL;
	//	
	//	/*this->clear();*/
	//	//m_treePanelTable->hide();
	//	//m_treePanelTable->show();
	//	//m_treePanelTable->refresh();
	//	//
	//	//m_pTrendReportTree->hide();
	//	//m_pTrendReportTree->show();
	//	//m_pTrendReportTree->refresh();
	//	//
	//	//m_pMainTable->hide();
	//	//m_pMainTable->show();
	//	//m_pMainTable->refresh();
	//	//
	//	//m_pQueryTable->hide();
	//	//m_pQueryTable->show();
	//	//m_pQueryTable->refresh();

	//	//this->refresh();

	//	initTreeTable();
	//}

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

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
void TrendReportFrame::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/trendreport.exe?'\",1250);  ";
	appSelf->quit();
}
void TrendReportFrame::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "trendreportRes";
	WebSession::js_af_up += "')";
}

//
void TrendReportFrame::TrendReportQuery()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "TrendReportQuery";
	LogItem.sDesc = strQueryBtn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	m_startTime = MakeTTime(pAlertStartTime->text());
	m_endTime = MakeTTime(pAlertEndTime->text());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void TrendReportFrame::AddJsParamToTable(const std::string name, const std::string value)
{
    std::string strTmp = "";
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    
	new WText(strTmp, m_treePanelTable->elementAt(0, 0));
}
//添加客户端脚本变量
void TrendReportFrame::AddJsParam(const std::string name, const std::string value)
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
void TrendReportFrame::ReportQueryResponse()
{
	//PrintDebugString("ReportQueryResponse");
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	m_startTime = MakeTTime(pAlertStartTime->text());
	m_endTime = MakeTTime(pAlertEndTime->text());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
}

//
void TrendReportFrame::Query2HourText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0,2,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query4HourText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0,4,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query8HourText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	TTimeSpan ts(0,8,0,0);
	m_startTime = m_endTime - ts;

	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query1DayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(1,0,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query3DayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(3,0,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query5DayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(5,0,0,0);
	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query1WeekText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(7, 0,0,0);
	m_startTime = m_endTime - ts;

	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::QueryCurWeekText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	int nDay = m_endTime.GetWeekDay();
	TTimeSpan ts(nDay, m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());

	m_startTime = m_endTime - ts;
	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query1MonthText()
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

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query3MonthText()
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

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::Query6MonthText()
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

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);	
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::QueryCurDayText()
{
	m_endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0, m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
	m_startTime = m_endTime - ts;

	m_strMonitorid = m_pTrendReportTree->getSelMonitorID();
	pAlertStartTime->setText(m_startTime.Format());
	pAlertEndTime->setText(m_endTime.Format());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";
}

//
void TrendReportFrame::ChangeTrendReport(string strMonitorid, TTime startTime, TTime endTime)
{

	if(m_trendReport == NULL)
	{
	//	m_trendReport = new CTrendReport(startTime, endTime, strMonitorid, true, true, true, true, true, (WContainerWidget *)reportTable->elementAt(0, 0));
	//	m_trendReport->setStyleClass("t5");

		m_trendReport = new CTrendReport(startTime, endTime, strMonitorid, true, true, true, true, true, (WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1, 0));

	}
	else
	{
		m_trendReport->clear();
		delete m_trendReport;
	//	m_trendReport  = new CTrendReport(startTime, endTime, strMonitorid, true, true, true, true, true, (WContainerWidget *)reportTable->elementAt(0, 0));
	//	m_trendReport->setStyleClass("t5");

		m_trendReport = new CTrendReport(startTime, endTime, strMonitorid, true, true, true, true, true, (WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1, 0));
	}

	//reportTable->elementAt(0, 0)->setStyleClass("t5");

}

////////////////////////////////////////////////////////////////////////////////////
typedef void( *func)(int , char **);

void wmain1(int argc, char *argv[])
{
  WApplication app(argc, argv);
  pTreeApp = &app;
  app.setTitle("Siteview 7.0");

  string strTmp = "";
  TrendReportFrame firsttest(app.root());
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

