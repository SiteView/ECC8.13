#ifndef _SiteView_Ecc_Push_Button_H_
#define _SiteView_Ecc_Push_Button_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>

using namespace std;

#include "../../opens/libwt/WTable"

class WText;
class WImage;

class CEccButton : public WTable
{
    //MOC: W_OBJECT CEccButton:WTable
    W_OBJECT;
public:
    CEccButton(string szText, string szToolTip = "", string szImgPath = "", WContainerWidget *parent = NULL);
    virtual void    setText(string szText);
    virtual void setToolTip(const std::string text);
private:
    WText       *m_pButton;
};

class CEccImportButton : public WTable
{
    //MOC: W_OBJECT CEccImportButton:WTable
    W_OBJECT;
public:
    CEccImportButton(string szText, string szToolTip = "", string szImgPath = "", WContainerWidget *parent = NULL);
    virtual void    setText(string szText);
    virtual void setToolTip(const std::string text);
private:
    WText       *m_pButton;
};

#endif
