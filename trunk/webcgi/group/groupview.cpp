#include "groupview.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WSVLinkText"
#include "../../opens/libwt/WLineEdit"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../opens/libwt/WebSession.h"
#include "../../kennel/svdb/libutil/time.h"

#include "resstring.h"
#include "../demotreeview/DemoTreeList.h"

#include "statedesc.h"
#include "monitorview.h"


extern void PrintDebugString (const char * szMsg);

extern void PrintDebugString (const string &szMsg);

char SVGroupview::m_szLogData[1025] = {0};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数
// 说明 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVGroupview::SVGroupview(WContainerWidget * parent /* = NULL */, CUser *pUser ,string szIDCUser, string szIDCPwd):
WContainerWidget(parent)
{
    m_szEditIndex = "";

    m_pSVSEView = NULL;	
    m_pMonitorview = NULL;
    m_pAddGroup = NULL;
    m_pDeviceList = NULL;
    m_pDevice = NULL;
    m_pMonitorList = NULL;
    m_pMonitor = NULL;
    m_pAddSVSE = NULL;
    m_pBatchAdd = NULL;
    m_pSortForm = NULL;
    m_pSVUser = NULL;
    m_pTitleCell = NULL;

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;   

    m_pSVUser = pUser;

    if(m_pSVUser)
        m_szUserShowName = m_pSVUser->getUserID();//GetIniFileString(m_pSVUser->getUserID(), "UserName", "", "user.ini");
    else
        m_szUserShowName = "unknown user";

    // 加载文字资源
    //loadGeneralText();
    // 初始化页面
    InitForm();
    memset(m_szLogData, 0, sizeof(m_szLogData));

    connect(&m_GroupName, SIGNAL(mapped(const std::string)), this, SLOT(enterGroupByID(const std::string)));      
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddStandard
// 说明 添加 组标准显示内容
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddStandard()
{
    int nRow = m_GeneralList.m_pGeneral->numRows();
    m_GeneralList.m_pStandard = new SVGeneral(m_GeneralList.m_pGeneral->elementAt( nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddGroup
// 说明 添加子组列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddGroup()
{
    int nRow = m_GeneralList.m_pGeneral->numRows();
    m_GeneralList.m_pGroup = new SVGroupList((WContainerWidget *) m_GeneralList.m_pGeneral->elementAt( nRow, 0 ), m_pSVUser);
    if(m_GeneralList.m_pGroup)
    {
        // 绑定 添加组处理函数
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(AddNewGroup()), this, SLOT(AddNewGroup()));
        // 绑定 根据索引编辑组消息
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(EditGroupByID(string)), this, SLOT(EditGroupParam(string)));
        // 绑定 枚举当前组下所有设备消息
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(EnumDeviceByID(string)), this, SLOT(EnumDevice(string)));
        // 绑定 删除组消息
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(DeleteGroupSucc(string,string)), this, SLOT(DelGroupByIdProc(string,string)));
        // 删除设备处理函数
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(DeleteDeviceSucc(string,string)), this, SLOT(DelDeviceByIdProc(string,string)));
        // 绑定 子组列表排序消息
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(sortGroupsList(int)), this, SLOT(SortObjects(int)));
        // 绑定 修改组状态消息
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(ChangeGroupState(string,int)), this, SLOT(ChangeGroupState(string,int)));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddEntity
// 说明 添加设备列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddEntity()
{
    int nRow = m_GeneralList.m_pGeneral->numRows();
    // 
    m_GeneralList.m_pDevice = new SVEnumDevice((WContainerWidget *) m_GeneralList.m_pGeneral->elementAt( nRow, 0 ), m_pSVUser);
    if(m_GeneralList.m_pDevice)
    {
        if(m_GeneralList.m_pGroup)
        {
            string szIndex = m_GeneralList.m_pGroup->getGroupIndex();
            // 设置当前组ID
            m_GeneralList.m_pDevice->EnterGroup(szIndex);
        }
        // 添加设备处理函数
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(AddNewDevice()), this, SLOT(AddNewDevice()));
        // 进入设备处理
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(EnterDeviceByID(string)), this, SLOT(EnterDeviceByID(string)));
        // 根据索引编辑设备
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(EditDeviceByID(string)), this, SLOT(EditDeviceByIndex(string)));
        // 删除设备处理函数
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(DeleteDeviceSucc(string,string)), this, SLOT(DelDeviceByIdProc(string,string)));
        // 排序处理函数
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(sortDevicesList(int)), this, SLOT(SortObjects(int)));
        // 更新设备ID
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(UpdateDeviceState(string,int)), this, SLOT(ChangeDeviceState(string,int)));
        // 绑定 拷贝设备成功消息
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(CopyDeviceSucc(string,string)), this, SLOT(CopyNewDeviceSucc(string,string)));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddViewControl
// 说明 添加视图控制内容
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddViewControl()
{
    WTable *pViewControl = new WTable( (WContainerWidget *) m_GeneralList.m_pGeneral->elementAt( 1, 0 ) );
    if ( pViewControl )
    {
        // 更改子表的样式
        pViewControl->setStyleClass("t3");
        m_GeneralList.m_pBackParent = new WPushButton(SVResString::getResString("IDS_Operate_Back_Parent"), (WContainerWidget *)pViewControl->elementAt(0 , 0));
        pViewControl->elementAt(0 , 0)->setContentAlignment(AlignTop | AlignRight);
        if(m_GeneralList.m_pBackParent)
        {
            // 设置 Tip
            m_GeneralList.m_pBackParent->setToolTip(SVResString::getResString("IDS_Operate_Back_Parent_Tip"));    
            // onclick 函数处理
            WObject::connect(m_GeneralList.m_pBackParent, SIGNAL(clicked()), "showbar();", this, SLOT(backParent()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddTitle
// 说明 添加标题
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddTitle()
{
    WTable *pTitle = new WTable(m_GeneralList.m_pGeneral->elementAt( 0, 0 ));
    if(pTitle)
    {
        pTitle->setStyleClass("t3");
        m_pTitleCell = pTitle->elementAt( 0, 0);

		// 翻译
        int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	    if(bTrans == 1)
	    {
	        m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), pTitle->elementAt(0, 1));
	        if(m_pTranslateBtn)
	        {
                // onclick
		        connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
                // tool tip
		        m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
            } 
            new WText("&nbsp;&nbsp;&nbsp;&nbsp;",  ((WContainerWidget *)pTitle->elementAt( 0, 1 )));

		    m_pExChangeBtn = new WPushButton(SVResString::getResString("IDS_Refresh"),((WContainerWidget *)pTitle->elementAt( 0, 1 )));
		    if(m_pExChangeBtn)
		    {
                // onclick
			    connect(m_pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
                // tool tip
			    m_pExChangeBtn->setToolTip(SVResString::getResString("IDS_Refresh_Tip"));
            }
 		    new WText("&nbsp;&nbsp;&nbsp;&nbsp;",  ((WContainerWidget *)pTitle->elementAt( 0, 1 )));
	    }

        // 刷新时间
        m_GeneralList.m_ptxtTime = new WText("local Time" , ((WContainerWidget *)pTitle->elementAt( 0, 1 )));
        // 得到当前时间
        svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
        string curTime = ttime.Format();
        if(m_GeneralList.m_ptxtTime)
        {
            // 设置TD 样式表
            pTitle->elementAt(0, 1)->setStyleClass("cell_40");
            // 设置文字
            m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
            // 设置样式表
            m_GeneralList.m_ptxtTime->setStyleClass("tgrouptitle2");    
        }
        // 设置对齐方式
        pTitle->elementAt( 0, 1 )->setContentAlignment(AlignRight | AlignTop);
    }
    // 设置样式表
    m_GeneralList.m_pGeneral->elementAt( 0, 0 )->setStyleClass("t1title");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Translate
// 说明 翻译按钮单击事件处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::Translate()
{
    // 显示 翻译页面
	WebSession::js_af_up = "showTranslate('groupRes')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ExChange
// 说明 刷新按钮单击事件处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ExChange()
{
    // 发起翻译成功消息
	emit TranslateSuccessful();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 InitForm
// 说明 页面初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::InitForm()
{
    // 使用 JS 文件
    new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

    // 判断是否为单机版
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {
        // 单机版 进入主SE 1（SE ID固定）
        enterSVSE("1");    
    }
    else 
    {   
        // 设置当前视图为 SE视图
        ShowActivateView(active_se_view);
    } 
    // 创建隐藏按钮
    createHideButton();
    // 创建当前编辑
    m_pcurEditIndex = new WLineEdit("", this);
    if(m_pcurEditIndex)
    {
        m_pcurEditIndex->hide();
        string strScript ("");
        strScript += "<SCRIPT language='JavaScript' > var curDeviceID='";
        strScript += m_pcurEditIndex->formName();
        strScript += "';</SCRIPT>";
        new WText(strScript, this);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 backParent
// 说明 返回上一级
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::backParent()
{
    if(m_GeneralList.m_pGroup)
    {
        // 得到当前组ID
        string szGroupIndex = m_GeneralList.m_pGroup->getGroupIndex(); 

        // 父节点是否是SE
        int nPos = static_cast<int>(szGroupIndex.find("."));
        if(nPos > 0)
        {
            string szParentID = FindParentID(szGroupIndex);
            if(!szParentID.empty())
                m_GeneralList.m_pGroup->BackGroup(szParentID);
        }
        else
        {
            // 是否是单机版
            if(GetIniFileInt("solover","solover",1,"general.ini") == 0)
                ShowActivateView(active_se_view);
            else
                m_GeneralList.m_pBackParent->hide(); // 返回上一级 按钮 隐藏
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showIconView
// 说明 图标视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::showIconView()
{
    /*
    if (!m_bShowList)
    return;

    m_bShowList = false;
    if (!m_bEntityHide)
    {
    if (m_GeneralList.m_pEntityIcon)
    m_GeneralList.m_pEntityIcon->show();
    if (m_GeneralList.m_pEntityList)
    m_GeneralList.m_pEntityList->hide();
    if (m_GeneralList.m_pEntityOper)
    m_GeneralList.m_pEntityOper->hide();
    }

    if (!m_bGroupHide)
    {
    if (m_GeneralList.m_pGroupIcon)
    m_GeneralList.m_pGroupIcon->show();
    if (m_GeneralList.m_pGroupList)
    m_GeneralList.m_pGroupList->hide();
    if (m_GeneralList.m_pGroupOper)
    m_GeneralList.m_pGroupOper->hide();
    }
    */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showListView
// 说明 列表视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::showListView()
{
    /*
    if (m_bShowList)
    return;

    m_bShowList = true;

    if(m_GeneralList.m_psvEntity)
    {
    if(!m_GeneralList.m_psvEntity->isHidden())//if (!m_bEntityHide)    
    {
    if (m_GeneralList.m_pEntityIcon)
    m_GeneralList.m_pEntityIcon->hide();
    if (m_GeneralList.m_pEntityList)
    m_GeneralList.m_pEntityList->show();
    if (m_GeneralList.m_pEntityOper)
    m_GeneralList.m_pEntityOper->show();
    }
    }
    if(m_GeneralList.m_psvGroup)
    {
    if(!m_GeneralList.m_psvGroup->isHidden())//if ( !m_bGroupHide )        
    {
    if (m_GeneralList.m_pGroupIcon)
    m_GeneralList.m_pGroupIcon->hide();
    if (m_GeneralList.m_pGroupList)
    m_GeneralList.m_pGroupList->show();
    if (m_GeneralList.m_pGroupOper)
    m_GeneralList.m_pGroupOper->show();
    }
    }
    */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 
// 说明 加载 文字资源
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVGroupview::loadGeneralText()
//{
    //// 加载资源
    //OBJECT objRes = LoadResource("default", "localhost");  
    //if( objRes != INVALID_VALUE )
    //{// 加载资源成功
    //    MAPNODE ResNode = GetResourceNode(objRes);
    //    if( ResNode != INVALID_VALUE )
    //    {
    //        FindNodeValue(ResNode, "IDS_Operate_Back_Parent",       m_GeneralText.szBackParent);
    //        FindNodeValue(ResNode, "IDS_Operate_Back_Parent_Tip",   m_GeneralText.szBackParentTip);
    //        FindNodeValue(ResNode, "IDS_Refresh_Time",              m_GeneralText.szRefreshTime);
    //        FindNodeValue(ResNode, "IDS_List_View_Tip",             m_GeneralText.szListviewDesc);
    //        FindNodeValue(ResNode, "IDS_Icon_View_Tip",             m_GeneralText.szIconviewDesc);
    //        FindNodeValue(ResNode, "IDS_Device_Can_not_Disable",    m_szDeviceDisable);
    //        FindNodeValue(ResNode, "IDS_Device_Can_not_Enable",     m_szDeviceEnable);
    //        FindNodeValue(ResNode, "IDS_Group_Can_not_Disable",     m_szGroupDisable);
    //        FindNodeValue(ResNode, "IDS_Group_Can_not_Enable",      m_szGroupEnable);
    //        FindNodeValue(ResNode, "IDS_Translate",                 m_szTranslate);
    //        FindNodeValue(ResNode, "IDS_Translate_Tip",             m_szTranslateTip);
    //        FindNodeValue(ResNode, "IDS_Refresh",                   m_szRefresh);
    //        FindNodeValue(ResNode, "IDS_Refresh_Tip",               m_szRefreshTip);
    //    }
    //    CloseResource(objRes);  // 关闭资源
    //}
//}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddNewGroup
// 说明 添加子组处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewGroup()
{
    ShowActivateView(active_add_group);     // 更改当前显示视图
    if(m_pAddGroup)
    {
        // 设置父组索引
        if(m_GeneralList.m_pGroup)
            m_pAddGroup->SetParentIndex(string(m_GeneralList.m_pGroup->getGroupIndex()));
        // 初始化所有参数
        m_pAddGroup->ResetParam();
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditGroupParam
// 说明 根据组索引修改组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditGroupParam(string szIndex)
{
    ShowActivateView(active_add_group);     // 更改当前显示视图
    m_szEditIndex = szIndex;                // 当前编辑的索引
    // 显示编辑组视图
    if(m_pAddGroup)
        m_pAddGroup->EditGroup(szIndex);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditGroupData
// 说明 成功编辑指定组处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditGroupData(string szName, string szIndex)
{
    // 得到父节点索引
    string szParentID = FindParentID(szIndex);
    // 编辑的是当前组
    if(m_GeneralList.m_pGroup && 
        szParentID.compare(m_GeneralList.m_pGroup->getGroupIndex()) == 0 )
        m_GeneralList.m_pGroup->EditGroup(szName, szIndex);    

    // 发起编辑组成功消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_EDIT;
    response.nNodeType = Tree_GROUP;
    response.strNodeId = szIndex;
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess =true;
    response.strName = szName;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Group") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + 
        "---parent id is " + response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") +
        ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddGroupData
// 说明 成功添加组处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddGroupData(string szName,string szIndex)
{   
    // 发起添加组成功消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_ADD;
    response.nNodeType = Tree_GROUP;
    response.strNodeId = szIndex;
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess =true;
    response.strName = szName;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Group") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + 
        response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);

    m_nPreviewView = active_group_view; // 重置上一视图
    enterSVSE(szIndex);                 // 进入当前组

    emit ChangeSelNode(szIndex);        // 发起更改选择节点消息
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 showMainView
// 说明 显示主视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::showMainView()
{
    ShowActivateView(m_nPreviewView);           // 显示上一视图
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EnterNewDeviceByID
// 说明 进入新添加的组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EnterNewDeviceByID(string szDeviceID)
{
    ShowActivateView(active_monitor_view);          // 更改当前显示视图
    if(m_pMonitorview)
        m_pMonitorview->enterDevice(szDeviceID);    // 进入设备

    // 发起更改选择节点消息
    emit ChangeSelNode(szDeviceID);
    
    // 刷新
    string szRefreshMonitor (""), szDevName("");
    // 打开设备
    OBJECT objDevice = GetEntity(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// 打开设备成功
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);

        if(mainnode != INVALID_VALUE)
        {
            FindNodeValue(mainnode, "sv_name", szDevName);
        }

        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {// 得到监测器列表成功
            string szQuery ("");
            if(lsMonitorID.size() > 0)
            {// 监测器总数大于零
                
                // 创建刷新回写队列名
                string szQueueName(makeQueueName());
                // 创建回写队列
                CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                // 创建刷新队列
                string szRefreshQueue(getRefreshQueueName(szDeviceID));
                CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);

                for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                {// 遍历每一个监测器
                    
                    // 将快速添加的监测记录到操作日志中
                    int nOptType = SV_ADD, nObjType = Tree_MONITOR, nMTID = 0;
                    string szMonitorName(getMonitorNameMTID((*lstItem), nMTID, m_szIDCUser, m_szIDCPwd));

                    string szMsg = SVResString::getResString("IDS_Quick_Add") + SVResString::getResString("IDS_Monitor_Title") +
                        "(Index)" + (*lstItem) + "---" + SVResString::getResString("IDS_Name") + ":" + szMonitorName +
                        "---parent id is: "  + ":" + szDeviceID + "---" + SVResString::getResString("IDS_Name") + ":" + szDevName;
                    AddOperaterLog(nOptType, nObjType, szMsg);
                    
                    if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
                    {// 监测器没有被禁止
                        szQuery += (*lstItem);
                        szQuery += "\v";
                    }
                    else
                    {// 监测器被禁止
                        int nSize = static_cast<int>((*lstItem).length()) + 2;
                        char *pszRefreshMonitor = new char[nSize];
                        if(pszRefreshMonitor)
                        {  
                            memset(pszRefreshMonitor, 0, nSize);
                            strcpy( pszRefreshMonitor, (*lstItem).c_str());
                            // 插入一条监测器被禁止消息
                            if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                                PrintDebugString("PushMessage into queue failed!");
                            delete []pszRefreshMonitor;
                        }
                    }
                }
                int nSize = static_cast<int>(szQuery.length()) + 1;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, szQuery.c_str());
                    // 整理消息内容
                    char *pPos = pszRefreshMonitor;
                    while((*pPos) != '\0' )
                    {
                        if((*pPos) == '\v')
                            (*pPos) = '\0';
                        pPos ++;
                    }
                    // 插入刷新消息
                    if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
                    delete [] pszRefreshMonitor;
                }
                m_nActiveOptType = Tree_DEVICE;
                m_szActiveOptIndex = szDeviceID;
                // JS 函数
                szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
            }
        }
    }
    WebSession::js_af_up = szRefreshMonitor + "hiddenbar();update('" + m_szGlobalEvent + "');";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EnterDeviceByID
// 说明 进入设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EnterDeviceByID(string szDeviceID)
{
    ShowActivateView(active_monitor_view);          // 更改当前显示视图
    if(m_pMonitorview)
    {
        // 进入设备
        m_pMonitorview->enterDevice(szDeviceID);
        // 发起更改选择节点消息
        emit ChangeSelNode(szDeviceID);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddNewDevice
// 说明 添加新的设备，显示设备模版列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewDevice()
{
    ShowActivateView(active_add_device1st);             // 更改当前显示视图（添加设备第一步）
    if(m_GeneralList.m_pGroup)
    {
        // 设置父组索引
        string szIndex = m_GeneralList.m_pGroup->getGroupIndex();
        if(m_pDeviceList)
            m_pDeviceList->setParentIndex(szIndex);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddDevice2nd
// 说明 根据设备模版名称显示不同内容
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddDevice2nd(string szIndex)
{
    ShowActivateView(active_add_device2nd);
    if(m_pDevice)
    { 
        // 设置父组索引
        if(m_pDeviceList)
            m_pDevice->SetParentIndex(m_pDeviceList->getParentID());   
        // 重置所有参数
        m_pDevice->ClearData(szIndex);
        // 请求动态参数
        m_pDevice->requesDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EnumDevice
// 说明 枚举当前组下的设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EnumDevice(string szIndex)
{
    // 是否是单机版
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {// 是
        if(m_GeneralList.m_pBackParent)
        {
            // 判断父节点是否是SE根据不同情况选择返回上一级按钮的显示/隐藏
            string szIndex = m_GeneralList.m_pGroup->getGroupIndex();
            int nPos = static_cast<int>(szIndex.find("."));
            if(nPos > 0)
                m_GeneralList.m_pBackParent->show();
            else
                m_GeneralList.m_pBackParent->hide();
        }
    }

    if(m_pTitleCell)
    {// 标题 Cell 不是空指针
        // 得到路径
        list<base_param> lsPath = m_GeneralList.m_pGroup->getGroupPath();
        
        // 移除绑定
        list<WText*>::iterator itPath;
        for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
            m_GroupName.removeMappings((*itPath));

        // 列表清空
        m_lsPath.clear();
        // 清除cell内所有的控件
        m_pTitleCell->clear();

        // 为每一个组创建一个处理onclick事件的文本控件（不包括当前组）
        list<base_param>::iterator pathItem;
        base_param svparam;
        while(lsPath.size() > 1)
        {
            svparam = lsPath.back();
            lsPath.pop_back();

            WText *pPath = new WText(svparam.szName, m_pTitleCell);
            if(pPath)
            {
                // 设置样式表
                pPath->setStyleClass("tgrouptitle") ;
                // onclick
                WObject::connect(pPath, SIGNAL(clicked()), "showbar();", &m_GroupName, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                m_GroupName.setMapping(pPath, svparam.szIndex);
                m_lsPath.push_back(pPath);
            }
            // ：
            WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitleCell);
            if(pTemp)
                pTemp->setStyleClass("tgrouptitle2") ;
        }
        // 当前组
        svparam = lsPath.back();
        lsPath.pop_back();
        WText * pTitle = new WText(svparam.szName, m_pTitleCell);
        if(pTitle)
            pTitle->setStyleClass("tgrouptitle2") ;
    }

    if(m_GeneralList.m_pDevice)
    {
        // 枚举当前组内所有设备
        m_GeneralList.m_pDevice->EnterGroup(szIndex);
        if(m_GeneralList.m_pStandard)
        {// 更新基础信息显示内容
            string szName = m_GeneralList.m_pGroup->getGroupName();
            m_GeneralList.m_pStandard->setTitle(szName);
            string szDesc = m_GeneralList.m_pGroup->getGroupDesc();
            m_GeneralList.m_pStandard->setDescription(szDesc);

            m_GeneralList.m_pStandard->m_nDeviceCount = m_GeneralList.m_pDevice->m_nDeviceCount + 
                m_GeneralList.m_pGroup->m_nDeviceCount;
            m_GeneralList.m_pStandard->m_nMonitorCount = m_GeneralList.m_pDevice->m_nMonitorCount + 
                m_GeneralList.m_pGroup->m_nMonitorCount; 
            m_GeneralList.m_pStandard->m_nMonitorErrCount = m_GeneralList.m_pDevice->m_nMonitorErrCount + 
                m_GeneralList.m_pGroup->m_nMonitorErrCount;
            m_GeneralList.m_pStandard->m_nMonitorWarnCount = m_GeneralList.m_pDevice->m_nMonitorWarnCount + 
                m_GeneralList.m_pGroup->m_nMonitorWarnCount; 
            m_GeneralList.m_pStandard->m_nMonitorDisableCount = m_GeneralList.m_pDevice->m_nMonitorDisableCount + 
                m_GeneralList.m_pGroup->m_nMonitorDisableCount; 
            m_GeneralList.m_pStandard->m_szAdvState = m_GeneralList.m_pGroup->m_szAdvState;
            m_GeneralList.m_pStandard->setState();
        }
    }
    // 发起更改选择节点消息
    emit ChangeSelNode(szIndex);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddNewDeviceSucc
// 说明 添加设备成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewDeviceSucc(string szName, string szIndex)
{
    // 发起添加设备成功消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_ADD;
    response.nNodeType = Tree_DEVICE;
    response.strName = szName;
    response.strNodeId = szIndex;		
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess = true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);  

    // 将前一视图置为 监测器视图
    m_nPreviewView = active_monitor_view;

    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " +
        response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 CopyNewDeviceSucc
// 说明 拷贝设备成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::CopyNewDeviceSucc(string szName, string szIndex)
{
    // 发起添加设备成功消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_ADD;
    response.nNodeType = Tree_DEVICE;
    response.strName = szName;
    response.strNodeId = szIndex;		
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess = true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Copy") + SVResString::getResString("IDS_Past") + 
        SVResString::getResString("IDS_Monitor_Title") + "(Index)" + szIndex +
        "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + response.strParentNodeId + "---" + 
        SVResString::getResString("IDS_Name") + ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 CopyNewMonitorSucc
// 说明 拷贝设备成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::CopyNewMonitorSucc(string szName, string szIndex)
{
    // 发起添加设备成功消息
    int nOptType = SV_ADD, nObjType = Tree_MONITOR;

    string szMsg = SVResString::getResString("IDS_Copy") + SVResString::getResString("IDS_Past")
        + SVResString::getResString("IDS_Device") + "(Index)" + szIndex + "---" + 
        SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is: " +
        ":" + FindParentID(szIndex) + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getDeviceNameByID(FindParentID(szIndex), m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(nOptType, nObjType, szMsg);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddMonitor
// 说明 根据设备的类型显示不同的监测器模版列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddMonitor(string szDeviceType,string szDeviceID)
{
    m_lsNewMonitorList.clear();             // 新监测器列表清空
    ShowActivateView(active_add_monitor1st);// 更改当前显示视图
    if(m_pMonitorList)
    {
        //PrintDebugString("enum monitor templet");
        // 根据设备类型枚举监测器模版
        m_pMonitorList->enumMonitorTempByType(szDeviceType,szDeviceID);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditDeviceSuccByID
// 说明 编辑设备成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditDeviceSuccByID(string szName, string szIndex)
{
    // 更新当前设备列表此设备的显示名称
    if(m_GeneralList.m_pDevice)
        m_GeneralList.m_pDevice->EditDevice(szName, szIndex);

    // 发起编辑设备成功消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_EDIT;
    response.nNodeType = Tree_DEVICE;
    response.strNodeId = szIndex;
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess = true;
    response.strName = szName;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Device") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + 
        "---parent id is " + response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") + 
        ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddMonitorSucc
// 说明 添加监测器成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddMonitorSucc(string szName, string szIndex)
{
    string szParentID = FindParentID(szIndex);
    m_lsNewMonitorList.push_back(szIndex);          // 添加到新监测器列表中

    int nOptType = SV_ADD, nObjType = Tree_MONITOR;

    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Monitor_Title") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName +
        "---parent id is: "  + ":" + FindParentID(szIndex) + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getDeviceNameByID(FindParentID(szIndex), m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(nOptType, nObjType, szMsg);
    // 更新相关视图的显示信息
    if(m_pMonitorview)
    {
        if(m_pMonitorview->GetCurrentID() == szParentID)
        {
            // 隐藏 无子 控件
            if(m_pMonitorview->m_pHasNoChild)
                m_pMonitorview->m_pHasNoChild->hide();
            // 添加新的检测
            m_pMonitorview->AddMonitorView(szName, szIndex);
            // 刷新状态
            m_pMonitorview->refreshState();
        }
    }
    if(m_GeneralList.m_pGroup)
    {
        // 是否是当前组列表内某一设备下添加了新的监测器
        if(m_GeneralList.m_pGroup->isInGroup(szParentID))
        {
            // 更新基础信息
            if(m_GeneralList.m_pStandard)
            {
                m_GeneralList.m_pStandard->m_nMonitorCount ++;
                m_GeneralList.m_pStandard->setState();
            }
            // 刷新组信息
            m_GeneralList.m_pGroup->refreshGroup(szIndex);
            if(m_GeneralList.m_pDevice)
                m_GeneralList.m_pDevice->refreshDevice(szIndex);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 CancelAddMonitor
// 说明 取消添加监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::CancelAddMonitor()
{
    ShowActivateView(m_nPreviewView);                   // 更改当前显示视图
    string szRefreshMonitor ("");
    if(m_lsNewMonitorList.size() > 0)
    {// 新监测器列表不为空
        // 创建刷新回写队列名称
        string szQueueName(makeQueueName());
        // 创建刷新回写队列
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
        // 创建刷新队列
        list<string>::iterator lstItem(m_lsNewMonitorList.begin());
        string szRefreshQueue(getRefreshQueueName((*lstItem)));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
        
        string szQuery ("");
        
        for(lstItem = m_lsNewMonitorList.begin(); lstItem != m_lsNewMonitorList.end(); lstItem ++)
        {// 枚举每一个监测器索引
            if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
            {// 监测没有被禁止
                szQuery += (*lstItem);
                szQuery += "\v";
            }
            else
            {// 被禁止
                int nSize = static_cast<int>((*lstItem).length()) + 2;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, (*lstItem).c_str());
                    // 插入一条被禁止消息到刷新回写队列
                    if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("PushMessage into queue failed!");
                    delete []pszRefreshMonitor;
                }
            }
        }
        int nSize = static_cast<int>(szQuery.length()) + 1;
        char *pszRefreshMonitor = new char[nSize];
        if(pszRefreshMonitor)
        {
            memset(pszRefreshMonitor, 0, nSize);
            strcpy( pszRefreshMonitor, szQuery.c_str());
            char *pPos = pszRefreshMonitor;
            while((*pPos) != '\0' )
            {
                if((*pPos) == '\v')
                    (*pPos) = '\0';
                pPos ++;
            }
            
            // 插入刷新消息到刷新队列
            if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            
            delete [] pszRefreshMonitor;
        }                    
        // JS函数
        szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
        szRefreshMonitor = szRefreshMonitor + "update('" + m_szGlobalEvent + "');";
    } 
    szRefreshMonitor += "hiddenbar();";
    WebSession::js_af_up = szRefreshMonitor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditMonitorSuccByID
// 说明 编辑监测器成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditMonitorSuccByID(string szName, string szIndex)
{
    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Monitor_Title") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName +
        "---parent id is: "  + ":" + FindParentID(szIndex) + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getDeviceNameByID(FindParentID(szIndex), m_szIDCUser, m_szIDCPwd);

    int nOptType = SV_EDIT, nObjType = Tree_MONITOR;
    AddOperaterLog(nOptType, nObjType, szMsg);

    static const string szRefreshEnd = "Refresh_END";
    ShowActivateView(m_nPreviewView);
    if(m_pMonitorview)
    {
        m_pMonitorview->EditMonitorView(szName, szIndex);
        // 创建刷新回写队列名称
        string szQueueName(makeQueueName());
        // 创建刷新回写队列
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
        // 创建刷新队列
        string szRefreshQueue(getRefreshQueueName(szIndex));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
        
        int nSize = static_cast<int>(szIndex.length()) + 2;
        char *pszRefreshMonitor = new char[nSize];
        if(pszRefreshMonitor)
        {
            memset(pszRefreshMonitor, 0, nSize);
            strcpy( pszRefreshMonitor, szIndex.c_str());
            if(!isMonitorDisable(szIndex, m_szIDCUser, m_szIDCPwd))
            {// 监测器没有被禁止
                if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            }
            else
            {// 被禁止
                // 插入一条被禁止消息
                if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into queue failed!");
                // 插入停止刷新消息
                if(!::PushMessage(szQueueName, szRefreshEnd, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into queue failed!");
            }
            
            // 更改当前操作索引
            m_szActiveOptIndex = m_pMonitorview->GetCurrentID();
            // 更改当前操作类型
            m_nActiveOptType = Tree_DEVICE;

            // JS
            string szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
            if(!m_szGlobalEvent.empty())
                szRefreshMonitor = szRefreshMonitor + "update('" + m_szGlobalEvent + "');";

            WebSession::js_af_up = szRefreshMonitor;
            delete [] pszRefreshMonitor;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 BackMonitorList
// 说明 返回监测器模版列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::BackMonitorList()
{
    ShowActivateView(active_add_monitor1st);   
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddNewMonitorByType
// 说明 显示监测器参数视图（添加监测器第二步）根据监测器的模版索引
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewMonitorByType(int nMTID, string szDeviceID)
{
    ShowActivateView(active_add_monitor2nd);
    if(m_pMonitor)
    {
        // 显示监测器参数根据监测器的模版并设置父设备的索引
        m_pMonitor->showMonitorParam(nMTID, szDeviceID);
        // 请求动态参数
        m_pMonitor->requesDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditDeviceByIndex
// 说明 根据设备的索引编辑设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditDeviceByIndex(string szDeviceIndex)
{
    ShowActivateView(active_edit_device);
    m_szEditIndex = szDeviceIndex;                  // 当前编辑
    if(m_pDevice)
    {
        // 更改当前编辑的设备索引
        if(m_pcurEditIndex)
            m_pcurEditIndex->setText(m_szEditIndex);

        // 编辑设备
        m_pDevice->EditDeviceByID(szDeviceIndex);
        // 请求动态参数
        m_pDevice->requesDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditMonitorByIndex
// 说明 根据监测器索引编辑监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditMonitorByIndex(string szMonitorIndex)
{
    m_lsNewMonitorList.clear();             // 新监测器列表清空
    ShowActivateView(active_edit_monitor);
    if(m_pMonitor)
    {
        m_pMonitor->EditMonitorByID(szMonitorIndex);    // 编辑监测器
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 BackGroupDeviceList
// 说明 从监测器视图返回到组视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::BackGroupDeviceList(string szGroupID)
{
    ShowActivateView(active_group_view);            // 更改当前显示视图
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->BackGroup(szGroupID);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 backSVSEView
// 说明 返回到SE 视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::backSVSEView()
{
    ShowActivateView(m_nPreviewView);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditSVSEByIndex
// 说明 根据SE索引编辑SE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditSVSEByIndex(string szIndex)
{
    ShowActivateView(active_add_se);
    if(m_pAddSVSE)
    {	       
        m_pAddSVSE->EditSVSE(szIndex);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 EditSVSESuccByIndex
// 说明 编辑SE成功
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditSVSESuccByIndex(string szName, string szIndex)
{
    if (m_pSVSEView)
        m_pSVSEView->EditSEView(szName, szIndex); 

    // 发起编辑SE成功消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_EDIT;
    response.nNodeType = Tree_SE;
    response.strNodeId = szIndex;
    response.strName = szName;
    response.strParentNodeId = "-1";
    response.bSucess =true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_SE") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName;

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enterSVSE
// 说明 根据SE索引进入相应的SE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::enterSVSE(string szSEID)
{
    ShowActivateView(active_group_view);
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->EnterGroupByID(szSEID);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 DelGroupByIdProc
// 说明 删除组处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::DelGroupByIdProc(string szName, string strId)
{
    // 发起删除组消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_DELETE;
    response.nNodeType = Tree_GROUP;
    response.strName = "";
    response.strNodeId = strId;
    response.strParentNodeId = FindParentID(strId);
    response.bSucess =true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Group") + 
        "(Index)" + response.strNodeId + "---" + SVResString::getResString("IDS_Name") + ":" +
        szName + "---parent id is " + response.strParentNodeId + "---" + 
        SVResString::getResString("IDS_Name") + ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);

    // 更新基础信息
    m_GeneralList.m_pStandard->m_nDeviceCount = m_GeneralList.m_pDevice->m_nDeviceCount + 
        m_GeneralList.m_pGroup->m_nDeviceCount;
    m_GeneralList.m_pStandard->m_nMonitorCount = m_GeneralList.m_pDevice->m_nMonitorCount + 
        m_GeneralList.m_pGroup->m_nMonitorCount; 
    m_GeneralList.m_pStandard->m_nMonitorErrCount = m_GeneralList.m_pDevice->m_nMonitorErrCount + 
        m_GeneralList.m_pGroup->m_nMonitorErrCount;
    m_GeneralList.m_pStandard->m_nMonitorWarnCount = m_GeneralList.m_pDevice->m_nMonitorWarnCount + 
        m_GeneralList.m_pGroup->m_nMonitorWarnCount; 
    m_GeneralList.m_pStandard->m_nMonitorDisableCount = m_GeneralList.m_pDevice->m_nMonitorDisableCount + 
        m_GeneralList.m_pGroup->m_nMonitorDisableCount; 
    m_GeneralList.m_pStandard->setState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 DelDeviceByIdProc
// 说明 删除设备处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::DelDeviceByIdProc(string szName, string strId)
{
    // 发起设备删除消息
    MENU_RESPONSE response;	
    response.nOperatCode = SV_DELETE;
    response.nNodeType = Tree_DEVICE;
    response.strNodeId = strId;
    response.strParentNodeId = FindParentID(strId);
    response.bSucess =true;
    response.strErrorMsg = "";
    response.strName = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Device") + 
        "(Index)" + response.strNodeId + "---" + SVResString::getResString("IDS_Name") + ":" +
        szName + "---parent id is " + response.strParentNodeId + "---" + 
        SVResString::getResString("IDS_Name") + ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);

    // 更新基础信息
    m_GeneralList.m_pStandard->m_nDeviceCount = m_GeneralList.m_pDevice->m_nDeviceCount + 
        m_GeneralList.m_pGroup->m_nDeviceCount;
    m_GeneralList.m_pStandard->m_nMonitorCount = m_GeneralList.m_pDevice->m_nMonitorCount + 
        m_GeneralList.m_pGroup->m_nMonitorCount; 
    m_GeneralList.m_pStandard->m_nMonitorErrCount = m_GeneralList.m_pDevice->m_nMonitorErrCount + 
        m_GeneralList.m_pGroup->m_nMonitorErrCount;
    m_GeneralList.m_pStandard->m_nMonitorWarnCount = m_GeneralList.m_pDevice->m_nMonitorWarnCount + 
        m_GeneralList.m_pGroup->m_nMonitorWarnCount; 
    m_GeneralList.m_pStandard->m_nMonitorDisableCount = m_GeneralList.m_pDevice->m_nMonitorDisableCount + 
        m_GeneralList.m_pGroup->m_nMonitorDisableCount; 
    m_GeneralList.m_pStandard->setState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 MenuItemRequestProc
// 说明 树节点菜单消息处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::MenuItemRequestProc(MENU_REQUEST request)
{
    string szRefreshMonitor (""), szMsg(""), szName("");
    m_szEditIndex = "";
    m_nActiveOptType = -1;
    m_szActiveOptIndex = "";

    //char chMsg[512] = {0};
    //sprintf(chMsg, "operate code %d, node type : %d", request.nOperatCode, request.nNodeType);
    //PrintDebugString(chMsg);
    // 根据操作码
    switch(request.nOperatCode)
    {
    case SV_ADD_GROUP :   // 添加
            AddNewGroup();      //显示增加组界面
            //设置添加组的父节点索引
            if(m_pAddGroup)
                m_pAddGroup->SetParentIndex(request.strNodeId);
            break;
    case SV_ADD_DEVICE:
        AddNewDevice();     //显示增加设备界面
        // 设置增加设备的父节点索引
        if(m_pDeviceList)
            m_pDeviceList->setParentIndex(request.strNodeId);
        break;
        case SV_ADD_MONITOR:
            //PrintDebugString("Add new monitor");
            //PrintDebugString("Device Type is : " + GetDeviceTypeById(request.strNodeId, m_szIDCUser, m_szIDCPwd));
            AddMonitor(GetDeviceTypeById(request.strNodeId, m_szIDCUser, m_szIDCPwd),  request.strNodeId);
            break;
    case SV_EDIT:   // 编辑
        switch(request.nNodeType)
        {
        case Tree_SE:
            EditSVSEByIndex(request.strNodeId);         //显示编辑SE界面
            break;
        case Tree_GROUP:
            EditGroupParam(request.strNodeId);          //显示编辑组界面
            break;
        case Tree_DEVICE:            
            EditDeviceByIndex(request.strNodeId);       //显示编辑设备界面
            break;
        }
        break;
    case SV_DELETE: // 删除
        szMsg = SVResString::getResString("IDS_Delete");
        switch(request.nNodeType)
        {
        case Tree_GROUP:
            szMsg += SVResString::getResString("IDS_Group");
            szName = getGroupNameByID(request.strNodeId, m_szIDCUser, m_szIDCPwd);
            break;
        case Tree_DEVICE:
            szName = getDeviceNameByID(request.strNodeId, m_szIDCUser, m_szIDCPwd);
            szMsg += SVResString::getResString("IDS_Device");
            break;
        }
        
        szMsg += "(Index)" + request.strNodeId + SVResString::getResString("IDS_Name") + ":" + szName +
            "---parent id is: "  + ":" + request.strParentNodeId + "---" + 
            SVResString::getResString("IDS_Name") + ":" + 
            getGroupNameByID(FindParentID(request.strNodeId), m_szIDCUser, m_szIDCPwd);

        AddOperaterLog(request.nOperatCode, request.nNodeType, szMsg);
        deleteObject(request.strNodeId);                // 调用删除处理函数
        break;
    case SV_ENABLE: // 启用
        m_nActiveOptType = request.nNodeType;
        m_szActiveOptIndex = request.strNodeId;
        switch(request.nNodeType)
        {
        case Tree_GROUP:
            if(isGroupDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) != sv_enable_state)
            {// 组已禁止
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=0&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
            }
            else
            {// 显示不能再次启用消息
                szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";
            }
            break;
        case Tree_DEVICE:
            if(isDeviceDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) != sv_enable_state)
            {// 设备已禁止
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=1&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
             }
            else
            {// 显示不能再次启用消息
                szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";             
            }
        }
        break;
    case SV_DISABLE: // 禁止
        m_nActiveOptType = request.nNodeType;
        m_szActiveOptIndex = request.strNodeId;
        switch(request.nNodeType)
        {
        case Tree_GROUP:
            if(isGroupDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) == sv_enable_state)
            {// 组已启用
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=0&operatetype=0&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
            }
            else
            {// 组已禁止
                   szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Disable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";    
            }
            break;
        case Tree_DEVICE:
            if(isDeviceDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) == sv_enable_state)
            {// 设备已启用
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=1&operatetype=0&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
            }
            else
            {// 设备已禁止
                   szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Disable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";    
            }
            break;
        }
        break;
    case SV_REFRESH:// 刷新
        m_nActiveOptType = request.nNodeType;
        m_szActiveOptIndex = request.strNodeId;
        if(request.nNodeType == Tree_DEVICE)
        {// 只有设备可以被刷新
            // 打开设备
            OBJECT objDevice = GetEntity(request.strNodeId, m_szIDCUser, m_szIDCPwd);
            if(objDevice != INVALID_VALUE)
            {// 打开设备成功
                list<string> lsMonitorID;
                list<string>::iterator lstItem;
                if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
                {// 得到设备下所有的监测器
                    string szQuery ("");
                    if(lsMonitorID.size() > 0)
                    {// 监测器总数大于零
                        // 创建刷新回写队列名
                        string szQueueName(makeQueueName());
                        // 创建刷新回写队列
                        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                        // 创建刷新队列
                        string szRefreshQueue(getRefreshQueueName(request.strNodeId));
                        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
                        for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                        {// 枚举每个监测器
                            if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
                            {// 监测器没有被禁止
                                szQuery += (*lstItem);
                                szQuery += "\v";
                            }
                            else
                            {// 监测器被禁止
                                int nSize = static_cast<int>((*lstItem).length()) + 2;
                                char *pszRefreshMonitor = new char[nSize];
                                if(pszRefreshMonitor)
                                {  
                                    memset(pszRefreshMonitor, 0, nSize);
                                    strcpy( pszRefreshMonitor, (*lstItem).c_str());
                                    // 插入一条监测器被禁止消息到刷新回写队列
                                    if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                                        PrintDebugString("PushMessage into queue failed!");
                                    delete []pszRefreshMonitor;
                                }
                            }
                        }                
                        int nSize = static_cast<int>(szQuery.length()) + 1;
                        char *pszRefreshMonitor = new char[nSize];
                        if(pszRefreshMonitor)
                        {
                            memset(pszRefreshMonitor, 0, nSize);
                            strcpy( pszRefreshMonitor, szQuery.c_str());
                            char *pPos = pszRefreshMonitor;
                            while((*pPos) != '\0' )
                            {
                                if((*pPos) == '\v')
                                    (*pPos) = '\0';
                                pPos ++;
                            }
                            // 插入刷新消息到刷新队列
                            if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                                PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
                            delete [] pszRefreshMonitor;
                        }                    
                        szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "')";
                    }
                }
            }
        }
        break;
    case SV_CLICK:  // 单击
        switch(request.nNodeType)
        {
        case Tree_SEGROUP:
            ShowActivateView(active_se_view);       // 显示 SE 视图
            break;
        case Tree_SE:
            enterSVSE(request.strNodeId);           // 进入 SE
            break;
        case Tree_GROUP:
            ShowActivateView(active_group_view);    // 显示 组 视图
            if(m_GeneralList.m_pGroup)
            {
                // 进入 组
                m_GeneralList.m_pGroup->EnterGroupByID(request.strNodeId);
            }
            break;
        case Tree_DEVICE:
            // 进入 设备
            EnterDeviceByID(request.strNodeId);
            break;
        }
        break;
    }
    if(!szRefreshMonitor.empty())
        WebSession::js_af_up = szRefreshMonitor + ";update('" + m_szGlobalEvent + "');hiddenbar();";
    else if(request.nNodeType != Tree_DEVICE )
        WebSession::js_af_up = "hiddenbar()";
    else if(request.nOperatCode != SV_EDIT)
        WebSession::js_af_up = "hiddenbar()";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ShowActivateView
// 说明 根据请求更改显示视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ShowActivateView(int nActivateView)
{
    // 当前视图是 SE视图/组视图/监测器视图
    if(m_nActiveView == active_se_view ||  m_nActiveView == active_group_view ||
        m_nActiveView == active_monitor_view)
    {
        // 上一视图 更新
        m_nPreviewView = m_nActiveView;
    }
    
    // 根据当前视图进行操作
    switch(m_nActiveView)
    {
    case active_edit_device:    // 编辑设备
        if(m_pMonitorview && !m_szEditIndex.empty())
            if(m_pMonitorview->isParentEdit(m_szEditIndex))
                m_pMonitorview->refreshNamePath();
        break;
    case active_add_group:      // 添加组
        if(m_GeneralList.m_pGroup && !m_szEditIndex.empty() && m_pTitleCell)
        {
            // 是否是父组被修改
            if(m_GeneralList.m_pGroup->isParentEdit(m_szEditIndex))
            {
                // 刷新路径
                m_GeneralList.m_pGroup->refreshNamePath();
                // 得到新的路径
                list<base_param> lsPath = m_GeneralList.m_pGroup->getGroupPath();
                
                // 移除绑定
                list<WText*>::iterator itPath;
                for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
                    m_GroupName.removeMappings((*itPath));

                // 列表清空
                m_lsPath.clear();
                // 清除cell内所有的控件
                m_pTitleCell->clear();

                // 为每一个组创建一个处理onclick事件的文本控件（不包括当前组）
                list<base_param>::iterator pathItem;
                base_param svparam;
                while(lsPath.size() > 1)
                {
                    svparam = lsPath.back();
                    lsPath.pop_back();

                    WText *pPath = new WText(svparam.szName, m_pTitleCell);
                    if(pPath)
                    {
                        // 设置样式表
                        pPath->setStyleClass("tgrouptitle") ;
                        // onclick
                        WObject::connect(pPath, SIGNAL(clicked()), "showbar();", &m_GroupName, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_GroupName.setMapping(pPath, svparam.szIndex);
                        m_lsPath.push_back(pPath);
                    }
                    // ：
                    WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitleCell);
                    if(pTemp)
                        pTemp->setStyleClass("tgrouptitle2") ;
                }
                // 当前组
                svparam = lsPath.back();
                lsPath.pop_back();
                WText * pTitle = new WText(svparam.szName, m_pTitleCell);
                if(pTitle)
                    pTitle->setStyleClass("tgrouptitle2") ;

                if(m_GeneralList.m_pStandard)
                {
                    string szName = m_GeneralList.m_pGroup->getGroupName();
                    m_GeneralList.m_pStandard->setTitle(szName);
                    string szDesc = m_GeneralList.m_pGroup->getGroupDesc();
                    m_GeneralList.m_pStandard->setDescription(szDesc);
                }
            }
        }        
        break;
    }
    m_nActiveView = nActivateView;
    m_szEditIndex = "";
    //隐藏所有视图
    if(m_pSVSEView)
        m_pSVSEView->hide();	
    if(m_GeneralList.m_pGroupview)
        m_GeneralList.m_pGroupview->hide();
    if(m_pMonitorview)
        m_pMonitorview->hide();
    if(m_pAddGroup)
        m_pAddGroup->hide();
    if(m_pDeviceList)
        m_pDeviceList->hide();
    if(m_pDevice)
        m_pDevice->hide();
    if(m_pMonitorList)
        m_pMonitorList->hide();
    if(m_pMonitor)
        m_pMonitor->hide();
    if(m_pAddSVSE)
        m_pAddSVSE->hide();
    if(m_pBatchAdd)
        m_pBatchAdd->hide();
    if(m_pSortForm)
        m_pSortForm->hide();

    // 得到当前时间
    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();
    //显示激活视图
    switch(nActivateView)
    {
    case active_se_view:                        // SE 视图
        if(m_pSVSEView == NULL)
        {// SE 未初始化
            // 初始化SE视图
            m_pSVSEView = new SVSEView(this, m_pSVUser);
            if(m_pSVSEView)
            {
                // 绑定 进入SE消息
                WObject::connect(m_pSVSEView, SIGNAL(showSVSE(string)), this, SLOT(enterSVSE(string)));
                // 绑定 根据SE索引编辑SE消息
                WObject::connect(m_pSVSEView, SIGNAL(EditSEByID(string)), this, SLOT(EditSVSEByIndex(string)));
            }			
        }
        if(m_pSVSEView)
        {            
            m_pSVSEView->show();                    // 显示SE 视图
            m_pSVSEView->refreshSElist();           // 刷新 SE 列表
            m_pSVSEView->setCurrentTime(curTime);   // 设置显示时间
        }
        break;
    case active_group_view:                         // 组视图
        if(m_GeneralList.m_pGroupview == NULL)
        {// 组视图 没有初始化
            // 组视图初始化
            m_GeneralList.m_pGroupview = new WTable(this);
            if(m_GeneralList.m_pGroupview)
            {
                // 设置主表的样式表
                m_GeneralList.m_pGroupview->setStyleClass("t5");
                int nRow = m_GeneralList.m_pGroupview->numRows();
                // 创建内容显示表
                WTable *pContent = new WTable(m_GeneralList.m_pGroupview->elementAt(nRow, 0));
                if(pContent)
                {
                    WScrollArea *pScrollArea = new WScrollArea(m_GeneralList.m_pGroupview->elementAt(nRow,0));
                    if(pScrollArea)
                    {
                        pScrollArea->setStyleClass("t5");           // 滚动区设置样式表
                        pScrollArea->setWidget(pContent);           // 此滚动区隶属于内容表
                    }        
                    pContent->setStyleClass("t5");                  // 设置内容标的样式表
                    // 设置主表的 cell(nRow, 0)的样式表
                    m_GeneralList.m_pGroupview->elementAt(nRow, 0)->setStyleClass("t10");
                    // 得到内容表的当前行数
                    nRow = pContent->numRows();
                    // 创建主内容表
                    m_GeneralList.m_pGeneral = new WTable(pContent->elementAt(nRow,0));
                    // 设置内容表 cell(nRow, 0)对齐方式（左上对齐）
                    pContent->elementAt(nRow, 0)->setContentAlignment(AlignLeft | AlignTop);
                    if (m_GeneralList.m_pGeneral)
                    {
                        m_GeneralList.m_pGeneral->setStyleClass("t8");// 设置主内容表样式表
                        AddTitle();                 // 标题
                        AddViewControl();           // 控制
                        AddStandard();              // 基础信息
                        AddGroup();                 // 组列表
                        AddEntity();                // 设备列表
                    }
                }
                nRow = m_GeneralList.m_pGroupview->numRows();
                // 状态描述
                new CSVStateDesc(m_GeneralList.m_pGroupview->elementAt(nRow, 0));
            }
        }
        if(m_GeneralList.m_pGroupview)
        {
            // 显示主表
            m_GeneralList.m_pGroupview->show();
            // 设置当前时间
            if(m_GeneralList.m_ptxtTime)
                m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        }
        break;
    case active_monitor_view:                       // 监测器视图
        if(m_pMonitorview == NULL)
        {// 监测器视图未初始化
            // 创建监测器视图
            m_pMonitorview = new SVMonitorview(this, m_pSVUser);
            if(m_pMonitorview)
            {
                // 绑定 添加监测器消息
                WObject::connect(m_pMonitorview, SIGNAL(AddNewMonitor(string,string)),this, SLOT(AddMonitor(string,string)));
                // 绑定 编辑监测器消息
                WObject::connect(m_pMonitorview, SIGNAL(EditMonitorByID(string)), this, SLOT(EditMonitorByIndex(string)));
                // 绑定 返回父组消息
                WObject::connect(m_pMonitorview, SIGNAL(BackDeviceParent(string)), this, SLOT(BackGroupDeviceList(string)));
                // 绑定 排序消息
                WObject::connect(m_pMonitorview, SIGNAL(sortMonitorsList(int)), this, SLOT(SortObjects(int)));
                // 绑定 根据组索引进入组消息
                WObject::connect(m_pMonitorview, SIGNAL(enterGroup(string)), this, SLOT(enterGroup(string)));
                // 绑定 根据设备索引进入绑定设备
                WObject::connect(m_pMonitorview, SIGNAL(enterDependDevice(string)), this, SLOT(EnterDeviceByID(string)));
                // 绑定 更新设备状态消息
                WObject::connect(m_pMonitorview, SIGNAL(ChangeDeviceState(string,int)), this, SLOT(ChangeDeviceState(string,int)));
                // 绑定 更新设备状态消息
                WObject::connect(m_pMonitorview, SIGNAL(CopyMonitorSucc(string,int)), this, SLOT(CopyNewMonitorSucc(string,int)));
                // 设置 刷新事件
                m_pMonitorview->setRefreshEvent(m_szGlobalEvent);
                // 设置 主页面
                m_pMonitorview->setMainview(this);
            }			
        }
        if(m_pMonitorview)
        {
            m_pMonitorview->show();                     // 显示监测器视图
            m_pMonitorview->setCurrentTime(curTime);    // 设置当前时间
        }
        break;
    case active_add_group:                              // 添加组
        if(m_pAddGroup == NULL)
        {// 添加组视图未初始化
            // 创建添加组视图
            m_pAddGroup = new SVAddGroup(this, m_pSVUser);
            if(m_pAddGroup)
            {
                // 绑定 添加组成功消息
                WObject::connect(m_pAddGroup, SIGNAL(addGroupName(string,string)), this, SLOT(AddGroupData(string,string)));
                // 绑定 编辑组成功消息
                WObject::connect(m_pAddGroup, SIGNAL(editGroupName(string,string)), this, SLOT(EditGroupData(string,string)));
                // 绑定 取消操作（添加/编辑）消息
                WObject::connect(m_pAddGroup, SIGNAL(backMain()), this, SLOT(showMainView()));
            }			
        }
        if(m_pAddGroup)
        {
            m_pAddGroup->show();                        // 显示 编辑组
        }
        break;
    case active_add_se:                                 // 添加 SE
        if(m_pAddSVSE == NULL)
        {// 添加 SE 视图 未初始化
            // 创建SE 视图
            m_pAddSVSE = new SVAddSE(this);
            if(m_pAddSVSE)
            {
                // 绑定 返回 SE 视图消息
                WObject::connect(m_pAddSVSE, SIGNAL(backSVSEView()), this, SLOT(backSVSEView()));
                // 绑定 编辑 SE 成功消息
                WObject::connect(m_pAddSVSE, SIGNAL(EditSVSESucc(string,string)), this, SLOT(EditSVSESuccByIndex(string,string)));
            }
        }
        if(m_pAddSVSE)
            m_pAddSVSE->show();                         // 显示 编辑SE 视图
        break;
    case active_add_device1st:                          // 添加设备第一步
        if(m_pcurEditIndex)
            m_pcurEditIndex->setText("");
        if(m_pDeviceList == NULL)
        {// 设备模版视图 未初始化
            //创建 设备模版视图
            m_pDeviceList = new SVDeviceList(this);
            if(m_pDeviceList)
            {
                // 绑定 取消添加消息
                WObject::connect(m_pDeviceList, SIGNAL(backPreview()), this, SLOT(showMainView()));
                // 绑定 根据设备模版索引继续添加消息
                WObject::connect(m_pDeviceList, SIGNAL(AddNewDevice(string)), this, SLOT(AddDevice2nd(string)));
            }
        }
        if(m_pDeviceList)
            m_pDeviceList->show();                      // 显示 设备模版视图
        break;
    case active_add_device2nd:                          // 添加设备第二步
    case active_edit_device:                            // 编辑设备
        if(m_pDevice == NULL)
        {// 设备参数视图未初始化
            // 创建设备参数视图
            m_pDevice = new SVDevice(this, m_pSVUser);
            if(m_pDevice)
            {
                // 绑定 返回主页面消息
                WObject::connect(m_pDevice, SIGNAL(backMain()), this, SLOT(showMainView()));
                // 绑定 返回上一页面消息
                WObject::connect(m_pDevice, SIGNAL(backPreview()), this, SLOT(AddNewDevice()));
                // 绑定 添加设备成功消息
                WObject::connect(m_pDevice, SIGNAL(AddDeviceSucc(string,string)), this, SLOT(AddNewDeviceSucc(string,string)));
                // 绑定 编辑设备成功消息
                WObject::connect(m_pDevice, SIGNAL(EditDeviceSucc(string,string)), this, SLOT(EditDeviceSuccByID(string,string)));
                // 绑定 进入新设备消息
                WObject::connect(m_pDevice, SIGNAL(EnterNewDevice(string)), this, SLOT(EnterNewDeviceByID(string)));
            }			
        }
        if(m_pDevice)
            m_pDevice->show();                      // 显示 设备参数视图
        break;
    case active_add_monitor1st:                     // 添加监测器第一步
        if(m_pMonitorList == NULL)
        {// 监测器模版视图未初始化
            // 创建监测器模版视图
            m_pMonitorList = new SVMonitorList(this);
            if(m_pMonitorList)
            {
                // 绑定 取消添加监测器消息
                WObject::connect(m_pMonitorList, SIGNAL(Cancel()), this, SLOT(CancelAddMonitor()));
                // 绑定 根据监测器模版索引继续添加监测器消息
                WObject::connect(m_pMonitorList, SIGNAL(AddMonitorByType(int,string)), this, SLOT(AddNewMonitorByType(int,string)));
            }			
        }
        if(m_pMonitorList)
            m_pMonitorList->show();                 // 显示 监测器模版视图
        break;
    case active_add_monitor2nd:                     // 添加监测器第二步
    case active_edit_monitor:                       // 编辑监测器
        if(m_pMonitor == NULL)
        {// 监测器参数 视图未初始化
            //初始化监测器参数 视图
            m_pMonitor = new SVMonitor(this, m_pSVUser);
            if(m_pMonitor)
            {
                // 绑定 取消操作事件
                WObject::connect(m_pMonitor, SIGNAL(CancelAddMonitor()), this , SLOT(CancelAddMonitor()));
                // 绑定 返回监测器列表视图事件
                WObject::connect(m_pMonitor, SIGNAL(BackPreview()), this, SLOT(BackMonitorList()));
                // 绑定 成功添加监测器事件
                WObject::connect(m_pMonitor, SIGNAL(AddMonitorSucc(string,string)), this, SLOT(AddMonitorSucc(string,string)));
                // 绑定 编辑监测器成功事件
                WObject::connect(m_pMonitor, SIGNAL(EditMonitorSucc(string,string)), this, SLOT(EditMonitorSuccByID(string,string)));
                // 绑定 批量添加监测器事件
                WObject::connect(m_pMonitor, SIGNAL(BatchAddNew()), this, SLOT(BatchAddMonitor()));
            }			
        }
        if(m_pMonitor)
            m_pMonitor->show();                 // 显示 监测器参数 视图
        break;
    case active_batch_add_monitor:              // 批量添加
        if(m_pBatchAdd == NULL)
        {// 批量添加未初始化
            // 初始化批量添加视图
            m_pBatchAdd = new SVBatchAdd(this, m_pSVUser);
            if(m_pBatchAdd)   
            {
                // 绑定 返回主页面消息
                WObject::connect(m_pBatchAdd, SIGNAL(backPreview()), this, SLOT(CancelAddMonitor()));
                // 绑定 添加监测器成功消息
                WObject::connect(m_pBatchAdd, SIGNAL(AddMonitorSucc(string,string)), this, SLOT(AddMonitorSucc(string,string)));
            }
        }
        if(m_pBatchAdd)
        {
            m_pBatchAdd->setDynParamList(m_pMonitor->m_lsDyn);                  // 动态参数    
            m_pBatchAdd->setAdvParamList(m_pMonitor->m_lsAdvParam);             // 高级参数
            m_pBatchAdd->setBaseParamList(m_pMonitor->m_lsBaseParam);           // 基础参数
    
            m_pBatchAdd->setNetworkset(m_pMonitor->m_szNetworkset);             // 监测器是否隶属于网络设备
            m_pBatchAdd->setPoint(m_pMonitor->m_szPoint);                       // 监测器点数
            m_pBatchAdd->setDeviceIndex(m_pMonitor->m_szDeviceIndex);           // 设备索引
            m_pBatchAdd->setMonitorType(m_pMonitor->m_nMonitorID);              // 监测器类型
            m_pBatchAdd->setHostName(m_pMonitor->m_szHostName);                 // 主机名称

            m_pBatchAdd->setErrCondition(m_pMonitor->m_pErrCond);               // 错误条件
            m_pBatchAdd->setWarnCondition(m_pMonitor->m_pWarnCond);             // 警告条件
            m_pBatchAdd->setGoodCondition(m_pMonitor->m_pGoodCond);             // 正常条件

            m_pBatchAdd->addValueList(m_pMonitor->m_szMonitorName);             // 监测器名称
            m_pBatchAdd->show();                                                // 显示 批量添加视图
        }
        break;
    case active_sort_objects:           // 排序
        if(m_pSortForm == NULL)
        {// 排序未初始化
            // 初始化排序视图
            m_pSortForm = new CSVSortList(this, m_pSVUser, m_szIDCUser, m_szIDCPwd);
            if(m_pSortForm)
            {
                // 绑定返回主页面消息
                WObject::connect(m_pSortForm, SIGNAL(backMainView()), this, SLOT(showMainView()));
                // 绑定刷新列表消息
                WObject::connect(m_pSortForm, SIGNAL(RefreshList()), this, SLOT(RefreshCurrentList()));
            }
        }
        if(m_pSortForm)
            m_pSortForm->show();        // 显示排序视图
        break;
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 RefreshCurrentList
// 说明 刷新当前显示视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::RefreshCurrentList()
{
    ShowActivateView(m_nPreviewView);
    // 得到当前时间
    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();
    // 更具当前显示视图刷新
    switch(m_nActiveView)
    {
    case active_se_view:
        if(m_pSVSEView)
        {
            m_pSVSEView->refreshSElist();           // 刷新SE 列表
            m_pSVSEView->setCurrentTime(curTime);   // 设置时间
        }
        break;
    case active_group_view:
        if(m_GeneralList.m_pGroup)
        {
            // 重新进入当前组
            string szGroupID = m_GeneralList.m_pGroup->getGroupIndex();
            m_GeneralList.m_pGroup->EnterGroupByID(szGroupID);
        }  
        // 设置时间
        if(m_GeneralList.m_ptxtTime)
            m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        break;
    case active_monitor_view:
        if(m_pMonitorview)
        {
            // 重新进入当前设备
            m_pMonitorview->enterDevice(m_pMonitorview->GetCurrentID());
            m_pMonitorview->setCurrentTime(curTime);
        }
        break;
    }

    if(m_nActiveView == active_group_view)
    {
        if(m_GeneralList.m_pGroup)
        {
            // 发起排序消息
            MENU_RESPONSE response;	
            response.nOperatCode = SV_SORT;
            response.nNodeType = Tree_GROUP;
            response.strNodeId = m_GeneralList.m_pGroup->getGroupIndex();
            response.bSucess = true;
            response.strName = "";
            response.strErrorMsg = "";
            emit MenuItemResponse(response);
        }
    }  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ReloadCurrentView
// 说明 重新加载当前视图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ReloadCurrentView()
{
    // 得到当前时间
    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();

    PrintDebugString("------* reload Current View *------" + curTime);

    // 是否单机版
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {
        // 得到SE （1）的显示名称
        string szName  ("");
        OBJECT objSE = GetSVSE("1", m_szIDCUser, m_szIDCPwd);
        if(objSE != INVALID_VALUE)
        {
            szName = GetSVSELabel(objSE);
            CloseSVSE(objSE);
        }
        if(!szName.empty())
        {// 如果不为空
            // 发起 SE 名称改变消息
            MENU_RESPONSE response;	
            response.nOperatCode = SV_EDIT;
            response.nNodeType = Tree_SE;
            response.strNodeId = "1";
            response.strParentNodeId = FindParentID("1");
            response.bSucess =true;
            response.strName = szName;
            response.strErrorMsg = "";
            emit MenuItemResponse(response);
        }
    }
    else
    {
        string szName = GetIniFileString("segroup","name","","general.ini");
        if(!szName.empty())
        {
            // 发起SE group 名称改变消息
            MENU_RESPONSE response;	
            response.nOperatCode = SV_EDIT;
            response.nNodeType = Tree_SE;
            response.strNodeId = "-1";
            response.strParentNodeId = "";
            response.bSucess =true;
            response.strName = szName;
            response.strErrorMsg = "";
            emit MenuItemResponse(response);
        }
    }

    switch(m_nActiveView)
    {
    case active_se_view:
        if(m_pSVSEView)
        {
            m_pSVSEView->refreshSElist();               // 刷新 SE 列表
            m_pSVSEView->setCurrentTime(curTime);       // 设置时间
        }
        break;
    case active_group_view:
        if(m_GeneralList.m_pGroup)
        {
            // 重新进入当前组
            string szGroupID = m_GeneralList.m_pGroup->getGroupIndex();
            m_GeneralList.m_pGroup->EnterGroupByID(szGroupID);
        }
        // 设置时间
        if(m_GeneralList.m_ptxtTime)
            m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        break;
    case active_monitor_view:
        if(m_pMonitorview)
        {
            // 重新进入设备
            m_pMonitorview->enterDevice(m_pMonitorview->GetCurrentID());
            // 设置当前时间
            m_pMonitorview->setCurrentTime(curTime);
        }
        break;
    }

    if(!m_szActiveOptIndex.empty())
    {// 如果当前操作索引不为空
        if(m_nActiveOptType == Tree_DEVICE)
        {// 操作类型是设备
            // 得到设备的简单状态
            int nState = getDeviceSimpleState(m_szActiveOptIndex, m_szIDCUser, m_szIDCPwd);
            // 更新设备的状态
            ChangeDeviceState(m_szActiveOptIndex, nState);
        }
        else if(m_nActiveOptType == Tree_GROUP)
        {// 操作类型是组
            // 组是否被禁止/更新组的状态
            if(isGroupDisable(m_szActiveOptIndex, m_szIDCUser, m_szIDCPwd) != 0)
                ChangeGroupState(m_szActiveOptIndex, dyn_disable);
            else
                ChangeGroupState(m_szActiveOptIndex, dyn_normal);
        }
    }
    
    // 重置 当前操作索引和操作类型
    m_nActiveOptType = -1;
    m_szActiveOptIndex = "";

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 isCurEditParentDel
// 说明 判断被删除的索引值是否包含当前正被修改索引
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVGroupview::isCurEditParentDel(string szIndex, string szCurrentID)
{
    if(szCurrentID.empty())
    {// 当前索引不为空
        if(m_szEditIndex == szIndex)                    // 两者相等
            return true;
        // 判断是否包含
        string szParent = FindParentID(m_szEditIndex);
        while(!szParent.empty())
        {
            if(szParent == szIndex)
                return true;
            szParent = FindParentID(szParent);
            if(IsSVSEID(szParent))
                break;
        }
        if(m_szEditIndex == szParent)
            return true;
    }
    else
    {
        if(szCurrentID == szIndex)
            return true;
        string szParent = FindParentID(szCurrentID);
        while(!szParent.empty())
        {
            if(szParent == szIndex)
                return true;
            szParent = FindParentID(szParent);
            if(IsSVSEID(szParent))
                break;
        }
        if(szCurrentID == szParent)
            return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 deleteObject
// 说明 树上删除对象后视图的处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::deleteObject(string szIndex)
{
    int nMonitorCount = 0;
    switch(m_nActiveView)
    {
    case active_se_view:
        if(m_pSVSEView)
        {
            m_pSVSEView->refreshSElist();
        }
        break;
    case active_group_view:                     // 组视图
        if(m_GeneralList.m_pGroup)
        {
            if(isCurEditParentDel(szIndex, m_GeneralList.m_pGroup->getGroupIndex()))
            {
                string szParent = FindParentID(szIndex);
                enterGroup(szParent);
            }
            else
            {
                ReloadCurrentView();                    // 重新加载当前组
            }
        }
        break;
    case active_monitor_view:                   // 监测器视图
        if(m_pMonitorview)
        {
            if(m_pMonitorview->isParentEdit(szIndex))
            {// 当前设备包含在此索引中
                // 得到当前ID 的父索引
                string szParentID = FindParentID(szIndex);
                // 发起返回到父索引消息
                emit m_pMonitorview->BackDeviceParent(szParentID);
            }
        }
        break;
    case active_add_group:                      // 添加组
        if(isCurEditParentDel(szIndex) || isCurEditParentDel(szIndex, m_pAddGroup->GetParentIndex()))
        {// 如果是当前组被删除/当前组父节点被删除
            m_szEditIndex = "";
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_device1st:                  // 添加设备第一步
        if(isCurEditParentDel(szIndex, m_pDeviceList->getParentID()))
        {// 父节点被删除
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_device2nd:                  // 添加设备第二步
        if(isCurEditParentDel(szIndex, m_pDevice->getParentIndex()))
        {// 父节点被删除
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_edit_device:                    // 编辑设备
        if(isCurEditParentDel(szIndex))
        {// 父节点被删除
            m_szEditIndex = "";
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_monitor1st:                 // 添加监测器第一步
        if(isCurEditParentDel(szIndex, m_pMonitorList->getParentIndex()))
        {// 当前设备父节点被删除
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_monitor2nd:                 // 添加监测器第二步
        if(isCurEditParentDel(szIndex, m_pMonitor->getParentID()))
        {// 当前设备父节点被删除
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_edit_monitor:                   // 编辑监测
        if(isCurEditParentDel(szIndex, m_pMonitor->getCurrentEditID()))
        {// 当前监测器父节点被删除
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 BatchAddMonitor
// 说明 批量添加消息处理函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::BatchAddMonitor()
{
    ShowActivateView(active_batch_add_monitor);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createHideButton
// 说明 创建隐藏按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::createHideButton()
{
    WPushButton *pBtnHide = new WPushButton("hide button", this);//(WContainerWidget*)elementAt(nRow,0));
    if(pBtnHide)
    {
        // onclick
        WObject::connect(pBtnHide, SIGNAL(clicked()), "showbar();", this, SLOT(ReloadCurrentView()), 
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        pBtnHide->hide();
        m_szGlobalEvent = pBtnHide->getEncodeCmd("xclicked()"); 
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 SortObjects
// 说明 排序处理
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::SortObjects(int nType)
{  
    string szSortID("");
    // 根据类型不同得到排序的索引
    switch(nType)
    {
    case Tree_MONITOR:
        if(m_pMonitorview)
            szSortID = m_pMonitorview->GetCurrentID();
        break;
    case Tree_GROUP:
    case Tree_DEVICE:
        if(m_GeneralList.m_pGroup)
            szSortID = m_GeneralList.m_pGroup->getGroupIndex();
        break;
    }

    ShowActivateView(active_sort_objects);      // 显示排序视图
    // 排序
    if(!szSortID.empty() && m_pSortForm)
        m_pSortForm->EnumObject(szSortID, nType);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enterGroup
// 说明 根据组索引进入组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::enterGroup(string szGroupID)
{
    ShowActivateView(active_group_view);
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->EnterGroupByID(szGroupID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enterGroupByID
// 说明 根据索引进入组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::enterGroupByID(const std::string szGroupID)
{
    string szGroupIndex(szGroupID);
    ShowActivateView(active_group_view);
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->EnterGroupByID(szGroupIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ChangeDeviceState
// 说明 更新设备状态
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ChangeDeviceState(string szDeviceID, int nState)
{
    // 发起设备状态改变事件
    MENU_RESPONSE response;	
    response.nOperatCode = nState;
    response.nNodeType = Tree_DEVICE;
    response.strNodeId = szDeviceID;
    response.bSucess = true;
    response.strName = "";
    response.strErrorMsg = "";
    emit MenuItemResponse(response);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ChangeGroupState
// 说明 更新组状态
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ChangeGroupState(string szGroupID, int nState)
{
    // 发起组状态改变消息
    MENU_RESPONSE response;	
    response.nOperatCode = nState;
    response.nNodeType = Tree_GROUP;
    response.strNodeId = szGroupID;
    response.bSucess = true;
    response.strName = "";
    response.strErrorMsg = "";
    emit MenuItemResponse(response);
}

void SVGroupview::AddOperaterLog(int &nOperateType, int &nObjectType, string &szOperateMsg)
{
    string szOperateType(""), szObjectType("");

    //memset(m_szLogData, 0, sizeof(m_szLogData));
    //
    ////DumpLog("treeview.log", m_szLogData, sizeof(m_szLogData));

    svutil::TTime curTime = svutil::TTime::GetCurrentTimeEx();


    switch(nOperateType)
    {
    case SV_ADD:
        szOperateType = SVResString::getResString("IDS_Add_Title");
        break;
    case SV_EDIT:
        szOperateType = SVResString::getResString("IDS_Edit");
        break;
    case SV_DELETE:
        szOperateType = SVResString::getResString("IDS_Delete");
        break;
    }

    switch(nObjectType)
    {
    case Tree_SE:
        szObjectType = SVResString::getResString("IDS_SE");
        break;
    case Tree_GROUP:
        szObjectType = SVResString::getResString("IDS_Group");
        break;
    case Tree_DEVICE:
        szObjectType = SVResString::getResString("IDS_Device");
        break;
    case Tree_MONITOR:
        szObjectType = SVResString::getResString("IDS_Monitor_Title");
        break;
    }

    //PrintDebugString("Operate Type Is : " + szOperateType + " && Object Type is " + szObjectType.c_str()
    //    + " && Operate Message is : " + szOperateMsg + " && user id is : " + m_pSVUser->getUserID());

    InsertTable(SV_USER_OPERATE_LOG_TABLE,  803);

    if(m_pSVUser)
        m_pOperateLog.InsertOperateRecord(SV_USER_OPERATE_LOG_TABLE, m_pSVUser->getUserID(), 
            curTime.Format(), szOperateType, szObjectType, szOperateMsg);
    //int nLen = sizeof(m_szLogData) - 1;

    //LP_RECORD_HEAD pRecordHead = reinterpret_cast<LP_RECORD_HEAD>(m_szLogData);

    //char *pPos = m_szLogData + sizeof(SV_DATABASE_TABLE_RECORD_HEAD);
    //nLen -= sizeof(SV_DATABASE_TABLE_RECORD_HEAD);
    //
    //if((pPos = buildbuf(m_szUserShowName, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + m_szUserShowName);
    //    return ;
    //}

    //if((pPos = buildbuf(curTime.Format(), pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + curTime.Format());
    //    return ;
    //}

    //if((pPos = buildbuf(szOperateType, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + szOperateType);
    //    return ;
    //}

    //if((pPos = buildbuf(szObjectType, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + szObjectType);
    //    return ;
    //}

    //if((pPos = buildbuf(szOperateMsg, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + szOperateMsg);
    //    return ;
    //}

    //pRecordHead->m_nState = 1;
    //pRecordHead->m_tCreatetime = curTime;
    //pRecordHead->m_nDataLen = static_cast<int>(pPos - m_szLogData) - sizeof(SV_DATABASE_TABLE_RECORD_HEAD);

    //strcpy(pPos , "DynString");
    //nLen = static_cast<int>(pPos - m_szLogData) + static_cast<int>(strlen(pPos)) + 1;
    //DumpLog("treeview.log", m_szLogData, nLen);


    //if(!AppendRecord(SV_USER_OPERATE_LOG_TABLE, m_szLogData, nLen))
    //{
    //    string szMsg = "Append record into table(";
    //    szMsg += SV_USER_OPERATE_LOG_TABLE;
    //    szMsg += ") failed";
    //    PrintDebugString(szMsg);
    //}

    //memset(m_szLogData, 0, sizeof(m_szLogData));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file

//可能的余留问题
//1、单机版能返回SVSEList界面， 但不让添加SVSE
//2、多机版能返回SVSEList界面， 让添加SVSE， 在点击TreeGroup节点时跳添加Se菜单， 所有和SVSE相关的增删修启用。
//3、返回界面方面可能会有问题。。。。
//4、测试方案：