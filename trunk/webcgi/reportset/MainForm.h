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

//////////////////////////////////////////////////////////////////////////////////
// include STL lib & using namespace std
#include <string>

using namespace std;

class CSVReportSet;
class CSVAddReport;
class CSVSendSms;
class WApplication;
class WPushButton;

#include "define.h"

class CSVMainForm : public WTable
{
    //MOC: W_OBJECT CSVMainForm:WTable
    W_OBJECT;
public:
    CSVMainForm(WContainerWidget *parent);

	CSVAddReport  * m_pfrAddPhone;

	WApplication*  appSelf;
public signals:
private slots:
    //MOC: SLOT CSVMainForm::ShowSetForm(std::string)
	void ShowSetForm(std::string);
    //MOC: SLOT CSVMainForm::ShowSmsForm()
    void ShowSmsForm();
    //MOC: SLOT CSVMainForm::ShowAddForm()
    void ShowAddForm();
    //MOC: SLOT CSVMainForm::Save_Phone(SAVE_REPORT_LIST)
    void Save_Phone(SAVE_REPORT_LIST phone);
    //MOC: SLOT CSVMainForm::Edit_Phone(SAVE_REPORT_LIST)
    void Edit_Phone(SAVE_REPORT_LIST phone);
	//MOC: SLOT CSVMainForm::ExChangeRefresh()
	void ExChangeRefresh();
private:
    void showSmsSet();
    void showAddPhone();
    void showSendSms();

    CSVReportSet    * m_pfrSmsSet;
    CSVSendSms   * m_pfrSmsSend;
    

    WStackedWidget * m_pmainStack;
	string szTitle;
	string  strCurrentUser;
	
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	std::string strAddReport;
	std::string strEditReport;

};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file