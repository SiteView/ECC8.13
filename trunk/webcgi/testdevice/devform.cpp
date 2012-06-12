#include "devform.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WLineEdit"

#include "../treeview/debuginfor.h"

#include "../svtable/WSPopTable.h"
#include "../svtable/WSPopButton.h"

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

extern void unescape_url(char *url); 

typedef bool (DeviceTest)(const char* szQuery, char* szReturn, int &nSize);

static const int  svBufferSize                  = 1024 * 10;
static const char SV_REFRESH_QUEUE[]            = "SiteView70_RefreshInfo_%s";  // 刷新队列头

#define WTGET

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadFromRetQueue(const string &szQueue, char *pBuffer, int &nRetSize, string szIDCUser = "default",
                       string szAddr = "localhost")
{
    bool bRet = false;
    static const string szDynLabel = "DYNPARAM";
    static const string szEnd   = "DYNEND";

    MQRECORD mrd = PopMessage(szQueue, 2000, szIDCUser, szAddr);
	if(mrd != INVALID_VALUE)
	{
        string szLabel("");
        svutil::TTime ct;
	    unsigned int len = 0;
	    if(GetMessageData(mrd, szLabel, ct, NULL, len))
	    {
            if(szLabel == szDynLabel)
            {
                if(pBuffer && len <= static_cast<unsigned int>(nRetSize))
                {
                    if(!::GetMessageData(mrd, szLabel, ct, pBuffer, len))
                    {
                        memset(pBuffer, 0, nRetSize);
                    }
                    else
                    {
                        nRetSize = len;
                        bRet = true;
                    }
                }
            }
            else if(szLabel == szEnd)
            {
                bRet = true;
            }
        }
    }
    return bRet;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize, string szIDCUser = "default",
                       string szAddr = "localhost")
{
    static const string szLabel = "DYNPARAM";
    static const string szDLLName = "DLL";
    static const string szFUNC = "FUNC";
    static const string szParam = "PARAMS";
    static const char szSeparator = '#';

    bool bRet = false;
    string szRefreshQueue(getRefreshQueueName(szIndex)), szQueueName(makeQueueName());
    string szParamQueue(szQueueName + "_R"), szRetQueue(szQueueName + "_W");
    CreateQueue(szRetQueue, 1, szIDCUser, szAddr);
    CreateQueue(szParamQueue, 1, szIDCUser, szAddr);
    CreateQueue(szRefreshQueue, 1, szIDCUser, szAddr);

    int nDllSize = static_cast<int>(szDll.size()) + 2, nFuncSize = static_cast<int>(szFunc.size()) + 2;

    char *pDll = new char[nDllSize];
    if(pDll)
    {
        memset(pDll, 0, nDllSize);
        strcpy(pDll, szDll.c_str());
        if(PushMessage(szParamQueue, szDLLName, pDll, nDllSize, szIDCUser, szAddr))
        {
            char *pFunc = new char[nFuncSize];
            if(pFunc)
            {
                memset(pFunc, 0, nFuncSize);
                strcpy(pFunc, szFunc.c_str());
                if(PushMessage(szParamQueue, szFUNC, pFunc, nFuncSize, szIDCUser, szAddr))
                {
                    if(PushMessage(szParamQueue, szParam, pszQuery, nSize, szIDCUser, szAddr))
                    {
                        int nQueueSize = static_cast<int>(szQueueName.size()) + 2;
                        char *pszQueue = new char[nQueueSize];
                        if(pszQueue)
                        {
                            memset(pszQueue, 0, nQueueSize);
                            strcpy(pszQueue, szQueueName.c_str());
                            if(PushMessage(szRefreshQueue, szLabel, pszQueue, nQueueSize, szIDCUser, 
                                szAddr))
                            {
                                int nTimes = 0;
                                while(!bRet)
                                {
                                    if(nTimes >= 40)
                                        break;
                                    bRet = ReadFromRetQueue(szRetQueue, pBuffer, nRetSize, szIDCUser, szAddr);
                                    nTimes ++;
                                }
                            }
                            delete []pszQueue;
                        }
                    }
                }
                delete []pFunc;
            }
        }
        delete []pDll;
    }
    DeleteQueue(szRetQueue, szIDCUser, szAddr);

    return bRet;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef WIN32
DWORD WINAPI SVDeviceTest::ThreadFunc(LPVOID lpParam) 
{ 
    PrintDebugString(((SVDeviceTest*)lpParam)->m_szQuery.c_str());
    if(!((SVDeviceTest*)lpParam)->m_szQuery.empty())
    {
        ((SVDeviceTest*)lpParam)->TestDevice();
    }
    return 0; 
}
#else
#endif

SVDeviceTest::SVDeviceTest(WContainerWidget *parent)
:WContainerWidget(parent)
{
    m_hThread = NULL;
    m_pState = NULL;
    m_pContentTable = NULL;
    m_pSubContent = NULL;
    m_pHideButton = NULL;
    m_pClose = NULL;
    m_pApp = NULL;
    m_bFirst = true;
	m_pFinish = NULL;
	m_pWait  = NULL;

    //setStyleClass("t5");
    loadString();
    //initForm();
	NewInitForm();
}


void SVDeviceTest::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Device_Test",			m_szTitle);
			FindNodeValue(ResNode,"IDS_Close_Space",			m_szClose);
			FindNodeValue(ResNode,"IDS_Close_Window",			m_szCloseTip);
			FindNodeValue(ResNode,"IDS_Device_Test_Result",		m_szResult);
			FindNodeValue(ResNode,"IDS_Testing_Please_Wait",	m_szWaiting);
			FindNodeValue(ResNode,"IDS_Open_Interface_Failed",	m_szFuncErr);
			FindNodeValue(ResNode,"IDS_Open_Dll_Failed",		m_szDllErr);
			FindNodeValue(ResNode,"IDS_Test_Success",			m_szTestSucc);
			FindNodeValue(ResNode,"IDS_Test_Failed",			m_szTestFail);
			FindNodeValue(ResNode,"IDS_Test_Time_Out",			m_szTimeout);
			FindNodeValue(ResNode,"IDS_Request_String_Is_Null",	m_szQueryEmpty);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);

		}
		CloseResource(objRes);
	}
/*
	// 以下除了 "关闭窗口" ，其余在 resource 中均没有
    m_szTitle    = "设备测试";						 // IDS_Device_Test
    m_szClose    = "&nbsp;&nbsp;关闭&nbsp;&nbsp;";   // IDS_Close_Space(已有的)
    m_szCloseTip = "关闭窗口";						// IDS_Close_Window (已有的)
    m_szResult   = "设备测试结果 ";				// IDS_Device_Test_Result
    m_szWaiting  = "设备测试中，请等候...";		 // IDS_Testing_Please_Wait
    m_szFuncErr  = "打开接口函数失败...";		// IDS_Open_Interface_Failed
    m_szDllErr   = "打开动态链接库失败...";		// IDS_Open_Dll_Failed
    m_szTestSucc = "测试完成...";				// IDS_Test_Success
    m_szTestFail = "测试失败...";				 // IDS_Test_Failed
    m_szTimeout  = "测试超时...";				// IDS_Test_Time_Out
    m_szQueryEmpty = "请求字符串为空...";		 // IDS_Request_String_Is_Null
	*/
}

void SVDeviceTest::initForm()
{
	//Jansion.zhou 2007-01-07
 //   int nRow = numRows();
	//new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", elementAt(nRow, 0));

 //   createContain();
 //   if(m_pSubContent)
 //   {
 //       m_pSubContent->setStyleClass("t3");
 //   }
 //   createOperate();
 //   nRow = numRows();
 //   m_pHideButton = new WPushButton("hide button", elementAt(nRow, 0));
 //   if(m_pHideButton)
 //   {
 //       WObject::connect(m_pHideButton, SIGNAL(clicked()), this, SLOT(showresult()));
 //       m_pHideButton->hide();
 //   }
}

//添加客户端脚本变量
void SVDeviceTest::AddJsParam(const std::string name, const std::string value,  WContainerWidget * parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}
//
////添加客户端脚本变量
//void SVDeviceTest::AddJsParam(const std::string name, const std::string value)
//{  
//	std::string strTmp("");
//	strTmp += "<SCRIPT language='JavaScript' > var ";
//	strTmp += name;
//	strTmp += "='";
//	strTmp += value;
//	strTmp += "';</SCRIPT>";
//	new WText(strTmp, this);
//}

void SVDeviceTest::NewInitForm()
{
	strListHeights = "";
	strListPans = "";
	strListTitles = "";
	
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>",this);

    NewCreateContain();

	new WText("</div>", this);
	AddJsParam("listheight", strListHeights, this);
	AddJsParam("listtitle", strListTitles, this);
	AddJsParam("listpan", strListPans, this);
	AddJsParam("uistyle", "viewpanandlist", this);
	AddJsParam("fullstyle", "true", this);
	AddJsParam("bGeneral", "false", this);
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", this);
}

//翻译后刷新
void SVDeviceTest::ExChange()
{
	string strNRefrsh = "setTimeout(\"location.href ='/fcgi-bin/testdevice.exe?";
	strNRefrsh += strParam;
	strNRefrsh += "'\",1250);  ";
	WebSession::js_af_up=strNRefrsh;
	appSelf->quit();
}
//翻译
void SVDeviceTest::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "testdeviceRes";
	WebSession::js_af_up += "')";
}

void SVDeviceTest::createContain()
{
	//Jansion.zhou 2007-01-07
//    int nRow = numRows();
//    WText *pTitle = new WText(m_szResult, elementAt(nRow,0));
//
//	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", elementAt(nRow, 0));
//
//	pTranslateBtn = new WPushButton(strTranslate, elementAt(nRow, 0));
//	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
//    pTranslateBtn->setToolTip(strTranslateTip);
//	pTranslateBtn->hide();
//
//	new WText("&nbsp;&nbsp;&nbsp;&nbsp;",elementAt(nRow, 0));
//
//	pExChangeBtn = new WPushButton(strRefresh, elementAt(nRow, 0));
//	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
//	pExChangeBtn->setToolTip(strRefreshTip);
//	pExChangeBtn->hide();
//
//	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
//	if(bTrans == 1)
//	{
//		pTranslateBtn->show();
//		pExChangeBtn->show();
//	}
//	else
//	{
//		pTranslateBtn->hide();
//		pExChangeBtn->hide();
//	}
//
////    if(pTitle)
////        pTitle->setStyleClass("wintestt1title");
//    nRow ++;
//    m_pContentTable = new WTable(elementAt(nRow,0));	
//    if(m_pContentTable)
//    {
//        m_pContentTable->setCellPadding(0);
//        m_pContentTable->setCellSpaceing(0);
//
//        m_pScrollArea = new WScrollArea(elementAt(nRow,0));
//        if(m_pScrollArea)
//        {
//            m_pScrollArea->setStyleClass("wintestarea"); 
//            m_pScrollArea->setWidget(m_pContentTable);
//        }
//        m_pContentTable->setStyleClass("wintestarea"); 
//        elementAt(nRow, 0)->setStyleClass("t7");
//
//        nRow = m_pContentTable->numRows();
//        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
//		m_pSubContent->setStyleClass("t3"); 
//        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
//    }
}

//Jansion.zhou
void SVDeviceTest::NewCreateContain()
{
	m_pContentTable = new WSPopTable(this);
    if(m_pContentTable)
    {
		m_pContentTable->AppendRows(m_szResult);
		m_pWait = new WText("", (WContainerWidget *)m_pContentTable->GeRowContentTable(0)->elementAt(0, 0));

		string strTmp = "<div id='";
		strTmp += "listpan1";
		strTmp += "' class='panel_item'>";
		new WText(strTmp, (WContainerWidget *)m_pContentTable->GeRowContentTable(0)->elementAt(1, 0));

		m_pSubContent = new WTable(m_pContentTable->GeRowContentTable(0)->elementAt(1, 0));
		if (!m_pSubContent)
		{
			return;
		}

		new WText("</div>", (WContainerWidget *)m_pContentTable->GeRowContentTable(0)->elementAt(1, 0));
		
		//设置高度
		strListHeights += "200";
		strListHeights += ",";
		strListPans += "listpan1";
		strListPans += ",";
		strListTitles +=  m_pSubContent->formName();
		strListTitles += ",";
		
		m_pFinish = new WText("", (WContainerWidget *)m_pContentTable->GeRowContentTable(0)->elementAt(2, 0));

		m_pContentTable->GeRowActionTable(0)->setStyleClass("widthauto");

		m_pClose = new WSPopButton(m_pContentTable->GeRowActionTable(0)->elementAt(0, 0), m_szClose, "button_bg_m.png", m_szClose, false);
		if(m_pClose)
		{
			m_pClose->setToolTip(m_szCloseTip);
			WObject::connect(m_pClose, SIGNAL(clicked()), this, SLOT(closeWnd()));
		}
		m_pContentTable->GeRowActionTable(0)->elementAt(0, 0)->setContentAlignment(AlignCenter);
    }

	//int RowList = m_pContentTable->GeRowActionTable(0)->numRows();
	m_pHideButton = new WPushButton("hide button", m_pContentTable->GeRowActionTable(0)->elementAt(0, 1));
    if(m_pHideButton)
    {
		OutputDebugString("--------------- is   --------------\n");
        WObject::connect(m_pHideButton, SIGNAL(clicked()), this, SLOT(showresult()));
        m_pHideButton->hide();
    }


	pTranslateBtn = new WPushButton(strTranslate, m_pContentTable->GeRowActionTable(0)->elementAt(0, 2));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    //pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	pExChangeBtn = new WPushButton(strRefresh, m_pContentTable->GeRowActionTable(0)->elementAt(0, 3));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	//pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();
}

void SVDeviceTest::createOperate()
{
    //int nRow = numRows();
    //m_pClose = new WPushButton(m_szClose, (WContainerWidget*)elementAt(nRow, 0));
    //if(m_pClose)
    //{
    //    m_pClose->setToolTip(m_szCloseTip);
    //    WObject::connect(m_pClose, SIGNAL(clicked()), this, SLOT(closeWnd()));
    //}
    //elementAt(nRow, 0)->setContentAlignment(AlignCenter);
}

void SVDeviceTest::NewCreateOperate()
{
	//m_pClose = new WSPopButton(m_pContentTable->GeRowActionTable(0)->elementAt(0, 0), m_szClose, "button_bg_m.png", m_szClose, false);
 //   if(m_pClose)
 //   {
 //       m_pClose->setToolTip(m_szCloseTip);
 //       WObject::connect(m_pClose, SIGNAL(clicked()), this, SLOT(closeWnd()));
 //   }
 //   m_pContentTable->GeRowActionTable(0)->elementAt(0, 0)->setContentAlignment(AlignCenter);
}

string SVDeviceTest::getCmd()
{
    string szCmd = "";
    if(m_pHideButton)
    {
        szCmd = m_pHideButton->getEncodeCmd("xclicked()");
		OutputDebugString("--------------- m_pHideButton is clicked --------------\n");
    }
    return szCmd;
}

void SVDeviceTest::refresh()
{
	OutputDebugString("--------------- refresh() --------------\n");

	if (m_pFinish)
	{
		m_pFinish->setText("");
	}

    char szQuery[4096] = {0};
    int nSize = 4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", szQuery,nSize);
#else
	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery != NULL)
	{
		strcpy(szQuery,tmpquery);
	}
	else
	{
		return;
	}
#endif

	strParam = szQuery;	
    if(strlen(szQuery) > 0)
    {
        unescape_url(szQuery);
        m_szQuery = szQuery;
        if(m_pSubContent)
        {
            m_pSubContent->clear();
            //new WText(m_szWaiting, m_pSubContent->elementAt(0, 0));
			if(m_pWait)
				m_pWait->setText(m_szWaiting);
        }
		//Jansion.zhou 2007-01-07
        //if(m_pClose)
        //    m_pClose->setEnabled(false);

		//if (m_pClose)
  //          m_pClose->SetDisable();
		OutputDebugString("--------------- m_pHideButton will clicked --------------\n");
		
        WebSession::js_af_up = "update('" + getCmd() + "');";
    }
    else
    {
        m_szQuery = "";
        if(m_pSubContent)
        {
            int nRow = m_pSubContent->numRows();
            new WText(m_szQueryEmpty, m_pSubContent->elementAt(nRow, 0));
        }
		OutputDebugString("--------------- m_pHideButton is not clicked --------------\n");
		//if (m_pClose)
		//	m_pClose->setEnabled(true);
	}


	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}

}

void SVDeviceTest::closeWnd()
{
    WebSession::js_af_up = "window.close();";
}

void SVDeviceTest::showresult()
{
	OutputDebugString("--------------- showresult()  is run --------------\n");
   
	if(m_pSubContent)
    {
		OutputDebugString("---------------TestDevice--------------\n");
        TestDevice();
    }
	//Jansion.zhou 2007-01-07
    if(m_pClose)
	{
		OutputDebugString("---------------m_pClose->setenable()--------------\n");
        //m_pClose->setEnabled(true);
	}	
	if (m_pFinish)
	{
		m_pFinish->setText(m_szTestSucc);
	}
}

void SVDeviceTest::TestDevice()
{
    bool bRet = false;
    char szReturn [svBufferSize] = {0};
    int nSize = sizeof(szReturn);
    int nQuerySize = static_cast<int>(m_szQuery.length()) + 2;
    char *pszQueryString = new char[nQuerySize];
    if(pszQueryString)
    {
		OutputDebugString("-------------enter TestDevice()-----------------\n");
        //PrintDebugString(m_szQuery.c_str());
        memset(pszQueryString, 0 , nQuerySize);
        changeQueryString(m_szQuery.c_str(), pszQueryString);
        string szDll = "", szFunc = "";
        GetDllAndFunc(m_szQuery.c_str(), szDll, szFunc);
        string szSEID(GetSEID(m_szQuery.c_str()));
        PrintDebugString("DLL name: " + szDll + "\tFunc name: " + szFunc);
        if(szSEID == "1")
        {
            szDll = GetSiteViewRootPath() + "\\fcgi-bin\\" + szDll;
            if(!szDll.empty() && !szFunc.empty())
            {
    #ifdef WIN32
                HINSTANCE hdll = LoadLibrary(szDll.c_str());
                if (hdll)
                {
                    DeviceTest* func = (DeviceTest*)::GetProcAddress(hdll, szFunc.c_str());
                    if (func)
                    {
                        bRet = (*func)(pszQueryString, szReturn, nSize);
                    }
					//Jansion.zhou 2007-01-07
                    //int nRow = m_pSubContent->numRows();
                    //new WText(m_szTestSucc, m_pSubContent->elementAt(nRow, 0));
                    FreeLibrary(hdll);
                }
    #else
    #endif
            }
        }
        else
        {
            PrintDebugString("Test Device by SiteView ECC Slave");
            string szMsg = "dll is " + szDll + " func is " + szFunc + " query stirng is ";
            szMsg += pszQueryString;
            PrintDebugString(szMsg);
            bRet = ReadWriteDynQueue(szSEID, szDll, szFunc, pszQueryString, nQuerySize, szReturn, nSize);
        }
        delete []pszQueryString;
    }
    if(bRet)
    {
        PrintReturn(szReturn);
        int nRow = m_pSubContent->numRows();		
		OutputDebugString("\n----------TestDevice-----------\n");
    }
    else
    {
        int nRow = m_pSubContent->numRows();
	}
}

void SVDeviceTest::changeQueryString(const char * pszQuery, char* pszQueryString)
{
    if(pszQueryString)
    {
        strcpy(pszQueryString , pszQuery);
        char *pPos = pszQueryString;
        while((*pPos) != '\0' )
        {
            if((*pPos) == '&')
                (*pPos) = '\0';
            pPos ++;
        }
    }
}

void SVDeviceTest::PrintReturn(const char * szReturn)
{
    int nRow = m_pSubContent->numRows();
    const char * pPos = szReturn; 
    while(*pPos != '\0')
    {
        int nSize = static_cast<int>(strlen(pPos));
        new WText(pPos, m_pSubContent->elementAt(nRow, 0));
        pPos = pPos + nSize + 1;
		nRow ++;
		OutputDebugString("\n----------PrintReturn-----------\n");
		WebSession::js_af_up = "addLoadEvent(_OnLoad());";
    }
}

void SVDeviceTest::GetDllAndFunc(const char * pszQuery, string &szDll, string &szFunc)
{
    char *pPos = strstr(pszQuery, "devicetype=");
    if(pPos)
    {
        char *chDevID = new char[strlen(pPos)];
        if(chDevID)
        {
            sscanf(pPos, "devicetype= %[^&]", chDevID);
            string szID = chDevID;
            OBJECT objDevice = GetEntityTemplet(szID);
            if(objDevice != INVALID_VALUE)
            {
                MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, "sv_dll", szDll);
                    FindNodeValue(node, "sv_func", szFunc);
                }
                CloseEntityTemplet(objDevice);
            }
            delete []chDevID;
        }
     }
}

string SVDeviceTest::GetSEID(const char *pszQuery)
{
    string szSEID;

    char *pPos = strstr(pszQuery, "seid=");
    if(pPos)
    {
        char *chSEID = new char[strlen(pPos)];
        if(chSEID)
        {
            sscanf(pPos, "seid= %[0-9]", chSEID);
            szSEID = chSEID;
            delete []chSEID;
        }
    }
    else
    {
        szSEID = "1";
		PrintDebugString("not found seid");
    }

    return szSEID;
}
