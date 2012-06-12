#ifndef _SiteView_Ecc_Advance_Table_H_
#define _SiteView_Ecc_Advance_Table_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"

class WText;
class WImage;
class WLineEdit;
class WTextArea;
class WPushButton;
class WRadioButton;
class WButtonGroup;


#include "../../kennel/svdb/svapi/svapi.h"

class CEccAdvanceTable : public WTable
{
    //MOC: W_OBJECT CEccAdvanceTable:WTable
    W_OBJECT;
public:
    CEccAdvanceTable(WContainerWidget *parent = NULL);

    string          getConditon();
    string          getDepends();
    string          getDescription();
   
    bool            isDependsChanged();

    void            ResetData();

    bool            SaveAdvanceParam(MAPNODE &mainNode);

    void            ShowHideHelp(bool bShow);
    void            setSEID(const string &szSEID);
    void            setCondition(const string &szCondition);
    void            setDepends(const string &szIndex);
    void            setDescription(const string &szDescription);

    void            AppendHelpInList(list<WText*> &lsHelp);
private://slots
    //MOC: SLOT CEccAdvanceTable::showDepend()
    void            showDepend();
    //MOC: SLOT CEccAdvanceTable::changePath()
    void            changePath();
    //MOC: SLOT CEccAdvanceTable::ShowHideSub()
    void            ShowHideSub();
private:
    void                initForm();

    void                createContent();
    // 创建标题栏
    void                createTitle();
    // 创建数据子表
    void                createSubTable(WTable *pSubTable);
    void                createDepends();
    void                createCondition();
    void                createDescription();

    void                createHide();

    WTextArea           *m_pDescription;
    WLineEdit           *m_pDependson;
    WButtonGroup        *m_pConditionGroup;//       *m_pDependsCondition;
    WRadioButton        *m_pNormal;
    WRadioButton        *m_pError;
    WRadioButton        *m_pWarnning;

    WLineEdit           *m_pHideEdit;
    WPushButton         *m_pHideButton;
    WTable              *m_pSubTable;           // 数据表
    WImage              *m_pControl;            // 隐藏/显示字表图片
    WText               *m_pTitle;              // 标题

    // 是否显示数据表
    bool                m_bShowSub;

    list<WText*>        m_lsHelp;

    int                 m_nOldCondition;
    string              m_szOldDependID;
    string              m_szSEID;
};


#endif
