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
#include <WApplication>
//////////////////////////////////////////////////////////////////////////////////

#include "../svtable/WSPopTable.h"
#include "WSVButton.h"
#include "../svtable/WSPopButton.h"

// include stl lib && using namespace std
#include <iostream>
#include <string>



using namespace std;

class WSPopTable;

#include "defines.h"
class CSVSendMail : public WContainerWidget
{
    //MOC: W_OBJECT CSVSendMail:WContainerWidget
    W_OBJECT;
public:
    CSVSendMail(WContainerWidget *parent = 0);
	virtual void refresh();
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
    //MOC: EVENT SIGNAL CSVSendMail::BackMailset()
    void BackMailset();
private slots:
    //MOC: SLOT CSVSendMail::SendTest()
    void SendTest();
    //MOC: SLOT CSVSendMail::Back()
    void Back();
    //MOC: SLOT CSVSendMail::SendMouseMove()
    void SendMouseMove();
	//MOC: SLOT CSVSendMail::Translate()
	void Translate();
	//MOC: SLOT CSVSendMail::ExChange()
	void ExChange();    
private:
    WLineEdit * pMailTo;
    WLineEdit * pMailSubject;
    WLineEdit * pMailContent;
    WLineEdit * pState;
    WPushButton * pSendTest;
    WText * m_pErrMsg;
	WTextArea* pStateTextArea; 
	//WLineEdit * pStateTextArea; 
    string m_szEmailTo;
    string m_szEmailSubject;
    string m_szEmailContent;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	WSPopTable *m_pMainTable;
	WSPopButton  *pTestBtn;
	WSPopButton  *pCloseBtn;
	WTable	   *pSendTable;
	WTable	   *pResultTable;

	WLineEdit * m_pServer;

    SEND_MAIL_PARAM m_sendParam;
	
    typedef struct _FORM_SHOW_TEXT
    {
        string szTitle, szMailTo, szMailToDes, szBack, szSend;		
        string szStateOK, szSubject, szSubjectDes, szContent;
        string szContext; string szStateFailed;
        string szErrMail; string szSending;string szSendHelp; 
        string szSubjectText, szClose, szSmtp;
		string szError,szMailSending;
		string szRowTitle;
    }FORM_SHOW_TEXT;
    FORM_SHOW_TEXT m_formText;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
private:
    void showErrorMsg(string &szErrMsg);
    bool checkEmail();
};


#endif
//////////////////////////////////////////////////////////////////////////////////
// end file
