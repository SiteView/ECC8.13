#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _MENUTABLE_H_
#define _MENUTABLE_H_

#include <list>

using namespace std;

#include <WText>
#include <WTable>
#include <WImage>
#include <WTableCell>
#include <WContainerWidget>
#include <WPushButton>
#include <WSignalMapper>

//////////////////////////////////////////////////////////////////////////////////
// class CMenuTable
class CMenuTable : public WTable
{
    //MOC: W_OBJECT CMenuTable:WTable
    W_OBJECT;
public:
    CMenuTable(WContainerWidget * parent, const std::string strTitle);
	CMenuTable();
public :
    inline WTable * GetContentTable()
	{
		return m_pContentTable;
	}
public:
private slots:
    //MOC: SLOT CMenuTable::ShowTable()
    void ShowTable();
    //MOC: SLOT CMenuTable::HideTable()
    void HideTable();
    //MOC: SLOT CMenuTable::ShowOrHideTable()
    void ShowOrHideTable();

private:
	bool bShow;

	WTable * m_pContentTable;
	WImage * m_pOpenimg;
	WImage * m_pCloseimg;
private :
	;
};

#endif