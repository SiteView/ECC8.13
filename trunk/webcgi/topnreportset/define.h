

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
	string szTitle;
	string szDescript;
	string szPeriod;
	string szEmailSend;
	string szParameter;
	string szDeny;
	string szGenerate;

	string szSelType;
	string szSelMark;
	string szSelSort;
	string szCount;
	string szGroupRight;
	string szPlan;
	string szGetValue;
	string szWeekEnd;
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