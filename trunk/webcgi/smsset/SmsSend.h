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
            szErrPhone = "�ֻ������ʽ����!!";
            szContentDes = "�������ݣ��������������";
            szPhoneDes = "�ֻ����룺���շ��ֻ����룬����ֻ������ʹ��Ӣ�Ķ��ŷָ�";
            szSend = "����"; 
            szBack = "����";
            szSending = "���ڷ����ֻ�����...";
            szSendSuc = "���Զ��ŷ��ͳɹ�...";
            szSendFail = "���Զ��ŷ���ʧ��...";
        }*/
    }SHOW_TEXT;
};
// end class
//////////////////////////////////////////////////////////////////////////////////

#endif
//////////////////////////////////////////////////////////////////////////////////
// end file
