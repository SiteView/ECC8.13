/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件: addmonitor2nd.h
// 添加或者修改监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_MONITOR_H_
#define _SV_ADD_MONITOR_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WApplication"
class WImage;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../group/showtable.h"

#include "../group/paramitem.h"
#include "../group/returnitem.h"

#include "conditionparam.h"

#include "../userright/user.h"
#include "../group/basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVMonitor : public WTable
{
    //MOC: W_OBJECT SVMonitor:WTable
    W_OBJECT;
public:
    friend class SVGroupview;
    SVMonitor(WContainerWidget * parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", 
        string szPwd = "localhost", int nMonitorID = -1);

    void showMonitorParam(int &nMTID, WApplication * szApp);                    // 显示监测器 参数                  

    void SetUserPwd(string &szUser, string &szPwd);                             // 设置IDC用户 密码

private slots:
    //MOC: SLOT SVMonitor::showHelpText()
    void showHelpText();                                                        // 显示/隐藏帮助
    //MOC: SLOT SVMonitor::Translate()
    void Translate();									                        // 翻译
    //MOC: SLOT SVMonitor::ExChange()
    void ExChange();                                                            // 刷新
private:
    int m_nMonitorID;                                                           // 监测器模板的索引
    string m_szMonitorName;                                                     // 监测器模版的显示名称
    string m_szHostName;                                                        // 主机名称

    bool   m_bContinueAdd;
    bool   m_bError;
    OBJECT m_objTemplate;                                                       // 监测器模板类

    list<SVParamItem*> m_lsDyn;

    typedef map<string, SVParamItem* , less<string> >::iterator mapitem;
    typedef list<SVParamItem*>::iterator listItem;
    list<SVParamItem*> m_lsBaseParam;                                           // 基础数据
    list<SVParamItem*> m_lsAdvParam;                                            // 高级

    list<SVReturnItem*> m_lsReturn;                                             // 返回值 list

    SVShowTable        * m_pGeneral;                                            // 基础选项
    SVShowTable        * m_pAdv;                                                // 高级选项
    SVShowTable        * m_pCondition;                                          // 条件

    bool m_bShowHelp;                                                           // 显示/隐藏帮助
private: // fuction
    void initForm();                                                            // 初始化页面

    void createTitle();                                                         // 标题
    void createHelp();                                                          // 帮助按钮
    void createAdvParam();                                                      // 创建高级选项
    void createBaseAdv(WTable * pTable);                                        // 创建高级参数中的基础数据

    void createDeviceName(WTable * pTable);                                     // 设备名称
    void createMonitorName(WTable * pTable);                                    // 监测器名称
    void createBaseParam();                                                     // 基础选项 
    void createConditionParam();                                                // 条件
    void createOperate();                                                       // 操作

    void enumBaseParam();                                                       // 枚举基础选项
    void enumAdvParam();                                                        // 枚举高级选项
    void enumReturnParam();                                                     // 枚举返回值

    void clearData();                                                           // 清理数据

    void SetBaseAdvParam(MAPNODE &mainnode);
    void SetBaseParam(OBJECT &objMonitor);                                      // 设置基础数据
    void SetAdvParam(OBJECT &objMonitor);                                       // 设置高级数据
    void SetConditionParam(OBJECT &objMonitor);                                 // 设置报警条件

    void clearBaseParam();                                                      // 清理基础数据
    void clearAdvParam();                                                       // 清理高级选项
    void clearConditionParam();                                                 // 清理报警条件
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct BASE_ADV_PARAM
    {
        BASE_ADV_PARAM()
        {
            m_pDescription = NULL;                   // 监测器描述
            m_pReportDesc = NULL;                    // 报告描述
            m_pPlan = NULL;                          // 任务计划
            m_pCheckErr = NULL;                      // 校验错误
            m_pMonitorFreq = NULL;                   // 错误时监测频率
            m_pTimeUnit = NULL;                      // 时间单位
        }
        WTextArea * m_pDescription;                   // 监测器描述
        WTextArea * m_pReportDesc;                    // 报告描述
        WComboBox * m_pPlan;                          // 任务计划
        WCheckBox * m_pCheckErr;                      // 校验错误
        WLineEdit * m_pMonitorFreq;                   // 错误时监测频率
        WComboBox * m_pTimeUnit;                      // 时间单位
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //BASE_ADV_SHOW_TEXT m_ShowText;
    BASE_ADV_PARAM     m_AdvList;
    //TIME_UNIT          m_timeunit;

    map<WText*, string , less<WText*> > m_HelpMap;              
    map<WText*, string , less<WText*> >::iterator m_helpItem;
    WText         *    m_pDeviceName;                           // 设备名称
    WLineEdit     *    m_pMonitorName;                          // 监测器名称

    WText         *    m_pMonitorHelp;                          // 监测器名称标题
    WText         *    m_pTitle;                                // 标题控件
    WText         *    m_pFreqHelp;

    SVConditionParam * m_pErrCond;                              // 错误条件
    SVConditionParam * m_pWarnCond;                             // 警告条件
    SVConditionParam * m_pGoodCond;                             // 正常条件

    WTable           * m_pContentTable;
    WTable           * m_pSubContent;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string         m_szIDCUser;
    string         m_szIDCPwd;
    CUser        * m_pSVUser;
    
	//翻译
	WPushButton * m_pTranslateBtn;
	WApplication * m_pAppSelf;	
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
