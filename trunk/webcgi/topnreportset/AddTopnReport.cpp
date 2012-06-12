#include "AddTopnreport.h"

//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WRadioButton"
#include "../../opens/libwt/WebSession.h"
#include "..\checkboxtreeview\WTreeNode.h"
#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "WSVFlexTable.h"
#include "WSVMainTable.h"
#include "WSVButton.h"
#include "WSTreeAndPanTable.h"

#include "..\base\basetype.h"


#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

typedef std::map<std::string, std::string> tmpmap;

extern void PrintDebugString(const char*);

CSVAddTopnReport::CSVAddTopnReport(WContainerWidget * parent /* = 0 */):
WContainerWidget(parent)
{
	new WText("<SCRIPT language='JavaScript' ></script>",this);
	IsHelp = true;
	bRadioSort = true;
    loadString();
    initForm();
	OutputDebugString("------------initForm3-------------\n");
}

//添加客户端脚本变量
void CSVAddTopnReport::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CSVAddTopnReport::initTree()
{

	std::string  strUserId;
	strUserId=GetWebUserID();
	pGroupTree->InitTree("",false,true,false,strUserId);
}
std::string CSVAddTopnReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
			strfieldlabel = strfieldlabel;
	return strfieldlabel;
}
CSVAddTopnReport::~CSVAddTopnReport(void)
{
		if( objRes !=INVALID_VALUE )
			CloseResource(objRes);
}
void CSVAddTopnReport::initForm()
{
	OutputDebugString("------------initForm1-------------\n");
	InitTreeTable();
	OutputDebugString("------------initForm2-------------\n");

	//Jansion.zhou 2006-12-26
	//m_pConnErr = new WText("", (WContainerWidget *)this);
	//m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	//m_pConnErr ->hide();
}


void CSVAddTopnReport::InitTreeTable()
{
	m_pTreePanTabel = new WSTreeAndPanTable(this);
	AddJsParam("treeviewPanel", m_pTreePanTabel->formName());



	m_pTreePanTabel->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	m_pTreePanTabel->elementAt(0, 0)->resize(WLength(200, WLength::Pixel), WLength(100, WLength::Percentage));
	m_pTreePanTabel->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);
	m_pTreePanTabel->elementAt(0, 1)->resize(WLength(4,WLength::Pixel),WLength(100,WLength::Percentage));


	//TreeTable
	new WText("<div id='tree_panel' name='tree_panel' class='panel_tree'>", m_pTreePanTabel->elementAt(0, 0));

	pFrameTable = new WTable(m_pTreePanTabel->elementAt(0, 0));
	pFrameTable ->setStyleClass("t3");

	//Jansion.zhou 2006-12-27
	//pFrameTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	//pFrameTable->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);
	//pFrameTable->elementAt(0, 0)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
	//pFrameTable->elementAt(0, 1)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));

	//WTable * pSubTreeTable = new WTable((WContainerWidget *)pFrameTable->elementAt(0,0));
	//pFrameTable->elementAt(0,0)->resize(WLength(200,WLength::Pixel),WLength(100,WLength::Percentage));

	//WTable * pUpTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	//pUpTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	//pUpTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	//new WText(strAlertArea, (WContainerWidget *)pUpTable->elementAt(0,0));

	//pGroupTree =new CCheckBoxTreeView((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	//pSubTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);

	WTable * pSubTreeTable = new WTable((WContainerWidget *)pFrameTable->elementAt(0,0));
	pFrameTable->elementAt(0,0)->resize(WLength(200,WLength::Pixel),WLength(100,WLength::Percentage));

	WTable * pUpTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	pUpTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	pUpTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	//new WText(m_formText.szAlertArea, (WContainerWidget *)pUpTable->elementAt(0,0));
	new WText("&nbsp;", (WContainerWidget *)pUpTable->elementAt(0,0));

	pGroupTree =new CCheckBoxTreeView((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	pSubTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);

	new WText("</div>", m_pTreePanTabel->elementAt(0, 0));


	//DragTable
	AddJsParam("drag_tree", m_pTreePanTabel->elementAt(0, 1)->formName());




	//PanTable
	new WText("<div id='view_panel' class='panel_view'>", m_pTreePanTabel->elementAt(0, 2));

	//m_pMainTable = new WSVMainTable(m_pTreePanTabel->elementAt(0, 2), szTopTitle, true);
	m_pMainTable = new WSVMainTable(m_pTreePanTabel->elementAt(0, 2), "编辑报告", true);

	if(m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(AddPhoneHelp()));
	}	

	InitReportTable(&m_pReportTable, 1, strAddReport, &m_pMainTable);

	new WText("</div>", m_pTreePanTabel->elementAt(0, 2));



	AddJsParam("uistyle", "treepan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	//new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>",this);
	//new WText("<SCRIPT language='JavaScript'>SetTreeViewPanel()</script>",this);
	//new WText("<SCRIPT language='JavaScript'>addLoadEvent(_OnLoad)</SCRIPT>", mainTable2->elementAt(0,0)); 
	new WText("<SCRIPT language='JavaScript'>addLoadEvent(_OnLoad)</SCRIPT>", this); 
}

void CSVAddTopnReport::InitReportTable(WSVFlexTable **pFlexTable_Add ,int nRow,std::string strTitle, WSVMainTable **pUserTable)
{
	//*pFlexTable_Add = new WSVFlexTable((WContainerWidget *)(*pUserTable)->GetContentTable()->elementAt(nRow,0), Group, strTitle);  
	*pFlexTable_Add = new WSVFlexTable((WContainerWidget *)(*pUserTable)->GetContentTable()->elementAt(nRow,0), Group, "TopN报告信息");  
	WSVFlexTable *pFlexTable = *pFlexTable_Add;

	if(pFlexTable->GetContentTable() != NULL)
	{
		pFlexTable->AppendRows("");

		m_pTitle = new WLineEdit("", pFlexTable->AppendRowsContent(0,m_formText.szReportTitle+"<span class =required>*</span>", m_formText.szReportTitleHelp, strErrorTitle));
		//m_pTitle = new WLineEdit("", pFlexTable->AppendRowsContent(0,m_formText.szReportTitle+"<span class =required>*</span>", m_formText.szReportTitleHelp, strInError));
		m_pTitle->resize(WLength(300, WLength::Pixel), WLength(0, WLength::Pixel));
		m_pTitle->setStyleClass("input_text");

		new WText("", pFlexTable->AppendRowsContent(0, "", "", strInError));
		new WText("", pFlexTable->AppendRowsContent(0, "", "", m_formText.szSameSection));

		m_pDescript = new WLineEdit("",pFlexTable->AppendRowsContent(0,m_formText.szReportDescript, m_formText.szReportDescriptHelp, ""));
		m_pDescript->resize(WLength(300, WLength::Pixel), WLength(0, WLength::Pixel));
		m_pDescript->setStyleClass("input_text");
		
		m_pSelType = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szTopnReportSelType, m_formText.szTopnReportSelTypeHelp, ""));
		WObject::connect(m_pSelType, SIGNAL(changed()), this, SLOT(SelActive(int)));
		
	    PAIRLIST retlist;
		PAIRLIST retlist1;
		std::list<struct sv_pair>::iterator svitem;
		std::list<struct sv_pair>::iterator svitem1;
		
		GetAllMonitorsInfo(retlist, "sv_monitortype");

		for(svitem = retlist.begin(); svitem != retlist.end(); svitem++)
		{
			sv_pair tp = * svitem;
			std::string value;
			
			bool bAdd = true;
			
			for(svitem1 = retlist1.begin(); svitem1 != retlist1.end(); svitem1++)
			{
				sv_pair tp1 = *svitem1;
				OBJECT hMonitor = GetMonitorTemplet(atoi(tp.value.c_str()));
				
				MAPNODE node = GetMTMainAttribNode(hMonitor);
				
				FindNodeValue(node, "sv_label", value);
				value=GetLabelResource(value);
		
				if(strcmp(tp1.value.c_str(),value.c_str()) == 0)
				{
					bAdd = false;
					break;
				}

				CloseMonitorTemplet(hMonitor);
			}
			if(bAdd)
			{
				OBJECT hMonitor = GetMonitorTemplet(atoi(tp.value.c_str()));				
				MAPNODE node = GetMTMainAttribNode(hMonitor);				
				
				FindNodeValue(node, "sv_label", value);
				value=GetLabelResource(value);

				if(strcmp(value.c_str(), "") !=0)
				{
					PrintDebugString("name:");
					PrintDebugString(tp.value.c_str());
					tp.name = tp.value;
					tp.value = value;
					
					retlist1.push_back(tp);
				}
				CloseMonitorTemplet(hMonitor);
			}
		}
		strRet = Sort(retlist1);
		std::list<sv_pair>::iterator sitem;
		for( sitem = strRet.begin(); sitem != strRet.end(); sitem++)
		{
			sv_pair tempstr = *sitem;
			m_pSelType ->addItem(tempstr.value);
		}

		m_pSelMark = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szTopnReportSelMark, m_formText.szTopnReportSelMarkHelp,""));
		m_pSelMark->addItem(m_formText.szMark1);

		WTable * SingleSel;
		SingleSel = new WTable(pFlexTable->AppendRowsContent(0, m_formText.szTopnReportSelSort, m_formText.szTopnReportSelSortHelp, ""));
		m_pSelSort1 = new WRadioButton(m_formText.szTopnReportSelSort1, (WContainerWidget*)SingleSel->elementAt(0, 0));
		m_pSelSort1 ->setChecked(true);
		WObject::connect(m_pSelSort1, SIGNAL(clicked()), this, SLOT(RadioSort1()));
		new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget*)SingleSel->elementAt(0, 0));
		m_pSelSort2 = new WRadioButton(m_formText.szTopnReportSelSort2, (WContainerWidget*)SingleSel->elementAt(0, 0));
		WObject::connect(m_pSelSort2, SIGNAL(clicked()), this, SLOT(RadioSort2()));

		m_pCount = new WLineEdit("10", pFlexTable->AppendRowsContent(0, m_formText.szTopnReportCount, m_formText.szTopnReportCountHelp, ""));
		//m_pCount->set
		m_pCount->resize(WLength(50, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pCount->setStyleClass("input_text");

		m_pPeriod = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szReportPeriod, m_formText.szReportPeriodHelp, ""));
		m_pPeriod ->addItem(m_formText.szDayReport);
		m_pPeriod ->addItem(m_formText.szWeekReport);
		m_pPeriod ->addItem(m_formText.szMonthReport);

		m_pGenerate = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szReportGenerateTime, m_formText.szReportGenerateTimeHelp, ""));
		for (int k=0; k<24; k++)
		{
			char buf[256];
			memset(buf, 0, 256);
			sprintf(buf, "%2d", k);
			m_pGenerate->addItem(buf);
		}

		m_pEmailSend = new WLineEdit("", pFlexTable->AppendRowsContent(0, m_formText.szReportEmailSend, m_formText.szReportEmailSendHelp, ""));
		m_pEmailSend->resize(WLength(300, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pEmailSend->setStyleClass("input_text");

		m_pDeny = new WCheckBox(m_formText.szReportDeny, pFlexTable->AppendRowsContent(0, m_formText.szReportDeny, m_formText.szReportDenyHelp, ""));

		m_pPlan = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szTaskDes1, m_formText.szHelpPlan, ""));
		std::list<string> tasknamelist;
		std::list<string>::iterator m_pItem;
		GetAllTaskName(tasknamelist);
		for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
		{
			std::string m_pNameStr = *m_pItem;
			
			OBJECT hTask = GetTask(m_pNameStr);
			std::string sValue = GetTaskValue("Type", hTask);
			
			if(strcmp(sValue.c_str(), m_formText.szPlanTypeRel.c_str()) == 0)
			{
				m_pPlan -> addItem(m_pNameStr);
			}
		}

		m_pValueCombo = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szGetValue, "", ""));
		m_pValueCombo->addItem(m_formText.szGetValuePer);
		m_pValueCombo->addItem(m_formText.szGetValueNew);

		m_pWeekEndBox = new WComboBox(pFlexTable->AppendRowsContent(0, m_formText.szWeekEndTime, m_formText.szHelpWeek, ""));
		m_pWeekEndBox->addItem(m_formText.szWeek1);
		m_pWeekEndBox ->addItem(m_formText.szWeek2);
		m_pWeekEndBox ->addItem(m_formText.szWeek3);
		m_pWeekEndBox ->addItem(m_formText.szWeek4);
		m_pWeekEndBox ->addItem(m_formText.szWeek5);
		m_pWeekEndBox ->addItem(m_formText.szWeek6);
		m_pWeekEndBox ->addItem(m_formText.szWeek7);


		pFlexTable->ShowOrHideHelp();
		pFlexTable->HideAllErrorMsg();
	}

	if(pFlexTable->GetActionTable()!=NULL)
	{
		WTable *pTbl;

		pTbl = new WTable(pFlexTable->GetActionTable()->elementAt(0, 1));

		m_pSave = new WSVButton(pTbl->elementAt(0,0), m_formText.szSave,  "button_bg_m_black.png", "", true);
		m_pCancel = new WSVButton(pTbl->elementAt(0, 1), m_formText.szBack, "button_bg_m.png", "", false);

		WObject::connect(m_pCancel, SIGNAL(clicked()), this, SLOT(Back()));
		WObject::connect(m_pSave, SIGNAL(clicked()), this, SLOT(Save()));
	}
}



void CSVAddTopnReport::ExChangeAdd()
{
	PrintDebugString("------ExChangeAddEvent------\n");
	emit ExChangeAddEvent();
}
void CSVAddTopnReport::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "topnreportsetRes";
	WebSession::js_af_up += "')";
}

void CSVAddTopnReport::loadString()
{
		//Resource
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
/*			//添加Resource
			bool bAdd = AddNodeAttrib(ResNode,"IDS_Invert_Task_Plan","相对任务计划");
			bAdd = AddNodeAttrib(ResNode,"IDS_Choose_Type","选择类型");
			bAdd = AddNodeAttrib(ResNode,"IDS_Choose_Type_Help","选择要统计的监测器类型");
			bAdd = AddNodeAttrib(ResNode,"IDS_Choose_Mark","选择指标");
			bAdd = AddNodeAttrib(ResNode,"IDS_Choose_Mark_Help","选择监测器指标类型");
			bAdd = AddNodeAttrib(ResNode,"IDS_Select_Sort","选择排序方式");
			bAdd = AddNodeAttrib(ResNode,"IDS_Select_Sort_Des","降序");
			bAdd = AddNodeAttrib(ResNode,"IDS_Select_Sort_Asc","升序");
			bAdd = AddNodeAttrib(ResNode,"IDS_Count","数量");
			bAdd = AddNodeAttrib(ResNode,"IDS_Count_Help","输入要统计的监测器数量");
			bAdd = AddNodeAttrib(ResNode,"IDS_Report_Title_Empty","报告标题不能为空！");
			bAdd = AddNodeAttrib(ResNode,"IDS_Help_Plan","只使用指定执行计划内采集的数据");
			bAdd = AddNodeAttrib(ResNode,"IDS_Get_Value_Method","取值方式");
			bAdd = AddNodeAttrib(ResNode,"IDS_Average","平均");
			bAdd = AddNodeAttrib(ResNode,"IDS_Later","最新");
*/
			FindNodeValue(ResNode,"IDS_Run_Plan_Delete",m_formText.szTaskDes1);
			FindNodeValue(ResNode,"IDS_AddMail_Schedule_Description",m_formText.szHelpTaskDes);
			//FindNodeValue(ResNode,"IDS_Invert_Task_Plan",m_formText.szPlanTypeRel);
			FindNodeValue(ResNode,"IDS_TopN_Report_Add",m_formText.szReportAddTitle);
			FindNodeValue(ResNode,"IDS_Report_Caption",m_formText.szReportTitle);
			FindNodeValue(ResNode,"IDS_Report_Caption_Help",m_formText.szReportTitleHelp);
			FindNodeValue(ResNode,"IDS_Report_Desc",m_formText.szReportDescript);
			FindNodeValue(ResNode,"IDS_Report_Note",m_formText.szReportDescriptHelp);
			FindNodeValue(ResNode,"IDS_Time_Period",m_formText.szReportPeriod);
			FindNodeValue(ResNode,"IDS_Time_Period_Description",m_formText.szReportPeriodHelp);
			FindNodeValue(ResNode,"IDS_Report_Option",m_formText.szReportOption);
			FindNodeValue(ResNode,"IDS_Report_Option_Help",m_formText.szReportOptionHelp);
			FindNodeValue(ResNode,"IDS_Send_Report_Email",m_formText.szReportEmailSend);
			FindNodeValue(ResNode,"IDS_Send_Report_Email_Help",m_formText.szReportEmailSendHelp);
			FindNodeValue(ResNode,"IDS_Show_Aler_Parameter",m_formText.szReportParameter);
			FindNodeValue(ResNode,"IDS_Show_Aler_Parameter_Help",m_formText.szReportParameterHelp);
			FindNodeValue(ResNode,"IDS_Show_Aler_Info",m_formText.szReportParameter1);
			FindNodeValue(ResNode,"IDS_Deny_Report",m_formText.szReportDeny);
			FindNodeValue(ResNode,"IDS_Deny_Report_Temp",m_formText.szReportDeny1);
			FindNodeValue(ResNode,"IDS_Deny_Report_Help",m_formText.szReportDenyHelp);
			FindNodeValue(ResNode,"IDS_Report_Create_Time",m_formText.szReportGenerateTime);
			FindNodeValue(ResNode,"IDS_Report_Create_Time_Help",m_formText.szReportGenerateTimeHelp);
			FindNodeValue(ResNode,"IDS_Week_Report_Config",m_formText.szReportWeek);
			FindNodeValue(ResNode,"IDS_Week_Report_Config_Help",m_formText.szReportWeekHelp);
			FindNodeValue(ResNode,"IDS_Save",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_Cancel",m_formText.szBack);
			FindNodeValue(ResNode,"IDS_Connect_SVDB_Fail",m_formText.szConnErr);
			FindNodeValue(ResNode,"IDS_TopN_Report_Same",m_formText.szSameSection);
			FindNodeValue(ResNode,"IDS_Choose_Type",m_formText.szTopnReportSelType);
			FindNodeValue(ResNode,"IDS_Choose_Type_Help",m_formText.szTopnReportSelTypeHelp);
			FindNodeValue(ResNode,"IDS_Choose_Mark",m_formText.szTopnReportSelMark);
			FindNodeValue(ResNode,"IDS_Choose_Mark_Help",m_formText.szTopnReportSelMarkHelp);
			FindNodeValue(ResNode,"IDS_Select_Sort",m_formText.szTopnReportSelSort);
			FindNodeValue(ResNode,"IDS_Select_Sort_Des",m_formText.szTopnReportSelSort1);
			FindNodeValue(ResNode,"IDS_Select_Sort_Asc",m_formText.szTopnReportSelSort2);
			FindNodeValue(ResNode,"IDS_Select_Sort",m_formText.szTopnReportSelSortHelp);
			FindNodeValue(ResNode,"IDS_Count",m_formText.szTopnReportCount);
			FindNodeValue(ResNode,"IDS_Count_Help",m_formText.szTopnReportCountHelp);
			FindNodeValue(ResNode,"IDS_Select_Sort_Des",m_formText.szSortDes);
			FindNodeValue(ResNode,"IDS_Select_Sort_Asc",m_formText.szSortAsc);
			FindNodeValue(ResNode,"IDS_Report_Day",m_formText.szDayReport);
			FindNodeValue(ResNode,"IDS_Report_Week",m_formText.szWeekReport);
			FindNodeValue(ResNode,"IDS_Report_Month",m_formText.szMonthReport);
			FindNodeValue(ResNode,"IDS_Report_Title_Empty",strErrorTitle);
			FindNodeValue(ResNode,"IDS_Week_Report_Date_Help",m_formText.szHelpPlan);
			FindNodeValue(ResNode,"IDS_Get_Value_Method",m_formText.szGetValue);
			FindNodeValue(ResNode,"IDS_Average",m_formText.szGetValuePer);
			FindNodeValue(ResNode,"IDS_Later",m_formText.szGetValueNew);
			FindNodeValue(ResNode,"IDS_Monday",m_formText.szWeek2);
			FindNodeValue(ResNode,"IDS_Tuesday",m_formText.szWeek3);
			FindNodeValue(ResNode,"IDS_Wednesday",m_formText.szWeek4);
			FindNodeValue(ResNode,"IDS_Thursday",m_formText.szWeek5);
			FindNodeValue(ResNode,"IDS_Friday",m_formText.szWeek6);
			FindNodeValue(ResNode,"IDS_Saturday",m_formText.szWeek7);
			FindNodeValue(ResNode,"IDS_Sunday",m_formText.szWeek1);
			FindNodeValue(ResNode,"IDS_Week_Report_Help",m_formText.szHelpWeek);
			FindNodeValue(ResNode,"IDS_Report_Range_Not_Empty",m_formText.szScopeError);
			FindNodeValue(ResNode,"IDS_TopN_Report",strTopNReport);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_Alert_Area",strAlertArea);
			FindNodeValue(ResNode,"IDS_Week_Report_End_Time",m_formText.szWeekEndTime);


			
			//FindNodeValue(ResNode,"IDS_Total_Report",strTotalReport);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);

			FindNodeValue(ResNode,"IDS_TopN_Report",szTopTitle);
			FindNodeValue(ResNode,"IDS_Report_Edit",strEditReport);
			FindNodeValue(ResNode,"IDS_Report_Add",strAddReport);
		}

		//CloseResource(objRes);
	}
	/*
	m_formText.szTaskDes1 = "执行计划过滤";
	m_formText.szHelpTaskDes = "设定执行计划允许的时间，如：允许星期一，从10:00到22:00";
	m_formText.szPlanTypeRel = "2";//相对任务计划
	m_formText.szReportAddTitle = "添加TopN报告";
	m_formText.szReportTitle = "报告标题";
	m_formText.szReportTitleHelp = "显示在报告的上方或报告列表中";
	m_formText.szReportDescript = "报告描述";
	m_formText.szReportDescriptHelp = "对报告的备注（可选）";
	
	m_formText.szReportPeriod = "时间周期";
	m_formText.szReportPeriodHelp = "请指定生成报告的时间周期";
	m_formText.szReportOption = "报告选项";
	m_formText.szReportOptionHelp = "请指定生成报告要显示的项目";

	m_formText.szReportEmailSend = "以E-mail方式发送报告";
	m_formText.szReportEmailSendHelp = "在下面框中添入收件邮箱的地址,多个邮件地址以逗号分隔.报告将以设置好的时间间隔"\
		"自动生成并发送到下框所添地址中";
	m_formText.szReportParameter = "显示监测的详细参数";
	m_formText.szReportParameterHelp = "选择此项后, 监测器所有返回值的监测情况都会显示在报告里, 否则只会显示每个监测的主要参数";
	m_formText.szReportParameter1 = "显示监测的详细信息";
	m_formText.szReportDeny = "禁止报告";
	m_formText.szReportDeny1 = "临时禁止报告";
	m_formText.szReportDenyHelp = "当选择此项后,报告将停止自动生成";
	m_formText.szReportGenerateTime = "报告生成时间";
	m_formText.szReportGenerateTimeHelp = "当选择此项后, 报告在指定时间生成,单位：时";
	m_formText.szReportWeek = "周报设置";
	m_formText.szReportWeekHelp = "当选择此项后, 报告将在指定的星期生成报告,单位：周";

	m_formText.szSave = "保存";
	m_formText.szBack = "取消";
	m_formText.szConnErr = "连接SVDB失败";
	m_formText.szSameSection = "已存在相同的TopN报告";

	m_formText.szTopnReportSelType = "选择类型";
	m_formText.szTopnReportSelTypeHelp = "选择要统计的监测器类型";
	m_formText.szTopnReportSelMark = "选择指标";
	m_formText.szTopnReportSelMarkHelp = "选择监测器指标类型";			
	m_formText.szTopnReportSelSort = "选择排序方式";
	m_formText.szTopnReportSelSort1 = "降序";
	m_formText.szTopnReportSelSort2 = "升序";
	m_formText.szTopnReportSelSortHelp = "选择排序方式";
	m_formText.szTopnReportCount = "数量";
	m_formText.szTopnReportCountHelp = "输入要统计的监测器数量";
	m_formText.szSortDes = "降序";
	m_formText.szSortAsc = "升序";
	m_formText.szDayReport = "日报";
	m_formText.szWeekReport = "周报";
	m_formText.szMonthReport = "月报";
	m_formText.szMark1 = "";

	strErrorTitle = "报告标题不能为空！";
	*/
	m_formText.szPlanTypeRel = "2";//相对任务计划
	m_formText.szMark1 = "";
/*
	m_formText.szWeek1 ="星期日";
	m_formText.szWeek2 ="星期一";
	m_formText.szWeek3 ="星期二";
	m_formText.szWeek4 ="星期三";
	m_formText.szWeek5 ="星期四";
	m_formText.szWeek6 ="星期五";
	m_formText.szWeek7 ="星期六";
	m_formText.szHelpWeek ="设置周报生成时间,如 设置周一，周报生成范围为 本周日0点到上周日0点";
	m_formText.szScopeError = "报告范围不能为空";*/

	strInError = "输入错误，标题包含非法字符！";
}

void CSVAddTopnReport::Save()
{
	OutputDebugString("----------------00----------------\n");
	//验证报告标题是否为空
	std::list<string> errorMsgList;
	bool bShowErr=false;
	//m_pReportTable->HideAllErrorMsg();
	if(m_pTitle->text().empty())
	{
		errorMsgList.push_back(strErrorTitle);
		//strInError = strErrorTitle;
		//errorMsgList.push_back(strInError);

		bShowErr=true;
	}
	//Jansion.zhou 2006-12-30 
	else
	{
		std::string strRname, Contrast;
		Contrast = "~!@#$%^&*()_+=-`[]}{;':.,<>\"\\|?";
		strRname = m_pTitle->text();
		int NameNum;
		NameNum = strRname.find_first_of(Contrast);
		if ( NameNum != string::npos )
		{
			//OutputDebugString("00000000000000000000000000000000000000000000000\n");
			//strInError = "输入错误，标题包含非法字符！";
			errorMsgList.push_back(strInError);
			bShowErr = true;
		}
	}


	//AnswerTable->ShowErrorMsg(errorMsgList);
	//if(bShowErr==true)
	//	return;
	//m_pReportTable->ShowErrorMsg(errorMsgList);

	if (bShowErr)
	{
		//OutputDebugString("----------------00---------11-------\n");
		m_pReportTable->ShowErrorMsg(errorMsgList);
		return;
	}


	chg = "";

	//Jansion.zhou 2006-12-26
	//m_pConnErr->setText("");
	//m_pConnErr->hide();

	std::list<string> sectionlist;
	bool IsSave = GetIniFileSections(sectionlist, "topnreportset.ini");

	if(IsSave)
	{
		std::list<string> sectionlist;
		std::list<string>::iterator Item;
		GetIniFileSections(sectionlist, "topnreportset.ini");
		bool bRe = false;
		//OutputDebugString("----------------00--------22--------\n");
		for(Item = sectionlist.begin(); Item != sectionlist.end(); Item++)
		{
			std::string str = *Item;
			if(strcmp(str.c_str(), m_pTitle->text().c_str()) == 0)
			{
				bRe = true;
				break;
			}
		}
	
		for(Item = sectionlist.begin(); Item != sectionlist.end(); Item++)
		{
			std::string str = *Item;
			if(strcmp(str.c_str(), m_pTitle->text().c_str()) == 0)
			{
				if(strcmp(str.c_str(), chgstr.c_str()) != 0)
				{
					bRe = true;
					break;
				}
				else
				{
					bRe = false;
					break;
				}
			}
		}

		if(bRe)
		{
			//Jansion.zhou 2006-12-26
			//m_pConnErr ->setText(m_formText.szSameSection);
			//m_pConnErr ->show();
			//OutputDebugString("----------------00-----wrong-----------\n");
			errorMsgList.push_back(m_formText.szSameSection);
			m_pReportTable->ShowErrorMsg(errorMsgList);
			return;

		}
		else
		{
			m_report.szTitle = m_pTitle->text();
			m_report.szDescript = m_pDescript->text();
			m_report.szPeriod = m_pPeriod->currentText();
			
			if(m_pDeny ->isChecked())
			{
				m_report.szDeny = "Yes";
			}
			else
			{
				m_report.szDeny = "No";
			}
			
			m_report.szEmailSend = m_pEmailSend->text();

			m_report.szGenerate = m_pGenerate->currentText();

			m_report.szSelType = m_pSelType ->currentText();

			m_report.szSelMark = m_pSelMark ->currentText();

			if(m_pSelSort1->isChecked())
			{
				m_report.szSelSort = m_formText.szSortDes;
			}
			else
			{
				m_report.szSelSort = m_formText.szSortAsc;
			}

			m_report.szCount = m_pCount ->text();
			
			GetGroupRightList();
			
			std::string strUnGroupRight;
			strUnGroupRight=",";
			for( list<std::string >::iterator _listitem = pUnGroupRightList.begin(); _listitem != pUnGroupRightList.end(); _listitem ++)
			{
				strUnGroupRight+=_listitem->c_str();
				strUnGroupRight+=",";
			}
			m_report.szGroupRight=",";
			for( list<std::string >::iterator _listitem = pGroupRightList.begin(); _listitem != pGroupRightList.end(); _listitem ++)
			{
				std::string strTmp;
				strTmp=",";
				strTmp+=_listitem->c_str();
				strTmp+=".";

				int nIndex;
				nIndex=strUnGroupRight.find(strTmp,0);
				if(nIndex <0)
				{
						m_report.szGroupRight +=_listitem->c_str();
						m_report.szGroupRight +=",";
				}
			}

			if(m_report.szGroupRight.size() <= 1)
			{
				WebSession::js_af_up="alert(\"" + m_formText.szScopeError +"\");";
				return;
			}
			m_report.szPlan = m_pPlan->currentText();

			m_report.szGetValue = m_pValueCombo->currentText();

			char wbuf[256];

			itoa(m_pWeekEndBox->currentIndex(),wbuf, 10);

			m_report.szWeekEnd = wbuf;
 
			//插记录到UserOperateLog表
			string strUserID = GetWebUserID();
			TTime mNowTime = TTime::GetCurrentTimeEx();
			OperateLog m_pOperateLog;
			string strOType;
			if(chgstr == "")
			{
				strOType = strTypeAdd;
			}
			else
			{
				strOType = strTypeEdit;
			}
			m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strTopNReport,m_pTitle->text());

			emit SaveTopnReport(m_report);
			chgstr = "";
		}
	}
	else
	{
		//Jansion.zhou 2006-12-26 数据库连接错误
		//m_pConnErr->setText(m_formText.szConnErr);
		//m_pConnErr->show();

	}
OutputDebugString("----------------00---------333-------\n");
	//AnswerTable->HideAllErrorMsg();
	m_pReportTable->HideAllErrorMsg();
}


void CSVAddTopnReport::Back()
{
	chg = "cancel";
    emit BackTo(chg);
}

void CSVAddTopnReport::setProperty(SAVE_REPORT_LIST * report)
{
	m_pTitle ->setText(report->szTitle);
	m_pDescript ->setText(report->szDescript);
	m_pPeriod ->setCurrentIndexByStr(report->szPeriod);

	m_pEmailSend->setText(report->szEmailSend);
		
	if(strcmp(report->szDeny.c_str(), "Yes") == 0)
	{
		m_pDeny ->setChecked(true);
	}
	else
	{
		m_pDeny ->setChecked(false);
	}
		
	m_pGenerate ->setCurrentIndexByStr(report->szGenerate);

	m_pSelType ->setCurrentIndexByStr(report->szSelType);

	std::string str = report->szSelType;
	std::list<struct sv_pair>::iterator svitem ;

	for(svitem = strRet.begin(); svitem != strRet.end(); svitem++)
	{
		sv_pair temp = *svitem;
		if(strcmp(temp.value.c_str(), str.c_str()) == 0)
		{
			m_pSelMark->clear();
		
			LISTITEM item;
			MAPNODE objNode;
			string value;
			OBJECT hTemplet = GetMonitorTemplet(atoi(temp.name.c_str()));
			
			bool bRet = FindMTReturnFirst(hTemplet, item);
			if(bRet)
			{
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					value = "";
					FindNodeValue(objNode, "sv_label", value);
					value=GetLabelResource(value);
				
					if(strcmp(value.c_str(), "") != 0)
					{
						m_pSelMark->addItem(value);
					}
				}
			}
			CloseMonitorTemplet(hTemplet);
			break;
		}
	}

	m_pSelMark ->setCurrentIndexByStr(report->szSelMark);

	m_pPlan->setCurrentIndexByStr(report->szPlan);

	m_pValueCombo->setCurrentIndexByStr(report->szGetValue);

	m_pWeekEndBox->setCurrentIndex(atoi(report->szWeekEnd.c_str()));

	if(strcmp(report->szSelSort.c_str(), m_formText.szSortDes.c_str()) == 0)
	{
		m_pSelSort1 ->setChecked(true);
		m_pSelSort2 ->setChecked(false);
	}
	else
	{
		m_pSelSort1 ->setChecked(false);
		m_pSelSort2 ->setChecked(true);
	}

	m_pCount ->setText(report->szCount);

	//Jansion.zhou 2006-12-26
	//m_pConnErr ->setText("");
}

void CSVAddTopnReport::upData()
{
	m_pMainTable->pTitleTxt->setText("编辑报告");
}
void CSVAddTopnReport::clearData()
{
	m_pPlan ->clear();
	m_pMainTable->pTitleTxt->setText("添加报告");
	std::list<string> tasknamelist;
	std::list<string>::iterator m_pItem;
	GetAllTaskName(tasknamelist);

	for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
	{
		std::string m_pNameStr = *m_pItem;
		
		OBJECT hTask = GetTask(m_pNameStr);
		std::string sValue = GetTaskValue("Type", hTask);
		
		//if(strcmp(sValue.c_str(), m_formText.szPlanTypeRel.c_str()) == 0)
		if(strcmp(sValue.c_str(), "2") == 0)
		{
			m_pPlan -> addItem(m_pNameStr);
		}
	}



	//m_pHelpTitle ->hide();
	//m_pHelpDescript ->hide();

	m_pTitle ->setText("");
	m_pDescript ->setText("");
	
	//m_pHelpEmailSend ->hide();
	m_pEmailSend ->setText("");

	//m_pHelpDeny ->hide();
    m_pDeny ->setChecked(false);
	//m_pHelpGenerate ->hide();

	//m_pHelpPlan ->hide();

	m_pPeriod ->setCurrentIndex(0);
	m_pGenerate ->setCurrentIndex(0);
	m_pSelType ->setCurrentIndex(0);
	m_pPlan ->setCurrentIndex(0);
	m_pValueCombo->setCurrentIndex(0);
	m_pWeekEndBox->setCurrentIndex(0);

	std::string str = m_pSelType->currentText();
	std::list<struct sv_pair>::iterator svitem ;

	for(svitem = strRet.begin(); svitem != strRet.end(); svitem++)
	{
		sv_pair temp = *svitem;
		if(strcmp(temp.value.c_str(), str.c_str()) == 0)
		{
			m_pSelMark->clear();
			
			LISTITEM item;
			MAPNODE objNode;
			string value;
			OBJECT hTemplet = GetMonitorTemplet(atoi(temp.name.c_str()));
			
			bool bRet = FindMTReturnFirst(hTemplet, item);
			if(bRet)
			{
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					FindNodeValue(objNode, "sv_label", value);
					value=GetLabelResource(value);
					m_pSelMark->addItem(value);
				}
			}
			CloseMonitorTemplet(hTemplet);
			break;
		}
	}

	m_pCount ->setText("10");

	//Jansion.zhou 2006-12-26
	//m_pConnErr ->setText("");
	m_pReportTable->HideAllErrorMsg();
}

void CSVAddTopnReport::showAddPhoneList()
{

}

void CSVAddTopnReport::hideAddPhoneList()
{
	
}

void CSVAddTopnReport::showAddReport()
{
	//pShow1 -> show();
	//pHide1 -> hide();
	//pTable1 -> show();
}

void CSVAddTopnReport::hideAddReport()
{
	//pShow1 -> hide();
	//pHide1 -> show();
	//pTable1 -> hide();
}


void CSVAddTopnReport::AddPhoneHelp()
{
	m_pReportTable->ShowOrHideHelp();
/*
	if(IsHelp)
	{
		m_pHelpTitle ->show();
		m_pHelpDescript ->show();
		m_pHelpPeriod ->show();
		m_pHelpEmailSend ->show();
		m_pHelpDeny ->show();
		m_pHelpGenerate ->show();

		m_pHelpSelType ->show();
		m_pHelpSelMark ->show();
		m_pHelpSelSort ->show();
		m_pHelpCount ->show();
		m_pHelpPlan ->show();
		IsHelp = false;
	}
	else
	{
		m_pHelpTitle ->hide();
		m_pHelpDescript ->hide();
		m_pHelpPeriod ->hide();
		m_pHelpEmailSend ->hide();
		m_pHelpDeny ->hide();
		m_pHelpGenerate ->hide();

		m_pHelpSelType ->hide();
		m_pHelpSelMark ->hide();
		m_pHelpSelSort ->hide();
		m_pHelpCount ->hide();
		m_pHelpPlan ->hide();
		IsHelp = true;
	}
*/
}

void CSVAddTopnReport::TestSMS()
{
}

void CSVAddTopnReport::TestSMSing()
{

}

void CSVAddTopnReport::RadioSort1()
{
	m_pSelSort1 ->setChecked(true);
	m_pSelSort2 ->setChecked(false);
}

void CSVAddTopnReport::RadioSort2()
{
	m_pSelSort1 ->setChecked(false);
	m_pSelSort2 ->setChecked(true);
}

void CSVAddTopnReport::SelActive(int val)
{
	std::string str = m_pSelType->currentText();
	std::list<struct sv_pair>::iterator svitem ;

	for(svitem = strRet.begin(); svitem != strRet.end(); svitem++)
	{
		
		sv_pair temp = *svitem;

		if(strcmp(temp.value.c_str(), str.c_str()) == 0)
		{
			m_pSelMark->clear();
			
			LISTITEM item;
			MAPNODE objNode;
			string value;
			OBJECT hTemplet = GetMonitorTemplet(atoi(temp.name.c_str()));
			
			bool bRet = FindMTReturnFirst(hTemplet, item);
			if(bRet)
			{
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					FindNodeValue(objNode, "sv_label", value);
					value=GetLabelResource(value);
					m_pSelMark->addItem(value);
				}
			}
			CloseMonitorTemplet(hTemplet);
			break;
		}
	}
}

std::list<sv_pair> CSVAddTopnReport::Sort(PAIRLIST retlist)
{
	std::list<sv_pair> retstr;
	std::list<struct sv_pair>::iterator svitem ;
	std::list<struct sv_pair>::iterator svitem1;
	sv_pair sv_item;
	sv_pair sv_item1;

	sv_pair str;
	sv_pair temp;
	sv_pair signstr;

	for(svitem = retlist.begin(); svitem != retlist.end(); svitem++)
	{
		sv_item = *svitem;

		signstr = sv_item;
		for(svitem1 = svitem; svitem1 != retlist.end(); svitem1++)
		{
			sv_item1 = *svitem1;

			str = sv_item1;
			if( strcmp(str.value.c_str(), signstr.value.c_str()) < 0)
			{
				temp = str;
				str = signstr;
				signstr = temp;

				svitem1->value = str.value;
				svitem1->name = str.name;
			}
		}
		retstr.push_back(signstr);		
	}
	return retstr;
}

void CSVAddTopnReport::GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_,std::list<string > &pUnGroupRightList_)
{
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			if(pNode->treeCheckBox_->isChecked())
			{
				pGroupRightList_.push_back(pNode->strId);
				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_);

			}else{
				pUnGroupRightList_.push_back(pNode->strId);
				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_);
			}
		}else{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_);
		}
	}
	return;

}
void CSVAddTopnReport::GetGroupRightList()
{
	pUnGroupRightList.clear();
	pGroupRightList.clear();
	if(pGroupTree->treeroot!=NULL)
	{
		GetGroupChecked(pGroupTree->treeroot,pGroupRightList,pUnGroupRightList);

	}

}

void CSVAddTopnReport::SetGroupChecked(WTreeNode*pNode,  std::string  pGroupRightList_ ,bool bPCheck)
{
	std::string  strSelId;
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			strSelId=","+ pNode->strId+",";

			int iPos=pGroupRightList_.find(strSelId);
			
			if(iPos>=0||bPCheck)
			{
				pNode->treeCheckBox_->setChecked();
			}
			else {

				if(pNode->nTreeType==Tree_DEVICE)
				{
					strSelId=","+ pNode->strId;
					iPos =pGroupRightList_.find(strSelId);
					if(iPos>=0)
						pGroupTree->AddMontiorInDevice(pNode);

				}
				
				
			}
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
				SetGroupChecked(pNode->childNodes()[i],pGroupRightList_, pNode->treeCheckBox_->isChecked());
			
		}else{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					SetGroupChecked(pNode->childNodes()[i],pGroupRightList_, pNode->treeCheckBox_->isChecked());
		}
	}
	return;

}


void CSVAddTopnReport::setGroupRightCheck(std::string groupright)
{
	if(pGroupTree->treeroot!=NULL)
        	SetGroupChecked(pGroupTree->treeroot,groupright,false);
}
