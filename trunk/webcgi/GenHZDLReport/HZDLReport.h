/*
*  HZDLReport.h
*
*  Modified on 2007-10-05 By 苏合
*     1、在报表中加入IP(或机器名)的数据
*
*/
#pragma once

#include "WContainerWidget"
#include <WTable>
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WImage;
class WApplication;
class WPushButton;
class WTable;

class WSVMainTable;
class WSVFlexTable;
class WSTreeAndPanTable;

#include "svdbapi.h"
#include <list>
#include <vector>
#include <string>

using namespace std;

//要列入报表的数据结构
struct DeviceItem
{
	string sName;
	string sIP;
	bool hasCPU;
	float CPUUtilization;
	bool hasMemory;
	float MemoryUtilization;
};

//数据库中监视数据记录的状态
enum RecordState{
    STATUS_OK       =1,
    STATUS_WARNING  =2,
    STATUS_ERROR    =3,
    STATUS_DISABLE  =4,
    STATUS_BAD      =5,
    STATUS_NULL		=0
};

class CHZDLReport : public WTable
{
	W_OBJECT;
public:
	CHZDLReport(TTime starttime, TTime endtime, WContainerWidget *parent);
	~CHZDLReport(void);

	TTime m_starttime;
	TTime m_endtime;
	string szXSLReportName;

	WTable *m_pListMainTable;
	WText * pReportTitle;
	WSVFlexTable * m_pDataTable;
	WTable * pDataCmdTable;

private:
	void initForm();
	void InitPageTable(WTable *mainTable, string title);
	void addData(WSVFlexTable * pParentTable);
	void GenList();
	void GetData(string deviceName, string & sIP, bool & useCPU, bool & useMemory, float & CPUUtl, float & MemoryUtl);
	float CalcAverage(string monitorID, string fieldName);

	list<DeviceItem> DeviceList;

private slots:
	void SaveExcelBtn();
};
