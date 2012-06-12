//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SendSMS.h"
#include <svapi.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <WTable>
#include <WTableCell>
#include <WTextArea>
#include <WebSession.h>
#include <WApplication>

extern void PrintDebugString(const char *szErrmsg);

typedef bool(SendEmail)(const char *pszServer, const char *pszMailfrom, 
                          const char *pszMailTo, const char *pszSubject,
                          const char * pszMailContent, const char *pszUser, 
                          const char *pszPassword);
#include "../kennel/svdb/svapi/svapi.h"
#include "../kennel/svdb/svapi/svdbapi.h"
#include "../../base/splitquery.h"
#include "../base/OperateLog.h"
using namespace SV_Split;


CSVSendSMS::CSVSendSMS(WContainerWidget * parent):
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
			FindNodeValue(ResNode,"IDS_Enter_SMS_Content",m_formText.szContent);
			FindNodeValue(ResNode,"IDS_Test_Context",m_formText.szContext);
			FindNodeValue(ResNode,"IDS_Phone_Number_Error",m_formText.szErrMail);
			FindNodeValue(ResNode,"IDS_Receive_Phone",m_formText.szMailTo);
			FindNodeValue(ResNode,"IDS_Receive_Phone_Help",m_formText.szSendHelp);
			FindNodeValue(ResNode,"IDS_Test_Result",m_formText.szMailToDes);
			FindNodeValue(ResNode,"IDS_Send_Test",m_formText.szSend);
			FindNodeValue(ResNode,"IDS_Send_SMS_Ing",m_formText.szSending);
			FindNodeValue(ResNode,"IDS_Send_Test_SMS_Success",m_formText.szStateOK);
			FindNodeValue(ResNode,"IDS_Send_Test_SMS_Fail",m_formText.szStateFailed);
			FindNodeValue(ResNode,"IDS_SMS_Caption",m_formText.szSubject);
			FindNodeValue(ResNode,"IDS_SMS_Caption_Desciption",m_formText.szSubjectDes);
			FindNodeValue(ResNode,"IDS_Test_Caption_Text",m_formText.szSubjectText);
			FindNodeValue(ResNode,"IDS_Series_Number",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Phone_Number_Error",m_formText.szErrMobile);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_SMS_Test",strSMSTest);
			FindNodeValue(ResNode,"IDS_Close",strClose);
			FindNodeValue(ResNode,"IDS_Test_SMS_Caption",strTestSMSCaption);
			FindNodeValue(ResNode,"IDS_Test_SMS_Content",strTestSMSContent);
			FindNodeValue(ResNode,"IDS_PhoneEmptyError",m_formText.szError);
			FindNodeValue(ResNode,"IDS_SendingSMS",m_formText.szSMSSending);
			FindNodeValue(ResNode,"IDS_Sms_Serial_Port_Test",strPortTest);
		}
		CloseResource(objRes);
	}
   SendTestForm();
}

void CSVSendSMS::SendTestForm()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	new WText("<div id='view_panel' class='panel_view'>", this);
	pMainTable= new WSPopTable(this, true);
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Sms_Serial_Port_Test",title);
		CloseResource(objRes);
	}
	pMainTable->AppendRows(title);
	pMainTable->GeRowActionTable(0)->setStyleClass("widthauto");
	std::string str1 = m_formText.szTitle;
	std::string ret;
	std::string index = GetIniFileString("SMSCommConfig", "Port", ret, "smsconfig.ini");
	str1 += "&nbsp&nbspCOM";
	str1 += index;
	//m_pSerialNum = new WText(str1, (WContainerWidget*)pMainTable->GeRowContentTable(0)->elementAt(0,0));

	//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->GeRowContentTable(0)->elementAt(0, 0));

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)pMainTable->GeRowContentTable(0)->elementAt(0, 0));
    pTranslateBtn->setToolTip(strTranslateTip);
	//pTranslateBtn->hide();

	//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	//翻译
	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)pMainTable->GeRowContentTable(0)->elementAt(0, 0));
	pExChangeBtn->setToolTip(strRefreshTip);
	//pExChangeBtn->hide();
	
	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	bTrans = 1; 
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
	
	m_pSerialNum = new WText(str1, (WContainerWidget*)pMainTable->GeRowContentTable(0)->elementAt(1,0));
	pMainTable->GeRowContentTable(0)->elementAt(1,0)->setStyleClass("pop_table_item");

	string szTmp = strSMSTest;
	
	WTable *pTable= new WTable(pMainTable->GeRowContentTable(0)->elementAt(2 , 0));
	new WText(m_formText.szMailTo, pTable->elementAt(0,0));
	pTable->elementAt(0,0)->setStyleClass("pop_table_item");

    pMailTo = new WLineEdit(m_sendParam.m_szFrom, (WContainerWidget*)pTable->elementAt(0,1));
	pTable->elementAt(0,1)->setStyleClass("pop_table_item_inp");
    //pMailTo -> setTextSize(20);
	pMailTo->setStyleClass("input_text_width100p");
	//pTable->elementAt(1,1)->resize(WLength(20,WLength::Percentage),WLength(0,WLength::Percentage));

	
//    pSendTest -> setStyleClass("searchbutton");
	//pSendTest->setToolTip(m_formText.szSend);
    //WObject::connect(pSendTest, SIGNAL(clicked()), this, SLOT(SendTest()));	
   //WObject::connect(pSendTest, SIGNAL(mouseWentDown()), this, SLOT(SendMouseMove()));
	
	new WText(m_formText.szSendHelp,(WContainerWidget*)pTable->elementAt(1,1));
	pTable->elementAt(1,1)->setStyleClass("table_data_input_des");

	pTable= new WTable(pMainTable->GeRowContentTable(0)->elementAt(4,0));
	pTable->elementAt( 0, 0)->setStyleClass("pop_table_item");

	new WText(m_formText.szMailToDes, pTable->elementAt( 0, 0));

	pStateTextArea = new WTextArea("", (WContainerWidget*)pTable->elementAt( 0, 1));
	pTable->elementAt( 0, 1)->setStyleClass("pop_table_item_inp");
	pStateTextArea->setStyleClass("input_text_width100p");
	pStateTextArea->disable();

    m_pErrMsg = new WText("",pMainTable->GeRowContentTable(0)->elementAt( 6, 0));
    //m_pErrMsg->setStyleClass("table_error");
    m_pErrMsg->hide();

	pSendTest = new WSPopButton((WContainerWidget*)pMainTable->GeRowActionTable(0)->elementAt(0,0),m_formText.szSend,"button_bg_m.png",m_formText.szSend, true);
	AddJsParam("pMailTo", pMailTo->formName());
	AddJsParam("pSendTest", pSendTest->formName());	
	AddJsParam("pStateTextArea", pStateTextArea->formName());	
	string strshow;
	strshow = "showsmswebsend('";
	strshow += m_formText.szError;
	strshow += "','";
	strshow += m_formText.szSMSSending;
	strshow += "')";
	connect(pSendTest, SIGNAL(clicked()), strshow.c_str() ,this, SLOT(SendTest()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	WSPopButton * pCloseBtn = new WSPopButton(pMainTable->GeRowActionTable(0)->elementAt(0,1),strClose, "button_bg_m.png", "", false);
	WObject::connect(pCloseBtn, SIGNAL(clicked()),  "window.close();", WObject::ConnectionType::JAVASCRIPT);
	new WText("</div>", this);
}

void CSVSendSMS::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/smstest.exe?'\",1250);  ";
	appSelf->quit();
}
void CSVSendSMS::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "smstestRes";
	WebSession::js_af_up += "')";
}

void CSVSendSMS::showErrorMsg(string &szErrMsg)
{
    m_pErrMsg->setText(szErrMsg);
    m_pErrMsg->show();
}

bool CSVSendSMS::checkEmail()
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

void CSVSendSMS::SendTest()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "smstest";
	LogItem.sHitFunc = "SendTest";
	LogItem.sDesc = strPortTest;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	//手机号格式
	std::string strMobile;
	strMobile = pMailTo->text() ;
	std::list<string> listMobile;
	std::list<string>::iterator OneList;
	char chSep = ',';
	SplitString(listMobile,strMobile,chSep);
	for(OneList=listMobile.begin();OneList!=listMobile.end();OneList++)
	{
//		OutputDebugString(OneList->c_str());
		if(!isNumeric(*OneList) || OneList->size() != 11)
		{
			pStateTextArea -> setText(m_formText.szErrMobile);	
			WebSession::js_af_up= "document.all(pSendTest).disabled = false;";
			bEnd = true;	
			goto OPEnd;
		}
//		OutputDebugString("   ");
	}	//2006/11/28

    bool bRet = false;

//    pSendTest -> disable();

    m_szEmailTo = pMailTo -> text();
    m_szEmailSubject = strTestSMSCaption;
    m_szEmailContent = strTestSMSContent;


#if WIN32

	//bRet = InitSerialPort();
	bRet = true;
#endif
    if (bRet)
    {
		string sPhone = pMailTo->text();
		if(!sPhone.empty())
		{
			char buf[2048]={0};
			memset(buf,0,2048);
			sprintf(buf, "%s", sPhone.c_str());
			
			//if(!::CreateQueue("SiteView70-Alert",1))
			//	OutputDebugString("Create queue failed");
			//else
			//	OutputDebugString("Create ok");
			OutputDebugString(buf);
			if(!::PushMessage("SiteView70-Alert","SmsTest",buf,strlen(buf)+1))
			{
				OutputDebugString("Push data failed");
				return;
			}

			//m_smsPort.SendMsg(sPhone.c_str(), "this is test");
			pStateTextArea -> setText(m_formText.szStateOK);
			//m_smsPort.CloseCom();
		}
		else
		{
			//showErrorMsg(string(""));
			//m_smsPort.CloseCom();
		}
    }
    else
    {
        pStateTextArea -> setText(m_formText.szStateFailed);
    }

	WebSession::js_af_up= "document.all(pSendTest).disabled = false;";
//    pSendTest -> enable();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 -dcalBegin);
}

void CSVSendSMS::Back()
{
    emit BackMailset();
}

void CSVSendSMS::SendMouseMove()
{
	string sPhone = pMailTo->text();
    if (strcmp(sPhone.c_str() , "") == 0)
    {
		pStateTextArea -> setText(m_formText.szErrMail);
        return;
    }
//    pSendTest -> disable();
    pStateTextArea -> setText(m_formText.szSending);
}

bool CSVSendSMS::InitSerialPort()
{
    //串口名称
	string sret;
	string Value = GetIniFileString("SMSCommConfig", "Port", sret, "smsconfig.ini");

    CString strCOM = "COM";
	strCOM += Value.c_str();

    //初始化串口
	int nErr = m_smsPort.InitPort(strCOM);
    if (nErr == 0)
		return TRUE;//初始化成功
    else
    {
        switch(nErr)
        {
        case CSerialPort::OpenPortFailed://打开端口失败
            break;
        case CSerialPort::NoSetCenter://没有设置短信中心
            break;
        }
		m_smsPort.CloseCom();
        return FALSE;//初始化失败
    }
}

void CSVSendSMS::refresh()
{
	std::string str1 = m_formText.szTitle;
	std::string ret;
	std::string index = GetIniFileString("SMSCommConfig", "Port", ret, "smsconfig.ini");
	str1 += "COM";
	str1 += index;
	m_pSerialNum->setText(str1);

	pMailTo->setText("");
	pStateTextArea->setText("");

	//翻译
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

}

void CSVSendSMS::AddJsParam(const std::string name, const std::string value)
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

