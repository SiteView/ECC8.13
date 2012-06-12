

#ifndef _SV_TEST_DEVICE_H_
#define _SV_TEST_DEVICE_H_

#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WScrollArea"

class WSPopTable;
class WSPopButton;

#include <string>
#include <list>

using namespace std;


#ifdef WIN32
#include <windows.h>
#endif


//const int svBufferSize = 1024 * 10 ; 
//const int svMax_Size = 512;

class SVDeviceTest : public WContainerWidget
{
    //MOC: W_OBJECT SVDeviceTest:WTable
    W_OBJECT;
public :
    SVDeviceTest(WContainerWidget* parent = NULL);

    void setApplication(WApplication *pApp){m_pApp = pApp;};
    virtual void refresh();

    string getCmd();

	WSPopButton * m_pClose;

public signals:
private slots:
    //MOC: SLOT SVDeviceTest::showresult()
    void showresult();
    //MOC: SLOT SVDeviceTest::closeWnd()
    void closeWnd();
	//MOC: SLOT SVDeviceTest::Translate()
	void Translate();
	//MOC: SLOT SVDeviceTest::ExChange()
	void ExChange();
private:
    void        loadString();
    void        initForm();
	void NewInitForm();

    void        createContain();
    void        createOperate();
	void NewCreateContain();
	void NewCreateOperate();

	void AddJsParam(const std::string name, const std::string value,  WContainerWidget * parent);

    void        TestDevice();
    void        changeQueryString(const char * pszQuery, char* pszQueryString);
    void        PrintReturn(const char* szReturn);
    void        GetDllAndFunc(const char * pszQuery, string &szDll, string &szFunc);
    string      GetSEID(const char * pszQuery);

#ifdef WIN32
    static DWORD WINAPI ThreadFunc(LPVOID lpParam);

    HANDLE m_hThread;
#else
#endif
private:
    string      m_szTitle;
    string      m_szClose;
    string      m_szCloseTip;
    string      m_szResult;
    string      m_szWaiting;
    string      m_szFuncErr;
    string      m_szDllErr;
    string      m_szTestSucc;
    string      m_szTestFail;
    string      m_szQuery;
    string      m_szTimeout;
    string      m_szQueryEmpty;

    bool        m_bFirst;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	std::string strParam;
private://WT
    WText    *  m_pState;
	WText    *  m_pWait;
	WText    *  m_pFinish;
    //WTable   *  m_pContentTable;
	WSPopTable   *  m_pContentTable;

    WTable   *  m_pSubContent;
    WScrollArea * m_pScrollArea;
    WPushButton * m_pHideButton;
	//WSPopButton * m_pHideButton;

    //WPushButton * m_pClose;

    WApplication * m_pApp;
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
