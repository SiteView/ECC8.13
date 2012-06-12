#include "grouplist.h"

#include "showtable.h"

//#include "../base/OperateLog.h"
#include "resstring.h"

#include "../../opens/libwt/WebSession.h"
#include "../demotreeview/define.h"
extern void PrintDebugString(const char * szMsg);
extern void PrintDebugString(const string &szMsg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVGroupList::SVGroupList(WContainerWidget * parent, CUser * pUser, string szIDCUser, string szIDCPwd):
WContainerWidget(parent)
{
    m_pGroupList     = NULL;
    m_pOperate       = NULL;
    m_pBtnHide       = NULL;
    m_pBtnHideDel    = NULL;

    m_pAdd           = NULL;
    m_pDel           = NULL;
    m_pEnable        = NULL;
    m_pDisable       = NULL;
    m_pSelAll        = NULL;
    m_pSelNone       = NULL;
    m_pSelInvert     = NULL;
    m_pSort          = NULL;

    m_pBtnRefresh    = NULL;
    m_pBtnDelSel     = NULL;
    m_pBtnEnterGroup = NULL;
    m_pBtnEdit       = NULL;
    
    m_pHasNoChild    = NULL;

    m_szIDCUser      = szIDCUser;
    m_szIDCPwd       = szIDCPwd;

    m_pSVUser        = pUser;

    m_szGroupName    = "localhost";

    //loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::AddGroup(string &szName, string &szIndex)
{
    string szParentID = FindParentID(szIndex);
    if(szParentID == m_szIndex)
        addGroupList(szName, szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::addGroupList(string &szName, string &szIndex)
{
    if (m_pGroupList)
    {
        SVTableCell svCell;
        int nRow = m_pGroupList->numRows();

        bool bHasEditRight = true;
        bool bHasDelRight = true;

        sv_group_state groupState = getGroupState(szIndex, m_pSVUser, m_szIDCUser, m_szIDCPwd);
        m_nDeviceCount += groupState.nDeviceCount;
        m_nMonitorCount += groupState.nMonitorCount;
        m_nMonitorErrCount += groupState.nErrorCount;
        m_nMonitorWarnCount += groupState.nWarnCount;
        m_nMonitorDisableCount += groupState.nDisableCount;
        if(m_pSVUser)
        {
            bHasEditRight = m_pSVUser->haveUserRight(szIndex, "editgroup");
            bHasDelRight = m_pSVUser->haveUserRight(szIndex, "delgroup");
        }
        else
        {
            bHasEditRight = false;
            bHasDelRight = false;
        }
        // 选择
        WCheckBox * pCheck =  NULL;
        if(m_bHasEditRight || m_bHasDelRight)
            if(bHasEditRight || bHasDelRight)
                pCheck = new WCheckBox("", (WContainerWidget *)m_pGroupList->elementAt(nRow, 0));

        // 状态
        string szState ("");
        bool bDisable = isDisable(szIndex, szState);
        WImage *pState = NULL;
        pState = new WImage("../icons/normal.gif", (WContainerWidget *)m_pGroupList->elementAt(nRow, 1));
        if(pState)
        {
            pState->setStyleClass("imgbutton");
			if(bDisable)
				pState->setImageRef("../../icons/disablemonitor.gif");
			else
			{
				switch(groupState.nState)
				{
				case 1:
					pState->setImageRef("../icons/normal.gif");
					break;
				case 2:
					pState->setImageRef("../icons/warnning.gif");
					break;
				case 3:
					pState->setImageRef("../icons/error.gif");
					break;
				}
			}
            pState->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
            if(bHasEditRight)
            {
                if(m_pBtnRefresh && m_pCurrentGroup)
                {
                    string szDisable = "onclick='showDisable(\"0\", \"" + szIndex + "\", \"" + m_pCurrentGroup->formName()
                        + "\", \"" + m_pBtnRefresh->getEncodeCmd("xclicked()") + "\")'";
                    strcpy(pState->contextmenu_, szDisable.c_str());
                }
            }
        }
        // 描述
        WText *pDesc = new WText("", (WContainerWidget *)m_pGroupList->elementAt(nRow, 2));
        if(pDesc)
        {
            char chState[512] = {0};
            sprintf(chState, "%s%s%d<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                szState.c_str(),
                SVResString::getResString("IDS_Device_Count").c_str(), groupState.nDeviceCount,
                SVResString::getResString("IDS_Monitor_Count").c_str(), groupState.nMonitorCount,
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), groupState.nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), groupState.nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), groupState.nWarnCount);
            pDesc->setText(chState);
        }

        // 名称
        WText *pName = new WText(szName, (WContainerWidget *)m_pGroupList->elementAt(nRow, 3));
        if ( pName )
        {
            if(m_pBtnEnterGroup && m_pCurrentGroup)
            {
                string szGroupOperate = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentGroup->formName()
                    + "\", \"" + m_pBtnEnterGroup->getEncodeCmd("xclicked()") + "\")' style='color:#669;cursor:pointer;' onmouseover='" 
                    + "this.style.textDecoration=\"underline\"' onmouseout='this.style.textDecoration=\"none\"'";
                strcpy(pName->contextmenu_, szGroupOperate.c_str());
            }
            pName->setToolTip(szName);
        }

        // 编辑
        WImage * pEdit = NULL;
        if(bHasEditRight) pEdit = new WImage("../icons/edit.gif", (WContainerWidget *)m_pGroupList->elementAt(nRow, 4));
        if (pEdit)
        {
            pEdit->setToolTip(SVResString::getResString("IDS_Edit"));
            pEdit->setStyleClass("imgbutton");
            if(m_pCurrentGroup && m_pBtnEdit)
            {
                string szGroupOperate = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentGroup->formName()
                    + "\", \"" + m_pBtnEdit->getEncodeCmd("xclicked()") + "\")'";

                strcpy(pEdit->contextmenu_, szGroupOperate.c_str());
            }
        }

        // 删除
        WImage * pDel = NULL;
        if(bHasDelRight) 
            pDel = new WImage("../icons/del.gif", (WContainerWidget *)m_pGroupList->elementAt(nRow, 5));
        if (pDel)
        {
            pDel->setStyleClass("imgbutton");
            pDel->setToolTip(SVResString::getResString("IDS_Delete_Group_Tip"));
            if(m_pCurrentGroup && m_pBtnDelSel)
            {
                string szGroupOperate = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentGroup->formName()
                    + "\", \"" + m_pBtnDelSel->getEncodeCmd("xclicked()") + "\")'";
                strcpy(pDel->contextmenu_, szGroupOperate.c_str());
            }
        }

        // 最后更新
        WText *pLast = new WText("", (WContainerWidget *)m_pGroupList->elementAt(nRow, 6));
        if(pLast)
        {
            svutil::TTime tmptime;
            if(tmptime != groupState.m_time)
                pLast->setText(groupState.m_time.Format());
        }

        if((nRow + 1) % 2 == 0)
            m_pGroupList->GetRow(nRow)->setStyleClass("tr1");
        else
            m_pGroupList->GetRow(nRow)->setStyleClass("tr2");


        if(pCheck)
        {
            svCell.setType(adCheckBox);
            svCell.setValue(pCheck);
            m_svGroup.WriteCell(szIndex, 0, svCell);
            SVTableRow *pRow = m_svGroup.Row(szIndex);
            if (pRow)
            {
                pRow->setProperty(szIndex.c_str());
            }
        }
        if(pState)
        {
            svCell.setType(adImage);
            svCell.setValue(pState);
            m_svGroup.WriteCell(szIndex, 1, svCell);
        }
        if(pDesc)
        {
            svCell.setType(adText);
            svCell.setValue(pDesc);
            m_svGroup.WriteCell(szIndex, 2, svCell);
        }
        if(pName)
        {
            svCell.setType(adText);
            svCell.setValue(pName);
            m_svGroup.WriteCell(szIndex, 3, svCell);
        }
        if(pLast)
        {
            svCell.setType(adText);
            svCell.setValue(pLast);
            m_svGroup.WriteCell(szIndex, 6, svCell);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::EditGroup(string &szName, string &szIndex)
{
    editGroupList(szName, szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::editGroupList(string &szName, string &szIndex)
{   
    SVTableRow *pRow = m_svGroup.Row(szIndex);
    if (pRow)
    {
        SVTableCell *pcell = pRow->Cell(3);
        if ( pcell )
        {
            if(pcell->Type() == adText)
            { 
                ((WText*)pcell->Value())->setToolTip(szName);
                ((WText*)pcell->Value())->setText(szName);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::createGroupList(WTable * pTable)
{
    int nRow = pTable->numRows();
    m_pGroupList = new WTable((WContainerWidget*)pTable->elementAt(nRow, 0));
    if(m_pGroupList)
    {
        m_pGroupList->setStyleClass("t3");
        new WText("", (WContainerWidget *)m_pGroupList->elementAt(0, 0));
        new WText(SVResString::getResString("IDS_State"), (WContainerWidget *)m_pGroupList->elementAt(0, 1));
        new WText(SVResString::getResString("IDS_State_Description"), (WContainerWidget *)m_pGroupList->elementAt(0, 2));
        new WText(SVResString::getResString("IDS_Name"), (WContainerWidget *)m_pGroupList->elementAt(0, 3));
        new WText(SVResString::getResString("IDS_Edit"), (WContainerWidget *)m_pGroupList->elementAt(0, 4));
        new WText(SVResString::getResString("IDS_Delete"), (WContainerWidget *)m_pGroupList->elementAt(0, 5));
        new WText(SVResString::getResString("IDS_Table_Col_Last_Refresh"), (WContainerWidget *)m_pGroupList->elementAt(0, 6));
        m_pGroupList->setCellPadding(0);
        m_pGroupList->setCellSpaceing(0);
        m_pGroupList->GetRow(0)->setStyleClass("t3title");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::createDelOperate()
{
    m_pDel = new WImage("../icons/del.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pDel)
    {
        m_pDel->setStyleClass("imgbutton");
        m_pDel->setToolTip(SVResString::getResString("IDS_Delete_Sel_Group_Tip"));
        WObject::connect(m_pDel, SIGNAL(clicked()), this, SLOT(deleteGroup()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::createSelOperate()
{
    m_pSelAll = new WImage("../icons/selall.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pSelAll)
    {
        m_pSelAll->setStyleClass("imgbutton");
        m_pSelAll->setToolTip(SVResString::getResString("IDS_All_Select"));
        WObject::connect(m_pSelAll, SIGNAL(clicked()), "showbar();", this, SLOT(selAll()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    m_pSelNone = new WImage("../icons/selnone.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pSelNone)
    {
        m_pSelNone->setStyleClass("imgbutton");
        m_pSelNone->setToolTip(SVResString::getResString("IDS_None_Select"));
        WObject::connect(m_pSelNone, SIGNAL(clicked()), "showbar();", this, SLOT(selNone()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    m_pSelInvert = new WImage("../icons/selinvert.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pSelInvert)
    {
        m_pSelInvert->setStyleClass("imgbutton");
        m_pSelInvert->setToolTip(SVResString::getResString("IDS_Invert_Select"));   
        WObject::connect(m_pSelInvert, SIGNAL(clicked()), "showbar();", this, SLOT(invertSel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::createEnableOperate()
{
    m_pEnable = new WImage("../icons/enable.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pEnable)
    {
        m_pEnable->setStyleClass("imgbutton");
        m_pEnable->setToolTip(SVResString::getResString("IDS_Enable_Group"));
        WObject::connect(m_pEnable, SIGNAL(clicked()), this, SLOT(enableSelGroup()));
    }

    m_pDisable = new WImage("../icons/disable.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pDisable)
    {
        m_pDisable->setStyleClass("imgbutton");
        m_pDisable->setToolTip(SVResString::getResString("IDS_Disable_Group"));
        WObject::connect(m_pDisable, SIGNAL(clicked()), this, SLOT(disableSelGroup()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::createOperate(WTable *pTable)
{
    int nRow = pTable->numRows();
    m_pOperate = new WTable((WContainerWidget*)pTable->elementAt(nRow, 0));
    if (m_pOperate)
    {
        m_pOperate->setStyleClass("t3");

        createSelOperate();
        createEnableOperate();
        createDelOperate();

        m_pSort = new WImage("../icons/sort.gif", (WContainerWidget *)m_pOperate->elementAt(0, 0));
        if(m_pSort)
        {
            m_pSort->setToolTip(SVResString::getResString("IDS_Sort"));
            m_pSort->setStyleClass("imgbutton");
            WObject::connect(m_pSort, SIGNAL(clicked()), "showbar();", this, SLOT(sortGroups()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        m_pAdd = new WPushButton(SVResString::getResString("IDS_Add_Group"), (WContainerWidget *)m_pOperate->elementAt(0, 1));
        m_pOperate->elementAt(0, 1)->setContentAlignment(AlignTop | AlignRight);
        if (m_pAdd)
        {
            m_pAdd->setStyleClass("wizardbutton");
            m_pAdd->setToolTip(SVResString::getResString("IDS_Add_Group_Tip"));
            WObject::connect(m_pAdd, SIGNAL(clicked()), "showbar();", this, SLOT(add()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVGroupList::loadString()
//{
//    //Resource
//    OBJECT objRes=LoadResource("default", "localhost");  
//    if( objRes !=INVALID_VALUE )
//    {	
//        MAPNODE ResNode=GetResourceNode(objRes);
//        if( ResNode != INVALID_VALUE )
//        {
//            FindNodeValue(ResNode,"IDS_Sub_Group",m_szTitle);
//            FindNodeValue(ResNode,"IDS_Delete",m_szColDel);
//            FindNodeValue(ResNode,"IDS_Edit",m_szColEdit);
//            FindNodeValue(ResNode,"IDS_Table_Col_Last_Refresh",m_szColLast);
//            FindNodeValue(ResNode,"IDS_Name",m_szColName);
//            FindNodeValue(ResNode,"IDS_State",m_szColState);
//            FindNodeValue(ResNode,"IDS_State_Description",m_szColDesc);
//            FindNodeValue(ResNode,"IDS_All_Select",m_szSelAllTip);
//            FindNodeValue(ResNode,"IDS_None_Select",m_szSelNoneTip);
//            FindNodeValue(ResNode,"IDS_Invert_Select",m_szInvertSelTip);
//            FindNodeValue(ResNode,"IDS_Delete_Sel_Group_Tip",m_szDelSelTip);
//            FindNodeValue(ResNode,"IDS_Delete_Group_Tip",m_szDelTip);
//            FindNodeValue(ResNode,"IDS_Sort",m_szSortTip);
//            FindNodeValue(ResNode,"IDS_Add_Group",m_szAdd);
//            FindNodeValue(ResNode,"IDS_Add_Group_Tip",m_szAddTip);
//            FindNodeValue(ResNode,"IDS_Disable_Group",m_szDisableTip);
//            FindNodeValue(ResNode,"IDS_Enable_Group",m_szEnableTip);
//            FindNodeValue(ResNode,"IDS_Delete_Group_Confirm",m_szDelAsk);
//            FindNodeValue(ResNode,"IDS_Delete_Sel_Group_Confirm",m_szDelSelAsk);
//            FindNodeValue(ResNode,"IDS_Edit",m_szEditTip);
//            FindNodeValue(ResNode,"IDS_Device_Count",m_szDeviceCount);
//            FindNodeValue(ResNode,"IDS_Monitor_Count",m_szMonitorCount);
//            FindNodeValue(ResNode,"IDS_Monitor_Disable_Count",m_szMonitorDisable);
//            FindNodeValue(ResNode,"IDS_Monitor_Error_Count",m_szMonitorError);
//            FindNodeValue(ResNode,"IDS_Monitor_Warn_Count",m_szMonitorWarn);
//            FindNodeValue(ResNode,"IDS_Group_Can_not_Disable",m_szGroupsDisable);
//            FindNodeValue(ResNode,"IDS_Group_Can_not_Enable",m_szGroupsEnable);
//            FindNodeValue(ResNode,"IDS_Group_Disable_Forver",m_szForver);
//            FindNodeValue(ResNode,"IDS_Group_Disable_Temprary",m_szTemprary);
//            FindNodeValue(ResNode,"IDS_Start_Time",m_szStartTime);
//            FindNodeValue(ResNode,"IDS_End_Time",m_szEndTime);
//            FindNodeValue(ResNode,"IDS_GROUP_LIST_IS_NULL", m_szNoGroup);
//            FindNodeValue(ResNode,"IDS_Group", m_szOperateGroup);
//        }
//        CloseResource(objRes);
//    }
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::initForm()
{
    SVShowTable * pTable = new SVShowTable(this);
    if (pTable)
    {
        pTable->setTitle(SVResString::getResString("IDS_Sub_Group").c_str());
        WTable *pSub = pTable->createSubTable();
        if(pSub)
        {
            createGroupList(pSub);

            int nRow = pSub->numRows();
            m_pHasNoChild = new WText( "<BR>" + SVResString::getResString("IDS_GROUP_LIST_IS_NULL"), pSub->elementAt(nRow, 0));
            pSub->elementAt(nRow, 0)->setContentAlignment(AlignCenter);
            if(m_pHasNoChild)
                m_pHasNoChild->setStyleClass("required");

            createOperate(pSub);
        }
    }
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::selNone()
{
    if(!m_svGroup.empty())
    {
        for(row it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    ((WCheckBox*)pcell->Value())->setChecked(false);
                }
            }
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::selAll()
{
    if(!m_svGroup.empty())
    {
        for(row it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    ((WCheckBox*)pcell->Value())->setChecked(true);
                }
            }
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::delSel()
{
    if(!m_szDelSelIndex.empty())
    {
        DelGroup(m_szDelSelIndex);
        SVTableRow * pRow = m_svGroup.Row(m_szDelSelIndex);
        if(pRow)
        {
            SVTableCell *pcell = pRow->Cell(1);
            if ( pcell)
            {
                int nRow = ((WTableCell*)(((WText*)pcell->Value())->parent()))->row();
                m_pGroupList->deleteRow(nRow);
            } 
        }
        m_svGroup.DelRow(m_szDelSelIndex); 
        m_szDelSelIndex = "";
    }
    else
    {
        if(!m_svGroup.empty())
        {
Delgroup:
            row it = NULL;
            for(it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
            {
                SVTableCell *pcell = (*it).second.Cell(0);
                if ( pcell )
                {
                    if (pcell->Type() == adCheckBox)
                    {
                        if(((WCheckBox*)pcell->Value())->isChecked())
                        {
                            string szGroupID = (*it).second.getProperty();
                            int nRow = ((WTableCell*)(((WCheckBox*)pcell->Value())->parent()))->row();
                            
                            m_pGroupList->deleteRow(nRow);
                            m_svGroup.DelRow(szGroupID);  
                            DelGroup(szGroupID);						
                            goto Delgroup;
                        }
                    }
                }
            }
        }
    }
    if(m_pGroupList)
    {
        int nRow = m_pGroupList->numRows();
        if(nRow > 1)
        {
            for(int i = 1; i<= nRow - 1; i++)
            {
                if( i % 2 == 0)
                    m_pGroupList->GetRow(i)->setStyleClass("tr2");
                else
                    m_pGroupList->GetRow(i)->setStyleClass("tr1");
            }
        }
        else
        {
            if(m_pHasNoChild)
                m_pHasNoChild->show();
        }
    }

	////插记录到UserOperateLog表
	//string szUserID("");
 //   if(m_pSVUser)
 //       szUserID = m_pSVUser->getUserID();
	//TTime mNowTime = TTime::GetCurrentTimeEx();
	//OperateLog m_pOperateLog;
	//m_pOperateLog.InsertOperateRecord("UserOperateLog", szUserID, mNowTime.Format(), m_szColDel, m_szOperateGroup, strDeleteGroupName);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::invertSel()
{
    if(!m_svGroup.empty())
    {
        for(row it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    ((WCheckBox*)pcell->Value())->setChecked(!(((WCheckBox*)pcell->Value())->isChecked()));
                }
            }
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::add()
{
    emit AddNewGroup();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::editGroup()//const std::string szGroupID)
{
    if(m_pCurrentGroup)
    {
        string szGroupID = m_pCurrentGroup->text();
        if(!szGroupID.empty())
            emit EditGroupByID(szGroupID);
        else
            WebSession::js_af_up = "hiddenbar();";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* SVGroupList::getGroupName()
{
    return m_szGroupName.c_str();
}


bool SVGroupList::isChildEdit(string szIndex)
{
    string szParent = FindParentID(szIndex);
    if(szParent == m_szIndex)
    {
        SVTableRow *pRow = m_svGroup.Row(szIndex);
        if (pRow)
        {
            SVTableCell *pcell = pRow->Cell(3);
            if ( pcell )
            {
                if(pcell->Type() == adText)
                { 
                    string szName = getGroupName(szIndex);
                    ((WText*)pcell->Value())->setToolTip(szName);
                    ((WText*)pcell->Value())->setText(szName);
                }
            }
        }
        return true;
    }
    return false;
}

string SVGroupList::getGroupName(string szIndex)
{
    string szName;
    OBJECT objGroup = GetGroup(m_szIndex,  m_szIDCUser, m_szIDCPwd);
    if(objGroup != INVALID_VALUE)
    {
        MAPNODE mainnode = GetGroupMainAttribNode(objGroup);
        if(mainnode != INVALID_VALUE)
            FindNodeValue(mainnode, "sv_name", szName);
        CloseGroup(objGroup);
    }
    return szName;
}

bool SVGroupList::isInGroup(string &szIndex)
{
    if(m_szIndex == szIndex)
        return true;
    szIndex = FindParentID(szIndex);
    while(!szIndex.empty())
    {
        if(szIndex == m_szIndex)
            return true;
        szIndex = FindParentID(szIndex);
        if(IsSVSEID(szIndex))
            break;
    }
    if(m_szIndex == szIndex)
        return true;
    return false;
}

bool SVGroupList::isParentEdit(string szIndex)
{
    if(m_szIndex == szIndex)
        return true;
    string szParent = FindParentID(m_szIndex);
    while(!szParent.empty())
    {
        if(szParent == szIndex)
            return true;
        szParent = FindParentID(szParent);
        if(IsSVSEID(szParent))
            break;
    }
    if(m_szIndex == szParent)
        return true;
    return false;
}

void SVGroupList::refreshGroup(string szIndex)
{
    if(m_szIndex != szIndex)
    {
        while(!szIndex.empty())
        {
            string szParent = FindParentID(szIndex);
            if(szParent == m_szIndex)
                break;
            else
            {
                szIndex = szParent;
                if(IsSVSEID(szIndex))
                    return;
            }
        }
    }
    SVTableRow *pRow = m_svGroup.Row(szIndex);
    if (pRow)
    {
        SVTableCell *pcell = pRow->Cell(2);
        if ( pcell )
        {
            if(pcell->Type() == adText)
            { 
                sv_group_state groupState = getGroupState(szIndex, m_pSVUser, m_szIDCUser, m_szIDCPwd);
                char szState[512] = {0};
                sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d<BR>", 
                SVResString::getResString("IDS_Device_Count").c_str(), groupState.nDeviceCount,
                SVResString::getResString("IDS_Monitor_Count").c_str(), groupState.nMonitorCount,
                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), groupState.nDisableCount,
                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), groupState.nErrorCount, 
                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), groupState.nWarnCount);
                ((WText*)pcell->Value())->setText(szState);
            }
        }
    }
}

void SVGroupList::refreshNamePath()
{
    int nPos = static_cast<int>(m_szIndex.find("."));

    if( nPos < 0)
    {
        OBJECT root = GetSVSE(m_szIndex, m_szIDCUser, m_szIDCPwd);
        if(root != INVALID_VALUE)
        {
            m_szGroupName = GetSVSELabel(root);
            m_szGroupDesc = "";
            CloseSVSE(root);
        }
    }
    else
    {
        OBJECT objGroup = GetGroup(m_szIndex,  m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            MAPNODE mainnode = GetGroupMainAttribNode(objGroup);
            if(mainnode != INVALID_VALUE)
            {
                FindNodeValue(mainnode, "sv_name", m_szGroupName);
                FindNodeValue(mainnode, "sv_description", m_szGroupDesc);
            }
            CloseGroup(objGroup);
        }
    }
    m_lsPath.clear();
    makePath(m_szIndex, m_lsPath);
}

void SVGroupList::delGroupRow(string &szIndex)
{
    if(isParentEdit(szIndex))
    {
        string szParentID = FindParentID(szIndex);
        enterGroup(szParentID);
    }
    else
    {
        string szParentID = FindParentID(szIndex);
        if(szParentID == m_szIndex)
        {
            SVTableRow * pRow = m_svGroup.Row(szIndex);
            if(pRow)
            {
                SVTableCell *pcell = pRow->Cell(1);
                if ( pcell)
                {
                    int nRow = ((WTableCell*)(((WText*)pcell->Value())->parent()))->row();
                    if(m_pGroupList)
                    {
                        m_pGroupList->deleteRow(nRow);
                        if(m_pGroupList->numRows() == 1)
                            if(m_pHasNoChild)
                                m_pHasNoChild->show();
                    }
                } 
            }
            m_svGroup.DelRow(szIndex); 
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::DelGroup(string &szIndex)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    if(!szIndex.empty())
    {
		sv_group_state groupState = getGroupState(szIndex, m_pSVUser, m_szIDCUser, m_szIDCPwd);
        OBJECT group = GetGroup(szIndex, m_szIDCUser, m_szIDCPwd);
        if(group != INVALID_VALUE)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
            if(GetSubEntitysIDByGroup(group, lsEntityID))
            {
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    DelDevice(szEntityID);
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    DelGroup(szSubGroupID);
                }
            }

            CloseGroup(group);
            string szName = getGroupNameByID(szIndex, m_szIDCUser, m_szIDCPwd);;

            DeleteGroup(szIndex, m_szIDCUser, m_szIDCPwd); 
			m_nDeviceCount -= groupState.nDeviceCount;
			m_nMonitorCount -= groupState.nMonitorCount;
			m_nMonitorErrCount -= groupState.nErrorCount;
			m_nMonitorWarnCount -= groupState.nWarnCount;
			m_nMonitorDisableCount -= groupState.nDisableCount;

            emit DeleteGroupSucc(szName, szIndex);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::DelDevice(string &szIndex)
{
    list<string> lstMonitors;
    list<string>::iterator lstItem;
    if(!szIndex.empty())
    {
        OBJECT entity = GetEntity(szIndex, m_szIDCUser, m_szIDCPwd);
        if (entity != INVALID_VALUE)
        {
            if(GetSubMonitorsIDByEntity(entity, lstMonitors))
            {
                for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                {
                    DeleteSVMonitor((*lstItem), m_szIDCUser, m_szIDCPwd);
                    DeleteTable((*lstItem), m_szIDCUser, m_szIDCPwd);
                }
            }
        }
        string szName = getDeviceNameByID(szIndex, m_szIDCUser, m_szIDCPwd);

        emit DeleteDeviceSucc(szName, szIndex);

        CloseEntity(entity);
        DeleteEntity(szIndex, m_szIDCUser, m_szIDCPwd);
    }
}

bool SVGroupList::makePath(string &szGroupID, list<base_param> &lsPath)
{
    OBJECT objGroup;
    int nPos = static_cast<int>(szGroupID.find("."));
    if(nPos < 0)
    {
        objGroup = GetSVSE(szGroupID, m_szIDCUser, m_szIDCPwd);
        string szName ("");
        if(objGroup != INVALID_VALUE)
            szName = GetSVSELabel(objGroup);
        else
            szName = "localhost";
        CloseSVSE(objGroup);
        base_param svparam;
        svparam.szIndex = szGroupID;
        svparam.szName = szName;
        lsPath.push_back(svparam);
        return true;   
    }
    else
    {
        string szParent = FindParentID(szGroupID);
        string szName ("");
        objGroup = GetGroup(szGroupID, m_szIDCUser, m_szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {

            MAPNODE node = GetGroupMainAttribNode(objGroup);
            if(node != INVALID_VALUE)
            {
                FindNodeValue(node, "sv_name", szName);  
            }
            CloseGroup(objGroup);
            base_param svparam;
            svparam.szIndex = szGroupID;
            svparam.szName = szName;
            lsPath.push_back(svparam);
        }
        return makePath(szParent, lsPath);// + " : " + szName;
    }
}

const char * SVGroupList::getGroupDesc()
{
    return m_szGroupDesc.c_str();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::enumGroup(string &szIndex)
{
    OBJECT root;
    m_szGroupDesc = "";
    m_szAdvState = "";
    bool bGroup = false;
    bool bSucc  = false;


    map<int, base_param, less<int> > sortList;
    map<int, base_param, less<int> >::iterator lsItem;

    if(m_pSVUser)
    {
        int nPos = static_cast<int>(szIndex.find("."));
        if( nPos < 0)
        {
            root = GetSVSE(szIndex, m_szIDCUser, m_szIDCPwd);
        }
        else
        {
            isDisable(szIndex, m_szAdvState, false); 
            bGroup = true;
            root = GetGroup(szIndex, m_szIDCUser, m_szIDCPwd);
        }

        if(root != INVALID_VALUE)
        {
            if(bGroup)
            {
                MAPNODE node = GetGroupMainAttribNode(root);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, "sv_name", m_szGroupName);
                    FindNodeValue(node, "sv_description", m_szGroupDesc);
                }
            }
            else
            {
                m_szGroupName = GetSVSELabel(root);
                m_szGroupDesc = "SE";
            }
            
            m_lsPath.clear();
            makePath(szIndex, m_lsPath);
            list<string> lsGroupID;
            list<string>::iterator lsItem;

            if(!bGroup)
                bSucc = GetSubGroupsIDBySE(root, lsGroupID);
            else
                bSucc = GetSubGroupsIDByGroup(root,lsGroupID);

            if(bSucc)
            {
                base_param group;
                int nMax = static_cast<int>(lsGroupID.size());
                int nIndex = 0;
                for(lsItem = lsGroupID.begin(); lsItem != lsGroupID.end(); lsItem ++)
                {
                    string szID = (*lsItem).c_str();
                    bool bHasRight = true;
                    if(m_pSVUser)
                        bHasRight = m_pSVUser->haveGroupRight(szID, Tree_GROUP);
                    if(bHasRight)
                    {
                        OBJECT  groupnode = GetGroup(szID, m_szIDCUser, m_szIDCPwd);
                        if(groupnode != INVALID_VALUE )
                        {
                            MAPNODE node = GetGroupMainAttribNode(groupnode);
                            if(node != INVALID_VALUE)
                            {
                                string szName (""), szIndex ("");
                                FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    nIndex = FindIndexByID(szID);
                                else
                                    nIndex = atoi(szIndex.c_str());

                                group.szIndex = szID;
                                group.szName = szName;

                                map<int, base_param, less<int> >::iterator lsItem = sortList.find(nIndex);
                                while(lsItem != sortList.end())
                                {
                                    nIndex ++;
                                    lsItem = sortList.find(nIndex);
                                }
                                sortList[nIndex] = group;
                            }
                            CloseGroup(groupnode);
                        }
                    }
                }
            }
            if(!bGroup)
                CloseSVSE(root);
            else     
                CloseGroup(root);            
        }
    }

    if(sortList.size() > 0)
    {
        for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
            AddGroup(lsItem->second.szName,lsItem->second.szIndex);
        if(m_pHasNoChild)
            m_pHasNoChild->hide();
    }
    else
    {
        if(m_pHasNoChild)
            m_pHasNoChild->show();
    }
    emit EnumDeviceByID(szIndex);

    if(m_pSort && m_bHasEditRight)
    {
        if(sortList.size() <= 1)
            m_pSort->hide();
        else
            m_pSort->show();
    }
    else if(m_pSort && !m_bHasEditRight)
    {
        m_pSort->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::gotoGroup()
{
    if(m_pCurrentGroup)
    {
        string szGroupIndex = m_pCurrentGroup->text();
        if(!szGroupIndex.empty())
            enterGroup(szGroupIndex);
        else
            WebSession::js_af_up = "hiddenbar();";
    }
}

void SVGroupList::EnterGroupByID(string &szIndex)
{
    enterGroup(szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::changeDelState()
{
    if(!m_bHasDelRight)
    {
        if(m_pDel)                  m_pDel->hide();
    }
    else
    {
        if(m_pDel)                  m_pDel->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::changeEnableState()
{
    if(!m_bHasEditRight)
    {
        if(m_pEnable)               m_pEnable->hide();
        if(m_pDisable)              m_pDisable->hide();
    }
    else
    {  
        if(m_pEnable)               m_pEnable->show();
        if(m_pDisable)              m_pDisable->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::changeSelState()
{
    if(m_bHasEditRight)
    {
        if(m_pSelAll)       m_pSelAll->show();
        if(m_pSelNone)      m_pSelNone->show();
        if(m_pSelInvert)    m_pSelInvert->show();
    }
    else
    {
        if(m_pSelAll)       m_pSelAll->hide();
        if(m_pSelNone)      m_pSelNone->hide();
        if(m_pSelInvert)    m_pSelInvert->hide();
    }
}

void SVGroupList::enumRight()
{
    m_bHasAddRight = true; 
    m_bHasEditRight = true;
    m_bHasDelRight = true;
    m_bHasSortRight = true;
    if(m_pSVUser)
    {
        m_bHasAddRight = m_pSVUser->haveUserRight(m_szIndex, "addsongroup");
        m_bHasEditRight = m_pSVUser->haveUserRight(m_szIndex, "editgroup");
        m_bHasDelRight = m_pSVUser->haveUserRight(m_szIndex, "delgroup");
    }
    else
    {
        m_bHasAddRight = false; 
        m_bHasEditRight = false;
        m_bHasDelRight = false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::changeOperateState()
{
    if(m_pAdd && !m_bHasAddRight)        m_pAdd->hide();
    else if(m_pAdd && m_bHasAddRight)    m_pAdd->show();

    changeDelState();
    changeSelState();
    changeEnableState();
}

void SVGroupList::BackGroup(string &szIndex)
{
    enterGroup(szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::enterGroup(string &szIndex)
{
    if(!szIndex.empty())
    {  
        m_szIndex = szIndex;
        if (m_pGroupList)
        {
            while ( m_pGroupList->numRows() > 1)
            {
                m_pGroupList->deleteRow(m_pGroupList->numRows() - 1);
            }
        }
        
        m_nDeviceCount = 0;
        m_nMonitorCount = 0;
        m_nMonitorErrCount = 0;
        m_nMonitorWarnCount = 0;
        m_nMonitorDisableCount = 0;

        m_svGroup.clear();
        enumRight();
        enumGroup(m_szIndex);
        changeOperateState();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::deleteGroup()
{
    if(!m_svGroup.empty())
    {
        for(row it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        if(m_pBtnHideDel)
                        {
                            string szCmd = m_pBtnHideDel->getEncodeCmd("xclicked()");
                            if(!szCmd.empty())
                            {
                                string szDelFunc = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Group_Confirm") + "\",'"  +
                                    SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szCmd + "');hiddenbar();" ;
                                WebSession::js_af_up = szDelFunc;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

void SVGroupList::changeState()
{
    if(m_pCurrentGroup)
    {
        string szGroupID = m_pCurrentGroup->text();
        SVTableRow *pRow = m_svGroup.Row(szGroupID);
        if (pRow)
        {
            SVTableCell *pcell = pRow->Cell(1);
            if(pcell)
            {
                if(pcell->Type() == adImage)
                {
                    string szTemp = szGroupID;
                    string szState ("");
                    if(isDisable(szTemp, szState))
                    {
                        emit ChangeGroupState(szGroupID, dyn_disable);
                        ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                        ((WImage*)pcell->Value())->setToolTip("");
                        pcell = pRow->Cell(2);
                        if(pcell && pcell->Type() == adText)
                            ((WText*)pcell->Value())->setText(szState + ((WText*)pcell->Value())->text());
                    }
                    else
                    {
                        emit ChangeGroupState(szGroupID, dyn_normal);
                        sv_group_state groupState = getGroupState(szTemp, m_pSVUser, m_szIDCUser, m_szIDCPwd);
                        switch(groupState.nState)
                        {
                        case 1:
                            ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                            break;
                        case 2:
                            ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                            break;
                        case 3:
                            ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                            break;
                        }
                        char szState[512] = {0};
                        sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                                SVResString::getResString("IDS_Device_Count").c_str(), groupState.nDeviceCount,
                                SVResString::getResString("IDS_Monitor_Count").c_str(), groupState.nMonitorCount,
                                SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), groupState.nDisableCount,
                                SVResString::getResString("IDS_Monitor_Error_Count").c_str(), groupState.nErrorCount, 
                                SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), groupState.nWarnCount);
                        pcell = pRow->Cell(2);
                        if(pcell && pcell->Type() == adText)
                            ((WText*)pcell->Value())->setText(szState);
                        pcell = pRow->Cell(6);
                        if(pcell && pcell->Type() == adText)
                            ((WText*)pcell->Value())->setText(groupState.m_time.Format());
                    }
                }
            }
        }
    }
}

bool SVGroupList::isDisable(string &szGroupID, string &szState, bool bAddBR)
{
    bool bDisable = false;

    string szBR ("");
    if(bAddBR)
        szBR = "<BR>";
    else
        szBR = ",";

    OBJECT objGroup = GetGroup(szGroupID, m_szIDCUser, m_szIDCPwd);
    if(objGroup != INVALID_VALUE)
    {
        MAPNODE mainnode = GetGroupMainAttribNode(objGroup);
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("IDS_Group_Disable_Forver");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                szState = SVResString::getResString("") + szBR;
                bDisable =  true;
            }
            else if( szDisable == "time")
            {
                szState = SVResString::getResString("IDS_Group_Disable_Temprary") + szBR;
                string szEndTime (""), szStartTime ("");
                FindNodeValue(mainnode, "sv_endtime", szEndTime);
                FindNodeValue(mainnode, "sv_starttime", szStartTime);
                int nYear = 0, nMonth = 0, nDay = 0;
                int nHour = 0, nMinute = 0;
                if(!szStartTime.empty())
                {
                    sscanf(szStartTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    char szMsg[256] = {0};
                    sprintf(szMsg, SVResString::getResString("IDS_Start_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
                    szState += szMsg;
                    szState += szBR;
                }
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    char szMsg[256] = {0};
                    sprintf(szMsg, SVResString::getResString("IDS_End_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
                    szState += szMsg;
                    szState += szBR;       
                    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

                    svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime < ttend)
                        bDisable =  true;                        
                }
            }
        }
        CloseGroup(objGroup);
    }
    if(!bDisable)
        szState = "";
    return bDisable;
}


void SVGroupList::createHideButton()
{
    m_pBtnHide = new WPushButton("hidebtn", this);
    if(m_pBtnHide)
    {
        WObject::connect(m_pBtnHide, SIGNAL(clicked()), this, SLOT(disableGroupSucc()));
        m_pBtnHide->hide();
    }
    m_pBtnHideDel = new WPushButton("hidebtn", this);
    if(m_pBtnHideDel)
    {
        WObject::connect(m_pBtnHideDel, SIGNAL(clicked()), this, SLOT(delSel()));
        m_pBtnHideDel->hide();
    }
    m_pBtnRefresh = new WPushButton("hidebutton", this);
    if(m_pBtnRefresh)
    {
        WObject::connect(m_pBtnRefresh, SIGNAL(clicked()), this, SLOT(changeState()));
        m_pBtnRefresh->hide();
    }
    m_pBtnDelSel = new WPushButton("hidebtn", this);
    if(m_pBtnDelSel)
    {
        WObject::connect(m_pBtnDelSel, SIGNAL(clicked()), this, SLOT(delSelGroup()));
        m_pBtnDelSel->hide();
    }
    m_pBtnEnterGroup = new WPushButton("hidebtn", this);
    if(m_pBtnEnterGroup)
    {
        WObject::connect(m_pBtnEnterGroup, SIGNAL(clicked()), this, SLOT(gotoGroup()));
        m_pBtnEnterGroup->hide();
    }
    m_pBtnEdit = new WPushButton("hidebtn", this);
    if(m_pBtnEdit)
    {
        WObject::connect(m_pBtnEdit, SIGNAL(clicked()), this, SLOT(editGroup()));
        m_pBtnEdit->hide();
    }
    m_pCurrentGroup = new WLineEdit("", this);
    if(m_pCurrentGroup)
        m_pCurrentGroup->hide();
}

void SVGroupList::disableGroupSucc()
{
    if(!m_svGroup.empty())
    {
        row it = NULL;
        for(it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szMonitorID = (*it).second.getProperty();
                        pcell = (*it).second.Cell(1);
                        if(pcell && pcell->Type() == adImage)
                        {
                            string szState ("");
                            if(isDisable(szMonitorID, szState))
                            {
                                emit ChangeGroupState(szMonitorID, dyn_disable);
                                ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                                ((WImage*)pcell->Value())->setToolTip("");
                                pcell = (*it).second.Cell(2);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(szState + ((WText*)pcell->Value())->text());
                            }
                            else
                            {
                                emit ChangeGroupState(szMonitorID, dyn_normal);
                                sv_group_state groupState = getGroupState(szMonitorID, m_pSVUser, m_szIDCUser, m_szIDCPwd);
                                switch(groupState.nState)
                                {
                                case 1:
                                    //emit ChangeGroupState(szMonitorID, dyn_normal);
                                    ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                                    break;
                                case 2:
                                    //emit ChangeGroupState(szMonitorID, dyn_warnning);
                                    ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                                    break;
                                case 3:
                                    //emit ChangeGroupState(szMonitorID, dyn_error);
                                    ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                                    break;
                                }
                                char szState[512] = {0};
                                sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                                    SVResString::getResString("IDS_Device_Count").c_str(), groupState.nDeviceCount,
                                    SVResString::getResString("IDS_Monitor_Count").c_str(), groupState.nMonitorCount,
                                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), groupState.nDisableCount,
                                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), groupState.nErrorCount, 
                                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), groupState.nWarnCount);
                                pcell = (*it).second.Cell(2);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(szState);
                                pcell = (*it).second.Cell(6);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(groupState.m_time.Format());
                            }
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::enableSelGroup()
{   
    list<string> lsSel;
    if(!m_svGroup.empty())
    {
        row it = NULL;
        for(it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {                    
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        if(isGroupDisable(szDeviceID) != 0)
                            lsSel.push_back((*it).second.getProperty());
                    }
                }
            }
        }
        if(lsSel.size() > 0)
        {
            string szQueueName = makeQueueName();
            CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
            list<string>::iterator lsItem;
            for(lsItem = lsSel.begin(); lsItem != lsSel.end(); lsItem++)
            {
                int nSize = static_cast<int>((*lsItem).length()) + 2;
                char * pszIndex = new char[nSize];
                if(pszIndex)
                {
                    memset(pszIndex, 0, nSize);
                    strcpy(pszIndex, (*lsItem).c_str());

                    if(!::PushMessage(szQueueName, "SV_INDEX", pszIndex, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("Disable group: PushMessage into queue failed!");
                    delete []pszIndex;
                }
                //szSelIndex += (*lsItem);
                //szSelIndex += ",";
            }
            char pEnd[2] = {0};
            if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("Disable group(End label): PushMessage into queue failed!");
            if(m_pBtnHide)
            {
                string szCmd = m_pBtnHide->getEncodeCmd("xclicked()");
                if(!szCmd.empty())
                {
                    string szDisable = "showDisableUrl('disable.exe?disabletype=0&operatetype=1&queuename=" +
                        szQueueName + "', '" + szCmd + "');";
                    WebSession::js_af_up = szDisable;
                }
            }
        }
        else
        {
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupList::disableSelGroup()
{   
    list<string> lsSel;
    if(!m_svGroup.empty())
    {
        row it = NULL;
        for(it = m_svGroup.begin(); it != m_svGroup.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {                    
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        if(isGroupDisable(szDeviceID) == 0)
                            lsSel.push_back((*it).second.getProperty());
                    }
                }
            }
        }
        if(lsSel.size() > 0)
        {
            string szQueueName = makeQueueName();
            CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
            list<string>::iterator lsItem;
            for(lsItem = lsSel.begin(); lsItem != lsSel.end(); lsItem++)
            {
                int nSize = static_cast<int>((*lsItem).length()) + 2;
                char * pszIndex = new char[nSize];
                if(pszIndex)
                {
                    memset(pszIndex, 0, nSize);
                    strcpy(pszIndex, (*lsItem).c_str());

                    if(!::PushMessage(szQueueName, "SV_INDEX", pszIndex, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("Disable group: PushMessage into queue failed!");
                    delete []pszIndex;
                }
                //szSelIndex += (*lsItem);
                //szSelIndex += ",";
            }
            char pEnd[2] = {0};
            if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("Disable Group(End label): PushMessage into queue failed!");
            if(m_pBtnHide)
            {
                string szCmd = m_pBtnHide->getEncodeCmd("xclicked()");
                if(!szCmd.empty())
                {
                    string szDisable = "showDisableUrl('disable.exe?disabletype=0&operatetype=0&queuename=" +
                        szQueueName + "', '" + szCmd + "');";
                    WebSession::js_af_up = szDisable;
                }
            }
        }
        else
        {
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Disable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
        }
    }
}

//
void SVGroupList::delSelGroup()
{
    if(m_pBtnHideDel)
    {
        string szCmd = m_pBtnHideDel->getEncodeCmd("xclicked()");
        if(!szCmd.empty())
        {
            string szDelFunc = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Sel_Group_Confirm") + "\",'"  +
                                    SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szCmd + "');hiddenbar();" ;
            WebSession::js_af_up = szDelFunc;
        }
    }
    if(m_pCurrentGroup)
        m_szDelSelIndex = m_pCurrentGroup->text();
    else
        WebSession::js_af_up = "hiddenbar();";
}

void SVGroupList::sortGroups()
{
    emit sortGroupsList(Tree_GROUP);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


