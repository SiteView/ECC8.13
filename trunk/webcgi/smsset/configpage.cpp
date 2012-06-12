/*************************************************
*  @file configpage.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include "stdafx.h"
#include "configpage.h"

//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WebSession.h"

#include "../../opens/libwt/WFileUpload"

#include "../../base/des.h"
#include "svapi.h"
#include "../base/OperateLog.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "WSVFlexTable.h"
#include "WSVMainTable.h"
#include "WSVButton.h"

extern void PrintDebugString(const char *szErrmsg);
extern unsigned int RandIndex();
int DirDllName(list<string> &param);

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

string GetDllNameFromStr(string strIn)
{
	string strDllName;
	int nStart = strIn.find("(");
	strDllName = strIn.substr(0, nStart);

	return strDllName;
}


string GetDllInfoFromStr(string strIn)
{
	string strDllInfo;
	
	int nStart = strIn.find("(");
	strDllInfo = strIn.substr(nStart + 1, strIn.length() - nStart - 2);

	return strDllInfo;
}

/*****************************************************
参数：
	parent：容器

功能：
	构造函数
*****************************************************/
CSVSmsSet::CSVSmsSet(WContainerWidget * parent):
WContainerWidget(parent)
{
	IsShow = true;
	chgstr = ""; 
	loadString();
    initForm();
}

/***************************************************
参数：
	无

功能：
	初始化短信主界面
***************************************************/
void CSVSmsSet::initForm()
{
	//设置list长度参数
	strListHeights = "";
	strListPans = "";
	strListTitles = "";
	
	WTable * TitleTable = new WTable(this);
	//WSVFlexTable * flexTable1 = new WSVFlexTable(this);
	TitleTable->setStyleClass("t3");
	
	//连接SVDB失败提示信息
	m_pConnErr = new WText("", (WContainerWidget *)TitleTable->elementAt(0, 0));
	m_pConnErr->decorationStyle().setForegroundColor(Wt::red);
	m_pConnErr ->hide();
	
	//测试连接SVDB
	std::list<string> sectionlist;
	BOOL IsConn = GetIniFileSections(sectionlist, "smsconfig.ini");
	if(!IsConn)
	{
		//连接SVDB失败
		m_pConnErr ->setText(m_formText.szConnErr);
		m_pConnErr ->show();
	}

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)TitleTable->elementAt(0, 1));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)TitleTable->elementAt(0, 1));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)TitleTable->elementAt(0,1));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)TitleTable->elementAt(0, 1));

	//翻译
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

	//主框架
	WSVMainTable *pUserTable = new WSVMainTable(this,m_formText.strMainTitle,true);
	if(pUserTable->pHelpImg)
	{
		connect(pUserTable->pHelpImg, SIGNAL(clicked()),this,SLOT(MainHelp()));
	}
	/*m_pHelpImg = new WImage("../Images/help.gif", (WContainerWidget *)TitleTable->elementAt( 0, 1));
	m_pHelpImg ->setStyleClass("helpimg");
	m_pHelpImg->setToolTip(strHelp);
	TitleTable->elementAt(0, 1) -> setContentAlignment(AlignTop | AlignRight);
	WObject::connect(m_pHelpImg, SIGNAL(clicked()), this, SLOT(MainHelp()));/**///wenbo*/

	//WEB SMS收/放栏
	m_pWebGeneral = new WSVFlexTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(0,0),Group,m_formText.szWebSms);
	m_pWebGeneral->AppendRows("");
	m_pUserID = new WLineEdit("", m_pWebGeneral->AppendRowsContent(0, m_formText.szInputUserLabel, m_formText.szUserDes,m_formText.szUserDes));
	m_pUserID->setStyleClass("input_text_300");
	m_pUserPwd = new WLineEdit("", m_pWebGeneral->AppendRowsContent(0, m_formText.szPwdDes, m_formText.szNote, ""));
	m_pUserPwd->setStyleClass("input_text_300");

	std::string user = GetIniFileString("SMSWebConfig", "User", ret, "smsconfig.ini");
	m_pUserID->setText(user);
	std::string pwd = GetIniFileString("SMSWebConfig", "Pwd", ret, "smsconfig.ini");
	m_pUserPwd->setEchoMode(WLineEdit::Password);
	Des mydes;
	char dechar[1024] = {0};
	if(pwd.size() > 0)
	{
		mydes.Decrypt(pwd.c_str(),dechar);
		pwd = dechar;
	}
	m_pUserPwd->setText(pwd);
	OutputDebugString(pwd.c_str());
	m_pWebGeneral->ShowOrHideHelp();
	m_pWebGeneral->HideAllErrorMsg();

	WTable *pTbl;

	pTbl = new WTable(m_pWebGeneral->GetActionTable()->elementAt(0, 1));

	WSVButton *pSave1 = new WSVButton(pTbl->elementAt(0,0), m_formText.szSave, "button_bg_m_black.png", "", true);
	connect(pSave1, SIGNAL(clicked()), this, SLOT(SaveConfig1()) );

	WSVButton *pTestSMS = new WSVButton(pTbl->elementAt(0, 1), m_formText.szTest, "button_bg_m.png", "", false);
	std::string strOpen = "OpenTest('";
	strOpen += "smswebtest.exe?";//smswebtest.exe:测试WEB SMS弹出窗口
	strOpen += "')";
	WObject::connect(pTestSMS, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);

	/*WTable * m_pWebGeneral = new WTable(this);
	m_pWebGeneral ->setStyleClass("t2");
	
	pHide1 = new WImage("../Images/close.gif", (WContainerWidget *)m_pWebGeneral->elementAt( 0, 0));
    if ( pHide1 )
    {
        pHide1->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pHide1, SIGNAL(clicked()), this, SLOT(showSmsList1()));   
        pHide1->hide();        
    }
    pShow1 = new WImage("../Images/open.gif", (WContainerWidget *)m_pWebGeneral->elementAt( 0, 0));
    if ( pShow1 )
    {
        pShow1->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pShow1, SIGNAL(clicked()), this, SLOT(hideSmsList1())); 
    }

	m_pWebGeneral->elementAt(0, 0)->setStyleClass("t2title");
	new WText(m_formText.szWebSms, (WContainerWidget *)m_pWebGeneral->elementAt( 0, 0));
	table1 = new WTable((WContainerWidget *)m_pWebGeneral->elementAt(1,0));
	table1 -> setStyleClass("t3");
    if ( table1 )
    {
		
		addWebSms(table1);
		
		WPushButton * pSave1 = new WPushButton(m_formText.szSave, (WContainerWidget*)table1->elementAt(2,0));
        connect(pSave1, SIGNAL(clicked()), this, SLOT(SaveConfig1()));    

		//new WImage("../Images/sblank.bmp", (WContainerWidget *)table1->elementAt( 2, 0));
		new WText("&nbsp;&nbsp;", (WContainerWidget *)table1->elementAt( 2, 0));
		WPushButton * pTestSMS = new WPushButton(m_formText.szTest, (WContainerWidget*)table1->elementAt(2,0));
		
		
		std::string strOpen = "OpenTest('";
		strOpen += "smswebtest.exe?";//smswebtest.exe:测试WEB SMS弹出窗口
		strOpen += "')";
		WObject::connect(pTestSMS, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	
	}
*/
	/*串口方式发送短信 */
	m_pGeneral = new WSVFlexTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(1,0),Group,m_formText.szSerialPortDes);
	m_pGeneral->AppendRows("");
	m_pSerialPort = new WComboBox(m_pGeneral->AppendRowsContent(0,m_formText.szPortList,m_formText.szHelpCOM,""));
	m_pSerialPort->setStyleClass("input_text_100");
	m_pSerialPort->addItem("Com1");
	m_pSerialPort->addItem("Com2");
	m_pSerialPort->addItem("Com3");
	m_pSerialPort->addItem("Com4");

	std::string index = GetIniFileString("SMSCommConfig", "Port", ret, "smsconfig.ini");
	m_pSerialPort->setCurrentIndex(atoi(index.c_str()) - 1);
	m_pGeneral->ShowOrHideHelp();

	table1 = new WTable(m_pGeneral->GetActionTable()->elementAt(0,0));
	if ( table1 )
	{

		WSVButton * pSave = new WSVButton(table1->elementAt(0,0), m_formText.szSave,"button_bg_m_black.png", "", true);
		connect(pSave, SIGNAL(clicked()), this, SLOT(SaveConfig()));    

		WSVButton * pTestSMS = new WSVButton(table1->elementAt(0,1), m_formText.szTest, "button_bg_m.png", "", false);
		
		std::string strOpen = "OpenTest('";
		strOpen += "smstest.exe?";//smswebtest.exe:测试WEB SMS弹出窗口
		strOpen += "')";
		WObject::connect(pTestSMS, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	
	}
	/*WTable * m_pGeneral = new WTable(this);
	m_pGeneral ->setStyleClass("t3");
	m_pGeneral ->setStyleClass("t2");

	//串口SMS收/放显示栏
	pHide = new WImage("../Images/close.gif", (WContainerWidget *)m_pGeneral->elementAt( 0, 0));
    if ( pHide )
    {
        pHide->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pHide, SIGNAL(clicked()), this, SLOT(showSmsList()));   
        pHide->hide();       
    }
    pShow = new WImage("../Images/open.gif", (WContainerWidget *)m_pGeneral->elementAt( 0, 0));
    if ( pShow )
    {
        pShow->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pShow, SIGNAL(clicked()), this, SLOT(hideSmsList())); 
        
    }

	m_pGeneral->elementAt(0,0)->setStyleClass("t2title");
	
	new WText(m_formText.szSerialPortDes, (WContainerWidget *)m_pGeneral->elementAt( 0, 0));
	table = new WTable((WContainerWidget *)m_pGeneral->elementAt(1,0));
	table -> setStyleClass("t3");
    if ( table )
    {		     
        addComSms(table);

        WPushButton * pSave = new WPushButton(m_formText.szSave, (WContainerWidget*)table->elementAt(4,0));
	    connect(pSave, SIGNAL(clicked()), this, SLOT(SaveConfig()));       
		
		new WText("&nbsp;&nbsp;", (WContainerWidget *)table->elementAt( 4, 0));
		WPushButton * pTestSMS = new WPushButton(m_formText.szTest, (WContainerWidget*)table->elementAt(4,0));
		std::string strOpen = "OpenTest('";
		strOpen += "smstest.exe?";
		strOpen += "')";
		WObject::connect(pTestSMS, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	

		
    }*/

	//动态库函数调用入口
	m_pDllTable = new WSVFlexTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(2,0),Group,m_formText.szFuncTitle);
	m_pDllTable->AppendRows("");
	m_pCDllName = new WComboBox(m_pDllTable->AppendRowsContent(0, m_formText.szDllName, m_formText.szSelfDefine1,""));
	m_pCDllName->setStyleClass("input_text_300");
	list<string> dllname;
	list<string>::iterator dllnameitem;
	DirDllName(dllname);

	std::string szRootPath =GetSiteViewRootPath();
	for(dllnameitem = dllname.begin(); dllnameitem != dllname.end(); dllnameitem++)
	{
		string temp = *dllnameitem;
		string retstr;

		char path[256];

		strcpy(path, szRootPath.c_str());
		strcat(path, "\\smsplugin\\");
		strcat(path , temp.c_str());

		HMODULE hMod = LoadLibrary(path);
		if(hMod != 0)
		{			
			typedef int (* getinfo)(string&retstr);
			getinfo getinfo1;
			getinfo1 = (getinfo)GetProcAddress(hMod, "getinfo");
			if(getinfo1 != 0)
			{			
				getinfo1(retstr);
			}
			else
			{
				if(hMod != 0)
				{
					FreeLibrary(hMod);
				}
				continue;
			}
		}
		else
		{
			continue;
		}

		if(!retstr.empty())
		{
			temp += "(";
			temp += retstr;
			temp += ")";
		}

		m_pCDllName -> addItem(temp.c_str());

		if(hMod != 0)
		{
			FreeLibrary(hMod);
		}
	}
	connect(m_pCDllName, SIGNAL(changed()), this, SLOT(SelDllChanged()));
	//std::string szDllName = GetIniFileString("SMSDllConfig", "DllName", ret, "smsconfig.ini");
	//m_pCDllName ->setCurrentIndexByStr(szDllName);
	m_pDllFunParam = new WLineEdit("",m_pDllTable->AppendRowsContent(0,m_formText.szDllFunParam, m_formText.szSelfDefine2,""));
	m_pDllFunParam -> setTextSize(60);
	m_pDllFunParam->setStyleClass("input_text_300");
	//std::string szDllFunParam = GetIniFileString("SMSDllConfig", "DllFunParam", ret, "smsconfig.ini");
	//m_pDllFunParam -> setText(szDllFunParam);
	m_pCDllName->setCurrentIndex(0);
	string strDllName = GetDllNameFromStr(m_pCDllName->currentText());
	
	//读Ini并显示DllParam
	std::string szDllFunParam = GetIniFileString(strDllName, "DllFunParam", "", "interfacedll.ini");
	m_pDllFunParam->setText(szDllFunParam);
	m_pDllTable->ShowOrHideHelp();
		

	table3 = new WTable((WContainerWidget *)m_pDllTable->GetActionTable()->elementAt(0,0));
	if ( table3 )
	{		     

		WSVButton *pSave3 = new WSVButton(table3->elementAt(0,0), m_formText.szSave,  "button_bg_m_black.png", "", true);
		connect(pSave3, SIGNAL(clicked()), this, SLOT(SaveDllConfig()));       

		WSVButton *pTestDll = new WSVButton(table3->elementAt(0,1), m_formText.szTest,  "button_bg_m.png", "", false);
		std::string strOpen = "OpenTest('";
		strOpen += "selfdefinesmstest.exe?";
		strOpen += "')";
		//WObject::connect(pTestDll, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	
		WObject::connect(pTestDll, SIGNAL(clicked()), this, SLOT(TestDll())); 
;
		WSVButton *pUpLoad = new WSVButton(table3->elementAt(0,2), m_formText.szUpLoad,  "button_bg_m.png", "", false);
		connect(pUpLoad, SIGNAL(clicked()), this, SLOT(UpLoadFile()));
		pUpLoad ->hide();
	}

	/*WTable * m_pDllTable = new WTable(this);
	m_pDllTable ->setStyleClass("t3");
	m_pDllTable ->setStyleClass("t2");

	pHide3 = new WImage("../Images/close.gif", (WContainerWidget *)m_pDllTable->elementAt( 0, 0));
    if ( pHide3 )
    {
        pHide3->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pHide3, SIGNAL(clicked()), this, SLOT(showDllTable()));   
        pHide3->hide();       
    }
    pShow3 = new WImage("../Images/open.gif", (WContainerWidget *)m_pDllTable->elementAt( 0, 0));
    if ( pShow3 )
    {
        pShow3->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pShow3, SIGNAL(clicked()), this, SLOT(hideDllTable())); 
        
    }

	m_pDllTable->elementAt(0,0)->setStyleClass("t2title");
	
	new WText(m_formText.szFuncTitle, (WContainerWidget *)m_pDllTable->elementAt( 0, 0));
	table3 = new WTable((WContainerWidget *)m_pDllTable->elementAt(1,0));
	table3 -> setStyleClass("t3");
    if ( table3 )
    {		     
        addDllTable(table3);

        WPushButton * pSave3 = new WPushButton(m_formText.szSave, (WContainerWidget*)table3->elementAt(4,0));
	    connect(pSave3, SIGNAL(clicked()), this, SLOT(SaveDllConfig()));       
		
		new WText("&nbsp;&nbsp;", (WContainerWidget *)table3->elementAt( 4, 0));
		WPushButton * pTestDll = new WPushButton(m_formText.szTest, (WContainerWidget*)table3->elementAt(4,0));
		std::string strOpen = "OpenTest('";
		strOpen += "selfdefinesmstest.exe?";
		strOpen += "')";
		WObject::connect(pTestDll, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	

		new WText("&nbsp;&nbsp;", (WContainerWidget *)table3->elementAt( 4, 0));
		WPushButton * pUpLoad = new WPushButton(m_formText.szUpLoad, (WContainerWidget*)table3->elementAt(4, 0));
		connect(pUpLoad, SIGNAL(clicked()), this, SLOT(UpLoadFile()));
		pUpLoad ->hide();
    }*/

	//sms接收电话列表
	
	m_pListGeneral =  new WSVFlexTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(3,0),List,m_formText.szTBTitle);
	m_pListGeneral->SetDivId("listpan1");
	if(m_pListGeneral->GetContentTable()!=NULL)
	{
		strListHeights += "200";
		strListHeights += ",";
		strListPans += m_pListGeneral->GetDivId();
		strListPans += ",";
		strListTitles +=  m_pListGeneral->dataTitleTable->formName();
		strListTitles += ",";

		m_pListGeneral->AppendColumn("",WLength(50,WLength::Pixel));
		m_pListGeneral->SetDataRowStyle("table_data_grid_item_text");
		m_pListGeneral->AppendColumn(m_formText.szColName,WLength(40,WLength::Percentage));
		m_pListGeneral->SetDataRowStyle("table_data_grid_item_text");
		m_pListGeneral->AppendColumn(m_formText.szColState,WLength(20,WLength::Percentage));
		m_pListGeneral->SetDataRowStyle("table_data_grid_item_text");
		m_pListGeneral->AppendColumn(m_formText.szColPhone,WLength(40,WLength::Percentage));
		m_pListGeneral->SetDataRowStyle("table_data_grid_item_text");
		m_pListGeneral->AppendColumn(m_formText.szColEdit,WLength(80,WLength::Pixel));
		m_pListGeneral->SetDataRowStyle("table_data_grid_item_img");

		std::list<string> sectionlist;
		std::list<string>::iterator m_sItem;
		GetIniFileSections(sectionlist, "smsphoneset.ini");

		for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
		{
			std::string section = *m_sItem;
			
			int numRow = m_pListGeneral->GeDataTable()->numRows();
			m_pListGeneral->InitRow(numRow);

			SMS_LIST list;

			// 是否选择
			WCheckBox * pCheck = new WCheckBox("", m_pListGeneral->GeDataTable()->elementAt(numRow,0));
			m_pListGeneral->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);

			// 名称
			std::string value = GetIniFileString(section, "Name", ret, "smsphoneset.ini");
			WText * pName = new WText(value, m_pListGeneral->GeDataTable()->elementAt(numRow,2));
			m_pListGeneral->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);

			// 状态
			value = GetIniFileString(section, "Status", ret, "smsphoneset.ini");
			WText * pState = NULL;
			if(strcmp(value.c_str(), "Yes") == 0)
			{
				pState = new WText(m_formText.szEnable, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow  , 4));
				m_pListGeneral->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
			}
			else
			{
				pState = new WText(m_formText.szDisable, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow  , 4));
				m_pListGeneral->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
			}

			// 手机号码
			std::string phonevalue = GetIniFileString(section,"Phone" , ret, "smsphoneset.ini");
			WText * pValue = new WText(phonevalue, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 6));
			m_pListGeneral->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);

			WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 8));
			m_pListGeneral->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(AlignCenter);
			pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
			connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));

			int nIndex = RandIndex();
			char chIndex[32] = {0};
			sprintf(chIndex, "%d", nIndex);
			//m_signalMapper.setMapping(pEdit, phonevalue); 
			m_signalMapper.setMapping(pEdit, section);

			list.pSelect = pCheck;
			list.pName = pName;
			list.pPhoneNum = pValue;
			list.pStatus = pState;
			list.id = section;
			m_pListSMS.push_back(list);

		}
	connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));
	
	if(m_pListGeneral->GetActionTable()!=NULL)
	{
		//全选,反选,全不选
		m_pListGeneral->AddStandardSelLink(m_formText.szColSelAll, m_formText.szTipSelNone, m_formText.szTipSelInv);
		
        if (m_pListGeneral->pSelAll)
        {
			connect(m_pListGeneral->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

        if (m_pListGeneral->pSelNone)
        {
			connect(m_pListGeneral->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

        if (m_pListGeneral->pSelReverse)
        {
			connect(m_pListGeneral->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		m_pListGeneral->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pListGeneral->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		m_pGroupOperate = new WTable(m_pListGeneral->GetActionTable()->elementAt(0,1));

		m_pGroupOperate->setStyleClass("widthauto");
		WSVButton *pDel= new WSVButton(m_pGroupOperate->elementAt(0,0),m_formText.szTipDel,"button_bg_del.png");
		if (pDel)
		{
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
		}

		m_pListGeneral->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		WSVButton * pAdd = new WSVButton(m_pListGeneral->GetActionTable()->elementAt(0,2),m_formText.szAddPhoneBut,"button_bg_add_black.png",m_formText.szAddPhoneBut, true);
		if (pAdd)
		{
			WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(AddPhone()));
			//隐藏按钮
			pHideBtn = new WPushButton("hide button",this);
			if(pHideBtn)
			{
				connect(pHideBtn,SIGNAL(clicked()),this,SLOT(DelPhone()));
				pHideBtn->hide();
			}
		}

		m_pListGeneral->SetNullTipInfo(m_formText.strNullList);

	}
	}

	AddJsParam("listheight", strListHeights, this);
	AddJsParam("listtitle", strListTitles, this);
	AddJsParam("listpan", strListPans, this);
	AddJsParam("uistyle", "viewpanandlist", this);
	AddJsParam("fullstyle", "true", this);


	/*WTable * m_pListGeneral = new WTable(this);
	m_pListGeneral ->setStyleClass("t2");
	
	//sms接收电话列表收/放显示栏
	pHide2 = new WImage("../Images/close.gif", (WContainerWidget *)m_pListGeneral->elementAt( 0, 0));
    if ( pHide2 )
    {
        pHide2->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pHide2, SIGNAL(clicked()), this, SLOT(showSmsList2()));   
        pHide2->hide();        
    }
    pShow2 = new WImage("../Images/open.gif", (WContainerWidget *)m_pListGeneral->elementAt( 0, 0));
    if ( pShow2 )
    {
        pShow2->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(pShow2, SIGNAL(clicked()), this, SLOT(hideSmsList2())); 
    }
	m_pListGeneral->elementAt(0, 0)->setStyleClass("t2title");
	new WText(m_formText.szTBTitle, (WContainerWidget *)m_pListGeneral->elementAt( 0, 0));

	table2 = new WTable((WContainerWidget *)m_pListGeneral->elementAt(2,0));
	table2 -> setStyleClass("t3");
    if ( table2 )
    {
		new WText(m_formText.szDescription, (WContainerWidget *)table2->elementAt( 0, 0));
        addPhoneList(table2);
		connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditRow(const std::string)));
		AddGroupOperate(table2);
	}*/
}

void CSVSmsSet::TestDll()
{
	OutputDebugString("\n----------TestDll------------\n");
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "TestDll";
	LogItem.sDesc = strTestDll;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	WriteIniFileString("SMSDllConfig", "TestDll", GetDllNameFromStr(m_pCDllName->currentText()), "smsconfig.ini");

	std::string strOpen = "OpenTest('";
	strOpen += "selfdefinesmstest.exe?";
	
	//strOpen += "dllname=";
	//strOpen += GetDllNameFromStr(m_pCDllName->currentText());
	
	strOpen += "')";
	
	//OutputDebugString("------------selfdefinesmstest.exe -----------\n");
	//OutputDebugString(strOpen.c_str());
	//OutputDebugString("\n");

	WebSession::js_af_up = strOpen;

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSmsSet::SelDllChanged()
{
	string strDllName = "";

	//
	strDllName = GetDllNameFromStr(m_pCDllName->currentText());
	
	//读Ini并显示DllParam
	std::string szDllFunParam = GetIniFileString(strDllName, "DllFunParam", "", "interfacedll.ini");
	m_pDllFunParam->setText(szDllFunParam);
}


void CSVSmsSet::ExChange()
{
	PrintDebugString("------ExChangeEvent------\n");
	emit ExChangeEvent();
}
void CSVSmsSet::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "smssetRes";
	WebSession::js_af_up += "')";
}

int  DirDllName(list<string> &param)
{
	char  path[256];
	memset(path, 0, 256);
	std::string szRootPath =GetSiteViewRootPath();
	strcpy(path, szRootPath.c_str());
	strcat(path, "\\smsplugin\\*.*");

	WIN32_FIND_DATA fd;
	
    HANDLE fr=::FindFirstFile(path, &fd);
	
	int nSize = 0;    
	while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{			
		}
        else
		{
			param.push_back(fd.cFileName);	
		}
    }
	return 1;
}

void CSVSmsSet::addDllTable(WTable *table)
{
	WTable * psubTb1 = NULL, * psubTb2 = NULL;
    psubTb1 = new WTable((WContainerWidget*)table->elementAt(1,0));
	psubTb1->setStyleClass("t3");
	if(psubTb1)
	{
		string ret;
		new WText(m_formText.szDllName, (WContainerWidget*)psubTb1->elementAt(0, 0));
		
		m_pCDllName = new WComboBox((WContainerWidget*)psubTb1->elementAt(0, 1));
		m_pHelpSelfDefine1 = new WText(m_formText.szSelfDefine1, (WContainerWidget*)psubTb1->elementAt(1, 1));
		
		OutputDebugString("---------------------help information output-----------\n");
		OutputDebugString(m_formText.szSelfDefine1.c_str());
		OutputDebugString("\n");

		m_pHelpSelfDefine1->setStyleClass("helps");
		m_pHelpSelfDefine1->hide();
		
		list<string> dllname;
		list<string>::iterator dllnameitem;
		DirDllName(dllname);

		std::string szRootPath =GetSiteViewRootPath();
		for(dllnameitem = dllname.begin(); dllnameitem != dllname.end(); dllnameitem++)
		{
			string temp = *dllnameitem;
			string retstr;
	
			char path[256];
			
			strcpy(path, szRootPath.c_str());
			strcat(path, "\\smsplugin\\");
			strcat(path , temp.c_str());

			HMODULE hMod = LoadLibrary(path);
			if(hMod != 0)
			{			
				typedef int (* getinfo)(string&retstr);
				getinfo getinfo1;
				getinfo1 = (getinfo)GetProcAddress(hMod, "getinfo");
				if(getinfo1 != 0)
				{			
					getinfo1(retstr);
				}
				else
				{
					if(hMod != 0)
					{
						FreeLibrary(hMod);
					}
					continue;
				}
			}
			else
			{
				continue;
			}

			if(!retstr.empty())
			{
				temp += "(";
				temp += retstr;
				temp += ")";
			}

			m_pCDllName -> addItem(temp.c_str());

			if(hMod != 0)
			{
				FreeLibrary(hMod);
			}
		}

		connect(m_pCDllName, SIGNAL(changed()), this, SLOT(SelDllChanged()));
		//std::string szDllName = GetIniFileString("SMSDllConfig", "DllName", ret, "smsconfig.ini");
		//m_pCDllName ->setCurrentIndexByStr(szDllName);
	//	psubTb1->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);

		
		new WText(m_formText.szDllFunParam, (WContainerWidget*)psubTb1->elementAt(2, 0));
		m_pDllFunParam = new WLineEdit("", (WContainerWidget*)psubTb1->elementAt(2, 1));
		m_pDllFunParam->setStyleClass("input_text");
		m_pHelpSelfDefine2 = new WText(m_formText.szSelfDefine2, (WContainerWidget*)psubTb1->elementAt(3, 1));
		
		//OutputDebugString("---------------------help information output2-----------\n");
		//OutputDebugString(m_formText.szSelfDefine1.c_str());
		//OutputDebugString("\n");

		m_pHelpSelfDefine2 ->setStyleClass("helps");
		m_pHelpSelfDefine2->hide();
		m_pDllFunParam -> setTextSize(60);
		//std::string szDllFunParam = GetIniFileString("SMSDllConfig", "DllFunParam", ret, "smsconfig.ini");
		//m_pDllFunParam -> setText(szDllFunParam);
	//	psubTb1->elementAt(2, 1)->setContentAlignment(AlignTop | AlignLeft);
		//
		m_pCDllName->setCurrentIndex(0);
		string strDllName = GetDllNameFromStr(m_pCDllName->currentText());
		
		//读Ini并显示DllParam
		std::string szDllFunParam = GetIniFileString(strDllName, "DllFunParam", "", "interfacedll.ini");
		m_pDllFunParam->setText(szDllFunParam);

	}
}

void CSVSmsSet::addWebSms(WTable * table)
{
    WTable * psubTb1 = NULL, * psubTb2 = NULL;
    psubTb1 = new WTable((WContainerWidget*)table->elementAt(1,0));
	psubTb1->setStyleClass("t3");
    if (psubTb1)
    { 
        m_pErrMsg = new WText(m_formText.szUserDes, (WContainerWidget*)psubTb1->elementAt(1,0));
        m_pErrMsg->decorationStyle().setForegroundColor(Wt::red);
        m_pErrMsg->hide();  
        
        psubTb2 = new WTable((WContainerWidget*)psubTb1->elementAt(2,0));
		psubTb2->setStyleClass("t3");
        if (psubTb2)
        {
			addWidget(new WText(m_formText.szInputUserLabel, (WContainerWidget*)psubTb2->elementAt(0,0)));
			psubTb2->elementAt(0,0)->resize(WLength(8, WLength::Percentage),WLength(100, WLength::Percentage));
            m_pUserID = new WLineEdit("", (WContainerWidget*)psubTb2->elementAt(0,1));
            m_pUserID->setTextSize(60);
			m_pUserID->setStyleClass("input_text");
			m_pHelpUserID = new WText(m_formText.szUserDes1, (WContainerWidget*)psubTb2->elementAt(1,1));
			m_pHelpUserID->setStyleClass("helps");
			m_pHelpUserID->hide();

			std::string ret;
			std::string user = GetIniFileString("SMSWebConfig", "User", ret, "smsconfig.ini");
			m_pUserID->setText(user);
            addWidget(new WText(m_formText.szPwdDes, (WContainerWidget*)psubTb2->elementAt(2,0)));
            m_pUserPwd = new WLineEdit("", (WContainerWidget*)psubTb2->elementAt(2,1));
			m_pUserPwd->setStyleClass("input_text");
            m_pUserPwd->setTextSize(60);



			m_pUserPwd->setEchoMode(WLineEdit::Password);
			std::string pwd = GetIniFileString("SMSWebConfig", "Pwd", ret, "smsconfig.ini");

			Des mydes;
			char dechar[1024]={0};
			if(pwd.size()>0)
			{
				mydes.Decrypt(pwd.c_str(),dechar);
				pwd= dechar;
			}

			m_pUserPwd->setText(pwd);
        }

        pNote = new WText(m_formText.szNote, (WContainerWidget*)psubTb2->elementAt(3,1));
		pNote ->setStyleClass("helps");
        pNote->decorationStyle().setForegroundColor(Wt::red);
		pNote ->hide();
    }
}

//add common sms windows
void CSVSmsSet::addComSms(WTable * table)
{
    WTable * psubTb1 = NULL, * psubTb2 = NULL;
    psubTb1 = new WTable((WContainerWidget*)table->elementAt(2,0));
    if (psubTb1)
    {
        table->elementAt(1,1)->setContentAlignment(AlignTop);
        psubTb2 = new WTable((WContainerWidget*)psubTb1->elementAt(2,0));        

        if (psubTb2)
        {
            
            addWidget(new WText(m_formText.szPortList, (WContainerWidget*)psubTb2->elementAt(0,0)));
            addWidget(new WText("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget*)psubTb2->elementAt(0,0)));
   
            m_pSerialPort = new WComboBox((WContainerWidget*)psubTb2->elementAt(0,1));
            

            m_pSerialPort->addItem("Com1");
            m_pSerialPort->addItem("Com2");
            m_pSerialPort->addItem("Com3");
            m_pSerialPort->addItem("Com4");

			std::string ret;
			std::string index = GetIniFileString("SMSCommConfig", "Port", ret, "smsconfig.ini");
			m_pSerialPort->setCurrentIndex(atoi(index.c_str()) - 1);

            m_pHelpCOM = new WText(m_formText.szHelpCOM, (WContainerWidget*)psubTb2->elementAt(1,1));
			m_pHelpCOM->setStyleClass("helps");
			m_pHelpCOM->hide();

		}      
    }
}

//add phone list function
void CSVSmsSet::addPhoneList(WTable * table)
{
    m_ptbPhone = new WTable((WContainerWidget*)table->elementAt(7,0));
	m_nullTable = new WTable((WContainerWidget*)table->elementAt(8, 0));
	m_ptbPhone->setStyleClass("t3");
	m_nullTable -> setStyleClass("t8");
    if (m_ptbPhone)
    {
        m_ptbPhone -> setCellPadding(0);   
		m_ptbPhone->setCellSpaceing(0);
//		new WText(m_formText.szColSelAll, (WContainerWidget*)m_ptbPhone->elementAt(0,0));
		new WText("", (WContainerWidget*)m_ptbPhone->elementAt(0,0));
        new WText(m_formText.szColName, (WContainerWidget*)m_ptbPhone->elementAt(0, 1));
        new WText(m_formText.szColState, (WContainerWidget*)m_ptbPhone->elementAt(0, 2));
        new WText(m_formText.szColPhone, (WContainerWidget*)m_ptbPhone->elementAt(0, 3));
        new WText(m_formText.szColEdit, (WContainerWidget*)m_ptbPhone->elementAt(0, 4));
		
		m_ptbPhone->elementAt(0, 0)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 1)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 2)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 3)->setStyleClass("t3title");
		m_ptbPhone->elementAt(0, 4)->setStyleClass("t3title");          
    }

	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	GetIniFileSections(sectionlist, "smsphoneset.ini");

	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		std::string section = *m_sItem;

		std::string ret;
		int numRow = m_ptbPhone->numRows();

		SMS_LIST list;
		
		// 是否选择
		WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_ptbPhone->elementAt(numRow, 0));

		// 名称
		std::string value = GetIniFileString(section, "Name", ret, "smsphoneset.ini");
		WText * pName = new WText(value, (WContainerWidget*)m_ptbPhone->elementAt(numRow , 1));
		
		// 状态
		value = GetIniFileString(section, "Status", ret, "smsphoneset.ini");
		WText * pState = NULL;
		if(strcmp(value.c_str(), "Yes") == 0)
		{
			pState = new WText(m_formText.szEnable, (WContainerWidget*)m_ptbPhone->elementAt(numRow  , 2));
		}
		else
		{
			pState = new WText(m_formText.szDisable, (WContainerWidget*)m_ptbPhone->elementAt(numRow  , 2));
		}

		// 手机号码
		std::string phonevalue = GetIniFileString(section,"Phone" , ret, "smsphoneset.ini");
		WText * pValue = new WText(phonevalue, (WContainerWidget*)m_ptbPhone->elementAt(numRow , 3));

		WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)m_ptbPhone->elementAt(numRow , 4));
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));

		int nIndex = RandIndex();
		char chIndex[32] = {0};
		sprintf(chIndex, "%d", nIndex);
		//m_signalMapper.setMapping(pEdit, phonevalue); 
		m_signalMapper.setMapping(pEdit, section);

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPhoneNum = pValue;
		list.pStatus = pState;
		list.id = section;
		m_pListSMS.push_back(list);
		
	}
	m_ptbPhone->adjustRowStyle("tr1","tr2");
	
			
}

void CSVSmsSet::showErrMsg(string &strErrMsg)
{
    if ( m_pErrMsg )
    {
        m_pErrMsg->setText(strErrMsg);
        m_pErrMsg->show();
    }
}

void CSVSmsSet::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_User_Name",m_formText.szInputUserLabel);
			FindNodeValue(ResNode,"IDS_SMS_Config",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Send_SMS_Web",m_formText.szWebSms);
			FindNodeValue(ResNode,"IDS_SMS_User_Desciption",m_formText.szUserDes);
			FindNodeValue(ResNode,"IDS_Password",m_formText.szPwdDes);
			FindNodeValue(ResNode,"IDS_Save",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_Test",m_formText.szTest);
			FindNodeValue(ResNode,"IDS_Send_SMS_Port",m_formText.szSerialPortDes);
			FindNodeValue(ResNode,"IDS_Port_Number",m_formText.szPortList);
			FindNodeValue(ResNode,"IDS_SMS_Receive_Phone_Config",m_formText.szTBTitle);
			FindNodeValue(ResNode,"IDS_SMS_Phone_List_Desciption",m_formText.szTableDes);
			FindNodeValue(ResNode,"IDS_All_Select",m_formText.szColSelAll);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szColName);
			FindNodeValue(ResNode,"IDS_State",m_formText.szColState);
			FindNodeValue(ResNode,"IDS_Phone_Number",m_formText.szColPhone);
			FindNodeValue(ResNode,"IDS_Edit",m_formText.szColEdit);
			FindNodeValue(ResNode,"IDS_SMS_Web_Note",m_formText.szNote);
			FindNodeValue(ResNode,"IDS_SMS_Phone_Add",m_formText.szAdd);
			FindNodeValue(ResNode,"IDS_SMS_Phone_Delete",m_formText.szDel);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Enable",m_formText.szEnable);
			FindNodeValue(ResNode,"IDS_All_Select_Other",m_formText.szTipSelAll);
			FindNodeValue(ResNode,"IDS_Add_SMS_Receive_Phone",m_formText.szAddPhoneBut);
			FindNodeValue(ResNode,"IDS_Connect_SVDB_Fail",m_formText.szConnErr);
			FindNodeValue(ResNode,"IDS_All_Select",m_formText.szTipSelAll1);
			FindNodeValue(ResNode,"IDS_None_Select",m_formText.szTipSelNone);
			FindNodeValue(ResNode,"IDS_Invert_Select",m_formText.szTipSelInv);
			FindNodeValue(ResNode,"IDS_Add",m_formText.szTipAddNew);
			FindNodeValue(ResNode,"IDS_Delete",m_formText.szTipDel);
			FindNodeValue(ResNode,"IDS_Save_Success",m_formText.szSaveSucess);
			FindNodeValue(ResNode,"IDS_SMS_Phone_List_Desciption",m_formText.szDescription);
			FindNodeValue(ResNode,"IDS_Check_SMS_Port",m_formText.szHelpCOM);
			FindNodeValue(ResNode,"IDS_Help",strHelp);
			FindNodeValue(ResNode,"IDS_Enable",strEnable);
			FindNodeValue(ResNode,"IDS_Disable",strDisable);
			FindNodeValue(ResNode,"IDS_Delete_SMS_Affirm",strDeleteSMSAffirm);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Edit",strTypeEdit);
			FindNodeValue(ResNode, "IDS_SELFDEFINEDLL", m_formText.szSelfDefine1);
			FindNodeValue(ResNode, "IDS_SELFDEFINEPARAM", m_formText.szSelfDefine2);
			FindNodeValue(ResNode, "IDS_SMS_DLL_Tilte", m_formText.szFuncTitle);
			FindNodeValue(ResNode, "IDS_DLL_Name", m_formText.szDllName);
			FindNodeValue(ResNode, "IDS_DLL_Function_Name", m_formText.szDllFunName);
			FindNodeValue(ResNode, "IDS_DLL_Parameter", m_formText.szDllFunParam);
			FindNodeValue(ResNode, "IDS_Up_Load", m_formText.szUpLoad);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",m_formText.szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",m_formText.szButMatch);
			FindNodeValue(ResNode,"IDS_SMS_Config",m_formText.strMainTitle);
			FindNodeValue(ResNode,"IDS_SMSPhoneListEmpty", m_formText.strNullList);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh1);
			FindNodeValue(ResNode,"IDS_ModifyWebMethod",strModifyWeb);
			FindNodeValue(ResNode,"IDS_ModifyPortMethod",strModifyPort);
			FindNodeValue(ResNode,"IDS_ModifyDLL",strModifyDLL);
			FindNodeValue(ResNode,"IDS_TestDLL",strTestDll);
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);
			FindNodeValue(ResNode,"IDS_Del_Confirm",strDelConfirm);
		}
		CloseResource(objRes);

/*		m_formText.szFuncTitle = "调用动态库中的函数发送短信";
		m_formText.szDllName = "动态库名称";
		m_formText.szDllFunName = "动态库函数名称";
		m_formText.szDllFunParam = "动态库函数参数";

		m_formText.szUpLoad = "上传";
*/
	}
/*
    m_formText.szTitle = "短信设置";
    m_formText.szWebSms = "以WEB方式发送短信";
    m_formText.szUserDes = "请输入用户名: 此手机号在短信报警中将作为报警发送方发送报警";
    m_formText.szPwdDes = "密码";
    m_formText.szSave = "保存";
    m_formText.szTest = "测试";
    m_formText.szSerialPortDes = "以串口方式发送短信";
    m_formText.szPortList = "端口号";
    m_formText.szTBTitle = "短信接收手机号设置";
    m_formText.szTableDes = "短信接收手机号设置允许设置命名的短信接收手机号码，设置的短信" \
        "接收手机号的名称将显示在短信报警的“报警接收手机号”列表中";
    m_formText.szColSelAll = "全选";
    m_formText.szColName = "名称";
    m_formText.szColState = "状态";
    m_formText.szColPhone = "手机号码";
    m_formText.szColEdit = "编辑";
    m_formText.szNote = "注：如果您使用WEB方式发送手机短信：请向游龙科技公司索要用户名、密码,"\
		"把用户名和密码输入相应的文本框即可";
    m_formText.szAdd = "增加短信接收号码";
    m_formText.szDel = "删除短信接收号码";
	m_formText.szDescription = "短信接收手机号设置允许设置命名的短信接收手机号，设置的短信接收" \
				"手机号的名称将显示在短信报警的“报警接收手机号”列表中";
	m_formText.szHelpCOM = "请选择短信猫所连接的串口";
	m_formText.strNullList = "[----------短信接收手机号设置列表为空-----------]";
	*/
}

void CSVSmsSet::ShowSendForm()
{

}

void CSVSmsSet::SaveConfig()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "SaveConfig";
	LogItem.sDesc = strModifyPort;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	// 需要继续编写保存配置代码 
	std::string port = m_pSerialPort->currentText();
	std::string temp = port.substr(port.size() - 1, 1);
	
	WriteIniFileString("SMSCommConfig", "Port", temp, "smsconfig.ini");

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeEdit,m_formText.szTitle,port);
	
	char buf[256]={0};
	memset(buf,0,256);
	sprintf(buf, "%s,%s,%s", "smsconfig.ini", "SMSCommConfig", "EDIT");

	if(!::PushMessage("SiteView70-Alert","IniChange",buf,strlen(buf)+1))
	{
		OutputDebugString("Push data failed");
		/*return;*/
	}

	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += m_formText.szSaveSucess;
	WebSession::js_af_up += "')";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSmsSet::SaveConfig1()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "SaveConfig1";
	LogItem.sDesc = strModifyWeb;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	std::string user = m_pUserID ->text();
	std::string pwd = m_pUserPwd ->text();

	Des mydes;
	
	if (user.empty())
	{
		list<string> list;
		m_pWebGeneral->HideAllErrorMsg();
		list.push_back(m_formText.szUserDes);
		m_pWebGeneral->ShowErrorMsg(list);
		OutputDebugString(m_formText.szUserDes.c_str());
		bEnd = true;	
		goto OPEnd;
	}

	char enchar[1024]={0};
	if(pwd.size() > 0)
	{
		mydes.Encrypt(pwd.c_str(),enchar);
		pwd= enchar;
	}
	
	WriteIniFileString("SMSWebConfig", "User", user, "smsconfig.ini");
	WriteIniFileString("SMSWebConfig", "Pwd", pwd, "smsconfig.ini");

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeEdit,m_formText.szTitle,user);

	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += m_formText.szSaveSucess;
	WebSession::js_af_up += "')";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSmsSet::SelAll()
{
	for(m_pListItem = m_pListSMS.begin(); m_pListItem != m_pListSMS.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(true);
    }
}

void CSVSmsSet::AddPhone()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "AddPhone";
	LogItem.sDesc = m_formText.szAddPhoneBut;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	OutputDebugString("-------------AddPhone----------------\n");
    emit AddNewPhone();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 -dcalBegin);
}

void CSVSmsSet::EditRow(const std::string str)
{
	chgstr = str;
    SAVE_PHONE_LIST phone;

	std::string ret;
	phone.id = str;
	phone.szPhone = GetIniFileString(str, "Phone", ret, "smsphoneset.ini");
	phone.szName = GetIniFileString(str,"Name", ret, "smsphoneset.ini");
	std::string temp = GetIniFileString(str, "Status", ret, "smsphoneset.ini");
	phone.szPlan = GetIniFileString(str, "Plan", ret, "smsphoneset.ini");
	phone.szTemplet = GetIniFileString(str, "Template", ret, "smsphoneset.ini");
	if(strcmp(temp.c_str(), "Yes") == 0)
	{
		phone.bDisable = false;
	}
	else
	{
		phone.bDisable = true;
	}
	phone.chgstr = str;

	emit EditPhone(phone);
}

void CSVSmsSet::DelPhone()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "DelPhone";
	LogItem.sDesc = strDelConfirm;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strDeletePhone;
	for(m_pListItem = m_pListSMS.begin(); m_pListItem != m_pListSMS.end(); m_pListItem ++)
    {
        
        if (m_pListItem->pSelect->isChecked())
        {   
        
			std::string temp = m_pListItem->id;
		
			DeleteIniFileSection(temp, "smsphoneset.ini");

            int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();
        
            list<SMS_LIST>::iterator pItem = m_pListItem;                     
        
            m_pListItem --;
        
			string strTemp = pItem->pName->text();
			strDeletePhone += strTemp;
			strDeletePhone += "  ";

			m_pListSMS.erase(pItem);          
        
            m_pListGeneral->GeDataTable()->deleteRow(nRow); 						
        }
    }

	// if(m_pListSMS.size() == 0)
	//{
	//	//WText * nText = new WText("[----------短信接收手机号设置列表为空-----------]", (WContainerWidget*)m_nullTable -> elementAt(0, 0));
	//	//nText ->decorationStyle().setForegroundColor(Wt::red);
	//	//m_nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}
	if(m_pListSMS.size() == 0)
	{
		m_pListGeneral->ShowNullTip();
	}
	else
	{
		m_pListGeneral->HideNullTip();
	}

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_formText.szTipDel,m_formText.szTitle,strDeletePhone);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSmsSet::SavePhone(SAVE_PHONE_LIST * phone)
{
    
	if(strcmp(chgstr.c_str(), "") != 0)
    {
        Edit_Phone(phone);
        return;
    }
    
    int numRow = m_pListGeneral->GeDataTable()->numRows();
	
	m_pListGeneral->InitRow(numRow);

    WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow, 0));
	m_pListGeneral->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);
    
	WText *pName = new WText(phone->szName, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 2));
	m_pListGeneral->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
    
	WText * pValue = new WText(phone->szPhone, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 6));
	m_pListGeneral->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);

    
    WText * pState = NULL;
    if(!phone->bDisable)
    {
	    pState = new WText(m_formText.szEnable, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow  , 4));
		m_pListGeneral->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
    }
    else
    {
        pState = new WText(m_formText.szDisable, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow  , 4));
		m_pListGeneral->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
    }

	WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 8));
    pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);    

    int nIndex = RandIndex();
    char chIndex[32] = {0};
    sprintf(chIndex, "%d", nIndex);
  
 	string key;
	std::string ret;
	char buf[256];
	key = GetIniFileString("Key", "Count", key, "smskey.ini");
	int key1 = atoi(key.c_str());
	key1++;
	itoa(key1, buf, 10);
	WriteIniFileString("Key", "Count", buf, "smskey.ini");

	if(strcmp(key.c_str(), "") == 0)
	{
		key = "0";
	}
	phone->id = key;
	m_signalMapper.setMapping(pEdit, phone->id);

	WriteIniFileString(key, "Phone", phone->szPhone, "smsphoneset.ini");
	WriteIniFileString(key, "Name", phone->szName, "smsphoneset.ini");
	if(phone->bDisable)
	{
		WriteIniFileString(key, "Status", "No", "smsphoneset.ini");
	}
	else
	{
		WriteIniFileString(key, "Status", "Yes", "smsphoneset.ini");
	}

	WriteIniFileString(key, "Plan", phone->szPlan, "smsphoneset.ini");
	WriteIniFileString(key, "Template", phone->szTemplet, "smsphoneset.ini");

	SMS_LIST list;
	list.id = key;
	list.pSelect = pCheck;
	list.pName = pName;
	list.pPhoneNum = pValue;
	list.pStatus = pState;
	m_pListSMS.push_back(list);
	
	if(m_pListSMS.size() == 0)
	{
		m_pListGeneral->ShowNullTip();
	}
	else
	{
		m_pListGeneral->HideNullTip();
	}

    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
}

void CSVSmsSet::Edit_Phone(SAVE_PHONE_LIST * phone)
{
	std::string key;
	WriteIniFileString(phone->id, "Phone", phone->szPhone, "smsphoneset.ini");
	WriteIniFileString(phone->id, "Name", phone->szName, "smsphoneset.ini");
	WriteIniFileString(phone->id, "Plan", phone->szPlan, "smsphoneset.ini");
	WriteIniFileString(phone->id, "Template", phone->szTemplet, "smsphoneset.ini");
	if(phone->bDisable)
	{
		WriteIniFileString(phone->id, "Status", "No", "smsphoneset.ini");
	}
	else
	{
		WriteIniFileString(phone->id, "Status", "Yes", "smsphoneset.ini");
	}

	for(m_pListItem = m_pListSMS.begin(); m_pListItem != m_pListSMS.end(); m_pListItem++)
	{
		if(strcmp(chgstr.c_str(), m_pListItem->id.c_str()) == 0)
		{
			m_pListItem->pName->setText(phone->szName);
			m_pListItem->pPhoneNum->setText(phone->szPhone);
			if(phone->bDisable)
			{
				m_pListItem->pStatus->setText(strDisable);
			}
			else
			{
				m_pListItem->pStatus->setText(strEnable);
			}
		}
	}
	chgstr = "";
}

void CSVSmsSet::showDllTable()
{
	pShow3 -> show();
	pHide3 -> hide();
	table3 -> show();
}

void CSVSmsSet::hideDllTable()
{
	pShow3 -> hide();
	pHide3 -> show();
	table3 -> hide();
}

void CSVSmsSet::SaveDllConfig()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "SaveDllConfig";
	LogItem.sDesc = strModifyDLL;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	std::string szDllName = m_pCDllName->currentText();
	std::string szDllFunParam = m_pDllFunParam->text();
	
	string strName = GetDllNameFromStr(szDllName);
	string strInfo = GetDllInfoFromStr(szDllName);
	
	WriteIniFileString(strName, "DllName", strName, "interfacedll.ini");
	WriteIniFileString(strName, "DllInfo", strInfo, "interfacedll.ini");
	WriteIniFileString(strName, "DllFunParam", szDllFunParam, "interfacedll.ini");

	//if(szDllName.find("") != -1)
	//{
	//	WriteIniFileString("SMSDllConfig", "DllName", szDllName, "dialconfig.ini");
	//	WriteIniFileString("SMSDllConfig", "DllFunParam", szDllFunParam, "dialconfig.ini");	
	//}
	//else
	//{
	//	WriteIniFileString("SMSDllConfig", "DllName", szDllName, "smsconfig.ini");
	//	WriteIniFileString("SMSDllConfig", "DllFunParam", szDllFunParam, "smsconfig.ini");
	//}
	
	//string strdllname = GetIniFileString("SMSDllConfig", "DllName", "", "smsconfig.ini");
	//OutputDebugString("-------------smsset savedllconfig output-----------------------\n");
	//OutputDebugString(szDllName.c_str());
	//OutputDebugString("\n");

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeEdit,m_formText.szTitle,szDllName);
	
	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += m_formText.szSaveSucess;
	WebSession::js_af_up += "')";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSmsSet::UpLoadFile()
{
	WFileUpload *upload_ = new WFileUpload(this);
	WebSession::js_af_up = "ReadFiles()";
	OutputDebugString("----------------------up load file---------------------\n");

}

void CSVSmsSet::showSmsList()
{
	pShow -> show();
	pHide -> hide();
	table -> show();
}

void CSVSmsSet::hideSmsList()
{
	pShow -> hide();
	pHide -> show();
	table -> hide();
}

void CSVSmsSet::showSmsList1()
{
	pShow1 -> show();
	pHide1 -> hide();
	table1 -> show();
}

void CSVSmsSet::hideSmsList1()
{
	pShow1 -> hide();
	pHide1 -> show();
	table1 -> hide();
}

void CSVSmsSet::showSmsList2()
{
	
	pShow2 -> show();
	pHide2 -> hide();
	table2 -> show();
}

void CSVSmsSet::hideSmsList2()
{	
	pShow2 -> hide();
	pHide2 -> show();
	table2 -> hide();
}



void CSVSmsSet::AddGroupOperate(WTable * pTable)
{
    m_pGroupOperate = new WTable((WContainerWidget *)pTable->elementAt( 8, 0));
    if ( m_pGroupOperate )
    {
/*		new WText("&nbsp&nbsp&nbsp",(WContainerWidget *)m_pGroupOperate->elementAt( 0, 1));
        WText * pSelAll = new WText("全选", (WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
        if (pSelAll)
        {
            pSelAll->setStyleClass("nullLink");
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

		new WText("&nbsp&nbsp&nbsp",(WContainerWidget *)m_pGroupOperate->elementAt( 0, 2));
        WText * pSelNone = new WText("全不选", (WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
        if (pSelAll)
        {
            pSelNone->setStyleClass("nullLink");
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

		new WText("&nbsp&nbsp&nbsp",(WContainerWidget *)m_pGroupOperate->elementAt( 0, 3));
        WText * pSelinvert = new WText("反选", (WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
        if (pSelinvert)
        {
            pSelinvert->setStyleClass("nullLink");
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		new WText("&nbsp&nbsp&nbsp",(WContainerWidget *)m_pGroupOperate->elementAt( 0, 4));
		WText * pDel = new WText("删除", (WContainerWidget *)m_pGroupOperate->elementAt(0, 4));
        if (pDel)
        {           
			pDel->setStyleClass("nullLink");
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));

			//隐藏按钮
			pHideBtn = new WPushButton("hide button",this);
			if(pHideBtn)
			{
				connect(pHideBtn,SIGNAL(clicked()),this,SLOT(DelPhone()));
				pHideBtn->hide();
			}
       }
*/
        WImage * pSelAll = new WImage("../Images/selall.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
        if (pSelAll)
        {
            pSelAll->setStyleClass("imgbutton");
			pSelAll->setToolTip(m_formText.szTipSelAll1);
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

        WImage * pSelNone = new WImage("../Images/selnone.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
        if (pSelAll)
        {
            pSelNone->setStyleClass("imgbutton");
			pSelNone->setToolTip(m_formText.szTipSelNone);
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

        WImage * pSelinvert = new WImage("../Images/selinvert.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
        if (pSelinvert)
        {
            pSelinvert->setStyleClass("imgbutton");
			pSelinvert->setToolTip(m_formText.szTipSelInv);
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		WImage * pDel = new WImage("../Images/del.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 4));
        if (pDel)
        {
           
			pDel->setStyleClass("imgbutton");
			pDel->setToolTip(m_formText.szTipDel);
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelPhone()));
        }

		WPushButton *pAdd = new WPushButton(m_formText.szAddPhoneBut, (WContainerWidget *)m_pGroupOperate->elementAt(0, 6));
        if (pAdd)
        {
            pAdd->setToolTip(m_formText.szTipAddNew);
			pAdd->setStyleClass("wizardbutton");
            WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(AddPhone()));
			//隐藏按钮
			pHideBtn = new WPushButton("hide button",this);
			if(pHideBtn)
			{
				connect(pHideBtn,SIGNAL(clicked()),this,SLOT(DelPhone()));
				pHideBtn->hide();
			}
        }
		
		m_pGroupOperate->elementAt(0, 6)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
		m_pGroupOperate->elementAt(0, 6)->setContentAlignment(AlignRight);
    }
}

void CSVSmsSet::BeforeDelPhone()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "BeforeDelPhone";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem = m_pListSMS.begin(); m_pListItem != m_pListSMS.end(); m_pListItem ++)
    {        
        if (m_pListItem->pSelect->isChecked())
        {   
			if(pHideBtn)
			{
				string strDelDes = pHideBtn->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + strDeleteSMSAffirm + "','" + m_formText.szButNum + "','" + m_formText.szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;
					OutputDebugString("-------------BeforeDelPhone-----------------");
					OutputDebugString(strDelDes.c_str());
				}					
			}
			break;
        }
    }

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVSmsSet::SelNone()
{
	for(m_pListItem = m_pListSMS.begin(); m_pListItem != m_pListSMS.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(false);
    }
}
void CSVSmsSet::SelInvert()
{
	for(m_pListItem = m_pListSMS.begin(); m_pListItem != m_pListSMS.end(); m_pListItem ++)
    {
		if(m_pListItem->pSelect->isChecked())
		{
			m_pListItem->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem->pSelect->setChecked(true);
		}
    }
}

void CSVSmsSet::MainHelp()
{
	/*if(IsShow)
	{
//		m_pHelpUserID->show();
		pNote->show();
		m_pHelpCOM->show();
		m_pHelpSelfDefine1->show();
		m_pHelpSelfDefine2->show();
		IsShow = false;
	}
	else
	{
		m_pHelpUserID->hide();
		pNote->hide();
		m_pHelpCOM->hide();
		m_pHelpSelfDefine1->hide();
		m_pHelpSelfDefine2->hide();
		IsShow = true;
	}*/
	m_pWebGeneral->ShowOrHideHelp();
	m_pGeneral->ShowOrHideHelp();
	m_pDllTable->ShowOrHideHelp();
}

void CSVSmsSet::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "SMS Set";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh1;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	OutputDebugString("refresh\n");
	//m_nullTable->clear();
	UpdatePhoneList();

	//翻译
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

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

void CSVSmsSet::UpdatePhoneList()
{
	int nNum = m_pListGeneral->GeDataTable()->numRows();
	for(int i=1;i < nNum;i++)
	{
		m_pListGeneral->GeDataTable()->deleteRow(1);

	}

	m_pListSMS.clear();
	std::list<string> sectionlist;
	std::list<string>::iterator m_sItem;
	GetIniFileSections(sectionlist, "smsphoneset.ini");
 //   if(sectionlist.size() == 0)
	//{
	//	WText * nText = new WText("[----------短信接收手机号设置列表为空-----------]", (WContainerWidget*)m_nullTable -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	m_nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}
	if(sectionlist.size() == 0)
	{
		m_pListGeneral->ShowNullTip();
	}
	else
	{
		m_pListGeneral->HideNullTip();
	}
	for(m_sItem = sectionlist.begin(); m_sItem != sectionlist.end(); m_sItem++)
	{
		std::string section = *m_sItem;

		int numRow = m_pListGeneral->GeDataTable()->numRows();
		m_pListGeneral->InitRow(numRow);

		SMS_LIST list;

		// 是否选择
		WCheckBox * pCheck = new WCheckBox("", m_pListGeneral->GeDataTable()->elementAt(numRow,0));
		m_pListGeneral->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);

		// 名称
		std::string value = GetIniFileString(section, "Name", ret, "smsphoneset.ini");
		WText * pName = new WText(value, m_pListGeneral->GeDataTable()->elementAt(numRow,2));
		m_pListGeneral->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);

		// 状态
		value = GetIniFileString(section, "Status", ret, "smsphoneset.ini");
		WText * pState = NULL;
		if(strcmp(value.c_str(), "Yes") == 0)
		{
			pState = new WText(m_formText.szEnable, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow  , 4));
			m_pListGeneral->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
		}
		else
		{
			pState = new WText(m_formText.szDisable, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow  , 4));
			m_pListGeneral->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
		}

		// 手机号码
		std::string phonevalue = GetIniFileString(section,"Phone" , ret, "smsphoneset.ini");
		WText * pValue = new WText(phonevalue, (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 6));
		m_pListGeneral->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(AlignCenter);

		WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)m_pListGeneral->GeDataTable()->elementAt(numRow , 8));
		m_pListGeneral->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(AlignCenter);
		pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
		connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));

		int nIndex = RandIndex();
		char chIndex[32] = {0};
		sprintf(chIndex, "%d", nIndex);
		//m_signalMapper.setMapping(pEdit, phonevalue); 
		m_signalMapper.setMapping(pEdit, section);

		list.pSelect = pCheck;
		list.pName = pName;
		list.pPhoneNum = pValue;
		list.pStatus = pState;
		list.id = section;
		m_pListSMS.push_back(list);
	}	
}


//////////////////////////////////////////////////////////////////////////////////
// end file
