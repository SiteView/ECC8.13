//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_EMAIL_SET_MAIN_FORM_H_
#define _SV_EMAIL_SET_MAIN_FORM_H_

#if _MSC_VER > 1000
#pragma once
#endif
//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include <WTable>
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////
class CSVEmailSet;
class CSVAddEmail;
//////////////////////////////////////////////////////////////////////////////////
class WStackedWidget;
class WApplication;
class WPushButton;

#include "defines.h"

class CMainForm : public WTable
{
    //MOC: W_OBJECT CMainForm:WTable
    W_OBJECT;
public:
    CMainForm(WContainerWidget *parent);

	WApplication*  appSelf;

public signals:
private slots:
    //MOC: SLOT CMainForm::Forword()
    void Forword();
    //MOC: SLOT CMainForm::showAddform()
    void showAddform();
    //MOC: SLOT CMainForm::SaveNewMailList(ADD_MAIL_OK)
    void SaveNewMailList(ADD_MAIL_OK addMail);
    //MOC: SLOT CMainForm::EditNewMailList(ADD_MAIL_OK)
    void EditNewMailList(ADD_MAIL_OK addMail);
    //MOC: SLOT CMainForm::BackFromAdd()
    void BackFromAdd();
	//MOC: SLOT CMainForm::ExChangeRefresh()
	void ExChangeRefresh();
private:
    void showMailSet();
    void showSendMail();
    void showAddEmai();
    void showAddEmail();
protected:
    WStackedWidget * m_pMainStack;
    CSVEmailSet    * m_pEmailSet;
    CSVAddEmail    * m_pAddEmail;
};

#endif


/////////////////////////////////////////////////////////////////////////////////
// end file

