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

class WSVMainTable;
class WSVFlexTable;
class WSVButton;

#include "WSignalMapper"
#include <list>
#include <vector>

#include "svdbapi.h"

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;


class CTopnReportList :	public WContainerWidget
{
//MOC: W_OBJECT CTopnReportList:WContainerWidget
    W_OBJECT;
public:
    CTopnReportList(WContainerWidget *parent = 0);
	void refresh();
	std::list<string>  CTopnReportList::ReadFileName(string path);
	std::list<WTable*> tablelist;
	void AddGroupOperate(WTable * pTable);

	~CTopnReportList(void);
public : //language;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;
	std::string strNameTest;

	std::string strRefresh;

	WSignalMapper m_userMapper; 
	WSignalMapper m_userMapper1;
	std::string strDel;

	std::list<string> colname;
	std::list<string> colname1;

	std::string querystr;

	std::string strReturn;
	string szButNum,szButMatch;
	string szDeleteAffirmInfo;
	OBJECT objRes;
	MAPNODE ResNode;
private slots:
	//MOC: SLOT CTopnReportList::FastGenReport()
    void FastGenReport();
	//MOC: SLOT CTopnReportList::Translate()
	void Translate();
	//MOC: SLOT CTopnReportList::ExChange()
	void ExChange();
	//MOC: SLOT CTopnReportList::SelAll()
    void SelAll();
	//MOC: SLOT  CTopnReportList::SelNone()
	void SelNone();
	//MOC: SLOT  CTopnReportList::SelInvert()
	void SelInvert();
    //MOC: SLOT  CTopnReportList::BeforeDelList()
    void BeforeDelList();
	//MOC: SLOT  CTopnReportList::DelList()
    void DelList(); 
	//MOC: SLOT CTopnReportList::ReturnMainTopnReport()
	void ReturnMainTopnReport();
public:
	//WScrollArea * pUserScrollArea;
	//CMainTable *pMainTable;
	//CFlexTable *pUserTable;
	WTable * pContainTable;
	WTable * pMonitorListTable;
	WApplication *  appSelf;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;
	WText * reporttitletext;
	WPushButton * pGenReportButn;
	WText * reporttitle;
	int nListNum;
	WTable * m_pGroupOperate;

	WSVMainTable * pMainTable;
	WSVFlexTable * m_pReportListTable;
	WSVButton * m_pDel;
	WSVButton * m_pAdd;
	WSVButton * m_pRen;

	typedef struct _LIST
	{
		WCheckBox * pSelect;
		WText * pSection;
		std::string szSection;
	}_LIST, *LP_LIST;

	std::list<_LIST> m_pList;
	std::list<_LIST>::iterator m_pListItem;

	WPushButton * pHideBut;

	WPushButton * pReturnBtn;

public:

	void ShowMainTable();

	void AddColum( WTable* pContain );
	void NewAddColum();

	void AddTableContentFromIni(std::string section, std::string filename , WTable * pContain);
	void NewAddTableContentFromIni(std::string section,std::string filename);

	void MonitorColumnSet(std::string str, int &tablenum, int & tablenum1);

	void TopnMonitorColumnSet();

	int InsertListRow(int num, int pos, std::string section, std::string tempsection, std::list<string> keylist, std::string filename);
	// 列表

	void AddJsParam(const std::string name, const std::string value);

	std::string bStrCurr ;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh1;
	std::string strRefreshTip1;
	std::string szReport;
	std::string szCreateImm;
	std::string szMaxValue;
	std::string szAverageValue;
	std::string szMinValue;
	std::string szReportDay;
	std::string szReportWeek;
	std::string szReportMonth;
	std::string strRefreshID;
	std::string strTopNReportList;
	string sztListEmpty;
	string strDelCon;
	string strDelList;

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
public:
        _FORM_SHOW_TEXT()
        {
/*
			szCaption1 = "监测总数:0 正常数:0 危险数:0 错误数:0";

			szTitle = "TOPN报告";
			szMonitorListName = "TOPN报告";

			szMonitorListStatus = "状态";
			szMonitorListDescription = "描述";
			szMonitorListName = "监测器名称";
			szMonitorListTime = "时间";
*/
		
        }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

};

