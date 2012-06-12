#include ".\ShowLog.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "..\svtable\MainTable.h"

#include "WImage"
#include "WTextArea"
#include "WApplication"
#include "websession.h"
#include "WCheckBox"
#include "WLineEdit"
#include  <fstream> 
#include  <iostream>

//
string  GetMonitorPropValue(string strId, string strPropName)
{
	string strTmp = "";

	//监测器id
	OBJECT objMonitor = GetMonitor(strId);
	if(objMonitor != INVALID_VALUE)
    {
        MAPNODE motnitornode = GetMonitorMainAttribNode(objMonitor);
        if(motnitornode != INVALID_VALUE)
        {
			FindNodeValue(motnitornode, strPropName, strTmp);
		}

		CloseMonitor(objMonitor);
	}

	return strTmp;
}

//根据monitorid获取父设备的名称
string  GetDeviceTitle(string strId)
{
	string strTmp = "";
	string strParentId = FindParentID(strId);

	//设备名称
	OBJECT objDevice = GetEntity(strParentId);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE devicenode = GetEntityMainAttribNode(objDevice);
        if(devicenode != INVALID_VALUE)
        {
			FindNodeValue(devicenode, "sv_name", strTmp);
		}
		
		CloseEntity(objDevice);
	}

	return strTmp;
}

CShowLog::CShowLog(WContainerWidget *parent):
WContainerWidget(parent)
{
	refreshCount=0;

	string strTemp1,strTemp2;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_LogShow",strMainTitle);
			FindNodeValue(ResNode,"IDS_ReadLogError",strTemp1);
			FindNodeValue(ResNode,"IDS_MonitorLogContext",strTemp2);
		}
		CloseResource(objRes);
	}
	
	
	char buf_tmp[4096]={0};
    int nSize =4095;


	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
	//char * tmpquery;
	//tmpquery = getenv( "QUERY_STRING");
	//if(tmpquery)
	//	strcpy(buf_tmp,tmpquery);
	if(buf_tmp != NULL)
	{
		std::string buf1 = buf_tmp;
		int pos = buf1.find("=", 0);
		querystr = buf1.substr(pos+1, buf1.size() - pos - 1);
	}
	
	strPath = "";
	strPath += GetSiteViewRootPath();
	strPath += "\\data\\Temp\\";
	strPath += querystr;
	strPath += ".txt";

	string   strTemp; 
	string   strOutput;

	try
	{
		ifstream  Input(strPath.c_str(), ios::out); 
			//获取日志行数
			nTotleLine = 0;
			nCurLine = 0;
			nPageLine = 100;

		if(Input.is_open())
		{
		
			while(!Input.eof())   
			{   
				nTotleLine++;
				getline(Input, strTemp , '\n');
				//puts(strTemp.c_str());
			}

			Input.close(); 
		}
		
		//获取日志最新100行数数据
		nStartLine = nTotleLine - nPageLine;

		//Input.open(strPath.c_str(), ios::out, 0);

		ifstream  Input1(strPath.c_str(), ios::out); 
		if(Input1.is_open())
		{
			while(!Input1.eof())   
			{   
				if(nTotleLine <= nPageLine)
				{
					getline(Input1, strTemp , '\n');
					strOutput += strTemp;
					strOutput += "\n";
				}
				else
				{
					if(nCurLine >=  nStartLine)
					{
						getline(Input1, strTemp , '\n');
						strOutput += strTemp;
						strOutput += "\n";
					}
					else
						getline(Input1, strTemp , '\n');
					
					nCurLine++;
				}
			}

			Input1.close(); 
		}

	}
	catch(...)
	{
		strOutput = strTemp1;
	}

	WTable * pContainTable = new WTable(this);
	
	//日志标题
	string strLogTitle = GetDeviceTitle(querystr);
	strLogTitle += ":";
	strLogTitle += GetMonitorPropValue(querystr, "sv_name");
	strLogTitle += strTemp2;


	pContainTable ->setStyleClass("t5");
	//pContainTable->setStyleClass("StatsTable");
	WText * pReportTitle = new WText(strLogTitle, (WContainerWidget*)pContainTable->elementAt(0, 0));
	pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	WFont font1;
	font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);


	//日志内容
	WTextArea * pStateTextArea = new WTextArea(strOutput, (WContainerWidget*)pContainTable->elementAt(1, 0));
	//pContainTable->elementAt(1, 0)->setStyleClass("t5");
	pContainTable->elementAt(1, 0)->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
	pStateTextArea->setRows(nPageLine);
	pStateTextArea->setColumns(60);
	pStateTextArea ->setStyleClass("testingresult2");
	//pStateTextArea->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
	pStateTextArea->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));

	strcpy(pStateTextArea->contextmenu_ , "readonly=\"readonly\"");

	//strPageTitle = "";
	//new WText("日志内容：", pMainTable->elementAt(4, 0));
	//new WText(strOutput, pMainTable->elementAt(2,0));

	//版权信息
	WText * bottomTitle = new WText("Copyright SiteView", pContainTable->elementAt(2, 0));
	bottomTitle ->decorationStyle().setFont(font1);
	pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
	bottomTitle->decorationStyle().setForegroundColor(Wt::blue);
}

CShowLog::~CShowLog(void)
{
		
}


//
void CShowLog::refresh()
{
	if(refreshCount != 0)
	{
		string strTemp1,strTemp2;
		OBJECT objRes=LoadResource("default", "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				FindNodeValue(ResNode,"IDS_ReadLogError",strTemp1);
				FindNodeValue(ResNode,"IDS_MonitorLogContext",strTemp2);
			}
			CloseResource(objRes);
		}
		this->clear();
		//pContainTable->clear();

		char buf_tmp[4096]={0};
		int nSize =4095;


		GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
		//char * tmpquery;
		//tmpquery = getenv( "QUERY_STRING");
		//if(tmpquery)
		//	strcpy(buf_tmp,tmpquery);
		if(buf_tmp != NULL)
		{
			std::string buf1 = buf_tmp;
			int pos = buf1.find("=", 0);
			querystr = buf1.substr(pos+1, buf1.size() - pos - 1);
		}
		
		strPath = "";
		strPath += GetSiteViewRootPath();
		strPath += "\\data\\Temp\\";
		strPath += querystr;
		strPath += ".txt";
		
		string   strTemp; 
		string   strOutput;
		
		
		try
		{
			ifstream  Input(strPath.c_str(), ios::out); 
			
			//获取日志行数
			nTotleLine = 0;
			nCurLine = 0;
			nPageLine = 100;

			if(Input.is_open())
			{
			
				while(!Input.eof())   
				{   
					nTotleLine++;
					getline(Input, strTemp , '\n');
					//puts(strTemp.c_str());
				}

				Input.close(); 
			}
			
			//获取日志最新100行数数据
			nStartLine = nTotleLine - nPageLine;

			//Input.open(strPath.c_str(), ios::out, 0);
			ifstream  Input1(strPath.c_str(), ios::out); 
			if(Input1.is_open())
			{
				while(!Input1.eof())   
				{   
					if(nTotleLine <= nPageLine)
					{
						getline(Input1, strTemp , '\n');
						strOutput += strTemp;
						strOutput += "\n";
					}
					else
					{
						if(nCurLine >=  nStartLine)
						{
							getline(Input1, strTemp , '\n');
							strOutput += strTemp;
							strOutput += "\n";
						}
						else
							getline(Input1, strTemp , '\n');
						
						nCurLine++;
					}
				}

				Input1.close(); 
			}

		}
		catch(...)
		{
			strOutput = strTemp1;
		}

		pContainTable = new WTable(this);
		
		//日志标题
		string strLogTitle = GetDeviceTitle(querystr);
		strLogTitle += ":";
		strLogTitle += GetMonitorPropValue(querystr, "sv_name");
		strLogTitle += strTemp2;

		pContainTable ->setStyleClass("t5");
		//pContainTable->setStyleClass("StatsTable");
		WText * pReportTitle = new WText(strLogTitle, (WContainerWidget*)pContainTable->elementAt(0, 0));
		pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
		WFont font1;
		font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
		pReportTitle ->decorationStyle().setFont(font1);


		//日志内容
		OutputDebugString(strOutput.c_str());
		WTextArea * pStateTextArea = new WTextArea(strOutput, (WContainerWidget*)pContainTable->elementAt(1, 0));
		//pContainTable->elementAt(1, 0)->setStyleClass("t5");
		pContainTable->elementAt(1, 0)->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
		pStateTextArea->setRows(nPageLine);
		pStateTextArea->setColumns(60);
		pStateTextArea ->setStyleClass("testingresult2");
		//pStateTextArea->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));
		pStateTextArea->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));

		strcpy(pStateTextArea->contextmenu_ , "readonly=\"readonly\"");

		//strPageTitle = "";
		//new WText("日志内容：", pMainTable->elementAt(4, 0));
		//new WText(strOutput, pMainTable->elementAt(2,0));

		//版权信息
		WText * bottomTitle = new WText("Copyright SiteView", pContainTable->elementAt(2, 0));
		bottomTitle ->decorationStyle().setFont(font1);
		pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
		bottomTitle->decorationStyle().setForegroundColor(Wt::blue);	
	}
	
	refreshCount = 1;
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("ShowLog");
    
	CShowLog showLog(app.root());
	showLog.appSelf = &app;
	app.setBodyAttribute("class='workbody' ");
    app.exec();
}

int main(int argc, char *argv[])
{
	func p = usermain;
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