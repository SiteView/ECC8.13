 /*********************************
 *
 *   ��װʱдgeneral.ini�ļ�
 *      
 *       ����          100
 *       �豸��        10
 *       ��ʼ����      ����
 *       ����ʱ��      30��
 *
 *********************************/

#include "stdafx.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "Des.h"

using namespace std;
using namespace svutil;

#define pointcount  "100"
#define entitycout  "10"

int _tmain(int argc, _TCHAR* argv[])
{
	Des OneDes;
	char strDes1[1024]={0},strDes2[1024]={0},strDes3[1024]={0},strDes4[1024]={0};
	//����
	std::string point = pointcount; 
	OneDes.Encrypt(point.c_str(),strDes1);
	WriteIniFileString("license", "point", strDes1,  "general.ini");
	//�豸��
	std::string  nw = entitycout;
	OneDes.Encrypt(nw.c_str(),strDes2);
	WriteIniFileString("license", "nw", strDes2,  "general.ini");
	//��ʼʱ��
	std::string starttime;
	TTime timer = TTime::GetCurrentTimeEx();
	char cYear[1024] = {0},cMonth[1024] = {0},cDay[1024] = {0};
	string strYear,strMonth,strDay;
	itoa(timer.GetYear(),cYear,10);
	strYear = cYear;
	starttime += strYear;
	starttime += '-';
	itoa(timer.GetMonth(),cMonth,10);
	strMonth = cMonth;
	if(timer.GetMonth() < 10)
	{
		starttime += '0';
		starttime += strMonth;
	}
	else
	{
		starttime += strMonth;
	}
	starttime += '-';
	itoa(timer.GetDay(),cDay,10);
	strDay = cDay;
	if(timer.GetDay() < 10)
	{
		starttime += '0';
		starttime += strDay;		
	}
	else
	{
		starttime += strDay;	
	}
	OneDes.Encrypt(starttime.c_str(),strDes3);
	WriteIniFileString("license", "starttime", strDes3,  "general.ini");
	//����ʱ��
	std::string lasttime="30";
	OneDes.Encrypt(lasttime.c_str(),strDes4);
	WriteIniFileString("license", "lasttime", strDes4,  "general.ini");

	return 0;
}

