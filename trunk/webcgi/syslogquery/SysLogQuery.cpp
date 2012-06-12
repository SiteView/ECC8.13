//#include <time.h>
#include ".\SysLogQuery.h"
//#include "../../kennel/svdb/svapi/libutil/Time.h"

#include "websession.h"
#include <WApplication>
#include <WCheckBox>
#include <WComboBox>
#include <WText>
#include <WLineEdit>
#include <WSelectionBox>
#include <WButtonGroup>
#include <WRadioButton>
#include "WSignalMapper"
#include <WScrollArea>
#include <SVTable.h>
#include <WButtonTab>
#include <WImage>

#include "..\svtable\FlexTable.h"
#include "..\svtable\MainTable.h"

#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVButton.h"
#include "../../monitor/base/regx/RegularExpressionClass.h"


//m_AlertRuleAdd, m_AlertRuleDel, m_AlertRuleEdit, m_alertLogs,
bool GetUserRight(string strRight)
{
	bool bRight = false;
	string strSection = GetWebUserID();
	
	//管理员则有所有权限
	if(GetIniFileInt(strSection, "nAdmin", -1, "user.ini") != -1)
		return true;

	if(GetIniFileInt(strSection, strRight, 0, "user.ini") == 1)
		bRight = true;
	else
		bRight = false;
	return bRight;
	//return true;
}

//
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

//
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

//
CSysLogQuery::CSysLogQuery(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Facility
	strFacility0 = "kernel messages";
	strFacility1 = "user-level messages";
	strFacility2 = "mail system";
	strFacility3 = "system daemons";
	strFacility4 = "security/authorization messages";
	strFacility5 = "messages generated internally by syslogd";
	strFacility6 = "line printer subsystem";
	strFacility7 = "network news subsystem";
	strFacility8 = "UUCP subsystem";
	strFacility9 = "clock daemon";
	strFacility10 = "security/authorization messages";
	strFacility11 = "FTP daemon";
	strFacility12 = "NTP subsystem";
	strFacility13 = "log audit";
	strFacility14 = "log alert";
	strFacility15 = "clock daemon";
	strFacility16 = "local use 0  (local0)";
	strFacility17 = "local use 1  (local1)";
	strFacility18 = "local use 2  (local2)";
	strFacility19 = "local use 3  (local3)";
	strFacility20 = "local use 4  (local4)";
	strFacility21 = "local use 5  (local5)";
	strFacility22 = "local use 6  (local6)";
	strFacility23 = "local use 7  (local7)";

	//Severities
	strSeverities0 = "Emergency";
	strSeverities1 = "Alert";
	strSeverities2 = "Critical";
	strSeverities3 = "Error";
	strSeverities4 = "Warning";
	strSeverities5 = "Notice";
	strSeverities6 = "Informational";
	strSeverities7 = "Debug";

	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_SysLogQuery",strSysLogTiltle);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Forward",strForward);
			FindNodeValue(ResNode,"IDS_Back",strBack);
			FindNodeValue(ResNode,"IDS_HSysLogMsgLabel",strHSysLogMsgLabel);
			FindNodeValue(ResNode,"IDS_HSysLogTimeLabel",strHSysLogTimeLabel);
			FindNodeValue(ResNode,"IDS_HSysLogIpLabel",strHSysLogIpLabel);
			FindNodeValue(ResNode,"IDS_HSysLogFacilityLabel",strHSysLogFacilityLabel);
			FindNodeValue(ResNode,"IDS_HSysLogSeveritiesLabel",strHSysLogSeveritiesLabel);
			FindNodeValue(ResNode,"IDS_SysLogMsgLabel",strSysLogMsgLabel);
			FindNodeValue(ResNode,"IDS_SysLogIpLabel",strSysLogIpLabel);
			FindNodeValue(ResNode,"IDS_SysLogFacilityLabel",strSysLogFacilityLabel);
			FindNodeValue(ResNode,"IDS_SysLogSeveritiesLabel",strSysLogSeveritiesLabel);
			FindNodeValue(ResNode,"IDS_Start_Time1",strStartTimeLabel);
			FindNodeValue(ResNode,"IDS_End_Time2",strEndTimeLabel);
			FindNodeValue(ResNode,"IDS_SysLogMsgDes",strSysLogMsgDes);
			FindNodeValue(ResNode,"IDS_SysLogIpDes",strSysLogIpDes);
			FindNodeValue(ResNode,"IDS_SysLogFacilityLabel",strSysLogFacilityDes);
			FindNodeValue(ResNode,"IDS_SysLogSeveritiesLabel",strSysLogSeveritiesDes);
			FindNodeValue(ResNode,"IDS_SysLog_StartTime",strStartTimeDes);
			FindNodeValue(ResNode,"IDS_SysLog_EndTime",strEndTimeDes);
			FindNodeValue(ResNode,"IDS_Query",strQueryBtn); 

			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Ini",strReocrdIni); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",strPage); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",strPageCount); 
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",strRecordCount); 
			FindNodeValue(ResNode,"IDS_No_SysLog",strNoSortRecord); 
		}
		CloseResource(objRes);
	}

	nCurPage = 0;
	nTotalPage = 0;
	nPageCount = 30;

	ShowMainTable();
}

//
CSysLogQuery::~CSysLogQuery(void)
{
	
}

void CSysLogQuery::ShowHelp()
{
	m_pSysLogTable->ShowOrHideHelp();
}

//初始化主界面
void CSysLogQuery::ShowMainTable()
{

	m_pMainTable = new WSVMainTable(this,strSysLogTiltle,true);

	if (m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg,SIGNAL(click()),this,SLOT(ShowHelp()));
	}

	//m_pSysLogTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(0,0),Query,strSysLogTiltle);
	m_pSysLogTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(0,0),Query,"查询参数");
	if (m_pSysLogTable->GetContentTable() != NULL)
	{
		m_pSysLogTable->AppendRows();
		//用户
		pSysLogMsg = new WLineEdit("", m_pSysLogTable->AppendRowsContent(0 ,0, 2, strSysLogMsgLabel, strSysLogMsgDes, ""));
		pSysLogMsg->setStyleClass("input_text");
		//操作对象
		pSysLogIp = new WLineEdit("",m_pSysLogTable->AppendRowsContent(0, 1, 2, strSysLogIpLabel, strSysLogIpDes, ""));
		pSysLogIp->setStyleClass("input_text");
		
		m_pSysLogTable->AppendRows();
		//开始时间
		pSysLogStartTime = new WLineEdit("", m_pSysLogTable->AppendRowsContent(1, 0, 2, strStartTimeLabel, strStartTimeDes, ""));	
		pSysLogStartTime->setStyleClass("input_text");
		TTime curTime = TTime::GetCurrentTimeEx();
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		pSysLogStartTime->setText(curTime.Format());
		strcpy(pSysLogStartTime->contextmenu_ , "onFocus=\"calendar()\"");

		pSysLogEndTime = new WLineEdit("", m_pSysLogTable->AppendRowsContent(1, 1, 2 , strEndTimeLabel, strEndTimeDes, ""));	
		pSysLogEndTime->setStyleClass("input_text");
		curTime = TTime::GetCurrentTimeEx();
		pSysLogEndTime->setText(curTime.Format());
		strcpy(pSysLogEndTime->contextmenu_ , "onFocus=\"calendar()\"");

		m_pSysLogTable->AppendRows();
		WTable *pFacilityListTable = new WTable(m_pSysLogTable->AppendRowsContent(2, 0, 2 , strSysLogFacilityLabel, strSysLogFacilityDes, ""));
		pFacility = new WLineEdit("", pFacilityListTable->elementAt(0, 0));
		pFacility->hide();
		AddJsParam("pFacility", pFacility->formName());
		pFacilityListTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
		new WText("<div id=Facilitylist style='width:200px;height:100px;overflow-y:scroll;overflow-x:hidden;border:1px solid #666666;'></div>", pFacilityListTable->elementAt(0, 1));		

		WTable *pSeveritiesListTable = new WTable(m_pSysLogTable->AppendRowsContent(2, 1, 2 , strSysLogSeveritiesLabel, strSysLogSeveritiesDes, ""));	
		pSeverities = new WLineEdit("", pSeveritiesListTable->elementAt(0, 0));
		pSeverities->hide();
		AddJsParam("pSeverities", pSeverities->formName());
		pSeveritiesListTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
		new WText("<div id='Severitieslist' style='width:200px;height:100px;overflow-y:scroll;overflow-x:hidden;border:1px solid #666666;'></div>", pSeveritiesListTable->elementAt(0, 1));
	}

	if (m_pSysLogTable->GetActionTable() != NULL)
	{

		WPushButton * pQueryBtn1 = new WPushButton(strQueryBtn, (WContainerWidget *)m_pSysLogTable->GetActionTable()->elementAt(0,1));	
		connect(pQueryBtn1, SIGNAL(clicked()), this, SLOT(SysLogQuery()));
		pQueryBtn1->hide();
		AddJsParam("pQueryBtn", pQueryBtn1->getEncodeCmd("xclicked()"));

		m_pSysLogTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		WSVButton *pQueryBtn = new WSVButton(m_pSysLogTable->GetActionTable()->elementAt(0,1),strQueryBtn,"button_bg_m_black.png","",true);	
		std::string strFocus = "setFacility();setSeverities();showbar();";
		WObject::connect(pQueryBtn, SIGNAL(clicked()),  strFocus.c_str(), WObject::ConnectionType::JAVASCRIPT);	

		new WText("<SCRIPT language='JavaScript' src='/Facilitylist.js'></SCRIPT>", this);		
		new WText("<SCRIPT language='JavaScript' src='/Severitieslist.js'></SCRIPT>", this);

	}

	//m_pSysLogListTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0),List,"");
	m_pSysLogListTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0),List,"查询结果");
	m_pSysLogListTable->SetDivId("listpan");
	if (m_pSysLogListTable->GetContentTable() != NULL)
	{
		strListHeights += "300";
		strListHeights += ",";
		strListPans += m_pSysLogListTable->GetDivId();
		strListPans += ",";
		strListTitles +=  m_pSysLogListTable->dataTitleTable->formName();
		strListTitles += ",";

		m_pSysLogListTable->AppendColumn("",WLength(2,WLength::Pixel));
		m_pSysLogListTable->SetDataRowStyle("table_data_grid_item_img");
		m_pSysLogListTable->AppendColumn(strHSysLogTimeLabel,WLength(15,WLength::Percentage));
		m_pSysLogListTable->SetDataRowStyle("table_data_grid_item_img");
		m_pSysLogListTable->AppendColumn(strHSysLogIpLabel,WLength(15,WLength::Percentage));
		m_pSysLogListTable->SetDataRowStyle("table_data_grid_item_img");
		m_pSysLogListTable->AppendColumn(strHSysLogFacilityLabel,WLength(10,WLength::Percentage));
		m_pSysLogListTable->SetDataRowStyle("table_data_grid_item_text");
		m_pSysLogListTable->AppendColumn(strHSysLogSeveritiesLabel,WLength(10,WLength::Percentage));
		m_pSysLogListTable->SetDataRowStyle("table_data_grid_item_text");
		m_pSysLogListTable->AppendColumn(strHSysLogMsgLabel,WLength(50,WLength::Percentage));
		m_pSysLogListTable->SetDataRowStyle("table_data_grid_item_img");
	}

	if(m_pSysLogListTable->GetActionTable() != NULL)
	{

		m_pSysLogListTable->AddStandardSelLink(strBack,strForward,strReocrdIni);
		connect(m_pSysLogListTable->pSelAll, SIGNAL(clicked()), this, SLOT(SysLogBack()));		
		connect(m_pSysLogListTable->pSelNone, SIGNAL(clicked()), this, SLOT(SysLogForward()));
		m_pSysLogListTable->pSelReverse->setStyleClass("");

	}

	m_pSysLogListTable->SetNullTipInfo(strNoSortRecord);
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


//
void CSysLogQuery::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/SysLogQuery.exe?'\",1250);  ";
	appSelf->quit();
}
//
void CSysLogQuery::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "SysLogQueryRes";
	WebSession::js_af_up += "')";
}

//加日志列表标题
void CSysLogQuery::AddSysLogColum(WTable* pContain)
{
	new WText("&nbsp;", pContain->elementAt(0, 0));
	new WText(strHSysLogTimeLabel, pContain->elementAt(0, 1));
	new WText(strHSysLogIpLabel, pContain->elementAt(0, 2));
	new WText(strHSysLogFacilityLabel, pContain->elementAt(0, 3));
	new WText(strHSysLogSeveritiesLabel, pContain->elementAt(0, 4));
	new WText(strHSysLogMsgLabel, pContain->elementAt(0, 5));

	//pContain->elementAt(0, 0)->resize(WLength(60), WLength(100,WLength::Percentage));
	//pContain->elementAt(0, 1)->resize(WLength(60), WLength(100,WLength::Percentage));
	//pContain->elementAt(0, 2)->resize(WLength(60), WLength(100,WLength::Percentage));
	//pContain->elementAt(0, 3)->resize(WLength(60), WLength(100,WLength::Percentage));
	//pContain->elementAt(0, 4)->resize(WLength(60), WLength(100,WLength::Percentage));
	//pContain->elementAt(0, 5)->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}



//
void  CSysLogQuery::AddSysLogItemNew(int numRow, string strSysLogTime, string strSysLogIp, string strSysLogMsg, int nFacility, int nSeverities)
{
	m_pSysLogListTable->InitRow(numRow);
	
	new WText("",m_pSysLogListTable->GeDataTable()->elementAt(numRow , 0));

	//WImage * Image;	
	//switch(nSeverities)
	//{
	//case 0:
	//case 1:
	//case 2:
	//case 3:
	//	Image = new WImage("../icons/small_error.gif", (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 2));
	//	break;
	//case 4:
	//	Image = new WImage("../icons/small_warnning.gif", (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 2));
	//	break;
	//case 5:
	//case 6:
	//case 7:
	//	Image = new WImage("../icons/small_normal.gif", (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 2));
	//	break;
	//default:
	//	break;
	//}
	WText * pTmpText;

	m_pSysLogListTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
	pTmpText = new WText(strSysLogTime, (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 2));
	
	m_pSysLogListTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);
	pTmpText = new WText(strSysLogIp, (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 4));
	
	m_pSysLogListTable->GeDataTable()->elementAt(numRow , 6)->setContentAlignment(AlignCenter);
	pTmpText = new WText(GetFicilityStrFormInt(nFacility), (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 6));
	
	m_pSysLogListTable->GeDataTable()->elementAt(numRow , 8)->setContentAlignment(AlignCenter);
	pTmpText = new WText(GetSeveritiesStrFormInt(nSeverities), (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 8));
	
	m_pSysLogListTable->GeDataTable()->elementAt(numRow , 10)->setContentAlignment(AlignCenter);
	pTmpText = new WText(strSysLogMsg, (WContainerWidget*)m_pSysLogListTable->GeDataTable()->elementAt(numRow , 10));
}

//
void  CSysLogQuery::AddSysLogItem(string strSysLogTime, string strSysLogIp, string strSysLogMsg, int nFacility, int nSeverities)
{

	//生成界面
	int numRow = pSysLogListTable->numRows();

	pSysLogListTable->elementAt(numRow, 0)->resize(WLength(10), WLength(100,WLength::Percentage));
	pSysLogListTable->elementAt(numRow, 1)->resize(WLength(150), WLength(100,WLength::Percentage));
	pSysLogListTable->elementAt(numRow, 2)->resize(WLength(100), WLength(100,WLength::Percentage));
	pSysLogListTable->elementAt(numRow, 3)->resize(WLength(80), WLength(100,WLength::Percentage));
	pSysLogListTable->elementAt(numRow, 4)->resize(WLength(80), WLength(100,WLength::Percentage));
	//pSysLogListTable->elementAt(numRow, 5)->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));

	//WImage * Image;	
	//switch(nSeverities)
	//{
	//	case 0:
	//	case 1:
	//	case 2:
	//	case 3:
	//		 Image = new WImage("../icons/small_error.gif", (WContainerWidget*)pSysLogListTable->elementAt(numRow , 1));
	//		 break;
	//	case 4:
	//		 Image = new WImage("../icons/small_warnning.gif", (WContainerWidget*)pSysLogListTable->elementAt(numRow , 1));
	//		break;
	//	case 5:
	//	case 6:
	//	case 7:
	//		 Image = new WImage("../icons/small_normal.gif", (WContainerWidget*)pSysLogListTable->elementAt(numRow , 1));
	//		 break;
	//	default:
	//		 break;
	//}
	WText * pTmpText;
	pTmpText = new WText(strSysLogTime, (WContainerWidget*)pSysLogListTable->elementAt(numRow , 1));
	pTmpText->setStyleClass("myTextstyle");
	pTmpText = new WText(strSysLogIp, (WContainerWidget*)pSysLogListTable->elementAt(numRow , 2));
	pTmpText->setStyleClass("myTextstyle");
	pTmpText = new WText(GetFicilityStrFormInt(nFacility), (WContainerWidget*)pSysLogListTable->elementAt(numRow , 3));
	pTmpText->setStyleClass("myTextstyle");
	pTmpText = new WText(GetSeveritiesStrFormInt(nSeverities), (WContainerWidget*)pSysLogListTable->elementAt(numRow , 4));
	pTmpText->setStyleClass("myTextstyle");
	pTmpText = new WText(strSysLogMsg, (WContainerWidget*)pSysLogListTable->elementAt(numRow , 5));
	pTmpText->setStyleClass("myTextstyle");
}

//历史日志往前
void CSysLogQuery::SysLogForward()
{
	nCurPage++;
	
	if(nCurPage >= nTotalPage)
		nCurPage = nTotalPage;
	//
	RefreshList();
}

//历史日志往后
void CSysLogQuery::SysLogBack()
{
	nCurPage--;

	//
	if(nCurPage < 1)
		nCurPage = 1;

	//
	RefreshList();
}

//返回报警日志
void CSysLogQuery::SysLogReturnBtn()
{
	//
	//显示列表界面	
}

//
string CSysLogQuery::GetFicilityStrFormInt(int nFacility)
{
	string strFacility  = "";
	switch(nFacility)
	{
		case 0:
			strFacility = "Kernel";
			break;
		case 1:
			strFacility = "User";
			break;
		case 2:
			strFacility = "Mail";
			break;
		case 3:
			strFacility = "Daemon";
			break;
		case 4:
			strFacility = "Auth";
			break;
		case 5:
			strFacility = "Syslog";
			break;
		case 6:
			strFacility = "Lpr";
			break;
		case 7:
			strFacility = "News";
			break;
		case 8:
			strFacility = "UUCP";
			break;
		case 9:
			strFacility = "Cron";
			break;
		case 10:
			strFacility = "Security";
			break;
		case 11:
			strFacility = "FTP Daemon";
			break;
		case 12:
			strFacility = "NTP";
			break;
		case 13:
			strFacility = "Log audit";	
			break;
		case 14:
			strFacility = "Log alert";
			break;
		case 15:
			strFacility = "Clock Daemon";
			break;
		case 16:
			strFacility = "local0";
			break;
		case 17:
			strFacility = "local1";
			break;
		case 18:
			strFacility = "local2";
			break;
		case 19:
			strFacility = "local3";
			break;
		case 20:
			strFacility = "local4";
			break;
		case 21:
			strFacility = "local5";
			break;
		case 22:
			strFacility = "local6";
			break;
		case 23:
			strFacility = "local7";
			break;

		//case 0:
		//	strFacility = "kernel messages";
		//	break;
		//case 1:
		//	strFacility = "user-level messages";
		//	break;
		//case 2:
		//	strFacility = "mail system";
		//	break;
		//case 3:
		//	strFacility = "system daemons";
		//	break;
		//case 4:
		//	strFacility = "security/authorization messages";
		//	break;
		//case 5:
		//	strFacility = "messages generated internally by syslogd";
		//	break;
		//case 6:
		//	strFacility = "line printer subsystem";
		//	break;
		//case 7:
		//	strFacility = "network news subsystem";
		//	break;
		//case 8:
		//	strFacility = "UUCP subsystem";
		//	break;
		//case 9:
		//	strFacility = "clock daemon";
		//	break;
		//case 10:
		//	strFacility = "security/authorization messages";
		//	break;
		//case 11:
		//	strFacility = "FTP daemon";
		//	break;
		//case 12:
		//	strFacility = "NTP subsystem";
		//	break;
		//case 13:
		//	strFacility = "log audit";	
		//	break;
		//case 14:
		//	strFacility = "log alert";
		//	break;
		//case 15:
		//	strFacility = "clock daemon";
		//	break;
		//case 16:
		//	strFacility = "local use 0  (local0)";
		//	break;
		//case 17:
		//	strFacility = "local use 1  (local1)";
		//	break;
		//case 18:
		//	strFacility = "local use 2  (local2)";
		//	break;
		//case 19:
		//	strFacility = "local use 3  (local3)";
		//	break;
		//case 20:
		//	strFacility = "local use 4  (local4)";
		//	break;
		//case 21:
		//	strFacility = "local use 5  (local5)";
		//	break;
		//case 22:
		//	strFacility = "local use 6  (local6)";
		//	break;
		//case 23:
		//	strFacility = "local use 7  (local7)";
		//	break;
		default:
			break;
	}

	return strFacility;
}

//
string CSysLogQuery::GetSeveritiesStrFormInt(int nSeverities)
{
	string strSeverities = "";
	switch(nSeverities)
	{
		case 0:
			strSeverities = "Emergency";
			break;
		case 1:
			strSeverities = "Alert";
			break;
		case 2:
			strSeverities = "Critical";
			break;
		case 3:
			strSeverities = "Error";
			break;
		case 4:
			strSeverities = "Warning";
			break;
		case 5:
			strSeverities = "Notice";
			break;
		case 6:
			strSeverities = "Informational";
			break;
		case 7:
			strSeverities = "Debug";
			break;
		default:
			break;
	}

	return strSeverities;
}

//查询条件匹配
bool CSysLogQuery::IsCondMatch(int nCond, string strCondValue, int nCondValue)
{
	char tmpchar[10] = {0};
	sprintf(tmpchar, "%d", nCondValue);
	string strTmpCond = tmpchar;
	bool bMatch = false;
	switch(nCond)
	{
		case 1:
			//SysLogMsg
			if(strSysLogMsgCond.empty())
			{
				bMatch = true;
			}
			else
			{
				long lTotalLine, lMatches;
				string strmid = "", szResult = "";				
				
				//if(strCondValue.find(strSysLogMsgCond) != -1)
				if(ParserContent((char *)strCondValue.c_str(), lTotalLine, lMatches, (char *)strSysLogMsgCond.c_str(), (char *)strmid.c_str(), (char *)szResult.c_str()))
				{
					bMatch = true;
				}
			}
			break;
		case 2:
			//SysLogIp
			if(strSysLogIpCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue.find(strSysLogIpCond) != -1)
				{
					bMatch = true;
				}
			}
			break;
		case 3:
			//SysLogTime
			if(strStartTimeCond.empty() && strEndTimeCond.empty())
			{
				bMatch = true;
			}
			else
			{
				TTime condValueTime = MakeTTime(strCondValue.c_str());

				if(!strStartTimeCond.empty() && !strEndTimeCond.empty())
				{
					//OutputDebugString("!strStartTimeCond.empty() && !strEndTimeCond.empty()");
					//OutputDebugString(condValueTime.Format());
					//OutputDebugString(startTime.Format());
					//OutputDebugString(endTime.Format());
					if(condValueTime >= startTime && condValueTime <= endTime)
					{
						bMatch = true;
					}
				}
				else if(!strStartTimeCond.empty() && strEndTimeCond.empty())
				{
					if(condValueTime >= startTime)
					{
						bMatch = true;
					}				
				}
				else if(strStartTimeCond.empty() && !strEndTimeCond.empty())
				{
					if(condValueTime <= endTime)
					{
						bMatch = true;
					}				
				}
				else
				{
					
				}
			}
			break;
		case 4:
			//nFacility
			if(mapFacility.find(strTmpCond) != mapFacility.end())
			{
				bMatch = true;
			}
			break;
		case 5:
			//nSeveritiesCond
			if(mapSeverities.find(strTmpCond) != mapSeverities.end())
			{
				bMatch = true;
			}
			break;
		default:
			break;
	}

	return bMatch;
}

//
BOOL CSysLogQuery::ParserContent( char *  content,long &lTotalLine, long & lMatches ,char *matchstr,char *strmid,char * szResult )
{
	RegularExpression RegularExpressionObject;
	char * ca=NULL;
	char * cb=NULL;
	char * tmpBuffer;

	ca =content;
	puts(ca);
	BOOL bFlag = FALSE;
	

	if(*matchstr)
	{
		RegularExpressionObject.FormatType = RegularExpression::FormatTypeAll;
		RegularExpressionObject.LocaleModel = RegularExpression::LocaleModelCpp;
		RegularExpressionObject.Expression =matchstr;
		if (RegularExpressionObject.ParseExpression() != RegularExpression::REG_NOERROR)
		{
			strcpy(szResult,"error=表达式错误");
			return FALSE;
		}
	}

    //while(cb =strstr(ca,"\n"))
	{

		//if(ca != cb)
		{
			lTotalLine ++;
			
			if(*matchstr)
			{
				//tmpBuffer =(char *)malloc(cb-ca+2);
				//memset(tmpBuffer,0,cb-ca+2);
				//strncpy(tmpBuffer, ca, cb - ca+1);				
				//RegularExpressionObject.StringToMatch=tmpBuffer;
				RegularExpressionObject.StringToMatch=ca;
				if(RegularExpressionObject.Search())
				{
//					AddToLogFileLog(tmpBuffer, strmid);
					bFlag = TRUE;
					lMatches ++;
				}
				
				//free(tmpBuffer);
			}
			
			//if(cb-content+ 1>=strlen(content )) 
			//	break;
			//ca =cb+1;			
		}
		//else
		//{
		//	if(cb-content+ 1>=strlen(content )) break;
		//	ca =cb+1;
		//}
	}

	return bFlag;
	//return TRUE;		
}

//查询数据
void CSysLogQuery::QueryRecordSet(string strTableName)
{
	//有问题的， 时间判断
	//TTimeSpan ts(0,100,0,0);
	//RECORDSET rds=::QueryRecords(strTableName,ts);
	//TTime tm1;
	//TTime tm2 = TTime::GetCurrentTimeEx();
	//RECORDSET rds=::QueryRecords(strTableName,tm1, tm2);
	RECORDSET rds=::QueryRecords(strTableName,startTime, endTime);
	if(rds==INVALID_VALUE)
	{
		//OutputDebugString("Query failed");
		return ;
	}

	LISTITEM item;
	if(!::FindRecordFirst(rds,item))
	{
		//puts("Find list failed");
		return;
	}

	RECORD rdobj;
	while((rdobj=::FindNextRecord(item))!=INVALID_VALUE)
	{
		TTime ctm;

		int state=0;
		int nRecordType = 0;
		int nRecordValue = 0;
		float fRecordValue = 0.0;
		string strRecordValue = "";

		string strQSysLogTime;
		string strQSysLogIp;
		string strQSysLogMsg;
		int nQFacility;
		int nQSeverities;

		//获取日志数据
		if(!::GetRecordValueByField(rdobj, "_SysLogTime", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertRuleName string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(3, strRecordValue, 0))
			{
				continue;
			}

			strQSysLogTime = strRecordValue;
		}

		//获取日志数据
		if(!::GetRecordValueByField(rdobj, "_SourceIp", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertRuleName string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(2, strRecordValue, 0))
			{
				continue;
			}

			strQSysLogIp = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_SysLogMsg", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertTime string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(1, strRecordValue, 0))
			{
				continue;
			}

			strQSysLogMsg = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_Facility", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record EntityName string failed");
			continue ;
		}
		else
		{
			if(!IsCondMatch(4, "1", nRecordValue))
			{
				continue;
			}

			nQFacility = nRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_Level", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record MonitorName string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(5, "1", nRecordValue))
			{
				continue;
			}

			nQSeverities = nRecordValue;
		}
		
		//
		SysLogItem * item = new SysLogItem();
	
		item->strSysLogTime = strQSysLogTime;
		item->strSysLogIp = strQSysLogIp;
		item->strSysLogMsg = strQSysLogMsg;
		item->nFacility = nQFacility;
		item->nSeverities = nQSeverities;

		m_SysLogList.push_back(item);
	}

	::ReleaseRecordList(item);
	::CloseRecordSet(rds);	
}

//
void CSysLogQuery::RefreshList()
{
	//pAlertRightMap.clear();
	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	//清空列表里面的数据
	m_pSysLogListTable->GeDataTable()->clear();

	//pSysLogListTable->clear();
	//AddSysLogColum(pSysLogListTable);
	
	char tmpchar[10] = {0};
	string strTipInfo = strPage;	
	sprintf(tmpchar, "%d", nCurPage);
	strTipInfo += tmpchar;
	strTipInfo += strPageCount;
	sprintf(tmpchar, "%d", nTotalPage);
	strTipInfo += tmpchar;
	strTipInfo += strRecordCount;
	sprintf(tmpchar, "%d", m_SysLogList.size());
	strTipInfo += tmpchar;
	m_pSysLogListTable->pSelReverse->setText(strTipInfo);
		
	if(m_SysLogList.size() <= 0)
	{
		m_pSysLogListTable->ShowNullTip();
		return;
	}
	else
	{
		m_pSysLogListTable->HideNullTip();
	}

	int index = 0;
	int nPage = 0;
	list<SysLogItem *> ::iterator item;

	int iRow = 1;
	for(item = m_SysLogList.begin(); item != m_SysLogList.end(); item ++)
	{
		nPage = index / nPageCount;
		nPage += 1;
		if(!bDivide && nCurPage == nTotalPage)
		{
			if(nPage == nTotalPage)
			{
				//AddSysLogItem((*item)->strSysLogTime, (*item)->strSysLogIp, (*item)->strSysLogMsg, (*item)->nFacility, (*item)->nSeverities);
				AddSysLogItemNew(iRow,(*item)->strSysLogTime, (*item)->strSysLogIp, (*item)->strSysLogMsg, (*item)->nFacility, (*item)->nSeverities);
				iRow ++;
			}
		}
		else if(nPage == nCurPage)
		{
			//AddSysLogItem((*item)->strSysLogTime, (*item)->strSysLogIp, (*item)->strSysLogMsg, (*item)->nFacility, (*item)->nSeverities);
			AddSysLogItemNew(iRow,(*item)->strSysLogTime, (*item)->strSysLogIp, (*item)->strSysLogMsg, (*item)->nFacility, (*item)->nSeverities);
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

//
void CSysLogQuery::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp = "";
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    new WText(strTmp, this);
}

//报警日志查询
void CSysLogQuery::SysLogQuery()
{
	//清空显示链表
	list<SysLogItem *> ::iterator item;
	for(item = m_SysLogList.begin(); item != m_SysLogList.end(); item ++)
	{
		delete (*item);
	}
	m_SysLogList.erase(m_SysLogList.begin(), m_SysLogList.end());
	
	std::string s = m_SysLogList.size() + "";
	OutputDebugString("数据=");
	OutputDebugString(s.c_str());
	OutputDebugString("\n");
	
	strSysLogMsgCond = pSysLogMsg->text();
	strSysLogIpCond = pSysLogIp->text();

	std::list<string> pTemptList;
	list <string>::iterator listitem;

	//
	if(strFacilityCond != pFacility->text())
	{	
		strFacilityCond = pFacility->text();
		mapFacility.clear();
		pTemptList.clear();
		ParserToken(pTemptList, strFacilityCond.c_str(), ",");		
		for(listitem = pTemptList.begin(); listitem != pTemptList.end(); listitem++)
		{
			mapFacility[(*listitem)] = 0;
		}	
	}
	
	//strFacilityCond = pFacility->text();	
	strFacilityCond = "1,2,3,4,5,6,7";

	//
	if(strSeveritiesCond != pSeverities->text())
	{	
		strSeveritiesCond = pSeverities->text();
		mapSeverities.clear();
		pTemptList.clear();
		ParserToken(pTemptList, strSeveritiesCond.c_str(), ",");		
		for(listitem = pTemptList.begin(); listitem != pTemptList.end(); listitem++)
		{
			mapSeverities[(*listitem)] = 0;
		}	

	}

	//strSeveritiesCond = pSeverities->text();
	strSeveritiesCond = "1,2,3,4,5";

	strStartTimeCond = pSysLogStartTime->text();
	strEndTimeCond = pSysLogEndTime->text();
	
	OutputDebugString("FacilityCond:");
	OutputDebugString(strFacilityCond.c_str());
	OutputDebugString("\n");
	OutputDebugString("Severities:");
	OutputDebugString(strSeveritiesCond.c_str());
	OutputDebugString("\n");
	
	startTime = MakeTTime(strStartTimeCond);
	if(strEndTimeCond.empty())
		endTime = TTime::GetCurrentTimeEx();
	else
		endTime = MakeTTime(strEndTimeCond);

	//根据TableName 和 查询出符合条件的记录
	QueryRecordSet("syslog");

	if(m_SysLogList.size() % nPageCount  > 0)
	{
		nTotalPage = m_SysLogList.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = m_SysLogList.size() / nPageCount;
		bDivide = true;
	}
	
	if(nTotalPage > 0)
		nCurPage = 1;
	else
		nCurPage = 0;

	//显示指定记录页	
		
	RefreshList();

	WebSession::js_af_up = "hiddenbar()";
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

void alerthistorymain(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("SysLogQuery");

	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>", app.root());
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",  app.root());	
	new WText("<SCRIPT language='JavaScript' src='/listbase.js'></SCRIPT>",  app.root());		
	new WText("<div id='view_panel' class='panel_view'>", app.root());

    CSysLogQuery sysLogQuery(app.root());
	sysLogQuery.appSelf = &app;
	app.setBodyAttribute("class='workbody' ");

	new WText("</div>", app.root());

	AddJsParam("uistyle", "viewpan", app.root());
	AddJsParam("fullstyle", "true", app.root());
	AddJsParam("bGeneral", "false", app.root());
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());

    app.exec();
}

//
int main(int argc, char *argv[])
{
    func p = alerthistorymain;

	if (argc == 1) 
    {
        char buf[256];

		WebSession s(buf, false);
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