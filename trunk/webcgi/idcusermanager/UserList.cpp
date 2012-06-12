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
#include <WButtonGroup>
#include <WRadioButton>
#include "WSignalMapper"
#include <WScrollArea>

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

//
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

//
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
	pFrameTable = NULL;
	pUserAddTable = NULL;
	ShowMainTable();
}

//
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

	p_MainTable = new WSVMainTable(this, strMainTitle,true);
	if (p_MainTable->pHelpImg)
	{
		connect(p_MainTable->pHelpImg, SIGNAL(clicked()),this,SLOT());
	}
	
	initUserTable();
}

//
void CUserList::initUserTable()
{
	p_UserTable = new WSVFlexTable((WContainerWidget *)p_MainTable->GetContentTable()->elementAt(0,0), List,strTitle);
	p_UserTable->SetDivId("listpan1");

	if(p_UserTable->GetContentTable()!=NULL)
	{
		p_UserTable->AppendColumn("",WLength(80,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");
		
		p_UserTable->AppendColumn(strNameLabel,WLength(150,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");
		
		//p_UserTable->AppendColumn(strLoginLabel,WLength(150,WLength::Pixel));		
		//p_UserTable->SetDataRowStyle("table_data_grid_item_text");

		p_UserTable->AppendColumn(strState,WLength(100,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");

		p_UserTable->AppendColumn("用户类型",WLength(150,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");

		p_UserTable->AppendColumn("用户描述",WLength(100,WLength::Percentage));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");

		p_UserTable->AppendColumn(strNameEdit,WLength(100,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_img");

		//
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
	connect(pAdd, SIGNAL(clicked()),  "showbar();" ,this, SLOT(AddUser()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelUser()));

	connect(p_UserTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
	connect(p_UserTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));
	connect(p_UserTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));

	//IDC用户存储权限到idcuser.ini（存储用户名称、密码以及和IDC用户ID等）
	//所有业务管理人员存储权限到yewuuser.ini（存储用户名称、密码等以及和公用业务管理用户ID）
	//所有销售代表要存储权限到xiaoshou.ini（存储用户名称、密码等以及和公用业务管理用户ID）
	//厂商支持用户和观摩用户人员存储权限到allquanxian.ini（存储用户名称、密码等）

	ReadUserInfoToMyIni("idcuser.ini");

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

	pHideBtn = new WPushButton("hide button",this);
	if(pHideBtn)
	{
		pHideBtn->setToolTip("Hide Button");
		connect(pHideBtn,SIGNAL(clicked()),this,SLOT(DelUser()));
		pHideBtn->hide();
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

	bAddEdit = false;
	if(pUserAddTable != NULL)
	{
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
	
	initEditUserTable(strIndex,true);

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

	WebSession::js_af_up = "window.location.reload(true);hiddenbar()";
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
	
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{        
		if (m_pListItem->pSelect->isChecked())
		{   
			if(pHideBtn)
			{
				string strDelDes = pHideBtn->getEncodeCmd("xclicked()") ;
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

	string strDeleteUser;
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		if (m_pListItem->pSelect->isChecked())
		{
			std::string temp = m_pListItem->id;
			std::string strIndex = m_pListItem->id;		
			
			//根据Type判断是否需删除删除 entity.data 和 数据目录等。
			DeleteIniFileSection(strIndex, "idcuser.ini");

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
	//delete p_AdminUserTable;
	//p_AdminUserTable = NULL;
	m_pListUSER.clear();
	initUserTable();
	//initAdminUserTable();

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

		
	bAddEdit = true;
	if(pUserAddTable != NULL)
	{
		delete pUserAddTable;
		pUserAddTable = NULL;		
	}
	
	//OutputDebugString("AddUser");
	initAddUserTable();
	
	//...
	p_SelIDC->setChecked();
	SelIDCBtn();
	//InitSelBagTableFromId("");
	//InitSelUserTableFromId("");

	p_MainTable->GetContentTable()->hide();

	pCheckDisable->show();

	strGenIndex = "-1";

	
	//OutputDebugString("AddUser2sdddd");
	ClearValue();
	//OutputDebugString("AddUser44444");
	pUserAddTable->show();
	DWORD dwStart = GetTickCount();

	//OutputDebugString("AddUser2");
	//pGroupTree->InitTree("",true,true,false,"1");

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
	if(GetIniFileSections(keylist, "idcuser.ini"))
	{
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据			
			//strUserName = GetIniFileString((*keyitem), "UserName", "", "idcuser.ini");
			strLoginName = GetIniFileString((*keyitem), "LoginName", "", "idcuser.ini");
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
	
	if(p_SelIDC->isChecked() || p_SelWeiHu->isChecked() || p_SelSysWeihu->isChecked())
	{
		string strTmpIdcUserId = "";
		
		//新建IDC用户目录
		strTmpIdcUserId = CreatIdcUser(strGenIndex, "0", "localhost");
		OutputDebugString("CreateIdcUser");
		OutputDebugString(strTmpIdcUserId.c_str());

		//1、
		//IDC用户存储权限到idcuser.ini（存储用户名称、密码等以及和IDC用户ID等）
		if(p_SelIDC->isChecked())
		{
			WriteUserInfoToMyIni("idcuser.ini", "IDCUser", strTmpIdcUserId, "On");
		}
		else if(p_SelWeiHu->isChecked())
		{
			WriteUserInfoToMyIni("idcuser.ini", "WeiHuUser", strTmpIdcUserId, "On");
		}
		else if(p_SelSysWeihu->isChecked())
		{
			WriteUserInfoToMyIni("idcuser.ini", "SysWeihuUser", strTmpIdcUserId, "On");
		}
		else
		{
			
		}

		//用户定制的功能包参数（基础服务、服务器监测服务包、模拟业务监测服务包、应用监测服务包、定制服务包）写入entity.data。
	}
	else if(p_SelYeWu->isChecked())
	{
		//从公共配置general.ini读公用业务管理用户ID， 如果公用业务管理用户ID为空则新建IDC用户目录并将公用业务管理用户ID写入general.ini
		
		//所有业务管理人员存储权限到yewuuser.ini（存储用户名称、密码等以及和公用业务管理用户ID）
		WriteUserInfoToMyIni("idcuser.ini", "YeWu", "YeWuId", "On");
	}
	else if(p_SelXiaoShou->isChecked())
	{
		//从公共配置general.ini读公用销售代表ID， 如果公用业务管理用户ID为空则新建IDC用户目录并将公用销售代表ID写入general.ini

		//所有销售代表要存储权限到xiaoshou.ini（存储用户名称、密码等以及和公用销售代表ID）
		WriteUserInfoToMyIni("idcuser.ini", "Xiaoshou", "XiaoShouId", "On");
	}
	else if(p_SelChangShang->isChecked())
	{
		//厂商支持用户（存储用户名称、密码等）。	
		//WriteUserInfoToMyIni("allquanxian.ini", "AllQuanXian", "default", "On");
		WriteUserInfoToMyIni("idcuser.ini", "ChangShang", "default", "On");		
	}
	else if(p_SelGuanMo->isChecked())
	{
		//观摩用户人员存储权限到（存储用户名称、密码等）。	
		//WriteUserInfoToMyIni("allquanxian.ini", "AllQuanXian", "default", "On");
		WriteUserInfoToMyIni("idcuser.ini", "GuanMo", "default", "On");
	}
	else
	{
		
	}

	//更新用户界面列表。。	
	//更新列表

	//p_UserTable->GeDataTable()->clear();
	delete p_UserTable;
	p_UserTable = NULL;
	m_pListUSER.clear();
	initUserTable();


	//隐藏编辑界面
	pUserAddTable->hide();
	//pUserAddTable->HideAllErrorMsg();
	
	//if(pUserAddTable != NULL)
	//{
	//	pUserAddTable->clear();
	//	delete pUserAddTable;
	//	pUserAddTable = NULL;
	//	
	//}

	p_MainTable->GetContentTable()->show();

	WebSession::js_af_up = "hiddenbar()";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
void CUserList::ReadUserInfoToMyIni(string strIniName)
{
	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	
	string strUserName, strLoginName, strIsUse, strPwd, strIndex;
	
	//Idc新增信息
	string strUserType, strPointNumber, strIdcId, strUserDes, strOther;

	int nIsUse, nAdmin = -1;
	
	//从ini获取用户列表
	if(GetIniFileSections(keylist, strIniName))
	{
		//是否先按类型分一下， 这样会好查看得多。。。？

		//是否提供定位到某用户名称的功能， 如果用户量很大这是很有必要的。。。？
		
		//从ini初始化用户列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//从ini读数据
			strIndex = GetIniFileString((*keyitem), "nIndex", "", strIniName);

			nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, strIniName);
			if(nIsUse == -1)
				strIsUse = "开启";
			else
				strIsUse = "关闭";

			strUserName = GetIniFileString((*keyitem), "UserName", "" , strIniName);
			strLoginName = GetIniFileString((*keyitem), "LoginName", "", strIniName);
			strPwd = GetIniFileString((*keyitem), "Password", "", strIniName);			
			
			//Idc新增信息
			strUserType = GetIniFileString((*keyitem), "UserType", "", strIniName);
			strIdcId = GetIniFileString((*keyitem), "IdcUserId", "", strIniName);
			strUserDes = GetIniFileString((*keyitem), "UserDes", "", strIniName);
			strOther = GetIniFileString((*keyitem), "Other", "", strIniName);

			OutputDebugString("\n---------strPwd------------\n");
			OutputDebugString(strPwd.c_str());

			USER_LIST list;

			std::string section = *keyitem;
			int numRow = p_UserTable->GeDataTable()->numRows();
			p_UserTable->InitRow(numRow);

			//char abc[100];
			//sprintf(abc,"---initUserTable-%d \n",numRow);
			//OutputDebugString(abc);
			
			//选择
			WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow, 0));
			p_UserTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);

			//用户名称
			WText * pUserNameText = new WText(strUserName, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 2));
			p_UserTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
			
			////登录名称
			//WText * pLoginNameText = new WText(strLoginName, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 4));
			//p_UserTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
			
			//是否禁用？ == 状态
			WText * pIsUseText = new WText(strIsUse, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 4));				
			p_UserTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);

			WText * pUseTypeText = new WText(strUserType, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 6));				
			p_UserTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);

			//string strUserDes = "";
			//string strBaseBagNumber, strServerBagNumber, strAppBagNumber, strSimulationBagNumber, strCustomBagNumber;
			//strBaseBagNumber = GetIniFileString(strIndex, "BaseBagNumber", "0", "idcuser.ini");
			//strServerBagNumber = GetIniFileString(strIndex, "ServerBagNumber", "0", "idcuser.ini");
			//strAppBagNumber = GetIniFileString(strIndex, "AppBagNumber", "0", "idcuser.ini");
			//strSimulationBagNumber = GetIniFileString(strIndex, "SimulationBagNumber", "0", "idcuser.ini");
			//strCustomBagNumber = GetIniFileString(strIndex, "CustomBagNumber", "0", "idcuser.ini");

			WText * pUseTextDes = new WText("点树描述", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 8));				
			p_UserTable->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(AlignCenter);

			//编辑
			WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 10));
			p_UserTable->GeDataTable()->elementAt(numRow, 10)->setContentAlignment(AlignCenter);
			pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
			m_genMapper.setMapping(pEdit, strIndex); 
			connect(pEdit, SIGNAL(clicked()), "showbar();" ,&m_genMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

			//密码
			WText * pPwdText = new WText(strPwd, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 12));
			pPwdText->hide();

			//类型

			//点数等描述

			list.pSelect = pCheck;
			list.pUserName = pUserNameText;
			//list.pLoginName = pLoginNameText;
			list.pStatus = pIsUseText;
			list.id = section;
			m_pListUSER.push_back(list);
		}
	}
}

//
void CUserList::WriteUserInfoToMyIni(string strIniName, string strUserType, string strIdcUserId, string strStatu)
{
	//OutputDebugString("SaveUser");
	//OutputDebugString(strGenIndex.c_str());
	WriteIniFileString(strGenIndex, "nIndex", strGenIndex, strIniName);
	WriteIniFileString(strGenIndex, "UserName", TrimStdString(pEditUserName->text()).c_str(), strIniName);
	WriteIniFileString(strGenIndex, "LoginName", TrimStdString(pEditLogin->text()).c_str(), strIniName);
	
	//Idc新增
	WriteIniFileString(strGenIndex, "UserType", strUserType, strIniName);
	WriteIniFileString(strGenIndex, "IdcUserId", strIdcUserId, strIniName);

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

	WriteIniFileString(strGenIndex, "Password", pwd.c_str(), strIniName);	
	
	if(pCheckDisable->isChecked())
		WriteIniFileInt(strGenIndex, "nIsUse", -1, strIniName);
	else
		WriteIniFileInt(strGenIndex, "nIsUse", 1, strIniName);

	if(strUserType == "IDCUser")
	{
		WriteIniFileString(strGenIndex, "BaseBagNumber", TrimStdString(pBaseBagNumber->text()).c_str(), strIniName);
		WriteIniFileString(strGenIndex, "ServerBagNumber", TrimStdString(pServerBagNumber->text()).c_str(), strIniName);
		WriteIniFileString(strGenIndex, "AppBagNumber", TrimStdString(pAppBagNumber->text()).c_str(), strIniName);
		WriteIniFileString(strGenIndex, "SimulationBagNumber", TrimStdString(pSimulationBagNumber->text()).c_str(), strIniName);
		WriteIniFileString(strGenIndex, "CustomBagNumber", TrimStdString(pCustomBagNumber->text()).c_str(), strIniName);
		
		//新的EntityString
		WriteIniFileString(strGenIndex, "EntityString", "", strIniName);
	}
	else if(strUserType == "WeiHuUser")
	{
		//EntityString(从标准配置里读来写 可以不需要, 因为可以根据用户类型判断就可以了)
		WriteIniFileString(strGenIndex, "WeiHuEntityString", "", strIniName);	
	}
	else if(strUserType == "SysWeihuUser")
	{
		//EntityString(从标准配置里读来写 可以不需要, 因为可以根据用户类型判断就可以了)
		WriteIniFileString(strGenIndex, "SysWeihuEntityString", "", strIniName);
	}
	else if(strUserType == "YeWu")
	{
		//EntityString
		//WriteIniFileString(strGenIndex, "EntityString", "", strIniName);
	}
	else if(strUserType == "Xiaoshou")
	{
		//EntityString
		//WriteIniFileString(strGenIndex, "EntityString", "", strIniName);
	}
	else if(strUserType == "ChangShang")
	{
		//EntityString
		//WriteIniFileString(strGenIndex, "EntityString", "", strIniName);
	}
	else if(strUserType == "GuanMo")
	{
		//EntityString
		//WriteIniFileString(strGenIndex, "EntityString", "", strIniName);
	}
	else
	{
		
	}	

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
	//}
}


//生成编辑用户界面
void CUserList::initAddUserTable()
{
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
	pCheckDisable = new WCheckBox("开启",p_AddGene->AppendRowsContent(0, "", "", ""));

	//密码
	pEditPwd= new WLineEdit("",p_AddGene->AppendRowsContent(0, strPwdLabel, strPwdDes, ""));
	pEditPwd->setStyleClass("input_text");
	pEditPwd->setEchoMode(WLineEdit::Password);

	//确认密码
	pEditConfirmPwd = new WLineEdit("",p_AddGene->AppendRowsContent(0, strConfirmPwdLabel, strConfirmPwdDes, strConfirmPwdError));
	pEditConfirmPwd->setStyleClass("input_text");
	pEditConfirmPwd->setEchoMode(WLineEdit::Password);
	
	//用户类型单选框应该加在这里..................................................
	
	//选择用户类型
	WButtonGroup *p_SelUserRadio = new WButtonGroup();
	
	//p_AddGene->AppendRows("");
	//WContainerWidget *tmp = p_AddGene->AppendRowsContent(0, 0, 0, "选择用户类型", "", "");

	WContainerWidget *tmp = p_AddGene->AppendRowsContent(0, "请选择用户类型<span class =required>*</span>", "请选择用户类型", "请选择用户类型");
	
	//IDC用户
	p_SelIDC = new WRadioButton("IDC用户", tmp);
	p_SelUserRadio->addButton(p_SelIDC);
	connect(p_SelIDC, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelIDCBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//销售代表
	p_SelXiaoShou = new WRadioButton("销售代表", tmp);
	p_SelUserRadio->addButton(p_SelXiaoShou);
	connect(p_SelXiaoShou, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelXiaoShouBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//本系统维护人员
	p_SelSysWeihu = new WRadioButton("本系统维护人员", tmp);
	p_SelUserRadio->addButton(p_SelSysWeihu);
	connect(p_SelSysWeihu, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelSysWeihuBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//机房维护人员
	p_SelWeiHu = new WRadioButton("机房维护人员", tmp);
	p_SelUserRadio ->addButton(p_SelWeiHu);
	connect(p_SelWeiHu, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelWeiHuBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	
	//业务管理人员
	p_SelYeWu = new WRadioButton("业务管理人员", tmp);
	p_SelUserRadio->addButton(p_SelYeWu);
	connect(p_SelYeWu, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelYeWuBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//厂商支持账号
	p_SelChangShang = new WRadioButton("厂商支持账号", tmp);
	p_SelUserRadio->addButton(p_SelChangShang);
	connect(p_SelChangShang, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelChangShangBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//观摩账号
	p_SelGuanMo = new WRadioButton("观摩账号", tmp);
	p_SelUserRadio->addButton(p_SelGuanMo);
	connect(p_SelGuanMo, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelGuanMoBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//隐藏help,erro
	p_AddGene->HideAllErrorMsg();
	p_AddGene->ShowOrHideHelp();
	
	
	p_ContentTabe1 = pUserAddTable->GetContentTable2();
	InitSelBagTableFromId("", (WContainerWidget *)p_ContentTabe1->elementAt(1,0));
	InitSelUserTableFromId("", (WContainerWidget *)p_ContentTabe1->elementAt(1,0));

	//保存,取消按钮触发
	connect(pUserAddTable->pSave, SIGNAL(clicked()), "showbar();" ,this, SLOT(SaveUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	connect(pUserAddTable->pCancel, SIGNAL(clicked()), "showbar();" ,this, SLOT(CancelUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
}

//生成功能包选择定制界面
void CUserList::InitSelBagTableFromId(string strUserId, WContainerWidget * pParent)
{
	p_FlexSelBag = new WSVFlexTable(pParent, Group, "功能包设置");
	p_FlexSelBag->InitTable();
	
	//p_FlexSelBag->AppendRows("功能包设置");
	p_FlexSelBag->AppendRows("");

	pBaseBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "基础服务包点数", "基础服务包点数", "基础服务包点数不能为负数！"));
	pBaseBagNumber->setStyleClass("input_text");

	pServerBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "服务器监测包点数", "服务器监测包点数", "服务器监测包点数不能为负数！"));
	pServerBagNumber->setStyleClass("input_text");

	pAppBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "应用监测包点数", "应用监测包点数", "应用监测包点数不能为负数！"));
	pAppBagNumber->setStyleClass("input_text");

	pSimulationBagNumber= new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "模拟业务监测包点数", "模拟业务监测包点数", "模拟业务监测包点数不能为负数！"));
	pSimulationBagNumber->setStyleClass("input_text");

	pCustomBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "定制服务监测包点数", "定制服务监测包点数", "定制服务监测包点数不能为负数！"));
	pCustomBagNumber->setStyleClass("input_text");

	//赋值
	if(strUserId == "")
	{
		
	}
	else
	{

	}

	p_FlexSelBag->HideAllErrorMsg();
	p_FlexSelBag->ShowOrHideHelp();
}

//生成销售代表选择用户界面
void CUserList::InitSelUserTableFromId(string strUserId, WContainerWidget * pParent)
{
	p_FlexSelUser = new WSVFlexTable(pParent, Group, "选择用户");	
	p_FlexSelUser->InitTable();
	

	p_FlexSelUser->AppendRows("我的用户");

	//WContainerWidget * tmp =;
	
	WTable * pMyListTable = new WTable(p_FlexSelUser->AppendRowsContent(0, "", "", ""));	
	for(int i = 0; i < 10; i++)
	{
		new WCheckBox("我的用户", pMyListTable->elementAt(i/4, i%4));
	}

	//new WCheckBox("设备1", p_FlexSelBag->AppendRowsContent(0, "", "设备", "设备"));
	//new WCheckBox("设备2", p_FlexSelBag->AppendRowsContent(0, "", "设备", "设备"));
	////new WCheckBox("设备1", p_FlexSelBag->AppendRowsContent(2, "", "", ""));

	////new WCheckBox("设备2", p_FlexSelBag->AppendRowsContent(2, 0, 1, "","",""));
	//new WCheckBox("设备11", p_FlexSelBag->AppendRowsContent(1, "", "设备", "设备"));
	//new WCheckBox("设备12", p_FlexSelBag->AppendRowsContent(1, "", "设备", "设备"));


	//new WCheckBox("设备21", p_FlexSelBag->AppendRowsContent(2, "", "设备", "设备"));
	//new WCheckBox("设备22", p_FlexSelBag->AppendRowsContent(2, "", "设备", "设备"));


	//new WCheckBox("设备211", p_FlexSelBag->AppendRowsContent(3, 0, 1, "", "设备", "设备"));
	//new WCheckBox("设备212", p_FlexSelBag->AppendRowsContent(3, 1, 1, "", "设备", "设备"));

	//WContainerWidget * tmp1 = p_FlexSelBag->AppendRowsContent(4, 0, 0, "定制服务包", "定制服务包", "定制服务包");
	//new WCheckBox("设备1", tmp1);
	//new WCheckBox("设备2", tmp1);

	p_FlexSelUser->AppendRows("其他用户");

	WTable * pOtherListTable = new WTable(p_FlexSelUser->AppendRowsContent(1, "", "", ""));	
	//for(int i = 0; i < 30; i++)
	//{
	//	new WCheckBox("设备1", pOtherListTable->elementAt(i/3, i%3));
	//}

	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	
	string strUserName, strIndex;	

	//赋值
	if(strUserId == "")
	{
		//1、取出所有用户（用户类型为IDC用户）索引列表。
	
		//从ini获取用户列表
		if(GetIniFileSections(keylist, "idcuser.ini"))
		{
			int j = 0;
			//从ini初始化用户列表
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem++)	
			{
				strIndex = GetIniFileString((*keyitem), "nIndex", "", "idcuser.ini");
				strUserName = GetIniFileString((*keyitem), "UserName", "" , "idcuser.ini");	
				
				IDCUSER_LIST list;
				list.pSelect = new WCheckBox(strUserName, pOtherListTable->elementAt(j/4, j%4));
				list.strId = (*keyitem);

				m_pSelUserList.push_back(list);
				j++;
			}
		}

		//2、我的用户为空， 其他用户为索引列表里的用户。
	}
	else
	{
		//1、分解出我的用户的索引列表， 和所有用户列表比较并算出其他用户（用户类型为IDC用户）索引列表。
		//2、根据两个索引列表构造界面。
	}

	p_FlexSelUser->HideAllErrorMsg();
	p_FlexSelUser->ShowOrHideHelp();
}

//IDC用户
void CUserList::SelIDCBtn()
{
	//显示功能包定制界面 隐藏用户选择界面
	p_FlexSelUser->hide();
	p_FlexSelBag->show();

	WebSession::js_af_up = "hiddenbar()";
}

//机房维护人员
void CUserList::SelWeiHuBtn()
{
	//显示功能包定制界面 隐藏用户选择界面
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//本系统维护人员
void CUserList::SelSysWeihuBtn()
{
	//显示功能包定制界面 隐藏用户选择界面
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//销售代表
void CUserList::SelXiaoShouBtn()
{
	//显示用户选择界面 隐藏功能包定制界面
	p_FlexSelUser->show();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//业务管理人员
void CUserList::SelYeWuBtn()
{
	//隐藏功能包定制和用户选择界面
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//厂商支持账号
void CUserList::SelChangShangBtn()
{
	//隐藏功能包定制和用户选择界面
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//观摩账号
void CUserList::SelGuanMoBtn()
{
	//隐藏功能包定制和用户选择界面
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
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
	bAddEdit=false;

	string strUserName, strLoginName, strIsUse, strPwd;

	//Idc新增信息
	string strUserType, strPointNumber, strIdcId, strUserDes, strOther;

	int nIsUse, nAdmin = -1;

	initAddUserTable();
	pUserAddTable->show();
	
	//读取文件
	strIndex = GetIniFileString(strIndex, "nIndex", "", "idcuser.ini");
	nIsUse = GetIniFileInt(strIndex, "nIsUse", -1, "idcuser.ini");
	strUserName = GetIniFileString(strIndex, "UserName", "" , "idcuser.ini");
	strLoginName = GetIniFileString(strIndex, "LoginName", "", "idcuser.ini");
	strPwd = GetIniFileString(strIndex, "Password", "", "idcuser.ini");
	nAdmin = GetIniFileInt(strIndex, "nAdmin", -1, "idcuser.ini");
	
	pEditUserName->setText(strUserName);
	pEditLogin->setText(strLoginName);

	if(bUserType)
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

	//Idc新增信息
	strUserType = GetIniFileString(strIndex, "UserType", "", "idcuser.ini");
	strIdcId = GetIniFileString(strIndex, "IdcUserId", "", "idcuser.ini");
	strUserDes = GetIniFileString(strIndex, "UserDes", "", "idcuser.ini");
	strOther = GetIniFileString(strIndex, "Other", "", "idcuser.ini");

	//不同用户有不同的的编辑界面， 且此时不能再修改用户类型
	if(strUserType == "IDCUser")
	{
		p_SelIDC->setChecked();
		p_FlexSelUser->hide();
		p_FlexSelBag->show();

		string strBaseBagNumber, strServerBagNumber, strAppBagNumber, strSimulationBagNumber, strCustomBagNumber;
		strBaseBagNumber = GetIniFileString(strIndex, "BaseBagNumber", "0", "idcuser.ini");
		strServerBagNumber = GetIniFileString(strIndex, "ServerBagNumber", "0", "idcuser.ini");
		strAppBagNumber = GetIniFileString(strIndex, "AppBagNumber", "0", "idcuser.ini");
		strSimulationBagNumber = GetIniFileString(strIndex, "SimulationBagNumber", "0", "idcuser.ini");
		strCustomBagNumber = GetIniFileString(strIndex, "CustomBagNumber", "0", "idcuser.ini");

		
		pBaseBagNumber->setText(strBaseBagNumber);
		pServerBagNumber->setText(strServerBagNumber);
		pAppBagNumber->setText(strAppBagNumber);
		pSimulationBagNumber->setText(strSimulationBagNumber);
		pCustomBagNumber->setText(strCustomBagNumber);
	}
	else if(strUserType == "WeiHuUser")
	{
		p_SelWeiHu->setChecked();
		p_FlexSelUser->hide();
		p_FlexSelBag->hide();
	}
	else if(strUserType == "SysWeihuUser")
	{
		p_SelSysWeihu->setChecked();
		p_FlexSelUser->hide();
		p_FlexSelBag->hide();
	}
	else if(strUserType == "YeWu")
	{
		p_SelYeWu->setChecked();
		p_FlexSelUser->hide();
		p_FlexSelBag->hide();
	}
	else if(strUserType == "Xiaoshou")
	{
		p_SelXiaoShou->setChecked();
		p_FlexSelUser->show();
		p_FlexSelBag->hide();
	}
	else if(strUserType == "ChangShang")
	{
		p_SelChangShang->setChecked();
		p_FlexSelUser->hide();
		p_FlexSelBag->hide();
	}
	else if(strUserType == "GuanMo")
	{
		p_SelGuanMo->setChecked();
		p_FlexSelUser->hide();
		p_FlexSelBag->hide();
	}
	else
	{
		
	}	

	p_SelIDC->disable();
	p_SelWeiHu->disable();
	p_SelSysWeihu->disable();
	p_SelYeWu->disable();
	p_SelXiaoShou->disable();
	p_SelChangShang->disable();
	p_SelGuanMo->disable();	

}

//选择全部按钮响应
void CUserList::SelAll()
{
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(true);
	}
}

//全部不选择按钮响应
void CUserList::SelNone()
{
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(false);
	}
}

//反选按钮响应
void CUserList::SelInvert()
{
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
	//delete p_AdminUserTable;
	//p_AdminUserTable = NULL;
	
	m_pListUSER.clear();
	initUserTable();
	
	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

//
void CUserList::ShowHelp()
{
	OutputDebugString("------showhelp()--------------");
	p_AddGene->ShowOrHideHelp();	
}
//
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

//写权限模板
void WriteRightTpl()
{
	string strTmp;

	////Resource
	//OBJECT objRes=LoadResource("default", "localhost");  
	//if( objRes !=INVALID_VALUE )
	//{	
	//	MAPNODE ResNode=GetResourceNode(objRes);
	//	if( ResNode != INVALID_VALUE )
	//	{
	//		FindNodeValue(ResNode,"IDS_Right_My_SiteView",strMySiteView);
	//	}
	//	CloseResource(objRes);
	//}

	
	//(1) 流量报表服务包：为IDC客户提供查看在网通IDC托管的设备连接网通网络设备端口的流量报表。
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(2) 基础监测服务包：包括网络设备监测、连通性测试。
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(3) 服务器监测服务包：包括服务器监测。
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(4) 模拟业务监测服务包：包括Web监测。
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(5) 应用监测服务包：包括邮件监测、DNS监测、NEWS监测。
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(6) 定制服务包：包括数据库监测、防火墙监测、中间件监测、负载均衡监测。
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");	
}

//
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