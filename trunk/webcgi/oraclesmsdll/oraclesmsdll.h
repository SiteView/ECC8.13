// oraclesmsdll.h : oraclesmsdll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CoraclesmsdllApp
// �йش���ʵ�ֵ���Ϣ������� oraclesmsdll.cpp
//

class CoraclesmsdllApp : public CWinApp
{
public:
	CoraclesmsdllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
