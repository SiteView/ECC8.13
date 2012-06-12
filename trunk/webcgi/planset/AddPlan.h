//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_ADD_PLAN_H_
#define _SV_ADD_PLAN_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib

#include "../../opens/libwt/WContainerWidget"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WTextArea"
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>


#include "defines.h"

using namespace std;

class CTaskList;
class CTaskList1;

//class CSVAddPlan
class CSVAddPlan : public WContainerWidget
{
	//MOC: W_OBJECT CSVAddPlan:WContainerWidget
    W_OBJECT;
public:
    CSVAddPlan(WContainerWidget *parent = 0);
    void clearContent();
    void UpdateData(ADD_PLAN_OK addPlan);


public signals:
    //MOC: EVENT SIGNAL CSVAddPlan::Successful(ADD_PLAN_OK)
    void Successful(ADD_PLAN_OK addPlan);
	//MOC: EVENT SIGNAL CSVAddPlan::SCancel()
	void SCancel();
public:
	 typedef struct _FORM_SHOW_TEXT
    {
        string szErrorMsg; string szPlanTypeRel;
		string szStatusAllow; string szStatusDeny;
		string szRunName; string szDescript;
		string szSaveBut; string szCancelBut;
		string szErrorMsg1; string szRunNameHelp;
		string szBasicAdd; string szAdvanceAdd;
		string strWeekHelp;
		string szAddReTitle;
    public :
        _FORM_SHOW_TEXT()
        {
 /*         szErrorMsg = "���Ʋ���Ϊ�գ�";
			szRunName = "����ƻ�����";
			szRunNameHelp = "����ƻ����Ʋ���Ϊ�գ�����ͬ�����򸲸�ԭ�е�����ƻ�";
			szDescript = "����";
			szSaveBut = "����";
			szCancelBut = "ȡ��";
			szErrorMsg1 = "����ͬ������ƻ�";
			szBasicAdd = "����ѡ��";
			szAdvanceAdd = "�߼�ѡ��";
			strWeekHelp = "���ʱ���֮���á�,���ָ�(���磺01:00--03:00;05:00-10:00����ʱ��Σ�����:�ӡ�01:00,05:00������03:00,10:00��.)";
*/
			szPlanTypeRel = "2";
			szStatusAllow = "1";
			szStatusDeny = "0";
		}
    }FORM_SHOW_TEXT;

	FORM_SHOW_TEXT m_FormShowText;
	WText * m_pConnErr;
	WImage * m_pHelpImg;
	string chgstr;
	WText * m_pPlanNameHelp;
	WText * m_pPlanNameError;
	WText * m_pSuHelp;


	
	WSVMainTable * pMainTable;
	WSVFlexTable * AddRangeTable;
/*	WText * m_pMoHelp;
	WText * m_pTuHelp;
	WText * m_pWeHelp;
	WText * m_pThHelp;
	WText * m_pFrHelp;
	WText * m_pSaHelp;
*/	bool IsShow;


public:
    WComboBox * m_pCombo[7];
    WLineEdit * m_pStart[7];
    WLineEdit * m_pEnd[7];

private slots:
    //MOC: SLOT CSVAddPlan::Save()
    void Save();
	//MOC: SLOT CSVAddPlan::Cancel()
	void Cancel();
	//MOC: SLOT CSVAddPlan::hidePlanList()
    void hidePlanList();
	//MOC: SLOT CSVAddPlan::showPlanList()
	void showPlanList();
	//MOC: SLOT CSVAddPlan::AhidePlanList()
	void AhidePlanList();
	//MOC: SLOT CSVAddPlan::AshowPlanList()
	void AshowPlanList();
	//MOC: SLOT CSVAddPlan::AddPlanHelp()
	void AddPlanHelp();
private:
    void showMainForm();
    void showErrorMsg(string &szErrMsg);
    bool checkPlan();
	void AddJsParam(const std::string name, const std::string value);
    
private:

    WLineEdit * m_pName;
    WCheckBox * m_pDisable;
    CTaskList * m_pTasklist;
    int m_nIndex ;
    WText * m_pErrMsg;
	WImage * pShow;
	WImage * pHide;
	WImage * pShow1;
	WImage * pHide1;
	WTable * table;
	WTable * table1;
	WTextArea * textarea;

	string strTypeAdd;
	string strTypeEdit;
	string strTimeTaskPlan;
	string strAllown;
	string strHelp;
	string szTitle;

	string szCancelAdd;
	string szSaveAddInPlan;
};

class CSVAddAbsolutePlan : public WContainerWidget
{
	//MOC: W_OBJECT CSVAddAbsolutePlan:WContainerWidget
    W_OBJECT;
public:
    CSVAddAbsolutePlan(WContainerWidget *parent = 0);
    void clearContent();
    void UpdateData(ADD_PLAN_OK addPlan);


public:
	 typedef struct _FORM_SHOW_TEXT
    {
        string szErrorMsg; string szPlanTypeAb;
		string szStatusAllow; string szStatusDeny;
		string szRunName; string szDescript;
		string szSaveBut; string szCancelBut;
		string szErrorMsg1;string szRunNameHelp;
		string szBasicAdd; string szAdvanceAdd;
		string strWeekHelp;
		string szAddAdTitle;
    public :   
        _FORM_SHOW_TEXT()
        {
 /*          szErrorMsg = "���Ʋ���Ϊ�գ�";
			szRunName = "����ƻ�����";
			szRunNameHelp = "����ƻ����Ʋ���Ϊ�գ�����ͬ�����򸲸�ԭ�е�����ƻ�";
			szDescript = "����";
			szSaveBut = "����";
			szCancelBut = "ȡ��";
			szErrorMsg1 = "����ͬ������ƻ�";
			szBasicAdd = "����ѡ��";
			szAdvanceAdd = "�߼�ѡ��";
			strWeekHelp = "���ʱ��֮���á�,���ָ�(���磺01:00��03:00��05:00����ʱ�䣬���롰01:00,03:00,05:00��)";
 */
			szPlanTypeAb = "1";
			szStatusAllow = "1";
			szStatusDeny = "0";
		}
    }FORM_SHOW_TEXT;

	FORM_SHOW_TEXT m_FormShowText;
	WText * m_pConnErr;
	WImage * m_pHelpImg;
	WText * m_pPlanNameHelp;
	WText * m_pPlanNameError;
	bool IsShow;
	string chgstr;
public signals:
    //MOC: EVENT SIGNAL CSVAddAbsolutePlan::Successful(ADD_PLAN_OK)
    void Successful(ADD_PLAN_OK addPlan);
	//MOC: EVENT SIGNAL CSVAddAbsolutePlan::SCancel1()
	void SCancel1();
private slots:
    //MOC: SLOT CSVAddAbsolutePlan::Save1()
    void Save1();
	//MOC: SLOT CSVAddAbsolutePlan::Cancel1()
	void Cancel1();
	//MOC: SLOT CSVAddAbsolutePlan::hidePlanList1()
    void hidePlanList1();
	//MOC: SLOT CSVAddAbsolutePlan::showPlanList1()
	void showPlanList1();
	//MOC: SLOT CSVAddAbsolutePlan::AhidePlanList1()
	void AhidePlanList1();
	//MOC: SLOT CSVAddAbsolutePlan::AshowPlanList1()
	void AshowPlanList1();
	//MOC: SLOT CSVAddAbsolutePlan::AddPlanHelp()
	void AddPlanHelp();
private:
    void showMainForm();
    void showErrorMsg(string &szErrMsg);
    bool checkPlan();
    void AddJsParam(const std::string name, const std::string value);

private:

    WLineEdit * m_pName;
    WCheckBox * m_pDisable;
    CTaskList1 * m_pTasklist;
    int m_nIndex ;
    WText * m_pErrMsg;
	WText * tWeekHelp;
	WImage * pShow;
	WImage * pHide;
	WImage * pShow1;
	WImage * pHide1;
	WTable * table;
	WTable * table1;
	WTextArea * textarea;

	string strTypeAdd;
	string strTypeEdit;
	string strTimeTaskPlan;
	string strAllown;
	string strHelp;
	string szTitle;

	WSVMainTable * pMainTable;
	WSVFlexTable * AddAdvanTable;
	WSVFlexTable * AddRangeTable;

	string szSaveAddAbPlan;
	string szCancelAdd;
};

#endif

// end class
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// end file