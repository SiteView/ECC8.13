/*
*  excelItem.h
*
*  Modified on 2007-10-10 By �պ�
*     1���ڱ����м��뷧ֵ������
*
*/
#ifndef sxcokok1029876_H
#define sxcokok1029876_H
#include <string>
using namespace std;
struct forXLSItem
{
	string name;
	int normalRunTime;
	int errorRunTime;
	int dangerRunTime;
	string measureName;
	float max;
	float avg;
	string bound;
	forXLSItem()
	{
		name = " ";
		normalRunTime = 0;
		errorRunTime = 0;
		dangerRunTime = 0;
		measureName = " ";
		max = 0.0;
		avg = 0.0;
		bound = " ";
	}
};
#endif