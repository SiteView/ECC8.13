/*************************
 *	UserOperateLog �� 
 *************************/

#include <string>
#include <vector>
#include <list>

#include "../../kennel/svdb/svapi/svdbapi.h"

using namespace std;

struct OperateLogItem
{
	string sUserName;
	string sOperateObject;
	string sOperateType;
	string sOperateTime;
	string sOperateObjectInfo;	
};

class OperateLog
{

public:
    OperateLog();
	~OperateLog();

private:
	vector<string> vOperateType;
	vector<string> vOperateObjName;
	vector<string>::iterator vOperateIter;
	string strAll;
private :
	void loadString();
	void OperateTypeInit();
	void OperateObjNameInit();
	int QueryOperateTypeNum(const string strTypeName);
	int QueryOperateObjNameNum(const string strObjName);
public :
	//��ѯ���еĲ�������
	bool QueryAllOperateObject(list<string> &ObjList);
	//��ѯ���еĲ�������
	bool QueryAllOperateType(list<string> &ObjList);
	//�����¼
	bool InsertOperateRecord(string strTableName, string strUserInfo, string strOperateTime, string strOperateType, string OperateObjName, string OperateObjInfo="");
	//��ѯ��¼
	bool QueryOperateRecord(string strUserName, string strOObj, TTime startTime, TTime endTime, string strOType, list<OperateLogItem> &RecordsList);
};

////////////////////////////////////////////////////////////////////////////////////////////////

/***
*
*  �û������ť��־  UserHitLog
*
***/

//��־�ṹ
struct HitLog
{
	string sUserName;
	string sHitPro;
	string sHitFunc;
	string sDesc;
	int sHitFlag;	
	int sHitInterval;	
};

struct HitLogQuery
{
	string sUserName;
	string sHitPro;
	string sHitFunc;
	string sDesc;
	int sHitFlag;	
	int sHitInterval;
	string sTime;
};

/***
*	iFlag
*   0  ������ʼ
*   1  ��������
***/

//�����û������־
bool InsertHitRecord(string strUser, string strPro, string strFunc, string strDesc, int iFlag, int iInterval);


//��ѯ�û������־
bool QueryHitRecord(string strProgram, string strFunc, TTime startTime, TTime endTime, string strUser, list<HitLogQuery> &RecordsList);