
#ifndef _SV_MONITOR_STATE_H_
#define _SV_MONITOR_STATE_H_

#pragma once

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"

#include <string>
using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"

class CSVStateDesc : public WTable
{
    //MOC: W_OBJECT CSVStateDesc:WTable
    W_OBJECT;
public:
    CSVStateDesc(WContainerWidget * parent = NULL);
private:
    //string m_szErrDesc;           // ´íÎóÃèÊö
    //string m_szWarnningDesc;      // ¾¯¸æÃèÊö
    //string m_szNormalDesc;        // Õı³£ÃèÊö
    //string m_szNoDataDesc;        // ÎŞ¼à²âÊı¾İÃèÊö
    //string m_szDisableDesc;       // ½ûÖ¹ÃèÊö
    //string m_szStatesDesc;        // ×´Ì¬ÃèÊö 

    //void loadString();
    void initForm();
};

#endif

