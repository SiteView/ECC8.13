#include "resstring.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVResString SVResString::m_DefineOnce;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVResString::SVResString(string szResLanguage, string szAddr):
m_szResLanguage(szResLanguage),
m_szResAddr(szAddr)
{
    m_objRes = INVALID_VALUE;
    loadStrings();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVResString::~SVResString()
{
    if(m_objRes != INVALID_VALUE)
        CloseResource(m_objRes);
    m_lsResource.clear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::ResetResoureType(string &szResLanguage, string &szAddr)
{
    m_szResLanguage = szResLanguage;
    m_szResAddr     = szAddr;
    if(m_objRes != INVALID_VALUE)
        CloseResource(m_objRes);

    m_objRes = LoadResource(m_szResLanguage, m_szResAddr);
    if(m_objRes != INVALID_VALUE)
    {
        MAPNODE resNode = GetResourceNode(m_objRes);
        if(resNode != INVALID_VALUE)
        {
            for(resItem it = m_lsResource.begin(); it != m_lsResource.end(); it++)
                FindNodeValue(resNode, it->first, it->second);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string SVResString::getResString(const string &szResID)
{
    resItem it = m_DefineOnce.m_lsResource.find(szResID);
    if(it != m_DefineOnce.m_lsResource.end())
        return it->second;
    else
        return m_DefineOnce.getStringFromRes(szResID.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string SVResString::getResString(const char* pszResID)
{
    string szID = pszResID;
    resItem it = m_DefineOnce.m_lsResource.find(szID);
    if(it != m_DefineOnce.m_lsResource.end())
        return it->second;
    else
        return m_DefineOnce.getStringFromRes(pszResID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadStrings()
{
    m_objRes = LoadResource(m_szResLanguage, m_szResAddr);
    if(m_objRes != INVALID_VALUE)
    {
        MAPNODE resNode = GetResourceNode(m_objRes);
        if(resNode != INVALID_VALUE)
        {
            loadTreeviewStrings(resNode);              // 加载树显示资源字符串
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadAddDeviceStrings(MAPNODE &objNode)
{
    string szTitle(""), szCancelAddTip(""),
        szAddTip(""), szCancelEditTip(""), szBack(""), szBackTip(""), 
        szHostHelp(""), szHostTip(""), szQuickAddTitle(""), szQuickAddCancelTip(""), 
        szConfigErr(""), szQuickAdd("");

    FindNodeValue(objNode, "IDS_Add_Device_Title",          szTitle);
    FindNodeValue(objNode, "IDS_Cancel_Add_Device_Tip",     szCancelAddTip);
    FindNodeValue(objNode, "IDS_Add_Device_Tip",            szAddTip);
    FindNodeValue(objNode, "IDS_Cancel_Edit_Device_Tip",    szCancelEditTip);
    FindNodeValue(objNode, "IDS_Back_One_Step",             szBack);
    FindNodeValue(objNode, "IDS_Back_Device_List_Tip",      szBackTip);
    FindNodeValue(objNode, "IDS_Host_Label_Help",           szHostHelp);
    FindNodeValue(objNode, "IDS_Host_Label_Error",          szHostTip);
    FindNodeValue(objNode, "IDS_Quick_Add_Monitor_Title",   szQuickAddTitle);
    FindNodeValue(objNode, "IDS_Cancel_Add_Monitor_Tip",    szQuickAddCancelTip);
    FindNodeValue(objNode, "IDS_Monitor_Templet_Error",     szConfigErr);
    FindNodeValue(objNode, "IDS_Quick_Add",                 szQuickAdd);

    m_lsResource["IDS_Add_Device_Title"] = szTitle;
    m_lsResource["IDS_Cancel_Add_Device_Tip"] = szCancelAddTip;
    m_lsResource["IDS_Add_Device_Tip"] = szAddTip;
    m_lsResource["IDS_Cancel_Edit_Device_Tip"] = szCancelEditTip;
    m_lsResource["IDS_Back_One_Step"] = szBack;
    m_lsResource["IDS_Back_Device_List_Tip"] = szBackTip;
    m_lsResource["IDS_Host_Label_Help"] = szHostHelp;
    m_lsResource["IDS_Host_Label_Error"] = szHostTip;
    m_lsResource["IDS_Quick_Add_Monitor_Title"] = szQuickAddTitle;
    m_lsResource["IDS_Cancel_Add_Monitor_Tip"] = szQuickAddCancelTip;
    m_lsResource["IDS_Monitor_Templet_Error"] = szConfigErr;
    m_lsResource["IDS_Quick_Add"] = szQuickAdd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadAddGroupStrings(MAPNODE &objNode)
{
    string szName(""), szNameHelp(""), szTitle(""), szAddTip(""),
        szSaveTip(""), szCancelEditTip(""), szNameErr(""), szEditTitle("");

    FindNodeValue(objNode, "IDS_Group_Name",            szName);
    FindNodeValue(objNode, "IDS_Group_Name_Help",       szNameHelp);
    FindNodeValue(objNode, "IDS_Add_Group_Title",       szTitle);
	FindNodeValue(objNode, "IDS_Add_Group_Tip",         szAddTip);
	FindNodeValue(objNode, "IDS_Save_Group_Tip",        szSaveTip);
	FindNodeValue(objNode, "IDS_Cancel_Group_Edit_Tip", szCancelEditTip);
	FindNodeValue(objNode, "IDS_Group_Name_Error",      szNameErr);
	FindNodeValue(objNode, "IDS_Edit_Group_Title",      szEditTitle);

    m_lsResource["IDS_Group_Name"] = szName;
    m_lsResource["IDS_Group_Name_Help"] = szNameHelp;
    m_lsResource["IDS_Add_Group_Title"] = szTitle;
    m_lsResource["IDS_Add_Group_Tip"] = szAddTip;
    m_lsResource["IDS_Save_Group_Tip"] = szSaveTip;
    m_lsResource["IDS_Cancel_Group_Edit_Tip"] = szCancelEditTip;
    m_lsResource["IDS_Group_Name_Error"] = szNameErr;
    m_lsResource["IDS_Edit_Group_Title"] = szEditTitle;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadAddMonitorStrings(MAPNODE &objNode)
{
    string szCancelTip(""), szTitle(""), szConditionTitle(""), szAddTip(""),
        szCancelEditTip(""), szBackTip(""), szBatchAddTip(""), szContinueAdd(""),
        szContinueAddTip(""), szSetAlert(""), szSetAlertTip(""), szDevice(""), szDeviceHelp(""), 
        szMonitor(""), szMonitorHelp(""), szCheckErr(""), szCheckHelp(""), 
        szDesc(""), szDescHelp(""), szFreq(""), szFreqHelp(""), szFreqErr(""), 
        szPlan(""), szPlanHelp(""), szReport(""), szReportHelp(""), szErrName("");

    FindNodeValue(objNode, "IDS_Cancle_Add_Monitor_Tip",    szCancelTip);
    FindNodeValue(objNode, "IDS_Add_Monitor_Title",         szTitle);
    FindNodeValue(objNode, "IDS_Alert_Condition_Title",     szConditionTitle);
    FindNodeValue(objNode, "IDS_Add_Monitor_Tip",           szAddTip);
    FindNodeValue(objNode, "IDS_Cancel_Current_Edit_Tip",   szCancelEditTip);
    FindNodeValue(objNode, "IDS_Back_Monitor_List_Tip",     szBackTip);
    FindNodeValue(objNode, "IDS_Batch_Add_Tip",             szBatchAddTip);
    FindNodeValue(objNode, "IDS_Continue_Add",              szContinueAdd);
    FindNodeValue(objNode, "IDS_Continue_Add_Tip",          szContinueAddTip);
    FindNodeValue(objNode, "IDS_Set_Default_Alert",         szSetAlert);
    FindNodeValue(objNode, "IDS_Set_Default_Alert_Tip",     szSetAlertTip);
    FindNodeValue(objNode, "IDS_Device_Name",               szDevice);
    FindNodeValue(objNode, "IDS_Device_Name_Help",          szDeviceHelp);
    FindNodeValue(objNode, "IDS_Monitor_Label",             szMonitor);
    FindNodeValue(objNode, "IDS_Monitor_Label_Help",        szMonitorHelp);
    FindNodeValue(objNode, "IDS_Check_Error",               szCheckErr);
    FindNodeValue(objNode, "IDS_Check_Err_Help",            szCheckHelp);
    FindNodeValue(objNode, "IDS_Monitor_Desc",              szDesc);
    FindNodeValue(objNode, "IDS_Monitor_Desc_Help",         szDescHelp);
    FindNodeValue(objNode, "IDS_Error_Freq",                szFreq);
    FindNodeValue(objNode, "IDS_Error_Freq_Help",           szFreqHelp);
    FindNodeValue(objNode, "IDS_Numbic_Error",              szFreqErr);
    FindNodeValue(objNode, "IDS_Plan",                      szPlan);
    FindNodeValue(objNode, "IDS_PlanHelp",                  szPlanHelp);
    FindNodeValue(objNode, "IDS_Report_Desc",               szReport);
    FindNodeValue(objNode, "IDS_Report_Desc_Help",          szReportHelp);
    FindNodeValue(objNode, "IDS_Monitor_Label_Error",       szErrName);

    m_lsResource["IDS_Cancle_Add_Monitor_Tip"] = szCancelTip;
    m_lsResource["IDS_Add_Monitor_Title"] = szTitle;
    m_lsResource["IDS_Add_Monitor_Tip"] = szAddTip;
    m_lsResource["IDS_Cancel_Current_Edit_Tip"] = szCancelEditTip;
    m_lsResource["IDS_Back_Monitor_List_Tip"] = szBackTip;
    m_lsResource["IDS_Batch_Add_Tip"] = szBatchAddTip;
    m_lsResource["IDS_Continue_Add"] = szContinueAdd;
    m_lsResource["IDS_Continue_Add_Tip"] = szContinueAddTip;
    m_lsResource["IDS_Set_Default_Alert"] = szSetAlert;
    m_lsResource["IDS_Set_Default_Alert_Tip"] = szSetAlertTip;
    m_lsResource["IDS_Device_Name"] = szDevice;
    m_lsResource["IDS_Device_Name_Help"] = szDeviceHelp;
    m_lsResource["IDS_Monitor_Label"] = szMonitor;
    m_lsResource["IDS_Monitor_Label_Help"] = szMonitorHelp;
    m_lsResource["IDS_Check_Error"] = szCheckErr;
    m_lsResource["IDS_Check_Err_Help"] = szCheckHelp;
    m_lsResource["IDS_Monitor_Desc"] = szDesc;
    m_lsResource["IDS_Monitor_Desc_Help"] = szDescHelp;
    m_lsResource["IDS_Error_Freq"] = szFreq;
    m_lsResource["IDS_Error_Freq_Help"] = szFreqHelp;
    m_lsResource["IDS_Numbic_Error"] = szFreqErr;
    m_lsResource["IDS_Plan"] = szPlan;
    m_lsResource["IDS_PlanHelp"] = szPlanHelp;
    m_lsResource["IDS_Report_Desc"] = szReport;
    m_lsResource["IDS_Report_Desc_Help"] = szReportHelp;
    m_lsResource["IDS_Monitor_Label_Error"] = szErrName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadAddSVSEStrings(MAPNODE &objNode)
{
    string szName(""), szNameHelp(""), szNameTip(""), szMainTitle(""),
            szTitle(""), szEditTitle(""), szHost(""), szHostHelp(""),
            szHostTip(""), szAdvTitle(""), szDescription(""), szDescriptionHelp("");

    FindNodeValue(objNode, "IDS_SE_Label",          szName);
    FindNodeValue(objNode, "IDS_SE_Label_Tip",      szNameHelp);
    FindNodeValue(objNode, "IDS_SE_Label_Error",    szNameTip);
    FindNodeValue(objNode, "IDS_Basic_Option",      szMainTitle);
    FindNodeValue(objNode, "IDS_Add_SE_Title",      szTitle);
    FindNodeValue(objNode, "IDS_Edit_SE_Title",     szEditTitle);
    FindNodeValue(objNode, "IDS_Host_Name",         szHost);
    FindNodeValue(objNode, "IDS_Host_Name_Tip",     szHostHelp);
    FindNodeValue(objNode, "IDS_Host_Name_Error",   szHostTip);
    FindNodeValue(objNode, "IDS_Advance_Option",    szAdvTitle);
    FindNodeValue(objNode, "IDS_Description",       szDescription);
    FindNodeValue(objNode, "IDS_Desc_Help",         szDescriptionHelp);

    m_lsResource["IDS_SE_Label"] = szName;
    m_lsResource["IDS_SE_Label_Tip"] = szNameHelp;
    m_lsResource["IDS_SE_Label_Error"] = szNameTip;
    m_lsResource["IDS_Basic_Option"] = szMainTitle;
    m_lsResource["IDS_Add_SE_Title"] = szTitle;
    m_lsResource["IDS_Edit_SE_Title"] = szEditTitle;
    m_lsResource["IDS_Host_Name"] = szHost;
    m_lsResource["IDS_Host_Name_Tip"] = szHostHelp;
    m_lsResource["IDS_Host_Name_Error"] = szHostTip;
    m_lsResource["IDS_Advance_Option"] = szAdvTitle;
    m_lsResource["IDS_Description"] = szDescription;
    m_lsResource["IDS_Desc_Help"] = szDescriptionHelp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadBatchAddStrings(MAPNODE &objNode)
{
    string szTitle(""), szSetSucc(""), szAffirmDelete(""), szMsg(""),
        szCancel(""), szAddGroup(""), szClose(""), szList(""), szAddDevice(""),
        szAddMonitor(""), szEnable(""), szDisable(""), szPaste(""), szRefresh("");

    FindNodeValue(objNode, "IDS_Batch_Add", szTitle);
    FindNodeValue(objNode, "IDS_SetAlertConditionSuccess", szSetSucc);
	FindNodeValue(objNode, "IDS_AffirmDelete", szAffirmDelete);
    FindNodeValue(objNode, "IDS_MessagePrompt", szMsg);
	FindNodeValue(objNode, "IDS_ConfirmCancel", szCancel);	
	FindNodeValue(objNode, "IDS_AddGroup", szAddGroup);
	FindNodeValue(objNode, "IDS_Right_AddDevice", szAddDevice);
	FindNodeValue(objNode, "IDS_AddMonitor", szAddMonitor);
	FindNodeValue(objNode, "IDS_Enable_Monitor", szEnable);
	FindNodeValue(objNode, "IDS_DisableMonitor", szDisable);
	FindNodeValue(objNode, "IDS_Close"	, szClose);
	FindNodeValue(objNode, "IDS_Paste"	, szPaste);
	FindNodeValue(objNode, "IDS_Right_Refresh"	, szRefresh);
	FindNodeValue(objNode, "IDS_DownloadList", szList);

    m_lsResource["IDS_Batch_Add"] = szTitle;
    m_lsResource["IDS_SetAlertConditionSuccess"] = szSetSucc;
    m_lsResource["IDS_AffirmDelete"] = szAffirmDelete;
    m_lsResource["IDS_MessagePrompt"] = szMsg;
    m_lsResource["IDS_ConfirmCancel"] = szCancel;
    m_lsResource["IDS_AddGroup"] = szAddGroup;
    m_lsResource["IDS_Right_AddDevice"] = szAddDevice;
    m_lsResource["IDS_AddMonitor"] = szAddMonitor;
    m_lsResource["IDS_Enable_Monitor"] = szEnable;
    m_lsResource["IDS_DisableMonitor"] = szDisable;
    m_lsResource["IDS_Close"] = szClose;
    m_lsResource["IDS_Paste"] = szPaste;
    m_lsResource["IDS_Right_Refresh"] = szRefresh;
    m_lsResource["IDS_DownloadList"] = szList;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadConditionStrings(MAPNODE &objNode)
{
    string szOr(""), szAnd(""), szSet(""), szCondition("");
    string szConditionIsNull(""), szRelationErr(""), szMatchingErr(""), szTypeError("");

    FindNodeValue(objNode, "IDS_Or",        szOr);              // 或
    FindNodeValue(objNode, "IDS_And",       szAnd);             // 与
    FindNodeValue(objNode, "IDS_Condition", szSet);             // 条件
    FindNodeValue(objNode, "IDS_Relation",  szCondition);       // 

    FindNodeValue(objNode, "IDS_Alert_Condition_NULL",                  szConditionIsNull);
    FindNodeValue(objNode, "IDS_Alert_Condition_Relation_Error",        szRelationErr);
    FindNodeValue(objNode, "IDS_Alert_Condition_Return_Param_Error",    szMatchingErr);
    FindNodeValue(objNode, "IDS_Alert_Condition_Param_Error",           szTypeError);

    m_lsResource["IDS_Or"] = szOr;
    m_lsResource["IDS_And"] = szAnd;
    m_lsResource["IDS_Condition"] = szSet;
    m_lsResource["IDS_Relation"] = szCondition;

    m_lsResource["IDS_Alert_Condition_NULL"] = szConditionIsNull;
    m_lsResource["IDS_Alert_Condition_Relation_Error"] = szRelationErr;
    m_lsResource["IDS_Alert_Condition_Return_Param_Error"] = szMatchingErr;
    m_lsResource["IDS_Alert_Condition_Param_Error"] = szTypeError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadGeneralStrings(MAPNODE &objNode)
{
    string szTranslate(""), szTranslateTip(""), szEdit(""), szDevice(""),
        szHelp(""), szTest(""), szDepends(""), szSave(""), szSaveTip(""),
        szAdd(""), szAddTitle(""), szCancel(""), szHostLabel(""), szTestTip(""),
        szSelAll(""), szMonitorTitle(""), szCancelAdd(""), szGeneralTitle(""),
        szSaveSelTip(""), szAddMonitorErr(""), szGroup(""), szFriendless(""),
        szDescriptionHelp(""), szCondition(""), szConditionHelp(""), szDependHelp(""),
        szErr(""), szNormal(""), szWarn(""), szAffir(""), szPoint("");

    FindNodeValue(objNode, "IDS_Translate",             szTranslate);           // 翻译
    FindNodeValue(objNode, "IDS_Translate_Tip",         szTranslateTip);        // 翻译
    FindNodeValue(objNode, "IDS_Device",                szDevice);              // 设备
    FindNodeValue(objNode, "IDS_Help",                  szHelp);                // 帮助
    FindNodeValue(objNode, "IDS_Depends_On",            szDepends);             // 依靠
    FindNodeValue(objNode, "IDS_Add",                   szAdd);                 // 添加
    FindNodeValue(objNode, "IDS_Edit",                  szEdit);                // 编辑
    FindNodeValue(objNode, "IDS_Save",                  szSave);                // 保存
    FindNodeValue(objNode, "IDS_Test",                  szTest);                // 测试
    FindNodeValue(objNode, "IDS_Save_Tip",              szSaveTip);             // 保存
    FindNodeValue(objNode, "IDS_Cancel",                szCancel);              // 取消
    FindNodeValue(objNode, "IDS_Title",                 szHostLabel);           // 
    FindNodeValue(objNode, "IDS_Add_Title",             szAddTitle);            // 添加
    FindNodeValue(objNode, "IDS_Curent_Test_Tip",       szTestTip);             // 测试此设备
    FindNodeValue(objNode, "IDS_All_Select",            szSelAll);              // 全选
    FindNodeValue(objNode, "IDS_Monitor_Title",         szMonitorTitle);        // 监测器
    FindNodeValue(objNode, "IDS_Cancel_Add",            szCancelAdd);           // 取消添加
    FindNodeValue(objNode, "IDS_General_Title",         szGeneralTitle);        // 基本选项
    FindNodeValue(objNode, "IDS_Save_Sel_Monitor_Tip",  szSaveSelTip);          // 保存所选的监测器
    FindNodeValue(objNode, "IDS_Monitor_Point_Lack_Tip",szAddMonitorErr);       // 点数不足
    FindNodeValue(objNode, "IDS_Group",                 szGroup);               // 组
    FindNodeValue(objNode, "IDS_Friendless",            szFriendless);          // 无依靠
    FindNodeValue(objNode, "IDS_Advance_Desc_Help",     szDescriptionHelp);     // 
    FindNodeValue(objNode, "IDS_Depends_Condition",     szCondition);           // 依靠条件
    FindNodeValue(objNode, "IDS_Depends_Condition_Help",szConditionHelp);       //
    FindNodeValue(objNode, "IDS_Depends_On_Help",       szDependHelp);          //
    FindNodeValue(objNode, "IDS_Error",                 szErr);                 // 错误
    FindNodeValue(objNode, "IDS_Normal",                szNormal);              // 普通
    FindNodeValue(objNode, "IDS_Warnning",              szWarn);                // 警告
    FindNodeValue(objNode, "IDS_Affirm",                szAffir);               // 警告
    FindNodeValue(objNode, "IDS_PointPoor",             szPoint);               // 警告

    m_lsResource["IDS_Translate"] = szTranslate;
    m_lsResource["IDS_Translate_Tip"] = szTranslateTip;
    m_lsResource["IDS_Edit"] = szEdit;
    m_lsResource["IDS_Device"] = szDevice;
    m_lsResource["IDS_Help"] = szHelp;
    m_lsResource["IDS_Test"] = szTest;
    m_lsResource["IDS_Depends_On"] = szDepends;
    m_lsResource["IDS_Save"] = szSave;
    m_lsResource["IDS_Save_Tip"] = szSaveTip;
    m_lsResource["IDS_Add"] = szAdd;
    m_lsResource["IDS_Cancel"] = szCancel;
    m_lsResource["IDS_Title"] = szHostLabel;
    m_lsResource["IDS_Add_Title"] = szAddTitle;
    m_lsResource["IDS_Curent_Test_Tip"] = szTestTip;
    m_lsResource["IDS_All_Select"] = szSelAll;
    m_lsResource["IDS_Monitor_Title"] = szMonitorTitle;
    m_lsResource["IDS_Cancel_Add"] = szCancelAdd;
    m_lsResource["IDS_General_Title"] = szGeneralTitle;
    m_lsResource["IDS_Save_Sel_Monitor_Tip"] = szSaveSelTip;
    m_lsResource["IDS_Monitor_Point_Lack_Tip"] = szAddMonitorErr;
    m_lsResource["IDS_Group"] = szGroup;
    m_lsResource["IDS_Friendless"] = szFriendless;
    m_lsResource["IDS_Advance_Desc_Help"] = szDescriptionHelp;
    m_lsResource["IDS_Depends_Condition"] = szCondition;
    m_lsResource["IDS_Depends_Condition_Help"] = szConditionHelp;
    m_lsResource["IDS_Depends_On_Help"] = szDependHelp;
    m_lsResource["IDS_Error"] = szErr;
    m_lsResource["IDS_Normal"] = szNormal;
    m_lsResource["IDS_Warnning"] = szWarn;
    m_lsResource["IDS_Affirm"] = szAffir;
    m_lsResource["IDS_PointPoor"] = szPoint;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadGroupviewStrings(MAPNODE &objNode)
{
    string szColDel(""), szColLast(""), szColName(""), szColState(""),
        szColDesc(""), szSelAllTip(""), szSelNoneTip(""), 
        szInvertSelTip(""), szDelSelDevTip(""), szDelDevTip(""), szSortTip(""),
        szDisableDevTip(""), szEnableDevTip(""), szAddDev(""), szAddDevTip(""),
        szDelSelDevAsk(""), szTestTip(""), szMonitorCount(""), szMonitorDisable(""),
        szMonitorError(""), szMonitorWarn(""), szDeviceType(""), szOSType(""), 
        szDevicesDisable(""), szDevicesEnable(""), szDevForver(""), szDevTemprary(""),
        szStartTime(""), szEndTime(""), szNoDevice(""), szGeneralTitle(""),
        szDeviceCount("");

    FindNodeValue(objNode, "IDS_Delete",                    szColDel);                  // 删除
    FindNodeValue(objNode, "IDS_Table_Col_Last_Refresh",    szColLast);                 // 最后更新
    FindNodeValue(objNode, "IDS_Name",                      szColName);                 // 名称
    FindNodeValue(objNode, "IDS_State",                     szColState);                // 状态
    FindNodeValue(objNode, "IDS_State_Description",         szColDesc);                 // 状态描述
    FindNodeValue(objNode, "IDS_None_Select",               szSelNoneTip);              // 取消全选
    FindNodeValue(objNode, "IDS_Invert_Select",             szInvertSelTip);            // 反选
    FindNodeValue(objNode, "IDS_Delete_All_Sel_Device_Tip", szDelSelDevTip);            // 是否删除所有选择的设备
    FindNodeValue(objNode, "IDS_Delete_Device_Tip",         szDelDevTip);               // 删除此设备
    FindNodeValue(objNode, "IDS_Sort",                      szSortTip);                 // 排序
    FindNodeValue(objNode, "IDS_Disable_Device",            szDisableDevTip);           // 禁用设备
    FindNodeValue(objNode, "IDS_Enable_Device",             szEnableDevTip);            // 启用设备
    FindNodeValue(objNode, "IDS_Add_Device",                szAddDev);                  // 添加设备
    FindNodeValue(objNode, "IDS_Add_Entity_Tip",            szAddDevTip);               // 添加新的设备
    FindNodeValue(objNode, "IDS_Delete_Device_Confirm",     szDelSelDevAsk);            // 是否删除所选设备
    FindNodeValue(objNode, "IDS_Table_Col_Test",            szTestTip);                 // 测试
    FindNodeValue(objNode, "IDS_Monitor_Count",             szMonitorCount);            // 监测器总数
    FindNodeValue(objNode, "IDS_Monitor_Disable_Count",     szMonitorDisable);          // 禁止
    FindNodeValue(objNode, "IDS_Monitor_Error_Count",       szMonitorError);            // 错误
    FindNodeValue(objNode, "IDS_Monitor_Warn_Count",        szMonitorWarn);             // 警告
    FindNodeValue(objNode, "IDS_Device_Type",               szDeviceType);              // 设备类型
    FindNodeValue(objNode, "IDS_OS_Type",                   szOSType);                  // 操作系统
    FindNodeValue(objNode, "IDS_Device_Can_not_Disable",    szDevicesDisable);          // 所选设备已禁用不能再次禁用
    FindNodeValue(objNode, "IDS_Device_Can_not_Enable",     szDevicesEnable);           // 所选设备已启用不能再次启用
    FindNodeValue(objNode, "IDS_Device_Disable_Forver",     szDevForver);               // 设备被永久禁止
    FindNodeValue(objNode, "IDS_Device_Disable_Temprary",   szDevTemprary);             // 设备被临时禁止
    FindNodeValue(objNode, "IDS_Start_Time",                szStartTime);               // 开始时间
    FindNodeValue(objNode, "IDS_End_Time",                  szEndTime);                 // 终止时间
    FindNodeValue(objNode, "IDS_DIEVICE_LIST_IS_NULL",      szNoDevice);                // 设备列表为空
    FindNodeValue(objNode, "IDS_General_Infor_Title",       szGeneralTitle);            // 基础信息
    FindNodeValue(objNode, "IDS_Device_Count",              szDeviceCount);             // 设备数

    string szGroupTitle(""), szDelSelTip(""), szDelTip(""), szAdd(""), szDisableTip(""),
        szEnableTip(""), szDelAsk(""), szGroupsDisable(""), szGroupsEnable(""), 
        szForver(""), szTemprary(""), szNoGroup("");

    FindNodeValue(objNode, "IDS_Sub_Group",                 szGroupTitle);              // 子组
    FindNodeValue(objNode, "IDS_Delete_Sel_Group_Tip",      szDelSelTip);               // 删除所有选择的子组
    FindNodeValue(objNode, "IDS_Delete_Group_Tip",          szDelTip);                  // 删除所选的子组
    FindNodeValue(objNode, "IDS_Add_Group",                 szAdd);                     // 添加子组
    FindNodeValue(objNode, "IDS_Disable_Group",             szDisableTip);              // 禁用子组
    FindNodeValue(objNode, "IDS_Enable_Group",              szEnableTip);               // 启用子组
    FindNodeValue(objNode, "IDS_Delete_Group_Confirm",      szDelAsk);                  // 是否删除所选的子组
    FindNodeValue(objNode, "IDS_Group_Can_not_Disable",     szGroupsDisable);           // 所选的组已经全部禁用不能再次禁用
    FindNodeValue(objNode, "IDS_Group_Can_not_Enable",      szGroupsEnable);            // 所选的组已经全部启用不能再次启用
    FindNodeValue(objNode, "IDS_Group_Disable_Forver",      szForver);                  // 组被永久禁用
    FindNodeValue(objNode, "IDS_Group_Disable_Temprary",    szTemprary);                // 组被临时禁用
    FindNodeValue(objNode, "IDS_GROUP_LIST_IS_NULL",        szNoGroup);                 // 组列表为空

    m_lsResource["IDS_Delete"] = szColDel;
    m_lsResource["IDS_Table_Col_Last_Refresh"] = szColLast;
    m_lsResource["IDS_Name"] = szColName;
    m_lsResource["IDS_State"] = szColState;
    m_lsResource["IDS_State_Description"] = szColDesc;
    m_lsResource["IDS_None_Select"] = szSelNoneTip;
    m_lsResource["IDS_Invert_Select"] = szInvertSelTip;
    m_lsResource["IDS_Delete_All_Sel_Device_Tip"] = szDelSelDevTip;
    m_lsResource["IDS_Delete_Device_Tip"] = szDelDevTip;
    m_lsResource["IDS_Sort"] = szSortTip;
    m_lsResource["IDS_Disable_Device"] = szDisableDevTip;
    m_lsResource["IDS_Enable_Device"] = szEnableDevTip;
    m_lsResource["IDS_Add_Device"] = szAddDev;
    m_lsResource["IDS_Add_Entity_Tip"] = szAddDevTip;
    m_lsResource["IDS_Delete_Device_Confirm"] = szDelSelDevAsk;
    m_lsResource["IDS_Table_Col_Test"] = szTestTip;
    m_lsResource["IDS_Monitor_Count"] = szMonitorCount;
    m_lsResource["IDS_Monitor_Disable_Count"] = szMonitorDisable;
    m_lsResource["IDS_Monitor_Error_Count"] = szMonitorError;
    m_lsResource["IDS_Monitor_Warn_Count"] = szMonitorWarn;
    m_lsResource["IDS_Device_Type"] = szDeviceType;
    m_lsResource["IDS_OS_Type"] = szOSType;
    m_lsResource["IDS_Device_Can_not_Disable"] = szDevicesDisable;
    m_lsResource["IDS_Device_Can_not_Enable"] = szDevicesEnable;
    m_lsResource["IDS_Device_Disable_Forver"] = szDevForver;
    m_lsResource["IDS_Device_Disable_Temprary"] = szDevTemprary;
    m_lsResource["IDS_Start_Time"] = szStartTime;
    m_lsResource["IDS_End_Time"] = szEndTime;
    m_lsResource["IDS_DIEVICE_LIST_IS_NULL"] = szNoDevice;
    m_lsResource["IDS_General_Infor_Title"] = szGeneralTitle;
    m_lsResource["IDS_Device_Count"] = szDeviceCount;
    m_lsResource["IDS_Sub_Group"] = szGroupTitle;
    m_lsResource["IDS_Delete_Sel_Group_Tip"] = szDelSelTip;
    m_lsResource["IDS_Delete_Group_Tip"] = szDelTip;
    m_lsResource["IDS_Add_Group"] = szAdd;
    m_lsResource["IDS_Disable_Group"] = szDisableTip;
    m_lsResource["IDS_Enable_Group"] = szEnableTip;
    m_lsResource["IDS_Delete_Group_Confirm"] = szDelAsk;
    m_lsResource["IDS_Group_Can_not_Disable"] = szGroupsDisable;
    m_lsResource["IDS_Group_Can_not_Enable"] = szGroupsEnable;
    m_lsResource["IDS_Group_Disable_Forver"] = szForver;
    m_lsResource["IDS_Group_Disable_Temprary"] = szTemprary;
    m_lsResource["IDS_GROUP_LIST_IS_NULL"] = szNoGroup;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadMonitorviewStrings(MAPNODE &objNode)
{
    string szDelAsk(""), szRefreshTime(""), szColRefresh(""), szEditTip(""), 
        szRefreshTip(""), szOperateTip(""), szMonitorTitle(""),
        szAdd(""), szListviewTip(""), szIconviewTip(""), szBackParent(""), 
        szBackParentTip(""), szDay(""), szHour(""), szMinute(""), szMonitorsDisable(""),
        szMonitorsEnable(""), szForver(""), szTemprary(""), 
        szEnableTip(""), szDisableTip(""), szDelSelTip(""), szNoMonitor(""), 
        szCopySelTip(""), szPastTip("");

    FindNodeValue(objNode, "IDS_Delete_Monitor_Confirm",    szDelAsk);              // 是否删除所选监测器
    FindNodeValue(objNode, "IDS_Refresh_Time",              szRefreshTime);         // 刷新时间
    FindNodeValue(objNode, "IDS_Refresh_Tip",               szColRefresh);          // 刷新
    FindNodeValue(objNode, "IDS_Monitor_Edit_Tip",          szEditTip);             // 编辑
    FindNodeValue(objNode, "IDS_Monitor_Refresh_Tip",       szRefreshTip);          // 刷新所选监测器
    FindNodeValue(objNode, "IDS_Disable_Enable_Tip",        szOperateTip);          // 禁用/启用
    FindNodeValue(objNode, "IDS_Monitor_List_Title",        szMonitorTitle);        // 监测器列表
    FindNodeValue(objNode, "IDS_Add_Monitor",               szAdd);                 // 添加监测器
    FindNodeValue(objNode, "IDS_List_View_Tip",             szListviewTip);         // 列表视图
    FindNodeValue(objNode, "IDS_Icon_View_Tip",             szIconviewTip);         // 图标视图
    FindNodeValue(objNode, "IDS_Operate_Back_Parent",       szBackParent);          // 返回上一级
    FindNodeValue(objNode, "IDS_Operate_Back_Parent_Tip",   szBackParentTip);       // 返回上一级组
    FindNodeValue(objNode, "IDS_Day",                       szDay);                 // 天
    FindNodeValue(objNode, "IDS_Hour",                      szHour);                // 小时
    FindNodeValue(objNode, "IDS_Minute",                    szMinute);              // 分钟
    FindNodeValue(objNode, "IDS_Monitor_Can_not_Disable",   szMonitorsDisable);     // 所选监测器已全部禁用不能再次禁用
    FindNodeValue(objNode, "IDS_Monitor_Can_not_Enable",    szMonitorsEnable);      // 所选监测器已全部启用不能再次启用
    FindNodeValue(objNode, "IDS_Monitor_Disable_Forver",    szForver);              // 监测器被永久禁止
    FindNodeValue(objNode, "IDS_Monitor_Disable_Temprary",  szTemprary);            // 监测器被临时禁止
    FindNodeValue(objNode, "IDS_Enable_Monitor_Tip",        szEnableTip);           // 启用所有选择的监测器
    FindNodeValue(objNode, "IDS_Disable_Monitor_Tip",       szDisableTip);          // 禁止所有选择的监测器
    FindNodeValue(objNode, "IDS_Delete_Select_Monitor_Tip", szDelSelTip);           // 是否删除所有选择的监测器
    FindNodeValue(objNode, "IDS_MONITOR_LIST_IS_NULL",      szNoMonitor);           // 监测器列表为空
    FindNodeValue(objNode, "IDS_Copy",                      szCopySelTip);          // 拷贝
    FindNodeValue(objNode, "IDS_Past",                      szPastTip);             // 粘贴
    
    m_lsResource["IDS_Delete_Monitor_Confirm"] = szDelAsk;
    m_lsResource["IDS_Refresh_Time"] = szRefreshTime;
    m_lsResource["IDS_Refresh_Tip"] = szColRefresh;
    m_lsResource["IDS_Monitor_Edit_Tip"] = szEditTip;
    m_lsResource["IDS_Monitor_Refresh_Tip"] = szRefreshTip;
    m_lsResource["IDS_Disable_Enable_Tip"] = szOperateTip;
    m_lsResource["IDS_Monitor_List_Title"] = szMonitorTitle;
    m_lsResource["IDS_Add_Monitor"] = szAdd;
    m_lsResource["IDS_List_View_Tip"] = szListviewTip;
    m_lsResource["IDS_Icon_View_Tip"] = szIconviewTip;
    m_lsResource["IDS_Operate_Back_Parent"] = szBackParent;
    m_lsResource["IDS_Operate_Back_Parent_Tip"] = szBackParentTip;
    m_lsResource["IDS_Day"] = szDay;
    m_lsResource["IDS_Hour"] = szHour;
    m_lsResource["IDS_Minute"] = szMinute;
    m_lsResource["IDS_Monitor_Can_not_Disable"] = szMonitorsDisable;
    m_lsResource["IDS_Monitor_Can_not_Enable"] = szMonitorsEnable;
    m_lsResource["IDS_Monitor_Disable_Forver"] = szForver;
    m_lsResource["IDS_Monitor_Disable_Temprary"] = szTemprary;
    m_lsResource["IDS_Enable_Monitor_Tip"] = szEnableTip;
    m_lsResource["IDS_Disable_Monitor_Tip"] = szDisableTip;
    m_lsResource["IDS_Delete_Select_Monitor_Tip"] = szDelSelTip;
    m_lsResource["IDS_MONITOR_LIST_IS_NULL"] = szNoMonitor;
    m_lsResource["IDS_Copy"] = szCopySelTip;
    m_lsResource["IDS_Past"] = szPastTip;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadSortStrings(MAPNODE &objNode)
{
    string szSave(""), szSaveTip(""), szCancelTip(""), szUpTip(""), szDownTip("");

    FindNodeValue(objNode, "IDS_OK",                szSave);        // 保存
    FindNodeValue(objNode, "IDS_Save_Sort_Tip",     szSaveTip);     // 保存并返回上一视图
    FindNodeValue(objNode, "IDS_Cancel_Sort_Tip",   szCancelTip);   // 取消排序
    FindNodeValue(objNode, "IDS_Up_Floor_Tip",      szUpTip);       // 上移一行
    FindNodeValue(objNode, "IDS_Down_Floor_Tip",    szDownTip);     // 下移一行

    m_lsResource["IDS_OK"] = szSave;
    m_lsResource["IDS_Save_Sort_Tip"] = szSaveTip;
    m_lsResource["IDS_Cancel_Sort_Tip"] = szCancelTip;
    m_lsResource["IDS_Up_Floor_Tip"] = szUpTip;
    m_lsResource["IDS_Down_Floor_Tip"] = szDownTip;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadSVSEViewStrings(MAPNODE &objNode)
{
    string szSE(""), szNoData(""), szDisable(""), szTitle(""), szAdd(""), 
        szAddTip(""), szDelSelTip(""), szRefresh(""), szEnable("");

    FindNodeValue(objNode, "IDS_SE",          szSE);              // SE
    FindNodeValue(objNode, "IDS_NO_Date",       szNoData);          // 无历史数据
    FindNodeValue(objNode, "IDS_Disable",       szDisable);         // 禁止
    FindNodeValue(objNode, "IDS_SE_List_Title", szTitle);           // SE 列表
    FindNodeValue(objNode, "IDS_Add_SE",        szAdd);             // 添加 SE
    FindNodeValue(objNode, "IDS_Add_SE_Tip",    szAddTip);          // 添加(配置) 新的SE
    FindNodeValue(objNode, "IDS_Delete_SE_Tip", szDelSelTip);       // 
    FindNodeValue(objNode, "IDS_Refresh",       szRefresh);         // 刷新
    FindNodeValue(objNode, "IDS_Enable",        szEnable);          // 允许

    m_lsResource["IDS_SE"] = szSE;
    m_lsResource["IDS_NO_Date"] = szNoData;
    m_lsResource["IDS_Disable"] = szDisable;
    m_lsResource["IDS_SE_List_Title"] = szTitle;
    m_lsResource["IDS_Add_SE"] = szAdd;
    m_lsResource["IDS_Add_SE_Tip"] = szAddTip;
    m_lsResource["IDS_Delete_SE_Tip"] = szDelSelTip;
    m_lsResource["IDS_Refresh"] = szRefresh;
    m_lsResource["IDS_Enable"] = szEnable;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVResString::loadTreeviewStrings(MAPNODE &objNode)
{
    string szBaseSEErr(""), szAskDelSE(""), szAskDelGroup(""), 
        szAskDelDevice(""), szRefreshTree(""), szNoChild("");

    FindNodeValue(objNode, "IDS_Base_SE_Not_Delete",        szBaseSEErr);       // 基础SE不能被删除
    FindNodeValue(objNode, "IDS_Delete_SE_Confirm",         szAskDelSE);        // 是否删除所选SE
    FindNodeValue(objNode, "IDS_Delete_Sel_Group_Confirm",  szAskDelGroup);     // 是否删除所选组
    FindNodeValue(objNode, "IDS_Delete_Sel_Device_Confirm", szAskDelDevice);    // 是否删除所选设备
    FindNodeValue(objNode, "IDS_Refresh_View",              szRefreshTree);     // 同步视图
    FindNodeValue(objNode, "IDS_SE_HAS_NO_CHILD",           szNoChild);         // SE下没有添加任何数据

    m_lsResource["IDS_Base_SE_Not_Delete"] = szBaseSEErr;
    m_lsResource["IDS_Delete_SE_Confirm"] = szAskDelSE;
    m_lsResource["IDS_Delete_Sel_Group_Confirm"] = szAskDelGroup;
    m_lsResource["IDS_Delete_Sel_Device_Confirm"] = szAskDelDevice;
    m_lsResource["IDS_Refresh_View"] = szRefreshTree;
    m_lsResource["IDS_SE_HAS_NO_CHILD"] = szNoChild;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string SVResString::getStringFromRes(const char *pcszResID)
{
    string szValue("");
    if(m_objRes != INVALID_VALUE)
    {
        MAPNODE resNode = GetResourceNode(m_objRes);
        if(resNode != INVALID_VALUE)
        {
            if(FindNodeValue(resNode, pcszResID, szValue))
                m_lsResource[pcszResID] = szValue;
            else
            {
                m_lsResource[pcszResID] = pcszResID;
                szValue = pcszResID;
            }
        }
    }
    return szValue;
}
