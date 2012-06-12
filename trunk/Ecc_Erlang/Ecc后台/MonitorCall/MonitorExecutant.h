#ifndef  DRAGONFLOW_MONITOREXECUTANT_H
#define DRAGONFLOW_MONITOREXECUTANT_H

#include "Monitor.h"
#include "Option.h"
#include "ReturnValue.h"
#include <libutil/buffer.h>
#include "Entity.h"
#include "LoadConfig.h"

#define		RETBUFCOUNT		(10*1024)
#define		INBUFCOUNT		(1024*2)
#define		SEPARATOR		'#'

using namespace svutil;

typedef BOOL(GatherData)(CStringList&, char*);
typedef bool (*LPFUNC)(const char *,char *,int &);

class QueuesManager; 

class MonitorExecutant
{
public:
	MonitorExecutant(void);
	~MonitorExecutant(void);
	void ExecuteMonitor();
	bool InitSocket(void);
	Option *m_pOption;
	enum{ retcount=5 };
	enum{
		Normal=0x1,
		Warning,
		Error,
	};
private:
	CTime m_StartTime;
	CString m_strDisplay;
	int m_nRunCount;
	int m_MonitorState;
	CReturnValueList m_RetValueList;
	char m_RetBuf[RETBUFCOUNT];
	svutil::buffer m_InBuf;
	ReturnValue m_RetValues[retcount];
	int	m_RetValueCount;
	STRINGMAP m_RVmap;
	LoadConfig m_lc;
	Groups * m_pGroups;
	QueuesManager *m_pTaskQueueManager;
protected:
	void RunMonitor(void);
	Monitor *m_Monitor;	
	Subsequent * m_pSub;
public:
	void SetMonitor(Monitor * pMonitor);
protected:
	bool RunInProcess(int iLen, string dllname, string funname);
private:
	BOOL PaserResultV70(void);
	void ParserMonitorState(void);
	void ProcessResultV70(void);
	void ClearResult(void);
	bool BulidStringMap(STRINGMAP & map, const char * buf);
	BOOL CheckStateByType(int Type);
	int ParserExpression(CString strExpression, CStringList & lstOperator, CStringList & lstID);
	BOOL CheckSingleItemState(StateCondition *pSt ,int ItemID);
	BOOL Judge(const char *szSource, const char *szDestination, const char *szRelation);
	int MakeInBuf(void);
public:
	void AdjustRetByMonitor(Monitor *pMonitor, bool isA);
	BOOL CheckTaskQueueByMonitor(Monitor *pMonitor);
	BOOL Init(void);
	bool LoadPreLibrary(void);
	Groups *GetGroups(void)
	{
		return m_pGroups;
	}
	Subsequent* GetSubsequtent(void)
	{
		return m_pSub;
	}
	bool CheckSubsequent(Monitor * pMonitor, bool & bTotal, bool & bPer);
};

#endif