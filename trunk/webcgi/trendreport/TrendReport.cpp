#include ".\trendreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"



//new ui 
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"
#include "../svtable/WSTreeAndPanTable.h"


#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"

#include "cspreadsheet.h"

#include "../base/OperateLog.h"

#define WTGET

//分解字符串
bool CTrendReport::ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps)
{
    char * token = NULL;
    // duplicate string
	char * cp = ::strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        if (pSVSeps) // using separators
            token = strtok( pTmp , pSVSeps);
        else // using separators
			return false;
            //token = strtok( pTmp, chDefSeps);
        // every field
        while( token != NULL )
        {
            //triml(token);
            //AddListItem(token);
			pTokenList.push_back(token);
            // next field
            if (pSVSeps)
                token = strtok( NULL , pSVSeps);
            else
               return false;
				//token = strtok( NULL, chDefSeps);
        }
        // free memory
        free(cp);
    }
    return true;
}

string& replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}


/***********************************************
参数：
	szRepStr：需替换的字符串

功能：
    替换字符串中的一些特殊字符， &-%26
	$-%24,#-%23,空-%20

返回值：
    替换后的字符串
***********************************************/
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

//
string  GetMonitorPropValue(string strId, string strPropName)
{
	string strTmp = "";

	//监测器id
	OBJECT objMonitor = GetMonitor(strId);
	if(objMonitor != INVALID_VALUE)
    {
        MAPNODE motnitornode = GetMonitorMainAttribNode(objMonitor);
        if(motnitornode != INVALID_VALUE)
        {
			FindNodeValue(motnitornode, strPropName, strTmp);
		}

		CloseMonitor(objMonitor);
	}

	return strTmp;
}

//根据monitorid获取父设备的名称
string  GetDeviceTitle(string strId)
{
	string strTmp = "";
	string strParentId = FindParentID(strId);

	//设备名称
	OBJECT objDevice = GetEntity(strParentId);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE devicenode = GetEntityMainAttribNode(objDevice);
        if(devicenode != INVALID_VALUE)
        {
			FindNodeValue(devicenode, "sv_name", strTmp);
		}
		
		CloseEntity(objDevice);
	}

	return strTmp;
}


//
CTrendReport::CTrendReport(TTime starttime, TTime endtime, std::string reportname, bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent ):
WTable(parent)
{
	WIN32_FIND_DATA fd;
	string	szRootPath = GetSiteViewRootPath();
	string szReportPath = szRootPath;
	szReportPath += "\\htdocs\\data";

	HANDLE fr=::FindFirstFile(szReportPath.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szReportPath.c_str(), NULL);
	}

	//Resource
	objResource=LoadResource("default", "localhost");  
	if( objResource !=INVALID_VALUE )
	{	
		resourceNode=GetResourceNode(objResource);
		if( resourceNode != INVALID_VALUE )
		{
			FindNodeValue(resourceNode,"IDS_Total_Report",strMainTitle);
			FindNodeValue(resourceNode,"IDS_Total_Report_List",strTitle);
			FindNodeValue(resourceNode,"IDS_Name",strLoginLabel);
			FindNodeValue(resourceNode,"IDS_Total_Report_Map",strNameUse);
			FindNodeValue(resourceNode,"IDS_Edit_Name",strNameEdit);
			FindNodeValue(resourceNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(resourceNode,"IDS_Run_Case_Table",m_formText.szRunTitle);
			FindNodeValue(resourceNode,"IDS_Time_Period",szInterTime);
			FindNodeValue(resourceNode,"IDS_Alert_Date_Total_Table",m_formText.szMonitorTitle);
			FindNodeValue(resourceNode,"IDS_Error_Precent",m_formText.szErrorTitle);
			FindNodeValue(resourceNode,"IDS_Danger_Prencet",m_formText.szDangerTitle);
			FindNodeValue(resourceNode,"IDS_Normal_Precent",m_formText.szNormalTitle);
			FindNodeValue(resourceNode,"IDS_Name",m_formText.szRunName);
			FindNodeValue(resourceNode,"IDS_Run_Time_Normal_Precent",m_formText.szRunTime);
			FindNodeValue(resourceNode,"IDS_Danger_Prencet",m_formText.szRunDanger);
			FindNodeValue(resourceNode,"IDS_Error",m_formText.szRunError);
			FindNodeValue(resourceNode,"IDS_Later",m_formText.szRunNew);
			FindNodeValue(resourceNode,"IDS_Clique_Value",m_formText.szRunClicket);
			FindNodeValue(resourceNode,"IDS_Name",m_formText.szMonName);
			FindNodeValue(resourceNode,"IDS_Measure",m_formText.szMonMeasure);
			FindNodeValue(resourceNode,"IDS_Max",m_formText.szMonMax);
			FindNodeValue(resourceNode,"IDS_Average",m_formText.szMonPer);
			FindNodeValue(resourceNode,"IDS_Later_Time",m_formText.szMonLast);
			FindNodeValue(resourceNode,"IDS_Name",m_formText.szErrName);
			FindNodeValue(resourceNode,"IDS_Time",m_formText.szErrStartTime);
			FindNodeValue(resourceNode,"IDS_State",m_formText.szErrStatus);
			FindNodeValue(resourceNode,"IDS_Name",m_formText.szDangerName);
			FindNodeValue(resourceNode,"IDS_Time",m_formText.szDangerStartTime);
			FindNodeValue(resourceNode,"IDS_State",m_formText.szDangerStatus);
			FindNodeValue(resourceNode,"IDS_Time",strHTimeLabel);
			FindNodeValue(resourceNode,"IDS_Name",strHNameLabel);
			FindNodeValue(resourceNode,"IDS_Data",strHDataLabel);
			FindNodeValue(resourceNode,"IDS_NormalData",strNormalBtn);
			FindNodeValue(resourceNode,"IDS_ErrorData",strErrorBtn);
			FindNodeValue(resourceNode,"IDS_WarningData",strWarnningBtn);
			FindNodeValue(resourceNode,"IDS_Back",strBack);
			FindNodeValue(resourceNode,"IDS_Forward",strForward);
			FindNodeValue(resourceNode,"IDS_Return",strReturn);
			FindNodeValue(resourceNode,"IDS_Date_Record",strDataTableName);
			FindNodeValue(resourceNode,"IDS_No_Sort_Record",strNoSortRecord); 
			FindNodeValue(resourceNode,"IDS_Name",m_formText.szXLSName);
			FindNodeValue(resourceNode,"IDS_Time",m_formText.szXLSTime);
			FindNodeValue(resourceNode,"IDS_State",m_formText.szXLSStatus);
			FindNodeValue(resourceNode,"IDS_Data1",m_formText.szXLSData); 
			FindNodeValue(resourceNode,"IDS_Normal",m_formText.szXLSNormal);
			FindNodeValue(resourceNode,"IDS_Error",m_formText.szXLSError);
			FindNodeValue(resourceNode,"IDS_Danger",m_formText.szXLSDanger); 
			FindNodeValue(resourceNode,"IDS_Generate_Excel_Table",m_formText.szExcelBut); 


			FindNodeValue(resourceNode,"IDS_Map_Table",m_formText.szChart); 			
			FindNodeValue(resourceNode,"IDS_Normal",m_formText.szGood); 			
			FindNodeValue(resourceNode,"IDS_Warning",m_formText.szWarning);			
			FindNodeValue(resourceNode,"IDS_Error",m_formText.szError); 			
			FindNodeValue(resourceNode,"IDS_Disable",m_formText.szDisable); 
			FindNodeValue(resourceNode,"IDS_Max_Value",m_formText.szMaxValue);			
			FindNodeValue(resourceNode,"IDS_Average_Value",m_formText.szAverageValue);			
			FindNodeValue(resourceNode,"IDS_Min_Value",m_formText.szMinValue); 			
			FindNodeValue(resourceNode,"IDS_Name",m_formText.szName); 
			FindNodeValue(resourceNode,"IDS_State",m_formText.szState); 
			FindNodeValue(resourceNode,"IDS_Time",m_formText.szTime); 
			FindNodeValue(resourceNode,"IDS_Data",m_formText.szData); 
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Page",m_formText.szPage); 
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Page_Count",m_formText.szPageCount); 
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Count",m_formText.szRecordCount); 
			FindNodeValue(resourceNode,"IDS_PageRecordCount",m_formText.szPageRecordCount); 
			FindNodeValue(resourceNode, "IDS_DownloadList", m_formText.szDownloadList);
			FindNodeValue(resourceNode, "IDS_Close", m_formText.szClose);
			FindNodeValue(resourceNode, "IDS_GoodDataRecord", strGoodData);
			FindNodeValue(resourceNode, "IDS_GoodErrorRecord", strErrorData);
			FindNodeValue(resourceNode, "IDS_GoodWarningRecord", strWarningData);

			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Ini",strReocrdIni); 
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Page",strPage); 
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Page_Count",strPageCount); 
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Count",strRecordCount); 

		}
		CloseResource(objResource);
	}

	/*
	strMainTitle ="统计报告";
	strTitle ="统计报告列表";

	strLoginLabel = "名 称";	
	strNameUse = "统计报告图";
	strNameEdit="编辑名称";

	strNameTest="游龙科技";
	strDel=  "确认删除选中用户吗？";
	//szInterTime = "(时间段：2006-09-29 00:00:00 ~  2006-09-29 23:59:59)";	

	szInterTime = "时间段:";

	strHTimeLabel = "时  间";
	strHNameLabel = "名  称";
	strHDataLabel = "                     数  据                       ";

	strNormalBtn = "正  常";
	strErrorBtn = "错  误";
	strWarnningBtn = "危  险";
	
	strBack = "后 退";
	strForward = "向 前";
	strReturn = "返 回";

	strDataTableName = "数据记录";
	*/
	gfieldnum = 0;

	m_starttime = starttime;
	m_endtime = endtime;
	m_reportname = reportname;
	szInterTime += starttime.Format();
	szInterTime += "~";
	szInterTime += endtime.Format();

	szXSLReportName = starttime.Format();
	szXSLReportName += endtime.Format();
	szXSLReportName += reportname;

	/*replace_all_distinct(szXSLReportName, ":", "_");
	replace_all_distinct(szXSLReportName, " ", "_");
	replace_all_distinct(szXSLReportName, ".", "_");
	*/
	replace_all_distinct(szXSLReportName, ":", "");
	replace_all_distinct(szXSLReportName, " ", "");
	replace_all_distinct(szXSLReportName, ".", "");
	replace_all_distinct(szXSLReportName, "-", "");
	replace_all_distinct(szXSLReportName, "\\", "");
	replace_all_distinct(szXSLReportName, "/", "");

	szXSLReportName += ".xls";

	OutputDebugString("----------construct function output xls file-------------------\n");
	OutputDebugString(szXSLReportName.c_str());

	gPageNum = 1;
	gPageCount = 0;
	nCurDataType = 0;

	normalrecnum = 1;
	dangerrecnum = 1;
	errorrecnum = 1;

	nCurPage = 0;
	nTotalPage = 0;
	nPageCount = 30;

	ShowMainTable(starttime, endtime, reportname, bClicket, bListError, bListDanger, bListStatsResult, bListImage);



}

//
CTrendReport::~CTrendReport(void)
{
	if( objResource !=INVALID_VALUE )
			CloseResource(objResource);
}

void CTrendReport::InitPageTable(WTable *mainTable, string title)
{
	//New Version 
	pReportTitle = new WText(title, (WContainerWidget*)mainTable->elementAt(0, 0));
	mainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	pReportTitle->setStyleClass("textbold");

	WText * text1 = new WText(szInterTime, (WContainerWidget*)mainTable->elementAt(1, 0));
	mainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);
	new WText("<br>", (WContainerWidget*)mainTable->elementAt(1, 0));

	m_pUptimeTable = new WSVFlexTable(mainTable->elementAt(2,0),List,m_formText.szRunTitle);

	if (m_pUptimeTable->GetContentTable() != NULL)
	{
		m_pUptimeTable->AppendColumn(m_formText.szRunName,WLength(60,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunTime,WLength(80,WLength::Pixel));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunDanger,WLength(80,WLength::Pixel));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunError,WLength(50,WLength::Pixel));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunNew,WLength(50,WLength::Pixel));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunClicket,WLength(30,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

	}

	m_pMeasurementTable = new WSVFlexTable(mainTable->elementAt(3,0),List,m_formText.szMonitorTitle);
	if (m_pMeasurementTable->GetContentTable() != NULL)
	{
		m_pMeasurementTable->AppendColumn(m_formText.szMonName,WLength(60,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonMeasure,WLength(80,WLength::Pixel));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonMax,WLength(80,WLength::Pixel));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonPer,WLength(80,WLength::Pixel));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonLast,WLength(30,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");
	}

	m_pChartTable = new WSVFlexTable(mainTable->elementAt(4,0),Blank,m_formText.szChart);


	//正常 错误 警告三个按钮
	mainTable->elementAt(5, 0)->setContentAlignment(AlignTop | AlignCenter);
	pDataCmdTable = new WTable(mainTable->elementAt(5,0));
	pDataCmdTable->setStyleClass("widthauto");

	WSVButton *pNormalBtn = new WSVButton(pDataCmdTable->elementAt(0,0), strNormalBtn, "button_bg_m.png", "", false);

	WSVButton *pErrorBtn = new WSVButton(pDataCmdTable->elementAt(0,1), strErrorBtn, "button_bg_m.png", "", false);

	WSVButton *pWarnningBtn = new WSVButton(pDataCmdTable->elementAt(0,2), strWarnningBtn, "button_bg_m.png", "", false);

	//保存为EXCEL文件
	WSVButton *pSaveExcel = new WSVButton(pDataCmdTable->elementAt(0,3), m_formText.szExcelBut, "button_bg_m.png", "", false);

	connect(pNormalBtn, SIGNAL(clicked()), this, SLOT(NormalBtn()));
	connect(pErrorBtn, SIGNAL(clicked()), this, SLOT(ErrorBtn()));
	connect(pWarnningBtn, SIGNAL(clicked()), this, SLOT(WarnningBtn()));
	connect(pSaveExcel, SIGNAL(clicked()), this, SLOT(SaveExcelBtn()));	


}

//
void CTrendReport::ShowMainTable(TTime starttime, TTime endtime, std::string reportname, bool bClicket, bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage)
{
	WIN32_FIND_DATA fd;
	string	szRootPath = GetSiteViewRootPath();
	string szReport = szRootPath;
	szReport += "\\htdocs\\report";

	HANDLE fr=::FindFirstFile(szReport.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szReport.c_str(), NULL);
	}
		
	string szIconPath = szRootPath;
	szIconPath += "\\htdocs\\report\\Images";
	fr=::FindFirstFile(szIconPath.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szIconPath.c_str(), NULL);
	}

	string strReportTitle = GetDeviceTitle(reportname);
	strReportTitle += ":";
	strReportTitle += GetMonitorPropValue(reportname, "sv_name");

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this->elementAt(0,0));

	m_pListMainTable = new WTable(this->elementAt(0,0));

	InitPageTable(m_pListMainTable,strReportTitle);

	char buf_tmp[4096]={0};
    int nSize =4095;

	//get query_string value
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
 	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif	
	std::string querystr;	
	int reccount = 0;
	strcpy(buf_tmp , reportname.c_str());
	
	//if(buf_tmp != NULL)
	//{
	//	GetMonitorGroup(buf_tmp, grouplist);//取报告对应监测器	
	//}
	


	//InitPageItem(pContainTable, buf_tmp);//初始化页面元素
//	InitPageItem(pContainTable, strReportTitle);//初始化页面元素

//	AddColum(NULL);
		
	std::list<string>::iterator item;
	int i6 = 1;

	int i1, i2;
	char buf[256];
	char buf1[256];
	
//	pImageTable = new WTable(pContainTable->elementAt(7 , 0));
	if(!bListImage)
	{
//		pImageTable->hide();
		
		//没有图表
		m_pChartTable->GeDataTable()->hide();
	}

//	pContainTable->elementAt(7, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	int i3 = 0;

	int fieldnum = 1;

	int gnormalnum = 1;
	int gdangernum = 1;
	int gerrornum = 1;

	int tcount = 0;

	GetMonitorRecord(reportname, starttime, endtime, bClicket, bListStatsResult, reportname, tcount, i6, i3, fieldnum);

	//新版本DataTable
	m_pDataTable = new WSVFlexTable(this->elementAt(1,0), List, strDataTableName);

	if (m_pDataTable->GetContentTable() != NULL)
	{
	/*	m_pDataTable->AppendColumn(strHNameLabel,WLength(40,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");

		m_pDataTable->AppendColumn(strHTimeLabel,WLength(30,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");

		m_pDataTable->AppendColumn(strHDataLabel,WLength(30,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");
		*/
	}

	if (m_pDataTable->GetActionTable() != NULL)
	{
		m_pDataTable->AddStandardSelLink(strBack,strForward,strReocrdIni);
		connect(m_pDataTable->pSelAll, SIGNAL(clicked()), this, SLOT(DataBack()));		
		connect(m_pDataTable->pSelNone, SIGNAL(clicked()), this, SLOT(DataForward()));
		m_pDataTable->pSelReverse->setStyleClass("");

		WTable *pTbl;
		m_pDataTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pDataTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		pTbl = new WTable(m_pDataTable->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");
		pTbl->elementAt(0,0)->setContentAlignment(AlignRight);
		WSVButton *pResturn = new WSVButton(pTbl->elementAt(0,0),strReturn, "button_bg_m.png","",false);
		connect(pResturn, SIGNAL(clicked()), this, SLOT(DataReturn()));	
	}

	m_pDataTable->SetNullTipInfo("[----------"+strNoSortRecord+"-----------]");
	m_pDataTable->hide();
}


//加列标题
void CTrendReport::AddColum(WTable* pContain)
{
	new WText(m_formText.szRunName, pRunTable->elementAt(0, 0));
	new WText(m_formText.szRunTime, pRunTable->elementAt(0, 1));
	new WText(m_formText.szRunDanger, pRunTable->elementAt(0, 2));
	new WText(m_formText.szRunError, pRunTable->elementAt(0, 3));
	new WText(m_formText.szRunNew, pRunTable->elementAt(0, 4));
	new WText(m_formText.szRunClicket, pRunTable->elementAt(0, 5));
	
	pRunTable->setCellSpaceing(0);
	pRunTable->GetRow(0) ->setStyleClass("t1title");
	//pRunTable->GetRow(0) ->setStyleClass("Statst1title");

	new WText(m_formText.szMonName, pMonitorTable->elementAt(0, 0));
	new WText(m_formText.szMonMeasure, pMonitorTable->elementAt(0, 1));
	new WText(m_formText.szMonMax, pMonitorTable->elementAt(0, 2));
	new WText(m_formText.szMonPer, pMonitorTable->elementAt(0, 3));
	new WText(m_formText.szMonLast, pMonitorTable->elementAt(0, 4));
	
	pMonitorTable->setCellSpaceing(0);
	pMonitorTable->GetRow(0) ->setStyleClass("t1title");
}

//
void CTrendReport::AddListColumn()
{

}

//
void CTrendReport::refresh()
{
	
}

//
void CTrendReport::GenLineImage(double data[],  double time[], const int len, char *xlabels[],int xscalelen, int xStep, char *ylabels[], int yscalelen, int yScale, int yStep, int xLinearScale, double starttime, double endtime, char* Title, char* xTitle, char * filename)
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

	//解决中文版ECC在生成报表时图片出现乱码的问题
	//苏合 2007-07-16 代码更改开始

	/* 对原来的代码此段进行修改
	//设置中文
	setlocale(LC_CTYPE, ""); 
	*/

	string IniPath("\\data\\svdbconfig.ini");
	IniPath = GetSiteViewRootPath() + IniPath;
	char buf[256]={0};
	GetPrivateProfileString("svdb","DefaultLanguage","",buf,255,IniPath.c_str());
	if (0 == strcmp("chinese", buf))
	{
		setlocale(LC_CTYPE, "chs");
		OutputDebugString("设置为中文");
	}
	else 
	{
		setlocale(LC_CTYPE, "");
	}		
	//苏合 2007-07-16 代码更改结束 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, Title, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
	c->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);
		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

    c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	//lpWideCharStr = L"游龙科技有限公司";
	lpWideCharStr = L"Copyright SiteView";

	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);
	c->xAxis()->setTitle(lpMultiByteStr, "mingliu.ttc", 8, 0x000000ff);
/*
	if(yScale <= 10)
	{
		c->yAxis()->setLinearScale(0, yScale + 1);
	}
	else
	{
		c->yAxis()->setLinearScale(0, yScale);//设置垂直刻度
	}


	c->xAxis()->setLinearScale(0, xLinearScale);
	
	 
 
	if(endtime - starttime < 90000)
	{
		c->xAxis()->setDateScale(starttime, endtime, 3600);
	}
	else
	{
		c->xAxis()->setDateScale(starttime, endtime, 86400 );
	}
	*/
	//c->addScatterLayer(DoubleArray(time, len), DoubleArray(data, len),
	//	"", Chart::PolygonShape(6), 3, 0xffff00);

	c->addTrendLayer(DoubleArray(time, len),DoubleArray(data, len), 0x6666ff)->setLineWidth(2);

	AreaLayer *layer = c->addAreaLayer();

	layer ->setXData(DoubleArray(time, len));
	layer->addDataSet(DoubleArray(data, len))->setDataColor(0x80d080, 0x007000);

    c->makeChart(filename);

	free(lpMultiByteStr);
	//delete [] m_timeStamps;

    delete c;
}

//
void CTrendReport::GenPieImage(char * szTitle, char ** labels, double data[], int len, char * filename)
{
	wchar_t lpWide[256];
	int colors[] = {0x00ff00, 0xffff00, 0xff0000};

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);

	BOOL buse ;
	//解决中文版ECC在生成报表时图片出现乱码的问题
	//苏合 2007-07-16 代码更改开始

	/* 对原来的代码此段进行修改
	//设置中文
	setlocale(LC_CTYPE, ""); 
	*/

	string IniPath("\\data\\svdbconfig.ini");
	IniPath = GetSiteViewRootPath() + IniPath;
	char buf[256]={0};
	GetPrivateProfileString("svdb","DefaultLanguage","",buf,255,IniPath.c_str());
	if (0 == strcmp("chinese", buf))
	{
		setlocale(LC_CTYPE, "chs");
		OutputDebugString("设置为中文");
	}
	else 
	{
		setlocale(LC_CTYPE, "");
	}		
	//苏合 2007-07-16 代码更改结束 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, szTitle, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

    PieChart *c = new PieChart(390, 300);

    c->setPieSize(180, 140, 100);

    c->addTitle(lpMultiByteStr, "mingliu.ttc", 9, 0x0000ff);

    c->set3D();

	c->addLegend(300, 40, true, "mingliu.ttc");

    c->setData(DoubleArray(data, len), StringArray(
        labels, len));

	 c->setColors(Chart::DataColor, IntArray(colors, sizeof(colors)/sizeof(colors[0]))
        );

	c->setLabelStyle("mingliu.ttc");

	//c->setLabelLayout(Chart::SideLayout);

   // c->setExplode(0);

    c->makeChart(filename);

	// *imageMap = c->getHTMLImageMap("clickable", "",
    //    "title='{label}: US${value}K ({percent}%)'");

    delete c;	
}

//
void CTrendReport::GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> &retmonnamelist, std::list<int> &retstatlist, std::list<string>& retstrlist, std::list<string>& rettimelist)
{
	LISTITEM item;
	RECORD hRec;
	list<string>::iterator fielditem;

	FindRecordFirst(hRecSet, item);
			
	int stat;
	std::string str;
	std::string	strNormal; 

	retnormalnamelist.clear();
	retnormaltimelist.clear();
	retdangernamelist.clear();
	retdangertimelist.clear();
	reterrornamelist.clear();
	reterrortimelist.clear();

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		GetRecordDisplayString(hRec, stat, str);			
		TTime tm;
		GetRecordCreateTime(hRec,tm);
		//if(stat == 1 || stat == 4)	
		if(stat == 1)
		{
			retnormalnamelist.push_back(monitorname);
			retnormaltimelist.push_back(tm.Format());
			
			//获取监测数据 并用;分隔
			strNormal = "";
			for(fielditem = fieldlist.begin(); fielditem != fieldlist.end(); fielditem++)
			{
				int type1;
				int state1;
				int iv1;
				float fv1;
				string sv1;

				char buf1[256];
				memset(buf1, 0, 256);

				GetRecordValueByField(hRec, *fielditem, type1, state1, iv1, fv1, sv1);
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
				
				strNormal.append(buf1);
				//OutputDebugString(buf1);
				
				strNormal.append(";");
			}
			
			//OutputDebugString(strNormal.c_str());
			//retnormalstatuslist.push_back(str);	
			retnormalstatuslist.push_back(strNormal);
		}
		if(stat == 2)
		{
			retdangernamelist.push_back(monitorname);
			retdangertimelist.push_back(tm.Format());
			retdangerstatuslist.push_back(str);
		}
		if(stat == 3 || stat == 5 || stat == 4)
		{
			reterrornamelist.push_back(monitorname);
			reterrortimelist.push_back(tm.Format());
			reterrorstatuslist.push_back(str);
		}
	}	
}

/*
void CTrendReport::GetMonitorDataRec(RECORDSET hRecSet,
std::string fieldname,
std::string fieldtype,
std::list<int> & intlist,
std::list<float> & floatlist, 
std::list<string> & stringlist, 
std::list<TTime> & timelist,
float & maxval,
float & minval, 
float & perval,
float & lastval, 
int & reccount)
							
{
	LISTITEM item;
	RECORD hRec;

	//取记录集中第一条记录的OBJECT
	FindRecordFirst(hRecSet, item);
			
	int type;//记录返回类型
	int stat;//记录返回状态
	int iv;//整型值
	float fv;//浮点型值
	std::string sv;//字符串值

	float countval = 0;//记录累加总和
	int itemnum = 0;//记录条数计数器

	bool bmin = true;//当记录为第一条记录时，给minval赋当前记录值
	bool bLast = true;//第一条记录即为最新值

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)//取下一条记录，并判断循环
	{		
		TTime tm;
		iv = 0;
		fv = 0.0;
		
		bool bret = GetRecordValueByField(hRec, fieldname, type, stat, iv, fv, sv);//按指定字段名取记录值
		if(stat == 4)//如果stat为4即禁止状态
		{
			//给最新值赋0
			if(bLast)
			{
				lastval = 0;
				bLast = false;
			}
		}
		else if((stat != 0) )//不为禁止状态
		{	
			GetRecordCreateTime(hRec,tm);//取当前记录时间		
						
			//与monitortemplet中取出的监测器返回类型比较是Int型
			if(strcmp(fieldtype.c_str(), "Int") == 0)
			{			
				//记录状态不为BAD
				if(stat != 5)
				{
					//如果是第一条记录，minval赋值
					if(bmin)
					{
						minval = iv;
						bmin = false;
					}
					
					//判断是否小于最大值，如果是则最大值赋为当前值
					if(maxval < iv)
					{
						maxval = iv;
					}

					//判断是否大于最小值，如果是则最小值赋为当前值
					if(minval > iv)
					{
						minval = iv;
					}
				
					//时间与Int型值push_back（必须一致）
					timelist.push_back(tm);
					intlist.push_back(iv);
					
					//累加整型记录值
					countval += iv;
				}
				else
				{
					timelist.push_back(tm);
					intlist.push_back(0);
				}

				//判断是否为最新值（为第一条记录）
				if(bLast)
				{
					lastval = iv;
					bLast = false;
				}
				
			}
			//与monitortemplet中取出的监测器返回类型比较是Float型
			else if(strcmp(fieldtype.c_str(), "Float") == 0)
			{
				//记录状态不为BAD
				if(stat != 5)
				{
					//如果是第一条记录，minval赋值
					if(bmin)
					{
						minval = fv;
						bmin = false;
					}

					//判断是否小于最大值，如果是则最大值赋为当前值
					if(maxval < fv)
					{
						maxval =fv;
					}

					//判断是否大于最小值，如果是则最小值赋为当前值
					if(minval >fv)
					{
						minval = fv;
					}
				
					//时间与Int型值push_back（必须一致）
					timelist.push_back(tm);
					floatlist.push_back(fv);
					
					//累加浮点型记录值
					countval += fv;		
				}
				else
				{
					timelist.push_back(tm);
					floatlist.push_back(0);
				}
				//判断是否为最新值（为第一条记录）
				if(bLast)
				{
					lastval = fv;
					bLast = false;
				}
			}
			//与monitortemplet中取出的监测器返回类型比较是String型
			else if(strcmp(fieldtype.c_str(), "String") == 0)
			{
				//时间与String型值push_back（必须一致）
				stringlist.push_back(sv);
				timelist.push_back(tm);

				//最大值、最小值、最新值都赋为0
				minval = 0;
				maxval = 0;
				if(bLast)
				{
					lastval = 0;
					bLast = false;
				}
				
			}

			//记录状态为BAD则记录条数不累加
			//if(stat != 5)
			{
				itemnum++;
			}
		}
				
	}

	//记录条数为零， 平均值为零，否则由累加和除以记录条数计算
	if(itemnum == 0)
	{
		perval = 0;
	}
	else
	{
		perval = countval/itemnum;
	}

	//返回的记录总条数
	reccount = itemnum;
}
*/


/*******************************************************
参数：
	hRecSet：查询指定监测器数据库句柄
	fieldname：需查询的字段名
	fieldtype：字段名类型即指定监测器返回值类型
	intlist：字段名为Int型时数据存储的LIST
	floatlist：字段名为Float型数据存储的LIST
	stringlist：字段名为String型数据存储的LIST
	timelist：与数据对应的记录创建时间LIST
	maxval：返回的最大值
	minval：返回的最小值
	perval：返回的平均值
	lastval：返回的最新值
	reccount：返回的记录总数

功能：
	按数据库句柄取记录及获取各指标数据
********************************************************/
void CTrendReport::GetMonitorDataRec(RECORDSET hRecSet, 
									 std::string fieldname,
									 std::string fieldtype, 
									 std::list<int> & intlist, 
									 std::list<float> & floatlist,
									 std::list<string> & stringlist,
									 std::list<int> & badlist,//11-10
									 std::list<TTime> & timelist, 
									 float & maxval,
									 float & minval, 
									 float & perval, 
									 float & lastval, 
									 int & reccount)
{
	LISTITEM item;
	RECORD hRec;

	//取记录集中第一条记录的OBJECT
	FindRecordFirst(hRecSet, item);
			
	int type;//记录返回类型
	int stat;//记录返回状态
	int iv;//整型值
	float fv;//浮点型值
	std::string sv;//字符串值

	float countval = 0;//记录累加总和
	int itemnum = 0;//记录条数计数器

	bool bmin = true;//当记录为第一条记录时，给minval赋当前记录值
	bool bLast = true;//第一条记录即为最新值

	int iBef = 0;
	bool bStat = false;

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)//取下一条记录，并判断循环
	{		
		TTime tm;
		iv = 0;
		fv = 0.0;
		
		if(strcmp(fieldtype.c_str(), "Int") == 0)
		{
			iBef = iv;
		}
		else if(strcmp(fieldtype.c_str(), "Float") == 0)
		{
			iBef = fv;
		}
		else
		{
			iBef = 0;
		}

		bool bret = GetRecordValueByField(hRec, fieldname, type, stat, iv, fv, sv);//按指定字段名取记录值
		if(stat == 4)//如果stat为4即禁止状态
		{
			//给最新值赋0
			if(bLast)
			{
				lastval = 0;
				bLast = false;
			}
		}
		else if((stat != 0) )//不为禁止状态
		{	
			GetRecordCreateTime(hRec,tm);//取当前记录时间		
						
			//与monitortemplet中取出的监测器返回类型比较是Int型
			if(strcmp(fieldtype.c_str(), "Int") == 0)
			{			
				//记录状态不为BAD
				if(stat != 5)
				{
					//如果是第一条记录，minval赋值
					if(bmin)
					{
						minval = iv;
						bmin = false;
					}
					
					//判断最大值是否小于当前值，如果是则最大值赋为当前值
					if(maxval < iv)
					{
						maxval = iv;
					}

					//判断最小值是否大于当前值，如果是则最小值赋为当前值
					if(minval > iv)
					{
						minval = iv;
					}
				
					//时间与Int型值push_back（必须一致）
					timelist.push_back(tm);
					intlist.push_back(iv);
					
					//累加整型记录值
					countval += iv;
				}
				else
				{
					
				}

				//判断是否为最新值（为第一条记录）
				if(bLast)
				{
					lastval = iv;
					bLast = false;
				}
				
			}
			//与monitortemplet中取出的监测器返回类型比较是Float型
			else if(strcmp(fieldtype.c_str(), "Float") == 0)
			{
				//记录状态不为BAD
				if(stat != 5)
				{
					//如果是第一条记录，minval赋值
					if(bmin)
					{
						minval = fv;
						bmin = false;
					}

					//判断最大值是否小于当前值，如果是则最大值赋为当前值
					if(maxval < fv)
					{
						maxval =fv;
					}

					//判断最小值是否大于当前值，如果是则最小值赋为当前值
					if(minval > fv)
					{
						minval = fv;
					}
				
					//时间与Int型值push_back（必须一致）
					timelist.push_back(tm);
					
					floatlist.push_back(fv);
					
					//累加浮点型记录值
					countval += fv;		
				}
				else
				{					
					
				}
				//判断是否为最新值（为第一条记录）
				if(bLast)
				{
					lastval = fv;
					bLast = false;
				}
			}
			//与monitortemplet中取出的监测器返回类型比较是String
			else if(strcmp(fieldtype.c_str(), "String") == 0)
			{
				//时间与String型值push_back（必须一致）
				stringlist.push_back(sv);
				timelist.push_back(tm);

				//最大值、最小值、最新值都赋为0
				minval = 0;
				maxval = 0;
				if(bLast)
				{
					lastval = 0;
					bLast = false;
				}				
			}

			//if(!bmin)//如果BAD记录不为第一条则添加至badlist
			{
				
				//记录状态为BAD则记录条数不累加
				if(stat != 5)
				{
					if(!bStat)
					{
						if(strcmp(fieldtype.c_str(), "Int") == 0)
						{
							badlist.push_back(iv);
						}
						else if(strcmp(fieldtype.c_str(), "Float") == 0)
						{
							int itemp = fv;
							badlist.push_back(itemp);
						}
						else
						{
							badlist.push_back(0);
						}
						
					}
					else
					{
						badlist.push_back(0);
					}

					itemnum++;
					bStat = true;
				}
				else
				{
					itemnum++;
					if(strcmp(fieldtype.c_str(), "Int") == 0)
					{
						intlist.push_back(0);
					}
					else if(strcmp(fieldtype.c_str(), "Float") == 0)
					{
						floatlist.push_back(0);
					}
					else
					{
						stringlist.push_back("0");
					}
					timelist.push_back(tm);
					if(bStat)
					{
						badlist.push_back(iBef);						
						bStat = false;
					}
					//badlist.push_back(0);
				}
			}
		}
				
	}

	//记录条数为零， 平均值为零，否则由累加和除以记录条数计算
	if(itemnum == 0)
	{
		perval = 0;
	}
	else
	{
		perval = countval/itemnum;
	}

	//返回的记录总条数
	reccount = itemnum;

}
//
void CTrendReport::GetMonitorGroup(char * reportname, std::list<string> & grouplist)
{
	std::string buf1 = reportname;
	int pos = buf1.find("=", 0);
	std::string querystr = buf1.substr(pos+1, buf1.size() - pos - 1);
			
	std::string defaultret = "error";
	std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "reportset.ini");

	int pos2 = 0;
	int pos1;
	
	
	while(pos2 >= 0)
	{
		pos1 = pos2;
		pos2 = groupright.find(",", ++pos2 );
		std::string tempstr = groupright.substr(pos1 + 1, pos2 - pos1 - 1);			
		grouplist.push_back(tempstr);			
	}						
}

//
void CTrendReport::InitPageItem(WTable *table, std::string title)
{
	pFrameTable = new WTable(this->elementAt(0,0));	

	pFrameTable ->setStyleClass("t5");
	/*pFrameTable->setStyleClass("StatsTable");	
	pFrameTable->tableprop_ = 2;
	pFrameTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
*/
	WTable * column = new WTable((WContainerWidget*)pFrameTable->elementAt(1, 0));
	pFrameTable->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);
	//column->setStyleClass("t5");
	column->setStyleClass("StatsTable");

	//std::string linkstr = "<a href='../fcgi-bin/statsreportlist.exe?id=";
	//linkstr += title;
	//linkstr += "'>返回</a>";
	//new WText(linkstr, (WContainerWidget*)column->elementAt(0, 0));

	column->elementAt(0, 0)->setStyleClass("t1title");
	column->elementAt(0, 0)->setContentAlignment(AlignTop | AlignRight);
	pContainTable = new WTable((WContainerWidget*)pFrameTable->elementAt(2,0));
/*	WScrollArea * pScrollArea = new WScrollArea(this);

	pScrollArea->setStyleClass("t5");
	pContainTable->setStyleClass("t5");
	pScrollArea->setWidget(pContainTable);
*/
	pContainTable ->setStyleClass("t5");
	pReportTitle = new WText(title, (WContainerWidget*)pContainTable->elementAt(0, 0));
	pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	WFont font1;
	font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);

	WText * text1 = new WText(szInterTime, (WContainerWidget*)pContainTable->elementAt(1, 0));
	pContainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	text1 = new WText(m_formText.szRunTitle, pContainTable->elementAt(2, 0));
	font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
	text1 ->decorationStyle().setFont(font1);
	pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
	pRunTable = new WTable(pContainTable->elementAt(3, 0));
	//pRunTable ->setStyleClass("t5");
	//pRunTable -> setStyleClass("t5");

	pRunTable->setStyleClass("StatsTable");	
	pRunTable->tableprop_ = 2;
	pRunTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(3, 0)->setContentAlignment(AlignTop | AlignCenter);

	text1 = new WText(m_formText.szMonitorTitle, pContainTable->elementAt(4, 0));
	text1 ->decorationStyle().setFont(font1);
	pContainTable ->elementAt(4, 0) ->setContentAlignment(AlignTop | AlignCenter);
	pMonitorTable = new WTable(pContainTable->elementAt(5, 0));
	//pMonitorTable ->setStyleClass("t5");
	pMonitorTable->setStyleClass("StatsTable");	
	pMonitorTable->tableprop_ = 2;
	pMonitorTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(5, 0)->setContentAlignment(AlignTop | AlignCenter);

	//text1 = new WText("图表", pContainTable->elementAt(6, 0));
	text1 = new WText(m_formText.szChart, pContainTable->elementAt(6, 0));
	text1 -> decorationStyle().setFont(font1);
	pContainTable -> elementAt(6, 0) -> setContentAlignment(AlignTop | AlignCenter);

}

//
void CTrendReport::WriteGenIni(std::string reportname, std::string starttime,std::string endtime,std::string value,std::string fieldlabel, float minval, float perval,float maxval)
{
	char buf[256];

	std::string section = reportname;
	section += "$";
	section += starttime;
	section += "$";
	section += endtime;
	section += "$";

	std::string keystr = value;
	keystr += "$";
	keystr += fieldlabel;
	keystr += "$";
	
	std::string valstr ;
	
	memset(buf, 0, 256);
	sprintf(buf, "%0.0f", minval);
	valstr = buf;
	valstr += "$";
	memset(buf, 0, 256);
	sprintf(buf, "%0.0f", perval);
	valstr += buf;
	valstr += "$";
	memset(buf, 0, 256);
	sprintf(buf, "%0.0f", maxval);
	valstr +=buf;
	valstr += "$";

	WriteIniFileString(section, keystr, valstr, "reportgenerate.ini");
}

std::string CTrendReport::GetLabelResource(std::string strLabel)
{
	OutputDebugString("strLabel = ");
	OutputDebugString(strLabel.c_str());
	OutputDebugString("\n");

	string strfieldlabel ="";
	if( resourceNode != INVALID_VALUE )
		FindNodeValue(resourceNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
		strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

//
void CTrendReport::GetMonitorRecord(std::string monitorid, TTime starttime, TTime endtime, bool bClicket,bool bListStatsResult, std::string reportname, int &tcount, int & i6, int & i3, int & fieldnum)
{
		char *pielabel[3] ;
		wchar_t lpWide[256];
		LPCWSTR lpWideCharStr =L"";
		int slen = 256;
		int wlen = 256;

		pielabel[0] = (char*)malloc(256);
		pielabel[1] = (char*)malloc(256);
		pielabel[2] = (char*)malloc(256);
		LPSTR lpMultiByteStr= (LPSTR)malloc(256);

		//解决中文版ECC在生成报表时图片出现乱码的问题
		//+++++++++++++++++苏合 2007-07-16 代码更改开始+++++++++++++++++

		/* 对原来的代码此段进行修改
		//设置中文
		setlocale(LC_CTYPE, ""); 
		*/

		string IniPath("\\data\\svdbconfig.ini");
		IniPath = GetSiteViewRootPath() + IniPath;
		char sxcbuf[256]={0};
		GetPrivateProfileString("svdb","DefaultLanguage","",sxcbuf,255,IniPath.c_str());
		if (0 == strcmp("chinese", sxcbuf))
		{
			setlocale(LC_CTYPE, "chs");
			OutputDebugString("设置为中文");
		}
		else 
		{
			setlocale(LC_CTYPE, "");
		}		
		//+++++++++++++++++苏合 2007-07-16 代码更改结束+++++++++++++++++

		memset(lpWide, 0, 256);
		mbstowcs(lpWide, m_formText.szXLSNormal.c_str(), 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
		strcpy(pielabel[0], lpMultiByteStr);

		memset(lpWide, 0, 256);
		memset(lpMultiByteStr, 0, 256);
		mbstowcs(lpWide, m_formText.szWarning.c_str(), 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
		strcpy(pielabel[1], lpMultiByteStr);

		memset(lpWide, 0, 256);
		memset(lpMultiByteStr, 0, 256);
		mbstowcs(lpWide, m_formText.szXLSError.c_str(), 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
		strcpy(pielabel[2], lpMultiByteStr);

		double piedata[64];//饼图数据
		
		double data[50000];	
		double time[50000];
		char buf[256];
		char buf2[256];
		OBJECT hMon = GetMonitor(monitorid);
		
		LISTITEM item;
		RECORD hRec;

		int normalnum = 0;
		int dangernum = 0;
		int errornum = 0;
		int othernum = 0;

		int stat = 0;
		int perval = 0;
		int laststat = 0;

		std::string dispstr;

		std::list<string> allstrlist;
	//	std::list<string> timelist;

		int reccount = 0;
		string monitorname = "";


		RECORDSET hRecSet = QueryRecords(monitorid, m_starttime, m_endtime);//取监测器数据集句柄
		//新增 cxy 06/11/23
		GetReocrdSetField(hRecSet, fieldlist);

		size_t countrec;
		GetRecordCount(hRecSet,countrec);//监测器数据记录条数
		tcount += countrec;

		FindRecordFirst(hRecSet, item);
		
		TTime tm = TTime(starttime.GetYear(),starttime.GetMonth(), starttime.GetDay(), starttime.GetHour(), starttime.GetMinute(), starttime.GetSecond());
		
		bool bStat = true;
		while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
		{	
			
			GetRecordCreateTime(hRec,tm);
//			timelist.push_back(tm.Format());

			GetRecordDisplayString(hRec, stat,dispstr);
			
			if(bStat)
			{
				laststat = stat;
				bStat = false;
			}

			if(stat == 1)
			{
				normalnum++;				
			}
			else if(stat == 2)
			{
				dangernum++;				
			}
			else
			{
				errornum++;				
			}
			
			allstrlist.push_back(dispstr);//字符显示记录队列									
		}		

		//double cstarttime = Chart::chartTime(starttime.GetYear(), starttime.GetMonth(), starttime.GetDay(), starttime.GetHour(), starttime.GetMinute(), starttime.GetSecond());
		double cstarttime = Chart::chartTime(tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

		MAPNODE node = GetMonitorMainAttribNode(hMon);
	
		FindNodeValue(node, "sv_name", value);//需要判断是监测器还是组

		string strEntity =	FindParentID(monitorid);
		OBJECT hEntity = GetEntity(strEntity);
		MAPNODE entitynode = GetEntityMainAttribNode(hEntity);
		std::string entityvalue;
		FindNodeValue(entitynode, "sv_name", entityvalue);

		std::string hrefstr = "<a href='#"; 
		hrefstr += entityvalue;
		hrefstr += ":";
		hrefstr += value;
		hrefstr += "'>";
		
		hrefstr += entityvalue;
		hrefstr += ":";

		hrefstr += value;
		hrefstr += "</a>";

		szEntityMonitor = entityvalue;
		szEntityMonitor += ":";
		szEntityMonitor += value;

		m_pUptimeTable->InitRow(i6);
		new WText(hrefstr, m_pUptimeTable->GeDataTable()->elementAt(i6,0));

	//	new WText(hrefstr, pRunTable->elementAt(i6, 0));


		memset(buf2, 0, 256);
		if((normalnum + dangernum + errornum + othernum) != 0)
		{
			perval = normalnum*100/(normalnum + dangernum + errornum + othernum);
			sprintf(buf2, "%d", perval);

			//new WText(buf2, pRunTable->elementAt(i6, 1));
			m_pUptimeTable->GeDataTable()->elementAt(i6, 2)->setContentAlignment(AlignCenter);
			new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 2));

			perval = dangernum*100/(normalnum + dangernum + errornum + othernum);
			sprintf(buf2, "%d", perval);

			//new WText(buf2, pRunTable->elementAt(i6, 2));
			m_pUptimeTable->GeDataTable()->elementAt(i6, 4)->setContentAlignment(AlignCenter);
			new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 4));
			
			perval = errornum*100/(normalnum + dangernum + errornum + othernum);
			sprintf(buf2, "%d", perval);
			//new WText(buf2, pRunTable->elementAt(i6, 3));
			m_pUptimeTable->GeDataTable()->elementAt(i6, 6)->setContentAlignment(AlignCenter);
			new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 6));
			
			m_pUptimeTable->GeDataTable()->elementAt(i6, 8)->setContentAlignment(AlignCenter);
			switch(laststat)
			{
			case 1:
				//new WText("正常", pRunTable->elementAt(i6, 4));
				new WText("正常", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
				break;
			case 2:
				//new WText("危险", pRunTable->elementAt(i6, 4));
				new WText("危险", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
				break;
			case 3:
				//new WText("错误", pRunTable->elementAt(i6, 4));
				new WText("危险", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
				break;
			case 4:
				//new WText("禁止", pRunTable->elementAt(i6, 4));
				new WText("危险", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
				break;
			case 5:
				//new WText("BAD", pRunTable->elementAt(i6, 4));
				new WText("危险",m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
				break;
			case 0:
				//new WText("NULL", pRunTable->elementAt(i6, 4));
				new WText("危险", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
				break;
			default:
				break;
			}
		}		

		//监测器返回值
		std::list<string> retliststr;
		std::list<string> retlisttype;
		OBJECT hTemplet;
	//	std::string monitorname;
		MAPNODE objNode;

		
		if(hMon != INVALID_VALUE)
		{			
			std::string getvalue;
			MAPNODE ma=GetMonitorMainAttribNode(hMon);
			
			if ( FindNodeValue( ma,"sv_monitortype",getvalue))
			{			
				hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				FindNodeValue(node, "sv_label", monitorname);

				
				//MAPNODE	GetMTErrorAlertCondition(OBJECT mtobj);
				//报告设置是否显示阀值
				std::string szErrorValue;
				if(bClicket)
				{					
					MAPNODE errorNode = GetMTErrorAlertCondition(hTemplet);
					FindNodeValue(errorNode, "sv_value", szErrorValue);

					//new WText(szErrorValue.c_str(), pRunTable->elementAt(i6, 5));
					
					new WText(szErrorValue.c_str(), m_pUptimeTable->GeDataTable()->elementAt(i6, 10));
				}
				szErrorValue = "";
			}
			else
			{
				return;
			}
			std::list<int> retstatlist1;
			std::list<string> retstrlist1;
			std::list<string> rettimelist1;
			std::list<string> retmonnamelist1;
		
			bool bRet = FindMTReturnFirst(hTemplet, item);
							
			if(bRet)
			{
				std::string fieldlabel;
				std::string fieldname;
				std::string fieldtype;
				
				float maxval = 0.0;
				float maxval1 = 0.0;
				float minval = 0.0;
				float perval = 0.0;
				float lastval = 0.0;

				std::string returnimage ;
				std::string returnstats ;
				std::string returndata ;

				gfieldnum = 0;
				int npie = 0;
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{			
					FindNodeValue(objNode, "sv_label", fieldlabel);
					fieldlabel =GetLabelResource(fieldlabel);

					retliststr.push_back(fieldlabel);	
					FindNodeValue(objNode, "sv_type", fieldtype);				
					retlisttype.push_back(fieldtype);
					FindNodeValue(objNode, "sv_name", fieldname);

															
					//取监测器报告显示项
					FindNodeValue(objNode, "sv_drawimage", returnimage);
					FindNodeValue(objNode, "sv_drawtable", returnstats);
					FindNodeValue(objNode, "sv_drawmeasure", returndata);

					maxval = 0;
					perval = 0;
					lastval = 0;
					std::list<int> intlist;
					std::list<float> floatlist;
					std::list<string> stringlist;
					std::list<TTime> timelist;
					std::list<int>::iterator intitem;
					std::list<float>::iterator floatitem;
					std::list<string>::iterator stringitem;
					std::list<TTime>::iterator timeitem;
					std::list<int> badlist;
					int count = 0;

					intlist.clear();
					floatlist.clear();
					stringlist.clear();
					
					//按字段取监测器记录队列
					GetMonitorDataRec(hRecSet, fieldname, fieldtype, intlist , floatlist, stringlist,badlist,timelist, maxval, minval, perval, lastval, reccount); 
					retfieldname[gfieldnum] = fieldlabel.c_str();										
					gfieldnum++;
					

					//如果不是主键值则不生成监测数据统计及图表
					std::string szPrimary;
					FindNodeValue(objNode, "sv_primary",szPrimary);
					if(strcmp(szPrimary.c_str(), "1") == 0)
					{						
						//WriteGenIni(reportname, starttime.Format(), endtime.Format(), value, fieldlabel, minval, perval, maxval);
					}
					else
					{
						//continue;
					}
					

					//数组赋值
					for(floatitem = floatlist.begin(), intitem = intlist.begin(), stringitem = stringlist.begin(),timeitem = timelist.begin(); \
						(timeitem != timelist.end()); floatitem++, intitem++, stringitem++, timeitem++)
					{
						TTime ctm = *timeitem;
						time[reccount - 1 - count] = Chart::chartTime(ctm.GetYear(), ctm.GetMonth(), ctm.GetDay(), ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());

						if(strcmp(fieldtype.c_str(), "Int") == 0)
						{	
						
							data[reccount - 1 - count] = *intitem;
							
						}
						else if(strcmp(fieldtype.c_str(), "Float") == 0)
						{
							
							data[reccount - 1 - count] = *floatitem;
						
						}
						else if(strcmp(fieldtype.c_str(), "String") == 0)
						{							
							string stringitemstr = *stringitem;
							data[reccount - 1 - count] = atof(stringitemstr.c_str());
							
						}						
						count++;						
					}	
					
					
					std::string imgtabletitle;
					std::string hrefstring;
					//图形显示
					if(strcmp(returnimage.c_str(), "1") == 0)
					{
						std::string namebuf;
						std::string namebuf1;

						string	szRootPath = GetSiteViewRootPath();
						string szIconPath = szRootPath;
						szIconPath += "\\htdocs\\report\\Images\\";

						namebuf = szIconPath;					
		
						std::string timestr = m_starttime.Format();
						timestr = replace_all_distinct(timestr, " ", "_");
						namebuf1 = timestr;
						timestr = m_endtime.Format();
						timestr = replace_all_distinct(timestr, " ", "_");
						namebuf1 += timestr;
						
						std::string namebuf3 = namebuf1;
						namebuf3 += reportname;
						namebuf3 += "\\";
						
						namebuf3 = replace_all_distinct(namebuf3, ":", "_");
						
						namebuf += namebuf3;						
						
						WIN32_FIND_DATA fd;
						HANDLE fr=::FindFirstFile(namebuf.c_str(),&fd);
						if(!::FindNextFile(fr, &fd))
						{
							CreateDirectory(namebuf.c_str(), NULL);
						}

						namebuf1 += value;
						itoa(rand(), buf, 10);
						namebuf1 += buf;
						
						namebuf1 += ".png";
						
						//namebuf = replace_all_distinct(namebuf, " ", "_");
						namebuf1 = replace_all_distinct(namebuf1, ":", "_");
						namebuf1 = replace_all_distinct(namebuf1, "<", "_");
						namebuf1 = replace_all_distinct(namebuf1, ">", "_");
						namebuf1 = replace_all_distinct(namebuf1, "\\", "_");
						namebuf1 = replace_all_distinct(namebuf1, "/", "_");

						namebuf += namebuf1;

						//double cstarttime = Chart::chartTime(starttime.GetYear(), starttime.GetMonth(), starttime.GetDay(), starttime.GetHour(), starttime.GetMinute(), starttime.GetSecond());
						double cendtime =Chart::chartTime(endtime.GetYear(), endtime.GetMonth(), endtime.GetDay(), endtime.GetHour(), endtime.GetMinute(), endtime.GetSecond());
						
						//加上设备Entity
						imgtabletitle = entityvalue;
						imgtabletitle += ":";

						imgtabletitle += value;
						
						hrefstring = imgtabletitle;

						imgtabletitle += "(";
						imgtabletitle += fieldlabel;
						imgtabletitle += ")";
						//hrefstring = imgtabletitle;

						imgtabletitle += "\n";

						imgtabletitle += m_formText.szMaxValue;
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", maxval);
						imgtabletitle += buf2;
						imgtabletitle += m_formText.szAverageValue;
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", perval);
						imgtabletitle += buf2;
						imgtabletitle += m_formText.szMinValue;
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", minval);
						imgtabletitle += buf2;											

						//返回
						std::string unitstr;
						FindNodeValue(objNode, "sv_unit", unitstr);
						if(strcmp(unitstr.c_str(), "(%)") == 0)
						{
							//maxval = 100;
							GenLineImage(data, time, count, NULL, 100, 10, NULL, 0, 100, 20, count, cstarttime, cendtime,(char*)imgtabletitle.c_str(), (char*)fieldlabel.c_str(), (char*)namebuf.c_str());
						}
						else
						{
							GenLineImage(data, time, count, NULL, 100, 10, NULL, 0, maxval, 20, count, cstarttime, cendtime,(char*)imgtabletitle.c_str(), (char*)fieldlabel.c_str(), (char*)namebuf.c_str());
						}
						
						//监测数据统计表跳转指向名称：监测器名（返回值）
						std::string temptitle = "<a name='" + hrefstring + "'>" + "</a>";
						new WText(temptitle, m_pChartTable->GetContentTable()->elementAt(i3, 0));
						
												
						std::string namebuf2 = "../report/Images/";
						namebuf2 += namebuf3;
						namebuf2 += "/";
						namebuf2 += namebuf1;

						/*std::string hreficon = "<a href='";
						hreficon += namebuf2;
						hreficon += "'>";
						hreficon += namebuf2;
						hreficon += "</a>";
						*/
						
						szXSLImage += "<a href=";
						szXSLImage += namebuf2;
						szXSLImage += ">";
						szXSLImage += namebuf2;
						szXSLImage += "</a>";
						szXSLImage += "<br>";

						if(strcmp(returndata.c_str(), "1") == 0)
						{
							GetMonitorDataRecStr(hRecSet, value, retmonnamelist1, retstatlist1, retstrlist1, rettimelist1);	
							int num = retdangernamelist.size() + retnormalnamelist.size() + reterrornamelist.size();
							int pierand = rand();
							char piebuf[256];
							sprintf(piebuf, "../htdocs/report/Images/%d", pierand);
							strcat(piebuf, ".png");

							if(num != 0)
							{
								//piedata[0] = (retnormalnamelist.size() * 100/num) ;
								//piedata[1] = (retdangernamelist.size() * 100/num) ;
								//piedata[2] = (reterrornamelist.size() * 100/num) ;
								piedata[0] = retnormalnamelist.size();
								piedata[1] = retdangernamelist.size();
								piedata[2] = reterrornamelist.size();

								if(npie == 0)
								{
									GenPieImage((char*)fieldlabel.c_str(), (char**)pielabel, piedata, 3, piebuf);
								
								
									char tbuf[256];
									OutputDebugString("--------pie image path----------\n");
									sprintf(tbuf, "%d %d %d\n", retnormalnamelist.size(), retdangernamelist.size(), reterrornamelist.size());
									OutputDebugString(tbuf);
									OutputDebugString(piebuf);
									OutputDebugString("\n");

									memset(piebuf, 0, 256);
									sprintf(piebuf, "../report/Images/%d", pierand);
									strcat(piebuf, ".png");

									new WImage(piebuf, m_pChartTable->GetContentTable()->elementAt(i3, 0));
									i3++;
								}
								npie++;
							}
							
						}
						//new WImage(namebuf2, (WContainerWidget*)pImageTable->elementAt(i3, 0));

						m_pChartTable->GetContentTable()->elementAt(i3,0)->setContentAlignment(AlignTop | AlignCenter);
						new WText(temptitle, (WContainerWidget*)m_pChartTable->GetContentTable()->elementAt(i3, 0));
						new WImage(namebuf2, m_pChartTable->GetContentTable()->elementAt(i3,0));
						i3 += 1;
						new WText("&nbsp;",m_pChartTable->GetContentTable()->elementAt(i3,0));
						
						//pImageTable->elementAt(i3, 0) ->setContentAlignment(AlignTop | AlignCenter);
						i3++;	
					}
					//监测统计显示
					if(bListStatsResult)
					{
						if(strcmp(returnstats.c_str(), "1") == 0)
						{
							//构造链接指向

							std::string firstfield = entityvalue;
							firstfield += value;
							
							std::string hrefstr = "<a href='#";
							hrefstr += hrefstring;
							//hrefstr += monitorid;
							hrefstr += "'>";
							hrefstr += firstfield;
						/*	hrefstr += "(";
							hrefstr += monitorid;
							hrefstr += ")";
							*/
							hrefstr += "</a>";

							m_pMeasurementTable->InitRow(fieldnum);

							new WText(hrefstr, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0 ));

							m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 2 )->setContentAlignment(AlignCenter);
							new WText(fieldlabel, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 2 ));


							/*new WText(hrefstr, pMonitorTable->elementAt(fieldnum, 0));
							new WText(fieldlabel, pMonitorTable->elementAt(fieldnum, 1));*/

							memset(buf2, 0, 256);
							sprintf(buf2, "%0.0f", maxval);
							//new WText(buf2, pMonitorTable->elementAt(fieldnum, 2));
							m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 4 )->setContentAlignment(AlignCenter);
							new WText(buf2,m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 4));

							
							memset(buf2, 0, 256);					
							sprintf(buf2, "%0.0f", perval);
							//new WText(buf2, pMonitorTable->elementAt(fieldnum, 3));
							m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 6 )->setContentAlignment(AlignCenter);
							new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 6));

							memset(buf2, 0, 256);
							sprintf(buf2, "%0.0f", lastval);
							//new WText(buf2, pMonitorTable->elementAt(fieldnum, 4));
							m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 8)->setContentAlignment(AlignCenter);
							new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 8));

							fieldnum++;					
						}
					}
					else
					{

					}
				
				}

				
				//判断数据是否显示
				if(strcmp(returndata.c_str(), "1") == 0)
				{
					GetMonitorDataRecStr(hRecSet, value, retmonnamelist1, retstatlist1, retstrlist1, rettimelist1);	
					int num = retdangernamelist.size() + retnormalnamelist.size() + reterrornamelist.size();
					int pierand = rand();
					char piebuf[256];
					sprintf(piebuf, "%d", pierand);
					strcat(piebuf, ".png");

					piedata[0] = (retnormalnamelist.size()/num) * 100;
					piedata[1] = (retdangernamelist.size()/num) * 100;
					piedata[2] = (reterrornamelist.size()/num) * 100;

					GenPieImage((char*)fieldlabel.c_str(), (char**)pielabel, piedata, 3, piebuf);
				}
			}		
		}	

		if(hMon != INVALID_VALUE)
		{
			std::string getvalue;												
			MAPNODE ma=GetMonitorMainAttribNode(hMon) ;
				
			if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
			{			
				hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				FindNodeValue(node, "sv_label", monitorname);
				//监测器阀值
				std::string szErrorValue;
				MAPNODE errorNode = GetMTErrorAlertCondition(hTemplet);
				FindNodeValue(errorNode, "sv_value", szErrorValue);
			}
			else
			{
				return;
			}

			
			bool bRet = FindMTReturnFirst(hTemplet, item);
			MAPNODE objNode;
			string strIDS;

			if(bRet)
			{
				
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					FindNodeValue(objNode, "sv_label", strIDS);
					
					//from ids to real value
					value ="";
					if( resourceNode != INVALID_VALUE )
							FindNodeValue(resourceNode,strIDS,value);
					if(value=="")
							value = strIDS;

					liststr.push_back(value);	
					FindNodeValue(objNode, "sv_type", value);				
				//	listtype.push_back(value);
				}
			}	
		}
		CloseMonitor(hMon);

		i6++;

		CloseRecordSet(hRecSet);
		free(pielabel[0]);
		free(pielabel[1]);
		free(pielabel[2]);
}

//
void CTrendReport::DataBack()
{
	//OutputDebugString("DataBack");
	nCurPage--;

	//
	if(nCurPage < 1)
		nCurPage = 1;

	//
	RefreshList();
}

//
void CTrendReport::DataForward()
{
	nCurPage++;
	
	if(nCurPage >= nTotalPage)
		nCurPage = nTotalPage;

	//
	RefreshList();
}

//
void CTrendReport::DataReturn()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "DataReturn";
	LogItem.sDesc = strReturn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//pDataTable->hide();	

	//pFrameTable->show();	
	//pDataCmdTable->show();	
	//pCopyRightInfo->show();	

	m_pListMainTable->show();
	m_pDataTable->hide();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
void CTrendReport::NormalBtn()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "NormalBtn";
	LogItem.sDesc = strNormalBtn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);
	
	nCurDataType = 1;
	//pDataTable->show();	

	//pFrameTable->hide();	
	//pDataCmdTable->hide();
	//pCopyRightInfo->hide();	

	//new 
	m_pListMainTable->hide();
	m_pDataTable->show();

	//计算总页数等
	if(retnormalnamelist.size() % nPageCount  > 0)
	{
		nTotalPage = retnormalnamelist.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = retnormalnamelist.size() / nPageCount;
		bDivide = true;
	}		
	
	if(nTotalPage > 0)
		nCurPage = 1;
	else
		nCurPage = 0;
	
	RefreshList();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
void CTrendReport::ErrorBtn()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "ErrorBtn";
	LogItem.sDesc = strErrorBtn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	nCurDataType = 2;
	//pDataTable->show();	

	//pFrameTable->hide();	
	//pDataCmdTable->hide();	
	//pCopyRightInfo->hide();	

	m_pListMainTable->hide();
	m_pDataTable->show();

	//计算总页数等
	if(reterrornamelist.size() % nPageCount  > 0)
	{
		nTotalPage = reterrornamelist.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = reterrornamelist.size() / nPageCount;
		bDivide = true;
	}		
	
	if(nTotalPage > 0)
		nCurPage = 1;
	else
		nCurPage = 0;

	RefreshList();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
void CTrendReport::WarnningBtn()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "WarnningBtn";
	LogItem.sDesc = strWarnningBtn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	nCurDataType = 3;
	//pDataTable->show();	

	//pFrameTable->hide();	
	//pDataCmdTable->hide();	
	//pCopyRightInfo->hide();	
	
	m_pListMainTable->hide();
	m_pDataTable->show();

	//计算总页数等
	if(retdangernamelist.size() % nPageCount  > 0)
	{
		nTotalPage = retdangernamelist.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = retdangernamelist.size() / nPageCount;
		bDivide = true;
	}		
	
	if(nTotalPage > 0)
		nCurPage = 1;
	else
		nCurPage = 0;

	RefreshList();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CTrendReport::SaveExcelBtn()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TrendReport";
	LogItem.sHitFunc = "SaveExcelBtn";
	LogItem.sDesc = m_formText.szExcelBut;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	OutputDebugString("------------start SaveExcelBtn()-------------------\n");
	std::string szRootPath =GetSiteViewRootPath();
	szRootPath += "\\htdocs\\data\\";
	//szRootPath = "c:\\";
	szRootPath += szXSLReportName;
	OutputDebugString(szRootPath.c_str());

	CSpreadSheet SS(szRootPath.c_str(), "TestSheet");

	CStringArray sampleArray, testRow;
	
	SS.BeginTransaction();
	
	// 加入标题
	sampleArray.RemoveAll();
	/*sampleArray.Add("名称");
	sampleArray.Add("时间");
	sampleArray.Add("状态");
	sampleArray.Add("数据");	
	*/
	sampleArray.Add(m_formText.szXLSName.c_str());
	sampleArray.Add(m_formText.szXLSTime.c_str());
	sampleArray.Add(m_formText.szXLSStatus.c_str());
	sampleArray.Add(m_formText.szXLSData.c_str());
	//SS.AddHeaders(sampleArray);
	//for(int k = 0; k < gfieldnum; k++)
	for(int k = 0; k < gfieldnum; k++)
	{
		OutputDebugString("-------------excel field name ----------------\n");
		OutputDebugString(retfieldname[k].GetBuffer());
		OutputDebugString("\n");
		
		if(strcmp(retfieldname[k].GetBuffer(), "名称") == 0 || strcmp(retfieldname[k].GetBuffer(), "时间") == 0
			|| strcmp(retfieldname[k].GetBuffer(), "状态") == 0|| strcmp(retfieldname[k].GetBuffer(), "数据") == 0)
		{
			retfieldname[k] += "1";
		}
		else
		{
		}
		sampleArray.Add(retfieldname[k]);
		
	}
	

	
	SS.AddHeaders(sampleArray);
	
	// 加入数据
	int num = retdangernamelist.size() + retnormalnamelist.size() + reterrornamelist.size();
	CString * strName = new CString[num];
	CString * strTime = new CString[num];
	CString * strData = new CString[num];
	CString * strStatus = new CString[num];

	int i = 0;
	for(retmonnamelistitem = retnormalnamelist.begin(), rettimelistitem = retnormaltimelist.begin(), retstrlistitem = retnormalstatuslist.begin();\
	retmonnamelistitem != retnormalnamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
	{
		//strStatus[i] = "正常";
		strStatus[i] = m_formText.szXLSNormal.c_str();
		string temp = *retmonnamelistitem;
		strName[i] = temp.c_str();	
		temp = *rettimelistitem;
		strTime[i] = temp.c_str();
		temp = *retstrlistitem;
		strData[i] = temp.c_str();
		i++;
	}

	for(retmonnamelistitem = reterrornamelist.begin(), rettimelistitem = reterrortimelist.begin(), retstrlistitem = reterrorstatuslist.begin();\
	retmonnamelistitem != reterrornamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
	{
		//strStatus[i] = "错误";
		strStatus[i] = m_formText.szXLSError.c_str();
		string temp = *retmonnamelistitem;
		strName[i] = temp.c_str();	
		temp = *rettimelistitem;
		strTime[i] = temp.c_str();
		temp = *retstrlistitem;
		strData[i] = temp.c_str();
		i++;
	}

	for(retmonnamelistitem = retdangernamelist.begin(), rettimelistitem = retdangertimelist.begin(), retstrlistitem = retdangerstatuslist.begin();\
	retmonnamelistitem != retdangernamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
	{
		//strStatus[i] = "危险";
		strStatus[i] = m_formText.szXLSDanger.c_str();
		string temp = *retmonnamelistitem;
		strName[i] = temp.c_str();	
		temp = *rettimelistitem;
		strTime[i] = temp.c_str();
		temp = *retstrlistitem;
		strData[i] = temp.c_str();
		i++;
	}

	for(int j = 0; j <  i; j++)
	{		
		
		sampleArray.RemoveAll();
		sampleArray.Add(szEntityMonitor.c_str());
		sampleArray.Add(strTime[j]);
		sampleArray.Add(strStatus[j]);
		sampleArray.Add(strData[j]);

		OutputDebugString("------------show trend report information-------------------\n");
		char buf[256];
		memset(buf, 0, 256);
		sprintf(buf, "entity:%s time:%s status:%s data:%s", szEntityMonitor.c_str(), strTime[j].GetBuffer(),\
			strStatus[j].GetBuffer(), strData[j].GetBuffer());
		OutputDebugString(buf);
		OutputDebugString("\n");

		char *stoken = NULL;
		stoken = strtok(strData[j].GetBuffer(), ",");
		while(stoken != NULL)
		{
			string signval = stoken;
			int pos = signval.find("=", 0);
			string signval1 = signval.substr(pos + 1, signval.size() - pos - 1 );
			sampleArray.Add(signval1.c_str());
			stoken = strtok(NULL, ",");
			
		}
		
		SS.AddRow(sampleArray);
		
	}
	
	SS.Commit();	

	delete [] strName;
	delete [] strTime;
	delete [] strData;

	for(int k = 0; k < gfieldnum; k++)
	{
	
	}
	OutputDebugString("---------------------success---------------------\n");
	//generate xsl file save for user
	/*WebSession::js_af_up = "window.showModalDialog('";
	WebSession::js_af_up += "/data/";
	WebSession::js_af_up += szXSLReportName;
	WebSession::js_af_up += "')";	
	*/
/*	WebSession::js_af_up = "showDownload('<a href=/data/";
	WebSession::js_af_up += szXSLReportName;
	WebSession::js_af_up += ">";
	WebSession::js_af_up += szXSLReportName;
	WebSession::js_af_up += "</a>');";
	*/

	//szXSLImage = RepHrefStr(szXSLImage);

	WebSession::js_af_up = "showDownload('<a href=/data/";
	WebSession::js_af_up += szXSLReportName;
	WebSession::js_af_up += ">";
	WebSession::js_af_up += szXSLReportName;
	WebSession::js_af_up += "</a><br>";	
	WebSession::js_af_up += szXSLImage;	
	WebSession::js_af_up += "', '";
	WebSession::js_af_up += m_formText.szDownloadList;
	WebSession::js_af_up += "', '";
	WebSession::js_af_up += m_formText.szClose;
	WebSession::js_af_up += "'";
	WebSession::js_af_up += ");";	
	
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//
void CTrendReport::AddDataColum(WSVFlexTable* pContain)
{
	/*new WText(strHNameLabel, pContain->elementAt(0, 0));
	new WText(strHTimeLabel, pContain->elementAt(0, 1));
	new WText(strHDataLabel, pContain->elementAt(0, 2));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
	*/
	pContain->AppendColumn(strHNameLabel,WLength(40,WLength::Percentage));
	pContain->SetDataRowStyle("table_data_grid_item_text");
	pContain->AppendColumn(strHTimeLabel,WLength(40,WLength::Percentage));
	pContain->SetDataRowStyle("table_data_grid_item_text");
	pContain->AppendColumn(strHDataLabel,WLength(40,WLength::Percentage));
	pContain->SetDataRowStyle("table_data_grid_item_text");
}

//
void CTrendReport::AddDataItem(string strName, string strTime, string strData)
{
	//生成界面
	int numRow = pDataListTable->numRows();



	pDataListTable->elementAt(numRow, 0)->resize(WLength(250), WLength(100,WLength::Percentage));
	pDataListTable->elementAt(numRow, 1)->resize(WLength(150), WLength(100,WLength::Percentage));
	//pDataListTable->elementAt(numRow, 2)->resize(WLength(70,WLength::Percentage), WLength(100,WLength::Percentage));
	//pSysLogListTable->elementAt(numRow, 5)->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));	
	WText * pTmpText;

	pTmpText = new WText(strName, (WContainerWidget*)pDataListTable->elementAt(numRow , 0));
	pTmpText->setStyleClass("myTextstyle");
	pTmpText = new WText(strTime, (WContainerWidget*)pDataListTable->elementAt(numRow , 1));
	pTmpText->setStyleClass("myTextstyle");
	pTmpText = new WText(strData, (WContainerWidget*)pDataListTable->elementAt(numRow , 2));
	pTmpText->setStyleClass("myTextstyle");
}

//新版本
void CTrendReport::AddDataItemNew(string strName, string strTime, string strData, int numRow)
{
	//生成界面
	m_pDataTable->InitRow(numRow);

	WText * pTmpText;
	
	pTmpText = new WText(strName, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 0));

	m_pDataTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
	pTmpText = new WText(strTime, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 2));
	
	pTmpText = new WText(strData, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 4));

}

//void CTrendReport::AddNormalDataColum(WTable* pContain)
void CTrendReport::AddNormalDataColum(WSVFlexTable * pContain)
{
	//new WText(strHTimeLabel, pContain->elementAt(0, 0));
	pContain->AppendColumn(strHTimeLabel,WLength(20,WLength::Percentage));
	pContain->SetDataRowStyle("table_data_grid_item_text");

	list<string>::iterator fielditem;
	
	int j = 1;
	int size = liststr.size();
	for(fielditem = liststr.begin(); fielditem != liststr.end(); fielditem++)
	{
		pContain->AppendColumn(*fielditem, WLength(80/size, WLength::Percentage));
		pContain->SetDataRowStyle("table_data_grid_item_text");
		//new WText(*fielditem, pContain->elementAt(0, j));
		j++;
	}

/*	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0, i)->setStyleClass("t3title");
	}
*/
}

//
void CTrendReport::AddNormalDataItem(string strName, string strTime, string strData, int numRow)
//void CTrendReport::AddNormalDataItem(string strTime, string strData)
{
	m_pDataTable->InitRow(numRow);

//	WText * pTmpText;
	
//	pTmpText = new WText(strName, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 0));

//	m_pDataTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
//	pTmpText = new WText(strTime, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 2));
	
//	pTmpText = new WText(strData, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 4));

//	int numRow = pDataListTable->numRows();
	
	WText * pTmpText;
	pTmpText = new WText(strTime, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 0));
	m_pDataTable->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);
	pTmpText->setStyleClass("myTextstyle");
	
	std::list<string> datalist;
	list<string>::iterator fielditem;
	ParserToken(datalist, strData.c_str(), ";");
	
	int j = 1;
	for(fielditem = datalist.begin(); fielditem != datalist.end(); fielditem++)
	{
		j++;
		pTmpText = new WText(*fielditem, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , j));
		m_pDataTable->GeDataTable()->elementAt(numRow , j)->setContentAlignment(AlignCenter);
		//pTmpText->setStyleClass("myTextstyle");
		j++;
	}
}
//
void CTrendReport::RefreshList()
{
	//清空数据

/*	for (int i=0; i< m_pDataTable->GeDataTable()->numRows(); i++)
	{
			m_pDataTable->GeDataTable()->deleteRow(1);
	}
*/	
	m_pDataTable->GeDataTable()->clear();	
	m_pDataTable->dataTitleTable->clear();

	if(nCurDataType == 1)
		AddNormalDataColum(m_pDataTable);
	else
		AddDataColum(m_pDataTable);

	OutputDebugString("清空数据了");

	//pDataListTable->clear();
	//AddDataColum(pDataListTable);

	char tmpchar[10] = {0};
	string strTipInfo = strPage;	
	sprintf(tmpchar, "%d", nCurPage);
	strTipInfo += tmpchar;
	strTipInfo += strPageCount;
	sprintf(tmpchar, "%d", nTotalPage);
	strTipInfo += tmpchar;
	strTipInfo += strRecordCount;


	
	//char tmpchar[10] = {0};
	//string strTipInfo = strPage;
	//sprintf(tmpchar, "%d", nCurPage);
	//pCurrPage->setText(tmpchar);
	//strTipInfo += tmpchar;
	//strTipInfo += strPageCount;
	//sprintf(tmpchar, "%d", nTotalPage);
	//pPageCount->setText(tmpchar);
	//strTipInfo += tmpchar;
	//strTipInfo += strRecordCount;

	switch(nCurDataType)
	{
		case 1:
			
			m_pDataTable->pTitleTxt->setText(strGoodData);
			sprintf(tmpchar, "%d", retnormaltimelist.size());				
			break;
		case 2:
			
			m_pDataTable->pTitleTxt->setText(strErrorData);
			sprintf(tmpchar, "%d", reterrortimelist.size());			
			break;
		case 3:
			
			m_pDataTable->pTitleTxt->setText(strWarningData);
			sprintf(tmpchar, "%d", retdangertimelist.size());			
			break;
		default:
			break;
	}
	//pRecCount->setText(tmpchar);	
	//strTipInfo += tmpchar;
	//sprintf(tmpchar, "%d", RecordsList.size());
	strTipInfo += tmpchar;
	m_pDataTable->pSelReverse->setText(strTipInfo);

	//pTextTipInfo->setText(strTipInfo);

	switch(nCurDataType)
	{
		case 1:
			
			if(retnormaltimelist.size() <= 0)
			{
				m_pDataTable->ShowNullTip();
				return;
			}
			else
			{
				m_pDataTable->HideNullTip();
			}

			break;
		case 2:
			
			if(reterrortimelist.size() <= 0)
			{
				m_pDataTable->ShowNullTip();
				return;
			}
			else
			{
				m_pDataTable->HideNullTip();
			}

			break;
		case 3:
			
			if(retdangertimelist.size() <= 0)
			{
				m_pDataTable->ShowNullTip();
				return;
			}
			else
			{
				m_pDataTable->HideNullTip();
			}

			break;
		default:
			break;
	}
	
	int index = 0;
	int nPage = 0;
	int iRow = 1;

	switch(nCurDataType)
	{
		case 1:
			for(retmonnamelistitem = retnormalnamelist.begin(), rettimelistitem = retnormaltimelist.begin(), retstrlistitem = retnormalstatuslist.begin();\
				retmonnamelistitem != retnormalnamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
			{
				char ibuf[256] = {0};
				sprintf(ibuf, "nPage: %d nCurPage: %d\n", nPage, nCurPage);
				OutputDebugString(ibuf);

				nPage = index / nPageCount;
				nPage += 1;
				if(!bDivide && nCurPage == nTotalPage)
				{
					if(nPage == nTotalPage)
					{
						//AddDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem);
					//	AddDataItemNew(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);
					//	OutputDebugString("\nin nPage == nTotalPage : call one\n");
					//	iRow++;
							
							AddNormalDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);
							iRow++;
					}
				}
				else if(nPage == nCurPage)
				{
					//AddDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem);
				//	AddDataItemNew(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);
				//	OutputDebugString("\nin nPage == nCurPage : call one\n");
				//	iRow++;
						
						AddNormalDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);
						iRow++;
				}
				else
				{
				}

				index ++;
			}

			break;
		case 2:
			for(retmonnamelistitem = reterrornamelist.begin(), rettimelistitem = reterrortimelist.begin(), retstrlistitem = reterrorstatuslist.begin();\
				retmonnamelistitem != reterrornamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
			{
				nPage = index / nPageCount;
				nPage += 1;
				if(!bDivide && nCurPage == nTotalPage)
				{
					if(nPage == nTotalPage)
					{
						//AddDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem);
						AddDataItemNew(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);

						iRow++;
					}
				}
				else if(nPage == nCurPage)
				{
					//AddDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem);
					AddDataItemNew(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);				
					iRow++;
				}
				else
				{
				
				}

				index ++;
			}

			break;
		case 3:
			for(retmonnamelistitem = retdangernamelist.begin(), rettimelistitem = retdangertimelist.begin(), retstrlistitem = retdangerstatuslist.begin();\
			retmonnamelistitem != retdangernamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
			{
				nPage = index / nPageCount;
				nPage += 1;
				if(!bDivide && nCurPage == nTotalPage)
				{
					if(nPage == nTotalPage)
					{
						//AddDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem);
						AddDataItemNew(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);				
						iRow++;
					}
				}
				else if(nPage == nCurPage)
				{
					//AddDataItem(*retmonnamelistitem, *rettimelistitem, *retstrlistitem);
					AddDataItemNew(*retmonnamelistitem, *rettimelistitem, *retstrlistitem, iRow);				
					iRow++;
				}
				else
				{
				
				}
				index ++;				
			}
			break;
		default:	
			break;
	}
}