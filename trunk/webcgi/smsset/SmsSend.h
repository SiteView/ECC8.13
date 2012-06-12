//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_SMS_SET_SEND_H_
#define _SV_SMS_SET_SEND_H_

#if _MSC_VER > 1000
#pragma once
#endif
//////////////////////////////////////////////////////////////////////////////////
// include WT LIB
#include "../../opens/dll-wt/wt/WContainerWidget"
class WLineEdit;
//////////////////////////////////////////////////////////////////////////////////
// include STL Lib & using namespace std;
//////////////////////////////////////////////////////////////////////////////////
// start CSVSendSms
class CSVSendSms : public WContainerWidget
{
    //MOC: W_OBJECT CSVSendSms:WContainerWidget
    W_OBJECT;
public:
    CSVSendSms(WContainerWidget * parent = 0);
public signals:
    //MOC: EVENT SIGNAL CSVSendSms::ShowSetForm()
    void ShowSetForm();
private slots:
    //MOC: SLOT CSVSendSms::SendSms()
    void SendSms();
    //MOC: SLOT CSVSendSms::Back()
    void Back();

private:
    // functions
    void initForm();
    void showErrMsg(string strErrMsg);
    void loadString();
    // members
    WLineEdit * m_pPhone;
    WLineEdit * m_pContent;

    WText     * m_pState;
    WText     * m_pErrMsg;

    typedef struct _FORM_SHOW_TEXT
    {
        string szPhoneDes; string szContentDes;
        string szSend; string szBack;
        string szErrPhone;
        string szSending; string szSendSuc;
        string szSendFail;
public:/*
        _FORM_SHOW_TEXT()
        {
            szErrPhone = "手机号码格式错误!!";
            szContentDes = "短信内容：请输入短信内容";
            szPhoneDes = "手机号码：接收方手机号码，多个手机号码间使用英文逗号分隔";
            szSend = "发送"; 
            szBack = "返回";
            szSending = "正在发送手机短信...";
            szSendSuc = "测试短信发送成功...";
            szSendFail = "测试短信发送失败...";
        }*/
    }SHOW_TEXT;
};
// end class
//////////////////////////////////////////////////////////////////////////////////

#endif
//////////////////////////////////////////////////////////////////////////////////
// end file
