#ifndef _SiteView_ECC_Group_View_H_
#define _SiteView_ECC_Group_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;

#include <string>
#include <list>

using namespace std;


#include "gentitle.h"

class CEccTreeGroup;
class CEccListTable;

class CEccGroupView : public WTable
{
    //MOC: W_OBJECT CEccGroupView:WTable
    W_OBJECT;
public:
    CEccGroupView(WContainerWidget *parent = NULL);
public:
    void        refreshTime();
    void        setCurrentObj(const CEccTreeGroup *pNode);
    void        UpdataGeneralData(const CEccTreeGroup * pNode);

private:
    void            createContent();
    void            createDeviceList();
    void            createGroupList();
    void            createGeneral();

    void            createStateDesc();
    void            createTitle();
    void            initForm();

    void            clearGroupList();
    void            clearDeviceList();
    void            changePath(const string &szIndex);

    void            EnumGroup(const CEccTreeGroup *pNode);
    void            EnumDevice(const CEccTreeGroup *pNode);
private:
    //CEccTreeGroup   *m_pGroupNode;

    CEccGenTitle    *m_pTitle;
    CEccListTable   *m_pGeneral;
    CEccListTable   *m_pGroupList;
    CEccListTable   *m_pDeviceList;

    WTable          *m_pDepend;
    WTable          *m_pContent;
    WText           *m_pName;
    WText           *m_pDescription;
    WText           *m_pState;
};

#endif