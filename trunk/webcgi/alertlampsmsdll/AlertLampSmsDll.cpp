/*************************************************
*  @file AlertLampSmsDll.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include "stdafx.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

enum
{
    OpenPortFailed = -1,//打开端口失败
    NoSetCenter = -2,//没有设置短信中心
    ShortSleepTime = 500
};

HANDLE hSerialPort;
string m_SmsCenterNum;


HANDLE OpenPort(const char* pPort,
				 			 int nBaudRate,
							 int nParity,
							 int nByteSize,
							 int nStopBits)
{
    HANDLE  hPort;
    DCB dcb;        // 串口控制块
    COMMTIMEOUTS timeouts = {    // 串口超时控制参数
        100,        // 读字符间隔超时时间: 100 ms
        1,          // 读操作时每字符的时间: 1 ms (n个字符总共为n ms)
        500,        // 基本的(额外的)读超时时间: 500 ms
        1,          // 写操作时每字符的时间: 1 ms (n个字符总共为n ms)
        100};       // 基本的(额外的)写超时时间: 100 ms
    
    hPort = CreateFile(pPort,    // 串口名称或设备路径
            GENERIC_READ | GENERIC_WRITE,    // 读写方式
            0,               // 共享方式：独占
            NULL,            // 默认的安全描述符
            OPEN_EXISTING,   // 创建方式
            0,               // 不需设置文件属性
            NULL);           // 不需参照模板文件
    
    if(hPort == INVALID_HANDLE_VALUE) 
    {
//        printf("Open Port Failed\n");
        return NULL;        // 打开串口失败
    }
    
    GetCommState(hPort, &dcb);        // 取DCB
    
    dcb.BaudRate = nBaudRate;
    dcb.ByteSize = nByteSize;
    dcb.Parity = nParity;
    dcb.StopBits = nStopBits;
    
    SetCommState(hPort, &dcb);        // 设置DCB    
    SetupComm(hPort, 4096, 1024);     // 设置输入输出缓冲区大小    
    SetCommTimeouts(hPort, &timeouts);    // 设置超时
    
    return hPort;
}

int ReadPort(void* pData,
			 int nLength)
{
    DWORD dwNumRead;    // 串口收到的数据长度    
    ReadFile(hSerialPort, pData, (DWORD)nLength, &dwNumRead, NULL);    
    return (int)dwNumRead;
}

/////////////////////////////////////////////////////////////////////////////////
// 函数：WritePort                                                             //
// 说明：写串口                                                                //
//      pData: 待写的数据缓冲区指针                                            //
//      nLength: 待写的数据长度                                                //
// 返回值：是否写成功                                                          //
/////////////////////////////////////////////////////////////////////////////////
BOOL WritePort(void* pData, int nLength)
{
    DWORD dwNumWrite;    // 串口发出的数据长度    
    return WriteFile(hSerialPort, pData, (DWORD)nLength, &dwNumWrite, NULL);
}



BOOL ClosePort(HANDLE hPort)
{
	return CloseHandle(hPort);
}

int InitPort(string strComName)
{
    hSerialPort = OpenPort(strComName.c_str(), CBR_9600,NOPARITY,8, ONESTOPBIT);   
    if(hSerialPort==NULL)
    {
		//MessageBox(NULL, "打开指定串口失败，请重新选择串口。","失败", MB_OK|MB_ICONWARNING);
        return -1;
    }
	string cmd = "AT+CSCA?\r";
	char ans[128] ;
	WritePort((void*)cmd.c_str(),strlen(cmd.c_str()));
	Sleep(ShortSleepTime);
	ReadPort(ans,128);
	string ansStr = ans;
	int cou;
	/*if((cou=ansStr.Find("+86")) != -1)
	{
	    m_SmsCenterNum = ansStr.Mid(cou+1,13);	
	}*/
	if((cou = ansStr.find("+86")) != -1)
	{
		m_SmsCenterNum = ansStr.substr(cou + 1, 13);
	}
	else
	{
		return -2;
	}
    return 0;
}

extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "报警灯";
	return 1;
}

extern "C" __declspec(dllexport) int run(char * source,
										 char * destination,
										 char * content)
{
	OutputDebugString("------------报警灯 function call()-------------------\n");
	int iRet = InitPort("Com3");

	char buf[256];// = Encoding.ASCII.GetBytes("#011001\r");
	strcpy(buf, "#011001\r");

	WritePort(buf, 8);
	
	Sleep(2000);
	
	//buf = Encoding.ASCII.GetBytes("#011000\r");
	memset(buf, 0, 256);
	strcpy(buf, "#011000\r");
	WritePort(buf, 8);
	
	ClosePort(hSerialPort);
	return 1;
}
