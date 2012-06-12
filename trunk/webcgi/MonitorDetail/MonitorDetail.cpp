#include "stdafx.h"
#include ".\monitordetail.h"
/////////////////////////////////////////
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVButton.h"
/////////////////////////////////////////
#include "WApplication"
#include "WebSession.h"
#include <WText>
#include <WPushButton>
/////////////////////////////////////////
#include "cspreadsheet.h"
#include "../base/OperateLog.h"
/////////////////////////////////////////
#include <string>
#include <list>

using namespace std;
using namespace svutil;

#define RecordCountPerPage 30

CMonitorDetail::CMonitorDetail(WContainerWidget *parent): 
	WContainerWidget(parent)
{
	m_pMainTable = NULL;
	m_pUserListTable = NULL;
	m_bRefresh = false;
	m_iForwardORBack = 1;

	loadString();
	initForm();
}

void CMonitorDetail::loadString()
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_MonitorReport",m_szMainTitile);
			FindNodeValue(ResNode,"IDS_Monitor_Name",m_szName);
			FindNodeValue(ResNode,"IDS_Group_Name",m_szGroupName);
			FindNodeValue(ResNode,"IDS_Type",m_szType);
			FindNodeValue(ResNode,"IDS_MontioFreq",m_szFrequent);
			FindNodeValue(ResNode,"IDS_Clique_Value",m_szValue);
			FindNodeValue(ResNode,"IDS_Forward",m_szForward);
			FindNodeValue(ResNode,"IDS_Back",m_szBack);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",m_szPage);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",m_szPageCount);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",m_szRecordCount);
			FindNodeValue(ResNode,"IDS_Generate_Excel_Table",m_szExport);
			FindNodeValue(ResNode,"IDS_Minute",m_szMinute);
			FindNodeValue(ResNode,"IDS_Hour",m_szHour);
			FindNodeValue(ResNode,"IDS_Error",m_szError);
			FindNodeValue(ResNode,"IDS_Warning",m_szWarning);
			FindNodeValue(ResNode,"IDS_Normal",m_szNormal);
			FindNodeValue(ResNode,"IDS_GoodClique",m_szGoodValue);
			FindNodeValue(ResNode,"IDS_WarningClique",m_szWarningValue);
			FindNodeValue(ResNode,"IDS_ErrorClique",m_szErrorValue);
			FindNodeValue(ResNode,"IDS_DownloadList",m_szDownLoad);
			FindNodeValue(ResNode,"IDS_Close",m_szConfirm);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
		}
		CloseResource(objRes);
	}
}

void CMonitorDetail::initForm()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);
	m_pMainTable = new WSVMainTable(this,m_szMainTitile,false);

	if(m_pMainTable)
	{
		m_pUserListTable = new WSVFlexTable((WContainerWidget *)m_pMainTable->GetContentTable()->elementAt(1,0), List ,m_szMainTitile);	
		m_pUserListTable->SetDivId("listpan1");
		if(m_pUserListTable->GetContentTable()!=NULL)
		{
//			m_pUserListTable->SetDivId("listpan1");
			addColumn(m_pUserListTable);
			addOperate(m_pUserListTable);

			AddJsParam("listheight", m_szListHeights);
			AddJsParam("listtitle", m_szListTitles);
			AddJsParam("listpan", m_szListPans);
			AddJsParam("uistyle", "viewpanandlist");
			AddJsParam("fullstyle", "true");
			AddJsParam("bGeneral", "true");
			new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);
			new WText("</div>", this);
		}
	}
}

void CMonitorDetail::addColumn(WSVFlexTable * pParentTable)
{
	m_szListHeights = "680";
	m_szListHeights += ",";
	m_szListPans = pParentTable->GetDivId();
	m_szListPans += ",";
	m_szListTitles =  pParentTable->dataTitleTable->formName();
	m_szListTitles += ",";

	pParentTable->AppendColumn("",WLength(2,WLength::Pixel));
	pParentTable->SetDataRowStyle("table_data_grid_item_img");
	pParentTable->AppendColumn(m_szName,WLength(30,WLength::Percentage));
	pParentTable->SetDataRowStyle("table_data_grid_item_text");
	pParentTable->AppendColumn(m_szGroupName,WLength(15,WLength::Percentage));     
	pParentTable->SetDataRowStyle("table_data_grid_item_text");
	pParentTable->AppendColumn(m_szType,WLength(10,WLength::Percentage));     
	pParentTable->SetDataRowStyle("table_data_grid_item_text");
	pParentTable->AppendColumn(m_szFrequent,WLength(10,WLength::Percentage));      
	pParentTable->SetDataRowStyle("table_data_grid_item_text");
	pParentTable->AppendColumn(m_szValue,WLength(45,WLength::Percentage));
	pParentTable->SetDataRowStyle("table_data_grid_item_text");
}

void CMonitorDetail::getMonitors()
{
	MonitorList.clear();
	PAIRLIST getDevList;
	PAIRLIST::iterator getDevItem;
	list<string> getMonList;
	list<string>::iterator getMonItem;
    if(GetAllEntitysInfo(getDevList))
	{
		OBJECT	objDevice;
		for(getDevItem=getDevList.begin(); getDevItem!=getDevList.end(); getDevItem++)
		{
			objDevice = GetEntity(getDevItem->name);
			if(objDevice!=INVALID_VALUE)
			{
				MAPNODE deviceNode = GetEntityMainAttribNode(objDevice);
				string deviceName;
				bool bFind = FindNodeValue(deviceNode, "sv_name", deviceName);

				if(GetSubMonitorsIDByEntity(objDevice, getMonList))
				{
					OBJECT objRes=LoadResource("default", "localhost");  
					if( objRes !=INVALID_VALUE )
					{	
						MAPNODE ResNode=GetResourceNode(objRes);
						if( ResNode != INVALID_VALUE )
						{
							OBJECT objMonitor;
							MAPNODE monitorNode;
							OBJECT objTempMonitor;
							MAPNODE monitorTempNode;
							for(getMonItem=getMonList.begin(); getMonItem!=getMonList.end(); getMonItem++)
							{
								string MonitorID = *getMonItem;
								//	设备名称
								string szDot = ".";
								size_t nPos1 = MonitorID.rfind(szDot);
								string szEntityID = MonitorID.substr(0, nPos1);
								size_t nPos2 = szEntityID.rfind(szDot);
								string szGroupID = szEntityID.substr(0, nPos2);
								OBJECT	objGroup = GetGroup(szGroupID);
								if(objGroup!=INVALID_VALUE)
								{
									string szname;
									MAPNODE GroupNode = GetGroupMainAttribNode(objGroup);
									bFind = FindNodeValue(GroupNode, "sv_name", szname);
									iItem.szGroupName = szname;
									CloseGroup(objGroup);
								}
								else
								{
									OBJECT	objSE = GetSVSE(szEntityID);
									if(objSE != INVALID_VALUE)
									{
										iItem.szGroupName = GetSVSELabel(objSE);
										CloseSVSE(objSE);
									}							
								}
								objMonitor = GetMonitor(MonitorID);
								if(objMonitor!=INVALID_VALUE)
								{
									monitorNode = GetMonitorMainAttribNode(objMonitor);
									//监测器名称
									string strTemp,monitorName;
									bFind = FindNodeValue(monitorNode, "sv_name", strTemp);
									monitorName = deviceName + ":" + strTemp;
									iItem.sName = monitorName;
									//监测器类型
									string TypeID,TypeIDS;
									bFind = FindNodeValue(monitorNode, "sv_monitortype", TypeID);
									int iType = atoi(TypeID.c_str());
									objTempMonitor = GetMonitorTemplet(iType);
									if(objTempMonitor!=INVALID_VALUE)
									{
										monitorTempNode = GetMTMainAttribNode(objTempMonitor);	
										bFind = FindNodeValue(monitorTempNode, "sv_label", TypeIDS);	
										FindNodeValue(ResNode,TypeIDS,iItem.sType);
									}	
									//监测频率
									monitorNode = GetMonitorParameter(objMonitor);
									//监测器名称
									bFind = FindNodeValue(monitorNode, "_frequency", strTemp);
									int iTemp,iTemp1;
									iTemp = atoi(strTemp.c_str());
									iTemp1 = iTemp % 60;
									if(iTemp1 == 0)
									{
										iTemp1 = iTemp / 60;
										char buf1[256] = {""};
										itoa(iTemp1, buf1, 10);
										strTemp = buf1;	
										iItem.sFrequest = strTemp + m_szHour;
									}
									else
									{
										iItem.sFrequest = strTemp + m_szMinute;	
									}

									PAIRLIST ParamList;
									LISTITEM ParamItem;
									//正常
									string strCondition = m_szNormal;
									strCondition += ": ";
									string strTempCon = "";
									monitorNode = GetMonitorGoodAlertCondition(objMonitor);
									if(monitorNode != INVALID_VALUE)
									{
										string strCount,strParamName,strParamValue,strParamOperate,strParamRelation,strReturn;
										bFind = FindNodeValue(monitorNode, "sv_conditioncount", strCount);
										int iCount = atoi(strCount.c_str());
										for(int i=1; i<=iCount; i++)
										{
											strTempCon = "[";
											string buffer;
											char buf2[256] = {""};
											itoa(i,buf2,10);
											buffer = buf2;
											strTemp = "sv_paramname" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											if(objTempMonitor!=INVALID_VALUE)
											{
												//返回值
												if(FindMTReturnFirst(objTempMonitor,ParamItem))
												{
													while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
													{ 
														ParamList.clear();
														if(::EnumNodeAttrib(monitorTempNode,ParamList))
														{	
															string sReturnName = "", MonitorIDSName ="", MonitorIDSValue ="";
															FindNodeValue(monitorTempNode, "sv_name",sReturnName);
															if(sReturnName == strReturn)
															{
																FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
																FindNodeValue(ResNode,MonitorIDSName,MonitorIDSValue);
																strTempCon += MonitorIDSValue;
															}
														}
													}
												}
											}	
											strTemp = "sv_operate" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											strTempCon += strReturn;
											strTemp = "sv_paramvalue" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											strTempCon += strReturn;
											strTempCon += "]";
											if(i<iCount)
											{
												strTemp = "sv_relation" + buffer;
												bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
												strTempCon += strReturn;											
											}
										}
									}
									iItem.sGoodClique = strTempCon;
									strCondition += strTempCon;
									strCondition += ";<br>";
									//危险
									strCondition += "&nbsp;";
									strCondition += m_szWarning;
									strCondition += ": ";
									monitorNode = GetMonitorWarningAlertCondition(objMonitor);
									if(monitorNode != INVALID_VALUE)
									{
										string strCount,strParamName,strParamValue,strParamOperate,strParamRelation,strReturn;
										bFind = FindNodeValue(monitorNode, "sv_conditioncount", strCount);
										int iCount = atoi(strCount.c_str());
										for(int i=1; i<=iCount; i++)
										{
											strTempCon = "[";
											string buffer;
											char buf3[256] = {""};
											itoa(i,buf3,10);
											buffer = buf3;
											strTemp = "sv_paramname" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											if(objTempMonitor!=INVALID_VALUE)
											{
												//返回值
												if(FindMTReturnFirst(objTempMonitor,ParamItem))
												{
													while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
													{ 
														ParamList.clear();
														if(::EnumNodeAttrib(monitorTempNode,ParamList))
														{	
															string sReturnName = "", MonitorIDSName ="", MonitorIDSValue ="";
															FindNodeValue(monitorTempNode, "sv_name",sReturnName);
															if(sReturnName == strReturn)
															{
																FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
																FindNodeValue(ResNode,MonitorIDSName,MonitorIDSValue);
																strTempCon += MonitorIDSValue;
															}
														}
													}
												}
											}	
											strTemp = "sv_operate" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											strTempCon += strReturn;
											strTemp = "sv_paramvalue" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											strTempCon += strReturn;
											strTempCon += "]";
											if(i<iCount)
											{
												strTemp = "sv_relation" + buffer;
												bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
												strTempCon += strReturn;											
											}
										}
									}
									iItem.sWarningClique = strTempCon;
									strCondition += strTempCon;
									strCondition += ";<br>";
									//错误
									strCondition += "&nbsp;";
									strCondition += m_szError;
									strCondition += ": ";
									monitorNode = GetMonitorErrorAlertCondition(objMonitor);
									if(monitorNode != INVALID_VALUE)
									{
										string strCount,strParamName,strParamValue,strParamOperate,strParamRelation,strReturn;
										bFind = FindNodeValue(monitorNode, "sv_conditioncount", strCount);
										int iCount = atoi(strCount.c_str());
										for(int i=1; i<=iCount; i++)
										{
											strTempCon = "[";
											string buffer;
											char buf4[256] = {""};
											itoa(i,buf4,10);
											buffer = buf4;
											strTemp = "sv_paramname" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											if(objTempMonitor!=INVALID_VALUE)
											{
												//返回值
												if(FindMTReturnFirst(objTempMonitor,ParamItem))
												{
													while((monitorTempNode=::FindNext(ParamItem))!=INVALID_VALUE )
													{ 
														ParamList.clear();
														if(::EnumNodeAttrib(monitorTempNode,ParamList))
														{	
															string sReturnName = "", MonitorIDSName ="", MonitorIDSValue ="";
															FindNodeValue(monitorTempNode, "sv_name",sReturnName);
															if(sReturnName == strReturn)
															{
																FindNodeValue(monitorTempNode, "sv_label",MonitorIDSName);
																FindNodeValue(ResNode,MonitorIDSName,MonitorIDSValue);
																strTempCon += MonitorIDSValue;
															}
														}
													}
												}
											}	
											strTemp = "sv_operate" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											strTempCon += strReturn;
											strTemp = "sv_paramvalue" + buffer;
											bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
											strTempCon += strReturn;
											strTempCon += "]";
											if(i<iCount)
											{
												strTemp = "sv_relation" + buffer;
												bFind = FindNodeValue(monitorNode, strTemp, strReturn);	
												strTempCon += strReturn;											
											}
										}
									}
									iItem.sErrorClique = strTempCon;
									strCondition += strTempCon;
									strCondition += ";";
									//////////
									iItem.sClique = strCondition;										
									MonitorList.push_back(iItem);
									ParamList.clear();
									CloseMonitorTemplet(objTempMonitor);
									CloseMonitor(objMonitor);
								}
							}
						}
						CloseResource(objRes);
					}
				}
				bFind = CloseEntity(objDevice);
			}
			getMonList.clear();
		}
		getDevList.clear();	
	}
}

void CMonitorDetail::addData(WSVFlexTable * pParentTable)
{
	m_iForwardORBack = 1;
	int iRow=1;
	for(RecordItem=MonitorList.begin(); RecordItem != MonitorList.end(); RecordItem++)
	{
		pParentTable->InitRow(iRow);
		int iColNum = 0;
		new WText("&nbsp;" , (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;
		new WText(RecordItem->sName, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;
		new WText(RecordItem->szGroupName, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;
		new WText(RecordItem->sType, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;
		new WText(RecordItem->sFrequest, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		iColNum += 2;
		new WText(RecordItem->sClique, (WContainerWidget *)pParentTable->GeDataTable()->elementAt(iRow,iColNum));
		if(iRow == RecordCountPerPage)
		{
			RecordItem++;
			return;
		}
		iRow++;
	}	
}

void CMonitorDetail::addOperate(WSVFlexTable * pParentTable)
{
	if(pParentTable->GetActionTable() != NULL)
	{
		WTable * pSubTab;

		((WContainerWidget *)pParentTable->GetActionTable()->elementAt(0,1))->setContentAlignment(AlignLeft);
		((WContainerWidget *)pParentTable->GetActionTable()->elementAt(0,1))->setStyleClass("textbold");
		pSubTab = new WTable((WContainerWidget *)pParentTable->GetActionTable()->elementAt(0,1));
		pSubTab->setStyleClass("widthauto");

		new WText("&nbsp;&nbsp;&nbsp;&nbsp;",(WContainerWidget *)pSubTab->elementAt(0,0));
		
		((WContainerWidget *)pSubTab->elementAt(0,1))->resize(WLength(50,WLength::Pixel),0);
		((WContainerWidget *)pSubTab->elementAt(0,1))->setStyleClass("textbold");
		WText * mForward = new WText(m_szBack, (WContainerWidget *)pSubTab->elementAt(0,1));
		mForward->setStyleClass("linktext");
		connect(mForward, SIGNAL(clicked()), this, SLOT(LogForward()));

		((WContainerWidget *)pSubTab->elementAt(0,2))->resize(WLength(50,WLength::Pixel),0);
		((WContainerWidget *)pSubTab->elementAt(0,2))->setStyleClass("textbold");
		WText * mBack = new WText(m_szForward, (WContainerWidget *)pSubTab->elementAt(0,2));
		mBack->setStyleClass("linktext");
		connect(mBack, SIGNAL(clicked()), this, SLOT(LogBack()));

		//页
		((WContainerWidget *)pSubTab->elementAt(0,3))->setStyleClass("textbold");
		((WContainerWidget *)pSubTab->elementAt(0,3))->resize(WLength(70,WLength::Pixel),0);
		WText *wPage = new WText(m_szPage, (WContainerWidget *)pSubTab->elementAt(0,3));
		wPage->setStyleClass("widthauto");
		size_t recordCount = MonitorList.size();
		if(recordCount > 0)
		{
			m_pPage = new WText("1", (WContainerWidget *)pSubTab->elementAt(0,3));
		}
		else
		{
			m_pPage = new WText("0", (WContainerWidget *)pSubTab->elementAt(0,3));
		}
		//页数
		((WContainerWidget *)pSubTab->elementAt(0,4))->setStyleClass("textbold");
		((WContainerWidget *)pSubTab->elementAt(0,4))->resize(WLength(100,WLength::Pixel),0);
		WText *wPageCount = new WText(m_szPageCount, (WContainerWidget *)pSubTab->elementAt(0,4));
		wPageCount->setStyleClass("widthauto");
		int pageCount = recordCount / RecordCountPerPage;
		int pageYu = recordCount % RecordCountPerPage;
		if(pageYu != 0)
		{
			pageCount += 1;
		}
		char buf[256];
		itoa(pageCount,buf,10);
		string strTemp = buf;
		m_pPageCount = new WText(strTemp, (WContainerWidget *)pSubTab->elementAt(0,4));
		//记录数
		((WContainerWidget *)pSubTab->elementAt(0,5))->setStyleClass("textbold");
		((WContainerWidget *)pSubTab->elementAt(0,5))->resize(WLength(200,WLength::Pixel),0);
		WText *wRecordCount = new WText(m_szRecordCount, (WContainerWidget *)pSubTab->elementAt(0,5));
		wRecordCount->setStyleClass("widthauto");
		itoa(recordCount,buf,10);
		strTemp = buf;
		m_pRecordCount = new WText(strTemp, (WContainerWidget *)pSubTab->elementAt(0,5));
		
		((WContainerWidget *)pSubTab->elementAt(0,6))->resize(WLength(100,WLength::Pixel),0);
		new WText("&nbsp", (WContainerWidget *)pSubTab->elementAt(0,6));

		//导出execl
		WTable * pSubTab2 = new WTable((WContainerWidget *)pParentTable->GetActionTable()->elementAt(0,2));
		pSubTab2->setStyleClass("widthauto");
		m_pExport = new WSVButton(((WContainerWidget *)pSubTab2->elementAt(0,1)), m_szExport,"button_bg_m_black.png","",true);	
		if(m_pExport)
			connect(m_pExport,SIGNAL(clicked()),"showbar();",this,SLOT(ExportExcel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		
		new WText("&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pSubTab2->elementAt(0,2));

		m_pHidden = new WSVButton(((WContainerWidget *)pSubTab2->elementAt(0,3)), "","button_bg_m_black.png","",true);	
		if(m_pHidden)
		{
			m_pHidden->hide();
			connect(m_pHidden,SIGNAL(clicked()),this,SLOT(AutoClickHiddenBtn()));
			AddJsParamExecClick();
		}
	}
}

void CMonitorDetail::AutoClickHiddenBtn()
{
	if(m_pUserListTable)
	{
		MonitorList.clear();
		getMonitors();
		addData(m_pUserListTable);

		if(m_bRefresh)
		{
			size_t recordCount = MonitorList.size();
			//页
			if(recordCount > 0)
			{
				m_pPage->setText("1");
			}
			else
			{
				m_pPage->setText("0"); 
			}
			//页数
			int pageCount = recordCount / RecordCountPerPage;
			int pageYu = recordCount % RecordCountPerPage;
			if(pageYu != 0)
			{
				pageCount += 1;
			}
			char buf[256];
			itoa(pageCount,buf,10);
			string strTemp = buf;
			if(m_pPageCount)
				m_pPageCount->setText(strTemp);
			//记录数	
			itoa(recordCount,buf,10);
			strTemp = buf;
			if(m_pRecordCount)
				m_pRecordCount->setText(strTemp);
		}

		m_szListHeights1 = "680";
		m_szListPans1 = m_pUserListTable->GetDivId();
		m_szListTitles1 =  m_pUserListTable->dataTitleTable->formName();
		WebSession::js_af_up = "changeListHeight('";
		WebSession::js_af_up +=	m_szListPans1;
		WebSession::js_af_up +=	"','";
		WebSession::js_af_up += m_pUserListTable->dataTitleTable->formName();
		WebSession::js_af_up += "', '";
		WebSession::js_af_up +=	m_szListHeights1;
		WebSession::js_af_up +=	"');hiddenbar();";
	}
}

void CMonitorDetail::LogForward()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "MonitorDetail";
	LogItem.sHitFunc = "LogForward";
	LogItem.sDesc = m_szBack;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	if(m_iForwardORBack == 1)
	{
		bEnd = true;	
		goto OPEnd;	
	}
	if(RecordItem != MonitorList.begin())
	{		
		m_pUserListTable->GeDataTable()->clear();

		if(m_iForwardORBack == 2)
		{
			ItemForward = RecordItem;
			ItemForward ++;
		}
		else
		{
			ItemForward = ItemBack;
			ItemForward ++;
			RecordItem = ItemBack;
		}

		//当前页
		string strTemp = m_pPage->text();
		int buf = atoi(strTemp.c_str());
		buf -= 1;
		char buffer[256] = {0};
		itoa(buf, buffer, 10);
		strTemp = buffer;
		m_pPage->setText(strTemp);

		list<MonitorItem> RecordsList1;
		list<MonitorItem>::iterator RecordsListItem1;
		int i = 0;
		for(RecordItem; RecordItem != MonitorList.begin(); RecordItem--)
		{
			MonitorItem item;
			item.sName = RecordItem->sName;
			item.sType = RecordItem->sType;
			item.sFrequest = RecordItem->sFrequest;
			item.sClique = RecordItem->sClique;
		
			RecordsList1.push_back(item);
			
			i++;
			if(i == RecordCountPerPage)
			{
				RecordItem --;
				break;
			}
		}
		//处理第一条记录
		if(RecordItem == MonitorList.begin())
		{
			MonitorItem item;
			item.sName = RecordItem->sName;
			item.sType = RecordItem->sType;
			item.sFrequest = RecordItem->sFrequest;
			item.sClique = RecordItem->sClique;
		
			RecordsList1.push_back(item);
		}

		RecordsListItem1 = RecordsList1.end();
		RecordsListItem1 --;

		int iRow = 1;

		for(RecordsListItem1; RecordsListItem1 != RecordsList1.begin(); RecordsListItem1--)
		{
			m_pUserListTable->InitRow(iRow);
			int iColNum = 0;

			new WText("&nbsp;" , (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sName, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sType, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sFrequest, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sClique, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iRow++;
		}

		if(RecordsListItem1 == RecordsList1.begin())
		{
			iRow = RecordCountPerPage;
			m_pUserListTable->InitRow(iRow);
			int iColNum = 0;
			new WText("&nbsp;" , (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sName, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sType, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sFrequest, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordsListItem1->sClique, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
		}

		RecordsList1.clear();

		m_iForwardORBack = 2;

		DWORD dcalEnd1=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 -dcalBegin);
	}
}

void CMonitorDetail::LogBack()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "MonitorDetail";
	LogItem.sHitFunc = "LogBack";
	LogItem.sDesc = m_szForward;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	if(RecordItem != MonitorList.end())
	{
		m_pUserListTable->GeDataTable()->clear();

		if(m_iForwardORBack == 2)
		{
			ItemBack = ItemForward;
			ItemBack --;
			RecordItem = ItemForward;
		}
		else
		{
			ItemBack = RecordItem;
			ItemBack --;
		}

		//当前页
		string strTemp = m_pPage->text();
		int buf = atoi(strTemp.c_str());
		buf += 1;
		char buffer[256] = {0};
		itoa(buf, buffer, 10);
		strTemp = buffer;
		m_pPage->setText(strTemp);

		int iRow=1;
		for(RecordItem; RecordItem != MonitorList.end(); RecordItem++)
		{
			m_pUserListTable->InitRow(iRow);
			int iColNum = 0;
			new WText("&nbsp;" , (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordItem->sName, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordItem->sType, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordItem->sFrequest, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));
			iColNum += 2;
			new WText(RecordItem->sClique, (WContainerWidget *)m_pUserListTable->GeDataTable()->elementAt(iRow,iColNum));

			m_iForwardORBack = 3;

			if(iRow == RecordCountPerPage)
			{
				RecordItem++;
				bEnd = true;	
				goto OPEnd;
			}
			iRow++;
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 -dcalBegin);
}

void CMonitorDetail::ExportExcel()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "MonitorDetail";
	LogItem.sHitFunc = "ExportExcel";
	LogItem.sDesc = m_szExport;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	OutputDebugString("\n----------ExportExcel Begin-------------\n");
	std::string szFilePath =GetSiteViewRootPath();
	szFilePath += "\\htdocs\\MonitorReport\\";

	string szFileName = "MonitorReport";
	TTime timer = TTime::GetCurrentTimeEx();

	char buf[100]={0};
	sprintf(buf,"%d-%02d-%02d-%2d-%02d-%02d", timer.GetYear(), timer.GetMonth(), timer.GetDay(), timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	szFileName += buf;
	szFileName += ".xls";
	szFilePath += szFileName;

	CSpreadSheet SS(szFilePath.c_str(), "MonitorDetail");

	CStringArray headerArray, contentArray;
	
	SS.BeginTransaction();
	
	// 加入标题
	headerArray.RemoveAll();
	headerArray.Add(m_szName.c_str());
	headerArray.Add(m_szGroupName.c_str());
	headerArray.Add(m_szType.c_str());
	headerArray.Add(m_szFrequent.c_str());
	headerArray.Add(m_szGoodValue.c_str());
	headerArray.Add(m_szWarningValue.c_str());
	headerArray.Add(m_szErrorValue.c_str());
	SS.AddHeaders(headerArray);

	for(RecordItem=MonitorList.begin(); RecordItem != MonitorList.end(); RecordItem++)
	{
		contentArray.RemoveAll();
		contentArray.Add(RecordItem->sName.c_str());
		contentArray.Add(RecordItem->szGroupName.c_str());
		contentArray.Add(RecordItem->sType.c_str());
		contentArray.Add(RecordItem->sFrequest.c_str());
		contentArray.Add(RecordItem->sGoodClique.c_str());
		contentArray.Add(RecordItem->sWarningClique.c_str());
		contentArray.Add(RecordItem->sErrorClique.c_str());
		SS.AddRow(contentArray);
	}	

	SS.Commit();		
	
	OutputDebugString("\n----------ExportExcel End-------------\n");
	
	DWORD dcalEnd=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

	OutputDebugString("\n----------showDownload-------------\n");
	
	string sDown = "hiddenbar();showDownload('<a href=/MonitorReport/";
	sDown += szFileName;
	sDown += " target=_blank>";
	sDown += szFileName;
	sDown += "</a>','";
	sDown += m_szDownLoad;
	sDown += "','";
	sDown += m_szConfirm;
	sDown += "')";
	WebSession::js_af_up = sDown;
}
//刷新
void CMonitorDetail::refresh()
{
	OutputDebugString("\n---------refresh begin---------\n");
	if(m_bRefresh)
	{
		string strUserID = GetWebUserID();

		HitLog LogItem;
		LogItem.sUserName = strUserID;
		LogItem.sHitPro = "MonitorDetail";
		LogItem.sHitFunc = "refresh";
		LogItem.sDesc = strRefresh;

		DWORD dcalBegin=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);


		m_pUserListTable->GeDataTable()->clear();
		//页
		if(m_pPage)
		{
			m_pPage->setText("0"); 
		}
		//页数
		if(m_pPageCount)
			m_pPageCount->setText("0");
		//记录数	
		if(m_pRecordCount)
			m_pRecordCount->setText("0");

		AddJsParamExecClick();

		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);

	}
	m_bRefresh = true;

	OutputDebugString("\n---------refresh end---------\n");
}

CMonitorDetail::~CMonitorDetail(void)
{
}

//添加客户端脚本变量
void CMonitorDetail::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CMonitorDetail::AddJsParamExecClick()
{  
	string strDelDes = m_pHidden->getEncodeCmd("xclicked()") ;

	std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript'>AutoExecBtnClick(\"";
	strTmp += strDelDes;
	strTmp += "\");";
    strTmp += "</SCRIPT>";
	new WText(strTmp, this);
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
	app.setTitle("MonitorDetail");
 	CMonitorDetail setform(app.root());
	app.setBodyAttribute("class='workbody' ");
	app.exec();
}
int main(int argc, char *argv[])
{
    func p = usermain;
    //WriteRightTpl();
	if (argc == 1) 
    {
		WebSession s("25", false);
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