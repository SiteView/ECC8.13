// genExcel.h : genExcel DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CgenExcelApp
// �йش���ʵ�ֵ���Ϣ������� genExcel.cpp
//

class CgenExcelApp : public CWinApp
{
public:
	CgenExcelApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
