#ifndef  DRAGONFLOW_QUEUESMANAGER
#define DRAGONFLOW_QUEUESMANAGER

#include "MonitorCall.h"

#include "QueueItem.h"
#include "monitorexecutant.h"

#define		MAXQUEUE	100


class QueuesManager
{
public:
	void ListAllQueueInfo(void);
	BOOL Push(Monitor *pMonitor,BOOL isTail=TRUE);
	Monitor* Pop(int QueueIndex);
	BOOL Push(Monitor *pMonitor,int QueueIndex,BOOL isTail);
	Monitor* Pop(const char *ClassName);
	int GetQueueIndexByClass(const char *ClassName);
	BOOL Push(Monitor *pMonitor,const char *ClassName,BOOL isTail=TRUE);
	BOOL Init(void);
	QueuesManager();
	QueuesManager(MonitorExecutant *pExecutant)
	{
		m_nQueueCount=0;
		for(int i=0;i<MAXQUEUE;i++)
			m_Queue[i]=NULL;
		
		m_pExecutant=pExecutant;
	}
	virtual ~QueuesManager();
	void SetSchMain(MonitorExecutant *pExecutant)
	{
		m_pExecutant=pExecutant;
	}

    int	GetQueueCount(void)
	{
		return m_nQueueCount;
	}

private:
	BOOL CreateMainQueue(void);
	BOOL CreateQueueBySubsequent(void);
	MonitorExecutant * m_pExecutant;
	QueueItem * m_Queue[MAXQUEUE];
	int m_nQueueCount;
};

#endif
