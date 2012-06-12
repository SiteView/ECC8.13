
#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WPushButton"
#include "../../kennel/svdb/svapi/svapi.h"

#include <string>
#include <iostream>

using namespace std;

#ifdef WIN32
#include <windows.h>
#endif

#include "devform.h"

typedef void (*func)(int , char**);


//添加客户端脚本变量
void AddJsParam(const std::string name, const std::string value,WContainerWidget *parent)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}

void testdevice(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Device_Test",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);


	//new WText("<div id='view_panel' class='panel_view'>", app.root());

	app.setTitle(title.c_str());
    //WApplication app(argc, argv);
    //app.setTitle("Test");
    SVDeviceTest devform(app.root());
    //"onbeforeunload = 'app.quit();'";
    //string szAttr = "class = \"winbg\"' ";
    app.setBodyAttribute("class = \"winbg\"");
    devform.setApplication(&app);

    //WPushButton * pQuitButton = new WPushButton("quit", app.root());
    //if(pQuitButton)
    //{
    //    WObject::connect(pQuitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    //    pQuitButton->hide();
    //    string szCmd = pQuitButton->getEncodeCmd("xclicked()");
    //    szAttr += "onbeforeunload =\"update('" + szCmd + "')\"";
    //}
    //app.setBodyAttribute(szAttr);
    //string szEvent = devform.getCmd();
    //if(!szEvent.empty())
    //    app.setRefreshTime(5, szEvent);
	devform.appSelf = &app;


	//new WText("</div>", app.root());

	//AddJsParam("uistyle", "viewpan", app.root());
	//AddJsParam("fullstyle", "true", app.root());
	//AddJsParam("bGeneral", "false", app.root());
	//new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());


    app.exec();
}

int main(int argc, char * argv[])
{
    func pfunc = testdevice;
    if (argc == 1) 
    {
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
        WebSession s(buf, false);
          s.start(pfunc);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(pfunc);
        return 1;
    }
}

