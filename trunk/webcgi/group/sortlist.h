
// 
#ifndef _SV_SORT_LIST_H_
#define _SV_SORT_LIST_H_

// build once
#pragma once

// include libwt files
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WScrollArea"

// include svdb api
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

// include svtable
#include "../svtable/SVTable.h"
#include "../userright/user.h"
#include "../base/basetype.h"

// include stl library
#include <string>
#include <list>
#include <map>

using namespace std;

// include base function head file
#include "basefunc.h"

class CSVSortList : public WTable
{
public:
    //MOC: W_OBJECT CSVSortList:WTable
    W_OBJECT;
public:
    CSVSortList(WContainerWidget* parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    void EnumObject(string &szIndex, int &nType);
public signals:
    //MOC: SIGNAL CSVSortList::RefreshList()
    void RefreshList();
    //MOC: SIGNAL CSVSortList::backMainView()
    void backMainView();
private slots:
    //MOC: SLOT CSVSortList::UpFloor(const std::string)
    void UpFloor(const std::string szIndex);
    //MOC: SLOT CSVSortList::DownFloor(const std::string)
    void DownFloor(const std::string szIndex);
    //MOC: SLOT CSVSortList::saveList()
    void saveList();
    //MOC: SLOT CSVSortList::cancelEdit()
    void cancelEdit();
private: // function list
    void initForm();
    //void loadString();
    void createOperate();
    void createTitle();
    void createContent();
    void enumSVSE();
    void enumGroup(string &szGroupIndex);
    void enumDevice(string &szGroupIndex);
    void enumMonitor(string &szDeviceIndex);

    void saveGroup(map<int, string, less<int> > &lsDis);
    void saveDevice(map<int, string, less<int> > &lsDis);
    void saveMonitor(map<int, string, less<int> > &lsDis);

    bool checkDisplayIndex();

    void addList();
private:
    WText          *m_pTitle;
    WTable         *m_pContent;

    //string          m_szTitle;
    //string          m_szSave;
    //string          m_szCancel;
    //string          m_szSaveTip;
    //string          m_szCancelTip;

    //string          m_szUpTip;
    //string          m_szDownTip;

    //string          m_szColName;
    //string          m_szColSort;

	list<base_param>    m_lsOld;
    list<base_param>    m_lsCurrent;

    string          m_szIDCUser;
    string          m_szIDCPwd;

    CUser          *m_pSVUser;

    map<int, base_param, less<int> > m_sortList;
    map<int, base_param, less<int> >::iterator lsItem;

    SVIntTable         m_svList;
    
    int             m_nType;
    //string          m_szCurrentID;
};

#endif
