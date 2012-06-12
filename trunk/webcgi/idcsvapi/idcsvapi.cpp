// idcsvapi.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "idcsvapi.h"

#include <svapi.h>
#include <windows.h>
#include "WebSession.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

// ���ǵ���������һ��ʾ��
IDCSVAPI_API int nidcsvapi=0;

// ���ǵ���������һ��ʾ����
IDCSVAPI_API int fnidcsvapi(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� idcsvapi.h
Cidcsvapi::Cidcsvapi()
{ 
	return; 
}

string strUserID = "";

////////////////////////////////// ini API/////////////////////////////////////////////////

//ÿ��ini �ļ������ж�� section, ÿ��section �����ж���� key = value �������ݶ�
//ÿһ��key ���������ͣ� int��string, binary ,����д�������Ӧ����

IDCSVAPI_API
bool GetIniFileSections_2(std::list<string> &sectionlist,string filename,string addr,string user)
{	
	#ifndef IDC_Version
		return GetIniFileSections(sectionlist,filename,addr,user);
	#else		
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();			
		}
		
		//OutputDebugString("GetIniFileSections_2:");
		//OutputDebugString(strUserID.c_str());
		
		return GetIniFileSections(sectionlist,filename,addr,strUserID);
	#endif

	
}

//��ȡĳ��ini�ļ������е� section  ��//���� section��list ���ã� ini�ļ�����SVDB ��ַ�� idc�û�id
IDCSVAPI_API
bool GetIniFileKeys_2(string section,std::list<string> &keylist,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return GetIniFileKeys(section,keylist,filename, addr, user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();			
		}
		
		//OutputDebugString("GetIniFileKeys_2:");
		//OutputDebugString(strUserID.c_str());

		return GetIniFileKeys(section,keylist,filename, addr, strUserID);

	#endif
}

//��ȡĳ��section �µ����е�key
IDCSVAPI_API
int	GetIniFileValueType_2(string section,string key,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return GetIniFileValueType(section,key, filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();			
		}

		//OutputDebugString("GetIniFileValueType_2:");
		//OutputDebugString(strUserID.c_str());

		return GetIniFileValueType(section,key, filename,addr,strUserID);
	#endif
}

//��ȡĳ�� key ������
// ����key������дini��3������ ��// section����   key ����value ֵ��  ini�ļ�����SVDB ��ַ�� idc�û�id
IDCSVAPI_API
bool WriteIniFileString_2(string section,string key,string str,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return WriteIniFileString(section, key, str,filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();				
		}

		//OutputDebugString("WriteIniFileString_2:");
		//OutputDebugString(strUserID.c_str());
		return WriteIniFileString(section,key, str,filename,addr,strUserID);
	#endif
}

IDCSVAPI_API
bool WriteIniFileInt_2(string section,string key,int value,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return WriteIniFileInt(section,key,value,filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}
		
		//OutputDebugString("WriteIniFileInt_2:");
		//OutputDebugString(strUserID.c_str());
		return WriteIniFileInt(section,key,value,filename,addr,strUserID);
	#endif
}

IDCSVAPI_API
bool WriteIniFileStruct_2(string section,string key, void *data,unsigned int len,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return WriteIniFileStruct(section,key,data, len, filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}

		//OutputDebugString("WriteIniFileStruct_2:");
		//OutputDebugString(strUserID.c_str());
		return WriteIniFileStruct(section,key,data, len, filename,addr,strUserID);
	#endif
}


// ����key�����Ͷ�ini��3��������            // Ĭ�Ϸ���ֵ������裩
IDCSVAPI_API
string GetIniFileString_2(string section,string key,string defaultret,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return GetIniFileString(section,key,defaultret,filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}
		
		//OutputDebugString("GetIniFileString_2:");
		//OutputDebugString(strUserID.c_str());
		return GetIniFileString(section,key, defaultret, filename,addr,strUserID);
	#endif
}

IDCSVAPI_API
int	GetIniFileInt_2(string section,string key,int defaultret,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return GetIniFileInt(section,key, defaultret, filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}
		
		//OutputDebugString("GetIniFileInt_2:");
		//OutputDebugString(strUserID.c_str());
		return GetIniFileInt(section,key, defaultret, filename,addr,strUserID);
	#endif
}

IDCSVAPI_API
bool GetIniFileStruct_2(string section,string key,void *buf,unsigned int &len,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return GetIniFileStruct(section,key,buf,len,filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}

		//OutputDebugString("GetIniFileStruct_2:");
		//OutputDebugString(strUserID.c_str());
		return GetIniFileStruct(section,key,buf,len,filename,addr,strUserID);
	#endif
}


IDCSVAPI_API
bool DeleteIniFileSection_2(string section,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return DeleteIniFileSection(section,filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}

		//OutputDebugString("DeleteIniFileSection_2:");
		//OutputDebugString(strUserID.c_str());
		return DeleteIniFileSection(section,filename,addr,strUserID);
	#endif
}
//ɾ��ĳ�� section

IDCSVAPI_API
bool DeleteIniFileKey_2(string section,string key,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return DeleteIniFileKey(section,key, filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();				
		}

		//OutputDebugString("DeleteIniFileKey_2:");
		//OutputDebugString(strUserID.c_str());
		return DeleteIniFileKey(section,key, filename,addr,strUserID);
	#endif
}
//ɾ��ĳ�� key


IDCSVAPI_API
bool EditIniFileSection_2(string oldsection,string newsection,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return EditIniFileSection(oldsection,newsection,filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();		
		}

		//OutputDebugString("EditIniFileSection_2:");
		//OutputDebugString(strUserID.c_str());
		return EditIniFileSection(oldsection,newsection,filename,addr,strUserID);
	#endif
}
//�޸�ĳ�� section

IDCSVAPI_API
bool EditIniFileKey_2(string section,string oldkey,string newkey,string filename,string addr,string user)
{
	#ifndef IDC_Version
		return EditIniFileKey(section,oldkey, newkey, filename,addr,user);
	#else
		if(user.compare("root") == 0)
		{
			strUserID = "default";			
		}
		else
		{
			strUserID = GetWebIdcUserID();			
		}

		//OutputDebugString("EditIniFileKey_2:");
		//OutputDebugString(strUserID.c_str());
		return EditIniFileKey(section,oldkey, newkey, filename,addr,strUserID);
	#endif

}
//�޸�ĳ�� key
