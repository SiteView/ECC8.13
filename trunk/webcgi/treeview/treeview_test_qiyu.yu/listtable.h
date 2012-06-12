#ifndef _SiteView_ECC_List_Table_H_
#define _SiteView_ECC_List_Table_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WSignalMapper"
#include "../../opens/libwt/WTable"
class WText;
class WImage;
class WCheckBox;
class WPushButton;

#include <map>
#include <list>
#include <string>

using namespace std;

#include "../../kennel/svdb/svapi/svdbapi.h"

typedef void (*ShowAddNew)(string);

class CEccImportButton;
class CEccButton;

class CEccListTable : public WTable
{
    //MOC: W_OBJECT CEccListTable:WTable
    W_OBJECT;
public:
    CEccListTable(WContainerWidget *parent = NULL, bool bHasOperate = true, bool bCreateHasNo = true, 
        bool bGridTable = true, bool bControl = true);

    // public fuction list
    // ��Ӹ�ѡ���б�
    void                addCheckList(string szIndex, WCheckBox *pCheck = NULL);
    // ����ѡ���б�
    void                clearCheckList();
    // �õ������б�
    WTable *            getListTable();
    // �����ӱ�
    void                hideSubTable();
    // ����������
    void                hideNoChild();
    // ������Ӱ�ť����ʾ����
    void                setAddNewTitle(string szTitle);
    // ������Ӱ�ť����ʾ��Ϣ
    void                setAddNewTip(string szTooltip);
    // ������Ӱ�ť���õĺ���
    void                setAddNewFunc(void(*pfunc)(string));
    // ���������б����
    void                setCols(list<string> &lsCols);
    // ���õ�ǰ����ID
    void                setCurrentID(string szCurrentID);
    // �������ݱ�ĸ�
    void                setHeight(int nHeight);
    // ���ò�����ť
    void                setOperaters(list<int> &lsOperaters, int nType);
    //
    void                setOperatePurview(int nPurview, int nType);
    // ������������ʾ����
    void                setNoChild(string szText);
    // ���ñ���
    void                setTitle(string szTitle);
    // �������ݱ�Ŀ��
    void                setWidth(int  nWidth);
    // ��ʾ������
    void                showNoChild();
    //
    void                showSubTable();
    //
    void                showHideSort(bool bShow);
private:
    //MOC: SLOT CEccListTable::ShowHideSub()
    void    ShowHideSub();
    //MOC: SLOT CEccListTable::SelectAll()
    void    SelectAll();
    //MOC: SLOT CEccListTable::SelectNone()
    void    SelectNone();
    //MOC: SLOT CEccListTable::InvertSelect()
    void    InvertSelect();
    //MOC: SLOT CEccListTable::Confirm()
    void    Confirm();
    //MOC: SLOT CEccListTable::AddNew()
    void    AddNew();
    //MOC: SLOT CEccListTable::Copy()
    void    Copy();
    //MOC: SLOT CEccListTable::Paste()
    void    Paste();
    //MOC: SLOT CEccListTable::Enable()
    void    Enable();
    //MOC: SLOT CEccListTable::Disable()
    void    Disable();
    //MOC: SLOT CEccListTable::DelSelect()
    void    DelSelect();
    //MOC: SLOT CEccListTable::RefreshSel()
    void    RefreshSel();
    //MOC: SLOT CEccListTable::Sort()
    void    Sort();
private:
    WTable              *m_pPath;
    WTable              *m_pSubTable;           // ���ݱ�
    WTable              *m_pOperate;            // ����
    WTable              *m_pSubOperate;
    WImage              *m_pControl;            // ����/��ʾ�ֱ�ͼƬ
    WText               *m_pTitle;              // ����
    WText               *m_pNoChild;            // ������

    WPushButton         *m_pHideButton;

    CEccImportButton    *m_pAddNew;             // ��Ӱ�ť

    map<int, CEccButton*, less<int> >   m_OperateList;
private:
    // ��ʼ��ҳ��
    void                initForm(bool bHasOperate, bool bCreateNoChild, bool bGridTable, bool bControl);
    // ����������
    void                createTitle(bool bControl);
    // ���������ӱ�
    void                createSubTable(WTable *pSubTable, bool bGridTable);
    // ����������Ϣ
    void                createOpaerate(WTable *pSubTable);

    void                createHideConfirm(WTable *pSubTable);

    void                pasteDevice();

    void                pasteMonitor();

    bool                IsCanBePaste();

    // �Ƿ���ʾ���ݱ�
    bool                m_bShowSub;
    // �Ƿ�������
    bool                m_bHasChild;
    // �Ƿ���������Ӳ�������
    bool                m_bSetFunc;

    //
    string              m_szCurrentID;
    int                 m_nDataType;
    int                 m_nHideRow;

    // ��ѡ���б�
    map<string, WCheckBox*, less<string> > m_lsCheckBox;

    list<string>                           m_lsSelIndex;
    // ��ӵ��ú���
    ShowAddNew          m_pAddFunc;
    // ��Ԫ��
    friend class        CEccAdvanceTable;
};

#endif
