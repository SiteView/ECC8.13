//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_WEB_CGI_TASK_LIST_H_
#define _SV_WEB_CGI_TASK_LIST_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// include WT libs
#include "../../opens/libwt//WTable"
#include "../../opens/libwt//WLineEdit"
#include "../../opens/libwt//WComboBox"
#include "../../opens/libwt//WText"
#include "../../opens/libwt//WImage"
#include "../../opens/libwt/WContainerWidget"
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std

#include "WSVMainTable.h"
#include "WSVFlexTable.h"

class CTaskList : public WTable
{
    //MOC: W_OBJECT CTaskList:WTable
    W_OBJECT;
public:
    //CTaskList(WContainerWidget *parent = 0, WTable * table = 0);
	CTaskList(WContainerWidget *parent, WSVFlexTable * table, const string helpSun);
    const char * GetTaskTime();
    void Reset();
public signals:
private slots:
public:
    WComboBox * m_pCombo[7];
    WLineEdit * m_pStart[7];
    WLineEdit * m_pEnd[7];
private:    
    void AddItem(WTable *parent);
};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file





