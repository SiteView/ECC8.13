
#include "addmonitor2nd.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WRadioButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

extern void PrintDebugString(const char * szMsg);
extern void PrintDebugString(const string &szMsg);

extern void AddTaskList(WComboBox * pTask = 0);
extern bool SV_IsNumeric(string &szValue);

#include "../base/basetype.h"
#include "../../base/des.h"
#include "resstring.h"
//#include "../base/OperateLog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVMonitor::SVMonitor(WContainerWidget *parent, CUser *pUser, string szIDCUser, string szIDCPwd, int nMonitorID):
WTable(parent)
{
    m_bHasDynamic = false;                  // 是否使用动态数据
    m_bShowHelp = false;                    // 显示/隐藏帮助信息
    m_pGeneral = NULL;                      // 标准属性参数
    m_pAdv = NULL;                          // 高级属性
    m_pCondition = NULL;                    // 
    m_pContentTable = NULL;                 // 阀值表
    m_pSubContent = NULL;                   // 子内容表
    m_nMonitorID = 0;                       // 监测器模板 ID

    m_pSave = NULL;                         // 保存按钮
    m_pBack = NULL;                         // 返回
    m_pContinue = NULL;                     // 添加并继续
    m_pBatchAdd = NULL;                     // 批量添加
    m_pSetAlert = NULL;                     // 设置为默认阀值
    m_pCancel = NULL;                       // 取消

    m_szEditMonitorID = "";                 // 正在编辑的设备
    m_pErrCond = NULL;                      // 错误
    m_pWarnCond = NULL;                     // 警告
    m_pGoodCond = NULL;                     // 正常

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pSVUser = pUser;

    //loadStrings();
    setStyleClass("t5");
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createAdvParam
// 说明 创建高级属性表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createAdvParam()
{
    list<SVParamItem*>::iterator lstItem;
    int nRow = m_pSubContent->numRows();
    if(m_pAdv == NULL)
    {
        // 创建新表
        m_pAdv = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    }
    if(m_pAdv)
    {
        // 设置标题 （高级参数）
        m_pAdv->setTitle(SVResString::getResString("IDS_Advance_Option").c_str());

        // 创建子表
        WTable *pSub = m_pAdv->createSubTable();
        if(pSub)
        {// 创建子表成功
            listItem it;
            // 枚举每一条属性
            for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
            {
                // 是否有跟随
                if((*it)->isHasFollow())
                {// 有跟随值
                    // 得到跟随值
                    string szFollow = (*it)->getFollow();
                    if(!szFollow.empty())
                    {
                        listItem ittmp;
                        // 枚举每条属性
                        for(ittmp = m_lsAdvParam.begin(); ittmp != m_lsAdvParam.end(); ittmp ++)
                        {
                            // 是否是跟随值
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                // 设置跟随值
                                (*it)->setFollowItem(*ittmp);
                                break;
                            }
                        }
                    }
                }
                // 创建控件
                (*it)->CreateControl(pSub);
                // 是否使用动态数据
                if((*it)->isDynamic())
                {
                    m_lsDyn.push_back((*it));
                    m_bHasDynamic = true;
                }
            }
            // 创建高级参数的几个基础属性参数
            createBaseAdv(pSub);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createBaseParam
// 说明 创建基础属性参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createBaseParam()
{
    list<SVParamItem*>::iterator lstItem;    
    int nRow = m_pSubContent->numRows();
    if(m_pGeneral == NULL)
    {
        // 创建新表
        m_pGeneral = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    }
    if(m_pGeneral)
    {
        // 设置标题
        m_pGeneral->setTitle(SVResString::getResString("IDS_Basic_Option").c_str());
        // 创建子表
        WTable *pSub = m_pGeneral->createSubTable();
        if(pSub)
        {// 成功创建子表
            // 显示设备名称
            createDeviceName(pSub);
            listItem it;
            // 枚举每个属性参数
            for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
            {
                // 是否有跟随值
                if((*it)->isHasFollow())
                {// 有跟随值
                    // 得到跟随值
                    string szFollow = (*it)->getFollow();
                    if(!szFollow.empty())
                    {// 跟随值不为空
                        listItem ittmp ;
                        // 枚举每一条属性参数
                        for(ittmp = m_lsBaseParam.begin(); ittmp != m_lsBaseParam.end(); ittmp ++)
                        {
                            // 是否匹配
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                // 设置跟随值
                                (*it)->setFollowItem((*ittmp));
                                break;
                            }
                        }
                    }
                }
                // 创建控件
                (*it)->CreateControl(pSub);
                // 是否使用动态数据
                if((*it)->isDynamic())
                {
                    m_lsDyn.push_back((*it));
                    m_bHasDynamic = true;
                }
            }
            // 监测器名称
            createMonitorName(pSub);
        }        
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createConditionParam
// 说明 阀值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createConditionParam()
{ 
    // 打开监测器模板
    m_objTemplate = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(m_objTemplate != INVALID_VALUE)
    {// 成功
        // 得到子内容标的当前行数
        int nRow = m_pSubContent->numRows();
        if(m_pCondition == NULL)
        {
            // 创建新表
            m_pCondition = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
        }
        if(m_pCondition)
        {
            // 设置标题
            m_pCondition->setTitle(SVResString::getResString("IDS_Alert_Condition_Title").c_str());
            // 创建子表
            WTable * pSub = m_pCondition->createSubTable();
            if(pSub)
            {// 创建子表成功
                // 得到错误阀值节点
                MAPNODE	objError = GetMTErrorAlertCondition(m_objTemplate);
                // 当前函数
                nRow = pSub->numRows(); 
                if(objError != INVALID_VALUE)
                {// 
                    // 创建新的条件
                    if(m_pErrCond == NULL)
                        m_pErrCond = new SVConditionParam(pSub->elementAt(nRow, 0));
                    if(m_pErrCond)
                    {
                        m_pErrCond->SetReturnList(m_lsReturn);
                        m_pErrCond->SetMapNode(objError);
                    }
                }

                // 当前行数加 1
                nRow ++;
                // 警告阀值节点
                MAPNODE objAlert = GetMTWarningAlertCondition(m_objTemplate);
                if(objAlert != INVALID_VALUE)
                {
                    if(m_pWarnCond == NULL)
                        m_pWarnCond = new SVConditionParam(pSub->elementAt(nRow, 0));
                    if(m_pWarnCond)
                    {
                        m_pWarnCond->SetReturnList(m_lsReturn);
                        m_pWarnCond->SetMapNode(objAlert);
                    }
                }

                nRow ++;
                // 正常阀值节点
                MAPNODE	objGood = GetMTGoodAlertCondition(m_objTemplate);
                if(objGood != INVALID_VALUE)
                { 
                    if(m_pGoodCond == NULL)
                        m_pGoodCond = new SVConditionParam(pSub->elementAt(nRow, 0));
                    if(m_pGoodCond)
                    {
                        m_pGoodCond->SetReturnList(m_lsReturn);
                        m_pGoodCond->SetMapNode(objGood);
                    }
                }
            }
        }
        // 关闭监测器模板
        CloseMonitorTemplet(m_objTemplate);
    }   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 setDefaultAlert
// 说明 设置为默认报警阀值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::setDefaultAlert()
{
    //// 错误 警告 正常
    //string szErrCond (""), szWarnCond (""), szGoodCond ("");

    //// 如果错误阀值表存在则得到错误阀值
    //if()
    //    szErrCond = m_pErrCond->GetStringValue();

    //// 得到警告阀值
    //if(m_pWarnCond)
    //    szWarnCond = m_pWarnCond->GetStringValue();

    //// 得到正常阀值
    //if(m_pGoodCond)
    //    szGoodCond = m_pGoodCond->GetStringValue();

    bool bSucc = false;
    // 打开监测器模板
    m_objTemplate = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(m_objTemplate != INVALID_VALUE)
    {// 成功
        // 错误阀值节点
        MAPNODE	objError = GetMTErrorAlertCondition(m_objTemplate);
        if(objError != INVALID_VALUE && m_pErrCond)//!szErrCond.empty())
        {
            if(m_pErrCond->SaveCondition(objError))
            {
                //m_pErrCond->resetDefaultValue();
                // 报警阀值
                MAPNODE	objAlert = GetMTWarningAlertCondition(m_objTemplate);
                if(objAlert != INVALID_VALUE && m_pWarnCond)//!szWarnCond.empty())
                {
                    //if(AddNodeAttrib(objAlert, "sv_value", szWarnCond))
                    if(m_pWarnCond->SaveCondition(objAlert))
                    {
                        //m_pWarnCond->resetDefaultValue();
                        // 正常阀值
                        MAPNODE	objGood = GetMTGoodAlertCondition(m_objTemplate);
                        if(objGood != INVALID_VALUE && m_pGoodCond)//!szGoodCond.empty())
                        {
                            //if(AddNodeAttrib(objGood, "sv_value", szGoodCond))
                            if(m_pGoodCond->SaveCondition(objGood))
                            {
                                //m_pGoodCond->resetDefaultValue();
                                bSucc = true;
                            }
                        }
                    }
                }
            }
        }
        // 提交
        SubmitMonitorTemplet(m_objTemplate, m_szIDCUser, m_szIDCPwd);
        CloseMonitorTemplet(m_objTemplate);  
    }

    if(bSucc)
        WebSession::js_af_up = "hiddenbar();showAlertMsg('" + SVResString::getResString("IDS_SetAlertConditionSuccess")
            + "','" + SVResString::getResString("IDS_Affirm") + "');";
    else
        WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createTitle
// 说明 创建主标题
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createTitle()
{
    // 得到当前行数
    int nRow = numRows();
    // 主标题
    m_pTitle = new WText(SVResString::getResString("IDS_Add_Title"), (WContainerWidget*)elementAt(nRow, 0));
    // 设置当前行显示样式
    elementAt(nRow, 0)->setStyleClass("t1title");

    // 行数递增1
    nRow ++;
    // 创建内容表
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // 设置单元格的Padding && Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);
        
        // 创建滚动区
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t5"); 
        elementAt(nRow, 0)->setStyleClass("t7");
        
        // 创建子内容表
        nRow = m_pContentTable->numRows();
        m_pSubContent = new WTable(m_pContentTable->elementAt(nRow,0));
        m_pContentTable->elementAt(nRow,0)->setContentAlignment(AlignTop);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumAdvParam
// 说明 枚举高级属性参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumAdvParam()
{
    LISTITEM lsItem;
    // 得到高级属性参数第一个节点
    if( FindMTAdvanceParameterFirst(m_objTemplate, lsItem))
    {
        // 枚举每个节点
        MAPNODE objNode;
        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
        {
            SVParamItem *param = new SVParamItem(objNode);
            m_lsAdvParam.push_back(param);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createDeviceName
// 说明 显示设备名称
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createDeviceName(WTable  * pTable)
{
    // 得到此表的当前行
    int nRow = pTable->numRows();
    // 前置说明
    new WText(SVResString::getResString("IDS_Device_Name"), (WContainerWidget*)pTable->elementAt(0, 0));
    // 设备名称
    m_pDeviceName = new WText("127.0.0.1", (WContainerWidget*)pTable->elementAt(0, 1));
    // 设置样式
    if(m_pDeviceName)
        m_pDeviceName->setStyleClass("readonly");

    // 折行
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(0, 1));
    // 创建设备名称帮助文本
    WText * pDeviceHelp = new WText(SVResString::getResString("IDS_Device_Name_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pDeviceHelp)
    {
        pDeviceHelp->hide();
        pDeviceHelp->setStyleClass("helps");
        m_HelpMap[pDeviceHelp] = SVResString::getResString("IDS_Device_Name_Help");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createMonitorName
// 说明 监测器名称
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createMonitorName(WTable  * pTable)
{
    int nRow = pTable->numRows();

    // 监测器名称标题（必填项）
    new WText(SVResString::getResString("IDS_Monitor_Label"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

    // 监测器名称
    m_pMonitorName = new WLineEdit("", (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_pMonitorName)
        m_pMonitorName->setStyleClass("cell_40");

    // 折行
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    // 监测器名称帮助
    m_pMonitorHelp = new WText(SVResString::getResString("IDS_Monitor_Label_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_pMonitorHelp)
    {
        m_pMonitorHelp->hide();
        m_pMonitorHelp->setStyleClass("helps");
        m_HelpMap[m_pMonitorHelp] = SVResString::getResString("IDS_Monitor_Label_Help");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumBaseParam
// 说明 枚举标准属性
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumBaseParam()
{
    LISTITEM lsItem;
    // 得到第一个标准属性参数
    if( FindMTParameterFirst(m_objTemplate, lsItem))
    {
        MAPNODE objNode;
        // 枚举每个属性
        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
        {
            SVParamItem *param = new SVParamItem(objNode);
            m_lsBaseParam.push_back(param);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumReturnParam
// 说明 枚举返回值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumReturnParam()
{
    LISTITEM lsItem;
    // 枚举每一条返回值
    if( FindMTReturnFirst(m_objTemplate, lsItem))
    {
        MAPNODE objNode;
        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
        {
            SVReturnItem *reItem = new SVReturnItem(objNode);
            m_lsReturn.push_back(reItem);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createHelp
// 说明 创建帮助按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createHelp()
{
    // 子内容表当前行
    int nRow = m_pSubContent->numRows();
    // 加载 js 文件
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));

    nRow ++;
	// 是否显示为翻译版本
    int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
        // 创建翻译按钮
	    m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)elementAt(nRow, 0));
	    if(m_pTranslateBtn)
	    {
            // 绑定 click
		    connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
            // tooltip
		    m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
        }
	    new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	}

    // 帮助按钮（图片按钮）
    WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    // 当前单元格对齐方式 右上
    m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
    if(pHelp)
    {
        // 设置样式
        pHelp->setStyleClass("imgbutton");
        // tooltip
        pHelp->setToolTip(SVResString::getResString("IDS_Help"));
        // 绑定 click
        WObject::connect(pHelp, SIGNAL(clicked()), "showbar();", this, SLOT(showHelpText()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Translate
// 说明 显示翻译界面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::Translate()
{
	WebSession::js_af_up = "showTranslate('groupRes')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createOperate
// 说明 创建操作按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createOperate()
{
    // 当前行
    int nRow = numRows();

    // 返回监测器列表按钮
    m_pBack = new WPushButton(SVResString::getResString("IDS_Back_One_Step"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pBack)
    {
        m_pBack->setToolTip(SVResString::getResString("IDS_Back_Monitor_List_Tip"));
        WObject::connect(m_pBack, SIGNAL(clicked()), "showbar();", this, SLOT(Preview()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    // 与上一个按钮隔开一定距离
    new WText("&nbsp;", elementAt(nRow,0));
    // 保存按钮
    m_pSave = new WPushButton(SVResString::getResString("IDS_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pSave)
    {
        m_pSave->setToolTip(SVResString::getResString("IDS_Add_Monitor_Tip"));
        WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(SaveMonitor()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    new WText("&nbsp;", elementAt(nRow, 0));
    // 取消按钮
    m_pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pCancel)
    {
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Current_Edit_Tip"));
        WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    new WText("&nbsp;", elementAt(nRow, 0));
    // 批量添加
    m_pBatchAdd = new WPushButton(SVResString::getResString("IDS_Batch_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pBatchAdd)
    {
        m_pBatchAdd->setToolTip(SVResString::getResString("IDS_Batch_Add_Tip"));
        WObject::connect(m_pBatchAdd, SIGNAL(clicked()), "showbar();", this, SLOT(BatchAddMonitor()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    new WText("&nbsp;", elementAt(nRow, 0));
    // 添加并继续
    m_pContinue = new WPushButton(SVResString::getResString("IDS_Continue_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pContinue)
    {
        m_pContinue->setToolTip(SVResString::getResString("IDS_Continue_Add_Tip"));
        WObject::connect(m_pContinue, SIGNAL(clicked()), "showbar();", this, SLOT(ContinueAdd()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    new WText("&nbsp;", elementAt(nRow, 0));
    // 设置默认报警条件
    m_pSetAlert = new WPushButton(SVResString::getResString("IDS_Set_Default_Alert"), elementAt(nRow, 0));
    if(m_pSetAlert)
    {
        m_pSetAlert->setToolTip(SVResString::getResString("IDS_Set_Default_Alert_Tip"));
        WObject::connect(m_pSetAlert, SIGNAL(clicked()), "showbar();", this, SLOT(setDefaultAlert()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    // 枚举动态数据
    m_pListDynBtn = new WPushButton("list dyn", (WContainerWidget*)elementAt(nRow, 0));
    if(m_pListDynBtn)
    {
        m_pListDynBtn->hide();
        WObject::connect(m_pListDynBtn, SIGNAL(clicked()),"showbar();",  this, SLOT(listDynParam()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    // 对齐方式（底部居中）
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    elementAt(nRow, 0)->setStyleClass("t3");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createBaseAdv
// 说明 创建高级参数中的几个基础属性参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createBaseAdv(WTable *pTable)
{
    int nRow = pTable->numRows();

    // 校验错误
    new WText(SVResString::getResString("IDS_Check_Error"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // 是否校验错误
    m_AdvList.m_pCheckErr = new WCheckBox("", (WContainerWidget*)pTable->elementAt(nRow, 1));
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    // 是否校验错误帮助
    WText * pCheckErrHelp = new WText(SVResString::getResString("IDS_Check_Err_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pCheckErrHelp)
    {
        pCheckErrHelp->hide();
        pCheckErrHelp->setStyleClass("helps");
        m_HelpMap[pCheckErrHelp] = SVResString::getResString("IDS_Check_Err_Help");
    }
    nRow += 1;

    // 错误频率
    new WText(SVResString::getResString("IDS_Error_Freq"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // 校验错误频率
    m_AdvList.m_pMonitorFreq = new WLineEdit((WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pMonitorFreq)
        m_AdvList.m_pMonitorFreq->setStyleClass("cell_10");
    // 校验错误频率时间单位
    m_AdvList.m_pTimeUnit = new WComboBox((WContainerWidget*)pTable->elementAt(nRow, 1));    
    if(m_AdvList.m_pTimeUnit)
    {
        m_AdvList.m_pTimeUnit->addItem(SVResString::getResString("IDS_Minute"));
        m_AdvList.m_pTimeUnit->addItem(SVResString::getResString("IDS_Hour"));
    }
    // 错误监测频率帮助
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    m_pFreqHelp = new WText(SVResString::getResString("IDS_Error_Freq_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_pFreqHelp)
    {
        m_pFreqHelp->hide();
        m_pFreqHelp->setStyleClass("helps");
        m_HelpMap[m_pFreqHelp] = SVResString::getResString("IDS_Error_Freq_Help");
    }
    nRow += 1;

    // 任务计划
    new WText(SVResString::getResString("IDS_Plan"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // 任务计划
    m_AdvList.m_pPlan = new WComboBox((WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pPlan)
    {
        m_AdvList.m_pPlan->setStyleClass("cell_40");
        AddTaskList(m_AdvList.m_pPlan);
    }
    // 任务计划帮助
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    WText * pPlanHelp = new WText(SVResString::getResString("IDS_PlanHelp"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pPlanHelp)
    {
        pPlanHelp->hide();
        pPlanHelp->setStyleClass("helps");
        m_HelpMap[pPlanHelp] = SVResString::getResString("IDS_PlanHelp");
    }
    nRow += 1;

    // 描述
    new WText(SVResString::getResString("IDS_Monitor_Desc"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // 描述信息
    m_AdvList.m_pDescription = new WTextArea("",(WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pDescription )
        m_AdvList.m_pDescription->setStyleClass("cell_98");

    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    // 描述信息帮助
    WText *pDescHelp = new WText(SVResString::getResString("IDS_Monitor_Desc_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pDescHelp)
    {
        pDescHelp->hide();
        pDescHelp->setStyleClass("helps");
        m_HelpMap[pDescHelp] = SVResString::getResString("IDS_Monitor_Desc_Help");
    }
    nRow += 1;

    // 报告描述文本
    new WText(SVResString::getResString("IDS_Report_Desc"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // 报告描述
    m_AdvList.m_pReportDesc = new WTextArea("",(WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pReportDesc)
        m_AdvList.m_pReportDesc->setStyleClass("cell_98");
    // 报告描述帮助
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    WText * pReportHelp = new WText(SVResString::getResString("IDS_Report_Desc_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pReportHelp)
    {
        pReportHelp->hide();
        pReportHelp->setStyleClass("helps");
        m_HelpMap[pReportHelp] = SVResString::getResString("IDS_Report_Desc_Help");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initForm
// 说明 初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::initForm()
{
    // 创建标题
    createTitle();
    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        // 创建帮助
        createHelp();
    }
    // 创建操作按钮
    createOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showHelpText
// 说明 显示/隐藏帮助信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::showHelpText()
{
    m_bShowHelp = !m_bShowHelp;

    list<SVParamItem *>::iterator lstItem;

    //mapitem it;
    listItem it;
    // 枚举每条基础属性参数
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
    {
        (*it)->m_bError = false;
        (*it)->showHelp(m_bShowHelp);
    }

    // 枚举高级属性参数
    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
    {
        (*it)->m_bError = false;
        (*it)->showHelp(m_bShowHelp);
    }

    // 错误阀值帮助
    if(m_pErrCond)
        m_pErrCond->showHelp(m_bShowHelp);

    // 警告阀值帮助
    if(m_pWarnCond)
        m_pWarnCond->showHelp(m_bShowHelp);

    // 正常阀值帮助
    if(m_pGoodCond)
        m_pGoodCond->showHelp(m_bShowHelp);

    if(m_bShowHelp)
    {
        // 显示每条帮助
        for(m_helpItem = m_HelpMap.begin(); m_helpItem != m_HelpMap.end(); m_helpItem ++)
        {
            (*(m_helpItem->first)).show();
            (*(m_helpItem->first)).setText(m_helpItem->second);
        }
    }
    else
    {
        // 隐藏帮助
        for(m_helpItem = m_HelpMap.begin(); m_helpItem != m_HelpMap.end(); m_helpItem ++)
            (*(m_helpItem->first)).hide();
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Preview
// 说明 返回到脚测器模板列表 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::Preview()
{
    emit BackPreview();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 checkAdvParam
// 说明 校验高级属性参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::checkAdvParam()
{
    listItem it;
    // 枚举每条属性
    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
    {
        // 校验数据
        if(!(*it)->checkValue())
        {// 发生错误
            if(m_pAdv)
                m_pAdv->ShowSubTable();
            m_bError = true;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 checkBaseParam
// 说明 校验基本属性参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::checkBaseParam()
{
    listItem it;
    // 枚举每条属性
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
    {
        // 校验数据
        if(!(*it)->checkValue())
        {// 发生错误
            if(m_pGeneral)
                m_pGeneral->ShowSubTable();
            m_bError = true;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 checkConditionParam
// 说明 校验阀值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::checkConditionParam()
{
    // 打开监测器模板
    OBJECT objMonitor = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {// 打开模板
        MAPNODE alertnode;
        // 是否已发生错误
        if(!m_bError)
        {
            // 错误阀值节点
            alertnode = GetMonitorErrorAlertCondition(objMonitor);
            // 是否成功，成功后校验数据
            if(alertnode != INVALID_VALUE)
                m_bError = !m_pErrCond->checkCondition(alertnode);
            else
                m_bError = true;
        }
        else
        {// 发生错误
            // 校验错误阀值
            alertnode = GetMonitorErrorAlertCondition(objMonitor);
            if(alertnode != INVALID_VALUE)
                m_pErrCond->checkCondition(alertnode);
        }
        // 是否已发生错误
        if(!m_bError)
        {
            // 警告阀值节点
            alertnode = GetMonitorWarningAlertCondition(objMonitor);
            // 是否成功，成功后校验数据
            if(alertnode != INVALID_VALUE)
                m_bError = !m_pWarnCond->checkCondition(alertnode);
            else
                m_bError = true;
        }
        else
        {// 发生错误
            // 校验警告阀值
            alertnode = GetMonitorWarningAlertCondition(objMonitor);
            if(alertnode != INVALID_VALUE)
                m_pWarnCond->checkCondition(alertnode);
        }

        // 是否已发生错误
        if(!m_bError)
        {
            // 正常阀值节点
            alertnode = GetMonitorGoodAlertCondition(objMonitor);
            // 是否成功，成功后校验数据
            if(alertnode != INVALID_VALUE)
                m_bError = !m_pGoodCond->checkCondition(alertnode);
            else
                m_bError = true;
        }
        else
        {// 发生错误
            // 校验正常阀值
            alertnode = GetMonitorGoodAlertCondition(objMonitor);
            if(alertnode != INVALID_VALUE)
                m_pGoodCond->checkCondition(alertnode);
        }
        // 关闭监测器模板
        CloseMonitorTemplet(objMonitor);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveAdvParam
// 说明 保存高级属性参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVMonitor::saveAdvParam(OBJECT &objMonitor)
{
    bool bNoError = true;
    list<SVParamItem*>::iterator lstItem;

    // 高级参数节点
    MAPNODE advnode = GetMonitorAdvanceParameterNode(objMonitor);
    if(advnode != INVALID_VALUE)
    {
        listItem it;
        // 枚举每条属性参数
        for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
        {
            // 名称 值 保存名称
            string szName (""), szValue (""), szSavename ("");
            (*it)->getName(szName);
            (*it)->getStringValue(szValue);
            szSavename = (*it)->getSaveName();
            
            // 计算属性 计算公式 计算使用的数据
            string szAccount (""), szExpress (""), szAccValue ("");
            char szAfterAcc[32] = {0};

            szAccount = (*it)->getAccount();
            if(!szAccount.empty())
            {// 需要计算
                szExpress = (*it)->getExpress();

                listItem itTmp;
                // 枚举每条属性
                for(itTmp = m_lsAdvParam.begin(); itTmp != m_lsAdvParam.end(); itTmp ++)
                {
                    if(szAccount.compare((*itTmp)->getName()) == 0)
                    {
                       (*itTmp)->getStringValue(szAccValue);
                        break;
                    }
                }
                // 计算
                int nAccValue = 0;
                switch(szExpress.c_str()[0])
                {
                case '+':
                    nAccValue = atoi(szValue.c_str()) + atoi(szAccValue.c_str());
                    break;
                case '-':
                    nAccValue = atoi(szValue.c_str()) - atoi(szAccValue.c_str());
                    break;
                case '*':
                    nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    break;
                case '/':
                    if(atoi(szAccValue.c_str()) != 0)
                        nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    else
                        nAccValue = atoi(szValue.c_str()) ;
                    break;
                }
                // 保存结果
                sprintf(szAfterAcc, "%d", nAccValue);
                AddNodeAttrib(advnode, szName + "1", szValue);
            }
            if(strlen(szAfterAcc) > 0)
                szValue = szAfterAcc;

            if(!szSavename.empty())
            {
                szName = szSavename;
                if(!szValue.empty() && !AddNodeAttrib(advnode, szName, szValue))
                {
                    bNoError = false;
                    break;
                }
            }
            else if(!AddNodeAttrib(advnode, szName, szValue))
            {
                bNoError = false;
                break;
            }
        }
    }

    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveCondition
// 说明 保存阀值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVMonitor::saveCondition(OBJECT &objMonitor)
{   
    bool bNoError = true;
    
    // 保存错误阀值
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE)
        bNoError = m_pErrCond->SaveCondition(alertnode);
    else
        bNoError = false;

    // 保存错误阀值成功
    if(bNoError)
    {
        // 保存警告阀值
        alertnode = GetMonitorWarningAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE)
            bNoError = m_pWarnCond->SaveCondition(alertnode);
        else
            bNoError = false;
    }

    if(bNoError)
    {
        // 保存正常阀值
        alertnode = GetMonitorGoodAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE)
            bNoError = m_pGoodCond->SaveCondition(alertnode);
        else
            bNoError = false;
    }

    return bNoError;
}

bool SVMonitor::saveBaseAdvParam(MAPNODE &mainnode)
{
    string szDesc (""), szReportDesc ("");
    string szPlan (""), szCheckErr ("");
    string szErrFreq (""), szErrFreqUnit ("");

    if(m_AdvList.m_pDescription)
        szDesc = m_AdvList.m_pDescription->text();

    if(m_AdvList.m_pCheckErr)
    {
        if(m_AdvList.m_pCheckErr->isChecked())
            szCheckErr = "true";
        else
            szCheckErr = "false";
    }

    if(m_AdvList.m_pMonitorFreq)
        szErrFreq = m_AdvList.m_pMonitorFreq->text();

    if(m_AdvList.m_pTimeUnit)
        szErrFreqUnit = m_AdvList.m_pTimeUnit->currentText();
    if(szErrFreqUnit == SVResString::getResString("IDS_Hour"))
        szErrFreqUnit = "60";
    else
        szErrFreqUnit = "1";

    int nFreq = atoi(szErrFreq.c_str()) * atoi(szErrFreqUnit.c_str());

    char szFreq[32] = {0};
    sprintf(szFreq , "%d", nFreq);
    //string szErrFreq = szFreq;

    if(m_AdvList.m_pPlan)
        szPlan = m_AdvList.m_pPlan->currentText();

    if(m_AdvList.m_pReportDesc)
        szReportDesc = m_AdvList.m_pReportDesc->text();

    bool bNoError = false;

    if((bNoError = AddNodeAttrib(mainnode, "sv_description", szDesc)))
    {
        if((bNoError = AddNodeAttrib(mainnode, "sv_reportdesc", szReportDesc)))
        {
            if((bNoError = AddNodeAttrib(mainnode, "sv_plan", szPlan)))
            {
                if((bNoError = AddNodeAttrib(mainnode, "sv_checkerr", szCheckErr)))
                {
                    if((bNoError = AddNodeAttrib(mainnode, "sv_errfreq", szFreq)))
                    {
                        if((bNoError = AddNodeAttrib(mainnode, "sv_errfrequint", szErrFreqUnit)))
                            bNoError = AddNodeAttrib(mainnode, "sv_errfreqsave", szErrFreq);
                    }
                }
            }
        }
    }
    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVMonitor::saveBaseParam(OBJECT &objMonitor)
{
    bool bNoError = true;
    list<SVParamItem*>::iterator lstItem;

    MAPNODE basenode = GetMonitorParameter(objMonitor);
    if(basenode != INVALID_VALUE)
    {
        listItem it;
        for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
        {
            string szName (""), szValue (""), szSavename ("");
            (*it)->getName(szName);
            (*it)->getStringValue(szValue);
            szSavename = (*it)->getSaveName();
            string szAccount (""), szExpress (""), szAccValue ("");
            char szAfterAcc[32] = {0};

            szAccount = (*it)->getAccount();
            if(!szAccount.empty())
            {
                szExpress = (*it)->getExpress();

                listItem itTmp;

                for(itTmp = m_lsBaseParam.begin(); itTmp != m_lsBaseParam.end(); itTmp ++)
                {
                    if(szAccount.compare((*itTmp)->getName()) == 0)
                    {
                       (*itTmp)->getStringValue(szAccValue);
                        break;
                    }
                }
                int nAccValue = 0;
                switch(szExpress.c_str()[0])
                {
                case '+':
                    nAccValue = atoi(szValue.c_str()) + atoi(szAccValue.c_str());
                    break;
                case '-':
                    nAccValue = atoi(szValue.c_str()) - atoi(szAccValue.c_str());
                    break;
                case '*':
                    nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    break;
                case '/':
                    if(atoi(szAccValue.c_str()) != 0)
                        nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    else
                        nAccValue = atoi(szValue.c_str()) ;
                    break;
                }
                sprintf(szAfterAcc, "%d", nAccValue);
                AddNodeAttrib(basenode, szName + "1", szValue);
            }
            if(strlen(szAfterAcc) > 0)
                szValue = szAfterAcc;

            if(!szSavename.empty())
            {
                szName = szSavename;
                if(!szValue.empty() && !AddNodeAttrib(basenode, szName, szValue))
                {
                    bNoError = false;
                    break;
                }
            }
            else if(!AddNodeAttrib(basenode, szName, szValue))
            {
                bNoError = false;
                break;
            }
        }

        if(bNoError)
            bNoError = saveBaseAdvParam(basenode);
    }
    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::checkMonitorName()
{
    string szName ("");
    if(m_pMonitorName)           szName = m_pMonitorName->text();
    if(szName.empty())
    {
        m_bError = true;
        if(m_pMonitorHelp)
        {
            m_pMonitorHelp->setStyleClass("errors");
            m_pMonitorHelp->setText(SVResString::getResString("IDS_Monitor_Label_Error"));
            m_pMonitorHelp->show();
        }
        if(m_pGeneral)          
            m_pGeneral->show();
    } 
    else
    {
        if(m_pMonitorHelp) 
        {
            if(!m_bShowHelp)
                m_pMonitorHelp->hide();
            else
            {
                m_pMonitorHelp->setText(SVResString::getResString("IDS_Monitor_Label_Help"));
                m_pMonitorHelp->setStyleClass("helps");
                m_pMonitorHelp->show();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::checkMonitorFreq()
{
    string szValue ("");
    if(m_AdvList.m_pMonitorFreq)
        szValue = m_AdvList.m_pMonitorFreq->text();
    if(!szValue.empty())
    {
        if(!SV_IsNumeric(szValue))
        {
            if(m_pFreqHelp)
            {
                m_pFreqHelp->setStyleClass("errors");
                m_pFreqHelp->setText(SVResString::getResString("IDS_Numbic_Error"));
                m_pFreqHelp->show();
            }
            m_bError = true;
        }
        else
        {
            if(m_pFreqHelp)
            {
                if(m_bShowHelp)
                {
                    m_pFreqHelp->setStyleClass("helps");
                    m_pFreqHelp->setText(SVResString::getResString("IDS_Error_Freq_Help"));
                }
                else
                    m_pFreqHelp->hide();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SaveMonitor()
{
    string szName (""), szRealIndex ("");
    m_bError = false;
    checkMonitorName();
    checkBaseParam(); 
    checkAdvParam();
    checkMonitorFreq();
    checkConditionParam();

    if(m_bError)
    {
        WebSession::js_af_up = "hiddenbar();";
        return;
    }

    if(m_pMonitorName) 
		szName = m_pMonitorName->text();

    OBJECT objMonitor; 

    if(m_szEditMonitorID.empty()) 
    { 
        if(m_szNetworkset != "true")
        {
            int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);

            int nPoint = atoi(m_szPoint.c_str());
            if(nPoint <= 0)
                nPoint = 0;
            nMonitorCount += nPoint;

            if(!checkMonitorsPoint(nMonitorCount))
            {
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                return;
            }
        }
        else
        {

            int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd, m_szDeviceIndex); 

            if(!checkNetworkPoint(nNetworkCount))
            {
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                return;
            }
        }
        objMonitor = CreateMonitor();
    }
    else
        objMonitor = GetMonitor(m_szEditMonitorID, m_szIDCUser, m_szIDCPwd);

    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode;
        mainnode  = GetMonitorMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
            char chMTID [8] = {0};
            sprintf(chMTID, "%d", m_nMonitorID);
            if(m_szNetworkset == "true")
                m_szPoint = "0";
             if(AddNodeAttrib(mainnode, "sv_name", szName) && AddNodeAttrib(mainnode, "sv_intpos", m_szPoint))
            {
                if(AddNodeAttrib(mainnode,"sv_monitortype", chMTID))
                {
                    if(saveBaseParam(objMonitor) && saveAdvParam(objMonitor) && saveCondition(objMonitor))
                    {
                        if(m_szEditMonitorID.empty())
                        {
                            saveDisableByParent(mainnode, Tree_DEVICE, m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
                            szRealIndex = AddNewMonitor(objMonitor, m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
                            if(!szRealIndex.empty())
                            {
                                int nIndex = FindIndexByID(szRealIndex);
                                char szIndex[16] = {0};
                                sprintf(szIndex, "%d", nIndex);
                                AddNodeAttrib(mainnode, "sv_index", szIndex);
                                InsertTable(szRealIndex, m_nMonitorID, m_szIDCUser, m_szIDCPwd);
                                if(m_pSVUser && !m_pSVUser->isAdmin())
                                    m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_MONITOR);
                                emit AddMonitorSucc(szName, szRealIndex);
                           }
                        }
                        else
                        {// Submit
                            if(SubmitMonitor(objMonitor, m_szIDCUser, m_szIDCPwd)) 
								emit EditMonitorSucc(szName, m_szEditMonitorID);
                       }
                    }
                }
            }
        }
        CloseMonitor(objMonitor);
    }
    
    if(m_bContinueAdd)
    {
        Preview();
        m_bContinueAdd = false;
    }
    else if(m_szEditMonitorID.empty())
    {
        Cancel();
    }
    m_szEditMonitorID = "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearBaseParam()
{
    listItem it;
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
    {
        (*it)->resetState();
        if(!(*it)->isDynamic())
            (*it)->setDefaultValue();
        else
            (*it)->clearDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearAdvParam()
{
    listItem it;
    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
    {
        (*it)->resetState();
        if(!(*it)->isDynamic())
            (*it)->setDefaultValue();
        else
            (*it)->clearDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearConditionParam()
{
    OBJECT objMonitor = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE alertnode = GetMTErrorAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE && m_pErrCond)
            m_pErrCond->SetCondition(alertnode);

        alertnode = GetMTWarningAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE && m_pWarnCond)
            m_pWarnCond->SetCondition(alertnode);

        alertnode = GetMTGoodAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE && m_pGoodCond)
            m_pGoodCond->SetCondition(alertnode);

        CloseMonitorTemplet(objMonitor);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::showMonitorParam(int &nMTID, string &szDeviceIndex)
{    
    m_szEditMonitorID = "";
    m_bContinueAdd = false;
    if(m_pContinue && !m_szEditMonitorID.empty()) 
        m_pContinue->setEnabled(false);
    else
        m_pContinue->setEnabled(true); 
    if(m_nMonitorID == nMTID)
    {
        m_szDeviceIndex = szDeviceIndex;
        string szHost ("");
        getHostNameByID (m_szDeviceIndex, szHost);
        m_szHostName = szHost;
        if(m_pDeviceName)
            m_pDeviceName->setText(m_szHostName);

        if(m_pMonitorName)
            m_pMonitorName->setText(m_szMonitorName);

        clearBaseParam();
        clearAdvParam();
        clearConditionParam();
        m_bShowHelp = true;
        showHelpText();

        if(m_pTitle)
            m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + m_szMonitorName + SVResString::getResString("IDS_Monitor_Title"));

        if(m_pBack)
            m_pBack->show();

        if(m_pSave)
        {
            m_pSave->setText(SVResString::getResString("IDS_Add"));
            m_pSave->setToolTip(SVResString::getResString("IDS_Add_Monitor_Tip"));
        }
        return;
    }

    m_nMonitorID = nMTID;
    m_szPoint    = "1";
    m_bHasDynamic = false;    
    m_szDeviceIndex = szDeviceIndex;
    clearData();

    m_objTemplate = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(m_objTemplate != INVALID_VALUE)
    {
        MAPNODE objNode = GetMTMainAttribNode(m_objTemplate);
        if(objNode != INVALID_VALUE)
        {
            if(FindNodeValue(objNode, "sv_label", m_szMonitorName))
                m_szMonitorName = SVResString::getResString(m_szMonitorName.c_str());

            FindNodeValue(objNode, "sv_intpos", m_szPoint);
            if(m_szPoint.empty())
                m_szPoint = "1";
            m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + m_szMonitorName + SVResString::getResString("IDS_Monitor_Title"));
        }
        enumAdvParam();
        enumBaseParam();
        enumReturnParam();

        CloseMonitorTemplet(m_objTemplate);
    }
    if(m_pSubContent)
    {
        // 基础选项
        createBaseParam();
        // 条件（错误、警告、正常）
        createConditionParam();
        // 高级选项
        createAdvParam();
    }
    //if(sv)

    string szHost ("");
    getHostNameByID (m_szDeviceIndex, szHost);
    m_szHostName = szHost;
    if(m_pDeviceName)
        m_pDeviceName->setText(szHost);

    if(m_pMonitorName)
        m_pMonitorName->setText(m_szMonitorName );// + ":" + szHost);

    if(m_pBack)
        m_pBack->show();
    if(m_pSave)
    {
        m_pSave->setText(SVResString::getResString("IDS_Add"));
        m_pSave->setToolTip(SVResString::getResString("IDS_Add_Monitor_Tip"));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearData()
{
    list<SVParamItem*>::iterator lsItem;


    listItem it;
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
        delete (*it);

    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
        delete (*it);

    list<SVReturnItem*>::iterator lsReItem;
    for(lsReItem = m_lsReturn.begin(); lsReItem != m_lsReturn.end(); lsReItem ++)
        delete (*lsReItem);

    m_lsBaseParam.clear();
    m_lsAdvParam.clear();

    m_lsReturn.clear();
    m_lsDyn.clear();

    if(m_pGeneral)
        m_pGeneral->createSubTable()->clear();
    if(m_pAdv)
        m_pAdv->createSubTable()->clear();
    m_HelpMap.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::Cancel()
{
    m_szEditMonitorID = "";
    emit CancelAddMonitor();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetAdvParam(OBJECT &objMonitor)
{
    list<SVParamItem*>::iterator lstItem;
    MAPNODE basenode = GetMonitorAdvanceParameterNode(objMonitor);
    if(basenode != INVALID_VALUE)
    {
        listItem it;
        for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
        {
            string szValue (""), szName (""), szSaveName ("");;
            (*it)->getName(szName);
            szSaveName = (*it)->getSaveName();
            if(!szSaveName.empty())
                szName = szSaveName;
            if(!(*it)->getAccount().empty())
                szName += "1";
            FindNodeValue(basenode, szName, szValue);
            (*it)->setStringValue(szValue);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetBaseAdvParam(MAPNODE &mainnode)
{
    string szDesc (""), szReportDesc ("");
    string szPlan (""), szCheckErr ("");
    string szErrFreq (""), szErrFreqUnit ("");

    FindNodeValue(mainnode, "sv_description", szDesc);
    FindNodeValue(mainnode, "sv_reportdesc", szReportDesc);
    FindNodeValue(mainnode, "sv_plan", szPlan);
    FindNodeValue(mainnode, "sv_checkerr", szCheckErr);
    FindNodeValue(mainnode, "sv_errfreqsave", szErrFreq);
    FindNodeValue(mainnode, "sv_errfrequint", szErrFreqUnit);

    if(m_AdvList.m_pDescription)
        m_AdvList.m_pDescription->setText(szDesc);

    if(m_AdvList.m_pCheckErr)
    {
        if(szCheckErr == "true")
            m_AdvList.m_pCheckErr->setChecked(true);
        else
            m_AdvList.m_pCheckErr->setChecked(false);;
    }

    if(m_AdvList.m_pMonitorFreq)
        m_AdvList.m_pMonitorFreq->setText(szErrFreq);

    if(m_AdvList.m_pTimeUnit)
    {
        if(szErrFreqUnit == "1")
            m_AdvList.m_pTimeUnit->setCurrentIndexByStr(SVResString::getResString("IDS_Minute"));
        else
            m_AdvList.m_pTimeUnit->setCurrentIndexByStr(SVResString::getResString("IDS_Hour"));
    }

    if(m_AdvList.m_pPlan)
        m_AdvList.m_pPlan->setCurrentIndexByStr(szPlan);

    if(m_AdvList.m_pReportDesc)
        m_AdvList.m_pReportDesc->setText(szReportDesc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetBaseParam(OBJECT &objMonitor)
{
    list<SVParamItem*>::iterator lstItem;
    MAPNODE basenode = GetMonitorParameter(objMonitor);
    if(basenode != INVALID_VALUE)
    {
        listItem it;
        for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
        {
            string szValue (""), szName (""), szSaveName ("");;
            (*it)->getName(szName);
            
            szSaveName = (*it)->getSaveName();
            if(!szSaveName.empty())
            {
                szName = szSaveName;
            }

            if(!(*it)->getAccount().empty())
                szName += "1";

            FindNodeValue(basenode, szName, szValue);
             (*it)->setStringValue(szValue);
        }
        SetBaseAdvParam(basenode);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetConditionParam(OBJECT &objMonitor)
{
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE && m_pErrCond)
        m_pErrCond->SetCondition(alertnode);

    alertnode = GetMonitorWarningAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE && m_pWarnCond)
        m_pWarnCond->SetCondition(alertnode);

    alertnode = GetMonitorGoodAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE && m_pGoodCond)
        m_pGoodCond->SetCondition(alertnode);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::EditMonitorByID(string &szEditMonitorID)
{
    if(szEditMonitorID.empty())
        return;


    string szDeviceID = FindParentID(szEditMonitorID);
    OBJECT objMonitor = GetMonitor(szEditMonitorID, m_szIDCUser, m_szIDCPwd);

    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
            string szName (""); FindNodeValue(mainnode, "sv_name", szName);

            string szMTID (""); FindNodeValue(mainnode, "sv_monitortype", szMTID);
            if(!szMTID.empty())
            {
                int nMonitorID = 0;
                nMonitorID = atoi(szMTID.c_str());
                showMonitorParam(nMonitorID, szDeviceID);
                
                listDynParam();
                
                m_szEditMonitorID = szEditMonitorID; 
                m_pMonitorName->setText(szName);
                if(m_pContinue && !m_szEditMonitorID.empty()) 
                    m_pContinue->setEnabled(false);
                else
                    m_pContinue->setEnabled(true);
                if(m_pBatchAdd && !m_szEditMonitorID.empty())
                    m_pBatchAdd->setEnabled(false);
                else
                    m_pBatchAdd->setEnabled(true);

                SetBaseParam(objMonitor);
                SetAdvParam(objMonitor);
                SetConditionParam(objMonitor);

            } 
            if(m_pTitle)
                m_pTitle->setText(SVResString::getResString("IDS_Edit") + szName + SVResString::getResString("IDS_Add_Title"));
        }
        CloseMonitor(objMonitor);
    }  
    if(m_pBack)
        m_pBack->hide();
    if(m_pSave)
    {
        m_pSave->setText(SVResString::getResString("IDS_Save"));
        m_pSave->setToolTip(SVResString::getResString("IDS_Save_Tip"));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::getHostNameByID(string &szDeviceID, string & szHostName)
{
    m_szNetworkset = "false";
    OBJECT objDevice = GetEntity(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {            
            FindNodeValue(mainnode, "sv_name", szHostName);
            FindNodeValue(mainnode, "sv_network", m_szNetworkset);

            if(m_szNetworkset.empty())
                m_szNetworkset = "false";

            if(szHostName.empty())
                szHostName = "127.0.0.1";
        }
        else
        {
            szHostName = "127.0.0.1";
        }  
        CloseEntity(objDevice);
    }
    else
    {
        szHostName = "127.0.0.1";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::BatchAddMonitor()
{
    emit BatchAddNew();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::ContinueAdd()
{
    m_bContinueAdd = true;
    SaveMonitor();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumDeviceRunParam()
{
    m_szQuery = "";
    OBJECT objDevice = GetEntity(m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDeviceType ("");
            map<string, string, less<string> > lsDeviceParam;
            if(FindNodeValue(mainnode, "sv_devicetype", szDeviceType))
            {
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDeviceTmp, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName (""), szRun ("");
                            string szType ("");
                            FindNodeValue(objNode, "sv_name", szName);
                            FindNodeValue(objNode, "sv_run", szRun);
                            FindNodeValue(objNode, "sv_type", szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    CloseEntityTemplet(objDeviceTmp);
                }
            }
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue ("");
                FindNodeValue(mainnode, (lstItem->first), szValue);
                if((lstItem->second).compare(svPassword) == 0)
                {
                    char szOutput[512] = {0};
                    Des des;
                    if(des.Decrypt(szValue.c_str(), szOutput))
                        szValue = szOutput;
                }
                m_szQuery = m_szQuery + (lstItem->first) + "=" + szValue + "\v";
            }
        }
        CloseEntity(objDevice);
    }
    char szTpl[32] = {0};
    sprintf(szTpl, "_TemplateID=%d", m_nMonitorID);
    m_szQuery += szTpl;
    PrintDebugString(m_szQuery.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::listDynParam()
{
    enumDeviceRunParam();
    listItem it;
	
    for(it = m_lsDyn.begin(); it != m_lsDyn.end(); it ++)
        (*it)->enumDynValue(m_szQuery, m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::requesDynData()
{
    if(m_pListDynBtn)
    {
        string szCmd = m_pListDynBtn->getEncodeCmd("xclicked()");
        if(!szCmd.empty() && m_bHasDynamic)
            WebSession::js_af_up = "update('" + szCmd + "');";
        else
            WebSession::js_af_up = "hiddenbar();";

        if(m_bHasDynamic)
        {
            if(m_pBatchAdd && m_szEditMonitorID.empty()) 
                m_pBatchAdd->setEnabled(true);
            else
                m_pBatchAdd->setEnabled(false);       
        }
        else
        {
            if(m_pBatchAdd) m_pBatchAdd->setEnabled(false);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
