////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#include <windows.h>
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"

#include "disableform.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void(*func)(int, char**);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const char * szMsg);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const string szMsg)
{
    PrintDebugString(szMsg.c_str());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const char* szMsg)
{
#ifdef WIN32
    OutputDebugString(szMsg);
    OutputDebugString("\n");
#endif
}

int getDisableOperate(const char* szQuery)
{
    int nType = 3;
    char *pPos= strstr(szQuery, "operatetype=");
    if(pPos)
    {
        char szType[2];
        sscanf(pPos, "operatetype= %[0-1]", szType);
        //PrintDebugString(pPos);
        nType = atoi(szType);
    }
    if(nType == 3)
        PrintDebugString("disable : dyn operate");
    return nType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getDisableType(const char * szQuery)
{
    int nType = -1;
    char *pPos = strstr(szQuery, "disabletype=");
    if(pPos)
    {
        int nLen = strlen(pPos);
        char * szType = new char[nLen];
        sscanf(pPos, "disabletype= %[0-2]", szType);
        nType = atoi(szType);
        delete []szType;
    }
    return nType;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getSVID(int nDisableType, const char *szQuery, string &szSVID)
{
    char *pPos = NULL;
    char * szTemp = NULL;
    pPos = strstr(szQuery, "disableid=");
    if(pPos)
    {
        int nLen = strlen(pPos);
        szTemp = new char[nLen];
        szTemp[0] = '\0';
        sscanf(pPos, "disableid= %[0-9,.]", szTemp);
        szSVID = szTemp;
        delete []szTemp;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void showDisableForm(int argc, char* argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Forbid_Allow_Monitor",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str()); //
    //new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", elementAt(nRow, 0));
    new WText("<div id='frame_loadBra' style='width:100%; height:100%; z-index:10000; " \
            "overflow:hidden; position:absolute; top:0px; left:0px; display:none;'><table " \
            "width=100% height=100% ID='Table1'><tr><td valign=middle align=center><img " \
            "src='../Images/loading.gif'></td></tr></table></div>", app.root());
    SVDisableForm disableform(app.root());
    disableform.setApp(&app);
    //string szAttr;
    //WPushButton * pQuitButton = new WPushButton("quit", app.root());
    //if(pQuitButton)
    //{
    //    WObject::connect(pQuitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    //    pQuitButton->hide();
    //    string szCmd = pQuitButton->getEncodeCmd("xclicked()");
    //    szAttr += "onbeforeunload =\"update('" + szCmd + "')\"";
    //}
    //app.setBodyAttribute(szAttr);
	disableform.appSelf = &app;
    app.exec();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    func pfunc = showDisableForm;
    if (argc == 1) 
    {
        //srand((unsigned)time( NULL ));
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end
