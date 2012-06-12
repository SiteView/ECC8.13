/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
// This may look like C code, but it's really -*- C++ -*-
#ifndef DEMO_TREE_LIST
#define DEMO_TREE_LIST

#include "define.h"

#include "../userright/user.h"
#include "../group/resstring.h"

#include <WContainerWidget>
class WText;
class WTable;
class WTreeNode;
class WLineEdit;
class WTreeNode;
class WComboBox;
class WPushButton;
class SVGroupview;
class WApplication;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void wmain1(int argc, char *argv[]);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DemoTreeList : public WContainerWidget
{
    //MOC: W_OBJECT DemoTreeList:WContainerWidget
    W_OBJECT;
public:
    DemoTreeList(WContainerWidget *parent);
    ~DemoTreeList();
    virtual void refresh();
private:
    WTreeNode * AddGroupTreeNode(string szSubGroupID, WTreeNode* parentNode);
	WTreeNode * GetNodeById(string strId);
    WTreeNode * makeTreeFile(string name, string xid, int nType, WTreeNode *parent, string strIcon1, string strIcon2);
    WTreeNode * makeTreeMap(string name, string id, int nType, WTable *parent, string strIcon1, string strIcon2); 

    void        AddJsParam(string name, string value);
    void        AddDeviceTreeNode(string szDeviceID,  WTreeNode * parentNode);
    void        DelTreeNode(WTreeNode* pNode, bool bSort = false);
    void        DelSVSE(string &szIndex);
    void        DelGroup(string &szIndex);
    void        DelDevice(string &szIndex);
    void        EnumGroup(string szIndex, WTreeNode* parentNode = NULL);
    void        UpdateSubGroupState(WTreeNode *pNode, int nState);

    bool        IsCanPaste();
    bool        InitTree();
    bool        SrcIsNetwork(int &nMonitorCount);

    string      copyDevice(string &szGroupID);
    string      getResizeObjectID() {return m_szObjID;};
public signals:
    //MOC: EVENT SIGNAL DemoTreeList::MenuItemRequest(MENU_REQUEST)
    void MenuItemRequest(MENU_REQUEST request);
private slots:
    //MOC: SLOT DemoTreeList::SelNode()
    void SelNode();
    //MOC: SLOT DemoTreeList::RunMenu()
    void RunMenu();
    //MOC: SLOT DemoTreeList::MenuItemResponseProc(MENU_RESPONSE)
    void MenuItemResponseProc(MENU_RESPONSE response);
    //MOC: SLOT DemoTreeList::changeSelNode(string)
    void changeSelNode(string szIndex);
    //MOC: SLOT DemoTreeList::delConfirm()
    void delConfirm();
    //MOC: SLOT DemoTreeList::InPhaseView()
    void InPhaseView();
	//MOC: SLOT DemoTreeList::ExChangeRefresh()
	void ExChangeRefresh();
private:
    vector<WTreeNode *>         nodeVector;
    WTable                    * m_pMenutable;    
    SVGroupview               * m_pGroupview;
	WTreeNode                 * treeroot;
	WPushButton               * m_pAddMapButton_;
	WPushButton               * m_pRemoveMapButton_;
    WPushButton               * m_pDelConform;
	WLineEdit                 * m_pCurIdEdit_;
	WLineEdit                 * m_pCurTypeEdit_;
	WLineEdit                 * m_pCurOprCodeEdit_;
	WLineEdit                 * m_pCurFocusEdit_;

    bool                        m_bConfirm;
    bool                        m_bFirstLoad;

    string                      m_szUserID;
    string                      m_szNoChild;
    string                      m_szIDCUser;
    string                      m_szIDCPwd;
    string                      m_szObjID;
    string                      m_szQueryID;
    string                      m_szSrcDeviceID;

    CUser                     * m_pSVUser;
    SVResString                 m_ResString;
    
    friend   void               wmain1(int argc, char *argv[]);
    friend   class              WTreeNode;
public:
	WApplication *  appSelf;
};

#endif // DEMO_TREE_LIST