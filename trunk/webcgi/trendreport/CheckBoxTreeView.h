/*
* Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
*
* See the LICENSE file for terms of use.
*/
// This may look like C code, but it's really -*- C++ -*-
#ifndef DEMO_TREE_LIST
#define DEMO_TREE_LIST

#include <WContainerWidget>
#include <list>
#include <WTable>
#include <vector>
#include <string>
class WText;
class WTable;
class WTreeNode;
class WLineEdit;
class WTreeNode;
class WComboBox;
class WPushButton;
class WTableCell;
class WCheckBox ;

typedef std::map<std::string,  WCheckBox * > TreeRightMap;

class CCheckBoxTreeView : public WTable
{
    //MOC: W_OBJECT CCheckBoxTreeView:WTable
    W_OBJECT;

public:
    friend class WTreeNode;
    //WLineEdit * m_pSelParam;
    CCheckBoxTreeView(WContainerWidget *parent);
    bool InitTree(std::string strFirstNode_="", bool bDevice_ =true,bool bCheck_ =true,bool bMain_=false,std::string strUser_="admin");
    std::string getSelMonitorID() {return m_szSelMonitorID;};
private:
    std::string m_szSelMonitorID;
    WTreeNode * m_pOldSelNode;
private:
	WTable* m_menutable;
	WTable* pRightTbl;//Ȩ���б�
	WTable *pSeRightTbl;
	WTable *pGroupRightTbl;
	WTable *pDeviceRightTbl;
	WTable *pMonitorRightTbl;

	WTable *pAppTbl;
	//��һ�з�SEȨ��
	//�ڶ��з�
	//WComboBox* m_viewlist;  
	WTreeNode * treeroot;
	WTreeNode * pTreeSelNode;
	WPushButton *pApp;
	WPushButton *pAppDec;
	void SetTreeNodeRight(WTreeNode * pNode, bool bDec);
	
	TreeRightMap mseRightMap;
	TreeRightMap mGroupRightMap;
	TreeRightMap mDeviceRightMap;
	TreeRightMap mMonitorRightMap;
	std::vector<std::string >  pUserSelGroupList;
	std::vector<std::string>   pUserTreeGroupList;

	void InitRightCell();
	void ClearRightCellCheck();

	void SetTreeNodeGroupRight(WTreeNode *pNode, bool bChecked );
	WPushButton *pMonitorBtn;
	WTreeNode *pTestNode;
	std::vector<WTreeNode *> nodeVector;
	void GetSelectedItem(std::list<std::string> &itemlist);
	void SelectedItems(std::list<std::string> itemlist);
	//bDevice  �豸�����Ǽ������
	//bCheck   �Ƿ����checkbox
	//bMain   �Ƿ�������
	
	void AddDeviceTreeNode(std::string szDeviceID,  WTreeNode* parentNode);
	WTreeNode *AddGroupTreeNode(std::string szSubGroupID,   WTreeNode* parentNode,bool bhaveCheck= true);

	WTreeNode *makeTreeMap(const std::string name, const std::string id, int nType,WTable *parent, bool clickIsSwitch,  
	bool bTreeCheck,const std::string strIcon1, const std::string strIcon2);  
  WTreeNode *makeTreeFile(const std::string name,  std::string xid, int nType, WTreeNode *parent, bool clickIsSwitch, 
	 bool bhaveCheck, const std::string strIcon1, const std::string strIcon2);

  void AddMontiorInDevice(WTreeNode* pDeviceNode,bool bExpand =false);

  bool bAdmin;

  void PushGroup(std::string strUserGroupRight, std::vector<std::string>& pUserRightVec );
  bool ParserToken(std::vector<std::string >&pTokenList,   const char * pQueryString,char *pSVSeps);


public signals:
    //MOC: EVENT SIGNAL CCheckBoxTreeView::ReportQueryRequest()
    void ReportQueryRequest();
private slots:
private:
  WText * timerText;
  WScrollArea * Scrolltable;
  WTreeNode *testMap_;
  int testCount_;


  
  std::string MyAddNode(std::string name, std::string id, std::string type, std::string index);
  void EnumGroup(std::string szIndex, WTreeNode* parentNode,bool bhaveCheck =true);

private:
	bool bDevice;
	bool bCheck;
	bool bMain;
	std::string strFirstNode;
	std::string strUser;

private slots:
    //MOC: SLOT CCheckBoxTreeView::ListMonitorInDevice()
    void ListMonitorInDevice();	
	//MOC: SLOT CCheckBoxTreeView::DoApp1()
	void DoApp1();
	//MOC: SLOT CCheckBoxTreeView::DoAppDec()
	void DoAppDec();
	//MOC: SLOT CCheckBoxTreeView::DoSetAppEnable()
	void DoSetAppEnable();
};

#endif // DEMO_TREE_LIST