// smsdll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <list>
#include "oracledsnset.h"
#include "Ado.h"
#include "AdoRecordSet.h"


#define OTL_ODBC // Compile OTL 4/ODBC
//#define OTL_ORA9I
#define OTL_STL // Turn on STL features
#ifndef OTL_ANSI_CPP
#define OTL_ANSI_CPP // Turn on ANSI C++ typecasts
#endif
#include "otlv4.h"

using namespace std;

//#define DebugToFile

void DebugePrint(string strDebugInfo)
{
	#ifndef DebugToFile
		printf(strDebugInfo.c_str());
	#else
		printf(strDebugInfo.c_str());
		FILE *fp;
		//fp=fopen("\\Release\\debug.txt","a+");
		fp=fopen("debug.txt","a+");
		fprintf(fp, strDebugInfo.c_str());
		fclose(fp);		
	#endif
}

void WriteLog(char *app)
{
	FILE *fp;
	fp=fopen("sms_database.txt","a+"); //oraclelog
	fprintf(fp,app);
	fclose(fp);

}

bool ParserToLength(list<string >&pTokenList, string  strQueryString, int nLength)
{
	//从源串中取得子串，要避免把中文字符一劈为二。
	if( nLength%2 )
		nLength--;
	int nCount = strQueryString.length() / nLength;

	for(int i = 0; i <= nCount; i++)
	{
		int tlen=nLength;
		unsigned char tempchar= (unsigned char)strQueryString[tlen-1];
		while( tempchar>0xa0 && tempchar<0xfe )
		{
			tlen--;
			if( tlen< 0 )
			{
				tlen=0;
				break;
			}
			tempchar= (unsigned char)strQueryString[tlen-1];
		}
		if( (nLength-tlen)%2 )
			tlen=nLength-1;
		else
			tlen=nLength;
		string strTmp = strQueryString.substr(0, tlen);
		pTokenList.push_back(strTmp);
		strQueryString.erase(0, tlen);
	}
	return true;
}

/*void InsertDatabase5(char *source,char *destination,char *content)
{
	//Provider=Sybase.ASEOLEDBProvider.2;Server Name=myASEserver;Server Port Address=5000;Initial Catalog=myDataBase;User ID=myUsername;Password=myPassword;
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

	CString connstr1 = "Provider=Sybase.ASEOLEDBProvider.2;Server Name=";
	connstr1 += inputparam[0].c_str();
	connstr1 += ";Server Port Address=";
	connstr1 += inputparam[1].c_str();
	connstr1 += ";Initial Catalog=";
	connstr1 += inputparam[2].c_str();
	connstr1 += ";User ID=";
	connstr1 += inputparam[3].c_str();
	connstr1 += ";Password=";
	connstr1 += inputparam[4].c_str();
	OutputDebugString(connstr1);
	free(buf1);

   _ConnectionPtr m_pConnection;
   _RecordsetPtr m_pRecordset;

   HRESULT hr;
   try
   {
	   hr = m_pConnection.CreateInstance("ADODB.Connection");
	   if(SUCCEEDED(hr))
	   {
		   m_pConnection->ConnectionTimeout = 15;
		   m_pConnection->Open((_bstr_t)connstr1, "", "", adModeUnknown);
		   try
		   {
			   hr =  m_pRecordset.CreateInstance(__uuidof(Recordset));
			   if(SUCCEEDED(hr))
			   {
				   try
				   {
					   hr = m_pRecordset->Open("select  * from sss",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
				   }
				   catch(_com_error *e)
				   {
					   AfxMessageBox(e->ErrorMessage());
				   }
				   if(SUCCEEDED(hr))
				   {
					  try
					   {
						   m_pRecordset->AddNew();
						   
						   CComVariant temp = " ";
						   CTime time = CTime::GetCurrentTime();
						   COleDateTime m_time(time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
						   temp = m_time;
						   m_pRecordset->PutCollect(_variant_t("RecordTime"), (_variant_t)temp);

						   temp = "1234";
						   m_pRecordset->PutCollect(_variant_t("MeterID"), (_variant_t)temp);

						   temp = "warning";
						   m_pRecordset->PutCollect(_variant_t("AlertType"), (_variant_t)temp);

						   temp = destination;
						   m_pRecordset->PutCollect(_variant_t("CellNumber"), (_variant_t)temp);

						   temp = content;
						   m_pRecordset->PutCollect(_variant_t("Content"), (_variant_t)temp);

						   temp = "0";
						   m_pRecordset->PutCollect(_variant_t("flag"), (_variant_t)temp);

						   m_pRecordset->Update();
					   }
					   catch(_com_error e)
					   {
						   CString errormessage;
						   errormessage.Format("数据添加失败!\r\n错误信息:%s",e.ErrorMessage());
						   AfxMessageBox(errormessage);
					   }
				   }
			   }
		   }
		   catch(_com_error e)
		   {
			   CString errormessage;
			   errormessage.Format("数据集打开失败!\r\n错误信息:%s",e.ErrorMessage());
			   AfxMessageBox(errormessage);
		   }
	   }
   }
   catch(_com_error e)
   {
	   CString errormessage;
	   errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
	   AfxMessageBox(errormessage);
   }

   m_pRecordset->Close();
   m_pConnection->Close();	
   m_pRecordset = NULL;
   m_pConnection = NULL;

}

*/
void InsertDatabase(char *source, char *destination, char *content)
{
	//OutputDebugString("------------start InsertDatabase() call------------\n");
	//WriteLog("------------start InsertDatabase() call------------\n");

	//DebugePrint("--------------oracle input source-------------\n");
	//DebugePrint(source);
	//DebugePrint("--------------oracle input destination-------------\n");
	//DebugePrint(destination);
	//DebugePrint("--------------oracle input content-------------\n");
	//DebugePrint(content);

	/*otl_connect db;
	CString strConn = _T("");
	CString strLog = _T("");
	otl_conn::initialize();
//	strConn.Format("%s/%s@%s", uid, pwd, dbconn);


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

	strConn.Format("UID=%s;PWD=%s;DSN=%s;QTO=F;APA=T;", inputparam[0].c_str(), inputparam[1].c_str(), inputparam[2].c_str());
	OutputDebugString("--------------oracle connect string---------------\n");
	OutputDebugString(strConn.GetBuffer());
	OutputDebugString("\n");
	//try
	{
		db.rlogon(strConn.GetBuffer(1));
		//otl_stream i(100, // buffer size
        //      "SELECT tablespace_name FROM DBA_TABLESPACES",
        //      db // connect object 
        //     );
		list<string> listSmsContent;
		ParserToLength(listSmsContent, content, 138);
		list<string>::iterator listSmsContentItem;
		string tcontent;
		for(listSmsContentItem = listSmsContent.begin(); listSmsContentItem!=listSmsContent.end(); listSmsContentItem++)
		{
			tcontent = *listSmsContentItem;
			CString insertstr = "INSERT INTO SMSUSER.SM_SEND_LR "
				"(SENDID ,FILIALEID, FUNCTIONID, MOBILE, WORKNO, CONTENT, COMMITTIME, SENDTIME, STATUS, SPFLAG)"
				"VALUES('0' ,'0','99', '";
			insertstr += destination;
			insertstr += "', '";
			insertstr += "1619";
			insertstr += "', '";
			insertstr += tcontent.c_str();
			insertstr += "', ";
			CTime tm = CTime::GetCurrentTime();
			CString stm = tm.Format("%Y-%m-%d %H:%M");
			insertstr += "TO_DATE('";
			insertstr += stm;
			insertstr += "', 'yyyy-mm-dd HH24:MI'), ";
			insertstr += "TO_DATE('";
			insertstr += stm;
			insertstr += "', 'yyyy-mm-dd HH24:MI'), ";
			insertstr += "'0', '0')";		

			WriteLog(insertstr.GetBuffer());
			WriteLog("\n");

			OutputDebugString("--------------oracle insert string---------------\n");
			OutputDebugString(insertstr.GetBuffer());
			OutputDebugString("\n");

			otl_stream i(1,
				insertstr.GetBuffer(),
				db);
			char szTableSpaceName[256] = {0};
			
			while(!i.eof())
			{
				i>>szTableSpaceName;
				//lstTexts.AddTail(szTableSpaceName);
				//lstValues.AddTail(szTableSpaceName);
				OutputDebugString("------------oracle table name output------------\n");
				OutputDebugString(szTableSpaceName);
				OutputDebugString("\n");				
			}
			i.close();
		}		
	}
	*/
	
	
/*	char connstr[50];
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

	//CString connstr1 = "driver={Microsoft ODBC for Oracle};Server=";
	CString connstr1 = "Provider=OraOLEDB.Oracle;Data Source=";
	connstr1 += inputparam[2].c_str();
	connstr1 += ";Persist  Security  Info=True;User ID=";
	connstr1 += inputparam[0].c_str();
	connstr1 += ";Password=";
	connstr1 += inputparam[1].c_str();

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
	   OutputDebugString("----------------record createinstance  failure------------\n");
		return;
   }
   else
   {
	   OutputDebugString("----------------record createinstance success------------\n");
   }


   try{
		_bstr_t connstr2 = connstr1;

		OutputDebugString("------------oracle open connection start-------------\n");
		OutputDebugString(connstr1.GetBuffer());
		OutputDebugString("\n");

		 pConn->ConnectionTimeout   =   8;   

		hr = pConn->Open(connstr2, "", "", -1);
		OutputDebugString("------------oracle open connection end---------------\n");
		if(FAILED(hr))
		{
				OutputDebugString("----------------open connection oracle failure------------\n");
				return;
		}
		else
		{
			OutputDebugString("----------------open connection oracle success------------\n");
		}
   }
   catch(...)
   {
		OutputDebugString("-----------------oracle open exception--------------\n");
		OutputDebugString(connstr1.GetBuffer());
		OutputDebugString("\n");
   }
	
   //hr = pRec->Open("SELECT * FROM tbl_SMToSend",pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
   hr = pRec->Open("SELECT * FROM SMSUSER.SM_SEND_LR", pConn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
   if(FAILED(hr))
   {
		return;
   }
   else
   {

   }

   try{
   pRec->AddNew();

   CComVariant temp = " ";

   pRec->PutCollect(_variant_t("SENDID"), (_variant_t)temp);

	CTime time = CTime::GetCurrentTime();
	COleDateTime m_time(time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

	temp = m_time;
	pRec->PutCollect(_variant_t("COMMITTIME"), (_variant_t)temp);

   temp = " ";
   pRec->PutCollect(_variant_t("FILIALEID"), (_variant_t)temp);
   
   temp = " ";
   pRec->PutCollect(_variant_t("FUNCTIONID"), (_variant_t)temp);

   temp = destination;
   pRec->PutCollect(_variant_t("MOBILE"), (_variant_t)temp);

   temp = content;
   pRec->PutCollect(_variant_t("CONTENT"), (_variant_t)temp);
    
   temp = m_time;
   pRec->PutCollect(_variant_t("SENTTIME"), (_variant_t)temp);
	
   temp = "1";
   pRec->PutCollect(_variant_t("STATUS"), (_variant_t)temp);

   temp = "1";
   pRec->PutCollect(_variant_t("SPFLAG"), (_variant_t)temp);

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
  
 */
	try
	{
		CString strConn = _T("");
		CString strLog = _T("");

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

		//DSN=oracle1;UID=SMSUSER;PWD=KENNY;
		CString connstr = "DSN=";
		connstr += inputparam[2].c_str();
		connstr += ";UID=";
		connstr += inputparam[0].c_str();
		connstr += ";PWD=";
		connstr += inputparam[1].c_str();

		
		//OutputDebugString("----------oracle insert start-----------\n");
		//DebugePrint("----------oracle insert start-----------\n");
	//	CoracledsnSet oracleset(NULL, connstr);

		list<string> listSmsContent;
//		ParserToLength(listSmsContent, content, 138);
		list<string>::iterator listSmsContentItem;
		string tcontent;
		
		CDatabase db;
		bool bRet = db.OpenEx(connstr,CDatabase::noOdbcDialog);

		if(bRet)
		{
			for(listSmsContentItem = listSmsContent.begin(); listSmsContentItem!=listSmsContent.end(); listSmsContentItem++)
			{			

				//tcontent = *listSmsContentItem;
				//oracleset.Open(CRecordset::dynaset);
				//oracleset.AddNew();		
				//oracleset.m_SENDID = "0";
				//oracleset.m_FILIALEID = "0";
				//oracleset.m_FUNCTIONID = "99";
				//oracleset.m_MOBILE = destination;
				//oracleset.m_WORKNO = "1619";
				//oracleset.m_CONTENT = tcontent.c_str();
				//oracleset.m_COMMITTIME = CTime::GetCurrentTime();
				//oracleset.m_SENDTIME = CTime::GetCurrentTime();
				//oracleset.m_STATUS = "0";
				//oracleset.m_SPFLAG = "0";
				//oracleset.Update();
				//oracleset.Close();

				tcontent = (*listSmsContentItem).c_str();

				//DebugePrint("--------------oracle insert destination-------------\n");
				//DebugePrint(destination);
				//OutputDebugString(destination);

				//DebugePrint("--------------oracle insert tcontent-------------\n");
				//DebugePrint(tcontent.c_str());
				//OutputDebugString(tcontent.c_str());

				CString strExec = "INSERT INTO SMSUSER.SM_SEND_LR (SENDID ,FILIALEID, FUNCTIONID, MOBILE, WORKNO, CONTENT)VALUES('0' ,'0','99', '";
				strExec += destination;
				strExec += "', '1619','";
				strExec += tcontent.c_str();
				strExec += "')";

				//DebugePrint("--------------oracle insert string-------------\n");				
				//OutputDebugString(strExec);

				db.ExecuteSQL(strExec);
				
				//DebugePrint("--------------oracle insert end-------------\n");
				//OutputDebugString("--------------oracle insert end1--------------\n");
			}

			db.Close();
		}
		else
		{		
			//OutputDebugString("--------------oracle Open failed--------------\n");
			//DebugePrint("--------------oracle Open failed-------------\n");
		}
	}
	//catch(...)
	catch(CDBException * e )
	{
		TCHAR  szCause[512];
		e->GetErrorMessage(szCause,512);

		//WriteLog("insert oracle database exception");
		//OutputDebugString("--------------insert oracle exception--------------\n");
		//DebugePrint("----------insert oracle exception------------\n");

		OutputDebugString(szCause);
		DebugePrint(szCause);
	}	
	catch(...)
	{
		OutputDebugString("--------------insert oracle other exception--------------\n");
		DebugePrint("----------insert oracle other exception------------\n");	
	}
}

//为广州电信短信开发所写
//ADO连sybase
void InsertDatabase4(char *source,char * destination,char *content)
{
	HKEY hKey;

	string inputparam[5];
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

	
    //Provider=Sybase.ASEOLEDBProvider.2;Initial Catalog=数据库名;User ID=用户名;Data Source=数据源;Extended Properties="";Server Name=ip地址;Network Protocol=Winsock;Server Port Address=5000;
	CString connstr = "Driver={Sybase ASE ODBC Driver};NetworkAddress=";
	connstr += inputparam[0].c_str();
	connstr += ",";
	connstr += inputparam[1].c_str();
	connstr += ";Db=";
	connstr += inputparam[2].c_str();
	connstr += ";Uid=";
	connstr += inputparam[3].c_str();	
	connstr += ";Pwd=";
	connstr += inputparam[4].c_str();
	
	_ConnectionPtr pConn;
	_RecordsetPtr pRec;
	HRESULT hr;
	
	hr = pConn.CreateInstance(__uuidof(Connection));
	if(FAILED(hr))
	{
		OutputDebugString("创建数据库Connection失败");
		return;
	}
	hr = pRec.CreateInstance(__uuidof(Recordset));

	if(FAILED(hr))
	{
		OutputDebugString("创建数据库Recordset失败");
		return;
	}
	try{
		
		_bstr_t connstr2 = connstr;
		pConn->ConnectionTimeout = 8;  
		hr = pConn->Open(connstr2, "", "", -1);
		
		if(FAILED(hr))	
		{
			OutputDebugString("数据库引擎连接失败");
			return;
		}

		CString sql = "select * from SMSInterface";
		hr = pRec->Open((_bstr_t)sql, pConn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		
		if(FAILED(hr))
		{
			OutputDebugString("打开数据库表记录失败");
			return;
		}
		else
		{
			try{
				
				CTime tm = CTime::GetCurrentTime();
				CString stm = tm.Format("%Y-%m-%d %H:%M:%S");
				_CommandPtr pCmd(__uuidof(Command));
				pCmd->put_ActiveConnection(_variant_t((IDispatch*)pConn));

				CString strExec1 = "INSERT INTO SMSInterface VALUES(convert(varchar(32),'"+stm+"',110) ,'1234','warning','";
				strExec1 += destination;
				strExec1 += "','";
				strExec1 += content;
				strExec1 += "',0";
				strExec1 += ")";

				pCmd->CommandText=(_bstr_t)strExec1;
				pCmd->Execute(NULL,NULL,adCmdText);
			}
			catch(...)
			{
				OutputDebugString("-----------add Record have exception---------\n");
			}
		}
		pRec->Close();
		pConn->Close();	
		pRec = NULL;
		pConn = NULL;

	}
	catch(...)
	{
		OutputDebugString("-----------------sybase open exception--------------\n");
		OutputDebugString(connstr.GetBuffer());
		OutputDebugString("\n");
	}

}


CString HexToBin(CString string)//将16进制数转换成2进制
{
	if( string == "0") return "0000";
	if( string == "1") return "0001";
	if( string == "2") return "0010";
	if( string == "3") return "0011";
	if( string == "4") return "0100";
	if( string == "5") return "0101";
	if( string == "6") return "0110";
	if( string == "7") return "0111";
	if( string == "8") return "1000";
	if( string == "9") return "1001";
	if( string == "a") return "1010";
	if( string == "b") return "1011";
	if( string == "c") return "1100";
	if( string == "d") return "1101";
	if( string == "e") return "1110";
	if( string == "f") return "1111";
	return "";
}


WCHAR *Gb2312ToUnicode(char *gbBuffer)  //GB2312 转换成　Unicode
{ 
	WCHAR *uniChar;
	uniChar = new WCHAR[1];
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,uniChar,1);
	return uniChar;
}

int BinToInt(CString string)//2进制字符数据转换成10进制整型
{
	int len =0;
	int tempInt = 0;
	int strInt = 0;
	for(int i =0 ;i < string.GetLength() ;i ++)
	{
		tempInt = 1;
		strInt = (int)string.GetAt(i)-48;
		for(int k =0 ;k < 7-i ; k++)
		{
			tempInt = 2*tempInt;
		}
		len += tempInt*strInt;
	}
	return len;
} 

char * UnicodeToUTF_8(WCHAR *UniChar) // Unicode 转换成UTF-8
{
	char *buffer;
	CString strOne;
	CString strTwo;
	CString strThree;
	CString strFour;
	CString strAnd;
	buffer = new char[3];
	int hInt,lInt;
	hInt = (int)((*UniChar)/256);
	lInt = (*UniChar)%256;
	CString string ;
	string.Format("%x",hInt);
	strTwo = HexToBin(string.Right(1));
	string = string.Left(string.GetLength() - 1);
	strOne = HexToBin(string.Right(1));
	string.Format("%x",lInt);
	strFour = HexToBin(string.Right(1));
	string = string.Left(string.GetLength() -1);
	strThree = HexToBin(string.Right(1));
	strAnd = strOne +strTwo + strThree + strFour;
	strAnd.Insert(0,"1110");
	strAnd.Insert(8,"10");
	strAnd.Insert(16,"10");
	strOne = strAnd.Left(8);
	strAnd = strAnd.Right(16);
	strTwo = strAnd.Left(8);
	strThree = strAnd.Right(8);
	*buffer = (char)BinToInt(strOne);
	buffer[1] = (char)BinToInt(strTwo);
	buffer[2] = (char)BinToInt(strThree);
	return buffer;
}     

CString BinToHex(CString BinString)//将2进制数转换成16进制
{
	if( BinString == "0000") return "0";
	if( BinString == "0001") return "1";
	if( BinString == "0010") return "2";
	if( BinString == "0011") return "3";
	if( BinString == "0100") return "4";
	if( BinString == "0101") return "5";
	if( BinString == "0110") return "6";
	if( BinString == "0111") return "7";
	if( BinString == "1000") return "8";
	if( BinString == "1001") return "9";
	if( BinString == "1010") return "a";
	if( BinString == "1011") return "b";
	if( BinString == "1100") return "c";
	if( BinString == "1101") return "d";
	if( BinString == "1110") return "e";
	if( BinString == "1111") return "f";
	return "";
}



char * translateCharToUTF_8(char *xmlStream, int len) 
{
	int newCharLen =0 ;
	int oldCharLen = 0;
	int revCharLen = len;
	char* newCharBuffer;
	char* finalCharBuffer;
	char *buffer ;
	CString string;
	buffer  = new char[sizeof(WCHAR)];
	newCharBuffer = new char[int(2*revCharLen)];//设置最大的一个缓冲区
	while(oldCharLen < revCharLen)
	{
		if( *(xmlStream + oldCharLen) >= 0)
		{
			*(newCharBuffer+newCharLen) = *(xmlStream +oldCharLen);
			newCharLen ++;
			oldCharLen ++;
		}//如果是英文直接复制就可以
		else
		{
			WCHAR *pbuffer = Gb2312ToUnicode(xmlStream+oldCharLen);
			buffer = UnicodeToUTF_8(pbuffer);
			*(newCharBuffer+newCharLen) = *buffer;
			*(newCharBuffer +newCharLen +1) = *(buffer + 1);
			*(newCharBuffer +newCharLen +2) = *(buffer + 2);
			newCharLen += 3;
			oldCharLen += 2;
			delete []pbuffer;
			delete []buffer;
		}
	}
	newCharBuffer[newCharLen] = '\0';
	CString string1 ;
	string1.Format("%s",newCharBuffer);
	finalCharBuffer = new char[newCharLen+1];
	memcpy(finalCharBuffer,newCharBuffer,newCharLen+1);
	delete []newCharBuffer;
	return finalCharBuffer;
}


void ConvertGBKToUtf8(CString &strGBK) 
{ 
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0); 
	unsigned short * wszUtf8 = new unsigned short[len+1]; 
	memset(wszUtf8, 0, len * 2 + 2); 
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, len); 
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL); 
	char *szUtf8=new char[len + 1]; 
	memset(szUtf8, 0, len + 1); 
	WideCharToMultiByte (CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL,NULL); 
	strGBK = szUtf8; 
	delete[] szUtf8; 
	delete[] wszUtf8; 
}

void ConvertUtf8ToGBK(CString &strUtf8) 
{ 
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0); 
	unsigned short * wszGBK = new unsigned short[len+1]; 
	memset(wszGBK, 0, len * 2 + 2); 
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, wszGBK, len); 
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL); 
	char *szGBK=new char[len + 1]; 
	memset(szGBK, 0, len + 1); 
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL); 
	strUtf8 = szGBK; 
	delete[] szGBK; 
	delete[] wszGBK; 
}

void InsertDatabase3(char *source, char *destination, char *content)
{

try
{
	CString strConn = _T("");
	CString strLog = _T("");
	COleDateTime date = COleDateTime::GetCurrentTime();

	CTime tm = CTime::GetCurrentTime();
	CString stm = tm.Format("%Y-%m-%d %H:%M:%S");
	string inputparam[100];
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

	list<string> listSmsContent;

	ParserToLength(listSmsContent, content, 256);
	list<string>::iterator listSmsContentItem;

	string tcontent;
	
	CAdoConnection m_adoCon;
	CAdoRecordSet m_adoRst;
	CString udl;
	udl.Format(_T("a.udl"));

	if(m_adoCon.OpenUDLFile(udl))
//	if (m_adoCon.Open("DSN=s;Database=GZFK;uid=sa;pwd=;"))
	{
		for(listSmsContentItem = listSmsContent.begin(); listSmsContentItem!=listSmsContent.end(); listSmsContentItem++)
		{			
			tcontent = (*listSmsContentItem).c_str();
			CString strExec1 = "INSERT INTO SMSInterface(RecordTime ,MeterID,AlertType,CellNumber,Content,flag) VALUES(convert(varchar(100),'"+stm+"',120) ,'1234','warning','";
			strExec1 += destination;
			strExec1 += "','";				
			CString csutf;
			csutf.Format(_T("%s"),tcontent.c_str());
//			csutf = "状态" + csutf;
			OutputDebugString(csutf);
			OutputDebugString("\n");
			
			strExec1 += csutf;
			strExec1 += "',0";
			strExec1 += ")";
			m_adoCon.Execute((LPCTSTR)strExec1);
			//OutputDebugString(strExec1);
			OutputDebugString(strExec1);
			OutputDebugString("\n");
		}
	}
	else
	{		
		OutputDebugString("--------------sybase Open failed--------------\n");
	}
}
catch(CDBException * e )
{
	TCHAR  szCause[512];
	e->GetErrorMessage(szCause,512);

	OutputDebugString(szCause);
	DebugePrint(szCause);
}	
catch(...)
{
	OutputDebugString("--------------insert sybase other exception--------------\n");
	DebugePrint("----------insert sybase other exception------------\n");	
}
///////////////////注释2007.6.13////////////  //
}



extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "写sybase数据库";
	return 1;
}

void InsertDatabase_2(char *source, char *destination, char *content); //给河北新禾科技的，2007-1-19 add by chenjiantang

//extern "C" __declspec(dllexport) int run(char * source, char * destination, char * content)
//{
//	char buf[256];
//
//	//WriteLog("------------start sms dll run function call--------------\n");
//	::CoInitialize(NULL);
//	try
//	{
//	InsertDatabase(source, destination, content);  //给汕头电力的， jiangxian
////	InsertDatabase3(source, destination, content);  //给广州供电局的，shennan
//	//InsertDatabase_2(source, destination, content);  //给河北新禾科技的,chenjiantang
//	}
//	catch(...)
//	{
//		DebugePrint("-----------insert sms_database failure-------------\n");
//	}
//	 ::CoUninitialize();
//	return 1;
//}

//给广州供电局的 shennan
//extern "C" __declspec(dllexport) int run(char *source, char *destination, WCHAR *content)
extern "C" __declspec(dllexport) int run(char *source, char *destination, char *content)
{
	::CoInitialize(NULL);
	try
	{
		puts("--------------正在写入sybase 数据库-----------------");
		//InsertDatabase5(source,destination, content);
		InsertDatabase3(source,destination, content);
	}
	catch(...)
	{
		DebugePrint("-----------insert sms_database failure-------------\n");
	}
	 ::CoUninitialize();
	return 1;
}



void WriteLog(char * filename, char * log)
{
/*
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

	CString connstr1 = "Provider=OraOLEDB.Oracle;Data Source=";
	connstr1 += inputparam[2].c_str();
	connstr1 += ";Persist  Security  Info=True;User ID=";
	connstr1 += inputparam[0].c_str();
	connstr1 += ";Password=";
	connstr1 += inputparam[1].c_str();
	free(buf1);

	_ConnectionPtr pConn;
	_RecordsetPtr pRec;
	HRESULT hr;

	hr = pConn.CreateInstance(__uuidof(Connection));
	if(FAILED(hr))
	{
		return;
	}
	hr = pRec.CreateInstance(__uuidof(Recordset));
	
	if(FAILED(hr))
	{
		return;
	}
	try{
		
		_bstr_t connstr2 = connstr1;
		pConn->ConnectionTimeout = 8;   
		hr = pConn->Open(connstr2, "", "", -1);
		
		if(FAILED(hr))	
		{
			return;
		}
		CString sql = "select * from SMSInterface";
		hr = pRec->Open((_bstr_t)sql, pConn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		
		if(FAILED(hr))
		{
			return;
		}
		else
		{
			try{
				
				 CTime tm = CTime::GetCurrentTime();
				 CString stm = tm.Format("%Y-%m-%d %H:%M:%S");
				 _CommandPtr pCmd(__uuidof(Command));
				 pCmd->put_ActiveConnection(_variant_t((IDispatch*)pConn));
				 
				 CString strExec1 = "INSERT INTO SMSInterface VALUES(SMSID.nextval ,to_date('"+stm+"','YYYY-MM-DD HH24:MI:SS'),'1234','warning','";
				 strExec1 += destination;
				 strExec1 += "','";
				 strExec1 += content;
				 strExec1 += "','1'";
				 strExec1 += ")";
				 
				 pCmd->CommandText=(_bstr_t)strExec1;
				 pCmd->Execute(NULL,NULL,adCmdText);
				 
			}
			catch(...)
			{
				OutputDebugString("-----------add update have exception---------\n");
			}
		}
		pRec->Close();
		pConn->Close();	
		pRec = NULL;
		pConn = NULL;

	}
	catch(...)
	{
		OutputDebugString("-----------------oracle open exception--------------\n");
		OutputDebugString(connstr1.GetBuffer());
		OutputDebugString("\n");
	}
*/
 
  
//---------------nan.shen--------------------------//
//source = "sys 888888 oracle1"
/*	try
	{
		CString strConn = _T("");
		CString strLog = _T("");

		CTime tm = CTime::GetCurrentTime();
		CString stm = tm.Format("%Y-%m-%d %H:%M:%S");
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
		//sybase
        //Driver={SYBASE ASE ODBC Driver};NA=Hostname,Portnumber;Uid=myUsername;Pwd=myPassword;
		
		//
		CString connstr = "DSN=";
		connstr += inputparam[2].c_str();
		connstr += ";UID=";
		connstr += inputparam[0].c_str();
		connstr += ";PWD=";
		connstr += inputparam[1].c_str();
		
		list<string> listSmsContent;
		ParserToLength(listSmsContent, content, 138);
		list<string>::iterator listSmsContentItem;
		string tcontent;
		
		CDatabase db;
		bool bRet = db.OpenEx(connstr,CDatabase::noOdbcDialog);
		
		if(bRet)
		{
			for(listSmsContentItem = listSmsContent.begin(); listSmsContentItem!=listSmsContent.end(); listSmsContentItem++)
			{			
				tcontent = (*listSmsContentItem).c_str();
				CString strExec1 = "INSERT INTO SMSInterface VALUES(SMSID.nextval ,to_date('"+stm+"','YYYY-MM-DD HH24:MI:SS'),'1234','warning','";
				strExec1 += destination;
				strExec1 += "','";
				strExec1 += tcontent.c_str();
				strExec1 += "','1'";
				strExec1 += ")";

				db.ExecuteSQL(strExec1);
			}

			db.Close();
		}
		else
		{		
			OutputDebugString("--------------oracle Open failed--------------\n");
		}
	}
	//catch(...)
	catch(CDBException * e )
	{
		TCHAR  szCause[512];
		e->GetErrorMessage(szCause,512);

		OutputDebugString(szCause);
		DebugePrint(szCause);
	}	
	catch(...)
	{
		OutputDebugString("--------------insert oracle other exception--------------\n");
		DebugePrint("----------insert oracle other exception------------\n");	
	}
*/	
//-----------------nan.shen------------------------------//
}


//以下是给河北新禾科技的，2007-1-19  add by chenjiantang
#include<ctime>
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include "../../kennel/svdb/libutil/Time.h"

int MyRand()
{
	unsigned int seed=GetTickCount();
	static unsigned int seed2=0;
	seed2 +=1111;
	srand( seed + seed2 );
	int ret= rand();
	ret %= 1000;
	return ret;
}

string GetSms_Id()
{
	time_t now_time2;
	now_time2 = time(NULL);
	char tmp2[256];
	strftime( tmp2, sizeof(tmp2), "%y%m%d%H%M%S", localtime(&now_time2) ); 
	string smsid=tmp2;

	std::ostringstream otemp1;
	unsigned int tick=GetTickCount();
	tick%= 1000;
	otemp1<<setw(3)<<setfill('0')<<tick;

	std::ostringstream otemp2;
	int rint=MyRand();
	otemp2<<setw(3)<<setfill('0')<<rint;

	smsid = smsid + otemp1.str() + otemp2.str();
	return smsid;
}


void InsertDatabase_2(char *source, char *destination, char *content)
{
	OutputDebugString("------------start InsertDatabase() call------------\n");
	//WriteLog("------------start InsertDatabase() call------------\n");

	CString connstr, strExec;
	
	chen::TTime now_time;

	try{
		CString strConn = _T("");
		CString strLog = _T("");

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

		connstr = "DSN=";
		connstr += inputparam[0].c_str();
		connstr += ";UID=";
		connstr += inputparam[1].c_str();
		connstr += ";PWD=";
		connstr += inputparam[2].c_str();
		string senderIP= inputparam[3].c_str(); 

		OutputDebugString("\n");
		OutputDebugString(content);
		OutputDebugString("\n");

		string sms_id_0=GetSms_Id();
		
		now_time= chen::TTime::GetCurrentTimeEx();

		string textout= "------------";
		textout += now_time.Format() + "      inserting ...   ";
		OutputDebugString(textout.c_str());
		//WriteLog( (char *)textout.c_str());

		list<string> listSmsContent;	
		//ParserToLength(listSmsContent, content, 58);
		list<string>::iterator listSmsContentItem;
		string tcontent;

		CDatabase db;
		bool bRet = db.OpenEx(connstr,CDatabase::noOdbcDialog);

		int count(0);
		for(listSmsContentItem = listSmsContent.begin(); listSmsContentItem!=listSmsContent.end(); listSmsContentItem++)
		{
			++count;
			if( count>99 )
				break;
			std::ostringstream otemp;
			otemp<<setw(2)<<setfill('0')<<count;
			string sms_id= sms_id_0 + otemp.str();

			tcontent= *listSmsContentItem;

			CString temps= tcontent.c_str();
			temps.Replace("\n","");
			temps.Replace("\r","");
			temps.Replace("'","''");
			tcontent= (LPCSTR)temps;
			if(tcontent.empty())
				continue;

			strExec = "insert into sms_tosend (sms_id,sms_cont,sms_tosend_time,send_type,sms_type_id,is_urgcy,sender_ip) values ('" ;
			strExec= strExec + sms_id.c_str() + "','" + tcontent.c_str() + "','" + (now_time.Format()).c_str();
			strExec= strExec + "','0','8888','1','" + senderIP.c_str() + "')";
			db.ExecuteSQL(strExec);

			strExec="insert into sms_tosend_user (sms_id,from_user_id,from_user_name,to_user_phone,to_user_name,rec_state) values ('";
			strExec= strExec + sms_id.c_str() + "','Super000000','网管系统','" + destination + "','"   + destination + "','0') ";
			db.ExecuteSQL(strExec);
		}
		db.Close();
		OutputDebugString(" succeeded. -----------\n");
		//WriteLog(" succeeded. -----------\n");
	}
	catch( CDBException * e )
	{
		TCHAR  szCause[512];
		e->GetErrorMessage(szCause,512);

		string failtext= szCause;
		failtext = failtext + "  " + (LPCSTR)connstr + " " +(now_time.Format()).c_str() + "\n" + (LPCSTR)strExec + "\n";
		WriteLog( (char *)failtext.c_str() );
		OutputDebugString( (char *)failtext.c_str() );
	}
	catch(...)
	{
		WriteLog("----------insert database exception------------\n");
		OutputDebugString("----------insert database exception------------\n");
	}
}//end of InsertDatabase_2

