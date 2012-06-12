#include "stdafx.h"
#include "MainForm.h"
#include "AddPhone.h"
#include "configpage.h"
#include "svapi.h"
#include "WApplication"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WStackedWidget"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WPushButton"
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
CSVMainForm::CSVMainForm(WContainerWidget * parent):
WTable(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
/*			//添加Resource
			bool bAdd = AddNodeAttrib(ResNode,"IDS_Add_SMS_Receive_Phone","添加短信接收手机号");
			bAdd = AddNodeAttrib(ResNode,"IDS_Edit_SMS_Receive_Phone","编辑短信接收手机号");
*/
			FindNodeValue(ResNode,"IDS_SMS_Config",strMainTitle);
			FindNodeValue(ResNode,"IDS_Add_SMS_Receive_Phone",strAddTitle);
			FindNodeValue(ResNode,"IDS_Edit_SMS_Receive_Phone",strEditTitle);
		}
//		SubmitResource(objRes);
		CloseResource(objRes);
	}
/*
	strMainTitle="短信设置";
	strAddTitle="添加短信接收手机号";
	strEditTitle="编辑短信接收手机号";
*/	//setStyleClass("t1");
	//new WText(strMainTitle, (WContainerWidget*)elementAt(0,0));
	//m_pMainTitle = new WText("", (WContainerWidget*)elementAt(0,0));

    m_pfrSmsSend = NULL;
    m_pfrAddPhone = NULL;

    m_pmainStack = new WStackedWidget(elementAt(0, 0));
    m_pmainStack->setPadding(WLength(0));
    m_pmainStack->addWidget(m_pfrSmsSet = new CSVSmsSet());

   
	WObject::connect(m_pfrSmsSet, SIGNAL(AddNewPhone()), this, SLOT(ShowAddForm()));  
    WObject::connect(m_pfrSmsSet, SIGNAL(EditPhone(SAVE_PHONE_LIST)), this, 
        SLOT(Edit_Phone(SAVE_PHONE_LIST)));
	WObject::connect(m_pfrSmsSet, SIGNAL(ExChangeEvent()), this, SLOT(ExChangeRefresh()));  

    showSmsSet();

}
					
void CSVMainForm::ExChangeRefresh()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/smsset.exe?'\",1250);  ";
	appSelf->quit();
}

void CSVMainForm::ShowAddForm()
{
    if (!m_pfrAddPhone)
    {
		//m_pMainTitle->setText();
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddPhone());
        WObject::connect(m_pfrAddPhone, SIGNAL(BackTo()), this, SLOT(ShowSetForm()));
        WObject::connect(m_pfrAddPhone, SIGNAL(SavePhone(SAVE_PHONE_LIST)), 
            this, SLOT(Save_Phone(SAVE_PHONE_LIST)));
        WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
    }
    m_pfrAddPhone->clearData();
    showAddPhone();
}

void CSVMainForm::showAddPhone()
{
	m_pmainStack->setCurrentWidget(m_pfrAddPhone);
}


void CSVMainForm::ShowSmsForm()
{

}

void CSVMainForm::showSendSms()
{

}

void CSVMainForm::ShowSetForm()
{
	//m_pMainTitle->setText();

	//m_pfrSmsSet->m_pHelpUserID ->hide();
	//m_pfrSmsSet->pNote ->hide();
	//m_pfrSmsSet->m_pHelpCOM->hide();
	m_pfrSmsSet -> IsShow = true;
    showSmsSet();
}

void CSVMainForm::showSmsSet()
{
    m_pmainStack->setCurrentWidget(m_pfrSmsSet);
}

void CSVMainForm::Save_Phone(SAVE_PHONE_LIST phone)
{
	//m_pMainTitle->setText();

    if ( m_pfrSmsSet )
    {
        m_pfrSmsSet->SavePhone(&phone);
 		//m_pfrSmsSet->m_pHelpUserID ->hide();
		//m_pfrSmsSet->pNote ->hide();
		//m_pfrSmsSet->m_pHelpCOM->hide();
		m_pfrSmsSet -> IsShow = true;
   }
    showSmsSet();
}

void CSVMainForm::Edit_Phone(SAVE_PHONE_LIST phone)
{

	//m_pMainTitle->setText();

	if (!m_pfrAddPhone)
    {
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddPhone());
        WObject::connect(m_pfrAddPhone, SIGNAL(BackTo()), this, SLOT(ShowSetForm()));
        WObject::connect(m_pfrAddPhone, SIGNAL(SavePhone(SAVE_PHONE_LIST)), 
            this, SLOT(Save_Phone(SAVE_PHONE_LIST)));
        WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
    }

	m_pfrAddPhone->chgstr = phone.chgstr;

    if ( m_pfrAddPhone)
    {
        m_pfrAddPhone->setProperty(&phone);
		m_pfrSmsSet ->m_pConnErr ->hide();
    }
    showAddPhone();
}