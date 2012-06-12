/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_DEVICE_2ND_H_
#define _SV_ADD_DEVICE_2ND_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WSignalMapper"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "showtable.h"

#include "paramitem.h"

#include "dependtable.h"
#include "../userright/user.h"
#include "basefunc.h"
#include "../svtable/SVTable.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVDevice : public WTable
{
    //MOC: W_OBJECT SVDevice:WTable
    W_OBJECT;
public:
    SVDevice(WContainerWidget * parent = NULL, CUser *pUser = NULL, string szIDCUser = "default", 
        string szPwd = "localhost", string szDeviceType = "");                  // ���캯��

    void requesDynData();
    void SetUserPwd(string &szUser, string &szPwd);                             // ���� IDC �û�
    void SetDeviceType(string &szDeviceType);                                   // ���� �豸�� ����
    void SetParentIndex(string &szGroupID) { m_szParentIndex = szGroupID;};     // ���� �ϼ� �ڵ� ID
    void ClearData(string &szIndex);                                            // ��������
    void EditDeviceByID(string &szIndex);                                       // ���� �豸 �����༭�豸
    string getParentIndex() {return m_szParentIndex;};
private signals:
    //MOC: SIGNAL SVDevice::backMain()
    void backMain();                                                            // ������ҳ��
    //MOC: SIGNAL SVDevice::backPreview()
    void backPreview();                                                         // ������һ��
    //MOC: SIGNAL SVDevice::AddDeviceSucc(string,string)
    void AddDeviceSucc(string strName,string szIndex);                          // ����豸�ɹ�
    //MOC: SIGNAL SVDevice::EditDeviceSucc(string,string)
    void EditDeviceSucc(string strName,string szIndex);                         // �༭�豸�ɹ�
    //MOC: SIGNAL SVDevice::EnterNewDevice(string)
    void EnterNewDevice(string szIndex);
private slots:
    //MOC: SLOT SVDevice::Cancel()
    void Cancel();                                                              // ȡ�����
    //MOC: SLOT SVDevice::Save()
    void Save();                                                                // ����
    //MOC: SLOT SVDevice::Preview()
    void Preview();                                                             // ��һ��
    //MOC: SLOT SVDevice::showHelp()
    void showHelp();                                                            // ��ʾ����
    //MOC: SLOT SVDevice::testDevice()
    void testDevice();
    //MOC: SLOT SVDevice::listDynParam()
    void listDynParam();
    //MOC: SLOT SVDevice::listDynData()
    void listDynData();
    //MOC: SLOT SVDevice::enterDevice()
    void enterDevice();
    //MOC: SLOT SVDevice::saveAllSelMonitors()
    void saveAllSelMonitors();
    //MOC: SLOT SVDevice::selAllByMonitorType(int)
    void selAllByMonitorType(int nMonitorType);
private:
    void initForm();                                                            // ��ʼ��ҳ��
    void createTitle();                                                         // ��������
    void createHelp();                                                          // ������������
    void createGeneral();                                                       // ���� ����ѡ��
    void createAdv();                                                           // ���� �߼�ѡ��

    void createOperate();                                                       // ���� ����
    void createHostName(WTable  * pTable);                                      // ���� ��������

    void enumBaseParam();                                                       // ö�� ��������
    void setTitle(string &szDeviceType);                                        // ���� ����

    typedef list<SVParamItem*>::iterator listItem;
    list<SVParamItem*> m_lsBasicParam;                                          // ����ѡ������list
    list<SVParamItem*> m_lsDyn;

    SVDependTable *  m_pAdvTable;                                               // �߼�ѡ��

    WText         * m_pTitle;                                                   // ����
    WText         * m_pHostHelp;                                                // �������ư���
    WText         * m_pHostNameHelp;                                            // ����������ʾ
    WPushButton   * m_pBack;                                                    // ����
    WPushButton   * m_pSave;                                                    // ����
    WPushButton   * m_pCancel;                                                  // ȡ��
    WPushButton   * m_pTest;
    WPushButton   * m_pListDynBtn;
    WPushButton   * m_pListDynData;
    WPushButton   * m_pSaveMonitor;
    WPushButton   * m_pCancelSaveMonitor;
    WLineEdit     * m_pDeviceTitle;                                             // �豸����


    SVShowTable   * m_pGeneral;                                                 // ������Ϣ��
    WTable        * m_pQuickAdd;
    WTable        * m_pContentTable;
    WTable        * m_pSubContent;
    string m_szEditIndex;                                                       // ���޸ĵ��豸
    string m_szDeviceType;                                                      // �豸����
    string m_szParentIndex;                                                     // ���ڵ�
    string m_szDeviceName;                                                      // �豸����
    string m_szDeviceID;                                                        // �豸����
    string m_szQueryString;                                                     //
    string m_szDllName;                                                         //
    string m_szFuncName;                                                        // 

    string m_szQuickAdd;                                                        // ������Ӽ�����б�
	string m_szQuickAddSel;                                                     // ������Ӽ����ȱʡ����ѡ��״̬�ļ����
    string m_szNetworkset;                                                      // ������豸�Ƿ��������豸
    
    void        AddDynData(WTable * pTable, const char* pszQuery, const int &nQuerySize, const int &nMonitorID, 
                            const string &szDllName, const string &szFuncName, const string &szSaveName, const bool &bSel);

    void        AddMonitorTempList();

    void        initQuickAdd();
    void        createQuickAddOperate();

    struct monitor_templet
    {
        monitor_templet()
        {
            nMonitorID = 0;
            szName = "";
            szLabel = "";
            szDllName = "";
            szFuncName = "";
            szSaveName = "";
			bSel = false;
            pTable = NULL;
        };
        int    nMonitorID;
        string szSaveName;
        string szName;
        string szLabel;
        string szDllName;
        string szFuncName;
		bool   bSel;
        WTable *pTable;
    };

    list<monitor_templet>      m_lsMonitorTemplet;

    bool m_bShowHelp;                                                           // ��ʾ/���ذ���
    bool m_bHasDynamic;
    
    SVIntTable m_svValueList;
    
    typedef map<string, string, less<string> > SVReturnMap;
    typedef map<string, string, less<string> >::iterator SVReturnItem;

    bool    saveMonitor(int nMonitorID, const char* pszSaveName, const char* pszExtraParam, const char *pszExtraLable);
    bool    saveMonitorBaseParam(OBJECT & objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam);
    bool    saveMonitorAdvParam(OBJECT & objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam);
    bool    saveMonitorCondition(OBJECT & objMonitor, OBJECT objMonitorTemp);
    bool    saveAlertNodeValue(MAPNODE &alertnode, MAPNODE &alertnodetmp);
    bool    checkParamValue(string &szParam, SVReturnMap &rtMap);
    //void    loadReturnParam(OBJECT &objMonitorTemp, SVReturnMap &rtMap);
    //void    loadCondition();
    list<string>        m_lsCondition;
    WSignalMapper       m_mapMinitor; 


	map<string, string, less<string> > m_DeviceParam;
	bool m_bChanged;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string    m_szIDCUser;                                                      // IDC �û�
    string    m_szIDCPwd;                                                       // IDC �û�����
    CUser   * m_pSVUser;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
