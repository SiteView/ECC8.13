//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_EMAIL_SET_MAIN_FORM_H_
#define _SV_EMAIL_SET_MAIN_FORM_H_

#if _MSC_VER > 1000
#pragma once
#endif
//////////////////////////////////////////////////////////////////////////////////
// include WT Libs
#include "../../opens/libwt/WTable"
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////

class CSVAddPlan;
class CSVAddAbsolutePlan;
class CSVPlanSet;
//////////////////////////////////////////////////////////////////////////////////
class WStackedWidget;
class WApplication;
class WPushButton;
class WSVMainTable;

#include "defines.h"

class CMainForm : public WTable
//class CMainForm : public WContainerWidget
{
    //MOC: W_OBJECT CMainForm:WTable
    W_OBJECT;
public:
    CMainForm(WContainerWidget *parent = 0);
public:
	std::string szTitle ;
	WApplication *  appSelf;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

	WSVMainTable * pMainTable;
public signals:
private slots:

    //MOC: SLOT CMainForm::Forword()
    void Forword();
    //MOC: SLOT CMainForm::showAddform()
    void showAddform();

	//MOC: SLOT CMainForm::SaveNewPlanList(ADD_PLAN_OK)
	void SaveNewPlanList(ADD_PLAN_OK addPlan);

	//MOC: SLOT CMainForm::EditNewPlanList(ADD_PLAN_OK)
	void EditNewPlanList(ADD_PLAN_OK addPlan);
	//MOC: SLOT CMainForm::CancelAdd()
	void CancelAdd();
	//MOC: SLOT CMainForm::showAddform1()
    void showAddform1();

	//MOC: SLOT CMainForm::SaveNewPlanList1(ADD_PLAN_OK)
	void SaveNewPlanList1(ADD_PLAN_OK addPlan);

	//MOC: SLOT CMainForm::EditNewPlanList1(ADD_PLAN_OK)
	void EditNewPlanList1(ADD_PLAN_OK addPlan);
	//MOC: SLOT CMainForm::CancelAdd1()
	void CancelAdd1();
	//MOC: SLOT CMainForm::Translate()
	void Translate();
	//MOC: SLOT CMainForm::ExChange()
	void ExChange();
private:
	void showAddPlan();
	void showAddPlan1();
	void showPlanSet();

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

protected:
    WStackedWidget * m_pMainStack;

	CSVAddPlan     * m_pAddPlan;
	CSVAddAbsolutePlan * m_pAddAbsolutePlan;
	CSVPlanSet     * m_pPlanSet;

};

#endif


/////////////////////////////////////////////////////////////////////////////////
// end file

