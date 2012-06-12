#include ".\hitlog.h"
#include "stdafx.h"
/////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVButton.h"
/////////////////////////////////////////
#include "WApplication"
#include "WebSession.h"
#include "WLineEdit"
#include "WComboBox"
#include "WImage"
#include "WText"
/////////////////////////////////////////
#include "cspreadsheet.h"
/////////////////////////////////////////
#include <string>
#include <list>
#include <algorithm>

using namespace std;
using namespace svutil;

#define RecordCountPerPage 15

//列表按字母排序
void ListSort(list<string> & StrList)
{
	//选择排序
	list<string>::iterator ListIter1;
	list<string>::iterator ListIter2;
	list<string>::iterator ListIter3;
	for(ListIter1=StrList.begin();ListIter1!=StrList.end();ListIter1++)
	{
		ListIter3 = ListIter1;
		ListIter2 = ListIter1;
		ListIter2++;
		if(ListIter2 == StrList.end())
			break;		
		//查找最小值
		for(ListIter2;ListIter2!=StrList.end();ListIter2++)
		{
			string strTemp2 = *ListIter2, strTemp3 = *ListIter3;
			transform(strTemp2.begin(),strTemp2.end(),strTemp2.begin(),(int(*)(int))tolower);
			transform(strTemp3.begin(),strTemp3.end(),strTemp3.begin(),(int(*)(int))tolower);
			int m = strTemp2.length();
			m = strTemp2.length() <= strTemp3.length() ? strTemp2.length() : strTemp3.length();
			for(int i=0; i<m; i++)
			{
				string ch2, ch3;
				ch2 = strTemp2.substr(i,1);
				ch3 = strTemp3.substr(i,1);
				if(ch2 == ch3)
					continue;
				ListIter3 = ch3 < ch2 ? ListIter3 : ListIter2;
				break;
			}
			if(i == m)
				ListIter3 = strTemp2.length() <= strTemp3.length() ? ListIter2 : ListIter3;
		}
		//交换
		if(ListIter1 != ListIter3)
		{
			string sTemp1 = *ListIter1, sTemp2 = *ListIter3;
			*ListIter1 = sTemp2;
			*ListIter3 = sTemp1;
		}
	}
}

CHitLog::CHitLog(WContainerWidget *parent):WContainerWidget(parent)
{
	loadString();
	ShowMainTable();
}

/////////////
void CHitLog::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);

	m_pMainTable = new WSVMainTable(this,m_szMainTitle,true);

	if(m_pMainTable)
	{
		WObject::connect(m_pMainTable->pHelpImg, SIGNAL(clicked()), this, SLOT(ShowHideHelp()));

		//查询	
		m_pQueryTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1,0), AlertSel ,m_szMainTitle);	
		if(m_pQueryTable->GetContentTable() != NULL)	
		{
			m_pQueryTable->InitTable();

			m_pQueryTable->AppendRows();
			//程序
			m_cProgram = new WComboBox(m_pQueryTable->AppendRowsContent(0 ,0, 1, m_szProgram, m_szProgramHelp, ""));
			if(m_cProgram)
			{
				m_cProgram->setStyleClass("input_text");
				m_cProgram->addItem(m_szAll);
				connect(m_cProgram, SIGNAL(changed()), this, SLOT(ShowFunc()));
				//从hitlog.ini获取程序列表
				list<string> keylist;
				list<string>::iterator keyitem;
				string strProgram;
				if(GetIniFileSections(keylist, "hitlog.ini"))
				{					
					ListSort(keylist);
					for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
					{
						m_cProgram->addItem((*keyitem));
					}
					keylist.clear();
				}
			}

			//函数
			m_cFunc = new WComboBox(m_pQueryTable->AppendRowsContent(0 ,1, 1, m_szFunc, m_szFuncHelp, ""));
			if(m_cFunc)
			{
				m_cFunc->setStyleClass("input_text");
				m_cFunc->addItem(m_szAll);
				connect(m_cFunc, SIGNAL(changed()), this, SLOT(ShowKey()));
			}

			m_pQueryTable->AppendRows();
			//开始时间
			m_EStartTime = new WLineEdit("", m_pQueryTable->AppendRowsContent(1, 0, 1, m_szStartTime, m_szStartTimeHelp, ""));
			if(m_EStartTime)
			{
				m_EStartTime->setStyleClass("input_text");
				TTime curTime = TTime::GetCurrentTimeEx();
				TTimeSpan ts(0,24,0,0);
				curTime -= ts;
				m_EStartTime->setText(curTime.Format());
				strcpy(m_EStartTime->contextmenu_ , "onFocus=\"calendar()\"");
			}

			//结束时间
			m_EEndTime = new WLineEdit("", m_pQueryTable->AppendRowsContent(1, 1, 1, m_szEndTime, m_szEndTimeHelp, ""));
			if(m_EEndTime)
			{
				m_EEndTime->setStyleClass("input_text");
				TTime curTime1 = TTime::GetCurrentTimeEx();
				m_EEndTime->setText(curTime1.Format());
				strcpy(m_EEndTime->contextmenu_ , "onFocus=\"calendar()\"");
			}

			m_pQueryTable->AppendRows();
			//用户
			m_cUserName = new WComboBox(m_pQueryTable->AppendRowsContent(2 ,0, 1, m_szUserName, m_szUserNameHelp, ""));
			if(m_cUserName)
			{
				m_cUserName->setStyleClass("input_text");
				m_cUserName->addItem(m_szAll);
				//从ini获取用户列表
				list<string> keylist1;
				list<string>::iterator keyitem1;
				string strLoginName;
				if(GetIniFileSections(keylist1, "user.ini"))
				{
					for(keyitem1 = keylist1.begin(); keyitem1 != keylist1.end(); keyitem1 ++)	
					{
						strLoginName = GetIniFileString((*keyitem1), "LoginName", "", "user.ini");
						m_cUserName->addItem(strLoginName);
					}
					keylist1.clear();
				}
			}
			//关键字
			m_cKey = new WComboBox(m_pQueryTable->AppendRowsContent(2 ,1, 1, m_szKey, m_szKeyHelp, ""));
			if(m_cKey)
			{
				m_cKey->setStyleClass("input_text");
				m_cKey->addItem(m_szAverTime);
				m_cKey->addItem(m_szHitTimes);
			}

			m_pQueryTable->ShowOrHideHelp();
			m_pQueryTable->HideAllErrorMsg();
		}

		//查询
		if(m_pQueryTable->GetActionTable()!=NULL)
		{
			WTable * pTbl = new WTable((WContainerWidget *)m_pQueryTable->GetActionTable()->elementAt(0, 1));
			if(pTbl)
			{
				WSVButton * pQuery = new WSVButton((WContainerWidget *)pTbl->elementAt(0, 0), m_szQuery, "button_bg_m.png", "", false);
//				connect(pQuery, SIGNAL(clicked()), "showbar();", this, SLOT(LogQuery()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
				connect(pQuery, SIGNAL(clicked()), this, SLOT(LogQuery()));
			}
		}
		
		//统计列表
		m_pStatisticTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(2,0), List, m_szLogStatisticList);
		if(m_pStatisticTable)
		{
			if(m_pStatisticTable->GetContentTable()!=NULL)
			{
				m_pStatisticTable->AppendColumn("",WLength(2,WLength::Pixel));
				m_pStatisticTable->SetDataRowStyle("table_data_grid_item_img");
				m_pStatisticTable->AppendColumn(m_szProgram,WLength(15,WLength::Percentage));
				m_pStatisticTable->SetDataRowStyle("table_data_grid_item_text");
				m_pStatisticTable->AppendColumn(m_szFunc,WLength(15,WLength::Percentage));
				m_pStatisticTable->SetDataRowStyle("table_data_grid_item_img");
				m_pStatisticTable->AppendColumn(m_szDes,WLength(30,WLength::Percentage));
				m_pStatisticTable->SetDataRowStyle("table_data_grid_item_text");
				m_pStatisticTable->AppendColumn(m_szHitTimes,WLength(15,WLength::Percentage));
				m_pStatisticTable->SetDataRowStyle("table_data_grid_item_text");
				m_pStatisticTable->AppendColumn(m_szAverTime,WLength(15,WLength::Percentage));
				m_pStatisticTable->SetDataRowStyle("table_data_grid_item_text");
			}
	
			if(m_pStatisticTable->GetActionTable() != NULL)
			{
				m_pStatisticTable->AddStandardSelLink(m_szPrevious,m_szNext,m_szReocrdIni);
				//connect(m_pStatisticTable->pSelAll, SIGNAL(clicked()), "showbar();", this, SLOT(LogStaPrevious()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);		
				//connect(m_pStatisticTable->pSelNone, SIGNAL(clicked()), "showbar();", this, SLOT(LogStaNext()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
				connect(m_pStatisticTable->pSelAll, SIGNAL(clicked()), this, SLOT(LogStaPrevious()));		
				connect(m_pStatisticTable->pSelNone, SIGNAL(clicked()), this, SLOT(LogStaNext()));
				m_pStatisticTable->pSelReverse->setStyleClass("");

				WTable * pNuTab = new WTable((WContainerWidget *)m_pStatisticTable->GetActionTable()->elementAt(0,2));
				if(pNuTab)
				{
					pNuTab->setStyleClass("width600");

					new WText("&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pNuTab->elementAt(0,1));
				}

				//导出execl
				WTable * pSubTab = new WTable((WContainerWidget *)m_pStatisticTable->GetActionTable()->elementAt(0,3));
				if(pSubTab)
				{
					pSubTab->setStyleClass("widthauto");

					m_pExport = new WSVButton(((WContainerWidget *)pSubTab->elementAt(0,1)), m_szExport,"button_bg_m_black.png","",true);	
					if(m_pExport)
//						connect(m_pExport,SIGNAL(clicked()),"showbar();",this,SLOT(ExportExcel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
						connect(m_pExport,SIGNAL(clicked()),this,SLOT(ExportExcel()));
				}
			}

			m_pStatisticTable->SetNullTipInfo(m_szLogNull);		
		}

		//日志列表
		m_pListTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(3,0), List, m_szLogList);
		if(m_pListTable)
		{
			if(m_pListTable->GetContentTable()!=NULL)
			{
				m_pStatisticTable->SetDivId("view_panel");

				m_pListTable->AppendColumn("",WLength(2,WLength::Pixel));
				m_pListTable->SetDataRowStyle("table_data_grid_item_img");
				m_pListTable->AppendColumn(m_szUserName,WLength(10,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_img");
				m_pListTable->AppendColumn(m_szProgram,WLength(15,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_text");
				m_pListTable->AppendColumn(m_szFunc,WLength(15,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_img");
				m_pListTable->AppendColumn(m_szDes,WLength(20,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_text");
				m_pListTable->AppendColumn(m_szFlag,WLength(5,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_text");
				m_pListTable->AppendColumn(m_szInterval,WLength(15,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_text");
				m_pListTable->AppendColumn(m_szTime,WLength(30,WLength::Percentage));
				m_pListTable->SetDataRowStyle("table_data_grid_item_text");

				AddJsParam("uistyle", "viewpanandlist");
				AddJsParam("fullstyle", "true");
				AddJsParam("bGeneral", "true");
			}
	
			if(m_pListTable->GetActionTable() != NULL)
			{
				m_pListTable->AddStandardSelLink(m_szPrevious,m_szNext,m_szReocrdIni);
//				connect(m_pListTable->pSelAll, SIGNAL(clicked()), "showbar();", this, SLOT(LogPrevious()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);		
//				connect(m_pListTable->pSelNone, SIGNAL(clicked()), "showbar();", this, SLOT(LogNext()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
				connect(m_pListTable->pSelAll, SIGNAL(clicked()), this, SLOT(LogPrevious()));		
				connect(m_pListTable->pSelNone, SIGNAL(clicked()), this, SLOT(LogNext()));
				m_pListTable->pSelReverse->setStyleClass("");

				WTable * pNuTab = new WTable((WContainerWidget *)m_pListTable->GetActionTable()->elementAt(0,2));
				if(pNuTab)
				{
					pNuTab->setStyleClass("width600");

					new WText("&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pNuTab->elementAt(0,1));
				}

				//页面跳转
				WTable * pSubTab = new WTable((WContainerWidget *)m_pListTable->GetActionTable()->elementAt(0,3));
				if(pSubTab)
				{
					pSubTab->setStyleClass("width150");

					WText * t1 = new WText(m_szPageFront, (WContainerWidget *)pSubTab->elementAt(0,1));
					t1->setStyleClass("button_link_font");
					m_cChangePage = new WComboBox(((WContainerWidget *)pSubTab->elementAt(0,1)));
					WText * t2 = new WText(m_szPageBack, (WContainerWidget *)pSubTab->elementAt(0,1));
					t2->setStyleClass("button_link_font");
					if(m_cChangePage)
					{
						m_cChangePage->addItem("0");
						m_cChangePage->setStyleClass("input_text_auto");
//						connect(m_cChangePage, SIGNAL(changed()), "showbar();", this, SLOT(ChangePage()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
						connect(m_cChangePage, SIGNAL(changed()), this, SLOT(ChangePage()));
					}
				}
			}

			new WText("</div>", this);
			new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

			m_pListTable->SetNullTipInfo(m_szLogNull);		
		}
	}
}

///////////////////////////
void CHitLog::ShowKey()
{
	string strFunc = m_cFunc->currentText();
	if(strFunc == m_szAll)
	{
		m_cKey->clear();
		m_cKey->addItem(m_szAverTime);
		m_cKey->addItem(m_szHitTimes);
	}
	else
	{
		m_cKey->clear();
		m_cKey->addItem(m_szTime);
	}
}

//////////////////////////
void CHitLog::ChangePage()
{
	string strPage = m_cChangePage->currentText();
	if(strPage != "0")
	{
		nCurPage = atoi(strPage.c_str());
   		ListPage();
	}
}

//////////////////////////
bool ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps)
{
    char * token = NULL;
	char * cp = ::strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        if (pSVSeps) 
            token = strtok( pTmp , pSVSeps);
        else 
			return false;
        while( token != NULL )
        {
			pTokenList.push_back(token);
            if (pSVSeps)
                token = strtok( NULL , pSVSeps);
            else
               return false;
        }
        free(cp);
    }
    return true;
}

//////////////////////////////////
TTime MakeTTime(string strTime)
{
	if(strTime.empty())
	{
		TTime time;
		return time;
	}

	std::list<string> pTmpList;	
	ParserToken(pTmpList, strTime.c_str(), " ");
	
	string strYear, strMonth, strDay;
	std::list<string> pTmpList1;
	ParserToken(pTmpList1, pTmpList.front().c_str(), "-");
	
	strYear = pTmpList1.front();
	pTmpList1.pop_front();
	strMonth = pTmpList1.front();
	pTmpList1.pop_front();
	strDay = pTmpList1.front();
	pTmpList1.pop_front();
	
	string strHour, strMinute, strSecond;
	std::list<string> pTmpList2;
	ParserToken(pTmpList2, pTmpList.back().c_str(), ":");

	strHour = pTmpList2.front();
	pTmpList2.pop_front();
	strMinute = pTmpList2.front();
	pTmpList2.pop_front();
	strSecond = pTmpList2.front();
	pTmpList2.pop_front();
	
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	sscanf(strYear.c_str(), "%d", &nYear);
	sscanf(strMonth.c_str(), "%d", &nMonth);
	sscanf(strDay.c_str(), "%d", &nDay);
	sscanf(strHour.c_str(), "%d", &nHour);
	sscanf(strMinute.c_str(), "%d", &nMinute);
	sscanf(strSecond.c_str(), "%d", &nSecond);	
	
	TTime time(nYear, nMonth, nDay, nHour, nMinute, nSecond);

	return time;
}

///////////////////////////
void CHitLog::ExportExcel()
{
	string strProgram, strFunc, strStartTime, strEndTime, strUserName, strSortKey;

	strProgram = m_cProgram->currentText();

	strFunc = m_cFunc->currentText();
   
	strStartTime = m_EStartTime->text();
	strEndTime = m_EEndTime->text();
	TTime startTime, endTime;
	startTime = MakeTTime(strStartTime);
	if(strEndTime.empty())
		endTime = TTime::GetCurrentTimeEx();
	else
		endTime = MakeTTime(strEndTime);

	strUserName = m_cUserName->currentText();

	strSortKey = m_cKey->currentText();

	bool bQuery;
	if(strFunc == m_szAll)
	{
		OutputDebugString("\n----------Statistics Begin-------------\n");
	
		list<HitLogQuery> LogList;	
		bQuery = QueryHitRecord(strProgram, strFunc, startTime, endTime, strUserName, LogList);
		////////////统计
		list<statLog> staLogList;
		list<statLog>::iterator LogItem;
		statisLog(strProgram, strSortKey, LogList, staLogList);

		OutputDebugString("\n----------Statistics End-------------\n");

		OutputDebugString("\n----------ExportExcel Begin-------------\n");
		std::string szFilePath =GetSiteViewRootPath();
		szFilePath += "\\htdocs\\hitlog\\";

		string szFileName = "HitLog";
		TTime timer = TTime::GetCurrentTimeEx();

		char buf[100]={0};
		sprintf(buf,"%d-%02d-%02d-%2d-%02d-%02d", timer.GetYear(), timer.GetMonth(), timer.GetDay(), timer.GetHour(), timer.GetMinute(), timer.GetSecond());
		szFileName += buf;
		szFileName += ".xls";
		szFilePath += szFileName;

		CSpreadSheet SS(szFilePath.c_str(), "HitLog");

		CStringArray headerArray, contentArray;
		
		SS.BeginTransaction();
		
		// 加入标题
		headerArray.RemoveAll();
		headerArray.Add(m_szProgram.c_str());
		headerArray.Add(m_szFunc.c_str());
		headerArray.Add(m_szDes.c_str());
		headerArray.Add(m_szHitTimes.c_str());
		headerArray.Add(m_szAverTime.c_str());
		SS.AddHeaders(headerArray);

		char buf1[256];
		string strTimes, strAverTime;
		for(LogItem=staLogList.begin(); LogItem != staLogList.end(); LogItem++)
		{
			contentArray.RemoveAll();
			contentArray.Add(LogItem->pProgram.c_str());
			contentArray.Add(LogItem->pFunc.c_str());
			contentArray.Add(LogItem->pDesc.c_str());
			sprintf( buf1,"%d", LogItem->pTimes);
			strTimes = buf1;
			contentArray.Add(strTimes.c_str());
			sprintf( buf1,"%d", LogItem->pAverTime);
			strAverTime = buf1;
			contentArray.Add(strAverTime.c_str());
			SS.AddRow(contentArray);
		}	

		SS.Commit();		
		LogList.clear();

		OutputDebugString("\n----------ExportExcel End-------------\n");
		
		OutputDebugString("\n----------showDownload-------------\n");
		
//		string sDown = "hiddenbar();showDownload('<a href=/hitlog/";
		string sDown = "showDownload('<a href=/hitlog/";
		sDown += szFileName;
		sDown += " target=_blank>";
		sDown += szFileName;
		sDown += "</a>','";
		sDown += m_szDownLoad;
		sDown += "','";
		sDown += m_szConfirm;
		sDown += "')";
		WebSession::js_af_up = sDown;
	}
	else
	{
//		WebSession::js_af_up = "hiddenbar();";
		return;
	}
}

//////////////////////////
void CHitLog::LogPrevious()
{
	if(nCurPage != 1)
	{
		nCurPage = nCurPage -1;
		ListPage();
	}
	else
	{
//		WebSession::js_af_up = "hiddenbar();";
	}
}

//////////////////////////
void CHitLog::LogNext()
{
	if(nCurPage != nTotalPage)
	{
		nCurPage ++;
    	ListPage();
	}
	else
	{
//		WebSession::js_af_up = "hiddenbar();";
	}
}

///////////////////////////
void CHitLog::ListPage()
{
	if(m_pListTable)
	{
		m_pListTable->GeDataTable()->clear();

		m_pListTable->HideNullTip();

		list<HitLogQuery>::iterator LogItem1;
		char buf[256];
		string strFlag, strTime;
		int iRow=1, reCount=1, curCount=(nCurPage-1)*RecordCountPerPage;
		for(LogItem1=LogList1.begin(); LogItem1 != LogList1.end(); LogItem1++)
		{
			if(reCount <= curCount)
			{
				reCount++;
				continue;			
			}
			m_pListTable->InitRow(iRow);
			int iColNum = 0;
			new WText("&nbsp;" , (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->sUserName , (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->sHitPro, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->sHitFunc, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->sDesc, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			sprintf( buf,"%d", LogItem1->sHitFlag);
			strFlag = buf;
			iColNum += 2;
			new WText(strFlag, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			sprintf( buf,"%d", LogItem1->sHitInterval);
			strTime = buf;
			iColNum += 2;
			new WText(strTime, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->sTime, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
			if(iRow == RecordCountPerPage)
			{
				LogItem1++;
				break;
			}
			iRow++;
		}

		size_t recordCount = LogList1.size();
		char tmpchar[10] = {0};
		string strRecordInfo = m_szPage;
		sprintf(tmpchar, "%d", nCurPage);
		strRecordInfo += tmpchar;
		strRecordInfo += m_szPageCount;
		sprintf(tmpchar, "%d", nTotalPage);
		strRecordInfo += tmpchar;
		strRecordInfo += m_szRecordCount;
		sprintf(tmpchar, "%d", recordCount);
		strRecordInfo += tmpchar;
		m_pListTable->pSelReverse->setText(strRecordInfo);
	}
//	WebSession::js_af_up = "hiddenbar();";
}

//////////////////////////
void CHitLog::LogStaPrevious()
{
	if(nSCurPage != 1)
	{
		nSCurPage--;
		StaListPage();
	}
	else
	{
//		WebSession::js_af_up = "hiddenbar();";
	}
}

//////////////////////////
void CHitLog::LogStaNext()
{
	if(nSCurPage != nSTotalPage)
	{
		nSCurPage ++;
    	StaListPage();
	}
	else
	{
//		WebSession::js_af_up = "hiddenbar();";
	}
}

///////////////////////////
void CHitLog::StaListPage()
{
	if(m_pStatisticTable)
	{
		m_pStatisticTable->GeDataTable()->clear();

		m_pStatisticTable->HideNullTip();

		list<statLog>::iterator LogItem1;
		char buf[256];
		string strFlag, strTime;
		int iRow=1, reCount=1, curCount=(nSCurPage-1)*RecordCountPerPage;
		for(LogItem1=staLogList.begin(); LogItem1 != staLogList.end(); LogItem1++)
		{
			if(reCount <= curCount)
			{
				reCount++;
				continue;			
			}
			m_pStatisticTable->InitRow(iRow);
			int iColNum = 0;
			new WText("&nbsp;" , (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->pProgram, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->pFunc, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(LogItem1->pDesc, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
			sprintf( buf,"%d", LogItem1->pTimes);
			strFlag = buf;
			iColNum += 2;
			new WText(strFlag, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
			sprintf( buf,"%d", LogItem1->pAverTime);
			strTime = buf;
			iColNum += 2;
			new WText(strTime, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
			if(iRow == RecordCountPerPage)
			{
				break;
			}
			if(iRow == RecordCountPerPage)
			{
				LogItem1++;
				break;
			}
			iRow++;
		}

		size_t recordCount = staLogList.size();
		char tmpchar[10] = {0};
		string strRecordInfo = m_szPage;
		sprintf(tmpchar, "%d", nSCurPage);
		strRecordInfo += tmpchar;
		strRecordInfo += m_szPageCount;
		sprintf(tmpchar, "%d", nSTotalPage);
		strRecordInfo += tmpchar;
		strRecordInfo += m_szRecordCount;
		sprintf(tmpchar, "%d", recordCount);
		strRecordInfo += tmpchar;
		m_pStatisticTable->pSelReverse->setText(strRecordInfo);
	}
//	WebSession::js_af_up = "hiddenbar();";
}

//////////////////////////
void CHitLog::ShowFunc()
{
	string strProgram = m_cProgram->currentText();
	if(m_cFunc)
	{
		m_cFunc->clear();

		m_cFunc->addItem(m_szAll);

		list<string> FuncList;
		list<string>::iterator FuncItem;
		int funCount = GetIniFileInt(strProgram, "funcount", 0, "hitlog.ini");
		string strKey, strFunc="subfunc", strFuncValue;
	    char szMsg[256] = {0};
		for(int i=1; i<=funCount; i++)
		{
			sprintf(szMsg, "%s%d", strFunc.c_str(), i);
			strKey = szMsg;	
			strFuncValue= GetIniFileString(strProgram, strKey, "", "hitlog.ini");
			FuncList.push_back(strFuncValue);
		}
		ListSort(FuncList);
		for(FuncItem=FuncList.begin();FuncItem!=FuncList.end();FuncItem++)
		{
			strFuncValue = *FuncItem;
			m_cFunc->addItem(strFuncValue);				
		}
	}
	if(m_cKey)
	{
		m_cKey->clear();
		m_cKey->addItem(m_szAverTime);
		m_cKey->addItem(m_szHitTimes);
	}
}

//////////////////////////
void CHitLog::LogQuery()
{
	string strProgram, strFunc, strStartTime, strEndTime, strUserName, strSortKey;

	strProgram = m_cProgram->currentText();

	strFunc = m_cFunc->currentText();
   
	strStartTime = m_EStartTime->text();
	strEndTime = m_EEndTime->text();
	TTime startTime, endTime;
	startTime = MakeTTime(strStartTime);
	if(strEndTime.empty())
		endTime = TTime::GetCurrentTimeEx();
	else
		endTime = MakeTTime(strEndTime);

	strUserName = m_cUserName->currentText();

	strSortKey = m_cKey->currentText();

	list<HitLogQuery> LogList;

	bool bQuery;
	if(strFunc == m_szAll)
	{
		bQuery = QueryHitRecord(strProgram, strFunc, startTime, endTime, strUserName, LogList);
		if(m_pStatisticTable)
		{
			m_pStatisticTable->GeDataTable()->clear();
	
			if(LogList.size() == 0)
			{
				m_pStatisticTable->ShowNullTip();
			}
			else
			{
				m_pStatisticTable->HideNullTip();
				////////////统计
				staLogList.clear();
				list<statLog>::iterator LogItem;
				statisLog(strProgram, strSortKey, LogList, staLogList);

				char buf[256];
				string strTimes, strAverTime, strFlag, strTime;
				int iRow=1;
				for(LogItem=staLogList.begin(); LogItem != staLogList.end(); LogItem++)
				{
					m_pStatisticTable->InitRow(iRow);
					int iColNum = 0;
					new WText("&nbsp;" , (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem->pProgram, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem->pFunc, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem->pDesc, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
					sprintf( buf,"%d", LogItem->pTimes);
					strFlag = buf;
					iColNum += 2;
					new WText(strFlag, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
					sprintf( buf,"%d", LogItem->pAverTime);
					strTime = buf;
					iColNum += 2;
					new WText(strTime, (WContainerWidget *)m_pStatisticTable->GeDataTable()->elementAt(iRow,iColNum));
					if(iRow == RecordCountPerPage)
					{
						break;
					}
					iRow++;
				}

				size_t recordCount = staLogList.size();
				char tmpchar[10] = {0};
				string strRecordInfo = m_szPage;
				nSCurPage = 1;
				strRecordInfo += "1";
				strRecordInfo += m_szPageCount;
				if(recordCount % RecordCountPerPage  > 0)
				{
					nSTotalPage = recordCount / RecordCountPerPage + 1;
				}
				else
				{
					nSTotalPage = recordCount / RecordCountPerPage;
				}
				sprintf(tmpchar, "%d", nSTotalPage);
				strRecordInfo += tmpchar;
				strRecordInfo += m_szRecordCount;
				sprintf(tmpchar, "%d", recordCount);
				strRecordInfo += tmpchar;
				m_pStatisticTable->pSelReverse->setText(strRecordInfo);
			}
		}
	}
	else
	{
		LogList1.clear();
		bQuery = QueryHitRecord(strProgram, strFunc, startTime, endTime, strUserName, LogList1);
		if(m_pListTable)
		{
			m_pListTable->GeDataTable()->clear();

			if(LogList1.size() == 0)
			{
				m_pListTable->ShowNullTip();
			}
			else
			{
				m_pListTable->HideNullTip();

				list<HitLogQuery>::iterator LogItem1;
				char buf[256];
				string strFlag, strTime;
				int iRow=1;
				for(LogItem1=LogList1.begin(); LogItem1 != LogList1.end(); LogItem1++)
				{
					m_pListTable->InitRow(iRow);
					int iColNum = 0;
					new WText("&nbsp;" , (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem1->sUserName , (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem1->sHitPro, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem1->sHitFunc, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem1->sDesc, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					sprintf( buf,"%d", LogItem1->sHitFlag);
					strFlag = buf;
					iColNum += 2;
					new WText(strFlag, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					sprintf( buf,"%d", LogItem1->sHitInterval);
					strTime = buf;
					iColNum += 2;
					new WText(strTime, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					iColNum += 2;
					new WText(LogItem1->sTime, (WContainerWidget *)m_pListTable->GeDataTable()->elementAt(iRow,iColNum));
					if(iRow == RecordCountPerPage)
					{
						break;
					}
					iRow++;
				}

				size_t recordCount = LogList1.size();
				char tmpchar[10] = {0};
				string strRecordInfo = m_szPage;
				nCurPage = 1;
				strRecordInfo += "1";
				strRecordInfo += m_szPageCount;
				if(recordCount % RecordCountPerPage  > 0)
				{
					nTotalPage = recordCount / RecordCountPerPage + 1;
				}
				else
				{
					nTotalPage = recordCount / RecordCountPerPage;
				}
				sprintf(tmpchar, "%d", nTotalPage);
				strRecordInfo += tmpchar;
				strRecordInfo += m_szRecordCount;
				sprintf(tmpchar, "%d", recordCount);
				strRecordInfo += tmpchar;
				m_pListTable->pSelReverse->setText(strRecordInfo);

				//////////////Page
				string sPage;
 				m_cChangePage->clear();
	            for(int i=1; i<=nTotalPage; i++)
				{
					sprintf(tmpchar, "%d", i);
					sPage = tmpchar;
					m_cChangePage->addItem(sPage);
				}
			}
		}
	}
	
	LogList.clear();
//	WebSession::js_af_up = "hiddenbar();";
}

////////////////////////////////
void CHitLog::statisLog(string &strPro, string &strKeySort, list<HitLogQuery> &RecordList, list<statLog> &statiLogList)
{
	//获取程序列表
	list<string> ProList;
	list<string>::iterator ProItem;
	list<string> keylist;
	list<string>::iterator keyitem;
	if(strPro == m_szAll)
	{
		if(GetIniFileSections(keylist, "hitlog.ini"))
		{					
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
			{
				ProList.push_back((*keyitem));
			}
			keylist.clear();
		}
	}
	else
	{
		ProList.push_back(strPro);
	}
	for(ProItem = ProList.begin(); ProItem != ProList.end(); ProItem ++)
	{
		string strProgram = *ProItem;
		//获取函数列表
		list<string> funcList;
		list<string>::iterator funcItem;
		int funCount = GetIniFileInt(strProgram, "funcount", 0, "hitlog.ini");
		string strKey, strFunc="subfunc", strFuncValue;
		char szMsg[256] = {0};
		for(int i=1; i<=funCount; i++)
		{
			sprintf(szMsg, "%s%d", strFunc.c_str(), i);
			strKey = szMsg;	
			strFuncValue= GetIniFileString(strProgram, strKey, "", "hitlog.ini");
			funcList.push_back(strFuncValue);
		}

		statLog statLogItem;
		statLogItem.pProgram = strProgram;
		list<HitLogQuery>::iterator RecordItem;
		list<HitLogQuery>::iterator RecordItem1;
		list<statLog>::iterator statLogItem1;
		list<statLog>::iterator statLogItem2;
		for(funcItem=funcList.begin(); funcItem != funcList.end(); funcItem++)
		{
			string strFunc = *funcItem;
			statLogItem.pFunc = strFunc;
			statLogItem.pDesc = "";
			statLogItem.pTimes = 0;
			statLogItem.pAverTime = 0;
			//统计
			int iTimes=0, iSum=0;
			for(RecordItem=RecordList.begin(); RecordItem != RecordList.end(); RecordItem++)
			{
				if(RecordItem->sHitPro == strProgram && RecordItem->sHitFunc == strFunc)
				{
					statLogItem.pDesc = RecordItem->sDesc;
					iTimes += 1;
					iSum += RecordItem->sHitInterval;
				}		
			}
			statLogItem.pTimes = iTimes;
			if(iTimes != 0)
			{
				statLogItem.pAverTime = iSum / iTimes;
			}
			size_t ListSize = statiLogList.size();
			if(ListSize == 0)
			{
				statiLogList.push_back(statLogItem);
			}
			else
			{
				//直接插入排序(非递增) 
				//	 Key1: 平均执行时间(0.1毫秒)
				//	 Key2: 点击次数 	
				bool bInsert = true;   //是否插入比所有记录小的记录
				statLogItem2 = statiLogList.end();
				if(strKeySort == m_szAverTime)     //Key1
				{
					for(statLogItem1=statiLogList.begin(); statLogItem1 != statLogItem2; statLogItem1++)
					{
						if(statLogItem.pAverTime > statLogItem1->pAverTime)
						{
							statiLogList.insert(statLogItem1,statLogItem);
							bInsert = false;
							break;
						}
						if(statLogItem.pAverTime == statLogItem1->pAverTime)
						{
							if(statLogItem.pTimes >= statLogItem1->pTimes)
							{
								statiLogList.insert(statLogItem1,statLogItem);
								bInsert = false;
								break;
							}
						}
					}
					if(bInsert)
						statiLogList.push_back(statLogItem);
				}
				else if(strKeySort == m_szHitTimes)  //Key2  
				{
					for(statLogItem1=statiLogList.begin(); statLogItem1 != statLogItem2; statLogItem1++)
					{
						if(statLogItem.pTimes > statLogItem1->pTimes)
						{
							statiLogList.insert(statLogItem1,statLogItem);
							bInsert = false;
							break;
						}
						if(statLogItem.pTimes == statLogItem1->pTimes)
						{
							if(statLogItem.pAverTime >= statLogItem1->pAverTime)
							{
								statiLogList.insert(statLogItem1,statLogItem);
								bInsert = false;
								break;
							}
						}
					}
					if(bInsert)
						statiLogList.push_back(statLogItem);	
				}
			}
		}
		funcList.clear();
	}
	ProList.clear();
}

void CHitLog::ShowHideHelp()
{
	if(m_pQueryTable)
		m_pQueryTable->ShowOrHideHelp();
}

/////////////
void CHitLog::refresh()
{
	LogList1.clear();
	staLogList.clear();
	if(m_cProgram)
	{
		m_cProgram->clear();
		m_cProgram->addItem(m_szAll);
		//从hitlog.ini获取程序列表
		list<string> keylist;
		list<string>::iterator keyitem;
		string strProgram;
		if(GetIniFileSections(keylist, "hitlog.ini"))
		{
			ListSort(keylist);
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
			{
				m_cProgram->addItem((*keyitem));
			}
			keylist.clear();
		}
	}	

	if(m_pStatisticTable)
	{
		m_pStatisticTable->GeDataTable()->clear();
		m_pStatisticTable->HideNullTip();
		m_pStatisticTable->pSelReverse->setText(m_szReocrdIni);
	}

	if(m_pListTable)
	{
		m_pListTable->GeDataTable()->clear();
		m_pListTable->HideNullTip();
		m_pListTable->pSelReverse->setText(m_szReocrdIni);
	}

	if(m_cChangePage)
	{
		m_cChangePage->clear();
		m_cChangePage->addItem("0");
	}
}

/////////////
void CHitLog::loadString()
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_UserHitLog",m_szMainTitle);
			FindNodeValue(ResNode,"IDS_HitProgram",m_szProgram);
			FindNodeValue(ResNode,"IDS_HitProgramHelp",m_szProgramHelp);
			FindNodeValue(ResNode,"IDS_HitFunc",m_szFunc);
			FindNodeValue(ResNode,"IDS_HitFuncHelp",m_szFuncHelp);
			FindNodeValue(ResNode,"IDS_Start_Time1",m_szStartTime);
			FindNodeValue(ResNode,"IDS_End_Time2",m_szEndTime);
			FindNodeValue(ResNode,"IDS_Log_StartTime_Help",m_szStartTimeHelp);
			FindNodeValue(ResNode,"IDS_Log_EndTime_Help",m_szEndTimeHelp);
			FindNodeValue(ResNode,"IDS_Operate_User_Name",m_szUserName);
			FindNodeValue(ResNode,"IDS_Log_UserName_Help",m_szUserNameHelp);
			FindNodeValue(ResNode,"IDS_Query",m_szQuery);
			FindNodeValue(ResNode,"IDS_All",m_szAll);
			FindNodeValue(ResNode,"IDS_Hit_Description",m_szDes);
			FindNodeValue(ResNode,"IDS_Flag",m_szFlag);
			FindNodeValue(ResNode,"IDS_HitInterval",m_szInterval);
			FindNodeValue(ResNode,"IDS_HitTime",m_szTime);
			FindNodeValue(ResNode,"IDS_HitTimes",m_szHitTimes);
			FindNodeValue(ResNode,"IDS_HitAverTime",m_szAverTime);
			FindNodeValue(ResNode,"IDS_LogList",m_szLogList);	
			FindNodeValue(ResNode,"IDS_LogStatisticsList",m_szLogStatisticList);
			FindNodeValue(ResNode,"IDS_Hit_Log_Null",m_szLogNull);
			FindNodeValue(ResNode,"IDS_Back",m_szPrevious);
			FindNodeValue(ResNode,"IDS_Forward",m_szNext);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Ini",m_szReocrdIni); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",m_szPage); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",m_szPageCount); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",m_szRecordCount); 
			FindNodeValue(ResNode,"IDS_Generate_Excel_Table",m_szExport);
			FindNodeValue(ResNode,"IDS_DownloadList",m_szDownLoad);
			FindNodeValue(ResNode,"IDS_Close",m_szConfirm);
			FindNodeValue(ResNode,"IDS_Change_Page_Front",m_szPageFront);
			FindNodeValue(ResNode,"IDS_Change_Page_Back",m_szPageBack);
			FindNodeValue(ResNode,"IDS_SorKey",m_szKey);
			FindNodeValue(ResNode,"IDS_SorKeyHelp",m_szKeyHelp);
		}
		CloseResource(objRes);
	}
}


/////////////////////////////
//添加客户端脚本变量
void CHitLog::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}
CHitLog::~CHitLog(void)
{
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
	app.setTitle("UserHitLog");
 	CHitLog setform(app.root());
	app.setBodyAttribute("class='workbody' ");
	app.exec();
}
int main(int argc, char *argv[])
{
    func p = usermain;
	if (argc == 1) 
    {
		WebSession s("25", false);
        s.start(p);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }
    return 0;
}