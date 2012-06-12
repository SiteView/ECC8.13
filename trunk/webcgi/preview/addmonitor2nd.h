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
#include "../../opens/libwt/WApplication"
class WImage;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../group/showtable.h"

#include "../group/paramitem.h"
#include "../group/returnitem.h"

#include "conditionparam.h"

#include "../userright/user.h"
#include "../group/basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVMonitor : public WTable
{
    //MOC: W_OBJECT SVMonitor:WTable
    W_OBJECT;
public:
    friend class SVGroupview;
    SVMonitor(WContainerWidget * parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", 
        string szPwd = "localhost", int nMonitorID = -1);

    void showMonitorParam(int &nMTID, WApplication * szApp);                    // ��ʾ����� ����                  

    void SetUserPwd(string &szUser, string &szPwd);                             // ����IDC�û� ����

private slots:
    //MOC: SLOT SVMonitor::showHelpText()
    void showHelpText();                                                        // ��ʾ/���ذ���
    //MOC: SLOT SVMonitor::Translate()
    void Translate();									                        // ����
    //MOC: SLOT SVMonitor::ExChange()
    void ExChange();                                                            // ˢ��
private:
    int m_nMonitorID;                                                           // �����ģ�������
    string m_szMonitorName;                                                     // �����ģ�����ʾ����
    string m_szHostName;                                                        // ��������

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

    void clearData();                                                           // ��������

    void SetBaseAdvParam(MAPNODE &mainnode);
    void SetBaseParam(OBJECT &objMonitor);                                      // ���û�������
    void SetAdvParam(OBJECT &objMonitor);                                       // ���ø߼�����
    void SetConditionParam(OBJECT &objMonitor);                                 // ���ñ�������

    void clearBaseParam();                                                      // �����������
    void clearAdvParam();                                                       // ����߼�ѡ��
    void clearConditionParam();                                                 // ����������
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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //BASE_ADV_SHOW_TEXT m_ShowText;
    BASE_ADV_PARAM     m_AdvList;
    //TIME_UNIT          m_timeunit;

    map<WText*, string , less<WText*> > m_HelpMap;              
    map<WText*, string , less<WText*> >::iterator m_helpItem;
    WText         *    m_pDeviceName;                           // �豸����
    WLineEdit     *    m_pMonitorName;                          // ���������

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
	WApplication * m_pAppSelf;	
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
