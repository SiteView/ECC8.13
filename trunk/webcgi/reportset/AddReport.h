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
#include "..\svtable\AnswerTable.h"
class WPushButton;
class WLineEdit;
class WCheckBox;
class WComboBox;
class WText;
class WTable;
class WImage;
class CCheckBoxTreeView;
class WTreeNode;


class WSVMainTable;
class WSVButton;
class WSTreeAndPanTable;
class WSVFlexTable;

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
#include <list>
using namespace std;

#include "define.h"


//////////////////////////////////////////////////////////////////////////////////
// class CSVAddReport

class CSVAddReport : public WContainerWidget
{
    //MOC: W_OBJECT CSVAddReport:WContainerWidget
    W_OBJECT;
public:
    CSVAddReport(WContainerWidget * parent = 0);

    void setProperty(SAVE_REPORT_LIST * report);

    void clearData();

	void initTree(std::string strUser);
	WTable * pFrameTable;

	void setGroupRightCheck(std::string groupright);
	void SetGroupChecked(WTreeNode*pNode,  std::string  pGroupRightList_,bool bPCheck=false);
public:
	WText * m_pAnswerTitle;
	std::string chgstr;
	
	std::string strErrorTitle;
	std::string strInError;

	CAnswerTable* AnswerTable;

public signals:
    //MOC: EVENT SIGNAL CSVAddReport::BackTo(std::string)
	void BackTo(std::string);
    //MOC: EVENT SIGNAL CSVAddReport::SavePhone(SAVE_REPORT_LIST)
    void SavePhone(SAVE_REPORT_LIST phone);
    //MOC: EVENT SIGNAL CSVAddReport::ExChangeAddEvent()
	void ExChangeAddEvent();
private slots:
    //MOC: SLOT CSVAddReport::Back()
	void Back();
    //MOC: SLOT CSVAddReport::Save()
    void Save();
	//MOC: SLOT CSVAddReport::hideAddPhoneList()
    void hideAddPhoneList();
	//MOC: SLOT CSVAddReport::showAddPhoneList()
	void showAddPhoneList();
	//MOC: SLOT CSVAddReport::hideAddReport()
	void hideAddReport();
	//MOC: SLOT CSVAddReport::showAddReport()
	void showAddReport();
	//MOC: SLOT CSVAddReport::AddPhoneHelp()
	void AddPhoneHelp();
	//MOC: SLOT CSVAddReport::TestSMS()
	void TestSMS();
	//MOC: SLOT CSVAddReport::TestSMSing()
	void TestSMSing();
	//MOC: SLOT CSVAddReport::Translate()
	void Translate();
	//MOC: SLOT CSVAddReport::ExChangeAdd()
	void ExChangeAdd();

	void ShowHelp();
private:
// functions
    void initForm();
    void loadString();
	std::string GetSelScope();
// member


	//new report add
	WImage * pHide1;
	WImage * pShow1;
	WTable * pTable1;
	//end new report add
  

    WCheckBox * m_pDisable;
    WComboBox * m_pTemplate;
	WImage * m_pHelpImg;
    
    WText     * m_pErrMsg; 
	WText     * m_pErrMsgSamePhone;

	WText * pTestShowInfo;
	WText * m_pConnErr;


	bool IsHelp;

	//add report help
	WText * m_pHelpTitle;
	WText * m_pErrorTitle;
	WText * m_pHelpDescript;
	WText * m_pHelpPeriod;
	WText * m_pHelpOpt;
	
	WLineEdit * m_pTitle;
	WLineEdit * m_pDescript;
	WComboBox * m_pPeriod;
	WCheckBox * m_pStatusResult;
	WCheckBox * m_pErrorResult;
	WCheckBox * m_pGraphic;
	WComboBox * m_pComboGraphic;
	WCheckBox * m_pListData;
	WCheckBox * m_pListNormal;
	WCheckBox * m_pListError;
	WCheckBox * m_pListDanger;
	WCheckBox * m_pListAlert;
	//Ticket #123     -------�պ�
	WCheckBox * m_pGenExcel;
	//Ticket #123     -------�պ�

	WText * m_pHelpEmailSend;
	WLineEdit * m_pEmailSend;
	
	WText * m_pHelpParameter;
	WCheckBox * m_pParameter;

	WText * m_pHelpDeny;
	WCheckBox * m_pDeny;

	WText * m_pHelpGenerate;
	WComboBox * m_pGenerate;

	WCheckBox * m_pClicketSet;
	WText * m_pHelpClicket;
	WLineEdit * m_pClicket;

	WComboBox * m_pPlan;
	WText * m_pHelpPlan;

	WCheckBox * m_pListClicket;

	CCheckBoxTreeView *pGroupTree;

	WLineEdit * m_pStartTime;
	//WLineEdit * m_pEndTime;
	WComboBox * m_pEndTime;
	WComboBox * m_pEndMinute;

	WText * m_pHelpStartTime;
	WText * m_pHelpEndTime;

	WComboBox *m_pWeekEndBox;

	WText * m_pHelpWeekPlan;

public :
	//New UI Version
	WSTreeAndPanTable *m_pTreePanTabel;
	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pReportTable;
	WSVButton *m_pSave;
	WSVButton *m_pCancel;

	WPushButton *pTranslateBtn;
	WPushButton *pExChangeBtn;

	void setTitle(string title);

private:
	string strTranslate;
	string strTranslateTip;
	string strRefresh;
	string strRefreshTip;
	string strEditReport;
	string strAddReport;

	void InitTreeTable();
	void InitReportTable(WSVFlexTable **pFlexTable_Add ,int nRow,std::string strTitle, WSVMainTable ** pUserTable);
	void AddJsParam(const std::string name, const std::string value);
	

	std::string chg ;

	std::list<string> pGroupRightList;
	std::list<string> pUnGroupRightList;
	void GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_ ,std::list<string > &pUnGroupRightList_);
	
	
	void GetGroupRightList();

	//end add report help

    typedef struct _FORM_SHOW_TEXT
    {
   
		string szReportAddTitle;
		string szReportTitle; string szReportTitleHelp;
		string szReportDescript; string szReportDescriptHelp;
		string szReportPeriod; string szReportPeriodHelp;
		string szReportOption; string szReportOptionHelp;
		string szReportOptStatus; string szReportOptError;
		string szReportOptGraphic1; string szReportOptGraphic2;
		string szReportGenerateTimeHelp;
		string szReportOptData; string szReportOptNormal;
		string szReportOptError1; string szReportOptDanger;
		string szReportOptAlert; string szReportEmailSend;
		string szReportEmailSendHelp; 
		string szReportParameter; string szReportParameter1; string szReportParameterHelp; 
		string szReportDeny; string szReportDeny1; string szReportDenyHelp;
		string szReportGenerateTime;
		string szReportWeek; string szReportWeekHelp;

		string szSave; string szBack;
		string szConnErr;
		string szClicket;
		string szClicketHelp;
		string szSameSection;
		string szTimeUnit;
		string szDayPeriod; string szWeekPeriod; string szMonthPeriod;
		string szTaskDes1; string szHelpTaskDes; string szPlanTypeRel;
		string szListClicket;

		string szStartTime; string szEndTime;
		string szHelpStartTime; string szHelpEndTime;
		string szHelpPlan; string szWeekEndTime;
		string szWeek1;string szWeek2;string szWeek3;string szWeek4;
		string szWeek5;string szWeek6;string szWeek7;
		string szHelpWeek;
		string szScopeError;
		string szAlertArea;
		string szAreaMap;
public: /*
        _FORM_SHOW_TEXT()
        {
			szListClicket = "�г���ֵ";
			szPlanTypeRel = "�������ƻ�";
			szTaskDes1 = "ִ�мƻ�����";
			szHelpTaskDes = "�趨ִ�мƻ������ʱ�䣬�磺��������һ����10:00��22:00";
			szDayPeriod = "�ձ�";
			szWeekPeriod = "�ܱ�";
			szMonthPeriod = "�±�";
			szTimeUnit = "ʱ";
			szReportAddTitle = "���ӱ���";
			szReportTitle = "������⣺";
			szReportTitleHelp = "��ʾ�ڱ�����Ϸ��򱨸��б���";
			szReportDescript = "����������";
			szReportDescriptHelp = "�Ա���ı�ע����ѡ��";
			
			szReportPeriod = "ʱ�����ڣ�";
			szReportPeriodHelp = "��ָ�����ɱ����ʱ������";
			szReportOption = "����ѡ�";
			szReportOptionHelp = "��ָ�����ɱ���Ҫ��ʾ����Ŀ";

			szReportOptStatus = "�г�״̬�ܽ�";
			szReportOptError = "�г�����";
			szReportOptGraphic1 = "��״ͼ";
			szReportOptGraphic2 = "��״ͼ";
			szReportOptData = "�г�����";
			szReportOptNormal = "�г�����";
			szReportOptError1 = "�г�����";
			szReportOptDanger = "�г�Σ��";
			szReportOptAlert = "�г����͵ı���";


			szReportEmailSend = "��E-mail��ʽ���ͱ��棺";
			szReportEmailSendHelp = "��������������ռ�����ĵ�ַ,����ʼ���ַ�Զ��ŷָ�.���潫�����úõ�ʱ����"\
				"�Զ����ɲ����͵��¿������ַ��";
			szReportParameter = "��ʾ������ϸ������";
			szReportParameterHelp = "ѡ������, ��������з���ֵ�ļ�����������ʾ�ڱ�����, ����ֻ����ʾÿ��������Ҫ����";
			szReportParameter1 = "��ʾ������ϸ��Ϣ";
			szReportDeny = "��ֹ���棺";
			szReportDeny1 = "��ʱ��ֹ����";
			szReportDenyHelp = "��ѡ������,���潫ֹͣ�Զ�����";
			szReportGenerateTime = "��������ʱ�䣺";
			szReportGenerateTimeHelp = "��ѡ������, ������ָ��ʱ������,��λ��ʱ";
			szReportWeek = "�ܱ����ã�";
			szReportWeekHelp = "��ѡ������, ���潫��ָ�����������ɱ���,��λ����";
			szClicket = "��ֵ����:";
			szClicketHelp = "��ֵ����";

			szSave = "����";
			szBack = "ȡ��";
			szConnErr = "����SVDBʧ��";
			szSameSection = "����ͬ�ı���";

			szStartTime = "��ʼʱ��";
			szEndTime = "�ձ���ֹʱ��";
			szHelpStartTime = "�趨���濪ʼʱ�䣬�磺10:00";
			szHelpEndTime = "�趨�����ֹʱ�䣬�磺22:00���ձ�����ʱ��ӵ���22:00������22:00";
			szWeekEndTime="�ܱ���ֹʱ��";

			szHelpPlan = "ֻʹ��ָ��ִ�мƻ��ڲɼ�������";

			szWeek1 ="����";
			szWeek2 ="��һ";
			szWeek3 ="�ܶ�";
			szWeek4 ="����";
			szWeek5 ="����";
			szWeek6 ="����";
			szWeek7 ="����";
			szHelpWeek ="�����ܱ�����ʱ��,�� ������һ���ܱ����ɷ�ΧΪ ������0�㵽������0��";
			szScopeError="���淶ΧΪ��";
        } */
    }SHOW_TEXT;
    SHOW_TEXT m_formText;


    SAVE_REPORT_LIST m_report;

    struct SV_SMS_ERROR_MESSAGE
    {
        WText * m_pNameErr;
        WText * m_pPhoneErr;
    };
    SV_SMS_ERROR_MESSAGE m_Err;

	string id;	

	string strTotalReport;
	string strTypeAdd;
	string strTypeEdit;

};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file

