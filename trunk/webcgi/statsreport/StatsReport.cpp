/*************************************************
*  @file StatsReport.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include ".\statsreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"

#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVMainTable.h"
#include <math.h>

#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
typedef void (GenExcelFile)(string name, list<forXLSItem>::iterator xlsListIterator1, list<forXLSItem>::iterator xlsListIterator2);
//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

using namespace std;

/***************************************************
参数：
	str:需替换的字符串
	old_value:被替换的字符串
	new_value:替换的字符串

功能：
    用new_value替换str中的所有old_value字符串

返回值：
    替换后的字符串
***************************************************/
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++苏合 2007-10-10+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//通过监视器对象找到其阀值                                                                                                            +
//                                                                                                                                    +
//参数：                                                                                                                              +
//   [in]  hMon     监视器对象                                                                                                        +
//   [out] bound    阀值                                                                                                              +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void getBoundName(OBJECT hMon, string & bound)
{
	PAIRLIST ParamList;
	bool bFind;
	LISTITEM ParamItem;
	MAPNODE monitorTempNode;
	MAPNODE ma;
	MAPNODE monitorNode;
	OBJECT objTempMonitor = INVALID_VALUE;
	OBJECT objRes=LoadResource("default", "localhost");
	MAPNODE ResNode=GetResourceNode(objRes);
	string getvalue;   //“getvalue”是用来保存监视器在模板中的ID

	monitorNode = GetMonitorMainAttribNode(hMon);
	if (FindNodeValue(monitorNode, "sv_monitortype", getvalue) )
	{						
		objTempMonitor = GetMonitorTemplet(atoi(getvalue.c_str())); //监视器模板对象
	}

	string strCount, strParamValue, strParamOperate, strParamRelation, strName;
	string strTemp;

	bound = "正常：[";
	ma = GetMonitorGoodAlertCondition(hMon);
	bFind = FindNodeValue(ma, "sv_conditioncount", strCount);  //读取阀值条件的数目
	int iCount = atoi(strCount.c_str());
	for (int i=1; i<=iCount; i++)
	{
		string paraIndex;
		char buf[10];
		itoa(i,buf,10);
		paraIndex = buf;
		strTemp = "sv_paramname" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strName);
	
		//在监视器模板的返回值中查找阀值条件的名字
		if( (objTempMonitor != INVALID_VALUE) && FindMTReturnFirst(objTempMonitor,ParamItem))
		{
			while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
			{ 
				ParamList.clear();
				if(::EnumNodeAttrib(monitorTempNode,ParamList))
				{	
					string sReturnName = "", MonitorIDSName ="";
					FindNodeValue(monitorTempNode, "sv_name", sReturnName);
					if(sReturnName == strName)
					{
						FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
						FindNodeValue(ResNode,MonitorIDSName, strName);
						break;
					}
				}
			}
		}
		bound += strName;
		strTemp = "sv_operate" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamOperate); //读取阀值操作符号（比如“>”“<=”）
		bound += strParamOperate;

		strTemp = "sv_paramvalue" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamValue);	//读取阀值
		bound += strParamValue;

		if(i<iCount)
		{
			strTemp = "sv_relation" + paraIndex;
			bFind = FindNodeValue(ma, strTemp, strParamRelation); //读取关系符
			bound = bound + " " + strParamRelation + " "; //加入空格，使显示更美观																	
		}
	}
	bound += "]";

	bound += "；危险：[";
	strCount = strParamValue = strParamOperate = strParamRelation = strName = "";
	iCount = 0;
	ma = GetMonitorWarningAlertCondition(hMon);
	bFind = FindNodeValue(ma, "sv_conditioncount", strCount);  //读取阀值条件的数目
	iCount = atoi(strCount.c_str());
	for (int i=1; i<=iCount; i++)
	{
		string paraIndex;
		char buf[10];
		itoa(i,buf,10);
		paraIndex = buf;
		strTemp = "sv_paramname" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strName);

		//在监视器模板的返回值中查找阀值条件的名字
		if( (objTempMonitor != INVALID_VALUE) && FindMTReturnFirst(objTempMonitor,ParamItem))
		{
			while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
			{ 
				ParamList.clear();
				if(::EnumNodeAttrib(monitorTempNode,ParamList))
				{	
					string sReturnName = "", MonitorIDSName ="";
					FindNodeValue(monitorTempNode, "sv_name", sReturnName);
					if(sReturnName == strName)
					{
						FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
						FindNodeValue(ResNode,MonitorIDSName, strName);
						break;
					}
				}
			}
		}
		bound += strName;
		strTemp = "sv_operate" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamOperate); //读取阀值操作符号（比如“>”“<=”）
		bound += strParamOperate;

		strTemp = "sv_paramvalue" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamValue);	//读取阀值
		bound += strParamValue;

		if(i<iCount)
		{
			strTemp = "sv_relation" + paraIndex;
			bFind = FindNodeValue(ma, strTemp, strParamRelation); //读取关系符
			bound = bound + " " + strParamRelation + " "; //加入空格，使显示更美观																	
		}
	}
	bound += "]";

	bound += "；错误：[";
	strCount = strParamValue = strParamOperate = strParamRelation = strName = "";
	iCount = 0;
	ma = GetMonitorErrorAlertCondition(hMon);
	bFind = FindNodeValue(ma, "sv_conditioncount", strCount);  //读取阀值条件的数目
	iCount = atoi(strCount.c_str());
	for (int i=1; i<=iCount; i++)
	{
		string paraIndex;
		char buf[10];
		itoa(i,buf,10);
		paraIndex = buf;
		strTemp = "sv_paramname" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strName);

		//在监视器模板的返回值中查找阀值条件的名字
		if( (objTempMonitor != INVALID_VALUE) && FindMTReturnFirst(objTempMonitor,ParamItem))
		{
			while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
			{ 
				ParamList.clear();
				if(::EnumNodeAttrib(monitorTempNode,ParamList))
				{	
					string sReturnName = "", MonitorIDSName ="";
					FindNodeValue(monitorTempNode, "sv_name", sReturnName);
					if(sReturnName == strName)
					{
						FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
						FindNodeValue(ResNode,MonitorIDSName, strName);
						break;
					}
				}
			}
		}
		bound += strName;
		strTemp = "sv_operate" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamOperate); //读取阀值操作符号（比如“>”“<=”）
		bound += strParamOperate;

		strTemp = "sv_paramvalue" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamValue);	//读取阀值
		bound += strParamValue;

		if(i<iCount)
		{
			strTemp = "sv_relation" + paraIndex;
			bFind = FindNodeValue(ma, strTemp, strParamRelation); //读取关系符
			bound = bound + " " + strParamRelation + " "; //加入空格，使显示更美观																	
		}
	}
	bound += "]";
}


/*******************************************************************
参数:
	szIndex:主ID
	monitorlist:返回监测器ID

功能:
    获取组下的所有监测器ID
*******************************************************************/
void EnumGroup(std::string szIndex,
			   std::list<string>& monitorlist)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    std::list<string> monlist;

    if(!szIndex.empty())
    {
        OBJECT group = GetGroup(szIndex);
        if(group != INVALID_VALUE)
        {    
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                
				for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
					std::string lstEntity = *lstItem;
					OBJECT hEntity = GetEntity(lstEntity);
					
					bool bRet = GetSubMonitorsIDByEntity(hEntity, monlist);

					std::list<string>::iterator litem = monlist.begin();
					
					std::list<string>::iterator monitem = monlist.begin();
					std::list<string>::iterator monitoritem = monitorlist.begin();
					bool bMerge = true;
					//判断子组下的设备LIST是否为空
					if(monitorlist.size() > 0 && monlist.size() > 0)
					{
						string temp = *monitem;
						string temp1= *monitoritem;
						//判断监测器在LIST中是否存在
						for(monitoritem = monitorlist.begin(); monitoritem != monitorlist.end(); monitoritem++)
						{					
							temp1 = *monitoritem;
							if(strcmp(temp.c_str(), temp1.c_str()) == 0)	
							{								
								bMerge = false;
								break;
							}
							
						}
					}
					//如果不存在则加入队列
					if(bMerge)
					{
						monitorlist.merge(monlist);										
					}
                }            
            }
            //如果是子组，递归获取子组下的监测器
			if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    EnumGroup(szSubGroupID, monitorlist);
                }                
            }

            CloseGroup(group);
        }        
    }
}


std::string CStatsReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
			strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

void ClearException(double *data, int count)
{
	//计算误差去除异常值，原理：测量误差大于3倍均方根误差为异常值
				
	if(count > 100)
	{
		float lCount = 0;
		float lAverage = 0;
		double lsCount = 0;
		double lsAverage = 0;
		for(int m = 0; m < count; m++)
		{
			lCount += data[m];
			
		}
		lAverage = lCount / count;

		for(int m = 0; m < count; m++)
		{
			lsCount += (data[m] - lAverage)*(data[m] - lAverage);
		}
		
		lsAverage = sqrt(lsCount/(count - 1))*3;
		

		for(int m = 0; m < count; m++)
		{						
			if(fabs(data[m] - lAverage) > lsAverage)
			{
				OutputDebugString("----------异常值--------------\n");
				char buf[256];
				sprintf(buf, "%f", data[m]);
				OutputDebugString(buf);
				//为异常值
				for(int m1 = m; m1 < count - 1; m1++)
				{
					data[m1] = data[m1+1];
					
				}
				count--;
				ClearException(data, count);
			}
			
		}
		
	}
	
}

/***************************************************
参数：
	starttime:开始时间
	endtime:截止时间
	reportname:报告名称
	bClicket:是否列出阀值
	bListError:是否列出错误
	bListDanger:是否列出危险
	bListStatsResult:是否列出状态总结
	bListImage:是否列出图形
	bGenExcel:是否导出excel文件                //Ticket #123(统计报告形式修改-江苏工行) 新增参数   苏合 2007-08-23
	parent:报告容器

功能：
	构造函数
****************************************************/
//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
// CStatsReport::CStatsReport(chen::TTime starttime,
// 						   chen::TTime endtime,
// 						   std::string reportname,
// 						   bool bClicket,
// 						   bool bListError, 
// 						   bool bListDanger, 
// 						   bool bListStatsResult, 
// 						   bool bListImage, 
// 						   string szGraphic,
// 						   WContainerWidget *parent ):WContainerWidget(parent)
CStatsReport::CStatsReport(chen::TTime starttime,
						   chen::TTime endtime,
						   std::string reportname,
						   bool bClicket,
						   bool bListError, 
						   bool bListDanger, 
						   bool bListStatsResult, 
						   bool bListImage, 
						   string szGraphic,
						   bool bGenExcel,
						   WContainerWidget *parent ):WContainerWidget(parent)
//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
{
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
			FindNodeValue(ResNode,"IDS_Affirm_Delete_User",strDel);
			FindNodeValue(ResNode,"IDS_Time_Period",szInterTime);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Run_Case_Table",m_formText.szRunTitle);
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
			FindNodeValue(ResNode,"IDS_Normal",m_formText.szNormal);
			FindNodeValue(ResNode,"IDS_Warning",m_formText.szDanger);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szError);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Max_Value",szMaxValue);
			FindNodeValue(ResNode,"IDS_Average_Value",szAverageValue);
			FindNodeValue(ResNode,"IDS_Min_Value",szMinValue);
			
			FindNodeValue(ResNode,"IDS_SiteView_Copyright",strCompany);
		}
	}
/*	//给变量赋初值
	strMainTitle ="统计报告";
	strTitle ="统计报告列表";
	strLoginLabel = "名 称";	
	strNameUse = "统计报告图";
	strNameEdit="编辑名称";
	strNameTest="游龙科技";
	strDel=  "确认删除选中用户吗？";
	szInterTime = "时间段:";
*/
	m_starttime = starttime;
	m_endtime = endtime;
	m_reportname = reportname;
	szInterTime += starttime.Format();
	szInterTime += "~";
	szInterTime += endtime.Format();
	normalrecnum = 1;
	dangerrecnum = 1;
	errorrecnum = 1;

	szComboGraphic = szGraphic;

	//主界面
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
// 	ShowMainTable(starttime, endtime, reportname, bClicket, bListError,bListDanger, \
// 		bListStatsResult, bListImage);
	ShowMainTable(starttime, endtime, reportname, bClicket, bListError,bListDanger, \
		bListStatsResult, bListImage, bGenExcel);
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
}

//析构函数
CStatsReport::~CStatsReport(void)
{
	CloseResource(objRes);
}

void CStatsReport::InitPageItemNew(string title, bool bListImage)
{
	m_pMainTable = new WSVMainTable(this, "", false);

	WTable *titleTable = new WTable(m_pMainTable->GetContentTable()->elementAt(1,0));	
	titleTable->elementAt(0,0)->setContentAlignment(AlignCenter | AlignMiddle);
	titleTable->elementAt(1,0)->setContentAlignment(AlignCenter | AlignMiddle);
	pReportTitle = new WText(title, (WContainerWidget*)titleTable->elementAt(0,0));

	WFont font1;
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);




	//报告时间段
	WText * text1 = new WText(szInterTime, (WContainerWidget*)titleTable->elementAt(1, 0));
	
	std::string linkstr = "<a href='../fcgi-bin/statsreportlist.exe?id=";
	linkstr += title;
	linkstr += "'>";
	linkstr += strReturn;
	linkstr += "</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";

	titleTable->elementAt(2, 0)->setContentAlignment(AlignRight);
	new WText(linkstr,(WContainerWidget*)titleTable->elementAt(2, 0));
	new WText("&nbsp;",(WContainerWidget*)titleTable->elementAt(3, 0));

	m_pUptimeTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(2,0), List, m_formText.szRunTitle, false);  
	if (m_pUptimeTable->GetContentTable() != NULL)
	{
		m_pUptimeTable->AppendColumn(m_formText.szRunName,WLength(40,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunTime,WLength(20,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunDanger,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunError,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunNew,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunClicket,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
	}


	m_pMeasurementTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(3,0), List, m_formText.szMonitorTitle, false);  
	if (m_pMeasurementTable->GetContentTable() != NULL)
	{
		m_pMeasurementTable->AppendColumn(m_formText.szMonName,WLength(40,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonMeasure,WLength(30,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonMax,WLength(10,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonPer,WLength(10,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonLast,WLength(10,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");
	}

	m_pGraphTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(4,0), Blank, "图表", false);  

	pImageTable = new WTable(m_pGraphTable->GetContentTable()->elementAt(0 , 0));
	//如果bListImage为TRUE则隐藏图片TABLE
	if(!bListImage)
	{
		pImageTable->hide();
	}
}


/***********************************************************
参数：
	starttime:开始时间
	endtime:截止时间
	reportname:报告名称
	bClicket:是否列出阀值
	bListError:是否列出错误
	bListDanger:是否列出危险
	bListStatsResult:是否列出状态总结
	bListImage:是否列出图形
	bGenExcel:是否导出excel文件                //Ticket #123(统计报告形式修改-江苏工行) 新增参数   苏合 2007-08-23

	//parent:报告容器            没这个参数，去掉此注释。 苏合 2007-08-23

功能：
   生成报告主界面
***********************************************************/
//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
// void CStatsReport::ShowMainTable(chen::TTime starttime,
// 								 chen::TTime endtime, 
// 								 std::string reportname, 
// 								 bool bClicket, 
// 								 bool bListError, 
// 								 bool bListDanger, 
// 								 bool bListStatsResult, 
// 								 bool bListImage)
void CStatsReport::ShowMainTable(chen::TTime starttime,
								 chen::TTime endtime, 
								 std::string reportname, 
								 bool bClicket, 
								 bool bListError, 
								 bool bListDanger, 
								 bool bListStatsResult, 
								 bool bListImage,
								 bool bGenExcel)
//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

{	
	WIN32_FIND_DATA fd;
	//从注册表中取安装路径
	string	szRootPath = GetSiteViewRootPath();
	string szReport = szRootPath;
	szReport += "\\htdocs\\report";
	//判断报告存储路径是否存在，不存在则创建
	HANDLE fr=::FindFirstFile(szReport.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szReport.c_str(), NULL);
	}
	
	string szIconPath = szRootPath;
	szIconPath += "\\htdocs\\report\\Images";
	fr=::FindFirstFile(szIconPath.c_str(), &fd);
	//判断报告图片路径是否存在，不存在则创建
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szIconPath.c_str(), NULL);
	}

	new WText("<div id='view_panel' class='panel_view'>", this);

	//在生成的报告中包含basic.js
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	char buf_tmp[4096]={0};
    int nSize =4095;

	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
	string	szExcelPathName = GetSiteViewRootPath() + "\\htdocs\\report\\";


	string szExcelName = starttime.Format();	
	szExcelName += endtime.Format();
	szExcelName = replace_all_distinct(szExcelName, " ", "_");
	szExcelName = replace_all_distinct(szExcelName, ":", "_");

	szExcelName += reportname;

	replace_all_distinct(szExcelName, "*", "_");
	replace_all_distinct(szExcelName, "/", "_");
	replace_all_distinct(szExcelName, "\\", "_");
	replace_all_distinct(szExcelName,"?", "_");
	replace_all_distinct(szExcelName,  "|", "_");
	replace_all_distinct(szExcelName,  "<", "_");
	replace_all_distinct(szExcelName,  ">", "_");
	replace_all_distinct(szExcelName,  ":", "_");
	replace_all_distinct(szExcelName,  "\"", "_");
	replace_all_distinct(szExcelName,  " ", "_");
	replace_all_distinct(szExcelName,  "%20", "_");

	szExcelName += ".xls";
	szExcelName = szExcelPathName + szExcelName;
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

	//把报告名中的空格替换为%20   --------注释错误。应该是“把报告名中的%20替换为空格”以便在“reportset.ini”查找正确的节 苏合 2007-08-23
	replace_all_distinct(reportname, "%20", " ");
	std::string querystr;	
	int reccount = 0;
	strcpy(buf_tmp , reportname.c_str());
	
	OutputDebugString("----------------CStatsReport 1--------------------\n");

	if(buf_tmp != NULL)
	{
		//取报告对应监测器	
		GetMonitorGroup(buf_tmp, grouplist);
	}


	//新版本式样
	InitPageItemNew(buf_tmp,bListImage);

	//初始化页面元素
	//InitPageItem(pContainTable, buf_tmp);

	//增加列表标题栏
	//AddColum(NULL);
		
	std::list<string>::iterator item;
	int i6 = 1;//运行情况列表行数
	int i1, i2;
	char buf[256];
	char buf1[256];
	
	//生成图片TABLE
	//pImageTable = new WTable(pContainTable->elementAt(7 , 0));
	////如果bListImage为TRUE则隐藏图片TABLE
	//if(!bListImage)
	//{
	//	pImageTable->hide();
	//}


	//设置表格项顶端靠齐、居中
	//pContainTable->elementAt(7, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	int i3 = 0;//图片列表行数
	int fieldnum = 1;//监测数据统计列表行数
	int gnormalnum = 1;//正常列表行数
	int gdangernum = 1;//危险列表行数
	int gerrornum = 1;//错误列表行数
	int tcount = 0;//记录总个数

	std::list<string> monitorlist;//监测器list
	std::list<string>::iterator monitorlistitem;
	std::string bGroupStr = "";

	OutputDebugString("----------------CStatsReport 2--------------------\n");
	for(item = grouplist.begin(); item != grouplist.end(); item++)
	{			
		std::string monitorid = *item;				
		
		//取监测器组句柄
		OBJECT	hGroup = GetGroup(monitorid);
		std::list<string> monitoridlist;
		std::list<string>::iterator monitoridlistitem;
	
		//组句柄无效则判断是否为设备或监测器
		if(hGroup == INVALID_VALUE)
		{
			//取设备句柄
			hGroup = GetEntity(monitorid);
			//是设备
			if(hGroup != INVALID_VALUE)
			{		
				//取设备下的所有子监测器（monitoridlist为list<string>类型）
				bool bRet = GetSubMonitorsIDByEntity(hGroup, monitoridlist);
				
				if(monitoridlist.size() != 0)
				{
					monitoridlistitem = monitoridlist.begin();
					std::string szGmon = *monitoridlistitem;
					for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
						monitorlistitem++)
					{
						std::string tempid = *monitorlistitem;
						std::string tempid1 = *monitoridlistitem;
						//monitorlist中存在monitorid则跳到cont
						if(strcmp( tempid1.c_str(), tempid.c_str()) == 0)
						{
							goto cont;
						}
					}
				/*	for(monitoridlistitem = monitoridlist.begin(); monitoridlistitem != monitoridlist.end(); \
						monitoridlistitem++)
					{					
						std::string itemstr = *monitoridlistitem;			
						//根据监测器ID取指定时段的数据
						GetMonitorRecord(itemstr, starttime, endtime,bClicket,bListStatsResult, reportname, \
							tcount, i6, i3, fieldnum);
					}				
					*/
					//把monitoridlist组合进monitorlist,并销毁monitoridlist
					monitorlist.merge(monitoridlist);
				}
			}
			//是监测器
			else
			{		
				//比较monitorid是否在monitorlist中
				for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
					monitorlistitem++)
				{
					std::string tempid = *monitorlistitem;
					//monitorlist中存在monitorid则跳到cont
					if(strcmp( monitorid.c_str(), tempid.c_str()) == 0)
					{
						goto cont;
					}
				}
				//根据监测器ID取指定时段的数据
				monitorlist.push_back(monitorid);
				//GetMonitorRecord(monitorid, starttime, endtime, bClicket, bListStatsResult,\
					reportname, tcount, i6, i3, fieldnum);
			}
		}
		//是组,暂未处理要取组下的所有监测器
		else
		{					
			EnumGroup(monitorid, monitorlist);			
		}
		//如果存在监测器ID则返回循环
cont:
			;
	}

	OutputDebugString("----------------finish EnumGroup, start GetMonitorRecord--------------------\n");

	for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
		monitorlistitem++)
	{		
		std::string monitorid = *monitorlistitem;
		OutputDebugString("----------------GetMonitorRecord monitor id output--------------------\n");
		OutputDebugString(monitorid.c_str());
		OutputDebugString("\n");

		GetMonitorRecord(monitorid, starttime, endtime, bClicket, bListStatsResult,\
					reportname, tcount, i6, i3, fieldnum);
	}
	
	//rettimelist,retstatlist,retstrlist未使用，retmonnamelist取第一个值
	rettimelistitem = rettimelist.begin();
	retstatlistitem = retstatlist.begin();
	retstrlistitem = retstrlist.begin();
	retmonnamelistitem = retmonnamelist.begin();
	
	bool bnormal = true; //是否列出正常
	bool bdanger = true;//是否列出危险
	bool berror = true;//是否列出错误
	std::string tempstr ;
	
	string strError,strName,strTime,strState,strWarning;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Error",strError);
			FindNodeValue(ResNode,"IDS_Name",strName);
			FindNodeValue(ResNode,"IDS_Time",strTime);
			FindNodeValue(ResNode,"IDS_State",strState);
			FindNodeValue(ResNode,"IDS_Warning",strWarning);
		}
		CloseResource(objRes);
	}

	bool bTr = false;//表格行之间间隔样式的变化（白底、淡蓝底）
	//列出错误列表
	if(bListError)
	{

		// m_pErrorTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(5,0), List, "错误", false);  

		// ++++++ 扩展了将危险列表Title文本设置为特殊颜色的功能 ++++++
		// 2007/6/27 龚超
		// 需要在css.css文件中增加如下定义
		// .table_title_text_error {
		//		width:100%;
		//		color:#FFF01F;
		//		font-weight:bold;
		// }
		m_pErrorTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(5,0), List, "错误", false);  
		// ------ 扩展了将危险列表Title文本设置为特殊颜色的功能 ------

		if (m_pErrorTable->GetContentTable() != NULL)
		{
			m_pErrorTable->AppendColumn("名 称",WLength(25,WLength::Percentage));
			m_pErrorTable->SetDataRowStyle("table_data_grid_item_img");

			m_pErrorTable->AppendColumn("时 间",WLength(25,WLength::Percentage));
			m_pErrorTable->SetDataRowStyle("table_data_grid_item_img");

			m_pErrorTable->AppendColumn("状 态",WLength(55,WLength::Percentage));
			m_pErrorTable->SetDataRowStyle("table_data_grid_item_text");
		}

		//left frame is 80px;
		//new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
		//tempstr = "<tr id='o25' style='text-align:left;text-align:center'><td colspan=3 style='vertical-align:top;font-size:18px;text-align:center;' bgcolor=#ffffff align='center'><b>错误</b></td></tr>";
		//new WText(tempstr, this);
		//tempstr = "<tr id='o63' class='t1title' style='vertical-align:top;text-align:left;'>"
		//	"<td id='o64' style='vertical-align:top;text-align:left;'><span id='o65'  >名称</span></td>"
		//	"<td id='o66' style='vertical-align:top;text-align:left;'><span id='o67'  >时间</span></td>"
		//	"<td id='o68' style='vertical-align:top;text-align:left;'><span id='o69'  >状态</span></td></tr>";
		//new WText(tempstr, this);

		int iRow = 1;
		for(retmonnamelistitem = reterrornamelist.begin(), rettimelistitem = reterrortimelist.begin(), retstrlistitem = reterrorstatuslist.begin();\
			retmonnamelistitem != reterrornamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
		{
			m_pErrorTable->InitRow(iRow);
			
			m_pErrorTable->GeDataTable()->elementAt(iRow,0)->setContentAlignment(AlignCenter);
			new WText(*retmonnamelistitem, m_pErrorTable->GeDataTable()->elementAt(iRow,0));

			m_pErrorTable->GeDataTable()->elementAt(iRow,2)->setContentAlignment(AlignCenter);
			new WText(*rettimelistitem, m_pErrorTable->GeDataTable()->elementAt(iRow,2));
			
			m_pErrorTable->GeDataTable()->elementAt(iRow,4)->setContentAlignment(AlignCenter);
			new WText(*retstrlistitem, m_pErrorTable->GeDataTable()->elementAt(iRow,4));
			
			//if(bTr)
			//{
			//	bTr = false;
			//	tempstr = "<tr id='o63' class='tr2' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//else
			//{
			//	bTr = true;
			//	tempstr = "<tr id='o63' class='tr1' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//tempstr += *retmonnamelistitem;
			//tempstr += "</span></td><td id='o66' style='text-align:left;'><span id='o67'  >";
			//tempstr += *rettimelistitem;
			//tempstr += "</span></td><td id='o68' style='text-align:left;'><span id='o69'  >";
			//tempstr += *retstrlistitem;
			//tempstr += "</span></td></tr>";
			//new WText(tempstr, this);

			iRow++;
		}
		//new WText("</tbody></table>", this);
	}

	//是否列出危险列表
	if(bListDanger)
	{
//		m_pWarnTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(6,0), List, "危险", false, 2);

		// ++++++ 扩展了将危险列表Title文本设置为特殊颜色的功能 ++++++
		// 2007/6/27 龚超
		// 需要在css.css文件中增加如下定义
		// .table_title_text_warning {
		//		width:100%;
		//		color:#FFF01F;
		//		font-weight:bold;
		// }
		m_pWarnTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(6,0), List, "危险", false);  
		// ------ 扩展了将危险列表Title文本设置为特殊颜色的功能 ------

		if (m_pWarnTable->GetContentTable() !=NULL)
		{
			m_pWarnTable->AppendColumn("名 称",WLength(25,WLength::Percentage));
			m_pWarnTable->SetDataRowStyle("table_data_grid_item_img");

			m_pWarnTable->AppendColumn("时 间",WLength(25,WLength::Percentage));
			m_pWarnTable->SetDataRowStyle("table_data_grid_item_img");

			m_pWarnTable->AppendColumn("状 态",WLength(55,WLength::Percentage));
			m_pWarnTable->SetDataRowStyle("table_data_grid_item_text");
		}

		//new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
		//tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='vertical-align:top;font-size:18px' bgcolor=#ffffff align='center'><b>危险</b></td></tr>";
		//new WText(tempstr, this);
		//tempstr = "<tr id='o63' class='t1title' style='vertical-align:top;text-align:left;'>"
		//	"<td id='o64' style='vertical-align:top;text-align:left;'><span id='o65'  >名称</span></td>"
		//	"<td id='o66' style='vertical-align:top;text-align:left;'><span id='o67'  >时间</span></td>"
		//	"<td id='o68' style='vertical-align:top;text-align:left;'><span id='o69'  >状态</span></td></tr>";
		//new WText(tempstr, this);

		int iRow = 1;
		for(retmonnamelistitem = retdangernamelist.begin(), rettimelistitem = retdangertimelist.begin(), retstrlistitem = retdangerstatuslist.begin();\
			retmonnamelistitem != retdangernamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
		{
			m_pWarnTable->InitRow(iRow);
			m_pWarnTable->GeDataTable()->elementAt(iRow,0)->setContentAlignment(AlignCenter);
			new WText(*retmonnamelistitem, m_pWarnTable->GeDataTable()->elementAt(iRow,0));

			m_pWarnTable->GeDataTable()->elementAt(iRow,2)->setContentAlignment(AlignCenter);
			new WText(*rettimelistitem, m_pWarnTable->GeDataTable()->elementAt(iRow,2));

			m_pWarnTable->GeDataTable()->elementAt(iRow,4)->setContentAlignment(AlignCenter);
			new WText(*retstrlistitem, m_pWarnTable->GeDataTable()->elementAt(iRow,4));

			//if(bTr)
			//{
			//	bTr = false;
			//	tempstr = "<tr id='o63' class='tr1' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//else
			//{
			//	bTr = true;
			//	tempstr = "<tr id='o63' class='tr2' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//tempstr += *retmonnamelistitem;
			//tempstr += "</span></td><td id='o66' style='text-align:left;'><span id='o67'  >";
			//tempstr += *rettimelistitem;
			//tempstr += "</span></td><td id='o68' style='text-align:left;'><span id='o69'  >";
			//tempstr += *retstrlistitem;
			//tempstr += "</span></td></tr>";

			//new WText(tempstr, this);
			iRow++;
		}
		//new WText("</tbody></table>", this);
	}

	//Copyright SiteView输出
	new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
	//tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='color:blue;font-family:Arial;font-size:3;' bgcolor=#ffffff align='center'>Copyright SiteView</td></tr>";
	tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='color:blue;font-family:Arial;' bgcolor=#ffffff align='center'>";
	tempstr += strCompany; 
	tempstr += "</td></tr>";
	new WText(tempstr, this);
	new WText("</tbody></table>", this);

	new WText("</div>", this);
	AddJsParam("bGeneral","true");
	AddJsParam("uistyle", "viewpanan");
	AddJsParam("fullstyle", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
	if (bGenExcel)
	{
		HINSTANCE hDll = LoadLibrary("genExcel.dll");						
		if (hDll)
		{
			GenExcelFile * func = (GenExcelFile*)::GetProcAddress(hDll, "run");
			list<forXLSItem>::iterator it1 = xlsList.begin();
			list<forXLSItem>::iterator it2 = xlsList.end();
// 			OutputDebugString("\n++++++++++++++++++++++++++++sxc++++++++++++++++++\n");
// 			OutputDebugString(it1->name.c_str());
// 			OutputDebugString("\n++++++++++++++++++++++++++++sxc++++++++++++++++++\n");
			func(szExcelName, it1, it2);
		}
		else
			OutputDebugString("\n生成Excel的动态链接库加载错误\n");
	}
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

}


//添加客户端脚本变量
void CStatsReport::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}



/***********************************************
参数：
	pContain:父容器
功能：
    运行情况、监测情况标题栏
***********************************************/
void CStatsReport::AddColum(WTable* pContain)
{
	//运行情况列表标题栏
	new WText(m_formText.szRunName, pRunTable->elementAt(0, 0));
	new WText(m_formText.szRunTime, pRunTable->elementAt(0, 1));
	new WText(m_formText.szRunDanger, pRunTable->elementAt(0, 2));
	new WText(m_formText.szRunError, pRunTable->elementAt(0, 3));
	new WText(m_formText.szRunNew, pRunTable->elementAt(0, 4));
	new WText(m_formText.szRunClicket, pRunTable->elementAt(0, 5));	
	pRunTable->setCellSpaceing(0);
	pRunTable->GetRow(0) ->setStyleClass("t1title");	
	
	//监测数据标题栏
	new WText(m_formText.szMonName, pMonitorTable->elementAt(0, 0));
	new WText(m_formText.szMonMeasure, pMonitorTable->elementAt(0, 1));
	new WText(m_formText.szMonMax, pMonitorTable->elementAt(0, 2));
	new WText(m_formText.szMonPer, pMonitorTable->elementAt(0, 3));
	new WText(m_formText.szMonLast, pMonitorTable->elementAt(0, 4));	
	pMonitorTable->setCellSpaceing(0);
	pMonitorTable->GetRow(0) ->setStyleClass("t1title");
}


/*****************************************************************
参数：
	data:生成图形数组
	time:图形横坐标的时间数组
	len:数组长度
	xlabels:横坐标标签（未使用）
	xscalelen:横坐标刻度（未使用）
	xStep:横坐标标签数组STEP（未使用）
	ylabels:纵坐标标签数组（未使用）
	yscalelen:（未使用）
	yScale:纵坐标最大刻度
	yStep:纵坐标标签数组STEP（未使用）
	xLinearScale:（未使用）
	starttime:图形横坐标开始时间
	endtime:图形横坐标截止时间
	Title:顶端居中标题
	xTitle:左侧标题
	filename:生成图片文件名

功能：
    依据数组传入值及时间生成图表并保存成文件
*****************************************************************/
void CStatsReport::GenLineImage(double data[],
								double bdata[],
								double time[],
								const int len, 
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
								char* Title, char* xTitle, char * filename)
{    
	
	{
		wchar_t lpWide[256];//unicode 字符串

		//300*2：图表宽度，300：高度，0xffffff:背景色，1：边框
		XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

		//设置表格 55：X轴偏移 36：Y轴偏移 260*2：表格宽度 200：高度 0XA08040：坐标轴COLOR 
		//dashLineColor:虚线并设置COLOR 
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
		
		//char*转到wchar*
		mbstowcs(lpWide, Title, 256);
		
		//wchar*转到UTF8
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

		//设置图表标题
		c->addTitle(lpMultiByteStr,
			"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

		memset(lpMultiByteStr, 0, 256);		
		memset(lpWide, 0, 256);
		mbstowcs(lpWide, xTitle, 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

		//设置左侧标题
		c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

		lpWideCharStr = L"Copyright SiteView";
		memset(lpMultiByteStr, 0, 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

		//设置Y轴刻度
		if(yScale <= 10)
		{
			c->yAxis()->setLinearScale(0, yScale + 1);
		}
		else
		{
			c->yAxis()->setLinearScale(0, yScale);
		}

		//增加横坐标时间层 数据与时间可以对应
		c->addScatterLayer(DoubleArray(time, len), DoubleArray(data, len),
			"", Chart::PolygonShape(0), 0, 0xffff00);

		string strAreaGraphic,strLineGraphic;
		OBJECT objRes=LoadResource("default", "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				FindNodeValue(ResNode,"IDS_AreaGraphic",strAreaGraphic);
				FindNodeValue(ResNode,"IDS_Line_Graphic",strLineGraphic);
			}
			CloseResource(objRes);
		}
		strAreaGraphic = replace_all_distinct(strAreaGraphic, " ", "");
		strLineGraphic = replace_all_distinct(strLineGraphic, " ", "");

		OutputDebugString("-------------stats report image type---------------\n");
		OutputDebugString(strLineGraphic.c_str());
		OutputDebugString("\n");
		OutputDebugString(szComboGraphic.c_str());
		OutputDebugString("\n");

		//AreaLayer *layer1 = c->addAreaLayer();
		if(strcmp(szComboGraphic.c_str(), strAreaGraphic.c_str()) == 0)
		{
			AreaLayer *layer = c->addAreaLayer();	

			//layer1 ->setXData(DoubleArray(time, len));

			//设置时间数组
			layer ->setXData(DoubleArray(time, len));
			
			//增加数据
			//layer1->addDataSet(DoubleArray(bdata, len))->setDataColor(
			//0xff0000, 0xff0000);

			layer->addDataSet(DoubleArray(data, len))->setDataColor(
				0x80d080, 0x007000);
		}
		else //(strcmp(szComboGraphic.c_str(), strLineGraphic.c_str()) == 0)
		{
			LineLayer *linelayer = c->addLineLayer(DoubleArray(data, len), 0x007000);
			
			linelayer->setXData(DoubleArray(time, len));
		//	linelayer->addDataSet(DoubleArray(data, len));			
			OutputDebugString("--------------generate line graphic-----------------\n");
		}
			


		//生成图表
		c->makeChart(filename);

		//释放UNICODE字符串内存
		free(lpMultiByteStr);

		//释放CHART内存
		delete c;
	}
	

}
/*
void CStatsReport::GenLineImage(double data[],
								double bdata[],
								double time[],
								const int len, 
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
								char* Title, char* xTitle, char * filename)
{    
	wchar_t lpWide[256];//unicode 字符串

	//300*2：图表宽度，300：高度，0xffffff:背景色，1：边框
	XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

	//设置表格 55：X轴偏移 36：Y轴偏移 260*2：表格宽度 200：高度 0XA08040：坐标轴COLOR 
	//dashLineColor:虚线并设置COLOR 
	c->setPlotArea(55, 36, 260*2, 200, 0xffffff, -1, 0xa08040, c->dashLineColor(0x000000,
        0x000103), c->dashLineColor(0x000000, 0x000103));

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;
	//设置中文
	setlocale(LC_CTYPE, ""); 

	memset(lpWide, 0, 256);
	
	//char*转到wchar*
	mbstowcs(lpWide, Title, 256);
	
	//wchar*转到UTF8
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

	//设置图表标题
	c->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

	//设置左侧标题
    c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	lpWideCharStr = L"Copyright SiteView";
	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

	//设置Y轴刻度
	if(yScale <= 10)
	{
		c->yAxis()->setLinearScale(0, yScale + 1);
	}
	else
	{
		c->yAxis()->setLinearScale(0, yScale);
	}

	//增加横坐标时间层 数据与时间可以对应
	c->addScatterLayer(DoubleArray(time, len), DoubleArray(data, len),
		"", Chart::PolygonShape(0), 0, 0xffff00);

	//AreaLayer *layer1 = c->addAreaLayer();

	AreaLayer *layer = c->addAreaLayer();	

	//layer1 ->setXData(DoubleArray(time, len));

	//设置时间数组
	layer ->setXData(DoubleArray(time, len));
	
	//增加数据
	//layer1->addDataSet(DoubleArray(bdata, len))->setDataColor(
	//0xff0000, 0xff0000);

	layer->addDataSet(DoubleArray(data, len))->setDataColor(
        0x80d080, 0x007000);
	


	//生成图表
    c->makeChart(filename);

	//释放UNICODE字符串内存
	free(lpMultiByteStr);

	//释放CHART内存
    delete c;
}
*/
/*********************************************************
参数：
	hRecSet:记录句柄
	monitorname:监测器名称
	retmonnamelist:监测器名称LIST
	
功能：
	取数据库全字符串显示记录集

返回值：
    危险LIST、错误LIST
*********************************************************/
void CStatsReport::GetMonitorDataRecStr(RECORDSET hRecSet, 
										std::string monitorname,
										std::list<string> &retmonnamelist, 
										std::list<int> &retstatlist, 
										std::list<string>& retstrlist, 
										std::list<string>& rettimelist)
{
	LISTITEM item;
	RECORD hRec;			
	int stat;
	std::string str;

	//取第一条数据记录句柄
	FindRecordFirst(hRecSet, item);

	//取下一条数据记录
	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		//取字符显示的记录
		GetRecordDisplayString(hRec, stat, str);			
		TTime tm;
		//取记录创建时间
		GetRecordCreateTime(hRec,tm);
		//记录状态为危险
		if(stat == 2)
		{
			//返回值到retdangerstatuslist
			//监测器名到retdangernamelist
			//创建时间到retdangertimelist
			retdangernamelist.push_back(monitorname);
			retdangertimelist.push_back(tm.Format());
			retdangerstatuslist.push_back(str);			
		}
		//记录状态为错误
		if(stat == 3)
		{
			//返回值到reterrorstatuslist
			//监测器名到reterrornamelist
			//创建时间到reterrortimelist
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
void CStatsReport::GetMonitorDataRec(RECORDSET hRecSet, 
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

/****************************************************************
参数：
	reportname:报告名称
	grouplist:组、设备、监测器LIST

功能：
    从reportset.ini的GroupRight取以逗号分割的组、设备、监测器
*****************************************************************/
void CStatsReport::GetMonitorGroup(char * reportname,
								   std::list<string> & grouplist)
{
	std::string buf1 = reportname;

	//取 id= 后的报告名
	int pos = buf1.find("=", 0);
	std::string querystr = buf1.substr(pos+1, buf1.size() - pos - 1);			

	//取GroupRight键下的值
	std::string defaultret = "error";
	std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "reportset.ini");

	//逗号分割的组、设备、监测器放入grouplist
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

/****************************************************
参数：
	table:上一级TABLE
	title:报告标题

功能：
    初始化运行情况列表、监测情况报表等
****************************************************/
void CStatsReport::InitPageItem(WTable *table,
								std::string title)
{
	//框架TABLE T5：{width:100%;height:100%;}
	WTable * FrameTable = new WTable(this);	
	FrameTable ->setStyleClass("t5");
	
	//返回项TABLE（二级）
	WTable * column = new WTable((WContainerWidget*)FrameTable->elementAt(1, 0));
	FrameTable->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);
	column->setStyleClass("StatsTable");	

	std::string linkstr = "<a href='../fcgi-bin/statsreportlist.exe?id=";
	linkstr += title;
	linkstr += "'>";
	linkstr += strReturn;
	linkstr += "</a>";

	WText * ltext = new WText(linkstr, (WContainerWidget*)column->elementAt(0, 0));	
	column->elementAt(0, 0)->setContentAlignment(AlignTop | AlignRight);
	column->elementAt(0, 0)->setStyleClass("t1title");
	ltext->decorationStyle().setForegroundColor(Wt::black);

	//报告主要项TABLE容器
	pContainTable = new WTable((WContainerWidget*)FrameTable->elementAt(2,0));
	pContainTable ->setStyleClass("t5");

	//报告标题
	pReportTitle = new WText(title, (WContainerWidget*)pContainTable->elementAt(0, 0));
	pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	WFont font1;
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);

	//报告时间段
	WText * text1 = new WText(szInterTime, (WContainerWidget*)pContainTable->elementAt(1, 0));
	pContainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	//运行情况列表标题
	text1 = new WText(m_formText.szRunTitle, pContainTable->elementAt(2, 0));
	font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
	text1 ->decorationStyle().setFont(font1);
	pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
	pRunTable = new WTable(pContainTable->elementAt(3, 0));

	//运行情况列表
	pRunTable->setStyleClass("StatsTable");	
	pRunTable->tableprop_ = 2;
	pRunTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(3, 0)->setContentAlignment(AlignTop | AlignCenter);

	//监测情况列表标题
	text1 = new WText(m_formText.szMonitorTitle, pContainTable->elementAt(4, 0));
	text1 ->decorationStyle().setFont(font1);
	pContainTable ->elementAt(4, 0) ->setContentAlignment(AlignTop | AlignCenter);

	//监测情况列表
	pMonitorTable = new WTable(pContainTable->elementAt(5, 0));
	pMonitorTable->setStyleClass("StatsTable");	
	pMonitorTable->tableprop_ = 2;
	pMonitorTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(5, 0)->setContentAlignment(AlignTop | AlignCenter);

	//图表标题
	//text1 = new WText("图表", pContainTable->elementAt(6, 0));
	string strChart,strLineGraphic;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Map_Table",strChart);
		}
		CloseResource(objRes);
	}
	text1 = new WText(strChart, pContainTable->elementAt(6, 0));

	text1 -> decorationStyle().setFont(font1);
	pContainTable -> elementAt(6, 0) -> setContentAlignment(AlignTop | AlignCenter);

}

/*****************************************************
参数：
	reportname:报告名称
	starttime:开始时间
	endtime:截止时间
	value:监测器名称
	fieldlabel:返回值字段
	minval:最小值
	perval:平均值
	maxval:最大值
功能：
	写报告生成记录INI文件    
*****************************************************/
void CStatsReport::WriteGenIni(std::string reportname, 
							   std::string starttime,
							   std::string endtime,
							   std::string value,
							   std::string fieldlabel,
							   float minval, 
							   float perval,
							   float maxval)
{
	char buf[256];
	//section节格式：报告名$开始时间$截止时间$
	std::string section = reportname;
	section += "$";
	section += starttime;
	section += "$";
	section += endtime;
	section += "$";

	//键值格式：监测器名$返回值$
	std::string keystr = value;
	keystr += "$";
	keystr += fieldlabel;
	keystr += "$";
	
	std::string valstr ;
	//值格式：最小值$平均值$最大值$
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

	//往reportgenerate.ini写值
	WriteIniFileString(section, keystr, valstr, "reportgenerate.ini");
}

/*****************************************************************
参数：
	monitorid:监测器ID
	starttime:开始时间
	endtime:截止时间
	bClicket:是否取阀值
	bListStatsResult:是否列示统计结果
	reportname:报告名称
	tcount:记录总条数
	i6:运行情况行数
	i3:图表个数
	fieldnum:监测情况行数

功能：
    取监测器时段内的数据库记录，并在运行情况列表、监测情况列表
	、图表列表、危险记录项列表、错误记录项列表中列示
*****************************************************************/
void CStatsReport::GetMonitorRecord(std::string monitorid, 
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
	//数据和时间数组也可动态分配 例：double *data = new double[5000];
	double data[50000];
	double *bdata = new double[50000]; 
	double time[50000];

	char buf[256];
	char buf2[256];	
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
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
	forXLSItem xlsItem;
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
	int reccount = 0;
	TTime tm;
	bool bStat = true;

	//监测器句柄
	OBJECT hMon = GetMonitor(monitorid);

	//取监测器数据集句柄
	RECORDSET hRecSet = QueryRecords(monitorid, m_starttime, m_endtime);

	size_t countrec;
	//监测器数据记录条数
	GetRecordCount(hRecSet,countrec);
	tcount += countrec;

	//取第一条记录句柄
	FindRecordFirst(hRecSet, item);
		
	//取数据集中的记录
	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{				
		//取记录创建时间
		GetRecordCreateTime(hRec,tm);
		//取记录显示字符串
		GetRecordDisplayString(hRec, stat,dispstr);
		
		//最新状态
		if(bStat)
		{
			laststat = stat;
			bStat = false;
		}

		//状态为正常或禁止
		if(stat == 1 || stat == 4)
		{
			normalnum++;				
		}
		//危险状态
		else if(stat == 2)
		{
			dangernum++;				
		}
		//错误状态
		else
		{
			errornum++;				
		}
		
		//字符显示记录push_back进队列
		allstrlist.push_back(dispstr);									
	}		
	
	//构造Chart::chartTime格式时间
	double cstarttime = Chart::chartTime(tm.GetYear(), tm.GetMonth(), tm.GetDay(),\
		tm.GetHour(), tm.GetMinute(), tm.GetSecond());

	//取监测器主属性
	MAPNODE node = GetMonitorMainAttribNode(hMon);

	//sv_name监测器名称（需要判断是监测器还是组）
	FindNodeValue(node, "sv_name", value);

	//设备ID
	string strEntity =	FindParentID(monitorid);

	//设备句柄
	OBJECT hEntity = GetEntity(strEntity);

	//设备主属性
	MAPNODE entitynode = GetEntityMainAttribNode(hEntity);

	//设备名称
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

	//运行情况名称 格式： 设备名：监测器
	//new WText(hrefstr, pRunTable->elementAt(i6, 0));

	m_pUptimeTable->InitRow(i6);

	if(entityvalue.empty() && value.empty())
	{
	}
	else
	{
		m_pUptimeTable->GeDataTable()->elementAt(i6, 0)->tablecellprop = " nowrap";
		m_pUptimeTable->GeDataTable()->elementAt(i6, 0)->setContentAlignment(AlignCenter);
		new WText(hrefstr, m_pUptimeTable->GeDataTable()->elementAt(i6, 0));
	}
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
	xlsItem.name = entityvalue + ":" + value;
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
	
	memset(buf2, 0, 256);
	if((normalnum + dangernum + errornum + othernum) != 0)
	{
		//计算运行情况表中的正常、危险、错误百分比，
		perval = normalnum*100/(normalnum + dangernum + errornum + othernum);
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
		xlsItem.normalRunTime = perval;
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
		sprintf(buf2, "%d", perval);

		m_pUptimeTable->GeDataTable()->elementAt(i6, 2)->setContentAlignment(AlignCenter);
		new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 2));
		//new WText(buf2, pRunTable->elementAt(i6, 1));

		m_pUptimeTable->GeDataTable()->elementAt(i6, 4)->setContentAlignment(AlignCenter);
		perval = dangernum*100/(normalnum + dangernum + errornum + othernum);
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
		xlsItem.dangerRunTime = perval;
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
		sprintf(buf2, "%d", perval);
		new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 4));
		//new WText(buf2, pRunTable->elementAt(i6, 2));
		
		m_pUptimeTable->GeDataTable()->elementAt(i6, 6)->setContentAlignment(AlignCenter);
		perval = errornum*100/(normalnum + dangernum + errornum + othernum);
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
		xlsItem.errorRunTime = perval;
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
		sprintf(buf2, "%d", perval);
		new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 6));
		//new WText(buf2, pRunTable->elementAt(i6, 3));
		
		m_pUptimeTable->GeDataTable()->elementAt(i6, 8)->setContentAlignment(AlignCenter);
		//列示最新记录的状态
		switch(laststat)
		{
		case 1:
			//new WText(m_formText.szNormal, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szNormal, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 2:
			//new WText(m_formText.szDanger, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szDanger, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 3:
			//new WText(m_formText.szError, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szError, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 4:
			//new WText(m_formText.szDisable, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szDisable, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 5:
			//new WText("BAD", pRunTable->elementAt(i6, 4));
			new WText("BAD", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 0:
			//new WText("NULL", pRunTable->elementAt(i6, 4));
			new WText("NULL", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		default:
			break;
		}
	}		

	//监测器返回值
	std::list<string> retliststr;
	std::list<string> retlisttype;
	OBJECT hTemplet;
	std::string monitorname;
	MAPNODE objNode;

	
	if(hMon != INVALID_VALUE)
	{			
		std::string getvalue;
		MAPNODE ma=GetMonitorMainAttribNode(hMon);
		
		//monitortemplet ID
		if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
		{						
			//monitortemplet 句柄
			hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
			MAPNODE node = GetMTMainAttribNode(hTemplet);
			//monitortemplet 标签
			FindNodeValue(node, "sv_label", monitorname);
			
			//报告设置是否显示阀值
			std::string szErrorValue;
			if(bClicket)
			{					
				MAPNODE errorNode = GetMTErrorAlertCondition(hTemplet);
				FindNodeValue(errorNode, "sv_value", szErrorValue);
				//new WText(szErrorValue.c_str(), pRunTable->elementAt(i6, 5));

				m_pUptimeTable->GeDataTable()->elementAt(i6, 10)->setContentAlignment(AlignCenter);
				new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 10));
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
	
		//monitortemplet返回值
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

			std::string returnimage = "";
			std::string returnstats = "";
			std::string returndata = "";

			std::string returnequally = "";

			//循环monitortemplet返回值
			string szDetail = GetIniFileString(reportname, "Parameter", "", "reportset.ini");
			while( (objNode = FindNext(item)) != INVALID_VALUE )
			{					
				FindNodeValue(objNode, "sv_label", fieldlabel);
				retliststr.push_back(fieldlabel);	
				FindNodeValue(objNode, "sv_type", fieldtype);				
				retlisttype.push_back(fieldtype);
				FindNodeValue(objNode, "sv_name", fieldname);
				fieldlabel = GetLabelResource(fieldlabel);
				
				//取监测器报告显示项
				FindNodeValue(objNode, "sv_drawimage", returnimage);
				FindNodeValue(objNode, "sv_drawtable", returnstats);
				FindNodeValue(objNode, "sv_drawmeasure", returndata);

				returnequally = "";
				bool bRet = false;
				bRet = FindNodeValue(objNode, "sv_equallyimage", returnequally);
				if(!bRet)
				{
					returnequally = "";
				}

				std::string szPrimary = "";
				FindNodeValue(objNode, "sv_primary",szPrimary);
				
				maxval = 0;//最大值
				perval = 0;//
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
				std::list<int>::iterator baditem;

				
				int count = 0;
				
				//清除 按类型存数据库中记录的intlist floatlist stringlist 数据
				intlist.clear();
				floatlist.clear();
				stringlist.clear();
				badlist.clear();


				//按字段取监测器记录队列
				GetMonitorDataRec(hRecSet, fieldname, fieldtype, intlist , floatlist, stringlist,badlist, timelist, maxval, minval, perval, lastval, reccount); 
				
				//如果不是主键值则不生成监测数据统计及图表				

				
				
				

				/***************************************************************
				数组赋值 floatlist（监测器为浮点型） intlist（监测器为整数型） 
				stringlist（监测器为字符串型） timeitem（时间数组）
				根据监测器返回值类型只能有一类数组有值
				****************************************************************/
				for(floatitem = floatlist.begin(), intitem = intlist.begin(), \
					stringitem = stringlist.begin(),timeitem = timelist.begin(), baditem = badlist.begin(); \
					(timeitem != timelist.end()); floatitem++, intitem++, stringitem++, timeitem++, baditem++)
				{
					//LIST中数据由当前时间往前，为图片显示必须做一下倒序
					TTime ctm = *timeitem;
					time[reccount - 1 - count] = Chart::chartTime(ctm.GetYear(), 
						ctm.GetMonth(), 
						ctm.GetDay(), 
						ctm.GetHour(),
						ctm.GetMinute(),
						ctm.GetSecond());

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
						std::string stringitemstr = *stringitem;
						data[reccount - 1 - count] = atof(stringitemstr.c_str());
					}		

					bdata[reccount - 1 - count ] = *baditem;
					count++;						
				}	
				
				//依据监测器是否使用排除异常算法
				if(strcmp(returnequally.c_str(), "1") == 0)
				{
					//计算误差去除异常值，原理：测量误差大于3倍均方根误差为异常值
					
					if(count > 100)
					{
						double lMaxVal = 0;
						double lMinVal = 0;

						float lCount = 0;
						float lAverage = 0;
						double lsCount = 0;
						double lsAverage = 0;
						for(int m = 0; m < count; m++)
						{
							lCount += data[m];						
						}
						lAverage = lCount / count;

						for(int m = 0; m < count; m++)
						{
							lsCount += (data[m] - lAverage)*(data[m] - lAverage);
						}
						
						lsAverage = sqrt(lsCount/(count - 1))*3;
						

						for(int m = 0; m < count; m++)
						{						
							if(fabs(data[m] - lAverage) > lsAverage)
							{
								OutputDebugString("----------异常值--------------\n");
								char buf[256];
								sprintf(buf, "%f", data[m]);
								OutputDebugString(buf);
								//为异常值
								for(int m1 = m; m1 < count - 1; m1++)
								{
									data[m1] = data[m1+1];								
								}
								m--;
								count--;
							}
							else
							{
								if(data[m] < lMinVal)
								{
									lMinVal = data[m];
								}

								if(data[m] > lMaxVal)
								{
									lMaxVal = data[m];
								}
							}
						}
						maxval = lMaxVal;
						minval = lMinVal;
						lCount = 0;
						for(int m = 0; m < count; m++)
						{
							lCount += data[m];
						}

						perval = lCount/count;
					}
				}
				//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
				xlsItem.max = maxval;
				xlsItem.avg = perval;
				xlsItem.measureName = fieldlabel;
				//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
					
				//判断是否显示监测的详细信息（reportset.ini中的KEY值为Parameter）
				if(strcmp(szDetail.c_str(), "Yes") == 0)
				{					
					WriteGenIni(reportname, starttime.Format(), endtime.Format(), value, fieldlabel, minval, perval, maxval);
				}
				else
				{				
					if(strcmp(szPrimary.c_str(), "1") == 0)
					{						
						//写reportgenerate.ini文件 在报告列表时取最大值、最小值、平均值
						WriteGenIni(reportname, starttime.Format(), endtime.Format(), value, fieldlabel, minval, perval, maxval);
					}
					else
					{
						//如果monitortemplete中sv_primary值不为1则返回循环
						continue;
					}
				}
				/*ClearException(data, count);
				double lMaxVal = 0;
				double lMinVal = data[0];
				double lCount = 0;

				for(int m = 0; m < count; m++)
				{
					if(data[m] < lMinVal)
					{
						lMinVal = data[m];
					}
					if(data[m] > lMaxVal)
					{
						lMaxVal = data[m];
					}
					lCount += data[m];
				}
				maxval = lMaxVal;
				minval = lMinVal;
				perval = lCount/count;
				*/
				std::string imgtabletitle;
				std::string hrefstring;
				//图形显示
				if(strcmp(returnimage.c_str(), "1") == 0)
				{
					//替换报告名中的特殊字符 : < > * ? | \\ /
					replace_all_distinct(reportname, " ", "_");
					replace_all_distinct(reportname, ":", "_");
					replace_all_distinct(reportname, "<", "_");
					replace_all_distinct(reportname, ">", "_");
					replace_all_distinct(reportname, "\\", "_");
					replace_all_distinct(reportname, "/", "_");
					replace_all_distinct(reportname, "*", "_");
					replace_all_distinct(reportname,"?", "_");
					replace_all_distinct(reportname,  "|", "_");

					std::string namebuf;//图片文件全路径
					std::string namebuf1;//构造图片文件路径临时string

					//取注册表中安装路径
					string	szRootPath = GetSiteViewRootPath();
					string szIconPath = szRootPath;
					
					szIconPath += "\\htdocs\\report\\Images\\";

					namebuf = szIconPath;					
	
					//图片路径格式： 开始时间+截止时间+报告名称 （空格 及 ： 由 _ 替换）
					std::string timestr = m_starttime.Format();
					timestr = replace_all_distinct(timestr, ":", "_");
					timestr = replace_all_distinct(timestr, " ", "_");
					namebuf1 = timestr;
					timestr = m_endtime.Format();
					timestr = replace_all_distinct(timestr, ":", "_");
					timestr = replace_all_distinct(timestr, " ", "_");
					namebuf1 += timestr;
											
					std::string namebuf3 = namebuf1;
					
					namebuf3 += reportname;
					namebuf3 += "\\";													

					//构造图片路径
					namebuf += namebuf3;						
					
					//判断图片路径是否存在，不存在则创建
					WIN32_FIND_DATA fd;
					HANDLE fr=::FindFirstFile(namebuf.c_str(),&fd);
					namebuf = replace_all_distinct(namebuf, "#", "_");
					if(!::FindNextFile(fr, &fd))
					{
						CreateDirectory(namebuf.c_str(), NULL);
					}

					namebuf1 += value;
					itoa(rand(), buf, 10);
					namebuf1 += buf;						
					namebuf1 += ".png";												

					//替换图片文件名字中的特殊字符 : < > * ? | \\ /
					replace_all_distinct(namebuf1, " ", "_");
					replace_all_distinct(namebuf1, ":", "_");
					replace_all_distinct(namebuf1, "<", "_");
					replace_all_distinct(namebuf1, ">", "_");
					replace_all_distinct(namebuf1, "*", "_");
					replace_all_distinct(namebuf1,"?", "_");
					replace_all_distinct(namebuf1,  "|", "_");
					replace_all_distinct(namebuf1, "\\", "_");
					replace_all_distinct(namebuf1, "/", "_");
					replace_all_distinct(namebuf1, "#", "_");

					//生成图片文件全路径
					namebuf += namebuf1;
											
					double cendtime =Chart::chartTime(endtime.GetYear(),
						endtime.GetMonth(),
						endtime.GetDay(), 
						endtime.GetHour(), 
						endtime.GetMinute(),
						endtime.GetSecond());
					
					//加上设备Entity
					imgtabletitle = entityvalue;
					imgtabletitle += ":";

					imgtabletitle += value;
					
					//设备名：监测器
					hrefstring = imgtabletitle;

					imgtabletitle += "(";
					imgtabletitle += fieldlabel;
					imgtabletitle += ")";						
					imgtabletitle += "\n";
					imgtabletitle += szMaxValue;
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", maxval);
					imgtabletitle += buf2;
					imgtabletitle += szAverageValue;
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", perval);
					imgtabletitle += buf2;
					imgtabletitle += szMinValue;
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", minval);
					imgtabletitle += buf2;											

					//返回
					std::string unitstr;
					FindNodeValue(objNode, "sv_unit", unitstr);
					
					//取回单位为(%)则最大值为100
					if(strcmp(unitstr.c_str(), "(%)") == 0)
					{							
						GenLineImage(data, bdata, time, count, NULL, 100, 10,\
							NULL, 0, 100, 20, count, cstarttime, cendtime,\
							(char*)imgtabletitle.c_str(),\
							(char*)fieldlabel.c_str(),\
							(char*)namebuf.c_str());
					}
					else
					{
						
						GenLineImage(data, bdata, time, count, NULL, 100, 10,\
							NULL, 0, maxval, 20, count, cstarttime, cendtime,\
							(char*)imgtabletitle.c_str(), \
							(char*)fieldlabel.c_str(),\
							(char*)namebuf.c_str());
					}
					
					//监测数据统计表跳转指向名称：监测器名（返回值）
					std::string temptitle = "<a name='" + hrefstring + "'>" + "</a>";						
					new WText(temptitle, (WContainerWidget*)pImageTable->elementAt(i3, 0));
																	
					std::string namebuf2 = "Images/";
					namebuf2 += namebuf3;
					namebuf2 += namebuf1;						

					//替换HTML中嵌入的图片名称中的特殊字符 : < > * ? |
					replace_all_distinct(namebuf2, ":", "_");
					replace_all_distinct(namebuf2, "<", "_");
					replace_all_distinct(namebuf2, ">", "_");
					replace_all_distinct(namebuf2, "*", "_");
					replace_all_distinct(namebuf2,"?", "_");
					replace_all_distinct(namebuf2,  "|", "_");		
					replace_all_distinct(namebuf2, "#", "_");
					
					new WImage(namebuf2, (WContainerWidget*)pImageTable->elementAt(i3, 0));												
					pImageTable->elementAt(i3, 0) ->setContentAlignment(AlignTop | AlignCenter);

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
						
						hrefstr += "'>";
						hrefstr += firstfield;
					
						hrefstr += "</a>";

						m_pMeasurementTable->InitRow(fieldnum);
						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0)->tablecellprop = " nowrap";
						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0)->setContentAlignment(AlignCenter);
						new WText(hrefstr, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0));
						//new WText(hrefstr, pMonitorTable->elementAt(fieldnum, 0));

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 2)->setContentAlignment(AlignCenter);
						new WText(fieldlabel, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 2));
						//new WText(fieldlabel, pMonitorTable->elementAt(fieldnum, 1));
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", maxval);

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 4)->setContentAlignment(AlignCenter);
						new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 4));
						//new WText(buf2, pMonitorTable->elementAt(fieldnum, 2));
						
						memset(buf2, 0, 256);					
						sprintf(buf2, "%0.0f", perval);

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 6)->setContentAlignment(AlignCenter);
						new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 6));
						//new WText(buf2, pMonitorTable->elementAt(fieldnum, 3));
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", lastval);

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 8)->setContentAlignment(AlignCenter);
						new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 8));
						//new WText(buf2, pMonitorTable->elementAt(fieldnum, 4));
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
				// ++++++ 在错误和报警列表的监测器名称前面附加设备名 ++++++
				// 2007/6/27 龚超

				std::string strMntName = entityvalue;
				strMntName += ":";
				strMntName += value;

				GetMonitorDataRecStr(hRecSet, strMntName, retmonnamelist1,
					retstatlist1, retstrlist1, rettimelist1);

				// ------ 在错误和报警列表的监测器名称前面附加设备名 ------

				/* // 在错误和报警列表的监测器名中没有包含设备名
				GetMonitorDataRecStr(hRecSet, value, retmonnamelist1, \
					retstatlist1, retstrlist1, rettimelist1);	
				*/
			}
		}		
	}						
	i6++;

	::getBoundName(hMon, xlsItem.bound);

	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
	xlsList.push_back(xlsItem);
	//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

	CloseRecordSet(hRecSet);	

	delete [] bdata;
}


//回调函数原型
typedef void(*func)(int , char **);

/***************************************************************************************************
参数:
	argc:参数个数
	argv:以空格分割的CHAR参数,
	格式:
	开始时间 截止时间 报告名称 HTML文件名 阀值 列出错误 列出危险 列出统计结果 列出图片
功能:
    传入WebSession的回调函数
***************************************************************************************************/
void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Total_Report",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
    //WApplication app(argc, argv);
    //app.setTitle("统计报告");
	CStatsReport * setform;

	if(argc > 3)
	{
		std::string timestr = argv[1];

		//分解开始时间串构造开始时间TTIME
		int pos = timestr.find("-", 0);
		std::string tempstr = timestr.substr(0, pos);
		int nYear = atoi(tempstr.c_str());
		int pos1 = timestr.find("-", pos+1);
		tempstr = timestr.substr(pos+1, pos1 - pos - 1 );
		int nMonth = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		int nDay = atoi(tempstr.c_str());		
		pos1 = timestr.find("_", pos + 1);
		tempstr = timestr.substr(pos + 1, pos1 - pos - 1);
		int nHour = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		int nMinute = atoi(tempstr.c_str());
		tempstr = timestr.substr(pos + 1, timestr.size() - pos);
		int nSecond = atoi(tempstr.c_str());

		chen::TTime starttime(nYear, nMonth, nDay, nHour, nMinute, nSecond);

		timestr = argv[2];
		//分解截止时间串构造截止时间TTIME
		pos = timestr.find("-", 0);
		tempstr = timestr.substr(0, pos);
		nYear = atoi(tempstr.c_str());
		pos1 = timestr.find("-", pos+1);
		tempstr = timestr.substr(pos+1, pos1 - pos - 1 );
		nMonth = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		nDay = atoi(tempstr.c_str());
		pos1 = timestr.find("_", pos + 1);
		tempstr = timestr.substr(pos + 1, pos1 - pos - 1);
		nHour = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		nMinute = atoi(tempstr.c_str());
		tempstr = timestr.substr(pos + 1, timestr.size() - pos);
		nSecond = atoi(tempstr.c_str());

		chen::TTime endtime(nYear, nMonth, nDay, nHour, nMinute, nSecond);

		bool bClicket = true ;
		bool bListError = true ;
		bool bListDanger = true ;
		bool bListStatsResult = true;
		bool bListImage = true;
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
		bool bGenExcel = true;
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
		string szGraphic = "";

		//阀值
		if(strcmp(argv[5], "Yes") == 0)
		{
			bClicket = true;
		}
		else
		{
			bClicket = false;
		}

		//列出错误
		if(strcmp(argv[6], "Yes") == 0)
		{
			bListError = true;
		}
		else
		{
			bListError = false;
		}

		//列出危险
		if(strcmp(argv[7], "Yes") == 0)
		{
			bListDanger = true;
		}
		else
		{
			bListDanger = false;
		}

		//列出统计结果
		if(strcmp(argv[8], "Yes") == 0)
		{
						
			bListStatsResult = true;
		}
		else
		{
			bListStatsResult = false;
		}

		//列出图表
		if(strcmp(argv[9], "Yes") == 0)
		{
			bListImage = true;
		}
		else
		{
			bListImage = false;
		}

		if(argv[10])
		{
			szGraphic = argv[10];
		}
		else
		{
			szGraphic = "";
		}

		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
		if(strcmp(argv[11], "Yes") == 0)
		{
			bGenExcel = true;
		}
		else
		{
			bGenExcel = false;
		}
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23

		//实例化统计报告
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
// 		setform = new CStatsReport(starttime, endtime, argv[3], \
// 			bClicket,bListError, bListDanger,bListStatsResult, bListImage, szGraphic, app.root());
		setform = new CStatsReport(starttime, endtime, argv[3], \
			bClicket,bListError, bListDanger,bListStatsResult, bListImage, szGraphic, bGenExcel, app.root());
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23		
	}
	else
	{
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改开始   苏合 2007-08-23
// 		setform = new CStatsReport(chen::TTime(2006, 8, 1, 0, 0, 0),\
// 			chen::TTime(2006, 8,16, 0, 0, 0),\
// 			"id=month_report",true, true, true, true, true, "", app.root());
		setform = new CStatsReport(chen::TTime(2006, 8, 1, 0, 0, 0),\
			chen::TTime(2006, 8,16, 0, 0, 0),\
			"id=month_report",true, true, true, true, true, "", false, app.root());
		//为解决Ticket #123(统计报告形式修改-江苏工行) 问题，修改代码。修改结束  苏合 2007-08-23
	}
    app.exec();
}

/***********************************************
主函数调用入口
***********************************************/
int main(int argc, char *argv[])
{
    func p = usermain;
	if (argc == 1) 
    {
        char buf[256];

		WebSession s("sds", false, true, "2006-7-21 2006-7-22month_report.html");
        s.start(p, argc, argv);
        return 1;
    }
    else if(argc > 3)
    {
		string szRootPath = GetSiteViewRootPath();
		szRootPath += "\\htdocs\\report\\";
        WebSession s("DEBUG", true, true, argv[4], szRootPath);
        s.start(p, argc, argv);
        return 1;
    }

    return 0;
}

