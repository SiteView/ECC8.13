// msdesmsdll.h : msdesmsdll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CmsdesmsdllApp
// �йش���ʵ�ֵ���Ϣ������� msdesmsdll.cpp
//

class CmsdesmsdllApp : public CWinApp
{
public:
	CmsdesmsdllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
