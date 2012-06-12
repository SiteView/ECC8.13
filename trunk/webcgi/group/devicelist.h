/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_DEVICE_LIST_H_
#define _SV_DEVICE_LIST_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WSignalMapper"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../svtable/SVTable.h"
#include "../userright/user.h"

#include "basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVEnumDevice : public WContainerWidget
{
    //MOC: W_OBJECT SVEnumDevice:WContainerWidget
    W_OBJECT;
public:
    SVEnumDevice(WContainerWidget* parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");

    void AddDevice(string &szName, string &szIndex);
    void EditDevice(string &szName, string &szIndex);
    void EnterGroup(string &szIndex);

    bool isChildEdit(string szIndex);
    const char * getDeviceName();

    void refreshDevice(string szIndex);
    void SetUserPwd(string &szUser, string &szPwd);

    void changeDeviceState(string &szIndex, bool bEnable = true);

    void delDeviceRow(string &szIndex);

    int m_nDeviceCount;
    int m_nMonitorCount;
    int m_nMonitorErrCount;
    int m_nMonitorWarnCount;
    int m_nMonitorDisableCount;
public signals:
    //MOC: SIGNAL SVEnumDevice::AddNewDevice()
    void AddNewDevice();
    //MOC: SIGNAL SVEnumDevice::EditDeviceByID(string)
    void EditDeviceByID(string szEditID);
    //MOC: SIGNAL SVEnumDevice::EnterDeviceByID(string)
    void EnterDeviceByID(string szDeviceID);
    //MOC: SIGNAL SVEnumDevice::sortDevicesList(int)
    void sortDevicesList(int nType);
    //MOC: SIGNAL SVEnumDevice::UpdateDeviceState(string,int)
    void UpdateDeviceState(string szDeviceID, int nMonitorState);
    //MOC: SIGNAL SVEnumDevice::CopyDeviceSucc(string,string)
    void CopyDeviceSucc(string strName,string szIndex);                          // 拷贝设备成功
    //MOC: SIGNAL SVEnumDevice::DeleteDeviceSucc(string,string)
    void DeleteDeviceSucc(string strName,string szIndex);                          // 拷贝设备成功
private slots:
    //MOC: SLOT SVEnumDevice::selAll()
    void selAll();
    //MOC: SLOT SVEnumDevice::selNone()
    void selNone();
    //MOC: SLOT SVEnumDevice::invertSel()
    void invertSel();
    //MOC: SLOT SVEnumDevice::delSel()
    void delSel();
    //MOC: SLOT SVEnumDevice::add()
    void add();
    //MOC: SLOT SVEnumDevice::editDevice()
    void editDevice();
    //MOC: SLOT SVEnumDevice::gotoDevice()
    void gotoDevice();    
    //MOC: SLOT SVEnumDevice::changeState()
    void changeState();
    //MOC: SLOT SVEnumDevice::DelSelDevice()
    void DelSelDevice();
    //MOC: SLOT SVEnumDevice::testDevice()
    void testDevice();
    //MOC: SLOT SVEnumDevice::deleteDevice()
    void deleteDevice();
    //MOC: SLOT SVEnumDevice::enableSelDevice()
    void enableSelDevice();
    //MOC: SLOT SVEnumDevice::disableSelDevice()
    void disableSelDevice();
    //MOC: SLOT SVEnumDevice::disableDeviceSucc()
    void disableDeviceSucc();
    //MOC: SLOT SVEnumDevice::sortDevices()
    void sortDevices();
    //MOC: SLOT SVEnumDevice::CopyDevice()
    void CopyDevice();
    //MOC: SLOT SVEnumDevice::PastDevice()
    void PastDevice();    
private:
    //function list
    //void loadString();
    void initForm();

    void createHideButton();
    void createOperate(WTable * pTable);
    void createDeviceList(WTable * pTable);

    void createSelOperate();
    void createEnableOperate();
    void createRefreshOperate();
    void createDelOperate();
    void createCopyPaste();

    void addDeviceList(string &szName, string &szIndex);
    void editDeviceList(string &szName, string &szIndex);

    void enumDevice(string &szIndex);
    void DelDevice(string &szIndex);

    bool isDisable(string &szDeviceID, string &szState);
    bool isCanBeTest(string &szDeviceID);

    void enumRight();
    void changeOperateState();
    void changeDelState();
    void changeSelState();
    void changeEnableState();
    void changeCopyPasteState();

    bool        IsCanPaste();
    string      copyDevice(string &szSrcDeviceID);
    string      enumDeviceRunParam(string szDeviceIndex);
    string      getDeviceName(string szDeviceIndex);
private:
    SVTable m_svDevice;
    list<string> m_lsCopyDevice;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string m_szDelSelIndex;
    string m_szParentID;
    string m_szIndex;
    string m_szDeviceName;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WPushButton  * m_pBtnHide;
    WPushButton  * m_pBtnHideDel;
    WPushButton  * m_pBtnDelSel;
    WPushButton  * m_pBtnRefresh;
    WPushButton  * m_pBtnEnterDevice;
    WPushButton  * m_pBtnTest;
    WPushButton  * m_pBtnEdit;

    WLineEdit    * m_pCurrentDevice;

    WPushButton * m_pAdd;
    WImage      * m_pDel;
    WImage      * m_pEnable;
    WImage      * m_pDisable;
    WImage      * m_pSort;
    WImage      * m_pSelAll;
    WImage      * m_pSelNone;
    WImage      * m_pSelInvert;
    WImage      * m_pCopy;
    WImage      * m_pPaste;
    WTable      * m_pDeviceList;
    WTable      * m_pOperate;
    
    WText       * m_pHasNoChild;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string    m_szIDCUser;
    string    m_szIDCPwd;
    CUser   * m_pSVUser;

    bool          m_bHasAddRight;
    bool          m_bHasDelRight;
    bool          m_bHasEditRight;
    bool          m_bHasSortRight;
    bool          m_bHasRefreshRight;
    bool          m_bHasTestRight;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
