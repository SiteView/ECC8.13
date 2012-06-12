// StartC.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <erl_driver.h>

typedef struct {
    ErlDrvPort port;
} startc_data;

CString startc(int nID)
{
	CString strRes=_T("");
	CString strCommandLine=_T("");
	strCommandLine.Format(".\\monitorcall %d", nID);

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
		//CREATE_NO_WINDOW,
		CREATE_NEW_CONSOLE,
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
static ErlDrvData startc_drv_start(ErlDrvPort port, char *buff)
{
    startc_data* d = (startc_data*)driver_alloc(sizeof(startc_data));
    d->port = port;
    return (ErlDrvData)d;
}

static void startc_drv_stop(ErlDrvData handle)
{
    driver_free((char*)handle);
}

static void startc_drv_output(ErlDrvData handle, char *buff, int bufflen)
{
    startc_data* d = (startc_data*)handle;
 	CString strNodeName;
 	strNodeName = startc(atoi(buff));

	driver_output(d->port, (char*)(LPCTSTR)strNodeName, strNodeName.GetLength());
}

ErlDrvEntry startc_driver_entry = {
    NULL,			/* F_PTR init, N/A */
    startc_drv_start,		/* L_PTR start, called when port is opened */
    startc_drv_stop,		/* F_PTR stop, called when port is closed */
    startc_drv_output,		/* F_PTR output, called when erlang has sent */
    NULL,			/* F_PTR ready_input, called when input descriptor ready */
    NULL,			/* F_PTR ready_output, called when output descriptor ready */
    "startc",		/* char *driver_name, the argument to open_port */
    NULL,			/* F_PTR finish, called when unloaded */
    NULL,			/* F_PTR control, port_command callback */
    NULL,			/* F_PTR timeout, reserved */
    NULL			/* F_PTR outputv, reserved */
};

DRIVER_INIT(startc_drv) /* must match name in driver_entry */
{
    return &startc_driver_entry;
}
}

