#include "TrendReportResult.h"
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

CTrendReportResult::CTrendReportResult(chen::TTime starttime, chen::TTime endtime, std::string reportname, bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent )
:WTable(parent)
{

}

CTrendReportResult::~CTrendReportResult()
{

}

void CTrendReportResult::refresh()
{

}


//
void CTrendReportResult::DataBack()
{
}

//
void CTrendReportResult::DataForward()
{
}

//
void CTrendReportResult::DataReturn()
{
}

//
void CTrendReportResult::NormalBtn()
{
}

//
void CTrendReportResult::ErrorBtn()
{
}

//
void CTrendReportResult::WarnningBtn()
{
}

void CTrendReportResult::SaveExcelBtn()
{
}