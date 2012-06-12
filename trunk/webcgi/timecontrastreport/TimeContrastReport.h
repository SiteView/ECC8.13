#pragma once

#include "stdafx.h"
#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WImage;
class WApplication;
class WPushButton;

//new ui class
class WSVMainTable;
class WSVFlexTable;
class WSTreeAndPanTable;



#include "svdbapi.h"
#include <list>
#include <vector>

#include "../../base/chartdir.h"
#include "CheckBoxTreeView.h"
//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

//Year , month , day
typedef struct _YYYYMMDD
{
	int year;
	int month;
	int day;
}YMD;

//拓扑记录结构
typedef struct _OneRecord
{
	WCheckBox * pCheckBox;
	//用户名
	std::string strUserName;
	WText *pstrUserName;
	WLineEdit * pLineEdit;
	//拓扑图
	WImage * pTuop;
	WImage * pEdit;
}OneRecord,*POneRecord;
class CFlexTable;

enum QUERY_TYPE
{
	BYDAY,BYWEEK,BYMONTH
};

class CTimeContrastReport : public WTable
{
	//MOC: W_OBJECT CTimeContrastReport:WTable
    W_OBJECT;
public:
	CTimeContrastReport(svutil::TTime starttime, svutil::TTime endtime, std::string reportname, string templatename, int selectType,  bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent );
	void refresh();

	//void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname,std::string fieldtype, std::list<int> & intlist, std::list<float> & floatlist, std::list<string> & stringlist,  std::list<string> & timelist, std::list<double> & timelist1, float & maxval, float & minval, float & perval, float & lastval, int & reccount);
	void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname, std::string fieldtype, std::list<int> & intlist, std::list<float> & floatlist, std::list<string> & stringlist, std::list<TTime> & timelist, float & maxval, float & minval, float & perval, float & lastval, int &reccount);
	void GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> & retmonnamelist, std::list<int> & retstatlist, std::list<string> &retstrlist, std::list<string> &rettimelist);

	void GetMonitorRecord(std::string monitorid, string templatename,svutil::TTime starttime, svutil::TTime endtime, QUERY_TYPE nType,  bool bClicket, bool bListStatsResult, std::string reportname, int &tcount, int &i6, int & i3, int & fieldnum);
	//void CTimeContrastReport::enumMonitor(string &szIndex);

	~CTimeContrastReport(void);
	
public : //language;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;

	std::string szInterTime;

	std::string strNameTest;
	//WSignalMapper m_userMapper; 
	//WSignalMapper m_userMapper1;
	std::string strDel;

	svutil::TTime m_starttime;
	svutil::TTime m_endtime;
	std::string m_reportname;

	std::list<string> grouplist;

	WText * pPageCount;
	WText * pCurrPage;
	WText * pRecCount;
	int gPageNum;//页计数
	int gPageCount;//总页数
	std::string value;

	std::list<int> retstatlist;
	std::list<string> retstrlist;
	std::list<string> rettimelist;
	std::list<string> retmonnamelist;
	
	std::list<int>::iterator retstatlistitem;
	std::list<string>::iterator retstrlistitem;
	std::list<string>::iterator rettimelistitem;
	std::list<string>::iterator retmonnamelistitem;

	std::list<string> retnormalnamelist;
	std::list<string> retnormaltimelist;
	std::list<string> retnormalstatuslist;

	std::list<string> retdangernamelist;
	std::list<string> retdangertimelist;
	std::list<string> retdangerstatuslist;

	std::list<string> reterrornamelist;
	std::list<string> reterrortimelist;
	std::list<string> reterrorstatuslist;
	
	std::list<string> retstatuslist;
	int nCurPage;
	int nTotalPage;
	int nPageCount;
	bool bDivide;

	int nCurDataType;
	
	string strHTimeLabel;
	string strHNameLabel;
	string strHDataLabel;
	string strNormalBtn;
	string strErrorBtn;
	string strWarnningBtn;
	string strBack;
	string strForward;
	string strReturn;
	string strDataTableName;
	string strNoSortRecord;

	WText * pTextTipInfo;
	WText * pCopyRightInfo;

	WTable * pFrameTable;
	CFlexTable * pDataTable;
	WTable * pDataCmdTable;
	WTable * pDataListTable;
	void AddDataColum(WTable* pContain);
	void AddDataItem(string strName, string strTime, string strData);

	//new UI by AndiLiu
	WSVFlexTable *m_pUptimeTable;
	WSVFlexTable *m_pMeasurementTable;
	WSVFlexTable *m_pChartTable;
	WSVFlexTable *m_pDataTable;
	WTable *m_pListMainTable;
	
	string strPage,strPageCount,strRecordCout;

	void InitPageTable(WTable *mainTable, string title, svutil::TTime timeponit1, svutil::TTime timepoint2, QUERY_TYPE nType);
	void AddDataItemNew(string strName, string strTime, string strData, int numRow);


	//new method
	void GenLineImage(double data[],
								   double time[],
								   const int len,
								   LineLayer *linelayer,
								   int color, 
								   char*name);
	void EndGenLineImage(XYChart *c,
									  LPSTR lpMultiByteStr,
									  char * filename);
	XYChart * StartGenLineImage(double data[], 
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
											 QUERY_TYPE nType);

public:
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;

	WLineEdit *pEditUserName; 

	WText * pCurrName;
	WLineEdit *pCurrEditUserName;
	WText * pReportTitle;

	//stats report variable
	WTable * pContainTable;
	WTable * pRunTable;
	WTable * pMonitorTable;
	WTable * pErrorTable;
	WTable * pDangerTable;
	WTable * pImageTable;
	WTable * pNormalTable;

	WTable * pOtherTable;

	WImage * pPrevImg;
	WImage * pNextImg;
	WImage * pGoPageImg;
	WLineEdit * pGoPageEdit;

	int normalrecnum;
	int dangerrecnum;
	int errorrecnum;

	int gfieldnum;
	CString retfieldname[64];
	string szEntityMonitor;
	string szXSLReportName;
//	CString *retfieldresult[10];

	OBJECT objResource;
	MAPNODE resourceNode;
	std::string GetLabelResource(std::string strLabel);

public:

	void ShowMainTable(svutil::TTime starttime, svutil::TTime endtime, QUERY_TYPE nType, std::string reportname,string templatename, bool bClicket, bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage);

	void AddColum( WTable* pContain );

	void AddListColumn();


	// 列表
	list<OneRecord> RecordList;
	//列表中的表项

	//生成线状图表
	//void GenLineImage(double data[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);
	//void GenLineImage(double data[], double time[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);
	//void GenLineImage1(double data[], double time[],  const int len, char *xlabels[],int xscalelen, int xStep, char *ylabels[], int yscalelen, int yScale, int yStep, int xLinearScale, double starttime, double endtime, char* Title, char* xTitle, char * filename);
	void GenPieImage(char * szTitle, char * labels[], double data[], int len,char * filename);

	std::list<OneRecord>::iterator m_pRecordList;

	std::string bStrCurr ;
private:
	void GetMonitorGroup(char * reportname, std::list<string> & grouplist);

	void InitPageItem(WTable * table, std::string title);

	void WriteGenIni(std::string reportname, std::string starttime,std::string endtime,std::string value,std::string fieldlabel, float minval, float perval,float maxval);
	
	typedef struct _FORM_SHOW_TEXT
    {
		string szTitle;

		string szRunTitle; string szMonitorTitle; string szErrorTitle; string szDangerTitle;

		string szRunName; string szRunTime;
		string szRunDanger; string szRunError;
		string szRunNew;

		string szMonName; string szMonMeasure;
		string szMonMax; string szMonPer;
		string szMonLast;

		string szErrName; string szErrStartTime;
		//string szErrEndTime; 
		string szErrStatus;

		string szDangerName; string szDangerStartTime;
		//string szDangerEndTime; 
		string szDangerStatus; string szRunClicket;
		
		string szNormalTitle;

		string szXLSName;
		string szXLSTime;
		string szXLSStatus;
		string szXLSData;

		string szXLSNormal;
		string szXLSError;
		string szXLSDanger;
		string szExcelBut;
public:
        _FORM_SHOW_TEXT()
        {
/*
			szTitle = "统计报告";

			szRunTitle = "运行情况报表";
			szMonitorTitle = "监测数据统计表";
			szErrorTitle = "错误(%)";
			szDangerTitle = "危险(%)";
			szNormalTitle = "正常(%)";
			
			szRunName = "名称";
			szRunTime = "正常运行时间(%)";
			szRunDanger = "危险(%)";
			szRunError = "错误(%)";
			szRunNew = "最新";
			szRunClicket = "阀值";


			szMonName = "名称";
			szMonMeasure = "测量";
			szMonMax = "最大";
			szMonPer = "平均";
			szMonLast = "最近一次";

			szErrName = "名称";
			szErrStartTime = "时间";
		//	szErrEndTime = "结束时间";
			szErrStatus = "状态";

			szDangerName = "名称";
			szDangerStartTime = "时间";
		//	szDangerEndTime = "结束时间";
			szDangerStatus = "状态";
  */      }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

private slots:
	size_t FindCount(string monitorid, TTime &start, TTime &stop, int week);
	size_t FindCount2(string monitorid, TTime &start, TTime &stop, int hour);
};

