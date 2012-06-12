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
#include "WColor"
#include "WMenuNode.h"
#include "WBorder"

#include "WebSession.h"

#include "svmenu.h"

WMenuNode::WMenuNode(const std::string labelText,  int controlid, WText::Formatting labelFormatting,  
					 WImage *labelIcon,  WWidget *userContent, WContainerWidget *parent, bool bPMenu)
  : parentNode_(0),
    labelIcon_(labelIcon),
    userContent_(userContent)
{
  setImplementation(layout_ = new WTable(parent));

  expandedContent_ = new WContainerWidget();
  if (userContent)
    expandedContent_->addWidget(userContent);

  labelText_ = new WText(labelText);
  labelText_->setFormatting(labelFormatting);
  labelText_->decorationStyle().font().setFamily(WFont::Serif, "Helvetica");
  
  if (labelIcon_) 
  {
    layout_->elementAt(0, 0)->addWidget(labelIcon_);
    labelIcon_->setVerticalAlignment(AlignMiddle);
  }
  
  labelText_->setToolTip(labelText);
  layout_->elementAt(0, 0)->addWidget(labelText_);
  

  layout_->elementAt(1, 0)->addWidget(expandedContent_);
  layout_->decorationStyle().setCursor(WCssDecorationStyle::Pointer);

    
  //每次treenode 初始化 执行expand出错	
  nFirstExpand=0;
  
  bSelItem = false;  
  bAnswer = true;
  nodeid = controlid;

  if(bPMenu)
  {
	  bChild = false;
	  layout_->elementAt(0, 0)->resize(WLength(110), WLength(19));
	  layout_->elementAt(0, 0)->decorationStyle().setBackgroundImage("../icons/menushow.gif",
		WCssDecorationStyle::NoRepeat);
	  //layout_->elementAt(0, 0)->setStyleClass("nav2title");
	  WBorder wb;
	  wb.setWidth(WBorder::Thin);
	  layout_->decorationStyle().setBorder(wb);
	  connect(layout_, SIGNAL(clicked()),  this, SLOT(expand()));
	  //connect(labelText_, SIGNAL(clicked()),  this, SLOT(expand()));
  }
  else
  {
		bChild = true;
		layout_->elementAt(0, 0)->resize(WLength(110), WLength(19));
		//layout_->elementAt(0, 0)->decorationStyle().setBackgroundColor(Wt::white);
		//layout_->elementAt(0, 0)->setStyleClass("general");
		labelText_->setStyleClass("general");
		std::string strId = "1";
		WObject::connect(labelText_, SIGNAL(mouseWentOver()), "menumouseover(this)", WObject::ConnectionType::JAVASCRIPT);
		WObject::connect(labelText_, SIGNAL(mouseWentOut()), "menumouseout(this)", WObject::ConnectionType::JAVASCRIPT);

		//焦点
		std::string strJs;
		char chItem[10]  = {0};
		sprintf(chItem, "%d", nodeid);

		strJs  = "SetMenufocus(\"";
		strJs += chItem;
		strJs +=  "\",";
		WObject::connect(layout_ , SIGNAL(clicked()),  strJs.c_str() ,this, SLOT(expand()));
		//WObject::connect(labelText_ , SIGNAL(clicked()),  strDelDes.c_str() ,this, SLOT(expand()));

		labelText_->setStyleClass("general");
  }
  
  layout_->elementAt(0, 0)->setContentAlignment(AlignTop);
}

void WMenuNode::addChildNode(WMenuNode *node)
{
	childNodes_.push_back(node);
	node->parentNode_ = this;

	expandedContent_->addWidget(node);
}

void WMenuNode::expand()
{
	if(nFirstExpand==0)
	{
	  nFirstExpand++;
	  return;
	}

	if(bChild)
	{
		//子菜单项...
		for(unsigned i = 0; i < pTopParent->menuParent_.size(); ++i)
			pTopParent->menuParent_[i]->unSelItem();

		//选中新选项(前景色、背景色、图标等)
		//labelText_->decorationStyle().setForegroundColor(Wt::green);
		//layout_->elementAt(0, 0)->decorationStyle().setBackgroundColor(Wt::red);
		labelText_->setStyleClass("onfoucs");
		//labelIcon_->setImageRef("../icons/error.gif");

		parentNode_->bAnswer = false;
		bSelItem = true;
	}
	else
	{		
		if(bAnswer)
		{
			//父级菜单...
			//OutputDebugString(labelText_->text().c_str());
			//OutputDebugString("\n");			
			//OutputDebugString("expand\n");  
			wasCollapsed_ = expandedContent_->isHidden();
			if(wasCollapsed_ )
				expand1();
			else
				collapse();	
		}
		else
			bAnswer = true;
	}  
}

void WMenuNode::expand1()
{
	wasCollapsed_ = expandedContent_->isHidden();
	layout_->elementAt(0, 0)->decorationStyle().setBackgroundImage("../icons/menushow.gif",
		WCssDecorationStyle::NoRepeat);

	expandedContent_->show();
}

void WMenuNode::collapse()
{	
	wasCollapsed_ = expandedContent_->isHidden();
	layout_->elementAt(0, 0)->decorationStyle().setBackgroundImage("../icons/menuhide.gif",
		WCssDecorationStyle::NoRepeat);
	
	expandedContent_->hide();
}

void WMenuNode::unSelItem()
{
	if(bChild && bSelItem)
	{
		//layout_->elementAt(0, 0)->decorationStyle().setBackgroundColor(Wt::white);
		//labelIcon_->setImageRef("../icons/normal.gif");
		//layout_->elementAt(0, 0)->setStyleClass("onfoucs");
		labelText_->setStyleClass("general");
	}
	else if(!bChild)
	{
	    for(unsigned i = 0; i < childNodes_.size(); ++i)
			childNodes_[i]->unSelItem();
	}
	else
	{
		
	}
}

//以下暂时未用...

void WMenuNode::undoCollapse()
{

}

void WMenuNode::undoExpand()
{

}
