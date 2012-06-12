#pragma once

#include "WContainerWidget"
/////////////////////////////////
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
class WLineEdit;
class WFileUpload;
class WCheckBox;
class WTable;
class WText;
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
using namespace std;

extern int main1(int argc, char *argv[]);

class CBackupRestore :
	public WContainerWidget
{
	//MOC: W_OBJECT CBackupRestore:WContainerWidget
    W_OBJECT;
public:
	CBackupRestore(WContainerWidget *parent = 0);
	~CBackupRestore(void);

private slots:
	//MOC: SLOT CBackupRestore::Backup()
	void Backup();
	//MOC: SLOT CBackupRestore::BackupData()
	void BackupData();
	//MOC: SLOT CBackupRestore::Restore()
	void Restore();
	//MOC: SLOT CBackupRestore::ShowHideHelp()
	void ShowHideHelp();
	//MOC: SLOT CBackupRestore::trueRestore()
	void trueRestore();

private: //func
	void loadString();
	void initForm();

private: //wt
	WSVMainTable * m_pMainTable;
	WSVFlexTable * m_pBackupTable;
	WSVFlexTable * m_pRestoreTable;
	WCheckBox * m_pConfig;
	WCheckBox * m_pData;
	WLineEdit * m_pBackFileName;
	WLineEdit * m_pHideEdit;
	WFileUpload * m_pFile;
	WSVButton * m_pBtnHide;

private: // var
	string m_szMainTitile;
	string m_szBackupData;
	string m_szRestoreData;
	string m_szBackupName;
	string m_szBackupHelp;
	string m_szBackupError;
	string m_szRes;
	string m_szRestore;
	string m_szRestoreName;
	string m_szRestoreHelp;
	string m_szRestoreError;
	string m_szFileName;
	string m_szButNum;
	string m_szButMatch;
	string m_szAffirmRestore;
	string m_szRestoreSucc;
	string m_szDownLoad;
	string m_szConfirm;
	string m_szConfigFile;
	string m_szMonitorData;
};
