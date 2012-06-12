#ifndef _SiteView_ECC_List_Table_H_
#define _SiteView_ECC_List_Table_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WTable"
class WText;
class WImage;
class WCheckBox;
class WPushButton;

#include <map>
#include <list>
#include <string>

using namespace std;

#include "../../kennel/svdb/svapi/svdbapi.h"

typedef void (*ShowAddNew)(string);

class CEccImportButton;
class CEccButton;

class CEccListTable : public WTable
{
    //MOC: W_OBJECT CEccListTable:WTable
    W_OBJECT;
public:
    CEccListTable(WContainerWidget *parent = NULL, bool bHasOperate = true, bool bCreateHasNo = true, 
        bool bGridTable = true, bool bControl = true);

    // public fuction list
    // 添加复选框列表
    void                addCheckList(string szIndex, WCheckBox *pCheck = NULL);
    // 清理复选框列表
    void                clearCheckList();
    // 得到数据列表
    WTable *            getListTable();
    // 隐藏子表
    void                hideSubTable();
    // 隐藏无数据
    void                hideNoChild();
    // 设置添加按钮的显示文字
    void                setAddNewTitle(string szTitle);
    // 设置添加按钮的提示信息
    void                setAddNewTip(string szTooltip);
    // 设置添加按钮调用的函数
    void                setAddNewFunc(void(*pfunc)(string));
    // 设置数据列表的列
    void                setCols(list<string> &lsCols);
    // 设置当前操作ID
    void                setCurrentID(string szCurrentID);
    // 设置数据表的高
    void                setHeight(int nHeight);
    // 设置操作按钮
    void                setOperaters(list<int> &lsOperaters, int nType);
    //
    void                setOperatePurview(int nPurview, int nType);
    // 设置无数据显示文字
    void                setNoChild(string szText);
    // 设置标题
    void                setTitle(string szTitle);
    // 设置数据表的宽度
    void                setWidth(int  nWidth);
    // 显示无数据
    void                showNoChild();
    //
    void                showSubTable();
    //
    void                showHideSort(bool bShow);
private:
    //MOC: SLOT CEccListTable::ShowHideSub()
    void    ShowHideSub();
    //MOC: SLOT CEccListTable::SelectAll()
    void    SelectAll();
    //MOC: SLOT CEccListTable::SelectNone()
    void    SelectNone();
    //MOC: SLOT CEccListTable::InvertSelect()
    void    InvertSelect();
    //MOC: SLOT CEccListTable::Confirm()
    void    Confirm();
    //MOC: SLOT CEccListTable::AddNew()
    void    AddNew();
    //MOC: SLOT CEccListTable::Copy()
    void    Copy();
    //MOC: SLOT CEccListTable::Paste()
    void    Paste();
    //MOC: SLOT CEccListTable::Enable()
    void    Enable();
    //MOC: SLOT CEccListTable::Disable()
    void    Disable();
    //MOC: SLOT CEccListTable::DelSelect()
    void    DelSelect();
    //MOC: SLOT CEccListTable::RefreshSel()
    void    RefreshSel();
    //MOC: SLOT CEccListTable::Sort()
    void    Sort();
private:
    WTable              *m_pPath;
    WTable              *m_pSubTable;           // 数据表
    WTable              *m_pOperate;            // 操作
    WTable              *m_pSubOperate;
    WImage              *m_pControl;            // 隐藏/显示字表图片
    WText               *m_pTitle;              // 标题
    WText               *m_pNoChild;            // 无数据

    WPushButton         *m_pHideButton;

    CEccImportButton    *m_pAddNew;             // 添加按钮

    map<int, CEccButton*, less<int> >   m_OperateList;
private:
    // 初始化页面
    void                initForm(bool bHasOperate, bool bCreateNoChild, bool bGridTable, bool bControl);
    // 创建标题栏
    void                createTitle(bool bControl);
    // 创建数据子表
    void                createSubTable(WTable *pSubTable, bool bGridTable);
    // 创建操作信息
    void                createOpaerate(WTable *pSubTable);

    void                createHideConfirm(WTable *pSubTable);

    void                pasteDevice();

    void                pasteMonitor();

    bool                IsCanBePaste();

    // 是否显示数据表
    bool                m_bShowSub;
    // 是否有数据
    bool                m_bHasChild;
    // 是否已设置添加操作函数
    bool                m_bSetFunc;

    //
    string              m_szCurrentID;
    int                 m_nDataType;
    int                 m_nHideRow;

    // 复选框列表
    map<string, WCheckBox*, less<string> > m_lsCheckBox;

    list<string>                           m_lsSelIndex;
    // 添加调用函数
    ShowAddNew          m_pAddFunc;
    // 友元类
    friend class        CEccAdvanceTable;
};

#endif
