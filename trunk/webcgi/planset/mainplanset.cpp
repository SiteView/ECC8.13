
//#include <time.h>

#include "MainForm.h"
#include "planSet.h"

#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"


typedef void( *func)(int , char **);

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


void wmain1(int argc, char *argv[])
{
  WApplication app(argc, argv);

  //Jansion.zhou 2006-12-26
	////new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
	////new WText("<div id='view_panel' class='panel_view'>", app.root());
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
	new WText("<div id='view_panel' class='panel_view'>", app.root());


	CMainForm mainform(app.root());
	mainform.appSelf = &app;
	app.setBodyAttribute("class='workbody'");


	//Jansion.zhou 2006-12-26
	////new WText("</div>",app.root());
	////AddJsParam("uistyle", "viewpanandlist",app.root());
	////AddJsParam("fullstyle", "true",app.root());
	////new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());

	new WText("</div>", app.root());
	AddJsParam("uistyle", "viewpan", app.root());
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
        
        char buf[256];
        sprintf(buf,"23344334");
        WebSession s(buf, false);
		//s.setRefreshTime(1);
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