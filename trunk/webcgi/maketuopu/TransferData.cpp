// TransferData.cpp: implementation of the CTransferData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransferData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CTransferData, CObject)

CTransferData::CTransferData()
{
	m_strIP = _T("");
	m_strLinkPage = _T("");
	m_strApp = _T("");
	m_strGroup = _T("");
	m_strEntity = _T("");
	m_strMonitor = _T("");
	m_strDes = _T("");

	//m_strHostName = _T("");
	//m_strMachine = _T("");
	//m_strAlias = _T("");
	//m_strTemplate = _T("");
	//m_strIndex = _T("");
}

CTransferData::~CTransferData()
{
	m_lstParentId.RemoveAll();
	m_lstMonitorId.RemoveAll();
	m_lstStatus.RemoveAll();
	m_lstMenuItemDes.RemoveAll();
}