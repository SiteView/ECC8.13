// smsdll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <string>

using namespace std;

void WriteLog(char *app)
{
	FILE *fp;
	fp=fopen("msdelog.txt","a+");
	fprintf(fp,app);
	fclose(fp);

}

void InsertDatabase(char *source, char *destination, char *content)
{
	char connstr[50];
	char buf[256];
	HKEY hKey;

	string inputparam[32];
	char * buf1 = strdup(source);
	char * token = NULL;

	token = strtok(buf1 , " ");    
	int i = 0;

    while( token != NULL )
    {
        inputparam[i] = token;
        token = strtok( NULL , " ");
		i++;
    }

	if(strcmp(inputparam[1].c_str(), "") == 0 )
	{
		WriteLog("msde content is error!");
		return;
	}
	else
	{
		
		sprintf(buf, "source: %s destination: %s content: %s  inputparam[0]: %s inputparam[1]: %s inputparam[2]: %s\n", source, destination, content, inputparam[0].c_str(), inputparam[1].c_str(), inputparam[2].c_str());
		WriteLog(buf);
	}
//CString connstr1="driver={SQL Server};Server=192.168.6.39;DATABASE=DB_CustomSMS;UID=sa;PWD=11";
//	CString connstr1 = "DSN=testmsde;UID=sa;PWD=11";
	CString connstr1 = "driver={SQL Server};Server=";

	
	connstr1 += inputparam[0].c_str();
	connstr1 += ";DATABASE=DB_CustomSMS;UID=";
	connstr1 += inputparam[1].c_str();
	connstr1 += ";PWD=";
	connstr1 += inputparam[2].c_str();
	connstr1 += ";";
	

	//CString connstr1 = "DSN=testmsde;";
	free(buf1);
	//Driver={Microsoft ODBC for Oracle};Server=OracleServer.world;Uid=Username;Pwd=asdasd;" 
	//connstr1 += "Server=192.168.6.110;DATABASE=DB_CustomSMS;UID=sa;PWD=";//,"","",adModeUnknown";

   _ConnectionPtr pConn;
   _RecordsetPtr pRec;
   HRESULT hr;

   hr = pConn.CreateInstance(_uuidof(Connection));
   if(FAILED(hr))
   {
		return;
   }
   else
   {
   }

   hr = pRec.CreateInstance(_uuidof(Recordset));
   if(FAILED(hr))
   {
		return;
   }
   else
   {
   }


   try{
		_bstr_t connstr2 = connstr1;

		hr = pConn->Open(connstr2, "", "", -1);
		if(FAILED(hr))
		{
				return;
		}
		else
		{

		}
   }
   catch(_com_error &e)
	{
		OutputDebugString("-----------------connect open exception-------------------\n");
		OutputDebugString(connstr1.GetBuffer());
	CString stemp ;
	stemp = "m_pDataRs指针创建实例失败";
	stemp += e.ErrorMessage();
	OutputDebugString(stemp.GetBuffer());
	OutputDebugString("\n");

	}

 /*  catch(...)
   {

		OutputDebugString("-----------------connect open exception-------------------\n");
		OutputDebugString(connstr1.GetBuffer());
		OutputDebugString("\n");
   }
*/	
   hr = pRec->Open("SELECT * FROM tbl_SMToSend",pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
   if(FAILED(hr))
   {
		return;
   }
   else
   {

   }

   try{
   pRec->AddNew();

   CComVariant temp = destination;

   pRec->PutCollect(_variant_t("OrgAddr"), (_variant_t)temp);

	CTime time = CTime::GetCurrentTime();
	COleDateTime m_time(time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

	temp = m_time;
	pRec->PutCollect(_variant_t("SubTime"), (_variant_t)temp);

   temp = destination;
   pRec->PutCollect(_variant_t("DestAddr"), (_variant_t)temp);
   
 //  string stemp = content;
 //  stemp += "test user error add";
   temp = content;
  // temp = stemp.c_str();
   pRec->PutCollect(_variant_t("SM_Content"), (_variant_t)temp);
    
   temp = m_time;
   pRec->PutCollect(_variant_t("SendTime"), (_variant_t)temp);
	
   temp = 0;
   pRec->PutCollect(_variant_t("TryTimes"), (_variant_t)temp);

   temp = 0;
   pRec->PutCollect(_variant_t("NeedStateReport"), (_variant_t)temp);

   temp = "Siteview user";
   pRec->PutCollect(_variant_t("CreatorID"), (_variant_t)temp);

   temp = 0;
   pRec->PutCollect(_variant_t("SMType"), (_variant_t)temp);

   temp = "0";
   pRec->PutCollect(_variant_t("MessageID"), (_variant_t)temp);

   temp = 0;
   pRec->PutCollect(_variant_t("DestAddrType"), (_variant_t)temp);
  
   pRec->Update();
   }
   catch(...)
   {
	   OutputDebugString("-----------add update have exception---------\n");
   }

   pRec->Close();
   pConn->Close();	
   pRec = NULL;
   pConn = NULL;
  
 
}


extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "写MSDE数据库";
	return 1;
}

extern "C" __declspec(dllexport) int run(char * source, char * destination, char * content)
{
	char buf[256];

	::CoInitialize(NULL);
	InsertDatabase(source, destination, content);  
	 ::CoUninitialize();
	return 1;
}
void WriteLog(char * filename, char * log)
{

}
