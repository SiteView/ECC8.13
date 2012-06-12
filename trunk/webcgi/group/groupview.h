
#ifndef _SV_GROUP_VIEW_H_
#define _SV_GROUP_VIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WContainerWidget"
#include "../../opens/libwt/WSignalMapper"

#include <string>
#include <list>
#include <map>

using namespace std;

class WTable;
class WImage;
class WText;
class WLineEdit;
class WTextArea;
class WComboBox;
class WLineEdit;
class WPushButton;
class OperateLog;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "general.h"
#include "grouplist.h"
#include "devicelist.h"
#include "addgroup.h"
#include "adddevice1st.h"
#include "adddevice2nd.h"
#include "addmonitor1st.h"
#include "addmonitor2nd.h"
#include "batchadd.h"
#include "sortlist.h"
#include "svseview.h"
#include "addsvse.h"

#include "basefunc.h"

#include "../demotreeview/define.h"
#include "../userright/user.h"
#include "../base/OperateLog.h"

class SVMonitorview;

enum Active_View
{
    active_se_view,                 // SE 视图
    active_group_view,              // 组 视图
    active_monitor_view,            // 监测器视图
    active_add_group,               // 添加组
    active_add_se,                  // 添加 SE
    active_add_device1st,           // 添加设备 第一步 （选择设备类型）
    active_add_device2nd,           // 添加设备 第二步
    active_add_monitor1st,          // 添加监测器 第一步 （根据设备类型显示的可添加监测器不同）
    active_add_monitor2nd,          // 添加监测器 第二步
    active_edit_group,              // 编辑组
    active_edit_device,             // 编辑设备
    active_edit_monitor,            // 编辑监测器
    active_batch_add_monitor,       // 批量添加监测器
    active_sort_objects             // 排序
};



class SVGroupview : public WContainerWidget 
{
    //MOC: W_OBJECT SVGroupview:WContainerWidget
    W_OBJECT;
public:
    // 构造函数
    // 父 用户权限管理
    // 访问数据库用户 用户密码
    SVGroupview(WContainerWidget * parent = NULL, CUser *pUser = NULL, 
        string szIDCUser = "default", string szIDCPwd = "localhost");

    void SetUserPwd(string &szUser, string &szPwd);
    void deleteObject(string szIndex);

public signals:
    //MOC: EVENT SIGNAL SVGroupview::MenuItemResponse(MENU_RESPONSE)
    void MenuItemResponse(MENU_RESPONSE response);                          // 树同步
    //MOC: EVENT SIGNAL SVGroupview::ChangeSelNode(string)
    void ChangeSelNode(string szIndex);                                     // 修改选择的节点
    //MOC: EVENT SIGNAL SVGroupview::TranslateSuccessful()
    void TranslateSuccessful();                                             // 翻译成功
public slots:
    //MOC: SLOT SVGroupview::MenuItemRequestProc(MENU_REQUEST)
    void MenuItemRequestProc(MENU_REQUEST request);                         // 树菜单处理函数
    //MOC: SLOT SVGroupview::backParent()
    void backParent();                                                      // 返回上一级
    //MOC: SLOT SVGroupview::AddNewGroup()
    void AddNewGroup();                                                     // 添加新的组
    //MOC: SLOT SVGroupview::EditGroupParam(string)
    void EditGroupParam(string szIndex);                                    // 编辑组
    //MOC: SLOT SVGroupview::showIconView()
    void showIconView();                                                    // 图标视图
    //MOC: SLOT SVGroupview::showListView()
    void showListView();                                                    // 列表视图
    //MOC: SLOT SVGroupview::AddGroupData(string,string)
    void AddGroupData(string szName,string szIndex);                        // 成功添加子组处理函数
    //MOC: SLOT SVGroupview::EditGroupData(string , string)
    void EditGroupData(string szName, string szIndex);                      // 编辑组成功处理函数
    //MOC: SLOT SVGroupview::ChangeGroupState(string,int)
    void ChangeGroupState(string szGroupID, int nState);                    // 更新组状态
    //MOC: SLOT SVGroupview::showMainView()
    void showMainView();                                                    // 显示主视图
    //MOC: SLOT SVGroupview::AddNewDevice()
    void AddNewDevice();                                                    // 添加设备
    //MOC: SLOT SVGroupview::AddDevice2nd(string)
    void AddDevice2nd(string szIndex);                                      // 添加设备第二步
    //MOC: SLOT SVGroupview::EnumDevice(string)
    void EnumDevice(string szIndex);                                        // 枚举设备
    //MOC: SLOT SVGroupview::EditDeviceByIndex(string)
    void EditDeviceByIndex(string szDeviceIndex);                           // 修改设备
    //MOC: SLOT SVGroupview::AddNewDeviceSucc(string,string)
    void AddNewDeviceSucc(string szName, string szIndex);                   // 添加设备成功
    //MOC: SLOT SVGroupview::EditDeviceSuccByID(string,string)
    void EditDeviceSuccByID(string szName, string szIndex);                 // 修改设备成功
    //MOC: SLOT SVGroupview::ChangeDeviceState(string,int)
    void ChangeDeviceState(string szDeviceID, int nState);                  // 更新设备状态
    //MOC: SLOT SVGroupview::EnterDeviceByID(string)
    void EnterDeviceByID(string szDeviceID);                                // 进入组（显示监测器视图）
    //MOC: SLOT SVGroupview::EnterNewDeviceByID(string)
    void EnterNewDeviceByID(string szDeviceID);                             // 进入新添加的设备
    //MOC: SLOT SVGroupview::AddMonitor(string,string)
    void AddMonitor(string szDeviceType,string szIndex);                    // 添加监测器
    //MOC: SLOT SVGroupview::CancelAddMonitor()
    void CancelAddMonitor();                                                // 取消添加监测器
    //MOC: SLOT SVGroupview::AddNewMonitorByType(int,string)
    void AddNewMonitorByType(int nMTID,string szDeviceID);                  // 根据监测器的 MTID和设备ID添加新的监测器
    //MOC: SLOT SVGroupview::AddMonitorSucc(string,string)
    void AddMonitorSucc(string szName,string szIndex);                      // 添加监测器成功
    //MOC: SLOT SVGroupview::EditMonitorSuccByID(string,string)
    void EditMonitorSuccByID(string szName,string szIndex);                 // 编辑监测器成功
    //MOC: SLOT SVGroupview::EditMonitorByIndex(string)
    void EditMonitorByIndex(string szMonitorIndex);                         // 修改监测器
    //MOC: SLOT SVGroupview::BackMonitorList()
    void BackMonitorList();                                                 // 返回监测器列表
    //MOC: SLOT SVGroupview::BackGroupDeviceList(string)
    void BackGroupDeviceList(string szGroupID);                             // 返回到组视图
    //MOC: SLOT SVGroupview::EditSVSESuccByIndex(string,string)
    void EditSVSESuccByIndex(string szName, string szSEID);                 // 编辑SE成功
    //MOC: SLOT SVGroupview::EditSVSEByIndex(string)
    void EditSVSEByIndex(string szSEID);                                    // 编辑SE
    //MOC: SLOT SVGroupview::enterSVSE(string)
    void enterSVSE(string szSEID);                                          // 进入SE
    //MOC: SLOT SVGroupview::enterGroup(string)
    void enterGroup(string szGroupID);                                      // 进入组
    //MOC: SLOT SVGroupview::backSVSEView()
    void backSVSEView();	                                                // 显示SE 视图
    //MOC: SLOT SVGroupview::DelDeviceByIdProc(string,string)
    void DelDeviceByIdProc(string szName, string strId);                    // 删除设备通知处理函数
    //MOC: SLOT SVGroupview::DelGroupByIdProc(string,string)
    void DelGroupByIdProc(string szName, string strId);                     // 删除组通知处理函数
    //MOC: SLOT SVGroupview::BatchAddMonitor()
    void BatchAddMonitor();                                                 // 批量添加
    //MOC: SLOT SVGroupview::ReloadCurrentView()
    void ReloadCurrentView();                                               // 重新加载当前视图
    //MOC: SLOT SVGroupview::SortObjects(int)
    void SortObjects(int nType);                                            // 排序
    //MOC: SLOT SVGroupview::RefreshCurrentList()
    void RefreshCurrentList();                                              // 排序后重新加载当前视图
    //MOC: SLOT SVGroupview::enterGroupByID(const std::string)
    void enterGroupByID(const std::string szGroupID);                       // 根据组索引直接进入某一组
	//MOC: SLOT SVGroupview::Translate()
	void Translate();                                                       // 翻译
	//MOC: SLOT SVGroupview::ExChange()
	void ExChange();                                                        // 重新加载
    //MOC: SLOT SVGroupview::CopyNewDeviceSucc(string,string)
    void CopyNewDeviceSucc(string szName, string szIndex);                  // 拷贝设备成功
    //MOC: SLOT SVGroupview::CopyNewMonitorSucc(string,string)
    void CopyNewMonitorSucc(string szName, string szIndex);                 // 拷贝监测器成功
private:
    //////////////////////////////////////////////////////////////////////////////////
    void            AddTitle();                             // 添加组视图的标题
    void            AddStandard();                          // 添加组视图的基础信息
    void            AddEntity();                            // 添加组视图的设备表
    void            AddGroup();                             // 添加组视图的子组表
    void            AddViewControl();                       // 添加组视图的控制表
    void            ShowActivateView(int nActivateView);    // 更改当前显示视图
    void            createHideButton();                     // 创建隐藏按钮
    // 当前正在浏览父是否被删除
    bool            isCurEditParentDel(string szIndex, string szCurrentID = "");
    // 记录操作日志
    void            AddOperaterLog(int &nOperateType, int &nObjectType, string &szOperateMsg);
    //////////////////////////////////////////////////////////////////////////////////
    void InitForm();                // 初始化
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    struct GENERAL_ACTIVEX_LIST
    {
        GENERAL_ACTIVEX_LIST()
        {
            m_pGroupview = NULL;        // 主表
            m_pGeneral = NULL;          // 主内容表
            m_pStandard = NULL;         // 基础信息
            m_pGroup = NULL;            // 子组
            m_pDevice = NULL;           // 设备
            m_pBackParent = NULL;       // 返回上一级按钮
            m_ptxtTime = NULL;          // 刷新时间
        }
        WTable * m_pGroupview;
        WTable * m_pGeneral;
        SVGeneral * m_pStandard;  
        SVGroupList * m_pGroup;
        SVEnumDevice * m_pDevice;       
        WPushButton * m_pBackParent;
        WText  * m_ptxtTime;
    };

    //////////////////////////////////////////////////////////////////////////////////
    GENERAL_ACTIVEX_LIST m_GeneralList;
    //////////////////////////////////////////////////////////////////////////////////    

    SVAddGroup          * m_pAddGroup;              // 添加组
    SVDeviceList        * m_pDeviceList;            // 设备列表（添加设备第一步）
    SVDevice            * m_pDevice;                // 添加设备第二步
    SVMonitorview       * m_pMonitorview;           // 监测器视图
    SVMonitorList       * m_pMonitorList;           // 监测器列表（添加监测器第一步）
    SVMonitor           * m_pMonitor;               // 添加监测器第二步
    SVSEView            * m_pSVSEView;              // SE视图
    SVAddSE             * m_pAddSVSE;               // 添加SE
    SVBatchAdd          * m_pBatchAdd;              // 批量添加
    CSVSortList         * m_pSortForm;              // 排序
    WLineEdit           * m_pcurEditIndex;          // 当前正在编辑
    WTableCell          * m_pTitleCell;             // 标题所在Cell
	WPushButton         * m_pTranslateBtn;          // 翻译按钮
	WPushButton         * m_pExChangeBtn;           // 刷新
    list<WText*>          m_lsPath;	                // 组路径
    WSignalMapper         m_GroupName;              // 组名称绑定MAP
    //////////////////////////////////////////////////////////////////////////////////    
    //bool m_bShowList;                               // 是否是列表试图
    //bool m_bEntityHide;                             // 设备是否隐藏
    //bool m_bGroupHide;                              // 组是否隐藏
    ////////////////////////////////////////////////////////////////////////////////// 
    string              m_szIDCUser;                    // User's ID
    string              m_szIDCPwd;                     // User's Password
    string              m_szGlobalEvent;                // 刷新事件
    string              m_szEditIndex;                  // 当前正在编辑的组||设备的索引
    string              m_szActiveOptIndex;             // 当前操作ID
    string              m_szUserShowName;               // 当前登录用户的显示名称

    CUser             * m_pSVUser;                      // 用户
    
	int		            m_nActiveView;                  // 当前激活视图
	int                 m_nPreviewView;                 // 前一视图
    int                 m_nActiveOptType;               // 当前操作
    OperateLog          m_pOperateLog;
    list<string>        m_lsNewMonitorList;             // 新监测器列表

    static char         m_szLogData[1025];
    friend              class SVMonitorview;            // 友元类
    friend              class DemoTreeList;
};


#endif

