#ifndef _SiteView_ECC_SVSE_View_H_
#define _SiteView_ECC_SVSE_View_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../opens/libwt/WTable"
class WText;

#include <string>
#include <list>

using namespace std;


#include "gentitle.h"

class CEccListTable;

class CEccSVSEView : public WTable
{
    //MOC: W_OBJECT CEccSVSEView:WTable
    W_OBJECT;
public:
    CEccSVSEView(WContainerWidget *parent = NULL);
public:
    void            refreshTime();
private:
    void            createSVSEList();
    void            createContent();
    void            createStateDesc();
    void            createTitle();

    void            EnumSVSE();

    void            initForm();
private:
    CEccGenTitle    *m_pTitle;
    CEccListTable   *m_pGeneral;
    WTable          *m_pContent;
};

#endif