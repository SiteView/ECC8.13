#include "refreshform.h"

#include "../../kennel/svdb/libutil/time.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

extern void PrintDebugString(const char * szMsg);
extern WApplication *gMainApp;

static const char SV_REFRESH_QUEUE[]            = "SiteView70_RefreshInfo_%s";  // 刷新队列头

#define WTGET

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isMonitorDisable(string &szMonitorID, string szIDCUser = "default", string szAddr = "localhost")
{
	bool bDisable = false;
	OBJECT objMonitor = GetMonitor(szMonitorID, szIDCUser, szAddr);
	if(objMonitor != INVALID_VALUE)
	{
		MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
		if(mainnode != INVALID_VALUE)
		{
			string szDisable ("");
			FindNodeValue(mainnode, "sv_disable", szDisable);
			if(szDisable == "true")
			{
				bDisable =  true;
			}
			else if( szDisable == "time")
			{
				string szEndTime ("");
				FindNodeValue(mainnode, "sv_endtime", szEndTime);
				int nYear = 0, nMonth = 0, nDay = 0;
				int nHour = 0, nMinute = 0;
				if(!szEndTime.empty())
				{
					sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);

					svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

					svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
					if(ttime < ttend)
						bDisable =  true;
				}
			}
		}
		CloseMonitor(objMonitor);
	}
	return bDisable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string makeQueueName()
{
	string szTime("");
	svutil::TTime curTime = svutil::TTime::GetCurrentTimeEx();
	char chTime[32] = {0};
	sprintf(chTime, "%d%d%d%d%d%d%d", getpid(), curTime.GetYear(), curTime.GetMonth(), 
		curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
	szTime =  chTime;
	return szTime;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string getRefreshQueueName(const string &szIndex)
{
	string szQueueName("");;
	char szRefreshQueue[64] = {0};
	sprintf(szRefreshQueue, SV_REFRESH_QUEUE, FindSEID(szIndex).c_str());
	szQueueName = szRefreshQueue;
	return szQueueName;
}

SVRefresh::SVRefresh(WContainerWidget *parent)
:WTable(parent)
{
	m_pFailed = NULL;
	m_pStateList = NULL;
	m_pHideButton = NULL;
	m_pHideRefresh = NULL;
	m_pContentTable = NULL;
	m_pSubContent = NULL;
	m_pScrollArea = NULL;
	//m_pRunning = NULL;
	m_pCloseWnd = NULL;

	loadString();
	initForm();
	m_szQueueName = "";
}


void SVRefresh::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Close_Space",m_szClose);
			FindNodeValue(ResNode,"IDS_Close_Window",m_szCloseTip);
			FindNodeValue(ResNode,"IDS_Monitor_Name",m_szColName);
			FindNodeValue(ResNode,"IDS_State",m_szColState);
			FindNodeValue(ResNode,"IDS_Description",m_szColDesc);
			FindNodeValue(ResNode,"IDS_Result_of_Refresh_Monitor",m_szResult);
			FindNodeValue(ResNode,"IDS_Normal",m_szNormal);
			FindNodeValue(ResNode,"IDS_Error",m_szError);
			FindNodeValue(ResNode,"IDS_Warning",m_szWarning);
			FindNodeValue(ResNode,"IDS_Refreshing",m_szRefreshStart);
			FindNodeValue(ResNode,"IDS_Refresh_Failed",m_szRefreshFailed);
			FindNodeValue(ResNode,"IDS_Refresh_Finish",m_szRefreshEnd);
			FindNodeValue(ResNode,"IDS_Refresh_Not_Available",m_szDisable);
			FindNodeValue(ResNode,"IDS_Refresh_Too_Long_Time",m_szRefreshTimeout);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);

		}
		CloseResource(objRes);
	}
	/*
	m_szTitle    = "刷新监测器";   // IDS_Refresh_Monitor
	m_szClose    = "&nbsp;&nbsp;关闭&nbsp;&nbsp;";  //
	m_szCloseTip = "关闭窗口";   // IDS_Close_Window
	m_szColName  = "监测器名称";  // IDS_Monitor_Name
	m_szColState = "状态";       // IDS_State
	m_szColDesc  = "描述";		 // IDS_Description
	m_szResult   = "监测器刷新结果: ";    // IDS_Result_of_Refresh_Monitor
	m_szNormal   = "正常";		// IDS_Normal
	m_szError    = "错误";		// IDS_Error
	m_szWarning  = "危险";		// IDS_Warning
	m_szRefreshStart = "正在刷新...";      // IDS_Refreshing
	m_szRefreshFailed = "刷新过程异常终止...";   // IDS_Refresh_Failed
	m_szRefreshEnd   = "刷新完成...";            // IDS_Refresh_Finish
	m_szDisable      = "监测器被禁止无法进行刷新操作，<BR>请启用后在进行刷新操作。";   // IDS_Refresh_Not_Available
	m_szRefreshTimeout = "刷新超时...";         // IDS_Refresh_Too_Long_Time
	*/
}

void SVRefresh::initForm()
{
	strListHeights = "";
	strListPans = "";
	strListTitles = "";

	//new WText("\n<SCRIPT language='JavaScript' src='/scroll.js'></SCRIPT>", elementAt(0, 0));
	int nRow = numRows();
	new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", elementAt(nRow, 0));
	new WText("<div id='view_panel' class='panel_view'>", elementAt(nRow, 0));
	createTitle();
	createContain();
	if(m_pSubContent)
	{
		createState();
	}
	createOperate();
	createHideButton();
	new WText("</div>", elementAt(nRow, 0));
	AddJsParam("listheight", strListHeights, elementAt(nRow, 0));
	AddJsParam("listtitle", strListTitles, elementAt(nRow, 0));
	AddJsParam("listpan", strListPans, elementAt(nRow, 0));
	AddJsParam("uistyle", "viewpanandlist", elementAt(nRow, 0));
	AddJsParam("fullstyle", "true", elementAt(nRow, 0));
	AddJsParam("bGeneral", "false", elementAt(nRow, 0));
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", elementAt(nRow, 0));
}

void SVRefresh::AddJsParam(const std::string name, const std::string value, WContainerWidget *parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}

//翻译后刷新
void SVRefresh::ExChange()
{
	PrintDebugString("---------Refresh------------\n");
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/refresh.exe?'\",1250);  ";
	appSelf->quit();
}
//翻译
void SVRefresh::Translate()
{
	PrintDebugString("---------Translate------------\n");
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "refreshRes";
	WebSession::js_af_up += "')";
}

void SVRefresh::createState()
{
	int nRow = m_pSubContent->numRows();
	WText * pStart = new WText(m_szRefreshStart, m_pSubContent->elementAt(nRow, 0));
	//if(pStart)
	// pStart->setStyleClass("refreshinfo");

	string strTmp = "<div id='";
	strTmp += "listpan1";
	strTmp += "' class='panel_item'>";
	new WText(strTmp, (WContainerWidget *)m_pSubContent->elementAt(nRow + 1, 0));

	m_pStateList = new WTable(m_pSubContent->elementAt(nRow + 1, 0));

	new WText("</div>", (WContainerWidget *)m_pSubContent->elementAt(nRow + 1, 0));
	if(m_pStateList)
	{
		strListHeights += "160";
		strListHeights += ",";
		strListPans += "listpan1";
		strListPans += ",";
		strListTitles +=  m_pStateList->formName();
		strListTitles += ",";

		// m_pStateList->setStyleClass("t3");
		new WText(m_szColName, m_pStateList->elementAt(0, 0));
		new WText(m_szColState, m_pStateList->elementAt(0, 1));
		new WText(m_szColDesc, m_pStateList->elementAt(0, 2));
		//m_pStateList->GetRow(0)->setStyleClass("t3title");
		//m_pStateList->elementAt(nRow, 0)->setStyleClass("cell_40");
		//m_pStateList->elementAt(nRow, 0)->setContentAlignment(AlignCenter);
		//m_pStateList->elementAt(nRow, 1)->setStyleClass("cell_10");
		//m_pStateList->elementAt(nRow, 1)->setContentAlignment(AlignCenter);
		//m_pStateList->elementAt(nRow, 2)->setStyleClass("tcelltopright");
		//m_pStateList->elementAt(nRow, 2)->setContentAlignment(AlignCenter);
		//m_pStateList->setCellPadding(0);
		//m_pStateList->setCellSpaceing(0);
	}
	m_pFailed = new WText(m_szRefreshFailed, m_pSubContent->elementAt(nRow + 2, 0));
	if(m_pFailed)
	{
		//m_pFailed->setStyleClass("refresherrors");
		m_pFailed->hide();
	}
}

void SVRefresh::createTitle()
{
}

void SVRefresh::createContain()
{
	int nRow = numRows() - 1;

	//m_pRunning = new WImage("../Images/loading.gif", elementAt(nRow,0));

	/* WText *pTitle = new WText(m_szResult, elementAt(nRow,0));
	if(pTitle)
	pTitle->setStyleClass("wintestt1title");*/

	//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", elementAt(nRow, 0));

	//pTranslateBtn = new WPushButton(strTranslate, elementAt(nRow, 0));
	//connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
	//   pTranslateBtn->setToolTip(strTranslateTip);
	//pTranslateBtn->hide();

	//new WText("&nbsp;&nbsp;&nbsp;&nbsp;",elementAt(nRow, 0));

	//pExChangeBtn = new WPushButton(strRefresh, elementAt(nRow, 0));
	//connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	//pExChangeBtn->setToolTip(strRefreshTip);
	//pExChangeBtn->hide();

	//int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	//if(bTrans == 1)
	//{
	//	pTranslateBtn->show();
	//	pExChangeBtn->show();
	//}
	//else
	//{
	//	pTranslateBtn->hide();
	//	pExChangeBtn->hide();
	//}

	//nRow ++;
	m_pPopTable = new WSPopTable((WContainerWidget *)elementAt(nRow,0));
	if(m_pPopTable)
	{
		m_pPopTable->AppendRows(m_szResult);
		m_pPopTable->GeRowActionTable(0)->setStyleClass("widthauto");
		m_pContentTable = m_pPopTable->GeRowContentTable(0);
		if(m_pContentTable)
		{
			nRow = m_pContentTable->numRows();
			m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
			m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);        
		}
	}
}

void SVRefresh::createOperate()
{
	//int nRow = numRows();
	//m_pCloseWnd = new WPushButton(m_szClose, (WContainerWidget*)m_pPopTable->GeRowActionTable(0)->elementAt(0, 0));
	m_pCloseWnd = new WSPopButton((WContainerWidget*)m_pPopTable->GeRowActionTable(0)->elementAt(0, 0), m_szClose, "button_bg_m.png", m_szCloseTip, true);
	if(m_pCloseWnd)
	{
		m_pCloseWnd->setToolTip(m_szCloseTip);
		WObject::connect(m_pCloseWnd, SIGNAL(clicked()), "window.close();", WObject::ConnectionType::JAVASCRIPT);
	}
	m_pPopTable->GeRowActionTable(0)->elementAt(0, 0)->setContentAlignment(AlignCenter);
}

void SVRefresh::clearEnvironment()
{
	PrintDebugString("close windows");
	if(!m_szQueueName.empty())
	{
		if(!DeleteQueue(m_szQueueName))
		{
			m_szQueueName = "delete queue failed! queue name is " + m_szQueueName;
			PrintDebugString(m_szQueueName.c_str());
		}
		m_szQueueName = "";
	}
	//if(gMainApp)
	//    gMainApp->quit();
	WebSession::js_af_up = "window.close();";
}

void SVRefresh::createHideButton()
{
	//int nRow = numRows();
	m_pHideButton = new WPushButton(m_szClose, (WContainerWidget*)m_pPopTable->GeRowActionTable(0)->elementAt(0, 2));
	if(m_pHideButton)
	{
		m_pHideButton->hide();
		WObject::connect(m_pHideButton, SIGNAL(clicked()), this, SLOT(showresult()));
	}

	m_pHideRefresh = new WPushButton(m_szClose, (WContainerWidget*)m_pPopTable->GeRowActionTable(0)->elementAt(0, 3));
	if(m_pHideRefresh)
	{
		m_pHideRefresh->hide();
		WObject::connect(m_pHideRefresh, SIGNAL(clicked()), this, SLOT(getresult()));
	}
	this->parent();
}

SVRefresh::~SVRefresh()
{
	if(!m_szQueueName.empty())
	{
		DeleteQueue(m_szQueueName);
		m_szQueueName = "";
	}
}

void SVRefresh::refresh()
{
	//    PrintDebugString("refresh");
	static const string szRefreshEnd = "Refresh_END";
	if(!m_szQueueName.empty())
	{
		DeleteQueue(m_szQueueName);
		m_szQueueName = "";
	}
	m_nTimes = 0;
	m_bGetDeviceData = false;
	m_szDeviceName = "";
	if(m_pFailed)
		m_pFailed->hide();

	if(m_pStateList)
	{
		while ( m_pStateList->numRows() > 1)
			m_pStateList->deleteRow(m_pStateList->numRows() - 1);
	}

	char szQuery[4096]={0};
	int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", szQuery, nSize);
#else
	char *tmpquery = getenv("QUERY_STRING");
	if(tmpquery)
		strcpy(szQuery,tmpquery);
#endif
	if(szQuery)
	{
		//            PrintDebugString(szQuery);
		/*if(m_pRunning)
		m_pRunning->show();*/
		char *pPos= strstr(szQuery, "queuename=");
		if(pPos)
		{
			char szQueue[32] = {0};
			sscanf(pPos, "queuename= %[0-9]", szQueue);
			//                PrintDebugString(szQueue);
			m_szQueueName = szQueue;
		}
		else
		{
			pPos = strstr(szQuery, "monitorid=");
			if(pPos)
			{
				pPos += strlen("monitorid=");
				string szMonitorID = pPos;
				m_szQueueName = makeQueueName();
				CreateQueue(m_szQueueName, 1);
				string szRefreshQueue(getRefreshQueueName(szMonitorID)); 
				CreateQueue(szRefreshQueue, 1);
				int nSize = static_cast<int>(szMonitorID.length()) + 2;
				char *pszRefreshMonitor = new char[nSize];
				if(pszRefreshMonitor)
				{
					memset(pszRefreshMonitor, 0, nSize);
					strcpy( pszRefreshMonitor, szMonitorID.c_str());
					if(!isMonitorDisable(szMonitorID))
					{
						if(!::PushMessage(szRefreshQueue, m_szQueueName, pszRefreshMonitor, nSize))
							PrintDebugString("PushMessage into SiteView70_RefreshInfo queue failed!");
						delete []pszRefreshMonitor;
					}
					else
					{
						if(!::PushMessage(m_szQueueName, "DISABLE", pszRefreshMonitor, nSize))
							PrintDebugString("PushMessage into queue failed!");
						if(!::PushMessage(m_szQueueName, szRefreshEnd, pszRefreshMonitor, nSize))
							PrintDebugString("PushMessage into queue failed!");
					}
				}
			}
		}
		if(m_pHideRefresh && !m_szQueueName.empty())
		{
			if(m_pCloseWnd)
				m_pCloseWnd->setEnabled(true);
			string szCmd = m_pHideRefresh->getEncodeCmd("xclicked()");
			if(!szCmd.empty())
			{
				szCmd = "update('" + szCmd + "');";
				//                    PrintDebugString(szCmd.c_str());
				WebSession::js_af_up = szCmd;
			}
		}
	}


	//int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	//if(bTrans == 1)
	//{
	//	pTranslateBtn->show();
	//	pExChangeBtn->show();
	//}
	//else
	//{
	//	pTranslateBtn->hide();
	//	pExChangeBtn->hide();
	//}

}

void SVRefresh::showresult()
{
	if(m_pHideRefresh && !m_szQueueName.empty())
	{
		string szCmd = m_pHideRefresh->getEncodeCmd("xclicked()");
		if(!szCmd.empty())
		{
			szCmd = "addLoadEvent(_OnLoad());update('" + szCmd + "');";
			if(m_pStateList)
			{
				int nRow = m_pStateList->numRows() - 1;
				string szName = m_pStateList->GetRow(nRow)->formName();
				szCmd = "document.getElementById(\"" + szName + "\").scrollIntoView(true);" + szCmd;
			}
			WebSession::js_af_up = szCmd;
		}
	}
	else if(m_szQueueName.empty())
	{
		Sleep( 5000 );
		WebSession::js_af_up = "window.close();";
	}
}

void SVRefresh::getresult()
{
	static const string szRefreshOK = "Refresh_OK";
	static const string szRefreshEnd = "Refresh_END";
	static const string sv_disable_sign = "DISABLE";
	static const int nMaxTimes = 20;

	string label;
	svutil::TTime ct;
	unsigned int len=0;

	MQRECORD mrd = PopMessage(m_szQueueName, 5000);
	if(mrd == INVALID_VALUE)
	{
		m_nTimes ++;
		//PrintDebugString("Pop Message Failed");
		goto ExitFunc;
	}

	if(!GetMessageData(mrd, label, ct, NULL, len))
	{
		PrintDebugString("Get message data failed");
		goto ExitFunc;
	}

	//PrintDebugString(label.c_str());
	if(label == szRefreshOK)
	{
		char * pszBuffer = new char[len];
		if(pszBuffer)
		{
			if(!::GetMessageData(mrd, label, ct, pszBuffer, len))
			{
				PrintDebugString("Get message data failed");
				delete []pszBuffer;
				goto ExitFunc;
			}

			m_nTimes = 0;
			addDynData(pszBuffer);
			delete []pszBuffer;
		}
	}
	else if(label == sv_disable_sign)
	{
		char * pszBuffer = new char[len];
		if(pszBuffer)
		{
			if(!::GetMessageData(mrd, label, ct, pszBuffer, len))
			{
				PrintDebugString("Get message data failed");
				delete []pszBuffer;
				goto ExitFunc;
			}

			m_nTimes = 0;
			addDisableDyn(pszBuffer);
			delete []pszBuffer;
		}
	}
	else
	{
		if(!DeleteQueue(m_szQueueName))
		{
			m_szQueueName = "delete queue failed! queue name is " + m_szQueueName;
			PrintDebugString(m_szQueueName.c_str());
		}

		m_szQueueName = "";
		if(m_pCloseWnd)
			m_pCloseWnd->setEnabled(true);

		/*if(m_pRunning)
		m_pRunning->hide();*/

		if(m_pFailed)
		{
			m_pFailed->show();
			if(label == szRefreshEnd)
			{
				// m_pFailed->setStyleClass("refreshinfo");
				m_pFailed->setText(m_szRefreshEnd);
			}
			else
			{
				m_pFailed->setText(m_szRefreshFailed);
				//m_pFailed->setStyleClass("refresherrors");
			}
		}
	}

ExitFunc:
	CloseMQRecord(mrd);
	if(m_nTimes >= nMaxTimes)
	{
		if(!DeleteQueue(m_szQueueName))
		{
			m_szQueueName = "delete queue failed! queue name is " + m_szQueueName;
			PrintDebugString(m_szQueueName.c_str());
		}
		m_szQueueName = "";

		if(m_pCloseWnd)
			m_pCloseWnd->setEnabled(true);

		if(m_pFailed)
		{
			m_pFailed->setText(m_szRefreshTimeout);
			m_pFailed->show();
		}

		/* if(m_pRunning)
		m_pRunning->hide();*/
	}

	if(m_pHideButton)
	{
		string szCmd = m_pHideButton->getEncodeCmd("xclicked()");
		if(!szCmd.empty())
		{
			szCmd = "update('" + szCmd + "');";
			WebSession::js_af_up = szCmd;
		}
	}
}

void SVRefresh::addDisableDyn(const char* pszMonitorID)
{
	if(m_pStateList)
	{
		int nRow = m_pStateList->numRows();

		sv_dyn dyn;

		WImage *pState = new WImage("/images/state_stop.gif", m_pStateList->elementAt(nRow, 1));
		WText  *pName  = new WText("", m_pStateList->elementAt(nRow, 0));
		WText  *pDesc  = new WText(m_szDisable, m_pStateList->elementAt(nRow, 2));
		//m_pStateList->elementAt(nRow, 0)->setStyleClass("tcell");
		//m_pStateList->elementAt(nRow, 1)->setStyleClass("tcell");
		//m_pStateList->elementAt(nRow, 2)->setStyleClass("tcellright");
		//m_pStateList->elementAt(nRow, 1)->setContentAlignment(AlignCenter);

		if(!m_bGetDeviceData)
		{
			string szDeviceID = FindParentID(pszMonitorID);
			this->getDeviceData(szDeviceID);
			m_bGetDeviceData = true;
		}
		OBJECT objMonitor = GetMonitor(pszMonitorID);
		if(objMonitor != INVALID_VALUE)
		{
			MAPNODE node = GetMonitorMainAttribNode(objMonitor);
			if(node != INVALID_VALUE)
			{
				string szName = "";
				FindNodeValue(node, "sv_name", szName);
				//PrintDebugString(szName.c_str());
				if(pName)
					pName->setText(m_szDeviceName + ":" + szName);
			}
		}

	}
}
void SVRefresh::addDynData(const char* pszMonitorID)
{
	if(m_pStateList)
	{
		int nRow = m_pStateList->numRows();

		sv_dyn dyn;

		WImage *pState = new WImage("", m_pStateList->elementAt(nRow, 1));
		WText  *pName  = new WText("", m_pStateList->elementAt(nRow, 0));
		WText  *pDesc  = new WText("", m_pStateList->elementAt(nRow, 2));

		//m_pStateList->elementAt(nRow, 0)->setStyleClass("tcell");
		//m_pStateList->elementAt(nRow, 1)->setStyleClass("tcell");
		//m_pStateList->elementAt(nRow, 2)->setStyleClass("tcellright");
		//m_pStateList->elementAt(nRow, 1)->setContentAlignment(AlignCenter);

		if(GetSVDYN(pszMonitorID, dyn))
		{
			if(pState)
			{
				switch(dyn.m_state)
				{
				case 0:
					pState->setImageRef("/images/state_grey.gif");
					break;
				case 1:
					pState->setImageRef("/images/state_green.gif");
					break;
				case 2:
					pState->setImageRef("/images/state_yellow.gif");
					break;
				case 3:
				case 5:
					pState->setImageRef("/images/state_red.gif");
					break;
				case 4:
					pState->setImageRef("/images/state_stop.gif");
				}
			}

			//if(dyn.m_displaystr)
			//    PrintDebugString(dyn.m_displaystr);
			//else
			//    PrintDebugString("display string is null");

			string szDisplay("");
			if(dyn.m_displaystr)
				szDisplay = dyn.m_displaystr;            
			int nPos = static_cast<int>(szDisplay.find(",", 0));
			while (nPos > 0)
			{
				szDisplay = szDisplay.substr(0, nPos + 1) + "<BR>" + szDisplay.substr(nPos + 1, szDisplay.length() - nPos + 1);
				nPos += 6;
				nPos = static_cast<int>(szDisplay.find(",", nPos));
			}
			if(pDesc)
				pDesc->setText(szDisplay);
		}
		if(!m_bGetDeviceData)
		{
			string szDeviceID = FindParentID(pszMonitorID);
			this->getDeviceData(szDeviceID);
			m_bGetDeviceData = true;
		}
		OBJECT objMonitor = GetMonitor(pszMonitorID);
		if(objMonitor != INVALID_VALUE)
		{
			MAPNODE node = GetMonitorMainAttribNode(objMonitor);
			if(node != INVALID_VALUE)
			{
				string szName = "";
				FindNodeValue(node, "sv_name", szName);
				//PrintDebugString(szName.c_str());
				if(pName)
					pName->setText(m_szDeviceName + ":" + szName);
			}
		}
	}
}


void SVRefresh::getDeviceData(string &szDeviceID)
{
	if(this->m_pContentTable)
	{
		OBJECT objDevice = GetEntity(szDeviceID);
		if(objDevice != INVALID_VALUE)
		{ 
			MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
			if(mainnode != INVALID_VALUE)
			{
				FindNodeValue(mainnode, "sv_name", m_szDeviceName);
				string szDeviceType = "";
				FindNodeValue(mainnode, "sv_devicetype", szDeviceType);
				OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType);
				if(objDeviceTmp != INVALID_VALUE)
				{
					MAPNODE node = GetEntityTempletMainAttribNode(objDeviceTmp);
					if(node != INVALID_VALUE)
						FindNodeValue(node, "sv_name", m_szDeviceType);
					CloseEntityTemplet(objDeviceTmp);
				}
			}
			CloseEntity(objDevice);
		}
	}
}