// SMSonWebService.h : SMSonWebService DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CSMSonWebServiceApp
// �йش���ʵ�ֵ���Ϣ������� SMSonWebService.cpp
//

class CSMSonWebServiceApp : public CWinApp
{
public:
	CSMSonWebServiceApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
