#pragma once

#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WPushButton;
class WApplication;
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
#include "WSignalMapper"
#include <list>
#include <SVTable.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;
//拓扑记录结构
typedef struct _OneRecord
{
	WCheckBox * pCheckBox;
	//用户名
	std::string strUserName;
	std::string strBackName;
	WText *pstrUserName;
	WLineEdit * pLineEdit;
	//拓扑图
	WImage * pTuop;
	std::string strTuop;
	WImage * pEdit;
	int nSort;
}OneRecord,*POneRecord;

class CTuopList :	public WContainerWidget
{
//MOC: W_OBJECT CTuopList:WContainerWidget
    W_OBJECT;
public:
    CTuopList(WContainerWidget *parent = 0);
	void refresh();

	~CTuopList(void);
public : //language;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;

	std::string strNameTest;
	WSignalMapper m_userMapper; 
	//WSignalMapper m_userMapper1;
	//WSignalMapper m_userMapper2;
	std::string strDel;
	bool bFirst;
	std::string strDelTip;
	std::string strEditTip;
	std::string strTuopTip;

	std::string strAllSel;
	std::string strAllNotSel;
	std::string strFanSel;
	std::string strDelete;

	std::string strNullList;
	std::string strDeleteType;
	string szButNum,szButMatch;
	string szSort;
	string szTuopDown;
	string szSortNum;
	string strRefresh;
	string strDelCon;
	string strSaveSort;
	string strReturnSave;

public:
	//WScrollArea * pUserScrollArea;
	//CMainTable *pMainTable;
	//CFlexTable *pUserTable;
	//WTable * pUserListTable;
	WLineEdit *pEditUserName; 

	WText * pCurrName;
	WLineEdit *pCurrEditUserName;

	WPushButton * pHideBtn;
	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;
	WApplication*  appSelf;


	WTable * pNullTable;


	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pTopologyListTable;

	//新增Sort功能的变量
	WTable * pSortListTable;
	WSVFlexTable * pSortTable;
    SVTable m_svSortList;

public:

	void ShowMainTable();
	std::list<string> ReadFileName(string path);
	std::list<string> ReadVSDName(string path);
	void AddColum( WTable* pContain );
	// 列表
	list<OneRecord> RecordList;
	//列表中的表项
	std::list<OneRecord>::iterator m_pRecordList;

	std::string bStrCurr ;

	void AddSortData(string strVsdName, int nRows, string strName, string strSort);
	void AddSortColum(WTable * pContain);


private slots:

	//MOC: SLOT CTuopList::EditUserName(const std::string strIndex)
    void EditUserName(const std::string strIndex);
	//MOC: SLOT CTuopList::OpenTuop(const std::string strTuop)
    void OpenTuop(const std::string strTuop);
	//MOC: SLOT CTuopList::SelAll()
    void SelAll();
	//MOC: SLOT CTuopList::SelNone()
	void SelNone();
	//MOC: SLOT CTuopList::SelInvert()
	void SelInvert();
	//MOC: SLOT CTuopList::BeforeDelUser()
	void BeforeDelUser();
    //MOC: SLOT CTuopList::DelUser()
    void DelUser(); 
	//MOC: SLOT CTuopList::EditReturn(int keyCode)
	void EditReturn(int keyCode);
	//MOC: SLOT CTuopList::Translate()
	void Translate();
	//MOC: SLOT CTuopList::ExChange()
	void ExChange();
	//MOC: SLOT CTuopList::Sort()
	void Sort();
	//MOC: SLOT CTuopList::SortOk()
	void SortOk();

	void ShowHelp();
};

