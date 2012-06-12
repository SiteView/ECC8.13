//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_SMS_SET_MAIN_FORM_H_
#define _SV_SMS_SET_MAIN_FORM_H

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WTable"
class WStackedWidget;
class WText;
class WPushButton;
//////////////////////////////////////////////////////////////////////////////////
// include STL lib & using namespace std
#include <string>

using namespace std;

class CSVSmsSet;
class CSVAddPhone;
class CSVSendSms;
class WApplication;

#include "define.h"
#include "WSVMainTable.h"

class CSVMainForm : public WTable
{
    //MOC: W_OBJECT CSVMainForm:WTable
    W_OBJECT;
public:
    CSVMainForm(WContainerWidget *parent);
public signals:
private slots:
    //MOC: SLOT CSVMainForm::ShowSetForm()
    void ShowSetForm();
    //MOC: SLOT CSVMainForm::ShowSmsForm()
    void ShowSmsForm();
    //MOC: SLOT CSVMainForm::ShowAddForm()
    void ShowAddForm();
    //MOC: SLOT CSVMainForm::Save_Phone(SAVE_PHONE_LIST)
    void Save_Phone(SAVE_PHONE_LIST phone);
    //MOC: SLOT CSVMainForm::Edit_Phone(SAVE_PHONE_LIST)
    void Edit_Phone(SAVE_PHONE_LIST phone);
	//MOC: SLOT CSVMainForm::ExChangeRefresh()
	void ExChangeRefresh();
private:
    void showSmsSet();
    void showAddPhone();
    void showSendSms();

    CSVSmsSet    * m_pfrSmsSet;
    CSVSendSms   * m_pfrSmsSend;
    CSVAddPhone  * m_pfrAddPhone;

    WStackedWidget * m_pmainStack;
	
	WText * m_pMainTitle;

public:
	std::string strMainTitle;
	std::string strEditTitle;
	std::string strAddTitle;

	WApplication*  appSelf;
};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file