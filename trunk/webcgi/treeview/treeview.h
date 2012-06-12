#ifndef _SiteView_ECC_Tree_View_H_
#define _SiteView_ECC_Tree_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;
class WImage;

#include <string>
#include <stack>
#include <list>
#include <map>

using namespace std;

#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../../kennel/svdb/libutil/time.h"

class CEccMainView;         // ����ͼ
class CEccTreeDevice;       // �豸�ڵ�
class CEccTreeGroup;        // ��ڵ�
class CECCMonitor;          // �����
class CUser;                // �û�����
class OperateLog;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView ECC base tree node class
class CEccTreeNode
{
public:
    CEccTreeNode();             // ���캯��
    ~CEccTreeNode();            // ��������
public:
    // �õ���ֹ����
    int         getDisableCount()   const;
    // �õ���������
    int         getErrorCount()     const;
    // �õ����������
    int         getMointorCount()   const;
    //
    int         getPurview()        const;
    // �õ���ʾ˳��
    int         getShowIndex()      const;
    // �õ�״̬
    int         getState()          const;
    // �õ�����
    int         getType()           const;
    // ����״̬����
    int         getWarnCount()      const;
    // ��ǰ����
    string      getECCIndex()       const;
    // ����
    string      getName()           const;
    // �õ���ʾ����
    string      getShowText()       const;
    // �õ�������
    string      getDependsID()      const;
    // �õ���������
    string      getCondition()      const;
    // �õ�������Ϣ
    string      getDescription()    const;
    // �õ�ˢ��ʱ��
    string      getShowTime()       const;
private:
    // �������г�Ա����
    virtual     void Reset();
    // ����ֹ�ļ��������
    int         m_nDisableCount;
    // ���ڴ���״̬�ļ��������
    int         m_nErrorCount;
    // ���������
    int         m_nMonitorCount;
    // ��ǰ����ʾ˳��
    int         m_nShowIndex;
    // ״̬
    int         m_nState;
    // ����
    int         m_nType;
    // ����״̬�ļ��������
    int         m_nWarnningCount;
    // Ȩ��
    int         m_nPurview;
    // ��ǰ����
    string      m_szIndex;
    // ����
    string      m_szName;
    // ��ʾ����
    string      m_szShowText;
    // ������
    string      m_szDependsOn;
    // ��������
    string      m_szDepCondition;
    // ����
    string      m_szDescription;
    //
    string      m_szState;
    // ˢ��ʱ��
    TTime m_tRefreshTime;
    // �ڵ�����
    WText       *m_pTreeText;
    // �ڵ���ʾͼƬ
    WImage      *m_pImgType;

    // ��Ԫ��
    friend      class       CEccTreeGroup;      // ��ڵ�
    friend      class       CEccTreeDevice;     // �豸�ڵ�
    friend      class       CEccTreeView;       // ����ͼ
    friend      class       CEccMainView;       // ����ͼ
    friend      class       CEccRightView;      // ����ͼ
    friend      class       CEccSortTable;      // ����
};
// end
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView ECC Monitor class
class CECCMonitor
{
public:
    // ���캯��
    CECCMonitor();
    // ��������
    ~CECCMonitor();
    // �õ��������ʾ˳��
    int         getShowIndex()  const;
    // �õ������״̬
    int         getState()      const;
    // �õ����������
    string      getECCIndex()   const;
    //
    int         getMTID()       const;
    // �õ����������
    string      getName()       const;
    // �õ������״̬��ʾ����
    string      getShowText()   const;
    // �õ������ˢ��ʱ��
    string      getShowTime()   const;
private:
    // ��ʾ˳��
    int         m_nShowIndex;
    // ״̬
    int         m_nState;
    // ���������
    int         m_nMTID;
    // ����
    string      m_szIndex;
    // ����
    string      m_szName;
    // ��ʾ����
    string      m_szShowText;
    // ˢ��ʱ��
    TTime m_tRefreshTime;

    // ��Ԫ��
    friend      class CEccTreeDevice;           // �豸�ڵ�
    friend      class CEccTreeView;             // ����ͼ
    friend      class CEccSortTable;            // ����
    friend      class CEccListTable;            // �б�
};
// End SiteView ECC Monitor class define
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEccTreeGroup : public CEccTreeNode
{
public:
    CEccTreeGroup();                            // ���캯��
    ~CEccTreeGroup();                           // ��������

    // ��ʾ�ӱ�
    void        showSubTables();
    // �õ��豸���������������ڵ��豸��
    int         getDeviceCount()    const;
    // ׷����
    int         AppendGroup(const string &szIndex, const string &szName, const string &szDesc, const string &szDepends,
                            const string &szCondition, const string &szMenu, int nPurview);
    // ׷���豸
    int         AppendDevice(const string &szIndex, const string &szName, const string &szDesc, const string &szDepends,
                             const string &szCondition, const string &szDeviceType, const string &szOsType,
                             const string &szIsNetworkSet, const string &szMenu, int nPurview);
private:

    virtual     void Reset();                               // �������г�Ա����

    int         m_nDeviceCount;                             // �豸����

    map<int, CEccTreeGroup, less<int> >    m_SubGroups;     // ����
    map<int, CEccTreeDevice, less<int> >   m_Devices;       // �豸

    WImage      *m_pImageExpand;                            // 
    WTable      *m_pSubGroupsTable;                         // �����
    WTable      *m_pDevicesTable;                           // �豸��

    // ��Ԫ��
    friend      class CEccTreeView;                         // ����ͼ
    friend      class CEccGroupView;                        // ����ͼ
    friend      class CEccSortTable;                        // ����
};
// end SiteView Ecc Group define
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView Ecc device
class CEccTreeDevice : public CEccTreeNode
{
public:
    CEccTreeDevice();
    ~CEccTreeDevice();
public:
    bool            MTCanUsing(int nMTID);              // �жϼ�����Ƿ��ܱ����豸ʹ�ã�ճ�������ʱʹ�ã�
    string          getRealDeviceType() const;          // �õ��豸����
    string          getDeviceType()     const;          // �õ��豸��ʾ����
    string          getOSType()         const;          // �õ��豸����ϵͳ����
    string          isNetworkSet()      const;          // �Ƿ��������豸

    int             AppendMonitor(const string &szIndex, const string &szName, int nMTID);      // ׷�Ӽ����
    void            EditMonitor(const string &szIndex, const string &szName);                   // �޸ļ����
private:
    virtual         void Reset();                   // �������г�Ա����
    string          m_szRealDeviceType;             // �豸����
    string          m_szDeviceType;                 // �豸��ʾ����
    string          m_szOSType;                     // ����ϵͳ����
    string          m_szIsNetworkset;               // �Ƿ��������豸
    
    map<int, CECCMonitor, less<int> >  m_Monitors;  // �������
    // ��Ԫ��
    friend      class CEccTreeView;             // ����ͼ
    friend      class CEccTreeGroup;            // ��ڵ�
    friend      class CEccMonitorView;          // �������ͼ
    friend      class CEccSortTable;            // ����
    friend      class CEccListTable;            // �б�
    friend      class CEccMainView;             // ����ͼ
};
// end SiteView Ecc Device define
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SiteView TreeView
class CEccTreeView : public WTable
{
    //MOC: W_OBJECT CEccTreeView:WTable
    W_OBJECT;
public:
    CEccTreeView(WContainerWidget *parent = NULL, string szUserID = "1");
    // ����se���������ֵ���ʾ����
    void            BuildSEShowText(string szSEID = "1");
    // �����豸���͵õ������豸��ʹ�õļ�����б�
    void            GetDevMTList(const string &szDTType, list<int> &lsMTID);
    // �����豸���ͼ������Ӧ�б�
    void            InsertDevMTList(const string &szDTType, const list<int> &lsMT);
    // ���¼����� 
    void            reloadTree();
    // �����½�û�ID
    void            resetUserID(const string &szUserID);
    // ������͵�����С��������
    void            setLeftResizeName(const string &szLeftName);
    // ���������õ�Ecc Object
    static const    CEccTreeNode   *getECCObject(const string &szIndex);
    // �õ�SE�б�
    static const map<string, CEccTreeGroup, less<string> > & getSEList();
    // �õ�SE������
    static int   getSVSECount();
    // ׷����
    static int   AppendGroup(const string &szIndex, const string &szName, const string &szDesc, 
                                            const string &szDepends, const string &szCondition);
    // ׷���豸
    static int   AppendDevice(const string &szIndex, const string &szName, const string &szDesc, 
                                             const string &szDepends, const string &szCondition, const string &szDeviceType,
                                             const string &szOsType, const string &szIsNetworkSet);
    // ��������ɾ����
    static void  DeleteGroupByID(const string &szGroupID);
    // ��������ɾ���豸
    static void  DeleteDeviceByID(const string &szDeviceID);
    // �༭��
    static void  EditGroup(const string &szIndex, const string &szName, const string &szDesc, 
                                            const string &szDepends, const string &szCondition);
    // �༭�豸
    static void  EditDevice(const string &szIndex, const string &szName, const string &szDesc, 
                                            const string &szDepends, const string &szCondition);
    // �༭ SE
    static void  EditSVSE(const string &szIndex, const string &szName);
    // �����������ڵ�
    static void  ReCreateTreeNode(const string &szIndex);
    // ���� ·��
    static void  MakePath(const string &szIndex, PAIRLIST &lsPath);
    //
    static void  AddOperaterLog(int nOperateType, int nObjectType, const string &szOperateMsg);
public:
    static      CUser               m_SVSEUser;         // �û�������
    static      OperateLog          m_OperateLog;
private:
    //MOC: SLOT CEccTreeView::ReloadTreeView()
    void    ReloadTreeView();
private:
    // ��������
    void    createContent();
    // ����Title
    void    createTitle();
    // ��ʼ��
    void    initForm();
    // �����˵�
    string  makeMenuText(int nType, string szIndex, int &nPurview);
    // ö��SiteView ECC SE
    void    EnumSVSE();
    // ö��ָ�������������е�������豸��Ϣ��SE�������飩
    void    EnumGroups(CEccTreeGroup &objGroup);
    // ö��ָ���豸�������豸��Ϣ
    void    EnumDevice(CEccTreeDevice &objDevice);
    // ö��ָ������������ļ������Ϣ
    void    EnumMonitor(CECCMonitor &objMonitor);
    // �õ�ָ���������״̬��Ϣ
    void    getMonitorState(CECCMonitor &objMonitor);
    // �����豸���͵õ���ʾ����
    string  getDeviceShowType(const string &szDeviceType);
    // �Ƿ񱻽�ֹ SE���ܱ���ֹ
    bool    isObjectDisable(MAPNODE &mainNode, string &szState, int nType);
    // �Ƿ�ǰ���ڵ㱻�޸�
    bool    isCurrentPathEdit(const string &szIndex);
    // �Ƿ�ǰ�ڵ��ӽڵ㱻�޸�
    bool    isCurrentChildEdit(const string &szIndex);
    // ��������Ϣ
    void    UpdateGroupData(CEccTreeGroup &objGroup);
    // ������
    void    CreateTree();
    // ��������
    void    CreateSubGroups(CEccTreeGroup &objGroup, WTable *pSubTable);
private:
    WTable          *m_pTree;           // ��
    WText           *m_pCurSel;         // ��ǰѡ��
    WImage          *m_pHideOpt;        // ��������ͼ���ư�ť
    string          m_szCurSelIndex;    // ��ǰѡ�������

    CEccTreeGroup   m_objRootGroup;     // ���ڵ�

    map<string, list<int>, less<string> >       m_DevMTList;    // �豸ģ��ͼ������Ӧ�ı�
    map<string, CEccTreeGroup, less<string> >   m_SVSEList;     // SiteView ECC SE��
    map<string, string, less<string> >          m_DevType;      // �豸ģ�����ƺ��豸��ʾ���ƶ�Ӧ��

    // ��Ԫ��
    friend class    CEccMainView;       // ������
    friend class    CEccTreeGroup;      // ��ڵ�
    friend class    CEccTreeDevice;     // �豸�ڵ�
    friend class    CEccRightView;      // ����ͼ
    friend class    CEccSortTable;      // ����
};

#endif
