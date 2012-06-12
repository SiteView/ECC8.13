#ifndef _SiteView_ECC_Base_Function_H_
#define _SiteView_ECC_Base_Function_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <list>
#include <string>

using namespace std;

// 生成HTML格式文本
void buildHtmlText(string &szText);

// 去掉字符串左空格
string strtriml(const char * str1);

// 去掉字符串右空格
string strtrimr(const char * str1);

// 得到连接符号
unsigned getCondition(list<string>& lst, string s);

// 得到参数
unsigned getParam(list<string>&lst, string s);

// 得到操作符号位置
unsigned getOperatePostion(string s, list<string> lstOperate, string &szCondition);

// 编码
string url_Encode(const char* pszValue);

// 拆分
int  sv_split(const char* str, const char* delim, list<string>& results, bool empties = true);

// 检测数据是否是数字类型
bool SV_IsNumeric(string &szValue);

#endif
