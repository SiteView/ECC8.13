#ifndef _SiteView_Ecc_Add_Device_1st_H_
#define _SiteView_Ecc_Add_Device_1st_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WSignalMapper"

#include "ecctable.h"

class WText;

class CEccAddDevice1st : public CEccBaseTable
{
    //MOC: W_OBJECT CEccAddDevice1st:CEccBaseTable
    W_OBJECT;
public:
    CEccAddDevice1st(WContainerWidget *parent = NULL);
    ~CEccAddDevice1st();

    void    setParentID(string szIndex);
private: //slots
    //MOC: SLOT CEccAddDevice1st::Cancel()
    void                    Cancel();
    //MOC: SLOT CEccAddDevice1st::AddDeviceByType(const std::string)
    void                    AddDeviceByType(const std::string szType);
private:
    virtual void            initForm(bool bHasHelp);

    void                    createOperate();
    void                    createTitle();
    void                    enumDeviceGroup();
    void                    AddDeviceTemplet(string szDTName, WTable *pSubTable);
    void                    removeMapping();

    string                  m_szParentId;

    WSignalMapper           m_MapperOfDT;

    list<WText*>             m_lsText;
};

#endif
