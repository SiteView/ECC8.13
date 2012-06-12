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

class CSVTopnReportSet;
class CSVAddTopnReport;
class CSVSendSms;
class WApplication;

#include "define.h"

class CSVMainForm : public WTable
{
    //MOC: W_OBJECT CSVMainForm:WTable
    W_OBJECT;
public:
    CSVMainForm(WContainerWidget *parent);
public:
	WText * m_pTitle;
	string szTitle2;

	string strEditReport;
	string strAddReport;

	 CSVAddTopnReport  * m_pfrAddPhone;
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

    CSVTopnReportSet    * m_pfrSmsSet;
    CSVSendSms   * m_pfrSmsSend;
   
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

    WStackedWidget * m_pmainStack;
	string szTitle;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file