#ifndef _SV_GENERAL_H_
#define _SV_GENERAL_H_

#pragma once

#include <string>
#include <list>

using namespace std;

#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"

#include "showtable.h"

class SVGeneral : public WContainerWidget
{
    //MOC: W_OBJECT SVGeneral:WContainerWidget
    W_OBJECT;
public:
    SVGeneral(WContainerWidget *parent = NULL);
    void setDescription(string &szDesc);
    void setState(string &szState);
    void setState();
    void setTitle(string &szGroupName);

    int m_nDeviceCount;
    int m_nMonitorCount;
    int m_nMonitorErrCount;
    int m_nMonitorWarnCount;
    int m_nMonitorDisableCount;
    string  m_szAdvState;
    WTable * getSubTable()
    {
        if(m_pStandard)
            return m_pStandard->createSubTable();
        else
            return NULL;
    }

private slots:
private:
    //string m_szDesc;
    //string m_szState;
    //string m_szName;
    //string m_szGeneralTitle;
    WText *  m_pName;
    WText *  m_pDescription;
    WText *  m_pStateInfo;
    SVShowTable * m_pStandard;

    //void loadString();
    void initForm();
    
    //string        m_szDeviceCount;
    //string        m_szMonitorCount;
    //string        m_szMonitorError;
    //string        m_szMonitorWarn;
    //string        m_szMonitorDisable;
};

#endif
