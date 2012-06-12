#include ".\simplereport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"


#include "include\chartdir.h"


#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
#include "WFont"
//ui
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"

#include <atlconv.h>

//#define WTGET

CSimpleReport::CSimpleReport(WContainerWidget *parent ):
WContainerWidget(parent)
{
	SetSvdbAddrByFile("svapi.ini");

	//////////////////modify at 07/07/31
	SetCgiVersionByFile("svapi.ini");
	///////////////////////////////////
	
	string keys = "IDS_Simple_Report,\
		,IDS_Simple_Report_List,\
		,IDS_Name,\
		,IDS_Simple_Report_Map,\
		,IDS_Edit_Name,\
		,IDS_Affirm_Delete_User,\
		,IDS_SiteView_Copyright,\
		,IDS_Report_Table,\
		,IDS_Simple_Report_Caption,\
		,IDS_MonitorTitle,\
		,IDS_Total,\
		,IDS_Map_Table,\
		,IDS_Total_Report,\
		,IDS_Name,\
		,IDS_Normal,\
		,IDS_Warning,\
		,IDS_Error,\
		,IDS_Disable,\
		,IDS_Clique_Value,\
		,IDS_Name,\
		,IDS_Return_Value,\
		,IDS_Max_Value,\
		,IDS_Average_Value,\
		,IDS_Run_Case_Table,\
		,IDS_Alert_Date_Total_Table,\
		,IDS_Error,\
		,IDS_Name,\
		,IDS_Run_Time_Normal,\
		,IDS_Warning,\
		,IDS_Error,\
		,IDS_Later,\
		,IDS_Name,\
		,IDS_Measure,\
		,IDS_Max,\
		,IDS_Average,\
		,IDS_Later_Time,\
		,IDS_Name,\
		,IDS_Start_Time1,\
		,IDS_End_Time2,\
		,IDS_State,\
		,IDS_Time,\
		,IDS_Name,\
		,IDS_Description,\
		,IDS_Time_Period,\
		,IDS_Min_Value,\
		,IDS_Alert_Count,\
		,IDS_Normal_Count,\
		,IDS_Danger_Count,\
		,IDS_Error_Count,\
		,IDS_Disable_Count,\
		,IDS_Translate,\
		,IDS_Translate_Tip,\
		,IDS_Refresh,\
		,IDS_Refresh_Tip,\
		,IDS_TimePeriod,\
		,IDS_IDC_COPY_RIGHT,";

	objRes=LoadResourceByKeys(keys,"default", "localhost");	
	//Resource
	//objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Simple_Report",strMainTitle);
			FindNodeValue(ResNode,"IDS_Simple_Report_List",strTitle);
			FindNodeValue(ResNode,"IDS_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Simple_Report_Map",strNameUse);
			FindNodeValue(ResNode,"IDS_Edit_Name",strNameEdit);
			FindNodeValue(ResNode,"IDS_Affirm_Delete_User",strDel);
			FindNodeValue(ResNode,"IDS_SiteView_Copyright",strCorporateName);
			FindNodeValue(ResNode,"IDS_Report_Table",strReportTitle);
			FindNodeValue(ResNode,"IDS_Simple_Report_Caption",m_formText.szCaption1);
			FindNodeValue(ResNode,"IDS_MonitorTitle",m_formText.szSimpleMonitorTitle);
			FindNodeValue(ResNode,"IDS_Total",m_formText.szSimpleStatsTitle);
			FindNodeValue(ResNode,"IDS_Map_Table",m_formText.szSimpleImageTitle);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szSimpleMonitorName);
			FindNodeValue(ResNode,"IDS_Normal",m_formText.szSimpleMonitorNormal);
			FindNodeValue(ResNode,"IDS_Warning",m_formText.szSimpleMonitorDanger);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szSimpleMonitorError);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szSimpleMonitorDisable);
			FindNodeValue(ResNode,"IDS_Clique_Value",m_formText.szSimpleMonitorClicket);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szSimpleStatsName);
			FindNodeValue(ResNode,"IDS_Return_Value",m_formText.szSimpleStatsReturn);
			FindNodeValue(ResNode,"IDS_Max_Value",m_formText.szSimpleStatsMax);
			FindNodeValue(ResNode,"IDS_Average_Value",m_formText.szSimpleStatsPer);
			FindNodeValue(ResNode,"IDS_Run_Case_Table",m_formText.szRunTitle);
			FindNodeValue(ResNode,"IDS_Alert_Date_Total_Table",m_formText.szMonitorTitle);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szErrorTitle);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szRunName);
			FindNodeValue(ResNode,"IDS_Run_Time_Normal",m_formText.szRunTime);
			FindNodeValue(ResNode,"IDS_Warning",m_formText.szRunDanger);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szRunError);
			FindNodeValue(ResNode,"IDS_Later",m_formText.szRunNew);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szMonName);
			FindNodeValue(ResNode,"IDS_Measure",m_formText.szMonMeasure);
			FindNodeValue(ResNode,"IDS_Max",m_formText.szMonMax);
			FindNodeValue(ResNode,"IDS_Average",m_formText.szMonPer);
			FindNodeValue(ResNode,"IDS_Later_Time",m_formText.szMonLast);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szErrName);
			FindNodeValue(ResNode,"IDS_Start_Time1",m_formText.szErrStartTime);
			FindNodeValue(ResNode,"IDS_End_Time2",m_formText.szErrEndTime);
			FindNodeValue(ResNode,"IDS_State",m_formText.szErrStatus);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szEDNTime);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szEDNName);
			FindNodeValue(ResNode,"IDS_Description",m_formText.szEDNDescription);
			FindNodeValue(ResNode,"IDS_Time_Period",szInterTime1);
			FindNodeValue(ResNode,"IDS_Min_Value",szMinValue);
			FindNodeValue(ResNode,"IDS_Alert_Count",szAlertCount);
			FindNodeValue(ResNode,"IDS_Normal_Count",strNormalCount);
			FindNodeValue(ResNode,"IDS_Danger_Count",strDangerCount);
			FindNodeValue(ResNode,"IDS_Error_Count",strErrorCount);
			FindNodeValue(ResNode,"IDS_Disable_Count",strDisableCount);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_TimePeriod",m_formText.szTimePeriod);
			
			//IDS_IDC_COPY_RIGHT = 中国网通(集团)有限公司北京市分公司 版权所有
			FindNodeValue(ResNode,"IDS_IDC_COPY_RIGHT",m_formText.szIDCCopyRight);
		}
	}

	/*
	strMainTitle ="简单报告";
	strTitle ="简单报告列表";

	strLoginLabel = "名 称";	
	strNameUse = "简单报告图";
	strNameEdit="编辑名称";

	strNameTest="游龙科技";
	strDel=  "确认删除选中用户吗？";

	strCorporateName = "Copyright SiteView";
	strReportTitle = "报表";
	*/

	reporttitletext = NULL;
	intertimetitle = NULL;
	monitorcounttitle = NULL;

	ShowMainTable();
}

CSimpleReport::~CSimpleReport(void)
{
	CloseResource(objRes);
}

void CSimpleReport::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	pContainTable = new WTable(this);
	pContainTable->setStyleClass("t5");
	WFont font1;
	font1.setFamily(WFont::Default, "Arial");
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	//#############################################################################################juxian.zhang--------------200701006	

	m_pContainTable = new WSVMainTable(this,strMainTitle,false);	

	namesTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(1,0),Query,"",false);

	detTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(2,0),List,m_formText.szSimpleMonitorTitle);

	if(detTable->GetContentTable()!=NULL)
	{

		detTable->AppendColumn(m_formText.szSimpleMonitorName,WLength(30,WLength::Percentage));
		detTable->SetDataRowStyle("table_data_grid_item_text");
		detTable->AppendColumn(m_formText.szSimpleMonitorNormal + "(%)",WLength(10,WLength::Percentage));
		detTable->SetDataRowStyle("table_data_grid_item_text");
		detTable->AppendColumn(m_formText.szSimpleMonitorDanger + "(%)",WLength(10,WLength::Percentage));
		detTable->SetDataRowStyle("table_data_grid_item_text");
		detTable->AppendColumn(m_formText.szSimpleMonitorError + "(%)",WLength(10,WLength::Percentage));
		detTable->SetDataRowStyle("table_data_grid_item_text");
		detTable->AppendColumn(m_formText.szSimpleMonitorDisable + "(%)",WLength(10,WLength::Percentage));
		detTable->SetDataRowStyle("table_data_grid_item_text");
		detTable->AppendColumn(m_formText.szSimpleMonitorClicket,WLength(30,WLength::Percentage));
		detTable->SetDataRowStyle("table_data_grid_item_text");

	}//Pixel

	statTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(3,0),List,m_formText.szSimpleStatsTitle);
	if(statTable->GetContentTable()!=NULL)
	{

		statTable->AppendColumn(m_formText.szSimpleStatsName,WLength(30,WLength::Percentage));
		statTable->SetDataRowStyle("table_data_grid_item_img");
		statTable->AppendColumn(m_formText.szSimpleStatsReturn ,WLength(25,WLength::Percentage));
		statTable->SetDataRowStyle("table_data_grid_item_img");
		statTable->AppendColumn(m_formText.szSimpleStatsMax + "(%)",WLength(25,WLength::Percentage));
		statTable->SetDataRowStyle("table_data_grid_item_img");
		statTable->AppendColumn(m_formText.szSimpleStatsPer + "(%)",WLength(20,WLength::Percentage));
		statTable->SetDataRowStyle("table_data_grid_item_text");


	}

	ImageTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(4,0),Query,m_formText.szSimpleImageTitle);

	ErrorTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(5,0),List,m_formText.szSimpleMonitorError);
	if (ErrorTable->GetContentTable()!=NULL)
	{
		ErrorTable->AppendColumn(m_formText.szEDNTime,WLength(20,WLength::Percentage));
		ErrorTable->SetDataRowStyle("table_data_grid_item_img");
		ErrorTable->AppendColumn(m_formText.szEDNName,WLength(40,WLength::Percentage));
		ErrorTable->SetDataRowStyle("table_data_grid_item_img");
		ErrorTable->AppendColumn(m_formText.szEDNDescription,WLength(40,WLength::Percentage));
		ErrorTable->SetDataRowStyle("table_data_grid_item_img");
	}

	DangerTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(6,0),List,m_formText.szSimpleMonitorDanger);
	if (DangerTable->GetContentTable()!=NULL)
	{
		DangerTable->AppendColumn(m_formText.szEDNTime,WLength(20,WLength::Percentage));
		DangerTable->SetDataRowStyle("table_data_grid_item_img");
		DangerTable->AppendColumn(m_formText.szEDNName,WLength(40,WLength::Percentage));
		DangerTable->SetDataRowStyle("table_data_grid_item_img");
		DangerTable->AppendColumn(m_formText.szEDNDescription,WLength(40,WLength::Percentage));
		DangerTable->SetDataRowStyle("table_data_grid_item_img");
	}

	NormalTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(7,0),List,m_formText.szSimpleMonitorNormal);
	if (NormalTable->GetContentTable()!=NULL)
	{

		NormalTable->AppendColumn(m_formText.szEDNTime,WLength(20,WLength::Percentage));
		NormalTable->SetDataRowStyle("table_data_grid_item_img");
		NormalTable->AppendColumn(m_formText.szEDNName,WLength(40,WLength::Percentage));
		NormalTable->SetDataRowStyle("table_data_grid_item_text");
	}

	DisableTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(8,0),List,m_formText.szSimpleMonitorDisable);
	if (DisableTable->GetContentTable()!= NULL)
	{
		DisableTable->AppendColumn(m_formText.szEDNTime,WLength(20,WLength::Percentage));
		DisableTable->SetDataRowStyle("table_data_grid_item_img");
		DisableTable->AppendColumn(m_formText.szEDNName,WLength(40,WLength::Percentage));
		DisableTable->SetDataRowStyle("table_data_grid_item_img");
		DisableTable->AppendColumn(m_formText.szEDNDescription,WLength(40,WLength::Percentage));
		DisableTable->SetDataRowStyle("table_data_grid_item_img");
	}

	newBottomTitle = new WText(strCorporateName, m_pContainTable->GetContentTable()->elementAt(9, 0));
	m_pContainTable->GetContentTable()->elementAt(9, 0)->setContentAlignment(AlignTop | AlignCenter);
	newBottomTitle->decorationStyle().setForegroundColor(Wt::blue);

	pContainTable->hide();


	//#############################################################################################juxian.zhang--------------200701006	

	WText * text1 = new WText(m_formText.szSimpleMonitorTitle, pContainTable->elementAt(2, 0));
	text1 ->decorationStyle().setFont(font1);
	pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pContainTable->elementAt(2, 0));

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)pContainTable->elementAt(2, 0));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
	pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pContainTable->elementAt(2, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)pContainTable->elementAt(2, 0));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip);
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

	pContainTable->elementAt(4, 0)->setContentAlignment(AlignTop | AlignCenter);
	pSimpleMonitorTable = new WTable(pContainTable->elementAt(4, 0));
	pSimpleMonitorTable->setStyleClass("StatsTable");	
	pSimpleMonitorTable->tableprop_ = 2;
	pSimpleMonitorTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";


	text1 = new WText(m_formText.szSimpleStatsTitle, pContainTable->elementAt(5, 0));
	text1 ->decorationStyle().setFont(font1);

	pContainTable->elementAt(5, 0) ->setContentAlignment(AlignTop | AlignCenter);
	pContainTable->elementAt(6, 0) ->setContentAlignment(AlignTop | AlignCenter);
	pSimpleStatsTable = new WTable(pContainTable ->elementAt(6, 0));
	pSimpleStatsTable->setStyleClass("StatsTable");	
	pSimpleStatsTable->tableprop_ = 2;
	pSimpleStatsTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";

	text1 = new WText(m_formText.szSimpleImageTitle, pContainTable->elementAt(7, 0));
	text1 ->decorationStyle().setFont(font1);
	pContainTable ->elementAt(7, 0) ->setContentAlignment(AlignTop | AlignCenter);

	pImageTable = new WTable(pContainTable->elementAt(8 , 0));
	pContainTable ->elementAt(8, 0) ->setContentAlignment(AlignTop | AlignCenter);

	text1 = new WText(m_formText.szSimpleMonitorError, pContainTable->elementAt(9, 0));
	text1 ->decorationStyle().setFont(font1);
	pContainTable->elementAt(9,0)->setContentAlignment(AlignTop | AlignCenter);
	pErrorTable = new WTable(pContainTable->elementAt(10 , 0));
	pContainTable->elementAt(10, 0)->setContentAlignment(AlignTop | AlignCenter);
	pErrorTable->setStyleClass("StatsTable");	
	pErrorTable->tableprop_ = 2;
	pErrorTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";

	text1 = new WText(m_formText.szSimpleMonitorDanger , pContainTable->elementAt(11, 0));
	pContainTable->elementAt(11, 0) ->setContentAlignment(AlignTop | AlignCenter);
	text1 ->decorationStyle().setFont(font1);
	pDangerTable = new WTable(pContainTable->elementAt(12 , 0));
	pContainTable->elementAt(12, 0)->setContentAlignment(AlignTop | AlignCenter);
	pDangerTable->setStyleClass("StatsTable");	
	pDangerTable->tableprop_ = 2;
	pDangerTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";

	text1 = new WText(m_formText.szSimpleMonitorNormal, pContainTable->elementAt(13, 0));
	pContainTable->elementAt(13, 0) ->setContentAlignment(AlignTop | AlignCenter);
	text1 ->decorationStyle().setFont(font1);
	pNormalTable = new WTable(pContainTable->elementAt(14 , 0));
	pContainTable->elementAt(14, 0)->setContentAlignment(AlignTop | AlignCenter);
	pNormalTable->setStyleClass("StatsTable");	
	pNormalTable->tableprop_ = 2;
	pNormalTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";

	text1 = new WText(m_formText.szSimpleMonitorDisable, pContainTable->elementAt(15, 0));
	pContainTable->elementAt(15, 0) ->setContentAlignment(AlignTop | AlignCenter);
	text1 ->decorationStyle().setFont(font1);
	pDisableTable = new WTable(pContainTable->elementAt(16 , 0));
	pContainTable->elementAt(16, 0)->setContentAlignment(AlignTop | AlignCenter);
	pDisableTable->setStyleClass("StatsTable");	
	pDisableTable->tableprop_ = 2;
	pDisableTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";


	bottomTitle = new WText(strCorporateName, pContainTable->elementAt(17, 0));
	bottomTitle ->decorationStyle().setFont(font1);
	pContainTable->elementAt(17, 0)->setContentAlignment(AlignTop | AlignCenter);
	bottomTitle->decorationStyle().setForegroundColor(Wt::blue);

	std::list<string> listtype;
	OBJECT hTemplet;
	string value;
	std::string querystr;
	std::string monitorname;
	std::string strMonType = "";

	char buf_tmp[4096]={0};
	int nSize =4095;
	std::string strFreq;
	int nFreq;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
	char *tmpquery = getenv("QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif

	
	if(buf_tmp != NULL)
	{
		std::string buf1 = buf_tmp;
		int pos = buf1.find("=", 0);
		querystr = buf1.substr(pos+1, buf1.size() - pos - 1);		

		std::string str = querystr;
		std::list<struct sv_pair>::iterator svitem ;		

		LISTITEM item;
		MAPNODE objNode;

		std::string strFreqUnit;
		bool bRet = GetMonitorParaValueByName(str,"_frequency",strFreq);
		GetMonitorParaValueByName(str, "_frequencyUnit", strFreqUnit);
		if(bRet)
		{
			if(strFreq.empty())
			{
				nFreq = 36;
			}
			else
			{
				nFreq = atoi(strFreq.c_str());
			}

		}
		else
		{
			nFreq = 36;
		}


		hMon = Cache_GetMonitor(str);
		m_monitorID = str;
		if(hMon != INVALID_VALUE)
		{
			std::string getvalue;

			MAPNODE ma=GetMonitorMainAttribNode(hMon) ;

			if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
			{
				strMonType = getvalue;
				hTemplet = Cache_GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				FindNodeValue(node, "sv_label", monitorname);
				//监测器阀值
				std::string szErrorValue;
				MAPNODE errorNode = GetMTErrorAlertCondition(hTemplet);
				FindNodeValue(errorNode, "sv_value", szErrorValue);
				new WText(szErrorValue.c_str(), pSimpleMonitorTable->elementAt(1, 5));	

			}
			else
			{
				return;
			}



			bRet = FindMTReturnFirst(hTemplet, item);

			if(bRet)
			{
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					FindNodeValue(objNode, "sv_label", value);
					liststr.push_back(value);	
					FindNodeValue(objNode, "sv_type", value);				
					listtype.push_back(value);
				}
			}	
		}
		//CloseMonitor(hMon);
	}

	svutil::TTime end = svutil::TTime::GetCurrentTimeEx();

	MAPNODE node = GetMTMainAttribNode(hTemplet);
	std::string ;
	FindNodeValue(node, "sv_label", value);
	//简单报表标题
	WFont font;
	font.setFamily(WFont::Default, "Arial");
	font.setSize(WFont::Large, WLength(60,WLength::Pixel));

	MAPNODE mnode = GetMTMainAttribNode(hMon);
	std::string val;
	FindNodeValue(mnode, "sv_name", val);

	std::string reportstr = strReportTitle;
	reportstr += val;
	//reporttitletext = new WText(reportstr, pContainTable->elementAt(0, 0));

	//#################################################################################-----------juxian.zhang
	reporttitletext = new WText(reportstr, namesTable->GetContentTable()->elementAt(0,0));
	namesTable->GetContentTable()->elementAt(0,0)->setContentAlignment(AlignTop | AlignCenter);
	reporttitletext->setText(reportstr);

	reporttitletext->decorationStyle().setFont(font);
	pContainTable->elementAt(0, 0) ->setContentAlignment(AlignTop | AlignCenter);


	int nHourFreq = (nFreq*40)/60;
	int nMinuteFreq = (nFreq*40)%60;
	svutil::TTime beftime = end - svutil::TTimeSpan(0, nHourFreq, nMinuteFreq, 0);		
	OutputDebugString(beftime.Format().c_str());

	szInterTime1 += beftime.Format();
	szInterTime1 += "~";
	szInterTime1 += end.Format();
	//intertimetitle = new WText(szInterTime1, pContainTable->elementAt(1, 0));
	//
	//pContainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);

	OutputDebugString("In ShowMainTable...");

	intertimetitle = new WText (szInterTime1, namesTable->GetContentTable()->elementAt(1,0));

	new WText ("&nbsp;&nbsp;&nbsp;&nbsp;", namesTable->GetContentTable()->elementAt(2,0));
	pOkBtn = new WPushButton("确定", namesTable->GetContentTable()->elementAt(2,1));
	namesTable->GetContentTable()->elementAt(2,0)->setContentAlignment(AlignMiddle | AlignRight);
	connect(pOkBtn, SIGNAL(clicked()), this, SLOT(AddNum()));
	pInitBtn = new WPushButton("清除", namesTable->GetContentTable()->elementAt(2,2));
	namesTable->GetContentTable()->elementAt(2,0)->setContentAlignment(AlignMiddle | AlignRight);
	connect(pInitBtn, SIGNAL(clicked()), this, SLOT(InitNum()));
//	pTranslateBtn->setToolTip("点击一下，少一行错误");
	
	
	if (strMonType != "35" && strMonType != "23")
	{
		pOkBtn->hide();
		pInitBtn->hide();
		OutputDebugString("++++++++++++++hide ini++++++++++++");
	}
	else
	{
		pOkBtn->show();
		pInitBtn->show();
		OutputDebugString("++++++++++++++hide show++++++++++++");
	}

	namesTable->GetContentTable()->elementAt(1,0)->setContentAlignment(AlignTop | AlignCenter);
	if(hMon != INVALID_VALUE)
	{
		OutputDebugString("------------- in hMon != INVALID_VALUE ------------");
		DataUpdate();
	}		
}

//加列标题
void CSimpleReport::AddColum(list<string> fieldlist, WTable* pContain)
{	
	new WText(m_formText.szSimpleMonitorName, pSimpleMonitorTable->elementAt(0, 0));
	new WText(m_formText.szSimpleMonitorNormal + "(%)", pSimpleMonitorTable->elementAt(0, 1));	
	new WText(m_formText.szSimpleMonitorDanger + "(%)", pSimpleMonitorTable->elementAt(0, 2));
	new WText(m_formText.szSimpleMonitorError + "(%)", pSimpleMonitorTable->elementAt(0, 3));
	new WText(m_formText.szSimpleMonitorDisable + "(%)", pSimpleMonitorTable->elementAt(0, 4));
	new WText(m_formText.szSimpleMonitorClicket, pSimpleMonitorTable->elementAt(0, 5));
	pSimpleMonitorTable->setCellSpaceing(0);
	pSimpleMonitorTable->GetRow(0) ->setStyleClass("t1title");

	new WText(m_formText.szSimpleStatsName, pSimpleStatsTable->elementAt(0, 0));
	new WText(m_formText.szSimpleStatsReturn, pSimpleStatsTable->elementAt(0, 1));	
	new WText(m_formText.szSimpleStatsMax, pSimpleStatsTable->elementAt(0, 2));	
	new WText(m_formText.szSimpleStatsPer, pSimpleStatsTable->elementAt(0, 3));	
	pSimpleStatsTable->setCellSpaceing(0);
	pSimpleStatsTable->GetRow(0)->setStyleClass("t1title");

	new WText(m_formText.szEDNTime, pErrorTable->elementAt(0, 0));
	new WText(m_formText.szEDNName, pErrorTable->elementAt(0, 1));
	new WText(m_formText.szEDNDescription, pErrorTable->elementAt(0, 2));
	pErrorTable->setCellSpaceing(0);
	pErrorTable->GetRow(0)->setStyleClass("t1title");

	new WText(m_formText.szEDNTime, pDangerTable->elementAt(0, 0));
	new WText(m_formText.szEDNName, pDangerTable->elementAt(0, 1));
	new WText(m_formText.szEDNDescription, pDangerTable->elementAt(0, 2));
	pDangerTable->setCellSpaceing(0);
	pDangerTable->GetRow(0)->setStyleClass("t1title");

	//取数据记录集字段名作为正常列表列名
	list<string>::iterator fielditem;

	new WText(m_formText.szEDNTime, pNormalTable->elementAt(0, 0));
	new WText(m_formText.szEDNName, pNormalTable->elementAt(0, 1));
	//new WText(m_formText.szEDNDescription, pNormalTable->elementAt(0, 2));

	NormalTable->clear();
	NormalTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(7,0),List,m_formText.szSimpleMonitorNormal);
	if (NormalTable->GetContentTable()!=NULL)
	{

		NormalTable->AppendColumn(m_formText.szEDNTime,WLength(20,WLength::Percentage));
		NormalTable->SetDataRowStyle("table_data_grid_item_img");
		NormalTable->AppendColumn(m_formText.szEDNName,WLength(20,WLength::Percentage));
		NormalTable->SetDataRowStyle("table_data_grid_item_text");
	}
	int Size = fieldlist.size();
	for(fielditem = fieldlist.begin(); fielditem != fieldlist.end(); fielditem++)
	{

		NormalTable->GetContentTable()->clear;
		//NormalTable->AppendColumn(GetLabelResource(*fielditem),WLength(60/Size,WLength::Percentage));
		NormalTable->AppendColumn((*fielditem),WLength(60/Size,WLength::Percentage));
		NormalTable->SetDataRowStyle("table_data_grid_item_text");
	}

	int j = 2;
	for(fielditem = fieldlist.begin(); fielditem != fieldlist.end(); fielditem++)
	{
		new WText(*fielditem, pNormalTable->elementAt(0, j));
		j++;
	}




	pNormalTable->setCellSpaceing(0);
	pNormalTable->GetRow(0)->setStyleClass("t1title");

	new WText(m_formText.szEDNTime, pDisableTable->elementAt(0, 0));

	new WText(m_formText.szEDNName, pDisableTable->elementAt(0, 1));
	new WText(m_formText.szEDNDescription, pDisableTable->elementAt(0, 2));
	pDisableTable->setCellSpaceing(0);
	pDisableTable->GetRow(0)->setStyleClass("t1title");




}


//
void CSimpleReport::refresh()
{				
	TableClear();
	//	AddColum(grset, NULL);
	DataUpdate();	

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

	char buf_tmp[4096]={0};
	int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
	char *tmpquery = getenv("QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
	if(buf_tmp != NULL)
	{
		OutputDebugString(buf_tmp);

		std::string buf1 = buf_tmp;
		int pos = buf1.find("=", 0);
		querystr1 = buf1.substr(pos+1, buf1.size() - pos - 1);
	}
	OutputDebugString(querystr1.c_str());
}
//

void CSimpleReport::AddNum()
{
	string iniFileName = "..\\data\\TmpIniFile\\Confirms_" + m_monitorID + ".ini";
	TTime ct = TTime::GetCurrentTimeEx();
	char sectionName[10] = {0};
	sprintf(sectionName, "%d%02d%02d", ct.GetYear(), ct.GetMonth(), ct.GetDay());
	char strNum[50] = {0};
	GetPrivateProfileString(sectionName, "Times", "0", strNum, 49, iniFileName.c_str());
	int n = atoi(strNum);
	++n;
	memset(strNum, 0, 50);
	sprintf(strNum, "%d", n);
	WritePrivateProfileString(sectionName, "Times", strNum, iniFileName.c_str());
}

void CSimpleReport::InitNum()
{
	string iniFileName = "..\\data\\TmpIniFile\\Confirms_" + m_monitorID + ".ini";
	TTime ct = TTime::GetCurrentTimeEx();
	char sectionName[10] = {0};
	sprintf(sectionName, "%d%02d%02d", ct.GetYear(), ct.GetMonth(), ct.GetDay());
	WritePrivateProfileString(sectionName, "Times", "0", iniFileName.c_str());
}

void CSimpleReport::ExChange()
{
	string strNRefrsh = "setTimeout(\"location.href ='/fcgi-bin/SimpleReport.exe?id=";
	strNRefrsh += querystr1;
	strNRefrsh += "'\",1250);  ";

	WebSession::js_af_up = strNRefrsh ;
	appSelf->quit();
}
//
void CSimpleReport::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "SimpleReportRes";
	WebSession::js_af_up += "')";
}
void CSimpleReport::GenLineImage1(double data[], double time[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename)
{
	wchar_t lpWide[256];
	XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

	double *m_timeStamps = new double[1500];

	double timespan = endtime - starttime;
	double intertime = timespan/len;
	for(int i = 0; i < len; i++)
	{
		m_timeStamps[i] = starttime + intertime*i;
	}

	//c->setPlotArea(55, 50, 450*2, 220, 0xffffff, -1, 0xa08040, 0xa08040, 0xa08040);
	c->setPlotArea(55, 50, 260*2, 200, 0xffffff, -1, 0xa08040, c->dashLineColor(0x000000,
		0x000103), c->dashLineColor(0x000000, 0x000103));

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;
	setlocale(LC_CTYPE, ""); 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, Title, 256);
	//mbstowcs(lpWide, "aaa", 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
	c->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x1e5b99);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);
	//mbstowcs(lpWide, "aaaa", 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

	c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	//lpWideCharStr = L"Copyright SiteView";

	//lpWideCharStr = L"中国网通(集团)有限公司北京市分公司 版权所有";
	USES_CONVERSION;
	lpWideCharStr = A2W(m_formText.szIDCCopyRight.c_str());
	
	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

	if(yScale <= 10)
	{
		c->yAxis()->setLinearScale(0, yScale + 1);
	}
	else
	{
		c->yAxis()->setLinearScale(0, yScale);//设置垂直刻度
	}

	c->addScatterLayer(DoubleArray(time, len), DoubleArray(data, len),
		"", Chart::PolygonShape(0), 0, 0xffff00);

	//AreaLayer *layer = c->addAreaLayer();

	//layer ->setXData(DoubleArray(time, len));
	//layer->addDataSet(DoubleArray(data, len))->setDataColor(
	//	0x80d080, 0x007000);
	LineLayer *linelayer = c->addLineLayer(DoubleArray(data, len), 0x007000);
			
	linelayer->setXData(DoubleArray(time, len));

	c->makeChart(filename);

	free(lpMultiByteStr);
	delete [] m_timeStamps;

	delete c;
}

void CSimpleReport::GenLineImage(double data[],  int len, char* xlabels[],int xscalelen, int xStep, string ylabels[], int yscalelen, int yScale, int yStep, char* Title, char* xTitle, char * filename)
{    	
	wchar_t lpWide[256];
	XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

	c->setPlotArea(55, 36, 260*2, 200, 0xffffff, -1, 0xa08040, c->dashLineColor(0x000000,
		0x000103), c->dashLineColor(0x000000, 0x000103));

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;

	setlocale(LC_CTYPE, ""); 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, Title, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);


	//c->addTitle(lpMultiByteStr,
	//	"mingliu.ttc", 9, 0x1e5b99);//->setBackground(0xffffff, -1, 1);

	c->addTitle(lpMultiByteStr,
		"SIMFANG.ttf", 9, 0x1e5b99);//->setBackground(0xffffff, -1, 1);


	slen = 256;
	wlen = 256;
	memset(lpMultiByteStr, 0, 256);


	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

	c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	//lpWideCharStr = L"Copyright SiteView";

	lpWideCharStr = L"中国网通(集团)有限公司北京市分公司 版权所有";//没起作用的

	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

	if(yScale <= 10)
	{
		c->yAxis()->setLinearScale(0, yScale + 1);//设置垂直刻度
	}
	else
	{
		c->yAxis()->setLinearScale(0, yScale);
	}

	c->yAxis()->setLabelStep(yStep);

	c->xAxis()->setLabels(StringArray(xlabels, xscalelen));

	AreaLayer * layer = c->addAreaLayer();

	layer->addDataSet(DoubleArray(data, len))->setDataColor(
		0x80d080, 0x007000);

	c->makeChart(filename);

	delete c;
}

void CSimpleReport::GenPieImage(char * szTitle, char * labels[], double data[], int len, char * filename)
{

	PieChart *c = new PieChart(360, 300);

	c->setPieSize(180, 140, 100);
	c->addTitle(szTitle);
	c->set3D();
	c->setData(DoubleArray(data, len), StringArray(
		labels, len));
	c->setExplode(0);

	c->makeChart(filename);

	delete c;
}

void CSimpleReport::DataUpdate()
{
	//	std::list<string> liststr;
	liststr.clear();
	std::list<string> listtype;
	std::list<string> listunit;
	std::list<string> listimage;
	std::list<string> listtable;
	OBJECT hTemplet;
	string value;
	std::string querystr;
	std::string monitorname;

	
	std::string str;
	std::string monname;//监测器名称
	float perval = 0;
	float minval = 0;

	std::string rtitle;
	
	char szQuery[4096] = {0};
	char buf_tmp[4096]={0};
	int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
	char* tmpquery = getenv("QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
	if(buf_tmp != NULL)
	{
		std::string buf1 = buf_tmp;
		int pos = buf1.find("=", 0);
		querystr = buf1.substr(pos+1, buf1.size() - pos - 1);

		str = querystr;
		std::list<struct sv_pair>::iterator svitem ;		

		LISTITEM item;
		MAPNODE objNode;

		hMon = Cache_GetMonitor(str);
		m_monitorID = str;
		if(hMon != INVALID_VALUE)
		{
			std::string getvalue;

			MAPNODE ma=GetMonitorMainAttribNode(hMon) ;

			if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
			{
				if (getvalue != "35" && getvalue != "23")
				{
					pOkBtn->hide();
					pInitBtn->hide();
					OutputDebugString("++++++++++++++hide++++++++++++");
				}
				else
				{
					pOkBtn->show();
					pInitBtn->show();
					OutputDebugString("++++++++++++++show++++++++++++");
				}
				hTemplet = Cache_GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				FindNodeValue(node, "sv_label", monitorname);

				//监测器阀值
				std::string szErrorValue;
				MAPNODE errorNode = GetMTErrorAlertCondition(hTemplet);
				FindNodeValue(errorNode, "sv_value", szErrorValue);
				new WText(szErrorValue.c_str(), pSimpleMonitorTable->elementAt(1, 5));	
				detTable->GeDataTable()->elementAt(1,10)->setContentAlignment(AlignTop | AlignCenter);//List-------------juxian.zhang
				new WText(szErrorValue.c_str(), detTable->GeDataTable()->elementAt(1,10));
				string strEntity =	FindParentID(str);
				OBJECT hEntity = Cache_GetEntity(strEntity);
				MAPNODE entitynode = GetEntityMainAttribNode(hEntity);
				std::string entityvalue;
				FindNodeValue(entitynode, "sv_name", entityvalue);

				std::string val;
				FindNodeValue(ma, "sv_name", val);
				rtitle = entityvalue;
				rtitle += ":";
				rtitle += val;
				reporttitletext->setText(rtitle);			
			}
			else
			{
				return;
			}

			bool bRet = FindMTReturnFirst(hTemplet, item);


			if(bRet)
			{
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					FindNodeValue(objNode, "sv_label", value);
					liststr.push_back(value);	
					FindNodeValue(objNode, "sv_type", value);				
					listtype.push_back(value);
					FindNodeValue(objNode, "sv_unit", value);
					listunit.push_back(value);
					FindNodeValue(objNode, "sv_drawimage", value);
					listimage.push_back(value);
					FindNodeValue(objNode, "sv_drawtable", value);
					listtable.push_back(value);
				}
			}		
		}
	}

	if(hMon != INVALID_VALUE)
	{
		svutil::TTime end = svutil::TTime::GetCurrentTimeEx();

		MAPNODE node = GetMTMainAttribNode(hTemplet);
		std::string ;
		FindNodeValue(node, "sv_label", value);
		//简单报表标题
		WFont font;
		font.setFamily(WFont::Default, "Arial");
		font.setSize(WFont::Large, WLength(60,WLength::Pixel));
		//std::string reportstr = "报表";
		std::string reportstr = strReportTitle;		
		reportstr += monname;



		reporttitletext->decorationStyle().setFont(font);
		pContainTable->elementAt(0, 0) ->setContentAlignment(AlignTop | AlignCenter);

		pContainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);

		new WText(rtitle, pSimpleMonitorTable->elementAt(1, 0));
		pSimpleMonitorTable->adjustRowStyle("tr1", "tr2");


		detTable->InitRow(1);
		//detTable->GeDataTable()->elementAt(1,0)->setContentAlignment(AlignCenter);//List-------------juxian.zhang
		new WText(rtitle, detTable->GeDataTable()->elementAt(1,0));

		std::list<string>::iterator pSItem;
		int i5 = 1;
		int i3 = 0;


		int i1, i2;
		char buf[256];
		char buf1[256];
		char buf2[256];

		std::list<float> floatlist;
		std::list<float>::iterator floatitem;

		std::list<int> intlist;
		std::list<int>::iterator intitem;

		std::list<string> stringlist;
		std::list<string>::iterator stringitem;

		std::list<string> timelist;
		std::list<string>::iterator timeitem;

		std::list<TTime> timelist1;
		std::list<TTime>::iterator timeitem1;				

		pContainTable->elementAt(7, 0) ->setContentAlignment(AlignTop | AlignCenter);

		svutil::TTime time = svutil::TTime::GetCurrentTimeEx();

		std::string strFreq;
		int nFreq;
		std::string strFreqUnit;
		bool bRet = GetMonitorParaValueByName(str,"_frequency",strFreq);
		GetMonitorParaValueByName(str, "_frequencyUnit", strFreqUnit);

		nFreq = atoi(strFreq.c_str());

		int nHourFreq = (nFreq*40)/60;
		int nMinuteFreq = (nFreq*40)%60;

		svutil::TTime begintime = time - svutil::TTimeSpan(0, nHourFreq, nMinuteFreq, 0);

		std::string szInterTime1 = m_formText.szTimePeriod;

		szInterTime1 += begintime.Format();
		szInterTime1 += "~";
		szInterTime1 += time.Format();

		intertimetitle->setText(szInterTime1);

		RECORDSET hRec = QueryRecords(querystr, begintime, svutil::TTime::GetCurrentTimeEx());


		AddColum(liststr, NULL);

		std::list<string> fieldlist;
		std::list<string>::iterator item;
		std::list<string>::iterator item2;
		std::list<string>::iterator typeitem;
		std::list<string>::iterator unititem;
		std::list<string>::iterator imageitem;
		std::list<string>::iterator tableitem;
		bool bret = GetReocrdSetField(hRec, fieldlist);

		int stat;
		std::string str1;

		LISTITEM item1;
		RECORD hRec1;
		int type;
		int iv;
		float fv;
		string sv;		
		int count = 0;
		size_t reccount = 0;

		GetRecordCount(hRec,reccount);


		double data[1500];
		char* labels1[1500];
		for(int recitem = 0; recitem < 1500; recitem++)
		{
			labels1[recitem] = (char*)malloc(32);			
		}


		for(item = fieldlist.begin(), item2 = liststr.begin(), typeitem = listtype.begin(), unititem = listunit.begin(), imageitem = listimage.begin(), tableitem = listtable.begin(); \
			item != fieldlist.end()&&item2 != liststr.end()&&typeitem != listtype.end()&&unititem != listunit.end(); item++, item2++, typeitem++, unititem++, imageitem++, tableitem++)
		{	
			statTable->InitRow(i5);//------------juxian.zhang
			count = 0;
			std::string str = *item;
			//std::string str2 =GetLabelResource(*item2);
			std::string str2 = (*item2);
			std::string unitstr =*unititem;
			std::string rettype =  *typeitem;

			std::string tablestr = *tableitem;

			if(strcmp(tablestr.c_str(), "1") == 0)//根据MONITORTEMPLET返回值属性sv_drawtable是否为1
			{
				new WText(rtitle, pSimpleStatsTable->elementAt(i5, 0));
				new WText(rtitle, statTable->GeDataTable()->elementAt(i5, 0));//-----------------juxian.zhang

				new WText(str2, pSimpleStatsTable->elementAt(i5, 1));
				new WText(str2, statTable->GeDataTable()->elementAt(i5, 2));//-----------------juxian.zhang
			}	

			stringlist.clear();
			intlist.clear();
			floatlist.clear();
			timelist.clear();			
			FindRecordFirst(hRec, item1);						
			float maxval = 0;
			float countval = 0;
			int itemnum = 0;
			TTime tm;	
			bool bMin = true;
			bool bInt = true;

			while( (hRec1 = FindNextRecord(item1)) != INVALID_VALUE)
			{						
				GetRecordValueByField(hRec1, str, type, stat, iv, fv, sv);
				//比较返回值类型
				if(stat == 4)
				{
					if(strcmp(rettype.c_str(), "Int") == 0)
					{												
						if(maxval < 0)
						{
							maxval = 0;

						}

						if(bMin)
						{
							minval = 0;
							bMin = false;
						}

						if(minval > 0)
						{
							minval = 0;
						}

						countval += 0;

						intlist.push_back(0);
					}
					else if(strcmp(rettype.c_str(), "Float") == 0)
					{
						bInt = false;
						if(maxval < 0)
						{
							if(maxval < 0)
							{
								maxval = 0;

							}
							maxval =0;
						}

						if(bMin)
						{
							minval = 0;
							bMin = false;
						}

						if(minval > 0)
						{
							minval = 0;
						}
						countval += 0;

						floatlist.push_back(0);
					}
					else if(strcmp(rettype.c_str(), "String") == 0)
					{
						stringlist.push_back(sv);
					}

				}
				else if(stat != 5)
				{
					if(strcmp(rettype.c_str(), "Int") == 0)
					{		
						itemnum++;
						if(maxval < iv)
						{
							maxval = iv;							
						}

						if(bMin)
						{
							minval = iv;
							bMin = false;
						}

						if(minval > iv)
						{
							minval = iv;
						}

						countval += iv;												
						intlist.push_back(iv);
					}
					else if(strcmp(rettype.c_str(), "Float") == 0)
					{
						itemnum++;
						bInt = false;
						if(maxval < fv)
						{
							if(maxval < iv)
							{
								maxval = iv;								
							}
							maxval =fv;
						}

						if(bMin)
						{
							minval = fv;
							bMin = false;
						}

						if(minval > fv)
						{
							minval = fv;
						}

						countval += fv;

						floatlist.push_back(fv);
					}
					else if(strcmp(rettype.c_str(), "String") == 0)
					{
						if(stat == 3)
						{
							itemnum++;
						}

						stringlist.push_back(sv);
					}
				}
				else
				{
					if(strcmp(rettype.c_str(), "Int") == 0)
					{	

						if(maxval < 0)
						{
							maxval = 0;

						}

						if(bMin)
						{
							minval = 0;
							bMin = false;
						}

						if(minval > 0)
						{
							minval = 0;
						}

						countval += 0;

						intlist.push_back(0);
					}
					else if(strcmp(rettype.c_str(), "Float") == 0)
					{						
						bInt = false;
						if(maxval < 0)
						{
							if(maxval < 0)
							{
								maxval = 0;

							}
							maxval =0;
						}

						if(bMin)
						{
							minval = 0;
							bMin = false;
						}

						if(minval > 0)
						{
							minval = 0;
						}
						countval += 0;

						floatlist.push_back(0);
					}
					else if(strcmp(rettype.c_str(), "String") == 0)
					{

						stringlist.push_back(sv);
					}
				}									
				GetRecordCreateTime(hRec1,tm);
				timelist.push_back(tm.Format());
				timelist1.push_back(tm);
				//itemnum++;

			}	
			if(itemnum == 0)
			{
				perval = 0;
			}
			else
			{
				perval = countval / itemnum;
			}

			if(reccount == 0)
			{
				maxval = 0;
				perval = 0;
				minval = 0;
			}

			if(strcmp(tablestr.c_str(), "1") == 0)//根据MONITORTEMPLET返回值属性sv_drawtable是否为1
			{
				memset(buf2, 0, 256);
				if(bInt)
				{
					statTable->InitRow(0);
					sprintf(buf2, "%0.0f", maxval);
					new WText(buf2, pSimpleStatsTable->elementAt(i5, 2));
					new WText(buf2, statTable->GeDataTable()->elementAt(i5, 4));//-----------------juxian.zhang
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", perval);
					new WText(buf2, pSimpleStatsTable->elementAt(i5, 3));
					new WText(buf2, statTable->GeDataTable()->elementAt(i5, 6));//-----------------juxian.zhang
				}
				else
				{
					sprintf(buf2, "%0.2f", maxval);
					new WText(buf2, pSimpleStatsTable->elementAt(i5, 2));
					new WText(buf2, statTable->GeDataTable()->elementAt(i5, 4));//-----------------juxian.zhang
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.2f", perval);
					new WText(buf2, pSimpleStatsTable->elementAt(i5, 3));
					new WText(buf2, statTable->GeDataTable()->elementAt(i5, 6));//-----------------juxian.zhang
				}
			}


			double time[1500];
			for(floatitem = floatlist.begin(), intitem = intlist.begin(), stringitem =stringlist.begin(),timeitem = timelist.begin(), timeitem1 = timelist1.begin(); \
				(timeitem != timelist.end()); floatitem++, intitem++, stringitem++, timeitem++, timeitem1++)
			{							
				svutil::TTime ctm = *timeitem1;
				time[reccount - 1 - count] = Chart::chartTime(ctm.GetYear(), ctm.GetMonth(), ctm.GetDay(), ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());

				if(strcmp(rettype.c_str(), "Int") == 0)
				{
					char ibuf[256];
					memset(ibuf, 0, 256);
					sprintf(ibuf, "int value:%d\n", *intitem);
					OutputDebugString(ibuf);

					data[reccount -1 - count] = *intitem;
				}
				else if(strcmp(rettype.c_str(), "Float") == 0)
				{
					data[reccount -1 - count] = *floatitem;
				}
				else if(strcmp(rettype.c_str(), "String") == 0)
				{
					std::string stringitemstr = *stringitem;
					data[reccount -1 - count] = 0;
				}

				char buf2[256];
				memset(buf2, 0, 256);

				std::string tempstr1 = *timeitem;

				int pos = tempstr1.find(" ", 0);
				std::string tempstr2 = tempstr1.substr(pos, tempstr1.size() - pos);
				memset(labels1[reccount - 1 -count], 0, 32);
				strcpy(labels1[reccount - 1 -count], tempstr2.c_str());
				count++;				
			}


			i2 = rand();
			memset(buf, 0, 256);
			strcpy(buf,"../htdocs/Images/report/");
			itoa(i2, buf1, 10);
			strcat(buf, buf1);
			strcat(buf, ".png");

			int per = count/24;

			if(reccount == 0)
			{
				maxval = 0;
				perval = 0;
				minval = 0;
			}



			std::string Title = monname;
			if(bInt)
			{

				Title += str2;
				Title += "\n";
				Title += m_formText.szSimpleStatsMax;
				memset(buf2, 0, 256);
				sprintf(buf2, "%0.0f", maxval);
				Title += buf2;
				Title += m_formText.szSimpleStatsPer;
				memset(buf2, 0, 256);
				sprintf(buf2, "%0.0f", perval);
				Title += buf2;
				Title += szMinValue;
				memset(buf2, 0, 256);
				sprintf(buf2, "%0.0f", minval);
				Title += buf2;
			}
			else
			{

				Title += str2;
				Title += "\n";
				Title += m_formText.szSimpleStatsMax;
				memset(buf2, 0, 256);
				sprintf(buf2, "%0.2f", maxval);
				Title += buf2;
				Title += m_formText.szSimpleStatsPer;
				memset(buf2, 0, 256);
				sprintf(buf2, "%0.2f", perval);
				Title += buf2;
				Title += szMinValue;
				memset(buf2, 0, 256);
				sprintf(buf2, "%0.2f", minval);
				Title += buf2;
			}

			if(reccount < 4)
			{

			}
			else
			{

			}		

			//10-26 change add 30 seconds
			double cstarttime =  Chart::chartTime(tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond() - 30);
			TTime endtm = TTime::GetCurrentTimeEx();
			double cendtime = Chart::chartTime(endtm.GetYear(), endtm.GetMonth(), endtm.GetDay(), endtm.GetHour(), endtm.GetMinute(), endtm.GetSecond() );			
			std::string imagestr = *imageitem;
			if(strcmp(imagestr.c_str(), "1") == 0)
			{
				if(strcmp(unitstr.c_str(), "(%)") == 0)
				{
					GenLineImage1(data, time, reccount,NULL, reccount, 4, NULL, 0, 100, 20, reccount, cstarttime, cendtime,  (char*)Title.c_str(),  (char*)str2.c_str(), buf);
				}
				else
				{
					GenLineImage1(data, time, reccount,NULL, reccount, 4, NULL, 0, maxval, 20, reccount, cstarttime, cendtime,  (char*)Title.c_str(),  (char*)str2.c_str(), buf);
				}



				itoa(i3, buf2, 10);
							
				char namebuf[256] = {0};
				strcpy(namebuf,"/Images/report/");				
				strcat(namebuf, buf1);
				strcat(namebuf, ".png");
				new WImage(namebuf, (WContainerWidget*)pImageTable->elementAt(i3, 0));
				new WImage (namebuf ,ImageTable->GetContentTable()->elementAt(i3,0));//-----------------------juxian.zhang
				ImageTable->GetContentTable()->elementAt(i3, 0) ->setContentAlignment(AlignTop | AlignCenter);//-----------------------juxian.zhang
				pImageTable->elementAt(i3, 0) ->setContentAlignment(AlignTop | AlignCenter);

				i3++;	
			}

			i5++;

		}


		for(int recitem = 0; recitem < 1500; recitem++)
		{
			free(labels1[recitem]);			
		}



		std::list<string> allstrlist;
		int normalnum = 0, normalindex = 1;
		int dangernum = 0, dangerindex = 1;
		int errornum = 0, errorindex = 1;
		int disablenum = 0 , disableindex = 1;
		int othernum = 0, otherindex =1;
		floatlist.clear();
		timelist.clear();
		FindRecordFirst(hRec, item1);


		count = 0;
		while( (hRec1 = FindNextRecord(item1)) != INVALID_VALUE)
		{				
			TTime tm;
			GetRecordCreateTime(hRec1,tm);
			timelist.push_back(tm.Format());

			GetRecordDisplayString(hRec1, stat, str1);
			if(stat == 1)
			{
				NormalTable->InitRow(normalindex);
				new WText(tm.Format(), NormalTable->GeDataTable()->elementAt(normalindex, 0));
				new WText(rtitle, NormalTable->GeDataTable()->elementAt(normalindex, 2));
				list<string>::iterator fielditem;
				int j = 2;
				int k = 4;
				for(fielditem = fieldlist.begin(); fielditem != fieldlist.end(); fielditem++)
				{
					int type1;
					int state1;
					int iv1;
					float fv1;
					string sv1;

					char buf1[256];
					memset(buf1, 0, 256);

					GetRecordValueByField(hRec1, *fielditem, type1, state1, iv1, fv1, sv1);
					if(type1 == 1)
					{
						sprintf(buf1, "%d", iv1);	
					}
					else if(type1 == 2)
					{
						sprintf(buf1, "%.2f", fv1);
					}
					else if(type1 == 3)
					{
						strcpy(buf1, sv1.c_str());
					}
					new WText(buf1,NormalTable->GeDataTable()->elementAt(normalindex,k));
					j++;
					k = k+2;
				}
				normalnum++;
				normalindex++;
			}
			else if(stat == 2)
			{
				DangerTable->InitRow(dangerindex); //---------------juxian.zhang 				
				new WText(tm.Format(),DangerTable->GeDataTable()->elementAt(dangerindex,0));//-----------------juxian.zhang
				new WText(rtitle,DangerTable->GeDataTable()->elementAt(dangerindex,2));//-----------------juxian.zhang
				new WText(str1,DangerTable->GeDataTable()->elementAt(dangerindex,4));//-----------------juxian.zhang
				dangernum++;
				dangerindex++;
			}
			else if(stat == 3 || stat == 5)
			{
				ErrorTable->InitRow(errorindex);//-----------------------juxian.zhang
				new WText(tm.Format(),ErrorTable->GeDataTable()->elementAt(errorindex,0));//-----------------juxian.zhang
				new WText(rtitle, ErrorTable->GeDataTable()->elementAt(errorindex, 2));//-----------------juxian.zhang
				new WText(str1, ErrorTable->GeDataTable()->elementAt(errorindex, 4));//-----------------juxian.zhang
				errornum++;errorindex++;
			}
			else if(stat == 4)
			{
				DisableTable->InitRow(disableindex);//-----------------juxian.zhang
				new WText(tm.Format(), DisableTable->GeDataTable()->elementAt(disableindex, 0));//-----------------juxian.zhang
				new WText(rtitle, DisableTable->GeDataTable()->elementAt(disableindex, 2));//-----------------juxian.zhang
				new WText(str1, DisableTable->GeDataTable()->elementAt(disableindex, 4));//-----------------juxian.zhang
				disablenum++;disableindex++;
			}
			else
			{
				othernum++;
			}

			allstrlist.push_back(str1);
			count++;						
		}		

		if((normalnum + dangernum + errornum + disablenum) != 0)
		{
			itoa((normalnum*100)/(normalnum + dangernum + errornum + disablenum), buf, 10);
		}
		else
		{
			memset(buf, 0, 256);
		}

		new WText(buf, (WContainerWidget*)pSimpleMonitorTable->elementAt(1, 1));
		detTable->GeDataTable()->elementAt(1,2)->setContentAlignment(AlignTop | AlignCenter);//List-------------juxian.zhang
		new WText(buf, detTable->GeDataTable()->elementAt(1,2));

		if((normalnum + dangernum + errornum + disablenum) != 0)
		{
			itoa((dangernum*100)/(normalnum + dangernum + errornum + disablenum), buf, 10);
		}
		else
		{
			memset(buf, 0, 256);
		}
		new WText(buf, (WContainerWidget*)pSimpleMonitorTable->elementAt(1, 2));
		detTable->GeDataTable()->elementAt(1, 4)->setContentAlignment(AlignTop | AlignCenter);//List-------------juxian.zhang
		new WText(buf, detTable->GeDataTable()->elementAt(1,4));

		if((normalnum + dangernum + errornum + disablenum) != 0)
		{
			itoa((errornum*100)/(normalnum + dangernum + errornum + disablenum), buf, 10);
		}
		else
		{
			memset(buf, 0, 256);
		}
		new WText(buf, (WContainerWidget*)pSimpleMonitorTable->elementAt(1, 3));
		detTable->GeDataTable()->elementAt(1, 6)->setContentAlignment(AlignTop | AlignCenter);//List-------------juxian.zhang
		new WText(buf, detTable->GeDataTable()->elementAt(1,6));

		if((normalnum + dangernum + errornum + disablenum) != 0)
		{
			itoa((disablenum*100)/(normalnum + dangernum + errornum + disablenum), buf, 10);

		}
		else
		{
			memset(buf, 0, 256);
		}
		new WText(buf, (WContainerWidget*)pSimpleMonitorTable->elementAt(1, 4));
		detTable->GeDataTable()->elementAt(1, 8)->setContentAlignment(AlignTop | AlignCenter);//List-------------juxian.zhang
		new WText(buf, detTable->GeDataTable()->elementAt(1,8));
		//std::string szStats = szAlertCount;
		//itoa(normalnum + dangernum + errornum + disablenum, buf, 10);
		//szStats += buf;
		//szStats += strNormalCount;
		//itoa(normalnum, buf, 10);
		//szStats += buf;
		//szStats += strDangerCount;
		//itoa(dangernum ,buf, 10);
		//szStats += buf;
		//szStats += strErrorCount;
		//itoa(errornum, buf, 10);
		//szStats += buf;
		//szStats += strDisableCount;
		//itoa(disablenum, buf, 10);
		//szStats += buf;


		//if(monitorcounttitle == NULL)
		//{
		//	monitorcounttitle = new WText(szStats, pContainTable->elementAt(3, 0));
		//	monitorcounttitle = new WText (szStats, namesTable->GetContentTable()->elementAt(2,0));//-----------------juxian.zhang
		//}
		//monitorcounttitle ->setText(szStats);
		//monitorcounttitle->decorationStyle().setForegroundColor(Wt::blue);
		pContainTable->elementAt(3, 0) ->setContentAlignment(AlignTop | AlignCenter);
		namesTable->GetContentTable()->elementAt(2,0)->setContentAlignment(AlignTop | AlignCenter);//juxian.zhang
		pSimpleStatsTable->adjustRowStyle("tr1","tr2");	

		pNormalTable->adjustRowStyle("tr1","tr2");	

		pDangerTable->adjustRowStyle("tr1", "tr2");

		pErrorTable->adjustRowStyle("tr1", "tr2");	

		pDisableTable->adjustRowStyle("tr1", "tr2");

		ReleaseRecordList(item1);
		CloseRecordSet(hRec);
	}
	else
	{
		if(monitorcounttitle == NULL)
		{
		}
		else
		{
			monitorcounttitle->setText(m_formText.szCaption1);
		}
	}


}

string  CSimpleReport::GetMonitorPropValue(string strId, string strPropName)
{
	string strTmp = "";

	//监测器名称
	OBJECT objMonitor = Cache_GetMonitor(strId);
	if(objMonitor != INVALID_VALUE)
	{
		MAPNODE motnitornode = GetMonitorMainAttribNode(objMonitor);
		if(motnitornode != INVALID_VALUE)
		{
			FindNodeValue(motnitornode, strPropName, strTmp);
		}

		//CloseMonitor(objMonitor);
	}

	return strTmp;
}

bool CSimpleReport::GetMonitorParaValueByName( string strID, string strName, string &strRet )
{
	OBJECT obj1=Cache_GetMonitor( strID ); 
	if ( obj1==INVALID_VALUE )
		return false;

	MAPNODE ma=GetMonitorParameter(obj1) ;
	if ( ma==INVALID_VALUE )
		return false;

	string getvalue;
	if ( ! FindNodeValue( ma,strName,getvalue) )
		return false;

	strRet= getvalue; 	
	//CloseMonitor(obj1);
	return true;
}

void CSimpleReport::TableClear()
{
	pSimpleMonitorTable->clear();
	//----------------juxian.zhang 20070108
	namesTable->GeDataTable()->clear(); 
	detTable->GeDataTable()->clear();
	statTable->GeDataTable()->clear();
	ImageTable->GetContentTable()->clear();
	ErrorTable->GeDataTable()->clear();
	DangerTable->GeDataTable()->clear();
	NormalTable->GeDataTable()->clear();
	DisableTable->GeDataTable()->clear();
	//----------------juxian.zhang 20070108
	pSimpleStatsTable->clear();
	pImageTable->clear();
	pNormalTable->clear();
	pDangerTable->clear();
	pErrorTable->clear();
	pDisableTable->clear();

}

//std::string CSimpleReport::GetLabelResource(std::string strLabel)

std::string CSimpleReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel =strLabel;
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	//if(strfieldlabel=="")
	//		strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

typedef void(*func)(int , char **);

//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes1=LoadResourceByKeys("IDS_Simple_Report","default", "localhost");
	if( objRes1 !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes1);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Simple_Report",title);
		//CloseResource(objRes1);
	}
	WApplication app(argc, argv);
	app.setTitle(title.c_str());
	//WApplication app(argc, argv);
	//app.setTitle("简单报告");
	CSimpleReport setform(app.root());
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


