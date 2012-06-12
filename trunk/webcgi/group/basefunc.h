#ifndef _SV_TREEVIEW_BASE_FUNC_H_
#define _SV_TREEVIEW_BASE_FUNC_H_

#include <string>
#include <list>

#pragma once

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

#include "../demotreeview/define.h"
#include "../../kennel/svdb/libutil/time.h"

#include "../userright/user.h"
#include "../base/basetype.h"

//const char sv_devicedisable[] = "设备被禁止<BR>";
const char SV_REFRESH_QUEUE[] = "SiteView70_RefreshInfo_%s";
const char SV_CONFIG_TRACK[]  = "SiteView70-ConfigTrack_%s";
const char SV_USER_OPERATE_LOG_TABLE[] = "UserOperateLog";
const char sv_disable_end[] = "DISABLE_END";
const char svPassword[] = "password";
const char svText[]    = "text";
const char svTextbox[] = "textbox";
const char svCheckBox[] = "checkbox";
const char svRadioBox[] = "radiobox";
const char svTextArea[] = "textarea";
const char svComboBox[] = "combobox";
const char svListBox[] = "listbox";
const char svTree[]    = "tree";
const char svButton[]  = "button";

const char chLeftBracket = '[';
const char chRightBracket = ']';

const int  svBufferSize = 1024 * 10;
const int  svMax_Size = 256;

struct sv_device_state
{
    sv_device_state()
    {
        nState = 1;
        nMonitorCount = 0;
        nErrorCount = 0;
        nWarnCount  = 0;
        nDisableCount = 0;
        pszDeviceType = NULL;
        pszOSName = NULL;
    };
    sv_device_state(const struct sv_device_state &devState)
    {
        nState = devState.nState;
        nDisableCount = devState.nDisableCount;
        nMonitorCount = devState.nMonitorCount;
        nErrorCount = devState.nErrorCount;
        nWarnCount  = devState.nWarnCount;
        if(devState.pszDeviceType)
        {
            pszDeviceType = new char[strlen(devState.pszDeviceType) + 1];
            strcpy(pszDeviceType, devState.pszDeviceType);
        }
        else
        {
            pszDeviceType = NULL;
        }
        if(devState.pszOSName)
        {
            pszOSName = new char[strlen(devState.pszOSName) + 1];
            strcpy(pszOSName, devState.pszOSName);
        }
        else
        {
            pszOSName = NULL;
        }
    };
    ~sv_device_state()
    {
        if(pszDeviceType)
            delete []pszDeviceType;
        pszDeviceType = NULL;
        if(pszOSName) 
            delete []pszOSName;
        pszOSName = NULL;
    };
    const struct sv_device_state &operator=(const struct sv_device_state &devState)
    {
        nState = devState.nState;
        nDisableCount = devState.nDisableCount;
        nMonitorCount = devState.nMonitorCount;
        nErrorCount = devState.nErrorCount;
        nWarnCount  = devState.nWarnCount;
        if(devState.pszDeviceType)
        {
            char *pszTemp = pszDeviceType;
            pszDeviceType = new char[strlen(devState.pszDeviceType) + 1];
            strcpy(pszDeviceType, devState.pszDeviceType);
            delete []pszTemp;
        }
        else
        {
            if(pszDeviceType)
                delete []pszDeviceType;
            pszDeviceType = NULL;
        }
        if(devState.pszOSName)
        {
            char *pszTemp = pszOSName;
            pszOSName = new char[strlen(devState.pszOSName) + 1];
            strcpy(pszOSName, devState.pszOSName);
            delete pszTemp;
        }
        else
        {
            if(pszOSName)
                delete []pszOSName;
            pszOSName = NULL;
        }
        return *this;
    }
    void reset()
    {
        nState = 1;
        nMonitorCount = 0;
        nDisableCount = 0;
        nErrorCount = 0;
        nWarnCount  = 0;
        if(pszDeviceType)
            delete []pszDeviceType;
        pszDeviceType = NULL;
        if(pszOSName) 
            delete []pszOSName;
        pszOSName = NULL;
        svutil::TTime tmpTime;
        m_time = tmpTime;
    };
    int nState;
    int nDisableCount;
    int nMonitorCount;
    int nErrorCount;
    int nWarnCount;
    char *pszDeviceType;
    char *pszOSName;
    svutil::TTime m_time;
};

struct sv_group_state
{
    sv_group_state()
    {
        nState = 1;
        nDisableCount = 0;
        nDeviceCount = 0;
        nMonitorCount = 0;
        nErrorCount = 0;
        nWarnCount  = 0;
    };
    void reset()
    {
        nState = 1;
        nDisableCount = 0;
        nMonitorCount = 0;
        nErrorCount = 0;
        nWarnCount  = 0;
        svutil::TTime tmpTime;
        m_time = tmpTime;
    };
    int nState;
    int nDisableCount;
    int nDeviceCount;
    int nMonitorCount;
    int nErrorCount;
    int nWarnCount;
    svutil::TTime m_time;
};

struct base_param
{
    string szIndex;
    string szName;
};

enum sv_disable_state
{
    sv_enable_state,
    sv_disable_state,
    sv_time_state
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../opens/boost/lexical_cast.hpp"
#include "../../kennel/svdb/libutil/Time.h"

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

static inline string getConfigTrackQueueName(const string &szIndex)
{
    string szQueueName("");;
    char szRefreshQueue[64] = {0};
    sprintf(szRefreshQueue, SV_CONFIG_TRACK, FindSEID(szIndex).c_str());
    szQueueName = szRefreshQueue;
    return szQueueName;
}

static inline string getRefreshQueueName(const string &szIndex)
{
    string szQueueName("");;
    char szRefreshQueue[64] = {0};
    sprintf(szRefreshQueue, SV_REFRESH_QUEUE, FindSEID(szIndex).c_str());
    szQueueName = szRefreshQueue;
    return szQueueName;
}

static inline string makeQueueName()
{
    string szTime("");
    svutil::TTime curTime = svutil::TTime::GetCurrentTimeEx();
    char chTime[32] = {0};
    sprintf(chTime, "%d%d%d%d%d%d%d", getpid(), curTime.GetYear(), curTime.GetMonth(), 
        curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
    szTime =  chTime;
    return szTime;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 拆分
int  sv_split(const char* str, const char* delim, list<string>& results, bool empties = true);

// 得到指定列表内的监测点数
int  getMonitorCountInList(list<string> &lsMonitors, string szIDCUser = "default", string szIDCPwd = "localhost");

// 得到已使用的设备总数
int  getUsingNetworkCount(string szIDCUser = "default", string szIDCPwd = "localhost", string szDeviceIndex = "");

// 得到已使用的监测器点数
int  getUsingMonitorCount(string szIDCUser = "default", string szIDCPwd = "localhost");

// 根据父禁止状态决定子的禁止状态
bool saveDisableByParent(MAPNODE &mainnode, int nObjType, string szParentID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 检查网络设备是否超点
bool checkNetworkPoint(int nNetworkCount);

// 检查监测器是否超点
bool checkMonitorsPoint(int nMonitorsCount);

// 监测器是否被禁止
bool isMonitorDisable(string &szMonitorID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 得到操作符号位置
unsigned getOperatePostion(string s, list<string> lstOperate, string &szCondition);

// 得到连接符号
unsigned getCondition(list<string>& lst, string s);

// 得到参数
unsigned getParam(list<string>&lst, string s);

// 根据监测器模板得到监测器模板的名称
string getMonitorNameMTID(string &szMonitorID, int &nMTID, string szIDCUser = "default", string szIDCPwd = "localhost");

string getDeviceNameByID(string szDeviceID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 根据组索引得到组名称
string getGroupNameByID(string szGroupID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 根据设备类型得到设备模板类型显示文字
string getDeviceNameByType(string szDeviceType, string szIDCUser = "default", string szIDCPwd = "localhost");

//
string makePath(string szIndex, string szIDCUser = "default", string szIDCPwd = "localhost");

// 根据设备索引得到设备的类型
string GetDeviceTypeById(string &szDeviceID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 组是否被禁止
int isGroupDisable(string &szGroupID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 设备是否被禁止
int isDeviceDisable(string &szDeviceID, string szIDCUser = "default", string szIDCPwd = "localhost");

// 得到设备状态
void getDeviceState(string szDeviceIndex, sv_device_state &devState, string szIDCUser = "default", string szIDCPwd = "localhost");

// 得到组状态
sv_group_state getGroupState(string szGroupIndex, CUser *pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");

// 得到 SE 状态
sv_group_state getSVSEState(string szSVSEIndex = "1", CUser *pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");

// 得到组简单状态
int getDeviceSimpleState(string szDeviceIndex, string szIDCUser = "default", string szIDCPwd = "localhost");

// 去掉字符串左空格
string strtriml(const char * str1);

// 去掉字符串右空格
string strtrimr(const char * str1);

// 编码
string url_Encode(const char* pszValue);

string makeDllName(const string & szDll);

bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize, string szIDCUser = "default", string szIDCPwd = "localhost");

bool ReadFromRetQueue(const string &szQueue, char *pBuffer, int &nRetSize, string szIDCUser = "default", string szIDCPwd = "localhost");
// 
char *buildbuf(string szData, char *pt, int &nBuflen);

// 记录日志
void DumpLog(const char * pszFileName, const char *pBuffer, const int nLen);

void createAllTableOfDevice(string &szDeviceIndex, string szIDCUser = "default", string szIDCPwd = "localhost");

#endif
