//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_ALERT_EVENT_H_
#define _SV_ALERT_EVENT_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std
#include <iostream>
#include <string>
#include <list>
using namespace std;

class CAlertEventObj
{
	public :
		CAlertEventObj();
	
	public :
		string strMonitorId;
		string strEventDes;
		string strTime;
		int nEventType; //1��������2��Σ�ա�3������4����ֹ��5������
		int nEventCount;

		string strMonitorName;
		string strEntityId;
		string strEntityName;
		string strEntityMachineName;

	public :
		inline string GetEventTypeString()
		{
			string strType = "";
			switch(nEventType)
			{
				case 1 :
					strType = "����";
					break;
				case 2 :
					strType = "Σ��";
					break;
				case 3 :
					strType = "����";
					break;
				case 4 :
					strType = "��ֹ";
					break;
				case 5 :
					strType = "����";
					break;
				default:
					break;
			}

			return strType;
		}

		inline string GetDebugInfo()
		{
			string strDebugInfo = "";
			strDebugInfo += "\r\n------------------�����¼���Ϣ��ʼ-----------------------------\r\n";
			strDebugInfo += ("�����Id��" + strMonitorId + "\r\n");
			strDebugInfo += ("�¼����ͣ�" + GetEventTypeString() + "\r\n");
			char chItem[32]  = {0};	
			sprintf(chItem, "%d", nEventCount);
			string strCount = chItem;
			strDebugInfo += ("�¼�������" + strCount + "\r\n");
			strDebugInfo += ("�¼�������" + strEventDes + "\r\n");		
			strDebugInfo += ("�¼�����ʱ�䣺" + strTime + "\r\n");		
			
			strDebugInfo += "------------------�����¼���Ϣ����------------------------------\r\n";			
			return strDebugInfo;
		}

};
#endif