

#ifndef _SV_SMS_SET_DEFINES_H_
#define _SV_SMS_SET_DEFINES_H_

#include <string>
using namespace std;

typedef struct _SAVE_PHONE_LIST
{
	string id;
	int nIndex;
	string szName;
	string szPhone;
	string szPlan;
	bool bDisable;
    public:
        _SAVE_PHONE_LIST() { nIndex = -1 ;};
}SAVE_PHONE_LIST;

typedef struct _SAVE_REPORT_LIST
{
	string chgstr;
	string szGroupRight;
	string szTitle;
	string szDescript;
	string szPeriod;
	string szStatusresult;
	string szErrorresult;
	string szGraphic;
	string szComboGraphic;
	string szListData;
	string szListNormal;
	string szListError;
	string szListDanger;
	string szListAlert;
	string szEmailSend;
	string szParameter;
	string szDeny;
	string szGenerate;
	string szClicket;
	string szClicketValue;
	string szPlan;
	string szListClicket;
	string szStartTime;
	string szEndTime;
	string szCreateTime;
	//Ticket #123  start   -------ку╨о
	string szExcel;
  //Ticket #123   end    -------ку╨о
	int    nWeekEndIndex;
}SAVE_REPORT_LIST;

typedef enum 
{
	Se = 1, Group2 = 2, Deveice = 3
}
NodeType;

typedef enum 
{
	Add = 1, Edit = 2, Delete = 3, Enable = 4, Disable = 5, Run = 6, Refresh = 7, Click = 8
}
OperateCode;

typedef struct _MENU_REQUEST 
{
    std::string strNodeId;
	NodeType nNodeType;
	OperateCode nOperatCode;
}
MENU_REQUEST, *LMENU_REQUEST;

typedef struct _MENU_RESPONSE 
{
    std::string strNodeId;
	NodeType nNodeType;
	OperateCode nOperatCode;
	bool bSucess;
	std::string strErrorMsg;
}
MENU_RESPONSE, *LMENU_RESPONSE;


#endif