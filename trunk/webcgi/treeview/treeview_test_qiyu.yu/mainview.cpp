#include "mainview.h"
#include "treeview.h"
#include "rightview.h"
#include "basedefine.h"
#include "debuginfor.h"
#include "eccobjfunc.h"

#include "../base/OperateLog.h"

#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WebSession.h"

#include "../userright/User.h"

#define WTGET

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ����̬��Ա����
CEccRightView * CEccMainView::m_pRightView = NULL;
CEccTreeView * CEccMainView::m_pTreeView = NULL;

string          CEccMainView::m_szAddr = "localhost";
string          CEccMainView::m_szIDCUser = "default";
string          CEccMainView::m_szGlobalEvent = "";
string          CEccMainView::m_szCurrentOpt = "";
string          CEccMainView::m_szLeftScroll = "";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccMainView::CEccMainView(WContainerWidget *parent):
WTable(parent),
m_pbtnConfirm(NULL),
m_pbtnRefresh(NULL),
m_pCurrentID(NULL),
m_pCurOperate(NULL),
m_szCurrentCopy(""),
m_szCurrentConfirm("")
{
    // ������ʽ��
    setStyleClass("panel");
    // �������ر��� 
    createHideObject();
    // �������
    createFrame();

    m_bFirstLoad = true;

    // ���õ�ǰ����ֵ
    if(m_pTreeView)
        m_szCurrentOpt = m_pTreeView->m_szCurSelIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::createFrame()
{
    // �õ���ǰ����
    int nRow = numRows();
    // �ڵ�ǰ���ڷֱ𴴽� �� ������С ����ͼ
    m_pTreeView = new CEccTreeView(elementAt(nRow, 0), GetWebUserID());
    // �滻��ͼƬ�ļ���
    WImage *pResize = new WImage("../Images/left.gif", elementAt(nRow,1));
    m_pRightView = new CEccRightView(elementAt(nRow, 2));

    // �������ı�����ʽ
    elementAt(nRow, 0)->setStyleClass("tree_bg");

    // ����������С���ɹ�
    if(pResize)
    {
        // ���ô�TD����ʽ��
        elementAt(nRow, 1)->setStyleClass("resize");
        // ����TD�Ĳ�����Ӧ
        strcpy(elementAt(nRow, 1)->contextmenu_, 
            "onmousedown='_canResize=true;this.setCapture(true)' "
            "onmouseup='this.releaseCapture();_canResize=false;'");
        
        pResize->setStyleClass("hand");
        sprintf(pResize->contextmenu_, "onclick='hideshowtree(this,\"%s\")'", elementAt(nRow, 0)->formName().c_str());
    }

    // ��������ͼ����ʽ��
    elementAt(nRow, 2)->setStyleClass("rightview");

    // ���������Ŀɲ�������
    //if(m_pTreeView)
    //    m_pTreeView->setLeftResizeName(elementAt(nRow, 0)->formName());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �õ����Ĳ�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CEccMainView::getTreeTableName()
{
    if(m_pTreeView)
        return m_pTreeView->formName();
    return "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���Ͻڵ�ĵ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::EccObjectClick()
{
    unsigned long ulStart = GetTickCount();
    if(m_pCurrentID && m_pRightView)
    {
        // ���赱ǰ��������
        m_szCurrentOpt = m_pCurrentID->text();
        // ��ǰ�����������������ϱ�ѡ��ڵ�
        if(m_szCurrentOpt != m_pTreeView->m_szCurSelIndex)
        {
            // ������ʽ��
            if(m_pTreeView->m_pCurSel)
                m_pTreeView->m_pCurSel->setStyleClass("treelink");

            // ��ǰ���ǲ����Ĳ���SE��
            if(m_szCurrentOpt != "0")
            {
                // �õ����ϵĽڵ�
                const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentOpt);
                if(pNode && pNode->m_pTreeText)
                {
                    // ������ʽ��
                    m_pTreeView->m_pCurSel = pNode->m_pTreeText;
                    m_pTreeView->m_szCurSelIndex = pNode->getECCIndex();
                    pNode->m_pTreeText->setStyleClass("treelinkactive");
                    m_pRightView->changeActive(pNode);
                }
            }
            else
            {
                // ѡ����SE ��
                m_pTreeView->m_szCurSelIndex = "0";
                if(m_pTreeView->m_objRootGroup.m_pTreeText)
                {                    
                    m_pTreeView->m_pCurSel = m_pTreeView->m_objRootGroup.m_pTreeText;
                    m_pTreeView->m_objRootGroup.m_pTreeText->setStyleClass("treelinkactive");
                }
                
                // ��ʾSE����ͼ
                m_pRightView->showSVSEView();
            }
        }
    }
    WebSession::js_af_up = "hiddenbar()";

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccObjectClick", "Enter Object--->" + m_szCurrentOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccObjectClick", "Enter Object--->" + m_szCurrentOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ڵ��Ҽ��˵��ĵ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::EccMenuClick()
{
    WebSession::js_af_up = "";

    string szOpt("");

    unsigned long ulStart = GetTickCount();

    // �Ƿ��Ǽ����
    bool bMonitor = false;
    // ˢ���¼�
    if(m_pbtnRefresh)
        m_szGlobalEvent = m_pbtnRefresh->getEncodeCmd("xclicked()");

    if(m_pCurrentID && m_pCurOperate && m_pRightView)
    {
        m_szCurrentOpt = m_pCurrentID->text();
        int nOperate = atoi(m_pCurOperate->text().c_str());
        const CEccTreeNode *pNode = NULL;

        // ����ÿ�����
        switch(nOperate)
        {
        case SV_ADD_GROUP:                              // �����
            szOpt = "Add new sub Group";
            m_pRightView->showAddGroupForm(m_szCurrentOpt);
            break;
        case SV_ADD_DEVICE:                             // ����豸
            szOpt = "Add new Device";
            m_pRightView->showAddDevice1st(m_szCurrentOpt);
            break;
        case SV_ADD_MONITOR:                            // ��Ӽ����
            szOpt = "Add new monitor";
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                m_pRightView->showAddMonitor1st(m_szCurrentOpt, pDevice->getRealDeviceType(), pDevice->isNetworkSet());
            }
            break;
        case SV_EDIT:                                   // �༭
            m_pRightView->showEditForm(m_szCurrentOpt, bMonitor);
            if(bMonitor)
                m_szCurrentOpt = FindParentID(m_szCurrentOpt);
            break;
        case SV_DELETE:                                 // ɾ��
            m_szCurrentConfirm = m_szCurrentOpt;
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                if(m_pbtnConfirm && !m_pbtnConfirm->getEncodeCmd("xclicked()").empty())
                {
                    if(pNode->getType() == SiteView_ECC_Group)
                    {
                        szOpt = "Delete Group";
                        WebSession::js_af_up = "_Delclick('" + SVResString::getResString("IDS_Delete_Sel_Group_Confirm") + "','" +
                                            SVResString::getResString("IDS_ConfirmCancel") + "','" + SVResString::getResString("IDS_Affirm")
                                            + "','"  +  m_pbtnConfirm->getEncodeCmd("xclicked()") + "');hiddenbar();";
                    }
                    else if(pNode->getType() == SiteView_ECC_Device)
                    {
                        szOpt = "Delete Device";
                        WebSession::js_af_up = "_Delclick('" + SVResString::getResString("IDS_Delete_Sel_Device_Confirm") + "','" +
                                                SVResString::getResString("IDS_ConfirmCancel") + "','" + SVResString::getResString("IDS_Affirm")
                                                + "','"  +  m_pbtnConfirm->getEncodeCmd("xclicked()") + "');hiddenbar();";
                    }
                }
                else
                {
                    PrintDebugString("confirm button create failed");
                }
            }
            else if(m_szCurrentOpt != "0" && !m_szCurrentOpt.empty())
            {
                if(m_pbtnConfirm && !m_pbtnConfirm->getEncodeCmd("xclicked()").empty())
                {
                    szOpt = "Delete monitor";
                    WebSession::js_af_up = "_Delclick('" + SVResString::getResString("IDS_Delete_Monitor_Confirm") + "','" +
                                            SVResString::getResString("IDS_ConfirmCancel") + "','" + SVResString::getResString("IDS_Affirm")
                                            + "','"  +  m_pbtnConfirm->getEncodeCmd("xclicked()") + "');hiddenbar();";
                }
                else
                {
                    PrintDebugString("confirm button create failed");
                }
            }
            break;
        case SV_ENABLE:                                 // ����
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                switch(pNode->getType())
                {
                case SiteView_ECC_Group:
                    if(isDisable(m_szCurrentOpt, SiteView_ECC_Group))
                    {// ��������
                        szOpt = "Enable Group";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=0&operatetype=1&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// ��ʾ�����ٴ�������Ϣ
                        szOpt = SVResString::getResString("IDS_Group_Can_not_Enable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Enable") + 
                        "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
                    }
                    break;
                case SiteView_ECC_Device:
                    if(isDisable(m_szCurrentOpt, SiteView_ECC_Device))
                    {// �豸������
                        szOpt = "Enable Device";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=1&operatetype=1&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// ��ʾ�����ٴ�������Ϣ
                        szOpt = SVResString::getResString("IDS_Device_Can_not_Enable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Enable") + 
                        "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
                    }
                    break;
                }
            }
            break;
        case SV_DISABLE:                                // ����
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                switch(pNode->getType())
                {
                case SiteView_ECC_Group:
                    if(!isDisable(m_szCurrentOpt, SiteView_ECC_Group))
                    {// ��������
                        szOpt = "Disable Group";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=0&operatetype=0&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// ���ѽ�ֹ
                        szOpt = SVResString::getResString("IDS_Group_Can_not_Disable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Disable") + 
                            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";
                    }
                    break;
                case SiteView_ECC_Device:
                    if(!isDisable(m_szCurrentOpt, SiteView_ECC_Device))
                    {// �豸������
                        szOpt = "Disable Device";
                        WebSession::js_af_up = "showDisableUrl('disable.exe?disabletype=1&operatetype=0&disableid=" + m_szCurrentOpt 
                            + "', '" + m_szGlobalEvent + "');";
                    }
                    else
                    {// �豸�ѽ�ֹ
                        szOpt = SVResString::getResString("IDS_Device_Can_not_Disable");
                        WebSession::js_af_up = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Disable") + 
                            "\",\"" + SVResString::getResString("IDS_Affirm") + "\");hiddenbar();";
                    }
                    break;
                }
            }
            break;
        case SV_REFRESH:                                // ˢ��
            szOpt = "Refresh Device";
            if(m_pTreeView)
                pNode = m_pTreeView->getECCObject(m_szCurrentOpt);
            if(pNode)
            {
                if(pNode->getType() == SiteView_ECC_Device)
                {
                    CEccTreeDevice* pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                    RefreshDevice(pDevice);
                }
            }
            break;
        case SV_COPY:                                   // ����
            szOpt = "Copy Device";
            m_szCurrentCopy = m_szCurrentOpt;
            WebSession::js_af_up = "hiddenbar();";
            break;
        case SV_PAST:                                   // ճ��
            szOpt = "Paste Device";
            if(!isCanBePasteDevice(m_szCurrentCopy))
            {
                WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
            }
            else if(!m_szCurrentCopy.empty())
            {
                string szNewDevID = PasteDevice(m_szCurrentOpt, m_szCurrentCopy);
                if(!szNewDevID.empty())
                {
                    m_szCurrentOpt = szNewDevID;
                    CEccMainView::m_pRightView->showNewDevice(szNewDevID);
                }
            }
            break;
        case SV_TEST:                                   // ����
            szOpt = "Test Device";
            TestDevice(m_szCurrentOpt);
            break;
        }
    }

    if(WebSession::js_af_up.empty())
        WebSession::js_af_up = "hiddenbar();";

    szOpt = m_szCurrentOpt + "--->" + szOpt;

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccMenuClick", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.EccMenuClick", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��� JavaScript����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::AddJsParam(string name, string value)
{  
    int nRow = numRows();
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
    new WText(strTmp, elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������ض���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::createHideObject()
{
    // ���ý��㰴ť
    WPushButton *pbtnHide = new WPushButton("", (WContainerWidget *)parent());
    if(pbtnHide)
    {
        // ��click�¼�
        WObject::connect(pbtnHide, SIGNAL(clicked()), this, SLOT(EccObjectClick()));
        pbtnHide->hide();
        AddJsParam("setNodeFocusButton", pbtnHide->getEncodeCmd("xclicked()"));
    }

    // ȷ�ϰ�ť
    m_pbtnConfirm = new WPushButton("", (WContainerWidget *)parent());
    {
        // ��click�¼�
        WObject::connect(m_pbtnConfirm, SIGNAL(clicked()), "showbar();", this, SLOT(ConfirmDelete()),
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        m_pbtnConfirm->hide();
    }

    // ˢ�����ݰ�ť
    m_pbtnRefresh = new WPushButton("", (WContainerWidget *)parent());
    if(m_pbtnRefresh)
    {
        // ��click�¼�
        WObject::connect(m_pbtnRefresh, SIGNAL(clicked()),"showbar();", this, SLOT(RefreshState()),
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        m_pbtnRefresh->hide();
        m_szGlobalEvent = m_pbtnRefresh->getEncodeCmd("xclicked()");
    }

    // �˵�������ť
    WPushButton *pbtnRunMenu = new WPushButton("", (WContainerWidget *)parent());
    if(pbtnRunMenu)
    {
        WObject::connect(pbtnRunMenu, SIGNAL(clicked()), this, SLOT(EccMenuClick()));
        pbtnRunMenu->hide();
        AddJsParam("runMenuButton", pbtnRunMenu->getEncodeCmd("xclicked()"));
    }

    // ��ǰ��������
    m_pCurrentID = new WLineEdit("", (WContainerWidget *)parent());
    if(m_pCurrentID)
    {
        m_pCurrentID->hide();
        AddJsParam("curId", m_pCurrentID->formName());
    }

    // ��ǰ����
    m_pCurOperate = new WLineEdit("", (WContainerWidget *)parent());
    if(m_pCurOperate)
    {
        m_pCurOperate->hide();
        AddJsParam("curOprCode", m_pCurOperate->formName());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȷ��ɾ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::ConfirmDelete()
{
    unsigned long ulStart = GetTickCount();
    if(m_pTreeView)
    {
        // �õ�ѡ��Ľڵ�
        const CEccTreeNode *pNode = m_pTreeView->getECCObject(m_szCurrentConfirm);
        if(pNode)
        {
            // ������������豸���������Ͳ�ͬ���ò�ͬ��ɾ������
            if(pNode->getType() == SiteView_ECC_Group)
                m_pTreeView->DeleteGroupByID(m_szCurrentConfirm);
            else if(pNode->getType() == SiteView_ECC_Device)
                m_pTreeView->DeleteDeviceByID(m_szCurrentConfirm);
        }
        else if(m_szCurrentOpt != "0" && !m_szCurrentOpt.empty())
        {
            // �����Ǽ����
            DeleteSVMonitor(m_szCurrentOpt, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            DeleteTable(m_szCurrentOpt, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

            // �õ����豸
            const CEccTreeNode *pNode = CEccTreeView::getECCObject(FindParentID(m_szCurrentOpt));
            if(pNode)
            {
                CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
                map<int, CECCMonitor, less<int> >::iterator monitoritem;
                // ɾ��������б��е�����
                for(monitoritem = pDevice->m_Monitors.begin(); monitoritem != pDevice->m_Monitors.end(); monitoritem ++)
                {
                    if(monitoritem->second.getECCIndex() == m_szCurrentOpt)
                    {
                        pDevice->m_Monitors.erase(monitoritem);
                        break;
                    }
                }
            }
        }
        
        if(m_pTreeView->isCurrentPathEdit(m_szCurrentConfirm))
        {// ��ǰ�������ݵ�·�����ж���ɾ��
            // �õ����ڵ�
            const CEccTreeNode *pCurNode = m_pTreeView->getECCObject(FindParentID(m_szCurrentConfirm));
            if(pCurNode && pCurNode->m_pTreeText && m_pRightView)
            {
                m_pTreeView->m_pCurSel = pCurNode->m_pTreeText;
                m_pTreeView->m_szCurSelIndex = pCurNode->getECCIndex();
                pCurNode->m_pTreeText->setStyleClass("treelinkactive");
                // ��������
                m_pRightView->changeActive(pCurNode);
            }
        }
        else if(m_pTreeView->isCurrentChildEdit(m_szCurrentConfirm))
        {// ��ǰ�������ݵ������ݱ�ɾ��
            if(m_pTreeView->m_szCurSelIndex == m_szCurrentConfirm)
                m_pTreeView->m_szCurSelIndex = FindParentID(m_szCurrentConfirm);
            const CEccTreeNode *pCurNode = m_pTreeView->getECCObject(m_pTreeView->m_szCurSelIndex);
            if(pCurNode && pCurNode->m_pTreeText && m_pRightView)
            {
                m_pTreeView->m_pCurSel = pCurNode->m_pTreeText;
                m_pTreeView->m_szCurSelIndex = pCurNode->getECCIndex();
                pCurNode->m_pTreeText->setStyleClass("treelinkactive");
                m_pRightView->changeActive(pCurNode);
            }
        }
    }

    // ���ȷ�����ݵ��ڴ��������������������������������
    if(m_szCurrentConfirm == m_szCurrentCopy)
        m_szCurrentCopy = "";

    int nPos = static_cast<int>(m_szCurrentCopy.find(m_szCurrentConfirm));
    if(nPos > 0)
        m_szCurrentCopy = "";

    m_szCurrentConfirm = "";

    WebSession::js_af_up = "hiddenbar();";

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.ConfirmDelete", "Delete Object--->" + m_szCurrentConfirm, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.ConfirmDelete", "Delete Object--->" + m_szCurrentConfirm, 
        0, GetTickCount() - ulStart);

    m_szCurrentConfirm = "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˢ��״̬
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::RefreshState()
{
    if(m_pTreeView && m_pRightView)
    {
        m_pTreeView->ReCreateTreeNode(m_szCurrentOpt);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::TestDevice(const string &szIndex)
{
    string szParam(enumDeviceRunParam(szIndex));
    szParam += "&seid=";
    szParam += FindSEID(szIndex);
    if(!szParam.empty())
    {
        szParam = "showtestdevice('testdevice.exe?" + szParam +"');hiddenbar();" ;
        WebSession::js_af_up = szParam;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˢ���豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::RefreshDevice(const CEccTreeDevice *pDevice)
{
    if(!pDevice->m_Monitors.empty())
    {// ���������������
        // ����ˢ�»�д������
        string szQueueName(makeQueueName());
        // ����ˢ�»�д����
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szAddr);
        // ����ˢ�¶���
        string szRefreshQueue(getRefreshQueueName(m_szCurrentOpt));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szAddr);

        string szQuery ("");
        map<int, CECCMonitor, less<int> >::const_iterator itmonitor;

        for(itmonitor = pDevice->m_Monitors.begin(); itmonitor != pDevice->m_Monitors.end(); itmonitor ++)
        {// ö��ÿ�������
            if(!isDisable(itmonitor->second.getECCIndex(), SiteView_ECC_Monitor))
            {// �����û�б���ֹ
                szQuery += itmonitor->second.getECCIndex();
                szQuery += "\v";
            }
            else
            {// ���������ֹ
                int nSize = static_cast<int>(itmonitor->second.getECCIndex().length()) + 2;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {  
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, itmonitor->second.getECCIndex().c_str());
                    // ����һ�����������ֹ��Ϣ��ˢ�»�д����
                    if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szAddr))
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
            // ����ˢ����Ϣ��ˢ�¶���
            if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szAddr))
                PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            delete [] pszRefreshMonitor;
        }

        WebSession::js_af_up = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');" + 
            "update('" + CEccMainView::m_szGlobalEvent + "');";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// refresh
// ˢ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccMainView::refresh()
{
    if(!m_bFirstLoad)
    {
        unsigned long ulStart = GetTickCount();

        InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.refresh", SVResString::getResString("IDS_Refresh_GUI"), 
            0, 0);

        if(m_pTreeView)
        {
            // �����û� ID
            m_pTreeView->resetUserID(GetWebUserID());

            // �õ������ַ���
            char szQuery[4097] = {0};
    #ifdef WTGET
            GetEnvironmentVariable("QUERY_STRING", szQuery, sizeof(szQuery));
    #else
            char * tmpQuery = getenv( "QUERY_STRING");
            if(tmpQuery && strlen(tmpQuery) > 0 && strlen(tmpQuery) < sizeof(szQuery))
                strcpy(szQuery, tmpQuery);
    #endif
            if(strlen(szQuery) > 0)
            {
                // ���ȴ��� 0
                char *pPos = strchr(szQuery, '=');
                if(pPos)
                {
                    pPos ++;
                    m_szCurrentOpt = pPos;
                    if(m_szCurrentOpt != m_pTreeView->m_szCurSelIndex)
                    {
                        if(m_pTreeView->m_pCurSel)
                            m_pTreeView->m_pCurSel->setStyleClass("treelink");

                        if(m_szCurrentOpt != "0")
                        {
                            const CEccTreeNode *pNode = CEccTreeView::getECCObject(m_szCurrentOpt);
                            if(pNode && pNode->m_pTreeText)
                            {
                                m_pTreeView->m_pCurSel = pNode->m_pTreeText;
                                m_pTreeView->m_szCurSelIndex = pNode->getECCIndex();
                                pNode->m_pTreeText->setStyleClass("treelinkactive");
                                m_pRightView->refreshCurrentNode(pNode);
                            }
                        }
                        else
                        {
                            m_pTreeView->m_szCurSelIndex = "0";
                            if(m_pTreeView->m_objRootGroup.m_pTreeText)
                            {                    
                                m_pTreeView->m_pCurSel = m_pTreeView->m_objRootGroup.m_pTreeText;
                                m_pTreeView->m_objRootGroup.m_pTreeText->setStyleClass("treelinkactive");
                            }
                            m_pRightView->showSVSEView();
                        }
                    }
                }
            }
        }

        InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccMainView.refresh", SVResString::getResString("IDS_Refresh_GUI"), 
            0, GetTickCount() - ulStart);
    }
    else
    {
        m_bFirstLoad = false;
    }
}

