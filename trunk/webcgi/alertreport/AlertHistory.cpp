//#include <time.h>
#include ".\alertHistory.h"
//#include "../../kennel/svdb/svapi/libutil/Time.h"
#include "..\svtable\FlexTable.h"
#include "..\svtable\MainTable.h"

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
#include <WPushButton>
#include "..\svtable\FlexTable.h"//zzzzzzzzzzzzzzz
#include "..\svtable\MainTable.h"
#include "..\svtable\WSVButton.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
//#include ".\useroperatelog.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
using namespace std;
using namespace chen;


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

//根据Id分解出pAlertTargetList
void WriteAlertTargerById(string strId, std::list<string> &pAlertTargetList)
{
	bool bAdd = true;
	string strTmp;

	//1.2和1.2.1同时在pAlertTargetList里就麻烦了，因为原来的串以递归方式存储，组串在前， 不会出现此情况， 此是投机取巧的方法， 需测试-->测试无问题。
	list <string>::iterator listitem;
	for(listitem = pAlertTargetList.begin(); listitem != pAlertTargetList.end(); listitem++)
	{
		strTmp = (*listitem);		

		//全匹配
		if(strId == strTmp)
		{
			bAdd = false;
			break;
		}

		basic_string <char>::size_type indexCh2a = strId.find(strTmp.c_str());
		//找到、从头匹配（错误如：1.3.1.1和1.1）、匹配后的字符应该是点（错误如：1.3和1.33）
		if(indexCh2a != -1 && indexCh2a == 0 && strId.at(strTmp.length()) == '.')
		{
			bAdd = false;
			break;
		}
	}
	
	if(bAdd)
		pAlertTargetList.push_back(strId);
}

//
bool IsUserHasAlertRight(string strIndex)
{
	bool bReturn = true;	
	std::list<string> pTempTargetList;	
	list <string>::iterator listitem;

	string strSection = GetWebUserID();
	
	//管理员则有所有权限
	if(GetIniFileInt(strSection, "nAdmin", -1, "user.ini") != -1)
		return true;
	
	//获取用户能管理的Target串........
	string strGroupRight = GetIniFileString(strSection, "groupright", "", "user.ini");

	if(strGroupRight == "")
		return false;

	//分析用户能管理的Target串=========
	std::list<string> pUserTargetList;
	ParserToken(pTempTargetList, strGroupRight.c_str(), ",");

	for(listitem = pTempTargetList.begin(); listitem != pTempTargetList.end(); listitem++)
	{		
		WriteAlertTargerById((*listitem), pUserTargetList);
	}

	//根据分析后的用户能管理的Target串构造hash匹配表+++++++++++
	map<string, int, less<string> > pUserTargetMap;
	string strNewUserTargetList = "";
	for(listitem = pUserTargetList.begin(); listitem != pUserTargetList.end(); listitem++)
	{
		strNewUserTargetList += (*listitem);
		strNewUserTargetList += ",";

		pUserTargetMap[(*listitem)] = 0;
	}


	//获取Alert监测的Target串..........
	string strAlertTarget = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini");
	
	if(strAlertTarget == "")
		return false;
	
	//分析Alert监测的Target串===========
	std::list<string> pAlertTargetList;
	ParserToken(pTempTargetList, strAlertTarget.c_str(), ",");

	for(listitem = pTempTargetList.begin(); listitem != pTempTargetList.end(); listitem++)
	{		
		WriteAlertTargerById((*listitem), pAlertTargetList);
	}

	//以Alert监测分析后的Targetlist循环匹配用户能管理的Target分析map以确认是否有权限管理该报警|||||||||||||||||
	for(listitem = pAlertTargetList.begin(); listitem != pAlertTargetList.end(); listitem++)
	{
		bool bTargetMatch = false;
		string strTmpId = (*listitem);
		string strTmp = "";
		int nPos = 0;
		while(nPos != -1)
		{
			if(pUserTargetMap.find(strTmpId) != pUserTargetMap.end())
			{
				bTargetMatch = true;
				break;
			}
			else
			{			
				nPos = strTmpId.rfind(".");	
				strTmp = strTmpId.substr(0, nPos);
				strTmpId = strTmp;
			}
		}

		if(!bTargetMatch)
		{
			bReturn = false;
			break;
		}
	}

	return bReturn;
}


//
bool ValidateTTime(string strTime)
{
	int nRet = 0;
	int nTmp = 0;
	std::list<string> pTmpList;	
	ParserToken(pTmpList, strTime.c_str(), " ");
	
	if(pTmpList.size() != 2)
		return false;

	string strYear, strMonth, strDay;
	std::list<string> pTmpList1;
	ParserToken(pTmpList1, pTmpList.front().c_str(), "-");
	
	if(pTmpList1.size() != 3)
		return false;

	strYear = pTmpList1.front();
	pTmpList1.pop_front();
	strMonth = pTmpList1.front();
	pTmpList1.pop_front();
	strDay = pTmpList1.front();
	pTmpList1.pop_front();
	
	nRet = sscanf(strYear.c_str(), "%d", &nTmp);
	if(nRet == EOF || nRet == 0 || nTmp < 1)
	{
		return false;
	}
	else
	{
		if(nTmp < 1970)
			return false;
	}

	nRet = sscanf(strMonth.c_str(), "%d", &nTmp);
	if(nRet == EOF || nRet == 0 || nTmp < 1)
	{
		return false;
	}
	else
	{
		if(nTmp > 12)
			return false;
	}

	nRet = sscanf(strDay.c_str(), "%d", &nTmp);
	if(nRet == EOF || nRet == 0 || nTmp < 1)
	{
		return false;
	}
	else
	{
		if(nTmp > 31)
			return false;
	}

	string strHour, strMinute, strSecond;
	std::list<string> pTmpList2;
	ParserToken(pTmpList2, pTmpList.back().c_str(), ":");

	strHour = pTmpList2.front();
	pTmpList2.pop_front();
	strMinute = pTmpList2.front();
	pTmpList2.pop_front();
	strSecond = pTmpList2.front();
	pTmpList2.pop_front();
	
	nRet = sscanf(strHour.c_str(), "%d", &nTmp);
	if(nRet == EOF || nRet == 0 || nTmp < 1)
	{
		return false;
	}
	else
	{
		if(nTmp > 23)
			return false;
	}

	nRet = sscanf(strMinute.c_str(), "%d", &nTmp);
	if(nRet == EOF || nRet == 0 || nTmp < 1)
	{
		return false;
	}
	else
	{
		if(nTmp > 60)
			return false;
	}

	nRet = sscanf(strSecond.c_str(), "%d", &nTmp);
	if(nRet == EOF || nRet == 0 || nTmp < 1)
	{
		return false;
	}
	else
	{
		if(nTmp > 60)
			return false;
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
CAlertHistory::CAlertHistory(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Alert_Log",strAlertHistoryTiltle);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Forward",strForward);
			FindNodeValue(ResNode,"IDS_Back",strBack);
			FindNodeValue(ResNode,"IDS_Alert_Start_Time",strStartTimeLabel);
			FindNodeValue(ResNode,"IDS_Alert_Start_Time",strStartTimeDes);
			FindNodeValue(ResNode,"IDS_Alert_End_Time",strEndTimeLabel);
			FindNodeValue(ResNode,"IDS_Alert_End_Time",strEndTimeDes);
			FindNodeValue(ResNode,"IDS_Alert_Name",strHAlertNameLabel);
			FindNodeValue(ResNode,"IDS_Device_Name",strHDeveiceNameLabel);
			FindNodeValue(ResNode,"IDS_Monitor_Name",strHMonitorNameLabel);
			FindNodeValue(ResNode,"IDS_Alert_Receiver",strHAlertReceiveLabel);
			FindNodeValue(ResNode,"IDS_Alert_Time",strHTimeLabel);
			FindNodeValue(ResNode,"IDS_Alert_Type",strHAlertTypeLabel);
			FindNodeValue(ResNode,"IDS_Alert_State",strHAlertStateLabel);
			FindNodeValue(ResNode,"IDS_Alert_Name",strAlertNameLabel);
			FindNodeValue(ResNode,"IDS_Alert_Name_Description",strAlertNameDes);
			FindNodeValue(ResNode,"IDS_Alert_Receiver",strAlertReceiveLabel);
			FindNodeValue(ResNode,"IDS_Alert_Receiver_Description",strAlertReceiveDes);
			FindNodeValue(ResNode,"IDS_Alert_Time_Description",strAlertTimeDes);
			FindNodeValue(ResNode,"IDS_Alert_Type",strAlertTypeLabel);
			FindNodeValue(ResNode,"IDS_Alert_Type_Description",strAlertTypeDes);
			FindNodeValue(ResNode,"IDS_All",strAlertAll);
			FindNodeValue(ResNode,"IDS_Alert_Email",strEmailAlert);
			FindNodeValue(ResNode,"IDS_Alert_SMS",strSmsAlert);
			FindNodeValue(ResNode,"IDS_Alert_Script",strScriptAlert);
			FindNodeValue(ResNode,"IDS_Alert_Sound",strSoundAlert);
			FindNodeValue(ResNode,"IDS_Query",strQueryBtn);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Ini",strAlertLogRecordIni);
			FindNodeValue(ResNode,"IDS_No_Alert_Log",strNoSortRecord); 
		}
		CloseResource(objRes);
	}
	nCurPage = 0;
	nTotalPage = 0;
	nPageCount = 30;
	ShowMainTable();
}



//
CAlertHistory::~CAlertHistory(void)

{
}

void CAlertHistory::ShowHelp()
{
	m_pHistoryTable->ShowOrHideHelp();
}

//初始化主界面
void CAlertHistory::ShowMainTable()
{

	m_pMainTable = new WSVMainTable(this,strAlertHistoryTiltle,true);

	if(m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg,SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}

	//m_pHistoryTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0), Query ,strAlertHistoryTiltle);
	m_pHistoryTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0), Query ,"查询参数");
	if (m_pHistoryTable->GetContentTable() != NULL)
	{
		m_pHistoryTable->AppendRows();	
		//报警名称
		pAlertName = new WLineEdit("",  m_pHistoryTable->AppendRowsContent(0, 0, 2, strAlertNameLabel, strAlertNameDes, ""));
		pAlertName->setStyleClass("input_text");
		//接受人
		pAlertReceive = new WLineEdit("",  m_pHistoryTable->AppendRowsContent(0, 1, 2, strAlertReceiveLabel, strAlertReceiveDes, ""));	
		pAlertReceive->setStyleClass("input_text");

		m_pHistoryTable->AppendRows();	
		//开始时间
		pAlertStartTime = new WLineEdit("",  m_pHistoryTable->AppendRowsContent(1, 0, 2, strStartTimeLabel,strStartTimeDes, ""));	
		pAlertStartTime->setStyleClass("input_text");
		TTime curTime = TTime::GetCurrentTimeEx();
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		pAlertStartTime->setText(curTime.Format());
		strcpy(pAlertStartTime->contextmenu_ , "onFocus=\"calendar()\"");
		//结束时间
		pAlertEndTime = new WLineEdit("",  m_pHistoryTable->AppendRowsContent(1,1, 2, strEndTimeLabel,strEndTimeDes, ""));
		pAlertEndTime->setStyleClass("input_text");
		curTime = TTime::GetCurrentTimeEx();
		pAlertEndTime->setText(curTime.Format());
		strcpy(pAlertEndTime->contextmenu_ , "onFocus=\"calendar()\"");

		//报警类型
		m_pHistoryTable->AppendRows();
		pAlertType = new WComboBox(m_pHistoryTable->AppendRowsContent(2, 0 ,1 , strAlertTypeLabel, strAlertTypeDes, ""));
		pAlertType->setStyleClass("input_text");
		pAlertType->addItem(strAlertAll);
		pAlertType->addItem(strEmailAlert);
		pAlertType->addItem(strSmsAlert);
		pAlertType->addItem(strScriptAlert);
		pAlertType->addItem(strSoundAlert);
	}

	if(m_pHistoryTable->GetActionTable()!=NULL)
	{
		m_pHistoryTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		
		WSVButton *pQuery = new WSVButton(m_pHistoryTable->GetActionTable()->elementAt(0,1),strQueryBtn,"button_bg_m_black.png","",true);	
	
		//connect(pQuery,SIGNAL(clicked()),"showbar()",this,SLOT(LogQuery()));
		connect(pQuery, SIGNAL(clicked()), "showbar();" ,this, SLOT(AlertQuery()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	}

	

	
	//m_pHistoryListTable = new WSVFlexTable( m_pMainTable->GetContentTable()->elementAt(1,0),List,"");
	m_pHistoryListTable = new WSVFlexTable( m_pMainTable->GetContentTable()->elementAt(1,0),List,"查询结果");
	
	m_pHistoryListTable->SetDivId("listpan2");
	if(m_pHistoryListTable->GetContentTable()!=NULL)
	{
		
		m_pHistoryListTable->AppendColumn("",WLength(2,WLength::Pixel));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_img");

		m_pHistoryListTable->AppendColumn(strHTimeLabel,WLength(10,WLength::Percentage));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_img");
		
		m_pHistoryListTable->AppendColumn(strHAlertNameLabel,WLength(10,WLength::Percentage));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_img");
		
		m_pHistoryListTable->AppendColumn(strHDeveiceNameLabel,WLength(120,WLength::Pixel));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pHistoryListTable->AppendColumn(strHMonitorNameLabel,WLength(120,WLength::Pixel));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pHistoryListTable->AppendColumn(strHAlertReceiveLabel,WLength(15,WLength::Percentage));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_img");

		m_pHistoryListTable->AppendColumn(strHAlertTypeLabel,WLength(15,WLength::Percentage));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_img");

		m_pHistoryListTable->AppendColumn(strHAlertStateLabel,WLength(10,WLength::Percentage));
		m_pHistoryListTable->SetDataRowStyle("table_data_grid_item_img");
	}
	
	
	if(m_pHistoryListTable->GetActionTable() != NULL)
	{
		string strPageIni,strPageCountIni,strRecorCountIni;	

		OBJECT objRes=LoadResource("default", "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",strPageIni);
				FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",strPageCountIni);
				FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",strRecorCountIni);
			}
			CloseResource(objRes);
		}

		m_pHistoryListTable->AddStandardSelLink(strBack,strForward,strAlertLogRecordIni);
		connect(m_pHistoryListTable->pSelAll, SIGNAL(clicked()), this, SLOT(HistoryBack()));		
		connect(m_pHistoryListTable->pSelNone, SIGNAL(clicked()), this, SLOT(HistoryForward()));
		m_pHistoryListTable->pSelReverse->setStyleClass("");
	}

	m_pHistoryListTable->SetNullTipInfo(strNoSortRecord);

	emit ShowHelp();

	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	//根据user和alert建立nIndex为key的权限map， 这样查权限会很快，　但此权限map需随alert的增删修而增删修, 在报警日志查询中会有用。
	if(GetIniFileSections(keylist, "alert.ini"))
	{
		//从ini初始化报警列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			if(IsUserHasAlertRight(*keyitem))
			{
				pAlertRightMap[(*keyitem)] = 0;					
			}
		}
	}

	//翻译
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


void CAlertHistory::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/alertreport.exe?'\",1250);  ";
	appSelf->quit();
}
void CAlertHistory::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "alertreportRes";
	WebSession::js_af_up += "')";
}

//加日志列表标题
void CAlertHistory::AddHistoryColum(WTable* pContain)
{
	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}

//
void  CAlertHistory::AddListItem(string strAlertTime, string strAlertName, 
	string strDeveiceName, string strMonitorName, string strAlertReceive, string strAlertType, string strAlertState, int numRow)
{	
	m_pHistoryListTable->InitRow(numRow);
	WText * pTmpText;
	pTmpText = new WText("", (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 0));

	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strAlertTime, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 2));

	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strAlertName, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 4));
	
	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 6)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strDeveiceName, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 6));

	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 8)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strMonitorName, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 8));

	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 10)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strAlertReceive, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 10));

	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 12)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strAlertType, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 12));

	m_pHistoryListTable->GeDataTable()->elementAt(numRow , 14)->setContentAlignment(AlignCenter);	
	pTmpText = new WText(strAlertState, (WContainerWidget*)m_pHistoryListTable->GeDataTable()->elementAt(numRow , 14));
	

}

//报警日志
void CAlertHistory::AlertHistory(const std::string strIndex)
{
	//根据strIndex读出数据

	//pHistoryTable
	//将数据插入pHistoryListTable
}

//历史日志往前
void CAlertHistory::HistoryForward()
{
	nCurPage++;
	
	if(nCurPage >= nTotalPage)
		nCurPage = nTotalPage;
	//
	RefreshList();
}

//历史日志往后
void CAlertHistory::HistoryBack()
{
	nCurPage--;

	//
	if(nCurPage < 1)
		nCurPage = 1;

	//
	RefreshList();
}

//返回报警日志
void CAlertHistory::HistoryReturnBtn()
{
	//
	//显示列表界面	
}

//
string CAlertHistory::GetAlertTypeStrFormInt(int nType)
{
	string strType = "";
	switch(nType)
	{
		case 0:
			strType = "All";
			break;
		case 1:
			strType = "EmailAlert";
			break;
		case 2:
			strType = "SmsAlert";
			break;
		case 3:
			strType = "ScriptAlert";
			break;
		case 4:
			strType = "SoundAlert";
			break;
		default:
			break;
	}

	return strType;
}

//
string CAlertHistory::GetAlertStatuStrFormInt(int nStatu)
{
	string strStatu = "";
	switch(nStatu)
	{
		case 1:
			strStatu = "Sucess";
			break;
		case 0:
			strStatu = "Fail";
			break;
		default:
			break;
	}

	return strStatu;
}

//查询条件匹配
bool CAlertHistory::IsCondMatch(int nCond, string strCondValue)
{
	bool bMatch = false;
	switch(nCond)
	{
		case 1:
			//AlertRuleName
			if(strAlertNameCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue.find(strAlertNameCond) != -1)
				{
					bMatch = true;
				}
			}
			break;
		case 2:
			//AlertReceive
			if(strAlertReceiveCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue.find(strAlertReceiveCond) != -1)
				{
					bMatch = true;
				}
			}
			break;
		case 3:
			//AlertTime
			/*bMatch = true;*/
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
			//AlertType
			if(strAlertTypeCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue.find(strAlertTypeCond) != -1)
				{
					bMatch = true;
				}

				if(strAlertTypeCond == "All")
				{
					bMatch = true;
				}
			}
			break;
		case 6:
			//AlertRight
			if(pAlertRightMap.find(strCondValue) != pAlertRightMap.end())
			{
				bMatch = true;
			}
			else
			{
				bMatch = false;
			}
			break;

		default:
			break;
	}

	return bMatch;
}

//查询数据
void CAlertHistory::QueryRecordSet(string strTableName)
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

		string strQAlertName;
		string strQMonitorName;
		string strQEnitityName;
		string strQAlertReceive;
		string strQAlertTime;
		string strQAlertType;
		string strQAlertStatu;

		//获取日志数据
		if(!::GetRecordValueByField(rdobj, "_AlertIndex", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertRuleName string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(6, strRecordValue))
			{
				continue;
			}

			//strQAlertIndex = strRecordValue;
		}

		//获取日志数据
		if(!::GetRecordValueByField(rdobj, "_AlertRuleName", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertRuleName string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(1, strRecordValue))
			{
				continue;
			}

			strQAlertName = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_AlertTime", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertTime string failed");
			continue;
		}
		else
		{
			//不需要了 QueryRecords已经做了
			//if(!IsCondMatch(3, strRecordValue))
			//{
			//	continue;
			//}

			strQAlertTime = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_DeviceName", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record EntityName string failed");
			return ;
		}
		else
		{
			strQEnitityName = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_MonitorName", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record MonitorName string failed");
			continue;
		}
		else
		{
			strQMonitorName = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_AlertReceive", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertReceive string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(2, strRecordValue))
			{
				continue;
			}

			strQAlertReceive = strRecordValue;
		}

		//nRecordValue
		if(!::GetRecordValueByField(rdobj, "_AlertType", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertType string failed");
			continue;
		}
		else
		{
			strQAlertType = GetAlertTypeStrFormInt(nRecordValue);

			if(!IsCondMatch(4, strQAlertType))
			{
				continue;
			}			
		}

		//fRecordValue
		if(!::GetRecordValueByField(rdobj, "_AlertStatus", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertStatus string failed");
			continue;
		}
		else
		{
			strQAlertStatu = GetAlertStatuStrFormInt(nRecordValue);
		}
		
		//
		AlertLogItem * item = new AlertLogItem();
	
		item->strAlertName = strQAlertName;
		item->strMonitorName = strQMonitorName;
		item->strEnitityName = strQEnitityName;
		item->strAlertReceive = strQAlertReceive;
		item->strAlertTime = strQAlertTime;
		item->strAlertType = strQAlertType;
		item->strAlertStatu = strQAlertStatu;

		m_AlertLogList.push_back(item);		
	}

	::ReleaseRecordList(item);
	::CloseRecordSet(rds);	
}

//
void CAlertHistory::RefreshList()
{
	pAlertRightMap.clear();
	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	//根据user和alert建立nIndex为key的权限map， 这样查权限会很快，　但此权限map需随alert的增删修而增删修, 在报警日志查询中会有用。
	if(GetIniFileSections(keylist, "alert.ini"))
	{
		//从ini初始化报警列表
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			if(IsUserHasAlertRight(*keyitem))
			{
				pAlertRightMap[(*keyitem)] = 0;					
			}
		}
	}


	//pHistoryListTable->clear();
	m_pHistoryListTable->GeDataTable()->clear();
	//AddHistoryColum(pHistoryListTable);

	string strPageIni,strPageCountIni,strRecorCountIni;
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",strPageIni);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",strPageCountIni);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",strRecorCountIni);
		}
		CloseResource(objRes);
	}

	char tmpchar[10] = {0};
	string strTipInfo = strPageIni;	
	sprintf(tmpchar, "%d", nCurPage);
	strTipInfo += tmpchar;
	strTipInfo += strPageCountIni;
	sprintf(tmpchar, "%d", nTotalPage);
	strTipInfo += tmpchar;
	//strTipInfo += "  页行数：";
	//sprintf(tmpchar, "%d", nPageCount);
	//strTipInfo += tmpchar;
	strTipInfo += strRecorCountIni;
	sprintf(tmpchar, "%d", m_AlertLogList.size());
	strTipInfo += tmpchar;
	m_pHistoryListTable->pSelReverse->setText(strTipInfo);
	
	if(m_AlertLogList.size() <= 0)
	{
		m_pHistoryListTable->ShowNullTip();
		return;
	}
	else
	{
		m_pHistoryListTable->HideNullTip();
	}

	int index = 0;
	int nPage = 0;
	list<AlertLogItem *> ::iterator item;
	int iRow = 1;
	for(item = m_AlertLogList.begin(); item != m_AlertLogList.end(); item ++)
	{
		nPage = index / nPageCount;
		nPage += 1;
		if(!bDivide && nCurPage == nTotalPage)
		{
			if(nPage == nTotalPage)
			{
				AddListItem((*item)->strAlertTime, (*item)->strAlertName, (*item)->strEnitityName, (*item)->strMonitorName, 
					(*item)->strAlertReceive, (*item)->strAlertType, (*item)->strAlertStatu, iRow);			
				iRow++;
			}
		}
		else if(nPage == nCurPage)
		{
			AddListItem((*item)->strAlertTime, (*item)->strAlertName, (*item)->strEnitityName, (*item)->strMonitorName, 
				(*item)->strAlertReceive, (*item)->strAlertType, (*item)->strAlertStatu, iRow);
			iRow++;
		}
		else
		{
		
		}

		index ++;
		
	}
	//翻译
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

//报警日志查询
void CAlertHistory::AlertQuery()
{
/*
	//错误检查
	bool bError = false;
	std::list<string> errorMsgList;

	//有效性检查。。。。
	if(!ValidateTTime(pAlertStartTime->text()))
	{
		bError = false;
	}

	if(!ValidateTTime(pAlertEndTime->text()))
	{
		bError = false;
	}
*/

	//清空显示链表
	list<AlertLogItem *> ::iterator item;
	for(item = m_AlertLogList.begin(); item != m_AlertLogList.end(); item ++)
	{
		delete (*item);
	}

	m_AlertLogList.erase(m_AlertLogList.begin(), m_AlertLogList.end());

	strAlertNameCond = pAlertName->text();
	strAlertReceiveCond = pAlertReceive->text();
	strStartTimeCond = pAlertStartTime->text();
	strEndTimeCond = pAlertEndTime->text();
	startTime = MakeTTime(strStartTimeCond);
	if(strEndTimeCond.empty())
		endTime = TTime::GetCurrentTimeEx();
	else
		endTime = MakeTTime(strEndTimeCond);
	strAlertTypeCond = GetAlertTypeStrFormInt(pAlertType->currentIndex());

	//OutputDebugString(startTime.Format());
	//OutputDebugString(endTime.Format());
	//OutputDebugString(strAlertTypeCond.c_str());

	//根据TableName 和 AlertName AlertReceive AlertTime AlertType查询出符合条件的记录
	QueryRecordSet("alertlogs");

	if(m_AlertLogList.size() % nPageCount  > 0)
	{
		nTotalPage = m_AlertLogList.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = m_AlertLogList.size() / nPageCount;
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
void AddJsParam(const std::string name, const std::string value, WContainerWidget *parent)
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
    app.setTitle("alertHistory");

	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>", app.root());
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());	

	new WText("<div id='view_panel' class='panel_view'>", app.root());

    CAlertHistory alertHistory(app.root());
	alertHistory.appSelf = &app;
	app.setBodyAttribute("class='workbody' ");

	new WText("</div>");
	AddJsParam("bGeneral","true",app.root());
	AddJsParam("uistyle", "viewpan",app.root());
	AddJsParam("fullstyle", "true",app.root());
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