//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"

#include <time.h>

#include "MainForm.h"
#include "configpage.h"
#include "addtopnreport.h"

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


typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
void reportset(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("Topn Report Set");
    CSVMainForm setform(app.root());
	setform.appSelf = &app;
    //CSVreportset setform(app.root());
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
			movestr+="   if(event.x < 150 || event.x>450)\n";
			movestr+="        obj.rows[0].cells[1].style.pixelWidth = 5;\n";
			movestr+="   else{\n";
			movestr+="        obj.rows[0].cells[1].style.pixelWidth = 5;\n";
			movestr+="        obj.rows[0].cells[0].style.pixelWidth = event.x;\n";
			movestr+="       }\n";
			movestr+="   }\n";
			movestr+="}\n";
			movestr+="</script>\n";
			

			app.setBeforBodyStr(movestr);
			string strBody = "onmousemove='resizeTable()' class='workbody'";
			app.setBodyAttribute(strBody.c_str());
			
		}
/*		else
		{
			app.setBodyAttribute("class='workbody' ");
		}
*/	}
	
    app.exec();
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    func p = reportset;
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

