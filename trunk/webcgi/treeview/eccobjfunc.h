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

// ���ݸ���ֹ״̬�����ӵĽ�ֹ״̬
bool saveDisableByParent(MAPNODE &mainnode, int nObjType, string szParentID);

static inline string getRefreshQueueName(const string &szIndex)
{
    string szQueueName("");;
    char szRefreshQueue[64] = {0};
    sprintf(szRefreshQueue, SV_REFRESH_QUEUE, FindSEID(szIndex).c_str());
    szQueueName = szRefreshQueue;
    return szQueueName;
}

// ���ɶ�����
static inline string makeQueueName()
{
    string szTime("");
    TTime curTime = TTime::GetCurrentTimeEx();
    char chTime[32] = {0};
    sprintf(chTime, "%d%d%d%d%d%d%d", getpid(), curTime.GetYear(), curTime.GetMonth(), 
        curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
    szTime =  chTime;
    return szTime;
}

// ���������޸Ķ�����
static inline string getConfigTrackQueueName(const string &szIndex)
{
    string szQueueName("");;
    char szRefreshQueue[64] = {0};
    sprintf(szRefreshQueue, SV_CONFIG_TRACK, FindSEID(szIndex).c_str());
    szQueueName = szRefreshQueue;
    return szQueueName;
}

// ���ɶ�̬���ӿ�����
string makeDllName(const string & szDll);

// ��̬���ݶ����ж�ȡ/д������
bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize);

// �ӻ�д�����ж�ȡ����
bool ReadFromRetQueue(const string &szQueue, char *pBuffer, int &nRetSize);

// �õ���ʹ�õ��豸����
int  getUsingNetworkCount(string szDeviceIndex = "");

// �õ���ʹ�õļ��������
int  getUsingMonitorCount();

// ��������豸�Ƿ񳬵�
bool checkNetworkPoint(int nNetworkCount);

// ��������Ƿ񳬵�
bool checkMonitorsPoint(int nMonitorsCount);

// ������Ƿ񱻽�ֹ
bool isDisable(const string &szID, int nType);

// �Ƿ���Զ�ָ���豸����ճ������
bool isCanBePasteDevice(const string &szID);

// ճ���豸
string PasteDevice(const string &szDestGroupID, const string &szSrcDevID);

// �����豸�����м�����ı�
void createAllTableOfDevice(const string &szDeviceIndex);

// �õ���������ͼ��������
string getMonitorNameMTID(const string &szMonitorID, int &nMTID);

// �������в���
string MakeRunParamStringByID(const string &szIndex, int nMTID);

// �����豸�����õ����в���
string enumDeviceRunParam(const string &szDeviceIndex);

// ��������б�
void AddTaskList(WComboBox * pTask = NULL);

#endif
