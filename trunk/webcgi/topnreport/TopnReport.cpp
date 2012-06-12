/*************************************************
*  @file TopnReport.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/

#include ".\topnreport.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"

#include <math.h>

#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
#include "WPushButton"

#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"


/***************************************************
参数：
	str:需替换的字符串
	old_value:被替换的字符串
	new_value:替换的字符串

功能：
    用new_value替换str中的所有old_value字符串

返回值：
    替换后的字符串
***************************************************/
string& replace_all_distinct(string& str,const string& old_value,const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

/****************************************************
参数:
	array:图形数据数组
	labels:监测器名称数组
	entity:设备数组
	last:最新返回值数组
	max:最大值数组
	min:最小值数组
	pj:平均值数组
	len:数组长度
	becr:为1降序,为0升序

功能:
    排序图形数据数组,监测器名称、设备、最新值、
	最大值、最小值、平均值对应调整

返回指：
    成功返回TRUE，失败FALSE
****************************************************/
bool sort(double array[],
		  char *labels[],
		  char * entity[], 
		  char *last[], 
		  double max[],
		  double min[],
		  double pj[],
		  int len,
		  bool becr)
{
	int i = 0, i1 = 0;
	double maxval = 0;
	double temp = 0;
	double imax = 0;
	double imin = 0;
	double ipj = 0;	
	char mtemp[1024];
	char stemp[1024];
	char ientity[1024];
	char ilast[1024];

	if(len <= 0)
	{
		return false;
	}

	//降序
	if(becr)
	{
		for(i = 0; i < len; i++)
		{
			memset(mtemp, 0, 1024);
			strcpy(mtemp, labels[i]);

			memset(ientity, 0, 1024);
			strcpy(ientity, entity[i]);

			memset(ilast, 0, 1024);
			strcpy(ilast, last[i]);

			maxval = array[i];
			imax = max[i];
			imin = min[i];
			ipj = pj[i];
			

			for(i1 = i+1; i1 < len; i1++)
			{
				if(maxval <= array[i1])
				{
					temp = maxval;
					maxval = array[i1];
					array[i1] = temp;

					temp = imax;
					imax = max[i1];
					max[i1] = temp;

					temp = imin;
					imin = min[i1];
					min[i1] = temp;

					temp = ipj;
					ipj = pj[i1];
					pj[i1] = temp;

					memset(stemp, 0, 1024);
					strcpy(stemp, mtemp);
					memset(mtemp, 0, 1024);
					strcpy(mtemp, labels[i1]);
					memset(labels[i1], 0, strlen(labels[i1]));
					strcpy(labels[i1], stemp);

					memset(stemp, 0, 1024);
					strcpy(stemp, ientity);
					memset(ientity, 0, 1024);
					strcpy(ientity, entity[i1]);
					memset(entity[i1], 0, strlen(entity[i1]));
					strcpy(entity[i1], stemp);

					memset(stemp, 0, 1024);
					strcpy(stemp, ilast);
					memset(ilast, 0, 1024);
					strcpy(ilast, last[i1]);
					memset(last[i1], 0, strlen(last[i1]));
					strcpy(last[i1], stemp);
				}
			}	
			memset(labels[i], 0, strlen(labels[i]));
			strcpy(labels[i], mtemp);
			array[i] = maxval;
			max[i] = imax;
			min[i] = imin;
			pj[i] = ipj;
			memset(entity[i], 0, strlen(entity[i]));
			strcpy(entity[i], ientity);
			memset(last[i], 0, strlen(last[i]));
			strcpy(last[i], ilast);
		}
	}
	else
	{
		for(i = 0; i < len; i++)
		{
			memset(mtemp, 0, 1024);
			strcpy(mtemp, labels[i]);

			memset(ientity, 0, 1024);
			strcpy(ientity, entity[i]);

			memset(ilast, 0, 1024);
			strcpy(ilast, last[i]);

			maxval = array[i];
			imax = max[i];
			imin = min[i];
			ipj = pj[i];

			for(i1 = i+1; i1 < len; i1++)
			{
				if(maxval >= array[i1])
				{
					temp = maxval;
					maxval = array[i1];
					array[i1] = temp;

					temp = imax;
					imax = max[i1];
					max[i1] = temp;

					temp = imin;
					imin = min[i1];
					min[i1] = temp;

					temp = ipj;
					ipj = pj[i1];
					pj[i1] = temp;

					memset(stemp, 0, 1024);
					strcpy(stemp, mtemp);
					memset(mtemp, 0, 1024);
					strcpy(mtemp, labels[i1]);
					memset(labels[i1], 0, strlen(labels[i1]));
					strcpy(labels[i1], stemp);

					memset(stemp, 0, 1024);
					strcpy(stemp, ientity);
					memset(ientity, 0, 1024);
					strcpy(ientity, entity[i1]);
					memset(entity[i1], 0, strlen(entity[i1]));
					strcpy(entity[i1], stemp);

					memset(stemp, 0, 1024);
					strcpy(stemp, ilast);
					memset(ilast, 0, 1024);
					strcpy(ilast, last[i1]);
					memset(last[i1], 0, strlen(last[i1]));
					strcpy(last[i1], stemp);
				}
			}	
			memset(labels[i], 0, strlen(labels[i]));
			strcpy(labels[i], mtemp);
			array[i] = maxval;
			max[i] = imax;
			min[i] = imin;
			pj[i] = ipj;
			memset(entity[i], 0, strlen(entity[i]));
			strcpy(entity[i], ientity);
			memset(last[i], 0, strlen(last[i]));
			strcpy(last[i], ilast);

		}
	}

	return true;
}

/*****************************************************************
参数：
	starttime:开始时间
	endtime:截止时间
	reportname:报告名称
	szCount:柱状图显示数量
	parent:容器

功能：
	构造函数
*****************************************************************/
CTopnReport::CTopnReport(chen::TTime starttime,
						 chen::TTime endtime, 
						 std::string reportname,
						 std::string szCount,
						 WContainerWidget *parent ):WContainerWidget(parent)
{
	//Resource
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_TopN_Report",strMainTitle);
			FindNodeValue(ResNode,"IDS_TopN_Report_List",strTitle);
			FindNodeValue(ResNode,"IDS_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Simple_Report_Map",strNameUse);
			FindNodeValue(ResNode,"IDS_Edit_Name",strNameEdit);
			FindNodeValue(ResNode,"IDS_Affirm_Delete_User",strDel);
			FindNodeValue(ResNode,"IDS_Time_Period",szInterTime);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Run_Case_Table",m_formText.szRunTitle);
			FindNodeValue(ResNode,"IDS_Alert_Date_Total_Table",m_formText.szMonitorTitle);
			FindNodeValue(ResNode,"IDS_Error_Precent",m_formText.szErrorTitle);
			FindNodeValue(ResNode,"IDS_Danger_Prencet",m_formText.szDangerTitle);
			FindNodeValue(ResNode,"IDS_Normal_Precent",m_formText.szNormalTitle);
			FindNodeValue(ResNode,"IDS_Device_Name",m_formText.szRunName);
			FindNodeValue(ResNode,"IDS_Monitor_Name",m_formText.szRunTime);
			FindNodeValue(ResNode,"IDS_Max_Value",m_formText.szRunDanger);
			FindNodeValue(ResNode,"IDS_Average_Value",m_formText.szRunError);
			FindNodeValue(ResNode,"IDS_Min_Value",m_formText.szRunNew);
			FindNodeValue(ResNode,"IDS_Latest_Description",m_formText.szRunClicket);
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
			FindNodeValue(ResNode,"IDS_Later",m_formText.szGetValueNew);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Select_Sort_Des",strDes);
			FindNodeValue(ResNode,"IDS_Select_Sort_Des_Bracket",strDes1);
			FindNodeValue(ResNode,"IDS_Select_Sort_Asc_Bracket",strAsc1);
			FindNodeValue(ResNode,"IDS_SiteView_Copyright",strCompany);
		}
		//CloseResource(objRes);
	}
	/*
	strMainTitle ="Topn报告";
	strTitle ="Topn报告列表";
	strLoginLabel = "名 称";	
	strNameUse = "Topn报告图";
	strNameEdit="编辑名称";
	strNameTest="游龙科技";
	strDel=  "确认删除选中用户吗？";
	szInterTime = "时间段:";
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
	bSort = true;

	ShowMainTable(starttime, endtime, reportname, szCount);
}
std::string CTopnReport::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
			strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

CTopnReport::~CTopnReport(void)
{
	if( objRes !=INVALID_VALUE )
			CloseResource(objRes);
}

/*******************************************************************
参数:
	szIndex:主ID
	monitorlist:返回监测器ID

功能:
    获取组下的所有监测器ID
*******************************************************************/
void EnumGroup(std::string szIndex, std::list<string>& entitylist)
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

					//判断子组下的设备LIST是否为空
					if(monlist.size() > 0)
					{
						bool bBreak = true;
						std::list<string>::iterator monitorlistitem;	
						std::list<string>::iterator monitoridlistitem = monlist.begin();
						for(monitorlistitem = entitylist.begin(); monitorlistitem != entitylist.end();\
							monitorlistitem++)
						{
							std::string tempid = *monitorlistitem;
							std::string tempid1 = *monitoridlistitem;
							//如果已存在则不合并到监测器LIST中
							if(strcmp( tempid1.c_str(), tempid.c_str()) == 0)
							{
								bBreak = false;
								break;
							}
						}

						if(bBreak)
						{
							std::list<string>::iterator litem = monlist.begin();
							
							entitylist.merge(monlist);										
						}
					}
                }            
            }
            //如果为子组递归获取子组下的所有监测器
			if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    EnumGroup(szSubGroupID, entitylist);
                }                
            }

            CloseGroup(group);
        }        
    }
}

/******************************************************************
参数：
	starttime:开始时间
	endtime:截止时间
	reportname:报告名称
	szCount:柱状图显示数量

功能：
    主界面显示函数
******************************************************************/
void CTopnReport::ShowMainTable(chen::TTime starttime, 
								chen::TTime endtime,
								std::string reportname,
								std::string szCount)
{	
	WIN32_FIND_DATA fd;
	string	szRootPath = GetSiteViewRootPath();
	string szReport = szRootPath;
	szReport += "\\htdocs\\topnreport";
	//判断topn报告文件存储路径是否存在， 不存在则创建
	HANDLE fr=::FindFirstFile(szReport.c_str(), &fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szReport.c_str(), NULL);
	}
		
	string szIconPath = szRootPath;
	szIconPath += "\\htdocs\\topnreport\\Images";
	fr=::FindFirstFile(szIconPath.c_str(), &fd);

	//判断TOPN报告文件图片存储路径是否存在， 不存在则创建
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(szIconPath.c_str(), NULL);
	}


	new WText("<div id='view_panel' class='panel_view'>",this);

	//生成HTML文件中包含basic.js文件
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);

	char buf_tmp[4096]={0};
    int nSize =4095;
	//把reportname中所有的空格替换为%20
	replace_all_distinct(reportname, "%20", " ");
	std::string querystr;	
	int reccount = 0;
	strcpy(buf_tmp , reportname.c_str());
	
	if(buf_tmp != NULL)
	{
		//取报告对应监测器	
		GetMonitorGroup(buf_tmp, grouplist);
	}
	
	std::string defaultret = "error";
	//TYPE值
	std::string szType = GetIniFileString(reportname, "Type", defaultret, "topnreportset.ini");
	//MARK值
	std::string szMark = GetIniFileString(reportname, "Mark", defaultret, "topnreportset.ini");
	//图形数据取值方式（平均、最新）
	std::string szGetValue = GetIniFileString(reportname, "GetValue", defaultret, "topnreportset.ini");
	//排序方式
	std::string szSort = GetIniFileString(reportname, "Sort", defaultret, "topnreportset.ini");	

	//任务计划
	std::string szPlan = GetIniFileString(reportname, "Plan", defaultret, "topnreportset.ini");
	OBJECT hPlan = GetTask(szPlan);

	std::string szPlanType = GetTaskValue("Type", hPlan);

	//取任务计划时间段
	/*
	string szStart[7];
	string szEnd[7];		
	
	if(strcmp(szPlanType.c_str(), "2") == 0)
	{
		for(int i = 0; i < 7; i++)
		{
			char buf[256];
			string szPreStart = "start";
			string szPreEnd = "end"; 
			itoa(i, buf, 10);
			szPreStart += buf;
			szPreEnd += buf;
			szStart[i] = GetTaskValue(szPreStart, hPlan);
			szEnd[i] = GetTaskValue(szPreEnd, hPlan);
		}
	}

	for(int i = 0; i < 7; i++)
	{
		char *token = NULL;
		char * cp = strdup(szStart[i].c_str());
		if (cp)
		{
			token = strtok(cp , ",");
			while( token != NULL )
			{
				string splitstr = token;
				int pos = splitstr.find(":", 0);
				string szHour = splitstr.substr(0, pos);
				string szMinute = splitstr.substr(pos + 1, splitstr.size() - pos - 1);
				starttimelist[i].push_back(TTimeSpan(0 , atoi(szHour.c_str()), atoi(szMinute.c_str()), 0));

				token = strtok( NULL , ",");
			}
			free(cp);
		}

		cp = strdup(szEnd[i].c_str());
		if (cp)
		{
			token = strtok(cp , ",");
			while( token != NULL )
			{
				string splitstr = token;
				int pos = splitstr.find(":", 0);
				string szHour = splitstr.substr(0, pos);
				string szMinute = splitstr.substr(pos + 1, splitstr.size() - pos - 1);
				endtimelist[i].push_back(TTimeSpan(0 , atoi(szHour.c_str()), atoi(szMinute.c_str()), 0));

				token = strtok( NULL , ",");
			}
			free(cp);
		}
	}
	*/

	if(strcmp(szSort.c_str(), strDes.c_str()) == 0)
	{		
		bSort = true;
	}
	else
	{		
		bSort = false;
	}

	//组合报告标题串
	std::string reporttitle = szType;
	reporttitle += "[";
	reporttitle += szMark;
	reporttitle += "]";

	if(bSort)
	{		
		reporttitle += strDes1;
	}
	else
	{
		reporttitle += strAsc1;
	}
	
	//初始化页面元素
	//InitPageItem(pContainTable, reporttitle, buf_tmp);
	NewInitPageItem(reporttitle, buf_tmp);

	//增加列表标题栏
	//AddColum(NULL);
		
	std::list<string>::iterator item;
	int i6 = 1;
	int i1, i2;
	char buf[256];
	char buf1[256];
	
	//实例图片表格

	//jansion.zhou 2006-12-19
	//pImageTable = new WTable(pContainTable->elementAt(2 , 0));
	//pContainTable->elementAt(2, 0) ->setContentAlignment(AlignTop | AlignCenter);
	//int Img_numRow = m_TopMainTable->numRows();
	//pImageTable = new WTable(m_TopMainTable->elementAt(2, 0));
	//m_TopMainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);	
	//new WImage(namebuf2, (WContainerWidget*)pImageTable->elementAt(i3, 0));	
	//pImageTable->elementAt(0, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	
	int i3 = 0;//图表行数
	int tcount = 0;

	std::list<string> monitorlist;//监测器LIST
	std::list<string>::iterator monitorlistitem;
	std::string bGroupStr = "";

	for(item = grouplist.begin(); item != grouplist.end(); item++)
	{			
		std::string monitorid = *item;				
		
		//取组句柄
		OBJECT	hGroup = GetGroup(monitorid);
		std::list<string> monitoridlist;
		std::list<string>::iterator monitoridlistitem;
	
		if(hGroup == INVALID_VALUE)
		{
			//取设备句柄
			hGroup = GetEntity(monitorid);			
			if(hGroup != INVALID_VALUE)
			{		
				//取设备下所有监测器
				bool bRet = GetSubMonitorsIDByEntity(hGroup, monitoridlist);
				
				if(monitoridlist.size() > 0)
				{
					std::string szFirst = *monitoridlist.begin();
					for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
						monitorlistitem++)
					{
						std::string tempid = *monitorlistitem;
						if(strcmp( szFirst.c_str(), tempid.c_str()) == 0)
						{
							goto cont;
						}
					}			
					//组合monitorlist
					monitorlist.merge(monitoridlist);
				}
			}
			else
			{	
				//查找监测器在monitorlist中是否已经存在
				for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
					monitorlistitem++)
				{
					std::string tempid = *monitorlistitem;
					if(strcmp( monitorid.c_str(), tempid.c_str()) == 0)
					{
						goto cont;
					}
				}
				//不为组不为ENTITY				
				monitorlist.push_back(monitorid);
			}
		}
		else
		{		
			EnumGroup(monitorid, monitorlist);
			continue;
		}
		//如果存在监测器ID则返回循环
cont:
			;
	}

	//  取TEMPLET的属性值
    std::list<string>::iterator monitoritem;
	OBJECT hTemplet;
	std::string monitorname;

	double perarray[1000];
	double maxarray[1000];
	double minarray[1000];
	double pjarray[1000];
	char* lastarray[1000];
	char* labels1[1000];
	char* entityarray[1000];	
	int color[1000];

	OutputDebugString("--------------------topn report right output------------------\n");

	for(int recitem = 0; recitem < 1000; recitem++)
	{
		labels1[recitem] = (char*)malloc(512);	
		lastarray[recitem] = (char*)malloc(512);
		entityarray[recitem] = (char*)malloc(512);
		memset(labels1[recitem], 0, 512);
		memset(lastarray[recitem], 0, 512);
		memset(entityarray[recitem], 0, 512);
	
	}

	int snum = atoi(szCount.c_str());

	int num1 = 1;
	for( monitoritem = monitorlist.begin(); monitoritem != monitorlist.end(); monitoritem++)
	{
		std::string szMonitor = *monitoritem;
		std::string getvalue;
		OBJECT hMon = GetMonitor(szMonitor);
		MAPNODE ma=GetMonitorMainAttribNode(hMon);
		std::string smonitorname = "";
		FindNodeValue( ma, "sv_name", smonitorname);
	OutputDebugString("------------------ppppppppppppppppppppppppppppppppp--------000-----\n");				
	
		if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
		{			
			OutputDebugString("------------------ppppppppppppppppppppppppppppppppp-----111--------\n");				

			hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
			MAPNODE node = GetMTMainAttribNode(hTemplet);
			monitorname = "";
			FindNodeValue(node, "sv_label", monitorname);				
			monitorname = GetLabelResource(monitorname);

			//Jansion.zhou 可能需要处理的判断
			if(strcmp(monitorname.c_str(), szType.c_str()) == 0)
			{
				OutputDebugString("------------------ppppppppppppppppppppppppppppppppp-----222--------\n");				

				string strEntity =	FindParentID(szMonitor);
				OBJECT hEntity = GetEntity(strEntity);
				MAPNODE entitynode = GetEntityMainAttribNode(hEntity);
				std::string entityvalue;
				FindNodeValue(entitynode, "sv_name", entityvalue);

				int retperval = 0;
				int retmaxval = 0;
				int retminval = 0;
				int lastval = 0;
				std::string retdispstr = "";

OutputDebugString("------------------ppppppppppppppppppppppppppppppppp-------------\n");				
				GetMonitorRecord(szMonitor, szMark, starttime, endtime,reportname,\
					retperval, retmaxval, retminval, retdispstr, szGetValue, lastval);
				perarray[num1 - 1] = retperval;
				pjarray[num1 - 1] = lastval;
				if(num1 <= snum)
				{
					
				}
				
				strcpy(entityarray[num1 - 1], entityvalue.c_str());
				maxarray[num1 - 1] = retmaxval;
				minarray[num1 - 1] = retminval;
				strcpy(lastarray[num1 - 1] , retdispstr.c_str());
				pjarray[num1 - 1] = lastval;

				std::string dispname = entityvalue;
				dispname += ":";
				dispname += smonitorname;
				
				strcpy(labels1[num1 - 1], dispname.c_str());

				color[num1 - 1] = 0x80d080;			
				std::string linkreport = "<a href=../fcgi-bin/SimpleReport.exe?id=";
				linkreport += szMonitor;
				linkreport += ">";
				linkreport += dispname;
				linkreport += "</a>";

				if(num1 <= snum)
				{
				
				}
				num1++;
			}
		}
	}
OutputDebugString("--------------------topn report right output--------1111111111----------\n");
	std::string namebuf;
	std::string namebuf1;

	namebuf = szIconPath;		
	namebuf += "\\";

	std::string timestr = starttime.Format();
	timestr = replace_all_distinct(timestr, " ", "_");
	namebuf1 = timestr;
	timestr = endtime.Format();
	timestr = replace_all_distinct(timestr, " ", "_");
	namebuf1 += timestr;
	
	std::string namebuf3 = namebuf1;
	namebuf3 += reportname;
	namebuf3 += "\\";
	
	namebuf3 = replace_all_distinct(namebuf3, ":", "_");
	
	namebuf += namebuf3;						
	
	fr=::FindFirstFile(namebuf.c_str(),&fd);
	if(!::FindNextFile(fr, &fd))
	{
		CreateDirectory(namebuf.c_str(), NULL);
	}

	namebuf1 += szType;
	itoa(rand(), buf, 10);
	namebuf1 += buf;
	
	namebuf1 += ".png";
	
	//namebuf = replace_all_distinct(namebuf, " ", "_");
	namebuf1 = replace_all_distinct(namebuf1, ":", "_");
	namebuf1 = replace_all_distinct(namebuf1, "<", "_");
	namebuf1 = replace_all_distinct(namebuf1, ">", "_");
	namebuf1 = replace_all_distinct(namebuf1, "\\", "_");
	namebuf1 = replace_all_distinct(namebuf1, "/", "_");
	namebuf1 = replace_all_distinct(namebuf1, "*", "_");

	namebuf += namebuf1;
	
	sort(perarray,labels1, entityarray, lastarray, maxarray, minarray, pjarray, num1 - 1, bSort);



	//if(num1 <= snum)
	//{
	//	GenBarImage(perarray, labels1,color, num1 - 1, (char*)szType.c_str(), (char*)szMark.c_str(), (char*)namebuf.c_str());
	//}
	//else
	//{
	//	GenBarImage(perarray, labels1,color, snum, (char*)szType.c_str(), (char*)szMark.c_str(), (char*)namebuf.c_str());
	//}
	//std::string namebuf2 = "Images/";
	//namebuf2 += namebuf3;
	//namebuf2 += namebuf1;
	//new WImage(namebuf2, (WContainerWidget*)pImageTable->elementAt(i3, 0));	
	//pImageTable->elementAt(0, 0) ->setContentAlignment(AlignTop | AlignCenter);


	int In_numRow = 1;
	if(num1 <= snum)
	{
		for(int inum = 0; inum < num1 - 1; inum++)
		{
			//new WText(entityarray[inum], pRunTable->elementAt(inum+1, 0));
			//WText * pName = new WText(labels1[inum], pRunTable->elementAt(inum+1, 1));			
			//itoa(maxarray[inum], buf, 10);
			//new WText(buf, pRunTable->elementAt(inum+1, 2));
			//itoa(pjarray[inum], buf, 10);
			//new WText(buf, pRunTable->elementAt(inum+1, 3));
			//itoa(minarray[inum], buf, 10);
			//new WText(buf, pRunTable->elementAt(inum+1, 4));
			//new WText(lastarray[inum], pRunTable->elementAt(inum+1, 5));

			m_TopFlexTable->InitRow(In_numRow);

			new WText(entityarray[inum], m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 0));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 0)->setContentAlignment(AlignCenter);

			WText * pName = new WText(labels1[inum], m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 2));	
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 2)->setContentAlignment(AlignCenter);

			itoa(maxarray[inum], buf, 10);
			new WText(buf, m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 4));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 4)->setContentAlignment(AlignCenter);

			itoa(pjarray[inum], buf, 10);
			new WText(buf, m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 6));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 6)->setContentAlignment(AlignCenter);

			itoa(minarray[inum], buf, 10);
			new WText(buf, m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 8));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 8)->setContentAlignment(AlignCenter);

			new WText(lastarray[inum], m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 10));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 10)->setContentAlignment(AlignCenter);
			In_numRow++;
		}
	}
	else
	{
		for(int inum = 0; inum < snum; inum++)
		{
			//new WText(entityarray[inum], pRunTable->elementAt(inum+1, 0));
			//WText * pName = new WText(labels1[inum], pRunTable->elementAt(inum+1, 1));			
			//itoa(maxarray[inum], buf, 10);
			//new WText(buf, pRunTable->elementAt(inum+1, 2));
			//itoa(pjarray[inum], buf, 10);
			//new WText(buf, pRunTable->elementAt(inum+1, 3));
			//itoa(minarray[inum], buf, 10);
			//new WText(buf, pRunTable->elementAt(inum+1, 4));
			//new WText(lastarray[inum], pRunTable->elementAt(inum+1, 5));

			m_TopFlexTable->InitRow(In_numRow);

			new WText(entityarray[inum], m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 0));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 0)->setContentAlignment(AlignCenter);
			WText * pName = new WText(labels1[inum], m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 2));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 2)->setContentAlignment(AlignCenter);
			itoa(maxarray[inum], buf, 10);
			new WText(buf, m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 4));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 4)->setContentAlignment(AlignCenter);
			itoa(pjarray[inum], buf, 10);
			new WText(buf, m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 6));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 6)->setContentAlignment(AlignCenter);
			itoa(minarray[inum], buf, 10);
			new WText(buf, m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 8));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 8)->setContentAlignment(AlignCenter);
			new WText(lastarray[inum], m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 10));
			m_TopFlexTable->GeDataTable()->elementAt(In_numRow, 10)->setContentAlignment(AlignCenter);
			In_numRow++;
		}
	}
	
OutputDebugString("--------------------topn report right output--------2222222----------\n");
	
	if(num1 <= snum)
	{
		GenBarImage(perarray, labels1,color, num1 - 1, (char*)szType.c_str(), (char*)szMark.c_str(), (char*)namebuf.c_str());

	}
	else
	{
		GenBarImage(perarray, labels1,color, snum, (char*)szType.c_str(), (char*)szMark.c_str(), (char*)namebuf.c_str());
	}
	/*for(int recitem = 0; recitem < 1000; recitem++)
	{
		free(labels1[recitem]);			
	}
	*/
	//取监测器的TYPE及MARK	

	std::string namebuf2 = "Images/";
	namebuf2 += namebuf3;
	namebuf2 += namebuf1;

	
	//int Img_numRow = m_TopMainTable->numRows();
	//pImageTable = new WTable(m_TopMainTable->elementAt(2, 0));
	//m_TopMainTable->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);	
	new WImage(namebuf2, (WContainerWidget*)pImageTable->elementAt(i3, 0));	
	pImageTable->elementAt(0, 0) ->setContentAlignment(AlignTop | AlignCenter);
	
	//pRunTable ->adjustRowStyle("tr1", "tr2");

	//// jansion.zhou  2006-12-19
	new WText("<table id='o1c' cellPadding='0' cellSpacing='0'  style='width:80%;margin-top:0px;margin-right:auto;margin-bottom:0px;margin-left:80px;'><tbody>", this);
	//std::string tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='color:blue;font-family:Arial,;font-size:little;' bgcolor=#ffffff align='center'>";
	std::string tempstr = "<tr id='o25' style='text-align:center;'><td colspan=3 style='color:blue;font-family:Arial;' bgcolor=#ffffff align='center'>";
	tempstr += strCompany; 
	tempstr += "</td></tr>";
	new WText(tempstr, this);
	new WText("</tbody></table>", this);

	//int ex_numRow = m_TopMainTable->numRows();
	//new WText(strCompany, m_TopMainTable->elementAt(ex_numRow, 0));
	//m_TopMainTable->elementAt(ex_numRow, 0)->setContentAlignment(AlignCenter);


	new WText("</div>", this);
	AddJsParam("uistyle", "viewpanan");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);


}


//加列标题
void CTopnReport::AddColum(WTable* pContain)
{
	new WText(m_formText.szRunName, pRunTable->elementAt(0, 0));
	new WText(m_formText.szRunTime, pRunTable->elementAt(0, 1));
	new WText(m_formText.szRunDanger, pRunTable->elementAt(0, 2));
	new WText(m_formText.szRunError, pRunTable->elementAt(0, 3));
	new WText(m_formText.szRunNew, pRunTable->elementAt(0, 4));
	new WText(m_formText.szRunClicket, pRunTable->elementAt(0, 5));

	pRunTable->setCellSpaceing(0);
	pRunTable->GetRow(0) ->setStyleClass("t1title");
}

//添加客户端脚本变量
void CTopnReport::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CTopnReport::AddListColumn()
{

}

void CTopnReport::refresh()
{

}



void CTopnReport::GenBarImage(double data[], char *labels[], int color[], int len, char * xtitle, char * ytitle, char * szFile)
{
	wchar_t lpWide[256];
    // Create a XYChart object of size 250 x 250 pixels
    XYChart *c = new XYChart(560, 540,0xffffff, 0x0, 1);//, Chart::goldColor(), -1, 2);

    // Set the plotarea at (30, 20) and of size 200 x 200 pixels
    c->setPlotArea(45, 20, 500, 400);

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;
	setlocale(LC_CTYPE, "chs"); 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xtitle, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
	c->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);
		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, ytitle, 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

    c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

    // Add a bar chart layer using the given data
    c->addBarLayer(DoubleArray(data, len), IntArray(color,
        len))->setBorderColor(-1, 1);

    // Set the labels on the x axis.
	
	for(int item = 0; item < len; item++)
	{
		int slen = 256;
		int wlen = 256;
		LPSTR lpMultiByteStr= (LPSTR)malloc(256);
		BOOL buse ;
		setlocale(LC_CTYPE, "chs"); 

		memset(lpWide, 0, 256);
		mbstowcs(lpWide, labels[item], 256);
		WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

		memset(labels[item], 0, strlen(labels[item]));
		strcpy(labels[item], lpMultiByteStr);
	}
	
	c->setDefaultFonts("SIMSUN.TTC","simhei.ttf");

    c->xAxis()->setLabels(StringArray(labels, len))->setFontAngle(90);

    // output the chart
    c->makeChart(szFile);
	
    delete c;
	//free(lpMultiByteStr);	
}


void CTopnReport::GenLineImage(double data[],  const int len, char *xlabels[],int xscalelen, int xStep, char *ylabels[], int yscalelen, int yScale, int yStep, int xLinearScale, double starttime, double endtime, char* Title, char* xTitle, char * filename)
{    
	wchar_t lpWide[256];
	XYChart *c = new XYChart(300*2, 300, 0xffffff, 0x0, 1);

	double m_timeStamps[60000];

	double timespan = endtime - starttime;
	double intertime = timespan/len;
	for(int i = 0; i < len; i++)
	{
		m_timeStamps[i] = starttime + intertime*i;
	}

	c->setPlotArea(55, 36, 260*2, 200, 0xffffff, -1, 0xa08040, c->dashLineColor(0x000000,
        0x000103), c->dashLineColor(0x000000, 0x000103));

	LPCWSTR lpWideCharStr =L"";
	int slen = 256;
	int wlen = 256;
	LPSTR lpMultiByteStr= (LPSTR)malloc(256);
	BOOL buse ;
	setlocale(LC_CTYPE, "chs"); 

	memset(lpWide, 0, 256);
	mbstowcs(lpWide, Title, 256);
	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);
	c->addTitle(lpMultiByteStr,
		"mingliu.ttc", 9, 0x0000ff);//->setBackground(0xffffff, -1, 1);

	memset(lpMultiByteStr, 0, 256);
		
	memset(lpWide, 0, 256);
	mbstowcs(lpWide, xTitle, 256);

	WideCharToMultiByte(CP_UTF8, 0, lpWide,  slen, lpMultiByteStr, wlen, NULL, NULL);

    c->yAxis()->setTitle(lpMultiByteStr, "mingliu.ttc");

	//lpWideCharStr = L"游龙科技有限公司";
	//memset(lpMultiByteStr, 0, 256);
	//WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, slen, lpMultiByteStr, wlen, NULL, NULL);

	if(yScale <= 10)
	{
		c->yAxis()->setLinearScale(0, yScale + 1);
	}
	else
	{
		c->yAxis()->setLinearScale(0, yScale);//设置垂直刻度
	}
	c->xAxis()->setLinearScale(0, xLinearScale);		 
 
	if(endtime - starttime < 90000)
	{
		c->xAxis()->setDateScale(starttime, endtime, 3600);
	}
	else
	{
		c->xAxis()->setDateScale(starttime, endtime, 86400 );
	}

	AreaLayer *layer = c->addAreaLayer();

	layer ->setXData(DoubleArray(m_timeStamps, len));
	layer->addDataSet(DoubleArray(data, len))->setDataColor(
        0x80d080, 0x007000);

    c->makeChart(filename);

	free(lpMultiByteStr);

    delete c;
}


void CTopnReport::GetMonitorDataRecStr(RECORDSET hRecSet, std::string monitorname, std::list<string> &retmonnamelist, std::list<int> &retstatlist, std::list<string>& retstrlist, std::list<string>& rettimelist)
{
	LISTITEM item;
	RECORD hRec;
	
	FindRecordFirst(hRecSet, item);
			
	int stat;
	std::string str;

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		GetRecordDisplayString(hRec, stat, str);			
		TTime tm;
		GetRecordCreateTime(hRec,tm);
		if(stat == 2)
		{
			retdangernamelist.push_back(monitorname);
			retdangertimelist.push_back(tm.Format());
			retdangerstatuslist.push_back(str);
			
		}
		if(stat == 3)
		{
			reterrornamelist.push_back(monitorname);
			reterrortimelist.push_back(tm.Format());
			reterrorstatuslist.push_back(str);
		}
	}	
}

void CTopnReport::GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname, std::string &fieldtype,std::list<int>&intlist, std::list<float>&floatlist, std::list<string>&stringlist, float & maxval, float & minval, float & perval, float & lastval, int &reccount, std::string &retdispstr, std::string gv)
//void CTopnReport::GetMonitorDataRec(RECORDSET hRecSet, std::string fieldname,std::string fieldtype,  float & maxval, float & minval, float & perval, float & lastval, int & reccount, std::string & retdispstr, std::string gv)
{
	LISTITEM item;
	RECORD hRec;
	FindRecordFirst(hRecSet, item);
			
	int type;
	int stat;
	int iv;
	float fv;
	std::string sv;

	float countval = 0;
	int itemnum = 0;

	bool bmin = true;
	bool bLast = true;

	float retperval = 0.0;

	while( (hRec = FindNextRecord(item)) != INVALID_VALUE)
	{		
		//GetRecordDisplayString(hRec1, stat, str1);	
		TTime tm;
		iv = 0;
		fv = 0.0;

		if(bLast)
		{
			bool bRet = GetRecordValueByField(hRec, fieldname, type, stat, iv, fv, sv);
			char buf[256];
			fieldtype = itoa(type, buf, 10);
			
			GetRecordDisplayString(hRec, stat, retdispstr);	
			

			if(stat == 4)
			{
			}
			else if(stat != 0)
			{
				if(type == 1)
				{
					retperval = iv;
				}
				else if(type == 2)
				{
					retperval = fv;
				}
				else if(type == 3)
				{
					retperval = 0;
				}
			}
			bLast = false;
		}
		
		bool bret = GetRecordValueByField(hRec, fieldname, type, stat, iv, fv, sv);
		if(stat == 4)
		{
		}
		else if((stat != 0) )
		{	
			GetRecordCreateTime(hRec,tm);
			//判断为星期几， 根据任务计划过滤记录
			int nWeek = tm.GetWeekDay();
			list<TTimeSpan>::iterator item;
			
			//比较返回值类型
			if(type == 1)
			{				
				if(bmin)
				{
					minval = iv;
					bmin = false;
				}
				
				if(maxval < iv)
				{
					maxval = iv;
				}

				if(minval > iv)
				{
					minval = iv;
				}
				intlist.push_back(iv);
				
				lastval = iv;
				countval += iv;
				
			}
			else if(type == 2)
			{
				if(bmin)
				{
					minval = fv;
					bmin = false;
				}

				if(maxval < fv)
				{
					maxval =fv;
				}

				if(minval >fv)
				{
					minval = fv;
				}

				floatlist.push_back(fv);

				lastval = fv;
				countval += fv;		
			}
			else if(type == 3)
			{	
				if(stat == 3)
				{
					minval = 0;
				}
				stringlist.push_back(sv);
				
			}
			if(stat != 5)
			{
				itemnum++;
			}
		}
				
	}
	if(itemnum == 0)
	{
		perval = 0;
	}
	else
	{
		perval = countval/itemnum;
	}

	

	lastval = perval;
	if(strcmp(gv.c_str(), m_formText.szGetValueNew.c_str()) == 0)
	{
		
		perval = retperval;
	}
	reccount = itemnum;

}

void CTopnReport::GetMonitorGroup(char * reportname, std::list<string> & grouplist)
{
	std::string buf1 = reportname;
	int pos = buf1.find("=", 0);
	std::string querystr = buf1.substr(pos+1, buf1.size() - pos - 1);
			
	std::string defaultret = "error";
	std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "topnreportset.ini");		

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

void CTopnReport::InitPageItem(WTable *table, std::string title, std::string reportname)
{
	std::string rtitle = reportname;
	rtitle += ":";
	rtitle += title;

	WTable * FrameTable = new WTable(this);	

	FrameTable ->setStyleClass("t8");

	WTable * column = new WTable((WContainerWidget*)FrameTable->elementAt(1, 0));
	FrameTable->elementAt(1, 0)->setContentAlignment(AlignTop | AlignCenter);
	column->setStyleClass("t8");

	std::string linkstr = "<a href='../fcgi-bin/topnreportlist.exe?id=";
	linkstr += reportname;
	linkstr += "'>";
	linkstr += strReturn;
	linkstr += "</a>";
	new WText(linkstr, (WContainerWidget*)column->elementAt(0, 0));
	
	column->elementAt(0, 0)->setContentAlignment(AlignTop | AlignRight);
	pContainTable = new WTable((WContainerWidget*)FrameTable->elementAt(2,0));

	pContainTable ->setStyleClass("t8");

	pReportTitle = new WText(rtitle, (WContainerWidget*)pContainTable->elementAt(0, 0));
	pContainTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignCenter);
	WFont font1;
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);

	WText * text1 = new WText(szInterTime, (WContainerWidget*)pContainTable->elementAt(1, 0));
	pContainTable->elementAt(1, 0) ->setContentAlignment(AlignTop | AlignCenter);			

	WTable * blanktable = new WTable((WContainerWidget*)pContainTable->elementAt(3, 0));
	blanktable->setStyleClass("t3");

	pRunTable = new WTable(pContainTable->elementAt(4, 0));
	pContainTable->elementAt(4, 0)->setContentAlignment(AlignTop | AlignCenter);
	pRunTable->setStyleClass("StatsTable");	
	pRunTable->tableprop_ = 2;
	pRunTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";

}


void CTopnReport::NewInitPageItem(std::string title, std::string reportname)
{
	//new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>",this);
	//new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	//new WText("<div id='view_panel' class='panel_view'>",this);

	std::string rtitle = reportname;
	rtitle += ":";
	rtitle += title;

	m_TopMainTable = new WSVMainTable(this, "", false);



	WTable *titleTable = new WTable(m_TopMainTable->GetContentTable()->elementAt(1,0));	
	titleTable->elementAt(0,0)->setContentAlignment(AlignCenter | AlignMiddle);
	titleTable->elementAt(1,0)->setContentAlignment(AlignCenter | AlignMiddle);
	pReportTitle = new WText(rtitle, (WContainerWidget*)titleTable->elementAt(0,0));

	WFont font1;
	font1.setSize(WFont::Large, WLength(60,WLength::Pixel));
	pReportTitle ->decorationStyle().setFont(font1);

	//报告时间段
	WText * text1 = new WText(szInterTime, (WContainerWidget*)titleTable->elementAt(1, 0));

	std::string linkstr = "<a href='../fcgi-bin/topnreportlist.exe?id=";
	linkstr += reportname;
	linkstr += "'>";
	linkstr += strReturn;
	linkstr += "</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";

	titleTable->elementAt(2, 0)->setContentAlignment(AlignRight);
	new WText(linkstr,(WContainerWidget*)titleTable->elementAt(2, 0));
	new WText("&nbsp;",(WContainerWidget*)titleTable->elementAt(3, 0));

	//new WText(linkstr, (WContainerWidget*)m_TopMainTable->GetContentTable()->elementAt(0, 0));
	//m_TopMainTable->GetContentTable()->elementAt(0, 0)->setContentAlignment(AlignRight);
	//new WText("&nbsp;", (WContainerWidget*)m_TopMainTable->GetContentTable()->elementAt(1, 0));
	
	pImageTable = new WTable(m_TopMainTable->GetContentTable()->elementAt(2, 0));
	m_TopMainTable->GetContentTable()->elementAt(2, 0)->setContentAlignment(AlignTop | AlignCenter);	

	new WText("&nbsp;", m_TopMainTable->GetContentTable()->elementAt(3, 0));


	m_TopFlexTable = new WSVFlexTable(m_TopMainTable->GetContentTable()->elementAt(4,0), List, "",false);

	if (m_TopFlexTable->GetContentTable() != NULL)
	{
		//m_TopFlexTable->AppendColumn(m_formText.szRunName,WLength(140,WLength::Pixel));
		m_TopFlexTable->AppendColumn(m_formText.szRunName,WLength(20,WLength::Percentage));
		m_TopFlexTable->SetDataRowStyle("table_data_grid_item_img");

		m_TopFlexTable->AppendColumn(m_formText.szRunTime,WLength(20,WLength::Percentage));
		m_TopFlexTable->SetDataRowStyle("table_data_grid_item_text");

		m_TopFlexTable->AppendColumn(m_formText.szRunDanger,WLength(10,WLength::Percentage));
		m_TopFlexTable->SetDataRowStyle("table_data_grid_item_img");

		m_TopFlexTable->AppendColumn(m_formText.szRunError,WLength(10,WLength::Percentage));
		m_TopFlexTable->SetDataRowStyle("table_data_grid_item_text");

		m_TopFlexTable->AppendColumn(m_formText.szRunNew,WLength(10,WLength::Percentage));
		m_TopFlexTable->SetDataRowStyle("table_data_grid_item_text");
		
		m_TopFlexTable->AppendColumn(m_formText.szRunClicket,WLength(30,WLength::Percentage));
		m_TopFlexTable->SetDataRowStyle("table_data_grid_item_text");
	}


	//if (m_TopFlexTable->GetActionTable() != NULL)
	//{

	//	WSVButton * Re_Butt = new WSVButton(m_TopFlexTable->GetActionTable()->elementAt(0,0),strReturn,"button_bg_m.png",strReturn, false);
	//	WObject::connect(Re_Butt, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainReport(reportname)),
	//			WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//}

	//new WText("</div>", this);
	//AddJsParam("uistyle", "viewpanan");
	//AddJsParam("fullstyle", "true");
	//AddJsParam("bGeneral", "true");
	//new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);

}

void CTopnReport::ReturnMainReport(std::string reportname)
{
	//std::string openurl = "hiddenbar();location.href ='/fcgi-bin/reportset.exe?'";

	std::string openurl = "hiddenbar();location.href ='/fcgi-bin/topnreportlist.exe?id=";
	openurl += reportname;
	openurl += "'";

	WebSession::js_af_up = openurl;
}


void CTopnReport::WriteGenIni(std::string reportname, std::string starttime,std::string endtime,std::string value,std::string fieldlabel, float minval, float perval,float maxval)
{
	char buf[256];

	std::string section = reportname;
	section += "$";
	section += starttime;
	section += "$";
	section += endtime;
	section += "$";

	std::string keystr = value;
	keystr += "$";
	keystr += fieldlabel;
	keystr += "$";
	
	std::string valstr ;
	
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
OutputDebugString("--------kkkkkkkkkkkkkkkkkkkkk------555555555---------\n");
	WriteIniFileString(section, keystr, valstr, "topnreportgenerate.ini");
}

void CTopnReport::GetPlanMonitorRecord(std::string monitorid, 
									   std::string returnstr, 
									   chen::TTime starttime, 
									   chen::TTime endtime,
									   std::string reportname,
									   int & retperval, 
									   int &retmaxval,
									   int &retminval,
									   std::string & retdispstr, 
									   std::string gv,
									   int &retlastval)
{
	int totalval = 0;
	int total = 0;
	//按任务计划有多个时间段时，取多时间段的数据记录


		char buf[256];
		char buf2[256];
		OBJECT hMon = GetMonitor(monitorid);
		
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
		int reccount = 0;
		
		RECORDSET hRecSet = QueryRecords(monitorid, starttime, endtime);//取监测器数据集句柄
		//监测器返回值
		OBJECT hTemplet;
		std::string monitorname;
		MAPNODE objNode;
		
		if(hMon != INVALID_VALUE)
		{			
			std::string getvalue;
			MAPNODE ma=GetMonitorMainAttribNode(hMon);
			
			if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
			{			
				hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				FindNodeValue(node, "sv_label", monitorname);
				monitorname = GetLabelResource(monitorname);
							
				//报告设置是否显示阀值			
			}
			else
			{
				return;
			}
			
			bool bRet = FindMTReturnFirst(hTemplet, item);
							
			if(bRet)
			{
				std::string fieldlabel;
				std::string fieldname;
				std::string fieldtype;
				
				float maxval = 0.0;
				float minval = 0.0;
				float perval = 0.0;
				float lastval = 0.0;

				std::string returnimage ;
				std::string returnstats ;
				std::string returndata ;

				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{									
					
					FindNodeValue(objNode, "sv_label", fieldlabel);				
					fieldlabel =GetLabelResource(fieldlabel);
					FindNodeValue(objNode, "sv_type", fieldtype);								
					FindNodeValue(objNode, "sv_name", fieldname);

					if(strcmp(fieldlabel.c_str(), returnstr.c_str()) != 0)
					{
						continue;
					}									
					
					maxval = 0.0;
					perval = 0.0;
					lastval = 0.0;
					minval = 0.0;				
					int count = 0;

					//按字段取监测器记录队列
					std::list<int>intlist;
					std::list<float>floatlist;
					std::list<string>stringlist;
					std::list<int>::iterator intitem;
					std::list<float>::iterator floatitem;
					std::list<string>::iterator stringitem;

					GetMonitorDataRec(hRecSet, fieldname, fieldtype, intlist, floatlist, stringlist, maxval, minval, perval, lastval, reccount, retdispstr, gv); 

					

					//取各时间段最大值、最小值、平均值
					if(maxval > retmaxval)
					{
						retmaxval = maxval;
					}

					if(minval < retminval)
					{
						retminval = minval;
					}

					totalval += perval * reccount;
					total += reccount;

					/*
					retperval = perval;
					retmaxval = maxval;
					retminval = minval;*/
					retlastval = lastval;
					
														
					//WriteGenIni(reportname, starttime1.Format(), endtime1.Format(), value, fieldlabel, minval, perval, maxval);												
				}	
			}		
		}						
		CloseRecordSet(hRecSet);		
	
	retperval = totalval/total;

}


void CTopnReport::GetMonitorRecord(std::string monitorid, std::string returnstr, chen::TTime starttime, chen::TTime endtime, std::string reportname, int & retperval, int &retmaxval, int &retminval, std::string & retdispstr, std::string gv, int &retlastval)
{
	double data[50000];
	char buf[256];
	char buf2[256];
	OBJECT hMon = GetMonitor(monitorid);
	
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
	int reccount = 0;
	
	RECORDSET hRecSet = QueryRecords(monitorid, starttime, endtime);//取监测器数据集句柄
	//监测器返回值
	OBJECT hTemplet;
	std::string monitorname;
	MAPNODE objNode;
	
	if(hMon != INVALID_VALUE)
	{			
		OutputDebugString("--------kkkkkkkkkkkkkkkkkkkkk--------0000000000-------\n");
		std::string getvalue;
		MAPNODE ma=GetMonitorMainAttribNode(hMon);
		
		if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
		{			
			hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
			MAPNODE node = GetMTMainAttribNode(hTemplet);
			FindNodeValue(node, "sv_label", monitorname);
			monitorname = GetLabelResource(monitorname);
			//报告设置是否显示阀值			
		}
		else
		{
			return;
		}
		
		bool bRet = FindMTReturnFirst(hTemplet, item);
						
		if(bRet)
		{
			OutputDebugString("--------kkkkkkkkkkkkkkkkkkkkk------11111111111---------\n");
			std::string fieldlabel;
			std::string fieldname;
			std::string fieldtype;
			
			float maxval = 0.0;
			float minval = 0.0;
			float perval = 0.0;
			float lastval = 0.0;

			std::string returnimage = "";
			std::string returnstats = "";
			std::string returndata = "";

			std::string returnequally = "";

			while( (objNode = FindNext(item)) != INVALID_VALUE )
			{							
OutputDebugString("--------kkkkkkkkkkkkkkkkkkkkk------11111111111-----jansion.zhou----\n");
				FindNodeValue(objNode, "sv_label", fieldlabel);				
				fieldlabel =GetLabelResource(fieldlabel);
				FindNodeValue(objNode, "sv_type", fieldtype);								
				FindNodeValue(objNode, "sv_name", fieldname);

				bool bRet = FindNodeValue(objNode, "sv_equallyimage", returnequally);
				if(!bRet)
				{
					returnequally = "";
				}

				//Jansion.zhou 可能需要处理.
				if(strcmp(fieldlabel.c_str(), returnstr.c_str()) != 0)
				{
					continue;
				}									
				
				maxval = 0.0;
				perval = 0.0;
				lastval = 0.0;
				minval = 0.0;				
				int count = 0;

				//按字段取监测器记录队列
				std::list<int>intlist;
				std::list<float>floatlist;
				std::list<string>stringlist;
				std::list<int>::iterator intitem;
				std::list<float>::iterator floatitem;
				std::list<string>::iterator stringitem;

				std::string fieldtype1;
				GetMonitorDataRec(hRecSet, fieldname, fieldtype1, intlist, floatlist, stringlist, maxval, minval, perval, lastval, reccount, retdispstr, gv); 

				
				//2006-11-2 排除异常值
				int nSize = 0;
				if(floatlist.size() > 0)
				{
					nSize = floatlist.size();
				}
				if(intlist.size() > 0)
				{
					nSize = intlist.size() + nSize;
				}
				

				for(floatitem = floatlist.begin(), intitem = intlist.begin(); \
				floatitem != floatlist.end() || intitem != intlist.end() ;\
				floatitem++, intitem++)
				{
					//LIST中数据由当前时间往前，为图片显示必须做一下倒序
				
					if(strcmp(fieldtype.c_str(), "Int") == 0)
					{							
						data[nSize - 1 - count] = *intitem;
						count++;	
					}
					else if(strcmp(fieldtype.c_str(), "Float") == 0)
					{
						data[nSize - 1 - count] = *floatitem;
						count++;	
						
					}
						
										
				}	
				
				
				//依据监测器是否使用排除异常算法
				if(strcmp(returnequally.c_str(), "1") == 0)
				{
					//计算误差去除异常值，原理：测量误差大于3倍均方根误差为异常值
					
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
								char buf[256];
								sprintf(buf, "%f", data[m]);
								OutputDebugString(buf);
								//为异常值
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
				

				retperval = perval;
				retmaxval = maxval;
				retminval = minval;
				retlastval = lastval;
OutputDebugString("--------kkkkkkkkkkkkkkkkkkkkk------22222222222222---------\n");													
				WriteGenIni(reportname, starttime.Format(), endtime.Format(), value, fieldlabel, minval, perval, maxval);
											
			}				
		}		
	}						
	CloseRecordSet(hRecSet);		
}


void CTopnReport::enumMonitor(string &szIndex)
{
    if(!szIndex.empty())
    {
        OBJECT objDevice = GetEntity(szIndex);
        if(objDevice != INVALID_VALUE)
        {
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
            
            list<string> lsMonitorID;
            list<string>::iterator lstItem;
            if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
            {
                for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
                {
                    string szMonitorId = (*lstItem).c_str();                    
                }
            }
            CloseEntity(objDevice);
        }
    }
}

typedef void(*func)(int , char **);

void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_TopN_Report",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
	app.setTitle(title.c_str());
    //WApplication app(argc, argv);
    //app.setTitle("Topn报告");
	CTopnReport * setform;

	if(argc > 3)
	{
		std::string timestr = argv[1];

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

		//是否显示阀值

		bool bClicket = true ;
		bool bListError = true ;
		bool bListDanger = true ;
		bool bListStatsResult = true;
		bool bListImage = true;
		
		setform = new CTopnReport(starttime, endtime, argv[3], argv[5], app.root());		
	}
	else
	{
		setform = new CTopnReport(chen::TTime(2006, 8, 1, 0, 0, 0), chen::TTime(2006, 8,16, 0, 0, 0), "id=month_report", "100", app.root());
	}

    app.exec();
}


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
       // FCGI_Accept();
		string szRootPath = GetSiteViewRootPath();
		szRootPath += "\\htdocs\\topnreport\\";
        WebSession s("DEBUG", true, true, argv[4], szRootPath);
        s.start(p, argc, argv);
        return 1;
    }

    return 0;
}

