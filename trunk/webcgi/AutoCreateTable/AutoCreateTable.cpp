 /*****************************************************
 *
 *   ��ȡ���е�Monitor������Ӧ��Table
 *
 *****************************************************/

#include "stdafx.h"

//User Include 

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

int _tmain(int argc, _TCHAR* argv[])
{
	PAIRLIST AllMonitorList;
	PAIRLIST::iterator MonitorListRecord;
	bool GetMonitor = GetAllMonitorsInfo(AllMonitorList,"sv_monitortype") ;
	if(GetMonitor)
	{
		for(MonitorListRecord = AllMonitorList.begin();MonitorListRecord != AllMonitorList.end();MonitorListRecord++)
		{
			int typeValue = atoi(MonitorListRecord->value.c_str());
			bool bCreateTable = InsertTable(MonitorListRecord->name,typeValue);
		}
		AllMonitorList.clear();
	}

	//������־��
	bool bCreate = InsertTable("UserOperateLog",803);
	
	//�û������
	bCreate = InsertTable("UserHitLog",804);

	return 0;
}

