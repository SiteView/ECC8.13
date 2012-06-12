// SMSIT39.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "SMSIT39.h"

#include "../SMSIT39/TimeoutSocket.h"
#include "../SMSIT39/MsgObjs.h"

#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39App

BEGIN_MESSAGE_MAP(CSMSIT39App, CWinApp)
	//{{AFX_MSG_MAP(CSMSIT39App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39App construction

CSMSIT39App::CSMSIT39App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSMSIT39App object

CSMSIT39App theApp;

/////////////////////////////////////////////////////////////////////////////
// CSMSIT39App initialization

BOOL CSMSIT39App::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}


// 连接短信网关服务器
// smapArgs = 相关参数的参数表
// Socket = 返回一个用来后续与短信网关通讯的Socket对象
// 返回值：如果成功返回TRUE，否则返回FALSE。
BOOL SMI_Connect(CMapStringToString & smapArgs, CTimeoutSocket & Socket)
{
	if (!Socket.Create())
		return FALSE;

	CString strServerName;
	smapArgs.Lookup("servername", strServerName); // 取短信网关服务器名（IP）
	CString strServerPort;
	smapArgs.Lookup("serverport", strServerPort); // 取短信网关服务器端口号
	int nServerPort = ::atoi(strServerPort);

	return Socket.Connect(strServerName, UINT(nServerPort));
}

// 发送一个短信网关通讯消息
// Socket = 指定一个可用的Socket链接
// piSMMsg = 制定一个消息对象的操作接口
// 返回值：如果成功返回TRUE，否则返回FALSE。
BOOL SMI_SendMsg(CTimeoutSocket & Socket, ISMMsg * piSMMsg)
{
	CString strMsgString = piSMMsg->GetString(); // 消息对象自动合成通讯字符串
	LPCSTR pszMsg = strMsgString;
	int nLen = strlen(pszMsg);
	return Socket.Send(pszMsg, nLen) == nLen;
}

// 接收一个短信网关服务器发回的消息
// Socket = 指定一个可用的Socket链接
// piSMMsg = 制定一个消息对象的操作接口
// 返回值：如果成功返回TRUE，否则返回FALSE。
BOOL SMI_RecvMsg(CTimeoutSocket & Socket, ISMMsg * piSMMsg)
{
	const int MAX_RECV_BUFF = 128;
	char szRecvBuffp[MAX_RECV_BUFF] = {0};
	int nRecv = Socket.Receive(szRecvBuffp, MAX_RECV_BUFF, 10000);
	if (nRecv < 1)
		return FALSE; // 超时未接收到预期的反馈信息

	return piSMMsg->SetString(CString(szRecvBuffp)); // 将收到的字符串放到消息对象自动解析
}

// 连接短信网关服务器
// smapArgs = 相关参数的参数表
// Socket = 返回一个用来后续与短信网关通讯的Socket对象
// 返回值：如果成功返回TRUE，否则返回FALSE。
BOOL SMI_Logon(CMapStringToString & smapArgs, CTimeoutSocket & Socket)
{
	// ++++++ 发送登录消息 ++++++
	CString strUserName;
	smapArgs.Lookup("uid", strUserName); // 取用户名
	CString strPassword;
	smapArgs.Lookup("pwd", strPassword); // 取用户密码

	CMsgLogon MsgLogon;
	if (!MsgLogon.setUserName(strUserName))
		return FALSE; // 用户名不符合规则
	if (!MsgLogon.setUserPassword(strPassword))
		return FALSE; // 密码不符合规则

	if (!SMI_SendMsg(Socket, &MsgLogon))
		return FALSE; // 发送登录消息失败
	// ------ 发送登录消息 ------

	// ++++++ 接收登录反馈 ++++++
	CMsgLogonRes MsgLogonRes;
	if (!SMI_RecvMsg(Socket, &MsgLogonRes))
		return FALSE; // 接收登录反馈消息失败

	if (MsgLogonRes.m_strResult != "1")
		return FALSE; // 登录失败，用户名或者密码错误
	// ------ 接收登录反馈 ------

	return TRUE;
}

// 连接短信网关服务器
// smapArgs = 相关参数的参数表
// Socket = 返回一个用来后续与短信网关通讯的Socket对象
// nSequence = 短信的序号，在发送超长正文短信时用到，正常短信单发，改值为1。
// 返回值：如果成功返回TRUE，否则返回FALSE。
BOOL SMI_SendSM(CMapStringToString & smapArgs, CTimeoutSocket & Socket, LPCSTR pszPhones, LPCSTR pszContent, int nSequence = 1)
{
	// ++++++ 发送短信数据消息 ++++++
	CMsgSMData MsgSMData;
	CString strUserName;
	smapArgs.Lookup("uid", strUserName); // 取用户名
	CString strServiceID;
	smapArgs.Lookup("serviceid", strServiceID); // 取服务ID
	CString strDisplayPhone;
	smapArgs.Lookup("displayphone", strDisplayPhone); // 取显示号码
	MsgSMData.m_strSequence.Format("%04d", nSequence);

	MsgSMData.m_strUserName = strUserName;
	MsgSMData.m_strServiceID = strServiceID;

	if (!MsgSMData.setDisplaySPhone(strDisplayPhone))
		return FALSE;
	if (MsgSMData.SetPhones(CString(pszPhones)) == pszPhones)
		return FALSE; // 目标电话号码长度不足11位

	// 先保留未发送完的多余正文部分
	CString strContent = MsgSMData.SetDataContent(CString(pszContent));

	if (!SMI_SendMsg(Socket, &MsgSMData))
		return FALSE; // 发送消息失败
	// ------ 发送短信数据消息 ------

	// ++++++ 接收短信发送反馈 ++++++
	CMsgSMDataRes MsgSMDataRes;
	if (!SMI_RecvMsg(Socket, &MsgSMDataRes))
		return FALSE; // 接收短信发送反馈消息失败

	if (MsgSMDataRes.m_strResult != "1")
		return FALSE; // 信息发送失败
	// ------ 接收短信发送反馈 ------

	if (strContent.GetLength() > 0)
		// 短信正文超长部分递归发送
		return SMI_SendSM(smapArgs, Socket, pszPhones, strContent, nSequence + 1);

	return TRUE;
}

// 一个完整的参数实例
// UID=abcdefgh;PWD=12345678;ServiceID=SIDSID;DisplayPhone=11608851;ServerName=127.0.0.1;ServerPort=1608
// UID：短信网关登录名
// PWD：短信网关登录密码
// ServiceID：服务ID
// DisplayPhone：显示号码
// ServerName：短信网关IP或URL
// ServerPort：短信网关端口
extern "C" _declspec(dllexport) int run(char *source, char *destination, char *content)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	// 参数解析
	CMapStringToString smapArgs;
	if (!AnalysisArgs(source, smapArgs))
		return 0;

	// ++++++ 建立TCP链接 ++++++
	CTimeoutSocket Socket;
	if (!SMI_Connect(smapArgs, Socket))
		return 0; // // 建链失败
	// ------ 建立TCP链接 ------

	// ++++++ 登录 ++++++
	if (!SMI_Logon(smapArgs, Socket))
		return 0;
	// ------ 登录 ------

	// ++++++ 发送短信数据消息 ++++++
	if (!::SMI_SendSM(smapArgs, Socket, destination, content))
		return 0; // 短信发送失败
	// ------ 发送短信数据消息 ------

	return 1;
}

extern "C" __declspec(dllexport) int getinfo(string & retstr)
{
	retstr = "电报局小灵通短信接口";
	return 1;
}