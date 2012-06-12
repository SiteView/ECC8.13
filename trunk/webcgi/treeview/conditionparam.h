/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_CONDITION_PARAM_H_

#define _SV_CONDITION_PARAM_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WButtonGroup"
#include "../../opens/libwt/WRadioButton"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"

#include "basefunc.h"
#include "returnitem.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum sv_condition_type
{
    SV_ERROR_CONDITION,
    SV_WARNING_CONDITION,
    SV_NORMAL_CONDITION
};

enum sv_condition_error
{
    sv_condition_is_null,
    sv_condition_relation_error,
    sv_condition_matching_error,
    sv_condition_type_error
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVConditionParam : public WTable
{
    //MOC: W_OBJECT SVConditionParam:WTable
    W_OBJECT;
public:
    SVConditionParam(WContainerWidget *parent = NULL, int nConditionType = SV_ERROR_CONDITION);

    void SetReturnList(list<SVReturnItem*> &lsReturn);                      // 设置返回值列表
    void SetMapNode(MAPNODE &mapnode);                                      // 设置 MAPNODE
    bool checkCondition(MAPNODE &alertnode);
    bool SaveCondition(MAPNODE &alertnode);                                 // 保存条件
    void SetCondition(MAPNODE &alertnode);                                  // 设置条件
    void showHelp(bool bShowHelp);                                          // 显示/隐藏帮助
    void clearReturnList() { m_lsReturn.clear(); };
    void setDefaultValue();
private slots:
    //MOC: SLOT SVConditionParam::showAddCondition()
    void showAddCondition();                                                // 显示添加条件表
    //MOC: SLOT SVConditionParam::hideAddCondition()
    void hideAddCondition();                                                // 隐藏添加条件表
    //MOC: SLOT SVConditionParam::addCondition()
    void addCondition();                                                    // 添加条件
private:
    string      m_szName;                                                   // 名称
    string      m_szLabel;                                                  // 显示标签
    string      m_szDefaultValue;                                           // 缺省值
    string      m_szHelp;                                                   // 帮助
    string      m_szTip;                                                    // 提示
    string      m_szStyle;                                                  // 样式

    int         m_nConditionType;                                           // 条件类型

    list<SVReturnItem*> m_lsReturn;                                         // 返回值
    list<string>        m_lsCondition;                                      // 条件

    WComboBox       * m_pReturnList;                                        // 返回值
    WComboBox       * m_pOperateList;                                       // 操作符
    WLineEdit       * m_pParam;                                             // 参数

    WButtonGroup    * m_pConditionGroup;
    WRadioButton    * m_pConditionOR;
    WRadioButton    * m_pConditionAND;

    WText           * m_pHelpText;
    WText           * m_pErrText;
    WText           * m_pLabel;
    WTextArea       * m_pConditionArea;

    WTable          * m_pOperate;
private:
    void createCondition();
    void createShowButton(int nRow);
    void createButtonGroup();
    void createAddButton(int nRow);
    void createHideButton();
    void createAddConidtion();
    void createHelp(int nRow);

    void EnumParam(MAPNODE &mapnode);

    void initForm();

    void loadCondition();
    void showErrorMsg(int nErrorCode);
    bool checkParamValue(string &szParam, string &szParamValue);
    void getParamLabel(string &szName);
    bool m_bShowHelp;
    
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
