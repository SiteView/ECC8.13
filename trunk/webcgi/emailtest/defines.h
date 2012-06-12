
#ifndef _SV_MAIL_SET_DEFINES_H_
#define _SV_MAIL_SET_DEFINES_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>

using namespace std;

typedef struct _SEND_MAIL_PARAM 
{
    string m_szServer;
    string m_szFrom;
    string m_szBackServer;
    string m_szUserID;
    string m_szPwd;
}SEND_MAIL_PARAM, *LPSEND_MAIL_PARAM;

#endif