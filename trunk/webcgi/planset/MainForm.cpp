//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "MainForm.h"
#include "PlanSet.h"
//#include "SendMail.h"
#include "AddPlan.h"
#include "svapi.h"
#include "WApplication"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WStackedWidget"
#include "../../opens/libwt/WebSession.h"
#ifdef WIN32
#pragma warning (disable: 4251)
#include <windows.h>
#endif

void PrintDebugString(const char *szErrmsg)
{
#ifdef WIN32
    OutputDebugString(szErrmsg);
#endif
}

//////////////////////////////////////////////////////////////////////////////////
// start
CMainForm::CMainForm(WContainerWidget * parent):WTable(parent)
//CMainForm::CMainForm(WContainerWidget * parent):WContainerWidget(parent)
{
	//setStyleClass("bg_Border");
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Plan",szTitle);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
		}
		CloseResource(objRes);
	}


	setStyleClass("t1");

	new WText("", (WContainerWidget*)elementAt(0,0));
	elementAt(0,0)->setStyleClass("t1title");

	elementAt(1, 0) -> setContentAlignment(AlignTop | AlignRight);

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)elementAt(1, 0));
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)elementAt(1, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)elementAt(1,0));
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)elementAt(1, 0));

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		WObject::connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pExChangeBtn->show();
		WObject::connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}

	m_pAddPlan = NULL;
	m_pAddAbsolutePlan = NULL;
    m_pMainStack = new WStackedWidget(elementAt(1, 0));
    m_pMainStack->setPadding(WLength(0));
	m_pPlanSet = new CSVPlanSet();
	m_pMainStack->addWidget(m_pPlanSet);
    

    WObject::connect(m_pPlanSet, SIGNAL(AddNewPlan()), this, SLOT(showAddform()));
    WObject::connect(m_pPlanSet, SIGNAL(EditPlanList(ADD_PLAN_OK)), this, SLOT(EditNewPlanList(ADD_PLAN_OK)));     

	WObject::connect(m_pPlanSet, SIGNAL(AddNewPlan1()), this, SLOT(showAddform1()));
    WObject::connect(m_pPlanSet, SIGNAL(EditPlanList1(ADD_PLAN_OK)), this, SLOT(EditNewPlanList1(ADD_PLAN_OK)));     

	showPlanSet();


/*
//	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

	new WText("<div id='view_panel' class='panel_view'>", this);

	
	pMainTable = new WSVMainTable(this, szTitle, false);
	
////	szTitle = "任务计划";
//	setStyleClass("t1");
//
//	new WText(szTitle, (WContainerWidget*)elementAt(0,0));
//	elementAt(0,0)->setStyleClass("t1title");
//
//	elementAt(1, 0) -> setContentAlignment(AlignTop | AlignRight);

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)pMainTable->elementAt(0, 0));
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->elementAt(0, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)pMainTable->elementAt(0,0));
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->elementAt(0, 0));

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	//bTrans = 1;
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		WObject::connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pExChangeBtn->show();
		WObject::connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}
	
	m_pAddPlan = NULL;
	m_pAddAbsolutePlan = NULL;
    //m_pMainStack = new WStackedWidget(elementAt(1, 0));
	m_pMainStack = new WStackedWidget((WContainerWidget *)pMainTable->elementAt(1,0));
    m_pMainStack->setPadding(WLength(0));
	m_pPlanSet = new CSVPlanSet(pMainTable);
	m_pMainStack->addWidget(m_pPlanSet);
    

    WObject::connect(m_pPlanSet, SIGNAL(AddNewPlan()), this, SLOT(showAddform()));
    WObject::connect(m_pPlanSet, SIGNAL(EditPlanList(ADD_PLAN_OK)), this, SLOT(EditNewPlanList(ADD_PLAN_OK)));     

	WObject::connect(m_pPlanSet, SIGNAL(AddNewPlan1()), this, SLOT(showAddform1()));
    WObject::connect(m_pPlanSet, SIGNAL(EditPlanList1(ADD_PLAN_OK)), this, SLOT(EditNewPlanList1(ADD_PLAN_OK)));     

	showPlanSet();

	new WText("</div>",this);
*/
}

void CMainForm::ExChange()
{
	PrintDebugString("-------ExChange-------\n");
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/planset.exe?'\",1250);  ";
	appSelf->quit();
}

void CMainForm::Translate()
{
	PrintDebugString("-------Translate-------\n");
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "plansetRes";
	WebSession::js_af_up += "')";
}

void CMainForm::showAddform()
{
	if(m_pAddPlan == NULL)
	{
		m_pMainStack->addWidget(m_pAddPlan = new CSVAddPlan());
		WObject::connect(m_pAddPlan, SIGNAL(Successful(ADD_PLAN_OK)), this,
			SLOT(SaveNewPlanList(ADD_PLAN_OK)));

		WObject::connect(m_pAddPlan, SIGNAL(SCancel()), this,
			SLOT(CancelAdd()));
	}
	m_pAddPlan->clearContent();
	showAddPlan();
}

void CMainForm::showAddform1()
{

	if(m_pAddAbsolutePlan == NULL)
	{
		
		m_pMainStack->addWidget(m_pAddAbsolutePlan = new CSVAddAbsolutePlan());
		
		WObject::connect(m_pAddAbsolutePlan, SIGNAL(Successful(ADD_PLAN_OK)), this,
			SLOT(SaveNewPlanList1(ADD_PLAN_OK)));

		WObject::connect(m_pAddAbsolutePlan, SIGNAL(SCancel1()), this,
			SLOT(CancelAdd()));
		
	}
	m_pAddAbsolutePlan->clearContent();
	showAddPlan1();
}

void CMainForm::Forword()
{
  
}


void CMainForm::EditNewPlanList(ADD_PLAN_OK addPlan)
{	
	if(m_pAddPlan == NULL)
	{
		
		m_pMainStack->addWidget(m_pAddPlan = new CSVAddPlan());
		WObject::connect(m_pAddPlan, SIGNAL(Successful(ADD_PLAN_OK)), this,
			SLOT(SaveNewPlanList(ADD_PLAN_OK)));

		WObject::connect(m_pAddPlan, SIGNAL(SCancel()), this,
			SLOT(CancelAdd()));
	}

	m_pAddPlan->clearContent();
	m_pAddPlan->UpdateData(addPlan);
	
	showAddPlan();
}

void CMainForm::EditNewPlanList1(ADD_PLAN_OK addPlan)
{	
	if(m_pAddAbsolutePlan == NULL)
	{		
		m_pMainStack->addWidget(m_pAddAbsolutePlan = new CSVAddAbsolutePlan());
		WObject::connect(m_pAddAbsolutePlan, SIGNAL(Successful(ADD_PLAN_OK)), this,
			SLOT(SaveNewPlanList1(ADD_PLAN_OK)));

		WObject::connect(m_pAddAbsolutePlan, SIGNAL(SCancel1()), this,
			SLOT(CancelAdd()));
	}

	m_pAddAbsolutePlan->clearContent();
	m_pAddAbsolutePlan->UpdateData(addPlan);
	showAddPlan1();
}

void CMainForm::CancelAdd()
{
	m_pPlanSet ->chgstr = "";
	showPlanSet();
}

void CMainForm::CancelAdd1()
{
}


void CMainForm::SaveNewPlanList(ADD_PLAN_OK addPlan)
{
	m_pPlanSet->AddPlanList(addPlan);
	showPlanSet();
}

void CMainForm::SaveNewPlanList1(ADD_PLAN_OK addPlan)
{
	m_pPlanSet->AddPlanList1(addPlan);
	showPlanSet();
}




void CMainForm::showAddPlan()
{
    m_pMainStack->setCurrentWidget(m_pAddPlan);
}

void CMainForm::showAddPlan1()
{
    m_pMainStack->setCurrentWidget(m_pAddAbsolutePlan);
}

void CMainForm::showPlanSet()
{
	m_pMainStack->setCurrentWidget(m_pPlanSet);
	//m_pPlanSet->adjustRowStyle();	


}
//////////////////////////////////////////////////////////////////////////////////
// end file
