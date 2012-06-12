#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WebSession.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

#include "preview.h"

#include "../../kennel/svdb/svapi/svapi.h"

void AddTaskList(WComboBox * pTask = NULL)
{
    if(pTask)
    {
        list<string> lsTaskName;
        list<string>::iterator lsItem;

        if(GetAllTaskName(lsTaskName))
        {
            for(lsItem = lsTaskName.begin(); lsItem != lsTaskName.end(); lsItem ++)
            {
                string szName = (*lsItem);
                pTask->addItem(szName);
            }
        }
    }
}

void PrintDebugString(const char * szMsg)
{
#ifdef WIN32
    OutputDebugString("Preview : ");
    OutputDebugString(szMsg);
    OutputDebugString("\n");
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const string & szMsg)
{
    PrintDebugString(szMsg.c_str());
}

typedef void( *func)(int , char **);

void showMainform(int argc, char *argv[])
{
  WApplication app(argc, argv);
  app.setTitle("Preview");
  CSVPreview preview(app.root());
  preview.appSelf = &app;
  app.exec();
}

int main(int argc, char *argv[])
{
    func p = showMainform;
    if (argc == 1) 
    {
        srand((unsigned)time( NULL ));
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
        WebSession s(buf, false);
        s.m_bReload = true;
        s.start(p);
        return 1;
    }
    else
    {
        cout << "This is a fast cgi program, it doesn't support execute in command line." << endl;
    }
    return 0;
}

