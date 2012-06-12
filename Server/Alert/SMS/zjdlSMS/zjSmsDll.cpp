// zjSmsDll.cpp : 定义 DLL 应用程序的入口点。
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

    //DEBUG_LOG("读取配置文件:%s", szPath);

    ::GetPrivateProfileString("SMS","ip","",gszIP,128,szPath);
    gnPort = ::GetPrivateProfileInt("SMS","port",0,szPath);
    ::GetPrivateProfileString("SMS","appid","",gszAppID,64,szPath);
    ::GetPrivateProfileString("SMS","password","",gszPwd,64,szPath);

    
    return 0;
}

//认证请求
struct SMSAuthReq
{
    char Length[5];             //报文长度
    char TransType[4];          //交易代码1001
    char SubType[2];            //标志字段（空）
    char AppId[12];             //应用程序标识号
    char Passwd[20];            //应用程序密码
};

//认证应答
struct SMSAuthRep
{
    char Length[5];             //报文长度
    char RetCode[4];            //响应代码（0000－成功，其它－失败）
    char RetMsg[100];           //失败原因
};



//请求发送报文
struct SMSSendReq
{
    char Length[5];             //报文长度
    char TransType[4];          //交易代码（3011）
    char SubType[2];            //标志字段（01）
    char AppId[12];             //应用程序标识号
    char AppSerialNo[35];       //应用流水号
    char MessageType[3];        //短信类型0表示中文;1表示英文;2表示UCS2码;21,4为压缩PDU码
    char RecvId[255];           //接收方地址，多个手机号之间用逗号分开
    char Ack[1];                //0表示不回复,1表示需要回执,2表示需回复，3表示需要回执＋需回复
    char Reply[30];             //回复地址
    char Priority[2];           //优先级0-9
    char Rep[2];                //重复次数
    char SubApp[3];             //子应用号
    char CheckFlag[2];          //标志位，必须为字符串CF，如不符合则网关认为消息无效,丢弃本数据包。
    char Content;               //正文内容，目前手机一般可以支持最长一条短信659个汉字
};

//请求发送报文应答
struct SMSSendRep
{
    char Length[5];             //报文长度
    char RetCode[4];            //响应代码（0000－成功，其它－失败。如果不为0000，接下来为失败原因）
    char RetMsg;                //失败原因（变长）
};


int SendBySocket(char *szSMSTo, char *szContent)
{
    int ret = 0;
    int len = 0;

    if (strlen(gszIP) <= 0 || gnPort <= 0)
    {
        ERR_LOG("IP地址和端口没有设置.");
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET==s)
    {
        int err = WSAGetLastError();
        ERR_LOG("连接到短信网关失败：%d",err);
        goto eh;
    }

    sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(gszIP);
    sockaddr.sin_port = htons(gnPort);

    if (connect(s, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("连接到短信网关失败：%d",err);
        goto eh;
    }

    struct SMSAuthReq stAuth;

    memset(&stAuth, ' ', sizeof(struct SMSAuthReq));

    char szTmp[64];

    sprintf(szTmp, "%d", sizeof(struct SMSAuthReq) - 5);

    if (strlen(szTmp) > 5)
    {
         ERR_LOG("发送到网关的报文长度过长。");
        goto eh;
    }

    memcpy(stAuth.Length, szTmp, strlen(szTmp)>5?5:strlen(szTmp));
    memcpy(stAuth.TransType, "1001", 4);
    memcpy(stAuth.AppId, gszAppID, strlen(gszAppID)>12?12:strlen(gszAppID));
    memcpy(stAuth.Passwd, gszPwd, strlen(gszPwd)>20?20:strlen(gszPwd));

    if (send(s, (char *)&stAuth,sizeof(struct SMSAuthReq),0) ==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("发送认证报文到网关失败：%d",err);
        goto eh;
    }

    
    char szHead[32];
    memset(szHead, 0, 32);

    //接受报文头
    if ((ret =recv(s, szHead, 5,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("接受认证应答报文失败：%d",err);
        goto eh;
    }


    //接受的长度不对
    if (ret < 5)
    {
        ERR_LOG("报文头长度字段长度小于5。");
        goto eh;
    }

    char *szEnd = NULL;

    len = strtod(szHead,&szEnd);

    if (len <= 0)
    {
        ERR_LOG("报文长度内容错误。");
        goto eh;
    }

    char *szRep = new char[len+2];

    memset(szRep, 0, len+2);

    if ((ret =recv(s, szRep, len,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("接受认证应答报文失败：%d",err);
        delete szRep;
        szRep = NULL;
        goto eh;
    }

    if (memcmp(szRep, "0000", 4) != 0)
    {
        ERR_LOG("认证时认证失败：%s", szRep+4);

        delete szRep;
        szRep = NULL;
        goto eh;
    }

    delete szRep;
    szRep = NULL;

    //发送SMS信息
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
        ERR_LOG("发送报文到网关失败：%d",err);
        delete szSendReq;
        goto eh;
    }

    delete szSendReq;

    memset(szHead, 0, 32);

    //接受报文头
    if ((ret =recv(s, szHead, 5,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("接受发送应答报文失败：%d",err);
        goto eh;
    }    

    //接受的长度不对
    if (ret < 5)
    {
        ERR_LOG("发送报文头长度字段长度小于5。");
        goto eh;
    }

    len = strtod(szHead,&szEnd);

    if (len <= 0)
    {
        ERR_LOG("发送报文长度内容错误。");
        goto eh;
    }

    szRep = new char[len+2];

    memset(szRep, 0, len+2);

    if ((ret =recv(s, szRep, len,0))==SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        ERR_LOG("接受发送应答报文失败：%d",err);
        delete szRep;
        szRep = NULL;
        goto eh;
    }

    if (memcmp(szRep, "0000", 4) != 0)
    {
        ERR_LOG("发送报文返回码错误：%s", szRep+4);

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
	retstr = "浙江电力短信发送DLL";
	return 1;
}


//动态链接库的入口
//funname,调用的发送短信的函数
//szSMTo，短信发送给谁
//szContent,短信内容
//返回为1表示成功
extern "C" __declspec(dllexport) int run(char * szFunName, char * szSMTo, char *szContent)   
{	

    DEBUG_LOG("=====发送短信报警开始:%s",szSMTo);

	read_config();
	//调用发送函数发送短信
	if (!SendBySocket(szSMTo,szContent))
	    return 1;
    else 
        return 0;
}