#pragma once

#include "WContainerWidget"
#include <string>
#include <list>
#include <iostream>
#include <SVTable.h>
using namespace std;
#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"
//class CUser;
#include "User.h"

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"

class WTable;
class WText;
class WCheckBox;
class CFlexTable;
class CMainTable;
class WLineEdit;
class WScrollArea;
class CAnswerTable;
class WApplication;
#include "WSignalMapper"

using namespace std;

typedef struct _OneRightmo
{
	std::string  strShowText;
	std::string strRightText;
	WCheckBox *pRightCheckBox;
} OneRight,*POneRight;

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
	CCheckBoxTreeView * pGroupTree;
	
	//此处应该用svtable.......
	WTable * pUserListTable;
	WTable * pAdminUserListTable;
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
	string strGenIndex; //-1 新增 否则 编辑

	std::list<string> pGroupRightList;
	std::list<string> pUnGroupRightList;

	//std::list<ScopeFunc *  > m_pScopeFuncList;

	void GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_,std::list<string >  &pUnGroupRightList_  ,
		ScopeFuncMap & pScopeFuncList,	bool bParentCheck_);
	void setGroupRightCheck(std::string strIndex);
	void SetGroupChecked(WTreeNode*pNode,  std::string  pGroupRightList_,CUser *pUser);
	void MakeTreeNodeFuncRight(WTreeNode *pNode,ScopeFuncMap & pScopeFuncList);
	void SetNodeRightMap(WTreeNode*pNode, CUser *pUser);	
	std::list<string> GetTopFileList(string path);
	bool IsUserExist(string strLoginNameIn, string strUserNameIn);
	virtual void refresh();

	void InitRightTableFromRes(WTable * pRightTable);
public : //add user var
	list <POneRight> m_RightTplList;
	list<POneRight>::iterator m_RightTplListItem;
	bool bShowRight;
	WLineEdit *pEditUserName; 
	WLineEdit *pEditLogin;
	WCheckBox *pCheckDisable;
	int nCurrentUser;
	
	WLineEdit *pEditPwd;
	WLineEdit *pEditConfirmPwd;

	WPushButton * pHideBut;

	WApplication*  appSelf;
	
public:

	void ShowMainTable();
	void initAddUserTable();
	void initEditUserTable(string strIndex,bool bUserType);
	void AddColum( WTable* pContain,bool bUserType );
	void AddGroupOperate(WTable * pTable);
	void ClearValue();
	void GetGroupRightList(CUser* pCurUser );

	void initUserTable();
	void initAdminUserTable();
	WSVMainTable *p_MainTable;
	WSVFlexTable *p_UserTable;
	WSVFlexTable *p_AdminUserTable;
	std::string strListHeights;
	std::string strListPans;
	std::string strListTitles;
	std::string szTipSelAll;
	std::string szTipNotSelAll;
	std::string szTipInvSel;
	std::string szTipDel;
	WSignalMapper m_signalMapper;
	//std::string ;
	typedef struct _USER_LIST 
	{
		int nIndex ;            // 索引
		string id;
		WCheckBox * pSelect;    // 选择框
		WText * pUserName;          // 名称
		WText * pLoginName;         // 状态
		WText * pStatus;      //手机号码

	}USER_LIST, *LPUSER_LIST;
	WTable *p_ContentTabe1;
	// 列表
	std::list<USER_LIST> m_pListUSER;
	//列表中的表项
	std::list<USER_LIST>::iterator m_pListItem;

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
    //MOC: SLOT CUserList::EditAdminUser(const std::string)
    void EditAdminUser(const std::string strIndex);
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

	void ShowHelp();
};