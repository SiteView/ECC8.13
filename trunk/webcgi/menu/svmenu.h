#ifndef _SV_MAIN_MENU_H_
#define _SV_MAIN_MENU_H_

#pragma once

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WLength"
#include "../../opens/libwt/WWidget"

#include <string>
#include <list>
#include <map>

using namespace std;

typedef struct SV_MAIN_MENU_ITEM
{
public:
    SV_MAIN_MENU_ITEM():
      m_szIDS(""),
      m_szCmd("")
    {
        m_bIsPop = false;
        m_pMenuText = NULL;
    }

    SV_MAIN_MENU_ITEM(const SV_MAIN_MENU_ITEM &item):
      m_szIDS(item.m_szIDS),
      m_szCmd(item.m_szCmd)
    {
        m_bIsPop = item.m_bIsPop;
        m_pMenuText = item.m_pMenuText;

        list<string>::const_iterator purItem;
        for(purItem = item.m_PurviewList.begin(); purItem != item.m_PurviewList.end(); purItem ++)
            m_PurviewList.push_back((*purItem));
    }    

    ~SV_MAIN_MENU_ITEM(){m_PurviewList.clear();}

    const SV_MAIN_MENU_ITEM &operator=(const SV_MAIN_MENU_ITEM &item)
    {
        m_szIDS = item.m_szIDS;
        m_szCmd = item.m_szCmd;
        m_bIsPop = item.m_bIsPop;
        m_pMenuText = item.m_pMenuText;

        list<string>::const_iterator purItem;
        for(purItem = item.m_PurviewList.begin();purItem != item.m_PurviewList.end(); purItem ++)
            m_PurviewList.push_back((*purItem));
        return *this;
    }
private:
    bool         m_bIsPop;
    string       m_szIDS;
    string       m_szCmd;

    list<string> m_PurviewList;

    WText      * m_pMenuText;

    friend class CSVSubMenu;
    friend class CSVMainMenu;
}MENUITEM;


class CSVSubMenu : public WTable
{
    //MOC: W_OBJECT CSVSubMenu:WTable
    W_OBJECT;
public:
    CSVSubMenu(WContainerWidget *parent = NULL);
private:
    void    loadSubMenuConfig(int nSubMenuID, map<string, string, less<string> > &ResStringMap);
    void    SplitPurview(const char* str, const char* delim, list<string>& results);
    map<int, MENUITEM, less<int> >    m_lsMenuItems;
    
    WText       * m_pTitle;
    WTable      * m_pSubTable;

    string        m_szIDS;
    string        m_szShowSub;

    friend class CSVMainMenu;
};

class CSVMainMenu : public WTable
{
    //MOC: W_OBJECT CSVMainMenu:WTable
    W_OBJECT;
public:
    CSVMainMenu(WContainerWidget *parent = NULL);
    virtual void refresh();
private slots:
    //MOC: SLOT CSVMainMenu::Translate()
    void    Translate();
    //MOC: SLOT CSVMainMenu::ExChange()
    void    ExChange();
    //MOC: SLOT CSVMainMenu::SelMenuItem()
    void    SelMenuItem();
private:
    void    loadStrings();
    void    LoadMenuConfig();
    void    initMenu();
    void    createHideItem();
    
    void    createTransBtn();

    void    changeMenuShowHide();

    bool    isAdmin();
    bool    getUserRight(string &szPurview);
    void    RequestSubItemByQuery(const char *pszQuery);
    void    RequestSubItem();

    void    showhideSubMenu(bool bShow, CSVSubMenu *pSubMenu);

    bool    m_bAdmin;

    string  m_szIDCUser;
    string  m_szIDCPwd;
    string  m_szResLanguage;

    string  m_szUserID;
    string  m_szIDS;

	string strRefresh;
	string strMenuItem;

    int     m_nSubMenuSel;
    int     m_nSubItemSel;
    int     m_nForwardSelMenu;
    int     m_nForwardSelItem;

    map<int , CSVSubMenu*, less<int> >   m_lsSubMenus;
    map<string, string, less<string> >  m_lsResStrings;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WText           * m_pMainTitle;
    WPushButton     * m_pbtnTranslate;
    WPushButton     * m_pbtnExchange;
    WPushButton     * m_pbtnSelMenu;

    WLineEdit       * m_pSubItem;
    WLineEdit       * m_pSubMenu;
};

#endif