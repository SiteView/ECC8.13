/*************************************************
*  @file AddAbsolutePlan.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/
//#include "addabsoluteplan.h"
#include "addplan.h"

#include "mainform.h"
#include "TaskList1.h"
#include "svapi.h"
#include "WTableCell"
#include "WSVButton.h"
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "websession.h"
#include "../base/OperateLog.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
extern void PrintDebugString(const char *szErrmsg);


/******************************************************************
参数：
	parent：父容器
功能：
	构造函数
*******************************************************************/
CSVAddAbsolutePlan::CSVAddAbsolutePlan(WContainerWidget * parent):
WContainerWidget(parent)
{
	//加载资源文件
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Time_Task_Add",m_FormShowText.szAddAdTitle);
			FindNodeValue(ResNode,"IDS_Plan",szTitle);

			FindNodeValue(ResNode,"IDS_Name_Edit_Error",m_FormShowText.szErrorMsg);
			FindNodeValue(ResNode,"IDS_Task_Plan_Name",m_FormShowText.szRunName);
			FindNodeValue(ResNode,"IDS_Task_Plan_Name_Help",m_FormShowText.szRunNameHelp);
			FindNodeValue(ResNode,"IDS_Description",m_FormShowText.szDescript);
			FindNodeValue(ResNode,"IDS_Save",m_FormShowText.szSaveBut);
			FindNodeValue(ResNode,"IDS_Cancel",m_FormShowText.szCancelBut);
			FindNodeValue(ResNode,"IDS_Task_Plan_Name_Same",m_FormShowText.szErrorMsg1);
			FindNodeValue(ResNode,"IDS_General_Check",m_FormShowText.szBasicAdd);
			FindNodeValue(ResNode,"IDS_Advance_Option",m_FormShowText.szAdvanceAdd);
			FindNodeValue(ResNode,"IDS_Week_Help_Absolute",m_FormShowText.strWeekHelp);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_Time_Task_Plan",strTimeTaskPlan);
			FindNodeValue(ResNode,"IDS_Enable",strAllown);
			FindNodeValue(ResNode,"IDS_Help",strHelp);
			FindNodeValue(ResNode,"IDS_SaveAddAbPlan",szSaveAddAbPlan);
			FindNodeValue(ResNode,"IDS_CancelAddAbPlan",szCancelAdd);



			//
			//FindNodeValue(ResNode,"IDS_Disable",szDisable);
			//FindNodeValue(ResNode,"IDS_Enable",szEnable);
			//FindNodeValue(ResNode,"IDS_Monday",szMon);
			//FindNodeValue(ResNode,"IDS_Tuesday",szThurs);
			//FindNodeValue(ResNode,"IDS_Wednesday",szWed);
			//FindNodeValue(ResNode,"IDS_Thursday",szTues);
			//FindNodeValue(ResNode,"IDS_Friday",szFri);
			//FindNodeValue(ResNode,"IDS_Saturday",szSat);
			//FindNodeValue(ResNode,"IDS_Sunday",szSun);
			//FindNodeValue(ResNode,"IDS_From",szfrom);
			//FindNodeValue(ResNode,"IDS_To",szTo);
		}
		CloseResource(objRes);
	}

	IsShow = true;//是否显示帮助
    m_nIndex = -1;

    showMainForm();//显示主界面
}

/************************************************
参数：

功能：
    保存绝对任务计划
************************************************/
void CSVAddAbsolutePlan::Save1()
{
	bool bEnd = false;	
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Plan Set";
	LogItem.sHitFunc = "Save1";
	LogItem.sDesc = szSaveAddAbPlan;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	OutputDebugString("----------------Add  01------------------\n");
	//增加任务计划结构：索引、任务名称、类型、是否选择
    ADD_PLAN_OK addPlan;
    //是否被选择，初始为未选择
	bool bCheck = 0;
	//任务计划名称
    addPlan.szName = m_pName->text();
	//任务计划名称LIST
    std::list<string> tasknamelist;
	//任务计划名称iterator
	std::list<string>::iterator m_pItem;
	//是否需要保存
	bool IsSave = false;
	bool IsConn = GetAllTaskName(tasknamelist);
	
	std::list<string> errorMsgList;
	
	//连接SVDB成功
	if(IsConn)
	{
		OutputDebugString("----------------Add  02------------------\n");
		for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
		{
			OutputDebugString("-------(IsConn Yes)---------Add  02----00--------------\n");

			std::string str = *m_pItem;
			if(strcmp(str.c_str(), addPlan.szName.c_str()) == 0)
			{
				IsSave = true;
				OutputDebugString("-------(IsConn Yes)---------Add  02----00----00---IsSave(true)-------\n");
				break;
			}
		}
		
		if(strcmp(chgstr.c_str(), "") == 0)
		{
			OutputDebugString("-------(strcmp(chgstr.c_str(), "") == 0)------------\n");
			if(!IsSave)
			{
				OutputDebugString("-------(IsConn Yes)------Save(false)--begin-----\n");
				if (addPlan.szName.empty())
				{
					errorMsgList.push_back(m_FormShowText.szErrorMsg);
					AddRangeTable->ShowErrorMsg(errorMsgList);
					//m_pPlanNameError-> show();
					bEnd = true;	
					goto OPEnd;
				}
				else
				{
					AddRangeTable -> HideAllErrorMsg();
					//m_pPlanNameError-> hide();
				}

				OutputDebugString("-------(IsConn Yes)------Save(false)--begin01-----\n");
				std::string str1 = m_pTasklist->m_pStart[1]->text();

				//Jansion.zhou 2006-12-26
				//m_pErrMsg->setText("");
				//m_pErrMsg->hide();

				addPlan.nIndex = m_nIndex;
				OutputDebugString("-------(IsConn Yes -> Save(false)---01-------------\n");

				OBJECT hTask = CreateTask(addPlan.szName);
				SetTaskValue("Type",m_FormShowText.szPlanTypeAb, hTask);
				OutputDebugString("-------(IsConn Yes -> Save(false)---02-------------\n");
				char buf[256];
				for(int i = 0; i < 7; i++)
				{	
					itoa(i, buf, 10);
					std::string temp = m_pTasklist->m_pStart[i]->text();
					std::string temp1 = "start";
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

				OutputDebugString("-------(IsConn Yes -> Save(false)---03-------------\n");
 				//插记录到UserOperateLog表
				string strUserID = GetWebUserID();
				TTime mNowTime = TTime::GetCurrentTimeEx();
				OperateLog m_pOperateLog;
				OutputDebugString("-------(IsConn Yes -> Save(false)---04-------------\n");
				m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeAdd,strTimeTaskPlan,m_pName->text());

				emit Successful(addPlan);
				OutputDebugString("-------(IsConn Yes -> Save(false)---05-------------\n");
			}
			else
			{
				OutputDebugString("-----IsSave(true)---(IsConn Yes)---------Add  02----00----00----------\n");
				//Jansion.zhou 2006-12-26
				//showErrorMsg(string(m_FormShowText.szErrorMsg1));

				errorMsgList.push_back(m_FormShowText.szErrorMsg1);
				AddRangeTable->ShowErrorMsg(errorMsgList);
			}
		}
		else
		{
			OutputDebugString("-------(strcmp(chgstr.c_str(), "") != 0---------Add  02----00----01----------\n");
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
				if (addPlan.szName.empty())
				{
					errorMsgList.push_back(m_FormShowText.szErrorMsg);
					AddRangeTable->ShowErrorMsg(errorMsgList);
					//m_pPlanNameError->show();
					bEnd = true;	
					goto OPEnd;
				}
				else
				{
					AddRangeTable -> HideAllErrorMsg();
					//m_pPlanNameError-> hide();
				}
				std::string str1 = m_pTasklist->m_pStart[1]->text();

				//Jansion.zhou 2006-12-26
				//m_pErrMsg->setText("");
				//m_pErrMsg->hide();

				addPlan.nIndex = m_nIndex;

				OBJECT hTask = GetTask(chgstr);
				SetTaskValue("Type",m_FormShowText.szPlanTypeAb, hTask);
				char buf[256];
				for(int i = 0; i < 7; i++)
				{	
					itoa(i, buf, 10);
					std::string temp = m_pTasklist->m_pStart[i]->text();
					
					std::string temp1 = "start";
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
				
				EditTask(hTask, addPlan.szName);
 
				//插记录到UserOperateLog表
				string strUserID = GetWebUserID();
				TTime mNowTime = TTime::GetCurrentTimeEx();
				OperateLog m_pOperateLog;
				m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeEdit,strTimeTaskPlan,m_pName->text());

				emit Successful(addPlan);
			}
			else
			{
				//Jansion.zhou 2006-12-26
				//showErrorMsg(string(m_FormShowText.szErrorMsg1));

				errorMsgList.push_back(m_FormShowText.szErrorMsg1);
				AddRangeTable->ShowErrorMsg(errorMsgList);
			}
			
		}
	}
	else
	{
		OutputDebugString("----------------Add  04(IsConn Not line SVDB)------------------\n");
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVAddAbsolutePlan::Cancel1()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Plan Set";
	LogItem.sHitFunc = "Cancel1";
	LogItem.sDesc = szCancelAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	emit SCancel1();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

bool CSVAddAbsolutePlan::checkPlan()
{
    return true;
}

void CSVAddAbsolutePlan::showErrorMsg(string &szErrMsg)
{
	//Jansion.zhou 2006-12-26
    //m_pErrMsg->setText(szErrMsg);
    //m_pErrMsg->show();
}

void CSVAddAbsolutePlan::showMainForm()
{

	//string szMon,szThurs,szWed,szTues,szFri,szSat,szSun,szDisable,szEnable,szfrom,szTo;
	////Resource
	//OBJECT objRes=LoadResource("default", "localhost");  
	//if( objRes !=INVALID_VALUE )
	//{	
	//	MAPNODE ResNode=GetResourceNode(objRes);
	//	if( ResNode != INVALID_VALUE )
	//	{

	//		FindNodeValue(ResNode,"IDS_Disable",szDisable);
	//		FindNodeValue(ResNode,"IDS_Enable",szEnable);
	//		FindNodeValue(ResNode,"IDS_Monday",szMon);
	//		FindNodeValue(ResNode,"IDS_Tuesday",szThurs);
	//		FindNodeValue(ResNode,"IDS_Wednesday",szWed);
	//		FindNodeValue(ResNode,"IDS_Thursday",szTues);
	//		FindNodeValue(ResNode,"IDS_Friday",szFri);
	//		FindNodeValue(ResNode,"IDS_Saturday",szSat);
	//		FindNodeValue(ResNode,"IDS_Sunday",szSun);
	//		FindNodeValue(ResNode,"IDS_From",szfrom);
	//		FindNodeValue(ResNode,"IDS_To",szTo);
	//	}
	//	CloseResource(objRes);
	//}

	//std::string DayType[] = {szSun, szMon, szThurs, szWed, szTues, szFri, szSat};

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	new WText("<div id='view_panel' class='panel_view'>", this);

	
	pMainTable = new WSVMainTable(this, szTitle, true);
	if(pMainTable->pHelpImg)
	{
		connect(pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(AddPlanHelp()));
	}
	
	
	AddRangeTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(1,0), Group, m_FormShowText.szAddAdTitle);

	if (AddRangeTable->GetContentTable() != NULL)
	{
		AddRangeTable->AppendRows(m_FormShowText.szBasicAdd);

		m_pName = new WLineEdit("", AddRangeTable->AppendRowsContent(0, m_FormShowText.szRunName+"<span class =required>*</span>", m_FormShowText.szRunNameHelp, m_FormShowText.szErrorMsg));
		m_pName->resize(WLength(300, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pName->setStyleClass("input_text");

		new WText("", AddRangeTable->AppendRowsContent(0, "", "", m_FormShowText.szErrorMsg1));

		m_pTasklist = new CTaskList1(NULL, AddRangeTable, m_FormShowText.strWeekHelp);

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
		WObject::connect(pSave, SIGNAL(clicked()), this, SLOT(Save1()));
		//pGroupOperate->elementAt(0,0)-> addWidget(pSave);

		WSVButton * pCancel = new WSVButton(pGroupOperate->elementAt(0,1),m_FormShowText.szCancelBut,"button_bg_m.png",m_FormShowText.szCancelBut,false);
		WObject::connect(pCancel, SIGNAL(clicked()), this, SLOT(Cancel1()));

		//pGroupOperate->elementAt(0,0)-> addWidget(pCancel);
		//pGroupOperate->elementAt(0,0)->setContentAlignment(AlignCenter);

	}



//
//	if (AddAdvanTable->GetContentTable() != NULL)
//	{
//		
//
//		//pAddrSetTable->InitTable();
//		//WLineEdit * AddName = new WLineEdit("", pAddrSetTable->AppendRowsContent(0, 0, 1, m_FormShowText.szRunName+"<span class =required>*</span>", m_FormShowText.szRunNameHelp, m_FormShowText.szErrorMsg));
//		//AddName->setStyleClass("input_text");
//	
//		pAddrSetTable->InitTable();
//
//		pAddrSetTable->AppendRows();
//		WLineEdit * m_pName = new WLineEdit("", pAddrSetTable->AppendRowsContent(0, 0, 1, m_FormShowText.szRunName+"<span class =required>*</span>", m_FormShowText.szRunNameHelp, m_FormShowText.szErrorMsg));
//		m_pName->setStyleClass("input_text");
//
//		for(int i=1; i< 8 ; i++)
//		{
//			pAddrSetTable->AppendRows();
//			//if ( i == 1 )
//			//{
//				WTable *aa = new WTable(pAddrSetTable->AppendRowsContent(i, 0, 1,DayType[i-1], m_FormShowText.strWeekHelp, "ERROR"));
//			//}else {
//			//	WTable *aa = new WTable(pAddrSetTable->AppendRowsContent(i, 0, 1,DayType, "", ""));
//			//}
//			//WTable *bb = new WTable(pAddrSetTable->AppendRowsContent(i, szSun, "help", "error"));
//			
//			aa->resize(WLength(10,WLength::Pixel),0);
//			WComboBox *c = new WComboBox(aa->elementAt(0,0));
//			c->addItem(szEnable);
//			c->addItem(szDisable);
//			c->setStyleClass("input_text_pop");
//			WLineEdit * TimeEdit = new WLineEdit("00:00", aa->elementAt(0,1));
//			TimeEdit->setStyleClass("input_text");
//			
//		}
//
//		//m_pTasklist = new CTaskList1(NULL, pAddrSetTable);
//		//pAddrSetTable->GetContentTable()->elementAt(pAddrSetTable->GetContentTable()->numRows(), 0)->addWidget(m_pTasklist);
//
//		//new WLineEdit(, AddrSetTable1->AppendRowsContent(
//	}
//
//
//
//	pAddrSetTable->ShowOrHideHelp();
//	pAddrSetTable->HideAllErrorMsg();
//
//
//	
//	WSVFlexTable *pAddrSetTable2 = new WSVFlexTable((WContainerWidget *)ppMainTable->GetContentTable()->elementAt(1,0), AlertSel, m_FormShowText.szAdvanceAdd);
//
//	
//	if (pAddrSetTable2->GetContentTable() != NULL)
//	{
//		pAddrSetTable2->InitTable();
//
//		pAddrSetTable2->AppendRows();
//		textarea = new WTextArea("", pAddrSetTable2->AppendRowsContent(0, 0, 1, m_FormShowText.szDescript, "", ""));
//
//		textarea->setStyleClass("input_text");
//		//new WLineEdit(, AddrSetTable1->AppendRowsContent(
//	}
//	//pAddrSetTable->ShowOrHideHelp();
//	//pAddrSetTable->HideAllErrorMsg();
//
//
//
//
//	WTable *pGroupOperate = new WTable(ppMainTable->elementAt(ppMainTable->numRows(),0));
//	//pGroupOperate->setStyleClass("t3");
//	pGroupOperate->setStyleClass("widthauto");
//
//	//WPushButton * pSave = new WPushButton(m_FormShowText.szSaveBut);
//	WSVButton * pSave = new WSVButton(pGroupOperate->elementAt(0,0),m_FormShowText.szSaveBut,"button_bg_add_black.png",m_FormShowText.szSaveBut,true);
//	//pSave -> setStyleClass("input_border");
//	WObject::connect(pSave, SIGNAL(clicked()), this, SLOT(Save1()));
//	pGroupOperate->elementAt(0,0)-> addWidget(pSave);
//
//	//new WText("&nbsp;&nbsp;&nbsp;",(WContainerWidget*)pGroupOperate->elementAt(0,0));
//
//	//WPushButton * pCancel = new WPushButton(m_FormShowText.szCancelBut);
//	WSVButton * pCancel = new WSVButton(pGroupOperate->elementAt(0,1),m_FormShowText.szCancelBut,"button_bg_m.png");
//	//pCancel -> setStyleClass("input_border");
//	WObject::connect(pCancel, SIGNAL(clicked()), this, SLOT(Cancel1()));
//
//	pGroupOperate->elementAt(0,0)-> addWidget(pCancel);
//	pGroupOperate->elementAt(0,0)->setContentAlignment(AlignCenter);
//	
////	pGroupOperate->elementAt(0,0)->resize(WLength(100,WLength::Percentage),\
////		WLength(100,WLength::Percentage));



//Jansion.zhou 2006-12-26
	//WTable * TitleTable = new WTable(this);
	//TitleTable->setStyleClass("t3");
	//
	//m_pErrMsg = new WText("", (WContainerWidget *)TitleTable->elementAt(0,0));
	//m_pErrMsg->decorationStyle().setForegroundColor(Wt::red);
	//m_pErrMsg->hide();
	//m_pConnErr = new WText("", (WContainerWidget *)TitleTable->elementAt(0, 0));
	//m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	//m_pConnErr ->hide();



	////main form help button
	//m_pHelpImg = new WImage("../Images/help.gif", \
	//	(WContainerWidget *)TitleTable->elementAt( 0, 1));
	//m_pHelpImg ->setStyleClass("helpimg");
	//m_pHelpImg->setToolTip(strHelp);
	//TitleTable->elementAt(0, 1) -> setContentAlignment(AlignTop | AlignRight);
	//WObject::connect(m_pHelpImg, SIGNAL(clicked()), this, SLOT(AddPlanHelp()));
	//addWidget(m_pHelpImg);

	//WTable * m_pGeneral = new WTable( this );
	//m_pGeneral->setStyleClass("t2");
 //   if ( m_pGeneral )
 //   {    
	//	pHide = new WImage("../Images/close.gif", \
	//		(WContainerWidget *)m_pGeneral->elementAt( 0, 0));
 //       if ( pHide )
 //       {
 //           pHide->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
 //           WObject::connect(pHide, SIGNAL(clicked()), this, SLOT(showPlanList1()));   
 //           pHide->hide();           
 //       }
 //       pShow = new WImage("../Images/open.gif", \
	//		(WContainerWidget *)m_pGeneral->elementAt( 0, 0));
 //       if ( pShow )
 //       {
 //           pShow->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
 //           WObject::connect(pShow, SIGNAL(clicked()), this, SLOT(hidePlanList1()));            
 //       }


 //       new WText(m_FormShowText.szBasicAdd, (WContainerWidget *)m_pGeneral->elementAt( 0, 0));
 //       ((WContainerWidget*)m_pGeneral->elementAt(0,0))->setStyleClass("t2title");

	//	table = new WTable((WContainerWidget *) m_pGeneral->elementAt(1,0));
	//	
	//	table -> setStyleClass("t3");
	//	new WText(m_FormShowText.szRunName, (WContainerWidget*)table->elementAt(0,0));
	//	new WText("<span class =required>*</span>", (WContainerWidget*)table -> elementAt(0,0));
	//	m_pName = new WLineEdit("", (WContainerWidget*)table->elementAt(0,1));
	//	m_pName -> setTextSize(50);
	//	
	//	m_pPlanNameHelp = new WText(m_FormShowText.szRunNameHelp,\
	//		(WContainerWidget*)table->elementAt(1,1));
	//	m_pPlanNameHelp->setStyleClass("helps");
	//	m_pPlanNameHelp -> hide();
	//
	//	m_pPlanNameError = new WText(m_FormShowText.szErrorMsg,\
	//		(WContainerWidget*)table->elementAt(2,1));
	//	m_pPlanNameError->setStyleClass("errors");
	//	m_pPlanNameError-> hide();


	//	tWeekHelp = new WText(m_FormShowText.strWeekHelp,\
	//		(WContainerWidget*)table->elementAt(4,1));
	//	tWeekHelp->setStyleClass("helps");
	//	tWeekHelp->hide();

	//	m_pTasklist = new CTaskList1(NULL, table);
	//	addWidget(m_pTasklist);		
	//}

/*
	WTable * m_pGeneral1 = new WTable( this );
	m_pGeneral1 ->setStyleClass("t2");
    if ( m_pGeneral1 )
    {    	
		pHide1 = new WImage("../Images/close.gif", \
			(WContainerWidget *)m_pGeneral1->elementAt( 0, 0));
        if ( pHide1 )
        {
            pHide1->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
            WObject::connect(pHide1, SIGNAL(clicked()), this, SLOT(AshowPlanList1()));   
            pHide1->hide();           
        }
	
        pShow1 = new WImage("../Images/open.gif", \
			(WContainerWidget *)m_pGeneral1->elementAt( 0, 0));

        if ( pShow1 )
        {
            pShow1->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
            WObject::connect(pShow1, SIGNAL(clicked()), this, SLOT(AhidePlanList1()));            
        }

        new WText(m_FormShowText.szAdvanceAdd, \
			(WContainerWidget *)m_pGeneral1->elementAt( 0, 0));
        ((WContainerWidget*)m_pGeneral1->elementAt(0,0))->setStyleClass("t2title");

		table1 = new WTable((WContainerWidget *) m_pGeneral1->elementAt(1,0));
		table1 -> setStyleClass("t3");

		new WText(m_FormShowText.szDescript, (WContainerWidget*)table1->elementAt(0,0));
		
		textarea = new WTextArea("", (WContainerWidget*)table1->elementAt(0,1));
		table1->elementAt(0,0)->resize( WLength(19 ,\
			WLength::Percentage),WLength(100 ,WLength::Percentage));
		textarea ->setColumns(50);
	}
*/

	//WTable *pGroupOperate1 = new WTable(this);
	//pGroupOperate1->setStyleClass("t3");
	//WPushButton * pSave1 = new WPushButton(m_FormShowText.szSaveBut);
	////pSave -> setStyleClass("input_border");
	//WObject::connect(pSave1, SIGNAL(clicked()), this, SLOT(Save1()));
	//pGroupOperate1->elementAt(0,0)-> addWidget(pSave);

	//new WText("&nbsp;&nbsp;&nbsp;",(WContainerWidget*)pGroupOperate1->elementAt(0,0));

	//WPushButton * pCancel1 = new WPushButton(m_FormShowText.szCancelBut);
	////pCancel -> setStyleClass("input_border");
	//WObject::connect(pCancel1, SIGNAL(clicked()), this, SLOT(Cancel1()));

	//pGroupOperate1->elementAt(0,0)-> addWidget(pCancel);
	//pGroupOperate1->elementAt(0,0)->setContentAlignment(AlignCenter);
	//
	//pGroupOperate1->elementAt(0,0)->resize(WLength(100,WLength::Percentage),\
	//	WLength(100,WLength::Percentage));

	new WText("</div>", this);

	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

}

//添加客户端脚本变量
void CSVAddAbsolutePlan::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CSVAddAbsolutePlan::clearContent()
{
    m_nIndex = -1;
    m_pName->setText("");
	textarea->setText("");

	//Jansion.zhou 2006-12-26
	//m_pErrMsg ->setText("");

    m_pTasklist->Reset();

	AddRangeTable->HideAllErrorMsg();
}

void CSVAddAbsolutePlan::UpdateData(ADD_PLAN_OK addMail)
{
    m_pName->setText(addMail.szName);
	chgstr = addMail.szName;
    m_nIndex = addMail.nIndex;
	
	OBJECT hTask = GetTask(addMail.szName);
//	OBJECT hTask;

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
	}
	std::string temp1 = "Description";
	std::string temp = GetTaskValue(temp1, hTask);
	textarea -> setText(temp);   

}
void CSVAddAbsolutePlan::showPlanList1()
{
	//Jansion.zhou 2006-12-26
	//pShow -> show();
	//pHide -> hide();
	//table -> show();
}

void CSVAddAbsolutePlan::hidePlanList1()
{
	//Jansion.zhou 2006-12-26
	//pShow -> hide();
	//pHide -> show();
	//table -> hide();
}

void CSVAddAbsolutePlan::AshowPlanList1()
{
	//Jansion.zhou 2006-12-26
	//pShow1 -> show();
	//pHide1 -> hide();
	//table1 -> show();
}

void CSVAddAbsolutePlan::AhidePlanList1()
{
	//Jansion.zhou 2006-12-26
	//pShow1 -> hide();
	//pHide1 -> show();
	//table1 -> hide();
}

void CSVAddAbsolutePlan::AddPlanHelp()
{
	AddRangeTable->ShowOrHideHelp();

	//Jansion.zhou 2006-12-26
	//if(IsShow)
	//{
	//	m_pPlanNameHelp ->show();
	//	tWeekHelp->show();
	//	IsShow = false;
	//}
	//else
	//{
	//	m_pPlanNameHelp ->hide();
	//	tWeekHelp->hide();
	//	IsShow = true;
	//}
}
