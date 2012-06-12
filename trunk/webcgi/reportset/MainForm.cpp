#include "MainForm.h"
#include "Addreport.h"
#include "configpage.h"
#include "svapi.h"

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WStackedWidget"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WApplication"
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
			FindNodeValue(ResNode,"IDS_Report_Edit",strEditReport);
			FindNodeValue(ResNode,"IDS_Report_Add",strAddReport);
		}
		CloseResource(objRes);
	}

	//strCurrentUser =GetWebUserID();
	strCurrentUser = "1";

//	char aaaa[200];
//	sprintf(aaaa,"user is  %s",strCurrentUser.c_str());
	//strCurrentUser ="26420";
	setStyleClass("t6");
	/*szTitle = "统计报告";
	new WText(szTitle, (WContainerWidget*)elementAt(0,0));
	elementAt(0,0)->setStyleClass("t1title");
*/
	

    m_pfrSmsSend = NULL;
    m_pfrAddPhone = NULL;

	elementAt(1, 0)->setVerticalAlignment(AlignTop);
    m_pmainStack = new WStackedWidget(elementAt(1, 0));
    m_pmainStack->setPadding(WLength(0));
	//WTable *FistTable =new WTable;
	m_pfrSmsSet = new CSVReportSet();

	PrintDebugString("Init CSVReportSet OK\n");
    

	if (!m_pfrAddPhone)
    {
		PrintDebugString("Begin Init CSVAddReport\n");
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddReport());
      //  WObject::connect(m_pfrAddPhone, SIGNAL(BackTo()), this, SLOT(ShowSetForm()));
		WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
        WObject::connect(m_pfrAddPhone, SIGNAL(SavePhone(SAVE_REPORT_LIST)), 
            this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
		WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
		PrintDebugString("Init CSVAddReport OK\n");
    }


   
	//WObject::connect(m_pfrSmsSet, SIGNAL(AddNewPhone()), this, SLOT(ShowAddForm()));  

	WObject::connect(m_pfrSmsSet, SIGNAL(AddNewPhone()), this, SLOT(ShowAddForm()));  

    WObject::connect(m_pfrSmsSet, SIGNAL(EditPhone(SAVE_REPORT_LIST)), this, 
        SLOT(Edit_Phone(SAVE_REPORT_LIST)));

	WObject::connect(m_pfrSmsSet, SIGNAL(ExChangeEvent()), this, SLOT(ExChangeRefresh()));  

	m_pmainStack->addWidget(m_pfrSmsSet);
    showSmsSet();
	//ShowAddForm();
}
							
void CSVMainForm::ExChangeRefresh()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/reportset.exe?'\",1250);  ";
	appSelf->quit();
}
void CSVMainForm::ShowAddForm()
{

    if (!m_pfrAddPhone)
    {
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddReport());
       // WObject::connect(m_pfrAddPhone, SIGNAL(BackTo()), this, SLOT(ShowSetForm()));
		WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
        WObject::connect(m_pfrAddPhone, SIGNAL(SavePhone(SAVE_REPORT_LIST)), 
            this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
 		WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
   }
    m_pfrAddPhone->clearData();
	//m_pfrAddPhone->m_pAnswerTitle->setText(strAddReport);
	m_pfrAddPhone->setTitle(strAddReport);
    showAddPhone();
}

void CSVMainForm::showAddPhone()
{
    m_pmainStack->setCurrentWidget(m_pfrAddPhone);
	OutputDebugString("showAddPhone1-------------\n");
	strCurrentUser =GetWebUserID();
	OutputDebugString("showAddPhone2-------------\n");
	m_pfrAddPhone->initTree(strCurrentUser);

	//static int abc = 1;
	//WebSession::js_af_up="hiddenbar();";
	//if(abc)
	//{
	//	abc--;
	//	WebSession::js_af_up += "window.location.reload(true);";
	//}	

	WebSession::js_af_up = "hiddenbar();window.location.reload(true);";

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
	PrintDebugString("begin show SmsSet \n");
    m_pmainStack->setCurrentWidget(m_pfrSmsSet);
	WebSession::js_af_up = "window.location.reload(true);";

	//m_pfrSmsSet->enabled();
	PrintDebugString("show SmsSet OK\n");
}

void CSVMainForm::Save_Phone(SAVE_REPORT_LIST phone)
{
    if ( m_pfrSmsSet )
    {
        m_pfrSmsSet->SavePhone(&phone);
    }
    showSmsSet();
}

void CSVMainForm::Edit_Phone(SAVE_REPORT_LIST phone)
{
	if (!m_pfrAddPhone)
    {
        m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddReport());
		WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
        WObject::connect(m_pfrAddPhone, SIGNAL(SavePhone(SAVE_REPORT_LIST)), 
            this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
		WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
    }

	//if (!m_pfrAddPhone)
 //   {
 //       m_pmainStack->addWidget(m_pfrAddPhone = new CSVAddReport());
	//	WObject::connect(m_pfrAddPhone, SIGNAL(BackTo(std::string)), this, SLOT(ShowSetForm(std::string)));
 //       WObject::connect(m_pfrAddPhone, SIGNAL(SavePhone(SAVE_REPORT_LIST)), 
 //           this, SLOT(Save_Phone(SAVE_REPORT_LIST)));
	//	WObject::connect(m_pfrAddPhone, SIGNAL(ExChangeAddEvent()), this, SLOT(ExChangeRefresh()));
 //   }


    if ( m_pfrAddPhone)
    {
        m_pfrAddPhone->setProperty(&phone);
		m_pfrSmsSet ->m_pConnErr ->hide();
    }

	m_pfrAddPhone->chgstr = phone.chgstr;
	//m_pfrAddPhone->m_pAnswerTitle->setText(strEditReport);
	m_pfrAddPhone->setTitle(strEditReport);
	OutputDebugString("showAddPhone1-------------\n");
    showAddPhone();
	OutputDebugString("showAddPhone2-------------\n");
	
	m_pfrAddPhone->setGroupRightCheck(phone.szGroupRight);
	//m_pfrAddPhone->setGroupRightCheck(phone.
	//WebSession::js_af_up="hiddenbar();window.location.reload(true);";



}