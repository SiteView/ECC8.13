//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_SMS_SET_ADD_PHONE_H_
#define _SV_SMS_SET_ADD_PHONE_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WContainerWidget"
class WPushButton;
class WLineEdit;
class WCheckBox;
class WComboBox;
class WText;
class WTable;
class WImage;

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

#include "define.h"


class CTaskList;

//////////////////////////////////////////////////////////////////////////////////
// class CSVAddPhone

class CSVAddPhone : public WContainerWidget
{
    //MOC: W_OBJECT CSVAddPhone:WContainerWidget
    W_OBJECT;
public:
    CSVAddPhone(WContainerWidget * parent = 0);

    void setProperty(SAVE_PHONE_LIST * phone);

    void clearData();
public:
	string chgstr;
	int iValue;
public signals:
    //MOC: EVENT SIGNAL CSVAddPhone::BackTo()
    void BackTo();
    //MOC: EVENT SIGNAL CSVAddPhone::SavePhone(SAVE_PHONE_LIST)
    void SavePhone(SAVE_PHONE_LIST phone);
    //MOC: EVENT SIGNAL CSVAddPhone::ExChangeAddEvent()
    void ExChangeAddEvent();
private slots:
    //MOC: SLOT CSVAddPhone::Back()
    void Back();
    //MOC: SLOT CSVAddPhone::Save()
    void Save();
	//MOC: SLOT CSVAddPhone::hideAddPhoneList()
    void hideAddPhoneList();
	//MOC: SLOT CSVAddPhone::showAddPhoneList()
	void showAddPhoneList();
	//MOC: SLOT CSVAddPhone::AddPhoneHelp()
	void AddPhoneHelp();
	//MOC: SLOT CSVAddPhone::TestSMS()
	void TestSMS();
	//MOC: SLOT CSVAddPhone::TestSMSing()
	void TestSMSing();
	//MOC: SLOT CSVAddPhone::Translate()
	void Translate();
	//MOC: SLOT CSVAddPhone::ExChangeAdd()
	void ExChangeAdd();
private:
// functions
    void initForm();
    void loadString();
	void errorTest(const string &errorMsg);
// member
	//new add by jiangxian
	WImage * pHide;
	WImage * pShow;
	WTable * pTable;
	WSVFlexTable * m_pGeneral;
	WComboBox * m_pSchedule;
	//new add end
    WLineEdit * m_pName;
    WLineEdit * m_pPhone;
	WText     * m_pHelpName;
	WText     * m_pHelpPhone;
	WText     * m_pHelpDisabled;
	WText     * m_pHelpTemplate;
	WText     * m_pHelpPlan;
	WText     * m_pErrorName;

    WCheckBox * m_pDisable;
    WComboBox * m_pTemplate;
	WImage * m_pHelpImg;
    
    WText     * m_pErrMsg; 
	WText     * m_pErrMsgSamePhone;

	WText * pTestShowInfo;
	WText * m_pConnErr;

    CTaskList * m_pTasklist;

	bool IsHelp;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

    typedef struct _FORM_SHOW_TEXT
    {
        string szTitle; string szNameDes; string szDisableDes;
        string szDisable;
        string szTemplateDes; string szPhoneDes;
        string szTaskDes; string szAdvTitleDes;
        string szErrName; string szErrPhone;
        string szSave; string szBack;
		string szPlanLabel;
		
		string szHelpDisableDes; string szHelpNameDes; 
		string szHelpPhoneDes; string szHelpTaskDes;
		string szHelpTemplateDes;

		string szNameDes1 ; string szPhoneDes1;
		string szDisableDes1; string szTaskDes1;
		string szTemplateDes1;
		string szSelDefault; string szSelLast;
		string szAddTitle;
		string szErrorMsg1;
		string szPlanTypeRel;
		string szTestBut;
		string szSending;
		string szSendSuc;
		string szSendFail;
		string szConnErr;
		string szErrorNameDes;
public:/*
        _FORM_SHOW_TEXT()
        {
			szSelDefault = "Default";
			szSelLast = "SelfDefine";
            szTitle = "��Ӷ��Ž����ֻ�������";
			szNameDes1 = "����";
			szHelpNameDes = "�����ƽ�����Ӷ��ű���ʱ��ʾ�ڡ����������ֻ���" \
                "���б����Զ�Ӧ��������������ֻ�����";
			szErrorNameDes = "�����ظ�����ѡ������������";
			szDisableDes1 = "��ֹ";
			szHelpDisableDes = "ѡ�����󣬱����������͵�ָ�����ֻ���";
            szDisable = "��ֹ";
            
			szPhoneDes1 = "�����ֻ���";
			szHelpPhoneDes = "�������ֻ������ֻ���֮����Ӣ�Ķ��ŷָ�";
            
			szTemplateDes1 = "����ģ��";
			szHelpTemplateDes = "��ѡ��һ������ģ��󣬴�ģ�彫�����ڷ��Ͷ�����Ϣ";
            szAdvTitleDes = "�߼�ѡ��";
            
			szTaskDes1 = "ִ�мƻ�";
			szHelpTaskDes = "�趨ִ�мƻ������ʱ�䣬�磺��������һ����10:00��22:00";
            
			szSave = "���渽������";
            szBack = "����";
            szErrPhone = " [ �ֻ����벻��Ϊ�� ] ";
            szErrName = " [ ���Ʋ���Ϊ�� ] ";
			szPlanLabel = "�ƻ�";
			szAddTitle = "�ֻ���������";
			szErrorMsg1 = "����ͬ���绰";
			szPlanTypeRel = "�������ƻ�";
			szTestBut = "����";
			szSending = "���ڷ����ֻ�����...";
            szSendSuc = "���Զ��ŷ��ͳɹ�...";
            szSendFail = "���Զ��ŷ���ʧ��...";
			szConnErr = "connect svdb failure!";
        }*/
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

    SAVE_PHONE_LIST m_phone;

	string m_pEditPhoneName;

    struct SV_SMS_ERROR_MESSAGE
    {
        WText * m_pNameErr;
        WText * m_pPhoneErr;
    };
    SV_SMS_ERROR_MESSAGE m_Err;

	string id;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

	std::string strTypeAdd;
	std::string strTypeEdit;
	string strSMSConfig;

	string strSaveAdd;
	string strCancelAdd;

};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file

