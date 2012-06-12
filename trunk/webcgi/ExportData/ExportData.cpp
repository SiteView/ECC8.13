#include ".\exportdata.h"

/////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVButton.h"
////////////////////////////////////////
#include "DataTransfer_dll.h"
////////////////////////////////////////
#include "WApplication"
#include "WebSession.h"
#include "WText"
#include "WLineEdit"
#include "WImage"
#include "WComboBox"
#include "WCheckBox"
////////////////////////////////
#include <string>
#include <list>		
using namespace std;

CExportData::CExportData(WContainerWidget *parent): 
WContainerWidget(parent)
{
	loadString();
	initForm();
}

void CExportData::initForm()
{   char buf[256]={0};
string IniPath("\\data\\IniFile\\TransferToSQL.ini");
IniPath=GetSiteViewRootPath()+IniPath;
new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
m_pMainTable = new WSVMainTable(this,m_szMainTitle,true);
if(m_pMainTable)
{
	connect(m_pMainTable->pHelpImg, SIGNAL(clicked()), this, SLOT(ShowHideHelp()));

	//时间
	m_pTimeTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1,0), AlertSel ,m_szTimeTitle);	
	if(m_pTimeTable->GetContentTable() != NULL)
	{
		m_pTimeTable->InitTable();

		m_pTimeTable->AppendRows();
		if(GetPrivateProfileString("time","transtime","",buf,255,IniPath.c_str()))

		{
			m_pTime = new WLineEdit(buf, m_pTimeTable->AppendRowsContent(0, 0, 1, "时间", "时间", "时间"));
		}else
		{
			m_pTime = new WLineEdit("", m_pTimeTable->AppendRowsContent(0, 0, 1, "时间", "时间", "时间"));
		}
		m_pTime->resize(WLength(200, WLength::Pixel),WLength());
		m_pTime->setStyleClass("input_text");

		if(m_pTimeTable->GetActionTable()!=NULL)
		{
			WTable * pTbl = new WTable((WContainerWidget *)m_pTimeTable->GetActionTable()->elementAt(0, 1));

			WSVButton * btn = new WSVButton((WContainerWidget *)pTbl->elementAt(0, 0), m_szSave, "button_bg_m.png", "", false);

			connect(btn, SIGNAL(clicked()), this, SLOT(SaveTime()));
		}

		m_pTimeTable->ShowOrHideHelp();
		m_pTimeTable->HideAllErrorMsg();
	}

	//TPL
	m_pExportConfigTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(2,0), AlertSel ,m_szConfigTitle);	
	if(m_pExportConfigTable->GetContentTable() != NULL)
	{
		m_pExportConfigTable->InitTable();

		m_pExportConfigTable->AppendRows();

		m_pFileType = new WComboBox(m_pExportConfigTable->AppendRowsContent(0, 0, 1, m_szDataType, m_szDataTypeHelp, m_szDataTypeError));
		m_pFileType->resize(WLength(200, WLength::Pixel),WLength());
		m_pFileType->setStyleClass("input_text");
		m_pFileType->addItem(m_szDataTypeConfig);
		m_pFileType->addItem(m_szDataTypeData);
		int transType;
		transType=GetPrivateProfileInt("time","transtime",3600000,IniPath.c_str());
		if(transType!=3600000)
		{
			m_pFileType->setCurrentIndex(transType);
		}
		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sDriverName","",buf,255,IniPath.c_str()))
		{m_pDriver = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(0, 1, 1, m_szDriverName, m_szDriverHelp, m_szDriverError));}
		else
		{
			m_pDriver = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(0, 1, 1, m_szDriverName, m_szDriverHelp, m_szDriverError));

		}
		m_pDriver->resize(WLength(200, WLength::Pixel),WLength());
		m_pDriver->setStyleClass("input_text");

		m_pExportConfigTable->AppendRows();
		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sServerName","",buf,255,IniPath.c_str()))
		{
			m_pServerName = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(1, 0, 1, m_szServerName, m_szServerNameHelp, m_szServerNameError));
		}
		else
		{
			m_pServerName = new WLineEdit("", m_pExportConfigTable->AppendRowsContent(1, 0, 1, m_szServerName, m_szServerNameHelp, m_szServerNameError));
		}
		m_pServerName->resize(WLength(200, WLength::Pixel),WLength());
		m_pServerName->setStyleClass("input_text");



		m_pDBType = new WComboBox(m_pExportConfigTable->AppendRowsContent(1, 1, 1, m_szDBType, m_szDBTypeHelp, m_szDBTypeError));
		m_pDBType->resize(WLength(200, WLength::Pixel),WLength());
		m_pDBType->setStyleClass("input_text");
		connect(m_pDBType, SIGNAL(changed()), this, SLOT(ShowMac()));
		m_pDBType->addItem("MySQL");
		m_pDBType->addItem("Oracle");
		m_pDBType->addItem("SQL Server");
		transType=GetPrivateProfileInt("tranfer","dbType",3600000,IniPath.c_str());
		if(transType!=3600000)
		{
			m_pDBType->setCurrentIndex(transType);
		}

		m_pExportConfigTable->AppendRows();

		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sMacName","",buf,255,IniPath.c_str()))
		{
			m_pMacName = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(2, 0, 1, m_szServerUserName, m_szServerUserNameHelp, m_szServerUserNameError));
		}
		else{
			m_pMacName = new WLineEdit("", m_pExportConfigTable->AppendRowsContent(2, 0, 1, m_szServerUserName, m_szServerUserNameHelp, m_szServerUserNameError));
		}
		m_pMacName->resize(WLength(200, WLength::Pixel),WLength());
		m_pMacName->setStyleClass("input_text");
		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sMacPWD","",buf,255,IniPath.c_str()))
		{
			m_pMacPWD = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(2, 1, 1, m_szServerPWD, m_szServerPWDHelp, m_szServerPWDError));
		}
		else
		{m_pMacPWD = new WLineEdit("", m_pExportConfigTable->AppendRowsContent(2, 1, 1, m_szServerPWD, m_szServerPWDHelp, m_szServerPWDError));
		}
		m_pMacPWD->resize(WLength(200, WLength::Pixel),WLength());
		m_pMacPWD->setStyleClass("input_text");
		m_pMacPWD->setEchoMode(WLineEdit::Password);

		((WTable *)m_pExportConfigTable->m_pListRowTable[2])->hide();

		m_pExportConfigTable->AppendRows();
		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sUserName","",buf,255,IniPath.c_str()))
		{

			m_pUserName = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(3, 0, 1, m_szDBUserName, m_szDBUserNameHelp, m_szDBUserNameError));
		}else
		{m_pUserName = new WLineEdit("", m_pExportConfigTable->AppendRowsContent(3, 0, 1, m_szDBUserName, m_szDBUserNameHelp, m_szDBUserNameError));
		}
		m_pUserName->resize(WLength(200, WLength::Pixel),WLength());
		m_pUserName->setStyleClass("input_text");
		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sPWD","",buf,255,IniPath.c_str()))
		{m_pPWD = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(3, 1, 1, m_szDBPWD, m_szDBPWDHelp, m_szDBPWDError));}
		else
		{
			m_pPWD = new WLineEdit("", m_pExportConfigTable->AppendRowsContent(3, 1, 1, m_szDBPWD, m_szDBPWDHelp, m_szDBPWDError));
		}
		m_pPWD->resize(WLength(200, WLength::Pixel),WLength());
		m_pPWD->setStyleClass("input_text");
		m_pPWD->setEchoMode(WLineEdit::Password);

		m_pExportConfigTable->AppendRows();
		memset(buf,0,256);
		if(GetPrivateProfileString("tranfer","sDBName","",buf,255,IniPath.c_str()))
		{
			m_pDBName = new WLineEdit(buf, m_pExportConfigTable->AppendRowsContent(4, 0, 1, m_szDBName, m_szDBNameHelp, m_szDBNameError));

		}
		else
		{m_pDBName = new WLineEdit("", m_pExportConfigTable->AppendRowsContent(4, 0, 1, m_szDBName, m_szDBNameHelp, m_szDBNameError));}
		m_pDBName->resize(WLength(200, WLength::Pixel),WLength());
		m_pDBName->setStyleClass("input_text");

		if(m_pExportConfigTable->GetActionTable()!=NULL)
		{
			WTable * pTb2 = new WTable((WContainerWidget *)m_pExportConfigTable->GetActionTable()->elementAt(0, 1));

			WSVButton * btn2 = new WSVButton((WContainerWidget *)pTb2->elementAt(0, 0), m_szExport, "button_bg_m.png", "", false);
			connect(btn2, SIGNAL(clicked()), "showbar();", this, SLOT(ExportData()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}

		m_pExportConfigTable->ShowOrHideHelp();
		m_pExportConfigTable->HideAllErrorMsg();
	}
}
}
/*bool CExportData::InitTime(void)
{
string IniPath("\\data\\IniFile\\TransferToSQL.ini");
IniPath=GetSiteViewRootPath()+IniPath;
char buf[256]={0};
GetPrivateProfileString("time","transtime","",buf,255,IniPath);
//m_szTime=string("buf");

}

bool CExportData::InitExport(void)
{   string IniPath("\\data\\IniFile\\TransferToSQL.ini");
IniPath=GetSiteViewRootPath()+IniPath;

//g_timespan = ::GetPrivateProfileInt("time","transtime",3600000,strPath);

//g_twhat =
::GetPrivateProfileInt("tranfer","fType",2 ,strPath);
//if(g_twhat == 2)
{
//g_canrun = FALSE;
return FALSE;
}

//g_sqltype
= ::GetPrivateProfileInt("tranfer","sqltype",3,strPath);
//if(g_sqltype == 3)
{
//g_canrun = FALSE;
return FALSE;
}

char buf[256]={0};
::GetPrivateProfileString("tranfer","sDriverName","",buf,255,strPath);
if(strlen(buf)>1)// g_drivername = buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","sServerName","",buf,255,strPath);
if(strlen(buf)>1) //g_hostname=buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","sDBName","",buf,255,strPath);
if(strlen(buf)>1) //g_dbname=buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","sUserName","",buf,255,strPath);
if(strlen(buf)>1) //g_dbuser=buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","sPWD","",buf,255,strPath);
if(strlen(buf)>1) //g_dbpwd=buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","ExportDataLog","",buf,255,strPath);
if(strlen(buf)>1) //g_logfname=buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","sMacName","",buf,255,strPath);
if(strlen(buf)>1) //g_winuser=buf;

memset(buf,0,256);
::GetPrivateProfileString("tranfer","sMacPWD","",buf,255,strPath);
if(strlen(buf)>1) //g_winpwd=buf;

return TRUE;
}*/
void CExportData::SaveTime()
{
	string sTime = m_pTime->text();
	string IniPath("\\data\\IniFile\\TransferToSQL.ini");
	IniPath=GetSiteViewRootPath()+IniPath;

	WritePrivateProfileString("time","transtime",sTime.c_str() ,IniPath.c_str());

}

void CExportData::ShowMac()
{
	string szDBType = m_pDBType->currentText();
	if(m_pExportConfigTable)
	{
		if(szDBType == "SQL Server")
		{
			((WTable *)m_pExportConfigTable->m_pListRowTable[2])->show();
		}
		else
		{
			((WTable *)m_pExportConfigTable->m_pListRowTable[2])->hide();
		}
	}
}

void CExportData::ExportData()
{
	OutputDebugString("\n-----------ExportData Begin------------\n");

	m_pExportConfigTable->HideAllErrorMsg();	

	list<string> msgErrorList;
	msgErrorList.clear();

	string sfType = m_pFileType->currentText();	
	int fType;
	if(sfType == m_szDataTypeConfig)
	{
		fType = ALLCONFIG;
	}
	else if(sfType == m_szDataTypeData)
	{
		fType = MONITORDATA;
	}

	string sDriverName = m_pDriver->text();
	if(sDriverName == "")
	{
		msgErrorList.push_back(m_szDriverError);
	}

	string sServerName = m_pServerName->text();
	if(sServerName == "")
	{
		msgErrorList.push_back(m_szServerNameError);
	}

	string sdbType = m_pDBType->currentText();
	int dbType; 
	string sMacName = m_pMacName->text();
	string sMacPWD = m_pMacPWD->text();
	if(sdbType == "MySQL")
	{
		dbType = MYSQL;
	}
	else if(sdbType == "SQL Server")
	{
		dbType = SQLSERVER;
		if(sMacName == "")
		{
			msgErrorList.push_back(m_szServerUserNameError);
		}
		if(sMacPWD == "")
		{
			msgErrorList.push_back(m_szServerPWDError);
		}
	}
	else if(sdbType == "Oracle")
	{
		dbType = ORACLE;
	}

	string sDBName = m_pDBName->text();
	if(sDBName == "")
	{
		msgErrorList.push_back(m_szDBNameError);
	}

	string sUserName = m_pUserName->text();
	if(sUserName == "")
	{
		msgErrorList.push_back(m_szDBUserNameError);
	}

	string sPWD = m_pPWD->text();
	if(sPWD == "")
	{
		msgErrorList.push_back(m_szDBPWDError);
	}

	if(msgErrorList.size() > 0)
	{
		m_pExportConfigTable->ShowErrorMsg(msgErrorList);	
		WebSession::js_af_up = "hiddenbar();";
		return;
	}
	char temp[255];
	//OutputDebugString("-----------------------mytest-----------------");
	string IniPath("\\data\\IniFile\\TransferToSQL.ini");
	IniPath=GetSiteViewRootPath()+IniPath;

	char *temp_point=temp;
	temp_point=_itoa(fType,temp,10);
	WritePrivateProfileString("tranfer","fType", temp_point,IniPath.c_str());
	//ToCharArray() 
	WritePrivateProfileString("tranfer","sDriverName",sDriverName.c_str() ,IniPath.c_str());
	temp_point=_itoa(dbType,temp,10);
	WritePrivateProfileString("tranfer","dbType",temp_point ,IniPath.c_str());
	WritePrivateProfileString("tranfer","sServerName",sServerName.c_str() ,IniPath.c_str());
	WritePrivateProfileString("tranfer","sDBName",sDBName.c_str() ,IniPath.c_str());
	WritePrivateProfileString("tranfer","sUserName",sUserName.c_str(),IniPath.c_str());
	WritePrivateProfileString("tranfer","ExportDataLog","ExportDataLog.txt" ,IniPath.c_str());
	WritePrivateProfileString("tranfer","sMacName",sMacName.c_str() ,IniPath.c_str());
	WritePrivateProfileString("tranfer","sMacPWD",sMacPWD.c_str() ,IniPath.c_str());
	WritePrivateProfileString("tranfer","sPWD",sPWD.c_str() ,IniPath.c_str());


	bool bExport = DataTransfer(fType, sDriverName, dbType, sServerName, sDBName, sUserName, sPWD, "ExportDataLog.txt", sMacName, sMacPWD);


	//C:\SiteView\SiteView ECC\data\IniFile

	if(bExport)
	{
		WebSession::js_af_up = "hiddenbar();";
		WebSession::js_af_up += "alert(\'";
		WebSession::js_af_up += m_szExportSuccess;
		WebSession::js_af_up += "\')";
	}
	else
	{
		WebSession::js_af_up = "hiddenbar();";
		WebSession::js_af_up += "alert(\'";
		WebSession::js_af_up += m_szExportFail;
		WebSession::js_af_up += "\')";
	}
	OutputDebugString("\n-----------ExportData End------------\n");
}

void CExportData::ShowHideHelp()
{
	m_pTimeTable->ShowOrHideHelp();
	m_pExportConfigTable->ShowOrHideHelp();
	m_pExportDataTable->ShowOrHideHelp();
}

void CExportData::loadString()
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{   //FindNodeValue(ResNode,"IDS_Save_Fail",m_szSaveFail);  
			//FindNodeValue(ResNode,"IDS_Save_Success",m_szSaveSucess);  
			FindNodeValue(ResNode,"IDS_ExportData",m_szMainTitle);    
			FindNodeValue(ResNode,"IDS_TimeSetting",m_szTimeTitle);    
			FindNodeValue(ResNode,"IDS_ExportConfig",m_szConfigTitle);    
			FindNodeValue(ResNode,"IDS_ExportMonitorData",m_szDataTitle);    
			FindNodeValue(ResNode,"IDS_Save",m_szSave);    
			FindNodeValue(ResNode,"IDS_Export",m_szExport);    
			FindNodeValue(ResNode,"IDS_ExportDateType",m_szDataType);    
			FindNodeValue(ResNode,"IDS_ExportDateTypeHelp",m_szDataTypeHelp);    
			FindNodeValue(ResNode,"IDS_ExportDateTypeError",m_szDataTypeError);    
			FindNodeValue(ResNode,"IDS_ExportDataConfig",m_szDataTypeConfig);    
			FindNodeValue(ResNode,"IDS_ExportDataData",m_szDataTypeData);    
			FindNodeValue(ResNode,"IDS_DriverName",m_szDriverName);    
			FindNodeValue(ResNode,"IDS_DriverHelp",m_szDriverHelp);    
			FindNodeValue(ResNode,"IDS_DriverError",m_szDriverError);
			FindNodeValue(ResNode,"IDS_ServerName",m_szServerName);    
			FindNodeValue(ResNode,"IDS_ServerNameHelp",m_szServerNameHelp);    
			FindNodeValue(ResNode,"IDS_ServerNameError",m_szServerNameError);
			FindNodeValue(ResNode,"IDS_DBType",m_szDBType);    
			FindNodeValue(ResNode,"IDS_DBTypeHelp",m_szDBTypeHelp);    
			FindNodeValue(ResNode,"IDS_DBTypeError",m_szDBTypeError); 
			FindNodeValue(ResNode,"IDS_ServerUserName",m_szServerUserName);    
			FindNodeValue(ResNode,"IDS_ServerUserNameHelp",m_szServerUserNameHelp);    
			FindNodeValue(ResNode,"IDS_ServerUserNameError",m_szServerUserNameError); 
			FindNodeValue(ResNode,"IDS_ServerPWD",m_szServerPWD);    
			FindNodeValue(ResNode,"IDS_ServerPWDHelp",m_szServerPWDHelp);    
			FindNodeValue(ResNode,"IDS_ServerPWDError",m_szServerPWDError);  
			FindNodeValue(ResNode,"IDS_DBUserName",m_szDBUserName);    
			FindNodeValue(ResNode,"IDS_DBUserNameHelp",m_szDBUserNameHelp);    
			FindNodeValue(ResNode,"IDS_DBUserNameError",m_szDBUserNameError);  
			FindNodeValue(ResNode,"IDS_DBPWD",m_szDBPWD);    
			FindNodeValue(ResNode,"IDS_DBPWDHelp",m_szDBPWDHelp);    
			FindNodeValue(ResNode,"IDS_DBPWDError",m_szDBPWDError);   
			FindNodeValue(ResNode,"IDS_DBName",m_szDBName);    
			FindNodeValue(ResNode,"IDS_DBNameHelp",m_szDBNameHelp);    
			FindNodeValue(ResNode,"IDS_DBNameError",m_szDBNameError); 
			FindNodeValue(ResNode,"IDS_ExportSuccess",m_szExportSuccess); 
			FindNodeValue(ResNode,"IDS_ExportFail",m_szExportFail); 
		}
		CloseResource(objRes);
	}

}

CExportData::~CExportData(void)
{
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void usermain(int argc, char * argv[])
{			
	WApplication app(argc, argv);
	app.setTitle("Export Data");
	CExportData setform(app.root());
	app.setBodyAttribute("class='workbody' ");
	app.exec();
}
int main(int argc, char *argv[])
{
	func p = usermain;
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