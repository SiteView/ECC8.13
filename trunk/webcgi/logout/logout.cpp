

#include "fcgi_stdio.h"
//#include <time.h>
#include <string.h>
#include <windows.h>


int main (int argc,char *argv[])
{

	HANDLE hevnt;
	char pidEventName[256];
	sprintf(pidEventName,"SiteView-Cgi-Event-%d",GetCurrentProcessId());	
	hevnt= CreateEvent(NULL,TRUE,FALSE,pidEventName);

	DWORD ret=WaitForSingleObject(hevnt,10000);
	ResetEvent(hevnt);

	if(FCGI_Accept()>=0)
	{
		int   nSvsid;
		char ** myenviron;
		char  wcookie[256];
		char *qrystr;
		char  *p;
		myenviron =FCGI_GetEnv();
		char myenviron1[4096]={0};
		for(int i=0 ;myenviron[i];++i)
		{
			strcpy(myenviron1,myenviron[i]);
			putenv(myenviron[i]);
		}

		qrystr=getenv("HTTP_COOKIE");
		if(qrystr)
		{
			if(strlen(qrystr)>0)
			{
				sprintf(wcookie,"%s",qrystr);
				p=strstr(wcookie,"svsid=");
				if(p!=NULL)
				{
					sscanf(p,"svsid=%d",&nSvsid);
				}
			}
		}


		printf("Content-type: text/html\r\n");
//		printf("Set-Cookie: svsid=%d\r\n" ,nSvsid   );
		printf("\r\n");
		printf("\r\n");
		printf("<SCRIPT LANGUAGE=\"JavaScript\">\n");
		printf("location.href=\"/fcgi-bin/treeview.exe?loginout\";location.href=\"/\";\n");
		printf("</SCRIPT>\n");

	}
}