#pragma once

#include "WContainerWidget"
#include <string>
#include <list>
#include <iostream>
using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

class WTable;
class WText;
class WImage;
class WLineEdit;
class CFlexTable;
class WComboBox;
class CMainTable;
class WApplication;
class WPushButton;

class WSVMainTable;
class WSVFlexTable;
class WSVButton;

	


typedef struct _AlertLogItem
{
	
	string strListHeights;//
		string strListPans;//
	string strListTitles;//
	string strAlertName;
	string strMonitorName;
	string strEnitityName;
	string strAlertReceive;
	string strAlertTime;
	string strAlertType;
	string strAlertStatu;

}AlertLogItem;

class CAlertHistory  :WContainerWidget
{
    //MOC: W_OBJECT CAlertHistory:WContainerWidget
    W_OBJECT;
public:
    CAlertHistory(WContainerWidget *parent = 0);

public : //add user var	
	//SVTable m_svAlertHistoryList;

	//报警列表
	CMainTable * pMainTable;
	
	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pHistoryTable;
	WSVFlexTable *m_pHistoryListTable;


	//报警历史报表
	CFlexTable * pHistoryTable;

	WTable * pHistoryListTable;
	WImage * pForward;
	WImage * pBack;
	WText * pTextTipInfo;
	
		WText * m_szPage;
		WText * m_szPageCout;
		WText * m_szRecordCount;
		

	WLineEdit * pAlertName;
	WLineEdit * pAlertReceive;
	WLineEdit * pAlertStartTime;
	WLineEdit * pAlertEndTime;
	WComboBox * pAlertType;

	WPushButton *pTranslateBtn;
	WPushButton *pExChangeBtn;

	WApplication *  appSelf;

	//
	int nCurPage;
	int nTotalPage;
	int nPageCount;
	bool bDivide;
	
	//std::vector<WText *> m_pListItemText ;

	list<AlertLogItem *> m_AlertLogList;
	map<string, int, less<string> > pAlertRightMap;
public:
	void ShowMainTable();
	void QueryRecordSet(string strTableName);
	void RefreshList();
	bool IsCondMatch(int nCond, string strCondValue);
	void AddHistoryColum(WTable* pContain);
	void AddListItem(string strAlertTime, string strAlertName, 
	string strDeveiceName, string strMonitorName, string strAlertReceive, string strAlertType, string strAlertState, int iRow);
	
	string GetAlertTypeStrFormInt(int nType);
	string GetAlertStatuStrFormInt(int nStatu);

	~CAlertHistory(void);
public : //language;

	//报警历史报表
	std::string strAlertHistoryTiltle; 
	std::string strReturn;
	std::string strForward;
	std::string strBack;
	std::string strStartTimeLabel;
	std::string strEndTimeLabel;
	

	std::string strHAlertNameLabel;
	std::string strHDeveiceNameLabel;
	std::string strHMonitorNameLabel;
	std::string strHAlertReceiveLabel;
	std::string strHAlertTypeLabel;
	std::string strHAlertStateLabel;
	std::string strHTimeLabel;

	std::string strAlertNameLabel;
	std::string strAlertNameDes;
	std::string strAlertReceiveLabel;
	std::string strAlertReceiveDes;
	std::string strAlertTimeDes;
	std::string strAlertTypeLabel;
	std::string strAlertTypeDes;
	std::string strStartTimeDes;
	std::string strEndTimeDes;

	std::string strAlertAll;
	std::string strEmailAlert;
	std::string strSmsAlert;
	std::string strScriptAlert;
	std::string strSoundAlert;
	std::string strQueryBtn;

	std::string strAlertNameCond;
	std::string strAlertReceiveCond;
	std::string strAlertTypeCond;
	std::string strStartTimeCond;
	std::string strEndTimeCond;	

	std::string strAlertLogRecordIni;
	std::string strNoSortRecord;
	TTime startTime;
	TTime endTime;
private slots:
    //MOC: SLOT CAlertHistory::AlertHistory(const std::string)
    void AlertHistory(const std::string strIndex);	
    //MOC: SLOT CAlertHistory::HistoryBack()
    void HistoryBack();	
    //MOC: SLOT CAlertHistory::HistoryForward()
    void HistoryForward();
    //MOC: SLOT CAlertHistory::HistoryReturnBtn()
    void HistoryReturnBtn();
	//MOC: SLOT CAlertHistory::AlertQuery()
	void AlertQuery();	
	//MOC: SLOT CAlertHistory::Translate()
	void Translate();
	//MOC: SLOT CAlertHistory::ExChange()
	void ExChange();
	void ShowHelp();
};