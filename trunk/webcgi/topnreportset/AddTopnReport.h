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
#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"
#include "..\svtable\FlexTable.h"
#include "..\svtable\AnswerTable.h"
#include "../../kennel/svdb/svapi/svapi.h"

class WPushButton;
class WLineEdit;
class WCheckBox;
class WComboBox;
class WText;
class WTable;
class WImage;
class WRadioButton;

class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class WSTreeAndPanTable;
//class CCheckBoxTreeView;
//class WTreeNode;

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

#include "define.h"
#include "svapi.h"


//////////////////////////////////////////////////////////////////////////////////
// class CSVAddTopnReport

class CSVAddTopnReport : public WContainerWidget
{
    //MOC: W_OBJECT CSVAddTopnReport:WContainerWidget
    W_OBJECT;
public:
    CSVAddTopnReport(WContainerWidget * parent = 0);
	~CSVAddTopnReport(void);


    void setProperty(SAVE_REPORT_LIST * report);

    void clearData();
	void upData();
	void initTree();

	void setGroupRightCheck(std::string groupright);
	void SetGroupChecked(WTreeNode*pNode,  std::string  pGroupRightList_ ,bool bPCheck);

	std::list<sv_pair> Sort(PAIRLIST retlist);

	CAnswerTable* AnswerTable;
	std::string strErrorTitle;
	std::string strInError;
	OBJECT objRes;
	MAPNODE ResNode;
public:
	std::string chgstr;
	bool bRadioSort;
	std::list<sv_pair> strRet ;
	WTable * pFrameTable;


	WPushButton *pTranslateBtn;
	WPushButton *pExChangeBtn;

	WSTreeAndPanTable *m_pTreePanTabel;
	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pReportTable;
	WSVButton *m_pSave;
	WSVButton *m_pCancel;


	string chg;
	std::string GetLabelResource(std::string strLabel);
public signals:
    //MOC: EVENT SIGNAL CSVAddTopnReport::BackTo(std::string)
    void BackTo(std::string);
    //MOC: EVENT SIGNAL CSVAddTopnReport::SaveTopnReport(SAVE_REPORT_LIST)
    void SaveTopnReport(SAVE_REPORT_LIST phone);
    //MOC: EVENT SIGNAL CSVAddTopnReport::ExChangeAddEvent()
    void ExChangeAddEvent();
private slots:
    //MOC: SLOT CSVAddTopnReport::Back()
    void Back();
    //MOC: SLOT CSVAddTopnReport::Save()
    void Save();
	//MOC: SLOT CSVAddTopnReport::hideAddPhoneList()
    void hideAddPhoneList();
	//MOC: SLOT CSVAddTopnReport::showAddPhoneList()
	void showAddPhoneList();
	//MOC: SLOT CSVAddTopnReport::hideAddReport()
	void hideAddReport();
	//MOC: SLOT CSVAddTopnReport::showAddReport()
	void showAddReport();
	//MOC: SLOT CSVAddTopnReport::AddPhoneHelp()
	void AddPhoneHelp();
	//MOC: SLOT CSVAddTopnReport::TestSMS()
	void TestSMS();
	//MOC: SLOT CSVAddTopnReport::TestSMSing()
	void TestSMSing();
	//MOC: SLOT CSVAddTopnReport::RadioSort1()
	void RadioSort1();
	//MOC: SLOT CSVAddTopnReport::RadioSort2()
	void RadioSort2();
	//MOC: SLOT CSVAddTopnReport::SelActive(int)
	void SelActive(int);
	//MOC: SLOT CSVAddTopnReport::Translate()
	void Translate();
	//MOC: SLOT CSVAddTopnReport::ExChangeAdd()
	void ExChangeAdd();
private:
// functions
    void initForm();
    void loadString();
// member


	string strTranslate;
	string strTranslateTip;
	string strRefresh;
	string strRefreshTip;
	string strEditReport;
	string strAddReport;
	string szTopTitle;


	void InitTreeTable();
	void InitReportTable(WSVFlexTable **pFlexTable_Add ,int nRow,std::string strTitle, WSVMainTable ** pUserTable);


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

	WText * m_pHelpPlan;

	//top report
	WComboBox * m_pSelType;
	WText * m_pHelpSelType;
	WComboBox * m_pSelMark;
	WText * m_pHelpSelMark;
	WRadioButton * m_pSelSort1;
	WRadioButton * m_pSelSort2;
	WText * m_pHelpSelSort;
	WLineEdit * m_pCount;
	WText * m_pHelpCount;

	WComboBox * m_pPlan;
	WComboBox * m_pValueCombo;

	WComboBox *m_pWeekEndBox;
	WText * m_pHelpWeekPlan;
	//	WText * m_pHelpPlan;

	CCheckBoxTreeView *pGroupTree;
	std::list<string> pGroupRightList;
	std::list<string> pUnGroupRightList;
	void GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_ ,std::list<string > &pUnGroupRightList_);
	

	void AddJsParam(const std::string name, const std::string value);
	
	
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
		string szReportEmailSend;
		string szReportEmailSendHelp; 
		string szReportParameter; string szReportParameter1; string szReportParameterHelp; 
		string szReportDeny; string szReportDeny1; string szReportDenyHelp;
		string szReportGenerateTime;
		string szReportWeek; string szReportWeekHelp;

		//topn report
		string szTopnReportSelType;
		string szTopnReportSelTypeHelp;
		string szTopnReportSelMark;
		string szTopnReportSelMarkHelp;
		string szTopnReportSelSort;
		string szTopnReportSelSort1;
		string szTopnReportSelSort2;
		string szTopnReportSelSortHelp;
		string szTopnReportCount;
		string szTopnReportCountHelp;

		string szSave; string szBack;
		string szConnErr;

		string szSameSection;
		string szSortDes;
		string szSortAsc;
		string szDayReport;
		string szWeekReport;
		string szMonthReport;
		string szMark1;
		string szPlanTypeRel;
		string szTaskDes1;
		string szHelpTaskDes;
		string szHelpPlan;
		string szGetValue;
		string szGetValuePer;
		string szGetValueNew;

		string szWeek1;string szWeek2;string szWeek3;string szWeek4;
		string szWeek5;string szWeek6;string szWeek7;
		string szHelpWeek;
		string szWeekEndTime;
		string szScopeError;
public:
        _FORM_SHOW_TEXT()
        {
/*			szTaskDes1 = "ִ�мƻ�����";
			szHelpTaskDes = "�趨ִ�мƻ������ʱ�䣬�磺��������һ����10:00��22:00";
			szPlanTypeRel = "2";//�������ƻ�
			szReportAddTitle = "���TopN����";
			szReportTitle = "�������";
			szReportTitleHelp = "��ʾ�ڱ�����Ϸ��򱨸��б���";
			szReportDescript = "��������";
			szReportDescriptHelp = "�Ա���ı�ע����ѡ��";
			
			szReportPeriod = "ʱ�����ڣ�";
			szReportPeriodHelp = "��ָ�����ɱ����ʱ������";
			szReportOption = "����ѡ��";
			szReportOptionHelp = "��ָ�����ɱ���Ҫ��ʾ����Ŀ";
			szReportEmailSend = "��E-mail��ʽ���ͱ���";
			szReportEmailSendHelp = "��������������ռ�����ĵ�ַ,����ʼ���ַ�Զ��ŷָ�.���潫�����úõ�ʱ����"\
				"�Զ����ɲ����͵��¿������ַ��";
			szReportParameter = "��ʾ������ϸ����";
			szReportParameterHelp = "ѡ������, ��������з���ֵ�ļ�����������ʾ�ڱ�����, ����ֻ����ʾÿ��������Ҫ����";
			szReportParameter1 = "��ʾ������ϸ��Ϣ";
			szReportDeny = "��ֹ����";
			szReportDeny1 = "��ʱ��ֹ����";
			szReportDenyHelp = "��ѡ������,���潫ֹͣ�Զ�����";
			szReportGenerateTime = "��������ʱ��";
			szReportGenerateTimeHelp = "��ѡ������, ������ָ��ʱ������,��λ��ʱ";
			szReportWeek = "�ܱ�����";
			szReportWeekHelp = "��ѡ������, ���潫��ָ�����������ɱ���,��λ����";


			szSave = "����";
			szBack = "ȡ��";
			szConnErr = "connect svdb failure!";
			szSameSection = "have same section in ini file";

			szTopnReportSelType = "ѡ������";
			szTopnReportSelTypeHelp = "ѡ��Ҫͳ�Ƶļ��������";
			szTopnReportSelMark = "ѡ��ָ��";
			szTopnReportSelMarkHelp = "ѡ������ָ������";			
			szTopnReportSelSort = "ѡ������ʽ��";
			szTopnReportSelSort1 = "����";
			szTopnReportSelSort2 = "����";
			szTopnReportSelSortHelp = "ѡ������ʽ";
			szTopnReportCount = "����";
			szTopnReportCountHelp = "����Ҫͳ�Ƶļ��������";
			szSortDes = "����";
			szSortAsc = "����";
			szDayReport = "�ձ�";
			szWeekReport = "�ܱ�";
			szMonthReport = "�±�";

			szHelpPlan = "ֻʹ��ָ��ִ�мƻ��ڲɼ�������";
			szGetValue = "ȡֵ��ʽ";
			szGetValuePer = "ƽ��";
			szGetValueNew = "����";�����ա�����һ�����ڶ������� ������ 

			szWeekEndTime="�ܱ���ֹʱ��";
			szWeek1 ="������";
			szWeek2 ="����һ";
			szWeek3 ="���ڶ�";
			szWeek4 ="������";
			szWeek5 ="������";
			szWeek6 ="������";
			szWeek7 ="������";
			szHelpWeek ="�����ܱ�����ʱ��,�� ������һ���ܱ����ɷ�ΧΪ ������0�㵽������0��";*/
			szMark1 = ""; 
        }
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
	string strTopNReport;
	std::string strTypeAdd;
	std::string strTypeEdit;
	string strAlertArea;
};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file

