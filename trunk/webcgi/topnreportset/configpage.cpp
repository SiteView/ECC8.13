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
������
    szRepStr����Ҫ�����ַ���

���ܣ�
	���������ַ������ʱ��"&" "$" "#" " "�ַ���
	��%26 %24 %23 %20�滻

����ֵ��
    ���º���ַ���
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
������
	parent������

���ܣ�
    ���캯��
**************************************************************/
CSVTopnReportSet::CSVTopnReportSet(WContainerWidget * parent):
WContainerWidget(parent)
{
	IsShow = true;//�Ƿ���ʾ����
	chgstr = ""; //���������Ƿ�ı�
	loadString();//������Դ�ļ�
    initForm();//��ʼ��������
}


//��ӿͻ��˽ű�����
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
������

���ܣ�
    ��ʼ��TOPN����ҳ��
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

		//���ذ�ť
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



	////��ҳ���а���basic.js�ű��ļ�
	//new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	////��һ����
	//WTable* T1table = new WTable(this);
	//T1table->setStyleClass("t1");

	//new WText(m_formText.szTitle, T1table->elementAt(0,0));
	//T1table->elementAt(0,0)->setStyleClass("t1title");
	//
	////TitleTable������ �Ƿ�������ʾ��Ϣ�� ���롢ˢ�¡�������ť
	//WTable * TitleTable = new WTable(T1table->elementAt(1,0));
	//TitleTable->setStyleClass("t3");
		
	//��ʼ������ʾ��Ϣ����
	m_pConnErr = new WText("", (WContainerWidget *)this);
	m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	m_pConnErr ->hide();
	
	//��������SVDB
	std::list<string> sectionlist;
	bool IsConn = GetIniFileSections(sectionlist, "smsconfig.ini");
	if(!IsConn)
	{
		//����SVDBʧ��
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
	//����
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

	////����ܰ�����ť
	//m_pHelpImg = new WImage("../icons/help.gif", (WContainerWidget *)TitleTable->elementAt( 0, 1));
	//m_pHelpImg ->setStyleClass("helpimg");
	//m_pHelpImg->setToolTip(m_formText.szHelp);
	//TitleTable->elementAt(0, 1) -> setContentAlignment(AlignTop | AlignRight);
	//WObject::connect(m_pHelpImg, SIGNAL(clicked()), this, SLOT(MainHelp()));


	////���ء���ʾ�б�
	//WTable * m_pListGeneral = new WTable(T1table->elementAt(2,0));
	//m_pListGeneral ->setStyleClass("t2");
	//
	////��/����ʾ��
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

	////���漰������ť
	//table2 = new WTable((WContainerWidget *)m_pListGeneral->elementAt(1,0));
	//table2 -> setStyleClass("t3");
 //   if ( table2 )
 //   {
 //       addPhoneList(table2);//�����б�
	//	//�༭ӳ��
	//	connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));
	//	AddGroupOperate(table2);//������ť
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
������
	table�������б���һ�����

���ܣ�
	��topnreportset.ini���TOPN����������䱨���б�
*******************************************************/
void CSVTopnReportSet::addPhoneList(WTable * table)
{
	//TOPN�����б�
    m_ptbPhone = new WTable((WContainerWidget*)table->elementAt(7,0));
	//�����б�Ϊ��
	nullTable = new WTable((WContainerWidget*)table->elementAt(8, 0));

	m_ptbPhone -> setStyleClass("t3");
	nullTable -> setStyleClass("t3");

    if (m_ptbPhone)
    {
		//�����б���������Ƿ�ѡ�񡢱������ơ��������ڡ��༭
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

	//��������LIST
	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;

	//��topnreportset.iniȡTOPN����LIST
	GetIniFileSections(sectionlist, "topnreportset.ini");

	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		//ȡ�����б������
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
		//��REPORT_LIST��ֵ
		list.pSelect = pCheck;
		list.pName = pName;
		list.pPeriod = pPeriod;
		list.pEdit = pEdit;
		//REPORT_LIST����LIST
		m_pListReport.push_back(list);		
	}
	//�����б�����ʾ��ʽ�� ��ɫΪһ�а�һ�е���
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

		// ����
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
������
	strErrMsg����ʾ������Ϣ�ַ���

���ܣ�
    TEXT���ô�����Ϣ��δʹ�ã�
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
������

���ܣ�
    ������Դ�ļ�
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
			//���Resource	
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
������

���ܣ�
    ѡ�����е�TOPN����
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
������

���ܣ�
    ����TOPN����
***********************************************/
void CSVTopnReportSet::AddPhone()
{
	//emit AddNewPhone() �ź�
    emit AddNewPhone();
}

/*************************************************************
������
	str���༭�ı�����
���ܣ�
	���ݱ������༭ָ���ı���
*************************************************************/
void CSVTopnReportSet::EditRow(const std::string str)
{
	chgstr = str;
	std::string ret = "error";
    SAVE_REPORT_LIST report;

	PrintDebugString(str.c_str());

	//��������
	report.szTitle = GetIniFileString(str, "Title", ret, "topnreportset.ini");
	if(strcmp(report.szTitle.c_str(), "error") == 0)
	{
		report.szTitle = "";
	}

	//��������
	report.szDescript = GetIniFileString(str, "Descript", ret, "topnreportset.ini");
	if(strcmp(report.szDescript.c_str(), "error") == 0)
	{
		report.szDescript = "";
	}

	//��������
	report.szPeriod = GetIniFileString(str, "Period", ret, "topnreportset.ini");
	if(strcmp(report.szPeriod.c_str(), "error") == 0)
	{
	}

	//����EMAIL��ַ
	report.szEmailSend = GetIniFileString(str, "EmailSend", ret, "topnreportset.ini");
	if(strcmp(report.szEmailSend.c_str(), "error") == 0)
	{
		report.szEmailSend = "";
	}

	//��ֹ����ѡ��
	report.szDeny = GetIniFileString(str, "Deny", ret, "topnreportset.ini");
	if(strcmp(report.szDeny.c_str(), "error") == 0)
	{
	}

	//���ɱ���ʱ��
	report.szGenerate = GetIniFileString(str, "Generate", ret, "topnreportset.ini");
	if(strcmp(report.szGenerate.c_str(), "error") == 0)
	{
	}

	//ѡ������
	report.szSelType = GetIniFileString(str, "Type", ret, "topnreportset.ini");
	if(strcmp(report.szSelType.c_str(), "error") == 0)
	{
	}

	//ѡ��ָ��
	report.szSelMark = GetIniFileString(str, "Mark", ret, "topnreportset.ini");
	if(strcmp(report.szSelMark.c_str(), "error") == 0)
	{
	}

	//����ʽ
	report.szSelSort = GetIniFileString(str, "Sort", ret, "topnreportset.ini");
	if(strcmp(report.szSelSort.c_str(), "error") == 0)
	{
	}

	//ͼ����ʾ��
	report.szCount = GetIniFileString(str, "Count", ret, "topnreportset.ini");
	if(strcmp(report.szCount.c_str(), "error") ==0)
	{
		report.szCount = "";
	}

	//����Ȩ��
	report.szGroupRight= GetIniFileString(str, "GroupRight", ret, "topnreportset.ini");
	if(strcmp(report.szGroupRight.c_str(), "error") ==0)
	{
		
	}

	//����ƻ�
	report.szPlan = GetIniFileString(str, "Plan", ret, "topnreportset.ini");
	if(strcmp(report.szPlan.c_str(), "error") == 0)
	{
	}

	//ȡֵ��ʽ
	report.szGetValue = GetIniFileString(str, "GetValue", ret, "topnreportset.ini");
	if(strcmp(report.szGetValue.c_str(), "error") == 0)
	{
	}

	//�ܱ���ֹʱ��
	report.szWeekEnd = GetIniFileString(str, "WeekEndTime", ret, "topnreportset.ini");
	if(strcmp(report.szGetValue.c_str(), "error") == 0)
	{
	}

	//�༭������ǰ�ı�������
	report.chgstr = str;
	//���ͱ༭�����ź�
	emit EditPhone(report);
}

/*******************************************
������

���ܣ�
    ɾ��������ǰ�Ĳ���
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
������

���ܣ�
    ɾ������
*******************************************/
void CSVTopnReportSet::DelPhone()
{
	string strDeletePhone;
	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
    {       
		//�����б��Ƿ�ѡ��
        if (m_pListItem->pSelect->isChecked())
        {           
			std::list<string> sectionlist;
			std::list<string>::iterator sectionitem;
			std::string temp = m_pListItem->pName->text();		
			int pos = temp.find(">", 0);
			int pos1 = temp.find("<", pos);
			temp = temp.substr(pos + 1, pos1 - pos - 1);			
			//��topnreportset.iniɾ������
			DeleteIniFileSection(temp, "topnreportset.ini");			
			
			//��topnreportgenerate.ini��ɾ�����������
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

			//ɾ��m_pListReport�ж�Ӧ����
            m_pListReport.erase(pItem);  
			//ɾ���б��е���
            m_pReportListTable->GeDataTable()->deleteRow(nRow); 						
        }
    }

	////����б�Ϊ�գ� ����ʾ��ʾ��Ϣ
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

	//���¼��UserOperateLog��
	string strUserID = GetWebUserID();
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_formText.szTipDel,m_formText.szTitle,strDeletePhone);

}

/******************************************************************
������
	report�� ����TOPN�����SAVE_REPORT_LIST�ṹ

���ܣ�
    ���ݱ���ṹ�еı���������TOPN����
******************************************************************/
void CSVTopnReportSet::SaveTopnReport(SAVE_REPORT_LIST * report)
{    
	////����б�Ϊ�յ���ʾ��Ϣ
	//nullTable -> clear();
	
	//����༭�������Ʋ�Ϊ����༭
	if(strcmp(chgstr.c_str(), "") != 0)
    {
        Edit_Phone(report);
        return;
    }	
    
	//judge report name/(ini section) is right
	//ȡ����Ȩ��
	std::list<string> sectionlist;
	std::list<string>::iterator Item;
	GetIniFileSections(sectionlist, "topnreportset.ini");
	//ȡ�б�����
	int numRow = m_pReportListTable->GeDataTable()->numRows();
	m_pReportListTable->InitRow(numRow);
	//�Ƿ�ѡ�����
	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
	m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignTop | AlignCenter);
	//����HREF�����ַ���
	std::string strlinkname;		
	std::string hrefstr = RepHrefStr(report->szTitle);
	strlinkname = "<a href=/fcgi-bin/topnreportlist.exe?id="+hrefstr+">"+report->szTitle+"</a>";
	
	//��������
	WText *pName = new WText(strlinkname, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 2));	
	m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignTop | AlignCenter);

	//��������
	WText *pPeriod = new WText(report->szPeriod, (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 4));
	m_pReportListTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignTop | AlignCenter);

	//�༭��ť
	WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow , 6));
	m_pReportListTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignTop | AlignCenter);
	pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   

	//�б���ʽ
	//Jansion.zhou 2006-12-26
	//m_pReportListTable->GeDataTable()->adjustRowStyle("tr1","tr2"); 

	//�༭��ťMAP�ַ�������������
	m_signalMapper.setMapping(pEdit, report->szTitle);
	
	//дINI�ļ�����ֵ
	bool isWriteIni = false;

	//��������
	isWriteIni = WriteIniFileString(report->szTitle, "Title", report->szTitle, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//��������
	isWriteIni = WriteIniFileString(report->szTitle, "Descript", report->szDescript, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//��������
	isWriteIni = WriteIniFileString(report->szTitle, "Period", report->szPeriod, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//EMAIL���͵�ַ
	isWriteIni = WriteIniFileString(report->szTitle, "EmailSend", report->szEmailSend, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//�����ֹѡ��
	isWriteIni = WriteIniFileString(report->szTitle, "Deny", report->szDeny, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//��������ʱ��
	isWriteIni = WriteIniFileString(report->szTitle, "Generate", report->szGenerate, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//ѡ������
	isWriteIni = WriteIniFileString(report->szTitle, "Type", report->szSelType, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//ѡ��ָ��
	isWriteIni = WriteIniFileString(report->szTitle, "Mark", report->szSelMark, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//����ʽ
	isWriteIni = WriteIniFileString(report->szTitle, "Sort", report->szSelSort, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//ͼ����ʾ��
	isWriteIni = WriteIniFileString(report->szTitle, "Count", report->szCount, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//����Ȩ��
	isWriteIni = WriteIniFileString(report->szTitle, "GroupRight", report->szGroupRight, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//����ƻ�
	isWriteIni = WriteIniFileString(report->szTitle, "Plan", report->szPlan, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//ȡֵ��ʽ
	isWriteIni = WriteIniFileString(report->szTitle, "GetValue", report->szGetValue, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//�ܱ���ֹʱ��
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
	//REPORT�ṹPUSHBACK��LIST
	m_pListReport.push_back(list);
	//����MAP�����¼�
	connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
}

/***************************************************************
������
	report�� ����༭�ṹ

���ܣ�
    ���ݽṹ�еı������Ʊ༭����
***************************************************************/
void CSVTopnReportSet::Edit_Phone(SAVE_REPORT_LIST * report)
{
	bool isWriteIni = false;

	//�༭�������ƣ� ���µı�������(report->szTitle)����ԭ������(chgstr)
	isWriteIni = EditIniFileSection(chgstr, report->szTitle, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д�������Ƶ�INI�ļ�
	isWriteIni = WriteIniFileString(report->szTitle, "Title", report->szTitle, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д����������INI�ļ�
	isWriteIni = WriteIniFileString(report->szTitle, "Descript", report->szDescript, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д�������ڵ�INI�ļ�
	isWriteIni = WriteIniFileString(report->szTitle, "Period", report->szPeriod, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//дEMAIL���͵�ַ
	isWriteIni = WriteIniFileString(report->szTitle, "EmailSend", report->szEmailSend, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д�Ƿ��ֹ����ѡ��
	isWriteIni = WriteIniFileString(report->szTitle, "Deny", report->szDeny, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д��������ʱ��
	isWriteIni = WriteIniFileString(report->szTitle, "Generate", report->szGenerate, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д����ѡ������
	isWriteIni = WriteIniFileString(report->szTitle, "Type", report->szSelType, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д����ѡ��ָ��
	isWriteIni = WriteIniFileString(report->szTitle, "Mark", report->szSelMark, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д��������ʽ
	isWriteIni = WriteIniFileString(report->szTitle, "Sort", report->szSelSort, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д����ͼ����ʾ��
	isWriteIni = WriteIniFileString(report->szTitle, "Count", report->szCount, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д����Ȩ��
	isWriteIni = WriteIniFileString(report->szTitle, "GroupRight", report->szGroupRight, "topnreportset.ini");

	if(!isWriteIni)
	{
	}

	//д����ƻ�
	isWriteIni = WriteIniFileString(report->szTitle, "Plan", report->szPlan, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д����ȡֵ��ʽ
	isWriteIni = WriteIniFileString(report->szTitle, "GetValue", report->szGetValue, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	//д�ܱ����ֹʱ��
	isWriteIni = WriteIniFileString(report->szTitle, "WeekEndTime", report->szWeekEnd, "topnreportset.ini");
	if(!isWriteIni)
	{
	}

	for(m_pListItem = m_pListReport.begin(); m_pListItem != m_pListReport.end(); m_pListItem++)
	{
		//�ڱ���LIST�и���ԭ�������Ʋ��ұ༭����
		if(strcmp(chgstr.c_str(), m_pListItem->pName->text().c_str()) == 0)
		{
			//���µı�����������ӳ��༭
			m_pListItem->pName->setText(report->szTitle);
			m_pListItem->pPeriod->setText(report->szPeriod);
			m_signalMapper.setMapping(m_pListItem->pEdit, report->szTitle);
			break;
		}
	}

	//�洢ԭ�������Ʊ������³�ʼ��Ϊ��
	chgstr = "";
}

/*****************************************
δʹ�ú���
*****************************************/
void CSVTopnReportSet::showSmsList()
{
	pShow -> show();
	pHide -> hide();
	table -> show();
}

/****************************************
δʹ�ú���
****************************************/
void CSVTopnReportSet::hideSmsList()
{
	pShow -> hide();
	pHide -> show();
	table -> hide();
}

/****************************************
δʹ�ú���
****************************************/
void CSVTopnReportSet::showSmsList1()
{
	pShow1 -> show();
	pHide1 -> hide();
	table1 -> show();
}

/****************************************
δʹ�ú���
****************************************/
void CSVTopnReportSet::hideSmsList1()
{
	pShow1 -> hide();
	pHide1 -> show();
	table1 -> hide();
}

/********************************************
������

���ܣ�
    ��ʾ�����б�
********************************************/
void CSVTopnReportSet::showSmsList2()
{
	pShow2 -> show();
	pHide2 -> hide();
	table2 -> show();	
}

/********************************************
������

���ܣ�
    ���ر����б�
********************************************/
void CSVTopnReportSet::hideSmsList2()
{	
	pShow2 -> hide();
	pHide2 -> show();
	table2 -> hide();
}

/***********************************************************
������
	pTable�� ������ť��һ�����

���ܣ�
	���Ӳ�����ť
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

	//���ذ�ť
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelPhone()));
		pHideBut->hide();
	}
}

/*********************************************
������

���ܣ�
	ȡ������ѡ��	
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
������

���ܣ�
    ��ѡ����ѡ����
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
������

���ܣ�
    ˢ�±���
**************************************/
void CSVTopnReportSet::refresh()
{
	//nullTable -> clear();

	UpdatePhoneList();

	//����
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
����:

����:
    ���±����б�
******************************************/
void CSVTopnReportSet::UpdatePhoneList()
{
	////ɾ�������б���
	//int nNum =m_pReportListTable->GeDataTable()->numRows();
	//for(int i=1;i<nNum;i++)
	//{
	//	m_pReportListTable->GeDataTable()->deleteRow(1);
	//}

	m_pReportListTable->GeDataTable()->clear();

	//�������LIST
	m_pListReport.clear();

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	
	bool IsConn = GetIniFileSections(sectionlist, "topnreportset.ini");
	
	if(!IsConn)
	{
		//����SVDBʧ��
		m_pConnErr ->setText(m_formText.szConnErr);
		m_pConnErr ->show();
	}
	else
	{
		m_pConnErr ->hide();
	}

	////�������Ϊ������ʾ��ʾ��Ϣ
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
		//ȡ�����������������ɱ���
		bRet = GetIniFileKeys(section,keylist, "topnreportset.ini" );
		if(!bRet)
		{
		}

		m_pItem = keylist.begin();

		std::string str = *m_pItem;
		std::string ret = "error";
		//int numRow = m_pReportListTable->GeDataTable()->numRows();

		REPORT_LIST list;
		
		// �Ƿ�ѡ��
		numRow = m_pReportListTable->GeDataTable()->numRows();
		m_pReportListTable->InitRow(numRow);

		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pReportListTable->GeDataTable()->elementAt(numRow, 0));		
		m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignTop | AlignCenter);

		// ����
		std::string ReportName = GetIniFileString(section, "Title", ret, "topnreportset.ini");
		if(strcmp(ReportName.c_str(), "error") == 0)
		{
		}
		std::string strlinkname;//������������
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

		//�ñ�������MAP�༭
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


