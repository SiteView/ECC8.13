#ifndef _SiteView_Ecc_Sort_List_H_
#define _SiteView_Ecc_Sort_List_H_

#include "ecctable.h"
class CEccListTable;
class CEccTreeNode;
class CEccTreeGroup;
class CEccTreeDevice;

class WText;
class WLineEdit;


class CEccSortTable : public CEccBaseTable
{
    //MOC: W_OBJECT CEccSortTable:CEccBaseTable
    W_OBJECT;
public:
    CEccSortTable(WContainerWidget *parent = NULL);

    void        setSortNode(const CEccTreeNode *pNode, int nType);
private://slots
    //MOC: SLOT CEccSortTable::Cancel()
    void        Cancel();
    //MOC: SLOT CEccSortTable::Save()
    void        Save();
private:
    virtual void    initForm(bool bHasHelp);

    void            createOperate();
    void            createListTitle();

    void            enumDevice(const CEccTreeNode *pGroupNode);
    void            enumGroup(const CEccTreeNode *pGroupNode);
    void            enumMonitor(const CEccTreeNode *pDeviceNode);

    void            checkDisplayIndex();

    void            saveGroup(map<int, string, less<int> > &lsDis);
    void            saveDevice(map<int, string, less<int> > &lsDis);
    void            saveMonitor(map<int, string, less<int> > &lsDis);

    map<int, WLineEdit*, less<int> > m_lsIndexList;
    map<WLineEdit*, string, less<WLineEdit*> >  m_lsLineEdit;

    int             m_nDataType;
    string          m_szParentID;
};

#endif
