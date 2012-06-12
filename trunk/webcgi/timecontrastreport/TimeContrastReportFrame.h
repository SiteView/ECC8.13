/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
// This may look like C code, but it's really -*- C++ -*-
#ifndef TRENDREPORT_FRAME
#define TRENDREPORT_FRAME

#include "TimeContrastReport.h"

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


class CTimeContrastReportFrame : public WContainerWidget
{
    //MOC: W_OBJECT CTimeContrastReportFrame:WContainerWidget
    W_OBJECT;

public:

    CTimeContrastReportFrame(WContainerWidget *parent);
    ~CTimeContrastReportFrame();

    virtual void refresh();
	void loadString();

	string m_szObjID;
	string getResizeObjectID() {return m_szObjID;};
	void AddJsParam(const std::string name, const std::string value);

	TTime m_startTime;
	TTime m_endTime;
	string m_strMonitorid;
	string m_strMonitortemplate;
	
	CTimeContrastReport * m_trendReport;
	CCheckBoxTreeView * m_pTrendReportTree;
	WTable * reportTable;

	void ChangeTrendReport(string strMonitorid, string strMonitorTemplate, TTime startTime, TTime endTime, int selectType = 0);

	WApplication*  appSelf;


	string strTimeReport, strContrastType;
	string strByDay;
	string strByWeek;
	string strByMonth;
	string strTimePoint1;
	string strTimePoint2;

public signals:
private slots:
    //MOC: SLOT CTimeContrastReportFrame::TrendReportQuery()
    void TrendReportQuery();
    //MOC: SLOT CTimeContrastReportFrame::ReportQueryResponse()
    void ReportQueryResponse();
    //MOC: SLOT CTimeContrastReportFrame::Query2HourText()
    void Query2HourText();
    //MOC: SLOT CTimeContrastReportFrame::Query4HourText()
    void Query4HourText();
    //MOC: SLOT CTimeContrastReportFrame::Query8HourText()
    void Query8HourText();
    //MOC: SLOT CTimeContrastReportFrame::Query1DayText()
    void Query1DayText();
    //MOC: SLOT CTimeContrastReportFrame::Query3DayText()
    void Query3DayText();
    //MOC: SLOT CTimeContrastReportFrame::Query5DayText()
    void Query5DayText();
    //MOC: SLOT CTimeContrastReportFrame::Query1WeekText()
    void Query1WeekText();
    //MOC: SLOT CTimeContrastReportFrame::QueryCurWeekText()
    void QueryCurWeekText();
    //MOC: SLOT CTimeContrastReportFrame::Query1MonthText()
    void Query1MonthText();
    //MOC: SLOT CTimeContrastReportFrame::Query3MonthText()
    void Query3MonthText();
    //MOC: SLOT CTimeContrastReportFrame::Query6MonthText()
    void Query6MonthText();
    //MOC: SLOT CTimeContrastReportFrame::QueryCurDayText()
    void QueryCurDayText();
	//MOC: SLOT CTimeContrastReportFrame::Translate()
	void Translate();
	//MOC: SLOT CTimeContrastReportFrame::ExChange()
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

	CMainTable * pMainTable;



	//New Version 7.0 --by AndiLiu
	WSTreeAndPanTable *m_treePanelTable;
	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pQueryTable;
	string strListHeights;
	string strListPans;
	string strListTitles;
	WComboBox *m_cUserName;
	int strSelectType;

	WPushButton *pExChangeBtn;
	WPushButton *pTranslateBtn;

	void initTreeTable();
	void initQueryTable(WSVFlexTable **p_QueryTable ,int nRow,std::string strTitle, WSVMainTable * pMainTable);
};

#endif // TRENDREPORT_FRAME