/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// addmonitor1st.cpp
// �����豸�����ͣ�չʾ�����͵��豸����ʹ�õļ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "addmonitor1st.h"
#include "listtable.h"
#include "resstring.h"
#include "mainview.h"
#include "rightview.h"
#include "basedefine.h"
#include "debuginfor.h"
#include "treeview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddMonitor1st::CEccAddMonitor1st(WContainerWidget *parent):
CEccBaseTable(parent),
m_szDTName("")
{
    setStyleClass("panel");
    initForm(false);
    connect(&m_MTMapper, SIGNAL(mapped(int)), this, SLOT(AddMonitorByType(int)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddMonitor1st::~CEccAddMonitor1st()
{
    // �Ƴ��¼���
    removeMapping();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �Ƴ����е��¼���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::removeMapping()
{
    list<WText*>::iterator it;

    // ö��ÿ������
    for(it = m_lsText.begin(); it != m_lsText.end(); it++)
        m_MTMapper.removeMappings((*it));

    // �����б����
    m_lsText.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::initForm(bool bHasHelp)
{
    // ��������
    CEccBaseTable::createTitle(bHasHelp);

    // ���ñ����ı�
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_Monitor"));

    // �õ���ǰ����
    int nRow = numRows();
    
    // �������鲢����TD����ʽ��
    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("height95p");
    if(pSub)
    {
        //������ʽ��
        pSub->setStyleClass("panel");
        // �����µĹ�����
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel");
        }

        // ���� ��
        CEccListTable *pSubList = new CEccListTable(pSub->elementAt(0, 0), false, false, false, false);
        if(pSubList)
        {
            // ���ñ���
            pSubList->setTitle(SVResString::getResString("IDS_Add_Monitor_Title"));
            // �õ����ݱ�
            m_pContent = pSubList->getListTable();
        }

        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);
    }
    
    createOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::createOperate()
{
    // �õ���ǰ��
    int nRow = numRows();
    // ����������
    m_pOperate = new WTable(elementAt(nRow, 0));
    if(m_pOperate)
    {
        // ������ʽ��
        m_pOperate->setStyleClass("widthauto");
        // ȡ�����
        int nOptRow = m_pOperate->numRows();
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel_Add"), 
            SVResString::getResString("IDS_Cancel_Add_Monitor_Tip"), 
            "", m_pOperate->elementAt(nOptRow, 0));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
    // �����������ʾ
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȡ�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::Cancel()
{
    CEccRightView::showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ݼ������������µļ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::AddMonitorByType(int nMTID)
{
    // ��ʾ��Ӽ�����ĵڶ�����ҳ��
    CEccRightView::showAddMonitor2nd(nMTID, m_szParentID, m_szNetworkset);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö�ٴ��豸����ʹ�õ����м����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddMonitor1st::EnumMT(const string &szParentID, const string &szDTName, const string &szNetworkSet)
{
    m_szParentID = szParentID;
    m_szNetworkset = szNetworkSet;

    if(szDTName.empty() || m_szDTName == szDTName)
        return ;

    m_szDTName = szDTName;

    // �Ƴ����е���Ϣ��
    removeMapping();

    if(m_pContent)
    {
        m_pContent->clear();

        list<int> lsMTID;
        CEccMainView::m_pTreeView->GetDevMTList(szDTName, lsMTID);
        list<int>::iterator lstItem;
        // ö��ÿ�������ģ��
        for(lstItem = lsMTID.begin(); lstItem != lsMTID.end(); lstItem++)
        {
            int nMTID = (*lstItem);
            // �򿪼����ģ��
            OBJECT objMonitor = GetMonitorTemplet(nMTID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objMonitor != INVALID_VALUE)
            {// �ɹ�
                // ���ڵ�
                MAPNODE node = GetMTMainAttribNode(objMonitor);
                if(node != INVALID_VALUE)
                {
                    // ���� ��ʾ �Ƿ����� ����
                    string szLabel(""), szHidden (""), szDesc ("");
                    if(FindNodeValue(node, svLabel, szLabel))
                        szLabel = SVResString::getResString(szLabel.c_str());
                    
                    if(FindNodeValue(node, svDescription, szDesc))
                        szDesc = SVResString::getResString(szDesc.c_str());

                    FindNodeValue(node, svHidden, szHidden);

                    if(szHidden != "true")
                    {
                        int nRow = m_pContent->numRows();

                        // �������ʾ����
                        WText *pName = new WText(szLabel, m_pContent->elementAt(nRow, 0));
                        if(pName)
                        {
                            // ������ʽ
                            sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onmouseover='" \
                                "this.style.textDecoration=\"underline\"' " \
                                "onmouseout='this.style.textDecoration=\"none\"'");
                            // �� click
                            connect(pName, SIGNAL(clicked()), "showbar();", &m_MTMapper, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                            m_MTMapper.setMapping(pName, nMTID);
                            pName->setToolTip(szLabel);
                            m_lsText.push_back(pName);
                        }
                        new WText(szDesc, m_pContent->elementAt(nRow, 1));

                        m_pContent->GetRow(nRow)->setStyleClass("padding_top");
                        m_pContent->elementAt(nRow, 0)->setStyleClass("widthbold");
                        m_pContent->elementAt(nRow, 1)->setStyleClass("color_2");
                    }
                }
                // �رռ����ģ��
                CloseMonitorTemplet(objMonitor);
            }
        }
    }
}



