#pragma once
#include "WContainerWidget"
class WText;
class WTable;
class WImage;
class WApplication;
class WPushButton;
class WTableCell;

#include "../userright/user.h"
#include "basefunc.h"

struct svse_simple_state
{
    svse_simple_state()
    {
        nDisableCount = 0;
        nMonitorCount = 0;
        nErrorCount = 0;
        nWarnCount  = 0;
    }
    int nDisableCount;
    int nMonitorCount;
    int nErrorCount;
    int nWarnCount;
};

class CHeader :
	public WContainerWidget
{
	//MOC: W_OBJECT CHeader:WContainerWidget
    W_OBJECT;
public:
	CHeader(WContainerWidget *parent = 0);
	~CHeader(void);

public: //add user var
	WTable * FrameTable;
	WTable * UserTable;
	std::string strHeader;
	std::string strUser;
	std::string strNormal;
	std::string strDanger;
	std::string strErrer;
	WText * m_pUserIDText;
    WText * m_pNormalText;
    WText * m_pWarnningText;
    WText * m_pErrorText;
    WText * m_pAllText;

	int refreshCount;

	std::string hWelcome;
	std::string hNormal;
	std::string hDanger;
	std::string hError;
	std::string hAll;

	std::string strReloadFuncName;

    CUser * m_pSVUser;
	WApplication *  appSelf;


public: //add user fun
	void ShowMainTable();
	std::string GetReloadEvent();
	virtual void refresh();  

private slots:
	//MOC: SLOT CHeader::ShowEdit()
    void ShowEdit();
	//MOC: SLOT CHeader::Translate()
	void Translate();
	//MOC: SLOT CHeader::ExChange()
	void ExChange();

private:
	string strRefresh;
	string m_szTranslate;
	string m_szTranslateTip;
	string m_szRefresh;
	string m_szRefreshTip;
	WPushButton * m_pTranslateBtn;
	WPushButton * m_pExChangeBtn;
    
    // µÃµ½SE ¼òµ¥×´Ì¬
    svse_simple_state getSVSESimpleState(string szSVSEIndex = "1", string szIDCUser = "default", string szIDCPwd = "localhost");
};
