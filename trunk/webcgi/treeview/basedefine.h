#ifndef _SITEVIEW_ECC_BASE_DEFINEC_H_
#define _SITEVIEW_ECC_BASE_DEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView ECC Object Type
// SE Group || SE || Group(Sub Group) || Device || Monitor
enum SiteView_ECC_OBJECT
{
    SiteView_ECC_SE_Group   = 0x01,
    SiteView_ECC_SE         = 0x02,
    SiteView_ECC_Group      = 0x03,
    SiteView_ECC_Device     = 0x04,
    SiteView_ECC_Monitor    = 0x05
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// monitor state
// ������ || ���� || ����״̬ || ���� || ��ֹ || ���ش����
enum dyn_monitor_state
{
    dyn_no_date     = 0x00,
    dyn_normal      = 0x01,
    dyn_warnning    = 0x02,
    dyn_error       = 0x03,
    dyn_disable     = 0x04,
    dyn_bad         = 0x05
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
typedef enum SV_PopMenu_Operate_Code
{
	SV_ADD_GROUP = 0x020,       // �����
	SV_ADD_DEVICE = 0x021,      // ����豸
	SV_ADD_MONITOR = 0x022,     // ��Ӽ����
    SV_EDIT = 0x012,            // �༭
    SV_DELETE = 0x013,          // ɾ��
    SV_ENABLE = 0x014,          // ����
    SV_DISABLE = 0x015,         // ����
    //SV_RUN = 0x016,           // ����
    SV_REFRESH = 0x017,         // ˢ��
    //SV_CLICK = 0x018,         // ����
    SV_SORT = 0x019,            // ����
    //SV_COLLAPSE = 0x01A,      // 
    SV_COPY = 0x01B,            // ����
    SV_PAST = 0x01C,            // ճ��
    SV_TEST = 0x01D             // ����
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ȩ�޶���
enum SiteView_ECC_Purview
{
    Add_Group       = 0x2,          // �����
    Add_Device      = 0x3,          // ����豸
    Add_Monitor     = 0x4,          // ��Ӽ����
    Edit_SVSE       = 0x10,         // �༭SE
    Edit_Group      = 0x20,         // �༭��
    Edit_Device     = 0x30,         // �༭�豸
    Edit_Monitor    = 0x40,         // �༭�����
    Delete_Group    = 0x200,        // ɾ����
    Delete_Device   = 0x300,        // ɾ���豸
    Delete_Monitor  = 0x400,        // ɾ�������
    Refresh_Device  = 0x3000,       // ˢ���豸
    Refresh_Monitor = 0x4000,       // ˢ�¼����
    Test_Device     = 0x30000,      // �����豸
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char SV_REFRESH_QUEUE[]            = "SiteView70_RefreshInfo_%s";  // ˢ�¶���ͷ
static const char SV_CONFIG_TRACK[]             = "SiteView70-ConfigTrack_%s";  // ���ø��Ķ���ͷ
static const char SV_USER_OPERATE_LOG_TABLE[]   = "UserOperateLog";             // ������־
static const char sv_disable_end[]              = "DISABLE_END";                // ��ֹ/����ֹͣ��־
// ��������
static const char svPassword[]                  = "password";                   // ����
static const char svText[]                      = "text";                       // �ı�
static const char svTextbox[]                   = "textbox";                    // �ı���
static const char svCheckBox[]                  = "checkbox";                   // ��ѡ��
static const char svRadioBox[]                  = "radiobox";                   // ��ѡ��
static const char svTextArea[]                  = "textarea";                   // ���ı���
static const char svComboBox[]                  = "combobox";                   // �����б��
static const char svListBox[]                   = "listbox";                    // �б��
static const char svTree[]                      = "tree";                       // ����
static const char svButton[]                    = "button";                     // ��ť

static const char svType[]                      = "sv_type";                    // ��������
static const char svTip[]                       = "sv_tip";                     // ������ʾ��Ϣ
static const char svSaveName[]                  = "sv_savename";                // �洢����
static const char svAllowNull[]                 = "sv_allownull";               // �Ƿ�����Ϊ��
static const char svHelpText[]                  = "sv_helptext";                // �����ı���Ϣ
static const char svStyle[]                     = "sv_style";                   // ��ʽ��
static const char svRun[]                       = "sv_run";                     // �Ƿ�����Ҫ����������ʱ������
static const char svDLL[]                       = "sv_dll";                     // ��̬���ӿ�
static const char svFunc[]                      = "sv_func";                    // ����
static const char svValue[]                     = "sv_value";                   // ����
static const char svFollow[]                    = "sv_follow";                  // ����
static const char svHidden[]                    = "sv_hidden";                  // �Ƿ�����
static const char svAccountWith[]               = "sv_accountwith";             // ����**����
static const char svIsNumeric[]                 = "sv_isnumeric";               // �Ƿ�������
static const char svItemCount[]                 = "sv_itemcount";               // ��Ŀ����
static const char svReadOnly[]                  = "sv_isreadonly";              // �Ƿ�ֻ��
static const char svExpressions[]               = "sv_expressions";             // ����ʽ
static const char svNoSort[]                    = "sv_nosort";                  // �Ƿ�����
static const char svMax[]                       = "sv_max";                     // ���ֵ
static const char svMin[]                       = "sv_min";                     // ��Сֵ
static const char svSynTitle[]                  = "sv_syntitle";                // ��̬����
static const char svName[]                      = "sv_name";                    // ����
static const char svLabel[]                     = "sv_label";                   // ��ǩ
static const char svOSType[]                    = "_OsType";                    // ϵͳ����
static const char svDeviceType[]                = "sv_devicetype";              // �豸����
static const char svDependCondition[]           = "sv_dependscondition";        // ��������
static const char svDependON[]                  = "sv_dependson";               // ������
static const char svShowIndex[]                 = "sv_index";                   // ��ʾ����
static const char svDescription[]               = "sv_description";             // ����
static const char svNetworkSet[]                = "sv_network";                 // �Ƿ��������豸
static const char svItemLable[]                 = "sv_itemlabel%d";             // ��Ŀ��ǩ
static const char svItemValue[]                 = "sv_itemvalue%d";             // ��Ŀ����
static const char svDisable[]                   = "sv_disable";                 // �Ƿ��ֹ��true, false, time��
static const char svStartTime[]                 = "sv_starttime";               // ��ʼʱ��
static const char svEndTime[]                   = "sv_endtime";                 // ����ʱ��
static const char svQuickAdd[]                  = "sv_quickadd";                // ������Ӽ�����б�
static const char svQuickAddSel[]               = "sv_quickaddsel";             // �������ȱʡѡ��
static const char svConditionCount[]            = "sv_conditioncount";          // ��������ƥ��ʽ����
static const char svParamValue[]                = "sv_paramvalue%d";            // ����ֵ
static const char svParamName[]                 = "sv_paramname%d";             // ������
static const char svOperate[]                   = "sv_operate%d";               // ����
static const char svRelation[]                  = "sv_relation%d";              // ���ӷ�
static const char svUnit[]                      = "sv_unit";                    // ��λ
static const char svExpression[]                = "sv_expression";              // 
static const char svReportDesc[]                = "sv_reportdesc";              // ��������
static const char svPlan[]                      = "sv_plan";                    // ����ƻ�
static const char svCheckErr[]                  = "sv_checkerr";                // У�����
static const char svErrFreqSave[]               = "sv_errfreqsave";             // ����ʱ���Ƶ�ʴ洢
static const char svErrFreq[]                   = "sv_errfreq";                 // ����ʱ���Ƶ��
static const char svErrFreqUnit[]               = "sv_errfrequint";             // ������Ƶ�ʵ�λ
static const char svMonitorType[]               = "sv_monitortype";             // ���������
static const char svIntPos[]                    = "sv_intpos";                  // �����ռ�õ���
static const char svExtraDll[]                  = "sv_extradll";                // ��չ��̬���ӿ�
static const char svExtraSave[]                 = "sv_extrasave";               // ��̬������չ�洢Ϊ
static const char svExtraFunc[]                 = "sv_extrafunc";               // ��չ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char chLeftBracket                 = '[';                          // ������
static const char chRightBracket                = ']';                          // ������

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int  svBufferSize                  = 1024 * 50;                    // ��󻺳�����С
static const int  svMax_Size                    = 256;                          // ���ֵ

static const string sv_refresh_end_sign         = "Refresh_END";                // ˢ�¼��ֹͣ��־
static const string sv_disable_sign             = "DISABLE";                    // ���������ֹ
#endif
