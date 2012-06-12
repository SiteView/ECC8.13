/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�: adddevice1st.h
// ����豸��һ������ʾ�豸�б�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_DEVICE_1ST_H_
#define _SV_ADD_DEVICE_1ST_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WPushButton"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "showtable.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVDeviceList : public  WTable//WContainerWidget
{
    //MOC: W_OBJECT SVDeviceList:WTable
    W_OBJECT;
public:
    SVDeviceList(WContainerWidget *parent = NULL,string szIDCUser = "default", string szIDCPwd = "localhost");

    void SetUserPwd(string &szUser, string &szPwd);                     // ���� IDC �û� ����
    void setParentIndex(string &szIndex){m_szParentID = szIndex;};      // ���� �ϼ� �ڵ� ����
    string getParentID(){return m_szParentID;};                         // �õ� �ϼ� �ڵ� ����
public signals:
    //MOC: SIGNAL SVDeviceList::backPreview()
    void backPreview();                                                 // ������һ��ҳ��
    //MOC: SIGNAL SVDeviceList::AddNewDevice(string)
    void AddNewDevice(string szIndex);                                  // �����Ϣ���豸���豸����������
private slots:
    //MOC: SLOT SVDeviceList::addDevice(const std::string)
    void addDevice(const std::string szIndex);                          // ����豸
    //MOC: SLOT SVDeviceList::cancel()
    void cancel();                                                      // ȡ�����
	//MOC: SLOT SVDeviceList::Translate()
	void Translate();                                                   // ����
private:
    //string m_szTitle;                                                   // ����
    //string m_szCancel;                                                  // ȡ�����
    //string m_szCancelTip;                                               // ȡ�������ʾ��Ϣ

    string m_szParentID;                                                // �ϼ��ڵ�
    list<SVShowTable*> m_lsDevice;                                      // ����/��ʾ�ӱ� ��list

    void enumDeviceGroup();                                             // ö�� �豸 ��
    void initForm();                                                    // ��ʼ��ҳ��
    //void loadString();                                                  // �����ַ���
    void createTitle();                                                 // ��������
    void createOperate();                                               // ��������
    void addDeviceByID(string &szDeviceID, SVShowTable * pTable);       // ��������豸�б�

    WSignalMapper m_DeviceMap;                                          // Singal map��Entity Template��
    WTable        * m_pContentTable;
    WTable        * m_pSubContent;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string    m_szIDCUser;                                              // IDC �û�
    string    m_szIDCPwd;                                               // IDC ����

	//����
	WPushButton * m_pTranslateBtn;
	
	//string          m_szTranslate;
	//string          m_szTranslateTip;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
