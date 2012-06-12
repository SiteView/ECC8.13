#include ".\about.h"
#include "../../kennel/svdb/svapi/svapi.h"

#include "..\svtable\MainTable.h"
#include "WApplication"
#include "websession.h"
#include "WText"
#include "WTable"
#include "WImage"
#include <WPushButton>
#include <vector>

CAbout::CAbout(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			string ResProductName,ResProductVersion,ResProductCopy,ResProductWel,ResProductCom,ResProductServ;
			
			FindNodeValue(ResNode,"IDS_Product_Name",ResProductName);
			FindNodeValue(ResNode,"IDS_Product_Version",ResProductVersion);
			FindNodeValue(ResNode,"IDS_Product_Copyright",ResProductCopy);
			FindNodeValue(ResNode,"IDS_Product_Welcome",ResProductWel);
			FindNodeValue(ResNode,"IDS_Product_Company",ResProductCom);
			FindNodeValue(ResNode,"IDS_Product_Service",ResProductServ);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);

			strName="<p>";
			strName += ResProductName;
			strName += "<br>";
			strTempVer = ResProductVersion;
			strCopyRight = ResProductCopy;

			strWelcom = ResProductWel;

			strSite = ResProductCom;

			strOther = ResProductServ;	
				

		}

//		SubmitResource(objRes);
		CloseResource(objRes);
	}

	refreshCount = 0;
	ShowMainTable();
}

void CAbout::ShowMainTable()
{
	
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	pUserTable = new WTable(this);
	pUserTable->setStyleClass("about_panel");
	strVersion = GetIniFileString("version", "version", "",  "general.ini");
	string strVer = strTempVer;
	
	strVer += strVersion;
	strTotal= strVer + "<br>" +strCopyRight;//+ strWelcom+ strSite+ strOther;

	pTotalText = new WText(strVer,pUserTable->elementAt(0,0));
	pUserTable->elementAt(0,0)->setStyleClass("about_bg");
	pUserTable->elementAt(1,0)->setStyleClass("panel");
	WTable *table = new WTable(pUserTable->elementAt(1,0));
	strTotal = strCopyRight ;
	new WText(strTotal,table->elementAt(0,0));
	table->elementAt(0,0)->setStyleClass("about_text1");
	table->elementAt(1,0)->setStyleClass("about_text2");
	strTotal =  strWelcom + "<br>"+strSite +"<br>"+ strOther;//zzzzzzzzzzzzzzzzzz
	new WText(strTotal,table->elementAt(1,0));
	new WText("&nbsp;", (WContainerWidget *)pUserTable->elementAt(0, 0));

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)pUserTable->elementAt(0, 0));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;", (WContainerWidget *)pUserTable->elementAt(0, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)pUserTable->elementAt(0, 0));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	bTrans = 1;
	if(bTrans == 1000000000000)  
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}
}
void CAbout::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/about.exe?'\",1250);  ";
	appSelf->quit();
}
void CAbout::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "aboutRes";
	WebSession::js_af_up += "')";
}

void CAbout::refresh()
{
	if(refreshCount != 0)
	{
		strVersion = GetIniFileString("version", "version", "",  "general.ini");
		string strVer = strTempVer;
	//	strVer += "&nbsp;";
		strVer += strVersion;
		strVer += "<br>";

		strTotal= "<br><br><br><br><br><br><br><br>" + strVer+"<br>" + strCopyRight+"<br>"+ strWelcom+ "<br>"+strSite+ strOther;
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
	}
	refreshCount = 1;
}
CAbout::~CAbout(void)
{
}
typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_About_Us",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
    CAbout setform(app.root());
	setform.appSelf = &app;
    app.exec();
}

int main(int argc, char *argv[])
{
    func p = usermain;
    //WriteRightTpl();
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

