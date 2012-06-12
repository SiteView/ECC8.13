/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件: adddevice1st.h
// 添加设备第一步，显示设备列表
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_DEVICE_1ST_H_
#define _SV_ADD_DEVICE_1ST_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WPushButton"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "showtable.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVDeviceList : public  WTable//WContainerWidget
{
    //MOC: W_OBJECT SVDeviceList:WTable
    W_OBJECT;
public:
    SVDeviceList(WContainerWidget *parent = NULL,string szIDCUser = "default", string szIDCPwd = "localhost");

    void SetUserPwd(string &szUser, string &szPwd);                     // 设置 IDC 用户 密码
    void setParentIndex(string &szIndex){m_szParentID = szIndex;};      // 设置 上级 节点 索引
    string getParentID(){return m_szParentID;};                         // 得到 上级 节点 索引
public signals:
    //MOC: SIGNAL SVDeviceList::backPreview()
    void backPreview();                                                 // 返回上一级页面
    //MOC: SIGNAL SVDeviceList::AddNewDevice(string)
    void AddNewDevice(string szIndex);                                  // 添加信息的设备（设备类型索引）
private slots:
    //MOC: SLOT SVDeviceList::addDevice(const std::string)
    void addDevice(const std::string szIndex);                          // 添加设备
    //MOC: SLOT SVDeviceList::cancel()
    void cancel();                                                      // 取消添加
	//MOC: SLOT SVDeviceList::Translate()
	void Translate();                                                   // 翻译
private:
    //string m_szTitle;                                                   // 标题
    //string m_szCancel;                                                  // 取消添加
    //string m_szCancelTip;                                               // 取消添加提示信息

    string m_szParentID;                                                // 上级节点
    list<SVShowTable*> m_lsDevice;                                      // 隐藏/显示子表 的list

    void enumDeviceGroup();                                             // 枚举 设备 组
    void initForm();                                                    // 初始化页面
    //void loadString();                                                  // 加载字符串
    void createTitle();                                                 // 创建标题
    void createOperate();                                               // 创建操作
    void addDeviceByID(string &szDeviceID, SVShowTable * pTable);       // 根据添加设备列表

    WSignalMapper m_DeviceMap;                                          // Singal map（Entity Template）
    WTable        * m_pContentTable;
    WTable        * m_pSubContent;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string    m_szIDCUser;                                              // IDC 用户
    string    m_szIDCPwd;                                               // IDC 密码

	//翻译
	WPushButton * m_pTranslateBtn;
	
	//string          m_szTranslate;
	//string          m_szTranslateTip;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
