#include "MainForm.h"
#include "AddTopnreport.h"
#include "configpage.h"
#include "WApplication"

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WStackedWidget"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WebSession.h"
#include "WSVFlexTable.h"

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
// start receive widget element at
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
			FindNodeValue(ResNode,"IDS_Report_Edit",strEditReport);
			FindNodeValue(ResNode,"IDS_Report_Add",strAddReport);
		}
		CloseResource(objRes);
	}



	setStyleClass("t6");

    m_pfrSmsSend = NULL;
    m_pfrAddPhone = NULL;

	
	//elementAt(1, 0)->setContentAlignment(AlignCenter);
	elementAt(1, 0)->setVerticalAlignment(AlignTop);
    m_pmainStack = new WStackedWidget(elementAt(1, 0));
    m_pmainStack->setPadding(WLength(0));
    //m_pmainStack->addWidget(m_pfrSmsSet = new CSVTopnReportSet());

	m_pfrSmsSet = new CSVTopnReportSet();
	
	//m_pmainStack->addWidget(m_pfrSmsSet);
	//OutputDebugString("------CSVMainForm0---------\n");
	//m_pmainStack->addWidget(m_pfrSmsSet = new CSVTopnReportSet());
	//OutputDebugString("------CSVMainForm1---------\n");
   
	if (!m_pfrAddPhone)
    {
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddTopnReport());
        WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
        WObject::connect(m_pfrAddPhone, SIGNAL(SaveTopnReport(SAVE_REPORT_LIST)), 
            this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
        WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
    }

	WObject::connect(m_pfrSmsSet, SIGNAL(AddNewPhone()), this, SLOT(ShowAddForm()));  
    WObject::connect(m_pfrSmsSet, SIGNAL(EditPhone(SAVE_REPORT_LIST)), this, 
        SLOT(Edit_Phone(SAVE_REPORT_LIST)));
	WObject::connect(m_pfrSmsSet, SIGNAL(ExChangeEvent()), this, SLOT(ExChangeRefresh()));  


	m_pmainStack->addWidget(m_pfrSmsSet);

    showSmsSet();
}
void CSVMainForm::ExChangeRefresh()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/topnreportset.exe?'\",1250);  ";
	appSelf->quit();
}
															
void CSVMainForm::ShowAddForm()
{
    if (!m_pfrAddPhone)
    {
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddTopnReport());
        WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
        WObject::connect(m_pfrAddPhone, SIGNAL(SaveTopnReport(SAVE_REPORT_LIST)), 
            this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
        WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
    }

    m_pfrAddPhone->clearData();
//	m_pfrAddPhone->m_pReportTable->pTitleTxt->setText(strAddReport);
    showAddPhone();

}

void CSVMainForm::showAddPhone()
{	
    m_pmainStack->setCurrentWidget(m_pfrAddPhone);
	

	m_pfrAddPhone->initTree();
	
	WebSession::js_af_up = "window.location.reload(true);hiddenbar();";
}


void CSVMainForm::ShowSmsForm()
{

}

void CSVMainForm::showSendSms()
{

}

void CSVMainForm::ShowSetForm(std::string str)
{
	if(strcmp(str.c_str(), "cancel") == 0)
	{
		m_pfrSmsSet->chgstr = "";
	}

	m_pfrSmsSet -> IsShow = true;
    showSmsSet();
}

void CSVMainForm::showSmsSet()
{
	//m_pTitle ->setText(szTitle);
    m_pmainStack->setCurrentWidget(m_pfrSmsSet);
	WebSession::js_af_up = "window.location.reload();";
}

void CSVMainForm::Save_Phone(SAVE_REPORT_LIST phone)
{
    if ( m_pfrSmsSet )
    {
        m_pfrSmsSet->SaveTopnReport(&phone);
    }
    showSmsSet();
}

void CSVMainForm::Edit_Phone(SAVE_REPORT_LIST phone)
{
	if (!m_pfrAddPhone)
    {
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddTopnReport());
		WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
        WObject::connect(m_pfrAddPhone, SIGNAL(SaveTopnReport(SAVE_REPORT_LIST)), 
            this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
        WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
    }

    if ( m_pfrAddPhone)
    {
        m_pfrAddPhone->setProperty(&phone);
		m_pfrSmsSet ->m_pConnErr ->hide();
    }
	m_pfrAddPhone->upData();
	m_pfrAddPhone->chgstr = phone.chgstr;
//	m_pfrAddPhone->m_pReportTable->pTitleTxt->setText(strEditReport);
	
    showAddPhone();
	m_pfrAddPhone->setGroupRightCheck(phone.szGroupRight);
	

}