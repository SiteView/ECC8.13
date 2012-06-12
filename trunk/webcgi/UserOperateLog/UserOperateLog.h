#pragma once

#include "WContainerWidget"
#include <WPushButton>

class WApplication;
class WTable;
class CMainTable;
class CFlexTable;
class WComboBox;
class WText;
class WLineEdit;
class WImage;

class WSVMainTable;
class WSVFlexTable;
class WSVButton;


#include <list>

#include "../base/OperateLog.h"

using namespace std;

class CUserOperateLog :	public WContainerWidget
{
	//MOC: W_OBJECT CUserOperateLog:WContainerWidget
    W_OBJECT;

public:
	CUserOperateLog(WContainerWidget *parent = 0);
	~CUserOperateLog(void);


public:
	WApplication *  appSelf;

private:
	//WScrollArea * pUserScrollArea;
	CMainTable * m_pMainTable;
	CFlexTable * m_pUserListTable;
	WTable * m_pLogTable;
	WComboBox * m_cUserName;
	WComboBox * m_cOperateType;
	WComboBox * m_cOperateObject;
	WPushButton * m_Btn;
	WLineEdit * m_EStartTime;
	WLineEdit * m_EEndTime;
	WTable *mNullTable;
	WTable *mOperateTable;
	WImage * pForward;
	WImage * pBack;
	WText * m_szPage;
	WText * m_szPageCout;
	WText * m_szRecordCount;
	WText *nText;


	WSVMainTable *pMainTable;
	WSVFlexTable *pQueryTable;
	WSVFlexTable *pUserListTable;


	string strListHeights;
	string strListPans;
	string strListTitles;


	//
	int nCurPage;
	int nTotalPage;
	int nPageCount;
	bool bDivide;
	std::string strReocrdIni;
	std::string strPageCount;
	std::string strRecordCount;
	std::string strPage;
	std::string strNoSortRecord;
	WText *pTextTipInfo;
	void AddLogItem(int iRow, string userName, string operObj, string operType, string operTime, string operObjInfo);
	void RefreshList();
	WPushButton *pExChangeBtn;
	WPushButton *pTranslateBtn;

	
private:
	void ShowMainTable();
	void loadString();
	void AddLogColumn(WTable* pContain);
	void refresh();

	void AddJsParam(const std::string name, const std::string value);

private:
	OperateLog m_pLog;
	string m_szMainTitle;
	string m_szUserName;
	string m_szOperateObj;
	string m_szOperateType;
	string m_szOperateTime;
	string m_szOperateObjInfo;
	string m_szStartTime;
	string m_szEndTime;
	string m_szQuery;
	string m_szAll;
	string m_szLogNull;
	string strForward;
	string strBack;
	list<OperateLogItem> RecordsList;
	list<OperateLogItem>::iterator RecordsListItem;
	list<OperateLogItem>::iterator RecordsListItemTempForward;
	list<OperateLogItem>::iterator RecordsListItemTempBack;

	/*************************
	*	m_szForwardORBack
	*
	*	 0  查询
	*	 1  向前
	*    2  向后
	*************************/
	int m_szForwardORBack;

	string m_szUserNameHelp;	
	string m_szOperateObjHelp;	
	string m_szStartTimeHelp;	
	string m_szEndTimeHelp;	
	string m_szOperateTypeHelp;	
private slots:
    //MOC: SLOT CUserOperateLog::LogQuery()
    void LogQuery();	
    //MOC: SLOT CUserOperateLog::LogForward()
    void LogForward();	
    //MOC: SLOT CUserOperateLog::LogBack()
    void LogBack();	

	void ShowHelp();
};
