// SMSonWebService.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SMSonWebService.h"
#include <string>
#include "WebService.h"
#include "md5.h"
using namespace SMSS;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CSMSonWebServiceApp

BEGIN_MESSAGE_MAP(CSMSonWebServiceApp, CWinApp)
END_MESSAGE_MAP()


// CSMSonWebServiceApp 构造

CSMSonWebServiceApp::CSMSonWebServiceApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSMSonWebServiceApp 对象

CSMSonWebServiceApp theApp;


// CSMSonWebServiceApp 初始化

BOOL CSMSonWebServiceApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++苏合 2007-07-25+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//DoMD5Hash方法用于对一个字符串进行MD5哈希，返回一个用字符代表的无空格的字符串（如"fe4567a3b8ed..."）                                 +
//参数：                                                                                                                              +
//   [in] dataStr      需要哈希的字符串指针                                                                                           +
//   [out] hashStr     通过此字符串指针返回哈希后的字符串                                                                             +
//                                                                                                                                    +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void DoMD5Hash(const char* dataStr, char* hashStr)
{
	//进行Hash需要的MD5对象
	MD5_CTX m_md5;

	//分3步进行hash运算
	MD5Init(&m_md5);
	MD5Update(&m_md5, (unsigned char *)dataStr, strlen(dataStr));
	MD5Final(&m_md5);

	//将hash后的数据转化为无空格的小写字符串
	for ( int i = 0 ; i < 16 ; i++ )
	{
		char tmp[3];
		_itoa(m_md5.digest[i], tmp , 16);

		if (strlen(tmp) == 1)
		{
			tmp[1] = tmp[0];
			tmp[0] = '0';
			tmp[2] = '\0';
		}
		strcat(hashStr, tmp);
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++苏合 2007-07-25+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//此DLL文件的接口方法，用于发送短信                                                                                                   +
//参数：                                                                                                                              +
//   [in] source          发送短信的参数                                                                                              +
//   [in] destination     发送短信的目的手机号码                                                                                      +
//   [in] content         要发送的短信内容                                                                                            +
//                                                                                                                                    +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern "C" __declspec(dllexport) int run(char *source, char *destination, char *content)
{
	// 因为生成的代码是基于ATL的，所以要初始化COM
	CoInitialize(NULL);

	char* inputparam[4];
	char * token = NULL;

	//从source得到第一个参数
	token = strtok(source , " ");    
	int i = 0;

	while( token != NULL )
	{
		//当还有参数在source中时
		inputparam[i] = token;
		//得到后面的参数
		token = strtok( NULL , " ");
		i++;
	}
	char* userName = inputparam[0];
	char* userPwd = inputparam[1];
	char* userAddress = inputparam[2];
	char* userFs = inputparam[3];

	char buf[256];
	char buf2[33];                 //用于存放MD5哈希后的字符串
	memset(buf, 0, 256);
	memset(buf2, 0, 33);
	CTime t = CTime::GetCurrentTime();
	char temp_time[30];
	memset(temp_time, 0, 30);
	sprintf(temp_time, "%d-%d-%d-%d:%d:%d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());

	OutputDebugString("\n");
	OutputDebugString(temp_time);
	OutputDebugString("\n");

	sprintf(buf, "%s|%s|%s", userPwd, temp_time, userAddress);

	OutputDebugString("\n");
	OutputDebugString(buf);
	OutputDebugString("\n");

	HRESULT hr = S_OK;
	CComBSTR Appid = "1";
   
	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, content, -1, NULL, 0);    //计算将短信内容由GB2313转换为Unicode需要的空间大小
	
	WCHAR *pwText;
	pwText = new WCHAR[dwNum];
	memset(pwText, 0, 2*dwNum);
	if(!pwText)
	{
		delete[] pwText;
	}

	MultiByteToWideChar (CP_ACP, 0, content, -1, pwText, dwNum);
	CComBSTR Msg = pwText;
	
	CComBSTR JsNo = destination;

	DoMD5Hash(userName, buf2);

	OutputDebugString("\n");
	OutputDebugString(buf2);
	OutputDebugString("\n");

	CComBSTR yhm = buf2;

	memset(buf2, 0, 33);
	DoMD5Hash(buf, buf2);

	OutputDebugString("\n");
	OutputDebugString(buf2);
	OutputDebugString("\n");
	CComBSTR mma = buf2;

	CComBSTR zz = temp_time;
	CComBSTR fsyy = userFs;
	CComBSTR hiResult;

	CSMSS* smss = new CSMSS();	// 代理对象
	hr = smss->JWSend1(Appid, Msg, JsNo, yhm, mma, zz, fsyy, &hiResult);

	if(FAILED(hr))
	{
		OutputDebugString("调用失败");
	}
	else
	{
		CString str(hiResult);
		OutputDebugString(str);
	}

	delete smss;
	
	CoUninitialize();
	delete[] pwText;
	return 1;
}

extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "通过Web Service发送短信";
	return 1;
}
