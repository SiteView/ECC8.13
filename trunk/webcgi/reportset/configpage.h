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

class CSVReportSet : public WContainerWidget
{
    //MOC: W_OBJECT CSVReportSet:WContainerWidget
    W_OBJECT;
public:
    CSVReportSet(WContainerWidget * parent = 0);
    
    void SavePhone(SAVE_REPORT_LIST * phone);
	void AddGroupOperate(WTable * pTable);
	void refresh();
	void UpdatePhoneList();
	void enabled();
public:
	WText * m_pHelpUserID;
	WText *pNote;
	WText * m_pHelpNote;
	bool IsShow;
	WPushButton * pHideBut;
	WImage * pDel;
	WText *m_pConnErr;
	string chgstr;
	string szListEmpty;

	WSVButton *m_pDel;
	WSVButton *m_pAdd;
	
public signals:
    //MOC: EVENT SIGNAL CSVReportSet::ShowWebSend(string, string)
    void ShowWebSend(string szUser, string szPwd);
    //MOC: EVENT SIGNAL CSVReportSet::ShowComSend(string)
    void ShowComSend(string szSerialPort);
    //MOC: EVENT SIGNAL CSVReportSet::AddNewPhone()
    void AddNewPhone();
    //MOC: EVENT SIGNAL CSVReportSet::EditPhone(SAVE_REPORT_LIST)
    void EditPhone(SAVE_REPORT_LIST phone);
    //MOC: EVENT SIGNAL CSVReportSet::ExChangeEvent()
    void ExChangeEvent();
private slots:
	//MOC: SLOT CSVReportSet::hideSmsList()
    void hideSmsList();
	//MOC: SLOT CSVReportSet::showSmsList()
    void showSmsList();
	//MOC: SLOT CSVReportSet::hideSmsList1()
	void hideSmsList1();
	//MOC: SLOT CSVReportSet::showSmsList1()
	void showSmsList1();
	//MOC: SLOT CSVReportSet::hideSmsList2()
	void hideSmsList2();
	//MOC: SLOT CSVReportSet::showSmsList2()
	void showSmsList2();
    //MOC: SLOT CSVReportSet::SaveConfig()
    void SaveConfig();
	//MOC: SLOT CSVReportSet::SaveConfig1()
	void SaveConfig1();
    //MOC: SLOT CSVReportSet::ShowSendForm()
    void ShowSendForm();
    //MOC: SLOT CSVReportSet::SelAll()
    void SelAll();
	//MOC: SLOT CSVReportSet::SelNone()
	void SelNone();
	//MOC: SLOT CSVReportSet::SelInvert()
	void SelInvert();
    //MOC: SLOT CSVReportSet::BeforeDelPhone()
    void BeforeDelPhone();
	//MOC: SLOT CSVReportSet::DelPhone()
    void DelPhone(); 
    //MOC: SLOT CSVReportSet::AddPhone()
    void AddPhone();
    //MOC: SLOT CSVReportSet::EditRow(const std::string)
	void EditRow(const std::string);
	//MOC: SLOT CSVReportSet::MainHelp()
	void MainHelp();
	//MOC: SLOT CSVReportSet::Translate()
	void Translate();
	//MOC: SLOT CSVReportSet::ExChange()
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
	WPushButton *pAdd ;//添加新报告按钮

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
		string szMainTitle;
        string szTitle;        string szSave;     
        string szTBTitle;      string szTableDes;
        string szColSelAll;    string szColName;
        string szColState;   string szTest; 
        string szColEdit;    string szColPeriod;  
        
        string szAdd;          string szDel;
        string szDisable;      string szEnable;
        string szTipSelAll;
		string szInputUserLabel;
		string szAddPhoneBut;
		string szConnErr;
		string szTipSelAll1;
		string szTipSelNone;
		string szTipSelInv;
		string szTipAddNew;
		string szTipDel;
		string szSameSection;
		string szDeleteSMSAffirm;
		string szButNum,szButMatch;
    public : /*
        _FORM_SHOW_TEXT()
        {
			szMainTitle="统计报告";

            szTitle = "报告设置";
            szSave = "保存";
            szTBTitle = "报告列表";
            szColSelAll = "状态";
            szColName = "标题";
            szColState = "状态";
			szColEdit = "编辑";
			szColPeriod = "时间周期";
 
            szDisable = "禁止";
            szEnable = "允许";
            szTipSelAll = "全选或者取消全选";
			szAddPhoneBut = "添加报告";
			szConnErr = "连接SVDB失败";
			szTipSelAll1 = "全选";
			szTipSelNone = "全不选";
			szTipSelInv = "反选";
			szTipAddNew = "添加";
			szTipDel = "删除";

			szSameSection = "有相同的TOPN报告";
        } */
    }FORM_SHOW_TEXT;

    FORM_SHOW_TEXT m_formText;
	WTable * m_pGroupOperate;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pReportListTable;

	void AddJsParam(const std::string name, const std::string value);

};


#endif
//////////////////////////////////////////////////////////////////////////////////
// end file

