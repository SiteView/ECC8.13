/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// adddevice2nd.cpp
// 添加设备的第二步，根据设备类型展示设备的参数
// 编辑设备也在此文件中完成
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "adddevice2nd.h"
#include "resstring.h"
#include "listtable.h"
#include "advanceparam.h"
#include "rightview.h"
#include "mainview.h"
#include "treeview.h"
#include "basefunc.h"
#include "basedefine.h"
#include "eccobjfunc.h"
#include "debuginfor.h"
#include "paramitem.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WText"

#include "../userright/User.h"

#include "../base/OperateLog.h"

#include "../../base/des.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice2nd::CEccAddDevice2nd(WContainerWidget *parent):
CEccBaseTable(parent),
m_pGeneral(NULL),
m_pAdvance(NULL),
m_pName(NULL),
m_pNameErr(NULL),
m_szParentID(""),
m_szEditIndex(""),
m_szDTType(""),
m_szDllName(""),
m_szFuncName(""),
m_szQuickAdd(""),
m_szQuickAddSel(""),
m_szNetworkset(""),
m_pTest(NULL),
m_pSave(NULL),
m_pCancel(NULL),
m_pBack(NULL),
m_pHideButton(NULL)
{
    setStyleClass("panel");
    initForm(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 说明 添加设备
// 参数
//      父组索引
//      设备类型
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::AddDeviceByType(string szParent, string szDTName)
{
    ResetData();

    m_szDllName     = "";
    m_szFuncName    = "";
    m_szQuickAdd    = "";
    m_szQuickAddSel = "";
    m_szNetworkset  = "";

    m_bHasDynamic   = false;

    m_szParentID    = szParent;
    m_szDTType      = szDTName;
    m_szEditIndex   = "";

    m_lsDyn.clear();
    list<CEccParamItem*>::iterator lstItem;
    // 删除以前的所有数据
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
        delete (CEccParamItem*)(*lstItem);

    m_lsBasicParam.clear();

    enumBaseParam();
    createBaseParam();

    if(m_pTest)
    {
        if(m_szDllName.empty() || m_szFuncName.empty())
            m_pTest->hide();
        else
            m_pTest->show();
    }

    if(m_pBack)
        m_pBack->show();

    if(m_pSave)
    {
        m_pSave->setText(SVResString::getResString("IDS_Add"));
        m_pSave->setToolTip(SVResString::getResString("IDS_Add_Device_Tip"));
    }

    if(m_pCancel)
    {
        m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
    }

    if(m_pAdvance)
        m_pAdvance->setSEID(FindSEID(m_szParentID));

    string szCmd("hiddenbar();");
    if(m_pHideButton)
    {
        if(!m_pHideButton->getEncodeCmd("xclicked()").empty())
        {
            szCmd = "update('" + m_pHideButton->getEncodeCmd("xclicked()") + "');" + szCmd ;
        }
    }

    if(m_pTitle)
        m_pTitle->setText( SVResString::getResString("IDS_Add") + SVResString::getResString("IDS_Device"));

    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::Cancel()
{
    CEccMainView::m_pRightView->showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createAdvance()
{
    int nRow = m_pContent->numRows();

    m_pAdvance = new CEccAdvanceTable(m_pContent->elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createBaseParam()
{
    if(m_pGeneral)
    {
        m_pGeneral->showSubTable();

        WTable *pSubTable = m_pGeneral->getListTable();
        if(pSubTable)
        {
            pSubTable->clear();
            m_lsHelp.clear();
            // 循环创建每个属性中的控件
            list<CEccParamItem*>::iterator lstItem;
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // 是否有跟随值
                if((*lstItem)->isHasFollow())
                {
                    // 得到跟随值 && 设置跟随值
                    string szFollow = (*lstItem)->getFollow();
                    if(!szFollow.empty())
                    {
                        list<CEccParamItem*>::iterator ittmp ;
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
                (*lstItem)->CreateControl(pSubTable, m_lsHelp, m_bShowHelp);
                // 是否是动态属性
                if((*lstItem)->isDynamic())
                {
                    m_lsDyn.push_back((*lstItem));
                    m_bHasDynamic = true;
                }
            }

            //
            createDeviceName(pSubTable);
            // 枚举每一个属性
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // 属性名称是否是_MachineName或者是否需要和设备名称动态绑定
                if(strcmp((*lstItem)->getName(), "_MachineName") == 0 || (*lstItem)->isSynTitle())
                {
                    // 动态绑定
                    if(m_szEditIndex.empty() && m_pName != NULL && (*lstItem)->getControl() != NULL)
                    {
                        WInteractWidget* pEdit = (*lstItem)->getControl();
                        string szCmd = "onkeyup='Synchronization(\"" + pEdit->formName() +
                            "\",\"" + m_pName->formName() + "\")'";
                        strcpy(pEdit->contextmenu_, szCmd.c_str());
                    }
                }
                else if(strcmp((*lstItem)->getName(), "_ProtocolType") == 0 && (*lstItem)->getControl() != NULL)
                {// 特殊处理_ProtocolType
                    list<CEccParamItem*>::iterator lsItem;
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
// 创建设备名称
// 参数
//      设备名称所在的表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createDeviceName(WTable *pTable)
{
    // 得到当前行数
    int nRow = pTable->numRows();
    // 说明
    new WText(SVResString::getResString("IDS_Title"), pTable->elementAt(nRow, 0));
    // 增加（红色*）标识为必添项
    new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

    // 创建标题输入框
    m_pName = new WLineEdit("", pTable->elementAt(nRow, 1));
    if(m_pName)
        m_pName->setStyleClass("Cell_40");

    // 创建帮助文本
    WText *pNameHelp = new WText(SVResString::getResString("IDS_Host_Label_Help"), pTable->elementAt(nRow + 1, 1));
    if(pNameHelp)
    {
        pNameHelp->hide();
        pTable->elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des");
        m_lsHelp.push_back(pNameHelp);
    }

    m_pNameErr = new WText(SVResString::getResString("IDS_Host_Label_Error"), pTable->elementAt(nRow + 2, 1));            
    if (m_pNameErr)
    {
        pTable->elementAt(nRow + 2, 1)->setStyleClass("table_data_input_error");
        m_pNameErr->hide();
    }

    // 这个表格单元对齐方式为左上对齐
    pTable->GetRow(0)->setStyleClass("padding_top");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    pTable->elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
    pTable->elementAt(nRow, 1)->setStyleClass("table_data_text");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建基础信息表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createGeneral()
{
    int nRow = m_pContent->numRows();

    m_pGeneral = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
    if(m_pGeneral)
    {
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Infor_Title"));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建操作
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createOperate()
{
    if(m_pOperate)
    {
        int nRow = m_pOperate->numRows();
        // 上一步
        m_pBack = new CEccButton(SVResString::getResString("IDS_Back_One_Step"), SVResString::getResString("IDS_Back_Device_List_Tip"),
            "", m_pOperate->elementAt(nRow, 0));
        if(m_pBack)
        {
            WObject::connect(m_pBack, SIGNAL(clicked()), "showbar();", this, SLOT(Forward()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(0, 1));

        // 保存
        m_pSave = new CEccImportButton(SVResString::getResString("IDS_Add"), SVResString::getResString("IDS_Add_Device_Tip"),
            "", m_pOperate->elementAt(nRow, 2));
        if(m_pSave)
        {
            WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(SaveDevice()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(0, 3));

        // 取消
        m_pCancel = new CEccButton(SVResString::getResString("IDS_Cancel_Add"), SVResString::getResString("IDS_Cancel_Add_Device_Tip"), 
            "", m_pOperate->elementAt(nRow, 4));
        if(m_pCancel)
        {
            WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        // 测试
        new WText("&nbsp;", m_pOperate->elementAt(0, 5));
        m_pTest = new CEccButton(SVResString::getResString("IDS_Test"), SVResString::getResString("IDS_Curent_Test_Tip"),
            "", m_pOperate->elementAt(nRow, 6));
        if(m_pTest)
        {
            WObject::connect(m_pTest, SIGNAL(clicked()), "showbar();", SLOT(TestDevice()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        nRow = static_cast<WTableCell*>(m_pOperate->parent())->row();
        elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 编辑设备
// 参数
//      待编辑设备的索引
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::EditDevice(string szDeviceID)
{
    // 清理 设备参数
	m_DeviceParam.clear();

    ResetData();

    m_szDllName     = "";
    m_szFuncName    = "";
    m_szQuickAdd    = "";
    m_szQuickAddSel = "";
    m_szNetworkset  = "";

    m_bHasDynamic   = false;

    m_szParentID    = "";
    m_szEditIndex   = szDeviceID;

    // 在树上得到指定设备
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szDeviceID);
    if(pNode)
    {
        const CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
        // 得到设备类型
        m_szDTType = pDevice->getRealDeviceType();
        
        m_lsDyn.clear();
        list<CEccParamItem*>::iterator lstItem;
        // 删除以前的所有数据
        for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            delete (CEccParamItem*)(*lstItem);

        m_lsBasicParam.clear();

        // 枚举基础参数
        enumBaseParam();
        // 枚举高级参数
        createBaseParam();

        // 打开设备
        OBJECT objDevice = GetEntity(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(objDevice != INVALID_VALUE)
        {
            // 得到主节点
            MAPNODE mainNode = GetEntityMainAttribNode(objDevice);
            if(mainNode != INVALID_VALUE)
            { 
                list<CEccParamItem*>::iterator lstItem;
                string szName(""), szValue("");
                // 得到基础属性参数值
                for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
                {
                    FindNodeValue(mainNode, (*lstItem)->getName(), szValue);
                    (*lstItem)->setStringValue(szValue);
                    if((*lstItem)->isRun())
                        m_DeviceParam[(*lstItem)->getName()] = szValue;
                }
            }
            // 关闭设备
            CloseEntity(objDevice);
        }

        // 是否可以测试设备
        if(m_szDllName.empty() || m_szFuncName.empty())
            if(m_pTest)
                m_pTest->hide();

        // 重置设备名称
        if(m_pName)
            m_pName->setText(pDevice->getName());

        // 重置标题栏
        if(m_pTitle)
            m_pTitle->setText( SVResString::getResString("IDS_Edit") + pDevice->getName() + SVResString::getResString("IDS_Device"));

        // 重置高级参数
        if(m_pAdvance)
        {
            // 依靠
            m_pAdvance->setDepends(pDevice->getDependsID());
            // 描述
            m_pAdvance->setDescription(pDevice->getDescription());
            // 依靠条件
            m_pAdvance->setCondition(pDevice->getCondition());
            // SE索引
            m_pAdvance->setSEID(FindSEID(szDeviceID));
        }

        // 隐藏 上一步 按钮
        if(m_pBack)
            m_pBack->hide();

        // 重置 保存 按钮的显示文字和提示信息
        if(m_pSave)
        {
            m_pSave->setText(SVResString::getResString("IDS_Save"));
            m_pSave->setToolTip(SVResString::getResString("IDS_Save_Tip"));
        }

        // 重置 取消 按钮的显示文字和提示信息
        if(m_pCancel)
        {
            m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
            m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Edit_Device_Tip"));
        }
    }

    string szCmd("hiddenbar();");
    if(m_pHideButton)
    {
        if(!m_pHideButton->getEncodeCmd("xclicked()").empty())
        {
            szCmd = "update('" + m_pHideButton->getEncodeCmd("xclicked()") + "');" + szCmd ;
        }
    }
    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举基础属性
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::enumBaseParam()
{
    // 打开设备模板
    OBJECT objDevice = GetEntityTemplet(m_szDTType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {// 成功
        LISTITEM lsItem;
        // 得到每个属性
        if(FindETContrlFirst(objDevice, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                CEccParamItem *param = new CEccParamItem(objNode);
                m_lsBasicParam.push_back(param);
            }
        }
        // 主节点
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            FindNodeValue(node, svDLL,           m_szDllName);           // 动态连接库名称
            FindNodeValue(node, svFunc,          m_szFuncName);          // 函数名称
            FindNodeValue(node, svQuickAdd,      m_szQuickAdd);          // 快速添加
			FindNodeValue(node, svQuickAddSel,   m_szQuickAddSel);       // 快速添加缺省选择
            FindNodeValue(node, svNetworkSet,    m_szNetworkset);        // 是否是网络设备

            if(m_szNetworkset.empty())
                m_szNetworkset = "false";
        }
        // 关闭设备模板
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 上一步
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::Forward()
{
    CEccMainView::m_pRightView->showAddDevice1st(m_szParentID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::initForm(bool bHasHelp)
{
    // 基础类初始化函数
    CEccBaseTable::initForm(bHasHelp);

    // 设置标题栏文字
    setTitle(SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device"));

    if(m_pContent)
    {
        CEccBaseTable::setContentCellStyle("height95p");
        // 创建基础属性表
        createGeneral();
        // 创建高级属性表
        createAdvance();
    }

    // 创建帮助
    createOperate();
    // 创建隐藏按钮
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 重置属性
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::ResetData()
{
    // 重置高级参数
    if(m_pAdvance)
        m_pAdvance->ResetData();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 保存设备（新添加和编辑设备）
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::SaveDevice()
{
    list<CEccParamItem*>::iterator lstItem;
    bool bError = false;
    bool bChanged = false;
    bool bAddAttribSucc = true;

    unsigned long ulStart = GetTickCount();

    string szDevName(""), szOSType(""), szRealIndex("");

    if(m_pNameErr)
        m_pNameErr->hide();

    // 校验基础属性
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        if(!(*lstItem)->checkValue())
        {
            if(m_pGeneral)
                m_pGeneral->showSubTable();
            bError = true;
        }
    }

    // 校验名称
    if(!checkName(szDevName))
    {
        if(m_pNameErr)
            m_pNameErr->show();
        bError = true;
    }

    string szOpt("Add new Device");
    
    // 发生错误
    if(bError)
    {
        m_pGeneral->showSubTable();
        goto exitSave;
    }

    OBJECT objDevice = INVALID_VALUE;
    if(m_szEditIndex.empty())
    {// 是否正在编辑设备
        if(m_szNetworkset == "true")
        {// 待添加设备是网络设备
            // 得到当前已使用网络设备总数
            int nNetworkCount = getUsingNetworkCount(); 
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
        szOpt = "Edit Device " + m_szEditIndex;
        objDevice = GetEntity(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
	}

    // 创建/打开设备是否成功
    if(objDevice != INVALID_VALUE)
    {
        // 得到主节点
        MAPNODE mainNode = GetEntityMainAttribNode(objDevice);
        if(mainNode != INVALID_VALUE)
        {
			map<string, string, less<string> >::iterator paramItem;
            // 增加每一个属性
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                string szValue(""), szName("");
                (*lstItem)->getStringValue(szValue);
                (*lstItem)->getName(szName);
                if(strcmp(szName.c_str(), svOSType) == 0)
                    szOSType = szValue;

				if(bChanged)
				{
					paramItem = m_DeviceParam.find(szName);
					if(paramItem != m_DeviceParam.end())
						if(paramItem->second != szValue)
							bChanged = true;
				}
                // 在主节点下添加属性
                if(!AddNodeAttrib(mainNode, szName, szValue))
                    bError = true;
            }

            if(!bError && AddNodeAttrib(mainNode, svName, szDevName) && AddNodeAttrib(mainNode, svNetworkSet, m_szNetworkset)
                &&AddNodeAttrib(mainNode, svDeviceType, m_szDTType))
                if(m_pAdvance && m_pAdvance->SaveAdvanceParam(mainNode))
                    bAddAttribSucc = true;

            string szDesc(""), szDepends(""), szCondition("");
            if(m_pAdvance)
            {
                szDesc = m_pAdvance->getDescription();
                szDepends = m_pAdvance->getDepends();
                szCondition = m_pAdvance->getConditon();
            }

            if(bAddAttribSucc && m_szEditIndex.empty())
            {
                if(!IsSVSEID(m_szParentID))
                    saveDisableByParent(mainNode, SiteView_ECC_Device, m_szParentID);

                szRealIndex = AddNewEntity(objDevice, m_szParentID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                // 创建组成功，触发创建成功消息
                if(!szRealIndex.empty())
                {    
                    int nIndex = FindIndexByID(szRealIndex);
                    nIndex = CEccTreeView::AppendDevice(szRealIndex, szDevName, szDesc, szDepends, szCondition, 
                        m_szDTType, szOSType, m_szNetworkset);
                    char szIndex[16] = {0};
                    sprintf(szIndex, "%d", nIndex);
                    AddNodeAttrib(mainNode, svShowIndex, szIndex);

                    CEccTreeView::m_SVSEUser.AddUserScopeAllRight(szRealIndex, SiteView_ECC_Device);
                }
            }
            else if(bAddAttribSucc)
            {
                if(SubmitEntity(objDevice, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                {
                    if((m_pAdvance && m_pAdvance->isDependsChanged()) || bChanged)
                    {
                        string szQueueName(getConfigTrackQueueName(m_szEditIndex));
                        CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                        if(!PushMessage(szQueueName, "ENTITY:UPDATE", m_szEditIndex.c_str(), 
                            static_cast<int>(m_szEditIndex.length()) + 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                            PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
                    }
                    CEccTreeView::EditDevice(m_szEditIndex, szDevName, szDesc, szDepends, szCondition);
                }
            }

            CloseEntity(objDevice);
        }
    }

    // 是否正在编辑设备
    // 添加新的设备且可以快速添加监测器
    if(m_szEditIndex.empty() && !m_szQuickAdd.empty())
    {
        string szRun("");
        MakeRunParamString(szRun, false);

        szOpt = "Show Quick Add Monitor Frame";

        // 显示添加设备第三步
        CEccMainView::m_pRightView->showAddDevice3rd(szRealIndex, szDevName, szRun, m_szQuickAdd, m_szQuickAddSel, m_szNetworkset);
        return;
    }
    else if(m_szEditIndex.empty())
    {// 不能快速添加监测器
        // 进入新设备
        CEccMainView::m_pRightView->showNewDevice(szRealIndex);
    }
    else
    {// 编辑设备
        CEccMainView::m_pRightView->showMainForm();
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccAddDevice2nd.SaveDevice", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccAddDevice2nd.SaveDevice", szOpt, 
        0, GetTickCount() - ulStart);

exitSave:
    if(WebSession::js_af_up.empty())
        WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示/隐藏帮助信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::ShowHideHelp()
{
    m_bShowHelp = !m_bShowHelp;

    if(m_pAdvance)
        m_pAdvance->ShowHideHelp(m_bShowHelp);

    list<WText*>::iterator it;
    for(it = this->m_lsHelp.begin(); it != m_lsHelp.end(); it++)
    {
        if(m_bShowHelp)
            (*it)->show();
        else
            (*it)->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 测试设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::TestDevice()
{
    list<CEccParamItem *>::iterator lstItem;

    string szQuery("");
    MakeRunParamString(szQuery);
    // 如果可以测试则显示设备测试界面
    if(!szQuery.empty())
    {
        szQuery = szQuery + "devicetype=" + m_szDTType + "&seid=";
        if(m_szEditIndex.empty())
            szQuery += FindSEID(m_szParentID);
        else
            szQuery += FindSEID(m_szEditIndex);

        szQuery = "showtestdevice('testdevice.exe?" + szQuery +"');" ;
        PrintDebugString(szQuery.c_str());
    }
    szQuery = "hiddenbar();" + szQuery;
    WebSession::js_af_up = szQuery; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 校验名称
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice2nd::checkName(string &szName)
{
    if(m_pName)
    {
        szName = m_pName->text();
        szName = strtriml(szName.c_str());
        szName = strtrimr(szName.c_str());

        if(!szName.empty())
            return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建隐藏按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createHideButton()
{
    int nRow = numRows();
    m_pHideButton = new WPushButton("", elementAt(nRow, 0));
    if(m_pHideButton)
    {
        m_pHideButton->hide();
        WObject::connect(m_pHideButton, SIGNAL(clicked()), "showbar();", this, SLOT(EnumDynData()), 
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举动态参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::EnumDynData()
{
    string szQuery("");
    // 枚举每个动态属性的动态数据
    listItem    lstItem;
    for(lstItem = m_lsDyn.begin(); lstItem != m_lsDyn.end(); lstItem ++)
    {
        if(m_szEditIndex.empty())
            (*lstItem)->enumDynValue(szQuery, m_szParentID);
        else
            (*lstItem)->enumDynValue(szQuery, m_szEditIndex);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举每个运行时属性构造属性字符串
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::MakeRunParamString(string &szRunParam, bool bEncode)
{
    list<CEccParamItem *>::iterator lstItem;

    // 枚举每一个属性的参数
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        // 是否是运行时必要属性参数
        if((*lstItem)->isRun())
        {
            // 检查值是否正确
            if(!(*lstItem)->checkValue())
            {
                szRunParam = "";
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
            if(bEncode)
                szValue = url_Encode(szValue.c_str());
            szRunParam = szRunParam + szName + "=" + szValue + "&";
        }
    }
}
