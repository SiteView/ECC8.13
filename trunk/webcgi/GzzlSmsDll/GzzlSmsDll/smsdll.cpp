// smsdll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <list>
#include "Ado.h"
#include "AdoRecordSet.h"


#define OTL_ODBC // Compile OTL 4/ODBC
//#define OTL_ORA9I
#define OTL_STL // Turn on STL features
#ifndef OTL_ANSI_CPP
#define OTL_ANSI_CPP // Turn on ANSI C++ typecasts
#endif

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

void InsertDatabase(char *source, char *destination, char *content)
{

try
{
	OutputDebugString("\n++++++++++++++++++source++++++++++++++++++++++++++\n");
	OutputDebugString(source);
	OutputDebugString("\n++++++++++++++++++sxc++++++++++++++++++++++++++\n");
	CString strConn = _T("");
	CString strLog = _T("");
	COleDateTime date = COleDateTime::GetCurrentTime();

	CTime tm = CTime::GetCurrentTime();
	CString stm = tm.Format("%Y-%m-%d %H:%M:%S");

	char * token = NULL;

	
	CAdoConnection m_adoCon;
	CAdoRecordSet m_adoRst;
	CString udl;
	udl.Format(_T("%s"),source);



	if(m_adoCon.OpenUDLFile(udl))
//	if (m_adoCon.Open("DSN=s;Database=GZFK;uid=sa;pwd=;"))
	{				
            //要插入类似的短信 insert into flagsend(tophone,send,comeflag) values('13697470055','短信测试内容',400)
			CString strExec1 = "insert into flagsend(tophone,send,comeflag) values('";
			strExec1 += destination;
			strExec1 += "','";				
			CString csutf;
			csutf.Format(_T("%s"),content);

			OutputDebugString(csutf);
			OutputDebugString("\n");
			
			strExec1 += csutf;
			strExec1 += "',400";
			strExec1 += ")";
			m_adoCon.Execute((LPCTSTR)strExec1);

			OutputDebugString(strExec1);
			OutputDebugString("\n");
	}
	else
	{		
		OutputDebugString("--------------database Open failed--------------\n");
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
}



extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "广州招考短信发送";
	return 1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++苏合 2007-09-04+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//此DLL文件的接口方法，用于发送短信                                                                                                   +
//参数：                                                                                                                              +
//   [in] source          发送短信的参数                                                                                              +
//   [in] destination     发送短信的目的手机号码                                                                                      +
//   [in] content         要发送的短信内容                                                                                            +
//                                                                                                                                    +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern "C" __declspec(dllexport) int run(char *source, char *destination, char *content)
{
	::CoInitialize(NULL);
	try
	{
		puts("--------------正在写入数据库-----------------");
		//InsertDatabase5(source,destination, content);
		InsertDatabase(source,destination, content);
	}
	catch(...)
	{
		DebugePrint("-----------insert sms_database failure-------------\n");
	}
	 ::CoUninitialize();
	return 1;
}
