#include "devicelist.h"
#include "resstring.h"
#include "showtable.h"
#include "../base/basetype.h"
#include "../../base/des.h"
#include "../../opens/libwt/WebSession.h"

extern void PrintDebugString(const string & szMsg);
extern void PrintDebugString(const char* szMsg);

//#include "../base/OperateLog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVEnumDevice::SVEnumDevice(WContainerWidget * parent, CUser * pUser, string szIDCUser, string szIDCPwd):
WContainerWidget(parent)
{
    m_pDeviceList = NULL;
    m_pOperate = NULL;
    m_pBtnHide = NULL;
    m_pBtnHideDel = NULL;
    m_pAdd = NULL;
    m_pDel = NULL;
    m_pEnable = NULL;
    m_pDisable = NULL; 
    m_pSelAll = NULL;
    m_pCopy   = NULL;
    m_pPaste   = NULL;
    m_pSelNone = NULL;
    m_pSelInvert = NULL;
    m_pSort = NULL;
    m_pBtnDelSel = NULL;
    m_pBtnRefresh = NULL;
    m_pBtnEnterDevice = NULL;
    m_pBtnTest = NULL;
    m_pBtnEdit = NULL;

    m_pHasNoChild   = NULL;
    m_pCurrentDevice = NULL;

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;

    m_pSVUser = pUser;

    m_szDeviceName = "localhost";

    //loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::AddDevice(string &szName, string &szIndex)
{
    string szParentID = FindParentID(szIndex);
    if(szParentID == m_szIndex)
        addDeviceList(szName, szIndex);
}

void SVEnumDevice::refreshDevice(string szIndex)
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
    SVTableRow *pRow = m_svDevice.Row(szIndex);
    if (pRow)
    {
        SVTableCell *pcell = pRow->Cell(2);
        if ( pcell )
        {
            if(pcell->Type() == adText)
            { 
                char szState[512] = {0};
                sv_device_state devState;
                getDeviceState(szIndex, devState, m_szIDCUser, m_szIDCPwd);
                if(devState.pszOSName && devState.pszDeviceType)
                {
                    sprintf(szState, "%s%s<BR>%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d",
                        SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                        SVResString::getResString("IDS_OS_Type").c_str(), devState.pszOSName,
                        SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                }
                else if(devState.pszDeviceType)
                {
                    sprintf(szState, "%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                        SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                        SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                }
                else
                {
                    sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                        SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                }
                ((WText*)pcell->Value())->setText(szState);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::addDeviceList(string &szName, string &szIndex)
{
    if (m_pDeviceList)
    {
        SVTableCell svCell;

        bool bHasEditRight = true;
        bool bHasDelRight = true;
        bool bHasTestRight = true;
        if(m_pSVUser)
        {
            bHasEditRight = m_pSVUser->haveUserRight(szIndex, "editdevice");
            bHasDelRight = m_pSVUser->haveUserRight(szIndex, "deldevice");
            bHasTestRight = m_pSVUser->haveUserRight(szIndex, "testdevice");
        }
        else
        {
            bHasEditRight = false;
            bHasDelRight = false;
            bHasTestRight = false;
        }

        sv_device_state devState;
        getDeviceState(szIndex, devState, m_szIDCUser, m_szIDCPwd);
        m_nMonitorCount += devState.nMonitorCount;
        m_nMonitorErrCount += devState.nErrorCount;
        m_nMonitorWarnCount += devState.nWarnCount;
        m_nMonitorDisableCount += devState.nDisableCount;
        int nRow = m_pDeviceList->numRows();
        // 选择
        WCheckBox * pCheck = NULL;
        if(m_bHasEditRight || m_bHasDelRight)
            if(bHasEditRight || bHasDelRight)
                pCheck = new WCheckBox("", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 0));
        // 状态
        string szDevState("");
        bool bDisable = isDisable(szIndex, szDevState);
        WImage *pState = NULL;
        pState = new WImage("../icons/normal.gif", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 1));
        if(pState)
        {   
            pState->setStyleClass("imgbutton");
			if(bDisable)
				pState->setImageRef("../icons/disablemonitor.gif");
			else
			{
				switch(devState.nState)
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
                if(m_pBtnRefresh && m_pCurrentDevice)
                {
                    string szDisable = "onclick='showDisable(\"1\", \"" + szIndex + "\", \"" + m_pCurrentDevice->formName()
                        + "\", \"" + m_pBtnRefresh->getEncodeCmd("xclicked()") + "\")'";
                    strcpy(pState->contextmenu_, szDisable.c_str());
                }
            }
        }

        // 描述
        WText *pDesc = new WText("", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 2));
        if(pDesc)
        {
            char szState[512] = {0};
            if(devState.pszOSName && devState.pszDeviceType)
            {
                sprintf(szState, "%s%s%s<BR>%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d",
                    szDevState.c_str(),
                    SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                    SVResString::getResString("IDS_OS_Type").c_str(), devState.pszOSName,
                    SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
            }
            else if(devState.pszDeviceType)
            {
                sprintf(szState, "%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                        SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                        SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
            }
            else
            {
                sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                        SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                        SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                        SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                        SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
            }
            pDesc->setText(szState);
        }
        if(pDesc && bDisable)
            pDesc->setText(SVResString::getResString("IDS_DeviceDisabled") + pDesc->text());

        // 名称
        WText *pName = new WText(szName, (WContainerWidget *)m_pDeviceList->elementAt(nRow, 3));
        if ( pName )
        {
            if(m_pBtnEnterDevice && m_pCurrentDevice)
            {
                string szDevice = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentDevice->formName()
                    + "\", \"" + m_pBtnEnterDevice->getEncodeCmd("xclicked()") + "\")' style='color:#669;cursor:pointer;' onmouseover='" 
                    + "this.style.textDecoration=\"underline\"' onmouseout='this.style.textDecoration=\"none\"'";
                strcpy(pName->contextmenu_, szDevice.c_str());
            }
            pName->setToolTip(szName);
        }

        // 编辑
        WImage * pEdit = NULL;
        if(bHasEditRight) 
            pEdit = new WImage("../icons/edit.gif", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 4));
        if (pEdit)
        {
            if(m_pCurrentDevice && m_pBtnEdit)
            {
                string szDevice = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentDevice->formName()
                    + "\", \"" + m_pBtnEdit->getEncodeCmd("xclicked()") + "\")'";

                strcpy(pEdit->contextmenu_, szDevice.c_str());
            }
            pEdit->setToolTip(SVResString::getResString("IDS_Edit"));
            pEdit->setStyleClass("imgbutton");
        }

        // 删除
        WImage * pDel = NULL;
        if(bHasDelRight) 
            pDel = new WImage("../icons/del.gif", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 5));
        if (pDel)
        {
            pDel->setToolTip(SVResString::getResString("IDS_Delete_Device_Tip"));
            if(m_pCurrentDevice && m_pBtnDelSel)
            {
                string szDevice = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentDevice->formName()
                    + "\", \"" + m_pBtnDelSel->getEncodeCmd("xclicked()") + "\")'";
                strcpy(pDel->contextmenu_, szDevice.c_str());
            }
             pDel->setStyleClass("imgbutton");
        }

        // 测试
        WImage * pTest = NULL;
        if(bHasTestRight && isCanBeTest(szIndex))
            pTest = new WImage("../icons/test.gif", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 6));
        if (pTest)
        {
            pTest->setStyleClass("imgbutton");
            pTest->setToolTip(SVResString::getResString("IDS_Table_Col_Test"));
            if(m_pCurrentDevice && m_pBtnTest)
            {
                string szDevice = "onclick='currentoperate(\"" + szIndex + "\", \"" + m_pCurrentDevice->formName()
                    + "\", \"" + m_pBtnTest->getEncodeCmd("xclicked()") + "\")'";
                strcpy(pTest->contextmenu_, szDevice.c_str());
            }
        }

        if((nRow + 1) % 2 == 0)
            m_pDeviceList->GetRow(nRow)->setStyleClass("tr1");
        else
            m_pDeviceList->GetRow(nRow)->setStyleClass("tr2");

        // 最后更新
        WText *pLast = new WText("", (WContainerWidget *)m_pDeviceList->elementAt(nRow, 7));
        if(pLast)
        {
            svutil::TTime tmptime;
            if(tmptime != devState.m_time)
                pLast->setText(devState.m_time.Format());
        }

        if(pCheck)
        {
            svCell.setType(adCheckBox);
            svCell.setValue(pCheck);
            m_svDevice.WriteCell(szIndex, 0, svCell);
            SVTableRow *pRow = m_svDevice.Row(szIndex);
            if (pRow)
            {
                pRow->setProperty(szIndex.c_str());
            }
        }
        if(pState)
        {
            svCell.setType(adImage);
            svCell.setValue(pState);
            m_svDevice.WriteCell(szIndex, 1, svCell);
        }
        if(pDesc)
        {
            svCell.setType(adText);
            svCell.setValue(pDesc);
            m_svDevice.WriteCell(szIndex, 2, svCell);
        }
        if(pName)
        {
            svCell.setType(adText);
            svCell.setValue(pName);
            m_svDevice.WriteCell(szIndex, 3, svCell);
        }
        if(pLast)
        {
            svCell.setType(adText);
            svCell.setValue(pLast);
            m_svDevice.WriteCell(szIndex, 7, svCell);
        }
    }
}

bool SVEnumDevice::isChildEdit(string szIndex)
{
    string szParent = FindParentID(szIndex);
    if(szParent == m_szIndex)
    {
        SVTableRow *pRow = m_svDevice.Row(szIndex);
        if (pRow)
        {
            SVTableCell *pcell = pRow->Cell(3);
            if ( pcell )
            {
                if(pcell->Type() == adText)
                { 
                    string szName = getDeviceName(szIndex);
                    ((WText*)pcell->Value())->setToolTip(szName);
                    ((WText*)pcell->Value())->setText(szName);
                }
            }
        }
        return true;
    }
    return false;
}

string SVEnumDevice::getDeviceName(string szDeviceIndex)
{
    string szName;
    OBJECT objDevice = GetEntity(szDeviceIndex,  m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
            FindNodeValue(mainnode, "sv_name", szName);
        CloseEntity(objDevice);
    }
    return szName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::EditDevice(string &szName, string &szIndex)
{
    editDeviceList(szName, szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::editDeviceList(string &szName, string &szIndex)
{
    SVTableRow *pRow = m_svDevice.Row(szIndex);
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
void SVEnumDevice::createDeviceList(WTable * pTable)
{
    int nRow = pTable->numRows();
    m_pDeviceList = new WTable((WContainerWidget*)pTable->elementAt(nRow, 0));
    if(m_pDeviceList)
    {
        m_pDeviceList->setStyleClass("t3");
        new WText("", (WContainerWidget *)m_pDeviceList->elementAt(0, 0));
        new WText(SVResString::getResString("IDS_State"), (WContainerWidget *)m_pDeviceList->elementAt(0, 1));
        new WText(SVResString::getResString("IDS_State_Description"), (WContainerWidget *)m_pDeviceList->elementAt(0, 2));
        new WText(SVResString::getResString("IDS_Name"), (WContainerWidget *)m_pDeviceList->elementAt(0, 3));
        new WText(SVResString::getResString("IDS_Edit"), (WContainerWidget *)m_pDeviceList->elementAt(0, 4));
        new WText(SVResString::getResString("IDS_Delete"), (WContainerWidget *)m_pDeviceList->elementAt(0, 5));
        new WText(SVResString::getResString("IDS_Table_Col_Test"), (WContainerWidget *)m_pDeviceList->elementAt(0, 6));
        new WText(SVResString::getResString("IDS_Table_Col_Last_Refresh"), (WContainerWidget *)m_pDeviceList->elementAt(0, 7));
        m_pDeviceList->setCellPadding(0);
        m_pDeviceList->setCellSpaceing(0);
        m_pDeviceList->GetRow(0)->setStyleClass("t3title");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::createDelOperate()
{
    m_pDel = new WImage("../icons/del.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pDel)
    {
        m_pDel->setStyleClass("imgbutton");
        m_pDel->setToolTip(SVResString::getResString("IDS_Delete_All_Sel_Device_Tip"));
        WObject::connect(m_pDel, SIGNAL(clicked()), this, SLOT(deleteDevice()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::createSelOperate()
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
void SVEnumDevice::createEnableOperate()
{
    m_pEnable = new WImage("../icons/enable.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pEnable)
    {
        m_pEnable->setStyleClass("imgbutton");
        m_pEnable->setToolTip(SVResString::getResString("IDS_Enable_Device"));
        WObject::connect(m_pEnable, SIGNAL(clicked()), this, SLOT(enableSelDevice()));
    }

    m_pDisable = new WImage("../icons/disable.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pDisable)
    {
        m_pDisable->setStyleClass("imgbutton");
        m_pDisable->setToolTip(SVResString::getResString("IDS_Disable_Device"));
        WObject::connect(m_pDisable, SIGNAL(clicked()), this, SLOT(disableSelDevice()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::createCopyPaste()
{
    m_pCopy = new WImage("../icons/copy.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pCopy)
    {
        m_pCopy->setStyleClass("imgbutton");
        m_pCopy->setToolTip(SVResString::getResString("IDS_Copy"));
        WObject::connect(m_pCopy, SIGNAL(clicked()), "showbar();", this, SLOT(CopyDevice()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    m_pPaste = new WImage("../icons/paste.gif", 
        (WContainerWidget *)m_pOperate->elementAt(0, 0));
    if (m_pPaste)
    {
        m_pPaste->setStyleClass("imgbutton");
        m_pPaste->setToolTip(SVResString::getResString("IDS_Past"));
        WObject::connect(m_pPaste, SIGNAL(clicked()), "showbar();", this, SLOT(PastDevice()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::createOperate(WTable *pTable)
{
    int nRow = pTable->numRows();
    m_pOperate = new WTable((WContainerWidget*)pTable->elementAt(nRow, 0));
    if (m_pOperate)
    {
        m_pOperate->setStyleClass("t3");

        createSelOperate();
        createEnableOperate();
        createDelOperate();
        createCopyPaste();

        m_pSort = new WImage("../icons/sort.gif", (WContainerWidget *)m_pOperate->elementAt(0, 0));
        if(m_pSort)
        {
            m_pSort->setToolTip(SVResString::getResString("IDS_Sort"));
            m_pSort->setStyleClass("imgbutton");
            WObject::connect(m_pSort, SIGNAL(clicked()), "showbar();", this, SLOT(sortDevices()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        m_pAdd = new WPushButton(SVResString::getResString("IDS_Add_Device"), (WContainerWidget *)m_pOperate->elementAt(0, 1));
        m_pOperate->elementAt(0, 1)->setContentAlignment(AlignTop | AlignRight);
        if (m_pAdd)
        {
            m_pAdd->setStyleClass("wizardbutton");
            m_pAdd->setToolTip(SVResString::getResString("IDS_Add_Entity_Tip"));
            WObject::connect(m_pAdd, SIGNAL(clicked()), "showbar();", this, SLOT(add()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVEnumDevice::loadString()
//{
//    OBJECT objRes=LoadResource("default", "localhost");  
//    if( objRes !=INVALID_VALUE )
//    {	
//        MAPNODE ResNode=GetResourceNode(objRes);
//        if( ResNode != INVALID_VALUE )
//        {
//            FindNodeValue(ResNode,"IDS_Device",m_szTitle);
//            FindNodeValue(ResNode,"IDS_Delete",m_szColDel);
//            FindNodeValue(ResNode,"IDS_Edit",m_szColEdit);
//            FindNodeValue(ResNode,"IDS_Table_Col_Last_Refresh",m_szColLast);
//            FindNodeValue(ResNode,"IDS_Name",m_szColName);
//            FindNodeValue(ResNode,"IDS_State",m_szColState);
//            FindNodeValue(ResNode,"IDS_State_Description",m_szColDesc);
//            FindNodeValue(ResNode,"IDS_Table_Col_Test",m_szColTest);
//            FindNodeValue(ResNode,"IDS_All_Select",m_szSelAllTip);
//            FindNodeValue(ResNode,"IDS_None_Select",m_szSelNoneTip);
//            FindNodeValue(ResNode,"IDS_Invert_Select",m_szInvertSelTip);
//            FindNodeValue(ResNode,"IDS_Delete_All_Sel_Device_Tip",m_szDelSelTip);
//            FindNodeValue(ResNode,"IDS_Delete_Device_Tip",m_szDelTip);
//            FindNodeValue(ResNode,"IDS_Sort",m_szSortTip);
//            FindNodeValue(ResNode,"IDS_Disable_Device",m_szDisableTip);
//            FindNodeValue(ResNode,"IDS_Enable_Device",m_szEnableTip);
//            FindNodeValue(ResNode,"IDS_Add_Device",m_szAdd);
//            FindNodeValue(ResNode,"IDS_Add_Entity_Tip",m_szAddTip);
//            FindNodeValue(ResNode,"IDS_Delete_Device_Confirm",m_szDelSelAsk);
//            FindNodeValue(ResNode,"IDS_Delete_Sel_Device_Confirm",m_szDelAsk);
//            FindNodeValue(ResNode,"IDS_Edit",m_szEditTip);
//            FindNodeValue(ResNode,"IDS_Table_Col_Test",m_szTestTip);
//            FindNodeValue(ResNode,"IDS_Monitor_Count",m_szMonitorCount);
//            FindNodeValue(ResNode,"IDS_Monitor_Disable_Count",m_szMonitorDisable);
//            FindNodeValue(ResNode,"IDS_Monitor_Error_Count",m_szMonitorError);
//            FindNodeValue(ResNode,"IDS_Monitor_Warn_Count",m_szMonitorWarn);
//            FindNodeValue(ResNode,"IDS_Device_Type",m_szDeviceType);
//            FindNodeValue(ResNode,"IDS_OS_Type",m_szOSType);
//            FindNodeValue(ResNode,"IDS_Device_Can_not_Disable",m_szDevicesDisable);
//            FindNodeValue(ResNode,"IDS_Device_Can_not_Enable",m_szDevicesEnable);
//            FindNodeValue(ResNode,"IDS_Device_Disable_Forver",m_szForver);
//            FindNodeValue(ResNode,"IDS_Device_Disable_Temprary",m_szTemprary);
//            FindNodeValue(ResNode,"IDS_Start_Time",m_szStartTime);
//            FindNodeValue(ResNode,"IDS_End_Time",m_szEndTime);
//            FindNodeValue(ResNode, "IDS_DIEVICE_LIST_IS_NULL", m_szNoDevice);
//        }
//        CloseResource(objRes);
//    }
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::initForm()
{
    SVShowTable * pTable = new SVShowTable(this);
    if (pTable)
    {
        pTable->setTitle(SVResString::getResString("IDS_Device").c_str());
        WTable *pSub = pTable->createSubTable();
        if(pSub)
        {
            createDeviceList(pSub);

            int nRow = pSub->numRows();
            m_pHasNoChild = new WText( "<BR>" + SVResString::getResString("IDS_DIEVICE_LIST_IS_NULL"), pSub->elementAt(nRow, 0));
            pSub->elementAt(nRow, 0)->setContentAlignment(AlignCenter);
            if(m_pHasNoChild)
                m_pHasNoChild->setStyleClass("required");

            createOperate(pSub);
        }
    }
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::selNone()
{
    if(!m_svDevice.empty())
    {
        for(row it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
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
void SVEnumDevice::selAll()
{
    if(!m_svDevice.empty())
    {
        for(row it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
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

void SVEnumDevice::delDeviceRow(string &szIndex)
{
    string szParentID = FindParentID(szIndex);
    if(szParentID == m_szIndex)
    {
        SVTableRow * pRow = m_svDevice.Row(szIndex);
        if(pRow)
        {
            SVTableCell *pcell = pRow->Cell(1);
            if(pcell)
            {
                int nRow = ((WTableCell*)(((WText*)pcell->Value())->parent()))->row();
                if(m_pDeviceList)
                {
                    m_pDeviceList->deleteRow(nRow); 
                    if(m_pDeviceList->numRows() == 1)
                        if(m_pHasNoChild)
                            m_pHasNoChild->show();
                }
            }
        }
        m_svDevice.DelRow(szIndex); 
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::delSel()
{
	//string strDeleteDevice;
    if(!m_szDelSelIndex.empty())
    {
        this->getDeviceName(m_szDelSelIndex);
        DelDevice(m_szDelSelIndex);
        SVTableRow * pRow = m_svDevice.Row(m_szDelSelIndex);
        if(pRow)
        {
            SVTableCell *pcell = pRow->Cell(1);
            if(pcell)
            {
 			//	//获取设备名称
				//SVTableCell *pcellName = pRow->Cell(3);
				//if ( pcellName)
				//{
				//	strDeleteDevice = ((WText*)(pcellName->Value()))->text();
				//} 

				int nRow = ((WTableCell*)(((WText*)pcell->Value())->parent()))->row();
                if(m_pDeviceList)
                    m_pDeviceList->deleteRow(nRow); 
            }
        }
        m_svDevice.DelRow(m_szDelSelIndex);
        m_szDelSelIndex= "";
    }
    else
    {
        if(!m_svDevice.empty())
        {
DeleteDevice:
            row it = NULL;
            for(it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
            {
                SVTableCell *pcell = (*it).second.Cell(0);
                if ( pcell )
                {
                    if (pcell->Type() == adCheckBox)
                    {
                        if(((WCheckBox*)pcell->Value())->isChecked())
                        {
							////获取设备名称
							//SVTableCell *pcellName = (*it).second.Cell(3);
							//if ( pcellName)
							//{
							//	strDeleteDevice += ((WText*)(pcellName->Value()))->text();
							//	strDeleteDevice += "  ";
							//} 

							string szDeviceID = (*it).second.getProperty();
                            string szName = pcell->Property();

                            int nRow = ((WTableCell*)(((WCheckBox*)pcell->Value())->parent()))->row();
                            m_pDeviceList->deleteRow(nRow);
                            m_svDevice.DelRow(szDeviceID);

                            DelDevice(szDeviceID);
                            goto DeleteDevice;
                        }
                    }
                }
            }
        }
    }
    if(m_pDeviceList)
    {
        int nRow = m_pDeviceList->numRows();
        if(nRow > 1)
        {
            for(int i = 1; i<= nRow - 1; i++)
            {
                if( i % 2 == 0)
                    m_pDeviceList->GetRow(i)->setStyleClass("tr2");
                else
                    m_pDeviceList->GetRow(i)->setStyleClass("tr1");
            }
        }
        else
        {
            if(m_pHasNoChild)
                m_pHasNoChild->show();
        }
    }
	//
	////插记录到UserOperateLog表
	//string strUserID = GetWebUserID();
	//TTime mNowTime = TTime::GetCurrentTimeEx();
	//OperateLog m_pOperateLog;
	//m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_szColDel,m_szTitle,strDeleteDevice);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::invertSel()
{
    if(!m_svDevice.empty())
    {
        for(row it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
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
void SVEnumDevice::add()
{
    emit AddNewDevice();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::editDevice()
{
    if(m_pCurrentDevice)
    {
        string szDeviceID = m_pCurrentDevice->text();
        if(!szDeviceID.empty())
            emit EditDeviceByID(szDeviceID);
        else
            WebSession::js_af_up = "hiddenbar();";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* SVEnumDevice::getDeviceName()
{
    return m_szDeviceName.c_str();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::DelDevice(string &szIndex)
{
    list<string> lstMonitors;
    list<string>::iterator lstItem;
    if(!szIndex.empty())
    {
		sv_device_state devState;
		getDeviceState(szIndex, devState, m_szIDCUser, m_szIDCPwd);
        OBJECT entity = GetEntity(szIndex, m_szIDCUser, m_szIDCPwd);
        if (entity != INVALID_VALUE)
        {
            if(GetSubMonitorsIDByEntity(entity, lstMonitors))
            {
                for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                {
                    string szMonitorID = (*lstItem).c_str();
                    DeleteSVMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
                    DeleteTable(szMonitorID, m_szIDCUser, m_szIDCPwd);
                }
            }
        }
        CloseEntity(entity);

        string szName = getDeviceName(szIndex);
        DeleteEntity(szIndex, m_szIDCUser, m_szIDCPwd);
        m_nDeviceCount --;
		m_nMonitorCount -= devState.nMonitorCount;
		m_nMonitorErrCount -= devState.nErrorCount;
		m_nMonitorWarnCount -= devState.nWarnCount;
		m_nMonitorDisableCount -= devState.nDisableCount;
        emit DeleteDeviceSucc(szName, szIndex);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::enumDevice(string &szIndex)
{
    OBJECT root;
    bool bGroup = false;
    bool bSucc  = false;
    m_nDeviceCount = 0;
    m_nMonitorCount = 0;
    m_nMonitorErrCount = 0;
    m_nMonitorWarnCount = 0;
    m_nMonitorDisableCount = 0;

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
            bGroup = true;
            root = GetGroup(szIndex, m_szIDCUser, m_szIDCPwd);
        }

        if(root != INVALID_VALUE)
        {
            list<string> lsDeviceID;
            list<string>::iterator lsItem;
            if(!bGroup)
                bSucc = GetSubEntitysIDBySE(root, lsDeviceID);
            else
                bSucc = GetSubEntitysIDByGroup(root, lsDeviceID);
            if(bSucc)
            {
                base_param device;
                int nMax = static_cast<int>(lsDeviceID.size());
                int nIndex = 0;
                for(lsItem = lsDeviceID.begin(); lsItem != lsDeviceID.end(); lsItem ++)
                {
                    string szID = (*lsItem).c_str();
                    bool bHasRight = true;
                    if(m_pSVUser)
                        bHasRight = m_pSVUser->haveGroupRight(szID, Tree_DEVICE);
                    if(bHasRight)
                    {
                        OBJECT objDevice = GetEntity(szID, m_szIDCUser, m_szIDCPwd);
                        if(objDevice != INVALID_VALUE)
                        {
                            MAPNODE node = GetEntityMainAttribNode(objDevice);
                            if(node != INVALID_VALUE)
                            {
                                string szName(""), szIndex("");
                                FindNodeValue(node, "sv_name", szName);
                                FindNodeValue(node, "sv_index", szIndex);
                                if(szIndex.empty())
                                    nIndex = FindIndexByID(szID);
                                else
                                    nIndex = atoi(szIndex.c_str());

                                device.szIndex = szID;
                                device.szName = szName;

                                map<int, base_param, less<int> >::iterator lsItem = sortList.find(nIndex);
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
            }
            if(!bGroup)
                CloseSVSE(root);
            else
                CloseGroup(root);
        }
    }

    m_nDeviceCount = static_cast<int>(sortList.size());
    if(sortList.size() > 0)
    {
        for(lsItem = sortList.begin(); lsItem != sortList.end(); lsItem ++)
            AddDevice(lsItem->second.szName,lsItem->second.szIndex); 
        if(m_pHasNoChild)
            m_pHasNoChild->hide();
    }
    else
    {
        if(m_pHasNoChild)
            m_pHasNoChild->show();
    }

    if(m_pSort)
    {
        if(m_nDeviceCount <= 1)
            m_pSort->hide();
        else
            m_pSort->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::gotoDevice()
{
    if(m_pCurrentDevice)
    {
        string szDeviceID = m_pCurrentDevice->text();
        if(!szDeviceID.empty())
            emit EnterDeviceByID(szDeviceID);
        else
            WebSession::js_af_up = "hiddenbar();";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::deleteDevice()
{
    if(!m_svDevice.empty())
    {
        for(row it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
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
                                string szDelFunc = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Sel_Device_Confirm") + "\",'" +
                                    SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" +  szCmd + "');hiddenbar();" ;
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
void SVEnumDevice::EnterGroup(string &szIndex)
{
    m_szIndex = szIndex;
    if (m_pDeviceList)
    {
        while ( m_pDeviceList->numRows() > 1)
        {
            m_pDeviceList->deleteRow(m_pDeviceList->numRows() - 1);
        }
    }
    enumRight();
    m_svDevice.clear();
    enumDevice(m_szIndex);
    changeOperateState();
}

void SVEnumDevice::changeCopyPasteState()
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
void SVEnumDevice::changeDelState()
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
void SVEnumDevice::changeEnableState()
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
void SVEnumDevice::changeSelState()
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

void SVEnumDevice::enumRight()
{
    m_bHasAddRight = true; 
    m_bHasEditRight = true;
    m_bHasDelRight = true;
    m_bHasSortRight = true;
    m_bHasRefreshRight = true;
    m_bHasTestRight = true;
    if(m_pSVUser)
    {
        m_bHasAddRight = m_pSVUser->haveUserRight(m_szIndex, "adddevice");
        m_bHasEditRight = m_pSVUser->haveUserRight(m_szIndex, "editdevice");
        m_bHasDelRight = m_pSVUser->haveUserRight(m_szIndex, "deldevice");
        m_bHasRefreshRight = m_pSVUser->haveUserRight(m_szIndex, "devicerefresh");
        m_bHasTestRight = m_pSVUser->haveUserRight(m_szIndex, "testdevice");
    }
    else
    {
        m_bHasAddRight = false; 
        m_bHasEditRight = false;
        m_bHasDelRight = false;
        m_bHasRefreshRight = false;
        m_bHasTestRight = false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::changeOperateState()
{
    if(m_pAdd && !m_bHasAddRight)        m_pAdd->hide();
    else if(m_pAdd && m_bHasAddRight)    m_pAdd->show();


    changeDelState();
    changeSelState();
    changeEnableState();
    changeCopyPasteState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::changeState()
{
    if(m_pCurrentDevice)
    {
        string szDeviceID = m_pCurrentDevice->text();
        SVTableRow *pRow = m_svDevice.Row(szDeviceID);
        if (pRow)
        {
            SVTableCell *pcell = pRow->Cell(1);
            if(pcell)
            {
                if(pcell->Type() == adImage)
                {
                    string szTemp = szDeviceID;
                    string szState("");
                    if(isDisable(szTemp, szState))
                    {
                        emit UpdateDeviceState(szDeviceID, dyn_disable);
                        ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                        ((WImage*)pcell->Value())->setToolTip("");
                        pcell = pRow->Cell(2);
                        if(pcell && pcell->Type() == adText)
                            ((WText*)pcell->Value())->setText(szState + ((WText*)pcell->Value())->text());
                    }
                    else
                    {
                        sv_device_state devState;
                        char szState[512] = {0};
                        getDeviceState(szTemp, devState, m_szIDCUser, m_szIDCPwd);
                        switch(devState.nState)
                        {
                        case 1:
                            ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                            emit UpdateDeviceState(szDeviceID, dyn_normal);
                            break;
                        case 2:
                            ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                            emit UpdateDeviceState(szDeviceID, dyn_warnning);
                            break;
                        case 3:
                            ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                            emit UpdateDeviceState(szDeviceID, dyn_error);
                            break;
                        }
                        if(devState.pszOSName && devState.pszDeviceType)
                        {
                            sprintf(szState, "%s%s<BR>%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d",
                                    SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                                    SVResString::getResString("IDS_OS_Type").c_str(), devState.pszOSName,
                                    SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                        }
                        else if(devState.pszDeviceType)
                        {
                            sprintf(szState, "%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                                    SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                                    SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                        }
                        else
                        {
                            sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                                    SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                                    SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                                    SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                                    SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                        }
                        pcell = pRow->Cell(2);
                        if(pcell && pcell->Type() == adText)
                            ((WText*)pcell->Value())->setText(szState);
                        pcell = pRow->Cell(7);
                        if(pcell && pcell->Type() == adText)
                            ((WText*)pcell->Value())->setText(devState.m_time.Format());
                    }
                }
            }
        }
    }
}


bool SVEnumDevice::isDisable(string &szDeviceID, string &szState)
{
    bool bDisable = false;
    OBJECT objEntity = GetEntity(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objEntity != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objEntity);
        if(mainnode != INVALID_VALUE)
        {
            string szDisable("");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                szState += SVResString::getResString("IDS_Device_Disable_Forver");
                szState += "<BR>";
                bDisable =  true;
            }
            else if( szDisable == "time")
            {
                szState = SVResString::getResString("IDS_Device_Disable_Temprary") + "<BR>";
                string szEndTime(""), szStartTime("");
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
                    if(ttime < ttend)
                        bDisable =  true;                        
                }
            }
        }
        CloseEntity(objEntity);
    }
    if(!bDisable)
        szState = "";
    return bDisable;
}

void SVEnumDevice::createHideButton()
{
    m_pBtnHide = new WPushButton("hidebutton", this);
    if(m_pBtnHide)
    {
        WObject::connect(m_pBtnHide, SIGNAL(clicked()), this, SLOT(disableDeviceSucc()));
        m_pBtnHide->hide();
    }
    m_pBtnHideDel = new WPushButton("hidebutton", this);
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
    m_pBtnDelSel = new WPushButton("hidebutton", this);
    if(m_pBtnDelSel)
    {
        WObject::connect(m_pBtnDelSel, SIGNAL(clicked()), this, SLOT(DelSelDevice()));
        m_pBtnDelSel->hide();
    }
    m_pBtnEnterDevice = new WPushButton("hidebutton", this);
    if(m_pBtnEnterDevice)
    {
        WObject::connect(m_pBtnEnterDevice, SIGNAL(clicked()), this, SLOT(gotoDevice()));
        m_pBtnEnterDevice->hide();
    }
    m_pBtnTest = new WPushButton("hidebutton", this);
    if(m_pBtnTest)
    {
        WObject::connect(m_pBtnTest, SIGNAL(clicked()), this, SLOT(testDevice()));
        m_pBtnTest->hide();
    }
    m_pBtnEdit = new WPushButton("hidebutton", this);
    if(m_pBtnEdit)
    {
        WObject::connect(m_pBtnEdit, SIGNAL(clicked()), this, SLOT(editDevice()));
        m_pBtnEdit->hide();
    }
    m_pCurrentDevice = new WLineEdit("", this);
    if(m_pCurrentDevice)
    {
        m_pCurrentDevice->hide();
    }
}

void SVEnumDevice::disableDeviceSucc()
{
    if(!m_svDevice.empty())
    {
        row it = NULL;
        for(it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
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
                            string szDevState;
                            if(isDisable(szMonitorID, szDevState))
                            {
                                emit UpdateDeviceState(szMonitorID, dyn_disable);
                                ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                                ((WImage*)pcell->Value())->setToolTip("");
                                pcell = (*it).second.Cell(2);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(szDevState + ((WText*)pcell->Value())->text());
                            }
                            else
                            {
                                sv_device_state devState;
                                char szState[512] = {0};
                                getDeviceState(szMonitorID, devState, m_szIDCUser, m_szIDCPwd);
                                switch(devState.nState)
                                {
                                case 1:
                                    ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
                                    emit UpdateDeviceState(szMonitorID, dyn_normal);
                                    break;
                                case 2:
                                    ((WImage*)pcell->Value())->setImageRef("../icons/warnning.gif");
                                    emit UpdateDeviceState(szMonitorID, dyn_warnning);
                                    break;
                                case 3:
                                    ((WImage*)pcell->Value())->setImageRef("../icons/error.gif");
                                    emit UpdateDeviceState(szMonitorID, dyn_error);
                                    break;
                                }
                                if(devState.pszOSName && devState.pszDeviceType)
                                {
                                    sprintf(szState, "%s%s<BR>%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d",
                                            SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                                            SVResString::getResString("IDS_OS_Type").c_str(), devState.pszOSName,
                                            SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                                            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                                            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                                            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                                }
                                else if(devState.pszDeviceType)
                                {
                                    sprintf(szState, "%s%s<BR>%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                                            SVResString::getResString("IDS_Device_Type").c_str(), devState.pszDeviceType,
                                            SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                                            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                                            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                                            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                                }
                                else
                                {
                                    sprintf(szState, "%s%d<BR>%s%d<BR>%s%d<BR>%s%d", 
                                            SVResString::getResString("IDS_Monitor_Count").c_str(), devState.nMonitorCount, 
                                            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), devState.nDisableCount,
                                            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), devState.nErrorCount, 
                                            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), devState.nWarnCount);
                                }
                                pcell = (*it).second.Cell(2);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(szState);
                                pcell = (*it).second.Cell(7);
                                if(pcell && pcell->Type() == adText)
                                    ((WText*)pcell->Value())->setText(devState.m_time.Format());                                
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
void SVEnumDevice::enableSelDevice()
{   
    list<string> lsSel;
    if(!m_svDevice.empty())
    {
        row it = NULL;
        for(it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        if(isDeviceDisable(szDeviceID) != 0)
                            lsSel.push_back((*it).second.getProperty());
                    }
                }
            }
        }
        if(lsSel.size() > 0)
        {
            // 改造Disable（后期任务）
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
                        PrintDebugString("Disable Device: PushMessage into queue failed!");
                    delete []pszIndex;
                }
            }
            char pEnd[2] = {0};
            if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("Disable Device(End label): PushMessage into queue failed!");

            if(m_pBtnHide)
            {
                string szCmd = m_pBtnHide->getEncodeCmd("xclicked()");
                if(!szCmd.empty())
                {
                    string szDisable = "showDisableUrl('disable.exe?disabletype=1&operatetype=1&queuename=" +
                        szQueueName + "', '" + szCmd + "');";
                    WebSession::js_af_up = szDisable;
                }
            }
        }
        else
        {
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVEnumDevice::disableSelDevice()
{   
    list<string> lsSel;
    if(!m_svDevice.empty())
    {
        row it = NULL;
        for(it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {                    
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        if(isDeviceDisable(szDeviceID) == 0)
                            lsSel.push_back((*it).second.getProperty());
                    }
                }
            }
        }
        if(lsSel.size() > 0)
        {
            // 改造Disable（后期任务）
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
                        PrintDebugString("Disable Device: PushMessage into queue failed!");
                    delete []pszIndex;
                }
                //szSelIndex += (*lsItem);
                //szSelIndex += ",";
            }
            char pEnd[2] = {0};
            if(!::PushMessage(szQueueName, sv_disable_end, pEnd, 2, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("Disable Device(End label): PushMessage into queue failed!");

            if(m_pBtnHide)
            {
                string szCmd = m_pBtnHide->getEncodeCmd("xclicked()");
                if(!szCmd.empty())
                {
                    string szDisable = "showDisableUrl('disable.exe?disabletype=1&operatetype=0&queuename=" +
                        szQueueName + "', '" + szCmd + "');";
                    WebSession::js_af_up = szDisable;
                }
            }
        }
        else
        {
            WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Disable") +  
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
        }
    }
}

//
void SVEnumDevice::DelSelDevice()
{    
    if(m_pBtnHideDel)
    {
        string szCmd = m_pBtnHideDel->getEncodeCmd("xclicked()");
        if(!szCmd.empty())
        {
            string szDelFunc = "_Delclick(\"" + SVResString::getResString("IDS_Delete_Device_Confirm") + "\",'"  +
                                    SVResString::getResString("IDS_ConfirmCancel") + "','" +
                                SVResString::getResString("IDS_Affirm") + "','" + szCmd + "');hiddenbar();" ;
            WebSession::js_af_up = szDelFunc;
        }                        
    }
    if(m_pCurrentDevice)
        m_szDelSelIndex = m_pCurrentDevice->text();
}

void SVEnumDevice::testDevice()
{   
    if(m_pCurrentDevice)
    {
        string szDeviceID = m_pCurrentDevice->text();
        if(!szDeviceID.empty())
        {
            string szParam = enumDeviceRunParam(szDeviceID);
            szParam += "&seid=";
            szParam += FindSEID(szDeviceID);
            if(!szParam.empty())
            {
                szParam = "showtestdevice('testdevice.exe?" + szParam +"');hiddenbar();" ;
                WebSession::js_af_up = szParam;
            }
            else
                WebSession::js_af_up = "hiddenbar();";
        }
        else
            WebSession::js_af_up = "hiddenbar();";
    }
}

bool SVEnumDevice::isCanBeTest(string &szDeviceID)
{
    string szDllName(""), szFuncName("");
    OBJECT objDevice = GetEntity(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDeviceType("");
            if(FindNodeValue(mainnode, "sv_devicetype", szDeviceType))
            {
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    MAPNODE node = GetEntityTempletMainAttribNode(objDeviceTmp);
                    if(node != INVALID_VALUE)
                    {
                        FindNodeValue(node, "sv_dll", szDllName);
                        FindNodeValue(node, "sv_func", szFuncName);
                    }
                    CloseEntityTemplet(objDeviceTmp);
                }
            }
        }
        CloseEntity(objDevice);
    }
    if(szDllName.empty() || szFuncName.empty())
        return false;
    return true;
}

string SVEnumDevice::enumDeviceRunParam(string szDeviceIndex)
{
    string szQuery("");
    OBJECT objDevice = GetEntity(szDeviceIndex, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDeviceType("");
            map<string, string, less<string> > lsDeviceParam;
            if(FindNodeValue(mainnode, "sv_devicetype", szDeviceType))
            {
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDeviceTmp, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName(""), szRun("");
                            string szType("");
                            FindNodeValue(objNode, "sv_name", szName);
                            FindNodeValue(objNode, "sv_run", szRun);
                            FindNodeValue(objNode, "sv_type", szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    CloseEntityTemplet(objDeviceTmp);
                }
            }
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue("");
                FindNodeValue(mainnode, (lstItem->first), szValue);
                if((lstItem->second).compare(svPassword) == 0)
                {
                    char szOutput[512] = {0};
                    Des des;
                    if(des.Decrypt(szValue.c_str(), szOutput))
                        szValue = szOutput;
                }
                szValue = url_Encode(szValue.c_str());
                szQuery = szQuery + (lstItem->first) + "=" + szValue + "&";
            }
            szQuery = szQuery + "devicetype=" + szDeviceType;
        }        
        CloseEntity(objDevice);
    }
    PrintDebugString(szQuery.c_str());
    return szQuery;
}

void SVEnumDevice::changeDeviceState(string &szIndex, bool bEnable)
{
    SVTableRow *pRow = m_svDevice.Row(szIndex);
    if (pRow)
    {
        SVTableCell *pcell = pRow->Cell(1);
        if(pcell)
        {
            if(pcell->Type() == adImage)
            {
                if(!bEnable)
                    ((WImage*)pcell->Value())->setImageRef("../icons/disablemonitor.gif");
                else
                    ((WImage*)pcell->Value())->setImageRef("../icons/normal.gif");
            }
        }
    }
}

void SVEnumDevice::sortDevices()
{
    emit sortDevicesList(Tree_DEVICE);
}

void SVEnumDevice::CopyDevice()
{
    m_lsCopyDevice.clear();
    if(!m_svDevice.empty())
    {
        for(row it = m_svDevice.begin(); it != m_svDevice.end(); it++ )
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if ( pcell )
            {
                if (pcell->Type() == adCheckBox)
                {
                    if(((WCheckBox*)pcell->Value())->isChecked())
                    {
                        string szDeviceID = (*it).second.getProperty();
                        m_lsCopyDevice.push_back(szDeviceID);
                    }
                }
            }
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

void SVEnumDevice::PastDevice()
{
    if(static_cast<int>(m_lsCopyDevice.size()) > 0)
    {
        if(!IsCanPaste())
        {
            WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
            return;
        }

        list<string>::iterator lsItem;
        string szNewDeviceIndex("");
        for(lsItem = m_lsCopyDevice.begin(); lsItem != m_lsCopyDevice.end(); lsItem ++)
            szNewDeviceIndex = copyDevice((*lsItem));

        if(static_cast<int>(m_lsCopyDevice.size()) == 1)
            PrintDebugString("New device can be refresh when copy list size is 1 (later).");
    } 
    
    if(m_pDeviceList->numRows() > 2)
        m_pSort->show();

    WebSession::js_af_up = "hiddenbar();";
}

string SVEnumDevice::copyDevice(string &szSrcDeviceID)
{
    string szNewDeviceID = EntityCopy(szSrcDeviceID, m_szIndex, m_szIDCUser, m_szIDCPwd);
    if(!szNewDeviceID.empty())
    {
        createAllTableOfDevice(szNewDeviceID, m_szIDCUser, m_szIDCPwd);                    
        string szName = getDeviceName(szNewDeviceID);
        AddDevice(szName, szNewDeviceID);

        emit CopyDeviceSucc(szName, szNewDeviceID);

        if(m_pHasNoChild) m_pHasNoChild->hide();
    }
    return szNewDeviceID;
}

bool SVEnumDevice::IsCanPaste()
{
    string szNetworkSet(""), szPoint("");

    int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);
    int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd);
    int nSubMonitorCount = 0;

    list<string>::iterator it;
    list<string> lsMonitorID;

    for(it = m_lsCopyDevice.begin(); it != m_lsCopyDevice.end(); it ++)
    {
        OBJECT objDevice = GetEntity((*it), m_szIDCUser, m_szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            if(mainnode != INVALID_VALUE)
                FindNodeValue(mainnode, "sv_network", szNetworkSet);
            if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
            {
                nSubMonitorCount = static_cast<int>(lsMonitorID.size());
                if(szNetworkSet == "true")
                {
                    if(nSubMonitorCount % 30 == 0 && nSubMonitorCount > 0)
                        nNetworkCount += nSubMonitorCount/ 30;
                    else
                        nNetworkCount += nSubMonitorCount / 30 + 1;
                }
                else
                {
                    nMonitorCount += getMonitorCountInList(lsMonitorID, m_szIDCUser, m_szIDCPwd);
                }
            }

            lsMonitorID.clear();
            CloseEntity(objDevice);

            if(szNetworkSet == "true")
                if(!checkNetworkPoint(nNetworkCount))
                    return false;
            else
                if(!checkMonitorsPoint(nMonitorCount))
                    return false;
        }
    }
    return true;
}
