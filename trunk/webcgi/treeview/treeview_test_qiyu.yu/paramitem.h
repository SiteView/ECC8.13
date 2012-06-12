#ifndef _SiteView_ECC_PARAM_ITEM_H_
#define _SiteView_ECC_PARAM_ITEM_H_

#pragma once

#include "../../opens/libwt/WText"

#include <string>
#include <list>
#include <map>

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"

#include "../svtable/SVTable.h"
#include "basedefine.h"
#include "rightview.h"

class CEccParamItem
{
public:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CEccParamItem(MAPNODE nodeobj = INVALID_VALUE);
    ~CEccParamItem();

    void clearDynData();
    void showHelp(bool bShow);
    void showTip();
    void hideTip();
    bool checkValue();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool                isSynTitle()
    {
        return m_bSynTitle;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool                isPassword()
    {
        if(m_szType.compare(svPassword) == 0) 
            return true; 
        else 
            return false;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool                isRun()
    {
        if(m_szIsRun == "true")
            return true;
        else
            return false;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool                isDynamic()
    {
        if(!m_szDllName.empty() && !m_szFuncName.empty())
            return true;
        else
            return false;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool                isHasFollow()
    {
        if(!m_szFollow.empty())
            return true;
        else
            return false;
    };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void                getName(string &szName)
    {
        szName = m_szName;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const char*         getName()
    {
        return m_szName.c_str();
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const char*         getDefaultValue()
    {
        return m_szDefaultValue.c_str();
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const char*         getFollow()
    {
        return m_szFollow.c_str();
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string              getSaveName()
    {
        return m_szSaveName;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string              getAccount()
    {
        if(!m_szAccount.empty() && !m_szExpress.empty())
            return m_szAccount;
        else
            return "";
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WInteractWidget *   getControl()
    {
        return m_pActiveX;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string              getExpress()
    {
        return m_szExpress;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void                resetState()
    {
        m_bParentFind = false;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void                setFollowItem(CEccParamItem * param)
    {
        m_pFollowItem = param;
        param->m_bHasParent = true;
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void        MakeValueList(list<ecc_value_list> &lsValue);
    void        CreateControl(WTable * pTable, list<WText*> &lsHelp, bool bShowHelp);
    void        enumDynValue(const string &szQuery, const string &szIndex);
    void        enumOS();
    void        getStringValue(string &szValue);
    void        setDefaultValue();
    void        resetDynData();

    void        setStringValue(string &szValue);
private:
    bool        m_bHasParent;
    bool        m_bParentFind;
    int         m_nConditionType;

    string      m_szName;
    string      m_szSaveName;
    string      m_szLabel;
    string      m_szTip;
    string      m_szHelp;
    string      m_szType;
    string      m_szAllowNull;
    string      m_szFollow;
    string      m_szIsRun;
    string      m_szNoSort;
    string      m_szDllName;
    string      m_szFuncName;
    string      m_szValue;

    string      m_szAccount;
    string      m_szExpress;

    bool        m_bSynTitle;
    
    string      m_szIsNumber;
    string      m_szIsReadOnly;
    string      m_szDefaultValue;
    string      m_szStyle;
    string      m_szHidden;

    int         m_nMax;
    int         m_nMin;
    int         m_nWidth;

    void        enumProperty();

    bool        checkTextEdit();
    bool        checkTextArea();
    bool        checkComboBox();

    void        EidtQueryString(const string &szQuery, char* pszQueryString);
    void        ParserReturnInList(const char* szReturn, list<string>& lsReturn);
    void        TidyReturnList(list<string>& lsReturn);

    void        addNoSortList(string &szText, string &szLabel);
    void        setNoSortString(string &szValue);
    const char* getNoSortString();
private:
    WText            * m_pErr;
    WText            * m_pHelp;
    WText            * m_pLabel;
    WInteractWidget  * m_pActiveX;

    MAPNODE            m_mainNode;
    CEccParamItem      * m_pFollowItem;

    map<string, string, less<string> > m_ValueList;
    typedef map<string, string, less<string> >::iterator listitem;

    SVIntTable m_iValueList;
};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
