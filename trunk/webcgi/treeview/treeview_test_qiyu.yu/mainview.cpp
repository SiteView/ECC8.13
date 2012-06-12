#include "mainview.h"
#include "treeview.h"
#include "rightview.h"
#include "basedefine.h"
#include "debuginfor.h"
#include "eccobjfunc.h"

#include "../base/OperateLog.h"

#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WebSession.h"

#include "../userright/User.h"

#define WTGET

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化静态成员变量
CEccRightView * CEccMainView::m_pRightView = NULL;
CEccTreeView * CEccMainView::m_pTreeView = NULL;

string          CEccMainView::m_szAddr = "localhost";
string          CEccMainView::m_szIDCUser = "default";
string          CEccMainView::m_szGlobalEvent = "";
string          CEccMainView::m_szCurrentOpt = "";
string          CEccMainView::m_szLeftScroll = "";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccMainView::CEccMainView(WContainerWidget *parent):
WTable(parent),
m_pbtnConfirm(NULL),
m_pbtnRefresh(NULL),
m_pCurrentID(NULL),
m_pCurOperate(NULL),
m_szCurrentCopy(""),
m_szCurrentConfirm("")
{
    // 设置样式表
    setStyleClass("panel");
    // 创建隐藏变量 
    createHideObject();
    // 创建框架
    createFrame();

    m_bFirstLoad = true;

    // 设置当前操作值
    if(m_pTreeView)
        m_szCurrentOpt = m_pTreeView->m_szCurSelIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建框架
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::createFrame()
{
    // 得到当前行数
    int nRow = numRows();
    // 在当前行内分别创建 树 调整大小 右视图
    m_pTreeView = new CEccTreeView(elementAt(nRow, 0), GetWebUserID());
    // 替换此图片文件名
    WImage *pResize = new WImage("../Images/left.gif", elementAt(nRow,1));
    m_pRightView = new CEccRightView(elementAt(nRow, 2));

    // 设置树的背景样式
    elementAt(nRow, 0)->setStyleClass("tree_bg");

    // 创建调整大小栏成功
    if(pResize)
    {
        // 设置此TD的样式表
        elementAt(nRow, 1)->setStyleClass("resize");
        // 设置TD的操作响应
        strcpy(elementAt(nRow, 1)->contextmenu_, 
            "onmousedown='_canResize=true;this.setCapture(true)' "
            "onmouseup='this.releaseCapture();_canResize=false;'");
        
        pResize->setStyleClass("hand");
        sprintf(pResize->contextmenu_, "onclick='hideshowtree(this,\"%s\")'", elementAt(nRow, 0)->formName().c_str());
    }

    // 设置右视图的样式表
    elementAt(nRow, 2)->setStyleClass("rightview");

    // 设置左树的可操作名称
    //if(m_pTreeView)
    //    m_pTreeView->setLeftResizeName(elementAt(nRow, 0)->formName());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 得到树的操作名称
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccMainView::getTreeTableName()
{
    if(m_pTreeView)
        return m_pTreeView->formName();
    return "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 树上节点的单击处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::EccObjectClick()
{
    unsigned long ulStart = GetTickCount();
    if(m_pCurrentID && m_pRightView)
    {
        // 重设当前操作索引
        m_szCurrentOpt = m_pCurrentID->text();
        // 当前操作索引不等于树上被选择节点
        if(m_szCurrentOpt != m_pTreeView->m_szCurSelIndex)
        {
            // 重设样式表
            if(m_pTreeView->m_pCurSel)
                m_pTreeView->m_pCurSel->setStyleClass("treelink");

            // 当前不是操作的不是SE组
            if(m_szCurrentOpt != "0")
            {
                // 得到树上的节点
                const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentOpt);
                if(pNode && pNode->m_pTreeText)
                {
                    // 设置样式表
                    m_pTreeView->m_pCurSel = pNode->m_pTreeText;
                    m_pTreeView->m_szCurSelIndex = pNode->getECCIndex();
                    pNode->m_pTreeText->setStyleClass("treelinkactive");
                    m_pRightView->changeActive(pNode);
                }
            }
            else
            {
                // 选择了SE 组
                m_pTreeView->m_szCurSelIndex = "0";
                if(m_pTreeView->m_objRootGroup.m_pTreeText)
                {                    
                    m_pTreeView->m_pCurSel = m_pTreeView->m_objRootGroup.m_pTreeText;
                    m_pTreeView->m_objRootGroup.m_pTreeText->setStyleClass("treelinkactive");
                }
                
                // 显示SE组视图
                m_pRightView->showSVSEView();
            }
        }
    }
    WebSession::js_af_up = "hiddenbar()";

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccObjectClick", "Enter Object--->" + m_szCurrentOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccObjectClick", "Enter Object--->" + m_szCurrentOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 树节点右键菜单的单击处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::EccMenuClick()
{
    WebSession::js_af_up = "";

    string szOpt("");

    unsigned long ulStart = GetTickCount();

    // 是否是监测器
    bool bMonitor = false;
    // 刷新事件
    if(m_pbtnRefresh)
        m_szGlobalEvent = m_pbtnRefresh->getEncodeCmd("xclicked()");

    if(m_pCurrentID && m_pCurOperate && m_pRightView)
    {
        m_szCurrentOpt = m_pCurrentID->text();
        int nOperate = atoi(m_pCurOperate->text().c_str());
        const CEccTreeNode *pNode = NULL;

        // 处理每类操作
        switch(nOperate)
        {
        case SV_ADD_GROUP:                              // 添加组
            szOpt = "Add new sub Group";
            m_pRightView->showAddGroupForm(m_szCurrentOpt);
            break;
        case SV_ADD_DEVICE:                             // 添加设备
            szOpt = "Add new Device";
            m_pRightView->showAddDevice1st(m_szCurrentOpt);
            break;
        case SV_ADD_MONITOR:                            // 添加监测器
            szOpt = "Add new monitor";
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                m_pRightView->showAddMonitor1st(m_szCurrentOpt, pDevice->getRealDeviceType(), pDevice->isNetworkSet());
            }
            break;
        case SV_EDIT:                                   // 编辑
            m_pRightView->showEditForm(m_szCurrentOpt, bMonitor);
            if(bMonitor)
                m_szCurrentOpt = FindParentID(m_szCurrentOpt);
            break;
        case SV_DELETE:                                 // 删除
            m_szCurrentConfirm = m_szCurrentOpt;
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                if(m_pbtnConfirm && !m_pbtnConfirm->getEncodeCmd("xclicked()").empty())
                {
                    if(pNode->getType() == SiteView_ECC_Group)
                    {
                        szOpt = "Delete Group";
                        WebSession::js_af_up = "_Delclick('" + SVResString::getResString("IDS_Delete_Sel_Group_Confirm") + "','" +
                                            SVResString::getResString("IDS_ConfirmCancel") + "','" + SVResString::getResString("IDS_Affirm")
                                            + "','"  +  m_pbtnConfirm->getEncodeCmd("xclicked()") + "');hiddenbar();";
                    }
                    else if(pNode->getType() == SiteView_ECC_Device)
                    {
                        szOpt = "Delete Device";
                        WebSession::js_af_up = "_Delclick('" + SVResString::getResString("IDS_Delete_Sel_Device_Confirm") + "','" +
                                                SVResString::getResString("IDS_ConfirmCancel") + "','" + SVResString::getResString("IDS_Affirm")
                                                + "','"  +  m_pbtnConfirm->getEncodeCmd("xclicked()") + "');hiddenbar();";
                    }
                }
                else
                {
                    PrintDebugString("confirm button create failed");
                }
            }
            else if(m_szCurrentOpt != "0" && !m_szCurrentOpt.empty())
            {
                if(m_pbtnConfirm && !m_pbtnConfirm->getEncodeCmd("xclicked()").empty())
                {
                    szOpt = "Delete monitor";
                    WebSession::js_af_up = "_Delclick('" + SVResString::getResString("IDS_Delete_Monitor_Confirm") + "','" +
                                            SVResString::getResString("IDS_ConfirmCancel") + "','" + SVResString::getResString("IDS_Affirm")
                                            + "','"  +  m_pbtnConfirm->getEncodeCmd("xclicked()") + "');hiddenbar();";
                }
                else
                {
                    PrintDebugString("confirm button create failed");
                }
            }
            break;
        case SV_ENABLE:                                 // 启用
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                switch(pNode->getType())
                {
                case SiteView_ECC_Group:
                    if(isDisable(m_szCurrentOpt, SiteView_ECC_Group))
                    {// 组已启用
                        szOpt = "Enable Group";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=0&operatetype=1&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// 显示不能再次启用消息
                        szOpt = SVResString::getResString("IDS_Group_Can_not_Enable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Enable") + 
                        "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
                    }
                    break;
                case SiteView_ECC_Device:
                    if(isDisable(m_szCurrentOpt, SiteView_ECC_Device))
                    {// 设备已启用
                        szOpt = "Enable Device";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=1&operatetype=1&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// 显示不能再次启用消息
                        szOpt = SVResString::getResString("IDS_Device_Can_not_Enable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Enable") + 
                        "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
                    }
                    break;
                }
            }
            break;
        case SV_DISABLE:                                // 禁用
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                switch(pNode->getType())
                {
                case SiteView_ECC_Group:
                    if(!isDisable(m_szCurrentOpt, SiteView_ECC_Group))
                    {// 组已启用
                        szOpt = "Disable Group";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=0&operatetype=0&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// 组已禁止
                        szOpt = SVResString::getResString("IDS_Group_Can_not_Disable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Disable") + 
                            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";
                    }
                    break;
                case SiteView_ECC_Device:
                    if(!isDisable(m_szCurrentOpt, SiteView_ECC_Device))
                    {// 设备已启用
                        szOpt = "Disable Device";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=1&operatetype=0&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// 设备已禁止
                        szOpt = SVResString::getResString("IDS_Device_Can_not_Disable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Disable") + 
                            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
                    }
                    break;
                }
            }
            break;
        case SV_REFRESH:                                // 刷新
            szOpt = "Refresh Device";
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                if(pNode->getType() == SiteView_ECC_Device)
                {
                    CEccTreeDevice* pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                    RefreshDevice(pDevice);
                }
            }
            break;
        case SV_COPY:                                   // 拷贝
            szOpt = "Copy Device";
            m_szCurrentCopy = m_szCurrentOpt;
            WebSession::js_af_up = "hiddenbar();";
            break;
        case SV_PAST:                                   // 粘贴
            szOpt = "Paste Device";
            if(!isCanBePasteDevice(m_szCurrentCopy))
            {
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
            }
            else if(!m_szCurrentCopy.empty())
            {
                string szNewDevID = PasteDevice(m_szCurrentOpt, m_szCurrentCopy);
                if(!szNewDevID.empty())
                {
                    m_szCurrentOpt = szNewDevID;
                    CEccMainView::m_pRightView->showNewDevice(szNewDevID);
                }
            }
            break;
        case SV_TEST:                                   // 测试
            szOpt = "Test Device";
            TestDevice(m_szCurrentOpt);
            break;
        }
    }

    if(WebSession::js_af_up.empty())
        WebSession::js_af_up = "hiddenbar();";

    szOpt = m_szCurrentOpt + "--->" + szOpt;

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccMenuClick", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccMenuClick", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 添加 JavaScript变量
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::AddJsParam(string name, string value)
{  
    int nRow = numRows();
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    new WText(strTmp, elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建隐藏对象
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::createHideObject()
{
    // 设置焦点按钮
    WPushButton *pbtnHide = new WPushButton("", (WContainerWidget *)parent());
    if(pbtnHide)
    {
        // 绑定click事件
        WObject::connect(pbtnHide, SIGNAL(clicked()), this, SLOT(EccObjectClick()));
        pbtnHide->hide();
        AddJsParam("setNodeFocusButton", pbtnHide->getEncodeCmd("xclicked()"));
    }

    // 确认按钮
    m_pbtnConfirm = new WPushButton("", (WContainerWidget *)parent());
    {
        // 绑定click事件
        WObject::connect(m_pbtnConfirm, SIGNAL(clicked()), "showbar();", this, SLOT(ConfirmDelete()),
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        m_pbtnConfirm->hide();
    }

    // 刷新数据按钮
    m_pbtnRefresh = new WPushButton("", (WContainerWidget *)parent());
    if(m_pbtnRefresh)
    {
        // 绑定click事件
        WObject::connect(m_pbtnRefresh, SIGNAL(clicked()),"showbar();", this, SLOT(RefreshState()),
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        m_pbtnRefresh->hide();
        m_szGlobalEvent = m_pbtnRefresh->getEncodeCmd("xclicked()");
    }

    // 菜单操作按钮
    WPushButton *pbtnRunMenu = new WPushButton("", (WContainerWidget *)parent());
    if(pbtnRunMenu)
    {
        WObject::connect(pbtnRunMenu, SIGNAL(clicked()), this, SLOT(EccMenuClick()));
        pbtnRunMenu->hide();
        AddJsParam("runMenuButton", pbtnRunMenu->getEncodeCmd("xclicked()"));
    }

    // 当前操作索引
    m_pCurrentID = new WLineEdit("", (WContainerWidget *)parent());
    if(m_pCurrentID)
    {
        m_pCurrentID->hide();
        AddJsParam("curId", m_pCurrentID->formName());
    }

    // 当前操作
    m_pCurOperate = new WLineEdit("", (WContainerWidget *)parent());
    if(m_pCurOperate)
    {
        m_pCurOperate->hide();
        AddJsParam("curOprCode", m_pCurOperate->formName());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 确认删除
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::ConfirmDelete()
{
    unsigned long ulStart = GetTickCount();
    if(m_pTreeView)
    {
        // 得到选择的节点
        const CEccTreeNode *pNode = m_pTreeView->getECCObject(m_szCurrentConfirm);
        if(pNode)
        {
            // 数据是组或者设备，根据类型不同调用不同的删除函数
            if(pNode->getType() == SiteView_ECC_Group)
                m_pTreeView->DeleteGroupByID(m_szCurrentConfirm);
            else if(pNode->getType() == SiteView_ECC_Device)
                m_pTreeView->DeleteDeviceByID(m_szCurrentConfirm);
        }
        else if(m_szCurrentOpt != "0" && !m_szCurrentOpt.empty())
        {
            // 数据是监测器
            DeleteSVMonitor(m_szCurrentOpt, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            DeleteTable(m_szCurrentOpt, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

            // 得到父设备
            const CEccTreeNode *pNode = CEccTreeView::getECCObject(FindParentID(m_szCurrentOpt));
            if(pNode)
            {
                CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                map<int, CECCMonitor, less<int> >::iterator monitoritem;
                // 删除监测器列表中的数据
                for(monitoritem = pDevice->m_Monitors.begin(); monitoritem != pDevice->m_Monitors.end(); monitoritem ++)
                {
                    if(monitoritem->second.getECCIndex() == m_szCurrentOpt)
                    {
                        pDevice->m_Monitors.erase(monitoritem);
                        break;
                    }
                }
            }
        }
        
        if(m_pTreeView->isCurrentPathEdit(m_szCurrentConfirm))
        {// 当前操作数据的路径中有对象被删除
            // 得到父节点
            const CEccTreeNode *pCurNode = m_pTreeView->getECCObject(FindParentID(m_szCurrentConfirm));
            if(pCurNode && pCurNode->m_pTreeText && m_pRightView)
            {
                m_pTreeView->m_pCurSel = pCurNode->m_pTreeText;
                m_pTreeView->m_szCurSelIndex = pCurNode->getECCIndex();
                pCurNode->m_pTreeText->setStyleClass("treelinkactive");
                // 重设数据
                m_pRightView->changeActive(pCurNode);
            }
        }
        else if(m_pTreeView->isCurrentChildEdit(m_szCurrentConfirm))
        {// 当前操作数据的子数据被删除
            if(m_pTreeView->m_szCurSelIndex == m_szCurrentConfirm)
                m_pTreeView->m_szCurSelIndex = FindParentID(m_szCurrentConfirm);
            const CEccTreeNode *pCurNode = m_pTreeView->getECCObject(m_pTreeView->m_szCurSelIndex);
            if(pCurNode && pCurNode->m_pTreeText && m_pRightView)
            {
                m_pTreeView->m_pCurSel = pCurNode->m_pTreeText;
                m_pTreeView->m_szCurSelIndex = pCurNode->getECCIndex();
                pCurNode->m_pTreeText->setStyleClass("treelinkactive");
                m_pRightView->changeActive(pCurNode);
            }
        }
    }

    // 如果确认数据等于待拷贝对象索引，待拷贝对象索引清空
    if(m_szCurrentConfirm == m_szCurrentCopy)
        m_szCurrentCopy = "";

    int nPos = static_cast<int>(m_szCurrentCopy.find(m_szCurrentConfirm));
    if(nPos > 0)
        m_szCurrentCopy = "";

    m_szCurrentConfirm = "";

    WebSession::js_af_up = "hiddenbar();";

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.ConfirmDelete", "Delete Object--->" + m_szCurrentConfirm, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.ConfirmDelete", "Delete Object--->" + m_szCurrentConfirm, 
        0, GetTickCount() - ulStart);

    m_szCurrentConfirm = "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 刷新状态
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::RefreshState()
{
    if(m_pTreeView && m_pRightView)
    {
        m_pTreeView->ReCreateTreeNode(m_szCurrentOpt);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 测试设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::TestDevice(const string &szIndex)
{
    string szParam(enumDeviceRunParam(szIndex));
    szParam += "&seid=";
    szParam += FindSEID(szIndex);
    if(!szParam.empty())
    {
        szParam = "showtestdevice('testdevice.exe?" + szParam +"');hiddenbar();" ;
        WebSession::js_af_up = szParam;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 刷新设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::RefreshDevice(const CEccTreeDevice *pDevice)
{
    if(!pDevice->m_Monitors.empty())
    {// 监测器总数大于零
        // 创建刷新回写队列名
        string szQueueName(makeQueueName());
        // 创建刷新回写队列
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szAddr);
        // 创建刷新队列
        string szRefreshQueue(getRefreshQueueName(m_szCurrentOpt));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szAddr);

        string szQuery ("");
        map<int, CECCMonitor, less<int> >::const_iterator itmonitor;

        for(itmonitor = pDevice->m_Monitors.begin(); itmonitor != pDevice->m_Monitors.end(); itmonitor ++)
        {// 枚举每个监测器
            if(!isDisable(itmonitor->second.getECCIndex(), SiteView_ECC_Monitor))
            {// 监测器没有被禁止
                szQuery += itmonitor->second.getECCIndex();
                szQuery += "\v";
            }
            else
            {// 监测器被禁止
                int nSize = static_cast<int>(itmonitor->second.getECCIndex().length()) + 2;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {  
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, itmonitor->second.getECCIndex().c_str());
                    // 插入一条监测器被禁止消息到刷新回写队列
                    if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szAddr))
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
            if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szAddr))
                PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            delete [] pszRefreshMonitor;
        }

        WebSession::js_af_up = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');" + 
            "update('" + CEccMainView::m_szGlobalEvent + "');";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// refresh
// 刷新
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::refresh()
{
    if(!m_bFirstLoad)
    {
        unsigned long ulStart = GetTickCount();

        InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.refresh", SVResString::getResString("IDS_Refresh_GUI"), 
            0, 0);

        if(m_pTreeView)
        {
            // 重置用户 ID
            m_pTreeView->resetUserID(GetWebUserID());

            // 得到请求字符串
            char szQuery[4097] = {0};
    #ifdef WTGET
            GetEnvironmentVariable("QUERY_STRING", szQuery, sizeof(szQuery));
    #else
            char * tmpQuery = getenv( "QUERY_STRING");
            if(tmpQuery && strlen(tmpQuery) > 0 && strlen(tmpQuery) < sizeof(szQuery))
                strcpy(szQuery, tmpQuery);
    #endif
            if(strlen(szQuery) > 0)
            {
                // 长度大于 0
                char *pPos = strchr(szQuery, '=');
                if(pPos)
                {
                    pPos ++;
                    m_szCurrentOpt = pPos;
                    if(m_szCurrentOpt != m_pTreeView->m_szCurSelIndex)
                    {
                        if(m_pTreeView->m_pCurSel)
                            m_pTreeView->m_pCurSel->setStyleClass("treelink");

                        if(m_szCurrentOpt != "0")
                        {
                            const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentOpt);
                            if(pNode && pNode->m_pTreeText)
                            {
                                m_pTreeView->m_pCurSel = pNode->m_pTreeText;
                                m_pTreeView->m_szCurSelIndex = pNode->getECCIndex();
                                pNode->m_pTreeText->setStyleClass("treelinkactive");
                                m_pRightView->refreshCurrentNode(pNode);
                            }
                        }
                        else
                        {
                            m_pTreeView->m_szCurSelIndex = "0";
                            if(m_pTreeView->m_objRootGroup.m_pTreeText)
                            {                    
                                m_pTreeView->m_pCurSel = m_pTreeView->m_objRootGroup.m_pTreeText;
                                m_pTreeView->m_objRootGroup.m_pTreeText->setStyleClass("treelinkactive");
                            }
                            m_pRightView->showSVSEView();
                        }
                    }
                }
            }
        }

        InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.refresh", SVResString::getResString("IDS_Refresh_GUI"), 
            0, GetTickCount() - ulStart);
    }
    else
    {
        m_bFirstLoad = false;
    }
}

