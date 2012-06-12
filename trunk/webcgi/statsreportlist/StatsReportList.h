#pragma once

#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WTableCell;
class WPushButton;
class WApplication;
class WSVFlexTable;
class WSVMainTable;
class WSVButton;

#include "svdbapi.h"

#include "WSignalMapper"
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;


class CStatsReportList :	public WContainerWidget
{
//MOC: W_OBJECT CStatsReportList:WContainerWidget
    W_OBJECT;
public:
    CStatsReportList(WContainerWidget *parent = 0);
	void refresh();
	std::list<string>  CStatsReportList::ReadFileName(string path);
	std::list<WTable*> tablelist;
	//void AddGroupOperate(WTable * pTable, int Rows);
	void AddGroupOperate();

	

	~CStatsReportList(void);
public : //language;

	OBJECT objRes;
	MAPNODE ResNode;
	std::string GetLabelResource(std::string strLabel);


	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;
	std::string strNameTest;

	//解决英文版出现中文的问题 苏合 2007-07-17
	std::string szTimePeriod;
	//解决英文版出现中文的问题 苏合 2007-07-17

	std::string strRefresh;

	WSignalMapper m_userMapper; 
	WSignalMapper m_userMapper1;
	std::string strDel;

	std::list<string> colname;
	std::list<string> colname1;

	std::string querystr;
	string szButNum,szButMatch;
	string szAffirmInfo;
	typedef struct _LIST
	{
		WCheckBox * pSelect;
		WText * pSection;
		std::string szSection;
	}_LIST, *LP_LIST;

	std::list<_LIST> m_pList;
	std::list<_LIST>::iterator m_pListItem;

	WPushButton * pHideBut;

private slots:
	//MOC: SLOT CStatsReportList::FastGenReport()
    void FastGenReport();
	//MOC: SLOT CStatsReportList::Translate()
	void Translate();
	//MOC: SLOT CStatsReportList::ExChange()
	void ExChange();
	//MOC: SLOT CStatsReportList::SelAll()
    void SelAll();
	//MOC: SLOT  CStatsReportList::SelNone()
	void SelNone();
	//MOC: SLOT  CStatsReportList::SelInvert()
	void SelInvert();
    //MOC: SLOT  CStatsReportList::BeforeDelList()
    void BeforeDelList();
	//MOC: SLOT  CStatsReportList::DelList()
    void DelList(); 
	//MOC: SLOT  CStatsReportList::ReturnMainReport()
	void ReturnMainReport();
public:
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	CFlexTable *pUserTable;
	WTable * pContainTable;
	WTable * pMonitorListTable;
	WText * reporttitletext;
	WPushButton * pGenReportButn;
	WText * reporttitle;
	WApplication *  appSelf;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;
	int nListNum;
	WTable * m_pGroupOperate;

	WPushButton * pReturnBtn;

	WSVFlexTable *m_pMainFlexTable;
	WSVMainTable *m_pMainTable;
	WSVButton *m_pGenButton;
	WSVButton *m_pReturnBtn;
	string strListHeights,strListTitles,strListPans;

	void AddJsParam(const std::string name, const std::string value);
public:

	void ShowMainTable();

	void AddColum( WTable* pContain );

	void AddTableContentFromIni(std::string section, std::string filename , WTable * pContain);

	void MonitorColumnSet(std::string str, int &tablenum, int & tablenum1);

	int InsertListRow(int num, int pos, std::string section, std::string tempsection, std::list<string> keylist, std::string filename, bool bAddColumn = false);
	// 列表

	std::string bStrCurr ;
	std::string szReport;
	std::string szCreateImm;
	std::string szMaxValue;
	std::string szAverageValue;
	std::string szMinValue;
	std::string szReportDay;
	std::string szReportWeek;
	std::string szReportMonth;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh1;
	std::string strRefreshTip1;
	std::string strRefreshID;

private:
	std::list<string> strAllTitle;
	int Ttablenum;
	int Dtablenum;

private slots:

	typedef struct _FORM_SHOW_TEXT
    {
		string szTitle;
		string szMonitorListTitle;	
		string szMonitorListStatus; string szMonitorListDescription;
		string szMonitorListName; string szMonitorListTime;
		string szCaption1;

		string szAdd;       
		string szDel;        
        string szTipSelAll;		
		string szTipSelAll1;
		string szTipSelNone;
		string szTipSelInv;		
		string szTipDel;

		string szReturn;
		
public:
        _FORM_SHOW_TEXT()
        {
/*			szCaption1 = "监测总数:0 正常数:0 危险数:0 错误数:0";

			szTitle = "统计报告";
			szMonitorListName = "统计报告";

			szMonitorListStatus = "状态";
			szMonitorListDescription = "描述";
			szMonitorListName = "监测器名称";
			szMonitorListTime = "时间";
*/
		
        }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

};

