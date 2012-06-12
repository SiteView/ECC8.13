/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_GORUP_LIST_H_
#define _SV_GORUP_LIST_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WSignalMapper"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../svtable/SVTable.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../demotreeview/define.h"
#include "../userright/user.h"

#include "basefunc.h"

class SVGroupList : public WContainerWidget
{
    //MOC: W_OBJECT SVGroupList:WContainerWidget
    W_OBJECT;
public:
    SVGroupList(WContainerWidget* parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    bool                isChildEdit(string szIndex);
    bool                isParentEdit(string szIndex);
    bool                isInGroup(string& szIndex);
    void                AddGroup(string &szName, string &szIndex);
    void                BackGroup(string &szIndex);
    void                DelGroup(string &szIndex);
    void                delGroupRow(string &szIndex);
    void                EditGroup(string &szName, string &szIndex);
    void                EnterGroupByID(string &szIndex);
    void                SetUserPwd(string &szUser, string &szPwd);
    void                refreshNamePath();
    void                refreshGroup(string szIndex);

    const char *        getGroupName();
    const char *        getGroupDesc();
    const char *        getGroupIndex() {return m_szIndex.c_str();}
    list<base_param>&   getGroupPath(){return m_lsPath;};
    int                 m_nDeviceCount;
    int                 m_nMonitorCount;
    int                 m_nMonitorErrCount;
    int                 m_nMonitorWarnCount;
    int                 m_nMonitorDisableCount;
    string              m_szAdvState;
public signals:
    //MOC: SIGNAL SVGroupList::AddNewGroup()
    void AddNewGroup();
    //MOC: SIGNAL SVGroupList::EditGroupByID(string)
    void EditGroupByID(string szEditID);
    //MOC: SIGNAL SVGroupList::EnumDeviceByID(string)
    void EnumDeviceByID(string szEditID);
    //MOC: SIGNAL SVGroupList::sortGroupsList(int)
    void sortGroupsList(int nType);
    //MOC: SIGNAL SVGroupList::ChangeGroupState(string,int)
    void ChangeGroupState(string szGroupID, int nMonitorState);
    //MOC: SIGNAL SVGroupList::DeleteGroupSucc(string,string)
    void DeleteGroupSucc(string szName, string szIndex);
    //MOC: SIGNAL SVGroupList::DeleteDeviceSucc(string,string)
    void DeleteDeviceSucc(string strName,string szIndex);                          // �����豸�ɹ�
private slots:
    //MOC: SLOT SVGroupList::selAll()
    void selAll();
    //MOC: SLOT SVGroupList::selNone()
    void selNone();
    //MOC: SLOT SVGroupList::invertSel()
    void invertSel();
    //MOC: SLOT SVGroupList::delSel()
    void delSel();
    //MOC: SLOT SVGroupList::add()
    void add();
    //MOC: SLOT SVGroupList::editGroup()
    void editGroup();
    //MOC: SLOT SVGroupList::gotoGroup()
    void gotoGroup();
    //MOC: SLOT SVGroupList::changeState()
    void changeState();
    //MOC: SLOT SVGroupList::delSelGroup()
    void delSelGroup();
    //MOC: SLOT SVGroupList::deleteGroup()
    void deleteGroup();
    //MOC: SLOT SVGroupList::enableSelGroup()
    void enableSelGroup();
    //MOC: SLOT SVGroupList::disableSelGroup()
    void disableSelGroup();
    //MOC: SLOT SVGroupList::disableGroupSucc()
    void disableGroupSucc();
    //MOC: SLOT SVGroupList::sortGroups()
    void sortGroups();
private:
    //function list
    //void            loadString();                                       // ������Դ�ַ���
    void            initForm();                                         // ��ʼ��

    void            addGroupList(string &szName, string &szIndex);      // ������鵽���б���
    void            createHideButton();                                 // �������ذ�ť
    void            createGroupList(WTable * pTable);                   // �������б�
    void            DelDevice(string &szIndex);                         // ɾ���豸
    void            editGroupList(string &szName, string &szIndex);     // �����������༭����ʾ����
    void            enumGroup(string &szIndex);                         // ö��������
    void            enterGroup(string &szIndex);                        // ������
    void            enumRight();                                        // ö��Ȩ��

    void            createOperate(WTable * pTable);                     // ��������
    void            createSelOperate();                                 // ���� ѡ�����
    void            createEnableOperate();                              // ���� ����/���ò���
    void            createRefreshOperate();                             // ���� ˢ�²���
    void            createDelOperate();                                 // ���� ɾ������
    void            changeOperateState();                               // �޸� ������ť����ʾ״̬
    void            changeDelState();                                   // �޸� ɾ����ť��ʾ״̬
    void            changeSelState();                                   // �޸� ѡ��ť��ʾ״̬
    void            changeEnableState();                                // �޸� ����/���ð�ť��ʾ״̬

    // �ж����Ƿ񱻽�ֹ���������״̬������Ϣ
    bool            isDisable(string &szGroupID, string &szState, bool bAddBR = true);
    // ��������������·��
    bool            makePath(string &szGroupID, list<base_param> &lsPath);
    // �����������õ�������
    string          getGroupName(string szIndex);
private:
    SVTable         m_svGroup;                          // ��¼�ؼ����
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string          m_szIndex;                          // ��ǰ���������ID��
    string          m_szGroupName;                      // ��ǰ�������
    string          m_szGroupDesc;                      // ��ǰ�������
    string          m_szDelSelIndex;                    // ��ǰѡ��ɾ��������
    string          m_szIDCUser;                        // user's id
    string          m_szIDCPwd;                         // user's password

    //string          m_szDelSelTip;                      // IDS_Delete_Sel_Group_Tip
    //string          m_szSelAllTip;                      // IDS_All_Select
    //string          m_szSelNoneTip;                     // IDS_None_Select
    //string          m_szInvertSelTip;                   // IDS_Invert_Select
    //string          m_szSortTip;                        // IDS_Sort
    //string          m_szAdd;                            // IDS_Add_Group
    //string          m_szAddTip;                         // IDS_Add_Group_Tip
    //string          m_szColState;                       // IDS_State
    //string          m_szColDesc;                        // IDS_State_Description
    //string          m_szColEdit;                        // IDS_Edit
    //string          m_szColName;                        // IDS_Name
    //string          m_szColLast;                        // IDS_Table_Col_Last_Refresh
    //string          m_szColDel;                         // IDS_Delete
    //string          m_szDelTip;                         // IDS_Delete_Group_Tip
    //string          m_szEditTip;                        // IDS_Edit
    //string          m_szEnableTip;                      // IDS_Enable_Group
    //string          m_szDisableTip;                     // IDS_Disable_Group
    //string          m_szDelAsk;                         // IDS_Delete_Group_Confirm
    //string          m_szDelSelAsk;                      // IDS_Delete_Sel_Group_Confirm
    //string          m_szTitle;                          // IDS_Sub_Group
    //string          m_szGroupsDisable;                  // IDS_Group_Can_not_Disable
    //string          m_szGroupsEnable;                   // IDS_Group_Can_not_Enable
    //string          m_szForver;                         // IDS_Group_Disable_Forver
    //string          m_szTemprary;                       // IDS_Group_Disable_Temprary
    //string          m_szStartTime;                      // IDS_Start_Time
    //string          m_szEndTime;                        // IDS_End_Time
    //string          m_szNoGroup;                        // IDS_GROUP_LIST_IS_NULL    
    //string          m_szMonitorDisable;                 // IDS_Monitor_Disable_Count
    //string          m_szDeviceCount;                    // IDS_Device_Count
    //string          m_szMonitorCount;                   // IDS_Monitor_Count
    //string          m_szMonitorError;                   // IDS_Monitor_Error_Count
    //string          m_szMonitorWarn;                    // IDS_Monitor_Warn_Count
    //string          m_szOperateGroup;                   // IDS_Group

    CUser           * m_pSVUser;                        // �û�Ȩ�޹�����
    bool            m_bHasAddRight;                     // �Ƿ����������Ȩ��
    bool            m_bHasDelRight;                     // �Ƿ���ɾ������Ȩ��
    bool            m_bHasEditRight;                    // �Ƿ��б༭����Ȩ��
    bool            m_bHasSortRight;                    // �Ƿ���������ʾ˳��Ȩ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WPushButton     * m_pBtnHide;                       // ����/������ɹ� ��ť
    WPushButton     * m_pBtnHideDel;                    // ɾ��������ѡ�� ��ť
    WPushButton     * m_pBtnRefresh;                    // ������ѡ��״̬ ��ť
    WPushButton     * m_pBtnDelSel;                     // ɾ����ѡ�� ��ť
    WPushButton     * m_pBtnEnterGroup;                 // ������ѡ�� ��ť
    WPushButton     * m_pBtnEdit;                       // �༭��ѡ�� ��ť
    WPushButton     * m_pAdd;                           // ��Ӱ�ť
    WLineEdit       * m_pCurrentGroup;                  // ��ǰ��������
    WImage          * m_pDel;                           // ɾ����ͼƬ����ť
    WImage          * m_pEnable;                        // ���ã�ͼƬ����ť
    WImage          * m_pDisable;                       // ���ã�ͼƬ����ť
    WImage          * m_pSort;                          // ����ͼƬ����ť
    WImage          * m_pSelAll;                        // ȫѡ��ͼƬ����ť
    WImage          * m_pSelNone;                       // ȡ��ȫѡ��ͼƬ����ť
    WImage          * m_pSelInvert;                     // ��ѡ��ͼƬ����ť
    WTable          * m_pGroupList;                     // ���б�
    WTable          * m_pOperate;                       // �������ܱ�
    WText           * m_pHasNoChild;                    // ������ ���ֿؼ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    list<base_param> m_lsPath;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
