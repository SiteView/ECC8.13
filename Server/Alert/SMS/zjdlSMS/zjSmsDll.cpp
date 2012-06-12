// zjSmsDll.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "zjSmsDll.h"
#include <string>
using namespace std;

#include <stdio.h>
#include <tchar.h>
#include <conio.h>

#include "Winsock2.h"
#include "shlwapi.h"

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"shlwapi.lib")



char gszIP[128];
int  gnPort;
char gszAppID[64];
char gszPwd[64];


struct app_init
{
public:
    app_init()
    {
        WSADATA wsd;
        WSAStartup(MAKEWORD(2,2), &wsd);
        memset(gszIP, 0 ,128);
        memset(gszAppID,0, 64);
        memset(gszPwd, 0, 64);
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

	vsprintf_s(tcBuf,1023,s,argptr);
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


#define ERR_LOG error_log
#define DEBUG_LOG

int read_config()
{
    char szPath[MAX_PATH];

    ::GetModuleFileName(NULL, szPath, MAX_PATH);

    PathRemoveFileSpec(szPath);

    strcat(szPath,"\\smsconfig.ini");

    //DEBUG_LOG("��ȡ�����ļ�:%s", szPath);

    ::GetPrivateProfileString("SMS","ip","",gszIP,128,szPath);
    gnPort = ::GetPrivateProfileInt("SMS","port",0,szPath);
    ::GetPrivateProfileString("SMS","appid","",gszAppID,64,szPath);
    ::GetPrivateProfileString("SMS","password","",gszPwd,64,szPath);

    
    return 0;
}

//��֤����
struct SMSAuthReq
{
    char Length[5];             //���ĳ���
    char TransType[4];          //���״���1001
    char SubType[2];            //��־�ֶΣ��գ�
    char AppId[12];             //Ӧ�ó����ʶ��
    char Passwd[20];            //Ӧ�ó�������
};

//��֤Ӧ��
struct SMSAuthRep
{
    char Length[5];             //���ĳ���
    char RetCode[4];            //��Ӧ���루0000���ɹ���������ʧ�ܣ�
    char RetMsg[100];           //ʧ��ԭ��
};



//�����ͱ���
struct SMSSendReq
{
    char Length[5];             //���ĳ���
    char TransType[4];          //���״��루3011��
    char SubType[2];            //��־�ֶΣ�01��
    char AppId[12];             //Ӧ�ó����ʶ��
    char AppSerialNo[35];       //Ӧ����ˮ��
    char MessageType[3];        //��������0��ʾ����;1��ʾӢ��;2��ʾUCS2��;21,4Ϊѹ��PDU��
    char RecvId[255];           //���շ���ַ������ֻ���֮���ö��ŷֿ�
    char Ack[1];                //0��ʾ���ظ�,1��ʾ��Ҫ��ִ,2��ʾ��ظ���3��ʾ��Ҫ��ִ����ظ�
    char Reply[30];             //�ظ���ַ
    char Priority[2];           //���ȼ�0-9
    char Rep[2];                //�ظ�����
    char SubApp[3];             //��Ӧ�ú�
    char CheckFlag[2];          //��־λ������Ϊ�ַ���CF���粻������������Ϊ��Ϣ��Ч,���������ݰ���
    char Content;               //�������ݣ�Ŀǰ�ֻ�һ�����֧���һ������659������
};

//�����ͱ���Ӧ��
struct SMSSendRep
{
    char Length[5];             //���ĳ���
    char RetCode[4];            //��Ӧ���루0000���ɹ���������ʧ�ܡ������Ϊ0000��������Ϊʧ��ԭ��
    char RetMsg;                //ʧ��ԭ�򣨱䳤��
};


int SendBySocket(char *szSMSTo, char *szContent)
{
    int ret = 0;
    int len = 0;

    if (strlen(gszIP) <= 0 || gnPort <= 0)
    {
        ERR_LOG("IP��ַ�Ͷ˿�û������.");
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET==s)
    {
        int err = WSAGetLastError();
        ERR_LOG("���ӵ���������ʧ�ܣ�%d",err);
        goto eh;
    }

    sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(gszIP);
    sockaddr.sin_port = htons(gnPort);

    if (connect(s, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("���ӵ���������ʧ�ܣ�%d",err);
        goto eh;
    }

    struct SMSAuthReq stAuth;

    memset(&stAuth, ' ', sizeof(struct SMSAuthReq));

    char szTmp[64];

    sprintf(szTmp, "%d", sizeof(struct SMSAuthReq) - 5);

    if (strlen(szTmp) > 5)
    {
         ERR_LOG("���͵����صı��ĳ��ȹ�����");
        goto eh;
    }

    memcpy(stAuth.Length, szTmp, strlen(szTmp)>5?5:strlen(szTmp));
    memcpy(stAuth.TransType, "1001", 4);
    memcpy(stAuth.AppId, gszAppID, strlen(gszAppID)>12?12:strlen(gszAppID));
    memcpy(stAuth.Passwd, gszPwd, strlen(gszPwd)>20?20:strlen(gszPwd));

    if (send(s, (char *)&stAuth,sizeof(struct SMSAuthReq),0) ==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("������֤���ĵ�����ʧ�ܣ�%d",err);
        goto eh;
    }

    
    char szHead[32];
    memset(szHead, 0, 32);

    //���ܱ���ͷ
    if ((ret =recv(s, szHead, 5,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("������֤Ӧ����ʧ�ܣ�%d",err);
        goto eh;
    }


    //���ܵĳ��Ȳ���
    if (ret < 5)
    {
        ERR_LOG("����ͷ�����ֶγ���С��5��");
        goto eh;
    }

    char *szEnd = NULL;

    len = strtod(szHead,&szEnd);

    if (len <= 0)
    {
        ERR_LOG("���ĳ������ݴ���");
        goto eh;
    }

    char *szRep = new char[len+2];

    memset(szRep, 0, len+2);

    if ((ret =recv(s, szRep, len,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("������֤Ӧ����ʧ�ܣ�%d",err);
        delete szRep;
        szRep = NULL;
        goto eh;
    }

    if (memcmp(szRep, "0000", 4) != 0)
    {
        ERR_LOG("��֤ʱ��֤ʧ�ܣ�%s", szRep+4);

        delete szRep;
        szRep = NULL;
        goto eh;
    }

    delete szRep;
    szRep = NULL;

    //����SMS��Ϣ
    char *szSendReq = new char[sizeof(struct SMSSendReq) + strlen(szContent)];

    memset(szSendReq, 0, sizeof(struct SMSSendReq) + strlen(szContent));
    
    struct SMSSendReq *stSendReq = (struct SMSSendReq *)szSendReq;

    memset(stSendReq, ' ', sizeof(struct SMSSendReq));

    sprintf(szTmp, "%d", sizeof(struct SMSSendReq) + strlen(szContent) - 5 );

    memcpy(stSendReq->Length, szTmp, strlen(szTmp)>5?5:strlen(szTmp));
    memcpy(stSendReq->TransType, "3011", 4);
    memcpy(stSendReq->SubType, "01", 2);
    memcpy(stSendReq->AppId, gszAppID, strlen(gszAppID)>12?12:strlen(gszAppID));
    memcpy(stSendReq->AppSerialNo,"1", 1);
    memcpy(stSendReq->MessageType, "0", 1);
    memcpy(stSendReq->RecvId, szSMSTo, strlen(szSMSTo) >255?255:strlen(szSMSTo));
    memcpy(stSendReq->Ack,"0", 1);
    memcpy(stSendReq->Priority, "1", 1);
    memcpy(stSendReq->SubApp,"0",1);
    memcpy(stSendReq->CheckFlag, "CF",2);
    memcpy(&(stSendReq->Content), szContent, strlen(szContent));

    
    if (send(s, szSendReq, sizeof(struct SMSSendReq) + strlen(szContent),0) ==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("���ͱ��ĵ�����ʧ�ܣ�%d",err);
        delete szSendReq;
        goto eh;
    }

    delete szSendReq;

    memset(szHead, 0, 32);

    //���ܱ���ͷ
    if ((ret =recv(s, szHead, 5,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("���ܷ���Ӧ����ʧ�ܣ�%d",err);
        goto eh;
    }    

    //���ܵĳ��Ȳ���
    if (ret < 5)
    {
        ERR_LOG("���ͱ���ͷ�����ֶγ���С��5��");
        goto eh;
    }

    len = strtod(szHead,&szEnd);

    if (len <= 0)
    {
        ERR_LOG("���ͱ��ĳ������ݴ���");
        goto eh;
    }

    szRep = new char[len+2];

    memset(szRep, 0, len+2);

    if ((ret =recv(s, szRep, len,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("���ܷ���Ӧ����ʧ�ܣ�%d",err);
        delete szRep;
        szRep = NULL;
        goto eh;
    }

    if (memcmp(szRep, "0000", 4) != 0)
    {
        ERR_LOG("���ͱ��ķ��������%s", szRep+4);

        delete szRep;
        szRep = NULL;
        goto eh;
    }

    delete szRep;
    szRep = NULL;

    closesocket(s);

    return 0;
eh:
    if (INVALID_SOCKET != s)
        closesocket(s);

    return -1;
}

extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "�㽭�������ŷ���DLL";
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

	read_config();
	//���÷��ͺ������Ͷ���
	if (!SendBySocket(szSMTo,szContent))
	    return 1;
    else 
        return 0;
}