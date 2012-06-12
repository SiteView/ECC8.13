#include "monitorview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../kennel/svdb/libutil/time.h"
#include "../../opens/libwt/WScrollArea"
//#include "../base/OperateLog.h"
#include "statedesc.h"

#include "groupview.h"
#include "resstring.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char* pszMsg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVMonitorview::SVMonitorview(WContainerWidget * parent, CUser * pUser, string szIDCUser, 
                             string szIDCPwd, string szDeviceIndex):
WTable(parent)
{
    m_pGeneral = NULL;
    m_pMonitorList = NULL;
    m_pOperate = NULL;
    m_pMonitor = NULL;
    //m_pTitle = NULL;
    m_pDeviceType = NULL;
    m_pbtnHide = NULL;
    m_pBtnHideDel = NULL;
    m_pAdd = NULL;
    m_pDel = NULL;
    m_pEnable = NULL;
    m_pDisable = NULL;
    m_pRefresh = NULL;
    m_pSelAll = NULL;
    m_pSelNone = NULL;
    m_pSelInvert = NULL;
    m_pPaste      = NULL;
    m_pCopy      = NULL;
    m_pTime      = NULL;
    m_pSort      = NULL;
    m_pContent   = NULL;
    m_pDependsCell = NULL;
    m_pDependDevice= NULL;
    m_pHasNoChild = NULL;

    m_szRefreshEvent = "";
    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;

    m_pbtnRefresh = NULL;
    m_pbtnEdit = NULL;

    m_pCurrentMonitor = NULL;

    m_pSVUser = pUser;
    m_pMain = NULL;

    //loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVMonitorview::loadString()
//{
//	//Resource
//	OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//            FindNodeValue(ResNode, "IDS_Delete_Monitor_Confirm", m_szDelAsk);
//			FindNodeValue(ResNode,"IDS_Device_Type",m_szDeviceTypeLabel);
//			FindNodeValue(ResNode,"IDS_Refresh_Time",m_szRefreshTime);
//			FindNodeValue(ResNode,"IDS_State",m_szColState);
//			FindNodeValue(ResNode,"IDS_State_Description",m_szColDesc);
//			FindNodeValue(ResNode,"IDS_Name",m_szColName);
//			FindNodeValue(ResNode,"IDS_Refresh_Tip",m_szColRefresh);
//			FindNodeValue(ResNode,"IDS_Table_Col_Last_Refresh",m_szColLast);
//			FindNodeValue(ResNode,"IDS_Edit",m_szColEdit);
//			FindNodeValue(ResNode,"IDS_Monitor_Edit_Tip",m_szEditTip);
//			FindNodeValue(ResNode,"IDS_Monitor_Refresh_Tip",m_szRefreshTip);
//			FindNodeValue(ResNode,"IDS_Disable_Enable_Tip",m_szOperateTip);
//			FindNodeValue(ResNode,"IDS_Monitor_List_Title",m_szMonitorTitle);
//			FindNodeValue(ResNode,"IDS_General_Infor_Title",m_szGeneralTitle);
//			FindNodeValue(ResNode,"IDS_Add_Monitor",m_szAdd);
//			FindNodeValue(ResNode,"IDS_All_Select",m_szSelAllTip);
//			FindNodeValue(ResNode,"IDS_None_Select",m_szSelNoneTip);
//			FindNodeValue(ResNode,"IDS_Invert_Select",m_szInvertSelTip);
//			FindNodeValue(ResNode,"IDS_Sort",m_szSortTip);
//			FindNodeValue(ResNode,"IDS_List_View_Tip",m_szListviewTip);
//			FindNodeValue(ResNode,"IDS_Icon_View_Tip",m_szIconviewTip);
//			FindNodeValue(ResNode,"IDS_Operate_Back_Parent",m_szBackParent);
//			FindNodeValue(ResNode,"IDS_Operate_Back_Parent_Tip",m_szBackParentTip);
//			FindNodeValue(ResNode,"IDS_Monitor_Count",m_szMonitorCount);
//			FindNodeValue(ResNode,"IDS_Monitor_Disable_Count",m_szMonitorDisable);
//			FindNodeValue(ResNode,"IDS_Depends_On",m_szDependsOn);
//			FindNodeValue(ResNode,"IDS_Depends_Condition",m_szDependsCondition);
//			FindNodeValue(ResNode,"IDS_Monitor_Error_Count",m_szMonitorError);
//			FindNodeValue(ResNode,"IDS_Monitor_Warn_Count",m_szMonitorWarn);
//			FindNodeValue(ResNode,"IDS_Day",m_szDay);
//			FindNodeValue(ResNode,"IDS_Hour",m_szHour);
//			FindNodeValue(ResNode,"IDS_Minute",m_szMinute);
//			FindNodeValue(ResNode,"IDS_Monitor_Can_not_Disable",m_szMonitorsDisable);
//			FindNodeValue(ResNode,"IDS_Monitor_Can_not_Enable",m_szMonitorsEnable);
//			FindNodeValue(ResNode,"IDS_Device_Disable_Forver",m_szDevForver);
//			FindNodeValue(ResNode,"IDS_Device_Disable_Temprary",m_szDevTemprary);
//			FindNodeValue(ResNode,"IDS_Monitor_Disable_Forver",m_szForver);
//			FindNodeValue(ResNode,"IDS_Monitor_Disable_Temprary",m_szTemprary);
//			FindNodeValue(ResNode,"IDS_Start_Time",m_szStartTime);
//			FindNodeValue(ResNode,"IDS_End_Time",m_szEndTime);
//			FindNodeValue(ResNode,"IDS_Enable_Monitor_Tip",m_szEnableTip);
//			FindNodeValue(ResNode,"IDS_Disable_Monitor_Tip",m_szDisableTip);
//			FindNodeValue(ResNode,"IDS_Delete_Select_Monitor_Tip",m_szDelSelTip);
//			FindNodeValue(ResNode, "IDS_MONITOR_LIST_IS_NULL", m_szNoMonitor);       
//			FindNodeValue(ResNode, "IDS_Monitor_Title", m_szOperateMonitor);       
//			FindNodeValue(ResNode, "IDS_Delete", m_szTypeDelete);
//			FindNodeValue(ResNode, "IDS_Copy", m_szCopySelTip);
//			FindNodeValue(ResNode, "IDS_Past", m_szPastTip);
//
//            FindNodeValue(ResNode,"IDS_Add_Title", m_szTypeAdd);
//            FindNodeValue(ResNode,"IDS_Monitor_Title", m_szMonitor);
//		}
//		CloseResource(objRes);
//	}
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::initForm()
{
    setStyleClass("t5");
    int nRow = numRows();
    WTable *pSub = new WTable(elementAt(nRow, 0));
    if(pSub)
    {
        WScrollArea *pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(pSub);
        }        
        pSub->setStyleClass("t5");
        elementAt(nRow, 0)->setStyleClass("t10");
        nRow = pSub->numRows();
        m_pContent = new WTable(pSub->elementAt(nRow,0));
        pSub->elementAt(nRow, 0)->setContentAlignment(AlignLeft | AlignTop);
        if(m_pContent)
        {
            m_pContent->setStyleClass("t8");
            createTitle();
            createControl();
            createGeneral();
            createMonitor();
            connect(&m_GroupName, SIGNAL(mapped(const std::string)), this, SLOT(gotoGroup(const std::string)));
            connect(&m_DeviceName, SIGNAL(mapped(const std::string)), this, SLOT(gotoDevice(const std::string)));
        }
    }
    nRow = numRows();
    new CSVStateDesc(elementAt(nRow, 0));
    elementAt(nRow, 0)->setContentAlignment(AlignBottom);
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createTitle()
{
    int nRow = m_pContent->numRows();
    WTable *pSub = new WTable(m_pContent->elementAt(nRow, 0));
    m_pContent->elementAt(0, 0)->setStyleClass("t1title");
    if(pSub)
    {
        pSub->setStyleClass("t3");
        nRow = pSub->numRows();
        m_pTitleCell = pSub->elementAt(nRow, 0);
        m_pTime  = new WText("local time", pSub->elementAt(nRow, 1));
        pSub->elementAt(nRow, 1)->setContentAlignment(AlignRight | AlignTop);
        pSub->elementAt(nRow, 1)->setStyleClass("cell_40");
        svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
        string curTime = ttime.Format();
        if(m_pTime)
        {
            m_pTime->setStyleClass("tgrouptitle2");
            m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        }
    }    
}

void SVMonitorview::setCurrentTime(const char * pszTime)
{
    if(m_pTime)
        m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + pszTime);
}

void SVMonitorview::setCurrentTime(const string &szTime)
{
    if(m_pTime)
        m_pTime->setText(SVResString::getResString("IDS_Refresh_Time") + szTime);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createGeneral()
{
    int nRow = m_pContent->numRows();
    m_pGeneral = new SVGeneral((WContainerWidget*)m_pContent->elementAt(nRow, 0));
    if(m_pGeneral)
    {
        string szTitle = SVResString::getResString("IDS_General_Infor_Title");
        m_pGeneral->setTitle(szTitle);
        WTable * pSub = m_pGeneral->getSubTable();
        if(pSub != NULL)
        {
            int nRow = pSub->numRows();
            new WText (SVResString::getResString("IDS_Device_Type"), pSub->elementAt(nRow, 0));
            m_pDeviceType = new WText("", pSub->elementAt(nRow, 1));
            
            nRow ++;
            new WText (SVResString::getResString("IDS_Depends_On"),  pSub->elementAt(nRow, 0));
            m_pDependsCell = pSub->elementAt(nRow, 1);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createDelOperate()
{
    m_pDel = new WImage("../icons/del.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pDel)
    {
        m_pDel->setStyleClass("imgbutton");
        m_pDel->setToolTip(SVResString::getResString("IDS_Delete_Select_Monitor_Tip"));
        WObject::connect(m_pDel, SIGNAL(clicked()), this, SLOT(delSelMonitor()));
    }
}

void SVMonitorview::createCopyPaste()
{
    m_pCopy = new WImage("../icons/copy.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pCopy)
    {
        m_pCopy->setStyleClass("imgbutton");
        m_pCopy->setToolTip(SVResString::getResString("IDS_Copy"));
        WObject::connect(m_pCopy, SIGNAL(clicked()), "showbar();", this, SLOT(copySelMonitor()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    m_pPaste = new WImage("../icons/paste.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pPaste)
    {
        m_pPaste->setStyleClass("imgbutton");
        m_pPaste->setToolTip(SVResString::getResString("IDS_Past"));
        WObject::connect(m_pPaste, SIGNAL(clicked()), "showbar();", this, SLOT(PastMonitor()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createSelOperate()
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
void SVMonitorview::createEnableOperate()
{
    m_pEnable = new WImage("../icons/enable.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pEnable)
    {
        m_pEnable->setStyleClass("imgbutton");
        m_pEnable->setToolTip(SVResString::getResString("IDS_Enable_Monitor_Tip"));
        WObject::connect(m_pEnable, SIGNAL(clicked()), this, SLOT(enableSel()));
    }

    m_pDisable = new WImage("../icons/disable.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pDisable)
    {
        m_pDisable->setStyleClass("imgbutton");
        m_pDisable->setToolTip(SVResString::getResString("IDS_Disable_Monitor_Tip"));
        WObject::connect(m_pDisable, SIGNAL(clicked()), this, SLOT(disableSel()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createRefreshOperate()
{
    m_pRefresh = new WImage("../icons/refresh.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pRefresh)
    {
        m_pRefresh->setToolTip(SVResString::getResString("IDS_Monitor_Refresh_Tip"));
        m_pRefresh->setStyleClass("imgbutton");
        WObject::connect(m_pRefresh, SIGNAL(clicked()), this, SLOT(refreshMonitors()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createOperate()
{
    int nRow = m_pMonitor->createSubTable()->numRows();
    m_pOperate = new WTable((WContainerWidget*)m_pMonitor->createSubTable()->elementAt(nRow, 0));
    if (m_pOperate)
    {
        m_pOperate->setStyleClass("t3");

        createSelOperate();
        createEnableOperate();
        createRefreshOperate();
        createDelOperate();
        createCopyPaste();
        m_pSort = new WImage("../icons/sort.gif", (WContainerWidget *)m_pOperate->elementAt(0, 0));
        if(m_pSort)
        {
            m_pSort->setToolTip(SVResString::getResString("IDS_Sort"));
            m_pSort->setStyleClass("imgbutton");
            WObject::connect(m_pSort, SIGNAL(clicked()), "showbar();", this, SLOT(sortMonitors()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        m_pAdd = new WPushButton(SVResString::getResString("IDS_Add_Monitor"), (WContainerWidget *)m_pOperate->elementAt(0, 1));
        m_pOperate->elementAt(0, 1)->setContentAlignment(AlignTop | AlignRight);
        if (m_pAdd)
        {
            m_pAdd->setStyleClass("wizardbutton");
            m_pAdd->setToolTip(SVResString::getResString("IDS_Add_Monitor"));
            WObject::connect(m_pAdd, SIGNAL(clicked()), "showbar();", this, SLOT(addMonitor()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createMonitor()
{
    int nRow = m_pContent->numRows();
    m_pMonitor = new SVShowTable((WContainerWidget*)m_pContent->elementAt(nRow, 0));
    if(m_pMonitor)
    {
        m_pMonitor->setTitle(SVResString::getResString("IDS_Monitor_List_Title").c_str());
        createMonitorList();

        int nRow = m_pMonitor->createSubTable()->numRows();
        m_pHasNoChild = new WText( "<BR>" + SVResString::getResString("IDS_MONITOR_LIST_IS_NULL"), m_pMonitor->createSubTable()->elementAt(nRow, 0));
        m_pMonitor->createSubTable()->elementAt(nRow, 0)->setContentAlignment(AlignCenter);
        if(m_pHasNoChild)
            m_pHasNoChild->setStyleClass("required");

        createOperate();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createMonitorList()
{
    int nRow = m_pMonitor->createSubTable()->numRows();
    m_pMonitorList = new WTable((WContainerWidget*)m_pMonitor->createSubTable()->elementAt(nRow, 0));
    if(m_pMonitorList)
    {
        m_pMonitorList->setStyleClass("t3");
        new WText("", (WContainerWidget *)m_pMonitorList->elementAt(0, 0));
        new WText(SVResString::getResString("IDS_State"), (WContainerWidget *)m_pMonitorList->elementAt(0, 1));
        new WText(SVResString::getResString("IDS_State_Description"), (WContainerWidget *)m_pMonitorList->elementAt(0, 2));
        new WText(SVResString::getResString("IDS_Name"), (WContainerWidget *)m_pMonitorList->elementAt(0, 3));
        new WText(SVResString::getResString("IDS_Edit"), (WContainerWidget *)m_pMonitorList->elementAt(0, 4));
        new WText(SVResString::getResString("IDS_Refresh_Tip"), (WContainerWidget *)m_pMonitorList->elementAt(0, 5));
        new WText(SVResString::getResString("IDS_Table_Col_Last_Refresh"), (WContainerWidget *)m_pMonitorList->elementAt(0, 6));
        m_pMonitorList->setCellPadding(0);
        m_pMonitorList->setCellSpaceing(0);
        m_pMonitorList->GetRow(0)->setStyleClass("t3title");
    }    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::AddMonitorList(string &szName, string &szMonitorIndex)
{
    if (m_pMonitorList)
    {        
        SVTableCell svCell;
        int nRow = m_pMonitorList->numRows();

        sv_dyn dyn ;
        bool bSucc = false;
        // —°‘Ò
        WCheckBox * pCheck = NULL;
        if(m_bHasEditRight || m_bHasDelRight || m_bHasRefreshRight) 
            pCheck = new WCheckBox("", (WContainerWidget *)m_pMonitorList->elementAt(nRow, 0));
        // ◊¥Ã¨

        WImage *pState = NULL;
        pState = new WImage("../icons/normal.gif", (WContainerWidget *)m_pMonitorList->elementAt(nRow, 1));
        if(pState)
        {     
            pState->setStyleClass("imgbutton");
            bSucc = GetSVDYN(szMonitorIndex, dyn, m_szIDCUser, m_szIDCPwd);
            if(bSucc)
            {
                switch(dyn.m_state)
                {
                case dyn_no_data:
                    pState->setImageRef("../icons/nodata.gif");
                    break;
                case dyn_normal:
                    pState->setImageRef("../icons/normal.gif");
                    break;
                case dyn_warnning:
                    m_nWarnCount ++;
                    pState->setImageRef("../icons/warnning.gif");
                    break;
                case dyn_error:
                case dyn_bad:
                    m_nErrCount ++;
                    pState->setImageRef("../icons/error.gif");
                    break;
                case dyn_disable:
                    m_nDisableCount ++;
                    pState->setImageRef("../icons/disablemonitor.gif");
                    break;
                }
                char chMsg[256] = {0};
                if(dyn.m_keeplaststatetime.GetDays() > 0 )
                {
                    sprintf(chMsg, "%s%d%s%d%s%d%s", m_szStateKeep.c_str(), 
                        dyn.m_keeplaststatetime.GetDays(), SVResString::getResString("IDS_Day").c_str(),
                        dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                        dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());
                }
                else
                {
                    if(dyn.m_keeplaststatetime.GetHours() > 0)
                    {
                        sprintf(chMsg, "%s%d%s%d%s", m_szStateKeep.c_str(), 
                            dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                            dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());                  
                    }
                    else
                    {
                        sprintf(chMsg, "%s%d%s",m_szStateKeep.c_str(), dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());

                    }
                }
                pState->setToolTip(chMsg);
            }
            else                    
                pState->setImageRef("../icons/nodata.gif"); 

            pState->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
            if(m_bHasEditRight) 
            {
                if(m_pbtnRefresh && m_pCurrentMonitor)
                {
                    string szDisable = "onclick='showDisable(\"2\", \"" + szMonitorIndex + "\", \"" + m_pCurrentMonitor->formName()
                        + "\", \"" + m_pbtnRefresh->getEncodeCmd("xclicked()") + "\")'";
                    strcpy(pState->contextmenu_, szDisable.c_str());
                }
            }
        }
        // √Ë ˆ
        WText *pDesc = NULL;
        string szDisplay("");
        if(dyn.m_displaystr != NULL)
            szDisplay += dyn.m_displaystr; 
        int nPos = static_cast<int>(szDisplay.find(",", 0));
        while (nPos > 0)
        {
            szDisplay = szDisplay.substr(0, nPos + 1) + "<BR>" + szDisplay.substr(nPos + 1, szDisplay.length() - nPos + 1);
            nPos += 6;
            nPos = static_cast<int>(szDisplay.find(",", nPos));
        }
        pDesc = new WText(szDisplay, (WContainerWidget *)m_pMonitorList->elementAt(nRow, 2));

        // √˚≥∆
        WText *pName = new WText(m_szDeviceName + ":" + szName, (WContainerWidget *)m_pMonitorList->elementAt(nRow, 3));
        if ( pName )
        {
            string szContent = "style='color:#669;cursor:pointer;' onmouseover='" \
                "this.style.textDecoration=\"underline\"' " \
                "onmouseout='this.style.textDecoration=\"none\"'' onclick = 'window.open(\"SimpleReport.exe?id=" + szMonitorIndex + "\");'";
            sprintf(pName->contextmenu_,  szContent.c_str());
            pName->setToolTip(szName);
        }

        // ±‡º≠
        WImage * pEdit = NULL;
        if(m_bHasEditRight) 
            pEdit = new WImage("../icons/edit.gif", (WContainerWidget *)m_pMonitorList->elementAt(nRow, 4));
        if (pEdit)
        {
            pEdit->setStyleClass("imgbutton");
            if(m_pbtnEdit && m_pCurrentMonitor)
            {
                string szEditMonitor = "onclick='currentoperate(\"" + szMonitorIndex + "\", \"" + m_pCurrentMonitor->formName()
                + "\", \"" + m_pbtnEdit->getEncodeCmd("xclicked()") + "\")'";

                strcpy(pEdit->contextmenu_, szEditMonitor.c_str());
            }
            pEdit->setToolTip(SVResString::getResString("IDS_Monitor_Edit_Tip"));
        }

        // À¢–¬
        WImage *pRefresh = NULL;
        if(m_bHasRefreshRight) 
            pRefresh = new WImage("../icons/refresh.gif", (WContainerWidget *)m_pMonitorList->elementAt(nRow, 5));
        if(pRefresh)
        {
            pRefresh->setToolTip(SVResString::getResString("IDS_Monitor_Refresh_Tip"));
            if(m_pbtnRefresh && m_pCurrentMonitor)
            {
                string szRefreshMonitor = "onclick='refreshmonitor(\"" + szMonitorIndex + "\", \"" + m_pCurrentMonitor->formName()
                + "\", \"" + m_pbtnRefresh->getEncodeCmd("xclicked()") + "\")'";
                strcpy(pRefresh->contextmenu_, szRefreshMonitor.c_str());
            }
            pRefresh->setStyleClass("imgbutton");
        }

        // ◊Ó∫Û∏¸–¬
        WText *pLast;
        if(bSucc)
        {
            svutil::TTime tmptime;
            if(tmptime != dyn.m_time)
                pLast = new WText(dyn.m_time.Format(), (WContainerWidget *)m_pMonitorList->elementAt(nRow, 6));
            else
                pLast = new WText("", (WContainerWidget *)m_pMonitorList->elementAt(nRow, 6));
        }
        else
            pLast = new WText("", (WContainerWidget *)m_pMonitorList->elementAt(nRow, 6));

        if((nRow + 1) % 2 == 0)
            m_pMonitorList->GetRow(nRow)->setStyleClass("tr1");
        else
            m_pMonitorList->GetRow(nRow)->setStyleClass("tr2");

        if(pCheck)
        {
            svCell.setType(adCheckBox);
            svCell.setValue(pCheck);
            svCell.setTag(dyn.m_state);
            svCell.setProperty(szName.c_str());
            m_svMonitorList.WriteCell(szMonitorIndex, 0, svCell);
            SVTableRow *pRow = m_svMonitorList.Row(szMonitorIndex);
            if (pRow)
            {
                pRow->setProperty(szMonitorIndex.c_str());
            }
        }
        if(pState)
        {
            svCell.setType(adImage);
            svCell.setValue(pState);
            m_svMonitorList.WriteCell(szMonitorIndex, 1, svCell);
        }
        if(pName)
        {
            svCell.setType(adText);
            svCell.setValue(pName);
            svCell.setProperty(szName.c_str());
            m_svMonitorList.WriteCell(szMonitorIndex, 3, svCell);            
        }
        if(pDesc)
        {
            svCell.setType(adText);
            svCell.setValue(pDesc);
            m_svMonitorList.WriteCell(szMonitorIndex, 2, svCell);
        }
        if(pLast)
        {
            svCell.setType(adText);
            svCell.setValue(pLast);
            m_svMonitorList.WriteCell(szMonitorIndex, 6, svCell);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::AddMonitorView(string &szName, string &szMonitorIndex)
{
    string szParentID = FindParentID(szMonitorIndex);
    if(szParentID == m_szDeviceIndex)
    {
        //if(m_pHasNoChild)
        //    m_pHasNoChild->show();
        m_nMonitorCount ++;
        AddMonitorList(szName, szMonitorIndex);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::selNone()
{
    if(!m_svMonitorList.empty())
    {
        for(row it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::selAll()
{ 
    if(!m_svMonitorList.empty())
    {
        for(row it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::invertSel()
{  
    if(!m_svMonitorList.empty())
    {
        for(row it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::delSelMonitor()
{
    if(!m_svMonitorList.empty())
    {
        for(row it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
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
                                string szDelFunc = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Monitor_Confirm") + "\",'"  +
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::delSel()
{
	//string strDeleteMonitorName;
    string szMsg("");
    if(!m_svMonitorList.empty())
    {
DelMonitor:
        row it = NULL;
        for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szMonitorID = (*it).second.getProperty();
                        string szName = pcell->Property();
                        
                        int nType = Tree_MONITOR, nOperate = SV_DELETE;
                        szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Monitor_Title") + 
                            "(Index)" + szMonitorID + "---" + SVResString::getResString("IDS_Name") + ":" +
                            szName + "---parent id is " + m_szDeviceIndex + "---" + 
                            SVResString::getResString("IDS_Name") + ":" + m_szDeviceName;

                        if(m_pMain)
                            m_pMain->AddOperaterLog(nOperate, nType, szMsg);
                        
                        int nRow = ((WTableCell*)(((WCheckBox*)pcell->Value())->parent()))->row();
                        m_pMonitorList->deleteRow(nRow);
                        m_svMonitorList.DelRow(szMonitorID);            

                        DeleteSVMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
                        DeleteTable(szMonitorID, m_szIDCUser, m_szIDCPwd);
                        m_nMonitorCount --;
                        goto DelMonitor;
                    }
                }
            }
        }
    }
    if(m_pMonitorList)
    {
        int nRow = m_pMonitorList->numRows();
        if(nRow > 1)
        {
            for(int i = 1; i<= nRow - 1; i++)
            {
                if( i % 2 == 0)
                    m_pMonitorList->GetRow(i)->setStyleClass("tr2");
                else
                    m_pMonitorList->GetRow(i)->setStyleClass("tr1");
            }
        }
        else
        {
            if(m_pHasNoChild)
                m_pHasNoChild->show();
        }
    }
    refreshState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::addMonitor()
{
    if(!m_szDeviceType.empty() && !m_szDeviceIndex.empty())
        emit AddNewMonitor(m_szDeviceType,m_szDeviceIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createHideButton()
{
    int nRow = numRows();
    m_pbtnHide = new WPushButton("hide button", (WContainerWidget*)elementAt(nRow,0));
    if(m_pbtnHide)
    {
        WObject::connect(m_pbtnHide, SIGNAL(clicked()), this, SLOT(disableSucc()));
        m_pbtnHide->hide();
    }

    m_pBtnHideDel = new WPushButton("hide button", (WContainerWidget*)elementAt(nRow,0));
    if(m_pBtnHideDel)
    {
        WObject::connect(m_pBtnHideDel, SIGNAL(clicked()), this, SLOT(delSel()));
        m_pBtnHideDel->hide();
    }

    m_pbtnRefresh = new WPushButton("hide button", (WContainerWidget*)elementAt(nRow,0));
    if(m_pbtnRefresh)
    {        
        WObject::connect(m_pbtnRefresh, SIGNAL(clicked()), this, SLOT(changeState()));
        m_pbtnRefresh->hide();
    }

    m_pbtnEdit = new WPushButton("hide button", (WContainerWidget*)elementAt(nRow,0));
    if(m_pbtnEdit)
    {
        WObject::connect(m_pbtnEdit, SIGNAL(clicked()), this, SLOT(editSelMonitor()));
        m_pbtnEdit->hide();
    }

    m_pCurrentMonitor = new WLineEdit("", (WContainerWidget*)elementAt(nRow,0));
    if(m_pCurrentMonitor)
        m_pCurrentMonitor->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::disableSucc()
{
    if(!m_svMonitorList.empty())
    {
        row it = NULL;
        for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
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
                            sv_dyn dyn ;
                            if(GetSVDYN(szMonitorID, dyn, m_szIDCUser, m_szIDCPwd))
                            {
                                switch(dyn.m_state)
                                {
                                case dyn_no_data:
                                    ((WImage*)pcell->Value())->setImageRef("../icons/nodata.gif");
                                    break;
                                case dyn_normal:
                                    ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                                    break;
                                case dyn_warnning:
                                    m_nWarnCount ++;
                                    ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                                    break;
                                case dyn_error:
                                case dyn_bad:
                                    m_nErrCount ++;
                                    ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                                    break;
                                case dyn_disable:
                                    m_nDisableCount ++;
                                    ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                                    break;                                    
                                }
                                char chMsg[256] = {0};
                                if(dyn.m_keeplaststatetime.GetDays() > 0 )
                                {
                                    sprintf(chMsg, "%s%d%s%d%s%d%s", m_szStateKeep.c_str(), 
                                        dyn.m_keeplaststatetime.GetDays(), SVResString::getResString("IDS_Day").c_str(),
                                        dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                                        dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());
                                }
                                else
                                {
                                    if(dyn.m_keeplaststatetime.GetHours() > 0)
                                    {
                                        sprintf(chMsg, "%s%d%s%d%s", m_szStateKeep.c_str(), 
                                            dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                                            dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());                  
                                    }
                                    else
                                    {
                                        sprintf(chMsg, "%s%d%s",m_szStateKeep.c_str(), dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());

                                    }
                                }
                                ((WImage*)pcell->Value())->setToolTip(chMsg);

                                string szDisplay ("");
                                if(dyn.m_displaystr != NULL)
                                    szDisplay += dyn.m_displaystr;
                                int nPos = static_cast<int>(szDisplay.find(",", 0));
                                while (nPos > 0)
                                {
                                    szDisplay = szDisplay.substr(0, nPos + 1) + "<BR>" + szDisplay.substr(nPos + 1, szDisplay.length() - nPos + 1);
                                    nPos += 6;
                                    nPos = static_cast<int>(szDisplay.find(",", nPos));
                                }
                                pcell = (*it).second.Cell(2);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(szDisplay);
                                pcell = (*it).second.Cell(6);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(dyn.m_time.Format());
                            }
                        }
                    }
                }
            }
        }
    }
    refreshState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::enableSel()
{   
    list<string> lsSel;
    if(!m_svMonitorList.empty())
    {
        row it = NULL;
        for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {                    
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        if(isMonitorDisable(szDeviceID) != 0)
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
            int nSize = 0;
            for(lsItem = lsSel.begin(); lsItem != lsSel.end(); lsItem++)
            {
                nSize = static_cast<int>((*lsItem).length()) + 2;
                char * pszIndex = new char[nSize];
                if(pszIndex)
                {
                    memset(pszIndex, 0, nSize);
                    strcpy(pszIndex, (*lsItem).c_str());
                    if(!::PushMessage(szQueueName, "SV_INDEX", pszIndex, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("Disable Monitor: PushMessage into queue failed!");
                    delete []pszIndex;
                }
            }
            char pEnd[2] = {0};
            if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("Disable Monitor(End label): PushMessage into queue failed!");
            if(m_pbtnHide)
            {
                string szCmd = m_pbtnHide->getEncodeCmd("xclicked()");
                if(!szCmd.empty())
                {
                    string szDisable = "showDisableUrl('disable.exe?disabletype=2&operatetype=1&queuename=" + 
                        szQueueName + "', '" + szCmd + "');";                    
                    WebSession::js_af_up = szDisable;
                }
            }
        }
        else
        {
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Monitor_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::disableSel()
{   
    list<string> lsSel;
    if(!m_svMonitorList.empty())
    {
        row it = NULL;
        for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {                    
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        if(isMonitorDisable(szDeviceID) == 0)
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
            int nSize = 0;
            for(lsItem = lsSel.begin(); lsItem != lsSel.end(); lsItem++)
            {
                nSize = static_cast<int>((*lsItem).length()) + 2;
                char * pszIndex = new char[nSize];
                if(pszIndex)
                {
                    memset(pszIndex, 0, nSize);
                    strcpy(pszIndex, (*lsItem).c_str());
                    if(!::PushMessage(szQueueName, "SV_INDEX", pszIndex, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("Disable Monitor: PushMessage into queue failed!");
                    delete []pszIndex;
                }
                //szSelIndex += (*lsItem);
                //szSelIndex += ",";
            }
            char pEnd[2] = {0};
            if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("Disable Monitor(End label): PushMessage into queue failed!");
            if(m_pbtnHide)
            {
                string szCmd = m_pbtnHide->getEncodeCmd("xclicked()");
                if(!szCmd.empty())
                {
                    string szDisable = "showDisableUrl('disable.exe?disabletype=2&operatetype=0&queuename=" +
                        szQueueName + "', '" + szCmd + "');";
                    WebSession::js_af_up = szDisable;
                }
            }
        }
        else
        {
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Monitor_Can_not_Disable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
        }
    }
}

bool SVMonitorview::isParentEdit(string szIndex)
{
    if(m_szDeviceIndex == szIndex)
        return true;
    string szParent = FindParentID(m_szDeviceIndex);
    while(!szParent.empty())
    {
        if(szParent == szIndex)
            return true;
        szParent = FindParentID(szParent);
        if(IsSVSEID(szParent))
            break;
    }
    return false;
}

bool SVMonitorview::isInDevice(string szIndex)
{
    if(m_szDeviceIndex == szIndex)
        return true;
    return false;
}

void SVMonitorview::refreshNamePath()
{
    OBJECT objDevice = GetEntity(m_szDeviceIndex,  m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDesc ("");
            FindNodeValue(mainnode, "sv_name", m_szDeviceName);
            FindNodeValue(mainnode, "sv_dependson", m_szDependsOnID);
            FindNodeValue(mainnode, "sv_description", szDesc);
            if(m_pGeneral)
                m_pGeneral->setDescription(szDesc);
            string szParent = FindParentID(m_szDeviceIndex);
            list<WText*>::iterator itPath;
            for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
                m_GroupName.removeMappings((*itPath));

            if(m_pDependDevice)
                m_DeviceName.removeMappings(m_pDependDevice);

            m_lsPath.clear();
            m_pTitleCell->clear();
            m_pDependsCell->clear();
            m_pDependDevice= NULL;

            list<base_param> lsPath;
            list<base_param>::iterator pathItem;
            makeGroupPath(szParent, lsPath);
            while(lsPath.size())
            {
                base_param svparam = lsPath.back();
                lsPath.pop_back();

                WText *pPath = new WText(svparam.szName, m_pTitleCell);
                if(pPath)
                {
                    pPath->setStyleClass("tgrouptitle") ;
                    WObject::connect(pPath, SIGNAL(clicked()), &m_GroupName, SLOT(map()));
                    m_GroupName.setMapping(pPath, svparam.szIndex);
                    m_lsPath.push_back(pPath);
                }

                WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitleCell);
                if(pTemp)
                    pTemp->setStyleClass("tgrouptitle2") ;
            }
            lsPath.clear();
            if(!m_szDependsOnID.empty() && m_szDependsOnID != "-2" && m_pDependsCell)
            {
                makeMonitorPath(m_szDependsOnID, lsPath);
                while(lsPath.size() > 2)
                {
                    base_param svparam = lsPath.back();
                    lsPath.pop_back();
                    WText *pPath = new WText(svparam.szName, m_pDependsCell);
                    if(pPath)
                    {
                        pPath->setStyleClass("fontlink") ;
                        WObject::connect(pPath, SIGNAL(clicked()), &m_GroupName, SLOT(map()));
                        m_GroupName.setMapping(pPath, svparam.szIndex);
                        m_lsPath.push_back(pPath);
                    }

                    new WText("&nbsp;:&nbsp;", m_pDependsCell);
                }
                if(lsPath.size() >= 2)
                {
                    base_param svparam = lsPath.back();
                    lsPath.pop_back();
                    m_pDependDevice = new WText(svparam.szName, m_pDependsCell);
                    if(m_pDependDevice)
                    {
                        WObject::connect(m_pDependDevice, SIGNAL(clicked()),  &m_DeviceName, SLOT(map()));
                        m_DeviceName.setMapping(m_pDependDevice, svparam.szIndex);
                        m_pDependDevice->setStyleClass("fontlink") ;
                    }

                    new WText("&nbsp;:&nbsp;", m_pDependsCell);

                    svparam = lsPath.back();
                    lsPath.pop_back();
                    WText * pMonitor = new WText(svparam.szName, m_pDependsCell);
                    if(pMonitor)
                    {
                        string szContent = "onclick = 'window.open(\"SimpleReport.exe?id=" + svparam.szIndex + "\");'";
                        sprintf(pMonitor->contextmenu_, szContent.c_str());
                        pMonitor->setStyleClass("fontlink");
                    }
                }
            }

            WText * pTitle = new WText(m_szDeviceName, m_pTitleCell);
            if(pTitle)
                pTitle->setStyleClass("tgrouptitle2") ;
            row it = NULL;
            for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
            {
                SVTableCell *pcell = (*it).second.Cell(3);
                if ( pcell )
                {
                    if (pcell->Type() == adText)
                    {
                        ((WText*)pcell->Value())->setText(m_szDeviceName + ":" + pcell->Property());
                    }
                }
            }

        }
        CloseEntity(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::enterDevice(string &szDeviceIndex)
{
    removeMapping();
    if(m_pMonitorList)
    {
        while ( m_pMonitorList->numRows() > 1)
        {
            m_pMonitorList->deleteRow(m_pMonitorList->numRows() - 1);
        }
    }
    m_svMonitorList.clear();
    m_szDeviceIndex = szDeviceIndex;
    enumDeviceRight();
    m_nErrCount = 0;
    m_nDisableCount = 0;
    m_nWarnCount = 0;
    m_nMonitorCount = 0;
    enumMonitor(m_szDeviceIndex);

    char szState[512] = {0};
    sprintf(szState, "%s%s%d, %s%d, %s%d, %s%d", 
        m_szDeviceState.c_str(),
        SVResString::getResString("IDS_Monitor_Count").c_str(),   m_nMonitorCount, 
        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), m_nDisableCount,
        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), m_nErrCount, 
        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), m_nWarnCount);

    
    if(m_pGeneral)
    {
        m_pGeneral->setTitle(m_szDeviceName);
        m_pGeneral->setState(string(szState));
    }

    m_szDeviceShowType = getDeviceShowType(m_szDeviceType);
    if(m_pDeviceType)
        m_pDeviceType->setText(m_szDeviceShowType);
    changeOperateState();
}

void SVMonitorview::reloadCurrentDevice()
{
    row it = NULL;
    SVTableCell *pcell = NULL;

    sv_dyn dyn;

    m_nWarnCount = 0;
    m_nErrCount = 0;
    m_nDisableCount = 0;

    for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
    {
        string szMonitorID = (*it).second.getProperty();
        
        OBJECT objMonitor = GetMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
        if(objMonitor != INVALID_VALUE)
        {
            MAPNODE node = GetMonitorMainAttribNode(objMonitor);
            if(node != INVALID_VALUE)
            {
                string szName ("");
                FindNodeValue(node, "sv_name", szName);
                pcell = (*it).second.Cell(3);
                if(pcell)
                    pcell->setProperty(szName.c_str());
            }
            CloseMonitor(objMonitor);
        }
        if(GetSVDYN(szMonitorID, dyn, m_szIDCUser, m_szIDCPwd))
        {
            pcell = (*it).second.Cell(1);
            switch(dyn.m_state)
            {
            case dyn_no_data:
                if(pcell && pcell->Type() == adImage)
                    ((WImage*)pcell->Value())->setImageRef("../icons/nodata.gif");
                break;
            case dyn_normal:
                if(pcell && pcell->Type() == adImage)
                    ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                break;
            case dyn_warnning:
                m_nWarnCount ++;
                if(pcell && pcell->Type() == adImage)
                    ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                break;
            case dyn_error:
            case dyn_bad:
                m_nErrCount ++;
                if(pcell && pcell->Type() == adImage)
                    ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                break;
            case dyn_disable:
                m_nDisableCount ++;
                if(pcell && pcell->Type() == adImage)
                    ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                break;
            }
            char chMsg[256] = {0};
            if(dyn.m_keeplaststatetime.GetDays() > 0 )
            {
                sprintf(chMsg, "%s%d%s%d%s%d%s", m_szStateKeep.c_str(), 
                    dyn.m_keeplaststatetime.GetDays(), SVResString::getResString("IDS_Day").c_str(),
                    dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                    dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());
            }
            else
            {
                if(dyn.m_keeplaststatetime.GetHours() > 0)
                {
                    sprintf(chMsg, "%s%d%s%d%s", m_szStateKeep.c_str(), 
                        dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                        dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());                  
                }
                else
                {
                    sprintf(chMsg, "%s%d%s",m_szStateKeep.c_str(), dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());

                }
            }
            ((WImage*)pcell->Value())->setToolTip(chMsg);
            string szMonitorIndex = szMonitorID;
            string szDisplay ("");
            if(dyn.m_displaystr != NULL)
                szDisplay += dyn.m_displaystr;
            int nPos = static_cast<int>(szDisplay.find(",", 0));
            while (nPos > 0)
            {
                szDisplay = szDisplay.substr(0, nPos + 1) + "<BR>" + szDisplay.substr(nPos + 1, szDisplay.length() - nPos + 1);
                nPos += 6;
                nPos = static_cast<int>(szDisplay.find(",", nPos));
            }
            pcell = (*it).second.Cell(2);
            if(pcell && pcell->Type() == adText)
                ((WText*)pcell->Value())->setText(szDisplay);
            pcell = (*it).second.Cell(6);
            if(pcell && pcell->Type() == adText)
                ((WText*)pcell->Value())->setText(dyn.m_time.Format());
        }
    }
    refreshNamePath();
}
void SVMonitorview::refreshState()
{
    row it = NULL;
    sv_dyn dyn;
    int nState = dyn_normal;
    m_nWarnCount = 0;
    m_nErrCount = 0;
    m_nDisableCount = 0;
    for(it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
    {
        string szMonitorID = (*it).second.getProperty();
        if(GetSVDYNNODisplayString(szMonitorID, dyn, m_szIDCUser, m_szIDCPwd))
        {
            switch(dyn.m_state)
            {
            case dyn_no_data:
            case dyn_normal:
                break;
            case dyn_warnning:
                if( nState!= dyn_error || nState != dyn_bad)
                    nState = dyn_warnning;
                m_nWarnCount ++;
                break;
            case dyn_error:
            case dyn_bad:
                nState = dyn_error;
                m_nErrCount ++;
                break;
            case dyn_disable:
                m_nDisableCount ++;
                break;
            }
        }        
    }

    OBJECT objDevice = GetEntity(m_szDeviceIndex,  m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDesc ("");
            m_szDeviceName = "";
            m_szDeviceState = "";
            FindNodeValue(mainnode, "sv_name", m_szDeviceName);
            FindNodeValue(mainnode, "sv_desc", m_szDeviceDesc);
            m_szDeviceType = "";
            FindNodeValue(mainnode, "sv_devicetype", m_szDeviceType);
            FindNodeValue(mainnode, "sv_description", szDesc);

            string szDisable ("");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                m_szDeviceState += SVResString::getResString("IDS_Device_Disable_Forver");
                m_szDeviceState += ", ";
            }
            else if( szDisable == "time")
            {
                m_szDeviceState = SVResString::getResString("IDS_Device_Disable_Temprary") + ", ";
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
                    m_szDeviceState += szMsg;
                    m_szDeviceState += ", ";
                }
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    char szMsg[256] = {0};
                    sprintf(szMsg, SVResString::getResString("IDS_End_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
                    m_szDeviceState += szMsg;
                    m_szDeviceState += ", ";       
                    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

                    svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime > ttend)
                        m_szDeviceState = "";                        
                }
            }
        }
        CloseEntity(objDevice);
    }

    char szState[512] = {0};
    sprintf(szState, "%s%s%d, %s%d, %s%d, %s%d", 
        m_szDeviceState.c_str(),
        SVResString::getResString("IDS_Monitor_Count").c_str(),   m_nMonitorCount, 
        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), m_nDisableCount,
        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), m_nErrCount, 
        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), m_nWarnCount);

    if(m_pGeneral)
        m_pGeneral->setState(string(szState));

    emit ChangeDeviceState(m_szDeviceIndex, nState);
}

void SVMonitorview::removeMapping()
{
    list<WText*>::iterator itPath;
    for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
        m_GroupName.removeMappings((*itPath));

    if(m_pDependDevice)
        m_DeviceName.removeMappings(m_pDependDevice);

    m_lsPath.clear();
    m_pTitleCell->clear();
    m_pDependsCell->clear();
    m_pDependDevice= NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::changeDelState()
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
void SVMonitorview::changeEnableState()
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
void SVMonitorview::changeRefreshState()
{
    if(!m_bHasRefreshRight)
    {
        if(m_pRefresh)                  m_pRefresh->hide();
    }
    else
    {
        if(m_pRefresh)                  m_pRefresh->show();           
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::changeSelState()
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

void SVMonitorview::enumDeviceRight()
{
    m_bHasAddRight = true; 
    m_bHasEditRight = true;
    m_bHasDelRight = true;
    m_bHasRefreshRight = true;
    if(m_pSVUser)
    {
        m_bHasAddRight = m_pSVUser->haveUserRight(m_szDeviceIndex, "addmonitor");
        m_bHasEditRight = m_pSVUser->haveUserRight(m_szDeviceIndex, "editmonitor");
        m_bHasDelRight = m_pSVUser->haveUserRight(m_szDeviceIndex, "delmonitor");
        m_bHasRefreshRight = m_pSVUser->haveUserRight(m_szDeviceIndex, "monitorrefresh");
    }
    else
    {
        m_bHasAddRight = false; 
        m_bHasEditRight = false;
        m_bHasDelRight = false;
        m_bHasRefreshRight = false;
    }
}

void SVMonitorview::changeCopyPasteState()
{
    if(m_pCopy && m_bHasEditRight)
        m_pCopy->show();
    else if(m_pCopy && !m_bHasEditRight)
        m_pCopy->hide();

    if(m_pPaste && m_bHasAddRight)
        m_pPaste->show();
    else if(m_pPaste && !m_bHasAddRight)
        m_pPaste->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::changeOperateState()
{
    if(m_pAdd && !m_bHasAddRight)        m_pAdd->hide();
    else if(m_pAdd && m_bHasAddRight)    m_pAdd->show();

    changeDelState();
    changeSelState();
    changeRefreshState();
    changeEnableState();
    changeCopyPasteState();
}

string SVMonitorview::getDeviceShowType(string &szDeviceType)
{
    string szShowType ("");
    OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            if(!FindNodeValue(node, "sv_label", szShowType))
                FindNodeValue(node, "sv_name", szShowType);
            else
                szShowType = SVResString::getResString(szShowType.c_str());
        }
        CloseEntityTemplet(objDevice);
    }
    return szShowType;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::enumMonitor(string &szIndex)
{
    map<int, base_param, less<int> > sortList;
    map<int, base_param, less<int> >::iterator lsItem;

    if(!szIndex.empty())
    {
        OBJECT objDevice = GetEntity(szIndex,  m_szIDCUser, m_szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            if(mainnode != INVALID_VALUE)
            {
                string szDesc (""), szDisable ("");
                m_szDependsOnID  = "";
                m_szDeviceName = "";
                m_szDeviceState = "";
                m_szDeviceType = "";
                FindNodeValue(mainnode, "sv_name", m_szDeviceName);
                FindNodeValue(mainnode, "sv_desc", m_szDeviceDesc);                
                FindNodeValue(mainnode, "sv_devicetype", m_szDeviceType);
                FindNodeValue(mainnode, "sv_description", szDesc);
                FindNodeValue(mainnode, "sv_dependson", m_szDependsOnID);
                FindNodeValue(mainnode, "sv_disable", szDisable);
                FindNodeValue(mainnode, "sv_network", m_szNetworkSet);
                if(szDisable == "true")
                {
                    m_szDeviceState += SVResString::getResString("IDS_Device_Disable_Forver");
                    m_szDeviceState += ", ";
                }
                else if( szDisable == "time")
                {
                    m_szDeviceState = SVResString::getResString("IDS_Device_Disable_Temprary") + ", ";
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
                        m_szDeviceState += szMsg;
                        m_szDeviceState += ", ";
                    }
                    if(!szEndTime.empty())
                    {
                        sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                        char szMsg[256] = {0};
                        sprintf(szMsg, SVResString::getResString("IDS_End_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
                        m_szDeviceState += szMsg;
                        m_szDeviceState += ", ";       
                        svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

                        svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                        if(ttime > ttend)
                            m_szDeviceState = "";                        
                    }
                }

                if(m_pGeneral)
                    m_pGeneral->setDescription(szDesc);

                string szParent = FindParentID(szIndex);
                list<WText*>::iterator itPath;
                for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
                    m_GroupName.removeMappings((*itPath));

                if(m_pDependDevice)
                    m_DeviceName.removeMappings(m_pDependDevice);

                m_lsPath.clear();
                m_pTitleCell->clear();
                m_pDependsCell->clear();
                m_pDependDevice= NULL; 

                list<base_param> lsPath;
                list<base_param>::iterator pathItem;
                makeGroupPath(szParent, lsPath);
                
                while(lsPath.size())
                {
                    base_param svparam = lsPath.back();
                    lsPath.pop_back();

                    WText *pPath = new WText(svparam.szName, m_pTitleCell);
                    if(pPath)
                    {
                        pPath->setStyleClass("tgrouptitle") ;
                        WObject::connect(pPath, SIGNAL(clicked()), &m_GroupName, SLOT(map()));
                        m_GroupName.setMapping(pPath, svparam.szIndex);
                        m_lsPath.push_back(pPath);
                    }

                    WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitleCell);
                    if(pTemp)
                        pTemp->setStyleClass("tgrouptitle2") ;
                }
                WText * pTitle = new WText(m_szDeviceName, m_pTitleCell);
                if(pTitle)
                    pTitle->setStyleClass("tgrouptitle2") ;

                lsPath.clear();
                if(!m_szDependsOnID.empty() && m_szDependsOnID != "-2" && m_pDependsCell)
                {
                    makeMonitorPath(m_szDependsOnID, lsPath);
                    while(lsPath.size() > 2)
                    {
                        base_param svparam = lsPath.back();
                        lsPath.pop_back();
                        WText *pPath = new WText(svparam.szName, m_pDependsCell);
                        if(pPath)
                        {
                            pPath->setStyleClass("fontlink") ;
                            WObject::connect(pPath, SIGNAL(clicked()), &m_GroupName, SLOT(map()));
                            m_GroupName.setMapping(pPath, svparam.szIndex);
                            m_lsPath.push_back(pPath);
                        }

                        new WText("&nbsp;:&nbsp;", m_pDependsCell);
                    }
                    if(lsPath.size() >= 2)
                    {
                        base_param svparam = lsPath.back();
                        lsPath.pop_back();
                        m_pDependDevice = new WText(svparam.szName, m_pDependsCell);
                        if(m_pDependDevice)
                        {
                            WObject::connect(m_pDependDevice, SIGNAL(clicked()),  &m_DeviceName, SLOT(map()));
                            m_DeviceName.setMapping(m_pDependDevice, svparam.szIndex);
                            m_pDependDevice->setStyleClass("fontlink") ;
                        }

                        new WText("&nbsp;:&nbsp;", m_pDependsCell);

                        svparam = lsPath.back();
                        lsPath.pop_back();
                        WText * pMonitor = new WText(svparam.szName, m_pDependsCell);
                        if(pMonitor)
                        {
                            string szContent = "onclick = 'window.open(\"SimpleReport.exe?id=" + svparam.szIndex + "\");'";
                            sprintf(pMonitor->contextmenu_, szContent.c_str());
                            pMonitor->setStyleClass("fontlink");
                        }
                    }
                }
            }
            list<string> lsMonitorID;
            list<string>::iterator lstItem;
            if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
            {
                base_param monitor;
                string szMonitorId(""), szName (""), szIndex ("");
                int nIndex = 0;
                for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                {
                    szMonitorId = (*lstItem).c_str();
                    OBJECT objMonitor = GetMonitor(szMonitorId, m_szIDCUser, m_szIDCPwd);
                    if(objMonitor != INVALID_VALUE)
                    {
                        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
                        if(node != INVALID_VALUE)
                        {
                            szName = ""; szIndex = "";
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
                                nIndex ++;
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
    }

    if(sortList.size() > 0)
    {
        for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
            AddMonitorView(lsItem->second.szName,lsItem->second.szIndex); 
        if(m_pHasNoChild)
            m_pHasNoChild->hide();
    }
    else
    {
        if(m_pHasNoChild)
            m_pHasNoChild->show();
    }
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

void SVMonitorview::gotoDevice(const std::string szDeviceID)
{
    emit enterDependDevice(szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::editSelMonitor()
{
    if(m_pCurrentMonitor)
    {
        string szMonitorID = m_pCurrentMonitor->text();
        if(!szMonitorID.empty())
            emit EditMonitorByID(szMonitorID);
        else
            WebSession::js_af_up = "hiddenbar();";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::createControl()
{
    int nRow = m_pContent->numRows();
    WTable * pViewControl = new WTable((WContainerWidget*)m_pContent->elementAt(nRow, 0));
    if ( pViewControl )
    {
        pViewControl->setStyleClass("t3");
        // –¥À¿
        WPushButton * pBackParent = new WPushButton(SVResString::getResString("IDS_Operate_Back_Parent"), 
            (WContainerWidget *)pViewControl->elementAt(0 , 1));
        pViewControl->elementAt(0 , 1)->setContentAlignment(AlignTop | AlignRight);

        if(pBackParent)
        {
            pBackParent->setToolTip(SVResString::getResString("IDS_Operate_Back_Parent_Tip"));    
            WObject::connect(pBackParent, SIGNAL(clicked()), "showbar();", this, SLOT(BackParent()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
}

bool SVMonitorview::makeMonitorPath(string &szMonitorID, list<base_param> &lsPath)
{
    OBJECT objMonitor = GetMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        string szName ("");
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
            FindNodeValue(mainnode, "sv_name", szName);

        base_param baseparam ;
        baseparam.szIndex = szMonitorID;
        baseparam.szName = szName;
        lsPath.push_back(baseparam);
        CloseMonitor(objMonitor);
    }

    string szParentID = FindParentID(szMonitorID);
    if(!szParentID.empty())
    {
        OBJECT objDevice = GetEntity(szParentID, m_szIDCUser, m_szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {
            string szName ("");
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            if(mainnode != INVALID_VALUE)
                FindNodeValue(mainnode, "sv_name", szName);

            base_param baseparam ;
            baseparam.szIndex = szParentID;
            baseparam.szName = szName;
            lsPath.push_back(baseparam);
        }
        CloseEntity(objDevice);

        szParentID = FindParentID(szParentID);
        if(!szParentID.empty())
            makeGroupPath(szParentID, lsPath);
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVMonitorview::makeGroupPath(string &szGroupID,  list<base_param> &lsPath)
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
        return makeGroupPath(szParent, lsPath);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::BackParent()
{
    string szParentID = FindParentID(m_szDeviceIndex);
    emit BackDeviceParent(szParentID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::changeState()
{
    string szMonitorID = "";
    if(m_pCurrentMonitor)
        szMonitorID = m_pCurrentMonitor->text();
    SVTableRow *pRow = m_svMonitorList.Row(szMonitorID);
    if (pRow)
    {
        SVTableCell *pcell = pRow->Cell(1);
        if(pcell)
        {
            if(pcell->Type() == adImage)
            {
                sv_dyn dyn ;
                if(GetSVDYN(szMonitorID, dyn, m_szIDCUser, m_szIDCPwd))
                {
                    switch(dyn.m_state)
                    {
                    case dyn_no_data:
                        if(pcell->Tag() == dyn_warnning)
                            m_nWarnCount --;
                        else if(pcell->Tag() == dyn_bad ||pcell->Tag() == dyn_error)
                            m_nErrCount --;
                        else if(pcell->Tag() == dyn_disable)
                            m_nDisableCount --;
                        ((WImage*)pcell->Value())->setImageRef("../icons/nodata.gif");
                        break;
                    case dyn_normal:
                        ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                        break;
                    case dyn_warnning:
                        if(pcell->Tag() != dyn_warnning)
                            m_nWarnCount ++;
                        ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                        break;
                    case dyn_error:
                    case dyn_bad:
                        if(pcell->Tag() != dyn_bad ||pcell->Tag() != dyn_error)
                            m_nErrCount ++;
                        ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                        break;
                    case dyn_disable:
                        if(pcell->Tag() != dyn_disable)
                            m_nDisableCount ++;
                        ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                        break;
                    }
                    pcell->setTag(dyn.m_state);
                    char chMsg[256] = {0};
                    if(dyn.m_keeplaststatetime.GetDays() > 0 )
                    {
                        sprintf(chMsg, "%s%d%s%d%s%d%s", m_szStateKeep.c_str(), 
                            dyn.m_keeplaststatetime.GetDays(), SVResString::getResString("IDS_Day").c_str(),
                            dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                            dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());
                    }
                    else
                    {
                        if(dyn.m_keeplaststatetime.GetHours() > 0)
                        {
                            sprintf(chMsg, "%s%d%s%d%s", m_szStateKeep.c_str(), 
                                dyn.m_keeplaststatetime.GetHours(), SVResString::getResString("IDS_Hour").c_str(), 
                                dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());                  
                        }
                        else
                        {
                            sprintf(chMsg, "%s%d%s",m_szStateKeep.c_str(), dyn.m_keeplaststatetime.GetMinutes(), SVResString::getResString("IDS_Minute").c_str());

                        }
                    }
                    ((WImage*)pcell->Value())->setToolTip(chMsg);
                    string szMonitorIndex = szMonitorID;
                    string szDisplay ("");
                    if(dyn.m_displaystr != NULL)
                        szDisplay += dyn.m_displaystr;
                    int nPos = static_cast<int>(szDisplay.find(",", 0));
                    while (nPos > 0)
                    {
                        szDisplay = szDisplay.substr(0, nPos + 1) + "<BR>" + szDisplay.substr(nPos + 1, szDisplay.length() - nPos + 1);
                        nPos += 6;
                        nPos = static_cast<int>(szDisplay.find(",", nPos));
                    }
                    pcell = pRow->Cell(2);
                    if(pcell && pcell->Type() == adText)
                        ((WText*)pcell->Value())->setText(szDisplay);
                    pcell = pRow->Cell(6);
                    if(pcell && pcell->Type() == adText)
                        ((WText*)pcell->Value())->setText(dyn.m_time.Format());
                }
            }
        }
        int nState = getDeviceSimpleState(m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
        emit ChangeDeviceState(m_szDeviceIndex, nState);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string SVMonitorview::makeState(string &szMonitorID)
{
    string szState ("");
    OBJECT objMonitor = GetMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                szState += SVResString::getResString("IDS_Monitor_Disable_Forver");
                szState += "<BR>";
            }
            else if( szDisable == "time")
            {
                szState = SVResString::getResString("IDS_Monitor_Disable_Temprary") + "<BR>";
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
                    szState += "<BR>";
                }
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    char szMsg[256] = {0};
                    sprintf(szMsg, SVResString::getResString("IDS_End_Time").c_str(), nYear, nMonth, nDay, nHour, nMinute);
                    szState += szMsg;
                    szState += "<BR>";       
                    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

                    svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime > ttend)
                        szState= ""; 
                }
            }
        }
        CloseMonitor(objMonitor);
    }
    return szState;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorview::EditMonitorView(string &szName, string &szMonitorIndex)
{
    SVTableRow *pRow = m_svMonitorList.Row(szMonitorIndex);
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

void SVMonitorview::refreshMonitors()
{
    static const string szRefreshEnd = "Refresh_END";
    list<string> lsSelMonitor;
    list<string>::iterator lstItem;
    if(!m_svMonitorList.empty())
    {
        for(row it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        lsSelMonitor.push_back( pcell->Row());;
                    }
                }
            }
        }
    }
    string szQuery ("");
    if(lsSelMonitor.size() > 0)
    {
        string szQueueName(makeQueueName());
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
        string szRefreshQueue(getRefreshQueueName(m_szDeviceIndex));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
        for(lstItem = lsSelMonitor.begin(); lstItem != lsSelMonitor.end(); lstItem ++)
        {
            if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
            {
                szQuery += (*lstItem);
                szQuery += "\v";
            }
            else
            {
                int nSize = static_cast<int>((*lstItem).length()) + 2;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {  
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, (*lstItem).c_str());
                    if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("PushMessage into queue failed!");
                    delete []pszRefreshMonitor;
                }
            }
        }

        int nSize = static_cast<int>(szQuery.length()) + 2;
        char *pszRefreshMonitor = new char[nSize];
        if(pszRefreshMonitor)
        {
            memset(pszRefreshMonitor, 0, nSize);
            strcpy( pszRefreshMonitor, szQuery.c_str());
            char *pPos = pszRefreshMonitor;
            while((*pPos) != '\0' )
            {
                if((*pPos) == '\v')
                    (*pPos) = '\0';
                pPos ++;
            }   
            
            if(szQuery.empty())
            {
                if(!::PushMessage(szQueueName, szRefreshEnd, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into queue failed!");          
            }
            else
            {
                if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            }
            delete [] pszRefreshMonitor;
        }
    
        string szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
        if(!m_szRefreshEvent.empty())
        {
            szRefreshMonitor = szRefreshMonitor + "update('" + m_szRefreshEvent + "');";
            if(m_pMain)
            {
                m_pMain->m_szActiveOptIndex = m_szDeviceIndex;
                m_pMain->m_nActiveOptType = Tree_DEVICE;
            }
        }
        WebSession::js_af_up = szRefreshMonitor;
    }
}

void SVMonitorview::sortMonitors()
{
    emit sortMonitorsList(Tree_MONITOR);
}

void SVMonitorview::gotoGroup(const std::string szGroupID)
{
    emit enterGroup(szGroupID);
}

void SVMonitorview::copySelMonitor()
{
    m_lsCopyList.clear();
    if(!m_svMonitorList.empty())
    {
        for(row it = m_svMonitorList.begin(); it != m_svMonitorList.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szMonitorID = (*it).second.getProperty();
                        m_lsCopyList.push_back(szMonitorID);
                    }
                }
            }
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

void SVMonitorview::PastMonitor()
{
    if(static_cast<int>(m_lsCopyList.size()) > 0)
    {
        if(!IsCanPaste())
        {
            WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
            return;
        }

        list<string> lsRefresh;
        list<string>::iterator lsItem;
        string szNewMonitorID("");
        for(lsItem = m_lsCopyList.begin(); lsItem != m_lsCopyList.end(); lsItem ++)
        {
            szNewMonitorID = "";
            szNewMonitorID = MonitorCopy((*lsItem), m_szDeviceIndex);
            if(!szNewMonitorID.empty())
            {
                int nMTID = 0;
                string szName = getMonitorNameMTID(szNewMonitorID, nMTID, m_szIDCUser, m_szIDCPwd);
                InsertTable(szNewMonitorID, nMTID, m_szIDCUser, m_szIDCPwd);
                lsRefresh.push_back(szNewMonitorID);

                if(m_pSVUser && !m_pSVUser->isAdmin())
                    m_pSVUser->AddUserScopeAllRight(szNewMonitorID, Tree_MONITOR);
                
                emit CopyMonitorSucc(szName, szNewMonitorID);

                AddMonitorList(szName, szNewMonitorID);

                if(m_pHasNoChild) m_pHasNoChild->hide();
            }
        }

        if(static_cast<int>(lsRefresh.size()) > 0)
        {
            string szQuery("");
            string szQueueName(makeQueueName());
            CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
            string szRefreshQueue(getRefreshQueueName(m_szDeviceIndex));
            CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
            for(lsItem = lsRefresh.begin(); lsItem != lsRefresh.end(); lsItem ++)
            {
                if(!isMonitorDisable((*lsItem), m_szIDCUser, m_szIDCPwd))
                {
                    szQuery += (*lsItem);
                    szQuery += "\v";
                }
                else
                {
                    int nSize = static_cast<int>((*lsItem).length()) + 2;
                    char *pszRefreshMonitor = new char[nSize];
                    if(pszRefreshMonitor)
                    {  
                        memset(pszRefreshMonitor, 0, nSize);
                        strcpy( pszRefreshMonitor, (*lsItem).c_str());
                        if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                            PrintDebugString("PushMessage into queue failed!");
                        delete []pszRefreshMonitor;
                    }
                }
            }                
            int nSize = static_cast<int>(szQuery.length()) + 1;
            char *pszRefreshMonitor = new char[nSize];
            if(pszRefreshMonitor)
            {
                memset(pszRefreshMonitor, 0, nSize);
                strcpy( pszRefreshMonitor, szQuery.c_str());
                char *pPos = pszRefreshMonitor;
                while((*pPos) != '\0' )
                {
                    if((*pPos) == '\v')
                        (*pPos) = '\0';
                    pPos ++;
                }
                if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
                delete [] pszRefreshMonitor;
            }

            string szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
            if(!m_szRefreshEvent.empty())
            {
                szRefreshMonitor = szRefreshMonitor + "update('" + m_szRefreshEvent + "');hiddenbar();";
                if(m_pMain)
                {
                    m_pMain->m_szActiveOptIndex = m_szDeviceIndex;
                    m_pMain->m_nActiveOptType = Tree_DEVICE;
                }
            }
            WebSession::js_af_up = szRefreshMonitor;
        }
	}
    else
    {
		WebSession::js_af_up = "hiddenbar();";
	}
    if(m_pMonitorList->numRows() > 2)
        m_pSort->show();
}

bool SVMonitorview::IsCanPaste()
{
    if(m_szNetworkSet == "true")
    {
        int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd, m_szDeviceIndex);
        return checkNetworkPoint(nNetworkCount);
    }
    else
    {
        int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);
        nMonitorCount += getMonitorCountInList(m_lsCopyList, m_szIDCUser, m_szIDCPwd);
        return checkMonitorsPoint(nMonitorCount);
    }
    return false;
}

void SVMonitorview::MakeMTTableOfET()
{
//bool GetAllEntityTemplets(PAIRLIST &retlist,string infoname="sv_Name",string user="default",string addr="localhost");
//std::list<int> & GetSubMonitorTypeList(OBJECT etobj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End file
