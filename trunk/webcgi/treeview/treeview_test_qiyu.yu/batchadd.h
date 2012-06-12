#ifndef _SiteView_Ecc_Batch_Add_H_
#define _SiteView_Ecc_Batch_Add_H_

#include "ecctable.h"

class WText;
class WCheckBox;

#include "../svtable/SVTable.h"

#include "rightview.h"

class CEccBatchAdd : public CEccBaseTable
{
    //MOC: W_OBJECT CEccBatchAdd:CEccBaseTable
    W_OBJECT;
public:
    CEccBatchAdd(WContainerWidget *parent = NULL);
    void        setListValue(list<ecc_value_list> &lsValue, string szDynName);
private:
    //MOC: SLOT CEccBatchAdd::SaveSelMonitor()
    void SaveSelMonitor();
    //MOC: SLOT CEccBatchAdd::Cancel()
    void Cancel();
    //MOC: SLOT CEccBatchAdd::SelAll()
    void SelAll();

private:
    virtual void    initForm(bool bHasHelp);

    void            createOperate();
    void            createListTitle();

    WText           *m_pDynName;
    WCheckBox       *m_pSelAll;

    map<string, WCheckBox*, less<string> >  m_lsCheckBox;
    map<string, string, less<string> >      m_lsValue;
};

#endif
