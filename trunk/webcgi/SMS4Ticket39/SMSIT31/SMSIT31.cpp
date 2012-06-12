// SMSIT31.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "SMSIT31.h"

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
// CSMSIT31App

BEGIN_MESSAGE_MAP(CSMSIT31App, CWinApp)
	//{{AFX_MSG_MAP(CSMSIT31App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMSIT31App construction

CSMSIT31App::CSMSIT31App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSMSIT31App object

CSMSIT31App theApp;

// һ�������Ĳ���ʵ��
// URL=http://127.0.0.1/SMSTest.asp;smallCode=TEST;srcMobile=13973100000;linkId=20050301030450001;workFlage=0;user=Test;password=123456
// URL����������HTTP�ӿ�URL
// smallCode����ȱ��������ȷ˵����
// srcMobile�����ŷ���Դ�ֻ�����
// linkId����ȱ��������ȷ˵����17λ�����ַ���
// workFlage����ȱ��������ȷ˵��������Ϊ'0'
// user���������ص�¼��
// password���������ص�¼����
extern "C" _declspec(dllexport) int run(char *source, char *destination, char *content)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	// ��������
	CMapStringToString smapArgs;
	if (!AnalysisArgs(source, smapArgs))
		return 0;

	// ++++++ ��������Ĳ����ϳ�HTTP���ô� ++++++
	CString strOpenUrl;
	smapArgs.Lookup("url", strOpenUrl);

	CString strSmallCode;
	smapArgs.Lookup("smallcode", strSmallCode);
	strOpenUrl += _T("?smallCode=");
	strOpenUrl += strSmallCode;

	CString strSrcMobile;
	smapArgs.Lookup("srcmobile", strSrcMobile);
	strOpenUrl += _T("&srcMobile=");
	strOpenUrl += strSrcMobile;

	CString strLinkId;
	smapArgs.Lookup("linkid", strLinkId);
	strOpenUrl += _T("&linkId=");
	strOpenUrl += strLinkId;

	CString strWorkFlage;
	smapArgs.Lookup("workflage", strWorkFlage);
	strOpenUrl += _T("&workFlage=");
	strOpenUrl += strWorkFlage;

	CString strUser;
	smapArgs.Lookup("user", strUser);
	strOpenUrl += _T("&user=");
	strOpenUrl += strUser;

	CString strPassword;
	smapArgs.Lookup("password", strPassword);
	strOpenUrl += _T("&password=");
	strOpenUrl += strPassword;

	CString strDesMobile = destination;
	strOpenUrl += _T("&destMobile=");
	strOpenUrl += strDesMobile;

	CString strContent = ToURLString(content);
	strOpenUrl += _T("&content=");
	strOpenUrl += strContent;
	// ------ ��������Ĳ����ϳ�HTTP���ô� ------

	int nRet = 0;

	// ʹ��Wininet API�Զ������ؽ���HTTP��������ɶ��ŷ���
	HINTERNET hRootHandle = NULL;
	HINTERNET hOpenUrlHandle = NULL;
	hRootHandle = InternetOpen("SMS Interface",INTERNET_OPEN_TYPE_DIRECT,NULL, NULL,0);
	if (NULL != hRootHandle)
	{
		hOpenUrlHandle = InternetOpenUrl(hRootHandle, strOpenUrl, NULL, 0, INTERNET_FLAG_RAW_DATA, 0);
		if (NULL != hOpenUrlHandle)
		{
			const int MAX_BUFF = 1024 * 8;
			TCHAR szBuff[MAX_BUFF] = {0};
			DWORD uSize = MAX_BUFF;
			if (::HttpQueryInfo(hOpenUrlHandle, HTTP_QUERY_CONTENT_LENGTH, szBuff, &uSize, NULL))
			{// ȡ�����÷������ݵĳ���

				DWORD uTextLen = DWORD(min(::atoi(szBuff), MAX_BUFF - 1));
				::memset(szBuff, 0, MAX_BUFF * sizeof(TCHAR));
				DWORD uReaded = 0;
				if (::InternetReadFile(hOpenUrlHandle, szBuff, uTextLen, &uReaded))
				{
					// �����÷����������������
					::OutputDebugString(szBuff);
				}
			}
			nRet = 1;
			InternetCloseHandle(hOpenUrlHandle); 
		}
		InternetCloseHandle(hRootHandle);
	}

	return nRet;
}

extern "C" __declspec(dllexport) int getinfo(string & retstr)
{
	retstr = "���������Žӿ�";
	return 1;
}