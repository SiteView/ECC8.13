#include "configpage.h"

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

#include "../svtable/MainTable.h"

#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"

#include "svapi.h"
#include "websession.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

#include <windows.h>
extern void PrintDebugString(const char *szErrmsg);
extern unsigned int RandIndex();

//////////////////////////////////////////////////////////////////////////////////
//
string& replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

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

bool GetUserRight(string strRight)
{
	bool bRight = false;
	string strSection = GetWebUserID();
	
	//管理员则有所有权限
	if(GetIniFileInt(strSection, "nAdmin", -1, "user.ini") != -1)
		return true;

	if(GetIniFileInt(strSection, strRight, 0, "user.ini") == 1)
		bRight = true;
	else
		bRight = false;
	return bRight;
	//return true;
}

CSVReportSet::CSVReportSet(WContainerWidget * parent):
WContainerWidget(parent)
{
	IsShow = true;
	chgstr = ""; 
	loadString();
    initForm();

	PrintDebugString("Init ReportSet Finish\n");
}

//添加客户端脚本变量
void CSVReportSet::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CSVReportSet::initForm()
{

	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>",this);


	m_pMainTable = new WSVMainTable(this,m_formText.szMainTitle,false);

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
	connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));

	if (m_pReportListTable->GetActionTable() != NULL)
	{
		
		m_pReportListTable->SetNullTipInfo(szListEmpty);

		if(m_pListReport.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
		}
		else
		{
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

		if(!GetUserRight("m_reportlistDel"))
			m_pDel->hide();
		else
			m_pDel->show();

		if (m_pDel)
		{
			m_pDel->setToolTip(m_formText.szTipDel);
			connect(m_pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
		}

		m_pReportListTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		m_pAdd = new WSVButton(m_pReportListTable->GetActionTable()->elementAt(0,2),m_formText.szAddPhoneBut, "button_bg_add_black.png", m_formText.szTipAddNew, true);
		if(!GetUserRight("m_reportlistAdd"))
			m_pAdd->hide();
		else
			m_pAdd->show();

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








//	new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
////	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>", this);
//	//CMainTable * T1table = new CMainTable(this ,"统计报告");
//		
//	WTable* T1table = new WTable(this);
//	T1table->setStyleClass("t1");
//	new WText(m_formText.szMainTitle, T1table->elementAt(0,0));
//	T1table->elementAt(0,0)->setStyleClass("t1title");
//	
//
//	WTable * TitleTable = new WTable(T1table->elementAt(1,0));
//
//	TitleTable->setStyleClass("t3");
		



	//Jansion.zhou 2006-12-25
	m_pConnErr = new WText("", (WContainerWidget *)this);
	m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	m_pConnErr ->hide();



	//if(m_pReportListTable->GetContentTable() != NULL)
	//{
	//	m_pReportListTable->AppendRows("");
	//	//int NowRows = m_pReportListTable->GeDataTable()->numRows();
	//	m_pConnErr = new WText("", m_pReportListTable->AppendRowsContent(0, "","",m_formText.szConnErr));
	//	m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	//}

	
	//测试连接SVDB
	std::list<string> sectionlist;
	bool IsConn = GetIniFileSections(sectionlist, "smsconfig.ini");
	if(!IsConn)
	{
		//连接SVDB失败
		m_pConnErr ->setText(m_formText.szConnErr);
		m_pConnErr ->show();
	}





	pTranslateBtn = new WPushButton(strTranslate, this);
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	pExChangeBtn = new WPushButton(strRefresh, this);
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
	//m_pHelpImg -> hide();
	//m_pHelpImg ->setStyleClass("helpimg");
	//TitleTable->elementAt(0, 1) -> setContentAlignment(AlignTop | AlignRight);
	//WObject::connect(m_pHelpImg, SIGNAL(clicked()), this, SLOT(MainHelp()));

	//

	////接受列表
	////WTable * m_pListGeneral = new WTable(this);
	//WTable * m_pListGeneral = new WTable(T1table->elementAt(2,0));
	//
	//m_pListGeneral ->setStyleClass("t2");
	//
	////接受列表收/放显示栏
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

	//table2 = new WTable((WContainerWidget *)m_pListGeneral->elementAt(1,0));
	////table2 -> setStyleClass("bg_Border");
	//table2 ->setStyleClass("t3");

	//PrintDebugString("Init Old Table\n");

 //   if ( table2 )
 //   {
 //       addPhoneList(table2);
	//	connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));

	//	PrintDebugString("Init Old Table2\n");

	//	//AddGroupOperate(table2);
	//}
		
	new WText("</div>", this);

	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

}

void CSVReportSet::ExChange()
{
	PrintDebugString("------ExChangeEvent------\n");
	emit ExChangeEvent();
}
void CSVReportSet::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "reportsetRes";
	WebSession::js_af_up += "')";
}

void CSVReportSet::addPhoneListNew()
{

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	GetIniFileSections(sectionlist, "reportset.ini");

	int numRow = 1;
	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		m_pReportListTable->InitRow(numRow);

		std::string section = *m_sItem;

		string ret = "error";

		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);
		// 名称
		std::string strlinkname;
		std::string hrefstr = RepHrefStr(section);
		strlinkname ="<a href=/fcgi-bin/startsreportlist.exe?id="+hrefstr+">"+section+"</a>";
		WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);

		std::string szPeriod = GetIniFileString(section, "Period", ret, "reportset.ini");
		if(strcmp(szPeriod.c_str(), "error") == 0)
		{
		}

		WText *pPeriod = new WText(szPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);

		WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow ,6));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);
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

//add  list function
void CSVReportSet::addPhoneList(WTable * table)
{
    m_ptbPhone = new WTable((WContainerWidget*)table->elementAt(7,0));
	nullTable = new WTable((WContainerWidget*)table->elementAt(8, 0));

	m_ptbPhone -> setStyleClass("t3");
	nullTable -> setStyleClass("t3");

    if (m_ptbPhone)
    {
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

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	GetIniFileSections(sectionlist, "reportset.ini");

	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		int numRow = m_ptbPhone->numRows();
		std::string section = *m_sItem;

		string ret = "error";

		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_ptbPhone->elementAt(numRow, 0));
		// 名称
		std::string strlinkname;
		std::string hrefstr = RepHrefStr(section);
		strlinkname ="<a href=/fcgi-bin/startsreportlist.exe?id="+hrefstr+">"+section+"</a>";
		WText *pName = new WText(strlinkname, (WContainerWidget*)m_ptbPhone->elementAt(numRow , 1));

		std::string szPeriod = GetIniFileString(section, "Period", ret, "reportset.ini");
		if(strcmp(szPeriod.c_str(), "error") == 0)
		{
		}
		
		WText *pPeriod = new WText(szPeriod, (WContainerWidget*)m_ptbPhone->elementAt(numRow, 2));
		
		WImage *pEdit = new WImage("../icons/edit.gif", (WContainerWidget*)m_ptbPhone->elementAt(numRow ,3));
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
		m_signalMapper.setMapping(pEdit, section);

		REPORT_LIST list;

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		m_pListReport.push_back(list);
		
	}
	m_ptbPhone->adjustRowStyle("tr1","tr2");
	

	//m_pReportListTable->HideNullTip();
		
}

void CSVReportSet::showErrMsg(string &strErrMsg)
{
    if ( m_pErrMsg )
    {
        m_pErrMsg->setText(strErrMsg);
        m_pErrMsg->show();
    }
}

void CSVReportSet::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szMainTitle);
			FindNodeValue(ResNode,"IDS_Report_Config",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Save",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_ReportList",m_formText.szTBTitle);
			FindNodeValue(ResNode,"IDS_State",m_formText.szColSelAll);
			FindNodeValue(ResNode,"IDS_Title",m_formText.szColName);
			FindNodeValue(ResNode,"IDS_State",m_formText.szColState);
			FindNodeValue(ResNode,"IDS_Edit",m_formText.szColEdit);
			FindNodeValue(ResNode,"IDS_Time_Period",m_formText.szColPeriod);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Enable",m_formText.szEnable);
			FindNodeValue(ResNode,"IDS_All_Select_Other",m_formText.szTipSelAll);
			FindNodeValue(ResNode,"IDS_Report_Add",m_formText.szAddPhoneBut);
			FindNodeValue(ResNode,"IDS_Connect_SVDB_Fail",m_formText.szConnErr);
			FindNodeValue(ResNode,"IDS_All_Select",m_formText.szTipSelAll1);
			FindNodeValue(ResNode,"IDS_None_Select",m_formText.szTipSelNone);
			FindNodeValue(ResNode,"IDS_Invert_Select",m_formText.szTipSelInv);
			FindNodeValue(ResNode,"IDS_Add",m_formText.szTipAddNew);
			FindNodeValue(ResNode,"IDS_Delete",m_formText.szTipDel);
			FindNodeValue(ResNode,"IDS_TopN_Report_Same",m_formText.szSameSection);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_DeleteSMSAffirmInfo",m_formText.szDeleteSMSAffirm);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",m_formText.szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",m_formText.szButMatch);
			FindNodeValue(ResNode,"IDS_TotalReportEmpty",szListEmpty);
		}
		CloseResource(objRes);
	}
	//szListEmpty = "[----------统计报告列表为空-----------]";
/*
	m_formText.szMainTitle="统计报告";
    m_formText.szTitle = "报告设置";
    m_formText.szSave = "保存";
    m_formText.szTBTitle = "报告列表";
    m_formText.szColSelAll = "状态";
    m_formText.szColName = "标题";
    m_formText.szColState = "状态";
	m_formText.szColEdit = "编辑";
	m_formText.szColPeriod = "时间周期";
    m_formText.szDisable = "禁止";
    m_formText.szEnable = "允许";
    m_formText.szTipSelAll = "全选或者取消全选";
	m_formText.szAddPhoneBut = "添加报告";
	m_formText.szConnErr = "连接SVDB失败";
	m_formText.szTipSelAll1 = "全选";
	m_formText.szTipSelNone = "全不选";
	m_formText.szTipSelInv = "反选";
	m_formText.szTipAddNew = "添加";
	m_formText.szTipDel = "删除";
	m_formText.szSameSection = "有相同的TOPN报告";*/
}

void CSVReportSet::ShowSendForm()
{

}

void CSVReportSet::SaveConfig()
{
 
}

void CSVReportSet::SaveConfig1()
{

}

void CSVReportSet::SelAll()
{
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(true);
    }
}

void CSVReportSet::AddPhone()
{
	OutputDebugString("\naaa\n");
    emit AddNewPhone();
}

void CSVReportSet::EditRow(const std::string str)
{
	PrintDebugString("Begin EditRow\n");

	chgstr = str;
	std::string ret = "error";
    SAVE_REPORT_LIST report;

	report.szTitle = GetIniFileString(str, "Title", ret, "reportset.ini");
	if(strcmp(report.szTitle.c_str(), "error") == 0)
	{
		report.szTitle = "";
	}

	report.szDescript = GetIniFileString(str, "Descript", ret, "reportset.ini");
	if(strcmp(report.szDescript.c_str(), "error") == 0)
	{
		report.szDescript = "";
	}

	report.szPlan = GetIniFileString(str, "Plan", ret, "reportset.ini");
	if(strcmp(report.szPlan.c_str(), "error") == 0)
	{
	}

	report.szPeriod = GetIniFileString(str, "Period", ret, "reportset.ini");
	if(strcmp(report.szPeriod.c_str(), "error") == 0)
	{
	}

	report.szStatusresult = GetIniFileString(str, "StatusResult", ret, "reportset.ini");
	if(strcmp(report.szStatusresult.c_str(), "error") == 0)
	{
	}

	report.szErrorresult = GetIniFileString(str, "ErrorResult", ret, "reportset.ini");
	if(strcmp(report.szErrorresult.c_str(), "error") == 0)
	{
	}

	report.szGraphic = GetIniFileString(str, "Graphic", ret, "reportset.ini");
	if(strcmp(report.szGraphic.c_str(), "error") == 0)
	{
	}

	report.szComboGraphic = GetIniFileString(str, "ComboGraphic", ret, "reportset.ini");
	if(strcmp(report.szComboGraphic.c_str(), "error") == 0)
	{
	}

	report.szListData = GetIniFileString(str, "ListData", ret, "reportset.ini");
	if(strcmp(report.szListData.c_str(), "error") == 0)
	{
	}

	report.szListNormal = GetIniFileString(str, "ListNormal", ret, "reportset.ini");
	if(strcmp(report.szListNormal.c_str(), "error") == 0)
	{
	}

	report.szListError = GetIniFileString(str, "ListError", ret, "reportset.ini");
	if(strcmp(report.szListError.c_str(), "error") == 0)
	{
	}

	report.szListDanger = GetIniFileString(str, "ListDanger", ret, "reportset.ini");
	if(strcmp(report.szListDanger.c_str(), "error") == 0)
	{
	}

	report.szListAlert = GetIniFileString(str, "ListAlert", ret, "reportset.ini");
	if(strcmp(report.szListAlert.c_str(), "error") == 0)
	{
	}

	report.szEmailSend = GetIniFileString(str, "EmailSend", ret, "reportset.ini");
	if(strcmp(report.szEmailSend.c_str(), "error") == 0)
	{
		report.szEmailSend = "";
	}

	report.szParameter = GetIniFileString(str, "Parameter", ret, "reportset.ini");
	if(strcmp(report.szParameter.c_str(), "error") == 0)
	{
	}

	report.szDeny = GetIniFileString(str, "Deny", ret, "reportset.ini");
	if(strcmp(report.szDeny.c_str(), "error") == 0)
	{
	}

	report.szGenerate = GetIniFileString(str, "Generate", ret, "reportset.ini");
	if(strcmp(report.szGenerate.c_str(), "error") == 0)
	{
	}

	report.szClicketValue = GetIniFileString(str, "ClicketValue", ret, "reportset.ini");
	if(strcmp(report.szClicketValue.c_str(), "error") == 0)
	{
		report.szClicketValue = "";
	}

	report.szListClicket = GetIniFileString(str, "ListClicket", ret, "reportset.ini");
	if(strcmp(report.szListClicket.c_str(), "error") == 0)
	{
		
	}

	report.szStartTime = GetIniFileString(str, "StartTime", ret, "reportset.ini");
	if(strcmp(report.szStartTime.c_str(), "error") == 0)
	{
		report.szStartTime = "";
	}

	report.szEndTime = GetIniFileString(str, "EndTime", ret, "reportset.ini");
	if(strcmp(report.szEndTime.c_str(), "error") == 0)
	{
		report.szEndTime = "";
	}
	report.nWeekEndIndex = GetIniFileInt(str,"WeekEndTime",0,"reportset.ini");
	//Ticket #123  start   -------苏合
	report.szExcel = GetIniFileString(str, "GenExcel", ret, "reportset.ini");
	if(strcmp(report.szExcel.c_str(), "error") == 0)
	{
		report.szExcel = "";
	}
  //Ticket #123   end    -------苏合


	report.szGroupRight= GetIniFileString(str, "GroupRight", ret, "reportset.ini");
	char abc[2000];
	sprintf(abc,"\n%s-------%s\n",str.c_str(),report.szGroupRight.c_str());
	OutputDebugString(abc);
	if(strcmp(report.szGroupRight.c_str(), "error") == 0)
	{
	}
	report.chgstr = str;

	emit EditPhone(report);
}

void CSVReportSet::BeforeDelPhone()
{
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
	{
		if (m_pListItem->pSelect->isChecked())
		{   
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + m_formText.szDeleteSMSAffirm + "','" + m_formText.szButNum + "','" + m_formText.szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;	
		}
	}
}

void CSVReportSet::DelPhone()
{
	string strDeletePhone;
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
    {
        
        if (m_pListItem->pSelect->isChecked())
        {   
        
			std::string temp = m_pListItem->pName->text();
			
			int pos = temp.find(">", 0);
			int pos1 = temp.find("<", pos);
			temp = temp.substr(pos + 1, pos1 - pos - 1);

			DeleteIniFileSection(temp, "reportset.ini");

            int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();
        
            list<REPORT_LIST>::iterator pItem = m_pListItem;                     
        
            m_pListItem --;
        
 			strDeletePhone += temp;
			strDeletePhone += "  ";

			m_pListReport.erase(pItem);          
        
			//jansion.zhou 2006-12-18
            //m_ptbPhone->deleteRow(nRow);
			m_pReportListTable->GeDataTable()->deleteRow(nRow);

			std::list<string> sectionlist;
			std::list<string>::iterator sectionitem;

			GetIniFileSections(sectionlist, "reportgenerate.ini");

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
					DeleteIniFileSection(tempsection, "reportgenerate.ini");
				}
			}
        }
    }


	
		if(m_pListReport.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
		}
		else
		{
			m_pReportListTable->HideNullTip();
		}

	//if(m_pListReport.size() == 0)
	//{
	//	WText * nText = new WText("[----------统计报告列表为空-----------]", (WContainerWidget*)nullTable -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}

	//插记录到UserOperateLog表
	string strUserID = GetWebUserID();
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_formText.szTipDel,m_formText.szMainTitle,strDeletePhone);

}

void CSVReportSet::SavePhone(SAVE_REPORT_LIST * report)
{
    //nullTable -> clear();

	if(strcmp(chgstr.c_str(), "") != 0)
    {
        Edit_Phone(report);
        return;
    }
    
	//judge report name/(ini section) is right
	
	std::list<string> sectionlist;
	std::list<string>::iterator Item;
	GetIniFileSections(sectionlist, "reportset.ini");
	bool bRe = false;

	for(Item = sectionlist.begin(); Item != sectionlist.end(); Item++)
	{
		std::string str = *Item;
		if(strcmp(str.c_str(), report->szTitle.c_str()) == 0)
		{
			bRe = true;
			break;
		}
	}

	if(bRe)//有重复
	{

		std::list<string> errorMsgList;
		errorMsgList.push_back(m_formText.szConnErr);
		m_pReportListTable->ShowErrorMsg(errorMsgList);		//show error msg


		//m_pConnErr ->setText(m_formText.szConnErr);
		//m_pConnErr ->show();	
	}
	else
	{
		//int numRow = m_ptbPhone->numRows();
		int numRow = m_pReportListTable->GeDataTable()->numRows();
		m_pReportListTable->InitRow(numRow);
		    
		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);
	    
		std::string strlinkname;

		std::string hrefstr =  RepHrefStr(report->szTitle);
		strlinkname ="<a href=/fcgi-bin/statsreportlist.exe?id="+hrefstr+">"+report->szTitle+"</a>";

		WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
	    
		WText *pPeriod = new WText(report->szPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);

		WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 6));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	    
		//m_ptbPhone->adjustRowStyle("tr1","tr2"); 

		m_signalMapper.setMapping(pEdit, report->szTitle);
	  
		bool isWriteIni = false;

		isWriteIni = WriteIniFileString(report->szTitle, "Title", report->szTitle, "reportset.ini");
		if(!isWriteIni)
		{

		}
		isWriteIni = WriteIniFileString(report->szTitle, "Descript", report->szDescript, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "Plan", report->szPlan, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "Period", report->szPeriod, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "StatusResult", report->szStatusresult, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ErrorResult", report->szErrorresult, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "Graphic", report->szGraphic, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ComboGraphic", report->szComboGraphic, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ListData", report->szListData, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ListNormal", report->szListNormal, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ListError", report->szListError, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ListDanger", report->szListDanger, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ListAlert", report->szListAlert, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "EmailSend", report->szEmailSend, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "Parameter", report->szParameter, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "Deny", report->szDeny, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "Generate", report->szGenerate, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ClicketValue", report->szClicketValue, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "ListClicket", report->szListClicket, "reportset.ini");
		if(!isWriteIni)
		{
		}
		isWriteIni = WriteIniFileString(report->szTitle, "GroupRight", report->szGroupRight, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "StartTime", report->szStartTime, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileString(report->szTitle, "EndTime", report->szEndTime, "reportset.ini");
		if(!isWriteIni)
		{
		}

		isWriteIni = WriteIniFileInt(report->szTitle, "WeekEndTime", report->nWeekEndIndex, "reportset.ini");
		if(!isWriteIni)
		{
		}
		//Ticket #123  start   -------苏合
		isWriteIni = WriteIniFileString(report->szTitle, "GenExcel", report->szExcel, "reportset.ini");
		if(!isWriteIni)
		{
		}
		//Ticket #123   end    -------苏合
		

		m_pReportListTable->HideNullTip();
		
		//REPORT_LIST list;
		REPORT_LIST list;

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		m_pListReport.push_back(list);
		chgstr = "";
		connect(pEdit, SIGNAL(clicked()), "showbar();",&m_signalMapper, SLOT(map()),WObject::ConnectionType::JAVASCRIPTDYNAMIC );
	}
	
}

void CSVReportSet::Edit_Phone(SAVE_REPORT_LIST * report)
{
	bool isWriteIni = false;

	isWriteIni = EditIniFileSection(chgstr, report->szTitle, "reportset.ini");
	if(!isWriteIni)
	{
	}

	std::list<string> sectionlist;
	std::list<string>::iterator sectionitem;
	GetIniFileSections(sectionlist, "reportgenerate.ini");

	int num =2;
	for(sectionitem = sectionlist.begin(); sectionitem != sectionlist.end(); sectionitem++)
	{
		std::string tempsection = *sectionitem;
		
		int pos = tempsection.find("$", 0);
		if(pos < 0)
		{
			continue;
		}

		std::string substr = tempsection.substr(0, pos);
		std::string rightstr = tempsection.substr(pos, tempsection.size() - pos);
		
		if(strcmp(substr.c_str(), chgstr.c_str()) == 0)
		{
			//bool EditIniFileSection(string oldsection,string newsection,string filename,string addr="localhost");
			std::string nsec = report->szTitle;
			nsec += rightstr;

			EditIniFileSection(tempsection, nsec, "reportgenerate.ini");
		}
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Title", report->szTitle, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Descript", report->szDescript, "reportset.ini");
	if(!isWriteIni)
	{
	}


	isWriteIni = WriteIniFileString(report->szTitle, "Plan", report->szPlan, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Period", report->szPeriod, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "StatusResult", report->szStatusresult, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ErrorResult", report->szErrorresult, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Graphic", report->szGraphic, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ComboGraphic", report->szComboGraphic, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ListData", report->szListData, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ListNormal", report->szListNormal, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ListError", report->szListError, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ListDanger", report->szListDanger, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ListAlert", report->szListAlert, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "EmailSend", report->szEmailSend, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Parameter", report->szParameter, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Deny", report->szDeny, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "Generate", report->szGenerate, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ClicketValue", report->szClicketValue, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "ListClicket", report->szListClicket, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "GroupRight", report->szGroupRight, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileString(report->szTitle, "StartTime", report->szStartTime, "reportset.ini");
	if(!isWriteIni)
	{

	}

	isWriteIni = WriteIniFileString(report->szTitle, "EndTime", report->szEndTime, "reportset.ini");
	if(!isWriteIni)
	{
	}

	isWriteIni = WriteIniFileInt(report->szTitle, "WeekEndTime", report->nWeekEndIndex, "reportset.ini");
	if(!isWriteIni)
	{
	}

	//Ticket #123  start   -------苏合
	isWriteIni = WriteIniFileString(report->szTitle, "GenExcel", report->szExcel, "reportset.ini");
	if(!isWriteIni)
	{
	}
    //Ticket #123   end    -------苏合
	


	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
	{
		if(strcmp(chgstr.c_str(), m_pListItem->pName->text().c_str()) == 0)
		{
			m_pListItem->pName->setText(report->szTitle);
			m_pListItem->pPeriod->setText(report->szPeriod);
			m_signalMapper.setMapping(m_pListItem->pEdit, report->szTitle);
			break;
		}
	}
	UpdatePhoneList();
	chgstr = "";
}

void CSVReportSet::showSmsList()
{
	pShow -> show();
	pHide -> hide();
	table -> show();
}

void CSVReportSet::hideSmsList()
{
	pShow -> hide();
	pHide -> show();
	table -> hide();
}

void CSVReportSet::showSmsList1()
{
	pShow1 -> show();
	pHide1 -> hide();
	table1 -> show();
}

void CSVReportSet::hideSmsList1()
{
	pShow1 -> hide();
	pHide1 -> show();
	table1 -> hide();
}

void CSVReportSet::showSmsList2()
{
	
	pShow2 -> show();
	pHide2 -> hide();
	table2 -> show();
}

void CSVReportSet::hideSmsList2()
{	
	pShow2 -> hide();
	pHide2 -> show();
	table2 -> hide();
}

void CSVReportSet::AddGroupOperate(WTable * pTable)
{
	PrintDebugString("begin Init AddOperator function\n");

    m_pGroupOperate = new WTable((WContainerWidget *)pTable->elementAt( 8, 0));
   
	if ( m_pGroupOperate )
    {

        WImage * pSelAll = new WImage("../icons/selall.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
        if (pSelAll)
        {
            pSelAll->setStyleClass("imgbutton");
			pSelAll->setToolTip(m_formText.szTipSelAll1);
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

        WImage * pSelNone = new WImage("../icons/selnone.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
        if (pSelAll)
        {
            pSelNone->setStyleClass("imgbutton");
			pSelNone->setToolTip(m_formText.szTipSelNone);
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

        WImage * pSelinvert = new WImage("../icons/selinvert.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
        if (pSelinvert)
        {
            pSelinvert->setStyleClass("imgbutton");
			pSelinvert->setToolTip(m_formText.szTipSelInv);
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		
		pDel = new WImage("../icons/del.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 4));
		if(!GetUserRight("m_reportlistDel"))
			pDel->hide();
		else
			pDel->show();

        if (pDel)
        {
           
			pDel->setStyleClass("imgbutton");
			pDel->setToolTip(m_formText.szTipDel);
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
        }

		
		pAdd = new WPushButton(m_formText.szAddPhoneBut, (WContainerWidget *)m_pGroupOperate->elementAt(0, 6));
		pAdd->setStyleClass("wizardbutton");
		if(!GetUserRight("m_reportlistAdd"))
			pAdd->hide();
		else
			pAdd->show();

        if (pAdd)
        {
            pAdd->setToolTip(m_formText.szTipAddNew);
			WObject::connect(pAdd, SIGNAL(clicked()),"showbar();", this, SLOT(AddPhone())
				, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
		m_pGroupOperate->elementAt(0, 6)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
		m_pGroupOperate->elementAt(0, 6)->setContentAlignment(AlignRight);
		
    }

	PrintDebugString("Init AddOperator function\n");

	//隐藏按钮
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelPhone()));
		pHideBut->hide();
	}

	PrintDebugString("Init AddOperator function finish\n");
}

void CSVReportSet::SelNone()
{
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(false);
    }
}
void CSVReportSet::SelInvert()
{
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem ++)
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

void CSVReportSet::MainHelp()
{
	
}

void CSVReportSet::refresh()
{
	//nullTable -> clear();
	PrintDebugString("Begin refresh function\n");

	UpdatePhoneList();
	
	if(!GetUserRight("m_reportlistAdd"))
		m_pAdd->hide();
	else
		m_pAdd->show();

	if(!GetUserRight("m_reportlistDel"))
		m_pDel->hide();
	else
		m_pDel->show();

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

void CSVReportSet::UpdatePhoneList()
{
	/*
	int nNum =m_ptbPhone->numRows();
	for(int i=1;i<nNum;i++)
	{
		m_ptbPhone->deleteRow(1);

	}
	*/
	PrintDebugString("Into UpdatePhoneList\n");

	m_pReportListTable->GeDataTable()->clear();

	m_pListReport.clear();

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	GetIniFileSections(sectionlist, "reportset.ini");

	//if(sectionlist.size() == 0)
	//{
	//	WText * nText = new WText("[----------统计报告列表为空-----------]", (WContainerWidget*)m_pReportListTable->GeDataTable() -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	//nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}

	int numRow = 1;
	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		std::string section = *m_sItem;

		std::list<string> keylist;
		std::list<string>::iterator m_pItem;
		
		bool bRet = false;
		bRet = GetIniFileKeys(section,keylist, "reportset.ini" );
		if(!bRet)
		{
		}

		m_pItem = keylist.begin();

		std::string str = *m_pItem;
		std::string ret = "error";


		REPORT_LIST list;

		m_pReportListTable->InitRow(numRow);
		
		// 是否选择
		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);

		
		// 名称
		std::string ReportName = GetIniFileString(section, "Title", ret, "reportset.ini");
		std::string strlinkname;
		std::string hrefstr =  RepHrefStr(ReportName);
		strlinkname ="<a href=/fcgi-bin/statsreportlist.exe?id="+hrefstr+">"+ReportName+"</a>";

		OutputDebugString("----------------report link name include null----------------\n");
		OutputDebugString(strlinkname.c_str());
		OutputDebugString("\n");

		if(strcmp(ReportName.c_str(), "error") == 0)
		{
		}
		WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);

		std::string ReportPeriod = GetIniFileString(section, "Period", ret, "reportset.ini");
		if(strcmp(ReportPeriod.c_str(), "error") == 0)
		{
		}
		WText *pPeriod = new WText(ReportPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);

		WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow ,6));
		m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);
		if(!GetUserRight("m_reportlistEdit"))
			pEdit->hide();
		else
			pEdit->show();

		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	    connect(pEdit, SIGNAL(clicked()),"showbar();", &m_signalMapper, SLOT(map()),
			WObject::ConnectionType::JAVASCRIPTDYNAMIC);

		m_signalMapper.setMapping(pEdit, section);

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		m_pListReport.push_back(list);		

		numRow++;

		PrintDebugString("Into UpdatePhoneList loop\n");
	}	
}

void CSVReportSet::enabled()
{	
	/*
	if(!pAdd->isEnabled())
		pAdd->setEnabled(true);
	*/
}




//////////////////////////////////////////////////////////////////////////////////
// end file
	