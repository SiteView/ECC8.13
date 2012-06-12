#ifndef _SiteView_Ecc_Object_Base_Func_H_
#define _SiteView_Ecc_Object_Base_Func_H_

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

#include<string>

using namespace std;

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include "basedefine.h"

class WComboBox;

// 根据父禁止状态决定子的禁止状态
bool saveDisableByParent(MAPNODE &mainnode, int nObjType, string szParentID);

static inline string getRefreshQueueName(const string &szIndex)
{
    string szQueueName("");;
    char szRefreshQueue[64] = {0};
    sprintf(szRefreshQueue, SV_REFRESH_QUEUE, FindSEID(szIndex).c_str());
    szQueueName = szRefreshQueue;
    return szQueueName;
}

// 生成队列名
static inline string makeQueueName()
{
    string szTime("");
     TTime curTime =  TTime::GetCurrentTimeEx();
    char chTime[32] = {0};
    sprintf(chTime, "%d%d%d%d%d%d%d", getpid(), curTime.GetYear(), curTime.GetMonth(), 
        curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
    szTime =  chTime;
    return szTime;
}

// 生成配置修改队列名
static inline string getConfigTrackQueueName(const string &szIndex)
{
    string szQueueName("");;
    char szRefreshQueue[64] = {0};
    sprintf(szRefreshQueue, SV_CONFIG_TRACK, FindSEID(szIndex).c_str());
    szQueueName = szRefreshQueue;
    return szQueueName;
}

// 生成动态链接库名称
string makeDllName(const string & szDll);

// 向动态数据队列中读取/写入数据
bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize);

// 从回写队列中读取数据
bool ReadFromRetQueue(const string &szQueue, char *pBuffer, int &nRetSize);

// 得到已使用的设备总数
int  getUsingNetworkCount(string szDeviceIndex = "");

// 得到已使用的监测器点数
int  getUsingMonitorCount();

// 检查网络设备是否超点
bool checkNetworkPoint(int nNetworkCount);

// 检查监测器是否超点
bool checkMonitorsPoint(int nMonitorsCount);

// 监测器是否被禁止
bool isDisable(const string &szID, int nType);

// 是否可以对指定设备进行粘贴操作
bool isCanBePasteDevice(const string &szID);

// 粘贴设备
string PasteDevice(const string &szDestGroupID, const string &szSrcDevID);

// 创建设备下所有监测器的表
void createAllTableOfDevice(const string &szDeviceIndex);

// 得到监测器名和监测器类型
string getMonitorNameMTID(const string &szMonitorID, int &nMTID);

// 生成运行参数
string MakeRunParamStringByID(const string &szIndex, int nMTID);

// 根据设备索引得到运行参数
string enumDeviceRunParam(const string &szDeviceIndex);

// 添加任务列表
void AddTaskList(WComboBox * pTask = NULL);

#endif
