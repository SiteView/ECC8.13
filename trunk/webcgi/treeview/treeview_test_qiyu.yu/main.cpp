/*
main.cpp
Need Library:
private library
svapi.lib:  SiteView ECC Database Access library, need svapi.dll.
usbdog.lib: SiteView ECC USB Dog Access library , need USB Dog driver.
svdes.lib:  SiteView ECC DES Encrypt library.

opensource library
libwt.lib:      WT library.
libfcgi.lib:    Fast CGI library.
*/

#include <time.h>

/*
Include STL Files 
Using namespace
*/
#include <iostream>
#include <string>

using namespace std;
/*
Include WT Files
*/
#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WText"


typedef void (*wtmain)(int, char**);

/*
*/
#include "mainview.h"
#include "popmenu.h"
/*
WT main function, show the main form.
*/

void showMainview(int argc, char *argv[])
{
    WApplication app(argc, argv);
    app.setTitle("SiteView ECC 7.0");

    new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());

    CEccPopMenu popmenu;
    new WText(popmenu.ShowMenu(), app.root());

    CEccMainView mainview(app.root());
    app.setBodyAttribute("oncontextmenu='return false;' onmousemove='resizeTable(\"" +
        mainview.getTreeTableName() + "\", \"" + mainview.m_szLeftScroll + "\");' scroll='no'");
    app.exec();
}

/*
main function, the program entry function
*/
int main(int argc, char *argv[])
{
    wtmain pMain = showMainview;
    if (argc == 1) 
    {
        srand((unsigned)time( NULL ));
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
        WebSession s(buf, false);
        s.m_bReload = true;
        s.start(pMain);
		return 1;
    }
    else
    {
        cout << "This program can not execute on command line." << endl;
        cout << "It's fastCGI program." << endl;
        cout << "Please access it in IE or firefox." << endl;

        return 1;
    }
}

