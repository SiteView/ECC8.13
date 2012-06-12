#include "OperateLog.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

#include <string>
#include <vector>
//
using namespace std;
using namespace svutil;

OperateLog::OperateLog()
{
	loadString();
	OperateTypeInit();
	OperateObjNameInit();
}
OperateLog::~OperateLog()
{
}
//������������
void OperateLog::OperateTypeInit()
{
	string strType[10] = {"", "", "", "", "",
                          "", "", "", "", ""};
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Login",strType[0]);				//��¼
			FindNodeValue(ResNode,"IDS_Add_Title",strType[1]);			//���
			FindNodeValue(ResNode,"IDS_Edit",strType[2]);				//�༭
			FindNodeValue(ResNode,"IDS_Delete",strType[3]);				//ɾ��
			FindNodeValue(ResNode,"IDS_Enable",strType[4]);				//����
			FindNodeValue(ResNode,"IDS_Disable",strType[5]);			//��ֹ
			FindNodeValue(ResNode,"IDS_Batch_Add",strType[6]);			//�������
			FindNodeValue(ResNode,"IDS_Quick_Add",strType[7]);			//�������
			FindNodeValue(ResNode,"IDS_Depends_On",strType[8]);			//����
			FindNodeValue(ResNode,"IDS_Event_Confirm",strType[9]);      //�¼�ȷ��
		}
		CloseResource(objRes);
	}                          
    for(int i = 0; i < 10; i++)
        if(!strType[i].empty())
            vOperateType.push_back(strdup(strType[i].c_str()));
}
//����������������
void OperateLog::OperateObjNameInit()
{
    string strObjName[18] = {"", "", "", "", "",
                             "", "", "", "", "",
                             "", "", "", "", "",
                             "", "", ""};
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_System",strObjName[0]);						//��¼
			FindNodeValue(ResNode,"IDS_SE",strObjName[1]);							//SE
			FindNodeValue(ResNode,"IDS_Group",strObjName[2]);						//��
			FindNodeValue(ResNode,"IDS_Device",strObjName[3]);						//�豸
			FindNodeValue(ResNode,"IDS_Monitor_Title",strObjName[4]);				//�����
			FindNodeValue(ResNode,"IDS_General_MainTitle",strObjName[5]);			//��������
			FindNodeValue(ResNode,"IDS_Customer_Name",strObjName[6]);				//�ͻ�����
			FindNodeValue(ResNode,"IDS_Monitor_Server_Name",strObjName[7]);			//������������
			FindNodeValue(ResNode,"IDS_Alert_Rule",strObjName[8]);					//��������
			FindNodeValue(ResNode,"IDS_Tuopu",strObjName[9]);						//������ͼ
			FindNodeValue(ResNode,"IDS_SysLogSetting",strObjName[10]);				//SysLog����
			FindNodeValue(ResNode,"IDS_User_Manage",strObjName[11]);				//�û�����
			FindNodeValue(ResNode,"IDS_Email_Set",strObjName[12]);					//�ʼ�����
			FindNodeValue(ResNode,"IDS_Time_Area_Task_Plan",strObjName[13]);		//ʱ�������ƻ�
			FindNodeValue(ResNode,"IDS_Time_Task_Plan",strObjName[14]);				//����ʱ������ƻ�
			FindNodeValue(ResNode,"IDS_SMS_Config",strObjName[15]);					//��������
			FindNodeValue(ResNode,"IDS_TopN_Report",strObjName[16]);				//TopN����
			FindNodeValue(ResNode,"IDS_Total_Report",strObjName[17]);				//ͳ�Ʊ���
		}
		CloseResource(objRes);
	}
    for(int i = 0; i < 18; i++)
        if(!strObjName[i].empty())
            vOperateObjName.push_back(strdup(strObjName[i].c_str()));
}
//��ѯ���еĲ�������
bool OperateLog::QueryAllOperateObject(list<string> &ObjList)
{
	for(vOperateIter=vOperateObjName.begin();vOperateIter!=vOperateObjName.end();vOperateIter++)
	{
		string strTemp = *vOperateIter;
		ObjList.push_back(strTemp);
	}
	return 1;
}
//��ѯ���еĲ�������
bool OperateLog::QueryAllOperateType(list<string> &ObjList)
{
	for(vOperateIter=vOperateType.begin();vOperateIter!=vOperateType.end();vOperateIter++)
	{
		string strTemp = *vOperateIter;
		ObjList.push_back(strTemp);
	}
	return 1;
}
//���ݲ�������Ѱ���������
int OperateLog::QueryOperateTypeNum(const string strTypeName)
{
	if(vOperateType.size() > 0)
    {
	    int i=0;
	    for(vOperateIter=vOperateType.begin();vOperateIter!=vOperateType.end();vOperateIter++)
	    {
		    if((*vOperateIter) == strTypeName)
			    return i;
		    i++;
	    }
    }
	return -1;
}
//���ݲ�����������Ѱ���������
int OperateLog::QueryOperateObjNameNum(const string strObjName)
{
	if(vOperateObjName.size() > 0)
    {
	    int i=0;
	    for(vOperateIter=vOperateObjName.begin();vOperateIter!=vOperateObjName.end();vOperateIter++)
	    {
		    if((*vOperateIter) == strObjName)
			    return i;
		    i++;
	    }
    }
	return -1;
}

void OperateLog::loadString()
{	
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_All",strAll);
		}
		CloseResource(objRes);
	}
}
struct RecordHead
{
    int prercord;
    int state;
    TTime createtime;
    int datalen;
}; 
//
char *buildbuf(int data,char *pt,int buflen)
{
    if(pt==NULL)
        return NULL;
    if(buflen<sizeof(int))
        return NULL;
    memmove(pt,&data,sizeof(int));
    pt += sizeof(int);
    return pt;
}
//
char *buildbuf(float data,char *pt,int buflen)
{
    if(pt==NULL)
        return NULL;
    if(buflen<sizeof(float))
        return NULL;
    memmove(pt,&data,sizeof(float));
    pt += sizeof(float);
    return pt;
}
//
char *buildbuf(string data,char *pt,int buflen)
{
	if(data.size()==0) data=" ";

    if(pt==NULL)
        return NULL;
    if(buflen < static_cast<int>(data.size()) + 1)
        return NULL;
    strcpy(pt,data.c_str());
    pt += data.size();
    pt[0]='\0';
    pt++;
    return pt;
}
//���¼��UserOperateLog��
bool OperateLog::InsertOperateRecord(string strTableName, string strUserInfo, string strOperateTime, string strOperateType, string OperateObjName, string OperateObjInfo)
{
	int iType = QueryOperateTypeNum(strOperateType);
	if(iType == -1)
	{
		return false;
	}

	int iName = QueryOperateObjNameNum(OperateObjName);
	if(iName == -1)
	{
		return false;
	}

    char data[1024]={0};

    RecordHead *prd=(RecordHead*)data;

    char *pt=data+sizeof(RecordHead);

    char *pm=NULL;
	
	if((pm=::buildbuf(strUserInfo,pt,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(strOperateTime,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(iType,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(iName,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(OperateObjInfo,pm,1024))==NULL)
    {
        return false;
	}
   
	prd->datalen= static_cast<int>(pm - pt);

    prd->state=1;

    prd->createtime=svutil::TTime::GetCurrentTimeEx();

    strcpy(pm,"DynString");

    int len= static_cast<int>(pm - data);

    len += static_cast<int>(strlen(pm)) + 1;

    if(!::AppendRecord(strTableName,data,len))
    {
        return false;
    }

	return true;
}
//��UserOperateLog���ѯ��¼
bool OperateLog::QueryOperateRecord(string strUserName, string strOObj, TTime startTime, TTime endTime, string strOType, list<OperateLogItem> &RecordsList)
{
	string strTableName = "UserOperateLog";

	RECORDSET rds=::QueryRecords(strTableName,startTime, endTime);
	if(rds==INVALID_VALUE)
	{
		return 0;
	}

	LISTITEM item;
	if(!::FindRecordFirst(rds,item))
	{
		return 0;
	}

	RECORD rdobj;
	while((rdobj=::FindNextRecord(item))!=INVALID_VALUE)
	{
		int state=0;
		int nRecordType = 0;
		int iRecordValue = 0;
		float fRecordValue = 0.0;
		string strRecordValue = "";

		string strUserLoginName;
		string strOperateObject;
		string strOperateType;
		string strOperateTime;
		string strOperateObjectInfo;	

		//��ȡ��־����
		if(::GetRecordValueByField(rdobj, "_UserID", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			string strTemp = GetIniFileString(strRecordValue, "LoginName", "", "user.ini");
			if(strcmp(strAll.c_str(), strUserName.c_str()) == 0)
			{
				strUserLoginName = strTemp;
			}
			else
			{
				if(strcmp(strTemp.c_str(), strUserName.c_str()) == 0)
				{
					strUserLoginName = strTemp;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_OperateObjName", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			string strTemp = vOperateObjName[iRecordValue];
			if(strcmp(strAll.c_str(), strOObj.c_str()) == 0)
			{
				strOperateObject = strTemp;
			}
			else
			{
				if(strcmp(strTemp.c_str(), strOObj.c_str()) == 0)
				{
					strOperateObject = strTemp;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_OperateType", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			string strTemp = vOperateType[iRecordValue];
			if(strcmp(strAll.c_str(), strOType.c_str()) == 0)
			{
				strOperateType = strTemp;
			}
			else
            {
				if(strcmp(strTemp.c_str(), strOType.c_str()) == 0)
				{
					strOperateType = strTemp;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_OperateTime", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			strOperateTime = strRecordValue;
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_OperateObjInfo", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			strOperateObjectInfo = strRecordValue;
		}
		else
		{
			continue;
		}

		OperateLogItem OItem;

		OItem.sUserName = strUserLoginName;
		OItem.sOperateObject = strOperateObject;
		OItem.sOperateType = strOperateType;
		OItem.sOperateTime = strOperateTime;
		OItem.sOperateObjectInfo = strOperateObjectInfo;	
		
		RecordsList.push_back(OItem);		
	}

	::ReleaseRecordList(item);
	::CloseRecordSet(rds);	

	return 1;
}

////////////////////////////////////////////////////////

//�����û������־
/////////////////////////////////////////////////////
bool InsertHitRecord(string strUser, string strPro, string strFunc, string strDesc, int iFlag, int iInterval)
{
    char data[1024]={0};

    RecordHead *prd=(RecordHead*)data;

    char *pt=data+sizeof(RecordHead);

    char *pm=NULL;
	
	if((pm=::buildbuf(strUser,pt,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(strPro,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(strFunc,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(strDesc,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(iFlag,pm,1024))==NULL)
    {
        return false;
	}
	if((pm=::buildbuf(iInterval,pm,1024))==NULL)
    {
        return false;
	}
   
	prd->datalen= static_cast<int>(pm - pt);

    prd->state=1;

    prd->createtime=svutil::TTime::GetCurrentTimeEx();

    strcpy(pm,"DynString");

    int len= static_cast<int>(pm - data);

    len += static_cast<int>(strlen(pm)) + 1;

    if(!::AppendRecord("UserHitLog",data,len))
    {
        return false;
    }

	return true;
}

//��ѯ�û������־
/////////////////////////////////////////////////////
bool QueryHitRecord(string strProgram, string strFunc, TTime startTime, TTime endTime, string strUser, list<HitLogQuery> &RecordsList)
{
	RECORDSET rds=::QueryRecords("UserHitLog",startTime, endTime);
	if(rds==INVALID_VALUE)
	{
		return false;
	}

	LISTITEM item;
	if(!::FindRecordFirst(rds,item))
	{
		return false;
	}

	string strAll(""); 
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_All",strAll);  //ȫ��
		}
		CloseResource(objRes);
	}

	RECORD rdobj;
	while((rdobj=::FindNextRecord(item))!=INVALID_VALUE)
	{
		int state=0;
		int nRecordType = 0;
		int iRecordValue = 0;
		float fRecordValue = 0.0;
		string strRecordValue = "";

		string sUser;
		string sHitPro;
		string sHitFunc;
		string sDesc;
		int sFlag;	
		int sInterval;
		string sCreateTime;

		//��ȡ��־����
		if(::GetRecordValueByField(rdobj, "_HitProgram", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			if(strProgram == strAll)
			{
				sHitPro = strRecordValue;	
			}
			else
			{
				if(strProgram == strRecordValue)
				{
					sHitPro = strRecordValue;			
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_HitFunc", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			if(strAll == strFunc)
			{
				sHitFunc = strRecordValue;
			}
			else
			{
				if(strFunc == strRecordValue)
				{
					sHitFunc = strRecordValue;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_UserID", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			string strTemp = GetIniFileString(strRecordValue, "LoginName", "", "user.ini");
			if(strAll == strUser)
			{
				sUser = strTemp;
			}
			else
			{
				if(strTemp == strUser)
				{
					sUser = strTemp;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_HitDescription", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			sDesc = strRecordValue;
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_HitFlag", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			if(strAll == strFunc)
			{
				if(iRecordValue == 1)
				{
					sFlag = 1;				
				}
				else
				{
					continue;
				}
			}
			else
			{
				sFlag = iRecordValue;
			}
		}
		else
		{
			continue;
		}
		if(::GetRecordValueByField(rdobj, "_HitInterval", nRecordType, state, iRecordValue, fRecordValue, strRecordValue))
		{
			sInterval = iRecordValue;
		}
		else
		{
			continue;
		}
		TTime createTime;
		if(::GetRecordCreateTime(rdobj, createTime))
		{
			sCreateTime = createTime.Format();
		}
		else
		{
			sCreateTime = "0000-00-00";
		}


		HitLogQuery LogItem;
		LogItem.sUserName = sUser;
		LogItem.sHitPro = sHitPro;
		LogItem.sHitFunc = sHitFunc;
		LogItem.sDesc = sDesc;
		LogItem.sHitFlag = sFlag;
		LogItem.sHitInterval = sInterval;
		LogItem.sTime = sCreateTime;
		
		RecordsList.push_back(LogItem);		
	}

	::ReleaseRecordList(item);
	::CloseRecordSet(rds);	

	return true;
}