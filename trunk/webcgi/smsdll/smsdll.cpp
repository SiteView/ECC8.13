// smsdll.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>

using namespace std;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C" __declspec(dllexport) int getinfo(string&retstr)
{
	retstr = "�û��Զ�����ŷ��ͽӿ�";
	return 1;
}

extern "C" __declspec(dllexport) int run(char * source, char * destination, char * content)
{
	char buf[256];

	bool bRet = Beep(1000, 1000);
  
	OutputDebugString("------------------call smsdll run()------------------------\n");
	if(bRet)
	{
		OutputDebugString("----------------self define sms send from dll output-------------------\n");
		sprintf(buf, "param1:%s param2:%s param3:%s", source, destination, content);
		OutputDebugString(buf);
		OutputDebugString("\n");
	}
	return 1;
}