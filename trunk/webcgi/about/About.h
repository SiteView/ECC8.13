#pragma once
#include "WContainerWidget"
class WTable;
class WImage;
class WText;
class WApplication;
class WPushButton;

using namespace std;

class CAbout :	public WContainerWidget
{
public:
	//MOC: W_OBJECT CAbout:WContainerWidget
    W_OBJECT;
public:
	CAbout(WContainerWidget *parent = 0);
	~CAbout(void);
public : //add user var
	std::string strMainTitle;
	std::string strName;
	std::string strVersion;
	std::string strCopyRight;
	std::string strWelcom;
	std::string strSite;
	std::string strOther;
	std::string strTotal;
	int refreshCount;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

	std::string strTempVer;
public:
	//WScrollArea * pUserScrollArea;
	WTable * pUserTable;
	WImage * pUserImage;
	WText * pTotalText;
	WApplication *  appSelf;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;
public:
	void ShowMainTable();
	virtual void refresh();   
private slots:
	//MOC: SLOT CAbout::Translate()
	void Translate();
	//MOC: SLOT CAbout::ExChange()
	void ExChange();
};
