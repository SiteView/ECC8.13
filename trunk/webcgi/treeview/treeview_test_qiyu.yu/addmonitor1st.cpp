/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// addmonitor1st.cpp
// 根据设备的类型，展示此类型的设备可以使用的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "addmonitor1st.h"
#include "listtable.h"
#include "resstring.h"
#include "mainview.h"
#include "rightview.h"
#include "basedefine.h"
#include "debuginfor.h"
#include "treeview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddMonitor1st::CEccAddMonitor1st(WContainerWidget *parent):
CEccBaseTable(parent),
m_szDTName("")
{
    setStyleClass("panel");
    initForm(false);
    connect(&m_MTMapper, SIGNAL(mapped(int)), this, SLOT(AddMonitorByType(int)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 析构函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddMonitor1st::~CEccAddMonitor1st()
{
    // 移除事件绑定
    removeMapping();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 移除现有的事件绑定
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::removeMapping()
{
    list<WText*>::iterator it;

    // 枚举每条数据
    for(it = m_lsText.begin(); it != m_lsText.end(); it++)
        m_MTMapper.removeMappings((*it));

    // 数据列表清空
    m_lsText.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::initForm(bool bHasHelp)
{
    // 创建标题
    CEccBaseTable::createTitle(bHasHelp);

    // 设置标题文本
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_Monitor"));

    // 得当当前行数
    int nRow = numRows();
    
    // 创建子组并设置TD的样式表
    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("height95p");
    if(pSub)
    {
        //设置样式表
        pSub->setStyleClass("panel");
        // 创建新的滚动区
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel");
        }

        // 创建 表
        CEccListTable *pSubList = new CEccListTable(pSub->elementAt(0, 0), false, false, false, false);
        if(pSubList)
        {
            // 设置标题
            pSubList->setTitle(SVResString::getResString("IDS_Add_Monitor_Title"));
            // 得到内容表
            m_pContent = pSubList->getListTable();
        }

        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);
    }
    
    createOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::createOperate()
{
    // 得到当前行
    int nRow = numRows();
    // 创建操作表
    m_pOperate = new WTable(elementAt(nRow, 0));
    if(m_pOperate)
    {
        // 设置样式表
        m_pOperate->setStyleClass("widthauto");
        // 取消添加
        int nOptRow = m_pOperate->numRows();
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel_Add"), 
            SVResString::getResString("IDS_Cancel_Add_Monitor_Tip"), 
            "", m_pOperate->elementAt(nOptRow, 0));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 操作表居中显示
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 取消添加
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::Cancel()
{
    CEccRightView::showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 根据监测器类型添加新的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::AddMonitorByType(int nMTID)
{
    // 显示添加监测器的第二步的页面
    CEccRightView::showAddMonitor2nd(nMTID, m_szParentID, m_szNetworkset);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举此设备可以使用的所有监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::EnumMT(const string &szParentID, const string &szDTName, const string &szNetworkSet)
{
    m_szParentID = szParentID;
    m_szNetworkset = szNetworkSet;

    if(szDTName.empty() || m_szDTName == szDTName)
        return ;

    m_szDTName = szDTName;

    // 移除已有的消息绑定
    removeMapping();

    if(m_pContent)
    {
        m_pContent->clear();

        list<int> lsMTID;
        CEccMainView::m_pTreeView->GetDevMTList(szDTName, lsMTID);
        list<int>::iterator lstItem;
        // 枚举每个监测器模板
        for(lstItem = lsMTID.begin(); lstItem != lsMTID.end(); lstItem++)
        {
            int nMTID = (*lstItem);
            // 打开监测器模板
            OBJECT objMonitor = GetMonitorTemplet(nMTID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objMonitor != INVALID_VALUE)
            {// 成功
                // 主节点
                MAPNODE node = GetMTMainAttribNode(objMonitor);
                if(node != INVALID_VALUE)
                {
                    // 名称 显示 是否隐藏 描述
                    string szLabel(""), szHidden (""), szDesc ("");
                    if(FindNodeValue(node, svLabel, szLabel))
                        szLabel = SVResString::getResString(szLabel.c_str());
                    
                    if(FindNodeValue(node, svDescription, szDesc))
                        szDesc = SVResString::getResString(szDesc.c_str());

                    FindNodeValue(node, svHidden, szHidden);

                    if(szHidden != "true")
                    {
                        int nRow = m_pContent->numRows();

                        // 监测器显示文字
                        WText *pName = new WText(szLabel, m_pContent->elementAt(nRow, 0));
                        if(pName)
                        {
                            // 文字样式
                            sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onmouseover='" \
                                "this.style.textDecoration=\"underline\"' " \
                                "onmouseout='this.style.textDecoration=\"none\"'");
                            // 绑定 click
                            connect(pName, SIGNAL(clicked()), "showbar();", &m_MTMapper, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                            m_MTMapper.setMapping(pName, nMTID);
                            pName->setToolTip(szLabel);
                            m_lsText.push_back(pName);
                        }
                        new WText(szDesc, m_pContent->elementAt(nRow, 1));

                        m_pContent->GetRow(nRow)->setStyleClass("padding_top");
                        m_pContent->elementAt(nRow, 0)->setStyleClass("widthbold");
                        m_pContent->elementAt(nRow, 1)->setStyleClass("color_2");
                    }
                }
                // 关闭监测器模板
                CloseMonitorTemplet(objMonitor);
            }
        }
    }
}



