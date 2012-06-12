/*************************************************
*  @file ContrastReportFrame.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/
#include <boost/lexical_cast.hpp>
#include <fcgi_stdio.h>
#include <WApplication>
#include <WText>
#include <WImage>
#include <WPushButton>
#include <WTable>
#include <WTableCell>
#include <WContainerWidget>
#include <WScrollArea>
#include <WLineEdit>

#include "ContrastReportFrame.h"
#include "websession.h"
#include "WLength"
#include "WComboBox"
#include "WBreak"
#include <stdlib.h>
#include <stdio.h>
#include "../../kennel/svdb/libutil/time.h"
#include <iostream>
#include <Algorithm>
#include "ContrastReportFrame.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "..\svtable\MainTable.h"
#include "../../base/stlini.h"
#include "../base/OperateLog.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>
#include <WSVLinkText>
#include <WSlotInstance_>

//#include "../group/basefunc.h"
//new ui 
#include "../svtable/WSVMainTable.h"
#include "../svtable/WSVFlexTable.h"
#include "../svtable/WSVButton.h"
#include "../svtable/WSTreeAndPanTable.h"

WApplication *pTreeApp = NULL;

/***********************************************
参数：
pTask: 任务计划下拉框

功能：
增加任务计划到下拉框

返回值：

***********************************************/
void AddTaskList(WComboBox * pTask = NULL)
{
	if(pTask)
	{
		list<string> lsTaskName;
		list<string>::iterator lsItem;

		if(GetAllTaskName(lsTaskName))
		{
			for(lsItem = lsTaskName.begin(); lsItem != lsTaskName.end(); lsItem ++)
			{
				string szName = (*lsItem);
				pTask->addItem(szName);
			}
		}
	}
}

/************************************************************************
参数：
strLabel:标签IDS

功能：
从资源文件取得LABEL

返回值：
资源文件中的LABEL
************************************************************************/
std::string ContrastReportFrame::GetLabelResource(std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
		FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
		strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

/*******************************************************************
参数:
szIndex:主ID
monitorlist:返回监测器ID

功能:
获取组下的所有监测器ID
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
					//判断子组下的设备LIST是否为空
					if(monitorlist.size() > 0 && monlist.size() > 0)
					{
						string temp = *monitem;
						string temp1= *monitoritem;
						//判断监测器在LIST中是否存在
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
					//如果不存在则加入队列
					if(bMerge)
					{
						monitorlist.merge(monlist);										
					}
				}            
			}
			//如果是子组，递归获取子组下的监测器
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


/********************************************
参数：
szMsg:DBMON.EXE输出的STRING

功能：
在DBMON输出屏幕显示STRING

返回值：

********************************************/
void PrintDebugString(const string & szMsg)
{
	//PrintDebugString(szMsg.c_str());
}

/********************************************************
参数：
szMsg:DBMON.EXE输出的STRING

功能：
如果DEFINE　ＷＩＮ３２，　在DBMON输出屏幕显示STRING

返回值：

*********************************************************/
void PrintDebugString(const char * szMsg)
{
#ifdef WIN32
	OutputDebugString(szMsg);
	OutputDebugString("\n");
#endif
}

/*****************************************************
参数：
pTokenList: 返回分解后存储的字符LIST
pQueryString: 需要分解的字符串
pSVSeps: 分隔的字符

功能：
分解字符串

返回值：
如果成功则返回ＴＲＵＥ，　否则返回ＦＡＬＳＥ
*****************************************************/
bool ParserToken(list<string >&pTokenList,
				 const char * pQueryString,
				 char *pSVSeps)
{
	char * token = NULL;
	// duplicate string
	char * cp = ::strdup(pQueryString);
	if (cp)
	{
		char * pTmp = cp;
		if (pSVSeps) // using separators
			token = strtok( pTmp , pSVSeps);
		else // using separators
			return false;
		//token = strtok( pTmp, chDefSeps);
		// every field
		while( token != NULL )
		{
			//triml(token);
			//AddListItem(token);
			pTokenList.push_back(token);
			// next field
			if (pSVSeps)
				token = strtok( NULL , pSVSeps);
			else
				return false;
			//token = strtok( NULL, chDefSeps);
		}
		free(cp);
	}
	return true;
}

/*********************************
参数：
strTime:时间字符串

功能：
构造时间

返回值：
构造好的TTime

*********************************/
TTime MakeTTime(string strTime)
{
	if(strTime.empty())
	{
		TTime time;
		return time;
	}

	std::list<string> pTmpList;	
	ParserToken(pTmpList, strTime.c_str(), " ");

	string strYear, strMonth, strDay;
	std::list<string> pTmpList1;
	ParserToken(pTmpList1, pTmpList.front().c_str(), "-");

	strYear = pTmpList1.front();
	pTmpList1.pop_front();
	strMonth = pTmpList1.front();
	pTmpList1.pop_front();
	strDay = pTmpList1.front();
	pTmpList1.pop_front();

	string strHour, strMinute, strSecond;
	std::list<string> pTmpList2;
	ParserToken(pTmpList2, pTmpList.back().c_str(), ":");

	strHour = pTmpList2.front();
	pTmpList2.pop_front();
	strMinute = pTmpList2.front();
	pTmpList2.pop_front();
	strSecond = pTmpList2.front();
	pTmpList2.pop_front();

	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	sscanf(strYear.c_str(), "%d", &nYear);
	sscanf(strMonth.c_str(), "%d", &nMonth);
	sscanf(strDay.c_str(), "%d", &nDay);
	sscanf(strHour.c_str(), "%d", &nHour);
	sscanf(strMinute.c_str(), "%d", &nMinute);
	sscanf(strSecond.c_str(), "%d", &nSecond);	

	TTime time(nYear, nMonth, nDay, nHour, nMinute, nSecond);

	return time;
}

/*******************************************
参数：

功能：
加载资源

返回：

*******************************************/
void ContrastReportFrame::loadString()
{ 
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Start_Time1",strStartTimeLabel);
			FindNodeValue(ResNode,"IDS_Start_Time1",strStartTimeDes);
			FindNodeValue(ResNode,"IDS_End_Time2",strEndTimeLabel);
			FindNodeValue(ResNode,"IDS_End_Time2",strEndTimeDes);
			FindNodeValue(ResNode,"IDS_Query",strQueryBtn);
			FindNodeValue(ResNode,"IDS_Trend_Report",strTrendTitle);
			FindNodeValue(ResNode,"IDS_The_Week",strWeek);
			FindNodeValue(ResNode,"IDS_The_Day",strDay);
		}
		CloseResource(objRes);
	}

}

/*******************************************************************
参数：
parent: 容器

功能：
构造函数

返回值：

*******************************************************************/
ContrastReportFrame::ContrastReportFrame(WContainerWidget *parent)
: WContainerWidget(parent)
{
	loadString();

	index = 0;

	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
	}

	m_trendReport = NULL;

	new WText("<SCRIPT language='JavaScript' src='/menu.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript' src='/Calendar.js'></SCRIPT>", this);


	char cFile[1024]={0};
	sprintf(cFile,"%s\\data\\svdbconfig.ini",GetSiteViewRootPath().c_str());
	INIFile ini2 = LoadIni(cFile);
	std::string strLan= GetIniSetting(ini2,"svdb", "DefaultLanguage", "chinese");
	//########################################################################################################//新建时间界面------------juxian.zhang


	m_pTreePanView = new WSTreeAndPanTable(this);
	AddJsParam("treeviewPanel", m_pTreePanView->formName());
	new WText("<div id='tree_panel' name='tree_panel' class='panel_tree'>", m_pTreePanView->elementAt(0, 0));

	//树
	WTable * pTreeTable = new WTable(m_pTreePanView->elementAt(0, 0));
	new WText ("&nbsp;",pTreeTable->elementAt(0,0));
	m_pTrendReportTree = new CCheckBoxTreeView((WTableCell*)pTreeTable->elementAt(1, 0));
	if(m_pTrendReportTree)
	{
		string strSection = GetWebUserID();

		m_pTrendReportTree->InitTree("", false, true, false, strSection);
		WObject::connect(m_pTrendReportTree, SIGNAL(ReportQueryRequest()), this, SLOT(ReportQueryResponse()));
	}
	m_pTrendReportTree->setStyleClass("viewtreebody");
	new WText("</div>", pTreeTable->elementAt(0, 0));


	//DragTable
	AddJsParam("drag_tree", m_pTreePanView->elementAt(0, 1)->formName());


	//ViewPan
	new WText("<div id='view_panel' class='panel_view'>", m_pTreePanView->elementAt(0, 2));
	
	m_pMainTable = new WSVMainTable(m_pTreePanView->elementAt(0,2),"对比报告",true);

	timeTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(0,0),Query,"时间选择");

	if(timeTable->GetContentTable() != NULL)	
	{

		timeTable->InitTable();
		timeTable->AppendRows();	

		pAlertStartTime = new WLineEdit("",  timeTable->AppendRowsContent(0, 0, 0, strStartTimeLabel,"", ""));	
		pAlertStartTime->setStyleClass("input_text");
		TTime curTime = TTime::GetCurrentTimeEx();
		TTimeSpan ts(0,24,0,0);
		curTime -= ts;
		pAlertStartTime->setText(curTime.Format());
		strcpy(pAlertStartTime->contextmenu_ , "onFocus=\"calendar()\"");

		pAlertEndTime = new WLineEdit("",  timeTable->AppendRowsContent(0,1, 0, strEndTimeLabel,"", ""));
		pAlertEndTime->setStyleClass("input_text");
		curTime = TTime::GetCurrentTimeEx();
		pAlertEndTime->setText(curTime.Format());
		strcpy(pAlertEndTime->contextmenu_ , "onFocus=\"calendar()\"");

	}

	if(timeTable->GetActionTable()!=NULL)
	{
		timeTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		timeTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		WSVButton *pQueryBtn = new WSVButton(timeTable->GetActionTable()->elementAt(0,3),strQueryBtn,"button_bg_m_black.png","",true);	
		connect(pQueryBtn,SIGNAL(clicked()),"showbar()",this,SLOT(TrendReportQuery()),WObject::ConnectionType::JAVASCRIPTDYNAMIC);	

	}

	reportTable = new WTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1, 0));

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	pTranslateBtn = new WPushButton("Translate",this);
	pExChangeBtn = new WPushButton("Refresh",this);
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}



	new WText("</div>",this);
	AddJsParam("uistyle", "treepan");
	AddJsParam("bGeneral", "false");
	AddJsParam("fullstyle", "true");
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", this);
	new WText("<SCRIPT language='JavaScript'>SetTreeViewPanel();</SCRIPT>", this);

}
//########################################################################################################//

/*********************************************
参数：

功能：
析构函数

返回值：

*********************************************/
ContrastReportFrame::~ContrastReportFrame()
{
	if( objRes !=INVALID_VALUE )
		CloseResource(objRes);
}


/**************************************
参数：

功能：
刷新

返回值：

**************************************/
void ContrastReportFrame::refresh()
{
	//刷新树
	string strSection = GetWebUserID();
	m_pTrendReportTree->InitTree("", false, true, false, strSection);

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}
}

/****************************************
参数：

功能：

返回值：
****************************************/
void ContrastReportFrame::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/trendreport.exe?'\",1250);  ";
	appSelf->quit();
}

/******************************************
参数：

功能：
翻译

返回值：

******************************************/
void ContrastReportFrame::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "trendreportRes";
	WebSession::js_af_up += "')";
}

/***************************************************
参数：

功能：
对比报告查询

返回值：
***************************************************/
void ContrastReportFrame::TrendReportQuery()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "contrastreport";
	LogItem.sHitFunc = "TrendReportQuery";
	LogItem.sDesc = strQueryBtn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	GetGroupRightList();
	list<string>::iterator rightitem;
	list<string> monitorlist;
	OBJECT hTemplet;

	GetMonitorId(pGroupRightList, monitorlist);

	list<string>::iterator testsmlitem;	
	for(int j = 0; j < index; j++)
	{
		smlname[j] = "";
		for(testsmlitem = sml[j].begin(); testsmlitem != sml[j].end(); testsmlitem++)
		{		
			string temp = *testsmlitem;
			free((void*)temp.c_str());
		}
		sml[j].clear();
	}

	index = 0;
	for(rightitem = monitorlist.begin(); rightitem != monitorlist.end(); rightitem++)
	{
		string getvalue = "";
		string strRight = *rightitem;		
		OBJECT hMon = GetMonitor(strRight);		
		MAPNODE ma=GetMonitorMainAttribNode(hMon);

		//monitortemplet ID
		if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
		{						 			
			bool ret = false;
			for(int j = 0; j < index; j ++)
			{
				if(strcmp(getvalue.c_str(), smlname[j].c_str()) == 0)
				{
					sml[j].push_back(strdup(strRight.c_str()));
					ret = true;
					break;
				}
			}

			if(!ret)
			{				
				smlname[index] = getvalue.c_str();
				sml[index].push_back(strRight.c_str());			
				index++;
			}
		}	
		CloseMonitor(hMon);
	}

	for(int j = 0; j < index; j++)
	{
		OutputDebugString("---------------sml number-----------------\n");
		OutputDebugString(smlname[j].c_str());
		OutputDebugString("\n");

		for(testsmlitem = sml[j].begin(); testsmlitem != sml[j].end(); testsmlitem++)
		{
			string str = *testsmlitem;
			OutputDebugString(str.c_str());
			OutputDebugString("\n");
		}

	}

	m_startTime = MakeTTime(pAlertStartTime->text());
	m_endTime = MakeTTime(pAlertEndTime->text());

	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
	WebSession::js_af_up = "hiddenbar()";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
/*************************************************************
参数：
name:JAVASCRIPT变量名称
value: JAVASCRIPT值

功能：
添加客户端脚本变量

返回值：

*************************************************************/
void ContrastReportFrame::AddJsParam(const std::string name, 
									 const std::string value)
{  
	std::string strTmp = "";
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

//
void ContrastReportFrame::ReportQueryResponse()
{
	m_startTime = MakeTTime(pAlertStartTime->text());
	m_endTime = MakeTTime(pAlertEndTime->text());
	ChangeTrendReport(m_strMonitorid, m_startTime, m_endTime);
}

void ContrastReportFrame::ChangeTrendReport(string strMonitorid,
											TTime startTime,
											TTime endTime)
{
	if(m_trendReport == NULL)
	{
		m_trendReport = new CContrastReport(startTime, endTime, smlname,sml, index,\
			true, true, true, true, true, (WContainerWidget *)reportTable->elementAt(0, 0));
	}
	else
	{		
		m_trendReport->clear();
		delete m_trendReport;
		m_trendReport  = new CContrastReport(startTime, endTime, smlname, sml, index,\
			true, true, true, true, true, (WContainerWidget *)reportTable->elementAt(0, 0));
	}
}

void ContrastReportFrame::GetGroupChecked(WTreeNode*pNode,
										  std::list<string > &pGroupRightList_,
										  std::list<string > &pUnGroupRightList_)
{
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			if(pNode->treeCheckBox_->isChecked())
			{
				pGroupRightList_.push_back(pNode->strId);
				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_);

			}
			else
			{
				pUnGroupRightList_.push_back(pNode->strId);
				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_);
			}
		}
		else
		{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
				GetGroupChecked(pNode->childNodes()[i],pGroupRightList_,pUnGroupRightList_);
		}
	}
	return;

}

void ContrastReportFrame::GetGroupRightList()
{
	pGroupRightList.clear();
	pUnGroupRightList.clear();
	if(m_pTrendReportTree->treeroot!=NULL)
	{
		GetGroupChecked(m_pTrendReportTree->treeroot,pGroupRightList,pUnGroupRightList);

	}

}

void ContrastReportFrame::GetMonitorId(list<string> grouplist, 
									   list<string> & monitorlist)
{
	list<string>::iterator item;
	list<string>::iterator monitorlistitem;

	for(item = grouplist.begin(); item != grouplist.end(); item++)
	{			
		std::string monitorid = *item;				

		//取监测器组句柄
		OBJECT	hGroup = GetGroup(monitorid);
		std::list<string> monitoridlist;
		std::list<string>::iterator monitoridlistitem;

		//组句柄无效则判断是否为设备或监测器
		if(hGroup == INVALID_VALUE)
		{
			//取设备句柄
			hGroup = GetEntity(monitorid);
			//是设备
			if(hGroup != INVALID_VALUE)
			{		
				//取设备下的所有子监测器（monitoridlist为list<string>类型）
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
						//monitorlist中存在monitorid则跳到cont
						if(strcmp( tempid1.c_str(), tempid.c_str()) == 0)
						{
							goto cont;
						}
					}

					//把monitoridlist组合进monitorlist,并销毁monitoridlist
					monitorlist.merge(monitoridlist);
				}
			}
			//是监测器
			else
			{		
				//比较monitorid是否在monitorlist中
				for(monitorlistitem = monitorlist.begin(); monitorlistitem != monitorlist.end();\
					monitorlistitem++)
				{
					std::string tempid = *monitorlistitem;
					//monitorlist中存在monitorid则跳到cont
					if(strcmp( monitorid.c_str(), tempid.c_str()) == 0)
					{
						goto cont;
					}
				}
				//根据监测器ID取指定时段的数据
				monitorlist.push_back(monitorid);				
			}
		}
		//是组,暂未处理要取组下的所有监测器
		else
		{					
			EnumGroup(monitorid, monitorlist);			
		}
		//如果存在监测器ID则返回循环
cont:
		;
	}
}


////////////////////////////////////////////////////////////////////////////////////
typedef void( *func)(int , char **);

void wmain1(int argc, char *argv[])
{
	WApplication app(argc, argv);
	pTreeApp = &app;
	app.setTitle("Siteview 7.0");
	string strTmp = "";

	ContrastReportFrame firsttest(app.root());
	firsttest.appSelf = &app;

	strTmp +="class='workbody'";
	app.setBodyAttribute(strTmp.c_str());

	app.exec();
}

//
int main(int argc, char * argv[])
{
	func p = wmain1;
	if (argc == 1) 
	{
		srand((unsigned)time( NULL ));
		int rand1 = rand();
		char buf[256];
		itoa(rand1, buf, 10);
		WebSession s(buf, false);
		//s.setRefreshTime(1);
		s.start(p);
		return 1;
	}
	else
	{
		FCGI_Accept();
		WebSession s("DEBUG", true);
		s.start(p);
		return 1;
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////////////



