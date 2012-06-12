/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// adddevice1st.cpp
// ����豸�ĵ�һ����ѡ���豸���ͣ���ʾ��Ϣ�����豸����豸ģ����ʾ���ƣ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "adddevice1st.h"
#include "listtable.h"
#include "resstring.h"
#include "mainview.h"
#include "rightview.h"
#include "basedefine.h"
#include "treeview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice1st::CEccAddDevice1st(WContainerWidget *parent):
CEccBaseTable(parent),
m_szParentId("")
{
    setStyleClass("panel");
    initForm(false);
    connect(&m_MapperOfDT, SIGNAL(mapped(const std::string)), this, SLOT(AddDeviceByType(const std::string)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice1st::~CEccAddDevice1st()
{
    // �Ƴ���Ϣ��
    removeMapping();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �Ƴ���Ϣ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::removeMapping()
{
    list<WText*>::iterator it;
    // �Ƴ�ÿ������
    for(it = m_lsText.begin(); it != m_lsText.end(); it++)
        m_MapperOfDT.removeMappings((*it));
    // �ɽ��������б����
    m_lsText.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::initForm(bool bHasHelp)
{
    // �������ʼ��
    CEccBaseTable::initForm(bHasHelp);

    // ��������
    createTitle();
    // ��������
    createOperate();
    // ö���豸��ģ����豸ģ��
    if(m_pContent)
    {
        CEccBaseTable::setContentCellStyle("height95p");
        enumDeviceGroup();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::createTitle()
{
    // ���ñ�������
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_Device_Title"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö���豸ģ����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::enumDeviceGroup()
{
    PAIRLIST lsDGName;
    PAIRLIST::iterator lsItem;

    map<int, string, less<int> > mapET;
    map<int, string, less<int> > mapETGroup;
    map<int, string, less<int> >::iterator mapETItem;
    map<int, string, less<int> >::iterator mapItem;

	OutputDebugString(" enumDeviceGroup++++++++ \n");

    // �õ����е��豸��
    if(GetAllEntityGroups(lsDGName, svLabel, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr) || 
        GetAllEntityGroups(lsDGName, svName, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
    {// �ɹ�
        list<string> lsDevice;
        list<string>::iterator lstItem;
        string szHidden(""), szIndex("");
		
        for(lsItem = lsDGName.begin(); lsItem != lsDGName.end(); lsItem ++)
        {// ö��ÿһ���豸��
            string szValue = SVResString::getResString((*lsItem).value.c_str());
            string szID = (*lsItem).name;
            // ���豸��
            OBJECT objDG = GetEntityGroup(szID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objDG != INVALID_VALUE)
            {// ���豸��ɹ�
                // �õ� Main MAPNODE
                szHidden = "";
                szIndex = "";
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, svHidden, szHidden); // �Ƿ�����
                    FindNodeValue(node, svShowIndex, szIndex);   // ��ʾ����
                }
				//OutputDebugString(" GetEntityGroup++++++++ \n");

                if(szHidden != "true")
                {// ����������
                    if(!szIndex.empty())
                    {// ��ʾ˳���Ѷ���
                        mapETGroup[atoi(szIndex.c_str())] = szID;
                    }
                    else
                    {
						//OutputDebugString(" else++++++++ \n");

                        int nRow = m_pContent->numRows();
                        // ��������/��ʾ���ܱ�
                        CEccListTable * pTable = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
                        if(pTable)
                        {// ����������/��ʾ���ܱ�ɹ�
                            // ���ô˱����
                            if(!szValue.empty())
                                pTable->setTitle(szValue.c_str());
                            else
                                pTable->setTitle(szID.c_str());
                            
                            // ���� �豸ģ�� �б�
                            lsDevice.clear();
                            WTable *pSubTable = pTable->getListTable();
                            if(GetSubEntityTempletIDByEG(lsDevice, objDG) && pSubTable)
                            {// 
                                for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                                {// ö��ÿһ���豸ģ��
                                    string szDeviceID = (*lstItem).c_str(); 
                                    AddDeviceTemplet(szDeviceID, pSubTable);
                                }
                            }
							//nIndexDeviceGroup++;
							//if(nIndexDeviceGroup<4 )
							//OutputDebugString(" nIndexDeviceGroup++ \n");

							//pTable->showSubTable();

                        }
                    }
                }
                // �ر��豸ģ����
                CloseEntityGroup(objDG);
            }
        }

        string szName("");
        // ������ʾ˳�� �����豸���
		int nIndexDeviceGroup=0;
        for(mapItem = mapETGroup.begin(); mapItem != mapETGroup.end(); mapItem ++)
        {
            OBJECT objDG = GetEntityGroup(mapItem->second, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objDG != INVALID_VALUE)
            {
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    szName = ("");
                    if(!FindNodeValue(node, svLabel, szName))
                        FindNodeValue(node, svName, szName);
                    else
                        szName = SVResString::getResString(szName.c_str());

                    int nRow = m_pContent->numRows();
                    CEccListTable * pTable = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
                    if(pTable)
                    {
                        pTable->setTitle(szName.c_str());
                        lsDevice.clear();

                        WTable *pSubTable = pTable->getListTable();
                        if(GetSubEntityTempletIDByEG(lsDevice, objDG) && pSubTable)
                        {
                            for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                            {
                                string szDeviceID = (*lstItem).c_str();
                                AddDeviceTemplet(szDeviceID, pSubTable);
                            }
                        }
						//ǰ3��չʾ
						nIndexDeviceGroup++;
						if(nIndexDeviceGroup>3 )
								pTable->hideSubTable();
                    }
                }
                CloseEntityGroup(objDG);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˵�� ����豸ģ��
// ����
//      �豸����
//      ����Ӵ��豸ģ��ı�
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::AddDeviceTemplet(string szDTName, WTable *pSubTable)
{
    // �õ� �豸ģ����ڵ�
    OBJECT objDevice = GetEntityTemplet(szDTName, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {

        list<int> lsMTID;
        // �õ��豸��ʹ�õļ����ģ���б�
        if(GetSubMonitorTypeByET(objDevice, lsMTID))
            CEccMainView::m_pTreeView->InsertDevMTList(szDTName, lsMTID);

        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szLabel(""), szName(""), szHidden("");
            if(FindNodeValue(node, svDescription, szLabel))      // ˵��
                szLabel = SVResString::getResString(szLabel.c_str());

            if(!FindNodeValue(node, svLabel, szName))
                FindNodeValue(node, svName, szName);             // ����
            else
                szName = SVResString::getResString(szName.c_str());

            FindNodeValue(node, svHidden, szHidden);             // �Ƿ�����
            if(szHidden != "true")
            {
                // �õ���ǰ��
                int nRow = pSubTable->numRows();
                if(!szName.empty())
                {
                    // ���� �ı���ģ������ƣ�
                    WText *pName = new WText(szName, pSubTable->elementAt(nRow, 0));
                    if(pName)
                    {
                        connect(pName, SIGNAL(clicked()), "showbar();" ,  &m_MapperOfDT, SLOT(map()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);

                        m_MapperOfDT.setMapping(pName, szDTName);

                        // ��ʽ����ɫ��#669 ��
                        sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onmouseover='" \
                            "this.style.textDecoration=\"underline\"' " \
                            "onmouseout='this.style.textDecoration=\"none\"'");
                        pName->setToolTip(szLabel);
                        m_lsText.push_back(pName);
                    }
                    new WText(szLabel, pSubTable->elementAt(nRow, 1));

                    pSubTable->GetRow(nRow)->setStyleClass("padding_top");
                    pSubTable->elementAt(nRow, 0)->setStyleClass("widthbold");
                    pSubTable->elementAt(nRow, 1)->setStyleClass("color_2");
                }
            }
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::createOperate()
{
    if(m_pOperate)
    {
        int nRow = m_pOperate->numRows();
        // ȡ�����
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel_Add"), SVResString::getResString("IDS_Cancel_Add_Device_Tip"), 
            "", m_pOperate->elementAt(nRow, 0));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        nRow = static_cast<WTableCell*>(m_pOperate->parent())->row();
        // �ײ����ж���
        elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȡ�����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::Cancel()
{
    // ��ʾ������
    CEccRightView::showMainForm();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˵�� ���豸��������µ��豸
// ����
//      ѡ����豸����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::AddDeviceByType(const std::string szType)
{
    // ��ʾ����豸�ĵڶ���
    CEccRightView::showAddDevice2nd(m_szParentId, szType);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ˵�� ���ø��ڵ�
// ����
//      ���ڵ������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::setParentID(string szIndex)
{
    m_szParentId = szIndex;
}
