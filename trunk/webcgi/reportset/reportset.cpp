//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"

//#include <time.h>

#include "MainForm.h"
#include "configpage.h"
#include "AddReport.h"


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


typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
void reportset(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("Report Set");


    CSVMainForm setform(app.root());
	setform.appSelf = &app;

    //CSVreportset setform(app.root());
	/*
	if(setform.m_pfrAddPhone!=NULL)
	{
		if(setform.m_pfrAddPhone->pFrameTable!=NULL)
		{
			std::string  movestr;
			movestr ="";
			movestr+="<script language=\"javascript\">\n";
			movestr+="var _canResize = false;\n";
			movestr+="function resizeTable(){\n";
			movestr+="   if(_canResize){\n";
			movestr+="   var obj = document.all('";
			movestr+=setform.m_pfrAddPhone->pFrameTable->formName();
			movestr+="');\n";
			movestr+="   if(event.x < 50 || event.x>2450)\n";
			movestr+="        obj.rows[0].cells[1].style.pixelWidth = 5;\n";
			movestr+="   else{\n";
			movestr+="        obj.rows[0].cells[1].style.pixelWidth = 5;\n";
			movestr+="        obj.rows[0].cells[0].style.pixelWidth = event.x;\n";
			movestr+="       }\n";
			movestr+="   }\n";
			movestr+="}\n";
			movestr+="</script>\n";
			

			app.setBeforBodyStr(movestr);
			app.setBodyAttribute(" class='workbody'  onmousemove='resizeTable()' ");
			
		}
		else {
			app.setBodyAttribute(" class='workbody' ");
		}
	}
	*/


	app.setBodyAttribute("class='workbody' ");

    app.exec();
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    func p = reportset;
    if (argc == 1) 
    {
//        srand((unsigned)time( NULL ));
 //       int rand1 = rand();
  ////      char buf[256];
      //  itoa(rand1, buf, 10);
        //WebSession s(buf, false);
		 WebSession s("24", false);
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

