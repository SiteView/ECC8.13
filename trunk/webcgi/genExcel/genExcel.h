// genExcel.h : genExcel DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// 主符号


// CgenExcelApp
// 有关此类实现的信息，请参阅 genExcel.cpp
//

class CgenExcelApp : public CWinApp
{
public:
	CgenExcelApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
