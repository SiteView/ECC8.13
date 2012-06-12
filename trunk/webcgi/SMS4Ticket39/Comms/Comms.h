// Comms.h: interface for the CComms class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMS_H__32507419_D5E3_4F0F_A392_9D30A7758AE7__INCLUDED_)
#define AFX_COMMS_H__32507419_D5E3_4F0F_A392_9D30A7758AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �����ַ�����ָ��λ�õ��ַ�����
// pszText = ָ���ַ����ڵ��ַ���
// uPos = ָ���������ַ���pszText�����ڵ�λ��
// ����ֵ��<0 - ��������0 - Ӣ���ַ���1 - ���ĵ�һ�ַ���2 - ���ĵڶ��ַ�
inline int GetCharType(LPCSTR pszText, UINT uPos)
{
	int nLen = strlen(pszText);
	for (int i = 0; i < nLen; i++)
	{
		if (BYTE(pszText[i]) > 0x80 && BYTE(pszText[i]) < 0xFE)
		{// ��һ�������ַ�
			if (UINT(i) == uPos)
				return 1; // Ŀ��λ�õ��ַ���ĳ�������ַ��ĵ�һ���ֽ�
			else if (UINT(i) + 1 == uPos)
				return 2; // Ŀ��λ�õ��ַ���ĳ�������ַ��ĵڶ����ֽ�
			++i;
		}
		else if (UINT(i) == uPos)
			return 0; // Ŀ��λ�õ��ַ���Ӣ���ַ�
	}
	return -1; // ����
}

// ��һ���ַ����з����������Զ��е�λ��
// pszString = ָ�����������ַ���
// ����ֵ������ҵ��ɶϵ��򷵻���λ�ã����򷵻�-1��
inline int ReverseFindBreakpoint(LPCSTR pszString)
{
	LPCSTR p = pszString + strlen(pszString);
	while(p > pszString)
	{
		if (*p == char(' '))
			return p - pszString; // ' '������Ϊ�ϵ�
		if (GetCharType(pszString, p - pszString) == 2)
			return p - pszString; // ���ĵĵڶ��ֽ�Ҳ������Ϊ�ϵ�
		--p;
	}
	return -1;
}

// ��������
// pszArgs = ָ��һ��ԭʼ�Ĳ����ַ������ַ�������';'�ָ��������ԣ�ÿ����������ʽ����ArgName=ArgValue
// smapArgs = ����һ����pszArgs���������Ĳ����ַ�����
// ����ֵ������ɹ�����TRUE�����򷵻�FALSE��
inline BOOL AnalysisArgs(LPCSTR pszArgs, CMapStringToString & smapArgs, bool bArgNameMakeLower = true)
{
	LPSTR pszBuff = new char[strlen(pszArgs) + 2];
	if (NULL == pszBuff)
		return FALSE;
	strcpy(pszBuff, pszArgs);
	pszBuff[strlen(pszArgs)] = char(';');
	LPSTR p = pszBuff;
	LPSTR pszArg = p;
	while(*p)
	{
		if (*p == char(';'))
		{// ';'�зֶ��������

			*p = char('\0');
			CString strArg = pszArg;
			// '='����ǲ��������ұ��ǲ���ֵ��
			int nPos = strArg.Find('=');
			CString strArgName = strArg.Left(nPos);
			if (bArgNameMakeLower)
				strArgName.MakeLower();
			strArgName.TrimLeft(' ');
			strArgName.TrimRight(' ');
			CString strArgVal = strArg.Mid(nPos + 1);
			strArgVal.TrimLeft(' ');
			strArgVal.TrimRight(' ');

			// ���������Ͳ���ֵ����һ���ַ������
			smapArgs.SetAt(strArgName, strArgVal);
			pszArg = p + 1;
		}
		++p;
	}
	delete[] pszBuff;
	return TRUE;
}

// ��һ���ַ���ת��Ϊ����HTTP����Ҫ���URL�ַ���
// pszString = ָ����ת�����ַ���
// ����ֵ������ɹ�����ת������ַ��������򷵻�""��
inline CString ToURLString(LPCTSTR pszString)
{
	CString strURLString;
	int nLen = strlen(pszString);
	LPTSTR pszURLString = new TCHAR[nLen * 3 + 1];
	if (NULL != pszURLString)
	{
		::memset(pszURLString, 0, sizeof(TCHAR) * (nLen * 3 + 1));
		LPTSTR p = pszURLString;
		for (int i = 0; i < nLen; i++)
		{
			if (BYTE(pszString[i]) > 0x80 && BYTE(pszString[i]) < 0xFE)
			{// ��һ�������ַ�
				::_stprintf(p, _T("%%%02X%%%02X"), BYTE(pszString[i]), BYTE(pszString[i + 1]));
				++i;
			}
			else
			{// ��һ��Ӣ���ַ�
				::_stprintf(p, _T("%c"), pszString[i]);
			}
			p += ::lstrlen(p);
		}
		strURLString = pszURLString;
		delete[] pszURLString;
	}
	return strURLString;
}

#endif // !defined(AFX_COMMS_H__32507419_D5E3_4F0F_A392_9D30A7758AE7__INCLUDED_)
