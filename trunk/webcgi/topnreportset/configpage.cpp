/*************************************************
*  @file topnreportset.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include "configpage.h"

// include WT Libs
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"

#include "svapi.h"
#include "websession.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

extern void PrintDebugString(const char *szErrmsg);
extern unsigned int RandIndex();


/**************************************************
参数：
    szRepStr：需要更新字符串

功能：
	在浏览器地址栏传输时，"&" "$" "#" " "字符需
	用%26 %24 %23 %20替换

返回值：
    更新后的字符串
**************************************************/
std::string RepHrefStr(std::string szRepStr)
{
	std::string szValue = szRepStr;

	int nPos = szValue.find("\\", 0);
    while (nPos > 0)
    {
        szValue = szValue.substr(0, nPos ) + "\\" + szValue.substr(nPos);
        nPos += 2;
        nPos = szValue.find("\\", nPos);
    }

    nPos = szValue.find("&", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%26" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find("&", nPos);
    }

    nPos = szValue.find("$", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%24" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find("$", nPos);
    }

    nPos = szValue.find("#", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%23" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find("#", nPos);
    }

    nPos = szValue.find(" ", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%20" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find(" ", nPos);
    }

	return szValue;
}

/**************************************************************
参数：
	parent：容器

功能：
    构造函数
**************************************************************/
CSVTopnReportSet::CSVTopnReportSet(WContainerWidget * parent):
WContainerWidget(parent)
{
	IsShow = true;//是否显示帮助
	chgstr = ""; //报告名称是否改变
	loadString();//加载资源文件
    initForm();//初始化主界面
}


//添加客户端脚本变量
void CSVTopnReportSet::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}
/***************************************
参数：

功能：
    初始化TOPN报告页面
***************************************/
void CSVTopnReportSet::initForm()
{



	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>",this);


	m_pMainTable = new WSVMainTable(this,m_formText.szTitle,false);

	m_pReportListTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(0,0), List, m_formText.szTBTitle);
	

	if (m_pReportListTable->GetContentTable() != NULL)
	{
		m_pReportListTable->AppendColumn("",WLength(5,WLength::Percentage));
		m_pReportListTable->SetDataRowStyle("table_data_grid_item_img");

		m_pReportListTable->AppendColumn(m_formText.szColName,WLength(55,WLength::Percentage));
		m_pReportListTable->SetDataRowStyle("table_data_grid_item_text");

		m_pReportListTable->AppendColumn(m_formText.szColPeriod,WLength(20,WLength::Percentage));
		m_pReportListTable->SetDataRowStyle("table_data_grid_item_img");

		m_pReportListTable->AppendColumn(m_formText.szColEdit,WLength(20,WLength::Percentage));
		m_pReportListTable->SetDataRowStyle("table_data_grid_item_text");
	}

	addPhoneListNew();
	//connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));
	connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));

	if (m_pReportListTable->GetActionTable() != NULL)
	{
		
		m_pReportListTable->SetNullTipInfo(m_formText.szListEmpty);

		if(m_pListReport.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
			OutputDebugString("---------------- NO A------------------\n");
		}
		else
		{
			OutputDebugString("---------------- Yes A------------------\n");
			m_pReportListTable->HideNullTip();
		}
		
		m_pReportListTable->AddStandardSelLink(m_formText.szTipSelAll1 ,m_formText.szTipSelNone,m_formText.szTipSelInv);
		connect(m_pReportListTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		connect(m_pReportListTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		connect(m_pReportListTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));


		WTable *pTbl;

		m_pReportListTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pReportListTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		pTbl = new WTable(m_pReportListTable->GetActionTable()->elementAt(0,1));

		pTbl->setStyleClass("widthauto");
		m_pDel = new WSVButton(pTbl->elementAt(0,1),m_formText.szTipDel, "button_bg_del.png", "", false);

		//if(!GetUserRight("m_reportlistDel"))
		//	m_pDel->hide();
		//else
		//	m_pDel->show();

		if (m_pDel)
		{
			m_pDel->setToolTip(m_formText.szTipDel);
			connect(m_pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
		}

		m_pReportListTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		m_pAdd = new WSVButton(m_pReportListTable->GetActionTable()->elementAt(0,2),m_formText.szAddPhoneBut, "button_bg_add_black.png", m_formText.szTipAddNew, true);
		//if(!GetUserRight("m_reportlistAdd"))
		//	m_pAdd->hide();
		//else
		//	m_pAdd->show();

		if (m_pAdd)
		{
			m_pAdd->setToolTip(m_formText.szTipAddNew);
			WObject::connect(m_pAdd, SIGNAL(clicked()),"showbar();", this, SLOT(AddPhone())
				, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}

		//隐藏按钮
		pHideBut = new WPushButton("hide button",this);
		if(pHideBut)
		{
			pHideBut->setToolTip("Hide Button");
			connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelPhone()));
			pHideBut->hide();
		}
	}

	new WText("</div>", this);

	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);



	////在页面中包含basic.js脚本文件
	//new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	////第一层表格
	//WTable* T1table = new WTable(this);
	//T1table->setStyleClass("t1");

	//new WText(m_formText.szTitle, T1table->elementAt(0,0));
	//T1table->elementAt(0,0)->setStyleClass("t1title");
	//
	////TitleTable表格包含 是否连接提示信息， 翻译、刷新、帮助按钮
	//WTable * TitleTable = new WTable(T1table->elementAt(1,0));
	//TitleTable->setStyleClass("t3");
		
	//初始连接提示信息隐藏
	m_pConnErr = new WText("", (WContainerWidget *)this);
	m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	m_pConnErr ->hide();
	
	//测试连接SVDB
	std::list<string> sectionlist;
	bool IsConn = GetIniFileSections(sectionlist, "smsconfig.ini");
	if(!IsConn)
	{
		//连接SVDB失败
		m_pConnErr ->setText(m_formText.szConnErr);
		m_pConnErr ->show();
	}

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)this);
 	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();
	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)this);
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();
	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}

	////主框架帮助按钮
	//m_pHelpImg = new WImage("../icons/help.gif", (WContainerWidget *)TitleTable->elementAt( 0, 1));
	//m_pHelpImg ->setStyleClass("helpimg");
	//m_pHelpImg->setToolTip(m_formText.szHelp);
	//TitleTable->elementAt(0, 1) -> setContentAlignment(AlignTop | AlignRight);
	//WObject::connect(m_pHelpImg, SIGNAL(clicked()), this, SLOT(MainHelp()));


	////隐藏、显示列表
	//WTable * m_pListGeneral = new WTable(T1table->elementAt(2,0));
	//m_pListGeneral ->setStyleClass("t2");
	//
	////收/放显示栏
	//pHide2 = new WImage("../icons/open.gif", (WContainerWidget *)m_pListGeneral->elementAt( 0, 0));
 //   if ( pHide2 )
 //   {
 //       pHide2->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
 //       WObject::connect(pHide2, SIGNAL(clicked()), this, SLOT(showSmsList2()));   
 //       pHide2->hide();        
 //   }

 //   pShow2 = new WImage("../icons/close.gif", (WContainerWidget *)m_pListGeneral->elementAt( 0, 0));
 //   if ( pShow2 )
 //   {
 //       pShow2->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
 //       WObject::connect(pShow2, SIGNAL(clicked()), this, SLOT(hideSmsList2())); 
 //   }

	//m_pListGeneral->elementAt(0, 0)->setStyleClass("t2title");
	//new WText(m_formText.szTBTitle, (WContainerWidget *)m_pListGeneral->elementAt( 0, 0));

	////报告及操作按钮
	//table2 = new WTable((WContainerWidget *)m_pListGeneral->elementAt(1,0));
	//table2 -> setStyleClass("t3");
 //   if ( table2 )
 //   {
 //       addPhoneList(table2);//报告列表
	//	//编辑映射
	//	connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));
	//	AddGroupOperate(table2);//操作按钮
	//}	
}

void CSVTopnReportSet::ExChange()
{
	PrintDebugString("------ExChangeEvent------\n");
	emit ExChangeEvent();
}

void CSVTopnReportSet::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "topnreportsetRes";
	WebSession::js_af_up += "')";
}


/*******************************************************
参数：
	table：报告列表上一级表格

功能：
	从topnreportset.ini获得TOPN报告名称填充报告列表
*******************************************************/
void CSVTopnReportSet::addPhoneList(WTable * table)
{
	//TOPN报告列表
    m_ptbPhone = new WTable((WContainerWidget*)table->elementAt(7,0));
	//报告列表为空
	nullTable = new WTable((WContainerWidget*)table->elementAt(8, 0));

	m_ptbPhone -> setStyleClass("t3");
	nullTable -> setStyleClass("t3");

    if (m_ptbPhone)
    {
		//报告列表标题栏：是否选择、报告名称、报告周期、编辑
        m_ptbPhone -> setCellPadding(0);   
		m_ptbPhone->setCellSpaceing(0);
		
		new WText("", (WContainerWidget*)m_ptbPhone->elementAt(0,0));
        new WText(m_formText.szColName, (WContainerWidget*)m_ptbPhone->elementAt(0, 1));
		new WText(m_formText.szColPeriod, (WContainerWidget*)m_ptbPhone->elementAt(0, 2));
		new WText(m_formText.szColEdit, (WContainerWidget*)m_ptbPhone->elementAt(0, 3));
		
		m_ptbPhone->elementAt(0, 0)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 1)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 2)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 3)->setStyleClass("t3title");		
    }

	//报告名称LIST
	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;

	//从topnreportset.ini取TOPN报告LIST
	GetIniFileSections(sectionlist, "topnreportset.ini");

	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		//取报告列表的行数
		int numRow = m_ptbPhone->numRows();
		std::string section = *m_sItem;

		string ret = "error";

		std::string szPeriod = GetIniFileString(section, "Period", ret, "topnreportset.ini");
		if(strcmp(szPeriod.c_str(), "error") == 0)
		{
		}

		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_ptbPhone->elementAt(numRow, 0));		
		WText *pName = new WText(section, (WContainerWidget*)m_ptbPhone->elementAt(numRow , 1));		
		WText *pPeriod = new WText(szPeriod, (WContainerWidget*)m_ptbPhone->elementAt(numRow, 2));		
		WImage *pEdit = new WImage("../icons/edit.gif", (WContainerWidget*)m_ptbPhone->elementAt(numRow ,3));
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
		m_signalMapper.setMapping(pEdit, section);

		REPORT_LIST list;
		//给REPORT_LIST赋值
		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		//REPORT_LIST加入LIST
		m_pListReport.push_back(list);		
	}
	//设置列表行显示样式， 底色为一行白一行淡蓝
	m_ptbPhone->adjustRowStyle("tr1","tr2");		
}


void CSVTopnReportSet::addPhoneListNew()
{

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	GetIniFileSections(sectionlist, "topnreportset.ini");

	int numRow = m_pReportListTable->GeDataTable()->numRows();;
	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		m_pReportListTable->InitRow(numRow);

		std::string section = *m_sItem;

		string ret = "error";

		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignTop | AlignCenter);

		// 名称
		std::string strlinkname;
		std::string hrefstr = RepHrefStr(section);
		strlinkname ="<a href=/fcgi-bin/startsreportlist.exe?id="+hrefstr+">"+section+"</a>";
		WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));
		//m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
		m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignTop | AlignCenter);

		std::string szPeriod = GetIniFileString(section, "Period", ret, "reportset.ini");
		if(strcmp(szPeriod.c_str(), "error") == 0)
		{
		}

		WText *pPeriod = new WText(szPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignTop | AlignCenter);

		WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow ,6));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignTop | AlignCenter);
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
		connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
		m_signalMapper.setMapping(pEdit, section);

		REPORT_LIST list;

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		m_pListReport.push_back(list);

		numRow++;
	}
}

/******************************************************
参数：
	strErrMsg：显示错误信息字符串

功能：
    TEXT设置错误信息（未使用）
******************************************************/
void CSVTopnReportSet::showErrMsg(string &strErrMsg)
{
    if ( m_pErrMsg )
    {
        m_pErrMsg->setText(strErrMsg);
        m_pErrMsg->show();
    }
}

/****************************************************
参数：

功能：
    加载资源文件
****************************************************/
void CSVTopnReportSet::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			//添加Resource	
			FindNodeValue(ResNode,"IDS_TopN_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Save",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_TopN_Report_List",m_formText.szTBTitle);
			FindNodeValue(ResNode,"IDS_State",m_formText.szColSelAll);
			FindNodeValue(ResNode,"IDS_Title",m_formText.szColName);
			FindNodeValue(ResNode,"IDS_State",m_formText.szColState);
			FindNodeValue(ResNode,"IDS_Edit",m_formText.szColEdit);
			FindNodeValue(ResNode,"IDS_Time_Period",m_formText.szColPeriod);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Enable",m_formText.szEnable);
			FindNodeValue(ResNode,"IDS_All_Select_Other",m_formText.szTipSelAll);
			FindNodeValue(ResNode,"IDS_TopN_Report_Add",m_formText.szAddPhoneBut);
			FindNodeValue(ResNode,"IDS_Connect_SVDB_Fail",m_formText.szConnErr);
			FindNodeValue(ResNode,"IDS_All_Select",m_formText.szTipSelAll1);
			FindNodeValue(ResNode,"IDS_None_Select",m_formText.szTipSelNone);
			FindNodeValue(ResNode,"IDS_Invert_Select",m_formText.szTipSelInv);
			FindNodeValue(ResNode,"IDS_Add",m_formText.szTipAddNew);
			FindNodeValue(ResNode,"IDS_Delete",m_formText.szTipDel);
			FindNodeValue(ResNode,"IDS_TopN_Report_Same",m_formText.szSameSection);
			FindNodeValue(ResNode,"IDS_Delete_TopN_Report_Affirm",m_formText.szDelTopNAffirm);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",m_formText.szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",m_formText.szButMatch);
			FindNodeValue(ResNode,"IDS_Help",m_formText.szHelp);
			FindNodeValue(ResNode,"IDS_TopNReportListEmpty",m_formText.szListEmpty);
		}
		CloseResource(objRes);
	}
}

void CSVTopnReportSet::ShowSendForm()
{

}

/***********************************************
参数：

功能：
    选择所有的TOPN报告
***********************************************/
void CSVTopnReportSet::SelAll()
{
	for(m_pListItem = m_pListReport.begin();\
		m_pListItem != m_pListReport.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(true);
    }
}

/***********************************************
参数：

功能：
    新增TOPN报告
***********************************************/
void CSVTopnReportSet::AddPhone()
{
	//emit AddNewPhone() 信号
    emit AddNewPhone();
}

/*************************************************************
参数：
	str：编辑的报告名
功能：
	根据报告名编辑指定的报告
*************************************************************/
void CSVTopnReportSet::EditRow(const std::string str)
{
	chgstr = str;
	std::string ret = "error";
    SAVE_REPORT_LIST report;

	PrintDebugString(str.c_str());

	//报告名称
	report.szTitle = GetIniFileString(str, "Title", ret, "topnreportset.ini");
	if(strcmp(report.szTitle.c_str(), "error") == 0)
	{
		report.szTitle = "";
	}

	//报告描述
	report.szDescript = GetIniFileString(str, "Descript", ret, "topnreportset.ini");
	if(strcmp(report.szDescript.c_str(), "error") == 0)
	{
		report.szDescript = "";
	}

	//报告周期
	report.szPeriod = GetIniFileString(str, "Period", ret, "topnreportset.ini");
	if(strcmp(report.szPeriod.c_str(), "error") == 0)
	{
	}

	//发送EMAIL地址
	report.szEmailSend = GetIniFileString(str, "EmailSend", ret, "topnreportset.ini");
	if(strcmp(report.szEmailSend.c_str(), "error") == 0)
	{
		report.szEmailSend = "";
	}

	//禁止报告选项
	report.szDeny = GetIniFileString(str, "Deny", ret, "topnreportset.ini");
	if(strcmp(report.szDeny.c_str(), "error") == 0)
	{
	}

	//生成报告时间
	report.szGenerate = GetIniFileString(str, "Generate", ret, "topnreportset.ini");
	if(strcmp(report.szGenerate.c_str(), "error") == 0)
	{
	}

	//选择类型
	report.szSelType = GetIniFileString(str, "Type", ret, "topnreportset.ini");
	if(strcmp(report.szSelType.c_str(), "error") == 0)
	{
	}

	//选择指标
	report.szSelMark = GetIniFileString(str, "Mark", ret, "topnreportset.ini");
	if(strcmp(report.szSelMark.c_str(), "error") == 0)
	{
	}

	//排序方式
	report.szSelSort = GetIniFileString(str, "Sort", ret, "topnreportset.ini");
	if(strcmp(report.szSelSort.c_str(), "error") == 0)
	{
	}

	//图表显示数
	report.szCount = GetIniFileString(str, "Count", ret, "topnreportset.ini");
	if(strcmp(report.szCount.c_str(), "error") ==0)
	{
		report.szCount = "";
	}

	//报告权限
	report.szGroupRight= GetIniFileString(str, "GroupRight", ret, "topnreportset.ini");
	if(strcmp(report.szGroupRight.c_str(), "error") ==0)
	{
		
	}

	//任务计划
	report.szPlan = GetIniFileString(str, "Plan", ret, "topnreportset.ini");
	if(strcmp(report.szPlan.c_str(), "error") == 0)
	{
	}

	//取值方式
	report.szGetValue = GetIniFileString(str, "GetValue", ret, "topnreportset.ini");
	if(strcmp(report.szGetValue.c_str(), "error") == 0)
	{
	}

	//周报截止时间
	report.szWeekEnd = GetIniFileString(str, "WeekEndTime", ret, "topnreportset.ini");
	if(strcmp(report.szGetValue.c_str(), "error") == 0)
	{
	}

	//编辑报告以前的报告名称
	report.chgstr = str;
	//发送编辑报告信号
	emit EditPhone(report);
}

/*******************************************
参数：

功能：
    删除报告以前的操作
*******************************************/
void CSVTopnReportSet::BeforeDelPhone()
{
	for(m_pListItem = m_pListReport.begin();\
		m_pListItem != m_pListReport.end(); m_pListItem++)
	{       
		if (m_pListItem->pSelect->isChecked())
		{           
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + m_formText.szDelTopNAffirm + "','" + m_formText.szButNum + "','" + m_formText.szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;										
		}
	}
}

/*******************************************
参数：

功能：
    删除报告
*******************************************/
void CSVTopnReportSet::DelPhone()
{
	string strDeletePhone;
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
    {       
		//报告列表是否被选择
        if (m_pListItem->pSelect->isChecked())
        {           
			std::list<string> sectionlist;
			std::list<string>::iterator sectionitem;
			std::string temp = m_pListItem->pName->text();		
			int pos = temp.find(">", 0);
			int pos1 = temp.find("<", pos);
			temp = temp.substr(pos + 1, pos1 - pos - 1);			
			//从topnreportset.ini删除报告
			DeleteIniFileSection(temp, "topnreportset.ini");			
			
			//从topnreportgenerate.ini中删除报告关连项
			GetIniFileSections(sectionlist, "topnreportgenerate.ini");
			int num =2;
			for(sectionitem = sectionlist.begin(); sectionitem != sectionlist.end(); sectionitem++)
			{
				std::string tempsection = *sectionitem;
				
				pos = tempsection.find("$", 0);
				if(pos < 0)
				{
					continue;
				}

				std::string substr = tempsection.substr(0, pos);
				
				if(strcmp(substr.c_str(), temp.c_str()) == 0)
				{
					DeleteIniFileSection(tempsection, "topnreportgenerate.ini");
				}
			}
			

            int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();        
            list<REPORT_LIST>::iterator pItem = m_pListItem;                             
            m_pListItem --;        

			strDeletePhone += temp;
			strDeletePhone += "  ";

			//删除m_pListReport中对应的项
            m_pListReport.erase(pItem);  
			//删除列表中的行
            m_pReportListTable->GeDataTable()->deleteRow(nRow); 						
        }
    }

	////如果列表为空， 则显示提示信息
	//if(m_pListReport.size() == 0)
	//{
	//	WText * nText = new WText(m_formText.szListEmpty,\
	//		(WContainerWidget*)nullTable -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}
	
		if(m_pListReport.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
		}
		else
		{
			m_pReportListTable->HideNullTip();
		}

	//插记录到UserOperateLog表
	string strUserID = GetWebUserID();
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_formText.szTipDel,m_formText.szTitle,strDeletePhone);

}

/******************************************************************
参数：
	report： 保存TOPN报告的SAVE_REPORT_LIST结构

功能：
    根据保存结构中的报告名保存TOPN报告
******************************************************************/
void CSVTopnReportSet::SaveTopnReport(SAVE_REPORT_LIST * report)
{    
	////清除列表为空的提示信息
	//nullTable -> clear();
	
	//如果编辑报告名称不为空则编辑
	if(strcmp(chgstr.c_str(), "") != 0)
    {
        Edit_Phone(report);
        return;
    }	
    
	//judge report name/(ini section) is right
	//取报告权限
	std::list<string> sectionlist;
	std::list<string>::iterator Item;
	GetIniFileSections(sectionlist, "topnreportset.ini");
	//取列表行数
	int numRow = m_pReportListTable->GeDataTable()->numRows();
	m_pReportListTable->InitRow(numRow);
	//是否选择检查框
	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
	m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignTop | AlignCenter);
	//构造HREF链接字符串
	std::string strlinkname;		
	std::string hrefstr = RepHrefStr(report->szTitle);
	strlinkname = "<a href=/fcgi-bin/topnreportlist.exe?id="+hrefstr+">"+report->szTitle+"</a>";
	
	//报告名称
	WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));	
	m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignTop | AlignCenter);

	//报告周期
	WText *pPeriod = new WText(report->szPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
	m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignTop | AlignCenter);

	//编辑按钮
	WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 6));
	m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignTop | AlignCenter);
	pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   

	//列表样式
	//Jansion.zhou 2006-12-26
	//m_pReportListTable->GeDataTable()->adjustRowStyle("tr1","tr2"); 

	//编辑按钮MAP字符串（报告名）
	m_signalMapper.setMapping(pEdit, report->szTitle);
	
	//写INI文件返回值
	bool isWriteIni = false;

	//报告名称
	isWriteIni = WriteIniFileString(report->szTitle, "Title", report->szTitle, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//报告描述
	isWriteIni = WriteIniFileString(report->szTitle, "Descript", report->szDescript, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//报告周期
	isWriteIni = WriteIniFileString(report->szTitle, "Period", report->szPeriod, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//EMAIL发送地址
	isWriteIni = WriteIniFileString(report->szTitle, "EmailSend", report->szEmailSend, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//报告禁止选项
	isWriteIni = WriteIniFileString(report->szTitle, "Deny", report->szDeny, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//报告生成时间
	isWriteIni = WriteIniFileString(report->szTitle, "Generate", report->szGenerate, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//选择类型
	isWriteIni = WriteIniFileString(report->szTitle, "Type", report->szSelType, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//选择指标
	isWriteIni = WriteIniFileString(report->szTitle, "Mark", report->szSelMark, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//排序方式
	isWriteIni = WriteIniFileString(report->szTitle, "Sort", report->szSelSort, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//图表显示数
	isWriteIni = WriteIniFileString(report->szTitle, "Count", report->szCount, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//报告权限
	isWriteIni = WriteIniFileString(report->szTitle, "GroupRight", report->szGroupRight, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//任务计划
	isWriteIni = WriteIniFileString(report->szTitle, "Plan", report->szPlan, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//取值方式
	isWriteIni = WriteIniFileString(report->szTitle, "GetValue", report->szGetValue, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//周报截止时间
	isWriteIni = WriteIniFileString(report->szTitle, "WeekEndTime", report->szWeekEnd, "topnreportset.ini");
	if(!isWriteIni)
	{
	}
		

	m_pReportListTable->HideNullTip();

	
	//TOPNREPORT_LIST list;
	REPORT_LIST list;

	list.pSelect = pCheck;
	list.pName = pName;
	list.pPeriod = pPeriod;
	list.pEdit = pEdit;
	//REPORT结构PUSHBACK到LIST
	m_pListReport.push_back(list);
	//关连MAP（）事件
	connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
}

/***************************************************************
参数：
	report： 报告编辑结构

功能：
    根据结构中的报告名称编辑报告
***************************************************************/
void CSVTopnReportSet::Edit_Phone(SAVE_REPORT_LIST * report)
{
	bool isWriteIni = false;

	//编辑报告名称， 用新的报告名称(report->szTitle)更新原报告名(chgstr)
	isWriteIni = EditIniFileSection(chgstr, report->szTitle, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告名称到INI文件
	isWriteIni = WriteIniFileString(report->szTitle, "Title", report->szTitle, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告描述到INI文件
	isWriteIni = WriteIniFileString(report->szTitle, "Descript", report->szDescript, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告周期到INI文件
	isWriteIni = WriteIniFileString(report->szTitle, "Period", report->szPeriod, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写EMAIL发送地址
	isWriteIni = WriteIniFileString(report->szTitle, "EmailSend", report->szEmailSend, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写是否禁止报告选项
	isWriteIni = WriteIniFileString(report->szTitle, "Deny", report->szDeny, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告生成时间
	isWriteIni = WriteIniFileString(report->szTitle, "Generate", report->szGenerate, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告选择类型
	isWriteIni = WriteIniFileString(report->szTitle, "Type", report->szSelType, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告选择指标
	isWriteIni = WriteIniFileString(report->szTitle, "Mark", report->szSelMark, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告排序方式
	isWriteIni = WriteIniFileString(report->szTitle, "Sort", report->szSelSort, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告图形显示数
	isWriteIni = WriteIniFileString(report->szTitle, "Count", report->szCount, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告权限
	isWriteIni = WriteIniFileString(report->szTitle, "GroupRight", report->szGroupRight, "topnreportset.ini");

	if(!isWriteIni)
	{
	}

	//写报告计划
	isWriteIni = WriteIniFileString(report->szTitle, "Plan", report->szPlan, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写报告取值方式
	isWriteIni = WriteIniFileString(report->szTitle, "GetValue", report->szGetValue, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//写周报告截止时间
	isWriteIni = WriteIniFileString(report->szTitle, "WeekEndTime", report->szWeekEnd, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
	{
		//在报告LIST中根据原报告名称查找编辑报告
		if(strcmp(chgstr.c_str(), m_pListItem->pName->text().c_str()) == 0)
		{
			//用新的报告名称重新映射编辑
			m_pListItem->pName->setText(report->szTitle);
			m_pListItem->pPeriod->setText(report->szPeriod);
			m_signalMapper.setMapping(m_pListItem->pEdit, report->szTitle);
			break;
		}
	}

	//存储原报告名称变量重新初始化为空
	chgstr = "";
}

/*****************************************
未使用函数
*****************************************/
void CSVTopnReportSet::showSmsList()
{
	pShow -> show();
	pHide -> hide();
	table -> show();
}

/****************************************
未使用函数
****************************************/
void CSVTopnReportSet::hideSmsList()
{
	pShow -> hide();
	pHide -> show();
	table -> hide();
}

/****************************************
未使用函数
****************************************/
void CSVTopnReportSet::showSmsList1()
{
	pShow1 -> show();
	pHide1 -> hide();
	table1 -> show();
}

/****************************************
未使用函数
****************************************/
void CSVTopnReportSet::hideSmsList1()
{
	pShow1 -> hide();
	pHide1 -> show();
	table1 -> hide();
}

/********************************************
参数：

功能：
    显示报告列表
********************************************/
void CSVTopnReportSet::showSmsList2()
{
	pShow2 -> show();
	pHide2 -> hide();
	table2 -> show();	
}

/********************************************
参数：

功能：
    隐藏报告列表
********************************************/
void CSVTopnReportSet::hideSmsList2()
{	
	pShow2 -> hide();
	pHide2 -> show();
	table2 -> hide();
}

/***********************************************************
参数：
	pTable： 操作按钮上一级表格

功能：
	增加操作按钮
***********************************************************/
void CSVTopnReportSet::AddGroupOperate(WTable * pTable)
{
    m_pGroupOperate = new WTable((WContainerWidget *)pTable->elementAt( 8, 0));
    if ( m_pGroupOperate )
    {
        WImage * pSelAll = new WImage("../icons/selall.gif", \
			(WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
        if (pSelAll)
        {
            pSelAll->setStyleClass("imgbutton");
			pSelAll->setToolTip(m_formText.szTipSelAll1);
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

        WImage * pSelNone = new WImage("../icons/selnone.gif",\
			(WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
        if (pSelAll)
        {
            pSelNone->setStyleClass("imgbutton");
			pSelNone->setToolTip(m_formText.szTipSelNone);
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

        WImage * pSelinvert = new WImage("../icons/selinvert.gif", \
			(WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
        if (pSelinvert)
        {
            pSelinvert->setStyleClass("imgbutton");
			pSelinvert->setToolTip(m_formText.szTipSelInv);
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		WImage * pDel = new WImage("../icons/del.gif", \
			(WContainerWidget *)m_pGroupOperate->elementAt(0, 4));
        if (pDel)
        {
           
			pDel->setStyleClass("imgbutton");
			pDel->setToolTip(m_formText.szTipDel);
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
        }

		WPushButton *pAdd = new WPushButton(m_formText.szAddPhoneBut, \
			(WContainerWidget *)m_pGroupOperate->elementAt(0, 6));
        if (pAdd)
        {
            pAdd->setToolTip(m_formText.szTipAddNew);
			pAdd->setStyleClass("wizardbutton");
            WObject::connect(pAdd, SIGNAL(clicked()), "showbar();", this, SLOT(AddPhone()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
			//connect(pEdit, SIGNAL(clicked()), "showbar();",&m_signalMapper, SLOT(map()),WObject::ConnectionType::JAVASCRIPTDYNAMIC );
        }
		
		m_pGroupOperate->elementAt(0, 6)->resize(WLength(100,WLength::Percentage),\
			WLength(100,WLength::Percentage));
		m_pGroupOperate->elementAt(0, 6)->setContentAlignment(AlignRight);
   }

	//隐藏按钮
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelPhone()));
		pHideBut->hide();
	}
}

/*********************************************
参数：

功能：
	取消所有选择	
*********************************************/
void CSVTopnReportSet::SelNone()
{
	for(m_pListItem = m_pListReport.begin(); \
		m_pListItem != m_pListReport.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(false);
    }
}

/************************************************
参数：

功能：
    反选所有选择项
************************************************/
void CSVTopnReportSet::SelInvert()
{
	for(m_pListItem = m_pListReport.begin();\
		m_pListItem != m_pListReport.end(); m_pListItem ++)
    {
		if(m_pListItem->pSelect->isChecked())
		{
			m_pListItem->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem->pSelect->setChecked(true);
		}
    }
}

void CSVTopnReportSet::MainHelp()
{	
}

/**************************************
参数：

功能：
    刷新报告
**************************************/
void CSVTopnReportSet::refresh()
{
	//nullTable -> clear();

	UpdatePhoneList();

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}
}

/******************************************
参数:

功能:
    更新报告列表
******************************************/
void CSVTopnReportSet::UpdatePhoneList()
{
	////删除报告列表项
	//int nNum =m_pReportListTable->GeDataTable()->numRows();
	//for(int i=1;i<nNum;i++)
	//{
	//	m_pReportListTable->GeDataTable()->deleteRow(1);
	//}

	m_pReportListTable->GeDataTable()->clear();

	//清楚报告LIST
	m_pListReport.clear();

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	
	bool IsConn = GetIniFileSections(sectionlist, "topnreportset.ini");
	
	if(!IsConn)
	{
		//连接SVDB失败
		m_pConnErr ->setText(m_formText.szConnErr);
		m_pConnErr ->show();
	}
	else
	{
		m_pConnErr ->hide();
	}

	////报告节名为空则显示提示信息
	//if(sectionlist.size() == 0)
	//{
	//	WText * nText = new WText(m_formText.szListEmpty, \
	//		(WContainerWidget*)nullTable -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}

	int numRow = 1;
	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		std::string section = *m_sItem;

		std::list<string> keylist;
		std::list<string>::iterator m_pItem;
		
		bool bRet = false;
		//取报告名称下所有生成报告
		bRet = GetIniFileKeys(section,keylist, "topnreportset.ini" );
		if(!bRet)
		{
		}

		m_pItem = keylist.begin();

		std::string str = *m_pItem;
		std::string ret = "error";
		//int numRow = m_pReportListTable->GeDataTable()->numRows();

		REPORT_LIST list;
		
		// 是否选择
		numRow = m_pReportListTable->GeDataTable()->numRows();
		m_pReportListTable->InitRow(numRow);

		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));		
		m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignTop | AlignCenter);

		// 名称
		std::string ReportName = GetIniFileString(section, "Title", ret, "topnreportset.ini");
		if(strcmp(ReportName.c_str(), "error") == 0)
		{
		}
		std::string strlinkname;//报告链接名称
		std::string hrefstr = RepHrefStr(section);
		strlinkname = "<a href=/fcgi-bin/topnreportlist.exe?id="+hrefstr+">"+ReportName+"</a>";
		WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignTop | AlignCenter);
		std::string ReportPeriod = GetIniFileString(section, "Period", ret, "topnreportset.ini");
		if(strcmp(ReportPeriod.c_str(), "error") == 0)
		{
		}
		WText *pPeriod = new WText(ReportPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignTop | AlignCenter);

		WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow ,6));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignTop | AlignCenter);
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));

		//用报告名称MAP编辑
		m_signalMapper.setMapping(pEdit, section);

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		m_pListReport.push_back(list);		
		numRow++;
	}



	//m_pReportListTable->GeDataTable()->adjustRowStyle("tr1","tr2");	
}


