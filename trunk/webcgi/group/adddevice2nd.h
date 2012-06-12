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
        string szPwd = "localhost", string szDeviceType = "");                  // 构造函数

    void requesDynData();
    void SetUserPwd(string &szUser, string &szPwd);                             // 设置 IDC 用户
    void SetDeviceType(string &szDeviceType);                                   // 设置 设备的 类型
    void SetParentIndex(string &szGroupID) { m_szParentIndex = szGroupID;};     // 设置 上级 节点 ID
    void ClearData(string &szIndex);                                            // 清理数据
    void EditDeviceByID(string &szIndex);                                       // 根据 设备 索引编辑设备
    string getParentIndex() {return m_szParentIndex;};
private signals:
    //MOC: SIGNAL SVDevice::backMain()
    void backMain();                                                            // 返回主页面
    //MOC: SIGNAL SVDevice::backPreview()
    void backPreview();                                                         // 返回上一级
    //MOC: SIGNAL SVDevice::AddDeviceSucc(string,string)
    void AddDeviceSucc(string strName,string szIndex);                          // 添加设备成功
    //MOC: SIGNAL SVDevice::EditDeviceSucc(string,string)
    void EditDeviceSucc(string strName,string szIndex);                         // 编辑设备成功
    //MOC: SIGNAL SVDevice::EnterNewDevice(string)
    void EnterNewDevice(string szIndex);
private slots:
    //MOC: SLOT SVDevice::Cancel()
    void Cancel();                                                              // 取消添加
    //MOC: SLOT SVDevice::Save()
    void Save();                                                                // 保存
    //MOC: SLOT SVDevice::Preview()
    void Preview();                                                             // 上一级
    //MOC: SLOT SVDevice::showHelp()
    void showHelp();                                                            // 显示帮助
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
    void initForm();                                                            // 初始化页面
    void createTitle();                                                         // 创建标题
    void createHelp();                                                          // 创建帮助操作
    void createGeneral();                                                       // 创建 基础选项
    void createAdv();                                                           // 创建 高级选项

    void createOperate();                                                       // 创建 操作
    void createHostName(WTable  * pTable);                                      // 创建 主机名称

    void enumBaseParam();                                                       // 枚举 基础数据
    void setTitle(string &szDeviceType);                                        // 设置 标题

    typedef list<SVParamItem*>::iterator listItem;
    list<SVParamItem*> m_lsBasicParam;                                          // 基础选项数据list
    list<SVParamItem*> m_lsDyn;

    SVDependTable *  m_pAdvTable;                                               // 高级选项

    WText         * m_pTitle;                                                   // 标题
    WText         * m_pHostHelp;                                                // 主机名称帮助
    WText         * m_pHostNameHelp;                                            // 主机名称提示
    WPushButton   * m_pBack;                                                    // 返回
    WPushButton   * m_pSave;                                                    // 保存
    WPushButton   * m_pCancel;                                                  // 取消
    WPushButton   * m_pTest;
    WPushButton   * m_pListDynBtn;
    WPushButton   * m_pListDynData;
    WPushButton   * m_pSaveMonitor;
    WPushButton   * m_pCancelSaveMonitor;
    WLineEdit     * m_pDeviceTitle;                                             // 设备标题


    SVShowTable   * m_pGeneral;                                                 // 基础信息表
    WTable        * m_pQuickAdd;
    WTable        * m_pContentTable;
    WTable        * m_pSubContent;
    string m_szEditIndex;                                                       // 待修改的设备
    string m_szDeviceType;                                                      // 设备类型
    string m_szParentIndex;                                                     // 父节点
    string m_szDeviceName;                                                      // 设备名称
    string m_szDeviceID;                                                        // 设备索引
    string m_szQueryString;                                                     //
    string m_szDllName;                                                         //
    string m_szFuncName;                                                        // 

    string m_szQuickAdd;                                                        // 快速添加监测器列表
	string m_szQuickAddSel;                                                     // 快速添加监测器缺省处于选择状态的监测器
    string m_szNetworkset;                                                      // 待添加设备是否是网络设备
    
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

    bool m_bShowHelp;                                                           // 显示/隐藏帮助
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
    string    m_szIDCUser;                                                      // IDC 用户
    string    m_szIDCPwd;                                                       // IDC 用户密码
    CUser   * m_pSVUser;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
