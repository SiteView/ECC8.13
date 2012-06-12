#pragma once
//////////////////////////
#include "WContainerWidget"
class WTable;
class WText;
class WCheckBox;
class WSVMainTable;
class WSVFlexTable;
class WLineEdit;
class WImage;
class WApplication;
///////////////////////////////////
#include "../../svdb/libutil/Time.h"
using namespace svutil;
////////////////////////////////////////
#include <string>
#include <list>
using namespace std;

class CLicense :	public WContainerWidget
{
public:
	//MOC: W_OBJECT CLicense:WContainerWidget
    W_OBJECT;
public:
    CLicense(WContainerWidget *parent = 0);
	~CLicense(void);
	virtual void refresh();

private :  //Var
	string strMainTitle;
	string strTitle;
	string strPointText;
	string strPointNum;
	string strPText;
	int strPNum;
	string strEquipText;
	string strEquipNum;
	string strEText;
	int strENum;
	string strDataText;
	string strDataNum;
	string strGeneral;
    int refreshCount;
	string strYear;
	string strMonth;
	string strDay;

private: //wt
	WSVMainTable *pMainTable;
	WSVFlexTable * pUserTable;
	WTable * pSubTable;
	WText * pBuyPText;
	WText * pEnablePText;
	WText * pBuyEText;
	WText * pEnableEText;
	WText * pDataText;

public: //wt
	WApplication*  appSelf;

private: //Func
	void ShowMainTable();
	void GetData();
	void InitTable(WTable * pContain);
	void GetEnityMonitorsCount(int *iEntityCount,int *iMonitorsCount);

private slots:
	//MOC: SLOT CLicense::Translate()
	void Translate();
	//MOC: SLOT CLicense::ExChange()
	void ExChange();
};
