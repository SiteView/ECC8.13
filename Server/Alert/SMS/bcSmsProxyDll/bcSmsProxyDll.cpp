// bcSmsProxyDll.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "Winsock2.h"
#include "shlwapi.h"
#include "stdio.h"
#include "tchar.h"
#include <string>

using namespace std;

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"shlwapi.lib")



char gszIP[128];
int  gnPort;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

struct app_init
{
public:
    app_init()
    {
        WSADATA wsd;
        WSAStartup(MAKEWORD(2,2), &wsd);
        memset(gszIP, 0 ,128);
        gnPort = 0;
    }
    ~app_init()
    {
        WSACleanup();
    }
};

struct app_init _init;

void error_log(char *s,...)
{
	va_list argptr;
	char tcBuf[1024];

	va_start(argptr, s);

	vsprintf(tcBuf,s,argptr);
	printf(_T("%s"),tcBuf);

	va_end(argptr);

	char tFileName[MAX_PATH];
	::GetModuleFileName(NULL,tFileName,MAX_PATH);

	PathRemoveFileSpec(tFileName);
	
	SYSTEMTIME syTm;
	::GetLocalTime(&syTm);

	sprintf(tFileName,"%s\\SmsLog.txt",tFileName);

	FILE *f = fopen(tFileName,_T("a+"));
	

	if (NULL != f)
	{

		fprintf(f,"%02d-%02d %02d:%02d:%02d %u %s\n",syTm.wMonth,syTm.wDay,syTm.wHour,syTm.wMinute,syTm.wSecond,GetTickCount(),tcBuf);

		fclose(f);
	}

	
}

string g_strIp = "127.0.0.1";
int	   g_nPort = 1968;
int	   g_nLocalPort = 10045;

#define ERR_LOG error_log
#define DEBUG_LOG

int SendBySocket(char *szSMSTo, char *szContent)
{
    int ret = 0;
    int len = 0;

	if (g_strIp.size() <= 0 || g_nPort <= 0)
    {
        ERR_LOG("IP��ַ�Ͷ˿�û������.");
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (INVALID_SOCKET==s)
    {
        int err = WSAGetLastError();
        ERR_LOG("���ӵ���������ʧ�ܣ�%d",err);
        goto eh;
    }

    sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockaddr.sin_port = htons(g_nLocalPort);

	if (bind(s,(SOCKADDR *)&sockaddr,sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		ERR_LOG(_T("socket bind error:%d\n"),err);
		goto eh;
	}

	int m = strlen(szContent);
	int n = 0;
	
	m = m>128?128:m;

	unsigned char *szBuf = new unsigned char[m+6];

	if (szBuf == NULL)
	{
		ERR_LOG("�����ڴ�ʧ�ܡ���");
		goto eh;
	}

	memset(szBuf, 0, m+6);

	szBuf[0] = 3;
	szBuf[1] = 0x01;
	szBuf[2] = '1';
	szBuf[3] = m;
	memcpy(szBuf+4, szContent, m);
	szBuf[m+4] = 0;
	szBuf[m+5] = 0;


	for(int i = 0; i <= m+4; i++)
	{
		szBuf[m+5] += szBuf[i];
	}

   sockaddr_in Remoteaddr;

    Remoteaddr.sin_family = AF_INET;
	Remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    Remoteaddr.sin_port = htons(g_nPort);

	if (sendto(s, (char *)szBuf, m+6, 0, (SOCKADDR *)&Remoteaddr,sizeof(SOCKADDR))== SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		ERR_LOG(_T("socket sendto error:%d\n"),err);
		delete szBuf;
		goto eh;

	}
	delete szBuf;
    closesocket(s);

    return 0;
eh:
    if (INVALID_SOCKET != s)
        closesocket(s);

    return -1;
}

extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "UDP���ŷ���DLL";
	return 1;
}


//��̬���ӿ�����
//funname,���õķ��Ͷ��ŵĺ���
//szSMTo�����ŷ��͸�˭
//szContent,��������
//����Ϊ1��ʾ�ɹ�
extern "C" __declspec(dllexport) int run(char * szFunName, char * szSMTo, char *szContent)   
{	

    DEBUG_LOG("=====���Ͷ��ű�����ʼ:%s",szSMTo);

	//���÷��ͺ������Ͷ���
	if (!SendBySocket(szSMTo,szContent))
	    return 1;
    else 
        return 0;
}

