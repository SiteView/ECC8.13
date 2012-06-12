#ifndef _SV_PARAM_ITEM_H_
#define _SV_PARAM_ITEM_H_

#pragma once

#include "../../opens/libwt/WText"

#include <string>
#include <list>
#include <map>

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"

extern void PrintDebugString(const char* szMsg);

#include "../svtable/SVTable.h"
#include "basefunc.h"
class SVDevice;
class SVMonitor;

class SVParamItem
{
    friend class SVMonitor;
    friend class SVDevice;
public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum codition_type
    {
        error_condition = 1,
        warning_condtion = 2,
        normal_condition = 3
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SVParamItem(MAPNODE nodeobj = INVALID_VALUE);
    ~SVParamItem();

    void setConditionType(int nType) { m_nConditionType = nType; };
    int  getConditionType() {return m_nConditionType;};

    void clearDynData();
    void showHelp(bool bShow);
    void showTip();
    bool checkValue();

    bool isSynTitle() {return m_bSynTitle;};
    bool isPassword() {if(m_szType.compare(svPassword) == 0) return true; else return false; };
    bool isRun() { if(!m_szIsRun.empty() && m_szIsRun == "true") return true; else return false; };
    bool isDynamic(){ if(!m_szDllName.empty() && !m_szFuncName.empty()) return true; else return false; };
    bool isHasFollow(){ if (!m_szFollow.empty()) return true; else return false;};

    void getName(string &szName) { szName = m_szName;};
    const char*  getLabel() {return m_szLabel.c_str();};
    const char*  getName() {return m_szName.c_str();};
    const char*  getDefaultValue() {return m_szDefaultValue.c_str();};
    const char*  getFollow() {return m_szFollow.c_str();};
    const char*  getValueByLabel(string &szLable);
    string       getSaveName() { return m_szSaveName;};

    string       getAccount()
    {
        if(!m_szAccount.empty() && !m_szExpress.empty())
            return m_szAccount;
        else
            return "";
    };

    string       getExpress()
    {
        return m_szExpress;
    };

    WInteractWidget * getControl() {return m_pActiveX;};

    void CreateControl(WTable * pTable = NULL);
    void setFollowItem(SVParamItem * param) { m_pFollowItem = param; param->m_bHasParent = true;};
    void getStringValue(string &szValue);
    void setStringValue(string &szValue);
    void setDefaultValue();
    void resetState() {m_bParentFind = false;};
    void enumDynValue(const string &szQuery, const string &szIndex, const string &szIDCUser, const string &szIDCPwd);
    void enumOS();

    void AddDynList(WTable * pTable, SVIntTable &svTable);
private:
    bool   m_bShowHelp;
    bool   m_bError;
    bool   m_bHasParent;
    bool   m_bParentFind ;
    int    m_nConditionType ;

    string m_szName;
    string m_szSaveName;
    string m_szLabel;
    string m_szTip;
    string m_szHelp;
    string m_szType;
    string m_szAllowNull;
    string m_szFollow;
    string m_szIsRun;
    string m_szNoSort;
    string m_szDllName;
    string m_szFuncName;

    string m_szAccount;
    string m_szExpress;

    bool   m_bSynTitle;
    
    //string m_szValue;
    //string m_szMax;
    //string m_szMin;
    string m_szIsNumber;
    string m_szIsReadOnly;
    string m_szDefaultValue;
    string m_szStyle;
    string m_szHidden;

    int    m_nMax;
    int    m_nMin;
    int    m_nWidth;
    //bool m_bFollow;
    void enumProperty();

    bool checkTextEdit();
    bool checkTextArea();
    bool checkComboBox();

    void EidtQueryString(const string &szQuery, char* pszQueryString);
    void ParserReturnInList(const char* szReturn, list<string>& lsReturn);
    void TidyReturnList(list<string>& lsReturn);

    void        addNoSortList(string &szText, string &szLabel);
    void        setNoSortString(string &szValue);
    const char* getNoSortString();
private:


    WText            * m_pHelp;
    WText            * m_pLabel;
    WInteractWidget  * m_pActiveX;

    MAPNODE            m_mainNode;
    SVParamItem      * m_pFollowItem;

    map<string, string, less<string> > m_ValueList;
    typedef map<string, string, less<string> >::iterator listitem;

    SVIntTable m_iValueList;
};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
