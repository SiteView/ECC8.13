#include "adddevice2nd.h"
#include "showtable.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../../base/des.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char *szMsg);
extern void WriteLogFile(const char *pszFile, const char *pszMsg);

#include "../base/basetype.h"

typedef bool(ListDevice)(const char* szQuery, char* szReturn, int &nSize);

#include "resstring.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDevice::SVDevice(WContainerWidget * parent, CUser *pUser, string szIDCUser, string szIDCPwd, string szDeviceType):
WTable(parent)
{
    m_bShowHelp = false;                            // 是否显示帮助
    m_pGeneral = NULL;                              // 基础信息参数
    m_pDeviceTitle = NULL;                          // 高级信息标题
    m_pContentTable = NULL;                         // 内容表
    m_pSaveMonitor = NULL;                          // 保存所选监测器按钮
 
    m_pSubContent = NULL;                           // 子内容表
    m_pAdvTable = NULL;                             // 高级参数表
    m_pSVUser = pUser;                              // 当前用户权限
    m_pQuickAdd = NULL;
    // 保存设备 返回 取消 枚举动态参数 测试
    m_pSave = m_pBack = m_pCancel = m_pListDynBtn = m_pTest = NULL;


    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;

    //loadCondition();                                // 加载阀值条件

    // 绑定
    connect(&m_mapMinitor, SIGNAL(mapped(int)), this, SLOT(selAllByMonitorType(int)));

    initForm();                                     // 初始化
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumBaseParam
// 说明 枚举设备模板中定义的基本属性
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::enumBaseParam()
{
    // 重置
    m_szQuickAdd = "";
	m_szQuickAddSel = "";
    m_szDllName = "";
    m_szFuncName = "";
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
        // 主节点
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            FindNodeValue(node, "sv_dll", m_szDllName);             // 动态连接库名称
            FindNodeValue(node, "sv_func", m_szFuncName);           // 函数名称
            FindNodeValue(node, "sv_quickadd", m_szQuickAdd);       // 快速添加
			FindNodeValue(node, "sv_quickaddsel", m_szQuickAddSel); // 快速添加缺省选择
            FindNodeValue(node, "sv_network", m_szNetworkset);      // 是否是网络设备
            if(m_szNetworkset.empty())
                m_szNetworkset = "false";
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
                    m_bHasDynamic = true;
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
// 函数 createOperate
// 说明 创建操作
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createOperate()
{
    // 得到当前行数
    int nRow = numRows();
    // 创建 m_pBack 按钮
    if(!m_pBack)
    {
        m_pBack = new WPushButton(SVResString::getResString("IDS_Back_One_Step"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pBack)
        {
            // 设置 Tooltip
            m_pBack->setToolTip(SVResString::getResString("IDS_Back_Device_List_Tip"));
            // 绑定 click 事件
            WObject::connect(m_pBack, SIGNAL(clicked()), "showbar();", this, SLOT(Preview()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 创建测试按钮
    if(!m_pTest)
    {
        // 与上一按钮隔开一定距离
        new WText("&nbsp;",this->elementAt(nRow,0));
        m_pTest = new WPushButton(SVResString::getResString("IDS_Test"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pTest)
        {
            // 设置 Tooltip
            m_pTest->setToolTip(SVResString::getResString("IDS_Curent_Test_Tip"));
            // 绑定 click 事件
            WObject::connect(m_pTest, SIGNAL(clicked()), "showbar();", this, SLOT(testDevice()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 创建保存按钮
    if(!m_pSave)
    {
        // 与上一按钮隔开一定距离
        new WText("&nbsp;",this->elementAt(nRow,0));
        m_pSave = new WPushButton(SVResString::getResString("IDS_Add"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pSave)
        {
            // 设置 Tooltip
            m_pSave->setToolTip(SVResString::getResString("IDS_Add_Device_Tip"));
            // 绑定 click 事件
            WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(Save()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 创建 取消（放弃）按钮
    if(!m_pCancel)
    {
        // 与上一按钮隔开一定距离
        new WText("&nbsp;",this->elementAt(nRow,0));
        m_pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pCancel)
        {
            // 设置 Tooltip
            m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
            // 绑定 click 事件
            WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 创建列举动态参数按钮
    if(!m_pListDynBtn)
    {
        m_pListDynBtn = new WPushButton("list dyn", (WContainerWidget*)elementAt(nRow, 0));
        if(m_pListDynBtn)
        {
            // 隐藏此按钮不在界面上显示出来
            m_pListDynBtn->hide();
            // 绑定 click 事件
            WObject::connect(m_pListDynBtn, SIGNAL(clicked()), "showbar();", this, SLOT(listDynParam()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // 设置本行的对齐属性（底部居中对齐）
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
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
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        // 设置 内容表 显示样式
        m_pContentTable->setStyleClass("t5");
        // Cell Padding && Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);
        // 设置此行的显示样式表
        elementAt(nRow, 0)->setStyleClass("t7");
        
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
    setStyleClass("t5");
    // 标题
    createTitle();

    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        createHelp();
    }

    // 创建操作
    createOperate();
    // 创建快速添加操作
    createQuickAddOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initQuickAdd
// 说明 初始化快速添加
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::initQuickAdd()
{
    // 添加监测器模板
    AddMonitorTempList();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Cancel
// 说明 返回主界面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::Cancel()
{
    // 重置正修改的索引
    m_szEditIndex = "";
    // 触发返回主界面事件
    emit backMain();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Preview
// 说明 返回设备模板列表重新选择设备类型
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::Preview()
{
    emit backPreview();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Save
// 说明 保存当前内容
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::Save()
{
    list<SVParamItem *>::iterator lstItem;
    string szDeviceHost("");
    string szDescription(""), szDepends(""), szCondition("");

	m_bChanged = false;
    m_szQueryString = "";
    m_szDeviceID = "";
    if(m_pDeviceTitle)
        m_szDeviceName = m_pDeviceTitle->text();

    bool bError = false;

    // 判断设备名称是否为空
    if(m_szDeviceName.empty())
    {// 显示错误信息 
DeviceNameEmpty:
        if(m_pHostHelp)
        {
            m_pHostHelp->setStyleClass("errors");
            m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Error"));
            m_pHostHelp->show();
            m_pGeneral->ShowSubTable();
        }
        bError = true;
    }
    else
    {
        // 去掉左右空格
        m_szDeviceName = strtriml(m_szDeviceName.c_str());
        m_szDeviceName = strtrimr(m_szDeviceName.c_str());
        // 名称是否为空
        if(m_szDeviceName.empty())
            goto DeviceNameEmpty;
        // 隐藏/显示帮助信息
        if(m_pHostHelp)
        {
            m_pHostHelp->setStyleClass("helps");
            m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Help"));
            if(m_bShowHelp)
                m_pHostHelp->show();
            else
                m_pHostHelp->hide();
        }
    }

    // 判断属性参数是否填写正确
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        if(!(*lstItem)->checkValue())
        {
            if(m_pGeneral)
                m_pGeneral->ShowSubTable();
            bError = true;
        }
    }

    // 是否发生错误
    if(bError)
    {
        WebSession::js_af_up = "hiddenbar();";
        return;
    }

    // 高级属性表是否创建成功
    if(m_pAdvTable)
    {
        // 描述
        m_pAdvTable->getDescription(szDescription);
        // 依靠
        m_pAdvTable->getDepend(szDepends);
        // 依靠条件
        m_pAdvTable->getCodition(szCondition);
    }

    OBJECT objDevice = INVALID_VALUE;
    if(m_szEditIndex.empty())
    {// 是否正在编辑设备
        if(m_szNetworkset == "true")
        {// 待添加设备是网络设备
            // 得到当前已使用网络设备总数
            int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd); 
            // 加1
            nNetworkCount ++;
            // 判断是否超点
            if(!checkNetworkPoint(nNetworkCount))
            {
                // 显示错误信息
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                return;
            }
        }
        // 创建一个设备
        objDevice = CreateEntity();
    }
    else
	{// 正在编辑设备
        // 打开设备
        objDevice = GetEntity(m_szEditIndex, m_szIDCUser, m_szIDCPwd);
        // 判断依靠条件是否被修改
		if(m_pAdvTable && m_pAdvTable->isDependChange())
			m_bChanged = true;
	}
    // 创建/打开设备是否成功
    if(objDevice != INVALID_VALUE)
    {
        // 得到主节点
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
			map<string, string, less<string> >::iterator paramItem;
            // 增加每一个属性
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                string szValue(""), szName("");
                (*lstItem)->getStringValue(szValue); 
                (*lstItem)->getName(szName);
				if(!m_bChanged)
				{
					paramItem = m_DeviceParam.find(szName);
					if(paramItem != m_DeviceParam.end())
						if(paramItem->second != szValue)
							m_bChanged = true;
				}
                // 在主节点下添加属性
                if(!AddNodeAttrib(mainnode, szName, szValue))
                    bError = true;
            }
            // 是否失败
            if(!bError)
            {
                // 添加 名称 设备类型 描述 依靠 依靠条件 是否是网络设备 属性
                if(AddNodeAttrib(mainnode, "sv_name", m_szDeviceName) &&  AddNodeAttrib(mainnode, "sv_devicetype", m_szDeviceType) &&
                    AddNodeAttrib(mainnode, "sv_description", szDescription) && AddNodeAttrib(mainnode, "sv_dependson", szDepends) &&
                    AddNodeAttrib(mainnode, "sv_dependscondition", szCondition) && AddNodeAttrib(mainnode, "sv_network", m_szNetworkset))
                {
                    if(m_szEditIndex.empty())
                    {// 不是正在编辑设备
                        // 根据父组的禁止方式决定当前设备是否被禁止
                        saveDisableByParent(mainnode, Tree_GROUP, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
                        // 添加新的设备
                        string szRealIndex = AddNewEntity(objDevice, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
                        if(!szRealIndex.empty())
                        {// 添加成功
                            m_szDeviceID = szRealIndex;
                            // 得到真实索引
                            int nIndex = FindIndexByID(szRealIndex);
                            char szIndex[16] = {0};
                            sprintf(szIndex, "%d", nIndex);
                            // 添加 显示索引 属性
                            AddNodeAttrib(mainnode, "sv_index", szIndex);
                            // 添加权限
                            if(m_pSVUser && !m_pSVUser->isAdmin())
                                m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_DEVICE);
                            // 触发 成功添加设备 事件
                            emit AddDeviceSucc(m_szDeviceName,szRealIndex);

                            // 得到每一个参数
                            list<SVParamItem *>::iterator lstItem;
                            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
                            {
                                if((*lstItem)->isRun())
                                {
                                    if(!(*lstItem)->checkValue())
                                    {
                                        m_szQueryString = "";
                                        break;
                                    }
                                    string szValue(""), szName("");

                                    (*lstItem)->getStringValue(szValue);
                                    (*lstItem)->getName(szName);
                                    if((*lstItem)->isPassword())
                                    {
                                        char szOutput[512] = {0};
                                        Des des;
                                        if(des.Decrypt(szValue.c_str(), szOutput))
                                            szValue = szOutput;
                                    }
                                    m_szQueryString = m_szQueryString + szName + "=" + szValue + "\v";
                                }
                            }
                            // 删除内容表中所有内容
                            if(m_pGeneral) m_pGeneral->hide();
                            if(m_pAdvTable) m_pAdvTable->hide();
                            if(m_pSubContent) m_pSubContent->elementAt(0, 0)->hide();
                            if(m_pQuickAdd) m_pQuickAdd->show();
                            // 隐藏 包含 保存按钮的行
                            if(m_pSave)
                                ((WTableCell*)m_pSave->parent())->hide();
                            // 显示 快速添加监测器操作
                            if(m_pCancelSaveMonitor)
                                ((WTableCell*)m_pCancelSaveMonitor->parent())->show();
                            // 设置主标题文字
                            m_pTitle->setText(SVResString::getResString("IDS_Quick_Add_Monitor_Title"));
                            // 是否支持快速添加
                            if(!m_szQuickAdd.empty())
                            {
                                // 快速添加
                                initQuickAdd();
                            }
                            else
                            {// 不支持快速添加
                                // 触发 进入新添加设备 属性
                                emit EnterNewDevice(m_szDeviceID);
                            }
                       }
                    }
                    else
                    {// 正在编辑设备
                        // 提交
                        if(SubmitEntity(objDevice, m_szIDCUser, m_szIDCPwd))
                        {// 提交成功、
                            // 触发 成功修改设备 事件
                            emit EditDeviceSucc(m_szDeviceName, m_szEditIndex);
                        }
						if(m_bChanged)
						{
                            string szQueueName(getConfigTrackQueueName(m_szEditIndex));
						    CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                            if(!::PushMessage(szQueueName, "ENTITY:UPDATE", m_szEditIndex.c_str(), 
                                                static_cast<unsigned int>(m_szEditIndex.length()) + 1, m_szIDCUser, m_szIDCPwd))
								PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
						}
                        // 调用此函数 返回主页面
						Cancel();
                    }
                }
            }
        }
    }
    // 重置正在编辑设备索引值
    m_szEditIndex = "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createHelp
// 说明 创建帮助按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHelp()
{
    // 帮助
    int nRow = m_pSubContent->numRows();
    WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
    if(pHelp)
    {
        pHelp->setStyleClass("imgbutton");
        pHelp->setToolTip(SVResString::getResString("IDS_Help"));
        WObject::connect(pHelp, SIGNAL(clicked()), "showbar();", this, SLOT(showHelp()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
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
    WebSession::js_af_up = "hiddenbar();";
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
void SVDevice::ClearData(string &szIndex)
{
    // 重置是否是网络设备
    m_szNetworkset = "";
    if(m_pAdvTable)
        m_pAdvTable->setUserID(FindSEID(m_szParentIndex));

    list<SVParamItem *>::iterator lstItem;
    m_szEditIndex = "";
    if(!szIndex.empty())
    {// 如果是正在编辑设备
        m_bHasDynamic = false;
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
        // 函数名重置
        m_szFuncName = "";
        m_szDllName = "";

        // 枚举基本参数
        enumBaseParam();
        createGeneral();
        createAdv();

        if(m_pSubContent) m_pSubContent->elementAt(0, 0)->show();

        if(m_pQuickAdd == NULL)
        {
            int nRow = m_pSubContent->numRows();
            m_pQuickAdd = new WTable(m_pSubContent->elementAt(nRow, 0));
        }
        if(m_pQuickAdd)
        {
            m_pQuickAdd->hide();
            m_pQuickAdd->setStyleClass("t3");
            m_pQuickAdd->clear();
        }

        // 显示操作按钮行
        if(m_pSave)
            ((WTableCell*)m_pSave->parent())->show();
        // 隐藏快速添加按钮行
        if(m_pCancelSaveMonitor)
            ((WTableCell*)m_pCancelSaveMonitor->parent())->hide();

        // 测试按钮是否创建成功
        if(m_pTest)
        {
            // 隐藏/显示测试按钮
            m_pTest->show();
            if(m_szDllName.empty() || m_szFuncName.empty())
                m_pTest->hide();
        }
    }
    // 
    m_bShowHelp = true;
    showHelp();

    // 显示返回设备模板按钮
    if(m_pBack) m_pBack->show();
    if(m_pSave) 
    {
        m_pSave->setText(SVResString::getResString("IDS_Add"));
        m_pSave->setToolTip(SVResString::getResString("IDS_Add_Device_Tip"));
    }
    if(m_pCancel)
    {
        m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
        setTitle(m_szDeviceType);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditDeviceByID
// 说明 根据设备ID（索引）编辑设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::EditDeviceByID(string &szIndex)
{
    // 待编辑设备所以是否为空
    if(szIndex.empty())
        return;
	
    // 清理 设备参数
	m_DeviceParam.clear();

    // 打开设备
    OBJECT objDevice = GetEntity(szIndex, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// 成功
        // 主节点
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            // 设备类型
            string szDeviceType("");
            list<SVParamItem *>::iterator lstItem;
            if(FindNodeValue(mainnode, "sv_devicetype", szDeviceType))
            {
                // 根据设备类型清理并重构数据
                ClearData(szDeviceType);
                // 待编辑设备索引赋值
                m_szEditIndex = szIndex;
                if(m_pAdvTable)
                    m_pAdvTable->setUserID(FindSEID(m_szEditIndex));
                // 隐藏返回设备模板列表按钮
                m_pBack->hide();
                // 设置文本、tooltip
                m_pSave->setText(SVResString::getResString("IDS_Save"));
                m_pSave->setToolTip(SVResString::getResString("IDS_Save_Tip"));
                m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
                m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Edit_Device_Tip"));

                // , 名称， 描述，依靠条件，依靠
                string szLabel(""), szName("") , szDesc(""), szCondition(""), szDepends("");
                FindNodeValue(mainnode, "sv_name", szName);
                FindNodeValue(mainnode, "sv_description", szDesc);
                FindNodeValue(mainnode, "sv_dependscondition", szCondition);
                FindNodeValue(mainnode, "sv_dependson", szDepends);

                if(m_pAdvTable)
                {
                    m_pAdvTable->setDescription(szDesc);
                    m_pAdvTable->setDepend(szDepends);
                    m_pAdvTable->setCodition(szCondition);
                }
                // 设置设备名称显示文本
                if(m_pDeviceTitle)
                    m_pDeviceTitle->setText(szName);
                // 重置主标题
                if(m_pTitle)
                    m_pTitle->setText( SVResString::getResString("IDS_Edit") + szName + SVResString::getResString("IDS_Device"));

                // 重置每个属性的参数
                for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
                {  
                    string szName(""), szValue("");
                    (*lstItem)->getName(szName);
                    FindNodeValue(mainnode, szName, szValue);
                    //int nPos = static_cast<int>(szValue.find("\\", 0));
                    //while (nPos >= 0)
                    //{
                    //    szValue = szValue.substr(0, nPos ) + "\\" + 
                    //        szValue.substr(nPos, szValue.length() - nPos);
                    //    nPos += 2;
                    //    nPos = static_cast<int>(szValue.find("\\", nPos));
                    //}
                    (*lstItem)->setStringValue(szValue);
					m_DeviceParam[szName] = szValue;
                }                
            }
        }
    }
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

            // 设置主标题栏文字
            if(szName.empty())
            {
                if(m_szEditIndex.empty())
                    m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device"));
                else
                    m_pTitle->setText(SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Device"));
            }
            else
            {
                if(m_szEditIndex.empty())
                    m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + szName);
            }
        }
        // 关闭设备模板
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 testDevice
// 说明 测试设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::testDevice()
{
    list<SVParamItem *>::iterator lstItem;

    string szQuery("");
    // 枚举每一个属性的参数
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        // 是否是运行时必要属性参数
        if((*lstItem)->isRun())
        {
            // 检查值是否正确
            if(!(*lstItem)->checkValue())
            {
                szQuery = "";
                break;
            }
            // 得到属性参数名称和值
            string szValue(""), szName("");
            (*lstItem)->getName(szName);
            (*lstItem)->getStringValue(szValue);
            // 是否是密文
            if((*lstItem)->isPassword())
            {// 是
                //解密
                char szOutput[512] = {0};
                Des des;
                if(des.Decrypt(szValue.c_str(), szOutput))
                    szValue = szOutput;
            }
            // 编码
            szValue = url_Encode(szValue.c_str());
            szQuery = szQuery + szName + "=" + szValue + "&";
        }
    }
    // 如果可以测试则显示设备测试界面
    if(!szQuery.empty())
    {
        szQuery = szQuery + "devicetype=" + m_szDeviceType + "&seid=";
        if(m_szEditIndex.empty())
            szQuery += FindSEID(m_szParentIndex);
        else
            szQuery += FindSEID(m_szEditIndex);

        szQuery = "showtestdevice('testdevice.exe?" + szQuery +"');" ;
        PrintDebugString(szQuery.c_str());
    }
    szQuery = "hiddenbar();" + szQuery;
    WebSession::js_af_up = szQuery;   
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 listDynParam
// 说明 枚举动态数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::listDynParam()
{
    listItem lstItem;
    string szQuery("");
    // 枚举每个动态属性的动态数据
    for(lstItem = m_lsDyn.begin(); lstItem != m_lsDyn.end(); lstItem ++)
        (*lstItem)->enumDynValue(szQuery, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 requesDynData
// 说明 请求动态数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::requesDynData()
{
    // 枚举动态数据按钮是否被成功创建
    if(m_pListDynBtn)
    {
        // 得到 click 绑定
        string szCmd = m_pListDynBtn->getEncodeCmd("xclicked()");
        if(!szCmd.empty() && m_bHasDynamic)
            WebSession::js_af_up = "update('" + szCmd + "');";
        else
            WebSession::js_af_up = "hiddenbar();";
    }
    else
            WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createQuickAddOperate
// 说明 创建快速添加操作按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createQuickAddOperate()
{
    // 得到当前行数
    int nRow = numRows();
    // 创建 保存所选按钮
    WPushButton *m_pSaveMonitor = new WPushButton(SVResString::getResString("IDS_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pSaveMonitor)
    {
        // tooltip
        m_pSaveMonitor->setToolTip(SVResString::getResString("IDS_Save_Sel_Monitor_Tip"));
        // 绑定 click 时间
        WObject::connect(m_pSaveMonitor, SIGNAL(clicked()), "showbar();", this, SLOT(saveAllSelMonitors()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    // 与一控件隔开一定距离
    new WText("&nbsp;",this->elementAt(nRow,0));
    // 取消添加监测器按钮
    m_pCancelSaveMonitor = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pCancelSaveMonitor)
    {
        // tooltip
        m_pCancelSaveMonitor->setToolTip(SVResString::getResString("IDS_Cancel_Add_Monitor_Tip"));
        // 绑定 click
        WObject::connect(m_pCancelSaveMonitor, SIGNAL(clicked()), "showbar();", this, SLOT(enterDevice()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    // 枚举动态数据 按钮
    m_pListDynData = new WPushButton("list dyn", (WContainerWidget*)elementAt(nRow, 0));
    if(m_pListDynData)
    {
        // 隐藏
        m_pListDynData->hide();
        // 绑定 click
        WObject::connect(m_pListDynData, SIGNAL(clicked()), "showbar();", this, SLOT(listDynData()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    // 当前行的对齐方式 底部居中
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    // 隐藏当前行
    //GetRow(nRow)->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddMonitorTempList
// 说明 增加根据监测器模板创建候选监测器列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::AddMonitorTempList()
{
    m_lsMonitorTemplet.clear();
    m_svValueList.clear();

    list<string> lstMonitors;
    // 快速添加字符不为空 且 成功 解析成功
    if(!m_szQuickAdd.empty() && sv_split(m_szQuickAdd.c_str(), ",", lstMonitors, false) > 0)
    {
        list<string>::iterator lstItem;
        int nPos = 0;
        bool bSelect;
        // 枚举每一监测器模板
        for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
        {
            // 缺省是否选择
			bSelect = false;
			nPos = static_cast<int>(m_szQuickAddSel.find((*lstItem).c_str()));
			if(nPos >= 0)
			{
				const char *pValue = m_szQuickAddSel.c_str();
				if( *(pValue + nPos +(*lstItem).length()) == ',' || *(pValue + nPos +(*lstItem).length()) == '\0')
					bSelect = true;
			}
            // 根据监测器模板ID枚举重要属性并进行记录
            int nMonitorID = atoi((*lstItem).c_str());
            OBJECT objMonitor = GetMonitorTemplet(nMonitorID, m_szIDCUser, m_szIDCPwd);
            if(objMonitor != INVALID_VALUE)
            {
                MAPNODE node = GetMTMainAttribNode(objMonitor);
                monitor_templet monitor;
                monitor.nMonitorID = nMonitorID;
				monitor.bSel = bSelect;
                // 名称 描述 扩展动态库（枚举动态数据使用，缺省使用sv_dll）
                // 扩展函数明
                // 扩展保存
                if(!FindNodeValue(node, "sv_label", monitor.szName))
                    FindNodeValue(node, "sv_name", monitor.szName);
                else
                    monitor.szName = SVResString::getResString(monitor.szName.c_str());

                if(FindNodeValue(node, "sv_description", monitor.szLabel))
                    monitor.szLabel = SVResString::getResString(monitor.szLabel.c_str());

                FindNodeValue(node, "sv_extradll", monitor.szDllName);
                if(monitor.szDllName.empty())
                    FindNodeValue(node, "sv_dll", monitor.szDllName);
                FindNodeValue(node, "sv_extrafunc", monitor.szFuncName);
                FindNodeValue(node, "sv_extrasave", monitor.szSaveName);
                list<monitor_templet>::iterator lstItem;
                // 子内容表是否成功创建
                if(m_pQuickAdd)
                {
                    // 子内容表的当前行数
                    int nRow = m_pQuickAdd->numRows();
                    WCheckBox *pCheck = NULL;
                    // 是否需要使用动态数据
                    if(!monitor.szDllName.empty() && !monitor.szFuncName.empty())
                    {// 需要
                        // 创建全选 checkbox
                        WCheckBox* pSelAll = new WCheckBox("", m_pQuickAdd->elementAt(nRow, 0));
                        if(pSelAll)
                        {
                            // tooltip
                            pSelAll->setToolTip(SVResString::getResString("IDS_All_Select"));
                            // 是否选择
                            pSelAll->setChecked(bSelect);
                            // 绑定 click
                            WObject::connect(pSelAll, SIGNAL(clicked()), "showbar();", &m_mapMinitor, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                            m_mapMinitor.setMapping(pSelAll, nMonitorID);
                        }
                        // 监测描述文本
                        new WText(monitor.szLabel, m_pQuickAdd->elementAt(nRow, 0));
                        // 设置此行的显示样式表
                        m_pQuickAdd->GetRow(nRow)->setStyleClass("t2title");
                        // 扩展保存属性参数名称是否为空
                        if(monitor.szSaveName.empty())
                        {
                            // 显示错误信息
                            new WText(SVResString::getResString("IDS_Monitor_Templet_Error"), m_pQuickAdd->elementAt(nRow + 1, 0));
                        }
                        else
                        {
                            // 创建子表以便能放置动态数据
                            monitor.pTable = new WTable(m_pQuickAdd->elementAt(nRow + 1, 0));
                            if(monitor.pTable)
                            {
                                monitor.pTable->setStyleClass("t3");
                                new WText("loading...", monitor.pTable->elementAt(0, 0));
                            }
                        }
                    }
                    else
                    {
                        // 监测描述文本
                        new WText(monitor.szLabel, m_pQuickAdd->elementAt(nRow, 0));
                        // 设置此行的显示样式表
                        m_pQuickAdd->GetRow(nRow)->setStyleClass("t2title");
                        // 在下一行内创建显示文字为监测器描述文字的checkbox
                        pCheck = new WCheckBox(monitor.szName, m_pQuickAdd->elementAt(nRow + 1, 0));							
                    }
                    
                    if(pCheck)
                    {// 创建成功
                        // 是否选择
						pCheck->setChecked(bSelect);
                        char szIndex[32] = {0};
                        sprintf(szIndex, "%d", nMonitorID);
                        SVTableCell svCell;
                        svCell.setType(adCheckBox);
                        svCell.setValue(pCheck);
                        // 记录
                        m_svValueList.WriteCell((nRow + 1) * 10, 0, svCell);
                        SVTableRow *pRow = m_svValueList.Row((nRow + 1) * 10);
                        if (pRow)
                            pRow->setTag(nMonitorID);
                    }
                }
                m_lsMonitorTemplet.push_back(monitor);

                CloseMonitorTemplet(objMonitor);
            }
        }
    }
    string szCmd = "hiddenbar();";
    if(m_pListDynData)
        if(!m_pListDynData->getEncodeCmd("xclicked()").empty())
            szCmd = "update('" + m_pListDynData->getEncodeCmd("xclicked()") + "');";

    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddDynData
// 说明 增加显示动态数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::AddDynData(WTable * pTable, const char* pszQuery, const int &nQuerySize, const int &nMonitorID, 
                            const string &szDllName, const string &szFuncName, const string &szSaveName, const bool &bSel)
{
// 是否是在Windows 平台下运行
    bool bGetDyn = false;
    char szReturn [svBufferSize] = {0};
    int nSize = sizeof(szReturn);

    if(FindSEID(m_szDeviceID) == "1")
    {
#ifdef WIN32
    string szDllName(makeDllName(szDllName));
    string szMsg = "Dll Name: " + szDllName + " Function Name: " + szFuncName;
    PrintDebugString(szMsg.c_str());
    // 打开动态链接库
    HINSTANCE hDll = LoadLibrary(szDllName.c_str());
    if (hDll)
    {
        // 获得函数
        ListDevice* func = (ListDevice*)GetProcAddress(hDll, szFuncName.c_str());
        if (func && szReturn)
        {            
            bGetDyn = (*func)(pszQuery, szReturn, nSize);
        }
        // 关闭动态链接库
        FreeLibrary(hDll);
    }
#else
#endif
    }
    else
    {
        bGetDyn = ReadWriteDynQueue(m_szDeviceID, szDllName, szFuncName, pszQuery, nQuerySize, szReturn, nSize, m_szIDCUser, m_szIDCPwd);
    }

    if(bGetDyn)
    {
        int nRow = pTable->numRows();
        char *pos = strstr(szReturn, "error");
        if(pos == NULL)
        {
            pos = szReturn;
            map<string , string, less<string> > dynData;
            while(*pos != '\0')
            {
                int nSize = static_cast<int>(strlen(pos));
                char *pPosition = strchr(pos, '=');
                if(pPosition)
                {
                    (*pPosition) = '\0';
                    ++pPosition;
                    dynData[pPosition] = pos;
                }
                pos = pos + nSize + 1;
            }
            
            // 为每一个动态数据创建一行
            int nParentRow = nMonitorID * 10;
            map<string , string, less<string> >::iterator it;
            for(it = dynData.begin(); it != dynData.end(); it++)
            {
                WCheckBox *pCheck = new WCheckBox(it->first, pTable->elementAt(nRow, 0));
                if(pCheck)
                {
					pCheck->setChecked(bSel);
                    SVTableCell svCell;
                    svCell.setType(adCheckBox);
                    svCell.setValue(pCheck);
                    svCell.setProperty(it->second.c_str());
                    m_svValueList.WriteCell(nParentRow + nRow, 0, svCell);
                    SVTableRow *pRow = m_svValueList.Row(nParentRow + nRow);
                    if (pRow)
                    {
                        pRow->setProperty(szSaveName.c_str());
                        pRow->setTag(nMonitorID);
                    }
                }
                // 设置行显示样式
                if((nRow + 1) % 2 == 0)
                    pTable->GetRow(nRow)->setStyleClass("tr1");
                else
                    pTable->GetRow(nRow)->setStyleClass("tr2");
                nRow ++;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 listDynData
// 说明 列举动态数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::listDynData()
{ 
    // 枚举每个监测器模板
    list<monitor_templet>::iterator lstItem;
    for(lstItem = m_lsMonitorTemplet.begin(); lstItem != m_lsMonitorTemplet.end(); lstItem ++)
    {      
        char szTpl [32] = {0};
        // 配置动态调用参数
        int nLen = sprintf(szTpl, "_TemplateID=%d\v", (*lstItem).nMonitorID);
        string szQuery = szTpl;
        szQuery += m_szQueryString;
        int nSize = static_cast<int>(szQuery.length()) + 2;
        char *pszQueryString = new char[nSize];
        if(pszQueryString)
        { 
            memset(pszQueryString, 0 , nSize);
            strcpy(pszQueryString , szQuery.c_str());
            PrintDebugString(pszQueryString);
            char *pPos = pszQueryString;
            while((*pPos) != '\0' )
            {
                if((*pPos) == '\v')
                    (*pPos) = '\0';
                pPos ++;
            }
            if((*lstItem).pTable)
            {
                (*lstItem).pTable->clear();
                AddDynData((*lstItem).pTable, pszQueryString,  nSize, (*lstItem).nMonitorID, (*lstItem).szDllName, 
                    (*lstItem).szFuncName, (*lstItem).szSaveName, (*lstItem).bSel);
            }
            delete []pszQueryString;
        } 
    }

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enterDevice
// 说明 进入设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::enterDevice()
{ 
    // 触发 进入新添加设备 事件
    if(!m_szDeviceID.empty())
        emit EnterNewDevice(m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveAllSelMonitors
// 说明 保存所有已选的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::saveAllSelMonitors()
{
	string strQuickAddMonitorName("");
	//获取设备的名称
    string szEntityName ("");
    // 打开设备
    OBJECT objEntity = GetEntity(m_szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objEntity != INVALID_VALUE)
    {// 打开成功
        // 主节点
        MAPNODE devnode = GetEntityMainAttribNode(objEntity);
        // 得到设备显示名称
        if(devnode != INVALID_VALUE)
        {
            FindNodeValue(devnode, "sv_name", szEntityName);
        }
        // 关闭设备
        CloseEntity(objEntity);
    }

    irow it;
    int nPos = 0;
    // 枚举每一条数据
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        // 当前数据是否被选择
        SVTableCell *pCell =  (*it).second.Cell(0);
        if(pCell && pCell->Type() == adCheckBox)
        {
            string szText = ((WCheckBox*)pCell->Value())->label()->text();
            nPos = static_cast<int>(szText.find(SVResString::getResString("IDS_Monitor_Point_Lack_Tip")));
            if(nPos >= 0)
                szText = szText.substr(0, nPos);

            ((WCheckBox*)pCell->Value())->label()->setText(szText);
            if(((WCheckBox*)pCell->Value())->isChecked())
            {// 选择状态
                string szLable = ((WCheckBox*)pCell->Value())->label()->text();
                // 保存监测器
                if(!saveMonitor((*it).second.getTag(),(*it).second.getProperty(), pCell->Property(), szLable.c_str()))
                {// 保存失败， 显示错误信息
                    ((WCheckBox*)pCell->Value())->label()->setText(((WCheckBox*)pCell->Value())->label()->text() + 
                        SVResString::getResString("IDS_Monitor_Point_Lack_Tip"));
                    ((WCheckBox*)pCell->Value())->label()->setStyleClass("errortip");
                    if(m_pSaveMonitor)
                        m_pSaveMonitor->setEnabled(false);
                    return;
				}
                // 
				strQuickAddMonitorName += szEntityName;
				strQuickAddMonitorName += ":";
				strQuickAddMonitorName += szLable;
 				strQuickAddMonitorName += "  ";                
            }
        }
    }
    if(!m_szDeviceID.empty())
        emit EnterNewDevice(m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitor
// 说明 保存监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitor(int nMonitorID, const char* pszSaveName, const char *pszExtraParam, const char *pszExtraLable)
{
    // 创建监测器
    OBJECT objMonitor = CreateMonitor();
    // 打开监测器模板
    OBJECT objMonitorTmp = GetMonitorTemplet(nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE && objMonitorTmp != INVALID_VALUE)
    {// 创建监测器和打开模板都成功
        // 得到监测器模板主节点
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        // 得到监测器主节点
        MAPNODE nodeTmp  = GetMTMainAttribNode(objMonitorTmp);
        if(mainnode != INVALID_VALUE && nodeTmp != INVALID_VALUE)
        {
            char chMTID [8] = {0};
            string szName (""), szLabel (""), szPoint ("");;
            string szMonitorName ("");
            if(!FindNodeValue(nodeTmp, "sv_label", szMonitorName))
                FindNodeValue(nodeTmp, "sv_name", szMonitorName);
            else
               szMonitorName  = SVResString::getResString(szMonitorName.c_str());
            if(m_szNetworkset != "true")
            {// 不是网络设备
                FindNodeValue(nodeTmp, "sv_intpos", szPoint);
                
                if(szPoint.empty())
                    szPoint = "1";
                // 已用监测器点数
                int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);

                int nPoint = atoi(szPoint.c_str());
                if(nPoint <= 0)
                    nPoint = 0;
                nMonitorCount += nPoint;
                // 检测是否超点
                if(!checkMonitorsPoint(nMonitorCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            else
            {// 网络设备
                // 已用网络设备
                // 网络设备已用点数
                int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd, m_szDeviceID);
                // 检测是否超点
                if(!checkNetworkPoint(nNetworkCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            // 是否是网络设备，是网络设备监测点数置为零
            if(m_szNetworkset == "true")
                szPoint = "0";
            sprintf(chMTID, "%d", nMonitorID);
            if(pszExtraLable && strlen(pszExtraLable) > 0 && szMonitorName.compare(pszExtraLable) != 0)
                szName = szMonitorName + ":"  + pszExtraLable;
            else if(pszExtraParam && strlen(pszExtraParam) > 0)
                szName = szMonitorName + ":"  + pszExtraParam;
            else
                szName = szMonitorName;
            AddNodeAttrib(mainnode, "sv_name", szName);
            AddNodeAttrib(mainnode,"sv_monitortype", chMTID);
            AddNodeAttrib(mainnode, "sv_intpos", szPoint);
            saveDisableByParent(mainnode, Tree_DEVICE, m_szDeviceID, m_szIDCUser, m_szIDCPwd);
        }
        // 监测器基本参数
        saveMonitorBaseParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // 监测器高级参数
        saveMonitorAdvParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // 监测器监测阀值
        saveMonitorCondition(objMonitor, objMonitorTmp);
        // 添加新的监测器
        string szRealIndex = AddNewMonitor(objMonitor, m_szDeviceID, m_szIDCUser, m_szIDCPwd);
        if(!szRealIndex.empty())
        {// 成功添加
            // 设置显示顺序
            int nIndex = FindIndexByID(szRealIndex);
            char szIndex[16] = {0};
            sprintf(szIndex, "%d", nIndex);
            AddNodeAttrib(mainnode, "sv_index", szIndex);
            
            // 创建监测数据表
            InsertTable(szRealIndex, nMonitorID, m_szIDCUser, m_szIDCPwd);
            // 配置权限
            if(m_pSVUser && !m_pSVUser->isAdmin())
                m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_MONITOR);
        }
    }
    // 关闭监测器
    if(objMonitor != INVALID_VALUE)
        CloseMonitor(objMonitor);
    // 关闭监测器模板
    if(objMonitorTmp != INVALID_VALUE)
        CloseMonitorTemplet(objMonitorTmp);

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitorAdvParam
// 说明 保存高级参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitorAdvParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // 监测器高级节点
    MAPNODE objMonitorNode = GetMonitorAdvanceParameterNode(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // 枚举监测器模板的每一条高级属性
        if( FindMTAdvanceParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // 参数名称 缺省值 计算方式
                string szName (""), szValue (""), szAccValue ("");
                FindNodeValue(objNode, "sv_name", szName);
                FindNodeValue(objNode, "sv_value", szValue);
                FindNodeValue(objNode, "sv_accountwith", szAccValue);
                if(!szAccValue.empty())
                    AddNodeAttrib(objMonitorNode, szName + "1", szValue);

                if(pszSaveName && strlen(pszSaveName) > 0 && szName.compare(pszSaveName) == 0)
                {
                    if(pszExtraParam && strlen(pszExtraParam) > 0)
                        AddNodeAttrib(objMonitorNode, szName, pszExtraParam);
                    else
                        AddNodeAttrib(objMonitorNode, szName, "");
                }
                else
                    AddNodeAttrib(objMonitorNode, szName, szValue);
            }
        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitorBaseParam
// 说明 保存基础参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitorBaseParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // 监测器基本节点
    MAPNODE objMonitorNode = GetMonitorParameter(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // 枚举监测器模板的每一条基本属性
        if( FindMTParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // 属性参数名称 缺省值 是否与其他值计算
                string szName (""), szValue (""), szAccValue ("");
                FindNodeValue(objNode, "sv_name", szName);
                FindNodeValue(objNode, "sv_value", szValue);
                FindNodeValue(objNode, "sv_accountwith", szAccValue);
                if(!szAccValue.empty())
                    AddNodeAttrib(objMonitorNode, szName + "1", szValue);

                if(pszSaveName && strlen(pszSaveName) > 0 && szName.compare(pszSaveName) == 0)
                {
                    if(pszExtraParam && strlen(pszExtraParam) > 0)
                        AddNodeAttrib(objMonitorNode, szName, pszExtraParam);
                    else
                        AddNodeAttrib(objMonitorNode, szName, "");
                }
                else
                    AddNodeAttrib(objMonitorNode, szName, szValue);
            }
        }
        AddNodeAttrib(objMonitorNode, "sv_description", "");
        AddNodeAttrib(objMonitorNode, "sv_reportdesc", "");
        AddNodeAttrib(objMonitorNode, "sv_plan", "7*24");
        AddNodeAttrib(objMonitorNode, "sv_checkerr", "false");
        AddNodeAttrib(objMonitorNode, "sv_errfreqsave", "");
        AddNodeAttrib(objMonitorNode, "sv_errfreq", "0");
        AddNodeAttrib(objMonitorNode, "sv_errfrequint", "1");
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitorCondition
// 说明 保存监测器的监测阀值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitorCondition(OBJECT &objMonitor, OBJECT objMonitorTemp)
{
    // 错误阀值
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    MAPNODE alertnodeTmp = GetMTErrorAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // 警告阀值
    alertnode = GetMonitorWarningAlertCondition(objMonitor);
    alertnodeTmp = GetMTWarningAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // 正常阀值
    alertnode = GetMonitorGoodAlertCondition(objMonitor);
    alertnodeTmp = GetMTGoodAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 函数 loadCondition
//// 说明 加载数学操作符号
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVDevice::loadCondition()
//{
//    m_lsCondition.push_back("==");
//    m_lsCondition.push_back("!=");
//    m_lsCondition.push_back(">");
//    m_lsCondition.push_back(">=");
//    m_lsCondition.push_back("<");
//    m_lsCondition.push_back("<=");
//    m_lsCondition.push_back("contains");
//    m_lsCondition.push_back("!contains");
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveAlertNodeValue
// 说明 保存阀值
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveAlertNodeValue(MAPNODE &alertnode, MAPNODE &alertnodeTmp)
{
    string szRelationCount("");
    FindNodeValue(alertnodeTmp, "sv_conditioncount", szRelationCount);
    if(!szRelationCount.empty())
    {
        char szKey [16] = {0};
        string szCondition (""), szExpression(""), szReturn (""), szParamValue ("") , szRelation ("");
        int nCount = 0;

        AddNodeAttrib(alertnode, "sv_conditioncount", szRelationCount);

        FindNodeValue(alertnodeTmp, "sv_expression", szExpression);
        AddNodeAttrib(alertnode, "sv_expression", szExpression);

        nCount = atoi(szRelationCount.c_str());
        for(int i = 1; i <= nCount; i++)
        {   
            sprintf(szKey, "sv_relation%d", i);
            FindNodeValue(alertnodeTmp, szKey, szRelation);
            AddNodeAttrib(alertnode, szKey, szRelation);

            sprintf(szKey, "sv_paramname%d", i);
            FindNodeValue(alertnodeTmp, szKey, szReturn);
            AddNodeAttrib(alertnode, szKey, szReturn);

            sprintf(szKey, "sv_operate%d", i);
            FindNodeValue(alertnodeTmp, szKey, szCondition);
            AddNodeAttrib(alertnode, szKey, szCondition);
            
            sprintf(szKey, "sv_paramvalue%d", i);
            FindNodeValue(alertnodeTmp, szKey, szParamValue);
            AddNodeAttrib(alertnode, szKey, szParamValue);
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 函数 loadReturnParam
//// 说明 根据监测器模板加载返回值
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVDevice::loadReturnParam(OBJECT &objMonitorTemp, SVReturnMap &rtMap)
//{
//    LISTITEM lsItem;
//    //得到每一个返回值
//    if( FindMTReturnFirst(objMonitorTemp, lsItem))
//    {
//        MAPNODE objNode;
//        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
//        {
//            string szName (""), szLabel ("");
//            FindNodeValue(objNode, "sv_name", szName);
//            FindNodeValue(objNode, "sv_label", szLabel);
//            if(!szName.empty() && !szLabel.empty())
//                rtMap[szName] = szLabel;
//        }
//    }   
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 checkParamValue
// 说明 检测阀值是否合理
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::checkParamValue(string &szParam, SVReturnMap &rtMap)
{
    bool bNoError = false;
    if(szParam.empty())
        return false;
    SVReturnItem rtItem;
    for(rtItem = rtMap.begin(); rtItem != rtMap.end(); rtItem ++)
    {
        if((*rtItem).second == szParam)
        {
            szParam = (*rtItem).first;
            return true;
        }
    }
    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 selAllByMonitorType
// 说明 根据监测器模板ID全选此类型的所有监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::selAllByMonitorType(int nMonitorType)
{
    bool bSel = true;
    WCheckBox* pSelAll = reinterpret_cast<WCheckBox*>(m_mapMinitor.mapping(nMonitorType));
    if(pSelAll)
        bSel = pSelAll->isChecked();
    irow it;
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        if((*it).second.getTag() == nMonitorType)
        {
            SVTableCell *pCell =  (*it).second.Cell(0);
            if(pCell && pCell->Type() == adCheckBox)
                ((WCheckBox*)pCell->Value())->setChecked(bSel);
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
