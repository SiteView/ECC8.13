//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_SMS_SET_CONFIG_H_
#define _SV_SMS_SET_CONFIG_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WContainerWidget"
#include "../../opens/libwt/WSignalMapper"
#include <list>

class WPushButton;
class WCheckBox;
class WLineEdit;
class WComboBox;
class WText;
class WTable;
class WImage;
class WSVMainTable;
class WSVFlexTable;
class WSVButton;

#include "define.h"


//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

class CSVTopnReportSet : public WContainerWidget
{
    //MOC: W_OBJECT CSVTopnReportSet:WContainerWidget
    W_OBJECT;
public:
    CSVTopnReportSet(WContainerWidget * parent = 0);
    
    void SaveTopnReport(SAVE_REPORT_LIST * phone);
	void AddGroupOperate(WTable * pTable);
	void refresh();
	void UpdatePhoneList();
public:
	WText * m_pHelpUserID;
	WText *pNote;
	WText * m_pHelpNote;
	bool IsShow;

	WText *m_pConnErr;
	string chgstr;

	WPushButton * pHideBut;
	
	WSVButton *m_pDel;
	WSVButton *m_pAdd;
	
public signals:
    //MOC: EVENT SIGNAL CSVTopnReportSet::ShowWebSend(string, string)
    void ShowWebSend(string szUser, string szPwd);
    //MOC: EVENT SIGNAL CSVTopnReportSet::ShowComSend(string)
    void ShowComSend(string szSerialPort);
    //MOC: EVENT SIGNAL CSVTopnReportSet::AddNewPhone()
    void AddNewPhone();
    //MOC: EVENT SIGNAL CSVTopnReportSet::EditPhone(SAVE_REPORT_LIST)
    void EditPhone(SAVE_REPORT_LIST phone);
    //MOC: EVENT SIGNAL CSVTopnReportSet::ExChangeEvent()
    void ExChangeEvent();
private slots:
	//MOC: SLOT CSVTopnReportSet::hideSmsList()
    void hideSmsList();
	//MOC: SLOT CSVTopnReportSet::showSmsList()
    void showSmsList();
	//MOC: SLOT CSVTopnReportSet::hideSmsList1()
	void hideSmsList1();
	//MOC: SLOT CSVTopnReportSet::showSmsList1()
	void showSmsList1();
	//MOC: SLOT CSVTopnReportSet::hideSmsList2()
	void hideSmsList2();
	//MOC: SLOT CSVTopnReportSet::showSmsList2()
	void showSmsList2();
    //MOC: SLOT CSVTopnReportSet::ShowSendForm()
    void ShowSendForm();
    //MOC: SLOT CSVTopnReportSet::SelAll()
    void SelAll();
	//MOC: SLOT CSVTopnReportSet::SelNone()
	void SelNone();
	//MOC: SLOT CSVTopnReportSet::SelInvert()
	void SelInvert();
    //MOC: SLOT CSVTopnReportSet::BeforeDelPhone()
    void BeforeDelPhone();
    //MOC: SLOT CSVTopnReportSet::DelPhone()
    void DelPhone();
    //MOC: SLOT CSVTopnReportSet::AddPhone()
    void AddPhone();
    //MOC: SLOT CSVTopnReportSet::EditRow(const std::string)
	void EditRow(const std::string);
	//MOC: SLOT CSVTopnReportSet::MainHelp()
	void MainHelp();
	//MOC: SLOT CSVTopnReportSet::Translate()
	void Translate();
	//MOC: SLOT CSVTopnReportSet::ExChange()
	void ExChange();
private:
// functions
    void initForm();
    void showErrMsg(string &strErrMsg);
    void loadString();
    void addPhoneList(WTable * table);
    void Edit_Phone(SAVE_REPORT_LIST * phone);

	void addPhoneListNew();
// members
	//new add by jiang xian
	WImage * pShow;
	WImage * pHide;
	WTable * table;

	WImage * pShow1;
	WImage * pHide1;
	WTable * table1;

	WImage * pShow2;
	WImage * pHide2;
	WTable * table2;
	//new add end

    WLineEdit * m_pUserID;
    WLineEdit * m_pUserPwd;
    WComboBox * m_pSerialPort;

	
    WCheckBox * m_pSelectAll;
    WTable    * m_ptbPhone;
    WText     * m_pErrMsg;
	WImage    * m_pHelpImg;
    WSignalMapper m_signalMapper;

	WTable    * nullTable;

	typedef struct _SMS_LIST 
	{
	  int nIndex ;            // 索引
	  string id;
	  WCheckBox * pSelect;    // 选择框
	  WText * pName;          // 名称
	  WText * pStatus;         // 状态
	  WText * pPhoneNum;      //手机号码
	  WText * pModify;        //
	}SMS_LIST, *LPSMS_LIST;

	typedef struct _REPORT_LIST
	{
		WCheckBox * pSelect;
		WText * pName;
		WText * pPeriod;
		WImage * pEdit;
	}REPORT_LIST, *LPREPORT_LIST;

// 列表
	std::list<REPORT_LIST> m_pListReport;
	std::list<SMS_LIST> m_pListSMS;
//列表中的表项
	std::list<REPORT_LIST>::iterator m_pListItem;

    typedef struct _FORM_SHOW_TEXT
    {
        string szTitle;        string szSave;     
        string szTBTitle;      string szTableDes;
        string szColSelAll;    string szColName;
        string szColState;   string szTest; 
        string szColEdit;    string szColPeriod;  
        
        string szAdd;          string szDel;
        string szDisable;      string szEnable;
        string szTipSelAll;	   string szDelTopNAffirm;	
		string szInputUserLabel;
		string szAddPhoneBut;
		string szConnErr;
		string szTipSelAll1;
		string szTipSelNone;
		string szTipSelInv;
		string szTipAddNew;
		string szTipDel;
		string szSameSection;
		string szButNum,szButMatch;
		string szHelp;
		string szListEmpty;
    public :
        _FORM_SHOW_TEXT()
        {
/*
            szTitle = "TopN报告";
            szSave = "保存";
            szTBTitle = "TopN报告列表";
            szColSelAll = "状态";
            szColName = "标题";
            szColState = "状态";
			szColEdit = "编辑";
			szColPeriod = "时间周期";
 
            szDisable = "禁止";
            szEnable = "允许";
            szTipSelAll = "全选或者取消全选";
			szAddPhoneBut = "添加TopN报告";
			szConnErr = "connect svdb failure!";
			szTipSelAll1 = "select all";
			szTipSelNone = "select none";
			szTipSelInv = "select invert";
			szTipAddNew = "new add";
			szTipDel = "del";

			szSameSection = "have same section in ini file!";  */
        }
    }FORM_SHOW_TEXT;

    FORM_SHOW_TEXT m_formText;
	WTable * m_pGroupOperate;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

	//WPushButton * pTranslateBtn;
	//WPushButton * pExChangeBtn;

	WSVMainTable * m_pMainTable;
	WSVFlexTable * m_pReportListTable;

	void AddJsParam(const std::string name, const std::string value);

};


#endif
//////////////////////////////////////////////////////////////////////////////////
// end file

