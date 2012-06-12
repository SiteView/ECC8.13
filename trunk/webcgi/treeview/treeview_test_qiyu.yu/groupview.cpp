#include "groupview.h"

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WCheckBox"

#include "basedefine.h"
#include "basefunc.h"
#include "treeview.h"
#include "statedesc.h"
#include "listtable.h"
#include "resstring.h"
#include "rightview.h"
#include "mainview.h"
#include "debuginfor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccGroupView::CEccGroupView(WContainerWidget *parent):
WTable(parent),
m_pTitle(NULL),
m_pGeneral(NULL),
m_pGroupList(NULL),
m_pDeviceList(NULL),
m_pDepend(NULL),
m_pContent(NULL),
m_pName(NULL),
m_pDescription(NULL),
m_pState(NULL)
{    
    setStyleClass("panel");
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::createStateDesc()
{
    int nRow = numRows();
    new CEccStateDesc(elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::createTitle()
{
    int nRow = m_pContent->numRows();
    m_pTitle = new CEccGenTitle(m_pContent->elementAt(nRow, 0));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::initForm()
{
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

        m_pContent = new WTable(pSub->elementAt(0, 0));
        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);

        if(m_pContent)
        {
            createTitle();
            createGeneral();
            createGroupList();
            createDeviceList();
        }
    }

    createStateDesc();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::createGeneral()
{
    int nRow = m_pContent->numRows();

    m_pGeneral = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
    if(m_pGeneral)
    {
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Infor_Title"));

        WTable *pTable = m_pGeneral->getListTable();
        if(pTable)
        {
            int nRow = 0;
            new WText(SVResString::getResString("IDS_Name"), pTable->elementAt(0, 0));
            new WText(SVResString::getResString("IDS_Description"), pTable->elementAt(1, 0));
            new WText(SVResString::getResString("IDS_State"), pTable->elementAt(2, 0));
            new WText(SVResString::getResString("IDS_Depends_On"), pTable->elementAt(3, 0));

            m_pName = new WText(SVResString::getResString("IDS_Name"), pTable->elementAt(0, 1));
            m_pDescription = new WText(SVResString::getResString("IDS_Description"), pTable->elementAt(1, 1));
            m_pState = new WText(SVResString::getResString("IDS_State"), pTable->elementAt(2, 1));
            m_pDepend = new WTable(pTable->elementAt(3, 1));
            if(m_pDepend)
                m_pDepend->setStyleClass("widthauto");

            pTable->GetRow(0)->setStyleClass("padding_top");
            pTable->GetRow(1)->setStyleClass("padding_top");
            pTable->GetRow(2)->setStyleClass("padding_top");
            pTable->GetRow(3)->setStyleClass("padding_top");

            pTable->elementAt(0, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(1, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(2, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(3, 0)->setStyleClass("table_data_grid_header_text");

            pTable->elementAt(0, 1)->setStyleClass("table_data_text");
            pTable->elementAt(1, 1)->setStyleClass("table_data_text");
            pTable->elementAt(2, 1)->setStyleClass("table_data_text");
            pTable->elementAt(3, 1)->setStyleClass("table_data_text");
            pTable->elementAt(4, 1)->setStyleClass("table_data_text");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::createDeviceList()
{
    int nRow = m_pContent->numRows();

    m_pDeviceList = new CEccListTable(m_pContent->elementAt(nRow, 0));
    if(m_pDeviceList)
    {
        m_pDeviceList->setTitle(SVResString::getResString("IDS_Device"));
        m_pDeviceList->setNoChild(SVResString::getResString("IDS_DIEVICE_LIST_IS_NULL"));

        list<string> lsCols;
        lsCols.push_back("&nbsp;");
        lsCols.push_back(SVResString::getResString("IDS_State"));
        lsCols.push_back(SVResString::getResString("IDS_State_Description"));
        lsCols.push_back(SVResString::getResString("IDS_Name"));
        lsCols.push_back(SVResString::getResString("IDS_Edit"));
        lsCols.push_back(SVResString::getResString("IDS_Delete"));
        lsCols.push_back(SVResString::getResString("IDS_Table_Col_Test"));
        lsCols.push_back(SVResString::getResString("IDS_Table_Col_Last_Refresh"));
        m_pDeviceList->setCols(lsCols);

        m_pDeviceList->setAddNewTitle(SVResString::getResString("IDS_Add_Device"));
        m_pDeviceList->setAddNewTip(SVResString::getResString("IDS_Add_Device_Tip"));

        m_pDeviceList->setAddNewFunc(CEccRightView::showAddDevice1st);

        list<int> lsOperate;
        lsOperate.push_back(SV_ENABLE);
        lsOperate.push_back(SV_DISABLE);
        lsOperate.push_back(SV_DELETE);
        lsOperate.push_back(SV_SORT);
        lsOperate.push_back(SV_COPY);
        lsOperate.push_back(SV_PAST);
        m_pDeviceList->setOperaters(lsOperate, SiteView_ECC_Device);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::createGroupList()
{
    int nRow = m_pContent->numRows();

    m_pGroupList = new CEccListTable(m_pContent->elementAt(nRow, 0));
    if(m_pGroupList)
    {
        m_pGroupList->setTitle(SVResString::getResString("IDS_Sub_Group"));
        m_pGroupList->setNoChild(SVResString::getResString("IDS_GROUP_LIST_IS_NULL"));

        list<string> lsCols;
        lsCols.push_back("&nbsp;");
        lsCols.push_back(SVResString::getResString("IDS_State"));
        lsCols.push_back(SVResString::getResString("IDS_State_Description"));
        lsCols.push_back(SVResString::getResString("IDS_Name"));
        lsCols.push_back(SVResString::getResString("IDS_Edit"));
        lsCols.push_back(SVResString::getResString("IDS_Delete"));
        lsCols.push_back(SVResString::getResString("IDS_Table_Col_Last_Refresh"));
        m_pGroupList->setCols(lsCols);

        m_pGroupList->setCols(lsCols);

        m_pGroupList->setAddNewTitle(SVResString::getResString("IDS_Add_Group"));
        m_pGroupList->setAddNewTip(SVResString::getResString("IDS_Add_Group_Tip"));

        m_pGroupList->setAddNewFunc(CEccRightView::showAddGroupForm);

        list<int> lsOperate;
        lsOperate.push_back(SV_ENABLE);
        lsOperate.push_back(SV_DISABLE);
        lsOperate.push_back(SV_DELETE);
        lsOperate.push_back(SV_SORT);
        m_pGroupList->setOperaters(lsOperate, SiteView_ECC_Group);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::UpdataGeneralData(const CEccTreeGroup *pNode)
{
    if(m_pTitle)
    {
        m_pTitle->setCurIndex(pNode->getECCIndex());
        m_pTitle->refreshTime();
    }

    if(m_pGeneral)
        m_pGeneral->showSubTable();

    if(m_pName)
        m_pName->setText(pNode->getName());

    if(m_pDescription)
        m_pDescription->setText(pNode->getDescription());

    if(m_pState)
        m_pState->setText(pNode->getShowText());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::setCurrentObj(const CEccTreeGroup *pNode)
{
    if(m_pTitle)
    {
        m_pTitle->setCurIndex(pNode->getECCIndex());
        m_pTitle->refreshTime();
    }
    
    changePath(pNode->getDependsID());

    if(m_pGeneral)
        m_pGeneral->showSubTable();

    if(m_pName)
        m_pName->setText(pNode->getName());

    if(m_pDescription)
        m_pDescription->setText(pNode->getDescription());

    if(m_pState)
        m_pState->setText(pNode->getShowText());

    if(m_pDeviceList)
    {
        clearDeviceList();
        m_pDeviceList->setOperatePurview(pNode->getPurview(), SiteView_ECC_Group);
        m_pDeviceList->clearCheckList();
        m_pDeviceList->hideNoChild();
        m_pDeviceList->showSubTable();

        EnumDevice(pNode);
    }

    if(m_pGroupList)
    {
        clearGroupList();
        m_pGroupList->setOperatePurview(pNode->getPurview(), SiteView_ECC_Group);
        m_pGroupList->clearCheckList();
        m_pGroupList->hideNoChild();
        m_pGroupList->showSubTable();

        EnumGroup(pNode);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::clearDeviceList()
{
    WTable *pSub = m_pDeviceList->getListTable();
    if(pSub)
    {
        while(pSub->numRows() > 1)
        {
            pSub->deleteRow(pSub->numRows() - 1);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::clearGroupList()
{
    WTable *pSub = m_pGroupList->getListTable();
    if(pSub)
    {
        while(pSub->numRows() > 1)
        {
            pSub->deleteRow(pSub->numRows() - 1);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::EnumGroup(const CEccTreeGroup *pNode)
{
    m_pGroupList->setCurrentID(pNode->getECCIndex());
    WTable *pSub = m_pGroupList->getListTable();
    if(pSub)
    {
        if(pNode->m_SubGroups.empty())
        {
            m_pGroupList->showNoChild();
        }
        else
        {
            int nRow = pSub->numRows();

            if(pNode->m_SubGroups.size() == 1)
                m_pGroupList->showHideSort(false);
            else if(pNode->m_SubGroups.size() > 1 && pNode->getPurview() & Edit_Group)
                 m_pGroupList->showHideSort(true);

            map<int, CEccTreeGroup, less<int> >::const_iterator group;
            for(group = pNode->m_SubGroups.begin(); group != pNode->m_SubGroups.end(); group ++)
            {
                if(group->second.getPurview() & Edit_Group || group->second.getPurview() & Delete_Group)
                {
                    WCheckBox *pCheck = new WCheckBox("", pSub->elementAt(nRow, 0));
                    if(pCheck)
                        m_pGroupList->addCheckList(group->second.getECCIndex(), pCheck);
                }

                WImage *pState = new WImage("../Images/state_green.gif", pSub->elementAt(nRow, 2));
                if(pState)
                {     
                    pState->setStyleClass("hand");
                    switch(group->second.getState())
                    {
                    case dyn_no_date:
                        pState->setImageRef("../Images/state_grey.gif");
                        break;
                    case dyn_normal:
                        pState->setImageRef("../Images/state_green.gif");
                        break;
                    case dyn_warnning:
                        pState->setImageRef("../Images/state_yellow.gif");
                        break;
                    case dyn_error:
                    case dyn_bad:
                        pState->setImageRef("../Images/state_red.gif");
                        break;
                    case dyn_disable:
                        pState->setImageRef("../Images/state_stop.gif");
                        break;
                    }

                    if(group->second.getPurview() & Edit_Group)
                    {
                        string szUrl = "onclick='showDisableUrl(\"disable.exe?disabletype=0&disableid=" + group->second.getECCIndex() 
                            + "\", \"" + CEccMainView::m_szGlobalEvent + "\");'";
                        strcpy(pState->contextmenu_, szUrl.c_str());
                    }
                }

                string szState(group->second.getShowText());
                buildHtmlText(szState);
                new WText(szState, pSub->elementAt(nRow, 4));

                WText *pName = new WText(group->second.getName(), pSub->elementAt(nRow, 6));
                if(pName)
                    sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onclick='SetCurfocus(\"%s\")' "
                        "onmouseover='this.style.textDecoration=\"underline\"' onmouseout='this.style.textDecoration=\"none\"'",
                        group->second.getECCIndex().c_str());

                if(group->second.getPurview() & Edit_Group)
                {
                    WImage *pEdit = new WImage("../Images/edit.gif",  pSub->elementAt(nRow, 8));
                    if(pEdit)
                    {
                        pEdit->setStyleClass("hand");
                        char chFunc[128] = {0};
                        sprintf(chFunc, "objoperatebyid('%s','%d');", group->second.getECCIndex().c_str(), SV_EDIT);
                        WObject::connect(pEdit, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                    }
                }

                if(group->second.getPurview() & Delete_Group)
                {
                    WImage *pDelete = new WImage("../Images/delete.gif", pSub->elementAt(nRow, 10));
                    if(pDelete)
                    {
                        pDelete->setStyleClass("hand");
                        char chFunc[128] = {0};
                        sprintf(chFunc, "objoperatebyid('%s','%d');", group->second.getECCIndex().c_str(), SV_DELETE);
                        WObject::connect(pDelete, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                    }
                }

                new WText(group->second.getShowTime(), pSub->elementAt(nRow, 12));

                pSub->elementAt(nRow, 2)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 4)->setStyleClass("table_data_grid_item_text");
                pSub->elementAt(nRow, 6)->setStyleClass("table_data_grid_item_text");
                pSub->elementAt(nRow, 8)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 10)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 12)->setStyleClass("table_data_grid_item_text");

                if(nRow % 2 == 0)
                    pSub->GetRow(nRow)->setStyleClass("table_data_grid_item_bg");

                nRow ++;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::EnumDevice(const CEccTreeGroup *pNode)
{
    m_pDeviceList->setCurrentID(pNode->getECCIndex());
    WTable *pSub = m_pDeviceList->getListTable();
    if(pSub)
    {
        if(pNode->m_Devices.empty())
        {
            m_pDeviceList->showNoChild();
        }
        else
        {
            int nRow = pSub->numRows();

            if(pNode->m_Devices.size() == 1)
                m_pDeviceList->showHideSort(false);
            else if(pNode->m_Devices.size() > 1 && pNode->getPurview() & Edit_Group)
                 m_pDeviceList->showHideSort(true);

            map<int, CEccTreeDevice, less<int> >::const_iterator device;
            for(device = pNode->m_Devices.begin(); device != pNode->m_Devices.end(); device ++)
            {
                if(device->second.getPurview() & Edit_Device || device->second.getPurview() & Delete_Device)
                {
                    WCheckBox *pCheck = new WCheckBox("", pSub->elementAt(nRow, 0));
                    if(pCheck)
                        m_pDeviceList->addCheckList(device->second.getECCIndex(), pCheck);
                }

                WImage *pState = new WImage("../Images/state_green.gif", pSub->elementAt(nRow, 2));
                if(pState)
                {     
                    pState->setStyleClass("hand");
                    switch(device->second.getState())
                    {
                    case dyn_no_date:
                        pState->setImageRef("../Images/state_grey.gif");
                        break;
                    case dyn_normal:
                        pState->setImageRef("../Images/state_green.gif");
                        break;
                    case dyn_warnning:
                        pState->setImageRef("../Images/state_yellow.gif");
                        break;
                    case dyn_error:
                    case dyn_bad:
                        pState->setImageRef("../Images/state_red.gif");
                        break;
                    case dyn_disable:
                        pState->setImageRef("../Images/state_stop.gif");
                        break;
                    }

                    if(device->second.getPurview() & Edit_Device)
                    {
                        string szUrl = "onclick='showDisableUrl(\"disable.exe?disabletype=1&disableid=" + device->second.getECCIndex() 
                            + "\", \"" + CEccMainView::m_szGlobalEvent + "\");'";
                        strcpy(pState->contextmenu_, szUrl.c_str());
                    }
                }

                string szState(device->second.getShowText());
                buildHtmlText(szState);
                new WText(szState, pSub->elementAt(nRow, 4));

                WText *pName = new WText(device->second.getName(), pSub->elementAt(nRow, 6));
                if(pName)
                    sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onclick='SetCurfocus(\"%s\")' "
                        "onmouseover='this.style.textDecoration=\"underline\"' onmouseout='this.style.textDecoration=\"none\"'",
                        device->second.getECCIndex().c_str());

                if(device->second.getPurview() & Edit_Device)
                {
                    WImage *pEdit = new WImage("../Images/edit.gif",  pSub->elementAt(nRow, 8));
                    if(pEdit)
                    {
                        pEdit->setStyleClass("hand");
                        char chFunc[128] = {0};
                        sprintf(chFunc, "objoperatebyid('%s','%d');", device->second.getECCIndex().c_str(), SV_EDIT);
                        WObject::connect(pEdit, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                    }
                }

                if(device->second.getPurview() & Delete_Device)
                {
                    WImage *pDelete = new WImage("../Images/delete.gif", pSub->elementAt(nRow, 10));
                    if(pDelete)
                    {
                        pDelete->setStyleClass("hand");
                        char chFunc[128] = {0};
                        sprintf(chFunc, "objoperatebyid('%s','%d');", device->second.getECCIndex().c_str(), SV_DELETE);
                        WObject::connect(pDelete, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                    }
                }

                if(device->second.getPurview() & Test_Device)
                {
                    WImage *pTest = new WImage("../Images/test.gif", pSub->elementAt(nRow, 12));
                    if(pTest)
                    {
                        pTest->setStyleClass("hand");
                        char chFunc[128] = {0};
                        sprintf(chFunc, "objoperatebyid('%s','%d');", device->second.getECCIndex().c_str(), SV_TEST);
                        WObject::connect(pTest, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                    }
                }

                new WText(device->second.getShowTime(), pSub->elementAt(nRow, 14));

                pSub->elementAt(nRow, 2)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 4)->setStyleClass("table_data_grid_item_text");
                pSub->elementAt(nRow, 6)->setStyleClass("table_data_grid_item_text");
                pSub->elementAt(nRow, 8)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 10)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 12)->setStyleClass("table_data_grid_item_img");
                pSub->elementAt(nRow, 14)->setStyleClass("table_data_grid_item_text");

                if(nRow % 2 == 0)
                    pSub->GetRow(nRow)->setStyleClass("table_data_grid_item_bg");

                nRow ++;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::refreshTime()
{
    if(m_pTitle)
        m_pTitle->refreshTime();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupView::changePath(const string &szIndex)
{
    if(m_pDepend)
    {
        m_pDepend->clear();

        if(!szIndex.empty())
        {
            PAIRLIST lsPath;
            CEccTreeView::MakePath(szIndex, lsPath);

            if(lsPath.size() >= 1)
            {
                sv_pair svitem;
                while(lsPath.size() > 1)
                {   
                    svitem = lsPath.front();
                    lsPath.pop_front();

                    WText *pName = new WText(svitem.value, m_pDepend->elementAt(0, 0));
                    if(pName)
                    {
                        string szContent = "style='cursor:pointer;' onmouseover='" \
                                "this.style.textDecoration=\"underline\"' " \
                                "onmouseout='this.style.textDecoration=\"none\"'' "
                                "onclick = 'SetCurfocus(\"" + svitem.name + "\");'";

                        strcpy(pName->contextmenu_,  szContent.c_str());
                        pName->setToolTip(svitem.value);
                    }

                    new WText("&nbsp;:&nbsp;", m_pDepend->elementAt(0, 0));
                }

                svitem = lsPath.front();
                lsPath.pop_front();
                WText *pName = new WText(svitem.value, m_pDepend->elementAt(0, 0));
                if(pName)
                {
                    string szContent = "style='cursor:pointer;' onmouseover='" \
                            "this.style.textDecoration=\"underline\"' " \
                            "onmouseout='this.style.textDecoration=\"none\"'' "
                            "onclick = 'window.open(\"SimpleReport.exe?id=";
                    szContent = szContent + svitem.name + "\");'";

                    strcpy(pName->contextmenu_,  szContent.c_str());
                    pName->setToolTip(svitem.value);
                }
            }
        }
    }
}

