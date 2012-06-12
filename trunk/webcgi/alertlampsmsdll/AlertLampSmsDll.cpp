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
    OpenPortFailed = -1,//�򿪶˿�ʧ��
    NoSetCenter = -2,//û�����ö�������
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
    DCB dcb;        // ���ڿ��ƿ�
    COMMTIMEOUTS timeouts = {    // ���ڳ�ʱ���Ʋ���
        100,        // ���ַ������ʱʱ��: 100 ms
        1,          // ������ʱÿ�ַ���ʱ��: 1 ms (n���ַ��ܹ�Ϊn ms)
        500,        // ������(�����)����ʱʱ��: 500 ms
        1,          // д����ʱÿ�ַ���ʱ��: 1 ms (n���ַ��ܹ�Ϊn ms)
        100};       // ������(�����)д��ʱʱ��: 100 ms
    
    hPort = CreateFile(pPort,    // �������ƻ��豸·��
            GENERIC_READ | GENERIC_WRITE,    // ��д��ʽ
            0,               // ����ʽ����ռ
            NULL,            // Ĭ�ϵİ�ȫ������
            OPEN_EXISTING,   // ������ʽ
            0,               // ���������ļ�����
            NULL);           // �������ģ���ļ�
    
    if(hPort == INVALID_HANDLE_VALUE) 
    {
//        printf("Open Port Failed\n");
        return NULL;        // �򿪴���ʧ��
    }
    
    GetCommState(hPort, &dcb);        // ȡDCB
    
    dcb.BaudRate = nBaudRate;
    dcb.ByteSize = nByteSize;
    dcb.Parity = nParity;
    dcb.StopBits = nStopBits;
    
    SetCommState(hPort, &dcb);        // ����DCB    
    SetupComm(hPort, 4096, 1024);     // �������������������С    
    SetCommTimeouts(hPort, &timeouts);    // ���ó�ʱ
    
    return hPort;
}

int ReadPort(void* pData,
			 int nLength)
{
    DWORD dwNumRead;    // �����յ������ݳ���    
    ReadFile(hSerialPort, pData, (DWORD)nLength, &dwNumRead, NULL);    
    return (int)dwNumRead;
}

/////////////////////////////////////////////////////////////////////////////////
// ������WritePort                                                             //
// ˵����д����                                                                //
//      pData: ��д�����ݻ�����ָ��                                            //
//      nLength: ��д�����ݳ���                                                //
// ����ֵ���Ƿ�д�ɹ�                                                          //
/////////////////////////////////////////////////////////////////////////////////
BOOL WritePort(void* pData, int nLength)
{
    DWORD dwNumWrite;    // ���ڷ��������ݳ���    
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
		//MessageBox(NULL, "��ָ������ʧ�ܣ�������ѡ�񴮿ڡ�","ʧ��", MB_OK|MB_ICONWARNING);
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
	retstr = "������";
	return 1;
}

extern "C" __declspec(dllexport) int run(char * source,
										 char * destination,
										 char * content)
{
	OutputDebugString("------------������ function call()-------------------\n");
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
