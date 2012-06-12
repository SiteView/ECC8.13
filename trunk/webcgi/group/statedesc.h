
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
    //string m_szErrDesc;           // ��������
    //string m_szWarnningDesc;      // ��������
    //string m_szNormalDesc;        // ��������
    //string m_szNoDataDesc;        // �޼����������
    //string m_szDisableDesc;       // ��ֹ����
    //string m_szStatesDesc;        // ״̬���� 

    //void loadString();
    void initForm();
};

#endif

