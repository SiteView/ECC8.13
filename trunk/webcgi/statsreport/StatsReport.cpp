/*************************************************
*  @file StatsReport.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include ".\statsreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"

#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVMainTable.h"
#include <math.h>

#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
typedef void (GenExcelFile)(string name, list<forXLSItem>::iterator xlsListIterator1, list<forXLSItem>::iterator xlsListIterator2);
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

using namespace std;

/***************************************************
������
	str:���滻���ַ���
	old_value:���滻���ַ���
	new_value:�滻���ַ���

���ܣ�
    ��new_value�滻str�е�����old_value�ַ���

����ֵ��
    �滻����ַ���
***************************************************/
string& replace_all_distinct(string& str,
							 const string& old_value,
							 const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++�պ� 2007-10-10+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ͨ�������������ҵ��䷧ֵ                                                                                                            +
//                                                                                                                                    +
//������                                                                                                                              +
//   [in]  hMon     ����������                                                                                                        +
//   [out] bound    ��ֵ                                                                                                              +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void getBoundName(OBJECT hMon, string & bound)
{
	PAIRLIST ParamList;
	bool bFind;
	LISTITEM ParamItem;
	MAPNODE monitorTempNode;
	MAPNODE ma;
	MAPNODE monitorNode;
	OBJECT objTempMonitor = INVALID_VALUE;
	OBJECT objRes=LoadResource("default", "localhost");
	MAPNODE ResNode=GetResourceNode(objRes);
	string getvalue;   //��getvalue�������������������ģ���е�ID

	monitorNode = GetMonitorMainAttribNode(hMon);
	if (FindNodeValue(monitorNode, "sv_monitortype", getvalue) )
	{						
		objTempMonitor = GetMonitorTemplet(atoi(getvalue.c_str())); //������ģ�����
	}

	string strCount, strParamValue, strParamOperate, strParamRelation, strName;
	string strTemp;

	bound = "������[";
	ma = GetMonitorGoodAlertCondition(hMon);
	bFind = FindNodeValue(ma, "sv_conditioncount", strCount);  //��ȡ��ֵ��������Ŀ
	int iCount = atoi(strCount.c_str());
	for (int i=1; i<=iCount; i++)
	{
		string paraIndex;
		char buf[10];
		itoa(i,buf,10);
		paraIndex = buf;
		strTemp = "sv_paramname" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strName);
	
		//�ڼ�����ģ��ķ���ֵ�в��ҷ�ֵ����������
		if( (objTempMonitor != INVALID_VALUE) && FindMTReturnFirst(objTempMonitor,ParamItem))
		{
			while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
			{ 
				ParamList.clear();
				if(::EnumNodeAttrib(monitorTempNode,ParamList))
				{	
					string sReturnName = "", MonitorIDSName ="";
					FindNodeValue(monitorTempNode, "sv_name", sReturnName);
					if(sReturnName == strName)
					{
						FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
						FindNodeValue(ResNode,MonitorIDSName, strName);
						break;
					}
				}
			}
		}
		bound += strName;
		strTemp = "sv_operate" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamOperate); //��ȡ��ֵ�������ţ����硰>����<=����
		bound += strParamOperate;

		strTemp = "sv_paramvalue" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamValue);	//��ȡ��ֵ
		bound += strParamValue;

		if(i<iCount)
		{
			strTemp = "sv_relation" + paraIndex;
			bFind = FindNodeValue(ma, strTemp, strParamRelation); //��ȡ��ϵ��
			bound = bound + " " + strParamRelation + " "; //����ո�ʹ��ʾ������																	
		}
	}
	bound += "]";

	bound += "��Σ�գ�[";
	strCount = strParamValue = strParamOperate = strParamRelation = strName = "";
	iCount = 0;
	ma = GetMonitorWarningAlertCondition(hMon);
	bFind = FindNodeValue(ma, "sv_conditioncount", strCount);  //��ȡ��ֵ��������Ŀ
	iCount = atoi(strCount.c_str());
	for (int i=1; i<=iCount; i++)
	{
		string paraIndex;
		char buf[10];
		itoa(i,buf,10);
		paraIndex = buf;
		strTemp = "sv_paramname" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strName);

		//�ڼ�����ģ��ķ���ֵ�в��ҷ�ֵ����������
		if( (objTempMonitor != INVALID_VALUE) && FindMTReturnFirst(objTempMonitor,ParamItem))
		{
			while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
			{ 
				ParamList.clear();
				if(::EnumNodeAttrib(monitorTempNode,ParamList))
				{	
					string sReturnName = "", MonitorIDSName ="";
					FindNodeValue(monitorTempNode, "sv_name", sReturnName);
					if(sReturnName == strName)
					{
						FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
						FindNodeValue(ResNode,MonitorIDSName, strName);
						break;
					}
				}
			}
		}
		bound += strName;
		strTemp = "sv_operate" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamOperate); //��ȡ��ֵ�������ţ����硰>����<=����
		bound += strParamOperate;

		strTemp = "sv_paramvalue" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamValue);	//��ȡ��ֵ
		bound += strParamValue;

		if(i<iCount)
		{
			strTemp = "sv_relation" + paraIndex;
			bFind = FindNodeValue(ma, strTemp, strParamRelation); //��ȡ��ϵ��
			bound = bound + " " + strParamRelation + " "; //����ո�ʹ��ʾ������																	
		}
	}
	bound += "]";

	bound += "������[";
	strCount = strParamValue = strParamOperate = strParamRelation = strName = "";
	iCount = 0;
	ma = GetMonitorErrorAlertCondition(hMon);
	bFind = FindNodeValue(ma, "sv_conditioncount", strCount);  //��ȡ��ֵ��������Ŀ
	iCount = atoi(strCount.c_str());
	for (int i=1; i<=iCount; i++)
	{
		string paraIndex;
		char buf[10];
		itoa(i,buf,10);
		paraIndex = buf;
		strTemp = "sv_paramname" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strName);

		//�ڼ�����ģ��ķ���ֵ�в��ҷ�ֵ����������
		if( (objTempMonitor != INVALID_VALUE) && FindMTReturnFirst(objTempMonitor,ParamItem))
		{
			while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
			{ 
				ParamList.clear();
				if(::EnumNodeAttrib(monitorTempNode,ParamList))
				{	
					string sReturnName = "", MonitorIDSName ="";
					FindNodeValue(monitorTempNode, "sv_name", sReturnName);
					if(sReturnName == strName)
					{
						FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
						FindNodeValue(ResNode,MonitorIDSName, strName);
						break;
					}
				}
			}
		}
		bound += strName;
		strTemp = "sv_operate" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamOperate); //��ȡ��ֵ�������ţ����硰>����<=����
		bound += strParamOperate;

		strTemp = "sv_paramvalue" + paraIndex;
		bFind = FindNodeValue(ma, strTemp, strParamValue);	//��ȡ��ֵ
		bound += strParamValue;

		if(i<iCount)
		{
			strTemp = "sv_relation" + paraIndex;
			bFind = FindNodeValue(ma, strTemp, strParamRelation); //��ȡ��ϵ��
			bound = bound + " " + strParamRelation + " "; //����ո�ʹ��ʾ������																	
		}
	}
	bound += "]";
}


/*******************************************************************
����:
	szIndex:��ID
	monitorlist:���ؼ����ID

����:
    ��ȡ���µ����м����ID
*******************************************************************/
void EnumGroup(std::string szIndex,
			   std::list<string>& monitorlist)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    std::list<string> monlist;

    if(!szIndex.empty())
    {
        OBJECT group = GetGroup(szIndex);
        if(group != INVALID_VALUE)
        {    
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                
				for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
					std::string lstEntity = *lstItem;
					OBJECT hEntity = GetEntity(lstEntity);
					
					bool bRet = GetSubMonitorsIDByEntity(hEntity, monlist);

					std::list<string>::iterator litem = monlist.begin();
					
					std::list<string>::iterator monitem = monlist.begin();
					std::list<string>::iterator monitoritem = monitorlist.begin();
					bool bMerge = true;
					//�ж������µ��豸LIST�Ƿ�Ϊ��
					if(monitorlist.size() > 0 && monlist.size() > 0)
					{
						string temp = *monitem;
						string temp1= *monitoritem;
						//�жϼ������LIST���Ƿ����
						for(monitoritem = monitorlist.begin(); monitoritem != monitorlist.end(); monitoritem++)
						{					
							temp1 = *monitoritem;
							if(strcmp(temp.c_str(), temp1.c_str()) == 0)	
							{								
								bMerge = false;
								break;
							}
							
						}
					}
					//�����������������
					if(bMerge)
					{
						monitorlist.merge(monlist);										
					}
                }            
            }
            //��������飬�ݹ��ȡ�����µļ����
			if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    EnumGroup(szSubGroupID, monitorlist);
                }                
            }

            CloseGroup(group);
        }        
    }
}


std::string CStatsReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
			strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

void ClearException(double *data, int count)
{
	//�������ȥ���쳣ֵ��ԭ������������3�����������Ϊ�쳣ֵ
				
	if(count > 100)
	{
		float lCount = 0;
		float lAverage = 0;
		double lsCount = 0;
		double lsAverage = 0;
		for(int m = 0; m < count; m++)
		{
			lCount += data[m];
			
		}
		lAverage = lCount / count;

		for(int m = 0; m < count; m++)
		{
			lsCount += (data[m] - lAverage)*(data[m] - lAverage);
		}
		
		lsAverage = sqrt(lsCount/(count - 1))*3;
		

		for(int m = 0; m < count; m++)
		{						
			if(fabs(data[m] - lAverage) > lsAverage)
			{
				OutputDebugString("----------�쳣ֵ--------------\n");
				char buf[256];
				sprintf(buf, "%f", data[m]);
				OutputDebugString(buf);
				//Ϊ�쳣ֵ
				for(int m1 = m; m1 < count - 1; m1++)
				{
					data[m1] = data[m1+1];
					
				}
				count--;
				ClearException(data, count);
			}
			
		}
		
	}
	
}

/***************************************************
������
	starttime:��ʼʱ��
	endtime:��ֹʱ��
	reportname:��������
	bClicket:�Ƿ��г���ֵ
	bListError:�Ƿ��г�����
	bListDanger:�Ƿ��г�Σ��
	bListStatsResult:�Ƿ��г�״̬�ܽ�
	bListImage:�Ƿ��г�ͼ��
	bGenExcel:�Ƿ񵼳�excel�ļ�                //Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ��������   �պ� 2007-08-23
	parent:��������

���ܣ�
	���캯��
****************************************************/
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// CStatsReport::CStatsReport(chen::TTime starttime,
// 						   chen::TTime endtime,
// 						   std::string reportname,
// 						   bool bClicket,
// 						   bool bListError, 
// 						   bool bListDanger, 
// 						   bool bListStatsResult, 
// 						   bool bListImage, 
// 						   string szGraphic,
// 						   WContainerWidget *parent ):WContainerWidget(parent)
CStatsReport::CStatsReport(chen::TTime starttime,
						   chen::TTime endtime,
						   std::string reportname,
						   bool bClicket,
						   bool bListError, 
						   bool bListDanger, 
						   bool bListStatsResult, 
						   bool bListImage, 
						   string szGraphic,
						   bool bGenExcel,
						   WContainerWidget *parent ):WContainerWidget(parent)
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
{
	//Resource
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Total_Report",strMainTitle);
			FindNodeValue(ResNode,"IDS_Total_Report_List",strTitle);
			FindNodeValue(ResNode,"IDS_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Total_Report_Map",strNameUse);
			FindNodeValue(ResNode,"IDS_Edit_Name",strNameEdit);
			FindNodeValue(ResNode,"IDS_Affirm_Delete_User",strDel);
			FindNodeValue(ResNode,"IDS_Time_Period",szInterTime);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Run_Case_Table",m_formText.szRunTitle);
			FindNodeValue(ResNode,"IDS_Alert_Date_Total_Table",m_formText.szMonitorTitle);
			FindNodeValue(ResNode,"IDS_Error_Precent",m_formText.szErrorTitle);
			FindNodeValue(ResNode,"IDS_Danger_Prencet",m_formText.szDangerTitle);
			FindNodeValue(ResNode,"IDS_Normal_Precent",m_formText.szNormalTitle);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szRunName);
			FindNodeValue(ResNode,"IDS_Run_Time_Normal_Precent",m_formText.szRunTime);
			FindNodeValue(ResNode,"IDS_Danger_Prencet",m_formText.szRunDanger);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szRunError);
			FindNodeValue(ResNode,"IDS_Later",m_formText.szRunNew);
			FindNodeValue(ResNode,"IDS_Clique_Value",m_formText.szRunClicket);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szMonName);
			FindNodeValue(ResNode,"IDS_Measure",m_formText.szMonMeasure);
			FindNodeValue(ResNode,"IDS_Max",m_formText.szMonMax);
			FindNodeValue(ResNode,"IDS_Average",m_formText.szMonPer);
			FindNodeValue(ResNode,"IDS_Later_Time",m_formText.szMonLast);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szErrName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szErrStartTime);
			FindNodeValue(ResNode,"IDS_State",m_formText.szErrStatus);
			FindNodeValue(ResNode,"IDS_Name",m_formText.szDangerName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szDangerStartTime);
			FindNodeValue(ResNode,"IDS_State",m_formText.szDangerStatus);
			FindNodeValue(ResNode,"IDS_Normal",m_formText.szNormal);
			FindNodeValue(ResNode,"IDS_Warning",m_formText.szDanger);
			FindNodeValue(ResNode,"IDS_Error",m_formText.szError);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Max_Value",szMaxValue);
			FindNodeValue(ResNode,"IDS_Average_Value",szAverageValue);
			FindNodeValue(ResNode,"IDS_Min_Value",szMinValue);
			
			FindNodeValue(ResNode,"IDS_SiteView_Copyright",strCompany);
		}
	}
/*	//����������ֵ
	strMainTitle ="ͳ�Ʊ���";
	strTitle ="ͳ�Ʊ����б�";
	strLoginLabel = "�� ��";	
	strNameUse = "ͳ�Ʊ���ͼ";
	strNameEdit="�༭����";
	strNameTest="�����Ƽ�";
	strDel=  "ȷ��ɾ��ѡ���û���";
	szInterTime = "ʱ���:";
*/
	m_starttime = starttime;
	m_endtime = endtime;
	m_reportname = reportname;
	szInterTime += starttime.Format();
	szInterTime += "~";
	szInterTime += endtime.Format();
	normalrecnum = 1;
	dangerrecnum = 1;
	errorrecnum = 1;

	szComboGraphic = szGraphic;

	//������
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// 	ShowMainTable(starttime, endtime, reportname, bClicket, bListError,bListDanger, \
// 		bListStatsResult, bListImage);
	ShowMainTable(starttime, endtime, reportname, bClicket, bListError,bListDanger, \
		bListStatsResult, bListImage, bGenExcel);
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
}

//��������
CStatsReport::~CStatsReport(void)
{
	CloseResource(objRes);
}

void CStatsReport::InitPageItemNew(string title, bool bListImage)
{
	m_pMainTable = new WSVMainTable(this, "", false);

	WTable *titleTable = new WTable(m_pMainTable->GetContentTable()->elementAt(1,0));	
	titleTable->elementAt(0,0)->setContentAlignment(AlignCenter | AlignMiddle);
	titleTable->elementAt(1,0)->setContentAlignment(AlignCenter | AlignMiddle);
	pReportTitle = new WText(title, (WContainerWidget*)titleTable->elementAt(0,0));

	WFont font1;
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);




	//����ʱ���
	WText * text1 = new WText(szInterTime, (WContainerWidget*)titleTable->elementAt(1, 0));
	
	std::string linkstr = "<a href='../fcgi-bin/statsreportlist.exe?id=";
	linkstr += title;
	linkstr += "'>";
	linkstr += strReturn;
	linkstr += "</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";

	titleTable->elementAt(2, 0)->setContentAlignment(AlignRight);
	new WText(linkstr,(WContainerWidget*)titleTable->elementAt(2, 0));
	new WText("&nbsp;",(WContainerWidget*)titleTable->elementAt(3, 0));

	m_pUptimeTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(2,0), List, m_formText.szRunTitle, false);  
	if (m_pUptimeTable->GetContentTable() != NULL)
	{
		m_pUptimeTable->AppendColumn(m_formText.szRunName,WLength(40,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");

		m_pUptimeTable->AppendColumn(m_formText.szRunTime,WLength(20,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunDanger,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunError,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunNew,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_pUptimeTable->AppendColumn(m_formText.szRunClicket,WLength(10,WLength::Percentage));
		m_pUptimeTable->SetDataRowStyle("table_data_grid_item_text");
		
	}


	m_pMeasurementTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(3,0), List, m_formText.szMonitorTitle, false);  
	if (m_pMeasurementTable->GetContentTable() != NULL)
	{
		m_pMeasurementTable->AppendColumn(m_formText.szMonName,WLength(40,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonMeasure,WLength(30,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonMax,WLength(10,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonPer,WLength(10,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");

		m_pMeasurementTable->AppendColumn(m_formText.szMonLast,WLength(10,WLength::Percentage));
		m_pMeasurementTable->SetDataRowStyle("table_data_grid_item_text");
	}

	m_pGraphTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(4,0), Blank, "ͼ��", false);  

	pImageTable = new WTable(m_pGraphTable->GetContentTable()->elementAt(0 , 0));
	//���bListImageΪTRUE������ͼƬTABLE
	if(!bListImage)
	{
		pImageTable->hide();
	}
}


/***********************************************************
������
	starttime:��ʼʱ��
	endtime:��ֹʱ��
	reportname:��������
	bClicket:�Ƿ��г���ֵ
	bListError:�Ƿ��г�����
	bListDanger:�Ƿ��г�Σ��
	bListStatsResult:�Ƿ��г�״̬�ܽ�
	bListImage:�Ƿ��г�ͼ��
	bGenExcel:�Ƿ񵼳�excel�ļ�                //Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ��������   �պ� 2007-08-23

	//parent:��������            û���������ȥ����ע�͡� �պ� 2007-08-23

���ܣ�
   ���ɱ���������
***********************************************************/
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// void CStatsReport::ShowMainTable(chen::TTime starttime,
// 								 chen::TTime endtime, 
// 								 std::string reportname, 
// 								 bool bClicket, 
// 								 bool bListError, 
// 								 bool bListDanger, 
// 								 bool bListStatsResult, 
// 								 bool bListImage)
void CStatsReport::ShowMainTable(chen::TTime starttime,
								 chen::TTime endtime, 
								 std::string reportname, 
								 bool bClicket, 
								 bool bListError, 
								 bool bListDanger, 
								 bool bListStatsResult, 
								 bool bListImage,
								 bool bGenExcel)
//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

{	
	WIN32_FIND_DATA fd;
	//��ע�����ȡ��װ·��
	string	szRootPath = GetSiteViewRootPath();
	string szReport = szRootPath;
	szReport += "\\htdocs\\report";
	//�жϱ���洢·���Ƿ���ڣ��������򴴽�
	HANDLE fr=::FindFirstFile(szReport.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szReport.c_str(), NULL);
	}
	
	string szIconPath = szRootPath;
	szIconPath += "\\htdocs\\report\\Images";
	fr=::FindFirstFile(szIconPath.c_str(), &fd);
	//�жϱ���ͼƬ·���Ƿ���ڣ��������򴴽�
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szIconPath.c_str(), NULL);
	}

	new WText("<div id='view_panel' class='panel_view'>", this);

	//�����ɵı����а���basic.js
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	char buf_tmp[4096]={0};
    int nSize =4095;

	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
	string	szExcelPathName = GetSiteViewRootPath() + "\\htdocs\\report\\";


	string szExcelName = starttime.Format();	
	szExcelName += endtime.Format();
	szExcelName = replace_all_distinct(szExcelName, " ", "_");
	szExcelName = replace_all_distinct(szExcelName, ":", "_");

	szExcelName += reportname;

	replace_all_distinct(szExcelName, "*", "_");
	replace_all_distinct(szExcelName, "/", "_");
	replace_all_distinct(szExcelName, "\\", "_");
	replace_all_distinct(szExcelName,"?", "_");
	replace_all_distinct(szExcelName,  "|", "_");
	replace_all_distinct(szExcelName,  "<", "_");
	replace_all_distinct(szExcelName,  ">", "_");
	replace_all_distinct(szExcelName,  ":", "_");
	replace_all_distinct(szExcelName,  "\"", "_");
	replace_all_distinct(szExcelName,  " ", "_");
	replace_all_distinct(szExcelName,  "%20", "_");

	szExcelName += ".xls";
	szExcelName = szExcelPathName + szExcelName;
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

	//�ѱ������еĿո��滻Ϊ%20   --------ע�ʹ���Ӧ���ǡ��ѱ������е�%20�滻Ϊ�ո��Ա��ڡ�reportset.ini��������ȷ�Ľ� �պ� 2007-08-23
	replace_all_distinct(reportname, "%20", " ");
	std::string querystr;	
	int reccount = 0;
	strcpy(buf_tmp , reportname.c_str());
	
	OutputDebugString("----------------CStatsReport 1--------------------\n");

	if(buf_tmp != NULL)
	{
		//ȡ�����Ӧ�����	
		GetMonitorGroup(buf_tmp, grouplist);
	}


	//�°汾ʽ��
	InitPageItemNew(buf_tmp,bListImage);

	//��ʼ��ҳ��Ԫ��
	//InitPageItem(pContainTable, buf_tmp);

	//�����б������
	//AddColum(NULL);
		
	std::list<string>::iterator item;
	int i6 = 1;//��������б�����
	int i1, i2;
	char buf[256];
	char buf1[256];
	
	//����ͼƬTABLE
	//pImageTable = new WTable(pContainTable->elementAt(7 , 0));
	////���bListImageΪTRUE������ͼƬTABLE
	//if(!bListImage)
	//{
	//	pImageTable->hide();
	//}


	//���ñ����˿��롢����
	//pContainTable->elementAt(7, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	int i3 = 0;//ͼƬ�б�����
	int fieldnum = 1;//�������ͳ���б�����
	int gnormalnum = 1;//�����б�����
	int gdangernum = 1;//Σ���б�����
	int gerrornum = 1;//�����б�����
	int tcount = 0;//��¼�ܸ���

	std::list<string> monitorlist;//�����list
	std::list<string>::iterator monitorlistitem;
	std::string bGroupStr = "";

	OutputDebugString("----------------CStatsReport 2--------------------\n");
	for(item = grouplist.begin(); item != grouplist.end(); item++)
	{			
		std::string monitorid = *item;				
		
		//ȡ���������
		OBJECT	hGroup = GetGroup(monitorid);
		std::list<string> monitoridlist;
		std::list<string>::iterator monitoridlistitem;
	
		//������Ч���ж��Ƿ�Ϊ�豸������
		if(hGroup == INVALID_VALUE)
		{
			//ȡ�豸���
			hGroup = GetEntity(monitorid);
			//���豸
			if(hGroup != INVALID_VALUE)
			{		
				//ȡ�豸�µ������Ӽ������monitoridlistΪlist<string>���ͣ�
				bool bRet = GetSubMonitorsIDByEntity(hGroup, monitoridlist);
				
				if(monitoridlist.size() != 0)
				{
					monitoridlistitem = monitoridlist.begin();
					std::string szGmon = *monitoridlistitem;
					for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
						monitorlistitem++)
					{
						std::string tempid = *monitorlistitem;
						std::string tempid1 = *monitoridlistitem;
						//monitorlist�д���monitorid������cont
						if(strcmp( tempid1.c_str(), tempid.c_str()) == 0)
						{
							goto cont;
						}
					}
				/*	for(monitoridlistitem = monitoridlist.begin(); monitoridlistitem != monitoridlist.end(); \
						monitoridlistitem++)
					{					
						std::string itemstr = *monitoridlistitem;			
						//���ݼ����IDȡָ��ʱ�ε�����
						GetMonitorRecord(itemstr, starttime, endtime,bClicket,bListStatsResult, reportname, \
							tcount, i6, i3, fieldnum);
					}				
					*/
					//��monitoridlist��Ͻ�monitorlist,������monitoridlist
					monitorlist.merge(monitoridlist);
				}
			}
			//�Ǽ����
			else
			{		
				//�Ƚ�monitorid�Ƿ���monitorlist��
				for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
					monitorlistitem++)
				{
					std::string tempid = *monitorlistitem;
					//monitorlist�д���monitorid������cont
					if(strcmp( monitorid.c_str(), tempid.c_str()) == 0)
					{
						goto cont;
					}
				}
				//���ݼ����IDȡָ��ʱ�ε�����
				monitorlist.push_back(monitorid);
				//GetMonitorRecord(monitorid, starttime, endtime, bClicket, bListStatsResult,\
					reportname, tcount, i6, i3, fieldnum);
			}
		}
		//����,��δ����Ҫȡ���µ����м����
		else
		{					
			EnumGroup(monitorid, monitorlist);			
		}
		//������ڼ����ID�򷵻�ѭ��
cont:
			;
	}

	OutputDebugString("----------------finish EnumGroup, start GetMonitorRecord--------------------\n");

	for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
		monitorlistitem++)
	{		
		std::string monitorid = *monitorlistitem;
		OutputDebugString("----------------GetMonitorRecord monitor id output--------------------\n");
		OutputDebugString(monitorid.c_str());
		OutputDebugString("\n");

		GetMonitorRecord(monitorid, starttime, endtime, bClicket, bListStatsResult,\
					reportname, tcount, i6, i3, fieldnum);
	}
	
	//rettimelist,retstatlist,retstrlistδʹ�ã�retmonnamelistȡ��һ��ֵ
	rettimelistitem = rettimelist.begin();
	retstatlistitem = retstatlist.begin();
	retstrlistitem = retstrlist.begin();
	retmonnamelistitem = retmonnamelist.begin();
	
	bool bnormal = true; //�Ƿ��г�����
	bool bdanger = true;//�Ƿ��г�Σ��
	bool berror = true;//�Ƿ��г�����
	std::string tempstr ;
	
	string strError,strName,strTime,strState,strWarning;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Error",strError);
			FindNodeValue(ResNode,"IDS_Name",strName);
			FindNodeValue(ResNode,"IDS_Time",strTime);
			FindNodeValue(ResNode,"IDS_State",strState);
			FindNodeValue(ResNode,"IDS_Warning",strWarning);
		}
		CloseResource(objRes);
	}

	bool bTr = false;//�����֮������ʽ�ı仯���׵ס������ף�
	//�г������б�
	if(bListError)
	{

		// m_pErrorTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(5,0), List, "����", false);  

		// ++++++ ��չ�˽�Σ���б�Title�ı�����Ϊ������ɫ�Ĺ��� ++++++
		// 2007/6/27 ����
		// ��Ҫ��css.css�ļ����������¶���
		// .table_title_text_error {
		//		width:100%;
		//		color:#FFF01F;
		//		font-weight:bold;
		// }
		m_pErrorTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(5,0), List, "����", false);  
		// ------ ��չ�˽�Σ���б�Title�ı�����Ϊ������ɫ�Ĺ��� ------

		if (m_pErrorTable->GetContentTable() != NULL)
		{
			m_pErrorTable->AppendColumn("�� ��",WLength(25,WLength::Percentage));
			m_pErrorTable->SetDataRowStyle("table_data_grid_item_img");

			m_pErrorTable->AppendColumn("ʱ ��",WLength(25,WLength::Percentage));
			m_pErrorTable->SetDataRowStyle("table_data_grid_item_img");

			m_pErrorTable->AppendColumn("״ ̬",WLength(55,WLength::Percentage));
			m_pErrorTable->SetDataRowStyle("table_data_grid_item_text");
		}

		//left frame is 80px;
		//new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
		//tempstr = "<tr id='o25' style='text-align:left;text-align:center'><td colspan=3 style='vertical-align:top;font-size:18px;text-align:center;' bgcolor=#ffffff align='center'><b>����</b></td></tr>";
		//new WText(tempstr, this);
		//tempstr = "<tr id='o63' class='t1title' style='vertical-align:top;text-align:left;'>"
		//	"<td id='o64' style='vertical-align:top;text-align:left;'><span id='o65'  >����</span></td>"
		//	"<td id='o66' style='vertical-align:top;text-align:left;'><span id='o67'  >ʱ��</span></td>"
		//	"<td id='o68' style='vertical-align:top;text-align:left;'><span id='o69'  >״̬</span></td></tr>";
		//new WText(tempstr, this);

		int iRow = 1;
		for(retmonnamelistitem = reterrornamelist.begin(), rettimelistitem = reterrortimelist.begin(), retstrlistitem = reterrorstatuslist.begin();\
			retmonnamelistitem != reterrornamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
		{
			m_pErrorTable->InitRow(iRow);
			
			m_pErrorTable->GeDataTable()->elementAt(iRow,0)->setContentAlignment(AlignCenter);
			new WText(*retmonnamelistitem, m_pErrorTable->GeDataTable()->elementAt(iRow,0));

			m_pErrorTable->GeDataTable()->elementAt(iRow,2)->setContentAlignment(AlignCenter);
			new WText(*rettimelistitem, m_pErrorTable->GeDataTable()->elementAt(iRow,2));
			
			m_pErrorTable->GeDataTable()->elementAt(iRow,4)->setContentAlignment(AlignCenter);
			new WText(*retstrlistitem, m_pErrorTable->GeDataTable()->elementAt(iRow,4));
			
			//if(bTr)
			//{
			//	bTr = false;
			//	tempstr = "<tr id='o63' class='tr2' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//else
			//{
			//	bTr = true;
			//	tempstr = "<tr id='o63' class='tr1' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//tempstr += *retmonnamelistitem;
			//tempstr += "</span></td><td id='o66' style='text-align:left;'><span id='o67'  >";
			//tempstr += *rettimelistitem;
			//tempstr += "</span></td><td id='o68' style='text-align:left;'><span id='o69'  >";
			//tempstr += *retstrlistitem;
			//tempstr += "</span></td></tr>";
			//new WText(tempstr, this);

			iRow++;
		}
		//new WText("</tbody></table>", this);
	}

	//�Ƿ��г�Σ���б�
	if(bListDanger)
	{
//		m_pWarnTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(6,0), List, "Σ��", false, 2);

		// ++++++ ��չ�˽�Σ���б�Title�ı�����Ϊ������ɫ�Ĺ��� ++++++
		// 2007/6/27 ����
		// ��Ҫ��css.css�ļ����������¶���
		// .table_title_text_warning {
		//		width:100%;
		//		color:#FFF01F;
		//		font-weight:bold;
		// }
		m_pWarnTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(6,0), List, "Σ��", false);  
		// ------ ��չ�˽�Σ���б�Title�ı�����Ϊ������ɫ�Ĺ��� ------

		if (m_pWarnTable->GetContentTable() !=NULL)
		{
			m_pWarnTable->AppendColumn("�� ��",WLength(25,WLength::Percentage));
			m_pWarnTable->SetDataRowStyle("table_data_grid_item_img");

			m_pWarnTable->AppendColumn("ʱ ��",WLength(25,WLength::Percentage));
			m_pWarnTable->SetDataRowStyle("table_data_grid_item_img");

			m_pWarnTable->AppendColumn("״ ̬",WLength(55,WLength::Percentage));
			m_pWarnTable->SetDataRowStyle("table_data_grid_item_text");
		}

		//new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
		//tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='vertical-align:top;font-size:18px' bgcolor=#ffffff align='center'><b>Σ��</b></td></tr>";
		//new WText(tempstr, this);
		//tempstr = "<tr id='o63' class='t1title' style='vertical-align:top;text-align:left;'>"
		//	"<td id='o64' style='vertical-align:top;text-align:left;'><span id='o65'  >����</span></td>"
		//	"<td id='o66' style='vertical-align:top;text-align:left;'><span id='o67'  >ʱ��</span></td>"
		//	"<td id='o68' style='vertical-align:top;text-align:left;'><span id='o69'  >״̬</span></td></tr>";
		//new WText(tempstr, this);

		int iRow = 1;
		for(retmonnamelistitem = retdangernamelist.begin(), rettimelistitem = retdangertimelist.begin(), retstrlistitem = retdangerstatuslist.begin();\
			retmonnamelistitem != retdangernamelist.end(); retmonnamelistitem++, rettimelistitem++ , retstrlistitem++)
		{
			m_pWarnTable->InitRow(iRow);
			m_pWarnTable->GeDataTable()->elementAt(iRow,0)->setContentAlignment(AlignCenter);
			new WText(*retmonnamelistitem, m_pWarnTable->GeDataTable()->elementAt(iRow,0));

			m_pWarnTable->GeDataTable()->elementAt(iRow,2)->setContentAlignment(AlignCenter);
			new WText(*rettimelistitem, m_pWarnTable->GeDataTable()->elementAt(iRow,2));

			m_pWarnTable->GeDataTable()->elementAt(iRow,4)->setContentAlignment(AlignCenter);
			new WText(*retstrlistitem, m_pWarnTable->GeDataTable()->elementAt(iRow,4));

			//if(bTr)
			//{
			//	bTr = false;
			//	tempstr = "<tr id='o63' class='tr1' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//else
			//{
			//	bTr = true;
			//	tempstr = "<tr id='o63' class='tr2' style='text-align:left;'><td id='o64' style='text-align:left;'><span id='o65'  >";
			//}
			//tempstr += *retmonnamelistitem;
			//tempstr += "</span></td><td id='o66' style='text-align:left;'><span id='o67'  >";
			//tempstr += *rettimelistitem;
			//tempstr += "</span></td><td id='o68' style='text-align:left;'><span id='o69'  >";
			//tempstr += *retstrlistitem;
			//tempstr += "</span></td></tr>";

			//new WText(tempstr, this);
			iRow++;
		}
		//new WText("</tbody></table>", this);
	}

	//Copyright SiteView���
	new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
	//tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='color:blue;font-family:Arial;font-size:3;' bgcolor=#ffffff align='center'>Copyright SiteView</td></tr>";
	tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='color:blue;font-family:Arial;' bgcolor=#ffffff align='center'>";
	tempstr += strCompany; 
	tempstr += "</td></tr>";
	new WText(tempstr, this);
	new WText("</tbody></table>", this);

	new WText("</div>", this);
	AddJsParam("bGeneral","true");
	AddJsParam("uistyle", "viewpanan");
	AddJsParam("fullstyle", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
	if (bGenExcel)
	{
		HINSTANCE hDll = LoadLibrary("genExcel.dll");						
		if (hDll)
		{
			GenExcelFile * func = (GenExcelFile*)::GetProcAddress(hDll, "run");
			list<forXLSItem>::iterator it1 = xlsList.begin();
			list<forXLSItem>::iterator it2 = xlsList.end();
// 			OutputDebugString("\n++++++++++++++++++++++++++++sxc++++++++++++++++++\n");
// 			OutputDebugString(it1->name.c_str());
// 			OutputDebugString("\n++++++++++++++++++++++++++++sxc++++++++++++++++++\n");
			func(szExcelName, it1, it2);
		}
		else
			OutputDebugString("\n����Excel�Ķ�̬���ӿ���ش���\n");
	}
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

}


//��ӿͻ��˽ű�����
void CStatsReport::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}



/***********************************************
������
	pContain:������
���ܣ�
    ���������������������
***********************************************/
void CStatsReport::AddColum(WTable* pContain)
{
	//��������б������
	new WText(m_formText.szRunName, pRunTable->elementAt(0, 0));
	new WText(m_formText.szRunTime, pRunTable->elementAt(0, 1));
	new WText(m_formText.szRunDanger, pRunTable->elementAt(0, 2));
	new WText(m_formText.szRunError, pRunTable->elementAt(0, 3));
	new WText(m_formText.szRunNew, pRunTable->elementAt(0, 4));
	new WText(m_formText.szRunClicket, pRunTable->elementAt(0, 5));	
	pRunTable->setCellSpaceing(0);
	pRunTable->GetRow(0) ->setStyleClass("t1title");	
	
	//������ݱ�����
	new WText(m_formText.szMonName, pMonitorTable->elementAt(0, 0));
	new WText(m_formText.szMonMeasure, pMonitorTable->elementAt(0, 1));
	new WText(m_formText.szMonMax, pMonitorTable->elementAt(0, 2));
	new WText(m_formText.szMonPer, pMonitorTable->elementAt(0, 3));
	new WText(m_formText.szMonLast, pMonitorTable->elementAt(0, 4));	
	pMonitorTable->setCellSpaceing(0);
	pMonitorTable->GetRow(0) ->setStyleClass("t1title");
}


/*****************************************************************
������
	data:����ͼ������
	time:ͼ�κ������ʱ������
	len:���鳤��
	xlabels:�������ǩ��δʹ�ã�
	xscalelen:������̶ȣ�δʹ�ã�
	xStep:�������ǩ����STEP��δʹ�ã�
	ylabels:�������ǩ���飨δʹ�ã�
	yscalelen:��δʹ�ã�
	yScale:���������̶�
	yStep:�������ǩ����STEP��δʹ�ã�
	xLinearScale:��δʹ�ã�
	starttime:ͼ�κ����꿪ʼʱ��
	endtime:ͼ�κ������ֹʱ��
	Title:���˾��б���
	xTitle:������
	filename:����ͼƬ�ļ���

���ܣ�
    �������鴫��ֵ��ʱ������ͼ��������ļ�
*****************************************************************/
void CStatsReport::GenLineImage(double data[],
								double bdata[],
								double time[],
								const int len, 
								char *xlabels[],
								int xscalelen,
								int xStep,
								char *ylabels[],
								int yscalelen,
								int yScale,
								int yStep,
								int xLinearScale, 
								double starttime,
								double endtime,
								char* Title, char* xTitle, char * filename)
{    
	
	{
		wchar_t lpWide[256];//unicode �ַ���

		//300*2��ͼ���ȣ�300���߶ȣ�0xffffff:����ɫ��1���߿�
		XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

		//���ñ�� 55��X��ƫ�� 36��Y��ƫ�� 260*2������� 200���߶� 0XA08040��������COLOR 
		//dashLineColor:���߲�����COLOR 
		c->setPlotArea(55, 36, 260*2, 200, 0xffffff, -1, 0xa08040, c->dashLineColor(0x000000,
			0x000103), c->dashLineColor(0x000000, 0x000103));

		LPCWSTR lpWideCharStr =L"";
		int slen = 256;
		int wlen = 256;
		LPSTR lpMultiByteStr= (LPSTR)malloc(256);
		BOOL buse ;

		//������İ�ECC�����ɱ���ʱͼƬ�������������
		//�պ� 2007-07-16 ������Ŀ�ʼ

		/* ��ԭ���Ĵ���˶ν����޸�
		//��������
		setlocale(LC_CTYPE, ""); 
		*/

		string IniPath("\\data\\svdbconfig.ini");
		IniPath = GetSiteViewRootPath() + IniPath;
		char buf[256]={0};
		GetPrivateProfileString("svdb","DefaultLanguage","",buf,255,IniPath.c_str());
		if (0 == strcmp("chinese", buf))
		{
			setlocale(LC_CTYPE, "chs");
			OutputDebugString("����Ϊ����");
		}
		else 
		{
			setlocale(LC_CTYPE, "");
		}		
		//�պ� 2007-07-16 ������Ľ���

		memset(lpWide, 0, 256);
		
		//char*ת��wchar*
		mbstowcs(lpWide, Title, 256);
		
		//wchar*ת��UTF8
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

		//����ͼ�����
		c->addTitle(lpMultiByteStr,
			"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

		memset(lpMultiByteStr, 0, 256);		
		memset(lpWide, 0, 256);
		mbstowcs(lpWide, xTitle, 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

		//����������
		c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

		lpWideCharStr = L"Copyright SiteView";
		memset(lpMultiByteStr, 0, 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

		//����Y��̶�
		if(yScale <= 10)
		{
			c->yAxis()->setLinearScale(0, yScale + 1);
		}
		else
		{
			c->yAxis()->setLinearScale(0, yScale);
		}

		//���Ӻ�����ʱ��� ������ʱ����Զ�Ӧ
		c->addScatterLayer(DoubleArray(time, len), DoubleArray(data, len),
			"", Chart::PolygonShape(0), 0, 0xffff00);

		string strAreaGraphic,strLineGraphic;
		OBJECT objRes=LoadResource("default", "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				FindNodeValue(ResNode,"IDS_AreaGraphic",strAreaGraphic);
				FindNodeValue(ResNode,"IDS_Line_Graphic",strLineGraphic);
			}
			CloseResource(objRes);
		}
		strAreaGraphic = replace_all_distinct(strAreaGraphic, " ", "");
		strLineGraphic = replace_all_distinct(strLineGraphic, " ", "");

		OutputDebugString("-------------stats report image type---------------\n");
		OutputDebugString(strLineGraphic.c_str());
		OutputDebugString("\n");
		OutputDebugString(szComboGraphic.c_str());
		OutputDebugString("\n");

		//AreaLayer *layer1 = c->addAreaLayer();
		if(strcmp(szComboGraphic.c_str(), strAreaGraphic.c_str()) == 0)
		{
			AreaLayer *layer = c->addAreaLayer();	

			//layer1 ->setXData(DoubleArray(time, len));

			//����ʱ������
			layer ->setXData(DoubleArray(time, len));
			
			//��������
			//layer1->addDataSet(DoubleArray(bdata, len))->setDataColor(
			//0xff0000, 0xff0000);

			layer->addDataSet(DoubleArray(data, len))->setDataColor(
				0x80d080, 0x007000);
		}
		else //(strcmp(szComboGraphic.c_str(), strLineGraphic.c_str()) == 0)
		{
			LineLayer *linelayer = c->addLineLayer(DoubleArray(data, len), 0x007000);
			
			linelayer->setXData(DoubleArray(time, len));
		//	linelayer->addDataSet(DoubleArray(data, len));			
			OutputDebugString("--------------generate line graphic-----------------\n");
		}
			


		//����ͼ��
		c->makeChart(filename);

		//�ͷ�UNICODE�ַ����ڴ�
		free(lpMultiByteStr);

		//�ͷ�CHART�ڴ�
		delete c;
	}
	

}
/*
void CStatsReport::GenLineImage(double data[],
								double bdata[],
								double time[],
								const int len, 
								char *xlabels[],
								int xscalelen,
								int xStep,
								char *ylabels[],
								int yscalelen,
								int yScale,
								int yStep,
								int xLinearScale, 
								double starttime,
								double endtime,
								char* Title, char* xTitle, char * filename)
{    
	wchar_t lpWide[256];//unicode �ַ���

	//300*2��ͼ���ȣ�300���߶ȣ�0xffffff:����ɫ��1���߿�
	XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

	//���ñ�� 55��X��ƫ�� 36��Y��ƫ�� 260*2������� 200���߶� 0XA08040��������COLOR 
	//dashLineColor:���߲�����COLOR 
	c->setPlotArea(55, 36, 260*2, 200, 0xffffff, -1, 0xa08040, c->dashLineColor(0x000000,
        0x000103), c->dashLineColor(0x000000, 0x000103));

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;
	//��������
	setlocale(LC_CTYPE, ""); 

	memset(lpWide, 0, 256);
	
	//char*ת��wchar*
	mbstowcs(lpWide, Title, 256);
	
	//wchar*ת��UTF8
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

	//����ͼ�����
	c->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

	//����������
    c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	lpWideCharStr = L"Copyright SiteView";
	memset(lpMultiByteStr, 0, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

	//����Y��̶�
	if(yScale <= 10)
	{
		c->yAxis()->setLinearScale(0, yScale + 1);
	}
	else
	{
		c->yAxis()->setLinearScale(0, yScale);
	}

	//���Ӻ�����ʱ��� ������ʱ����Զ�Ӧ
	c->addScatterLayer(DoubleArray(time, len), DoubleArray(data, len),
		"", Chart::PolygonShape(0), 0, 0xffff00);

	//AreaLayer *layer1 = c->addAreaLayer();

	AreaLayer *layer = c->addAreaLayer();	

	//layer1 ->setXData(DoubleArray(time, len));

	//����ʱ������
	layer ->setXData(DoubleArray(time, len));
	
	//��������
	//layer1->addDataSet(DoubleArray(bdata, len))->setDataColor(
	//0xff0000, 0xff0000);

	layer->addDataSet(DoubleArray(data, len))->setDataColor(
        0x80d080, 0x007000);
	


	//����ͼ��
    c->makeChart(filename);

	//�ͷ�UNICODE�ַ����ڴ�
	free(lpMultiByteStr);

	//�ͷ�CHART�ڴ�
    delete c;
}
*/
/*********************************************************
������
	hRecSet:��¼���
	monitorname:���������
	retmonnamelist:���������LIST
	
���ܣ�
	ȡ���ݿ�ȫ�ַ�����ʾ��¼��

����ֵ��
    Σ��LIST������LIST
*********************************************************/
void CStatsReport::GetMonitorDataRecStr(RECORDSET hRecSet, 
										std::string monitorname,
										std::list<string> &retmonnamelist, 
										std::list<int> &retstatlist, 
										std::list<string>& retstrlist, 
										std::list<string>& rettimelist)
{
	LISTITEM item;
	RECORD hRec;			
	int stat;
	std::string str;

	//ȡ��һ�����ݼ�¼���
	FindRecordFirst(hRecSet, item);

	//ȡ��һ�����ݼ�¼
	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		//ȡ�ַ���ʾ�ļ�¼
		GetRecordDisplayString(hRec, stat, str);			
		TTime tm;
		//ȡ��¼����ʱ��
		GetRecordCreateTime(hRec,tm);
		//��¼״̬ΪΣ��
		if(stat == 2)
		{
			//����ֵ��retdangerstatuslist
			//���������retdangernamelist
			//����ʱ�䵽retdangertimelist
			retdangernamelist.push_back(monitorname);
			retdangertimelist.push_back(tm.Format());
			retdangerstatuslist.push_back(str);			
		}
		//��¼״̬Ϊ����
		if(stat == 3)
		{
			//����ֵ��reterrorstatuslist
			//���������reterrornamelist
			//����ʱ�䵽reterrortimelist
			reterrornamelist.push_back(monitorname);
			reterrortimelist.push_back(tm.Format());
			reterrorstatuslist.push_back(str);
		}
	}	
}

/*******************************************************
������
	hRecSet����ѯָ����������ݿ���
	fieldname�����ѯ���ֶ���
	fieldtype���ֶ������ͼ�ָ�����������ֵ����
	intlist���ֶ���ΪInt��ʱ���ݴ洢��LIST
	floatlist���ֶ���ΪFloat�����ݴ洢��LIST
	stringlist���ֶ���ΪString�����ݴ洢��LIST
	timelist�������ݶ�Ӧ�ļ�¼����ʱ��LIST
	maxval�����ص����ֵ
	minval�����ص���Сֵ
	perval�����ص�ƽ��ֵ
	lastval�����ص�����ֵ
	reccount�����صļ�¼����

���ܣ�
	�����ݿ���ȡ��¼����ȡ��ָ������
********************************************************/
void CStatsReport::GetMonitorDataRec(RECORDSET hRecSet, 
									 std::string fieldname,
									 std::string fieldtype, 
									 std::list<int> & intlist, 
									 std::list<float> & floatlist,
									 std::list<string> & stringlist,
									 std::list<int> & badlist,//11-10
									 std::list<TTime> & timelist, 
									 float & maxval,
									 float & minval, 
									 float & perval, 
									 float & lastval, 
									 int & reccount)
{
	LISTITEM item;
	RECORD hRec;

	//ȡ��¼���е�һ����¼��OBJECT
	FindRecordFirst(hRecSet, item);
			
	int type;//��¼��������
	int stat;//��¼����״̬
	int iv;//����ֵ
	float fv;//������ֵ
	std::string sv;//�ַ���ֵ

	float countval = 0;//��¼�ۼ��ܺ�
	int itemnum = 0;//��¼����������

	bool bmin = true;//����¼Ϊ��һ����¼ʱ����minval����ǰ��¼ֵ
	bool bLast = true;//��һ����¼��Ϊ����ֵ

	int iBef = 0;
	bool bStat = false;

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)//ȡ��һ����¼�����ж�ѭ��
	{		
		TTime tm;
		iv = 0;
		fv = 0.0;
		
		if(strcmp(fieldtype.c_str(), "Int") == 0)
		{
			iBef = iv;
		}
		else if(strcmp(fieldtype.c_str(), "Float") == 0)
		{
			iBef = fv;
		}
		else
		{
			iBef = 0;
		}

		bool bret = GetRecordValueByField(hRec, fieldname, type, stat, iv, fv, sv);//��ָ���ֶ���ȡ��¼ֵ
		if(stat == 4)//���statΪ4����ֹ״̬
		{
			//������ֵ��0
			if(bLast)
			{
				lastval = 0;
				bLast = false;
			}
		}
		else if((stat != 0) )//��Ϊ��ֹ״̬
		{	
			GetRecordCreateTime(hRec,tm);//ȡ��ǰ��¼ʱ��		
						
			//��monitortemplet��ȡ���ļ�����������ͱȽ���Int��
			if(strcmp(fieldtype.c_str(), "Int") == 0)
			{			
				//��¼״̬��ΪBAD
				if(stat != 5)
				{
					//����ǵ�һ����¼��minval��ֵ
					if(bmin)
					{
						minval = iv;
						bmin = false;
					}
					
					//�ж����ֵ�Ƿ�С�ڵ�ǰֵ������������ֵ��Ϊ��ǰֵ
					if(maxval < iv)
					{
						maxval = iv;
					}

					//�ж���Сֵ�Ƿ���ڵ�ǰֵ�����������Сֵ��Ϊ��ǰֵ
					if(minval > iv)
					{
						minval = iv;
					}
				
					//ʱ����Int��ֵpush_back������һ�£�
					timelist.push_back(tm);
					intlist.push_back(iv);
					
					//�ۼ����ͼ�¼ֵ
					countval += iv;
				}
				else
				{
					
				}

				//�ж��Ƿ�Ϊ����ֵ��Ϊ��һ����¼��
				if(bLast)
				{
					lastval = iv;
					bLast = false;
				}
				
			}
			//��monitortemplet��ȡ���ļ�����������ͱȽ���Float��
			else if(strcmp(fieldtype.c_str(), "Float") == 0)
			{
				//��¼״̬��ΪBAD
				if(stat != 5)
				{
					//����ǵ�һ����¼��minval��ֵ
					if(bmin)
					{
						minval = fv;
						bmin = false;
					}

					//�ж����ֵ�Ƿ�С�ڵ�ǰֵ������������ֵ��Ϊ��ǰֵ
					if(maxval < fv)
					{
						maxval =fv;
					}

					//�ж���Сֵ�Ƿ���ڵ�ǰֵ�����������Сֵ��Ϊ��ǰֵ
					if(minval > fv)
					{
						minval = fv;
					}
				
					//ʱ����Int��ֵpush_back������һ�£�
					timelist.push_back(tm);
					
					floatlist.push_back(fv);
					
					//�ۼӸ����ͼ�¼ֵ
					countval += fv;		
				}
				else
				{					
					
				}
				//�ж��Ƿ�Ϊ����ֵ��Ϊ��һ����¼��
				if(bLast)
				{
					lastval = fv;
					bLast = false;
				}
			}
			//��monitortemplet��ȡ���ļ�����������ͱȽ���String��
			else if(strcmp(fieldtype.c_str(), "String") == 0)
			{
				//ʱ����String��ֵpush_back������һ�£�
				stringlist.push_back(sv);
				timelist.push_back(tm);

				//���ֵ����Сֵ������ֵ����Ϊ0
				minval = 0;
				maxval = 0;
				if(bLast)
				{
					lastval = 0;
					bLast = false;
				}
				
			}

			//if(!bmin)//���BAD��¼��Ϊ��һ���������badlist
			{
				
				//��¼״̬ΪBAD���¼�������ۼ�
				if(stat != 5)
				{
					if(!bStat)
					{
						if(strcmp(fieldtype.c_str(), "Int") == 0)
						{
							badlist.push_back(iv);
						}
						else if(strcmp(fieldtype.c_str(), "Float") == 0)
						{
							int itemp = fv;
							badlist.push_back(itemp);
						}
						else
						{
							badlist.push_back(0);
						}
						
					}
					else
					{
						badlist.push_back(0);
					}

					itemnum++;
					bStat = true;
				}
				else
				{
					itemnum++;
					if(strcmp(fieldtype.c_str(), "Int") == 0)
					{
						intlist.push_back(0);
					}
					else if(strcmp(fieldtype.c_str(), "Float") == 0)
					{
						floatlist.push_back(0);
					}
					else
					{
						stringlist.push_back("0");
					}
					timelist.push_back(tm);
					if(bStat)
					{
						badlist.push_back(iBef);						
						bStat = false;
					}
					//badlist.push_back(0);
				}
			}
		}
				
	}

	//��¼����Ϊ�㣬 ƽ��ֵΪ�㣬�������ۼӺͳ��Լ�¼��������
	if(itemnum == 0)
	{
		perval = 0;
	}
	else
	{
		perval = countval/itemnum;
	}

	//���صļ�¼������
	reccount = itemnum;

}

/****************************************************************
������
	reportname:��������
	grouplist:�顢�豸�������LIST

���ܣ�
    ��reportset.ini��GroupRightȡ�Զ��ŷָ���顢�豸�������
*****************************************************************/
void CStatsReport::GetMonitorGroup(char * reportname,
								   std::list<string> & grouplist)
{
	std::string buf1 = reportname;

	//ȡ id= ��ı�����
	int pos = buf1.find("=", 0);
	std::string querystr = buf1.substr(pos+1, buf1.size() - pos - 1);			

	//ȡGroupRight���µ�ֵ
	std::string defaultret = "error";
	std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "reportset.ini");

	//���ŷָ���顢�豸�����������grouplist
	int pos2 = 0;
	int pos1;		
	while(pos2 >= 0)
	{
		pos1 = pos2;
		pos2 = groupright.find(",", ++pos2 );
		std::string tempstr = groupright.substr(pos1 + 1, pos2 - pos1 - 1);			
		grouplist.push_back(tempstr);			
	}						
}

/****************************************************
������
	table:��һ��TABLE
	title:�������

���ܣ�
    ��ʼ����������б������������
****************************************************/
void CStatsReport::InitPageItem(WTable *table,
								std::string title)
{
	//���TABLE T5��{width:100%;height:100%;}
	WTable * FrameTable = new WTable(this);	
	FrameTable ->setStyleClass("t5");
	
	//������TABLE��������
	WTable * column = new WTable((WContainerWidget*)FrameTable->elementAt(1, 0));
	FrameTable->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);
	column->setStyleClass("StatsTable");	

	std::string linkstr = "<a href='../fcgi-bin/statsreportlist.exe?id=";
	linkstr += title;
	linkstr += "'>";
	linkstr += strReturn;
	linkstr += "</a>";

	WText * ltext = new WText(linkstr, (WContainerWidget*)column->elementAt(0, 0));	
	column->elementAt(0, 0)->setContentAlignment(AlignTop | AlignRight);
	column->elementAt(0, 0)->setStyleClass("t1title");
	ltext->decorationStyle().setForegroundColor(Wt::black);

	//������Ҫ��TABLE����
	pContainTable = new WTable((WContainerWidget*)FrameTable->elementAt(2,0));
	pContainTable ->setStyleClass("t5");

	//�������
	pReportTitle = new WText(title, (WContainerWidget*)pContainTable->elementAt(0, 0));
	pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	WFont font1;
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);

	//����ʱ���
	WText * text1 = new WText(szInterTime, (WContainerWidget*)pContainTable->elementAt(1, 0));
	pContainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	//��������б����
	text1 = new WText(m_formText.szRunTitle, pContainTable->elementAt(2, 0));
	font1.setSize(WFont::Large, WLength(60, WLength::Pixel));
	text1 ->decorationStyle().setFont(font1);
	pContainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);
	pRunTable = new WTable(pContainTable->elementAt(3, 0));

	//��������б�
	pRunTable->setStyleClass("StatsTable");	
	pRunTable->tableprop_ = 2;
	pRunTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(3, 0)->setContentAlignment(AlignTop | AlignCenter);

	//�������б����
	text1 = new WText(m_formText.szMonitorTitle, pContainTable->elementAt(4, 0));
	text1 ->decorationStyle().setFont(font1);
	pContainTable ->elementAt(4, 0) ->setContentAlignment(AlignTop | AlignCenter);

	//�������б�
	pMonitorTable = new WTable(pContainTable->elementAt(5, 0));
	pMonitorTable->setStyleClass("StatsTable");	
	pMonitorTable->tableprop_ = 2;
	pMonitorTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
    pContainTable->elementAt(5, 0)->setContentAlignment(AlignTop | AlignCenter);

	//ͼ�����
	//text1 = new WText("ͼ��", pContainTable->elementAt(6, 0));
	string strChart,strLineGraphic;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Map_Table",strChart);
		}
		CloseResource(objRes);
	}
	text1 = new WText(strChart, pContainTable->elementAt(6, 0));

	text1 -> decorationStyle().setFont(font1);
	pContainTable -> elementAt(6, 0) -> setContentAlignment(AlignTop | AlignCenter);

}

/*****************************************************
������
	reportname:��������
	starttime:��ʼʱ��
	endtime:��ֹʱ��
	value:���������
	fieldlabel:����ֵ�ֶ�
	minval:��Сֵ
	perval:ƽ��ֵ
	maxval:���ֵ
���ܣ�
	д�������ɼ�¼INI�ļ�    
*****************************************************/
void CStatsReport::WriteGenIni(std::string reportname, 
							   std::string starttime,
							   std::string endtime,
							   std::string value,
							   std::string fieldlabel,
							   float minval, 
							   float perval,
							   float maxval)
{
	char buf[256];
	//section�ڸ�ʽ��������$��ʼʱ��$��ֹʱ��$
	std::string section = reportname;
	section += "$";
	section += starttime;
	section += "$";
	section += endtime;
	section += "$";

	//��ֵ��ʽ���������$����ֵ$
	std::string keystr = value;
	keystr += "$";
	keystr += fieldlabel;
	keystr += "$";
	
	std::string valstr ;
	//ֵ��ʽ����Сֵ$ƽ��ֵ$���ֵ$
	memset(buf, 0, 256);
	sprintf(buf, "%0.0f", minval);
	valstr = buf;
	valstr += "$";
	memset(buf, 0, 256);
	sprintf(buf, "%0.0f", perval);
	valstr += buf;
	valstr += "$";
	memset(buf, 0, 256);
	sprintf(buf, "%0.0f", maxval);
	valstr +=buf;
	valstr += "$";

	//��reportgenerate.iniдֵ
	WriteIniFileString(section, keystr, valstr, "reportgenerate.ini");
}

/*****************************************************************
������
	monitorid:�����ID
	starttime:��ʼʱ��
	endtime:��ֹʱ��
	bClicket:�Ƿ�ȡ��ֵ
	bListStatsResult:�Ƿ���ʾͳ�ƽ��
	reportname:��������
	tcount:��¼������
	i6:�����������
	i3:ͼ�����
	fieldnum:����������

���ܣ�
    ȡ�����ʱ���ڵ����ݿ��¼��������������б��������б�
	��ͼ���б�Σ�ռ�¼���б������¼���б�����ʾ
*****************************************************************/
void CStatsReport::GetMonitorRecord(std::string monitorid, 
									chen::TTime starttime, 
									chen::TTime endtime,
									bool bClicket,
									bool bListStatsResult,
									std::string reportname,
									int &tcount,
									int & i6,
									int & i3,
									int & fieldnum)
{
	//���ݺ�ʱ������Ҳ�ɶ�̬���� ����double *data = new double[5000];
	double data[50000];
	double *bdata = new double[50000]; 
	double time[50000];

	char buf[256];
	char buf2[256];	
	LISTITEM item;
	RECORD hRec;
	int normalnum = 0;
	int dangernum = 0;
	int errornum = 0;
	int othernum = 0;
	int stat = 0;
	int perval = 0;
	int laststat = 0;
	std::string dispstr;
	std::list<string> allstrlist;
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
	forXLSItem xlsItem;
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
	int reccount = 0;
	TTime tm;
	bool bStat = true;

	//��������
	OBJECT hMon = GetMonitor(monitorid);

	//ȡ��������ݼ����
	RECORDSET hRecSet = QueryRecords(monitorid, m_starttime, m_endtime);

	size_t countrec;
	//��������ݼ�¼����
	GetRecordCount(hRecSet,countrec);
	tcount += countrec;

	//ȡ��һ����¼���
	FindRecordFirst(hRecSet, item);
		
	//ȡ���ݼ��еļ�¼
	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{				
		//ȡ��¼����ʱ��
		GetRecordCreateTime(hRec,tm);
		//ȡ��¼��ʾ�ַ���
		GetRecordDisplayString(hRec, stat,dispstr);
		
		//����״̬
		if(bStat)
		{
			laststat = stat;
			bStat = false;
		}

		//״̬Ϊ�������ֹ
		if(stat == 1 || stat == 4)
		{
			normalnum++;				
		}
		//Σ��״̬
		else if(stat == 2)
		{
			dangernum++;				
		}
		//����״̬
		else
		{
			errornum++;				
		}
		
		//�ַ���ʾ��¼push_back������
		allstrlist.push_back(dispstr);									
	}		
	
	//����Chart::chartTime��ʽʱ��
	double cstarttime = Chart::chartTime(tm.GetYear(), tm.GetMonth(), tm.GetDay(),\
		tm.GetHour(), tm.GetMinute(), tm.GetSecond());

	//ȡ�����������
	MAPNODE node = GetMonitorMainAttribNode(hMon);

	//sv_name��������ƣ���Ҫ�ж��Ǽ���������飩
	FindNodeValue(node, "sv_name", value);

	//�豸ID
	string strEntity =	FindParentID(monitorid);

	//�豸���
	OBJECT hEntity = GetEntity(strEntity);

	//�豸������
	MAPNODE entitynode = GetEntityMainAttribNode(hEntity);

	//�豸����
	std::string entityvalue;
	FindNodeValue(entitynode, "sv_name", entityvalue);

	std::string hrefstr = "<a href='#"; 
	hrefstr += entityvalue;
	hrefstr += ":";
	hrefstr += value;
	hrefstr += "'>";	
	hrefstr += entityvalue;
	hrefstr += ":";
	hrefstr += value;
	hrefstr += "</a>";

	//����������� ��ʽ�� �豸���������
	//new WText(hrefstr, pRunTable->elementAt(i6, 0));

	m_pUptimeTable->InitRow(i6);

	if(entityvalue.empty() && value.empty())
	{
	}
	else
	{
		m_pUptimeTable->GeDataTable()->elementAt(i6, 0)->tablecellprop = " nowrap";
		m_pUptimeTable->GeDataTable()->elementAt(i6, 0)->setContentAlignment(AlignCenter);
		new WText(hrefstr, m_pUptimeTable->GeDataTable()->elementAt(i6, 0));
	}
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
	xlsItem.name = entityvalue + ":" + value;
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
	
	memset(buf2, 0, 256);
	if((normalnum + dangernum + errornum + othernum) != 0)
	{
		//��������������е�������Σ�ա�����ٷֱȣ�
		perval = normalnum*100/(normalnum + dangernum + errornum + othernum);
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
		xlsItem.normalRunTime = perval;
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
		sprintf(buf2, "%d", perval);

		m_pUptimeTable->GeDataTable()->elementAt(i6, 2)->setContentAlignment(AlignCenter);
		new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 2));
		//new WText(buf2, pRunTable->elementAt(i6, 1));

		m_pUptimeTable->GeDataTable()->elementAt(i6, 4)->setContentAlignment(AlignCenter);
		perval = dangernum*100/(normalnum + dangernum + errornum + othernum);
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
		xlsItem.dangerRunTime = perval;
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
		sprintf(buf2, "%d", perval);
		new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 4));
		//new WText(buf2, pRunTable->elementAt(i6, 2));
		
		m_pUptimeTable->GeDataTable()->elementAt(i6, 6)->setContentAlignment(AlignCenter);
		perval = errornum*100/(normalnum + dangernum + errornum + othernum);
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
		xlsItem.errorRunTime = perval;
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
		sprintf(buf2, "%d", perval);
		new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 6));
		//new WText(buf2, pRunTable->elementAt(i6, 3));
		
		m_pUptimeTable->GeDataTable()->elementAt(i6, 8)->setContentAlignment(AlignCenter);
		//��ʾ���¼�¼��״̬
		switch(laststat)
		{
		case 1:
			//new WText(m_formText.szNormal, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szNormal, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 2:
			//new WText(m_formText.szDanger, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szDanger, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 3:
			//new WText(m_formText.szError, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szError, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 4:
			//new WText(m_formText.szDisable, pRunTable->elementAt(i6, 4));
			new WText(m_formText.szDisable, m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 5:
			//new WText("BAD", pRunTable->elementAt(i6, 4));
			new WText("BAD", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		case 0:
			//new WText("NULL", pRunTable->elementAt(i6, 4));
			new WText("NULL", m_pUptimeTable->GeDataTable()->elementAt(i6, 8));
			break;
		default:
			break;
		}
	}		

	//���������ֵ
	std::list<string> retliststr;
	std::list<string> retlisttype;
	OBJECT hTemplet;
	std::string monitorname;
	MAPNODE objNode;

	
	if(hMon != INVALID_VALUE)
	{			
		std::string getvalue;
		MAPNODE ma=GetMonitorMainAttribNode(hMon);
		
		//monitortemplet ID
		if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
		{						
			//monitortemplet ���
			hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
			MAPNODE node = GetMTMainAttribNode(hTemplet);
			//monitortemplet ��ǩ
			FindNodeValue(node, "sv_label", monitorname);
			
			//���������Ƿ���ʾ��ֵ
			std::string szErrorValue;
			if(bClicket)
			{					
				MAPNODE errorNode = GetMTErrorAlertCondition(hTemplet);
				FindNodeValue(errorNode, "sv_value", szErrorValue);
				//new WText(szErrorValue.c_str(), pRunTable->elementAt(i6, 5));

				m_pUptimeTable->GeDataTable()->elementAt(i6, 10)->setContentAlignment(AlignCenter);
				new WText(buf2, m_pUptimeTable->GeDataTable()->elementAt(i6, 10));
			}
			szErrorValue = "";
		}
		else
		{
			return;
		}
		std::list<int> retstatlist1;
		std::list<string> retstrlist1;
		std::list<string> rettimelist1;
		std::list<string> retmonnamelist1;
	
		//monitortemplet����ֵ
		bool bRet = FindMTReturnFirst(hTemplet, item);
						
		if(bRet)
		{
			std::string fieldlabel;
			std::string fieldname;
			std::string fieldtype;
			
			float maxval = 0.0;
			float maxval1 = 0.0;
			float minval = 0.0;
			float perval = 0.0;
			float lastval = 0.0;

			std::string returnimage = "";
			std::string returnstats = "";
			std::string returndata = "";

			std::string returnequally = "";

			//ѭ��monitortemplet����ֵ
			string szDetail = GetIniFileString(reportname, "Parameter", "", "reportset.ini");
			while( (objNode = FindNext(item)) != INVALID_VALUE )
			{					
				FindNodeValue(objNode, "sv_label", fieldlabel);
				retliststr.push_back(fieldlabel);	
				FindNodeValue(objNode, "sv_type", fieldtype);				
				retlisttype.push_back(fieldtype);
				FindNodeValue(objNode, "sv_name", fieldname);
				fieldlabel = GetLabelResource(fieldlabel);
				
				//ȡ�����������ʾ��
				FindNodeValue(objNode, "sv_drawimage", returnimage);
				FindNodeValue(objNode, "sv_drawtable", returnstats);
				FindNodeValue(objNode, "sv_drawmeasure", returndata);

				returnequally = "";
				bool bRet = false;
				bRet = FindNodeValue(objNode, "sv_equallyimage", returnequally);
				if(!bRet)
				{
					returnequally = "";
				}

				std::string szPrimary = "";
				FindNodeValue(objNode, "sv_primary",szPrimary);
				
				maxval = 0;//���ֵ
				perval = 0;//
				lastval = 0;
				std::list<int> intlist;
				std::list<float> floatlist;
				std::list<string> stringlist;
				std::list<TTime> timelist;
				std::list<int>::iterator intitem;
				std::list<float>::iterator floatitem;
				std::list<string>::iterator stringitem;
				std::list<TTime>::iterator timeitem;

				std::list<int> badlist;
				std::list<int>::iterator baditem;

				
				int count = 0;
				
				//��� �����ʹ����ݿ��м�¼��intlist floatlist stringlist ����
				intlist.clear();
				floatlist.clear();
				stringlist.clear();
				badlist.clear();


				//���ֶ�ȡ�������¼����
				GetMonitorDataRec(hRecSet, fieldname, fieldtype, intlist , floatlist, stringlist,badlist, timelist, maxval, minval, perval, lastval, reccount); 
				
				//�����������ֵ�����ɼ������ͳ�Ƽ�ͼ��				

				
				
				

				/***************************************************************
				���鸳ֵ floatlist�������Ϊ�����ͣ� intlist�������Ϊ�����ͣ� 
				stringlist�������Ϊ�ַ����ͣ� timeitem��ʱ�����飩
				���ݼ��������ֵ����ֻ����һ��������ֵ
				****************************************************************/
				for(floatitem = floatlist.begin(), intitem = intlist.begin(), \
					stringitem = stringlist.begin(),timeitem = timelist.begin(), baditem = badlist.begin(); \
					(timeitem != timelist.end()); floatitem++, intitem++, stringitem++, timeitem++, baditem++)
				{
					//LIST�������ɵ�ǰʱ����ǰ��ΪͼƬ��ʾ������һ�µ���
					TTime ctm = *timeitem;
					time[reccount - 1 - count] = Chart::chartTime(ctm.GetYear(), 
						ctm.GetMonth(), 
						ctm.GetDay(), 
						ctm.GetHour(),
						ctm.GetMinute(),
						ctm.GetSecond());

					if(strcmp(fieldtype.c_str(), "Int") == 0)
					{							
						data[reccount - 1 - count] = *intitem;
					}
					else if(strcmp(fieldtype.c_str(), "Float") == 0)
					{
						data[reccount - 1 - count] = *floatitem;
					}
					else if(strcmp(fieldtype.c_str(), "String") == 0)
					{
						std::string stringitemstr = *stringitem;
						data[reccount - 1 - count] = atof(stringitemstr.c_str());
					}		

					bdata[reccount - 1 - count ] = *baditem;
					count++;						
				}	
				
				//���ݼ�����Ƿ�ʹ���ų��쳣�㷨
				if(strcmp(returnequally.c_str(), "1") == 0)
				{
					//�������ȥ���쳣ֵ��ԭ������������3�����������Ϊ�쳣ֵ
					
					if(count > 100)
					{
						double lMaxVal = 0;
						double lMinVal = 0;

						float lCount = 0;
						float lAverage = 0;
						double lsCount = 0;
						double lsAverage = 0;
						for(int m = 0; m < count; m++)
						{
							lCount += data[m];						
						}
						lAverage = lCount / count;

						for(int m = 0; m < count; m++)
						{
							lsCount += (data[m] - lAverage)*(data[m] - lAverage);
						}
						
						lsAverage = sqrt(lsCount/(count - 1))*3;
						

						for(int m = 0; m < count; m++)
						{						
							if(fabs(data[m] - lAverage) > lsAverage)
							{
								OutputDebugString("----------�쳣ֵ--------------\n");
								char buf[256];
								sprintf(buf, "%f", data[m]);
								OutputDebugString(buf);
								//Ϊ�쳣ֵ
								for(int m1 = m; m1 < count - 1; m1++)
								{
									data[m1] = data[m1+1];								
								}
								m--;
								count--;
							}
							else
							{
								if(data[m] < lMinVal)
								{
									lMinVal = data[m];
								}

								if(data[m] > lMaxVal)
								{
									lMaxVal = data[m];
								}
							}
						}
						maxval = lMaxVal;
						minval = lMinVal;
						lCount = 0;
						for(int m = 0; m < count; m++)
						{
							lCount += data[m];
						}

						perval = lCount/count;
					}
				}
				//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
				xlsItem.max = maxval;
				xlsItem.avg = perval;
				xlsItem.measureName = fieldlabel;
				//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
					
				//�ж��Ƿ���ʾ������ϸ��Ϣ��reportset.ini�е�KEYֵΪParameter��
				if(strcmp(szDetail.c_str(), "Yes") == 0)
				{					
					WriteGenIni(reportname, starttime.Format(), endtime.Format(), value, fieldlabel, minval, perval, maxval);
				}
				else
				{				
					if(strcmp(szPrimary.c_str(), "1") == 0)
					{						
						//дreportgenerate.ini�ļ� �ڱ����б�ʱȡ���ֵ����Сֵ��ƽ��ֵ
						WriteGenIni(reportname, starttime.Format(), endtime.Format(), value, fieldlabel, minval, perval, maxval);
					}
					else
					{
						//���monitortemplete��sv_primaryֵ��Ϊ1�򷵻�ѭ��
						continue;
					}
				}
				/*ClearException(data, count);
				double lMaxVal = 0;
				double lMinVal = data[0];
				double lCount = 0;

				for(int m = 0; m < count; m++)
				{
					if(data[m] < lMinVal)
					{
						lMinVal = data[m];
					}
					if(data[m] > lMaxVal)
					{
						lMaxVal = data[m];
					}
					lCount += data[m];
				}
				maxval = lMaxVal;
				minval = lMinVal;
				perval = lCount/count;
				*/
				std::string imgtabletitle;
				std::string hrefstring;
				//ͼ����ʾ
				if(strcmp(returnimage.c_str(), "1") == 0)
				{
					//�滻�������е������ַ� : < > * ? | \\ /
					replace_all_distinct(reportname, " ", "_");
					replace_all_distinct(reportname, ":", "_");
					replace_all_distinct(reportname, "<", "_");
					replace_all_distinct(reportname, ">", "_");
					replace_all_distinct(reportname, "\\", "_");
					replace_all_distinct(reportname, "/", "_");
					replace_all_distinct(reportname, "*", "_");
					replace_all_distinct(reportname,"?", "_");
					replace_all_distinct(reportname,  "|", "_");

					std::string namebuf;//ͼƬ�ļ�ȫ·��
					std::string namebuf1;//����ͼƬ�ļ�·����ʱstring

					//ȡע����а�װ·��
					string	szRootPath = GetSiteViewRootPath();
					string szIconPath = szRootPath;
					
					szIconPath += "\\htdocs\\report\\Images\\";

					namebuf = szIconPath;					
	
					//ͼƬ·����ʽ�� ��ʼʱ��+��ֹʱ��+�������� ���ո� �� �� �� _ �滻��
					std::string timestr = m_starttime.Format();
					timestr = replace_all_distinct(timestr, ":", "_");
					timestr = replace_all_distinct(timestr, " ", "_");
					namebuf1 = timestr;
					timestr = m_endtime.Format();
					timestr = replace_all_distinct(timestr, ":", "_");
					timestr = replace_all_distinct(timestr, " ", "_");
					namebuf1 += timestr;
											
					std::string namebuf3 = namebuf1;
					
					namebuf3 += reportname;
					namebuf3 += "\\";													

					//����ͼƬ·��
					namebuf += namebuf3;						
					
					//�ж�ͼƬ·���Ƿ���ڣ��������򴴽�
					WIN32_FIND_DATA fd;
					HANDLE fr=::FindFirstFile(namebuf.c_str(),&fd);
					namebuf = replace_all_distinct(namebuf, "#", "_");
					if(!::FindNextFile(fr, &fd))
					{
						CreateDirectory(namebuf.c_str(), NULL);
					}

					namebuf1 += value;
					itoa(rand(), buf, 10);
					namebuf1 += buf;						
					namebuf1 += ".png";												

					//�滻ͼƬ�ļ������е������ַ� : < > * ? | \\ /
					replace_all_distinct(namebuf1, " ", "_");
					replace_all_distinct(namebuf1, ":", "_");
					replace_all_distinct(namebuf1, "<", "_");
					replace_all_distinct(namebuf1, ">", "_");
					replace_all_distinct(namebuf1, "*", "_");
					replace_all_distinct(namebuf1,"?", "_");
					replace_all_distinct(namebuf1,  "|", "_");
					replace_all_distinct(namebuf1, "\\", "_");
					replace_all_distinct(namebuf1, "/", "_");
					replace_all_distinct(namebuf1, "#", "_");

					//����ͼƬ�ļ�ȫ·��
					namebuf += namebuf1;
											
					double cendtime =Chart::chartTime(endtime.GetYear(),
						endtime.GetMonth(),
						endtime.GetDay(), 
						endtime.GetHour(), 
						endtime.GetMinute(),
						endtime.GetSecond());
					
					//�����豸Entity
					imgtabletitle = entityvalue;
					imgtabletitle += ":";

					imgtabletitle += value;
					
					//�豸���������
					hrefstring = imgtabletitle;

					imgtabletitle += "(";
					imgtabletitle += fieldlabel;
					imgtabletitle += ")";						
					imgtabletitle += "\n";
					imgtabletitle += szMaxValue;
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", maxval);
					imgtabletitle += buf2;
					imgtabletitle += szAverageValue;
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", perval);
					imgtabletitle += buf2;
					imgtabletitle += szMinValue;
					memset(buf2, 0, 256);
					sprintf(buf2, "%0.0f", minval);
					imgtabletitle += buf2;											

					//����
					std::string unitstr;
					FindNodeValue(objNode, "sv_unit", unitstr);
					
					//ȡ�ص�λΪ(%)�����ֵΪ100
					if(strcmp(unitstr.c_str(), "(%)") == 0)
					{							
						GenLineImage(data, bdata, time, count, NULL, 100, 10,\
							NULL, 0, 100, 20, count, cstarttime, cendtime,\
							(char*)imgtabletitle.c_str(),\
							(char*)fieldlabel.c_str(),\
							(char*)namebuf.c_str());
					}
					else
					{
						
						GenLineImage(data, bdata, time, count, NULL, 100, 10,\
							NULL, 0, maxval, 20, count, cstarttime, cendtime,\
							(char*)imgtabletitle.c_str(), \
							(char*)fieldlabel.c_str(),\
							(char*)namebuf.c_str());
					}
					
					//�������ͳ�Ʊ���תָ�����ƣ��������������ֵ��
					std::string temptitle = "<a name='" + hrefstring + "'>" + "</a>";						
					new WText(temptitle, (WContainerWidget*)pImageTable->elementAt(i3, 0));
																	
					std::string namebuf2 = "Images/";
					namebuf2 += namebuf3;
					namebuf2 += namebuf1;						

					//�滻HTML��Ƕ���ͼƬ�����е������ַ� : < > * ? |
					replace_all_distinct(namebuf2, ":", "_");
					replace_all_distinct(namebuf2, "<", "_");
					replace_all_distinct(namebuf2, ">", "_");
					replace_all_distinct(namebuf2, "*", "_");
					replace_all_distinct(namebuf2,"?", "_");
					replace_all_distinct(namebuf2,  "|", "_");		
					replace_all_distinct(namebuf2, "#", "_");
					
					new WImage(namebuf2, (WContainerWidget*)pImageTable->elementAt(i3, 0));												
					pImageTable->elementAt(i3, 0) ->setContentAlignment(AlignTop | AlignCenter);

					i3++;	
				}
				//���ͳ����ʾ
				if(bListStatsResult)
				{
					if(strcmp(returnstats.c_str(), "1") == 0)
					{
						//��������ָ��
						std::string firstfield = entityvalue;
						firstfield += value;
						
						std::string hrefstr = "<a href='#";
						hrefstr += hrefstring;
						
						hrefstr += "'>";
						hrefstr += firstfield;
					
						hrefstr += "</a>";

						m_pMeasurementTable->InitRow(fieldnum);
						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0)->tablecellprop = " nowrap";
						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0)->setContentAlignment(AlignCenter);
						new WText(hrefstr, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 0));
						//new WText(hrefstr, pMonitorTable->elementAt(fieldnum, 0));

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 2)->setContentAlignment(AlignCenter);
						new WText(fieldlabel, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 2));
						//new WText(fieldlabel, pMonitorTable->elementAt(fieldnum, 1));
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", maxval);

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 4)->setContentAlignment(AlignCenter);
						new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 4));
						//new WText(buf2, pMonitorTable->elementAt(fieldnum, 2));
						
						memset(buf2, 0, 256);					
						sprintf(buf2, "%0.0f", perval);

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 6)->setContentAlignment(AlignCenter);
						new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 6));
						//new WText(buf2, pMonitorTable->elementAt(fieldnum, 3));
						memset(buf2, 0, 256);
						sprintf(buf2, "%0.0f", lastval);

						m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 8)->setContentAlignment(AlignCenter);
						new WText(buf2, m_pMeasurementTable->GeDataTable()->elementAt(fieldnum, 8));
						//new WText(buf2, pMonitorTable->elementAt(fieldnum, 4));
						fieldnum++;					
					}
				}
				else
				{

				}
			}

			//�ж������Ƿ���ʾ
			if(strcmp(returndata.c_str(), "1") == 0)
			{
				// ++++++ �ڴ���ͱ����б�ļ��������ǰ�渽���豸�� ++++++
				// 2007/6/27 ����

				std::string strMntName = entityvalue;
				strMntName += ":";
				strMntName += value;

				GetMonitorDataRecStr(hRecSet, strMntName, retmonnamelist1,
					retstatlist1, retstrlist1, rettimelist1);

				// ------ �ڴ���ͱ����б�ļ��������ǰ�渽���豸�� ------

				/* // �ڴ���ͱ����б�ļ��������û�а����豸��
				GetMonitorDataRecStr(hRecSet, value, retmonnamelist1, \
					retstatlist1, retstrlist1, rettimelist1);	
				*/
			}
		}		
	}						
	i6++;

	::getBoundName(hMon, xlsItem.bound);

	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
	xlsList.push_back(xlsItem);
	//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

	CloseRecordSet(hRecSet);	

	delete [] bdata;
}


//�ص�����ԭ��
typedef void(*func)(int , char **);

/***************************************************************************************************
����:
	argc:��������
	argv:�Կո�ָ��CHAR����,
	��ʽ:
	��ʼʱ�� ��ֹʱ�� �������� HTML�ļ��� ��ֵ �г����� �г�Σ�� �г�ͳ�ƽ�� �г�ͼƬ
����:
    ����WebSession�Ļص�����
***************************************************************************************************/
void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_Total_Report",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
    //WApplication app(argc, argv);
    //app.setTitle("ͳ�Ʊ���");
	CStatsReport * setform;

	if(argc > 3)
	{
		std::string timestr = argv[1];

		//�ֽ⿪ʼʱ�䴮���쿪ʼʱ��TTIME
		int pos = timestr.find("-", 0);
		std::string tempstr = timestr.substr(0, pos);
		int nYear = atoi(tempstr.c_str());
		int pos1 = timestr.find("-", pos+1);
		tempstr = timestr.substr(pos+1, pos1 - pos - 1 );
		int nMonth = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		int nDay = atoi(tempstr.c_str());		
		pos1 = timestr.find("_", pos + 1);
		tempstr = timestr.substr(pos + 1, pos1 - pos - 1);
		int nHour = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		int nMinute = atoi(tempstr.c_str());
		tempstr = timestr.substr(pos + 1, timestr.size() - pos);
		int nSecond = atoi(tempstr.c_str());

		chen::TTime starttime(nYear, nMonth, nDay, nHour, nMinute, nSecond);

		timestr = argv[2];
		//�ֽ��ֹʱ�䴮�����ֹʱ��TTIME
		pos = timestr.find("-", 0);
		tempstr = timestr.substr(0, pos);
		nYear = atoi(tempstr.c_str());
		pos1 = timestr.find("-", pos+1);
		tempstr = timestr.substr(pos+1, pos1 - pos - 1 );
		nMonth = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		nDay = atoi(tempstr.c_str());
		pos1 = timestr.find("_", pos + 1);
		tempstr = timestr.substr(pos + 1, pos1 - pos - 1);
		nHour = atoi(tempstr.c_str());
		pos = timestr.find("_", pos1 + 1);
		tempstr = timestr.substr(pos1 + 1, pos - pos1 - 1);
		nMinute = atoi(tempstr.c_str());
		tempstr = timestr.substr(pos + 1, timestr.size() - pos);
		nSecond = atoi(tempstr.c_str());

		chen::TTime endtime(nYear, nMonth, nDay, nHour, nMinute, nSecond);

		bool bClicket = true ;
		bool bListError = true ;
		bool bListDanger = true ;
		bool bListStatsResult = true;
		bool bListImage = true;
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
		bool bGenExcel = true;
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
		string szGraphic = "";

		//��ֵ
		if(strcmp(argv[5], "Yes") == 0)
		{
			bClicket = true;
		}
		else
		{
			bClicket = false;
		}

		//�г�����
		if(strcmp(argv[6], "Yes") == 0)
		{
			bListError = true;
		}
		else
		{
			bListError = false;
		}

		//�г�Σ��
		if(strcmp(argv[7], "Yes") == 0)
		{
			bListDanger = true;
		}
		else
		{
			bListDanger = false;
		}

		//�г�ͳ�ƽ��
		if(strcmp(argv[8], "Yes") == 0)
		{
						
			bListStatsResult = true;
		}
		else
		{
			bListStatsResult = false;
		}

		//�г�ͼ��
		if(strcmp(argv[9], "Yes") == 0)
		{
			bListImage = true;
		}
		else
		{
			bListImage = false;
		}

		if(argv[10])
		{
			szGraphic = argv[10];
		}
		else
		{
			szGraphic = "";
		}

		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
		if(strcmp(argv[11], "Yes") == 0)
		{
			bGenExcel = true;
		}
		else
		{
			bGenExcel = false;
		}
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23

		//ʵ����ͳ�Ʊ���
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// 		setform = new CStatsReport(starttime, endtime, argv[3], \
// 			bClicket,bListError, bListDanger,bListStatsResult, bListImage, szGraphic, app.root());
		setform = new CStatsReport(starttime, endtime, argv[3], \
			bClicket,bListError, bListDanger,bListStatsResult, bListImage, szGraphic, bGenExcel, app.root());
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23		
	}
	else
	{
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ŀ�ʼ   �պ� 2007-08-23
// 		setform = new CStatsReport(chen::TTime(2006, 8, 1, 0, 0, 0),\
// 			chen::TTime(2006, 8,16, 0, 0, 0),\
// 			"id=month_report",true, true, true, true, true, "", app.root());
		setform = new CStatsReport(chen::TTime(2006, 8, 1, 0, 0, 0),\
			chen::TTime(2006, 8,16, 0, 0, 0),\
			"id=month_report",true, true, true, true, true, "", false, app.root());
		//Ϊ���Ticket #123(ͳ�Ʊ�����ʽ�޸�-���չ���) ���⣬�޸Ĵ��롣�޸Ľ���  �պ� 2007-08-23
	}
    app.exec();
}

/***********************************************
�������������
***********************************************/
int main(int argc, char *argv[])
{
    func p = usermain;
	if (argc == 1) 
    {
        char buf[256];

		WebSession s("sds", false, true, "2006-7-21 2006-7-22month_report.html");
        s.start(p, argc, argv);
        return 1;
    }
    else if(argc > 3)
    {
		string szRootPath = GetSiteViewRootPath();
		szRootPath += "\\htdocs\\report\\";
        WebSession s("DEBUG", true, true, argv[4], szRootPath);
        s.start(p, argc, argv);
        return 1;
    }

    return 0;
}

