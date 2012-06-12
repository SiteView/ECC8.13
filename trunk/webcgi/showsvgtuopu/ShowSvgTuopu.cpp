#include ".\ShowSvgTuopu.h"
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

CShowSvgTuopu::CShowSvgTuopu(WContainerWidget *parent):
WContainerWidget(parent)
{
	refreshCount=0;
	
	/*
	
	char buf_tmp[4096]={0};
    int nSize =4095;


	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
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

*/
	//new WText("<object type='image/svg+xml' name='omap' data='55.svg' width='100%' height='100%'></object>", this);
	new WText("<embed width='100%' height='100%' src='55.svg'>", this);
	//WTable * pContainTable = new WTable(this);
	//
	////日志标题
	//string strLogTitle = GetDeviceTitle(querystr);
	////strLogTitle += ":";
	//strLogTitle += GetMonitorPropValue(querystr, "sv_name");
	//strLogTitle += "拓扑图";


	//pContainTable ->setStyleClass("t5");
	////pContainTable->setStyleClass("StatsTable");
	//WText * pReportTitle = new WText(strLogTitle, (WContainerWidget*)pContainTable->elementAt(0, 0));
	//pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	//WFont font1;
	//font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
	//pReportTitle ->decorationStyle().setFont(font1);

	////new WText("<embed width='100%' height='100%' src='55.svg'>", (WContainerWidget*)pContainTable->elementAt(1, 0));
	////new WText("<object type='image/svg+xml' name='omap' data='.\55.svg' width='100%' height='100%'></object>", (WContainerWidget*)pContainTable->elementAt(1, 0));
	//
	//pContainTable->elementAt(1, 0)->resize(WLength(100,WLength::Percentage), WLength(100,WLength::Percentage));

	////日志内容
	////strPageTitle = "";
	////new WText("日志内容：", pMainTable->elementAt(4, 0));
	////new WText(strOutput, pMainTable->elementAt(2,0));

	////版权信息
	//WText * bottomTitle = new WText("Copyright SiteView", pContainTable->elementAt(2, 0));
	//bottomTitle ->decorationStyle().setFont(font1);
	//pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
	//bottomTitle->decorationStyle().setForegroundColor(Wt::blue);
}

CShowSvgTuopu::~CShowSvgTuopu(void)
{
		
}


//
void CShowSvgTuopu::refresh()
{
	if(refreshCount != 0)
	{

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
    
	CShowSvgTuopu showLog(app.root());
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