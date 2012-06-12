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

#include "../group/basefunc.h"
#include "../group/returnitem.h"
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
//
//struct sv_condition_error_msg
//{
//    sv_condition_error_msg()
//    {
//        m_szConditionIsNull = "阀值不允许为空";             //IDS_Alert_Condition_NULL
//        m_szRelationErr = "条件关系连接符错误";             //IDS_Alert_Condition_Relation_Error
//        m_szMatchingErr = "匹配返回参数错误";               //IDS_Alert_Condition_Return_Param_Error
//        m_szTypeError   = "条件参数类型有误";               //IDS_Alert_Condition_Param_Error
//    };
//    static string m_szConditionIsNull;
//    static string m_szRelationErr;
//    static string m_szMatchingErr;
//    static string m_szTypeError;
//};
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
    bool SaveCondition(MAPNODE &alertnode);                                  // 保存条件
    void SetCondition(MAPNODE &alertnode);                                   // 设置条件
    void showHelp(bool bShowHelp);                                          // 显示/隐藏帮助
    void clearReturnList() { m_lsReturn.clear(); };
    void setDefaultValue();
    //void resetDefaultValue();
    //const string GetStringValue();
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

    //string      m_szAdd;                                                    // 添加
    //string      m_szAddTip;                                                 // 添加提示
    //string      m_szOr;                                                     // 或
    //string      m_szAnd;                                                    // 与
    //string      m_szSet;                                                    // 设置
    //string      m_szCondition;                                              // 条件

    WComboBox       * m_pReturnList;                                        // 返回值
    WComboBox       * m_pOperateList;                                       // 操作符
    WLineEdit       * m_pParam;                                             // 参数

    WButtonGroup    * m_pConditionGroup;
    WRadioButton    * m_pConditionOR;
    WRadioButton    * m_pConditionAND;

    WText           * m_pHelpText;
    WText           * m_pLabel;
    WTextArea       * m_pConditionArea;

    WTable          * m_pOperate;

    //sv_condition_error_msg m_svErrList;
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
    //void loadString();
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
