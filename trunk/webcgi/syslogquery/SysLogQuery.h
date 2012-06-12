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
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class WPushButton;

typedef struct _SysLogItem
{
	string strSysLogTime;
	string strSysLogIp;
	string strSysLogMsg;
	int nFacility;
	int nSeverities;
}SysLogItem;

class CSysLogQuery  :WContainerWidget
{
    //MOC: W_OBJECT CSysLogQuery:WContainerWidget
    W_OBJECT;
public:
    CSysLogQuery(WContainerWidget *parent = 0);

public : //add user var	
	//SVTable m_svAlertHistoryList;

	//报警列表
	CMainTable * pMainTable;
	
	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pSysLogTable;
	WSVFlexTable *m_pSysLogListTable;

	
	//报警历史报表
	CFlexTable * pSysLogTable;
	WTable * pSysLogListTable;
	WImage * pForward;
	WImage * pBack;
	WText * pTextTipInfo;

	WLineEdit * pSysLogMsg;
	WLineEdit * pSysLogIp;
	WLineEdit * pSysLogStartTime;
	WLineEdit * pSysLogEndTime;
	WLineEdit * pFacility;
	WLineEdit * pSeverities;
	//WComboBox * pFacilityBox;
	//WComboBox * pSeveritiesBox;

	WPushButton *pTranslateBtn;
	WPushButton *pExChangeBtn;

	//
	int nCurPage;
	int nTotalPage;
	int nPageCount;
	bool bDivide;
	
	//std::vector<WText *> m_pListItemText ;

	list<SysLogItem *> m_SysLogList;
	map<string, int, less<string> > pSysLogRightMap;
	map<string, int, less<string> > mapFacility;
	map<string, int, less<string> > mapSeverities;
public:
	void ShowMainTable();
	void QueryRecordSet(string strTableName);
	void RefreshList();
	bool IsCondMatch(int nCond, string strCondValue, int nCondValue);
	void AddSysLogColum(WTable* pContain);
	void AddSysLogItem(string strSysLogTime, string strSysLogIp, string strSysLogMsg, int nFacility, int nSeverities);

	void AddSysLogItemNew(int numRow,string strSysLogTime, string strSysLogIp, string strSysLogMsg, int nFacility, int nSeverities);

	void AddJsParam(const std::string name, const std::string value);
	BOOL ParserContent( char *  content,long &lTotalLine, long & lMatches ,char *matchstr,char *strmid,char * szResult);

	string GetFicilityStrFormInt(int nFacility);
	string GetSeveritiesStrFormInt(int nSeverities);

	~CSysLogQuery(void);
public : //language;

	//报警历史报表
	std::string strSysLogTiltle; 
	std::string strReturn;
	std::string strForward;
	std::string strBack;

	std::string strHSysLogMsgLabel;
	std::string strHSysLogTimeLabel;
	std::string strHSysLogIpLabel;
	std::string strHSysLogFacilityLabel;
	std::string strHSysLogSeveritiesLabel;

	std::string strSysLogMsgLabel;
	//std::string strSysLogTimeLabel;
	std::string strSysLogIpLabel;
	std::string strSysLogFacilityLabel;
	std::string strSysLogSeveritiesLabel;
	std::string strStartTimeLabel;
	std::string strEndTimeLabel;

	std::string strSysLogMsgDes;
	std::string strSysLogTimeDes;
	std::string strSysLogIpDes;
	std::string strSysLogFacilityDes;
	std::string strSysLogSeveritiesDes;
	std::string strStartTimeDes;
	std::string strEndTimeDes;
	
	std::string strQueryBtn;

	//Facility
	string strFacility0;
	string strFacility1;
	string strFacility2;
	string strFacility3;
	string strFacility4;
	string strFacility5;
	string strFacility6;
	string strFacility7;
	string strFacility8;
	string strFacility9;
	string strFacility10;
	string strFacility11;
	string strFacility12;
	string strFacility13;
	string strFacility14;
	string strFacility15;
	string strFacility16;
	string strFacility17;
	string strFacility18;
	string strFacility19;
	string strFacility20;
	string strFacility21;
	string strFacility22;
	string strFacility23;

	//Severities
	string strSeverities0;
	string strSeverities1;
	string strSeverities2;
	string strSeverities3;
	string strSeverities4;
	string strSeverities5;
	string strSeverities6;
	string strSeverities7;

	std::string strSysLogMsgCond;
	std::string strSysLogIpCond;
	//int nFacilityCond;
	//int nSeveritiesCond;
	std::string strFacilityCond;
	std::string strSeveritiesCond;
	std::string strStartTimeCond;
	std::string strEndTimeCond;	

	std::string strReocrdIni;
	std::string strPage;
	std::string strPageCount;
	std::string strNoSortRecord;
	std::string strRecordCount;


	string strListHeights;
	string strListPans;
	string strListTitles;

	WApplication*  appSelf;

	TTime startTime;
	TTime endTime;
private slots:
    //MOC: SLOT CSysLogQuery::SysLogBack()
    void SysLogBack();
    //MOC: SLOT CSysLogQuery::SysLogForward()
    void SysLogForward();
    //MOC: SLOT CSysLogQuery::SysLogReturnBtn()
    void SysLogReturnBtn();
	//MOC: SLOT CSysLogQuery::SysLogQuery()
	void SysLogQuery();
	//MOC: SLOT CSysLogQuery::Translate()
	void Translate();
	//MOC: SLOT CSysLogQuery::ExChange()
	void ExChange();

	void ShowHelp();
};