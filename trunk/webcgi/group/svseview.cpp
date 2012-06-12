#include "svseview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/libutil/time.h"

#include "resstring.h"

extern void PrintDebugString(const string &szMsg);



SVSEView::SVSEView(WContainerWidget *parent, CUser * pUser, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pSVUser = pUser;

    //m_pBtnHideDel = NULL;
    //m_pAdd = NULL;
    //m_pDel = NULL;
    //m_pDel_g = NULL;

    //loadString();
    initForm();
    setStyleClass("t1");
}

void SVSEView::SetUserPwd(string &szUser, string &szPwd)
{
}

void SVSEView::EditSEView(string &szName, string &szIndex)
{
    editSVSEList(szName, szIndex);
}

void SVSEView::enterSVSE(const std::string szSEID)
{
    emit showSVSE(szSEID);
}


void SVSEView::initForm()
{
    createTitle();
    createSEList();
    enumSVSE();
}

void SVSEView::refreshSElist()
{
    if(m_pSEList)
    {
        while ( m_pSEList->numRows() > 1)
        {
            m_pSEList->deleteRow(m_pSEList->numRows() - 1);
        }
    }
    m_svSEList.clear();
    enumSVSE();
}

void SVSEView::enumSVSE()
{
    PAIRLIST lsSVSE;
    PAIRLIST::iterator lsItem; 
    if(m_pSVUser)
    {
        if(GetAllSVSEInfo(lsSVSE, m_szIDCUser, m_szIDCPwd))
        {
            for(lsItem = lsSVSE.begin(); lsItem != lsSVSE.end(); lsItem++)
            {
                string szSEID = (*lsItem).name;
                string szName = (*lsItem).value;
                bool bHasRight = true;
                if(m_pSVUser)
                    bHasRight = m_pSVUser->haveGroupRight(szSEID, Tree_SE);
                if(bHasRight)
                    addSVSEList(szName, szSEID);
            }
        }
    }
}

void SVSEView::createSEList()
{
    int nRow  = numRows();
    SVShowTable * pTable = new SVShowTable((WContainerWidget*)elementAt(nRow, 0));
    if(pTable)
    {
        pTable->setTitle(SVResString::getResString("IDS_SE_List_Title").c_str());
        WTable * pSub = pTable->createSubTable();
        if(pSub)
        {
            int nRow = pSub->numRows();
            m_pSEList = new WTable((WContainerWidget*)pSub->elementAt(nRow, 0));
            if(m_pSEList)
            {
                m_pSEList->setStyleClass("t3");
                //new WText("", (WContainerWidget *)m_pSEList->elementAt(0, 0));
                new WText(SVResString::getResString("IDS_State_Description"), (WContainerWidget *)m_pSEList->elementAt(0, 0));
                new WText(SVResString::getResString("IDS_Name"), (WContainerWidget *)m_pSEList->elementAt(0, 1));
                new WText(SVResString::getResString("IDS_Edit"), (WContainerWidget *)m_pSEList->elementAt(0, 2));
                m_pSEList->setCellPadding(0);
                m_pSEList->setCellSpaceing(0);
                m_pSEList->GetRow(0)->setStyleClass("t3title");

                connect(&m_wNameMapper, SIGNAL(mapped(const std::string)), this, SLOT(enterSVSE(const std::string)));
                connect(&m_wEditMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditSE(const std::string)));
            }
            //createOperate(pSub);
        }
    }
}

void SVSEView::setCurrentTime(const char * pszTime)
{
    if(m_pTime)
        m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + pszTime);
}

void SVSEView::setCurrentTime(const string &szTime)
{
    if(m_pTime)
        m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + szTime);
}

void SVSEView::createTitle()
{
    int nRow = numRows();
    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("t1title");
    if(pSub)
    {
        pSub->setStyleClass("t3");
        nRow = pSub->numRows();
        WText *pTitle = new WText(SVResString::getResString("IDS_SE_List_Title"), (WContainerWidget*)pSub->elementAt(nRow, 0));
        if(pTitle)
            pTitle->setStyleClass("tgrouptitle2");
        pSub->elementAt(nRow, 0)->setStyleClass("cell_80");
        m_pTime  = new WText("local time", pSub->elementAt(nRow, 1));
        pSub->elementAt(nRow, 1)->setContentAlignment(AlignRight | AlignCenter);
        svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
        string curTime = ttime.Format();
        if(m_pTime)
        {
            m_pTime->setStyleClass("tgrouptitle2");
            m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        }
    }
}

void SVSEView::EditSE(const std::string szSEID)
{
    emit EditSEByID(szSEID);
}

void SVSEView::addSVSEList(string &szName, string &szIndex)
{
    if(m_pSEList)
    {
        int nRow = m_pSEList->numRows();

        SVTableCell cell;

        sv_group_state groupState = getSVSEState(szIndex, m_pSVUser, m_szIDCUser, m_szIDCPwd);
        bool bHasEditRight = true;
        bool bHasDelRight = true;
        if(m_pSVUser)
        {
            bHasEditRight = m_pSVUser->haveUserRight(szIndex, "se_edit");
            bHasDelRight = m_pSVUser->haveUserRight(szIndex, "se_delse");
        }
        else
        {
            bHasEditRight = false;
            bHasDelRight = false;
        }
        // Ñ¡Ôñ
        //if(szIndex.compare("1") != 0)
        //{
        //    WCheckBox * pCheck = NULL;
        //    if(bHasEditRight || bHasDelRight) pCheck = new WCheckBox("", (WContainerWidget *)m_pSEList->elementAt(nRow, 0));
        //    if(pCheck)
        //    {
        //        cell.setType(adCheckBox);
        //        cell.setValue(pCheck);
        //        m_svSEList.WriteCell(szIndex, 0, cell);
        //    }
        //}
        // ÃèÊö
        WText *pDesc = new WText("", (WContainerWidget *)m_pSEList->elementAt(nRow, 0));
        if(pDesc)
        {
            char szState[512] = {0};
            sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                SVResString::getResString("IDS_Device_Count").c_str(), groupState.nDeviceCount,
                SVResString::getResString("IDS_Monitor_Count").c_str(), groupState.nMonitorCount, 
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), groupState.nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), groupState.nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), groupState.nWarnCount);
            pDesc->setText(szState);
        }
        // Ãû³Æ
        WText *pName = new WText(szName, (WContainerWidget *)m_pSEList->elementAt(nRow, 1));
        if ( pName )
        {
            sprintf(pName->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                "this.style.textDecoration=\"underline\"' " \
                "onmouseout='this.style.textDecoration=\"none\"'");
            pName->setToolTip(szName);
            WObject::connect(pName, SIGNAL(clicked()), "showbar();", &m_wNameMapper, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            m_wNameMapper.setMapping(pName, szIndex);

            cell.setType(adText);
            cell.setValue(pName);

            m_svSEList.WriteCell(szIndex, 2, cell);
            SVTableRow *pRow = m_svSEList.Row(szIndex);
            if(pRow)
                pRow->setProperty(szIndex.c_str());
        }
        // ±à¼­
        WImage * pEdit = NULL;
        if(bHasEditRight) pEdit = new WImage("../icons/edit.gif", (WContainerWidget *)m_pSEList->elementAt(nRow, 2));
        if (pEdit)
        {
            pEdit->setToolTip(SVResString::getResString("IDS_Edit"));
            pEdit->setStyleClass("imgbutton");
            WObject::connect(pEdit, SIGNAL(clicked()), "showbar();", &m_wEditMapper, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            m_wEditMapper.setMapping(pEdit,szIndex);
        }

        if((nRow + 1) % 2 == 0)
            m_pSEList->GetRow(nRow)->setStyleClass("tr1");
        else
            m_pSEList->GetRow(nRow)->setStyleClass("tr2");
    }

}

void SVSEView::editSVSEList(string &szName, string &szIndex)
{
    if(!m_svSEList.empty())
    {
        SVTableRow *pRow = m_svSEList.Row(szIndex);
        if(pRow)
        {
            SVTableCell * pCell = pRow->Cell(2);
            if(pCell)
            {
                if(pCell->Type() == adText)
                {
                    ((WText*)pCell->Value())->setText(szName);
                    ((WText*)pCell->Value())->setToolTip(szName);
                }
            }
        }
    }   
}

