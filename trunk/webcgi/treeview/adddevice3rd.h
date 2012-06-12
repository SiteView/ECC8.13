#ifndef _SiteView_Ecc_Add_Device_3rd_H_
#define _SiteView_Ecc_Add_Device_3rd_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WSignalMapper"

#include "ecctable.h"

class CEccListTable;
class CEccAdvanceTable;

class WCheckBox;
class WPushButton;

#include "../svtable/SVTable.h"

#include "../../kennel/svdb/svapi/svapi.h"

class CEccAddDevice3rd : public CEccBaseTable
{
    //MOC: W_OBJECT CEccAddDevice3rd:CEccBaseTable
    W_OBJECT;
public:
    CEccAddDevice3rd(WContainerWidget *parent = NULL);
    ~CEccAddDevice3rd();

    void    QuickAdd(string szDeviceId, string szDevName, string szRunParam, string szQuickAdd, 
                    string szQuickAddSel, string szNetworkset);
private: //slots
    //MOC: SLOT CEccAddDevice3rd::saveAllSelMonitors()
    void        saveAllSelMonitors();
    //MOC: SLOT CEccAddDevice3rd::Cancel()
    void        Cancel();
    //MOC: SLOT CEccAddDevice3rd::EnumDynData()
    void        EnumDynData();
    //MOC: SLOT CEccAddDevice3rd::selAllByMonitorType(int)
    void        selAllByMonitorType(int nMTID);
private:
    virtual void        initForm(bool bHasHelp);

    void                createHideButton();
    void                createOperate();

    bool                saveMonitorBaseParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam);
    bool                saveMonitorAdvParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam);
    bool                saveMonitorCondition(OBJECT &objMonitor, OBJECT objMonitorTemp);
    bool                saveAlertNodeValue(MAPNODE &alertnode, MAPNODE &alertnodeTmp);

    void                removeMapping();

    void                AddDynData(WTable * pTable, const char* pszQuery, const int &nQuerySize, const int &nMonitorID, 
                            const string &szDllName, const string &szFuncName, const string &szSaveName, const bool &bSel);

    bool                saveMonitor(int nMonitorID, const char* pszSaveName, const char *pszExtraParam, 
                                   const char *pszExtraLable);

    CEccImportButton    *m_pSave;
    WPushButton         *m_pHideButton;
    WSignalMapper       m_mapMinitor;

    struct monitor_templet
    {
        monitor_templet()
        {
            nMonitorID = 0;
            szName = "";
            szLabel = "";
            szDllName = "";
            szFuncName = "";
            szSaveName = "";
			bSel = false;
            pTable = NULL;
        };
        int    nMonitorID;
        string szSaveName;
        string szName;
        string szLabel;
        string szDllName;
        string szFuncName;
		bool   bSel;
        WTable *pTable;
    };

    list<WCheckBox*>            m_lsCkMT;

    list<monitor_templet>       m_lsMonitorTemplet;
    SVIntTable                  m_svValueList;

    string                      m_szDeviceID;
    string                      m_szNetworkSet;
    string                      m_szRunParam;
    string                      m_szDevName;

};

#endif
