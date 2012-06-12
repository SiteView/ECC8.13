// SVWebSMS.h: interface for the CSVWebSMS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVWEBSMS_H__BFAF909A_733E_4C85_8E10_674435D5F848__INCLUDED_)
#define AFX_SVWEBSMS_H__BFAF909A_733E_4C85_8E10_674435D5F848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#import "../base/sms/SmSend.dll" no_namespace

class CSVWebSMS  
{
public:

	const char* GetErrMsg(int nErrCode);
	int SendSMS(CString strSMS, CString strPhone);
	int Init();
	CSVWebSMS();
	virtual ~CSVWebSMS();

protected:
	int GetResponseCode(_bstr_t bstrResponse);
	BSTR UTF2GB(LPCSTR lp, int nLen);
private:
    CString strUser;
    CString strPwd;
	IUMSmSendPtr pSender;
};

#endif // !defined(AFX_SVWEBSMS_H__BFAF909A_733E_4C85_8E10_674435D5F848__INCLUDED_)
