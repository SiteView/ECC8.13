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
	//Ticket #123     -------苏合
	WCheckBox * m_pGenExcel;
	//Ticket #123     -------苏合

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
			szListClicket = "列出阀值";
			szPlanTypeRel = "相对任务计划";
			szTaskDes1 = "执行计划过滤";
			szHelpTaskDes = "设定执行计划允许的时间，如：允许星期一，从10:00到22:00";
			szDayPeriod = "日报";
			szWeekPeriod = "周报";
			szMonthPeriod = "月报";
			szTimeUnit = "时";
			szReportAddTitle = "增加报告";
			szReportTitle = "报告标题：";
			szReportTitleHelp = "显示在报告的上方或报告列表中";
			szReportDescript = "报告描述：";
			szReportDescriptHelp = "对报告的备注（可选）";
			
			szReportPeriod = "时间周期：";
			szReportPeriodHelp = "请指定生成报告的时间周期";
			szReportOption = "报告选项：";
			szReportOptionHelp = "请指定生成报告要显示的项目";

			szReportOptStatus = "列出状态总结";
			szReportOptError = "列出错误";
			szReportOptGraphic1 = "线状图";
			szReportOptGraphic2 = "柱状图";
			szReportOptData = "列出数据";
			szReportOptNormal = "列出正常";
			szReportOptError1 = "列出错误";
			szReportOptDanger = "列出危险";
			szReportOptAlert = "列出发送的报警";


			szReportEmailSend = "以E-mail方式发送报告：";
			szReportEmailSendHelp = "在下面框中添入收件邮箱的地址,多个邮件地址以逗号分隔.报告将以设置好的时间间隔"\
				"自动生成并发送到下框所添地址中";
			szReportParameter = "显示监测的详细参数：";
			szReportParameterHelp = "选择此项后, 监测器所有返回值的监测情况都会显示在报告里, 否则只会显示每个监测的主要参数";
			szReportParameter1 = "显示监测的详细信息";
			szReportDeny = "禁止报告：";
			szReportDeny1 = "临时禁止报告";
			szReportDenyHelp = "当选择此项后,报告将停止自动生成";
			szReportGenerateTime = "报告生成时间：";
			szReportGenerateTimeHelp = "当选择此项后, 报告在指定时间生成,单位：时";
			szReportWeek = "周报设置：";
			szReportWeekHelp = "当选择此项后, 报告将在指定的星期生成报告,单位：周";
			szClicket = "阀值设置:";
			szClicketHelp = "阀值输入";

			szSave = "保存";
			szBack = "取消";
			szConnErr = "连接SVDB失败";
			szSameSection = "有相同的报告";

			szStartTime = "开始时间";
			szEndTime = "日报截止时间";
			szHelpStartTime = "设定报告开始时间，如：10:00";
			szHelpEndTime = "设定报告截止时间，如：22:00，日报数据时间从当日22:00至昨日22:00";
			szWeekEndTime="周报截止时间";

			szHelpPlan = "只使用指定执行计划内采集的数据";

			szWeek1 ="周日";
			szWeek2 ="周一";
			szWeek3 ="周二";
			szWeek4 ="周三";
			szWeek5 ="周四";
			szWeek6 ="周五";
			szWeek7 ="周六";
			szHelpWeek ="设置周报生成时间,如 设置周一，周报生成范围为 本周日0点到上周日0点";
			szScopeError="报告范围为空";
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

