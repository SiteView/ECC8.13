// DnsMonitor.h : main header file for the DNSMONITOR DLL
//

#if !defined(AFX_DNSMONITOR_H__92413A01_E071_4D9D_9440_6F26DE40F0A4__INCLUDED_)
#define AFX_DNSMONITOR_H__92413A01_E071_4D9D_9440_6F26DE40F0A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDnsMonitorApp
// See DnsMonitor.cpp for the implementation of this class
//

#define		__MACHINETYPE__					"_MachineType="
#define		__OSTYPE__						"_OsType="
//wangpeng  
#define		__ServerPort__					"_ServerPort="
#define		__MACHINENAME__					"_MachineName="
#define		__USERACCOUNT__					"_UserAccount="
#define		__PASSWORD__					"_PassWord="
#define		__PROMPT__						"_Prompt="
#define		__LOGINPROMPT__					"_LoginPrompt="
#define		__PASSWORDPROMPT__				"_PWPrompt="
#define		__PROTOCOLTYPE__				"_ProtocolType="
#define		__SERVERPORT__					"_ServerPort="
#define		__DOWNLOADFILE__				"_DownLoadFile="
#define		__TIMEOUT__						"_TimeOut="
#define		__PORT__						"_connPort="
#define		__SENDSTR__						"_SendStr="
#define		__MATCHSTR__					"_MatchStr="
#define		__DSNNAME__						"_DsnName="
#define		__SQLSTR__						"_SqlStr="
#define		__REQUIREID__					"_RequireID="
#define		__COMMUNITY__					"_Community="
#define		__DOMAINNAME__					"_DomName="
#define		__MATCHIP__						"_MatchIP="
#define		__DIRECTORY__					"_Directory="
#define		__ISSUBDIR__					"_IsSubDir="
#define		__FILEPATH__					"_FilePath="
#define		__SERVICE__						"_Service="
#define		__DISK__						"_Disk="
#define		__SERVERMANURL__				"_ServerManUrl="
#define		__SENDBYTES__					"_SendBytes="
#define		__CPUNUM__						"_CpuNum="
#define		__DETAIL__						"_Detail="
#define		__TRACE__						"_Trace="

#define		__PROXYSERVERPORT__				"_ProxyServerPort="
#define		__PROXYUSERNAME__				"_ProxyUser="
#define		__PROXYPASSWORD__				"_ProxyPass="
#define		__RETRYDELAY__					"_RetryDelay="
#define		__CONNECTTIMEOUT__				"_ConnTimeout="
#define		__QUERYTIMEOUT__				"_QueryTimeout="
#define		__PASSIVEMODE__					"_PassiveMode="
#define		__PROVIDER__					"_Provider="
#define		__PRINCIPAL__					"_Principal="
#define		__CREDENTIALS__					"_Credentials="
#define		__QUERY__						"_Query="
#define		__FILTER__						"_Filter="
#define		__SMTPSERVERPORT__				"_SmtpServPort="
#define		__RCPTSERVERPORT__				"_RcptServPort="
#define		__MAILTYPE__					"_MailType="
#define		__MAILPROTOCOLTYPE__			"_MailProtocolType="
#define		__FROMADDRESS__					"_SendAddress="
#define		__RCPTADDRESS__					"_RcptAddress="
#define		__CHECKDELAY__					"_CheckDelay="
#define		__ATTACHMENT__					"_Attachment="
#define		__SECRET__						"_Secret="
#define		__INDEX__						"_Index="
#define		__INTERFACEINDEX__				"_InterfaceIndex="
#define		__GROUP__						"_Group="
#define		__CONNECTADDRESS__				"_ConnAddr="
#define		__URL__							"_URL="
#define		__STOPTIME__					"_StopTime="
#define		__PROXYTYPE__					"_ProxyType="
#define		__POSTDATA__					"_PostData="
#define		__ENABLEPASSWORD__				"_EnablePassword="
#define		__ENABLEPASSWORDPROMPT__		"_EnablePasswordPrompt="
#define		__ENABLEPROMPT__				"_EnalbePrompt="
#define		__VERIFYUSERNAME__				"_VerifyUsername="
#define		__VERIFYPASSWORD__				"_VerifyPassword="
#define		__REQUESTADDRESS__				"_RequestAddress="
#define		__MQQUEUEMANAGER__				"_MQQueueManager="
#define		__MQQUEUENAME__					"_MQQueueName="
#define		__INSTANCE__					"_Instance="
#define		__ALERTTYPE__					"_AlertType="
#define		__LOGFILE__						"_LogFilePathname="
#define		__RULEFILE__					"_RuleFile="
#define		__CUSTOMERPATH__				"_CustomerPath="
#define		__APPENDMETHOD__				"_AppendMethod="
#define		__GTJAID__						"_ID="
#define		__PARAMETERS__					"_Parameters="
#define		__SCRIPT__						"_Script="
#define		__SERVERNAME__					"_ServerName="
#define		__NEEDAUTH__					"_IsSMTPAu="
#define		__VPNCONNECTION__				"_VpnConn="
#define		__DIALBEFOREVPN__				"_DialBeforeVpn="
#define		__DIALCONNECTION__				"_DialConn="
#define		__USERACCOUNTD__				"_UserAccountD="
#define		__PASSWORDD__					"_PassWordD="
#define		__DOMAINNAMED__					"_DomNameD="
#define		__CLUSTERLOG__					"_ClusterLogPath="
#define		__RUNNING_CONFIG__				"_RunCmd="

#define		__GROUPID__						"_GroupID="  // xiao quan
#define		__MONITORID__					"_MonitorID="// xiao quan

#define		DNS_TIMEOUT				1*60

class CDnsMonitorApp : public CWinApp
{
public:
	CDnsMonitorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDnsMonitorApp)
	public:
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDnsMonitorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNSMONITOR_H__92413A01_E071_4D9D_9440_6F26DE40F0A4__INCLUDED_)
