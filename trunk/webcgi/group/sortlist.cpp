
#include "sortlist.h"
#include "resstring.h"

extern void PrintDebugString(const char * szErrMsg);
extern void PrintDebugString(const string &szErrMsg);

CSVSortList::CSVSortList(WContainerWidget *parent, CUser *pUser, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szIDCUser = szIDCUser;
    m_szIDCPwd  = szIDCPwd;
    m_pSVUser   = pUser;

    m_pContent  = NULL;

    //loadString();
    initForm();
}

void CSVSortList::UpFloor(const std::string szIndex)
{
}

void CSVSortList::DownFloor(const std::string szIndex)
{
}

void CSVSortList::EnumObject(string &szIndex, int &nType)
{
    m_lsOld.clear();
    m_lsCurrent.clear();

    m_sortList.clear();

    m_nType = nType;

    switch(nType)
    {
    case Tree_SE:
        break;
    case Tree_GROUP:
        enumGroup(szIndex);
        break;
    case Tree_DEVICE:
        enumDevice(szIndex);
        break;
    case Tree_MONITOR:
        enumMonitor(szIndex);
        break;
    }
    addList();
}

void CSVSortList::addList()
{
    if(m_pContent)
    {
        while(m_pContent->numRows() > 1)
            m_pContent->deleteRow(m_pContent->numRows() - 1);

        m_svList.clear();
        int nRow = m_pContent->numRows();
        for(lsItem = m_sortList.begin(); lsItem != m_sortList.end(); lsItem ++)
        {
            WText *pName  = new WText(lsItem->second.szName, m_pContent->elementAt(nRow, 0));
            char szDisIndex[8] = {0};
            sprintf(szDisIndex, "%d", nRow);
            WLineEdit *pIndex = new WLineEdit (szDisIndex, m_pContent->elementAt(nRow, 1));

            if((nRow + 1) % 2 == 0)
                m_pContent->GetRow(nRow)->setStyleClass("tr1");
            else
                m_pContent->GetRow(nRow)->setStyleClass("tr2");

            SVTableCell svCell;
            if(pIndex)
            {
                svCell.setType(adLineEdit);
                svCell.setValue(pIndex);
                svCell.setTag(lsItem->first);
                svCell.setProperty(lsItem->second.szIndex.c_str());
                m_svList.WriteCell(nRow, 1, svCell);
            }

            nRow ++;
        }
    }
}

void CSVSortList::createOperate()
{
    int nRow = numRows();
    WPushButton *pSave = new WPushButton(SVResString::getResString("IDS_OK"), elementAt(nRow, 0));
    if(pSave)
    {
        WObject::connect(pSave, SIGNAL(clicked()) , "showbar();", this, SLOT(saveList()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        pSave->setToolTip(SVResString::getResString("IDS_Save_Sort_Tip"));
    }

    new WText("&nbsp;", elementAt(nRow, 0));

    WPushButton *pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), elementAt(nRow,0));
    if(pCancel)
    {
        pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Sort_Tip"));
        WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(cancelEdit()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    elementAt(nRow, 0)->setContentAlignment(AlignCenter);
}

void CSVSortList::createTitle()
{
    int nRow = numRows();
    m_pTitle = new WText(SVResString::getResString("IDS_Sort"), (WContainerWidget*)elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("t1title");
}

void CSVSortList::createContent()
{
    int nRow = numRows();
    WTable * pTable = new WTable(elementAt(nRow,0));	
    if(pTable)
    {
        pTable->setCellPadding(0);
        pTable->setCellSpaceing(0);

        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(pTable);
        }
        pTable->setStyleClass("t5"); 
        elementAt(nRow, 0)->setStyleClass("t7");

        nRow = pTable->numRows();
        m_pContent = new WTable(pTable->elementAt(nRow,0));
        pTable->elementAt(nRow,0)->setContentAlignment(AlignTop);
    }

    if(m_pContent)
    {
        m_pContent->setStyleClass("t3");
        nRow = m_pContent->numRows();
        new WText(SVResString::getResString("IDS_Name"), m_pContent->elementAt(nRow, 0));
        new WText(SVResString::getResString("IDS_Sort"), m_pContent->elementAt(nRow, 1));
        m_pContent->GetRow(0)->setStyleClass("t3title");
    }
}

void CSVSortList::enumDevice(string &szGroupIndex)
{
    list<string> lsDeviceID;
    list<string>::iterator lsItem;
    OBJECT objGroup;

    base_param device;

    if(IsSVSEID(szGroupIndex))
    {
        objGroup = GetSVSE(szGroupIndex, m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            GetSubEntitysIDBySE(objGroup, lsDeviceID);
            CloseSVSE(objGroup);
        }
    }
    else
    {
        objGroup = GetGroup(szGroupIndex, m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            GetSubEntitysIDByGroup(objGroup, lsDeviceID);
            CloseGroup(objGroup);
        }
    }

    int nIndex = 0;
    for(lsItem = lsDeviceID.begin(); lsItem != lsDeviceID.end(); lsItem ++)
    {
        string szID = (*lsItem).c_str();
        bool bHasRight = true;
        if(m_pSVUser)
            bHasRight = m_pSVUser->haveGroupRight(szID, Tree_DEVICE);
        if(bHasRight)
        {
            OBJECT objDevice = GetEntity(szID, m_szIDCUser, m_szIDCPwd);
            if(objDevice != INVALID_VALUE)
            {
                MAPNODE node = GetEntityMainAttribNode(objDevice);
                if(node != INVALID_VALUE)
                {
                    string szName (""), szIndex ("");
                    FindNodeValue(node, "sv_name", szName);
                    FindNodeValue(node, "sv_index", szIndex);
                    if(szIndex.empty())
                        nIndex = FindIndexByID(szID);
                    else
                        nIndex = atoi(szIndex.c_str());
                    device.szIndex = szID;
                    device.szName = szName;
                    m_sortList[nIndex] = device;
                }
                CloseEntity(objDevice);
            }
        }
    }
}

void CSVSortList::enumGroup(string &szGroupIndex)
{
    list<string> lsGroupID;
    list<string>::iterator lsItem;
    OBJECT objGroup;

    base_param group;

    if(IsSVSEID(szGroupIndex))
    {
        objGroup = GetSVSE(szGroupIndex, m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            GetSubGroupsIDBySE(objGroup, lsGroupID);
            CloseSVSE(objGroup);
        }
    }
    else
    {
        objGroup = GetGroup(szGroupIndex, m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            GetSubGroupsIDByGroup(objGroup, lsGroupID);
            CloseGroup(objGroup);
        }
    }

    int nIndex = 0;
    for(lsItem = lsGroupID.begin(); lsItem != lsGroupID.end(); lsItem ++)
    {
        string szID = (*lsItem).c_str();
        bool bHasRight = true;
        if(m_pSVUser)
            bHasRight = m_pSVUser->haveGroupRight(szID, Tree_DEVICE);
        if(bHasRight)
        {
            objGroup = GetGroup(szID, m_szIDCUser, m_szIDCPwd);
            if(objGroup != INVALID_VALUE)
            {
                MAPNODE node = GetGroupMainAttribNode(objGroup);
                if(node != INVALID_VALUE)
                {
                    string szName (""), szIndex ("");
                    FindNodeValue(node, "sv_name", szName);
                    FindNodeValue(node, "sv_index", szIndex);
                    if(szIndex.empty())
                        nIndex = FindIndexByID(szID);
                    else
                        nIndex = atoi(szIndex.c_str());
                    group.szIndex = szID;
                    group.szName = szName;
                    m_sortList[nIndex] = group;
                }
                CloseGroup(objGroup);
            }
        }
    }
}

void CSVSortList::enumMonitor(string &szDeviceIndex)
{
    OBJECT objDevice = GetEntity(szDeviceIndex,  m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {
            string szDeviceName ("");
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            if(mainnode != INVALID_VALUE)
                FindNodeValue(mainnode, "sv_name", szDeviceName);
            
            int nIndex = 0;
            base_param monitor;
            for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
            {
                string szMonitorId = (*lstItem).c_str();
                OBJECT objMonitor = GetMonitor(szMonitorId, m_szIDCUser, m_szIDCPwd);
                if(objMonitor != INVALID_VALUE)
                {
                    MAPNODE node = GetMonitorMainAttribNode(objMonitor);
                    if(node != INVALID_VALUE)
                    {
                        string szName (""), szIndex ("");
                        FindNodeValue(node, "sv_name", szName);
                        FindNodeValue(node, "sv_index", szIndex);
                        if(szIndex.empty())
                            nIndex = FindIndexByID(szMonitorId);
                        else
                            nIndex = atoi(szIndex.c_str());

                        monitor.szIndex = szMonitorId;
                        monitor.szName = szDeviceName + ":" + szName;
                        m_sortList[nIndex] = monitor;
                    }
                    CloseMonitor(objMonitor);
                }
            }
        }
        CloseEntity(objDevice);
    }
}

void CSVSortList::enumSVSE()
{
}

void CSVSortList::initForm()
{
    setStyleClass("t5");
    createTitle();
    createContent();
    createOperate();
}

//void CSVSortList::loadString()
//{
//	//Resource
//	OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//			FindNodeValue(ResNode,"IDS_Sort",m_szTitle);
//			FindNodeValue(ResNode,"IDS_OK",m_szSave);
//			FindNodeValue(ResNode,"IDS_Cancel",m_szCancel);
//			FindNodeValue(ResNode,"IDS_Save_Sort_Tip",m_szSaveTip);
//			FindNodeValue(ResNode,"IDS_Cancel_Sort_Tip",m_szCancelTip);
//			FindNodeValue(ResNode,"IDS_Up_Floor_Tip",m_szUpTip);
//			FindNodeValue(ResNode,"IDS_Down_Floor_Tip",m_szDownTip);
//			FindNodeValue(ResNode,"IDS_Name",m_szColName);
//			FindNodeValue(ResNode,"IDS_Sort",m_szColSort);
//
//		}
//		CloseResource(objRes);
//	}
//}

bool CSVSortList::checkDisplayIndex()
{
    irow it;
    map<int, string, less<int> > lsDis;
    map<int, string, less<int> >::iterator lsDisItem;
    for(it = m_svList.begin(); it != m_svList.end(); it++)
    {
        SVTableCell *pCell = (*it).second.Cell(1);
        if(pCell && pCell->Type() == adLineEdit)
        {
            if(pCell->Value())
            {                
                string szIndex = ((WLineEdit*)pCell->Value())->text();
                int nIndex = 0;
                if(!szIndex.empty())
                    nIndex = atoi(szIndex.c_str());
                lsDisItem = lsDis.find(nIndex);
                while(lsDisItem != lsDis.end())
                {
                    nIndex ++;
                    lsDisItem = lsDis.find(nIndex);
                }
                lsDis[nIndex] = pCell->Property();
            }
        }
    } 
    switch(m_nType)
    {
    case Tree_GROUP:
        saveGroup(lsDis);
        break;
    case Tree_DEVICE:
        saveDevice(lsDis);
        break;
    case Tree_MONITOR:
        saveMonitor(lsDis);
        break;
    }
    return true;
}

void CSVSortList::saveList()
{
    checkDisplayIndex();
    emit RefreshList();
}

void CSVSortList::saveDevice(map<int, string, less<int> > &lsDis)
{
    map<int, string, less<int> >::iterator lsDisItem;
    for(lsDisItem = lsDis.begin(); lsDisItem != lsDis.end(); lsDisItem ++)
    {
        string szDeviceID = lsDisItem->second;
        OBJECT objDevice = GetEntity(szDeviceID,  m_szIDCUser, m_szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {
            char szIndex[8] = {0};
            sprintf(szIndex, "%d", lsDisItem->first);
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            if(mainnode != INVALID_VALUE)
                AddNodeAttrib(mainnode, "sv_index", szIndex);

            SubmitEntity(objDevice);
            CloseEntity(objDevice);
        }
    }
}

void CSVSortList::saveMonitor(map<int, string, less<int> > &lsDis)
{
    map<int, string, less<int> >::iterator lsDisItem;
    for(lsDisItem = lsDis.begin(); lsDisItem != lsDis.end(); lsDisItem ++)
    {
        string szMonitorID = lsDisItem->second;
        OBJECT objMonitor = GetMonitor(szMonitorID,  m_szIDCUser, m_szIDCPwd);
        if(objMonitor != INVALID_VALUE)
        {
            char szIndex[8] = {0};
            sprintf(szIndex, "%d", lsDisItem->first);
            
            MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
            if(mainnode != INVALID_VALUE)
                AddNodeAttrib(mainnode, "sv_index", szIndex);
            SubmitMonitor(objMonitor);
            CloseMonitor(objMonitor);           
        } 
    }
}

void CSVSortList::saveGroup(map<int, string, less<int> > &lsDis)
{
    map<int, string, less<int> >::iterator lsDisItem;
    for(lsDisItem = lsDis.begin(); lsDisItem != lsDis.end(); lsDisItem ++)
    {
        string szGroupID = lsDisItem->second;
        OBJECT objGroup = GetGroup(szGroupID,  m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            char szIndex[8] = {0};
            sprintf(szIndex, "%d", lsDisItem->first);
            MAPNODE mainnode = GetGroupMainAttribNode(objGroup);
            if(mainnode != INVALID_VALUE)
                AddNodeAttrib(mainnode, "sv_index", szIndex);

            SubmitGroup(objGroup);
            CloseGroup(objGroup);
        }
    }
}


void CSVSortList::cancelEdit()
{
    emit backMainView();
}

