#include ".\SysLogSet.h"


#include "WApplication"
#include "websession.h"
#include "WCheckBox"
#include "WLineEdit"
#include "WImage"

#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVButton.h"


#include "..\svtable\FlexTable.h"
#include "..\svtable\MainTable.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

#include "../base/splitquery.h"

extern void PrintDebugString(const char *);

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

CSysLogSet::CSysLogSet(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Save",strSave);
			FindNodeValue(ResNode,"IDS_Save_Success",strSaveSucess);
			FindNodeValue(ResNode,"IDS_SysLogSetting",strMainTitle);
			FindNodeValue(ResNode,"IDS_SysLogSetting",strTitle);
			FindNodeValue(ResNode,"IDS_FacilitY_Param_Set",strFacilityTitle);
			FindNodeValue(ResNode,"IDS_Level_Param_Set",strSeveritiesTitle);
			FindNodeValue(ResNode,"IDS_SysLog_Delete_Config",strDelSetTitle);
			FindNodeValue(ResNode,"IDS_Delete_Records_Ago",strManualDelLabel);
			FindNodeValue(ResNode,"IDS_Delete_Records_Ago",strManualDelDes);
			FindNodeValue(ResNode,"IDS_Record_Keep_Date",strAutoDelLabel);
			FindNodeValue(ResNode,"IDS_Record_Keep_Date_Des",strAutoDelDes);
			FindNodeValue(ResNode,"IDS_Delete",strDel);
			FindNodeValue(ResNode,"IDS_Save_Success",strSaveSucess);
			FindNodeValue(ResNode,"IDS_Delete_Success",strDelSucess);
			FindNodeValue(ResNode,"IDS_Edit",strOType);
			FindNodeValue(ResNode,"IDS_SysLog_Delete_Config",strDelSetTitle);
			FindNodeValue(ResNode,"IDS_Modify_Facility",strModifyFacility);
			FindNodeValue(ResNode,"IDS_Modify_Days",strDays);
			FindNodeValue(ResNode,"IDS_Delete_Records_Ago",strDelRecord);
			FindNodeValue(ResNode,"IDS_Modify_Level",strModifyLevel);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
		}
		CloseResource(objRes);
	}

/*	strDelSetTitle = "SysLog删除设置";
	strManualDelLabel = "删除此时间以前的记录：";
	strManualDelDes = "删除此时间以前的记录";
	strAutoDelLabel = "记录保持天数：";
	strAutoDelDes = "记录保持天数，　为0则永久保持";

	strDel = "删　除";
	strSaveSucess = "保存成功!";
	strDelSucess = "删除成功!";
*/
	//
/*	strMainTitle="SysLog设置";
	strTitle="SysLog设置";
	strFacilityTitle="Facility参数设置";
	strSeveritiesTitle="Level参数设置";
*/
	//Facility
	//strFacility0 = "kernel messages";
	//strFacility1 = "user-level messages";
	//strFacility2 = "mail system";
	//strFacility3 = "system daemons";
	//strFacility4 = "security/authorization messages";
	//strFacility5 = "messages generated internally by syslogd";
	//strFacility6 = "line printer subsystem";
	//strFacility7 = "network news subsystem";
	//strFacility8 = "UUCP subsystem";
	//strFacility9 = "clock daemon";
	//strFacility10 = "security/authorization messages";
	//strFacility11 = "FTP daemon";
	//strFacility12 = "NTP subsystem";
	//strFacility13 = "log audit";
	//strFacility14 = "log alert";
	//strFacility15 = "clock daemon";
	//strFacility16 = "local use 0  (local0)";
	//strFacility17 = "local use 1  (local1)";
	//strFacility18 = "local use 2  (local2)";
	//strFacility19 = "local use 3  (local3)";
	//strFacility20 = "local use 4  (local4)";
	//strFacility21 = "local use 5  (local5)";
	//strFacility22 = "local use 6  (local6)";
	//strFacility23 = "local use 7  (local7)";
	strFacility0 = "Kernel";
	strFacility1 = "User";
	strFacility2 = "Mail";
	strFacility3 = "Daemon";
	strFacility4 = "Auth";
	strFacility5 = "Syslog";
	strFacility6 = "Lpr";
	strFacility7 = "News";
	strFacility8 = "UUCP";
	strFacility9 = "Cron";
	strFacility10 = "Security";
	strFacility11 = "FTP Daemon";
	strFacility12 = "NTP";
	strFacility13 = "Log audit";	
	strFacility14 = "Log alert";
	strFacility15 = "Clock Daemon";
	strFacility16 = "local0";
	strFacility17 = "local1";
	strFacility18 = "local2";
	strFacility19 = "local3";
	strFacility20 = "local4";
	strFacility21 = "local5";
	strFacility22 = "local6";
	strFacility23 = "local7";
	//Severities
	strSeverities0 = "Emergency";
	strSeverities1 = "Alert";
	strSeverities2 = "Critical";
	strSeverities3 = "Error";
	strSeverities4 = "Warning";
	strSeverities5 = "Notice";
	strSeverities6 = "Informational";
	strSeverities7 = "Debug";

	refreshCount=0;

	ShowMainTable();
}

CSysLogSet::~CSysLogSet(void)
{
}

void CSysLogSet::ShowHelp()
{
	//m_pFacilityTable->ShowOrHideHelp();
	m_pDeleteSetTable->ShowOrHideHelp();
	m_pDeleteSetTable->HideAllErrorMsg();
}

//初始化主界面
void CSysLogSet::ShowMainTable()
{

	m_pMainTable = new WSVMainTable(this,strMainTitle,true);
	if (m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}
	
	m_pFacilityTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0),EntityList,strFacilityTitle);
	if(m_pFacilityTable->GetContentTable() != NULL)
	{
		m_pFacilityTable->AppendRows("");

		WTable * contentTable = new WTable(m_pFacilityTable->GetContentTable()->elementAt(0, 0));
		contentTable->resize(WLength(100,WLength::Percentage),0);
		contentTable->elementAt(0, 0)->resize(WLength(50,WLength::Percentage),0);
		contentTable->elementAt(0, 1)->resize(WLength(50,WLength::Percentage),0);

		//contentTable->elementAt(0, 0)->resize(WLength(50,WLength::Pixel),0);
		//new WText("&nbsp;",contentTable->elementAt(0, 0));
		WTable * leftTable = new WTable(contentTable->elementAt(0, 0));
		WTable * rightTable = new WTable(contentTable->elementAt(0, 1));

		m_pListFacBox.push_back(new WCheckBox(strFacility0, (WContainerWidget*)leftTable->elementAt(0, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility1, (WContainerWidget*)rightTable->elementAt(0, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility2, (WContainerWidget*)leftTable->elementAt(1, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility3, (WContainerWidget*)rightTable->elementAt(1, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility4, (WContainerWidget*)leftTable->elementAt(2, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility5, (WContainerWidget*)rightTable->elementAt(2, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility6, (WContainerWidget*)leftTable->elementAt(3, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility7, (WContainerWidget*)rightTable->elementAt(3, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility8, (WContainerWidget*)leftTable->elementAt(4, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility9, (WContainerWidget*)rightTable->elementAt(4, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility10, (WContainerWidget*)leftTable->elementAt(5, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility11, (WContainerWidget*)rightTable->elementAt(5, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility12, (WContainerWidget*)leftTable->elementAt(6, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility13, (WContainerWidget*)rightTable->elementAt(6, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility14, (WContainerWidget*)leftTable->elementAt(7, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility15, (WContainerWidget*)rightTable->elementAt(7, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility16, (WContainerWidget*)leftTable->elementAt(8, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility17, (WContainerWidget*)rightTable->elementAt(8, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility18, (WContainerWidget*)leftTable->elementAt(9, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility19, (WContainerWidget*)rightTable->elementAt(9, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility20, (WContainerWidget*)leftTable->elementAt(10, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility21, (WContainerWidget*)rightTable->elementAt(10, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility22, (WContainerWidget*)leftTable->elementAt(11, 0)));
		m_pListFacBox.push_back(new WCheckBox(strFacility23, (WContainerWidget*)rightTable->elementAt(11, 0)));
	}	

	if(m_pFacilityTable->GetActionTable() != NULL)
	{
			WTable *pTbl;

			pTbl = new WTable(m_pFacilityTable->GetActionTable()->elementAt(0, 1));

			WSVButton * pSaveButton = new WSVButton(pTbl->elementAt(0,0),strSave,"button_bg_m_black.png","",true);
			connect(pSaveButton, SIGNAL(clicked()), this, SLOT(SaveFacility()));
	}
	

	m_pLevelTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(2,0),EntityList,strSeveritiesTitle);
	if(m_pLevelTable->GetContentTable() != NULL)
	{
		m_pLevelTable->AppendRows("");
		
		WTable * contentTable = new WTable(m_pLevelTable->GetContentTable()->elementAt(0, 0));
		contentTable->resize(WLength(100,WLength::Percentage),0);
		contentTable->elementAt(0, 0)->resize(WLength(50,WLength::Percentage),0);
		contentTable->elementAt(0, 1)->resize(WLength(50,WLength::Percentage),0);

		//contentTable->elementAt(0, 0)->resize(WLength(50,WLength::Pixel),0);
		//new WText("&nbsp;",contentTable->elementAt(0, 0));
		WTable * leftSTable = new WTable(contentTable->elementAt(0, 0));
		WTable * rightSTable = new WTable(contentTable->elementAt(0, 1));

		m_pListServerBox.push_back(new WCheckBox(strSeverities0, (WContainerWidget*)leftSTable->elementAt(0, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities1, (WContainerWidget*)rightSTable->elementAt(1, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities2, (WContainerWidget*)leftSTable->elementAt(2, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities3, (WContainerWidget*)rightSTable->elementAt(3, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities4, (WContainerWidget*)leftSTable->elementAt(4, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities5, (WContainerWidget*)rightSTable->elementAt(5, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities6, (WContainerWidget*)leftSTable->elementAt(6, 0)));
		m_pListServerBox.push_back(new WCheckBox(strSeverities7, (WContainerWidget*)rightSTable->elementAt(7, 0)));
	}		

	if(m_pLevelTable->GetActionTable() != NULL)
	{
		WTable *pTbl;

		pTbl = new WTable(m_pLevelTable->GetActionTable()->elementAt(0, 1));

		WSVButton * pSaveButton = new WSVButton(pTbl->elementAt(0,0),strSave,"button_bg_m_black.png","",true);
		connect(pSaveButton, SIGNAL(clicked()), this, SLOT(SaveSeverities()));

		pTbl = new WTable(m_pLevelTable->GetActionTable()->elementAt(0,2));
	}


	m_pDeleteSetTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(3,0),Group,strDelSetTitle);
	if(m_pDeleteSetTable->GetContentTable() != NULL)
	{
		TTime curTime = TTime::GetCurrentTimeEx();
		string strKeepDay = GetIniFileString("DelCond", "KeepDay", "", "syslog.ini");
		m_pDeleteSetTable->AppendRows("");
		WTable *saveTbl = new WTable(m_pDeleteSetTable->AppendRowsContent(0,strManualDelLabel, strManualDelDes, ""));
		saveTbl->setStyleClass("widthauto");
		pManualEdit = new WLineEdit("", saveTbl->elementAt(0,0));
		pManualEdit->setText(curTime.Format());
		pManualEdit->setStyleClass("input_text");
		strcpy(pManualEdit->contextmenu_ , "onFocus=\"calendar()\"");

		saveTbl->elementAt(0,1)->setContentAlignment(AlignRight);
		WSVButton * pDelManualBtn = new WSVButton(saveTbl->elementAt(0,1),strDel,"button_bg_del.png","",false);
		connect(pDelManualBtn, SIGNAL(clicked()), this, SLOT(DelSysLogData()));

		WTable *deleteTbl = new WTable(m_pDeleteSetTable->AppendRowsContent(0,strAutoDelLabel, strAutoDelDes, "记录保持天数必须为数字！"));
		deleteTbl->setStyleClass("widthauto");
		pKeepDay = new WLineEdit(strKeepDay,deleteTbl->elementAt(0,0));
		pKeepDay->setStyleClass("input_text");
		deleteTbl->elementAt(0,1)->setContentAlignment(AlignRight);
		WSVButton * pSaveButton2 = new WSVButton(deleteTbl->elementAt(0,1), strSave, "button_bg_m_black.png", "", true);
		connect(pSaveButton2, SIGNAL(clicked()), this, SLOT(SaveKeepDay()));

	}

	pTranslateBtn = new WPushButton("翻译",this);
	pExChangeBtn  = new WPushButton("刷新",this);

	emit ShowHelp();

	InitCheckBox();

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
void CSysLogSet::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/SysLogSet.exe?'\",1250);  ";
	appSelf->quit();
}
//
void CSysLogSet::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "SysLogSetRes";
	WebSession::js_af_up += "')";
}
//
void CSysLogSet::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SysLogSet";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	InitCheckBox();
	m_pDeleteSetTable->HideAllErrorMsg();

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
	
	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

//
void CSysLogSet::InitCheckBox()
{
	string strSeveritiesValue = "", strFacilityValue = "", strTmp = "";
	strFacilityValue = GetIniFileString("QueryCond", "Facility", "", "syslog.ini");
	strSeveritiesValue = GetIniFileString("QueryCond", "Severities", "", "syslog.ini");

	std::list<string> pTemptList;
	list <string>::iterator listitem;
	
	map<string, int, less<string> > mapFacility;
	ParserToken(pTemptList, strFacilityValue.c_str(), ",");		
	for(listitem = pTemptList.begin(); listitem != pTemptList.end(); listitem++)
	{
		mapFacility[(*listitem)] = 0;
	}	
	for (unsigned j = 0; j < m_pListFacBox.size(); j++)
	{
		char chItem[32]  = {0};	
		sprintf(chItem, "%d", j);
		strTmp = chItem;

		if(mapFacility.find(strTmp) != mapFacility.end())
		{
			m_pListFacBox[j]->setChecked();
		}
		else
		{
			m_pListFacBox[j]->setUnChecked();
		}
	}

	pTemptList.clear();

	map<string, int, less<string> > mapSeverities;
	ParserToken(pTemptList, strSeveritiesValue.c_str(), ",");		
	for(listitem = pTemptList.begin(); listitem != pTemptList.end(); listitem++)
	{
		mapSeverities[(*listitem)] = 0;
	}
	for (unsigned j = 0; j < m_pListServerBox.size(); j++)
	{
		char chItem[32]  = {0};	
		sprintf(chItem, "%d", j);
		strTmp = chItem;

		if(mapFacility.find(strTmp) != mapFacility.end())
		{
			m_pListServerBox[j]->setChecked();
		}
		else
		{
			m_pListServerBox[j]->setUnChecked();
		}
	}
}

//
void CSysLogSet::SaveSeverities()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SysLogSet";
	LogItem.sHitFunc = "SaveSeverities";
	LogItem.sDesc = strModifyLevel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	string strSeveritiesValue = "";
	for (unsigned j = 0; j < m_pListServerBox.size(); j++)
	{
		if(m_pListServerBox[j]->isChecked())
		{
			char chItem[32]  = {0};	
			sprintf(chItem, "%d", j);

			strSeveritiesValue  += chItem;
			strSeveritiesValue  += ",";
		}
	}			

	WriteIniFileString("QueryCond", "Severities", strSeveritiesValue .c_str(), "syslog.ini");

	char buf[2048]={0};
	memset(buf,0,2048);
	sprintf(buf, "%s", strSeveritiesValue.c_str());

	if(!::PushMessage("SiteView70-SysLog","SvrChange",buf,strlen(buf)+1))
	{
		OutputDebugString("Push data failed");
		bEnd = true;	
		goto OPEnd;
	}
	
	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strTitle);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += strSaveSucess;
	WebSession::js_af_up += "')";
}

//
void CSysLogSet::SaveFacility()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SysLogSet";
	LogItem.sHitFunc = "SaveFacility";
	LogItem.sDesc = strModifyFacility;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	string strFacilityValue = "";
	for (unsigned j = 0; j < m_pListFacBox.size(); j++)
	{
		if(m_pListFacBox[j]->isChecked())
		{
			char chItem[32]  = {0};	
			sprintf(chItem, "%d", j);

			strFacilityValue += chItem;
			strFacilityValue += ",";
		}
	}			

	WriteIniFileString("QueryCond", "Facility", strFacilityValue.c_str(), "syslog.ini");

	char buf[2048]={0};
	memset(buf,0,2048);
	sprintf(buf, "%s", strFacilityValue.c_str());

	if(!::PushMessage("SiteView70-SysLog","FacilityChange",buf,strlen(buf)+1))
	{
		OutputDebugString("Push data failed");
		bEnd = true;	
		goto OPEnd;
	}

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strTitle);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	//触发保存成功事件
	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += strSaveSucess;
	WebSession::js_af_up += "')";
}

//
void CSysLogSet::SaveKeepDay()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SysLogSet";
	LogItem.sHitFunc = "SaveKeepDay";
	LogItem.sDesc = strDays;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	string strSaveKeepDay = pKeepDay->text();

	std::list<string> errorMsgList;
	if(!SV_Split::isNumeric(strSaveKeepDay))
	{
		errorMsgList.push_back("记录保持天数必须为数字！");
		m_pDeleteSetTable->ShowErrorMsg(errorMsgList);
		bEnd = true;	
		goto OPEnd;
	}

	WriteIniFileString("DelCond", "KeepDay", strSaveKeepDay.c_str(), "syslog.ini");

	char buf[2048]={0};
	memset(buf,0,2048);
	sprintf(buf, "%s", strSaveKeepDay.c_str());

	OutputDebugString("Push data failed");

	if(!::PushMessage("SiteView70-SysLog","KeepDayChange",buf,strlen(buf)+1))
	{
		OutputDebugString("Push data failed");
		return;
	}

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strTitle,strSaveKeepDay);

	m_pDeleteSetTable->HideAllErrorMsg();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	//触发保存成功事件
	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += strSaveSucess;
	WebSession::js_af_up += "')";
}


//
void CSysLogSet::DelSysLogData()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SysLogSet";
	LogItem.sHitFunc = "DelSysLogData";
	LogItem.sDesc = strDelRecord;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strEndTime = pManualEdit->text();
	TTime endtime = MakeTTime(strEndTime);

	//
	DeleteRecords("syslog", endtime);

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strDel,strTitle,strEndTime);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	//触发删除成功事件
	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += strDelSucess;
	WebSession::js_af_up += "')";
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
    app.setTitle("SysLogSet");

	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",app.root());
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());

	new WText("<div id='view_panel' class='panel_view'>", app.root());

    CSysLogSet sysLogSet(app.root());
	sysLogSet.appSelf = &app;
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