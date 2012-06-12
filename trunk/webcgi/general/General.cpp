#include ".\general.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "..\svtable\FlexTable.h"
#include "..\svtable\MainTable.h"
///////////////////////////////////////////
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"
///////////////////////////////////////////
#include "WApplication"
#include "websession.h"
#include "WCheckBox"
#include "WLineEdit"
#include "WImage"
///////////////////////////////////////////
#include "../../base/splitquery.h"
#include "../base/OperateLog.h"
using namespace SV_Split;
///////////////////////////////////////////


CGeneral::CGeneral(WContainerWidget *parent ):
WContainerWidget(parent)
{
	strCurrentLanguage = "chinese";

	loadString();

	NewShowMainTable();

	//ShowMainTable();
}

CGeneral::~CGeneral(void)
{
}

//添加客户端脚本变量
void CGeneral::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CGeneral::loadString()
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_General_MainTitle",strMainTitle);
			FindNodeValue(ResNode,"IDS_General_Title",strTitle);
			FindNodeValue(ResNode,"IDS_IP_Check",strCheckBox);
			FindNodeValue(ResNode,"IDS_IP_Edit",strEdit);
			FindNodeValue(ResNode,"IDS_Save",strSave);
			FindNodeValue(ResNode,"IDS_IP_Check_Help",strHelp);
			FindNodeValue(ResNode,"IDS_Save_Date",strDateName);
			FindNodeValue(ResNode,"IDS_Save_Date_Help",strDateHelp);
			FindNodeValue(ResNode,"IDS_IP_Edit_Error",sErrIP);
			FindNodeValue(ResNode,"IDS_Save_Date_Error",sErrDate);
			FindNodeValue(ResNode,"IDS_Save_Date_Error1",sErrDate1);
			FindNodeValue(ResNode,"IDS_Save_Success",szSaveSucess);
			FindNodeValue(ResNode,"IDS_Save_Fail",szSaveFail);
			FindNodeValue(ResNode,"IDS_General_Advanced_Title",strMtitle);
			FindNodeValue(ResNode,"IDS_Customer_Name",strBName);
			FindNodeValue(ResNode,"IDS_Monitor_Server_Name",strSName);
			FindNodeValue(ResNode,"IDS_Customer_Name_Help",strCustomHelp);
			FindNodeValue(ResNode,"IDS_Monitor_Server_Name_Help",strSEHelp);
			FindNodeValue(ResNode,"IDS_Customer_Name_Error",sCustomErr);
			FindNodeValue(ResNode,"IDS_Monitor_Server_Name_Error",sSEErr);
			FindNodeValue(ResNode,"IDS_Edit",strOType);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Modify_Monitor_Server_Name",strModifyName);
			FindNodeValue(ResNode,"IDS_Modify_Day_IP",strModifyDay);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh1);
		}
		CloseResource(objRes);
	}
}

//最新初始化界面 jansion.zhou 2006-12-22
void CGeneral::NewShowMainTable()
{
	new WText("<div id='view_panel' class='panel_view'>",this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	
	

	m_pMainTable = new WSVMainTable(this, strMainTitle, true);
	if (m_pMainTable->pHelpImg)
	{
		connect(m_pMainTable->pHelpImg, SIGNAL(clicked()), this, SLOT(ShowHelp()));
	}

	//bShow = true;

	m_sFlexTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1, 0), Group, strTitle);

	if (m_sFlexTable->GetContentTable() != NULL)
	{
		m_sFlexTable->AppendRows("");
		pCheckBox = new WCheckBox(strCheckBox, m_sFlexTable->AppendRowsContent(0, "", "", ""));
		connect(pCheckBox,SIGNAL(clicked()),this,SLOT(ShowEdit()));
		
		pIPEdit = new WLineEdit("", m_sFlexTable->AppendRowsContent(0, strEdit, strHelp, sErrIP));
		pIPEdit->resize(WLength(300, WLength::Pixel), 0);
		pIPEdit->setStyleClass("input_text");

		pDataEdit = new WLineEdit("", m_sFlexTable->AppendRowsContent(0, strDateName+"<span class =required>*</span>", strDateHelp, sErrDate));
		pDataEdit->resize(WLength(80, WLength::Pixel), 0);
		pDataEdit->setStyleClass("input_text");

		new WText("", m_sFlexTable->AppendRowsContent(0, "","",sErrDate1));

		m_sFlexTable->ShowOrHideHelp();
		m_sFlexTable->HideAllErrorMsg();
	}

	if (m_sFlexTable->GetActionTable() != NULL)
	{
		//pSaveButton = new WSVButton(,m_sFlexTable->GetActionTable()->elementAt(0,1));
		pSaveButton = new WSVButton(m_sFlexTable->GetActionTable()->elementAt(0, 1), strSave, "button_bg_m_black.png", strSave, true);
		connect(pSaveButton, SIGNAL(clicked()), this, SLOT(Save()));
	}

	//读取ini文件
	IPAddress pIPAddress;
	pIPAddress.iCheck = GetIniFileInt("IPCheck", "isCheck", 0,  "general.ini");
	if(pIPAddress.iCheck==1)
	{
		pCheckBox->setChecked(true);
		pIPEdit->enable();
	}
	else
	{
		pCheckBox->setChecked(false);
		pIPEdit->disable();
	}
	pIPAddress.strIPAddress = GetIniFileString("IPCheck", "IPAddress", "",  "general.ini");
	pIPEdit->setText(pIPAddress.strIPAddress);
	int iDate;
	bool bGetDate = GetLogKeepDays(iDate);
	char buf[256] = {0};
	itoa(iDate,buf,10);
	pIPAddress.strDate = buf;
	pDataEdit->setText(pIPAddress.strDate);

	m_aFlexTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(2, 0), Group, strMtitle);

	if (m_aFlexTable->GetContentTable() != NULL)
	{
		m_aFlexTable->AppendRows("");
		
		 /***********************
		 *    0  多机版  
		 *    1  单机版 
		 ***********************/
		bVersion = GetIniFileInt("solover","solover",1,"general.ini");
	
		if(bVersion==0)
		{
			//读取客户名称
			std::string strCustomName;

			strCustomName = GetIniFileString("segroup","name","","general.ini");

			pAdvancedEdit = new WLineEdit(strCustomName, m_aFlexTable->AppendRowsContent(0, strSName+"<span class =required>*</span>", strSEHelp, sSEErr));
			pAdvancedEdit->resize(WLength(300, WLength::Pixel), 0);
			pAdvancedEdit->setStyleClass("input_text");
		}
		else if(bVersion==1)
		{
		//SVSE
			std::string strLabel = "";
			OBJECT objSE;
			objSE = GetSVSE("1");
			if(objSE != INVALID_VALUE)
			{
				strLabel=GetSVSELabel(objSE);
				CloseSVSE(objSE);
			}
			pAdvancedEdit = new WLineEdit(strSName, m_aFlexTable->AppendRowsContent(0, strSName+"<span class = required>*</span>", strSEHelp, sSEErr));
			pAdvancedEdit->resize(WLength(300, WLength::Pixel), 0);
			pAdvancedEdit->setStyleClass("input_text");
		}
		m_aFlexTable->ShowOrHideHelp();
		m_aFlexTable->HideAllErrorMsg();
	}

	if (m_aFlexTable->GetActionTable() !=NULL)
	{
		pSaveButton2 = new WSVButton(m_aFlexTable->GetActionTable()->elementAt(0, 1), strSave, "button_bg_m_black.png", strSave, true);
		connect(pSaveButton2, SIGNAL(clicked()), this, SLOT(SaveName()));
	}


	//translate refresh button
	int mRow = m_pMainTable->GetContentTable()->numRows();

	m_TranslateBtn = new WPushButton(strTranslate, m_pMainTable->GetContentTable()->elementAt(mRow, 0));
	m_TranslateBtn->setToolTip(strTranslateTip);
	connect(m_TranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));

	//new WText("&nbsp;&nbsp;", m_pMainTable->GetContentTable()->elementAt(mRow, 0));

	m_ExChangeBtn = new WPushButton(strRefresh, m_pMainTable->GetContentTable()->elementAt(mRow, 0));
	m_ExChangeBtn->setToolTip(strRefreshTip);
	connect(m_ExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		m_TranslateBtn->show();
		m_ExChangeBtn->show();
	}
	else
	{
		m_TranslateBtn->hide();
		m_ExChangeBtn->hide();
	}
	

	new WText("</div>",this);
	AddJsParam("bGeneral", "false");
	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

}

//初始化主界面
void CGeneral::ShowMainTable()
{
//
//	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	
//
//	pMainTable = new CMainTable(this, strMainTitle);
//	pUserTable = new CFlexTable(pMainTable->elementAt(2,0),strTitle);
//	pUserListTable = new WTable( pUserTable->GetContentTable()->elementAt(0,0));
//	pUserListTable ->setStyleClass("t3");
//
//	pCheckBox=new WCheckBox(strCheckBox, (WContainerWidget*)pUserListTable->elementAt(0, 1));
//	connect(pCheckBox,SIGNAL(clicked()),this,SLOT(ShowEdit()));
//
//	pUserListTable->elementAt(0,0)->resize(WLength(15, WLength::Percentage),WLength(100, WLength::Percentage));
//
//	pIPText = new WText(strEdit,(WContainerWidget*)pUserListTable->elementAt(1, 0));
//	pIPEdit = new WLineEdit("", (WContainerWidget*)pUserListTable->elementAt(1, 1));
//	pIPEdit->setTextSize(100);
//
//	//IP地址不能为空
//	pMainTable->AddErrorText(pUserListTable,sErrIP,2,1);
//
//	pMainTable->AddHelpText(pUserListTable,strHelp,3,1);
//
//
//
//	//保存天数
//	pSaveDataText = new WText(strDateName,(WContainerWidget*)pUserListTable->elementAt(4, 0));
//	new WText("<span class =required>*</span>", (WContainerWidget*)pUserListTable->elementAt(4, 0));
//	pDataEdit=new WLineEdit("", (WContainerWidget*)pUserListTable->elementAt(4, 1));
//	pDataEdit->setTextSize(25);
//	
//	pMainTable->AddErrorText(pUserListTable,sErrDate,5,1);
//	pMainTable->AddErrorText(pUserListTable,sErrDate1,5,1);
//
//	pMainTable->AddHelpText(pUserListTable,strDateHelp,6,1);
//
//	// 保存功能
//	pSaveButton3 = new WPushButton(strSave,(WContainerWidget*)pUserListTable->elementAt(7,0));
//	connect(pSaveButton3, SIGNAL(clicked()), this, SLOT(Save()));
//
//
//	//读取ini文件
//	IPAddress pIPAddress;
//	pIPAddress.iCheck = GetIniFileInt("IPCheck", "isCheck", 0,  "general.ini");
//	if(pIPAddress.iCheck==1)
//	{
//		pCheckBox->setChecked(true);
//		pIPEdit->enable();
//	}
//	else
//	{
//		pCheckBox->setChecked(false);
//		pIPEdit->disable();
//	}
//	pIPAddress.strIPAddress = GetIniFileString("IPCheck", "IPAddress", "",  "general.ini");
//	pIPEdit->setText(pIPAddress.strIPAddress);
//	int iDate;
//	bool bGetDate = GetLogKeepDays(iDate);
//	char buf[256] = {0};
//	itoa(iDate,buf,10);
//	pIPAddress.strDate = buf;
//	pDataEdit->setText(pIPAddress.strDate);
//	
//	//
//	pUserTable2 = new CFlexTable(pMainTable->elementAt(3,0),strMtitle);
//	pUserListTable2 = new WTable( pUserTable2->GetContentTable()->elementAt(0,0));
//	pUserListTable2 ->setStyleClass("t3");
//
//	pUserListTable2->elementAt(0,0)->resize(WLength(15, WLength::Percentage),WLength(100, WLength::Percentage));
//
//	bVersion = GetIniFileInt("solover","solover",1,"general.ini");
//	
//	 /***********************
//	 *    0  多机版  
//	 *    1  单机版 
//	 ***********************/
//	
//	if(bVersion==0)
//	{
//		//客户名称
//		pAdvancedText = new WText(strBName,(WContainerWidget*)pUserListTable2->elementAt(1, 0));
//		new WText("<span class =required>*</span>", (WContainerWidget*)pUserListTable2->elementAt(1, 0));
//		//读取客户名称
//		std::string strCustomName;
///*		OBJECT objSE;
//		objSE = GetSVSE("1");
//		if(objSE != INVALID_VALUE)
//		{
//			strCustomName=GetSVSELabel(objSE);
//			CloseSVSE(objSE);
//		}
//*/
//		strCustomName = GetIniFileString("segroup","name","","general.ini");	
//		pAdvancedEdit = new WLineEdit(strCustomName, (WContainerWidget*)pUserListTable2->elementAt(1, 1));
//		pAdvancedEdit->setTextSize(50);
//		
//		pMainTable->AddErrorText(pUserListTable2,sCustomErr,2,1);
//		pMainTable->AddHelpText(pUserListTable2,strCustomHelp,3,1);
//	}
//	else if(bVersion==1)
//	{
//		//SVSE
//		pAdvancedText = new WText(strSName,(WContainerWidget*)pUserListTable2->elementAt(1, 0));
//		new WText("<span class =required>*</span>", (WContainerWidget*)pUserListTable2->elementAt(1, 0));
//		std::string strLabel = "";
//		OBJECT objSE;
//		objSE = GetSVSE("1");
//		if(objSE != INVALID_VALUE)
//		{
//			strLabel=GetSVSELabel(objSE);
//			CloseSVSE(objSE);
//		}
//		
//		pAdvancedEdit = new WLineEdit(strLabel, (WContainerWidget*)pUserListTable2->elementAt(1, 1));
//		pAdvancedEdit->setTextSize(50);
//
//		pMainTable->AddErrorText(pUserListTable2,sSEErr,2,1);
//		pMainTable->AddHelpText(pUserListTable2,strSEHelp,3,1);
//	}
//
//	// 保存功能
//	pSaveButton4 = new WPushButton(strSave,(WContainerWidget*)pUserListTable2->elementAt(4,0));
//	connect(pSaveButton4, SIGNAL(clicked()), this, SLOT(SaveName()));
//	
//	/*********************************
//	 *  translate  
//	 *      1   显示
//	 *      0   隐藏
//	 *********************************/
//	//翻译
//	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
//	if(bTrans == 1)
//	{
//		pMainTable->pTranslateBtn->show();
//		connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
//
//		pMainTable->pExChangeBtn->show();
//		connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
//	}
//	else
//	{
//		pMainTable->pTranslateBtn->hide();
//		pMainTable->pExChangeBtn->hide();
//	}

}
void CGeneral::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/general.exe?'\",1250);  ";
	appSelf->quit();
}
void CGeneral::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "generalRes";
	WebSession::js_af_up += "')";
}

void CGeneral::ShowHelp()
{
	m_sFlexTable->ShowOrHideHelp();
	m_aFlexTable->ShowOrHideHelp();
}

void CGeneral::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "general";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh1;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//取数据
	//基础选项
	IPAddress pIPAddress;
	pIPAddress.iCheck = GetIniFileInt("IPCheck", "isCheck", 0,  "general.ini");
	if(pIPAddress.iCheck==1)
	{
		pCheckBox->setChecked(true);
		pIPEdit->enable();
	}
	else
	{        
		pCheckBox->setChecked(false);
		pIPEdit->disable();
	}
	pIPAddress.strIPAddress = GetIniFileString("IPCheck", "IPAddress", "",  "general.ini");
	pIPEdit->setText(pIPAddress.strIPAddress);
	int iDate;
	bool bGetDate = GetLogKeepDays(iDate);
	char buf[256] = {0};
	itoa(iDate,buf,10);
	pIPAddress.strDate = buf;
	pDataEdit->setText(pIPAddress.strDate);		

	//高级选项
	bVersion = GetIniFileInt("solover","solover",1,"general.ini");

	if(bVersion==0)
	{
		//客户名称
		//jansion.zhou 2006-12-25
		//pAdvancedText->setText(strBName);
		//读取客户名称
		std::string strCustomName;

		strCustomName = GetIniFileString("segroup","name","","general.ini");	
		pAdvancedEdit->setText(strCustomName);
	}
	else if(bVersion==1)
	{
		//SVSE
		//jansion.zhou 2006-12-25
		//pAdvancedText->setText(strSName);
		

		std::string strLabel = "";

		OBJECT objSE;
		objSE = GetSVSE("1");

		if(objSE != INVALID_VALUE)
		{
			strLabel=GetSVSELabel(objSE);
			CloseSVSE(objSE);
		}
		pAdvancedEdit->setText(strLabel);
	}
	loadString();

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		m_TranslateBtn->show();
		m_ExChangeBtn->show();
	}
	else
	{
		m_TranslateBtn->hide();
		m_ExChangeBtn->hide();
	}
	//jansion.zhou 2006-12-22
	//if(bTrans == 1)
	//{
	//	pMainTable->pTranslateBtn->show();
	//	connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

	//	pMainTable->pExChangeBtn->show();
	//	connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	//}
	//else
	//{
	//	pMainTable->pTranslateBtn->hide();
	//	pMainTable->pExChangeBtn->hide();
	//}

	m_aFlexTable->HideAllErrorMsg();
	m_sFlexTable->HideAllErrorMsg();


	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

void CGeneral::SaveName()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "general";
	LogItem.sHitFunc = "SaveName";
	LogItem.sDesc = strModifyName;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	std::list<string> errorMsgList;
	bool bShowErr=false;

	if(pAdvancedEdit->text().empty())
	{
		if(bVersion==0)
		{
			errorMsgList.push_back(sCustomErr);		
		}
		else
		{
			errorMsgList.push_back(sSEErr);			
		}
		bShowErr=true;
	}

OPEnd:

	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}
	//Jansion.zhou 2006-12-22
	//pMainTable->ShowErrorMsg(errorMsgList);
	m_aFlexTable->ShowErrorMsg(errorMsgList);
	if(bShowErr==true)
	{
		bEnd = true;	
		goto OPEnd;
	}

	bVersion = GetIniFileInt("solover","solover",1,"general.ini");

	if(bVersion==0)
	{
		WriteIniFileString("segroup", "name", pAdvancedEdit->text() , "general.ini");
		//触发保存成功事件
		WebSession::js_af_up = "alert('";
		WebSession::js_af_up += szSaveSucess;
		WebSession::js_af_up += "')";
	}
	else if(bVersion==1)
	{
		//保存SE
		OBJECT objSE;
		objSE = GetSVSE("1");
		if(objSE != INVALID_VALUE)
		{
			if(PutSVSELabel(objSE,pAdvancedEdit->text()))
			{
				if(SubmitSVSE(objSE))
				{
					CloseSVSE(objSE);
					//触发保存成功事件
					WebSession::js_af_up = "alert('";
					WebSession::js_af_up += szSaveSucess;
					WebSession::js_af_up += "')";
				}
			}
		}
		else
		{
			WebSession::js_af_up = "alert('";
			WebSession::js_af_up += szSaveFail;
			WebSession::js_af_up += "')";
		}
	}
	else
	{
		WebSession::js_af_up = "alert('";
		WebSession::js_af_up += szSaveFail;
		WebSession::js_af_up += "')";
	}

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();

	bVersion = GetIniFileInt("solover","solover",1,"general.ini");
	
	if(bVersion==0)
	{
		strOName = strBName;
	}
	else
	{
		strOName = strSName;
	}
	
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strOName,pAdvancedEdit->text());

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 -dcalBegin);
/*	
	TTime beginTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts(0,24,0,0);
	beginTime -= ts;

	TTime endTime = TTime::GetCurrentTimeEx();
	TTimeSpan ts1(0,24,0,0);
	endTime += ts1;

	list<HitLog> RecordsList;
	list<HitLog>::iterator RecordsItem;

	QueryHitRecord("admin", beginTime, endTime, RecordsList);

	OutputDebugString("\n----------------QueryHitRecord Begin-------------------\n");
	for(RecordsItem=RecordsList.begin();RecordsItem!=RecordsList.end();RecordsItem++)
	{
		OutputDebugString(RecordsItem->sUserName.c_str());
		OutputDebugString("\n");
		OutputDebugString(RecordsItem->sHitPro.c_str());
		OutputDebugString("\n");
		OutputDebugString(RecordsItem->sHitFunc.c_str());
		OutputDebugString("\n");
		OutputDebugString(RecordsItem->sDesc.c_str());
		OutputDebugString("\n");
		string strTemp="";
		char buf[256]={""};
		itoa(RecordsItem->sHitFlag, buf, 10);
		strTemp = buf;
		OutputDebugString(strTemp.c_str());
		OutputDebugString("\n");
		char buf1[256]={""};
		itoa(RecordsItem->sHitInterval, buf1, 10);
		strTemp = buf1;
		OutputDebugString(strTemp.c_str());
		OutputDebugString("\n----------------------------\n");
	}
	OutputDebugString("\n----------------QueryHitRecord End-------------------\n");
*/
}
//保存IP地址和天数
void CGeneral::Save()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "general";
	LogItem.sHitFunc = "Save";
	LogItem.sDesc = strModifyDay;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}
	//验证IP地址和保存天数是否为空
	std::list<string> errorMsgList;
	bool bShowErr=false;
	if(pCheckBox->isChecked())
	{
		if(pIPEdit->text().empty())
		{
			errorMsgList.push_back(sErrIP);
			bShowErr=true;
		}
	}
	if(pDataEdit->text().empty())
	{
		errorMsgList.push_back(sErrDate);
		bShowErr=true;
	}
	else
	{
		//Jansion.zhou 2006-12-22
		string strHisSaveDate = pDataEdit->text();
		bool bNum = isNumeric(strHisSaveDate); 
		if(!bNum)
		{
			errorMsgList.push_back(sErrDate1);
			bShowErr=true;
		}
	}
	//Jansion.zhou 2006-12-22
	//pMainTable->ShowErrorMsg(errorMsgList);
	m_sFlexTable->ShowErrorMsg(errorMsgList);
	if(bShowErr==true)
	{	
		bEnd = true;	
		goto OPEnd;
	}		

	IPAddress pIPAddress;
	if(pCheckBox->isChecked())
		pIPAddress.iCheck=1;
	else
		pIPAddress.iCheck=0;
	pIPAddress.strIPAddress=pIPEdit->text();
	pIPAddress.strDate=pDataEdit->text();
	//写入ini文件
	WriteIniFileInt("IPCheck", "isCheck", pIPAddress.iCheck, "general.ini");
	WriteIniFileString("IPCheck", "IPAddress", pIPAddress.strIPAddress.c_str(), "general.ini");

	int SaveDate = atoi(pIPAddress.strDate.c_str());
	bool bDate = SetLogKeepDays(SaveDate);

	//隐藏错误提示信息
	//Jansion.zhou 2006-12-22
	//pMainTable->HideAllErrorMsg();
	m_sFlexTable->HideAllErrorMsg();

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strMainTitle);
   
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	//触发保存成功事件
	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += szSaveSucess;
	WebSession::js_af_up += "')";

}
//IP文本框是否可用
void CGeneral::ShowEdit()
{
	if(pCheckBox->isChecked())
		pIPEdit->enable();
	else
		pIPEdit->disable();
}
typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("General Set");
    CGeneral setform(app.root());
	setform.appSelf = &app;
	app.setBodyAttribute("class='workbody' ");
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