/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件: addsvse.h
// 添加或者修改SE
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_SVSE_H_
#define _SV_ADD_SVSE_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "category.h"
#include "dependtable.h"

#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"

#include "../../kennel/svdb/svapi/svapi.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVAddSE : public WTable
{
    //MOC: W_OBJECT SVAddSE:WTable
    W_OBJECT;
public:
    SVAddSE(WContainerWidget * parent = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    void AddSVSE();                                     // 添加 SE
    void EditSVSE(string &szIndex);                     // 编辑 SE    
    void SetUserPwd(string &szUser, string &szPwd);     // 设置 IDC 用户和密码
public signals:
    //MOC: SIGNAL SVAddSE::EditSVSESucc(string,string)
    void EditSVSESucc(string strName,string szIndex);   // 编辑SE 成功
    //MOC: SIGNAL SVAddSE::AddSVSESucc(string,string)
    void AddSVSESucc(string strName,string szIndex);    // 添加SE 成功
    //MOC: SIGNAL SVAddSE::backSVSEView()
    void backSVSEView();                    // 返回上一级页面
private slots:
    //MOC: SLOT SVAddSE::backPreview()
    void backPreview();                     // 返回上一级页面
    //MOC: SLOT SVAddSE::saveSVSE()
    void saveSVSE();                        // 保存修改
    //MOC: SLOT SVAddSE::showHelp()
    void showHelp();                        // 显示帮助
private:
    WLineEdit       * m_pName;              // SE名称
    //WLineEdit       * m_pHost;              // 主机
    //WTextArea       * m_pDescription;       // 描述
    WTable          * m_pGeneral;           // 主
    WTable          * m_pContentTable;
    WTable          * m_pSubContent;
    WText           * m_pNameHelp;          // SE名称帮助
    WText           * m_pTitle;             // 标题
    //WText           * m_pHostHelp;          // 主机名称帮助
    //WText           * m_pDescriptionHelp;   // 描述信息帮助
    WPushButton     * m_pSave;
    WPushButton     * m_pCancel;

    void initForm();            // 初始化页面

    //void addAdvance();          // 添加高级属性
    void addTitle();            // 添加标题
    void addGeneral();          // 添加基础选项
    void addOperate();          // 添加操作
    void resetData();           // 重置数据

    string m_szEditIndex;       // 修改的SE 索引
    bool m_bShowHelp;           // 是否显示帮助信息
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string      m_szIDCUser;    // IDC 用户
    string      m_szIDCPwd;     // IDC 用户密码
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file