

#ifndef	SITEVIEW_DATATRANSFER_DLL_H
#define	SITEVIEW_DATATRANSFER_DLL_H

#include <string>
using std::string;

#ifdef DATATRANSFER_EXPORT
#define DTRNSF_API  __declspec(dllexport)
#else
#define DTRNSF_API  __declspec(dllimport)
#endif









//ע�⣺���н�Ǩ�Ƶ�Դ���ݣ������Ա�����

enum sqldbType{ MYSQL, SQLSERVER, ORACLE };	  //���ݿ�����
enum transferWhat{ ALLCONFIG, MONITORDATA };  //Ǩ��ʲô

DTRNSF_API 
bool DataTransfer(int twhat, string drivername , int sqltype, string hostname, string dbname, string dbuser, string dbpwd,  string logfname="",            string winuser="", string winpwd="");
//             	  Ǩ��ʲô��   odbc��������        ���ݿ����ͣ�  ��������         ���ݿ�����   ���ݿ��û����� ���ݿ����룬��־�ļ�����Ϊ�����������Ļ���� windows��¼�û�����  windows��¼����



#endif