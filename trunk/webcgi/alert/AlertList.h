#pragma once

#include "WContainerWidget"
#include <string>
#include <list>
#include <iostream>
#include <SVTable.h>
using namespace std;
#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"
class WTable;
class WText;
class WImage;
class WCheckBox;
class WComboBox;
class WLineEdit;
class CFlexTable;
class CMainTable;
class WScrollArea;
class CAnswerTable;
class WRadioButton;
class WSelectionBox;
class CCheckBoxTreeView;
class WApplication;
#include "WSignalMapper"

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"
#include "WButtonGroup"
#include "WSTreeAndPanTable.h"

typedef struct _AlertLogItem
{
	string strAlertName;
	string strMonitorName;
	string strEnitityName;
	string strAlertReceive;
	string strAlertTime;
	string strAlertType;
	string strAlertStatu;
}AlertLogItem;

class CAlertList  :WContainerWidget
{
    //MOC: W_OBJECT CAlertList:WContainerWidget
    W_OBJECT;
public:
    CAlertList(WContainerWidget *parent = 0);

public:
    SVTable m_svAlertList;
	WTable * nullTable;
	WTable * nullTable1;
	bool bSaveAndAdd;
	string strGolobalType;
	string strOldAlertName;
	bool IsAlertNameExist(string strName);
	int GetIntFromAlertType(string strType);
	int GetIntFromAlertCond();
	string GetOnlyIndex(int nList);
	void RefreshAlertState(string strIndex, string strAlertState);
	void AddAlertItem(string strIndex, string strAlertName, string strAlertType, string strAlertCategory, string strAlertState);
	void EditAlertItem(string strIndex, string strAlertName, string strAlertType, string strAlertCategory);

	string strAlertTargerList;
	CCheckBoxTreeView * pAlertTargerTree;
	std::list<string> pAlertTargetList;
	std::list<string> pUnpAlertTargetList;

	void SetAlertTargetCheck();
	void GetAlertTargetList();
	void GetTreeChecked(WTreeNode * pNode,  std::list<string > &pAlertTargerList ,std::list<string > & pUnpAlertTargetList_);
	void SetTreeChecked(WTreeNode * pNode,  std::string  strAlertTargerList,bool bPCheck=false);

	void GetScriptFileFromServer();
	std::list<string>  GetScriptFileFromDirectory(string path);
	WSignalMapper m_alertMapper;     // 
	WSignalMapper m_historyMapper;   // 
	string strGenIndex; //-1 新增 否则 编辑
	
	virtual void refresh();

	//查询AlertLog日志相关

	int nCurPage;
	int nTotalPage;
	int nPageCount;
	bool bDivide;
	
	std::string strAlertNameCond;
	std::string strAlertTypeCond;

	list<AlertLogItem *> m_AlertLogList;

	void QueryRecordSet(string strTableName);
	void RefreshList();
	bool IsCondMatch(int nCond, string strCondValue);
	void AddListItem(string strAlertTime, string strAlertName, string strDeveiceName, 
	string strMonitorName, string strAlertReceive, string strAlertType, string strAlertState);

	string GetAlertTypeStrFormInt(int nType);
	string GetAlertStatuStrFormInt(int nStatu);

public : //add user var	

	WApplication*  appSelf;

	WPushButton * pHideButton;

	//报警列表
	CMainTable * pMainTable;
	
	CFlexTable * pAlertTable;
	WTable * pAlertListTable;
	WImage * pEnableAlert;
	WImage * pDisableAlert;
	//WText * pEnableAlert;
	//WText * pDisableAlert;
	
	CFlexTable * pAlertSelectTable;

	//报警历史报表
	bool bHistoryTable;
	CFlexTable * pHistoryTable;
	WTable * pHistoryListTable;
	WImage * pForward;
	WImage * pBack;
	
	//
	WText * pTextTipInfo;	

	//报警编辑
	CAnswerTable * pAlertAddTable;		
	CFlexTable * pAlertBaseTable;
	CFlexTable * pAlertConditionTable;
	
	//基础属性
	WLineEdit * pAlertName;
	//CCheckBoxTreeView * pAertTargrt;
	WLineEdit * pAlertUpgrade;
	WLineEdit * pAlertUpgradeTo;
	//为解决Ticket #112 东方有线ECC邮件报警主题定制问题而增加下面代码。
	//苏合 2007-08-02

	//+++++++++++++++++++++++++++代码增加开始  苏合 2007-08-02+++++++++++++++++++++++++++
	WCheckBox *pCheckBox;
	WLineEdit * pAlertEmailTitle;
	//+++++++++++++++++++++++++++代码增加结束  苏合 2007-08-02+++++++++++++++++++++++++++
	WLineEdit * pAlertStop;

	//
	//WTable * pEmailTable;
	WSelectionBox * pEmailAdress;
	WLineEdit * pOtherAdress;
	WComboBox * pEmailTemplate;
	WText * pEmailAdressLabel;
	WText * pEmailTemplateLabel;

	//
	//WTable * pSmsTable;
	WSelectionBox * pSmsNumber;
	WLineEdit * pOtherNumber;
	WComboBox * pSmsTemplate;
	WComboBox * pSmsSendMode;
	WText * pSmsNumberLabel;
	WText * pSmsTemplateLabel;

	//
	//WTable * pScriptTable;
	//WLineEdit * pScriptServer;
	WComboBox * pScriptServer;
	WComboBox * pScriptFile;
	WLineEdit * pScriptParam;
	WText * pServerTextLabel;
	WText * pScriptFileLabel;
	WText * pScriptParamLabel;
	string strScriptServerId;
	//
	//WTable * pSoundTable;
	//WComboBox * pSoundFile;
	WLineEdit * pServer;
	WLineEdit * pLoginName;
	WLineEdit * pLoginPwd;
	WText * pServerLabel;
	WText * pLoginNameLabel;
	WText * pLoginPwdLabel;

	//报警条件
	WComboBox * pEventName;
	WRadioButton * pAlwaysCond;
	WRadioButton * pOnlyCond;
	WRadioButton * pSelectCond;
	WRadioButton * pGroupCond;

	WLineEdit * pAlwaysTimes;
	WLineEdit * pOnlyTimes;
	WLineEdit * pSelTimes1;
	WLineEdit * pSelTimes2;

	WTable * pTreeTable;
	WTable * pSubTreeTable;
	WRadioButton *p_SelectEMail;
	WRadioButton *p_SelectSms ;
	WRadioButton *p_SelectScript;
	WRadioButton *p_SelectSound;

private ://wenbo

	WContainerWidget *parent;

	WSTreeAndPanTable *treeTotleTable;
	WSVMainTable * p_MainTable;
	WSVMainTable * p_MainTable1;
	WSVMainTable * p_TreeMainTable;
	WSVFlexTable * p_AlertTable;
	WSVFlexTable * p_HistoryTable;
	WSVFlexTable * p_AlertSelectTable;
	WSVFlexTable * p_AlertConditionTable;
	WSVButton *p_Del;
	WSVButton *p_EnableAlert;
	WSVButton *p_DisableAlert;
	WSVButton *p_Add;
	WSVButton *p_Back;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	WTable *mainTable;
	WTable *mainTable1;
	WTable *mainTable2;
	WLineEdit * p_AlertName;
	WText *p_ShowPage;

	std::string strListHeights;
	std::string strListPans;
	std::string strListTitles;

	WImage *pvDel;
	
	void AddJsParam(const std::string name, const std::string value, WContainerWidget *parent);
	void initMaitTable();
	void initAlertListTable();
	void initHistoryTable();
	void initAlertSelect();
	void ShowHelp();

	std::string szTipSelAll;
	std::string szTipNotSelAll;
	std::string szTipInvSel;
	std::string szTipDel;
	typedef struct _Alert_LIST 
	{
		int nIndex ;            // 索引
		std::string id;
		WCheckBox * pSelect;    // 选择框
		WText * pAlertNameText;          // 报警名称
		WText * pAlertDesText;         // 报警类型
		WText * pAlertCategoryText;      //报警状态
		WText * pAlertTypeText;
		WText * pAlertStateText;
	}Alert_LIST, *LPALTER_LIST;

	// 列表
	std::list<Alert_LIST> m_pListAlert;
	//列表中的表项
	std::list<Alert_LIST>::iterator m_pListItem;

	std::string strSave;
	std::string strCancel;
	std::string strSaveAndAdd;

public:
	void ShowMainTable();
	void initAddAlertTableOld();
	void initAddAlertTable(int nAlertType,int iType = 0);
	void initEditAlertTable(string strIndex);
	void ShowAlertParamOld(int nAlertType);
	void ShowAlertParam(int nAlertType,int iType = 0);
	void AddColum(WTable* pContain);
	void AddHistoryColum(WTable* pContain);
	void AddGroupOperate(WTable * pTable);
	void ClearValue();
	
	~CAlertList(void);
public : //language;
	int iType;
	//报警列表
	std::string strMainTitle; 
	std::string strAlertTitle;
	std::string strAlertNameLabel; 
	std::string strAlertDesLabel;
	std::string strAlertAdd; 
	std::string strAlertDel;
	std::string strIsAlertDel;
	std::string strAlertEditLabel;
	std::string strAlertEnable; 
	std::string strAlertDisable; 
	std::string strAlertHistoryLabel; 	
	std::string strAlertNullList;

	//报警历史报表
	std::string strAlertHistoryTiltle; 
	std::string strReturn;
	std::string strForward;
	std::string strBack;
	std::string strHTimeLabel;
	std::string strHAlertNameLabel;
	std::string strHDeveiceNameLabel;
	std::string strHMonitorNameLabel;
	std::string strHAlertReceiveLabel;
	std::string strHAlertTypeLabel;
	std::string strHAlertStateLabel;
	std::string strHAlertNullList;


	//选择报警类型
	std::string strAlertSelTitle; 		
	std::string strEmail; 	
	std::string strSms;
	std::string strScript; 	
	std::string strSound; 
	std::string strSelfDefine;

	//报警编辑	
	std::string strBaseTitle; 
	
	//基础属性
	std::string strAlertNameTitle; 
	std::string strAlertNameDes; 
	std::string strAlertNameError; 
	
	std::string strAlertTargetTitle; 
	std::string strAlertTargetDes; 
	std::string strAlertTargetError; 

	std::string strAlertUpgradeTitle;
	std::string strAlertUpgradeError;
	std::string strAlertUpgradeDes;
	std::string strAlertUpgradeToTitle;
	std::string strAlertUpgradeToDes;
	std::string strAlertUpgradeToDes1;
	std::string strAlertStopTitle;
	std::string strAlertStopError;
	std::string strAlertStopDes;

	//报警条件
	std::string strCondTitle; 
	
	//事件名称
	std::string strEventNameTitle; 
	std::string strEventNameDes; 

	//条件
	std::string strWhenSetingTitle; 
	std::string strWhenDes; 
	std::string strWhenError; 
	
	std::string strAlwaysCondTitle; 
	std::string strAlwaysCond1; 
	std::string strAlwaysCond2; 
	std::string strOnlyCondTitle; 
	std::string strOnlyCond1;
	std::string strOnlyCond2;
	std::string strSelectCondTitle; 
	std::string strSelectCond1;
	std::string strSelectCond2;
	std::string strSelectCond3;
	std::string strGroupCondTitle; 
	std::string strGroupCond1;

	//e_mail报警参数
	std::string strEmailAlertTitle;
	std::string strEmailAdressTitle; 
	std::string strEmailAdressDes; 
	std::string strEmailAdressError; 
	std::string strEmailAdressSet; 
	std::string strEmailTemplateTitle; 
	std::string strEmailTemplateDes; 
	std::string strEmailTemplateSet;
	//为解决Ticket #112 东方有线ECC邮件报警主题定制问题而增加下面代码。
	//苏合 2007-08-02

	//+++++++++++++++++++++++++++代码增加开始  苏合 2007-08-02+++++++++++++++++++++++++++
	std::string strEmailSubjectTemplate;
	std::string strEmailSubjectTemplateCheck;
	//+++++++++++++++++++++++++++代码增加结束  苏合 2007-08-02+++++++++++++++++++++++++++

	//sms报警参数
	std::string strSmsAlertTitle;
	std::string strPhoneNumberTitle;
	std::string strPhoneNumberDes;
	std::string strPhoneNumberError;
	std::string strSendModeTitle;
	std::string strSendModeWeb;
	std::string strSendModeCom;
	std::string strSendModeDes;
	std::string strSmsTemplateTitle;
	std::string strSmsTemplateDes;
	std::string strSmsTemplateSet;

	std::string strSendModeSelfDefine;

	//声音报警参数
	std::string strSoundAlertTitle;
	std::string strSoundServerTitle;
	std::string strSoundServerDes;
	//std::string strSoundServerError;
	std::string strSoundSeting;
	std::string strSoundSetingDes;
	std::string strLoginNameTitle;
	std::string strLoginNameDes;
	//std::string strLoginNameError;
	std::string strLoginPwdTitle;
	std::string strLoginPwdDes;
	//std::string strLoginPwdError;

	//脚步报警参数
	std::string strScriptAlertTitle;
	std::string strScriptServerTitle;
	std::string strScriptServerDes;
	//std::string strScriptServerError;
	std::string strScriptServerSeting;	
	std::string strScriptTitle;
	std::string strScriptDes;
	//std::string strScriptError;
	std::string strScriptSet;
	std::string strScriptParamTitle;
	std::string strScriptParamDes;
	//std::string strScriptParamError;

	//其他
	std::string strEnable;
	std::string strDisable;
	std::string strNormal;
	std::string strWarning;
	std::string strError;
	std::string strOther;
	std::string strAlertArea;
	std::string strPage;
	std::string strPageCount;
	std::string strRecordCount;
	std::string strAlertRecordIni;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	std::string strAlertAreaNotEmpty;
	std::string strNoAlertItem;
	std::string strNoSortRecord;
	std::string strTypeDelete;
	std::string strDeleteAlert;
	std::string strTypeAdd;
	std::string strEnableAlert;
	std::string strDisableAlert;
	std::string strDisableType;
	std::string strEnableType;

	string szButNum,szButMatch;

	string strDelCon;
	string strSaveAdd;
	string strCancelAdd;
	string strRefresh1;

private slots:
	//MOC: SLOT CAlertList::AddAlert()
    void AddAlert();
    //MOC: SLOT CAlertList::BeforeDelAlert()
    void BeforeDelAlert(); 
    //MOC: SLOT CAlertList::DelAlert()
    void DelAlert(); 
	//MOC: SLOT CAlertList::EnableAlert()
    void EnableAlert();
    //MOC: SLOT CAlertList::DisableAlert()
    void DisableAlert(); 
    //MOC: SLOT CAlertList::SelAll()
    void SelAll();
    //MOC: SLOT CAlertList::EditAlert(const std::string)
    void EditAlert(const std::string strIndex);
	//MOC: SLOT CAlertList::SelNone()
	void SelNone();
	//MOC: SLOT CAlertList::SelInvert()
	void SelInvert();
	//MOC: SLOT CAlertList::SaveAlert()
	bool SaveAlert();
	//MOC: SLOT CAlertList::CancelAlert()
	void CancelAlert();
	//MOC: SLOT CAlertList::EmailBtn()
	void EmailBtn();
	//MOC: SLOT CAlertList::SmsBtn()
	void SmsBtn();
	//MOC: SLOT CAlertList::ScriptBtn()
	void ScriptBtn();
	//MOC: SLOT CAlertList::SoundBtn()
	void SoundBtn();
	//MOC: SLOT CAlertList::SelfDefineBtn()
	void SelfDefineBtn();
    //MOC: SLOT CAlertList::AlertHistory(const std::string)
    void AlertHistory(const std::string strIndex);	
    //MOC: SLOT CAlertList::HistoryBack()
    void HistoryBack();	
    //MOC: SLOT CAlertList::HistoryForward()
    void HistoryForward();
    //MOC: SLOT CAlertList::HistoryReturnBtn()
    void HistoryReturnBtn();
    //MOC: SLOT CAlertList::BackBtn()
    void BackBtn();
	//MOC: SLOT CAlertList::SaveAndAddAlert()
	void SaveAndAddAlert();
	//MOC: SLOT CAlertList::SelSeverChanged()
	void SelSeverChanged();
	//MOC: SLOT CAlertList::Translate()
	void Translate();
	//MOC: SLOT CAlertList::ExChange()
	void ExChange();

	//为解决Ticket #112 东方有线ECC邮件报警主题定制问题而增加下面代码。
	//苏合 2007-08-02

	//+++++++++++++++++++++++++++代码增加开始  苏合 2007-08-02+++++++++++++++++++++++++++
	void ShowEdit();
	//+++++++++++++++++++++++++++代码增加结束  苏合 2007-08-02+++++++++++++++++++++++++++

};