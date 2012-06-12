// emailTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "mysendmail.h"
using namespace SiteView_MySenderMail;

int _tmain(int argc, _TCHAR* argv[])
{
	MySendMail* mail = MySendMail::GetInstance();
	mail->content = "hello world";
	mail->mailSubject = "warning-email 工工工工工 工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工工";
/*	mail->password = "197010";
	mail->user = "jiewen.zhang@dragonflow.com";
	mail->receiverAddress = "jiewen.zhang@dragonflow.com";
	mail->receiverName = "Customer";
	mail->senderAddress = "jiewen.zhang@dragonflow.com";
	mail->sendName = "SiteView";
	mail->smptAddress = "mail.dragonflow.com";

	mail->SendMail ();
*/

	mail->password = "zjw1970";
	mail->user = "jiewen_z";
	mail->receiverAddress = "jiewen.zhang@dragonflow.com";
	mail->receiverName = "Customer";
	mail->senderAddress = "jiewen_z@21cn.com";
	mail->sendName = "SiteView";
	mail->smptAddress = "smtp.21cn.com";
	mail->SendMail ();
	return 0;
}

