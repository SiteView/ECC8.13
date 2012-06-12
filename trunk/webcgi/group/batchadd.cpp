#include "batchadd.h"

extern void PrintDebugString(const char * szErrmsg);
extern void PrintDebugString(const string &szMsg);

#include "../base/basetype.h"
#include "resstring.h"
//#include "../base/OperateLog.h"

SVBatchAdd::SVBatchAdd(WContainerWidget *parent, CUser *pUser, string szIDCUser, string szIDCPwd)
:WTable(parent)
{
    m_pList = NULL;
    m_pSelAll = NULL;
    m_pMonitorName = NULL;
    m_pContentTable = NULL;
    m_pContentTable = NULL;
    m_pSVUser = pUser;


    m_szIDCUser = szIDCUser;
    m_szIDCPwd  = szIDCPwd;

    setStyleClass("t5");
    loadString();
    initForm();
}

void SVBatchAdd::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Save",m_szSave);
			FindNodeValue(ResNode,"IDS_Save_Sel_Monitor_Tip",m_szSaveTip);
			FindNodeValue(ResNode,"IDS_Cancel",m_szCancel);
			FindNodeValue(ResNode,"IDS_Cancle_Add_Monitor_Tip",m_szCancelTip);
			FindNodeValue(ResNode,"IDS_All_Select",m_szSelAll);
			FindNodeValue(ResNode,"IDS_Batch_Add",m_szAddTitle);
			FindNodeValue(ResNode,"IDS_Monitor_Point_Lack_Tip",m_szAddMonitorErr);
			FindNodeValue(ResNode,"IDS_Monitor_Title",m_szOperateMonitor);
		}
		CloseResource(objRes);
	}
}

void SVBatchAdd::initForm()
{
    int nRow = numRows();
    new WText(m_szAddTitle, (WContainerWidget*)elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("t1title");

    nRow ++;
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t5"); 
        elementAt(nRow, 0)->setStyleClass("t7");

        nRow = m_pContentTable->numRows();
        m_pSubContent = new WTable(m_pContentTable->elementAt(nRow,0));
        m_pContentTable->elementAt(nRow,0)->setContentAlignment(AlignTop);
    }

    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t3");
        CreateList();
    }

    CreateOperater();    
}

void SVBatchAdd::clearlist()
{
    if(m_pSelAll)
        m_pSelAll->setUnChecked();
    if(m_pList)
    {
        while(m_pList->numRows() > 1)
        {
            m_pList->deleteRow(m_pList->numRows() - 1);
        }
    }
    m_pSVList.clear();
}

void SVBatchAdd::CreateList()
{
    m_pList = new WTable(m_pSubContent->elementAt(0,0));
    if(m_pList)
    {
        m_pList->setStyleClass("t3");
        m_pSelAll = new WCheckBox(m_szSelAll, m_pList->elementAt(0, 0));
        if(m_pSelAll)
        {
            WObject::connect(m_pSelAll, SIGNAL(clicked()), "showbar();", this, SLOT(selall()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
        m_pMonitorName = new WText("Label", m_pList->elementAt(0, 1));
        m_pList->setCellPadding(0);
        m_pList->setCellSpaceing(0);
        m_pList->elementAt(0, 1)->setStyleClass("cell_40");
        m_pList->GetRow(0)->setStyleClass("t3title");
    }
}

void SVBatchAdd::CreateOperater()
{
    int nRow = numRows();
    m_pSave = new WPushButton(m_szSave, elementAt(nRow, 0));
    if(m_pSave)
    {
        WObject::connect(m_pSave, SIGNAL(clicked()) , "showbar();", this, SLOT(savemonitor()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        m_pSave->setToolTip(m_szSaveTip);
    }

    new WText("&nbsp;", elementAt(nRow, 0));

    m_pCancel = new WPushButton(m_szCancel, elementAt(nRow,0));
    if(m_pCancel)
    {
        m_pCancel->setToolTip(m_szCancelTip);
        WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(cancel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    elementAt(nRow, 0)->setContentAlignment(AlignCenter);

}

void SVBatchAdd::savemonitor()
{
	string strBatAddMonitorName("");
	//获取设备的名称
    string szEntityName ("");
    OBJECT objEntity = GetEntity(m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
    if(objEntity != INVALID_VALUE)
    {
        MAPNODE devnode = GetEntityMainAttribNode(objEntity);
        if(devnode != INVALID_VALUE)
        {
            FindNodeValue(devnode, "sv_name", szEntityName);
        }
        CloseEntity(objEntity);
    }

    OBJECT objMonitor;
    for(irow it = m_pSVList.begin(); it != m_pSVList.end(); it++ )
    {
        SVTableCell *pcell = (*it).second.Cell(0);
        if ( pcell )
        {
            if (pcell->Type() == adCheckBox)
            {
                ((WCheckBox*)pcell->Value())->label()->setText("");
                if(((WCheckBox*)pcell->Value())->isChecked())
                {
                    if(m_szNetworkset != "true")
                    {
                        int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);
                        int nPoint = atoi(m_szPoint.c_str());
                        if(nPoint <= 0)
                            nPoint = 1;
                        nMonitorCount += nPoint;
                        if(!checkMonitorsPoint(nMonitorCount))
                        {
                            ((WCheckBox*)pcell->Value())->label()->setText(((WCheckBox*)pcell->Value())->label()->text() + m_szAddMonitorErr);
                            ((WCheckBox*)pcell->Value())->label()->setStyleClass("errortip");
                            WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                                SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                            return;
                        }
                    }
                    else
                    {
                        int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd, m_szDeviceIndex);
                        if(!checkNetworkPoint(nNetworkCount))
                        {
                            ((WCheckBox*)pcell->Value())->label()->setText(((WCheckBox*)pcell->Value())->label()->text() + m_szAddMonitorErr);
                            ((WCheckBox*)pcell->Value())->label()->setStyleClass("errortip");
                            WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                                SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                            return;
                        }
                    }

                    objMonitor = CreateMonitor();

                    if(objMonitor != INVALID_VALUE)
                    {
                        MAPNODE mainnode;
                        mainnode  = GetMonitorMainAttribNode(objMonitor);
                        if(mainnode != INVALID_VALUE)
                        {
                            char chMTID [8] = {0};string szName (""), szLabel ("");
                            sprintf(chMTID, "%d", m_nMonitorID);                        

                            pcell = (*it).second.Cell(1);
                            if(pcell->Type() == adText)
                            {
                                szLabel = ((WText*)pcell->Value())->text();
                                szName = m_szMonitorName + ":"  + szLabel;
                            }
                            else
                                szName = m_szMonitorName + ":" + m_szHostName;
                            if(m_szPoint.empty())
                                m_szPoint = "1";
                            if(m_szNetworkset == "true")
                                m_szPoint = "0";

                            if(AddNodeAttrib(mainnode, "sv_name", szName) && AddNodeAttrib(mainnode,"sv_monitortype", chMTID) 
                                && AddNodeAttrib(mainnode, "sv_intpos", m_szPoint))
                            {                            
                                //saveDisableByParent(mainnode, 3, m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
                                if(saveBaseParam(objMonitor, szLabel) && saveAdvParam(objMonitor, szLabel) && saveCondition(objMonitor))
                                {
                                    saveDisableByParent(mainnode, Tree_DEVICE, m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
                                    string szRealIndex = AddNewMonitor(objMonitor, m_szDeviceIndex);
                                    if(!szRealIndex.empty())
                                    {
                                        int nIndex = FindIndexByID(szRealIndex);
                                        char szIndex[16] = {0};
                                        sprintf(szIndex, "%d", nIndex);

                                        AddNodeAttrib(mainnode, "sv_index", szIndex);
                                        emit AddMonitorSucc(szName,szRealIndex);
                                        InsertTable(szRealIndex, m_nMonitorID, m_szIDCUser, m_szIDCPwd);
                                        if(m_pSVUser && !m_pSVUser->isAdmin())
                                            m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_MONITOR);
                                    }
                                }
                            }
							strBatAddMonitorName += szEntityName;
							strBatAddMonitorName += ":";
							strBatAddMonitorName += szName;
 							strBatAddMonitorName += "  ";
                       }
                       CloseMonitor(objMonitor);
                    }
                }
            }
        }
    }
    emit backPreview();

	////插记录到UserOperateLog表
	//string szUserID("");
 //   if(m_pSVUser)
 //       szUserID = m_pSVUser->getUserID();
	//TTime mNowTime = TTime::GetCurrentTimeEx();
	//OperateLog m_pOperateLog;
	//m_pOperateLog.InsertOperateRecord("UserOperateLog", szUserID, mNowTime.Format(), m_szAddTitle, m_szOperateMonitor, strBatAddMonitorName);
}

void SVBatchAdd::cancel()
{
    emit backPreview();
}

bool SVBatchAdd::saveCondition(OBJECT & objMonitor)
{
    bool bNoError = true;

    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE)
        bNoError = m_pErrCond->SaveCondition(alertnode);
    else
        bNoError = false;

    if(bNoError)
    {
        alertnode = GetMonitorWarningAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE)
            bNoError = m_pWarnCond->SaveCondition(alertnode);
        else
            bNoError = false;
    }

    if(bNoError)
    {
        alertnode = GetMonitorGoodAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE)
            bNoError = m_pGoodCond->SaveCondition(alertnode);
        else
        {
            bNoError = false;
        }
    }

    return bNoError;
}

bool SVBatchAdd::saveAdvParam(OBJECT & objMonitor, string &szLabel)
{
    bool bNoError = true;
    MAPNODE advnode = GetMonitorAdvanceParameterNode(objMonitor);
    if(advnode != INVALID_VALUE)
    {
        listParamItem it;
        for(it = m_plsAdvParam->begin(); it != m_plsAdvParam->end(); it ++)
        {
            string szName (""), szValue ("");
            (*it)->getName(szName);
            if(szName == m_szDynName)
                szValue = (*it)->getValueByLabel(szLabel);
            else
                szValue = (*it)->getDefaultValue();
            string szAccount (""), szExpress (""), szAccValue ("");
            char szAfterAcc[32] = {0};

            szAccount = (*it)->getAccount();
            if(!szAccount.empty())
            {
                szExpress = (*it)->getExpress();

                listParamItem itTmp;

                for(itTmp = m_plsAdvParam->begin(); itTmp != m_plsAdvParam->end(); itTmp ++)
                {
                    if(szAccount.compare((*itTmp)->getName()) == 0)
                    {
                       (*itTmp)->getStringValue(szAccValue);
                        break;
                    }
                }
                int nAccValue = 0;
                switch(szExpress.c_str()[0])
                {
                case '+':
                    nAccValue = atoi(szValue.c_str()) + atoi(szAccValue.c_str());
                    break;
                case '-':
                    nAccValue = atoi(szValue.c_str()) - atoi(szAccValue.c_str());
                    break;
                case '*':
                    nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    break;
                case '/':
                    if(atoi(szAccValue.c_str()) != 0)
                        nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    else
                        nAccValue = atoi(szValue.c_str()) ;
                    break;
                }
                sprintf(szAfterAcc, "%d", nAccValue);
                AddNodeAttrib(advnode, szName + "1", szValue);
            }
            if(strlen(szAfterAcc) > 0)
                szValue = szAfterAcc;

            if(!AddNodeAttrib(advnode, szName, szValue))
            {
                bNoError = false;
                break;
            }
        }
    }
    return bNoError;
}

bool SVBatchAdd::saveBaseParam(OBJECT & objMonitor, string &szLabel)
{
    bool bNoError = true;
    MAPNODE basenode = GetMonitorParameter(objMonitor);
    if(basenode != INVALID_VALUE)
    {
        listParamItem it;
        for(it = m_plsBaseParam->begin(); it != m_plsBaseParam->end(); it ++)
        {
            string szName (""), szValue ("");
            (*it)->getName(szName);
            if(szName == m_szDynName)
                szValue = (*it)->getValueByLabel(szLabel);
            else
                szValue = (*it)->getDefaultValue();
            string szAccount (""), szExpress (""), szAccValue ("");
            char szAfterAcc[32] = {0};

            szAccount = (*it)->getAccount();
            if(!szAccount.empty())
            {
                szExpress = (*it)->getExpress();

                listParamItem itTmp;

                for(itTmp = m_plsBaseParam->begin(); itTmp != m_plsBaseParam->end(); itTmp ++)
                {
                    if(szAccount.compare((*itTmp)->getName()) == 0)
                    {
                       (*itTmp)->getStringValue(szAccValue);
                        break;
                    }
                }
                int nAccValue = 0;
                switch(szExpress.c_str()[0])
                {
                case '+':
                    nAccValue = atoi(szValue.c_str()) + atoi(szAccValue.c_str());
                    break;
                case '-':
                    nAccValue = atoi(szValue.c_str()) - atoi(szAccValue.c_str());
                    break;
                case '*':
                    nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    break;
                case '/':
                    if(atoi(szAccValue.c_str()) != 0)
                        nAccValue = atoi(szValue.c_str()) * atoi(szAccValue.c_str());
                    else
                        nAccValue = atoi(szValue.c_str()) ;
                    break;
                }
                sprintf(szAfterAcc, "%d", nAccValue);
                AddNodeAttrib(basenode, szName + "1", szValue);
            }
            if(strlen(szAfterAcc) > 0)
                szValue = szAfterAcc;
            if(!AddNodeAttrib(basenode, szName, szValue))
            {
                bNoError = false;
                break;
            }
        }
        AddNodeAttrib(basenode, "sv_description", "");
        AddNodeAttrib(basenode, "sv_reportdesc", "");
        AddNodeAttrib(basenode, "sv_plan", "7*24");
        AddNodeAttrib(basenode, "sv_checkerr", "false");
        AddNodeAttrib(basenode, "sv_errfreq", "0");
        AddNodeAttrib(basenode, "sv_errfrequint", "1");
        AddNodeAttrib(basenode, "sv_errfreqsave", "");
    }
    return bNoError;
}

void SVBatchAdd::addValueList(string &szDynName)
{
    clearlist();
    m_szMonitorName = szDynName;

    if(m_pMonitorName)
    {
        m_pMonitorName->setText(szDynName);
    }

    if(m_pList)
    {
        listParamItem it;
        for(it = m_pDynList->begin(); it != m_pDynList->end(); it ++)
        {
            m_szDynName = (*it)->getName();
            (*it)->AddDynList(m_pList, m_pSVList);
            break;
        }
        int nRow = m_pList->numRows();
        for(int i = 1; i < nRow; i++)
        {
            if((i + 1) % 2 == 0)
                m_pList->GetRow(i)->setStyleClass("tr1");
            else
                m_pList->GetRow(i)->setStyleClass("tr2");

            WCheckBox * pCheck = new WCheckBox("", m_pList->elementAt(i, 0));
            if(pCheck)
            {
                SVTableCell svCell;
                svCell.setType(adCheckBox);
                svCell.setValue(pCheck);
                m_pSVList.WriteCell(i, 0, svCell);
            }
            m_pList->elementAt(i, 0)->setStyleClass("cell_5");
        }
    }
}

void SVBatchAdd::selall()
{
    for(irow it = m_pSVList.begin(); it != m_pSVList.end(); it++ )
    {
        SVTableCell *pcell = (*it).second.Cell(0);
        if ( pcell )
        {
            if (pcell->Type() == adCheckBox)
            {
                ((WCheckBox*)pcell->Value())->setChecked(m_pSelAll->isChecked());
            }
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}
