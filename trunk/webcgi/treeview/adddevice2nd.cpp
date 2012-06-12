/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// adddevice2nd.cpp
// ����豸�ĵڶ����������豸����չʾ�豸�Ĳ���
// �༭�豸Ҳ�ڴ��ļ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "adddevice2nd.h"
#include "resstring.h"
#include "listtable.h"
#include "advanceparam.h"
#include "rightview.h"
#include "mainview.h"
#include "treeview.h"
#include "basefunc.h"
#include "basedefine.h"
#include "eccobjfunc.h"
#include "debuginfor.h"
#include "paramitem.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WText"

#include "../userright/User.h"

#include "../base/OperateLog.h"

#include "../../base/des.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice2nd::CEccAddDevice2nd(WContainerWidget *parent):
CEccBaseTable(parent),
m_pGeneral(NULL),
m_pAdvance(NULL),
m_pName(NULL),
m_pNameErr(NULL),
m_szParentID(""),
m_szEditIndex(""),
m_szDTType(""),
m_szDllName(""),
m_szFuncName(""),
m_szQuickAdd(""),
m_szQuickAddSel(""),
m_szNetworkset(""),
m_pTest(NULL),
m_pSave(NULL),
m_pCancel(NULL),
m_pBack(NULL),
m_pHideButton(NULL)
{
    setStyleClass("panel");
    initForm(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˵�� ����豸
// ����
//      ��������
//      �豸����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::AddDeviceByType(string szParent, string szDTName)
{
    ResetData();

    m_szDllName     = "";
    m_szFuncName    = "";
    m_szQuickAdd    = "";
    m_szQuickAddSel = "";
    m_szNetworkset  = "";

    m_bHasDynamic   = false;

    m_szParentID    = szParent;
    m_szDTType      = szDTName;
    m_szEditIndex   = "";

    m_lsDyn.clear();
    list<CEccParamItem*>::iterator lstItem;
    // ɾ����ǰ����������
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
        delete (CEccParamItem*)(*lstItem);

    m_lsBasicParam.clear();

    enumBaseParam();
    createBaseParam();

    if(m_pTest)
    {
        if(m_szDllName.empty() || m_szFuncName.empty())
            m_pTest->hide();
        else
            m_pTest->show();
    }

    if(m_pBack)
        m_pBack->show();

    if(m_pSave)
    {
        m_pSave->setText(SVResString::getResString("IDS_Add"));
        m_pSave->setToolTip(SVResString::getResString("IDS_Add_Device_Tip"));
    }

    if(m_pCancel)
    {
        m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
    }

    if(m_pAdvance)
        m_pAdvance->setSEID(FindSEID(m_szParentID));

    string szCmd("hiddenbar();");
    if(m_pHideButton)
    {
        if(!m_pHideButton->getEncodeCmd("xclicked()").empty())
        {
            szCmd = "update('" + m_pHideButton->getEncodeCmd("xclicked()") + "');" + szCmd ;
        }
    }

    if(m_pTitle)
        m_pTitle->setText( SVResString::getResString("IDS_Add") + SVResString::getResString("IDS_Device"));

    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::Cancel()
{
    CEccMainView::m_pRightView->showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createAdvance()
{
    int nRow = m_pContent->numRows();

    m_pAdvance = new CEccAdvanceTable(m_pContent->elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createBaseParam()
{
    if(m_pGeneral)
    {
        m_pGeneral->showSubTable();

        WTable *pSubTable = m_pGeneral->getListTable();
        if(pSubTable)
        {
            pSubTable->clear();
            m_lsHelp.clear();
            // ѭ������ÿ�������еĿؼ�
            list<CEccParamItem*>::iterator lstItem;
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // �Ƿ��и���ֵ
                if((*lstItem)->isHasFollow())
                {
                    // �õ�����ֵ && ���ø���ֵ
                    string szFollow = (*lstItem)->getFollow();
                    if(!szFollow.empty())
                    {
                        list<CEccParamItem*>::iterator ittmp ;
                        // ö��ÿ������
                        for(ittmp = m_lsBasicParam.begin(); ittmp != m_lsBasicParam.end(); ittmp ++)
                        {
                            // �Ƿ�ƥ��
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                (*lstItem)->setFollowItem((*ittmp));
                                break;
                            }
                        }
                    }
                }
                // �����ؼ�
                (*lstItem)->CreateControl(pSubTable, m_lsHelp, m_bShowHelp);
                // �Ƿ��Ƕ�̬����
                if((*lstItem)->isDynamic())
                {
                    m_lsDyn.push_back((*lstItem));
                    m_bHasDynamic = true;
                }
            }

            //
            createDeviceName(pSubTable);
            // ö��ÿһ������
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // ���������Ƿ���_MachineName�����Ƿ���Ҫ���豸���ƶ�̬��
                if(strcmp((*lstItem)->getName(), "_MachineName") == 0 || (*lstItem)->isSynTitle())
                {
                    // ��̬��
                    if(m_szEditIndex.empty() && m_pName != NULL && (*lstItem)->getControl() != NULL)
                    {
                        WInteractWidget* pEdit = (*lstItem)->getControl();
                        string szCmd = "onkeyup='Synchronization(\"" + pEdit->formName() +
                            "\",\"" + m_pName->formName() + "\")'";
                        strcpy(pEdit->contextmenu_, szCmd.c_str());
                    }
                }
                else if(strcmp((*lstItem)->getName(), "_ProtocolType") == 0 && (*lstItem)->getControl() != NULL)
                {// ���⴦��_ProtocolType
                    list<CEccParamItem*>::iterator lsItem;
                    for(lsItem = m_lsBasicParam.begin(); lsItem != m_lsBasicParam.end(); lsItem ++)
                    {
                        if(strcmp((*lsItem)->getName(), "_Port") == 0 && (*lstItem)->getControl() != NULL)
                        {
                            string szCmd = "onchange='ChangePort(this.options[this.value].text ,\"" 
                                + (*lsItem)->getControl()->formName() + "\")'";
                            strcpy((*lstItem)->getControl()->contextmenu_, szCmd.c_str());
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����豸����
// ����
//      �豸�������ڵı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createDeviceName(WTable *pTable)
{
    // �õ���ǰ����
    int nRow = pTable->numRows();
    // ˵��
    new WText(SVResString::getResString("IDS_Title"), pTable->elementAt(nRow, 0));
    // ���ӣ���ɫ*����ʶΪ������
    new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

    // �������������
    m_pName = new WLineEdit("", pTable->elementAt(nRow, 1));
    if(m_pName)
        m_pName->setStyleClass("Cell_40");

    // ���������ı�
    WText *pNameHelp = new WText(SVResString::getResString("IDS_Host_Label_Help"), pTable->elementAt(nRow + 1, 1));
    if(pNameHelp)
    {
        pNameHelp->hide();
        pTable->elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des");
        m_lsHelp.push_back(pNameHelp);
    }

    m_pNameErr = new WText(SVResString::getResString("IDS_Host_Label_Error"), pTable->elementAt(nRow + 2, 1));            
    if (m_pNameErr)
    {
        pTable->elementAt(nRow + 2, 1)->setStyleClass("table_data_input_error");
        m_pNameErr->hide();
    }

    // ������Ԫ���뷽ʽΪ���϶���
    pTable->GetRow(0)->setStyleClass("padding_top");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    pTable->elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
    pTable->elementAt(nRow, 1)->setStyleClass("table_data_text");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����������Ϣ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createGeneral()
{
    int nRow = m_pContent->numRows();

    m_pGeneral = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
    if(m_pGeneral)
    {
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Infor_Title"));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createOperate()
{
    if(m_pOperate)
    {
        int nRow = m_pOperate->numRows();
        // ��һ��
        m_pBack = new CEccButton(SVResString::getResString("IDS_Back_One_Step"), SVResString::getResString("IDS_Back_Device_List_Tip"),
            "", m_pOperate->elementAt(nRow, 0));
        if(m_pBack)
        {
            WObject::connect(m_pBack, SIGNAL(clicked()), "showbar();", this, SLOT(Forward()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(0, 1));

        // ����
        m_pSave = new CEccImportButton(SVResString::getResString("IDS_Add"), SVResString::getResString("IDS_Add_Device_Tip"),
            "", m_pOperate->elementAt(nRow, 2));
        if(m_pSave)
        {
            WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(SaveDevice()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(0, 3));

        // ȡ��
        m_pCancel = new CEccButton(SVResString::getResString("IDS_Cancel_Add"), SVResString::getResString("IDS_Cancel_Add_Device_Tip"), 
            "", m_pOperate->elementAt(nRow, 4));
        if(m_pCancel)
        {
            WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        // ����
        new WText("&nbsp;", m_pOperate->elementAt(0, 5));
        m_pTest = new CEccButton(SVResString::getResString("IDS_Test"), SVResString::getResString("IDS_Curent_Test_Tip"),
            "", m_pOperate->elementAt(nRow, 6));
        if(m_pTest)
        {
            WObject::connect(m_pTest, SIGNAL(clicked()), "showbar();", SLOT(TestDevice()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        nRow = static_cast<WTableCell*>(m_pOperate->parent())->row();
        elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �༭�豸
// ����
//      ���༭�豸������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::EditDevice(string szDeviceID)
{
    // ���� �豸����
	m_DeviceParam.clear();

    ResetData();

    m_szDllName     = "";
    m_szFuncName    = "";
    m_szQuickAdd    = "";
    m_szQuickAddSel = "";
    m_szNetworkset  = "";

    m_bHasDynamic   = false;

    m_szParentID    = "";
    m_szEditIndex   = szDeviceID;

    // �����ϵõ�ָ���豸
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szDeviceID);
    if(pNode)
    {
        const CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
        // �õ��豸����
        m_szDTType = pDevice->getRealDeviceType();
        
        m_lsDyn.clear();
        list<CEccParamItem*>::iterator lstItem;
        // ɾ����ǰ����������
        for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            delete (CEccParamItem*)(*lstItem);

        m_lsBasicParam.clear();

        // ö�ٻ�������
        enumBaseParam();
        // ö�ٸ߼�����
        createBaseParam();

        // ���豸
        OBJECT objDevice = GetEntity(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(objDevice != INVALID_VALUE)
        {
            // �õ����ڵ�
            MAPNODE mainNode = GetEntityMainAttribNode(objDevice);
            if(mainNode != INVALID_VALUE)
            { 
                list<CEccParamItem*>::iterator lstItem;
                string szName(""), szValue("");
                // �õ��������Բ���ֵ
                for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
                {
                    FindNodeValue(mainNode, (*lstItem)->getName(), szValue);
                    (*lstItem)->setStringValue(szValue);
                    if((*lstItem)->isRun())
                        m_DeviceParam[(*lstItem)->getName()] = szValue;
                }
            }
            // �ر��豸
            CloseEntity(objDevice);
        }

        // �Ƿ���Բ����豸
        if(m_szDllName.empty() || m_szFuncName.empty())
            if(m_pTest)
                m_pTest->hide();

        // �����豸����
        if(m_pName)
            m_pName->setText(pDevice->getName());

        // ���ñ�����
        if(m_pTitle)
            m_pTitle->setText( SVResString::getResString("IDS_Edit") + pDevice->getName() + SVResString::getResString("IDS_Device"));

        // ���ø߼�����
        if(m_pAdvance)
        {
            // ����
            m_pAdvance->setDepends(pDevice->getDependsID());
            // ����
            m_pAdvance->setDescription(pDevice->getDescription());
            // ��������
            m_pAdvance->setCondition(pDevice->getCondition());
            // SE����
            m_pAdvance->setSEID(FindSEID(szDeviceID));
        }

        // ���� ��һ�� ��ť
        if(m_pBack)
            m_pBack->hide();

        // ���� ���� ��ť����ʾ���ֺ���ʾ��Ϣ
        if(m_pSave)
        {
            m_pSave->setText(SVResString::getResString("IDS_Save"));
            m_pSave->setToolTip(SVResString::getResString("IDS_Save_Tip"));
        }

        // ���� ȡ�� ��ť����ʾ���ֺ���ʾ��Ϣ
        if(m_pCancel)
        {
            m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
            m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Edit_Device_Tip"));
        }
    }

    string szCmd("hiddenbar();");
    if(m_pHideButton)
    {
        if(!m_pHideButton->getEncodeCmd("xclicked()").empty())
        {
            szCmd = "update('" + m_pHideButton->getEncodeCmd("xclicked()") + "');" + szCmd ;
        }
    }
    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö�ٻ�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::enumBaseParam()
{
    // ���豸ģ��
    OBJECT objDevice = GetEntityTemplet(m_szDTType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {// �ɹ�
        LISTITEM lsItem;
        // �õ�ÿ������
        if(FindETContrlFirst(objDevice, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                CEccParamItem *param = new CEccParamItem(objNode);
                m_lsBasicParam.push_back(param);
            }
        }
        // ���ڵ�
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            FindNodeValue(node, svDLL,           m_szDllName);           // ��̬���ӿ�����
            FindNodeValue(node, svFunc,          m_szFuncName);          // ��������
            FindNodeValue(node, svQuickAdd,      m_szQuickAdd);          // �������
			FindNodeValue(node, svQuickAddSel,   m_szQuickAddSel);       // �������ȱʡѡ��
            FindNodeValue(node, svNetworkSet,    m_szNetworkset);        // �Ƿ��������豸

            if(m_szNetworkset.empty())
                m_szNetworkset = "false";
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��һ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::Forward()
{
    CEccMainView::m_pRightView->showAddDevice1st(m_szParentID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::initForm(bool bHasHelp)
{
    // �������ʼ������
    CEccBaseTable::initForm(bHasHelp);

    // ���ñ���������
    setTitle(SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device"));

    if(m_pContent)
    {
        CEccBaseTable::setContentCellStyle("height95p");
        // �����������Ա�
        createGeneral();
        // �����߼����Ա�
        createAdvance();
    }

    // ��������
    createOperate();
    // �������ذ�ť
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::ResetData()
{
    // ���ø߼�����
    if(m_pAdvance)
        m_pAdvance->ResetData();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����豸������Ӻͱ༭�豸��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::SaveDevice()
{
    list<CEccParamItem*>::iterator lstItem;
    bool bError = false;
    bool bChanged = false;
    bool bAddAttribSucc = true;

    unsigned long ulStart = GetTickCount();

    string szDevName(""), szOSType(""), szRealIndex("");

    if(m_pNameErr)
        m_pNameErr->hide();

    // У���������
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        if(!(*lstItem)->checkValue())
        {
            if(m_pGeneral)
                m_pGeneral->showSubTable();
            bError = true;
        }
    }

    // У������
    if(!checkName(szDevName))
    {
        if(m_pNameErr)
            m_pNameErr->show();
        bError = true;
    }

    string szOpt("Add new Device");
    
    // ��������
    if(bError)
    {
        m_pGeneral->showSubTable();
        goto exitSave;
    }

    OBJECT objDevice = INVALID_VALUE;
    if(m_szEditIndex.empty())
    {// �Ƿ����ڱ༭�豸
        if(m_szNetworkset == "true")
        {// ������豸�������豸
            // �õ���ǰ��ʹ�������豸����
            int nNetworkCount = getUsingNetworkCount(); 
            // ��1
            nNetworkCount ++;
            // �ж��Ƿ񳬵�
            if(!checkNetworkPoint(nNetworkCount))
            {
                // ��ʾ������Ϣ
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                    SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                return;
            }
        }
        // ����һ���豸
        objDevice = CreateEntity();
    }
    else
	{// ���ڱ༭�豸
        // ���豸
        szOpt = "Edit Device " + m_szEditIndex;
        objDevice = GetEntity(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
	}

    // ����/���豸�Ƿ�ɹ�
    if(objDevice != INVALID_VALUE)
    {
        // �õ����ڵ�
        MAPNODE mainNode = GetEntityMainAttribNode(objDevice);
        if(mainNode != INVALID_VALUE)
        {
			map<string, string, less<string> >::iterator paramItem;
            // ����ÿһ������
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                string szValue(""), szName("");
                (*lstItem)->getStringValue(szValue);
                (*lstItem)->getName(szName);
                if(strcmp(szName.c_str(), svOSType) == 0)
                    szOSType = szValue;

				if(bChanged)
				{
					paramItem = m_DeviceParam.find(szName);
					if(paramItem != m_DeviceParam.end())
						if(paramItem->second != szValue)
							bChanged = true;
				}
                // �����ڵ����������
                if(!AddNodeAttrib(mainNode, szName, szValue))
                    bError = true;
            }

            if(!bError && AddNodeAttrib(mainNode, svName, szDevName) && AddNodeAttrib(mainNode, svNetworkSet, m_szNetworkset)
                &&AddNodeAttrib(mainNode, svDeviceType, m_szDTType))
                if(m_pAdvance && m_pAdvance->SaveAdvanceParam(mainNode))
                    bAddAttribSucc = true;

            string szDesc(""), szDepends(""), szCondition("");
            if(m_pAdvance)
            {
                szDesc = m_pAdvance->getDescription();
                szDepends = m_pAdvance->getDepends();
                szCondition = m_pAdvance->getConditon();
            }

            if(bAddAttribSucc && m_szEditIndex.empty())
            {
                if(!IsSVSEID(m_szParentID))
                    saveDisableByParent(mainNode, SiteView_ECC_Device, m_szParentID);

                szRealIndex = AddNewEntity(objDevice, m_szParentID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                // ������ɹ������������ɹ���Ϣ
                if(!szRealIndex.empty())
                {    
                    int nIndex = FindIndexByID(szRealIndex);
                    nIndex = CEccTreeView::AppendDevice(szRealIndex, szDevName, szDesc, szDepends, szCondition, 
                        m_szDTType, szOSType, m_szNetworkset);
                    char szIndex[16] = {0};
                    sprintf(szIndex, "%d", nIndex);
                    AddNodeAttrib(mainNode, svShowIndex, szIndex);

                    CEccTreeView::m_SVSEUser.AddUserScopeAllRight(szRealIndex, SiteView_ECC_Device);
                }
            }
            else if(bAddAttribSucc)
            {
                if(SubmitEntity(objDevice, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                {
                    if((m_pAdvance && m_pAdvance->isDependsChanged()) || bChanged)
                    {
                        string szQueueName(getConfigTrackQueueName(m_szEditIndex));
                        CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                        if(!PushMessage(szQueueName, "ENTITY:UPDATE", m_szEditIndex.c_str(), 
                            static_cast<int>(m_szEditIndex.length()) + 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                            PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
                    }
                    CEccTreeView::EditDevice(m_szEditIndex, szDevName, szDesc, szDepends, szCondition);
                }
            }

            CloseEntity(objDevice);
        }
    }

    // �Ƿ����ڱ༭�豸
    // ����µ��豸�ҿ��Կ�����Ӽ����
    if(m_szEditIndex.empty() && !m_szQuickAdd.empty())
    {
        string szRun("");
        MakeRunParamString(szRun, false);

        szOpt = "Show Quick Add Monitor Frame";

        // ��ʾ����豸������
        CEccMainView::m_pRightView->showAddDevice3rd(szRealIndex, szDevName, szRun, m_szQuickAdd, m_szQuickAddSel, m_szNetworkset);
        return;
    }
    else if(m_szEditIndex.empty())
    {// ���ܿ�����Ӽ����
        // �������豸
        CEccMainView::m_pRightView->showNewDevice(szRealIndex);
    }
    else
    {// �༭�豸
        CEccMainView::m_pRightView->showMainForm();
    }

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccAddDevice2nd.SaveDevice", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccAddDevice2nd.SaveDevice", szOpt, 
        0, GetTickCount() - ulStart);

exitSave:
    if(WebSession::js_af_up.empty())
        WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ/���ذ�����Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::ShowHideHelp()
{
    m_bShowHelp = !m_bShowHelp;

    if(m_pAdvance)
        m_pAdvance->ShowHideHelp(m_bShowHelp);

    list<WText*>::iterator it;
    for(it = this->m_lsHelp.begin(); it != m_lsHelp.end(); it++)
    {
        if(m_bShowHelp)
            (*it)->show();
        else
            (*it)->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::TestDevice()
{
    list<CEccParamItem *>::iterator lstItem;

    string szQuery("");
    MakeRunParamString(szQuery);
    // ������Բ�������ʾ�豸���Խ���
    if(!szQuery.empty())
    {
        szQuery = szQuery + "devicetype=" + m_szDTType + "&seid=";
        if(m_szEditIndex.empty())
            szQuery += FindSEID(m_szParentID);
        else
            szQuery += FindSEID(m_szEditIndex);

        szQuery = "showtestdevice('testdevice.exe?" + szQuery +"');" ;
        PrintDebugString(szQuery.c_str());
    }
    szQuery = "hiddenbar();" + szQuery;
    WebSession::js_af_up = szQuery; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// У������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice2nd::checkName(string &szName)
{
    if(m_pName)
    {
        szName = m_pName->text();
        szName = strtriml(szName.c_str());
        szName = strtrimr(szName.c_str());

        if(!szName.empty())
            return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������ذ�ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::createHideButton()
{
    int nRow = numRows();
    m_pHideButton = new WPushButton("", elementAt(nRow, 0));
    if(m_pHideButton)
    {
        m_pHideButton->hide();
        WObject::connect(m_pHideButton, SIGNAL(clicked()), "showbar();", this, SLOT(EnumDynData()), 
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö�ٶ�̬����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::EnumDynData()
{
    string szQuery("");
    // ö��ÿ����̬���ԵĶ�̬����
    listItem    lstItem;
    for(lstItem = m_lsDyn.begin(); lstItem != m_lsDyn.end(); lstItem ++)
    {
        if(m_szEditIndex.empty())
            (*lstItem)->enumDynValue(szQuery, m_szParentID);
        else
            (*lstItem)->enumDynValue(szQuery, m_szEditIndex);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö��ÿ������ʱ���Թ��������ַ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice2nd::MakeRunParamString(string &szRunParam, bool bEncode)
{
    list<CEccParamItem *>::iterator lstItem;

    // ö��ÿһ�����ԵĲ���
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        // �Ƿ�������ʱ��Ҫ���Բ���
        if((*lstItem)->isRun())
        {
            // ���ֵ�Ƿ���ȷ
            if(!(*lstItem)->checkValue())
            {
                szRunParam = "";
                break;
            }
            // �õ����Բ������ƺ�ֵ
            string szValue(""), szName("");
            (*lstItem)->getName(szName);
            (*lstItem)->getStringValue(szValue);
            // �Ƿ�������
            if((*lstItem)->isPassword())
            {// ��
                //����
                char szOutput[512] = {0};
                Des des;
                if(des.Decrypt(szValue.c_str(), szOutput))
                    szValue = szOutput;
            }
            // ����
            if(bEncode)
                szValue = url_Encode(szValue.c_str());
            szRunParam = szRunParam + szName + "=" + szValue + "&";
        }
    }
}
