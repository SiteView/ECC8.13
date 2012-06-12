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
// 无数据 || 正常 || 警告状态 || 错误 || 禁止 || 严重错误的
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
// 操作
typedef enum SV_PopMenu_Operate_Code
{
	SV_ADD_GROUP = 0x020,       // 添加组
	SV_ADD_DEVICE = 0x021,      // 添加设备
	SV_ADD_MONITOR = 0x022,     // 添加监测器
    SV_EDIT = 0x012,            // 编辑
    SV_DELETE = 0x013,          // 删除
    SV_ENABLE = 0x014,          // 启用
    SV_DISABLE = 0x015,         // 禁用
    //SV_RUN = 0x016,           // 运行
    SV_REFRESH = 0x017,         // 刷新
    //SV_CLICK = 0x018,         // 单击
    SV_SORT = 0x019,            // 排序
    //SV_COLLAPSE = 0x01A,      // 
    SV_COPY = 0x01B,            // 拷贝
    SV_PAST = 0x01C,            // 粘贴
    SV_TEST = 0x01D             // 测试
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 权限定义
enum SiteView_ECC_Purview
{
    Add_Group       = 0x2,          // 添加组
    Add_Device      = 0x3,          // 添加设备
    Add_Monitor     = 0x4,          // 添加监测器
    Edit_SVSE       = 0x10,         // 编辑SE
    Edit_Group      = 0x20,         // 编辑组
    Edit_Device     = 0x30,         // 编辑设备
    Edit_Monitor    = 0x40,         // 编辑监测器
    Delete_Group    = 0x200,        // 删除组
    Delete_Device   = 0x300,        // 删除设备
    Delete_Monitor  = 0x400,        // 删除监测器
    Refresh_Device  = 0x3000,       // 刷新设备
    Refresh_Monitor = 0x4000,       // 刷新监测器
    Test_Device     = 0x30000,      // 测试设备
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char SV_REFRESH_QUEUE[]            = "SiteView70_RefreshInfo_%s";  // 刷新队列头
static const char SV_CONFIG_TRACK[]             = "SiteView70-ConfigTrack_%s";  // 配置更改队列头
static const char SV_USER_OPERATE_LOG_TABLE[]   = "UserOperateLog";             // 操作日志
static const char sv_disable_end[]              = "DISABLE_END";                // 禁止/启用停止标志
// 数据类型
static const char svPassword[]                  = "password";                   // 密码
static const char svText[]                      = "text";                       // 文本
static const char svTextbox[]                   = "textbox";                    // 文本框
static const char svCheckBox[]                  = "checkbox";                   // 复选框
static const char svRadioBox[]                  = "radiobox";                   // 单选框
static const char svTextArea[]                  = "textarea";                   // 复文本框
static const char svComboBox[]                  = "combobox";                   // 下拉列表框
static const char svListBox[]                   = "listbox";                    // 列表框
static const char svTree[]                      = "tree";                       // 树形
static const char svButton[]                    = "button";                     // 按钮

static const char svType[]                      = "sv_type";                    // 数据类型
static const char svTip[]                       = "sv_tip";                     // 错误提示信息
static const char svSaveName[]                  = "sv_savename";                // 存储名称
static const char svAllowNull[]                 = "sv_allownull";               // 是否允许为空
static const char svHelpText[]                  = "sv_helptext";                // 帮助文本信息
static const char svStyle[]                     = "sv_style";                   // 样式表
static const char svRun[]                       = "sv_run";                     // 是否是主要参数（运行时参数）
static const char svDLL[]                       = "sv_dll";                     // 动态链接库
static const char svFunc[]                      = "sv_func";                    // 函数
static const char svValue[]                     = "sv_value";                   // 数据
static const char svFollow[]                    = "sv_follow";                  // 跟随
static const char svHidden[]                    = "sv_hidden";                  // 是否隐藏
static const char svAccountWith[]               = "sv_accountwith";             // 根据**计算
static const char svIsNumeric[]                 = "sv_isnumeric";               // 是否是数字
static const char svItemCount[]                 = "sv_itemcount";               // 项目总数
static const char svReadOnly[]                  = "sv_isreadonly";              // 是否只读
static const char svExpressions[]               = "sv_expressions";             // 计算式
static const char svNoSort[]                    = "sv_nosort";                  // 是否不排序
static const char svMax[]                       = "sv_max";                     // 最大值
static const char svMin[]                       = "sv_min";                     // 最小值
static const char svSynTitle[]                  = "sv_syntitle";                // 动态标题
static const char svName[]                      = "sv_name";                    // 名称
static const char svLabel[]                     = "sv_label";                   // 标签
static const char svOSType[]                    = "_OsType";                    // 系统类型
static const char svDeviceType[]                = "sv_devicetype";              // 设备类型
static const char svDependCondition[]           = "sv_dependscondition";        // 依靠条件
static const char svDependON[]                  = "sv_dependson";               // 依靠于
static const char svShowIndex[]                 = "sv_index";                   // 显示索引
static const char svDescription[]               = "sv_description";             // 描述
static const char svNetworkSet[]                = "sv_network";                 // 是否是网络设备
static const char svItemLable[]                 = "sv_itemlabel%d";             // 项目标签
static const char svItemValue[]                 = "sv_itemvalue%d";             // 项目数据
static const char svDisable[]                   = "sv_disable";                 // 是否禁止（true, false, time）
static const char svStartTime[]                 = "sv_starttime";               // 开始时间
static const char svEndTime[]                   = "sv_endtime";                 // 结束时间
static const char svQuickAdd[]                  = "sv_quickadd";                // 快速添加监测器列表
static const char svQuickAddSel[]               = "sv_quickaddsel";             // 快速添加缺省选择
static const char svConditionCount[]            = "sv_conditioncount";          // 报警条件匹配式总数
static const char svParamValue[]                = "sv_paramvalue%d";            // 参数值
static const char svParamName[]                 = "sv_paramname%d";             // 参数名
static const char svOperate[]                   = "sv_operate%d";               // 操作
static const char svRelation[]                  = "sv_relation%d";              // 连接符
static const char svUnit[]                      = "sv_unit";                    // 单位
static const char svExpression[]                = "sv_expression";              // 
static const char svReportDesc[]                = "sv_reportdesc";              // 报告描述
static const char svPlan[]                      = "sv_plan";                    // 任务计划
static const char svCheckErr[]                  = "sv_checkerr";                // 校验错误
static const char svErrFreqSave[]               = "sv_errfreqsave";             // 错误时监测频率存储
static const char svErrFreq[]                   = "sv_errfreq";                 // 错误时监测频率
static const char svErrFreqUnit[]               = "sv_errfrequint";             // 错误监测频率单位
static const char svMonitorType[]               = "sv_monitortype";             // 监测器类型
static const char svIntPos[]                    = "sv_intpos";                  // 监测器占用点数
static const char svExtraDll[]                  = "sv_extradll";                // 扩展动态链接库
static const char svExtraSave[]                 = "sv_extrasave";               // 动态参数扩展存储为
static const char svExtraFunc[]                 = "sv_extrafunc";               // 扩展函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char chLeftBracket                 = '[';                          // 左括弧
static const char chRightBracket                = ']';                          // 右括弧

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int  svBufferSize                  = 1024 * 50;                    // 最大缓冲区大小
static const int  svMax_Size                    = 256;                          // 最大值

static const string sv_refresh_end_sign         = "Refresh_END";                // 刷新监测停止标志
static const string sv_disable_sign             = "DISABLE";                    // 监测器被禁止
#endif
