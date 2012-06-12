#include "basefunc.h"
#include "../../opens/boost/regex.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数
// 说明
// 参数
// 返回值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void buildHtmlText(string &szText)
{
    int nPos = static_cast<int>(szText.find(",", 0));
    while (nPos > 0)
    {
        szText = szText.substr(0, nPos + 1) + "<BR>" + szText.substr(nPos + 1, szText.length() - nPos + 1);
        nPos += 6;
        nPos = static_cast<int>(szText.find(",", nPos));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     strtriml
// 说明     去掉指定文本的左空格
// 参数
// 返回值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string strtriml(const char * str1)
{
    string szValue ("");
    if (str1 && strlen(str1) > 0)
    {    
        char * cp = strdup(str1);
        if (cp)
        {    
            char * pos = cp;
            while (*pos)
            {
                if ( *pos == ' ' || *pos == '\r' || *pos == '\n' || *pos == '\t' )
                {
                    *pos = '\0';
                    pos ++;
                }
                else
                {
                    break;
                }
            }
            szValue = pos;
        }
        free(cp);
    }
    return szValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     strtrimr
// 说明     去掉指定文本的右空格
// 参数
// 返回值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string strtrimr(const char * str1)
{
    string szValue ("");
    if(str1 && strlen(str1) > 0)
    {    
        char *chTemp = strdup(str1);
        if(chTemp)
        {
            char * cp = chTemp + (strlen(chTemp) - 1);
            while (*cp)
            {
                if ( *cp == ' ' || *cp == '\r' || *cp == '\n' || *cp == '\t')
                {
                    *cp = '\0';
                    cp --;
                }
                else
                {
                    break;
                }
            }
            szValue = chTemp;
            free(chTemp);
        }
    }
    return szValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     getCondition
// 说明
// 参数
// 返回值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned getCondition(list<string>& lst, string s)
{
    static const boost::regex e("\\s+(and|or)\\s+");
    return static_cast<int>(boost::regex_split(std::back_inserter(lst), s, e));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     getParam
// 说明
// 参数
// 返回值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned getParam(list<string>&lst, string s)
{
    static const boost::regex e("([^\\[\\]]+)(?=\\])");
    return static_cast<int>(boost::regex_split(std::back_inserter(lst), s, e));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     getOperatePostion
// 说明     得到操作符位置
// 参数     
//          string s，包含操作符号的字符串
//          list<string> lstOperate，操作符号list
// 返回值   位置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned getOperatePostion(string s, list<string> lstOperate, string &szCondition)
{
    int nPos = 0;
    list<string>::iterator lsItem;
    szCondition = "";
    for(lsItem = lstOperate.begin(); lsItem != lstOperate.end(); lsItem++)
    {
        nPos = static_cast<int>(s.find((*lsItem)));
        if(nPos > 0 )
        {
            if((*lsItem) == "==" || (*lsItem) == "!=")
            {
                szCondition = (*lsItem);
            }
            else if(nPos > 0 && (*lsItem) == "<")
            {
                if(s.c_str()[nPos + 1] == '=')
                    szCondition = "<=";
                else if(s.c_str()[nPos - 1] == ' ')
                    szCondition = "<";
            }
            else if(nPos > 0 && (*lsItem) == ">")
            {
                if(s.c_str()[nPos + 1] == '=')
                    szCondition = ">=";
                else if(s.c_str()[nPos - 1] == ' ')
                    szCondition = ">";
            }
            else if(nPos > 0 && (*lsItem) == "contains")
            {
                if(s.c_str()[nPos - 1] == '!')
                {
                    nPos -= 1;
                    szCondition = "!contains";
                }
                else
                    szCondition = "contains";
            }
            break;
        }
    }
    return nPos;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     url_Encode
// 说明     url编码
// 参数     待编码字符串
// 返回值   编码后字符串
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string url_Encode(const char* pszValue)
{
    string szEnUrl ("");
    int nSize = static_cast<int>(strlen(pszValue) * 3) + 1;
    char *chEncode = new char[nSize];

    const char *pPos = pszValue;
    if(chEncode)
    {
        memset(chEncode, 0, nSize);
        char *pTmp = chEncode;
        while(*pPos != '\0')
        {
            if(*pPos >= 48 && *pPos <= 57) // 0-9
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos >= 65 && *pPos <= 90) // A-Z
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos >= 97 && *pPos <= 122) // a-z
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos == '.') // .
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos >=0 && *pPos <= 255) // 其他ASICC字符
            {
                *pTmp = '%';
                pTmp++;
                sprintf(pTmp, "%x", *pPos);
                pTmp += 2;
            }
            pPos++;
        }

        szEnUrl = chEncode; 
        delete []chEncode;
    }
    return szEnUrl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     sv_split
// 说明     使用指定分隔符将字符串拆分到list中
// 参数     
//          const char* str，待拆分字符串
//          const char* delim，分隔符
//          list<string>& results，结果list
//          
// 返回值   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sv_split(const char* str, const char* delim, 
     list<string>& results, bool empties)
{
    char* pstr = const_cast<char*>(str);
    char* r = NULL;
    r = strstr(pstr, delim);
    int dlen = static_cast<int>(strlen(delim));

    while( r != NULL )
    {
        char* cp = new char[(r-pstr)+1];
        memcpy(cp, pstr, (r-pstr));
        cp[(r-pstr)] = '\0';
        if( strlen(cp) > 0 || empties )
        {
            string s(cp);
            results.push_back(s);
        }
        delete[] cp;
        pstr = r + dlen;
        r = strstr(pstr, delim);
    }

    if( strlen(pstr) > 0 || empties )
    {
        results.push_back(string(pstr));
    }
    return static_cast<int>(results.size());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数     SV_IsNumeric
// 说明     判断输入参数是否是数字（使用boost）
// 参数     string 类型数据
// 返回值   是否可以转换为数字
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SV_IsNumeric(string &szValue)
{
    static const boost::regex e("\\d*");
    return regex_match(szValue, e);
}
