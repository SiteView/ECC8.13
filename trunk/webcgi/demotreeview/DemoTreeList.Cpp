/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
#include <boost/lexical_cast.hpp>
#include <fcgi_stdio.h>
//#include <cgi-util.h>

#include <WApplication>
#include <WText>
#include <WImage>
#include <WPushButton>
#include <WTable>
#include <WTableCell>
#include <WContainerWidget>
#include <WScrollArea>
#include <WLineEdit>
#include "websession.h"
#include "WLength"
#include "WComboBox"

#include <stdlib.h>
#include <stdio.h>


#include <iostream>
#include <Algorithm>

#include "DemoTreeList.h"
#include "WTreeNode.h"
#include "WStateIcon.h"
#include "popmenu.h"

#include "../group/basefunc.h"
#include "../group/resstring.h"
#include "../group/groupview.h"

#include "../../kennel/svdb/libutil/time.h"
#include "../../kennel/svdb/svapi/svapi.h"

static  char szFromIP[4096] = {0};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddTaskList(WComboBox * pTask = NULL)
{
    if(pTask)
    {
        list<string> lsTaskName;
        list<string>::iterator lsItem;

        if(GetAllTaskName(lsTaskName))
        {
            for(lsItem = lsTaskName.begin(); lsItem != lsTaskName.end(); lsItem ++)
            {
                string szName = (*lsItem);
                pTask->addItem(szName);
            }
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const char * szMsg)
{
#ifdef WIN32
    OutputDebugString("treeview : ");
    OutputDebugString(szMsg);
    OutputDebugString(" ---------* from ");
    OutputDebugString(szFromIP);
    OutputDebugString("*---------");
    OutputDebugString("\n");
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const string & szMsg)
{
    PrintDebugString(szMsg.c_str());
}

DemoTreeList::DemoTreeList(WContainerWidget *parent)
: WContainerWidget(parent)
{	
    m_bConfirm = false;
    m_bFirstLoad = true;
    treeroot = NULL;

    //loadString();
    CSVPopMenu popmenu;
    new WText(popmenu.ShowMenu(), this);

    m_pGroupview = NULL;
    m_pSVUser = NULL;
    m_szUserID = GetWebUserID();
    if(!m_szUserID.empty())
        m_pSVUser = new CUser(m_szUserID);

    m_szIDCUser = "default";
    m_szIDCPwd = "localhost";
    m_szSrcDeviceID = "";

    new WText("<SCRIPT language='JavaScript' src='/menu.js'></SCRIPT>", this);

    int nSize = 4095;
	GetEnvironmentVariable( "REMOTE_ADDR", szFromIP, nSize);

    WTable * wholetable = new WTable(this);
    if(wholetable)
    {
        wholetable->setStyleClass("t5");
        WTable * MenuWholetable = new WTable(wholetable->elementAt(0, 0));
        wholetable->elementAt(0, 0)->resize(WLength(200), WLength(100,WLength::Percentage));
        if(MenuWholetable)
        {
            MenuWholetable->setStyleClass("t6");
            WText *pReload = new WText(SVResString::getResString("IDS_Refresh_View"), MenuWholetable->elementAt(0, 0));
            if(pReload)
            {
                sprintf(pReload->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                "this.style.textDecoration=\"underline\";this.style.backgroundColor=\"#CCCCFF\";' " \
                "onmouseout='this.style.textDecoration=\"none\";this.style.backgroundColor=\"#CCCCCC\";'");
                WObject::connect(pReload, SIGNAL(clicked()), "showbar()", this, SLOT(InPhaseView()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            }

            MenuWholetable->elementAt(0,0)->setStyleClass("treerefresh");
            MenuWholetable->elementAt(0,0)->setContentAlignment(AlignRight);

            m_pMenutable = NULL;
            WTable * pMenu = new WTable((WTableCell*)MenuWholetable->elementAt(1,0));
            if(pMenu)
            {
                MenuWholetable->elementAt(1, 0)->setStyleClass("t6");
                pMenu->setStyleClass("viewtreebody");
                WScrollArea * table = new WScrollArea(MenuWholetable->elementAt(1,0));
                if(table)
                {
                    table->setWidget(pMenu);
                    table->setStyleClass("treebackgroup");
                    m_szObjID = table->formName();
                }
                m_pMenutable = new WTable(pMenu->elementAt(0, 0));
                pMenu->elementAt(0, 0)->setContentAlignment(AlignTop);
            }

            WImage * spaceImage = new WImage("../icons/space.gif", (WContainerWidget *)wholetable->elementAt(0, 1));
            wholetable->elementAt(0, 1)->setStyleClass("menuresize");
            strcpy(wholetable->elementAt(0, 1)->contextmenu_, 
                "onmousedown='_canResize=true;this.setCapture(true)' onmouseup='this.releaseCapture();_canResize=false;'");
            WTable *rightTable = new WTable((WContainerWidget *)wholetable->elementAt(0, 2));
            if(rightTable)
            {
                rightTable->setStyleClass("t6");
                rightTable->elementAt(0, 0)->setContentAlignment(AlignTop);
                rightTable->elementAt(0, 0)->setStyleClass("t6");

                m_pGroupview = new SVGroupview((WContainerWidget *)rightTable->elementAt(0, 0), m_pSVUser, m_szIDCUser, m_szIDCPwd);
                if(m_pGroupview)
                {
                    WObject::connect(this, SIGNAL(MenuItemRequest(MENU_REQUEST)), m_pGroupview, SLOT(MenuItemRequestProc(MENU_REQUEST)));
                    WObject::connect(m_pGroupview, SIGNAL(MenuItemResponse(MENU_RESPONSE)), this, SLOT(MenuItemResponseProc(MENU_RESPONSE)));
                    WObject::connect(m_pGroupview, SIGNAL(ChangeSelNode(string)), this, SLOT(changeSelNode(string)));
					WObject::connect(m_pGroupview, SIGNAL(TranslateSuccessful()), this, SLOT(ExChangeRefresh()));  
                    WScrollArea * scrollarea = new WScrollArea(rightTable->elementAt(0,0));
                    scrollarea->setStyleClass("t6");
                    scrollarea->setWidget(m_pGroupview);
                }
            }

            AddJsParam("tableName", wholetable->formName());

            //右键菜单相关逻辑
            WPushButton * pRunMenuButton_ = new WPushButton("runMenu", MenuWholetable->elementAt(1, 0));
            if(pRunMenuButton_)
            {
                connect(pRunMenuButton_, SIGNAL(clicked()), this, SLOT(RunMenu()));
                pRunMenuButton_->hide();
                AddJsParam("runMenuButton", pRunMenuButton_->getEncodeCmd("xclicked()"));
            }

            m_pCurIdEdit_ = new WLineEdit("", MenuWholetable->elementAt(1, 0));
            if(m_pCurIdEdit_)
            {
                m_pCurIdEdit_->hide();
                AddJsParam("curId", m_pCurIdEdit_->formName());
            }

            m_pCurTypeEdit_ = new WLineEdit("", MenuWholetable->elementAt(1, 0));
            if(m_pCurTypeEdit_)
            {
                m_pCurTypeEdit_->hide();
                AddJsParam("curType", m_pCurTypeEdit_->formName());
            }

            m_pCurOprCodeEdit_ = new WLineEdit("", MenuWholetable->elementAt(1, 0));
            if(m_pCurOprCodeEdit_)
            {
                m_pCurOprCodeEdit_->hide();
                AddJsParam("curOprCode", m_pCurOprCodeEdit_ ->formName());
            }

            //焦点相关响应逻辑
            WPushButton * pSetNodeFocusButton_ =new WPushButton("setNodeFocus", MenuWholetable->elementAt(1, 0));
            if(pSetNodeFocusButton_)
            {
                connect(pSetNodeFocusButton_, SIGNAL(clicked()),	"showbar();", this, SLOT(SelNode()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                pSetNodeFocusButton_->hide();
                AddJsParam("setNodeFocusButton", pSetNodeFocusButton_->getEncodeCmd("xclicked()"));
            }

            m_pCurFocusEdit_ = new WLineEdit("", MenuWholetable->elementAt(1, 0));
            if(m_pCurFocusEdit_)
            {
                m_pCurFocusEdit_->hide();
                AddJsParam("curFocusId", m_pCurFocusEdit_ ->formName());
            }

            m_pDelConform = new WPushButton("hide del button", MenuWholetable->elementAt(1,0));
            if(m_pDelConform)
            {        
                m_pDelConform->hide();
                WObject::connect(m_pDelConform, SIGNAL(clicked()), this, SLOT(delConfirm()));
            }

            //WLineEdit *pcurEventX_ = new WLineEdit("", MenuWholetable->elementAt(1, 0));
            //if(pcurEventX_)
            //{
            //    pcurEventX_->hide();
            //    AddJsParam("curEventX", pcurEventX_->formName());
            //}

            //WLineEdit *pcurEventY_ = new WLineEdit("", MenuWholetable->elementAt(1, 0));
            //if(pcurEventY_)
            //{
            //    pcurEventY_->hide();
            //    AddJsParam("curEventY", pcurEventX_->formName());
            //}
        }
    }


}

DemoTreeList::~DemoTreeList()
{
    if(m_pSVUser)
        delete m_pSVUser;

    if(treeroot)
        delete treeroot;
}

void DemoTreeList::delConfirm()
{
    m_bConfirm = true;
    RunMenu();
    m_bConfirm = false;
}

void DemoTreeList::refresh()
{
    if(!m_bFirstLoad)
    {
        string szUserID = GetWebUserID();
        if(szUserID != m_szUserID)
        {
            m_szUserID = szUserID;
            //if(groupview)
            //    groupview->resetUserID(m_szUserID); 
            if(m_pSVUser)
                m_pSVUser->setUserID(m_szUserID);
            InitTree(); 
            WTreeNode *node = GetNodeById("1");
            if(node != NULL)
            {
                node->SelItem();

                //提交点击树项事件
                MENU_REQUEST request;

                request.nOperatCode = SV_CLICK;
                request.nNodeType = (TreeNodeType)node->nTreeType;		
                request.strNodeId = node->strId;

                emit MenuItemRequest(request);
            }
        }
        else
        {
            for(unsigned i = 0; i < nodeVector.size(); ++i)
            {
                if(nodeVector[i]->nTreeType == Tree_DEVICE)
                {
                    int nState = getDeviceSimpleState(nodeVector[i]->strId, m_szIDCUser, m_szIDCPwd);
                    nodeVector[i]->ChangeState(nState);
                }
            }
            if(m_pGroupview)
                m_pGroupview->ReloadCurrentView();
        }
        m_szQueryID = "";
        char szQuery[4096]={0};
        int nSize = 4095;
        GetEnvironmentVariable( "QUERY_STRING", szQuery,nSize);
        char *pPos = strchr(szQuery, '=');
        if(pPos)
        {
            pPos ++;
            m_szQueryID = pPos; 
            WTreeNode *node = GetNodeById(m_szQueryID);
            if(node != NULL)
            {
                node->SelItem();

                //提交点击树项事件
                MENU_REQUEST request;

                request.nOperatCode = SV_CLICK;
                request.nNodeType = (TreeNodeType)node->nTreeType;		
                request.strNodeId = node->strId;

                emit MenuItemRequest(request);
            }
        }
    }
    else
    {
        m_bFirstLoad = false;
    }
}

//
WTreeNode *DemoTreeList::makeTreeMap(string name, string id, int nType, WTable *parent, string strIcon1, string strIcon2)
{
    WStateIcon *labelIcon = new WStateIcon(strIcon1, strIcon2, false);

    //放树控件到一个表格中
    //string szMenu = CreateMenuByID(id , nType);
    WTreeNode *node = new WTreeNode(this, name, id, nType, -1, WText::PlainFormatting, labelIcon, 0, NULL, m_szIDCUser, m_szIDCPwd);
    parent->elementAt(0,0)->addWidget(node);
    nodeVector.push_back(node);
    return node;
}

//生成树节点
WTreeNode *DemoTreeList::makeTreeFile(string name, string xid, int nType, WTreeNode *parent, string strIcon1, string strIcon2)
{
    WStateIcon *labelIcon = NULL;
    
    //string szMenu = CreateMenuByID(xid , nType);
    int nState = -1;
    if(nType == Tree_DEVICE)
    {
        labelIcon = new WStateIcon(strIcon1, strIcon2, false);
        nState = getDeviceSimpleState(xid, m_szIDCUser, m_szIDCPwd);
    }
    else
        labelIcon = new WStateIcon(strIcon1, strIcon2, false);

    WTreeNode *node = new WTreeNode(this, name, xid, nType, nState, WText::XHMTLFormatting, labelIcon, 0, NULL, m_szIDCUser, m_szIDCPwd);
    //node->m_pParentTreeView=(DemoTreeList *)this;
    if (parent)
    {
        parent->addChildNode(node, nType);
        nodeVector.push_back(node);
    }

    return node;
}


//左键点击树时清空以前的焦点项
void DemoTreeList::SelNode()
{
    for(unsigned i = 0; i < nodeVector.size(); ++i)
    {
        nodeVector[i]->unSelItem();
    }

    WTreeNode *node = GetNodeById(m_pCurFocusEdit_->text());
    if(node != NULL)
    {
        node->SelItem();

        //提交点击树项事件
        MENU_REQUEST request;

        request.nOperatCode = SV_CLICK;
        request.nNodeType = (TreeNodeType)node->nTreeType;		
        request.strNodeId = node->strId;

        emit MenuItemRequest(request);
    }
}

//根据id获取树节点
WTreeNode *DemoTreeList::GetNodeById(std::string strId)
{
    for(unsigned i = 0; i < nodeVector.size(); ++i)
    {
        if(nodeVector[i]->strId == strId)
        {
            return nodeVector[i];
        }
    }

    return NULL;
}

//客户端菜单的响应函数
void DemoTreeList::RunMenu()
{
    //跳出等待时间图标．．．

    //发送菜单项执行信息给组等模块
    MENU_REQUEST request;

    int nOprcode = 0;

    sscanf(m_pCurOprCodeEdit_->text().c_str(), "%d", &nOprcode);
    request.nOperatCode = (SV_Tree_OperateCode)nOprcode;

    int nType = 0;
    sscanf(m_pCurTypeEdit_->text().c_str(), "%d", &nType);
    request.nNodeType = (TreeNodeType)nType;

    request.strNodeId = m_pCurIdEdit_->text().c_str();
    if(request.nOperatCode == SV_DELETE)
    {
        if(!m_bConfirm)
        {
            if(m_pDelConform)
            {
                string szMsg = m_pDelConform->getEncodeCmd("xclicked()");
                if(!szMsg.empty())
                {
                    switch (request.nNodeType)
                    {
                    case Tree_SE:
                        if(request.strNodeId == "1")
                            szMsg =  "alert('" + SVResString::getResString("IDS_Base_SE_Not_Delete") + "');";
                        else
                            szMsg =  "_Delclick('" + SVResString::getResString("IDS_Delete_SE_Confirm") + "','" +
                                SVResString::getResString("IDS_ConfirmCancel") + "','" + 
                                SVResString::getResString("IDS_Affirm") + "','" + szMsg + "');";
                        break;
                    case Tree_GROUP:                
                        szMsg = "_Delclick('" + SVResString::getResString("IDS_Delete_Sel_Group_Confirm") + "','" +
                            SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szMsg + "');";
                        break;
                    case Tree_DEVICE:
                        szMsg = "_Delclick('" + SVResString::getResString("IDS_Delete_Sel_Device_Confirm") + "','" +
                            SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" +  szMsg + "');";
                        break;
                    default:
                        szMsg = "";
                        break;
                    }
                    if(!szMsg.empty())
                    {
                        WebSession::js_af_up = szMsg;
                        return;
                    }
                }
            }            
        }

        //删除数据及树节点
        if(request.nNodeType == Tree_SE)
        {
            if(request.strNodeId != "1")
                DelSVSE(request.strNodeId);
            else
                WebSession::js_af_up = "alert('" + SVResString::getResString("IDS_Base_SE_Not_Delete") + "');";
        }
        if(request.nNodeType == Tree_GROUP)
        {
            DelGroup(request.strNodeId);
        }
        else if(request.nNodeType == Tree_DEVICE)
        {
            DelDevice(request.strNodeId);
        }

        WTreeNode * pNode = GetNodeById(request.strNodeId);
        if(pNode)
        {
            request.strParentNodeId = pNode->getText();
            DelTreeNode(pNode);
        }
    }
    if(request.nOperatCode == SV_COPY)
    {
        m_szSrcDeviceID = request.strNodeId;
        WebSession::js_af_up = "hiddenbar();";
    }
    else if(request.nOperatCode == SV_PAST)
    {
        if(!m_szSrcDeviceID.empty())
        {
            if(IsCanPaste())
            {
                string szNewDeviceID = copyDevice(request.strNodeId);
                if(!szNewDeviceID.empty())
                {
                    request.nOperatCode = SV_REFRESH;                
                    request.nNodeType = Tree_DEVICE;
                    request.strParentNodeId = request.strNodeId;
                    request.strNodeId = szNewDeviceID;
                    emit MenuItemRequest(request);
                }
                else
                    WebSession::js_af_up = "hiddenbar();";
            }
            else
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
        }
        else
            WebSession::js_af_up = "hiddenbar();";
    }
    else
        emit MenuItemRequest(request);
}

bool DemoTreeList::SrcIsNetwork(int &nMonitorCount)
{
    OBJECT objDevice = GetEntity(m_szSrcDeviceID,  m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        string szNetwork("");
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
            FindNodeValue(mainnode, "sv_network", szNetwork);

        list<string> lsMonitorID;
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {
            if(szNetwork == "true")
                nMonitorCount = static_cast<int>(lsMonitorID.size());
            else
            {
                list<string>::iterator lsItem;
                string szPoint("");
                for(lsItem = lsMonitorID.begin(); lsItem != lsMonitorID.end(); lsItem++)
                {
                    OBJECT objMonitor = GetMonitor((*lsItem), m_szIDCUser, m_szIDCPwd);
                    if(objMonitor != INVALID_VALUE)
                    {
                        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
                        if(node != INVALID_VALUE)
                        {
                            FindNodeValue(node, "sv_intpos", szPoint);
                            if(szPoint.empty())
                                nMonitorCount ++;
                            else
                                nMonitorCount += atoi(szPoint.c_str());
                        }
                        else
                            nMonitorCount ++;
                        CloseMonitor(objMonitor);
                    }
                    else
                        nMonitorCount ++;
                }
            }
        }

        CloseEntity(objDevice);

        if(szNetwork == "true")
            return true;
    }
    return false;
}

bool DemoTreeList::IsCanPaste()
{
    int nSrcMonitorCount = 0;
    if(SrcIsNetwork(nSrcMonitorCount))
    {
        int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd);
        if(nSrcMonitorCount % 30 == 0 && nSrcMonitorCount > 0)
            nNetworkCount = nNetworkCount + (nSrcMonitorCount / 30);
        else
            nNetworkCount = nNetworkCount + (nSrcMonitorCount / 30) + 1;

        return checkNetworkPoint(nNetworkCount);
    }
    else
    {
        int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);
        nMonitorCount += nSrcMonitorCount;
        return checkMonitorsPoint(nMonitorCount);
    }
    return false;
}

string DemoTreeList::copyDevice(string &szGroupID)
{
    string szNewDeviceID = EntityCopy(m_szSrcDeviceID, szGroupID, m_szIDCUser, m_szIDCPwd);
    if(!szNewDeviceID.empty())
    {
        WTreeNode *pNode = GetNodeById(m_szSrcDeviceID); 
        string szName("");
        if(pNode)
        {
            szName = pNode->getText();
            pNode = GetNodeById(szGroupID);
            if(pNode)
                makeTreeFile(szName, szNewDeviceID, Tree_DEVICE, pNode, "../icons/device.gif", "../icons/device.gif"); 
            if(m_pGroupview)
            {
                string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device") +
                    "(Index)" + szNewDeviceID + "---" + SVResString::getResString("IDS_Name") + ":" + szName + 
                    "---parent id is " + szGroupID + "---" + SVResString::getResString("IDS_Name") +
                    ":" + getGroupNameByID(szGroupID, m_szIDCUser, m_szIDCPwd);

                int nOperate = SV_ADD, nType = Tree_DEVICE;
                m_pGroupview->AddOperaterLog(nOperate, nType, szMsg);
            }
        }
        createAllTableOfDevice(szNewDeviceID, m_szIDCUser, m_szIDCPwd);
    }
    return szNewDeviceID;
}

//菜单执行后的响应函数
void DemoTreeList::MenuItemResponseProc(MENU_RESPONSE response)
{
    if(response.bSucess)
    {
        WTreeNode *node = NULL;
        string szName("");
        OBJECT obj = NULL;
        MAPNODE mapnode = NULL;
        switch(response.nOperatCode)
        {
        case SV_ADD:
            //加相应节点到树
            node = GetNodeById(response.strParentNodeId);
            if(node != NULL)
            {
                WTreeNode * node1 = NULL;
                switch(response.nNodeType)
                {
                case Tree_SE:
                    node1 = makeTreeFile(response.strName, response.strNodeId, Tree_SE, node, "../icons/home.gif", "../icons/home.gif");
                    if(node1)   
                        node1->parentNode_->expand();
                    break;							
                case Tree_GROUP:
                    node1 = makeTreeFile(response.strName, response.strNodeId, Tree_GROUP, node, "../icons/group.gif", "../icons/group.gif");
                    //展开
                    if(node1)   
                        node1->parentNode_->expand();
                    break;
                case Tree_DEVICE:
                    node1 = makeTreeFile(response.strName, response.strNodeId, Tree_DEVICE, node, "../icons/device.gif", "../icons/device.gif");
                    break;
                }                
            }
            break;
        case SV_EDIT:
            //加相应节点到树				
            node = GetNodeById(response.strNodeId);
            if(node != NULL)
                node->ChangeText(response.strName);
            break;
        case SV_DELETE:
            //删除节点
            node = GetNodeById(response.strNodeId);
            if(node != NULL)
            {
                DelTreeNode(node);
                delete node;
            }
            break;
        case SV_SORT:
            node = GetNodeById(response.strNodeId);
            if(node != NULL)
            {
                while(node->childNodes_.size() > 0)
                {
                    WTreeNode* pTmpNode = node->childNodes_[node->childNodes_.size() - 1];
                    if(pTmpNode != NULL)
                    {
                        PrintDebugString("delete node's index is : " + pTmpNode->strId);
                        DelTreeNode(pTmpNode, true);
                        delete pTmpNode;
                    }
                }
                node->childNodes_.clear();
                EnumGroup(response.strNodeId, node);
            }
            break;
        case    dyn_no_data:
        case    dyn_normal:
        case    dyn_warnning:
        case    dyn_error:
        case    dyn_disable:
        case    dyn_bad:
            node = GetNodeById(response.strNodeId);
            if(node != NULL)
            {
                if(node->nTreeType == Tree_DEVICE)
                    node->ChangeState(response.nOperatCode);
                if(response.nNodeType == Tree_GROUP)
                {
                    for(int i = 0; i < static_cast<int>(node->childNodes_.size()); i++)
                    {
                        if(((WTreeNode*)(node->childNodes_[i]))->nTreeType == Tree_DEVICE)
                            ((WTreeNode*)(node->childNodes_[i]))->ChangeState(response.nOperatCode);
                        else if(((WTreeNode*)(node->childNodes_[i]))->nTreeType == Tree_GROUP ||
                            ((WTreeNode*)(node->childNodes_[i]))->nTreeType == Tree_SE)
                            UpdateSubGroupState(node->childNodes_[i], response.nOperatCode);
                    }
                }
            }
            break;
        }
    }
}


void DemoTreeList::UpdateSubGroupState(WTreeNode *pNode, int nState)
{
    for(int i = 0; i < static_cast<int>(pNode->childNodes_.size()); i++)
    {
        if(((WTreeNode*)(pNode->childNodes_[i]))->nTreeType == Tree_DEVICE)
            ((WTreeNode*)(pNode->childNodes_[i]))->ChangeState(nState);    
        else if(((WTreeNode*)(pNode->childNodes_[i]))->nTreeType == Tree_GROUP ||
            ((WTreeNode*)(pNode->childNodes_[i]))->nTreeType == Tree_SE)
            UpdateSubGroupState(pNode->childNodes_[i], nState);
    }
}

//void DemoTreeList::changeFoucs(WTreeNode *pNode)
//{
//    MENU_REQUEST request;
//
//    request.nOperatCode = SV_COLLAPSE;
//    request.nNodeType = (TreeNodeType)pNode->nTreeType;
//    request.strNodeId = pNode->strId;
//
//    emit MenuItemRequest(request);
//}

//递归有问题， 改为在DelGroup等中删除。
void DemoTreeList::DelTreeNode(WTreeNode* pNode, bool bSort)
{
    WTreeNode* pTmpNode = NULL;
    if(pNode != NULL)
    {
        if(!pNode->HasChild())
        {
            WTreeNode * pParentNode = pNode->parentNode_;
            if(pParentNode != NULL)
            {                
                pParentNode->removeChildNode(pNode);
                if(IsSVSEID(pParentNode->strId) && !(pParentNode->HasChild()) && !bSort)
                {
                    WTreeNode *pNoChild = new WTreeNode(this, m_szNoChild, "-2", Tree_NOCHILD, -1, WText::XHMTLFormatting, NULL, NULL, NULL, m_szIDCUser, m_szIDCPwd);
                    //pNoChild->m_pParentTreeView=(DemoTreeList *)this;
                    pParentNode->addChildNode(pNoChild, Tree_NOCHILD);
                }			
            }
            nodeVector.erase(std::find(nodeVector.begin(), nodeVector.end(), pNode));
        }
        else
        {
            while(pNode->childNodes_.size() > 0)
            {
                //vector中元素已经删除带来错误..............
                pTmpNode = pNode->childNodes_[pNode->childNodes_.size() - 1];
                if(pTmpNode != NULL)
                {
                    DelTreeNode(pTmpNode, bSort);
                    delete pTmpNode;
                }
            }
            if(pNode != NULL)
            {
                WTreeNode * pParentNode = pNode->parentNode_;
                if(pParentNode != NULL)
                {                
                    pParentNode->removeChildNode(pNode);
                    if(IsSVSEID(pParentNode->strId) && !(pParentNode->HasChild()) && !bSort)
                    {
                        WTreeNode *pNoChild = new WTreeNode(this, m_szNoChild, "-2", Tree_NOCHILD, -1, WText::XHMTLFormatting, NULL, NULL, NULL, m_szIDCUser, m_szIDCPwd);
                        //pNoChild->m_pParentTreeView=(DemoTreeList *)this;
                        pParentNode->addChildNode(pNoChild, Tree_NOCHILD);
                    }
                }
                nodeVector.erase(std::find(nodeVector.begin(), nodeVector.end(), pNode));
            }
        }
    }
}

void DemoTreeList::DelSVSE(string &szIndex)
{
    OBJECT objSE = GetSVSE(szIndex, m_szIDCUser, m_szIDCPwd);
    list<string> lsGroupID;
    list<string> lsDeviceID;
    list<string>::iterator lstItem;
    if(objSE != INVALID_VALUE)
    {
        if(GetSubGroupsIDBySE(objSE, lsGroupID))
        {  
            for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
            {
                string szID = (*lstItem).c_str();
                DelGroup(szID);
            }
        }

        if(GetSubEntitysIDBySE(objSE, lsDeviceID))
        {
            for(lstItem = lsDeviceID.begin(); lstItem != lsDeviceID.end(); lstItem ++)
            {
                string szID = (*lstItem).c_str();
                DelDevice(szID);
            }
        }

        CloseSVSE(objSE);
    }

    DeleteSVSE(szIndex, m_szIDCUser, m_szIDCPwd);
}

void DemoTreeList::DelGroup(string &szIndex)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    if(!szIndex.empty())
    {
        OBJECT group = GetGroup(szIndex, m_szIDCUser, m_szIDCPwd);
        if(group != INVALID_VALUE)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    DelDevice(szEntityID);      
                }            
            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    DelGroup(szSubGroupID);      
                }                
            }

            CloseGroup(group);

            DeleteGroup(szIndex, m_szIDCUser, m_szIDCPwd); 
        }        
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DemoTreeList::DelDevice(string &szIndex)
{
    list<string> lstMonitors;
    list<string>::iterator lstItem;
    if(!szIndex.empty())
    {
        OBJECT entity = GetEntity(szIndex, m_szIDCUser, m_szIDCPwd);
        if (entity != INVALID_VALUE)
        {
            if(GetSubMonitorsIDByEntity(entity, lstMonitors))
            {
                for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                {
                    string szMonitorID = (*lstItem).c_str();
                    DeleteSVMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
                    DeleteTable(szMonitorID, m_szIDCUser, m_szIDCPwd);
                }
            }
        }
        CloseEntity(entity);
        DeleteEntity(szIndex, m_szIDCUser, m_szIDCPwd);
    }
}

//添加客户端脚本变量
void DemoTreeList::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    new WText(strTmp, this);
}

//添加设备节点
void DemoTreeList::AddDeviceTreeNode(std::string szDeviceID,  WTreeNode* parentNode)
{

    WTreeNode* pNode = NULL;
    OBJECT objDevice = GetEntity(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE node = GetEntityMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szName("");
            FindNodeValue(node, "sv_name", szName);

            pNode=makeTreeFile(szName, szDeviceID, Tree_DEVICE, parentNode, "../icons/device.gif", "../icons/device.gif");   
        }
        CloseEntity(objDevice);
    }
}

//添加组节点
WTreeNode * DemoTreeList::AddGroupTreeNode(std::string szSubGroupID, WTreeNode* parentNode)
{
    WTreeNode * tmpNode=NULL;
    OBJECT  groupnode = GetGroup(szSubGroupID, m_szIDCUser, m_szIDCPwd);
    if(groupnode != INVALID_VALUE)
    {
        MAPNODE node = GetGroupMainAttribNode(groupnode);
        if(node != INVALID_VALUE)
        {
            string szName("");
            FindNodeValue(node, "sv_name", szName);

            tmpNode = makeTreeFile(szName, szSubGroupID, Tree_GROUP, parentNode, "../icons/group.gif", "../icons/group.gif");
        }
        CloseGroup(groupnode);
    }
    return tmpNode;
}

//递归以初始化树

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DemoTreeList::EnumGroup(std::string szIndex, WTreeNode* parentNode)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    WTreeNode *tmpNode;
    vector<string >::iterator iSelItor;
    bool bGroup = true;
    if(!szIndex.empty())
    {   
        OBJECT group = INVALID_VALUE;
        if(IsSVSEID(szIndex))
        {
            bGroup = false;
            group = GetSVSE(szIndex, m_szIDCUser, m_szIDCPwd);
        }
        else
            group = GetGroup(szIndex, m_szIDCUser, m_szIDCPwd);
        if(group != INVALID_VALUE)
        {
            bool bSucc = false;
            if(bGroup)
                bSucc = GetSubGroupsIDByGroup(group, lsGroupID);
            else
                bSucc = GetSubGroupsIDBySE(group, lsGroupID);
            if(bSucc)
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param group;
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID =(*lstItem).c_str();
                    bool bHasRight = true;
                    if(m_pSVUser)
                        bHasRight = m_pSVUser->haveGroupRight(szSubGroupID, Tree_DEVICE);
					if(bHasRight)
                    {
                        OBJECT objGroup = GetGroup(szSubGroupID, m_szIDCUser, m_szIDCPwd);
                        if(objGroup != INVALID_VALUE)
                        {
                            MAPNODE node = GetGroupMainAttribNode(objGroup);
                            if(node != INVALID_VALUE)
                            {
                                string szName(""), szIndex("");
                                int nIndex = 0;
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    nIndex = FindIndexByID(szSubGroupID);
                                else
                                    nIndex = atoi(szIndex.c_str());

                                group.szIndex = szSubGroupID;
                                group.szName = szName;

                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = group;
                            }
                            CloseGroup(objGroup);
                        }
                    }
                }
                for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                {
                    tmpNode=AddGroupTreeNode(lsItem->second.szIndex, parentNode);
                    if(tmpNode!=NULL )
                        EnumGroup(lsItem->second.szIndex, tmpNode);
                }               
            }
            if(bGroup)
                bSucc = GetSubEntitysIDByGroup(group, lsEntityID);
            else
                bSucc = GetSubEntitysIDBySE(group, lsGroupID);

            if(bSucc)            
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param device;
                int nIndex = 0;
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID =(*lstItem).c_str();
                    bool bHasRight = true;
                    if(m_pSVUser)
                        bHasRight = m_pSVUser->haveGroupRight(szEntityID, Tree_DEVICE);
					if(bHasRight)
                    {
                        OBJECT objDevice = GetEntity(szEntityID, m_szIDCUser, m_szIDCPwd);
                        if(objDevice != INVALID_VALUE)
                        {
                            MAPNODE node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                string szName(""), szIndex("");
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    nIndex = FindIndexByID(szEntityID);
                                else
                                    nIndex = atoi(szIndex.c_str());

                                device.szIndex = szEntityID;
                                device.szName = szName;
                                
                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = device;
                            }
                            CloseEntity(objDevice);
                        }
                    }
                }
                for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                {
                    AddDeviceTreeNode(lsItem->second.szIndex, parentNode);
                }
            }
            if(bGroup)
                CloseGroup(group);
            else
                CloseSVSE(group);
        }        
    }
}

void DemoTreeList::changeSelNode(string szIndex)
{
    for(unsigned i = 0; i < nodeVector.size(); ++i)
    {
        nodeVector[i]->unSelItem();
    }
    WTreeNode *node = GetNodeById(szIndex);
    if(node != NULL)
    {
        node->SelItem();
        if(node->parentNode_)
            node->parentNode_->expand();
    }
}

bool DemoTreeList::InitTree()
{
    vector<string >::iterator iSelItor;
    nodeVector.clear();

    if(treeroot)
        delete treeroot;
    treeroot = NULL; 

    if(m_pMenutable)
        m_pMenutable->clear();

    WTreeNode *FirstNode = NULL;
    if(m_pSVUser)
    {
        PAIRLIST selist;
        if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
        {       
            sv_pair svpair;
            svpair.name = "1";
            OBJECT objSE = GetSVSE("1", m_szIDCUser, m_szIDCPwd);
            if(objSE != INVALID_VALUE)
            {
                svpair.value = GetSVSELabel(objSE);
                CloseSVSE(objSE);
            }        
            selist.push_back(svpair);
        }
        else
        {
            GetAllSVSEInfo(selist);
            string szName = GetIniFileString("segroup","name","","general.ini");
            if(szName.empty())
                szName = "Siteview";
            FirstNode= makeTreeMap(szName, "-1", Tree_SEGROUP, m_pMenutable, "../icons/home.gif", "../icons/home.gif");  
            treeroot = FirstNode;
        }        
        PAIRLIST::iterator iSe;
        for(  iSe= selist.begin();iSe!=selist.end();iSe++)
        {
            string szSEID = (*iSe).name;
            bool bHasRight = true;
            if(m_pSVUser)
                bHasRight = m_pSVUser->haveGroupRight(szSEID, Tree_SE);
            if(bHasRight)
            {
                OBJECT root = GetSVSE(szSEID, m_szIDCUser, m_szIDCPwd);
                list<string> lsGroupID;
                list<string>::iterator lstItem;
                WTreeNode *tmpNode = NULL;
                if(treeroot != NULL)
                {
                    string szName = (*iSe).name;
                    FirstNode = makeTreeFile((*iSe).value, szName, Tree_SE, treeroot, "../icons/home.gif", "../icons/home.gif"); 
                }
                else
                {
                    FirstNode = makeTreeMap((*iSe).value, (*iSe).name, Tree_SE, m_pMenutable, "../icons/home.gif", "../icons/home.gif"); 
                    treeroot= FirstNode ;
                }
                if (root != INVALID_VALUE)
                {	
                    int nChildCount = 0;	
                    //第一层组
			        if(GetSubGroupsIDBySE(root, lsGroupID))
			        {
                        map<int, base_param, less<int> > sortList;
                        map<int, base_param, less<int> >::iterator lsItem;
                        base_param group;
                        int nIndex = 0;
                        for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                        {
                            string szSubGroupID =(*lstItem).c_str();
                            bHasRight = true;
                            if(m_pSVUser)
                                bHasRight = m_pSVUser->haveGroupRight(szSubGroupID, Tree_DEVICE);
					        if(bHasRight)
                            {
                                OBJECT objGroup = GetGroup(szSubGroupID, m_szIDCUser, m_szIDCPwd);
                                if(objGroup != INVALID_VALUE)
                                {
                                    MAPNODE node = GetGroupMainAttribNode(objGroup);
                                    if(node != INVALID_VALUE)
                                    {
                                        string szName(""), szIndex("");
                                        //FindNodeValue(node, "sv_name", szName);
                                        FindNodeValue(node, "sv_index", szIndex);
                                        if(szIndex.empty())
                                            nIndex = FindIndexByID(szSubGroupID);
                                        else
                                            nIndex = atoi(szIndex.c_str());

                                        group.szIndex = szSubGroupID;
                                        group.szName = szName;

                                        lsItem = sortList.find(nIndex);
                                        while(lsItem != sortList.end())
                                        {
                                            nIndex ++;
                                            lsItem = sortList.find(nIndex);
                                        }
                                        sortList[nIndex] = group;
                                    }
                                    CloseGroup(objGroup);
                                }
                            }
                        }
                        nChildCount += static_cast<int>(sortList.size());
                        for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                        {
                            tmpNode=AddGroupTreeNode(lsItem->second.szIndex, FirstNode);
                            if(tmpNode!=NULL )
                                EnumGroup(lsItem->second.szIndex, tmpNode);
                        }
                    }

                    if(GetSubEntitysIDBySE(root, lsGroupID))
                    {
                        map<int, base_param, less<int> > sortList;
                        map<int, base_param, less<int> >::iterator lsItem;
                        base_param device;
                        int nIndex = 0;
                        for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                        {
                            string szEntityID =(*lstItem).c_str();
                            bHasRight = true;
                            if(m_pSVUser)
                                bHasRight = m_pSVUser->haveGroupRight(szEntityID, Tree_DEVICE);
					        if(bHasRight)
                            {
                                OBJECT objDevice = GetEntity(szEntityID, m_szIDCUser, m_szIDCPwd);
                                if(objDevice != INVALID_VALUE)
                                {
                                    MAPNODE node = GetEntityMainAttribNode(objDevice);
                                    if(node != INVALID_VALUE)
                                    {
                                        string szName(""), szIndex("");
                                        FindNodeValue(node, "sv_index", szIndex);
                                        if(szIndex.empty())
                                            nIndex = FindIndexByID(szEntityID);
                                        else
                                            nIndex = atoi(szIndex.c_str());

                                        device.szIndex = szEntityID;
                                        device.szName = szName;

                                        lsItem = sortList.find(nIndex);
                                        while(lsItem != sortList.end())
                                        {
                                            nIndex ++;
                                            lsItem = sortList.find(nIndex);
                                        }
                                        sortList[nIndex] = device;
                                    }
                                    CloseEntity(objDevice);
                                }
                            }
                        }
                        nChildCount += static_cast<int>(sortList.size());
                        for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                            AddDeviceTreeNode(lsItem->second.szIndex, FirstNode);
                    }
			        CloseSVSE(root); 
                    if(nChildCount <= 0)
                    {
                        string szID = "-2" + szSEID;
                        WTreeNode *pNode = new WTreeNode(this, m_szNoChild, "-2", Tree_NOCHILD, -1, WText::XHMTLFormatting, NULL, NULL, NULL, m_szIDCUser, m_szIDCPwd);
                        //pNode->m_pParentTreeView=(DemoTreeList *)this;
                        if (FirstNode)
                        {
                            FirstNode->addChildNode(pNode, Tree_NOCHILD);
                        }
                    }
				}
            }
	    }
    }
	return true;
}

//翻译后刷新
void DemoTreeList::ExChangeRefresh()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/treeview.exe?'\",1250);  ";
	appSelf->quit();
}

////////////////////////////////////////////////////////////////////////////////////
typedef void( *func)(int , char **);

void wmain1(int argc, char *argv[])
{
  WApplication app(argc, argv);
  //pTreeApp = &app;
  app.setTitle("Siteview 7.0");
  string strTmp("");

  DemoTreeList firsttest(app.root());
  firsttest.appSelf = &app;
  firsttest.InitTree();

  strTmp +="class='workbody' onmousemove='resizeTable(\"" + firsttest.getResizeObjectID()
      +  "\")\' oncontextmenu='return false;' scroll='no' margin:0px";
  app.setBodyAttribute(strTmp.c_str());
  app.exec();
}

int main(int argc, char * argv[])
{
    func p = wmain1;
    if (argc == 1) 
    {
        srand((unsigned)time( NULL ));
        int rand1 = rand();
        char buf[256];
        itoa(rand1, buf, 10);
        WebSession s(buf, false);
        s.m_bReload = true;
        s.start(p);
		return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }

    return 0;
}

void DemoTreeList::InPhaseView()
{
    string szCurSelID(m_pCurFocusEdit_->text());
    if(szCurSelID.empty())
        szCurSelID = "1";
    InitTree(); 
    WebSession::js_af_up = "hiddenbar();";
}

//////////////////////////////////////////////////////////////////////////////////
