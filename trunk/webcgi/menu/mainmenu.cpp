#include "svmenu.h"
#include "WApplication"
#include "WTable"
#include "WWidget"

#include "WebSession.h"

#ifdef  WIN32

typedef void (  *fun)(int , char **);

void   wmain1(int argc, char **argv)
{
	
	WApplication appl(argc, argv);
	appl.setTitle("ÏµÍ³²Ëµ¥");

	WTable *top = new WTable(appl.root());
	top->setStyleClass("menu_bg");
	top->elementAt(0,0)->setVerticalAlignment(WWidget::AlignTop);
	CSVMainMenu s(top->elementAt(0,0));
	appl.exec();
}

int main(int argc, char *argv[])
{
	
	
	fun p = wmain1;
	
	if (argc == 1) 
	{
		
		
		int rand1 = rand();
		char buf[256];
		itoa(rand1, buf, 10);
		WebSession s(buf, false);
		
		s.start(p);
		return 1;
		
		
	}else
	{
		FCGI_Accept();
		WebSession s("DEBUG", true);
		s.start(p);
		return 1;
	}
	
	return 0;
	
}

#else

#endif
