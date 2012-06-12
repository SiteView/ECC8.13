#ifndef _SiteView_ECC_Base_Function_H_
#define _SiteView_ECC_Base_Function_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <list>
#include <string>

using namespace std;

// ����HTML��ʽ�ı�
void buildHtmlText(string &szText);

// ȥ���ַ�����ո�
string strtriml(const char * str1);

// ȥ���ַ����ҿո�
string strtrimr(const char * str1);

// �õ����ӷ���
unsigned getCondition(list<string>& lst, string s);

// �õ�����
unsigned getParam(list<string>&lst, string s);

// �õ���������λ��
unsigned getOperatePostion(string s, list<string> lstOperate, string &szCondition);

// ����
string url_Encode(const char* pszValue);

// ���
int  sv_split(const char* str, const char* delim, list<string>& results, bool empties = true);

// ��������Ƿ�����������
bool SV_IsNumeric(string &szValue);

#endif
