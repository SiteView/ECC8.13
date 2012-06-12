

#ifndef _SV_ECC_TREEVIEW_RES_STRING_H_
#define _SV_ECC_TREEVIEW_RES_STRING_H_

#pragma once

#include <map>
#include <string>

using namespace std;

#include "../../kennel/svdb/svapi/svapi.h"

class SVResString
{
public:
    // ���캯��
    SVResString(string szResLanguage = "default", string szAddr = "localhost");
    ~SVResString();                                                 // ��������
    static const string getResString(const char* pszResID);         // ������ԴID�õ��ַ���
    static const string getResString(const string &szResID);        // ������ԴID�õ��ַ���
    void ResetResoureType(string &szResLanguage, string &szAddr);   // ������Դ�����Ժ�λ��
    static SVResString      m_DefineOnce;
private:
    string      m_szResLanguage;                                    // ��Դ����
    string      m_szResAddr;                                        // ��ȡ��Դλ��
    // ��Դ�ַ����б�
    map<string, string, less<string> > m_lsResource;
    typedef     map<string, string, less<string> >::iterator    resItem;
    void        loadStrings();                                      // ������Դ�ַ���

    void        loadAddSVSEStrings(MAPNODE &objNode);               // �������SE��Դ�ַ���
    void        loadAddGroupStrings(MAPNODE &objNode);              // �����������Դ�ַ���
    void        loadAddDeviceStrings(MAPNODE &objNode);             // ��������豸��Դ�ַ���
    void        loadAddMonitorStrings(MAPNODE &objNode);            // ������Ӽ������Դ�ַ���

    void        loadBatchAddStrings(MAPNODE &objNode);              // �������������Դ�ַ���

    void        loadConditionStrings(MAPNODE &objNode);             // ���ر���������Դ�ַ���
    void        loadTreeviewStrings(MAPNODE &objNode);              // ��������ʾ��Դ�ַ���
    void        loadSVSEViewStrings(MAPNODE &objNode);              // ����SE ��ͼ��ʾ��Դ�ַ���
    void        loadGroupviewStrings(MAPNODE &objNode);             // ��������ͼ��ʾ��Դ�ַ���
    void        loadMonitorviewStrings(MAPNODE &objNode);           // ���ؼ������ͼ��ʾ��Դ�ַ���
    void        loadSortStrings(MAPNODE &objNode);                  // �������������Դ�ַ���

    void        loadGeneralStrings(MAPNODE &objNode);               // ����ͨ����Դ�ַ���

    const string getStringFromRes(const char* pszResID);

    OBJECT      m_objRes;
};

#endif
