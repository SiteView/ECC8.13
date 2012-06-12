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
            loadTreeviewStrings(resNode);              // ��������ʾ��Դ�ַ���
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

    FindNodeValue(objNode, "IDS_Or",        szOr);              // ��
    FindNodeValue(objNode, "IDS_And",       szAnd);             // ��
    FindNodeValue(objNode, "IDS_Condition", szSet);             // ����
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

    FindNodeValue(objNode, "IDS_Translate",             szTranslate);           // ����
    FindNodeValue(objNode, "IDS_Translate_Tip",         szTranslateTip);        // ����
    FindNodeValue(objNode, "IDS_Device",                szDevice);              // �豸
    FindNodeValue(objNode, "IDS_Help",                  szHelp);                // ����
    FindNodeValue(objNode, "IDS_Depends_On",            szDepends);             // ����
    FindNodeValue(objNode, "IDS_Add",                   szAdd);                 // ���
    FindNodeValue(objNode, "IDS_Edit",                  szEdit);                // �༭
    FindNodeValue(objNode, "IDS_Save",                  szSave);                // ����
    FindNodeValue(objNode, "IDS_Test",                  szTest);                // ����
    FindNodeValue(objNode, "IDS_Save_Tip",              szSaveTip);             // ����
    FindNodeValue(objNode, "IDS_Cancel",                szCancel);              // ȡ��
    FindNodeValue(objNode, "IDS_Title",                 szHostLabel);           // 
    FindNodeValue(objNode, "IDS_Add_Title",             szAddTitle);            // ���
    FindNodeValue(objNode, "IDS_Curent_Test_Tip",       szTestTip);             // ���Դ��豸
    FindNodeValue(objNode, "IDS_All_Select",            szSelAll);              // ȫѡ
    FindNodeValue(objNode, "IDS_Monitor_Title",         szMonitorTitle);        // �����
    FindNodeValue(objNode, "IDS_Cancel_Add",            szCancelAdd);           // ȡ�����
    FindNodeValue(objNode, "IDS_General_Title",         szGeneralTitle);        // ����ѡ��
    FindNodeValue(objNode, "IDS_Save_Sel_Monitor_Tip",  szSaveSelTip);          // ������ѡ�ļ����
    FindNodeValue(objNode, "IDS_Monitor_Point_Lack_Tip",szAddMonitorErr);       // ��������
    FindNodeValue(objNode, "IDS_Group",                 szGroup);               // ��
    FindNodeValue(objNode, "IDS_Friendless",            szFriendless);          // ������
    FindNodeValue(objNode, "IDS_Advance_Desc_Help",     szDescriptionHelp);     // 
    FindNodeValue(objNode, "IDS_Depends_Condition",     szCondition);           // ��������
    FindNodeValue(objNode, "IDS_Depends_Condition_Help",szConditionHelp);       //
    FindNodeValue(objNode, "IDS_Depends_On_Help",       szDependHelp);          //
    FindNodeValue(objNode, "IDS_Error",                 szErr);                 // ����
    FindNodeValue(objNode, "IDS_Normal",                szNormal);              // ��ͨ
    FindNodeValue(objNode, "IDS_Warnning",              szWarn);                // ����
    FindNodeValue(objNode, "IDS_Affirm",                szAffir);               // ����
    FindNodeValue(objNode, "IDS_PointPoor",             szPoint);               // ����

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

    FindNodeValue(objNode, "IDS_Delete",                    szColDel);                  // ɾ��
    FindNodeValue(objNode, "IDS_Table_Col_Last_Refresh",    szColLast);                 // ������
    FindNodeValue(objNode, "IDS_Name",                      szColName);                 // ����
    FindNodeValue(objNode, "IDS_State",                     szColState);                // ״̬
    FindNodeValue(objNode, "IDS_State_Description",         szColDesc);                 // ״̬����
    FindNodeValue(objNode, "IDS_None_Select",               szSelNoneTip);              // ȡ��ȫѡ
    FindNodeValue(objNode, "IDS_Invert_Select",             szInvertSelTip);            // ��ѡ
    FindNodeValue(objNode, "IDS_Delete_All_Sel_Device_Tip", szDelSelDevTip);            // �Ƿ�ɾ������ѡ����豸
    FindNodeValue(objNode, "IDS_Delete_Device_Tip",         szDelDevTip);               // ɾ�����豸
    FindNodeValue(objNode, "IDS_Sort",                      szSortTip);                 // ����
    FindNodeValue(objNode, "IDS_Disable_Device",            szDisableDevTip);           // �����豸
    FindNodeValue(objNode, "IDS_Enable_Device",             szEnableDevTip);            // �����豸
    FindNodeValue(objNode, "IDS_Add_Device",                szAddDev);                  // ����豸
    FindNodeValue(objNode, "IDS_Add_Entity_Tip",            szAddDevTip);               // ����µ��豸
    FindNodeValue(objNode, "IDS_Delete_Device_Confirm",     szDelSelDevAsk);            // �Ƿ�ɾ����ѡ�豸
    FindNodeValue(objNode, "IDS_Table_Col_Test",            szTestTip);                 // ����
    FindNodeValue(objNode, "IDS_Monitor_Count",             szMonitorCount);            // ���������
    FindNodeValue(objNode, "IDS_Monitor_Disable_Count",     szMonitorDisable);          // ��ֹ
    FindNodeValue(objNode, "IDS_Monitor_Error_Count",       szMonitorError);            // ����
    FindNodeValue(objNode, "IDS_Monitor_Warn_Count",        szMonitorWarn);             // ����
    FindNodeValue(objNode, "IDS_Device_Type",               szDeviceType);              // �豸����
    FindNodeValue(objNode, "IDS_OS_Type",                   szOSType);                  // ����ϵͳ
    FindNodeValue(objNode, "IDS_Device_Can_not_Disable",    szDevicesDisable);          // ��ѡ�豸�ѽ��ò����ٴν���
    FindNodeValue(objNode, "IDS_Device_Can_not_Enable",     szDevicesEnable);           // ��ѡ�豸�����ò����ٴ�����
    FindNodeValue(objNode, "IDS_Device_Disable_Forver",     szDevForver);               // �豸�����ý�ֹ
    FindNodeValue(objNode, "IDS_Device_Disable_Temprary",   szDevTemprary);             // �豸����ʱ��ֹ
    FindNodeValue(objNode, "IDS_Start_Time",                szStartTime);               // ��ʼʱ��
    FindNodeValue(objNode, "IDS_End_Time",                  szEndTime);                 // ��ֹʱ��
    FindNodeValue(objNode, "IDS_DIEVICE_LIST_IS_NULL",      szNoDevice);                // �豸�б�Ϊ��
    FindNodeValue(objNode, "IDS_General_Infor_Title",       szGeneralTitle);            // ������Ϣ
    FindNodeValue(objNode, "IDS_Device_Count",              szDeviceCount);             // �豸��

    string szGroupTitle(""), szDelSelTip(""), szDelTip(""), szAdd(""), szDisableTip(""),
        szEnableTip(""), szDelAsk(""), szGroupsDisable(""), szGroupsEnable(""), 
        szForver(""), szTemprary(""), szNoGroup("");

    FindNodeValue(objNode, "IDS_Sub_Group",                 szGroupTitle);              // ����
    FindNodeValue(objNode, "IDS_Delete_Sel_Group_Tip",      szDelSelTip);               // ɾ������ѡ�������
    FindNodeValue(objNode, "IDS_Delete_Group_Tip",          szDelTip);                  // ɾ����ѡ������
    FindNodeValue(objNode, "IDS_Add_Group",                 szAdd);                     // �������
    FindNodeValue(objNode, "IDS_Disable_Group",             szDisableTip);              // ��������
    FindNodeValue(objNode, "IDS_Enable_Group",              szEnableTip);               // ��������
    FindNodeValue(objNode, "IDS_Delete_Group_Confirm",      szDelAsk);                  // �Ƿ�ɾ����ѡ������
    FindNodeValue(objNode, "IDS_Group_Can_not_Disable",     szGroupsDisable);           // ��ѡ�����Ѿ�ȫ�����ò����ٴν���
    FindNodeValue(objNode, "IDS_Group_Can_not_Enable",      szGroupsEnable);            // ��ѡ�����Ѿ�ȫ�����ò����ٴ�����
    FindNodeValue(objNode, "IDS_Group_Disable_Forver",      szForver);                  // �鱻���ý���
    FindNodeValue(objNode, "IDS_Group_Disable_Temprary",    szTemprary);                // �鱻��ʱ����
    FindNodeValue(objNode, "IDS_GROUP_LIST_IS_NULL",        szNoGroup);                 // ���б�Ϊ��

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

    FindNodeValue(objNode, "IDS_Delete_Monitor_Confirm",    szDelAsk);              // �Ƿ�ɾ����ѡ�����
    FindNodeValue(objNode, "IDS_Refresh_Time",              szRefreshTime);         // ˢ��ʱ��
    FindNodeValue(objNode, "IDS_Refresh_Tip",               szColRefresh);          // ˢ��
    FindNodeValue(objNode, "IDS_Monitor_Edit_Tip",          szEditTip);             // �༭
    FindNodeValue(objNode, "IDS_Monitor_Refresh_Tip",       szRefreshTip);          // ˢ����ѡ�����
    FindNodeValue(objNode, "IDS_Disable_Enable_Tip",        szOperateTip);          // ����/����
    FindNodeValue(objNode, "IDS_Monitor_List_Title",        szMonitorTitle);        // ������б�
    FindNodeValue(objNode, "IDS_Add_Monitor",               szAdd);                 // ��Ӽ����
    FindNodeValue(objNode, "IDS_List_View_Tip",             szListviewTip);         // �б���ͼ
    FindNodeValue(objNode, "IDS_Icon_View_Tip",             szIconviewTip);         // ͼ����ͼ
    FindNodeValue(objNode, "IDS_Operate_Back_Parent",       szBackParent);          // ������һ��
    FindNodeValue(objNode, "IDS_Operate_Back_Parent_Tip",   szBackParentTip);       // ������һ����
    FindNodeValue(objNode, "IDS_Day",                       szDay);                 // ��
    FindNodeValue(objNode, "IDS_Hour",                      szHour);                // Сʱ
    FindNodeValue(objNode, "IDS_Minute",                    szMinute);              // ����
    FindNodeValue(objNode, "IDS_Monitor_Can_not_Disable",   szMonitorsDisable);     // ��ѡ�������ȫ�����ò����ٴν���
    FindNodeValue(objNode, "IDS_Monitor_Can_not_Enable",    szMonitorsEnable);      // ��ѡ�������ȫ�����ò����ٴ�����
    FindNodeValue(objNode, "IDS_Monitor_Disable_Forver",    szForver);              // ����������ý�ֹ
    FindNodeValue(objNode, "IDS_Monitor_Disable_Temprary",  szTemprary);            // ���������ʱ��ֹ
    FindNodeValue(objNode, "IDS_Enable_Monitor_Tip",        szEnableTip);           // ��������ѡ��ļ����
    FindNodeValue(objNode, "IDS_Disable_Monitor_Tip",       szDisableTip);          // ��ֹ����ѡ��ļ����
    FindNodeValue(objNode, "IDS_Delete_Select_Monitor_Tip", szDelSelTip);           // �Ƿ�ɾ������ѡ��ļ����
    FindNodeValue(objNode, "IDS_MONITOR_LIST_IS_NULL",      szNoMonitor);           // ������б�Ϊ��
    FindNodeValue(objNode, "IDS_Copy",                      szCopySelTip);          // ����
    FindNodeValue(objNode, "IDS_Past",                      szPastTip);             // ճ��
    
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

    FindNodeValue(objNode, "IDS_OK",                szSave);        // ����
    FindNodeValue(objNode, "IDS_Save_Sort_Tip",     szSaveTip);     // ���沢������һ��ͼ
    FindNodeValue(objNode, "IDS_Cancel_Sort_Tip",   szCancelTip);   // ȡ������
    FindNodeValue(objNode, "IDS_Up_Floor_Tip",      szUpTip);       // ����һ��
    FindNodeValue(objNode, "IDS_Down_Floor_Tip",    szDownTip);     // ����һ��

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
    FindNodeValue(objNode, "IDS_NO_Date",       szNoData);          // ����ʷ����
    FindNodeValue(objNode, "IDS_Disable",       szDisable);         // ��ֹ
    FindNodeValue(objNode, "IDS_SE_List_Title", szTitle);           // SE �б�
    FindNodeValue(objNode, "IDS_Add_SE",        szAdd);             // ��� SE
    FindNodeValue(objNode, "IDS_Add_SE_Tip",    szAddTip);          // ���(����) �µ�SE
    FindNodeValue(objNode, "IDS_Delete_SE_Tip", szDelSelTip);       // 
    FindNodeValue(objNode, "IDS_Refresh",       szRefresh);         // ˢ��
    FindNodeValue(objNode, "IDS_Enable",        szEnable);          // ����

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

    FindNodeValue(objNode, "IDS_Base_SE_Not_Delete",        szBaseSEErr);       // ����SE���ܱ�ɾ��
    FindNodeValue(objNode, "IDS_Delete_SE_Confirm",         szAskDelSE);        // �Ƿ�ɾ����ѡSE
    FindNodeValue(objNode, "IDS_Delete_Sel_Group_Confirm",  szAskDelGroup);     // �Ƿ�ɾ����ѡ��
    FindNodeValue(objNode, "IDS_Delete_Sel_Device_Confirm", szAskDelDevice);    // �Ƿ�ɾ����ѡ�豸
    FindNodeValue(objNode, "IDS_Refresh_View",              szRefreshTree);     // ͬ����ͼ
    FindNodeValue(objNode, "IDS_SE_HAS_NO_CHILD",           szNoChild);         // SE��û������κ�����

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
