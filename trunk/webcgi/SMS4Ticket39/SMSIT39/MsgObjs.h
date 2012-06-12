// defs.h: interface for the defs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFS_H__773D829D_3BB1_4942_93FF_4FD533717C7B__INCLUDED_)
#define AFX_DEFS_H__773D829D_3BB1_4942_93FF_4FD533717C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _strlen strlen

// 小灵通短信网关通讯消息解析和封装类

// 短信消息接口
class ISMMsg
{
public:
	// 将指定字符串解析为各项独立属性
	// strMsg = 完整的消息字符串
	// 返回：如果消息字符串符合消息格式要求则返回TRUE，否则返回FALSE。
	virtual BOOL SetString(CString & strMsg) = 0;
	// 取消息各项属性合并而成的字符串
	virtual CString GetString(void) = 0;
};

// 消息头定义
class CMsgHead : public ISMMsg
{
public:
	CString m_strMsgLen; // [8] 填充内容为整个消息内容(消息头+消息体)的长度
	                     // 如果不满8个字节，则左边补字符'0'，使其满足8个字节长度。
	CString m_strMsgType; // [2] 消息类型
public:
	// 将指定字符串解析为各项独立属性
	// strMsg = 完整的消息字符串
	// 返回：如果消息字符串符合消息格式要求则返回TRUE，否则返回FALSE。
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != 10)
			return FALSE; // 长度错误

		CString strMsgLen = strMsg.Left(8);
		CString strMsgType = strMsg.Right(2);
		if (::atoi(strMsgLen) < 1 || ::atoi(strMsgType) < 1)
			return FALSE; // 字段不是数字

		m_strMsgLen = strMsgLen;
		m_strMsgType = strMsgType;

		return TRUE;
	}
	// 取消息各项属性合并而成的字符串
	virtual CString GetString(void)
	{
		CString strMsg = m_strMsgLen + m_strMsgType;
		return strMsg;
	}
protected:
	// 当前消息体字符数
	enum { MSG_CHARS = 10 };
	// 设置消息长度
	// nMsgLen = 消息体的字符长度（不包括消息头）
	void _SetMsgLen(int nMsgLen)
	{
		m_strMsgLen.Format("%08d", CMsgHead::MSG_CHARS + nMsgLen);
	}
};

// 消息对象类
// 该类的作用是统一实现ISMMsg的GetString方法，所有具体的消息类都继承于此类，从而
// 统一继承GetString方法的实现，如此一来，各具体消息类在消息字符串合成方面仅需要
// 实现合并其独有的消息属性项方法_GetMsgDataString即可。
class CMsgObject : public CMsgHead
{
public:
	// 取消息各项属性合并而成的字符串
	virtual CString GetString(void)
	{
		CString strMsgDataString = _GetMsgDataString();
		_SetMsgLen(_strlen(strMsgDataString));
		CString strMsg = CMsgHead::GetString() + strMsgDataString;
		return strMsg;
	}
protected:
	// 将消息各项属性合成消息数据字符串
	virtual CString _GetMsgDataString(void) = 0;
};

// 登录请求消息
// 消息类型："01"
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
	CString m_strUserName; // [8] 请求登陆的用户名
	BOOL setUserPassword(CString & strUserPassword)
	{
		if (_strlen(strUserPassword) != 8)
			return FALSE;
		m_strUserPassword = strUserPassword;
		return TRUE;
	}
	CString m_strUserPassword; // [8] 请求登陆的用户名
public:
	// 将指定字符串解析为各项独立属性
	// strMsg = 完整的消息字符串
	// 返回：如果消息字符串符合消息格式要求则返回TRUE，否则返回FALSE。
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != CMsgHead::MSG_CHARS + CMsgLogon::MSG_CHARS)
			return FALSE; // 长度错误

		// 取消息头并进行分析
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // 消息头格式错误

		if (strcmp(MSG_TYPE, m_strMsgType) != 0)
			return FALSE; // 消息类型错误

		m_strUserName = strMsg.Mid(CMsgHead::MSG_CHARS, 8);
		m_strUserPassword = strMsg.Right(8);

		return TRUE;
	}
protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strUserName + m_strUserPassword;
	}
	// 当前消息体字符数
	enum { MSG_CHARS = 16 };
	// 当前消息体的消息类型
	LPCTSTR MSG_TYPE;
};

// 登录请求反馈消息
// 消息类型："11"
class CMsgLogonRes : public CMsgObject
{
public:
	CMsgLogonRes() : MSG_TYPE("11")
	{
		m_strMsgType = MSG_TYPE;
	}
public:
	CString m_strResult; // [1] 用户登陆状态。0登陆失败，1登陆成功
public:
	// 将指定字符串解析为各项独立属性
	// strMsg = 完整的消息字符串
	// 返回：如果消息字符串符合消息格式要求则返回TRUE，否则返回FALSE。
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != CMsgHead::MSG_CHARS + CMsgLogonRes::MSG_CHARS)
			return FALSE; // 长度错误

		// 取消息头并进行分析
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // 消息头格式错误

		if (strcmp(MSG_TYPE, m_strMsgType) != 0)
			return FALSE; // 消息类型错误

		m_strResult = strMsg.Right(1);

		return TRUE;
	}
protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strResult;
	}
	// 当前消息体字符数
	enum { MSG_CHARS = 1 };
	// 当前消息体的消息类型
	LPCTSTR MSG_TYPE;
};

// 短信数据消息
// 消息类型："42"
class CMsgSMData : public CMsgObject
{
public:
	CMsgSMData() : MSG_TYPE("42")
	{
		m_strMsgType = MSG_TYPE;
		m_strSendType = "2"; // [1] 发送方式，0单发（反馈短信网关提交结果），2单发（反馈短信平台处理结果）
		m_strFeeUser = "0"; // [1] 计费用户类型，0-对目的手机计费3-对其它指定手机计费
		m_strServiceID = "ABCDEF"; // [6] 服务代码，即记费标记，需双方商定
		m_strDisplaySPhone = "11608851#############"; // [21] 用户手机显示的源号码。可以显示CP的长号码(格式：填写1160****，以#补齐剩余字节)
		m_strFeePhone = "00000000000"; // [11] 当SM_FEEUSER值为3时，填写被计费手机的号码；为其他值时，填写长度为11的字串'00000000000'

		// 短信消息的ID，username+mmddhhmmss+4位的序列号
		m_strUserName; // [8] 用户名
		CTime Time = CTime::GetCurrentTime();
		m_strTime = Time.Format("%m%d%H%M%S"); // [10] 当前时间，格式为MMddHHmmss
		m_strSequence = "0001"; // [4] 序列号
		// ---------------------------------------------

		m_strMsgCause = "0"; // [1] 短信产生的原因，0-MO产生,1-第二条MO产生，2-MT产生，3-产生SMC包月话单
		m_strDataFormat = "0"; // [1] 短信数据的待发格式，0-text 1-bin 2-免提 3-bin(Alct,simentz,eric,0x75) 9-GB232
		m_strDataTP = "00"; // [2] TP_pId和TP_udhi(各占一个字节,缺省'00')
		m_strDataLength = "0000"; // [4] 短信数据的长度，左补0。
		m_strDataContent = ""; // [<140] 短信数据的内容（不能超过140个字符）
		m_strLinkID = "#####################"; // [21] LINKID长度不足时使用"#"进行补齐，无LINKID时，全部为"#"
		m_strPhonesLength = "0011"; // [4] 目标手机号码的总长度，左补0。
		m_strPhones = "13910000001"; // [>11 & <1100] 发送对象的手机号码。如果群发，以逗号隔开（不能超过100个手机号码，目前群发无效）
	}
public:
	CString m_strSendType; // [1] 发送方式，0单发（反馈短信网关提交结果），2单发（反馈短信平台处理结果）
	CString m_strFeeUser; // [1] 计费用户类型，0-对目的手机计费3-对其它指定手机计费
	CString m_strServiceID; // [6] 服务代码，即记费标记，需双方商定
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
	CString m_strDisplaySPhone; // [21] 用户手机显示的源号码。可以显示CP的长号码(格式：填写1160****，以#补齐剩余字节)
	CString m_strFeePhone; // [11] 当SM_FEEUSER值为3时，填写被计费手机的号码；为其他值时，填写长度为11的字串'00000000000'

	// 短信消息的ID，username+mmddhhmmss+4位的序列号
	CString m_strUserName; // [8] 用户名
	CString m_strTime; // [10] 当前时间，格式为MMddHHmmss
	CString m_strSequence; // [4] 序列号
	// ---------------------------------------------

	CString m_strMsgCause; // [1] 短信产生的原因，0-MO产生,1-第二条MO产生，2-MT产生，3-产生SMC包月话单
	CString m_strDataFormat; // [1] 短信数据的待发格式，0-text 1-bin 2-免提 3-bin(Alct,simentz,eric,0x75) 9-GB232
	CString m_strDataTP; // [2] TP_pId和TP_udhi(各占一个字节,缺省'00')
	CString m_strDataLength; // [4] 短信数据的长度，左补0。
	// 设置短信正文
	// strDataContent = 短信正文文本
	// 返回值，如果成功则返回一个""字符串，在strDataContent超过140字符时，返回多余的字符串。
	CString SetDataContent(CString & strDataContent)
	{
		int nMaxContent = 139;
		if (int(_strlen(strDataContent)) > nMaxContent)
		{// 正文超长需要截断

			int nCharType = GetCharType(strDataContent, nMaxContent - 1);
			switch(nCharType)
			{// 判断截断后字符串最后一个字符的类型
			case 0: // 英文字符
				if (strDataContent[nMaxContent - 1] != char(' ') &&
					strDataContent[nMaxContent] != char(' ') &&
					GetCharType(strDataContent, nMaxContent) == 0)
				{// 断口前字符不为' '&&断口后字符不为' '&&或者断口后字符不是中文

					// 从断口处反向搜索可以做为断行点的位置
					CString strTemp = strDataContent.Left(nMaxContent);
					int nSPos = ReverseFindBreakpoint(strTemp);
					if (nSPos > 0)
						nMaxContent = nSPos + 1; // 重新设定截断位置
				}
				break;
			case 1: // 中文的第一个字节
				// 如果截断位置正好是某个中文字符的第一个字节则截断位置后移一个字节以避免截断中文字符
				++nMaxContent; 
				break;
			case 2: // 中文的第二个字节
				break;
			}
		}
		m_strDataContent = strDataContent.Left(nMaxContent);
		CString strRet = strDataContent.Mid(nMaxContent);
		m_strDataLength.Format("%04d", _strlen(m_strDataContent));
		return strRet;
	}
	CString m_strDataContent; // [<140] 短信数据的内容（不能超过140个字符）
	CString m_strLinkID; // [21] LINKID长度不足时使用"#"进行补齐，无LINKID时，全部为"#"
	CString m_strPhonesLength; // [4] 目标手机号码的总长度，左补0。
	// 设置目标手机号码
	// strPhones = 手机号码
	// 返回值：如果成功则返回一个""字符串，在strPhones超过1100字符时，返回多余的字符串。
	// 错误：当strPhones字符串长度不足11时将返回全部strPhones原文。
	CString SetPhones(CString & strPhones)
	{
		if (_strlen(strPhones) < 11)
			return strPhones;

		m_strPhones = strPhones.Left(1100);
		CString strRet = strPhones.Mid(1100);
		m_strPhonesLength.Format("%04d", _strlen(m_strPhones));
		return strRet;
	}
	CString m_strPhones; // [>11 & <1100] 发送对象的手机号码。如果群发，以逗号隔开（不能超过100个手机号码，目前群发无效）

public:
	// 将指定字符串解析为各项独立属性
	// strMsg = 完整的消息字符串
	// 返回：如果消息字符串符合消息格式要求则返回TRUE，否则返回FALSE。
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) < CMsgHead::MSG_CHARS + CMsgSMData::MSG_CHARS)
			return FALSE; // 长度错误

		// 取消息头并进行分析
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // 消息头格式错误

		if (strcmp(MSG_TYPE, m_strMsgType) != 0)
			return FALSE; // 消息类型错误

		m_strSendType = strMsg.Mid(CMsgHead::MSG_CHARS + 0, 1); // [1] 发送方式，0单发（反馈短信网关提交结果），2单发（反馈短信平台处理结果）
		m_strFeeUser = strMsg.Mid(CMsgHead::MSG_CHARS + 1, 1); // [1] 计费用户类型，0-对目的手机计费3-对其它指定手机计费
		m_strServiceID = strMsg.Mid(CMsgHead::MSG_CHARS + 2, 6); // [6] 服务代码，即记费标记，需双方商定
		m_strDisplaySPhone = strMsg.Mid(CMsgHead::MSG_CHARS + 8, 21); // [21] 用户手机显示的源号码。可以显示CP的长号码(格式：填写1160****，以#补齐剩余字节)
		m_strFeePhone = strMsg.Mid(CMsgHead::MSG_CHARS + 29, 11); // [11] 当SM_FEEUSER值为3时，填写被计费手机的号码；为其他值时，填写长度为11的字串'00000000000'

		// 短信消息的ID，username+mmddhhmmss+4位的序列号
		m_strUserName = strMsg.Mid(CMsgHead::MSG_CHARS + 40, 8); // [8] 用户名
		m_strTime = strMsg.Mid(CMsgHead::MSG_CHARS + 48, 10); // [10] 当前时间，格式为MMddHHmmss
		m_strSequence = strMsg.Mid(CMsgHead::MSG_CHARS + 58, 4); // [4] 序列号
		// ---------------------------------------------

		m_strMsgCause = strMsg.Mid(CMsgHead::MSG_CHARS + 62, 1); // [1] 短信产生的原因，0-MO产生,1-第二条MO产生，2-MT产生，3-产生SMC包月话单
		m_strDataFormat = strMsg.Mid(CMsgHead::MSG_CHARS + 63, 1); // [1] 短信数据的待发格式，0-text 1-bin 2-免提 3-bin(Alct,simentz,eric,0x75) 9-GB232
		m_strDataTP = strMsg.Mid(CMsgHead::MSG_CHARS + 64, 2); // [2] TP_pId和TP_udhi(各占一个字节,缺省'00')
		m_strDataLength = strMsg.Mid(CMsgHead::MSG_CHARS + 66, 4); // [4] 短信数据的长度，左补0。
		int nDataLength = ::atoi(m_strDataLength);
		m_strDataContent = strMsg.Mid(CMsgHead::MSG_CHARS + 70, nDataLength); // [<140] 短信数据的内容（不能超过140个字符）
		m_strLinkID = strMsg.Mid(CMsgHead::MSG_CHARS + 70 + nDataLength, 21); // [21] LINKID长度不足时使用"#"进行补齐，无LINKID时，全部为"#"
		m_strPhonesLength = strMsg.Mid(CMsgHead::MSG_CHARS + 91 + nDataLength, 4); // [4] 目标手机号码的总长度，左补0。
		int nPhoneLength = ::atoi(m_strPhonesLength);
		m_strPhones = strMsg.Mid(CMsgHead::MSG_CHARS + 95 + nDataLength, nPhoneLength); // [>11 & <1100] 发送对象的手机号码。如果群发，以逗号隔开（不能超过100个手机号码，目前群发无效）

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
	// 当前消息体字符数(这里表示最小值，因为这个消息的长度是不定的)
	enum { MSG_CHARS = 106 };
	// 当前消息体的消息类型
	LPCTSTR MSG_TYPE;
};

// 业务数据反馈消息
// 消息类型："32" or "12"
class CMsgSMDataRes : public CMsgObject
{
public:
	CMsgSMDataRes() : MSG_TYPE("12"), MSG_TYPE2("32")
	{
		m_strMsgType = MSG_TYPE;
	}
public:
	CString m_strResult; // [1] 短信数据的状态，0提交数据失败，1发送数据成功，2发送数据失败，3错误的数据格式，4黑户或无效用户，5内容含有非法字符
public:
	// 将指定字符串解析为各项独立属性
	// strMsg = 完整的消息字符串
	// 返回：如果消息字符串符合消息格式要求则返回TRUE，否则返回FALSE。
	virtual BOOL SetString(CString & strMsg)
	{
		if (_strlen(strMsg) != CMsgHead::MSG_CHARS + CMsgSMDataRes::MSG_CHARS)
			return FALSE; // 长度错误

		// 取消息头并进行分析
		CString strHead = strMsg.Left(CMsgHead::MSG_CHARS);
		if (!CMsgHead::SetString(strHead))
			return FALSE; // 消息头格式错误

		if (strcmp(MSG_TYPE, m_strMsgType) != 0 &&
			strcmp(MSG_TYPE2, m_strMsgType) != 0)
			return FALSE; // 消息类型错误

		m_strResult = strMsg.Right(1);

		return TRUE;
	}
protected:
	virtual CString _GetMsgDataString(void)
	{
		return m_strResult;
	}
	// 当前消息体字符数
	enum { MSG_CHARS = 1 };
	// 当前消息体的消息类型
	LPCTSTR MSG_TYPE;
	// 当前消息体的第二个合法消息类型
	LPCTSTR MSG_TYPE2;
};

#endif // !defined(AFX_DEFS_H__773D829D_3BB1_4942_93FF_4FD533717C7B__INCLUDED_)
