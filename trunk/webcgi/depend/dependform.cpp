#include "dependform.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WApplication"

#include "../svtable/WSPopButton.h"
#include "../svtable/WSPopTable.h"
#include "../base/OperateLog.h"
extern void PrintDebugString(const char * szErrmsg);
extern void PrintDebugString(const string &szMsg);

#define WTGET

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDepend::SVDepend(WContainerWidget *parent)
:WContainerWidget(parent),
m_szSEID(""),
m_pDependTree(NULL),
m_pTranslateBtn(NULL),
m_pExChangeBtn(NULL)
{
    loadString();
    initForm();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::loadString()
{	
	// Resource
	OBJECT objRes = LoadResource("default", "localhost");  
	if( objRes != INVALID_VALUE )
	{	
		MAPNODE ResNode = GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{			
			FindNodeValue(ResNode,"IDS_Depends_Condition",m_szTitle);
			FindNodeValue(ResNode,"IDS_Cancel",m_szClose);
			FindNodeValue(ResNode,"IDS_Close_Window",m_szCloseTip);
			FindNodeValue(ResNode,"IDS_OK",m_szSave);
			FindNodeValue(ResNode,"IDS_Save_Close_Window",m_szSaveTip);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Affirm",strAffirm);
			FindNodeValue(ResNode,"IDS_Cancel1",strCancel);
		}
		CloseResource(objRes);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string SVDepend::getSEID(const char* pQuery)
{
    string szSEID;
	char *pPos = strstr(pQuery, "seid=");
	if(pPos)
	{
		char *chSEID = new char[strlen(pPos)];
		if(chSEID)
		{
			sscanf(pPos, "seid=%[0-9]", chSEID);
			szSEID = chSEID;
			delete []chSEID;
		}
	}
	else
	{
		PrintDebugString("not found seid");
	}
    return szSEID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::initForm()
{
	char szQuery[4096] = {0};
    int nSize = 4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", szQuery,nSize);
#else
	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery == NULL)
	{
		PrintDebugString("QUERY_STRING must not be null");
		new WText("QUERY_STRING can not be null! Please check it!",this);
		return;
	}
	else
	{
		strcpy(szQuery,tmpquery);
	}	
#endif
    string szUserID = GetWebUserID();
    string szSEID = getSEID(szQuery);
    m_szSEID = szSEID;
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);
	m_pMainTable = new WSPopTable(this);
	if(m_pMainTable)
	{
		m_pMainTable->AppendRows(m_szTitle);		
	}
	m_pdiv1 = new WText("<div id='listpan1' class='panel_item'>",m_pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	m_pDependTree = new CCheckBoxTreeView(m_pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	m_pdiv2 = new WText("</div>",m_pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	if(m_pDependTree)
	{		
		m_pDependTree->InitTree("", false, false, false, szUserID, szSEID);
	}    
    createOperate();
    showTranslate();	
	new WText("</div>", this);
	AddJsParam("listheight","200,");
	AddJsParam("listtitle","form,");
	AddJsParam("listpan", "listpan1,");
	AddJsParam("bGeneral","true");
	AddJsParam("bGeneral","true");
	AddJsParam("uistyle", "viewpanandlist");
	AddJsParam("fullstyle", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 添加客户端脚本变量
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SVDepend::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp = "";
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 刷新
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::refresh()
{
	PrintDebugString("In Refresh\n");
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
#endif
	string szUserID = GetWebUserID();
	string szSEID = getSEID(szQuery);
	m_szSEID = szSEID;

	if(m_pDependTree)
		delete m_pDependTree;	
	if(m_pdiv1)
		delete m_pdiv1;
	if(m_pdiv2)
		delete m_pdiv2;

	m_pdiv1 = new WText("<div id='listpan1' class='panel_item'>",m_pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	m_pDependTree = new CCheckBoxTreeView(m_pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	m_pdiv2 = new WText("</div>",m_pMainTable->GeRowContentTable(0)->elementAt(0, 0));

	if(m_pDependTree)
	{		
		m_pDependTree->InitTree("", false, false, false, szUserID, szSEID);
	}
	showTranslate();	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 翻译后刷新
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::ExChange()
{
	string strNRefresh = "setTimeout(\"location.href ='/fcgi-bin/depend.exe?seid=";
	strNRefresh += m_szSEID;
	strNRefresh += "'\",1250);  ";
	WebSession::js_af_up = strNRefresh;
	appSelf->quit();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 翻译
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "dependRes";
	WebSession::js_af_up += "')";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建操作
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::createOperate()
{
	WTable *pTbl = new WTable(m_pMainTable->GeRowActionTable(0)->elementAt(0, 0));
	pTbl->setStyleClass("widthauto");

	WSPopButton *pSaveNew = new WSPopButton(pTbl->elementAt(0,0), m_szSave,"button_bg_m_black.png", m_szSaveTip, false);
	if (pSaveNew)
	{// 保存
		WObject::connect(pSaveNew, SIGNAL(clicked()), this, SLOT(closeWnd()));
	}

    new WText("&nbsp;&nbsp;", pTbl->elementAt(0, 1));

	WSPopButton *pCancelNew = new WSPopButton(pTbl->elementAt(0,2), m_szClose,"button_bg_m.png",m_szCloseTip,false);
	if (pCancelNew)
	{// 取消
		WObject::connect(pCancelNew, SIGNAL(clicked()), this, SLOT(cancel()));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 取消操作的响应函数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::cancel()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "depend";
	LogItem.sHitFunc = "cancel";
	LogItem.sDesc = strCancel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	WebSession::js_af_up ="window.returnValue='IDCANCEL';window.close();";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::closeWnd()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "depend";
	LogItem.sHitFunc = "closeWnd";
	LogItem.sDesc = strAffirm;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string szReturn = "";
    if(m_pDependTree)
        szReturn = m_pDependTree->getSelMonitorID();

    szReturn = "window.returnValue='" + szReturn + "';window.close();";
    WebSession::js_af_up = szReturn; 

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDepend::showTranslate()
{
	if(GetIniFileInt("translate", "translate", 0, "general.ini") == 1)
	{// 翻译
        // 翻译按钮
        if(!m_pTranslateBtn)
        {
            m_pTranslateBtn = new WPushButton(strTranslate, this);
            if(m_pTranslateBtn)
            {// 绑定事件 并 设置Tooltip
	            connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
	            m_pTranslateBtn->setToolTip(strTranslateTip);
            }
        }

        // 刷新按钮
        if(!m_pExChangeBtn)
        {
	        m_pExChangeBtn = new WPushButton(strRefresh, this);
            if(m_pExChangeBtn)
            {// 绑定事件 并 设置Tooltip
	            connect(m_pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	            m_pExChangeBtn->setToolTip(strRefreshTip);
            }
        }

        if(m_pTranslateBtn)
            m_pTranslateBtn->show();

        if(m_pExChangeBtn)
            m_pExChangeBtn->show();
    }
    else
    {
        if(m_pTranslateBtn)
            m_pTranslateBtn->hide();

        if(m_pExChangeBtn)
            m_pExChangeBtn->hide();
    }
}
