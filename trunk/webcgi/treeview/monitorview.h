#ifndef _SiteView_ECC_Monitor_View_H_
#define _SiteView_ECC_Monitor_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;

#include <string>
#include <list>

using namespace std;


#include "gentitle.h"

class CEccTreeDevice;
class CEccListTable;

class CEccMonitorView : public WTable
{
    //MOC: W_OBJECT CEccMonitorView:WTable
    W_OBJECT;
public:
    CEccMonitorView(WContainerWidget *parent = NULL);
    static void AddNewMonitor(string szIndex);
public:
    void        UpdataGeneralData(const CEccTreeDevice * pNode);
    void        setDeviceNode(const CEccTreeDevice* pNode);
    void        refreshTime();
private:
    void            createContent();
    void            createGeneral();
    void            createMonitorList();
    void            createStateDesc();
    void            createTitle();
    void            initForm();

    void            clearMonitorList();
    void            changePath(const string &szIndex);
private:
    CEccGenTitle    *m_pTitle;
    CEccListTable   *m_pGeneral;
    CEccListTable   *m_pMonitorList;

    WTable          *m_pDepend;
    WTable          *m_pContent;
    WText           *m_pName;
    WText           *m_pDescription;
    WText           *m_pState;
    WText           *m_pDeviceType;
    WText           *m_pOSType;

    string          m_szDeviceID;
    string          m_szDTName;
    string          m_szNetworkset;
};

#endif