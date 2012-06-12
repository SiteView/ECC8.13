#include "stdafx.h"
//#include <time.h>

#include "SendSMS.h"

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
			FindNodeValue(ResNode,"IDS_Sms_Serial_Port_Test",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
  //WApplication app(argc, argv);
  //app.setTitle("短信串口测试");
  app.setBodyAttribute("class='winbg' ");
  CSVSendSMS sendmail(app.root());
  OutputDebugString("---------显示部分成功--------\n");
  sendmail.appSelf = &app;
	OutputDebugString("---------显示部分成功1--------\n");
  app.exec();
}


int main(int argc, char * argv[])
{
    func p = wmain1;
    if (argc == 1) 
    {
//        srand((unsigned)time( NULL ));
//        int rand1 = rand();
//        char buf[256];
//        itoa(rand1, buf, 10);
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