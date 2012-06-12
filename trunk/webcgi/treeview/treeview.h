#ifndef _SiteView_ECC_Tree_View_H_
#define _SiteView_ECC_Tree_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;
class WImage;

#include <string>
#include <stack>
#include <list>
#include <map>

using namespace std;

#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../../kennel/svdb/libutil/time.h"

class CEccMainView;         // 主视图
class CEccTreeDevice;       // 设备节点
class CEccTreeGroup;        // 组节点
class CECCMonitor;          // 监测器
class CUser;                // 用户管理
class OperateLog;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView ECC base tree node class
class CEccTreeNode
{
public:
    CEccTreeNode();             // 构造函数
    ~CEccTreeNode();            // 析构函数
public:
    // 得到禁止总数
    int         getDisableCount()   const;
    // 得到错误总数
    int         getErrorCount()     const;
    // 得到监测器总数
    int         getMointorCount()   const;
    //
    int         getPurview()        const;
    // 得到显示顺序
    int         getShowIndex()      const;
    // 得到状态
    int         getState()          const;
    // 得到类型
    int         getType()           const;
    // 警告状态总数
    int         getWarnCount()      const;
    // 当前索引
    string      getECCIndex()       const;
    // 名称
    string      getName()           const;
    // 得到显示文字
    string      getShowText()       const;
    // 得到依靠于
    string      getDependsID()      const;
    // 得到依靠条件
    string      getCondition()      const;
    // 得到描述信息
    string      getDescription()    const;
    // 得到刷新时间
    string      getShowTime()       const;
private:
    // 重置所有成员变量
    virtual     void Reset();
    // 被禁止的监测器总数
    int         m_nDisableCount;
    // 处于错误状态的监测器总数
    int         m_nErrorCount;
    // 监测器总数
    int         m_nMonitorCount;
    // 当前的显示顺序
    int         m_nShowIndex;
    // 状态
    int         m_nState;
    // 类型
    int         m_nType;
    // 警告状态的监测器总数
    int         m_nWarnningCount;
    // 权限
    int         m_nPurview;
    // 当前索引
    string      m_szIndex;
    // 名称
    string      m_szName;
    // 显示文字
    string      m_szShowText;
    // 依靠于
    string      m_szDependsOn;
    // 依靠条件
    string      m_szDepCondition;
    // 描述
    string      m_szDescription;
    //
    string      m_szState;
    // 刷新时间
    TTime m_tRefreshTime;
    // 节点文字
    WText       *m_pTreeText;
    // 节点显示图片
    WImage      *m_pImgType;

    // 友元类
    friend      class       CEccTreeGroup;      // 组节点
    friend      class       CEccTreeDevice;     // 设备节点
    friend      class       CEccTreeView;       // 树视图
    friend      class       CEccMainView;       // 主视图
    friend      class       CEccRightView;      // 右视图
    friend      class       CEccSortTable;      // 排序
};
// end
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView ECC Monitor class
class CECCMonitor
{
public:
    // 构造函数
    CECCMonitor();
    // 析构函数
    ~CECCMonitor();
    // 得到监测器显示顺序
    int         getShowIndex()  const;
    // 得到监测器状态
    int         getState()      const;
    // 得到监测器索引
    string      getECCIndex()   const;
    //
    int         getMTID()       const;
    // 得到监测器名称
    string      getName()       const;
    // 得到监测器状态显示文字
    string      getShowText()   const;
    // 得到监测器刷新时间
    string      getShowTime()   const;
private:
    // 显示顺序
    int         m_nShowIndex;
    // 状态
    int         m_nState;
    // 监测器类型
    int         m_nMTID;
    // 索引
    string      m_szIndex;
    // 名称
    string      m_szName;
    // 显示文字
    string      m_szShowText;
    // 刷新时间
    TTime m_tRefreshTime;

    // 友元类
    friend      class CEccTreeDevice;           // 设备节点
    friend      class CEccTreeView;             // 树视图
    friend      class CEccSortTable;            // 排序
    friend      class CEccListTable;            // 列表
};
// End SiteView ECC Monitor class define
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEccTreeGroup : public CEccTreeNode
{
public:
    CEccTreeGroup();                            // 构造函数
    ~CEccTreeGroup();                           // 析构函数

    // 显示子表
    void        showSubTables();
    // 得到设备总数（包含子组内的设备）
    int         getDeviceCount()    const;
    // 追加组
    int         AppendGroup(const string &szIndex, const string &szName, const string &szDesc, const string &szDepends,
                            const string &szCondition, const string &szMenu, int nPurview);
    // 追加设备
    int         AppendDevice(const string &szIndex, const string &szName, const string &szDesc, const string &szDepends,
                             const string &szCondition, const string &szDeviceType, const string &szOsType,
                             const string &szIsNetworkSet, const string &szMenu, int nPurview);
private:

    virtual     void Reset();                               // 重置所有成员变量

    int         m_nDeviceCount;                             // 设备总数

    map<int, CEccTreeGroup, less<int> >    m_SubGroups;     // 子组
    map<int, CEccTreeDevice, less<int> >   m_Devices;       // 设备

    WImage      *m_pImageExpand;                            // 
    WTable      *m_pSubGroupsTable;                         // 子组表
    WTable      *m_pDevicesTable;                           // 设备表

    // 友元类
    friend      class CEccTreeView;                         // 树视图
    friend      class CEccGroupView;                        // 组视图
    friend      class CEccSortTable;                        // 排序
};
// end SiteView Ecc Group define
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView Ecc device
class CEccTreeDevice : public CEccTreeNode
{
public:
    CEccTreeDevice();
    ~CEccTreeDevice();
public:
    bool            MTCanUsing(int nMTID);              // 判断监测器是否能被此设备使用（粘贴监测器时使用）
    string          getRealDeviceType() const;          // 得到设备类型
    string          getDeviceType()     const;          // 得到设备显示类型
    string          getOSType()         const;          // 得到设备操作系统类型
    string          isNetworkSet()      const;          // 是否是网络设备

    int             AppendMonitor(const string &szIndex, const string &szName, int nMTID);      // 追加监测器
    void            EditMonitor(const string &szIndex, const string &szName);                   // 修改监测器
private:
    virtual         void Reset();                   // 重置所有成员变量
    string          m_szRealDeviceType;             // 设备类型
    string          m_szDeviceType;                 // 设备显示类型
    string          m_szOSType;                     // 操作系统类型
    string          m_szIsNetworkset;               // 是否是网络设备
    
    map<int, CECCMonitor, less<int> >  m_Monitors;  // 监测器表
    // 友元类
    friend      class CEccTreeView;             // 树视图
    friend      class CEccTreeGroup;            // 组节点
    friend      class CEccMonitorView;          // 监测器视图
    friend      class CEccSortTable;            // 排序
    friend      class CEccListTable;            // 列表
    friend      class CEccMainView;             // 主视图
};
// end SiteView Ecc Device define
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView TreeView
class CEccTreeView : public WTable
{
    //MOC: W_OBJECT CEccTreeView:WTable
    W_OBJECT;
public:
    CEccTreeView(WContainerWidget *parent = NULL, string szUserID = "1");
    // 生成se下所有文字的显示文字
    void            BuildSEShowText(string szSEID = "1");
    // 根据设备类型得到此类设备可使用的监测器列表
    void            GetDevMTList(const string &szDTType, list<int> &lsMTID);
    // 插入设备类型监测器对应列表
    void            InsertDevMTList(const string &szDTType, const list<int> &lsMT);
    // 重新加载树 
    void            reloadTree();
    // 重设登陆用户ID
    void            resetUserID(const string &szUserID);
    // 设置左和调整大小栏的名称
    void            setLeftResizeName(const string &szLeftName);
    // 根据索引得到Ecc Object
    static const    CEccTreeNode   *getECCObject(const string &szIndex);
    // 得到SE列表
    static const map<string, CEccTreeGroup, less<string> > & getSEList();
    // 得到SE的总数
    static int   getSVSECount();
    // 追加组
    static int   AppendGroup(const string &szIndex, const string &szName, const string &szDesc, 
                                            const string &szDepends, const string &szCondition);
    // 追加设备
    static int   AppendDevice(const string &szIndex, const string &szName, const string &szDesc, 
                                             const string &szDepends, const string &szCondition, const string &szDeviceType,
                                             const string &szOsType, const string &szIsNetworkSet);
    // 根据索引删除组
    static void  DeleteGroupByID(const string &szGroupID);
    // 根据索引删除设备
    static void  DeleteDeviceByID(const string &szDeviceID);
    // 编辑组
    static void  EditGroup(const string &szIndex, const string &szName, const string &szDesc, 
                                            const string &szDepends, const string &szCondition);
    // 编辑设备
    static void  EditDevice(const string &szIndex, const string &szName, const string &szDesc, 
                                            const string &szDepends, const string &szCondition);
    // 编辑 SE
    static void  EditSVSE(const string &szIndex, const string &szName);
    // 重新生成树节点
    static void  ReCreateTreeNode(const string &szIndex);
    // 创建 路径
    static void  MakePath(const string &szIndex, PAIRLIST &lsPath);
    //
    static void  AddOperaterLog(int nOperateType, int nObjectType, const string &szOperateMsg);
public:
    static      CUser               m_SVSEUser;         // 用户管理类
    static      OperateLog          m_OperateLog;
private:
    //MOC: SLOT CEccTreeView::ReloadTreeView()
    void    ReloadTreeView();
private:
    // 创建树形
    void    createContent();
    // 创建Title
    void    createTitle();
    // 初始化
    void    initForm();
    // 创建菜单
    string  makeMenuText(int nType, string szIndex, int &nPurview);
    // 枚举SiteView ECC SE
    void    EnumSVSE();
    // 枚举指定组索引下所有的子组和设备信息（SE是特殊组）
    void    EnumGroups(CEccTreeGroup &objGroup);
    // 枚举指定设备索引的设备信息
    void    EnumDevice(CEccTreeDevice &objDevice);
    // 枚举指定监测器索引的监测器信息
    void    EnumMonitor(CECCMonitor &objMonitor);
    // 得到指定监测器的状态信息
    void    getMonitorState(CECCMonitor &objMonitor);
    // 根据设备类型得到显示文字
    string  getDeviceShowType(const string &szDeviceType);
    // 是否被禁止 SE不能被禁止
    bool    isObjectDisable(MAPNODE &mainNode, string &szState, int nType);
    // 是否当前父节点被修改
    bool    isCurrentPathEdit(const string &szIndex);
    // 是否当前节点子节点被修改
    bool    isCurrentChildEdit(const string &szIndex);
    // 更新组信息
    void    UpdateGroupData(CEccTreeGroup &objGroup);
    // 创建树
    void    CreateTree();
    // 创建子组
    void    CreateSubGroups(CEccTreeGroup &objGroup, WTable *pSubTable);
private:
    WTable          *m_pTree;           // 树
    WText           *m_pCurSel;         // 当前选择
    WImage          *m_pHideOpt;        // 隐藏左视图控制按钮
    string          m_szCurSelIndex;    // 当前选择的索引

    CEccTreeGroup   m_objRootGroup;     // 根节点

    map<string, list<int>, less<string> >       m_DevMTList;    // 设备模板和监测器对应的表
    map<string, CEccTreeGroup, less<string> >   m_SVSEList;     // SiteView ECC SE表
    map<string, string, less<string> >          m_DevType;      // 设备模板名称和设备显示名称对应表

    // 友元类
    friend class    CEccMainView;       // 主界面
    friend class    CEccTreeGroup;      // 组节点
    friend class    CEccTreeDevice;     // 设备节点
    friend class    CEccRightView;      // 右视图
    friend class    CEccSortTable;      // 排序
};

#endif
