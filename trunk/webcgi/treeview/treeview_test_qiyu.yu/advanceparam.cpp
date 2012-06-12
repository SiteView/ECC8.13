#include "advanceparam.h"
#include "resstring.h"
#include "pushbutton.h"
#include "treeview.h"
#include "basedefine.h"
#include "debuginfor.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/Websession.h"
#include "../../opens/libwt/WButtonGroup"
#include "../../opens/libwt/WRadioButton"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAdvanceTable::CEccAdvanceTable(WContainerWidget *parent):
WTable(parent),
m_pDescription(NULL),
m_pDependson(NULL),
m_pConditionGroup(NULL),
m_pNormal(NULL),
m_pError(NULL),
m_pWarnning(NULL),
m_pHideEdit(NULL),
m_pHideButton(NULL)
{
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化页面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::initForm()
{
    createTitle();                      // 创建标题
    
    // 得到当前行数
    int nRow = numRows();
    // 创建子表格
    WTable *pSub = new WTable(elementAt(nRow, 1));
    new WImage("../Images/table_shadow_left.png", elementAt(nRow, 0));
    new WImage("../Images/table_shadow_right.png", elementAt(nRow, 2));
    elementAt(nRow, 0)->setStyleClass("table_shadow_l");
    elementAt(nRow, 2)->setStyleClass("table_shadow_r");
    if(pSub)
    {
        // 创建子表
        createSubTable(pSub);

        // 设置控制TD的样式表和操作响应
        if(m_pControl)
        {
            sprintf(((WTableCell*)m_pControl->parent())->contextmenu_, 
                "width='13px' height='17px' style='CURSOR:pointer' onclick='listtableclick(\"%s\",\"%s\")'",
                m_pControl->formName().c_str(),
                GetRow(nRow)->formName().c_str());
        }
    }

    // 创建内容
    createContent();

    // 封闭表
    nRow = numRows();
    new WImage("../Images/table_shadow_left.png", elementAt(nRow, 0));
    new WImage("../Images/table_shadow_bottom.gif", elementAt(nRow, 1));
    new WImage("../Images/table_shadow_right.png", elementAt(nRow, 2));
    elementAt(nRow, 0)->setStyleClass("table_shadow_l");
    elementAt(nRow, 1)->setStyleClass("table_shadow_bom");
    elementAt(nRow, 2)->setStyleClass("table_shadow_r");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建标题
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createTitle()
{
    int nRow = numRows();
    elementAt(nRow, 0)->setStyleClass("table_shadow_l");
	elementAt(nRow, 2)->setStyleClass("table_shadow_r");

    WTable *pPath = new WTable(elementAt(nRow, 1));
    if(pPath)
    {
        elementAt(nRow, 1)->setStyleClass("table_title");
        m_pTitle = new WText(SVResString::getResString("IDS_Advance_Option"), pPath->elementAt(0, 0));
        pPath->elementAt(0, 0)->setStyleClass("table_title_text");

        m_pControl = new WImage("../Images/table_pucker.png", pPath->elementAt(0, 1));
        pPath->elementAt(0, 1)->setContentAlignment(AlignRight);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示或者隐藏子表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::ShowHideSub()
{
    if(m_bShowSub)
    {
        m_pControl->setImageRef("../Images/table_unwrap.png");
        if(m_pSubTable)
            m_pSubTable->hide();
    }
    else
    {
        m_pControl->setImageRef("../Images/table_pucker.png");
        if(m_pSubTable)
            m_pSubTable->show();
    }
    m_bShowSub = !m_bShowSub;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建子表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createSubTable(WTable *pSubTable)
{
    // 得到指定表的当前行数
    int nRow = pSubTable->numRows();
    // 创建子表
    WTable *pSub = new WTable(pSubTable->elementAt(nRow, 0));
    if(pSub)
    {
        // 设置样式表
        pSub->setStyleClass("panel_item");
        // 设置滚动区
        WScrollArea *pScroll = new WScrollArea(pSubTable->elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel_item");
        }

        // 设置TD的样式表
        pSubTable->elementAt(nRow, 0)->setStyleClass("table_data_input");

        // 创建 子表的子表
        m_pSubTable = new WTable(pSub->elementAt(0, 0));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建内容
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createContent()
{
    if(m_pSubTable)
    {
        // 创建描述
        createDescription();
        // 创建依靠
        createDepends();
        // 创建依靠条件
        createCondition();
    }

    // 创建隐藏变量
    createHide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建依靠条件
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createCondition()
{
    int nRow = m_pSubTable->numRows();
    // 表头（依靠条件）
    new WText(SVResString::getResString("IDS_Depends_Condition"), m_pSubTable->elementAt(nRow, 0));

    // 创建按钮组
    m_pConditionGroup = new WButtonGroup();

    // 依靠条件-错误
    m_pError = new WRadioButton(SVResString::getResString("IDS_Error"), m_pSubTable->elementAt(nRow, 1));
    if(m_pError && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pError);
        m_pError->setChecked();
    }

    // 依靠条件-警告
    m_pWarnning = new WRadioButton(SVResString::getResString("IDS_Warnning"), m_pSubTable->elementAt(nRow, 1));
    if(m_pWarnning && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pWarnning);
    }

    // 依靠条件-正常
    m_pNormal = new WRadioButton(SVResString::getResString("IDS_Normal"), m_pSubTable->elementAt(nRow, 1));
    if(m_pNormal && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pNormal);
    }

    // 依靠条件帮助信息
    WText *pConditionHelp = new WText(SVResString::getResString("IDS_Depends_Condition_Help"),  m_pSubTable->elementAt(nRow  + 1, 1));
    if (pConditionHelp)
    {
        // 设置样式表
        m_pSubTable->elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des");
        // 隐藏
        pConditionHelp->hide();

        m_lsHelp.push_back(pConditionHelp);
    }

    m_pSubTable->GetRow(nRow)->setStyleClass("padding_top");
    m_pSubTable->elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建描述
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createDescription()
{
    int nRow = m_pSubTable->numRows();
    new WText(SVResString::getResString("IDS_Description"), m_pSubTable->elementAt(nRow, 0));
    m_pSubTable->elementAt(nRow, 0)->setContentAlignment(WTable::AlignLeft | WTable::AlignTop);
    // 描述
    m_pDescription = new WTextArea("", m_pSubTable->elementAt(nRow, 1)); 
    if(m_pDescription)
    {   
        m_pDescription->setStyleClass("cell_98");
        m_pDescription->setRows(5);
    }
    // 描述帮助
    WText *pDescHelp = new WText(SVResString::getResString("IDS_Advance_Desc_Help"),  m_pSubTable->elementAt(nRow + 1, 1));
    if (pDescHelp)
    {
        // 样式表
        m_pSubTable->elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des"); 
        // 隐藏
        pDescHelp->hide();

        m_lsHelp.push_back(pDescHelp);
    }

    m_pSubTable->GetRow(nRow)->setStyleClass("padding_top");
    m_pSubTable->elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建依靠
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createDepends()
{
    int nRow = m_pSubTable->numRows();
    // 表头（依靠）
    new WText(SVResString::getResString("IDS_Depends_On"), m_pSubTable->elementAt(nRow, 0));

    WTable *pSub = new WTable(m_pSubTable->elementAt(nRow, 1));
    if(pSub)
    {
        pSub->setStyleClass("widthauto");
        m_pDependson = new WLineEdit(SVResString::getResString("IDS_Friendless"), pSub->elementAt(0, 0));
        if(m_pDependson)
            strcpy(m_pDependson->contextmenu_, "class='input_text' readOnly=true");

        WPushButton * pSet = new WPushButton("...", pSub->elementAt(0, 1));
        if(pSet)
        {
            pSet->setStyleClass("hand");
            WObject::connect(pSet, SIGNAL(clicked()), "showbar();",this, SLOT(showDepend()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }

    m_pSubTable->elementAt(nRow, 1)->setContentAlignment(AlignBottom);

    // 依靠帮助
    WText *pDependHelp = new WText(SVResString::getResString("IDS_Depends_On_Help"), m_pSubTable->elementAt(nRow + 1, 1));
    if (pDependHelp)
    {
        m_pSubTable->elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des");
        pDependHelp->hide();
        m_lsHelp.push_back(pDependHelp);
    }

    m_pSubTable->GetRow(nRow)->setStyleClass("padding_top");
    m_pSubTable->elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示depend树
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::showDepend()
{
    if(m_pHideButton && !m_szSEID.empty())
    {
        string szCmd = m_pHideButton->getEncodeCmd("xclicked()");
        if(!szCmd.empty() && m_pHideEdit)
        {
            szCmd = "DependTree(\"depend.exe?seid=" + m_szSEID + "\", \"" + 
                m_pHideEdit->formName() + "\", \"" + szCmd + "\");hiddenbar();";
            WebSession::js_af_up = szCmd;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示或者隐藏帮助信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::ShowHideHelp(bool bShow)
{
    list<WText*>::iterator txtItem;
    for(txtItem = m_lsHelp.begin(); txtItem != m_lsHelp.end(); txtItem ++)
    {        
        if(bShow)
            (*txtItem)->show();
        else
            (*txtItem)->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建隐藏变量
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::createHide()
{
    int nRow = numRows();
    m_pHideEdit = new WLineEdit("", elementAt(nRow, 0));
    if(m_pHideEdit)
        m_pHideEdit->hide();

    m_pHideButton = new WPushButton("hide button", elementAt(nRow, 0));
    if(m_pHideButton)
    {
        m_pHideButton->hide();
        WObject::connect(m_pHideButton, SIGNAL(clicked()), this, SLOT(changePath()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 得到依靠条件
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccAdvanceTable::getConditon()
{
    string szValue("1");
    if(m_pNormal && m_pError && m_pWarnning)
    {
        if(m_pError->isChecked())
            szValue = "3";

        if(m_pWarnning->isChecked())
            szValue = "2";
    }
    return szValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 得到依靠值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccAdvanceTable::getDepends()
{
    string szValue("");
    if(m_pHideEdit)
        szValue = m_pHideEdit->text();
    if(szValue == "-2")
        szValue = "";
    return szValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 得到描述
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccAdvanceTable::getDescription()
{
    string szValue("");
    if(m_pDescription)
    {
        szValue =  m_pDescription->text();
    }
    return szValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置依靠条件
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::setCondition(const string &szCondition)
{
    if(m_pNormal && m_pError && m_pWarnning)
    {
        if(szCondition == "3")
            m_pError->setChecked();
        else if(szCondition == "2")
            m_pWarnning->setChecked();
        else
            m_pNormal->setChecked();

        m_nOldCondition = atoi(szCondition.c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置依靠
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::setDepends(const string &szIndex)
{
    if(m_pHideEdit && !szIndex.empty())
    {
        m_szOldDependID = szIndex;
        if(m_szOldDependID.empty())
            m_szOldDependID = "-2";
        m_pHideEdit->setText(szIndex);
        
        PAIRLIST lsPath;
        CEccTreeView::MakePath(szIndex, lsPath);

        if(lsPath.size() >= 1)
        {
            string szPath("");
            sv_pair svitem;
            while(lsPath.size() > 1)
            {
                svitem = lsPath.front();
                lsPath.pop_front();
                szPath += svitem.value + ":";
            }
            svitem = lsPath.front();
            lsPath.pop_front();
            szPath += svitem.value;

            if(m_pDependson)
                m_pDependson->setText(szPath);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置描述
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::setDescription(const string &szDescription)
{
    if(m_pDescription)
        m_pDescription->setText(szDescription);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 重至数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::ResetData()
{
    m_szSEID = "";

    if(m_pHideEdit)
    {
        m_pHideEdit->setText("");
        if(m_pDependson)
            m_pDependson->setText(SVResString::getResString("IDS_Friendless"));
    }

    if(m_pDescription)
        m_pDescription->setText("");

    if(m_pError)
        m_pError->setChecked();
    if(m_pNormal)
        m_pNormal->unChecked();
    if(m_pWarnning)
        m_pWarnning->unChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置SE索引
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::setSEID(const string &szSEID)
{
    m_szSEID = szSEID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 添加帮助信息到指定list中
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::AppendHelpInList(list<WText*> &lsHelp)
{
    list<WText*>::iterator it;
    for(it = this->m_lsHelp.begin(); it != m_lsHelp.end(); it++)
    {
        lsHelp.push_back((*it));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 保存高级参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAdvanceTable::SaveAdvanceParam(MAPNODE &mainNode)
{
    bool bNoError = false;

    string szDescription(""), szDepends(""), szCondition("");

    szDescription = getDescription();
    szDepends = getDepends();
    szCondition = getConditon();

    if(AddNodeAttrib(mainNode, svDescription, szDescription) && AddNodeAttrib(mainNode, svDependON, szDepends)
        && AddNodeAttrib(mainNode, svDependCondition, szCondition))
        bNoError = true;

    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 依靠条件被修改
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAdvanceTable::isDependsChanged()
{
    if(m_pHideEdit)
    {
        int nCondition = 1;
        if(m_pError && m_pError->isChecked())
            nCondition = 3;
        else if(m_pWarnning && m_pWarnning->isChecked())
            nCondition = 2;

        if(m_szOldDependID == m_pHideEdit->text() && m_nOldCondition == nCondition )
            return false;
        else
            return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 展示依靠路径
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAdvanceTable::changePath()
{
//? change path
    if(m_pHideEdit && !m_pHideEdit->text().empty() && m_pHideEdit->text() != "-2")
    {
        PAIRLIST lsPath;
        CEccTreeView::MakePath(m_pHideEdit->text(), lsPath);

        if(lsPath.size() >= 1)
        {
            string szPath("");
            sv_pair svitem;
            while(lsPath.size() > 1)
            {
                svitem = lsPath.front();
                lsPath.pop_front();
                szPath += svitem.value + ":";
            }
            svitem = lsPath.front();
            lsPath.pop_front();
            szPath += svitem.value;

            if(m_pDependson)
                m_pDependson->setText(szPath);
        }
    }
    else
    {
        if(m_pDependson)
            m_pDependson->setText(SVResString::getResString("IDS_Friendless"));
    }
}
