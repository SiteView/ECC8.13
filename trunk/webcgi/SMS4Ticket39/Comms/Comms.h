// Comms.h: interface for the CComms class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMS_H__32507419_D5E3_4F0F_A392_9D30A7758AE7__INCLUDED_)
#define AFX_COMMS_H__32507419_D5E3_4F0F_A392_9D30A7758AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 分析字符串中指定位置的字符特性
// pszText = 指定字符所在的字符串
// uPos = 指定待分析字符在pszText中所在的位置
// 返回值：<0 - 参数错误，0 - 英文字符，1 - 中文第一字符，2 - 中文第二字符
inline int GetCharType(LPCSTR pszText, UINT uPos)
{
	int nLen = strlen(pszText);
	for (int i = 0; i < nLen; i++)
	{
		if (BYTE(pszText[i]) > 0x80 && BYTE(pszText[i]) < 0xFE)
		{// 是一个中文字符
			if (UINT(i) == uPos)
				return 1; // 目标位置的字符是某个中文字符的第一个字节
			else if (UINT(i) + 1 == uPos)
				return 2; // 目标位置的字符是某个中文字符的第二个字节
			++i;
		}
		else if (UINT(i) == uPos)
			return 0; // 目标位置的字符是英文字符
	}
	return -1; // 错误
}

// 在一个字符串中反向搜索可以断行的位置
// pszString = 指定待搜索的字符串
// 返回值：如果找到可断点则返回其位置，否则返回-1。
inline int ReverseFindBreakpoint(LPCSTR pszString)
{
	LPCSTR p = pszString + strlen(pszString);
	while(p > pszString)
	{
		if (*p == char(' '))
			return p - pszString; // ' '可以做为断点
		if (GetCharType(pszString, p - pszString) == 2)
			return p - pszString; // 中文的第二字节也可以做为断点
		--p;
	}
	return -1;
}

// 参数解析
// pszArgs = 指定一个原始的参数字符串，字符串中用';'分割多个参数对，每个参数的形式都是ArgName=ArgValue
// smapArgs = 返回一个由pszArgs解析而来的参数字符串表。
// 返回值：如果成功返回TRUE，否则返回FALSE。
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
		{// ';'切分多个参数对

			*p = char('\0');
			CString strArg = pszArg;
			// '='左边是参数名，右边是参数值。
			int nPos = strArg.Find('=');
			CString strArgName = strArg.Left(nPos);
			if (bArgNameMakeLower)
				strArgName.MakeLower();
			strArgName.TrimLeft(' ');
			strArgName.TrimRight(' ');
			CString strArgVal = strArg.Mid(nPos + 1);
			strArgVal.TrimLeft(' ');
			strArgVal.TrimRight(' ');

			// 将参数名和参数值放入一个字符串表格
			smapArgs.SetAt(strArgName, strArgVal);
			pszArg = p + 1;
		}
		++p;
	}
	delete[] pszBuff;
	return TRUE;
}

// 将一个字符串转换为符合HTTP调用要求的URL字符串
// pszString = 指定待转换的字符串
// 返回值：如果成功返回转换后的字符串，否则返回""。
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
			{// 是一个中文字符
				::_stprintf(p, _T("%%%02X%%%02X"), BYTE(pszString[i]), BYTE(pszString[i + 1]));
				++i;
			}
			else
			{// 是一个英文字符
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
