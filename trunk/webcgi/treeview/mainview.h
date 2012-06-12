#ifndef _SiteView_ECC_Main_View_H_
#define _SiteView_ECC_Main_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WSignalMapper"
class WText;
class WLineEdit;
class WPushButton;

#include <string>
#include <list>

using namespace std;

class CEccTreeView;
class CEccRightView;
class CEccTreeDevice;

#include "resstring.h"

class CEccMainView : public WTable
{
    //MOC: W_OBJECT CEccMainView:WTable
    W_OBJECT;
public:
    CEccMainView(WContainerWidget *parent = NULL);
    string getTreeTableName();

    virtual void refresh();
    //static void SetOldSel(const string &szName);

    static CEccRightView    *m_pRightView;                  // 右视图
    static CEccTreeView     *m_pTreeView;                   // 树形视图
    static string           m_szIDCUser;                    // IDC用户
    static string           m_szAddr;                       // 地址
    static string           m_szGlobalEvent;                // 刷新事件
    static string           m_szCurrentOpt;                 // 当前操作索引
    static string           m_szLeftScroll;                 // 树的滚动区域
private://slots
    //MOC: SLOT CEccMainView::EccObjectClick()
    void    EccObjectClick();                               // 对象操作响应函数
    //MOC: SLOT CEccMainView::EccMenuClick()
    void    EccMenuClick();                                 // 节点菜单响应函数
    //MOC: SLOT CEccMainView::ConfirmDelete()
    void    ConfirmDelete();                                // 确认删除
    //MOC: SLOT CEccMainView::RefreshState()
    void    RefreshState();                                 // 状态刷新
private:
    void    createFrame();                                  // 创建框架
    void    createHideObject();                             // 创建隐藏对象
    //void    createGlobalEvent();

    void    AddJsParam(string name, string value);          // 添加JaveScript变量
    void    TestDevice(const string &szIndex);              // 测试设备

    void    RefreshDevice(const CEccTreeDevice *pDevice);   // 刷新设备
private:

    SVResString             m_pResString;                   // 资源字符
    // WT
    WPushButton             *m_pbtnConfirm;                 // 确认按钮（隐藏）
    WPushButton             *m_pbtnRefresh;                 // 刷新按钮（隐藏）
    WLineEdit               *m_pCurrentID;                  // 当前对象索引（隐藏）
    WLineEdit               *m_pCurOperate;                 // 当前操作（隐藏）
private:
    string                  m_szCurrentCopy;                // 当前拷贝
    string                  m_szCurrentConfirm;             // 当前等待确认删除对象的索引

    bool                    m_bFirstLoad;
};

#endif
