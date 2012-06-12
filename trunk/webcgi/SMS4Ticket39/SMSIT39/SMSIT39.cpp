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


// ���Ӷ������ط�����
// smapArgs = ��ز����Ĳ�����
// Socket = ����һ�������������������ͨѶ��Socket����
// ����ֵ������ɹ�����TRUE�����򷵻�FALSE��
BOOL SMI_Connect(CMapStringToString & smapArgs, CTimeoutSocket & Socket)
{
	if (!Socket.Create())
		return FALSE;

	CString strServerName;
	smapArgs.Lookup("servername", strServerName); // ȡ�������ط���������IP��
	CString strServerPort;
	smapArgs.Lookup("serverport", strServerPort); // ȡ�������ط������˿ں�
	int nServerPort = ::atoi(strServerPort);

	return Socket.Connect(strServerName, UINT(nServerPort));
}

// ����һ����������ͨѶ��Ϣ
// Socket = ָ��һ�����õ�Socket����
// piSMMsg = �ƶ�һ����Ϣ����Ĳ����ӿ�
// ����ֵ������ɹ�����TRUE�����򷵻�FALSE��
BOOL SMI_SendMsg(CTimeoutSocket & Socket, ISMMsg * piSMMsg)
{
	CString strMsgString = piSMMsg->GetString(); // ��Ϣ�����Զ��ϳ�ͨѶ�ַ���
	LPCSTR pszMsg = strMsgString;
	int nLen = strlen(pszMsg);
	return Socket.Send(pszMsg, nLen) == nLen;
}

// ����һ���������ط��������ص���Ϣ
// Socket = ָ��һ�����õ�Socket����
// piSMMsg = �ƶ�һ����Ϣ����Ĳ����ӿ�
// ����ֵ������ɹ�����TRUE�����򷵻�FALSE��
BOOL SMI_RecvMsg(CTimeoutSocket & Socket, ISMMsg * piSMMsg)
{
	const int MAX_RECV_BUFF = 128;
	char szRecvBuffp[MAX_RECV_BUFF] = {0};
	int nRecv = Socket.Receive(szRecvBuffp, MAX_RECV_BUFF, 10000);
	if (nRecv < 1)
		return FALSE; // ��ʱδ���յ�Ԥ�ڵķ�����Ϣ

	return piSMMsg->SetString(CString(szRecvBuffp)); // ���յ����ַ����ŵ���Ϣ�����Զ�����
}

// ���Ӷ������ط�����
// smapArgs = ��ز����Ĳ�����
// Socket = ����һ�������������������ͨѶ��Socket����
// ����ֵ������ɹ�����TRUE�����򷵻�FALSE��
BOOL SMI_Logon(CMapStringToString & smapArgs, CTimeoutSocket & Socket)
{
	// ++++++ ���͵�¼��Ϣ ++++++
	CString strUserName;
	smapArgs.Lookup("uid", strUserName); // ȡ�û���
	CString strPassword;
	smapArgs.Lookup("pwd", strPassword); // ȡ�û�����

	CMsgLogon MsgLogon;
	if (!MsgLogon.setUserName(strUserName))
		return FALSE; // �û��������Ϲ���
	if (!MsgLogon.setUserPassword(strPassword))
		return FALSE; // ���벻���Ϲ���

	if (!SMI_SendMsg(Socket, &MsgLogon))
		return FALSE; // ���͵�¼��Ϣʧ��
	// ------ ���͵�¼��Ϣ ------

	// ++++++ ���յ�¼���� ++++++
	CMsgLogonRes MsgLogonRes;
	if (!SMI_RecvMsg(Socket, &MsgLogonRes))
		return FALSE; // ���յ�¼������Ϣʧ��

	if (MsgLogonRes.m_strResult != "1")
		return FALSE; // ��¼ʧ�ܣ��û��������������
	// ------ ���յ�¼���� ------

	return TRUE;
}

// ���Ӷ������ط�����
// smapArgs = ��ز����Ĳ�����
// Socket = ����һ�������������������ͨѶ��Socket����
// nSequence = ���ŵ���ţ��ڷ��ͳ������Ķ���ʱ�õ����������ŵ�������ֵΪ1��
// ����ֵ������ɹ�����TRUE�����򷵻�FALSE��
BOOL SMI_SendSM(CMapStringToString & smapArgs, CTimeoutSocket & Socket, LPCSTR pszPhones, LPCSTR pszContent, int nSequence = 1)
{
	// ++++++ ���Ͷ���������Ϣ ++++++
	CMsgSMData MsgSMData;
	CString strUserName;
	smapArgs.Lookup("uid", strUserName); // ȡ�û���
	CString strServiceID;
	smapArgs.Lookup("serviceid", strServiceID); // ȡ����ID
	CString strDisplayPhone;
	smapArgs.Lookup("displayphone", strDisplayPhone); // ȡ��ʾ����
	MsgSMData.m_strSequence.Format("%04d", nSequence);

	MsgSMData.m_strUserName = strUserName;
	MsgSMData.m_strServiceID = strServiceID;

	if (!MsgSMData.setDisplaySPhone(strDisplayPhone))
		return FALSE;
	if (MsgSMData.SetPhones(CString(pszPhones)) == pszPhones)
		return FALSE; // Ŀ��绰���볤�Ȳ���11λ

	// �ȱ���δ������Ķ������Ĳ���
	CString strContent = MsgSMData.SetDataContent(CString(pszContent));

	if (!SMI_SendMsg(Socket, &MsgSMData))
		return FALSE; // ������Ϣʧ��
	// ------ ���Ͷ���������Ϣ ------

	// ++++++ ���ն��ŷ��ͷ��� ++++++
	CMsgSMDataRes MsgSMDataRes;
	if (!SMI_RecvMsg(Socket, &MsgSMDataRes))
		return FALSE; // ���ն��ŷ��ͷ�����Ϣʧ��

	if (MsgSMDataRes.m_strResult != "1")
		return FALSE; // ��Ϣ����ʧ��
	// ------ ���ն��ŷ��ͷ��� ------

	if (strContent.GetLength() > 0)
		// �������ĳ������ֵݹ鷢��
		return SMI_SendSM(smapArgs, Socket, pszPhones, strContent, nSequence + 1);

	return TRUE;
}

// һ�������Ĳ���ʵ��
// UID=abcdefgh;PWD=12345678;ServiceID=SIDSID;DisplayPhone=11608851;ServerName=127.0.0.1;ServerPort=1608
// UID���������ص�¼��
// PWD���������ص�¼����
// ServiceID������ID
// DisplayPhone����ʾ����
// ServerName����������IP��URL
// ServerPort���������ض˿�
extern "C" _declspec(dllexport) int run(char *source, char *destination, char *content)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	// ��������
	CMapStringToString smapArgs;
	if (!AnalysisArgs(source, smapArgs))
		return 0;

	// ++++++ ����TCP���� ++++++
	CTimeoutSocket Socket;
	if (!SMI_Connect(smapArgs, Socket))
		return 0; // // ����ʧ��
	// ------ ����TCP���� ------

	// ++++++ ��¼ ++++++
	if (!SMI_Logon(smapArgs, Socket))
		return 0;
	// ------ ��¼ ------

	// ++++++ ���Ͷ���������Ϣ ++++++
	if (!::SMI_SendSM(smapArgs, Socket, destination, content))
		return 0; // ���ŷ���ʧ��
	// ------ ���Ͷ���������Ϣ ------

	return 1;
}

extern "C" __declspec(dllexport) int getinfo(string & retstr)
{
	retstr = "�籨��С��ͨ���Žӿ�";
	return 1;
}