// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef WTREENODE_H_
#define WTREENODE_H_

#include "define.h"

#include <WCompositeWidget>
#include <WText>
#include <WCheckBox>
#include <WSVLinkText>

class WStateIcon;
class WTable;
class WImage;
class WSVLinkText;
class DemoTreeList;

class WTreeNode : public WCompositeWidget
{
  //MOC: W_OBJECT WTreeNode:WCompositeWidget
  W_OBJECT;
public:
    WTreeNode(DemoTreeList *pTreeList, string labelText, string nodeId, int nType, int nState,
	    WText::Formatting labelFormatting,
        WStateIcon *labelIcon, WWidget *userContent, 
	    WContainerWidget *parent = 0, string szIDCUser = "default", string szIDCPwd = "localhost");
  
    ~WTreeNode();

	void addChildNode(WTreeNode *node, int nType);
	void removeChildNode(WTreeNode *node);
	void SelItem();
	void unSelItem();	
	void SetCurrentItem();
	void UnSetCurrentItem();
	void ChangeText(string strName);
    void ChangeState(const int &nState);
    const string getText() const {if(labelText_) return labelText_->text(); else return "";} ;
	bool HasChild();  
	const std::vector<WTreeNode *>& childNodes() const { return childNodes_; }

    void UpdateContentText();

	DemoTreeList        * m_pParentTreeView;
	WTreeNode           * parentNode_;
	bool                bSelected;
	bool                bCurrently;

	int                 nTreeType;	

	std::string                 strId;
	std::vector<WTreeNode *>    childNodes_;  
public static_slots:
  //MOC: STATIC SLOT WTreeNode::collapse()
  void collapse();
  //MOC: STATIC SLOT WTreeNode::expand()
  void expand();
private:
    bool                        bFistundoCollapse;//first 因为monitor 异步，所以假设device expandicon 为 +
    string                      m_szFocus;
    string                      m_szIDCUser;
    string                      m_szIDCPwd;
    WTable                    * layout_;
    WStateIcon                * labelIcon_;
    WStateIcon                * expandIcon_;
    WText	                  * labelText_;
    WWidget                   * userContent_;
    WContainerWidget          * expandedContent_;
    WContainerWidget          * expandedDeviceContent_;
    bool                        wasCollapsed_;
    bool                        m_bNoChild;
    enum                        ImageIndex { OPEN = 0, CLOSE = 1 };
    static                      string imageFold_[]; 
    
    void                        adjustExpandIcon();
    void                        childNodesChanged();
    void                        undoCollapse();
    void                        undoExpand(); 
    string                      makeMenuText();
};

#endif // WTREENODE_H_
