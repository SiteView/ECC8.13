#include "batchaddform.h"

#include "../../base/splitquery.h"


#include "../../opens/boost/regex.hpp"

int getMonitorType(const char* szValue);

int getMonitorType(string &szValue)
{
    return getMonitorType(szValue.c_str());
}

int getMonitorType(const char* szValue)
{
    int nMonitorType = -1;
    char *pPos = strstr(szValue, "monitortype=");
    if(pPos)
    {
        sscanf(pPos, "monitortype= %d", &nMonitorType);
    }
    return nMonitorType;
}

extern void PrintDebugString(const char * szErrmsg);
extern void PrintDebugString(const string szMsg);

CSVBatchAdd::CSVBatchAdd(WContainerWidget *parent)
:WContainerWidget(parent)
{
    m_pList = NULL;
    m_pSelAll = NULL;
    m_pMonitorName = NULL;

    loadString();
    initForm();
}

void CSVBatchAdd::loadString()
{
    m_szSave = "添加";
    m_szSaveTip = "添加";
    m_szCancel = "取消";
    m_szCancelTip = "取消";
    m_szSelAll = "全选";
}

void CSVBatchAdd::initForm()
{
    CreateList();
    CreateOperater();
}

void CSVBatchAdd::refresh()
{
    char *szQuery = NULL;

    string szIn = "c:$d:$";
    list<string> lsValue ;
    list<string>::iterator lsItem;
    //SV_Split::SplitString(lsValue, szIn, '$');
    SV_Split::SplitString(lsValue, szIn, '$');
    for(lsItem = lsValue.begin(); lsItem != lsValue.end(); lsItem ++)
    {
        PrintDebugString("Item's value:");
        PrintDebugString((*lsItem).c_str());
    }


    szQuery = getenv("QUERY_STRING");

    if(m_pList)
    {
        while(m_pList->numRows() > 1)
        {
            m_pList->deleteRow(m_pList->numRows() - 1);
        }
    }
    if(szQuery)
    {
        m_nMonitorType = getMonitorType(szQuery);
    }
}

void CSVBatchAdd::CreateList()
{
    m_pList = new WTable(this);
    if(m_pList)
    {
        m_pSelAll = new WCheckBox(m_szSelAll, m_pList->elementAt(0, 0));
        m_pMonitorName = new WText("Label", m_pList->elementAt(0, 1));
        //m_pList->GetRow(0)->setContentAlignment(AlignCenter);

        m_pList->setCellPadding(0);
        m_pList->setCellSpaceing(0);

        m_pList->GetRow(0)->setStyleClass("t1title");
        //m_pList->GetRow(0)->setStyleClass("t2title");
        //m_pList->GetRow(0)->setStyleClass("t3title");
    }
}

void CSVBatchAdd::CreateOperater()
{
    WTable * pSub = new WTable(this);
    if(pSub)
    {
        WPushButton * pSave = new WPushButton(m_szSave, pSub->elementAt(0, 0));
        if(pSave)
        {
            pSave->setToolTip(m_szSaveTip);
        }

        WPushButton * pCancel = new WPushButton(m_szCancel, pSub->elementAt(0,1));
        if(pCancel)
        {
            pCancel->setToolTip(m_szCancelTip);
            WObject::connect(pCancel, SIGNAL(clicked()), "window.close();", WObject::ConnectionType::JAVASCRIPT);
        }
    }
}

void CSVBatchAdd::enumAdvParam()
{
}

void CSVBatchAdd::enumBaseParam()
{
}

void CSVBatchAdd::savemonitor()
{
}

bool CSVBatchAdd::saveAdvParam()
{
    bool bNoError = true;
    return bNoError;
}

bool CSVBatchAdd::saveBaseParam()
{
    bool bNoError = true;
    return bNoError;
}


