
#ifndef _SV_GROUP_VIEW_H_
#define _SV_GROUP_VIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WContainerWidget"
#include "../../opens/libwt/WSignalMapper"

#include <string>
#include <list>
#include <map>

using namespace std;

class WTable;
class WImage;
class WText;
class WLineEdit;
class WTextArea;
class WComboBox;
class WLineEdit;
class WPushButton;
class OperateLog;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "general.h"
#include "grouplist.h"
#include "devicelist.h"
#include "addgroup.h"
#include "adddevice1st.h"
#include "adddevice2nd.h"
#include "addmonitor1st.h"
#include "addmonitor2nd.h"
#include "batchadd.h"
#include "sortlist.h"
#include "svseview.h"
#include "addsvse.h"

#include "basefunc.h"

#include "../demotreeview/define.h"
#include "../userright/user.h"
#include "../base/OperateLog.h"

class SVMonitorview;

enum Active_View
{
    active_se_view,                 // SE ��ͼ
    active_group_view,              // �� ��ͼ
    active_monitor_view,            // �������ͼ
    active_add_group,               // �����
    active_add_se,                  // ��� SE
    active_add_device1st,           // ����豸 ��һ�� ��ѡ���豸���ͣ�
    active_add_device2nd,           // ����豸 �ڶ���
    active_add_monitor1st,          // ��Ӽ���� ��һ�� �������豸������ʾ�Ŀ���Ӽ������ͬ��
    active_add_monitor2nd,          // ��Ӽ���� �ڶ���
    active_edit_group,              // �༭��
    active_edit_device,             // �༭�豸
    active_edit_monitor,            // �༭�����
    active_batch_add_monitor,       // ������Ӽ����
    active_sort_objects             // ����
};



class SVGroupview : public WContainerWidget 
{
    //MOC: W_OBJECT SVGroupview:WContainerWidget
    W_OBJECT;
public:
    // ���캯��
    // �� �û�Ȩ�޹���
    // �������ݿ��û� �û�����
    SVGroupview(WContainerWidget * parent = NULL, CUser *pUser = NULL, 
        string szIDCUser = "default", string szIDCPwd = "localhost");

    void SetUserPwd(string &szUser, string &szPwd);
    void deleteObject(string szIndex);

public signals:
    //MOC: EVENT SIGNAL SVGroupview::MenuItemResponse(MENU_RESPONSE)
    void MenuItemResponse(MENU_RESPONSE response);                          // ��ͬ��
    //MOC: EVENT SIGNAL SVGroupview::ChangeSelNode(string)
    void ChangeSelNode(string szIndex);                                     // �޸�ѡ��Ľڵ�
    //MOC: EVENT SIGNAL SVGroupview::TranslateSuccessful()
    void TranslateSuccessful();                                             // ����ɹ�
public slots:
    //MOC: SLOT SVGroupview::MenuItemRequestProc(MENU_REQUEST)
    void MenuItemRequestProc(MENU_REQUEST request);                         // ���˵�������
    //MOC: SLOT SVGroupview::backParent()
    void backParent();                                                      // ������һ��
    //MOC: SLOT SVGroupview::AddNewGroup()
    void AddNewGroup();                                                     // ����µ���
    //MOC: SLOT SVGroupview::EditGroupParam(string)
    void EditGroupParam(string szIndex);                                    // �༭��
    //MOC: SLOT SVGroupview::showIconView()
    void showIconView();                                                    // ͼ����ͼ
    //MOC: SLOT SVGroupview::showListView()
    void showListView();                                                    // �б���ͼ
    //MOC: SLOT SVGroupview::AddGroupData(string,string)
    void AddGroupData(string szName,string szIndex);                        // �ɹ�������鴦����
    //MOC: SLOT SVGroupview::EditGroupData(string , string)
    void EditGroupData(string szName, string szIndex);                      // �༭��ɹ�������
    //MOC: SLOT SVGroupview::ChangeGroupState(string,int)
    void ChangeGroupState(string szGroupID, int nState);                    // ������״̬
    //MOC: SLOT SVGroupview::showMainView()
    void showMainView();                                                    // ��ʾ����ͼ
    //MOC: SLOT SVGroupview::AddNewDevice()
    void AddNewDevice();                                                    // ����豸
    //MOC: SLOT SVGroupview::AddDevice2nd(string)
    void AddDevice2nd(string szIndex);                                      // ����豸�ڶ���
    //MOC: SLOT SVGroupview::EnumDevice(string)
    void EnumDevice(string szIndex);                                        // ö���豸
    //MOC: SLOT SVGroupview::EditDeviceByIndex(string)
    void EditDeviceByIndex(string szDeviceIndex);                           // �޸��豸
    //MOC: SLOT SVGroupview::AddNewDeviceSucc(string,string)
    void AddNewDeviceSucc(string szName, string szIndex);                   // ����豸�ɹ�
    //MOC: SLOT SVGroupview::EditDeviceSuccByID(string,string)
    void EditDeviceSuccByID(string szName, string szIndex);                 // �޸��豸�ɹ�
    //MOC: SLOT SVGroupview::ChangeDeviceState(string,int)
    void ChangeDeviceState(string szDeviceID, int nState);                  // �����豸״̬
    //MOC: SLOT SVGroupview::EnterDeviceByID(string)
    void EnterDeviceByID(string szDeviceID);                                // �����飨��ʾ�������ͼ��
    //MOC: SLOT SVGroupview::EnterNewDeviceByID(string)
    void EnterNewDeviceByID(string szDeviceID);                             // ��������ӵ��豸
    //MOC: SLOT SVGroupview::AddMonitor(string,string)
    void AddMonitor(string szDeviceType,string szIndex);                    // ��Ӽ����
    //MOC: SLOT SVGroupview::CancelAddMonitor()
    void CancelAddMonitor();                                                // ȡ����Ӽ����
    //MOC: SLOT SVGroupview::AddNewMonitorByType(int,string)
    void AddNewMonitorByType(int nMTID,string szDeviceID);                  // ���ݼ������ MTID���豸ID����µļ����
    //MOC: SLOT SVGroupview::AddMonitorSucc(string,string)
    void AddMonitorSucc(string szName,string szIndex);                      // ��Ӽ�����ɹ�
    //MOC: SLOT SVGroupview::EditMonitorSuccByID(string,string)
    void EditMonitorSuccByID(string szName,string szIndex);                 // �༭������ɹ�
    //MOC: SLOT SVGroupview::EditMonitorByIndex(string)
    void EditMonitorByIndex(string szMonitorIndex);                         // �޸ļ����
    //MOC: SLOT SVGroupview::BackMonitorList()
    void BackMonitorList();                                                 // ���ؼ�����б�
    //MOC: SLOT SVGroupview::BackGroupDeviceList(string)
    void BackGroupDeviceList(string szGroupID);                             // ���ص�����ͼ
    //MOC: SLOT SVGroupview::EditSVSESuccByIndex(string,string)
    void EditSVSESuccByIndex(string szName, string szSEID);                 // �༭SE�ɹ�
    //MOC: SLOT SVGroupview::EditSVSEByIndex(string)
    void EditSVSEByIndex(string szSEID);                                    // �༭SE
    //MOC: SLOT SVGroupview::enterSVSE(string)
    void enterSVSE(string szSEID);                                          // ����SE
    //MOC: SLOT SVGroupview::enterGroup(string)
    void enterGroup(string szGroupID);                                      // ������
    //MOC: SLOT SVGroupview::backSVSEView()
    void backSVSEView();	                                                // ��ʾSE ��ͼ
    //MOC: SLOT SVGroupview::DelDeviceByIdProc(string,string)
    void DelDeviceByIdProc(string szName, string strId);                    // ɾ���豸֪ͨ������
    //MOC: SLOT SVGroupview::DelGroupByIdProc(string,string)
    void DelGroupByIdProc(string szName, string strId);                     // ɾ����֪ͨ������
    //MOC: SLOT SVGroupview::BatchAddMonitor()
    void BatchAddMonitor();                                                 // �������
    //MOC: SLOT SVGroupview::ReloadCurrentView()
    void ReloadCurrentView();                                               // ���¼��ص�ǰ��ͼ
    //MOC: SLOT SVGroupview::SortObjects(int)
    void SortObjects(int nType);                                            // ����
    //MOC: SLOT SVGroupview::RefreshCurrentList()
    void RefreshCurrentList();                                              // ��������¼��ص�ǰ��ͼ
    //MOC: SLOT SVGroupview::enterGroupByID(const std::string)
    void enterGroupByID(const std::string szGroupID);                       // ����������ֱ�ӽ���ĳһ��
	//MOC: SLOT SVGroupview::Translate()
	void Translate();                                                       // ����
	//MOC: SLOT SVGroupview::ExChange()
	void ExChange();                                                        // ���¼���
    //MOC: SLOT SVGroupview::CopyNewDeviceSucc(string,string)
    void CopyNewDeviceSucc(string szName, string szIndex);                  // �����豸�ɹ�
    //MOC: SLOT SVGroupview::CopyNewMonitorSucc(string,string)
    void CopyNewMonitorSucc(string szName, string szIndex);                 // ����������ɹ�
private:
    //////////////////////////////////////////////////////////////////////////////////
    void            AddTitle();                             // �������ͼ�ı���
    void            AddStandard();                          // �������ͼ�Ļ�����Ϣ
    void            AddEntity();                            // �������ͼ���豸��
    void            AddGroup();                             // �������ͼ�������
    void            AddViewControl();                       // �������ͼ�Ŀ��Ʊ�
    void            ShowActivateView(int nActivateView);    // ���ĵ�ǰ��ʾ��ͼ
    void            createHideButton();                     // �������ذ�ť
    // ��ǰ����������Ƿ�ɾ��
    bool            isCurEditParentDel(string szIndex, string szCurrentID = "");
    // ��¼������־
    void            AddOperaterLog(int &nOperateType, int &nObjectType, string &szOperateMsg);
    //////////////////////////////////////////////////////////////////////////////////
    void InitForm();                // ��ʼ��
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    struct GENERAL_ACTIVEX_LIST
    {
        GENERAL_ACTIVEX_LIST()
        {
            m_pGroupview = NULL;        // ����
            m_pGeneral = NULL;          // �����ݱ�
            m_pStandard = NULL;         // ������Ϣ
            m_pGroup = NULL;            // ����
            m_pDevice = NULL;           // �豸
            m_pBackParent = NULL;       // ������һ����ť
            m_ptxtTime = NULL;          // ˢ��ʱ��
        }
        WTable * m_pGroupview;
        WTable * m_pGeneral;
        SVGeneral * m_pStandard;  
        SVGroupList * m_pGroup;
        SVEnumDevice * m_pDevice;       
        WPushButton * m_pBackParent;
        WText  * m_ptxtTime;
    };

    //////////////////////////////////////////////////////////////////////////////////
    GENERAL_ACTIVEX_LIST m_GeneralList;
    //////////////////////////////////////////////////////////////////////////////////    

    SVAddGroup          * m_pAddGroup;              // �����
    SVDeviceList        * m_pDeviceList;            // �豸�б�����豸��һ����
    SVDevice            * m_pDevice;                // ����豸�ڶ���
    SVMonitorview       * m_pMonitorview;           // �������ͼ
    SVMonitorList       * m_pMonitorList;           // ������б���Ӽ������һ����
    SVMonitor           * m_pMonitor;               // ��Ӽ�����ڶ���
    SVSEView            * m_pSVSEView;              // SE��ͼ
    SVAddSE             * m_pAddSVSE;               // ���SE
    SVBatchAdd          * m_pBatchAdd;              // �������
    CSVSortList         * m_pSortForm;              // ����
    WLineEdit           * m_pcurEditIndex;          // ��ǰ���ڱ༭
    WTableCell          * m_pTitleCell;             // ��������Cell
	WPushButton         * m_pTranslateBtn;          // ���밴ť
	WPushButton         * m_pExChangeBtn;           // ˢ��
    list<WText*>          m_lsPath;	                // ��·��
    WSignalMapper         m_GroupName;              // �����ư�MAP
    //////////////////////////////////////////////////////////////////////////////////    
    //bool m_bShowList;                               // �Ƿ����б���ͼ
    //bool m_bEntityHide;                             // �豸�Ƿ�����
    //bool m_bGroupHide;                              // ���Ƿ�����
    ////////////////////////////////////////////////////////////////////////////////// 
    string              m_szIDCUser;                    // User's ID
    string              m_szIDCPwd;                     // User's Password
    string              m_szGlobalEvent;                // ˢ���¼�
    string              m_szEditIndex;                  // ��ǰ���ڱ༭����||�豸������
    string              m_szActiveOptIndex;             // ��ǰ����ID
    string              m_szUserShowName;               // ��ǰ��¼�û�����ʾ����

    CUser             * m_pSVUser;                      // �û�
    
	int		            m_nActiveView;                  // ��ǰ������ͼ
	int                 m_nPreviewView;                 // ǰһ��ͼ
    int                 m_nActiveOptType;               // ��ǰ����
    OperateLog          m_pOperateLog;
    list<string>        m_lsNewMonitorList;             // �¼�����б�

    static char         m_szLogData[1025];
    friend              class SVMonitorview;            // ��Ԫ��
    friend              class DemoTreeList;
};


#endif

