#include "svseview.h"
#include "basedefine.h"

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WPushButton"

#include "statedesc.h"
#include "listtable.h"
#include "resstring.h"
#include "treeview.h"
#include "basefunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccSVSEView::CEccSVSEView(WContainerWidget *parent):
WTable(parent),
m_pTitle(NULL),
m_pContent(NULL)
{
    setStyleClass("panel");
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSVSEView::createStateDesc()
{
    int nRow = numRows();
    new CEccStateDesc(elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSVSEView::createTitle()
{
    int nRow = m_pContent->numRows();
    m_pTitle = new CEccGenTitle(m_pContent->elementAt(nRow, 0));
    if(m_pTitle )
        m_pTitle->setTitle(SVResString::getResString("IDS_SE_List_Title"));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSVSEView::initForm()
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
            createSVSEList();
        }
    }

    EnumSVSE();

    createStateDesc();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSVSEView::createSVSEList()
{
    int nRow = m_pContent->numRows();

    m_pGeneral = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false);
    if(m_pGeneral)
    {
        m_pGeneral->setTitle(SVResString::getResString("IDS_SE_List_Title"));

        list<string> lsCols;
        lsCols.push_back(SVResString::getResString("IDS_State_Description"));
        lsCols.push_back(SVResString::getResString("IDS_Name"));
        lsCols.push_back(SVResString::getResString("IDS_Edit"));
        m_pGeneral->setCols(lsCols);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSVSEView::EnumSVSE()
{
    if(m_pGeneral && m_pGeneral->getListTable())
    {
        int nRow = m_pGeneral->getListTable()->numRows();
        map<string, CEccTreeGroup, less<string> >::const_iterator seitem;
        for(seitem = CEccTreeView::getSEList().begin(); seitem != CEccTreeView::getSEList().end(); seitem ++)
        {
            string szState(seitem->second.getShowText());
            buildHtmlText(szState);

            new WText(szState, m_pGeneral->getListTable()->elementAt(nRow, 0));

            WText *pName = new WText(seitem->second.getName(), m_pGeneral->getListTable()->elementAt(nRow, 2));
            if(pName)
                sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onclick='SetCurfocus(\"%s\")' "
                "onmouseover='this.style.textDecoration=\"underline\"' onmouseout='this.style.textDecoration=\"none\"'",
                seitem->second.getECCIndex().c_str());

            WImage *pEdit = new WImage("../Images/edit.gif", m_pGeneral->getListTable()->elementAt(nRow, 4));
            if(pEdit)
            {
                pEdit->setStyleClass("hand");
                char chFunc[128] = {0};
                sprintf(chFunc, "objoperatebyid('%s','%d');", seitem->second.getECCIndex().c_str(), SV_EDIT);
                WObject::connect(pEdit, SIGNAL(clicked()),  chFunc, WObject::ConnectionType::JAVASCRIPT);
            }


            m_pGeneral->getListTable()->elementAt(nRow, 0)->setStyleClass("table_data_grid_item_text");
            m_pGeneral->getListTable()->elementAt(nRow, 2)->setStyleClass("table_data_grid_item_text");
            m_pGeneral->getListTable()->elementAt(nRow, 4)->setStyleClass("table_data_grid_item_img");

            if(nRow % 2 == 0)
                m_pGeneral->getListTable()->GetRow(nRow)->setStyleClass("table_data_grid_item_bg");

            nRow ++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccSVSEView::refreshTime()
{
    if(m_pTitle)
        m_pTitle->refreshTime();
}
