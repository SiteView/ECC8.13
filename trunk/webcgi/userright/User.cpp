#include ".\user.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../base/basetype.h"

#ifdef WIN32
#include <windows.h>
#endif

extern void PrintDebugString(const char * szMsg);

CUser::CUser(void)
{
    m_bAdmin =false;
    strUserId ="";
}

CUser::CUser(std::string strUid )
{
    strUserId =strUid;
    int nAdmin = GetIniFileInt(strUserId , "nAdmin", -1, "user.ini");
    if(nAdmin==-1) 
        m_bAdmin =false;
    else 
        m_bAdmin =true;

    if(!m_bAdmin)
    {
        ClearScopeFuncList();
        strScope = GetIniFileString(strUserId, "groupright", "", "user.ini");	
        strUnScope = GetIniFileString(strUserId, "ungroupright", "", "user.ini");
        MakeGroupFunc();
    }
}

void CUser::setUserID(std::string strUID)
{
    strUserId =strUID;
    int nAdmin = GetIniFileInt(strUserId , "nAdmin", -1, "user.ini");
    if(nAdmin==-1) 
        m_bAdmin =false;
    else 
        m_bAdmin =true;

    if(!m_bAdmin)
    {
        ClearScopeFuncList();
        strScope = GetIniFileString(strUserId, "groupright", "", "user.ini");	
        strUnScope = GetIniFileString(strUserId, "ungroupright", "", "user.ini");
        MakeGroupFunc();
    }
}

void CUser::ClearScopeFuncList()
{
    for (ScopeFuncMap::iterator it = m_ScopeFuncmap.begin(); it != m_ScopeFuncmap.end(); it++) 
        delete it->second;

    m_ScopeFuncmap.erase(m_ScopeFuncmap.begin(), m_ScopeFuncmap.end());
}

void CUser::MakeGroupFunc()
{
    vector<string > pGroupRightVec;
    ParserToken(pGroupRightVec, strScope.c_str(), ",");
    for(int iScope = 0; iScope < static_cast<int>(pGroupRightVec.size()); iScope++)
    {
        string oneScopeRight = GetIniFileString(strUserId, pGroupRightVec[iScope].c_str(), "", "user.ini");
        if(oneScopeRight.size()>0)
        {
            vector<string> pRightVec;
            ParserToken(pRightVec, oneScopeRight.c_str(), ",");
            PScopeFunc aScopeFunc = new ScopeFunc;
            aScopeFunc->strScopeId= pGroupRightVec[iScope].c_str();
            for (int i = 0 ;i < static_cast<int>(pRightVec.size()); i++ )
            {
                int j = static_cast<int>(pRightVec[i].find('=', 0));
                if(j > 0)
                {
                    char strRightId[100] = {0}, strRightTrue[100] = {0};
                    pRightVec[i].copy(strRightId, j, 0);
                    pRightVec[i].copy(strRightTrue, pRightVec[i].size() - j - 1, j + 1);
                    if(strcmp(strRightTrue, "1") == 0)
                        aScopeFunc->m_ScopeRightMap[strRightId] = true;
                    else
                        aScopeFunc->m_ScopeRightMap[strRightId] = false;
                }
            }
            ScopeFuncMap::iterator it = m_ScopeFuncmap.find(pGroupRightVec[iScope]);
            if(it != m_ScopeFuncmap.end())
                delete it->second; 
            m_ScopeFuncmap[pGroupRightVec[iScope]]=aScopeFunc;   
        }
    }
}

CUser::~CUser(void)
{
    ClearScopeFuncList();
}

bool CUser::ParserToken(vector<string >&pTokenList,   const char * pQueryString,char *pSVSeps)
{
    char * token = NULL;
    char * tokendot = NULL;
    if(!pSVSeps)
        return false;
    char * cp = strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        token = strtok( pTmp , pSVSeps);
        while( token != NULL )
        {
            pTokenList.push_back(token);
            token = strtok( NULL , pSVSeps);
        }
        free(cp); 
    }
    return true;
}

bool CUser::haveUserRight(std::string strScopeId ,std::string strRightId)
{
    if(m_bAdmin)
        return true;

    if(m_ScopeFuncmap.find(strScopeId)!=m_ScopeFuncmap.end())
    {
        ScopeFunc *aScopeFunc;
        aScopeFunc = m_ScopeFuncmap.find(strScopeId)->second;
        if(aScopeFunc!=NULL)
        {  
            if(aScopeFunc->m_ScopeRightMap.find(strRightId)!=aScopeFunc->m_ScopeRightMap.end())
            {
                bool bHaveRight= aScopeFunc->m_ScopeRightMap.find(strRightId)->second;
                int nRight = bHaveRight;
                return bHaveRight;
            }
        }
    }
    return false;
}
bool CUser::haveGroupRight(std::string strScopeId, int nScopeType )  // nScopeType  SE  Group Device 
{
    if(m_bAdmin)
        return true;

    string strFind("," + strScopeId + ",");
    int nIndex = static_cast<int>(strScope.find(strFind , 0));
    if(nIndex >= 0)
        return true;
    else
    {
        strFind = "," + strScopeId + ".";
        nIndex = static_cast<int>(strScope.find( strFind ,0));
        if(nIndex >= 0)
            return true;
        return false;
    }
    return false;
}
bool CUser::AddUserScopeAllRight(std::string strScopeId,int nScopeType )  // nScopeType  SE  Group Device 
{

    strScope=	GetIniFileString(strUserId, "groupright", "", "user.ini");	

    if(strScope.size()==0)
        strScope=",";

    strScope+=strScopeId;
    strScope+=",";
    WriteIniFileString(strUserId,"groupright",strScope,"user.ini");

    std::string strSection;
	std::string strRightLi;
    switch(nScopeType)
    {
    case Tree_DEVICE:
        strSection ="monitor";
		AddScopeRight(strSection, strScopeId,strRightLi);
		AddScopeRight("device",strScopeId,strRightLi);
		WriteIniFileString(strUserId,strScopeId,strRightLi,"user.ini");


        break;
    case Tree_GROUP:
        strSection ="group";
		AddScopeRight(strSection,strScopeId,strRightLi);
		AddScopeRight("device",strScopeId,strRightLi);
		WriteIniFileString(strUserId,strScopeId,strRightLi,"user.ini");

        break;
    case Tree_SE:
        strSection ="group";
		AddScopeRight(strSection,strScopeId,strRightLi);
		AddScopeRight("device",strScopeId,strRightLi);
		WriteIniFileString(strUserId,strScopeId,strRightLi,"user.ini");
        break;

    }

    
	return true;

}
bool CUser::AddScopeRight(std::string strSection,std::string strScopeId ,std::string & strRightLi)
{
	std::list<std::string> keylist;
    GetIniFileKeys(strSection,keylist,"userright.ini");
    //std::string strRightLi;
    //strRightLi ="";
    std::list<std::string>::iterator It;
    ScopeFunc * pScopeFunc = new  ScopeFunc;
    for(It= keylist.begin();It!=keylist.end();It++)
    {
        pScopeFunc->m_ScopeRightMap[(*It)] = true;
        strRightLi +=It->c_str();
        strRightLi+="=1,";
    }

    m_ScopeFuncmap[strScopeId] = pScopeFunc;
	return true;
    //return	WriteIniFileString(strUserId,strScopeId,strRightLi,"user.ini");
	
}