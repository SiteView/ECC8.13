// SMSonWebService.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CSMSonWebServiceApp

BEGIN_MESSAGE_MAP(CSMSonWebServiceApp, CWinApp)
END_MESSAGE_MAP()


// CSMSonWebServiceApp ����

CSMSonWebServiceApp::CSMSonWebServiceApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSMSonWebServiceApp ����

CSMSonWebServiceApp theApp;


// CSMSonWebServiceApp ��ʼ��

BOOL CSMSonWebServiceApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++�պ� 2007-07-25+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//DoMD5Hash�������ڶ�һ���ַ�������MD5��ϣ������һ�����ַ�������޿ո���ַ�������"fe4567a3b8ed..."��                                 +
//������                                                                                                                              +
//   [in] dataStr      ��Ҫ��ϣ���ַ���ָ��                                                                                           +
//   [out] hashStr     ͨ�����ַ���ָ�뷵�ع�ϣ����ַ���                                                                             +
//                                                                                                                                    +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void DoMD5Hash(const char* dataStr, char* hashStr)
{
	//����Hash��Ҫ��MD5����
	MD5_CTX m_md5;

	//��3������hash����
	MD5Init(&m_md5);
	MD5Update(&m_md5, (unsigned char *)dataStr, strlen(dataStr));
	MD5Final(&m_md5);

	//��hash�������ת��Ϊ�޿ո��Сд�ַ���
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


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++�պ� 2007-07-25+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//��DLL�ļ��Ľӿڷ��������ڷ��Ͷ���                                                                                                   +
//������                                                                                                                              +
//   [in] source          ���Ͷ��ŵĲ���                                                                                              +
//   [in] destination     ���Ͷ��ŵ�Ŀ���ֻ�����                                                                                      +
//   [in] content         Ҫ���͵Ķ�������                                                                                            +
//                                                                                                                                    +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern "C" __declspec(dllexport) int run(char *source, char *destination, char *content)
{
	// ��Ϊ���ɵĴ����ǻ���ATL�ģ�����Ҫ��ʼ��COM
	CoInitialize(NULL);

	char* inputparam[4];
	char * token = NULL;

	//��source�õ���һ������
	token = strtok(source , " ");    
	int i = 0;

	while( token != NULL )
	{
		//�����в�����source��ʱ
		inputparam[i] = token;
		//�õ�����Ĳ���
		token = strtok( NULL , " ");
		i++;
	}
	char* userName = inputparam[0];
	char* userPwd = inputparam[1];
	char* userAddress = inputparam[2];
	char* userFs = inputparam[3];

	char buf[256];
	char buf2[33];                 //���ڴ��MD5��ϣ����ַ���
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
   
	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, content, -1, NULL, 0);    //���㽫����������GB2313ת��ΪUnicode��Ҫ�Ŀռ��С
	
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

	CSMSS* smss = new CSMSS();	// �������
	hr = smss->JWSend1(Appid, Msg, JsNo, yhm, mma, zz, fsyy, &hiResult);

	if(FAILED(hr))
	{
		OutputDebugString("����ʧ��");
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
	retstr = "ͨ��Web Service���Ͷ���";
	return 1;
}
