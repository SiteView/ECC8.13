/* port_driver.c */

#include <afxdisp.h>
#include <stdio.h>
#include <erl_driver.h>

typedef struct {
    ErlDrvPort port;
} example_data;

int foo(int x) {
  COleDateTime dt = COleDateTime::GetCurrentTime();
  COleDateTimeSpan span( 0, 0, 0, 0 );   
  while(span.GetSeconds() < 3)
  {
		span = COleDateTime::GetCurrentTime() - dt;
  }
  return x+1;
}

int bar(int y) {
  COleDateTime dt = COleDateTime::GetCurrentTime();
  COleDateTimeSpan span( 0, 0, 0, 0 );   
  while(span.GetSeconds() < 3)
  {
		span = COleDateTime::GetCurrentTime() - dt;
  }
  return y*2;
}

CString startc(int nID)
{
	CString strRes=_T("");
	CString strCommandLine=_T("");
	strCommandLine.Format(".\\cclient %d", nID);

	STARTUPINFO   startupInfo={0};   
	startupInfo.cb=sizeof(STARTUPINFO);   
	startupInfo.lpReserved=NULL;   
	startupInfo.lpReserved2=NULL;   
	startupInfo.lpDesktop=NULL;   
	startupInfo.dwFlags=0; 

	PROCESS_INFORMATION processinfo;
	
	int n = 0;
	while(!::CreateProcess(NULL,
		(LPSTR)(LPCTSTR)strCommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,
		//CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&startupInfo,
		&processinfo))
	{
		::Sleep(1000);
		n++;
		if(n==4)
			return strRes;
	}

	TCHAR szHostName[20];   
	DWORD dwSize   =   20;   
	GetComputerName(szHostName, &dwSize);   

	strRes.Format("c%d@%s", nID, szHostName);
	strRes.MakeLower();
	return strRes;
}

extern "C"
{
static ErlDrvData example_drv_start(ErlDrvPort port, char *buff)
{
    example_data* d = (example_data*)driver_alloc(sizeof(example_data));
    d->port = port;
    return (ErlDrvData)d;
}

static void example_drv_stop(ErlDrvData handle)
{
    driver_free((char*)handle);
}

static void example_drv_output(ErlDrvData handle, char *buff, int bufflen)
{
    example_data* d = (example_data*)handle;
    char fn = buff[0], arg = buff[1];
	CString strNodeName;
    if (fn == 3) 
		strNodeName = startc(arg);

	driver_output(d->port, (char*)(LPCTSTR)strNodeName, strNodeName.GetLength());
}

ErlDrvEntry example_driver_entry = {
    NULL,			/* F_PTR init, N/A */
    example_drv_start,		/* L_PTR start, called when port is opened */
    example_drv_stop,		/* F_PTR stop, called when port is closed */
    example_drv_output,		/* F_PTR output, called when erlang has sent */
    NULL,			/* F_PTR ready_input, called when input descriptor ready */
    NULL,			/* F_PTR ready_output, called when output descriptor ready */
    "example_drv",		/* char *driver_name, the argument to open_port */
    NULL,			/* F_PTR finish, called when unloaded */
    NULL,			/* F_PTR control, port_command callback */
    NULL,			/* F_PTR timeout, reserved */
    NULL			/* F_PTR outputv, reserved */
};

DRIVER_INIT(example_drv) /* must match name in driver_entry */
{
    return &example_driver_entry;
}
}

