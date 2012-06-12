
#include "Addreport.h"

///////////////////////////////////////////////////////////////////szReportOptNormal = "列出正常";szReportOptError1 = "列出错误";
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
#include "..\svtable\AnswerTable.h"
#include "../../opens/libwt/WebSession.h"

#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"
#include "..\svtable\FlexTable.h"
#include "../base/basetype.h"
#include "svapi.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

#include <windows.h>
//#include <atltime.h>
#include "../../kennel/svdb/libutil/Time.h"

#include "../svtable/WSVButton.h"
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSTreeAndPanTable.h"

extern void PrintDebugString(const char*);

string TrimStdString(string strIn)
{	
	if(!strIn.empty())
	{
		//会不会出错?
		strIn.erase(strIn.begin(),strIn.begin() + strIn.find_first_not_of(' '));
		strIn.erase(strIn.begin() + strIn.find_last_not_of(' ') + 1,strIn.end());
		return strIn;
	}
	else
		return "";
}

CSVAddReport::CSVAddReport(WContainerWidget * parent /* = 0 */):
WContainerWidget(parent)
{
	//new WText("<SCRIPT language='JavaScript' >_OnLoad();</script>",this);
	IsHelp = true;
    loadString();
    initForm();
}

void CSVAddReport::initTree(std::string strUser)
{
	OutputDebugString("----------------strUser----------------\n");
	OutputDebugString((strUser+"\n").c_str());
	pGroupTree->InitTree("",false,true,false,strUser);
}

//添加客户端脚本变量
void CSVAddReport::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CSVAddReport::InitReportTable(WSVFlexTable **pFlexTable_Add ,int nRow,std::string strTitle, WSVMainTable ** pUserTable)
{
	//*pFlexTable_Add = new WSVFlexTable((WContainerWidget *)(*pUserTable)->GetContentTable()->elementAt(nRow,0), Group, strTitle);  
	*pFlexTable_Add = new WSVFlexTable((WContainerWidget *)(*pUserTable)->GetContentTable()->elementAt(nRow,0), Group, "统计报告信息");  
	WSVFlexTable *pFlexTable = *pFlexTable_Add;

	if(pFlexTable->GetContentTable() != NULL)
	{
		pFlexTable->AppendRows("");

		m_pTitle = new WLineEdit("", pFlexTable->AppendRowsContent(0,m_formText.szReportTitle+"<span class =required>*</span>", m_formText.szReportTitleHelp, strErrorTitle));
		m_pTitle->resize(WLength(300, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pTitle->setStyleClass("input_text");

		new WText("", pFlexTable->AppendRowsContent(0, "", "", strInError));
		new WText("", pFlexTable->AppendRowsContent(0, "","",m_formText.szSameSection));

		m_pDescript = new WLineEdit("",pFlexTable->AppendRowsContent(0,m_formText.szReportDescript, m_formText.szReportDescriptHelp, ""));
		m_pDescript->resize(WLength(300, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pDescript->setStyleClass("input_text");

		m_pPeriod = new WComboBox(pFlexTable->AppendRowsContent(0,m_formText.szReportDescript, m_formText.szReportPeriodHelp, ""));
		m_pPeriod ->addItem(m_formText.szDayPeriod);
		m_pPeriod ->addItem(m_formText.szWeekPeriod);
		m_pPeriod ->addItem(m_formText.szMonthPeriod);

		WTable *optTable = new WTable(pFlexTable->AppendRowsContent(0,m_formText.szReportOption, m_formText.szReportOptionHelp, ""));

		m_pStatusResult = new WCheckBox(m_formText.szReportOptStatus, (WContainerWidget*)optTable->elementAt(0,0));
		m_pStatusResult->setChecked(true);
		m_pListClicket = new WCheckBox(m_formText.szListClicket, (WContainerWidget*)optTable->elementAt(1,0));
		m_pListClicket ->setChecked(true);

		m_pErrorResult = new WCheckBox(m_formText.szReportOptError1, (WContainerWidget*)optTable->elementAt(2,0));
		m_pErrorResult ->setChecked(true);
		m_pErrorResult -> hide();

		m_pGraphic = new WCheckBox("", (WContainerWidget*)optTable->elementAt(3,0));
		m_pGraphic ->setChecked(true);		
		m_pComboGraphic = new WComboBox((WContainerWidget*)optTable->elementAt(3,0));
		m_pComboGraphic ->addItem(m_formText.szReportOptGraphic1);
		m_pComboGraphic ->addItem(m_formText.szReportOptGraphic2);
		m_pComboGraphic ->addItem(m_formText.szAreaMap);

		m_pListData = new WCheckBox(m_formText.szReportOptData, (WContainerWidget*)optTable->elementAt(4,0));
		m_pListData->hide();		
		m_pListNormal = new WCheckBox(m_formText.szReportOptNormal , (WContainerWidget*)optTable->elementAt(5,0));
		m_pListNormal->hide();

		m_pListError = new WCheckBox(m_formText.szReportOptError, (WContainerWidget*)optTable->elementAt(6,0));
		m_pListError -> setChecked(true);

		m_pListDanger = new WCheckBox(m_formText.szReportOptDanger, (WContainerWidget*)optTable->elementAt(7,0));
		m_pListDanger ->setChecked(true);
		m_pListAlert = new WCheckBox(m_formText.szReportOptAlert, (WContainerWidget*)optTable->elementAt(8,0));

		//Ticket #123     -------苏合
		m_pGenExcel = new WCheckBox("生成Excel报告", (WContainerWidget*)optTable->elementAt(9,0));
		//Ticket #123     -------苏合

		m_pEmailSend = new WLineEdit("",pFlexTable->AppendRowsContent(0,m_formText.szReportEmailSend,m_formText.szReportEmailSendHelp, ""));
		m_pEmailSend->resize(WLength(300, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pEmailSend->setStyleClass("input_text");

		WTable *parameterTable = new WTable(pFlexTable->AppendRowsContent(0,m_formText.szReportParameter,m_formText.szReportParameterHelp, ""));

		m_pParameter = new WCheckBox(m_formText.szReportParameter1, parameterTable->elementAt(0,0));
		m_pDeny = new WCheckBox(m_formText.szReportDeny, parameterTable->elementAt(1, 0));

		WTable *generateTable = new WTable(pFlexTable->AppendRowsContent(0,m_formText.szReportGenerateTime,m_formText.szReportGenerateTimeHelp, ""));
		m_pGenerate = new WComboBox(generateTable->elementAt(0,0));
		new WText(m_formText.szTimeUnit, (WContainerWidget*)generateTable->elementAt(0,0));
		for(int k = 0; k < 24; k++)
		{
			char buf[256];
			memset(buf, 0, 256);
			sprintf(buf, "%2d",k);
			m_pGenerate ->addItem(buf);
		}

		m_pClicket = new WLineEdit("",pFlexTable->AppendRowsContent(0, "", "", ""));
		m_pClicket->setStyleClass("input_text");
		m_pClicket->hide();
		
		m_pPlan = new WComboBox(pFlexTable->AppendRowsContent(0,m_formText.szTaskDes1,m_formText.szHelpPlan, ""));

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

		m_pStartTime = new WLineEdit("",pFlexTable->AppendRowsContent(0, "", "", ""));
		m_pStartTime->setStyleClass("input_text");
		m_pStartTime->hide();

		WTable *endTimeTable = new WTable(pFlexTable->AppendRowsContent(0,m_formText.szEndTime,m_formText.szHelpEndTime, ""));
		m_pEndTime = new WComboBox((WContainerWidget*)endTimeTable->elementAt(0, 0));
		for(int nEndTime = 0; nEndTime < 24; nEndTime++)
		{
			char sEndTime[256];
			sprintf(sEndTime, "%d", nEndTime);
			m_pEndTime ->addItem(sEndTime);
		}
		new WText(":", (WContainerWidget*)endTimeTable->elementAt(0, 0));
		m_pEndMinute = new WComboBox((WContainerWidget*)endTimeTable->elementAt(0, 0));
		m_pEndMinute->addItem("00");
		m_pEndMinute->addItem("30");

		m_pWeekEndBox = new WComboBox(pFlexTable->AppendRowsContent(0,m_formText.szWeekEndTime,m_formText.szHelpWeek, ""));
		m_pWeekEndBox ->addItem(m_formText.szWeek1);
		m_pWeekEndBox ->addItem(m_formText.szWeek7);
		m_pWeekEndBox ->addItem(m_formText.szWeek6);
		m_pWeekEndBox ->addItem(m_formText.szWeek5);
		m_pWeekEndBox ->addItem(m_formText.szWeek4);
		m_pWeekEndBox ->addItem(m_formText.szWeek3);
		m_pWeekEndBox ->addItem(m_formText.szWeek2);

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

void CSVAddReport::ShowHelp()
{
	m_pReportTable->ShowOrHideHelp();
}

void CSVAddReport::InitTreeTable()
{
	m_pTreePanTabel = new WSTreeAndPanTable(this);
	AddJsParam("treeviewPanel", m_pTreePanTabel->formName());



	m_pTreePanTabel->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	m_pTreePanTabel->elementAt(0, 0)->resize(WLength(200, WLength::Pixel), WLength(100, WLength::Percentage));
	m_pTreePanTabel->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);
	m_pTreePanTabel->elementAt(0, 1)->resize(WLength(4,WLength::Pixel),WLength(100,WLength::Percentage));



	//TreeTable
	new WText("<div id='tree_panel' name='tree_panel' class='panel_tree'>", m_pTreePanTabel->elementAt(0, 0));

	WTable * pTreeTable = new WTable(m_pTreePanTabel->elementAt(0, 0));
	pTreeTable ->setStyleClass("t62");

	WTable * pUpTable = new WTable((WContainerWidget *)pTreeTable->elementAt(0,0));
	pUpTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	pUpTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	//new WText(m_formText.szAlertArea, (WContainerWidget *)pUpTable->elementAt(0,0));
	new WText("&nbsp;", (WContainerWidget *)pUpTable->elementAt(0,0));

	pGroupTree =new CCheckBoxTreeView((WContainerWidget *)pTreeTable->elementAt(1,0));
	pTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);

PrintDebugString("*****************11111111111************************************");



	//WTable * pTreeTable = new WTable(m_pTreePanTabel->elementAt(0, 0));
	//new WImage("/Images/tree_data.png", pTreeTable->elementAt(0, 0));
	new WText("</div>", m_pTreePanTabel->elementAt(0, 0));



	//DragTable
	AddJsParam("drag_tree", m_pTreePanTabel->elementAt(0, 1)->formName());


	//PanTable
	new WText("<div id='view_panel' class='panel_view'>", m_pTreePanTabel->elementAt(0, 2));

	m_pMainTable = new WSVMainTable(m_pTreePanTabel->elementAt(0, 2), m_formText.szReportAddTitle, true);

	if(m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}	



	InitReportTable(&m_pReportTable,1, strAddReport,&m_pMainTable);


	new WText("</div>", m_pTreePanTabel->elementAt(0, 2));


	AddJsParam("uistyle", "treepan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	//new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>",this);
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>",this);
	//new WText("<SCRIPT language='JavaScript'>SetTreeViewPanel()</script>",this);
	new WText("<SCRIPT language='JavaScript'>addLoadEvent(_OnLoad)</SCRIPT>", this); 
}

void CSVAddReport::setTitle(string title)
{
	if(m_pMainTable != NULL)
		m_pMainTable->pTitleTxt->setText(title);
}

void CSVAddReport::initForm()
{	 

	InitTreeTable();
/*

	string ret;

	chg = "";
	AnswerTable = new CAnswerTable(this, "");	
	//AnswerTable->setStyleClass("t6");
	
	m_pAnswerTitle = new WText("",AnswerTable->elementAt(0,0));
*/
	pTranslateBtn = new WPushButton(strTranslate,this);
	pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	pExChangeBtn = new WPushButton(strRefresh, this);
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChangeAdd()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}

/*
	WTable * TitleTable = new WTable(AnswerTable->GetContentTable()->elementAt(1,0));	
*/
	//connect svdb failure WText

	//jansion.zhou 2006-12-25
	//m_pConnErr = new WText("", this);
	//m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	//m_pConnErr ->hide();

	
//	WObject::connect(AnswerTable->m_pHelpimg, SIGNAL(clicked()), this, SLOT(AddPhoneHelp()));
//	
//	pFrameTable = new WTable(AnswerTable->GetContentTable() ->elementAt(2,0));
//	pFrameTable ->setStyleClass("t6");
//	pFrameTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
//
//	pFrameTable->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);
//	pFrameTable->elementAt(0, 0)->resize(WLength(26,WLength::Percentage),WLength(100,WLength::Percentage));
//	pFrameTable->elementAt(0, 1)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
//	//add report page
//	WTable * pSubTreeTable = new WTable((WContainerWidget *)pFrameTable->elementAt(0,0));
//	pSubTreeTable ->setStyleClass("t62");
//	pFrameTable->elementAt(0,0)->resize(WLength(200,WLength::Pixel),WLength(100,WLength::Percentage));
//
//	WTable * pUpTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
//	pUpTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
//	pUpTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
//	new WText(m_formText.szAlertArea, (WContainerWidget *)pUpTable->elementAt(0,0));
//	
//	pGroupTree =new CCheckBoxTreeView((WContainerWidget *)pSubTreeTable->elementAt(0,0));
//	pSubTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
//
//	WImage *spaceImg =new WImage("../icons/space.gif");
//	pFrameTable ->elementAt(0,1)->addWidget(spaceImg);
//	std::string strContext;
//	strContext+="style=\"WIDTH:1px;CURSOR: w-resize\" ";
//	strContext+=" onmousedown='_canResize=true;this.setCapture(true)'";
//	strContext+="  onmouseup='this.releaseCapture();_canResize=false;'";
//	sprintf(pFrameTable ->elementAt(0,1)->contextmenu_,"%s", strContext.c_str());
//		 
//
//	WTable * pReportTable = new WTable((WContainerWidget *)pFrameTable ->elementAt(0,2));
//	pFrameTable->elementAt(0,2)->setVerticalAlignment(AlignTop);
//	pReportTable ->setStyleClass("t62");
///*	pHide1 = new WImage("../icons/close.gif", (WContainerWidget *)pReportTable->elementAt(0,0));
//	if( pHide1)
//	{
//		pHide1->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
//		WObject::connect(pHide1, SIGNAL(clicked()), this, SLOT(showAddReport()));
//		pHide1->hide();
//	}
//	pShow1 = new WImage("../icons/open.gif", (WContainerWidget *)pReportTable->elementAt(0,0));
//	if(pShow1)
//	{
//		pShow1->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
//		WObject::connect(pShow1, SIGNAL(clicked()), this, SLOT(hideAddReport()));
//	}
//
//	new WText(m_formText.szReportAddTitle, (WContainerWidget *)pReportTable->elementAt(0,0));
//	pReportTable->elementAt(0,0)->setStyleClass("t1title");
//*/	pReportTable->elementAt(1,0)->setVerticalAlignment(AlignTop);
//	pTable1 = new WTable((WContainerWidget *)pReportTable->elementAt(1,0));
//	if(pTable1)
//	{
//
//		pTable1->setStyleClass("t3");
//		
//		new WText(m_formText.szReportTitle,(WContainerWidget*)pTable1->elementAt(0,0));
//		new WText("<span class =required>*</span>", (WContainerWidget*)pTable1 -> elementAt(0,0));
//		m_pTitle = new WLineEdit("", (WContainerWidget*)pTable1->elementAt(0,1));
//		m_pTitle ->setTextSize(60);
//
//		//
//		AnswerTable->AddErrorText(pTable1,strErrorTitle,2,1);
//
//		m_pHelpTitle = new WText(m_formText.szReportTitleHelp, (WContainerWidget*)pTable1->elementAt(3,1));
//		m_pHelpTitle ->setStyleClass("helps");
//		m_pHelpTitle ->hide();
//
//		m_pErrorTitle = new WText(m_formText.szSameSection, (WContainerWidget*)pTable1->elementAt(4,1));
//		m_pErrorTitle ->setStyleClass("errors");
//		m_pErrorTitle->hide();
//
//		pTable1->elementAt(0,0)->resize(WLength(30, WLength::Percentage),WLength(100, WLength::Percentage));
//
//		new WText(m_formText.szReportDescript, (WContainerWidget*)pTable1->elementAt(5,0));
//		m_pDescript = new WLineEdit("", (WContainerWidget*)pTable1->elementAt(5,1));
//		m_pDescript ->setTextSize(60);
//		m_pHelpDescript = new WText(m_formText.szReportDescriptHelp, (WContainerWidget*)pTable1->elementAt(6,1));
//		m_pHelpDescript ->setStyleClass("helps");
//		m_pHelpDescript ->hide();
//		
//
//		new WText(m_formText.szReportPeriod, (WContainerWidget*)pTable1->elementAt(7, 0));
//		m_pPeriod = new WComboBox((WContainerWidget*)pTable1->elementAt(7,1));
//		m_pPeriod ->addItem(m_formText.szDayPeriod);
//		m_pPeriod ->addItem(m_formText.szWeekPeriod);
//		m_pPeriod ->addItem(m_formText.szMonthPeriod);
//
//		m_pHelpPeriod = new WText(m_formText.szReportPeriodHelp, (WContainerWidget*)pTable1->elementAt(8, 1));
//		m_pHelpPeriod ->setStyleClass("helps");
//		m_pHelpPeriod ->hide();
//
//		new WText(m_formText.szReportOption, (WContainerWidget*)pTable1->elementAt(9, 0));
//		m_pStatusResult = new WCheckBox(m_formText.szReportOptStatus, (WContainerWidget*)pTable1->elementAt(10,1));
//		m_pStatusResult->setChecked(true);
//		m_pListClicket = new WCheckBox(m_formText.szListClicket, (WContainerWidget*)pTable1->elementAt(11,1));
//		m_pListClicket ->setChecked(true);
//		
//		m_pErrorResult = new WCheckBox(m_formText.szReportOptError1, (WContainerWidget*)pTable1->elementAt(13,1));
//		m_pErrorResult ->setChecked(true);
//		m_pErrorResult -> hide();
//		
//		m_pGraphic = new WCheckBox("", (WContainerWidget*)pTable1->elementAt(12,1));
//		m_pGraphic ->setChecked(true);		
//		m_pComboGraphic = new WComboBox((WContainerWidget*)pTable1->elementAt(12,1));
//		m_pComboGraphic ->addItem(m_formText.szReportOptGraphic1);
//		m_pComboGraphic ->addItem(m_formText.szReportOptGraphic2);
//		
//		m_pListData = new WCheckBox(m_formText.szReportOptData, (WContainerWidget*)pTable1->elementAt(14,1));
//		m_pListData->hide();		
//		m_pListNormal = new WCheckBox(m_formText.szReportOptNormal , (WContainerWidget*)pTable1->elementAt(15,1));
//		m_pListNormal->hide();
//		
//		m_pListError = new WCheckBox(m_formText.szReportOptError, (WContainerWidget*)pTable1->elementAt(13,1));
//		m_pListError -> setChecked(true);
//		
//		m_pListDanger = new WCheckBox(m_formText.szReportOptDanger, (WContainerWidget*)pTable1->elementAt(14,1));
//		m_pListDanger ->setChecked(true);
//		m_pListAlert = new WCheckBox(m_formText.szReportOptAlert, (WContainerWidget*)pTable1->elementAt(16,1));
//
//		new WText(m_formText.szReportEmailSend, (WContainerWidget*)pTable1->elementAt(17, 0));
//		m_pEmailSend = new WLineEdit("", (WContainerWidget*)pTable1->elementAt(17, 1));
//		m_pEmailSend->setTextSize(60);
//		m_pHelpEmailSend = new WText(m_formText.szReportEmailSendHelp, (WContainerWidget*)pTable1->elementAt(18, 1));
//		
//		m_pHelpEmailSend->setStyleClass("helps");
//		m_pHelpEmailSend->hide();
//
//		new WText(m_formText.szReportParameter, (WContainerWidget*)pTable1->elementAt(19,0));
//		m_pParameter = new WCheckBox(m_formText.szReportParameter1, (WContainerWidget*)pTable1->elementAt(19,1));
//		m_pHelpParameter = new WText(m_formText.szReportParameterHelp, (WContainerWidget*)pTable1->elementAt(20, 1));
//		m_pHelpParameter ->setStyleClass("helps");
//		m_pHelpParameter ->hide();
//		
////		new WText(m_formText.szReportDeny, (WContainerWidget*)pTable1->elementAt(19,0));
//		m_pDeny = new WCheckBox(m_formText.szReportDeny, (WContainerWidget*)pTable1->elementAt(21, 1));
//		m_pHelpDeny = new WText(m_formText.szReportDenyHelp, (WContainerWidget*)pTable1->elementAt(22, 1));
//		m_pHelpDeny ->setStyleClass("helps");
//		m_pHelpDeny ->hide();
//
//		new WText(m_formText.szReportGenerateTime, (WContainerWidget*)pTable1->elementAt(23,0));
//		m_pGenerate = new WComboBox((WContainerWidget*)pTable1->elementAt(23,1));
//		new WText(m_formText.szTimeUnit, (WContainerWidget*)pTable1->elementAt(23,1));
//		for(int k = 0; k < 24; k++)
//		{
//			char buf[256];
//			memset(buf, 0, 256);
//			sprintf(buf, "%2d",k);
//			m_pGenerate ->addItem(buf);
//		}
//		m_pHelpGenerate = new WText(m_formText.szReportGenerateTimeHelp, (WContainerWidget*)pTable1->elementAt(24,1));
//		m_pHelpGenerate ->setStyleClass("helps");
//		m_pHelpGenerate ->hide();
//
//
//		WText* temptext = new WText(m_formText.szClicket, (WContainerWidget*)pTable1->elementAt(25,0));
//		temptext ->hide();
//
//		//m_pClicketSet = new WCheckBox("", (WContainerWidget*)pTable1->elementAt(23,1));
//		m_pClicket = new WLineEdit("", (WContainerWidget*)pTable1->elementAt(25,1));
//		m_pClicket ->hide();
//		m_pHelpClicket = new WText(m_formText.szClicketHelp, (WContainerWidget*)pTable1->elementAt(26, 1));
//		m_pHelpClicket ->setStyleClass("helps");
//		m_pHelpClicket ->hide();
//
//		new WText(m_formText.szTaskDes1, (WContainerWidget*)pTable1->elementAt(25, 0));
//		m_pPlan = new WComboBox((WContainerWidget*)pTable1->elementAt(25,1));
//        //m_pSchedule -> setStyleClass("input_border");
//		
//		std::list<string> tasknamelist;
//		std::list<string>::iterator m_pItem;
//		GetAllTaskName(tasknamelist);
//
//		for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem++)
//		{
//			std::string m_pNameStr = *m_pItem;
//			
//			OBJECT hTask = GetTask(m_pNameStr);
//			std::string sValue = GetTaskValue("Type", hTask);
//			
//			//if(strcmp(sValue.c_str(), m_formText.szPlanTypeRel.c_str()) == 0)
//			if(strcmp(sValue.c_str(), "2") == 0)
//			{
//				m_pPlan -> addItem(m_pNameStr);
//			}
//		}
//		m_pHelpPlan = new WText(m_formText.szHelpPlan, (WContainerWidget*)pTable1->elementAt(26, 1));
//		m_pHelpPlan -> setStyleClass("helps");
//		m_pHelpPlan -> hide();
//
//
//		WText * starttimetext = new WText(m_formText.szStartTime, (WContainerWidget*)pTable1->elementAt(27, 0));
//		starttimetext -> hide();
//
//		m_pStartTime = new WLineEdit("", (WContainerWidget*)pTable1->elementAt(27, 1));
//		m_pStartTime->setTextSize(60);
//		m_pStartTime->hide();
//		m_pHelpStartTime = new WText(m_formText.szHelpStartTime, (WContainerWidget*)pTable1->elementAt(28, 1));
//		m_pHelpStartTime -> setStyleClass("helps");
//		m_pHelpStartTime -> hide();
//		new WText(m_formText.szEndTime, (WContainerWidget*)pTable1->elementAt(29, 0));
//		//m_pEndTime = new WLineEdit("", (WContainerWidget*)pTable1->elementAt(28, 1));
//		//m_pEndTime->setTextSize(60);			
//		//m_pEndTime->setStyleClass("ttext");		
//		m_pEndTime = new WComboBox((WContainerWidget*)pTable1->elementAt(29, 1));
//		for(int nEndTime = 0; nEndTime < 24; nEndTime++)
//		{
//			char sEndTime[256];
//			sprintf(sEndTime, "%d", nEndTime);
//			m_pEndTime ->addItem(sEndTime);
//		}
//		new WText(":", (WContainerWidget*)pTable1->elementAt(29, 1));
//		m_pEndMinute = new WComboBox((WContainerWidget*)pTable1->elementAt(29, 1));
//		m_pEndMinute->addItem("00");
//		m_pEndMinute->addItem("30");
//		
//
//		m_pHelpEndTime = new WText(m_formText.szHelpEndTime, (WContainerWidget*)pTable1->elementAt(30, 1));
//		m_pHelpEndTime -> setStyleClass("helps");
//		m_pHelpEndTime -> hide();
//
//		new WText(m_formText.szWeekEndTime, (WContainerWidget*)pTable1->elementAt(31, 0));
//		m_pWeekEndBox = new WComboBox((WContainerWidget*)pTable1->elementAt(31,1));
//		m_pWeekEndBox ->addItem(m_formText.szWeek1);
//		m_pWeekEndBox ->addItem(m_formText.szWeek7);
//		m_pWeekEndBox ->addItem(m_formText.szWeek6);
//		m_pWeekEndBox ->addItem(m_formText.szWeek5);
//		m_pWeekEndBox ->addItem(m_formText.szWeek4);
//		m_pWeekEndBox ->addItem(m_formText.szWeek3);
//		m_pWeekEndBox ->addItem(m_formText.szWeek2);
//		m_pHelpWeekPlan = new WText(m_formText.szHelpWeek, (WContainerWidget*)pTable1->elementAt(32, 1));
//		m_pHelpWeekPlan->setStyleClass("helps");
//		m_pHelpWeekPlan->hide();
//	}
//
//	pReportTable->elementAt(1,0)->setVerticalAlignment(AlignTop);
//	pReportTable->elementAt(1,0)->addWidget(pTable1);
//	//WScrollArea * righttable = new WScrollArea(pReportTable->elementAt(1,0));
//	//righttable->resize(WLength(800,WLength::Pixel), WLength(536,WLength::Pixel));
//
//	WObject::connect(AnswerTable->pCancel, SIGNAL(clicked()), this, SLOT(Back()));
//	WObject::connect(AnswerTable->pSave, SIGNAL(clicked()), this, SLOT(Save()));
//#if 1
//	int nRow;
//	nRow = AnswerTable->GetContentTable()->numRows();
//	AnswerTable->GetContentTable()->elementAt(nRow,0)->setStyleClass("t5");
//	//end report page
//#endif

}

void CSVAddReport::ExChangeAdd()
{
	PrintDebugString("------ExChangeAddEvent------\n");
	emit ExChangeAddEvent();
}
void CSVAddReport::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "reportsetRes";
	WebSession::js_af_up += "')";
}

void CSVAddReport::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_List_Key_Value",m_formText.szListClicket);
			FindNodeValue(ResNode,"IDS_Run_Plan_Delete",m_formText.szTaskDes1);
			FindNodeValue(ResNode,"IDS_AddMail_Schedule_Description",m_formText.szHelpTaskDes);
			FindNodeValue(ResNode,"IDS_Report_Day",m_formText.szDayPeriod);
			FindNodeValue(ResNode,"IDS_Report_Week",m_formText.szWeekPeriod);
			FindNodeValue(ResNode,"IDS_Report_Month",m_formText.szMonthPeriod);
			FindNodeValue(ResNode,"IDS_Hours",m_formText.szTimeUnit);
			FindNodeValue(ResNode,"IDS_Report_Add",m_formText.szReportAddTitle);
			FindNodeValue(ResNode,"IDS_Report_Caption",m_formText.szReportTitle);
			FindNodeValue(ResNode,"IDS_Report_Caption_Help",m_formText.szReportTitleHelp);
			FindNodeValue(ResNode,"IDS_Report_Desc",m_formText.szReportDescript);
			FindNodeValue(ResNode,"IDS_Report_Note",m_formText.szReportDescriptHelp);
			FindNodeValue(ResNode,"IDS_Time_Period",m_formText.szReportPeriod);
			FindNodeValue(ResNode,"IDS_Time_Period_Description",m_formText.szReportPeriodHelp);
			FindNodeValue(ResNode,"IDS_Report_Option",m_formText.szReportOption);
			FindNodeValue(ResNode,"IDS_Report_Option_Help",m_formText.szReportOptionHelp);
			FindNodeValue(ResNode,"IDS_State_List",m_formText.szReportOptStatus);
			FindNodeValue(ResNode,"IDS_List_Error",m_formText.szReportOptError);
			FindNodeValue(ResNode,"IDS_Line_Graphic",m_formText.szReportOptGraphic1);
			FindNodeValue(ResNode,"IDS_Strike_Graphic",m_formText.szReportOptGraphic2);
			FindNodeValue(ResNode,"IDS_Date_List",m_formText.szReportOptData);
			FindNodeValue(ResNode,"IDS_List_Normal",m_formText.szReportOptNormal);
			FindNodeValue(ResNode,"IDS_List_Error",m_formText.szReportOptError1);
			FindNodeValue(ResNode,"IDS_List_Danger",m_formText.szReportOptDanger);
			FindNodeValue(ResNode,"IDS_List_Send_Alert",m_formText.szReportOptAlert);
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
			FindNodeValue(ResNode,"IDS_Clicked_Config",m_formText.szClicket);
			FindNodeValue(ResNode,"IDS_Clicked_Enter",m_formText.szClicketHelp);
			FindNodeValue(ResNode,"IDS_Save",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_Cancel",m_formText.szBack);
			FindNodeValue(ResNode,"IDS_Connect_SVDB_Fail",m_formText.szConnErr);
			FindNodeValue(ResNode,"IDS_Report_Same",m_formText.szSameSection);
			FindNodeValue(ResNode,"IDS_Start_Time1",m_formText.szStartTime);
			FindNodeValue(ResNode,"IDS_End_Time1",m_formText.szEndTime);
			FindNodeValue(ResNode,"IDS_Report_Start_Time",m_formText.szHelpStartTime);
			FindNodeValue(ResNode,"IDS_Report_End_Time",m_formText.szHelpEndTime);
			FindNodeValue(ResNode,"IDS_Monday",m_formText.szWeek7);
			FindNodeValue(ResNode,"IDS_Tuesday",m_formText.szWeek6);
			FindNodeValue(ResNode,"IDS_Wednesday",m_formText.szWeek5);
			FindNodeValue(ResNode,"IDS_Thursday",m_formText.szWeek4);
			FindNodeValue(ResNode,"IDS_Friday",m_formText.szWeek3);
			FindNodeValue(ResNode,"IDS_Saturday",m_formText.szWeek2);
			FindNodeValue(ResNode,"IDS_Sunday",m_formText.szWeek1);
			FindNodeValue(ResNode,"IDS_Week_Report_End_Time",m_formText.szWeekEndTime);
			FindNodeValue(ResNode,"IDS_Week_Report_Date_Help",m_formText.szHelpPlan);
			FindNodeValue(ResNode,"IDS_Week_Report_Help",m_formText.szHelpWeek);
			FindNodeValue(ResNode,"IDS_Week_Report_Content_Empty",m_formText.szScopeError);
			FindNodeValue(ResNode,"IDS_Alert_Area",m_formText.szAlertArea);
			FindNodeValue(ResNode,"IDS_Total_Report",strTotalReport);
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Report_Edit",strEditReport);
			FindNodeValue(ResNode,"IDS_Report_Add",strAddReport);
			FindNodeValue(ResNode,"IDS_Report_Title_Empty",strErrorTitle);
			FindNodeValue(ResNode,"IDS_AreaGraphic",m_formText.szAreaMap);
		}
//		SubmitResource(objRes);
		CloseResource(objRes);
	}
	//strErrorTitle = "报告标题不能为空！";
	
	strInError = "输入错误，标题包含非法字符！";

}
std::string CSVAddReport::GetSelScope()
{
			GetGroupRightList();
			std::string strUnGroupRight;
			strUnGroupRight=",";
			//get un select  scope
			for( list<std::string >::iterator _listitem = pUnGroupRightList.begin(); _listitem != pUnGroupRightList.end(); _listitem ++)
			{
				strUnGroupRight+=_listitem->c_str();
				strUnGroupRight+=",";
			}
			std::string   szGroupRight=",";
			/*char aaaa[2000];
			sprintf(aaaa,"\n ungroup is %s\n",strUnGroupRight.c_str());
			OutputDebugString(aaaa);*/
			for( list<std::string >::iterator _listitem = pGroupRightList.begin(); _listitem != pGroupRightList.end(); _listitem ++)
			{  	
				std::string strTmp;
				strTmp=",";
				strTmp+=_listitem->c_str();
				strTmp+=".";

//				OutputDebugString(strTmp.c_str());

				int nIndex;
				nIndex=strUnGroupRight.find(strTmp,0);
				if(nIndex <0)
				{
					szGroupRight +=_listitem->c_str();
					szGroupRight +=",";
				}
			}
			return szGroupRight;

}
void CSVAddReport::Save()
{
	//验证报告标题是否为空
	std::list<string> errorMsgList;
	bool bShowErr=false;
	if(m_pTitle->text().empty())
	{
		errorMsgList.push_back(strErrorTitle);
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
	//验证名字是否重复

	if(bShowErr==true)
	{
		m_pReportTable->ShowErrorMsg(errorMsgList);		//show error msg
		return;
	}

	//检测范围不能为空
	std::string szGroupRight;

	//TODO::修改这里，这里引用了GroupTree
	szGroupRight=GetSelScope();

	if(szGroupRight.size()<=1)
	{
		WebSession::js_af_up="alert(\"" + m_formText.szScopeError +"\");";
		return;
	}

	chg = "";
	
	PrintDebugString("-------------------00-------Begin Save Function");

	//jansion.zhou 2006-12-25
	//m_pConnErr->setText("");
	//m_pConnErr->hide();

	//m_pErrorTitle->hide();
	//m_pReportTable->HideAllErrorMsg();
	
	std::list<string> sectionlist;
	bool IsSave = GetIniFileSections(sectionlist, "reportset.ini");

	if(IsSave)
	{
		std::list<string> sectionlist;
		std::list<string>::iterator Item;
		GetIniFileSections(sectionlist, "reportset.ini");
		bool bRe = false;

		std::string strTitleTxt;
		strTitleTxt= TrimStdString(m_pTitle->text());


		for(Item = sectionlist.begin(); Item != sectionlist.end(); Item++)
		{
			std::string str = *Item;
			if(strcmp(str.c_str(), strTitleTxt.c_str()) == 0)
			{
				bRe = true;
				break;
			}
		}
		
		if(strcmp(chgstr.c_str(), "") != 0)
		{
			for(Item = sectionlist.begin(); Item != sectionlist.end(); Item++)
			{
				std::string str = *Item;
				if(strcmp(str.c_str(), strTitleTxt.c_str()) == 0)
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
		//	bRe = false;
		}
		PrintDebugString("-------------------01------");
		if(bRe)
		{
			//jansion.zhou 2006-12-25
			//m_pConnErr ->setText(m_formText.szSameSection);
			//m_pConnErr ->show();
			errorMsgList.push_back(m_formText.szSameSection);
			m_pReportTable->ShowErrorMsg(errorMsgList);		//show error msg
			//return;
PrintDebugString("-------------------011111111111111111111111111------");
			return;

//			m_pErrorTitle->show();
			//m_pReportTable->ShowErrorMsg(errorMsgList);		//show error msg
		}
		else
		{

			m_report.szTitle =TrimStdString( m_pTitle->text());

			m_report.szDescript = m_pDescript->text();
			m_report.szPeriod = m_pPeriod->currentText();

			m_report.szPlan = m_pPlan->currentText();
			
			if(m_pStatusResult ->isChecked())
			{
				m_report.szStatusresult = "Yes";
			}
			else
			{
				m_report.szStatusresult = "No";
			}
			
			if(m_pErrorResult->isChecked())
			{
				m_report.szErrorresult = "Yes";
			}
			else
			{
				m_report.szErrorresult = "No";
			}
			
			if(m_pGraphic->isChecked())
			{
				m_report.szGraphic = "Yes";
				m_report.szComboGraphic = m_pComboGraphic->currentText();
			}
			else
			{
				m_report.szGraphic = "No";
				m_report.szComboGraphic = "";
			}

			if(m_pListData ->isChecked())
			{
				m_report.szListData = "Yes";
			}
			else
			{
				m_report.szListData = "No";
			}
			//Ticket #123  start   -------苏合
			if(m_pGenExcel ->isChecked())
			{
				m_report.szExcel = "Yes";
			}
			else
			{
				m_report.szExcel = "No";
			}
            //Ticket #123   end    -------苏合
			

			if(m_pListError ->isChecked())
			{
				m_report.szListError = "Yes";
			}
			else
			{
				m_report.szListError = "No";
			}

			if(m_pListDanger ->isChecked())
			{
				m_report.szListDanger = "Yes";
			}
			else
			{
				m_report.szListDanger = "No";
			}

			if(m_pListAlert ->isChecked())
			{
				m_report.szListAlert = "Yes";
			}
			else
			{
				m_report.szListAlert = "No";
			}

			if(m_pParameter ->isChecked())
			{
				m_report.szParameter = "Yes";
			}
			else
			{
				m_report.szParameter = "No";
			}

			if(m_pDeny ->isChecked())
			{
				m_report.szDeny = "Yes";
			}
			else
			{
				m_report.szDeny = "No";
			}

			if(m_pListClicket->isChecked())
			{
				m_report.szListClicket = "Yes";
			}
			else
			{
				m_report.szListClicket = "No";
			}

			m_report.nWeekEndIndex=m_pWeekEndBox->currentIndex();

			// group right tree
			m_report.szGroupRight=szGroupRight;


			m_report.szClicketValue = m_pClicket->text();
			

			m_report.szEmailSend = m_pEmailSend->text();

			m_report.szGenerate = m_pGenerate->currentText();

			m_report.szStartTime = m_pStartTime->text();
			//m_report.szEndTime = m_pEndTime->text();
			std::string szTime = m_pEndTime->currentText();
			szTime += ":";
			szTime += m_pEndMinute->currentText();
			m_report.szEndTime = szTime;

			chen::TTime time = chen::TTime::GetCurrentTimeEx();
			
			m_report.szCreateTime = time.Format();

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
			m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strTotalReport,m_pTitle->text());

			emit SavePhone(m_report);
			chgstr = "";

			//m_pErrorTitle->hide();
			//m_pReportTable->HideAllErrorMsg();
		}
	}
	else
	{
		//jansion.zhou 2006-12-25
		//m_pConnErr->setText(m_formText.szConnErr);
		//m_pConnErr->show();
		//errorMsgList.push_back(m_formText.szSameSection);
		//m_pReportTable->ShowErrorMsg(errorMsgList);		//show error msg
		//return;

	}

//	AnswerTable->HideAllErrorMsg();
	m_pReportTable->HideAllErrorMsg();

	PrintDebugString("-------------------02  end-------Begin Save Function");
}


void CSVAddReport::Back()
{
	//AnswerTable->HideAllErrorMsg();
	m_pReportTable->HideAllErrorMsg();
	chg = "cancel";
    emit BackTo(chg);
}

void CSVAddReport::setProperty(SAVE_REPORT_LIST * report)
{
	
	m_pTitle ->setText(report->szTitle);
	m_pDescript ->setText(report->szDescript);
	m_pPeriod ->setCurrentIndexByStr(report->szPeriod);

	m_pPlan ->setCurrentIndexByStr(report->szPlan);


	if(strcmp(report->szStatusresult.c_str() , "Yes") == 0)
	{
		m_pStatusResult ->setChecked(true);
	}
	else
	{
		m_pStatusResult ->setChecked(false);
	}
	
	if(strcmp(report->szErrorresult.c_str() , "Yes") == 0)
	{
		m_pErrorResult ->setChecked(true);
	}
	else
	{
		m_pErrorResult ->setChecked(false);
	}

	if(strcmp(report->szGraphic.c_str(), "Yes") == 0)
	{
		m_pGraphic ->setChecked(true);
		m_pComboGraphic ->setCurrentIndexByStr(report->szComboGraphic);
	}
	else
	{
		m_pGraphic ->setChecked(false);
		m_pComboGraphic ->setCurrentIndex(0);
	}

	if(strcmp(report->szListData.c_str(), "Yes") == 0)
	{
		m_pListData ->setChecked(true);
	}
	else
	{
		m_pListData ->setChecked(false);
	}

	if(strcmp(report->szListError.c_str(), "Yes") == 0)
	{
		m_pListError ->setChecked(true);
	}
	else
	{
		m_pListError ->setChecked(false);
	}

	if(strcmp(report->szListDanger.c_str(), "Yes") == 0)
	{
		m_pListDanger ->setChecked(true);
	}
	else
	{
		m_pListDanger ->setChecked(false);
	}

	if(strcmp(report->szListAlert.c_str(), "Yes") == 0)
	{
		m_pListAlert ->setChecked(true);
	}
	else
	{
		m_pListAlert ->setChecked(false);
	}

	m_pEmailSend->setText(report->szEmailSend);

	//Ticket #123  start   -------苏合
	if(strcmp(report->szExcel.c_str(), "Yes") == 0)
	{
		m_pGenExcel ->setChecked(true);
	}
	else
	{
		m_pGenExcel ->setChecked(false);
	}
    //Ticket #123   end    -------苏合
	

	if(strcmp(report->szParameter.c_str(), "Yes") == 0)
	{
		m_pParameter ->setChecked(true);
	}
	else
	{
		m_pParameter ->setChecked(false);
	}

	if(strcmp(report->szDeny.c_str(), "Yes") == 0)
	{
		m_pDeny ->setChecked(true);
	}
	else
	{
		m_pDeny ->setChecked(false);
	}

	if(strcmp(report->szListClicket.c_str(), "Yes") ==0)
	{
		m_pListClicket ->setChecked(true);
	}
	else
	{
		m_pListClicket ->setChecked(false);
	}
	

	m_pClicket ->setText(report->szClicketValue);
	
	m_pGenerate ->setCurrentIndexByStr(report->szGenerate);

	m_pStartTime ->setText(report->szStartTime);
	m_pStartTime ->hide();

	//m_pEndTime->setText(report->szEndTime);
	std::string szEndTime = report->szEndTime;
	int pos = szEndTime.find(":", 0);
	std::string szHour = szEndTime.substr(0, pos);
	std::string szMinute = szEndTime.substr(pos + 1, szEndTime.size() - pos - 1);

	m_pEndTime->setCurrentIndexByStr(szHour);
	m_pEndMinute->setCurrentIndexByStr(szMinute);

	m_pWeekEndBox->setCurrentIndex(report->nWeekEndIndex);

	//jansion.zhou 2006-12-25
	//m_pConnErr ->setText("");
}

void CSVAddReport::clearData()
{
	//初始化任务计划
	m_pPlan ->clear();
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

		/*
		m_pHelpTitle ->hide();
		m_pHelpDescript ->hide();
		m_pHelpPeriod ->hide();
		m_pHelpEmailSend ->hide();
		m_pHelpParameter ->hide();
		m_pHelpDeny ->hide();
		m_pHelpGenerate ->hide();
		m_pHelpClicket ->hide();
		m_pHelpStartTime ->hide();
		m_pHelpEndTime ->hide();
		m_pHelpPlan -> hide();
		m_pHelpWeekPlan->hide();
		*/

		m_pTitle ->setText("");

		m_pDescript ->setText("");

		m_pStatusResult ->setChecked(true);
		m_pErrorResult ->setChecked(true);

		m_pGraphic ->setChecked(true);
		m_pListData ->setChecked(true);
		m_pListNormal ->setChecked(true);
		m_pListClicket ->setChecked(true);
		m_pListError ->setChecked(true);
		m_pListDanger ->setChecked(true);
		m_pListAlert ->setChecked(false);

		//Ticket #123     -------苏合
		m_pGenExcel->setChecked(false);
		//Ticket #123     -------苏合

	//	m_pHelpEmailSend ->hide();
		m_pEmailSend ->setText("");
	//	m_pHelpParameter ->hide();

		m_pParameter ->setChecked(false);
	//	m_pHelpDeny ->hide();
		m_pDeny ->setChecked(false);
	//	m_pHelpGenerate ->hide();

		m_pPeriod ->setCurrentIndex(0);
		m_pComboGraphic ->setCurrentIndex(0);
		m_pGenerate ->setCurrentIndex(0);
		m_pPlan->setCurrentIndex(0);
		m_pEndMinute->setCurrentIndex(0);
//		m_pHelpClicket ->hide();
		m_pClicket ->setText("");
		//jansion.zhou 2006-12-25
		//m_pConnErr ->setText("");

		m_pStartTime -> setText("");
		
		chen::TTime time = chen::TTime::GetCurrentTimeEx();
		//m_pEndTime -> setText(time.Format());
		m_pEndTime->setCurrentIndex(0);
		//m_pEndTime -> setText("00:00");
		m_pWeekEndBox->setCurrentIndex(0);

		m_pReportTable->HideAllErrorMsg();
		if (m_pReportTable->bShowHelp)
		{
			m_pReportTable->ShowOrHideHelp();
		}
}
void CSVAddReport::showAddPhoneList()
{


}

void CSVAddReport::hideAddPhoneList()
{
	
}

void CSVAddReport::showAddReport()
{
	pShow1 -> show();
	pHide1 -> hide();
	pTable1 -> show();
}

void CSVAddReport::hideAddReport()
{
	pShow1 -> hide();
	pHide1 -> show();
	pTable1 -> hide();
}


void CSVAddReport::AddPhoneHelp()
{
	AnswerTable->HideAllErrorMsg();
	if(IsHelp)
	{
		m_pHelpTitle ->show();
		m_pHelpDescript ->show();
		m_pHelpPeriod ->show();
		m_pHelpEmailSend ->show();
		m_pHelpParameter ->show();
		m_pHelpDeny ->show();
		m_pHelpGenerate ->show();
		m_pHelpClicket ->hide();
		//m_pHelpStartTime ->show();
		m_pHelpEndTime ->show();
		m_pHelpPlan -> show();
		m_pHelpWeekPlan->show();
		IsHelp = false;
	}
	else
	{
		m_pHelpTitle ->hide();
		m_pHelpDescript ->hide();
		m_pHelpPeriod ->hide();
		m_pHelpEmailSend ->hide();
		m_pHelpParameter ->hide();
		m_pHelpDeny ->hide();
		m_pHelpGenerate ->hide();
		m_pHelpClicket ->hide();
		m_pHelpStartTime ->hide();
		m_pHelpEndTime ->hide();
		m_pHelpPlan -> hide();
		m_pHelpWeekPlan->hide();
		IsHelp = true;
	}
}

void CSVAddReport::TestSMS()
{
}

void CSVAddReport::TestSMSing()
{


}
void CSVAddReport::GetGroupChecked(WTreeNode*pNode,  std::list<string > &pGroupRightList_,std::list<string > &pUnGroupRightList_)
{
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			if(pNode->treeCheckBox_->isChecked())
			{
				//char aaa[300];
				//sprintf(aaa, "scope id is    %s\n",pNode->strId.c_str());
				
				//OutputDebugString(aaa);
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
void CSVAddReport::GetGroupRightList()
{
	pGroupRightList.clear();
	pUnGroupRightList.clear();
	if(pGroupTree->treeroot!=NULL)
	{
		GetGroupChecked(pGroupTree->treeroot,pGroupRightList,pUnGroupRightList);
	}
}

void CSVAddReport::SetGroupChecked(WTreeNode*pNode,  std::string  pGroupRightList_,bool bPCheck)
{
	std::string  strSelId;
	if(pNode!=NULL)
	{
		//pNode->expand();
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


void CSVAddReport::setGroupRightCheck(std::string groupright)
{
	
	char abc[2000];
	sprintf(abc,"-----groupright is %s-------------  ",groupright.c_str());
	OutputDebugString(abc);
	//TODO::这里需要修改
	
	if(pGroupTree->treeroot!=NULL)
        	SetGroupChecked(pGroupTree->treeroot,groupright,false);
}
