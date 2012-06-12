#include "adddevice2nd.h"
#include "showtable.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../../base/des.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char *szMsg);
extern void WriteLogFile(const char *pszFile, const char *pszMsg);

#include "../base/basetype.h"

typedef bool(ListDevice)(const char* szQuery, char* szReturn, int &nSize);

#include "resstring.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDevice::SVDevice(WContainerWidget * parent, CUser *pUser, string szIDCUser, string szIDCPwd, string szDeviceType):
WTable(parent)
{
    m_bShowHelp = false;                            // �Ƿ���ʾ����
    m_pGeneral = NULL;                              // ������Ϣ����
    m_pDeviceTitle = NULL;                          // �߼���Ϣ����
    m_pContentTable = NULL;                         // ���ݱ�
    m_pSaveMonitor = NULL;                          // ������ѡ�������ť
 
    m_pSubContent = NULL;                           // �����ݱ�
    m_pAdvTable = NULL;                             // �߼�������
    m_pSVUser = pUser;                              // ��ǰ�û�Ȩ��
    m_pQuickAdd = NULL;
    // �����豸 ���� ȡ�� ö�ٶ�̬���� ����
    m_pSave = m_pBack = m_pCancel = m_pListDynBtn = m_pTest = NULL;


    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;

    //loadCondition();                                // ���ط�ֵ����

    // ��
    connect(&m_mapMinitor, SIGNAL(mapped(int)), this, SLOT(selAllByMonitorType(int)));

    initForm();                                     // ��ʼ��
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumBaseParam
// ˵�� ö���豸ģ���ж���Ļ�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::enumBaseParam()
{
    // ����
    m_szQuickAdd = "";
	m_szQuickAddSel = "";
    m_szDllName = "";
    m_szFuncName = "";
    // ���豸ģ��
    OBJECT objDevice = GetEntityTemplet(m_szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// �ɹ�
        LISTITEM lsItem;
        // �õ�ÿ������
        if( FindETContrlFirst(objDevice, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                SVParamItem *param = new SVParamItem(objNode);
                m_lsBasicParam.push_back(param);
            }
        }
        // ���ڵ�
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            FindNodeValue(node, "sv_dll", m_szDllName);             // ��̬���ӿ�����
            FindNodeValue(node, "sv_func", m_szFuncName);           // ��������
            FindNodeValue(node, "sv_quickadd", m_szQuickAdd);       // �������
			FindNodeValue(node, "sv_quickaddsel", m_szQuickAddSel); // �������ȱʡѡ��
            FindNodeValue(node, "sv_network", m_szNetworkset);      // �Ƿ��������豸
            if(m_szNetworkset.empty())
                m_szNetworkset = "false";
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createGeneral
// ˵�� ������ʾ�������Եı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createGeneral()
{
    //�õ���ǰ���ݱ������
    int nRow = m_pSubContent->numRows();
    // �Ƿ��Ѵ����˱�
    if(m_pGeneral == NULL)
        m_pGeneral = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    if(m_pGeneral)
    {// �����ɹ�
        m_pGeneral->show();
        // ���ñ�������
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Title").c_str());
        list<SVParamItem*>::iterator lstItem;
        // �����ӱ�
        WTable *pSub = m_pGeneral->createSubTable();
        if(pSub)
        {
            // ѭ������ÿ�������еĿؼ�
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // �Ƿ��и���ֵ
                if((*lstItem)->isHasFollow())
                {
                    // �õ�����ֵ && ���ø���ֵ
                    string szFollow = (*lstItem)->getFollow();
                    if(!szFollow.empty())
                    {
                        list<SVParamItem*>::iterator ittmp ;
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
                (*lstItem)->CreateControl(pSub);
                // �Ƿ��Ƕ�̬����
                if((*lstItem)->isDynamic())
                {
                    m_lsDyn.push_back((*lstItem));
                    m_bHasDynamic = true;
                }
            }
            
            // �����豸����
            createHostName(pSub);
            // ö��ÿһ������
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // ���������Ƿ���_MachineName�����Ƿ���Ҫ���豸���ƶ�̬��
                if(strcmp((*lstItem)->getName(), "_MachineName") == 0 || (*lstItem)->isSynTitle())
                {
                    // ��̬��
                    if(m_pDeviceTitle != NULL && (*lstItem)->getControl() != NULL)
                    {
                        WInteractWidget* pEdit = (*lstItem)->getControl();
                        string szCmd = "onkeyup='Synchronization(\"" + pEdit->formName() +
                            "\",\"" + m_pDeviceTitle->formName() + "\")'";
                        strcpy(pEdit->contextmenu_, szCmd.c_str());
                    }
                }
                else if(strcmp((*lstItem)->getName(), "_ProtocolType") == 0 && (*lstItem)->getControl() != NULL)
                {// ���⴦��_ProtocolType
                    list<SVParamItem*>::iterator lsItem;
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
// ���� createOperate
// ˵�� ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createOperate()
{
    // �õ���ǰ����
    int nRow = numRows();
    // ���� m_pBack ��ť
    if(!m_pBack)
    {
        m_pBack = new WPushButton(SVResString::getResString("IDS_Back_One_Step"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pBack)
        {
            // ���� Tooltip
            m_pBack->setToolTip(SVResString::getResString("IDS_Back_Device_List_Tip"));
            // �� click �¼�
            WObject::connect(m_pBack, SIGNAL(clicked()), "showbar();", this, SLOT(Preview()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // �������԰�ť
    if(!m_pTest)
    {
        // ����һ��ť����һ������
        new WText("&nbsp;",this->elementAt(nRow,0));
        m_pTest = new WPushButton(SVResString::getResString("IDS_Test"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pTest)
        {
            // ���� Tooltip
            m_pTest->setToolTip(SVResString::getResString("IDS_Curent_Test_Tip"));
            // �� click �¼�
            WObject::connect(m_pTest, SIGNAL(clicked()), "showbar();", this, SLOT(testDevice()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // �������水ť
    if(!m_pSave)
    {
        // ����һ��ť����һ������
        new WText("&nbsp;",this->elementAt(nRow,0));
        m_pSave = new WPushButton(SVResString::getResString("IDS_Add"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pSave)
        {
            // ���� Tooltip
            m_pSave->setToolTip(SVResString::getResString("IDS_Add_Device_Tip"));
            // �� click �¼�
            WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(Save()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // ���� ȡ������������ť
    if(!m_pCancel)
    {
        // ����һ��ť����һ������
        new WText("&nbsp;",this->elementAt(nRow,0));
        m_pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
        if(m_pCancel)
        {
            // ���� Tooltip
            m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
            // �� click �¼�
            WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // �����оٶ�̬������ť
    if(!m_pListDynBtn)
    {
        m_pListDynBtn = new WPushButton("list dyn", (WContainerWidget*)elementAt(nRow, 0));
        if(m_pListDynBtn)
        {
            // ���ش˰�ť���ڽ�������ʾ����
            m_pListDynBtn->hide();
            // �� click �¼�
            WObject::connect(m_pListDynBtn, SIGNAL(clicked()), "showbar();", this, SLOT(listDynParam()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // ���ñ��еĶ������ԣ��ײ����ж��룩
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createAdv
// ˵�� �����߼�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createAdv()
{
    // �õ������ݱ�����
    int nRow = m_pSubContent->numRows();
    // �����������߼�������
    if(m_pAdvTable == NULL)
    m_pAdvTable = new SVDependTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));

    if(m_pAdvTable)
    {
        m_pAdvTable->setDescription(string(""));
        m_pAdvTable->resetDepend();
        m_pAdvTable->setCodition(string(""));
        m_pAdvTable->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createTitle
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createTitle()
{
    // �õ���ǰ����
    int nRow = numRows();
    // ������
    m_pTitle = new WText("", (WContainerWidget*)elementAt(nRow, 0));
    // ���ô��е���ʾ��ʽ��
    elementAt(nRow,0)->setStyleClass("t1title");

    // ��һ��
    nRow ++;
    // ����һ���ӱ����ݱ�
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // ����������
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            // ������ʽ��
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        // ���� ���ݱ� ��ʾ��ʽ
        m_pContentTable->setStyleClass("t5");
        // Cell Padding && Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);
        // ���ô��е���ʾ��ʽ��
        elementAt(nRow, 0)->setStyleClass("t7");
        
        // �õ����ݱ������
        nRow = m_pContentTable->numRows();
        // �����±������ݱ�
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // �������ݱ�ǰ�еĶ��뷽ʽ
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initForm
// ˵�� ��ʼ��ҳ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::initForm()
{
    setStyleClass("t5");
    // ����
    createTitle();

    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        createHelp();
    }

    // ��������
    createOperate();
    // ����������Ӳ���
    createQuickAddOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initQuickAdd
// ˵�� ��ʼ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::initQuickAdd()
{
    // ��Ӽ����ģ��
    AddMonitorTempList();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Cancel
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::Cancel()
{
    // �������޸ĵ�����
    m_szEditIndex = "";
    // ���������������¼�
    emit backMain();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Preview
// ˵�� �����豸ģ���б�����ѡ���豸����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::Preview()
{
    emit backPreview();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Save
// ˵�� ���浱ǰ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::Save()
{
    list<SVParamItem *>::iterator lstItem;
    string szDeviceHost("");
    string szDescription(""), szDepends(""), szCondition("");

	m_bChanged = false;
    m_szQueryString = "";
    m_szDeviceID = "";
    if(m_pDeviceTitle)
        m_szDeviceName = m_pDeviceTitle->text();

    bool bError = false;

    // �ж��豸�����Ƿ�Ϊ��
    if(m_szDeviceName.empty())
    {// ��ʾ������Ϣ 
DeviceNameEmpty:
        if(m_pHostHelp)
        {
            m_pHostHelp->setStyleClass("errors");
            m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Error"));
            m_pHostHelp->show();
            m_pGeneral->ShowSubTable();
        }
        bError = true;
    }
    else
    {
        // ȥ�����ҿո�
        m_szDeviceName = strtriml(m_szDeviceName.c_str());
        m_szDeviceName = strtrimr(m_szDeviceName.c_str());
        // �����Ƿ�Ϊ��
        if(m_szDeviceName.empty())
            goto DeviceNameEmpty;
        // ����/��ʾ������Ϣ
        if(m_pHostHelp)
        {
            m_pHostHelp->setStyleClass("helps");
            m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Help"));
            if(m_bShowHelp)
                m_pHostHelp->show();
            else
                m_pHostHelp->hide();
        }
    }

    // �ж����Բ����Ƿ���д��ȷ
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        if(!(*lstItem)->checkValue())
        {
            if(m_pGeneral)
                m_pGeneral->ShowSubTable();
            bError = true;
        }
    }

    // �Ƿ�������
    if(bError)
    {
        WebSession::js_af_up = "hiddenbar();";
        return;
    }

    // �߼����Ա��Ƿ񴴽��ɹ�
    if(m_pAdvTable)
    {
        // ����
        m_pAdvTable->getDescription(szDescription);
        // ����
        m_pAdvTable->getDepend(szDepends);
        // ��������
        m_pAdvTable->getCodition(szCondition);
    }

    OBJECT objDevice = INVALID_VALUE;
    if(m_szEditIndex.empty())
    {// �Ƿ����ڱ༭�豸
        if(m_szNetworkset == "true")
        {// ������豸�������豸
            // �õ���ǰ��ʹ�������豸����
            int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd); 
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
        objDevice = GetEntity(m_szEditIndex, m_szIDCUser, m_szIDCPwd);
        // �ж����������Ƿ��޸�
		if(m_pAdvTable && m_pAdvTable->isDependChange())
			m_bChanged = true;
	}
    // ����/���豸�Ƿ�ɹ�
    if(objDevice != INVALID_VALUE)
    {
        // �õ����ڵ�
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
			map<string, string, less<string> >::iterator paramItem;
            // ����ÿһ������
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                string szValue(""), szName("");
                (*lstItem)->getStringValue(szValue); 
                (*lstItem)->getName(szName);
				if(!m_bChanged)
				{
					paramItem = m_DeviceParam.find(szName);
					if(paramItem != m_DeviceParam.end())
						if(paramItem->second != szValue)
							m_bChanged = true;
				}
                // �����ڵ����������
                if(!AddNodeAttrib(mainnode, szName, szValue))
                    bError = true;
            }
            // �Ƿ�ʧ��
            if(!bError)
            {
                // ��� ���� �豸���� ���� ���� �������� �Ƿ��������豸 ����
                if(AddNodeAttrib(mainnode, "sv_name", m_szDeviceName) &&  AddNodeAttrib(mainnode, "sv_devicetype", m_szDeviceType) &&
                    AddNodeAttrib(mainnode, "sv_description", szDescription) && AddNodeAttrib(mainnode, "sv_dependson", szDepends) &&
                    AddNodeAttrib(mainnode, "sv_dependscondition", szCondition) && AddNodeAttrib(mainnode, "sv_network", m_szNetworkset))
                {
                    if(m_szEditIndex.empty())
                    {// �������ڱ༭�豸
                        // ���ݸ���Ľ�ֹ��ʽ������ǰ�豸�Ƿ񱻽�ֹ
                        saveDisableByParent(mainnode, Tree_GROUP, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
                        // ����µ��豸
                        string szRealIndex = AddNewEntity(objDevice, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
                        if(!szRealIndex.empty())
                        {// ��ӳɹ�
                            m_szDeviceID = szRealIndex;
                            // �õ���ʵ����
                            int nIndex = FindIndexByID(szRealIndex);
                            char szIndex[16] = {0};
                            sprintf(szIndex, "%d", nIndex);
                            // ��� ��ʾ���� ����
                            AddNodeAttrib(mainnode, "sv_index", szIndex);
                            // ���Ȩ��
                            if(m_pSVUser && !m_pSVUser->isAdmin())
                                m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_DEVICE);
                            // ���� �ɹ�����豸 �¼�
                            emit AddDeviceSucc(m_szDeviceName,szRealIndex);

                            // �õ�ÿһ������
                            list<SVParamItem *>::iterator lstItem;
                            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
                            {
                                if((*lstItem)->isRun())
                                {
                                    if(!(*lstItem)->checkValue())
                                    {
                                        m_szQueryString = "";
                                        break;
                                    }
                                    string szValue(""), szName("");

                                    (*lstItem)->getStringValue(szValue);
                                    (*lstItem)->getName(szName);
                                    if((*lstItem)->isPassword())
                                    {
                                        char szOutput[512] = {0};
                                        Des des;
                                        if(des.Decrypt(szValue.c_str(), szOutput))
                                            szValue = szOutput;
                                    }
                                    m_szQueryString = m_szQueryString + szName + "=" + szValue + "\v";
                                }
                            }
                            // ɾ�����ݱ�����������
                            if(m_pGeneral) m_pGeneral->hide();
                            if(m_pAdvTable) m_pAdvTable->hide();
                            if(m_pSubContent) m_pSubContent->elementAt(0, 0)->hide();
                            if(m_pQuickAdd) m_pQuickAdd->show();
                            // ���� ���� ���水ť����
                            if(m_pSave)
                                ((WTableCell*)m_pSave->parent())->hide();
                            // ��ʾ ������Ӽ��������
                            if(m_pCancelSaveMonitor)
                                ((WTableCell*)m_pCancelSaveMonitor->parent())->show();
                            // ��������������
                            m_pTitle->setText(SVResString::getResString("IDS_Quick_Add_Monitor_Title"));
                            // �Ƿ�֧�ֿ������
                            if(!m_szQuickAdd.empty())
                            {
                                // �������
                                initQuickAdd();
                            }
                            else
                            {// ��֧�ֿ������
                                // ���� ����������豸 ����
                                emit EnterNewDevice(m_szDeviceID);
                            }
                       }
                    }
                    else
                    {// ���ڱ༭�豸
                        // �ύ
                        if(SubmitEntity(objDevice, m_szIDCUser, m_szIDCPwd))
                        {// �ύ�ɹ���
                            // ���� �ɹ��޸��豸 �¼�
                            emit EditDeviceSucc(m_szDeviceName, m_szEditIndex);
                        }
						if(m_bChanged)
						{
                            string szQueueName(getConfigTrackQueueName(m_szEditIndex));
						    CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                            if(!::PushMessage(szQueueName, "ENTITY:UPDATE", m_szEditIndex.c_str(), 
                                                static_cast<unsigned int>(m_szEditIndex.length()) + 1, m_szIDCUser, m_szIDCPwd))
								PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
						}
                        // ���ô˺��� ������ҳ��
						Cancel();
                    }
                }
            }
        }
    }
    // �������ڱ༭�豸����ֵ
    m_szEditIndex = "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createHelp
// ˵�� ����������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHelp()
{
    // ����
    int nRow = m_pSubContent->numRows();
    WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
    if(pHelp)
    {
        pHelp->setStyleClass("imgbutton");
        pHelp->setToolTip(SVResString::getResString("IDS_Help"));
        WObject::connect(pHelp, SIGNAL(clicked()), "showbar();", this, SLOT(showHelp()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showHelp
// ˵�� ��ʾ�����ذ�����Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::showHelp()
{
    m_bShowHelp = !m_bShowHelp;

    list<SVParamItem *>::iterator lstItem;

    // ö��ÿһ������
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        (*lstItem)->m_bError = false;
        (*lstItem)->showHelp(m_bShowHelp); 
    }

    // �߼����Ա���ʾ/���ذ���
    m_pAdvTable->showHelp(m_bShowHelp);
    //
    if(m_pHostHelp)
    {
        if(m_bShowHelp)
            m_pHostHelp->show();
        else
            m_pHostHelp->hide();

        m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Help"));
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createHostName
// ˵�� �����豸����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHostName(WTable  * pTable)
{
    if(m_pDeviceTitle == NULL)
    {
        // �õ���ǰ����
        int nRow = pTable->numRows();
        // ˵��
        new WText(SVResString::getResString("IDS_Title"), (WContainerWidget*)pTable->elementAt(nRow, 0));
        // ���ӣ���ɫ*����ʶΪ������
        new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

        // ������Ԫ���뷽ʽΪ���϶���
        pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
        pTable->elementAt(nRow, 0)->setStyleClass("cell_10");

        // �������������
        m_pDeviceTitle = new WLineEdit("", (WContainerWidget*)pTable->elementAt(nRow, 1));
        if(m_pDeviceTitle)
            m_pDeviceTitle->setStyleClass("Cell_40");

        // ���������ı�
        new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
        m_pHostHelp = new WText(SVResString::getResString("IDS_Host_Label_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
        if(m_pHostHelp)
        {
            m_pHostHelp->hide();
            m_pHostHelp->setStyleClass("helps");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ClearData
// ˵�� ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::ClearData(string &szIndex)
{
    // �����Ƿ��������豸
    m_szNetworkset = "";
    if(m_pAdvTable)
        m_pAdvTable->setUserID(FindSEID(m_szParentIndex));

    list<SVParamItem *>::iterator lstItem;
    m_szEditIndex = "";
    if(!szIndex.empty())
    {// ��������ڱ༭�豸
        m_bHasDynamic = false;
        m_lsDyn.clear();
        // ɾ����ǰ����������
        for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            delete (SVParamItem*)(*lstItem);
        m_lsBasicParam.clear();
        
        // ����������Ա��е���������
        if(m_pGeneral && m_pGeneral->createSubTable())
            m_pGeneral->createSubTable()->clear();

        m_pHostHelp = NULL;
        m_pDeviceTitle = NULL;

        // ����ʾ������Ϣ
        m_bShowHelp = false;
        // �豸��������
        m_szDeviceType = szIndex;
        // ����������
        m_szFuncName = "";
        m_szDllName = "";

        // ö�ٻ�������
        enumBaseParam();
        createGeneral();
        createAdv();

        if(m_pSubContent) m_pSubContent->elementAt(0, 0)->show();

        if(m_pQuickAdd == NULL)
        {
            int nRow = m_pSubContent->numRows();
            m_pQuickAdd = new WTable(m_pSubContent->elementAt(nRow, 0));
        }
        if(m_pQuickAdd)
        {
            m_pQuickAdd->hide();
            m_pQuickAdd->setStyleClass("t3");
            m_pQuickAdd->clear();
        }

        // ��ʾ������ť��
        if(m_pSave)
            ((WTableCell*)m_pSave->parent())->show();
        // ���ؿ�����Ӱ�ť��
        if(m_pCancelSaveMonitor)
            ((WTableCell*)m_pCancelSaveMonitor->parent())->hide();

        // ���԰�ť�Ƿ񴴽��ɹ�
        if(m_pTest)
        {
            // ����/��ʾ���԰�ť
            m_pTest->show();
            if(m_szDllName.empty() || m_szFuncName.empty())
                m_pTest->hide();
        }
    }
    // 
    m_bShowHelp = true;
    showHelp();

    // ��ʾ�����豸ģ�尴ť
    if(m_pBack) m_pBack->show();
    if(m_pSave) 
    {
        m_pSave->setText(SVResString::getResString("IDS_Add"));
        m_pSave->setToolTip(SVResString::getResString("IDS_Add_Device_Tip"));
    }
    if(m_pCancel)
    {
        m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
        setTitle(m_szDeviceType);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditDeviceByID
// ˵�� �����豸ID���������༭�豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::EditDeviceByID(string &szIndex)
{
    // ���༭�豸�����Ƿ�Ϊ��
    if(szIndex.empty())
        return;
	
    // ���� �豸����
	m_DeviceParam.clear();

    // ���豸
    OBJECT objDevice = GetEntity(szIndex, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// �ɹ�
        // ���ڵ�
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            // �豸����
            string szDeviceType("");
            list<SVParamItem *>::iterator lstItem;
            if(FindNodeValue(mainnode, "sv_devicetype", szDeviceType))
            {
                // �����豸���������ع�����
                ClearData(szDeviceType);
                // ���༭�豸������ֵ
                m_szEditIndex = szIndex;
                if(m_pAdvTable)
                    m_pAdvTable->setUserID(FindSEID(m_szEditIndex));
                // ���ط����豸ģ���б�ť
                m_pBack->hide();
                // �����ı���tooltip
                m_pSave->setText(SVResString::getResString("IDS_Save"));
                m_pSave->setToolTip(SVResString::getResString("IDS_Save_Tip"));
                m_pCancel->setText(SVResString::getResString("IDS_Cancel"));
                m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Edit_Device_Tip"));

                // , ���ƣ� ��������������������
                string szLabel(""), szName("") , szDesc(""), szCondition(""), szDepends("");
                FindNodeValue(mainnode, "sv_name", szName);
                FindNodeValue(mainnode, "sv_description", szDesc);
                FindNodeValue(mainnode, "sv_dependscondition", szCondition);
                FindNodeValue(mainnode, "sv_dependson", szDepends);

                if(m_pAdvTable)
                {
                    m_pAdvTable->setDescription(szDesc);
                    m_pAdvTable->setDepend(szDepends);
                    m_pAdvTable->setCodition(szCondition);
                }
                // �����豸������ʾ�ı�
                if(m_pDeviceTitle)
                    m_pDeviceTitle->setText(szName);
                // ����������
                if(m_pTitle)
                    m_pTitle->setText( SVResString::getResString("IDS_Edit") + szName + SVResString::getResString("IDS_Device"));

                // ����ÿ�����ԵĲ���
                for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
                {  
                    string szName(""), szValue("");
                    (*lstItem)->getName(szName);
                    FindNodeValue(mainnode, szName, szValue);
                    //int nPos = static_cast<int>(szValue.find("\\", 0));
                    //while (nPos >= 0)
                    //{
                    //    szValue = szValue.substr(0, nPos ) + "\\" + 
                    //        szValue.substr(nPos, szValue.length() - nPos);
                    //    nPos += 2;
                    //    nPos = static_cast<int>(szValue.find("\\", nPos));
                    //}
                    (*lstItem)->setStringValue(szValue);
					m_DeviceParam[szName] = szValue;
                }                
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� setTitle
// ˵�� �����豸�������ñ��� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::setTitle(string &szDeviceType)
{
    // ���豸ģ��
    OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// �ɹ�
        // ���ڵ�
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szName("");
            // �豸���͵���ʾ����
            if(!FindNodeValue(node, "sv_label", szName))
                FindNodeValue(node, "sv_name", szName);
            else
                szName = SVResString::getResString(szName.c_str());

            // ����������������
            if(szName.empty())
            {
                if(m_szEditIndex.empty())
                    m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device"));
                else
                    m_pTitle->setText(SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Device"));
            }
            else
            {
                if(m_szEditIndex.empty())
                    m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + szName);
            }
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� testDevice
// ˵�� �����豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::testDevice()
{
    list<SVParamItem *>::iterator lstItem;

    string szQuery("");
    // ö��ÿһ�����ԵĲ���
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        // �Ƿ�������ʱ��Ҫ���Բ���
        if((*lstItem)->isRun())
        {
            // ���ֵ�Ƿ���ȷ
            if(!(*lstItem)->checkValue())
            {
                szQuery = "";
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
            szValue = url_Encode(szValue.c_str());
            szQuery = szQuery + szName + "=" + szValue + "&";
        }
    }
    // ������Բ�������ʾ�豸���Խ���
    if(!szQuery.empty())
    {
        szQuery = szQuery + "devicetype=" + m_szDeviceType + "&seid=";
        if(m_szEditIndex.empty())
            szQuery += FindSEID(m_szParentIndex);
        else
            szQuery += FindSEID(m_szEditIndex);

        szQuery = "showtestdevice('testdevice.exe?" + szQuery +"');" ;
        PrintDebugString(szQuery.c_str());
    }
    szQuery = "hiddenbar();" + szQuery;
    WebSession::js_af_up = szQuery;   
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� listDynParam
// ˵�� ö�ٶ�̬����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::listDynParam()
{
    listItem lstItem;
    string szQuery("");
    // ö��ÿ����̬���ԵĶ�̬����
    for(lstItem = m_lsDyn.begin(); lstItem != m_lsDyn.end(); lstItem ++)
        (*lstItem)->enumDynValue(szQuery, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� requesDynData
// ˵�� ����̬����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::requesDynData()
{
    // ö�ٶ�̬���ݰ�ť�Ƿ񱻳ɹ�����
    if(m_pListDynBtn)
    {
        // �õ� click ��
        string szCmd = m_pListDynBtn->getEncodeCmd("xclicked()");
        if(!szCmd.empty() && m_bHasDynamic)
            WebSession::js_af_up = "update('" + szCmd + "');";
        else
            WebSession::js_af_up = "hiddenbar();";
    }
    else
            WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createQuickAddOperate
// ˵�� ����������Ӳ�����ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createQuickAddOperate()
{
    // �õ���ǰ����
    int nRow = numRows();
    // ���� ������ѡ��ť
    WPushButton *m_pSaveMonitor = new WPushButton(SVResString::getResString("IDS_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pSaveMonitor)
    {
        // tooltip
        m_pSaveMonitor->setToolTip(SVResString::getResString("IDS_Save_Sel_Monitor_Tip"));
        // �� click ʱ��
        WObject::connect(m_pSaveMonitor, SIGNAL(clicked()), "showbar();", this, SLOT(saveAllSelMonitors()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    // ��һ�ؼ�����һ������
    new WText("&nbsp;",this->elementAt(nRow,0));
    // ȡ����Ӽ������ť
    m_pCancelSaveMonitor = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pCancelSaveMonitor)
    {
        // tooltip
        m_pCancelSaveMonitor->setToolTip(SVResString::getResString("IDS_Cancel_Add_Monitor_Tip"));
        // �� click
        WObject::connect(m_pCancelSaveMonitor, SIGNAL(clicked()), "showbar();", this, SLOT(enterDevice()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    // ö�ٶ�̬���� ��ť
    m_pListDynData = new WPushButton("list dyn", (WContainerWidget*)elementAt(nRow, 0));
    if(m_pListDynData)
    {
        // ����
        m_pListDynData->hide();
        // �� click
        WObject::connect(m_pListDynData, SIGNAL(clicked()), "showbar();", this, SLOT(listDynData()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    // ��ǰ�еĶ��뷽ʽ �ײ�����
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    // ���ص�ǰ��
    //GetRow(nRow)->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddMonitorTempList
// ˵�� ���Ӹ��ݼ����ģ�崴����ѡ������б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::AddMonitorTempList()
{
    m_lsMonitorTemplet.clear();
    m_svValueList.clear();

    list<string> lstMonitors;
    // ��������ַ���Ϊ�� �� �ɹ� �����ɹ�
    if(!m_szQuickAdd.empty() && sv_split(m_szQuickAdd.c_str(), ",", lstMonitors, false) > 0)
    {
        list<string>::iterator lstItem;
        int nPos = 0;
        bool bSelect;
        // ö��ÿһ�����ģ��
        for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
        {
            // ȱʡ�Ƿ�ѡ��
			bSelect = false;
			nPos = static_cast<int>(m_szQuickAddSel.find((*lstItem).c_str()));
			if(nPos >= 0)
			{
				const char *pValue = m_szQuickAddSel.c_str();
				if( *(pValue + nPos +(*lstItem).length()) == ',' || *(pValue + nPos +(*lstItem).length()) == '\0')
					bSelect = true;
			}
            // ���ݼ����ģ��IDö����Ҫ���Բ����м�¼
            int nMonitorID = atoi((*lstItem).c_str());
            OBJECT objMonitor = GetMonitorTemplet(nMonitorID, m_szIDCUser, m_szIDCPwd);
            if(objMonitor != INVALID_VALUE)
            {
                MAPNODE node = GetMTMainAttribNode(objMonitor);
                monitor_templet monitor;
                monitor.nMonitorID = nMonitorID;
				monitor.bSel = bSelect;
                // ���� ���� ��չ��̬�⣨ö�ٶ�̬����ʹ�ã�ȱʡʹ��sv_dll��
                // ��չ������
                // ��չ����
                if(!FindNodeValue(node, "sv_label", monitor.szName))
                    FindNodeValue(node, "sv_name", monitor.szName);
                else
                    monitor.szName = SVResString::getResString(monitor.szName.c_str());

                if(FindNodeValue(node, "sv_description", monitor.szLabel))
                    monitor.szLabel = SVResString::getResString(monitor.szLabel.c_str());

                FindNodeValue(node, "sv_extradll", monitor.szDllName);
                if(monitor.szDllName.empty())
                    FindNodeValue(node, "sv_dll", monitor.szDllName);
                FindNodeValue(node, "sv_extrafunc", monitor.szFuncName);
                FindNodeValue(node, "sv_extrasave", monitor.szSaveName);
                list<monitor_templet>::iterator lstItem;
                // �����ݱ��Ƿ�ɹ�����
                if(m_pQuickAdd)
                {
                    // �����ݱ�ĵ�ǰ����
                    int nRow = m_pQuickAdd->numRows();
                    WCheckBox *pCheck = NULL;
                    // �Ƿ���Ҫʹ�ö�̬����
                    if(!monitor.szDllName.empty() && !monitor.szFuncName.empty())
                    {// ��Ҫ
                        // ����ȫѡ checkbox
                        WCheckBox* pSelAll = new WCheckBox("", m_pQuickAdd->elementAt(nRow, 0));
                        if(pSelAll)
                        {
                            // tooltip
                            pSelAll->setToolTip(SVResString::getResString("IDS_All_Select"));
                            // �Ƿ�ѡ��
                            pSelAll->setChecked(bSelect);
                            // �� click
                            WObject::connect(pSelAll, SIGNAL(clicked()), "showbar();", &m_mapMinitor, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                            m_mapMinitor.setMapping(pSelAll, nMonitorID);
                        }
                        // ��������ı�
                        new WText(monitor.szLabel, m_pQuickAdd->elementAt(nRow, 0));
                        // ���ô��е���ʾ��ʽ��
                        m_pQuickAdd->GetRow(nRow)->setStyleClass("t2title");
                        // ��չ�������Բ��������Ƿ�Ϊ��
                        if(monitor.szSaveName.empty())
                        {
                            // ��ʾ������Ϣ
                            new WText(SVResString::getResString("IDS_Monitor_Templet_Error"), m_pQuickAdd->elementAt(nRow + 1, 0));
                        }
                        else
                        {
                            // �����ӱ��Ա��ܷ��ö�̬����
                            monitor.pTable = new WTable(m_pQuickAdd->elementAt(nRow + 1, 0));
                            if(monitor.pTable)
                            {
                                monitor.pTable->setStyleClass("t3");
                                new WText("loading...", monitor.pTable->elementAt(0, 0));
                            }
                        }
                    }
                    else
                    {
                        // ��������ı�
                        new WText(monitor.szLabel, m_pQuickAdd->elementAt(nRow, 0));
                        // ���ô��е���ʾ��ʽ��
                        m_pQuickAdd->GetRow(nRow)->setStyleClass("t2title");
                        // ����һ���ڴ�����ʾ����Ϊ������������ֵ�checkbox
                        pCheck = new WCheckBox(monitor.szName, m_pQuickAdd->elementAt(nRow + 1, 0));							
                    }
                    
                    if(pCheck)
                    {// �����ɹ�
                        // �Ƿ�ѡ��
						pCheck->setChecked(bSelect);
                        char szIndex[32] = {0};
                        sprintf(szIndex, "%d", nMonitorID);
                        SVTableCell svCell;
                        svCell.setType(adCheckBox);
                        svCell.setValue(pCheck);
                        // ��¼
                        m_svValueList.WriteCell((nRow + 1) * 10, 0, svCell);
                        SVTableRow *pRow = m_svValueList.Row((nRow + 1) * 10);
                        if (pRow)
                            pRow->setTag(nMonitorID);
                    }
                }
                m_lsMonitorTemplet.push_back(monitor);

                CloseMonitorTemplet(objMonitor);
            }
        }
    }
    string szCmd = "hiddenbar();";
    if(m_pListDynData)
        if(!m_pListDynData->getEncodeCmd("xclicked()").empty())
            szCmd = "update('" + m_pListDynData->getEncodeCmd("xclicked()") + "');";

    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddDynData
// ˵�� ������ʾ��̬����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::AddDynData(WTable * pTable, const char* pszQuery, const int &nQuerySize, const int &nMonitorID, 
                            const string &szDllName, const string &szFuncName, const string &szSaveName, const bool &bSel)
{
// �Ƿ�����Windows ƽ̨������
    bool bGetDyn = false;
    char szReturn [svBufferSize] = {0};
    int nSize = sizeof(szReturn);

    if(FindSEID(m_szDeviceID) == "1")
    {
#ifdef WIN32
    string szDllName(makeDllName(szDllName));
    string szMsg = "Dll Name: " + szDllName + " Function Name: " + szFuncName;
    PrintDebugString(szMsg.c_str());
    // �򿪶�̬���ӿ�
    HINSTANCE hDll = LoadLibrary(szDllName.c_str());
    if (hDll)
    {
        // ��ú���
        ListDevice* func = (ListDevice*)GetProcAddress(hDll, szFuncName.c_str());
        if (func && szReturn)
        {            
            bGetDyn = (*func)(pszQuery, szReturn, nSize);
        }
        // �رն�̬���ӿ�
        FreeLibrary(hDll);
    }
#else
#endif
    }
    else
    {
        bGetDyn = ReadWriteDynQueue(m_szDeviceID, szDllName, szFuncName, pszQuery, nQuerySize, szReturn, nSize, m_szIDCUser, m_szIDCPwd);
    }

    if(bGetDyn)
    {
        int nRow = pTable->numRows();
        char *pos = strstr(szReturn, "error");
        if(pos == NULL)
        {
            pos = szReturn;
            map<string , string, less<string> > dynData;
            while(*pos != '\0')
            {
                int nSize = static_cast<int>(strlen(pos));
                char *pPosition = strchr(pos, '=');
                if(pPosition)
                {
                    (*pPosition) = '\0';
                    ++pPosition;
                    dynData[pPosition] = pos;
                }
                pos = pos + nSize + 1;
            }
            
            // Ϊÿһ����̬���ݴ���һ��
            int nParentRow = nMonitorID * 10;
            map<string , string, less<string> >::iterator it;
            for(it = dynData.begin(); it != dynData.end(); it++)
            {
                WCheckBox *pCheck = new WCheckBox(it->first, pTable->elementAt(nRow, 0));
                if(pCheck)
                {
					pCheck->setChecked(bSel);
                    SVTableCell svCell;
                    svCell.setType(adCheckBox);
                    svCell.setValue(pCheck);
                    svCell.setProperty(it->second.c_str());
                    m_svValueList.WriteCell(nParentRow + nRow, 0, svCell);
                    SVTableRow *pRow = m_svValueList.Row(nParentRow + nRow);
                    if (pRow)
                    {
                        pRow->setProperty(szSaveName.c_str());
                        pRow->setTag(nMonitorID);
                    }
                }
                // ��������ʾ��ʽ
                if((nRow + 1) % 2 == 0)
                    pTable->GetRow(nRow)->setStyleClass("tr1");
                else
                    pTable->GetRow(nRow)->setStyleClass("tr2");
                nRow ++;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� listDynData
// ˵�� �оٶ�̬����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::listDynData()
{ 
    // ö��ÿ�������ģ��
    list<monitor_templet>::iterator lstItem;
    for(lstItem = m_lsMonitorTemplet.begin(); lstItem != m_lsMonitorTemplet.end(); lstItem ++)
    {      
        char szTpl [32] = {0};
        // ���ö�̬���ò���
        int nLen = sprintf(szTpl, "_TemplateID=%d\v", (*lstItem).nMonitorID);
        string szQuery = szTpl;
        szQuery += m_szQueryString;
        int nSize = static_cast<int>(szQuery.length()) + 2;
        char *pszQueryString = new char[nSize];
        if(pszQueryString)
        { 
            memset(pszQueryString, 0 , nSize);
            strcpy(pszQueryString , szQuery.c_str());
            PrintDebugString(pszQueryString);
            char *pPos = pszQueryString;
            while((*pPos) != '\0' )
            {
                if((*pPos) == '\v')
                    (*pPos) = '\0';
                pPos ++;
            }
            if((*lstItem).pTable)
            {
                (*lstItem).pTable->clear();
                AddDynData((*lstItem).pTable, pszQueryString,  nSize, (*lstItem).nMonitorID, (*lstItem).szDllName, 
                    (*lstItem).szFuncName, (*lstItem).szSaveName, (*lstItem).bSel);
            }
            delete []pszQueryString;
        } 
    }

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enterDevice
// ˵�� �����豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::enterDevice()
{ 
    // ���� ����������豸 �¼�
    if(!m_szDeviceID.empty())
        emit EnterNewDevice(m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveAllSelMonitors
// ˵�� ����������ѡ�ļ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::saveAllSelMonitors()
{
	string strQuickAddMonitorName("");
	//��ȡ�豸������
    string szEntityName ("");
    // ���豸
    OBJECT objEntity = GetEntity(m_szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objEntity != INVALID_VALUE)
    {// �򿪳ɹ�
        // ���ڵ�
        MAPNODE devnode = GetEntityMainAttribNode(objEntity);
        // �õ��豸��ʾ����
        if(devnode != INVALID_VALUE)
        {
            FindNodeValue(devnode, "sv_name", szEntityName);
        }
        // �ر��豸
        CloseEntity(objEntity);
    }

    irow it;
    int nPos = 0;
    // ö��ÿһ������
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        // ��ǰ�����Ƿ�ѡ��
        SVTableCell *pCell =  (*it).second.Cell(0);
        if(pCell && pCell->Type() == adCheckBox)
        {
            string szText = ((WCheckBox*)pCell->Value())->label()->text();
            nPos = static_cast<int>(szText.find(SVResString::getResString("IDS_Monitor_Point_Lack_Tip")));
            if(nPos >= 0)
                szText = szText.substr(0, nPos);

            ((WCheckBox*)pCell->Value())->label()->setText(szText);
            if(((WCheckBox*)pCell->Value())->isChecked())
            {// ѡ��״̬
                string szLable = ((WCheckBox*)pCell->Value())->label()->text();
                // ��������
                if(!saveMonitor((*it).second.getTag(),(*it).second.getProperty(), pCell->Property(), szLable.c_str()))
                {// ����ʧ�ܣ� ��ʾ������Ϣ
                    ((WCheckBox*)pCell->Value())->label()->setText(((WCheckBox*)pCell->Value())->label()->text() + 
                        SVResString::getResString("IDS_Monitor_Point_Lack_Tip"));
                    ((WCheckBox*)pCell->Value())->label()->setStyleClass("errortip");
                    if(m_pSaveMonitor)
                        m_pSaveMonitor->setEnabled(false);
                    return;
				}
                // 
				strQuickAddMonitorName += szEntityName;
				strQuickAddMonitorName += ":";
				strQuickAddMonitorName += szLable;
 				strQuickAddMonitorName += "  ";                
            }
        }
    }
    if(!m_szDeviceID.empty())
        emit EnterNewDevice(m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveMonitor
// ˵�� ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitor(int nMonitorID, const char* pszSaveName, const char *pszExtraParam, const char *pszExtraLable)
{
    // ���������
    OBJECT objMonitor = CreateMonitor();
    // �򿪼����ģ��
    OBJECT objMonitorTmp = GetMonitorTemplet(nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE && objMonitorTmp != INVALID_VALUE)
    {// ����������ʹ�ģ�嶼�ɹ�
        // �õ������ģ�����ڵ�
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        // �õ���������ڵ�
        MAPNODE nodeTmp  = GetMTMainAttribNode(objMonitorTmp);
        if(mainnode != INVALID_VALUE && nodeTmp != INVALID_VALUE)
        {
            char chMTID [8] = {0};
            string szName (""), szLabel (""), szPoint ("");;
            string szMonitorName ("");
            if(!FindNodeValue(nodeTmp, "sv_label", szMonitorName))
                FindNodeValue(nodeTmp, "sv_name", szMonitorName);
            else
               szMonitorName  = SVResString::getResString(szMonitorName.c_str());
            if(m_szNetworkset != "true")
            {// ���������豸
                FindNodeValue(nodeTmp, "sv_intpos", szPoint);
                
                if(szPoint.empty())
                    szPoint = "1";
                // ���ü��������
                int nMonitorCount = getUsingMonitorCount(m_szIDCUser, m_szIDCPwd);

                int nPoint = atoi(szPoint.c_str());
                if(nPoint <= 0)
                    nPoint = 0;
                nMonitorCount += nPoint;
                // ����Ƿ񳬵�
                if(!checkMonitorsPoint(nMonitorCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            else
            {// �����豸
                // ���������豸
                // �����豸���õ���
                int nNetworkCount = getUsingNetworkCount(m_szIDCUser, m_szIDCPwd, m_szDeviceID);
                // ����Ƿ񳬵�
                if(!checkNetworkPoint(nNetworkCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            // �Ƿ��������豸���������豸��������Ϊ��
            if(m_szNetworkset == "true")
                szPoint = "0";
            sprintf(chMTID, "%d", nMonitorID);
            if(pszExtraLable && strlen(pszExtraLable) > 0 && szMonitorName.compare(pszExtraLable) != 0)
                szName = szMonitorName + ":"  + pszExtraLable;
            else if(pszExtraParam && strlen(pszExtraParam) > 0)
                szName = szMonitorName + ":"  + pszExtraParam;
            else
                szName = szMonitorName;
            AddNodeAttrib(mainnode, "sv_name", szName);
            AddNodeAttrib(mainnode,"sv_monitortype", chMTID);
            AddNodeAttrib(mainnode, "sv_intpos", szPoint);
            saveDisableByParent(mainnode, Tree_DEVICE, m_szDeviceID, m_szIDCUser, m_szIDCPwd);
        }
        // �������������
        saveMonitorBaseParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // ������߼�����
        saveMonitorAdvParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // �������ֵⷧ
        saveMonitorCondition(objMonitor, objMonitorTmp);
        // ����µļ����
        string szRealIndex = AddNewMonitor(objMonitor, m_szDeviceID, m_szIDCUser, m_szIDCPwd);
        if(!szRealIndex.empty())
        {// �ɹ����
            // ������ʾ˳��
            int nIndex = FindIndexByID(szRealIndex);
            char szIndex[16] = {0};
            sprintf(szIndex, "%d", nIndex);
            AddNodeAttrib(mainnode, "sv_index", szIndex);
            
            // ����������ݱ�
            InsertTable(szRealIndex, nMonitorID, m_szIDCUser, m_szIDCPwd);
            // ����Ȩ��
            if(m_pSVUser && !m_pSVUser->isAdmin())
                m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_MONITOR);
        }
    }
    // �رռ����
    if(objMonitor != INVALID_VALUE)
        CloseMonitor(objMonitor);
    // �رռ����ģ��
    if(objMonitorTmp != INVALID_VALUE)
        CloseMonitorTemplet(objMonitorTmp);

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveMonitorAdvParam
// ˵�� ����߼�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitorAdvParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // ������߼��ڵ�
    MAPNODE objMonitorNode = GetMonitorAdvanceParameterNode(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // ö�ټ����ģ���ÿһ���߼�����
        if( FindMTAdvanceParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // �������� ȱʡֵ ���㷽ʽ
                string szName (""), szValue (""), szAccValue ("");
                FindNodeValue(objNode, "sv_name", szName);
                FindNodeValue(objNode, "sv_value", szValue);
                FindNodeValue(objNode, "sv_accountwith", szAccValue);
                if(!szAccValue.empty())
                    AddNodeAttrib(objMonitorNode, szName + "1", szValue);

                if(pszSaveName && strlen(pszSaveName) > 0 && szName.compare(pszSaveName) == 0)
                {
                    if(pszExtraParam && strlen(pszExtraParam) > 0)
                        AddNodeAttrib(objMonitorNode, szName, pszExtraParam);
                    else
                        AddNodeAttrib(objMonitorNode, szName, "");
                }
                else
                    AddNodeAttrib(objMonitorNode, szName, szValue);
            }
        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveMonitorBaseParam
// ˵�� �����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitorBaseParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // ����������ڵ�
    MAPNODE objMonitorNode = GetMonitorParameter(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // ö�ټ����ģ���ÿһ����������
        if( FindMTParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // ���Բ������� ȱʡֵ �Ƿ�������ֵ����
                string szName (""), szValue (""), szAccValue ("");
                FindNodeValue(objNode, "sv_name", szName);
                FindNodeValue(objNode, "sv_value", szValue);
                FindNodeValue(objNode, "sv_accountwith", szAccValue);
                if(!szAccValue.empty())
                    AddNodeAttrib(objMonitorNode, szName + "1", szValue);

                if(pszSaveName && strlen(pszSaveName) > 0 && szName.compare(pszSaveName) == 0)
                {
                    if(pszExtraParam && strlen(pszExtraParam) > 0)
                        AddNodeAttrib(objMonitorNode, szName, pszExtraParam);
                    else
                        AddNodeAttrib(objMonitorNode, szName, "");
                }
                else
                    AddNodeAttrib(objMonitorNode, szName, szValue);
            }
        }
        AddNodeAttrib(objMonitorNode, "sv_description", "");
        AddNodeAttrib(objMonitorNode, "sv_reportdesc", "");
        AddNodeAttrib(objMonitorNode, "sv_plan", "7*24");
        AddNodeAttrib(objMonitorNode, "sv_checkerr", "false");
        AddNodeAttrib(objMonitorNode, "sv_errfreqsave", "");
        AddNodeAttrib(objMonitorNode, "sv_errfreq", "0");
        AddNodeAttrib(objMonitorNode, "sv_errfrequint", "1");
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveMonitorCondition
// ˵�� ���������ļ�ֵⷧ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveMonitorCondition(OBJECT &objMonitor, OBJECT objMonitorTemp)
{
    // ����ֵ
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    MAPNODE alertnodeTmp = GetMTErrorAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // ���淧ֵ
    alertnode = GetMonitorWarningAlertCondition(objMonitor);
    alertnodeTmp = GetMTWarningAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // ������ֵ
    alertnode = GetMonitorGoodAlertCondition(objMonitor);
    alertnodeTmp = GetMTGoodAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// ���� loadCondition
//// ˵�� ������ѧ��������
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVDevice::loadCondition()
//{
//    m_lsCondition.push_back("==");
//    m_lsCondition.push_back("!=");
//    m_lsCondition.push_back(">");
//    m_lsCondition.push_back(">=");
//    m_lsCondition.push_back("<");
//    m_lsCondition.push_back("<=");
//    m_lsCondition.push_back("contains");
//    m_lsCondition.push_back("!contains");
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveAlertNodeValue
// ˵�� ���淧ֵ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::saveAlertNodeValue(MAPNODE &alertnode, MAPNODE &alertnodeTmp)
{
    string szRelationCount("");
    FindNodeValue(alertnodeTmp, "sv_conditioncount", szRelationCount);
    if(!szRelationCount.empty())
    {
        char szKey [16] = {0};
        string szCondition (""), szExpression(""), szReturn (""), szParamValue ("") , szRelation ("");
        int nCount = 0;

        AddNodeAttrib(alertnode, "sv_conditioncount", szRelationCount);

        FindNodeValue(alertnodeTmp, "sv_expression", szExpression);
        AddNodeAttrib(alertnode, "sv_expression", szExpression);

        nCount = atoi(szRelationCount.c_str());
        for(int i = 1; i <= nCount; i++)
        {   
            sprintf(szKey, "sv_relation%d", i);
            FindNodeValue(alertnodeTmp, szKey, szRelation);
            AddNodeAttrib(alertnode, szKey, szRelation);

            sprintf(szKey, "sv_paramname%d", i);
            FindNodeValue(alertnodeTmp, szKey, szReturn);
            AddNodeAttrib(alertnode, szKey, szReturn);

            sprintf(szKey, "sv_operate%d", i);
            FindNodeValue(alertnodeTmp, szKey, szCondition);
            AddNodeAttrib(alertnode, szKey, szCondition);
            
            sprintf(szKey, "sv_paramvalue%d", i);
            FindNodeValue(alertnodeTmp, szKey, szParamValue);
            AddNodeAttrib(alertnode, szKey, szParamValue);
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// ���� loadReturnParam
//// ˵�� ���ݼ����ģ����ط���ֵ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVDevice::loadReturnParam(OBJECT &objMonitorTemp, SVReturnMap &rtMap)
//{
//    LISTITEM lsItem;
//    //�õ�ÿһ������ֵ
//    if( FindMTReturnFirst(objMonitorTemp, lsItem))
//    {
//        MAPNODE objNode;
//        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
//        {
//            string szName (""), szLabel ("");
//            FindNodeValue(objNode, "sv_name", szName);
//            FindNodeValue(objNode, "sv_label", szLabel);
//            if(!szName.empty() && !szLabel.empty())
//                rtMap[szName] = szLabel;
//        }
//    }   
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� checkParamValue
// ˵�� ��ֵⷧ�Ƿ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVDevice::checkParamValue(string &szParam, SVReturnMap &rtMap)
{
    bool bNoError = false;
    if(szParam.empty())
        return false;
    SVReturnItem rtItem;
    for(rtItem = rtMap.begin(); rtItem != rtMap.end(); rtItem ++)
    {
        if((*rtItem).second == szParam)
        {
            szParam = (*rtItem).first;
            return true;
        }
    }
    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� selAllByMonitorType
// ˵�� ���ݼ����ģ��IDȫѡ�����͵����м����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::selAllByMonitorType(int nMonitorType)
{
    bool bSel = true;
    WCheckBox* pSelAll = reinterpret_cast<WCheckBox*>(m_mapMinitor.mapping(nMonitorType));
    if(pSelAll)
        bSel = pSelAll->isChecked();
    irow it;
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        if((*it).second.getTag() == nMonitorType)
        {
            SVTableCell *pCell =  (*it).second.Cell(0);
            if(pCell && pCell->Type() == adCheckBox)
                ((WCheckBox*)pCell->Value())->setChecked(bSel);
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
