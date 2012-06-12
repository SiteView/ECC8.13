/*
 *  HZDLReport.cpp
 *
 *  Modified on 2007-10-05 By 苏合
 *     1、在报表中加入IP(或机器名)的数据
 *
 */
#include ".\hzdlreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"
#include "svdbapi.h"
#include "..\..\base\stlini.h"
#include "CSpreadSheet.h"

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

string& replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

bool findString(string source, string toSearch)
{
	bool bRet = false;
	basic_string <char>::size_type indexStr;
	static const basic_string <char>::size_type npos = -1;

	indexStr = source.find(toSearch);
	if (indexStr != npos) bRet = true;

	return bRet;
}

CHZDLReport::CHZDLReport(TTime starttime, TTime endtime, WContainerWidget *parent):
	WTable(parent)
{
	m_starttime = starttime;
	m_endtime = endtime;

	//生成xml文件的名字
	szXSLReportName = "HZDL";
	szXSLReportName += starttime.Format();
	szXSLReportName += endtime.Format();
	replace_all_distinct(szXSLReportName, ":", "");
	replace_all_distinct(szXSLReportName, " ", "");
	replace_all_distinct(szXSLReportName, ".", "");
	replace_all_distinct(szXSLReportName, "-", "");
	replace_all_distinct(szXSLReportName, "\\", "");
	replace_all_distinct(szXSLReportName, "/", "");
	szXSLReportName += ".xls";

	initForm();
}

void CHZDLReport::addData(WSVFlexTable * pParentTable)
{
	int iRow=1;
	list<DeviceItem>::iterator RecordItem;
	char buf[256];
	memset(buf, 0, 256);

	for(RecordItem=DeviceList.begin(); RecordItem != DeviceList.end(); RecordItem++)
	{
		pParentTable->InitRow(iRow);
		int iColNum = 1;
		new WText(RecordItem->sName, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;

		new WText(RecordItem->sIP, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;

		if (RecordItem->hasCPU) sprintf(buf, "%0.0f", RecordItem->CPUUtilization);
		else sprintf(buf, "%s", "无数据");
		new WText(buf, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;

		memset(buf, 0, 256);
		if (RecordItem->hasMemory) sprintf(buf, "%0.0f", RecordItem->MemoryUtilization);
		else sprintf(buf, "%s", "无数据");
		new WText(buf, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		
		iRow++;
	}
}

void CHZDLReport::initForm()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this->elementAt(0,0));

	m_pListMainTable = new WTable(this->elementAt(0,0));

	string szInterTime = "时间段 ";
	szInterTime += m_starttime.Format();
	szInterTime += "~";
	szInterTime += m_endtime.Format();

	InitPageTable(m_pListMainTable, szInterTime);
	GenList();
	addData(m_pDataTable);
}

void CHZDLReport::InitPageTable(WTable *mainTable, string title)
{
	//New Version 
	pReportTitle = new WText(title, (WContainerWidget*)mainTable->elementAt(0, 0));
	mainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	pReportTitle->setStyleClass("textbold");
	new WText("<br>", (WContainerWidget*)mainTable->elementAt(0, 0));

	m_pDataTable = new WSVFlexTable(mainTable->elementAt(1,0), List ,"CPU、内存 统计报表");

	if (m_pDataTable->GetContentTable() != NULL)
	{
		m_pDataTable->AppendColumn("",WLength(2,WLength::Pixel));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_img");

		m_pDataTable->AppendColumn("设备名称", WLength(40,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");

		m_pDataTable->AppendColumn("IP/机器名", WLength(20,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");

		m_pDataTable->AppendColumn("CPU平均利用率(%)", WLength(20,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");

		m_pDataTable->AppendColumn("内存平均利用率(%)", WLength(20,WLength::Percentage));
		m_pDataTable->SetDataRowStyle("table_data_grid_item_text");
	}

	mainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
	pDataCmdTable = new WTable(mainTable->elementAt(2,0));
	pDataCmdTable->setStyleClass("widthauto");


	//保存为EXCEL文件
	WSVButton *pSaveExcel = new WSVButton(pDataCmdTable->elementAt(0,1), "生成Excel表", "button_bg_m.png", "", false);

	connect(pSaveExcel, SIGNAL(clicked()), this, SLOT(SaveExcelBtn()));	
}

CHZDLReport::~CHZDLReport(void)
{
}

void CHZDLReport::GenList()
{
	DeviceList.clear();
	PAIRLIST getDevList;
	PAIRLIST::iterator getDevItem;
	
	DeviceItem  tmpDevItem;
		
	float tmpCPUUtilization = 0;
	float tmpMemoryUtilization = 0;
	bool tmpCPU = false;
	bool tmpMemory = false;
	tmpDevItem.sIP = "无IP";
	
	if(GetAllEntitysInfo(getDevList, "sv_name"))
	{
		for(getDevItem = getDevList.begin(); getDevItem != getDevList.end(); getDevItem++)
		{
			tmpDevItem.sName  = getDevItem->value;

			GetData(getDevItem->name, tmpDevItem.sIP, tmpCPU, tmpMemory, tmpCPUUtilization, tmpMemoryUtilization);
			if (tmpCPU || tmpMemory)
			{
				tmpDevItem.hasCPU = tmpCPU;
				tmpDevItem.hasMemory = tmpMemory;
				tmpDevItem.CPUUtilization = tmpCPUUtilization;
				tmpDevItem.MemoryUtilization = tmpMemoryUtilization;
				DeviceList.push_back(tmpDevItem);
			}
		}
		getDevList.clear();		
	}
}

void CHZDLReport::GetData(string deviceName, string & sIP, bool & useCPU, bool & useMemory, float & CPUUtl, float & MemoryUtl)
{
	list<string> getMonList;
	list<string>::iterator getMonItem;
	string MonitorID;

	OBJECT tmpObjMonitor = NULL;
	OBJECT tmpObjTempMonitor = NULL;
	MAPNODE tmpMonitorNode = NULL;
	MAPNODE tmpMonitorTempNode = NULL;
	MAPNODE tempParamNode = NULL;
	LISTITEM ParamItem;
	bool bFind;
	string tmpMonitorTempName;

	useCPU = false;
	useMemory = false;
	CPUUtl = 0;
	MemoryUtl = 0;

	bFind = GetSubMonitorsIDByEntity(GetEntity(deviceName), getMonList);
	if (!bFind) return;

	MAPNODE tmpEntityNode = NULL;
	tmpEntityNode = GetEntityMainAttribNode(GetEntity(deviceName));
	string v;
	bFind = FindNodeValue(tmpEntityNode, "_MachineName", v);
	if (bFind)
	{
		sIP = v;
	}

	getMonItem = getMonList.begin();
	
	while ( (getMonItem != getMonList.end()) && ( (!useCPU) || (!useMemory) ) )
	{
		MonitorID = *getMonItem;
		tmpObjMonitor = GetMonitor(MonitorID);
		if (tmpObjMonitor != INVALID_VALUE)
		{
			tmpMonitorNode = GetMonitorMainAttribNode(tmpObjMonitor);
			string TypeID;
			bFind = FindNodeValue(tmpMonitorNode, "sv_monitortype", TypeID);
			int iType = atoi(TypeID.c_str());
			tmpObjTempMonitor = GetMonitorTemplet(iType);
			if(tmpObjTempMonitor!=INVALID_VALUE)
			{
				tmpMonitorTempNode = GetMTMainAttribNode(tmpObjTempMonitor);	
				bFind = FindNodeValue(tmpMonitorTempNode, "sv_name", tmpMonitorTempName);

				if (!useCPU)
				{
					string stmp1 = "CPU";
					string stmp2 = "Cpu";
					string stmp3 = "cpu";
					if ( findString(tmpMonitorTempName, stmp1) || findString(tmpMonitorTempName, stmp2) || findString(tmpMonitorTempName, stmp3) )
					{
						bFind = FindMTReturnFirst(tmpObjTempMonitor, ParamItem);
						bool findPrimary = false;
						while( ((tempParamNode=::FindNext(ParamItem)) != INVALID_VALUE) && !findPrimary )
						{ 
							string szPrimary;
							FindNodeValue(tempParamNode, "sv_primary",szPrimary);
							if(strcmp(szPrimary.c_str(), "1") == 0)
							{
								findPrimary = true;
								string tmpFieldName;
								FindNodeValue(tempParamNode, "sv_name", tmpFieldName);
								CPUUtl = CalcAverage(MonitorID, tmpFieldName);
							}
						}
						useCPU = true;
					}
				} 
				if (!useMemory)
				{
					string stmp = "Memory";
					if ( findString(tmpMonitorTempName, stmp) )
					{
						bFind = FindMTReturnFirst(tmpObjTempMonitor, ParamItem);
						bool findPrimary = false;
						while( ((tempParamNode=::FindNext(ParamItem)) != INVALID_VALUE) && !findPrimary )
						{ 
							string szPrimary;
							FindNodeValue(tempParamNode, "sv_primary",szPrimary);
							if(strcmp(szPrimary.c_str(), "1") == 0)
							{
								findPrimary = true;
								string tmpFieldName;
								FindNodeValue(tempParamNode, "sv_name", tmpFieldName);
								MemoryUtl = CalcAverage(MonitorID, tmpFieldName);
							}
						}
						useMemory = true;
					}
				}
			}	
		}
		getMonItem++;
	}
}

float CHZDLReport::CalcAverage(string monitorID, string fieldName)
{
	LISTITEM item;
	RECORD hRec;
	float Ret = 0.0;
	float countval = 0.0;
	int nCount = 0;
	int nState = 0;  //记录状态
	float recValue = 0.0;

	int iv = 0;
	string sv;

	RECORDSET hRecSet = QueryRecords(monitorID, m_starttime, m_endtime);
	FindRecordFirst(hRecSet, item);
	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{
		int nTmpType = 2;
		GetRecordValueByField(hRec, fieldName, nTmpType, nState, iv, recValue, sv);
		switch(nState)
		{
		case STATUS_OK:
		case STATUS_WARNING:
		case STATUS_ERROR:
			countval += recValue;
			nCount++;
		    break;
		case STATUS_DISABLE:
		case STATUS_BAD:
		case STATUS_NULL:
		    break;
		default:
		    break;
		}
	}
	if (nCount != 0) Ret = countval / nCount;

	return Ret;
}

void CHZDLReport::SaveExcelBtn()
{
	OutputDebugString("\n----------ExportExcel Begin-------------\n");
	std::string szFilePath =GetSiteViewRootPath();
	szFilePath += "\\htdocs\\";	
	szFilePath += szXSLReportName;

	CSpreadSheet SS(szFilePath.c_str(), "统计报表");

	CStringArray headerArray, contentArray;

	SS.BeginTransaction();

	// 加入标题
	headerArray.RemoveAll();
	headerArray.Add("设备名称");
	headerArray.Add("IP/机器名");
	headerArray.Add("CPU平均利用率(%)");
	headerArray.Add("内存平均利用率(%)");
	SS.AddHeaders(headerArray);

	list<DeviceItem>::iterator RecordItem;
	char buf[256];
	memset(buf, 0, 256);

	for(RecordItem=DeviceList.begin(); RecordItem != DeviceList.end(); RecordItem++)
	{
		contentArray.RemoveAll();

		contentArray.Add(RecordItem->sName.c_str());
		contentArray.Add(RecordItem->sIP.c_str());

		if (RecordItem->hasCPU) sprintf(buf, "%0.0f", RecordItem->CPUUtilization);
		else sprintf(buf, "%s", "无CPU监视器");
		contentArray.Add(buf);

		memset(buf, 0, 256);
		if (RecordItem->hasMemory) sprintf(buf, "%0.0f", RecordItem->MemoryUtilization);
		else sprintf(buf, "%s", "无Memory监视器");
		contentArray.Add(buf);

		SS.AddRow(contentArray);
	}
	SS.Commit();		
	OutputDebugString("\n----------ExportExcel End-------------\n");

	OutputDebugString("\n----------showDownload-------------\n");

	string sDown = "hiddenbar();showDownload('<a href=/";
	sDown += szXSLReportName;
	sDown += " target=_blank>";
	sDown += szXSLReportName;
	sDown += "</a>','";
	sDown += "下载列表";
	sDown += "','";
	sDown += "关闭";
	sDown += "')";
	WebSession::js_af_up = sDown;
}
