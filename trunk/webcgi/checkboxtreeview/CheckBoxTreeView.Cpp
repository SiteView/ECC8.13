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
  strUser ="1";

  pTreeSelNode = NULL;
//  this->setStyleClass("t2");
  pRightTbl =NULL;

  

  m_menutable = new WTable((WTableCell*)this->elementAt(0,0));
  m_menutable->decorationStyle().setBackgroundColor(WColor(235 ,244 ,255));
  m_menutable->setStyleClass("widthauto");
  
  m_menutable->setCellPadding(0);
  m_menutable->setCellSpaceing(0);

   Scrolltable = new WScrollArea(this->elementAt(0,0));
  
  //table->resize(WLength(100,WLength::Percentage), 350);
  //table->setStyleClass("t6");
  Scrolltable->setWidget(m_menutable);
  
  pMonitorBtn = new WPushButton("",this->elementAt(0,0));
  pMonitorBtn->hide();
  WObject::connect(pMonitorBtn,SIGNAL(clicked()),this,SLOT(ListMonitorInDevice()));


}

void CCheckBoxTreeView::ListMonitorInDevice()
{
//	Sleep(500);
	//OutputDebugString("ListMonitorInDevice()\n");
	AddMontiorInDevice(pTestNode,true);
}
 const char*  CCheckBoxTreeView::findIndexByRealID(string &szRealID)
{
    const char* pPos = strrchr(szRealID.c_str(), '.');
    if(pPos && *(pPos + 1) != '\0')
        return pPos + 1;
    else
        return "";
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
			string szType = "";
			
            FindNodeValue(node, "sv_name", szName);
			FindNodeValue(node, "sv_devicetype",szType);
			
			pNode=makeTreeFile(szName, szDeviceID, Tree_DEVICE, parentNode, false, true, 
								  "/Images/cbb-4server.gif", "/Images/cbb-4server.gif");    

			if (pNode != NULL)
			{
				std::vector<std::string> list = pNode->findDeviceImage(szType);
				pNode->getLabelIcon()->icon1()->setImageRef(list[0]);
				pNode->getLabelIcon()->icon2()->setImageRef(list[0]);
			}


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
	if(pDeviceNode!=NULL)
	{
		//OutputDebugString("AddMontiorInDevice\n");
		pDeviceNode->bMExpand=true;
		OBJECT objDevice = GetEntity(pDeviceNode->strId);
        if(objDevice != INVALID_VALUE)
        {
            list<string> lsMonitorID;
            list<string>::iterator lstItem;
            if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
            {
				
                for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                {
                    string szMonitorId = (*lstItem).c_str();
                    OBJECT objMonitor = GetMonitor(szMonitorId);
                    if(objMonitor != INVALID_VALUE)
                    {
                        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
                        if(node != INVALID_VALUE)
                        {
                            string szName = "";
                            FindNodeValue(node, "sv_name", szName);
							
						    WTreeNode *pNode=makeTreeFile(szName,szMonitorId,Tree_MONITOR,pDeviceNode,false,	
							true,"/Images/cbb-6application.gif","/Images/cbb-6application.gif");
							if(bExpand)
							{
								if(pDeviceNode->treeCheckBox_->isChecked())
									pNode->treeCheckBox_->setChecked(true);
							}	
                        }
                        CloseMonitor(objMonitor);
                    }
                }
            }
            CloseEntity(objDevice);			
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
			
            //printf("-------- group name -----------\n%s\n", szName.c_str());

			//构造树节点。。。	
			//GetParentTreeNode()．．．
			//MakeTreeFileNode
			//构造树节点。。。	
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
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
				int nMax = 0;
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
						bool bTreehaveCheck=true;
						if(bhaveCheck)
							bTreehaveCheck =true;
						else
						{
							iSelItor =find(pUserSelGroupList.begin(),pUserSelGroupList.end(),szSubGroupID);
							if(iSelItor ==pUserSelGroupList.end())
								bTreehaveCheck= false;
						}
						OBJECT objGroup = GetGroup(szSubGroupID );
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
								group.bTreehaveCheck =bTreehaveCheck;
                                int nIndex = atoi(szIndex.c_str());
                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nMax ++;
                                    nIndex = nMax;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = group;
                            }
                            CloseGroup(objGroup);
						}

/*						tmpNode=AddGroupTreeNode(szSubGroupID,parentNode,bTreehaveCheck);
						if(tmpNode!=NULL)
							EnumGroup(szSubGroupID,tmpNode,bTreehaveCheck);
*/					}
                }
				for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                {
					
                    tmpNode=AddGroupTreeNode(lsItem->second.szIndex,parentNode,lsItem->second.bTreehaveCheck);
					if(tmpNode!=NULL)
								EnumGroup(lsItem->second.szIndex,tmpNode,lsItem->second.bTreehaveCheck);
                }
            }

			///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
			
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
				int nMax = 0;
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
//						AddDeviceTreeNode(szEntityID,parentNode );      
						OBJECT objDevice = GetEntity(szEntityID );
                        if(objDevice != INVALID_VALUE)
                        {
                            MAPNODE node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                string szName = "", szIndex = "";
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    szIndex = findIndexByRealID(szEntityID);
                                device.szIndex = szEntityID;
                                device.szName = szName;
                                int nIndex = atoi(szIndex.c_str());
                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nMax ++;
                                    nIndex = nMax;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = device;
                            }
                            CloseEntity(objDevice);
                        }

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

	//
	//string strMySiteView,strDummyGroup,strMonitor,strOverallView,strTreeView,strTuop,strTuop1;
	//string strAlert,strAddAlert,strDeleteAlert,strEditAlert,strAlertLog,strReport,strTrendReport;
	//string strMonitorReport,strAddReport,strDeleteReport,strEditReport,strTopnReport,strSetting,strFounditionSet;
	//string strUserManager,strEmailSet,strSMSSet,strSEServer,strAddSEServer,strDeleteSEServer,strEditSEServer;
	//string strManagerGroup,strEditGroup,strDeleteGroup,strAddSubGroup,strAddDevice,strRefresh,strManagerDevice;
	//string strEditDevice,strDeleteDevice,strCopyDevice,strManagerMonitor,strAddMonitor,strEditMonitor,strDeleteMonitor;
	
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			//FindNodeValue(ResNode,"IDS_Right_My_SiteView",strMySiteView);
			//FindNodeValue(ResNode,"IDS_Right_DummyGroup",strDummyGroup);
			//FindNodeValue(ResNode,"IDS_Right_Monitor",strMonitor);
			//FindNodeValue(ResNode,"IDS_Right_OverallView",strOverallView);
			//FindNodeValue(ResNode,"IDS_Right_TreeView",strTreeView);
			//FindNodeValue(ResNode,"IDS_Right_Tuop",strTuop);
			//FindNodeValue(ResNode,"IDS_Right_Tuop",strTuop1);
			//FindNodeValue(ResNode,"IDS_Right_Alert",strAlert);
			//FindNodeValue(ResNode,"IDS_Right_AddAlert",strAddAlert);
			//FindNodeValue(ResNode,"IDS_Right_DeleteAlert",strDeleteAlert);
			//FindNodeValue(ResNode,"IDS_Right_EditAlert",strEditAlert);
			//FindNodeValue(ResNode,"IDS_Right_AlertLog",strAlertLog);
			//FindNodeValue(ResNode,"IDS_Right_Report",strReport);
			//FindNodeValue(ResNode,"IDS_Right_TrendReport",strTrendReport);
			//FindNodeValue(ResNode,"IDS_Right_MonitorReport",strMonitorReport);
			//FindNodeValue(ResNode,"IDS_Right_AddReport",strAddReport);
			//FindNodeValue(ResNode,"IDS_Right_DeleteReport",strDeleteReport);
			//FindNodeValue(ResNode,"IDS_Right_EditReport",strEditReport);
			//FindNodeValue(ResNode,"IDS_Right_TopnReport",strTopnReport);
			//FindNodeValue(ResNode,"IDS_Right_Setting",strSetting);
			//FindNodeValue(ResNode,"IDS_Right_FounditionSet",strFounditionSet);
			//FindNodeValue(ResNode,"IDS_Right_UserManager",strUserManager);
			//FindNodeValue(ResNode,"IDS_Right_EmailSet",strEmailSet);
			//FindNodeValue(ResNode,"IDS_Right_SMSSet",strSMSSet);
			//FindNodeValue(ResNode,"IDS_Right_SEServer",strSEServer);
			//FindNodeValue(ResNode,"IDS_Right_AddSEServer",strAddSEServer);
			//FindNodeValue(ResNode,"IDS_Right_DeleteSEServer",strDeleteSEServer);
			//FindNodeValue(ResNode,"IDS_Right_EditSEServer",strEditSEServer);
			//FindNodeValue(ResNode,"IDS_Right_ManagerGroup",strManagerGroup);
			//FindNodeValue(ResNode,"IDS_Right_EditGroup",strEditGroup);
			//FindNodeValue(ResNode,"IDS_Right_DeleteGroup",strDeleteGroup);
			//FindNodeValue(ResNode,"IDS_Right_AddSubGroup",strAddSubGroup);
			//FindNodeValue(ResNode,"IDS_Right_AddDevice",strAddDevice);
			//FindNodeValue(ResNode,"IDS_Right_Refresh",strRefresh);
			//FindNodeValue(ResNode,"IDS_Right_ManagerDevice",strManagerDevice);
			//FindNodeValue(ResNode,"IDS_Right_AddDevice",strAddDevice);
			//FindNodeValue(ResNode,"IDS_Right_EditDevice",strEditDevice);
			//FindNodeValue(ResNode,"IDS_Right_DeleteDevice",strDeleteDevice);
			//FindNodeValue(ResNode,"IDS_Right_CopyDevice",strCopyDevice);
			//FindNodeValue(ResNode,"IDS_Right_ManagerMonitor",strManagerMonitor);
			//FindNodeValue(ResNode,"IDS_Right_AddMonitor",strAddMonitor);
			//FindNodeValue(ResNode,"IDS_Right_EditMonitor",strEditMonitor);
			//FindNodeValue(ResNode,"IDS_Right_DeleteMonitor",strDeleteMonitor);

			string strTmp;
			string strTmpValue;
			{	
				std::list<string> keylist;
				int nRightTplIndex;
				GetIniFileKeys("group",keylist,"userright.ini");
				nRightTplIndex =1;
				strTmp = GetIniFileString("group", "value", "","userright.ini");
				FindNodeValue(ResNode, strTmp, strTmpValue);
				new WText(strTmpValue,  pGroupRightTbl->elementAt(0,0));
				pGroupRightTbl->elementAt(0,0)->setStyleClass("t3title");
				for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
				{
					if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
					{
						strTmp = GetIniFileString("group", _aRight->c_str(), "","userright.ini");
						FindNodeValue(ResNode, strTmp, strTmpValue);
						WCheckBox* pCheckBox= new WCheckBox(strTmpValue, pGroupRightTbl->elementAt(nRightTplIndex++,0));
						connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
						mGroupRightMap[_aRight->c_str()]=  pCheckBox ;
					}
					
				}
				//--------------------------device--------------------------------------------------------
				GetIniFileKeys("device",keylist,"userright.ini");
				
				nRightTplIndex =1;
				strTmp = GetIniFileString("device", "value", "","userright.ini");
				FindNodeValue(ResNode, strTmp, strTmpValue);
				new WText(strTmpValue,  pDeviceRightTbl->elementAt(0,0));
				pDeviceRightTbl->elementAt(0,0)->setStyleClass("t3title");
				for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
				{
					if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
					{
						strTmp = GetIniFileString("device", _aRight->c_str(), "","userright.ini");
						FindNodeValue(ResNode, strTmp, strTmpValue);
						WCheckBox* pCheckBox= new WCheckBox(strTmpValue, pDeviceRightTbl->elementAt(nRightTplIndex++,0));
						connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
						//pCheckBox->disable();
						mDeviceRightMap[_aRight->c_str()]=  pCheckBox ;
					}
				}

				//---------------------------monitor---------------------------------------------------------------
				GetIniFileKeys("monitor",keylist,"userright.ini");
				nRightTplIndex =1;
				strTmp = GetIniFileString("monitor", "value", "","userright.ini");
				FindNodeValue(ResNode, strTmp, strTmpValue);
				new WText(strTmpValue,  pMonitorRightTbl->elementAt(0,0));
				pMonitorRightTbl->elementAt(0,0)->setStyleClass("t3title");
				for( list<std::string >::iterator _aRight = keylist.begin(); _aRight != keylist.end(); _aRight ++)
				{
					if ( (_aRight->compare("value")!=0)&&(_aRight->compare("sort")!=0) )
					{
						strTmp = GetIniFileString("monitor", _aRight->c_str(), "","userright.ini");
						FindNodeValue(ResNode, strTmp, strTmpValue);
						WCheckBox* pCheckBox= new WCheckBox(strTmpValue, pMonitorRightTbl->elementAt(nRightTplIndex++,0));
						connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable()));
						mMonitorRightMap[_aRight->c_str()]=  pCheckBox ;
					}
					
				}
			}				
		}
		CloseResource(objRes);	
	}
	//WCheckBox* pCheckBox;
	////管理SE服务器 seserver strSEServer se_addse strAddSEServer se_delse strDeleteSEServe se_edit strEditSEServer 6
	//
	//
 //   //管理组 group strManagerGroup editgroup strEditGroup delgroup strDeleteGroup addsongroup strAddSubGroup grouprefresh strRefresh 7
	//new WText(strManagerGroup ,  pGroupRightTbl->elementAt(0,0));
	//pGroupRightTbl->elementAt(0,0)->setStyleClass("t3title");

	//pCheckBox = new WCheckBox(strEditGroup,	pGroupRightTbl->elementAt(2, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["editgroup"] = pCheckBox;

	//pCheckBox = new WCheckBox(strDeleteGroup, pGroupRightTbl->elementAt(3, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["delgroup"] = pCheckBox;

	//pCheckBox = new WCheckBox(strAddSubGroup, pGroupRightTbl->elementAt(4, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["addsongroup"] = pCheckBox;

	//pCheckBox = new WCheckBox(strRefresh, pGroupRightTbl->elementAt(5, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["grouprefresh"] = pCheckBox;

	////管理应用设备 device strManagerDevice adddevice strAddDevice editdevice strEditDevice deldevice strDeleteDevice copydevice strCopyDevice devicerefresh strRefresh 8
	//new WText(strManagerDevice ,  pDeviceRightTbl->elementAt(0,0));
	//pDeviceRightTbl->elementAt(0,0)->setStyleClass("t3title");

	//pCheckBox = new WCheckBox(strAddDevice,	pDeviceRightTbl->elementAt(2, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["adddevice"] = pCheckBox;

	//pCheckBox = new WCheckBox(strEditDevice, pDeviceRightTbl->elementAt(3, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["editdevice"] = pCheckBox;

	//pCheckBox = new WCheckBox(strDeleteDevice, pDeviceRightTbl->elementAt(4, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["deldevice"] = pCheckBox;

	//pCheckBox = new WCheckBox(strCopyDevice, pDeviceRightTbl->elementAt(5, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["copydevice"] = pCheckBox;

	//pCheckBox = new WCheckBox(strRefresh, pDeviceRightTbl->elementAt(6, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["devicerefresh"] = pCheckBox;

	////管理监测器 monitor strManagerMonitor addmonitor strAddMonitor editmonitor strEditMonitor delmonitor strDeleteMonitor monitorrefresh strRefresh 9
	//new WText(strManagerMonitor, pMonitorRightTbl->elementAt(0,0));
	//pMonitorRightTbl->elementAt(0,0)->setStyleClass("t3title");

	//pCheckBox = new WCheckBox(strAddMonitor, pMonitorRightTbl->elementAt(2, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["addmonitor"] = pCheckBox;

	//pCheckBox = new WCheckBox(strEditMonitor, pMonitorRightTbl->elementAt(3, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["editmonitor"] = pCheckBox;

	//pCheckBox = new WCheckBox(strDeleteMonitor, pMonitorRightTbl->elementAt(4, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["delmonitor"] = pCheckBox;

	//pCheckBox = new WCheckBox(strRefresh, pMonitorRightTbl->elementAt(5, 0));
	//connect(pCheckBox,SIGNAL(clicked()),this,SLOT(DoSetAppEnable())); 
	//mGroupRightMap["monitorrefresh"] = pCheckBox;
	
/*
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
		
	}*/
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
	//从资源文件获取文字
	string szAdhibition,szAdhibitionSelf;
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Adhibition",szAdhibition);
			FindNodeValue(ResNode,"IDS_OnlyAdhibitionSelf",szAdhibitionSelf);
		}
		CloseResource(objRes);
	}

	//pApp = new WPushButton(szAdhibition,pAppTbl->elementAt(0,0));
	pAppTbl->setStyleClass("widthauto");
	pApp    = new WSVButton(pAppTbl->elementAt(0,0), szAdhibition,     "button_bg_m.png", "", false);
	//new WText("&nbsp;&nbsp;",pAppTbl->elementAt(0,0));
	//pAppDec = new WPushButton(szAdhibitionSelf,pAppTbl->elementAt(0,0));
	pAppDec = new WSVButton(pAppTbl->elementAt(0,1), szAdhibitionSelf, "button_bg_m.png", "", false);

	//pApp->disable();

	std::string strTmp = "";
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += "pApp";
	strTmp += "='";
	strTmp += pApp->formName();
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this->elementAt(0,0));
	
	strTmp = "";
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += "pAppDec";
	strTmp += "='";
	strTmp += pAppDec->formName();
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this->elementAt(0,0));
	
	connect(pAppDec,SIGNAL(clicked()),this,SLOT(DoApp1()));
	connect(pApp,SIGNAL(clicked()),this,SLOT(DoAppDec()));
}
bool CCheckBoxTreeView::InitTree(std::string strFirstNode_, bool bDevice_ ,bool bCheck_ ,bool bMain_ ,std::string strUser_ )
{


	
	vector<string >::iterator iSelItor;

	m_menutable->clear();
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
//		Scrolltable->resize(WLength(2000,WLength::Pixel), WLength(100,WLength::Percentage));
	}

//	printf(strUser.c_str());
	int nAdmin = GetIniFileInt(strUser, "nAdmin", -1, "user.ini");
	if(nAdmin == -1)
		bAdmin = false;
	else bAdmin= true;

	if(!bAdmin)
	{
		std::string groupright= GetIniFileString(strUser, "groupright", "", "user.ini");
		ParserToken(pUserSelGroupList,groupright.c_str(),",");
		vector<string>::iterator  result1; 
		for( result1=pUserSelGroupList.begin();result1!=pUserSelGroupList.end();result1++)
			PushGroup(result1->c_str(),pUserTreeGroupList);

	}


	//return true;
	treeroot =NULL;
	PAIRLIST selist;
	GetAllSVSEInfo(selist);
	WTreeNode *FistNode;
	
	if(selist.size()>1)
	{
		FistNode= makeTreeMap("SiteView", "-1", Tree_SEGROUP, m_menutable, false, false,
	   "/Images/cbb-2main.gif", "/Images/cbb-2main.gif");  
  
		treeroot= FistNode;
		treeroot->m_CheckBoxTreeView =this;

	}
	PAIRLIST::iterator iSe;
	for(  iSe= selist.begin();iSe!=selist.end();iSe++)
	{
		OBJECT root = GetSVSE((*iSe).name);
		list<string> lsGroupID;
		list<string>::iterator lstItem;
		WTreeNode *tmpNode = NULL;
		
		if(treeroot!=NULL)
		{
			FistNode= makeTreeFile((*iSe).value,(*iSe).name, Tree_SE, treeroot, false, true,
		 "/Images/cbb-2main.gif", "/Images/cbb-2main.gif");  
	  
		}else{
			FistNode= makeTreeMap((*iSe).value, (*iSe).name, Tree_SE, m_menutable, false, true,
	   "/Images/cbb-2main.gif", "/Images/cbb-2main.gif");  
  
		treeroot= FistNode;

		}
		/*
		for(int i=0; i<200;i++)
		{
			makeTreeFile((*iSe).value,(*iSe).name, Tree_SE, treeroot, false, true,
		"../Images/home.gif", "../Images/home.gif");  
	  
		}
		*/


		if (root != INVALID_VALUE)
		{
			

			//第一层组
			lsGroupID.clear();
			if(GetSubGroupsIDBySE(root, lsGroupID))
			{
				map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
				base_param group;
				int nMax =0;
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
							bool bTreehaveCheck =true ;
							if(bAdmin)
								bTreehaveCheck =true;
							else
							{
								iSelItor =find(pUserSelGroupList.begin(),pUserSelGroupList.end(),szSubGroupID);
								if(iSelItor ==pUserSelGroupList.end())
									bTreehaveCheck= false;
							}
							

							//tmpNode=AddGroupTreeNode(szSubGroupID,FistNode,bTreehaveCheck);
							//if(tmpNode!=NULL)
							//	EnumGroup(szSubGroupID,tmpNode,bTreehaveCheck);

							OBJECT objGroup = GetGroup(szSubGroupID );
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
									group.bTreehaveCheck =bTreehaveCheck;
                                    int nIndex = atoi(szIndex.c_str());
                                    lsItem = sortList.find(nIndex);
                                    while(lsItem != sortList.end())
                                    {
                                        nMax ++;
                                        nIndex = nMax;
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
					
                    tmpNode=AddGroupTreeNode(lsItem->second.szIndex,FistNode,lsItem->second.bTreehaveCheck);
					if(tmpNode!=NULL)
								EnumGroup(lsItem->second.szIndex,tmpNode,lsItem->second.bTreehaveCheck);
                }
			}

			lsGroupID.clear();
			if(GetSubEntitysIDBySE(root, lsGroupID))
			{
		
				int nMax = 0;
				map<int, base_param, less<int> > sortList;
				map<int, base_param, less<int> >::iterator lsItem;
				base_param device;
				
				for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
				{
					string szEntityID =(*lstItem).c_str();

					bool bSelTree =true;// 是否增加组或者设备到树上
					if(!bAdmin)
					{
						iSelItor =find(pUserTreeGroupList.begin(),pUserTreeGroupList.end(),szEntityID);
						if(iSelItor ==pUserTreeGroupList.end())
							bSelTree= false;
						

					}
					if(bSelTree)
					{
						//AddDeviceTreeNode(szEntityID,FistNode );      
						OBJECT objDevice = GetEntity(szEntityID);
                        if(objDevice != INVALID_VALUE)
                        {
                            MAPNODE node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                string szName = "", szIndex = "";
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    szIndex = findIndexByRealID(szEntityID);
                                device.szIndex = szEntityID;
                                device.szName = szName;
                                int nIndex = atoi(szIndex.c_str());
                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nMax ++;
                                    nIndex = nMax;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = device;
                            }
                            CloseEntity(objDevice);
                        }
					}

					
				}
				for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                            AddDeviceTreeNode(lsItem->second.szIndex, FistNode);
			}


			CloseSVSE(root);
		}
	}
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
	node->m_CheckBoxTreeView=(CCheckBoxTreeView *)this;

//	nodeVector.push_back(node);
    
	return node;
}

//生成树节点
WTreeNode *CCheckBoxTreeView::makeTreeFile(const std::string name,  std::string xid, int nType, WTreeNode *parent, bool clickIsSwitch, bool bhaveCheck,
	const std::string strIcon1, const std::string strIcon2)
{
	WStateIcon *labelIcon = new WStateIcon(strIcon1, strIcon2, clickIsSwitch);

	if(bCheck== false) bhaveCheck= false;
	
	WTreeNode *node = new WTreeNode(name, xid, bhaveCheck,bDevice, nType, WText::XHMTLFormatting, labelIcon, 0);
	node->m_CheckBoxTreeView=(CCheckBoxTreeView *)this;
	if (parent)
	{
		parent->addChildNode(node);
//		nodeVector.push_back(node);
	}

	return node;
}

void CCheckBoxTreeView::SetTreeNodeRight(WTreeNode *pNode, bool bChecked )
{
	//if(bChecked)
	//OutputDebugString("SetTreeNodeRight\n");
	if(1)
	{
		if(pTreeSelNode!=NULL)
			pTreeSelNode->layout_->elementAt(0, 1)->setStyleClass("RightTree");

		pTreeSelNode =pNode;
		pTreeSelNode ->layout_->elementAt(0, 1)->setStyleClass("RightTreeactive");

		char aaa[100];
		sprintf(aaa,"--------%s---nTreeType:----------%d\n",pTreeSelNode->strId.c_str(), pTreeSelNode->nTreeType);
		//OutputDebugString(aaa);
		switch(pTreeSelNode->nTreeType)
		{
		case Tree_SEGROUP:
			pSeRightTbl->show();
			pGroupRightTbl->hide();
			pDeviceRightTbl->hide();
			pMonitorRightTbl->hide();
			
			for( TreeRightMap::iterator lRight =mseRightMap.begin();lRight !=mseRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					
					
						pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);
				}else pCheckbox->setChecked(false);

			}
			break;
		case Tree_SE :

			pSeRightTbl->hide();
			pGroupRightTbl->show();
			pDeviceRightTbl->show();
			pMonitorRightTbl->show();

			for( TreeRightMap::iterator lRight =mGroupRightMap.begin();lRight !=mGroupRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					//OutputDebugString("checked");
					
						pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);
				}else pCheckbox->setChecked(false);

			}


			for( TreeRightMap::iterator lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					
						pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);
				}else pCheckbox->setChecked(false);

			}

			for( TreeRightMap::iterator lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
			{
				
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					  
					pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);

				}else{
					char aaa[200];
				     
				     
				      sprintf(aaa," --- %s-- \n ",lRight->first.c_str() );
				      //OutputDebugString(aaa); 
					

					 pCheckbox->setChecked(false);
				}

			}

			break;
		case Tree_GROUP:
			pSeRightTbl->hide();
			pGroupRightTbl->show();
			pDeviceRightTbl->show();
			pMonitorRightTbl->show();

			for( TreeRightMap::iterator lRight =mGroupRightMap.begin();lRight !=mGroupRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					//OutputDebugString("checked");
					
						pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);
				}else pCheckbox->setChecked(false);

			}


			for( TreeRightMap::iterator lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					
						pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);
				}else pCheckbox->setChecked(false);

			}

			for( TreeRightMap::iterator lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
			{
				
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					  
					pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);

				}else{
					char aaa[200];
				     
				     
				      sprintf(aaa," --- %s-- \n ",lRight->first.c_str() );
				      //OutputDebugString(aaa); 
					

					 pCheckbox->setChecked(false);
				}

			}

			break;
		case Tree_DEVICE:
			//OutputDebugString("Tree_DEVICE\n");
			pSeRightTbl->hide();
			pGroupRightTbl->hide();
			pDeviceRightTbl->show();
			pMonitorRightTbl->show();

			for( TreeRightMap::iterator lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
			{
				
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					  
					pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);

				}else{
					char aaa[200];
				     
				     
				      sprintf(aaa," --- %s-- \n ",lRight->first.c_str() );
				      //OutputDebugString(aaa); 
					

					 pCheckbox->setChecked(false);
				}

			}			

			for( TreeRightMap::iterator lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
			{
				
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				if(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)!=pTreeSelNode->m_TreeNodeRightMap.end())
				{
					  
					pCheckbox->setChecked(pTreeSelNode->m_TreeNodeRightMap.find(lRight->first)->second);

				}else{
					char aaa[200];
				     
				     
				      sprintf(aaa," --- %s-- \n ",lRight->first.c_str() );
				      //OutputDebugString(aaa); 
					

					 pCheckbox->setChecked(false);
				}

			}			
			break;
		}
		
		
	}
	//pApp->disable();
	//pAppDec->disable();
	WebSession::js_af_up = "document.all(pApp).disabled = true;";
	WebSession::js_af_up += "document.all(pAppDec).disabled = true;";

}

//读出选中节点的strNodeId
void CCheckBoxTreeView::GetSelectedItem(std::list<std::string> &itemlist)
{
	/*
	for(unsigned i = 0; i < nodeVector.size(); ++i)
	{
		if(nodeVector[i]->treeCheckBox_->isChecked())
			itemlist.push_back(nodeVector[i]->strId);
	}*/

}

//选中指定的节点
void CCheckBoxTreeView::SelectedItems(std::list<std::string> itemlist)
{
	std::list<string>::iterator keyitem;
	/*
	for(keyitem = itemlist.begin(); keyitem != itemlist.end(); keyitem ++)	
	{
		for(unsigned i = 0; i < nodeVector.size(); ++i)
		{
			if(nodeVector[i]->strId == (*keyitem).c_str())
				nodeVector[i]->treeCheckBox_ ->setChecked();
		}
	}
	*/
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
	//OutputDebugString("Tree_GROUP\n");
	TreeRightMap::iterator lRight;
		switch(pNode->nTreeType)
		{
		case Tree_SEGROUP:

			for(lRight =mseRightMap.begin();lRight !=mseRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			break;
			case Tree_SE :
			for(lRight =mGroupRightMap.begin();lRight !=mGroupRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			for(lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			for(lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
			{
				//OutputDebugString("Tree_DEVICE\n");
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			
			
			break;
		case Tree_GROUP:
			
			for(lRight =mGroupRightMap.begin();lRight !=mGroupRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			for(lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
			{
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			
			for(lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
			{
				//OutputDebugString("Tree_DEVICE\n");
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			break;
		case Tree_DEVICE:
			
			for(lRight =mDeviceRightMap.begin();lRight !=mDeviceRightMap.end();lRight ++)
			{
				//OutputDebugString("Tree_DEVICE\n");
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();
			}
			for(lRight =mMonitorRightMap.begin();lRight !=mMonitorRightMap.end();lRight ++)
			{
				//OutputDebugString("Tree_Monitor\n");
				WCheckBox *pCheckbox;
				pCheckbox =(WCheckBox *) lRight->second;
				pNode->m_TreeNodeRightMap[lRight->first.c_str()]= pCheckbox->isChecked();

			}
			break;
		}
		if(bDec&&(Tree_SEGROUP!=pNode->nTreeType))
		{

			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
			{
				SetTreeNodeGroupRight(pNode->childNodes()[i],bDec);
				
			}
		}
	

}
void CCheckBoxTreeView::DoApp1()
{


	
	if(	pTreeSelNode!=NULL)  
		SetTreeNodeGroupRight(pTreeSelNode,false);

	//pApp->disable();
	//pAppDec->disable();
	WebSession::js_af_up = "document.all(pApp).disabled = true;";
	WebSession::js_af_up += "document.all(pAppDec).disabled = true;";

	
}
void CCheckBoxTreeView::DoAppDec()
{
	if(	pTreeSelNode!=NULL)  
		SetTreeNodeGroupRight(pTreeSelNode,true);
	//pApp->disable();
	//pAppDec->disable();
	WebSession::js_af_up = "document.all(pApp).disabled = true;";
	WebSession::js_af_up += "document.all(pAppDec).disabled = true;";

}
void CCheckBoxTreeView::DoSetAppEnable()
{
		//OutputDebugString("DoSetAppEnable\n");
	//pApp->enable();
	//pAppDec->enable();
	WebSession::js_af_up = "document.all(pApp).disabled = false;";
	WebSession::js_af_up += "document.all(pAppDec).disabled = false;";

}
