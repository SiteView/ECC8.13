/*************************************************
*  @file ContrastReport.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include ".\contrastreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"
#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
#include "cspreadsheet.h"


//new ui 
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"
#include "../svtable/WSTreeAndPanTable.h"
//分解字符串
/**************************************************************
参数：
	pTokenist:
	pQueryString:
	pSVSeps:

功能：
	用指定字符替换特殊字符

返回值：
	如果成功返回TRUE， 否则返回FALSE
***************************************************************/
bool CContrastReport::ParserToken( list<string >&pTokenList,
								   const char * pQueryString,
								   char *pSVSeps)
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

/*****************************************************
参数：
	str:需要替换的字符串
	old_value:被替换字符
	new_value:替换字符

功能：
	用new_value替换所有的old_value

返回值：
	返回替换后的字符串
******************************************************/
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

//
/************************************************
参数：
	strId:监测器ID
	strPropName:ID属性

功能：
	取得监测器属性值

返回值：
	返回监测器属性值
	
************************************************/
string  GetMonitorPropValue(string strId, 
							string strPropName)
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
/*********************************************
参数：
	strId:

功能：
    取得设备名称

返回值：
	返回设备名称
*********************************************/
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


/*****************************************************************
参数：
	starttime:报告开始时间
	endtime:报告截止时间
	templatename:监测器模板值
	monitorlist:监测器LIST
	index:监测器个数
	bClicket:是否列出阀值
	bListError:是否列出错误
	bListDanger:是否列出危险
	bListStatsResult:是否列出统计结果
	bListImage:是否列出图象
	parent:容器

功能：
	构造函数

返回值:
	
*****************************************************************/
CContrastReport::CContrastReport(chen::TTime starttime, 
								 chen::TTime endtime,
								 std::string *templatename,
								 std::list<string> *monitorlist,
								 int index, 
								 bool bClicket ,
								 bool bListError, 
								 bool bListDanger, 
								 bool bListStatsResult, 
								 bool bListImage, 
								 WContainerWidget *parent ):
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
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Total_Report",strMainTitle);
			FindNodeValue(ResNode,"IDS_Total_Report_List",strTitle);
			FindNodeValue(ResNode,"IDS_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Total_Report_Map",strNameUse);
			FindNodeValue(ResNode,"IDS_Edit_Name",strNameEdit);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Run_Case_Table",m_formText.szRunTitle);
			FindNodeValue(ResNode,"IDS_Time_Period",szInterTime);
			FindNodeValue(ResNode,"IDS_Alert_Date_Total_Table",m_formText.szMonitorTitle);
			FindNodeValue(ResNode,"IDS_Error_Precent",m_formText.szErrorTitle);
			FindNodeValue(ResNode,"IDS_Danger_Prencet",m_formText.szDangerTitle);
			FindNodeValue(ResNode,"IDS_Normal_Precent",m_formText.szNormalTitle);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szRunName);
			FindNodeValue(ResNode,"IDS_Run_Time_Normal_Precent",m_formText.szRunTime);
			FindNodeValue(ResNode,"IDS_Danger_Prencet",m_formText.szRunDanger);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szRunError);
			FindNodeValue(ResNode,"IDS_Later",m_formText.szRunNew);
			FindNodeValue(ResNode,"IDS_Clique_Value",m_formText.szRunClicket);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szMonName);
			FindNodeValue(ResNode,"IDS_Measure",m_formText.szMonMeasure);
			FindNodeValue(ResNode,"IDS_Max",m_formText.szMonMax);
			FindNodeValue(ResNode,"IDS_Average",m_formText.szMonPer);
			FindNodeValue(ResNode,"IDS_Later_Time",m_formText.szMonLast);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szErrName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szErrStartTime);
			FindNodeValue(ResNode,"IDS_State",m_formText.szErrStatus);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szDangerName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szDangerStartTime);
			FindNodeValue(ResNode,"IDS_State",m_formText.szDangerStatus);
			FindNodeValue(ResNode,"IDS_Time",strHTimeLabel);
			FindNodeValue(ResNode,"IDS_Name",strHNameLabel);
			FindNodeValue(ResNode,"IDS_Data",strHDataLabel);
			FindNodeValue(ResNode,"IDS_NormalData",strNormalBtn);
			FindNodeValue(ResNode,"IDS_ErrorData",strErrorBtn);
			FindNodeValue(ResNode,"IDS_WarningData",strWarnningBtn);
			FindNodeValue(ResNode,"IDS_Back",strBack);
			FindNodeValue(ResNode,"IDS_Forward",strForward);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Date_Record",strDataTableName);
			FindNodeValue(ResNode,"IDS_No_Sort_Record",strNoSortRecord); 
			FindNodeValue(ResNode,"IDS_Name",m_formText.szXLSName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szXLSTime);
			FindNodeValue(ResNode,"IDS_State",m_formText.szXLSStatus);
			FindNodeValue(ResNode,"IDS_Data1",m_formText.szXLSData); 
			FindNodeValue(ResNode,"IDS_Normal",m_formText.szXLSNormal);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szXLSError);
			FindNodeValue(ResNode,"IDS_Danger",m_formText.szXLSDanger); 
			FindNodeValue(ResNode,"IDS_Generate_Excel_Table",m_formText.szExcelBut); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Ini",m_formText.szPageIni); 
			FindNodeValue(ResNode,"IDS_Map_Table",m_formText.szChart); 			
			FindNodeValue(ResNode,"IDS_Normal",m_formText.szGood); 			
			FindNodeValue(ResNode,"IDS_Warning",m_formText.szWarning);			
			FindNodeValue(ResNode,"IDS_Error",m_formText.szError); 			
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable); 
			FindNodeValue(ResNode,"IDS_Max_Value",m_formText.szMaxValue);			
			FindNodeValue(ResNode,"IDS_Average_Value",m_formText.szAverageValue);			
			FindNodeValue(ResNode,"IDS_Min_Value",m_formText.szMinValue); 			
			FindNodeValue(ResNode,"IDS_Name",m_formText.szName); 
			FindNodeValue(ResNode,"IDS_State",m_formText.szState); 
			FindNodeValue(ResNode,"IDS_Time",m_formText.szTime); 
			FindNodeValue(ResNode,"IDS_Data",m_formText.szData); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",m_formText.szPage); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",m_formText.szPageCount); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",m_formText.szRecordCount); 
			FindNodeValue(ResNode,"IDS_PageRecordCount",m_formText.szPageRecordCount); 
			FindNodeValue(ResNode,"IDS_ContrastTitle",m_formText.szContrastTitle); 
		}
		//CloseResource(objRes);
	}

	gfieldnum = 0;
	m_starttime = starttime;
	m_endtime = endtime;

	//12-6 new add by ()
	string szEInterTime = "(";
	szEInterTime += szInterTime;
	szEInterTime += starttime.Format();
	szEInterTime += "~";
	szEInterTime += endtime.Format();
	szEInterTime += ")";

	szInterTime = szEInterTime;

	string strName = "";

	szXSLReportName = strName;
	szXSLReportName += "_";
	szXSLReportName += starttime.Format();
	szXSLReportName += "_";
	szXSLReportName += endtime.Format();	
	replace_all_distinct(szXSLReportName, ":", "");
	replace_all_distinct(szXSLReportName, " ", "");
	replace_all_distinct(szXSLReportName, ".", "");
	replace_all_distinct(szXSLReportName, "-", "");
	szXSLReportName += ".xls";
	gPageNum = 1;
	gPageCount = 0;
	nCurDataType = 0;
	normalrecnum = 1;
	dangerrecnum = 1;
	errorrecnum = 1;
	nCurPage = 0;
	nTotalPage = 0;
	nPageCount = 30;

	ShowMainTable(starttime, endtime, templatename,monitorlist,index, bClicket, bListError,\
		bListDanger, bListStatsResult, bListImage);
}

/********************************************
参数：

功能：
	析构函数

返回值：

********************************************/
CContrastReport::~CContrastReport(void)
{
	if( objRes !=INVALID_VALUE )
			CloseResource(objRes);
}

/********************************************************************
参数：
	strLabel:标签IDS

功能：
	从资源文件取得LABEL

返回值：
	资源文件中的LABEL
********************************************************************/
std::string CContrastReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
			strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

/*******************************************************************
参数：
	starttime: 报告开始时间
	endtime: 报告截止时间
	templatename: 监测器模板值
	monitorlist: 监测器列表
	index: 监测器个数
	bClicket: 是否列出阀值
	bListError: 是否列出错误
	bListDanger: 是否列出危险
	bListStatsResult: 是否列出结果
	bListImage: 是否列出图象

功能：
	显示对比报告查询界面

返回值:

*******************************************************************/
void CContrastReport::ShowMainTable(chen::TTime starttime, 
									chen::TTime endtime,
									std::string *templatename,
									std::list<string> *monitorlist,
									int index,
									bool bClicket,
									bool bListError, 
									bool bListDanger,
									bool bListStatsResult, 
									bool bListImage)
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
	szIconPath += "\\htdocs\\report\\icons";
	fr=::FindFirstFile(szIconPath.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szIconPath.c_str(), NULL);
	}

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this->elementAt(0,0));

	char buf_tmp[4096]={0};
    int nSize =4095;

	//get query_string value
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
	
	string strReportTitle = "对比报告";
	InitPageItem(pContainTable, strReportTitle);//初始化页面元素
		
	std::list<string>::iterator item;
	int i6 = 1;
	int i1, i2;
	char buf[256];
	char buf1[256];
	
	//pImageTable = new WTable(pContainTable->elementAt(7 , 0));
	 // pImageTable= new WTable(m_pContainTable->GetContentTable()->elementAt(7,0));
	//  pImageTable = new WSVFlexTable(m_pContainTable->GetContentTable()->elementAt(7,0),List,"");
	if(!bListImage)
	{
		pImageTable->hide();
	}

	pContainTable->elementAt(7, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	int i3 = 2;
	int fieldnum = 1;
	int gnormalnum = 1;
	int gdangernum = 1;
	int gerrornum = 1;
	int tcount = 0;

	GetMonitorRecord(templatename,monitorlist, index, starttime, endtime, bClicket,\
		bListStatsResult, "ContrastReport", tcount, i6, i3, fieldnum);
}


void CContrastReport::refresh()
{
	
}

/********************************************************************
参数：
	data: 数据
	len: 长度
	linelayer: 线状图图层指针
	lpMultiByteStr: 存储UDF-8的LPSTR
	xlabels: 横坐标的LABEL
	xscalelen: 横坐标的刻度
	xStep: 横坐标间距
	ylabels: 纵坐标LABEL
	yscalelen: 纵坐标刻度长度
	yScale: 纵坐标刻度
	yStep: 纵坐标间距
	xLinearScale: 
	starttime: 开始时间
	endtime: 截止时间
	Title: 标题
	xTitle: 横坐标标题
	ctitle: 监测器个数

功能：
	设置对比报告图象的大小， 标题， 横、纵坐标， 样式等，返回
	XYChart及LineLayer对象指针
返回值：
	XYChart对象指针
********************************************************************/
XYChart * CContrastReport::StartGenLineImage(double data[], 
											 int len,
											 LineLayer **linelayer,
											 LPSTR lpMultiByteStr,
											 char *xlabels[],
											 int xscalelen, 
											 int xStep, 
											 char *ylabels[],
											 int yscalelen,
											 int yScale,
											 int yStep,
											 int xLinearScale, 
											 double starttime, 
											 double endtime, 
											 char* Title, 
											 char* xTitle,
											 int ctitle)
{
	wchar_t lpWide[256];
		
	XYChart *c = new XYChart(300*2, 300 + ctitle*20, 0xffffff, 0x0, 1);
	
	if(ctitle > 90)
	{
		(c)->setPlotArea(55, -130 + ctitle*20, 260*2, 170, 0xffffff, -1, 0xa08040, (c)->dashLineColor(0x000000,		
			0x000103), (c)->dashLineColor(0x000000, 0x000103));
	}
	else if(ctitle > 40)
	{
		(c)->setPlotArea(55, -20 + ctitle*20, 260*2, 170, 0xffffff, -1, 0xa08040, (c)->dashLineColor(0x000000,		
			0x000103), (c)->dashLineColor(0x000000, 0x000103));
	}
	else if(ctitle > 20)
	{
		(c)->setPlotArea(55, 23 + ctitle*20, 260*2, 170, 0xffffff, -1, 0xa08040, (c)->dashLineColor(0x000000,		
			0x000103), (c)->dashLineColor(0x000000, 0x000103));
	}
	else
	{
		(c)->setPlotArea(55, 63 + ctitle*20, 260*2, 170, 0xffffff, -1, 0xa08040, (c)->dashLineColor(0x000000,		
			0x000103), (c)->dashLineColor(0x000000, 0x000103));
	}

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;
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
	mbstowcs(lpWide, Title, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
//	(c)->addTitle(lpMultiByteStr,
//		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);
		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

    (c)->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	lpWideCharStr = L"Copyright SiteView";

	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);
	(c)->xAxis()->setTitle(lpMultiByteStr, "mingliu.ttc", 8, 0x000000ff);

	c->addLegend(55, 36, true, "mingliu.ttc");
	//c->addTrendLayer(DoubleArray(time, len),DoubleArray(data, len), 0x6666ff)->setLineWidth(2);
	//*linelayer = (*c)->addLineLayer(DoubleArray(data, len), 0x007000);
	*linelayer = (c)->addLineLayer();
	(*linelayer)->setXData(DoubleArray(data, len));
//	(*c)->setPlotArea(60, 75, 190, 320)->setGridColor(0xc0c0c0, 0xc0c0c0);
//	(*linelayer)->setLineWidth(2);
	return c;
}

/************************************************************
参数：
	c: XYChart指针
	lpMultiByteStr: UDF-8字符指针
	filename: 图像名称

功能：
	生成对比报告图象

返回值：

************************************************************/
void CContrastReport::EndGenLineImage(XYChart *c,
									  LPSTR lpMultiByteStr,
									  char * filename)
{
	
	c->makeChart(filename);
	
	(c)->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	 if(!lpMultiByteStr)
	 {
		free(lpMultiByteStr);
	 }
  
	 try{
		if(c)
		{		
			delete c;
			c = 0;
		}
	 }
	 catch(...)
	 {
	 }	
}

/*******************************************************
参数：
	data: 数据数组
	time: 时间数组
	len: 数组长度
	linelayer: 图层指针
	color: 线颜色
	name: 线名称

功能：
	增加数据线到图表中

返回值：

*******************************************************/
void CContrastReport::GenLineImage(double data[],
								   double time[],
								   const int len,
								   LineLayer *linelayer,
								   int color, 
								   char*name)
{    				
		wchar_t lpWide[256];

		int sr = rand() + 0x00ff00;
		int ncol = sr%0xffffff;

		LPSTR lpMultiByteStr;
		LPCWSTR lpWideCharStr =L"";
		int slen = 256;
		int wlen = 256;
		lpMultiByteStr= (LPSTR)malloc(256);
		BOOL buse ;
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
		mbstowcs(lpWide, name, 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);		
		linelayer->addDataSet(DoubleArray(data, len), -1, lpMultiByteStr);
		if(lpMultiByteStr)
		{
			free(lpMultiByteStr);
		}
	
}

/*******************************************************
参数：
	szTitle:标题
	labels:数据标签
	data:数据
	len:数组长度
	filename:报告名称

功能：
	生成饼状图

返回值：

*******************************************************/
void CContrastReport::GenPieImage(char * szTitle,
								  char * labels[],
								  double data[], 
								  int len,
								  char * filename)
{
    PieChart *c = new PieChart(360, 300);

    c->setPieSize(180, 140, 100);

    c->addTitle(szTitle);

    c->set3D();

	c->addLegend(330, 40);
	
    c->setData(DoubleArray(data, len), StringArray(
        labels, len));

    c->setExplode(0);

    c->makeChart(filename);

    delete c;
}

/********************************************************************************
参数：
	hRecSet: 数据集句柄
	monitorname: 监测器名称
	retmonnamelist: 监测器名称LIST
	retstatlist: 状态LIST
	retstrlist: 数据串LIST
	rettimelist: 时间LIST

功能：
	取监测器字符串数据PUSH_BACK到LIST中

返回值：

********************************************************************************/
void CContrastReport::GetMonitorDataRecStr(RECORDSET hRecSet,
										   std::string monitorname,
										   std::list<string> &retmonnamelist, 
										   std::list<int> &retstatlist,
										   std::list<string>& retstrlist, 
										   std::list<string>& rettimelist)
{
	LISTITEM item;
	RECORD hRec;
	list<string>::iterator fielditem;

	FindRecordFirst(hRecSet, item);
			
	int stat;
	std::string str;
	std::string	strNormal; 

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		GetRecordDisplayString(hRec, stat, str);			
		TTime tm;
		GetRecordCreateTime(hRec,tm);
		//if(stat == 1 || stat == 4) //禁止先不显示了 cxy 06/11/23
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
void CContrastReport::GetMonitorDataRec(RECORDSET hRecSet, 
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
									 int & reccount,
									 std::string & maxtime)
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
						maxtime = tm.Format();
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
						maxtime = tm.Format();
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

/*********************************************************************
参数：
	reportname: 报告名称
	grouplist: 组LIST

功能：
    取得组下所有的监测器

返回值：

*********************************************************************/
void CContrastReport::GetMonitorGroup(char * reportname, 
									  std::list<string> & grouplist)
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

/***********************************************************
参数：
	table: 容器表
	title: 标题

功能：
	初始化页面元素

返回值：

***********************************************************/
void CContrastReport::InitPageItem(WTable *table, std::string title)
{
	//################################################################################################//建立新搜索界面-------------juxian.zhang
	m_pFrameTable = new WSVMainTable(this->elementAt(1,0),"",false);
	
	m_column =new WSVFlexTable(m_pFrameTable->GetContentTable()->elementAt(2,0),List,"运行情况报表&nbsp&nbsp&nbsp"+szInterTime);
	if(m_column->GetContentTable()!=NULL)
	{

		m_column->AppendColumn("",WLength(2,WLength::Percentage));
		m_column->SetDataRowStyle("table_data_grid_item_img");
		m_column->AppendColumn("类型",WLength(40,WLength::Percentage));
		m_column->SetDataRowStyle("table_data_grid_item_img");
		m_column->AppendColumn(m_formText.szMaxValue,WLength(20,WLength::Percentage));
		m_column->SetDataRowStyle("table_data_grid_item_img");
		m_column->AppendColumn(m_formText.szAverageValue,WLength(20,WLength::Percentage));
		m_column->SetDataRowStyle("table_data_grid_item_text");
		m_column->AppendColumn(m_formText.szMinValue,WLength(20,WLength::Percentage));
		m_column->SetDataRowStyle("table_data_grid_item_text");
	
	}
		
		//m_pContainTable= new WSVFlexTable(m_pFrameTable->elementAt(3,0),Blank,"图表");
	 //   pImageTable = new WSVFlexTable(m_pFrameTable->GetContentTable()->elementAt(3,0),List,"");
		//if (pImageTable->GetContentTable()!=NULL );
		//{
		//	pImageTable->AppendColumn("",WLength(20,WLength::Percentage));
		//	pImageTable->SetDataRowStyle("table_data_grid_item_img");
		//	pImageTable->AppendColumn("",WLength(60,WLength::Percentage));
		//	pImageTable->SetDataRowStyle("table_data_grid_item_img");
		//	pImageTable->AppendColumn("",WLength(20,WLength::Percentage));
		//	pImageTable->SetDataRowStyle("table_data_grid_item_img");
		//}
	//############################################################################################################################*/
	pFrameTable = new WTable(this->elementAt(0,0));	
	pFrameTable ->setStyleClass("t5");
	pFrameTable->hide();// 隐藏原界面，不影响原逻辑结构-------------juxian.zhang
	WTable * column = new WTable((WContainerWidget*)pFrameTable->elementAt(1, 0));
	pFrameTable->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);
	column->setStyleClass("StatsTable");
	column->elementAt(0, 0)->setStyleClass("t1title");
	column->elementAt(0, 0)->setContentAlignment(AlignTop | AlignRight);
	
	pContainTable = new WTable((WContainerWidget*)pFrameTable->elementAt(2,0));
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

	pRunTable ->adjustRowStyle("tr1", "tr2");

	new WText("类型", pRunTable->elementAt(0, 0));
	new WText(m_formText.szMaxValue, pRunTable->elementAt(0,1 ));
	new WText(m_formText.szAverageValue, pRunTable->elementAt(0, 2));
	new WText(m_formText.szMinValue, pRunTable->elementAt(0, 3));
	pRunTable->GetRow(0) ->setStyleClass("t1title");

	pRunTable->setStyleClass("StatsTable");	
	pRunTable->tableprop_ = 2;
	pRunTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(3, 0)->setContentAlignment(AlignTop | AlignCenter);
	text1 ->decorationStyle().setFont(font1);
	pContainTable ->elementAt(4, 0) ->setContentAlignment(AlignTop | AlignCenter);
	pMonitorTable = new WTable(pContainTable->elementAt(5, 0));
	pMonitorTable->setStyleClass("StatsTable");	
	pMonitorTable->tableprop_ = 2;
	pMonitorTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(5, 0)->setContentAlignment(AlignTop | AlignCenter);

//	text1 = new WText(m_formText.szChart, pContainTable->elementAt(6, 0));//-------------juxian.zhang
//	text1 -> decorationStyle().setFont(font1);
	pContainTable -> elementAt(6, 0) -> setContentAlignment(AlignTop | AlignCenter);

}

/**************************************************************
参数：
	reportname: 报告名称
	starttime: 开始时间
	endtime: 截止时间
	value: 值
	fieldlabel: 字段名称
	minval: 最小值
	perval: 平均值
	maxval: 最大值

功能:
	写reportgenerate.ini文件

返回值：
**************************************************************/
void CContrastReport::WriteGenIni(std::string reportname, 
								  std::string starttime,
								  std::string endtime,
								  std::string value,
								  std::string fieldlabel,
								  float minval,
								  float perval,
								  float maxval)
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

/***********************************************************************
参数：
	templatename: 监测器模板值
	monitorlist: 监测器列表
	index: 监测器个数
	starttime: 报告开始时间
	endtime: 报告截止时间
	bClicket: 是否显示阀值
	bListStatsResult: 是否列出统计结果
	reportname: 报告名称
	tcount: 
	i6:
	i3:
	fieldnum:

功能：
	取同一类型监测器指定时间段的数据
***********************************************************************/
void CContrastReport::GetMonitorRecord(std::string *templatename,
									   std::list<string>*monitorlist, 
									   int index,
									   chen::TTime starttime,
									   chen::TTime endtime, 
									   bool bClicket,
									   bool bListStatsResult, 
									   std::string reportname, 
									   int &tcount,
									   int & i6,
									   int & i3, 
									   int & fieldnum)
{
	double data[50000];	
	double time[50000];
	char buf[256];
	char buf2[256];
	
	for(int j = 0; j < index; j++)
	{		
		std::list<string>::iterator monitorlistitem;			
		XYChart *c = NULL;
		LineLayer *linelayer = NULL;
		LPSTR lpMultiByteStr;
		std::string hrefstring;
		std::string namebuf3;
		std::string namebuf1;
		std::string namebuf;
	
		OBJECT hTemplet;									
		hTemplet = GetMonitorTemplet(atoi(templatename[j].c_str()));

		std::list<int> retstatlist1;
		std::list<string> retstrlist1;
		std::list<string> rettimelist1;
		std::list<string> retmonnamelist1;				
		LISTITEM item;
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
			std::string maxtime = "";
			std::string returnimage ;
			std::string returnstats ;
			std::string returndata ;
			std::list<int> intlist;
			std::list<float> floatlist;
			std::list<string> stringlist;
			std::list<TTime> timelist;
			std::list<int>::iterator intitem;
			std::list<float>::iterator floatitem;
			std::list<string>::iterator stringitem;
			std::list<TTime>::iterator timeitem;
			std::list<int> badlist;
			
			MAPNODE objNode;
			int count = 0;
			gfieldnum = 0;
			int reccount = 0;
		
			while( (objNode = FindNext(item)) != INVALID_VALUE )
			{		
				int idnum = 0;
				int color = 0x007000;
									
				FindNodeValue(objNode, "sv_label", fieldlabel);
				fieldlabel=GetLabelResource(fieldlabel);
				FindNodeValue(objNode, "sv_type", fieldtype);				
				FindNodeValue(objNode, "sv_name", fieldname);

				
				//取监测器报告显示项
				FindNodeValue(objNode, "sv_drawimage", returnimage);
				FindNodeValue(objNode, "sv_drawtable", returnstats);
				FindNodeValue(objNode, "sv_drawmeasure", returndata);

				float gmaxval = 0;
				float gminval = 0;
				float gperval = 0;
				float gcountval = 0;
				bool gret = true;
					//pImageTable->InitRow(i3);
				//WTable * pInsertTable = new WTable(pImageTable->GeDataTable()->elementAt(i3, 2));

				pInsertTable = new WSVFlexTable(m_pFrameTable->GetContentTable()->elementAt(i3,0),List,"","");
				if (pInsertTable!= NULL)
				{
					pInsertTable->AppendColumn(strHNameLabel,WLength(39,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
					pInsertTable->AppendColumn(m_formText.szMaxValue,WLength(17,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
					pInsertTable->AppendColumn(m_formText.szAverageValue,WLength(17,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
					pInsertTable->AppendColumn("最大值时标",WLength(35,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
				}
				//new WText(strHNameLabel, pInsertTable->elementAt(0, 0));
				//new WText(m_formText.szMaxValue, pInsertTable->elementAt(0, 1));
				//new WText(m_formText.szAverageValue, pInsertTable->elementAt(0, 2));
				//new WText("最大值时标", pInsertTable->elementAt(0, 3));

				//pInsertTable->GetRow(0) ->setStyleClass("t1title");
				//pInsertTable->setStyleClass("StatsTable1");	
				//pInsertTable->tableprop_ = 2;
				//pInsertTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
				////pInsertTable->elementAt(3, 0)->setContentAlignment(AlignTop | AlignCenter);

				gfieldnum = 0;
				int stypemon = 1;
				for(monitorlistitem = monitorlist[j].begin(); monitorlistitem != monitorlist[j].end(); monitorlistitem++)
				{							
					count = 0;
					string monitorid = *monitorlistitem;
					OBJECT hMon = GetMonitor(monitorid);

					RECORDSET hRecSet = QueryRecords(monitorid, m_starttime, m_endtime);//取监测器数据集句柄
					
					maxval = 0;
					perval = 0;
					lastval = 0;
					intlist.clear();
					floatlist.clear();
					stringlist.clear();
					timelist.clear();
					badlist.clear();
					
					//按字段取监测器记录队列
					reccount = 0;
					try
					{
					GetMonitorDataRec(hRecSet, fieldname, fieldtype, intlist , floatlist, stringlist,badlist, \
						timelist, maxval, minval, perval, lastval, reccount, maxtime); 												
					}
					catch(...)
					{
						continue;
					}					

					if(maxval > gmaxval)
					{
						gmaxval = maxval;
					}
					if(gret)
					{
						gminval = minval;
						gret = false;
					}
					else
					{
						if(minval < gminval)
						{
							gminval = minval;
						}
					}
					
					gcountval += perval;					
					retfieldname[gfieldnum] = fieldlabel.c_str();										
					gfieldnum++;
							
					//如果不是主键值则不生成监测数据统计及图表
					std::string szPrimary;
					FindNodeValue(objNode, "sv_primary",szPrimary);
																	
					//数组赋值
					for(floatitem = floatlist.begin(), intitem = intlist.begin(), stringitem = stringlist.begin(),timeitem = timelist.begin(); \
						(timeitem != timelist.end()); floatitem++, intitem++, stringitem++, timeitem++)
					{
						TTime ctm = *timeitem;
						time[reccount - 1 - count] = Chart::chartTime(ctm.GetYear(), ctm.GetMonth(),\
							ctm.GetDay(), ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());

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
					//图形显示，直接调用方法-------------juxian.zhang
				//	if(strcmp(returnimage.c_str(), "1") == 0)
					{						
						string	szRootPath = GetSiteViewRootPath();
						string szIconPath = szRootPath;
						szIconPath += "\\htdocs\\report\\icons\\";

						namebuf = szIconPath;					
		
						std::string timestr = m_starttime.Format();
						timestr = replace_all_distinct(timestr, " ", "_");
						namebuf1 = timestr;
						timestr = m_endtime.Format();
						timestr = replace_all_distinct(timestr, " ", "_");
						namebuf1 += timestr;
						
						namebuf3 = namebuf1;
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
						namebuf1 = replace_all_distinct(namebuf1, ":", "_");
						namebuf1 = replace_all_distinct(namebuf1, "<", "_");
						namebuf1 = replace_all_distinct(namebuf1, ">", "_");
						namebuf1 = replace_all_distinct(namebuf1, "\\", "_");
						namebuf1 = replace_all_distinct(namebuf1, "/", "_");
						namebuf += namebuf1;
						
						CTime tm = CTime::GetCurrentTime();						
						//加上设备Entity

						//返回
						std::string unitstr;
						FindNodeValue(objNode, "sv_unit", unitstr);
						
						//color += 0x001f00;
						hMon = GetMonitor(monitorid);
						OBJECT hMon = GetMonitor(monitorid);
						MAPNODE ma=GetMonitorMainAttribNode(hMon);
						std::string smonitorname = "";
						FindNodeValue( ma, "sv_name", smonitorname);

						//设备ID
						string strEntity =	FindParentID(monitorid);

						//设备句柄
						OBJECT hEntity = GetEntity(strEntity);

						//设备主属性
						MAPNODE entitynode = GetEntityMainAttribNode(hEntity);

						//设备名称
						std::string entityvalue;
						FindNodeValue(entitynode, "sv_name", entityvalue);

						string lstr = entityvalue;
						lstr += ":";
						lstr += smonitorname;
						pInsertTable->InitRow(stypemon);
						new WText(lstr, pInsertTable->GeDataTable()->elementAt(stypemon, 0));
						char tbuf[256];
						sprintf(tbuf, "%0.2f", maxval);
						new WText(tbuf, pInsertTable->GeDataTable()->elementAt(stypemon, 2));
						sprintf(tbuf, "%0.2f", perval);
						new WText(tbuf, pInsertTable->GeDataTable()->elementAt(stypemon, 4));
						new WText(maxtime, pInsertTable->GeDataTable()->elementAt(stypemon, 6));
						stypemon++;
						
						if(idnum == 0)
						{					
							int ctitle = monitorlist[j].size();
							OutputDebugString("-----------new chardirectory instance------------\n");
							c = StartGenLineImage(time, count, &linelayer, lpMultiByteStr, NULL, 100, 10, NULL, 0, 100, 20, count, 0, 0,(char*)fieldlabel.c_str(), (char*)fieldlabel.c_str(), ctitle);
							GenLineImage(data, time, count, linelayer, color,(char*) lstr.c_str());
						}
						else
						{		
							OutputDebugString("------------exist chardirectory instance----------\n");
							color = 0xff0000; 													
							GenLineImage(data,  time, count, linelayer, color, (char*)lstr.c_str());								
						}															
					}			
					CloseMonitor(hMon);
					CloseRecordSet(hRecSet);
					idnum++;
										
					//判断数据是否显示
				}				
			
				//监测数据统计表跳转指向名称：监测器名（返回值）													
				std::string namebuf2 = "../report/icons/";
				namebuf2 += namebuf3;
				namebuf2 += "/";
				namebuf2 += namebuf1;

				OutputDebugString(namebuf2.c_str());
				OutputDebugString("\n");
				m_column->InitRow(i3);//List-------------juxian.zhang
				//new WText(namebuf, m_column->GeDataTable()->elementAt(i6,0));
				if(c)
				{
					char buf2[256];
					string imgtabletitle = fieldlabel;					
								
					imgtabletitle += "\n";
					imgtabletitle += m_formText.szMaxValue;//"最大值:";
					imgtabletitle += ":";
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", gmaxval);
					
				//	new WText(fieldlabel, pRunTable->elementAt(i3+1, 0));
					m_column->GeDataTable()->elementAt(i3, 2)->setContentAlignment(AlignCenter);//List-------------juxian.zhang
					new WText(fieldlabel, m_column->GeDataTable()->elementAt(i3,2));
					
					
				//	new WText(buf2, pRunTable->elementAt(i3+1, 1));
				
					m_column->GeDataTable()->elementAt(i3, 4)->setContentAlignment(AlignCenter);//List-------------juxian.zhang
					new WText(buf2, m_column->GeDataTable()->elementAt(i3, 4));

					imgtabletitle += buf2;
					imgtabletitle += m_formText.szAverageValue;//"平均值:";
					imgtabletitle += ":";
					memset(buf2, 0, 256);
					float perval1 = (gcountval/idnum);
					sprintf(buf2, "%0.2f", perval1);

				//	new WText(buf2, pRunTable->elementAt(i3+1, 2));
					m_column->GeDataTable()->elementAt(i3, 6)->setContentAlignment(AlignCenter);//List-------------juxian.zhang
					new WText(buf2, m_column->GeDataTable()->elementAt(i3,6));



					imgtabletitle += buf2;
					imgtabletitle += m_formText.szMinValue;//"最小值:";
					imgtabletitle += ":";
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.2f", gminval);
					imgtabletitle += buf2;	

				//	new WText(buf2, pRunTable->elementAt(i3+1, 3));
					
					m_column->GeDataTable()->elementAt(i3, 8)->setContentAlignment(AlignCenter);//List-------------juxian.zhang
					new WText(buf2, m_column->GeDataTable()->elementAt(i3,8));

					wchar_t lpWide[256];					
					LPCWSTR lpWideCharStr =L"";
					int slen = 256;
					int wlen = 256;
					lpMultiByteStr= (LPSTR)malloc(256);
					memset(lpMultiByteStr, 0, 256);					
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
					mbstowcs(lpWide, imgtabletitle.c_str(), 256);
					WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
					(c)->addTitle(lpMultiByteStr,
						"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);
					free(lpMultiByteStr);
					EndGenLineImage(c, lpMultiByteStr, (char*)namebuf.c_str());
					pImageTable = new WSVFlexTable(m_pFrameTable->GetContentTable()->elementAt(i3+1,0),Query,"","");
					//new WImage(namebuf2, (WContainerWidget*)pImageTable->GeDataTable()->elementAt(i3, 2));					
					//pImageTable->GeDataTable()->elementAt(i3, 2) ->setContentAlignment(AlignTop | AlignCenter);										
					new WImage(namebuf2, (WContainerWidget*)pImageTable->GetContentTable()->elementAt(0, 1));					
					pImageTable->GetContentTable()->elementAt(0, 1) ->setContentAlignment(AlignTop | AlignCenter);	
					i3++;
				
				}
			}				
		}		
		CloseMonitorTemplet(hTemplet);
	}		
}

/*对比报告简介：
1、在左边监测器树中选择需要生成对比报告的监测器；
2、根据监测器的TEMPLATE生成不同类型的对比报告；
3、同一类型对比报告在同一张图上以不同颜色的线表示；
*/