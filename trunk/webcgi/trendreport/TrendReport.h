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
class CTrendReport : public WTable
{
	//MOC: W_OBJECT CTrendReport:WTable
    W_OBJECT;
public:
	CTrendReport(TTime starttime, TTime endtime, std::string reportname, bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent );
	void refresh();

	//void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname,std::string fieldtype, std::list<int> & intlist, std::list<float> & floatlist, std::list<string> & stringlist,  std::list<string> & timelist, std::list<double> & timelist1, float & maxval, float & minval, float & perval, float & lastval, int & reccount);
	void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname, std::string fieldtype,\
		std::list<int> & intlist, std::list<float> & floatlist, std::list<string> & stringlist,\
		std::list<int>&badlist, std::list<TTime> & timelist, float & maxval, float & minval, float & perval,\
		float & lastval, int &reccount);	void GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> & retmonnamelist, std::list<int> & retstatlist, std::list<string> &retstrlist, std::list<string> &rettimelist);

	void GetMonitorRecord(std::string monitorid, TTime starttime, TTime endtime, bool bClicket, bool bListStatsResult, std::string reportname, int &tcount, int &i6, int & i3, int & fieldnum);
	//void CTrendReport::enumMonitor(string &szIndex);

	~CTrendReport(void);
	
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

	TTime m_starttime;
	TTime m_endtime;
	std::string m_reportname;

	std::list<string> grouplist;

	string strReocrdIni, strPage, strPageCount, strRecordCount;
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

	std::list<string> fieldlist;
	bool ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps);
	list<string> liststr;

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

	string strGoodData;
	string strErrorData;
	string strWarningData;

	WText * pTextTipInfo;
	WText * pCopyRightInfo;

	WTable * pFrameTable;
	CFlexTable * pDataTable;
	WTable * pDataCmdTable;
	WTable * pDataListTable;
	void AddDataColum(WSVFlexTable* pContain);
	void AddDataItem(string strName, string strTime, string strData);

	void AddNormalDataColum(WSVFlexTable* pContain);
	//void AddNormalDataItem(string strTime, string strData);
	void CTrendReport::AddNormalDataItem(string strName, string strTime, string strData, int numRow);

	void RefreshList();


	//new UI by AndiLiu
	WSVFlexTable *m_pUptimeTable;
	WSVFlexTable *m_pMeasurementTable;
	WSVFlexTable *m_pChartTable;
	WSVFlexTable *m_pDataTable;
	WTable *m_pListMainTable;
	
//	string strPage,strPageCount,strRecordCout;

	void InitPageTable(WTable *mainTable, string title);
	void AddDataItemNew(string strName, string strTime, string strData, int numRow);

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

	string szXSLImage;
public:

	void ShowMainTable(TTime starttime, TTime endtime, std::string reportname, bool bClicket, bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage);

	void AddColum( WTable* pContain );

	void AddListColumn();


	// 列表
	list<OneRecord> RecordList;
	//列表中的表项

	//生成线状图表
	//void GenLineImage(double data[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);
	void GenLineImage(double data[], double time[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);
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

		string szPageIni;
		string szChart;
		string szGood;
		string szWarning;
		string szError;
		string szDisable;
		string szMaxValue;
		string szAverageValue;
		string szMinValue;
		string szName;
		string szState;
		string szTime;
		string szData;
		string szPage;
		string szPageCount;
		string szRecordCount;
		string szPageRecordCount;
		string szClose;
		string szDownloadList;

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
	//MOC: SLOT CTrendReport::DataBack()
    void DataBack();
	//MOC: SLOT CTrendReport::DataForward()
	void DataForward();
	//MOC: SLOT CTrendReport::DataReturn()
	void DataReturn();
	//MOC: SLOT CTrendReport::NormalBtn()
	void NormalBtn();
	//MOC: SLOT CTrendReport::ErrorBtn()
	void ErrorBtn();
	//MOC: SLOT CTrendReport::WarnningBtn()
	void WarnningBtn();
	//MOC: SLOT CTrendReport::SaveExcelBtn()
	void SaveExcelBtn();
};

