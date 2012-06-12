#pragma once

#include "stdafx.h"
#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WImage;
class WApplication;
class WPushButton;



#include "svdbapi.h"
#include <list>
#include <vector>

#include "../../base/chartdir.h"
#include "CheckBoxTreeView.h"
//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

class CFlexTable;
//new ui class
class WSVMainTable;
class WSVFlexTable;
class WSTreeAndPanTable;

class CTrendReportResult : public WTable
{
	//MOC: W_OBJECT CTrendReport:WTable
	W_OBJECT;
public:
	CTrendReportResult(chen::TTime starttime, chen::TTime endtime, std::string reportname, bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, WContainerWidget *parent );
	void refresh();

	~CTrendReportResult(void);

public : //language;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;

	std::string szInterTime;

	std::string strNameTest;
	//WSignalMapper m_userMapper; 
	//WSignalMapper m_userMapper1;
	std::string strDel;

	chen::TTime m_starttime;
	chen::TTime m_endtime;
	std::string m_reportname;

	std::list<string> grouplist;

	WText * pPageCount;
	WText * pCurrPage;
	int gPageNum;//ҳ����
	int gPageCount;//��ҳ��
	std::string value;

	std::list<int> retstatlist;
	std::list<string> retstrlist;
	std::list<string> rettimelist;
	std::list<string> retmonnamelist;

	std::list<int>::iterator retstatlistitem;
	std::list<string>::iterator retstrlistitem;
	std::list<string>::iterator rettimelistitem;
	std::list<string>::iterator retmonnamelistitem;

	std::list<string> retnormalnamelist;
	std::list<string> retnormaltimelist;
	std::list<string> retnormalstatuslist;

	std::list<string> retdangernamelist;
	std::list<string> retdangertimelist;
	std::list<string> retdangerstatuslist;

	std::list<string> reterrornamelist;
	std::list<string> reterrortimelist;
	std::list<string> reterrorstatuslist;

	std::list<string> retstatuslist;
	int nCurPage;
	int nTotalPage;
	int nPageCount;
	bool bDivide;

	int nCurDataType;

	string strHTimeLabel;
	string strHNameLabel;
	string strHDataLabel;
	string strNormalBtn;
	string strErrorBtn;
	string strWarnningBtn;
	string strBack;
	string strForward;
	string strReturn;
	string strDataTableName;
	string strNoSortRecord;

public:

	
private:
	typedef struct _FORM_SHOW_TEXT
	{
		string szTitle;

		string szRunTitle; string szMonitorTitle; string szErrorTitle; string szDangerTitle;

		string szRunName; string szRunTime;
		string szRunDanger; string szRunError;
		string szRunNew;

		string szMonName; string szMonMeasure;
		string szMonMax; string szMonPer;
		string szMonLast;

		string szErrName; string szErrStartTime;
		//string szErrEndTime; 
		string szErrStatus;

		string szDangerName; string szDangerStartTime;
		//string szDangerEndTime; 
		string szDangerStatus; string szRunClicket;

		string szNormalTitle;

		string szXLSName;
		string szXLSTime;
		string szXLSStatus;
		string szXLSData;

		string szXLSNormal;
		string szXLSError;
		string szXLSDanger;
		string szExcelBut;
	public:
		_FORM_SHOW_TEXT()
		{
			/*
			szTitle = "ͳ�Ʊ���";

			szRunTitle = "�����������";
			szMonitorTitle = "�������ͳ�Ʊ�";
			szErrorTitle = "����(%)";
			szDangerTitle = "Σ��(%)";
			szNormalTitle = "����(%)";

			szRunName = "����";
			szRunTime = "��������ʱ��(%)";
			szRunDanger = "Σ��(%)";
			szRunError = "����(%)";
			szRunNew = "����";
			szRunClicket = "��ֵ";


			szMonName = "����";
			szMonMeasure = "����";
			szMonMax = "���";
			szMonPer = "ƽ��";
			szMonLast = "���һ��";

			szErrName = "����";
			szErrStartTime = "ʱ��";
			//	szErrEndTime = "����ʱ��";
			szErrStatus = "״̬";

			szDangerName = "����";
			szDangerStartTime = "ʱ��";
			//	szDangerEndTime = "����ʱ��";
			szDangerStatus = "״̬";
			*/      }
	}SHOW_TEXT;
	SHOW_TEXT m_formText;

private slots:
	//MOC: SLOT CTrendReport::DataBack()
	void DataBack();
	//MOC: SLOT CTrendReport::DataForward()
	void DataForward();
	//MOC: SLOT CTrendReport::DataReturn()
	void DataReturn();
	//MOC: SLOT CTrendReport::NormalBtn()
	void NormalBtn();
	//MOC: SLOT CTrendReport::ErrorBtn()
	void ErrorBtn();
	//MOC: SLOT CTrendReport::WarnningBtn()
	void WarnningBtn();
	//MOC: SLOT CTrendReport::SaveExcelBtn()
	void SaveExcelBtn();
};

