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
	strMainTitle ="�û�����";
	strTitle ="��ͨ�û��б�";
	
	strNameLabel = "�û���";
	strNameDes = "��¼��ҳ������ʾ������";
	strNameError = "�û�������Ϊ�ջ��ظ�";

	strLoginLabel = "��¼��";	
	strLoginDes = "��¼ϵͳʱ���������";
	strLoginError = "��¼������Ϊ�ջ��ظ�";
	strState = "״̬";
	strNameUse = "��ֹ";
	strNameEdit="�༭";
	strAdminTitle ="����Ա�б�";
	strDel=  "ȷ��ɾ��ѡ���û���";
	strAdd="����û�";
	strEdit="�༭�û�";
	strGeneral="��������";	

	strPwdLabel = "����";
	strPwdDes = "���û������룬����Ϊ�ա����ʹ��LDAP��֤������ʹ��";
	
	strConfirmPwdLabel = "����ȷ��";
	strConfirmPwdDes = "�ظ��������û�������";
	strConfirmPwdError = "������������, ����������";
	strNullList = "[----------��ͨ�û��б�Ϊ��-----------]";
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


//���index
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

//����list�Ż�ȡΨһ��index
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

//��ʼ��������
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

		p_UserTable->AppendColumn("�û�����",WLength(150,WLength::Pixel));
		p_UserTable->SetDataRowStyle("table_data_grid_item_text");

		p_UserTable->AppendColumn("�û�����",WLength(100,WLength::Percentage));
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
	
	//ɾ��
	WSVButton *pDel= new WSVButton(m_pGroupOperate->elementAt(0,0),szTipDel,"button_bg_del.png");	
	
	//���
	p_UserTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
	WSVButton * pAdd = new WSVButton(p_UserTable->GetActionTable()->elementAt(0,2), strAdd, "button_bg_add_black.png", strAdd, true);

	connect(&m_genMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditUser(const std::string)));
	connect(pAdd, SIGNAL(clicked()),  "showbar();" ,this, SLOT(AddUser()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelUser()));

	connect(p_UserTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
	connect(p_UserTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));
	connect(p_UserTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));

	//IDC�û��洢Ȩ�޵�idcuser.ini���洢�û����ơ������Լ���IDC�û�ID�ȣ�
	//����ҵ�������Ա�洢Ȩ�޵�yewuuser.ini���洢�û����ơ�������Լ��͹���ҵ������û�ID��
	//�������۴���Ҫ�洢Ȩ�޵�xiaoshou.ini���洢�û����ơ�������Լ��͹���ҵ������û�ID��
	//����֧���û��͹�Ħ�û���Ա�洢Ȩ�޵�allquanxian.ini���洢�û����ơ�����ȣ�

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


//�༭��ͨ�û���ť��Ӧ
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

	//����
	//pUserTable->hide();
	//pAdminUserTable->hide();

	p_MainTable->GetContentTable()->hide();

	strGenIndex = strIndex;

	//��ͨ�û�
	
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

//ɾ���û���ť��Ӧ
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
			
			//����Type�ж��Ƿ���ɾ��ɾ�� entity.data �� ����Ŀ¼�ȡ�
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

	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeDelete,strMainTitle,strDelName);
	strDelName = "";

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

//�����û���ť��Ӧ
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

//�Ƿ�����ͬ�ĵ�¼���û�����
bool CUserList::IsUserExist(string strLoginNameIn, string strUserNameIn)
{
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strUserName;
	string strLoginName;

	bool bExist = false;
	//��ini��ȡ�û��б�
	if(GetIniFileSections(keylist, "idcuser.ini"))
	{
		//��ini��ʼ���û��б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//��ini������			
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

//���水ť��Ӧ
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

	//������
	bool bError = false;
	std::list<string> errorMsgList;

    //�û�����
	if(pEditUserName->text().empty())
    {
		ErrorTest(strNameError);
		bError = true;
    }

    // ��½����
    if(pEditLogin->text().empty())
    {
        ErrorTest(strLoginError);
		bError = true;
    }
    
    // �������벻��
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

	//�д��󷵻�
	if(bError)
	{
		//pUserAddTable->ShowErrorMsg(errorMsgList);
		WebSession::js_af_up = "hiddenbar()";
		bEnd = true;	
		goto OPEnd;
	}

	//���ݴ洢����
	bool bAdd = false;

	//��������(���� �༭һ��)
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
		
		//�½�IDC�û�Ŀ¼
		strTmpIdcUserId = CreatIdcUser(strGenIndex, "0", "localhost");
		OutputDebugString("CreateIdcUser");
		OutputDebugString(strTmpIdcUserId.c_str());

		//1��
		//IDC�û��洢Ȩ�޵�idcuser.ini���洢�û����ơ�������Լ���IDC�û�ID�ȣ�
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

		//�û����ƵĹ��ܰ��������������񡢷��������������ģ��ҵ����������Ӧ�ü�����������Ʒ������д��entity.data��
	}
	else if(p_SelYeWu->isChecked())
	{
		//�ӹ�������general.ini������ҵ������û�ID�� �������ҵ������û�IDΪ�����½�IDC�û�Ŀ¼��������ҵ������û�IDд��general.ini
		
		//����ҵ�������Ա�洢Ȩ�޵�yewuuser.ini���洢�û����ơ�������Լ��͹���ҵ������û�ID��
		WriteUserInfoToMyIni("idcuser.ini", "YeWu", "YeWuId", "On");
	}
	else if(p_SelXiaoShou->isChecked())
	{
		//�ӹ�������general.ini���������۴���ID�� �������ҵ������û�IDΪ�����½�IDC�û�Ŀ¼�����������۴���IDд��general.ini

		//�������۴���Ҫ�洢Ȩ�޵�xiaoshou.ini���洢�û����ơ�������Լ��͹������۴���ID��
		WriteUserInfoToMyIni("idcuser.ini", "Xiaoshou", "XiaoShouId", "On");
	}
	else if(p_SelChangShang->isChecked())
	{
		//����֧���û����洢�û����ơ�����ȣ���	
		//WriteUserInfoToMyIni("allquanxian.ini", "AllQuanXian", "default", "On");
		WriteUserInfoToMyIni("idcuser.ini", "ChangShang", "default", "On");		
	}
	else if(p_SelGuanMo->isChecked())
	{
		//��Ħ�û���Ա�洢Ȩ�޵����洢�û����ơ�����ȣ���	
		//WriteUserInfoToMyIni("allquanxian.ini", "AllQuanXian", "default", "On");
		WriteUserInfoToMyIni("idcuser.ini", "GuanMo", "default", "On");
	}
	else
	{
		
	}

	//�����û������б���	
	//�����б�

	//p_UserTable->GeDataTable()->clear();
	delete p_UserTable;
	p_UserTable = NULL;
	m_pListUSER.clear();
	initUserTable();


	//���ر༭����
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
	
	//Idc������Ϣ
	string strUserType, strPointNumber, strIdcId, strUserDes, strOther;

	int nIsUse, nAdmin = -1;
	
	//��ini��ȡ�û��б�
	if(GetIniFileSections(keylist, strIniName))
	{
		//�Ƿ��Ȱ����ͷ�һ�£� ������ò鿴�öࡣ������

		//�Ƿ��ṩ��λ��ĳ�û����ƵĹ��ܣ� ����û����ܴ����Ǻ��б�Ҫ�ġ�������
		
		//��ini��ʼ���û��б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//��ini������
			strIndex = GetIniFileString((*keyitem), "nIndex", "", strIniName);

			nIsUse = GetIniFileInt((*keyitem), "nIsUse", -1, strIniName);
			if(nIsUse == -1)
				strIsUse = "����";
			else
				strIsUse = "�ر�";

			strUserName = GetIniFileString((*keyitem), "UserName", "" , strIniName);
			strLoginName = GetIniFileString((*keyitem), "LoginName", "", strIniName);
			strPwd = GetIniFileString((*keyitem), "Password", "", strIniName);			
			
			//Idc������Ϣ
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
			
			//ѡ��
			WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow, 0));
			p_UserTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);

			//�û�����
			WText * pUserNameText = new WText(strUserName, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 2));
			p_UserTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
			
			////��¼����
			//WText * pLoginNameText = new WText(strLoginName, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 4));
			//p_UserTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
			
			//�Ƿ���ã� == ״̬
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

			WText * pUseTextDes = new WText("��������", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 8));				
			p_UserTable->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(AlignCenter);

			//�༭
			WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 10));
			p_UserTable->GeDataTable()->elementAt(numRow, 10)->setContentAlignment(AlignCenter);
			pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
			m_genMapper.setMapping(pEdit, strIndex); 
			connect(pEdit, SIGNAL(clicked()), "showbar();" ,&m_genMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

			//����
			WText * pPwdText = new WText(strPwd, (WContainerWidget*)p_UserTable->GeDataTable()->elementAt(numRow , 12));
			pPwdText->hide();

			//����

			//����������

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
	
	//Idc����
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
		
		//�µ�EntityString
		WriteIniFileString(strGenIndex, "EntityString", "", strIniName);
	}
	else if(strUserType == "WeiHuUser")
	{
		//EntityString(�ӱ�׼���������д ���Բ���Ҫ, ��Ϊ���Ը����û������жϾͿ�����)
		WriteIniFileString(strGenIndex, "WeiHuEntityString", "", strIniName);	
	}
	else if(strUserType == "SysWeihuUser")
	{
		//EntityString(�ӱ�׼���������д ���Բ���Ҫ, ��Ϊ���Ը����û������жϾͿ�����)
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

//ȡ����ť��Ӧ
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

	//���� pUserAddTable
	pUserAddTable->hide();
	//pUserAddTable->HideAllErrorMsg();
	p_MainTable->GetContentTable()->show();
	OutputDebugString("ȡ���ɹ�!");
	WebSession::js_af_up = "hiddenbar()";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}


//��ձ༭�û�����
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


//���ɱ༭�û�����
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
	
	//һ������
	p_AddGene = new WSVFlexTable((WContainerWidget *)p_ContentTabe->GetContentTable()->elementAt(0,0),Group,strGeneral);
	
	p_AddGene->AppendRows("");
	
	//��¼��
	pEditLogin= new WLineEdit("",p_AddGene->AppendRowsContent(0, strLoginLabel+"<span class =required>*</span>", strLoginDes, strLoginError));
	pEditLogin->setStyleClass("input_text");
	//�û���
	pEditUserName= new WLineEdit("",p_AddGene->AppendRowsContent(0, strNameLabel+"<span class =required>*</span>", strNameDes, strNameError));
	pEditUserName->setStyleClass("input_text");
	
	//
	pCheckDisable = new WCheckBox("����",p_AddGene->AppendRowsContent(0, "", "", ""));

	//����
	pEditPwd= new WLineEdit("",p_AddGene->AppendRowsContent(0, strPwdLabel, strPwdDes, ""));
	pEditPwd->setStyleClass("input_text");
	pEditPwd->setEchoMode(WLineEdit::Password);

	//ȷ������
	pEditConfirmPwd = new WLineEdit("",p_AddGene->AppendRowsContent(0, strConfirmPwdLabel, strConfirmPwdDes, strConfirmPwdError));
	pEditConfirmPwd->setStyleClass("input_text");
	pEditConfirmPwd->setEchoMode(WLineEdit::Password);
	
	//�û����͵�ѡ��Ӧ�ü�������..................................................
	
	//ѡ���û�����
	WButtonGroup *p_SelUserRadio = new WButtonGroup();
	
	//p_AddGene->AppendRows("");
	//WContainerWidget *tmp = p_AddGene->AppendRowsContent(0, 0, 0, "ѡ���û�����", "", "");

	WContainerWidget *tmp = p_AddGene->AppendRowsContent(0, "��ѡ���û�����<span class =required>*</span>", "��ѡ���û�����", "��ѡ���û�����");
	
	//IDC�û�
	p_SelIDC = new WRadioButton("IDC�û�", tmp);
	p_SelUserRadio->addButton(p_SelIDC);
	connect(p_SelIDC, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelIDCBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//���۴���
	p_SelXiaoShou = new WRadioButton("���۴���", tmp);
	p_SelUserRadio->addButton(p_SelXiaoShou);
	connect(p_SelXiaoShou, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelXiaoShouBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//��ϵͳά����Ա
	p_SelSysWeihu = new WRadioButton("��ϵͳά����Ա", tmp);
	p_SelUserRadio->addButton(p_SelSysWeihu);
	connect(p_SelSysWeihu, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelSysWeihuBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//����ά����Ա
	p_SelWeiHu = new WRadioButton("����ά����Ա", tmp);
	p_SelUserRadio ->addButton(p_SelWeiHu);
	connect(p_SelWeiHu, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelWeiHuBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	
	//ҵ�������Ա
	p_SelYeWu = new WRadioButton("ҵ�������Ա", tmp);
	p_SelUserRadio->addButton(p_SelYeWu);
	connect(p_SelYeWu, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelYeWuBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//����֧���˺�
	p_SelChangShang = new WRadioButton("����֧���˺�", tmp);
	p_SelUserRadio->addButton(p_SelChangShang);
	connect(p_SelChangShang, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelChangShangBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//��Ħ�˺�
	p_SelGuanMo = new WRadioButton("��Ħ�˺�", tmp);
	p_SelUserRadio->addButton(p_SelGuanMo);
	connect(p_SelGuanMo, SIGNAL(clicked()), "showbar();" ,this, SLOT(SelGuanMoBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//����help,erro
	p_AddGene->HideAllErrorMsg();
	p_AddGene->ShowOrHideHelp();
	
	
	p_ContentTabe1 = pUserAddTable->GetContentTable2();
	InitSelBagTableFromId("", (WContainerWidget *)p_ContentTabe1->elementAt(1,0));
	InitSelUserTableFromId("", (WContainerWidget *)p_ContentTabe1->elementAt(1,0));

	//����,ȡ����ť����
	connect(pUserAddTable->pSave, SIGNAL(clicked()), "showbar();" ,this, SLOT(SaveUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	connect(pUserAddTable->pCancel, SIGNAL(clicked()), "showbar();" ,this, SLOT(CancelUser()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
}

//���ɹ��ܰ�ѡ���ƽ���
void CUserList::InitSelBagTableFromId(string strUserId, WContainerWidget * pParent)
{
	p_FlexSelBag = new WSVFlexTable(pParent, Group, "���ܰ�����");
	p_FlexSelBag->InitTable();
	
	//p_FlexSelBag->AppendRows("���ܰ�����");
	p_FlexSelBag->AppendRows("");

	pBaseBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "�������������", "�������������", "�����������������Ϊ������"));
	pBaseBagNumber->setStyleClass("input_text");

	pServerBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "��������������", "��������������", "������������������Ϊ������"));
	pServerBagNumber->setStyleClass("input_text");

	pAppBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "Ӧ�ü�������", "Ӧ�ü�������", "Ӧ�ü�����������Ϊ������"));
	pAppBagNumber->setStyleClass("input_text");

	pSimulationBagNumber= new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "ģ��ҵ���������", "ģ��ҵ���������", "ģ��ҵ�������������Ϊ������"));
	pSimulationBagNumber->setStyleClass("input_text");

	pCustomBagNumber = new WLineEdit("0",p_FlexSelBag->AppendRowsContent(0, "���Ʒ����������", "���Ʒ����������", "���Ʒ��������������Ϊ������"));
	pCustomBagNumber->setStyleClass("input_text");

	//��ֵ
	if(strUserId == "")
	{
		
	}
	else
	{

	}

	p_FlexSelBag->HideAllErrorMsg();
	p_FlexSelBag->ShowOrHideHelp();
}

//�������۴���ѡ���û�����
void CUserList::InitSelUserTableFromId(string strUserId, WContainerWidget * pParent)
{
	p_FlexSelUser = new WSVFlexTable(pParent, Group, "ѡ���û�");	
	p_FlexSelUser->InitTable();
	

	p_FlexSelUser->AppendRows("�ҵ��û�");

	//WContainerWidget * tmp =;
	
	WTable * pMyListTable = new WTable(p_FlexSelUser->AppendRowsContent(0, "", "", ""));	
	for(int i = 0; i < 10; i++)
	{
		new WCheckBox("�ҵ��û�", pMyListTable->elementAt(i/4, i%4));
	}

	//new WCheckBox("�豸1", p_FlexSelBag->AppendRowsContent(0, "", "�豸", "�豸"));
	//new WCheckBox("�豸2", p_FlexSelBag->AppendRowsContent(0, "", "�豸", "�豸"));
	////new WCheckBox("�豸1", p_FlexSelBag->AppendRowsContent(2, "", "", ""));

	////new WCheckBox("�豸2", p_FlexSelBag->AppendRowsContent(2, 0, 1, "","",""));
	//new WCheckBox("�豸11", p_FlexSelBag->AppendRowsContent(1, "", "�豸", "�豸"));
	//new WCheckBox("�豸12", p_FlexSelBag->AppendRowsContent(1, "", "�豸", "�豸"));


	//new WCheckBox("�豸21", p_FlexSelBag->AppendRowsContent(2, "", "�豸", "�豸"));
	//new WCheckBox("�豸22", p_FlexSelBag->AppendRowsContent(2, "", "�豸", "�豸"));


	//new WCheckBox("�豸211", p_FlexSelBag->AppendRowsContent(3, 0, 1, "", "�豸", "�豸"));
	//new WCheckBox("�豸212", p_FlexSelBag->AppendRowsContent(3, 1, 1, "", "�豸", "�豸"));

	//WContainerWidget * tmp1 = p_FlexSelBag->AppendRowsContent(4, 0, 0, "���Ʒ����", "���Ʒ����", "���Ʒ����");
	//new WCheckBox("�豸1", tmp1);
	//new WCheckBox("�豸2", tmp1);

	p_FlexSelUser->AppendRows("�����û�");

	WTable * pOtherListTable = new WTable(p_FlexSelUser->AppendRowsContent(1, "", "", ""));	
	//for(int i = 0; i < 30; i++)
	//{
	//	new WCheckBox("�豸1", pOtherListTable->elementAt(i/3, i%3));
	//}

	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	
	string strUserName, strIndex;	

	//��ֵ
	if(strUserId == "")
	{
		//1��ȡ�������û����û�����ΪIDC�û��������б�
	
		//��ini��ȡ�û��б�
		if(GetIniFileSections(keylist, "idcuser.ini"))
		{
			int j = 0;
			//��ini��ʼ���û��б�
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

		//2���ҵ��û�Ϊ�գ� �����û�Ϊ�����б�����û���
	}
	else
	{
		//1���ֽ���ҵ��û��������б� �������û��б�Ƚϲ���������û����û�����ΪIDC�û��������б�
		//2���������������б�����档
	}

	p_FlexSelUser->HideAllErrorMsg();
	p_FlexSelUser->ShowOrHideHelp();
}

//IDC�û�
void CUserList::SelIDCBtn()
{
	//��ʾ���ܰ����ƽ��� �����û�ѡ�����
	p_FlexSelUser->hide();
	p_FlexSelBag->show();

	WebSession::js_af_up = "hiddenbar()";
}

//����ά����Ա
void CUserList::SelWeiHuBtn()
{
	//��ʾ���ܰ����ƽ��� �����û�ѡ�����
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//��ϵͳά����Ա
void CUserList::SelSysWeihuBtn()
{
	//��ʾ���ܰ����ƽ��� �����û�ѡ�����
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//���۴���
void CUserList::SelXiaoShouBtn()
{
	//��ʾ�û�ѡ����� ���ع��ܰ����ƽ���
	p_FlexSelUser->show();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//ҵ�������Ա
void CUserList::SelYeWuBtn()
{
	//���ع��ܰ����ƺ��û�ѡ�����
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//����֧���˺�
void CUserList::SelChangShangBtn()
{
	//���ع��ܰ����ƺ��û�ѡ�����
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//��Ħ�˺�
void CUserList::SelGuanMoBtn()
{
	//���ع��ܰ����ƺ��û�ѡ�����
	p_FlexSelUser->hide();
	p_FlexSelBag->hide();

	WebSession::js_af_up = "hiddenbar()";
}

//��ʾ������Ϣ
void CUserList::ErrorTest(const string &errorMsg)
{
	p_AddGene->HideAllErrorMsg();

	std::list<string> errorMsgList;
	errorMsgList.push_back(errorMsg);
	p_AddGene->ShowErrorMsg(errorMsgList);
}

//��ʾ�༭�û�����
void CUserList::initEditUserTable(string strIndex,bool bUserType)
{
	bAddEdit=false;

	string strUserName, strLoginName, strIsUse, strPwd;

	//Idc������Ϣ
	string strUserType, strPointNumber, strIdcId, strUserDes, strOther;

	int nIsUse, nAdmin = -1;

	initAddUserTable();
	pUserAddTable->show();
	
	//��ȡ�ļ�
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

	//Idc������Ϣ
	strUserType = GetIniFileString(strIndex, "UserType", "", "idcuser.ini");
	strIdcId = GetIniFileString(strIndex, "IdcUserId", "", "idcuser.ini");
	strUserDes = GetIniFileString(strIndex, "UserDes", "", "idcuser.ini");
	strOther = GetIniFileString(strIndex, "Other", "", "idcuser.ini");

	//��ͬ�û��в�ͬ�ĵı༭���棬 �Ҵ�ʱ�������޸��û�����
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

//ѡ��ȫ����ť��Ӧ
void CUserList::SelAll()
{
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(true);
	}
}

//ȫ����ѡ��ť��Ӧ
void CUserList::SelNone()
{
	for(m_pListItem = m_pListUSER.begin(); m_pListItem != m_pListUSER.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(false);
	}
}

//��ѡ��ť��Ӧ
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

//����ˢ��
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

	//�����б�
	
	//����б�
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

//дȨ��ģ��
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

	
	//(1) ��������������ΪIDC�ͻ��ṩ�鿴����ͨIDC�йܵ��豸������ͨ�����豸�˿ڵ���������
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(2) ����������������������豸��⡢��ͨ�Բ��ԡ�
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(3) ���������������������������⡣
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(4) ģ��ҵ��������������Web��⡣
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(5) Ӧ�ü�������������ʼ���⡢DNS��⡢NEWS��⡣
	WriteIniFileString("base","entityid",  "_App&_Asp" , "idcbagconfig.ini");
	//(6) ���Ʒ�������������ݿ��⡢����ǽ��⡢�м����⡢���ؾ����⡣
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