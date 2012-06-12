//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_EMAIL_SET_H_
#define _SV_EMAIL_SET_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib

#include <WContainerWidget>
#include <WPushButton>
#include <WLineEdit>
#include <WCheckBox>
#include <WText>
#include <WImage>
#include <WTable>
#include <WTableCell>
#include <WSignalMapper>
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>
#include <list>

using namespace std;

#include "defines.h"

class CFlexTable;
class CMainTable;

class WSVMainTable;
class WSVFlexTable;
class WSVButton;

extern void PrintDebugString(const char *szErrmsg);
extern unsigned int RandIndex();
extern void RandID(string &strID);

//////////////////////////////////////////////////////////////////////////////////
// class CSVEmailSet
class CSVEmailSet : public WContainerWidget
{
    //MOC: W_OBJECT CSVEmailSet:WContainerWidget
    W_OBJECT;
public:
    CSVEmailSet(WContainerWidget *parent = 0);
    void EmailSetForm();
    void AddMailList(ADD_MAIL_OK mail);
    virtual void refresh();
	void WriteMailList(ADD_MAIL_OK mail);
	ADD_MAIL_OK ReadMailList(string strSectionItem);

	//cxy add 
	int GetOnlyIndex();
	void InitMailList(ADD_MAIL_OK mail,int iRow);
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	std::string strAllSel;
	std::string strAllNotSel;
	std::string strFanSel;
	std::string strDelete;
	std::string strAddNew;

	string strListHeights,strListTitles, strListPans;
public signals:
    //MOC: EVENT SIGNAL CSVEmailSet::SaveSuccessful(SEND_MAIL_PARAM)
    void SaveSuccessful(SEND_MAIL_PARAM sendParam);
    //MOC: EVENT SIGNAL CSVEmailSet::AddNewMail()
    void AddNewMail();
    //MOC: EVENT SIGNAL CSVEmailSet::EditMailList(ADD_MAIL_OK)
    void EditMailList(ADD_MAIL_OK addMail);
    //MOC: EVENT SIGNAL CSVEmailSet::ExChangeEvent()
    void ExChangeEvent();
private slots:
    //MOC: SLOT CSVEmailSet::Save()
    void Save();
    //MOC: SLOT CSVEmailSet::AddEmail()
    void AddEmail();
	
    //MOC: SLOT CSVEmailSet::BeforeDelEmail()
    void BeforeDelEmail(); 
    //MOC: SLOT CSVEmailSet::DelEmail()
    void DelEmail(); 

    //MOC: SLOT CSVEmailSet::EditMail(int)
    void EditMail(int nIndex);
	//MOC: SLOT CSVEmailSet::SelInvert()
	void SelInvert();
    //MOC: SLOT CSVEmailSet::SelAll()
    void SelAll();
	//MOC: SLOT CSVEmailSet::SelNone()
	void SelNone();
	//MOC: SLOT CSVEmailSet::Translate()
	void Translate();
	//MOC: SLOT CSVEmailSet::ExChange()
	void ExChange();

	void ShowHelp();
private:
    WLineEdit * pServerIp;          // 发件服务器
    WLineEdit * pMailFrom;          // 邮件来源
    WLineEdit * pUser;              // 用户
    WLineEdit * pPwd;               // 密码
    WLineEdit * pBackupServer;      // 备份发件服务器

	WPushButton * pHideBut;

    //WCheckBox * m_pSelectAll;       // 全选

    //WText * m_pErrMsg;              // 错误消息

    WSignalMapper m_signalMapper;   // 

	//WSingalMapper m_editSignalMap;
    //SVTable m_AdressList;

	//cxy change 5 30
	std::vector<WText *> m_pListHelpText ;

//	CFlexTable * m_pSetTable;
//	CFlexTable * m_pAddressTable;
	WTable * m_pAddressListTable;
//	CMainTable *pMainTable;

	WSVMainTable *pMainTable;
	WSVFlexTable *m_pSetTable;
	WSVFlexTable *m_pAddressTable;

	std::string szEmailNull;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	void InitSetTable();
	void InitAddressTable();
	void AddAddressOperate(WTable * pTable);	
	void AddGeneralOperate(WTable * pTable);

	string szAddEmailBut;

	void AddJsParam(const std::string name, const std::string value);

	//list<ADD_MAIL_OK> m_pListMail;
	//list<ADD_MAIL_OK>::iterator m_pListItem;

// 邮件地址表格行
typedef struct _MAIL_LIST 
{
    int nIndex ;            // 索引
    WCheckBox * pSelect;    // 选择框
    WText * pName;          // 名称
    WText * pValue;         // mail地址
    WText * pState;         // 状态
    bool  bDisable;
	
	string szTemplate;
	string szSchedule;
	string szDes;
}MAIL_LIST, *LPMAIL_LIST;

typedef struct _FORM_SHOW_TEXT
{
    string szSMTP;
	string szBackServer;
    string szUser; 
	string szPwd;
    string szFrom; 
	string szTest;
    
	string szSMTPDes;
	string szBackServerDes;
    string szUserDes; 
	string szPwdDes;
    string szFromDes; 

	string szDisable;
    string szEnable;
    
	string szErrMail;
	string szErrSmtp;
    string szErrUser;


	string szTBTitle;
    string szTBDiscri;
	string szSave;
    string szAdd;     
	string szDel;
    string szTitle;
	string szAdvTitle;
	string szGenTitle;
	string szSaveSucess;
	string szNoEmailSetItem;
	string szButNum;
	string szButMatch;
	string szDelAffirmInfo;

    typedef struct TABLE_COL_TITLE
    {
        string szSelAll; string szName; string szState;
        string szEdit; string szMail;
    }TableColTitle;
    TableColTitle tbColtitle;
}showtext;
    showtext m_formText;

// 邮件地址列表
    list<MAIL_LIST> m_pListMail;
// 邮件地址列表中的表项
    list<MAIL_LIST>::iterator m_pListItem;
private:
    // 校验邮件地址
    bool checkEmail();
    // 修改行
    void EditRow(ADD_MAIL_OK &maillist);

private:
	string strRefresh1;
	string strDelCon;
};
// end class
//////////////////////////////////////////////////////////////////////////////////
#endif
//////////////////////////////////////////////////////////////////////////////////
// end file

