/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SV_SE_VIEW_H_
#define _SV_SE_VIEW_H_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WSignalMapper"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "showtable.h"
#include "../svtable/SVTable.h"
#include "../demotreeview/define.h"
#include "../userright/user.h"

#include "basefunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SVSEView : public WTable
{
    //MOC: W_OBJECT SVSEView:WTable
    W_OBJECT;
public:
    SVSEView(WContainerWidget* parent = NULL, CUser * pUser = NULL, string szIDCUser = "default", string szIDCPwd = "localhost");
    void EditSEView(string &szName, string &szIndex);
    void SetUserPwd(string &szUser, string &szPwd);
    void refreshSElist();
    void setCurrentTime(const char* pszTime);
    void setCurrentTime(const string &szTime);
public signals:
    //MOC: SIGNAL SVSEView::showSVSE(string)
    void showSVSE(string szSEID);
    //MOC: SIGNAL SVSEView::EditSEByID(string)
    void EditSEByID(string szSEID);
private slots:
    //MOC: SLOT SVSEView::enterSVSE(const std::string)
    void enterSVSE(const std::string szSEID);
    //MOC: SLOT SVSEView::EditSE(const std::string szSEID)
    void EditSE(const std::string szSEID);
private:
    string  m_szIDCUser;
    string  m_szIDCPwd;
    CUser   * m_pSVUser;
    void initForm();
    void createTitle();
    void createSEList();
    void enumSVSE();
    void addSVSEList(string &szName,string &szIndex);
    void editSVSEList(string &szName,string &szIndex);

    WTable      *  m_pSEList;
    WPushButton *  m_pBtnHideDel;
    WText  * m_pTime;
    WSignalMapper m_wNameMapper;
    WSignalMapper m_wEditMapper;

    SVTable    m_svSEList;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
