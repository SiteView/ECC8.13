/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件 dependtable.cpp
// 说明
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "dependtable.h"

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WebSession.h"

extern void PrintDebugString(const string &szMsg);

#include "basefunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 SVDependTable
// 说明 构造函数
// 参数 WContainerWidget * parent，父页面
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDependTable::SVDependTable(WContainerWidget * parent):
WTable(parent)
{
    m_pSub = NULL;
    m_pShow = NULL;
    m_pHide = NULL;
    m_pHideEdit = NULL;
    m_pHideButton = NULL;
    // 加载文字
    //loadString();
    // 样式表
    setStyleClass("t2");
    //初始化界面
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 loadString
// 说明 加载界面文字
// 参数 无
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVDependTable::loadString()
//{
//	//Resource
//	OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//			FindNodeValue(ResNode,"IDS_Friendless",m_szFriendless);
//			FindNodeValue(ResNode,"IDS_Description",m_szDescription);
//			FindNodeValue(ResNode,"IDS_Advance_Desc_Help",m_szDescriptionHelp);
//			FindNodeValue(ResNode,"IDS_Depends_Condition",m_szCondition);
//			FindNodeValue(ResNode,"IDS_Depends_Condition_Help",m_szConditionHelp);
//			FindNodeValue(ResNode,"IDS_Depends_On",m_szDepend);
//			FindNodeValue(ResNode,"IDS_Depends_On_Help",m_szDependHelp);
//			FindNodeValue(ResNode,"IDS_Advance_Option",m_szTitle);
//			FindNodeValue(ResNode,"IDS_Error",m_szConditionErr);
//			FindNodeValue(ResNode,"IDS_Normal",m_szConditionNormal);
//			FindNodeValue(ResNode,"IDS_Warnning",m_szConditionWarn);
//		}
//		CloseResource(objRes);
//	}
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initForm
// 说明 初始化页面
// 参数 无
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::createCondition()
{
    int nRow = m_pSub->numRows();
    // 表头（依靠条件）
    new WText(SVResString::getResString("IDS_Depends_Condition"), (WContainerWidget*)m_pSub->elementAt(nRow, 0));
    m_pSub->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    m_pSub->elementAt(nRow, 0)->setStyleClass("cell_10");

    // 依靠条件
    m_pDependCondition = new WComboBox((WContainerWidget*)m_pSub->elementAt(nRow, 1));
    if (m_pDependCondition)
    {
        // 正确
        m_pDependCondition->addItem(SVResString::getResString("IDS_Normal"));
        // 警告
        m_pDependCondition->addItem(SVResString::getResString("IDS_Warnning"));
        // 错误
        m_pDependCondition->addItem(SVResString::getResString("IDS_Error"));
        // 设置样式表
        m_pDependCondition->setStyleClass("cell_10"); 
    }

    // 换行
    new WText("<BR>", (WContainerWidget*)m_pSub->elementAt(nRow, 1));
    // 依靠条件帮助信息
    m_pConditionHelp = new WText(SVResString::getResString("IDS_Depends_Condition_Help"), (WContainerWidget*)m_pSub->elementAt(nRow, 1));
    if (m_pConditionHelp)
    {
        // 设置样式表
        m_pConditionHelp->setStyleClass("helps");
        // 隐藏
        m_pConditionHelp->hide();

    }
}
void SVDependTable::createDesc()
{
    int nRow = m_pSub->numRows();
    new WText(SVResString::getResString("IDS_Description"), m_pSub->elementAt(nRow, 0));            
    m_pSub->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    m_pSub->elementAt(nRow, 0)->setStyleClass("cell_10");

    // 描述
    m_pDescription = new WTextArea("", m_pSub->elementAt(nRow, 1)); 
    if(m_pDescription)
    {   
        m_pDescription->setStyleClass("cell_98");           
        m_pDescription->setRows(5);
    }
    //换行
    new WText("<BR>", (WContainerWidget*)m_pSub->elementAt(nRow, 1));
    // 描述帮助
    m_pDescriptionHelp = new WText(SVResString::getResString("IDS_Advance_Desc_Help"), (WContainerWidget*)m_pSub->elementAt(0, 1));
    if (m_pDescriptionHelp)
    {
        // 样式表
        m_pDescriptionHelp->setStyleClass("helps"); 
        // 隐藏
        m_pDescriptionHelp->hide();
    }
}

void SVDependTable::createTitle()
{
    int nRow = numRows();
    m_pHide = new WImage("../icons/open.gif", (WContainerWidget *)elementAt( nRow, 0));
    if ( m_pHide )
    {
        m_pHide->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(m_pHide, SIGNAL(clicked()), this, SLOT(showSubTable()));
        m_pHide->hide();
    }

    m_pShow = new WImage("../icons/close.gif", (WContainerWidget *)elementAt(nRow, 0));
    if ( m_pShow )
    {
        m_pShow->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
        WObject::connect(m_pShow, SIGNAL(clicked()), this, SLOT(hideSubTable()));
    }

    new WText(SVResString::getResString("IDS_Advance_Option"), (WContainerWidget *)elementAt(nRow, 0));
    elementAt(0,0)->setStyleClass("t2title");
}

void SVDependTable::initForm()
{
    createTitle();
    int nRow = numRows();
    m_pSub = new WTable(elementAt(nRow, 0));
    if(m_pSub)
    {

        m_pSub->setStyleClass("t3");
        createDesc();
        createDependList();
        createCondition();
    } 
    createHideEdit(); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showHelp
// 说明 显示/隐藏帮助信息
// 参数 bool bShow，显示/隐藏
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::showHelp(bool bShow)
{
    if(bShow)
    {
        // 描述信息帮助
        if(m_pDescriptionHelp)
            m_pDescriptionHelp->show();
        // 依靠帮助
        if(m_pDependHelp)
            m_pDependHelp->show();
        // 依靠条件帮助
        if(m_pConditionHelp)
            m_pConditionHelp->show();
    }
    else
    {
        // 隐藏描述信息帮助
        if(m_pDescriptionHelp)
            m_pDescriptionHelp->hide();
        // 隐藏依靠帮助
        if(m_pDependHelp)
            m_pDependHelp->hide();
        // 隐藏依靠条件帮助
        if(m_pConditionHelp)
            m_pConditionHelp->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createDependList
// 说明 依靠表
// 参数 无
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::createDependList()
{
    int nRow = m_pSub->numRows();
    // 表头（依靠）
    new WText(SVResString::getResString("IDS_Depends_On"), (WContainerWidget*)m_pSub->elementAt(nRow, 0));
    m_pSub->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    m_pSub->elementAt(nRow, 0)->setStyleClass("cell_10");

    m_pPath = new WText(SVResString::getResString("IDS_Friendless"), m_pSub->elementAt(nRow, 1));
    if(m_pPath)
    {
        m_pPath->setStyleClass("readonly");
    }

    new WText("&nbsp;", (WContainerWidget*)m_pSub->elementAt(nRow, 1));
    
    WPushButton *pShow = new WPushButton("...", m_pSub->elementAt(nRow, 1));
    if(pShow)
    {
        WObject::connect(pShow, SIGNAL(clicked()), this, SLOT(showDependTree()));
    }

    // 换行
    new WText("<BR>", (WContainerWidget*)m_pSub->elementAt(nRow, 1));
    // 依靠帮助
    m_pDependHelp = new WText(SVResString::getResString("IDS_Depends_On_Help"), (WContainerWidget*)m_pSub->elementAt(nRow, 1));
    if (m_pDependHelp)
    {
        m_pDependHelp->setStyleClass("helps");
        m_pDependHelp->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 SVDependTable
// 说明 依靠条件
// 参数 无
// 返回 const char * 指针，依靠条件
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::getCodition(string &szValue)
{
    if(m_pDependCondition)
    {
        int nIndex = m_pDependCondition->currentIndex();
        switch(nIndex)
        {
        case 0:
            szValue = "1";
            break;
        case 1:
            szValue = "2";
            break;
        case 2:
            szValue = "3";
            break;
        default:
            szValue = "1";
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 SVDependTable
// 说明 依靠
// 参数 无
// 返回 const char * 指针，依靠
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::getDepend(string &szValue)
{
    if(m_pHideEdit)
        szValue = m_pHideEdit->text();
    if(szValue == "-2")
        szValue = "";
    // 暂时无法进行设置
    // 需等待树的完成
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 getDescription
// 说明 得到描述信息
// 参数 无
// 返回 const char * 指针，描述信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::getDescription(string &szValue)
{
    if(m_pDescription)
    {
        szValue =  m_pDescription->text();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 setCodition
// 说明 设置依靠条件
// 参数 string &szCondition, 依靠条件
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::setCodition(string &szCondition)
{
    if(m_pDependCondition)
    {
        if(!szCondition.empty())
            m_pDependCondition->setCurrentIndex(atoi(szCondition.c_str()) - 1);
        else
            m_pDependCondition->setCurrentIndex(0);
        m_nOldCondition = m_pDependCondition->currentIndex() + 1;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 setDepend
// 说明 设置依靠
// 参数 string &szDepend, 依靠
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::setDepend(string &szDepend)
{
    // 暂时无法进行设置
    // 需等待树的完成
    if(m_pHideEdit && !szDepend.empty())
    {
        m_szOldDependID = szDepend;
        if(m_szOldDependID.empty())
            m_szOldDependID = "-2";
        m_pHideEdit->setText(szDepend);
        if(m_pPath)
            m_pPath->setText(makePath(m_pHideEdit->text()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 setDescription
// 说明 设置描述信息
// 参数 string &szDesc, 描述信息
// 返回 无
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::setDescription(string &szDesc)
{
    m_pDescription->setText(szDesc);
}

void SVDependTable::showDependTree()
{
    if(m_pHideButton)
    {
        string szCmd = m_pHideButton->getEncodeCmd("xclicked()");
        if(!szCmd.empty() && m_pHideEdit)
        {
            szCmd = "DependTree(\"depend.exe?seid=" + m_szUserID + "\", \"" + 
                m_pHideEdit->formName() + "\", \"" + szCmd + "\");";
            WebSession::js_af_up = szCmd;
        }
    }
}

void SVDependTable::createHideEdit()
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

void SVDependTable::cleardate()
{
    if(m_pHideEdit)
    {
        m_pHideEdit->setText("");
        if(m_pPath)
            m_pPath->setText(SVResString::getResString("IDS_Friendless"));
    }
}

void SVDependTable::changePath()
{
    if(m_pHideEdit && !m_pHideEdit->text().empty() && m_pHideEdit->text() != "-2")
    {
        if(m_pPath)
            m_pPath->setText(makePath(m_pHideEdit->text()));
    }
    else
    {
        if(m_pPath)
            m_pPath->setText(SVResString::getResString("IDS_Friendless"));
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::showSubTable()
{
    if(m_pShow)
    {
        m_bHide = false;
        m_pShow->show();
        m_pHide->hide();
        if(m_pSub)
            m_pSub->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDependTable::hideSubTable()
{
    if(m_pHide)
    {
        m_bHide = true;
        m_pHide->show();
        m_pShow->hide();
        if(m_pSub)
            m_pSub->hide();
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
