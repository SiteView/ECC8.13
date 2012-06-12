/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "addgroup.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../base/basetype.h"
#include "resstring.h"
//#include "../base/OperateLog.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char * szMsg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVAddGroup::SVAddGroup(WContainerWidget *parent,CUser * pUser, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pTitle = NULL;
    m_pContentTable = NULL;
    m_pSubContent = NULL;
    m_pAdvanced = NULL;
    m_pSave = NULL;
    m_pCancel = NULL;

    m_pSVUser = pUser;

    //loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initForm
// 说明 初始化页面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::initForm()
{
    setStyleClass("t5");

    addGroupTitle();
    if(m_pSubContent)
    {
        addGroupGeneral();
        addGroupAdv();
    }
    addGroupOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 addGroupGeneral
// 说明 添加基本属性表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupGeneral()
{
    // 得到子内容表行数
    int nRow = m_pSubContent->numRows();
    // 创建新隐藏/显示表
    SVShowTable *pSub = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    if (pSub)
    {
        // 设置标题
        pSub->setTitle(SVResString::getResString("IDS_General_Title").c_str());
        // 创建子表
        m_pGeneral = pSub->createSubTable();
        if (m_pGeneral)
        {
            // 组名（必添项）显示文字
            new WText(SVResString::getResString("IDS_Group_Name"), (WContainerWidget*)m_pGeneral->elementAt(0, 0));
            new WText("<span class =required>*</span>", m_pGeneral->elementAt(0, 0));
            // 对齐方式
            m_pGeneral->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
            m_pGeneral->elementAt(0, 0)->setStyleClass("cell_10");
            // 组名
            m_pName = new WLineEdit("", (WContainerWidget*)m_pGeneral->elementAt(0, 1));
            if(m_pName)
                m_pName->setStyleClass("cell_98");
            // 帮助
            new WText("<BR>", (WContainerWidget*)m_pGeneral->elementAt(0, 1));
            m_pNameHelp = new WText(SVResString::getResString("IDS_Group_Name_Help"), (WContainerWidget*)m_pGeneral->elementAt(0, 1));
            if (m_pNameHelp)
            {
                m_pNameHelp->setStyleClass("helps");
                m_pNameHelp->hide();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 addGroupAdv
// 说明 创建高级属性表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupAdv()
{
    // 得到子内容表当前行数
    int nRow = m_pSubContent->numRows();
    // 高级属性参数表
    m_pAdvanced = new SVDependTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 addGroupOperate
// 说明 添加组操作按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupOperate()
{
    int nRow = numRows();
    // 保存 按钮
    m_pSave = new WPushButton(SVResString::getResString("IDS_Save"), (WContainerWidget*)elementAt(nRow, 0));
    if (m_pSave)
    {
        // 绑定 click
        WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(saveGroup()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        // tooltip
        m_pSave->setToolTip(SVResString::getResString("IDS_Save_Group_Tip"));
    }

    new WText("&nbsp;",this->elementAt(nRow,0));

    // 返回上一级
    m_pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
    if (m_pCancel)
    {
        // 绑定 click
        WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(backPreview()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        // tooltip
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Group_Edit_Tip"));
    }
    // 设置对齐方式
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 addGroupTitle
// 说明 创建主标题
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupTitle()
{
    // 得到当前行数
    int nRow = numRows();
    // 引入js文件
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));
    
    // 当前行数加1
	nRow ++;
    // 创建主标题
    m_pTitle = new WText(SVResString::getResString("IDS_Add_Group_Title"), (WContainerWidget*)elementAt(nRow, 0));
    // 主标题样式
    elementAt(nRow, 0)->setStyleClass("t1title");
    // 当前行数加1
    nRow ++;
    // 创建内容表
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // 设置单元格的 Padding和Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        // 创建滚动区
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        // 设置样式
        m_pContentTable->setStyleClass("t5");           
        elementAt(nRow, 0)->setStyleClass("t7");

        // 得到内容表当前行
        nRow = m_pContentTable->numRows();
        // 创建子内容表
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // 内容表当前对其方式
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
        if(m_pSubContent)
        {
            // 子内容表 样式
            m_pSubContent->setStyleClass("t8");
            // 子内容表单元格对齐方式（右上）
            m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight); 

			// 翻译
            int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	        if(bTrans == 1)
	        {
                // 翻译按钮
	            m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)elementAt(nRow, 0));
	            if(m_pTranslateBtn)
	            {
                    // 绑定 click
		            connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
		            m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
                }
                new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	        }

            // 帮助
			WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
            if(pHelp)
            {
                // 样式
                pHelp->setStyleClass("imgbutton");
                // tooltip
                pHelp->setToolTip(SVResString::getResString("IDS_Help"));
                // 绑定click
                WObject::connect(pHelp, SIGNAL(clicked()), "showbar();", this, SLOT(showHelp()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Translate
// 说明 翻译响应函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "groupRes";
	WebSession::js_af_up += "')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveGroup
// 说明 保存组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::saveGroup()
{
    // 名称 描述 依靠 依靠条件 
    string szName(""), szDescription(""), szDepends(""), szCondition("");

    // 错误
    bool bError = false;
    // 组名
    szName  = m_pName->text();
    szName = strtriml(szName.c_str());
    szName = strtrimr(szName.c_str());
    if ( szName.empty() )
    { // 组名为空
        // 显示错误信息
        if(m_pNameHelp)
        {
            m_pNameHelp->setStyleClass("errors");
            m_pNameHelp->setText(SVResString::getResString("IDS_Group_Name_Error"));
            // 显示帮助
            m_pNameHelp->show();
        }
        // 显示基础表
        m_pGeneral->show();
        // 发生错误
        bError = true;
    }
    if(m_pAdvanced)
    {
        m_pAdvanced->getDescription(szDescription);
        m_pAdvanced->getDepend(szDepends);
        m_pAdvanced->getCodition(szCondition);
    }

    // 如果发生错误，退出函数
    if(bError)
    {
        WebSession::js_af_up = "hiddenbar();";
        return;
    }


    // 如果隐藏帮助信息
    if(!m_bShowHelp)
        m_pNameHelp->hide();
    else
    {
        m_pNameHelp->setText(SVResString::getResString("IDS_Group_Name_Help"));
        m_pNameHelp->setStyleClass("helps");
    }


    //调用底层函数保存数据，成功后返回上一级页面并添加数据否则返回上一级页面。
    OBJECT groupobj = 0;


    // 是否是添加新的组
    if(m_szEditIndex.empty())
        groupobj = CreateGroup();
    else
        groupobj = GetGroup(m_szEditIndex, m_szIDCUser, m_szIDCPwd);

    // 创建/打开组 是否 成功
    if (groupobj != INVALID_VALUE)
    {
        // 得到主属性
        MAPNODE attr = GetGroupMainAttribNode(groupobj);
        // 状态
        bool bState = false;
        if(attr != INVALID_VALUE)
        { // 打开属性
            if(AddNodeAttrib(attr, "sv_name", szName) && AddNodeAttrib(attr, "sv_description", szDescription) &&
                AddNodeAttrib(attr, "sv_dependson", szDepends) && AddNodeAttrib(attr, "sv_dependscondition", szCondition))
            {
                bState = true;
            }
        }

        // 保存信息全部成功且是创建新的组
        if(bState && m_szEditIndex.empty())
        {
            // 创建新组
            if(!IsSVSEID(m_szParentIndex))
                saveDisableByParent(attr, Tree_GROUP, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
            string szRealIndex = AddNewGroup(groupobj, m_szParentIndex, m_szIDCUser, m_szIDCPwd);

            // 创建组成功，触发创建成功消息
            if(!szRealIndex.empty())
            {    
                int nIndex = FindIndexByID(szRealIndex);
                char szIndex[16] = {0};
                sprintf(szIndex, "%d", nIndex);
                AddNodeAttrib(attr, "sv_index", szIndex);
                if(m_pSVUser && !m_pSVUser->isAdmin())
                    m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_GROUP);
                emit addGroupName(szName, szRealIndex);
            }
		}
        else if (bState && !m_szEditIndex.empty())
        {// 编辑组
            // 编辑成功 触发编辑成功消息

            if(SubmitGroup(groupobj, m_szIDCUser, m_szIDCPwd))
            {   
                emit editGroupName(szName,m_szEditIndex);

                if(m_pAdvanced->isDependChange())
                {
                    string szQueueName(getConfigTrackQueueName(m_szEditIndex));
                    CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                    if(!::PushMessage(szQueueName, "GROUP:UPDATE", m_szEditIndex.c_str(), static_cast<int>(m_szEditIndex.length()) + 1, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
                }
           }
        }
        // 关闭组
        CloseGroup(groupobj);
    }

    // 返回上一级页面
    // 编辑组ID 为空
    m_szEditIndex = "";
    emit backMain();    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 backPreview
// 说明 返回主页面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::backPreview()
{
    m_szEditIndex = "";
    emit backMain();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showHelp
// 说明 显示/隐藏帮助信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::showHelp()
{
    m_bShowHelp = ! m_bShowHelp;
    m_pAdvanced->showHelp(m_bShowHelp);
    if (m_bShowHelp)
    {
        if(m_pNameHelp)
        {
            m_pNameHelp->setText(SVResString::getResString("IDS_Group_Name_Help"));
            m_pNameHelp->show();
        }
    }
    else
    {
        if(m_pNameHelp)
            m_pNameHelp->hide();
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditGroup
// 说明 根据组索引编辑组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::EditGroup(string &szIndex)
{
    // 重置所有数据
    ResetParam();
	if(m_pSave)
	{
        // 设置保存按钮显示文字
		m_pSave->setText(SVResString::getResString("IDS_Save"));
        // tooltip
		m_pSave->setToolTip(SVResString::getResString("IDS_Save_Group_Tip"));
	}
    m_szEditIndex = szIndex;
    if(m_pAdvanced)
        m_pAdvanced->setUserID(FindSEID(m_szEditIndex));
    if (!m_szEditIndex.empty())
    {
        // 打开组
        OBJECT groupobj = GetGroup(m_szEditIndex, m_szIDCUser, m_szIDCPwd);
        if(groupobj != INVALID_VALUE)
        {// 成功
            string szName(""), szDesc(""), szCondition(""), szDepends("");
            MAPNODE nodeobj =  GetGroupMainAttribNode(groupobj);
            if(nodeobj != INVALID_VALUE)
            {
                // 组名称
                FindNodeValue(nodeobj, "sv_name", szName);
                // 描述
                FindNodeValue(nodeobj, "sv_description", szDesc);
                // 依靠条件
                FindNodeValue(nodeobj, "sv_dependscondition", szCondition);
                // 依靠
                FindNodeValue(nodeobj, "sv_dependson", szDepends);
                if(m_pName)
                    m_pName->setText(szName); 
                if(m_pAdvanced)
                {
                    m_pAdvanced->setDescription(szDesc);
                    m_pAdvanced->setDepend(szDepends);
                    m_pAdvanced->setCodition(szCondition);
                }
            }
            // 关闭组
            CloseGroup(groupobj);
        }
    }
    // 设置 主标题 显示文字
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Edit_Group_Title"));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ResetParam
// 说明 重置所有参数显示文字
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::ResetParam()
{
    // 重置编辑
    m_szEditIndex = "";
    // 重置组名
    if(m_pName)
        m_pName->setText("");
    // 重置主标题
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_Group_Title"));
	if(m_pSave)
	{
        // 重置保存按钮显示文字
		m_pSave->setText(SVResString::getResString("IDS_Add"));
        // tooltip
		m_pSave->setToolTip(SVResString::getResString("IDS_Add_Group_Tip"));
	}
    // 重置高级参数
    if(m_pAdvanced)
    {
        m_pAdvanced->setDescription(string(""));
        m_pAdvanced->resetDepend();
        m_pAdvanced->setCodition(string(""));
        m_pAdvanced->setUserID(FindSEID(m_szParentIndex));
    }
    // 隐藏帮助
    m_bShowHelp = true;
    showHelp();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
