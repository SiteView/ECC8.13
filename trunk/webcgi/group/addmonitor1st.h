/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件: addmonitor1st.h
// 添加监测器第一步（枚举设备可以添加的监测器）
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_MONITOR_1ST_H_
#define _SV_ADD_MONITOR_1ST_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVMonitorList : public WTable
{
    //MOC: W_OBJECT SVMonitorList:WTable
    W_OBJECT;
public:
    SVMonitorList(WContainerWidget* parent = NULL, string szIDCUser = "default", 
        string szPwd = "localhost");
    void enumMonitorTempByType(string &szDeviceType, string &szDeviceID);               // 根据设备类型 枚举 监测器模板
    void SetUserPwd(string &szUser, string &szPwd);                                     // 设置IDC 用户 密码
    string getParentIndex() {return m_szDeviceID;};
public signals:
    //MOC: SIGNAL SVMonitorList::AddMonitorByType(int,string)
    void AddMonitorByType(int nMonitorType,string szDeviceIndex);                       // 选择监测器模板添加 监测器
    //MOC: SIGNAL SVMonitorList::Cancel()       
    void Cancel();                                                                      // 取消添加
private slots:
    //MOC: SLOT SVMonitorList::CancelAdd()
    void CancelAdd();                                                                   // 取消添加监测器
    //MOC: SLOT SVMonitorList::MonitorMTClicked(int)
    void MonitorMTClicked(int nMTID);                                                   // 监测器模版 选定处理
private:        
    //string m_szCancel;                                                                  // 取消
    //string m_szCancelTip;                                                               // 取消提示
    //string m_szTitle;                                                                   // 标题

    string m_szDeviceType;                                                              // 设备类型
    string m_szDeviceID;                                                                // 设备索引

    //void loadString();                                                                  // 加载字符串
    void initForm();                                                                    // 初始化

    void createTitle();                                                                 // 创建标题
    void createMonitorList();                                                           // 创建监测器模板列表
    void createOperate();

    void enumMonitor(string &szDeviceType);                                             // 枚举 监测器 模版

    WTable * m_pList;                                                                   // 列表
    WTable * m_pContentTable;
    WTable * m_pSubContent;
    WText  * m_pTitle;                                                                  // 标题
    
    WSignalMapper m_MonitorMap;                                                         // signal map
    void          removeMapping();

    list<WText*> m_lsName;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string   m_szIDCUser;                                                               // IDC 用户
    string   m_szIDCPwd;                                                                // IDC 用户密码
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
