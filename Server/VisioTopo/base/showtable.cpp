#include "showtable.h"

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"

SVShowTable::SVShowTable(WContainerWidget * parent):
WTable(parent)
{
    m_bHide = false;
    m_pSub = NULL;
    m_pTitle = NULL;
    m_pHide = NULL;
    m_pShow = NULL;

    InitForm();
}

void SVShowTable::showSubTable()
{
    if(m_pShow)
    {
        m_bHide = false;
        m_pShow->show();
        m_pHide->hide();
        if(m_pSub)
            m_pSub->show();
    }
}

void SVShowTable::hideSubTable()
{
    if(m_pHide)
    {
        m_bHide = true;
        m_pHide->show();
        m_pShow->hide();
        if(m_pSub)
            m_pSub->hide();
    }
}

WTable * SVShowTable::createSubTable()
{
    return m_pSub;
}

void SVShowTable::InitForm()
{
    this->setStyleClass("bg_Border");
    m_pHide = new WImage("../icons/open.gif", (WContainerWidget *)elementAt( 0, 0));
    if ( m_pHide )
    {
        m_pHide->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(m_pHide, SIGNAL(clicked()), this, SLOT(showSubTable()));
        m_pHide->hide();
    }

    m_pShow = new WImage("../icons/close.gif", (WContainerWidget *)elementAt( 0, 0));
    if ( m_pShow )
    {
        m_pShow->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(m_pShow, SIGNAL(clicked()), this, SLOT(hideSubTable()));
    }
    m_pTitle = new WText("", (WContainerWidget *)elementAt( 0, 0));
    elementAt(0,0)->setStyleClass("t2title");

    m_pSub = new WTable(elementAt( 1, 0));
}

void SVShowTable::setTitle(const char *szTitle)
{
    if(m_pTitle)
        m_pTitle->setText(szTitle);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
