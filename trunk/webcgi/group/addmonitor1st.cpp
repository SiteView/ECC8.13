#include "addmonitor1st.h"

#include "../../opens/libwt/WScrollArea"

extern void PrintDebugString(const char *szMsg);

#include "resstring.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVMonitorList::SVMonitorList(WContainerWidget *parent, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szDeviceType = "";
    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pContentTable = NULL;
    m_pSubContent = NULL;
    m_pTitle = NULL;
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initForm
// 说明 初始化页面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::initForm()
{
    setStyleClass("t5");
    createTitle();
    if(m_pContentTable)
        createMonitorList();
    createOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 CancelAdd
// 说明 取消添加
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::CancelAdd()
{
    emit Cancel();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createTitle
// 说明 创建主标题
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::createTitle()
{
    // 得到当前行
    int nRow = numRows();
    // 主标题
    m_pTitle = new WText(SVResString::getResString("IDS_Add_Monitor_Title"), (WContainerWidget*)elementAt(nRow, 0));
    // 主标题显示样式
    elementAt(nRow, 0)->setStyleClass("t1title");
    nRow ++;
    // 内容表
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // 设置单元格Padding和Spaceing
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
    }
    elementAt(nRow, 0)->setStyleClass("t7");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createMonitorList
// 说明 创建监测器列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::createMonitorList()
{
    connect(&m_MonitorMap, SIGNAL(mapped(int)), this, SLOT(MonitorMTClicked(int)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumMonitorTempByType
// 说明 根据设备类型枚举此类型设备可使用的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::enumMonitorTempByType(string &szDeviceType, string &szDeviceID)
{ 
    if(m_szDeviceType == szDeviceType)
    {
        m_szDeviceID = szDeviceID;
        return;
    }
    removeMapping();
    m_pContentTable->clear();
    m_lsName.clear();
    m_szDeviceID = szDeviceID;
    m_szDeviceType = szDeviceType;
    enumMonitor(m_szDeviceType);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 removeMapping
// 说明 移除绑定
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::removeMapping()
{
    list<WText*>::iterator it;
    for(it = m_lsName.begin(); it != m_lsName.end(); it++ )
        m_MonitorMap.removeMappings((*it));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumMonitor
// 说明 根据设备类型枚举监测器模板
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::enumMonitor(string &szDeviceType)
{
    if(m_pContentTable)
    {
        // 得到内容表当前行
        int nRow = m_pContentTable->numRows();
        // 创建子表
        WTable * pSub = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // 内容表当前行对齐方式
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignCenter);
        // 子表样式表
        if(pSub) pSub->setStyleClass("t3");
        // 打开设备模板
        OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {// 成功
            list<int> lsMTID;
            list<int>::iterator lstItem;
            // 得到设备能使用的监测器模板列表
            if(GetSubMonitorTypeByET(objDevice, lsMTID))
            {
                // 枚举每个监测器模板
                for(lstItem = lsMTID.begin(); lstItem != lsMTID.end(); lstItem++)
                {
                    int nMTID = (*lstItem);
                    // 打开监测器模板
                    OBJECT objMonitor = GetMonitorTemplet(nMTID, m_szIDCUser, m_szIDCPwd);
                    if(objMonitor != INVALID_VALUE)
                    {// 成功
                        // 主节点
                        MAPNODE node = GetMTMainAttribNode(objMonitor);
                        if(node != INVALID_VALUE)
                        {
                            // 名称 显示 是否隐藏 描述
                            string szLabel(""), szHidden (""), szDesc ("");;
                            //FindNodeValue(node, "sv_name", szName);
                            if(FindNodeValue(node, "sv_label", szLabel))
                                szLabel = SVResString::getResString(szLabel.c_str());
                            
                            if(FindNodeValue(node, "sv_description", szDesc))
                                szDesc = SVResString::getResString(szDesc.c_str());

                            FindNodeValue(node, "sv_hidden", szHidden);
                            if(szHidden != "true")
                            {// 不隐藏
                                if(pSub && !szLabel.empty())
                                {
                                    // 子表当前行
                                    nRow = pSub->numRows();
                                   
                                    // 监测器显示文字
                                    WText *pName = new WText(szLabel, (WContainerWidget*)pSub->elementAt(nRow, 0));
                                    if(pName)
                                    {
                                        // 文字样式
                                        sprintf(pName->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                                            "this.style.textDecoration=\"underline\"' " \
                                            "onmouseout='this.style.textDecoration=\"none\"'");
                                        // 绑定 click
                                        connect(pName, SIGNAL(clicked()), "showbar();", &m_MonitorMap, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                                        m_MonitorMap.setMapping(pName, nMTID);
                                        pName->setToolTip(szLabel);
                                        m_lsName.push_back(pName);
                                    }
                                    
                                    pSub->elementAt(nRow, 0)->setStyleClass("cell_40");
                                    new WText(szDesc, (WContainerWidget*)pSub->elementAt(nRow, 1));
                                    // 设置行的显示样式
                                    if((nRow + 1) % 2 == 0)
                                        pSub->GetRow(nRow)->setStyleClass("tr1");
                                    else
                                        pSub->GetRow(nRow)->setStyleClass("tr2");
                                }
                            }
                        }
                        // 关闭监测器模板
                        CloseMonitorTemplet(objMonitor);
                    }
                }
            }
            // 关闭设备模板
            CloseEntityTemplet(objDevice);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createOperate
// 说明 创建操作按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::createOperate()
{
    int nRow = numRows();
    // 放弃添加
    WPushButton * pCancel = new WPushButton(SVResString::getResString("IDS_Cancel_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(pCancel)
    {
        // tooltip
        pCancel->setToolTip(SVResString::getResString("IDS_Cancle_Add_Monitor_Tip"));
        // 绑定click
        WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(CancelAdd()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 MonitorMTClicked
// 说明 监测器模板click响应
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::MonitorMTClicked(int nMTID)
{
    emit AddMonitorByType(nMTID, m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
