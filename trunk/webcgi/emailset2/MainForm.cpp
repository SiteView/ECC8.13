//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "MainForm.h"
#include "EmailSet.h"
#include "AddEmail.h"
#include "svapi.h"
#include <WTable>
#include <WTableCell>
#include <WStackedWidget>
#include <WApplication>
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
CMainForm::CMainForm(WContainerWidget * parent) :
WTable(parent)
{
	this->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
	this->setCellPadding(0);
	this->elementAt(0, 0)->setContentAlignment( WWidget::AlignTop);
	//this->elementAt(0, 0)->setColumnSpan(0);
	//this->elementAt(0, 0)->setRowSpan(0);
	//this->elementAt(0, 0)->setPadding(0, WWidget::Side::All);
	
	//this->elementAt(0, 0)->setCellPadding(0)
		
    m_pAddEmail = NULL;
    m_pMainStack = new WStackedWidget(elementAt(0, 0));
    //m_pMainStack->setPadding(WLength(20));
    m_pMainStack->addWidget(m_pEmailSet = new CSVEmailSet());
  
    //WObject::connect(m_pEmailSet, SIGNAL(SaveSuccessful(SEND_MAIL_PARAM)), this, SLOT(ShowsendForm(SEND_MAIL_PARAM)));
    WObject::connect(m_pEmailSet, SIGNAL(AddNewMail()), this, SLOT(showAddform()));
    WObject::connect(m_pEmailSet, SIGNAL(EditMailList(ADD_MAIL_OK)), this, SLOT(EditNewMailList(ADD_MAIL_OK)));     
    WObject::connect(m_pEmailSet, SIGNAL(ExChangeEvent()), this, SLOT(ExChangeRefresh()));
   showMailSet();
}

void CMainForm::ExChangeRefresh()
{
    PrintDebugString("------ExChangeRefresh------\n");
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/emailset.exe?'\",1250);  ";
	appSelf->quit();
}

void CMainForm::showAddform()
{
    PrintDebugString("Add mail list\n");
    if(m_pAddEmail == NULL)
    {        
		PrintDebugString("In m_pAddEmail == null");

        m_pMainStack->addWidget(m_pAddEmail = new CSVAddEmail());
        WObject::connect(m_pAddEmail, SIGNAL(Successful(ADD_MAIL_OK)), this,
            SLOT(SaveNewMailList(ADD_MAIL_OK)));
        WObject::connect(m_pAddEmail, SIGNAL(BackMain()), this,
            SLOT(BackFromAdd()));        
        WObject::connect(m_pAddEmail, SIGNAL(ExChangeEventAdd()), this,
            SLOT(ExChangeRefresh()));
    }

	PrintDebugString("m_pAddEmail != NULL");
    m_pAddEmail->clearContent();
    showAddEmail();
}

void CMainForm::EditNewMailList(ADD_MAIL_OK addMail)
{
    PrintDebugString("EditNewMailList\n");
    if(m_pAddEmail == NULL)
    {        
        m_pMainStack->addWidget(m_pAddEmail = new CSVAddEmail());
        WObject::connect(m_pAddEmail, SIGNAL(Successful(ADD_MAIL_OK)), this,
            SLOT(SaveNewMailList(ADD_MAIL_OK)));
        WObject::connect(m_pAddEmail, SIGNAL(BackMain()), this,
            SLOT(BackFromAdd()));        
         WObject::connect(m_pAddEmail, SIGNAL(ExChangeEventAdd()), this,
            SLOT(ExChangeRefresh()));        
   }
   //m_pAddEmail->clearContent();
	m_pAddEmail->UpdateData(addMail);
    showAddEmail();
}

void CMainForm::showAddEmail()
{
    m_pMainStack->setCurrentWidget(m_pAddEmail);
}

void CMainForm::Forword()
{
    showMailSet();
}


void CMainForm::SaveNewMailList(ADD_MAIL_OK addMail)//, bool bCheck)
{
    m_pEmailSet->AddMailList(addMail);
	PrintDebugString("Begin Show MailSet");
    showMailSet(); 
}

void CMainForm::showMailSet()
{
    m_pMainStack->setCurrentWidget(m_pEmailSet);
}


void CMainForm::BackFromAdd()
{
    showMailSet();
}
//////////////////////////////////////////////////////////////////////////////////
// end file
