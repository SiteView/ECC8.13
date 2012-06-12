#pragma once

#include "stdafx.h"
#include "WContainerWidget"
class CMainTable;
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WImage;
class WApplication;
class WPushButton;
#include "svdbapi.h"
#include <list>
#include <vector>

#include "../../base/chartdir.h"

#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"
#include "../svtable/WSTreeAndPanTable.h"
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
class CContrastReport : public WTable
{
	//MOC: W_OBJECT CContrastReport:WTable
    W_OBJECT;
public:
	//CContrastReport(chen::TTime starttime, chen::TTime endtime, std::string reportname, bool bClicket ,
	//bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent );
	CContrastReport(chen::TTime starttime, chen::TTime endtime, std::string *templatename,\
		std::list<string>*monitorlist, int index, bool bClicket ,bool bListError, \
		bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent );
	void refresh();

	//void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname,std::string fieldtype, std::list<int> & intlist,
	// std::list<float> & floatlist, std::list<string> & stringlist,  std::list<string> & timelist, 
	//std::list<double> & timelist1, float & maxval, float & minval, float & perval, float & lastval, int & reccount);
	void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname, std::string fieldtype, std::list<int> & intlist, \
		std::list<float> & floatlist, std::list<string> & stringlist, std::list<int>&badlist, std::list<TTime> & timelist,\
		float & maxval, float & minval, float & perval, float & lastval, int &reccount, std::string &maxtime);
	void GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> & retmonnamelist, \
		std::list<int> & retstatlist, std::list<string> &retstrlist, std::list<string> &rettimelist);

	void GetMonitorRecord(std::string *templatename,std::list<string> *monitorlist, int index, chen::TTime starttime, chen::TTime endtime, bool bClicket, bool bListStatsResult, std::string reportname, int &tcount, int &i6, int & i3, int & fieldnum);
	//void CContrastReport::enumMonitor(string &szIndex);

	~CContrastReport(void);
	
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

	chen::TTime m_starttime;
	chen::TTime m_endtime;
	std::string m_reportname;

	std::list<string> grouplist;

	WText * pPageCount;
	WText * pCurrPage;
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

	//
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

	WText * pTextTipInfo;
	WText * pCopyRightInfo;
	
	WTable * pFrameTable;
	CFlexTable * pDataTable;
	WSVMainTable *m_pFrameTable;
	WSVFlexTable *m_pContainTable;
	WTable * pDataCmdTable;
	WTable * pDataListTable;

	OBJECT objRes;
	MAPNODE ResNode;	

	void AddDataColum(WTable* pContain);
	void AddDataItem(string strName, string strTime, string strData);

	void AddNormalDataColum(WTable* pContain);
	void AddNormalDataItem(string strTime, string strData);

	std::string GetLabelResource(std::string strLabel);

public:
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	WSVMainTable *m_pMainTable;
	WLineEdit *pEditUserName; 
	WSVFlexTable *m_column;
		WSVFlexTable *pImageTable;
		WSVFlexTable *pInsertTable;
	WText * pCurrName;
	WLineEdit *pCurrEditUserName;
	WText * pReportTitle;
	
	//stats report variable
	WTable * pContainTable;
	WTable * pRunTable;
	WTable * pMonitorTable;
	WTable * pErrorTable;
	WTable * pDangerTable;
//	WTable * pImageTable;
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
	CString retfieldname[256];
	string szEntityMonitor;
	string szXSLReportName;

	string szXSLImage;
//	CString *retfieldresult[10];

public:
	void ShowMainTable(chen::TTime starttime, chen::TTime endtime, std::string *templatename,\
		std::list<string>*monitorlist, int index, bool bClicket, bool bListError,\
		bool bListDanger, bool bListStatsResult, bool bListImage);
	void AddListColumn();

	// 列表
	list<OneRecord> RecordList;
	//列表中的表项

	//生成线状图表
	//void GenLineImage(double data[], const int len, char *xlabels[], int xlabelslen, \
	//int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale,
	// double starttime,double endtime, char* Title, char* xTitle, char * filename);
	//void GenLineImage(double data[], int arraylen, double time[], const int len, 
	//char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen, 
	// int yScale, int yStep, int xLinearScale, double starttime,double endtime, 
	//char* Title, char* xTitle, char * filename);
	XYChart* StartGenLineImage(double time[], int len, LineLayer **linelayer, LPSTR lpMultiByteStr,\
		char *xlabels[],int xscalelen, int xStep, char *ylabels[], int yscalelen, int yScale,\
		int yStep, int xLinearScale, double starttime, double endtime, char* Title, char* xTitle, int ctitle);
	void EndGenLineImage(XYChart *c, LPSTR lpMultiByteStr, char * filename);
	void GenLineImage(double data[], double time[], const int len, LineLayer *linelayer, int color, char*name);
	//void GenLineImage1(double data[], double time[],  const int len, char *xlabels[],int xscalelen,
	// int xStep, char *ylabels[], int yscalelen, int yScale, int yStep, int xLinearScale,
	// double starttime, double endtime, char* Title, char* xTitle, char * filename);
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
		string szContrastTitle;
public:
        _FORM_SHOW_TEXT()
        {
     }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

private slots:


};

