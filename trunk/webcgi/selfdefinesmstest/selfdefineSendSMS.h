//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_EMAIL_SET_SEND_H_
#define _SV_EMAIL_SET_SEND_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib
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
//#include "WSVButton.h"

using namespace std;

#include "defines.h"
class CSVSelfDefineSendSMS : public WContainerWidget
{
    //MOC: W_OBJECT CSVSelfDefineSendSMS:WContainerWidget
    W_OBJECT;
public:
    CSVSelfDefineSendSMS(WContainerWidget *parent = 0);
    void SendTestForm();
	void refresh();
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
    //MOC: EVENT SIGNAL CSVSelfDefineSendSMS::BackMailset()
    void BackMailset();
private slots:
    //MOC: SLOT CSVSelfDefineSendSMS::SendTest()
    void SendTest();
    //MOC: SLOT CSVSelfDefineSendSMS::Back()
    void Back();
    //MOC: SLOT CSVSelfDefineSendSMS::SendMouseMove()
    void SendMouseMove();
	//MOC: SLOT CSVSelfDefineSendSMS::Translate()
	void Translate();
	//MOC: SLOT CSVSelfDefineSendSMS::ExChange()
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

	WText * m_pSerialNum ;

    string m_szEmailTo;
    string m_szEmailSubject;
    string m_szEmailContent;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	std::string strSMSTest;
	std::string strClose;
	std::string strTestSMSCaption;
	std::string strTestSMSContent;
	std::string strSelfDefineTitle;

	std::string index ;
	std::string strparam;
	std::string strSelfdefineTest;

    SEND_MAIL_PARAM m_sendParam;
	
    typedef struct _FORM_SHOW_TEXT
    {
        string szTitle, szMailTo, szMailToDes, szBack, szSend;		
        string szStateOK, szSubject, szSubjectDes, szContent;
        string szContext; string szStateFailed;
        string szErrMail; string szSending; string szSendHelp; 
        string szSubjectText;string szErrMobile;
		string szError,szSMSSending;
    }FORM_SHOW_TEXT;
    FORM_SHOW_TEXT m_formText;

private:
    void showErrorMsg(string &szErrMsg);
    bool checkEmail();
	bool InitSerialPort();
};


#endif
//////////////////////////////////////////////////////////////////////////////////
// end file
