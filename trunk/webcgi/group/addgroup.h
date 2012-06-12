/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�: addgroup.h
// ���/�༭��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_GROUP_VIEW_H_
#define _SV_ADD_GROUP_VIEW_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "category.h"
#include "dependtable.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"

#include "../userright/user.h"
#include "basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVAddGroup : public WTable
{
    //MOC: W_OBJECT SVAddGroup:WTable
    W_OBJECT;
public:
    SVAddGroup(WContainerWidget * parent = NULL, CUser *pUser = NULL, string szIDCUser = "default", 
        string szIDCPwd = "localhost");
    void EditGroup(string &szIndex);                                            // �༭��
    void SetParentIndex(string &szIndex) { m_szParentIndex = szIndex; };        // ���ø��ڵ�����
    string GetParentIndex(){return m_szParentIndex;};                           // �õ����ڵ�����        
    void ResetParam();                                                          // ��������
    void SetUserPwd(string &szUser, string &szPwd);                             // ����IDC �û� ����    
public signals:
    //MOC: SIGNAL SVAddGroup::editGroupName(string,string)
    void editGroupName(string strName,string szIndex);                          // �༭�� �ɹ�
    //MOC: SIGNAL SVAddGroup::addGroupName(string,string)
    void addGroupName(string strName,string szIndex);                           // �����ɹ�
    //MOC: SIGNAL SVAddGroup::backMain()
    void backMain();                                                            // ������ҳ��
private slots:
    //MOC: SLOT SVAddGroup::backPreview()
    void backPreview();                                                         // ������һ��ҳ��
    //MOC: SLOT SVAddGroup::saveGroup()
    void saveGroup();                                                           // ���� ����
    //MOC: SLOT SVAddGroup::showHelp()
    void showHelp();                                                            // ��ʾ/���ذ���
	//MOC: SLOT SVAddGroup::Translate()
	void Translate();                                                           //����
private:
    SVDependTable   * m_pAdvanced;                                              // �߼�ѡ���
    WPushButton     * m_pSave;
    WPushButton     * m_pCancel;
    WLineEdit       * m_pName;                                                  // ������
    WTable          * m_pGeneral;                                               // ��
    WTable          * m_pContentTable;
    WTable          * m_pSubContent;
    WText           * m_pNameHelp;                                              // �����ư���
    WText           * m_pTitle;                                                 // ����

    void initForm();                                                            // ��ʼ������
    void addGroupAdv();                                                         // �߼�ѡ��
    void addGroupTitle();                                                       // �����
    void addGroupGeneral();                                                     // ����ѡ��
    void addGroupOperate();                                                     // ����

    string m_szEditIndex;                                                       // �༭����
    string m_szParentIndex;                                                     // ���ڵ� ����
    bool m_bShowHelp;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string      m_szIDCUser;                                                    // IDC �û�
    string      m_szIDCPwd;                                                     // IDC �û�����
    CUser     * m_pSVUser;

	//����
	WPushButton * m_pTranslateBtn;	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
