#include "wholeview.h"
#include "../../opens/libwt/WebSession.h"
#include "../base/basetype.h"
#include "../base/OperateLog.h"
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"

extern void PrintDebugString(const char* szMsg);
extern void PrintDebugString(const string &szMsg);
CSVWholeview::CSVWholeview(WContainerWidget *parent, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szIDCUser = szIDCUser;
    m_szIDCPwd  = szIDCPwd;

    m_szUserID  = "";
    m_bFirstLoad   = true;

    m_pTime     = NULL;
    m_pContent  = NULL;
    m_pSVUser   = NULL;


	//new WText("<div id='view_panel' class='panel_view'>",elementAt(0, 0));

    new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", elementAt(0, 0));


    loadStrings();
    //initForm();
	NewInitForm();


	//new WText("</div>", elementAt(0, 0));

	//AddJsParam("uistyle", "viewpan");
	//AddJsParam("fullstyle", "true");
	//AddJsParam("bGeneral", "false");
	//new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", elementAt(0, 0));

}


//添加客户端脚本变量
void CSVWholeview::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, elementAt(0, 0));
}

void CSVWholeview::loadStrings()
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode, "IDS_Refresh_Time", m_szRefreshTime);
			FindNodeValue(ResNode, "IDS_WHOLE_TREE_VIEW", m_szTitle);
            FindNodeValue(ResNode, "IDS_SE_HAS_NO_CHILD", m_szNoChild);
 			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
       }
        CloseResource(objRes);
    }
}

void CSVWholeview::NewInitForm()
{
    int pRow = numRows();
	//elementAt(pRow, 0)->resize(WLength(90, WLength::Percentage), 0);
	elementAt(pRow, 0)->setContentAlignment(AlignCenter);
	WTable *pSub = new WTable(elementAt(pRow, 0));
	if(pSub)
	{
		//elementAt(pRow, 0)->setStyleClass("padding_top");
		pSub->setStyleClass("padding_top");
		//pSub->setStyleClass("padding_2");
		pSub->resize(WLength(96, WLength::Percentage), 0);

		WText *pTitle = new WText(m_szTitle, pSub->elementAt(0, 0));
		pSub->elementAt(0, 0)->setStyleClass("textbold1");

		m_pTime = new WText("local time", pSub->elementAt(0, 1));
		pSub->elementAt(0, 1)->setContentAlignment(AlignRight | AlignTop);

		//m_pMainTable = new WSVMainTable(elementAt(pRow, 0), m_szTitle, false);
		//m_pTime = new WText("local time", m_pMainTable->GetContentTable()->elementAt(0, 0));
		//m_pMainTable->elementAt(0, 1)->setContentAlignment(AlignRight | AlignTop);

		svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
		string curTime = ttime.Format();
		if(m_pTime)
		{
			m_pTime->setText(m_szRefreshTime + curTime);
		}
	}

	pRow = numRows();
	m_pMainTable = new WSVMainTable(elementAt(pRow, 0), "", false);
	m_pFlexTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1, 0), EntityDes, "");
	m_pContent = new WTable(m_pFlexTable->GetContentTable()->elementAt(1, 0));
	m_pContent->setStyleClass("widthauto");
}

void CSVWholeview::initForm()
{
    //setStyleClass("t8");
    //createTitle();
    //int nRow = numRows();
    //m_pContent = new WTable(elementAt(nRow, 0));
}

void CSVWholeview::createTitle()
{
    //int nRow = numRows();
    //WTable *pSub = new WTable(elementAt(nRow, 0));
    //elementAt(nRow, 0)->setStyleClass("t1title");
    ////m_pContent->elementAt(0, 0)->setStyleClass("t1title");
    //if(pSub)
    //{
    //    pSub->setStyleClass("t3");
    //    nRow = pSub->numRows();
    //    WText *pTitle = new WText(m_szTitle, pSub->elementAt(nRow, 0));
    //    if(pTitle)
    //        pTitle->setStyleClass("tgrouptitle2");

    //    m_pTime  = new WText("local time", pSub->elementAt(nRow, 1));
    //    pSub->elementAt(nRow, 1)->setContentAlignment(AlignRight | AlignTop);
    //    pSub->elementAt(nRow, 1)->setStyleClass("cell_40");
    //    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    //    string curTime = ttime.Format();
    //    if(m_pTime)
    //    {
    //        m_pTime->setStyleClass("tgrouptitle2");
    //        m_pTime->setText(m_szRefreshTime + curTime);
    //    }
    //}
    ////new WText(m_szTitle, elementAt(nRow, 0));
    ////elementAt(nRow, 0)->setStyleClass("t1title");
}

void CSVWholeview::enumSVSE()
{
    if(!m_pContent)
        return;

    PAIRLIST selist;
    string szRootname("");
    int nRow = 0;

    WTable *pTable = m_pContent;
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {       
        sv_pair svpair;
        svpair.name = "1";
        OBJECT objSE = GetSVSE("1");//, m_szIDCUser, m_szIDCPwd);
        if(objSE != INVALID_VALUE)
        {
            svpair.value = GetSVSELabel(objSE);
            CloseSVSE(objSE);
        }        
        selist.push_back(svpair);
    }
    else
    {
        GetAllSVSEInfo(selist);
        szRootname = GetIniFileString("segroup","name","","general.ini");
        if(szRootname.empty())
            szRootname = "SiteView ECC 7.0";        
        nRow = m_pContent->numRows();
        //WImage *pShow = new WImage("../Images/foldopen.gif", m_pContent->elementAt(nRow, 0));
        //WImage *pHide = new WImage("../Images/foldclose.gif", m_pContent->elementAt(nRow, 0));
        WImage *pShow = new WImage("/Images/cb1-unwrap.gif", m_pContent->elementAt(nRow, 0));
        WImage *pHide = new WImage("/Images/cb1-fold.gif", m_pContent->elementAt(nRow, 0));

		new WText("&nbsp;",m_pContent->elementAt(nRow, 0));

        //new WImage("../Images/home.gif", m_pContent->elementAt(nRow, 1));
		new WImage("/Images/cbb-2main.gif", m_pContent->elementAt(nRow, 1));

		new WText("&nbsp;",m_pContent->elementAt(nRow, 1));

        WText *pName = new WText(szRootname, m_pContent->elementAt(nRow, 2));
        if(pName)
        {
            sprintf(pName->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                "this.style.textDecoration=\"underline\"' " \
                "onmouseout='this.style.textDecoration=\"none\"'");
        }
        pTable = new WTable(m_pContent->elementAt(nRow + 1, 2));
		pTable->setStyleClass("widthauto");
        if(!pTable)
            return;
        else
        {
            if(pShow && pHide)
            {
                string szShow = "", szHide = "", szSubTable = "";
                szShow = pHide->formName();
                szHide = pShow->formName();
                szSubTable = pTable->formName();

                string szShowText = "onclick='showsubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='display:none;cursor:pointer'";
                string szHideText = "onclick='hidesubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='cursor:pointer'";
                sprintf(pShow->contextmenu_, szShowText.c_str());
                sprintf(pHide->contextmenu_, szHideText.c_str());            
            }
        }
    }

    PAIRLIST::iterator iSe;
    
    bool bHasRight = true;

    int  nChildCount = 0, nIndex = 0;

    OBJECT objSE = INVALID_VALUE;
    OBJECT objGroup = INVALID_VALUE;
    MAPNODE node = INVALID_VALUE;

    string szSEID(""), szSubGroupID(""), szEntityID("");
    string szName(""), szIndex("");
    string szContext(""), szShow(""), szHide(""), szSubTable("");
    string szShowText(""), szHideText("");

    list<string> lsGroupID;
    list<string> lsDeviceID;
    list<string>::iterator lstItem;

    for(iSe= selist.begin(); iSe!=selist.end(); iSe++)
    {
        szSEID = (*iSe).name;
        bHasRight = true;
        if(m_pSVUser)
            bHasRight = m_pSVUser->haveGroupRight(szSEID, Tree_SE);
        if(bHasRight)
        {
            nRow = pTable->numRows();
            //WImage *pShow = new WImage("../Images/foldopen.gif", pTable->elementAt(nRow, 0));
            //WImage *pHide = new WImage("../Images/foldclose.gif", pTable->elementAt(nRow, 0));
            WImage *pShow = new WImage("/Images/cb1-unwrap.gif", pTable->elementAt(nRow, 0));
            WImage *pHide = new WImage("/Images/cb1-fold.gif", pTable->elementAt(nRow, 0));
           
			new WText("&nbsp;",pTable->elementAt(nRow, 0));

			new WImage("/Images/cbb-2main.gif", pTable->elementAt(nRow, 1));

			new WText("&nbsp;",pTable->elementAt(nRow, 1));

            WText *pName = new WText((*iSe).value, pTable->elementAt(nRow, 2));
            if(pName)
            {
                szContext = "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/menu.exe?cmd=treeview.exe?svseid=" + szSEID 
                    + "\");' style='color:#669;cursor:pointer;' onmouseover='this.style.textDecoration=\"underline\"'"
                    + "onmouseout='this.style.textDecoration=\"none\"'";
                sprintf(pName->contextmenu_, szContext.c_str());
            }
            WTable *pSubTable = new WTable(pTable->elementAt(nRow + 1, 2));
			pSubTable->setStyleClass("widthauto");
            if(!pSubTable)
                return;
            else
            {
                if(pShow && pHide)
                {                    
                    szShow = pHide->formName();
                    szHide = pShow->formName();
                    szSubTable = pSubTable->formName();

                    szShowText = "onclick='showsubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='display:none;cursor:pointer'";
                    szHideText = "onclick='hidesubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='cursor:pointer'";
                    sprintf(pShow->contextmenu_, szShowText.c_str());
                    sprintf(pHide->contextmenu_, szHideText.c_str());            
                }
            }
            
            objSE = GetSVSE(szSEID);
            if(objSE != INVALID_VALUE)
            {
                lsGroupID.clear();
                if(GetSubGroupsIDBySE(objSE, lsGroupID))
			    {
                    map<int, base_param, less<int> > sortList;
                    map<int, base_param, less<int> >::iterator lsItem;
					map<int, base_param, less<int> >::iterator compItem;

                    base_param group;

                    for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                    {
                        szSubGroupID =(*lstItem);
                        bHasRight = true;
                        if(m_pSVUser)
                            bHasRight = m_pSVUser->haveGroupRight(szSubGroupID, Tree_GROUP);
                        if(bHasRight)
                        {
                            objGroup = GetGroup(szSubGroupID, m_szIDCUser, m_szIDCPwd);
                            if(objGroup != INVALID_VALUE)
                            {
                                node = GetGroupMainAttribNode(objGroup);
                                if(node != INVALID_VALUE)
                                {
                                    FindNodeValue(node, "sv_name", szName);
                                    FindNodeValue(node, "sv_index", szIndex);

                                    if(szIndex.empty())
                                        nIndex = FindIndexByID(szSubGroupID);
                                    else
                                        nIndex = atoi(szIndex.c_str());

                                    group.szIndex = szSubGroupID;
                                    group.szName = szName;

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
                    nChildCount += static_cast<int>(sortList.size());

                    for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                    {
						//PrintDebugString("In first setting ---------" + lsItem->second.szName + "\n");
						//bool bbbb = false;
                        nRow = pSubTable->numRows();
					    WImage *pShow = new WImage("/Images/cb1-unwrap.gif", pSubTable->elementAt(nRow, 0));
					    WImage *pHide = new WImage("/Images/cb1-fold.gif", pSubTable->elementAt(nRow, 0));

						new WText("&nbsp;",pSubTable->elementAt(nRow, 0));

						new WImage("/Images/cbb-3group.gif", pSubTable->elementAt(nRow, 1));

						new WText("&nbsp;",pSubTable->elementAt(nRow, 1));

                        WText *pName = new WText(lsItem->second.szName, pSubTable->elementAt(nRow, 2));
                        if(pName)
                        {
                            string szContext = "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/menu.exe?cmd=treeview.exe?groupid=" + lsItem->second.szIndex 
                                + "\");' style='color:#669;cursor:pointer;' onmouseover='this.style.textDecoration=\"underline\"'"
                                + "onmouseout='this.style.textDecoration=\"none\"'";
                            sprintf(pName->contextmenu_, szContext.c_str());
                        }
                        WTable * pSub = new WTable(pSubTable->elementAt(nRow + 1, 2));
                        if(pSub)
                        {                        
                            if(pShow && pHide)
                            {
                                szShow = pHide->formName();
                                szHide = pShow->formName();
                                szSubTable = pSub->formName();

                                string szShowText = "onclick='showsubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='display:none;cursor:pointer'";
                                string szHideText = "onclick='hidesubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='cursor:pointer'";
                                sprintf(pShow->contextmenu_, szShowText.c_str());
                                sprintf(pHide->contextmenu_, szHideText.c_str());            
                            }
                            if(!enumGroups(lsItem->second.szIndex, pSub))
							{
								//bbbb = true;
                                //pSubTable->deleteRow(nRow);
								pShow->hide();
								pHide->hide();

							}
                        }
                    }

                }
                lsDeviceID.clear();
                if(GetSubEntitysIDBySE(objSE, lsDeviceID))
                {
                    map<int, base_param, less<int> > sortList;
                    map<int, base_param, less<int> >::iterator lsItem;
                    base_param device;
                    for(lstItem = lsDeviceID.begin(); lstItem != lsDeviceID.end(); lstItem ++)
                    {
                        szEntityID =(*lstItem);
                        bHasRight = true;
                        if(m_pSVUser)
                            bHasRight = m_pSVUser->haveGroupRight(szEntityID, Tree_DEVICE);
                        if(bHasRight)
                        {
                            OBJECT objDevice = GetEntity(szEntityID, m_szIDCUser, m_szIDCPwd);
                            if(objDevice != INVALID_VALUE)
                            {
                                MAPNODE node = GetEntityMainAttribNode(objDevice);
                                if(node != INVALID_VALUE)
                                {
                                    FindNodeValue(node, "sv_name", szName);
                                    FindNodeValue(node, "sv_index", szIndex);
                                    if(szIndex.empty())
                                        nIndex = FindIndexByID(szEntityID);
                                    else
                                        nIndex = atoi(szIndex.c_str());

                                    device.szIndex = szEntityID;
                                    device.szName = szName;

                                    lsItem = sortList.find(nIndex);
                                    while(lsItem != sortList.end())
                                    {
                                        nIndex ++;
                                        lsItem = sortList.find(nIndex);
                                    }
                                    sortList[nIndex] = device;
                                }
                                CloseEntity(objDevice);
                            }
                        }
                    }
                    nChildCount += static_cast<int>(sortList.size());
                    for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                    {
                        nRow = pSubTable->numRows();

						new WText("&nbsp;",pSubTable->elementAt(nRow , 0));

						new WImage("/Images/cbb-4server.gif", pSubTable->elementAt(nRow, 1));

						new WText("&nbsp;",pSubTable->elementAt(nRow , 1));

                        WText *pName = new WText(lsItem->second.szName, pSubTable->elementAt(nRow, 2));
                        if(pName)
                        {
                            szContext = "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/menu.exe?cmd=treeview.exe?deviceid=" + lsItem->second.szIndex 
                                + "\");' style='color:#669;cursor:pointer;' onmouseover='this.style.textDecoration=\"underline\"'"
                                + "onmouseout='this.style.textDecoration=\"none\"'";
                            sprintf(pName->contextmenu_, szContext.c_str());
                        }
                        if(!enumMonitors(lsItem->second.szIndex, lsItem->second.szName, pSubTable->elementAt(nRow, 2)))
						{
							//pSubTable->deleteRow(nRow);
						}

                    }
                }
                CloseSVSE(objSE);

                if(nChildCount <= 0)
                {
                    new WText(m_szNoChild, pSubTable->elementAt(nRow, 2));
                }
            }
        }
    }
}

bool CSVWholeview::enumGroups(const string &szGroupID, WTable *pTable)
{
    bool bShowGroup = false;
	bool gShowGroup = true;//jansion
	bool mShowGroup = true; //jansion
	pTable->setStyleClass("widthauto");
    if(!szGroupID.empty())
    {     
        OBJECT objGroup = GetGroup(szGroupID);
        if(objGroup != INVALID_VALUE)
        { 
			//PrintDebugString("In ------------------------------------\n");
            string szIndex(""), szName(""), szShowIndex(""), szContext("");
            string szShow(""), szHide(""), szSubTable("");
            string szShowText(""), szHideText("");
            bool bHasRight = true;
            int nIndex = 0, nRow = 0; 
            MAPNODE node = INVALID_VALUE;
            list<string> lsGroupID;
            list<string> lsDeviceID;
            list<string>::iterator lstItem;
			//list<string>::iterator bcompItem;

            if(GetSubGroupsIDByGroup(objGroup, lsGroupID))
            {
				
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
				map<int, base_param, less<int> >::iterator bcompItem;

				//bool gShow = false;

                base_param group;
                OBJECT objSubGroup = INVALID_VALUE;
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
					//PrintDebugString("In --------------- for ---------------------\n");
                    szIndex =(*lstItem);
                    bHasRight = true;
                    if(m_pSVUser)
                        bHasRight = m_pSVUser->haveGroupRight(szIndex, Tree_GROUP);
                    if(bHasRight)
                    {
                        objSubGroup = GetGroup(szIndex, m_szIDCUser, m_szIDCPwd);
                        if(objGroup != INVALID_VALUE)
                        {
                            node = GetGroupMainAttribNode(objSubGroup);
                            if(node != INVALID_VALUE)
                            { 
                                FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szShowIndex);
                                if(szShowIndex.empty())
                                    nIndex = FindIndexByID(szIndex);
                                else
                                    nIndex = atoi(szShowIndex.c_str());
                                group.szIndex = szIndex;
                                group.szName = szName;

                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = group;
                            }							
							else
							{
								gShowGroup = false;
							}
                            CloseGroup(objSubGroup);
                        }
                    }
					else
					{
						gShowGroup =false;
					}
                }

				//if (lsGroupID.empty())
				//	PrintDebugString("In group is ====== false\n");

                for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                {					
					//PrintDebugString("In emnuGroup " + lsItem->second.szName + "\n");

					//bool gShow = false;

                    nRow = pTable->numRows();
                    //WImage *pShow = new WImage("../Images/foldopen.gif", pTable->elementAt(nRow, 0));
                    //WImage *pHide = new WImage("../Images/foldclose.gif", pTable->elementAt(nRow, 0));
					//if(!enumGroups(lsItem->second.szIndex, pSub))
					//{
                    WImage *pShow = new WImage("/Images/cb1-unwrap.gif", pTable->elementAt(nRow, 0));
                    WImage *pHide = new WImage("/Images/cb1-fold.gif", pTable->elementAt(nRow, 0));
					//}


					new WText("&nbsp;",pTable->elementAt(nRow, 0));

                    //new WImage("../Images/group.gif", pTable->elementAt(nRow, 1));
					new WImage("/Images/cbb-3group.gif", pTable->elementAt(nRow, 1));
					new WText("&nbsp;",pTable->elementAt(nRow, 1));

                    WText *pName = new WText(lsItem->second.szName, pTable->elementAt(nRow, 2));
                    if(pName)
                    {
                        szContext = "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/menu.exe?cmd=treeview.exe?groupid=" + lsItem->second.szIndex 
                            + "\");' style='color:#669;cursor:pointer;' onmouseover='this.style.textDecoration=\"underline\"'"
                            + "onmouseout='this.style.textDecoration=\"none\"'";
                        sprintf(pName->contextmenu_, szContext.c_str());
                    }
                    WTable * pSub = new WTable(pTable->elementAt(nRow + 1, 2));
                    if(pSub)
                    {          
                        if(pShow && pHide)
                        {
                            szShow = pHide->formName();
                            szHide = pShow->formName();
                            szSubTable = pSub->formName();

                            szShowText = "onclick='showsubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='display:none;cursor:pointer'";
                            szHideText = "onclick='hidesubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='cursor:pointer'";
                            sprintf(pShow->contextmenu_, szShowText.c_str());
                            sprintf(pHide->contextmenu_, szHideText.c_str());            
                        }

                        if(!enumGroups(lsItem->second.szIndex, pSub))
						{
							//gShow = true;
							//pTable->deleteRow(nRow);
							pShow->hide();
							pHide->hide();
						}
                        else
						{
                            //bShowGroup = true;
							//pShow->hide();
							//pHide->hide();
						}
                    }

                }

				if (sortList.empty())
					gShowGroup = false;

            }
			else
			{
				gShowGroup = false;
			}
            if(GetSubEntitysIDByGroup(objGroup, lsDeviceID))
            {
                map<int, base_param, less<int> > sortList;
                map<int, base_param, less<int> >::iterator lsItem;
                base_param device;
                OBJECT objDevice = INVALID_VALUE;
                for(lstItem = lsDeviceID.begin(); lstItem != lsDeviceID.end(); lstItem ++)
                {
                    szIndex =(*lstItem);
                    bHasRight = true;
                    if(m_pSVUser)
                        bHasRight = m_pSVUser->haveGroupRight(szIndex, Tree_DEVICE);
                    if(bHasRight)
                    {
                        objDevice = GetEntity(szIndex, m_szIDCUser, m_szIDCPwd);
                        if(objDevice != INVALID_VALUE)
                        {
                            node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szShowIndex);
                                if(szShowIndex.empty())
                                    nIndex = FindIndexByID(szIndex);
                                else
                                    nIndex =  atoi(szShowIndex.c_str());
                                device.szIndex = szIndex;
                                device.szName = szName;

                                lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = device;
                            }
							else
							{
								mShowGroup = false;
							}
                            CloseEntity(objDevice);
                        }
                    }
                }
                for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
                {
					//PrintDebugString("In emnuGroup " + lsItem->second.szName + "------------------------\n");
                    nRow = pTable->numRows();
                    //new WImage("../Images/device.gif", pTable->elementAt(nRow, 1));
					new WImage("/Images/cbb-4server.gif", pTable->elementAt(nRow, 1));
					new WText("&nbsp;",pTable->elementAt(nRow, 1));

                    WText *pName = new WText(lsItem->second.szName, pTable->elementAt(nRow, 2));
                    if(pName)
                    {
                        szContext = "onclick='parent.document.frames(\"left\").location.replace(\"/fcgi-bin/menu.exe?cmd=treeview.exe?deviceid=" + lsItem->second.szIndex 
                            + "\");' style='color:#669;cursor:pointer;' onmouseover='this.style.textDecoration=\"underline\"'"
                            + "onmouseout='this.style.textDecoration=\"none\"'";
                        sprintf(pName->contextmenu_, szContext.c_str());
                    }
                    if(!enumMonitors(lsItem->second.szIndex, lsItem->second.szName, pTable->elementAt(nRow, 2)))
					{
						bShowGroup = false;
						//bShowGroup = true;
                        //pTable->deleteRow(nRow);
					}
                    else
                        bShowGroup = true;
                }

				//84200891
				if (sortList.empty())
				{
					mShowGroup = false;
				}

            }
			else
			{
				mShowGroup = false;
			}
            CloseGroup(objGroup);
        }
		else
		{
			mShowGroup = false;
			gShowGroup = false;
		}
    }
	else
	{
		mShowGroup = false;
		gShowGroup = false;
	}

	bool bbShowGroup;
	bbShowGroup = gShowGroup || mShowGroup;
    return bbShowGroup;
}

bool CSVWholeview::enumMonitors(const string &szDeviceID, const string &szDeviceName, WTableCell *pTableCell)
{
    map<int, base_param, less<int> > sortList;
    map<int, base_param, less<int> >::iterator lsItem;

    OBJECT objDevice = GetEntity(szDeviceID,  m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {
            base_param monitor;
            string szMonitorId("");
            OBJECT objMonitor = INVALID_VALUE;
            MAPNODE node = INVALID_VALUE;

            string szName(""), szIndex("");

            int nIndex = 0;
            for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
            {
                szMonitorId = (*lstItem).c_str();
                objMonitor = GetMonitor(szMonitorId, m_szIDCUser, m_szIDCPwd);
                if(objMonitor != INVALID_VALUE)
                {
                    node = GetMonitorMainAttribNode(objMonitor);
                    if(node != INVALID_VALUE)
                    {
                        FindNodeValue(node, "sv_name", szName);
                        FindNodeValue(node, "sv_index", szIndex);
                        if(szIndex.empty())
                            nIndex = FindIndexByID(szMonitorId);
                        else
                            nIndex = atoi(szIndex.c_str());
                        monitor.szIndex = szMonitorId;
                        monitor.szName = szName;

                        lsItem = sortList.find(nIndex);
                        while(lsItem != sortList.end())
                        {
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
    string szShowText(""), szContent("");
    int nState = dyn_normal;
    bool bShowDevice = false;

    for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
    {
        // get monitor's current state
        nState = getMonitorState(lsItem->second.szIndex, szShowText);
        WImage *pMonitor = NULL;
        if(m_nShowType == -1 || m_nShowType == nState || 
            (m_nShowType == dyn_normal && nState == dyn_no_data) ||
            (m_nShowType == dyn_error && nState == dyn_bad))
        {
            bShowDevice = true;
            pMonitor = new WImage("/Images/state_green.gif", pTableCell);
        }
        if(pMonitor)
        {   
            // change show image by state
            switch(nState)
            {
            case dyn_no_data:
                pMonitor->setImageRef("/Images/state_grey.gif");
                break;
            case dyn_normal:
                pMonitor->setImageRef("/Images/state_green.gif");
                break;
            case dyn_warnning:
                pMonitor->setImageRef("/Images/state_yellow.gif");
                break;
            case dyn_error:
            case dyn_bad:
                pMonitor->setImageRef("/Images/state_red.gif");
                break;
            case dyn_disable:
                pMonitor->setImageRef("/Images/state_stop.gif");
                break;
            }

            // monitor's style && onclick event
            szContent = "style='cursor:pointer;' onclick = 'window.open(\"SimpleReport.exe?id=" + lsItem->second.szIndex + "\");'";
            sprintf(pMonitor->contextmenu_, szContent.c_str());
            pMonitor->setToolTip(szDeviceName + ":" + lsItem->second.szName + "\r\n" + szShowText);
        }
    }
    return bShowDevice;
}

int CSVWholeview::getMonitorState(const string & szMonitorID, string &szShowText)
{
    int nState = 0;
    sv_dyn dyn ;
    if(GetSVDYN(szMonitorID, dyn, m_szIDCUser, m_szIDCPwd))
    {
        nState = dyn.m_state;
        if(dyn.m_displaystr)
        szShowText = dyn.m_displaystr;
    }
    return nState;
}

void CSVWholeview::clearTree()
{
    if(m_pContent)
    {
        m_pContent->clear();
    }
}

void CSVWholeview::initTree()
{
    enumSVSE();
}

void CSVWholeview::refresh()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "wholetree";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();
    if(m_pTime)
        m_pTime->setText(m_szRefreshTime + curTime);

    char szQuery[4096]={0};
    int nSize = 4095;
    m_nShowType = -1;
    GetEnvironmentVariable( "QUERY_STRING", szQuery,nSize);
    char *pPos = strchr(szQuery, '=');
    if(pPos)
    {
        pPos ++;
        m_nShowType = atoi(pPos);
    }

    string szUserID = GetWebUserID();
    if(szUserID != m_szUserID)
    {
        m_szUserID = szUserID;
        if(m_pSVUser)
            m_pSVUser->setUserID(m_szUserID);
        else 
            m_pSVUser = new CUser(m_szUserID);
    }
    clearTree();
    initTree();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}