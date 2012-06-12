/*************************************************
*  @file StatsReport.h
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/
#pragma once

#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WImage;
class WSVMainTable;
class WSVFlexTable;

class WApplication;
class WPushButton;
#include "WSignalMapper"
#include "svdbapi.h"
#include <list>
#include <vector>
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
#include "excelItem.h"
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
#include "include\chartdir.h"

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;

class CStatsReport :	public WContainerWidget
{
//MOC: W_OBJECT CStatsReport:WContainerWidget
    W_OBJECT;
public:
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// 	CStatsReport(chen::TTime starttime, chen::TTime endtime, std::string reportname, \
// 		bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult,\
// 		bool bListImage,string szGraphic, WContainerWidget *parent );
	CStatsReport(chen::TTime starttime, chen::TTime endtime, std::string reportname, \
		bool bClicket ,bool bListError, bool bListDanger, bool bListStatsResult,\
		bool bListImage,string szGraphic, bool bGenExcel, WContainerWidget *parent );
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

	void GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname, \
		std::string fieldtype, std::list<int> & intlist, \
		std::list<float> & floatlist, std::list<string> & stringlist, std::list<int> & badlist,\
		std::list<TTime> & timelist,\
		float & maxval, float & minval, float & perval, float & lastval, int &reccount);

	void GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, \
		std::list<string> & retmonnamelist, \
		std::list<int> & retstatlist, std::list<string> &retstrlist, std::list<string> &rettimelist);

	void GetMonitorRecord(std::string monitorid, chen::TTime starttime, chen::TTime endtime,\
		bool bClicket, bool bListStatsResult, std::string reportname, \
		int &tcount, int &i6, int & i3, int & fieldnum);

	void CStatsReport::enumMonitor(string &szIndex);

	~CStatsReport(void);
	
public : //language;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;
	std::string szInterTime;
	std::string strNameTest;
	WSignalMapper m_userMapper; 
	WSignalMapper m_userMapper1;
	std::string strDel;
	chen::TTime m_starttime;
	chen::TTime m_endtime;
	std::string m_reportname;
	std::list<string> grouplist;
	std::string value;
	std::string strCompany;

	OBJECT objRes;
	MAPNODE ResNode;
	std::string GetLabelResource(std::string strLabel);

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
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
	list<forXLSItem> xlsList;
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
	
	std::string strReturn;
	string szMaxValue;
	string szAverageValue;
	string szMinValue;

	string szComboGraphic;
public:
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	CFlexTable *pUserTable;
	WTable * pUserListTable;
	WLineEdit *pEditUserName; 

	WText * pCurrName;
	WLineEdit *pCurrEditUserName;
	WText * pReportTitle;

	//stats report variable
	WTable * pContainTable;
	WTable * pRunTable;
	WTable * pMonitorTable;
	WTable * pErrorTable;
	WTable * pDangerTable;
	WTable * pImageTable;
	WTable * pNormalTable;

	WTable * pOtherTable;

	WImage * pPrevImg;
	WImage * pNextImg;
	WImage * pGoPageImg;
	WLineEdit * pGoPageEdit;

	int normalrecnum;
	int dangerrecnum;
	int errorrecnum;

	WSVMainTable *m_pMainTable;
	WSVFlexTable *m_pUptimeTable;
	WSVFlexTable *m_pMeasurementTable;
	WSVFlexTable *m_pGraphTable;
	WSVFlexTable *m_pErrorTable;
	WSVFlexTable *m_pWarnTable;

	void InitPageItemNew(string title,bool bListImage);
	void AddJsParam(const std::string name, const std::string value);

public:

	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// 	void ShowMainTable(chen::TTime starttime, chen::TTime endtime, std::string reportname,\
// 		bool bClicket, bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage);
	void ShowMainTable(chen::TTime starttime, chen::TTime endtime, std::string reportname,\
		bool bClicket, bool bListError, bool bListDanger, bool bListStatsResult, bool bListImage, bool bGenExcel);
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

	void AddColum( WTable* pContain );


	//�б��еı���

	//������״ͼ��
	void GenLineImage(double data[], double bdata[], double time[], const int len, char *xlabels[],\
		int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep,\
		int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);

	std::string bStrCurr ;
private:
	void GetMonitorGroup(char * reportname, std::list<string> & grouplist);

	void InitPageItem(WTable * table, std::string title);

	void WriteGenIni(std::string reportname, std::string starttime,std::string endtime,\
		std::string value,std::string fieldlabel, float minval, float perval,float maxval);

private slots:

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
		string szErrStatus;
		string szDangerName; string szDangerStartTime;
		string szDangerStatus; string szRunClicket;		
		string szNormalTitle;
		string szNormal;
		string szDanger;
		string szError;
		string szDisable;
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
			szErrStatus = "״̬";
			szDangerName = "����";
			szDangerStartTime = "ʱ��";		
			szDangerStatus = "״̬";
 */       }
    }SHOW_TEXT;
    SHOW_TEXT m_formText;

};

