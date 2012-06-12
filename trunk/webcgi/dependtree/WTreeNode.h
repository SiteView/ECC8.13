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
	//bDevice ���һ�����豸��
  WTreeNode(const std::string labelText, const std::string nodeId, bool bCheck, bool bDevice,
	  int nType,    WText::Formatting labelFormatting,
	    WStateIcon *labelIcon, WWidget *userContent,
	    WContainerWidget *parent = 0);
  
  void addChildNode(WTreeNode *node);
  void removeChildNode(WTreeNode *node);
  const std::vector<WTreeNode *>& childNodes() const { return childNodes_; }

  void SetTreeCheck(bool bNodeCheck);
  
  void SelItem();
  void UnSelItem();
  TreeNodeRightMap  m_TreeNodeRightMap;
  WCheckBox        *treeCheckBox_;//2006-4-20 new add
  std::string strId;
  CCheckBoxTreeView *m_CheckBoxTreeView;
  WStateIcon               *expandIcon_;
  int nTreeType;
  bool bMExpand;//�����豸�ڵ�ʱ ����һ��չ�� bMExpand = true; �Ժ�bMExpand =false;
  WTable                   *layout_;
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
  bool bFistundoCollapse;//first ��Ϊmonitor �첽�����Լ���device expandicon Ϊ +

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

