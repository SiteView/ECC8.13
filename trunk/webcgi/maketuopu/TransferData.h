// TransferData.h: interface for the CTransferData class.
//
//////////////////////////////////////////////////////////////////////
#include "afxtempl.h"			// xiao quan

#if !defined(AFX_TRANSFERDATA_H__0B34D7B2_DDAA_4C5D_8EA8_649DDD8D0429__INCLUDED_)
#define AFX_TRANSFERDATA_H__0B34D7B2_DDAA_4C5D_8EA8_649DDD8D0429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTransferData : public CObject  
{
	DECLARE_DYNCREATE(CTransferData)
public:
	CTransferData();
	virtual ~CTransferData();

public:

	//SV_Ip
	CString m_strIP;
	
	//SV_App
	CString m_strApp;
	
	//SV_Group
	CString m_strGroup;
	
	//SV_Entity
	CString m_strEntity;
	
	//SV_Monitor
	CString m_strMonitor;
	
	//SV_Link
	CString m_strLinkPage;

	//SV_Des
	CString m_strDes;

	//parentid链表
	CStringList m_lstParentId;

	//monitorid链表
	CStringList m_lstMonitorId;

	//状态链表
	CStringList m_lstStatus;

	//菜单项描述链表
	CStringList m_lstMenuItemDes;
};

typedef CTypedPtrList<CObList, CTransferData*> CTransferDataList;

#endif // !defined(AFX_TRANSFERDATA_H__0B34D7B2_DDAA_4C5D_8EA8_649DDD8D0429__INCLUDED_)
