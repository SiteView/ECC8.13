/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
#include <boost/lexical_cast.hpp>
#include <WTable>
#include <WTableCell>
#include <WImage>
#include <WText>
#include <WCssDecorationStyle>
#include <Algorithm>

#include "WTreeNode.h"
#include "WStateIcon.h"
#include "CheckBoxTreeView.h"

#include <svapi.h>
#include <windows.h>
#include "WebSession.h"
#include "WPushButton"
#include "../base/basetype.h"

std::string WTreeNode::imageFold_[]={"/Images/cb1-unwrap.gif",
"/Images/cb1-fold.gif"};

WTreeNode::WTreeNode(const std::string labelText, const std::string nodeId, bool bCheck, bool bDevice,int nType, 
                     WText::Formatting labelFormatting,
                     WStateIcon *labelIcon,
                     WWidget *userContent, WContainerWidget *parent)
                     : parentNode_(0),
                     labelIcon_(labelIcon),
                     userContent_(userContent),
                     wasSelected_(false)
{
	_win.push_back("/Images/cbb-4server.gif");
	_win.push_back("/Images/cbb-4server_r.gif");
	_win.push_back("/Images/cbb-4server.gif");

	_unix.push_back("/Images/cbb-4server.gif");
	_unix.push_back("/Images/cbb-4server_r.gif");
	_unix.push_back("/Images/cbb-4server.gif");	

	_default.push_back("/Images/cbb-5router.gif");
	_default.push_back("/Images/cbb-5router_r.gif");
	_default.push_back("/Images/cbb-5router.gif");

	deveiceImg.insert(make_pair("_win",_win));
	deveiceImg.insert(make_pair("_unix",_unix));
	deveiceImg.insert(make_pair("_default",_default));

    bMExpand =false;
    bFirst = true;
    bFirstadjust=true;
    bFistundoCollapse =true;
    m_CheckBoxTreeView =NULL;
    treeCheckBox_ =NULL;
    nTreeType= nType;
    setImplementation(layout_ = new WTable(parent));


    layout_->setCellPadding(0);
    layout_->setCellSpaceing(0);
	layout_->setStyleClass("widthauto");

    strId = nodeId;
    expandIcon_ = new WStateIcon(imageFold_[OPEN], imageFold_[CLOSE ]);
    expandedContent_ = new WContainerWidget();
    //expandedContent_->hide();
    if (userContent)
        expandedContent_->addWidget(userContent);

	std::string temp = " " + labelText;
    labelText_ = new WText(temp);
    labelText_->setFormatting(labelFormatting);
	labelText_->setStyleClass("hand");
	labelText_->setToolTip(labelText);


    connect(labelText_ , SIGNAL(clicked()), this ,SLOT(OnRightClick()));

    noExpandIcon_ = new WImage("../Images/9bland.gif");

	WText *blank = new WText("&nbsp;");
	layout_->elementAt(0, 0)->setStyleClass("padding_right_2");
    layout_->elementAt(0, 0)->addWidget(expandIcon_);
    layout_->elementAt(0, 0)->addWidget(noExpandIcon_);
	layout_->elementAt(0, 0)->addWidget(blank);

    if( (false==bDevice)&&( Tree_DEVICE==nTreeType))//ajax --monitor
    {
        noExpandIcon_->hide();
    }else 
    {
        expandIcon_->hide();
    }

    treeCheckBox_ = new WCheckBox(labelText);
    treeCheckBox_->setStyleClass("smallcheckbox");

    if(nTreeType==Tree_MONITOR)
    {
        connect(treeCheckBox_,SIGNAL(clicked()),this,SLOT(OnTreeNodeCheck()));
        layout_->elementAt(0, 1)->setStyleClass("tree_text");
    }
    if (labelIcon_) 
    {
        if(bCheck)
        {
            layout_->elementAt(0, 0)->addWidget(treeCheckBox_);
        }
        layout_->elementAt(0, 1)->addWidget(labelIcon_);
        labelIcon_->setVerticalAlignment(AlignMiddle);
    }
    layout_->elementAt(0, 1)->addWidget(labelText_);	
    layout_->elementAt(1, 1)->addWidget(expandedContent_);
    layout_->elementAt(0, 0)->setVerticalAlignment(AlignMiddle);
    layout_->elementAt(0, 0)->setContentAlignment(AlignMiddle);
    layout_->elementAt(0, 1)->setContentAlignment(AlignMiddle);
    layout_->elementAt(0, 1)->setVerticalAlignment(AlignMiddle);



    //add end
    connect(expandIcon_->icon1(), SIGNAL(clicked()),
        this, SLOT(expand()), STATIC);
    connect(expandIcon_->icon2(), SIGNAL(clicked()),
        this, SLOT(collapse()), STATIC);
}

bool WTreeNode::isLastChildNode() const
{
    if (parentNode_) {
        return parentNode_->childNodes_.back() == this;
    } else
        return true;
}

void WTreeNode::addChildNode(WTreeNode *node)
{
    childNodes_.push_back(node);
    node->parentNode_ = this;

    expandedContent_->addWidget(node);

    childNodesChanged();
}

void WTreeNode::removeChildNode(WTreeNode *node)
{
    childNodes_.erase(std::find(childNodes_.begin(), childNodes_.end(), node));

    node->parentNode_ = 0;

    expandedContent_->removeWidget(node);

    childNodesChanged();
}

void WTreeNode::childNodesChanged()
{
    /*	
    for (unsigned i = 0; i < childNodes_.size(); ++i)
    childNodes_[i]->adjustExpandIcon();


    adjustExpandIcon();

    staticSlotChanged(SLOT(expand()));
    staticSlotChanged(SLOT(collapse()));
    */
    adjustExpandIcon();
}

void WTreeNode::collapse()
{
    //if(strId=="1.11") OutputDebugString("collapse \n");  
    //return;
    wasCollapsed_ = expandedContent_->isHidden();

    //expandIcon_->setIcon(0);
    expandedContent_->hide();
    if (labelIcon_)
        labelIcon_->setIcon(0);
}

void WTreeNode::expand()
{

	OutputDebugString("expand called \n");

    //if(strId=="1.11") OutputDebugString("expand() \n");  
    wasCollapsed_ = expandedContent_->isHidden();

    //expandIcon_->setIcon(1);
    expandedContent_->show();

    if (labelIcon_)	
        labelIcon_->setIcon(1);

    if((bFirst==false)&&(bMExpand== false)&& (nTreeType==Tree_DEVICE)  )
    {
        OutputDebugString("assssss\n");

        bMExpand =true;

        std::string tmpclick= m_CheckBoxTreeView->pMonitorBtn->getEncodeCmd("xclicked()");
        char tmpchar[200];

        sprintf(tmpchar,"update(\"%s\");",tmpclick.c_str());
        WebSession::js_af_up =tmpchar;
        if(m_CheckBoxTreeView)
            m_CheckBoxTreeView->pTestNode=this;
    }
    bFirst =false;
    /*
    * collapse all children
    */
    /*
    for (unsigned i = 0; i < childNodes_.size(); ++i)
    childNodes_[i]->collapse();
    */
}

void WTreeNode::SelItem()
{
    labelText_->setStyleClass("hand");
}

void WTreeNode::UnSelItem()
{
    labelText_->setStyleClass("hand");
}

void WTreeNode::SetTreeCheck(bool bNodeCheck)
{
	for (unsigned i = 0; i < childNodes_.size(); ++i)
		{
			childNodes_[i]->treeCheckBox_->setChecked(bNodeCheck);
			childNodes_[i]->SetTreeCheck(bNodeCheck);
		}
}
void WTreeNode::OnTreeNodeCheck()
{
	
	if(treeCheckBox_->isChecked())		
		SetTreeCheck(true);
	else
		SetTreeCheck(false);


}
void WTreeNode::OnRightClick()
{
	if(nTreeType==Tree_MONITOR)
		m_CheckBoxTreeView->SetTreeNodeRight(this,true);

}

void WTreeNode::select()
{
/*	if(treeCheckBox_->nCheck)
	{
		UnSelected();
	}
	else
	{
		Selected();
	}	
	*/
	if(treeCheckBox_->nCheck)
	{
		treeCheckBox_->SetCheck(false);
	}
	else
	{
		treeCheckBox_->SetCheck(true);
	}

}

void WTreeNode::Selected()
{
		treeCheckBox_->nCheck = true;
		treeCheckBox_->SetCheck(true);
		for (unsigned i = 0; i < childNodes_.size(); ++i)
		{
			childNodes_[i]->Selected();
			
		}
}

void WTreeNode::UnSelected()
{
	
		treeCheckBox_->nCheck = false;
		treeCheckBox_->SetCheck(false);
		for (unsigned i = 0; i < childNodes_.size(); ++i)
		{
			childNodes_[i]->UnSelected();			
		}
}
void WTreeNode::undoCollapse()
{
	//last run
	//if(strId=="1.11") OutputDebugString("undoCollapse() \n");  
    if(bFistundoCollapse&&(nTreeType==Tree_DEVICE ))
	{
		bFistundoCollapse =false;
		expandIcon_->setIcon(0);
		expandedContent_->show();

	}
	else{
		if (!wasCollapsed_) {
			// re-expand
			expandIcon_->setIcon(1);
			expandedContent_->show();
			if (labelIcon_)
			labelIcon_->setIcon(1);    
		}
	}

}

void WTreeNode::undoExpand()
{
	//if(strId=="1.11") OutputDebugString("undoCollapse() \n");  
	
  if (wasCollapsed_) {
    // re-collapse
    expandIcon_->setIcon(0);
    expandedContent_->hide();
    if (labelIcon_)
      labelIcon_->setIcon(0);
  }

  /*
   * undo collapse of children
   */
  //for (unsigned i = 0; i < childNodes_.size(); ++i)
    //childNodes_[i]->undoCollapse();  
}

void WTreeNode::undoSelect()
{
	refresh();
}

void WTreeNode::adjustExpandIcon()
{
	
//	OutputDebugString("begin adjustExpandIco1n()\n");
	/*
	if(nTreeType==Tree_DEVICE)
	{
		//OutputDebugString("begin adjustExpandIcon()\n");
		if(bFirstadjust)
		{
			expandIcon_->showIcon1();
			//OutputDebugString("adjustExpandIcon()\n");
		}
		bFirstadjust=false;

	}*/



	if (childNodes_.empty()) {
		if (noExpandIcon_->isHidden()) {
		noExpandIcon_->show();
		expandIcon_->hide();
		}
	} else {
		if (expandIcon_->isHidden()) {
		noExpandIcon_->hide();
		expandIcon_->show();
		}
  }

	wasCollapsed_ = expandedContent_->isHidden();
	if(wasCollapsed_)
	{
		expandIcon_->showIcon1();
	}else {
		expandIcon_->showIcon2();
	}


	/*
  ImageIndex index = isLastChildNode() ? OPEN : CLOSE;

  if (expandIcon_->icon1()->imageRef() != imageFold_[index])
    expandIcon_->icon1()->setImageRef(imageFold_[index]);
  if (expandIcon_->icon2()->imageRef() != imageFold_[index])
    expandIcon_->icon2()->setImageRef(imageFold_[index]);
	*/
  /*if (noExpandIcon_->imageRef() != imageFold_[index])
    noExpandIcon_->setImageRef(imageFold_[index]);
*/
  /*
  if (index == Last) {
    layout_->elementAt(0, 0)
      ->decorationStyle().setBackgroundImage("");
    layout_->elementAt(1, 0)
      ->decorationStyle().setBackgroundImage("");
  } else {
    layout_->elementAt(0, 0)
      ->decorationStyle().setBackgroundImage("../Images/line-trunk.gif",
					     WCssDecorationStyle::RepeatY);
    layout_->elementAt(1, 0)
      ->decorationStyle().setBackgroundImage("../Images/line-trunk.gif",
					     WCssDecorationStyle::RepeatY);
					
  }
*/
/*
  if (childNodes_.empty()) {
    if (noExpandIcon_->isHidden()) {
      noExpandIcon_->show();
      expandIcon_->hide();
    }
  } else {
    if (expandIcon_->isHidden()) {
      noExpandIcon_->hide();
      expandIcon_->show();
    }
  }
  */
}

