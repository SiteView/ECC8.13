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
    WLineEdit * pServerIp;          // ����������
    WLineEdit * pMailFrom;          // �ʼ���Դ
    WLineEdit * pUser;              // �û�
    WLineEdit * pPwd;               // ����
    WLineEdit * pBackupServer;      // ���ݷ���������

	WPushButton * pHideBut;

    //WCheckBox * m_pSelectAll;       // ȫѡ

    //WText * m_pErrMsg;              // ������Ϣ

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

// �ʼ���ַ�����
typedef struct _MAIL_LIST 
{
    int nIndex ;            // ����
    WCheckBox * pSelect;    // ѡ���
    WText * pName;          // ����
    WText * pValue;         // mail��ַ
    WText * pState;         // ״̬
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

// �ʼ���ַ�б�
    list<MAIL_LIST> m_pListMail;
// �ʼ���ַ�б��еı���
    list<MAIL_LIST>::iterator m_pListItem;
private:
    // У���ʼ���ַ
    bool checkEmail();
    // �޸���
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

