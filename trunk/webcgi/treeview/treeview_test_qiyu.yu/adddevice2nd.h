#ifndef _SiteView_Ecc_Add_Device_2nd_H_
#define _SiteView_Ecc_Add_Device_2nd_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WSignalMapper"
#include "../../kennel/svdb/svapi/svapi.h"

#include "ecctable.h"

class CEccListTable;
class CEccAdvanceTable;
class WLineEdit;
class WPushButton;

class CEccParamItem;

class CEccAddDevice2nd : public CEccBaseTable
{
    //MOC: W_OBJECT CEccAddDevice2nd:CEccBaseTable
    W_OBJECT;
public:
    CEccAddDevice2nd(WContainerWidget *parent = NULL);

    void                    AddDeviceByType(string szParent, string szDTName);
    void                    EditDevice(string szDeviceID);
private: //slots
    //MOC: SLOT CEccAddDevice2nd::Forward()
    void                    Forward();
    //MOC: SLOT CEccAddDevice2nd::SaveDevice()
    void                    SaveDevice();
    //MOC: SLOT CEccAddDevice2nd::Cancel()
    void                    Cancel();
    //MOC: SLOT CEccAddDevice2nd::TestDevice()
    void                    TestDevice();
    //MOC: SLOT CEccAddDevice2nd::EnumDynData()
    void                    EnumDynData();

    virtual void            ShowHideHelp();
private:
    virtual void            initForm(bool bHasHelp);

    bool                    checkName(string &szName);

    void                    createAdvance();
    void                    createBaseParam();
    void                    createGeneral();
    void                    createDeviceName(WTable *pTable);
    void                    createOperate();

    void                    createHideButton();

    void                    enumBaseParam();

    void                    ResetData();
    void                    MakeRunParamString(string &szRunParam, bool bEncode = true);

    void                    saveBaseParam(OBJECT &objDevice);
    void                    saveAdvParam(OBJECT &objDevice);
private:
    CEccListTable           *m_pGeneral;
    CEccAdvanceTable        *m_pAdvance;

    WLineEdit               *m_pName;
    WText                   *m_pNameErr;

    string                  m_szEditIndex;
    string                  m_szParentID;
    string                  m_szDTType;

    string                  m_szDllName;
    string                  m_szFuncName;

    string                  m_szQuickAdd;
    string                  m_szQuickAddSel;
    string                  m_szNetworkset;

    bool                    m_bHasDynamic;

    CEccButton              *m_pTest;
    CEccImportButton        *m_pSave;
    CEccButton              *m_pCancel;
    CEccButton              *m_pBack;

    WPushButton             *m_pHideButton;

    map<string, string, less<string> > m_DeviceParam;

    typedef list<CEccParamItem*>::iterator listItem;
    list<CEccParamItem*> m_lsBasicParam;                                          // 基础选项数据list
    list<CEccParamItem*> m_lsDyn;
};

#endif
