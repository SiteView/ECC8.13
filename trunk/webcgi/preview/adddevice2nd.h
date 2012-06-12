/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_DEVICE_2ND_H_
#define _SV_ADD_DEVICE_2ND_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WApplication"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../group/showtable.h"

#include "../group/paramitem.h"

#include "dependtable.h"
#include "../userright/user.h"
#include "../group/basefunc.h"
#include "../svtable/SVTable.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVDevice : public WTable
{
    //MOC: W_OBJECT SVDevice:WTable
    W_OBJECT;
public:
    SVDevice(WContainerWidget * parent = NULL, CUser *pUser = NULL, string szIDCUser = "default", 
        string szPwd = "localhost", string szDeviceType = "");                  // ���캯��

    void requesDynData();
    void SetUserPwd(string &szUser, string &szPwd);                             // ���� IDC �û�
    void SetDeviceType(string &szDeviceType);                                   // ���� �豸�� ����
    void ClearData(string &szIndex, WApplication *szApp);                       // ��������
private slots:
    //MOC: SLOT SVDevice::showHelp()
    void showHelp();                                                            // ��ʾ����
    //MOC: SLOT SVDevice::TranslateNew()
    void TranslateNew();                                                        // ����
    //MOC: SLOT SVDevice::ExChange()
    void ExChange();                                                            // ˢ��
private:
    void initForm();                                                            // ��ʼ��ҳ��
    void createTitle();                                                         // ��������
    void createHelp();                                                          // ������������
    void createGeneral();                                                       // ���� ����ѡ��
    void createAdv();                                                           // ���� �߼�ѡ��

    void createHostName(WTable  * pTable);                                      // ���� ��������

    void enumBaseParam();                                                       // ö�� ��������
    void setTitle(string &szDeviceType);                                        // ���� ����

    typedef list<SVParamItem*>::iterator listItem;
    list<SVParamItem*> m_lsBasicParam;                                          // ����ѡ������list
    list<SVParamItem*> m_lsDyn;

    SVDependTable *  m_pAdvTable;                                               // �߼�ѡ��

    WText         * m_pTitle;                                                   // ����
    WText         * m_pHostHelp;                                                // �������ư���
    WText         * m_pHostNameHelp;                                            // ����������ʾ
    WLineEdit     * m_pDeviceTitle;                                             // �豸����


    SVShowTable   * m_pGeneral;                                                 // ������Ϣ��
    WTable        * m_pQuickAdd;
    WTable        * m_pContentTable;
    WTable        * m_pSubContent;
    string m_szDeviceType;                                                      // �豸����
    string m_szDeviceName;                                                      // �豸����
    

    bool m_bShowHelp;                                                           // ��ʾ/���ذ���
    
    typedef map<string, string, less<string> > SVReturnMap;
    typedef map<string, string, less<string> >::iterator SVReturnItem;
	map<string, string, less<string> > m_DeviceParam;
	bool m_bChanged;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string    m_szIDCUser;                                                      // IDC �û�
    string    m_szIDCPwd;                                                       // IDC �û�����
    CUser   * m_pSVUser;
	WApplication * m_pAppSelf;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
