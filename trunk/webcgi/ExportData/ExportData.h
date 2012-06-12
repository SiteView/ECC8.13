#pragma once

#include "WContainerWidget"
#include "WSignalMapper"
/////////////////////////////////
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class WComboBox;
class WLineEdit;
class WTable;
class WText;
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
using namespace std;

class CExportData :
	public WContainerWidget
{
	//MOC: W_OBJECT CExportData:WContainerWidget
    W_OBJECT;
public:
	CExportData(WContainerWidget *parent = 0);
	~CExportData(void);

private: //wt
	WSVMainTable * m_pMainTable;
	WSVFlexTable * m_pTimeTable;
	WSVFlexTable * m_pExportConfigTable;
	WSVFlexTable * m_pExportDataTable;
	WSignalMapper m_userMapper;
	WComboBox * m_pFileType;
	WLineEdit * m_pDriver;
	WLineEdit * m_pTime;
	WLineEdit * m_pServerName;
	WComboBox * m_pDBType;
	WLineEdit * m_pMacName;
	WLineEdit * m_pMacPWD;
	WLineEdit * m_pDBName;
	WLineEdit * m_pUserName;
	WLineEdit * m_pPWD;

private: //func
	void loadString();
	void initForm();

private slots:
	//MOC: SLOT CExportData::SaveTime()
	void SaveTime();
	//MOC: SLOT CExportData::ShowHideHelp()
	void ShowHideHelp();
	//MOC: SLOT CExportData::ExportData()
	void ExportData();
	//MOC: SLOT CExportData::ShowMac()
	void ShowMac();

private: //Var
	string m_szMainTitle;
	string m_szTimeTitle;
	string m_szConfigTitle;
	string m_szDataTitle;
	string m_szSave;
	string m_szExport;
	string m_szDataType;
	string m_szDataTypeHelp;
	string m_szDataTypeError;
	string m_szDataTypeConfig;
	string m_szDataTypeData;
	string m_szDriverName;
	string m_szDriverHelp;
	string m_szDriverError;
	string m_szServerName;
	string m_szServerNameHelp;
	string m_szServerNameError;
	string m_szDBType;
	string m_szDBTypeHelp;
	string m_szDBTypeError;
	string m_szServerUserName;
	string m_szServerUserNameHelp;
	string m_szServerUserNameError;
	string m_szServerPWD;
	string m_szServerPWDHelp;
	string m_szServerPWDError;
	string m_szDBUserName;
	string m_szDBUserNameHelp;
	string m_szDBUserNameError;
	string m_szDBPWD;
	string m_szDBPWDHelp;
	string m_szDBPWDError;
	string m_szDBName;
	string m_szDBNameHelp;
	string m_szDBNameError;
	string m_szExportSuccess;
	string m_szExportFail;
};
