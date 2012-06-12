#include "stdafx.h"
#include "mysendmail.h"

using namespace SiteView_MySenderMail;
using namespace MUtils;

MySendMail* MySendMail::m_sendmail = NULL;

MySendMail::MySendMail(void)
{
	smptAddress = NULL;
	content = NULL;
	sendName = NULL;
	senderAddress = NULL;
	receiverAddress = NULL;
	mailSubject = NULL;
	receiverName = NULL;
	user = NULL;
	password = NULL;
}

MySendMail::~MySendMail(void)
{
	
}
bool MySendMail::SendMail()
{
	if(!smptAddress || !content || !sendName || !senderAddress || !receiverAddress || !mailSubject
		|| !user || !password || !receiverName)
	{
		return false;
	}
	WinSockHelper wshelper;
	SMailer::TextPlainContent  mailContent(content);
	SMailer::MailInfo info;
	info.setSenderName(sendName);
    info.setSenderAddress(senderAddress);
    info.addReceiver(receiverName, receiverAddress);
    
    info.setPriority(SMailer::Priority::normal);
    info.setSubject(mailSubject);
    info.addMimeContent(&mailContent);

	try
    {
		sender.GetMailBaseInfo(smptAddress, user, password);
        sender.setMail(&SMailer::MailWrapper(&info));
        sender.sendMail();
    }
    catch (SMailer::MailException& e)
    {
		sender.quit();
        return false;
    }
    catch (...)
    {
		sender.quit();
        return false;
    }
	return true;
}

MySendMail* MySendMail::GetInstance()
{
	if(m_sendmail == NULL)
	{
		m_sendmail = new MySendMail();
	}
	return m_sendmail;
}
void MySendMail::DisposeInstance()
{
	if(m_sendmail != NULL)
	{
		delete m_sendmail;
	}
	m_sendmail = NULL;
}