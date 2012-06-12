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

// 一个完整的参数实例
// URL=http://127.0.0.1/SMSTest.asp;smallCode=TEST;srcMobile=13973100000;linkId=20050301030450001;workFlage=0;user=Test;password=123456
// URL：短信网关HTTP接口URL
// smallCode：（缺少资料明确说明）
// srcMobile：短信发送源手机号码
// linkId：（缺少资料明确说明）17位数字字符串
// workFlage：（缺少资料明确说明）设置为'0'
// user：短信网关登录名
// password：短信网关登录密码
extern "C" _declspec(dllexport) int run(char *source, char *destination, char *content)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	// 参数解析
	CMapStringToString smapArgs;
	if (!AnalysisArgs(source, smapArgs))
		return 0;

	// ++++++ 将解析后的参数合成HTTP调用串 ++++++
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
	// ------ 将解析后的参数合成HTTP调用串 ------

	int nRet = 0;

	// 使用Wininet API对短信网关进行HTTP调用以完成短信发送
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
			{// 取到调用反馈内容的长度

				DWORD uTextLen = DWORD(min(::atoi(szBuff), MAX_BUFF - 1));
				::memset(szBuff, 0, MAX_BUFF * sizeof(TCHAR));
				DWORD uReaded = 0;
				if (::InternetReadFile(hOpenUrlHandle, szBuff, uTextLen, &uReaded))
				{
					// 将调用反馈内容输出到调试
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
	retstr = "大港油田短信接口";
	return 1;
}