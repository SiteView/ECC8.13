#ifndef _SiteView_ECC_Print_Debug_H_
#define _SiteView_ECC_Print_Debug_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>

using namespace std;

// windows
// 在Dbmon.exe中显示调试信息
void PrintDebugString(const char* pcszMsg = NULL);

void PrintDebugString(const string &szMsg);

#endif