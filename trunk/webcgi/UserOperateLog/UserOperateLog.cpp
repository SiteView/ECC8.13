#include ".\useroperatelog.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"


#include "..\svtable\FlexTable.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\WSVButton.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"

#include "WApplication"
#include "WebSession.h"
#include <WText>
#include <WComboBox>
#include <WPushButton>
#include <WLength>
#include <WLineEdit>
#include <list>



using namespace std;
using namespace svutil;

//一页显示50条记录
#define OnePageShowRecord 50

CUserOperateLog::CUserOperateLog(WContainerWidget *parent): 
	WContainerWidget(parent)
{
	RecordsList.clear();
	RecordsListItem = RecordsList.begin();
	mNullTable = NULL;
	loadString();

	nCurPage = 0;
	nTotalPage = 0;
	nPageCount = 30;

	ShowMainTable();
}

CUserOperateLog::~CUserOperateLog(void)
{
}

void CUserOperateLog::ShowHelp()
{
	pQueryTable->ShowOrHideHelp();
}

/////////////
void CUserOperateLog::ShowMainTable()
{

	strListHeights = "";
	strListPans = "";
	strListTitles = "";

	pMainTable = new WSVMainTable(this,m_szMainTitle,true);

	if(pMainTable->pHelpImg)
	{
		connect(pMainTable->pHelpImg,SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}
	
	pQueryTable = new WSVFlexTable(pMainTable->GetContentTable()->elementAt(1,0), AlertSel ,m_szMainTitle);	

	if(pQueryTable->GetContentTable() != NULL)	
	{
		pQueryTable->InitTable();

		pQueryTable->AppendRows();
		//用户
		m_cUserName = new WComboBox(pQueryTable->AppendRowsContent(0 ,0, 2, m_szUserName, m_szUserNameHelp, ""));
		m_cUserName->setStyleClass("input_text");
		m_cUserName->addItem(m_szAll);
		std::list<string> keylist;
		std::list<string>::iterator keyitem;
		string strLoginName;
		//从ini获取用户列表
		if(GetIniFileSections(keylist, "user.ini"))
		{
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
			{
				strLoginName = GetIniFileString((*keyitem), "LoginName", "", "user.ini");
				m_cUserName->addItem(strLoginName);
			}
			keylist.clear();
		}

		//操作对象
		m_cOperateObject = new WComboBox(pQueryTable->AppendRowsContent(0, 1, 2, m_szOperateObj, m_szOperateObjHelp, ""));
		m_cOperateObject->setStyleClass("input_text");
		m_cOperateObject->addItem(m_szAll);
		list<string> AllList;
		list<string>::iterator ListItem;
		if(	m_pLog.QueryAllOperateObject(AllList))
		{
			for(ListItem = AllList.begin(); ListItem != AllList.end(); ListItem++)
			{
				string strTemp = *ListItem;
				m_cOperateObject->addItem(strTemp);
			}
			AllList.clear();
		}

		pQueryTable->AppendRows();
		//开始时间
		m_EStartTime = new WLineEdit("", pQueryTable->AppendRowsContent(1, 0, 2, m_szStartTime, m_szStartTimeHelp, ""));	
		m_EStartTime->setStyleClass("input_text");
		TTime curTime = TTime::GetCurrentTimeEx();
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		m_EStartTime->setText(curTime.Format());
		strcpy(m_EStartTime->contextmenu_ , "onFocus=\"calendar()\"");

		m_EEndTime = new WLineEdit("", pQueryTable->AppendRowsContent(1, 1, 2 , m_szEndTime, m_szEndTimeHelp, ""));	
		m_EEndTime->setStyleClass("input_text");
		curTime = TTime::GetCurrentTimeEx();
		m_EEndTime->setText(curTime.Format());
		strcpy(m_EEndTime->contextmenu_ , "onFocus=\"calendar()\"");

		pQueryTable->AppendRows();
		m_cOperateType = new WComboBox(pQueryTable->AppendRowsContent(2, 0 ,1 , m_szOperateType, m_szOperateTypeHelp, ""));
		m_cOperateType->setStyleClass("input_text");
		m_cOperateType->addItem(m_szAll);
		if(	m_pLog.QueryAllOperateType(AllList))
		{
			for(ListItem = AllList.begin(); ListItem != AllList.end(); ListItem++)
			{
				string strTemp = *ListItem;
				m_cOperateType->addItem(strTemp);
			}
			AllList.clear();
		}
	}

	if(pQueryTable->GetActionTable()!=NULL)
	{
		pQueryTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		WSVButton *pQuery = new WSVButton(pQueryTable->GetActionTable()->elementAt(0,1),m_szQuery,"button_bg_m_black.png","",true);	
		connect(pQuery, SIGNAL(clicked()), "showbar();" ,this, SLOT(LogQuery()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	}

	pUserListTable = new WSVFlexTable( pMainTable->GetContentTable()->elementAt(2,0),List,"");

	pUserListTable->SetDivId("listpan1");
	if(pUserListTable->GetContentTable()!=NULL)
	{
		strListHeights += "300";
		strListHeights += ",";
		strListPans += pUserListTable->GetDivId();
		strListPans += ",";
		strListTitles +=  pUserListTable->dataTitleTable->formName();
		strListTitles += ",";
		
		pUserListTable->AppendColumn("",WLength(2,WLength::Pixel));
		pUserListTable->SetDataRowStyle("table_data_grid_item_img");
		pUserListTable->AppendColumn(m_szUserName,WLength(10,WLength::Percentage));
		pUserListTable->SetDataRowStyle("table_data_grid_item_img");
		pUserListTable->AppendColumn(m_szOperateObj,WLength(15,WLength::Percentage));
		pUserListTable->SetDataRowStyle("table_data_grid_item_text");
		pUserListTable->AppendColumn(m_szOperateType,WLength(15,WLength::Percentage));
		pUserListTable->SetDataRowStyle("table_data_grid_item_img");
		pUserListTable->AppendColumn(m_szOperateTime,WLength(20,WLength::Percentage));
		pUserListTable->SetDataRowStyle("table_data_grid_item_text");
		pUserListTable->AppendColumn(m_szOperateObjInfo,WLength(30,WLength::Percentage));
		pUserListTable->SetDataRowStyle("table_data_grid_item_text");
	}

	if(pUserListTable->GetActionTable() != NULL)
	{
		pUserListTable->AddStandardSelLink(strBack,strForward,strReocrdIni);
		connect(pUserListTable->pSelAll, SIGNAL(clicked()), this, SLOT(LogBack()));		
		connect(pUserListTable->pSelNone, SIGNAL(clicked()), this, SLOT(LogForward()));
		pUserListTable->pSelReverse->setStyleClass("");
	}

	pUserListTable->SetNullTipInfo(m_szLogNull);
	
	emit ShowHelp();

	pTranslateBtn = new WPushButton("Translate",this);
	pExChangeBtn = new WPushButton("Refresh",this);

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}
}
/////////////
void CUserOperateLog::LogForward()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserOperateLog";
	LogItem.sHitFunc = "LogForward";
	LogItem.sDesc = strForward;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	nCurPage++;

	if(nCurPage >= nTotalPage)
		nCurPage = nTotalPage;
	//
	RefreshList();

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

}
/////////////

void CUserOperateLog::LogBack()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserOperateLog";
	LogItem.sHitFunc = "LogBack";
	LogItem.sDesc = strBack;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	nCurPage--;

	//
	if(nCurPage < 1)
		nCurPage = 1;

	//
	RefreshList();

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

/////////////
void CUserOperateLog::AddLogColumn(WTable* pContain)
{
	int iColNum = pContain->numColumns();
	new WText("&nbsp;" , pContain->elementAt(0,iColNum));
	iColNum ++;
	new WText(m_szUserName , pContain->elementAt(0,iColNum));
	iColNum ++;
	new WText(m_szOperateObj , pContain->elementAt(0,iColNum));
	iColNum ++;
	new WText(m_szOperateType , pContain->elementAt(0,iColNum));
	iColNum ++;
	new WText(m_szOperateTime , pContain->elementAt(0,iColNum));
	iColNum ++;
	new WText(m_szOperateObjInfo , pContain->elementAt(0,iColNum));
	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}
/////////////
bool ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps)
{
    char * token = NULL;
    // duplicate string
	char * cp = ::strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        if (pSVSeps) // using separators
            token = strtok( pTmp , pSVSeps);
        else // using separators
			return false;
            //token = strtok( pTmp, chDefSeps);
        // every field
        while( token != NULL )
        {
            //triml(token);
            //AddListItem(token);
			pTokenList.push_back(token);
            // next field
            if (pSVSeps)
                token = strtok( NULL , pSVSeps);
            else
               return false;
				//token = strtok( NULL, chDefSeps);
        }
        // free memory
        free(cp);
    }
    return true;
}
/////////////
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

/////////////
void CUserOperateLog::LogQuery()
{
 	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "UserOperateLog";
	LogItem.sHitFunc = "LogQuery";
	LogItem.sDesc = m_szQuery;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	RecordsList.clear();

	string strUserName, strStartTime, strEndTime, strOType, strOObj;

	strUserName = m_cUserName->currentText();
   
	strStartTime = m_EStartTime->text();
	strEndTime = m_EEndTime->text();
	TTime startTime, endTime;
	startTime = MakeTTime(strStartTime);
	if(strEndTime.empty())
		endTime = TTime::GetCurrentTimeEx();
	else
		endTime = MakeTTime(strEndTime);

	strOType = m_cOperateType->currentText();
	strOObj = m_cOperateObject->currentText();

	m_pLog.QueryOperateRecord(strUserName, strOObj, startTime, endTime, strOType, RecordsList);

	if(RecordsList.size() % nPageCount  > 0)
	{
		nTotalPage = RecordsList.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = RecordsList.size() / nPageCount;
		bDivide = true;
	}

	if(nTotalPage > 0)
		nCurPage = 1;
	else
		nCurPage = 0;

	RefreshList();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	m_szForwardORBack = 0;
	WebSession::js_af_up = "hiddenbar()";
}

void CUserOperateLog::RefreshList()
{
	//pAlertRightMap.clear();
	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	//清空列表里面的数据
	pUserListTable->GeDataTable()->clear();

	char tmpchar[10] = {0};
	string strTipInfo = strPage;	
	sprintf(tmpchar, "%d", nCurPage);
	strTipInfo += tmpchar;
	strTipInfo += strPageCount;
	sprintf(tmpchar, "%d", nTotalPage);
	strTipInfo += tmpchar;
	strTipInfo += strRecordCount;
	sprintf(tmpchar, "%d", RecordsList.size());
	strTipInfo += tmpchar;
	pUserListTable->pSelReverse->setText(strTipInfo);

	if(RecordsList.size() <= 0)
	{
		pUserListTable->ShowNullTip();
		return;
	}
	else
	{
		pUserListTable->HideNullTip();
	}

	list<OperateLogItem>::iterator item;

	int iRow = 1;	
	int index = 0;
	int nPage = 0;
	for(item = RecordsList.begin(); item != RecordsList.end(); item ++)
	{
		nPage = index / nPageCount;
		nPage += 1;
		if(!bDivide && nCurPage == nTotalPage)
		{
			if(nPage == nTotalPage)
			{
				AddLogItem(iRow,item->sUserName,item->sOperateObject,item->sOperateType,item->sOperateTime,item->sOperateObjectInfo);
				iRow ++;
			}
		}
		else if(nPage == nCurPage)
		{
			AddLogItem(iRow,item->sUserName,item->sOperateObject,item->sOperateType,item->sOperateTime,item->sOperateObjectInfo);
			iRow ++;
		}
		else
		{

		}

		index ++;
	}

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}
}

void CUserOperateLog::AddLogItem(int iRow, string userName, string operObj, string operType, string operTime, string operObjInfo)
{
	pUserListTable->InitRow(iRow);

	new WText("&nbsp;" , pUserListTable->GeDataTable()->elementAt(iRow,0));

	new WText(userName , pUserListTable->GeDataTable()->elementAt(iRow,2));

	new WText(operObj , pUserListTable->GeDataTable()->elementAt(iRow,4));

	pUserListTable->GeDataTable()->elementAt(iRow,6)->setContentAlignment(AlignCenter);
	new WText(operType, pUserListTable->GeDataTable()->elementAt(iRow,6));

	new WText(operTime, pUserListTable->GeDataTable()->elementAt(iRow,8));

	new WText(operObjInfo, pUserListTable->GeDataTable()->elementAt(iRow,10));
}
/////////////
void CUserOperateLog::refresh()
{
	
}
/////////////
void CUserOperateLog::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_User_Operate_Log",m_szMainTitle);
			FindNodeValue(ResNode,"IDS_Operate_User_Name",m_szUserName);
			FindNodeValue(ResNode,"IDS_Operate_Object",m_szOperateObj);
			FindNodeValue(ResNode,"IDS_Operate_Type",m_szOperateType);
			FindNodeValue(ResNode,"IDS_Operate_Time",m_szOperateTime);
			FindNodeValue(ResNode,"IDS_Operate_Object_Info",m_szOperateObjInfo);
			FindNodeValue(ResNode,"IDS_Start_Time1",m_szStartTime);
			FindNodeValue(ResNode,"IDS_End_Time2",m_szEndTime);
			FindNodeValue(ResNode,"IDS_Query",m_szQuery);
			FindNodeValue(ResNode,"IDS_All",m_szAll);
			FindNodeValue(ResNode,"IDS_Operate_Log_Null",m_szLogNull);
			FindNodeValue(ResNode,"IDS_Forward",strForward);
			FindNodeValue(ResNode,"IDS_Back",strBack);
			FindNodeValue(ResNode,"IDS_Log_UserName_Help",m_szUserNameHelp);
			FindNodeValue(ResNode,"IDS_Log_OperateObj_Help",m_szOperateObjHelp);
			FindNodeValue(ResNode,"IDS_Log_StartTime_Help",m_szStartTimeHelp);
			FindNodeValue(ResNode,"IDS_Log_EndTime_Help",m_szEndTimeHelp);
			FindNodeValue(ResNode,"IDS_Log_OperateType_Help",m_szOperateTypeHelp);

			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Ini",strReocrdIni); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",strPage); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",strPageCount); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",strRecordCount); 
		}
		CloseResource(objRes);
	}
}

//添加客户端脚本变量
void CUserOperateLog::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

//添加客户端脚本变量
void AddJsParam(const std::string name, const std::string value,  WContainerWidget * parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}


typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void usermain(int argc, char * argv[])
{
	

    WApplication app(argc, argv);
	app.setTitle("UserOperateLog");

	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",app.root());
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
	new WText("<div id='view_panel' class='panel_view'>", app.root());

    CUserOperateLog setform(app.root());
	setform.appSelf = &app;
	app.setBodyAttribute("class='workbody' ");

	new WText("</div>", app.root());

	AddJsParam("uistyle", "viewpan", app.root());
	AddJsParam("fullstyle", "true", app.root());
	AddJsParam("bGeneral", "false", app.root());
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());
	app.exec();
}
int main(int argc, char *argv[])
{
    func p = usermain;
    //WriteRightTpl();
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