#ifndef _SiteView_ECC_Print_Debug_H_
#define _SiteView_ECC_Print_Debug_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>

using namespace std;

// windows
// ��Dbmon.exe����ʾ������Ϣ
void PrintDebugString(const char* pcszMsg = NULL);

void PrintDebugString(const string &szMsg);

#endif