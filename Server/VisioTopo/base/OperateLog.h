/*************************
 *	UserOperateLog 表 
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
	
	//
	string strIdcUserId;
	bool IsMyOperateLog(string strUseIndex);

public :
	//查询所有的操作对象
	bool QueryAllOperateObject(list<string> &ObjList);
	//查询所有的操作类型
	bool QueryAllOperateType(list<string> &ObjList);
	//插入记录
	bool InsertOperateRecord(string strTableName, string strUserInfo, string strOperateTime, string strOperateType, string OperateObjName, string OperateObjInfo="");
	//查询记录
	bool QueryOperateRecord(string strUserName, string strOObj, TTime startTime, TTime endTime, string strOType, list<OperateLogItem> &RecordsList);
};

////////////////////////////////////////////////////////////////////////////////////////////////

/***
*
*  用户点击按钮日志  UserHitLog
*
***/

//日志结构
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
*   0  函数开始
*   1  函数结束
***/

//插入用户点击日志
bool InsertHitRecord(string strUser, string strPro, string strFunc, string strDesc, int iFlag, int iInterval);


//查询用户点击日志
bool QueryHitRecord(string strProgram, string strFunc, TTime startTime, TTime endTime, string strUser, list<HitLogQuery> &RecordsList);