

#ifndef _SV_RETURN_PARAM_ITEM_H_
#define _SV_RETURN_PARAM_ITEM_H_

#pragma once

#include <string>
using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"

#include "basedefine.h"
#include "resstring.h"

struct sv_return_param_type
{
    sv_return_param_type()
    {
        m_szFloat = "float";
        m_szInt  = "int";
    };
    static string m_szFloat;
    static string m_szInt;
};

class SVReturnItem
{
public:
    SVReturnItem(MAPNODE node){enumAttrib(node);};
    ~SVReturnItem(){};
    const string getName(){return m_szName;};
    const string getType(){return m_szType;};
    const string getUnit(){return m_szUnit;};
    const string getLabel(){return m_szLabel;};
    bool isNumeric()
    {
        if(m_szType == m_svTypeList.m_szFloat || m_szType == m_svTypeList.m_szInt)
            return true;
        else
            return false;
    }
private:
    void enumAttrib(MAPNODE node)
    {
        FindNodeValue(node, svName, m_szName);                    // 名称
        FindNodeValue(node, svType, m_szType);                    // 类型

        if(FindNodeValue(node, svLabel, m_szLabel))              // 标签
            m_szLabel = SVResString::getResString(m_szLabel.c_str());

        FindNodeValue(node, svUnit, m_szUnit);          // 是否允许为空
    };
    string m_szName;
    string m_szType;
    string m_szUnit;
    string m_szLabel;
    sv_return_param_type m_svTypeList;
};

#endif
