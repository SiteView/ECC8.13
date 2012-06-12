/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
#include <WTable>
#include <WTableCell>
#include <WImage>
#include <WText>
#include <WSVLinkText>
#include <WFont>
#include <WPushButton>
#include <WCssDecorationStyle>

#include <Algorithm>
#include "WTreeNode.h"
#include "WStateIcon.h"
#include "WebSession.h"
#include "../../kennel/svdb/svapi/svapi.h"

#include "DemoTreeList.h"
//#include "popmenu.h"
#include "../group/basefunc.h"

extern void PrintDebugString(const char *szMsg);

std::string WTreeNode::imageFold_[]={"../icons/foldopen.gif", "../icons/foldclose.gif"};
WTreeNode::WTreeNode(DemoTreeList *pTreeList, const std::string labelText, const std::string nodeId, int nType, int nState,
                     WText::Formatting labelFormatting,
                     WStateIcon *labelIcon,
                     WWidget *userContent,
                     WContainerWidget *parent,
                     string szIDCUser,
                     string szIDCPwd)
                     : parentNode_(0),
                     m_pParentTreeView(pTreeList),
                     strId(nodeId),
                     labelIcon_(labelIcon),
                     userContent_(userContent),
                     nTreeType(nType),
                     m_szIDCUser(szIDCUser),
                     m_szIDCPwd(szIDCPwd)
{
    bFistundoCollapse = true;
    //m_pParentTreeView = NULL;

    bSelected = false;
    bCurrently = false;	
    m_bNoChild = false;
    setImplementation(layout_ = new WTable(parent));

    expandedContent_ = new WContainerWidget();
    if (userContent)
        expandedContent_->addWidget(userContent);

    expandedDeviceContent_ = new WContainerWidget();
    if (userContent)
        expandedDeviceContent_->addWidget(userContent);

    labelText_ = new WText(labelText);
    if(labelText_)
    {
        labelText_->setToolTip(labelText);
        labelText_->setFormatting(labelFormatting);
    }


    expandIcon_ = NULL;
    if(nType != Tree_DEVICE && nType != Tree_NOCHILD)
    {
        expandIcon_ = new WStateIcon(imageFold_[OPEN], imageFold_[CLOSE ]);
        if(expandIcon_)
        {
            connect(expandIcon_->icon1(), SIGNAL(clicked()), this, SLOT(expand()), STATIC);
            connect(expandIcon_->icon2(), SIGNAL(clicked()),this, SLOT(collapse()), STATIC);
        }
    }
    else if(nType == Tree_DEVICE)
    {
        expandIcon_ = new WStateIcon("../icons/small_normal.gif", "../icons/small_normal.gif");
        if(expandIcon_)
        {
            switch(nState)
            {
            case dyn_normal:
                break;
            case dyn_warnning:
                expandIcon_->icon1()->setImageRef("../icons/small_warnning.gif");
                break;
            case dyn_error:
                expandIcon_->icon1()->setImageRef("../icons/small_error.gif");
                break;
            case dyn_disable:
                expandIcon_->icon1()->setImageRef("../icons/small_disablemonitor.gif");
                break;
            }
        }
    }

    if(expandIcon_)
        layout_->elementAt(0, 0)->addWidget(expandIcon_);

    if (labelIcon_) 
    {   
        layout_->elementAt(0, 1)->addWidget(labelIcon_);
    }

    if(labelText_)
    {
        layout_->elementAt(0, 1)->addWidget(labelText_);
    }
    layout_->elementAt(1, 1)->addWidget(expandedContent_);
    layout_->elementAt(2, 1)->addWidget(expandedDeviceContent_);

    //焦点
    m_szFocus = "SetCurfocus(\"" + strId + "\")";


    //根据权限显示相应的菜单项．．．．．．．．未做

    //右键菜单
    if(nType == Tree_SE)
    {
        if(expandIcon_)
            expandIcon_->showIcon2();
    }
    else if(nType == Tree_GROUP)
    {        
        if(expandIcon_)
            expandIcon_->showIcon2();
    }

    if(labelText_ && nType != Tree_NOCHILD)
    {
        string szMenu(makeMenuText());
        sprintf(labelText_->contextmenu_, "class='treelink' onclick='%s' oncontextmenu='showPopMenu(\"%s\",\"%d\",\"%s\");' onmouseover='mouseover(this)' onmouseout='mouseout(this)'",
            m_szFocus.c_str(), strId.c_str(), nType, szMenu.c_str());
    }
    if(expandedContent_) expandedContent_->show();
    if(expandedDeviceContent_) expandedDeviceContent_->show();
}

WTreeNode::~WTreeNode()
{
    vector<WTreeNode*>::iterator itNode;
    for(itNode = childNodes_.begin(); itNode != childNodes_.end(); itNode ++)
        delete (*itNode);
}

void WTreeNode::addChildNode(WTreeNode *node, int nType)
{
    if(m_bNoChild)
    {
        vector<WTreeNode*>::iterator itNode;
        for(itNode = childNodes_.begin(); itNode != childNodes_.end(); itNode ++)
            delete (*itNode);

        childNodes_.clear();
        m_bNoChild = false;
    }

    childNodes_.push_back(node);
    switch(nType)
    {
    case Tree_SE:
    case Tree_GROUP:
        expandedContent_->addWidget(node);
        break;
    case Tree_NOCHILD:
        expandedDeviceContent_->addWidget(node);
        m_bNoChild = true;
        break;
    case Tree_DEVICE:
        expandedDeviceContent_->addWidget(node);
        break;
    }
    node->parentNode_ = this;
    childNodesChanged();
}

void WTreeNode::removeChildNode(WTreeNode *node)
{
    childNodes_.erase(std::find(childNodes_.begin(), childNodes_.end(), node));	

    node->parentNode_ = 0;

    expandedContent_->removeWidget(node); 
    expandedDeviceContent_->removeWidget(node);
    childNodesChanged();
}

void WTreeNode::childNodesChanged()
{
    adjustExpandIcon();
}

void WTreeNode::collapse()
{
    wasCollapsed_ = expandedContent_->isHidden();
    expandedContent_->hide();
    expandedDeviceContent_->hide();
    if (labelIcon_)
    {
        labelIcon_->setIcon(0);
    }
}

void WTreeNode::expand()
{
    wasCollapsed_ = expandedContent_->isHidden();
    expandedContent_->show();
    expandedDeviceContent_->show();
    if(expandIcon_ && (nTreeType == Tree_GROUP || nTreeType == Tree_SE))
        expandIcon_->setIcon(1);
    if (labelIcon_)	
        labelIcon_->setIcon(0);
    if(parentNode_)
        parentNode_->expand();
}

void WTreeNode::undoCollapse()
{
    if(bFistundoCollapse&&(nTreeType==Tree_DEVICE ))
    {
        bFistundoCollapse =false;
        if(expandIcon_)
            expandIcon_->setIcon(0);
        expandedContent_->show();
        expandedDeviceContent_->show();
    }
    else
    {
        if (!wasCollapsed_) 
        {
            // re-expand
            if(expandIcon_)
                expandIcon_->setIcon(1);
            expandedContent_->show();
            expandedDeviceContent_->show();
            if (labelIcon_)
                labelIcon_->setIcon(1);    
        }
    }
}

void WTreeNode::undoExpand()
{
    if (wasCollapsed_) 
    {
        // re-collapse
        if(expandIcon_)
            expandIcon_->setIcon(0);
        expandedContent_->hide();
        expandedDeviceContent_->hide();
        if (labelIcon_)
            labelIcon_->setIcon(0);
  }
}


void WTreeNode::adjustExpandIcon()
{
	wasCollapsed_ = expandedContent_->isHidden();
	if(wasCollapsed_ && expandIcon_)
	{
		expandIcon_->showIcon1();
	}
	else
	{
		expandIcon_->showIcon2();
	}
}

void WTreeNode::unSelItem()
{	
	if(bSelected)
		labelText_->setStyleClass("treelink");
	bSelected = false;
}

void WTreeNode::SelItem()
{
	bSelected = true;
	labelText_->setStyleClass("treelinkactive");
    wasCollapsed_ = expandedContent_->isHidden();
    expandedContent_->show();
    expandedDeviceContent_->show();
    if(expandIcon_ && (nTreeType == Tree_GROUP || nTreeType == Tree_SE))
        expandIcon_->setIcon(1);
    if (labelIcon_)	
        labelIcon_->setIcon(0);
}

void WTreeNode::SetCurrentItem()
{
	bCurrently = true;
}

void WTreeNode::UnSetCurrentItem()
{	
	if(!bSelected)
	{
		if(bCurrently)
		{
			labelText_->setStyleClass("treelink");
			bCurrently = false;
		}
	}

	bCurrently = false;
}

void WTreeNode::ChangeText(string strName)
{
	labelText_->setText(strName);
}

void WTreeNode::ChangeState(const int &nState)
{
    if(expandIcon_)
    {
        switch(nState)
        {
        case dyn_normal:
            expandIcon_->icon1()->setImageRef("../icons/small_normal.gif");
            break;
        case dyn_warnning:
            expandIcon_->icon1()->setImageRef("../icons/small_warnning.gif");
            break;
        case dyn_error:
            expandIcon_->icon1()->setImageRef("../icons/small_error.gif");
            break;
        case dyn_disable:
            expandIcon_->icon1()->setImageRef("../icons/small_disablemonitor.gif");
            break;
        }
    }
    //UpdateContentText();
}

bool WTreeNode::HasChild()
{
	if(!childNodes_.empty())
		return true;
	return false;
}

string WTreeNode::makeMenuText()
{
    string          szMenu("");
    char            szMenus[32] = {0};

    bool bHasAddSERight = false;
    bool bHasAddGroupRight = false;
    bool bHasAddDeviceRight = false;
    bool bHasAddMonitorRight = false;

    bool bHasEditRight = false;
    
    bool bHasDelRight = false;

    bool bHasDeviceRefresh = false;
    bool bDisable = false;

    switch(nTreeType)
    {
    case Tree_SE:
        if(m_pParentTreeView && m_pParentTreeView->m_pSVUser)
        {
            bHasAddGroupRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "addsongroup");
            bHasAddDeviceRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "adddevice");
            bHasEditRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "se_edit");
            sprintf(szMenus, "%d%d00%d00000", bHasAddGroupRight, bHasAddDeviceRight, bHasEditRight);
        }
        break;
    case Tree_GROUP:
        if(m_pParentTreeView && m_pParentTreeView->m_pSVUser)
        {
            bHasDelRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "delgroup");
            bHasEditRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "editgroup");
            bHasAddGroupRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "addsongroup");
            bHasAddDeviceRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "adddevice");
            sprintf(szMenus, "%d%d0%d%d0%d%d%d0", bHasAddGroupRight, bHasAddDeviceRight, bHasEditRight, 
                    bHasDelRight, bHasAddDeviceRight, bHasEditRight, bHasEditRight);
        }
        break;
    case Tree_DEVICE:
        if(m_pParentTreeView && m_pParentTreeView->m_pSVUser)
        {
            bHasDelRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "deldevice");
            bHasEditRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "editdevice");
            bHasAddMonitorRight = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "addmonitor");
            bHasDeviceRefresh  = m_pParentTreeView->m_pSVUser->haveUserRight(strId, "devicerefresh");
            sprintf(szMenus, "00%d%d%d%d0%d%d%d", bHasAddMonitorRight,  bHasEditRight, bHasDelRight, 
                bHasEditRight, bHasEditRight, bHasEditRight, bHasDeviceRefresh);
        }
        break;
    default:
        sprintf(szMenus, "0000000000");
        break;
    }

    szMenu = szMenus;
    return szMenu;
}

void WTreeNode::UpdateContentText()
{
    if(labelText_)
    {
        string szMenu(makeMenuText());
        PrintDebugString(szMenu.c_str());
        sprintf(labelText_->contextmenu_, "class='treelink' onclick='%s' oncontextmenu='showPopMenu(\"%s\",\"%d\",\"%s\");' onmouseover='mouseover(this)' onmouseout='mouseout(this)'",
            m_szFocus.c_str(), strId.c_str(), nTreeType, szMenu.c_str());
    }
}

