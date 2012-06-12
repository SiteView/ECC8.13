/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�: addmonitor2nd.h
// ��ӻ����޸ļ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_MONITOR_H_
#define _SV_ADD_MONITOR_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WText"
class WImage;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "showtable.h"

#include "paramitem.h"
#include "returnitem.h"

#include "conditionparam.h"
#include "batchadd.h"

#include "../userright/user.h"
#include "basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVMonitor : public WTable
{
    //MOC: W_OBJECT SVMonitor:WTable
    W_OBJECT;
public:
    friend class SVGroupview;
    SVMonitor(WContainerWidget * parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", 
        string szPwd = "localhost", int nMonitorID = -1);

    void showMonitorParam(int &nMTID,string &szDeviceIndex);                    // ��ʾ����� ����                  

    void EditMonitorByID(string &szEditMonitorID);                              // ���ݼ�������޸ļ����

    void SetUserPwd(string &szUser, string &szPwd);                             // ����IDC�û� ����

    string getCurrentEditID() {return m_szEditMonitorID;};
    string getParentID() {return m_szDeviceIndex;};

    void requesDynData();
public signals:
    //MOC: SIGNAL SVMonitor::CancelAddMonitor()
    void CancelAddMonitor();                                                    // ȡ�����
    //MOC: SIGNAL SVMonitor::BackPreview()
    void BackPreview();                                                         // ������һ��ҳ��
    //MOC: SIGNAL SVMonitor::AddMonitorSucc(string,string)
    void AddMonitorSucc(string szName, string szIndex);                         // ��ӳɹ�
    //MOC: SIGNAL SVMonitor::EditMonitorSucc(string,string)
    void EditMonitorSucc(string,string);                                        // �༭�ɹ�
    //MOC: SIGNAL SVMonitor::BatchAddNew()
    void BatchAddNew();                                        // �༭�ɹ�
private slots:
    //MOC: SLOT SVMonitor::Preview()
    void Preview();                                                             // ��һ��ҳ��
    //MOC: SLOT SVMonitor::showHelpText()
    void showHelpText();                                                        // ��ʾ/���ذ���
    //MOC: SLOT SVMonitor::SaveMonitor()
    void SaveMonitor();                                                         // ��������
    //MOC: SLOT SVMonitor::Cancel()
    void Cancel();                                                              // ȡ��
    //MOC: SLOT SVMonitor::setDefaultAlert()
    void setDefaultAlert();
    //MOC: SLOT SVMonitor::ContinueAdd()
    void ContinueAdd();
    //MOC: SLOT SVMonitor::BatchAddMonitor()
    void BatchAddMonitor();
    //MOC: SLOT SVMonitor::listDynParam()
    void listDynParam();
	//MOC: SLOT SVMonitor::Translate()
	void Translate();                                                           // ����
private:
    int m_nMonitorID;                                                           // �����ģ�������
    string m_szMonitorName;                                                     // �����ģ�����ʾ����
    string m_szDeviceIndex;                                                     // ����Ӽ�������豸
    string m_szNetworkset;
    string m_szEditMonitorID;                                                   // �༭���������
    string m_szHostName;                                                        // ��������
    string m_szPoint;
    string m_szDll;
    string m_szFunc;
    string m_szQuery;

    bool   m_bHasDynamic;
    bool   m_bContinueAdd;
    bool   m_bError;
    OBJECT m_objTemplate;                                                       // �����ģ����

    list<SVParamItem*> m_lsDyn;

    typedef map<string, SVParamItem* , less<string> >::iterator mapitem;
    typedef list<SVParamItem*>::iterator listItem;
    list<SVParamItem*> m_lsBaseParam;                                           // ��������
    list<SVParamItem*> m_lsAdvParam;                                            // �߼�

    list<SVReturnItem*> m_lsReturn;                                             // ����ֵ list

    SVShowTable        * m_pGeneral;                                            // ����ѡ��
    SVShowTable        * m_pAdv;                                                // �߼�ѡ��
    SVShowTable        * m_pCondition;                                          // ����

    bool m_bShowHelp;                                                           // ��ʾ/���ذ���
private: // fuction
    void initForm();                                                            // ��ʼ��ҳ��

    void createTitle();                                                         // ����
    void createHelp();                                                          // ������ť
    void createAdvParam();                                                      // �����߼�ѡ��
    void createBaseAdv(WTable * pTable);                                        // �����߼������еĻ�������

    void createDeviceName(WTable * pTable);                                     // �豸����
    void createMonitorName(WTable * pTable);                                    // ���������
    void createBaseParam();                                                     // ����ѡ�� 
    void createConditionParam();                                                // ����
    void createOperate();                                                       // ����

    void enumBaseParam();                                                       // ö�ٻ���ѡ��
    void enumAdvParam();                                                        // ö�ٸ߼�ѡ��
    void enumReturnParam();                                                     // ö�ٷ���ֵ

    void enumDeviceRunParam();

    //void loadStrings();                                                         // �����ַ���
    void clearData();                                                           // ��������
    void getHostNameByID(string &szDeviceID, string &szHostName);               // �����豸ID�õ���������

    void checkBaseParam();                                                      // У���������
    void checkAdvParam();                                                       // У��߼�����
    void checkConditionParam();                                                 // У�鱨������
    void checkMonitorName();
    void checkMonitorFreq();

    bool saveBaseAdvParam(MAPNODE &mainnode);
    bool saveBaseParam(OBJECT &objMonitor);                                     // �����������
    bool saveAdvParam(OBJECT &objMonitor);                                      // ����߼�����
    bool saveCondition(OBJECT &objMonitor);                                     // ���汨������

    void SetBaseAdvParam(MAPNODE &mainnode);
    void SetBaseParam(OBJECT &objMonitor);                                      // ���û�������
    void SetAdvParam(OBJECT &objMonitor);                                       // ���ø߼�����
    void SetConditionParam(OBJECT &objMonitor);                                 // ���ñ�������

    void clearBaseParam();                                                      // �����������
    void clearAdvParam();                                                       // ����߼�ѡ��
    void clearConditionParam();                                                 // ����������

    //string m_szBack;                                // ����
    //string m_szBackTip;                             // ������һ����ʾ
    //string m_szAdd;                                 // ���
    //string m_szAddTip;                              // �����ʾ
    //string m_szCancel;                              // ȡ��
    //string m_szCancelTip;                           // ȡ����ʾ
    //string m_szSaveTip;                             // ������ʾ
    //string m_szSave;                                // ����
    //string m_szBatchAdd;                            // �������
    //string m_szBatchAddTip;                         // ���������ʾ
    //string m_szContinueAdd;                         // �������
    //string m_szContinueAddTip;                      // ���������ʾ
    //string m_szSetAlert;
    //string m_szSetAlertTip;

    //string m_szMonitor;                             // �����
    //string m_szAddTitle;                            // ��ӱ���
    //string m_szEditTitle;                           // �༭����
    //string m_szAdvTitle;                            // �߼�ѡ�����
    //string m_szConditionTitle;                      // ������������
    //string m_szGeneralTitle;                        // ����ѡ�����
    //string m_szHelpTip;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct BASE_ADV_PARAM
    {
        BASE_ADV_PARAM()
        {
            m_pDescription = NULL;                   // ���������
            m_pReportDesc = NULL;                    // ��������
            m_pPlan = NULL;                          // ����ƻ�
            m_pCheckErr = NULL;                      // У�����
            m_pMonitorFreq = NULL;                   // ����ʱ���Ƶ��
            m_pTimeUnit = NULL;                      // ʱ�䵥λ
        }
        WTextArea * m_pDescription;                   // ���������
        WTextArea * m_pReportDesc;                    // ��������
        WComboBox * m_pPlan;                          // ����ƻ�
        WCheckBox * m_pCheckErr;                      // У�����
        WLineEdit * m_pMonitorFreq;                   // ����ʱ���Ƶ��
        WComboBox * m_pTimeUnit;                      // ʱ�䵥λ
    };
    //struct BASE_ADV_SHOW_TEXT
    //{
    //    string m_szDesc, m_szDescHelp;                  // ������ ��������
    //    string m_szCheckErr, m_szCheckHelp;             // У�����У��������
    //    string m_szPlan, m_szPlanHelp;                  // ����ƻ�������ƻ�����
    //    string m_szFreq, m_szFreqHelp;                  // ���Ƶ�ʣ����Ƶ�ʰ���
    //    string m_szReport, m_szReportHelp;              // ������ʾ��Ϣ���������
    //    string m_szDevice, m_szDeviceHelp;              // �豸���ƣ��豸���ư���
    //    string m_szMonitor, m_szMonitorHelp;            // ��������ƣ���������ư���
    //    string m_szErrName, m_szFreqErr;//, m_szErrIPAddress;        // ��������ƴ���
    //};

    //// ʱ�䵥λ
    //struct TIME_UNIT
    //{
    //    string      m_szMinute;         // ����
    //    string      m_szHours;          // Сʱ
    //};
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //BASE_ADV_SHOW_TEXT m_ShowText;
    BASE_ADV_PARAM     m_AdvList;
    //TIME_UNIT          m_timeunit;

    map<WText*, string , less<WText*> > m_HelpMap;              
    map<WText*, string , less<WText*> >::iterator m_helpItem;
    WText         *    m_pDeviceName;                           // �豸����
    WLineEdit     *    m_pMonitorName;                          // ���������

    WPushButton   *    m_pBack;                                 // ����
    WPushButton   *    m_pCancel;
    WPushButton   *    m_pSave;                                 // ���
    WPushButton   *    m_pBatchAdd;                             // �������
    WPushButton   *    m_pContinue;                             // ������ť

    WPushButton   *    m_pSetAlert;
    WPushButton   *    m_pListDynBtn;

    WText         *    m_pMonitorHelp;                          // ��������Ʊ���
    WText         *    m_pTitle;                                // ����ؼ�
    WText         *    m_pFreqHelp;

    SVConditionParam * m_pErrCond;                              // ��������
    SVConditionParam * m_pWarnCond;                             // ��������
    SVConditionParam * m_pGoodCond;                             // ��������

    WTable           * m_pContentTable;
    WTable           * m_pSubContent;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string         m_szIDCUser;
    string         m_szIDCPwd;
    CUser        * m_pSVUser;
    
	//����
	WPushButton * m_pTranslateBtn;
	
	//string m_szTranslate;
	//string m_szTranslateTip;

	//д������־
	//string m_szTypeAdd;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
