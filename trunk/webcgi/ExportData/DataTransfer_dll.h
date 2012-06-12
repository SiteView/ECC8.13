

#ifndef	SITEVIEW_DATATRANSFER_DLL_H
#define	SITEVIEW_DATATRANSFER_DLL_H

#include <string>
using std::string;

#ifdef DATATRANSFER_EXPORT
#define DTRNSF_API  __declspec(dllexport)
#else
#define DTRNSF_API  __declspec(dllimport)
#endif









//注意：所有将迁移的源数据，均来自本机！

enum sqldbType{ MYSQL, SQLSERVER, ORACLE };	  //数据库类型
enum transferWhat{ ALLCONFIG, MONITORDATA };  //迁移什么

DTRNSF_API 
bool DataTransfer(int twhat, string drivername , int sqltype, string hostname, string dbname, string dbuser, string dbpwd,  string logfname="",            string winuser="", string winpwd="");
//             	  迁移什么，   odbc驱动名称        数据库类型，  主机名，         数据库名，   数据库用户名， 数据库密码，日志文件名（为空则输出到屏幕）， windows登录用户名，  windows登录密码



#endif