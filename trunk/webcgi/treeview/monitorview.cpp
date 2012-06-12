#include "monitorview.h"

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WCheckBox"

#include "basefunc.h"
#include "basedefine.h"
#include "treeview.h"
#include "listtable.h"
#include "statedesc.h"
#include "resstring.h"
#include "rightview.h"
#include "mainview.h"
#include "debuginfor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccMonitorView::CEccMonitorView(WContainerWidget *parent):
WTable(parent),
m_pTitle(NULL),
m_pGeneral(NULL),
m_pMonitorList(NULL),
m_pDepend(NULL),
m_pContent(NULL),
m_pName(NULL),
m_pDescription(NULL),
m_pState(NULL),
m_pDeviceType(NULL),
m_pOSType(NULL),
m_szDeviceID(""),
m_szDTName(""),
m_szNetworkset("")
{    
    setStyleClass("panel");
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::createStateDesc()
{
    int nRow = numRows();
    new CEccStateDesc(elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::createTitle()
{
    int nRow = m_pContent->numRows();
    m_pTitle = new CEccGenTitle(m_pContent->elementAt(nRow, 0));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::initForm()
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
            createMonitorList();
        }
    }

    createStateDesc();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::createGeneral()
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
            new WText(SVResString::getResString("IDS_Device_Type"), pTable->elementAt(2, 0));
            new WText(SVResString::getResString("IDS_State"), pTable->elementAt(3, 0));
            new WText(SVResString::getResString("IDS_Depends_On"), pTable->elementAt(4, 0));

            m_pName = new WText(SVResString::getResString("IDS_Name"), pTable->elementAt(0, 1));
            m_pDescription = new WText(SVResString::getResString("IDS_Description"), pTable->elementAt(1, 1));
            m_pDeviceType = new WText(SVResString::getResString("IDS_Device_Type"), pTable->elementAt(2, 1));
            m_pState = new WText(SVResString::getResString("IDS_State"), pTable->elementAt(3, 1));
            m_pDepend = new WTable(pTable->elementAt(4, 1));
            if(m_pDepend)
                m_pDepend->setStyleClass("widthauto");

            pTable->GetRow(0)->setStyleClass("padding_top");
            pTable->GetRow(1)->setStyleClass("padding_top");
            pTable->GetRow(2)->setStyleClass("padding_top");
            pTable->GetRow(3)->setStyleClass("padding_top");
            pTable->GetRow(4)->setStyleClass("padding_top");

            pTable->elementAt(0, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(1, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(2, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(3, 0)->setStyleClass("table_data_grid_header_text");
            pTable->elementAt(4, 0)->setStyleClass("table_data_grid_header_text");

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
void CEccMonitorView::createMonitorList()
{
    int nRow = m_pContent->numRows();

    m_pMonitorList = new CEccListTable(m_pContent->elementAt(nRow, 0));
    if(m_pMonitorList)
    {
        m_pMonitorList->setTitle(SVResString::getResString("IDS_Monitor_List_Title"));
        m_pMonitorList->setNoChild(SVResString::getResString("IDS_MONITOR_LIST_IS_NULL"));

        list<string> lsCols;
        lsCols.push_back("&nbsp;");
        lsCols.push_back(SVResString::getResString("IDS_State"));
        lsCols.push_back(SVResString::getResString("IDS_State_Description"));
        lsCols.push_back(SVResString::getResString("IDS_Name"));
        lsCols.push_back(SVResString::getResString("IDS_Edit"));
        lsCols.push_back(SVResString::getResString("IDS_Delete"));
        lsCols.push_back(SVResString::getResString("IDS_Refresh_Tip"));
        lsCols.push_back(SVResString::getResString("IDS_Table_Col_Last_Refresh"));
        m_pMonitorList->setCols(lsCols);

        m_pMonitorList->setAddNewTitle(SVResString::getResString("IDS_Add_Monitor"));
        m_pMonitorList->setAddNewTip(SVResString::getResString("IDS_Add_Monitor"));

        m_pMonitorList->setAddNewFunc(AddNewMonitor);

        list<int> lsOperate;
        lsOperate.push_back(SV_ENABLE);
        lsOperate.push_back(SV_DISABLE);
        lsOperate.push_back(SV_DELETE);
        lsOperate.push_back(SV_REFRESH);
        lsOperate.push_back(SV_SORT);
        lsOperate.push_back(SV_COPY);
        lsOperate.push_back(SV_PAST);
        m_pMonitorList->setOperaters(lsOperate, SiteView_ECC_Monitor);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::UpdataGeneralData(const CEccTreeDevice *pNode)
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
void CEccMonitorView::setDeviceNode(const CEccTreeDevice *pNode)
{
    m_szDeviceID = pNode->getECCIndex();
    m_szDTName = pNode->getRealDeviceType();
    m_szNetworkset = pNode->isNetworkSet();
    changePath(pNode->getDependsID());

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

    if(m_pDeviceType)
        m_pDeviceType->setText(pNode->getDeviceType());

    if(m_pMonitorList)
    {
        clearMonitorList();

        m_pMonitorList->setOperatePurview(pNode->getPurview(), SiteView_ECC_Device);
        m_pMonitorList->setCurrentID(pNode->getECCIndex());
        m_pMonitorList->hideNoChild();
        m_pMonitorList->clearCheckList();
        m_pMonitorList->showSubTable();

        WTable *pSub = m_pMonitorList->getListTable();
        if(pSub)
        {
            if(pNode->m_Monitors.empty())
            {
                m_pMonitorList->showNoChild();
            }
            else
            {
                int nRow = pSub->numRows();
                if(pNode->m_Monitors.size() == 1)
                    m_pMonitorList->showHideSort(false);
                else if(pNode->m_Monitors.size() > 1 && pNode->getPurview() & Edit_Device)
                    m_pMonitorList->showHideSort(true);

                map<int, CECCMonitor, less<int> >::const_iterator monitor;
                for(monitor = pNode->m_Monitors.begin(); monitor != pNode->m_Monitors.end(); monitor ++)
                {
                    if(pNode->getPurview() & Edit_Monitor || pNode->getPurview() & Delete_Monitor)
                    {
                        WCheckBox *pCheck = new WCheckBox("", pSub->elementAt(nRow, 0));
                        if(pCheck)
                            m_pMonitorList->addCheckList(monitor->second.getECCIndex(), pCheck);
                    }

                    WImage *pState = new WImage("../Images/state_green.gif", pSub->elementAt(nRow, 2));
                    if(pState)
                    {     
                        pState->setStyleClass("hand");
                        switch(monitor->second.getState())
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

                        if(pNode->getPurview() & Edit_Monitor)
                        {
                            string szUrl = "onclick='showDisableUrl(\"disable.exe?disabletype=2&disableid=" + monitor->second.getECCIndex() 
                                + "\", \"" + CEccMainView::m_szGlobalEvent + "\");'";
                            strcpy(pState->contextmenu_, szUrl.c_str());
                        }
                    }

                    string szState(monitor->second.getShowText());
                    buildHtmlText(szState);
                    if(szState.empty())
                        szState = " ";
                    new WText(szState, pSub->elementAt(nRow, 4));

                    WText *pName = new WText(monitor->second.getName(), pSub->elementAt(nRow, 6));                    
                    if(pName)
                    {
                        string szContent = "style='color:#1E5B99;cursor:pointer;' onmouseover='" \
                                "this.style.textDecoration=\"underline\"' " \
                                "onmouseout='this.style.textDecoration=\"none\"'' "
                                "onclick = 'window.open(\"SimpleReport.exe?id=";
                        szContent = szContent + monitor->second.getECCIndex() + "\");'";
                        
                        strcpy(pName->contextmenu_,  szContent.c_str());
                        pName->setToolTip(monitor->second.getName());
                    }
                    
                    if(pNode->getPurview() & Edit_Monitor)
                    {
                        WImage *pEdit = new WImage("../Images/edit.gif",  pSub->elementAt(nRow, 8));
                        if(pEdit)
                        {
                            pEdit->setStyleClass("hand");
                            char chFunc[128] = {0};
                            sprintf(chFunc, "objoperatebyid('%s','%d');", monitor->second.getECCIndex().c_str(), SV_EDIT);
                            WObject::connect(pEdit, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                        }
                    }

                    if(pNode->getPurview() & Delete_Monitor)
                    {
                        WImage *pDel = new WImage("../Images/delete.gif", pSub->elementAt(nRow, 10));
                        if(pDel)
                        {
                            pDel->setStyleClass("hand");
                            char chFunc[128] = {0};
                            sprintf(chFunc, "objoperatebyid('%s','%d');", monitor->second.getECCIndex().c_str(), SV_DELETE);
                            WObject::connect(pDel, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
                        }
                    }

                    if(pNode->getPurview() & Refresh_Monitor)
                    {
                        WImage *pRefresh = new WImage("../Images/refresh.gif", pSub->elementAt(nRow, 12));
                        if(pRefresh)
                        {
                            pRefresh->setStyleClass("hand");
                            string szContent = "onclick='refreshmonitors(\"refresh.exe?monitorid=" + monitor->second.getECCIndex() + "\");";
                            szContent += "update(\"" + CEccMainView::m_szGlobalEvent + "\");'";
                            strcpy(pRefresh->contextmenu_, szContent.c_str());
                        }
                    }

                    new WText(monitor->second.getShowTime(), pSub->elementAt(nRow, 14));

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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::clearMonitorList()
{
    WTable *pSub = m_pMonitorList->getListTable();
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
void CEccMonitorView::AddNewMonitor(string szIndex)
{
    PrintDebugString("Device ID is : " + CEccRightView::m_pMonitorview->m_szDeviceID);
    CEccRightView::showAddMonitor1st(CEccRightView::m_pMonitorview->m_szDeviceID, 
                                        CEccRightView::m_pMonitorview->m_szDTName, 
                                        CEccRightView::m_pMonitorview->m_szNetworkset);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::refreshTime()
{
    if(m_pTitle)
        m_pTitle->refreshTime();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMonitorView::changePath(const string &szIndex)
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

