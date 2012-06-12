#include "treeview.h"
#include "mainview.h"
#include "rightview.h"
#include "resstring.h"
#include "basedefine.h"
#include "debuginfor.h"
#include "monitorview.h"
#include "../base/OperateLog.h"

#include "../../opens/libwt/Websession.h"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"

#include "../userright/User.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CUser       CEccTreeView::m_SVSEUser;
OperateLog  CEccTreeView::m_OperateLog;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeView::CEccTreeView(WContainerWidget *parent, string szUserID):
WTable(parent),
m_pTree(NULL),
m_pCurSel(NULL),
m_pHideOpt(NULL),
m_szCurSelIndex("")
{
    setStyleClass("panel");
    m_SVSEUser.setUserID(szUserID);
    initForm();
    EnumSVSE();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::createContent()
{
    int nRow = numRows();
    WTable *pContent = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("treeview");
    //elementAt(nRow, 0)->setContentAlignment(AlignBottom);
    if(pContent)
    {
        pContent->setStyleClass("viewtreebody");
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pContent);
            pScroll->setStyleClass("viewtreebody");
            CEccMainView::m_szLeftScroll = pScroll->formName();
        }

        m_pTree = new WTable(pContent->elementAt(0, 0));
        //if(m_pTree)
        //    m_pTree->setStyleClass("widthauto");
        
        pContent->elementAt(0, 0)->setContentAlignment(AlignTop);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::createTitle()
{
    int nRow = numRows();
    WTable *pRefresh = new WTable(elementAt(nRow, 0));
    if(pRefresh)
    {
        pRefresh->setStyleClass("tree_sync");
        WText *pReload = new WText(SVResString::getResString("IDS_Refresh_View"), pRefresh->elementAt(0, 0));
        new WImage("../Images/tree_sync.gif", pRefresh->elementAt(0, 0));
        pRefresh->elementAt(0, 0)->setStyleClass("hand");
        
        //sprintf(pRefresh->elementAt(0, 0)->contextmenu_, "class='width100p' style='top:-1px;border=1px solid "
        //                    "#cccccc;color:#669;cursor:pointer;' onmouseover='this.style.border=\"1px solid "#003399\";' onmouseout='this.style."
        //                    "backgroundColor=\"#CCCCCC\";this.style.border=\"1px solid #cccccc\";'");

        WObject::connect(pRefresh->elementAt(0, 0), SIGNAL(clicked()), "showbar();", this, SLOT(ReloadTreeView()),
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);

        //new WText("&nbsp;", pRefresh->elementAt(0, 1));

        //m_pHideOpt = new WImage("../Images/tree_hide.gif", pRefresh->elementAt(0, 1));
        //pRefresh->elementAt(0, 1)->setStyleClass("hand");
        //sprintf(pRefresh->elementAt(0, 2)->contextmenu_, "style='top:-1px;border=1px solid #cccccc;color:#669;"
        //                    "cursor:pointer;' onmouseover='this.style.backgroundColor=\"#CCCCFF\";this.style."
        //                    "border=\"1px solid #003399\";' onmouseout='this.style.backgroundColor=\"#CCCCCC\""
        //                    ";this.style.border=\"1px solid #cccccc\";'");
        //pRefresh->elementAt(0, 1)->setContentAlignment(AlignRight);
    }

    elementAt(nRow, 0)->setContentAlignment(AlignRight | AlignBottom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::initForm()
{
    createTitle();
    createContent();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeNode::CEccTreeNode():
m_nDisableCount(0),
m_nErrorCount(0),
m_nMonitorCount(0),
m_nShowIndex(0),
m_nState(0),
m_nType(0),
m_nWarnningCount(0),
m_nPurview(0),
m_szIndex(""),
m_szName(""),
m_szShowText(""),
m_szDependsOn(""),
m_szDepCondition(""),
m_szDescription(""),
m_szState(""),
m_pTreeText(NULL),
m_pImgType(NULL)
{
    m_tRefreshTime =  TTime::GetCurrentTimeEx();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeNode::~CEccTreeNode()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeNode::Reset()
{
    m_nDisableCount = 0;
    m_nErrorCount = 0;
    m_nMonitorCount = 0;
    m_nShowIndex = 0;
    m_nState = 0;
    m_nType = 0;
    m_nWarnningCount = 0;
    m_nPurview = 0;
    m_szIndex = "";
    m_szName = "";
    m_szShowText = "";
    m_szDependsOn = "";
    m_szDepCondition = "";
    m_szDescription = "";
    m_szState = "";
    m_pTreeText = NULL;
    m_pImgType = NULL;
    m_tRefreshTime =  TTime::GetCurrentTimeEx();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getDisableCount() const
{
    return m_nDisableCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getECCIndex() const
{
    return m_szIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getErrorCount() const
{
    return m_nErrorCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getMointorCount() const
{
    return m_nMonitorCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getName() const
{
    return m_szName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getPurview() const
{
    return m_nPurview;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getShowIndex() const
{
    return m_nShowIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getShowText() const
{
    return m_szShowText;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getShowTime() const
{
    return m_tRefreshTime.Format();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getDependsID() const
{
    return m_szDependsOn;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getCondition() const
{
    return m_szDepCondition;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeNode::getDescription() const
{
    return m_szDescription;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getState() const
{
    return m_nState;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getType() const
{
    return m_nType;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeNode::getWarnCount() const
{
    return m_nWarnningCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeDevice::CEccTreeDevice():
m_szRealDeviceType(""),
m_szDeviceType(""),
m_szOSType(""),
m_szIsNetworkset("")
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeDevice::~CEccTreeDevice()
{
    m_Monitors.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeDevice::Reset()
{
    CEccTreeNode::Reset();
    m_Monitors.clear();

    m_szRealDeviceType = "";
    m_szDeviceType = "";
    m_szOSType = "";
    m_szIsNetworkset = "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeDevice::getDeviceType() const
{
    return m_szDeviceType;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeDevice::getRealDeviceType() const
{
    return m_szRealDeviceType;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeDevice::getOSType() const
{
    return m_szOSType;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeDevice::isNetworkSet() const
{
    return m_szIsNetworkset;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccTreeDevice::MTCanUsing(int nMTID)
{
    list<int> lsMTID;
    list<int>::iterator it;

    CEccMainView::m_pTreeView->GetDevMTList(m_szRealDeviceType, lsMTID);

    for(it = lsMTID.begin(); it != lsMTID.end(); it ++)
        if((*it) == nMTID)
            return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeDevice::EditMonitor(const string &szIndex, const string &szName)
{
    string szOldName("");

    map<int, CECCMonitor, less<int> >::iterator monitor;
    for(monitor = m_Monitors.begin(); monitor != m_Monitors.end(); monitor ++)
    {
        if(monitor->second.getECCIndex() == szIndex)
        {
            string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Monitor_Title") +
                            "(Index)" + szIndex + "---(old)" + monitor->second.m_szName + ":" 
                            + szOldName + "---(new)" + SVResString::getResString("IDS_Name") + ":" + szName 
                            + "---parent id is " + m_szIndex + "---" + SVResString::getResString("IDS_Name") +
                            ":" + m_szName;

            CEccTreeView::AddOperaterLog(SV_EDIT, SiteView_ECC_Monitor, szMsg);

            monitor->second.m_szName = szName;

            CEccMainView::m_pRightView->m_lsNewMonitors.push_back(szIndex);
        }
    }
    //? 记录日志
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeDevice::AppendMonitor(const string &szIndex, const string &szName, int nMTID)
{
    map<int, CECCMonitor, less<int> >::iterator mapitem;

    m_nMonitorCount ++;

    CECCMonitor objMonitor;

    objMonitor.m_szIndex = szIndex;
    objMonitor.m_nShowIndex = FindIndexByID(objMonitor.m_szIndex);
    objMonitor.m_szName = szName;
    objMonitor.m_nMTID = nMTID;
    mapitem = m_Monitors.find(objMonitor.m_nShowIndex);
    while(mapitem != m_Monitors.end())
    {
        objMonitor.m_nShowIndex ++;
        mapitem = m_Monitors.find(objMonitor.m_nShowIndex);
    }

    char chState[512] = {0};
    if(!m_szOSType.empty() && !m_szDeviceType.empty())
    {
        sprintf(chState, "%s%s%s,%s%s,%s%d,%s%d,%s%d,%s%d",
            m_szState.c_str(),
            SVResString::getResString("IDS_Device_Type").c_str(), m_szDeviceType.c_str(),
            SVResString::getResString("IDS_OS_Type").c_str(), m_szOSType.c_str(),
            SVResString::getResString("IDS_Monitor_Count").c_str(), m_nMonitorCount, 
            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), m_nDisableCount,
            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), m_nErrorCount, 
            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), m_nWarnningCount);
    }
    else if(!m_szDeviceType.empty())
    {
        sprintf(chState, "%s%s%s,%s%d,%s%d,%s%d,%s%d", 
            m_szState.c_str(),
            SVResString::getResString("IDS_Device_Type").c_str(), m_szDeviceType.c_str(),
            SVResString::getResString("IDS_Monitor_Count").c_str(), m_nMonitorCount, 
            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), m_nDisableCount,
            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), m_nErrorCount, 
            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), m_nWarnningCount);
    }
    else
    {
        sprintf(chState, "%s%s%d,%s%d,%s%d,%s%d", 
            m_szState.c_str(),
            SVResString::getResString("IDS_Monitor_Count").c_str(), m_nMonitorCount, 
            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), m_nDisableCount,
            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), m_nErrorCount, 
            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), m_nWarnningCount);
    }
    m_szShowText = chState;

    m_Monitors[objMonitor.m_nShowIndex] = objMonitor;
    
    CEccMainView::m_pRightView->m_lsNewMonitors.push_back(szIndex);

    //? 记录日志
    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Monitor_Title") +
            "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + 
            m_szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + m_szName;

    CEccTreeView::AddOperaterLog(SV_ADD_MONITOR, SiteView_ECC_Monitor, szMsg);

    if(CEccMainView::m_pTreeView->m_szCurSelIndex == m_szIndex)
        CEccMainView::m_pRightView->changeActive(this);

    return objMonitor.m_nShowIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeGroup::CEccTreeGroup():
m_nDeviceCount(0),
m_pImageExpand(NULL),
m_pSubGroupsTable(NULL),
m_pDevicesTable(NULL)
{
    m_Devices.clear();
    m_SubGroups.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccTreeGroup::~CEccTreeGroup()
{
    m_Devices.clear();
    m_SubGroups.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeGroup::Reset()
{
    CEccTreeNode::Reset();

    m_Devices.clear();
    m_SubGroups.clear();
    m_nDeviceCount = 0;
    m_pSubGroupsTable = NULL;
    m_pDevicesTable = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeGroup::getDeviceCount() const
{
    return m_nDeviceCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeGroup::AppendDevice(const string &szIndex, const string &szName, const string &szDesc, const string &szDepends,
                             const string &szCondition, const string &szDeviceType, const string &szOsType,
                             const string &szIsNetworkSet, const string &szMenu, int nPurview)
{
    CEccTreeDevice objDevice;
    objDevice.m_szIndex = szIndex;
    objDevice.m_szName = szName;
    objDevice.m_szDescription = szDesc;
    objDevice.m_szDependsOn = szDepends;
    objDevice.m_szDepCondition = szCondition;
    objDevice.m_szRealDeviceType = szDeviceType;
    objDevice.m_szDeviceType = CEccMainView::m_pTreeView->getDeviceShowType(objDevice.m_szRealDeviceType);
    objDevice.m_szOSType = GetIniFileString(szOsType, "description", "", "oscmd.ini");;
    objDevice.m_szIsNetworkset = szIsNetworkSet;
    objDevice.m_nType = SiteView_ECC_Device;
    objDevice.m_nPurview = nPurview;

    if(m_pDevicesTable)
    {
        int nRow = m_pDevicesTable->numRows();
        new WImage("../Images/space.gif", m_pDevicesTable->elementAt(nRow, 0));
        if(objDevice.m_szIsNetworkset == "true")
            objDevice.m_pImgType = new WImage("../Images/cbb-5router.gif", m_pDevicesTable->elementAt(nRow, 1));
        else
            objDevice.m_pImgType = new WImage("../Images/cbb-4server.gif", m_pDevicesTable->elementAt(nRow, 1));

        objDevice.m_pTreeText = new WText(objDevice.m_szName, m_pDevicesTable->elementAt(nRow, 1));
        if(objDevice.m_pTreeText)
        {
            sprintf(objDevice.m_pTreeText->contextmenu_, "onclick='SetCurfocus(\"%s\")' onmouseover='mouseover(this)' "
                "onmouseout='mouseout(this)' oncontextmenu='showPopMenu(\"%s\", \"%s\");'", objDevice.m_szIndex.c_str(),
                objDevice.m_szIndex.c_str(), szMenu.c_str());
            objDevice.m_pTreeText->setStyleClass("treelink");
        }
        //strcpy(m_pDevicesTable->elementAt(nRow, 0)->contextmenu_, "class='padding_right_2' width=14px");
        m_pDevicesTable->elementAt(nRow, 0)->setStyleClass("width14");
        m_pDevicesTable->elementAt(nRow, 1)->setStyleClass("padding_right_2");

        WebSession::js_af_up = "document.getElementById(\"" + m_pDevicesTable->GetRow(nRow)->formName() 
            + "\").scrollIntoView(true);";
    }

    OBJECT svDevice = GetEntity(szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(svDevice != INVALID_VALUE)
    {
        MAPNODE mainNode = GetEntityMainAttribNode(svDevice);
        if(mainNode != INVALID_VALUE)
        {
            if(CEccMainView::m_pTreeView->isObjectDisable(mainNode, objDevice.m_szState, SiteView_ECC_Device))
                objDevice.m_nState = dyn_disable;

            char chState[512] = {0};
            if(!objDevice.m_szOSType.empty() && !objDevice.m_szDeviceType.empty())
            {
                sprintf(chState, "%s%s%s,%s%s,%s%d,%s%d,%s%d,%s%d",
                    objDevice.m_szState.c_str(),
                    SVResString::getResString("IDS_Device_Type").c_str(), objDevice.m_szDeviceType.c_str(),
                    SVResString::getResString("IDS_OS_Type").c_str(), objDevice.m_szOSType.c_str(),
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objDevice.m_nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objDevice.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objDevice.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objDevice.m_nWarnningCount);
            }
            else if(!objDevice.m_szDeviceType.empty())
            {
                sprintf(chState, "%s%s%s,%s%d,%s%d,%s%d,%s%d", 
                    objDevice.m_szState.c_str(),
                    SVResString::getResString("IDS_Device_Type").c_str(), objDevice.m_szDeviceType.c_str(),
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objDevice.m_nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objDevice.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objDevice.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objDevice.m_nWarnningCount);
            }
            else
            {
                sprintf(chState, "%s%s%d,%s%d,%s%d,%s%d", 
                    objDevice.m_szState.c_str(),
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objDevice.m_nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objDevice.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objDevice.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objDevice.m_nWarnningCount);
            }
            objDevice.m_szShowText = chState;
        }
        CloseEntity(svDevice);
    }
    objDevice.m_nShowIndex = FindIndexByID(objDevice.m_szIndex);
    map<int, CEccTreeDevice, less<int> >::iterator deviceitem = m_Devices.find(objDevice.m_nShowIndex);
    while(deviceitem != m_Devices.end())
    {
        objDevice.m_nShowIndex ++;
        deviceitem = m_Devices.find(objDevice.m_nShowIndex);
    }
    m_Devices[objDevice.m_nShowIndex] = objDevice;

    if(m_pImageExpand)
        m_pImageExpand->setImageRef("../Images/cb1-fold.gif");

    return objDevice.m_nShowIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeGroup::AppendGroup(const string &szIndex, const string &szName, const string &szDesc, const string &szDepends,
                                const string &szCondition, const string &szMenu, int nPurview)
{
    CEccTreeGroup objGroup;
    objGroup.m_szIndex = szIndex;
    objGroup.m_szName = szName;
    objGroup.m_szDescription = szDesc;
    objGroup.m_szDependsOn = szDepends;
    objGroup.m_szDepCondition = szCondition;
    objGroup.m_nPurview = nPurview;

    if(m_pSubGroupsTable)
    {
        int nRow = m_pSubGroupsTable->numRows();
        objGroup.m_pImageExpand = new WImage("../Images/cb1-fold.gif", m_pSubGroupsTable->elementAt(nRow, 0));
        objGroup.m_pImgType = new WImage("../Images/cbb-3group.gif", m_pSubGroupsTable->elementAt(nRow, 1));
        objGroup.m_pTreeText = new WText(objGroup.m_szName, m_pSubGroupsTable->elementAt(nRow, 1));

        //strcpy(m_pSubGroupsTable->elementAt(nRow, 0)->contextmenu_, "class='padding_right_2' width=14px");
        m_pSubGroupsTable->elementAt(nRow, 0)->setStyleClass("width14");
        m_pSubGroupsTable->elementAt(nRow, 1)->setStyleClass("padding_right_2");
        if(objGroup.m_pTreeText)
        {
            objGroup.m_nType = SiteView_ECC_Group;
            sprintf(objGroup.m_pTreeText->contextmenu_, "onclick='SetCurfocus(\"%s\")' "
                "onmouseover='mouseover(this)' onmouseout='mouseout(this)' oncontextmenu='showPopMenu"
                "(\"%s\", \"%s\");'", objGroup.m_szIndex.c_str(), objGroup.m_szIndex.c_str(), szMenu.c_str());
            objGroup.m_pTreeText->setStyleClass("treelink");
        }

        objGroup.m_pSubGroupsTable = new WTable(m_pSubGroupsTable->elementAt(nRow + 1, 1));
        objGroup.m_pDevicesTable = new WTable(m_pSubGroupsTable->elementAt(nRow + 2, 1));

        if(objGroup.m_pSubGroupsTable)
            objGroup.m_pSubGroupsTable->setStyleClass("widthauto");

        if(objGroup.m_pDevicesTable)
            objGroup.m_pDevicesTable->setStyleClass("widthauto");

        if(objGroup.m_pImageExpand)
            objGroup.m_pImageExpand->setImageRef("../Images/space.gif");

        if(objGroup.m_pImageExpand && objGroup.m_pSubGroupsTable && objGroup.m_pDevicesTable)
        {
            string szContext = "onclick='treenodeclick(this, \"" + objGroup.m_pSubGroupsTable->formName()
                + "\", \"" + objGroup.m_pDevicesTable->formName() + "\")' style='cursor:pointer'";
            strcpy(objGroup.m_pImageExpand->contextmenu_, szContext.c_str());
        }

        WebSession::js_af_up = "document.getElementById(\"" + m_pSubGroupsTable->GetRow(nRow)->formName() 
            + "\").scrollIntoView(true);";
    }

    objGroup.m_nShowIndex = FindIndexByID(objGroup.m_szIndex);
    map<int, CEccTreeGroup, less<int> >::iterator groupitem = m_SubGroups.find(objGroup.m_nShowIndex);
    while(groupitem != m_SubGroups.end())
    {
        objGroup.m_nShowIndex ++;
        groupitem = m_SubGroups.find(objGroup.m_nShowIndex);
    }
    m_SubGroups[objGroup.m_nShowIndex] = objGroup;

    CEccMainView::m_pTreeView->m_szCurSelIndex = szIndex;

    if(CEccMainView::m_pTreeView->m_pCurSel)
        CEccMainView::m_pTreeView->m_pCurSel->setStyleClass("treelink");

    if(objGroup.m_pTreeText)
    {
        objGroup.m_pTreeText->setStyleClass("treelinkactive");
        CEccMainView::m_pTreeView->m_pCurSel = objGroup.m_pTreeText;
    }

    if(m_pImageExpand)
        m_pImageExpand->setImageRef("../Images/cb1-fold.gif");

    OBJECT svGroup = GetGroup(szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(svGroup != INVALID_VALUE)
    {
        MAPNODE mainNode = GetGroupMainAttribNode(svGroup);
        if(mainNode != INVALID_VALUE)
        {
            if(CEccMainView::m_pTreeView->isObjectDisable(mainNode, objGroup.m_szState, SiteView_ECC_Group))
                objGroup.m_nState = dyn_disable;

            char chState[512] = {0};
            sprintf(chState, "%s%s%d,%s%d,%s%d,%s%d,%s%d", 
                objGroup.m_szState.c_str(),
                SVResString::getResString("IDS_Device_Count").c_str(), objGroup.m_nDeviceCount,
                SVResString::getResString("IDS_Monitor_Count").c_str(), objGroup.m_nMonitorCount,
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objGroup.m_nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objGroup.m_nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objGroup.m_nWarnningCount);

            objGroup.m_szShowText = chState;
        }
        CloseGroup(svGroup);
    }

    CEccMainView::m_pRightView->changeActive(&objGroup);

    return objGroup.m_nShowIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeGroup::showSubTables()
{
    if(m_pDevicesTable)
        m_pDevicesTable->show();

    if(m_pSubGroupsTable)
        m_pSubGroupsTable->show();

    if(m_pImageExpand && m_Devices.empty() && m_SubGroups.empty())
    {
        m_pImageExpand->setImageRef("../Images/space.gif");
    }
    else if(m_pImageExpand)
    {
        m_pImageExpand->setImageRef("../Images/cb1-fold.gif");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::ReloadTreeView()
{
    unsigned long ulStart = GetTickCount();

    reloadTree();
    WebSession::js_af_up = "hiddenbar();";

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccTreeView.ReloadTreeView", SVResString::getResString("IDS_Refresh_View"), 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccTreeView.ReloadTreeView", SVResString::getResString("IDS_Refresh_View"), 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::reloadTree()
{
    if(m_pTree)
        m_pTree->clear();
    m_SVSEList.clear();
    
    m_pCurSel = NULL;

    m_objRootGroup.Reset();

    EnumSVSE();

    if(!m_szCurSelIndex.empty())
    {
refreshenode:
        const CEccTreeNode *pNode = getECCObject(m_szCurSelIndex);
        if(pNode)
        {
            if(pNode->m_pTreeText)
            {
                pNode->m_pTreeText->setStyleClass("treelinkactive");
                m_pCurSel = pNode->m_pTreeText;
                CEccMainView::m_pRightView->refreshCurrentNode(pNode);
            }
        }
        else
        {
            if(m_szCurSelIndex != "1")
            {
                m_szCurSelIndex = "1";                
                goto refreshenode;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::resetUserID(const string &szUserID)
{
    if(m_SVSEUser.getUserID() != szUserID)
    {
        m_szCurSelIndex = "1";

        m_SVSEUser.setUserID(szUserID);
    }

    reloadTree();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EnumSVSE()
{
    PAIRLIST selist;
    PAIRLIST::iterator iSe;
    string szRootname("");
    int nRow = 0;

    bool bHasRight = false;
    if(GetIniFileInt("solover", "solover", 1, "general.ini") == 1)
    {
        m_objRootGroup.m_szIndex = "1";
        m_objRootGroup.m_nType = SiteView_ECC_SE;
        bHasRight = m_SVSEUser.haveGroupRight(m_objRootGroup.m_szIndex, SiteView_ECC_SE);
        if(bHasRight)
        {
            EnumGroups(m_objRootGroup);

            m_SVSEList[m_objRootGroup.m_szIndex] = m_objRootGroup;
        }
    }
    else
    {
        string szName(GetIniFileString("segroup", "name", "", "general.ini"));
        if(szName.empty())
            szName = "Siteview Ecc SE Group";

        m_objRootGroup.m_nType = SiteView_ECC_SE_Group;
        m_objRootGroup.m_szName = szName;
        m_objRootGroup.m_szIndex = "0";

        GetAllSVSEInfo(selist);

        CEccTreeGroup objGroup;
        for(iSe = selist.begin(); iSe != selist.end(); iSe++)
        {
            objGroup.Reset();
            objGroup.m_szIndex = (*iSe).name;
            bHasRight = false;
            bHasRight = m_SVSEUser.haveGroupRight(objGroup.m_szIndex, SiteView_ECC_SE);
            if(bHasRight)
            {
                EnumGroups(objGroup);
                m_SVSEList[objGroup.m_szIndex] = objGroup;
            }
        }
    }

    CreateTree();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EnumGroups(CEccTreeGroup &objGroup)
{
    bool bSVSE = IsSVSEID(objGroup.m_szIndex);
    OBJECT svGroup = INVALID_VALUE;
    if(bSVSE)
        svGroup = GetSVSE(objGroup.m_szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    else
        svGroup = GetGroup(objGroup.m_szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    if(svGroup != INVALID_VALUE)
    {
        list<string> lsGroupID;
        list<string> lsDeviceID;
        list<string>::iterator lsItem;

        if(bSVSE)
            objGroup.m_nType = SiteView_ECC_SE;
        else
            objGroup.m_nType = SiteView_ECC_Group;

        if(bSVSE)
            GetSubEntitysIDBySE(svGroup, lsDeviceID);
        else
            GetSubEntitysIDByGroup(svGroup, lsDeviceID);

        objGroup.m_nDeviceCount = static_cast<int>(lsDeviceID.size());
        CEccTreeDevice objDevice;
        objDevice.m_nType = SiteView_ECC_Device;
        map<int, CEccTreeDevice, less<int> >::iterator devitem;
        bool bHasRight = false;
        for(lsItem = lsDeviceID.begin(); lsItem != lsDeviceID.end(); lsItem ++)
        {
            objDevice.Reset();
            objDevice.m_szIndex = (*lsItem);
            objDevice.m_nState = dyn_normal;
            bHasRight = false;
            bHasRight = m_SVSEUser.haveGroupRight(objDevice.m_szIndex, SiteView_ECC_Device);
            if(bHasRight)
            {
                EnumDevice(objDevice);
                objGroup.m_nMonitorCount += objDevice.m_nMonitorCount;
                objGroup.m_nDisableCount += objDevice.m_nDisableCount;
                objGroup.m_nErrorCount += objDevice.m_nErrorCount;
                objGroup.m_nWarnningCount += objDevice.m_nWarnningCount;
                devitem = objGroup.m_Devices.find(objDevice.m_nShowIndex);
                while(devitem != objGroup.m_Devices.end())
                {
                    objDevice.m_nShowIndex ++;
                    devitem = objGroup.m_Devices.find(objDevice.m_nShowIndex);
                }
                objGroup.m_Devices[objDevice.m_nShowIndex] = objDevice;
                if(objGroup.m_tRefreshTime < objDevice.m_tRefreshTime)
                    objGroup.m_tRefreshTime = objDevice.m_tRefreshTime;
            }
        }

        if(bSVSE)
            GetSubGroupsIDBySE(svGroup, lsGroupID);
        else
            GetSubGroupsIDByGroup(svGroup, lsGroupID);
    
        CEccTreeGroup   objSubGroup;
        objSubGroup.m_nType = SiteView_ECC_Group;
        map<int, CEccTreeGroup, less<int> >::iterator groupitem;

        for(lsItem = lsGroupID.begin(); lsItem != lsGroupID.end(); lsItem ++)
        {
            objSubGroup.Reset();
            objSubGroup.m_szIndex = (*lsItem);
            objSubGroup.m_nState = dyn_normal;
            bHasRight = false;
            bHasRight = m_SVSEUser.haveGroupRight(objSubGroup.m_szIndex, SiteView_ECC_Group);
            if(bHasRight)
            {
                EnumGroups(objSubGroup);
                objGroup.m_nDeviceCount += objSubGroup.m_nDeviceCount;
                objGroup.m_nMonitorCount += objSubGroup.m_nMonitorCount;
                objGroup.m_nDisableCount += objSubGroup.m_nDisableCount;
                objGroup.m_nErrorCount += objSubGroup.m_nErrorCount;
                objGroup.m_nWarnningCount += objSubGroup.m_nWarnningCount;
                groupitem = objGroup.m_SubGroups.find(objSubGroup.m_nShowIndex);
                while(groupitem != objGroup.m_SubGroups.end())
                {
                    objSubGroup.m_nShowIndex ++;
                    groupitem = objGroup.m_SubGroups.find(objSubGroup.m_nShowIndex);
                }

                if(objSubGroup.m_nErrorCount > 0)
                    objSubGroup.m_nState = dyn_error;
                else if(objSubGroup.m_nWarnningCount > 0)
                    objSubGroup.m_nState = dyn_warnning;

                objGroup.m_SubGroups[objSubGroup.m_nShowIndex] = objSubGroup;
                if(objGroup.m_tRefreshTime < objSubGroup.m_tRefreshTime)
                    objGroup.m_tRefreshTime = objSubGroup.m_tRefreshTime;
            }
        }

        if(objGroup.m_nErrorCount > 0)
            objGroup.m_nState = dyn_error;
        else if(objGroup.m_nWarnningCount > 0)
            objGroup.m_nState = dyn_warnning;

        if(bSVSE)
        {
            objGroup.m_szName = GetSVSELabel(svGroup);
            char chState[512] = {0};
            sprintf(chState, "%s%d,%s%d,%s%d,%s%d,%s%d", 
                SVResString::getResString("IDS_Device_Count").c_str(), objGroup.m_nDeviceCount,
                SVResString::getResString("IDS_Monitor_Count").c_str(), objGroup.m_nMonitorCount,
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objGroup.m_nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objGroup.m_nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objGroup.m_nWarnningCount);
            
            objGroup.m_szShowText = chState;
        }
        else
        {
            MAPNODE mainNode = GetGroupMainAttribNode(svGroup);
            if(mainNode != INVALID_VALUE)
            {
                FindNodeValue(mainNode, svName, objGroup.m_szName);
                FindNodeValue(mainNode, svDependCondition,  objGroup.m_szDepCondition);
                FindNodeValue(mainNode, svDependON,         objGroup.m_szDependsOn);
                FindNodeValue(mainNode, svDescription,      objGroup.m_szDescription);
                string szIndex("");
                FindNodeValue(mainNode, svShowIndex, szIndex);
                if(szIndex.empty())
                    objGroup.m_nShowIndex = FindIndexByID(objGroup.m_szIndex);
                else
                    objGroup.m_nShowIndex = atoi(szIndex.c_str());


                if(isObjectDisable(mainNode, objGroup.m_szState, SiteView_ECC_Group))
                    objGroup.m_nState = dyn_disable;

                char chState[512] = {0};
                sprintf(chState, "%s%s%d,%s%d,%s%d,%s%d,%s%d", 
                    objGroup.m_szState.c_str(),
                    SVResString::getResString("IDS_Device_Count").c_str(), objGroup.m_nDeviceCount,
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objGroup.m_nMonitorCount,
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objGroup.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objGroup.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objGroup.m_nWarnningCount);
                
                objGroup.m_szShowText = chState;
            }
        }

        if(bSVSE)
            CloseSVSE(svGroup);
        else
            CloseGroup(svGroup);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EnumDevice(CEccTreeDevice &objDevice)
{
    OBJECT svDevice = GetEntity(objDevice.m_szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(svDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lsItem;
        map<int, CECCMonitor, less<int> >::iterator mapitem;
        GetSubMonitorsIDByEntity(svDevice, lsMonitorID);
        objDevice.m_nMonitorCount = static_cast<int>(lsMonitorID.size());

        CECCMonitor objMonitor;       
        for(lsItem = lsMonitorID.begin(); lsItem != lsMonitorID.end(); lsItem ++)
        {
            objMonitor.m_szIndex = (*lsItem);
            EnumMonitor(objMonitor);
            mapitem = objDevice.m_Monitors.find(objMonitor.m_nShowIndex);
            while(mapitem != objDevice.m_Monitors.end())
            {
                objMonitor.m_nShowIndex ++;
                mapitem = objDevice.m_Monitors.find(objMonitor.m_nShowIndex);
            }
            objDevice.m_Monitors[objMonitor.m_nShowIndex] = objMonitor;
            if(objDevice.m_tRefreshTime < objMonitor.m_tRefreshTime)
               objDevice.m_tRefreshTime = objMonitor.m_tRefreshTime;

            switch(objMonitor.m_nState)
            {
            case dyn_no_date:
            case dyn_normal:
                break;
            case dyn_disable:
                objDevice.m_nDisableCount ++;
                break;
            case dyn_warnning:
                objDevice.m_nWarnningCount ++;
                break;
            case dyn_error:
            case dyn_bad:
                objDevice.m_nErrorCount ++;
                break;
            }
        }

        if(objDevice.m_nErrorCount > 0)
            objDevice.m_nState = dyn_error;
        else if(objDevice.m_nWarnningCount > 0)
            objDevice.m_nState = dyn_warnning;

        MAPNODE mainNode = GetEntityMainAttribNode(svDevice);
        if(mainNode != INVALID_VALUE)
        {            
            FindNodeValue(mainNode, svName,             objDevice.m_szName);
            FindNodeValue(mainNode, svOSType,           objDevice.m_szOSType);
            FindNodeValue(mainNode, svDeviceType,       objDevice.m_szRealDeviceType);
            FindNodeValue(mainNode, svDependCondition,  objDevice.m_szDepCondition);
            FindNodeValue(mainNode, svDependON,         objDevice.m_szDependsOn);
            FindNodeValue(mainNode, svDescription,      objDevice.m_szDescription);
            FindNodeValue(mainNode, svNetworkSet,       objDevice.m_szIsNetworkset);

            string szIndex("");
            FindNodeValue(mainNode, svShowIndex, szIndex);
            if(szIndex.empty())
                objDevice.m_nShowIndex = FindIndexByID(objDevice.m_szIndex);
            else
                objDevice.m_nShowIndex = atoi(szIndex.c_str());

            if(!objDevice.m_szOSType.empty())
                objDevice.m_szOSType = GetIniFileString(objDevice.m_szOSType, "description", "", "oscmd.ini");
            if(!objDevice.m_szRealDeviceType.empty())
                objDevice.m_szDeviceType = getDeviceShowType(objDevice.m_szRealDeviceType);


            if(isObjectDisable(mainNode, objDevice.m_szState, SiteView_ECC_Device))
                objDevice.m_nState = dyn_disable;
            char chState[512] = {0};
            if(!objDevice.m_szOSType.empty() && !objDevice.m_szDeviceType.empty())
            {
                sprintf(chState, "%s%s%s,%s%s,%s%d,%s%d,%s%d,%s%d",
                    objDevice.m_szState.c_str(),
                    SVResString::getResString("IDS_Device_Type").c_str(), objDevice.m_szDeviceType.c_str(),
                    SVResString::getResString("IDS_OS_Type").c_str(), objDevice.m_szOSType.c_str(),
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objDevice.m_nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objDevice.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objDevice.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objDevice.m_nWarnningCount);
            }
            else if(!objDevice.m_szDeviceType.empty())
            {
                sprintf(chState, "%s%s%s,%s%d,%s%d,%s%d,%s%d", 
                    objDevice.m_szState.c_str(),
                    SVResString::getResString("IDS_Device_Type").c_str(), objDevice.m_szDeviceType.c_str(),
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objDevice.m_nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objDevice.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objDevice.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objDevice.m_nWarnningCount);
            }
            else
            {
                sprintf(chState, "%s%s%d,%s%d,%s%d,%s%d", 
                    objDevice.m_szState.c_str(),
                    SVResString::getResString("IDS_Monitor_Count").c_str(), objDevice.m_nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objDevice.m_nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objDevice.m_nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objDevice.m_nWarnningCount);
            }
            objDevice.m_szShowText = chState;
        }
        objDevice.m_nType = SiteView_ECC_Device;
        
        CloseEntity(svDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeView::makeMenuText(int nType, string szIndex, int &nPurview)
{
    string          szMenu("");
    char            szMenus[32] = {0};

    bool bHasAddSERight = false;
    bool bHasAddGroupRight = false;
    bool bHasAddDeviceRight = false;
    bool bHasAddMonitorRight = false;

    bool bHasEditRight = false;
    
    bool bHasDelRight = false;

    bool bHasDeviceRefresh = false;

    switch(nType)
    {
    case SiteView_ECC_SE:
        bHasAddGroupRight = m_SVSEUser.haveUserRight(szIndex, "addsongroup");
        bHasAddDeviceRight = m_SVSEUser.haveUserRight(szIndex, "adddevice");
        bHasEditRight = m_SVSEUser.haveUserRight(szIndex, "se_edit");
        sprintf(szMenus, "%d%d00%d0%d000", bHasAddGroupRight, bHasAddDeviceRight, bHasEditRight, 
            bHasAddDeviceRight);
        break;
    case SiteView_ECC_Group:
        bHasDelRight = m_SVSEUser.haveUserRight(szIndex, "delgroup");
        bHasEditRight = m_SVSEUser.haveUserRight(szIndex, "editgroup");
        bHasAddGroupRight = m_SVSEUser.haveUserRight(szIndex, "addsongroup");
        bHasAddDeviceRight = m_SVSEUser.haveUserRight(szIndex, "adddevice");
        sprintf(szMenus, "%d%d0%d%d0%d%d%d0", bHasAddGroupRight, bHasAddDeviceRight, bHasEditRight, 
                bHasDelRight, bHasAddDeviceRight, bHasEditRight, bHasEditRight);
        break;
    case SiteView_ECC_Device:
        bHasDelRight = m_SVSEUser.haveUserRight(szIndex, "deldevice");
        bHasEditRight = m_SVSEUser.haveUserRight(szIndex, "editdevice");
        bHasAddMonitorRight = m_SVSEUser.haveUserRight(szIndex, "addmonitor");
        bHasDeviceRefresh  = m_SVSEUser.haveUserRight(szIndex, "devicerefresh");        
        sprintf(szMenus, "00%d%d%d%d0%d%d%d", bHasAddMonitorRight, bHasEditRight, bHasDelRight, 
            bHasEditRight, bHasEditRight, bHasEditRight, bHasDeviceRefresh);
        break;
    default:
        sprintf(szMenus, "0000000000");
        break;
    }

    if(m_SVSEUser.haveUserRight(szIndex, "se_edit"))
        nPurview = nPurview | Edit_SVSE;
    if(m_SVSEUser.haveUserRight(szIndex, "addsongroup"))
        nPurview = nPurview | Add_Group;
    if(m_SVSEUser.haveUserRight(szIndex, "adddevice"))
        nPurview = nPurview | Add_Device;
    if(m_SVSEUser.haveUserRight(szIndex, "editgroup"))
        nPurview = nPurview | Edit_Group;
    if(m_SVSEUser.haveUserRight(szIndex, "delgroup"))
        nPurview = nPurview | Delete_Group;
    if(m_SVSEUser.haveUserRight(szIndex, "addmonitor"))
        nPurview = nPurview | Add_Monitor;
    if( m_SVSEUser.haveUserRight(szIndex, "editdevice"))
        nPurview = nPurview | Edit_Group;
    if(m_SVSEUser.haveUserRight(szIndex, "deldevice"))
        nPurview = nPurview | Delete_Device;
    if(m_SVSEUser.haveUserRight(szIndex, "devicerefresh"))
        nPurview = nPurview | Refresh_Device;
    if(m_SVSEUser.haveUserRight(szIndex, "testdevice"))
        nPurview = nPurview | Test_Device;
    if(m_SVSEUser.haveUserRight(szIndex, "editmonitor"))
        nPurview = nPurview | Edit_Monitor;
    if(m_SVSEUser.haveUserRight(szIndex, "delmonitor"))
        nPurview = nPurview | Delete_Monitor;
    if(m_SVSEUser.haveUserRight(szIndex, "monitorrefresh"))
        nPurview = nPurview | Refresh_Monitor;
    szMenu = szMenus;
    return szMenu;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccTreeView::isObjectDisable(MAPNODE &mainNode, string &szState, int nType)
{
    bool bDisable = false;
    string szDisable("");
    FindNodeValue(mainNode, svDisable, szDisable);
    if(szDisable == "true")
    {
        if(nType == SiteView_ECC_Group)
            szState += SVResString::getResString("IDS_Group_Disable_Forver");
        else if(SiteView_ECC_Device)
            szState += SVResString::getResString("IDS_Device_Disable_Forver");

        szState += ",";

        bDisable =  true;
    }
    else if( szDisable == "time")
    {
        if(nType == SiteView_ECC_Group)
            szState = SVResString::getResString("IDS_Group_Disable_Temprary");
        else if(SiteView_ECC_Device)
            szState = SVResString::getResString("IDS_Device_Disable_Temprary");

        szState += ",";

        string szEndTime(""), szStartTime("");
        FindNodeValue(mainNode, svEndTime, szEndTime);
        FindNodeValue(mainNode, svStartTime, szStartTime);
        int nYear = 0, nMonth = 0, nDay = 0;
        int nHour = 0, nMinute = 0;
        if(!szStartTime.empty())
        {
            sscanf(szStartTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
            char szMsg[256] = {0};
            sprintf(szMsg, SVResString::getResString("IDS_Start_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
            szState += szMsg;
            szState += ",";
        }
        if(!szEndTime.empty())
        {
            sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
            char szMsg[256] = {0};
            sprintf(szMsg, SVResString::getResString("IDS_End_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
            szState += szMsg;
            szState += ",";   

             TTime ttime =  TTime::GetCurrentTimeEx();
             TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
            if(ttime < ttend)
                bDisable =  true;
        }
    }
    
    if(!bDisable)
        szState = "";

    return bDisable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeView::AppendDevice(const string &szIndex, const string &szName, const string &szDesc, 
                                const string &szDepends, const string &szCondition, const string &szDeviceType, 
                                const string &szOsType, const string &szIsNetworkSet)
{
    string szParentID = FindParentID(szIndex);
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szParentID);
    if(pNode)
    {
        CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
        int nType = SiteView_ECC_Device;
        int nState = dyn_normal;
        int nPurview = 0;

        string szMenus(CEccMainView::m_pTreeView->makeMenuText(nType, szIndex, nPurview));

        string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device") +
            "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + 
            pGroup->m_szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + pGroup->m_szName;

        AddOperaterLog(SV_ADD_DEVICE, SiteView_ECC_Device, szMsg);

        return pGroup->AppendDevice(szIndex, szName, szDesc, szDepends, szCondition, szDeviceType, szOsType, szIsNetworkSet, szMenus, nPurview);
    }

    return -1;
    //? 记录日志
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::BuildSEShowText(string szSEID)
{
    map<string, CEccTreeGroup, less<string> >::iterator seitem;
    seitem = CEccMainView::m_pTreeView->m_SVSEList.find(szSEID);
    if(seitem != CEccMainView::m_pTreeView->m_SVSEList.end())
        CEccMainView::m_pTreeView->UpdateGroupData(seitem->second);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::UpdateGroupData(CEccTreeGroup &objGroup)
{
    objGroup.m_nDeviceCount = 0;
    objGroup.m_nDisableCount = 0;
    objGroup.m_nErrorCount = 0;
    objGroup.m_nMonitorCount = 0;
    objGroup.m_nWarnningCount = 0;

    map<int, CEccTreeGroup, less<int> >::iterator groupitem;
    for(groupitem = objGroup.m_SubGroups.begin(); groupitem != objGroup.m_SubGroups.end(); groupitem ++)
    {
        UpdateGroupData(groupitem->second);

        objGroup.m_nDeviceCount += groupitem->second.m_nDeviceCount;
        objGroup.m_nDisableCount += groupitem->second.m_nDisableCount;
        objGroup.m_nErrorCount += groupitem->second.m_nErrorCount;
        objGroup.m_nMonitorCount += groupitem->second.m_nMonitorCount;
        objGroup.m_nWarnningCount += groupitem->second.m_nWarnningCount;
    }

    objGroup.m_nDeviceCount += static_cast<int>(objGroup.m_Devices.size());
    map<int, CEccTreeDevice, less<int> >::iterator deviceitem;
    for(deviceitem = objGroup.m_Devices.begin(); deviceitem != objGroup.m_Devices.end(); deviceitem ++)
    {
        objGroup.m_nDisableCount += deviceitem->second.m_nDisableCount;
        objGroup.m_nErrorCount += deviceitem->second.m_nErrorCount;
        objGroup.m_nMonitorCount += deviceitem->second.m_nMonitorCount;
        objGroup.m_nMonitorCount += deviceitem->second.m_nWarnningCount;

        char chState[512] = {0};
        if(!deviceitem->second.m_szOSType.empty() && !deviceitem->second.m_szDeviceType.empty())
        {
            sprintf(chState, "%s%s%s,%s%s,%s%d,%s%d,%s%d,%s%d",
                deviceitem->second.m_szState.c_str(),
                SVResString::getResString("IDS_Device_Type").c_str(), deviceitem->second.m_szDeviceType.c_str(),
                SVResString::getResString("IDS_OS_Type").c_str(), deviceitem->second.m_szOSType.c_str(),
                SVResString::getResString("IDS_Monitor_Count").c_str(), deviceitem->second.m_nMonitorCount, 
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), deviceitem->second.m_nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), deviceitem->second.m_nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), deviceitem->second.m_nWarnningCount);
        }
        else if(!deviceitem->second.m_szDeviceType.empty())
        {
            sprintf(chState, "%s%s%s,%s%d,%s%d,%s%d,%s%d", 
                deviceitem->second.m_szState.c_str(),
                SVResString::getResString("IDS_Device_Type").c_str(), deviceitem->second.m_szDeviceType.c_str(),
                SVResString::getResString("IDS_Monitor_Count").c_str(), deviceitem->second.m_nMonitorCount, 
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), deviceitem->second.m_nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), deviceitem->second.m_nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), deviceitem->second.m_nWarnningCount);
        }
        else
        {
            sprintf(chState, "%s%s%d,%s%d,%s%d,%s%d", 
                deviceitem->second.m_szState.c_str(),
                SVResString::getResString("IDS_Monitor_Count").c_str(), deviceitem->second.m_nMonitorCount, 
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), deviceitem->second.m_nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), deviceitem->second.m_nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), deviceitem->second.m_nWarnningCount);
        }
        deviceitem->second.m_szShowText = chState;        
    }

    char chState[512] = {0};
    sprintf(chState, "%s%d,%s%d,%s%d,%s%d,%s%d", 
        SVResString::getResString("IDS_Device_Count").c_str(), objGroup.m_nDeviceCount,
        SVResString::getResString("IDS_Monitor_Count").c_str(), objGroup.m_nMonitorCount,
        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), objGroup.m_nDisableCount,
        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), objGroup.m_nErrorCount, 
        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), objGroup.m_nWarnningCount);
    
    objGroup.m_szShowText = chState;

    if(objGroup.m_nErrorCount > 0)
        objGroup.m_nState = dyn_error;
    else if(objGroup.m_nWarnningCount > 0)
        objGroup.m_nState = dyn_disable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeView::AppendGroup(const string &szIndex, const string &szName, const string &szDesc, 
                               const string &szDepends, const string &szCondition)
{
    string szParentID = FindParentID(szIndex);
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szParentID);
    if(pNode)
    {
        CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
        int nType = SiteView_ECC_Group;
        int nState = dyn_normal;
        int nPurview = 0;

        string szMenus(CEccMainView::m_pTreeView->makeMenuText(nType, szIndex, nPurview));

        string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Group") +
            "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + 
            pGroup->m_szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + pGroup->m_szName;

        AddOperaterLog(SV_ADD_GROUP, SiteView_ECC_Group, szMsg);
        //? 记录日志
        return pGroup->AppendGroup(szIndex, szName, szDesc, szDepends, szCondition, szMenus, nPurview);
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccTreeView::isCurrentChildEdit(const string &szIndex)
{
    string szParentID = FindParentID(szIndex);
    while(szParentID.empty())
    {
        if(szParentID == m_szCurSelIndex)
            return true;

        szParentID = FindParentID(szParentID);
        if(IsSVSEID(szParentID))
            break;
    }

    if(szParentID == m_szCurSelIndex)
        return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccTreeView::isCurrentPathEdit(const string &szIndex)
{
    if(m_szCurSelIndex == szIndex)
        return true;

    string szParent = FindParentID(m_szCurSelIndex);
    while(!szParent.empty())
    {
        if(szParent == szIndex)
            return true;

        szParent = FindParentID(szParent);
        if(IsSVSEID(szParent))
            break;
    }

    if(szParent == szIndex)
        return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EditSVSE(const string &szIndex, const string &szName)
{
    map<string, CEccTreeGroup, less<string> >::iterator seitem = CEccMainView::m_pTreeView->m_SVSEList.find(szIndex);
    if(seitem != CEccMainView::m_pTreeView->m_SVSEList.end())
    {
        string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_SE") +
                    "(Index)" + szIndex + "---(old)" + SVResString::getResString("IDS_Name") + ":" 
                    + seitem->second.m_szName + "---(new)" + SVResString::getResString("IDS_Name") + ":" + szName;

        AddOperaterLog(SV_EDIT, SiteView_ECC_SE, szMsg);

        seitem->second.m_szName = szName;
        if(seitem->second.m_pTreeText)
            seitem->second.m_pTreeText->setText(szName);
    }

    if(CEccMainView::m_pTreeView->isCurrentPathEdit(szIndex))
    {
        PrintDebugString("Current Path is Edited");
        const CEccTreeNode *pCurNode = CEccMainView::m_pTreeView->getECCObject(CEccMainView::m_pTreeView->m_szCurSelIndex);
        if(pCurNode)
            CEccMainView::m_pRightView->UpdateData(pCurNode);
    }
    //? 记录日志
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::DeleteDeviceByID(const string &szDeviceID)
{
    //? delete all monitor of this device
    list<string> lstMonitors;
    list<string>::iterator lstItem;
    OBJECT entity = GetEntity(szDeviceID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if (entity != INVALID_VALUE)
    {
        if(GetSubMonitorsIDByEntity(entity, lstMonitors))
        {
            for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
            {
                DeleteSVMonitor((*lstItem), CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                DeleteTable((*lstItem), CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            }
        }
        CloseEntity(entity);
    }

    DeleteEntity(szDeviceID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    //? 记录日志

    string szParentID(FindParentID(szDeviceID));
    const CEccTreeNode *pNode = getECCObject(szParentID);
    if(pNode)
    {
        CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));

        map<int, CEccTreeDevice, less<int> >::iterator devitem;
        for(devitem = pGroup->m_Devices.begin(); devitem != pGroup->m_Devices.end(); devitem ++)
        {
            if(devitem->second.m_szIndex == szDeviceID)
            {
                string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Group") +
                        "(Index)" + szDeviceID + "---" + SVResString::getResString("IDS_Name") + ":" + devitem->second.m_szName + 
                        "---parent id is " + pGroup->m_szIndex + "---" + SVResString::getResString("IDS_Name") +
                        ":" + pGroup->m_szName;

                AddOperaterLog(SV_DELETE, SiteView_ECC_Device, szMsg);

                if(devitem->second.m_pTreeText)
                    pGroup->m_pDevicesTable->deleteRow(static_cast<WTableCell*>(devitem->second.m_pTreeText->parent())->row());
                pGroup->m_Devices.erase(devitem);
                break;
            }
        }

        if(pGroup->m_Devices.empty() && pGroup->m_SubGroups.empty() && pGroup->m_pImageExpand)
            pGroup->m_pImageExpand->setImageRef("../Images/space.gif");
    }



    CEccMainView::m_pTreeView->BuildSEShowText(FindSEID(szDeviceID));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::DeleteGroupByID(const string &szGroupID)
{
    //? delete all sub groups and device of this group
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;

    OBJECT objGroup = GetGroup(szGroupID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objGroup != INVALID_VALUE)
    {
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // 删除每一个设备
        if(GetSubEntitysIDByGroup(objGroup, lsEntityID))
        {
            for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                DeleteDeviceByID((*lstItem));
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // 删除每一个子组
        if(GetSubGroupsIDByGroup(objGroup, lsGroupID))
        {
            for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                DeleteGroupByID((*lstItem));
        }

        CloseGroup(objGroup);

        //? 记录日志

        DeleteGroup(szGroupID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

        string szParentID(FindParentID(szGroupID));
        const CEccTreeNode *pNode = getECCObject(szParentID);
        if(pNode)
        {
            CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));


            map<int, CEccTreeGroup, less<int> >::iterator groupitem;
            for(groupitem = pGroup->m_SubGroups.begin(); groupitem != pGroup->m_SubGroups.end(); groupitem ++)
            {
                if(groupitem->second.m_szIndex == szGroupID)
                {
                    string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Group") +
                        "(Index)" + szGroupID + "---" + SVResString::getResString("IDS_Name") + ":" + groupitem->second.m_szName + 
                        "---parent id is " + pGroup->m_szIndex + "---" + SVResString::getResString("IDS_Name") +
                        ":" + pGroup->m_szName;

                    AddOperaterLog(SV_DELETE, SiteView_ECC_Group, szMsg);

                    if(groupitem->second.m_pTreeText)
                        pGroup->m_pSubGroupsTable->deleteRow(static_cast<WTableCell*>(groupitem->second.m_pTreeText->parent())->row());
                    if(groupitem->second.m_pSubGroupsTable)
                        pGroup->m_pSubGroupsTable->deleteRow(static_cast<WTableCell*>(groupitem->second.m_pSubGroupsTable->parent())->row());
                    if(groupitem->second.m_pDevicesTable)
                        pGroup->m_pSubGroupsTable->deleteRow(static_cast<WTableCell*>(groupitem->second.m_pDevicesTable->parent())->row());
                    pGroup->m_SubGroups.erase(groupitem);
                    break;
                }
            }

            if(pGroup->m_Devices.empty() && pGroup->m_SubGroups.empty() && pGroup->m_pImageExpand)
                pGroup->m_pImageExpand->setImageRef("../Images/space.gif");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EditDevice(const string & szIndex, const string & szName, const string & szDesc, 
                             const string & szDepends, const string & szCondition)
{
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szIndex);
    if(pNode)
    {
        string szOldName(pNode->m_szName);
        CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
        pDevice->m_szDependsOn = szDepends;
        pDevice->m_szDescription = szDesc;
        pDevice->m_szDepCondition = szCondition;
        pDevice->m_szName = szName;
        if(pDevice->m_pTreeText)
            pDevice->m_pTreeText->setText(szName);

        if(CEccMainView::m_pTreeView->m_szCurSelIndex == FindParentID(szIndex))
        {
            const CEccTreeNode *pParent = CEccTreeView::getECCObject(CEccMainView::m_pTreeView->m_szCurSelIndex);
            if(pParent)
            {
                CEccMainView::m_pRightView->changeActive(pParent);

                string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Device") +
                    "(Index)" + szIndex + "---(old)" + SVResString::getResString("IDS_Name") + ":" + szOldName + 
                    "---(new)" + SVResString::getResString("IDS_Name") + ":" + szName +
                    "---parent id is " + pParent->m_szIndex + "---" + SVResString::getResString("IDS_Name") +
                    ":" + pParent->m_szName;

                AddOperaterLog(SV_EDIT, SiteView_ECC_Device, szMsg);
            }
        }
    }
    if(CEccMainView::m_pTreeView->isCurrentPathEdit(szIndex))
    {
        PrintDebugString("Current Path is Edited");
        const CEccTreeNode *pCurNode = CEccMainView::m_pTreeView->getECCObject(CEccMainView::m_pTreeView->m_szCurSelIndex);
        if(pCurNode)
            CEccMainView::m_pRightView->UpdateData(pCurNode);
    }
    //? 记录日志
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EditGroup(const string & szIndex, const string & szName, const string & szDesc, 
                             const string & szDepends, const string & szCondition)
{
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szIndex);
    if(pNode)
    {
        string szOldName(pNode->m_szName);
        CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
        pGroup->m_szDependsOn = szDepends;
        pGroup->m_szDescription = szDesc;
        pGroup->m_szDepCondition = szCondition;
        pGroup->m_szName = szName;
        if(pGroup->m_pTreeText)
            pGroup->m_pTreeText->setText(szName);

        if(CEccMainView::m_pTreeView->m_szCurSelIndex == FindParentID(szIndex))
        {
            const CEccTreeNode *pParent = CEccTreeView::getECCObject(CEccMainView::m_pTreeView->m_szCurSelIndex);
            if(pParent)
            {
                CEccMainView::m_pRightView->changeActive(pParent);

                string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Group") +
                    "(Index)" + szIndex + "---(old)" + SVResString::getResString("IDS_Name") + ":" + szOldName + 
                    "---(new)" + SVResString::getResString("IDS_Name") + ":" + szName + 
                    "---parent id is " + pParent->m_szIndex + "---" + SVResString::getResString("IDS_Name") +
                    ":" + pParent->m_szName;

                AddOperaterLog(SV_EDIT, SiteView_ECC_Group, szMsg);
            }
        }
    }
    if(CEccMainView::m_pTreeView->isCurrentPathEdit(szIndex))
    {
        PrintDebugString("Current Path is Edited");
        const CEccTreeNode *pCurNode = CEccMainView::m_pTreeView->getECCObject(CEccMainView::m_pTreeView->m_szCurSelIndex);
        if(pCurNode)
            CEccMainView::m_pRightView->UpdateData(pCurNode);
    }
    //? 记录日志
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CEccTreeView::getSVSECount()
{
    return static_cast<int>(CEccMainView::m_pTreeView->m_SVSEList.size());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const map<string, CEccTreeGroup, less<string> > &CEccTreeView::getSEList()
{
    return CEccMainView::m_pTreeView->m_SVSEList;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::MakePath(const string &szIndex, PAIRLIST &lsPath)
{
    stack<string> stIndex;
    string szParentID = FindParentID(szIndex);
    while(!IsSVSEID(szParentID))
    {
        stIndex.push(szParentID);
        szParentID = FindParentID(szParentID);
    }

    map<int, CEccTreeGroup, less<int> >::iterator subgroupitem, groupitem;
    map<int, CEccTreeDevice, less<int> >::iterator devitem;
    map<string, CEccTreeGroup, less<string> >::iterator seitem;
    
    sv_pair svitem;
    seitem = CEccMainView::m_pTreeView->m_SVSEList.find(szParentID);
    if(seitem != CEccMainView::m_pTreeView->m_SVSEList.end())
    {
        if(seitem->second.m_szIndex == szIndex)
        {
            svitem.name = szIndex;
            svitem.value = seitem->second.m_szName;
            lsPath.push_back(svitem);
        }
        else
        {
            svitem.name = szParentID;
            svitem.value = seitem->second.m_szName;
            lsPath.push_back(svitem);

            if(stIndex.empty())
            {
                for(devitem = (*seitem).second.m_Devices.begin(); devitem != (*seitem).second.m_Devices.end(); devitem ++)
                {
                    if((*devitem).second.m_szIndex == szIndex)
                    {
                        svitem.name = szIndex;
                        svitem.value = devitem->second.m_szName;
                        lsPath.push_back(svitem);

                        return;
                    }
                }

                for(groupitem = (*seitem).second.m_SubGroups.begin(); groupitem != (*seitem).second.m_SubGroups.end();
                        groupitem ++)
                {
                    if((*groupitem).second.m_szIndex == szIndex)
                    {
                        svitem.name = szIndex;
                        svitem.value = groupitem->second.m_szName;
                        lsPath.push_back(svitem);
                        return ;
                    }
                }
            }
            else
            {
                szParentID = stIndex.top();
                stIndex.pop();
                for(groupitem = (*seitem).second.m_SubGroups.begin(); groupitem != (*seitem).second.m_SubGroups.end();
                        groupitem ++)
                {
                    if((*groupitem).second.m_szIndex == szParentID)
                    {
                        svitem.name = szParentID;
                        svitem.value = groupitem->second.m_szName;
                        lsPath.push_back(svitem);
                        break;
                    }
                }

                while(!stIndex.empty())
                {
                    szParentID = stIndex.top();
                    stIndex.pop();
                    for(subgroupitem = (*groupitem).second.m_SubGroups.begin(); subgroupitem != (*groupitem).second.m_SubGroups.end();
                            subgroupitem ++)
                    {
                        if((*subgroupitem).second.m_szIndex == szParentID)
                        {
                            groupitem = subgroupitem;

                            svitem.name = szParentID;
                            svitem.value = subgroupitem->second.m_szName;
                            lsPath.push_back(svitem);

                            break;
                        }
                    }
                }
                
                szParentID = FindParentID(szIndex);
                if(CEccTreeView::getECCObject(szParentID)->m_nType == SiteView_ECC_Device)
                {
                    for(devitem = (*groupitem).second.m_Devices.begin(); devitem != (*groupitem).second.m_Devices.end(); devitem ++)
                    {
                        if((*devitem).second.m_szIndex == szParentID)
                        {
                            svitem.name = szParentID;
                            svitem.value = devitem->second.m_szName;
                            lsPath.push_back(svitem);
                            
                            map<int, CECCMonitor, less<int> >::iterator monitoritem;
                            for(monitoritem = devitem->second.m_Monitors.begin(); monitoritem != devitem->second.m_Monitors.end();
                                monitoritem ++)
                            {
                                if(monitoritem->second.m_szIndex == szIndex)
                                {
                                    svitem.name = szIndex;
                                    svitem.value = monitoritem->second.m_szName;
                                    lsPath.push_back(svitem);

                                    break;
                                }
                            }
                            return;
                        }
                    }
                }

                for(devitem = (*groupitem).second.m_Devices.begin(); devitem != (*groupitem).second.m_Devices.end(); devitem ++)
                {
                    if((*devitem).second.m_szIndex == szIndex)
                    {
                        svitem.name = szIndex;
                        svitem.value = devitem->second.m_szName;
                        lsPath.push_back(svitem);

                        return;
                    }
                }

                for(subgroupitem = (*groupitem).second.m_SubGroups.begin(); subgroupitem != (*groupitem).second.m_SubGroups.end();
                        subgroupitem ++)
                {
                    if((*subgroupitem).second.m_szIndex == szIndex)
                    {
                        svitem.value = subgroupitem->second.m_szName;
                        svitem.name = szIndex;
                        lsPath.push_back(svitem);

                        return;                    
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CEccTreeNode * CEccTreeView::getECCObject(const string &szIndex)
{
    CEccTreeNode *pNode = NULL;
    stack<string> stIndex;
    string szParentID = FindParentID(szIndex);
    while(!IsSVSEID(szParentID))
    {
        stIndex.push(szParentID);
        szParentID = FindParentID(szParentID);
    }

    map<int, CEccTreeGroup, less<int> >::iterator subgroupitem, groupitem;
    map<int, CEccTreeDevice, less<int> >::iterator devitem;
    map<string, CEccTreeGroup, less<string> >::iterator seitem;

    seitem = CEccMainView::m_pTreeView->m_SVSEList.find(szParentID);
    if(seitem != CEccMainView::m_pTreeView->m_SVSEList.end())
    { 
        if(seitem->second.m_szIndex == szIndex)
        {
            pNode = static_cast<CEccTreeNode*>(&(*seitem).second);
            return pNode;
        }
        else
        {
            if(stIndex.empty())
            {
                for(devitem = (*seitem).second.m_Devices.begin(); devitem != (*seitem).second.m_Devices.end(); devitem ++)
                {
                    if((*devitem).second.m_szIndex == szIndex)
                    {
                        pNode = static_cast<CEccTreeNode*>(&(*devitem).second);
                        return pNode;
                    }
                }

                for(groupitem = (*seitem).second.m_SubGroups.begin(); groupitem != (*seitem).second.m_SubGroups.end();
                        groupitem ++)
                {
                    if((*groupitem).second.m_szIndex == szIndex)
                    {
                        pNode = static_cast<CEccTreeNode*>(&(*groupitem).second);
                        return pNode;
                    }
                }
            }
            else
            {
                szParentID = stIndex.top();
                stIndex.pop();
                for(groupitem = (*seitem).second.m_SubGroups.begin(); groupitem != (*seitem).second.m_SubGroups.end();
                        groupitem ++)
                    if((*groupitem).second.m_szIndex == szParentID)
                        break;

                if(groupitem != (*seitem).second.m_SubGroups.end())
                {
                    while(!stIndex.empty())
                    {
                        szParentID = stIndex.top();
                        stIndex.pop();
                        for(subgroupitem = (*groupitem).second.m_SubGroups.begin(); subgroupitem != (*groupitem).second.m_SubGroups.end();
                                subgroupitem ++)
                        {
                            if((*subgroupitem).second.m_szIndex == szParentID)
                            {
                                groupitem = subgroupitem;
                                break;
                            }
                        }
                    }

                    for(devitem = (*groupitem).second.m_Devices.begin(); devitem != (*groupitem).second.m_Devices.end(); devitem ++)
                    {
                        if((*devitem).second.m_szIndex == szIndex)
                        {
                            pNode = static_cast<CEccTreeNode*>(&(*devitem).second);
                            return pNode;
                        }
                    }

                    for(subgroupitem = (*groupitem).second.m_SubGroups.begin(); subgroupitem != (*groupitem).second.m_SubGroups.end();
                            subgroupitem ++)
                    {
                        if((*subgroupitem).second.m_szIndex == szIndex)
                        {
                            pNode = static_cast<CEccTreeNode*>(&(*subgroupitem).second);
                            return pNode;
                        }
                    }
                }
            }
        }
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccTreeView::getDeviceShowType(const string &szDeviceType)
{
    string szName ("");
    map<string, string, less<string> >::iterator item;
    
    item = m_DevType.find(szDeviceType);
    if(item != m_DevType.end())
    {
        szName = (*item).second;
    }
    else
    {
        OBJECT objDevice = GetEntityTemplet(szDeviceType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(objDevice != INVALID_VALUE)
        {
            MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
            if(node != INVALID_VALUE)
            {
                if(!FindNodeValue(node, svLabel, szName))
                    FindNodeValue(node, svName, szName);
                else
                    szName = SVResString::getResString(szName.c_str());
            }

            list<int> lsMTID;
            // 得到设备能使用的监测器模板列表
            if(GetSubMonitorTypeByET(objDevice, lsMTID))
                this->m_DevMTList[szDeviceType] = lsMTID;

            m_DevType[szDeviceType] = szName;

            CloseEntityTemplet(objDevice);
        }
    }
    return szName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::EnumMonitor(CECCMonitor &objMonitor)
{
    OBJECT svMonitor = GetMonitor(objMonitor.m_szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(svMonitor != INVALID_VALUE)
    {
        MAPNODE mainNode = GetMonitorMainAttribNode(svMonitor);
        
        if(mainNode != INVALID_VALUE)
        {
            string szIndex(""), szMTID;
            FindNodeValue(mainNode, svShowIndex, szIndex);
            FindNodeValue(mainNode, svMonitorType, szMTID);
            if(szIndex.empty())
                objMonitor.m_nShowIndex = FindIndexByID(objMonitor.m_szIndex);
            else
                objMonitor.m_nShowIndex = atoi(szIndex.c_str());

            objMonitor.m_nMTID = atoi(szMTID.c_str());

            FindNodeValue(mainNode, svName, objMonitor.m_szName);
        }

        getMonitorState(objMonitor);

        CloseMonitor(svMonitor);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::getMonitorState(CECCMonitor &objMonitor)
{
    sv_dyn dyn ;
    if(GetSVDYN(objMonitor.m_szIndex, dyn, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
    {
        objMonitor.m_nState = dyn.m_state;
        
        if(dyn.m_displaystr)
            objMonitor.m_szShowText = dyn.m_displaystr;

        objMonitor.m_tRefreshTime = dyn.m_time;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CECCMonitor::CECCMonitor():
m_nShowIndex(0),
m_nState(0),
m_szIndex(""),
m_szName(""),
m_szShowText("")
{
    m_tRefreshTime =  TTime::GetCurrentTimeEx();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CECCMonitor::~CECCMonitor()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CECCMonitor::getECCIndex() const
{
    return m_szIndex;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CECCMonitor::getMTID()  const
{
    return m_nMTID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CECCMonitor::getName() const
{
    return m_szName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  CECCMonitor::getShowIndex() const
{
    return m_nShowIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CECCMonitor::getShowText() const
{
    return m_szShowText;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CECCMonitor::getShowTime() const
{
    return m_tRefreshTime.Format();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CECCMonitor::getState() const
{
    return m_nState;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::CreateTree()
{
    if(m_pTree)
    {
        int nRow = m_pTree->numRows();
        if(m_objRootGroup.m_nType == SiteView_ECC_SE)
        {
            map<string, CEccTreeGroup, less<string> >::iterator seitem;
            for(seitem = m_SVSEList.begin(); seitem != m_SVSEList.end(); seitem ++)
            {
                CreateSubGroups(seitem->second, m_pTree);
            }
        }
        else
        {
            m_objRootGroup.m_pImageExpand = new WImage("../Images/cb1-fold.gif", m_pTree->elementAt(nRow, 0));
            m_objRootGroup.m_pImgType = new WImage("../Images/cbb-1globe.gif", m_pTree->elementAt(nRow, 1));
            m_objRootGroup.m_pTreeText = new WText(m_objRootGroup.m_szName, m_pTree->elementAt(nRow, 1));

            //strcpy(m_pTree->elementAt(nRow, 0)->contextmenu_, "class='padding_right_2' width=14px");
            m_pTree->elementAt(nRow, 0)->setStyleClass("width14");
            m_pTree->elementAt(nRow, 1)->setStyleClass("padding_right_2");
            if(m_objRootGroup.m_pTreeText)
            {
                strcpy(m_objRootGroup.m_pTreeText->contextmenu_, "onclick='SetCurfocus(\"0\")' onmouseover='mouseover(this)' "
                    "onmouseout='mouseout(this)'");
                m_pCurSel = m_objRootGroup.m_pTreeText;
            }

            m_objRootGroup.m_pSubGroupsTable = new WTable(m_pTree->elementAt(nRow + 1, 1));
            if(m_objRootGroup.m_pSubGroupsTable)
                m_objRootGroup.m_pSubGroupsTable->setStyleClass("widthauto");

            if(m_objRootGroup.m_pImageExpand && m_objRootGroup.m_pSubGroupsTable)
            {
                string szContext = "onclick='treenodeclick(this, \"" + m_objRootGroup.m_pSubGroupsTable->formName()
                    + "\", \"\")' style='cursor:pointer'";
                strcpy(m_objRootGroup.m_pImageExpand->contextmenu_, szContext.c_str());
            }

            if(m_objRootGroup.m_pSubGroupsTable)
            {
                map<string, CEccTreeGroup, less<string> >::iterator seitem;
                for(seitem = m_SVSEList.begin(); seitem != m_SVSEList.end(); seitem ++)
                {
                    CreateSubGroups(seitem->second, m_objRootGroup.m_pSubGroupsTable);
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::CreateSubGroups(CEccTreeGroup &objGroup, WTable *pSubTable)
{
    int nRow = pSubTable->numRows();

    map<int, CEccTreeDevice, less<int> >::iterator device;
    map<int, CEccTreeGroup, less<int> >::iterator group;

    objGroup.m_pImageExpand = new WImage("../Images/cb1-fold.gif", pSubTable->elementAt(nRow, 0));
    if(IsSVSEID(objGroup.m_szIndex))
        objGroup.m_pImgType = new WImage("../Images/cbb-2main.gif", pSubTable->elementAt(nRow, 1));
    else
    {
        string szImgState("../Images/cbb-3group");
        if(objGroup.m_nState == dyn_error)
            szImgState += "_r";
        else if(objGroup.m_nState == dyn_warnning)
            szImgState += "_y";

        szImgState += ".gif";

        objGroup.m_pImgType = new WImage(szImgState, pSubTable->elementAt(nRow, 1));
    }

    //strcpy(pSubTable->elementAt(nRow, 0)->contextmenu_, "class='padding_right_2' width=14px");
    pSubTable->elementAt(nRow, 0)->setStyleClass("width14");
    pSubTable->elementAt(nRow, 1)->setStyleClass("padding_right_2");

    objGroup.m_pTreeText = new WText(objGroup.m_szName, pSubTable->elementAt(nRow, 1));
    if(objGroup.m_pTreeText)
    {
        string szMenus(makeMenuText(objGroup.m_nType, objGroup.m_szIndex, objGroup.m_nPurview));
        sprintf(objGroup.m_pTreeText->contextmenu_, "onclick='SetCurfocus(\"%s\")' onmouseover='mouseover(this)' "
            "onmouseout='mouseout(this)' oncontextmenu='showPopMenu(\"%s\", \"%s\");'", objGroup.m_szIndex.c_str(),
            objGroup.m_szIndex.c_str(), szMenus.c_str());
        objGroup.m_pTreeText->setStyleClass("treelink");
    }

    objGroup.m_pSubGroupsTable = new WTable(pSubTable->elementAt(nRow + 1, 1));
    objGroup.m_pDevicesTable = new WTable(pSubTable->elementAt(nRow + 2, 1));        

    if(objGroup.m_pImageExpand && objGroup.m_Devices.empty() && objGroup.m_SubGroups.empty())
    {
        objGroup.m_pImageExpand->setImageRef("../Images/space.gif");
    }

    if(objGroup.m_pImageExpand && objGroup.m_pSubGroupsTable && objGroup.m_pDevicesTable)
    {
        objGroup.m_pDevicesTable->setStyleClass("widthauto");
        objGroup.m_pSubGroupsTable->setStyleClass("widthauto");

        string szContext = "onclick='treenodeclick(this, \"" + objGroup.m_pSubGroupsTable->formName()
            + "\", \"" + objGroup.m_pDevicesTable->formName() + "\")' style='cursor:pointer'";
        strcpy(objGroup.m_pImageExpand->contextmenu_, szContext.c_str());

        for(group = objGroup.m_SubGroups.begin(); group != objGroup.m_SubGroups.end(); group ++)
            CreateSubGroups(group->second, objGroup.m_pSubGroupsTable);

        int nDevRow = objGroup.m_pDevicesTable->numRows();
        for(device = objGroup.m_Devices.begin(); device != objGroup.m_Devices.end(); device ++)
        {
            new WImage("../Images/space.gif", objGroup.m_pDevicesTable->elementAt(nDevRow, 0));
            if(device->second.m_szIsNetworkset == "true")
            {
                string szImgState("../Images/cbb-5router");
                if(device->second.m_nState == dyn_error)
                    szImgState += "_r";
                else if(device->second.m_nState == dyn_warnning)
                    szImgState += "_y";

                szImgState += ".gif";
                
                device->second.m_pImgType = new WImage(szImgState, objGroup.m_pDevicesTable->elementAt(nDevRow, 1));
            }
            else
            {
                string szImgState("../Images/cbb-4server");
                if(device->second.m_nState == dyn_error)
                    szImgState += "_r";
                else if(device->second.m_nState == dyn_warnning)
                    szImgState += "_y";

                szImgState += ".gif";

                device->second.m_pImgType = new WImage(szImgState, objGroup.m_pDevicesTable->elementAt(nDevRow, 1));
            }


            device->second.m_pTreeText = new WText(device->second.m_szName, objGroup.m_pDevicesTable->elementAt(nDevRow, 1));
            if(device->second.m_pTreeText)
            {
                string szMenus(makeMenuText(device->second.m_nType, device->second.m_szIndex, device->second.m_nPurview));
                sprintf(device->second.m_pTreeText->contextmenu_, "onclick='SetCurfocus(\"%s\")' onmouseover='mouseover(this)' "
                    "onmouseout='mouseout(this)' oncontextmenu='showPopMenu(\"%s\", \"%s\");'", device->second.m_szIndex.c_str(),
                    device->second.m_szIndex.c_str(), szMenus.c_str());
                device->second.m_pTreeText->setStyleClass("treelink");
            }

            //strcpy(objGroup.m_pDevicesTable->elementAt(nRow, 0)->contextmenu_, "class='padding_right_2' width=14px");
            objGroup.m_pDevicesTable->elementAt(nDevRow, 0)->setStyleClass("width14");
            objGroup.m_pDevicesTable->elementAt(nDevRow, 1)->setStyleClass("padding_right_2");

            nDevRow ++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::ReCreateTreeNode(const string &szIndex)
{
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(szIndex);
    if(pNode)
    {
        if(pNode->m_nType == SiteView_ECC_Device)
        {
            CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
            pDevice->m_Monitors.clear();
            pDevice->m_nMonitorCount = 0;
            pDevice->m_nDisableCount = 0;
            pDevice->m_nErrorCount = 0;
            pDevice->m_nWarnningCount = 0;
            pDevice->m_nState = dyn_normal;

            CEccMainView::m_pTreeView->EnumDevice((*pDevice));

            if(pDevice->m_szIsNetworkset == "true")
            {
                string szImgState("../Images/cbb-5router");
                if(pDevice->m_nState == dyn_error)
                    szImgState += "_r";
                else if(pDevice->m_nState == dyn_warnning)
                    szImgState += "_y";

                szImgState += ".gif";
                if(pDevice->m_pImgType)
                    pDevice->m_pImgType->setImageRef(szImgState);
            }
            else
            {
                string szImgState("../Images/cbb-4server");
                if(pDevice->m_nState == dyn_error)
                    szImgState += "_r";
                else if(pDevice->m_nState == dyn_warnning)
                    szImgState += "_y";

                szImgState += ".gif";

                if(pDevice->m_pImgType)
                    pDevice->m_pImgType->setImageRef(szImgState);
            }
        }
        else if(pNode->m_nType == SiteView_ECC_Group || pNode->m_nType == SiteView_ECC_SE)
        {
            CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));
            if(pGroup->m_pSubGroupsTable)
                pGroup->m_pSubGroupsTable->clear();

            if(pGroup->m_pDevicesTable)
                pGroup->m_pDevicesTable->clear();

            pGroup->m_Devices.clear();
            pGroup->m_SubGroups.clear();

            pGroup->m_nDeviceCount = 0;
            pGroup->m_nMonitorCount = 0;
            pGroup->m_nDisableCount = 0;
            pGroup->m_nErrorCount = 0;
            pGroup->m_nWarnningCount = 0;
            pGroup->m_nState = dyn_normal;

            CEccMainView::m_pTreeView->EnumGroups((*pGroup));

            if(pGroup->m_nType == SiteView_ECC_Group && pGroup->m_pImgType)
            {
                string szImgState("../Images/cbb-3group");
                if(pGroup->m_nState == dyn_error)
                    szImgState += "_r";
                else if(pGroup->m_nState == dyn_warnning)
                    szImgState += "_y";

                szImgState += ".gif";

                pGroup->m_pImgType->setImageRef(szImgState);
            }

            map<int, CEccTreeDevice, less<int> >::iterator device;
            map<int, CEccTreeGroup, less<int> >::iterator group;
            if(pGroup->m_pSubGroupsTable)
            {
                for(group = pGroup->m_SubGroups.begin(); group != pGroup->m_SubGroups.end(); group ++)
                    CEccMainView::m_pTreeView->CreateSubGroups(group->second, pGroup->m_pSubGroupsTable);
            }

            if(pGroup->m_pDevicesTable)
            {
                int nDevRow = pGroup->m_pDevicesTable->numRows();
                for(device = pGroup->m_Devices.begin(); device != pGroup->m_Devices.end(); device ++)
                {
                    pGroup->m_pDevicesTable->elementAt(nDevRow, 0)->setStyleClass("width14");
                    if(device->second.m_szIsNetworkset == "true")
                    {
                        string szImgState("../Images/cbb-5router");
                        if(device->second.m_nState == dyn_error)
                            szImgState += "_r";
                        else if(device->second.m_nState == dyn_warnning)
                            szImgState += "_y";

                        szImgState += ".gif";
                        
                        device->second.m_pImgType = new WImage(szImgState, pGroup->m_pDevicesTable->elementAt(nDevRow, 1));
                    }
                    else
                    {
                        string szImgState("../Images/cbb-4server");
                        if(device->second.m_nState == dyn_error)
                            szImgState += "_r";
                        else if(device->second.m_nState == dyn_warnning)
                            szImgState += "_y";

                        szImgState += ".gif";

                        device->second.m_pImgType = new WImage(szImgState, pGroup->m_pDevicesTable->elementAt(nDevRow, 1));
                    }

                    device->second.m_pTreeText = new WText(device->second.m_szName, pGroup->m_pDevicesTable->elementAt(nDevRow, 1));
                    if(device->second.m_pTreeText)
                    {
                        string szMenus(CEccMainView::m_pTreeView->makeMenuText(device->second.m_nType, 
                            device->second.m_szIndex, device->second.m_nPurview));

                        sprintf(device->second.m_pTreeText->contextmenu_, "onclick='SetCurfocus(\"%s\")' onmouseover='mouseover(this)' "
                            "onmouseout='mouseout(this)' oncontextmenu='showPopMenu(\"%s\", \"%s\");'", device->second.m_szIndex.c_str(),
                            device->second.m_szIndex.c_str(), szMenus.c_str());
                        device->second.m_pTreeText->setStyleClass("treelink");
                    }

                    nDevRow ++;
                }
            }
        }

        CEccMainView::m_pTreeView->BuildSEShowText(FindSEID(szIndex));

        if(CEccMainView::m_pTreeView->m_szCurSelIndex == szIndex)
            CEccMainView::m_pRightView->changeActive(pNode);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::InsertDevMTList(const string &szDTType, const list<int> &lsMT)
{
    m_DevMTList[szDTType] = lsMT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::GetDevMTList(const string &szDTType, list<int> &lsMTID)
{
    map<string, list<int>, less<string> >::iterator it;
    it = m_DevMTList.find(szDTType);
    if(it != m_DevMTList.end())
    {
        list<int>::iterator mtid;
        for(mtid = it->second.begin(); mtid != it->second.end(); mtid++)
            lsMTID.push_back((*mtid));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::setLeftResizeName(const string &szLeftName)
{
    if(m_pHideOpt)
        sprintf(m_pHideOpt->contextmenu_, "onclick='hideleft(\"%s\")'", szLeftName.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccTreeView::AddOperaterLog(int nOperateType, int nObjectType, const string &szOperateMsg)
{
    string szOperateType(""), szObjectType("");

     TTime curTime =  TTime::GetCurrentTimeEx();

    switch(nOperateType)
    {
    case SV_ADD_GROUP:
    case SV_ADD_DEVICE:
    case SV_ADD_MONITOR:
        szOperateType = SVResString::getResString("IDS_Add_Title");
        break;
    case SV_EDIT:
        szOperateType = SVResString::getResString("IDS_Edit");
        break;
    case SV_DELETE:
        szOperateType = SVResString::getResString("IDS_Delete");
        break;
    }

    switch(nObjectType)
    {
    case SiteView_ECC_SE:
        szObjectType = SVResString::getResString("IDS_SE");
        break;
    case SiteView_ECC_Group:
        szObjectType = SVResString::getResString("IDS_Group");
        break;
    case SiteView_ECC_Device:
        szObjectType = SVResString::getResString("IDS_Device");
        break;
    case SiteView_ECC_Monitor:
        szObjectType = SVResString::getResString("IDS_Monitor_Title");
        break;
    }

    InsertTable(SV_USER_OPERATE_LOG_TABLE,  803);

    m_OperateLog.InsertOperateRecord(SV_USER_OPERATE_LOG_TABLE, m_SVSEUser.getUserID(), 
            curTime.Format(), szOperateType, szObjectType, szOperateMsg);
}


// end file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

