#pragma once

#include "WContainerWidget"
class CMainTable;
class CFlexTable;
class WCheckBox;
class WImage;
class WText;
class WLineEdit;
class WPushButton;
class WApplication;
class WSVMainTable;//-------------juxian.zhang
class WSVFlexTable;
class WSVButton;
#include "WSignalMapper"

#include "C:\siteview\Ecc_Common\Svdb\svapi\svdbapi.h"
//#include "../../kennel/svdb/svapi/svdbapi.h"

#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
// include STL Libs & using namespace std;
#include <string>
using namespace std;
//���˼�¼�ṹ
typedef struct _OneRecord
{
	WCheckBox * pCheckBox;
	//�û���
	std::string strUserName;
	WText *pstrUserName;
	WLineEdit * pLineEdit;
	//����ͼ
	WImage * pTuop;
	WImage * pEdit;
}OneRecord,*POneRecord;

class CSimpleReport :	public WContainerWidget
{	
	//MOC: W_OBJECT CSimpleReport:WContainerWidget
	W_OBJECT;
public:
	CSimpleReport(WContainerWidget *parent = 0);

	void refresh();
	void DataUpdate();
	void TableClear();
	
	std::string GetLabelResource(std::string strLabel);
	OBJECT objRes;
	MAPNODE ResNode;


	~CSimpleReport(void);
public : //language;
	std::string strCorporateName;
	std::string strReportTitle;
	std::string strMainTitle; 
	std::string strTitle;
	std::string strLoginLabel;
	std::string strNameUse;
	std::string strNameEdit;
	std::string strNameTest;
	std::string querystr1;
	WSignalMapper m_userMapper; 
	WSignalMapper m_userMapper1;
	std::string strDel;
	
public:
	//WScrollArea * pUserScrollArea;
	CMainTable *pMainTable;
	CFlexTable *pUserTable;
	WTable * pUserListTable;
	WLineEdit *pEditUserName; 
	WSVMainTable * m_pContainTable;//------------------juxian.zhang
	WSVFlexTable * namesTable;
	WSVFlexTable * detTable;
	WSVFlexTable * statTable;
	WSVFlexTable * ImageTable;
	WSVFlexTable * ErrorTable;
	WSVFlexTable * DangerTable;
	WSVFlexTable * NormalTable;
	WSVFlexTable * DisableTable;
	WText * newBottomTitle;
	WText * pCurrName;
	WLineEdit *pCurrEditUserName;

	//stats report variable
	WTable * pContainTable;  
	WTable * pRunTable;
	WTable * pMonitorTable;
	WTable * pErrorTable;
	WTable * pDangerTable;
	WTable * pNormalTable;
	WTable * pDisableTable;

	WTable * pSimpleMonitorTable;
	WTable * pSimpleStatsTable;
	WTable * pImageTable;

	WText * reporttitletext;
	WText * intertimetitle;
	WText * monitorcounttitle;

	WApplication *  appSelf;

	WText * bottomTitle;

	OBJECT hMon;

	std::string szInterTime1;
	std::string szMinValue;
	std::string szAlertCount;
	std::string strNormalCount;
	std::string strDangerCount;
	std::string strErrorCount;
	std::string strDisableCount;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;

	std::list<string> liststr;

public:

	void ShowMainTable();

	void AddColum( list<string>fieldlist, WTable* pContain );
	// �б�
	list<OneRecord> RecordList;
	//�б��еı���

	//������״ͼ��
	//	void GenLineImage(double data[], int len, char * filename);
	void GenLineImage(double data[],  int len, char* xlabels[],int xscalelen, int xStep, string ylabels[], int yscalelen, int yScale, int yStep,char * Title,  char* xTitle, char * filename);
	void GenLineImage1(double data[], double time[], const int len, char *xlabels[], int xlabelslen, int xStep, char *ylabels[], int ylabelslen,  int yScale, int yStep, int xLinearScale, double starttime,double endtime, char* Title, char* xTitle, char * filename);

	void GenPieImage(char * szTitle, char * labels[], double data[], int len, char * filename);

	std::list<OneRecord>::iterator m_pRecordList;

	std::string bStrCurr ;

private slots:
	//MOC: SLOT CSimpleReport::Translate()
	void Translate();
	//MOC: SLOT CSimpleReport::ExChange()
	void ExChange();

private:
	string GetMonitorPropValue(string strId, string strPropName);
	bool GetMonitorParaValueByName( string strID, string strName, string &strRet );

	WPushButton * pTranslateBtn;
	WPushButton * pExChangeBtn;


	typedef struct _FORM_SHOW_TEXT
	{
		string szTitle;

		string szRunTitle; string szMonitorTitle; string szErrorTitle;

		string szRunName; string szRunTime;
		string szRunDanger; string szRunError;
		string szRunNew; 

		string szMonName; string szMonMeasure;
		string szMonMax; string szMonPer;
		string szMonLast;

		string szErrName; string szErrStartTime;
		string szErrEndTime; string szErrStatus;

		string szSimpleMonitorTitle; string szSimpleStatsTitle;
		string szSimpleImageTitle;

		string szSimpleMonitorName; string szSimpleMonitorNormal;
		string szSimpleMonitorDanger; string szSimpleMonitorError;
		string szSimpleMonitorClicket;

		string szSimpleStatsName; string szSimpleStatsReturn;
		string szSimpleStatsMax; string szSimpleStatsPer;

		string szCaption1;

		string szEDNTime; string szEDNName; string szEDNDescription;

		string szSimpleMonitorDisable; string szTimePeriod;

		//IDS_IDC_COPY_RIGHT = �й���ͨ(����)���޹�˾�����зֹ�˾ ��Ȩ����
		string szIDCCopyRight;

	public:
		/*       _FORM_SHOW_TEXT()
		{
		szCaption1 = "�������:0 ������:0 Σ����:0 ������:0";
		szSimpleMonitorTitle = "���";
		szSimpleStatsTitle = "ͳ��";
		szSimpleImageTitle = "ͼ��";

		szTitle = "ͳ�Ʊ���";

		szSimpleMonitorName = "����";
		szSimpleMonitorNormal = "����";
		szSimpleMonitorDanger = "Σ��";
		szSimpleMonitorError = "����";
		szSimpleMonitorDisable = "��ֹ";
		szSimpleMonitorClicket = "��ֵ";

		szSimpleStatsName = "����";
		szSimpleStatsReturn = "����ֵ";
		szSimpleStatsMax = "���ֵ";
		szSimpleStatsPer = "ƽ��ֵ";

		szRunTitle = "�����������";
		szMonitorTitle = "�������ͳ�Ʊ�";
		szErrorTitle = "����";

		szRunName = "����";
		szRunTime = "��������ʱ��";
		szRunDanger = "Σ��";
		szRunError = "����";
		szRunNew = "����";



		szMonName = "����";
		szMonMeasure = "����";
		szMonMax = "���";
		szMonPer = "ƽ��";
		szMonLast = "���һ��";

		szErrName = "����";
		szErrStartTime = "��ʼʱ��";
		szErrEndTime = "����ʱ��";
		szErrStatus = "״̬";

		szEDNTime = "ʱ��";
		szEDNName = "����";
		szEDNDescription = "����";
		}
		*/   }SHOW_TEXT;
		SHOW_TEXT m_formText;

};

