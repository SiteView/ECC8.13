#include "stdafx.h"
#include "AddPhone.h"

//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WebSession.h"
#include "svapi.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

extern void PrintDebugString(const char*);

CSVAddPhone::CSVAddPhone(WContainerWidget * parent /* = 0 */):
WContainerWidget(parent)
{
	IsHelp = false;
	OutputDebugString("-------初始化1------\n");
	loadString();
	OutputDebugString("-------初始化2------\n");
    initForm();
	OutputDebugString("-------初始化3------\n");
}

void CSVAddPhone::initForm()
{	 
	string ret;
	
	
	WTable * TitleTable = new WTable(this);
	TitleTable->setStyleClass("t3");
	
	//connect svdb failure WText
	m_pConnErr = new WText("", (WContainerWidget *)TitleTable->elementAt(0, 0));
	m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	m_pConnErr ->hide();

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)TitleTable->elementAt(0, 1));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)TitleTable->elementAt(0, 1));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)TitleTable->elementAt(0,1));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChangeAdd()));	
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)TitleTable->elementAt(0, 1));

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}

	//main form help button
	/*m_pHelpImg = new WImage("../Images/help.gif", (WContainerWidget *)TitleTable->elementAt( 0, 1));
	m_pHelpImg ->setStyleClass("helpimg");
	m_pHelpImg->setToolTip("帮助");
	TitleTable->elementAt(0, 1) -> setContentAlignment(AlignTop | AlignRight);
	WObject::connect(m_pHelpImg, SIGNAL(clicked()), this, SLOT(AddPhoneHelp()));
	addWidget(m_pHelpImg);*/
				
	WSVMainTable *mainTable = new WSVMainTable(this,"",true);
	if (mainTable->pHelpImg)
	{
		connect(mainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(AddPhoneHelp()));
	}
	m_pGeneral = new WSVFlexTable((WContainerWidget *)mainTable->GetContentTable()->elementAt(1,0), Group, m_formText.szAddTitle);
	m_pGeneral->AppendRows("");
	m_pName = new WLineEdit("", (WContainerWidget*)m_pGeneral->AppendRowsContent(0,m_formText.szNameDes1+"<span class =required>*</span>",m_formText.szHelpNameDes,m_formText.szErrorNameDes));
	m_pName->setStyleClass("input_text");
	//用户名不能为空
	m_Err.m_pNameErr = new WText("", (WContainerWidget*)m_pGeneral->AppendRowsContent(0,"","",""));
	m_Err.m_pNameErr->setStyleClass("table_data_input_error");
	if (m_Err.m_pNameErr)
	{
		m_Err.m_pNameErr->setText(m_formText.szErrName);
		m_Err.m_pNameErr->hide();
	}
	//手机号
	m_pPhone = new WLineEdit("", (WContainerWidget*)m_pGeneral->AppendRowsContent(0,m_formText.szPhoneDes1+"<span class =required>*</span>",m_formText.szHelpPhoneDes,""));
	m_pPhone->setStyleClass("input_text");
	//手机号不能为空
	m_Err.m_pPhoneErr = new WText("" , (WContainerWidget*)m_pGeneral->AppendRowsContent(0,"","",""));
	m_Err.m_pPhoneErr->setStyleClass("table_data_input_error");
	if (m_Err.m_pPhoneErr)
	{
		m_Err.m_pPhoneErr->setText(m_formText.szErrPhone);
		m_Err.m_pPhoneErr->hide();
	}
	m_pDisable = new WCheckBox(m_formText.szDisable, (WContainerWidget*)m_pGeneral->AppendRowsContent(0,"",m_formText.szHelpDisableDes,""));
	m_pTemplate = new WComboBox((WContainerWidget*)m_pGeneral->AppendRowsContent(0,m_formText.szTemplateDes1,m_formText.szHelpTemplateDes,""));
	m_pTemplate->setStyleClass("input_text");
	std::list<string> keylist;
	std::list<string>::iterator keyitem;	
	//从TXTTemplate.ini初始化pEmailTemplate()
	if(GetIniFileKeys("Email", keylist, "TXTTemplate.ini"))
	{
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
		{
			//从ini读数据
			//strTmp = GetIniFileString("Email", (*keyitem), "", "TXTTemplate.ini");
			//pEmailTemplate->addItem(strTmp.c_str());
			m_pTemplate->addItem((*keyitem));
		}
	}
	m_pSchedule = new WComboBox((WContainerWidget*)m_pGeneral->AppendRowsContent(0,m_formText.szTaskDes1,m_formText.szHelpTaskDes,""));
	m_pSchedule->setStyleClass("input_text");
	std::list<string> tasknamelist;
	std::list<string>::iterator m_pItem;
	GetAllTaskName(tasknamelist);

	for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
	{
		std::string m_pNameStr = *m_pItem;

		OBJECT hTask = GetTask(m_pNameStr);
		std::string sValue = GetTaskValue("Type", hTask);

		char aaa[2000];
		sprintf(aaa, "%s--%s\n",m_pNameStr.c_str(),sValue.c_str());
		OutputDebugString(aaa);
		//if(strcmp(sValue.c_str(), m_formText.b.c_str()) == 0)
		//if(strcmp(sValue.c_str(), "1") == 0)
		///	{
		m_pSchedule -> addItem(m_pNameStr);
		//	}
	}

	WTable * pButTable = new WTable(m_pGeneral->GetActionTable()->elementAt(0, 1));

	WSVButton * pSave = new WSVButton(pButTable->elementAt(0,0), m_formText.szSave, "button_bg_m_black.png", "", true);

	WObject::connect(pSave, SIGNAL(clicked()), this, SLOT(Save()));

 
	// 返回
	WSVButton * pBack = new WSVButton(pButTable->elementAt(0,1), m_formText.szBack, "button_bg_m.png", "", false);
	WObject::connect(pBack, SIGNAL(clicked()), this, SLOT(Back()));
	m_pGeneral->ShowOrHideHelp();
	m_pGeneral->HideAllErrorMsg();
	OutputDebugString("-------结束------\n");
}

void CSVAddPhone::ExChangeAdd()
{
	PrintDebugString("------ExChangeAddEvent------\n");
	emit ExChangeAddEvent();
}
void CSVAddPhone::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "smssetRes";
	WebSession::js_af_up += "')";
}


void CSVAddPhone::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
/*			//添加Resource
			bool bAdd = AddNodeAttrib(ResNode,"IDS_SMS_Receive_Phone_Title","添加短信接收手机号设置");
			bAdd = AddNodeAttrib(ResNode,"IDS_SMS_Receive_Phone_Name_Desciption","名称：此名称将在添加短信报警时显示在“报警接收手机号" \
						"”列表中以对应本名称所代表的手机号码");
			bAdd = AddNodeAttrib(ResNode,"IDS_Disable_Desciption","禁止：选择此项后，报警将不发送到指定的手机上");
			bAdd = AddNodeAttrib(ResNode,"IDS_Receive_Phone_Help","接收手机号：允许多个手机，各手机号之间用英文逗号分隔");
			bAdd = AddNodeAttrib(ResNode,"IDS_SMS_Template_Help","短信模板：当选择一个模板后，此模板将被用于发送短信信息");
			bAdd = AddNodeAttrib(ResNode,"IDS_Task_Plan_Help","执行计划：设定执行计划允许的时间，如：允许星期一，从10:00到22:00");
			bAdd = AddNodeAttrib(ResNode,"IDS_Phone_Number_NO_Empty","[ 手机号码不能为空 ]");
			bAdd = AddNodeAttrib(ResNode,"IDS_Phone_Name_NO_Empty","[ 名称不能为空 ]");
			bAdd = AddNodeAttrib(ResNode,"IDS_Plan","计划");
			bAdd = AddNodeAttrib(ResNode,"IDS_Name_Repeat_Error","名称重复，请选择其他的名称");
			bAdd = AddNodeAttrib(ResNode,"IDS_Phone_Number_Config","手机号码设置");
			bAdd = AddNodeAttrib(ResNode,"IDS_Phone_Number_Same","存在同名电话");
			bAdd = AddNodeAttrib(ResNode,"IDS_Send_Phone_SMS_Ing","正在发送手机短信...");
			bAdd = AddNodeAttrib(ResNode,"IDS_Test_Phone_SMS_Success","测试短信发送成功...");
			bAdd = AddNodeAttrib(ResNode,"IDS_Test_Phone_SMS_Fail","测试短信发送失败...");
*/			
			FindNodeValue(ResNode,"IDS_SMS_Receive_Phone_Title",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szNameDes1);
			FindNodeValue(ResNode,"IDS_SMS_Receive_Phone_Name_Desciption",m_formText.szHelpNameDes);
			FindNodeValue(ResNode,"IDS_Name_Repeat_Error",m_formText.szErrorNameDes);
			FindNodeValue(ResNode,"IDS_SMS_Receive_Phone_Name_Desciption",m_formText.szNameDes);
			FindNodeValue(ResNode,"IDS_Disable_Desciption",m_formText.szDisableDes);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Receive_Phone",m_formText.szPhoneDes1);
			FindNodeValue(ResNode,"IDS_Receive_Phone_Help",m_formText.szHelpPhoneDes);
			FindNodeValue(ResNode,"IDS_SMS_Template",m_formText.szTemplateDes1);
			FindNodeValue(ResNode,"IDS_SMS_Template_Help",m_formText.szHelpTemplateDes);
			FindNodeValue(ResNode,"IDS_Advance_Option",m_formText.szAdvTitleDes);
			FindNodeValue(ResNode,"IDS_Plan",m_formText.szTaskDes1);
			FindNodeValue(ResNode,"IDS_Task_Plan_Help",m_formText.szHelpTaskDes);
			FindNodeValue(ResNode,"IDS_Phone_Number_Config",m_formText.szAddTitle);
			FindNodeValue(ResNode,"IDS_Phone_Number_Same",m_formText.szErrorMsg1);
			FindNodeValue(ResNode,"IDS_Send_Phone_SMS_Ing",m_formText.szSending);
			FindNodeValue(ResNode,"IDS_Test_Phone_SMS_Success",m_formText.szSendSuc);
			FindNodeValue(ResNode,"IDS_Test_Phone_SMS_Fail",m_formText.szSendFail);
			FindNodeValue(ResNode,"IDS_Connect_SVDB_Fail",m_formText.szConnErr);
			FindNodeValue(ResNode,"IDS_Receive_Phone_Help",m_formText.szPhoneDes);
			FindNodeValue(ResNode,"IDS_SMS_Template_Help",m_formText.szTemplateDes);
			FindNodeValue(ResNode,"IDS_Advance_Option",m_formText.szAdvTitleDes);
			FindNodeValue(ResNode,"IDS_Task_Plan_Help",m_formText.szTaskDes);
			FindNodeValue(ResNode,"IDS_Save",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_Cancel",m_formText.szBack);
			FindNodeValue(ResNode,"IDS_Phone_Number_NO_Empty",m_formText.szErrPhone);
			FindNodeValue(ResNode,"IDS_Phone_Name_NO_Empty",m_formText.szErrName);
			FindNodeValue(ResNode,"IDS_Plan",m_formText.szPlanLabel);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_SMS_Config",strSMSConfig);
			FindNodeValue(ResNode,"IDS_Save_Add",strSaveAdd);
			FindNodeValue(ResNode,"IDS_Cancel_Add1",strCancelAdd);
		}
//		SubmitResource(objRes);
		CloseResource(objRes);
	}
/*
    m_formText.szTitle = "添加短信接收手机号设置";
    m_formText.szNameDes = "名称：此名称将在添加短信报警时显示在“报警接收手机号" \
        "”列表中以对应本名称所代表的手机号码";
    m_formText.szDisableDes = "禁止：选择此项后，报警将不发送到指定的手机上";
    m_formText.szDisable = "禁止";
    m_formText.szPhoneDes = "接收手机号：允许多个手机，各手机号之间用英文逗号分隔";
    m_formText.szTemplateDes = "短信模板：当选择一个模板后，此模板将被用于发送短信信息";
    m_formText.szAdvTitleDes = "高级选项";
    m_formText.szTaskDes = "执行计划：设定执行计划允许的时间，如：允许星期一，从10:00到22:00";
    m_formText.szSave = "保存";
    m_formText.szBack = "取消";
    m_formText.szErrPhone = " [ 手机号码不能为空 ] ";
    m_formText.szErrName = " [ 名称不能为空 ] ";
	m_formText.szPlanLabel = "计划";*/
}

void CSVAddPhone::Save()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "Save";
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

	m_Err.m_pNameErr->hide();
	m_Err.m_pPhoneErr->hide();
	m_pGeneral->HideAllErrorMsg();
	std::list<string> sectionlist;
	bool IsSave = GetIniFileSections(sectionlist, "smsconfig.ini");
	if(IsSave)
	{
		m_phone.szName = m_pName->text();
		m_phone.szPhone = m_pPhone->text();
		m_phone.szPlan = m_pSchedule->currentText();
		m_phone.bDisable = m_pDisable->isChecked();
		m_phone.szTemplet = m_pTemplate->currentText();

		bool bErr = false;

		if (m_phone.szName.empty())
		{ 
			m_Err.m_pNameErr->show();
			bErr = true;
		}

		if (m_phone.szPhone.empty())
		{        
			m_Err.m_pPhoneErr->show();
			bErr = true;
		}

		//名称重复
		if((strcmp(m_phone.szName.c_str(), m_pEditPhoneName.c_str())) != 0)
		{
			std::list<string> sectionlist;
			std::list<string>::iterator m_sItem;
			GetIniFileSections(sectionlist, "smsphoneset.ini");

			for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
			{		
				std::string section = *m_sItem;
				std::string name = GetIniFileString(section, "Name", "", "smsphoneset.ini");
				if(strcmp(name.c_str(),m_phone.szName.c_str()) == 0)
				{
					errorTest(m_formText.szErrorNameDes);
					bErr = true;
					break;
				}
			}
		}

		if ( bErr )
		{
			bEnd = true;	
			goto OPEnd;
		}

		//m_pErrorName->hide();
		m_Err.m_pNameErr->hide();
		m_Err.m_pPhoneErr->hide();
 
		//插记录到UserOperateLog表
		string strUserID = GetWebUserID();
		TTime mNowTime = TTime::GetCurrentTimeEx();
		OperateLog m_pOperateLog;
		string strOType;
		if(chgstr == "")
		{
			strOType = strTypeAdd;
		}
		else
		{
			strOType = strTypeEdit;
		}
		m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strSMSConfig,m_phone.szName);

		OutputDebugString("------------SavePhone(m_phone)--------------------");
		emit SavePhone(m_phone);
	}
	else
	{
		//m_pConnErr->setText(m_formText.szConnErr);
		//m_pConnErr->show();
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}


void CSVAddPhone::Back()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "Back";
	LogItem.sDesc = strCancelAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	clearData();
    emit BackTo();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVAddPhone::setProperty(SAVE_PHONE_LIST * phone)
{
	m_pEditPhoneName = phone->szName;

	m_phone.id = phone->id;
    m_phone.bDisable = phone->bDisable;
    m_phone.nIndex = phone->nIndex;
    m_phone.szName = phone->szName;
    m_phone.szPhone = phone->szPhone;
	m_phone.szTemplet = phone->szTemplet;

    m_pName->setText(m_phone.szName);
    m_pPhone->setText(m_phone.szPhone);
    m_pDisable->setChecked(m_phone.bDisable);
	
	int i=0;
	for(i;i<m_pTemplate->count();i++)
	{
		if(strcmp(phone->szTemplet.c_str(),m_pTemplate->itemText(i).c_str()) == 0)
		{
			m_pTemplate->setCurrentIndex(i);
			return;
		}
	}


	int itemnum = m_pSchedule->count();
	for(int i = 0; i < itemnum; i++)
	{
		string temp = m_pSchedule->itemText(i);
		if(strcmp(temp.c_str(), phone->szPlan.c_str()) == 0)
		{
			m_pSchedule->setCurrentIndex(i);
		}
	}

	IsHelp = true;
	/*m_pHelpName->hide();
	m_pHelpPhone->hide();
	m_pHelpDisabled->hide();
	m_pHelpTemplate->hide();
	m_pHelpPlan->hide();
	m_pErrorName->hide();
	m_pConnErr->hide();*/
    m_Err.m_pNameErr->hide();
    m_Err.m_pPhoneErr->hide();
}

void CSVAddPhone::clearData()
{
	m_pSchedule->clear();
	std::list<string> tasknamelist;
	std::list<string>::iterator m_pItem;
	GetAllTaskName(tasknamelist);

	for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
	{
		std::string m_pNameStr = *m_pItem;
		
		OBJECT hTask = GetTask(m_pNameStr);
		std::string sValue = GetTaskValue("Type", hTask);
		
		//if(strcmp(sValue.c_str(), m_formText.szPlanTypeRel.c_str()) == 0)
		if(strcmp(sValue.c_str(), "2") == 0)
		{
			m_pSchedule -> addItem(m_pNameStr);
		}
	}
	OutputDebugString("-----------clearData---------------------------\n");
	IsHelp = true;
	/*m_pHelpName ->hide();
	m_pHelpPhone ->hide();
	m_pHelpDisabled ->hide();
	m_pHelpTemplate ->hide();
	m_pHelpPlan ->hide();
	m_pErrorName->hide();*/
    m_pName->setText("");
    m_pPhone->setText("");
    m_pDisable->setChecked(false);
    m_Err.m_pNameErr->hide();
    m_Err.m_pPhoneErr->hide();//wenbo
}
void CSVAddPhone::showAddPhoneList()
{
	pShow -> show();
	pHide -> hide();
	pTable -> show();
}

void CSVAddPhone::hideAddPhoneList()
{
	pShow -> hide();
	pHide -> show();
	pTable -> hide();
}

void CSVAddPhone::AddPhoneHelp()
{
	if(IsHelp)
	{
		/*m_pHelpName ->show();
		m_pHelpPhone->show();
		m_pHelpDisabled->show();
		m_pHelpTemplate->show();
		m_pHelpPlan->show();*/
		IsHelp = false;
	}
	else
	{
		//m_pHelpName ->hide();
		//m_pHelpPhone ->hide();
		//m_pHelpDisabled->hide();
		//m_pHelpTemplate->hide();
		//m_pHelpPlan->hide();
		IsHelp = true;
	}
	m_pGeneral->ShowOrHideHelp();
}

void CSVAddPhone::TestSMS()
{
	Sleep(1000);
	pTestShowInfo ->setText(m_formText.szSendSuc);
}

void CSVAddPhone::TestSMSing()
{
	pTestShowInfo ->setText(m_formText.szSending);

}

void CSVAddPhone::errorTest(const string &errorMsg)
{
	m_pGeneral->HideAllErrorMsg();

	std::list<string> errorMsgList;
	errorMsgList.push_back(errorMsg);
	m_pGeneral->ShowErrorMsg(errorMsgList);
}