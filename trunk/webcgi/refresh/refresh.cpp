#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WApplication"
#include "../../kennel/svdb/svapi/svapi.h"

#include "refreshform.h"

#include <string>

using namespace std;


#ifdef WIN32
#include <windows.h>
#endif

typedef void(*func)(int, char**);

void PrintDebugString(const char * szMsg);

void PrintDebugString(const string & szMsg)
{
    PrintDebugString(szMsg.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const char * szMsg)
{
#ifdef WIN32
    OutputDebugString(szMsg);
    OutputDebugString("\n");
#endif
}

WApplication *gMainApp = NULL;

void refreshmonitor(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Refresh_To_Get_Monitor_Status",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());	
    SVRefresh refreshform(app.root());
	refreshform.appSelf = &app;
    app.setBodyAttribute("class = 'winbg'");
    string szAttr = "class = \"winbg\"";
    app.setBodyAttribute(szAttr);
    gMainApp = &app;
    app.exec();
}

int main(int argc, char * argv[])
{
    func pfunc = refreshmonitor;
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