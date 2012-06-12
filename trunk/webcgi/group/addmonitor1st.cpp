#include "addmonitor1st.h"

#include "../../opens/libwt/WScrollArea"

extern void PrintDebugString(const char *szMsg);

#include "resstring.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVMonitorList::SVMonitorList(WContainerWidget *parent, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szDeviceType = "";
    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pContentTable = NULL;
    m_pSubContent = NULL;
    m_pTitle = NULL;
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initForm
// ˵�� ��ʼ��ҳ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::initForm()
{
    setStyleClass("t5");
    createTitle();
    if(m_pContentTable)
        createMonitorList();
    createOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� CancelAdd
// ˵�� ȡ�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::CancelAdd()
{
    emit Cancel();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createTitle
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::createTitle()
{
    // �õ���ǰ��
    int nRow = numRows();
    // ������
    m_pTitle = new WText(SVResString::getResString("IDS_Add_Monitor_Title"), (WContainerWidget*)elementAt(nRow, 0));
    // ��������ʾ��ʽ
    elementAt(nRow, 0)->setStyleClass("t1title");
    nRow ++;
    // ���ݱ�
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // ���õ�Ԫ��Padding��Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        // ����������
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t5"); 
    }
    elementAt(nRow, 0)->setStyleClass("t7");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createMonitorList
// ˵�� ����������б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::createMonitorList()
{
    connect(&m_MonitorMap, SIGNAL(mapped(int)), this, SLOT(MonitorMTClicked(int)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumMonitorTempByType
// ˵�� �����豸����ö�ٴ������豸��ʹ�õļ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::enumMonitorTempByType(string &szDeviceType, string &szDeviceID)
{ 
    if(m_szDeviceType == szDeviceType)
    {
        m_szDeviceID = szDeviceID;
        return;
    }
    removeMapping();
    m_pContentTable->clear();
    m_lsName.clear();
    m_szDeviceID = szDeviceID;
    m_szDeviceType = szDeviceType;
    enumMonitor(m_szDeviceType);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� removeMapping
// ˵�� �Ƴ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::removeMapping()
{
    list<WText*>::iterator it;
    for(it = m_lsName.begin(); it != m_lsName.end(); it++ )
        m_MonitorMap.removeMappings((*it));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumMonitor
// ˵�� �����豸����ö�ټ����ģ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::enumMonitor(string &szDeviceType)
{
    if(m_pContentTable)
    {
        // �õ����ݱ�ǰ��
        int nRow = m_pContentTable->numRows();
        // �����ӱ�
        WTable * pSub = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // ���ݱ�ǰ�ж��뷽ʽ
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignCenter);
        // �ӱ���ʽ��
        if(pSub) pSub->setStyleClass("t3");
        // ���豸ģ��
        OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {// �ɹ�
            list<int> lsMTID;
            list<int>::iterator lstItem;
            // �õ��豸��ʹ�õļ����ģ���б�
            if(GetSubMonitorTypeByET(objDevice, lsMTID))
            {
                // ö��ÿ�������ģ��
                for(lstItem = lsMTID.begin(); lstItem != lsMTID.end(); lstItem++)
                {
                    int nMTID = (*lstItem);
                    // �򿪼����ģ��
                    OBJECT objMonitor = GetMonitorTemplet(nMTID, m_szIDCUser, m_szIDCPwd);
                    if(objMonitor != INVALID_VALUE)
                    {// �ɹ�
                        // ���ڵ�
                        MAPNODE node = GetMTMainAttribNode(objMonitor);
                        if(node != INVALID_VALUE)
                        {
                            // ���� ��ʾ �Ƿ����� ����
                            string szLabel(""), szHidden (""), szDesc ("");;
                            //FindNodeValue(node, "sv_name", szName);
                            if(FindNodeValue(node, "sv_label", szLabel))
                                szLabel = SVResString::getResString(szLabel.c_str());
                            
                            if(FindNodeValue(node, "sv_description", szDesc))
                                szDesc = SVResString::getResString(szDesc.c_str());

                            FindNodeValue(node, "sv_hidden", szHidden);
                            if(szHidden != "true")
                            {// ������
                                if(pSub && !szLabel.empty())
                                {
                                    // �ӱ�ǰ��
                                    nRow = pSub->numRows();
                                   
                                    // �������ʾ����
                                    WText *pName = new WText(szLabel, (WContainerWidget*)pSub->elementAt(nRow, 0));
                                    if(pName)
                                    {
                                        // ������ʽ
                                        sprintf(pName->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                                            "this.style.textDecoration=\"underline\"' " \
                                            "onmouseout='this.style.textDecoration=\"none\"'");
                                        // �� click
                                        connect(pName, SIGNAL(clicked()), "showbar();", &m_MonitorMap, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                                        m_MonitorMap.setMapping(pName, nMTID);
                                        pName->setToolTip(szLabel);
                                        m_lsName.push_back(pName);
                                    }
                                    
                                    pSub->elementAt(nRow, 0)->setStyleClass("cell_40");
                                    new WText(szDesc, (WContainerWidget*)pSub->elementAt(nRow, 1));
                                    // �����е���ʾ��ʽ
                                    if((nRow + 1) % 2 == 0)
                                        pSub->GetRow(nRow)->setStyleClass("tr1");
                                    else
                                        pSub->GetRow(nRow)->setStyleClass("tr2");
                                }
                            }
                        }
                        // �رռ����ģ��
                        CloseMonitorTemplet(objMonitor);
                    }
                }
            }
            // �ر��豸ģ��
            CloseEntityTemplet(objDevice);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createOperate
// ˵�� ����������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::createOperate()
{
    int nRow = numRows();
    // �������
    WPushButton * pCancel = new WPushButton(SVResString::getResString("IDS_Cancel_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(pCancel)
    {
        // tooltip
        pCancel->setToolTip(SVResString::getResString("IDS_Cancle_Add_Monitor_Tip"));
        // ��click
        WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(CancelAdd()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� MonitorMTClicked
// ˵�� �����ģ��click��Ӧ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitorList::MonitorMTClicked(int nMTID)
{
    emit AddMonitorByType(nMTID, m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
