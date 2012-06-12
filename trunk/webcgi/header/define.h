#ifndef DEFINE_H_
#define DEFINE_H_

#include <string>
using namespace std;
#include "../base/basetype.h"

typedef enum SV_Tree_OperateCode
{
    SV_ADD = 0x011,
	SV_ADD_GROUP = 0x020,
	SV_ADD_DEVICE = 0x021,
	SV_ADD_MONITOR = 0x022,
    SV_EDIT = 0x012, 
    SV_DELETE = 0x013, 
    SV_ENABLE = 0x014, 
    SV_DISABLE = 0x015, 
    SV_RUN = 0x016, 
    SV_REFRESH = 0x017, 
    SV_CLICK = 0x018, 
    SV_SORT = 0x019,
    SV_COLLAPSE = 0x01A,
    SV_COPY = 0x01B,
    SV_PAST = 0x01C
};

typedef struct _MENU_REQUEST 
{
    std::string                 strNodeId;
	std::string                 strParentNodeId;
	int                         nNodeType;
	int                         nOperatCode;
}
MENU_REQUEST, *LMENU_REQUEST;

typedef struct _MENU_RESPONSE 
{
    std::string             strNodeId;
	std::string             strParentNodeId;
	int                     nNodeType;
	int                     nOperatCode;
	bool                    bSucess;
	std::string             strErrorMsg;
    std::string             strName;
}
MENU_RESPONSE, *LMENU_RESPONSE;

#endif
