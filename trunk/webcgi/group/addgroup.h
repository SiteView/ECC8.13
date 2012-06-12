/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件: addgroup.h
// 添加/编辑组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_GROUP_VIEW_H_
#define _SV_ADD_GROUP_VIEW_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "category.h"
#include "dependtable.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"

#include "../userright/user.h"
#include "basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVAddGroup : public WTable
{
    //MOC: W_OBJECT SVAddGroup:WTable
    W_OBJECT;
public:
    SVAddGroup(WContainerWidget * parent = NULL, CUser *pUser = NULL, string szIDCUser = "default", 
        string szIDCPwd = "localhost");
    void EditGroup(string &szIndex);                                            // 编辑组
    void SetParentIndex(string &szIndex) { m_szParentIndex = szIndex; };        // 设置父节点索引
    string GetParentIndex(){return m_szParentIndex;};                           // 得到父节点索引        
    void ResetParam();                                                          // 重置数据
    void SetUserPwd(string &szUser, string &szPwd);                             // 设置IDC 用户 密码    
public signals:
    //MOC: SIGNAL SVAddGroup::editGroupName(string,string)
    void editGroupName(string strName,string szIndex);                          // 编辑组 成功
    //MOC: SIGNAL SVAddGroup::addGroupName(string,string)
    void addGroupName(string strName,string szIndex);                           // 添加组成功
    //MOC: SIGNAL SVAddGroup::backMain()
    void backMain();                                                            // 返回主页面
private slots:
    //MOC: SLOT SVAddGroup::backPreview()
    void backPreview();                                                         // 返回上一级页面
    //MOC: SLOT SVAddGroup::saveGroup()
    void saveGroup();                                                           // 保存 数据
    //MOC: SLOT SVAddGroup::showHelp()
    void showHelp();                                                            // 显示/隐藏帮助
	//MOC: SLOT SVAddGroup::Translate()
	void Translate();                                                           //翻译
private:
    SVDependTable   * m_pAdvanced;                                              // 高级选项表
    WPushButton     * m_pSave;
    WPushButton     * m_pCancel;
    WLineEdit       * m_pName;                                                  // 组名称
    WTable          * m_pGeneral;                                               // 主
    WTable          * m_pContentTable;
    WTable          * m_pSubContent;
    WText           * m_pNameHelp;                                              // 组名称帮助
    WText           * m_pTitle;                                                 // 标题

    void initForm();                                                            // 初始化界面
    void addGroupAdv();                                                         // 高级选项
    void addGroupTitle();                                                       // 组标题
    void addGroupGeneral();                                                     // 基础选项
    void addGroupOperate();                                                     // 操作

    string m_szEditIndex;                                                       // 编辑标题
    string m_szParentIndex;                                                     // 父节点 索引
    bool m_bShowHelp;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string      m_szIDCUser;                                                    // IDC 用户
    string      m_szIDCPwd;                                                     // IDC 用户密码
    CUser     * m_pSVUser;

	//翻译
	WPushButton * m_pTranslateBtn;	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
