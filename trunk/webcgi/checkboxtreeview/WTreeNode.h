// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef WTREENODE_H_
#define WTREENODE_H_

#include <WCompositeWidget>
#include <WText>
#include <WCheckBox>

class WStateIcon;
class WTable;
class WImage;
class CCheckBoxTreeView;

//enum TreeNodeType { Tree_SEGROUP, Tree_SE,Tree_GROUP,Tree_DEVICE ,Tree_MONITOR };
typedef std::map<std::string, bool> TreeNodeRightMap;
class WTreeNode : public WCompositeWidget
{
  //MOC: W_OBJECT WTreeNode:WCompositeWidget
  W_OBJECT;

public:
	//bDevice 最后一层是设备。

  WTreeNode(const std::string labelText, const std::string nodeId, bool bCheck, bool bDevice,
	  int nType,    WText::Formatting labelFormatting,
	    WStateIcon *labelIcon, WWidget *userContent,
	    WContainerWidget *parent = 0);
  
  void addChildNode(WTreeNode *node);
  void removeChildNode(WTreeNode *node);
  const std::vector<WTreeNode *>& childNodes() const { return childNodes_; }

  const WStateIcon* getLabelIcon() const {return labelIcon_;}

  const std::vector<std::string>& findDeviceImage(std::string type)
  {
	  std::map<std::string , std::vector<std::string> >::iterator it = deveiceImg.find(type);
	  if (it != deveiceImg.end())
	  {
		  return (*it).second;
	  }else
	  {
		  return (* deveiceImg.find("_default")).second;
	  }
  }

  void SetTreeCheck(bool bNodeCheck);

  TreeNodeRightMap  m_TreeNodeRightMap;
  WCheckBox        *treeCheckBox_;//2006-4-20 new add
  std::string strId;
  CCheckBoxTreeView *m_CheckBoxTreeView;
  WStateIcon               *expandIcon_;
  int nTreeType;
  bool bMExpand;//当是设备节点时 ，第一次展开 bMExpand = true; 以后bMExpand =false;
  WTable                   *layout_;
  bool bUserMg;// 是否是用户管理的树
public static_slots:
  //MOC: STATIC SLOT WTreeNode::collapse()
  void collapse();

  //MOC: STATIC SLOT WTreeNode::expand()
  void expand();

  //MOC: STATIC SLOT WTreeNode::select()
  void select();
public signals:
    //MOC: SIGNAL WTreeNode::addmonitor()
    void addmonitor();

private:
  std::vector<WTreeNode *> childNodes_;
  WTreeNode		   *parentNode_;

  
  
  WImage		   *noExpandIcon_;
  WStateIcon		   *labelIcon_;
  WText			   *labelText_;
  WWidget                  *userContent_;
  WContainerWidget         *expandedContent_;
  
  
  
  bool bFirst;
  bool bFirstadjust;
  bool bFistundoCollapse;//first 因为monitor 异步，所以假设device expandicon 为 +

  void adjustExpandIcon();
  bool isLastChildNode() const;
  void childNodesChanged();

  bool wasCollapsed_;
  bool wasSelected_;//2006-4-20 new add
  void undoCollapse();
  void undoExpand();
  void undoSelect();

  void Selected();
  void UnSelected();

  //void EnumMonitor();

  enum ImageIndex { OPEN = 0, CLOSE = 1 };
  static std::string imageFold_[];

  std::map<std::string,std::vector<std::string> > deveiceImg;
  std::vector<std::string> _win;
  std::vector<std::string> _unix;
  std::vector<std::string> _default;
  
/*  static std::string imageLine_[];
  static std::string imagePlus_[];
  static std::string imageMin_[];
  */
  private slots:
    //MOC: SLOT WTreeNode::OnTreeNodeCheck()
    void OnTreeNodeCheck();
	//MOC: SLOT WTreeNode::OnRightClick()
	void OnRightClick();
};

#endif // WTREENODE_H_

