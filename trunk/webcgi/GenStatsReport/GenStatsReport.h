#pragma once

#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WTableCell;
class WPushButton;
class WApplication;
class WSVMainTable;
class WSVFlexTable;
class WSVButton;
#include "WSignalMapper"
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;


class CGenStatsReport :	public WContainerWidget
{
//MOC: W_OBJECT CGenStatsReport:WContainerWidget
    W_OBJECT;
public:
    CGenStatsReport(WContainerWidget *parent = 0);
	void refresh();

	~CGenStatsReport(void);
public : //language;

private slots:
	//MOC: SLOT CGenStatsReport::FastGenReport()
    void FastGenReport();
	//MOC: SLOT CGenStatsReport::Close()
	void Close();

public:
	string querystr;
	string szReportDay;
	string szReportWeek;
	string szReportMonth;

	WLineEdit * starttimeedit;
	WLineEdit * endtimeedit;
	WSVMainTable * pMainTable;
	WSVFlexTable * pFlexTable;

	string strBeginTime;
	string strEndTime;
	string strGeneral;
	string strReturn;
	string szCreateTitle;
//	string strGeneralReport;

public:
	void ShowMainTable();	
	
private slots:

	typedef struct _FORM_SHOW_TEXT
    {
		
public:
        _FORM_SHOW_TEXT()
        {
		
        }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

};

