/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// batchadd.cpp
// 批量添加同一类型的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "batchadd.h"
#include "pushbutton.h"
#include "rightview.h"
#include "resstring.h"
#include "listtable.h"
#include "mainview.h"
#include "treeview.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"


#include "../base/OperateLog.h"

#include "../userright/User.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccBatchAdd::CEccBatchAdd(WContainerWidget *parent):
CEccBaseTable(parent),
m_pDynName(NULL)
{
    setStyleClass("panel");
    initForm(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::initForm(bool bHasHelp)
{
    // 基础类初始化
    CEccBaseTable::createTitle(bHasHelp);
    // 设置标题文本
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Batch_Add"));

    int nRow = numRows();

    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("height95p");
    if(pSub)
    {
        pSub->setStyleClass("panel");
        // 创建滚动区
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel");
        }

        CEccListTable *pSubList = new CEccListTable(pSub->elementAt(0, 0), false, false, true, false);
        if(pSubList)
        {
            pSubList->setTitle(SVResString::getResString("IDS_Batch_Add"));
            m_pContent = pSubList->getListTable();
        }
        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);
    }
    
    // 创建操作按钮
    createOperate();
    // 创建数据表栏目头
    createListTitle();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 创建数据表栏目头
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::createListTitle()
{
    if(m_pContent)
    {
        int nRow = m_pContent->numRows();
        // 全选
        m_pSelAll = new WCheckBox("", m_pContent->elementAt(nRow, 0));
        if(m_pSelAll)
        {
            WObject::connect(m_pSelAll, SIGNAL(clicked()), "showbar();", this, SLOT(SelAll()),  
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
        
        // 创建分隔条
        new WImage("../Images/table_head_space.png", m_pContent->elementAt(nRow, 1));
        new WImage("../Images/space.gif", m_pContent->elementAt(0, 1));
        // 动态参数
        m_pDynName = new WText("dyn value", m_pContent->elementAt(nRow, 2));

        // 设置样式表和对齐方式
        m_pContent->elementAt(0, 1)->setStyleClass("width4");
        m_pContent->elementAt(0, 0)->setStyleClass("table_data_grid_header_text");
        m_pContent->elementAt(0, 2)->setStyleClass("table_data_grid_header_text");
        m_pContent->elementAt(0, 0)->setContentAlignment(AlignCenter);
        m_pContent->elementAt(0, 2)->setContentAlignment(AlignCenter);
        m_pContent->GetRow(0)->setStyleClass("table_data_grid_header");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建操作
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::createOperate()
{
    int nRow = numRows();
    m_pOperate = new WTable(elementAt(nRow, 0));
    if(m_pOperate)
    {
        // 设置样式表
        m_pOperate->setStyleClass("widthauto");
        int nOptRow = m_pOperate->numRows();
        // 保存
        CEccImportButton *pSave = new CEccImportButton(SVResString::getResString("IDS_Save"), SVResString::getResString("IDS_Save_Sel_Monitor_Tip"), 
            "", m_pOperate->elementAt(nOptRow, 0));
        if(pSave)
        {
            WObject::connect(pSave, SIGNAL(clicked()), "showbar();", this, SLOT(SaveSelMonitor()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        // 分隔符
        new WText("&nbsp;", m_pOperate->elementAt(nOptRow, 1));

        // 取消
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel"), SVResString::getResString("IDS_Cancle_Add_Monitor_Tip"), 
            "", m_pOperate->elementAt(nOptRow, 2));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 底部居中对齐
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 保存所选的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::SaveSelMonitor()
{
    list<ecc_value_list> lsValue;
    map<string, string, less<string> >::iterator itValue;
    map<string, WCheckBox*, less<string> >::iterator itCheckBox;

    unsigned long ulStart = GetTickCount();

    // 枚举是否被选中
    for(itCheckBox = m_lsCheckBox.begin(); itCheckBox != m_lsCheckBox.end(); itCheckBox ++)
    {
        if(itCheckBox->second->isChecked())
        {
            itValue = m_lsValue.find(itCheckBox->first);
            if(itValue != m_lsValue.end())
            {
                ecc_value_list item(itValue->second, itCheckBox->first);
                lsValue.push_back(item);
            }
        }
    }

    // 批量添加
    string szValue = CEccRightView::AddMonitorBySel(lsValue);
    if(!szValue.empty())
    {// 添加失败
        map<string, WCheckBox*, less<string> >::iterator it = m_lsCheckBox.find(szValue);
        if(it != m_lsCheckBox.end())
        {
            it->second->label()->setText(it->second->label()->text() + SVResString::getResString("IDS_Monitor_Point_Lack_Tip"));
            it->second->label()->setStyleClass("errortip");
        }
    }
    else
    {// 添加成功
        // 显示主界面
        CEccRightView::showMainForm();
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccBatchAdd.SaveSelMonitor", SVResString::getResString("IDS_Batch_Add"), 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccBatchAdd.SaveSelMonitor", SVResString::getResString("IDS_Batch_Add"), 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 取消添加
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::Cancel()
{
    CEccRightView::showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 全选
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::SelAll()
{
    if(m_pSelAll)
    {
        map<string, WCheckBox*, less<string> >::iterator lsItem;
        for(lsItem = m_lsCheckBox.begin(); lsItem != m_lsCheckBox.end(); lsItem ++)
            lsItem->second->setChecked(m_pSelAll->isChecked());
    }

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置动态数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccBatchAdd::setListValue(list<ecc_value_list> &lsValue, string szDynName)
{
    if(m_pDynName)
        m_pDynName->setText(szDynName);

    if(m_pSelAll)
        m_pSelAll->setChecked(false);

    if(m_pContent)
        while(m_pContent->numRows() > 1)
            m_pContent->deleteRow(m_pContent->numRows() - 1);

    m_lsCheckBox.clear();
    m_lsValue.clear();

    list<ecc_value_list>::iterator itValue;
    
    int nRow = m_pContent->numRows();

    for(itValue = lsValue.begin(); itValue != lsValue.end(); itValue ++)
    {
        WCheckBox *pCheck = new WCheckBox("", m_pContent->elementAt(nRow, 0));
        if(pCheck)
            m_lsCheckBox[(*itValue).m_szValue] = pCheck;

        new WText((*itValue).m_szLabel, m_pContent->elementAt(nRow, 2));

        m_pContent->elementAt(nRow, 0)->setContentAlignment(AlignCenter);

        if(nRow % 2 == 0)
            m_pContent->GetRow(nRow)->setStyleClass("table_data_grid_item_bg");

        m_pContent->elementAt(nRow, 0)->setStyleClass("width120px");
        m_pContent->elementAt(nRow, 2)->setStyleClass("table_data_grid_item_text");

        m_lsValue[(*itValue).m_szValue] = (*itValue).m_szLabel;

        nRow ++;
    }
}

