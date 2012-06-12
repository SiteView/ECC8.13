#ifndef _SV_SHOW_HIDE_TABLE_H_
#define _SV_SHOW_HIDE_TABLE_H_

#pragma once

#include "../../opens/libwt/WTable"
class WImage;
class WText;

class SVShowTable : public WTable
{
    //MOC: W_OBJECT SVShowTable:WTable
    W_OBJECT;
public:
    SVShowTable(WContainerWidget * parent = 0);
    void setTitle(const char * szTitle);

    bool isHidden() { return m_bHide; };

    WTable * createSubTable();
private slots:
    //MOC: SLOT SVShowTable::showSubTable()
    void showSubTable();
    //MOC: SLOT SVShowTable::hideSubTable()
    void hideSubTable();
private:
    WImage * m_pShow;
    WImage * m_pHide;
    WText  * m_pTitle;
    WTable * m_pSub;
    bool     m_bHide;
private:
    void InitForm();
};

#endif