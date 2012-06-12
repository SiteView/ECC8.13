// oracledsnSet.h: CoracledsnSet ��Ľӿ�
//


#pragma once

// ���������� 2006��12��12��, 13:24

class CoracledsnSet : public CRecordset
{
public:
	CoracledsnSet(CDatabase* pDatabase = NULL, CString str = "");
	DECLARE_DYNAMIC(CoracledsnSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringA	m_SENDID;
	CStringA	m_FILIALEID;
	CStringA	m_FUNCTIONID;
	CStringA	m_MOBILE;
	CStringA	m_WORKNO;
	CStringA	m_CONTENT;
	CTime	m_COMMITTIME;
	CTime	m_SENDTIME;
	CStringA	m_STATUS;
	CStringA	m_DBLINK_FLAG;
	CStringA	m_COMPANY_FLAG;
	CStringA	m_SPFLAG;
	double	m_XLT_SENDID;

	CString connstr;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

