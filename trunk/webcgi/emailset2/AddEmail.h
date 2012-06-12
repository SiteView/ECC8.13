//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_ADD_EMAIL_H_
#define _SV_ADD_EMAIL_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// includ WT lib

#include <WContainerWidget>
#include <WPushButton>
#include <WLineEdit>
#include <WCheckBox>
#include <WComboBox>
#include <WTextArea>
#include <WText>
#include <WImage>
#include <WTable>
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>
#include <list>


#include "defines.h"

using namespace std;

extern void PrintDebugString(const char *szErrmsg);

class CTaskList;
class CFlexTable;
class CMainTable;
class WSVMainTable;
class WSVFlexTable;

//////////////////////////////////////////////////////////////////////////////////
// class CSVEmailSet
class CSVAddEmail : public WContainerWidget
{
    //MOC: W_OBJECT CSVAddEmail:WContainerWidget
    W_OBJECT;
public:
    CSVAddEmail(WContainerWidget *parent = 0);
    void clearContent();
    void UpdateData(ADD_MAIL_OK addMail);
public signals:
    //MOC: EVENT SIGNAL CSVAddEmail::Successful(ADD_MAIL_OK)
    void Successful(ADD_MAIL_OK addMail);
    //MOC: EVENT SIGNAL CSVAddEmail::BackMain()
    void BackMain();
    //MOC: EVENT SIGNAL CSVAddEmail::ExChangeEventAdd()
    void ExChangeEventAdd();
private slots:
    //MOC: SLOT CSVAddEmail::Save()
    void Save();
    //MOC: SLOT CSVAddEmail::Back()
    void Back();
	//MOC: SLOT CSVAddEmail::Translate()
	void Translate();
	//MOC: SLOT CSVAddEmail::ExChangeAdd()
	void ExChangeAdd();
	void ShowHelp();
private:
    void showMainForm();
    bool checkEmail();
	 
private:
	//cxy change 5 30
	WSVMainTable * pMainTable;
	WSVFlexTable * m_pAddTable;

	WTable * m_pGeneralTable;
	WTable * m_pAdvanceTable;		

	WPushButton *pTranslateBtn;
	WPushButton *pExChangeBtn;


	std::list<string> tasknamelist;
	std::list<string>::iterator taskname;	

    WCheckBox * m_pDisable;
    WLineEdit * m_pName;
    WLineEdit * m_pMailList;

	bool bEditAdd;
	std::string strTypeAdd;
	std::string strTypeEdit;
	std::string strEmailSet;

	string strCancelAdd;
	string strSaveEmail;

	WComboBox * m_pTemplate;
	WComboBox * m_pSchedule;
	WTextArea * m_pDesciption;

	//CTaskList * m_pTasklist;
    int m_nIndex ;
	string strSave,strCancel;
    //WText * m_pErrMsg;
    typedef struct _FORM_SHOW_TEXT
    {
		string szTitle; 

		string szName;
		string szDisable;
        string szTemplate; 
		string szMail;
        string szSchedule;
		string szDesciption;

		string szNameDes;
		string szDisableDes;
        string szTemplateDes; 
		string szMailDes;
        string szScheduleDes;
		string szDesciptionDes;
		
		string szGenTitle;
		string szAdvTitle;
        string szErrName;
		string szErrName1;
		string szErrMail;
		string szReturn;

		string szEditName;
    }SHOW_TEXT;
    SHOW_TEXT m_formText;
};

#endif

// end class
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// end file