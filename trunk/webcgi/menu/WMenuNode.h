// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef WMenuNode_H_
#define WMenuNode_H_

#include <WCompositeWidget>
#include <WText>


class WStateIcon;
class WTable;
class WImage;
class SVMenu;

class WMenuNode : public WCompositeWidget
{
  //MOC: W_OBJECT WMenuNode:WCompositeWidget
  W_OBJECT;

public:
  WMenuNode(const std::string labelText, int controlid, 
	    WText::Formatting labelFormatting,
	    WImage *labelIcon, WWidget *userContent,
	    WContainerWidget *parent = 0,bool bPMenu=true );

  void addChildNode(WMenuNode *node);

  const std::vector<WMenuNode *>& childNodes() const { return childNodes_; }

  //cxy add 
  bool bChild;
  bool bSelItem;    
  bool bAnswer;
  int nodeid;
  SVMenu* pTopParent;
  void unSelItem();
public static_slots:
  //MOC: STATIC SLOT WMenuNode::collapse()
  void collapse();
  //MOC: STATIC SLOT WMenuNode::expand()
  void expand();

private:
  std::vector<WMenuNode *> childNodes_;
  WMenuNode		   *parentNode_;

  WTable                   *layout_;
  //WStateIcon               *expandIcon_;
  //WImage		   *noExpandIcon_;
  WImage		   *labelIcon_;
  WText			   *labelText_;
  //WText			   *childCountLabel_;
  WWidget                  *userContent_;
  WContainerWidget         *expandedContent_;

  int nFirstExpand;

  bool wasCollapsed_;
  void undoCollapse();
  void undoExpand();
  void expand1();
};

#endif // WMenuNode_H_
