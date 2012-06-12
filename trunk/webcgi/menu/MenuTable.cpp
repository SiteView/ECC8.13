#include "MenuTable.h"

#include <Algorithm>
#include <WText>
#include <WTable>
#include <WImage>
#include <WTableCell>
#include <WPushButton>

#include "WebSession.h"
//////////////////////////////////////////////////////////////////////////////////
// start
CMenuTable::CMenuTable()
{

}

CMenuTable::CMenuTable(WContainerWidget * parent, const std::string strTitle)
:WTable(parent)
{
	this->setCellPadding(0);
	this->setCellSpaceing(0);
	bShow = true;

	WTable * pTable = new WTable(this->elementAt(0,0));
	pTable->setCellPadding(0);
	pTable->setCellSpaceing(0);
	new WText(strTitle, (WContainerWidget*)pTable->elementAt(0,0));
	pTable->elementAt(0,0)->setStyleClass("navt2title");

	m_pOpenimg = new WImage("../icons/arrowdown.gif", (WContainerWidget *)pTable->elementAt(0, 1)); 
	m_pOpenimg->setStyleClass("helpimg");
	m_pCloseimg = new WImage("../icons/arrowup.gif", (WContainerWidget *)pTable->elementAt(0, 1));
	m_pCloseimg->setStyleClass("helpimg");
	//m_pOpenimg->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
	//m_pCloseimg->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
	//pTable->elementAt(0,0)->resize(15, 11);
	//m_pCloseimg->resize(15, 11);
	pTable->elementAt(0, 1)->setContentAlignment(AlignRight);
	pTable->setStyleClass("navt2");

	m_pOpenimg->hide();
	WObject::connect(pTable->elementAt(0,0),SIGNAL(clicked()),this,SLOT(ShowOrHideTable()));	
	WObject::connect(m_pOpenimg,SIGNAL(clicked()),this,SLOT(ShowTable()));
	WObject::connect(m_pCloseimg,SIGNAL(clicked()),this,SLOT(HideTable()));	
	

	m_pContentTable = new WTable((WContainerWidget*)this->elementAt(1,0)) ;	
	m_pContentTable->setCellPadding(0);
	m_pContentTable->setCellSpaceing(0);
	m_pContentTable->setStyleClass("navt3");
}


void CMenuTable::ShowTable()
{
	bShow = true;
	m_pContentTable->show();
	m_pOpenimg->hide();
	m_pCloseimg->show();
}

void CMenuTable::HideTable()
{
	bShow = false;
	m_pContentTable->hide();
	m_pOpenimg->show();
	m_pCloseimg->hide();	
}

void CMenuTable::ShowOrHideTable()
{
	if(bShow)
	{
		bShow = false;
		m_pContentTable->hide();
		m_pOpenimg->show();
		m_pCloseimg->hide();
	}
	else
	{
		bShow = true;
		m_pContentTable->show();
		m_pOpenimg->hide();
		m_pCloseimg->show();
	}
}