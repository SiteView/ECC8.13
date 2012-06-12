

#ifndef _SV_REFRESH_MONITOR_H_
#define _SV_REFRESH_MONITOR_H_

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WScrollBar"
#include "../../opens/libwt/WApplication"

#include <string>
#include <list>

using namespace std;

#include "../svtable/WSPopButton.h"
#include "../svtable/WSPopTable.h"

class SVRefresh : public WTable
{
	//MOC: W_OBJECT SVRefresh:WTable
	W_OBJECT;
public :
	SVRefresh(WContainerWidget* parent = NULL);
	~SVRefresh();
	virtual void refresh();

private slots:
	//MOC: SLOT SVRefresh::clearEnvironment()
	void clearEnvironment();
	//MOC: SLOT SVRefresh::showresult()
	void showresult();
	//MOC: SLOT SVRefresh::getresult()
	void getresult();
	//MOC: SLOT SVRefresh::Translate()
	void Translate();
	//MOC: SLOT SVRefresh::ExChange()
	void ExChange();
private:
	void        loadString();
	void        initForm();

	void        createState();
	void        createTitle();

	void        createContain();
	void        createOperate();

	void        createHideButton();

	void        AddJsParam(const std::string name, const std::string value, WContainerWidget *parent);

	void        addDynData(const char* pszMonitorID);

	void        addDisableDyn(const char * pszMonitorID);

	void        getDeviceData(string &szDeviceID);
private:
	string      m_szTitle;
	string      m_szClose;
	string      m_szCloseTip;
	string      m_szResult;
	string      m_szColName;
	string      m_szColState;
	string      m_szColDesc;
	string      m_szDeviceName;
	string      m_szDeviceType;

	string      m_szDisable;

	bool        m_bGetDeviceData;

	string      m_szNormal;
	string      m_szError;
	string      m_szWarning;

	string      m_szMonitor;
	string      m_szState;
	string      m_szQueueName ;

	string      m_szRefreshStart;
	string      m_szRefreshEnd;
	string      m_szRefreshFailed;
	string      m_szRefreshTimeout;

	int         m_nTimes;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
public:
	//WPushButton * m_pCloseWnd;
	WSPopButton * m_pCloseWnd;

private://WT
	WTable   *  m_pStateList;
	WTable   *  m_pContentTable;
	WTable   *  m_pSubContent;

	WSPopTable * m_pPopTable;

	WScrollArea * m_pScrollArea;
	WText    *  m_pFailed;
	WImage   *  m_pRunning;

	WPushButton * m_pHideButton;
	WPushButton * m_pHideRefresh;

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;

public://WT
	WApplication *  appSelf;
public:
	string strListHeights;	
	string strListPans;
	string strListTitles;
};

#endif
