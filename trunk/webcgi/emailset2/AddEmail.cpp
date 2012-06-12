//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "AddEmail.h"
#include "TaskList.h"

#include <WTable>
#include <WTableCell>
#include <WTextArea>
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"


#include "WebSession.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

//////////////////////////////////////////////////////////////////////////////////
// start
CSVAddEmail::CSVAddEmail(WContainerWidget * parent):
WContainerWidget(parent)
{
    m_nIndex = -1;

	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_AddMail_Title",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Return",m_formText.szReturn);
			FindNodeValue(ResNode,"IDS_Advance_Option",m_formText.szAdvTitle);
			FindNodeValue(ResNode,"IDS_Basic_Option",m_formText.szGenTitle);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Mail_Edit_Error",m_formText.szErrMail);
			FindNodeValue(ResNode,"IDS_Name_Edit_Error",m_formText.szErrName);
			FindNodeValue(ResNode,"IDS_Name_Edit_Error1",m_formText.szErrName1);
			FindNodeValue(ResNode,"IDS_Receive_Mail",m_formText.szMail);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szName);
			FindNodeValue(ResNode,"IDS_Email_Template",m_formText.szTemplate);
			FindNodeValue(ResNode,"IDS_Plan",m_formText.szSchedule);
			FindNodeValue(ResNode,"IDS_Description",m_formText.szDesciption);
			FindNodeValue(ResNode,"IDS_AddMail_Name_Description",m_formText.szNameDes);
			FindNodeValue(ResNode,"IDS_AddMail_Disable_Description",m_formText.szDisableDes);
			FindNodeValue(ResNode,"IDS_AddMail_Template_Description",m_formText.szTemplateDes);
			FindNodeValue(ResNode,"IDS_AddMail_Mail_Description",m_formText.szMailDes);
			FindNodeValue(ResNode,"IDS_AddMail_Schedule_Description",m_formText.szScheduleDes);
			FindNodeValue(ResNode,"IDS_AddMail_Description_Description",m_formText.szDesciptionDes);
			FindNodeValue(ResNode,"IDS_Cancel",strCancel);
			FindNodeValue(ResNode,"IDS_Save",strSave);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Email_Set",strEmailSet);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_Cancel_Add_User",strCancelAdd);
			FindNodeValue(ResNode,"IDS_Save_Add_Email",strSaveEmail);
		}
		CloseResource(objRes);
	}

	//new WText("<div id='view_panel' class='panel_view'>", this);
	bEditAdd = false;

    showMainForm();
}

//添加客户端脚本变量
//void CSVAddEmail::AddJsParam(const std::string name, const std::string value)
//{  
//	std::string strTmp("");
//	strTmp += "<SCRIPT language='JavaScript' > var ";
//	strTmp += name;
//	strTmp += "='";
//	strTmp += value;
//	strTmp += "';</SCRIPT>";
//	new WText(strTmp, this);
//}

void CSVAddEmail::ShowHelp()
{
	m_pAddTable->ShowOrHideHelp();
}

//显示界面
void CSVAddEmail::showMainForm()
{
	
	pMainTable = new WSVMainTable(this, m_formText.szTitle,true);

	if(pMainTable->pHelpImg)
	{
		connect(pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}	
	
	m_pAddTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(1,0), Group, m_formText.szTitle);

	
	if(m_pAddTable != NULL && m_pAddTable->GetContentTable() != NULL)
	{
		//标准选项
		m_pAddTable->AppendRows(m_formText.szGenTitle);
		m_pName = new WLineEdit("", m_pAddTable->AppendRowsContent(0,m_formText.szName, m_formText.szNameDes , m_formText.szErrName,true));
		m_pName->setStyleClass("input_text_300");
		
		m_pMailList = new WLineEdit("", m_pAddTable->AppendRowsContent(0,m_formText.szMail, m_formText.szMailDes , m_formText.szErrMail,true));
		m_pMailList->setStyleClass("input_text_300");
		
		m_pDisable = new WCheckBox("", m_pAddTable->AppendRowsContent(0,m_formText.szDisable, m_formText.szDisable , ""));
		
		//高级选项
		m_pAddTable->AppendRows(m_formText.szAdvTitle);
		//Email模版
		WTable *pTemplate = new WTable(m_pAddTable->AppendRowsContent(1, m_formText.szTemplate, m_formText.szTemplateDes, ""));
		pTemplate->setStyleClass("widthauto");

		m_pTemplate = new WComboBox((WContainerWidget*)pTemplate->elementAt(1,2));
		std::list<string> keylist;
		std::list<string>::iterator keyitem;	
		//从TXTTemplate.ini初始化pEmailTemplate()
		if(GetIniFileKeys("Email", keylist, "TXTTemplate.ini"))
		{
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				m_pTemplate->addItem((*keyitem));
			}
		}
		
		//任务计划
		WTable *pSchedule = new WTable(m_pAddTable->AppendRowsContent(1, m_formText.szSchedule, m_formText.szScheduleDes, ""));
		pSchedule->setStyleClass("widthauto");

		m_pSchedule = new WComboBox((WContainerWidget*)pSchedule->elementAt(1,2));    
		//读取调度ini以初始化控件
		GetAllTaskName(tasknamelist);
		//PrintDebugString("GetAllTaskName");
		for(taskname = tasknamelist.begin(); taskname != tasknamelist.end(); taskname++)	
		{
			//PrintDebugString((*taskname).c_str());
			std::string m_pNameStr = *taskname;

			OBJECT hTask = GetTask(m_pNameStr);
			std::string sValue = GetTaskValue("Type", hTask);						

			if(strcmp(sValue.c_str(), "2") == 0)
			{
				PrintDebugString(sValue.c_str());
				PrintDebugString("-------\n");
				m_pSchedule->addItem(m_pNameStr);
			}
		}

		m_pDesciption = new WTextArea("", m_pAddTable->AppendRowsContent(1,m_formText.szDesciption, m_formText.szDesciption , ""));
		m_pDesciption->setStyleClass("input_text_300");

		if(m_pAddTable->GetActionTable() != NULL)
		{
			WTable *pTbl;

			pTbl = new WTable(m_pAddTable->GetActionTable()->elementAt(0, 1));

			WSVButton * pSave = new WSVButton(pTbl->elementAt(0,0), strSave, "button_bg_m_black.png", "", true);
			WObject::connect(pSave, SIGNAL(clicked()), this, SLOT(Save()));

			WSVButton * pBack = new WSVButton(pTbl->elementAt(0, 1), strCancel, "button_bg_m.png", "", false);
			WObject::connect(pBack, SIGNAL(clicked()), this, SLOT(Back()));	
			
			//隐藏按钮
			pTranslateBtn = new WPushButton("翻译", pTbl->elementAt(0,2));
			pExChangeBtn = new WPushButton("刷新", pTbl->elementAt(0,3));

			
			//翻译
			int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
			if(bTrans == 1)
			{
				this->pTranslateBtn->show();
				connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

				this->pExChangeBtn->show();
				connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChangeAdd()));	
			}
			else
			{
				this->pTranslateBtn->hide();
				this->pExChangeBtn->hide();
			}
			

		}
	}

	emit ShowHelp();
}

void CSVAddEmail::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "emailsetRes";
	WebSession::js_af_up += "')";
}

void CSVAddEmail::ExChangeAdd()
{
	
	PrintDebugString("------ExChangeEventAdd------\n");
	emit ExChangeEventAdd();
	
}

//增加时清空数据
void CSVAddEmail::clearContent()
{
	
	//清空调度组合框
	m_pSchedule->clear();
	//读取调度ini以初始化控件
	GetAllTaskName(tasknamelist);
	//PrintDebugString("GetAllTaskName");
	for(taskname = tasknamelist.begin(); taskname != tasknamelist.end(); taskname++)	
	{
		//PrintDebugString((*taskname).c_str());
		std::string m_pNameStr = *taskname;
		
		OBJECT hTask = GetTask(m_pNameStr);
		std::string sValue = GetTaskValue("Type", hTask);						

		if(strcmp(sValue.c_str(), "2") == 0)
		{
			PrintDebugString(sValue.c_str());
			PrintDebugString("-------\n");
			m_pSchedule->addItem(m_pNameStr);
		}
//		m_pSchedule->addItem(*taskname);
	}

	m_nIndex = -1;
    m_pName->setText("");
    m_pMailList->setText("");
    m_pDisable->setUnChecked();
    m_pTemplate->setCurrentIndex(0);
	m_pSchedule->setCurrentIndex(0);
	m_pDesciption->setText("");

	m_pAddTable->HideAllErrorMsg();

	if(m_pAddTable->bShowHelp)		//隐藏帮助
		m_pAddTable->ShowOrHideHelp();

    //m_pTasklist->Reset();

	bEditAdd = true;	
}

//编辑时传数据
void CSVAddEmail::UpdateData(ADD_MAIL_OK addMail)
{
	
	//清空调度组合框
	m_pSchedule->clear();
	//读取调度ini以初始化控件
	GetAllTaskName(tasknamelist);
	//PrintDebugString("GetAllTaskName");
	for(taskname = tasknamelist.begin(); taskname != tasknamelist.end(); taskname++)	
	{
		//PrintDebugString((*taskname).c_str());
		m_pSchedule->addItem(*taskname);
	}

	m_pAddTable->HideAllErrorMsg();
	
	m_pName->setText(addMail.szName);
	m_formText.szEditName = addMail.szName;
	m_pMailList->setText(addMail.szMailList);
	if(addMail.bCheck)
	{
//		PrintDebugString("#####################################\n");	
		m_pDisable->setChecked();
	}
	else
	{
//		PrintDebugString("*************************************\n");
		m_pDisable->setUnChecked();
	}
	m_nIndex = addMail.nIndex;
	
	//PrintDebugString(addMail.szTemplate.c_str());
	//PrintDebugString(addMail.szSchedule.c_str());
	//PrintDebugString(addMail.szDes.c_str());
	m_pTemplate->setCurrentIndexByStr(addMail.szTemplate);
	m_pSchedule->setCurrentIndexByStr(addMail.szSchedule);
	m_pDesciption->setText(addMail.szDes.c_str());
    //m_pTasklist->Reset();

	bEditAdd = false;
	
}

//close按钮响应
void CSVAddEmail::Back()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "Back";
	LogItem.sDesc = strCancelAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//ShowHelp();
    emit BackMain();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//ok按钮响应
void CSVAddEmail::Save()
{
 	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "Save";
	LogItem.sDesc = strSaveEmail;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);
	
OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	ADD_MAIL_OK addMail;
	bool bCheck = 0;
	
	//错误检查
	bool bError = false;
	std::list<string> errorMsgList;

	if (m_pName->text().empty())
    {
		errorMsgList.push_back(m_formText.szErrName);
		bError = true;        
    }
	else
	{
		if(strcmp(m_formText.szEditName.c_str() ,m_pName->text().c_str()) != 0)
		{
			//验证名称是否重复
			std::list<string> keylist;
			std::list<string>::iterator keyitem; 
			if(GetIniFileSections(keylist, "emailAdress.ini"))
			{
				//初始化地址列表。。。
				for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
				{
					string section = (*keyitem);
					string allName = GetIniFileString(section, "Name", "" , "emailAdress.ini");
					if(strcmp(allName.c_str(), m_formText.szEditName.c_str()) == 0)
					{
						continue;
					}
					else
					{
						if(strcmp(allName.c_str(), m_pName->text().c_str()) == 0)
						{
							errorMsgList.push_back(m_formText.szErrName1);
							bError = true;        
						}

					}
				}
			}
		}
	}

    if(!checkEmail())
    {
		errorMsgList.push_back(m_formText.szErrMail);
		bError = true;        
    }
    
	if(bError)
	{
		m_pAddTable->ShowErrorMsg(errorMsgList);
		bEnd = true;	
		goto OPEnd;
	}


	//从用户界面获取数据
	addMail.nIndex = m_nIndex;    
    addMail.szName = m_pName->text();
    addMail.szMailList = m_pMailList->text();
    addMail.bCheck = m_pDisable->isChecked();	
	addMail.szSchedule = m_pSchedule->currentText();
	addMail.szTemplate = m_pTemplate->currentText();
	addMail.szDes = m_pDesciption->text();

 	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	string strOType;
	if(bEditAdd)
	{
		strOType = strTypeAdd;
	}
	else
	{
		strOType = strTypeEdit;
	}
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strEmailSet,m_pMailList->text());

	//提交保存事件
	emit Successful(addMail);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//检查mail的有效性
bool CSVAddEmail::checkEmail()
{

    string szMailList = m_pMailList->text();

    if(szMailList.empty())
        return false;

    char * pTemp1 = NULL, * pTemp2 = NULL;
    
    pTemp1 = strchr(szMailList.c_str(), '@');
    if (!pTemp1)
        return false;
    
    if (*(++pTemp1) == '.')
        return false;
    
    pTemp2 = strchr(pTemp1, '.');
    if (!pTemp2)
        return false;

    return true;
}
