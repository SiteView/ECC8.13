#pragma once
#include "WContainerWidget"
#include <WPushButton>

class WTable;
class WText;
class WCheckBox;
class CFlexTable;
class CMainTable;
class WLineEdit;
class WImage;
class WApplication;

class WSVMainTable;
class WSVFlexTable;
class WSVButton;

//IP地址
typedef struct _IPAddress
{
	//是否验证
	int iCheck;
	//IP地址
	std::string strIPAddress;
	//保存天数
	std::string strDate;
}IPAddress,*PIPAddress;

class CGeneral :	public WContainerWidget
{
//MOC: W_OBJECT CGeneral:WContainerWidget
    W_OBJECT;
public:
	CGeneral(WContainerWidget *parent = 0);
	~CGeneral(void);

public:
	WApplication*  appSelf;
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	CFlexTable *pUserTable;
	CFlexTable *pUserTable2;
	WCheckBox *pCheckBox;
	WTable * pUserListTable;
	WTable * pUserListTable2;
	WText * pSText;
	WText * pIPText;
	WText * pSaveDataText;
	WText * pAdvancedText;
	WLineEdit * pAdvancedEdit;
	WLineEdit * pIPEdit;
	WLineEdit * pDataEdit;
	WPushButton * pSaveButton3;
	WPushButton * pSaveButton4;

	WSVMainTable * m_pMainTable;
	WSVFlexTable * m_sFlexTable;
	WSVFlexTable * m_aFlexTable;
	WPushButton * m_TranslateBtn;
	WPushButton * m_ExChangeBtn;
	WSVButton * pSaveButton;
	WSVButton * pSaveButton2;

	virtual void refresh();

public:
	void ShowMainTable();
	void NewShowMainTable();
	void AddJsParam(const std::string name, const std::string value);
	void loadString();

private : //language;
	std::string strMainTitle; 
	std::string strTitle; 
	std::string strCheckBox; 
	std::string strEdit;
	std::string strHelp;
	std::string strSave;
	std::string strDateName;
	std::string strDateHelp;
	std::string sErrIP;
	std::string sErrDate;
	std::string sErrDate1;
	std::string szSaveSucess;
	std::string szSaveFail;
	std::string strMtitle;
	std::string strBName;
	std::string strSName;
	int bVersion;
	std::string strCustomHelp;
	std::string strSEHelp;
	std::string sCustomErr;
	std::string sSEErr;
	std::string strCurrentLanguage;

	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

private :
	std::string strOType;
	std::string strOName;
	std::string strModifyName;
	std::string strModifyDay;
	std::string strRefresh1;

private slots:
	//MOC: SLOT CGeneral::ShowEdit()
    void ShowEdit();
	//MOC: SLOT CGeneral::Save()
	void Save();
	//MOC: SLOT CGeneral::SaveName()
	void SaveName();
	//MOC: SLOT CGeneral::Translate()
	void Translate();
	//MOC: SLOT CGeneral::ExChange()
	void ExChange();
	//MOC: SLOT CGeneral::ShowHelp();
	void ShowHelp();
};
