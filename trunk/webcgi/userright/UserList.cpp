#include <time.h>
#include ".\userlist.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "AnswerTable.h"
#include "../../base/des.h"
#include "FlexTable.h"
//#include "../../base/GetInstallPath.h"
#include "../base/OperateLog.h"

#include "User.h"
#include "websession.h"
#include "WApplication"
#include "WCheckBox"
#include "WLineEdit"
#include "WSignalMapper"
#include <WScrollArea>

#define ShanTou

#ifdef ShanTou
#include "../login/MD5.h"	

string myMd5(string strTmpPwd)
{
	int ilen = strTmpPwd.length();
	unsigned char output[16];
	MD5(output, (const unsigned char *)strTmpPwd.c_str(), ilen);
	
	string strUserPwd = "";
	
	//strPwd = output;			
	//strUserPwd.append((char*)output);
	//OutputDebugString((char*)output);

	char tmpbuf[2];
	for(int i =0; i< 16;i++)
	{
		sprintf(tmpbuf, "%02x", output[i]);	
		strUserPwd.append((char*)tmpbuf);
	}			
	
	for(int i=0;i<strUserPwd.length();i++)
	{
		strUserPwd[i]=toupper(strUserPwd[i]);
	}

	return strUserPwd;
}

#endif

string TrimStdString(string strIn)
{	
	if(!strIn.empty())
	{		
		strIn.erase(strIn.begin(),strIn.begin() + strIn.find_first_not_of(' '));
		strIn.erase(strIn.begin() + strIn.find_last_not_of(' ') + 1,strIn.end());
		return strIn;
	}
	else
		return "";
}

CUserList::CUserList(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_User_Manage",strMainTitle);
			FindNodeValue(ResNode,"IDS_General_User_List",strTitle);
			FindNodeValue(ResNode,"IDS_User_Name",strNameLabel);
			FindNodeValue(ResNode,"IDS_User_Name_Help",strNameDes);
			FindNodeValue(ResNode,"IDS_User_Name_Error",strNameError);
			FindNodeValue(ResNode,"IDS_Login_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Login_Name_Help",strLoginDes);
			FindNodeValue(ResNode,"IDS_Login_Name_Error",strLoginError);
			FindNodeValue(ResNode,"IDS_State",strState);
			FindNodeValue(ResNode,"IDS_Disable",strNameUse);
			FindNodeValue(ResNode,"IDS_Edit",strNameEdit);
			FindNodeValue(ResNode,"IDS_Manager_List",strAdminTitle);
			FindNodeValue(ResNode,"IDS_Delete_User_Affirm",strDel);
			FindNodeValue(ResNode,"IDS_Add_User",strAdd);
			FindNodeValue(ResNode,"IDS_Edit_User",strEdit);
			FindNodeValue(ResNode,"IDS_General_Set",strGeneral);
			FindNodeValue(ResNode,"IDS_Password",strPwdLabel);
			FindNodeValue(ResNode,"IDS_Password_Help",strPwdDes);
			FindNodeValue(ResNode,"IDS_Password_Affirm",strConfirmPwdLabel);
			FindNodeValue(ResNode,"IDS_Password_Repeat",strConfirmPwdDes);
			FindNodeValue(ResNode,"IDS_Password_Error",strConfirmPwdError);
			FindNodeValue(ResNode,"IDS_Enable",strEnable);
			FindNodeValue(ResNode,"IDS_Delete_User_Affirm",strDeleteUserAffirm);
			FindNodeValue(ResNode,"IDS_Device",strEntity);
			FindNodeValue(ResNode,"IDS_Tuop_Right",strTuopRight);
			FindNodeValue(ResNode,"IDS_None_General_User",szNoGenUserItem);
			FindNodeValue(ResNode,"IDS_Delete",strTypeDelete);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",szButMatch);
			FindNodeValue(ResNode,"IDS_All_Select",szTipSelAll);
			FindNodeValue(ResNode,"IDS_None_Select",szTipNotSelAll);
			FindNodeValue(ResNode,"IDS_Invert_Select",szTipInvSel);
			FindNodeValue(ResNode,"IDS_Delete",szTipDel);
			FindNodeValue(ResNode,"IDS_General_User_List_Null",strNullList);
			FindNodeValue(ResNode,"IDS_Edit_Adv_User",strEditAdvUser);
			FindNodeValue(ResNode,"IDS_Edit_General_User",strEditUser);
			FindNodeValue(ResNode,"IDS_Del_User",strDelUser);
			FindNodeValue(ResNode,"IDS_Save_Add",strSaveAdd);
			FindNodeValue(ResNode,"IDS_Cancel_Add_User",strCancelAdd);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);
		}
		CloseResource(objRes);
	}

/*
	strMainTitle ="用户管理";
	strTitle ="普通用户列表";
	
	strNameLabel = "用户名";
	strNameDes = "登录后，页面中显示的名称";
	strNameError = "用户名不能为空或重复";

	strLoginLabel = "登录名";	
	strLoginDes = "登录系统时输入的名称";
	strLoginError = "登录名不能为空或重复";
	strState = "状态";
	strNameUse = "禁止";
	strNameEdit="编辑";
	strAdminTitle ="管理员列表";
	strDel=  "确认删除选中用户吗？";
	strAdd="添加用户";
	strEdit="编辑用户";
	strGeneral="基础设置";	

	strPwdLabel = "密码";
	strPwdDes = "新用户的密码，允许为空。如果使用LDAP验证则此项将不使用";
	
	strConfirmPwdLabel = "密码确认";
	strConfirmPwdDes = "重复输入新用户的密码";
	strConfirmPwdError = "密码输入有误, 请重新输入";
	strNullList = "[----------普通用户列表为空-----------]";
*/
	bAddEdit=false;
	bShowRight = false;
	pFrameTable = NULL;
	pUserAddTable = NULL;
	ShowMainTable();
}

CUserList::~CUserList(void)
{

}


//随机index
unsigned int RandIndex()
{
	unsigned int nPort = 0;
	unsigned int nMin  = 0x4000;
	unsigned int nMax  = 0x7FFF;
	srand((unsigned)time( NULL ));
	nPort = rand();
	nPort = nPort | nMin;
	nPort = nPort & nMax;

	return nPort;
}

//根据list号获取唯一的index
string CUserList::GetOnlyIndex(int nList)
{
	string strIndex = "";
	int index = 0;
	while(true)
	{
		index = RandIndex();

		char chItem[32]  = {0};
		sprintf(chItem, "%d", index);
		strIndex = chItem;
	    SVTableRow * pRow = NULL;
		//if(nList == 0)
			pRow = m_svGenUserList.Row(chItem);
		//else
		//	pRow = m_svAddUserList.Row(chItem);
		
		if (pRow)
		{
			continue;
		}
		else
			break;
	}
	
	return strIndex;
}

//初始化主界面
void CUserList::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);		
/*
	pMainTable = new CMainTable(this, strMainTitle);

	pUserTable = new CFlexTable(pMainTable->elementAt(2,0),strTitle);
	
	pUserListTable = new WTable( pUserTable->GetContentTable()->elementAt(0,0));
	pUserListTable ->setStyleClass("t3");
	AddColum(pUserListTable,true);


	pUserTable->AddGroupOperate(pUserTable->GetContentTable(),strDel);
	pUserTable->AddGroupAddBtn(pUserTable->m_pGroupOperate, strAdd);

	connect(&m_genMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditUser(const std::string)));
	
	connect(&m_adMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditAdminUser(const std::string)));
	
	connect(pUserTable->pAdd, SIGNAL(clicked()),  "showbar();" ,this, SLOT(AddUser()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	
	connect(pUserTable->pDel , SIGNAL(clicked()),this, SLOT(BeforeDelUser()));
	
	connect(pUserTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
	connect(pUserTable->pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
	connect(pUserTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
	
	pUserTable->pAdd->setStyleClass("wizardbutton");

	pAdminUserTable = new CFlexTable(pMainTable->elementAt(3,0),strAdminTitle);
	pAdminUserListTable =new WTable(pAdminUserTable->GetContentTable()->elementAt(0,0));
	pAdminUserListTable ->setStyleClass("t3");
	AddColum(pAdminUserListTable,false);
    
	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName, strLoginName, strIsUse, strPwd, strIndex;
	int nIsUse, nAdmin = -1;
	
	//从ini获取用户列表
	if(GetIniFileSections(keylist, "user.ini"))
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据
			strIndex = GetIniFileString((*keyitem), "nIndex", "", "user.ini");

			nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, "user.ini");
			if(nIsUse == -1)
				strIsUse = strNameUse;
			else
				strIsUse = strEnable;

			strUserName = GetIniFileString((*keyitem), "UserName", "" , "user.ini");
			
			strLoginName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");
			
			strPwd = GetIniFileString((*keyitem), "Password", "", "user.ini");

			nAdmin = GetIniFileInt((*keyitem), "nAdmin", -1, "user.ini");

			if(nAdmin == -1)
				AddGenUser(strIndex, strUserName, strLoginName, strPwd, strIsUse);
			else
				AddAdminUser(strIndex, strUserName, strLoginName, strPwd, strIsUse);
		}
	}	

	if(m_svGenUserList.RowCount() <= 1)
	{
		WText * m_pNullText = new WText(szNoGenUserItem, (WContainerWidget*)pUserListTable->elementAt(1 , 2));
		m_pNullText->decorationStyle().setForegroundColor(Wt::red);
	}

	//隐藏按钮
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelUser()));
		pHideBut->hide();
	}


	//new WText("请选择组",pMainTable->elementAt(4,0));
	
//	initAddUserTable();
//	pUserAddTable->hide();

	//pGroupTree
	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pMainTable->pTranslateBtn->show();
		connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pMainTable->pExChangeBtn->show();
		connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pMainTable->pTranslateBtn->hide();
		pMainTable->pExChangeBtn->hide();
	}
	*/
	p_MainTable = new WSVMainTable(this, strMainTitle,true);
	if (p_MainTable->pHelpImg)
	{
		connect(p_MainTable->pHelpImg, SIGNAL(clicked()),this,SLOT());
	}
	initUserTable();
	initAdminUserTable();
}


void CUserList::initUserTable()
{
	p_UserTable = new WSVFlexTable((WContainerWidget *)p_MainTable->GetContentTable()->elementAt(0,0), List,strTitle);
	p_UserTable->SetDivId("listpan1");
	if(p_UserTable->GetContentTable()!=NULL)
	{
		strListHeights += 1;
		strListHeights += ",";
		strListPans += p_UserTable->GetDivId();
		strListPans += ",";
		strListTitles +=  p_UserTable->dataTitleTable->formName();
		strListTitles += ",";

		p_UserTable->AppendColumn("",WLength(80,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");
		p_UserTable->AppendColumn(strNameLabel,WLength(50,WLength::Percentage));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");
		p_UserTable->AppendColumn(strLoginLabel,WLength(50,WLength::Percentage));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");
		p_UserTable->AppendColumn(strState,WLength(100,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");
		p_UserTable->AppendColumn(strNameEdit,WLength(100,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_img");
	}
	if(p_UserTable->GetActionTable()!=NULL)
	{
		p_UserTable->AddStandardSelLink(szTipSelAll, szTipNotSelAll, szTipInvSel);
	}

	p_UserTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
	p_UserTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");

	WTable *m_pGroupOperate = new WTable(p_UserTable->GetActionTable()->elementAt(0,1));

	m_pGroupOperate->setStyleClass("widthauto");
	//删除
	WSVButton *pDel= new WSVButton(m_pGroupOperate->elementAt(0,0),szTipDel,"button_bg_del.png");
	//添加
	p_UserTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
	WSVButton * pAdd = new WSVButton(p_UserTable->GetActionTable()->elementAt(0,2), strAdd, "button_bg_add_black.png", strAdd, true);

	connect(&m_genMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditUser(const std::string)));

	connect(&m_adMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditAdminUser(const std::string)));

	connect(pAdd, SIGNAL(clicked()),  "showbar();" ,this, SLOT(AddUser()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelUser()));

	connect(p_UserTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
	connect(p_UserTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));
	connect(p_UserTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));

	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName, strLoginName, strIsUse, strPwd, strIndex;
	int nIsUse, nAdmin = -1;

	//从ini获取用户列表
	if(GetIniFileSections(keylist, "user.ini"))
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据
			strIndex = GetIniFileString((*keyitem), "nIndex", "", "user.ini");

			nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, "user.ini");
			if(nIsUse == -1)
				strIsUse = strNameUse;
			else
				strIsUse = strEnable;

			strUserName = GetIniFileString((*keyitem), "UserName", "" , "user.ini");

			strLoginName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");

			strPwd = GetIniFileString((*keyitem), "Password", "", "user.ini");
			OutputDebugString("\n---------strPwd------------\n");
			OutputDebugString(strPwd.c_str());

			nAdmin = GetIniFileInt((*keyitem), "nAdmin", -1, "user.ini");

			if(nAdmin == -1)
			{
				USER_LIST list;

				std::string section = *keyitem;
				int numRow = p_UserTable->GeDataTable()->numRows();
				char abc[100];
				sprintf(abc,"---initUserTable-%d \n",numRow);
				OutputDebugString(abc);
				p_UserTable->InitRow(numRow);
				//选择
				WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow, 0));
				p_UserTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);

				//文本
				WText * pUserNameText = new WText(strUserName, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 2));
				p_UserTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
				WText * pLoginNameText = new WText(strLoginName, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 4));
				p_UserTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
				WText * pIsUseText = new WText(strIsUse, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 6));				
				p_UserTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);

				WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 8));
				p_UserTable->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(AlignCenter);
				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
				m_genMapper.setMapping(pEdit, strIndex); 
				connect(pEdit, SIGNAL(clicked()), "showbar();" ,&m_genMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

				WText * pPwdText = new WText(strPwd, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 10));
				pPwdText->hide();

				list.pSelect = pCheck;
				list.pUserName = pUserNameText;
				list.pLoginName = pLoginNameText;
				list.pStatus = pIsUseText;
				list.id = section;
				m_pListUSER.push_back(list);
			}
		}
		p_UserTable->SetNullTipInfo(strNullList);

		if(m_pListUSER.size() == 0)
		{
			p_UserTable->ShowNullTip();
			OutputDebugString("\n-----------ShowNullTip------------\n");
		}
		else
		{
			p_UserTable->HideNullTip();
			OutputDebugString("\n-----------HideNullTip------------\n");
		}
	}
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelUser()));
		pHideBut->hide();
	}
}

void CUserList::initAdminUserTable()
{
	p_AdminUserTable = new WSVFlexTable((WContainerWidget *)p_MainTable->GetContentTable()->elementAt(1,0), List, strAdminTitle);
	p_AdminUserTable->SetDivId("listpan2");
	if(p_AdminUserTable->GetContentTable()!=NULL)
	{
		strListHeights += 2;
		strListHeights += ",";
		strListPans += p_AdminUserTable->GetDivId();
		strListPans += ",";
		strListTitles +=  p_AdminUserTable->dataTitleTable->formName();
		strListTitles += ",";

		p_AdminUserTable->AppendColumn("",WLength(80,WLength::Pixel));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_text");
		p_AdminUserTable->AppendColumn(strNameLabel,WLength(50,WLength::Percentage));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_text");
		p_AdminUserTable->AppendColumn(strLoginLabel,WLength(50,WLength::Percentage));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_text");
		p_AdminUserTable->AppendColumn("",WLength(100,WLength::Pixel));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_text");
		p_AdminUserTable->AppendColumn(strNameEdit,WLength(100,WLength::Pixel));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_img");
/*
		p_AdminUserTable->AppendColumn(strNameLabel,WLength(50,WLength::Percentage));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_text");
		p_AdminUserTable->AppendColumn(strLoginLabel,WLength(50,WLength::Percentage));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_text");;
		p_AdminUserTable->AppendColumn(strNameEdit,WLength(100,WLength::Pixel));
		p_AdminUserTable->SetDataRowStyle("table_data_grid_item_img");
*/
		}

	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName, strLoginName, strIsUse, strPwd, strIndex;
	int nIsUse, nAdmin = -1;

	//从ini获取用户列表
	if(GetIniFileSections(keylist, "user.ini"))
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据
			strIndex = GetIniFileString((*keyitem), "nIndex", "", "user.ini");

			nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, "user.ini");
			if(nIsUse == -1)
				strIsUse = strNameUse;
			else
				strIsUse = strEnable;

			strUserName = GetIniFileString((*keyitem), "UserName", "" , "user.ini");

			strLoginName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");

			strPwd = GetIniFileString((*keyitem), "Password", "", "user.ini");

			nAdmin = GetIniFileInt((*keyitem), "nAdmin", -1, "user.ini");

			if(nAdmin != -1)
			{
				int numRow = p_AdminUserTable->GeDataTable()->numRows();

				//new WText(" ", (WContainerWidget*)pAdminUserListTable->elementAt(numRow, 0));

				//文本
				//用户名
				WText * pUserNameText = new WText(strUserName, (WContainerWidget*)p_AdminUserTable->GeDataTable()->elementAt(numRow , 2));
				p_AdminUserTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
				WText * pLoginNameText = new WText(strLoginName, (WContainerWidget*)p_AdminUserTable->GeDataTable()->elementAt(numRow , 4));
				p_AdminUserTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
				//	WText * pIsUseText = new WText(strIsUse, (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 3));

				WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)p_AdminUserTable->GeDataTable()->elementAt(numRow , 8));
				p_AdminUserTable->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(AlignCenter);
				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
				m_adMapper.setMapping(pEdit, strIndex); 
				connect(pEdit, SIGNAL(clicked()), "showbar();", &m_adMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

				WText * pPwdText = new WText(strPwd, (WContainerWidget*)p_AdminUserTable->elementAt(numRow , 10));
				pPwdText->hide();
			}
		}
	}
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelUser()));
		pHideBut->hide();
	}
}

//
void CUserList::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/userright.exe?'\",1250);  ";
	appSelf->quit();
}
//
void CUserList::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "userrightRes";
	WebSession::js_af_up += "')";
}

//加列标题
/*void CUserList::AddColum(WTable* pContain,bool bUserType)
{
	new WText(" ", pContain->elementAt(0,0));
	new WText(strNameLabel, pContain->elementAt(0,1));
	new WText(strLoginLabel, pContain->elementAt(0,2));
	if( bUserType==true )
	{
		new WText(strState, pContain->elementAt(0,3));
	}
	new WText(strNameEdit, pContain->elementAt(0,4));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}*/

//编辑普通用户按钮响应
void CUserList::EditUser(const std::string strIndex)
{	
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "EditUser";
	LogItem.sDesc = strEditUser;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	/*bAddEdit = false;
	if(pUserAddTable != NULL)
	{
		m_RightTplList.clear();
		pUserAddTable->clear();
		delete pUserAddTable;
		pUserAddTable = NULL;
		
	}
	//隐藏
	//pUserTable->hide();
	//pAdminUserTable->hide();
	pMainTable->hide();

	strGenIndex = strIndex;

	//普通用户
	bShowRight = true;	

	initEditUserTable(strIndex,true);
	WebSession::js_af_up = "hiddenbar()";*/
	bAddEdit = false;
	if(pUserAddTable != NULL)
	{
		m_RightTplList.clear();
		m_pListUSER.clear();
		pUserAddTable->clear();
		delete pUserAddTable;
		pUserAddTable = NULL;

	}
	//隐藏
	//pUserTable->hide();
	//pAdminUserTable->hide();
	p_MainTable->GetContentTable()->hide();

	strGenIndex = strIndex;

	//普通用户
	bShowRight = true;	

	initEditUserTable(strIndex,true);

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

	WebSession::js_af_up = "window.location.reload(true);hiddenbar()";
}

//编辑高级用户按钮响应
void CUserList::EditAdminUser(const std::string strIndex)
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "EditAdminUser";
	LogItem.sDesc = strEditAdvUser;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	if(pUserAddTable != NULL)
	{
		m_RightTplList.clear();
		m_pListUSER.clear();
		pUserAddTable->clear();
		delete pUserAddTable;
		pUserAddTable = NULL;
		
	}	
	//隐藏
	p_MainTable->GetContentTable()->hide();
	
	strGenIndex = strIndex;

	bShowRight = false;
		
	initEditUserTable(strIndex,false);		

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

	WebSession::js_af_up = "hiddenbar()";
}

//
void CUserList::BeforeDelUser()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "BeforeDelUser";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);
	
	/*for(row it = m_svGenUserList.begin(); it != m_svGenUserList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
            if (pcell->Type() == adCheckBox)
            {
                if(((WCheckBox*)pcell->Value())->isChecked())
                {
					if(pHideBut)
					{
						string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
						if(!strDelDes.empty())
						{
							strDelDes  = "_Delclick('" + strDeleteUserAffirm + "','" + szButNum + "','" + szButMatch + "','" + strDelDes + "');"; 
							WebSession::js_af_up = strDelDes;							
						}					
					}
					break;	                    
               }
            }
        }  
	}*/
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{        
		if (m_pListItem->pSelect->isChecked())
		{   
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + strDeleteUserAffirm + "','" + szButNum + "','" + szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;
				}					
			}
			break;
		}
	}

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

//删除用户按钮响应
void CUserList::DelUser()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "DelUser";
	LogItem.sDesc = strDelUser;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//OutputDebugString("dfdf\n");
	//return;
//Del:
	/*row it = NULL;
	for(it = m_svGenUserList.begin(); it != m_svGenUserList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
            if (pcell->Type() == adCheckBox)
            {
                if(((WCheckBox*)pcell->Value())->isChecked())
                {
                   SVTableCell *pcell2 = it->second.Cell(1);
				   string strTemp1 = ((WText*)pcell2->Value())->text();
				   strDelName += strTemp1;
				   strDelName += "  ";

				   int nRow = ((WTableCell*)(((WCheckBox*)pcell->Value())->parent()))->row();
                   string  strIndex = pcell->Row();
                   //row pTemp = it --;					
				   
				   //ini数据更新。。
					DeleteIniFileSection(strIndex, "user.ini");
				   	
					//内存列表数据更新。。	
					m_svGenUserList.DelRow(strIndex); 	
				   
					//界面列表更新。。                  
				   pUserListTable->deleteRow(nRow);
                      
                   //it = pTemp;
				   goto Del;
                }
            }
        }       
    }

	pUserListTable->adjustRowStyle("tr1","tr2"); 

	if(m_svGenUserList.RowCount() <= 1)
	{
		WText * m_pNullText = new WText(szNoGenUserItem, (WContainerWidget*)pUserListTable->elementAt(1 , 2));
		m_pNullText->decorationStyle().setForegroundColor(Wt::red);
	}

	if(pUserAddTable != NULL)
	{
		pUserAddTable->hide();
	}

	//插记录到UserOperateLog表
	string strUserID = GetWebUserID();
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeDelete,strMainTitle,strDelName);
	strDelName = "";*/

	string strDeleteUser;
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		if (m_pListItem->pSelect->isChecked())
		{   
			std::string temp = m_pListItem->id;
			std::string strIndex = m_pListItem->id;
			//DeleteIniFileSection(temp, "user.ini");
			
			//ShanTou
			#ifdef ShanTou						
				string strDelUserName = GetIniFileString(strIndex, "UserName", "" , "user.ini");						
				string strDelLoginName = GetIniFileString(strIndex, "LoginName", "", "user.ini");						
				string strDelPwd = GetIniFileString(strIndex, "Password", "", "user.ini");
				Des mydes;
				char dechar[1024]={0};
				if(strDelPwd.size()>0)
				{
					mydes.Decrypt(strDelPwd.c_str(),dechar);
					strDelPwd= dechar;
				}
				
				//ShanTou	
				//与Eip同步用户名称和密码, 用js调用webservice 组织js同步串		
				string strWebservice = "RequestByGet('";
				//string strWebservice = "RequestByPost('";
				strWebservice += "0015";
				strWebservice += "','";
				strWebservice += TrimStdString(strDelLoginName);
				strWebservice += "','";
				strWebservice += TrimStdString(strDelUserName);
				strWebservice += "','";
				
				//Md5加密密码 
				strWebservice += myMd5(strDelPwd);
				strWebservice += "','";
				
				strWebservice += "delete";
				strWebservice += "');";
				
				OutputDebugString("strWebservice:");
				OutputDebugString(strWebservice.c_str());
				OutputDebugString("\n");

				WebSession::js_af_up = strWebservice;

				DeleteIniFileSection(strIndex, "user.ini");
			#else
				DeleteIniFileSection(strIndex, "user.ini");
			#endif


			int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();

			list<USER_LIST>::iterator pItem = m_pListItem;                     

			m_pListItem --;

			string strTemp = pItem->pUserName->text();
			strDeleteUser += strTemp;
			strDeleteUser += "  ";


			m_pListUSER.erase(pItem);          

			p_UserTable->GeDataTable()->deleteRow(nRow); 						
		}
	}

	//if(m_pListUSER.size() == 0)
	//{
	//	//WText * nText = new WText("[----------短信接收手机号设置列表为空-----------]", (WContainerWidget*)m_nullTable -> elementAt(0, 0));
	//	//nText ->decorationStyle().setForegroundColor(Wt::red);
	//	//m_nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}

	if(m_pListUSER.size() == 0)
	{
		p_UserTable->ShowNullTip();
		OutputDebugString("\n-----------ShowNullTip------------\n");
	}
	else
	{
		p_UserTable->HideNullTip();
		OutputDebugString("\n-----------HideNullTip------------\n");
	}

	delete p_UserTable;
	p_UserTable = NULL;
	delete p_AdminUserTable;
	p_AdminUserTable = NULL;
	m_pListUSER.clear();
	initUserTable();
	initAdminUserTable();

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeDelete,strMainTitle,strDelName);
	strDelName = "";

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

//增加用户按钮响应
void CUserList::AddUser()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "AddUser";
	LogItem.sDesc = strAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	/*bAddEdit = true;
	if(pUserAddTable != NULL)
	{
		m_RightTplList.clear();
		pUserAddTable->clear();
		delete pUserAddTable;
		pUserAddTable = NULL;		
	}
	//OutputDebugString("AddUser");
	initAddUserTable();
	//OutputDebugString("AddUser1");
	pUserTable->hide();
	pAdminUserTable->hide();

	pCheckDisable->show();

	strGenIndex = "-1";

	bShowRight = true;
	//OutputDebugString("AddUser2sdddd");
	ClearValue();
	//OutputDebugString("AddUser44444");
	pMainTable->hide();
	pUserAddTable->show();
	DWORD dwStart = GetTickCount();
	//OutputDebugString("AddUser2");
	pGroupTree->InitTree("",true,true,false,"1");

	//OutputDebugString("AddUser3");
	pUserAddTable->HideAllErrorMsg();
	
	pRightTable->show();
	//OutputDebugString("AddUser4");
	char aa[300];
	sprintf(aa,"---%d--\n", GetTickCount()-dwStart);
	//OutputDebugString(aa);
	WebSession::js_af_up = "hiddenbar()";*/
	
	bAddEdit = true;
	if(pUserAddTable != NULL)
	{
		m_RightTplList.clear();
		delete pUserAddTable;
		pUserAddTable = NULL;		
	}
	//OutputDebugString("AddUser");
	initAddUserTable();
	//OutputDebugString("AddUser1");
	p_MainTable->GetContentTable()->hide();

	pCheckDisable->show();

	strGenIndex = "-1";

	bShowRight = true;
	//OutputDebugString("AddUser2sdddd");
	ClearValue();
	//OutputDebugString("AddUser44444");
	pUserAddTable->show();
	DWORD dwStart = GetTickCount();
	//OutputDebugString("AddUser2");
	pGroupTree->InitTree("",true,true,false,"1");

	//OutputDebugString("AddUser3");
	//pUserAddTable->HideAllErrorMsg();

	//pRightTable->show();
	//OutputDebugString("AddUser4");

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

	WebSession::js_af_up = "window.location.reload(true);hiddenbar()";
}

//是否有相同的登录名用户存在
bool CUserList::IsUserExist(string strLoginNameIn, string strUserNameIn)
{
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName;
	string strLoginName;

	bool bExist = false;
	//从ini获取用户列表
	if(GetIniFileSections(keylist, "user.ini"))
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据			
			//strUserName = GetIniFileString((*keyitem), "UserName", "", "user.ini");
			strLoginName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");
			//if(strLoginName == strLoginNameIn || strUserName == strUserNameIn)
			if(strLoginName == strLoginNameIn && (*keyitem) != strGenIndex)
			{
				bExist = true;
				break;
			}
		}
	}

	return bExist;		
}

//保存按钮响应
void CUserList::SaveUser()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "EditUser";
	LogItem.sDesc = strSaveAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	//错误检查
	bool bError = false;
	std::list<string> errorMsgList;

    //用户名称
	if(pEditUserName->text().empty())
    {
		ErrorTest(strNameError);
		bError = true;
    }
    // 登陆名称
    if(pEditLogin->text().empty())
    {
        ErrorTest(strLoginError);
		bError = true;
    }
    
    // 密码输入不对
    if (pEditPwd->text() != pEditConfirmPwd->text())
    {
		ErrorTest(strConfirmPwdError);
		bError = true;
    }
	
	if(IsUserExist(pEditLogin->text(), pEditUserName->text()))
	{
		 ErrorTest(strLoginError);
		bError = true;
	}

	//有错误返回
	if(bError)
	{
		//pUserAddTable->ShowErrorMsg(errorMsgList);
		WebSession::js_af_up = "hiddenbar()";
		bEnd = true;	
		goto OPEnd;
	}

	//数据存储。。
	bool bAdd = false;

	//基础参数(增加 编辑一样)
	if(strGenIndex == "-1")
	{
		strGenIndex = GetOnlyIndex(0);
		bAdd = true;
	}
	else
	{
		bAdd = false;
	}

	//OutputDebugString("SaveUser");
	//OutputDebugString(strGenIndex.c_str());
	WriteIniFileString(strGenIndex, "nIndex", strGenIndex, "user.ini");
	WriteIniFileString(strGenIndex, "UserName", TrimStdString(pEditUserName->text()).c_str(), "user.ini");
	WriteIniFileString(strGenIndex, "LoginName", TrimStdString(pEditLogin->text()).c_str(), "user.ini");

	std::string pwd;
	pwd = pEditPwd->text();
	pwd = TrimStdString(pEditPwd->text());
	Des mydes;
	char enchar[1024]={0};
	if(pwd.size()>0)
	{
		mydes.Encrypt(pwd.c_str(),enchar);
		pwd= enchar;
	}

	WriteIniFileString(strGenIndex, "Password", pwd.c_str(), "user.ini");	
	CUser* pCurUser = new CUser();
	GetGroupRightList(pCurUser);
	std::string groupright;
	groupright=",";

	for( list<std::string >::iterator _listitem = pGroupRightList.begin(); _listitem != pGroupRightList.end(); _listitem ++)
	{  	
		groupright +=_listitem->c_str();
		groupright +=",";
	}
	std::string ungroupright;
	for( list<std::string >::iterator _listitem = pUnGroupRightList.begin(); _listitem != pUnGroupRightList.end(); _listitem ++)
	{  	
		ungroupright +=_listitem->c_str();
		ungroupright +=",";
	}

	if(pGroupRightList.empty())
	{
		WebSession::js_af_up += "hiddenbar();";
		WebSession::js_af_up += "alert('";
		WebSession::js_af_up += "没有选择监测范围";
		WebSession::js_af_up += "')";

		return ;
	}

	
	for(ScopeFuncMap::iterator pList1 = pCurUser->m_ScopeFuncmap.begin();pList1!=pCurUser->m_ScopeFuncmap.end();pList1++)
	{
	
		PScopeFunc pList=PScopeFunc( pList1->second);
		
		
		std::string  strTmp;
		
		ScopeRightMap::iterator i;
		
		
		for( i= pList->m_ScopeRightMap.begin();i!=pList->m_ScopeRightMap.end();i++)
		{
			strTmp+=i->first;
			strTmp+="=";
			if(i->second)
				strTmp+= "1,";
			else
				strTmp+="0,";

		}
		WriteIniFileString(strGenIndex, pList->strScopeId, strTmp, "user.ini");	
		/*
		char aaa[3000];
		sprintf(aaa," size is %d,  %s=%s\n",pCurUser->m_ScopeFuncmap.size(), pList->strScopeId.c_str(),strTmp.c_str());
		OutputDebugString(aaa);
		*/

	}

	delete pCurUser;
/*
    char abc[2000];
	sprintf(abc,"groupright is  %s\n",ungroupright.c_str());
	OutputDebugString(abc);
*/
	WriteIniFileString(strGenIndex, "groupright", groupright, "user.ini");	
	WriteIniFileString(strGenIndex, "ungroupright", ungroupright, "user.ini");	

	if(pCheckDisable->isChecked())
		WriteIniFileInt(strGenIndex, "nIsUse", -1, "user.ini");
	else
		WriteIniFileInt(strGenIndex, "nIsUse", 1, "user.ini");

	//Admin测试函数
	//WriteIniFileInt(strGenIndex, "nAdmin", 1, "user.ini");

	if(bShowRight)
	{
		//权限列表参数
		for(m_RightTplListItem = m_RightTplList.begin(); m_RightTplListItem != m_RightTplList.end(); m_RightTplListItem ++)
		{
			if(((POneRight)*m_RightTplListItem)->pRightCheckBox->isChecked())
			{
				WriteIniFileInt(strGenIndex, ((POneRight)*m_RightTplListItem)->strRightText.c_str(), 1, "user.ini");
			}
			else
			{
				WriteIniFileInt(strGenIndex, ((POneRight)*m_RightTplListItem)->strRightText.c_str(), -1, "user.ini");
			}
		}
	}	

	//更新用户界面列表。。	
	//更新列表

	//清空列表
	//p_UserTable->GeDataTable()->clear();
	delete p_UserTable;
	p_UserTable = NULL;
	//p_AdminUserTable->GeDataTable()->clear();
	delete p_AdminUserTable;
	p_AdminUserTable = NULL;
	m_pListUSER.clear();
	initUserTable();
	initAdminUserTable();

	/*string strPwd = "", strIsUse;
	if(pCheckDisable->isChecked())
		strIsUse = strNameUse;		
	else
		strIsUse = strEnable;

	if(bAdd)
	{
		//1、增加。。。	
		if(m_svGenUserList.RowCount() <= 1)
		{
			pUserListTable->deleteRow(1);
		}

		AddGenUser(strGenIndex, TrimStdString(pEditUserName->text()).c_str(), TrimStdString(pEditLogin->text()).c_str(), TrimStdString(pEditPwd->text()).c_str(), strIsUse);
	}
	else
	{
		//2、编辑。。。
		EditGenUser(strGenIndex, TrimStdString(pEditUserName->text()).c_str(), TrimStdString(pEditLogin->text()).c_str(), TrimStdString(pEditPwd->text()).c_str(), strIsUse);
	}*/

	//插记录到UserOperateLog表
	//string strUserID = GetWebUserID();
	//TTime mNowTime = TTime::GetCurrentTimeEx();
	//OperateLog m_pOperateLog;
	//if(bAdd)
	//{
	//	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeAdd,strMainTitle,pEditUserName->text());
	//}
	//else
	//{
	//	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strNameEdit,strMainTitle,pEditUserName->text());
	//}

	//隐藏编辑界面
	pUserAddTable->hide();
	//pUserAddTable->HideAllErrorMsg();
	
	//if(pRightTable != NULL)
	//{
	//	pRightTable->clear();
	//	delete pRightTable;
	//	pRightTable = NULL;		
	//}

	//if(pFrameTable != NULL)
	//{
	//	pFrameTable->clear();
	//	delete pFrameTable;
	//	pFrameTable = NULL;
	//	
	//}

	//if(pSubTreeTable != NULL)
	//{
	//	pSubTreeTable->clear();
	//	delete pSubTreeTable;
	//	pSubTreeTable = NULL;
	//	
	//}

	//if(pUserAddTable != NULL)
	//{
	//	pUserAddTable->clear();
	//	delete pUserAddTable;
	//	pUserAddTable = NULL;
	//	
	//}

	//m_RightTplList.clear();


	p_MainTable->GetContentTable()->show();

#ifdef ShanTou
	//ShanTou	
	//与Eip同步用户名称和密码, 用js调用webservice 组织js同步串		
	string strWebservice = "RequestByGet('";
	//string strWebservice = "RequestByPost('";
	strWebservice += "0015";
	strWebservice += "','";
	strWebservice += TrimStdString(pEditLogin->text());
	strWebservice += "','";
	strWebservice += TrimStdString(pEditUserName->text());
	strWebservice += "','";
	//Md5加密密码 
	
	strWebservice += myMd5(TrimStdString(pEditPwd->text()));
	strWebservice += "','";
	
	if(bAdd)
	{
		strWebservice += "add";
		strWebservice += "');hiddenbar()";
		
		//OutputDebugString("strWebservice:");
		//OutputDebugString(strWebservice.c_str());
		//OutputDebugString("\n");
		
		WebSession::js_af_up = strWebservice;
	}
	else
	{
		strWebservice += "update";
		strWebservice += "');hiddenbar()";

		//OutputDebugString("strWebservice:");
		//OutputDebugString(strWebservice.c_str());
		//OutputDebugString("\n");

		WebSession::js_af_up = strWebservice;
	}
#else
	WebSession::js_af_up = "hiddenbar()";
#endif

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//取消按钮响应
void CUserList::CancelUser()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "EditUser";
	LogItem.sDesc = strCancelAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	strGenIndex = "-1";

	//隐藏 pUserAddTable
	pUserAddTable->hide();
	//pUserAddTable->HideAllErrorMsg();
	p_MainTable->GetContentTable()->show();
	OutputDebugString("取消成功!");
	WebSession::js_af_up = "hiddenbar()";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}


//清空编辑用户界面
void CUserList::ClearValue()
{
	//if(pUserAddTable != NULL)
	//{
	//	pEditUserName->setText(""); 
	//	pEditLogin->setText("");
	//	pCheckDisable->setUnChecked();
	//	pEditPwd->setText("");
	//	pEditConfirmPwd->setText("");

	//	for(m_RightTplListItem = m_RightTplList.begin(); m_RightTplListItem != m_RightTplList.end(); m_RightTplListItem ++)
	//	{		
	//		((POneRight) *m_RightTplListItem)->pRightCheckBox->setChecked();
	//	}
	//}
}

//生成编辑用户界面

void CUserList::initAddUserTable()
{/*
	if( bAddEdit == true)
	{
		pUserAddTable = new CAnswerTable(this, strAdd);
	}
	else
	{
		pUserAddTable = new CAnswerTable(this, strEdit);
	}
	

	//#if 0 //关闭树
//	//框架
//	pFrameTable = new WTable(pUserAddTable->GetContentTable() ->elementAt(2,0));
//	pFrameTable ->setStyleClass("t3");
//	pFrameTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
//
//	pFrameTable->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);
//	pFrameTable->elementAt(0, 2)->setContentAlignment(AlignTop | AlignLeft);
//
//
//	pFrameTable->elementAt(0, 0)->resize(WLength(26,WLength::Percentage),WLength(100,WLength::Percentage));
//	pFrameTable->elementAt(0, 1)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
//	
//	//左边树
//	pSubTreeTable = new WTable((WContainerWidget *)pFrameTable->elementAt(0,0));
//	pSubTreeTable ->setStyleClass("t62");
//	pFrameTable->elementAt(0,0)->resize(WLength(200,WLength::Pixel),WLength(100,WLength::Percentage));
//	
//	
//	
//	pSubTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
//
//	//中间可拖动的分割表格
//	WImage *spaceImg =new WImage("../Images/space.gif");
//	pFrameTable ->elementAt(0,1)->addWidget(spaceImg);
//	std::string strContext;
//	strContext+="style=\"WIDTH:1px;CURSOR: w-resize\" ";
//	strContext+=" onmousedown='_canResize=true;this.setCapture(true)'";
//	strContext+="  onmouseup='this.releaseCapture();_canResize=false;'";
//	sprintf(pFrameTable ->elementAt(0,1)->contextmenu_,"%s", strContext.c_str());
//	
//	CFlexTable * pAddGene = new CFlexTable((WContainerWidget *)pFrameTable->elementAt(0, 2), strGeneral);
//#endif

	pFrameTable = new WTable(pUserAddTable->GetContentTable() ->elementAt(1,0));

	pFrameTable ->setStyleClass("t1");
	
	CFlexTable * pAddGene=new CFlexTable(pFrameTable->elementAt(0,0),strGeneral);
	new WText(strLoginLabel,pAddGene->GetContentTable()->elementAt(0, 0));
	new WText("<span class =required>*</span>", pAddGene->GetContentTable()->elementAt(0,0));
	pEditLogin= new WLineEdit("",pAddGene->GetContentTable()->elementAt(0, 1));
	pEditLogin->setStyleClass("cell_40");
	pAddGene->GetContentTable()->elementAt(0, 0)->setStyleClass("t3left");
	pUserAddTable->AddErrorText(pAddGene->GetContentTable(), strLoginError, 1, 1);
	pUserAddTable->AddHelpText(pAddGene->GetContentTable(), strLoginDes, 2, 1);

	new WText(strNameLabel,pAddGene->GetContentTable()->elementAt(3,0));
	new WText("<span class =required>*</span>", pAddGene->GetContentTable()->elementAt(3,0));
	pEditUserName= new WLineEdit("",pAddGene->GetContentTable()->elementAt(3,1));
	pEditUserName->setStyleClass("cell_40");
	pAddGene->GetContentTable()->elementAt(1, 0)->setStyleClass("t3left");
	pUserAddTable->AddErrorText(pAddGene->GetContentTable(), strNameError, 4, 1);
	pUserAddTable->AddHelpText(pAddGene->GetContentTable(), strNameDes, 5, 1);

	pCheckDisable = new WCheckBox(strNameUse,pAddGene->GetContentTable()->elementAt(6, 1));
	
	new WText(strPwdLabel,pAddGene->GetContentTable()->elementAt(7, 0));
	pEditPwd= new WLineEdit("",pAddGene->GetContentTable()->elementAt(7, 1));
	pEditPwd->setStyleClass("cell_40");
	pEditPwd->setEchoMode(WLineEdit::Password);
	pAddGene->GetContentTable()->elementAt(3, 0)->setStyleClass("t3left");
	pUserAddTable->AddHelpText(pAddGene->GetContentTable(), strPwdDes, 8, 1);

	new WText(strConfirmPwdLabel,pAddGene->GetContentTable()->elementAt(9, 0));
	pEditConfirmPwd = new WLineEdit("",pAddGene->GetContentTable()->elementAt(9, 1));
	pEditConfirmPwd->setStyleClass("cell_40");
	pEditConfirmPwd->setEchoMode(WLineEdit::Password);
	pAddGene->GetContentTable()->elementAt(4, 0)->setStyleClass("t3left");
	pUserAddTable->AddErrorText(pAddGene->GetContentTable(), strConfirmPwdError, 10, 1);
	pUserAddTable->AddHelpText(pAddGene->GetContentTable(), strConfirmPwdDes, 11, 1);

	pRightTable = new WTable(pUserAddTable->GetContentTable()->elementAt(2,0));	
	pRightTable->setStyleClass("t1");	
	CFlexTable* pFlex = new CFlexTable(pRightTable->elementAt(0, 0), strEntity);	 
	pGroupTree = new CCheckBoxTreeView((WContainerWidget *)pFlex ->GetContentTable()->elementAt(0,0));

	//InitRightTableFromRes(pRightTable);

	//if(bShowRight)
	//{
	//	list<string>   sectionlist;
	//	GetIniFileSections(sectionlist, "userright.ini");

	//	int nRightIndex =2;
	//	
	//	for( list<std::string >::iterator _RightTplpListItem = sectionlist.begin(); _RightTplpListItem != sectionlist.end(); _RightTplpListItem ++)
	//	{
	//		CFlexTable *pFlex;
	//		nRightIndex =GetIniFileInt(_RightTplpListItem->c_str(), "sort", -1,"userright.ini") ;
	//		
	//		if(nRightIndex > 0 && nRightIndex != 6 && nRightIndex != 7 && nRightIndex != 8 && nRightIndex != 9)
	//		{
	//			pFlex = new CFlexTable(pRightTable->elementAt(nRightIndex, 0), 
	//				GetIniFileString(_RightTplpListItem->c_str(), "value", "","userright.ini")   );
	//			list<string>   keylist;
	//			GetIniFileKeys(_RightTplpListItem->c_str(),keylist,"userright.ini");
	//			int nRightTplIndex;
	//			nRightTplIndex =1;
	//			for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
	//			{
	//				POneRight aPOneRight;
	//				aPOneRight = new OneRight;
	//				aPOneRight->strRightText=_aRight->c_str();

	//				if((aPOneRight->strRightText.compare("value")!=0) && (aPOneRight->strRightText.compare("sort")!=0))
	//				{
	//					aPOneRight->strShowText= GetIniFileString(_RightTplpListItem->c_str(), _aRight->c_str(), "","userright.ini");
	//					aPOneRight->pRightCheckBox = new WCheckBox(aPOneRight->strShowText  , pFlex->GetContentTable()->elementAt(nRightTplIndex++,0));
	//					
	//					aPOneRight->pRightCheckBox->setChecked();
	//					
	//					//添加帮助信息。。。
	//					m_RightTplList.push_back(aPOneRight);
	//				}

	//			}

	//			pFlex->HideTable();
	//		}
	//	}		
	//}
	
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			string strTmp;
			string strTmpValue;
			//if(bShowRight)
			{
				list<string>   sectionlist;
				GetIniFileSections(sectionlist, "userright.ini");

				int nRightIndex =2;
				
				for( list<std::string >::iterator _RightTplpListItem = sectionlist.begin(); _RightTplpListItem != sectionlist.end(); _RightTplpListItem ++)
				{
					CFlexTable *pFlex;
					nRightIndex =GetIniFileInt(_RightTplpListItem->c_str(), "sort", -1,"userright.ini") ;
					
					if(nRightIndex > 0 && nRightIndex != 6 && nRightIndex != 7 && nRightIndex != 8 && nRightIndex != 9)
					{
						strTmp = GetIniFileString(_RightTplpListItem->c_str(), "value", "","userright.ini");
						FindNodeValue(ResNode, strTmp.c_str(), strTmpValue);
						pFlex = new CFlexTable(pRightTable->elementAt(nRightIndex, 0), strTmpValue);

						list<string>   keylist;
						GetIniFileKeys(_RightTplpListItem->c_str(),keylist,"userright.ini");
						int nRightTplIndex;
						nRightTplIndex =1;
						for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
						{
							POneRight aPOneRight;
							aPOneRight = new OneRight;
							aPOneRight->strRightText=_aRight->c_str();

							if((aPOneRight->strRightText.compare("value")!=0) && (aPOneRight->strRightText.compare("sort")!=0))
							{
								strTmp = GetIniFileString(_RightTplpListItem->c_str(), _aRight->c_str(), "","userright.ini");
								FindNodeValue(ResNode, strTmp.c_str(), strTmpValue);
								
								aPOneRight->strShowText= strTmpValue;
								aPOneRight->pRightCheckBox = new WCheckBox(aPOneRight->strShowText  , pFlex->GetContentTable()->elementAt(nRightTplIndex++,0));
								
								aPOneRight->pRightCheckBox->setChecked();
								
								//添加帮助信息。。。
								m_RightTplList.push_back(aPOneRight);
							}

						}

						pFlex->HideTable();
					}
				}		
			}		
		}
		CloseResource(objRes);
	}
	
	//拓扑图权限
	int nRow = 0;		
	nRow = pRightTable->numRows();
	CFlexTable *pFlexTop = new CFlexTable(pRightTable->elementAt(nRow, 0), strTuopRight);

	std::list<string> tuopList;
	std::list<string> ::iterator tuopListItem;

	int nRightTopIndex = 1;

	tuopList = GetTopFileList(GetSiteViewRootPath() + "\\htdocs\\tuoplist");
	//tuopList = GetTopFileList("C:\\Program Files\\Apache Group\\apache2\\htdocs\\tuoplist");
	for(tuopListItem = tuopList.begin(); tuopListItem != tuopList.end(); tuopListItem++)
	{
		//
		POneRight aPOneRight;
		aPOneRight = new OneRight;
		aPOneRight->strRightText = (*tuopListItem);
		aPOneRight->strShowText = (*tuopListItem);
						
		//
		aPOneRight->pRightCheckBox = new WCheckBox(aPOneRight->strShowText  , pFlexTop->GetContentTable()->elementAt(nRightTopIndex++, 0));
		aPOneRight->pRightCheckBox->setUnChecked();
		
		//
		m_RightTplList.push_back(aPOneRight);
	}

	pFlexTop->HideTable();

	nRow = pUserAddTable->GetContentTable()->numRows();
	pUserAddTable->GetContentTable()->elementAt(nRow,0)->setStyleClass("t5");
	
	pUserAddTable->HideAllErrorMsg();	
	//connect(pUserAddTable->pSave, SIGNAL(clicked()),this, SLOT(SaveUser()));	
	//connect(pUserAddTable->pCancel, SIGNAL(clicked()),this, SLOT(CancelUser()));
	connect(pUserAddTable->pSave, SIGNAL(clicked()), "showbar();" ,this, SLOT(SaveUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	connect(pUserAddTable->pCancel, SIGNAL(clicked()), "showbar();" ,this, SLOT(CancelUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pUserAddTable->pTranslateBtn->show();
		connect(pUserAddTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pUserAddTable->pExChangeBtn->show();
		connect(pUserAddTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pUserAddTable->pTranslateBtn->hide();
		pUserAddTable->pExChangeBtn->hide();
	}
*/


	if( bAddEdit == true)
	{
		pUserAddTable = new CAnswerTable(this, strAdd);
	}
	else
	{
		pUserAddTable = new CAnswerTable(this, strEdit);
	}

	WSVMainTable *p_ContentTabe = pUserAddTable->GetContentTable1();

	if (p_ContentTabe->pHelpImg)
	{
		connect(p_ContentTabe->pHelpImg ,SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}
	//一般设置
	p_AddGene = new WSVFlexTable((WContainerWidget *)p_ContentTabe->GetContentTable()->elementAt(0,0),Group,strGeneral);
	p_AddGene->AppendRows("");
	//登录名
	pEditLogin= new WLineEdit("",p_AddGene->AppendRowsContent(0, strLoginLabel+"<span class =required>*</span>", strLoginDes, strLoginError));
	pEditLogin->setStyleClass("input_text");
	//用户名
	pEditUserName= new WLineEdit("",p_AddGene->AppendRowsContent(0, strNameLabel+"<span class =required>*</span>", strNameDes, strNameError));
	pEditUserName->setStyleClass("input_text");
	//
	pCheckDisable = new WCheckBox(strNameUse,p_AddGene->AppendRowsContent(0, "", "", ""));

	//密码
	pEditPwd= new WLineEdit("",p_AddGene->AppendRowsContent(0, strPwdLabel, strPwdDes, ""));
	pEditPwd->setStyleClass("input_text");
	pEditPwd->setEchoMode(WLineEdit::Password);

	//确认密码
	pEditConfirmPwd = new WLineEdit("",p_AddGene->AppendRowsContent(0, strConfirmPwdLabel, strConfirmPwdDes, strConfirmPwdError));
	pEditConfirmPwd->setStyleClass("input_text");
	pEditConfirmPwd->setEchoMode(WLineEdit::Password);
	//隐藏help,erro
	p_AddGene->HideAllErrorMsg();
	p_AddGene->ShowOrHideHelp();
	
	//pRightTable->setStyleClass("t1");	
	//CFlexTable* pFlex = new CFlexTable(pRightTable->elementAt(0, 0), strEntity);	 
	//pGroupTree = new CCheckBoxTreeView((WContainerWidget *)pFlex ->GetContentTable()->elementAt(0,0));
	p_ContentTabe1 = pUserAddTable->GetContentTable2();

	pRightTable = p_ContentTabe1;
	WSVFlexTable* p_Flex = new WSVFlexTable((WContainerWidget *)p_ContentTabe1->elementAt(1,0),Group, strEntity);	 
	pGroupTree = new CCheckBoxTreeView((WContainerWidget *)p_Flex ->GetContentTable()->elementAt(0,0));

	//Resource
	int rowcount = 1;
	OBJECT 	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			string strTmp;
			string strTmpValue;
			//if(bShowRight)
			{
				list<string>   sectionlist;
				GetIniFileSections(sectionlist, "userright.ini");

				int nRightIndex =2;
                //DeleteIniFileKey("m_report","m_statisticReport","userright.ini");
				//WriteIniFileString("m_report","m_reportlistAdd","IDS_Total_Report","userright.ini");
                WriteIniFileString("m_report","m_reportlistAdd_add","IDS_Report_Add","userright.ini");
				for( list<std::string >::iterator _RightTplpListItem = sectionlist.begin(); _RightTplpListItem != sectionlist.end(); _RightTplpListItem ++)
				{
					nRightIndex =GetIniFileInt(_RightTplpListItem->c_str(), "sort", -1,"userright.ini") ;
					OutputDebugString(("\n444444444444444444444"+(*_RightTplpListItem)+"5555555555555555\n").c_str());
					char x[100];
					sprintf(x,"%d\n",rowcount);
					OutputDebugString("---------nRightIndex----------\n");
					OutputDebugString(x);

					if(nRightIndex > 0 && nRightIndex != 6 && nRightIndex != 7 && nRightIndex != 8 && nRightIndex != 9)
					{
						strTmp = GetIniFileString(_RightTplpListItem->c_str(), "value", "","userright.ini");
						FindNodeValue(ResNode, strTmp.c_str(), strTmpValue);
						
						p_Flex  = new WSVFlexTable((WContainerWidget *)p_ContentTabe1->elementAt(rowcount,0),AlertSel, strTmpValue);
						p_Flex->InitTable();
						
						list<string>   keylist;
						GetIniFileKeys(_RightTplpListItem->c_str(),keylist,"userright.ini");
						int nRightTplIndex;
						nRightTplIndex =1;
						int i = 0;
						for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
						{
							POneRight aPOneRight;
							aPOneRight = new OneRight;
							aPOneRight->strRightText = _aRight->c_str();

							if((aPOneRight->strRightText.compare("value")!=0) && (aPOneRight->strRightText.compare("sort")!=0))
							{
								strTmp = GetIniFileString(_RightTplpListItem->c_str(), _aRight->c_str(), "","userright.ini");
								FindNodeValue(ResNode, strTmp.c_str(), strTmpValue);

								aPOneRight->strShowText = strTmpValue;

								p_Flex->AppendRows();
								aPOneRight->pRightCheckBox = new WCheckBox( aPOneRight->strShowText, (WContainerWidget *)p_Flex->AppendRowsContent(i++, 0, 1,"", "", ""));
			
								aPOneRight->pRightCheckBox->setChecked();

								//添加帮助信息。。。
								m_RightTplList.push_back(aPOneRight);
							}

						}
						//p_Flex->GetContentTable()->hide();
						//p_Flex->ShowHide();
						rowcount++;
					}
				}		
			}		
		}
		CloseResource(objRes);
	}
	//拓扑图权限
	
	WSVFlexTable *p_FlexTop = new WSVFlexTable((WContainerWidget *)p_ContentTabe1->elementAt(rowcount,0), AlertSel, strTuopRight);
	p_FlexTop->InitTable();
	std::list<string> tuopList;
	std::list<string> ::iterator tuopListItem;

	int nRightTopIndex = 1;

	tuopList = GetTopFileList(GetSiteViewRootPath() + "\\htdocs\\tuoplist");
	int i = 0;
	for(tuopListItem = tuopList.begin(); tuopListItem != tuopList.end(); tuopListItem++)
	{
		//
		POneRight aPOneRight;
		aPOneRight = new OneRight;
		aPOneRight->strRightText = (*tuopListItem);
		aPOneRight->strShowText = (*tuopListItem);

		//
		p_FlexTop->AppendRows();
		aPOneRight->pRightCheckBox = new WCheckBox(aPOneRight->strShowText  , (WContainerWidget *)p_FlexTop->AppendRowsContent( i++, 0, 0, "", "", ""));
		aPOneRight->pRightCheckBox->setUnChecked();

		//
		m_RightTplList.push_back(aPOneRight);
	}

	//p_FlexTop->GetContentTable()->hide();
	//需要开放方法
	//p_FlexTop->ShowHide();

	//保存,取消按钮触发
	connect(pUserAddTable->pSave, SIGNAL(clicked()), "showbar();" ,this, SLOT(SaveUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	connect(pUserAddTable->pCancel, SIGNAL(clicked()), "showbar();" ,this, SLOT(CancelUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
}

//
std::list<string>  CUserList::GetTopFileList(string path)
{
	WIN32_FIND_DATA fd;
	std::list<string> strlist;
	path += "\\*.*";
    
	HANDLE fr=::FindFirstFile(path.c_str(),&fd);    
	while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//
		}
        else
		{
			std::string str1 = fd.cFileName;
			int npos = str1.find(".htm", 0);
			if(npos >= 0)
			{				
				strlist.push_back(fd.cFileName);
			}
		}
    }

	return strlist;
}

//显示错误信息
void CUserList::ErrorTest(const string &errorMsg)
{
	p_AddGene->HideAllErrorMsg();

	std::list<string> errorMsgList;
	errorMsgList.push_back(errorMsg);
	p_AddGene->ShowErrorMsg(errorMsgList);
}

//显示编辑用户界面
void CUserList::initEditUserTable(string strIndex,bool bUserType)
{
	/*bAddEdit=false;
	//OutputDebugString("initEditUserTable1");
	initAddUserTable();
	pUserAddTable->show();
	//OutputDebugString("initEditUserTable122");

    string strUserName;
	SVTableRow * pRow = m_svGenUserList.Row(strIndex);
    if(pRow)
    {       
        SVTableCell * pName = pRow->Cell(1);
        if (pName)
        {
            if (pName->Type() == adText)
			{
                 strUserName = ((WText *)pName->Value())->text();
				 pEditUserName->setText(strUserName);
			}
        }

        SVTableCell * pLoginName = pRow->Cell(2);
        if (pLoginName)
        {
            if (pLoginName->Type() == adText)
			{                 
				 pEditLogin->setText(((WText *)pLoginName->Value())->text());
			}
        }

        SVTableCell * pIsUse = pRow->Cell(3);
		if( bUserType==true )
		{
			pCheckDisable->show();
			if (pIsUse)
			{
				if (pIsUse->Type() == adText)
				{
					string strIsUse = ((WText *)pIsUse->Value())->text();
					if(strIsUse == strNameUse)
						pCheckDisable->setChecked();
					else
						pCheckDisable->setUnChecked();				
				}
			}
		}
		else
		{
			pCheckDisable->hide();
		}

		
        SVTableCell * pPwd = pRow->Cell(4);
        if (pPwd)
        {
            if (pPwd->Type() == adText)
			{                 
				pEditPwd->setText(((WText *)pPwd->Value())->text());
				pEditConfirmPwd->setText(((WText *)pPwd->Value())->text());
				
			}
        }

	}	
	//OutputDebugString("initEditUserTable1111");
	pUserAddTable->HideAllErrorMsg();
	//OutputDebugString("initEditUserTable133");
	if(bShowRight)
	{
		pRightTable->show();
		//OutputDebugString("initEditUserTable155");
		//pSubTreeTable->show();
		//pUserScrollArea->show();
		for(m_RightTplListItem = m_RightTplList.begin(); m_RightTplListItem != m_RightTplList.end(); m_RightTplListItem ++)
		{
			OneRight* right = (POneRight) *m_RightTplListItem;
			int nCheck = GetIniFileInt(strIndex, right->strRightText.c_str(), -1, "user.ini");
			if(nCheck != -1)
				right->pRightCheckBox->setChecked();
			else
				right->pRightCheckBox->setUnChecked();
		}		
	}
	else
	{
		pRightTable->hide();
		//OutputDebugString("initEditUserTable155");
		//pSubTreeTable->hide();
	//	pUserScrollArea->hide();
	}
	
	//OutputDebugString("initEditUserTable222");
	
	pGroupTree->InitTree("",true,true,false,"1");

	setGroupRightCheck(strIndex);
	*/


	bAddEdit=false;
	string strUserName, strLoginName, strIsUse, strPwd;
	int nIsUse, nAdmin = -1;
	//OutputDebugString("initEditUserTable1");
	initAddUserTable();
	pUserAddTable->show();
	//OutputDebugString("initEditUserTable122");
	
	//读取文件
	strIndex = GetIniFileString(strIndex, "nIndex", "", "user.ini");

	nIsUse = GetIniFileInt(strIndex, "nIsUse", -1, "user.ini");

	strUserName = GetIniFileString(strIndex, "UserName", "" , "user.ini");

	strLoginName = GetIniFileString(strIndex, "LoginName", "", "user.ini");

	strPwd = GetIniFileString(strIndex, "Password", "", "user.ini");

	nAdmin = GetIniFileInt(strIndex, "nAdmin", -1, "user.ini");

	pEditUserName->setText(strUserName);
	pEditLogin->setText(strLoginName);

	if( bUserType==true )
	{
	if(nIsUse == -1)
		pCheckDisable->setChecked();
	else
		pCheckDisable->setUnChecked();	
	}
	else
	{
		pCheckDisable->hide();
	}
	std::string pwd(strPwd);
	Des mydes;
	char enchar[1024]={0};
	if(pwd.size()>0)
	{
		mydes.Decrypt(pwd.c_str(),enchar);
		pwd = enchar;
	}
	pEditPwd->setText(pwd);
	pEditConfirmPwd->setText(pwd);

	if(bShowRight)
	{
		for(m_RightTplListItem = m_RightTplList.begin(); m_RightTplListItem != m_RightTplList.end(); m_RightTplListItem ++)
		{
			OneRight* right = (POneRight) *m_RightTplListItem;
			int nCheck = GetIniFileInt(strIndex, right->strRightText.c_str(), -1, "user.ini");
			if(nCheck != -1)
				right->pRightCheckBox->setChecked();
			else
				right->pRightCheckBox->setUnChecked();
		}		
	}
	else
	{
		pRightTable->hide();
	}
	//OutputDebugString("initEditUserTable222");

	pGroupTree->InitTree("",true,true,false,"1");

	setGroupRightCheck(strIndex);
}
//新增普通用户列表
void CUserList::AddGenUser(string strIndex, string strUserName, string strLoginName, string strPwd, string strIsUse)
{
	//生成界面
	int numRow = pUserListTable->numRows();
	
	//选择
	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)pUserListTable->elementAt(numRow, 0));
	
	//文本
	WText * pUserNameText = new WText(strUserName, (WContainerWidget*)pUserListTable->elementAt(numRow , 1));
	WText * pLoginNameText = new WText(strLoginName, (WContainerWidget*)pUserListTable->elementAt(numRow , 2));
	WText * pIsUseText = new WText(strIsUse, (WContainerWidget*)pUserListTable->elementAt(numRow , 3));				
	
	WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)pUserListTable->elementAt(numRow , 4));
	pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	m_genMapper.setMapping(pEdit, strIndex); 
	connect(pEdit, SIGNAL(clicked()), "showbar();" ,&m_genMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	
	WText * pPwdText = new WText(strPwd, (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 5));
	pPwdText->hide();

	pUserListTable->adjustRowStyle("tr1","tr2"); 

	//组织数据到内存列表中
	SVTableCell ce;
	ce.setType(adCheckBox);
	ce.setValue(pCheck);
	m_svGenUserList.WriteCell(strIndex, 0, ce);

	ce.setType(adText);
	ce.setValue(pUserNameText);
	m_svGenUserList.WriteCell(strIndex, 1, ce);

	ce.setType(adText);
	ce.setValue(pLoginNameText);
	m_svGenUserList.WriteCell(strIndex, 2, ce);

	ce.setType(adText);
	ce.setValue(pIsUseText);
	m_svGenUserList.WriteCell(strIndex, 3, ce);

	ce.setType(adText);
	ce.setValue(pPwdText);
	m_svGenUserList.WriteCell(strIndex, 4, ce);	
}

//新增Admin用户列表
void CUserList::AddAdminUser(string strIndex, string strUserName, string strLoginName, string strPwd, string strIsUse)
{
	int numRow = pAdminUserListTable->numRows();

	//new WText(" ", (WContainerWidget*)pAdminUserListTable->elementAt(numRow, 0));

	//文本
	WText * pUserNameText = new WText(strUserName, (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 1));
	WText * pLoginNameText = new WText(strLoginName, (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 2));
//	WText * pIsUseText = new WText(strIsUse, (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 3));
	
	WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 4));
	pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	m_adMapper.setMapping(pEdit, strIndex); 
	connect(pEdit, SIGNAL(clicked()), "showbar();", &m_adMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	
	WText * pPwdText = new WText(strPwd, (WContainerWidget*)pAdminUserListTable->elementAt(numRow , 5));
	pPwdText->hide();

	//组织数据到内存列表中
	SVTableCell ce;

	//string strAdmin = "admin";
	//ce.setType(adString);
	//ce.setValue((void*)(strAdmin.c_str()));
	//m_svGenUserList.WriteCell(strIndex, 0, ce);

	ce.setType(adText);
	ce.setValue(pUserNameText);
	m_svGenUserList.WriteCell(strIndex, 1, ce);

	ce.setType(adText);
	ce.setValue(pLoginNameText);
	m_svGenUserList.WriteCell(strIndex, 2, ce);

/*	ce.setType(adText);
	ce.setValue(pIsUseText);
	m_svGenUserList.WriteCell(strIndex, 3, ce);
*/
	ce.setType(adText);
	ce.setValue(pPwdText);
	m_svGenUserList.WriteCell(strIndex, 4, ce);
}


//修改普通用户列表
void CUserList::EditGenUser(string strIndex, string strUserName, string strLoginName, string strPwd, string strIsUse)
{
	SVTableRow * pRow = m_svGenUserList.Row(strIndex);
    if(pRow)
    {       
        SVTableCell * pName = pRow->Cell(1);
        if (pName)
        {
            if (pName->Type() == adText)
			{
                 ((WText *)pName->Value())->setText(strUserName);				 
			}
        }

        SVTableCell * pLoginName = pRow->Cell(2);
        if (pLoginName)
        {
            if (pLoginName->Type() == adText)
			{
				((WText *)pLoginName->Value())->setText(strLoginName);				 
			}
        }

        SVTableCell * pIsUse = pRow->Cell(3);
        if (pIsUse)
        {
            if (pIsUse->Type() == adText)
			{
				((WText *)pIsUse->Value())->setText(strIsUse);
			}
        }
		
        SVTableCell * pPwd = pRow->Cell(4);
        if (pPwd)
        {
            if (pPwd->Type() == adText)
			{
				((WText *)pPwd->Value())->setText(strPwd);
				//pPwd->setValue(&strPwd);
			}
        }
	}	
}


//选择全部按钮响应
void CUserList::SelAll()
{
    /*for(row it = m_svGenUserList.begin(); it != m_svGenUserList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
            // 修改每一项的选择状态
			if (pcell->Type() == adCheckBox)
            {
                ((WCheckBox*)pcell->Value())->setChecked(true);
            }
        }
    }*/
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(true);
	}
}


//全部不选择按钮响应
void CUserList::SelNone()
{
    /*for(row it = m_svGenUserList.begin(); it != m_svGenUserList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
            // 修改每一项的选择状态
			if (pcell->Type() == adCheckBox)
            {
                ((WCheckBox*)pcell->Value())->setChecked(false);
            }
        }
    }*/
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(false);
	}
}


//反选按钮响应
void CUserList::SelInvert()
{
   /* for(row it = m_svGenUserList.begin(); it != m_svGenUserList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
             // 修改每一项的选择状态
			if (pcell->Type() == adCheckBox)
            {
                if(((WCheckBox*)pcell->Value())->isChecked())
					((WCheckBox*)pcell->Value())->setChecked(false);
				else				
					((WCheckBox*)pcell->Value())->setChecked(true);
            }
        }
    }*/

	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		if(m_pListItem->pSelect->isChecked())
		{
			m_pListItem->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem->pSelect->setChecked(true);
		}
	}
}
//界面刷新
void CUserList::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserRight";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//更新列表
	
	//清空列表
	//p_UserTable->GeDataTable()->clear();
	delete p_UserTable;
	p_UserTable = NULL;
	//p_AdminUserTable->GeDataTable()->clear();
	delete p_AdminUserTable;
	p_AdminUserTable = NULL;
	m_pListUSER.clear();
	initUserTable();
	initAdminUserTable();

	/*int nNum = pUserListTable->numRows();
	for(int i = 1;i < nNum; i++)
	{
		pUserListTable->deleteRow(1);
	}

	nNum = pAdminUserListTable->numRows();
	for(int i = 1; i < nNum; i++)
	{
		pAdminUserListTable->deleteRow(1);
	}
	
	m_svGenUserList.clear();

	//重新读数据
	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName, strLoginName, strIsUse, strPwd, strIndex;
	int nIsUse, nAdmin = -1;
	
	//从ini获取用户列表
	if(GetIniFileSections(keylist, "user.ini"))
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据
			strIndex = GetIniFileString((*keyitem), "nIndex", "", "user.ini");

			nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, "user.ini");
			if(nIsUse == -1)
				strIsUse = strNameUse;
			else
				strIsUse = strEnable;

			strUserName = GetIniFileString((*keyitem), "UserName", "" , "user.ini");
			
			strLoginName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");
			
			strPwd = GetIniFileString((*keyitem), "Password", "", "user.ini");
			
			Des mydes;
			char dechar[1024]={0};
			if(strPwd.size()>0)
			{
				mydes.Decrypt(strPwd.c_str(),dechar);
				strPwd= dechar;
			}


			nAdmin = GetIniFileInt((*keyitem), "nAdmin", -1, "user.ini");

			if(nAdmin == -1)
				AddGenUser(strIndex, strUserName, strLoginName, strPwd, strIsUse);
			else
				AddAdminUser(strIndex, strUserName, strLoginName, strPwd, strIsUse);
		}
	}

	if(m_svGenUserList.RowCount() <= 1)
	{
		WText * m_pNullText = new WText(szNoGenUserItem, (WContainerWidget*)pUserListTable->elementAt(1 , 2));
		m_pNullText->decorationStyle().setForegroundColor(Wt::red);
	}

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pMainTable->pTranslateBtn->show();
		connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pMainTable->pExChangeBtn->show();
		connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));
		if(pUserAddTable)
		{
			pUserAddTable->pTranslateBtn->show();
			connect(pUserAddTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

			pUserAddTable->pExChangeBtn->show();
			connect(pUserAddTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
		}
	}
	else
	{
		pMainTable->pTranslateBtn->hide();
		pMainTable->pExChangeBtn->hide();
		if(pUserAddTable)
		{
			pUserAddTable->pTranslateBtn->hide();
			pUserAddTable->pExChangeBtn->hide();
		}
	}*/

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}
//
void CUserList::MakeTreeNodeFuncRight(WTreeNode *pNode,ScopeFuncMap & pScopeFuncList)
{
	PScopeFunc pSF;
	pSF = new ScopeFunc;
	pSF->strScopeId= pNode->strId;
	for(TreeNodeRightMap::iterator i= pNode->m_TreeNodeRightMap.begin();i!=pNode->m_TreeNodeRightMap.end();i++)
	{
		//char aaaa[2000];
		//sprintf(aaaa,"MakeTreeNodeFuncRight:   %s=%d\n",i->first.c_str(),i->second);
		//OutputDebugString(aaaa);
		pSF->m_ScopeRightMap[i->first]= i->second;
		
		
	}
	if(pSF->m_ScopeRightMap.size()>0)
	//pScopeFuncList.   push_back(pSF);
	pScopeFuncList[pSF->strScopeId]=pSF;
	
	
}
//从界面获取依赖列表
void CUserList::GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_,std::list<string > & pUnGroupRightList_  ,ScopeFuncMap & pScopeFuncList,	bool bParentCheck_)
{
	bool bParentCheck;
	bParentCheck = bParentCheck_;
	
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			if(pNode->treeCheckBox_->isChecked())
			{
				pGroupRightList_.push_back(pNode->strId);


				MakeTreeNodeFuncRight(pNode,pScopeFuncList);

				if(bParentCheck== false)
						bParentCheck = true;

				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_,pScopeFuncList ,bParentCheck);

			}else{
				if(bParentCheck== true)
					pUnGroupRightList_.push_back(pNode->strId);
				
				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_,pScopeFuncList,  bParentCheck);
			}

		}else{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_ ,pScopeFuncList,bParentCheck);
		}
	}
	return;

}
//获取选中的节点列表到变量
void CUserList::GetGroupRightList(CUser* pCurUser )
{
	pGroupRightList.clear();
	pUnGroupRightList.clear();
	pCurUser->ClearScopeFuncList();

	if(pGroupTree->treeroot!=NULL)
	{
		GetGroupChecked(pGroupTree->treeroot,pGroupRightList ,pUnGroupRightList,pCurUser->m_ScopeFuncmap,false );

	}

}
//
void CUserList::SetNodeRightMap(WTreeNode*pNode, CUser *pUser)
{
	PScopeFunc aScopeFunc;
	if(pUser->m_ScopeFuncmap.find(pNode->strId)!=pUser->m_ScopeFuncmap.end())
	{//find it ok
		//OutputDebugString("find it \n");
		aScopeFunc =pUser->m_ScopeFuncmap.find(pNode->strId)->second;
		for(ScopeRightMap::iterator it =aScopeFunc->m_ScopeRightMap.begin();it!=aScopeFunc->m_ScopeRightMap.end();it++)
		{
			bool bCheck;
			bCheck =it->second;
			pNode->m_TreeNodeRightMap[it->first]=bCheck;
			/*
			if(pNode->strId.compare("1.11")==0)
			{
			char aaa[300];
			sprintf(aaa,"%s %s  %d\n",pNode->strId.c_str(),it->first.c_str(),pNode->m_TreeNodeRightMap.find(it->first)->second);
			OutputDebugString(aaa);
			}*/

		}
		
	}
	
	
}
//根据指定字符串初始化树的CheckBox
void CUserList::SetGroupChecked(WTreeNode*pNode,  std::string  pGroupRightList_   ,CUser *pUser)
{
	std::string  strSelId;
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			strSelId=","+ pNode->strId+",";

			int iPos=pGroupRightList_.find(strSelId);
			if(iPos>=0)
			{
				/*
				
				char abc[200];
				sprintf(abc,"  %s--%s --%d \n",pGroupRightList_.c_str(),
					strSelId.c_str(),iPos);
				OutputDebugString(abc);
				*/
				pNode->treeCheckBox_->setChecked();
				SetNodeRightMap(pNode,pUser);

				//find(pUser->m_ScopeFunclist.begin(),
			}
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					SetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUser);
			
		}
		else
		{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					SetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUser);
		}
	}
	return;

}
//根据用户串初始化数的CheckBox
void CUserList::setGroupRightCheck(std::string strIndex)
{

	std::string groupright= GetIniFileString(strIndex, "groupright", "", "user.ini");
	CUser *pCurUser = new CUser(strIndex);
	pCurUser->MakeGroupFunc();

	if(pGroupTree->treeroot!=NULL)
        	SetGroupChecked(pGroupTree->treeroot,groupright,pCurUser);

}

//
void CUserList::ShowHelp()
{
	OutputDebugString("------showhelp()--------------");
	p_AddGene->ShowOrHideHelp();	
}
//

void CUserList::InitRightTableFromRes(WTable * pRightTable)
{
	string strMySiteView,strDummyGroup,strMonitor,strOverallView,strTreeView,strTuop,strTuop1;
	string strAlert,strAddAlert,strDeleteAlert,strEditAlert,strAlertLog,strReport,strTrendReport;
	string strMonitorReport,strAddReport,strDeleteReport,strEditReport,strTopnReport,strSetting,strFounditionSet;
	string strUserManager,strEmailSet,strSMSSet,strSEServer,strAddSEServer,strDeleteSEServer,strEditSEServer;
	string strManagerGroup,strEditGroup,strDeleteGroup,strAddSubGroup,strAddDevice,strRefresh,strManagerDevice;
	string strEditDevice,strDeleteDevice,strCopyDevice,strManagerMonitor,strAddMonitor,strEditMonitor,strDeleteMonitor;

	//FindNodeValue(ResNode,"IDS_Right_My_SiteView",strMySiteView);
	//FindNodeValue(ResNode,"IDS_Right_DummyGroup",strDummyGroup);
	//FindNodeValue(ResNode,"IDS_Right_Monitor",strMonitor);
	//FindNodeValue(ResNode,"IDS_Right_OverallView",strOverallView);
	//FindNodeValue(ResNode,"IDS_Right_TreeView",strTreeView);
	//FindNodeValue(ResNode,"IDS_Right_Tuop",strTuop);
	//FindNodeValue(ResNode,"IDS_Right_Tuop",strTuop1);
	//FindNodeValue(ResNode,"IDS_Right_Alert",strAlert);
	//FindNodeValue(ResNode,"IDS_Right_AddAlert",strAddAlert);
	//FindNodeValue(ResNode,"IDS_Right_DeleteAlert",strDeleteAlert);
	//FindNodeValue(ResNode,"IDS_Right_EditAlert",strEditAlert);
	//FindNodeValue(ResNode,"IDS_Right_AlertLog",strAlertLog);
	//FindNodeValue(ResNode,"IDS_Right_Report",strReport);
	//FindNodeValue(ResNode,"IDS_Right_TrendReport",strTrendReport);
	//FindNodeValue(ResNode,"IDS_Right_MonitorReport",strMonitorReport);
	//FindNodeValue(ResNode,"IDS_Right_AddReport",strAddReport);
	//FindNodeValue(ResNode,"IDS_Right_DeleteReport",strDeleteReport);
	//FindNodeValue(ResNode,"IDS_Right_EditReport",strEditReport);
	//FindNodeValue(ResNode,"IDS_Right_TopnReport",strTopnReport);
	//FindNodeValue(ResNode,"IDS_Right_Setting",strSetting);
	//FindNodeValue(ResNode,"IDS_Right_FounditionSet",strFounditionSet);
	//FindNodeValue(ResNode,"IDS_Right_UserManager",strUserManager);
	//FindNodeValue(ResNode,"IDS_Right_EmailSet",strEmailSet);
	//FindNodeValue(ResNode,"IDS_Right_SMSSet",strSMSSet);
	//FindNodeValue(ResNode,"IDS_Right_SEServer",strSEServer);
	//FindNodeValue(ResNode,"IDS_Right_AddSEServer",strAddSEServer);
	//FindNodeValue(ResNode,"IDS_Right_DeleteSEServer",strDeleteSEServer);
	//FindNodeValue(ResNode,"IDS_Right_EditSEServer",strEditSEServer);
	//FindNodeValue(ResNode,"IDS_Right_ManagerGroup",strManagerGroup);
	//FindNodeValue(ResNode,"IDS_Right_EditGroup",strEditGroup);
	//FindNodeValue(ResNode,"IDS_Right_DeleteGroup",strDeleteGroup);
	//FindNodeValue(ResNode,"IDS_Right_AddSubGroup",strAddSubGroup);
	//FindNodeValue(ResNode,"IDS_Right_AddDevice",strAddDevice);
	//FindNodeValue(ResNode,"IDS_Right_Refresh",strRefresh);
	//FindNodeValue(ResNode,"IDS_Right_ManagerDevice",strManagerDevice);
	//FindNodeValue(ResNode,"IDS_Right_AddDevice",strAddDevice);
	//FindNodeValue(ResNode,"IDS_Right_EditDevice",strEditDevice);
	//FindNodeValue(ResNode,"IDS_Right_DeleteDevice",strDeleteDevice);
	//FindNodeValue(ResNode,"IDS_Right_CopyDevice",strCopyDevice);
	//FindNodeValue(ResNode,"IDS_Right_ManagerMonitor",strManagerMonitor);
	//FindNodeValue(ResNode,"IDS_Right_AddMonitor",strAddMonitor);
	//FindNodeValue(ResNode,"IDS_Right_EditMonitor",strEditMonitor);
	//FindNodeValue(ResNode,"IDS_Right_DeleteMonitor",strDeleteMonitor);

	//设备
	CFlexTable *pFlex;
	POneRight aPOneRight;

	//监测 strMonitor m_allview strOverallView m_tree strTreeView
	pFlex = new CFlexTable(pRightTable->elementAt(1, 0), strMySiteView);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_allview";
	aPOneRight->strShowText = strOverallView;
	aPOneRight->pRightCheckBox = new WCheckBox(strOverallView, pFlex->GetContentTable()->elementAt(1, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_tree";
	aPOneRight->strShowText = strTreeView;
	aPOneRight->pRightCheckBox = new WCheckBox(strTreeView, pFlex->GetContentTable()->elementAt(2, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	pFlex->HideTable();

	//拓扑视图 strTuop m_tuop strTuop1
	pFlex = new CFlexTable(pRightTable->elementAt(2, 0), strTuop);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_allview";
	aPOneRight->strShowText = strOverallView;
	aPOneRight->pRightCheckBox = new WCheckBox(strOverallView, pFlex->GetContentTable()->elementAt(1, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	pFlex->HideTable();

	//报警 strAlert m_AlertRuleAdd strAddAlert m_AlertRuleDel strDeleteAlert m_AlertRuleEdit strEditAlert m_alertLogs strAlertLog
	pFlex = new CFlexTable(pRightTable->elementAt(3, 0), strAlert);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_AlertRuleAdd";
	aPOneRight->strShowText = strAddAlert;
	aPOneRight->pRightCheckBox = new WCheckBox(strAddAlert, pFlex->GetContentTable()->elementAt(1, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_AlertRuleDel";
	aPOneRight->strShowText = strDeleteAlert;
	aPOneRight->pRightCheckBox = new WCheckBox(strDeleteAlert, pFlex->GetContentTable()->elementAt(2, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_AlertRuleEdit";
	aPOneRight->strShowText = strEditAlert;
	aPOneRight->pRightCheckBox = new WCheckBox(strEditAlert, pFlex->GetContentTable()->elementAt(3, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_alertLogs";
	aPOneRight->strShowText = strAlertLog;
	aPOneRight->pRightCheckBox = new WCheckBox(strAlertLog, pFlex->GetContentTable()->elementAt(4, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	pFlex->HideTable();

	//报表 strReport m_SetshowSystemReport strTrendReport m_logshower strMonitorReport m_reportlistAdd strAddReport m_reportlistDel strDeleteReport
	pFlex = new CFlexTable(pRightTable->elementAt(4, 0), strReport);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_SetshowSystemReport";
	aPOneRight->strShowText = strTrendReport;
	aPOneRight->pRightCheckBox = new WCheckBox(strTrendReport, pFlex->GetContentTable()->elementAt(1, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_logshower";
	aPOneRight->strShowText = strMonitorReport;
	aPOneRight->pRightCheckBox = new WCheckBox(strMonitorReport, pFlex->GetContentTable()->elementAt(2, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_reportlistAdd";
	aPOneRight->strShowText = strAddReport;
	aPOneRight->pRightCheckBox = new WCheckBox(strAddReport, pFlex->GetContentTable()->elementAt(3, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_reportlistDel";
	aPOneRight->strShowText = strDeleteReport;
	aPOneRight->pRightCheckBox = new WCheckBox(strDeleteReport, pFlex->GetContentTable()->elementAt(4, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	pFlex->HideTable();

	//设置 strSetting m_general strFounditionSet m_mailsetting strEmailSet m_smssetting strSMSSet
	pFlex = new CFlexTable(pRightTable->elementAt(5, 0), strSetting);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_general";
	aPOneRight->strShowText = strFounditionSet;
	aPOneRight->pRightCheckBox = new WCheckBox(strFounditionSet, pFlex->GetContentTable()->elementAt(1, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_mailsetting";
	aPOneRight->strShowText = strEmailSet;
	aPOneRight->pRightCheckBox = new WCheckBox(strEmailSet, pFlex->GetContentTable()->elementAt(2, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	aPOneRight = new OneRight;
	aPOneRight->strRightText = "m_smssetting";
	aPOneRight->strShowText = strSMSSet;
	aPOneRight->pRightCheckBox = new WCheckBox(strSMSSet, pFlex->GetContentTable()->elementAt(3, 0));
	aPOneRight->pRightCheckBox->setChecked();
	m_RightTplList.push_back(aPOneRight);

	pFlex->HideTable();

	//拓扑图权限

}

void AddJsParam(const std::string name, const std::string value, WContainerWidget *parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}

//写权限模板
void WriteRightTpl()
{
	string strMySiteView,strDummyGroup,strMonitor,strOverallView,strTreeView,strTuop,strTuop1;
	string strAlert,strAddAlert,strDeleteAlert,strEditAlert,strAlertLog,strReport,strTrendReport;
	string strMonitorReport,strAddReport,strDeleteReport,strEditReport,strTopnReport,strSetting,strFounditionSet;
	string strUserManager,strEmailSet,strSMSSet,strSEServer,strAddSEServer,strDeleteSEServer,strEditSEServer;
	string strManagerGroup,strEditGroup,strDeleteGroup,strAddSubGroup,strAddDevice,strRefresh,strManagerDevice;
	string strEditDevice,strDeleteDevice,strCopyDevice,strManagerMonitor,strAddMonitor,strEditMonitor,strDeleteMonitor;
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Right_My_SiteView",strMySiteView);
			FindNodeValue(ResNode,"IDS_Right_DummyGroup",strDummyGroup);
			FindNodeValue(ResNode,"IDS_Right_Monitor",strMonitor);
			FindNodeValue(ResNode,"IDS_Right_OverallView",strOverallView);
			FindNodeValue(ResNode,"IDS_Right_TreeView",strTreeView);
			FindNodeValue(ResNode,"IDS_Right_Tuop",strTuop);
			FindNodeValue(ResNode,"IDS_Right_Tuop",strTuop1);
			FindNodeValue(ResNode,"IDS_Right_Alert",strAlert);
			FindNodeValue(ResNode,"IDS_Right_AddAlert",strAddAlert);
			FindNodeValue(ResNode,"IDS_Right_DeleteAlert",strDeleteAlert);
			FindNodeValue(ResNode,"IDS_Right_EditAlert",strEditAlert);
			FindNodeValue(ResNode,"IDS_Right_AlertLog",strAlertLog);
			FindNodeValue(ResNode,"IDS_Right_Report",strReport);
			FindNodeValue(ResNode,"IDS_Right_TrendReport",strTrendReport);
			FindNodeValue(ResNode,"IDS_Right_MonitorReport",strMonitorReport);
			FindNodeValue(ResNode,"IDS_Right_AddReport",strAddReport);
			FindNodeValue(ResNode,"IDS_Right_DeleteReport",strDeleteReport);
			FindNodeValue(ResNode,"IDS_Right_EditReport",strEditReport);
			FindNodeValue(ResNode,"IDS_Right_TopnReport",strTopnReport);
			FindNodeValue(ResNode,"IDS_Right_Setting",strSetting);
			FindNodeValue(ResNode,"IDS_Right_FounditionSet",strFounditionSet);
			FindNodeValue(ResNode,"IDS_Right_UserManager",strUserManager);
			FindNodeValue(ResNode,"IDS_Right_EmailSet",strEmailSet);
			FindNodeValue(ResNode,"IDS_Right_SMSSet",strSMSSet);
			FindNodeValue(ResNode,"IDS_Right_SEServer",strSEServer);
			FindNodeValue(ResNode,"IDS_Right_AddSEServer",strAddSEServer);
			FindNodeValue(ResNode,"IDS_Right_DeleteSEServer",strDeleteSEServer);
			FindNodeValue(ResNode,"IDS_Right_EditSEServer",strEditSEServer);
			FindNodeValue(ResNode,"IDS_Right_ManagerGroup",strManagerGroup);
			FindNodeValue(ResNode,"IDS_Right_EditGroup",strEditGroup);
			FindNodeValue(ResNode,"IDS_Right_DeleteGroup",strDeleteGroup);
			FindNodeValue(ResNode,"IDS_Right_AddSubGroup",strAddSubGroup);
			FindNodeValue(ResNode,"IDS_Right_AddDevice",strAddDevice);
			FindNodeValue(ResNode,"IDS_Right_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Right_ManagerDevice",strManagerDevice);
			FindNodeValue(ResNode,"IDS_Right_AddDevice",strAddDevice);
			FindNodeValue(ResNode,"IDS_Right_EditDevice",strEditDevice);
			FindNodeValue(ResNode,"IDS_Right_DeleteDevice",strDeleteDevice);
			FindNodeValue(ResNode,"IDS_Right_CopyDevice",strCopyDevice);
			FindNodeValue(ResNode,"IDS_Right_ManagerMonitor",strManagerMonitor);
			FindNodeValue(ResNode,"IDS_Right_AddMonitor",strAddMonitor);
			FindNodeValue(ResNode,"IDS_Right_EditMonitor",strEditMonitor);
			FindNodeValue(ResNode,"IDS_Right_DeleteMonitor",strDeleteMonitor);
		}
		CloseResource(objRes);
	}

	////我的siteview
	//WriteIniFileString("m_homePage","value",  strMySiteView , "userright.ini");
	//WriteIniFileString("m_homePage","m_favorite",strDummyGroup,"userright.ini");
	//WriteIniFileInt("m_homePage","sort",9,"userright.ini");
	//
	////监测
	//WriteIniFileString("m_Monitor","value" , strMonitor , "userright.ini");
	//WriteIniFileString("m_Monitor","m_allview",strOverallView,"userright.ini");
	//WriteIniFileString("m_Monitor","m_tree",strTreeView,"userright.ini");
	//WriteIniFileInt("m_Monitor","sort",1,"userright.ini");
	//
	////拓扑视图
	//WriteIniFileString("topoview","value"  ,strTuop , "userright.ini");
	//WriteIniFileString("topoview","m_tuop",strTuop1,"userright.ini");
	//WriteIniFileInt("topoview","sort",2,"userright.ini");
	//
	////报警
	//WriteIniFileString("m_service","value" , strAlert , "userright.ini");
	//WriteIniFileString("m_service","m_AlertRuleAdd",strAddAlert,"userright.ini");
	//WriteIniFileString("m_service","m_AlertRuleDel",strDeleteAlert,"userright.ini");
	//WriteIniFileString("m_service","m_AlertRuleEdit",strEditAlert,"userright.ini");
	//WriteIniFileString("m_service","m_alertLogs",strAlertLog,"userright.ini");
	//WriteIniFileInt("m_service","sort",3,"userright.ini");
	//
	////报表
	//WriteIniFileString("m_report","value" , strReport , "userright.ini");
	//WriteIniFileString("m_report","m_SetshowSystemReport",strTrendReport,"userright.ini");
	//WriteIniFileString("m_report","m_logshower",strMonitorReport,"userright.ini");
	//WriteIniFileString("m_report","m_reportlistAdd",strAddReport,"userright.ini");
	//WriteIniFileString("m_report","m_reportlistDel",strDeleteReport,"userright.ini");
	//WriteIniFileString("m_report","m_reportlistEdit",strEditReport,"userright.ini");
	//WriteIniFileString("m_report","m_topnadd",strTopnReport,"userright.ini");
	//WriteIniFileInt("m_report","sort",4,"userright.ini");
	//
	////设置
	//WriteIniFileString("m_setting","value" , strSetting , "userright.ini");
	//WriteIniFileString("m_setting","m_general",strFounditionSet,"userright.ini");
	////WriteIniFileString("m_setting","m_UserAdmin","用户管理","userright.ini");
	//WriteIniFileString("m_setting","m_mailsetting",strEmailSet,"userright.ini");
	//WriteIniFileString("m_setting","m_smssetting",strSMSSet,"userright.ini");	
	//WriteIniFileInt("m_setting","sort",5,"userright.ini");

	////管理SE服务器
	// WriteIniFileString("seserver","value" , strSEServer , "userright.ini");
	// WriteIniFileString("seserver","se_addse" , strAddSEServer ,"userright.ini");
	// WriteIniFileString("seserver","se_delse" , strDeleteSEServer ,	"userright.ini");
	// WriteIniFileString("seserver","se_edit" , strEditSEServer ,	"userright.ini");
	// WriteIniFileInt("seserver","sort",6,"userright.ini");

	// //管理组
	// WriteIniFileString("group","value" , strManagerGroup , "userright.ini");
	// WriteIniFileString("group","editgroup",strEditGroup,"userright.ini");
	// WriteIniFileString("group","delgroup",strDeleteGroup,"userright.ini");
	// WriteIniFileString("group","addsongroup",strAddSubGroup,"userright.ini");
	// //WriteIniFileString("group","addsondevice","添加设备","userright.ini");
	// WriteIniFileString("group","grouprefresh",strRefresh,"userright.ini");
	// WriteIniFileInt("group","sort",7,"userright.ini");

	// //管理应用设备
	// WriteIniFileString("device","value" , strManagerDevice , "userright.ini");
	// WriteIniFileString("device","adddevice",strAddDevice,"userright.ini");
	// WriteIniFileString("device","editdevice",strEditDevice,"userright.ini");
	// WriteIniFileString("device","deldevice" , strDeleteDevice ,"userright.ini");
	// WriteIniFileString("device","copydevice",strCopyDevice,"userright.ini");
	// WriteIniFileString("device","devicerefresh",strRefresh,"userright.ini");
	// WriteIniFileInt("device","sort",8,"userright.ini");

	// //管理监测器
	// WriteIniFileString("monitor","value" , strManagerMonitor , "userright.ini");
	// WriteIniFileString("monitor","addmonitor",strAddMonitor,"userright.ini");
	// WriteIniFileString("monitor","editmonitor",strEditMonitor,"userright.ini");
	// WriteIniFileString("monitor","delmonitor" , strDeleteMonitor ,"userright.ini");
	// WriteIniFileString("monitor","monitorrefresh",strRefresh,"userright.ini");
	// WriteIniFileInt("monitor","sort",9,"userright.ini"); 

	
	//我的siteview
	WriteIniFileString("m_homePage","value",  "IDS_Right_My_SiteView" , "userright.ini");
	WriteIniFileString("m_homePage","m_favorite","IDS_Right_DummyGroup","userright.ini");
	WriteIniFileInt("m_homePage","sort",9,"userright.ini");
	
	//监测
	WriteIniFileString("m_Monitor","value" , "IDS_Right_Monitor" , "userright.ini");
	WriteIniFileString("m_Monitor","m_allview","IDS_Right_OverallView","userright.ini");
	WriteIniFileString("m_Monitor","m_tree","IDS_Right_TreeView","userright.ini");
	WriteIniFileInt("m_Monitor","sort",1,"userright.ini");
	
	//拓扑视图
	WriteIniFileString("topoview","value"  ,"IDS_Right_Tuop" , "userright.ini");
	WriteIniFileString("topoview","m_tuop","IDS_Right_Tuop","userright.ini");
	WriteIniFileInt("topoview","sort",2,"userright.ini");
	
	//报警
	WriteIniFileString("m_service","value" , "IDS_Right_Alert" , "userright.ini");
	WriteIniFileString("m_service","m_AlertRuleAdd","IDS_Right_AddAlert","userright.ini");
	WriteIniFileString("m_service","m_AlertRuleDel","IDS_Right_DeleteAlert","userright.ini");
	WriteIniFileString("m_service","m_AlertRuleEdit","IDS_Right_EditAlert","userright.ini");
	WriteIniFileString("m_service","m_alertLogs","IDS_Right_AlertLog","userright.ini");
	WriteIniFileInt("m_service","sort",3,"userright.ini");
	
	//报表
	WriteIniFileString("m_report","value" , "IDS_Right_Report" , "userright.ini");
	WriteIniFileString("m_report","m_SetshowSystemReport","IDS_Right_TrendReport","userright.ini");
	WriteIniFileString("m_report","m_logshower","IDS_Right_MonitorReport","userright.ini");
	WriteIniFileString("m_report","m_reportlistAdd","IDS_Right_AddReport","userright.ini");
	WriteIniFileString("m_report","m_reportlistDel","IDS_Right_DeleteReport","userright.ini");
	WriteIniFileString("m_report","m_reportlistEdit","IDS_Right_EditReport","userright.ini");
	WriteIniFileString("m_report","m_topnadd","IDS_Right_TopnReport","userright.ini");
	WriteIniFileInt("m_report","sort",4,"userright.ini");
	
	//设置
	WriteIniFileString("m_setting","value" , "IDS_Right_Setting" , "userright.ini");
	WriteIniFileString("m_setting","m_general","IDS_Right_FounditionSet","userright.ini");
	WriteIniFileString("m_setting","m_mailsetting","IDS_Right_EmailSet","userright.ini");
	WriteIniFileString("m_setting","m_smssetting","IDS_Right_SMSSet","userright.ini");	
	WriteIniFileInt("m_setting","sort",5,"userright.ini");

	//管理SE服务器
	 WriteIniFileString("seserver","value" , "IDS_Right_SEServer" , "userright.ini");
	 WriteIniFileString("seserver","se_addse" , "IDS_Right_AddSEServer" ,"userright.ini");
	 WriteIniFileString("seserver","se_delse" , "IDS_Right_DeleteSEServer" ,	"userright.ini");
	 WriteIniFileString("seserver","se_edit" , "IDS_Right_EditSEServer" ,	"userright.ini");
	 WriteIniFileInt("seserver","sort",6,"userright.ini");

	 //管理组
	 WriteIniFileString("group","value" , "IDS_Right_ManagerGroup" , "userright.ini");
	 WriteIniFileString("group","editgroup","IDS_Right_EditGroup","userright.ini");
	 WriteIniFileString("group","delgroup","IDS_Right_DeleteGroup","userright.ini");
	 WriteIniFileString("group","addsongroup","IDS_Right_AddSubGroup","userright.ini");
	 WriteIniFileString("group","grouprefresh","IDS_Right_Refresh","userright.ini");
	 WriteIniFileInt("group","sort",7,"userright.ini");

	 //管理应用设备
	 WriteIniFileString("device","value" , "IDS_Right_ManagerDevice" , "userright.ini");
	 WriteIniFileString("device","adddevice","IDS_Right_AddDevice","userright.ini");
	 WriteIniFileString("device","editdevice","IDS_Right_EditDevice","userright.ini");
	 WriteIniFileString("device","deldevice" , "IDS_Right_DeleteDevice" ,"userright.ini");
	 WriteIniFileString("device","copydevice","IDS_Right_CopyDevice","userright.ini");
	 WriteIniFileString("device","devicerefresh","IDS_Right_Refresh","userright.ini");
	 WriteIniFileString("device","testdevice","IDS_Right_TestDevice","userright.ini");
	 WriteIniFileInt("device","sort",8,"userright.ini");

	 //管理监测器
	 WriteIniFileString("monitor","value" , "IDS_Right_ManagerMonitor" , "userright.ini");
	 WriteIniFileString("monitor","addmonitor","IDS_Right_AddMonitor","userright.ini");
	 WriteIniFileString("monitor","editmonitor","IDS_Right_EditMonitor","userright.ini");
	 WriteIniFileString("monitor","delmonitor" , "IDS_Right_DeleteMonitor" ,"userright.ini");
	 WriteIniFileString("monitor","monitorrefresh","IDS_Right_Refresh","userright.ini");
	 WriteIniFileInt("monitor","sort",9,"userright.ini"); 
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
	new WText("<div id='view_panel' class='panel_view'>", app.root());
    app.setTitle("Sms Set");
    CUserList setform(app.root());
	setform.appSelf = &app;
	if(setform.pFrameTable != NULL)
	{
			std::string  movestr;
			movestr ="";
			movestr+="<script language=\"javascript\">\n";
			movestr+="var _canResize = false;\n";
			movestr+="function resizeTable(){\n";
			movestr+="   if(_canResize){\n";
			movestr+="   var obj = document.all('";
			movestr+= setform.pFrameTable->formName();
			movestr+="');\n";
			movestr+="   if(event.x < 150 || event.x>450)\n";
			movestr+="        obj.rows[0].cells[1].style.pixelWidth = 5;\n";
			movestr+="   else{\n";
			movestr+="        obj.rows[0].cells[1].style.pixelWidth = 5;\n";
			movestr+="        obj.rows[0].cells[0].style.pixelWidth = event.x;\n";
			movestr+="       }\n";
			movestr+="   }\n";
			movestr+="}\n";
			movestr+="</script>\n";			

			app.setBeforBodyStr(movestr);
			app.setBodyAttribute(" class='workbody' onmousemove='resizeTable()' ");
	}
	else 
	app.setBodyAttribute(" class='workbody' ");

	new WText("</div>", app.root());
	AddJsParam("uistyle", "viewpan", app.root());
	AddJsParam("fullstyle", "true", app.root());
	AddJsParam("bGeneral", "false", app.root());
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", app.root());
	new WText("<SCRIPT language='JavaScript'>_OnLoad()</SCRIPT>", app.root());

	app.exec();
}


int main(int argc, char *argv[])
{

    func p = usermain;
    //WriteRightTpl();
	if (argc == 1) 
    {
        char buf[256];

		WebSession s(buf, false);
        s.start(p);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }

    return 0;
}