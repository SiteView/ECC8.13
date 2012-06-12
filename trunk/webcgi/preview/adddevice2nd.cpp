#include "adddevice2nd.h"
#include "../group/showtable.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../../base/des.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char *szMsg);
extern void WriteLogFile(const char *pszFile, const char *pszMsg);

#include "../base/basetype.h"

typedef bool(ListDevice)(const char* szQuery, char* szReturn, int &nSize);

#include "../group/resstring.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDevice::SVDevice(WContainerWidget * parent, CUser *pUser, string szIDCUser, string szIDCPwd, string szDeviceType):
WTable(parent)
{
    m_bShowHelp = false;                            // 是否显示帮助
    m_pGeneral = NULL;                              // 基础信息参数
    m_pDeviceTitle = NULL;                          // 高级信息标题
    m_pContentTable = NULL;                         // 内容表
 
    m_pSubContent = NULL;                           // 子内容表
    m_pAdvTable = NULL;                             // 高级参数表
    m_pSVUser = pUser;                              // 当前用户权限

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;

    initForm();                                     // 初始化
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumBaseParam
// 说明 枚举设备模板中定义的基本属性
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::enumBaseParam()
{
    // 重置
    // 打开设备模板
    OBJECT objDevice = GetEntityTemplet(m_szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// 成功
        LISTITEM lsItem;
        // 得到每个属性
        if( FindETContrlFirst(objDevice, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                SVParamItem *param = new SVParamItem(objNode);
                m_lsBasicParam.push_back(param);
            }
        }
        // 关闭设备模板
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createGeneral
// 说明 创建显示基础属性的表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createGeneral()
{
    //得到当前内容表的行数
    int nRow = m_pSubContent->numRows();
    // 是否已创建此表
    if(m_pGeneral == NULL)
        m_pGeneral = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    if(m_pGeneral)
    {// 创建成功
        m_pGeneral->show();
        // 设置标题文字
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Title").c_str());
        list<SVParamItem*>::iterator lstItem;
        // 创建子表
        WTable *pSub = m_pGeneral->createSubTable();
        if(pSub)
        {
            // 循环创建每个属性中的控件
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // 是否有跟随值
                if((*lstItem)->isHasFollow())
                {
                    // 得到跟随值 && 设置跟随值
                    string szFollow = (*lstItem)->getFollow();
                    if(!szFollow.empty())
                    {
                        list<SVParamItem*>::iterator ittmp ;
                        // 枚举每条属性
                        for(ittmp = m_lsBasicParam.begin(); ittmp != m_lsBasicParam.end(); ittmp ++)
                        {
                            // 是否匹配
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                (*lstItem)->setFollowItem((*ittmp));
                                break;
                            }
                        }
                    }
                }
                // 创建控件
                (*lstItem)->CreateControl(pSub);
                // 是否是动态属性
                if((*lstItem)->isDynamic())
                {
                    m_lsDyn.push_back((*lstItem));
                }
            }
            
            // 创建设备名称
            createHostName(pSub);
            // 枚举每一个属性
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // 属性名称是否是_MachineName或者是否需要和设备名称动态绑定
                if(strcmp((*lstItem)->getName(), "_MachineName") == 0 || (*lstItem)->isSynTitle())
                {
                    // 动态绑定
                    if(m_pDeviceTitle != NULL && (*lstItem)->getControl() != NULL)
                    {
                        WInteractWidget* pEdit = (*lstItem)->getControl();
                        string szCmd = "onkeyup='Synchronization(\"" + pEdit->formName() +
                            "\",\"" + m_pDeviceTitle->formName() + "\")'";
                        strcpy(pEdit->contextmenu_, szCmd.c_str());
                    }
                }
                else if(strcmp((*lstItem)->getName(), "_ProtocolType") == 0 && (*lstItem)->getControl() != NULL)
                {// 特殊处理_ProtocolType
                    list<SVParamItem*>::iterator lsItem;
                    for(lsItem = m_lsBasicParam.begin(); lsItem != m_lsBasicParam.end(); lsItem ++)
                    {
                        if(strcmp((*lsItem)->getName(), "_Port") == 0 && (*lstItem)->getControl() != NULL)
                        {
                            string szCmd = "onchange='ChangePort(this.options[this.value].text ,\"" 
                                + (*lsItem)->getControl()->formName() + "\")'";
                            strcpy((*lstItem)->getControl()->contextmenu_, szCmd.c_str());
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createAdv
// 说明 创建高级参数表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createAdv()
{
    // 得到子内容表行数
    int nRow = m_pSubContent->numRows();
    // 创建依靠（高级参数表）
    if(m_pAdvTable == NULL)
    m_pAdvTable = new SVDependTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));

    if(m_pAdvTable)
    {
        m_pAdvTable->setDescription(string(""));
        m_pAdvTable->resetDepend();
        m_pAdvTable->setCodition(string(""));
        m_pAdvTable->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createTitle
// 说明 创建主标题
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createTitle()
{
    // 得到当前行数
    int nRow = numRows();
    // 主标题
    m_pTitle = new WText("", (WContainerWidget*)elementAt(nRow, 0));
    // 设置此行的显示样式表
    elementAt(nRow,0)->setStyleClass("t1title");

    // 下一行
    nRow ++;
    // 创建一个子表（内容表）
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // 创建滚动区
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            // 设置样式表
            pScrollArea->setStyleClass("t1"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        // 设置 内容表 显示样式
        m_pContentTable->setStyleClass("t1");
        // Cell Padding && Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);
        // 设置此行的显示样式表
        elementAt(nRow, 0)->setStyleClass("t1");
        elementAt(nRow, 0)->setContentAlignment(AlignTop);
        
        // 得到内容表的行数
        nRow = m_pContentTable->numRows();
        // 创建新表（子内容表）
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // 设置内容表当前行的对齐方式
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initForm
// 说明 初始化页面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::initForm()
{
	setStyleClass("t1");
    // 标题
    createTitle();

    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        createHelp();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createHelp
// 说明 创建帮助按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHelp()
{
	int nRow = m_pSubContent->numRows();

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));

	nRow ++;

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

		//翻译
		WPushButton * pTranslate = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));	
		if(pTranslate)
		{
	        WObject::connect(pTranslate, SIGNAL(clicked()), this, SLOT(TranslateNew()));	
		    pTranslate->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
		}	

		new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	}

	// 帮助
    WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
    if(pHelp)
    {
        pHelp->setStyleClass("imgbutton");
        pHelp->setToolTip(SVResString::getResString("IDS_Help"));
        WObject::connect(pHelp, SIGNAL(clicked()), this, SLOT(showHelp()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ExChange
// 说明 刷新看效果
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::ExChange()
{
	WebSession::js_af_up  = "setTimeout(\"location.href ='/fcgi-bin/preview.exe?type=0&preview=";
	WebSession::js_af_up += m_szDeviceType;
	WebSession::js_af_up += "'\",1250);  ";
	m_pAppSelf->quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Translate
// 说明 翻译
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::TranslateNew()
{
	string pTranPath = "DeviceMonitorTemplate$deviceid=";
	pTranPath += m_szDeviceType;
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += pTranPath;
	WebSession::js_af_up += "')";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showHelp
// 说明 显示或隐藏帮助信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::showHelp()
{
    m_bShowHelp = !m_bShowHelp;

    list<SVParamItem *>::iterator lstItem;

    // 枚举每一个属性
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        (*lstItem)->m_bError = false;
        (*lstItem)->showHelp(m_bShowHelp); 
    }

    // 高级属性表显示/隐藏帮助
    m_pAdvTable->showHelp(m_bShowHelp);
    //
    if(m_pHostHelp)
    {
        if(m_bShowHelp)
            m_pHostHelp->show();
        else
            m_pHostHelp->hide();

        m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Help"));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createHostName
// 说明 创建设备名称
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHostName(WTable  * pTable)
{
    if(m_pDeviceTitle == NULL)
    {
        // 得到当前行数
        int nRow = pTable->numRows();
        // 说明
        new WText(SVResString::getResString("IDS_Title"), (WContainerWidget*)pTable->elementAt(nRow, 0));
        // 增加（红色*）标识为必添项
        new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

        // 这个表格单元对齐方式为左上对齐
        pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
        pTable->elementAt(nRow, 0)->setStyleClass("cell_10");

        // 创建标题输入框
        m_pDeviceTitle = new WLineEdit("", (WContainerWidget*)pTable->elementAt(nRow, 1));
        if(m_pDeviceTitle)
            m_pDeviceTitle->setStyleClass("Cell_40");

        // 创建帮助文本
        new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
        m_pHostHelp = new WText(SVResString::getResString("IDS_Host_Label_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
        if(m_pHostHelp)
        {
            m_pHostHelp->hide();
            m_pHostHelp->setStyleClass("helps");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ClearData
// 说明 重置数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::ClearData(string &szIndex, WApplication *szApp)
{
	m_pAppSelf = szApp;
    list<SVParamItem *>::iterator lstItem;
    if(!szIndex.empty())
    {// 如果是正在编辑设备
        m_lsDyn.clear();
        // 删除以前的所有数据
        for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            delete (SVParamItem*)(*lstItem);
        m_lsBasicParam.clear();
        
        // 清理基本属性表中的所有内容
        if(m_pGeneral && m_pGeneral->createSubTable())
            m_pGeneral->createSubTable()->clear();

        m_pHostHelp = NULL;
        m_pDeviceTitle = NULL;

        // 不显示帮助信息
        m_bShowHelp = false;
        // 设备类型重置
        m_szDeviceType = szIndex;

        // 枚举基本参数
        enumBaseParam();
        createGeneral();
        createAdv();

        if(m_pSubContent) m_pSubContent->elementAt(0, 0)->show();

    }
    // 
    m_bShowHelp = true;
    showHelp();
    setTitle(m_szDeviceType);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 setTitle
// 说明 根据设备类型设置标题 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::setTitle(string &szDeviceType)
{
    // 打开设备模板
    OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// 成功
        // 主节点
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szName("");
            // 设备类型的显示名称
            if(!FindNodeValue(node, "sv_label", szName))
                FindNodeValue(node, "sv_name", szName);
            else
                szName = SVResString::getResString(szName.c_str());

            m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + " " + szName + " " +SVResString::getResString("IDS_Device"));
        }
        // 关闭设备模板
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
