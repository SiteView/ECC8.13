// oracledsnSet.cpp : CoracledsnSet 类的实现
//

#include "stdafx.h"
#include "oraclesmsdll.h"
#include "oracledsnSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CoracledsnSet 实现

// 代码生成在 2006年12月12日, 13:24

IMPLEMENT_DYNAMIC(CoracledsnSet, CRecordset)

CoracledsnSet::CoracledsnSet(CDatabase* pdb, CString str)
	: CRecordset(pdb)
{
	m_SENDID = "";
	m_FILIALEID = "";
	m_FUNCTIONID = "";
	m_MOBILE = "";
	m_WORKNO = "";
	m_CONTENT = "";
	m_COMMITTIME;
	m_SENDTIME;
	m_STATUS = "";
	m_DBLINK_FLAG = "";
	m_COMPANY_FLAG = "";
	m_SPFLAG = "";
	m_XLT_SENDID = 0.0;
	m_nFields = 13;
	m_nDefaultType = dynaset;

	connstr = str;
}
//#error Security Issue: The connection string may contain a password
// 此连接字符串中可能包含密码
// 下面的连接字符串中可能包含明文密码和/或
// 其他重要信息。请在查看完
// 此连接字符串并找到所有与安全有关的问题后移除 #error。可能需要
// 将此密码存储为其他格式或使用其他的用户身份验证。
CString CoracledsnSet::GetDefaultConnect()
{
	CString str = connstr;
	//str += ";DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;GDE=F;FRL=F;BAM=IfAllSuccessful;MTS=F;MDI=F;CSR=F;FWC=F;PFC=10;TLO=0;";
	//return _T("DSN=oracle1;UID=SMSUSER;PWD=KENNY;DBQ=ORACLE ;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;GDE=F;FRL=F;BAM=IfAllSuccessful;MTS=F;MDI=F;CSR=F;FWC=F;PFC=10;TLO=0;");
	OutputDebugString("------------GetDefaultConnect()---------------\n");
	OutputDebugString(str.GetBuffer());

	return str.AllocSysString();
}

CString CoracledsnSet::GetDefaultSQL()
{
	return _T("[SMSUSER].[SM_SEND_LR]");
}

void CoracledsnSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[SENDID]"), m_SENDID);
	RFX_Text(pFX, _T("[FILIALEID]"), m_FILIALEID);
	RFX_Text(pFX, _T("[FUNCTIONID]"), m_FUNCTIONID);
	RFX_Text(pFX, _T("[MOBILE]"), m_MOBILE);
	RFX_Text(pFX, _T("[WORKNO]"), m_WORKNO);
	RFX_Text(pFX, _T("[CONTENT]"), m_CONTENT);
	RFX_Date(pFX, _T("[COMMITTIME]"), m_COMMITTIME);
	RFX_Date(pFX, _T("[SENDTIME]"), m_SENDTIME);
	RFX_Text(pFX, _T("[STATUS]"), m_STATUS);
	RFX_Text(pFX, _T("[DBLINK_FLAG]"), m_DBLINK_FLAG);
	RFX_Text(pFX, _T("[COMPANY_FLAG]"), m_COMPANY_FLAG);
	RFX_Text(pFX, _T("[SPFLAG]"), m_SPFLAG);
	RFX_Double(pFX, _T("[XLT_SENDID]"), m_XLT_SENDID);

}
/////////////////////////////////////////////////////////////////////////////
// CoracledsnSet 诊断

#ifdef _DEBUG
void CoracledsnSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CoracledsnSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

