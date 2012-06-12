#include ".\header.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../base/OperateLog.h"
#include "WApplication"
#include "websession.h"
#include "WText"
#include "WTable"
#include "WImage"
#include "WPushButton"
#include "WTableCell"

CHeader::CHeader(WContainerWidget *parent):WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Welcom", hWelcome);
			FindNodeValue(ResNode,"IDS_Normal_Point", hNormal);
			FindNodeValue(ResNode,"IDS_Warning_Point", hDanger);
			FindNodeValue(ResNode,"IDS_Error_Point", hError);
			FindNodeValue(ResNode,"IDS_Translate", m_szTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip", m_szTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh", m_szRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip", m_szRefreshTip);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
			FindNodeValue(ResNode,"IDS_All1",hAll);
		}
		CloseResource(objRes);
	}
    refreshCount = 0;
    string strSection = GetWebUserID();
    string strUserName;
    strUserName	 = GetIniFileString(strSection, "UserName", "", "user.ini");

    m_pSVUser = new CUser(strSection);

    strUser = strUserName;
    m_pUserIDText = NULL;
    m_pNormalText = NULL;
    m_pWarnningText = NULL;
    m_pErrorText = NULL;

    m_pTranslateBtn = NULL;
	m_pExChangeBtn = NULL;
    ShowMainTable();
}

void CHeader::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	FrameTable = new WTable(this);
	if(FrameTable)
	{
		FrameTable->setCellPadding(0);
		FrameTable->setCellSpaceing(0);
		FrameTable->elementAt(0, 0)->setStyleClass("header_bg");
		FrameTable->elementAt(0, 0)->setContentAlignment(AlignCenter);
	}

	UserTable = new WTable((WContainerWidget *)FrameTable->elementAt(0,0));
	if(UserTable)
	{
		UserTable->setStyleClass("widthauto");
		UserTable->setCellPadding(0);
		UserTable->setCellSpaceing(0);
	}

    m_pUserIDText = new WText("", (WContainerWidget *)UserTable->elementAt(0,0));
	m_pUserIDText->setStyleClass("header_font");

	WImage * headerIma = new WImage("/Images/header.gif",(WContainerWidget *)UserTable->elementAt(0,0));
    m_pAllText = new WText("", (WContainerWidget *)UserTable->elementAt(0,0));
    if(m_pAllText)
    {
		strcpy(m_pAllText->contextmenu_, "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/"
			"menu.exe?cmd=wholetree.exe?\")' style='color:#FFFFFF;text-decoration:underline;font-weight:bold;white-space:nowrap;padding-left:5px;padding-right:15px;cursor:pointer;'");
    }

	WImage * headerIma1 = new WImage("/Images/header1.gif",(WContainerWidget *)UserTable->elementAt(0,0));
    m_pNormalText = new WText("", (WContainerWidget *)UserTable->elementAt(0,0));
    if(m_pNormalText)
    {
		strcpy(m_pNormalText->contextmenu_, "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/"
			"menu.exe?cmd=wholetree.exe?showtype=1\")' style='color:#FFFFFF;text-decoration:underline;font-weight:bold;white-space:nowrap;padding-left:5px;padding-right:15px;cursor:pointer;'");
    }

	WImage * headerIma2 = new WImage("/Images/header2.gif",(WContainerWidget *)UserTable->elementAt(0,0));
    m_pWarnningText = new WText("", (WContainerWidget *)UserTable->elementAt(0,0));
    if(m_pWarnningText)
    {
        strcpy(m_pWarnningText->contextmenu_, "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/"
            "menu.exe?cmd=wholetree.exe?showtype=2\")' style='color:#FFFFFF;text-decoration:underline;font-weight:bold;white-space:nowrap;padding-left:5px;padding-right:15px;cursor:pointer;'");
    }

	WImage * headerIma3 = new WImage("/Images/header3.gif",(WContainerWidget *)UserTable->elementAt(0,0));
    m_pErrorText = new WText("", (WContainerWidget *)UserTable->elementAt(0,0));
    if(m_pErrorText)
    {
        strcpy(m_pErrorText->contextmenu_, "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/"
            "menu.exe?cmd=wholetree.exe?showtype=3\")' style='color:#FFFFFF;text-decoration:underline;font-weight:bold;white-space:nowrap;padding-left:5px;padding-right:15px;cursor:pointer;'");
   }

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
	    new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)UserTable->elementAt(0, 0));
	    m_pTranslateBtn = new WPushButton(m_szTranslate, (WContainerWidget *)UserTable->elementAt(0, 0));
        if(m_pTranslateBtn)
        {
	        connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));
            m_pTranslateBtn->setToolTip(m_szTranslateTip);
        }

	    new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)UserTable->elementAt(0, 0));
	    m_pExChangeBtn = new WPushButton(m_szRefresh, (WContainerWidget *)UserTable->elementAt(0, 0));
        if(m_pExChangeBtn)
        {
            WObject::connect(m_pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	        m_pExChangeBtn->setToolTip(m_szRefreshTip);
        }
	}

	string strTemp = "<SCRIPT type='text/javascript'> top.document.getElementById('header').style.visibility='visible' </SCRIPT>";
	new WText(strTemp, this);

	ShowEdit();
}
void CHeader::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/header.exe?'\",1250);  ";
	appSelf->quit();
}

void CHeader::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "headerRes";
	WebSession::js_af_up += "')";
}

void CHeader::refresh()
{
	string strUserID = GetWebUserID();
//	OutputDebugString(strUserID.c_str());
	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Header";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	ShowEdit();

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

CHeader::~CHeader(void)
{
    if(m_pSVUser)
        delete m_pSVUser;
}
std::string CHeader::GetReloadEvent()
{
	return strReloadFuncName;
}

void CHeader::ShowEdit()
{
	string strSection = GetWebUserID();
    string strUserName;
    strUserName	 = GetIniFileString(strSection, "UserName", "", "user.ini");
    m_pSVUser->setUserID(strSection);

    char szMsg[256] = {0};
    string szNormal(""), szWarning(""), szError(""), zsAll("");
    if(m_pSVUser->isAdmin())
    {
        int nMonitorCount = 0, nDisableCount = 0, nWarnCount = 0, nErrorCount = 0;
        PAIRLIST selist;
	    GetAllSVSEInfo(selist);
        PAIRLIST::iterator iSe;
	    for(iSe = selist.begin(); iSe != selist.end(); iSe++)
        {
            svse_simple_state svsestate = getSVSESimpleState((*iSe).name);
            nMonitorCount += svsestate.nMonitorCount;
            nDisableCount += svsestate.nDisableCount;
            nWarnCount += svsestate.nWarnCount;
            nErrorCount += svsestate.nErrorCount;
        }
        sprintf(szMsg, "%s%d", hAll.c_str(), nMonitorCount);
        zsAll = szMsg;
        sprintf(szMsg, "%s%d", hNormal.c_str(), (nMonitorCount - nDisableCount - nWarnCount - nErrorCount));
        szNormal = szMsg;
        sprintf(szMsg, "%s%d", hDanger.c_str(), nWarnCount);
        szWarning = szMsg;
        sprintf(szMsg, "%s%d", hError.c_str(), nErrorCount);
        szError = szMsg;
    }
    else
    {
        sv_group_state groupstate = getGroupState("1", m_pSVUser);
        sprintf(szMsg, "%s%d", hAll.c_str(), groupstate.nMonitorCount);
        zsAll = szMsg;
        sprintf(szMsg, "%s%d", hNormal.c_str(), 
            (groupstate.nMonitorCount - groupstate.nDisableCount -groupstate.nWarnCount - groupstate.nErrorCount));
        szNormal = szMsg;
        sprintf(szMsg, "%s%d", hDanger.c_str(), groupstate.nWarnCount);
        szWarning = szMsg;
        sprintf(szMsg, "%s%d", hError.c_str(), groupstate.nErrorCount);
        szError = szMsg;
    }
    if(m_pUserIDText)
        m_pUserIDText->setText(hWelcome + strUserName);
    if(m_pAllText)
        m_pAllText->setText(zsAll);
    if(m_pNormalText)
        m_pNormalText->setText(szNormal);
    if(m_pWarnningText)
        m_pWarnningText->setText(szWarning);
    if(m_pErrorText)
	    m_pErrorText->setText(szError);

    if(refreshCount == 0)
    {
        WPushButton *pBtn= new WPushButton("hide",(WContainerWidget *)UserTable->elementAt(0,0));
        if(pBtn)
        {
		    connect(pBtn,SIGNAL(clicked()),this,SLOT(ShowEdit()));
		    strReloadFuncName =pBtn->getEncodeCmd(SIGNAL(clicked()));
		    pBtn->hide();
        }
	}
	refreshCount = 1;

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		if(m_pTranslateBtn) m_pTranslateBtn->show();
		if(m_pExChangeBtn) m_pExChangeBtn->show();
	}
	else
	{
		if(m_pTranslateBtn) m_pTranslateBtn->hide();
		if(m_pExChangeBtn) m_pExChangeBtn->hide();
	}
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Login",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
    CHeader setform(app.root());
	setform.appSelf = &app;
    app.setRefreshTime(3, setform.GetReloadEvent());

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

svse_simple_state CHeader::getSVSESimpleState(string szSVSEIndex, string szIDCUser, string szIDCPwd)
{
    svse_simple_state svsestate;
    PAIRLIST retlist;
    GetMonitorsInfoBySE(szSVSEIndex, retlist, "sv_intpos", szIDCUser, szIDCPwd);
    PAIRLIST::iterator lsItem;
    int nMonitorCount = 0;
    sv_dyn dyn;
    string szMonitorID("");
    svsestate.nMonitorCount = static_cast<int>(retlist.size());
    for(lsItem = retlist.begin(); lsItem != retlist.end(); lsItem ++)
    {
        szMonitorID = (*lsItem).name;       
        if(GetSVDYNNODisplayString(szMonitorID, dyn, szIDCUser, szIDCPwd))
        {
            switch(dyn.m_state)
            {
            case dyn_no_data:
                break;
            case dyn_normal:
                break;
            case dyn_disable:
                svsestate.nDisableCount ++;
                break;
            case dyn_warnning:
                svsestate.nWarnCount ++;
                break;
            case dyn_error:
            case dyn_bad:
                svsestate.nErrorCount ++;
                break;
            }
        }
    }
    return svsestate;
}
