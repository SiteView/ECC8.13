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
#include "../../opens/libwt/WApplication"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../group/showtable.h"

#include "../group/paramitem.h"

#include "dependtable.h"
#include "../userright/user.h"
#include "../group/basefunc.h"
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
    void ClearData(string &szIndex, WApplication *szApp);                       // 清理数据
private slots:
    //MOC: SLOT SVDevice::showHelp()
    void showHelp();                                                            // 显示帮助
    //MOC: SLOT SVDevice::TranslateNew()
    void TranslateNew();                                                        // 翻译
    //MOC: SLOT SVDevice::ExChange()
    void ExChange();                                                            // 刷新
private:
    void initForm();                                                            // 初始化页面
    void createTitle();                                                         // 创建标题
    void createHelp();                                                          // 创建帮助操作
    void createGeneral();                                                       // 创建 基础选项
    void createAdv();                                                           // 创建 高级选项

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
    WLineEdit     * m_pDeviceTitle;                                             // 设备标题


    SVShowTable   * m_pGeneral;                                                 // 基础信息表
    WTable        * m_pQuickAdd;
    WTable        * m_pContentTable;
    WTable        * m_pSubContent;
    string m_szDeviceType;                                                      // 设备类型
    string m_szDeviceName;                                                      // 设备名称
    

    bool m_bShowHelp;                                                           // 显示/隐藏帮助
    
    typedef map<string, string, less<string> > SVReturnMap;
    typedef map<string, string, less<string> >::iterator SVReturnItem;
	map<string, string, less<string> > m_DeviceParam;
	bool m_bChanged;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string    m_szIDCUser;                                                      // IDC 用户
    string    m_szIDCPwd;                                                       // IDC 用户密码
    CUser   * m_pSVUser;
	WApplication * m_pAppSelf;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
