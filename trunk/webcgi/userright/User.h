#pragma once

#include <string>
#include <map>
#include <list>
#include <vector>


using namespace std;
class CUserList;
typedef std::map<std::string ,  bool > ScopeRightMap;  //string  strScopeID    strRightID  bool

typedef struct ScopeFunc {
	std::string strScopeId;
	//std::string strRightID;
	//bool  bHave;
	ScopeRightMap m_ScopeRightMap;
}*PScopeFunc;


typedef  std::map< string , ScopeFunc *  >  ScopeFuncMap;

class CUser
{
public:
	//bool isAdmin;
    bool   isAdmin() { return m_bAdmin; };
	bool haveUserRight(std::string strScopeId ,std::string strRightId);
	bool haveGroupRight(std::string strScopeId,int nScopeType );  // nScopeType  SE  Group Device 
	bool AddUserScopeAllRight(std::string strScopeId,int nScopeType );  // nScopeType  SE  Group Device 
	bool AddScopeRight(std::string strSection,std::string strScopeId,std::string & strRightLi);
	
    void setUserID(std::string strUID);
    const string getUserID() { return strUserId;};
private:
	bool m_bAdmin;
	string strScope; 
	string strUnScope;
    	
	string strUserId;
	//std::list<ScopeFunc *  > m_ScopeFunclist;
	 ScopeFuncMap m_ScopeFuncmap;
	//UserRightMap userRightMap; 
     
    void MakeGroupFunc();
	bool ParserToken(vector<string >&pTokenList,   const char * pQueryString,char *pSVSeps);
	void ClearScopeFuncList();

public:
	CUser(void);
	CUser(std::string strUid );
	~CUser(void);
	friend class CUserList;
};

