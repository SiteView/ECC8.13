#include ".\topnreportlist.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"

//#include "chart/include\chartdir.h"
#include "../base/OperateLog.h"

#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
#include "WFont"
#include "WPushButton"

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"

#define WTGET

std::string RetRepHrefStr(std::string szRepStr)
{
	std::string szValue = szRepStr;

    int nPos = szValue.find("%26", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "&" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%26", nPos);
    }

    nPos = szValue.find("%24", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "$" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%24", nPos);
    }

    nPos = szValue.find("%23", 0);
    while (nPos >= 0)
    {
		szValue = szValue.substr(0, nPos ) + "#" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%23", nPos);
    }

    nPos = szValue.find("%20", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + " " + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%20", nPos);
    }

	return szValue;
}
string& replace_all_distinct(string& str,
							 const string& old_value,
							 const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

int CTopnReportList::InsertListRow(int num,
								   int pos, 
								   std::string section,
								   std::string tempsection,
								   std::list<string> keylist, 
								   std::string filename)
{
	std::list<string>::iterator keyitem;
	std::string keystr;
	std::string keyval;
	int pos1 = 0;

	GetIniFileKeys(tempsection, keylist, filename);
			
	std::string starttime ;
	std::string endtime;

	pos1 = tempsection.find("$", pos+1);
	starttime = tempsection.substr(pos + 1, pos1 - pos - 1);
	pos = tempsection.find("$", pos1 + 1);
	endtime = tempsection.substr(pos1 + 1, pos - pos1 - 1);

	std::string temptime = "<a href=../report/";
	std::string temphtmlname = starttime;
	temphtmlname += endtime;
	temphtmlname += section;
	temphtmlname += ".html";	

	std::string mapstr = section;
	mapstr += "$";
	mapstr += starttime;
	mapstr += "$";
	mapstr += endtime;
	mapstr += "$";

	replace_all_distinct(temphtmlname, " ", "_");
	replace_all_distinct(temphtmlname, ":", "_");
	temptime += temphtmlname;
	temptime += ">";
	temptime += starttime;
	temptime += "~";
	temptime += endtime;
	//链接文件名
	temptime += "</a>";			
	
	WText * pSection = new WText(temptime, (WContainerWidget*)pMonitorListTable -> elementAt(num, 1));
	pMonitorListTable -> elementAt(num, 1) ->setContentAlignment(AlignTop | AlignCenter);

	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)pMonitorListTable->elementAt(num, 0));

	_LIST list;
	list.pSelect = pCheck;
	list.pSection = pSection;
	list.szSection = mapstr;

	m_pList.push_back(list);

	std::string defaultret = "error";
	int knum = 1;
	for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem++)
	{
		std::string sval; std::string sval1; std::string sval2;
		keystr = *keyitem;

		std::list<string>::iterator colitem;
		
		for(colitem = colname1.begin(); colitem != colname1.end(); colitem++)
		{
			std::string tempstr = *colitem;
													
			if(strcmp(tempstr.c_str(),keystr.c_str()) == 0)
			{														
				keyval = GetIniFileString(tempsection, keystr, defaultret, filename);
				if(strcmp(keyval.c_str(), "error") == 0)
				{
					continue;
				}
								
				char valbuf[256];
				memset(valbuf, 0, 256);
				pos = keyval.find("$", 0);
				sval = keyval.substr(0, pos);						

				pos1 = keyval.find("$", pos + 1);
				sval1 = keyval.substr(pos + 1, pos1 - pos - 1);

				pos = keyval.find("$", pos1 + 1);
				sval2 = keyval.substr(pos1 + 1, pos - pos1 - 1);
				
				
				new WText(sval, (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				knum++;
				new WText(sval1, (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				knum++;
				new WText(sval2, (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
															
				knum++;	 
			}										
		}
	}
	num++;	
	return num;
}


//添加客户端脚本变量
void CTopnReportList::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

CTopnReportList::CTopnReportList(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Simple_Report_Caption",m_formText.szCaption1);
			FindNodeValue(ResNode,"IDS_TopN_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_TopN_Report",m_formText.szMonitorListName);
			FindNodeValue(ResNode,"IDS_State",m_formText.szMonitorListStatus);
			FindNodeValue(ResNode,"IDS_Description",m_formText.szMonitorListDescription);
			FindNodeValue(ResNode,"IDS_Monitor_Name",m_formText.szMonitorListName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szMonitorListTime);
			FindNodeValue(ResNode,"IDS_All_Select_Other",m_formText.szTipSelAll);
			FindNodeValue(ResNode,"IDS_All_Select",m_formText.szTipSelAll1);
			FindNodeValue(ResNode,"IDS_None_Select",m_formText.szTipSelNone);
			FindNodeValue(ResNode,"IDS_Invert_Select",m_formText.szTipSelInv);
			FindNodeValue(ResNode,"IDS_Delete",m_formText.szTipDel);
			FindNodeValue(ResNode,"IDS_Report",szReport);
			FindNodeValue(ResNode,"IDS_Create_Immediately",szCreateImm);
			FindNodeValue(ResNode,"IDS_Max_Value",szMaxValue);
			FindNodeValue(ResNode,"IDS_Average_Value",szAverageValue);
			FindNodeValue(ResNode,"IDS_Min_Value",szMinValue);
			FindNodeValue(ResNode,"IDS_Report_Day",szReportDay);
			FindNodeValue(ResNode,"IDS_Report_Week",szReportWeek);
			FindNodeValue(ResNode,"IDS_Report_Month",szReportMonth);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh1);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip1);
			FindNodeValue(ResNode,"IDS_TopN_Report_List",strTopNReportList);
			FindNodeValue(ResNode, "IDS_Return", strReturn);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",szButMatch);
			FindNodeValue(ResNode,"IDS_DeleteSMSAffirmInfo",szDeleteAffirmInfo);
			FindNodeValue(ResNode,"IDS_TopNReportListEmpty",sztListEmpty);
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);
			FindNodeValue(ResNode,"IDS_Delete_TopNList",strDelList);
		}
		CloseResource(objRes);
	}

	nListNum = 0;

	ShowMainTable();
}

CTopnReportList::~CTopnReportList(void)
{
	if( objRes !=INVALID_VALUE )
			CloseResource(objRes);
}

void CTopnReportList::ShowMainTable()
{


	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>",this);


	char buf_tmp[4096]={0};
    int nSize =4095;
	std::string reportstr;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
 	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif

	std::string repbuf = RetRepHrefStr(buf_tmp);
	memset(buf_tmp, 0, 4096);
	strcpy(buf_tmp, repbuf.c_str());
	//strcpy(buf_tmp, "id=month_report");
	if(strcmp(buf_tmp, "") == 0)
	{		
		return;
	}
	else
	{		
		std::string fstr = buf_tmp;
		std::string s = fstr.substr(0, 3);
		if(strcmp(s.c_str(), "id=") == 0)
		{
			reportstr = fstr.substr(3, fstr.size() - 3);
		}
	}
	szReport += ":"+reportstr;


	pMainTable = new WSVMainTable(this, strTopNReportList, false);

	m_pReportListTable = new WSVFlexTable(pMainTable->GetContentTable()->elementAt(0,0), List, szReport);
	
	if (m_pReportListTable->GetContentTable() != NULL)
	{
		m_pReportListTable->AppendColumn("",WLength(40,WLength::Pixel));
		m_pReportListTable->SetDataRowStyle("table_data_grid_item_img");

		m_pReportListTable->AppendColumn(strTopNReportList,0);
		m_pReportListTable->SetDataRowStyle("table_data_grid_item_img");

		//m_pReportListTable->AppendColumn(m_formText.szColPeriod,WLength(120,WLength::Pixel));
		//m_pReportListTable->SetDataRowStyle("table_data_grid_item_img");

		//m_pReportListTable->AppendColumn(m_formText.szColEdit,WLength(120,WLength::Pixel));
		//m_pReportListTable->SetDataRowStyle("table_data_grid_item_text");
	}


	NewAddColum();
	//addPhoneListNew();
	//connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));

	if (m_pReportListTable->GetActionTable() != NULL)
	{

		m_pReportListTable->SetNullTipInfo(sztListEmpty);

		if(m_pList.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
			//OutputDebugString("---------------- NO A------------------\n");
		}
		else
		{
			//OutputDebugString("---------------- Yes A------------------\n");
			m_pReportListTable->HideNullTip();
		}
		
		m_pReportListTable->AddStandardSelLink(m_formText.szTipSelAll1 ,m_formText.szTipSelNone,m_formText.szTipSelInv);
		connect(m_pReportListTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		connect(m_pReportListTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		connect(m_pReportListTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));


		WTable *pTbl;
		m_pReportListTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pReportListTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		//m_pReportListTable->GetActionTable()->elementAt(0,1)->resize(WLength(100, WLength::Pixel),0);
		pTbl = new WTable(m_pReportListTable->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");

		m_pDel = new WSVButton(pTbl->elementAt(0,1),m_formText.szTipDel, "button_bg_del.png", m_formText.szTipDel, false);
		if ( m_pDel)
            connect(m_pDel , SIGNAL(clicked()),this, SLOT(BeforeDelList()));
		//if (m_pDel)
		//{
		//	m_pDel->setToolTip(m_formText.szTipDel);
		//	connect(m_pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
		//}

		m_pReportListTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		m_pAdd = new WSVButton(m_pReportListTable->GetActionTable()->elementAt(0,2), szCreateImm, "button_bg_m_black.png", szCreateImm, true);
		//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", m_pReportListTable->GetActionTable()->elementAt(0, 3));
		m_pRen = new WSVButton(m_pReportListTable->GetActionTable()->elementAt(0,3), strReturn, "button_bg_m.png", strReturn, false);
		m_pReportListTable->GetActionTable()->elementAt(0,4)->setContentAlignment(AlignCenter);
		if(m_pAdd)
		{
		//	WObject::connect(pGenReportButn, SIGNAL(clicked()), this, SLOT(FastGenReport()));
			WObject::connect(m_pAdd, SIGNAL(clicked()), "showbar();", this, SLOT(FastGenReport())
					, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}

		if(m_pRen)
		{
			WObject::connect(m_pRen, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainTopnReport()),
				WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}

		//if (m_pAdd)
		//{
		//	m_pAdd->setToolTip(m_formText.szTipAddNew);
		//	WObject::connect(m_pAdd, SIGNAL(clicked()),"showbar();", this, SLOT(AddPhone())
		//		, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//}
			
		//隐藏按钮
		pHideBut = new WPushButton("hide button",this);
		if(pHideBut)
		{
			pHideBut->setToolTip("Hide Button");
			connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelList()));
			pHideBut->hide();
		}
	}


	int m_numRow = m_pReportListTable->numRows();
	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)m_pReportListTable->elementAt(m_numRow, 1));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pReportListTable->elementAt(m_numRow, 1));

	pExChangeBtn = new WPushButton(strRefresh1, (WContainerWidget *)m_pReportListTable->elementAt(m_numRow, 1));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip1);
	pExChangeBtn->hide();

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	//bTrans = 1;
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

	new WText("</div>", this);

	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);






	//new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);		
	//
	//WTable * FrameTable = new WTable(this);
	//FrameTable->setStyleClass("t1");
	////
	////char buf_tmp[4096]={0};
 ////   int nSize =4095;
	////std::string reportstr;
	////GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);

	////std::string repbuf = RetRepHrefStr(buf_tmp);
	////memset(buf_tmp, 0, 4096);
	////strcpy(buf_tmp, repbuf.c_str());

	////

	//////strcpy(buf_tmp, "id=month_report");
	////if(strcmp(buf_tmp, "") == 0)
	////{		
	////	return;
	////}
	////else
	////{		
	////	std::string fstr = buf_tmp;
	////	std::string s = fstr.substr(0, 3);
	////	if(strcmp(s.c_str(), "id=") == 0)
	////	{
	////		reportstr = fstr.substr(3, fstr.size() - 3);
	////	}
	////}

	////szReport += reportstr;
	//reporttitle = new WText(szReport, (WContainerWidget*)FrameTable->elementAt(0, 0));
	////reporttitle->setText
	//FrameTable->elementAt(0, 0)->setStyleClass("t1title");

	//WTable * blanktable = new WTable((WContainerWidget*)FrameTable->elementAt(1, 0));
	//blanktable->setStyleClass("t3");

	//pMonitorListTable = new WTable((WContainerWidget*)FrameTable->elementAt(2, 0));
	////pMonitorListTable->setStyleClass("tablewidth");
	//pMonitorListTable->setStyleClass("StatsTable1");
	////pMonitorListTable->prop = "border='1' bordercolorlight='#eeeeee' bordercolordark='#ffffff'";
	//pMonitorListTable->tableprop_ = 2;
	//pMonitorListTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";	 
	//pMonitorListTable->setCellSpaceing(10);

	////AddGroupOperate(FrameTable);

	///*
	//WScrollArea * pScrollArea = new WScrollArea(this);
	//
	//pScrollArea->setStyleClass("tableheight");
	//pScrollArea->setWidget(pMonitorListTable);
	//*/
	////AddColum(NULL);	
}

void CTopnReportList::AddColum(WTable* pContain)
{		
	char buf_tmp[4096]={0};
    int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
 	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
	std::string repbuf = RetRepHrefStr(buf_tmp);
	memset(buf_tmp, 0, 4096);
	strcpy(buf_tmp, repbuf.c_str());

	strRefreshID = buf_tmp; 
	//strcpy(buf_tmp, "id=month_report");
	if(strcmp(buf_tmp, "") == 0)
	{
		if(strRefresh.empty())
		{
			return;
		}
		
	}
	else
	{		
		std::string fstr = buf_tmp;
		std::string s = fstr.substr(0, 3);
		if(strcmp(s.c_str(), "id=") == 0)
		{
			strRefresh = buf_tmp;
		}

	}	

	std::list<string> grouplist;

	char outstr[256];	

	if(!strRefresh.empty())
	{
		
		std::string buf1 = strRefresh;
		int pos = buf1.find("=", 0);
		querystr = buf1.substr(pos+1, buf1.size() - pos - 1);

		szReport = "";
		szReport += querystr;
		reporttitle->setText(szReport);

		std::string defaultret = "error";
		std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "reportset.ini");

		int pos2 = 0;
		int pos1;
				
		while(pos2 >= 0)
		{
			pos1 = pos2;
			pos2 = groupright.find(",", ++pos2 );
			std::string tempstr = groupright.substr(pos1 + 1, pos2 - pos1 - 1);			
			if(!tempstr.empty())
			{
				grouplist.push_back(tempstr);			
			}
		}						
	}

	std::list<string>::iterator item;
	int tablenum = 1;
	int tablenum1 = 1;
	pMonitorListTable->elementAt(0, 0) ->setStyleClass("t3left1");
	pMonitorListTable->elementAt(0, 1) ->setStyleClass("t3left1");
	pMonitorListTable->elementAt(0, 0) ->setContentAlignment(AlignTop | AlignCenter);
	pMonitorListTable->elementAt(0, 1) ->setContentAlignment(AlignTop | AlignCenter);

	pGenReportButn = new WPushButton(szCreateImm, pMonitorListTable->elementAt(0, 1));
	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMonitorListTable->elementAt(0, 1));
	pReturnBtn = new WPushButton(strReturn, (WContainerWidget *)pMonitorListTable->elementAt(0, 1));
	pMonitorListTable->elementAt(0, 1)->setContentAlignment(AlignTop | AlignCenter);

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMonitorListTable->elementAt(0, 1));

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)pMonitorListTable->elementAt(0, 1));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMonitorListTable->elementAt(0, 1));

	pExChangeBtn = new WPushButton(strRefresh1, (WContainerWidget *)pMonitorListTable->elementAt(0, 1));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip1);
	pExChangeBtn->hide();

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


	if(pGenReportButn)
	{
	//	WObject::connect(pGenReportButn, SIGNAL(clicked()), this, SLOT(FastGenReport()));
		WObject::connect(pGenReportButn, SIGNAL(clicked()), "showbar();", this, SLOT(FastGenReport())
				, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	}

	if(pReturnBtn)
	{
		WObject::connect(pReturnBtn, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainTopnReport()),
			WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	}


	TopnMonitorColumnSet();

	AddTableContentFromIni(querystr, "topnreportgenerate.ini",  pMonitorListTable);

	pMonitorListTable->setCellSpaceing(0);
	pMonitorListTable->GetRow(0) ->setStyleClass("Statst1title");
	
}


void CTopnReportList::NewAddColum()
{		
	char buf_tmp[4096]={0};
    int nSize =4095;

	//what to do?
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
	std::string repbuf = RetRepHrefStr(buf_tmp);
	memset(buf_tmp, 0, 4096);
	strcpy(buf_tmp, repbuf.c_str());

	strRefreshID = buf_tmp; 
	//strcpy(buf_tmp, "id=month_report");
	if(strcmp(buf_tmp, "") == 0)
	{
		if(strRefresh.empty())
		{
			return;
		}
		
	}
	else
	{		
		std::string fstr = buf_tmp;
		std::string s = fstr.substr(0, 3);
		if(strcmp(s.c_str(), "id=") == 0)
		{
			strRefresh = buf_tmp;
		}

	}	

	std::list<string> grouplist;

	char outstr[256];	

	if(!strRefresh.empty())
	{
		
		std::string buf1 = strRefresh;
		int pos = buf1.find("=", 0);
		querystr = buf1.substr(pos+1, buf1.size() - pos - 1);

		szReport = "";
		szReport += querystr;
OutputDebugString(querystr.c_str());
OutputDebugString("-----------------------\n");
		//jansion.zhou 2006-12-13
		//reporttitle->setText(szReport);
		m_pReportListTable->pTitleTxt->setText(szReport);
		std::string defaultret = "error";
		std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "reportset.ini");
		int pos2 = 0;
		int pos1;
				
		while(pos2 >= 0)
		{
			pos1 = pos2;
			pos2 = groupright.find(",", ++pos2 );
			std::string tempstr = groupright.substr(pos1 + 1, pos2 - pos1 - 1);			
			if(!tempstr.empty())
			{
				grouplist.push_back(tempstr);			
			}
		}						
	}
	std::list<string>::iterator item;
	int tablenum = 1;
	int tablenum1 = 1;


	TopnMonitorColumnSet();
	OutputDebugString("--------------01-----------------\n");
	
OutputDebugString(querystr.c_str());
OutputDebugString("--------kkkkkkkkkkkkkkkkkkkkk---------------\n");


	NewAddTableContentFromIni(querystr, "topnreportgenerate.ini");

	OutputDebugString("--------------01-Jansion test topnreport----------------\n");
}


//
void CTopnReportList::ExChange()
{

	string strRefresh = "setTimeout(\"location.href ='/fcgi-bin/TopnReportList.exe?";
	strRefresh += strRefreshID;
	strRefresh += "'\",1250);  ";

	WebSession::js_af_up = strRefresh;

	appSelf->quit();
}
//
void CTopnReportList::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "TopnReportListRes";
	WebSession::js_af_up += "')";
}
void CTopnReportList::TopnMonitorColumnSet()
{
	OBJECT hTemplet;

	//new WText(strTopNReportList, pMonitorListTable->elementAt(1, 1));
	//pMonitorListTable->elementAt(1, 1)->setContentAlignment(AlignTop | AlignCenter);
}

void CTopnReportList::MonitorColumnSet(std::string str, int & tablenum, int & tablenum1)
{
		OBJECT hTemplet;
		MAPNODE objNode;

		OBJECT hMon = GetMonitor(str);
		
		MAPNODE node = GetMonitorMainAttribNode(hMon);
		std::string value;
		FindNodeValue(node, "sv_name", value);//需要判断是监测器还是组
		if(value.empty())
		{
						
		}
				
		if( hMon != INVALID_VALUE)
		{			
			//取监测器返回值
			std::string getvalue;
			MAPNODE ma=GetMonitorMainAttribNode(hMon) ;
				
			if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
			{			
				hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				
			}

			LISTITEM item;
			bool bRet = FindMTReturnFirst(hTemplet, item);
				
			
			if(bRet)
			{
				std::string fieldlabel;
				std::string fieldname;
				std::string fieldtype;
				
				float maxval;
				float minval;
				float perval;
				float lastval;

				colname.push_back(value);
				//objNode = FindNext(item);

				string strIDS;
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{
					FindNodeValue(objNode, "sv_label", strIDS);				
					fieldlabel ="";
					if( ResNode != INVALID_VALUE )
							FindNodeValue(ResNode,strIDS,fieldlabel);
					if(fieldlabel=="")
							fieldlabel = strIDS;

					
					FindNodeValue(objNode, "sv_type", fieldtype);								
					FindNodeValue(objNode, "sv_name", fieldname);


					std::string szPrimary;
					FindNodeValue(objNode, "sv_primary", szPrimary);
					if(strcmp(szPrimary.c_str(), "1") == 0)
					{
						std::string tempcol = value;
						tempcol += "$";
						tempcol += fieldlabel;
						tempcol += "$";
						colname1.push_back(tempcol);
						
						std::string tstr = value;
						tstr += "(";
						tstr += fieldlabel;
						tstr += ")";

						new WText(tstr, pMonitorListTable->elementAt(0,tablenum));	
						//pMonitorListTable->elementAt(0,tablenum)->tablecellprop_ = 2;
						//pMonitorListTable->elementAt(0,tablenum)->tablecellprop = " colspan=3 width=300 ";
						pMonitorListTable->elementAt(0, tablenum) ->setContentAlignment(AlignTop | AlignCenter);

						pMonitorListTable->elementAt(0, tablenum) ->setStyleClass("Statst3left");
						pMonitorListTable->elementAt(1, tablenum) ->setContentAlignment(AlignTop | AlignCenter);

						
						new WText(szMinValue, pMonitorListTable->elementAt(1, tablenum1));
						pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
						tablenum1++;
						new WText(szAverageValue, pMonitorListTable->elementAt(1, tablenum1));
						pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
						tablenum1++;
						new WText(szMaxValue, pMonitorListTable->elementAt(1, tablenum1));
						pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
						
						tablenum1++;
						tablenum++;

					}
				}
			}
			if(hTemplet != INVALID_VALUE)
			{
				CloseMonitorTemplet(hTemplet);
			}
		}
		
		CloseMonitor(hMon);
}

void CTopnReportList::AddTableContentFromIni(std::string section,std::string filename, WTable *pContain)
{	
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	std::list<string> sectionlist;
	std::list<string>::iterator sectionitem;
	std::string keystr;
	std::string keyval;
	int pos = 0; int pos1 = 0;
	
	if(section.empty())
	{
		return;
	}


	GetIniFileSections(sectionlist, filename);

	int num =2;
	
	bool bNull = true;

	for(sectionitem = sectionlist.begin(); sectionitem != sectionlist.end(); sectionitem++)
	{
		std::string tempsection = *sectionitem;
		
		pos = tempsection.find("$", 0);
		if(pos < 0)
		{
			continue;
		}

		std::string substr = tempsection.substr(0, pos);

		if(strcmp(substr.c_str(), section.c_str()) == 0)
		{
			bNull = false;
			GetIniFileKeys(tempsection, keylist, filename);
				
			std::string starttime ;
			std::string endtime;

			pos1 = tempsection.find("$", pos+1);
			starttime = tempsection.substr(pos + 1, pos1 - pos - 1);
			pos = tempsection.find("$", pos1 + 1);
			endtime = tempsection.substr(pos1 + 1, pos - pos1 - 1);

			std::string temptime = "<a href=../topnreport/";
			std::string temphtmlname = starttime;
			temphtmlname += endtime;
			temphtmlname += section;
			temphtmlname += ".html";	

			std::string mapstr = section;
			mapstr += "$";
			mapstr += starttime;
			mapstr += "$";
			mapstr += endtime;
			mapstr += "$";

			replace_all_distinct(temphtmlname, " ", "_");
			replace_all_distinct(temphtmlname, ":", "_");
			temptime += temphtmlname;
			temptime += ">";
			temptime += starttime;
			temptime += "~";
			temptime += endtime;
			//链接文件名
			temptime += "</a>";				
			
			WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)pMonitorListTable->elementAt(num, 0));			
			WText * pSection = new WText(temptime, (WContainerWidget*)pMonitorListTable -> elementAt(num, 1));
			pMonitorListTable -> elementAt(num, 0) ->setContentAlignment(AlignTop | AlignCenter);
			pMonitorListTable -> elementAt(num, 1) ->setContentAlignment(AlignTop | AlignCenter);

			_LIST list;
			list.pSelect = pCheck;
			list.pSection = pSection;
			list.szSection = mapstr;

			m_pList.push_back(list);

			num++;
		}

		/*		
		if(strcmp(substr.c_str(), section.c_str()) == 0)
		{
			
			//属于该报告集
			GetIniFileKeys(tempsection, keylist, filename);
			num = InsertListRow(num,pos, section, tempsection, keylist, filename);
			nListNum = num;
			
		}
		*/
	}

	if(bNull)
	{	
		
		WText *nText = new WText(sztListEmpty, (WContainerWidget*)pMonitorListTable -> elementAt(2, 1));	
		nText ->decorationStyle().setForegroundColor(Wt::red);
		pMonitorListTable -> elementAt(2, 1) ->setContentAlignment(AlignTop | AlignCenter);
	}
}


void CTopnReportList::NewAddTableContentFromIni(std::string section,std::string filename)
{	
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	std::list<string> sectionlist;
	std::list<string>::iterator sectionitem;
	std::string keystr;
	std::string keyval;
	int pos = 0; int pos1 = 0;
	OutputDebugString("--------------01-Jansion test topnreport----------------\n");
	if(section.empty())
	{
		return;
	}

	GetIniFileSections(sectionlist, filename);

	int num =2;
	
	bool bNull = true;

	int numRow = 1;

	for(sectionitem = sectionlist.begin(); sectionitem != sectionlist.end(); sectionitem++)
	{
		std::string tempsection = *sectionitem;
		
		pos = tempsection.find("$", 0);
		if(pos < 0)
		{
			continue;
		}

		std::string substr = tempsection.substr(0, pos);

		if(strcmp(substr.c_str(), section.c_str()) == 0)
		{
			bNull = false;
			GetIniFileKeys(tempsection, keylist, filename);
				
			std::string starttime ;
			std::string endtime;

			pos1 = tempsection.find("$", pos+1);
			starttime = tempsection.substr(pos + 1, pos1 - pos - 1);
			pos = tempsection.find("$", pos1 + 1);
			endtime = tempsection.substr(pos1 + 1, pos - pos1 - 1);

			std::string temptime = "<a href=../topnreport/";
			std::string temphtmlname = starttime;
			temphtmlname += endtime;
			temphtmlname += section;
			temphtmlname += ".html";	

			std::string mapstr = section;
			mapstr += "$";
			mapstr += starttime;
			mapstr += "$";
			mapstr += endtime;
			mapstr += "$";

			replace_all_distinct(temphtmlname, " ", "_");
			replace_all_distinct(temphtmlname, ":", "_");
			temptime += temphtmlname;
			temptime += ">";
			temptime += starttime;
			temptime += "~";
			temptime += endtime;
			//链接文件名
			temptime += "</a>";				
			//WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)pMonitorListTable->elementAt(num, 0));			
			//WText * pSection = new WText(temptime, (WContainerWidget*)pMonitorListTable -> elementAt(num, 1));
			//pMonitorListTable -> elementAt(num, 0) ->setContentAlignment(AlignTop | AlignCenter);
			//pMonitorListTable -> elementAt(num, 1) ->setContentAlignment(AlignTop | AlignCenter);
			m_pReportListTable->InitRow(numRow);
			WCheckBox * pCheck = new WCheckBox("", m_pReportListTable->GeDataTable()->elementAt(numRow, 0));
			m_pReportListTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignTop | AlignCenter);
			WText * pSection = new WText(temptime, m_pReportListTable->GeDataTable()->elementAt(numRow, 2));
			m_pReportListTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignTop | AlignCenter);

			_LIST list;
			list.pSelect = pCheck;
			list.pSection = pSection;
			list.szSection = mapstr;

			m_pList.push_back(list);

			num++;
			numRow++;
		}

		/*		
		if(strcmp(substr.c_str(), section.c_str()) == 0)
		{
			
			//属于该报告集
			GetIniFileKeys(tempsection, keylist, filename);
			num = InsertListRow(num,pos, section, tempsection, keylist, filename);
			nListNum = num;
			
		}
		*/
	}

	if(bNull)
	{
		//m_pReportListTable->HideNullTip();
		//WText *nText = new WText(sztListEmpty, (WContainerWidget*)pMonitorListTable -> elementAt(2, 1));	
		//nText ->decorationStyle().setForegroundColor(Wt::red);
		//pMonitorListTable -> elementAt(2, 1) ->setContentAlignment(AlignTop | AlignCenter);
	}
}


//手工生成报告
void CTopnReportList::FastGenReport()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TopNReportList";
	LogItem.sHitFunc = "FastGenReport";
	LogItem.sDesc = szCreateImm;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	std::string szdaystarttime; std::string szdayendtime;
	std::string szReportName;

	std::string strCmdLine;
	SECURITY_ATTRIBUTES sa;	
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	
	HANDLE hRead, hWrite;

	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	//si.hStdOutput = hWrite;
	//si.hStdError = hWrite;
	si.wShowWindow =SW_HIDE;
	
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	std::string ret = "error";
	if(!querystr.empty())
	{		
		std::string szPeriod = GetIniFileString(querystr, "Period", ret, "topnreportset.ini");
		svutil::TTime dayendtime = svutil::TTime::GetCurrentTimeEx();
		svutil::TTime daystarttime;

		std::string szGenNum = GetIniFileString(querystr, "Count", ret, "topnreportset.ini");


		if(strcmp(szPeriod.c_str(), "error") != 0)
		{
			if(strcmp(szPeriod.c_str(), szReportDay.c_str()) == 0)
			{				
				daystarttime = dayendtime - svutil::TTimeSpan(1, 0, 0, 0);				
			}
			else if(strcmp(szPeriod.c_str(), szReportWeek.c_str()) == 0)
			{
				daystarttime = dayendtime - svutil::TTimeSpan(7, 0, 0, 0);
			}
			else if(strcmp(szPeriod.c_str(), szReportMonth.c_str()) == 0)
			{
				if(dayendtime.GetMonth() == 1)
				{
					daystarttime = svutil::TTime(dayendtime.GetYear() - 1, 12, dayendtime.GetDay() , dayendtime.GetHour(), dayendtime.GetMinute(), dayendtime.GetSecond());
				}
				else
				{
					daystarttime = svutil::TTime(dayendtime.GetYear(), dayendtime.GetMonth() - 1, dayendtime.GetDay() , dayendtime.GetHour(), dayendtime.GetMinute(), dayendtime.GetSecond());
				}
				
			}
			
			std::string szRootPath = GetSiteViewRootPath();
			strCmdLine = szRootPath;
			strCmdLine += "\\fcgi-bin\\topnreport.exe ";
				
			szdaystarttime = daystarttime.Format();
			szdaystarttime = replace_all_distinct(szdaystarttime, " ", "_");
			szdaystarttime = replace_all_distinct(szdaystarttime, ":", "_");
			strCmdLine += szdaystarttime;
			strCmdLine += " ";

			szdayendtime = dayendtime.Format();
			szdayendtime = replace_all_distinct(szdayendtime, " ", "_");
			szdayendtime = replace_all_distinct(szdayendtime, ":", "_");
			strCmdLine += szdayendtime;
			strCmdLine += " ";

			replace_all_distinct(querystr, " ", "%20");
			strCmdLine += querystr;
			strCmdLine += " ";

			szReportName = szdaystarttime;
			szReportName += szdayendtime;
			szReportName += querystr;
			szReportName += ".html";

			replace_all_distinct(szReportName, "*", "_");
			replace_all_distinct(szReportName, "/", "_");
			replace_all_distinct(szReportName, "\\", "_");
			replace_all_distinct(szReportName,"?", "_");
			replace_all_distinct(szReportName,  "|", "_");
			replace_all_distinct(szReportName,  "<", "_");
			replace_all_distinct(szReportName,  ">", "_");
			replace_all_distinct(szReportName,  ":", "_");
			replace_all_distinct(szReportName,  "\"", "_");
			replace_all_distinct(szReportName,  " ", "_");
			replace_all_distinct(szReportName,  "%20", "_");

			strCmdLine += szReportName;		

			strCmdLine += " ";
			strCmdLine += szGenNum;
				
			if (CreateProcess(NULL,(LPSTR) strCmdLine.c_str(),  &sa, &sa, TRUE, CREATE_NEW_CONSOLE/*CREATE_NO_WINDOW*/, NULL, NULL, &si, &pi)) 
			{
				
			}
			else
			{
					
			}
			WaitForSingleObject( pi.hProcess, INFINITE );

			// Close process and thread handles. 
			CloseHandle( pi.hProcess );
			CloseHandle( pi.hThread );

			//跳转到生成报告页面
			/*std::string openurl = "hiddenbar();window.open('../report/";
			openurl += szReportName;
			openurl += "')";
			*/
			std::string openurl = "hiddenbar();location.href='../topnreport/";
			openurl += szReportName;
			openurl += "'";

			WebSession::js_af_up = openurl;
		
			/*
			pMonitorListTable->setStyleClass("StatsTable1");
			pMonitorListTable->tableprop_ = 2;
			pMonitorListTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
			pMonitorListTable->setCellSpaceing(10);*/

			std::string tempsection = szReportName;
			tempsection += "$";
			tempsection += szdaystarttime;
			tempsection += "$";
			tempsection += szdayendtime;
			tempsection += "$";			
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CTopnReportList::refresh()
{
	//pMonitorListTable->clear();
	//colname1.clear();
	//m_pList.clear();

	//new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);		
	////AddColum(NULL);
	m_pReportListTable->GeDataTable()->clear();
	colname1.clear();
	m_pList.clear();

	//new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	NewAddColum();

	if(m_pList.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
		}
		else
		{
			m_pReportListTable->HideNullTip();
		}
}


std::list<string>  CTopnReportList::ReadFileName(string path)
{
	WIN32_FIND_DATA fd;
	std::list<string> strlist;

	path += "\\*.*";

    HANDLE fr=::FindFirstFile(path.c_str(),&fd);

    while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{

		}
        else
		{
			std::list<string> keylist;
			std::list<string>::iterator itemkey;
			bool bret = GetIniFileKeys("filename", keylist, "tuopfile.ini");
			if(!bret)
			{
			}

			bool bExist = false;
			for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
			{
				std::string str = *itemkey;
				if(strcmp(str.c_str(), fd.cFileName) == 0)
				{
					bExist = true;
					break;
				}
			}

			if(bExist)
			{
				std::string defaultret = "error";
				std::string sret = GetIniFileString("filename", fd.cFileName, defaultret, "tuopfile.ini");
				strlist.push_back(sret);
			}
			else
			{
				std::string str1 = fd.cFileName;
				int npos = str1.find(".htm", 0);
				if(npos >= 0)
				{
					WriteIniFileString("filename", fd.cFileName, fd.cFileName, "tuopfile.ini");
					strlist.push_back(fd.cFileName);
				}
			}	
		}
    }
	return strlist;
}


void CTopnReportList::SelAll()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
    {
		OutputDebugString("-----------topn report list select all output------------\n");
		m_pListItem->pSelect->setChecked(true);
    }
}

void CTopnReportList::SelNone()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(false);
    }
}
void CTopnReportList::SelInvert()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
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


void CTopnReportList::BeforeDelList()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TopNReportList";
	LogItem.sHitFunc = "BeforeDelList";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem++)
	{
		if (m_pListItem->pSelect->isChecked())
		{   
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + szDeleteAffirmInfo + "','" + szButNum + "','" + szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;	
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CTopnReportList::DelList()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TopNReportList";
	LogItem.sHitFunc = "FastGenReport";
	LogItem.sDesc = strDelList;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
    {
        
        if (m_pListItem->pSelect->isChecked())
        {   
			int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();

			DeleteIniFileSection(m_pListItem->szSection, "topnreportgenerate.ini");

			list<_LIST>::iterator pItem = m_pListItem;                     

			m_pListItem --;

			m_pList.erase(pItem);

			m_pReportListTable->GeDataTable()->deleteRow(nRow); 
        }
    }

		if(m_pList.size() <= 0)
		{
			m_pReportListTable->ShowNullTip();
		}
		else
		{
			m_pReportListTable->HideNullTip();
		}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CTopnReportList::ReturnMainTopnReport()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TopNReportList";
	LogItem.sHitFunc = "ReturnMainTopnReport";
	LogItem.sDesc = strReturn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	std::string openurl = "hiddenbar();location.href ='/fcgi-bin/topnreportset.exe?'";
	WebSession::js_af_up = openurl;

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CTopnReportList::AddGroupOperate(WTable * pTable)
{
    m_pGroupOperate = new WTable((WContainerWidget *)pTable->elementAt( 3, 0));
    if ( m_pGroupOperate )
    {

        WImage * pSelAll = new WImage("../Images/selall.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
        if (pSelAll)
        {
            pSelAll->setStyleClass("imgbutton");
			pSelAll->setToolTip(m_formText.szTipSelAll1);
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

        WImage * pSelNone = new WImage("../Images/selnone.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
        if (pSelAll)
        {
            pSelNone->setStyleClass("imgbutton");
			pSelNone->setToolTip(m_formText.szTipSelNone);
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

        WImage * pSelinvert = new WImage("../Images/selinvert.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
        if (pSelinvert)
        {
            pSelinvert->setStyleClass("imgbutton");
			pSelinvert->setToolTip(m_formText.szTipSelInv);
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		WImage * pDel = new WImage("../Images/del.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 4));		

        if (pDel)
        {
           
			pDel->setStyleClass("imgbutton");
			pDel->setToolTip(m_formText.szTipDel);
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelList()));
        }

		
		m_pGroupOperate->elementAt(0, 6)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
		m_pGroupOperate->elementAt(0, 6)->setContentAlignment(AlignRight);
    }

	//隐藏按钮
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelList()));
		pHideBut->hide();
	}
}


typedef void(*func)(int , char **);

//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
 	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Total_Report_List",title);
		CloseResource(objRes);
	}

	WApplication app(argc, argv);
	app.setTitle(title.c_str());
	
    CTopnReportList setform(app.root());
	setform.appSelf = &app;
    app.exec();
}


int main(int argc, char *argv[])
{
    func p = usermain;
	if (argc == 1) 
    {
        char buf[256];
		
		WebSession s(buf, false);
        s.start(p);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }
    return 0;
}


