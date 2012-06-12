#ifndef _SiteView_ECC_Right_View_H_
#define _SiteView_ECC_Right_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WStackedWidget;
class WText;

#include <string>
#include <list>

using namespace std;

class   CEccSVSEView;
class   CEccGroupView;
class   CEccMonitorView;
class   CEccGroupOperate;
class   CEccButton;
class   CEccImportButton;
class   CEccTreeNode;
class   CEccAddDevice1st;
class   CEccAddDevice2nd;
class   CEccAddDevice3rd;
class   CEccAddMonitor1st;
class   CEccAddMonitor2nd;
class   CEccBatchAdd;
class   CEccSortForm;
class   CEccEidtSVSE;
class   CEccSortTable;

enum SiteView_Ecc_View
{
    SVSE_List_View,
    Group_List_View,
    Monitor_List_View,
    Edit_SVSE_View,
    Group_Operate_View,
    Add_Device_1st_View,
    Add_Device_2nd_View,
    Add_Device_3rd_View,
    Add_Monitor_1st_View,
    Add_Monitor_2nd_View,
    Add_Monitor_Batch_Add,
    SV_Sort_View
};

struct ecc_value_list
{
    ecc_value_list():
    m_szLabel(""),
    m_szValue("")
    {
    };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ecc_value_list(const string &szLabel, const string &szValue):
    m_szLabel(szLabel),
    m_szValue(szValue)
    {
    };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string m_szLabel;
    string m_szValue;
};

class CEccRightView : public WTable
{
    //MOC: W_OBJECT CEccRightView:WTable
    W_OBJECT;
public:
    CEccRightView(WContainerWidget *parent = NULL);

    static string   AddMonitorBySel(list<ecc_value_list> &lsValue);

    void            refreshCurrentNode(const CEccTreeNode *pNode);
    void            changeActive(const CEccTreeNode *pNode);
    void            clearNewMonitorList();
    bool            isNewMonitorListEmpty();
    static void     InsertNewMonitorList(const string &szIndex);

    string          refreshNewMonitors();

    static void     showAddGroupForm(string szIndex);

    static void     showAddDevice1st(string szIndex);
    static void     showAddDevice2nd(string szIndex, string szDTName);
    static void     showAddDevice3rd(string szIndex, string szName, string szRunParam, string szQuickAdd, 
                                     string szQuickAddSel, string szIsNetworkset);

    static void     showAddMonitor1st(string szIndex, string szDTType, string szNetworkset);
    static void     showAddMonitor2nd(int nMTID, string szParentID, string szNetworkset);

    static void     showBatchAddForm(list<ecc_value_list> &lsValue, string szDynName);

    void            showEditForm(const string &szIndex, bool &bMonitor);
    void            showEditMonitor(const string &szIndex);

    static void     showNewDevice(string szIndex);

    static void     showMainForm();

    static void     showSortForm(string szIndex, int nType);

    void            showSVSEView();

    static void     UpdateData(const CEccTreeNode *pNode);
private://slots
private:
    WStackedWidget              *m_pMainStack;

    static CEccSVSEView         *m_pSVSEView;
    static CEccGroupView        *m_pGroupview;
    static CEccMonitorView      *m_pMonitorview;

    CEccGroupOperate            *m_pGroupOperate;

    CEccAddDevice1st            *m_pAddDevice1st;
    CEccAddDevice2nd            *m_pAddDevice2nd;
    CEccAddDevice3rd            *m_pAddDevice3rd;

    CEccAddMonitor1st           *m_pAddMonitor1st;
    CEccAddMonitor2nd           *m_pAddMonitor2nd;

    CEccBatchAdd                *m_pBatchAdd;
    CEccEidtSVSE                *m_pEditSVSE;
    CEccSortTable               *m_pSortList;
private:
    void            initForm();

    int             m_nActiveView;
    int             m_nPreviewView;

    list<string>    m_lsNewMonitors;

    // Friend Class Lists;
    friend  class       CEccGroupView;
    friend  class       CEccMonitorView;
    friend  class       CEccTreeDevice;
    friend  class       CEccAddMonitor2nd;
    friend  class       CEccListTable;
};

#endif
