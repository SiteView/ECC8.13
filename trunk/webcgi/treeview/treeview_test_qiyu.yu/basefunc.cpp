#include "basefunc.h"
#include "../../opens/boost/regex.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
// ˵��
// ����
// ����ֵ
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
// ����     strtriml
// ˵��     ȥ��ָ���ı�����ո�
// ����
// ����ֵ
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
// ����     strtrimr
// ˵��     ȥ��ָ���ı����ҿո�
// ����
// ����ֵ
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
// ����     getCondition
// ˵��
// ����
// ����ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned getCondition(list<string>& lst, string s)
{
    static const boost::regex e("\\s+(and|or)\\s+");
    return static_cast<int>(boost::regex_split(std::back_inserter(lst), s, e));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����     getParam
// ˵��
// ����
// ����ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned getParam(list<string>&lst, string s)
{
    static const boost::regex e("([^\\[\\]]+)(?=\\])");
    return static_cast<int>(boost::regex_split(std::back_inserter(lst), s, e));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����     getOperatePostion
// ˵��     �õ�������λ��
// ����     
//          string s�������������ŵ��ַ���
//          list<string> lstOperate����������list
// ����ֵ   λ��
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
// ����     url_Encode
// ˵��     url����
// ����     �������ַ���
// ����ֵ   ������ַ���
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
            else if(*pPos >=0 && *pPos <= 255) // ����ASICC�ַ�
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
// ����     sv_split
// ˵��     ʹ��ָ���ָ������ַ�����ֵ�list��
// ����     
//          const char* str��������ַ���
//          const char* delim���ָ���
//          list<string>& results�����list
//          
// ����ֵ   
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
// ����     SV_IsNumeric
// ˵��     �ж���������Ƿ������֣�ʹ��boost��
// ����     string ��������
// ����ֵ   �Ƿ����ת��Ϊ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SV_IsNumeric(string &szValue)
{
    static const boost::regex e("\\d*");
    return regex_match(szValue, e);
}
