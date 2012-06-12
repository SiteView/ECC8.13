#include "groupview.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WSVLinkText"
#include "../../opens/libwt/WLineEdit"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../opens/libwt/WebSession.h"
#include "../../kennel/svdb/libutil/time.h"

#include "resstring.h"
#include "../demotreeview/DemoTreeList.h"

#include "statedesc.h"
#include "monitorview.h"


extern void PrintDebugString (const char * szMsg);

extern void PrintDebugString (const string &szMsg);

char SVGroupview::m_szLogData[1025] = {0};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
// ˵�� ���캯��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVGroupview::SVGroupview(WContainerWidget * parent /* = NULL */, CUser *pUser ,string szIDCUser, string szIDCPwd):
WContainerWidget(parent)
{
    m_szEditIndex = "";

    m_pSVSEView = NULL;	
    m_pMonitorview = NULL;
    m_pAddGroup = NULL;
    m_pDeviceList = NULL;
    m_pDevice = NULL;
    m_pMonitorList = NULL;
    m_pMonitor = NULL;
    m_pAddSVSE = NULL;
    m_pBatchAdd = NULL;
    m_pSortForm = NULL;
    m_pSVUser = NULL;
    m_pTitleCell = NULL;

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;   

    m_pSVUser = pUser;

    if(m_pSVUser)
        m_szUserShowName = m_pSVUser->getUserID();//GetIniFileString(m_pSVUser->getUserID(), "UserName", "", "user.ini");
    else
        m_szUserShowName = "unknown user";

    // ����������Դ
    //loadGeneralText();
    // ��ʼ��ҳ��
    InitForm();
    memset(m_szLogData, 0, sizeof(m_szLogData));

    connect(&m_GroupName, SIGNAL(mapped(const std::string)), this, SLOT(enterGroupByID(const std::string)));      
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddStandard
// ˵�� ��� ���׼��ʾ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddStandard()
{
    int nRow = m_GeneralList.m_pGeneral->numRows();
    m_GeneralList.m_pStandard = new SVGeneral(m_GeneralList.m_pGeneral->elementAt( nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddGroup
// ˵�� ��������б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddGroup()
{
    int nRow = m_GeneralList.m_pGeneral->numRows();
    m_GeneralList.m_pGroup = new SVGroupList((WContainerWidget *) m_GeneralList.m_pGeneral->elementAt( nRow, 0 ), m_pSVUser);
    if(m_GeneralList.m_pGroup)
    {
        // �� ����鴦����
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(AddNewGroup()), this, SLOT(AddNewGroup()));
        // �� ���������༭����Ϣ
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(EditGroupByID(string)), this, SLOT(EditGroupParam(string)));
        // �� ö�ٵ�ǰ���������豸��Ϣ
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(EnumDeviceByID(string)), this, SLOT(EnumDevice(string)));
        // �� ɾ������Ϣ
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(DeleteGroupSucc(string,string)), this, SLOT(DelGroupByIdProc(string,string)));
        // ɾ���豸������
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(DeleteDeviceSucc(string,string)), this, SLOT(DelDeviceByIdProc(string,string)));
        // �� �����б�������Ϣ
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(sortGroupsList(int)), this, SLOT(SortObjects(int)));
        // �� �޸���״̬��Ϣ
        WObject::connect(m_GeneralList.m_pGroup, SIGNAL(ChangeGroupState(string,int)), this, SLOT(ChangeGroupState(string,int)));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddEntity
// ˵�� ����豸�б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddEntity()
{
    int nRow = m_GeneralList.m_pGeneral->numRows();
    // 
    m_GeneralList.m_pDevice = new SVEnumDevice((WContainerWidget *) m_GeneralList.m_pGeneral->elementAt( nRow, 0 ), m_pSVUser);
    if(m_GeneralList.m_pDevice)
    {
        if(m_GeneralList.m_pGroup)
        {
            string szIndex = m_GeneralList.m_pGroup->getGroupIndex();
            // ���õ�ǰ��ID
            m_GeneralList.m_pDevice->EnterGroup(szIndex);
        }
        // ����豸������
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(AddNewDevice()), this, SLOT(AddNewDevice()));
        // �����豸����
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(EnterDeviceByID(string)), this, SLOT(EnterDeviceByID(string)));
        // ���������༭�豸
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(EditDeviceByID(string)), this, SLOT(EditDeviceByIndex(string)));
        // ɾ���豸������
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(DeleteDeviceSucc(string,string)), this, SLOT(DelDeviceByIdProc(string,string)));
        // ��������
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(sortDevicesList(int)), this, SLOT(SortObjects(int)));
        // �����豸ID
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(UpdateDeviceState(string,int)), this, SLOT(ChangeDeviceState(string,int)));
        // �� �����豸�ɹ���Ϣ
        WObject::connect(m_GeneralList.m_pDevice, SIGNAL(CopyDeviceSucc(string,string)), this, SLOT(CopyNewDeviceSucc(string,string)));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddViewControl
// ˵�� �����ͼ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddViewControl()
{
    WTable *pViewControl = new WTable( (WContainerWidget *) m_GeneralList.m_pGeneral->elementAt( 1, 0 ) );
    if ( pViewControl )
    {
        // �����ӱ����ʽ
        pViewControl->setStyleClass("t3");
        m_GeneralList.m_pBackParent = new WPushButton(SVResString::getResString("IDS_Operate_Back_Parent"), (WContainerWidget *)pViewControl->elementAt(0 , 0));
        pViewControl->elementAt(0 , 0)->setContentAlignment(AlignTop | AlignRight);
        if(m_GeneralList.m_pBackParent)
        {
            // ���� Tip
            m_GeneralList.m_pBackParent->setToolTip(SVResString::getResString("IDS_Operate_Back_Parent_Tip"));    
            // onclick ��������
            WObject::connect(m_GeneralList.m_pBackParent, SIGNAL(clicked()), "showbar();", this, SLOT(backParent()), 
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddTitle
// ˵�� ��ӱ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddTitle()
{
    WTable *pTitle = new WTable(m_GeneralList.m_pGeneral->elementAt( 0, 0 ));
    if(pTitle)
    {
        pTitle->setStyleClass("t3");
        m_pTitleCell = pTitle->elementAt( 0, 0);

		// ����
        int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	    if(bTrans == 1)
	    {
	        m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), pTitle->elementAt(0, 1));
	        if(m_pTranslateBtn)
	        {
                // onclick
		        connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
                // tool tip
		        m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
            } 
            new WText("&nbsp;&nbsp;&nbsp;&nbsp;",  ((WContainerWidget *)pTitle->elementAt( 0, 1 )));

		    m_pExChangeBtn = new WPushButton(SVResString::getResString("IDS_Refresh"),((WContainerWidget *)pTitle->elementAt( 0, 1 )));
		    if(m_pExChangeBtn)
		    {
                // onclick
			    connect(m_pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
                // tool tip
			    m_pExChangeBtn->setToolTip(SVResString::getResString("IDS_Refresh_Tip"));
            }
 		    new WText("&nbsp;&nbsp;&nbsp;&nbsp;",  ((WContainerWidget *)pTitle->elementAt( 0, 1 )));
	    }

        // ˢ��ʱ��
        m_GeneralList.m_ptxtTime = new WText("local Time" , ((WContainerWidget *)pTitle->elementAt( 0, 1 )));
        // �õ���ǰʱ��
        svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
        string curTime = ttime.Format();
        if(m_GeneralList.m_ptxtTime)
        {
            // ����TD ��ʽ��
            pTitle->elementAt(0, 1)->setStyleClass("cell_40");
            // ��������
            m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
            // ������ʽ��
            m_GeneralList.m_ptxtTime->setStyleClass("tgrouptitle2");    
        }
        // ���ö��뷽ʽ
        pTitle->elementAt( 0, 1 )->setContentAlignment(AlignRight | AlignTop);
    }
    // ������ʽ��
    m_GeneralList.m_pGeneral->elementAt( 0, 0 )->setStyleClass("t1title");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Translate
// ˵�� ���밴ť�����¼�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::Translate()
{
    // ��ʾ ����ҳ��
	WebSession::js_af_up = "showTranslate('groupRes')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ExChange
// ˵�� ˢ�°�ť�����¼�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ExChange()
{
    // ������ɹ���Ϣ
	emit TranslateSuccessful();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� InitForm
// ˵�� ҳ���ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::InitForm()
{
    // ʹ�� JS �ļ�
    new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

    // �ж��Ƿ�Ϊ������
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {
        // ������ ������SE 1��SE ID�̶���
        enterSVSE("1");    
    }
    else 
    {   
        // ���õ�ǰ��ͼΪ SE��ͼ
        ShowActivateView(active_se_view);
    } 
    // �������ذ�ť
    createHideButton();
    // ������ǰ�༭
    m_pcurEditIndex = new WLineEdit("", this);
    if(m_pcurEditIndex)
    {
        m_pcurEditIndex->hide();
        string strScript ("");
        strScript += "<SCRIPT language='JavaScript' > var curDeviceID='";
        strScript += m_pcurEditIndex->formName();
        strScript += "';</SCRIPT>";
        new WText(strScript, this);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� backParent
// ˵�� ������һ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::backParent()
{
    if(m_GeneralList.m_pGroup)
    {
        // �õ���ǰ��ID
        string szGroupIndex = m_GeneralList.m_pGroup->getGroupIndex(); 

        // ���ڵ��Ƿ���SE
        int nPos = static_cast<int>(szGroupIndex.find("."));
        if(nPos > 0)
        {
            string szParentID = FindParentID(szGroupIndex);
            if(!szParentID.empty())
                m_GeneralList.m_pGroup->BackGroup(szParentID);
        }
        else
        {
            // �Ƿ��ǵ�����
            if(GetIniFileInt("solover","solover",1,"general.ini") == 0)
                ShowActivateView(active_se_view);
            else
                m_GeneralList.m_pBackParent->hide(); // ������һ�� ��ť ����
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showIconView
// ˵�� ͼ����ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::showIconView()
{
    /*
    if (!m_bShowList)
    return;

    m_bShowList = false;
    if (!m_bEntityHide)
    {
    if (m_GeneralList.m_pEntityIcon)
    m_GeneralList.m_pEntityIcon->show();
    if (m_GeneralList.m_pEntityList)
    m_GeneralList.m_pEntityList->hide();
    if (m_GeneralList.m_pEntityOper)
    m_GeneralList.m_pEntityOper->hide();
    }

    if (!m_bGroupHide)
    {
    if (m_GeneralList.m_pGroupIcon)
    m_GeneralList.m_pGroupIcon->show();
    if (m_GeneralList.m_pGroupList)
    m_GeneralList.m_pGroupList->hide();
    if (m_GeneralList.m_pGroupOper)
    m_GeneralList.m_pGroupOper->hide();
    }
    */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showListView
// ˵�� �б���ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::showListView()
{
    /*
    if (m_bShowList)
    return;

    m_bShowList = true;

    if(m_GeneralList.m_psvEntity)
    {
    if(!m_GeneralList.m_psvEntity->isHidden())//if (!m_bEntityHide)    
    {
    if (m_GeneralList.m_pEntityIcon)
    m_GeneralList.m_pEntityIcon->hide();
    if (m_GeneralList.m_pEntityList)
    m_GeneralList.m_pEntityList->show();
    if (m_GeneralList.m_pEntityOper)
    m_GeneralList.m_pEntityOper->show();
    }
    }
    if(m_GeneralList.m_psvGroup)
    {
    if(!m_GeneralList.m_psvGroup->isHidden())//if ( !m_bGroupHide )        
    {
    if (m_GeneralList.m_pGroupIcon)
    m_GeneralList.m_pGroupIcon->hide();
    if (m_GeneralList.m_pGroupList)
    m_GeneralList.m_pGroupList->show();
    if (m_GeneralList.m_pGroupOper)
    m_GeneralList.m_pGroupOper->show();
    }
    }
    */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� ���� ������Դ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVGroupview::loadGeneralText()
//{
    //// ������Դ
    //OBJECT objRes = LoadResource("default", "localhost");  
    //if( objRes != INVALID_VALUE )
    //{// ������Դ�ɹ�
    //    MAPNODE ResNode = GetResourceNode(objRes);
    //    if( ResNode != INVALID_VALUE )
    //    {
    //        FindNodeValue(ResNode, "IDS_Operate_Back_Parent",       m_GeneralText.szBackParent);
    //        FindNodeValue(ResNode, "IDS_Operate_Back_Parent_Tip",   m_GeneralText.szBackParentTip);
    //        FindNodeValue(ResNode, "IDS_Refresh_Time",              m_GeneralText.szRefreshTime);
    //        FindNodeValue(ResNode, "IDS_List_View_Tip",             m_GeneralText.szListviewDesc);
    //        FindNodeValue(ResNode, "IDS_Icon_View_Tip",             m_GeneralText.szIconviewDesc);
    //        FindNodeValue(ResNode, "IDS_Device_Can_not_Disable",    m_szDeviceDisable);
    //        FindNodeValue(ResNode, "IDS_Device_Can_not_Enable",     m_szDeviceEnable);
    //        FindNodeValue(ResNode, "IDS_Group_Can_not_Disable",     m_szGroupDisable);
    //        FindNodeValue(ResNode, "IDS_Group_Can_not_Enable",      m_szGroupEnable);
    //        FindNodeValue(ResNode, "IDS_Translate",                 m_szTranslate);
    //        FindNodeValue(ResNode, "IDS_Translate_Tip",             m_szTranslateTip);
    //        FindNodeValue(ResNode, "IDS_Refresh",                   m_szRefresh);
    //        FindNodeValue(ResNode, "IDS_Refresh_Tip",               m_szRefreshTip);
    //    }
    //    CloseResource(objRes);  // �ر���Դ
    //}
//}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddNewGroup
// ˵�� ������鴦����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewGroup()
{
    ShowActivateView(active_add_group);     // ���ĵ�ǰ��ʾ��ͼ
    if(m_pAddGroup)
    {
        // ���ø�������
        if(m_GeneralList.m_pGroup)
            m_pAddGroup->SetParentIndex(string(m_GeneralList.m_pGroup->getGroupIndex()));
        // ��ʼ�����в���
        m_pAddGroup->ResetParam();
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditGroupParam
// ˵�� �����������޸���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditGroupParam(string szIndex)
{
    ShowActivateView(active_add_group);     // ���ĵ�ǰ��ʾ��ͼ
    m_szEditIndex = szIndex;                // ��ǰ�༭������
    // ��ʾ�༭����ͼ
    if(m_pAddGroup)
        m_pAddGroup->EditGroup(szIndex);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditGroupData
// ˵�� �ɹ��༭ָ���鴦����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditGroupData(string szName, string szIndex)
{
    // �õ����ڵ�����
    string szParentID = FindParentID(szIndex);
    // �༭���ǵ�ǰ��
    if(m_GeneralList.m_pGroup && 
        szParentID.compare(m_GeneralList.m_pGroup->getGroupIndex()) == 0 )
        m_GeneralList.m_pGroup->EditGroup(szName, szIndex);    

    // ����༭��ɹ���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_EDIT;
    response.nNodeType = Tree_GROUP;
    response.strNodeId = szIndex;
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess =true;
    response.strName = szName;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Group") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + 
        "---parent id is " + response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") +
        ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddGroupData
// ˵�� �ɹ�����鴦����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddGroupData(string szName,string szIndex)
{   
    // ���������ɹ���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_ADD;
    response.nNodeType = Tree_GROUP;
    response.strNodeId = szIndex;
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess =true;
    response.strName = szName;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Group") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + 
        response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);

    m_nPreviewView = active_group_view; // ������һ��ͼ
    enterSVSE(szIndex);                 // ���뵱ǰ��

    emit ChangeSelNode(szIndex);        // �������ѡ��ڵ���Ϣ
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showMainView
// ˵�� ��ʾ����ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::showMainView()
{
    ShowActivateView(m_nPreviewView);           // ��ʾ��һ��ͼ
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EnterNewDeviceByID
// ˵�� ��������ӵ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EnterNewDeviceByID(string szDeviceID)
{
    ShowActivateView(active_monitor_view);          // ���ĵ�ǰ��ʾ��ͼ
    if(m_pMonitorview)
        m_pMonitorview->enterDevice(szDeviceID);    // �����豸

    // �������ѡ��ڵ���Ϣ
    emit ChangeSelNode(szDeviceID);
    
    // ˢ��
    string szRefreshMonitor (""), szDevName("");
    // ���豸
    OBJECT objDevice = GetEntity(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// ���豸�ɹ�
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);

        if(mainnode != INVALID_VALUE)
        {
            FindNodeValue(mainnode, "sv_name", szDevName);
        }

        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {// �õ�������б�ɹ�
            string szQuery ("");
            if(lsMonitorID.size() > 0)
            {// ���������������
                
                // ����ˢ�»�д������
                string szQueueName(makeQueueName());
                // ������д����
                CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                // ����ˢ�¶���
                string szRefreshQueue(getRefreshQueueName(szDeviceID));
                CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);

                for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                {// ����ÿһ�������
                    
                    // ��������ӵļ���¼��������־��
                    int nOptType = SV_ADD, nObjType = Tree_MONITOR, nMTID = 0;
                    string szMonitorName(getMonitorNameMTID((*lstItem), nMTID, m_szIDCUser, m_szIDCPwd));

                    string szMsg = SVResString::getResString("IDS_Quick_Add") + SVResString::getResString("IDS_Monitor_Title") +
                        "(Index)" + (*lstItem) + "---" + SVResString::getResString("IDS_Name") + ":" + szMonitorName +
                        "---parent id is: "  + ":" + szDeviceID + "---" + SVResString::getResString("IDS_Name") + ":" + szDevName;
                    AddOperaterLog(nOptType, nObjType, szMsg);
                    
                    if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
                    {// �����û�б���ֹ
                        szQuery += (*lstItem);
                        szQuery += "\v";
                    }
                    else
                    {// ���������ֹ
                        int nSize = static_cast<int>((*lstItem).length()) + 2;
                        char *pszRefreshMonitor = new char[nSize];
                        if(pszRefreshMonitor)
                        {  
                            memset(pszRefreshMonitor, 0, nSize);
                            strcpy( pszRefreshMonitor, (*lstItem).c_str());
                            // ����һ�����������ֹ��Ϣ
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
                    // ������Ϣ����
                    char *pPos = pszRefreshMonitor;
                    while((*pPos) != '\0' )
                    {
                        if((*pPos) == '\v')
                            (*pPos) = '\0';
                        pPos ++;
                    }
                    // ����ˢ����Ϣ
                    if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
                    delete [] pszRefreshMonitor;
                }
                m_nActiveOptType = Tree_DEVICE;
                m_szActiveOptIndex = szDeviceID;
                // JS ����
                szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
            }
        }
    }
    WebSession::js_af_up = szRefreshMonitor + "hiddenbar();update('" + m_szGlobalEvent + "');";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EnterDeviceByID
// ˵�� �����豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EnterDeviceByID(string szDeviceID)
{
    ShowActivateView(active_monitor_view);          // ���ĵ�ǰ��ʾ��ͼ
    if(m_pMonitorview)
    {
        // �����豸
        m_pMonitorview->enterDevice(szDeviceID);
        // �������ѡ��ڵ���Ϣ
        emit ChangeSelNode(szDeviceID);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddNewDevice
// ˵�� ����µ��豸����ʾ�豸ģ���б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewDevice()
{
    ShowActivateView(active_add_device1st);             // ���ĵ�ǰ��ʾ��ͼ������豸��һ����
    if(m_GeneralList.m_pGroup)
    {
        // ���ø�������
        string szIndex = m_GeneralList.m_pGroup->getGroupIndex();
        if(m_pDeviceList)
            m_pDeviceList->setParentIndex(szIndex);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddDevice2nd
// ˵�� �����豸ģ��������ʾ��ͬ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddDevice2nd(string szIndex)
{
    ShowActivateView(active_add_device2nd);
    if(m_pDevice)
    { 
        // ���ø�������
        if(m_pDeviceList)
            m_pDevice->SetParentIndex(m_pDeviceList->getParentID());   
        // �������в���
        m_pDevice->ClearData(szIndex);
        // ����̬����
        m_pDevice->requesDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EnumDevice
// ˵�� ö�ٵ�ǰ���µ��豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EnumDevice(string szIndex)
{
    // �Ƿ��ǵ�����
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {// ��
        if(m_GeneralList.m_pBackParent)
        {
            // �жϸ��ڵ��Ƿ���SE���ݲ�ͬ���ѡ�񷵻���һ����ť����ʾ/����
            string szIndex = m_GeneralList.m_pGroup->getGroupIndex();
            int nPos = static_cast<int>(szIndex.find("."));
            if(nPos > 0)
                m_GeneralList.m_pBackParent->show();
            else
                m_GeneralList.m_pBackParent->hide();
        }
    }

    if(m_pTitleCell)
    {// ���� Cell ���ǿ�ָ��
        // �õ�·��
        list<base_param> lsPath = m_GeneralList.m_pGroup->getGroupPath();
        
        // �Ƴ���
        list<WText*>::iterator itPath;
        for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
            m_GroupName.removeMappings((*itPath));

        // �б����
        m_lsPath.clear();
        // ���cell�����еĿؼ�
        m_pTitleCell->clear();

        // Ϊÿһ���鴴��һ������onclick�¼����ı��ؼ�����������ǰ�飩
        list<base_param>::iterator pathItem;
        base_param svparam;
        while(lsPath.size() > 1)
        {
            svparam = lsPath.back();
            lsPath.pop_back();

            WText *pPath = new WText(svparam.szName, m_pTitleCell);
            if(pPath)
            {
                // ������ʽ��
                pPath->setStyleClass("tgrouptitle") ;
                // onclick
                WObject::connect(pPath, SIGNAL(clicked()), "showbar();", &m_GroupName, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                m_GroupName.setMapping(pPath, svparam.szIndex);
                m_lsPath.push_back(pPath);
            }
            // ��
            WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitleCell);
            if(pTemp)
                pTemp->setStyleClass("tgrouptitle2") ;
        }
        // ��ǰ��
        svparam = lsPath.back();
        lsPath.pop_back();
        WText * pTitle = new WText(svparam.szName, m_pTitleCell);
        if(pTitle)
            pTitle->setStyleClass("tgrouptitle2") ;
    }

    if(m_GeneralList.m_pDevice)
    {
        // ö�ٵ�ǰ���������豸
        m_GeneralList.m_pDevice->EnterGroup(szIndex);
        if(m_GeneralList.m_pStandard)
        {// ���»�����Ϣ��ʾ����
            string szName = m_GeneralList.m_pGroup->getGroupName();
            m_GeneralList.m_pStandard->setTitle(szName);
            string szDesc = m_GeneralList.m_pGroup->getGroupDesc();
            m_GeneralList.m_pStandard->setDescription(szDesc);

            m_GeneralList.m_pStandard->m_nDeviceCount = m_GeneralList.m_pDevice->m_nDeviceCount + 
                m_GeneralList.m_pGroup->m_nDeviceCount;
            m_GeneralList.m_pStandard->m_nMonitorCount = m_GeneralList.m_pDevice->m_nMonitorCount + 
                m_GeneralList.m_pGroup->m_nMonitorCount; 
            m_GeneralList.m_pStandard->m_nMonitorErrCount = m_GeneralList.m_pDevice->m_nMonitorErrCount + 
                m_GeneralList.m_pGroup->m_nMonitorErrCount;
            m_GeneralList.m_pStandard->m_nMonitorWarnCount = m_GeneralList.m_pDevice->m_nMonitorWarnCount + 
                m_GeneralList.m_pGroup->m_nMonitorWarnCount; 
            m_GeneralList.m_pStandard->m_nMonitorDisableCount = m_GeneralList.m_pDevice->m_nMonitorDisableCount + 
                m_GeneralList.m_pGroup->m_nMonitorDisableCount; 
            m_GeneralList.m_pStandard->m_szAdvState = m_GeneralList.m_pGroup->m_szAdvState;
            m_GeneralList.m_pStandard->setState();
        }
    }
    // �������ѡ��ڵ���Ϣ
    emit ChangeSelNode(szIndex);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddNewDeviceSucc
// ˵�� ����豸�ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewDeviceSucc(string szName, string szIndex)
{
    // ��������豸�ɹ���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_ADD;
    response.nNodeType = Tree_DEVICE;
    response.strName = szName;
    response.strNodeId = szIndex;		
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess = true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);  

    // ��ǰһ��ͼ��Ϊ �������ͼ
    m_nPreviewView = active_monitor_view;

    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Device") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " +
        response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� CopyNewDeviceSucc
// ˵�� �����豸�ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::CopyNewDeviceSucc(string szName, string szIndex)
{
    // ��������豸�ɹ���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_ADD;
    response.nNodeType = Tree_DEVICE;
    response.strName = szName;
    response.strNodeId = szIndex;		
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess = true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Copy") + SVResString::getResString("IDS_Past") + 
        SVResString::getResString("IDS_Monitor_Title") + "(Index)" + szIndex +
        "---" + SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is " + response.strParentNodeId + "---" + 
        SVResString::getResString("IDS_Name") + ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� CopyNewMonitorSucc
// ˵�� �����豸�ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::CopyNewMonitorSucc(string szName, string szIndex)
{
    // ��������豸�ɹ���Ϣ
    int nOptType = SV_ADD, nObjType = Tree_MONITOR;

    string szMsg = SVResString::getResString("IDS_Copy") + SVResString::getResString("IDS_Past")
        + SVResString::getResString("IDS_Device") + "(Index)" + szIndex + "---" + 
        SVResString::getResString("IDS_Name") + ":" + szName + "---parent id is: " +
        ":" + FindParentID(szIndex) + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getDeviceNameByID(FindParentID(szIndex), m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(nOptType, nObjType, szMsg);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddMonitor
// ˵�� �����豸��������ʾ��ͬ�ļ����ģ���б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddMonitor(string szDeviceType,string szDeviceID)
{
    m_lsNewMonitorList.clear();             // �¼�����б����
    ShowActivateView(active_add_monitor1st);// ���ĵ�ǰ��ʾ��ͼ
    if(m_pMonitorList)
    {
        //PrintDebugString("enum monitor templet");
        // �����豸����ö�ټ����ģ��
        m_pMonitorList->enumMonitorTempByType(szDeviceType,szDeviceID);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditDeviceSuccByID
// ˵�� �༭�豸�ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditDeviceSuccByID(string szName, string szIndex)
{
    // ���µ�ǰ�豸�б���豸����ʾ����
    if(m_GeneralList.m_pDevice)
        m_GeneralList.m_pDevice->EditDevice(szName, szIndex);

    // ����༭�豸�ɹ���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_EDIT;
    response.nNodeType = Tree_DEVICE;
    response.strNodeId = szIndex;
    response.strParentNodeId = FindParentID(szIndex);
    response.bSucess = true;
    response.strName = szName;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Device") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName + 
        "---parent id is " + response.strParentNodeId + "---" + SVResString::getResString("IDS_Name") + 
        ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddMonitorSucc
// ˵�� ��Ӽ�����ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddMonitorSucc(string szName, string szIndex)
{
    string szParentID = FindParentID(szIndex);
    m_lsNewMonitorList.push_back(szIndex);          // ��ӵ��¼�����б���

    int nOptType = SV_ADD, nObjType = Tree_MONITOR;

    string szMsg = SVResString::getResString("IDS_Add_Title") + SVResString::getResString("IDS_Monitor_Title") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName +
        "---parent id is: "  + ":" + FindParentID(szIndex) + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getDeviceNameByID(FindParentID(szIndex), m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(nOptType, nObjType, szMsg);
    // ���������ͼ����ʾ��Ϣ
    if(m_pMonitorview)
    {
        if(m_pMonitorview->GetCurrentID() == szParentID)
        {
            // ���� ���� �ؼ�
            if(m_pMonitorview->m_pHasNoChild)
                m_pMonitorview->m_pHasNoChild->hide();
            // ����µļ��
            m_pMonitorview->AddMonitorView(szName, szIndex);
            // ˢ��״̬
            m_pMonitorview->refreshState();
        }
    }
    if(m_GeneralList.m_pGroup)
    {
        // �Ƿ��ǵ�ǰ���б���ĳһ�豸��������µļ����
        if(m_GeneralList.m_pGroup->isInGroup(szParentID))
        {
            // ���»�����Ϣ
            if(m_GeneralList.m_pStandard)
            {
                m_GeneralList.m_pStandard->m_nMonitorCount ++;
                m_GeneralList.m_pStandard->setState();
            }
            // ˢ������Ϣ
            m_GeneralList.m_pGroup->refreshGroup(szIndex);
            if(m_GeneralList.m_pDevice)
                m_GeneralList.m_pDevice->refreshDevice(szIndex);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� CancelAddMonitor
// ˵�� ȡ����Ӽ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::CancelAddMonitor()
{
    ShowActivateView(m_nPreviewView);                   // ���ĵ�ǰ��ʾ��ͼ
    string szRefreshMonitor ("");
    if(m_lsNewMonitorList.size() > 0)
    {// �¼�����б�Ϊ��
        // ����ˢ�»�д��������
        string szQueueName(makeQueueName());
        // ����ˢ�»�д����
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
        // ����ˢ�¶���
        list<string>::iterator lstItem(m_lsNewMonitorList.begin());
        string szRefreshQueue(getRefreshQueueName((*lstItem)));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
        
        string szQuery ("");
        
        for(lstItem = m_lsNewMonitorList.begin(); lstItem != m_lsNewMonitorList.end(); lstItem ++)
        {// ö��ÿһ�����������
            if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
            {// ���û�б���ֹ
                szQuery += (*lstItem);
                szQuery += "\v";
            }
            else
            {// ����ֹ
                int nSize = static_cast<int>((*lstItem).length()) + 2;
                char *pszRefreshMonitor = new char[nSize];
                if(pszRefreshMonitor)
                {
                    memset(pszRefreshMonitor, 0, nSize);
                    strcpy( pszRefreshMonitor, (*lstItem).c_str());
                    // ����һ������ֹ��Ϣ��ˢ�»�д����
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
            
            // ����ˢ����Ϣ��ˢ�¶���
            if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            
            delete [] pszRefreshMonitor;
        }                    
        // JS����
        szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
        szRefreshMonitor = szRefreshMonitor + "update('" + m_szGlobalEvent + "');";
    } 
    szRefreshMonitor += "hiddenbar();";
    WebSession::js_af_up = szRefreshMonitor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditMonitorSuccByID
// ˵�� �༭������ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditMonitorSuccByID(string szName, string szIndex)
{
    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_Monitor_Title") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName +
        "---parent id is: "  + ":" + FindParentID(szIndex) + "---" + SVResString::getResString("IDS_Name") + ":" + 
        getDeviceNameByID(FindParentID(szIndex), m_szIDCUser, m_szIDCPwd);

    int nOptType = SV_EDIT, nObjType = Tree_MONITOR;
    AddOperaterLog(nOptType, nObjType, szMsg);

    static const string szRefreshEnd = "Refresh_END";
    ShowActivateView(m_nPreviewView);
    if(m_pMonitorview)
    {
        m_pMonitorview->EditMonitorView(szName, szIndex);
        // ����ˢ�»�д��������
        string szQueueName(makeQueueName());
        // ����ˢ�»�д����
        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
        // ����ˢ�¶���
        string szRefreshQueue(getRefreshQueueName(szIndex));
        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
        
        int nSize = static_cast<int>(szIndex.length()) + 2;
        char *pszRefreshMonitor = new char[nSize];
        if(pszRefreshMonitor)
        {
            memset(pszRefreshMonitor, 0, nSize);
            strcpy( pszRefreshMonitor, szIndex.c_str());
            if(!isMonitorDisable(szIndex, m_szIDCUser, m_szIDCPwd))
            {// �����û�б���ֹ
                if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
            }
            else
            {// ����ֹ
                // ����һ������ֹ��Ϣ
                if(!::PushMessage(szQueueName, "DISABLE", pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into queue failed!");
                // ����ֹͣˢ����Ϣ
                if(!::PushMessage(szQueueName, szRefreshEnd, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                    PrintDebugString("PushMessage into queue failed!");
            }
            
            // ���ĵ�ǰ��������
            m_szActiveOptIndex = m_pMonitorview->GetCurrentID();
            // ���ĵ�ǰ��������
            m_nActiveOptType = Tree_DEVICE;

            // JS
            string szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "');";
            if(!m_szGlobalEvent.empty())
                szRefreshMonitor = szRefreshMonitor + "update('" + m_szGlobalEvent + "');";

            WebSession::js_af_up = szRefreshMonitor;
            delete [] pszRefreshMonitor;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� BackMonitorList
// ˵�� ���ؼ����ģ���б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::BackMonitorList()
{
    ShowActivateView(active_add_monitor1st);   
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddNewMonitorByType
// ˵�� ��ʾ�����������ͼ����Ӽ�����ڶ��������ݼ������ģ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::AddNewMonitorByType(int nMTID, string szDeviceID)
{
    ShowActivateView(active_add_monitor2nd);
    if(m_pMonitor)
    {
        // ��ʾ������������ݼ������ģ�沢���ø��豸������
        m_pMonitor->showMonitorParam(nMTID, szDeviceID);
        // ����̬����
        m_pMonitor->requesDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditDeviceByIndex
// ˵�� �����豸�������༭�豸
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditDeviceByIndex(string szDeviceIndex)
{
    ShowActivateView(active_edit_device);
    m_szEditIndex = szDeviceIndex;                  // ��ǰ�༭
    if(m_pDevice)
    {
        // ���ĵ�ǰ�༭���豸����
        if(m_pcurEditIndex)
            m_pcurEditIndex->setText(m_szEditIndex);

        // �༭�豸
        m_pDevice->EditDeviceByID(szDeviceIndex);
        // ����̬����
        m_pDevice->requesDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditMonitorByIndex
// ˵�� ���ݼ���������༭�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditMonitorByIndex(string szMonitorIndex)
{
    m_lsNewMonitorList.clear();             // �¼�����б����
    ShowActivateView(active_edit_monitor);
    if(m_pMonitor)
    {
        m_pMonitor->EditMonitorByID(szMonitorIndex);    // �༭�����
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� BackGroupDeviceList
// ˵�� �Ӽ������ͼ���ص�����ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::BackGroupDeviceList(string szGroupID)
{
    ShowActivateView(active_group_view);            // ���ĵ�ǰ��ʾ��ͼ
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->BackGroup(szGroupID);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� backSVSEView
// ˵�� ���ص�SE ��ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::backSVSEView()
{
    ShowActivateView(m_nPreviewView);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditSVSEByIndex
// ˵�� ����SE�����༭SE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditSVSEByIndex(string szIndex)
{
    ShowActivateView(active_add_se);
    if(m_pAddSVSE)
    {	       
        m_pAddSVSE->EditSVSE(szIndex);
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditSVSESuccByIndex
// ˵�� �༭SE�ɹ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::EditSVSESuccByIndex(string szName, string szIndex)
{
    if (m_pSVSEView)
        m_pSVSEView->EditSEView(szName, szIndex); 

    // ����༭SE�ɹ���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_EDIT;
    response.nNodeType = Tree_SE;
    response.strNodeId = szIndex;
    response.strName = szName;
    response.strParentNodeId = "-1";
    response.bSucess =true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Edit") + SVResString::getResString("IDS_SE") +
        "(Index)" + szIndex + "---" + SVResString::getResString("IDS_Name") + ":" + szName;

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enterSVSE
// ˵�� ����SE����������Ӧ��SE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::enterSVSE(string szSEID)
{
    ShowActivateView(active_group_view);
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->EnterGroupByID(szSEID);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� DelGroupByIdProc
// ˵�� ɾ���鴦����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::DelGroupByIdProc(string szName, string strId)
{
    // ����ɾ������Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_DELETE;
    response.nNodeType = Tree_GROUP;
    response.strName = "";
    response.strNodeId = strId;
    response.strParentNodeId = FindParentID(strId);
    response.bSucess =true;
    response.strErrorMsg = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Group") + 
        "(Index)" + response.strNodeId + "---" + SVResString::getResString("IDS_Name") + ":" +
        szName + "---parent id is " + response.strParentNodeId + "---" + 
        SVResString::getResString("IDS_Name") + ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);

    // ���»�����Ϣ
    m_GeneralList.m_pStandard->m_nDeviceCount = m_GeneralList.m_pDevice->m_nDeviceCount + 
        m_GeneralList.m_pGroup->m_nDeviceCount;
    m_GeneralList.m_pStandard->m_nMonitorCount = m_GeneralList.m_pDevice->m_nMonitorCount + 
        m_GeneralList.m_pGroup->m_nMonitorCount; 
    m_GeneralList.m_pStandard->m_nMonitorErrCount = m_GeneralList.m_pDevice->m_nMonitorErrCount + 
        m_GeneralList.m_pGroup->m_nMonitorErrCount;
    m_GeneralList.m_pStandard->m_nMonitorWarnCount = m_GeneralList.m_pDevice->m_nMonitorWarnCount + 
        m_GeneralList.m_pGroup->m_nMonitorWarnCount; 
    m_GeneralList.m_pStandard->m_nMonitorDisableCount = m_GeneralList.m_pDevice->m_nMonitorDisableCount + 
        m_GeneralList.m_pGroup->m_nMonitorDisableCount; 
    m_GeneralList.m_pStandard->setState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� DelDeviceByIdProc
// ˵�� ɾ���豸������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::DelDeviceByIdProc(string szName, string strId)
{
    // �����豸ɾ����Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = SV_DELETE;
    response.nNodeType = Tree_DEVICE;
    response.strNodeId = strId;
    response.strParentNodeId = FindParentID(strId);
    response.bSucess =true;
    response.strErrorMsg = "";
    response.strName = "";
    emit MenuItemResponse(response);

    string szMsg = SVResString::getResString("IDS_Delete") + SVResString::getResString("IDS_Device") + 
        "(Index)" + response.strNodeId + "---" + SVResString::getResString("IDS_Name") + ":" +
        szName + "---parent id is " + response.strParentNodeId + "---" + 
        SVResString::getResString("IDS_Name") + ":" + getGroupNameByID(response.strParentNodeId, m_szIDCUser, m_szIDCPwd);

    AddOperaterLog(response.nOperatCode, response.nNodeType, szMsg);

    // ���»�����Ϣ
    m_GeneralList.m_pStandard->m_nDeviceCount = m_GeneralList.m_pDevice->m_nDeviceCount + 
        m_GeneralList.m_pGroup->m_nDeviceCount;
    m_GeneralList.m_pStandard->m_nMonitorCount = m_GeneralList.m_pDevice->m_nMonitorCount + 
        m_GeneralList.m_pGroup->m_nMonitorCount; 
    m_GeneralList.m_pStandard->m_nMonitorErrCount = m_GeneralList.m_pDevice->m_nMonitorErrCount + 
        m_GeneralList.m_pGroup->m_nMonitorErrCount;
    m_GeneralList.m_pStandard->m_nMonitorWarnCount = m_GeneralList.m_pDevice->m_nMonitorWarnCount + 
        m_GeneralList.m_pGroup->m_nMonitorWarnCount; 
    m_GeneralList.m_pStandard->m_nMonitorDisableCount = m_GeneralList.m_pDevice->m_nMonitorDisableCount + 
        m_GeneralList.m_pGroup->m_nMonitorDisableCount; 
    m_GeneralList.m_pStandard->setState();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� MenuItemRequestProc
// ˵�� ���ڵ�˵���Ϣ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::MenuItemRequestProc(MENU_REQUEST request)
{
    string szRefreshMonitor (""), szMsg(""), szName("");
    m_szEditIndex = "";
    m_nActiveOptType = -1;
    m_szActiveOptIndex = "";

    //char chMsg[512] = {0};
    //sprintf(chMsg, "operate code %d, node type : %d", request.nOperatCode, request.nNodeType);
    //PrintDebugString(chMsg);
    // ���ݲ�����
    switch(request.nOperatCode)
    {
    case SV_ADD_GROUP :   // ���
            AddNewGroup();      //��ʾ���������
            //���������ĸ��ڵ�����
            if(m_pAddGroup)
                m_pAddGroup->SetParentIndex(request.strNodeId);
            break;
    case SV_ADD_DEVICE:
        AddNewDevice();     //��ʾ�����豸����
        // ���������豸�ĸ��ڵ�����
        if(m_pDeviceList)
            m_pDeviceList->setParentIndex(request.strNodeId);
        break;
        case SV_ADD_MONITOR:
            //PrintDebugString("Add new monitor");
            //PrintDebugString("Device Type is : " + GetDeviceTypeById(request.strNodeId, m_szIDCUser, m_szIDCPwd));
            AddMonitor(GetDeviceTypeById(request.strNodeId, m_szIDCUser, m_szIDCPwd),  request.strNodeId);
            break;
    case SV_EDIT:   // �༭
        switch(request.nNodeType)
        {
        case Tree_SE:
            EditSVSEByIndex(request.strNodeId);         //��ʾ�༭SE����
            break;
        case Tree_GROUP:
            EditGroupParam(request.strNodeId);          //��ʾ�༭�����
            break;
        case Tree_DEVICE:            
            EditDeviceByIndex(request.strNodeId);       //��ʾ�༭�豸����
            break;
        }
        break;
    case SV_DELETE: // ɾ��
        szMsg = SVResString::getResString("IDS_Delete");
        switch(request.nNodeType)
        {
        case Tree_GROUP:
            szMsg += SVResString::getResString("IDS_Group");
            szName = getGroupNameByID(request.strNodeId, m_szIDCUser, m_szIDCPwd);
            break;
        case Tree_DEVICE:
            szName = getDeviceNameByID(request.strNodeId, m_szIDCUser, m_szIDCPwd);
            szMsg += SVResString::getResString("IDS_Device");
            break;
        }
        
        szMsg += "(Index)" + request.strNodeId + SVResString::getResString("IDS_Name") + ":" + szName +
            "---parent id is: "  + ":" + request.strParentNodeId + "---" + 
            SVResString::getResString("IDS_Name") + ":" + 
            getGroupNameByID(FindParentID(request.strNodeId), m_szIDCUser, m_szIDCPwd);

        AddOperaterLog(request.nOperatCode, request.nNodeType, szMsg);
        deleteObject(request.strNodeId);                // ����ɾ��������
        break;
    case SV_ENABLE: // ����
        m_nActiveOptType = request.nNodeType;
        m_szActiveOptIndex = request.strNodeId;
        switch(request.nNodeType)
        {
        case Tree_GROUP:
            if(isGroupDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) != sv_enable_state)
            {// ���ѽ�ֹ
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=0&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
            }
            else
            {// ��ʾ�����ٴ�������Ϣ
                szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";
            }
            break;
        case Tree_DEVICE:
            if(isDeviceDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) != sv_enable_state)
            {// �豸�ѽ�ֹ
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=1&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
             }
            else
            {// ��ʾ�����ٴ�������Ϣ
                szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Enable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";             
            }
        }
        break;
    case SV_DISABLE: // ��ֹ
        m_nActiveOptType = request.nNodeType;
        m_szActiveOptIndex = request.strNodeId;
        switch(request.nNodeType)
        {
        case Tree_GROUP:
            if(isGroupDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) == sv_enable_state)
            {// ��������
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=0&operatetype=0&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
            }
            else
            {// ���ѽ�ֹ
                   szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Group_Can_not_Disable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";    
            }
            break;
        case Tree_DEVICE:
            if(isDeviceDisable(request.strNodeId, m_szIDCUser, m_szIDCPwd) == sv_enable_state)
            {// �豸������
                szRefreshMonitor = "showDisableUrl('disable.exe?disabletype=1&operatetype=0&disableid=" + request.strNodeId 
                     + "', '" + m_szGlobalEvent + "');";
            }
            else
            {// �豸�ѽ�ֹ
                   szRefreshMonitor = "showAlertMsg(\"" + SVResString::getResString("IDS_Device_Can_not_Disable") + 
                "\",\"" + SVResString::getResString("IDS_Affirm") + "\");";    
            }
            break;
        }
        break;
    case SV_REFRESH:// ˢ��
        m_nActiveOptType = request.nNodeType;
        m_szActiveOptIndex = request.strNodeId;
        if(request.nNodeType == Tree_DEVICE)
        {// ֻ���豸���Ա�ˢ��
            // ���豸
            OBJECT objDevice = GetEntity(request.strNodeId, m_szIDCUser, m_szIDCPwd);
            if(objDevice != INVALID_VALUE)
            {// ���豸�ɹ�
                list<string> lsMonitorID;
                list<string>::iterator lstItem;
                if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
                {// �õ��豸�����еļ����
                    string szQuery ("");
                    if(lsMonitorID.size() > 0)
                    {// ���������������
                        // ����ˢ�»�д������
                        string szQueueName(makeQueueName());
                        // ����ˢ�»�д����
                        CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                        // ����ˢ�¶���
                        string szRefreshQueue(getRefreshQueueName(request.strNodeId));
                        CreateQueue(szRefreshQueue, 1, m_szIDCUser, m_szIDCPwd);
                        for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                        {// ö��ÿ�������
                            if(!isMonitorDisable((*lstItem), m_szIDCUser, m_szIDCPwd))
                            {// �����û�б���ֹ
                                szQuery += (*lstItem);
                                szQuery += "\v";
                            }
                            else
                            {// ���������ֹ
                                int nSize = static_cast<int>((*lstItem).length()) + 2;
                                char *pszRefreshMonitor = new char[nSize];
                                if(pszRefreshMonitor)
                                {  
                                    memset(pszRefreshMonitor, 0, nSize);
                                    strcpy( pszRefreshMonitor, (*lstItem).c_str());
                                    // ����һ�����������ֹ��Ϣ��ˢ�»�д����
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
                            // ����ˢ����Ϣ��ˢ�¶���
                            if(!::PushMessage(szRefreshQueue, szQueueName, pszRefreshMonitor, nSize, m_szIDCUser, m_szIDCPwd))
                                PrintDebugString("PushMessage into " + szRefreshQueue + " queue failed!");
                            delete [] pszRefreshMonitor;
                        }                    
                        szRefreshMonitor = "refreshmonitors('refresh.exe?queuename=" + szQueueName + "')";
                    }
                }
            }
        }
        break;
    case SV_CLICK:  // ����
        switch(request.nNodeType)
        {
        case Tree_SEGROUP:
            ShowActivateView(active_se_view);       // ��ʾ SE ��ͼ
            break;
        case Tree_SE:
            enterSVSE(request.strNodeId);           // ���� SE
            break;
        case Tree_GROUP:
            ShowActivateView(active_group_view);    // ��ʾ �� ��ͼ
            if(m_GeneralList.m_pGroup)
            {
                // ���� ��
                m_GeneralList.m_pGroup->EnterGroupByID(request.strNodeId);
            }
            break;
        case Tree_DEVICE:
            // ���� �豸
            EnterDeviceByID(request.strNodeId);
            break;
        }
        break;
    }
    if(!szRefreshMonitor.empty())
        WebSession::js_af_up = szRefreshMonitor + ";update('" + m_szGlobalEvent + "');hiddenbar();";
    else if(request.nNodeType != Tree_DEVICE )
        WebSession::js_af_up = "hiddenbar()";
    else if(request.nOperatCode != SV_EDIT)
        WebSession::js_af_up = "hiddenbar()";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ShowActivateView
// ˵�� �������������ʾ��ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ShowActivateView(int nActivateView)
{
    // ��ǰ��ͼ�� SE��ͼ/����ͼ/�������ͼ
    if(m_nActiveView == active_se_view ||  m_nActiveView == active_group_view ||
        m_nActiveView == active_monitor_view)
    {
        // ��һ��ͼ ����
        m_nPreviewView = m_nActiveView;
    }
    
    // ���ݵ�ǰ��ͼ���в���
    switch(m_nActiveView)
    {
    case active_edit_device:    // �༭�豸
        if(m_pMonitorview && !m_szEditIndex.empty())
            if(m_pMonitorview->isParentEdit(m_szEditIndex))
                m_pMonitorview->refreshNamePath();
        break;
    case active_add_group:      // �����
        if(m_GeneralList.m_pGroup && !m_szEditIndex.empty() && m_pTitleCell)
        {
            // �Ƿ��Ǹ��鱻�޸�
            if(m_GeneralList.m_pGroup->isParentEdit(m_szEditIndex))
            {
                // ˢ��·��
                m_GeneralList.m_pGroup->refreshNamePath();
                // �õ��µ�·��
                list<base_param> lsPath = m_GeneralList.m_pGroup->getGroupPath();
                
                // �Ƴ���
                list<WText*>::iterator itPath;
                for(itPath = m_lsPath.begin(); itPath != m_lsPath.end(); itPath++)
                    m_GroupName.removeMappings((*itPath));

                // �б����
                m_lsPath.clear();
                // ���cell�����еĿؼ�
                m_pTitleCell->clear();

                // Ϊÿһ���鴴��һ������onclick�¼����ı��ؼ�����������ǰ�飩
                list<base_param>::iterator pathItem;
                base_param svparam;
                while(lsPath.size() > 1)
                {
                    svparam = lsPath.back();
                    lsPath.pop_back();

                    WText *pPath = new WText(svparam.szName, m_pTitleCell);
                    if(pPath)
                    {
                        // ������ʽ��
                        pPath->setStyleClass("tgrouptitle") ;
                        // onclick
                        WObject::connect(pPath, SIGNAL(clicked()), "showbar();", &m_GroupName, SLOT(map()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                        m_GroupName.setMapping(pPath, svparam.szIndex);
                        m_lsPath.push_back(pPath);
                    }
                    // ��
                    WText *pTemp = new WText("&nbsp;:&nbsp;", m_pTitleCell);
                    if(pTemp)
                        pTemp->setStyleClass("tgrouptitle2") ;
                }
                // ��ǰ��
                svparam = lsPath.back();
                lsPath.pop_back();
                WText * pTitle = new WText(svparam.szName, m_pTitleCell);
                if(pTitle)
                    pTitle->setStyleClass("tgrouptitle2") ;

                if(m_GeneralList.m_pStandard)
                {
                    string szName = m_GeneralList.m_pGroup->getGroupName();
                    m_GeneralList.m_pStandard->setTitle(szName);
                    string szDesc = m_GeneralList.m_pGroup->getGroupDesc();
                    m_GeneralList.m_pStandard->setDescription(szDesc);
                }
            }
        }        
        break;
    }
    m_nActiveView = nActivateView;
    m_szEditIndex = "";
    //����������ͼ
    if(m_pSVSEView)
        m_pSVSEView->hide();	
    if(m_GeneralList.m_pGroupview)
        m_GeneralList.m_pGroupview->hide();
    if(m_pMonitorview)
        m_pMonitorview->hide();
    if(m_pAddGroup)
        m_pAddGroup->hide();
    if(m_pDeviceList)
        m_pDeviceList->hide();
    if(m_pDevice)
        m_pDevice->hide();
    if(m_pMonitorList)
        m_pMonitorList->hide();
    if(m_pMonitor)
        m_pMonitor->hide();
    if(m_pAddSVSE)
        m_pAddSVSE->hide();
    if(m_pBatchAdd)
        m_pBatchAdd->hide();
    if(m_pSortForm)
        m_pSortForm->hide();

    // �õ���ǰʱ��
    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();
    //��ʾ������ͼ
    switch(nActivateView)
    {
    case active_se_view:                        // SE ��ͼ
        if(m_pSVSEView == NULL)
        {// SE δ��ʼ��
            // ��ʼ��SE��ͼ
            m_pSVSEView = new SVSEView(this, m_pSVUser);
            if(m_pSVSEView)
            {
                // �� ����SE��Ϣ
                WObject::connect(m_pSVSEView, SIGNAL(showSVSE(string)), this, SLOT(enterSVSE(string)));
                // �� ����SE�����༭SE��Ϣ
                WObject::connect(m_pSVSEView, SIGNAL(EditSEByID(string)), this, SLOT(EditSVSEByIndex(string)));
            }			
        }
        if(m_pSVSEView)
        {            
            m_pSVSEView->show();                    // ��ʾSE ��ͼ
            m_pSVSEView->refreshSElist();           // ˢ�� SE �б�
            m_pSVSEView->setCurrentTime(curTime);   // ������ʾʱ��
        }
        break;
    case active_group_view:                         // ����ͼ
        if(m_GeneralList.m_pGroupview == NULL)
        {// ����ͼ û�г�ʼ��
            // ����ͼ��ʼ��
            m_GeneralList.m_pGroupview = new WTable(this);
            if(m_GeneralList.m_pGroupview)
            {
                // �����������ʽ��
                m_GeneralList.m_pGroupview->setStyleClass("t5");
                int nRow = m_GeneralList.m_pGroupview->numRows();
                // ����������ʾ��
                WTable *pContent = new WTable(m_GeneralList.m_pGroupview->elementAt(nRow, 0));
                if(pContent)
                {
                    WScrollArea *pScrollArea = new WScrollArea(m_GeneralList.m_pGroupview->elementAt(nRow,0));
                    if(pScrollArea)
                    {
                        pScrollArea->setStyleClass("t5");           // ������������ʽ��
                        pScrollArea->setWidget(pContent);           // �˹��������������ݱ�
                    }        
                    pContent->setStyleClass("t5");                  // �������ݱ����ʽ��
                    // ��������� cell(nRow, 0)����ʽ��
                    m_GeneralList.m_pGroupview->elementAt(nRow, 0)->setStyleClass("t10");
                    // �õ����ݱ�ĵ�ǰ����
                    nRow = pContent->numRows();
                    // ���������ݱ�
                    m_GeneralList.m_pGeneral = new WTable(pContent->elementAt(nRow,0));
                    // �������ݱ� cell(nRow, 0)���뷽ʽ�����϶��룩
                    pContent->elementAt(nRow, 0)->setContentAlignment(AlignLeft | AlignTop);
                    if (m_GeneralList.m_pGeneral)
                    {
                        m_GeneralList.m_pGeneral->setStyleClass("t8");// ���������ݱ���ʽ��
                        AddTitle();                 // ����
                        AddViewControl();           // ����
                        AddStandard();              // ������Ϣ
                        AddGroup();                 // ���б�
                        AddEntity();                // �豸�б�
                    }
                }
                nRow = m_GeneralList.m_pGroupview->numRows();
                // ״̬����
                new CSVStateDesc(m_GeneralList.m_pGroupview->elementAt(nRow, 0));
            }
        }
        if(m_GeneralList.m_pGroupview)
        {
            // ��ʾ����
            m_GeneralList.m_pGroupview->show();
            // ���õ�ǰʱ��
            if(m_GeneralList.m_ptxtTime)
                m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        }
        break;
    case active_monitor_view:                       // �������ͼ
        if(m_pMonitorview == NULL)
        {// �������ͼδ��ʼ��
            // �����������ͼ
            m_pMonitorview = new SVMonitorview(this, m_pSVUser);
            if(m_pMonitorview)
            {
                // �� ��Ӽ������Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(AddNewMonitor(string,string)),this, SLOT(AddMonitor(string,string)));
                // �� �༭�������Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(EditMonitorByID(string)), this, SLOT(EditMonitorByIndex(string)));
                // �� ���ظ�����Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(BackDeviceParent(string)), this, SLOT(BackGroupDeviceList(string)));
                // �� ������Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(sortMonitorsList(int)), this, SLOT(SortObjects(int)));
                // �� ������������������Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(enterGroup(string)), this, SLOT(enterGroup(string)));
                // �� �����豸����������豸
                WObject::connect(m_pMonitorview, SIGNAL(enterDependDevice(string)), this, SLOT(EnterDeviceByID(string)));
                // �� �����豸״̬��Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(ChangeDeviceState(string,int)), this, SLOT(ChangeDeviceState(string,int)));
                // �� �����豸״̬��Ϣ
                WObject::connect(m_pMonitorview, SIGNAL(CopyMonitorSucc(string,int)), this, SLOT(CopyNewMonitorSucc(string,int)));
                // ���� ˢ���¼�
                m_pMonitorview->setRefreshEvent(m_szGlobalEvent);
                // ���� ��ҳ��
                m_pMonitorview->setMainview(this);
            }			
        }
        if(m_pMonitorview)
        {
            m_pMonitorview->show();                     // ��ʾ�������ͼ
            m_pMonitorview->setCurrentTime(curTime);    // ���õ�ǰʱ��
        }
        break;
    case active_add_group:                              // �����
        if(m_pAddGroup == NULL)
        {// �������ͼδ��ʼ��
            // �����������ͼ
            m_pAddGroup = new SVAddGroup(this, m_pSVUser);
            if(m_pAddGroup)
            {
                // �� �����ɹ���Ϣ
                WObject::connect(m_pAddGroup, SIGNAL(addGroupName(string,string)), this, SLOT(AddGroupData(string,string)));
                // �� �༭��ɹ���Ϣ
                WObject::connect(m_pAddGroup, SIGNAL(editGroupName(string,string)), this, SLOT(EditGroupData(string,string)));
                // �� ȡ�����������/�༭����Ϣ
                WObject::connect(m_pAddGroup, SIGNAL(backMain()), this, SLOT(showMainView()));
            }			
        }
        if(m_pAddGroup)
        {
            m_pAddGroup->show();                        // ��ʾ �༭��
        }
        break;
    case active_add_se:                                 // ��� SE
        if(m_pAddSVSE == NULL)
        {// ��� SE ��ͼ δ��ʼ��
            // ����SE ��ͼ
            m_pAddSVSE = new SVAddSE(this);
            if(m_pAddSVSE)
            {
                // �� ���� SE ��ͼ��Ϣ
                WObject::connect(m_pAddSVSE, SIGNAL(backSVSEView()), this, SLOT(backSVSEView()));
                // �� �༭ SE �ɹ���Ϣ
                WObject::connect(m_pAddSVSE, SIGNAL(EditSVSESucc(string,string)), this, SLOT(EditSVSESuccByIndex(string,string)));
            }
        }
        if(m_pAddSVSE)
            m_pAddSVSE->show();                         // ��ʾ �༭SE ��ͼ
        break;
    case active_add_device1st:                          // ����豸��һ��
        if(m_pcurEditIndex)
            m_pcurEditIndex->setText("");
        if(m_pDeviceList == NULL)
        {// �豸ģ����ͼ δ��ʼ��
            //���� �豸ģ����ͼ
            m_pDeviceList = new SVDeviceList(this);
            if(m_pDeviceList)
            {
                // �� ȡ�������Ϣ
                WObject::connect(m_pDeviceList, SIGNAL(backPreview()), this, SLOT(showMainView()));
                // �� �����豸ģ���������������Ϣ
                WObject::connect(m_pDeviceList, SIGNAL(AddNewDevice(string)), this, SLOT(AddDevice2nd(string)));
            }
        }
        if(m_pDeviceList)
            m_pDeviceList->show();                      // ��ʾ �豸ģ����ͼ
        break;
    case active_add_device2nd:                          // ����豸�ڶ���
    case active_edit_device:                            // �༭�豸
        if(m_pDevice == NULL)
        {// �豸������ͼδ��ʼ��
            // �����豸������ͼ
            m_pDevice = new SVDevice(this, m_pSVUser);
            if(m_pDevice)
            {
                // �� ������ҳ����Ϣ
                WObject::connect(m_pDevice, SIGNAL(backMain()), this, SLOT(showMainView()));
                // �� ������һҳ����Ϣ
                WObject::connect(m_pDevice, SIGNAL(backPreview()), this, SLOT(AddNewDevice()));
                // �� ����豸�ɹ���Ϣ
                WObject::connect(m_pDevice, SIGNAL(AddDeviceSucc(string,string)), this, SLOT(AddNewDeviceSucc(string,string)));
                // �� �༭�豸�ɹ���Ϣ
                WObject::connect(m_pDevice, SIGNAL(EditDeviceSucc(string,string)), this, SLOT(EditDeviceSuccByID(string,string)));
                // �� �������豸��Ϣ
                WObject::connect(m_pDevice, SIGNAL(EnterNewDevice(string)), this, SLOT(EnterNewDeviceByID(string)));
            }			
        }
        if(m_pDevice)
            m_pDevice->show();                      // ��ʾ �豸������ͼ
        break;
    case active_add_monitor1st:                     // ��Ӽ������һ��
        if(m_pMonitorList == NULL)
        {// �����ģ����ͼδ��ʼ��
            // ���������ģ����ͼ
            m_pMonitorList = new SVMonitorList(this);
            if(m_pMonitorList)
            {
                // �� ȡ����Ӽ������Ϣ
                WObject::connect(m_pMonitorList, SIGNAL(Cancel()), this, SLOT(CancelAddMonitor()));
                // �� ���ݼ����ģ������������Ӽ������Ϣ
                WObject::connect(m_pMonitorList, SIGNAL(AddMonitorByType(int,string)), this, SLOT(AddNewMonitorByType(int,string)));
            }			
        }
        if(m_pMonitorList)
            m_pMonitorList->show();                 // ��ʾ �����ģ����ͼ
        break;
    case active_add_monitor2nd:                     // ��Ӽ�����ڶ���
    case active_edit_monitor:                       // �༭�����
        if(m_pMonitor == NULL)
        {// ��������� ��ͼδ��ʼ��
            //��ʼ����������� ��ͼ
            m_pMonitor = new SVMonitor(this, m_pSVUser);
            if(m_pMonitor)
            {
                // �� ȡ�������¼�
                WObject::connect(m_pMonitor, SIGNAL(CancelAddMonitor()), this , SLOT(CancelAddMonitor()));
                // �� ���ؼ�����б���ͼ�¼�
                WObject::connect(m_pMonitor, SIGNAL(BackPreview()), this, SLOT(BackMonitorList()));
                // �� �ɹ���Ӽ�����¼�
                WObject::connect(m_pMonitor, SIGNAL(AddMonitorSucc(string,string)), this, SLOT(AddMonitorSucc(string,string)));
                // �� �༭������ɹ��¼�
                WObject::connect(m_pMonitor, SIGNAL(EditMonitorSucc(string,string)), this, SLOT(EditMonitorSuccByID(string,string)));
                // �� ������Ӽ�����¼�
                WObject::connect(m_pMonitor, SIGNAL(BatchAddNew()), this, SLOT(BatchAddMonitor()));
            }			
        }
        if(m_pMonitor)
            m_pMonitor->show();                 // ��ʾ ��������� ��ͼ
        break;
    case active_batch_add_monitor:              // �������
        if(m_pBatchAdd == NULL)
        {// �������δ��ʼ��
            // ��ʼ�����������ͼ
            m_pBatchAdd = new SVBatchAdd(this, m_pSVUser);
            if(m_pBatchAdd)   
            {
                // �� ������ҳ����Ϣ
                WObject::connect(m_pBatchAdd, SIGNAL(backPreview()), this, SLOT(CancelAddMonitor()));
                // �� ��Ӽ�����ɹ���Ϣ
                WObject::connect(m_pBatchAdd, SIGNAL(AddMonitorSucc(string,string)), this, SLOT(AddMonitorSucc(string,string)));
            }
        }
        if(m_pBatchAdd)
        {
            m_pBatchAdd->setDynParamList(m_pMonitor->m_lsDyn);                  // ��̬����    
            m_pBatchAdd->setAdvParamList(m_pMonitor->m_lsAdvParam);             // �߼�����
            m_pBatchAdd->setBaseParamList(m_pMonitor->m_lsBaseParam);           // ��������
    
            m_pBatchAdd->setNetworkset(m_pMonitor->m_szNetworkset);             // ������Ƿ������������豸
            m_pBatchAdd->setPoint(m_pMonitor->m_szPoint);                       // ���������
            m_pBatchAdd->setDeviceIndex(m_pMonitor->m_szDeviceIndex);           // �豸����
            m_pBatchAdd->setMonitorType(m_pMonitor->m_nMonitorID);              // ���������
            m_pBatchAdd->setHostName(m_pMonitor->m_szHostName);                 // ��������

            m_pBatchAdd->setErrCondition(m_pMonitor->m_pErrCond);               // ��������
            m_pBatchAdd->setWarnCondition(m_pMonitor->m_pWarnCond);             // ��������
            m_pBatchAdd->setGoodCondition(m_pMonitor->m_pGoodCond);             // ��������

            m_pBatchAdd->addValueList(m_pMonitor->m_szMonitorName);             // ���������
            m_pBatchAdd->show();                                                // ��ʾ ���������ͼ
        }
        break;
    case active_sort_objects:           // ����
        if(m_pSortForm == NULL)
        {// ����δ��ʼ��
            // ��ʼ��������ͼ
            m_pSortForm = new CSVSortList(this, m_pSVUser, m_szIDCUser, m_szIDCPwd);
            if(m_pSortForm)
            {
                // �󶨷�����ҳ����Ϣ
                WObject::connect(m_pSortForm, SIGNAL(backMainView()), this, SLOT(showMainView()));
                // ��ˢ���б���Ϣ
                WObject::connect(m_pSortForm, SIGNAL(RefreshList()), this, SLOT(RefreshCurrentList()));
            }
        }
        if(m_pSortForm)
            m_pSortForm->show();        // ��ʾ������ͼ
        break;
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� RefreshCurrentList
// ˵�� ˢ�µ�ǰ��ʾ��ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::RefreshCurrentList()
{
    ShowActivateView(m_nPreviewView);
    // �õ���ǰʱ��
    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();
    // ���ߵ�ǰ��ʾ��ͼˢ��
    switch(m_nActiveView)
    {
    case active_se_view:
        if(m_pSVSEView)
        {
            m_pSVSEView->refreshSElist();           // ˢ��SE �б�
            m_pSVSEView->setCurrentTime(curTime);   // ����ʱ��
        }
        break;
    case active_group_view:
        if(m_GeneralList.m_pGroup)
        {
            // ���½��뵱ǰ��
            string szGroupID = m_GeneralList.m_pGroup->getGroupIndex();
            m_GeneralList.m_pGroup->EnterGroupByID(szGroupID);
        }  
        // ����ʱ��
        if(m_GeneralList.m_ptxtTime)
            m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        break;
    case active_monitor_view:
        if(m_pMonitorview)
        {
            // ���½��뵱ǰ�豸
            m_pMonitorview->enterDevice(m_pMonitorview->GetCurrentID());
            m_pMonitorview->setCurrentTime(curTime);
        }
        break;
    }

    if(m_nActiveView == active_group_view)
    {
        if(m_GeneralList.m_pGroup)
        {
            // ����������Ϣ
            MENU_RESPONSE response;	
            response.nOperatCode = SV_SORT;
            response.nNodeType = Tree_GROUP;
            response.strNodeId = m_GeneralList.m_pGroup->getGroupIndex();
            response.bSucess = true;
            response.strName = "";
            response.strErrorMsg = "";
            emit MenuItemResponse(response);
        }
    }  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ReloadCurrentView
// ˵�� ���¼��ص�ǰ��ͼ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ReloadCurrentView()
{
    // �õ���ǰʱ��
    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
    string curTime = ttime.Format();

    PrintDebugString("------* reload Current View *------" + curTime);

    // �Ƿ񵥻���
    if(GetIniFileInt("solover","solover",1,"general.ini") == 1)
    {
        // �õ�SE ��1������ʾ����
        string szName  ("");
        OBJECT objSE = GetSVSE("1", m_szIDCUser, m_szIDCPwd);
        if(objSE != INVALID_VALUE)
        {
            szName = GetSVSELabel(objSE);
            CloseSVSE(objSE);
        }
        if(!szName.empty())
        {// �����Ϊ��
            // ���� SE ���Ƹı���Ϣ
            MENU_RESPONSE response;	
            response.nOperatCode = SV_EDIT;
            response.nNodeType = Tree_SE;
            response.strNodeId = "1";
            response.strParentNodeId = FindParentID("1");
            response.bSucess =true;
            response.strName = szName;
            response.strErrorMsg = "";
            emit MenuItemResponse(response);
        }
    }
    else
    {
        string szName = GetIniFileString("segroup","name","","general.ini");
        if(!szName.empty())
        {
            // ����SE group ���Ƹı���Ϣ
            MENU_RESPONSE response;	
            response.nOperatCode = SV_EDIT;
            response.nNodeType = Tree_SE;
            response.strNodeId = "-1";
            response.strParentNodeId = "";
            response.bSucess =true;
            response.strName = szName;
            response.strErrorMsg = "";
            emit MenuItemResponse(response);
        }
    }

    switch(m_nActiveView)
    {
    case active_se_view:
        if(m_pSVSEView)
        {
            m_pSVSEView->refreshSElist();               // ˢ�� SE �б�
            m_pSVSEView->setCurrentTime(curTime);       // ����ʱ��
        }
        break;
    case active_group_view:
        if(m_GeneralList.m_pGroup)
        {
            // ���½��뵱ǰ��
            string szGroupID = m_GeneralList.m_pGroup->getGroupIndex();
            m_GeneralList.m_pGroup->EnterGroupByID(szGroupID);
        }
        // ����ʱ��
        if(m_GeneralList.m_ptxtTime)
            m_GeneralList.m_ptxtTime->setText(SVResString::getResString("IDS_Refresh_Time") + curTime);
        break;
    case active_monitor_view:
        if(m_pMonitorview)
        {
            // ���½����豸
            m_pMonitorview->enterDevice(m_pMonitorview->GetCurrentID());
            // ���õ�ǰʱ��
            m_pMonitorview->setCurrentTime(curTime);
        }
        break;
    }

    if(!m_szActiveOptIndex.empty())
    {// �����ǰ����������Ϊ��
        if(m_nActiveOptType == Tree_DEVICE)
        {// �����������豸
            // �õ��豸�ļ�״̬
            int nState = getDeviceSimpleState(m_szActiveOptIndex, m_szIDCUser, m_szIDCPwd);
            // �����豸��״̬
            ChangeDeviceState(m_szActiveOptIndex, nState);
        }
        else if(m_nActiveOptType == Tree_GROUP)
        {// ������������
            // ���Ƿ񱻽�ֹ/�������״̬
            if(isGroupDisable(m_szActiveOptIndex, m_szIDCUser, m_szIDCPwd) != 0)
                ChangeGroupState(m_szActiveOptIndex, dyn_disable);
            else
                ChangeGroupState(m_szActiveOptIndex, dyn_normal);
        }
    }
    
    // ���� ��ǰ���������Ͳ�������
    m_nActiveOptType = -1;
    m_szActiveOptIndex = "";

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� isCurEditParentDel
// ˵�� �жϱ�ɾ��������ֵ�Ƿ������ǰ�����޸�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVGroupview::isCurEditParentDel(string szIndex, string szCurrentID)
{
    if(szCurrentID.empty())
    {// ��ǰ������Ϊ��
        if(m_szEditIndex == szIndex)                    // �������
            return true;
        // �ж��Ƿ����
        string szParent = FindParentID(m_szEditIndex);
        while(!szParent.empty())
        {
            if(szParent == szIndex)
                return true;
            szParent = FindParentID(szParent);
            if(IsSVSEID(szParent))
                break;
        }
        if(m_szEditIndex == szParent)
            return true;
    }
    else
    {
        if(szCurrentID == szIndex)
            return true;
        string szParent = FindParentID(szCurrentID);
        while(!szParent.empty())
        {
            if(szParent == szIndex)
                return true;
            szParent = FindParentID(szParent);
            if(IsSVSEID(szParent))
                break;
        }
        if(szCurrentID == szParent)
            return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� deleteObject
// ˵�� ����ɾ���������ͼ�Ĵ�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::deleteObject(string szIndex)
{
    int nMonitorCount = 0;
    switch(m_nActiveView)
    {
    case active_se_view:
        if(m_pSVSEView)
        {
            m_pSVSEView->refreshSElist();
        }
        break;
    case active_group_view:                     // ����ͼ
        if(m_GeneralList.m_pGroup)
        {
            if(isCurEditParentDel(szIndex, m_GeneralList.m_pGroup->getGroupIndex()))
            {
                string szParent = FindParentID(szIndex);
                enterGroup(szParent);
            }
            else
            {
                ReloadCurrentView();                    // ���¼��ص�ǰ��
            }
        }
        break;
    case active_monitor_view:                   // �������ͼ
        if(m_pMonitorview)
        {
            if(m_pMonitorview->isParentEdit(szIndex))
            {// ��ǰ�豸�����ڴ�������
                // �õ���ǰID �ĸ�����
                string szParentID = FindParentID(szIndex);
                // ���𷵻ص���������Ϣ
                emit m_pMonitorview->BackDeviceParent(szParentID);
            }
        }
        break;
    case active_add_group:                      // �����
        if(isCurEditParentDel(szIndex) || isCurEditParentDel(szIndex, m_pAddGroup->GetParentIndex()))
        {// ����ǵ�ǰ�鱻ɾ��/��ǰ�鸸�ڵ㱻ɾ��
            m_szEditIndex = "";
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_device1st:                  // ����豸��һ��
        if(isCurEditParentDel(szIndex, m_pDeviceList->getParentID()))
        {// ���ڵ㱻ɾ��
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_device2nd:                  // ����豸�ڶ���
        if(isCurEditParentDel(szIndex, m_pDevice->getParentIndex()))
        {// ���ڵ㱻ɾ��
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_edit_device:                    // �༭�豸
        if(isCurEditParentDel(szIndex))
        {// ���ڵ㱻ɾ��
            m_szEditIndex = "";
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_monitor1st:                 // ��Ӽ������һ��
        if(isCurEditParentDel(szIndex, m_pMonitorList->getParentIndex()))
        {// ��ǰ�豸���ڵ㱻ɾ��
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_add_monitor2nd:                 // ��Ӽ�����ڶ���
        if(isCurEditParentDel(szIndex, m_pMonitor->getParentID()))
        {// ��ǰ�豸���ڵ㱻ɾ��
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    case active_edit_monitor:                   // �༭���
        if(isCurEditParentDel(szIndex, m_pMonitor->getCurrentEditID()))
        {// ��ǰ��������ڵ㱻ɾ��
            ShowActivateView(m_nPreviewView);
            deleteObject(szIndex);
        }
        break;
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� BatchAddMonitor
// ˵�� ���������Ϣ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::BatchAddMonitor()
{
    ShowActivateView(active_batch_add_monitor);
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createHideButton
// ˵�� �������ذ�ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::createHideButton()
{
    WPushButton *pBtnHide = new WPushButton("hide button", this);//(WContainerWidget*)elementAt(nRow,0));
    if(pBtnHide)
    {
        // onclick
        WObject::connect(pBtnHide, SIGNAL(clicked()), "showbar();", this, SLOT(ReloadCurrentView()), 
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        pBtnHide->hide();
        m_szGlobalEvent = pBtnHide->getEncodeCmd("xclicked()"); 
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� SortObjects
// ˵�� ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::SortObjects(int nType)
{  
    string szSortID("");
    // �������Ͳ�ͬ�õ����������
    switch(nType)
    {
    case Tree_MONITOR:
        if(m_pMonitorview)
            szSortID = m_pMonitorview->GetCurrentID();
        break;
    case Tree_GROUP:
    case Tree_DEVICE:
        if(m_GeneralList.m_pGroup)
            szSortID = m_GeneralList.m_pGroup->getGroupIndex();
        break;
    }

    ShowActivateView(active_sort_objects);      // ��ʾ������ͼ
    // ����
    if(!szSortID.empty() && m_pSortForm)
        m_pSortForm->EnumObject(szSortID, nType);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enterGroup
// ˵�� ����������������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::enterGroup(string szGroupID)
{
    ShowActivateView(active_group_view);
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->EnterGroupByID(szGroupID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enterGroupByID
// ˵�� ��������������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::enterGroupByID(const std::string szGroupID)
{
    string szGroupIndex(szGroupID);
    ShowActivateView(active_group_view);
    if(m_GeneralList.m_pGroup)
        m_GeneralList.m_pGroup->EnterGroupByID(szGroupIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ChangeDeviceState
// ˵�� �����豸״̬
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ChangeDeviceState(string szDeviceID, int nState)
{
    // �����豸״̬�ı��¼�
    MENU_RESPONSE response;	
    response.nOperatCode = nState;
    response.nNodeType = Tree_DEVICE;
    response.strNodeId = szDeviceID;
    response.bSucess = true;
    response.strName = "";
    response.strErrorMsg = "";
    emit MenuItemResponse(response);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ChangeGroupState
// ˵�� ������״̬
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGroupview::ChangeGroupState(string szGroupID, int nState)
{
    // ������״̬�ı���Ϣ
    MENU_RESPONSE response;	
    response.nOperatCode = nState;
    response.nNodeType = Tree_GROUP;
    response.strNodeId = szGroupID;
    response.bSucess = true;
    response.strName = "";
    response.strErrorMsg = "";
    emit MenuItemResponse(response);
}

void SVGroupview::AddOperaterLog(int &nOperateType, int &nObjectType, string &szOperateMsg)
{
    string szOperateType(""), szObjectType("");

    //memset(m_szLogData, 0, sizeof(m_szLogData));
    //
    ////DumpLog("treeview.log", m_szLogData, sizeof(m_szLogData));

    svutil::TTime curTime = svutil::TTime::GetCurrentTimeEx();


    switch(nOperateType)
    {
    case SV_ADD:
        szOperateType = SVResString::getResString("IDS_Add_Title");
        break;
    case SV_EDIT:
        szOperateType = SVResString::getResString("IDS_Edit");
        break;
    case SV_DELETE:
        szOperateType = SVResString::getResString("IDS_Delete");
        break;
    }

    switch(nObjectType)
    {
    case Tree_SE:
        szObjectType = SVResString::getResString("IDS_SE");
        break;
    case Tree_GROUP:
        szObjectType = SVResString::getResString("IDS_Group");
        break;
    case Tree_DEVICE:
        szObjectType = SVResString::getResString("IDS_Device");
        break;
    case Tree_MONITOR:
        szObjectType = SVResString::getResString("IDS_Monitor_Title");
        break;
    }

    //PrintDebugString("Operate Type Is : " + szOperateType + " && Object Type is " + szObjectType.c_str()
    //    + " && Operate Message is : " + szOperateMsg + " && user id is : " + m_pSVUser->getUserID());

    InsertTable(SV_USER_OPERATE_LOG_TABLE,  803);

    if(m_pSVUser)
        m_pOperateLog.InsertOperateRecord(SV_USER_OPERATE_LOG_TABLE, m_pSVUser->getUserID(), 
            curTime.Format(), szOperateType, szObjectType, szOperateMsg);
    //int nLen = sizeof(m_szLogData) - 1;

    //LP_RECORD_HEAD pRecordHead = reinterpret_cast<LP_RECORD_HEAD>(m_szLogData);

    //char *pPos = m_szLogData + sizeof(SV_DATABASE_TABLE_RECORD_HEAD);
    //nLen -= sizeof(SV_DATABASE_TABLE_RECORD_HEAD);
    //
    //if((pPos = buildbuf(m_szUserShowName, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + m_szUserShowName);
    //    return ;
    //}

    //if((pPos = buildbuf(curTime.Format(), pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + curTime.Format());
    //    return ;
    //}

    //if((pPos = buildbuf(szOperateType, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + szOperateType);
    //    return ;
    //}

    //if((pPos = buildbuf(szObjectType, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + szObjectType);
    //    return ;
    //}

    //if((pPos = buildbuf(szOperateMsg, pPos, nLen)) == NULL)
    //{
    //    PrintDebugString("build buffer failed ---* " + szOperateMsg);
    //    return ;
    //}

    //pRecordHead->m_nState = 1;
    //pRecordHead->m_tCreatetime = curTime;
    //pRecordHead->m_nDataLen = static_cast<int>(pPos - m_szLogData) - sizeof(SV_DATABASE_TABLE_RECORD_HEAD);

    //strcpy(pPos , "DynString");
    //nLen = static_cast<int>(pPos - m_szLogData) + static_cast<int>(strlen(pPos)) + 1;
    //DumpLog("treeview.log", m_szLogData, nLen);


    //if(!AppendRecord(SV_USER_OPERATE_LOG_TABLE, m_szLogData, nLen))
    //{
    //    string szMsg = "Append record into table(";
    //    szMsg += SV_USER_OPERATE_LOG_TABLE;
    //    szMsg += ") failed";
    //    PrintDebugString(szMsg);
    //}

    //memset(m_szLogData, 0, sizeof(m_szLogData));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file

//���ܵ���������
//1���������ܷ���SVSEList���棬 ���������SVSE
//2��������ܷ���SVSEList���棬 �����SVSE�� �ڵ��TreeGroup�ڵ�ʱ�����Se�˵��� ���к�SVSE��ص���ɾ�����á�
//3�����ؽ��淽����ܻ������⡣������
//4�����Է�����