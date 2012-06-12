/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_DISABLE_FORM_H_
#define _SV_DISABLE_FORM_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WButtonGroup"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WRadioButton"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WApplication"

#include "../svtable/WSPopTable.h"
#include "../svtable/WSPopButton.h"
#include "../svtable/WSVMainTable.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <map>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "Time.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SVDisableForm : public WTable
{   
    enum sv_disable_type
    {
        sv_group,
        sv_device,
        sv_monitor
    };
    //MOC: W_OBJECT SVDisableForm:WTable
    W_OBJECT;
public:
    SVDisableForm(WContainerWidget* parent = NULL,int nType =sv_group, const char *szQueryString = NULL);
    virtual void refresh();

    void setApp(WApplication *app) {appl = app;};
public signals:
private slots:
    //MOC: SLOT SVDisableForm::ShowHelp()
    void ShowHelp();                    // show/hide disable
    //MOC: SLOT SVDisableForm::Disable()
    void Disable();    
    //MOC: SLOT SVDisableForm::ShowHideTemporary()
    void ShowHideTemporary();
    //MOC: SLOT SVDisableForm::cancel()
    void cancel();
    //MOC: SLOT SVDisableForm::eventConfirm()
    void eventConfirm();
	//MOC: SLOT SVDisableForm::Translate()
	void Translate();
	//MOC: SLOT SVDisableForm::ExChange()
	void ExChange();
	//MOC: SLOT SVDisableForm::ViewLog()
	void ViewLog();
	
private: // member list
    // form show text
    string      m_szTitle;              // title
    string      m_szEnableTitle;
    string      m_szGroupEnableMsg;
    string      m_szDeviceEnableMsg;
    string      m_szGroupDisableMsg;
    string      m_szDeviceDisableMsg;
    string      m_szEnableMsg;
    string      m_szForeverDis;          // Forver disable
    string      m_szTemporaryDis;       // Temporary Disable
    string      m_szDisableDesc;        // disable discription
    string      m_szDisableDescHelp;    // disable discription help
    string      m_szErrTip;
    string      m_szHelpTip;
    string      m_szStartTime;
    string      m_szEndTime;

    string      m_szConfirm;

    string      m_szStart;              // start
    string      m_szStartTimeHelp;
    string      m_szStartTimeTip;

    string      m_szEnd;                // end
    string      m_szEndTimeHelp;
    string      m_szEndTimeTip;

    string      m_szEndTimeError;

    string      m_szDisable;            // disable
    string      m_szEnable;
    string      m_szCancel;             // cancel
    string      m_szClose;
    string      m_szConfirmTitle;       // 事件确认
    string      m_szConfirmDesc;

    string      m_szDisableSucc;
    string      m_szConfirmSucc;

    string      m_szReturn;
    string      m_szQueueName ;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

	string m_szQueryLog;
	string strCancel;
	string strAffirm;

	std::string strParam;
    // show/hide help information
    bool   m_bShowHelp;
    int               m_nOperate;
    bool              m_bParentDisable;
    list<string>      m_lsIndex;

    int    m_nDisableType;
    string m_szQueryString;

    TTime  m_tStart;
    TTime  m_tEnd;
    // WT ActiveX list;
    WLineEdit       * m_pStartTime;  // start time
    WLineEdit       * m_pStartDay;   // start day
    WLineEdit       * m_pEndTime;    // end   time
    WLineEdit       * m_pEndDay;     // end   day
    WLineEdit       * m_pDisable;
    WLineEdit       * m_pConfirm;
    WTable          * m_pDisTable;
    WTable          * m_pTemporary;
    WTable          * m_pConfirmTable;
	WTable          * m_pConfirmTable1;
    WButtonGroup    * m_btnGroup;    // radio button group

	WText           * m_pSelectType;
	WRadioButton    * m_pForever;
    WRadioButton    * m_pTemporaryDis;

    WText           * m_pErrTip;
    WText           * m_pDisableHelp;
    WText           * m_pEndTimeHelp;
    WText           * m_pStartTimeHelp;
    WText           * m_pTitle;
    WText           * m_pEnableMsg;
    WImage          * m_pHelp;
    WText           * m_pPostion;

    //WPushButton     * m_pbtnDisable ;
	//WPushButton     * m_pbtnClose ;
	WSPopButton    * m_pbtnDisable;
	WSPopButton    * m_pbtnEnable;
	WSPopButton    * m_pbtnClose;

    WPushButton     * m_pbtnCloseWnd;
    WApplication    * appl;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

private: // function list
    void loadString();
    void initForm();

    void createOperate();
    void createTitle();
    void createButtonGroup();
    void createHelp();
    void createTemporary();

    void createConfirm();

    void createEnableMsg();
    void createTipMsg();
    //void 

    void saveAttribByNode(MAPNODE &node);

    bool checkStartTime();
    bool checkEndTime();
    bool checkTime(string &szTime, string &szDay);
    //bool endLessstart();

    void DisableGroup(string &szGroupID);
    void DisableDevice(string &szDeviceID);
    void DisableMonitor(string &szMonitorID);
    void EnableGroup(string &szGroupID);
    void EnableDevice(string &szDeviceID);
    void EnableMonitor(string &szMonitorID);

    int isDisable(string szIndex);
    int isParentDisable(string &szIndex);
    int isEntityDisable(string &szIndex);
    bool isSVSE(string &szIndex);

    void ParserQueryString(string &szQuery);

    bool showConfirmTable();

    list<string>    m_lsMonitors;

    string          m_szIDCUser;
    string          m_szIDCPwd;

	//写操作日志用
	string m_szTypeEnable;
	string m_szTypeDisable;
	string m_szOType;
	string m_szOName;
	string m_szOGroup;
	string m_szODevice;
	string m_szOMonitor;
	string m_szONameTemp;
	string m_szDeviceName;
public://WT
	WApplication *  appSelf;

public://2007-01-06
	WSVMainTable *MainTable; 
	WSPopTable *PopTable;
private:
	void AddJsParam(const std::string name, const std::string value, WContainerWidget * parent);

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
