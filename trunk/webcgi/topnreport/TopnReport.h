#pragma once

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
class WSVMainTable;
class WSVFlexTable;
class WSButton;

#include "WSignalMapper"
#include "svdbapi.h"
#include <list>
#include <vector>

#include "..\statsreport\include\chartdir.h"

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

class CTopnReport :	public WContainerWidget
{
//MOC: W_OBJECT CTopnReport:WContainerWidget
    W_OBJECT;

public:
	CTopnReport(chen::TTime starttime, chen::TTime endtime, std::string reportname, std::string szCount, WContainerWidget *parent );
	void refresh();
  
	void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname, std::string &fieldtype,std::list<int>&intlist, std::list<float>&floatlist, std::list<string>&stringlist, float & maxval, float & minval, float & perval, float & lastval, int &reccount, std::string &reddispstr, std::string gv);

	void GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> & retmonnamelist, std::list<int> & retstatlist, std::list<string> &retstrlist, std::list<string> &rettimelist);

	void GetMonitorRecord(std::string monitorid, std::string returnstr, chen::TTime starttime, chen::TTime endtime,std::string reportname, int & retperval, int &retmaxval, int &retminval, std::string & retdispstr, std::string gv, int &retlastval);
	void GetPlanMonitorRecord(std::string monitorid, std::string returnstr, chen::TTime starttime, chen::TTime endtime,std::string reportname, int & retperval, int &retmaxval, int &retminval, std::string & retdispstr, std::string gv, int &retlastval);

	void enumMonitor(string &szIndex);

	void GenBarImage(double data[], char *labels[],int color[], int len,  char * xtitle, char * ytitle, char * szFile);

	//void GetTempletByMonitor(
	
	void AddJsParam(const std::string name, const std::string value);
	void ReturnMainReport(std::string reportname);
	void NewInitPageItem(std::string title, std::string reportname);


	~CTopnReport(void);

public : //language;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;

	std::string szInterTime;

	std::string strNameTest;
	WSignalMapper m_userMapper; 
	WSignalMapper m_userMapper1;
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
	
	std::string strRefreshID;

	list<TTimeSpan> starttimelist[7];
	list<TTimeSpan> endtimelist[7];

public:
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	CFlexTable *pUserTable;
	WTable * pUserListTable;
	WLineEdit *pEditUserName; 

	WSVMainTable * m_TopMainTable;
	WSVFlexTable * m_TopFlexTable;


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

	int normalrecnum;
	int dangerrecnum;
	int errorrecnum;

	bool bSort;	

	std::string strReturn;
	std::string strDes;
	std::string strDes1;
	std::string strAsc1;
	std::string strCompany;

	OBJECT objRes;
	MAPNODE ResNode;

public:

	void ShowMainTable(chen::TTime starttime, chen::TTime endtime, std::string reportname, std::string szCount);

	void AddColum( WTable* pContain );

	void AddListColumn();
	std::string GetLabelResource(std::string strLabel);


	// 列表
	list<OneRecord> RecordList;
	//列表中的表项

	//生成线状图表
	void GenLineImage(double data[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);

	std::list<OneRecord>::iterator m_pRecordList;

	std::string bStrCurr ;
private:
	void GetMonitorGroup(char * reportname, std::list<string> & grouplist);

	void InitPageItem(WTable * table, std::string title, std::string reportname);

	void WriteGenIni(std::string reportname, std::string starttime,std::string endtime,std::string value,std::string fieldlabel, float minval, float perval,float maxval);

private slots:

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
		string szGetValueNew;
public:
        _FORM_SHOW_TEXT()
        {
/*			szTitle = "统计报告";

			szRunTitle = "运行情况报表";
			szMonitorTitle = "监测数据统计表";
			szErrorTitle = "错误(%)";
			szDangerTitle = "危险(%)";
			szNormalTitle = "正常(%)";
			
			szRunName = "设备名称";
			szRunTime = "监测器名";
			szRunDanger = "平均值";
			szRunError = "最大值";
			szRunNew = "最小值";
			szRunClicket = "最近一次描述";


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
			szGetValueNew = "最新";
*/        }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

};

