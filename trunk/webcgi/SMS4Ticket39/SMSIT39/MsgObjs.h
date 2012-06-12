// defs.h: interface for the defs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFS_H__773D829D_3BB1_4942_93FF_4FD533717C7B__INCLUDED_)
#define AFX_DEFS_H__773D829D_3BB1_4942_93FF_4FD533717C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _strlen strlen

// С��ͨ��������ͨѶ��Ϣ�����ͷ�װ��

// ������Ϣ�ӿ�
class ISMMsg
{
public:
	// ��ָ���ַ�������Ϊ�����������
	// strMsg = ��������Ϣ�ַ���
	// ���أ������Ϣ�ַ���������Ϣ��ʽҪ���򷵻�TRUE�����򷵻�FALSE��
	virtual BOOL SetString(CString & strMsg) = 0;
	// ȡ��Ϣ�������Ժϲ����ɵ��ַ���
	virtual CString GetString(void) = 0;
};

// ��Ϣͷ����
class CMsgHead : public ISMMsg
{
public:
	CString m_strMsgLen; // [8] �������Ϊ������Ϣ����(��Ϣͷ+��Ϣ��)�ĳ���
	                     // �������8���ֽڣ�����߲��ַ�'0'��ʹ������8���ֽڳ��ȡ�
	CString m_strMsgType; // [2] ��Ϣ����
public:
	// ��ָ���ַ�������Ϊ�����������
	// strMsg = ��������Ϣ�ַ���
	// ���أ������Ϣ�ַ���������Ϣ��ʽҪ���򷵻�TRUE�����򷵻�FALSE��
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != 10)
			return FALSE; // ���ȴ���

		CString strMsgLen = strMsg.Left(8);
		CString strMsgType = strMsg.Right(2);
		if (::atoi(strMsgLen) < 1 || ::atoi(strMsgType) < 1)
			return FALSE; // �ֶβ�������

		m_strMsgLen = strMsgLen;
		m_strMsgType = strMsgType;

		return TRUE;
	}
	// ȡ��Ϣ�������Ժϲ����ɵ��ַ���
	virtual CString GetString(void)
	{
		CString strMsg = m_strMsgLen + m_strMsgType;
		return strMsg;
	}
protected:
	// ��ǰ��Ϣ���ַ���
	enum { MSG_CHARS = 10 };
	// ������Ϣ����
	// nMsgLen = ��Ϣ����ַ����ȣ���������Ϣͷ��
	void _SetMsgLen(int nMsgLen)
	{
		m_strMsgLen.Format("%08d", CMsgHead::MSG_CHARS + nMsgLen);
	}
};

// ��Ϣ������
// �����������ͳһʵ��ISMMsg��GetString���������о������Ϣ�඼�̳��ڴ��࣬�Ӷ�
// ͳһ�̳�GetString������ʵ�֣����һ������������Ϣ������Ϣ�ַ����ϳɷ������Ҫ
// ʵ�ֺϲ�����е���Ϣ�������_GetMsgDataString���ɡ�
class CMsgObject : public CMsgHead
{
public:
	// ȡ��Ϣ�������Ժϲ����ɵ��ַ���
	virtual CString GetString(void)
	{
		CString strMsgDataString = _GetMsgDataString();
		_SetMsgLen(_strlen(strMsgDataString));
		CString strMsg = CMsgHead::GetString() + strMsgDataString;
		return strMsg;
	}
protected:
	// ����Ϣ�������Ժϳ���Ϣ�����ַ���
	virtual CString _GetMsgDataString(void) = 0;
};

// ��¼������Ϣ
// ��Ϣ���ͣ�"01"
class CMsgLogon : public CMsgObject
{
public:
	CMsgLogon() : MSG_TYPE("01")
	{
		m_strMsgType = MSG_TYPE;
	}
public:
	BOOL setUserName(CString & strUserName)
	{
		if (_strlen(strUserName) != 8)
			return FALSE;
		m_strUserName = strUserName;
		return TRUE;
	}
	CString m_strUserName; // [8] �����½���û���
	BOOL setUserPassword(CString & strUserPassword)
	{
		if (_strlen(strUserPassword) != 8)
			return FALSE;
		m_strUserPassword = strUserPassword;
		return TRUE;
	}
	CString m_strUserPassword; // [8] �����½���û���
public:
	// ��ָ���ַ�������Ϊ�����������
	// strMsg = ��������Ϣ�ַ���
	// ���أ������Ϣ�ַ���������Ϣ��ʽҪ���򷵻�TRUE�����򷵻�FALSE��
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != CMsgHead::MSG_CHARS + CMsgLogon::MSG_CHARS)
			return FALSE; // ���ȴ���

		// ȡ��Ϣͷ�����з���
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // ��Ϣͷ��ʽ����

		if (strcmp(MSG_TYPE, m_strMsgType) != 0)
			return FALSE; // ��Ϣ���ʹ���

		m_strUserName = strMsg.Mid(CMsgHead::MSG_CHARS, 8);
		m_strUserPassword = strMsg.Right(8);

		return TRUE;
	}
protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strUserName + m_strUserPassword;
	}
	// ��ǰ��Ϣ���ַ���
	enum { MSG_CHARS = 16 };
	// ��ǰ��Ϣ�����Ϣ����
	LPCTSTR MSG_TYPE;
};

// ��¼��������Ϣ
// ��Ϣ���ͣ�"11"
class CMsgLogonRes : public CMsgObject
{
public:
	CMsgLogonRes() : MSG_TYPE("11")
	{
		m_strMsgType = MSG_TYPE;
	}
public:
	CString m_strResult; // [1] �û���½״̬��0��½ʧ�ܣ�1��½�ɹ�
public:
	// ��ָ���ַ�������Ϊ�����������
	// strMsg = ��������Ϣ�ַ���
	// ���أ������Ϣ�ַ���������Ϣ��ʽҪ���򷵻�TRUE�����򷵻�FALSE��
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != CMsgHead::MSG_CHARS + CMsgLogonRes::MSG_CHARS)
			return FALSE; // ���ȴ���

		// ȡ��Ϣͷ�����з���
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // ��Ϣͷ��ʽ����

		if (strcmp(MSG_TYPE, m_strMsgType) != 0)
			return FALSE; // ��Ϣ���ʹ���

		m_strResult = strMsg.Right(1);

		return TRUE;
	}
protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strResult;
	}
	// ��ǰ��Ϣ���ַ���
	enum { MSG_CHARS = 1 };
	// ��ǰ��Ϣ�����Ϣ����
	LPCTSTR MSG_TYPE;
};

// ����������Ϣ
// ��Ϣ���ͣ�"42"
class CMsgSMData : public CMsgObject
{
public:
	CMsgSMData() : MSG_TYPE("42")
	{
		m_strMsgType = MSG_TYPE;
		m_strSendType = "2"; // [1] ���ͷ�ʽ��0�������������������ύ�������2��������������ƽ̨��������
		m_strFeeUser = "0"; // [1] �Ʒ��û����ͣ�0-��Ŀ���ֻ��Ʒ�3-������ָ���ֻ��Ʒ�
		m_strServiceID = "ABCDEF"; // [6] ������룬���Ƿѱ�ǣ���˫���̶�
		m_strDisplaySPhone = "11608851#############"; // [21] �û��ֻ���ʾ��Դ���롣������ʾCP�ĳ�����(��ʽ����д1160****����#����ʣ���ֽ�)
		m_strFeePhone = "00000000000"; // [11] ��SM_FEEUSERֵΪ3ʱ����д���Ʒ��ֻ��ĺ��룻Ϊ����ֵʱ����д����Ϊ11���ִ�'00000000000'

		// ������Ϣ��ID��username+mmddhhmmss+4λ�����к�
		m_strUserName; // [8] �û���
		CTime Time = CTime::GetCurrentTime();
		m_strTime = Time.Format("%m%d%H%M%S"); // [10] ��ǰʱ�䣬��ʽΪMMddHHmmss
		m_strSequence = "0001"; // [4] ���к�
		// ---------------------------------------------

		m_strMsgCause = "0"; // [1] ���Ų�����ԭ��0-MO����,1-�ڶ���MO������2-MT������3-����SMC���»���
		m_strDataFormat = "0"; // [1] �������ݵĴ�����ʽ��0-text 1-bin 2-���� 3-bin(Alct,simentz,eric,0x75) 9-GB232
		m_strDataTP = "00"; // [2] TP_pId��TP_udhi(��ռһ���ֽ�,ȱʡ'00')
		m_strDataLength = "0000"; // [4] �������ݵĳ��ȣ���0��
		m_strDataContent = ""; // [<140] �������ݵ����ݣ����ܳ���140���ַ���
		m_strLinkID = "#####################"; // [21] LINKID���Ȳ���ʱʹ��"#"���в��룬��LINKIDʱ��ȫ��Ϊ"#"
		m_strPhonesLength = "0011"; // [4] Ŀ���ֻ�������ܳ��ȣ���0��
		m_strPhones = "13910000001"; // [>11 & <1100] ���Ͷ�����ֻ����롣���Ⱥ�����Զ��Ÿ��������ܳ���100���ֻ����룬ĿǰȺ����Ч��
	}
public:
	CString m_strSendType; // [1] ���ͷ�ʽ��0�������������������ύ�������2��������������ƽ̨��������
	CString m_strFeeUser; // [1] �Ʒ��û����ͣ�0-��Ŀ���ֻ��Ʒ�3-������ָ���ֻ��Ʒ�
	CString m_strServiceID; // [6] ������룬���Ƿѱ�ǣ���˫���̶�
	BOOL setDisplaySPhone(CString & strDisplaySPhone)
	{
		int nLen = _strlen(strDisplaySPhone);
		if (nLen > 21)
			return FALSE;
		char szFill[] = {"#####################"};
		szFill[21 - nLen] = char('\0');
		m_strDisplaySPhone = strDisplaySPhone + szFill;
		return TRUE;
	}
	CString m_strDisplaySPhone; // [21] �û��ֻ���ʾ��Դ���롣������ʾCP�ĳ�����(��ʽ����д1160****����#����ʣ���ֽ�)
	CString m_strFeePhone; // [11] ��SM_FEEUSERֵΪ3ʱ����д���Ʒ��ֻ��ĺ��룻Ϊ����ֵʱ����д����Ϊ11���ִ�'00000000000'

	// ������Ϣ��ID��username+mmddhhmmss+4λ�����к�
	CString m_strUserName; // [8] �û���
	CString m_strTime; // [10] ��ǰʱ�䣬��ʽΪMMddHHmmss
	CString m_strSequence; // [4] ���к�
	// ---------------------------------------------

	CString m_strMsgCause; // [1] ���Ų�����ԭ��0-MO����,1-�ڶ���MO������2-MT������3-����SMC���»���
	CString m_strDataFormat; // [1] �������ݵĴ�����ʽ��0-text 1-bin 2-���� 3-bin(Alct,simentz,eric,0x75) 9-GB232
	CString m_strDataTP; // [2] TP_pId��TP_udhi(��ռһ���ֽ�,ȱʡ'00')
	CString m_strDataLength; // [4] �������ݵĳ��ȣ���0��
	// ���ö�������
	// strDataContent = ���������ı�
	// ����ֵ������ɹ��򷵻�һ��""�ַ�������strDataContent����140�ַ�ʱ�����ض�����ַ�����
	CString SetDataContent(CString & strDataContent)
	{
		int nMaxContent = 139;
		if (int(_strlen(strDataContent)) > nMaxContent)
		{// ���ĳ�����Ҫ�ض�

			int nCharType = GetCharType(strDataContent, nMaxContent - 1);
			switch(nCharType)
			{// �жϽضϺ��ַ������һ���ַ�������
			case 0: // Ӣ���ַ�
				if (strDataContent[nMaxContent - 1] != char(' ') &&
					strDataContent[nMaxContent] != char(' ') &&
					GetCharType(strDataContent, nMaxContent) == 0)
				{// �Ͽ�ǰ�ַ���Ϊ' '&&�Ͽں��ַ���Ϊ' '&&���߶Ͽں��ַ���������

					// �ӶϿڴ���������������Ϊ���е��λ��
					CString strTemp = strDataContent.Left(nMaxContent);
					int nSPos = ReverseFindBreakpoint(strTemp);
					if (nSPos > 0)
						nMaxContent = nSPos + 1; // �����趨�ض�λ��
				}
				break;
			case 1: // ���ĵĵ�һ���ֽ�
				// ����ض�λ��������ĳ�������ַ��ĵ�һ���ֽ���ض�λ�ú���һ���ֽ��Ա���ض������ַ�
				++nMaxContent; 
				break;
			case 2: // ���ĵĵڶ����ֽ�
				break;
			}
		}
		m_strDataContent = strDataContent.Left(nMaxContent);
		CString strRet = strDataContent.Mid(nMaxContent);
		m_strDataLength.Format("%04d", _strlen(m_strDataContent));
		return strRet;
	}
	CString m_strDataContent; // [<140] �������ݵ����ݣ����ܳ���140���ַ���
	CString m_strLinkID; // [21] LINKID���Ȳ���ʱʹ��"#"���в��룬��LINKIDʱ��ȫ��Ϊ"#"
	CString m_strPhonesLength; // [4] Ŀ���ֻ�������ܳ��ȣ���0��
	// ����Ŀ���ֻ�����
	// strPhones = �ֻ�����
	// ����ֵ������ɹ��򷵻�һ��""�ַ�������strPhones����1100�ַ�ʱ�����ض�����ַ�����
	// ���󣺵�strPhones�ַ������Ȳ���11ʱ������ȫ��strPhonesԭ�ġ�
	CString SetPhones(CString & strPhones)
	{
		if (_strlen(strPhones) < 11)
			return strPhones;

		m_strPhones = strPhones.Left(1100);
		CString strRet = strPhones.Mid(1100);
		m_strPhonesLength.Format("%04d", _strlen(m_strPhones));
		return strRet;
	}
	CString m_strPhones; // [>11 & <1100] ���Ͷ�����ֻ����롣���Ⱥ�����Զ��Ÿ��������ܳ���100���ֻ����룬ĿǰȺ����Ч��

public:
	// ��ָ���ַ�������Ϊ�����������
	// strMsg = ��������Ϣ�ַ���
	// ���أ������Ϣ�ַ���������Ϣ��ʽҪ���򷵻�TRUE�����򷵻�FALSE��
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) < CMsgHead::MSG_CHARS + CMsgSMData::MSG_CHARS)
			return FALSE; // ���ȴ���

		// ȡ��Ϣͷ�����з���
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // ��Ϣͷ��ʽ����

		if (strcmp(MSG_TYPE, m_strMsgType) != 0)
			return FALSE; // ��Ϣ���ʹ���

		m_strSendType = strMsg.Mid(CMsgHead::MSG_CHARS + 0, 1); // [1] ���ͷ�ʽ��0�������������������ύ�������2��������������ƽ̨��������
		m_strFeeUser = strMsg.Mid(CMsgHead::MSG_CHARS + 1, 1); // [1] �Ʒ��û����ͣ�0-��Ŀ���ֻ��Ʒ�3-������ָ���ֻ��Ʒ�
		m_strServiceID = strMsg.Mid(CMsgHead::MSG_CHARS + 2, 6); // [6] ������룬���Ƿѱ�ǣ���˫���̶�
		m_strDisplaySPhone = strMsg.Mid(CMsgHead::MSG_CHARS + 8, 21); // [21] �û��ֻ���ʾ��Դ���롣������ʾCP�ĳ�����(��ʽ����д1160****����#����ʣ���ֽ�)
		m_strFeePhone = strMsg.Mid(CMsgHead::MSG_CHARS + 29, 11); // [11] ��SM_FEEUSERֵΪ3ʱ����д���Ʒ��ֻ��ĺ��룻Ϊ����ֵʱ����д����Ϊ11���ִ�'00000000000'

		// ������Ϣ��ID��username+mmddhhmmss+4λ�����к�
		m_strUserName = strMsg.Mid(CMsgHead::MSG_CHARS + 40, 8); // [8] �û���
		m_strTime = strMsg.Mid(CMsgHead::MSG_CHARS + 48, 10); // [10] ��ǰʱ�䣬��ʽΪMMddHHmmss
		m_strSequence = strMsg.Mid(CMsgHead::MSG_CHARS + 58, 4); // [4] ���к�
		// ---------------------------------------------

		m_strMsgCause = strMsg.Mid(CMsgHead::MSG_CHARS + 62, 1); // [1] ���Ų�����ԭ��0-MO����,1-�ڶ���MO������2-MT������3-����SMC���»���
		m_strDataFormat = strMsg.Mid(CMsgHead::MSG_CHARS + 63, 1); // [1] �������ݵĴ�����ʽ��0-text 1-bin 2-���� 3-bin(Alct,simentz,eric,0x75) 9-GB232
		m_strDataTP = strMsg.Mid(CMsgHead::MSG_CHARS + 64, 2); // [2] TP_pId��TP_udhi(��ռһ���ֽ�,ȱʡ'00')
		m_strDataLength = strMsg.Mid(CMsgHead::MSG_CHARS + 66, 4); // [4] �������ݵĳ��ȣ���0��
		int nDataLength = ::atoi(m_strDataLength);
		m_strDataContent = strMsg.Mid(CMsgHead::MSG_CHARS + 70, nDataLength); // [<140] �������ݵ����ݣ����ܳ���140���ַ���
		m_strLinkID = strMsg.Mid(CMsgHead::MSG_CHARS + 70 + nDataLength, 21); // [21] LINKID���Ȳ���ʱʹ��"#"���в��룬��LINKIDʱ��ȫ��Ϊ"#"
		m_strPhonesLength = strMsg.Mid(CMsgHead::MSG_CHARS + 91 + nDataLength, 4); // [4] Ŀ���ֻ�������ܳ��ȣ���0��
		int nPhoneLength = ::atoi(m_strPhonesLength);
		m_strPhones = strMsg.Mid(CMsgHead::MSG_CHARS + 95 + nDataLength, nPhoneLength); // [>11 & <1100] ���Ͷ�����ֻ����롣���Ⱥ�����Զ��Ÿ��������ܳ���100���ֻ����룬ĿǰȺ����Ч��

		return TRUE;
	}

protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strSendType +
			m_strFeeUser +
			m_strServiceID +
			m_strDisplaySPhone +
			m_strFeePhone +
			m_strUserName +
			m_strTime +
			m_strSequence +
			m_strMsgCause +
			m_strDataFormat +
			m_strDataTP +
			m_strDataLength +
			m_strDataContent +
			m_strLinkID +
			m_strPhonesLength +
			m_strPhones;
	}
	// ��ǰ��Ϣ���ַ���(�����ʾ��Сֵ����Ϊ�����Ϣ�ĳ����ǲ�����)
	enum { MSG_CHARS = 106 };
	// ��ǰ��Ϣ�����Ϣ����
	LPCTSTR MSG_TYPE;
};

// ҵ�����ݷ�����Ϣ
// ��Ϣ���ͣ�"32" or "12"
class CMsgSMDataRes : public CMsgObject
{
public:
	CMsgSMDataRes() : MSG_TYPE("12"), MSG_TYPE2("32")
	{
		m_strMsgType = MSG_TYPE;
	}
public:
	CString m_strResult; // [1] �������ݵ�״̬��0�ύ����ʧ�ܣ�1�������ݳɹ���2��������ʧ�ܣ�3��������ݸ�ʽ��4�ڻ�����Ч�û���5���ݺ��зǷ��ַ�
public:
	// ��ָ���ַ�������Ϊ�����������
	// strMsg = ��������Ϣ�ַ���
	// ���أ������Ϣ�ַ���������Ϣ��ʽҪ���򷵻�TRUE�����򷵻�FALSE��
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != CMsgHead::MSG_CHARS + CMsgSMDataRes::MSG_CHARS)
			return FALSE; // ���ȴ���

		// ȡ��Ϣͷ�����з���
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // ��Ϣͷ��ʽ����

		if (strcmp(MSG_TYPE, m_strMsgType) != 0 &&
			strcmp(MSG_TYPE2, m_strMsgType) != 0)
			return FALSE; // ��Ϣ���ʹ���

		m_strResult = strMsg.Right(1);

		return TRUE;
	}
protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strResult;
	}
	// ��ǰ��Ϣ���ַ���
	enum { MSG_CHARS = 1 };
	// ��ǰ��Ϣ�����Ϣ����
	LPCTSTR MSG_TYPE;
	// ��ǰ��Ϣ��ĵڶ����Ϸ���Ϣ����
	LPCTSTR MSG_TYPE2;
};

#endif // !defined(AFX_DEFS_H__773D829D_3BB1_4942_93FF_4FD533717C7B__INCLUDED_)
