//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "AddPlan.h"
#include "TaskList.h"
#include "mainform.h"
#include "svapi.h"
#include "websession.h"
#include "WTableCell"
#include "../base/OperateLog.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "WSVButton.h"
extern void PrintDebugString(const char *szErrmsg);



//////////////////////////////////////////////////////////////////////////////////
// start
CSVAddPlan::CSVAddPlan(WContainerWidget * parent):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			//添加Resource
			FindNodeValue(ResNode,"IDS_Plan",szTitle);
			FindNodeValue(ResNode,"IDS_Time_Area_Task_Add",m_FormShowText.szAddReTitle);
			FindNodeValue(ResNode,"IDS_Name_Edit_Error",m_FormShowText.szErrorMsg);
			FindNodeValue(ResNode,"IDS_Task_Plan_Name",m_FormShowText.szRunName);
			FindNodeValue(ResNode,"IDS_Task_Plan_Name_Help",m_FormShowText.szRunNameHelp);
			FindNodeValue(ResNode,"IDS_Description",m_FormShowText.szDescript);
			FindNodeValue(ResNode,"IDS_Save",m_FormShowText.szSaveBut);
			FindNodeValue(ResNode,"IDS_Cancel",m_FormShowText.szCancelBut);
			FindNodeValue(ResNode,"IDS_Task_Plan_Name_Same",m_FormShowText.szErrorMsg1);
			FindNodeValue(ResNode,"IDS_General_Check",m_FormShowText.szBasicAdd);
			FindNodeValue(ResNode,"IDS_Advance_Option",m_FormShowText.szAdvanceAdd);
			FindNodeValue(ResNode,"IDS_Week_Help",m_FormShowText.strWeekHelp);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_Time_Area_Task_Plan",strTimeTaskPlan);
			FindNodeValue(ResNode,"IDS_Enable",strAllown);
			FindNodeValue(ResNode,"IDS_Help",strHelp);
			FindNodeValue(ResNode,"IDS_CancelAddInPlan",szCancelAdd);
			FindNodeValue(ResNode,"IDS_SaveAddInPlan",szSaveAddInPlan);
		}
		CloseResource(objRes);
	}

	IsShow = true;
	chgstr = "";
    m_nIndex = -1;
    showMainForm();
}

void CSVAddPlan::Save()
{
	bool bEnd = false;	
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Plan Set";
	LogItem.sHitFunc = "Save";
	LogItem.sDesc = szSaveAddInPlan;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}
	
	ADD_PLAN_OK addPlan;
    bool bCheck = 0;

    addPlan.szName = m_pName->text();

	std::list<string> errorMsgList;

	
    if (addPlan.szName.empty())
    {
		errorMsgList.push_back(m_FormShowText.szErrorMsg);
		AddRangeTable->ShowErrorMsg(errorMsgList);
		//m_pPlanNameError->show();
		bEnd = true;	
		goto OPEnd;
    }
	//else
	//{
	//	AddRangeTable -> HideAllErrorMsg();
	//	//m_pPlanNameError-> hide();
	//}

	std::string str1 = m_pTasklist->m_pStart[1]->text();
	//Jansion.zhou 2006-12-25
    //m_pErrMsg->setText("");
    //m_pErrMsg->hide();

    addPlan.nIndex = m_nIndex;

	std::list<string> tasknamelist;
	std::list<string>::iterator m_pItem;
	bool IsSave = false;
	bool IsConn = GetAllTaskName(tasknamelist);
	
	if(IsConn)
	{
		OutputDebugString("----------------isconn true------------------\n");
		for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
		{
			std::string str = *m_pItem;
			if(strcmp(str.c_str(), addPlan.szName.c_str()) == 0)
			{
				IsSave = true;
				break;
			}
		}
		
		
		if(strcmp(chgstr.c_str(), "") == 0)
		{
			if(!IsSave)
			{
				OutputDebugString("----------------Issave false------------------\n");
				OBJECT hTask = CreateTask(addPlan.szName);
				
				SetTaskValue("Type", m_FormShowText.szPlanTypeRel, hTask);
				char buf[256];
				for(int i = 0; i < 7; i++)
				{

					itoa(i, buf, 10);
					std::string temp = m_pTasklist->m_pStart[i]->text();
					std::string temp1 = "start";
					temp1 += buf;
					SetTaskValue(temp1, temp, hTask);
					
					temp = m_pTasklist->m_pEnd[i]->text();
					temp1 = "end";
					temp1 += buf;
					SetTaskValue(temp1, temp, hTask);
					
					temp1 = "Allow";
					temp1 += buf;

					std::string temp3 = m_pTasklist->m_pCombo[i]->currentText();
					if(strcmp(temp3.c_str(), strAllown.c_str()) == 0)
					{
						SetTaskValue(temp1, m_FormShowText.szStatusAllow, hTask);
					}
					else
					{
						SetTaskValue(temp1, m_FormShowText.szStatusDeny, hTask);
					}
				}
				SetTaskValue("Description", textarea->text(), hTask);
				SubmitTask(hTask);

				//Jansion.zhou 2006-12-25
				//m_pErrMsg->setText("");
				//m_pErrMsg->hide();
				addPlan.nIndex = m_nIndex;

				//插记录到UserOperateLog表
				string strUserID = GetWebUserID();
				TTime mNowTime = TTime::GetCurrentTimeEx();
				OperateLog m_pOperateLog;
				m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeAdd,strTimeTaskPlan,m_pName->text());

				emit Successful(addPlan);
			}
			else
			{
OutputDebugString("----------------Issave true------------------\n");
				//Jansion.zhou 2006-12-25
				//m_pErrMsg->setText(m_FormShowText.szErrorMsg1);
				//m_pErrMsg->show();

				errorMsgList.push_back(m_FormShowText.szErrorMsg1);
				AddRangeTable->ShowErrorMsg(errorMsgList);
			}
		}
		else
		{

			std::string str;
			for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
			{
				str = *m_pItem;
				if(strcmp(str.c_str(), addPlan.szName.c_str()) == 0)
				{
					if(strcmp(str.c_str(), chgstr.c_str()) != 0)
					{
						IsSave = true;
						break;
					}
					else
					{				
						IsSave = false;
						break;
					}
				}
			}

			
			if(!IsSave)
			{
				OutputDebugString("----------------Issave00 false------------------\n");
				OBJECT hTask = GetTask(chgstr);
				
				SetTaskValue("Type", m_FormShowText.szPlanTypeRel, hTask);
				char buf[256];
				for(int i = 0; i < 7; i++)
				{
					itoa(i, buf, 10);
					std::string temp = m_pTasklist->m_pStart[i]->text();
					std::string temp1 = "start";
					temp1 += buf;
					SetTaskValue(temp1, temp, hTask);
					
					temp = m_pTasklist->m_pEnd[i]->text();
					temp1 = "end";
					temp1 += buf;
					SetTaskValue(temp1, temp, hTask);

					temp1 = "Allow";
					temp1 += buf;

					std::string temp3 = m_pTasklist->m_pCombo[i]->currentText();
					if(strcmp(temp3.c_str(), strAllown.c_str()) == 0)
					{
						SetTaskValue(temp1, m_FormShowText.szStatusAllow, hTask);
					}
					else
					{
						SetTaskValue(temp1, m_FormShowText.szStatusDeny, hTask);
					}
				}
				SetTaskValue("Description", textarea->text(), hTask);
				EditTask(hTask,addPlan.szName);

				//Jansion.zhou 2006-12-25
				//m_pErrMsg->setText("");
				//m_pErrMsg->hide();

				addPlan.nIndex = m_nIndex;

				//插记录到UserOperateLog表
				string strUserID = GetWebUserID();
				TTime mNowTime = TTime::GetCurrentTimeEx();
				OperateLog m_pOperateLog;
				m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeEdit,strTimeTaskPlan,m_pName->text());

				chgstr = "";
				emit Successful(addPlan);
			}
			else
			{
				OutputDebugString("----------------Issave000 true------------------\n");
				//Jansion.zhou 2006-12-25
				//m_pErrMsg->setText(m_FormShowText.szErrorMsg1);
				//m_pErrMsg->show();

				errorMsgList.push_back(m_FormShowText.szErrorMsg1);
				AddRangeTable->ShowErrorMsg(errorMsgList);
			}
		}
	}
	else
	{

	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVAddPlan::Cancel()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Plan Set";
	LogItem.sHitFunc = "Cancel";
	LogItem.sDesc = szCancelAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	emit SCancel();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

bool CSVAddPlan::checkPlan()
{
    return true;
}

void CSVAddPlan::showErrorMsg(string &szErrMsg)
{
	//Jansion.zhou 2006-12-25
    //m_pErrMsg->setText(szErrMsg);
    //m_pErrMsg->show();

	//AddRangeTable->
}

void CSVAddPlan::showMainForm()
{
	
	string szMon,szThurs,szWed,szTues,szFri,szSat,szSun,szDisable,szEnable,szfrom,szTo,szAddRelPlanBut;
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Time_Area_Task_Add",szAddRelPlanBut);

			FindNodeValue(ResNode,"IDS_Disable",szDisable);
			FindNodeValue(ResNode,"IDS_Enable",szEnable);
			FindNodeValue(ResNode,"IDS_Monday",szMon);
			FindNodeValue(ResNode,"IDS_Tuesday",szThurs);
			FindNodeValue(ResNode,"IDS_Wednesday",szWed);
			FindNodeValue(ResNode,"IDS_Thursday",szTues);
			FindNodeValue(ResNode,"IDS_Friday",szFri);
			FindNodeValue(ResNode,"IDS_Saturday",szSat);
			FindNodeValue(ResNode,"IDS_Sunday",szSun);
			FindNodeValue(ResNode,"IDS_From",szfrom);
			FindNodeValue(ResNode,"IDS_To",szTo);
		}
		CloseResource(objRes);
	}

	
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);


OutputDebugString("----------------strUser----------------\n");
	pMainTable = new WSVMainTable(this, szTitle, true);
	if(pMainTable->pHelpImg)
	{
		connect(pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(AddPlanHelp()));
	}
	

	AddRangeTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(1,0), Group, m_FormShowText.szAddReTitle);

	if (AddRangeTable->GetContentTable() != NULL)
	{
		AddRangeTable->AppendRows(m_FormShowText.szBasicAdd);

		m_pName = new WLineEdit("", AddRangeTable->AppendRowsContent(0, m_FormShowText.szRunName+"<span class =required>*</span>", m_FormShowText.szRunNameHelp, m_FormShowText.szErrorMsg));
		//m_pName -> setTextSize(50);
		m_pName->resize(WLength(300, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pName->setStyleClass("input_text");
		
		new WText("", AddRangeTable->AppendRowsContent(0, "", "", m_FormShowText.szErrorMsg1));

		m_pTasklist = new CTaskList(NULL, AddRangeTable,m_FormShowText.strWeekHelp);
		/*
		m_pCombo[0] = new WComboBox(RecList->elementAt(0, 1));
		m_pCombo[0]->addItem(szEnable);
		m_pCombo[0]->addItem(szDisable);
		pFrom[0] = new WText(szfrom, RecList->elementAt(0, 2));
		m_pStart[0] = new WLineEdit("00:00", RecList->elementAt(0, 3));
		m_pStart[0]->setStyleClass("input_text");
		pTo[0] = new WText(szTo, RecList->elementAt(0, 4));
		m_pEnd[0] = new WLineEdit("23:59", RecList->elementAt(0, 5));
		m_pEnd[0]->setStyleClass("input_text");

		for (int i=1; i<7; i++)
		{
			WTable *RecList = new WTable(AddRangeTable->AppendRowsContent(0, DayType[i], "", ""));
			RecList->setStyleClass("widthauto");
			m_pCombo[i] = new WComboBox(RecList->elementAt(0, 1));
			m_pCombo[i]->addItem(szEnable);
			m_pCombo[i]->addItem(szDisable);
			pFrom[i] = new WText(szfrom, RecList->elementAt(0, 2));
			m_pStart[i] = new WLineEdit("00:00", RecList->elementAt(0, 3));
			m_pStart[i]->setStyleClass("input_text");
			pTo[i] = new WText(szTo, RecList->elementAt(0, 4));
			m_pEnd[i] = new WLineEdit("23:59", RecList->elementAt(0, 5));
			m_pEnd[i]->setStyleClass("input_text");
		}
		*/
		AddRangeTable->AppendRows(m_FormShowText.szAdvanceAdd);
		textarea = new WTextArea("", AddRangeTable->AppendRowsContent(1, m_FormShowText.szDescript, "", ""));
		textarea->resize(WLength(400, WLength::Pixel),WLength(100, WLength::Pixel));
		textarea->setStyleClass("input_text");

		AddRangeTable->ShowOrHideHelp();
		AddRangeTable->HideAllErrorMsg();
	}

	if (AddRangeTable->GetActionTable() != NULL)
	{
		WTable *pGroupOperate = new WTable(AddRangeTable->GetActionTable()->elementAt(0, 1));
		pGroupOperate->setStyleClass("widthauto");

		WSVButton * pSave = new WSVButton(pGroupOperate->elementAt(0,0),m_FormShowText.szSaveBut,"button_bg_m_black.png",m_FormShowText.szSaveBut,true);
		WObject::connect(pSave, SIGNAL(clicked()), this, SLOT(Save()));
		//pGroupOperate->elementAt(0,0)-> addWidget(pSave);

		WSVButton * pCancel = new WSVButton(pGroupOperate->elementAt(0,1),m_FormShowText.szCancelBut,"button_bg_m.png",m_FormShowText.szCancelBut,false);
		WObject::connect(pCancel, SIGNAL(clicked()), this, SLOT(Cancel()));

		//pGroupOperate->elementAt(0,0)-> addWidget(pCancel);
		//pGroupOperate->elementAt(0,0)->setContentAlignment(AlignCenter);
		
	}

	//new WText("</div>");

	//Jansion.zhou 2006-12-25
 //   WTable * TitleTable = new WTable(this);
	//TitleTable->setStyleClass("t3");
	//m_pErrMsg = new WText("", (WContainerWidget *)TitleTable->elementAt(0,0));
 //   m_pErrMsg->decorationStyle().setForegroundColor(Wt::red);
 //   m_pErrMsg->hide();

	//Jansion.zhou 2006-12-25
	////connect svdb failure WText
	//m_pConnErr = new WText("", (WContainerWidget *)TitleTable->elementAt(0, 0));
	//m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	//m_pConnErr ->hide();
	



	new WText("</div>", this);

	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);
}


//添加客户端脚本变量
void CSVAddPlan::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CSVAddPlan::clearContent()
{
    m_nIndex = -1;
    m_pName->setText("");
    textarea->setText("");
	//jansion.zhou 2006-12-25
	//m_pErrMsg->setText("");

    m_pTasklist->Reset();

	AddRangeTable->HideAllErrorMsg();
}

void CSVAddPlan::UpdateData(ADD_PLAN_OK addMail)
{	
    m_pName->setText(addMail.szName);
	
	chgstr = addMail.szName;
	OBJECT hTask = GetTask(addMail.szName);


	for(int i = 0; i < 7; i++)
	{
		char buf[256];
		std::string temp1 = "Allow";
		itoa(i, buf, 10);
		temp1 += buf;
		std::string temp = GetTaskValue(temp1, hTask);
		if(strcmp(temp.c_str(), m_FormShowText.szStatusAllow.c_str()) == 0)
		{
			m_pTasklist -> m_pCombo[i]->setCurrentIndex(0);
		}
		else
		{
			m_pTasklist -> m_pCombo[i]->setCurrentIndex(1);
		}

		temp1 = "start";
		temp1 += buf;
		temp = GetTaskValue(temp1, hTask);
		m_pTasklist->m_pStart[i] -> setText(temp);

		temp1 = "end";
		temp1 += buf;
		temp = GetTaskValue(temp1, hTask);
		m_pTasklist->m_pEnd[i] ->setText(temp);
	
	}
	std::string temp1 = "Description";
	std::string temp = GetTaskValue(temp1, hTask);
	textarea -> setText(temp);

}


void CSVAddPlan::showPlanList()
{
	pShow -> show();
	pHide -> hide();
	table -> show();
}

void CSVAddPlan::hidePlanList()
{
	pShow -> hide();
	pHide -> show();
	table -> hide();
}

void CSVAddPlan::AshowPlanList()
{
	pShow1 -> show();
	pHide1 -> hide();
	table1 -> show();
}

void CSVAddPlan::AhidePlanList()
{
	pShow1 -> hide();
	pHide1 -> show();
	table1 -> hide();
}

void CSVAddPlan::AddPlanHelp()
{
	AddRangeTable->ShowOrHideHelp();
//	if(IsShow)
//	{
//		m_pPlanNameHelp ->show();
//		m_pSuHelp ->show();
///*		m_pMoHelp ->show();
//		m_pTuHelp ->show();
//		m_pWeHelp ->show();
//		m_pThHelp ->show();
//		m_pFrHelp ->show();
//		m_pSaHelp ->show();
//*/		IsShow = false;
//	}
//	else
//	{
//		m_pPlanNameHelp ->hide();
//		m_pSuHelp ->hide();
///*		m_pMoHelp ->hide();
//		m_pTuHelp ->hide();
//		m_pWeHelp ->hide();
//		m_pThHelp ->hide();
//		m_pFrHelp ->hide();
//		m_pSaHelp ->hide();
//*/		IsShow = true;
//	}
}



