/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_MONITOR_VIEW_H_
#define _SV_MONITOR_VIEW_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WLineEdit"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../svtable/SVTable.h"
#include "general.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "showtable.h"
#include "basefunc.h"
#include "../userright/user.h"

class SVGroupview;

class SVMonitorview : public WTable
{
    //MOC: W_OBJECT SVMonitorview:WTable
    W_OBJECT;
public:
    SVMonitorview(WContainerWidget * parent = NULL, CUser * pUser = NULL, string szIDCUser = "defualt", 
        string szIDCPwd = "localhost", string szDeviceIndex = "");

    void refreshState();
    void reloadCurrentDevice();

    bool isInDevice(string szIndex);

    void setRefreshEvent(string szEvent){m_szRefreshEvent = szEvent ;};
    void setMainview(SVGroupview *pMain){m_pMain = pMain;};
    void AddMonitorView(string &szName, string &szMonitorIndex);
    void EditMonitorView(string &szName, string &szMonitorIndex);
    
    //void changeMonitor(const char *pszMonitor) {string szMonitor = pszMonitor;changeState(szMonitor);};
    void enterDevice(string &szDeviceIndex);
    void setCurrentTime(const char* pszTime);
    void setCurrentTime(const string &szTime);
    void SetUserPwd(string &szUser, string &szPwd);
    string GetCurrentID(){return m_szDeviceIndex;};					//
    void refreshNamePath();
    bool isParentEdit(string szIndex);
public signals:
    //MOC: SIGNAL SVMonitorview::AddNewMonitor(string,string)
    void AddNewMonitor(string szDevivceType, string szDeviceIndex);
    //MOC: SIGNAL SVMonitorview::EditMonitorByID(string)
    void EditMonitorByID(string szMonitorIndex);
    //MOC: SIGNAL SVMonitorview::BackDeviceParent(string)
    void BackDeviceParent(string szGroupID);
    //MOC: SIGNAL SVMonitorview::sortMonitorsList(int)
    void sortMonitorsList(int nType);
    //MOC: SIGNAL SVMonitorview::enterGroup(string)
    void enterGroup(string szGroupID);
    //MOC: SIGNAL SVMonitorview::enterDependDevice(string)
    void enterDependDevice(string szDeviceID);
    //MOC: SIGNAL SVMonitorview::ChangeDeviceState(string,int)
    void ChangeDeviceState(string szDeviceID, int nMonitorState);
    //MOC: SIGNAL SVMonitorview::CopyMonitorSucc(string,string)
    void CopyMonitorSucc(string szName, string szIndex);
private slots:
    //MOC: SLOT SVMonitorview::selAll()
    void selAll();
    //MOC: SLOT SVMonitorview::selNone()
    void selNone();
    //MOC: SLOT SVMonitorview::invertSel()
    void invertSel();
    //MOC: SLOT SVMonitorview::delSel()
    void delSel();
    //MOC: SLOT SVMonitorview::delSelMonitor()
    void delSelMonitor();
    //MOC: SLOT SVMonitorview::enableSel()
    void enableSel();
    //MOC: SLOT SVMonitorview::disableSel()
    void disableSel();
    //MOC: SLOT SVMonitorview::addMonitor()
    void addMonitor();
    //MOC: SLOT SVMonitorview::editSelMonitor()
    void editSelMonitor();
    //MOC: SLOT SVMonitorview::changeState()
    void changeState();
    //MOC: SLOT SVMonitorview::BackParent()
    void BackParent();
    //MOC: SLOT SVMonitorview::disableSucc()
    void disableSucc();
    //MOC: SLOT SVMonitorview::refreshMonitors()
    void refreshMonitors();
    //MOC: SLOT SVMonitorview::sortMonitors()
    void sortMonitors();
    //MOC: SLOT SVMonitorview::gotoGroup(const std::string)
    void gotoGroup(const std::string szGroupID);
    //MOC: SLOT SVMonitorview::gotoDevice(const std::string)
    void gotoDevice(const std::string szDeviceID);
    //MOC: SLOT SVMonitorview::copySelMonitor()
    void copySelMonitor();
    //MOC: SLOT SVMonitorview::PastMonitor()
    void PastMonitor();
private:
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string  m_szDependsOnID;                                        // �豸�����ļ��������
    string  m_szDeviceDesc;                                         // ��ǰ�豸����
    string  m_szDeviceIndex;                                        // ��ǰ�豸����
    string  m_szDeviceName;                                         // ��ǰ�豸����
    string  m_szDeviceState;                                        // �豸״̬
    string  m_szDeviceShowType;                                     // �豸������ʾ����
    string  m_szDeviceType;                                         // �豸�洢����
    string  m_szIDCPwd;                                             // 
    string  m_szIDCUser;                                            // 
    string  m_szNetworkSet;                                         // ��ǰ�豸�Ƿ��������豸
    string  m_szRefreshEvent;                                       // ˢ���¼�
    string  m_szStateKeep;                                          // ��ǰ״̬������

    int     m_nErrCount;                                            // ������������
    int     m_nWarnCount;                                           // ������������
    int     m_nMonitorCount;                                        // ���������
    int     m_nDisableCount;                                        // ����ֹ���������
    bool    m_bHasAddRight;                                         // �Ƿ������Ȩ��
    bool    m_bHasDelRight;                                         // �Ƿ���ɾ��Ȩ��
    bool    m_bHasRefreshRight;                                     // �Ƿ���ˢ��Ȩ��
    bool    m_bHasEditRight;                                        // �Ƿ��б༭Ȩ��
    bool    m_bHasSortRight;                                        // �Ƿ�������Ȩ��

    CUser   * m_pSVUser;                                            // ��ǰ�û�Ȩ�޹�����
    SVTable m_svMonitorList;                                        // �������
    SVTable m_svMTTableOfET;                                        // ���豸���ʹ洢�Ŀ�ʹ�ü������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void    AddMonitorList(string &szName, string &szMonitorIndex);
    void    createControl();
    void    createCopyPaste();
    void    createDelOperate();
    void    createEnableOperate();
    void    createGeneral();
    void    createHideButton();
    void    createMonitor();
    void    createMonitorList();
    void    createOperate();
    void    createRefreshOperate();
    void    createSelOperate(); 
    void    createTitle();
    void    changeOperateState();
    void    changeCopyPasteState();
    void    changeDelState();
    void    changeEnableState();
    void    changeRefreshState(); 
    void    changeSelState();
    void    enumDeviceRight();
    void    enumMonitor(string &szIndex);
    void    initForm();
    void    removeMapping();
    void    MakeMTTableOfET();
    bool    IsCanPaste();
    bool    makeGroupPath(string &szGroupID, list<base_param> &lsPath);
    bool    makeMonitorPath(string &szMonitorID, list<base_param> &lsPath);
    string  getDeviceShowType(string &szDeviceType);
    string  makeState(string &szMonitorID);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SVGeneral   *  m_pGeneral;
    WTable      *  m_pContent;
    WTable      *  m_pMonitorList;
    WTable      *  m_pOperate;
    SVShowTable *  m_pMonitor;
    WText       *  m_pTitle;
    WText       *  m_pDeviceType;
    WText       *  m_pTime;
    WText       *  m_pConditionType;
    WText       *  m_pHasNoChild;
    WText       *  m_pDependDevice;
    WPushButton *  m_pbtnHide;
    WPushButton *  m_pBtnHideDel; 
    WPushButton *  m_pbtnRefresh;
    WPushButton *  m_pbtnEdit;
    WPushButton *  m_pAdd;
    WLineEdit   *  m_pCurrentMonitor;
    WImage      *  m_pDel;
    WImage      *  m_pEnable;
    WImage      *  m_pDisable;
    WImage      *  m_pRefresh;
    WImage      *  m_pSelAll;
    WImage      *  m_pSelNone;
    WImage      *  m_pSelInvert;
    WImage      *  m_pSort;
    WImage      *  m_pCopy;
    WImage      *  m_pPaste;
    WTableCell  *  m_pTitleCell;
    WTableCell  *  m_pDependsCell;

    WSignalMapper m_GroupName;
    WSignalMapper m_DeviceName;

    list<WText*> m_lsPath;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    friend class SVGroupview;
    SVGroupview *m_pMain;
    list<string> m_lsCopyList;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end if
