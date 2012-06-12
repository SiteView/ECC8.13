#include "listtable.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WebSession.h"

#include "basedefine.h"
#include "eccobjfunc.h"
#include "debuginfor.h"
#include "pushbutton.h"
#include "resstring.h"
#include "rightview.h"
#include "mainview.h"
#include "treeview.h"

#include "../userright/User.h"

#include "../base/OperateLog.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccListTable::CEccListTable(WContainerWidget *parent, bool bHasOperate, bool bCreateHasNo, bool bGridTable,
                             bool bControl):
WTable(parent),
m_pPath(NULL),
m_pSubTable(NULL),
m_pOperate(NULL),
m_pSubOperate(NULL),
m_pControl(NULL),
m_pNoChild(NULL),
m_pHideButton(NULL),
m_pAddNew(NULL),
m_szCurrentID("")
{
    m_bShowSub = true;
    m_bHasChild = false;
    m_bSetFunc = false;

    initForm(bHasOperate, bCreateHasNo, bGridTable, bControl);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ñ����ı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setTitle(string szTitle)
{
    if(m_pTitle)
        m_pTitle->setText(szTitle);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::createOpaerate(WTable *pSubTable)
{
    int nRow = pSubTable->numRows();
    m_pOperate = new WTable(pSubTable->elementAt(nRow, 0));
    if(m_pOperate)
    {
        m_pOperate->setStyleClass("padding_3");

        // ����ȫѡ ȫ��ѡ ��ѡ����click�¼�
        WText *pSelAll = new WText(SVResString::getResString("IDS_All_Select"), m_pOperate->elementAt(0, 0));
        new WText("&nbsp;", m_pOperate->elementAt(0, 0));

        WText *pSelNone = new WText(SVResString::getResString("IDS_None_Select"), m_pOperate->elementAt(0, 0));
        new WText("&nbsp;", m_pOperate->elementAt(0, 0));

        WText *pInvertSel = new WText(SVResString::getResString("IDS_Invert_Select"), m_pOperate->elementAt(0, 0));
        
        if(pSelAll)
        {
            pSelAll->setStyleClass("tgrouptitle");
            WObject::connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelectAll()));
        }

        if(pSelNone)
        {
            pSelNone->setStyleClass("tgrouptitle");
            WObject::connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelectNone()));
        }

        if(pInvertSel)
        {
            pInvertSel->setStyleClass("tgrouptitle");
            WObject::connect(pInvertSel, SIGNAL(clicked()), this, SLOT(InvertSelect()));
        }

        // �����Ӳ�����
        m_pSubOperate = new WTable(m_pOperate->elementAt(1, 0));
        if(m_pSubOperate)
        {
            WTable * pSubOpt = new WTable(m_pSubOperate->elementAt(0, 1));
            if(pSubOpt)
            {
                pSubOpt->setStyleClass("widthauto");
                // ���� add new
                m_pAddNew = new CEccImportButton("Add New", "Add New", "../Images/button_bg_add_black.png", pSubOpt->elementAt(0, 0));
                if(m_pAddNew)
                    WObject::connect(m_pAddNew, SIGNAL(clicked()), "showbar();", this, SLOT(AddNew()), 
                        WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            }
            m_pSubOperate->elementAt(0, 1)->setContentAlignment(AlignRight);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������ݱ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::createSubTable(WTable *pSubTable, bool bGridTable)
{
    int nRow = pSubTable->numRows();

    WTable *pSub = new WTable(pSubTable->elementAt(nRow, 0));
    if(pSub)
    {
        pSub->setStyleClass("panel_item");
        WScrollArea *pScroll = new WScrollArea(pSubTable->elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel_item");
        }

        m_pSubTable = new WTable(pSub->elementAt(0, 0));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::createTitle(bool bControl)
{
    int nRow = numRows();

    m_pPath = new WTable(elementAt(nRow, 1));
    new WImage("../Images/table_shadow_left.png", elementAt(nRow, 0));
    new WImage("../Images/table_shadow_right.png", elementAt(nRow, 2));
    elementAt(nRow, 0)->setStyleClass("table_shadow_l");
    elementAt(nRow, 2)->setStyleClass("table_shadow_r");
    if(m_pPath)
    {
        elementAt(nRow, 1)->setStyleClass("table_title");
        m_pTitle = new WText("", m_pPath->elementAt(0, 0));
        m_pPath->elementAt(0, 0)->setStyleClass("table_title_text");
        
        if(bControl)
        {
            m_pControl = new WImage("../Images/table_pucker.png", m_pPath->elementAt(0, 1));
            m_pPath->elementAt(0, 1)->setContentAlignment(AlignRight);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �õ������б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WTable * CEccListTable::getListTable()
{
    return m_pSubTable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::initForm(bool bHasOperate, bool bCreateNoChild, bool bGridTable, bool bControl)
{
    createTitle(bControl);

    int nRow = numRows();
    WTable *pSub = new WTable(elementAt(nRow, 1));
    new WImage("../Images/table_shadow_left.png", elementAt(nRow, 0));
    new WImage("../Images/table_shadow_right.png", elementAt(nRow, 2));
    elementAt(nRow, 0)->setStyleClass("table_shadow_l");
    elementAt(nRow, 2)->setStyleClass("table_shadow_r");
    if(pSub)
    {
        m_nHideRow = nRow;
        if(m_pControl)
        {
            sprintf(((WTableCell*)m_pControl->parent())->contextmenu_, 
                "width='13px' height='17px' style='CURSOR:pointer' onclick='listtableclick(\"%s\",\"%s\")'",
                m_pControl->formName().c_str(),
                GetRow(m_nHideRow)->formName().c_str());
        }

        if(bGridTable)
            pSub->setStyleClass("table_data_grid");
        else
            pSub->setStyleClass("table_data_input");

        createSubTable(pSub, bGridTable);

        if(bCreateNoChild)
        {
            int nRow = pSub->numRows();
            m_pNoChild = new WText("no child", pSub->elementAt(nRow, 0));
            if(m_pNoChild)
                m_pNoChild->setStyleClass("required");

            pSub->elementAt(nRow, 0)->setContentAlignment(AlignCenter);
        }

        if(bHasOperate)
        {
            createOpaerate(pSub);
            createHideConfirm(pSub);
        }
    }

    nRow = numRows();
    new WImage("../Images/table_shadow_bottom.gif", elementAt(nRow, 1));
    elementAt(nRow, 0)->setStyleClass("table_shadow_l");
    elementAt(nRow, 1)->setStyleClass("table_shadow_bom");
    elementAt(nRow, 2)->setStyleClass("table_shadow_r");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ñ�ı�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setCols(list<string> &lsCols)
{
    if(m_pSubTable)
    {
        string szCol("");
        int nCols = 0;
        while(lsCols.size() > 0)
        {
            szCol = lsCols.front();
            lsCols.pop_front();
            if(nCols != 0)
            {
                new WImage("../Images/table_head_space.png", m_pSubTable->elementAt(0, nCols));
                new WImage("../Images/space.gif", m_pSubTable->elementAt(0, nCols));
                m_pSubTable->elementAt(0, nCols)->setStyleClass("width4");
                nCols ++;
            }

            new WText(szCol, m_pSubTable->elementAt(0, nCols));

            m_pSubTable->elementAt(0, nCols)->setStyleClass("table_data_grid_header_text");
            m_pSubTable->elementAt(0, nCols)->setContentAlignment(AlignCenter);
            nCols ++;
        }
        m_pSubTable->GetRow(0)->setStyleClass("table_data_grid_header");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ò���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setOperaters(list<int> &lsOperaters, int nType)
{
    if(m_pSubOperate)
    {
        m_nDataType = nType;
        WTable *pSub = new WTable(m_pSubOperate->elementAt(0, 0));
        if(pSub)
        {
            pSub->setStyleClass("widthAuto");
            int nCol = 0;
            list<int>::iterator item;
            for(item = lsOperaters.begin(); item != lsOperaters.end(); item ++)
            {
                CEccButton *pOperate = NULL;
                switch((*item))
                {
                case SV_ENABLE:             // ����
                    pOperate = new CEccButton(SVResString::getResString("IDS_Enable"), "",
                        "../Images/button_bg_start.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(Enable()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_ENABLE] = pOperate;
                    }
                    break;
                case SV_DISABLE:            // ����
                    pOperate = new CEccButton(SVResString::getResString("IDS_Disable"), "",
                        "../Images/button_bg_stop.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(Disable()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_DISABLE] = pOperate;
                    }
                    break;
                case SV_DELETE:             // ɾ��
                    pOperate = new CEccButton(SVResString::getResString("IDS_Delete"), "",
                        "../Images/button_bg_del.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(DelSelect()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_DELETE] = pOperate;
                    }
                    break;
                case SV_REFRESH:           // ˢ��
                    pOperate = new CEccButton(SVResString::getResString("IDS_Refresh_Tip"), "", 
                        "../Images/button_bg_refresh.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(RefreshSel()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_REFRESH] = pOperate;
                    }
                    break;
                case SV_SORT:               // ����
                    pOperate = new CEccButton(SVResString::getResString("IDS_Sort"), "", 
                        "../Images/button_bg_taxis.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(Sort()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_SORT] = pOperate;
                    }
                    break;
                case SV_COPY:              // ����
                    pOperate = new CEccButton(SVResString::getResString("IDS_Copy"), "", 
                        "../Images/button_bg_copy.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(Copy()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_COPY] = pOperate;
                    }
                    break;
                case SV_PAST:               // ճ��
                    pOperate = new CEccButton(SVResString::getResString("IDS_Past"), "",
                        "../Images/button_bg_plaster.png", pSub->elementAt(0, nCol));
                    if(pOperate)
                    {
                        WObject::connect(pOperate, SIGNAL(clicked()), "showbar();", this, SLOT(Paste()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_OperateList[SV_PAST] = pOperate;
                    }
                    break;
                }
                if(pOperate)
                {
                    pOperate->setStyleClass("hand");
                }
                nCol ++;
                new WText("&nbsp;", pSub->elementAt(0, nCol));
                nCol ++;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ���������ӱ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::ShowHideSub()
{
    if(m_bShowSub)
    {
        m_pControl->setImageRef("../Images/table_unwrap.png");
        
        elementAt(m_nHideRow, 0)->hide();
        elementAt(m_nHideRow, 1)->hide();
        elementAt(m_nHideRow, 2)->hide();

        if(m_pNoChild)
        {
            int nRow = static_cast<WTableCell*>(m_pNoChild->parent())->row();
            GetRow(nRow)->hide();
        }
    }
    else
    {
        m_pControl->setImageRef("../Images/table_pucker.png");

        elementAt(m_nHideRow, 0)->show();
        elementAt(m_nHideRow, 1)->show();
        elementAt(m_nHideRow, 2)->show();

        if(m_pNoChild && !m_bHasChild)
        {
            int nRow = static_cast<WTableCell*>(m_pNoChild->parent())->row();
            GetRow(nRow)->show();
        }
    }
    m_bShowSub = !m_bShowSub;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����ӱ�ĸ߶�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setHeight(int nHeight)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setWidth(int nWidth)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ���������ı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::showNoChild()
{
    m_bHasChild = false;
    if(m_pNoChild)
    {
        m_pNoChild->show();
    }

    showHideSort(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����������ı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::hideNoChild()
{
    m_bHasChild = true;
    if(m_pNoChild)
    {
        m_pNoChild->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������������ʾ�ı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setNoChild(string szText)
{
    if(m_pNoChild)
        m_pNoChild->setText("<BR>" + szText);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȫѡ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::SelectAll()
{
    map<string, WCheckBox*, less<string> >::iterator it;
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
        it->second->setChecked(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȡ��ȫѡ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::SelectNone()
{
    map<string, WCheckBox*, less<string> >::iterator it;
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
        it->second->setChecked(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ѡ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::InvertSelect()
{
    map<string, WCheckBox*, less<string> >::iterator it;
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
        it->second->setChecked(!it->second->isChecked());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����add new��ť����ʾ�ı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setAddNewTitle(string szTitle)
{
    if(m_pAddNew)
        m_pAddNew->setText(szTitle);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����add new��ť����ʾ��Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setAddNewTip(string szToolTip)
{
    if(m_pAddNew)
        m_pAddNew->setToolTip(szToolTip);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����checkbox�������Ķ�Ӧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::addCheckList(string szIndex, WCheckBox *pCheck)
{
    m_lsCheckBox[szIndex] = pCheck;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���checkbox�������Ķ�Ӧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::clearCheckList()
{
    m_lsCheckBox.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::AddNew()
{
    unsigned long ulStart = GetTickCount();
    if(m_bSetFunc)
        m_pAddFunc(m_szCurrentID);
    else
        WebSession::js_af_up = "hiddenbar();";

    string szOpt("");

    switch(m_nDataType)
    {
    case SiteView_ECC_Group:
        szOpt = "Add new group";
        break;
    case SiteView_ECC_Device:
        szOpt = "Add new Device";
        break;
    case SiteView_ECC_Monitor:
        szOpt = "Add new Monitor";
        break;
    }


    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.AddNew", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.AddNew", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����add new�ĵ��ú���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setAddNewFunc(void (*pfunc)(string))
{
    m_bSetFunc = true;
    m_pAddFunc = pfunc;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���õ�ǰ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setCurrentID(string szCurrentID)
{
    m_szCurrentID = szCurrentID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ�ӱ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::showSubTable()
{
    m_bShowSub = true;

    GetRow(m_nHideRow)->show();
    
    if(m_pControl)
        m_pControl->setImageRef("../Images/table_pucker.png");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����ӱ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::hideSubTable()
{
    m_bShowSub = false;

    GetRow(m_nHideRow)->hide();

    if(m_pControl)
        m_pControl->setImageRef("../Images/table_unwrap.png");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::Copy()
{
    unsigned long ulStart = GetTickCount();

    string szCmd("hiddenbar();");

    // ѡ��list���
    m_lsSelIndex.clear();

    map<string, WCheckBox*, less<string> >::iterator it;
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
        if(it->second->isChecked())
            m_lsSelIndex.push_back(it->first);

    WebSession::js_af_up = szCmd;
    string szOpt("");

    switch(m_nDataType)
    {
    case SiteView_ECC_Device:
        szOpt = "Copy Device";
        break;
    case SiteView_ECC_Monitor:
        szOpt = "Copy Monitor";
        break;
    }


    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Copy", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Copy", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ɾ����ѡ����ȷ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::DelSelect()
{
    string szCmd("hiddenbar();");

    string szOpt("");

    unsigned long ulStart = GetTickCount();

    //? ��ʾȷ����Ϣ�����ݲ�ͬ������
    map<string, WCheckBox*, less<string> >::iterator it;

    if(m_pHideButton && !m_pHideButton->getEncodeCmd("xclicked()").empty())
    {
        for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
        {
            if(it->second->isChecked())
            {
                string szClick = m_pHideButton->getEncodeCmd("xclicked()");

                if(m_nDataType == SiteView_ECC_Group)
                {
                    szOpt = "Delete Group";
                    szCmd = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Sel_Group_Confirm") + "\",'"  +
                                SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szClick + "');hiddenbar();" ;
                }
                else if(m_nDataType == SiteView_ECC_Device)
                {
                    szOpt = "Delete Device";
                    szCmd = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Sel_Device_Confirm") + "\",'"  +
                                SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szClick + "');hiddenbar();" ;
                }
                else if(m_nDataType == SiteView_ECC_Monitor)
                {
                    szOpt = "Delete Monitor";
                    szCmd = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Monitor_Confirm") + "\",'"  +
                                SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szClick + "');hiddenbar();" ;
                }
                break;
            }
        }
    }
    else
    {
        PrintDebugString("confirm button create failed");
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.DelSelect", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.DelSelect", szOpt, 
        0, GetTickCount() - ulStart);

    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ֹ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::Disable()
{
    string szCmd("hiddenbar();");
    map<string, WCheckBox*, less<string> >::iterator it;

    list<string> lsSelMonitor;
    list<string>::iterator lstItem;

    bool bSelect = false;

    unsigned long ulStart = GetTickCount();

    string szOpt("");

    // �Ƿ������õĶ���
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
    {
        if(it->second->isChecked())
        {
            bSelect = true;
            if(!isDisable(it->first, m_nDataType))
                lsSelMonitor.push_back(it->first);
        }
    }
    if(!lsSelMonitor.empty())
    {
        // ����ѡ������ѹ�����
        string szQueueName = makeQueueName();
        CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        list<string>::iterator lsItem;
        for(lsItem = lsSelMonitor.begin(); lsItem != lsSelMonitor.end(); lsItem++)
        {
            int nSize = static_cast<int>((*lsItem).length()) + 2;
            char * pszIndex = new char[nSize];
            if(pszIndex)
            {
                memset(pszIndex, 0, nSize);
                strcpy(pszIndex, (*lsItem).c_str());

                if(!::PushMessage(szQueueName, "SV_INDEX", pszIndex, nSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                    PrintDebugString("PushMessage into queue failed!");
                delete []pszIndex;
            }
        }
        char pEnd[2] = {0};
        if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
            PrintDebugString("PushMessage into queue failed!");

        string szDisable("showDisableUrl('disable.exe?disabletype=");
        switch(m_nDataType)
        {
        case SiteView_ECC_Group:
            szOpt = "Disable Group";
            szDisable += "0";
            break;
        case SiteView_ECC_Device:
            szOpt = "Disable Device";
            szDisable += "1";
            break;
        case SiteView_ECC_Monitor:
            szOpt = "Disable Monitor";
            szDisable += "2";
            break;
        }
        szDisable += "&operatetype=0&queuename=" + szQueueName + "', '" + CEccMainView::m_szGlobalEvent + "');";
        WebSession::js_af_up = szDisable;
    }
    else if(bSelect)
    {
        // ȫ���ѽ��ã���������������ʾ��ͬ����ʾ��Ϣ
        switch(m_nDataType)
        {
        case SiteView_ECC_Group:
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Disable") +  
            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
            break;
        case SiteView_ECC_Device:
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Disable") +  
            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
            break;
        case SiteView_ECC_Monitor:
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Monitor_Can_not_Disable") +  
            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
            break;
        }
    }
    else
    {
        WebSession::js_af_up = "hiddenbar();";
    }

    //string szOpt("");

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Disable", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Disable", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::Enable()
{
    string szCmd("hiddenbar();");
    map<string, WCheckBox*, less<string> >::iterator it;

    list<string> lsSelMonitor;
    list<string>::iterator lstItem;

    bool bSelect = false;

    unsigned long ulStart = GetTickCount();

    string szOpt("");

    // �Ƿ��б���ֹ�Ķ���
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
    {
        if(it->second->isChecked())
        {
            bSelect = true;
            if(isDisable(it->first, m_nDataType))
                lsSelMonitor.push_back(it->first);
        }
    }
    if(!lsSelMonitor.empty())
    {
        // ����ѡ������ѹ�����
        string szQueueName = makeQueueName();
        CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        list<string>::iterator lsItem;
        for(lsItem = lsSelMonitor.begin(); lsItem != lsSelMonitor.end(); lsItem++)
        {
            int nSize = static_cast<int>((*lsItem).length()) + 2;
            char * pszIndex = new char[nSize];
            if(pszIndex)
            {
                memset(pszIndex, 0, nSize);
                strcpy(pszIndex, (*lsItem).c_str());

                if(!::PushMessage(szQueueName, "SV_INDEX", pszIndex, nSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                    PrintDebugString("PushMessage into queue failed!");
                delete []pszIndex;
            }
        }
        char pEnd[2] = {0};
        if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
            PrintDebugString("PushMessage into queue failed!");

        string szDisable("showDisableUrl('disable.exe?disabletype=");
        switch(m_nDataType)
        {
        case SiteView_ECC_Group:
            szOpt = "Enable Group";
            szDisable += "0";
            break;
        case SiteView_ECC_Device:
            szOpt = "Enalbe Device";
            szDisable += "1";
            break;
        case SiteView_ECC_Monitor:
            szOpt = "Enalbe Monitor";
            szDisable += "2";
            break;
        }
        szDisable += "&operatetype=1&queuename=" + szQueueName + "', '" + CEccMainView::m_szGlobalEvent + "');";
        WebSession::js_af_up = szDisable;
    }
    else if(bSelect)
    {
        // ȫ�������ã���������������ʾ��ͬ����ʾ��Ϣ
        switch(m_nDataType)
        {
        case SiteView_ECC_Group:
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Enable") +  
            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
            break;
        case SiteView_ECC_Device:
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Enable") +  
            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
            break;
        case SiteView_ECC_Monitor:
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Monitor_Can_not_Enable") +  
            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
            break;
        }
    }
    else
    {
        WebSession::js_af_up = "hiddenbar();";
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Enable", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Enable", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ճ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::Paste()
{
    unsigned long ulStart = GetTickCount();

    string szOpt("");

    // ѡ���б�Ϊ��
    if(!m_lsSelIndex.empty())
    {
        // �Ƿ���Ա�ճ��
        if(!IsCanBePaste())
        {
            // ��ʾ������Ϣ
            WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
        }
        else
        {
            // �����������͵���ճ������
            if(m_nDataType == SiteView_ECC_Monitor)
            {
                szOpt = "paste monitor";
                // ճ�������
                pasteMonitor();
            }
            else
            {
                szOpt = "paste Device";
                // ճ���豸
                pasteDevice();
                
                WebSession::js_af_up = "hiddenbar()";
            }
        }
    }
    else
    {
        WebSession::js_af_up = "hiddenbar()";
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Paste", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Paste", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˢ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::RefreshSel()
{
    string szCmd("hiddenbar();");

    list<string> lsSelMonitor;
    list<string>::iterator lstItem;

    unsigned long ulStart = GetTickCount();

    // 
    map<string, WCheckBox*, less<string> >::iterator it;
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
        if(it->second->isChecked())
            lsSelMonitor.push_back(it->first);

    if(!lsSelMonitor.empty())
    {
        string szQuery("");

        string szQueueName(makeQueueName());
        CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        string szRefreshQueue(getRefreshQueueName(m_szCurrentID));
        CreateQueue(szRefreshQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

        for(lstItem = lsSelMonitor.begin(); lstItem != lsSelMonitor.end(); lstItem ++)
        {
            if(isDisable((*lstItem), SiteView_ECC_Monitor))
            {
                int nSize = static_cast<int>((*lstItem).length()) + 2;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, (*lstItem).c_str());
                    if(!::PushMessage(szQueueName, sv_disable_sign, pszRefreshMonitor, nSize, CEccMainView::m_szIDCUser, 
                        CEccMainView::m_szAddr))
                        PrintDebugString("PushMessage into queue failed!");
                    delete []pszRefreshMonitor;
                }
            }
            else
            {
                szQuery += (*lstItem);
                szQuery += "\v";
            }
        }

        int nSize = static_cast<int>(szQuery.length()) + 2;
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
            
            if(szQuery.empty())
            {
                if(!::PushMessage(szQueueName, sv_refresh_end_sign, pszRefreshMonitor, nSize, CEccMainView::m_szIDCUser, 
                    CEccMainView::m_szAddr))
                    PrintDebugString("PushMessage into queue failed!");          
            }
            else
            {
                if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, CEccMainView::m_szIDCUser, 
                    CEccMainView::m_szAddr))
                    PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            }
            delete [] pszRefreshMonitor;
        }

        //? ����ˢ��
        WebSession::js_af_up = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');" + 
            "update('" + CEccMainView::m_szGlobalEvent + "');";
    }
    else
        WebSession::js_af_up = szCmd;

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.RefreshSel", "Refresh Monitor", 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.RefreshSel", "Refresh Monitor", 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::Sort()
{
    unsigned long ulStart = GetTickCount();

    string szCmd("hiddenbar();");
    CEccRightView::showSortForm(m_szCurrentID, m_nDataType);
    WebSession::js_af_up = szCmd;

    string szOpt("");
    switch(m_nDataType)
    {
    case SiteView_ECC_Group:
        szOpt = "Sort Group";
        break;
    case SiteView_ECC_Device:
        szOpt = "Sort Device";
        break;
    case SiteView_ECC_Monitor:
        szOpt = "Sort Monitor";
        break;
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Sort", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Sort", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ճ���豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::pasteDevice()
{
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentID);
    if(pNode)
    {
        if(pNode->getType() == SiteView_ECC_Group || pNode->getType() == SiteView_ECC_SE)
        {
            list<string>::iterator it;
            for(it = m_lsSelIndex.begin(); it != m_lsSelIndex.end(); it ++)
                PasteDevice(m_szCurrentID, (*it));
            
            CEccMainView::m_pRightView->clearNewMonitorList();
            CEccMainView::m_pRightView->changeActive(pNode);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ճ�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::pasteMonitor()
{
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentID);
    if(pNode)
    {
        if(pNode->getType() == SiteView_ECC_Device)
        {
            CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));

            list<string>::iterator lsItem;
            string szNewMonitorID(""), szName("");
            int nMTID = 0;

            for(lsItem = m_lsSelIndex.begin(); lsItem != m_lsSelIndex.end(); lsItem ++)
            {
                szNewMonitorID = "";                
                szName = getMonitorNameMTID((*lsItem), nMTID);
                if(pDevice->MTCanUsing(nMTID))
                {
                    szNewMonitorID = MonitorCopy((*lsItem), m_szCurrentID);
                    if(!szNewMonitorID.empty())
                    {
                        
                        InsertTable(szNewMonitorID, nMTID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

                        CEccTreeView::m_SVSEUser.AddUserScopeAllRight(szNewMonitorID, SiteView_ECC_Monitor);

                        CEccMainView::m_pRightView->InsertNewMonitorList(szNewMonitorID);
                    }
                }
            }
        }
        
        if(!CEccMainView::m_pRightView->isNewMonitorListEmpty())
        {
            // ˢ����ӵļ����
            CEccMainView::m_pTreeView->BuildSEShowText(FindSEID(m_szCurrentID));
            CEccMainView::m_pRightView->changeActive(pNode);
            WebSession::js_af_up = CEccMainView::m_pRightView->refreshNewMonitors();// + "hiddenbar();";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �Ƿ��ܱ�ճ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccListTable::IsCanBePaste()
{
    if(m_nDataType == SiteView_ECC_Monitor)
    {// �����
        // �õ���ǰ�豸
        const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentID);
        if(pNode)
        {
            if(pNode->getType() == SiteView_ECC_Device)
            {
                CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                if(pDevice->isNetworkSet() == "true")
                {// �豸�������豸
                    // �Ѿ�ʹ�õ������豸����
                    int nNetworkCount = getUsingNetworkCount();
                    // �����������ȥ�������������豸�����ڵļ����������
                    int nMonitorCount = pDevice->getMointorCount() % 30 + static_cast<int>(m_lsSelIndex.size());

                    // ������������� 30�����¼��������豸����
                    if(nMonitorCount > 30)
                        nNetworkCount = nNetworkCount + nMonitorCount / 30;

                    // ���
                    return checkNetworkPoint(nNetworkCount);
                }
                else
                {
                    // ��ʹ�õ������豸
                    int nMonitorCount = getUsingMonitorCount() + static_cast<int>(m_lsSelIndex.size());
                    return checkMonitorsPoint(nMonitorCount);
                }
            }
        }
    }
    else if(m_nDataType == SiteView_ECC_Device)
    {// �����������豸
        list<string>::iterator it;

        // �õ���ǰ�Ѿ�ʹ�õ������豸�����ͼ��������
        int nNetworkCount = getUsingNetworkCount();
        int nMonitorCount = getUsingMonitorCount();
        
        bool bCanPaste = true;
        // ö�������Ѿ�ѡ�������
        for(it = m_lsSelIndex.begin(); it != m_lsSelIndex.end(); it ++)
        {
            // �õ��ڵ�
            const CEccTreeNode *pDevNode = CEccTreeView::getECCObject((*it));
            if(pDevNode)
            {
                // �ڵ����豸
                if(pDevNode->getType() == SiteView_ECC_Device)
                {
                    CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pDevNode));
                    if(pDevice->isNetworkSet() == "true")
                    {// �豸�������豸
                        // ��ճ���豸�ļ��������
                        int nDevCount = pDevice->getMointorCount();
                        // ���������豸����
                        if(nDevCount == 30)
                            nNetworkCount ++;
                        else
                            nNetworkCount = nNetworkCount + nDevCount / 30 + 1;
                        // �Ƿ���Կ���
                        bCanPaste = checkNetworkPoint(nNetworkCount);
                    }
                    else
                    {
                        // ����ʹ�ü��������
                        nMonitorCount += pDevice->getMointorCount();
                        // �Ƿ����ʹ��
                        bCanPaste = checkMonitorsPoint(nMonitorCount);
                    }
                }
                // ����ճ��
                if(!bCanPaste)
                    return false;
            }
        }

        return bCanPaste;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ȷ�ϰ�ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::createHideConfirm(WTable *pSubTable)
{
    int nRow = pSubTable->numRows();

    m_pHideButton = new WPushButton("", pSubTable->elementAt(nRow, 0));
    if(m_pHideButton)
    {
        WObject::connect(m_pHideButton, SIGNAL(clicked()), "showbar();", this, SLOT(Confirm()), 
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        m_pHideButton->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȷ��ɾ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::Confirm()
{
    string szOpt("");

    unsigned long ulStart = GetTickCount();

    switch(m_nDataType)
    {
    case SiteView_ECC_Group:
        szOpt = "Delete group";
        break;
    case SiteView_ECC_Device:
        szOpt = "Delete Device";
        break;
    case SiteView_ECC_Monitor:
        szOpt = "Delete Monitor";
        break;
    }


    map<string, WCheckBox*, less<string> >::iterator it;
deletebegin:
    for(it = m_lsCheckBox.begin(); it != m_lsCheckBox.end(); it ++)
    {
        if(it->second->isChecked())
        {
            if(m_nDataType == SiteView_ECC_Group)
                CEccTreeView::DeleteGroupByID(it->first);
            else if(m_nDataType == SiteView_ECC_Device)
                CEccTreeView::DeleteDeviceByID(it->first);
            else if(m_nDataType == SiteView_ECC_Monitor)
            {
                //? ��¼��־
                DeleteSVMonitor(it->first, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                DeleteTable(it->first, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

                const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentID);
                if(pNode)
                {
                    CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                    map<int, CECCMonitor, less<int> >::iterator monitoritem;
                    for(monitoritem = pDevice->m_Monitors.begin(); monitoritem != pDevice->m_Monitors.end(); monitoritem ++)
                    {
                        if(monitoritem->second.m_szIndex == it->first)
                        {
                            string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Group") +
                                "(Index)" + it->first + "---" + SVResString::getResString("IDS_Name") + ":" 
                                + monitoritem->second.m_szName + "---parent id is " + pDevice->getECCIndex() + 
                                "---" + SVResString::getResString("IDS_Name") + ":" + pDevice->getName();

                            CEccTreeView::AddOperaterLog(SV_DELETE, SiteView_ECC_Monitor, szMsg);

                            pDevice->m_Monitors.erase(monitoritem);
                            break;
                        }
                    }
                }
            }
            int nRow = static_cast<WTableCell*>(it->second->parent())->row();
            m_pSubTable->deleteRow(nRow);

            m_lsCheckBox.erase(it);
            goto deletebegin;
        }
    }

    if(m_lsCheckBox.empty())
            this->showNoChild();

    WebSession::js_af_up = "hiddenbar();";

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Confirm", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccListTable.Confirm", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ò���Ȩ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::setOperatePurview(int nPurview, int nType)
{
    map<int, CEccButton*, less<int> >::iterator  it;

    for(it = m_OperateList.begin(); it != m_OperateList.end(); it ++)
        it->second->hide();

    if(m_pAddNew)
        m_pAddNew->hide();

    bool bHasAdd = false, bHasDel = false, bHasEdit = false;

    if(nType == SiteView_ECC_Group && nPurview & Add_Group)
        bHasAdd = true;
    else if(nType == SiteView_ECC_Group && nPurview & Add_Device)
        bHasAdd = true;
    else if(nType == SiteView_ECC_Device && nPurview & Add_Monitor)
        bHasAdd = true;

    if(bHasAdd)
    {
        if(m_pAddNew)
            m_pAddNew->show();

        it = m_OperateList.find(SV_PAST);
        if(it != m_OperateList.end())
            it->second->show();
    }

    if(nType == SiteView_ECC_Group && nPurview & Edit_Group)
        bHasEdit = true;
    else if(nType == SiteView_ECC_Group && nPurview & Edit_Device)
        bHasEdit = true;
    else if(nType == SiteView_ECC_Device && nPurview & Edit_Device)
        bHasEdit = true;

    if(bHasEdit)
    {
        it = m_OperateList.find(SV_ENABLE);
        if(it != m_OperateList.end())
            it->second->show();

        it = m_OperateList.find(SV_DISABLE);
        if(it != m_OperateList.end())
            it->second->show();

        it = m_OperateList.find(SV_COPY);
        if(it != m_OperateList.end())
            it->second->show();
    }

    if(nPurview & Refresh_Device)
    {
        it = m_OperateList.find(SV_REFRESH);
        if(it != m_OperateList.end())
            it->second->show();
    }

    if(nType == SiteView_ECC_Group && nPurview & Delete_Group)
        bHasDel = true;
    else if(nType == SiteView_ECC_Group && nPurview & Delete_Device)
        bHasDel = true;
    else if(nType == SiteView_ECC_Device && nPurview & Delete_Monitor)
        bHasDel = true;

    if(bHasDel)
    {
        it = m_OperateList.find(SV_DELETE);
        if(it != m_OperateList.end())
            it->second->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccListTable::showHideSort(bool bShow)
{
    map<int, CEccButton*, less<int> >::iterator it;
    it = m_OperateList.find(SV_SORT);
    if(it != m_OperateList.end())
    {
        if(bShow)
            it->second->show();
        else
            it->second->hide();
    }
}
