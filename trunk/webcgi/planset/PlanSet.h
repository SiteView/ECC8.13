//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_EMAIL_SET_H_
#define _SV_EMAIL_SET_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib

#include "../../opens/libwt//WContainerWidget"
#include "../../opens/libwt//WPushButton"
#include "../../opens/libwt//WLineEdit"
#include "../../opens/libwt//WCheckBox"
#include "../../opens/libwt//WText"
#include "../../opens/libwt//WImage"
#include "../../opens/libwt//WTable"
#include "../../opens/libwt//WTableCell"
#include "../../opens/libwt//WSignalMapper"
#include "FlexTable.h"
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>
#include <list>

class WSVMainTable;
class WSVButton;
class WSVFlexTable;

using namespace std;

#include "defines.h"

//////////////////////////////////////////////////////////////////////////////////
// class CSVEmailSet
class CSVPlanSet : public WContainerWidget
{
    //MOC: W_OBJECT CSVPlanSet:WContainerWidget
    W_OBJECT;
public:
    CSVPlanSet(WContainerWidget *parent = 0);

	void PlanSetForm();
	void PlanSetForm(WSVMainTable *parent);
    void AddPlanList(ADD_PLAN_OK mail);
	void AddPlanList1(ADD_PLAN_OK mail);
	void adjustRowStyle();
    virtual void refresh();
	void updateAbsSchedule();
	void updateRangeSchedule();

	void InitFlexTable(std::string strTitle1, std::string strTitle2);

	void AddJsParam(const std::string name, const std::string value);
	
public:
	bool    hBegin;
	WImage * pShow;
	WImage * pHide;

	WImage * pShow1;
	WImage * pHide1;
	CFlexTable * ft;//相对时间段flex tabel
	CFlexTable * ft1;// abs time

	WPushButton * pHideBut;
	WPushButton * pHideBut1;

	WSVMainTable * pMainTable;
	WSVMainTable * pUserTable;
	WSVFlexTable * pUserTable1;
	WSVFlexTable * pUserTable2;

	WSVButton * pTranslateBtn;
	WSVButton * pExChangeBtn;
	
	string strListHeights;	
	string strListPans;
	string strListTitles;
	string szTitle;
	string strNullList;

	string chgstr;
	
	string strSepPlanNull;
	string strAbsPlanNull;


public signals:
    //MOC: EVENT SIGNAL CSVPlanSet::SaveSuccessful(SEND_MAIL_PARAM)
    void SaveSuccessful(SEND_MAIL_PARAM sendParam);
    //MOC: EVENT SIGNAL CSVPlanSet::AddNewPlan()
    void AddNewPlan();
    //MOC: EVENT SIGNAL CSVPlanSet::EditPlanList(ADD_PLAN_OK)
    void EditPlanList(ADD_PLAN_OK addPlan);
	//MOC: EVENT SIGNAL CSVPlanSet::SaveSuccessful1(SEND_MAIL_PARAM)
    void SaveSuccessful1(SEND_MAIL_PARAM sendParam);
    //MOC: EVENT SIGNAL CSVPlanSet::AddNewPlan1()
    void AddNewPlan1();
    //MOC: EVENT SIGNAL CSVPlanSet::EditPlanList1(ADD_PLAN_OK)
    void EditPlanList1(ADD_PLAN_OK addPlan);
private slots:
	//MOC: SLOT CSVPlanSet::hidePlanList()
    void hidePlanList();
	//MOC: SLOT CSVPlanSet::showPlanList()
    void showPlanList();
	//MOC: SLOT CSVPlanSet::Save()
    void Save();
    //MOC: SLOT CSVPlanSet::AddPlan()
    void AddPlan();
    //MOC: SLOT CSVPlanSet::BeforeDelPlan()
    void BeforeDelPlan();
	//MOC: SLOT CSVPlanSet::DelPlan()
    void DelPlan(); 
    //MOC: SLOT CSVPlanSet::SelAll()
    void SelAll();
    //MOC: SLOT CSVPlanSet::EditPlan(const std::string)
    void EditPlan(const std::string str);
	//MOC: SLOT CSVPlanSet::hidePlanList1()
    void hidePlanList1();
	//MOC: SLOT CSVPlanSet::showPlanList1()
    void showPlanList1();
	//MOC: SLOT CSVPlanSet::Save1()
    void Save1();
    //MOC: SLOT CSVPlanSet::AddPlan1()
    void AddPlan1();
    //MOC: SLOT CSVPlanSet::BeforeDelPlan1()
    void BeforeDelPlan1(); 
    //MOC: SLOT CSVPlanSet::DelPlan1()
    void DelPlan1(); 
    //MOC: SLOT CSVPlanSet::SelAll1()
    void SelAll1();
    //MOC: SLOT CSVPlanSet::EditPlan1(const std::string)
	void EditPlan1(const std::string str);
	//MOC: SLOT CSVPlanSet::SelNone()
	void SelNone();
	//MOC: SLOT CSVPlanSet::SelNone1()
	void SelNone1();
	//MOC: SLOT CSVPlanSet::SelInvert()
	void SelInvert();
	//MOC: SLOT CSVPlanSet::SelInvert1()
	void SelInvert1();
	//MOC: SLOT CSVPlanSet::AdjustAbsDelState()
	void AdjustAbsDelState();
	//MOC: SLOT CSVPlanSet::AdjustRangeDelState()
	void AdjustRangeDelState();

private:
    WLineEdit * pServerIp;          // 发件服务器
    WLineEdit * pMailFrom;          // 邮件来源
    WLineEdit * pUser;              // 用户
    WLineEdit * pPwd;               // 密码
    WLineEdit * pBackupServer;      // 备份发件服务器

    WCheckBox * m_pSelectAll;       // 全选
	WCheckBox * m_pSelectAll1;

 //   WText * m_pErrMsg;              // 错误消息
 //   WTable * ReceiveAddrSetTable;   // 邮件地址表
	//WTable * ReceiveAddrSetTable1;
	//WTable * ContainerReceiveAddrSetTable;
	//WTable * ContainerReceiveAddrSetTable1;
	//WTable * nullTable;
	//WTable * nullTable1;
 //   WSignalMapper m_signalMapper;   // 
	//WSignalMapper m_signalMapper1;

    WText * m_pErrMsg;              // 错误消息
    WSVFlexTable * ReceiveAddrSetTable;   // 邮件地址表
	WSVFlexTable * ReceiveAddrSetTable1;
//	WTable * ContainerReceiveAddrSetTable;
//	WTable * ContainerReceiveAddrSetTable1;
	WTable * nullTable;
	WTable * nullTable1;
    WSignalMapper m_signalMapper;   // 
	WSignalMapper m_signalMapper1;
// 邮件地址表格行
typedef struct _PLAN_LIST 
{
    int nIndex ;            // 索引
    WCheckBox * pSelect;    // 选择框
    WText * pName;          // 名称
//    WText * pType;         // mail地址
    WImage * pImage;
}PLAN_LIST, *LPPLAN_LIST;

 typedef struct _FORM_SHOW_TEXT
    {
        string szColStatus; string szColName;
		string szColType; string szColMod;
		string szPlanTypeRel; string szColPlanTypeRel;
		string szPlanTypeAb; string szValDel;
		string szAddRelPlanBut; string szAddAbPlanBut;
		string szTitle1; string szTaskType;
		string szTitle2; string szTipSelAll;
		string szTipNotSelAll; string szTipInvSel;
		string szTipAddNew;string szTipDel;
		string szButNum,szButMatch;
    public :
        _FORM_SHOW_TEXT()
        {/*
            szColStatus = "状态";
			szColName = "名称";
			szColType = "类型";
			szColMod = "编辑";
			szColPlanTypeRel = "时间段";
			szValDel = "你确认删除任务计划吗？";
			szAddRelPlanBut = "添加时间段任务计划";
			szAddAbPlanBut = "添加绝对时间任务计划";
			szTitle1 = "时间段任务计划";
			szTaskType = "Type";
			szTitle2 = "绝对时间任务计划";
			szTipSelAll = "全选";
			szTipNotSelAll = "全不选";
			szTipInvSel = "反选";
			szTipAddNew = "添加";  //"add new";
			szTipDel = "删除";
			*/
			szPlanTypeRel = "2";
			szPlanTypeAb = "1";

        }
    }FORM_SHOW_TEXT;

	FORM_SHOW_TEXT m_FormShowText;
// 邮件地址列表
    list<PLAN_LIST> m_pListPlan;
// 邮件地址列表中的表项
    list<PLAN_LIST>::iterator m_pListItem;

	list<PLAN_LIST> m_pListPlan1;
	list<PLAN_LIST>::iterator m_pListItem1;
private:
    // 显示错误信息
    void showErrorMsg(string &szErrMsg);
    // 校验邮件地址
    bool checkEmail();
    // 修改行
    void EditRow(ADD_PLAN_OK &maillist);
	void EditRow1(ADD_PLAN_OK &maillist);

	void AddGroupOperate(WTable * pTable);
	void AddGroupOperate1(WTable * pTable);

	WTable * m_pGroupOperate;
	WTable * m_pGroupOperate1;

private: //Var
	string strEditIntervalPlan;
	string strEditAbPlan;
	string strRefresh;
	string strDelCon;
	string strDelInPlan;
	string strDelAbPlan;
	
};

// end class
//////////////////////////////////////////////////////////////////////////////////
#endif
//////////////////////////////////////////////////////////////////////////////////
// end file

