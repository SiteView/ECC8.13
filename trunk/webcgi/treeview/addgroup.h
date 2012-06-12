#ifndef _SiteView_ECC_Group_Operate_H_
#define _SiteView_ECC_Group_Operate_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "ecctable.h"

class WLineEdit;

class CEccListTable;
class CEccAdvanceTable;

class CEccGroupOperate : public CEccBaseTable
{
    //MOC: W_OBJECT CEccGroupOperate:CEccBaseTable
    W_OBJECT;
public:
    CEccGroupOperate(WContainerWidget *parent = NULL);

    void    AddGroup(string szParentID);
    void    EditGroup(string  szCurrentID);
private:
    //MOC: SLOT CEccGroupOperate::SaveGroup()
    void SaveGroup();
    //MOC: SLOT CEccGroupOperate::Cancel()
    void Cancel();
    
    virtual void        ShowHideHelp();
private:
    virtual void        initForm(bool bHasHelp);

    bool                checkName(string &szName);

    void                createAdvance();
    void                createGeneral();
    void                createOperate();

    void                ResetData();
private:
    CEccListTable       *m_pGeneral;
    CEccAdvanceTable    *m_pAdvance;

    WLineEdit           *m_pName;
    WText               *m_pNameErr;

    string              m_szParentID;
    string              m_szEditIndex;
};

#endif
