//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SV_WEB_CGI_TASK_LIST_H_
#define _SV_WEB_CGI_TASK_LIST_H_

#if _MSC_VER > 1000
#pragma once
#endif

//////////////////////////////////////////////////////////////////////////////////
// include WT libs
#include <WTable>
#include <WLineEdit>
#include <WComboBox>
#include <WText>
#include <WImage>
#include <WContainerWidget>
//////////////////////////////////////////////////////////////////////////////////
// include stl lib && using namespace std

#include <string>
using namespace std;

class CTaskList : public WTable
{
    //MOC: W_OBJECT CTaskList:WTable
    W_OBJECT;
public:
    CTaskList(WContainerWidget *parent = 0);
    const char * GetTaskTime();
    void Reset();
public signals:
private slots:
private:
    WComboBox * m_pCombo[7];
    WLineEdit * m_pStart[7];
    WLineEdit * m_pEnd[7];

    typedef struct _FORM_SHOW
    {
        string szMon, szTues, szWed, szThurs, szFri, szSat, szSun;
        string szfrom , szTo;
        string szEnable, szDisable;
    };

    _FORM_SHOW m_formText;
private:    
    void AddItem();
};

#endif

//////////////////////////////////////////////////////////////////////////////////
// end file





