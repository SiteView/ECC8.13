
#ifndef _SV_PREVIEW_H_
#define _SV_PREVIEW_H_

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include    "../../opens/libwt/WPushButton"
#include    "../../opens/libwt/WLineEdit"
#include    "../../opens/libwt/WTableCell"
#include    "../../opens/libwt/WTable"
#include "../../opens/libwt/WApplication"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>

using namespace std;

#include "../group/resstring.h"
#include "adddevice2nd.h"
#include "addmonitor2nd.h"


class CSVPreview : public WTable
{
    //MOC: W_OBJECT CSVPreview:WTable
    W_OBJECT;
public:
    CSVPreview(WContainerWidget *parent = NULL);
    virtual void refresh();
	WApplication *  appSelf;
private:
    SVDevice    *m_pDeviceShow;
    SVMonitor   *m_pMonitorShow;
};

#endif
