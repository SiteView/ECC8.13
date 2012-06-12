#include "rightview.h"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WStackedWidget"
#include "../../opens/libwt/WebSession.h"

#include "basedefine.h"
#include "svseview.h"
#include "groupview.h"
#include "monitorview.h"
#include "treeview.h"
#include "addgroup.h"
#include "pushbutton.h"
#include "debuginfor.h"
#include "mainview.h"
#include "adddevice1st.h"
#include "adddevice2nd.h"
#include "adddevice3rd.h"
#include "addmonitor1st.h"
#include "addmonitor2nd.h"
#include "batchadd.h"
#include "addsvse.h"
#include "sortlist.h"
#include "eccobjfunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 静态成员变量初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccSVSEView * CEccRightView::m_pSVSEView = NULL;
CEccGroupView * CEccRightView::m_pGroupview = NULL;
CEccMonitorView * CEccRightView::m_pMonitorview = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccRightView::CEccRightView(WContainerWidget *parent):
WTable(parent),
m_pMainStack(NULL),
m_pGroupOperate(NULL),
m_pAddDevice1st(NULL),
m_pAddDevice2nd(NULL),
m_pAddDevice3rd(NULL),
m_pAddMonitor1st(NULL),
m_pBatchAdd(NULL),
m_pEditSVSE(NULL)
{
    setStyleClass("panel");
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::initForm()
{
    int nRow = numRows();
    // 创建界面栈
    m_pMainStack = new WStackedWidget(elementAt(nRow, 0));
    elementAt(nRow, 0)->setContentAlignment(AlignTop);

    if(m_pMainStack)
    {
        // 得到SE的总数
        if(CEccTreeView::getSVSECount() > 1)
        {
            // 当前视图
            m_nActiveView = SVSE_List_View;
            
            m_pMainStack->addWidget(m_pSVSEView = new CEccSVSEView());
            if(m_pSVSEView)
                m_pMainStack->setCurrentWidget(m_pSVSEView);
        }
        else
        {
            // 组视图
            m_nActiveView = Group_List_View;
            // 创建组视图
            m_pMainStack->addWidget(m_pGroupview = new CEccGroupView());
            if(m_pGroupview)
            {
                // 设置为当前窗口
                m_pMainStack->setCurrentWidget(m_pGroupview);

                if(CEccMainView::m_pTreeView->m_pCurSel)
                    CEccMainView::m_pTreeView->m_pCurSel->setStyleClass("treelink");

                // 选择SE（1）
                const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject("1");
                if(pNode && pNode->m_pTreeText)
                {
                    CEccMainView::m_pTreeView->m_pCurSel = pNode->m_pTreeText;
                    CEccMainView::m_pTreeView->m_szCurSelIndex = pNode->getECCIndex();
                    pNode->m_pTreeText->setStyleClass("treelinkactive");
                    const CEccTreeGroup *pGroupnode = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
                    m_pGroupview->setCurrentObj(pGroupnode);
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 刷新当前节点
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::refreshCurrentNode(const CEccTreeNode *pNode)
{
    // 在 SE视图、组视图、监测器视图模式下刷新当前节点
    if(m_nActiveView == SVSE_List_View || m_nActiveView == Monitor_List_View ||
        m_nActiveView == Group_List_View)
        changeActive(pNode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::changeActive(const CEccTreeNode *pNode)
{
    if(m_pMainStack)
    {
        if(pNode->getType() == SiteView_ECC_Group || pNode->getType() == SiteView_ECC_SE)
        {
            m_nActiveView = Group_List_View;
            if(!m_pGroupview)
                m_pMainStack->addWidget(m_pGroupview = new CEccGroupView());
            if(m_pGroupview)
            {
                m_pMainStack->setCurrentWidget(m_pGroupview);
                CEccTreeGroup *pGroupnode = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
                m_pGroupview->setCurrentObj(pGroupnode);

                pGroupnode->showSubTables();
            }
        }
        else if(pNode->getType() == SiteView_ECC_Device)
        {
            m_nActiveView = Monitor_List_View;
            if(!m_pMonitorview)
                m_pMainStack->addWidget(m_pMonitorview = new CEccMonitorView());
            if(m_pMonitorview)
            {
                m_pMainStack->setCurrentWidget(m_pMonitorview);                
                const CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                m_pMonitorview->setDeviceNode(pDevice);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示SE 视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showSVSEView()
{
    if(m_pMainStack)
    {
        m_nActiveView = SVSE_List_View;
        if(!m_pSVSEView)
            m_pMainStack->addWidget(m_pSVSEView = new CEccSVSEView());

        if(m_pSVSEView)
        {
            m_pMainStack->setCurrentWidget(m_pSVSEView);
            m_pSVSEView->refreshTime();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示添加组视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showAddGroupForm(string szIndex)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pGroupOperate)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pGroupOperate = new CEccGroupOperate());

        if(CEccMainView::m_pRightView->m_pGroupOperate)
        {
            if(CEccMainView::m_pRightView->m_nActiveView == SVSE_List_View || CEccMainView::m_pRightView->m_nActiveView == Monitor_List_View ||
                        CEccMainView::m_pRightView->m_nActiveView == Group_List_View)
                CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

            CEccMainView::m_pRightView->m_nActiveView = Group_Operate_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pGroupOperate);
            CEccMainView::m_pRightView->m_pGroupOperate->AddGroup(szIndex);
        }
    }
    WebSession::js_af_up = "hiddenbar()";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示主视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showMainForm()
{
    string szCmd("hiddenbar();");

    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(CEccMainView::m_pRightView->m_nActiveView != SVSE_List_View || CEccMainView::m_pRightView->m_nActiveView != Monitor_List_View ||
                        CEccMainView::m_pRightView->m_nActiveView != Group_List_View)
            CEccMainView::m_pRightView->m_nActiveView = CEccMainView::m_pRightView->m_nPreviewView;

        switch(CEccMainView::m_pRightView->m_nActiveView)
        {
        case SVSE_List_View:
            if(CEccMainView::m_pRightView->m_pSVSEView)
            {
                CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(m_pSVSEView);
                CEccMainView::m_pRightView->m_pSVSEView->refreshTime();
            }
            break;
        case Group_List_View:
            if(CEccMainView::m_pRightView->m_pGroupview)
            {
                CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(m_pGroupview);
                CEccMainView::m_pRightView->m_pGroupview->refreshTime();
            }
            break;
        case Monitor_List_View:
            if(CEccMainView::m_pRightView->m_pMonitorview)
            {
                CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(m_pMonitorview);
                CEccMainView::m_pRightView->m_pMonitorview->refreshTime();
            }
            break;
        }
    }

    if(!CEccMainView::m_pRightView->m_lsNewMonitors.empty())
    {
        szCmd = CEccMainView::m_pRightView->refreshNewMonitors();// + szCmd;
    }

    WebSession::js_af_up += szCmd;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showNewDevice(string szIndex)
{
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szIndex);
    if(pNode)
    {
        CEccMainView::m_szCurrentOpt = szIndex;
        CEccMainView::m_pRightView->m_nActiveView = Monitor_List_View;

        if(CEccMainView::m_pTreeView->m_pCurSel)
            CEccMainView::m_pTreeView->m_pCurSel->setStyleClass("treelink");

        if(pNode && pNode->m_pTreeText)
        {
            CEccMainView::m_pTreeView->m_pCurSel = pNode->m_pTreeText;
            CEccMainView::m_pTreeView->m_szCurSelIndex = pNode->getECCIndex();
            pNode->m_pTreeText->setStyleClass("treelinkactive");
        }

        if(!CEccMainView::m_pRightView->m_pMonitorview)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(m_pMonitorview = new CEccMonitorView());
        if(CEccMainView::m_pRightView->m_pMonitorview)
        {
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pMonitorview);                
            const CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
            m_pMonitorview->setDeviceNode(pDevice);
        }
    }
    //? 刷新新监测器

    CEccMainView::m_pTreeView->BuildSEShowText(FindSEID(szIndex));
    if(!CEccMainView::m_pRightView->m_lsNewMonitors.empty())
        WebSession::js_af_up = CEccMainView::m_pRightView->refreshNewMonitors();// + "hiddenbar();";
    else
        WebSession::js_af_up = "hiddenbar();";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::UpdateData(const CEccTreeNode *pNode)
{
    if(CEccMainView::m_pRightView->m_nPreviewView == Group_List_View)
    {
        if(m_pGroupview)
        {
            const CEccTreeGroup *pGroupnode = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
            m_pGroupview->UpdataGeneralData(pGroupnode);
        }
    }
    else if(CEccMainView::m_pRightView->m_nPreviewView == Monitor_List_View)
    {
        if(m_pMonitorview)
        {
            const CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
            m_pMonitorview->UpdataGeneralData(pDevice);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showAddDevice1st(string szIndex)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pAddDevice1st)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddDevice1st = new CEccAddDevice1st());

        if(CEccMainView::m_pRightView->m_pAddDevice1st)
        {
            if(CEccMainView::m_pRightView->m_nActiveView == SVSE_List_View || CEccMainView::m_pRightView->m_nActiveView == Monitor_List_View ||
                        CEccMainView::m_pRightView->m_nActiveView == Group_List_View)
                CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

            CEccMainView::m_pRightView->m_nActiveView = Add_Device_1st_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddDevice1st);
            CEccMainView::m_pRightView->m_pAddDevice1st->setParentID(szIndex);
        }
    }
    WebSession::js_af_up = "hiddenbar()";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showAddDevice2nd(string szIndex, string szDTName)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pAddDevice2nd)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddDevice2nd = new CEccAddDevice2nd());

        if(CEccMainView::m_pRightView->m_pAddDevice2nd)
        {
            CEccMainView::m_pRightView->m_nActiveView = Add_Device_2nd_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddDevice2nd);
            CEccMainView::m_pRightView->m_pAddDevice2nd->AddDeviceByType(szIndex, szDTName);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showAddDevice3rd(string szIndex, string szName, string szRunParam, string szQuickAdd,string szQuickAddSel, 
                                     string szIsNetworkset)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pAddDevice3rd)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddDevice3rd = new CEccAddDevice3rd());

        if(CEccMainView::m_pRightView->m_pAddDevice2nd)
        {
            CEccMainView::m_pRightView->m_nActiveView = Add_Device_3rd_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddDevice3rd);
            CEccMainView::m_pRightView->m_pAddDevice3rd->QuickAdd(szIndex, szName, szRunParam, szQuickAdd, szQuickAddSel, szIsNetworkset);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showEditForm(const string &szIndex, bool &bMonitor)
{
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szIndex);
    if(pNode)
    {
        if(pNode->getType() == SiteView_ECC_Group)
        {
            if(CEccMainView::m_pRightView->m_pMainStack)
            {
                if(!CEccMainView::m_pRightView->m_pGroupOperate)
                    CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pGroupOperate = new CEccGroupOperate());

                if(CEccMainView::m_pRightView->m_pGroupOperate)
                {
                    if(m_nActiveView == SVSE_List_View || m_nActiveView == Monitor_List_View ||
                            m_nActiveView == Group_List_View)
                        CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

                    CEccMainView::m_pRightView->m_nActiveView = Group_Operate_View;
                    CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pGroupOperate);
                    CEccMainView::m_pRightView->m_pGroupOperate->EditGroup(szIndex);
                }
            }
        }
        else if(pNode->getType() == SiteView_ECC_Device)
        {
            if(CEccMainView::m_pRightView->m_pMainStack)
            {
                if(!CEccMainView::m_pRightView->m_pAddDevice2nd)
                    CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddDevice2nd = new CEccAddDevice2nd());

                if(CEccMainView::m_pRightView->m_pAddDevice2nd)
                {
                    if(m_nActiveView == SVSE_List_View || m_nActiveView == Monitor_List_View ||
                            m_nActiveView == Group_List_View)
                        CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

                    CEccMainView::m_pRightView->m_nActiveView = Add_Device_2nd_View;
                    CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddDevice2nd);
                    CEccMainView::m_pRightView->m_pAddDevice2nd->EditDevice(szIndex);
                }
            }
        }
        else if(pNode->getType() == SiteView_ECC_SE)
        {
            if(CEccMainView::m_pRightView->m_pMainStack)
            {
                if(!CEccMainView::m_pRightView->m_pEditSVSE)
                    CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pEditSVSE = new CEccEidtSVSE());

                if(CEccMainView::m_pRightView->m_pEditSVSE)
                {
                    if(m_nActiveView == SVSE_List_View || m_nActiveView == Monitor_List_View ||
                            m_nActiveView == Group_List_View)
                        CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

                    CEccMainView::m_pRightView->m_nActiveView = Edit_SVSE_View;
                    CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pEditSVSE);
                    CEccMainView::m_pRightView->m_pEditSVSE->EditSVSE(szIndex);
                }
            }
        }
    }
    else if(szIndex != "0" && !IsSVSEID(szIndex))
    {
        bMonitor = true;

        CEccMainView::m_pRightView->m_nPreviewView = Monitor_List_View;

        CEccMainView::m_pRightView->m_nActiveView = Add_Monitor_2nd_View;
        showEditMonitor(szIndex);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showAddMonitor1st(string szIndex, string szDTType, string szNetworkset)
{
    PrintDebugString("show monitor list!" + szIndex);
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pAddMonitor1st)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddMonitor1st = new CEccAddMonitor1st());

        if(CEccMainView::m_pRightView->m_pAddMonitor1st)
        {
            if(CEccMainView::m_pRightView->m_nActiveView == SVSE_List_View || CEccMainView::m_pRightView->m_nActiveView == Monitor_List_View ||
                        CEccMainView::m_pRightView->m_nActiveView == Group_List_View)
                CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

            CEccMainView::m_pRightView->m_nActiveView = Add_Monitor_1st_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddMonitor1st);
            CEccMainView::m_pRightView->m_pAddMonitor1st->EnumMT(szIndex, szDTType, szNetworkset);
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showAddMonitor2nd(int nMTID, string szParentID, string szNetworkset)
{
    PrintDebugString("Device ID is " + szParentID);
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pAddMonitor2nd)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddMonitor2nd = new CEccAddMonitor2nd());

        if(CEccMainView::m_pRightView->m_pAddMonitor2nd)
        {
            CEccMainView::m_pRightView->m_nActiveView = Add_Monitor_2nd_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddMonitor2nd);
            CEccMainView::m_pRightView->m_pAddMonitor2nd->AddMonitorByMTID(nMTID, szParentID, szNetworkset);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showEditMonitor(const string &szIndex)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pAddMonitor2nd)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pAddMonitor2nd = new CEccAddMonitor2nd());

        if(CEccMainView::m_pRightView->m_pAddMonitor2nd)
        {
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pAddMonitor2nd);
            CEccMainView::m_pRightView->m_pAddMonitor2nd->EditMonitorByID(szIndex);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showBatchAddForm(list<ecc_value_list> &lsValue, string szDynName)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        if(!CEccMainView::m_pRightView->m_pBatchAdd)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pBatchAdd = new CEccBatchAdd());

        if(CEccMainView::m_pRightView->m_pBatchAdd)
        {
            CEccMainView::m_pRightView->m_nActiveView = Add_Monitor_Batch_Add;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pBatchAdd);
            CEccMainView::m_pRightView->m_pBatchAdd->setListValue(lsValue, szDynName);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccRightView::AddMonitorBySel(list<ecc_value_list> &lsValue)
{
    if(CEccMainView::m_pRightView->m_pAddMonitor2nd)
        return CEccMainView::m_pRightView->m_pAddMonitor2nd->BatchAddMonitor(lsValue);

    return "";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::showSortForm(string szIndex, int nType)
{
    if(CEccMainView::m_pRightView->m_pMainStack)
    {
        const CEccTreeNode *pNode = CEccTreeView::getECCObject(szIndex);
        if(!CEccMainView::m_pRightView->m_pSortList)
            CEccMainView::m_pRightView->m_pMainStack->addWidget(CEccMainView::m_pRightView->m_pSortList = new CEccSortTable());

        if(CEccMainView::m_pRightView->m_pSortList && pNode)
        {
            if(CEccMainView::m_pRightView->m_nActiveView == SVSE_List_View || CEccMainView::m_pRightView->m_nActiveView == Monitor_List_View ||
                        CEccMainView::m_pRightView->m_nActiveView == Group_List_View)
                CEccMainView::m_pRightView->m_nPreviewView = CEccMainView::m_pRightView->m_nActiveView;

            CEccMainView::m_pRightView->m_nActiveView = SV_Sort_View;
            CEccMainView::m_pRightView->m_pMainStack->setCurrentWidget(CEccMainView::m_pRightView->m_pSortList);
            CEccMainView::m_pRightView->m_pSortList->setSortNode(pNode, nType);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::InsertNewMonitorList(const string &szIndex)
{
    CEccMainView::m_pRightView->m_lsNewMonitors.push_back(szIndex);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccRightView::refreshNewMonitors()
{
    //? refresh
    string szRefreshMonitor ("");
    // 创建刷新回写队列名称
    string szQueueName(makeQueueName());
    // 创建刷新回写队列
    CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    // 创建刷新队列
    list<string>::iterator lstItem(CEccMainView::m_pRightView->m_lsNewMonitors.begin());
    string szRefreshQueue(getRefreshQueueName((*lstItem)));
    CreateQueue(szRefreshQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    
    string szQuery ("");

    for(lstItem = CEccMainView::m_pRightView->m_lsNewMonitors.begin(); lstItem != CEccMainView::m_pRightView->m_lsNewMonitors.end();
        lstItem ++)
    {// 枚举每一个监测器索引
        if(!isDisable((*lstItem), SiteView_ECC_Monitor))
        {// 监测没有被禁止
            szQuery += (*lstItem);
            szQuery += "\v";
        }
        else
        {// 被禁止
            int nSize = static_cast<int>((*lstItem).length()) + 2;
            char *pszRefreshMonitor = new char[nSize];
            if(pszRefreshMonitor)
            {
                memset(pszRefreshMonitor, 0, nSize);
                strcpy( pszRefreshMonitor, (*lstItem).c_str());
                // 插入一条被禁止消息到刷新回写队列
                if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                    PrintDebugString("PushMessage into queue failed!");
                delete []pszRefreshMonitor;
            }
        }
    }
    int nSize = static_cast<int>(szQuery.length()) + 1;
    char *pszRefreshMonitor = new char[nSize];
    if(pszRefreshMonitor)
    {
        memset(pszRefreshMonitor, 0, nSize);
        strcpy( pszRefreshMonitor, szQuery.c_str());
        char *pPos = pszRefreshMonitor;
        while((*pPos) != '\0' )
        {
            if((*pPos) == '\v')
                (*pPos) = '\0';
            pPos ++;
        }
        
        // 插入刷新消息到刷新队列
        if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
            PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
        
        delete [] pszRefreshMonitor;
    }                    
    // JS函数
    szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
    szRefreshMonitor = szRefreshMonitor + "update('" + CEccMainView::m_szGlobalEvent + "');";

    
    CEccMainView::m_pRightView->m_lsNewMonitors.clear();

    return szRefreshMonitor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccRightView::clearNewMonitorList()
{
    CEccMainView::m_pRightView->m_lsNewMonitors.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccRightView::isNewMonitorListEmpty()
{
    return CEccMainView::m_pRightView->m_lsNewMonitors.empty();
}
