//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_ADD_ABPLAN_H_
#define _SV_ADD_ABPLAN_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib

#include "../../opens/libwt//WContainerWidget"
#include "../../opens/libwt//WPushButton"
#include "../../opens/libwt//WLineEdit"
#include "../../opens/libwt//WCheckBox"
#include "../../opens/libwt//WComboBox"
#include "../../opens/libwt//WText"
#include "../../opens/libwt//WImage"
#include "../../opens/libwt//WTable"

#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>


#include "defines.h"

using namespace std;

class CTaskList;
class WSVMainTable;
class WSVFlexTable;

//class CSVAddPlan
class CSVAddAbsolutePlan : public WContainerWidget
{
	//MOC: W_OBJECT CSVAddAbsolutePlan:WContainerWidget
    W_OBJECT;
public:
    CSVAddAbsolutePlan(WContainerWidget *parent = 0);
    void clearContent();
    void UpdateData(ADD_PLAN_OK addPlan);

public signals:
    //MOC: EVENT SIGNAL CSVAddAbsolutePlan::Successful(ADD_PLAN_OK)
    void Successful(ADD_PLAN_OK addPlan);
private slots:
    //MOC: SLOT CSVAddAbsolutePlan::Save()
    void Save();
	//MOC: SLOT CSVAddAbsolutePlan::hidePlanList()
    void hidePlanList();
	//MOC: SLOT CSVAddAbsolutePlan::showPlanList()
	void showPlanList();
private:
    void showMainForm();
    void showErrorMsg(string &szErrMsg);
    bool checkPlan();

private:

    WLineEdit * m_pName;
    WCheckBox * m_pDisable;
    CTaskList * m_pTasklist;
    int m_nIndex ;
    WText * m_pErrMsg;
	WImage * pShow;
	WImage * pHide;
	WTable * table;

	WSVMainTable * ppMainTable;
	WSVFlexTable * pAddrSetTable;

};

#endif

// end class
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// end file