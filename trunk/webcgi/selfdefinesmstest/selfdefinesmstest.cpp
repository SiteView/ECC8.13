#include "stdafx.h"
//#include <time.h>

#include "selfdefineSendSMS.h"

#include <WApplication>
#include <WebSession.h>

#include "../../kennel/svdb/svapi/svapi.h"

typedef void( *func)(int , char **);


void wmain1(int argc, char *argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_SelfSmsSerialPortTest",title);
		CloseResource(objRes);
	}
//	title = "自定义短信接口测试";
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
  //WApplication app(argc, argv);
  //app.setTitle("短信串口测试");
  app.setBodyAttribute("class='winbg' ");
  CSVSelfDefineSendSMS sendmail(app.root());
  sendmail.appSelf = &app;

  app.exec();
}


int main(int argc, char * argv[])
{
    func p = wmain1;
    if (argc == 1) 
    {
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