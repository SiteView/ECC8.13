 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����������ࣺ
//    1�����ݽṹ
//		a��һ��AlertBaseObjList, ����Ϊ�������������ࡣ
//		b���ĸ�WaitSendAlertObjList, ����Ϊ�������Ͷ����ࡣ
//		c��һ������EventList, ����Ϊ�����¼��ࡣ
//		d���̣߳����롢�����
//    2����������
//		a����alert.ini�Գ�ʼ��AlertBaseObjList�� ���ֽ����ȷ��AlertTargetList��
//		b��ѭ����ȡ����Event��EventList��
//		c��ѭ������AlertBaseObjList��EventList���Eventƥ�䣬������AlertSendObj�����͵�WaitSendAlertObjList��
//		d��ѭ����WaitSendAlertObjList���ͳ�ȥ�� ά��WaitSendAlertObjList����¼��־��
//		e
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <typeinfo>
#include "AlertMain.h"
#include "AlertBaseObj.h"
#include "AlertSendObj.h"
#include "AlertEventObj.h"
#include <cc++/numbers.h>
#include "svapi.h"
#include "svdbapi.h"
#include "SerialPort.h"
//#import  < msxml4.dll > 

int nSendCount = 0;
static CSerialPort m_smsPort;
string CAlertMain::strDisable = "";
string CAlertMain::strNormal = "";
string CAlertMain::strWarning = "";
string CAlertMain::strError = "";
string CAlertMain::strOther = "";

string CAlertMain::strMontorFreq = "";
string CAlertMain::strHour = "";
string CAlertMain::strMinute = "";
string CAlertMain::strMonitorFazhi = "";

string CAlertMain::strWeiHuUserIdcId = "";
string CAlertMain::strSysWeihuUserIdcId = "";
string CAlertMain::strYeWuIdcId = "";
string CAlertMain::strXiaoshouIdcId = "";
int    CAlertMain::nSMSSendLength=50;//��ʼ�����ŷ��͵ĳ���
string    CAlertMain::strSMSSendURL;//���ŷ��ͷ������ĵ�ַ
string    CAlertMain::strSMSSendPort;//���ŷ��ͷ������Ķ˿�
//#define AddOnEventSever

#define DebugToFile

void DebugePrint(string strDebugInfo)
{

	#ifndef DebugToFile
		printf("%s\n",strDebugInfo.c_str());
	#else
		printf(strDebugInfo.c_str());
		FILE *fp;
		//fp=fopen("\\Release\\debug.txt","a+");
		fp=fopen("wuxinonghangdebug.txt","a+");
		fprintf(fp,"%s\n",strDebugInfo.c_str());
		fclose(fp);		
	#endif
	return;
}

#include "C:\SiteView\Ecc_Common\Base\des.h"
#include "afxinet.h"
#include "windows.h"

typedef unsigned char BYTE;

inline BYTE toHex(const BYTE &x)
{
	return x > 9 ? x + 55: x + 48;
}

string urlEncoding( string &sIn )
{
	string sOut;
	for( int ix = 0; ix < sIn.size(); ix++ )
	{
		BYTE buf[4];
		memset( buf, 0, 4 );
		if( isalnum( (BYTE)sIn[ix] ) )
		{
			buf[0] = sIn[ix];
		}
		else if ( isspace( (BYTE)sIn[ix] ) )
		{
			buf[0] = '+';
			cout << "sp" << endl;
		}
		else
		{
			buf[0] = '%';
			buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
			buf[2] = toHex( (BYTE)sIn[ix] % 16);
		}
		sOut += (char *)buf;
	}
	return sOut;
}

BOOL GetSourceHtml(char const * theUrl, char * retState) 
{
	CInternetSession session;
	CInternetFile* file = NULL;
	try
	{
		// �������ӵ�ָ��URL
		file = (CInternetFile*) session.OpenURL(theUrl); 
	}
	catch (...)
	{
		// ����д���Ļ���������Ϊ��
		strcpy(retState, "error");
		return FALSE;
	}

	if (file)
	{
		CString  somecode;

		bool flagReplace = false;
		int replaceNum = 0;
		while (file->ReadString(somecode) != NULL) //�������LPTSTR���ͣ���ȡ������nMax��0��ʹ�������ַ�ʱ����
		{
			strncpy(retState, somecode,1000);
		}

	}
	else
	{
		strcpy(retState, "error");
		return FALSE;
	}
	return TRUE;
}

 #include <list>
#import "msxml.dll" //�������Ϳ� 
bool WriteXML(string title,list<string> key,list<string> context,string filename)
{
	AfxOleInit(); 
	MSXML::IXMLDOMDocumentPtr pDoc; 
	// ����DOMDocument���� 
	HRESULT hr;
	hr   =   CoInitialize(NULL);   

	hr =pDoc.CreateInstance(__uuidof(MSXML::DOMDocument)); 

	if ( ! SUCCEEDED(hr)) 
	{  
		return  false;
	}  


	MSXML::IXMLDOMElementPtr xmlRoot=pDoc->createElement("title"); 
	pDoc->appendChild(xmlRoot);  

	// ���ڵ������Ϊtitle
	// ����Ԫ�ز���ӵ��ĵ��� 
	const _variant_t  var1;

	// �������� 
//	xmlRoot -> setAttribute( " id " ,( const   char   * )title.c_str());
//	pDoc -> appendChild(xmlRoot);
	MSXML::IXMLDOMElementPtr pNode;
	std::list<string>::iterator	 itkey,itcontext;
	itcontext=context.begin();
	for(itkey=key.begin();itkey!=key.end();itkey++)
	{
		// �����Ӧ��Ԫ�� 
		pNode = pDoc -> createElement((_bstr_t) (*itkey).c_str());
		pNode -> Puttext((_bstr_t)( const   char   * )(*itcontext).c_str());
		xmlRoot -> appendChild(pNode);
		itcontext++;
	}
	// ���浽�ļ� 
	// ��������ھͽ���,���ھ͸���  
	pDoc -> save( filename.c_str());
	CoUninitialize();
}

bool WebSmsTest(string phoneNumber, string content)
{
	bool bRet = true;

	string User("test");
	string Pwd("testpwd123");
	string RetValue("OK");
	string strWebHead;
	//�Ӷ���ģ���ж�������ͷ��ģ��
	strWebHead = GetIniFileString("WEBSMSFORMAT", "default", "", "TxtTemplate.Ini");

	User = GetIniFileString("SMSWebConfig", "User", "", "smsconfig.ini");
	Pwd = GetIniFileString("SMSWebConfig", "Pwd", "", "smsconfig.ini");
	string sendlength="50";
	sendlength = GetIniFileString("SMSWebConfig", "length", "", "smsconfig.ini");
	int nSMSSendLength=CAlertMain::nSMSSendLength;
	if (!sendlength.empty())
		sscanf(sendlength.c_str(),"%d",&nSMSSendLength);
	//����ֵ����������˸�ֵ�����ʾ������ȷ
	string strTmp;
	strTmp = GetIniFileString("SMSWebConfig", "Return", "", "smsconfig.ini");
	if (!strTmp.empty())
		RetValue=strTmp;


	Des mydes;
	char dechar[1024]={0};
	if(Pwd.size()>0)
	{
		mydes.Decrypt(Pwd.c_str(),dechar);
		Pwd = dechar;
	}
	//����Ӷ��ŷ��������͵�ͷ
	//�滻�û���������
	strTmp = CAlertMain::ReplaceStdString(strWebHead, "@UserName@", User);
	strWebHead=strTmp;
	strTmp = CAlertMain::ReplaceStdString(strWebHead, "@Pwd@", Pwd);
	strWebHead=strTmp;
	//�滻�ֻ�����
	strTmp = CAlertMain::ReplaceStdString(strWebHead, "@Phone@", phoneNumber);
	strWebHead=strTmp;
	std::list<string> listSms;
	std::list<string>::iterator listSmsItem;
	char * buf = new char[300];
//�滻����
	strTmp = CAlertMain::ReplaceStdString(strWebHead, "@Content@", content);
	strWebHead=strTmp;
	GetSourceHtml(strWebHead.c_str(), buf);
	//�ж��Ƿ�������
	strTmp=buf;
	string::size_type indexBeg;
	static const string::size_type npos = -1;
	indexBeg = strTmp.find(RetValue);
	if (indexBeg == npos)
		bRet=false;
	string testResult;
	if (bRet)
	{
		testResult="�ɹ�%������Ϣ�����ŷ���������\n";
	}
	else
	{
		testResult="ʧ��%���Ӷ��ŷ�����ʧ��\n";
	}

	//���ļ���д�뷵�ؽ��
	list<string> key,context;
	key.push_back("phone");
	key.push_back("result");
	context.push_back(phoneNumber);
	context.push_back(testResult);
	WriteIniFileString("websms","phone",phoneNumber,"smstestresult.ini");
	WriteIniFileString("websms","result",testResult,"smstestresult.ini");
	return bRet;	
}


//
CAlertMain::CAlertMain()
{
	receivethread = NULL;
	processthread = NULL;
	//sendthread = NULL;
	
	sendemailthread = NULL;
	sendsmsthread = NULL;
	sendscriptthread = NULL;
	sendsoundthread = NULL;
	waitlistmutex = NULL;
	//waitlistmutexreceive = NULL;
	event = NULL;
}

//
CAlertMain::~CAlertMain()
{
	if(receivethread != NULL)
		delete receivethread;
	if(processthread != NULL)
		delete processthread;
	
	//if(sendthread != NULL)
	//	delete sendthread;

	if(sendemailthread != NULL)
		delete sendemailthread;
	if(sendsmsthread != NULL)
		delete sendsmsthread;
	if(sendscriptthread != NULL)
		delete sendscriptthread;
	if(sendsoundthread != NULL)
		delete sendsoundthread;


	if(waitlistmutex != NULL)
		delete waitlistmutex;

	//if(waitlistmutexreceive != NULL)
	//	delete waitlistmutexreceive;
	 
	if(event != NULL)
		delete event;
	
	CAlertMain::UnloadSendApi();
	CAlertMain::UnloadSoundAlertCom();
	CAlertMain::UnloadScriptAlertCom();
	CAlertMain::UnloadWebSmsAlertCom();
}

//��ʼ��
bool CAlertMain::Init()
{

	OBJECT objRes=LoadResource("default", "localhost");  
	
	//��svdb�������˲�������...
	while(objRes == INVALID_VALUE)
	{
		::Sleep(60000);		
		objRes=LoadResource("default", "localhost");  
		//OutputDebugString(" wait");
		DebugePrint("----------wait for svdb---------------\r\n");
	}
    
	SetSvdbAddrByFile("svapi.ini");
	
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Disable",CAlertMain::strDisable);
			FindNodeValue(ResNode,"IDS_Normal",CAlertMain::strNormal);
			FindNodeValue(ResNode,"IDS_Warnning",CAlertMain::strWarning);
			FindNodeValue(ResNode,"IDS_Error",CAlertMain::strError);
			FindNodeValue(ResNode,"IDS_Other",CAlertMain::strOther);

			FindNodeValue(ResNode,"IDS_MontioFreq",CAlertMain::strMontorFreq);
			FindNodeValue(ResNode,"IDS_Hour",CAlertMain::strHour);
			FindNodeValue(ResNode,"IDS_Minute",CAlertMain::strMinute);
			FindNodeValue(ResNode,"IDS_Clique_Value",CAlertMain::strMonitorFazhi);
		}

		CloseResource(objRes);
	}

	//��ȡ���ŷ��͵����ò���
	ifstream input("smspara.ini", ios::in);
	string line; 
    if (input.is_open())
    {
		while(1) 
		{ 
			getline(input,line);
			if(!line.empty())
			{
				string beFindStr="smslength=";
				string::size_type nPos=line.find(beFindStr,0);
				string::size_type nLength=beFindStr.size();
				if(nPos!= string::npos)//����ҵ���smslength=����������ֵ
				{
					line.erase(0,nPos+nLength);
					sscanf(line.c_str(),"%d",&nSMSSendLength);
				}

				//������ŷ�������URL��ַ
				beFindStr="smsurl=";
				nPos=line.find(beFindStr,0);
				nLength=beFindStr.size();
				if(nPos!= string::npos)//����ҵ���smslength=����������ֵ
				{
					line.erase(0,nPos+nLength);
					strSMSSendURL=line;
				}

				//������ŷ������Ķ˿ں�
				beFindStr="smsport=";
				nPos=line.find(beFindStr,0);
				nLength=beFindStr.size();
				if(nPos!= string::npos)//����ҵ���smslength=����������ֵ
				{
					line.erase(0,nPos+nLength);
					strSMSSendPort=line;
				}
			}
			if (input.eof())
				break;
			
		}
	}
	input.close();
	//����
//	CAlertSmsSendObj alert;
//	alert.SendSmsFromWeb();
	//string strTmp = "��������SiteView��\r\n�����:		@Group@ : @monitor@   \r\n��:		@AllGroup@  \r\n״̬:		@Status@ \r\nʱ��:		@Time@\r\nLogFile���ݣ�  \r\n��@Log@��\r\n";
	//WriteIniFileString("Email", "Default", strTmp, "TxtTemplate.Ini");
	//WriteIniFileString("Email", "SelfDefine", strTmp, "TxtTemplate.Ini");
	//WriteIniFileString("Email", "LogTemplate", strTmp.c_str(), "TXTTemplate.Ini");

	//
	//string strTmp1 = "��������SiteView�������:@AllGroup@:@Group@:@monitor@ ״̬: @Status@  ʱ��: @Time@ \r\n";
	//string strTmp1 = "����:@monitor@ ״̬: @Status@  ʱ��: @Time@ \r\n";
	//WriteIniFileString("SMS", "SelfDefine", strTmp1, "TxtTemplate.Ini");
	//WriteIniFileString("SMS", "Default", strTmp1, "TxtTemplate.Ini");
	//WriteIniFileString("SMS", "JKLSMS", strTmp1, "TxtTemplate.Ini");

	//std::list<string> listSms;
	//std::list<string>::iterator listSmsItem;

	//string strTest = "��������SiteView�������:		SiteView7.0 : :localhost : Memory:localhost  ״̬: Memoryʹ����()=26.09, ʣ��ռ�(MB)=1135.23,  ����ҳ/��(ҳ/��)=0.00, �ڴ�����(MB)=1536.00,   ʱ��: 2006-8-22 11:40:01 ";
	// 
	//CAlertMain::ParserToLength(listSms, strTest, 140);
	//for(listSmsItem = listSms.begin(); listSmsItem!=listSms.end(); listSmsItem++)
	//{
	//	DebugePrint((*listSmsItem));
	//	DebugePrint("ParserToLength\r\n");
	//}

	//return false;
	//bool CreateQueue(string queuename,int type=1,string user="default",string addr="localhost");


	#ifdef AddOnEventSever
		CreateQueue("EventSeverInputQueue");//���������¼���EventSever��¼���� 
	#endif

	CreateQueue("ExportQueue");//���������¼���¼���� JIANG 10-16

	bool bInsert = InsertTable("alertlogs", 801);
	if(bInsert)
	{
		OutputDebugString(" InsertTable ok");	
	}
	else
	{
		OutputDebugString(" InsertTable failed");			
	}

	//string strTmp = GetIniFileString("Email", "Default", "", "TxtTemplate.Ini");
	//printf(strTmp.c_str());

	//////////////////////begin to modify at 07/07/31 /////////////////////////////
	//#ifdef IDC_Version
	//	strWeiHuUserIdcId = GetIniFileString("IdcUserCfg", "WeiHuUserIdcId", "", "general.ini");
	//	strSysWeihuUserIdcId = GetIniFileString("IdcUserCfg", "SysWeihuUserIdcId", "", "general.ini");
	//	strYeWuIdcId = GetIniFileString("IdcUserCfg", "YeWuIdcId", "", "general.ini");
	//	strXiaoshouIdcId = GetIniFileString("IdcUserCfg", "XiaoshouIdcId", "", "general.ini");
	//#endif

	if(GetCgiVersion().compare("IDC") == 0)
	{
		strWeiHuUserIdcId = GetIniFileString("IdcUserCfg", "WeiHuUserIdcId", "", "general.ini");
		strSysWeihuUserIdcId = GetIniFileString("IdcUserCfg", "SysWeihuUserIdcId", "", "general.ini");
		strYeWuIdcId = GetIniFileString("IdcUserCfg", "YeWuIdcId", "", "general.ini");
		strXiaoshouIdcId = GetIniFileString("IdcUserCfg", "XiaoshouIdcId", "", "general.ini");
	}
	//////////////////////modify end at 07/07/31 //////////////////////////////////


	CAlertMain::InitSendApi();
	//CAlertMain::InitWebSmsAlertCom();
	InitAlertObjList();
	
	bInitSerialPort = CAlertMain::InitSerialPort();

	//ReadCfgFromWatchIni();

	//����ͬ��
	waitlistmutex = new Mutex("");
	//waitlistmutexreceive = new Mutex("");

	//�����߳�ѭ����������
	receivethread = new ReceiveThread(this);
	receivethread->start();
	
	processthread = new ProcessThread(this);
	processthread->start();

	//sendthread = new SendThread(this);
	//sendthread->start();	

	sendemailthread = new SendEmailAlertThread(this);
	sendemailthread->start();
	sendsmsthread = new SendSmsAlertThread(this);
	sendsmsthread->start();
	sendscriptthread = new SendScriptAlertThread(this);
	sendscriptthread->start();
	sendsoundthread = new SendSoundAlertThread(this);
	sendsoundthread->start();
	
	//Datetime tm;
	//int nDay = tm.getDayOfWeek();
	//printf("dddddd");
	//printf("day of week %d", nDay);

	//sendpythonthread = new SendPythonAlertThread(this);
	//sendpythonthread->start();	
	return true;
}

//
void CAlertMain::DoReceive()
{
	bool bStop = false;
	CAlertEventObj * lastEventobj = NULL;

	while(!bStop)
	{
		//printf("DoReceive:");
		::Sleep(50);
		//���յ�m_AlertEventList

		//if(!waitlistmutex->test())
		//{
		//	continue;
		//}

		MQRECORD mrd;

		mrd=::BlockPopMessage("SiteView70-Alert");

		
		if(mrd!=INVALID_VALUE)
		{
			//puts("Pop message failed");

			string label;
			svutil::TTime ct;
			unsigned int len=0;

			if(!::GetMessageData(mrd, label, ct, NULL, len))
			{
				OutputDebugString("Get message data failed");
				//::CloseMQRecord(mrd);
				//waitlistmutex->leave();
				//continue;
			}

			//printf("Data len is :%d\n",len);
			char * buf = NULL;
			buf = new char[len];

			if(!::GetMessageData(mrd, label, ct, buf, len))
			{
				OutputDebugString("Get message data failed");
				//::CloseMQRecord(mrd);
				//waitlistmutex->leave();
				//continue;
			}
			
			::CloseMQRecord(mrd);
			

			//OutputDebugString(label.c_str());
			//OutputDebugString("\n");
			if(label == "WebSmsTest")
			{
				//����web���ŷ���
				OutputDebugString("Get message From SmsTest:\n");
				OutputDebugString(buf);

				string szSmsTo = "";
				szSmsTo += buf;
				std::list<string> listSms;
				std::list<string>::iterator listSmsItem;
				
				CAlertMain::ParserToken(listSms, szSmsTo.c_str(), ",");
				bool bSucess = false;
				bool bAllSucess = true;
				for(listSmsItem = listSms.begin(); listSmsItem!=listSms.end(); listSmsItem++)
					WebSmsTest((*listSmsItem), " This is a test!");	

			}
			else if(label == "SmsTest")
			{
				//���Զ��ŷ���
				OutputDebugString("Get message From SmsTest:\n");
				OutputDebugString(buf);

				string szSmsTo = "";
				szSmsTo += buf;
				std::list<string> listSms;
				std::list<string>::iterator listSmsItem;
				
				CAlertMain::ParserToken(listSms, szSmsTo.c_str(), ",");
				bool bSucess = false;
				bool bAllSucess = true;
				for(listSmsItem = listSms.begin(); listSmsItem!=listSms.end(); listSmsItem++)
				{
					CString strSmsTo = (*listSmsItem).c_str();

					CAlertMain::TestSmsFromComm(strSmsTo, " This is a Test3");	
				}

				//CAlertMain::SendSmsFromComm(buf, " This is a Test2");
				//continue;
			}
			else if(label == "IniChange")
			{
				#ifdef AddOnEventSever				
				::PushMessage("EventSeverInputQueue", label, buf, len); //�����¼���EventSever��¼���� 
				#endif

				//OutputDebugString(label.c_str());
				//OutputDebugString("\n");

				//�����ļ������仯
				string strIniName, strSection, strOperate;
				std::list<string> listIniParam;
				std::list<string>::iterator listIniParamItem;
				
				CAlertMain::ParserToken(listIniParam, buf, ",");
				
				strIniName = listIniParam.front();
				listIniParam.pop_front();
				strSection = listIniParam.front();
				listIniParam.pop_front();
				strOperate = listIniParam.front();				
				listIniParam.pop_front();

				OutputDebugString(strIniName.c_str());
				OutputDebugString("\n");
				OutputDebugString(strSection.c_str());
				OutputDebugString("\n");
				OutputDebugString(strOperate.c_str());
				OutputDebugString("\n");
				
				//�����ٽ���
				if(!waitlistmutex->test())
				{
					continue;
				}

				//////////////////////begin to modify at 07/07/31 /////////////////////////////
				//#ifdef IDC_Version
				if(GetCgiVersion().compare("IDC") == 0)
				{
				//////////////////////modify end at 07/07/31 //////////////////////////////////

					string strIniIdcId = listIniParam.front();
					listIniParam.pop_front();

					if(strIniName == "alert.ini")
					{
						//alert.ini	
						if(strOperate == "ADD")
						{
							//ADD
							ReadAlertObjFromIni(strSection, strIniIdcId);
						}
						else if(strOperate == "DELETE")
						{
							//DELETE
							DeleteAlertObjFromSection(strSection, strIniIdcId);
						}
						else
						{
							//EDIT UPDATE
							DeleteAlertObjFromSection(strSection, strIniIdcId);
							ReadAlertObjFromIni(strSection, strIniIdcId);
						}
					}
					else if(strIniName == "smsconfig.ini")
					{
						//smsconfig.ini
						//�Ƿ�Ƚ�һ�£�������
						CAlertMain::CloseSerialPort();
						bInitSerialPort = CAlertMain::InitSerialPort();
					}
					else
					{
						
					}

				//////////////////////begin to modify at 07/07/31 /////////////////////////////
				//#else
				}
				else
				{
				//////////////////////modify end at 07/07/31 //////////////////////////////////

					if(strIniName == "alert.ini")
					{
						//alert.ini	
						if(strOperate == "ADD")
						{
							//ADD
							ReadAlertObjFromIni(strSection);
						}
						else if(strOperate == "DELETE")
						{
							//DELETE
							DeleteAlertObjFromSection(strSection);
						}
						else
						{
							//EDIT UPDATE
							DeleteAlertObjFromSection(strSection);
							ReadAlertObjFromIni(strSection);
						}
					}
					else if(strIniName == "smsconfig.ini")
					{
						//smsconfig.ini
						//�Ƿ�Ƚ�һ�£�������
						CAlertMain::CloseSerialPort();
						bInitSerialPort = CAlertMain::InitSerialPort();
					}
					else if(strIniName == "watchsheetcfg.ini")
					{
						//ֵ�� ���øı� watchsheetcfg.ini --> ��ʱ���� 
						if(strOperate == "ADD")
						{
							//ADD
							ReadCfgFromWatchIniSection(strSection);
						}
						else if(strOperate == "DELETE")
						{
							//DELETE
							DeleteCfgFromWatchIniSection(strSection);
						}
						else
						{
							//EDIT UPDATE
							DeleteCfgFromWatchIniSection(strSection);
							ReadCfgFromWatchIniSection(strSection);
						}					
					}
					else
					{

					}

				//////////////////////begin to modify at 07/07/31 /////////////////////////////
				//#endif
				}
				//////////////////////modify end at 07/07/31 //////////////////////////////////
				//�˳��ٽ���
				waitlistmutex->leave();
			}
			else
			{
				if(label != "alertlogs")
				{
					//�¼�
					SVDYN dyn;
					if(!BuildDynByData(buf, len, dyn))
					{
						//waitlistmutex->leave();
						//delete buf;
						//continue;			
					}

					event = new CAlertEventObj();

					event->strMonitorId = label;
					if (dyn.m_displaystr!=NULL)
						event->strEventDes = dyn.m_displaystr;
					event->nEventType = dyn.m_state;
					event->nEventCount = dyn.m_laststatekeeptimes;
					event->strTime = ct.Format();
					
					string strEvent;
					char tmpBuf[256];
					sprintf(tmpBuf, "Id:%s  Type:%d  Count:%d", label.c_str(), dyn.m_state, dyn.m_laststatekeeptimes);
					strEvent = tmpBuf;
					//OutputDebugString(strEvent.c_str());
					//OutputDebugString("\n");
					
					//bool PushMessage(string queuename,string label,const char *data,unsigned int datalen,string user="default",string addr="localhost");
					std::string defaultret = "error";
					std::string alertexport = GetIniFileString("ExportQueue", "Enable",  defaultret, "general.ini");
					if(strcmp(alertexport.c_str(), "error") == 0)
					{					
					}
					else if(strcmp(alertexport.c_str(), "1") == 0)
					{						
						::PushMessage("ExportQueue", label, buf, len); 
					}
					else
					{
						#ifdef AddOnEventSever				
						::PushMessage("EventSeverInputQueue", label, buf, len); //�����¼���EventSever��¼���� 
						#endif
					}

					//�����ٽ���
					if(!waitlistmutex->test())
					{
						continue;
					}
		
					m_AlertEventList.push_back(event);
					printf("alerteventlist size=%d",m_AlertEventList.size());

					//�˳��ٽ���
					waitlistmutex->leave();

				}
			}

			if(buf != NULL)
			{
				delete buf;
				buf=NULL;
			}
		}
		else
		{
			DebugePrint("BlockPopMessage Error!!!");
			continue;
		}

		//waitlistmutex->leave();
	}	
}

//
void CAlertMain::DoProcess()
{
	bool bStop = false;
	CAlertEventObj * lastEventobj = NULL;
	while(!bStop)
	{
		//printf("DoReceive:");
		::Sleep(50);
		//���յ�m_AlertEventList

		//�����ٽ���
		if(!waitlistmutex->test())
		{
			continue;
		}

		//printf("label:%s,ct:%s,data:%s\n",label.c_str(),ct.Format().c_str(),buf.getbuffer());

		//����AlertSendObj�����͵�m_WaitSendEmailList�ȶ��У�
		if(!m_AlertEventList.empty())
		{
			lastEventobj = NULL;
			lastEventobj = m_AlertEventList.front();	
			//printf("lastEventobj:%d\n", lastEventobj->nEventCount);
			if(lastEventobj != NULL)
			{
				//printf(lastEventobj->GetDebugInfo().c_str());
				DebugePrint(lastEventobj->GetDebugInfo());
				for(m_AlertObjListItem = m_AlertObjList.begin(); m_AlertObjListItem != m_AlertObjList.end(); m_AlertObjListItem++)
				{
					//����ƥ��
					if((*m_AlertObjListItem)->IsUpgradeMatching(lastEventobj))
					{					
						CAlertSendObj * sendobj = (*m_AlertObjListItem)->MakeSendObj();
						if(sendobj != NULL)
						{
							sendobj->SetUpgradeTrue();

							if(sendobj->nType == 1)
							{
								m_WaitSendEmailList.push_back(sendobj);
								nSendCount ++;
							}
							else if(sendobj->nType == 2)
							{
								m_WaitSendSmsList.push_back(sendobj);
								nSendCount ++;
							}
							else
							{
								
							}
							//DebugePrint("------------------------------ ����ƥ�� etc-------------------\r\n");
							//DebugePrint(sendobj->GetDebugInfo());
							//if(typeid(sendobj) == typeid(CAlertEmailSendObj))
							//{
							//	m_WaitSendEmailList.push_back(sendobj);
							//}
							//else if(typeid(sendobj) == typeid(CAlertSmsSendObj))
							//{
							//	m_WaitSendSmsList.push_back(sendobj);
							//}
							//else
							//{
							//
							//}
							//m_WaitSendList.push_back(sendobj);
						}

					}

					//��ͨƥ��
					if((*m_AlertObjListItem)->IsMatching(lastEventobj))
					{
						CAlertSendObj * sendobj = (*m_AlertObjListItem)->MakeSendObj();
						if(sendobj != NULL)
						{
							//OutputDebugString(typeid(sendobj).name());
							//OutputDebugString(typeid(CAlertEmailSendObj *).name());

							if(sendobj->nType == 1)
							{
								m_WaitSendEmailList.push_back(sendobj);
								nSendCount ++;
							}
							else if(sendobj->nType == 2)
							{
								DebugePrint("------------------------------ ��ͨƥ�� SMS etc-------------------\r\n");
								m_WaitSendSmsList.push_back(sendobj);								
								nSendCount ++;
							}
							else if(sendobj->nType == 3)
							{
								m_WaitSendScriptList.push_back(sendobj);
								nSendCount ++;
							}
							else if(sendobj->nType == 4)
							{
								m_WaitSendSoundList.push_back(sendobj);
								nSendCount ++;
							}
							else if(sendobj->nType == 5)
							{
								m_WaitSendPythonList.push_back(sendobj);
								nSendCount ++;
							}
							else if(sendobj->nType == 6)
							{
								m_WaitSendWebList.push_back(sendobj);
								nSendCount ++;
							}
							else
							{
								delete 	sendobj;
							}
							
							
							//DebugePrint(sendobj->GetDebugInfo());

							//m_WaitSendEmailList.push_back(sendobj);
							//CAlertSendObj * lastSendObj = NULL;
							//lastSendObj = m_WaitSendEmailList.front();

							////printf("lastSendObj:%d\n", lastSendObj->nSendId);
							//if(lastSendObj != NULL)
							//{
							//	m_WaitSendEmailList.pop_front();
							//	delete lastSendObj;
							//}
							//else
							//{
							//	m_WaitSendEmailList.pop_front();
							//	DebugePrint("lastSendObj Error\r\n");
							//}


						//	//if(typeid(sendobj) == typeid(CAlertEmailSendObj *))
						//	//{
						//	//	m_WaitSendEmailList.push_back(sendobj);
						//	//}
						//	//else if(typeid(sendobj) == typeid(CAlertSmsSendObj *))
						//	//{
						//	//	m_WaitSendSmsList.push_back(sendobj);
						//	//}
						//	//else if(typeid(sendobj) == typeid(CAlertSoundSendObj *))
						//	//{
						//	//	m_WaitSendScriptList.push_back(sendobj);
						//	//}
						//	//else if(typeid(sendobj) == typeid(CAlertScriptSendObj *))
						//	//{
						//	//	m_WaitSendSoundList.push_back(sendobj);
						//	//}
						//	//else
						//	//{
						//	//
						//	//}
						//	
						//	//m_WaitSendList.push_back(sendobj);
						}
					}					
				}
			}

			//DebugePrint("m_AlertEventList pop_front");
			m_AlertEventList.pop_front();

			if(lastEventobj != NULL)
				delete lastEventobj;

			//�˳��ٽ���
			waitlistmutex->leave();
		}
		else
		{
			//�˳��ٽ���
			waitlistmutex->leave();		
		}
	}
}

//
//void CAlertMain::DoSend()
//{
//	CAlertSendObj * lastSendObj = NULL;
//	bool bStop = false;
//	while(!bStop)
//	{	
//		//printf("DoSend:");
//		::Sleep(50);
//		if(!waitlistmutex->test())
//		{
//			continue;
//		}
//		//�����ٽ���
//
//		//��m_WaitSendList���ͳ�ȥ
//		if(!m_WaitSendList.empty())
//		{
//			lastSendObj = NULL;
//			lastSendObj = m_WaitSendList.front();
//
//			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
//			if(lastSendObj != NULL)
//			{
//				m_WaitSendList.pop_front();
//				waitlistmutex->leave();
//				//printf(lastSendObj->GetDebugInfo().c_str());
//				DebugePrint(lastSendObj->GetDebugInfo().c_str());
//				lastSendObj->SendAlert();
//			}
//			else
//			{
//				m_WaitSendList.pop_front();
//				waitlistmutex->leave();
//			}
//		}
//
//		//�߼�����������...
//		waitlistmutex->leave();
//
//		//�˳��ٽ���
//	}
//}

//����Email����
void CAlertMain::DoSendEmailAlert()
{	
	bool bStop = false;
	while(!bStop)
	{	
		//printf("DoSend:");
		::Sleep(10);
		if(!waitlistmutex->test())
		{
			continue;
		}
		//�����ٽ���

		//��m_WaitSendEmailList���ͳ�ȥ
		if(!m_WaitSendEmailList.empty())
		{
			//���͵ȴ����д�С����1000�����
			if(m_WaitSendEmailList.size() > 1000)
			{
				//m_WaitSendEmailList.clear();
				
				list <CAlertSendObj *>::iterator  item;

				for(item = m_WaitSendEmailList.begin(); item != m_WaitSendEmailList.end(); item ++)
				{
					delete (*item);
				}

				m_WaitSendEmailList.erase(m_WaitSendEmailList.begin(), m_WaitSendEmailList.end());

				waitlistmutex->leave();
				DebugePrint("Error, m_WaitSendEmailList.size() > 1000, Clear Ok!");
				continue;
			}

			CAlertSendObj * lastSendObj = NULL;
			lastSendObj = m_WaitSendEmailList.front();

			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
			if(lastSendObj != NULL)
			{
				m_WaitSendEmailList.pop_front();
				waitlistmutex->leave();

				//DebugePrint("----------------------------DoSendEmailAlert Normal  Delete-------------------\r\n");
				DebugePrint(lastSendObj->GetDebugInfo());
				
				
				try
				{
					lastSendObj->SendAlert();
				}
				catch(...)
				{
					//DebugePrint("\r\n------------------�����ʼ��쳣��ʼ-----------------------------\r\n");
					DebugePrint(" DoSendEmailAlert SendAlert Error!\r\n");
					//DebugePrint("------------------�����ʼ��쳣����------------------------------\r\n");
				}

				delete lastSendObj;	
				nSendCount --;

				char chItem[32]  = {0};	
				sprintf(chItem, "%d", nSendCount);
				string strOutput = "DoSendEmailAlert : The SendCount is : ";
				strOutput += chItem;
				strOutput += "\r\n";
				DebugePrint(strOutput);
			}
			else
			{
				DebugePrint("------------------------------DoSendEmailAlert Error-------------------\r\n");
				m_WaitSendEmailList.pop_front();
				waitlistmutex->leave();
			}
		}
		else
		{
			//�߼�����������...
			waitlistmutex->leave();
		}

		//�˳��ٽ���
	}
}

//����
void CAlertMain::DoSendSmsAlert()
{
	bool bStop = false;
	while(!bStop)
	{	
		//printf("DoSend:");
		::Sleep(10);
		if(!waitlistmutex->test())
		{
			continue;
		}
		//�����ٽ���

		//��m_WaitSendSmsList���ͳ�ȥ
		if(!m_WaitSendSmsList.empty())
		{
			//���͵ȴ����д�С����1000�����
			if(m_WaitSendSmsList.size() > 1000)
			{
				//m_WaitSendEmailList.clear();
				
				list <CAlertSendObj *>::iterator  item;

				for(item = m_WaitSendSmsList.begin(); item != m_WaitSendSmsList.end(); item ++)
				{
					delete (*item);
				}

				m_WaitSendSmsList.erase(m_WaitSendSmsList.begin(), m_WaitSendSmsList.end());

				waitlistmutex->leave();
				DebugePrint("Error, m_WaitSendSmsList.size() > 1000, Clear Ok!");
				continue;
			}

			CAlertSendObj * lastSendObj = NULL;
			lastSendObj = m_WaitSendSmsList.front();

			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
			if(lastSendObj != NULL)
			{
				m_WaitSendSmsList.pop_front();
				waitlistmutex->leave();
				//printf(lastSendObj->GetDebugInfo().c_str());
				DebugePrint(lastSendObj->GetDebugInfo());
				

				try
				{
					lastSendObj->SendAlert();
				}
				catch(...)
				{
					//DebugePrint("------------------���Ͷ����쳣��ʼ-----------------------------\r\n");
					DebugePrint(" DoSendSmsAlert SendAlert Error!\r\n");					
					//DebugePrint("------------------���Ͷ����쳣����------------------------------\r\n")	;
					
					//�����
					//CAlertMain::UnloadWebSmsAlertCom();
					//CAlertMain::InitWebSmsAlertCom();
				}

				delete lastSendObj;				
				nSendCount --;
				char chItem[32]  = {0};	
				sprintf(chItem, "%d", nSendCount);
				string strOutput = "DoSendSmsAlert : The SendCount is : ";
				strOutput += chItem;
				strOutput += "\r\n";
				DebugePrint(strOutput);

			}
			else
			{
				m_WaitSendSmsList.pop_front();
				waitlistmutex->leave();
			}
		}
		else
		{
			//�߼�����������...
			waitlistmutex->leave();
		}

	}

	//CAlertMain::UnloadWebSmsAlertCom();
}


//
void CAlertMain::DoSendScriptAlert()
{	
	bool bStop = false;
	while(!bStop)
	{	
		//printf("DoSend:");
		::Sleep(10);
		if(!waitlistmutex->test())
		{
			continue;
		}
		//�����ٽ���

		//��m_WaitSendScriptList���ͳ�ȥ
		if(!m_WaitSendScriptList.empty())
		{
			//���͵ȴ����д�С����1000�����
			if(m_WaitSendScriptList.size() > 1000)
			{
				//m_WaitSendScriptList.clear();
				
				list <CAlertSendObj *>::iterator  item;

				for(item = m_WaitSendScriptList.begin(); item != m_WaitSendScriptList.end(); item ++)
				{
					delete (*item);
				}

				m_WaitSendScriptList.erase(m_WaitSendScriptList.begin(), m_WaitSendScriptList.end());

				waitlistmutex->leave();
				DebugePrint("Error, m_WaitSendScriptList.size() > 1000, Clear Ok!");
				continue;
			}

			CAlertSendObj * lastSendObj = NULL;
			lastSendObj = m_WaitSendScriptList.front();

			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
			if(lastSendObj != NULL)
			{
				m_WaitSendScriptList.pop_front();
				waitlistmutex->leave();
				DebugePrint(lastSendObj->GetDebugInfo());
				

				try
				{
					lastSendObj->SendAlert();
				}
				catch(...)
				{
					//DebugePrint("\r\n------------------���ͽű��쳣��ʼ-----------------------------\r\n");
					DebugePrint(" DoSendScriptAlert SendAlert Error!\r\n");
					//DebugePrint("------------------���ͽű��쳣����------------------------------\r\n");
					//CAlertMain::UnloadScriptAlertCom();
					//CAlertMain::InitScriptAlertCom();
				}

				delete lastSendObj;	
				//waitlistmutex->leave();
				nSendCount --;
				char chItem[32]  = {0};	
				sprintf(chItem, "%d", nSendCount);
				string strOutput = "DoSendScriptAlert : The SendCount is : ";
				strOutput += chItem;
				strOutput += "\r\n";
				DebugePrint(strOutput);
			}
			else
			{
				m_WaitSendScriptList.pop_front();
				waitlistmutex->leave();
			}
		}
		else
		{
			//�߼�����������...
			waitlistmutex->leave();
		}
	}
}

//
void CAlertMain::DoSendSoundAlert()
{	
	bool bStop = false;
	while(!bStop)
	{	
		//printf("DoSend:");
		::Sleep(10);
		if(!waitlistmutex->test())
		{
			continue;
		}
		//�����ٽ���

		//��m_WaitSendSoundList���ͳ�ȥ
		if(!m_WaitSendSoundList.empty())
		{
			//���͵ȴ����д�С����1000�����
			if(m_WaitSendSoundList.size() > 1000)
			{
				//m_WaitSendSoundList.clear();
				
				list <CAlertSendObj *>::iterator  item;

				for(item = m_WaitSendSoundList.begin(); item != m_WaitSendSoundList.end(); item ++)
				{
					delete (*item);
				}

				m_WaitSendSoundList.erase(m_WaitSendSoundList.begin(), m_WaitSendSoundList.end());

				waitlistmutex->leave();
				DebugePrint("Error, m_WaitSendSoundList.size() > 1000, Clear Ok!");
				continue;
			}

			CAlertSendObj * lastSendObj = NULL;
			lastSendObj = m_WaitSendSoundList.front();

			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
			if(lastSendObj != NULL)
			{
				m_WaitSendSoundList.pop_front();
				waitlistmutex->leave();
				//printf(lastSendObj->GetDebugInfo().c_str());
				DebugePrint(lastSendObj->GetDebugInfo());				

				try
				{

					lastSendObj->SendAlert();
				}
				catch(...)
				{
					//DebugePrint("\r\n------------------���������쳣��ʼ-----------------------------\r\n");
					DebugePrint(" DoSendSoundAlert SendAlert Error!\r\n");
					//DebugePrint("------------------���������쳣����------------------------------\r\n");		
					//CAlertMain::UnloadSoundAlertCom();
					//CAlertMain::InitSoundAlertCom();
				}
				
				delete lastSendObj;				
				//waitlistmutex->leave();
				
				nSendCount --;
				char chItem[32]  = {0};	
				sprintf(chItem, "%d", nSendCount);
				string strOutput = "DoSendSoundAlert : The SendCount is : ";
				strOutput += chItem;
				strOutput += "\r\n";
				DebugePrint(strOutput);

			}
			else
			{
				m_WaitSendSoundList.pop_front();
				waitlistmutex->leave();
			}
		}
		else
		{
			//�߼�����������...
			waitlistmutex->leave();
		}
	}
}

//
void CAlertMain::DoSendPythonAlert()
{	
	bool bStop = false;
	while(!bStop)
	{	
		//printf("DoSend:");
		::Sleep(10);
		if(!waitlistmutex->test())
		{
			continue;
		}
		//�����ٽ���

		//��m_WaitSendSoundList���ͳ�ȥ
		if(!m_WaitSendPythonList.empty())
		{
			//���͵ȴ����д�С����1000�����
			if(m_WaitSendPythonList.size() > 1000)
			{
				//m_WaitSendSoundList.clear();
				
				list <CAlertSendObj *>::iterator  item;

				for(item = m_WaitSendPythonList.begin(); item != m_WaitSendPythonList.end(); item ++)
				{
					delete (*item);
				}

				m_WaitSendPythonList.erase(m_WaitSendPythonList.begin(), m_WaitSendPythonList.end());

				waitlistmutex->leave();
				DebugePrint("Error, m_WaitSendPythonList.size() > 1000, Clear Ok!");
				continue;
			}

			CAlertSendObj * lastSendObj = NULL;
			lastSendObj = m_WaitSendPythonList.front();

			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
			if(lastSendObj != NULL)
			{
				m_WaitSendPythonList.pop_front();
				waitlistmutex->leave();
				//printf(lastSendObj->GetDebugInfo().c_str());
				DebugePrint(lastSendObj->GetDebugInfo());				

				try
				{

					lastSendObj->SendAlert();
				}
				catch(...)
				{
					//DebugePrint("\r\n------------------���������쳣��ʼ-----------------------------\r\n");
					DebugePrint(" DoSendSoundAlert SendAlert Error!\r\n");
					//DebugePrint("------------------���������쳣����------------------------------\r\n");		
					//CAlertMain::UnloadSoundAlertCom();
					//CAlertMain::InitSoundAlertCom();
				}
				
				delete lastSendObj;				
				//waitlistmutex->leave();
				
				nSendCount --;
				char chItem[32]  = {0};	
				sprintf(chItem, "%d", nSendCount);
				string strOutput = "DoSendPythonAlert : The SendCount is : ";
				strOutput += chItem;
				strOutput += "\r\n";
				DebugePrint(strOutput);

			}
			else
			{
				m_WaitSendPythonList.pop_front();
				waitlistmutex->leave();
			}
		}
		else
		{
			//�߼�����������...
			waitlistmutex->leave();
		}
	}
}

void CAlertMain::DoSendWebAlert()
{	
	bool bStop = false;
	while(!bStop)
	{	
		//printf("DoSend:");
		::Sleep(10);
		if(!waitlistmutex->test())
		{
			continue;
		}
		//�����ٽ���

		//��m_WaitSendWebList���ͳ�ȥ
		if(!m_WaitSendWebList.empty())
		{
			//���͵ȴ����д�С����1000�����
			if(m_WaitSendWebList.size() > 1000)
			{
				//m_WaitSendWebList.clear();
				
				list <CAlertSendObj *>::iterator  item;

				for(item = m_WaitSendWebList.begin(); item != m_WaitSendWebList.end(); item ++)
				{
					delete (*item);
				}

				m_WaitSendWebList.erase(m_WaitSendWebList.begin(), m_WaitSendWebList.end());

				waitlistmutex->leave();
				DebugePrint("Error, m_WaitSendWebList.size() > 1000, Clear Ok!");
				continue;
			}

			CAlertSendObj * lastSendObj = NULL;
			lastSendObj = m_WaitSendWebList.front();

			//printf("lastSendObj:%d\n", lastSendObj->nSendId);
			if(lastSendObj != NULL)
			{
				m_WaitSendWebList.pop_front();
				waitlistmutex->leave();
				//printf(lastSendObj->GetDebugInfo().c_str());
				DebugePrint(lastSendObj->GetDebugInfo());				

				try
				{

					lastSendObj->SendAlert();
				}
				catch(...)
				{
					//DebugePrint("\r\n------------------���������쳣��ʼ-----------------------------\r\n");
					DebugePrint(" DoSendSoundAlert SendAlert Error!\r\n");
					//DebugePrint("------------------���������쳣����------------------------------\r\n");		
					//CAlertMain::UnloadSoundAlertCom();
					//CAlertMain::InitSoundAlertCom();
				}
				
				delete lastSendObj;				
				//waitlistmutex->leave();
				
				nSendCount --;
				char chItem[32]  = {0};	
				sprintf(chItem, "%d", nSendCount);
				string strOutput = "DoSendWebAlert : The SendCount is : ";
				strOutput += chItem;
				strOutput += "\r\n";
				DebugePrint(strOutput);

			}
			else
			{
				m_WaitSendWebList.pop_front();
				waitlistmutex->leave();
			}
		}
		else
		{
			//�߼�����������...
			waitlistmutex->leave();
		}
	}
}


//��alert.ini��ʼ�����������б�
void CAlertMain::InitAlertObjList()
{	
	//
	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	//////////////////////begin to modify at 07/07/31 /////////////////////////////
	//#ifdef IDC_Version
	if(GetCgiVersion().compare("IDC") == 0)
	{
	//////////////////////modify end at 07/07/31 //////////////////////////////////

		//�����IDC�汾����Ҫ��ȡ����IDC�û���Ŀ¼�µ�alert.ini��ֵ�ϳ�һ���б�����Ĵ���ʹ�á�

		//��Ҫ�洢IDC�û������û�ID��һ���б���߶�alert.ini�á�
		std::list<string> idcIdlist;
		std::list<string>::iterator m_idcItem;

		PAIRLIST retlist;
		std::list<struct sv_pair>::iterator svitem;		
		string strStrIdcId = "";
		GetAllGroupsInfo(retlist, "sv_name");
		OutputDebugString("---------------alert idcinfo  load----------------------\n");
		for(svitem = retlist.begin(); svitem != retlist.end(); svitem++)
		{
			strStrIdcId = (*svitem).name;

			//���ǻ�������Ա��
			if(strStrIdcId.compare(strWeiHuUserIdcId) != 0 && strStrIdcId.compare(strSysWeihuUserIdcId) != 0 \
				&& strStrIdcId.compare(strYeWuIdcId) != 0 && strStrIdcId.compare(strXiaoshouIdcId) != 0)
			{			
				//ֻ��һ���ָ���
				if(IsIdcGroup(strStrIdcId.c_str()))
				{
					OutputDebugString(strStrIdcId.c_str());
					OutputDebugString("\n");
					idcIdlist.push_back(strStrIdcId);
				}
			}
		}

		//����IdcId������
		for(m_idcItem = idcIdlist.begin(); m_idcItem != idcIdlist.end(); m_idcItem++)
		{
			//��ini��ȡ�����б�
			if(GetIniFileSections(keylist, "alert.ini", "localhost", (*m_idcItem)))
			{
				//��ini��ʼ�������б�
				for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
				{
					ReadAlertObjFromIni((*keyitem), (*m_idcItem));
				}
			}
		}

	//////////////////////begin to modify at 07/07/31 /////////////////////////////
	//#else
	}
	else
	{
	//////////////////////modify end at 07/07/31 //////////////////////////////////

		//��ini��ȡ�����б�
		if(GetIniFileSections(keylist, "alert.ini"))
		{
			//��ini��ʼ�������б�
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				ReadAlertObjFromIni((*keyitem));
			}
		}	

	//////////////////////begin to modify at 07/07/31 /////////////////////////////
	//#endif
	}
	//////////////////////modify end at 07/07/31 //////////////////////////////////
}

//
void CAlertMain::ReadAlertObjFromIni(string strSection)
{
	//��������
	string strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState, strTmp;
	string strAlertTargerList;

	//��������	
	string strEmailAdressValue, strOtherAdressValue, strEmailTemplateValue;
	string strSmsNumberValue, strOtherNumberValue, strSmsSendMode, strSmsTemplateValue;	
	string strServerTextValue, strScriptFileValue, strScriptParamValue, strScriptServerId;
	string strServerValue, strLoginNameValue, strLoginPwdValue;
	string strAlertUpgradeValue, strAlertUpgradeToValue, strAlertStopValue;
	string strReceive, strLevel, strContent;
	int nCond = 0, nAlertType = 0, index = 0;
	string strAlwaysTimesValue, strOnlyTimesValue,strSelTimes1Value,strSelTimes2Value;
	
	CAlertBaseObj * alertbaseobj = NULL;
	CAlertEmailObj * alertemailobj = NULL;
	CAlertSmsObj * alertsmsobj = NULL;
	CAlertScriptObj * alertscriptobj = NULL;
	CAlertSoundObj * alertsoundobj = NULL;
	CAlertPythonObj * alertpythonobj = NULL;

	//��ini������
	strIndex = GetIniFileString(strSection, "nIndex", "", "alert.ini");
	strAlertName = GetIniFileString(strSection, "AlertName", "", "alert.ini");
	strAlertType = GetIniFileString(strSection, "AlertType", "" , "alert.ini");
	strAlertCategory = GetIniFileString(strSection, "AlertCategory", "", "alert.ini");
	strAlertState = GetIniFileString(strSection, "AlertState", "", "alert.ini");
	
	//��ȡ��������Ŀ��
	strAlertTargerList = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini");
	nAlertType = GetIntFromAlertType(strAlertType);
	
	//��������
	nCond = GetIniFileInt(strIndex, "AlertCond", 0, "alert.ini");

	strAlwaysTimesValue = GetIniFileString(strIndex, "AlwaysTimes", "", "alert.ini");
	strOnlyTimesValue = GetIniFileString(strIndex, "OnlyTimes", "", "alert.ini");
	strSelTimes1Value = GetIniFileString(strIndex, "SelTimes1", "", "alert.ini");
	strSelTimes2Value = GetIniFileString(strIndex, "SelTimes2", "", "alert.ini");			

	switch(nAlertType)
	{
		case 1:
			//email����
			strEmailAdressValue = GetIniFileString(strIndex, "EmailAdress", "", "alert.ini");
			strOtherAdressValue = GetIniFileString(strIndex, "OtherAdress", "", "alert.ini");
			strEmailTemplateValue = GetIniFileString(strIndex, "EmailTemplate", "", "alert.ini");
			
			strAlertUpgradeValue = GetIniFileString(strIndex, "Upgrade", "", "alert.ini");
			if(strAlertUpgradeValue == "")
				strAlertUpgradeValue = "0";
			
			strAlertUpgradeToValue = GetIniFileString(strIndex, "UpgradeTo", "", "alert.ini");
			
			strAlertStopValue = GetIniFileString(strIndex, "Stop", "", "alert.ini");
			if(strAlertStopValue == "")
				strAlertStopValue = "0";

			//index = strEmailAdressValue.find("��ֹ");
			index = strEmailAdressValue.find(CAlertMain::strDisable.c_str());
			if(index != -1)
			{		
				//OutputDebugString(strEmailAdressValue.c_str());
				strTmp = strEmailAdressValue.substr(0, index - 1);
				//OutputDebugString(strTmp.c_str());
				strEmailAdressValue = strTmp;
			}

			DebugePrint(strEmailAdressValue.c_str());

			alertemailobj = new CAlertEmailObj();					

			alertemailobj->strEmailAdressValue = strEmailAdressValue;
			alertemailobj->strOtherAdressValue = strOtherAdressValue;
			alertemailobj->strEmailTemplateValue = strEmailTemplateValue;
			
			alertemailobj->strAlertUpgradeValue = strAlertUpgradeValue;
			alertemailobj->strAlertUpgradeToValue = strAlertUpgradeToValue;
			alertemailobj->strAlertStopValue = strAlertStopValue;
			
			alertemailobj->RefreshData();
			alertbaseobj = (CAlertBaseObj *)alertemailobj;
			break;
		case 2:
			//���ű���
			strSmsNumberValue = GetIniFileString(strIndex, "SmsNumber", "", "alert.ini");
			strOtherNumberValue = GetIniFileString(strIndex, "OtherNumber", "", "alert.ini");
			strSmsSendMode = GetIniFileString(strIndex, "SmsSendMode", "", "alert.ini");
			strSmsTemplateValue = GetIniFileString(strIndex, "SmsTemplate", "", "alert.ini");

			strAlertUpgradeValue = GetIniFileString(strIndex, "Upgrade", "", "alert.ini");
			if(strAlertUpgradeValue == "")
				strAlertUpgradeValue = "0";

			strAlertUpgradeToValue = GetIniFileString(strIndex, "UpgradeTo", "", "alert.ini");

			strAlertStopValue = GetIniFileString(strIndex, "Stop", "", "alert.ini");
			if(strAlertStopValue == "")
				strAlertStopValue = "0";

			//index = strSmsNumberValue.find("��ֹ");
			index = strSmsNumberValue.find(CAlertMain::strDisable.c_str());
			if(index != -1)
			{		
				//OutputDebugString(strEmailAdressValue.c_str());
				strTmp = strSmsNumberValue.substr(0, index - 1);
				//OutputDebugString(strTmp.c_str());
				strSmsNumberValue = strTmp;
			}
			
			DebugePrint(strSmsNumberValue.c_str());
			//alertsmsobj = (CAlertSmsObj *)alertbaseobj;
			alertsmsobj = new CAlertSmsObj();
			alertsmsobj->strSmsNumberValue = strSmsNumberValue;
			alertsmsobj->strOtherNumberValue = strOtherNumberValue;
			alertsmsobj->strSmsSendMode = strSmsSendMode;
			alertsmsobj->strSmsTemplateValue = strSmsTemplateValue;

			alertsmsobj->strAlertUpgradeValue = strAlertUpgradeValue;
			alertsmsobj->strAlertUpgradeToValue = strAlertUpgradeToValue;
			alertsmsobj->strAlertStopValue = strAlertStopValue;

			alertsmsobj->RefreshData();
			alertbaseobj = (CAlertBaseObj *)alertsmsobj;
			break;
		case 3:
			//�ű�����
			strServerTextValue = GetIniFileString(strIndex, "ScriptServer", "", "alert.ini");
			strScriptServerId = GetIniFileString(strIndex, "ScriptServerId", "", "alert.ini");
			strScriptFileValue = GetIniFileString(strIndex, "ScriptFile", "", "alert.ini");
			strScriptParamValue = GetIniFileString(strIndex, "ScriptParam", "", "alert.ini");

			//alertscriptobj = (CAlertScriptObj *)alertbaseobj;
			alertscriptobj = new CAlertScriptObj();					
			alertscriptobj->strServerTextValue = strServerTextValue;
			alertscriptobj->strScriptServerId = strScriptServerId;
			alertscriptobj->strScriptFileValue = strScriptFileValue;
			alertscriptobj->strScriptParamValue = strScriptParamValue;
			
			alertbaseobj = (CAlertBaseObj *)alertscriptobj;
			break;
		case 4:
			//��������
			strServerValue = GetIniFileString(strIndex, "Server", "", "alert.ini");
			strLoginNameValue = GetIniFileString(strIndex, "LoginName", "", "alert.ini");
			strLoginPwdValue = GetIniFileString(strIndex, "LoginPwd", "", "alert.ini");
			
			alertsoundobj = new CAlertSoundObj();					
			alertsoundobj->strServerValue = strServerValue;
			alertsoundobj->strLoginNameValue = strLoginNameValue;
			alertsoundobj->strLoginPwdValue = strLoginPwdValue;
			
			alertbaseobj = (CAlertBaseObj *)alertsoundobj;
			break;
		case 5:
			//��������
			strReceive = GetIniFileString(strIndex, "PythonReceive", "", "alert.ini");
			strLevel = GetIniFileString(strIndex, "PythonLevel", "", "alert.ini");
			strContent = GetIniFileString(strIndex, "Content", "", "alert.ini");
			
			alertpythonobj = new CAlertPythonObj();
			alertpythonobj->strReceive = strReceive;
			alertpythonobj->strLevel = strLevel;
			alertpythonobj->strContent = strContent;
			
			alertbaseobj = (CAlertBaseObj *)alertpythonobj;
			break;
		default:
			break;
	}

	if(alertbaseobj != NULL)
	{
		alertbaseobj->strIndex = strIndex;
		alertbaseobj->strAlertName = strAlertName;
		alertbaseobj->strAlertType = strAlertType;
		alertbaseobj->strAlertCategory = strAlertCategory;
		alertbaseobj->strAlertState = strAlertState;
		alertbaseobj->strAlertTargerList = strAlertTargerList;
		alertbaseobj->nAlertType = nAlertType;
		alertbaseobj->nCond = nCond;
		alertbaseobj->strAlwaysTimesValue = strAlwaysTimesValue;
		alertbaseobj->strOnlyTimesValue = strOnlyTimesValue;
		alertbaseobj->strSelTimes1Value = strSelTimes1Value;
		alertbaseobj->strSelTimes2Value = strSelTimes2Value;			
		
		//printf(alertbaseobj->GetDebugInfo().c_str());
		//DebugePrint(alertbaseobj->GetDebugInfo().c_str());
		
		//�����ٽ���
		
		//if(!waitlistmutex->test())
		{	
			m_AlertObjList.push_back(alertbaseobj);	
			alertbaseobj->AnalysisAlertTarget();
			//waitlistmutex->leave();
		}
		//else
		{
			//DebugePrint("--------------------------��ȡini��¼�����ݳ�ͻ������!!!!!!!!----------------------------------\r\n");
		}		

		DebugePrint(alertbaseobj->GetDebugInfo());
	}

	//alertbaseobj = NULL;
}

//
void CAlertMain::DeleteAlertObjFromSection(string strSection)
{
	bool bExist = false;
	//�ֽ����ȷ��pAlertTargetList
	for(m_AlertObjListItem = m_AlertObjList.begin(); m_AlertObjListItem != m_AlertObjList.end(); m_AlertObjListItem++)
	{
		if((*m_AlertObjListItem)->strIndex == strSection)
		{
			bExist = true;
			break;
		}		
	}

	if(bExist)
	{
		//�����ٽ���
		//if(!waitlistmutex->test())
		{	
			m_AlertObjList.erase(m_AlertObjListItem);			
			//waitlistmutex->leave();
		}
		//else
		{
			//DebugePrint("--------------------------ɾ��ini��¼�����ݳ�ͻ������!!!!!!!!----------------------------------\r\n");
		}
		//delete (*m_AlertObjListItem);

	}
}

//
void CAlertMain::ReadAlertObjFromIni(string strSection, string strIdcId)
{
	//��������
	string strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState, strTmp;
	string strAlertTargerList;

	//��������	
	string strEmailAdressValue, strOtherAdressValue, strEmailTemplateValue;
	string strSmsNumberValue, strOtherNumberValue, strSmsSendMode, strSmsTemplateValue;	
	string strServerTextValue, strScriptFileValue, strScriptParamValue, strScriptServerId;
	string strServerValue, strLoginNameValue, strLoginPwdValue;
	string strAlertUpgradeValue, strAlertUpgradeToValue, strAlertStopValue;
	int nCond = 0, nAlertType = 0, index = 0;
	string strAlwaysTimesValue, strOnlyTimesValue,strSelTimes1Value,strSelTimes2Value;
	
	CAlertBaseObj * alertbaseobj = NULL;
	CAlertEmailObj * alertemailobj = NULL;
	CAlertSmsObj * alertsmsobj = NULL;
	CAlertScriptObj * alertscriptobj = NULL;
	CAlertSoundObj * alertsoundobj = NULL;

	//��ini������
	strIndex = GetIniFileString(strSection, "nIndex", "", "alert.ini", "localhost", strIdcId);
	strAlertName = GetIniFileString(strSection, "AlertName", "", "alert.ini", "localhost", strIdcId);
	strAlertType = GetIniFileString(strSection, "AlertType", "" , "alert.ini", "localhost", strIdcId);
	strAlertCategory = GetIniFileString(strSection, "AlertCategory", "", "alert.ini", "localhost", strIdcId);
	strAlertState = GetIniFileString(strSection, "AlertState", "", "alert.ini", "localhost", strIdcId);
	
	//��ȡ��������Ŀ��
	strAlertTargerList = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini", "localhost", strIdcId);
	nAlertType = GetIntFromAlertType(strAlertType);
	
	//��������
	nCond = GetIniFileInt(strIndex, "AlertCond", 0, "alert.ini", "localhost", strIdcId);

	strAlwaysTimesValue = GetIniFileString(strIndex, "AlwaysTimes", "", "alert.ini", "localhost", strIdcId);
	strOnlyTimesValue = GetIniFileString(strIndex, "OnlyTimes", "", "alert.ini", "localhost", strIdcId);
	strSelTimes1Value = GetIniFileString(strIndex, "SelTimes1", "", "alert.ini", "localhost", strIdcId);
	strSelTimes2Value = GetIniFileString(strIndex, "SelTimes2", "", "alert.ini", "localhost", strIdcId);			

	switch(nAlertType)
	{
		case 1:
			//email����
			strEmailAdressValue = GetIniFileString(strIndex, "EmailAdress", "", "alert.ini", "localhost", strIdcId);
			strOtherAdressValue = GetIniFileString(strIndex, "OtherAdress", "", "alert.ini", "localhost", strIdcId);
			strEmailTemplateValue = GetIniFileString(strIndex, "EmailTemplate", "", "alert.ini", "localhost", strIdcId);
			
			strAlertUpgradeValue = GetIniFileString(strIndex, "Upgrade", "", "alert.ini", "localhost", strIdcId);
			if(strAlertUpgradeValue == "")
				strAlertUpgradeValue = "0";
			
			strAlertUpgradeToValue = GetIniFileString(strIndex, "UpgradeTo", "", "alert.ini", "localhost", strIdcId);
			
			strAlertStopValue = GetIniFileString(strIndex, "Stop", "", "alert.ini", "localhost", strIdcId);
			if(strAlertStopValue == "")
				strAlertStopValue = "0";

			//index = strEmailAdressValue.find("��ֹ");
			index = strEmailAdressValue.find(CAlertMain::strDisable.c_str());
			if(index != -1)
			{		
				//OutputDebugString(strEmailAdressValue.c_str());
				strTmp = strEmailAdressValue.substr(0, index - 1);
				//OutputDebugString(strTmp.c_str());
				strEmailAdressValue = strTmp;
			}

			DebugePrint(strEmailAdressValue.c_str());

			alertemailobj = new CAlertEmailObj();					

			alertemailobj->strEmailAdressValue = strEmailAdressValue;
			alertemailobj->strOtherAdressValue = strOtherAdressValue;
			alertemailobj->strEmailTemplateValue = strEmailTemplateValue;
			
			alertemailobj->strAlertUpgradeValue = strAlertUpgradeValue;
			alertemailobj->strAlertUpgradeToValue = strAlertUpgradeToValue;
			alertemailobj->strAlertStopValue = strAlertStopValue;
			
			alertemailobj->RefreshData();
			alertbaseobj = (CAlertBaseObj *)alertemailobj;
			break;
		case 2:
			//���ű���
			strSmsNumberValue = GetIniFileString(strIndex, "SmsNumber", "", "alert.ini", "localhost", strIdcId);
			strOtherNumberValue = GetIniFileString(strIndex, "OtherNumber", "", "alert.ini", "localhost", strIdcId);
			strSmsSendMode = GetIniFileString(strIndex, "SmsSendMode", "", "alert.ini", "localhost", strIdcId);
			strSmsTemplateValue = GetIniFileString(strIndex, "SmsTemplate", "", "alert.ini", "localhost", strIdcId);

			strAlertUpgradeValue = GetIniFileString(strIndex, "Upgrade", "", "alert.ini", "localhost", strIdcId);
			if(strAlertUpgradeValue == "")
				strAlertUpgradeValue = "0";

			strAlertUpgradeToValue = GetIniFileString(strIndex, "UpgradeTo", "", "alert.ini", "localhost", strIdcId);

			strAlertStopValue = GetIniFileString(strIndex, "Stop", "", "alert.ini", "localhost", strIdcId);
			if(strAlertStopValue == "")
				strAlertStopValue = "0";

			//index = strSmsNumberValue.find("��ֹ");
			index = strSmsNumberValue.find(CAlertMain::strDisable.c_str());
			if(index != -1)
			{		
				//OutputDebugString(strEmailAdressValue.c_str());
				strTmp = strSmsNumberValue.substr(0, index - 1);
				//OutputDebugString(strTmp.c_str());
				strSmsNumberValue = strTmp;
			}
			
			DebugePrint(strSmsNumberValue.c_str());
			//alertsmsobj = (CAlertSmsObj *)alertbaseobj;
			alertsmsobj = new CAlertSmsObj();
			alertsmsobj->strSmsNumberValue = strSmsNumberValue;
			alertsmsobj->strOtherNumberValue = strOtherNumberValue;
			alertsmsobj->strSmsSendMode = strSmsSendMode;
			alertsmsobj->strSmsTemplateValue = strSmsTemplateValue;

			alertsmsobj->strAlertUpgradeValue = strAlertUpgradeValue;
			alertsmsobj->strAlertUpgradeToValue = strAlertUpgradeToValue;
			alertsmsobj->strAlertStopValue = strAlertStopValue;

			alertsmsobj->RefreshData();
			alertbaseobj = (CAlertBaseObj *)alertsmsobj;
			break;
		case 3:
			//�ű�����
			strServerTextValue = GetIniFileString(strIndex, "ScriptServer", "", "alert.ini", "localhost", strIdcId);
			strScriptServerId = GetIniFileString(strIndex, "ScriptServerId", "", "alert.ini", "localhost", strIdcId);
			strScriptFileValue = GetIniFileString(strIndex, "ScriptFile", "", "alert.ini", "localhost", strIdcId);
			strScriptParamValue = GetIniFileString(strIndex, "ScriptParam", "", "alert.ini", "localhost", strIdcId);

			//alertscriptobj = (CAlertScriptObj *)alertbaseobj;
			alertscriptobj = new CAlertScriptObj();					
			alertscriptobj->strServerTextValue = strServerTextValue;
			alertscriptobj->strScriptServerId = strScriptServerId;
			alertscriptobj->strScriptFileValue = strScriptFileValue;
			alertscriptobj->strScriptParamValue = strScriptParamValue;
			
			alertbaseobj = (CAlertBaseObj *)alertscriptobj;
			break;
		case 4:
			//��������
			strServerValue = GetIniFileString(strIndex, "Server", "", "alert.ini", "localhost", strIdcId);
			strLoginNameValue = GetIniFileString(strIndex, "LoginName", "", "alert.ini", "localhost", strIdcId);
			strLoginPwdValue = GetIniFileString(strIndex, "LoginPwd", "", "alert.ini", "localhost", strIdcId);
			
			alertsoundobj = new CAlertSoundObj();					
			alertsoundobj->strServerValue = strServerValue;
			alertsoundobj->strLoginNameValue = strLoginNameValue;
			alertsoundobj->strLoginPwdValue = strLoginPwdValue;
			
			alertbaseobj = (CAlertBaseObj *)alertsoundobj;
			break;
		case 5:
			//
			break;
		default:
			break;
	}

	if(alertbaseobj != NULL)
	{
		alertbaseobj->strIndex = strIndex;
		alertbaseobj->strAlertName = strAlertName;
		alertbaseobj->strAlertType = strAlertType;
		alertbaseobj->strAlertCategory = strAlertCategory;
		alertbaseobj->strAlertState = strAlertState;
		alertbaseobj->strAlertTargerList = strAlertTargerList;
		alertbaseobj->nAlertType = nAlertType;
		alertbaseobj->nCond = nCond;
		alertbaseobj->strAlwaysTimesValue = strAlwaysTimesValue;
		alertbaseobj->strOnlyTimesValue = strOnlyTimesValue;
		alertbaseobj->strSelTimes1Value = strSelTimes1Value;
		alertbaseobj->strSelTimes2Value = strSelTimes2Value;			
		
		alertbaseobj->strIdcId = strIdcId;
		
		//printf(alertbaseobj->GetDebugInfo().c_str());
		//DebugePrint(alertbaseobj->GetDebugInfo().c_str());
		
		//�����ٽ���
		
		//if(!waitlistmutex->test())
		{	
			m_AlertObjList.push_back(alertbaseobj);	
			alertbaseobj->AnalysisAlertTarget();
			//waitlistmutex->leave();
		}
		//else
		{
			//DebugePrint("--------------------------��ȡini��¼�����ݳ�ͻ������!!!!!!!!----------------------------------\r\n");
		}		

		DebugePrint(alertbaseobj->GetDebugInfo());
	}

	//alertbaseobj = NULL;
}

//
void CAlertMain::DeleteAlertObjFromSection(string strSection, string strIdcId)
{
	bool bExist = false;
	//�ֽ����ȷ��pAlertTargetList
	for(m_AlertObjListItem = m_AlertObjList.begin(); m_AlertObjListItem != m_AlertObjList.end(); m_AlertObjListItem++)
	{
		if((*m_AlertObjListItem)->strIndex == strSection && (*m_AlertObjListItem)->strIdcId == strIdcId)
		{
			bExist = true;
			break;
		}		
	}

	if(bExist)
	{
		//�����ٽ���
		//if(!waitlistmutex->test())
		{	
			m_AlertObjList.erase(m_AlertObjListItem);			
			//waitlistmutex->leave();
		}
		//else
		{
			//DebugePrint("--------------------------ɾ��ini��¼�����ݳ�ͻ������!!!!!!!!----------------------------------\r\n");
		}
		//delete (*m_AlertObjListItem);

	}
}


//alert.ini�����仯ʱˢ�¾������б�
void CAlertMain::RefreshAlertObjList()
{
	//
}

//����Ҫ��
void  CAlertMain::IniChangeProc()
{
	DebugePrint("IniChangeProc");
	
	//DoReceive  �ȹ���һ��
	receivethread->suspend();
	
	//
	m_AlertObjList.clear();
	InitAlertObjList();

	//�ֽ����ȷ��pAlertTargetList
	for(m_AlertObjListItem = m_AlertObjList.begin(); m_AlertObjListItem != m_AlertObjList.end(); m_AlertObjListItem++)
	{
		(*m_AlertObjListItem)->AnalysisAlertTarget();
		DebugePrint((*m_AlertObjListItem)->GetDebugInfo());
	}

	//DoReceive  ��������
	receivethread->resume();
}

//����Ҫ��
void  CAlertMain::SmsPortChangeProc()
{
	//���ն��кͲ��¼����еĺ���������
	//

	//�رմ���
	CAlertMain::CloseSerialPort();
	
	bInitSerialPort = CAlertMain::InitSerialPort();	
}

//��AlertType��ȡint
int CAlertMain::GetIntFromAlertType(string strType)
{
	int nType = 0;
	if(strType == "EmailAlert")
		nType = 1;
	else if(strType == "SmsAlert")
		nType = 2;
	else if(strType == "ScriptAlert")
		nType = 3;
	else if(strType == "SoundAlert")
		nType = 4;
	else if(strType == "PythonAlert")
		nType = 5;
	else
		nType = 0;
	return nType;
}

//////////////////////////////////////////////////////


////////////////��̬������ʼ//////////////////////////

HINSTANCE CAlertMain::hDll = NULL;//��̬��Ա�ĳ�ʼ��
SendEmail * CAlertMain::pSendEmail = NULL;//��̬��Ա�ĳ�ʼ��
EXECUTESCRIPT * CAlertMain::pExcuteScript = NULL;//��̬��Ա�ĳ�ʼ��
_Alert * CAlertMain::mySoundRef = NULL;
_Alert * CAlertMain::myScriptRef = NULL;
IUMSmSendPtr CAlertMain::pSender = NULL;
static const basic_string <char>::size_type npos = -1;
bool CAlertMain::bInitSerialPort = false;

//ֵ�������б�
list<WATCH_LIST> CAlertMain::m_pListWatch;
//ֵ�������б�ı���
list<WATCH_LIST>::iterator CAlertMain::m_pListWatchItem;

//static jwsmtp::mailer sendmail(false, 25);

//��ʼ������SendIpi
bool CAlertMain::InitSendApi()
{
	//AlertEmail.dll
#if WIN32
    //hDll = LoadLibrary(strPath.c_str());
	//hDll = LoadLibrary("AlertEmail.dll");
	//
 //   if (hDll)
 //   {
 //       pSendEmail = (SendEmailAlert*)::GetProcAddress(hDll, "EmailSendMessage");
 //       if(pSendEmail)
 //       {  
	//		int iEmailRet = 0;
	//		printf("load dll sucess");
	//		CAlertMain::pSendEmail("mail.dragonflow.com", "xingyu.cheng@dragonflow.com","test", "cxytgf@sina.com",
	//		"ffffffff", "xingyu.cheng",	"xingyu.cheng@dragonflow.com", iEmailRet);

	//	}
 //   }
    hDll = LoadLibrary("emailalert.dll");
    if (hDll)
    {
        pSendEmail = (SendEmail*)::GetProcAddress(hDll, "SendEmail");
        if (pSendEmail)
        {  
   //         bool bRet = pSendEmail("mail.dragonflow.com", "xingyu.cheng@dragonflow.com",
   //             "xingyu.cheng@dragonflow.com", "ffffffff",
   //             "ffffffffffffffff", "xingyu.cheng@dragonflow.com", "xingyu.cheng");
   ////         //bool bRet = (*func)("smtp.sina.com.cn", "cxytgf@sina.com",
   ////         //    "cxytgf@sina.com", "ffffffff",
   ////         //    "ffffffffffffffff", "cxytgf@sina.com", "cxytgf");
			//if(bRet)
			//	printf("SendEmail sucess");
			//else
			//	printf("SendEmail fail");
        }
        /*FreeLibrary(hDll);*/
    }
	
    hDll = LoadLibrary("Monitor.dll");
    if (hDll)
    {
        pExcuteScript = (EXECUTESCRIPT*)::GetProcAddress(hDll, "EXECUTESCRIPT");
        if (pExcuteScript)
        {  

		}
    }

#endif
	return true;
}

//ж�ظ���SendIpi
void CAlertMain::UnloadSendApi()
{
	#if WIN32
		if(hDll != NULL)
		{
			FreeLibrary(hDll);
		}
	#endif
}

//
bool CAlertMain::SendMail(string strServer, string strFrom, string strTo, string strSubject, string strContent, string strUser, string strPwd)
{
	//sendmail.setserver(strServer.c_str());
	//sendmail.setsender(strFrom.c_str());
	//sendmail.addrecipient(strTo.c_str());
	//sendmail.setsubject(strSubject.c_str());
	//sendmail.setmessage(strContent.c_str());
 //   sendmail.username(strUser.c_str());
 //   sendmail.password(strPwd.c_str());   

	//sendmail.send();

	return true;
}
//
bool CAlertMain::InitSoundAlertCom()
{
	CoInitialize(NULL);
	HRESULT hr=CoCreateInstance(CLSID_Alert,NULL,
							CLSCTX_ALL,
							IID__Alert,(void **)&CAlertMain::mySoundRef);
	if(SUCCEEDED(hr))
	{
		DebugePrint("CAlertSoundSendObj creat com success");
		//CoUninitialize();
		return true;	
	}
	else 
	{
		DebugePrint("CAlertSoundSendObj creat com failed");
		//CoUninitialize();
		return false;
	}
	//CoUninitialize();
}

//
void CAlertMain::UnloadSoundAlertCom()
{
	if(CAlertMain::mySoundRef != NULL)
	{
		//CoInitialize(NULL);
		CAlertMain::mySoundRef->Release();
		CAlertMain::mySoundRef = NULL;
	}
	CoUninitialize();	
}

//
bool CAlertMain::InitScriptAlertCom()
{
	CoInitialize(NULL);
	HRESULT hr=CoCreateInstance(CLSID_Alert,NULL,
							CLSCTX_ALL,
							IID__Alert,(void **)&CAlertMain::myScriptRef);
	if(SUCCEEDED(hr))
	{
		DebugePrint("CAlertScriptSendObj creat com success");
		//CoUninitialize();
		return true;	
	}
	else 
	{
		DebugePrint("CAlertScriptSendObj creat com failed");
		//CoUninitialize();
		return false;
	}
	//CoUninitialize();
}

//
void CAlertMain::UnloadScriptAlertCom()
{
	if(CAlertMain::myScriptRef != NULL)
	{
		CAlertMain::myScriptRef->Release();
		CAlertMain::myScriptRef = NULL;
	}

	CoUninitialize();	
}

//
bool CAlertMain::InitWebSmsAlertCom()
{
	CoInitialize(NULL);
	HRESULT hr = pSender.CreateInstance("SMSend.UMSmSend");

	if(SUCCEEDED(hr))
	{
		DebugePrint("CAlertWebSmsSendObj creat com success");
		//CoUninitialize();
		return true;	
	}
	else 
	{
		DebugePrint("CAlertWebSmsSendObj creat com failed");
		//CoUninitialize();
		return false;
	}
	//CoUninitialize();
}

//
void CAlertMain::UnloadWebSmsAlertCom()
{
	//CoInitialize(NULL);
	//CAlertMain::myRef->Release();
	//CAlertMain::myRef = NULL;
	//CAlertMain::pSender.Release();
	CoUninitialize();	
}



//
bool CAlertMain::ParserToLength(list<string >&pTokenList, string  strQueryString, int nLength)
{
	int nCount = strQueryString.length() / nLength;
	for(int i = 0; i <= nCount; i++)
	{
		string strTmp = strQueryString.substr(0, nLength);
		pTokenList.push_back(strTmp);
		strQueryString.erase(0, nLength);
	}

	return true;
}

//�ֽ��ַ���
bool CAlertMain::ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps)
{
    char * token = NULL;
    // duplicate string
	char * cp = ::strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        if (pSVSeps) // using separators
            token = strtok( pTmp , pSVSeps);
        else // using separators
			return false;
            //token = strtok( pTmp, chDefSeps);
        // every field
        while( token != NULL )
        {
            //triml(token);
            //AddListItem(token);
			pTokenList.push_back(token);
            // next field
            if (pSVSeps)
                token = strtok( NULL , pSVSeps);
            else
               return false;
				//token = strtok( NULL, chDefSeps);
        }
        // free memory
        free(cp);
    }
    return true;
}

//�ַ����滻
string CAlertMain::ReplaceStdString(string strIn, string strFrom, string strTo)
{
	string strTmp = strIn;
	int nPos=0;
	while(1)
	{
		nPos= strTmp.find(strFrom, nPos);
		int nLength = strFrom.length();

		if(nPos != npos)
		{
			strTmp = strTmp.replace(nPos, nLength, strTo);
		}
		else
		{
			break;
		}
	}
	
	return strTmp;
}

//��monitorid��ȡIdcUserId
string CAlertMain::TruncateToUId(string id)
{
	string uid=id;
	string::size_type pos1=id.find(".");
	if(pos1 != string::npos)
	{
		string::size_type pos2=id.find(".",pos1+1);
		if(pos2 != string::npos)
			uid= id.erase(pos2);
	}
	return uid;
}

//�Ƿ���idcuserid
bool CAlertMain::IsIdcGroup(const char * pQueryString)
{	
    char * token = NULL;
	int nCount = 0;   
	// duplicate string
	char * cp = ::strdup(pQueryString);
    if(cp)
    {
        char * pTmp = cp;        
        token = strtok( pTmp , ".");

         //token = strtok( pTmp, chDefSeps);
        // every field
        while( token != NULL )
        {
            nCount ++;
			// next field
            token = strtok( NULL , ".");
        }

        free(cp);
    }
	
	//return (nCount == 1) ? true : false;
	if(nCount == 2)
		return true;
	else
		return false;
}

//���ݵ����ж��Ƿ�������
bool CAlertMain::IsScheduleMatch(string strSchedule)
{
	if(strSchedule == "")
		return true;

	bool bReturn = false;	
	Datetime tm;
	int nDay;
	int nHour;	
	int nMin;  	
	nDay = tm.getDayOfWeek();
	nHour = tm.getHour();
	nMin = tm.getMinute();
	printf("%d:%d:%d ",nDay,nHour,nMin);

	//"Type"  "��������ƻ�"	"�������ƻ�" ������"��������ƻ�"������� Ӧ����emailset.exe�����ε�
	OBJECT hTask = GetTask(strSchedule);
	
	//if(GetTaskValue("Type", hTask) == "�������ƻ�")
	{
		//��Ե�����������
			
		char buf[256];
		string temp1 = "Allow";
		itoa(nDay, buf, 10);
		temp1 += buf;
		string temp = GetTaskValue(temp1, hTask);
		
		if(strcmp(temp.c_str(), "1") == 0)
		{				
			//����	
			int nTaskStartHour = 0, nTaskEndHour = 0, nTaskStartMin = 0, nTaskEndMin = 0;
			int nTaskStart = 0, nTaskEnd = 0, nInput = 0;

			//��ʼ
			temp1 = "start";
			temp1 += buf;
			std::list<string> pTmpList;	
			temp = GetTaskValue(temp1, hTask);
			CAlertMain::ParserToken(pTmpList, temp.c_str(), ":");

			sscanf(pTmpList.front().c_str(), "%d", &nTaskStartHour);
			sscanf(pTmpList.back().c_str(), "%d", &nTaskStartMin);
			
			//����
			pTmpList.clear();
			temp1 = "end";
			temp1 += buf;
			temp = GetTaskValue(temp1, hTask);
			CAlertMain::ParserToken(pTmpList, temp.c_str(), ":");

			sscanf(pTmpList.front().c_str(), "%d", &nTaskEndHour);
			sscanf(pTmpList.back().c_str(), "%d", &nTaskEndMin);

			//�Ƚ�
			nTaskStart = nTaskStartHour * 60 + nTaskStartMin;
			nTaskEnd = nTaskEndHour * 60 + nTaskEndMin;
			nInput = nHour * 60 +  nMin;

			if(nInput >= nTaskStart && nInput <= nTaskEnd)
				bReturn = true;
		}
		else
		{
			//��ֹ���ء�false;
		}
	}

	return bReturn;
}

//ɾ��ĳ��ֵ�����ñ�
void CAlertMain::DeleteCfgFromWatchIniSection(string strSection)
{
	for(m_pListWatchItem = m_pListWatch.begin(); m_pListWatchItem != m_pListWatch.end(); m_pListWatchItem++)
	{
		if(m_pListWatchItem->strItemindex == strSection)
		{
			//bExist = true;
			//break;
			m_pListWatch.erase(m_pListWatchItem);
		}		
	}
}

//��ĳ��ֵ�����ñ�
void CAlertMain::ReadCfgFromWatchIniSection(string strSection)
{
	string strCount = GetIniFileString(strSection, "count", "", "watchsheetcfg.ini");
	//string strAlertindex = GetIniFileString(strSection, "alertindex", "", "watchsheetcfg.ini");
	string strWatchType = GetIniFileString(strSection, "type", "", "watchsheetcfg.ini");
	
	int nCount = 0;
	
	sscanf(strCount.c_str(), "%d", &nCount);
	for(int i = 1 ; i <= nCount; i++)
	{
		WATCH_LIST watchItem;
		
		char chItem[32]  = {0};	
		string strItemDes = "item";
		sprintf(chItem, "%d", i);
		strItemDes.append(chItem);

		string strItem = GetIniFileString(strSection, strItemDes, "", "watchsheetcfg.ini");
		
		std::list<string> listWatchItem;
		
		CAlertMain::ParserToken(listWatchItem, strItem.c_str(), ",");
		
		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nDayOfWeek);
		listWatchItem.pop_front();
		
		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nYear);
		listWatchItem.pop_front();
		
		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nMonth);
		listWatchItem.pop_front();

		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nDay);
		watchItem.nDayOfMonth = watchItem.nDay;
		listWatchItem.pop_front();

		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nItemStartHour);
		listWatchItem.pop_front();
		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nItemStartMin);
		listWatchItem.pop_front();
		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nItemEndHour);
		listWatchItem.pop_front();				
		sscanf(listWatchItem.front().c_str(), "%d", &watchItem.nItemEndMin);
		listWatchItem.pop_front();
		
		watchItem.strPhoneNumber = listWatchItem.front();
		listWatchItem.pop_front();

		watchItem.strEmailAddress = listWatchItem.front();
		listWatchItem.pop_front();
		
		//watchItem.strAlertindex = strAlertindex;
		watchItem.strItemindex = strSection;
		watchItem.strType = strWatchType;
		
		m_pListWatch.push_back(watchItem);
	}
}

//��ʼ������ֵ�������б�
void CAlertMain::ReadCfgFromWatchIni()
{
	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	//��ini��ȡ����ֵ�������б�
	//if(GetIniFileSections(keylist, "watchsmscfg.ini"))
	if(GetIniFileSections(keylist, "watchsheetcfg.ini"))
	{
		//��ini��ʼ�������б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
		{
			ReadCfgFromWatchIniSection((*keyitem));
		}
	}
	//OutputDebugString(CAlertMain::GetCurPhoneNumberFromWatchList("20024").c_str());
}

//���ݱ���������ֵ�������ȡ��Ӧ�÷��͵��ֻ�����
string CAlertMain::GetCfgFromWatchList(string strAlertindex, bool bEmail)
{
	OutputDebugString("GetCfgFromWatchList Start:\n");
	OutputDebugString(strAlertindex.c_str());

	//����strAlertindex��ȡ ֵ������������ cfg	
	string strWatchSheet = GetIniFileString(strAlertindex, "WatchSheet", "", "alert.ini");

	if(strWatchSheet == "��" || strWatchSheet == "default" || strWatchSheet == "")
		return "";
	
	//��ʱ���¶�ȡ��Ӧ����������
	m_pListWatch.clear();
	ReadCfgFromWatchIniSection(strWatchSheet);

	//���ַ�ʽ	
	Datetime tm;
	int nYear, nMonth, nDayOfWeek, nDayOfMonth, nDay;	
	int nHour, nMin, nCurTmStat, nItemStartStat, nItemEndStat;	
	
	//��ȡ��ǰʱ�� ��ʽ ����X XX�� XX�� ��	

	nYear = tm.getYear();
	nMonth = tm.getMonth();
	
	nDayOfWeek = tm.getDayOfWeek();	
	nDayOfMonth = tm.getDay();
	nDay = tm.getDay();

	nHour = tm.getHour();
	nMin = tm.getMinute();
	
	nCurTmStat = nHour * 60 +  nMin;

	bool bWatchMatch = false;
	
	for(m_pListWatchItem = m_pListWatch.begin(); m_pListWatchItem != m_pListWatch.end(); m_pListWatchItem++)
	{
		bWatchMatch = false;

		//�Ƚ�����
		if(m_pListWatchItem->strType == "day")
		{
			//ָ������
			if(strWatchSheet == m_pListWatchItem->strItemindex && nYear == m_pListWatchItem->nYear && 
				  nMonth == m_pListWatchItem->nMonth && nDay == m_pListWatchItem->nDay)
			{
				bWatchMatch = true;
			}		
		}
		else if(m_pListWatchItem->strType == "dayofmonth")
		{
			//����
			if(strWatchSheet == m_pListWatchItem->strItemindex && nDayOfMonth == m_pListWatchItem->nDayOfMonth)
			{
				bWatchMatch = true;
			}		
		}
		else if(m_pListWatchItem->strType == "dayofweek")
		{
			//����
			if(strWatchSheet == m_pListWatchItem->strItemindex && nDayOfWeek == m_pListWatchItem->nDayOfWeek)
			{
				bWatchMatch = true;
			}
		}
		else
		{
		
		}

		if(bWatchMatch)
		{
			//�Ƚ�ʱ��
			nItemStartStat = m_pListWatchItem->nItemStartHour * 60 + m_pListWatchItem->nItemStartMin;
			nItemEndStat = m_pListWatchItem->nItemEndHour * 60 + m_pListWatchItem->nItemEndMin;
			if(nCurTmStat >= nItemStartStat && nCurTmStat <= nItemEndStat)
			{
				if(bEmail)
					return m_pListWatchItem->strEmailAddress;
				else
					return m_pListWatchItem->strPhoneNumber;
			}
		}
	}

	OutputDebugString("GetCfgFromWatchList End:\n");
	return "";
}

//����monitorid��ѯָ�����Ե�ֵ
string  CAlertMain::GetMonitorPropValue(string strId, string strPropName)
{
	string strTmp = "";

	//���������
	OBJECT objMonitor = GetMonitor(strId);
	if(objMonitor != INVALID_VALUE)
    {
        MAPNODE motnitornode = GetMonitorMainAttribNode(objMonitor);
        if(motnitornode != INVALID_VALUE)
        {
			FindNodeValue(motnitornode, strPropName, strTmp);
		}

		CloseMonitor(objMonitor);
	}

	return strTmp;
}

//����monitorid��ȡ�����������
string  CAlertMain::GetMonitorTitle(string strId)
{
	string strTmp = "";

	//---------------------------------------------------------------------------------------------
	//_zouxiao_2008.7.22
	//�޸Ľ��̺ͷ���ı���
	string strMonitorType = GetMonitorPropValue(strId, "sv_monitortype");	
		
	/*
	if(strMonitorType == "14" || strMonitorType == "33" || strMonitorType == "41"
		|| strMonitorType == "111" || strMonitorType == "174"  || strMonitorType == "175")
	{
		// 14 Service  33 Nt4.0Process  41 Process  111 UnixProcess  174 SNMP_Process  175 SNMP_Service
	}
	*/

	if(strMonitorType == "14")
		strTmp="Service";

	else if(strMonitorType == "33")
		strTmp="Process";

	else if(strMonitorType == "41")
		strTmp="Process";

	else if(strMonitorType == "111")
		strTmp="Process";

	else if(strMonitorType == "174")
		strTmp="Process";

	else if(strMonitorType == "175")
		strTmp="Service";

	//---------------------------------------------------------------------------------------------

	else
	{
		//���������
		OBJECT objMonitor = GetMonitor(strId);
		if(objMonitor != INVALID_VALUE)
		{
			MAPNODE motnitornode = GetMonitorMainAttribNode(objMonitor);

			if(motnitornode != INVALID_VALUE)
			{
				FindNodeValue(motnitornode, "sv_name", strTmp);
			}

			CloseMonitor(objMonitor);
		}
    }


	//�ӽ�����	
	if(strMonitorType == "14" || strMonitorType == "33" || strMonitorType == "41"
		|| strMonitorType == "111" || strMonitorType == "174"  || strMonitorType == "175")
	{
		// 14 Service  33 Nt4.0Process  41 Process  111 UnixProcess  174 SNMP_Process  175 SNMP_Service
		//strAlertTitle += " ";		

		string strProcName = "";
		OBJECT hMon = GetMonitor(strId);
		MAPNODE paramNode = GetMonitorParameter(hMon);		
		if(strMonitorType == "14")
		{
			FindNodeValue(paramNode, "_Service", strProcName);
		}
		else if(strMonitorType == "33")
		{
			FindNodeValue(paramNode, "_monitorProcessList", strProcName);
		}
		else if(strMonitorType == "41")
		{
			FindNodeValue(paramNode, "_monitorProcessList", strProcName);
		}
		else if(strMonitorType == "111")
		{
			FindNodeValue(paramNode, "_Service", strProcName);
		}
		else if(strMonitorType == "174")
		{
			FindNodeValue(paramNode, "_SelValue", strProcName);
		}
		else if(strMonitorType == "175")
		{
			FindNodeValue(paramNode, "_InterfaceIndex", strProcName);
		}
		else
		{
			
		}
		strTmp += ":";
		strTmp += strProcName;
		
	}

	return strTmp;
}

//����monitorid��ȡ���豸������
string  CAlertMain::GetDeviceTitle(string strId)
{
	string strTmp = "";
	string strParentId = FindParentID(strId);

	//�豸����
	OBJECT objDevice = GetEntity(strParentId);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE devicenode = GetEntityMainAttribNode(objDevice);
        if(devicenode != INVALID_VALUE)
        {
			FindNodeValue(devicenode, "sv_name", strTmp);
		}
		
		CloseEntity(objDevice);
	}

	return strTmp;
}

//����monitorid��ȡȫ·��
string CAlertMain::GetAllGroupTitle(string strId)
{
    OBJECT objGroup;
    int nPos = strId.find(".");
    if(nPos < 0)
    {
        objGroup = GetSVSE(strId);
        string szName = "";
        if(objGroup != INVALID_VALUE)
            szName = GetSVSELabel(objGroup);
        else
            szName = "localhost";
        CloseSVSE(objGroup);
        return szName;        
    }
    else
    {
        string szParent = FindParentID(strId);
        string szName = "";
        objGroup = GetGroup(strId);
        if(objGroup != INVALID_VALUE)
        {

            MAPNODE node = GetGroupMainAttribNode(objGroup);
            if(node != INVALID_VALUE)
            {
                FindNodeValue(node, "sv_name", szName);  
            }
            CloseGroup(objGroup);
        }
        return GetAllGroupTitle(szParent) + " : " + szName;
    }
}

//�򿪷����Ŵ���
bool CAlertMain::InitSerialPort()
{
    //��������
	string sret;
	string Value = GetIniFileString("SMSCommConfig", "Port", sret, "smsconfig.ini");

    CString strCOM = "COM";
	strCOM += Value.c_str();

    //��ʼ������
	int nErr = m_smsPort.InitPort(strCOM);
    if (nErr == 0)
		return TRUE;//��ʼ���ɹ�
    else
    {
        switch(nErr)
        {
        case CSerialPort::OpenPortFailed://�򿪶˿�ʧ��
            break;
        case CSerialPort::NoSetCenter://û�����ö�������
            break;
        }
		m_smsPort.CloseCom();
        return FALSE;//��ʼ��ʧ��
    }

	return true;
}

//�رմ���
void CAlertMain::CloseSerialPort()
{
	m_smsPort.CloseCom();
}

//ͨ�����ڷ�����
int CAlertMain::SendSmsFromComm(CString strSmsTo, CString strContent)
{
	string testResult;
	bool bRet=false;
   if(bInitSerialPort)
	{
		bRet=m_smsPort.SendMsg(strSmsTo, strContent);
	}

	return bRet;
}

//ͨ�����ڲ��Է�����
int CAlertMain::TestSmsFromComm(CString strSmsTo, CString strContent)
{
	string testResult;
	if(bInitSerialPort)
	{
		bool bRet;
		bRet=m_smsPort.SendMsg(strSmsTo, strContent);

		//���ļ���д�뷵�ؽ��
		if (bRet)
			testResult="�ɹ�%���Ͷ��ŵ���������\n";
		else
			testResult="ʧ��%���Ͷ��ŵ�����ʧ��\n";

	}
	else
		testResult="ʧ��%��ʼ������ʧ��\n";

	string strto=strSmsTo.GetBuffer(0);
	WriteIniFileString("comsms","phone",strto,"smstestresult.ini");
	WriteIniFileString("comsms","result",testResult,"smstestresult.ini");

	return -1;
}



////////////////��̬��������//////////////////////////

///////////////CommonC++�߳̿�ʼ/////////////////////

ReceiveThread::ReceiveThread()
{
	
}

//
ReceiveThread::~ReceiveThread()
{
	
}

//
ReceiveThread::ReceiveThread(CAlertMain* obj)
{
	parentObj = obj;
}


//
void ReceiveThread::run()
{
	parentObj->DoReceive();
}



//
ProcessThread::ProcessThread()
{
	
}

//
ProcessThread::~ProcessThread()
{
	
}

//
ProcessThread::ProcessThread(CAlertMain* obj)
{
	parentObj = obj;
}

//
void ProcessThread::run()
{
	parentObj->DoProcess();
}


////
//SendThread::SendThread()
//{
//	
//}
//
////
//SendThread::~SendThread()
//{
//	
//}
//
////
//SendThread::SendThread(CAlertMain* obj)
//{
//	parentObj = obj;
//}
//
////
//void SendThread::run()
//{
//	//parentObj->DoSend();
//}

//
SendEmailAlertThread::SendEmailAlertThread()
{
	
}

//
SendEmailAlertThread::~SendEmailAlertThread()
{
	
}

//
SendEmailAlertThread::SendEmailAlertThread(CAlertMain* obj)
{
	parentObj = obj;
}

//
void SendEmailAlertThread::run()
{
	parentObj->DoSendEmailAlert();
}

//
SendSmsAlertThread::SendSmsAlertThread()
{
	
}

//
SendSmsAlertThread::~SendSmsAlertThread()
{
	//CAlertMain::UnloadWebSmsAlertCom();	
}

//
SendSmsAlertThread::SendSmsAlertThread(CAlertMain* obj)
{
	parentObj = obj;
}

//
void SendSmsAlertThread::run()
{	
	CAlertMain::InitWebSmsAlertCom();
	parentObj->DoSendSmsAlert();
}

//
SendScriptAlertThread::SendScriptAlertThread()
{
	
}

//
SendScriptAlertThread::~SendScriptAlertThread()
{
	//CAlertMain::UnloadScriptAlertCom();
}

//
SendScriptAlertThread::SendScriptAlertThread(CAlertMain* obj)
{
	parentObj = obj;
}

//
void SendScriptAlertThread::run()
{
	CAlertMain::InitScriptAlertCom();
	parentObj->DoSendScriptAlert();
}

//
SendSoundAlertThread::SendSoundAlertThread()
{
	
}

//
SendSoundAlertThread::~SendSoundAlertThread()
{
	//CAlertMain::UnloadSoundAlertCom();
}

//
SendSoundAlertThread::SendSoundAlertThread(CAlertMain* obj)
{
	parentObj = obj;
}

//
void SendSoundAlertThread::run()
{
	CAlertMain::InitSoundAlertCom();
	parentObj->DoSendSoundAlert();
}

//
SendPythonAlertThread::SendPythonAlertThread()
{
	
}

//
SendPythonAlertThread::~SendPythonAlertThread()
{

}

//
SendPythonAlertThread::SendPythonAlertThread(CAlertMain* obj)
{
	parentObj = obj;
}

//
void SendPythonAlertThread::run()
{
	parentObj->DoSendPythonAlert();
}

///////////////CommonC++�߳̽���/////////////////////