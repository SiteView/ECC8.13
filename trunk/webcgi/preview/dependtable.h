/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_DEPEND_ON_TABLE_H_
#define _SV_DEPEND_ON_TABLE_H_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


//#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WText"

#include <string>
using namespace std;

#include "../group/showtable.h"
#include "../group/resstring.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVDependTable : public WTable
{
    //MOC: W_OBJECT SVDependTable:WTable
    W_OBJECT;
public :
    SVDependTable(WContainerWidget * parent = NULL);

    bool isDependChange()
    { 
        if ( (m_szOldDependID == m_pHideEdit->text()) && (m_nOldCondition == m_pDependCondition->currentIndex() + 1) )
            return false;
        else
            return true;
    };

    void showHelp(bool bShow);

    void getDescription(string &szValue);
    void getDepend(string &szValue);
    void getCodition(string &szValue);
    void resetDepend()
    {
        if(m_pHideEdit) 
            m_pHideEdit->setText("");
        if(m_pPath) 
            m_pPath->setText(SVResString::getResString("IDS_Friendless"));
    };
    void setCodition(string &szCondition);
    void setDepend(string &szDepend);
    void setDescription(string &szDesc);
    void setUserID(string szUserID){ m_szUserID = szUserID;};
private slots:
    //MOC: SLOT SVDependTable::showDependTree()
    void showDependTree();
    //MOC: SLOT SVDependTable::showSubTable()
    void showSubTable();
    //MOC: SLOT SVDependTable::hideSubTable()
    void hideSubTable();
    //MOC: SLOT SVDependTable::changePath()
    void changePath();
    //MOC: SLOT SVDependTable::cleardate()
    void cleardate();

private :
    WTable * m_pDependList;
    WComboBox * m_pDependCondition;
    WText *  m_pPath;
    WText *  m_pDependHelp;
    WText *  m_pConditionHelp;
    WTextArea * m_pDescription;
    WText *  m_pDescriptionHelp;

    //string m_szFriendless;
    //string m_szCondition;
    //string m_szConditionHelp;
    //string m_szDepend;
    //string m_szDependHelp;
    //string m_szTitle;
    //string m_szConditionWarn;
    //string m_szConditionErr;
    //string m_szConditionNormal;
    //string m_szDescription;
    //string m_szDescriptionHelp;

    string m_szOldDependID;
    int    m_nOldCondition;

    string m_szUserID;

    WLineEdit * m_pHideEdit;
    WPushButton * m_pHideButton;
    WTable    * m_pSub;
    WImage * m_pShow;
    WImage * m_pHide;
    bool     m_bHide;
private:
    // 
    void initForm();
    void createTitle();
    void createDesc();
    void createCondition();
    void createDependList();
    //void loadString();

    void createHideEdit();

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//end file
