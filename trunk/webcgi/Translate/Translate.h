#pragma once

#include "WContainerWidget"
class CAnswerTable;
class CMainTable;
class WTable;
class CFlexTable;
class WApplication;
#include "..\svtable\SVTable.h"
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WPushButton;
#include "WSignalMapper"
#include <list>
#include <vector>

using namespace std;

class CTranslate :	public WContainerWidget
{
//MOC: W_OBJECT CTranslate:WContainerWidget
    W_OBJECT;
public:
	CTranslate(WContainerWidget *parent = 0);
	~CTranslate(void);

private: 
	//WScrollArea * pUserScrollArea;
	WSignalMapper m_userMapper; 
	CAnswerTable * pMainTable;
	WTable * pUserListTable;
	SVTable m_pList;
	WLineEdit * m_pEditValue;
	SVTableCell * pEditCell;
public:

	void ShowMainTable();
	void AddColum( WTable* pContain );
	void AddValue( WTable* pContain,const string filename );
	void AddDeviceList( WTable* pContain,const string deviceid );
	void AddMonitorList( WTable* pContain,const string monitorid );
	void refresh();
private: //User Var
	string strIDSList; 
	string strFileName;
	string strIDSName;
	string strEditTip;
	int iLanguCount;
	int DefaultLanguCol;
	string DefaultLangu;
	int iRefresh;
	bool bState;
	WTable * pTempTable;
	string strEditName;
	string strTitle;
private slots:
	//MOC: SLOT CTranslate::EditIDSValue(const std::string strValue)
    void EditIDSValue(const std::string strValue);
	//MOC: SLOT CTranslate::EditReturn(int keyCode)
	void EditReturn(int keyCode);
};
