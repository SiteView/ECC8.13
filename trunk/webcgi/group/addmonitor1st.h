/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�: addmonitor1st.h
// ��Ӽ������һ����ö���豸������ӵļ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_MONITOR_1ST_H_
#define _SV_ADD_MONITOR_1ST_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVMonitorList : public WTable
{
    //MOC: W_OBJECT SVMonitorList:WTable
    W_OBJECT;
public:
    SVMonitorList(WContainerWidget* parent = NULL, string szIDCUser = "default", 
        string szPwd = "localhost");
    void enumMonitorTempByType(string &szDeviceType, string &szDeviceID);               // �����豸���� ö�� �����ģ��
    void SetUserPwd(string &szUser, string &szPwd);                                     // ����IDC �û� ����
    string getParentIndex() {return m_szDeviceID;};
public signals:
    //MOC: SIGNAL SVMonitorList::AddMonitorByType(int,string)
    void AddMonitorByType(int nMonitorType,string szDeviceIndex);                       // ѡ������ģ����� �����
    //MOC: SIGNAL SVMonitorList::Cancel()       
    void Cancel();                                                                      // ȡ�����
private slots:
    //MOC: SLOT SVMonitorList::CancelAdd()
    void CancelAdd();                                                                   // ȡ����Ӽ����
    //MOC: SLOT SVMonitorList::MonitorMTClicked(int)
    void MonitorMTClicked(int nMTID);                                                   // �����ģ�� ѡ������
private:        
    //string m_szCancel;                                                                  // ȡ��
    //string m_szCancelTip;                                                               // ȡ����ʾ
    //string m_szTitle;                                                                   // ����

    string m_szDeviceType;                                                              // �豸����
    string m_szDeviceID;                                                                // �豸����

    //void loadString();                                                                  // �����ַ���
    void initForm();                                                                    // ��ʼ��

    void createTitle();                                                                 // ��������
    void createMonitorList();                                                           // ���������ģ���б�
    void createOperate();

    void enumMonitor(string &szDeviceType);                                             // ö�� ����� ģ��

    WTable * m_pList;                                                                   // �б�
    WTable * m_pContentTable;
    WTable * m_pSubContent;
    WText  * m_pTitle;                                                                  // ����
    
    WSignalMapper m_MonitorMap;                                                         // signal map
    void          removeMapping();

    list<WText*> m_lsName;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string   m_szIDCUser;                                                               // IDC �û�
    string   m_szIDCPwd;                                                                // IDC �û�����
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
