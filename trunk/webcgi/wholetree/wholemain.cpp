
#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WApplication"

#include <string>
#include <iostream>

using namespace std;

#include "wholeview.h"

#ifdef WIN32
#include <windows.h>
#endif

typedef void (*wtmain)(int, char**);

void PrintDebugString(const char* szErrmsg)
{
#ifdef WIN32
    OutputDebugString("wholetreeview: ");
    OutputDebugString(szErrmsg);
    OutputDebugString("\n");
#endif
}

void PrintDebugString(const string &szMsg)
{
    PrintDebugString(szMsg.c_str());
}


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

void showWholeview(int argc, char *argv[])
{
	WApplication app(argc, argv);

	new WText("<div id='view_panel' class='panel_view'>",app.root());


	app.setTitle("Siteview 7.0");
	CSVWholeview wholetree(app.root());


	new WText("</div>", app.root());

	AddJsParam("uistyle", "viewpan",app.root());
	AddJsParam("fullstyle", "true",app.root());
	AddJsParam("bGeneral", "false",app.root());
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());


	//app.setRefreshTime(3, wholetree.m_szGlobalEvent);
	app.exec();
}

int main(int argc, char *argv[])
{
    wtmain pMain = showWholeview;
    if (argc == 1) 
    {
        srand((unsigned)time( NULL ));
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
        WebSession s(buf, false);
        s.m_bReload = true;
        //s.setRefreshTime(3 * 60 * 1000);
        s.start(pMain);
		return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(pMain);
        return 1;
    }

    return 0;
}



