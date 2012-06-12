#ifndef _SiteView_ECC_Main_View_H_
#define _SiteView_ECC_Main_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WSignalMapper"
class WText;
class WLineEdit;
class WPushButton;

#include <string>
#include <list>

using namespace std;

class CEccTreeView;
class CEccRightView;
class CEccTreeDevice;

#include "resstring.h"

class CEccMainView : public WTable
{
    //MOC: W_OBJECT CEccMainView:WTable
    W_OBJECT;
public:
    CEccMainView(WContainerWidget *parent = NULL);
    string getTreeTableName();

    virtual void refresh();
    //static void SetOldSel(const string &szName);

    static CEccRightView    *m_pRightView;                  // ����ͼ
    static CEccTreeView     *m_pTreeView;                   // ������ͼ
    static string           m_szIDCUser;                    // IDC�û�
    static string           m_szAddr;                       // ��ַ
    static string           m_szGlobalEvent;                // ˢ���¼�
    static string           m_szCurrentOpt;                 // ��ǰ��������
    static string           m_szLeftScroll;                 // ���Ĺ�������
private://slots
    //MOC: SLOT CEccMainView::EccObjectClick()
    void    EccObjectClick();                               // ���������Ӧ����
    //MOC: SLOT CEccMainView::EccMenuClick()
    void    EccMenuClick();                                 // �ڵ�˵���Ӧ����
    //MOC: SLOT CEccMainView::ConfirmDelete()
    void    ConfirmDelete();                                // ȷ��ɾ��
    //MOC: SLOT CEccMainView::RefreshState()
    void    RefreshState();                                 // ״̬ˢ��
private:
    void    createFrame();                                  // �������
    void    createHideObject();                             // �������ض���
    //void    createGlobalEvent();

    void    AddJsParam(string name, string value);          // ���JaveScript����
    void    TestDevice(const string &szIndex);              // �����豸

    void    RefreshDevice(const CEccTreeDevice *pDevice);   // ˢ���豸
private:

    SVResString             m_pResString;                   // ��Դ�ַ�
    // WT
    WPushButton             *m_pbtnConfirm;                 // ȷ�ϰ�ť�����أ�
    WPushButton             *m_pbtnRefresh;                 // ˢ�°�ť�����أ�
    WLineEdit               *m_pCurrentID;                  // ��ǰ�������������أ�
    WLineEdit               *m_pCurOperate;                 // ��ǰ���������أ�
private:
    string                  m_szCurrentCopy;                // ��ǰ����
    string                  m_szCurrentConfirm;             // ��ǰ�ȴ�ȷ��ɾ�����������

    bool                    m_bFirstLoad;
};

#endif
