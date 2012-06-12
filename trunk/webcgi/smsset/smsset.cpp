//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"

#include <time.h>

#include "MainForm.h"
#include "configpage.h"
#include "WText"


unsigned int RandIndex()
{
    unsigned int nPort = 0;
    unsigned int nMin  = 0x4000;
    unsigned int nMax  = 0x7FFF;
    srand((unsigned)time( NULL ));
    nPort = rand();
    nPort = nPort | nMin;
    nPort = nPort & nMax;
//    cout << "Port: " << nPort << endl;
    return nPort;
}

void AddJsParam1 (const std::string name, const std::string value, WContainerWidget *parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}
typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void smsset(int argc, char * argv[])
{
    WApplication app(argc, argv);

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
	new WText("<div id='view_panel' class='panel_view'>", app.root());
    app.setTitle("Sms Set");
    CSVMainForm setform(app.root());
	//setform.appSelf = &app;
	//app.setBodyAttribute(" class='workbody' ");
	
	new WText("</div>", app.root());
	AddJsParam1("uistyle", "viewpanandlist", app.root());
	AddJsParam1("fullstyle", "true", app.root());
	AddJsParam1("bGeneral", "false", app.root());

	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());
    app.exec();
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    func p = smsset;
    if (argc == 1) 
    {
        srand((unsigned)time( NULL ));
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
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

//////////////////////////////////////////////////////////////////////////////////
// end file

