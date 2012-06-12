#pragma once

#include ".\hzdlreport.h"
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


class CGenHZDLReport :	public WContainerWidget
{
//MOC: W_OBJECT CGenHZDLReport:WContainerWidget
    W_OBJECT;
public:
    CGenHZDLReport(WContainerWidget *parent = 0);	
	~CGenHZDLReport(void);
	void CGenHZDLReport::ChangeTrendReport(TTime startTime, TTime endTime);
	void ShowMainTable();

private: slots
    void FastGenReport();

public:
	CHZDLReport* m_reportFrame;

	WLineEdit * starttimeedit;
	WLineEdit * endtimeedit;
	WSVMainTable * pMainTable;
	WSVFlexTable * pFlexTable;

	TTime m_startTime;
	TTime m_endTime;

	string strBeginTime;
	string strEndTime;
	string strGeneral;
	string szCreateTitle;	

private:
	void AddJsParam(const std::string name, const std::string value);
};

