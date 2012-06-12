// LotusMon.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "LotusMon.h"

#define NT 1;
#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfsearc.h>
#include <osfile.h>
#include <names.h>
#include <nsferr.h>
#include <textlist.h>
#include <ods.h>
#include <odstypes.h>

#include <nsfdata.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <stdnames.h>
#include <osmem.h>
#include <osmisc.h>
#include <ostime.h>
#include <oserr.h>
#include <nsfobjec.h>
#include <misc.h>
#include <osfile.h>
#include <kfm.h>                        
     

#include <nsf.h>                        
#include <osenv.h>                      
#include <mail.h>                       
#include <mailserv.h>                   
#include <neterr.h>                     
#include <clerr.h>                      


#include <log.h>
#include <lapiplat.h>
#include <osmem.h>
#include <addin.h>

#include "stats.h"


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

// CLotusMonApp

BEGIN_MESSAGE_MAP(CLotusMonApp, CWinApp)
END_MESSAGE_MAP()


// CLotusMonApp ����

CLotusMonApp::CLotusMonApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLotusMonApp ����

CLotusMonApp theApp;


// CLotusMonApp ��ʼ��

BOOL CLotusMonApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


void WritePassword(const char * szPwd);
BOOL GetValue(char *Context,char *Name,char *Value,int nSpace, char *flag,int n);
BOOL CutFlag(char *src,char flag);
BOOL getDBSpace(CString strServer, CString strDBFile, char *szReturn);
BOOL NSF_List(CString strServer, CString strDirectory, CStringList &lstTexts,  CStringList &lstValues, char* szResult);
STATUS NF_Command(char *server ,char* szcommand,char* szResult);
bool MakeStringListByChar(CStringList& pList, const char * pInput );
bool MakeCharByString(char *pOut,int &nOutSize,CString strInput );

STATUS LNPUBLIC file_action_list(void *szReturn, SEARCH_MATCH far *pSearchMatch, ITEM_TABLE *summary_info);
STATUS LNPUBLIC print_file_summary_list (ITEM_TABLE *summary, void* szReturn);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STATUS LNPUBLIC file_action_list(void *szReturn, SEARCH_MATCH far *pSearchMatch,  ITEM_TABLE *summary_info)
{
    STATUS        error;
    SEARCH_MATCH SearchMatch;

    memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );

	/* Skip this object if it does not really match the search criteria (it
	is now deleted or modified).  This is not necessary for full searches,
	but is shown here in case a starting date was used in the search. */
    if (!(SearchMatch.SERetFlags & SE_FMATCH))
        return (NOERROR);

	/* Call a local function to print the file information in the summary buffer. */
    if (error = print_file_summary_list (summary_info, szReturn))
		 return(error);

	/* End of subroutine. */
    return (NOERROR);

}

STATUS LNPUBLIC print_file_summary_list (ITEM_TABLE *summary, void* szReturn)
{
	#define     MAX_ITEMS           30
	#define     MAX_TEXT_LEN        1000
	#define     DATATYPE_SIZE       sizeof(USHORT)
	#define     NAME_LENGTH_SIZE    sizeof(USHORT)
	#define     ITEM_LENGTH_SIZE    sizeof(USHORT)	
	#define     NUMERIC_SIZE        sizeof(FLOAT)
	#define     TIME_SIZE           ODSLength(_TIMEDATE)

	/* Local variables */
    BYTE       *summary_position;       /* current position in summary */
    ITEM_TABLE item_table;              /* header at start of summary */
    USHORT     item_count;              /* number of items in summary */
    USHORT     name_length[MAX_ITEMS];  /* length of each item name */
    USHORT     item_length[MAX_ITEMS];  /* length of each item */
    char       item_name[MAX_TEXT_LEN]; /* name of a summary item */
    USHORT     datatype;                /* type of item */
    char       item_text[MAX_TEXT_LEN]; /* text of a summary item */
    FLOAT      numeric_item;            /* a numeric item */
    TIMEDATE   time_item;               /* a time/date item */
    WORD       time_string_len;         /* length of ASCII time/date */
    STATUS     error;                   /* return code from API calls */
    USHORT     i;                       /* a counter */

    CStringList* lstText;
    lstText = (CStringList*)szReturn;

	/* Print a blank line to start this display. */
    printf ("\n");

	/* Get the header at the beginning of the summary buffer. */
    item_table = *summary;

	/* Keep track of where we are in the buffer. */
    summary_position = (BYTE *) summary;

	/* Get the number of items in the summary. */
    item_count = item_table.Items;

	/* Check boundary of the array */
	if (item_count > MAX_ITEMS)
	{
		printf("ERROR: Number of items has exceeded boundary of defined array.\n");
		return (0);
	}

	/* Advance the buffer pointer over the header. */
    summary_position += ODSLength(_ITEM_TABLE);

	/* Get the length of each item in the summary. */
    for (i=0; i < item_count; i++)
    {
        memcpy (&name_length[i], summary_position, NAME_LENGTH_SIZE);
        summary_position += NAME_LENGTH_SIZE;
        memcpy (&item_length[i], summary_position, ITEM_LENGTH_SIZE);
        summary_position += ITEM_LENGTH_SIZE;
    }

	/* Start a loop that extracts each item in the summary. */
    bool bNeedAdd = false;
    for (i=0; i < item_count; i++)
    {
		/* Print the name of the item. */
        memcpy (item_name, summary_position, name_length[i]);
        item_name[name_length[i]] = '\0';
        summary_position += name_length[i];

        printf ("%s:  ", item_name);
        if (0 == strcmp(item_name, "$TITLE"))
        {
            bNeedAdd = true;
        }

		/* Get the data type of this item. */
        memcpy (&datatype, summary_position, DATATYPE_SIZE);
        summary_position += DATATYPE_SIZE;

		/* Extract the item from the summary and put it in readable
		form. The way in which we extract the item depends on its type.
		This program handles TEXT, NUMBER, and TIME. */
        switch (datatype)
        {
			/* Extract a text item from the summary. */
			case TYPE_TEXT:
				memcpy (item_text, summary_position, item_length[i] - DATATYPE_SIZE);
				item_text[item_length[i] - DATATYPE_SIZE] = '\0';
				if (bNeedAdd)
				{
					lstText->AddTail(item_text);
					bNeedAdd = false;
				}
            break;

			/* Extract a number item from the summary. */
			case TYPE_NUMBER:
				memcpy (&numeric_item, summary_position, NUMERIC_SIZE);
				sprintf (item_text, "%g", numeric_item);
            break;

			/* Extract a time/date item from the summary. */
	        case TYPE_TIME:
	            memcpy (&time_item, summary_position, TIME_SIZE);
	            if (error = ConvertTIMEDATEToText (NULL,
                                               NULL,
                                               &time_item,
                                               item_text,
                                               MAXALPHATIMEDATE,
                                               &time_string_len))
				return (ERR(error));
	            item_text[time_string_len] = '\0';
            break;

			case TYPE_TEXT_LIST:
			{
				LIST      *pList;
				WORD      list_entry;
				char      *Buffer;
				WORD      text_size;

				memset (item_text,'\0', item_length[i] - DATATYPE_SIZE + 1);
				pList = (LIST *)summary_position;
				for (list_entry = 0; list_entry < pList->ListEntries; list_entry++)
				{
					ListGetText(pList, FALSE, list_entry, &Buffer, &text_size);
					strncat (item_text, Buffer, text_size);
				}
			}
			break;

			/* If the summary item is not one of the data types this program handles. */
			default:
            strcpy (item_text, "(Data type not handled)");
            break;
        }

		/* Print the item. */
        printf ("%s\n", item_text);

		/* Advance to next item in the summary. */
        summary_position += (item_length[i] - DATATYPE_SIZE);

		/* End of loop that is extracting each item in the summary. */
	}

	/* End of function */
    return (NOERROR);
}

int GetFile(char *file)
{
	//����ѯע����ֵ������
	struct HKEY__* ReRootKey = HKEY_CURRENT_USER;
	TCHAR *ReSubKey = "Software\\Lotus\\Notes\\Installer";
	TCHAR *ReValueName = "DATADIR";
	char content[256] = {0};			
	HKEY hKey;

	//�����ȡ��������
	DWORD dwType = REG_SZ;		
	DWORD dwLength = 256;


	int Result=0;

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_READ,&hKey)==ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey,ReValueName,NULL,&dwType,(unsigned char *)content,&dwLength)!=ERROR_SUCCESS)
		{
			//printf("�����޷���ѯ�йص�ע�����Ϣ");
			;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//printf("�����޷����йص�hKEY");
		;
	}

	if(strlen(content) <=0)
		strcpy(file,"C:\\lotus\\notes\\data\\password.txt");
	else
	{
		strcat(file,content);
		strcat(file,"password.txt");
	}


	return 0;
}

void WritePassword(const char * szPwd)
{
	char file[256] = {0};
	GetFile(file);

	FILE * fp = NULL;

	fp = fopen(file, "w+");
	if (fp) 
	{
		fputs(szPwd, fp);
		//fputs("\r\n", fp);
		fclose(fp);
	}
}

BOOL CutFlag(char *src,char flag)
{
	char value[1024] = {0};

	char *tmp = src;
	int len = (int)strlen(tmp);

	int n = 0;
	for(int i=0; i<len; i++)
	{
		if(*tmp != flag)
		{
			value[n] = *tmp;
			n++;
		}

		tmp++;
	}

	memset(src,0,1024);
	strcpy(src,value);

	return TRUE;

}

BOOL GetValue(char *Context,char *Name,char *Value,int nSpace, char *flag,int n)
{
	char * tmp = NULL;
	tmp = strstr(Context,Name);
	if(!tmp)
	{
		strcpy(Value,"0");
		return TRUE;
	}
	tmp+= strlen(Name);
	tmp+= nSpace;

	char * pos = strstr(tmp,flag);
	if(!pos)
	{
		strcpy(Value,"0");
		return TRUE;
	}
	int len = (int)(pos - tmp - n);
	while (*tmp==' '){
		tmp++;
		len--;
	}
	strncpy(Value,tmp,len);

	return TRUE;
}

bool MakeStringListByChar(CStringList& pList, const char * pInput )
{
	const char * p;
	int nSize;
	p=pInput;
	while(*p!='\0')
	{
		nSize = static_cast<int>(strlen(p));
		if( nSize>0 )
		{	
			pList.AddHead(p);
		//	printf(p);
		}
		p=p+nSize+1;
	}

	return true;
}

bool MakeCharByString(char *pOut,int &nOutSize,CString strInput )
{
	 char *p;
	
	int nSize=strInput.GetLength();
	if(nSize+2 <nOutSize)
	{
		strcpy(pOut,strInput.GetBuffer(strInput.GetLength()));
	}else return false;
	p=pOut;
	//printf("%d\n",nSize);23028830 13602067678 ����
	for(int i=0;i<nSize;i++)
	{
		if(*p=='$') 	*p='\0';
		p++;
	}
	nOutSize=nSize+1;
	return true;
	
}

CString GetValueFromList(const CString strName,CStringList& strList)
{
	POSITION pos=NULL;
	pos=strList.GetHeadPosition();
	int nIndex=0;
	CString strItem=_T("");
	CString strValue=_T("");
	while(pos!=NULL)
	{
		strItem=strList.GetNext(pos);
		nIndex=strItem.Find("=");
		strValue=strItem.Left(nIndex);
		if (strValue==strName)
		{
			strValue=strItem.Right(strItem.GetLength()-nIndex-1);
			return strValue;
		}
	}
	return "";	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STATUS NF_Command(char *server ,char* szcommand,char * szResult)
{
	HANDLE hRetInfo;
	STATUS nError;
	char *pBuffer;
        
	nError = NotesInitExtended (0, NULL);
	if (nError)
		return ERR(nError);
	
	nError = NSFRemoteConsole (server, szcommand, &hRetInfo);
	if (nError != NOERROR)
	{
		OSLoadString(NULLHANDLE, ERR(nError), szResult, 1024);
		CutFlag(szResult,0x13);
		NotesTerm();
		return (ERR(nError));
	}
	
	pBuffer = OSLock (char, hRetInfo);
	strcpy(szResult,pBuffer);
	OSUnlock (hRetInfo);
	OSMemFree (hRetInfo);
	NotesTerm();
	
	return (NOERROR);
}

/*
STATUS NF_Statics(char *server ,char *Facility,char *StatName,char * szResult)
{
	HANDLE hRetInfo;
	char *pBuffer;
	STATUS nError;
	STATUS      error = NOERROR;            
	DWORD dwWord;

	error = NotesInitExtended (0, NULL);
    if (error)
    {
        return FALSE;
    }
	nError = NSFGetServerStats (server, Facility,StatName, &hRetInfo,&dwWord);

	if (nError != NOERROR)
	{
		NotesTerm();
	    return (ERR(nError));
	}

	pBuffer = OSLock (char, hRetInfo);

	printf(pBuffer);
	strcpy(szResult,pBuffer);

	OSUnlock (hRetInfo);

	OSMemFree (hRetInfo);
	NotesTerm();

	return (NOERROR);

}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" _declspec (dllexport) BOOL Init(const char * strParas, char * szRet, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	STATUS nStatus = NOERROR;

	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	WaitForSingleObject(hhandle,INFINITE);

	WritePassword(strPassWord);

	nStatus = NotesInitExtended (0, NULL);
    if (nStatus != NOERROR)
    {
		ReleaseMutex(hhandle);
		CloseHandle(hhandle);
		OSLoadString(NULLHANDLE, ERR(nStatus), szResult, 1024);
		CutFlag(szResult,0x13);
		sprintf(szRet,"error=Can't Init Notes Extended:%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
        return FALSE;
    }

	nStatus=NF_Command(szServer,"show server",szResult);
	if(nStatus != NOERROR)
	{
		ReleaseMutex(hhandle);
		CloseHandle(hhandle);
		sprintf(szRet,"error=Can't Connect to Server:%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		NotesTerm();
		return FALSE;
	}
	
	NotesTerm();
	sprintf(szRet,"Connected to Server[%s]", szServer);
	nSize = static_cast<int>(strlen(szRet));
	
	ReleaseMutex(hhandle);
	CloseHandle(hhandle);

	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Close(const char * strParas, char * szRet,int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	WaitForSingleObject(hhandle,INFINITE);
	
	WritePassword(strPassWord);

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);
	
	strcpy(szRet,"Disconnected from Server");
	nSize = static_cast<int>(strlen(szRet));
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Mem(const char * strParas, char * szRet, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	WaitForSingleObject(hhandle,INFINITE);

	WritePassword(strPassWord);

	//�õ��ڴ�
	STATUS nStatus=NF_Command(szServer,"show stat mem",szResult);

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);

	if(nStatus != NOERROR)
	{
		sprintf(szRet,"error=%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}

	//Mem.Free
	char value[64]={0};
	GetValue(szResult,"Mem.Free",value,3,"\n",1);
	CutFlag(value,',');
	double dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sFree=%.2f$", szRet,dValue);

	//Mem.Allocated
	memset(value,0,64);
	GetValue(szResult,"Mem.Allocated",value,3,"\n",1);
	CutFlag(value,',');
	dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sAllocTotal=%.2f$", szRet,dValue);

	//Mem.Allocated.Process
	memset(value,0,64);
	GetValue(szResult,"Mem.Allocated.Process",value,3,"\n",1);
	CutFlag(value,',');
	dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sAllocProcess=%.2f$", szRet,dValue);

	//Mem.Allocated.Shared
	memset(value,0,64);
	GetValue(szResult,"Mem.Allocated.Shared",value,3,"\n",1);
	CutFlag(value,',');
	dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sAllocShared=%.2f$", szRet,dValue);

	//Mem.PhysicalRAM
	memset(value,0,64);
	GetValue(szResult,"Mem.PhysicalRAM",value,3,"\n",1);
	CutFlag(value,',');
	dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sPhysicalRAM=%.2f$", szRet,dValue);

	//Mem.Availability
	memset(value,0,64);
	GetValue(szResult,"Mem.Availability",value,3,"\n",1);
	sprintf(szRet, "%sAvailability=%s$", szRet, value);
	
	CString strInput =szRet;
	nSize = 4096;
	MakeCharByString(szRet,nSize,strInput);
	
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Disk(const char * strParas, char * szRet, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		sprintf(szRet,"error=CreateMutex Failed code is %d ", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	WaitForSingleObject(hhandle,INFINITE);
	
	WritePassword(strPassWord);

	//�õ����� 
	STATUS nStatus = NF_Command(szServer,"show stat disk",szResult);

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);

	if(nStatus != NOERROR)
	{
		sprintf(szRet,"error=%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	
	//Free
	char value[64]={0};
	GetValue(szResult,"Free",value,3,"\n",1);
	CutFlag(value,',');
	double dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sFreeDisks=%.2f$", szRet,dValue);
	
	//Size
	memset(value,0,64);
	GetValue(szResult,"Size",value,3,"\n",1);
	CutFlag(value,',');
	dValue  = atof(value)/1024/1024;
	sprintf(szRet, "%sSizeDisks=%.2f$", szRet,dValue);
	
	//Type
	memset(value,0,64);
	GetValue(szResult,"Type",value,3,"\n",1);
	sprintf(szRet, "%sTypeDisks=%s$", szRet, value);

	//Fixed
	memset(value,0,64);
	GetValue(szResult,"Fixed",value,3,"\n",1);
	sprintf(szRet, "%sFixedDisks=%s$", szRet, value);

	//Remote
	memset(value,0,64);
	GetValue(szResult,"Fixed",value,3,"\n",1);
	sprintf(szRet, "%sRemoteDisks=%s$", szRet, value);

	CString strInput =szRet;
	nSize = 4096;
	MakeCharByString(szRet,nSize,strInput);
	
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Task(const char * strParas, char * szRet, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	WaitForSingleObject(hhandle,INFINITE);
	
	WritePassword(strPassWord);

	STATUS nStatus=NF_Command(szServer,"show stat server",szResult);
	if(nStatus != NOERROR)
	{
		sprintf(szRet,"error=%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		ReleaseMutex(hhandle);
		CloseHandle(hhandle);
		return FALSE;
	}

	//Task count
	char value[64]={0};
	GetValue(szResult,"Tasks",value,3,"\n",1);
	sprintf(szRet, "%sTaskCount=%s$", szRet, value);

	//TransPerMinute
	memset(value,0,64);
	GetValue(szResult,"Server.Trans.PerMinute",value,3,"\n",1);
	sprintf(szRet, "%sTransPerMinute=%s$", szRet, value);

	//UsersPeak
	memset(value,0,64);
	GetValue(szResult,"Server.Users.Peak",value,3,"\n",1);
	sprintf(szRet, "%sUsersPeak=%s$", szRet, value);
	
	memset(szResult, 0, 1024*10);
	nStatus=NF_Command(szServer,"show tasks",szResult);
	if(nStatus != NOERROR)
	{
		sprintf(szRet,"error=%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		ReleaseMutex(hhandle);
		CloseHandle(hhandle);
		return FALSE;
	}

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);

	memset(value,0,64);
	GetValue(szResult,"Router",value,3,"\n",1);
	sprintf(szRet, "%sRouterStatus=%s$", szRet, value);

	memset(value,0,64);
	GetValue(szResult,"Replicator",value,3,"\n",1);
	sprintf(szRet, "%sRepicatorStatus=%s$", szRet, value);

	memset(value,0,64);
	GetValue(szResult,"Event Monitor",value,3,"\n",1);
	sprintf(szRet, "%sEventStatus=%s$", szRet, value);

	CString strInput =szRet;
	nSize = 4096;
	MakeCharByString(szRet,nSize,strInput);
	
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Mail(const char * strParas, char * szRet, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}
	WaitForSingleObject(hhandle,INFINITE);
	
	WritePassword(strPassWord);

	STATUS nStatus =NF_Command(szServer,"show stat mail",szResult);

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);

	if(nStatus != NOERROR)
	{
		sprintf(szRet,"error=%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}

	//CurrentByteDeliveryRate
	char value[64]={0};
	GetValue(szResult,"CurrentByteDeliveryRate",value,3,"\n",1);
	sprintf(szRet, "%sDeliveredMailRate=%s$", szRet, value);

	//CurrentByteTransferRate
	memset(value,0,64);
	GetValue(szResult,"CurrentByteTransferRate",value,3,"\n",1);
	sprintf(szRet, "%sTaskMailTransferRate=%s$", szRet, value);

	//CurrentMessageDeliveryRate
	memset(value,0,64);
	GetValue(szResult,"CurrentMessageDeliveryRate",value,3,"\n",1);
	sprintf(szRet, "%sRoutedMailRate=%s$", szRet, value);

	//Dead
	memset(value,0,64);
	GetValue(szResult,"Dead",value,3,"\n",1);
	sprintf(szRet, "%sDeadmailRate=%s$", szRet, value);

	//TotalPending
	memset(value,0,64);
	GetValue(szResult,"TotalPending",value,3,"\n",1);
	sprintf(szRet, "%sTotalPending=%s$", szRet, value);

	//Waiting
	memset(value,0,64);
	GetValue(szResult,"Waiting",value,3,"\n",1);
	sprintf(szRet, "%sWaitingMail=%s$", szRet, value);

	//WaitingRecipients
	memset(value,0,64);
	GetValue(szResult,"WaitingRecipients",value,3,"\n",1);
	sprintf(szRet, "%sWaitingRecipients=%s$", szRet, value);

	CString strInput =szRet;
	nSize = 4096;
	MakeCharByString(szRet,nSize,strInput);
	
	return TRUE;
}

extern "C" _declspec (dllexport)  BOOL FileList(const char * strParas, char * szRet, int& nSize)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");
	CString strDirectory = _T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);
	strDirectory = GetValueFromList("_Directory",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);

	CStringList lstTexts;
	CStringList lstValues;

	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		printf("begin wait  last error is %d\n",nlast);
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;

	}
	WaitForSingleObject(hhandle,INFINITE);

	WritePassword(strPassWord);

	BOOL bResult = NSF_List(strServerName, strDirectory, lstTexts, lstValues, szResult);
	if(!bResult)
	{
		ReleaseMutex(hhandle);
		CloseHandle(hhandle);
		CutFlag(szResult,0x13);
		sprintf(szRet,"error=NSF_List Failed %s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);

	POSITION pos=NULL;
    pos = lstTexts.GetHeadPosition();
	char * ca;
	ca =szRet;
	CString strTemp;
    while(pos)
    {
		strTemp=lstTexts.GetNext(pos);
		if(strTemp.Find(".nsf",0)>=0)
		{
			sprintf(ca,"%s=%s$",strTemp.GetBuffer(strTemp.GetLength()),strTemp.GetBuffer(strTemp.GetLength()));
			ca=ca+2*strTemp.GetLength()+2;
		}
        //lstValues.AddTail(lstTexts.GetNext(pos));        
    }
	
	CString strInput =szRet;
	nSize = 4096;
	MakeCharByString(szRet,nSize,strInput);

	return TRUE;
}

BOOL NSF_List(CString strServer, CString strDirectory, CStringList &lstTexts,  CStringList &lstValues, char* szReturn)
{
	char        szFullNetPath[MAXPATH] = ""; /* full network path */
    DBHANDLE    dir_handle;                 /* handle for directory */
    STATUS      error = NOERROR;            /* return status from API calls */

	error = NotesInitExtended (0, NULL);
	if (error)
	{
		OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
		return FALSE;
	}
	
    if (strDirectory != _T(""))
    {
        strcpy(szFullNetPath, strDirectory.GetBuffer(0));
    }
    
    if(strServer != _T(""))
    {
        // Compose the full network pathname to the directory. 
        if (error = OSPathNetConstruct(NULL, strServer.GetBuffer(0), strDirectory.GetBuffer(0), szFullNetPath))
	     {
		      OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
		      NotesTerm();
		      return FALSE;
	     }
    }

    // Open the directory. 
    if (error = NSFDbOpen (szFullNetPath, &dir_handle))
    {
        OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
        NotesTerm();
        return FALSE;
    }

    /* Call NSFSearch to find files in the directory. For each file found,
    call an action routine. */
    if (error = NSFSearch (
        dir_handle,        /* directory handle */
        NULLHANDLE,        /* selection formula */
        NULL,              /* title of view in formula */
        SEARCH_FILETYPE +  /* search for files */
        SEARCH_SUMMARY,    /* return a summary buffer */
        FILE_DBANY +       /* find any .NS? file */
        FILE_DIRS +        /* find subdirectories */
        FILE_NOUPDIRS,     /* don't find the ".." dir */
        NULL,              /* starting date */
        file_action_list,  /* call for each file found */
        &lstTexts,         /* argument to action routine */
        NULL))             /* returned ending date (unused) */

        {
            OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
            NSFDbClose (dir_handle);
            NotesTerm();
            return FALSE;
        }

    /* Close the directory. */
    if (error = NSFDbClose (dir_handle))
    {
        OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
        NotesTerm();
        return FALSE;
    }

    /* Terminate Domino and Notes. */
    NotesTerm();
    POSITION pos=NULL;
    pos = lstTexts.GetHeadPosition();
    while(pos)
    {
        lstValues.AddTail(lstTexts.GetNext(pos));        
    }
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL DBSpace(const char * strParas, char * szRet, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strServerName=_T("");
	CString strUserAccount=_T("");
	CString strPassWord=_T("");
	CString strDBFile=_T("");

	CStringList lstParas;
	MakeStringListByChar(lstParas,strParas);

	strServerName = GetValueFromList("_ServerName",lstParas);
	strUserAccount = GetValueFromList("_UserAccount",lstParas);	
	strPassWord = GetValueFromList("_PassWord",lstParas);
	strDBFile = GetValueFromList("_DBFile",lstParas);

	char szResult[1024*10]={0};
	char szServer[1024]={0};
	strcpy(szServer,strServerName);
	
	HANDLE hhandle =CreateMutex(NULL,FALSE,"Global\\SiteView-Lotus-Montior");
	if(hhandle ==NULL)
	{
		DWORD nlast;
		nlast =GetLastError();
		printf("begin wait  last error is %d\n",nlast);
		sprintf(szRet,"error=CreateMutex Failed code is %d", nlast);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;

	}
	WaitForSingleObject(hhandle,INFINITE);

	WritePassword(strPassWord);

	if(!getDBSpace(szServer,strDBFile,szResult))
	{
		ReleaseMutex(hhandle);
		CloseHandle(hhandle);
		CutFlag(szResult,0x13);
		sprintf(szRet,"error=%s", szResult);
		nSize = static_cast<int>(strlen(szRet));
		return FALSE;
	}

	ReleaseMutex(hhandle);
	CloseHandle(hhandle);
	
	CString strInput =szResult;
	nSize = 4096;
	MakeCharByString(szRet,nSize,strInput);
	
	return TRUE;
}

BOOL getDBSpace(CString strServer, CString strDBFile, char *szReturn)
{
	char        szFullNetPath[MAXPATH] = ""; /* full network path */
    DBHANDLE    dir_handle;                  /* handle for directory */
    STATUS      error = NOERROR;             /* return status from API calls */
    DWORD       dwAvalid = 0;
    DWORD       dwFree = 0;

	error = NotesInitExtended (0, NULL);
	if (error)
	{
		sprintf (szReturn, "error=Error initializing Notes.");
		return FALSE;
	}
	
    if(strServer != _T(""))
    {
        /* Compose the full network pathname to the directory. */
        if (error = OSPathNetConstruct(NULL, strServer.GetBuffer(0), strDBFile.GetBuffer(0), szFullNetPath))
	     {
		      OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
			  NotesTerm();
		      return FALSE;
	     }
    }
    
    /* Open the directory. */
    if (error = NSFDbOpen (szFullNetPath, &dir_handle))
    {
        OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
		NotesTerm();
		return FALSE;
    }

    if (error = NSFDbSpaceUsage(dir_handle, &dwAvalid, &dwFree))
    {
        OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
		NotesTerm();
        return FALSE;
    }

    /* Close the directory. */
    if (error = NSFDbClose (dir_handle))
    {
        OSLoadString(NULLHANDLE, ERR(error), szReturn, 1024);
		NotesTerm();
        return FALSE;
    }

	NotesTerm();
	sprintf(szReturn, "Used=%f$Free=%f$FreePer=%f$", dwAvalid/(1024.0*1024), dwFree/(1024.0*1024), 100.0*dwFree/(dwFree+dwAvalid));
    return TRUE;
}
