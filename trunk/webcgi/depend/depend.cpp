#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WApplication"
#include "../../kennel/svdb/svapi/svapi.h"

#include <string>
#include <iostream>

using namespace std;

#ifdef WIN32
#include <windows.h>
#endif

#include "dependform.h"

//const char szTitle[] = "ÒÀ¿¿ÓÚ";

typedef void (*func)(int , char**);

void PrintDebugString(const char * szMsg);
void PrintDebugString(const string & szMsg)
{
    PrintDebugString(szMsg.c_str());
}

void PrintDebugString(const char* szMsg)
{
#ifdef WIN32
    OutputDebugString("Depend Tree: ");
    OutputDebugString(szMsg);
    OutputDebugString("\n");
#endif
}

void testdevice(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Depend_On",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
    SVDepend dependform(app.root());
	dependform.appSelf = &app;
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