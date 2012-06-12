//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "selfdefineSendSMS.h"
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


CSVSelfDefineSendSMS::CSVSelfDefineSendSMS(WContainerWidget * parent):
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
			FindNodeValue(ResNode,"IDS_SelfSmsSerialPortTest",strSelfdefineTest);
			FindNodeValue(ResNode,"IDS_SelfSmsSerialPortTest",strSelfDefineTitle);
		}
		CloseResource(objRes);
	}

    SendTestForm();
}

void CSVSelfDefineSendSMS::SendTestForm()
{
	/*new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	WTable *pMainTable= new WTable(this);
	std::string str1 ;
	std::string ret;
	std::string index = GetIniFileString("SMSDllConfig", "DllName", ret, "smsconfig.ini");
	
	str1 = index;

	m_pSerialNum = new WText(str1, (WContainerWidget*)pMainTable->elementAt(0,0));

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->elementAt(0, 0));

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)pMainTable->elementAt(0, 0));
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMainTable->elementAt(0, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)pMainTable->elementAt(0, 0));
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

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

	string szTmp = strSMSTest;
	
	WTable *pTable= new WTable(pMainTable->elementAt(1, 0));
	pTable->setStyleClass("testingsearch");
	
	WText * pStatic = new WText(m_formText.szMailTo, pTable->elementAt(0,0));
	//pStatic->hide();

    pMailTo = new WLineEdit(m_sendParam.m_szFrom, (WContainerWidget*)pTable->elementAt(0,1));
    pMailTo -> setStyleClass("input_border");
    pMailTo -> setTextSize(50);
	
	//pMailTo ->setText("13111111111");

	//pMailTo ->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;",\
		(WContainerWidget*)pMainTable->elementAt(0,0));
	pSendTest = new WPushButton(m_formText.szSend, (WContainerWidget*)pTable->elementAt(0,2));
//    pSendTest -> setStyleClass("searchbutton");
	pSendTest->setToolTip(m_formText.szSend);
    //WObject::connect(pSendTest, SIGNAL(clicked()), this, SLOT(SendTest()));	
   //WObject::connect(pSendTest, SIGNAL(mouseWentDown()), this, SLOT(SendMouseMove()));
	
	WText * pStatic1 = new WText(m_formText.szSendHelp,(WContainerWidget*)pTable->elementAt(1,1));
	//pStatic1 ->hide();

	new WText(m_formText.szMailToDes, pMainTable->elementAt(2,0));

	pStateTextArea = new WText("", (WContainerWidget*)pMainTable->elementAt(3,0));
	pStateTextArea ->setStyleClass("testingresult2"); 

    m_pErrMsg = new WText("",pMainTable->elementAt(4,0));
    m_pErrMsg->decorationStyle().setForegroundColor(Wt::red);
    m_pErrMsg->hide();

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

	WPushButton * pCloseBtn = new WPushButton(strClose, pMainTable->elementAt(5,0));
	pMainTable->elementAt(5,0)->setContentAlignment(AlignCenter);
	WObject::connect(pCloseBtn, SIGNAL(clicked()),  "window.close();", WObject::ConnectionType::JAVASCRIPT);	
	*/
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);
	pMainTable= new WSPopTable(this);
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
	std::string str1 ;
	std::string ret;
	//std::string index = GetIniFileString("SMSDllConfig", "DllName", ret, "smsconfig.ini");
	index = GetIniFileString("SMSDllConfig", "TestDll", "", "smsconfig.ini");
	str1 = index;
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

	m_pSerialNum = new WText(str1, pMainTable->GeRowContentTable(0)->elementAt(1, 0));

	string szTmp = strSMSTest;

	WTable *pTable= new WTable(pMainTable->GeRowContentTable(0)->elementAt(2, 0));
	new WText(m_formText.szMailTo, pTable->elementAt(0,0));
	pTable->elementAt(0,0)->setStyleClass("pop_table_item");

	pMailTo = new WLineEdit(m_sendParam.m_szFrom, (WContainerWidget*)pTable->elementAt(0,1));
	pTable->elementAt(0,1)->setStyleClass("pop_table_item_inp");
	pMailTo->setStyleClass("input_text_width100p");

	//    pSendTest -> setStyleClass("searchbutton");
	//pSendTest->setToolTip(m_formText.szSend);
	//WObject::connect(pSendTest, SIGNAL(clicked()), this, SLOT(SendTest()));	
	//WObject::connect(pSendTest, SIGNAL(mouseWentDown()), this, SLOT(SendMouseMove()));

	new WText(m_formText.szSendHelp,(WContainerWidget*)pTable->elementAt(2,1));
	pTable->elementAt(2,1)->setStyleClass("table_data_input_des");

	new WText(m_formText.szMailToDes, pTable->elementAt(4,0));
	pTable->elementAt(4,0)->setStyleClass("pop_table_item");

	pStateTextArea = new WTextArea("", (WContainerWidget*)pTable->elementAt(4,1));
	pTable->elementAt(4,1)->setStyleClass("pop_table_item_inp");
	pStateTextArea->setStyleClass("input_text_width100p");
	pStateTextArea->disable();

	m_pErrMsg = new WText("",pTable->elementAt(6,0));
	m_pErrMsg->setStyleClass("table_error");
	m_pErrMsg->hide();

	pSendTest = new WSPopButton((WContainerWidget*)pMainTable->GeRowActionTable(0)->elementAt(0,0),m_formText.szSend,"button_bg_m.png","", false);
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

void CSVSelfDefineSendSMS::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/smstest.exe?'\",1250);  ";
	appSelf->quit();
}
void CSVSelfDefineSendSMS::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "smstestRes";
	WebSession::js_af_up += "')";
}

void CSVSelfDefineSendSMS::showErrorMsg(string &szErrMsg)
{
    m_pErrMsg->setText(szErrMsg);
    m_pErrMsg->show();
}

bool CSVSelfDefineSendSMS::checkEmail()
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

void CSVSelfDefineSendSMS::SendTest()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SelfdefineSMSTest";
	LogItem.sHitFunc = "SendTest";
	LogItem.sDesc = strSelfdefineTest;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	string strDllName = "";
	strDllName = index;
	string strDllFuncParam = "";
	strparam = GetIniFileString(index, "DllFunParam", "", "interfacedll.ini");
	strDllFuncParam = strparam;

	OutputDebugString("------------SendTest() call DllFunParam output-----------\n");
	OutputDebugString(strDllName.c_str());
	OutputDebugString("\n");

	int pos = 0;

	pos = strDllName.find("(", 0);
	strDllName = strDllName.substr(0, pos);

	/* // 用来输出调试信息的数组但是在一些情况下会引起内存错误
	string param[3];
	for(int i = 0; i < 3; i++)
	{
		param[i] = "";
	}
	*/

	list<string> paramlist;
	list<string>::iterator paramitem;
	pos = 0;
	int pos1 = strDllFuncParam.find(" ", pos);
	while(pos1 >= 0)
	{		
		string temp = strDllFuncParam.substr(pos, pos1 - pos);
		paramlist.push_back(temp);
		pos = pos1 + 1;
		pos1 = strDllFuncParam.find(" ", pos);		
	}
	string temp1 = strDllFuncParam.substr(pos , strDllFuncParam.size() - pos);
	paramlist.push_back(temp1);

	/* // 该段代码仅仅用来输出调试信息，但是在一些情况下会引起内存错误。
	int iparam = 0;
	for(paramitem = paramlist.begin(); paramitem != paramlist.end(); paramitem++)
	{
		param[iparam] = *paramitem;
		OutputDebugString("--------------self define parameter output-------------------\n");
		OutputDebugString(param[iparam].c_str());
		OutputDebugString("\n");
		
		iparam ++;
	}
	*/

	typedef int (* smssend)(char *, char *, char *);
	smssend smssend1;

	std::string szRootPath =GetSiteViewRootPath();
	char path[256];
	
	strcpy(path, szRootPath.c_str());
	strcat(path, "\\smsplugin\\");
	strcat(path , strDllName.c_str());

	HMODULE hMod = LoadLibrary(path);

	OutputDebugString(path);

	if(hMod != 0)
	{		
		smssend1 = (smssend)GetProcAddress(hMod, "run");
		if(smssend1 != 0)
		{
			string sPhone = pMailTo->text();
			if (strcmp(sPhone.c_str() , "") != 0)
			{
				std::string strMobile;
				strMobile = pMailTo->text() ;
				std::list<string> listMobile;
				std::list<string>::iterator OneList;
				char chSep = ',';
				SplitString(listMobile,strMobile,chSep);
				for(OneList=listMobile.begin();OneList!=listMobile.end();OneList++)
				{
					if(!isNumeric(*OneList) /*|| OneList->size() != 11*/)
					{
						pStateTextArea -> setText(m_formText.szErrMobile);	
						WebSession::js_af_up= "document.all(pSendTest).disabled = false;";
						bEnd = true;	
						goto OPEnd;
					}	
					std::string temp = *OneList;
					OutputDebugString("--------------Mobile telephone output-----------------\n");
					OutputDebugString(temp.c_str());
					OutputDebugString("\n");
					smssend1((char*)strDllFuncParam.c_str(), (char*)temp.c_str(), "This is testing");
				}	
				pStateTextArea -> setText("测试成功！");
			}
		}
		else
		{
			pStateTextArea -> setText("测试失败！");
		}
	}

	if(hMod != 0)
	{
		FreeLibrary(hMod);
	}
	WebSession::js_af_up= "document.all(pSendTest).disabled = false;";
//	pSendTest->enable();
	
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 -dcalBegin);
}

void CSVSelfDefineSendSMS::Back()
{
    emit BackMailset();
}

void CSVSelfDefineSendSMS::SendMouseMove()
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

bool CSVSelfDefineSendSMS::InitSerialPort()
{
  return true;
}

void CSVSelfDefineSendSMS::refresh()
{
//	pSendTest->enable();
	std::string str1 = m_formText.szTitle;
	std::string ret = "error";
	//index = GetIniFileString("SMSDllConfig", "DllName", ret, "smsconfig.ini");	
	index = GetIniFileString("SMSDllConfig", "TestDll", "", "smsconfig.ini");

	//strparam = GetIniFileString("SMSDllConfig", "DllFunParam", ret, "smsconfig.ini");
	strparam = GetIniFileString(index, "DllFunParam", ret, "interfacedll.ini");	
	str1 = index;

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

void CSVSelfDefineSendSMS::AddJsParam(const std::string name, const std::string value)
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

