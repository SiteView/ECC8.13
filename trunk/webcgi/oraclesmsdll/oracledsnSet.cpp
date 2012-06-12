// oracledsnSet.cpp : CoracledsnSet ���ʵ��
//

#include "stdafx.h"
#include "oraclesmsdll.h"
#include "oracledsnSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CoracledsnSet ʵ��

// ���������� 2006��12��12��, 13:24

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
// �������ַ����п��ܰ�������
// ����������ַ����п��ܰ������������/��
// ������Ҫ��Ϣ�����ڲ鿴��
// �������ַ������ҵ������밲ȫ�йص�������Ƴ� #error��������Ҫ
// ��������洢Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// CoracledsnSet ���

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

