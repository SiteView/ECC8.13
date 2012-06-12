#include "svmenu.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../opens/libwt/WebSession.h"
#include "../base/OperateLog.h"
#define WTGET

const char SV_MENU_INI_FILE[] = "menu.ini";
#include "../../tools/usbdog/doglib/safedog.h"
//const char SV_REQUEST[] = "class='navgeneral' onmouseout='menumouseout(this)' onmouseover='menumouseover(this)'"
 //                         " onclick='SelSubMenu(\"%d\", \"%d\");'";

const char SV_REQUEST[] = " onclick='SelSubMenu(\"%d\", \"%d\")' onmouseout='menumouseout(this)' onmouseover='menumouseover(this)'";

const char POP_WND[] = "var feature = 'dialogWidth:506px;dialogHeight:370px;scroll:no;status:no;resizeable:no;edge:raised';"
		                "window.showModalDialog(\"/fcgi-bin/%s\", \"\", feature);";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const char * szMsg)
{
#ifdef WIN32
    OutputDebugString("Main Menu : ");
    OutputDebugString(szMsg);
    OutputDebugString("\n");
#endif
}

string RandIndex()
{
	unsigned int nPort = 0;
	unsigned int nMin  = 0x4000;
	unsigned int nMax  = 0x7FFF;
	srand((unsigned)time( NULL ));
	nPort = rand();
	nPort = nPort | nMin;
	nPort = nPort & nMax;


	char chItem[32]  = {0};
	sprintf(chItem, "%d", nPort);
	string strIndex = chItem;

	return strIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDebugString(const string & szMsg)
{
    PrintDebugString(szMsg.c_str());
}

CSVMainMenu::CSVMainMenu(WContainerWidget *parent):
WTable(parent),
m_szIDS(""),
m_szUserID(""),
m_szResLanguage("default"),
m_szIDCPwd("localhost"),
m_szIDCUser("default"),
m_nSubMenuSel(-1),
m_nSubItemSel(-1),
m_nForwardSelMenu(-1),
m_nForwardSelItem(-1)
{
//	OutputDebugString("\n--------- Menu init --------------\n");  
	m_pMainTitle = NULL;		//不用了

    m_pbtnExchange = NULL;
    m_pbtnTranslate = NULL;
    m_pbtnSelMenu = NULL;


    m_pSubItem = NULL;
    m_pSubMenu = NULL;
	setStyleClass("menu_top");
	setCellSpaceing(5);

	
    createHideItem();
    LoadMenuConfig();
    loadStrings();
    initMenu();
    createTransBtn();
	
}

void CSVMainMenu::initMenu()
{
    map<int, CSVSubMenu*, less<int> >::iterator subMenu;
    map<int, MENUITEM, less<int> >::iterator menuItem;
    map<string , string, less<string> >::iterator resItem;

	/*
    if(m_pMainTitle)
    {
        resItem = m_lsResStrings.find(m_szIDS);
        if(resItem != m_lsResStrings.end())
            m_pMainTitle->setText(resItem->second);
    }
	*/

    int nRow = 0;
    int nSubMenu = 0, nSubItem = 0;
    for(nSubMenu = 1, subMenu = m_lsSubMenus.begin(); subMenu != m_lsSubMenus.end(); subMenu ++, nSubMenu ++)
    {
        CSVSubMenu *pSubMenu = subMenu->second;
        if(pSubMenu->m_pTitle)
        {
            resItem = m_lsResStrings.find(pSubMenu->m_szIDS);
            if(resItem != m_lsResStrings.end())
			{
                pSubMenu->m_pTitle->setText(resItem->second);
			}
        }

        if(pSubMenu->m_pSubTable)
        {  
            for(nSubItem = 1, menuItem = pSubMenu->m_lsMenuItems.begin(); menuItem != pSubMenu->m_lsMenuItems.end(); menuItem ++, nSubItem ++)
            {
                MENUITEM *pMenuItem = &menuItem->second;
                resItem = m_lsResStrings.find(pMenuItem->m_szIDS);
                if(resItem != m_lsResStrings.end())
                {
                    if(pMenuItem->m_pMenuText == NULL)
                    {
                        nRow = pSubMenu->m_pSubTable->numRows();
                        pMenuItem->m_pMenuText = new WText(resItem->second, pSubMenu->m_pSubTable->elementAt(nRow, 0));
						//pMenuItem->m_pMenuText->setStyleClass("menu_default_td");
                        if(pMenuItem->m_pMenuText && m_pSubItem && m_pSubMenu && m_pbtnSelMenu)
                        {
                            //sprintf(pMenuItem->m_pMenuText->contextmenu_, SV_REQUEST, nSubMenu, nSubItem);
							sprintf(pSubMenu->m_pSubTable->elementAt(nRow, 0)->contextmenu_, SV_REQUEST, nSubMenu, nSubItem);							
							pSubMenu->m_pSubTable->elementAt(nRow, 0)->setStyleClass("menu_default_td");
                        }
                    }
                    else
                    {
                        pMenuItem->m_pMenuText->setText(resItem->second);
                    }
                }
            }
        }
    }
}

void CSVMainMenu::loadStrings()
{
	OBJECT objRes = LoadResource(m_szResLanguage, "localhost");  
	if( objRes != INVALID_VALUE )
	{
		MAPNODE resNode = GetResourceNode(objRes);
        if(resNode != INVALID_VALUE)
        {
            m_lsResStrings["IDS_Translate"] = "";
            m_lsResStrings["IDS_Translate_Tip"] = "";
            m_lsResStrings["IDS_Refresh"] = "";
            m_lsResStrings["IDS_Refresh_Tip"] = "";

            map<string, string, less<string> >::iterator lsItem;
            for(lsItem = m_lsResStrings.begin(); lsItem != m_lsResStrings.end(); lsItem ++)
                FindNodeValue(resNode, lsItem->first, lsItem->second);

			FindNodeValue(resNode,"IDS_Refresh_GUI",strRefresh);
			FindNodeValue(resNode,"IDS_Menu_Item_Reponse",strMenuItem);
       }
        CloseResource(objRes);
    }
}

void CSVMainMenu::LoadMenuConfig()
{
    m_szIDS = GetIniFileString("general", "showtext", "IDS_FunctionTitle", SV_MENU_INI_FILE);
    if(!m_szIDS.empty() && m_szIDS != "error")
        m_lsResStrings[m_szIDS] = "";

    //setStyleClass("navt1");
    int nRow = numRows(); 
    //m_pMainTitle = new WText("", elementAt(nRow, 0));
    //elementAt(nRow, 0)->setStyleClass("menu_font_sel");

    int nSubMenuCount = GetIniFileInt("general", "submenucount", 0, SV_MENU_INI_FILE);
    for(int i = 1; i <= nSubMenuCount; i++)
    {
        nRow = numRows();
        CSVSubMenu  *pSubMenu = new CSVSubMenu(elementAt(nRow, 0));
        if(pSubMenu)
        {
            m_lsSubMenus[i] = pSubMenu;
            pSubMenu->loadSubMenuConfig(i, m_lsResStrings);
        }
		nRow++;
		if(i != nSubMenuCount)
			elementAt(nRow,0)->setStyleClass("menu_space_td");		//分隔线
    }
}

void CSVMainMenu::refresh()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "menu";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string szUserID = GetWebUserID();
    if(!szUserID.empty() && szUserID != m_szUserID)
    {
        m_szUserID = szUserID;
        m_bAdmin = isAdmin();
        changeMenuShowHide();

        m_nSubItemSel = 1;
        //m_nSubMenuSel = 1;
    }
    m_nForwardSelItem = -1;
    m_nForwardSelMenu = -1;
    createTransBtn();
    char szQuery[4096]={0};
    int nSize = 4095;
#ifdef WTGET
    GetEnvironmentVariable( "QUERY_STRING", szQuery, nSize);
#else
 	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(szQuery,tmpquery);
#endif    
	char *pPos = strchr(szQuery, '=');
    if(pPos)
        RequestSubItemByQuery(++ pPos);
    else
        RequestSubItem();

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

void CSVMainMenu::RequestSubItemByQuery(const char *pszQuery)
{
    map<int, CSVSubMenu*, less<int> >::iterator subMenu;
    map<int, MENUITEM, less<int> >::iterator menuItem;

    int nSubMenu = 0, nSubItem = 0;
    for(nSubMenu = 1, subMenu = m_lsSubMenus.begin(); subMenu != m_lsSubMenus.end(); subMenu ++, nSubMenu ++)
    {
        CSVSubMenu *pSubMenu = subMenu->second;
        for(nSubItem = 1, menuItem = pSubMenu->m_lsMenuItems.begin(); menuItem != pSubMenu->m_lsMenuItems.end(); menuItem ++, nSubItem ++)
        {
            MENUITEM *pMenuItem = &menuItem->second;
            if(strstr(pszQuery, pMenuItem->m_szCmd.c_str()))
            {
                if(pMenuItem->m_pMenuText && !pMenuItem->m_bIsPop)
                {
                    m_nForwardSelItem = m_nSubItemSel;
                    m_nForwardSelMenu = m_nSubMenuSel;
                    m_nSubItemSel = nSubItem;
                    m_nSubMenuSel = nSubMenu;
                    
                    //pMenuItem->m_pMenuText->setStyleClass("menu_select_td");		//被选中的菜单式样
					static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->setStyleClass("menu_select_td");
                    string szMsg("parent.document.frames(\"right\").location.replace(\"/fcgi-bin/");
                    szMsg += pszQuery;
					//szMsg += "random=";
					//szMsg += RandIndex();
                    szMsg += "\");";
                    WebSession::js_af_up = szMsg;
                }
                else
                {
                    char chPop[1024]= {0};
                    sprintf(chPop, POP_WND, pszQuery);
                    WebSession::js_af_up = chPop;

                    m_nForwardSelItem = -1;
                    m_nForwardSelMenu = -1;
                }
                break;
            }

        }
        if(menuItem != pSubMenu->m_lsMenuItems.end())
            break;
    }
    subMenu = m_lsSubMenus.find(m_nForwardSelMenu);
    if(subMenu != m_lsSubMenus.end())
    {
        CSVSubMenu *pSubMenu = subMenu->second;
        menuItem = pSubMenu->m_lsMenuItems.find(m_nForwardSelItem);
        if(menuItem != pSubMenu->m_lsMenuItems.end())
        {
            MENUITEM *pMenuItem = &menuItem->second;
            if(pMenuItem->m_pMenuText)
            {
                //pMenuItem->m_pMenuText->setStyleClass("menu_default_td");
				static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->setStyleClass("menu_default_td");
            }
        }
    }
}

void CSVMainMenu::RequestSubItem()
{
    map<int, CSVSubMenu*, less<int> >::iterator subMenu;
    map<int, MENUITEM, less<int> >::iterator menuItem;
    subMenu = m_lsSubMenus.find(m_nForwardSelMenu);
    if(subMenu != m_lsSubMenus.end())
    {
        CSVSubMenu *pSubMenu = subMenu->second;
        menuItem = pSubMenu->m_lsMenuItems.find(m_nForwardSelItem);
        if(menuItem != pSubMenu->m_lsMenuItems.end())
        {
            MENUITEM *pMenuItem = &menuItem->second;
            if(pMenuItem->m_pMenuText)
            {
				pSubMenu->m_pTitle->setStyleClass("menu_font");
                //pMenuItem->m_pMenuText->setStyleClass("menu_default_td");
				static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->setStyleClass("menu_default_td");
            }
        }
    }

    subMenu = m_lsSubMenus.find(m_nSubMenuSel);
    if(subMenu != m_lsSubMenus.end())
    {
        CSVSubMenu *pSubMenu = subMenu->second;		
        menuItem = pSubMenu->m_lsMenuItems.find(m_nSubItemSel);
        if(menuItem != pSubMenu->m_lsMenuItems.end())
        {
            MENUITEM *pMenuItem = &menuItem->second;
            if(pMenuItem->m_pMenuText && !pMenuItem->m_bIsPop)
            {
				pSubMenu->m_pTitle->setStyleClass("menu_font_sel");
                //pMenuItem->m_pMenuText->setStyleClass("menu_select_td");
				static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->setStyleClass("menu_select_td");
                //WebSession::js_af_up = "parent.document.getElementById(\"right\").src=\"/fcgi-bin/" +
                //    pMenuItem->m_szCmd + "\";";
				
				//string szMsg = "random=";
				//szMsg += RandIndex();
                //WebSession::js_af_up = "parent.document.getElementById(\"right\").contentWindow.location.replace(\"/fcgi-bin/" +
                //   pMenuItem->m_szCmd + szMsg + "\");";
                 WebSession::js_af_up = "parent.document.getElementById(\"right\").contentWindow.location.replace(\"/fcgi-bin/" +
                    pMenuItem->m_szCmd + "\");";
           }
            else
            {
                char chPop[1024]= {0};
                sprintf(chPop, POP_WND, pMenuItem->m_szCmd.c_str());
                WebSession::js_af_up = chPop;
                
                m_nSubItemSel = m_nForwardSelItem;
                m_nSubMenuSel = m_nForwardSelMenu;

                m_nForwardSelItem = -1;
                m_nForwardSelMenu = -1;
            }
        }
    }
}

bool CSVMainMenu::isAdmin()
{
    if(GetIniFileInt(m_szUserID , "nAdmin", -1, "user.ini") == 1)
        return true;
    return false;
}

bool CSVMainMenu::getUserRight(string &szPurview)
{     OutputDebugString(("\n!!!!!!!!!!!!!!!!!!!!"+szPurview+"!!!!!!!!!!!!!!\n").c_str());
    if(GetIniFileInt(m_szUserID, szPurview, 0, "user.ini") == 1)
       
	{  
		return true;
	}
    return false;
}

void CSVMainMenu::changeMenuShowHide()
{
    map<int, CSVSubMenu*, less<int> >::iterator subMenu;
    map<int, MENUITEM, less<int> >::iterator menuItem;
    list<string>::iterator purItem;

    //showsub项为1则显示菜单， 否则隐藏(jiangxian)
    SafeDog safedog;
    vector<bool> shows;
    int icount = 0;
    int nRet = safedog.GetMenuShow(shows);

    m_nSubMenuSel = 1;
    for(vector<bool>::iterator it = shows.begin(); it != shows.end(); it ++)
    {
        if( (*it) )
            break;
        m_nSubMenuSel ++;
    }

    bool bShowSubMenu = false;
    for(subMenu = m_lsSubMenus.begin(); subMenu != m_lsSubMenus.end(); subMenu ++)
    {      int tempint=1;
        bShowSubMenu = false;
        CSVSubMenu *pSubMenu = subMenu->second;
        for(menuItem = pSubMenu->m_lsMenuItems.begin(); menuItem != pSubMenu->m_lsMenuItems.end(); menuItem ++)
        {
            MENUITEM *pMenuItem = &menuItem->second;
           
            if(pMenuItem->m_pMenuText)
            {
                static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->hide();
                if(static_cast<int>(pMenuItem->m_PurviewList.size()) > 0 && !m_bAdmin)
                {
                    //for(purItem = pMenuItem->m_PurviewList.begin(); purItem != pMenuItem->m_PurviewList.end(); purItem ++)
                    purItem = pMenuItem->m_PurviewList.begin();
					{   
                       if(tempint++&&getUserRight(*purItem))
						
                        {
                            bShowSubMenu = true;
                            static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->show();
                            break;
                        }

                     }
                }
                else
                {
                    static_cast<WTableCell*>(pMenuItem->m_pMenuText->parent())->show();
                    bShowSubMenu = true;
				    
                }
            }
			//char tt[100];
			//OutputDebugString(_itoa(tempint,tt,10));
        }        

        if(nRet != 0 || pSubMenu->m_szShowSub.compare("error") == 0)
        {
            showhideSubMenu(bShowSubMenu, pSubMenu);
        }
        else
        {
            int nItem = atoi(pSubMenu->m_szShowSub.c_str());
            if(nItem > 0 && nItem < 15 && shows[nItem - 1])
                showhideSubMenu(bShowSubMenu, pSubMenu);
            else
                showhideSubMenu(false, pSubMenu);
        }
    }
}

void CSVMainMenu::showhideSubMenu(bool bShow, CSVSubMenu *pSubMenu)
{
    int nRow = static_cast<WTableCell*>(pSubMenu->parent())->row();
        
    if(nRow < numRows() - 1)
    {
        if(!bShow)
            GetRow(nRow + 1)->hide();//elementAt(nRow + 1, 0)->hide();
        else
            GetRow(nRow + 1)->show();
    }

    if(!bShow)
        GetRow(nRow)->hide();
    else
        GetRow(nRow)->show();
}

void CSVMainMenu::createHideItem()
{   
    string szJavaFun("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>\n");
        
    int nRow = numRows();
    m_pbtnSelMenu = new WPushButton("hide", elementAt(nRow, 0));
    if(m_pbtnSelMenu)
    {
        m_pbtnSelMenu->hide();
		WObject::connect(m_pbtnSelMenu, SIGNAL(clicked()), "showbar();", this, SLOT(SelMenuItem()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
       // WObject::connect(m_pbtnSelMenu, SIGNAL(clicked()),, this, SLOT(SelMenuItem()));
        szJavaFun = szJavaFun + "\n<SCRIPT language='JavaScript'>var mainMenuSelBtn ='" + m_pbtnSelMenu->getEncodeCmd("xclicked()") + "';</SCRIPT>\n";
    }

    //nRow ++;
    m_pSubItem = new WLineEdit("", elementAt(nRow, 0));
    if(m_pSubItem)
    {
        m_pSubItem->hide();
        szJavaFun = szJavaFun + "\n<SCRIPT language='JavaScript'>var mainSubItem ='" + m_pSubItem->formName() + "';</SCRIPT>\n";
    }

    //nRow ++;
    m_pSubMenu = new WLineEdit("", elementAt(nRow, 0));
    if(m_pSubMenu)
    {
        m_pSubMenu->hide();
        szJavaFun = szJavaFun + "\n<SCRIPT language='JavaScript'>var mainSubMenu ='" + m_pSubMenu->formName() + "';</SCRIPT>\n";
    }

    szJavaFun += "<SCRIPT language='JavaScript'>\n"
                "function menumouseover(obj)\n"
                "{\n"
			//	"	 alert(obj.className);"
			//	"	 showbar();"
				"    if (obj.className != 'menu_select_td')\n"
                "        obj.className='menu_hover_td';\n"
                "}"            	
                "function menumouseout(obj)\n"
                "{\n"
			//	"	 alert(obj.className);"
			//	"    hiddenbar();"
				"	if (obj.className != 'menu_select_td')\n"
                "        obj.className='menu_default_td';\n"
                "}\n"
                "</SCRIPT>\n";

    //nRow ++;
    new WText(szJavaFun, elementAt(nRow, 0));
}

void CSVMainMenu::createTransBtn()
{
    map<string , string, less<string> >::iterator resItem;
    int nRow = numRows();
    if(!m_pbtnTranslate)
    {
        m_pbtnTranslate = new WPushButton("", elementAt(nRow, 0));
		if(m_pbtnTranslate)
		{  
            resItem = m_lsResStrings.find("IDS_Translate");
            if(resItem != m_lsResStrings.end())
                m_pbtnTranslate->setText(resItem->second);

            resItem = m_lsResStrings.find("IDS_Translate_Tip");
            if(resItem != m_lsResStrings.end())
                m_pbtnTranslate->setToolTip(resItem->second);

            WObject::connect(m_pbtnTranslate, SIGNAL(clicked()), this, SLOT(Translate()));	
		}
    }
    
    if(!m_pbtnExchange)
    {
        nRow = numRows();
	    m_pbtnExchange = new WPushButton("", elementAt(nRow, 0));
		if(m_pbtnExchange)
		{
            resItem = m_lsResStrings.find("IDS_Refresh");
            if(resItem != m_lsResStrings.end())
                m_pbtnExchange->setText(resItem->second);

            resItem = m_lsResStrings.find("IDS_Refresh_Tip");
            if(resItem != m_lsResStrings.end())
                m_pbtnExchange->setToolTip(resItem->second);

            WObject::connect(m_pbtnExchange, SIGNAL(clicked()), this, SLOT(ExChange()));	
		}
    }
  	if(GetIniFileInt("translate", "translate", 0, "general.ini") == 1)
	//if(true)
	{
        if(m_pbtnTranslate)
            m_pbtnTranslate->show();

        if(m_pbtnExchange)
            m_pbtnExchange->show();
	}
    else
    {
        if(m_pbtnTranslate)
            m_pbtnTranslate->hide();

        if(m_pbtnExchange)
            m_pbtnExchange->hide();
    }
}

void CSVMainMenu::Translate()
{
    WebSession::js_af_up = "showTranslate('menuRes')";
}

void CSVMainMenu::ExChange()
{
    loadStrings();
    initMenu();
}

void CSVMainMenu::SelMenuItem()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "menu";
	LogItem.sHitFunc = "SelMenuItem";
	LogItem.sDesc = strMenuItem;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

    if(m_pSubItem && m_pSubMenu)
    {
        int nSubItem = atoi(m_pSubItem->text().c_str());
        int nSubMenu = atoi(m_pSubMenu->text().c_str());
        if(nSubItem != m_nSubItemSel || nSubMenu != m_nSubMenuSel)
        {
            m_nForwardSelItem = m_nSubItemSel;
            m_nForwardSelMenu = m_nSubMenuSel;
            m_nSubItemSel = nSubItem;
            m_nSubMenuSel = nSubMenu;
            RequestSubItem();
        }
    }

	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
}

CSVSubMenu::CSVSubMenu(WContainerWidget *parent):
WTable(parent),
m_pTitle(NULL),
m_pSubTable(NULL),
m_szIDS(""),
m_szShowSub("")
{  
    setCellPadding(0);
	setCellSpaceing(0);

    int nRow = numRows();
    WTable *pSub = new WTable(elementAt(nRow, 0));
    
    nRow = numRows();
    m_pSubTable = new WTable(elementAt(nRow, 0));
    if(m_pSubTable)
    {
        m_pSubTable->setCellPadding(0);
	    m_pSubTable->setCellSpaceing(0);
    }

    if(pSub)
    {
        nRow = pSub->numRows();
        m_pTitle = new WText("", pSub->elementAt(nRow, 0));
        m_pTitle->setStyleClass("menu_font");

		WImage *pOpenimg = new WImage("/Images/menu_unwrap_l.gif", pSub->elementAt(nRow, 1));	    
		WImage *pCloseimg = new WImage("/Images/menu_pucker_l.gif", pSub->elementAt(nRow, 1));
        pSub->elementAt(nRow, 1)->setContentAlignment(AlignRight);
		pSub->elementAt(nRow, 1)->setStyleClass("menu_img");
        if(pOpenimg && pCloseimg && m_pSubTable)
        {
            string szShow(""), szHide(""), szSubTable("");
            szShow = pCloseimg->formName();
            szHide = pOpenimg->formName();
            szSubTable = m_pSubTable->formName();

            string szShowText = "onclick='showsubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='display:none;cursor:pointer'";
            string szHideText = "onclick='hidesubtable(\"" + szShow + "\", \"" + szHide + "\", \"" + szSubTable + "\")' " + "style='cursor:pointer'";
            sprintf(pOpenimg->contextmenu_, szShowText.c_str());
            sprintf(pCloseimg->contextmenu_, szHideText.c_str());            
        }
    }
}

void CSVSubMenu::loadSubMenuConfig(int nSubMenuID, map<string, string, less<string> >&ResStringMap)
{
    char chSection[32] = {0}, chKey[32] = {0};
    sprintf(chSection, "submenu%d", nSubMenuID);

    m_szShowSub = GetIniFileString(chSection, "showsub", "error", SV_MENU_INI_FILE);

    m_szIDS = GetIniFileString(chSection, "showtext", "", SV_MENU_INI_FILE);
    if(!m_szIDS.empty() && m_szIDS != "error")
        ResStringMap[m_szIDS] = "";

    int nSubItemCount = GetIniFileInt(chSection, "itemcount", 0, SV_MENU_INI_FILE);
    
    string szSubSection("");
    for(int i = 1; i <= nSubItemCount; i++)
    {
        MENUITEM subItem;
        sprintf(chKey, "subitem%d", i);
        szSubSection = GetIniFileString(chSection, chKey, "", SV_MENU_INI_FILE);
        if(!szSubSection.empty() && szSubSection != "error")
        {
            subItem.m_szCmd = GetIniFileString(szSubSection, "exe_cmd", "", SV_MENU_INI_FILE);
            subItem.m_szIDS = GetIniFileString(szSubSection, "showtext", "", SV_MENU_INI_FILE);
            if(!subItem.m_szIDS.empty() && subItem.m_szIDS != "error")
                ResStringMap[subItem.m_szIDS] = "";

            string szPurview(GetIniFileString(szSubSection, "purview", "", SV_MENU_INI_FILE));
            if(!szPurview.empty() && szPurview != "error")
                SplitPurview(szPurview.c_str(), ",", subItem.m_PurviewList);

            if(GetIniFileInt(szSubSection, "ispop", 0, SV_MENU_INI_FILE) == 1)
                subItem.m_bIsPop = true;
        }
        m_lsMenuItems[i] = subItem;
    }
}

void CSVSubMenu::SplitPurview(const char* str, const char* delim, list<string>& results)
{
    const char* pstr = str;
    const char* r = NULL;
    r = strstr(pstr, delim);
    int dlen = static_cast<int>(strlen(delim));
    while( r != NULL )
    {
        char* cp = new char[(r-pstr)+1];
        memcpy(cp, pstr, (r-pstr));
        cp[(r-pstr)] = '\0';
        if( strlen(cp) > 0)
        {
            string s(cp);
            results.push_back(s);
        }
        delete[] cp;
        pstr = r + dlen;
        r = strstr(pstr, delim);
    }
    if( strlen(pstr) > 0)
    {
        results.push_back(string(pstr));
    }
}
