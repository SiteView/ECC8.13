/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�: addsvse.h
// ��ӻ����޸�SE
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_ADD_SVSE_H_
#define _SV_ADD_SVSE_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "category.h"
#include "dependtable.h"

#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"

#include "../../kennel/svdb/svapi/svapi.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVAddSE : public WTable
{
    //MOC: W_OBJECT SVAddSE:WTable
    W_OBJECT;
public:
    SVAddSE(WContainerWidget * parent = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    void AddSVSE();                                     // ��� SE
    void EditSVSE(string &szIndex);                     // �༭ SE    
    void SetUserPwd(string &szUser, string &szPwd);     // ���� IDC �û�������
public signals:
    //MOC: SIGNAL SVAddSE::EditSVSESucc(string,string)
    void EditSVSESucc(string strName,string szIndex);   // �༭SE �ɹ�
    //MOC: SIGNAL SVAddSE::AddSVSESucc(string,string)
    void AddSVSESucc(string strName,string szIndex);    // ���SE �ɹ�
    //MOC: SIGNAL SVAddSE::backSVSEView()
    void backSVSEView();                    // ������һ��ҳ��
private slots:
    //MOC: SLOT SVAddSE::backPreview()
    void backPreview();                     // ������һ��ҳ��
    //MOC: SLOT SVAddSE::saveSVSE()
    void saveSVSE();                        // �����޸�
    //MOC: SLOT SVAddSE::showHelp()
    void showHelp();                        // ��ʾ����
private:
    WLineEdit       * m_pName;              // SE����
    //WLineEdit       * m_pHost;              // ����
    //WTextArea       * m_pDescription;       // ����
    WTable          * m_pGeneral;           // ��
    WTable          * m_pContentTable;
    WTable          * m_pSubContent;
    WText           * m_pNameHelp;          // SE���ư���
    WText           * m_pTitle;             // ����
    //WText           * m_pHostHelp;          // �������ư���
    //WText           * m_pDescriptionHelp;   // ������Ϣ����
    WPushButton     * m_pSave;
    WPushButton     * m_pCancel;

    void initForm();            // ��ʼ��ҳ��

    //void addAdvance();          // ��Ӹ߼�����
    void addTitle();            // ��ӱ���
    void addGeneral();          // ��ӻ���ѡ��
    void addOperate();          // ��Ӳ���
    void resetData();           // ��������

    string m_szEditIndex;       // �޸ĵ�SE ����
    bool m_bShowHelp;           // �Ƿ���ʾ������Ϣ
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string      m_szIDCUser;    // IDC �û�
    string      m_szIDCPwd;     // IDC �û�����
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file