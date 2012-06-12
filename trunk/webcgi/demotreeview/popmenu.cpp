#include "popmenu.h"
#include "../base/basetype.h"
#include "define.h"
#include "../group/resstring.h"
#include "../group/basefunc.h"

CSVPopMenu::CSVPopMenu():
m_szMenu("")
{
    static const string szTDTR = ("<tr><td style='cursor:pointer;border:outset 1;width:100%;height:21px;background-image:url(../icons/menu0.gif);' "
        "align='center' onmouseout='this.style.backgroundImage=\\\"url(../icons/menu0.gif)\\\"' "
        "onmouseover='this.style.backgroundImage=\\\"url(../icons/menu1.gif)\\\"' onclick='parent.runmenu(\\\"");
    static const string szEndTDTR("</td></tr>");
    static const char szOpt[] = "%d\\\")'>";
    static const char szShow[] = "pop.show(event.clientX - 1,event.clientY - 1,100,rowCount*25,window.document.body);";
    m_szMenu = "<SCRIPT language='JavaScript'>"
        "function showPopMenu(nodeid, nodetype, rowControlString){"
        "document.all(curId).value = nodeid;"
        "document.all(curType).value = nodetype;"
        "var pop=window.createPopup();"
        "pop.document.body.innerHTML=\"<table border='1' width='100%' height='100%' bgcolor='#cccccc' "
        " style='border:1px solid #BBF0F4; background-color:#91BFF0;font-size:12px' cellspacing='0'>";

    int nRowCount = 0;
    char szOperate[12] = {0};
    char szShowText[256] = {0};

    sprintf(szOperate, szOpt, SV_ADD_GROUP);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_AddGroup");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_ADD_DEVICE);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_Right_AddDevice");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_ADD_MONITOR);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_AddMonitor");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_DELETE);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_Delete");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_EDIT);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_Edit");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_COPY);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_Copy");
    m_szMenu += szEndTDTR;
    nRowCount ++;
    
    sprintf(szOperate, szOpt, SV_PAST);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_Paste");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_ENABLE);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;    
    m_szMenu += SVResString::getResString("IDS_Enable_Monitor");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_DISABLE);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;   
    m_szMenu += SVResString::getResString("IDS_DisableMonitor");
    m_szMenu += szEndTDTR;
    nRowCount ++;

    sprintf(szOperate, szOpt, SV_REFRESH);
    m_szMenu += szTDTR;
    m_szMenu += szOperate;
    m_szMenu += SVResString::getResString("IDS_Right_Refresh");
    m_szMenu += szEndTDTR;
    nRowCount ++;
    m_szMenu += "</table>\";";

    m_szMenu += "	var rowObjs=pop.document.body.all[0].rows;"
        "var rowCount=rowObjs.length;"
        "for(var i=0;i<rowObjs.length;i++)"
        "{"
        "var hide=rowControlString.charAt(i)!='1';"
        "if(hide)"
        "rowCount--;"
        "rowObjs[i].style.display=(hide)?\"none\":\"\";"
        "}";

    m_szMenu += "pop.document.oncontextmenu='return false;';";
    m_szMenu += "pop.document.onclick='this->hide()';";
    //sprintf(szShowText, szShow, nRowCount);
    m_szMenu += szShow;
    m_szMenu += "}</SCRIPT>";
    //DumpLog("memu.htm", m_szMenu.c_str(), static_cast<int>(m_szMenu.length()));
}

CSVPopMenu::~CSVPopMenu()
{
}

const string CSVPopMenu::ShowMenu()
{
    return m_szMenu;
}
