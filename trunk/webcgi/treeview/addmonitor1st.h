#ifndef _SiteView_Ecc_Add_Monitor_1st_H_
#define _SiteView_Ecc_Add_Monitor_1st_H_

#include "ecctable.h"

#include "../../opens/libwt/WSignalMapper"

class CEccAddMonitor1st : public CEccBaseTable
{
    //MOC: W_OBJECT CEccAddMonitor1st:CEccBaseTable
    W_OBJECT;
public:
    CEccAddMonitor1st(WContainerWidget *parent = NULL);
    ~CEccAddMonitor1st();

    void    EnumMT(const string &szParentID, const string &szDTName, const string &szNetworkSet);
private://slots
    //MOC: SLOT CEccAddMonitor1st::Cancel()
    void            Cancel();
    //MOC: SLOT CEccAddMonitor1st::AddMonitorByType(int)
    void            AddMonitorByType(int nMTID);
private:
    virtual void    initForm(bool bHasHelp);

    void            createOperate();

    void            removeMapping();

    WSignalMapper   m_MTMapper;

    list<WText*>    m_lsText;

    string          m_szParentID;
    string          m_szNetworkset;
    string          m_szDTName;
};

#endif
