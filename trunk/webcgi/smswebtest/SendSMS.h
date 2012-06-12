//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_EMAIL_SET_SEND_H_
#define _SV_EMAIL_SET_SEND_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib
#include "svwebsms.h"
#include <WContainerWidget>
#include <WPushButton>
#include <WLineEdit>
#include <WTextArea>
#include <WText>
#include <WImage>
#include <WTable>
class WApplication;
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>

#include "../svtable/WSPopTable.h"
#include "WSPopButton.h"
#include "WSVButton.h"

using namespace std;

#include "defines.h"
class CSVSendSMS : public WContainerWidget
{
    //MOC: W_OBJECT CSVSendSMS:WContainerWidget
    W_OBJECT;
public:
    CSVSendSMS(WContainerWidget *parent = 0);
	void refresh();
    void SendTestForm();
    void ClearState() 
    {
        if (pState)
            pState -> setText("");
    }
    void setSendParam(SEND_MAIL_PARAM sendParam)
    {
        m_sendParam = sendParam;
        pMailTo -> setText(m_sendParam.m_szFrom);
        pMailSubject -> setText("Siteview ²âÊÔ");
        pMailContent -> setText("This is test!!!");
    }
	void AddJsParam(const std::string name, const std::string value);
	WApplication*  appSelf;
public signals:
    //MOC: EVENT SIGNAL CSVSendSMS::BackMailset()
    void BackMailset();
private slots:
    //MOC: SLOT CSVSendSMS::SendTest()
    void SendTest();
    //MOC: SLOT CSVSendSMS::Back()
    void Back();
    //MOC: SLOT CSVSendSMS::SendMouseMove()
    void SendMouseMove();
	//MOC: SLOT CSVSendSMS::Translate()
	void Translate();
	//MOC: SLOT CSVSendSMS::ExChange()
	void ExChange();      
private:
    WLineEdit * pMailTo;
    WLineEdit * pMailSubject;
    WLineEdit * pMailContent;

    WLineEdit * pState;

	/*WPushButton * pSendTest;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;*/
	WSPopButton * pSendTest;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;
	WSPopTable * pMainTable;

    WText * m_pErrMsg;

	WTextArea* pStateTextArea; 
	//WText * pStateTextArea;

	WText * m_pUser;

    string m_szEmailTo;
    string m_szEmailSubject;
    string m_szEmailContent;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	std::string strClose;

	string strWebTest;

    SEND_MAIL_PARAM m_sendParam;
	
    typedef struct _FORM_SHOW_TEXT
    {
        string szTitle, szMailTo, szMailToDes, szBack, szSend;		
        string szStateOK, szSubject, szContent;
        string szContext; string szStateFailed;
        string szErrMail; string szSending; string szSendHelp; 
        string szSubjectText;string szErrMobile;
		string szError,szSMSSending;
    }FORM_SHOW_TEXT;
    FORM_SHOW_TEXT m_formText;

	CSVWebSMS m_webSMS;
private:
    void showErrorMsg(string &szErrMsg);
};


#endif
//////////////////////////////////////////////////////////////////////////////////
// end file
