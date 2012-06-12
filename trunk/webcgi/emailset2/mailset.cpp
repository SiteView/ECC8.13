
#include <time.h>

#include "MainForm.h"
#include "EmailSet.h"

#include <WApplication>
#include <WebSession.h>

string strListHeights, strListTitles, strListPans;

typedef void( *func)(int , char **);

void RandID(string &strID)
{
    unsigned int nPort = 0;
    unsigned int nMin  = 0x42;
    unsigned int nMax  = 0x5A;
    srand((unsigned)time( NULL ));
    char chID[12] = {0};
    for (int i = 0; i <sizeof(chID); i++)
    {
        nPort = rand();
        nPort = nPort | nMin;
        nPort = nPort & nMax;
        chID[i] = nPort;
    }
    chID[11] = '\0';
    strID = chID;
}

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

//添加客户端脚本变量
void AddJsParam(const std::string name, const std::string value,  WContainerWidget * parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}

void wmain1(int argc, char *argv[])
{
	
  WApplication app(argc, argv);
  app.setTitle("Email Set");

  new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
  new WText("<div id='view_panel' class='panel_view'>", app.root());

  CMainForm mainform(app.root());
  mainform.appSelf = &app;
  app.setBodyAttribute(" class='workbody'");

  new WText("</div>", app.root());

  AddJsParam("uistyle", "viewpanandlist", app.root());
  AddJsParam("fullstyle", "true", app.root());
  AddJsParam("bGeneral", "false", app.root());
  new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());

  app.exec();

}


int main(int argc, char * argv[])
{
    func p = wmain1;
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