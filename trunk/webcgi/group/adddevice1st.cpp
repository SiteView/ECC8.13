#include "adddevice1st.h"

#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../../kennel/svdb/svapi/svapi.h"

#include "resstring.h"

extern void PrintDebugString(const char * szMsg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDeviceList::SVDeviceList(WContainerWidget * parent,string szIDCUser, string szIDCPwd):
WTable(parent)
{
    setStyleClass("t5");        // ��ʽ��    
    m_pContentTable = NULL;     // ���ݱ�
    m_pSubContent= NULL;        // �����ݱ�
    m_szIDCUser = szIDCUser;    // 
    m_szIDCPwd = szIDCPwd;      //
    initForm();                 // ��ʼ��ҳ��
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initForm
// ˵�� ��ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::initForm()
{
    connect(&m_DeviceMap, SIGNAL(mapped(const std::string)), this, SLOT(addDevice(const std::string)));
    createTitle();
    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        enumDeviceGroup();
    }
    createOperate();   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createTitle
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::createTitle()
{
    // �õ���ǰ��
    int nRow = numRows();
    // ���� basic.js �ļ�
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));

	nRow ++;
    // ����������
    WText *pTitle = new WText(SVResString::getResString("IDS_Add_Device_Title"), (WContainerWidget*)elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("t1title");

	// �����Ƿ��Ƿ��汾�����Ƿ񴴽� �����ˢ�°�ť
    int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{ // ���� ���� ��ť
        new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)elementAt(nRow, 0));
	    m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)elementAt(nRow, 0));
	    if(m_pTranslateBtn)
	    {
		    connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
		    m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
        }
	}

    // �������ݱ�
    nRow ++;
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        // ������
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t5"); 
        elementAt(nRow, 0)->setStyleClass("t7");

        // ���������ݱ�
        nRow = m_pContentTable->numRows();
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Translate
// ˵�� ��ʾ�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::Translate()
{
    // 
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "groupRes";
	WebSession::js_af_up += "')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� addDeviceByID
// ˵�� �����豸ģ�������ö�ٲ�������Ӵ��豸ģ�嵽ָ������
// ����
//      szDeviceID���豸ģ�������
//      pTable�� ��Ų����ı��ָ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::addDeviceByID(string &szDeviceID, SVShowTable *pTable)
{
    // �õ� �豸ģ����ڵ�
    OBJECT objDevice = GetEntityTemplet(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szLabel(""), szName(""), szHidden("");
            if(FindNodeValue(node, "sv_description", szLabel))      // ˵��
                szLabel = SVResString::getResString(szLabel.c_str());

            if(!FindNodeValue(node, "sv_label", szName))
                FindNodeValue(node, "sv_name", szName);             // ����
            else
                szName = SVResString::getResString(szName.c_str());

            FindNodeValue(node, "sv_hidden", szHidden);             // �Ƿ�����
            if(szHidden != "true")
            {
                WTable * pSub = pTable->createSubTable();           // �����ӱ�
                if(pSub)
                {
                    // �õ���ǰ��
                    int nSubRow = pSub->numRows();
                    if(!szName.empty())
                    {
                        // ���� �ı���ģ������ƣ�
                        WText *pName = new WText(szName, (WContainerWidget*)pSub->elementAt(nSubRow, 0));
                        if(pName)
                        {
                            connect(pName, SIGNAL(clicked()), "showbar();" ,  &m_DeviceMap, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                            m_DeviceMap.setMapping(pName, szDeviceID.c_str());
                            // ��ʽ����ɫ��#669 ��
                            sprintf(pName->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                                "this.style.textDecoration=\"underline\"' " \
                                "onmouseout='this.style.textDecoration=\"none\"'");
                            pName->setToolTip(szLabel);
                        }
                        pSub->elementAt(nSubRow, 0)->setStyleClass("cell_40");
                        new WText(szLabel, (WContainerWidget*)pSub->elementAt(nSubRow, 1));
                    }
                }
            }
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumDeviceGroup
// ˵�� ö�������豸��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::enumDeviceGroup()
{
    PAIRLIST lsDGName;
    PAIRLIST::iterator lsItem;

    map<int, string, less<int> > mapET;
    map<int, string, less<int> > mapETGroup;
    map<int, string, less<int> >::iterator mapETItem;
    map<int, string, less<int> >::iterator mapItem;

    // �õ����е��豸��
    if(GetAllEntityGroups(lsDGName, "sv_label", m_szIDCUser, m_szIDCPwd) || 
        GetAllEntityGroups(lsDGName, "sv_name", m_szIDCUser, m_szIDCPwd))
    {// �ɹ�
        list<string> lsDevice;
        list<string>::iterator lstItem;
        string szHidden(""), szIndex("");
        for(lsItem = lsDGName.begin(); lsItem != lsDGName.end(); lsItem ++)
        {// ö��ÿһ���豸��
            string szValue = SVResString::getResString((*lsItem).value.c_str());
            string szID = (*lsItem).name;
            // ���豸��
            OBJECT objDG = GetEntityGroup(szID, m_szIDCUser, m_szIDCPwd);
            if(objDG != INVALID_VALUE)
            {// ���豸��ɹ�
                // �õ� Main MAPNODE
                szHidden = "";
                szIndex = "";
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, "sv_hidden", szHidden); // �Ƿ�����
                    FindNodeValue(node, "sv_index", szIndex);   // ��ʾ����
                }
                if(szHidden != "true")
                {// ����������
                    if(!szIndex.empty())
                    {// ��ʾ˳���Ѷ���
                        mapETGroup[atoi(szIndex.c_str())] = szID;
                    }
                    else
                    {// ��ʾ˳��δ����
                        // �õ� �����ݱ�ǰ����
                        int nRow = m_pSubContent->numRows();
                        // ��������/��ʾ���ܱ�
                        SVShowTable * pTable = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
                        if(pTable)
                        {// ����������/��ʾ���ܱ�ɹ�
                            // ���ô˱����
                            if(!szValue.empty())
                                pTable->setTitle(szValue.c_str());
                            else
                                pTable->setTitle(szID.c_str());
                            
                            // ���� �豸ģ�� �б�
                            lsDevice.clear();
                            if(GetSubEntityTempletIDByEG(lsDevice, objDG))
                            {// 
                                for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                                {// ö��ÿһ���豸ģ��
                                    string szDeviceID = (*lstItem).c_str(); 
                                    addDeviceByID(szDeviceID, pTable);
                                }
                            }
                            // ���ش˱���ӱ�
                            pTable->HideSubTable();
                        }
                    }
                }
                // �ر��豸ģ����
                CloseEntityGroup(objDG);
            }
        }
        string szName("");
        // ������ʾ˳�� �����豸���
        for(mapItem = mapETGroup.begin(); mapItem != mapETGroup.end(); mapItem ++)
        {
            OBJECT objDG = GetEntityGroup(mapItem->second, m_szIDCUser, m_szIDCPwd);
            if(objDG != INVALID_VALUE)
            {
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    szName = ("");
                    if(!FindNodeValue(node, "sv_label", szName))
                        FindNodeValue(node, "sv_name", szName);
                    else
                        szName = SVResString::getResString(szName.c_str());
                    int nRow = m_pSubContent->numRows();
                    SVShowTable * pTable = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
                    if(pTable)
                    {
                        pTable->setTitle(szName.c_str());
                        lsDevice.clear();
                        if(GetSubEntityTempletIDByEG(lsDevice, objDG))
                        {
                            for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                            {
                                string szDeviceID = (*lstItem).c_str();
                                addDeviceByID(szDeviceID, pTable);
                            }
                        }
                        pTable->HideSubTable();
                    }
                }
                CloseEntityGroup(objDG);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� addDevice
// ˵�� ����ѡ���豸��������豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::addDevice(const std::string szIndex)
{
    // ���� ����豸 �¼�
    emit AddNewDevice(szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createOperate
// ˵�� ����������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::createOperate()
{
    // �õ���ǰ����
    int nRow = numRows();
    // �����µİ�ť
    WPushButton * pCancel = new WPushButton(SVResString::getResString("IDS_Cancel_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(pCancel)
    {
        // �� click �¼�
        pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
        WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(cancel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� cancel
// ˵�� ȡ����Ӳ�������ҳ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::cancel()
{
    emit backPreview();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file