#pragma once

#include "WContainerWidget"
#include <string>
#include <list>
#include <iostream>
#include <SVTable.h>
using namespace std;
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"
#include "WButtonGroup"

class WText;
class WTable;
class WCheckBox;
class WLineEdit;
class CFlexTable;
class CMainTable;
class WScrollArea;
class WPushButton;
class CAnswerTable;
class WApplication;
class WRadioButton;
#include "WSignalMapper"

using namespace std;

class CUserList  :WContainerWidget
{
    //MOC: W_OBJECT CUserList:WContainerWidget
    W_OBJECT;
public:
    CUserList(WContainerWidget *parent = 0);

public:
	
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	CFlexTable *pUserTable;
	CFlexTable *pAdminUserTable;
	CAnswerTable * pUserAddTable;
	//CCheckBoxTreeView * pGroupTree;
	
	//�˴�Ӧ����svtable.......
	WTable * pUserListTable;
	//WTable * pAdminUserListTable;
	WTable * pRightTable;
	WTable * pFrameTable;
	WTable * pSubTreeTable;
    SVTable m_svGenUserList;
    //SVTable m_svAddUserList;
	string GetOnlyIndex(int nList);
	void AddGenUser(string strIndex, string strUserName, string strLoginName, string strPwd, string strIsUse);
	void AddAdminUser(string strIndex, string strUserName, string strLoginName, string strPwd, string strIsUse);	
	void EditGenUser(string strIndex, string strUserName, string strLoginName, string strPwd, string strIsUse);
	
	WSignalMapper m_genMapper;   // 
	WSignalMapper m_adMapper;   // 
	string strGenIndex; //-1 ���� ���� �༭

	bool IsUserExist(string strLoginNameIn, string strUserNameIn);
	virtual void refresh();

public : //add user var
	WLineEdit *pEditUserName; 
	WLineEdit *pEditLogin;
	WCheckBox *pCheckDisable;
	int nCurrentUser;
	
	WLineEdit *pEditPwd;
	WLineEdit *pEditConfirmPwd;

	WPushButton * pHideBtn;
	WApplication*  appSelf;

	//IDC�û�����
	WRadioButton * p_SelIDC;
	WRadioButton * p_SelWeiHu;
	WRadioButton * p_SelSysWeihu;
	WRadioButton * p_SelYeWu;
	WRadioButton * p_SelXiaoShou;
	WRadioButton * p_SelChangShang;
	WRadioButton * p_SelGuanMo;
	
	WSVFlexTable* p_FlexSelBag;
	WSVFlexTable* p_FlexSelUser;

	WLineEdit * pBaseBagNumber;
	WLineEdit * pServerBagNumber;
	WLineEdit * pAppBagNumber;
	WLineEdit * pSimulationBagNumber;
	WLineEdit * pCustomBagNumber;

	void ReadUserInfoToMyIni(string strIniName);
	void WriteUserInfoToMyIni(string strIniName, string strUserType, string strIdcUserId, string strStatu);

	void InitSelBagTableFromId(string strUserId, WContainerWidget * pParent);
	void InitSelUserTableFromId(string strUserId, WContainerWidget * pParent);

public:

	void ShowMainTable();
	void initAddUserTable();
	void initEditUserTable(string strIndex,bool bUserType);
	void AddColum( WTable* pContain,bool bUserType );
	void AddGroupOperate(WTable * pTable);
	void ClearValue();

	void initUserTable();

	WSVMainTable *p_MainTable;
	WSVFlexTable *p_UserTable;

	WTable *p_ContentTabe1;

	std::string strListHeights;
	std::string strListPans;
	std::string strListTitles;
	std::string szTipSelAll;
	std::string szTipNotSelAll;
	std::string szTipInvSel;
	std::string szTipDel;
	WSignalMapper m_signalMapper;

	typedef struct _USER_LIST 
	{
		int nIndex ;            // ����
		string id;
		WCheckBox * pSelect;    // ѡ���
		WText * pUserName;          // ����
		//WText * pLoginName;         // ��¼����
		WText * pStatus;      //״̬
	}USER_LIST, *LPUSER_LIST;	
	
	// �б�
	std::list<USER_LIST> m_pListUSER;
	//�б��еı���
	std::list<USER_LIST>::iterator m_pListItem;

	//IDC���������۴���ѡ�����û��ã�
	typedef struct _IDCUSER_LIST
	{
		string strId;
		WCheckBox * pSelect;    // ѡ���
	}IDCUSER_LIST, *LPIDCUSER_LIST;	
	
	// �б�
	std::list<IDCUSER_LIST> m_pSelUserList;
	//�б��еı���
	std::list<IDCUSER_LIST>::iterator m_pSelUserListItem;

	WSVFlexTable * p_AddGene;

	void ErrorTest(const string &errorMsg);

	~CUserList(void);
public : //language;
	std::string strMainTitle; 
	std::string strTitle ;

	std::string strNameLabel;
	std::string strNameDes;
	std::string strNameError;
	std::string strLoginLabel;
	std::string strLoginDes;
	std::string strLoginError;
	std::string strState;
	std::string strNameUse;
	std::string strNameEdit;
	std::string strAdminTitle;
	std::string strDel;
	std::string strAdd;
	std::string strEdit;
	bool bAddEdit;
	
	std::string strGeneral;

	std::string strPwdLabel;
	std::string strPwdDes;
	std::string strConfirmPwdLabel;
	std::string strConfirmPwdDes;
	std::string strConfirmPwdError;
	std::string strEnable;

	std::string strDeleteUserAffirm;
	std::string strEntity;
	std::string strTuopRight;

	std::string szNoGenUserItem;

	std::string strTypeDelete;
	std::string strDelName;
	std::string strTypeAdd;
	string szButNum,szButMatch;

	std::string strNullList;
	
	string strEditAdvUser;
	string strEditUser;
	string strDelUser;
	string strCancelAdd;
	string strSaveAdd;
	string strRefresh;
	string strDelCon;
	
private slots:

	//MOC: SLOT CUserList::AddUser()
    void AddUser();
    //MOC: SLOT CUserList::BeforeDelUser()
    void BeforeDelUser(); 
    //MOC: SLOT CUserList::DelUser()
    void DelUser(); 
    //MOC: SLOT CUserList::SelAll()
    void SelAll();
    //MOC: SLOT CUserList::EditUser(const std::string)
    void EditUser(const std::string strIndex);
	//MOC: SLOT CUserList::SelNone()
	void SelNone();
	//MOC: SLOT CUserList::SelInvert()
	void SelInvert();
	//MOC: SLOT CUserList::SaveUser()
	void SaveUser();
	//MOC: SLOT CUserList::CancelUser()
	void CancelUser();
	//MOC: SLOT CUserList::Translate()
	void Translate();
	//MOC: SLOT CUserList::ExChange()
	void ExChange();
	//MOC: SLOT CUserList::SelIDCBtn()
	void SelIDCBtn();
	//MOC: SLOT CUserList::SelWeiHuBtn()
	void SelWeiHuBtn();
	//MOC: SLOT CUserList::SelSysWeihuBtn()
	void SelSysWeihuBtn();
	//MOC: SLOT CUserList::SelYeWuBtn()
	void SelYeWuBtn();
	//MOC: SLOT CUserList::SelXiaoShouBtn()
	void SelXiaoShouBtn();
	//MOC: SLOT CUserList::SelChangShangBtn()
	void SelChangShangBtn();
	//MOC: SLOT CUserList::SelGuanMoBtn()
	void SelGuanMoBtn();

	void ShowHelp();
};