
#ifndef _SV_WHOLE_VIEW_H_
#define _SV_WHOLE_VIEW_H_

#pragma once


#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WSignalMapper"

class WSVMainTable;
class WSVFlexTable;

#include <string>
#include <map>
#include <list>

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

#include "../userright/user.h"

class CSVWholeview : public WTable
{
    //MOC: W_OBJECT CSVWholeview:WTable
    W_OBJECT;
public:
    // 构造函数
    CSVWholeview(WContainerWidget *parent = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    // 刷新
    virtual void refresh();

	void NewInitForm();
	void AddJsParam(const std::string name, const std::string value);

    string m_szGlobalEvent;

private ://WT
    WTable        * m_pContent;
    WText         * m_pTime;

	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pFlexTable;
private:
    // load string resource
    void            loadStrings();
    // init form (create activex control)
    void            initForm();
    // title
    void            createTitle();
    // 枚举 SE
    void            enumSVSE();
    // 枚举 子组
    bool            enumGroups(const string &szGroupID, WTable *pTable);
    // 枚举 监测器
    bool            enumMonitors(const string &szDeviceID, const string &szDeviceName, WTableCell *pTableCell);
    // 监测器 状态
    int             getMonitorState(const string &szMonitorID, string &szShowText);

    // clear tree
    void            clearTree();
    // init tree
    void            initTree();

    // refresh time 
    string          m_szRefreshTime;
    // title
    string          m_szTitle;
    // have no child
    string          m_szNoChild;
    // User's ID
    string          m_szUserID;
    string          m_szIDCUser;
    string          m_szIDCPwd;
 
    struct base_param
    {
        base_param()
        {
            szName  = "";
            szIndex = "";
        };
        string szName;
        string szIndex;
    };
    CUser           * m_pSVUser;
    bool              m_bFirstLoad;

    int         m_nShowType;
	string strRefresh;
};

#endif
