#include ".\backuprestore.h"

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
///////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVButton.h"
////////////////////////////////////////
#include <winbase.h>
#include "../base/OperateLog.h"
////////////////////////////////////////
#include "WApplication"
#include "WebSession.h"
#include "WText"
#include "WLineEdit"
#include "WCheckBox"
#include "WImage"
#include "WFileUpload"
////////////////////////////////
#include <string>
#include <list>
using namespace std;
using namespace svutil;


CBackupRestore::CBackupRestore(WContainerWidget *parent): 
	WContainerWidget(parent)
{
	loadString();
	initForm();
}

void CBackupRestore::initForm()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	m_pMainTable = new WSVMainTable(this,m_szMainTitile,true);
	if(m_pMainTable)
	{
		connect(m_pMainTable->pHelpImg, SIGNAL(clicked()), this, SLOT(ShowHideHelp()));

		//备份	
		m_pBackupTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1,0), AlertSel ,m_szBackupData);	
		WTable * mContent = m_pBackupTable->GetContentTable();
		if(mContent != NULL)
		{
			m_pBackupTable->InitTable();

			m_pBackupTable->AppendRows();

			TTime timer=TTime::GetCurrentTimeEx();
			string bName = "SiteViewECC-";
			char buf[100]={0};
			sprintf(buf,"%d-%02d-%02d", timer.GetYear(), timer.GetMonth(), timer.GetDay());
			bName += buf;

			m_pBackFileName = new WLineEdit(bName, m_pBackupTable->AppendRowsContent(0, 0, 1, m_szBackupName, m_szBackupHelp, m_szBackupError));
			m_pBackFileName->setStyleClass("input_text");
			m_pBackFileName->resize(WLength(200, WLength::Pixel),WLength());

			if(m_pBackupTable->GetActionTable()!=NULL)
			{
				WTable * pTbl = new WTable((WContainerWidget *)m_pBackupTable->GetActionTable()->elementAt(0, 1));

				WSVButton * btn = new WSVButton((WContainerWidget *)pTbl->elementAt(0, 0), m_szConfigFile, "button_bg_m.png", "", false);
				connect(btn, SIGNAL(clicked()), "showbar();", this, SLOT(Backup()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);

				WSVButton * btn1 = new WSVButton((WContainerWidget *)pTbl->elementAt(0, 1), m_szMonitorData, "button_bg_m.png", "", false);
				connect(btn1, SIGNAL(clicked()), "showbar();", this, SLOT(BackupData()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
			}

			m_pBackupTable->ShowOrHideHelp();
			m_pBackupTable->HideAllErrorMsg();
		}
		
		//恢复	
		m_pRestoreTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(2,0), AlertSel ,m_szRestoreData);	
		if(m_pRestoreTable->GetContentTable() != NULL)
		{
			m_pRestoreTable->InitTable();

			m_pRestoreTable->AppendRows();

			m_pFile = new WFileUpload((WContainerWidget *)m_pRestoreTable->AppendRowsContent(0, 0, 1, m_szRestoreName, m_szRestoreHelp, m_szRestoreError));
			if(m_pFile)
			{
				connect(m_pFile, SIGNAL(newFileUploaded()), this, SLOT(GetFileName()));
				m_pFile->setStyleClass("input_text_400");
			}

			m_pRestoreTable->AppendRows();

			m_pHideEdit = new WLineEdit("", (WContainerWidget *)m_pRestoreTable->AppendRowsContent(1, 0, 1, "", "", ""));
			m_pHideEdit->hide();

			if(m_pRestoreTable->GetActionTable()!=NULL)
			{
				WTable * pTbl = new WTable((WContainerWidget *)m_pRestoreTable->GetActionTable()->elementAt(0, 1));

				WSVButton * btn = new WSVButton((WContainerWidget *)pTbl->elementAt(0, 0), m_szRestore, "button_bg_m.png", "", false);
				connect(btn, SIGNAL(clicked()), this, SLOT(Restore()));

				m_pBtnHide = new WSVButton((WContainerWidget *)pTbl->elementAt(1, 0), "Hide", "button_bg_m.png", "", false);
				m_pBtnHide->hide();
				connect(m_pBtnHide, SIGNAL(clicked()), this, SLOT(trueRestore()));
			}

			m_pRestoreTable->ShowOrHideHelp();
			m_pRestoreTable->HideAllErrorMsg();
		}
	}
}

void CBackupRestore::ShowHideHelp()
{
	m_pBackupTable->ShowOrHideHelp();
	m_pRestoreTable->ShowOrHideHelp();
}

void CBackupRestore::Backup()
{
	OutputDebugString("-----------Begin Backup Config---------------\n");

	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "BackupRestore";
	LogItem.sHitFunc = "Backup";
	LogItem.sDesc = m_szConfigFile;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	m_pBackupTable->HideAllErrorMsg();

	list<string> msgErrorList;
	msgErrorList.clear();

	string sName = m_pBackFileName->text();
	sName += "-Config";
	if(sName == "")
	{
		msgErrorList.push_back(m_szBackupError);
	}

	if(msgErrorList.size() >0)
	{
		m_pBackupTable->ShowErrorMsg(msgErrorList);	
		WebSession::js_af_up = "hiddenbar();";
		bEnd = true;	
		goto OPEnd;
	}

	char * argv[7];
	string ziptempstr;

	argv[0] = "zipfile";
	ziptempstr = argv[0];	
	ziptempstr += "  ";

	argv[1] = "-f";
	ziptempstr += argv[1];
	ziptempstr += "  ";

	argv[2] = (char*)malloc(160);
	memset(argv[2], 0, 160);					
	string szPath = "..\\htdocs\\backup\\config\\";
	strcpy(argv[2], szPath.c_str());
	strcat(argv[2], sName.c_str());
	strcat(argv[2], ".zip");
	ziptempstr += argv[2];
	ziptempstr += "  ";

	argv[3] = "-a";
	ziptempstr += argv[3];
	ziptempstr += "  ";

	argv[4] = "..\\data\\*.data";
	ziptempstr += argv[4];
	ziptempstr += "  ";

	argv[5] = "..\\data\\*.ini";
	ziptempstr += argv[5];
	ziptempstr += "  ";

	argv[6] = "-re";
	ziptempstr += argv[6];

	OutputDebugString(ziptempstr.c_str());

	main1(7, argv);

	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv[4]);
	free(argv[5]);
	free(argv[6]);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	WebSession::js_af_up = "hiddenbar();";
	WebSession::js_af_up += "showDownload('<a href=/backup/config/";
	WebSession::js_af_up += sName;
	WebSession::js_af_up +=	".zip>";
	WebSession::js_af_up += sName;
	WebSession::js_af_up += ".zip</a>','";
	WebSession::js_af_up += m_szDownLoad;
	WebSession::js_af_up += "','";
	WebSession::js_af_up += m_szConfirm;
	WebSession::js_af_up += "')";

	OutputDebugString("\n-----------End Backup Config-----------------\n");
}

void CBackupRestore::BackupData()
{
	OutputDebugString("\n-----------Begin Backup Data---------------\n");

	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "BackupRestore";
	LogItem.sHitFunc = "BackupData";
	LogItem.sDesc = m_szMonitorData;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	m_pBackupTable->HideAllErrorMsg();

	list<string> msgErrorList;
	msgErrorList.clear();

	string sName = m_pBackFileName->text();
	sName += "-Data";
	if(sName == "")
	{
		msgErrorList.push_back(m_szBackupError);
	}

	if(msgErrorList.size() >0)
	{
		m_pBackupTable->ShowErrorMsg(msgErrorList);	
		WebSession::js_af_up = "hiddenbar();";
		bEnd = true;	
		goto OPEnd;
	}

	char * argv[7];
	string ziptempstr;

	argv[0] = "zipfile";
	ziptempstr = argv[0];	
	ziptempstr += "  ";

	argv[1] = "-f";
	ziptempstr += argv[1];
	ziptempstr += "  ";

	argv[2] = (char*)malloc(160);
	memset(argv[2], 0, 160);					
	string szPath = "..\\htdocs\\backup\\data\\";
	strcpy(argv[2], szPath.c_str());
	strcat(argv[2], sName.c_str());
	strcat(argv[2], ".zip");
	ziptempstr += argv[2];
	ziptempstr += "  ";

	argv[3] = "-a";
	ziptempstr += argv[3];
	ziptempstr += "  ";

	argv[4] = "..\\data\\SiteViewLog_data_00.db";
	ziptempstr += argv[4];
	ziptempstr += "  ";

	argv[5] = "..\\data\\SiteViewLog_head_00.db";
	ziptempstr += argv[5];
	ziptempstr += "  ";

	argv[6] = "-re";
	ziptempstr += argv[6];

	OutputDebugString(ziptempstr.c_str());

	main1(7, argv);

	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv[4]);
	free(argv[5]);
	free(argv[6]);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	WebSession::js_af_up = "hiddenbar();";
	WebSession::js_af_up += "showDownload('<a href=/backup/data/";
	WebSession::js_af_up += sName;
	WebSession::js_af_up +=	".zip>";
	WebSession::js_af_up += sName;
	WebSession::js_af_up += ".zip</a>','";
	WebSession::js_af_up += m_szDownLoad;
	WebSession::js_af_up += "','";
	WebSession::js_af_up += m_szConfirm;
	WebSession::js_af_up += "')";

	OutputDebugString("\n-----------End Backup Data-----------------\n");
}

void CBackupRestore::Restore()
{
	m_pRestoreTable->HideAllErrorMsg();

	if(m_pBtnHide)
	{
		string strDelDes = m_pBtnHide->getEncodeCmd("xclicked()") ;
		if(!strDelDes.empty())
		{
			strDelDes = "showbar();_DataRestore(\"" + m_pFile->formName() + "\",\"" + m_pHideEdit->formName() + "\",\"" + m_szAffirmRestore + "\",\"" + m_szButNum + "\",\"" + m_szButMatch + "\",\"" + strDelDes + "\");"; 
			WebSession::js_af_up = strDelDes;							
		}					
	}
}

void CBackupRestore::trueRestore()
{
	OutputDebugString("\n-----------Begin Restore---------------\n");
	OutputDebugString("\n--------------- Backup Begin------------------\n");

	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "BackupRestore";
	LogItem.sHitFunc = "trueRestore";
	LogItem.sDesc = m_szRes;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd - dcalBegin);
		return;
	}

	string sName = m_pHideEdit->text();
	if(sName == "")
	{
		list<string> msgErrorList;
		msgErrorList.push_back(m_szRestoreError);
        m_pRestoreTable->ShowErrorMsg(msgErrorList);	
		WebSession::js_af_up = "hiddenbar();";
		bEnd = true;	
		goto OPEnd;
	}

	TTime timer=TTime::GetCurrentTimeEx();
	string bName = "SiteViewECC-ALL-";
	char buf[100]={0};
	sprintf(buf,"%d-%02d-%02d", timer.GetYear(), timer.GetMonth(), timer.GetDay());
	bName += buf;

	//压缩备份
	char * argv1[6];
	string ziptempstr1;

	argv1[0] = "zipfile";
	ziptempstr1 = argv1[0];	
	ziptempstr1 += "  ";

	argv1[1] = "-f";
	ziptempstr1 += argv1[1];
	ziptempstr1 += "  ";

	argv1[2] = (char*)malloc(160);
	memset(argv1[2], 0, 160);					
	string szPath = "..\\htdocs\\backup\\all\\";
	strcpy(argv1[2], szPath.c_str());
	strcat(argv1[2], bName.c_str());
	strcat(argv1[2], ".zip");
	ziptempstr1 += argv1[2];
	ziptempstr1 += "  ";

	argv1[3] = "-a";
	ziptempstr1 += argv1[3];
	ziptempstr1 += "  ";

	argv1[4] = "..\\data\\*.*";
	ziptempstr1 += argv1[4];
	ziptempstr1 += "  ";

	argv1[5] = "-re";
	ziptempstr1 += argv1[5];

	main1(6, argv1);

	free(argv1[0]);
	free(argv1[1]);
	free(argv1[2]);
	free(argv1[3]);
	free(argv1[4]);
	free(argv1[5]);

	OutputDebugString(ziptempstr1.c_str());
	OutputDebugString("\n--------------- Backup End------------------\n");

	//解压覆盖
	char * argv[6];
	string ziptempstr;

	argv[0] = "zipfile";
	ziptempstr = argv[0];	
	ziptempstr += "  ";

	argv[1] = "-f";
	ziptempstr += argv[1];
	ziptempstr += "  ";

	argv[2] = (char*)malloc(160);
	memset(argv[2], 0, 160);	
	strcpy(argv[2], sName.c_str());
	ziptempstr += argv[2];
	ziptempstr += "  ";

	argv[3] = "-xp";
	ziptempstr += argv[3];
	ziptempstr += "  ";

	string szReportPath = GetSiteViewRootPath();
	argv[4] = (char*)malloc(160);
	memset(argv[4], 0, 160);					
	strcpy(argv[4], szReportPath.c_str());
	strcat(argv[4], "\\data");
	ziptempstr += argv[4];
	ziptempstr += "  ";

	argv[5] = "-xa";
	ziptempstr += argv[5];

	main1(6, argv);

	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv[4]);
	free(argv[5]);

	OutputDebugString("\n--------------- Restore ------------------\n");
	OutputDebugString(ziptempstr.c_str());

	//调用Restore.bat重启SVDB等服务
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPTSTR szCmdline=_T("..\\fcgi-bin\\Restore.bat");

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if( CreateProcess(szCmdline, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
	{
		WebSession::js_af_up = "hiddenbar();";
		WebSession::js_af_up += "alert('";
		WebSession::js_af_up += m_szRestoreSucc;
		WebSession::js_af_up += "')";

		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}


	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);

	OutputDebugString("\n-----------End Restore-----------------\n");

	/*UINT uReturn = WinExec("..\\fcgi-bin\\Restore.bat",SW_HIDE);	
	if(uReturn>31)
	{
		WebSession::js_af_up = "alert('";
		WebSession::js_af_up += m_szRestoreSucc;
		WebSession::js_af_up += "')";
	}*/
}

void CBackupRestore::loadString()
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_BackupRestore",m_szMainTitile);    
			FindNodeValue(ResNode,"IDS_BackupData",m_szBackupData);    
			FindNodeValue(ResNode,"IDS_RestoreData",m_szRestoreData);    
			FindNodeValue(ResNode,"IDS_BackupFileName",m_szBackupName);    
			FindNodeValue(ResNode,"IDS_BackupHelp",m_szBackupHelp);    
			FindNodeValue(ResNode,"IDS_BackupError",m_szBackupError);    
			FindNodeValue(ResNode,"IDS_RetoreLabel",m_szRes);   
			FindNodeValue(ResNode,"IDS_Restore1",m_szRestore);   
			FindNodeValue(ResNode,"IDS_BackupFile",m_szRestoreName);    
			FindNodeValue(ResNode,"IDS_BackupFileHelp",m_szRestoreHelp);    
			FindNodeValue(ResNode,"IDS_BackupFileError",m_szRestoreError);    
			FindNodeValue(ResNode,"IDS_ConfirmCancel",m_szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",m_szButMatch);
			FindNodeValue(ResNode,"IDS_AffirmRestore",m_szAffirmRestore);
			FindNodeValue(ResNode,"IDS_RestoreSucc",m_szRestoreSucc);
			FindNodeValue(ResNode,"IDS_DownloadList", m_szDownLoad);
			FindNodeValue(ResNode,"IDS_Close", m_szConfirm);
			FindNodeValue(ResNode,"IDS_ConfigFile", m_szConfigFile);
			FindNodeValue(ResNode,"IDS_MonitorData", m_szMonitorData);
		}
		CloseResource(objRes);
	}
}

CBackupRestore::~CBackupRestore(void)
{
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void usermain(int argc, char * argv[])
{			
    WApplication app(argc, argv);
	app.setTitle("Backup and Restore Data");
 	CBackupRestore setform(app.root());
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