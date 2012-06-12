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

#include "CheckBoxTreeView.h"
#include "WTreeNode.h"
#include "WStateIcon.h"
#include "websession.h"
#include "WLength"
#include "WComboBox"
#include "WBreak"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <Algorithm>

#include "../../kennel/svdb/svapi/svapi.h"
#include "../base/basetype.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>
#include <WSVLinkText>

#include <WSlotInstance_>

CCheckBoxTreeView::CCheckBoxTreeView(WContainerWidget *parent)
:WTable(parent),
testCount_(0)
{
    bDevice =true;
    bCheck = true;
    bMain  = false;
    strFirstNode ="";
    m_szSelMonitorID = "";
    strUser ="1";

    pTreeSelNode = NULL;
    m_pOldSelNode = NULL;
    //  this->setStyleClass("t2");
    treeroot = NULL;
    pRightTbl = NULL;



    m_menutable = new WTable((WTableCell*)this->elementAt(0,0));
    m_menutable->decorationStyle().setBackgroundColor(WColor(235 ,244 ,255));
    m_menutable->setStyleClass("widthauto");

    m_menutable->setCellPadding(0);
    m_menutable->setCellSpaceing(0);

    //makeTreeFile("无依靠", "-2", Tree_MONITOR, NULL, false,	
    //    false, "../Images/monitor.gif", "../Images/monitor.gif");

    Scrolltable = new WScrollArea(this->elementAt(0,0));

    //table->resize(WLength(100,WLength::Percentage), 350);
    //table->setStyleClass("t6");
    Scrolltable->setWidget(m_menutable);

    pMonitorBtn = new WPushButton("",this->elementAt(0,0));
    pMonitorBtn->hide();
    WObject::connect(pMonitorBtn,SIGNAL(clicked()),this,SLOT(ListMonitorInDevice()));
	//WObject::connect(pMonitorBtn,SIGNAL(clicked()), "alert('hhhh');SetViewPanelHeight();SetItemPanelHeight();" ,this, SLOT(ListMonitorInDevice()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

}

void CCheckBoxTreeView::ListMonitorInDevice()
{
    //	Sleep(500);
    OutputDebugString("ListMonitorInDevice()\n");
    AddMontiorInDevice(pTestNode,true);

	WebSession::js_af_up = "SetViewPanelHeight();SetItemPanelHeight();";
}

void CCheckBoxTreeView::AddDeviceTreeNode(std::string szDeviceID,  WTreeNode* parentNode)
{

    WTreeNode* pNode;
    OBJECT objDevice = GetEntity(szDeviceID);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE node = GetEntityMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szName = "";

            FindNodeValue(node, "sv_name", szName);

            pNode=makeTreeFile(szName, szDeviceID, Tree_DEVICE, parentNode, false, true, 
               "/Images/cbb-4server.gif", "/Images/cbb-4server.gif");   

            if(bDevice ==true) //树的最后一层是设备
            {
                pNode->expandIcon_->hide();
            }
            else
            {
                if(pNode!=NULL)
                    connect(pNode,SIGNAL(addmonitor()),this, SLOT(ListMonitorInDevice()));			
            }

            //			if(szDeviceID=="1.11")  pTestNode= pNode;
        }
        CloseEntity(objDevice);
    }
}

//bExpand :当点击expand时候执行该程序 bExpand ：true
//程序设置时 bExpand ：false

void CCheckBoxTreeView::AddMontiorInDevice(WTreeNode* pDeviceNode,bool bExpand)
{	
	OutputDebugString("AddMonitorInDevice()\n");
    if(pDeviceNode!=NULL)
    {
        //OutputDebugString("AddMontiorInDevice\n");
        map<int, base_param, less<int> > sortList;
        map<int, base_param, less<int> >::iterator lsItem;
        pDeviceNode->bMExpand=true;
        OBJECT objDevice = GetEntity(pDeviceNode->strId);
        if(objDevice != INVALID_VALUE)
        {
            list<string> lsMonitorID;
            list<string>::iterator lstItem;
            if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
            {
                base_param monitor;
                //nMax = lsMonitorID.size();
                for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                {
                    string szMonitorId = (*lstItem).c_str();
                    OBJECT objMonitor = GetMonitor(szMonitorId);
                    if(objMonitor != INVALID_VALUE)
                    {
                        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
                        if(node != INVALID_VALUE)
                        {
                            string szName = "", szIndex = "";
                            FindNodeValue(node, "sv_name", szName);
                            FindNodeValue(node, "sv_index", szIndex);
                            if(szIndex.empty())
                                szIndex = findIndexByRealID(szMonitorId);
                            monitor.szIndex = szMonitorId;
                            monitor.szName = szName;

                            int nIndex = atoi(szIndex.c_str());
                            lsItem = sortList.find(nIndex);
                            while(lsItem != sortList.end())
                            {
                                //PrintDebugString("be found");
                                //nMax ++;
                                nIndex ++;//= nMax;
                                lsItem = sortList.find(nIndex);
                            }
                            sortList[nIndex] = monitor;
                        }
                        CloseMonitor(objMonitor);
                    }
                }
            }
            CloseEntity(objDevice);			
        }
        for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
        {
            WTreeNode *pNode=makeTreeFile(lsItem->second.szName,lsItem->second.szIndex, Tree_MONITOR, pDeviceNode, false,	
                    true,"/Images/cbb-6application.gif","/Images/cbb-6application.gif");
            if(bExpand)
            {
                if(pDeviceNode->treeCheckBox_->isChecked())
                pNode->treeCheckBox_->setChecked(true);
            }
        }
    }
}

WTreeNode * CCheckBoxTreeView::AddGroupTreeNode(std::string szSubGroupID,   WTreeNode* parentNode,bool bhaveCheck)
{
    WTreeNode * tmpNode=NULL;
    OBJECT  groupnode = GetGroup(szSubGroupID);
    if(groupnode != INVALID_VALUE)
    {
        MAPNODE node = GetGroupMainAttribNode(groupnode);
        if(node != INVALID_VALUE)
        {
            string szName = "";

            FindNodeValue(node, "sv_name", szName);
            tmpNode = makeTreeFile(szName, szSubGroupID, Tree_GROUP, parentNode,false, bhaveCheck,  
                "/Images/cbb-3group.gif", "/Images/cbb-3group.gif"); 

        }
        CloseGroup(groupnode);
    }
    return tmpNode;

}

//递归以初始化树

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCheckBoxTreeView::EnumGroup(std::string szIndex, WTreeNode* parentNode, bool bhaveCheck )
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    WTreeNode *tmpNode;
    vector<string >::iterator iSelItor;

    if(!szIndex.empty())
    {
        OBJECT group = GetGroup(szIndex);
        if(group != INVALID_VALUE)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param group;
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    bool bSelTree =true;// 是否增加组或者设备到树上
                    if(!bAdmin)
                    {
                        iSelItor =find(pUserTreeGroupList.begin(),pUserTreeGroupList.end(),szSubGroupID);
                        if(iSelItor ==pUserTreeGroupList.end())
                            bSelTree= false;
                    }
                    if(bSelTree)
                    {
                        OBJECT objGroup = GetGroup(szSubGroupID);
                        if(objGroup != INVALID_VALUE)
                        {
                            MAPNODE node = GetGroupMainAttribNode(objGroup);
                            if(node != INVALID_VALUE)
                            {
                                string szName = "", szIndex = "";
                                //FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    szIndex = findIndexByRealID(szSubGroupID);
                                group.szIndex = szSubGroupID;
                                group.szName = szName;
                                int nIndex = atoi(szIndex.c_str());
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

                    bool bTreehaveCheck=true;
                    if(bhaveCheck)
                        bTreehaveCheck =true;
                    else
                    {
                        iSelItor =find(pUserSelGroupList.begin(),pUserSelGroupList.end(), lsItem->second.szIndex);
                        if(iSelItor ==pUserSelGroupList.end())
                            bTreehaveCheck= false;
                    }

                    tmpNode=AddGroupTreeNode(lsItem->second.szIndex, parentNode, bTreehaveCheck);
                    if(tmpNode!=NULL)
                        EnumGroup(lsItem->second.szIndex, tmpNode, bTreehaveCheck);
                }
               
            }

            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param device;
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    bool bSelTree =true;// 是否增加组或者设备到树上
                    if(!bAdmin)
                    {
                        iSelItor =find(pUserTreeGroupList.begin(),pUserTreeGroupList.end(),szEntityID);
                        if(iSelItor ==pUserTreeGroupList.end())
                            bSelTree= false;
                    }
                    if(bSelTree)
                    {
                        OBJECT objDevice = GetEntity(szEntityID);
                        if(objDevice != INVALID_VALUE)
                        {
                            MAPNODE node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                string szName = "", szIndex = "";
                                //FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    szIndex = findIndexByRealID(szEntityID);
                                device.szIndex = szEntityID;
                                device.szName = szName;
                                int nIndex = atoi(szIndex.c_str());
                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    //nMax ++;
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = device;
                            }
                            CloseEntity(objDevice);
                        }
                        //AddDeviceTreeNode(szEntityID, parentNode );      
                    }
                } 
                for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                    AddDeviceTreeNode(lsItem->second.szIndex, parentNode);           
            }

            CloseGroup(group);

        }        
    }
}

void CCheckBoxTreeView::PushGroup(std::string strUserGroupRight, vector<string>& pUserRightVec )
{
    //bool bFirst= true;
    std::string  strParent= strUserGroupRight;
    vector<string> ::iterator plistitem;
    while(!IsSVSEID(strParent))
    {

        plistitem= find(pUserRightVec.begin(),pUserRightVec.end(),strParent);
        if(plistitem==pUserRightVec.end())
            pUserRightVec.push_back(strParent);
        strParent= FindParentID(strParent);

    }
    plistitem= find(pUserRightVec.begin(),pUserRightVec.end(),strParent);
    if(plistitem==pUserRightVec.end())
        pUserRightVec.push_back(strParent);


}
bool CCheckBoxTreeView::ParserToken(vector<string >&pTokenList,   const char * pQueryString,char *pSVSeps)
{
    char * token = NULL;
    // duplicate string
    char * cp = strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        if (pSVSeps) // using separators
            token = strtok( pTmp , pSVSeps);
        else // using separators
            return false;
        //token = strtok( pTmp, chDefSeps);
        // every field
        while( token != NULL )
        {
            //triml(token);
            //AddListItem(token);
            pTokenList.push_back(token);
            // next field
            if (pSVSeps)
                token = strtok( NULL , pSVSeps);
            else
                return false;
            //token = strtok( NULL, chDefSeps);
        }
        // free memory
        free(cp);
    }
    return true;
}

void CCheckBoxTreeView::ClearRightCellCheck()
{
    TreeRightMap::iterator lRight;
    for(lRight =mGroupRightMap.begin();lRight !=mGroupRightMap.end();lRight ++)
    {
        WCheckBox *pCheckbox;
        pCheckbox =(WCheckBox *) lRight->second;
        if( pCheckbox->isChecked())
            pCheckbox->setChecked(false);
    }
    for(lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
    {
        WCheckBox *pCheckbox;
        pCheckbox =(WCheckBox *) lRight->second;
        if( pCheckbox->isChecked())
            pCheckbox->setChecked(false);
    }
    for(lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
    {
        OutputDebugString("Tree_DEVICE\n");
        WCheckBox *pCheckbox;
        pCheckbox =(WCheckBox *) lRight->second;
        if( pCheckbox->isChecked())
            pCheckbox->setChecked(false);
    }



}
void CCheckBoxTreeView::InitRightCell()
{

    pRightTbl = new WTable(this->elementAt(0,1));
    pSeRightTbl =  new WTable( pRightTbl->elementAt(0,0));
    pGroupRightTbl= new WTable( pRightTbl->elementAt(1,0));
    pDeviceRightTbl = new WTable( pRightTbl->elementAt(2,0));
    pMonitorRightTbl =new WTable( pRightTbl->elementAt(3,0));
    pAppTbl  = new WTable( pRightTbl->elementAt(4,0));
    for(int i =0;i<pRightTbl->numRows();i++)
        pRightTbl->elementAt(i,0)->setVerticalAlignment(AlignTop);



    std::list<string> keylist;
    int nRightTplIndex;
    GetIniFileKeys("group",keylist,"userright.ini");
    nRightTplIndex =1;
    new WText(GetIniFileString("group", "value", "","userright.ini") ,  pGroupRightTbl->elementAt(0,0));
    pGroupRightTbl->elementAt(0,0)->setStyleClass("t3title");
    for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
    {
        if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
        {
            WCheckBox* pCheckBox= new WCheckBox(GetIniFileString("group", _aRight->c_str(), "","userright.ini"),
                pGroupRightTbl->elementAt(nRightTplIndex++,0));
            connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
            mGroupRightMap[_aRight->c_str()]=  pCheckBox ;
        }

    }
    //--------------------------device--------------------------------------------------------
    GetIniFileKeys("device",keylist,"userright.ini");

    nRightTplIndex =1;
    new WText(GetIniFileString("device", "value", "","userright.ini") ,  pDeviceRightTbl->elementAt(0,0));
    pDeviceRightTbl->elementAt(0,0)->setStyleClass("t3title");
    for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
    {
        if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
        {
            WCheckBox* pCheckBox= new WCheckBox(GetIniFileString("device", _aRight->c_str(), "","userright.ini"),
                pDeviceRightTbl->elementAt(nRightTplIndex++,0));
            connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
            //pCheckBox->disable();
            mDeviceRightMap[_aRight->c_str()]=  pCheckBox ;
        }
    }

    //---------------------------monitor---------------------------------------------------------------
    GetIniFileKeys("monitor",keylist,"userright.ini");
    nRightTplIndex =1;
    new WText(GetIniFileString("monitor", "value", "","userright.ini") ,  pMonitorRightTbl->elementAt(0,0));
    pMonitorRightTbl->elementAt(0,0)->setStyleClass("t3title");
    for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
    {
        if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
        {
            WCheckBox* pCheckBox= new WCheckBox(GetIniFileString("monitor", _aRight->c_str(), "","userright.ini"),
                pMonitorRightTbl->elementAt(nRightTplIndex++,0));
            connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
            mMonitorRightMap[_aRight->c_str()]=  pCheckBox ;
        }

    }
    /*
    //---------------------------se---------------------------------------------------------------
    GetIniFileKeys("seserver",keylist,"userright.ini");
    nRightTplIndex =1;
    new WText(GetIniFileString("seserver", "value", "","userright.ini") ,  pSeRightTbl->elementAt(0,0));
    pSeRightTbl->elementAt(0,0)->setStyleClass("t3title");
    for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
    {
    if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
    {
    WCheckBox* pCheckBox= new WCheckBox(GetIniFileString("seserver", _aRight->c_str(), "","userright.ini"),
    pSeRightTbl->elementAt(nRightTplIndex++,0));
    connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
    mseRightMap[_aRight->c_str()]=  pCheckBox ;
    }

    }
    */

    pApp = new WPushButton("应用",pAppTbl->elementAt(0,0));
    new WText("&nbsp;&nbsp;",pAppTbl->elementAt(0,0));
    pAppDec = new WPushButton("应用包括下级 ",pAppTbl->elementAt(0,0));

    connect(pApp,SIGNAL(clicked()),this,SLOT(DoApp1()));
    connect(pAppDec,SIGNAL(clicked()),this,SLOT(DoAppDec()));
    pApp->disable();
    pAppDec->disable();


}
bool CCheckBoxTreeView::InitTree(std::string strFirstNode_, bool bDevice_ ,bool bCheck_ ,bool bMain_ ,std::string strUser_, 
                                 std::string szSEID)
{
    vector<string >::iterator iSelItor;
	m_pOldSelNode =NULL;

    if(treeroot)
        delete treeroot;

    if (m_menutable)
    {
        while ( m_menutable->numRows() > 1)
        {
            m_menutable->deleteRow(m_menutable->numRows() - 1);
        }
    }
    strFirstNode=strFirstNode_;
    bDevice=bDevice_;
    bCheck=bCheck_;
    bMain=bMain_;
    strUser=strUser_;
    pTreeSelNode =NULL;
    if (bDevice_)  //增加权限table cell
    {
        if(pRightTbl==NULL)
        {
            InitRightCell();
        }
        Scrolltable->resize(WLength(100,WLength::Percentage), 450);
        this->setStyleClass("margin_top");
    }else {
        this->setStyleClass("margin_top");
        Scrolltable->setStyleClass("widthauto");
    }

    int nAdmin = GetIniFileInt(strUser, "nAdmin", -1, "user.ini");
    if(nAdmin==-1)
        bAdmin = false;
    else 
		bAdmin= true;

    if(!bAdmin)
    {
        std::string groupright= GetIniFileString(strUser, "groupright", "", "user.ini");
        ParserToken(pUserSelGroupList,groupright.c_str(),",");
        vector<string>::iterator  result1; 
        for( result1=pUserSelGroupList.begin();result1!=pUserSelGroupList.end();result1++)
            PushGroup(result1->c_str(),pUserTreeGroupList);
    }

    WTreeNode *FistNode;

    {
        OBJECT root = GetSVSE(szSEID);
        list<string> lsGroupID;
        list<string>::iterator lstItem;
        WTreeNode *tmpNode = NULL;

        if(treeroot!=NULL)
        {
            FistNode= makeTreeFile(GetSVSELabel(root), szSEID, Tree_SE, treeroot, false, false,
                 "/Images/cbb-2main.gif", "/Images/cbb-2main.gif");  
        }else{
            FistNode= makeTreeMap(GetSVSELabel(root), szSEID, Tree_SE, m_menutable, false, false,
                "/Images/cbb-2main.gif", "/Images/cbb-2main.gif");  
            treeroot= FistNode;
        }

        if (root != INVALID_VALUE)
        {
            //第一层组
            if(GetSubGroupsIDBySE(root, lsGroupID))
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param group;
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    bool bSelTree = true;// 是否增加组或者设备到树上
                    if(!bAdmin)
                    {
                        iSelItor = find(pUserTreeGroupList.begin(),pUserTreeGroupList.end(),szSubGroupID);
                        if(iSelItor == pUserTreeGroupList.end())
                            bSelTree= false;
					}
                    if(bSelTree)
                    {
                        OBJECT objGroup = GetGroup(szSubGroupID);
                        if(objGroup != INVALID_VALUE)
                        {
                            MAPNODE node = GetGroupMainAttribNode(objGroup);
                            if(node != INVALID_VALUE)
                            {
                                string szName = "", szIndex = "";
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    szIndex = findIndexByRealID(szSubGroupID);
                                group.szIndex = szSubGroupID;
                                group.szName = szName;
                                int nIndex = atoi(szIndex.c_str());
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
                    bool bTreehaveCheck=true;
                    if(bCheck_)
                        bTreehaveCheck =true;
                    else
                    {
                        iSelItor =find(pUserSelGroupList.begin(),pUserSelGroupList.end(), lsItem->second.szIndex);
                        if(iSelItor ==pUserSelGroupList.end())
                            bTreehaveCheck= false;
                    }
                    tmpNode=AddGroupTreeNode(lsItem->second.szIndex, FistNode, bTreehaveCheck);
                    if(tmpNode!=NULL)
                        EnumGroup(lsItem->second.szIndex, tmpNode, bTreehaveCheck);
                }
            }

            if(GetSubEntitysIDBySE(root, lsGroupID))
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param device;
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    bool bSelTree =true;// 是否增加组或者设备到树上
                    if(!bAdmin)
                    {
                        iSelItor =find(pUserTreeGroupList.begin(),pUserTreeGroupList.end(),szEntityID);
                        if(iSelItor ==pUserTreeGroupList.end())
                            bSelTree= false;
                    }
                    if(bSelTree)
                    {
                        OBJECT objDevice = GetEntity(szEntityID);
                        if(objDevice != INVALID_VALUE)
                        {
                            MAPNODE node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                string szName = "", szIndex = "";
                                //FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    szIndex = findIndexByRealID(szEntityID);
                                device.szIndex = szEntityID;
                                device.szName = szName;
                                int nIndex = atoi(szIndex.c_str());
                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    //nMax ++;
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = device;
                            }
                            CloseEntity(objDevice);
                        }
                        //AddDeviceTreeNode(szEntityID, parentNode );      
                    }
                } 
                for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                    AddDeviceTreeNode(lsItem->second.szIndex, FistNode); 
            }
            CloseSVSE(root);
        }
    }
	
	makeTreeFile("无依靠", "-2", Tree_MONITOR, FistNode, false,	 false, "/Images/cbb-6application.gif","/Images/cbb-6application.gif");

    return true;
}

//生成树节点
WTreeNode *CCheckBoxTreeView::makeTreeMap(const std::string name, const std::string id, int nType, WTable *parent, bool clickIsSwitch, bool bTreeCheck,
                                          const std::string strIcon1, const std::string strIcon2)
{
    WStateIcon *labelIcon = new WStateIcon(strIcon1, strIcon2, clickIsSwitch);

    //放树控件到一个表格中
    WTreeNode *node = new WTreeNode(name, id, bTreeCheck,bDevice, nType, WText::PlainFormatting, labelIcon, 0);
    parent->elementAt(0,0)->addWidget(node);
    parent->elementAt(0,0)->setVerticalAlignment(AlignTop);

    nodeVector.push_back(node);

    return node;
}

//生成树节点
WTreeNode *CCheckBoxTreeView::makeTreeFile(const std::string name,  std::string xid, int nType, WTreeNode *parent, bool clickIsSwitch, bool bhaveCheck,
                                           const std::string strIcon1, const std::string strIcon2)
{
    WStateIcon *labelIcon = new WStateIcon(strIcon1, strIcon2, clickIsSwitch);
    if(bCheck== false) 
		bhaveCheck= false;
    WTreeNode *node = new WTreeNode(name, xid, bhaveCheck,bDevice, nType, WText::XHMTLFormatting, labelIcon, 0);
    node->m_CheckBoxTreeView=(CCheckBoxTreeView *)this;
    if (parent)
    {
        parent->addChildNode(node);
        nodeVector.push_back(node);
    }
    return node;
}

void CCheckBoxTreeView::SetTreeNodeRight(WTreeNode *pNode, bool bChecked )
{
    //std::string  strSelId;
    if(m_pOldSelNode)
        m_pOldSelNode->UnSelItem();
    m_szSelMonitorID =pNode->strId;
    pNode->SelItem();
    m_pOldSelNode = pNode;
	//WebSession::js_af_up="alert('";
	//WebSession::js_af_up+=strSelId;
	//WebSession::js_af_up+="');";
}

//读出选中节点的strNodeId
void CCheckBoxTreeView::GetSelectedItem(std::list<std::string> &itemlist)
{
	for(unsigned i = 0; i < nodeVector.size(); ++i)
	{
		if(nodeVector[i]->treeCheckBox_->isChecked())
			itemlist.push_back(nodeVector[i]->strId);
	}
}

//选中指定的节点
void CCheckBoxTreeView::SelectedItems(std::list<std::string> itemlist)
{
	std::list<string>::iterator keyitem;
	for(keyitem = itemlist.begin(); keyitem != itemlist.end(); keyitem ++)	
	{
		for(unsigned i = 0; i < nodeVector.size(); ++i)
		{
			if(nodeVector[i]->strId == (*keyitem).c_str())
				nodeVector[i]->treeCheckBox_ ->setChecked();
		}
	}
}

//测试用的函数
std::string CCheckBoxTreeView::MyAddNode(std::string name, std::string id, std::string type, std::string index)
{
	std::string strTmp = "";	
	
	OBJECT root;	
	if(type == "1")
		root = CreateGroup();
	else
		root = CreateEntity();
	
	if (root != INVALID_VALUE)
	{
		MAPNODE attr;
		if(type == "1")
			attr = GetGroupMainAttribNode(root);
		else
			attr = GetEntityMainAttribNode(root);


		bool bState = false;
		if(attr != INVALID_VALUE)
		{
			if(AddNodeAttrib(attr, "sv_id", id))
			{
				if(AddNodeAttrib(attr, "sv_type", type))
				{
					bState = AddNodeAttrib(attr, "sv_name", name);
				}
			}
		}
		
		if(bState)
		{
			if(type == "1")
				strTmp = AddNewGroup(root, index);
			else
				strTmp = AddNewEntity(root, index);
		}

		if(type == "1")
			CloseGroup(root);
		else
			CloseEntity(root);			
	}

	return strTmp;
}

void CCheckBoxTreeView::SetTreeNodeGroupRight(WTreeNode * pNode, bool bDec)
{
	


}
void CCheckBoxTreeView::DoApp1()
{

	
}
void CCheckBoxTreeView::DoAppDec()
{

}
void CCheckBoxTreeView::DoSetAppEnable()
{

}
