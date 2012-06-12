#include ".\timecontrastreport.h"
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

extern void PrintDebugString(const string &szMsg);

string& replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
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
CTimeContrastReport::CTimeContrastReport(svutil::TTime starttime, svutil::TTime endtime, std::string reportname, std::string templatename, int selectType,  bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent ):
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
			FindNodeValue(resourceNode,"IDS_Min_Value",m_formText.szMonLast);
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
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Page",strPage);
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Page_Count",strPageCount);
			FindNodeValue(resourceNode,"IDS_Alert_Log_Record_Count",strRecordCout);
		}
		//CloseResource(objResource);
	}
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

	replace_all_distinct(szXSLReportName, ":", "_");
	replace_all_distinct(szXSLReportName, " ", "_");
	replace_all_distinct(szXSLReportName, ".", "_");
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

	QUERY_TYPE type = BYDAY;
	switch(selectType)
	{
		case 0:
			{	
				OutputDebugString("按天\n");
				type = BYDAY;
				break;
			}
		case 1:
			{
				OutputDebugString("按周\n");
				type = BYWEEK;
				break;
			}
		case 2:
			{
				OutputDebugString("按月\n");
				type= BYMONTH;
				break;
			}
	}

	ShowMainTable(starttime, endtime, type, reportname, templatename, bClicket, bListError, bListDanger, bListStatsResult, bListImage);
}

//
CTimeContrastReport::~CTimeContrastReport(void)
{
	CloseResource(objResource);
}

void CTimeContrastReport::InitPageTable(WTable *mainTable, string title, svutil::TTime timepoint1, svutil::TTime timepoint2, QUERY_TYPE nType)
{
	szInterTime = "";
	if(nType == BYDAY)
	{
		TTime tmp(timepoint1.GetYear(),timepoint1.GetMonth(),timepoint1.GetDay(),0,0,0);
		TTimeSpan ts(0,23,59,59);
		TTime st1 = tmp;
		TTime et1 = tmp + ts;

		TTime tmp2(timepoint2.GetYear(),timepoint2.GetMonth(),timepoint2.GetDay(),0,0,0);
		TTime st2 = tmp2 ;
		TTime et2 = tmp2+ ts;
		szInterTime += "第一时间段：" + st1.Format() + " ~ " + et1.Format();
		szInterTime += "<br>第二时间段：" + st2.Format() + " ~ " + et2.Format();
	}else if(nType == BYWEEK)
	{
		int currentWeekDay1 = timepoint1.GetWeekDay();
		int currentWeekDay2 = timepoint2.GetWeekDay();
		TTimeSpan aweek(6, 23, 59, 59);
		TTimeSpan ts(currentWeekDay1, timepoint1.GetHour(), timepoint1.GetMinute(), timepoint1.GetSecond());
		TTime	start_timepoint1 = timepoint1 - ts;
		TTime tmp(start_timepoint1.GetYear(), start_timepoint1.GetMonth(), start_timepoint1.GetDay() + 7 , 0, 0 ,0);
		TTime end_timepoint1 = start_timepoint1 + aweek;

		TTimeSpan ts2(currentWeekDay2, timepoint2.GetHour(), timepoint2.GetMinute(), timepoint2.GetSecond());
		TTime start_timepoint2 = timepoint2 - ts2;
		TTime tmp2(start_timepoint2.GetYear(), start_timepoint2.GetMonth(), start_timepoint2.GetDay() + 7 , 0, 0 ,0);
		TTime end_timepoint2 = start_timepoint2 + aweek;
		szInterTime += "第一时间段：" + start_timepoint1.Format() + " ~ " + end_timepoint1.Format();
		szInterTime += "<br>第二时间段：" + start_timepoint2.Format() + " ~ " + end_timepoint2.Format();
	}else if(nType == BYMONTH)
	{
		TTime tmp(timepoint1.GetYear(), timepoint1.GetMonth(), 1, 0 , 0 , 0);
		TTime start_timepoint1 = tmp;
		TTime end_timepoint1 = tmp;
		TTimeSpan ts(0,0,0,1);
		if(timepoint1.GetMonth() >= 12)
		{
			TTime temp(timepoint1.GetYear() + 1, 1, 1 ,0 , 0, 0 );
			end_timepoint1 = temp - ts;
		}else
		{
			TTime temp(timepoint1.GetYear(), timepoint1.GetMonth() +1 , 1 ,0 ,0, 0);
			end_timepoint1 = temp - ts;
		}

		TTime tmp2(timepoint2.GetYear(), timepoint2.GetMonth(), 1, 0 , 0 , 0);
		TTime start_timepoint2 = tmp2;
		TTime end_timepoint2 = tmp2;
		if(timepoint2.GetMonth() >= 12)
		{
			TTime temp(timepoint2.GetYear() + 1, 1, 1 ,0 , 0, 0 );
			end_timepoint2 = temp - ts;
		}else
		{
			TTime temp(timepoint2.GetYear(), timepoint2.GetMonth() +1 , 1 ,0 ,0, 0);
			end_timepoint2 = temp - ts;
		}
		szInterTime += "第一时间段：" + start_timepoint1.Format() + " ~ " + end_timepoint1.Format();
		szInterTime += "<br>第二时间段：" + start_timepoint2.Format() + " ~ " + end_timepoint2.Format();
	}

	//New Version 
	pReportTitle = new WText(title+"<br>" + szInterTime, (WContainerWidget*)mainTable->elementAt(0, 0));
	mainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	pReportTitle->setStyleClass("textbold");
}

//
void CTimeContrastReport::ShowMainTable(svutil::TTime starttime, svutil::TTime endtime, QUERY_TYPE type, std::string reportname, std::string templatename, bool bClicket, bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage)
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

	string strReportTitle = GetDeviceTitle(reportname);
	strReportTitle += ":";
	strReportTitle += GetMonitorPropValue(reportname, "sv_name");

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this->elementAt(0,0));

	m_pListMainTable = new WTable(this->elementAt(0,0));
	
	InitPageTable(m_pListMainTable,strReportTitle, starttime, endtime, type);

	int reccount = 0;
			
	//int i1, i2;
	//char buf[256];
	//char buf1[256];		
	std::list<string>::iterator item;
	int i6 = 1;
	int i3 = 1;
	int fieldnum = 1;
	int gnormalnum = 1;
	int gdangernum = 1;
	int gerrornum = 1;
	int tcount = 0;

	GetMonitorRecord(reportname, templatename, starttime, endtime, type, bClicket, bListStatsResult, reportname, tcount, i6, i3, fieldnum);
}


//加列标题
void CTimeContrastReport::AddColum(WTable* pContain)
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
void CTimeContrastReport::AddListColumn()
{

}

//
void CTimeContrastReport::refresh()
{
	
}

//
void CTimeContrastReport::GenPieImage(char * szTitle, char * labels[], double data[], int len, char * filename)
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

//
void CTimeContrastReport::GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> &retmonnamelist, std::list<int> &retstatlist, std::list<string>& retstrlist, std::list<string>& rettimelist)
{
	LISTITEM item;
	RECORD hRec;
	
	FindRecordFirst(hRecSet, item);
			
	int stat;
	std::string str;

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		GetRecordDisplayString(hRec, stat, str);			
		TTime tm;
		GetRecordCreateTime(hRec,tm);
		if(stat == 1 || stat == 4)		
		{
			retnormalnamelist.push_back(monitorname);
			retnormaltimelist.push_back(tm.Format());
			retnormalstatuslist.push_back(str);		

		}
		if(stat == 2)
		{
			retdangernamelist.push_back(monitorname);
			retdangertimelist.push_back(tm.Format());
			retdangerstatuslist.push_back(str);
		}
		if(stat == 3 || stat == 5)
		{
			reterrornamelist.push_back(monitorname);
			reterrortimelist.push_back(tm.Format());
			reterrorstatuslist.push_back(str);
		}
	}	
}

//
void CTimeContrastReport::GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname,std::string fieldtype, std::list<int> & intlist, std::list<float> & floatlist, std::list<string> & stringlist,  std::list<TTime> & timelist, float & maxval, float & minval, float & perval, float & lastval, int & reccount)
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
		else if((stat != 0 && stat != 5) )//不为禁止状态
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

//
void CTimeContrastReport::GetMonitorGroup(char * reportname, std::list<string> & grouplist)
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
void CTimeContrastReport::InitPageItem(WTable *table, std::string title)
{
	pFrameTable = new WTable(this->elementAt(0,0));	

	pFrameTable ->setStyleClass("t5");
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

	text1 = new WText("图表", pContainTable->elementAt(6, 0));
	text1 -> decorationStyle().setFont(font1);
	pContainTable -> elementAt(6, 0) -> setContentAlignment(AlignTop | AlignCenter);

}

//
void CTimeContrastReport::WriteGenIni(std::string reportname, std::string starttime,std::string endtime,std::string value,std::string fieldlabel, float minval, float perval,float maxval)
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

std::string CTimeContrastReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( resourceNode != INVALID_VALUE )
		FindNodeValue(resourceNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
		strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

//
void CTimeContrastReport::GetMonitorRecord(std::string monitorid, std::string templatename, svutil::TTime starttime, svutil::TTime endtime, QUERY_TYPE nType, bool bClicket,bool bListStatsResult, std::string reportname, int &tcount, int & i6, int & i3, int & fieldnum)
{
	double data[50000];
	double time[50000];
	char buf[256];
	
	TTime start_timepoint1, end_timepoint1, start_timepoint2, end_timepoint2;
	if(nType == BYDAY)
	{
		OutputDebugString("进入按天查询!\n");
		TTime tmp(starttime.GetYear(),starttime.GetMonth(),starttime.GetDay(), 0 , 0 , 0);
		TTimeSpan ts( 0,23,59,59);
		start_timepoint1 = tmp ;
		end_timepoint1   = tmp + ts;

		TTime tmp2(endtime.GetYear(), endtime.GetMonth(), endtime.GetDay(), 0 ,0 ,0);
		start_timepoint2 = tmp2;
		end_timepoint2   = tmp2 +ts;
	}else if(nType == BYWEEK)
	{
		OutputDebugString("进入按周查询!\n");
		//当前是星期几
		int currentWeekDay1 = starttime.GetWeekDay();
		int currentWeekDay2 = endtime.GetWeekDay();

		TTimeSpan aweek(6 , 23, 59 , 59);
 
		TTimeSpan ts(currentWeekDay1, starttime.GetHour(), starttime.GetMinute(), starttime.GetSecond());
		start_timepoint1 = starttime - ts;
		TTime tmp(start_timepoint1.GetYear(), start_timepoint1.GetMonth(), start_timepoint1.GetDay() + 7 , 0, 0 ,0);
		end_timepoint1 = start_timepoint1 + aweek;

		TTimeSpan ts2(currentWeekDay2, endtime.GetHour(), endtime.GetMinute(), endtime.GetSecond());
		start_timepoint2 = endtime - ts2;
		TTime tmp2(start_timepoint2.GetYear(), start_timepoint2.GetMonth(), start_timepoint2.GetDay() + 7 , 0, 0 ,0);
		end_timepoint2 = start_timepoint2 + aweek;

	}else if(nType == BYMONTH)
	{
		OutputDebugString("进入按月查询!\n");
		TTime tmp(starttime.GetYear(), starttime.GetMonth(), 1, 0 , 0 , 0);
		start_timepoint1 = tmp;
		TTimeSpan ts(0,0,0,1);
		if(start_timepoint1.GetMonth() >= 12)
		{
			TTime temp(starttime.GetYear() + 1, 1, 1 ,0 , 0, 0 );
			end_timepoint1 = temp - ts;
		}else
		{
			TTime temp(starttime.GetYear(), starttime.GetMonth() +1 , 1 ,0 ,0, 0);
			end_timepoint1 = temp- ts;
		}
		
		TTime tmp2(endtime.GetYear(), endtime.GetMonth(), 1, 0 , 0 , 0);
		start_timepoint2 = tmp2;
		if(start_timepoint2.GetMonth() >= 12)
		{
			TTime temp(endtime.GetYear() + 1, 1, 1 ,0 , 0, 0 );
			end_timepoint2 = temp- ts;
		}else
		{
			TTime temp(endtime.GetYear(), endtime.GetMonth() +1 , 1 ,0 ,0, 0);
			end_timepoint2 = temp- ts;
		}
	}

	int index = 1;
	std::list<string> m1;
	m1.push_back(monitorid);
	m1.push_back(monitorid);
	std::list<string> monitorlist[2];
	monitorlist[0] = m1;

	for(int j = 0; j < index; j++)
	{	
		std::list<string>::iterator monitorlistitem;			
		XYChart *c = NULL;
		LineLayer *linelayer = NULL;
		LPSTR lpMultiByteStr;
		LPSTR lpMBStr[7];
		for(int i=0;i < 7; i++)
		{
			lpMBStr[i] = NULL;
		}
		std::string hrefstring;
		std::string namebuf3;
		std::string namebuf1;
		std::string namebuf;
	
		OBJECT hTemplet;									
		hTemplet = GetMonitorTemplet(atoi(templatename.c_str()));

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
				WSVFlexTable *pInsertTable = new WSVFlexTable(m_pListMainTable->elementAt(i3,0),List,fieldlabel);
				if (pInsertTable!= NULL)
				{
					pInsertTable->AppendColumn(strHNameLabel,WLength(39,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
					pInsertTable->AppendColumn(m_formText.szMonMax,WLength(17,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
					pInsertTable->AppendColumn(m_formText.szMonPer,WLength(17,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
					pInsertTable->AppendColumn(m_formText.szMonLast,WLength(35,WLength::Percentage));
					pInsertTable->SetDataRowStyle("table_data_grid_item_img");
				}

				gfieldnum = 0;
				int stypemon = 1;
				int msize = monitorlist[j].size(), index = 1;	//index用于计算是在哪个时段
                
				std::map<double, pair<double, double> > time_datalist;	//用于存放按周、月查询的天 -〉数据的对应数据
				string lstr ;
				string timepoint1Desc;	//监视器在图片上的描述文字
				string timepoint2Desc;

				////按星期查询需要使用的星期与日期的对应表
				YMD ymdlist[7];
				TTime ymdTime = start_timepoint1;
				for(int kk=0; kk< 7; kk++)	//init ymdlist，按照第一时间段里的每天与星期对应
				{
					TTimeSpan ts(1, 0 , 0 ,0);
					YMD ymd;
					ymd.year = ymdTime.GetYear(); ymd.month = ymdTime.GetMonth(); ymd.day = ymdTime.GetDay();
					ymdlist[kk] = ymd;
					ymdTime = ymdTime + ts;
				}
				
				std::map<int, pair<pair<double,int>, pair<double, int> > > dataList;
				double d1max = 0,d2max =0, d1avg = 0,d2avg =0, d1min =0,d2min =0;	//最大、最小、平均值				
				for(monitorlistitem = monitorlist[j].begin(); monitorlistitem != monitorlist[j].end(); monitorlistitem++)
				{
					count = 0;
					string monitorid = *monitorlistitem;
					OBJECT hMon = GetMonitor(monitorid);
					
					RECORDSET hRecSet;
					if(msize != index)
					{
						hRecSet = QueryRecords(monitorid, start_timepoint1, end_timepoint1);//取第一时间点的监测数据
					}
					else
					{
						hRecSet = QueryRecords(monitorid, start_timepoint2, end_timepoint2);//取第二时间点的监测数据
					}				

					//按字段取监测器记录队列
					reccount = 0;
					maxval = 0;
					minval = 0;
					perval = 0;
					lastval = 0;
					intlist.clear();
					floatlist.clear();
					stringlist.clear();
					timelist.clear();
					badlist.clear();
					
					try
					{
						GetMonitorDataRec(hRecSet, fieldname, fieldtype, intlist , floatlist, stringlist, \
							timelist, maxval, minval, perval, lastval, reccount); 												
					}
					catch(...)
					{
						continue;
					}					

					//使用自己的求平均值、最大值的方法
					//if(maxval > gmaxval)
					//{
					//	gmaxval = maxval;
					//}
					//if(gret)
					//{
					//	gminval = minval;
					//	gret = false;
					//}
					//else
					//{
					//	if(minval < gminval)
					//	{
					//		gminval = minval;
					//	}
					//}
					
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
						if(nType == BYDAY)
						{
							time[reccount - 1 - count] = Chart::chartTime(2007 , 1,\
								1, ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());
						}else if(nType == BYWEEK)
						{
							if(msize != index)
							{								
								time[reccount - 1 - count] = Chart::chartTime(ctm.GetYear(), ctm.GetMonth(),\
									ctm.GetDay(), ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());
							}else
							{
								int currentWeekDay = ctm.GetWeekDay();
								YMD ymd = ymdlist[currentWeekDay];
								time[reccount - 1 - count] = Chart::chartTime(ymd.year, ymd.month,\
								ymd.day,  ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());
							}
						}else if (nType == BYMONTH)
						{
							time[reccount - 1 - count] = Chart::chartTime(2007 , 1,\
								ctm.GetDay(),  ctm.GetHour(), ctm.GetMinute(), ctm.GetSecond());
						}

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

						if(nType == BYDAY)
						{
							int hour = ctm.GetHour();
							std::map<int, pair<pair<double,int>, pair<double, int> > >::iterator item = dataList.find(hour);
							
							if(msize != index)
							{
                                if(item == dataList.end())
								{	
									dataList[hour] = make_pair(make_pair(data[reccount - 1 - count],1),make_pair(0,1));
								}else
								{
									data[reccount - 1 - count] = data[reccount - 1 - count] + item->second.first.first;
									dataList[hour] = make_pair(make_pair(data[reccount - 1 - count], 1),make_pair(0,1));
								}
							}else
							{								
								double d1 = item->second.first.first;
								if(item == dataList.end())
								{	
									dataList[hour] = make_pair(make_pair(d1,1),make_pair(data[reccount - 1 - count],1));
								}else
								{
									data[reccount - 1 - count] = data[reccount - 1 - count] + item->second.second.first;
									dataList[hour] = make_pair(make_pair(d1, 1),make_pair(data[reccount - 1 - count],1));
								}
							}
						}else
						{			
							map<double,pair<double,double> >::iterator it = time_datalist.find(time[reccount-1-count]);
							if(it != time_datalist.end())		//已经在hash表里存在了
							{
								time_datalist[time[reccount - 1 - count]] = make_pair(it->second.first,data[reccount - 1 - count]);
							}else
							{
								if(msize != index)		//第一次新增节点
									time_datalist[time[reccount - 1 - count]] = make_pair(data[reccount - 1 - count], 0);
								else					//第二次新增节点
									time_datalist[time[reccount - 1 - count]] = make_pair(0,data[reccount - 1 - count]);
							}			
						}
						count++;		
					}

					std::string imgtabletitle;
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

						lstr = entityvalue;
						lstr += ":";
						lstr += smonitorname;
						pInsertTable->InitRow(stypemon);

						if(msize != index)
						{
							lstr += " (" + start_timepoint1.Format() + " ~ " + end_timepoint1.Format() + ")";
							timepoint1Desc = lstr;
						}else
						{
							lstr += " (" + start_timepoint2.Format() + " ~ " + end_timepoint2.Format() + ")";
							timepoint2Desc = lstr;
						}
						new WText(lstr, pInsertTable->GeDataTable()->elementAt(stypemon, 0));
					
						stypemon++;		
					}			
					CloseMonitor(hMon);
					CloseRecordSet(hRecSet);
					idnum++;
					index++;
				}
				//测试

				//这里画图
				int kkindex = 0;

				bool first = true;	//用于计算平均值、最大值、最小值

				if(nType != BYDAY)	//只有按月、按周的计算才需要对time_dataList进行处理得到dataList，按天已经得到了dataList
				{
					for(map<double, pair<double, double> >::iterator iter = time_datalist.begin(); iter != time_datalist.end(); iter++)
					{
						if(nType == BYWEEK)
						{
							int week = Chart::getChartWeekDay(iter->first);
							double d1 = iter->second.first;
							double d2 = iter->second.second;						
							std::map<int, pair<pair<double,int>, pair<double, int> > >::iterator item = dataList.find(week);
							if(item == dataList.end())
							{	
								dataList[week] = make_pair(make_pair(d1,1),make_pair(d2,1));
							}else
							{
								d1 = d1 + item->second.first.first;
								d2 = d2 + item->second.second.first;
								dataList[week] = make_pair(make_pair(d1, 1),make_pair(d2,1));
							}
							kkindex++;
						}else if(nType == BYMONTH)
						{
							int ymd = Chart::getChartYMD(iter->first);
							double d1 = iter->second.first;
							double d2 = iter->second.second;						
							std::map<int, pair<pair<double,int>, pair<double, int> > >::iterator item = dataList.find(ymd);
							if(item == dataList.end())
							{	
								dataList[ymd] = make_pair(make_pair(d1,1),make_pair(d2,1));
							}else
							{
								d1 = d1 + item->second.first.first;
								d2 = d2 + item->second.second.first;
								dataList[ymd] = make_pair(make_pair(d1, 1),make_pair(d2,1));
							}	
							kkindex++;
						}
					}
				}
				
				//根据得到的dataList数据画图
				if(nType == BYDAY)
				{				
					double atime[24], adata[24], bdata[24];
					bool first = true;
					for(int kk=1; kk<=24;kk++)
					{
						atime[kk-1] = Chart::chartTime(2007,1,1,kk-1,0,0);
						unsigned long recCount1 =(unsigned long) FindCount2(monitorid,start_timepoint1,end_timepoint1,kk-1);
						unsigned long recCount2 = (unsigned long) FindCount2(monitorid,start_timepoint2,end_timepoint2,kk-1);
						std::map<int, pair<pair<double,int>, pair<double, int> > >::iterator item = dataList.find(kk-1);
						if(item != dataList.end())
						{	
							if(recCount1 != 0)
								adata[kk-1] = (double)(item->second.first.first / recCount1);
							else
								adata[kk-1] = 0;
							if(recCount2  != 0)
								bdata[kk-1] = (double)(item->second.second.first / recCount2);	
							else 
								bdata[kk-1] = 0;	
						}else
						{
							adata[kk-1] = 0.0;
							bdata[kk-1] = 0.0;
						}
						if(first)
						{
							d1max = adata[kk-1];
							d2max = bdata[kk-1];
							d1min = adata[kk-1];
							d2min = bdata[kk-1];
							first = false;
						}else
						{
							if(adata[kk-1] > d1max)
								d1max = adata[kk-1];
							if(bdata[kk-1] > d2max)
								d2max = bdata[kk-1];
							if(adata[kk-1] < d1min)
								d1min = adata[kk-1];
							if(bdata[kk-1] < d2min)
								d2min = bdata[kk-1];
						}
						d1avg = d1avg + adata[kk-1];
						d2avg = d2avg + bdata[kk-1];  						
					}
					int i = 24;
					d1avg = d1avg / i;
					d2avg = d2avg / i;
					int ctitle = monitorlist[j].size();
					c = StartGenLineImage(atime, i, &linelayer, lpMultiByteStr, NULL, 100, 10, NULL, 0, 100, 20, i, 0, 0,(char*)fieldlabel.c_str(), (char*)fieldlabel.c_str(), ctitle, lpMBStr, nType);
					GenLineImage(adata, atime, i, linelayer, color,(char*) timepoint1Desc.c_str());
					color = 0xff0000; 						
					GenLineImage(bdata,  atime, i, linelayer, color, (char*)timepoint2Desc.c_str());	
				}else if(nType == BYWEEK)
				{
					double atime[7], adata[7], bdata[7];
					bool first = true;
					for(int kk=0; kk<7;kk++)
					{
						atime[kk] = Chart::chartTime(2007,7,kk+1,0,0,0);
						int week = Chart::getChartWeekDay(atime[kk]);
						unsigned long recCount1 =(unsigned long) FindCount(monitorid,start_timepoint1,end_timepoint1,week);
						unsigned long recCount2 = (unsigned long) FindCount(monitorid,start_timepoint2,end_timepoint2,week);
						std::map<int, pair<pair<double,int>, pair<double, int> > >::iterator item = dataList.find(week);
						if(item != dataList.end())
						{	
							if(recCount1 != 0)
								adata[kk] = (double)(item->second.first.first / recCount1);
							else
								adata[kk] = 0;
							if(recCount2  != 0)
								bdata[kk] = (double)(item->second.second.first / recCount2);	
							else 
								bdata[kk] = 0;	
						}else
						{
							adata[kk] = 0.0;
							bdata[kk] = 0.0;
						}
						if(first)
						{
							d1max = adata[kk];
							d2max = bdata[kk];
							d1min = adata[kk];
							d2min = bdata[kk];
							first = false;
						}else
						{
							if(adata[kk] > d1max)
								d1max = adata[kk];
							if(bdata[kk] > d2max)
								d2max = bdata[kk];
							if(adata[kk] < d1min)
								d1min = adata[kk];
							if(bdata[kk] < d2min)
								d2min = bdata[kk];
						}
						d1avg = d1avg + adata[kk];
						d2avg = d2avg + bdata[kk];  
					}
					int i = 7;
					d1avg = d1avg / i;
					d2avg = d2avg / i;
					int ctitle = monitorlist[j].size();					
					c = StartGenLineImage(atime, i, &linelayer, lpMultiByteStr, NULL, 100, 10, NULL, 0, 100, 20, i, 0, 0,(char*)fieldlabel.c_str(), (char*)fieldlabel.c_str(), ctitle, lpMBStr, nType);
					GenLineImage(adata, atime, i, linelayer, color,(char*) timepoint1Desc.c_str());
					color = 0xff0000; 						
					GenLineImage(bdata,  atime, i, linelayer, color, (char*)timepoint2Desc.c_str());	
				}else if(nType == BYMONTH)
				{
					double atime[31], adata[31], bdata[31];
					bool first = true;
					for(int kk = 1; kk<=31; kk++)
					{
						atime[kk-1] = Chart::chartTime(2007,1,kk,0,0,0);
						int ymd = Chart::getChartYMD(atime[kk-1]);
						unsigned long recCount1 =(unsigned long) FindCount(monitorid,start_timepoint1,end_timepoint1,kk-1);
						unsigned long recCount2 = (unsigned long) FindCount(monitorid,start_timepoint2,end_timepoint2,kk-1);
						std::map<int, pair<pair<double,int>, pair<double, int> > >::iterator item = dataList.find(ymd);
						if(item != dataList.end())
						{		
							if(recCount1 != 0)
								adata[kk-1] = (double)(item->second.first.first / recCount1);
							else
								adata[kk-1] = 0;
							if(recCount2  != 0)
								bdata[kk-1] = (double)(item->second.second.first / recCount2);	
							else 
								bdata[kk-1] = 0;	
						}else
						{
							adata[kk-1] = 0.0;
							bdata[kk-1] = 0.0;
						}						
						if(first)
						{
							d1max = adata[kk-1];
							d2max = bdata[kk-1];
							d1min = adata[kk-1];
							d2min = bdata[kk-1];
							first = false;
						}else
						{
							if(adata[kk-1] > d1max)
								d1max = adata[kk-1];
							if(bdata[kk-1] > d2max)
								d2max = bdata[kk-1];
							if(adata[kk-1] < d1min)
								d1min = adata[kk-1];
							if(bdata[kk-1] < d2min)
								d2min = bdata[kk-1];
						}
						d1avg = d1avg + adata[kk-1];
						d2avg = d2avg + bdata[kk-1];  
					}
					int i = 31;
					d1avg = d1avg /i;
					d2avg = d2avg /i;
					int ctitle = monitorlist[j].size();					
					c = StartGenLineImage(atime, i, &linelayer, lpMultiByteStr, NULL, 100, 10, NULL, 0, 100, 20, i, 0, 0,(char*)fieldlabel.c_str(), (char*)fieldlabel.c_str(), ctitle, lpMBStr, nType);
					GenLineImage(adata, atime, i, linelayer, color,(char*) timepoint1Desc.c_str());
					color = 0xff0000; 						
					GenLineImage(bdata,  atime, i, linelayer, color, (char*)timepoint2Desc.c_str());
				}	
				
				std::string namebuf2 = "../report/icons/";
				namebuf2 += namebuf3;
				namebuf2 += "/";
				namebuf2 += namebuf1;

				OutputDebugString(namebuf2.c_str());
				OutputDebugString("\n");

				if(c)
				{
					char buf2[256];
					string imgtabletitle = fieldlabel;	
					imgtabletitle += "\n";
					imgtabletitle += "最大值:";
					imgtabletitle += ":";
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f / %0.0f\t", d1max, d2max);
					
					imgtabletitle += buf2;
					imgtabletitle += "平均值:";
					imgtabletitle += ":";
					memset(buf2, 0, 256);
					float perval1 = (gcountval/idnum);
					sprintf(buf2, "%0.0f / %0.0f\t", d1avg, d2avg);

					imgtabletitle += buf2;
					imgtabletitle += "最小值:";
					imgtabletitle += ":";
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f / %0.0f", d1min, d2min);
					imgtabletitle += buf2;

					char tableElement[256];
					memset(tableElement,0,256);
					sprintf(tableElement,"%0.0f",d1max);
					new WText(tableElement, pInsertTable->GeDataTable()->elementAt(1, 2));
					memset(tableElement, 0, 256);
					sprintf(tableElement,"%0.0f",d2max);
					new WText(tableElement, pInsertTable->GeDataTable()->elementAt(2, 2));
					memset(tableElement,0,256);
					sprintf(tableElement,"%0.0f",d1avg);
					new WText(tableElement, pInsertTable->GeDataTable()->elementAt(1, 4));
					memset(tableElement, 0, 256);
					sprintf(tableElement,"%0.0f",d2avg);
					new WText(tableElement, pInsertTable->GeDataTable()->elementAt(2, 4));
					memset(tableElement,0,256);
					sprintf(tableElement,"%0.0f",d1min);
					new WText(tableElement, pInsertTable->GeDataTable()->elementAt(1, 6));
					memset(tableElement, 0, 256);
					sprintf(tableElement,"%0.0f",d2min);
					new WText(tableElement, pInsertTable->GeDataTable()->elementAt(2, 6));
				
					wchar_t lpWide[256];					
					LPCWSTR lpWideCharStr =L"";
					int slen = 256;
					int wlen = 256;
					lpMultiByteStr= (LPSTR)malloc(256);
					memset(lpMultiByteStr, 0, 256);					
					setlocale(LC_CTYPE, ""); 
					memset(lpWide, 0, 256);
					mbstowcs(lpWide, imgtabletitle.c_str(), 256);
					WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
					(c)->addTitle(lpMultiByteStr,
					"mingliu.ttc", 9, 0x0000ff);
					free(lpMultiByteStr);
					EndGenLineImage(c, lpMultiByteStr, (char*)namebuf.c_str());
					//释放星期的几个中文内存
					for(int i=0;i < 7; i++)
					{
						if(lpMBStr[i] != NULL)
							free(lpMBStr[i]);
					}

					WSVFlexTable* pImageTable = new WSVFlexTable(m_pListMainTable->elementAt(i3+1,0),Blank,"");										
					new WImage(namebuf2, (WContainerWidget*)pImageTable->GetContentTable()->elementAt(0, 1));					
					pImageTable->GetContentTable()->elementAt(0, 1) ->setContentAlignment(AlignTop | AlignCenter);	
					i3++;				
				}
			}				
		}		
		CloseMonitorTemplet(hTemplet);
	}			
}

//
void CTimeContrastReport::AddDataColum(WTable* pContain)
{
	new WText(strHNameLabel, pContain->elementAt(0, 0));
	new WText(strHTimeLabel, pContain->elementAt(0, 1));
	new WText(strHDataLabel, pContain->elementAt(0, 2));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}

//
void CTimeContrastReport::AddDataItem(string strName, string strTime, string strData)
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
void CTimeContrastReport::AddDataItemNew(string strName, string strTime, string strData, int numRow)
{
	//生成界面
	m_pDataTable->InitRow(numRow);

	WText * pTmpText;
	
	pTmpText = new WText(strName, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 0));

	m_pDataTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
	pTmpText = new WText(strTime, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 2));
	
	pTmpText = new WText(strData, (WContainerWidget*)m_pDataTable->GeDataTable()->elementAt(numRow , 4));

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
XYChart * CTimeContrastReport::StartGenLineImage(double data[], 
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
											 int ctitle,
											 LPSTR *lpMBStr,
											 QUERY_TYPE nType)
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
	setlocale(LC_CTYPE, ""); 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, Title, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
	memset(lpMultiByteStr, 0, 256);
		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

    (c)->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	lpWideCharStr = L"Copyright SiteView";

	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);
	(c)->xAxis()->setTitle(lpMultiByteStr, "mingliu.ttc", 8, 0x000000ff);	
	if(nType == BYDAY)
	{
		(c)->xAxis()->setLabelFormat("{value|hh:mm:ss}");
	}else if(nType == BYWEEK)
	{
		LPTSTR data[7];
		LPCWSTR lpWideCharStr1 = L"星期日";
		lpMBStr[0] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr1, slen, lpMBStr[0], wlen, NULL, NULL);
		data[0] = lpMBStr[0];
		
		LPCWSTR lpWideCharStr2 = L"星期一";
		lpMBStr[1] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr2, slen, lpMBStr[1], wlen, NULL, NULL);
		data[1] = lpMBStr[1];

		LPCWSTR lpWideCharStr3 = L"星期二";
		lpMBStr[2] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr3, slen, lpMBStr[2], wlen, NULL, NULL);
		data[2] = lpMBStr[2];

		LPCWSTR lpWideCharStr4 = L"星期三";
		lpMBStr[3] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr4, slen, lpMBStr[3], wlen, NULL, NULL);
		data[3] = lpMBStr[3];

		LPCWSTR lpWideCharStr5 = L"星期四";
		lpMBStr[4] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr5, slen, lpMBStr[4], wlen, NULL, NULL);
		data[4] = lpMBStr[4];

		LPCWSTR lpWideCharStr6 = L"星期五";
		lpMBStr[5] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr6, slen, lpMBStr[5], wlen, NULL, NULL);
		data[5] = lpMBStr[5];

		LPCWSTR lpWideCharStr7 = L"星期六";
		lpMBStr[6] = (LPSTR)malloc(256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr7, slen, lpMBStr[6], wlen, NULL, NULL);
		data[6] = lpMBStr[6];

		StringArray names;
		names.len = 7;
		names.data = data;
		(c)->setWeekDayNames(names);
		(c)->xAxis()->setLabelFormat("{value|w}");
		(c)->xAxis()->setLabelStyle("mingliu.TTC", 8, 0x000000ff);
	}else if(nType == BYMONTH)
	{
		(c)->xAxis()->setLabelFormat("{value|dd}");
	}
	(c)->xAxis()->setLabelStep(3);
	c->addLegend(55, 36, true, "mingliu.ttc");
	*linelayer = (c)->addLineLayer();
	(*linelayer)->setXData(DoubleArray(data, len));
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
void CTimeContrastReport::EndGenLineImage(XYChart *c,
									  LPSTR lpMultiByteStr,
									  char * filename)
{	
	c->makeChart(filename);	
	//(c)->addTitle(lpMultiByteStr,
	//	"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

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
void CTimeContrastReport::GenLineImage(double data[],
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
		setlocale(LC_CTYPE, ""); 

		memset(lpWide, 0, 256);
		mbstowcs(lpWide, name, 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);		
		linelayer->addDataSet(DoubleArray(data, len), -1, lpMultiByteStr);
		if(lpMultiByteStr)
		{
			free(lpMultiByteStr);
		}
	
}

size_t CTimeContrastReport::FindCount(string monitorid, TTime &start, TTime &stop, int week)
{

	TTimeSpan ts(week,23,59,59);
	TTime stoptime = start + ts;
	TTime starttime(stoptime.GetYear(),stoptime.GetMonth(),stoptime.GetDay(),0,0,0);

	size_t recCount = 0;
	OBJECT hMon = GetMonitor(monitorid);
    RECORDSET hrSet = QueryRecords(monitorid,starttime,stoptime);
	GetRecordCount(hrSet, recCount);
	CloseMonitor(hMon);
	CloseRecordSet(hrSet);
	return recCount;
}

size_t CTimeContrastReport::FindCount2(string monitorid, TTime &start, TTime &stop, int hour)
{

	TTimeSpan ts(0,hour,59,59);
	TTime stoptime = start + ts;
	TTime starttime(stoptime.GetYear(),stoptime.GetMonth(),stoptime.GetDay(),stoptime.GetHour(),0,0);

	size_t recCount = 0;
	OBJECT hMon = GetMonitor(monitorid);
    RECORDSET hrSet = QueryRecords(monitorid,starttime,stoptime);
	GetRecordCount(hrSet, recCount);
	CloseMonitor(hMon);
	CloseRecordSet(hrSet);
	return recCount;
}

