#ifndef _SiteView_ECC_Base_Table
#define _SiteView_ECC_Base_Table

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;
class WIamge;

#include <map>
#include <list>
#include <string>

using namespace std;

#include "pushbutton.h"

class CEccBaseTable : public WTable
{
    //MOC: W_OBJECT CEccBaseTable:WTable
    W_OBJECT;
public:
    CEccBaseTable(WContainerWidget *parent = NULL);

    void                    setTitle(string szTitle);

    void                    AddHelpText(WText *pHelp);
private:
    //MOC: SLOT CEccBaseTable::ShowHideHelp()
    virtual     void        ShowHideHelp();
private:
    virtual void            initForm(bool bHasHelp);
    void                    createTitle(bool bHasHelp);
    void                    createContent();
    void                    createOperate();

    void                    setContentCellStyle(string szStyle);
private:
    list<WText*>            m_lsHelp;

    WText                   *m_pTitle;
    WTable                  *m_pContent;
    WTable                  *m_pOperate;

    bool                    m_bShowHelp;

    int                     m_nContentRow;

    friend  class           CEccGroupOperate;
    friend  class           CEccAddDevice1st;
    friend  class           CEccAddDevice2nd;
    friend  class           CEccAddDevice3rd;
    friend  class           CEccAddMonitor1st;
    friend  class           CEccAddMonitor2nd;
    friend  class           CEccBatchAdd;
    friend  class           CEccEidtSVSE;
    friend  class           CEccSortTable;
};

#endif
