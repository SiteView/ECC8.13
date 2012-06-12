
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

class CEccStateDesc : public WTable
{
    //MOC: W_OBJECT CEccStateDesc:WTable
    W_OBJECT;
public:
    CEccStateDesc(WContainerWidget * parent = NULL);
private:
    void initForm();
};

#endif

