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

    void SetReturnList(list<SVReturnItem*> &lsReturn);                      // ���÷���ֵ�б�
    void SetMapNode(MAPNODE &mapnode);                                      // ���� MAPNODE
    bool checkCondition(MAPNODE &alertnode);
    bool SaveCondition(MAPNODE &alertnode);                                 // ��������
    void SetCondition(MAPNODE &alertnode);                                  // ��������
    void showHelp(bool bShowHelp);                                          // ��ʾ/���ذ���
    void clearReturnList() { m_lsReturn.clear(); };
    void setDefaultValue();
private slots:
    //MOC: SLOT SVConditionParam::showAddCondition()
    void showAddCondition();                                                // ��ʾ���������
    //MOC: SLOT SVConditionParam::hideAddCondition()
    void hideAddCondition();                                                // �������������
    //MOC: SLOT SVConditionParam::addCondition()
    void addCondition();                                                    // �������
private:
    string      m_szName;                                                   // ����
    string      m_szLabel;                                                  // ��ʾ��ǩ
    string      m_szDefaultValue;                                           // ȱʡֵ
    string      m_szHelp;                                                   // ����
    string      m_szTip;                                                    // ��ʾ
    string      m_szStyle;                                                  // ��ʽ

    int         m_nConditionType;                                           // ��������

    list<SVReturnItem*> m_lsReturn;                                         // ����ֵ
    list<string>        m_lsCondition;                                      // ����

    WComboBox       * m_pReturnList;                                        // ����ֵ
    WComboBox       * m_pOperateList;                                       // ������
    WLineEdit       * m_pParam;                                             // ����

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
