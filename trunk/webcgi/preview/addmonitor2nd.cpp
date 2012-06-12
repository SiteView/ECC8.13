
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
#include "../group/resstring.h"
//#include "../base/OperateLog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVMonitor::SVMonitor(WContainerWidget *parent, CUser *pUser, string szIDCUser, string szIDCPwd, int nMonitorID):
WTable(parent)
{
    m_bShowHelp = false;                    // 显示/隐藏帮助信息
    m_pGeneral = NULL;                      // 标准属性参数
    m_pAdv = NULL;                          // 高级属性
    m_pCondition = NULL;                    // 
    m_pContentTable = NULL;                 // 阀值表
    m_pSubContent = NULL;                   // 子内容表
    m_nMonitorID = 0;                       // 监测器模板 ID

    m_pErrCond = NULL;                      // 错误
    m_pWarnCond = NULL;                     // 警告
    m_pGoodCond = NULL;                     // 正常

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pSVUser = pUser;

    //loadStrings();
    setStyleClass("t1");
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
            pScrollArea->setStyleClass("t1"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t1"); 
        elementAt(nRow, 0)->setStyleClass("t1");
        elementAt(nRow,0)->setContentAlignment(AlignTop);

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
    pTable->elementAt(0, 0)->setStyleClass("cell_10");
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
 		//刷新看效果
		WPushButton * pRefresh = new WPushButton(SVResString::getResString("IDS_Refresh"), (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));	
		if(pRefresh)
		{
	        WObject::connect(pRefresh, SIGNAL(clicked()), this, SLOT(ExChange()));	
		    pRefresh->setToolTip(SVResString::getResString("IDS_Refresh_Tip"));
		}

		new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));

		// 创建翻译按钮
	    m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
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
        WObject::connect(pHelp, SIGNAL(clicked()), this, SLOT(showHelpText()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ExChange
// 说明 刷新看效果
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::ExChange()
{
	char buf[256] = {"0"};
	itoa(m_nMonitorID,buf,10);
	string pMonitorID = buf; 

	WebSession::js_af_up  = "setTimeout(\"location.href ='/fcgi-bin/preview.exe?type=1&preview=";
	WebSession::js_af_up += pMonitorID;
	WebSession::js_af_up += "'\",1250);  ";
	m_pAppSelf->quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Translate
// 说明 翻译
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::Translate()
{
    string pTranPath = "DeviceMonitorTemplate$monitorid=";
	char buf[256] = {"0"};
	itoa(m_nMonitorID,buf,10);
	pTranPath += buf; 
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += pTranPath;
	WebSession::js_af_up += "')";
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
void SVMonitor::showMonitorParam(int &nMTID, WApplication * szApp)
{    
    m_bContinueAdd = false;

    m_nMonitorID = nMTID;
	m_pAppSelf = szApp;

    clearData();

    m_objTemplate = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(m_objTemplate != INVALID_VALUE)
    {
        MAPNODE objNode = GetMTMainAttribNode(m_objTemplate);
        if(objNode != INVALID_VALUE)
        {
            if(FindNodeValue(objNode, "sv_label", m_szMonitorName))
                m_szMonitorName = SVResString::getResString(m_szMonitorName.c_str());

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
    m_szHostName = "127.0.0.1";
    if(m_pDeviceName)
        m_pDeviceName->setText(m_szHostName);

    if(m_pMonitorName)
        m_pMonitorName->setText(m_szMonitorName );// + ":" + szHost);
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
// end file
