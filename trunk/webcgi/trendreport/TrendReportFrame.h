/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
// This may look like C code, but it's really -*- C++ -*-
#ifndef TRENDREPORT_FRAME
#define TRENDREPORT_FRAME

#include "TrendReport.h"

#include "CheckBoxTreeView.h"
#include <WContainerWidget>
class WText;
class WTable;
class WTreeNode;
class WLineEdit;
class WTreeNode;
class WComboBox;
class WPushButton;
class CTrendReport;
class CCheckBoxTreeView;
class WApplication;

//new ui class
class WSVMainTable;
class WSVFlexTable;
class WSTreeAndPanTable;


class TrendReportFrame : public WContainerWidget
{
    //MOC: W_OBJECT TrendReportFrame:WContainerWidget
    W_OBJECT;

public:

    TrendReportFrame(WContainerWidget *parent);
    ~TrendReportFrame();

    virtual void refresh();
	void loadString();

	string m_szObjID;
	string getResizeObjectID() {return m_szObjID;};
	void AddJsParam(const std::string name, const std::string value);
	void AddJsParamToTable(const std::string name, const std::string value);

	TTime m_startTime;
	TTime m_endTime;
	string m_strMonitorid;
	
	CTrendReport * m_trendReport;
	CCheckBoxTreeView * m_pTrendReportTree;
	WTable * reportTable;

	void ChangeTrendReport(string strMonitorid, TTime startTime, TTime endTime);

	WApplication*  appSelf;

public signals:
private slots:
    //MOC: SLOT TrendReportFrame::TrendReportQuery()
    void TrendReportQuery();
    //MOC: SLOT TrendReportFrame::ReportQueryResponse()
    void ReportQueryResponse();
    //MOC: SLOT TrendReportFrame::Query2HourText()
    void Query2HourText();
    //MOC: SLOT TrendReportFrame::Query4HourText()
    void Query4HourText();
    //MOC: SLOT TrendReportFrame::Query8HourText()
    void Query8HourText();
    //MOC: SLOT TrendReportFrame::Query1DayText()
    void Query1DayText();
    //MOC: SLOT TrendReportFrame::Query3DayText()
    void Query3DayText();
    //MOC: SLOT TrendReportFrame::Query5DayText()
    void Query5DayText();
    //MOC: SLOT TrendReportFrame::Query1WeekText()
    void Query1WeekText();
    //MOC: SLOT TrendReportFrame::QueryCurWeekText()
    void QueryCurWeekText();
    //MOC: SLOT TrendReportFrame::Query1MonthText()
    void Query1MonthText();
    //MOC: SLOT TrendReportFrame::Query3MonthText()
    void Query3MonthText();
    //MOC: SLOT TrendReportFrame::Query6MonthText()
    void Query6MonthText();
    //MOC: SLOT TrendReportFrame::QueryCurDayText()
    void QueryCurDayText();
	//MOC: SLOT TrendReportFrame::Translate()
	void Translate();
	//MOC: SLOT TrendReportFrame::ExChange()
	void ExChange();
private:

	WLineEdit * pAlertStartTime;
	WLineEdit * pAlertEndTime;

	std::string strStartTimeDes;
	std::string strEndTimeDes;
	std::string strStartTimeLabel;
	std::string strEndTimeLabel;
	std::string	strQueryBtn;
	std::string	strTrendTitle;
	std::string strWeek;
	std::string strDay;

	string strRefresh;	
	
	CMainTable * pMainTable;

	//New Version 7.0 --by AndiLiu
	WSTreeAndPanTable *m_treePanelTable;
	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pQueryTable;
	string strListHeights;
	string strListPans;
	string strListTitles;

	WPushButton *pExChangeBtn;
	WPushButton *pTranslateBtn;

	void initTreeTable();
	void initQueryTable(WSVFlexTable **p_QueryTable ,int nRow,std::string strTitle, WSVMainTable * pMainTable);
};

#endif // TRENDREPORT_FRAME