

#ifndef _SV_ECC_TREEVIEW_RES_STRING_H_
#define _SV_ECC_TREEVIEW_RES_STRING_H_

#pragma once

#include <map>
#include <string>

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"

class SVResString
{
public:
    // 构造函数
    SVResString(string szResLanguage = "default", string szAddr = "localhost");
    ~SVResString();                                                 // 析构函数
    static const string getResString(const char* pszResID);         // 根据资源ID得到字符串
    static const string getResString(const string &szResID);        // 根据资源ID得到字符串
    void ResetResoureType(string &szResLanguage, string &szAddr);   // 重置资源的语言和位置
    static SVResString      m_DefineOnce;
private:
    string      m_szResLanguage;                                    // 资源语言
    string      m_szResAddr;                                        // 读取资源位置
    // 资源字符串列表
    map<string, string, less<string> > m_lsResource;
    typedef     map<string, string, less<string> >::iterator    resItem;
    void        loadStrings();                                      // 加载资源字符串

    void        loadAddSVSEStrings(MAPNODE &objNode);               // 加载添加SE资源字符串
    void        loadAddGroupStrings(MAPNODE &objNode);              // 加载添加组资源字符串
    void        loadAddDeviceStrings(MAPNODE &objNode);             // 加载添加设备资源字符串
    void        loadAddMonitorStrings(MAPNODE &objNode);            // 加载添加监测器资源字符串

    void        loadBatchAddStrings(MAPNODE &objNode);              // 加载批量添加资源字符串

    void        loadConditionStrings(MAPNODE &objNode);             // 加载报警条件资源字符串
    void        loadTreeviewStrings(MAPNODE &objNode);              // 加载树显示资源字符串
    void        loadSVSEViewStrings(MAPNODE &objNode);              // 加载SE 视图显示资源字符串
    void        loadGroupviewStrings(MAPNODE &objNode);             // 加载组视图显示资源字符串
    void        loadMonitorviewStrings(MAPNODE &objNode);           // 加载监测器视图显示资源字符串
    void        loadSortStrings(MAPNODE &objNode);                  // 加载排序操作资源字符串

    void        loadGeneralStrings(MAPNODE &objNode);               // 加载通用资源字符串

    const string getStringFromRes(const char* pszResID);

    OBJECT      m_objRes;
};

#endif
