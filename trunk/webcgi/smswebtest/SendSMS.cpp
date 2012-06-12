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
#include <WScrollArea>
#include <WScrollBar>
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
#include "../../base/des.h"
#include "../base/OperateLog.h"
//#include "../../base/GetInstallPath.h"

using namespace SV_Split; 

CSVSendSMS::CSVSendSMS(WContainerWidget * parent):
WContainerWidget(parent)
{
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
			FindNodeValue(ResNode,"IDS_Test_Caption_Text",m_formText.szSubjectText);
			FindNodeValue(ResNode,"IDS_User_Name",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Phone_Number_Error",m_formText.szErrMobile);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Close",strClose);
			FindNodeValue(ResNode,"IDS_PhoneEmptyError",m_formText.szError);
			FindNodeValue(ResNode,"IDS_SendingSMS",m_formText.szSMSSending);
			FindNodeValue(ResNode,"IDS_Sms_Web_Test",strWebTest);
		}
		CloseResource(objRes);
	}
	SendTestForm();
}

void CSVSendSMS::SendTestForm()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);
	pMainTable= new WSPopTable(this);
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Sms_Web_Test",title);
		CloseResource(objRes);
	}
	pMainTable->AppendRows(title);
	pMainTable->GeRowActionTable(0)->setStyleClass("widthauto");
	std::string ret;
	std::string str1;
	std::string user = GetIniFileString("SMSWebConfig", "User", ret, "smsconfig.ini");
	str1 = m_formText.szTitle;
	str1 += ": ";
	str1 += user;
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

	m_pUser = new WText(str1, (WContainerWidget*)pMainTable->GeRowContentTable(0)->elementAt(1,0));
	pMainTable->GeRowContentTable(0)->elementAt(1,0)->setStyleClass("pop_table_item");

	WTable *pTable= new WTable(pMainTable->GeRowContentTable(0)->elementAt(2, 0));
	new WText(m_formText.szMailTo, pTable->elementAt(0,0));
	pTable->elementAt(0,0)->setStyleClass("pop_table_item");

	pMailTo = new WLineEdit(m_sendParam.m_szFrom, (WContainerWidget*)pTable->elementAt(0,1));
	pTable->elementAt(0,1)->setStyleClass("pop_table_item_inp");
	//pMailTo->setTextSize(20);
	pMailTo->setStyleClass("input_text_width100p");
	//pTable->elementAt(1,1)->resize(WLength(20,WLength::Percentage),WLength(0,WLength::Percentage));

	//    pSendTest -> setStyleClass("searchbutton");
	//pSendTest->setToolTip(m_formText.szSend);
	//WObject::connect(pSendTest, SIGNAL(clicked()), this, SLOT(SendTest()));	
	//WObject::connect(pSendTest, SIGNAL(mouseWentDown()), this, SLOT(SendMouseMove()));

	new WText(m_formText.szSendHelp,(WContainerWidget*)pTable->elementAt(1,1));
	pTable->elementAt(1,1)->setStyleClass("table_data_input_des");

	new WText(m_formText.szMailToDes, pTable->elementAt(2,0));
	pTable->elementAt(2,0)->setStyleClass("pop_table_item");

	pStateTextArea = new WTextArea("", (WContainerWidget*)pTable->elementAt(2,1));
	pTable->elementAt(2,1)->setStyleClass("pop_table_item_inp");
	pStateTextArea->setStyleClass("input_text_width100p");
	pStateTextArea->disable();

	m_pErrMsg = new WText("", pTable->elementAt(3,1));
	//pMainTable->GeRowContentTable(0)->elementAt(4,0)->setStyleClass("table_error");
	m_pErrMsg->hide();

	pSendTest = new WSPopButton((WContainerWidget*)pMainTable->GeRowActionTable(0)->elementAt(0,0), m_formText.szSend,"button_bg_m.png",m_formText.szSend, true);
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
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/smswebtest.exe?'\",1250);  ";
	appSelf->quit();
}
void CSVSendSMS::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "smswebtestRes";
	WebSession::js_af_up += "')";
}
void CSVSendSMS::showErrorMsg(string &szErrMsg)
{
    m_pErrMsg->setText(szErrMsg);
    m_pErrMsg->show();
}


void CSVSendSMS::SendTest()
{
	OutputDebugString("\n----------- SendTest -------------\n");
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "smswebtext";
	LogItem.sHitFunc = "SendTest";
	LogItem.sDesc = strWebTest;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	//SendMouseMove();
	//OutputDebugString("SendTest");
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
	} 
	
	//pSendTest->disable();
	//if(!::CreateQueue("SiteView70-Alert",1))
	//	OutputDebugString("Create queue failed");
	//else
	//	OutputDebugString("Create ok");

	//char buf[2048]={0};
	//memset(buf,0,2048);
	//string sPhone = pMailTo ->text();
	//sprintf(buf, "%s", sPhone.c_str());	
	//OutputDebugString(buf);
	//pSendTest -> enable();
	//if(!::PushMessage("SiteView70-Alert","SmsTest",buf,strlen(buf)+1))
	//{
	//	OutputDebugString("Push data failed");
	//	return;
	//}

	//pStateTextArea->setText("Web短信加入发送队列成功!");

    bool bRet = false;

	string sret;
	string User = GetIniFileString("SMSWebConfig", "User", sret, "smsconfig.ini");
	string Pwd = GetIniFileString("SMSWebConfig", "Pwd", sret, "smsconfig.ini");
	
	Des mydes;
	char dechar[1024]={0};
	if(Pwd.size()>0)
	{
		mydes.Decrypt(Pwd.c_str(),dechar);
		Pwd= dechar;
	}

	string strSMS = "This is test!";
	string strPhone = pMailTo ->text();
	//OutputDebugString("SendTest");
	::CoInitialize(NULL);
	{
		HRESULT hr = S_OK;

		IUMSmSendPtr pSender = NULL;
		hr = pSender.CreateInstance("SMSend.UMSmSend");
		if( SUCCEEDED(hr) && (NULL != pSender) )
		{
			
			//OutputDebugString("SUCCEEDED");
			// 构造短消息XML:
			/*_bstr_t bstrSendSMSXML("<?xml version=\"1.0\" encoding=\"GB2312\"?> \
			<message><CompAccount>companyName</CompAccount><password>companyPass</password><InternalUserName>demo</InternalUserName><MobileNumber>13910000000</MobileNumber></message>");
			*/
			
			 char chSMSXML[1024] = {0};
			    sprintf(chSMSXML, "<?xml version=\"1.0\"?><message><EntCode>62016161</EntCode>" \
				"<EntUserID>%s</EntUserID><password>%s</password><Content>%s</Content>" \
				"<DestMobileNumber>%s</DestMobileNumber><URGENT_Flag>1</URGENT_Flag>" \
				"<ScheduledTime></ScheduledTime><Batch_SendID></Batch_SendID><DataType>15" \
				"</DataType><SrcNumber></SrcNumber></message>", User.c_str(), Pwd.c_str(), strSMS.c_str(), 
				strPhone.c_str());
			
			//OutputDebugString("chSMSXML[1024]: \n");
			//OutputDebugString(chSMSXML);

			//
			//  公钥文件的物理位置:
			//_bstr_t bstrPublicKeyPath("D:\\Program Files\\SMSIIGatewayAPI\\PublicKey\\pub.txt");
			string strPath = "";
			strPath = GetSiteViewRootPath() + "\\fcgi-bin\\pub.txt";		

			_bstr_t bstrPublicKeyPath(strPath.c_str());
			OutputDebugString(strPath.c_str());

			//
			//  服务器端接收的ASP页面的URL
			//_bstr_t bstrServerSiteURL("http://gateway.bjums.com/smssite/smsstart.asp");
			_bstr_t bstrServerSiteURL("http://sms.bmcc.com.cn/GatewayAPI/SMSIIGateWay.asp");
			//
			///////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////
			//
			// 设置组件接口所需要的参数
			//
			//  第一个:公钥文件的物理位置
			printf("公钥文件的物理位置: %s\n", (char*)bstrPublicKeyPath);
			pSender->SetPkpath(bstrPublicKeyPath);
			//
			//  第二个:服务器端接收的ASP页面的URL
			printf("服务器端接收的ASP页面的URL: %s\n\n", (char*)bstrServerSiteURL);
			pSender->SetServerSite(bstrServerSiteURL);
			//
			///////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////
			//
			// 实际发送短消息XML给服务器
			//
			// 第一个参数257代表采用RSA加密算法
			// 第二个参数就是短消息XML
			
			//printf("实际发送短消息XML给服务器: %s\n\n", (char*)bstrSendSMSXML);
			//pSender->LoadSendXML("257",
			//	                 bstrSendSMSXML);
			printf("实际发送短消息XML给服务器: %s\n\n", (char*)chSMSXML);
			pSender->LoadSendXML("257", 
								chSMSXML);
			//
			///////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////
			//
			// 发送短消息XML之后，可以通过以下两个方法得到服务器方的反馈
			//  1:GetResponseText(通过这个方法可以取到服务器端返回的responseText)
			//  2:GetHTTPPostStatus(通过这个方法可以取到服务器端返回的状态值,即200、404、500之类的值)
			//
			// 第一个参数257代表采用RSA加密算法
			// 第二个参数就是短消息XML
			_bstr_t bstrServerResponseText = pSender->GetResponseText();
			printf("服务器端返回的responseText: %s\n", (char*)bstrServerResponseText);
			OutputDebugString("服务器端返回的responseText: \n");
			OutputDebugString(bstrServerResponseText);
			//
			long    lServerResponseStatus  = pSender->GetHTTPPostStatus();
			printf("服务器端返回的状态值: %d\n", lServerResponseStatus);
			char buf[256];
			char buf1[256];
			memset(buf, 0, 256);
			memset(buf1, 0, 256);
			sprintf(buf, "服务器端返回的responseText: %s\n", (char*)bstrServerResponseText);
			sprintf(buf1, "服务器端返回的状态值:%d\n", lServerResponseStatus);
			strcat(buf, buf1);

			std::string sRet = buf;
			int bFind = sRet.find("提交成功", 0);
			
			if(bFind >= 0)
			{
				pStateTextArea->setText("Web短信测试成功!");
			}
			else
			{
				pStateTextArea->setText("Web短信测试失败!");
			}

			//
			///////////////////////////////////////////////////////////
		}
	}
	::CoUninitialize();
	WebSession::js_af_up= "document.all(pSendTest).disabled = false;";
//	pSendTest -> enable();	

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

void CSVSendSMS::refresh()
{
	std::string ret;
	std::string str = m_formText.szTitle;
	std::string user = GetIniFileString("SMSWebConfig", "User", ret, "smsconfig.ini");
	str += " ";
	str += user;
	m_pUser->setText(str);

	pMailTo->setText("");
	pStateTextArea -> setText("");
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

