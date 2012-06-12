#pragma once

#include "WContainerWidget"
/////////////////////////////////
#include "../base/OperateLog.h"
/////////////////////////////////
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class WLineEdit;
class WComboBox;
class WImage;
class WTable;
class WText;
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
using namespace std;


//////////////////////////////////
struct statLog
{
	string pProgram;
	string pFunc;
	string pDesc;
	int    pTimes;
	int    pAverTime;
};

class CHitLog :
	public WContainerWidget
{
	//MOC: W_OBJECT CHitLog:WContainerWidget
    W_OBJECT;
public:
	CHitLog(WContainerWidget *parent = 0);
	~CHitLog(void);

private: //WT
	//WScrollArea * pUserScrollArea;
	WSVMainTable * m_pMainTable;
	WSVFlexTable * m_pQueryTable;
	WSVFlexTable * m_pListTable;
	WSVFlexTable * m_pStatisticTable;
	WComboBox * m_cProgram;
	WComboBox * m_cFunc;
	WComboBox * m_cUserName;
	WComboBox * m_cKey;
	WComboBox * m_cChangePage;
	WSVButton * m_pExport ;
	WSVButton * m_Btn;
	WLineEdit * m_EStartTime;
	WLineEdit * m_EEndTime;
	WTable * m_pNullTable;
	WTable * m_pOperateTable;
	WImage * pForward;
	WImage * pBack;
	WText * m_Page;
	WText * m_PageCout;
	WText * m_RecordCount;
	list<HitLogQuery> LogList1;
	list<statLog> staLogList;

private slots:
	//MOC: SLOT CHitLog::ShowHideHelp()
	void ShowHideHelp();
    //MOC: SLOT CHitLog::LogQuery()
    void LogQuery();	
    //MOC: SLOT CHitLog::ShowFunc()
    void ShowFunc();	
     //MOC: SLOT CHitLog::ShowKey()
    void ShowKey();	
   //MOC: SLOT CHitLog::LogPrevious()
    void LogPrevious();	
    //MOC: SLOT CHitLog::LogNext()
    void LogNext();	
    //MOC: SLOT CHitLog::LogStaPrevious()
    void LogStaPrevious();	
    //MOC: SLOT CHitLog::LogStaNext()
    void LogStaNext();	
    //MOC: SLOT CHitLog::ExportExcel()
    void ExportExcel();	
    //MOC: SLOT CHitLog::ChangePage()
    void ChangePage();	

private:  //Func
	void ShowMainTable();
	void loadString();
	void AddLogColumn(WTable* pContain);
	virtual void refresh();
	void statisLog(string &strPro, string &strKeySort, list<HitLogQuery> &RecordList, list<statLog> &statiLogList);
	void AddJsParam(const std::string name, const std::string value);
	void ListPage();
	void StaListPage();

private:  //Var
	string m_szMainTitle;
	string m_szProgram;
	string m_szProgramHelp;
	string m_szFunc;
	string m_szFuncHelp;
	string m_szStartTime;
	string m_szStartTimeHelp;
	string m_szEndTime;
	string m_szEndTimeHelp;
	string m_szUserName;
	string m_szUserNameHelp;
	string m_szKey;
	string m_szKeyHelp;
	string m_szQuery;
	string m_szAll;
	string m_szLogList;
	string m_szLogStatisticList;
	string m_szLogNull;
	string m_szDes;
	string m_szFlag;
	string m_szInterval;
	string m_szTime;
	string m_szHitTimes;
	string m_szAverTime;
	string m_szPrevious;
	string m_szNext;
	string m_szReocrdIni;
	string m_szPage;
	string m_szPageCount;
	string m_szRecordCount;
	string m_szExport;
	string m_szDownLoad;
	string m_szConfirm;
	string m_szPageFront;
	string m_szPageBack;
	int nCurPage;
	int nTotalPage;
	int nSCurPage;
	int nSTotalPage;
};
