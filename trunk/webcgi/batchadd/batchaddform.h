#ifndef _SV_BATCH_ADD_H_
#define _SV_BATCH_ADD_H_

#pragma once

#include "../../opens/libwt/WContainerWidget"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"

#include <string>
#include <list>

using namespace std;

class CSVBatchAdd : public WContainerWidget
{
    //MOC: W_OBJECT CSVBatchAdd:WContainerWidget
    W_OBJECT;
public:
    CSVBatchAdd(WContainerWidget* parent = NULL);
    virtual void refresh();
public signals:
private slots:
    //MOC: SLOT CSVBatchAdd::savemonitor()
    void savemonitor();
private:
    void loadString();
    void initForm();

    void CreateOperater();
    void CreateList();
    void enumBaseParam();
    void enumAdvParam();

    bool saveBaseParam();
    bool saveAdvParam();

    string  m_szSave;
    string  m_szSaveTip;
    string  m_szCancel;
    string  m_szCancelTip;
    string  m_szSelAll;

    map<string, string, less<string> > m_mapValue;

    map<string, string, less<string> > m_mapAdvParam;
    map<string, string, less<string> > m_mapBaseParam;

    int          m_nMonitorType;

    WTable       * m_pList;
    WCheckBox   * m_pSelAll;
    WText        * m_pMonitorName;
};

#endif