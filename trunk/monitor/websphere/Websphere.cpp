/*
* Websphere.cpp 
*
* Created on 2007��9��26��, ����10:24 By �պ�
* Modified on 2007-10-16 By �պ�
*          ���Ӷ�Ӣ�İ�WebSphere��֧��
* 
*
* ͨ��XMLȡ��WebSphere��һЩ���ܲ���
* 
*/

// Websphere.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Websphere.h"
#include "tinyxml.h"
#include "../../base/funcGeneral.h"
#include <string>
#include <map>

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

// CWebsphereApp

BEGIN_MESSAGE_MAP(CWebsphereApp, CWinApp)
END_MESSAGE_MAP()

void ConvertUtf8ToGBK(CString &strUtf8) 
{ 
	int len= ::MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0); 
	unsigned short * wszGBK = new unsigned short[len+1]; 
	memset(wszGBK, 0, len * 2 + 2); 
	::MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, wszGBK, len); 
	len = ::WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL); 
	char *szGBK=new char[len + 1]; 
	memset(szGBK, 0, len + 1); 
	::WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL); 
	strUtf8 = szGBK; 
	delete[] szGBK; 
	delete[] wszGBK; 
}

BOOL GetSourceHtml(char* theUrl, char* saveFileName) 
{
	CInternetSession session;
	CInternetFile* file = NULL;
	try
	{
		// �������ӵ�ָ��URL
		file = (CInternetFile*) session.OpenURL(theUrl); 
	}
	catch (CInternetException* m_pException)
	{
		// ����д���Ļ������ļ�Ϊ��
		file = NULL; 
		m_pException->Delete();
		return FALSE;
	}

	// ��dataStore�������ȡ����ҳ�ļ�
	CStdioFile dataStore;

	if (file)
	{
		CString  somecode;							//Ҳ�ɲ���LPTSTR���ͣ�������ɾ���ı��е�\n�س���

		BOOL bIsOk = dataStore.Open(saveFileName,
			  CFile::modeCreate 
			| CFile::modeWrite 
			| CFile::shareDenyWrite 
			| CFile::typeText);

		if (!bIsOk)
			return FALSE;

		// ��д��ҳ�ļ���ֱ��Ϊ��
		bool flagReplace = false;
		int replaceNum = 0;
		while (file->ReadString(somecode) != NULL) //�������LPTSTR���ͣ���ȡ������nMax��0��ʹ�������ַ�ʱ����
		{
			if (!flagReplace)
			{
				replaceNum = somecode.Replace("encoding=\"UTF-8\"" ,"encoding=\"gb2312\"");
				if (0 != replaceNum)
				{
					flagReplace = true;
				}
			}
			ConvertUtf8ToGBK(somecode);
			dataStore.WriteString(somecode);
			dataStore.WriteString("\n");		   //���somecode����LPTSTR����,�ɲ��ô˾�
		}

		file->Close();
		delete file;
	}
	else
	{
		dataStore.WriteString(_T("��ָ�������������ӽ���ʧ��..."));	
		return FALSE;
	}

	return TRUE;
}

// CWebsphereApp ����

CWebsphereApp::CWebsphereApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWebsphereApp ����

CWebsphereApp theApp;


// CWebsphereApp ��ʼ��

BOOL CWebsphereApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Bean(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');           //�������ơ�a.a.a.xml�����ļ������ں����� TiXmlDocument �򿪻��д���

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );
	

	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && (0 != strcmp(statElement->Attribute("name"), "��ҵ bean")))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	
	sprintf(strReturn, "%screates=%s$", strReturn, listPerf["CreateCount"].c_str());

	sprintf(strReturn, "%sremoves=%s$", strReturn, listPerf["RemoveCount"].c_str());

	sprintf(strReturn, "%sactivates=%s$", strReturn, listPerf["ActivateCount"].c_str());

	sprintf(strReturn, "%spassivates=%s$", strReturn, listPerf["PassivateCount"].c_str());

	sprintf(strReturn, "%sinstantiates=%s$", strReturn, listPerf["InstantiateCount"].c_str());

	sprintf(strReturn, "%sdestroys=%s$", strReturn, listPerf["FreedCount"].c_str());

	sprintf(strReturn, "%sloads=%s$", strReturn, listPerf["LoadCount"].c_str());

	sprintf(strReturn, "%sstores=%s$", strReturn, listPerf["StoreCount"].c_str());

	sprintf(strReturn, "%sconcurrentActives=%s$", strReturn, listPerf["MethodReadyCount"].c_str());

	sprintf(strReturn, "%sconcurrentLives=%s$", strReturn, listPerf["LiveCount"].c_str());

	sprintf(strReturn, "%stotalMethodCalls=%s$", strReturn, listPerf["MethodCallCount"].c_str());

	sprintf(strReturn, "%savgMethodRt=%s$", strReturn, listPerf["CreateCount"].c_str());

	sprintf(strReturn, "%savgCreateTime=%s$", strReturn, listPerf["CreateTime"].c_str());

	sprintf(strReturn, "%savgRemoveTime=%s$", strReturn, listPerf["RemoveTime"].c_str());

	sprintf(strReturn, "%sactiveMethods=%s$", strReturn, listPerf["ActiveMethodCount"].c_str());

	sprintf(strReturn, "%sgetsFromPool=%s$", strReturn, listPerf["RetrieveFromPoolCount"].c_str());

	sprintf(strReturn, "%sgetsFound=%s$", strReturn, listPerf["RetrieveFromPoolSuccessCount"].c_str());

	sprintf(strReturn, "%sreturnsToPool=%s$", strReturn, listPerf["ReturnsToPoolCount"].c_str());

	sprintf(strReturn, "%sreturnsDiscarded=%s$", strReturn, listPerf["ReturnsDiscardCount"].c_str());

	sprintf(strReturn, "%sdrainsFromPool=%s$", strReturn, listPerf["DrainsFromPoolCount"].c_str());

	sprintf(strReturn, "%savgDrainSize=%s$", strReturn, listPerf["DrainSize"].c_str());

	sprintf(strReturn, "%spoolSize=%s$", strReturn, "0");

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL JVM(const char * strParas, char * strReturn, int& nSize)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");
	
	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );

	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "JVM ����ʱ")) && (0 != strcmp(statElement->Attribute("name"), "JVM Runtime"))))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}


	long nValue = 0;
	double dValue = 0;
	double percentMemory;

	nValue = atol(listPerf["FreeMemory"].c_str());
	dValue = nValue/1024.00;
	sprintf(strReturn, "%sfreeMemory=%.2f$", strReturn, dValue);

	nValue = atol(listPerf["UsedMemory"].c_str());
	percentMemory = nValue;       //percentMemory ��ʱ����������Ҫ����ķ���ֵ
	dValue = nValue/1024.00;
	sprintf(strReturn, "%susedMemory=%.2f$", strReturn, dValue);

	nValue = atol(listPerf["HeapSize"].c_str());
	percentMemory = 100 * percentMemory / nValue;
	dValue = nValue/1024.00;
	sprintf(strReturn, "%stotalMemory=%.2f$", strReturn, dValue);

	sprintf(strReturn, "%spercentMemory=%.2f$", strReturn, percentMemory);

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL ThreadPool(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "�̳߳�")) && (0 != strcmp(statElement->Attribute("name"), "Thread Pools"))))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	sprintf(strReturn, "%sthreadCreates=%s$", strReturn, listPerf["CreateCount"].c_str());

	sprintf(strReturn, "%sthreadDestroys=%s$", strReturn, listPerf["DestroyCount"].c_str());

	sprintf(strReturn, "%sactiveThreads=%s$", strReturn, listPerf["ActiveCount"].c_str());

	sprintf(strReturn, "%spoolSize=%s$", strReturn, listPerf["PoolSize"].c_str());

	sprintf(strReturn, "%spercentMaxed=%s$", strReturn, listPerf["PercentMaxed"].c_str());

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL ConnectionPool(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		OutputDebugString("���ڴ����У��ļ�����");
		OutputDebugString(xmlFileName);
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		return FALSE;
	}
	OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
	OutputDebugString("�ҳ�����");
	OutputDebugString(xmlFileName);
	OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "JDBC ���ӳ�")) && (0 != strcmp(statElement->Attribute("name"), "JDBC Connection Pools"))))
	{
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		OutputDebugString(statElement->Attribute("name"));
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->FirstChildElement()->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	sprintf(strReturn, "%snumCreates=%s$", strReturn, listPerf["CreateCount"].c_str());
	sprintf(strReturn, "%snumDestroys=%s$", strReturn, listPerf["CloseCount"].c_str());
	sprintf(strReturn, "%snumAllocates=%s$", strReturn, listPerf["AllocateCount"].c_str());
	sprintf(strReturn, "%snumReturns=%s$", strReturn, listPerf["ReturnCount"].c_str());
	sprintf(strReturn, "%spoolSize=%s$", strReturn, listPerf["PoolSize"].c_str());
	sprintf(strReturn, "%sconcurrentWaiters=%s$", strReturn, listPerf["WaitingThreadCount"].c_str());
	sprintf(strReturn, "%savgWaitTime=%s$", strReturn, listPerf["WaitTime"].c_str());
	sprintf(strReturn, "%spercentUsed=%s$", strReturn, listPerf["PercentUsed"].c_str());
	sprintf(strReturn, "%spercentMaxed=%s$", strReturn, listPerf["PercentMaxed"].c_str());
	sprintf(strReturn, "%sprepStmtCacheDiscards=%s$", strReturn, listPerf["PrepStmtCacheDiscardCount"].c_str());
	
	strInput = strReturn;
	OutputDebugString("\n+++++++++++++++++++++++++++++����ֵ+++++++++++++++++++++++++++++\n");
	OutputDebugString("strReturn");
	OutputDebugString("\n+++++++++++++++++++++++++++++����ֵ+++++++++++++++++++++++++++++\n");
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL WebApp(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && (0 != strcmp(statElement->Attribute("name"), "Web Applications")))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	sprintf(strReturn, "%snumLoadedServlets=%s$", strReturn, listPerf["LoadedServletCount"].c_str());
	sprintf(strReturn, "%snumReloads=%s$", strReturn, listPerf["ReloadCount"].c_str());
	sprintf(strReturn, "%stotalRequests=%s$", strReturn, listPerf["RequestCount"].c_str());
	sprintf(strReturn, "%sconcurrentRequests=%s$", strReturn, listPerf["ConcurrentRequests"].c_str());
	sprintf(strReturn, "%sresponseTime=%s$", strReturn, listPerf["ServiceTime"].c_str());
	sprintf(strReturn, "%snumErrors=%s$", strReturn, listPerf["ErrorCount"].c_str());

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL ServletSessions(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "Servlet �Ự������")) && (0 != strcmp(statElement->Attribute("name"), "Servlet Session Manager"))))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	sprintf(strReturn, "%screatedSessions=%s$", strReturn, listPerf["CreateCount"].c_str());

	sprintf(strReturn, "%sinvalidatedSessions=%s$", strReturn, listPerf["InvalidateCount"].c_str());

	sprintf(strReturn, "%ssessionLifeTime=%s$", strReturn, listPerf["LifeTime"].c_str());

	sprintf(strReturn, "%sactiveSessions=%s$", strReturn, listPerf["ActiveCount"].c_str());

	sprintf(strReturn, "%sliveSessions=%s$", strReturn, listPerf["LiveCount"].c_str());

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Transaction(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //����ת������ֵstrReturn����ʱ����

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_Url",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL����Ϊ��$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//����xml�ļ�
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//����XML�ļ�
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=��xml�ļ�ʧ�ܣ���鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = statRootElement->FirstChildElement();
	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "���������")) && (0 != strcmp(statElement->Attribute("name"), "Transaction Manager"))))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=�Ҳ�����ѡ��Ŀ����鿴�����Ƿ���ȷ$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	sprintf(strReturn, "%sglobalTransBegun=%s$", strReturn, listPerf["GlobalBegunCount"].c_str());

	sprintf(strReturn, "%sglobalTransInvolved=%s$", strReturn, listPerf["GlobalInvolvedCount"].c_str());

	sprintf(strReturn, "%slocalTransBegun=%s$", strReturn, listPerf["LocalBegunCount"].c_str());

	sprintf(strReturn, "%sactiveGlobalTrans=%s$", strReturn, listPerf["ActiveCount"].c_str());

	sprintf(strReturn, "%sactiveLocalTrans=%s$", strReturn, listPerf["LocalActiveCount"].c_str());

	sprintf(strReturn, "%sglobalTranDuration=%s$", strReturn, listPerf["GlobalTranTime"].c_str());


	sprintf(strReturn, "%slocalTranDuration=%s$", strReturn, listPerf["LocalTranTime"].c_str());

	sprintf(strReturn, "%sglobalBeforeCompletionDuration=%s$", strReturn, listPerf["GlobalBeforeCompletionTime"].c_str());

	sprintf(strReturn, "%sglobalPrepareDuration=%s$", strReturn, listPerf["GlobalPrepareTime"].c_str());

	sprintf(strReturn, "%sglobalCommitDuration=%s$", strReturn, listPerf["GlobalCommitTime"].c_str());

	sprintf(strReturn, "%slocalBeforeCompletionDuration=%s$", strReturn, listPerf["LocalBeforeCompletionTime"].c_str());

	sprintf(strReturn, "%slocalCommitDuration=%s$", strReturn, listPerf["LocalCommitTime"].c_str()); 


	sprintf(strReturn, "%snumOptimization=%s$", strReturn, listPerf["OptimizationCount"].c_str());

	sprintf(strReturn, "%sglobalTransCommitted=%s$", strReturn, listPerf["CommittedCount"].c_str());

	sprintf(strReturn, "%slocalTransCommitted=%s$", strReturn, listPerf["LocalCommittedCount"].c_str());

	sprintf(strReturn, "%sglobalTransRolledBack=%s$", strReturn, listPerf["RolledbackCount"].c_str());

	sprintf(strReturn, "%slocalTransRolledBack=%s$", strReturn, listPerf["LocalRolledbackCount"].c_str());

	sprintf(strReturn, "%sglobalTransTimeout=%s$", strReturn, listPerf["GlobalTimeoutCount"].c_str());

	sprintf(strReturn, "%slocalTransTimeout=%s$", strReturn, listPerf["LocalTimeoutCount"].c_str());

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}