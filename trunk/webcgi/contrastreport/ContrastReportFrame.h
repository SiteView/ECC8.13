/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
// This may look like C code, but it's really -*- C++ -*-
#ifndef TRENDREPORT_FRAME
#define TRENDREPORT_FRAME

#include "contrastReport.h"

#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"

#include <WContainerWidget>
class WText;
class WTable;
class WTreeNode;
class WLineEdit;
class WTreeNode;
class WComboBox;
class WPushButton;
class CContrastReport;
class CCheckBoxTreeView;
class WApplication;
class WSTreeAndPanTable;

class ContrastReportFrame : public WContainerWidget
{
    //MOC: W_OBJECT ContrastReportFrame:WContainerWidget
    W_OBJECT;

public:

    ContrastReportFrame(WContainerWidget *parent);
    ~ContrastReportFrame();

    virtual void refresh();
	void loadString();

	string m_szObjID;
	string getResizeObjectID() {return m_szObjID;};
	void AddJsParam(const std::string name, const std::string value);

	TTime m_startTime;
	TTime m_endTime;
	string m_strMonitorid;
	
	CContrastReport * m_trendReport;
	CCheckBoxTreeView * m_pTrendReportTree;
	CCheckBoxTreeView * pTrendReportTree;//12/24


	WSTreeAndPanTable *m_pTreePanView;
	WTable * reportTable;
	WSVMainTable *m_pMainTable;
	WSVMainTable *m_rinhtTable;
	WSVFlexTable *timeTable;
	WSVFlexTable *listTable;

	WPushButton *pTranslateBtn;
	WPushButton *pExChangeBtn;




	void ChangeTrendReport(string strMonitorid, TTime startTime, TTime endTime);
	void GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_,std::list<string > &pUnGroupRightList_);
	void GetGroupRightList();
	void GetMonitorId(list<string> grouplist, list<string> & monitorlist);
	std::string GetLabelResource(std::string strLabel);
	WApplication*  appSelf;

	std::list<string> pGroupRightList;
	std::list<string> pUnGroupRightList;

	list<string> sml[1000];	
	string smlname[1000];
	int index ;

	OBJECT objRes;
	MAPNODE ResNode;

public signals:
private slots:
    //MOC: SLOT ContrastReportFrame::TrendReportQuery()
    void TrendReportQuery();
    //MOC: SLOT ContrastReportFrame::ReportQueryResponse()
    void ReportQueryResponse();
	//MOC: SLOT ContrastReportFrame::Translate()
	void Translate();
	//MOC: SLOT ContrastReportFrame::ExChange()
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
};

#endif // TRENDREPORT_FRAME