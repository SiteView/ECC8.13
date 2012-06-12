#pragma once
#include "WContainerWidget"
#include <string>
#include <list>
#include <iostream>
using namespace std;

#include <WPushButton>

class WTable;
class WText;
class WCheckBox;
class CFlexTable;
class CMainTable;
class WLineEdit;
class WImage;
class WApplication;


class WSVMainTable;
class WSVFlexTable;
class WSVButton;

//IP地址
typedef struct _IPAddress
{
	//是否验证
	int iCheck;
	//IP地址
	std::string strIPAddress;
	//保存天数
	std::string strDate;
}IPAddress,*PIPAddress;

class CSysLogSet :	public WContainerWidget
{
//MOC: W_OBJECT CSysLogSet:WContainerWidget
    W_OBJECT;
public:
	CSysLogSet(WContainerWidget *parent = 0);
	~CSysLogSet(void);

public:
	std::vector<WCheckBox *> m_pListFacBox;
	std::vector<WCheckBox *> m_pListServerBox;

	CMainTable * pMainTable;
	CFlexTable * pFacilityTable;
	CFlexTable * pSeveritiesTable;

	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pFacilityTable;
	WSVFlexTable *m_pLevelTable;
	WSVFlexTable *m_pDeleteSetTable;

	
	CFlexTable * pDelSetTable;
	WLineEdit * pManualEdit;
	WLineEdit * pKeepDay;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	WApplication*  appSelf;

	virtual void refresh();

public:

	void ShowMainTable();
	void InitCheckBox();

public : //language;
	
	//
	string strMainTitle;
	string strTitle;
	string strFacilityTitle;
	string strSeveritiesTitle;

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

	string strDel;
	string strSave;

	string strDelSetTitle;
	string strManualDelLabel;
	string strManualDelDes;
	string strAutoDelLabel;
	string strAutoDelDes;
	string strSaveSucess;
	string strDelSucess;

	int refreshCount;

	string strOType;

	string strModifyFacility;
	string strDays;
	string strDelRecord;
	string strModifyLevel;
	string strRefresh;

private slots:
	//MOC: SLOT CSysLogSet::SaveFacility()
    void SaveFacility();
	//MOC: SLOT CSysLogSet::SaveSeverities()
	void SaveSeverities();
	//MOC: SLOT CSysLogSet::Translate()
	void Translate();
	//MOC: SLOT CSysLogSet::ExChange()
	void ExChange();
	//MOC: SLOT CSysLogSet::DelSysLogData()
	void DelSysLogData();
	//MOC: SLOT CSysLogSet::SaveKeepDay()
	void SaveKeepDay();

	void ShowHelp();
};
