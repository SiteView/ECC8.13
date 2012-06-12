#include "sortlist.h"
#include "rightview.h"
#include "resstring.h"
#include "basedefine.h"
#include "treeview.h"
#include "debuginfor.h"
#include "mainview.h"
#include "listtable.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccSortTable::CEccSortTable(WContainerWidget *parent):
CEccBaseTable(parent)
{
    setStyleClass("panel");
    initForm(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::Cancel()
{
    CEccRightView::showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::createListTitle()
{
    if(m_pContent)
    {
        int nRow = m_pContent->numRows();
        new WText(SVResString::getResString("IDS_Name"), m_pContent->elementAt(0, 0));

        new WImage("../Images/table_head_space.png", m_pContent->elementAt(0, 1));
        new WImage("../Images/space.gif", m_pContent->elementAt(0, 1));
        new WText(SVResString::getResString("IDS_Sort"), m_pContent->elementAt(0, 2));

        m_pContent->elementAt(0, 0)->setStyleClass("table_data_grid_header_text");
        m_pContent->elementAt(0, 1)->setStyleClass("width4");
        m_pContent->elementAt(0, 2)->setStyleClass("table_data_grid_header_text");

        m_pContent->elementAt(0, 0)->setContentAlignment(AlignCenter);
        m_pContent->elementAt(0, 2)->setContentAlignment(AlignCenter);
        m_pContent->GetRow(0)->setStyleClass("table_data_grid_header");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::createOperate()
{
    int nRow = numRows();
    m_pOperate = new WTable(elementAt(nRow, 0));
    if(m_pOperate)
    {
        m_pOperate->setStyleClass("widthauto");
        int nOptRow = m_pOperate->numRows();
        CEccImportButton *pSave = new CEccImportButton(SVResString::getResString("IDS_Save"), SVResString::getResString("IDS_Save_Sort_Tip"), 
            "", m_pOperate->elementAt(nOptRow, 0));
        if(pSave)
        {
            WObject::connect(pSave, SIGNAL(clicked()), "showbar();", this, SLOT(Save()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(nOptRow, 1));

        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel"), SVResString::getResString("IDS_Cancel_Sort_Tip"), 
            "", m_pOperate->elementAt(nOptRow, 2));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::initForm(bool bHasHelp)
{
    CEccBaseTable::createTitle(bHasHelp);
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Sort"));

    int nRow = numRows();

    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("height95p");
    if(pSub)
    {
        pSub->setStyleClass("panel");
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel");
        }

        CEccListTable *pSubList = new CEccListTable(pSub->elementAt(0, 0), false, false, true, false);
        if(pSubList)
        {
            pSubList->setTitle(SVResString::getResString("IDS_Sort"));
            m_pContent = pSubList->getListTable();
        }
        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);
        //pSub->elementAt(0, 0)->setStyleClass("padding_top");
    }

    createOperate();
    createListTitle();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::Save()
{
    //? 保存

    checkDisplayIndex();

    CEccTreeView::ReCreateTreeNode(m_szParentID);

    CEccRightView::showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::setSortNode(const CEccTreeNode *pNode, int nType)
{
    CEccTreeGroup *pGroup = NULL;
    CEccTreeDevice *pDevice = NULL;

    m_szParentID = pNode->getECCIndex();

    if(m_pContent)
    {
        while(m_pContent->numRows() > 1)
            m_pContent->deleteRow(m_pContent->numRows() - 1);

        m_lsIndexList.clear();
        m_lsLineEdit.clear();

        m_nDataType = nType;

        switch(nType)
        {
        case SiteView_ECC_Group:
            //? 枚举组
            enumGroup(pNode);
            break;
        case SiteView_ECC_Device:
            //? 枚举设备
            enumDevice(pNode);
            break;
        case SiteView_ECC_Monitor:
            //? 枚举监测器
            enumMonitor(pNode);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::enumDevice(const CEccTreeNode *pGroupNode)
{
    map<int, CEccTreeDevice, less<int> >::iterator itdevice;
    if(pGroupNode->m_nType == SiteView_ECC_Group || pGroupNode->m_nType == SiteView_ECC_SE)
    {
        CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pGroupNode));
        int nRow = m_pContent->numRows();

        char szIndex[32] = {0};
        for(itdevice = pGroup->m_Devices.begin(); itdevice != pGroup->m_Devices.end(); itdevice ++)
        {
            new WText(itdevice->second.m_szName, m_pContent->elementAt(nRow, 0));

            sprintf(szIndex, "%d", nRow);
            WLineEdit *pIndex = new WLineEdit(szIndex, m_pContent->elementAt(nRow, 2));
            if(pIndex)
            {
                pIndex->setStyleClass("cell_50px");
                m_lsLineEdit[pIndex] = itdevice->second.m_szIndex;
                m_lsIndexList[nRow] = pIndex;
            }

            m_pContent->elementAt(nRow, 2)->setStyleClass("width120px");
            m_pContent->elementAt(nRow, 2)->setContentAlignment(AlignCenter);
            m_pContent->elementAt(nRow, 0)->setStyleClass("table_data_grid_item_text");
            nRow ++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::enumGroup(const CEccTreeNode *pGroupNode)
{
    map<int, CEccTreeGroup, less<int> >::iterator itgroup;

    if(pGroupNode->m_nType == SiteView_ECC_Group || pGroupNode->m_nType == SiteView_ECC_SE)
    {
        CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pGroupNode));
        int nRow = m_pContent->numRows();

        char szIndex[32] = {0};
        for(itgroup = pGroup->m_SubGroups.begin(); itgroup != pGroup->m_SubGroups.end(); itgroup ++)
        {
            new WText(itgroup->second.m_szName, m_pContent->elementAt(nRow, 0));
            
            sprintf(szIndex, "%d", nRow);
            WLineEdit *pIndex = new WLineEdit(szIndex, m_pContent->elementAt(nRow, 2));
            if(pIndex)
            {
                pIndex->setStyleClass("cell_50px");
                m_lsLineEdit[pIndex] = itgroup->second.m_szIndex;
                m_lsIndexList[nRow] = pIndex;
            }

            m_pContent->elementAt(nRow, 2)->setStyleClass("width120px");
            m_pContent->elementAt(nRow, 2)->setContentAlignment(AlignCenter);
            m_pContent->elementAt(nRow, 0)->setStyleClass("table_data_grid_item_text");
            nRow ++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::enumMonitor(const CEccTreeNode *pDeviceNode)
{
    map<int, CECCMonitor, less<int> >::iterator itmonitor;
    if(pDeviceNode->m_nType == SiteView_ECC_Device)
    {
        CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pDeviceNode));
        int nRow = m_pContent->numRows();

        char szIndex[32] = {0};
        for(itmonitor = pDevice->m_Monitors.begin(); itmonitor != pDevice->m_Monitors.end(); itmonitor ++)
        {
            new WText(itmonitor->second.m_szName, m_pContent->elementAt(nRow, 0));
            
            sprintf(szIndex, "%d", nRow);
            WLineEdit *pIndex = new WLineEdit(szIndex, m_pContent->elementAt(nRow, 2));
            if(pIndex)
            {
                pIndex->setStyleClass("cell_50px");
                m_lsLineEdit[pIndex] = itmonitor->second.m_szIndex;
                m_lsIndexList[nRow] = pIndex;
            }

            m_pContent->elementAt(nRow, 2)->setStyleClass("width120px");
            m_pContent->elementAt(nRow, 2)->setContentAlignment(AlignCenter);
            m_pContent->elementAt(nRow, 0)->setStyleClass("table_data_grid_item_text");

            nRow ++;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::checkDisplayIndex()
{
    map<int, WLineEdit*, less<int> >::iterator intit;
    map<WLineEdit*, string, less<WLineEdit*> >::iterator szit;
    
    map<int, string, less<int> > lsDis;
    map<int, string, less<int> >::iterator lsDisItem;

    string szIndex("");
    int nIndex = 0;

    for(intit = m_lsIndexList.begin(); intit != m_lsIndexList.end(); intit ++)
    {
        szit = m_lsLineEdit.find(intit->second);
        if(szit != m_lsLineEdit.end())
        {
            szIndex = szit->first->text();
            nIndex = 0;
            if(!szIndex.empty())
                nIndex = atoi(szIndex.c_str());
            else
                nIndex = 0;

            lsDisItem = lsDis.find(nIndex);
            while(lsDisItem != lsDis.end())
            {
                nIndex ++;
                lsDisItem = lsDis.find(nIndex);
            }
            lsDis[nIndex] = szit->second;
        }
    }

    switch(m_nDataType)
    {
    case SiteView_ECC_Group:
        saveGroup(lsDis);
        break;
    case SiteView_ECC_Device:
        saveDevice(lsDis);
        break;
    case SiteView_ECC_Monitor:
        saveMonitor(lsDis);
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::saveGroup(map<int, string, less<int> > &lsDis)
{
    map<int, string, less<int> >::iterator lsDisItem;
    for(lsDisItem = lsDis.begin(); lsDisItem != lsDis.end(); lsDisItem ++)
    {
        string szGroupID = lsDisItem->second;
        OBJECT objGroup = GetGroup(szGroupID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(objGroup != INVALID_VALUE)
        {
            char szIndex[8] = {0};
            sprintf(szIndex, "%d", lsDisItem->first);
            MAPNODE mainnode = GetGroupMainAttribNode(objGroup);
            if(mainnode != INVALID_VALUE)
                AddNodeAttrib(mainnode, svShowIndex, szIndex);

            SubmitGroup(objGroup);
            CloseGroup(objGroup);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::saveDevice(map<int, string, less<int> > &lsDis)
{
    map<int, string, less<int> >::iterator lsDisItem;
    for(lsDisItem = lsDis.begin(); lsDisItem != lsDis.end(); lsDisItem ++)
    {
        string szDeviceID = lsDisItem->second;
        OBJECT objDevice = GetEntity(szDeviceID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(objDevice != INVALID_VALUE)
        {
            char szIndex[8] = {0};
            sprintf(szIndex, "%d", lsDisItem->first);
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            if(mainnode != INVALID_VALUE)
                AddNodeAttrib(mainnode, svShowIndex, szIndex);

            SubmitEntity(objDevice);
            CloseEntity(objDevice);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSortTable::saveMonitor(map<int, string, less<int> > &lsDis)
{
    map<int, string, less<int> >::iterator lsDisItem;
    for(lsDisItem = lsDis.begin(); lsDisItem != lsDis.end(); lsDisItem ++)
    {
        string szMonitorID = lsDisItem->second;
        OBJECT objMonitor = GetMonitor(szMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(objMonitor != INVALID_VALUE)
        {
            char szIndex[8] = {0};
            sprintf(szIndex, "%d", lsDisItem->first);

            MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
            if(mainnode != INVALID_VALUE)
                AddNodeAttrib(mainnode, svShowIndex, szIndex);
            SubmitMonitor(objMonitor);
            CloseMonitor(objMonitor);
        }
    }
}

