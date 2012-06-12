#pragma once

#include "WContainerWidget"
/////////////////////////////////
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class WTable;
class WText;
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
using namespace std;


struct MonitorItem
{
	string sName;
	string szGroupName;
	string sType;
	string sFrequest;
	string sClique;
	string sGoodClique;
	string sWarningClique;
	string sErrorClique;
};

class CMonitorDetail :	public WContainerWidget
{
	//MOC: W_OBJECT CMonitorDetail:WContainerWidget
    W_OBJECT;
public:
	CMonitorDetail(WContainerWidget *parent = 0);
	~CMonitorDetail(void);

private slots:
    //MOC: SLOT CMonitorDetail::LogForward()
    void LogForward();	
    //MOC: SLOT CMonitorDetail::LogBack()
    void LogBack();	
    //MOC: SLOT CMonitorDetail::ExportExcel()
    void ExportExcel();	
    //MOC: SLOT CMonitorDetail::AutoClickHiddenBtn()
    void AutoClickHiddenBtn();	

private:
	void loadString();
	void initForm();
	void addColumn(WSVFlexTable * pParentTable);
	void getMonitors();
	void addData(WSVFlexTable * pParentTable);
	void addOperate(WSVFlexTable * pParentTable);
	void AddJsParam(const std::string name, const std::string value);
	void AddJsParamExecClick();
	virtual void refresh(); 

private:  //Wt
	WSVMainTable * m_pMainTable;
	WSVFlexTable * m_pUserListTable;
	WSVButton * m_pExport ;
	WSVButton * m_pHidden ;
	WText * m_pPage;
	WText * m_pPageCount;
	WText * m_pRecordCount;

private:
	MonitorItem iItem;
	list<MonitorItem> MonitorList;
	list<MonitorItem>::iterator RecordItem;
	list<MonitorItem>::iterator ItemForward;
	list<MonitorItem>::iterator ItemBack;
	string m_szMainTitile;
	string m_szName;
	string m_szGroupName;
	string m_szType;
	string m_szFrequent;
	string m_szValue;
	string m_szForward;
	string m_szBack;
	string m_szPage;
	string m_szPageCount;
	string m_szRecordCount;
	string m_szExport;
	string m_szMinute;
	string m_szHour;
	string m_szError;
	string m_szWarning;
	string m_szNormal;
	string m_szListHeights;	
	string m_szListPans;
	string m_szListTitles;
	string m_szListHeights1;	
	string m_szListPans1;
	string m_szListTitles1;
	string m_szGoodValue;
	string m_szWarningValue;
	string m_szErrorValue;
	string m_szDownLoad;
	string m_szConfirm;
	string strRefresh;

	int m_iForwardORBack;
	bool m_bRefresh;
};
