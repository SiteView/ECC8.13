#ifndef _SiteView_ECC_Title_H_
#define _SiteView_ECC_Title_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;
class WImage;
class WPushButton;

#include <string>
#include <list>

using namespace std;

#include "../../kennel/svdb/svapi/svdbapi.h"

class CEccGenTitle : public WTable
{
    //MOC: W_OBJECT CEccGenTitle:WTable
    W_OBJECT;
public:
    CEccGenTitle(WContainerWidget *parent = NULL);
    void                setCurIndex(const string &szIndex);
    void                setTitle(const string &szTitle);
    void                refreshTime();
    WImage*             getIconControl() const;
    WImage*             getListControl() const;
private:
    void            initForm();
    void            createViewControl();
private:
    WTable              *m_pTitle;
    WText               *m_pTime;
    WImage              *m_pIcon;
    WImage              *m_pList;

    list<WText*>        *m_lsIndex;
};

#endif
