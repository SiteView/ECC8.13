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
#include "WSVFlexTable.h"
#include "WSVMainTable.h"
#include "WSVButton.h"

class WPushButton;
class WCheckBox;
class WLineEdit;
class WComboBox;
class WText;
class WTable;
class WImage;

#include "define.h"


//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

class CSVSmsSet : public WContainerWidget
{
    //MOC: W_OBJECT CSVSmsSet:WContainerWidget
    W_OBJECT;
public:
    CSVSmsSet(WContainerWidget * parent = 0);
    
    void SavePhone(SAVE_PHONE_LIST * phone);
	void AddGroupOperate(WTable * pTable);
	void refresh();
	void UpdatePhoneList();
public:
	WText * m_pHelpUserID;
	WText *pNote;
	WText * m_pHelpNote;
	bool IsShow;
	WText *m_pHelpCOM;
	WText *m_pConnErr;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	WText *m_pHelpSelfDefine1;
	WText *m_pHelpSelfDefine2;
	
public:
	string strListHeights;	
	string strListPans;
	string strListTitles;

public signals:
    //MOC: EVENT SIGNAL CSVSmsSet::ShowWebSend(string, string)
    void ShowWebSend(string szUser, string szPwd);
    //MOC: EVENT SIGNAL CSVSmsSet::ShowComSend(string)
    void ShowComSend(string szSerialPort);
    //MOC: EVENT SIGNAL CSVSmsSet::AddNewPhone()
    void AddNewPhone();
    //MOC: EVENT SIGNAL CSVSmsSet::EditPhone(SAVE_PHONE_LIST)
    void EditPhone(SAVE_PHONE_LIST phone);
    //MOC: EVENT SIGNAL CSVSmsSet::ExChangeEvent()
    void ExChangeEvent();
private slots:
	//MOC: SLOT CSVSmsSet::hideSmsList()
    void hideSmsList();
	//MOC: SLOT CSVSmsSet::showSmsList()
    void showSmsList();
	//MOC: SLOT CSVSmsSet::hideSmsList1()
	void hideSmsList1();
	//MOC: SLOT CSVSmsSet::showSmsList1()
	void showSmsList1();
	//MOC: SLOT CSVSmsSet::hideSmsList2()
	void hideSmsList2();
	//MOC: SLOT CSVSmsSet::showSmsList2()
	void showSmsList2();
    //MOC: SLOT CSVSmsSet::SaveConfig()
    void SaveConfig();
	//MOC: SLOT CSVSmsSet::SaveConfig1()
	void SaveConfig1();
    //MOC: SLOT CSVSmsSet::ShowSendForm()
    void ShowSendForm();
    //MOC: SLOT CSVSmsSet::SelAll()
    void SelAll();
	//MOC: SLOT CSVSmsSet::SelNone()
	void SelNone();
	//MOC: SLOT CSVSmsSet::SelInvert()
	void SelInvert();
    //MOC: SLOT CSVSmsSet::BeforeDelPhone()
    void BeforeDelPhone();
    //MOC: SLOT CSVSmsSet::DelPhone()
    void DelPhone();
    //MOC: SLOT CSVSmsSet::AddPhone()
    void AddPhone();
    //MOC: SLOT CSVSmsSet::EditRow(const std::string)
	void EditRow(const std::string);
	//MOC: SLOT CSVSmsSet::MainHelp()
	void MainHelp();
	//MOC: SLOT CSVSmsSet::Translate()
	void Translate();
	//MOC: SLOT CSVSmsSet::ExChange()
	void ExChange();
	//MOC: SLOT CSVSmsSet::showDllTable()
	void showDllTable();
	//MOC: SLOT CSVSmsSet::hideDllTable()
	void hideDllTable();
	//MOC: SLOT CSVSmsSet::SaveDllConfig()
	void SaveDllConfig();
	//MOC: SLOT CSVSmsSet::UpLoadFile()
	void UpLoadFile();
	//MOC: SLOT CSVSmsSet::SelDllChanged()
	void SelDllChanged();
	//MOC: SLOT CSVSmsSet::TestDll()
	void TestDll();
private:
// functions
    void initForm();
    void showErrMsg(string &strErrMsg);
    void loadString();
    void addWebSms(WTable * table);
    void addComSms(WTable * table);
	void addDllTable(WTable * table);
    void addPhoneList(WTable * table);
    void Edit_Phone(SAVE_PHONE_LIST * phone);
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

	WImage * pShow3;
	WImage * pHide3;
	WTable * table3;
	//new add end

    WLineEdit * m_pUserID;
    WLineEdit * m_pUserPwd;
    WComboBox * m_pSerialPort;

	WLineEdit * m_pDllName;
	WLineEdit * m_pDllFunName;
	WLineEdit * m_pDllFunParam;

	WComboBox * m_pCDllName;

	
    WCheckBox * m_pSelectAll;
    WTable    * m_ptbPhone;
	WTable    * m_nullTable;
    WText     * m_pErrMsg;
	WImage    * m_pHelpImg;
    WSignalMapper m_signalMapper;
	WPushButton * pHideBtn;

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

// 列表
	std::list<SMS_LIST> m_pListSMS;
//列表中的表项
	std::list<SMS_LIST>::iterator m_pListItem;

    typedef struct _FORM_SHOW_TEXT
    {
        string szTitle;        string szUserDes;
		string szUserDes1;
        string szPwdDes;       string szSave;
        string szTest;         string szSerialPortDes;
        string szTBTitle;      string szTableDes;
        string szColSelAll;    string szColName;
        string szColState;     string szColPhone;
        string szColEdit;      string szPortList;
        string szWebSms;       string szNote;
        string szAdd;          string szDel;
        string szDisable;      string szEnable;
        string szTipSelAll;	   string szHelpCOM;	
		string szInputUserLabel;
		string szAddPhoneBut;
		string szConnErr;
		string szTipSelAll1;
		string szTipSelNone;
		string szTipSelInv;
		string szTipAddNew;
		string szTipDel;
		string szSaveSucess;
		string szDescription;
		string strMainTitle;

		string szFuncTitle;
		string szDllName;
		string szDllFunName;
		string szDllFunParam;

		string szUpLoad;
		string szSelfDefine1;
		string szSelfDefine2;
		string szButNum;
		string szButMatch;
		string strNullList;
    public :
		/*
        _FORM_SHOW_TEXT()
        {
			szInputUserLabel = "用户名";
            szTitle = "短信设置";
            szWebSms = "以WEB方式发送短信";
            szUserDes = "用户名";
			szUserDes1 = "此手机号在短信报警中将作为报警发送方发送报警";
            szPwdDes = "密码";
            szSave = "保存";
            szTest = "测试";
            szSerialPortDes = "以串口方式发送短信";
			szPortList = "端口号:";
            szTBTitle = "短信接收手机号设置";
            szTableDes = "短信接收手机号设置允许设置命名的短信接收手机号码，设置的短信" \
                "接收手机号的名称将显示在短信报警的“报警接收手机号”列表中";
            szColSelAll = "状态";
            szColName = "名称";
            szColState = "状态";
            szColPhone = "手机号码";
            szColEdit = "编辑";
            szNote = "注：如果您使用WEB方式发送手机短信：请向游龙科技公司索要用户名、密码" \
				"把用户名和密码输入相应的文本框即可";
            szAdd = "增加短信接收号码";
            szDel = "删除短信接收号码";
            szDisable = "禁止";
            szEnable = "允许";
            szTipSelAll = "全选或者取消全选";
			szAddPhoneBut = "添加短信接收手机号";
			szConnErr = "connect svdb failure!";
			szTipSelAll1 = "全选";
			szTipSelNone = "全不选";
			szTipSelInv = "反选";
			szTipAddNew = "添加";
			szTipDel = "删除";
			szSaveSucess = "保存成功！";
			szDescription = "短信接收手机号设置允许设置命名的短信接收手机号，设置的短信接收" \
				"手机号的名称将显示在短信报警的“报警接收手机号”列表中";
			szHelpCOM = "请选择短信猫所连接的串口";
        }
 */   }FORM_SHOW_TEXT;

		//_FORM_SHOW_TEXT  FORM_SHOW_TEXT;
    FORM_SHOW_TEXT m_formText;
	WTable * m_pGroupOperate;
	string chgstr;

	string strHelp;
	string strEnable;
	string strDisable;
	string strDeleteSMSAffirm;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

	std::string strTypeEdit;

	string strRefresh1;
	string strModifyWeb;
	string strModifyPort;
	string strModifyDLL;
	string strTestDll;
	string strDelCon;
	string strDelConfirm;

	std::string ret;
	WSVFlexTable * m_pWebGeneral;
	WSVFlexTable *m_pGeneral;
	WSVFlexTable *m_pDllTable;
	WSVFlexTable *m_pListGeneral;
};


#endif
//////////////////////////////////////////////////////////////////////////////////
// end file

