/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_GORUP_LIST_H_
#define _SV_GORUP_LIST_H_
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../demotreeview/define.h"
#include "../userright/user.h"

#include "basefunc.h"

class SVGroupList : public WContainerWidget
{
    //MOC: W_OBJECT SVGroupList:WContainerWidget
    W_OBJECT;
public:
    SVGroupList(WContainerWidget* parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    bool                isChildEdit(string szIndex);
    bool                isParentEdit(string szIndex);
    bool                isInGroup(string& szIndex);
    void                AddGroup(string &szName, string &szIndex);
    void                BackGroup(string &szIndex);
    void                DelGroup(string &szIndex);
    void                delGroupRow(string &szIndex);
    void                EditGroup(string &szName, string &szIndex);
    void                EnterGroupByID(string &szIndex);
    void                SetUserPwd(string &szUser, string &szPwd);
    void                refreshNamePath();
    void                refreshGroup(string szIndex);

    const char *        getGroupName();
    const char *        getGroupDesc();
    const char *        getGroupIndex() {return m_szIndex.c_str();}
    list<base_param>&   getGroupPath(){return m_lsPath;};
    int                 m_nDeviceCount;
    int                 m_nMonitorCount;
    int                 m_nMonitorErrCount;
    int                 m_nMonitorWarnCount;
    int                 m_nMonitorDisableCount;
    string              m_szAdvState;
public signals:
    //MOC: SIGNAL SVGroupList::AddNewGroup()
    void AddNewGroup();
    //MOC: SIGNAL SVGroupList::EditGroupByID(string)
    void EditGroupByID(string szEditID);
    //MOC: SIGNAL SVGroupList::EnumDeviceByID(string)
    void EnumDeviceByID(string szEditID);
    //MOC: SIGNAL SVGroupList::sortGroupsList(int)
    void sortGroupsList(int nType);
    //MOC: SIGNAL SVGroupList::ChangeGroupState(string,int)
    void ChangeGroupState(string szGroupID, int nMonitorState);
    //MOC: SIGNAL SVGroupList::DeleteGroupSucc(string,string)
    void DeleteGroupSucc(string szName, string szIndex);
    //MOC: SIGNAL SVGroupList::DeleteDeviceSucc(string,string)
    void DeleteDeviceSucc(string strName,string szIndex);                          // 拷贝设备成功
private slots:
    //MOC: SLOT SVGroupList::selAll()
    void selAll();
    //MOC: SLOT SVGroupList::selNone()
    void selNone();
    //MOC: SLOT SVGroupList::invertSel()
    void invertSel();
    //MOC: SLOT SVGroupList::delSel()
    void delSel();
    //MOC: SLOT SVGroupList::add()
    void add();
    //MOC: SLOT SVGroupList::editGroup()
    void editGroup();
    //MOC: SLOT SVGroupList::gotoGroup()
    void gotoGroup();
    //MOC: SLOT SVGroupList::changeState()
    void changeState();
    //MOC: SLOT SVGroupList::delSelGroup()
    void delSelGroup();
    //MOC: SLOT SVGroupList::deleteGroup()
    void deleteGroup();
    //MOC: SLOT SVGroupList::enableSelGroup()
    void enableSelGroup();
    //MOC: SLOT SVGroupList::disableSelGroup()
    void disableSelGroup();
    //MOC: SLOT SVGroupList::disableGroupSucc()
    void disableGroupSucc();
    //MOC: SLOT SVGroupList::sortGroups()
    void sortGroups();
private:
    //function list
    //void            loadString();                                       // 加载资源字符串
    void            initForm();                                         // 初始化

    void            addGroupList(string &szName, string &szIndex);      // 添加子组到组列表中
    void            createHideButton();                                 // 创建隐藏按钮
    void            createGroupList(WTable * pTable);                   // 创建组列表
    void            DelDevice(string &szIndex);                         // 删除设备
    void            editGroupList(string &szName, string &szIndex);     // 根据组索引编辑组显示名称
    void            enumGroup(string &szIndex);                         // 枚举所有组
    void            enterGroup(string &szIndex);                        // 进入组
    void            enumRight();                                        // 枚举权限

    void            createOperate(WTable * pTable);                     // 创建操作
    void            createSelOperate();                                 // 创建 选择操作
    void            createEnableOperate();                              // 创建 启用/禁用操作
    void            createRefreshOperate();                             // 创建 刷新操作
    void            createDelOperate();                                 // 创建 删除操作
    void            changeOperateState();                               // 修改 操作按钮的显示状态
    void            changeDelState();                                   // 修改 删除按钮显示状态
    void            changeSelState();                                   // 修改 选择按钮显示状态
    void            changeEnableState();                                // 修改 启用/禁用按钮显示状态

    // 判断组是否被禁止并返回组的状态描述信息
    bool            isDisable(string &szGroupID, string &szState, bool bAddBR = true);
    // 根据组索引创建路径
    bool            makePath(string &szGroupID, list<base_param> &lsPath);
    // 根据组索引得到组名称
    string          getGroupName(string szIndex);
private:
    SVTable         m_svGroup;                          // 记录控件表格
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string          m_szIndex;                          // 当前组的索引（ID）
    string          m_szGroupName;                      // 当前组的名称
    string          m_szGroupDesc;                      // 当前组的描述
    string          m_szDelSelIndex;                    // 当前选择删除的索引
    string          m_szIDCUser;                        // user's id
    string          m_szIDCPwd;                         // user's password

    //string          m_szDelSelTip;                      // IDS_Delete_Sel_Group_Tip
    //string          m_szSelAllTip;                      // IDS_All_Select
    //string          m_szSelNoneTip;                     // IDS_None_Select
    //string          m_szInvertSelTip;                   // IDS_Invert_Select
    //string          m_szSortTip;                        // IDS_Sort
    //string          m_szAdd;                            // IDS_Add_Group
    //string          m_szAddTip;                         // IDS_Add_Group_Tip
    //string          m_szColState;                       // IDS_State
    //string          m_szColDesc;                        // IDS_State_Description
    //string          m_szColEdit;                        // IDS_Edit
    //string          m_szColName;                        // IDS_Name
    //string          m_szColLast;                        // IDS_Table_Col_Last_Refresh
    //string          m_szColDel;                         // IDS_Delete
    //string          m_szDelTip;                         // IDS_Delete_Group_Tip
    //string          m_szEditTip;                        // IDS_Edit
    //string          m_szEnableTip;                      // IDS_Enable_Group
    //string          m_szDisableTip;                     // IDS_Disable_Group
    //string          m_szDelAsk;                         // IDS_Delete_Group_Confirm
    //string          m_szDelSelAsk;                      // IDS_Delete_Sel_Group_Confirm
    //string          m_szTitle;                          // IDS_Sub_Group
    //string          m_szGroupsDisable;                  // IDS_Group_Can_not_Disable
    //string          m_szGroupsEnable;                   // IDS_Group_Can_not_Enable
    //string          m_szForver;                         // IDS_Group_Disable_Forver
    //string          m_szTemprary;                       // IDS_Group_Disable_Temprary
    //string          m_szStartTime;                      // IDS_Start_Time
    //string          m_szEndTime;                        // IDS_End_Time
    //string          m_szNoGroup;                        // IDS_GROUP_LIST_IS_NULL    
    //string          m_szMonitorDisable;                 // IDS_Monitor_Disable_Count
    //string          m_szDeviceCount;                    // IDS_Device_Count
    //string          m_szMonitorCount;                   // IDS_Monitor_Count
    //string          m_szMonitorError;                   // IDS_Monitor_Error_Count
    //string          m_szMonitorWarn;                    // IDS_Monitor_Warn_Count
    //string          m_szOperateGroup;                   // IDS_Group

    CUser           * m_pSVUser;                        // 用户权限管理类
    bool            m_bHasAddRight;                     // 是否有添加子组权限
    bool            m_bHasDelRight;                     // 是否有删除子组权限
    bool            m_bHasEditRight;                    // 是否有编辑子组权限
    bool            m_bHasSortRight;                    // 是否有排序显示顺序权限
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WPushButton     * m_pBtnHide;                       // 禁用/启用组成功 按钮
    WPushButton     * m_pBtnHideDel;                    // 删除所有所选组 按钮
    WPushButton     * m_pBtnRefresh;                    // 更新所选组状态 按钮
    WPushButton     * m_pBtnDelSel;                     // 删除所选组 按钮
    WPushButton     * m_pBtnEnterGroup;                 // 进入所选组 按钮
    WPushButton     * m_pBtnEdit;                       // 编辑所选组 按钮
    WPushButton     * m_pAdd;                           // 添加按钮
    WLineEdit       * m_pCurrentGroup;                  // 当前操作的组
    WImage          * m_pDel;                           // 删除（图片）按钮
    WImage          * m_pEnable;                        // 启用（图片）按钮
    WImage          * m_pDisable;                       // 禁用（图片）按钮
    WImage          * m_pSort;                          // 排序（图片）按钮
    WImage          * m_pSelAll;                        // 全选（图片）按钮
    WImage          * m_pSelNone;                       // 取消全选（图片）按钮
    WImage          * m_pSelInvert;                     // 反选（图片）按钮
    WTable          * m_pGroupList;                     // 组列表
    WTable          * m_pOperate;                       // 操作功能表
    WText           * m_pHasNoChild;                    // 无子组 文字控件
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    list<base_param> m_lsPath;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
