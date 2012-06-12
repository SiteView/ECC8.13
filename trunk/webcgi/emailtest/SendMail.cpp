//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "SendMail.h"



#ifdef WIN32
#include <windows.h>
#endif

#include <WTable>
#include <WTableCell>
#include <WTextArea>
#include <WebSession.h>
#include "../../kennel/svdb/svapi/svapi.h"
#include "../base/OperateLog.h"
#include "../../base/des.h"

//#include "../../kennel/svdb/svapi/jwsmtp/jwsmtp.h"

extern void PrintDebugString(const char *szErrmsg);

//重写了邮件发送代码，对此工程进行相应修改
//苏合 2007-07-24
//+++++++++++++修改开始 苏合 2007-07-24+++++++++++++
/*
typedef bool(SendEmail)(const char *pszServer, const char *pszMailfrom, 
                          const char *pszMailTo, const char *pszSubject,
                          const char * pszMailContent, const char *pszUser, 
                          const char *pszPassword);
*/
typedef bool(SendEmail)(const char *pszServer, const char *pszMailfrom, 
						const char *pszMailTo, const char *pszSubject,
						const char * pszMailContent, const char *pszUser, 
						const char *pszPassword, const char* pszAttachName);
//+++++++++++++修改结束 苏合 2007-07-24+++++++++++++

CSVSendMail::CSVSendMail(WContainerWidget * parent):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Return",m_formText.szBack);
			FindNodeValue(ResNode,"IDS_Email_Content",m_formText.szContent);
			FindNodeValue(ResNode,"IDS_Test_Context",m_formText.szContext);
			FindNodeValue(ResNode,"IDS_Receive_Email_Error",m_formText.szErrMail);
			FindNodeValue(ResNode,"IDS_Email_Receive_Address",m_formText.szMailTo);
			FindNodeValue(ResNode,"IDS_Email_Receive_Address_Help",m_formText.szSendHelp);
			FindNodeValue(ResNode,"IDS_Test_Result",m_formText.szMailToDes);
			FindNodeValue(ResNode,"IDS_Send_Test",m_formText.szSend);
			FindNodeValue(ResNode,"IDS_Send_Email_Ing",m_formText.szSending);
			FindNodeValue(ResNode,"IDS_Send_Email_Success",m_formText.szStateOK);
			FindNodeValue(ResNode,"IDS_Send_Email_Fail",m_formText.szStateFailed);
			FindNodeValue(ResNode,"IDS_Email_Caption",m_formText.szSubject);
			FindNodeValue(ResNode,"IDS_Email_Caption_Help",m_formText.szSubjectDes);
			FindNodeValue(ResNode,"IDS_Test_Caption_Text",m_formText.szSubjectText);
			FindNodeValue(ResNode,"IDS_Email_Server_Address",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Close",m_formText.szClose);
			FindNodeValue(ResNode,"IDS_SMTP_Server",m_formText.szSmtp);
			FindNodeValue(ResNode,"IDS_Test_Email_Caption",m_szEmailSubject);
			FindNodeValue(ResNode,"IDS_Test_Email_Text",m_szEmailContent);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_EmailEmptyError",m_formText.szError);
			FindNodeValue(ResNode,"IDS_SendingEmail",m_formText.szMailSending);
			FindNodeValue(ResNode,"IDS_Test_Email",m_formText.szRowTitle);
		}
		CloseResource(objRes);
	}
    SendTestForm();
}

void CSVSendMail::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/emailtest.exe?'\",1250);  ";
	appSelf->quit();
}
void CSVSendMail::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "emailtestRes";
	WebSession::js_af_up += "')";
}

void CSVSendMail::SendTestForm()
{
	m_pMainTable = new WSPopTable((WContainerWidget *)this, true); 

	//读取email基础设置值
    string szEmailServer = "", szEmailfrom = "", szUserID = "", szUserPwd = "",
			szBackServer = "" ,szTmp = "";

    // SMTP 服务器
	szEmailServer=GetIniFileString("email_config", "server", "",  "email.ini");
    // Email from
	szEmailfrom=GetIniFileString("email_config", "from", "",  "email.ini");
    // 校验用户
	szUserID=GetIniFileString("email_config", "user", "",  "email.ini");
   
	// 校验密码
	szUserPwd=GetIniFileString("email_config", "password", "",  "email.ini");
	Des mydes;
	char dechar[1024]={0};
	if(szUserPwd.size()>0)
	{
		mydes.Decrypt(szUserPwd.c_str(),dechar);
		szUserPwd = dechar;
	}

    // 备份SMTP服务器
	szBackServer=GetIniFileString("email_config", "backupserver", "",  "email.ini");

	m_sendParam.m_szServer =szEmailServer;
    m_sendParam.m_szBackServer = szBackServer;
    m_sendParam.m_szFrom = szEmailfrom;
    m_sendParam.m_szUserID = szUserID;
    m_sendParam.m_szPwd = szUserPwd;

	
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	string rowsTitle = m_formText.szTitle + "&nbsp;&nbsp;";
	rowsTitle += m_sendParam.m_szServer;
	m_pMainTable->AppendRows(m_formText.szRowTitle);		//发送框

	m_pMainTable->GeRowActionTable(0)->setStyleClass("widthauto");


	//服务器
	m_pMainTable->GeRowContentTable(0)->elementAt(0, 0)->setStyleClass("pop_table_item");
	m_pMainTable->GeRowContentTable(0)->elementAt(0, 0)->resize(WLength(160,WLength::Pixel),WLength(0,WLength::Pixel));
	new WText(m_formText.szTitle,m_pMainTable->GeRowContentTable(0)->elementAt(0,0));
	
	m_pMainTable->GeRowContentTable(0)->elementAt(0, 1)->setStyleClass("pop_table_item_inp");

    m_pServer =	new WLineEdit(m_sendParam.m_szServer,m_pMainTable->GeRowContentTable(0)->elementAt(0,1));
	m_pServer->setStyleClass("input_text_width100p");
	m_pServer->disable();

	//地址
	m_pMainTable->GeRowContentTable(0)->elementAt(1, 0)->setStyleClass("pop_table_item");
	m_pMainTable->GeRowContentTable(0)->elementAt(1, 0)->resize(WLength(160,WLength::Pixel),WLength(0,WLength::Pixel));
	new WText(m_formText.szMailTo, m_pMainTable->GeRowContentTable(0)->elementAt(1, 0));

	m_pMainTable->GeRowContentTable(0)->elementAt(1, 1)->setStyleClass("pop_table_item_inp");
	pMailTo  = new WLineEdit(m_sendParam.m_szFrom, m_pMainTable->GeRowContentTable(0)->elementAt(1, 1));
	pMailTo ->setStyleClass("input_text_width100p");

	m_pMainTable->GeRowContentTable(0)->elementAt(2, 1)->setStyleClass("table_data_input_des");
	new WText(m_formText.szSendHelp, m_pMainTable->GeRowContentTable(0)->elementAt(2, 1));

	m_pMainTable->GeRowContentTable(0)->elementAt(3, 1)->setStyleClass("table_data_input_error");
	m_pErrMsg = new WText("",m_pMainTable->GeRowContentTable(0)->elementAt(3, 1));
	m_pErrMsg->decorationStyle().setForegroundColor(Wt::red);
	m_pErrMsg->hide();

	//发送结果
	m_pMainTable->GeRowContentTable(0)->elementAt(4, 0)->setStyleClass("pop_table_item");
	new WText(m_formText.szMailToDes,m_pMainTable->GeRowContentTable(0)->elementAt(4, 0));

	m_pMainTable->GeRowContentTable(0)->elementAt(4, 1)->setStyleClass("pop_table_item_inp");
	pStateTextArea = new WTextArea("", m_pMainTable->GeRowContentTable(0)->elementAt(4, 1));
	pStateTextArea->setStyleClass("input_text_width100p");
	pStateTextArea->disable();
	pStateTextArea->setRows(5);
	

	//发送按钮
	pTestBtn = new WSPopButton(m_pMainTable->GeRowActionTable(0)->elementAt(0, 0), m_formText.szSend, "button_bg_m_black.png", "", true);
	AddJsParam("pMailTo", pMailTo->formName());
	AddJsParam("pSendTest", pTestBtn->formName());	
	AddJsParam("pStateTextArea", pStateTextArea->formName());
	string strshow;
	strshow = "showsmswebsend('";
	strshow += m_formText.szError;
	strshow += "','";
	strshow += m_formText.szMailSending;
	strshow += "')";
	connect(pTestBtn, SIGNAL(clicked()), strshow.c_str() ,this, SLOT(SendTest()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);


	//关闭按钮
	pCloseBtn = new WSPopButton(m_pMainTable->GeRowActionTable(0)->elementAt(0, 1), m_formText.szClose, "button_bg_m.png", "", false);
	WObject::connect(pCloseBtn, SIGNAL(clicked()),  "window.close();", WObject::ConnectionType::JAVASCRIPT);

	//翻译按钮
	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget*)m_pMainTable->GeRowActionTable(0)->elementAt(0, 1));
	pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	//刷新按钮
	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget*)m_pMainTable->GeRowActionTable(0)->elementAt(0, 2));
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();


	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pExChangeBtn->show();
		connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}


//	
//	WTable *pMainTable= new WTable(this);
//	new WText(m_formText.szTitle, (WContainerWidget*)pMainTable->elementAt(0,0));
//	m_pServer = new WText(m_sendParam.m_szServer, (WContainerWidget*)pMainTable->elementAt(0,0));
//
//	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget*)pMainTable->elementAt(0, 0));
//
//
//
//	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->elementAt(0, 0));
//
//	WTable *pTable= new WTable(pMainTable->elementAt(1, 0));
//	pTable->setStyleClass("testingsearch");
//	
//	new WText(m_formText.szMailTo, (WContainerWidget*)pTable->elementAt(0,0));
//
//    pMailTo = new WLineEdit(m_sendParam.m_szFrom, (WContainerWidget*)pTable->elementAt(0,1));
//    
//    pMailTo -> setTextSize(50);
//	
//
//
//	pSendTest = new WPushButton(m_formText.szSend, (WContainerWidget*)pTable->elementAt(0,2));
//
////    pSendTest -> setStyleClass("searchbutton");
//    //WObject::connect(pSendTest, SIGNAL(clicked()), this, SLOT(SendTest()));	
//   //WObject::connect(pSendTest, SIGNAL(mouseWentDown()), this, SLOT(SendMouseMove()));
//	
//
//	
//
//	new WText(m_formText.szSendHelp, (WContainerWidget*)pTable->elementAt(1,1));
//
//  //  new WText(m_formText.szMailToDes, pMainTable->elementAt(3,0));
//  // 	pStateTextArea = new WText("", (WContainerWidget*)pMainTable->elementAt(4,0));
////	pStateTextArea ->setStyleClass("testingresult2");
//	
///*
//	pStateTextArea = new WTextArea("", (WContainerWidget*)pMainTable->elementAt(4,0));
//	pStateTextArea->setRows(20);
//	pStateTextArea->setColumns(60);
//	pStateTextArea ->setStyleClass("testingresult2");
//*/	//pStateTextArea->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
//	
//	/*
//	AddJsParam("pMailTo", pMailTo->formName());
//	AddJsParam("pSendTest", pSendTest->formName());	
//	AddJsParam("pStateTextArea", pStateTextArea->formName());
//	string strshow;
//	strshow = "showsmswebsend('";
//	strshow += m_formText.szError;
//	strshow += "','";
//	strshow += m_formText.szMailSending;
//	strshow += "')";
//	connect(pSendTest, SIGNAL(clicked()), strshow.c_str() ,this, SLOT(SendTest()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
//	*/
// //	WPushButton * pCloseBtn = new WPushButton(m_formText.szClose, pMainTable->elementAt(5,0));
////	pMainTable->elementAt(5,0)->setContentAlignment(AlignCenter);
////	WObject::connect(pCloseBtn, SIGNAL(clicked()),  "window.close();", WObject::ConnectionType::JAVASCRIPT);
//
// //       
// //   new WText(m_formText.szMailTo, (WContainerWidget*)m_pGeneralTable->GetContentTable()->elementAt(1,1));
// //   pMailTo = new WLineEdit(m_sendParam.m_szFrom, (WContainerWidget*)m_pGeneralTable->GetContentTable()->elementAt(1,2));
// //   pMailTo -> setStyleClass("input_border");
// //   pMailTo -> setTextSize(50);
////	  m_pGeneralTable->AddHelpText(m_formText.szMailToDes, 2, 2);
// //   
// //   new WText(m_formText.szSubject, (WContainerWidget*)m_pGeneralTable->GetContentTable()->elementAt(3,1));
// //   pMailSubject = new WLineEdit(m_formText.szSubjectText, (WContainerWidget*)m_pGeneralTable->GetContentTable()->elementAt(3,2));
// //   pMailSubject -> setStyleClass("input_border");
// //   pMailSubject -> setTextSize(50);
////	  m_pGeneralTable->AddHelpText(m_formText.szSubjectDes, 4, 2);
//
// //   
// //   new WText(m_formText.szContent, (WContainerWidget*)m_pGeneralTable->GetContentTable()->elementAt(5,1));
// //   pMailContent = new WLineEdit("This is test!", (WContainerWidget*)m_pGeneralTable->GetContentTable()->elementAt(6,1));
// //   pMailContent -> setStyleClass("input_border");
// //   pMailContent -> setTextSize(50);
}

void CSVSendMail::showErrorMsg(string &szErrMsg)
{
    m_pErrMsg->setText(szErrMsg);
    m_pErrMsg->show();
}

bool CSVSendMail::checkEmail()
{
    string szMailList = pMailTo->text();

    if(szMailList.empty())
        return false;

    char * pTemp1 = NULL, * pTemp2 = NULL;
    
    pTemp1 = strchr(szMailList.c_str(), '@');
    if (!pTemp1)
        return false;
    
    if (*(++pTemp1) == '.')
        return false;
    
    pTemp2 = strchr(pTemp1, '.');
    if (!pTemp2)
        return false;

    return true;
}

void CSVSendMail::SendTest()
{
 	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailTest";
	LogItem.sHitFunc = "SendTest";
	LogItem.sDesc = m_formText.szRowTitle;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}


	m_pErrMsg->setText("");
    m_pErrMsg->hide();

    if (!checkEmail())
    {
        showErrorMsg(m_formText.szErrMail);
		WebSession::js_af_up= "document.all(pSendTest).disabled = false;";
		bEnd = true;	
		goto OPEnd;
    }

    bool bRet = false;

    m_szEmailTo = pMailTo -> text();
    //m_szEmailSubject = pMailSubject -> text();
    //m_szEmailContent = pMailContent -> text();

#if WIN32
   //jwsmtp::mailer m("xingyu.cheng@dragonflow.com","xingyu.cheng@dragonflow.com",  "test mail send", "test mail send",
	  // "mail.dragonflow.com", 25, false);
/*
	jwsmtp::mailer sendmail(false, 25);
	
	sendmail.setserver(m_sendParam.m_szServer.c_str());
	sendmail.setsender(m_sendParam.m_szFrom.c_str());
	sendmail.addrecipient(m_szEmailTo.c_str());
	sendmail.setsubject(m_szEmailSubject.c_str());
	sendmail.setmessage(m_szEmailContent.c_str());
    sendmail.username(m_sendParam.m_szUserID.c_str());
    sendmail.password(m_sendParam.m_szPwd.c_str());   

	sendmail.send();
	bRet = true;
*/
	
    HINSTANCE hDll = LoadLibrary("emailalert.dll");
    if (hDll)
    {
        SendEmail * func = (SendEmail*)::GetProcAddress(hDll, "SendEmail");
        if (func)
        {  
			OutputDebugString("\n***************\n");
			OutputDebugString(m_sendParam.m_szServer.c_str());
			OutputDebugString("\n***************\n");
			OutputDebugString(m_sendParam.m_szFrom.c_str());
			OutputDebugString("\n***************\n");
			OutputDebugString(m_szEmailTo.c_str());
			OutputDebugString("\n***************\n");
			OutputDebugString(m_szEmailSubject.c_str());
			OutputDebugString("\n***************\n");
			OutputDebugString(m_szEmailContent.c_str());
			OutputDebugString("\n***************\n");
			OutputDebugString(m_sendParam.m_szUserID.c_str());
			OutputDebugString("\n***************\n");
			OutputDebugString(m_sendParam.m_szPwd.c_str());

			//重写了邮件发送代码，对此工程进行相应修改
			//苏合 2007-07-24
			//+++++++++++++修改开始 苏合 2007-07-24+++++++++++++
			/*
            bRet = (*func)(m_sendParam.m_szServer.c_str(), m_sendParam.m_szFrom.c_str(),
                m_szEmailTo.c_str(), m_szEmailSubject.c_str(),
                m_szEmailContent.c_str(), m_sendParam.m_szUserID.c_str(),
                m_sendParam.m_szPwd.c_str());
			*/
			bRet = (*func)(m_sendParam.m_szServer.c_str(), m_sendParam.m_szFrom.c_str(),
				m_szEmailTo.c_str(), m_szEmailSubject.c_str(),
				m_szEmailContent.c_str(), m_sendParam.m_szUserID.c_str(),
				m_sendParam.m_szPwd.c_str(), NULL);
			//+++++++++++++修改结束 苏合 2007-07-24+++++++++++++
        }
        FreeLibrary(hDll);
    }
	
#endif
//    pTestBtn -> enable();
    if (bRet)
    {
        //pStateTextArea -> setText(m_formText.szStateOK + sendmail.response());
		pStateTextArea -> setText(m_formText.szStateOK);
		
    }
    else
    {
        //pStateTextArea -> setText(m_formText.szStateFailed + sendmail.response());
		pStateTextArea -> setText(m_formText.szStateFailed);
    }

	WebSession::js_af_up= "document.all(pSendTest).disabled = false;";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSendMail::Back()
{
 
}

void CSVSendMail::SendMouseMove()
{

}

void CSVSendMail::refresh()
{
	//读取email基础设置值
    string szEmailServer = "", szEmailfrom = "", szUserID = "", szUserPwd = "",
			szBackServer = "" ,szTmp = "";

    // SMTP 服务器
	szEmailServer=GetIniFileString("email_config", "server", "",  "email.ini");
    // Email from
	szEmailfrom=GetIniFileString("email_config", "from", "",  "email.ini");
    // 校验用户
	szUserID=GetIniFileString("email_config", "user", "",  "email.ini");
    // 校验密码
	//szUserPwd=GetIniFileString("email_config", "password", "",  "email.ini");
	// 校验密码
	szUserPwd=GetIniFileString("email_config", "password", "",  "email.ini");
	Des mydes;
	char dechar[1024]={0};
	if(szUserPwd.size()>0)
	{
		mydes.Decrypt(szUserPwd.c_str(),dechar);
		szUserPwd = dechar;
	}
    // 备份SMTP服务器
	szBackServer=GetIniFileString("email_config", "backupserver", "",  "email.ini");

	m_sendParam.m_szServer =szEmailServer;
    m_sendParam.m_szBackServer = szBackServer;
    m_sendParam.m_szFrom = szEmailfrom;
    m_sendParam.m_szUserID = szUserID;
    m_sendParam.m_szPwd = szUserPwd;
	
	OutputDebugString(szEmailServer.c_str());
	m_pServer ->setText(szEmailServer);

	pMailTo->setText(m_sendParam.m_szFrom);
	pStateTextArea->setText("");
	m_pErrMsg->hide();
}

void CSVSendMail::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp = "";
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    new WText(strTmp, this);
}

//////////////////////////////////////////////////////////////////////////////////
// end file

