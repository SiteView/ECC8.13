#ifndef _SV_GROUP_BATCH_ADD_H_
#define _SV_GROUP_BATCH_ADD_H_

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WebSession.h"

#include <string>
#include <list>

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

#include "conditionparam.h"
#include "paramitem.h"

#include "../svtable/SVTable.h"
#include "../userright/user.h"

class SVBatchAdd : public WTable
{
    //MOC: W_OBJECT SVBatchAdd:WTable
    W_OBJECT;
public:
    SVBatchAdd(WContainerWidget* parent = NULL,  CUser * pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");    
    //~SVBatchAdd();

    void setAdvParamList(list<SVParamItem*> & lstParam)  { m_plsAdvParam = &lstParam; };
    void setBaseParamList(list<SVParamItem*> & lstParam) { m_plsBaseParam = &lstParam; };
    void setDynParamList(list<SVParamItem*> & lstParam) { m_pDynList = &lstParam; };

    void setDeviceIndex(string &szIndex) { m_szDeviceIndex = szIndex; };
    void setMonitorType(int &nMonitorType) { m_nMonitorID = nMonitorType; };
    void setHostName(string &szHostName) { m_szHostName = szHostName; };
    void setPoint(string &szPoint) {m_szPoint = szPoint;};
    void setNetworkset(string &szNetwork) {m_szNetworkset = szNetwork; };
    void setErrCondition(SVConditionParam * pCondition){ m_pErrCond = pCondition ;};
    void setWarnCondition(SVConditionParam * pCondition){ m_pWarnCond = pCondition ;};
    void setGoodCondition(SVConditionParam * pCondition){ m_pGoodCond = pCondition ;};
    //void setValueList(list<sv_value_label*> & lsParam)   { m_pValueList = &lsParam; };

    void addValueList(string &szDynName); 
public signals:
    //MOC: SIGNAL SVBatchAdd::backPreview()
    void backPreview();
    //MOC: SIGNAL SVBatchAdd::AddMonitorSucc(string,string)
    void AddMonitorSucc(string szName, string szIndex);
private slots:
    //MOC: SLOT SVBatchAdd::savemonitor()
    void savemonitor();
    //MOC: SLOT SVBatchAdd::cancel()
    void cancel();
    //MOC: SLOT SVBatchAdd::selall()
    void selall();
private:
    int    m_nMonitorID;
    string m_szNetworkset;
    string m_szDeviceIndex ;
    string m_szMonitorName;
    string m_szHostName;
    string m_szPoint;
    string m_szDynName;

    string m_szAddMonitorErr;

    void loadString();
    void initForm();
    void clearlist();

    void CreateOperater();
    void CreateList();

    bool saveBaseParam(OBJECT & objMonitor, string &szLabel);
    bool saveAdvParam(OBJECT & objMonitor, string &szLabel);
    bool saveCondition(OBJECT & objMonitor);

    string  m_szSave;
    string  m_szSaveTip;
    string  m_szCancel;
    string  m_szCancelTip;
    string  m_szSelAll;
    string  m_szAddTitle;

    int          m_nMonitorType;

    WTable           * m_pContentTable;
    WTable           * m_pSubContent;
    WTable           * m_pList;
    WCheckBox        * m_pSelAll;
    WText            * m_pMonitorName;

    typedef list<SVParamItem*>::iterator listParamItem;
    list<SVParamItem*> * m_plsBaseParam;                                           // 基础数据
    list<SVParamItem*> * m_plsAdvParam;
    list<SVParamItem*> * m_pDynList;

    SVConditionParam * m_pErrCond;                              // 错误条件
    SVConditionParam * m_pWarnCond;                             // 警告条件
    SVConditionParam * m_pGoodCond;                             // 正常条件

    SVIntTable              m_pSVList;

    CUser *  m_pSVUser;
    string   m_szIDCUser;
    string   m_szIDCPwd;

    WPushButton *  m_pSave;
    WPushButton *  m_pCancel;

	//写操作日志用
	string m_szOperateMonitor;
};

#endif