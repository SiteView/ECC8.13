#include "gentitle.h"
#include "treeview.h"
#include "resstring.h"

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"

#include "../../kennel/svdb/libutil/time.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccGenTitle::CEccGenTitle(WContainerWidget *parent):
WTable(parent),
m_pTitle(NULL),
m_pTime(NULL),
m_pIcon(NULL),
m_pList(NULL)
{
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGenTitle::initForm()
{
    m_pTitle = new WTable(elementAt(0, 0));
    if(m_pTitle)
    {
        m_pTitle->setStyleClass("padding_2");
        m_pTime = new WText("refresh time", m_pTitle->elementAt(0, 1));
        if(m_pTime)
        {
            TTime ttime = TTime::GetCurrentTimeEx();
            m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + ttime.Format());
        }
        m_pTitle->elementAt(0, 1)->setStyleClass("width40p");
        m_pTitle->elementAt(0, 1)->setContentAlignment(AlignRight | AlignTop);
    }

    elementAt(0, 0)->setStyleClass("padding_top");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置当前路径
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGenTitle::setCurIndex(const string &szIndex)
{
    PAIRLIST lsPath;
    CEccTreeView::MakePath(szIndex, lsPath);
    if(lsPath.size() >= 1 && m_pTitle)
    {
        m_pTitle->elementAt(0, 0)->clear();

        sv_pair svitem;
        while(lsPath.size() > 1)
        {
            svitem = lsPath.front();
            lsPath.pop_front();

            WText *pName = new WText(svitem.value, m_pTitle->elementAt(0, 0));
            if(pName)
            {
                string szCmd = "SetCurfocus(\"" + svitem.name + "\");";
                pName->setStyleClass("tgrouptitle");
                WObject::connect(pName, SIGNAL(clicked()), szCmd.c_str(), WObject::ConnectionType::JAVASCRIPT);
            }

            WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitle->elementAt(0, 0));
            if(pTemp)
                pTemp->setStyleClass("tgrouptitle2");
        }

        svitem = lsPath.front();
        lsPath.pop_front();
        WText *pTitle = new WText(svitem.value, m_pTitle->elementAt(0, 0));
        if(pTitle)
            pTitle->setStyleClass("tgrouptitle2");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置标题文本
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGenTitle::setTitle(const string &szTitle)
{
    if(m_pTitle)
    {
        m_pTitle->elementAt(0, 0)->clear();

        WText *pTitle = new WText(szTitle, m_pTitle->elementAt(0, 0));
        if(pTitle)
            pTitle->setStyleClass("tgrouptitle2");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建视图控制
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGenTitle::createViewControl()
{
    int nRow = numRows();
    
    WTable *pSub = new WTable(elementAt(nRow, 0));

    if(pSub)
    {
        pSub->setStyleClass("widthauto");
        m_pList = new WImage("../Images/treeview_list.png", pSub->elementAt(0, 0));
        pSub->elementAt(0, 0)->setStyleClass("padding_2");
        m_pIcon = new WImage("../Images/treeview_graph.png", pSub->elementAt(0, 1));
        pSub->elementAt(0, 1)->setStyleClass("padding_bom");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 刷新时间
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGenTitle::refreshTime()
{
    if(m_pTime)
    {
        TTime ttime = TTime::GetCurrentTimeEx();
        m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + ttime.Format());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WImage* CEccGenTitle::getIconControl() const
{
    return m_pIcon;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WImage* CEccGenTitle::getListControl() const
{
    return m_pList;
}

