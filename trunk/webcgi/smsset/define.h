

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
	string chgstr;
	string szTemplet;
    public:
        _SAVE_PHONE_LIST() { nIndex = -1 ;};
}SAVE_PHONE_LIST;

#endif