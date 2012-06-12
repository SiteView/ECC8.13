#include ".\tuoplist.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVButton.h"
#include "svapi.h"
//#include "../../base/GetInstallPath.h"
#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

//是否是拓扑列表
#define Tuopu

//新增的Sort相关函数
int GetMaxSortId()
{
	int nMaxId = 0;
	std::list<string> keylist;
	std::list<string>::iterator itemkey;

#ifdef	 Tuopu
	bool bret = GetIniFileKeys("sort", keylist, "tuopfile.ini");
#else
	bool bret = GetIniFileKeys("sort", keylist, "maintainfile.ini");
#endif

	if(bret)
	{
		std::string sVal = "";
		
		int nSort = 0;
		for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
		{
			sVal = *itemkey;
		#ifdef	 Tuopu
			nSort = GetIniFileInt("sort", sVal, -1, "tuopfile.ini");
		#else
			nSort = GetIniFileInt("sort", sVal, -1, "maintainfile.ini");
		#endif
			
			//char chItem[32]  = {0};	
			//sprintf(chItem, "%d", nSort);
			//string strSort = chItem;
			//
			//OutputDebugString("GetMaxSortId:");
			//OutputDebugString(strSort.c_str());
			
			if(nSort > nMaxId)
				nMaxId = nSort;
		}
	}

	return nMaxId;
}

//删除了拓扑图  序号怎么变？---》是直接删除呢？ 还是要加把其他的序号都整理一遍？---》或者把大于它的序号都减1即可。
void DelSortId(string strVsd)
{
	//获取要删除 sortid 删除该记录
	int nDelSortId = 0;	

	#ifdef	 Tuopu
		nDelSortId = GetIniFileInt("sort", strVsd, -1, "tuopfile.ini");			
		DeleteIniFileKey("sort", strVsd, "tuopfile.ini");
	#else
		nDelSortId = GetIniFileInt("sort", strVsd, -1, "maintainfile.ini");
		DeleteIniFileKey("sort", strVsd, "maintainfile.ini");
	#endif

	//删除了拓扑图  序号怎么变？---》是直接删除呢？ 还是要加把其他的序号都整理一遍？---》或者把大于它的序号都减1即可。
	std::list<string> keylist;
	std::list<string>::iterator itemkey;

#ifdef	 Tuopu
	bool bret = GetIniFileKeys("sort", keylist, "tuopfile.ini");
#else
	bool bret = GetIniFileKeys("sort", keylist, "maintainfile.ini");
#endif

	if(bret)
	{
		std::string sVal = "";
		
		int nSort = 0;
		for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
		{
			sVal = *itemkey;
		#ifdef	 Tuopu
			nSort = GetIniFileInt("sort", sVal, -1, "tuopfile.ini");
		#else
			nSort = GetIniFileInt("sort", sVal, -1, "maintainfile.ini");
		#endif
			
			if(nSort > nDelSortId)
			{
				nSort--;
				
			#ifdef	 Tuopu
				WriteIniFileInt("sort", sVal, nSort, "tuopfile.ini");
			#else
				WriteIniFileInt("sort", sVal, nSort, "maintainfile.ini");
			#endif
			}
		}
	}
}

bool DeleteDirectory(string path)
{
	OutputDebugString(path.c_str());
	WIN32_FIND_DATA fd;
	std::list<string> strlist;
	string strfilepath = path;
	strfilepath	+= "\\*.*";
	string strTmp = "";
    HANDLE fr=::FindFirstFile(strfilepath.c_str(),&fd);
    while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//
		}
        else
		{			
			strTmp = path;
			strTmp += "\\";
			strTmp += fd.cFileName;
			OutputDebugString(strTmp.c_str());
			if(!DeleteFile(strTmp.c_str()))
				return false;
		}
	}

	if(!RemoveDirectory(path.c_str()))
		return false;

	return true;
}

string ReplaceStdString(string strIn, string strFrom, string strTo)
{
	string strTmp = strIn;
	int nPos = strIn.find(strFrom, 0);
	int nLength = strFrom.length();

	if(nPos != -1)
	{
		strTmp = strIn.replace(nPos, nLength, strTo);
	}
	
	return strTmp;
}

bool GetUserRight(string strRight)
{
	bool bRight = false;
	string strSection = GetWebUserID();
	
	//管理员则有所有权限
	if(GetIniFileInt(strSection, "nAdmin", -1, "user.ini") != -1)
		return true;

	if(GetIniFileInt(strSection, strRight, 0, "user.ini") == 1)
		bRight = true;
	else
		bRight = false;
	return bRight;
	//return true;
}

CTuopList::CTuopList(WContainerWidget *parent ):
WContainerWidget(parent)
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
		#ifdef	 Tuopu
			FindNodeValue(ResNode,"IDS_Tuopu",strMainTitle);
			FindNodeValue(ResNode,"IDS_Tuopu_List",strTitle);
			FindNodeValue(ResNode,"IDS_Tuopu1",strNameUse);
			FindNodeValue(ResNode,"IDS_Delete_Tuop_Affirm",strDel);
			FindNodeValue(ResNode,"IDS_Tuop_List_Null",strNullList);
			FindNodeValue(ResNode,"IDS_Tuopu1",strTuopTip);
		#else
			FindNodeValue(ResNode,"IDS_Maintain",strMainTitle);//Ecc展示视图
			FindNodeValue(ResNode,"IDS_Maintain_List",strTitle);//Ecc展示视图列表
			FindNodeValue(ResNode,"IDS_Maintain1",strNameUse);//展示图
			FindNodeValue(ResNode,"IDS_Delete_Maintain_Affirm",strDel);//确认删除选中展示视图吗？
			FindNodeValue(ResNode,"IDS_Maintain_List_Null",strNullList);//Ecc展示视图列表为空
			FindNodeValue(ResNode,"IDS_Maintian1",strTuopTip);//Ecc展示视图
		#endif

			FindNodeValue(ResNode,"IDS_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Edit",strNameEdit);			
			FindNodeValue(ResNode,"IDS_Edit",strEditTip);			
			FindNodeValue(ResNode,"IDS_Delete",strDeleteType);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",szButMatch);

			FindNodeValue(ResNode,"IDS_Delete_Tuop_Affirm",strDel);
			FindNodeValue(ResNode,"IDS_Edit",strEditTip);
			FindNodeValue(ResNode,"IDS_Delete",strDeleteType);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",szButMatch);
			FindNodeValue(ResNode,"IDS_All_Select",strAllSel);
			FindNodeValue(ResNode,"IDS_None_Select",strAllNotSel);
			FindNodeValue(ResNode,"IDS_Invert_Select",strFanSel);
			FindNodeValue(ResNode,"IDS_Delete",strDelete);
			FindNodeValue(ResNode,"IDS_Sort",szSort);
			FindNodeValue(ResNode,"IDS_TuopDown",szTuopDown);
			FindNodeValue(ResNode,"IDS_SortNum",szSortNum);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);
			FindNodeValue(ResNode,"IDS_Save_Sort",strSaveSort);
			FindNodeValue(ResNode,"IDS_ReturnSave",strReturnSave);

			//IDS_Sort = 排序
			FindNodeValue(ResNode,"IDS_Sort",strSort);
			//IDS_TUOPU_SORT_LIST = 拓扑排序列表
			FindNodeValue(ResNode,"IDS_TUOPU_SORT_LIST",strTuoPuSortList);
			//IDS_Name = 名称
			FindNodeValue(ResNode,"IDS_Name",strName);
			//IDS_SEQUENCE_NO = 序号
			FindNodeValue(ResNode,"IDS_SEQUENCE_NO",strSequenceNo);
			//IDS_Affirm = 确定
			FindNodeValue(ResNode,"IDS_Affirm",strAffirm);

		}
		CloseResource(objRes);
	}
	bFirst =true;
	ShowMainTable();
}

CTuopList::~CTuopList(void)
{

}

void CTuopList::ShowHelp()
{
	m_pTopologyListTable->ShowOrHideHelp();
}

void CTuopList::ShowMainTable()
{
	//strNullList = "空的列表";

	m_pMainTable = new WSVMainTable(this,strMainTitle,false);
	//if(m_pMainTable->pHelpImg)
	//{
	//	connect(m_pMainTable->pHelpImg,SIGNAL(click()),this,SLOT(ShowHelp()));
	//}

	//拓扑列表界面
	m_pTopologyListTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(0,0),List, strTitle);

	if (m_pTopologyListTable->GetContentTable() != NULL)
	{
		m_pTopologyListTable->AppendColumn("",WLength(40,WLength::Pixel));
		m_pTopologyListTable->SetDataRowStyle("table_data_grid_item_text");

		m_pTopologyListTable->AppendColumn(strLoginLabel,WLength(70,WLength::Percentage));
		m_pTopologyListTable->SetDataRowStyle("table_data_grid_item_text");

		m_pTopologyListTable->AppendColumn(strNameUse,WLength(10,WLength::Percentage));
		m_pTopologyListTable->SetDataRowStyle("table_data_grid_item_text");

		m_pTopologyListTable->AppendColumn(strNameEdit,WLength(10,WLength::Percentage));
		m_pTopologyListTable->SetDataRowStyle("table_data_grid_item_text");
	}

	if (m_pTopologyListTable->GetActionTable() != NULL)
	{
		m_pTopologyListTable->AddStandardSelLink(strAllSel ,strAllNotSel,strFanSel);
		connect(m_pTopologyListTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		connect(m_pTopologyListTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		connect(m_pTopologyListTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));
	
		WTable *pTbl;
		m_pTopologyListTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pTopologyListTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		
		pTbl = new WTable(m_pTopologyListTable->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");
		WSVButton * pDel = new WSVButton(pTbl->elementAt(0,1),strDelete, "button_bg_del.png", "", false);
		if (pDel)
		{
			connect(pDel, SIGNAL(clicked()), this, SLOT(BeforeDelUser()));
		} 

		//新增
		//WSVButton * pSort = new WSVButton(pTbl->elementAt(0,2), "排序", "button_bg_taxis.png", "", false);
		WSVButton * pSort = new WSVButton(pTbl->elementAt(0,2), strSort, "button_bg_taxis.png", "", false);
		if (pSort)
		{
			connect(pSort, SIGNAL(clicked()), this, SLOT(Sort()));
		}

		//WTable *pTbl2;
		m_pTopologyListTable->GetActionTable()->elementAt(0, 2)->setContentAlignment(AlignRight);		
		strcpy(m_pTopologyListTable->GetActionTable()->elementAt(0, 2)->contextmenu_, "nowrap");			

		//Tuopu 发布插件下载
		string strTuopPluginJs = "window.open('../TuopoClient.exe','newwindow')";
		
		string szLink = "<a href='#'>" + szTuopDown + "</a>&nbsp;&nbsp;";
		WText * pTuopPlugin = new WText(szLink, (WContainerWidget *)m_pTopologyListTable->GetActionTable()->elementAt(0, 2));
		connect(pTuopPlugin, SIGNAL(clicked()),strTuopPluginJs.c_str() ,WObject::JAVASCRIPT);
	}

	m_pTopologyListTable->SetNullTipInfo(strNullList);


	//拓扑排序列表界面
	//pSortTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0), List, "拓扑排序列表");
	pSortTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0), List, strTuoPuSortList);
	if (pSortTable->GetContentTable() != NULL)
	{
		pSortTable->AppendColumn("",WLength(40,WLength::Pixel));
		pSortTable->SetDataRowStyle("table_data_grid_item_text");

		//pSortTable->AppendColumn("名称",WLength(50,WLength::Percentage));
		pSortTable->AppendColumn(strName,WLength(50,WLength::Percentage));
		pSortTable->SetDataRowStyle("table_data_grid_item_text");

		//pSortTable->AppendColumn("序号",WLength(50,WLength::Percentage));
		pSortTable->AppendColumn(strSequenceNo,WLength(50,WLength::Percentage));
		pSortTable->SetDataRowStyle("table_data_grid_item_text");
	}

	if (pSortTable->GetActionTable() != NULL)
	{
		WTable *pTbl1;
		pSortTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		pSortTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		
		pTbl1 = new WTable(pSortTable->GetActionTable()->elementAt(0,1));
		pTbl1->setStyleClass("widthauto");
		//WSVButton * pSortOkBtn = new WSVButton(pTbl1->elementAt(0, 1), "确 定", "button_bg_m.png", "", false);
		WSVButton * pSortOkBtn = new WSVButton(pTbl1->elementAt(0, 1), strAffirm, "button_bg_m.png", "", false);

		if(pSortOkBtn)
		{
			connect(pSortOkBtn,SIGNAL(clicked()),this,SLOT(SortOk()));
		}
	}
	
	//编辑事件
	std::string strIndex;

	std::list<string> m_pList;
	std::list<string>::iterator m_pItem;

	#ifdef	 Tuopu
		m_pList = ReadFileName(GetSiteViewRootPath() + "\\htdocs\\tuoplist");		
	#else
		m_pList = ReadFileName(GetSiteViewRootPath() + "\\htdocs\\maintainlist");
	#endif

	std::list<string> m_pVList;
	std::list<string>::iterator m_pVItem;

	#ifdef	 Tuopu
		m_pVList = ReadVSDName(GetSiteViewRootPath() + "\\htdocs\\tuoplist");
	#else
		m_pVList = ReadVSDName(GetSiteViewRootPath() + "\\htdocs\\maintainlist");
	#endif

	m_pVItem = m_pVList.begin();	
	for(m_pItem = m_pList.begin(); m_pItem != m_pList.end(); m_pItem++)
	{
		std::string strUserName = *m_pItem;
		std::string strVSD = *m_pVItem; 
		OneRecord list;
		list.strUserName = strUserName;
		//vsd文件始终不会更改， 所以用它来制造key
		list.strBackName = ReplaceStdString(strVSD, ".vsd", ".htm");
		list.strTuop = strVSD;

		//读取tuopfile.ini的sort信息并赋值给OneRecord变量。：
		//如果没有预先设置的sort信息则按什么规则自动赋值？ ---》先是读预先设置的序号， 为默认值 则不存在 意味着是新发布的 
		//---》规则（读一遍ini， 找到序号最大值， 加1 并写到tuopfile.ini文件中）
		int nSort = GetIniFileInt("sort", strVSD, -1, "tuopfile.ini");
		if(nSort != -1)
		{
			list.nSort = nSort;
		}
		else
		{
			//获取序号最大值， 加1
			list.nSort = GetMaxSortId() + 1;

			//写序号值到ini
		#ifdef	 Tuopu
			WriteIniFileInt("sort", strVSD, list.nSort, "tuopfile.ini");
		#else
			WriteIniFileInt("sort", strVSD, list.nSort, "maintainfile.ini");
		#endif
		}

		RecordList.push_back(list);

		m_pVItem++;
	}	
	
	
	//绑定编辑事件
	connect(&m_userMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditUserName(const std::string)));

	//显示列表
	int i = 1;
	std::string strOpen;

	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		m_pTopologyListTable->InitRow(i);
		pSortTable->InitRow(i);
		i++;
	}

	i = 1;
	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		//列表数据界面初始化
		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 0)->setContentAlignment(AlignCenter);
		m_pRecordList->pCheckBox = new WCheckBox("", (WContainerWidget*)m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 0));		

		strOpen = "<a href=./showtuopu.exe?pageid=";
		strOpen += ReplaceStdString(m_pRecordList->strBackName, ".htm", "");
	#ifdef	 Tuopu
		strOpen += "&version=0";
	#else
		strOpen += "&version=0&usrleader=0&maintain=1";
	#endif
		strOpen += " target=_blank>";
		strOpen += m_pRecordList->strUserName;
		strOpen += "</a>";

		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2)->setContentAlignment(AlignCenter);
		m_pRecordList->pstrUserName = new WText(strOpen, (WContainerWidget*)m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2));
		

		m_pRecordList->pLineEdit = new WLineEdit(m_pRecordList->strUserName,m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2));
		m_pRecordList->pLineEdit->hide();


		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4)->setContentAlignment(AlignCenter);		
		m_pRecordList->pTuop = new WImage("../Images/resource.gif",m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4));
		m_pRecordList->pTuop->setToolTip(strTuopTip);
		m_pRecordList->pTuop->setStyleClass("hand");

		//绑定visio事件
		std::string strJavascript;

	#ifdef	 Tuopu
		strJavascript = "window.open('../tuoplist/" + m_pRecordList->strTuop + "','newwindow')";	
	#else
		strJavascript = "window.open('../maintainlist/" + m_pRecordList->strTuop + "','newwindow')";	
	#endif

		connect(m_pRecordList->pTuop, SIGNAL(clicked()),strJavascript.c_str() ,WObject::JAVASCRIPT );

		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 6)->setContentAlignment(AlignCenter);
		m_pRecordList->pEdit = new WImage("/Images/edit.gif",m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 6));		
		m_pRecordList->pEdit->setToolTip(strEditTip);
		m_pRecordList->pEdit->setStyleClass("hand");
		
		strIndex=m_pRecordList->strUserName.c_str();

		m_userMapper.setMapping(m_pRecordList->pEdit, strIndex); 
		
		connect(m_pRecordList->pEdit, SIGNAL(clicked()), &m_userMapper, SLOT(map()));
		connect(m_pRecordList->pLineEdit, SIGNAL(keyWentDown(int)), this, SLOT(EditReturn(int)));
		i++;

		//排序数据界面初始化
		pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2)->setContentAlignment(AlignCenter);
		WText * pTmpText = new WText(m_pRecordList->strUserName, pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2));

		char chItem[32]  = {0};	
		sprintf(chItem, "%d", m_pRecordList->nSort);
		string strSort = chItem;

		pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4)->setContentAlignment(AlignCenter);
		WLineEdit * pTmpEdit = new WLineEdit(strSort, pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4));

		//放到sv_table里去
		SVTableCell ce;
		ce.setType(adText);
		ce.setValue(pTmpText);
		m_svSortList.WriteCell(m_pRecordList->strTuop, 0, ce);

		ce.setType(adLineEdit);
		ce.setValue(pTmpEdit);
		m_svSortList.WriteCell(m_pRecordList->strTuop, 1, ce);
	}
	
	m_pList.clear();
	m_pVList.clear();
	
	//列表为空
	if(RecordList.size() <= 0)
	{
		m_pTopologyListTable->ShowNullTip();
	}
	else
	{
		m_pTopologyListTable->HideNullTip();
	}

	pSortTable->hide();


	//隐藏按钮
	pHideBtn = new WPushButton("hide button",this);
	if(pHideBtn)
	{
		pHideBtn->setToolTip("Hide Button");
		connect(pHideBtn,SIGNAL(clicked()),this,SLOT(DelUser()));
		pHideBtn->hide();
	}

	pTranslateBtn = new WPushButton("Translate",this);
	pExChangeBtn = new WPushButton("Refresh",this);

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
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
}

void CTuopList::ExChange()
{	
#ifdef	 Tuopu
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/tuoplist.exe?'\",1250);  ";
#else
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/maintainlist.exe?'\",1250);  ";
#endif
	appSelf->quit();
}
void CTuopList::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "tuoplistRes";
	WebSession::js_af_up += "')";
}

//删除用户按钮响应
void CTuopList::BeforeDelUser()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "BeforeDelUser";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//m_pTopologyListTable->HideNullTip();
	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		if(m_pRecordList->pCheckBox->isChecked() == true )
		{
			if(pHideBtn)
			{
				string strDelDes = pHideBtn->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + strDel + "','" + szButNum + "','" + szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//删除操作
void CTuopList::DelUser()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "DelUser";
	LogItem.sDesc = strDeleteType;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strDeleteTuop;

	for(m_pRecordList = RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList++)
    {       
        if (m_pRecordList->pCheckBox->isChecked())
        {			
			std::string sVal = m_pRecordList->strBackName;
			std::string sVsd = ReplaceStdString(sVal, ".htm", ".vsd");
			std::string sDiretory = ReplaceStdString(sVal, ".htm", ".files");

		#ifdef	 Tuopu
			DeleteIniFileKey("filename", sVal, "tuopfile.ini");
			DeleteIniFileKey("filename", sVsd, "tuopfile.ini");
		#else
			std::string sName = ReplaceStdString(m_pRecordList->strBackName, ".htm", "");
			DeleteIniFileKey("filename", sVal, "maintainfile.ini");
			DeleteIniFileKey("filename", sVsd, "maintainfile.ini");
			DeleteIniFileSection(sName, "maintain.ini");
		#endif			

			//std::string filepath = "C:\\Program Files\\Apache Group\\apache2\\htdocs\\tuoplist\\";			
			//删除了拓扑图  序号怎么变？---》是直接删除呢？ 还是要加把其他的序号都整理一遍？---》或者把大于它的序号都减1即可。
			DelSortId(sVsd);

			string strDelDir;
		#ifdef	 Tuopu
			std::string filepath = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\";
			
			filepath += sVal;
			
			bool bret = DeleteFile(filepath.c_str());
			if(!bret)
			{
				//
			}
		#else
			std::string filepath = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\";
			std::string fileleaderpath = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\";
			strDelDir = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\";

			filepath += sVal;			
			
			bool bret = DeleteFile(filepath.c_str());
			if(!bret)
			{
				//
			}

			fileleaderpath += sVal;
			
			bret = DeleteFile(fileleaderpath.c_str());
			if(!bret)
			{
				//
			}

			strDelDir += sDiretory;

			//DeleteDirectory(strDelDir);
		#endif			
			


		#ifdef	 Tuopu
			filepath = GetSiteViewRootPath() + "\\htdocs\\tuoplist\\";

			filepath += sVsd;
			
			bret = DeleteFile(filepath.c_str());
			if(!bret)
			{
				//
			}

		#else
			filepath = GetSiteViewRootPath() + "\\htdocs\\maintainlist\\";
			fileleaderpath = GetSiteViewRootPath() + "\\htdocs\\maintainleaderlist\\";

			filepath += sVsd;
			
			bret = DeleteFile(filepath.c_str());
			if(!bret)
			{
				//
			}

			fileleaderpath += sVsd;
			
			bret = DeleteFile(fileleaderpath.c_str());
			if(!bret)
			{
				//
			}

		#endif			


			//files目录是否也删除

            int nRow = ((WTableCell*)(m_pRecordList->pCheckBox->parent()))->row();
        
            list<OneRecord>::iterator pItem = m_pRecordList;
        
            m_pRecordList --;
        
			std::string temp = pItem->pstrUserName->text();		
			int pos = temp.find(">", 0);
			int pos1 = temp.find("<", pos);
			string strTemp = temp.substr(pos + 1, pos1 - pos - 1);			
 			strDeleteTuop += strTemp;
			strDeleteTuop += "  ";

			RecordList.erase(pItem);          
        
            m_pTopologyListTable->GeDataTable()->deleteRow(nRow); 						
        }
    }

	//列表为空
	if(RecordList.size() <= 0)
	{
		m_pTopologyListTable->ShowNullTip();
	}
	else
	{
		m_pTopologyListTable->HideNullTip();
	}

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strDeleteType,strMainTitle,strDeleteTuop);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//反选按钮响应
void CTuopList::SelInvert()
{
 	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		if(m_pRecordList->pCheckBox->isChecked())
			m_pRecordList->pCheckBox->setChecked(false);
		else
			m_pRecordList->pCheckBox->setChecked(true);
	}
}

//全部不选择按钮响应
void CTuopList::SelNone()
{
 	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		m_pRecordList->pCheckBox->setChecked(false);
	}
}

//选择全部按钮响应
void CTuopList::SelAll()
{
	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		m_pRecordList->pCheckBox->setChecked(true);
	}
}

//编辑拓扑图的处理函数(没用)
void CTuopList::OpenTuop(const std::string strTuop)
{
/*	WebSession::js_af_up = "window.open('../tuoplist/";
	WebSession::js_af_up += strTuop;
	WebSession::js_af_up += "','newwindow')";
*/
//	WebSession::js_af_up = "window.open('http://127.0.0.1:81/tuoplist/aaaa.vsd','newwindow')";
}

//编辑事件的处理函数
void CTuopList::EditUserName(const std::string strIndex)
{	
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "EditUserName";
	LogItem.sDesc = strNameEdit;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//查找名称相同的用户
	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		if(strIndex == m_pRecordList->strUserName)	
		{
			bStrCurr = m_pRecordList->strUserName;
			m_pRecordList->pstrUserName->hide();
			
			m_pRecordList->pLineEdit->show();
			
			pCurrName = m_pRecordList->pstrUserName;
			
			pCurrEditUserName = m_pRecordList->pLineEdit;			
			m_pRecordList->pLineEdit->enable();
		}
		else
		{
			m_pRecordList->pstrUserName->show();
//			m_pRecordList->pLineEdit->setText(m_pRecordList->pstrUserName->text());
			m_pRecordList->pLineEdit->hide();
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//加列标题
void CTuopList::AddColum(WTable* pContain)
{
	new WText(" ", pContain->elementAt(0,0));
	new WText(strLoginLabel, pContain->elementAt(0,1));
	
	new WText(strNameUse, pContain->elementAt(0,2));
	new WText(strNameEdit, pContain->elementAt(0,3));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}

//
void CTuopList::EditReturn(int keyCode)
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "EditReturn";
	LogItem.sDesc = strReturnSave;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

//	OutputDebugString("EditReturn\n");
	if(keyCode == 13)
	{	
		char buf[1024];
		memset(buf, 0, 1023);
		string str = pCurrEditUserName->text();
		sprintf(buf, "%s", str.c_str());
		
//		OutputDebugString(buf);
		std::list<string> keylist;
		std::list<string>::iterator itemkey;
	#ifdef	 Tuopu
		bool bret = GetIniFileKeys("filename", keylist, "tuopfile.ini");
	#else
		bool bret = GetIniFileKeys("filename", keylist, "maintainfile.ini");
	#endif

		if(!bret)
		{
			//
		}
		
		bool bExist1 = true;
		std::string sVal = "";
		std::string defaultret = "error";
		std::string sret = "";
		
		//此名字是否已经存在？
		for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
		{
			sVal = *itemkey;
		#ifdef	 Tuopu
			sret = GetIniFileString("filename", sVal, defaultret, "tuopfile.ini");
		#else
			sret = GetIniFileString("filename", sVal, defaultret, "maintainfile.ini");
		#endif				
			
			if(strcmp(sret.c_str(), bStrCurr.c_str()) == 0)
			{
				continue;
			}

			if(strcmp(sret.c_str(), str.c_str()) == 0)
			{
				bExist1 = false;
			}
		}
//		OutputDebugString("befor bExtit1\n");
		
		if(bExist1)
		{
			for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
			{
				sVal = *itemkey;

			#ifdef	 Tuopu
				sret = GetIniFileString("filename", sVal, defaultret, "tuopfile.ini");
			#else
				sret = GetIniFileString("filename", sVal, defaultret, "maintainfile.ini");
			#endif
				
				if(strcmp(sret.c_str(), bStrCurr.c_str()) == 0)
				{
//					OutputDebugString("befor write1\n");
				#ifdef	 Tuopu
					WriteIniFileString("filename", sVal, str, "tuopfile.ini");
				#else
					WriteIniFileString("filename", sVal, str, "maintainfile.ini");
				#endif

					break;
				}				
			}

			string strOpen;

			strOpen = "<a href=./showtuopu.exe?pageid=";
			strOpen += ReplaceStdString(sVal, ".htm", "");
		#ifdef	 Tuopu
			strOpen += "&version=0";
		#else
			strOpen += "&version=0&usrleader=0&maintain=1";
		#endif
			strOpen += " target=_blank>";
			strOpen += buf;
			strOpen += "</a>";
			
			pCurrName->setText(strOpen.c_str());
			pCurrName->show();		
			
			pCurrEditUserName->hide();

			//插记录到UserOperateLog表
			string strUserID = GetWebUserID();
			TTime mNowTime = TTime::GetCurrentTimeEx();
			OperateLog m_pOperateLog;
			m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strEditTip,strMainTitle,buf);
		}
		else
		{
			WebSession::js_af_up = "alert('";
			WebSession::js_af_up += "have same name tuop";
			WebSession::js_af_up += "')";
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
void CTuopList::refresh()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	if(bFirst)
	{
		bFirst =false;
		bEnd = true;	
		goto OPEnd;
	}

	m_pTopologyListTable->GeDataTable()->clear();
	RecordList.clear();

	pSortTable->GeDataTable()->clear();
	
	
	std::string strIndex;
	std::list<string> m_pList;
	std::list<string>::iterator m_pItem;

	#ifdef	 Tuopu
		m_pList = ReadFileName(GetSiteViewRootPath() + "\\htdocs\\tuoplist");		
	#else
		m_pList = ReadFileName(GetSiteViewRootPath() + "\\htdocs\\maintainlist");
	#endif

	std::list<string> m_pVList;
	std::list<string>::iterator m_pVItem;

	#ifdef	 Tuopu
		m_pVList = ReadVSDName(GetSiteViewRootPath() + "\\htdocs\\tuoplist");
	#else
		m_pVList = ReadVSDName(GetSiteViewRootPath() + "\\htdocs\\maintainlist");
	#endif
	
	m_pVItem = m_pVList.begin();	
	for(m_pItem = m_pList.begin(); m_pItem != m_pList.end(); m_pItem++)
	{
		std::string strUserName = *m_pItem;
		std::string strVSD = *m_pVItem; 
		OneRecord list;
		list.strUserName = strUserName;
		//vsd文件始终不会更改， 所以用它来制造key
		list.strBackName = ReplaceStdString(strVSD, ".vsd", ".htm");
		list.strTuop = strVSD;

		//读取tuopfile.ini的sort信息并赋值给OneRecord变量。：
		//如果没有预先设置的sort信息则按什么规则自动赋值？ ---》先是读预先设置的序号， 为默认值 则不存在 意味着是新发布的 
		//---》规则（读一遍ini， 找到序号最大值， 加1 并写到tuopfile.ini文件中）
		int nSort = GetIniFileInt("sort", strVSD, -1, "tuopfile.ini");
		if(nSort != -1)
		{
			list.nSort = nSort;
		}
		else
		{
			//获取序号最大值， 加1
			list.nSort = GetMaxSortId() + 1;

			//写序号值到ini
		#ifdef	 Tuopu
			WriteIniFileInt("sort", strVSD, list.nSort, "tuopfile.ini");
		#else
			WriteIniFileInt("sort", strVSD, list.nSort, "maintainfile.ini");
		#endif
		}

		RecordList.push_back(list);

		m_pVItem++;
	}


	//显示列表
	int i = 1;
	std::string strOpen;

	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		m_pTopologyListTable->InitRow(i);
		pSortTable->InitRow(i);
		i++;
	}

	i = 1;
	for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	{
		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 0)->setContentAlignment(AlignCenter);
		m_pRecordList->pCheckBox = new WCheckBox("", (WContainerWidget*)m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 0));		

		strOpen = "<a href=./showtuopu.exe?pageid=";
		strOpen += ReplaceStdString(m_pRecordList->strBackName, ".htm", "");
	#ifdef	 Tuopu
		strOpen += "&version=0";
	#else
		strOpen += "&version=0&usrleader=0&maintain=1";
	#endif
		strOpen += " target=_blank>";
		strOpen += m_pRecordList->strUserName;
		strOpen += "</a>";

		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2)->setContentAlignment(AlignCenter);
		m_pRecordList->pstrUserName = new WText(strOpen, (WContainerWidget*)m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2));
		
		m_pRecordList->pLineEdit = new WLineEdit(m_pRecordList->strUserName,m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2));
		m_pRecordList->pLineEdit->hide();

		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4)->setContentAlignment(AlignCenter);		
		m_pRecordList->pTuop = new WImage("../Images/resource.gif",m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4));
		m_pRecordList->pTuop->setToolTip(strTuopTip);
		m_pRecordList->pTuop->setStyleClass("hand");

		//绑定visio事件
		std::string strJavascript;

	#ifdef	 Tuopu
		strJavascript = "window.open('../tuoplist/" + m_pRecordList->strTuop + "','newwindow')";	
	#else
		strJavascript = "window.open('../maintainlist/" + m_pRecordList->strTuop + "','newwindow')";	
	#endif

		connect(m_pRecordList->pTuop, SIGNAL(clicked()),strJavascript.c_str() ,WObject::JAVASCRIPT );

		m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 6)->setContentAlignment(AlignCenter);
		m_pRecordList->pEdit = new WImage("/Images/edit.gif",m_pTopologyListTable->GeDataTable()->elementAt(m_pRecordList->nSort, 6));		
		m_pRecordList->pEdit->setToolTip(strEditTip);
		m_pRecordList->pEdit->setStyleClass("hand");
		
		strIndex=m_pRecordList->strUserName.c_str();

		m_userMapper.setMapping(m_pRecordList->pEdit, strIndex); 
		
		connect(m_pRecordList->pEdit, SIGNAL(clicked()), &m_userMapper, SLOT(map()));
		connect(m_pRecordList->pLineEdit, SIGNAL(keyWentDown(int)), this, SLOT(EditReturn(int)));
		i++;

		//排序界面初始化
		pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2)->setContentAlignment(AlignCenter);
		WText * pTmpText = new WText(m_pRecordList->strUserName, pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 2));
		
		char chItem[32]  = {0};	
		sprintf(chItem, "%d", m_pRecordList->nSort);
		string strSort = chItem;

		pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4)->setContentAlignment(AlignCenter);
		WLineEdit * pTmpEdit = new WLineEdit(strSort, pSortTable->GeDataTable()->elementAt(m_pRecordList->nSort, 4));

		//放到sv_table里去
		SVTableCell ce;
		ce.setType(adText);
		ce.setValue(pTmpText);
		m_svSortList.WriteCell(m_pRecordList->strTuop, 0, ce);

		ce.setType(adLineEdit);
		ce.setValue(pTmpEdit);
		m_svSortList.WriteCell(m_pRecordList->strTuop, 1, ce);
	}
	
	m_pList.clear();
	m_pVList.clear();
	
	//列表为空
	if(RecordList.size() <= 0)
	{
		m_pTopologyListTable->ShowNullTip();
	}
	else
	{
		m_pTopologyListTable->HideNullTip();
	}

	//可能有问题..
	pSortTable->hide();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
std::list<string>  CTuopList::ReadVSDName(string path)
{
	WIN32_FIND_DATA fd;
	std::list<string> strlist;
	path += "\\*.*";
    HANDLE fr=::FindFirstFile(path.c_str(),&fd);
    while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//
		}
        else
		{
			std::string str1 = fd.cFileName;
			int npos = str1.find(".vsd", 0);
			if(npos >= 0)
			{
				std::list<string> keylist;
				std::list<string>::iterator itemkey;
				#ifdef	 Tuopu
					bool bret = GetIniFileKeys("filename", keylist, "tuopfile.ini");
				#else
					bool bret = GetIniFileKeys("filename", keylist, "maintainfile.ini");
				#endif

				if(!bret)
				{
					//
				}

				bool bExist = false;
				for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
				{
					std::string str = *itemkey;
					if(strcmp(str.c_str(), fd.cFileName) == 0)
					{
						bExist = true;
						break;
					}
				}
				
				string strHtmName = ReplaceStdString(str1, ".vsd", ".htm");
				if(GetUserRight(strHtmName))
				{
					if(bExist)
					{
						std::string defaultret = "error";
					#ifdef	 Tuopu
						std::string sret = GetIniFileString("filename", fd.cFileName, defaultret, "tuopfile.ini");
					#else
						std::string sret = GetIniFileString("filename", fd.cFileName, defaultret, "maintainfile.ini");
					#endif
						int npos = sret.find(".vsd", 0);
						if(npos >= 0)
						{
							strlist.push_back(sret);
						}
					}
					else
					{
					#ifdef	 Tuopu
						WriteIniFileString("filename", fd.cFileName, fd.cFileName, "tuopfile.ini");
					#else
						WriteIniFileString("filename", fd.cFileName, fd.cFileName, "maintainfile.ini");
					#endif						
						strlist.push_back(fd.cFileName);
					}	
				}
			}
		}
    }
	return strlist;
}

//
std::list<string>  CTuopList::ReadFileName(string path)
{
	WIN32_FIND_DATA fd;
	std::list<string> strlist;
	path += "\\*.*";
    HANDLE fr=::FindFirstFile(path.c_str(),&fd);
    while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//
		}
        else
		{
			std::string str1 = fd.cFileName;
			int npos = str1.find(".htm", 0);
			if(npos >= 0)
			{
				std::list<string> keylist;
				std::list<string>::iterator itemkey;
				
			#ifdef	 Tuopu
				bool bret = GetIniFileKeys("filename", keylist, "tuopfile.ini");
			#else
				bool bret = GetIniFileKeys("filename", keylist, "maintainfile.ini");
			#endif

				if(!bret)
				{
					//
				}

				bool bExist = false;
				for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
				{
					std::string str = *itemkey;
					if(strcmp(str.c_str(), fd.cFileName) == 0)
					{
						bExist = true;
						break;
					}
				}

				//用户权限			
				if(GetUserRight(fd.cFileName))
				{
					if(bExist)
					{
						std::string defaultret = "error";

					#ifdef	 Tuopu
						std::string sret = GetIniFileString("filename", fd.cFileName, defaultret, "tuopfile.ini");
					#else
						std::string sret = GetIniFileString("filename", fd.cFileName, defaultret, "maintainfile.ini");
					#endif
						
						//int npos = sret.find(".htm", 0);
						//if(npos >= 0)
						if(sret != defaultret)
						{
							strlist.push_back(sret);
						}
					}
					else
					{

					#ifdef	 Tuopu
						WriteIniFileString("filename", fd.cFileName, fd.cFileName, "tuopfile.ini");
					#else
						WriteIniFileString("filename", fd.cFileName, fd.cFileName, "maintainfile.ini");
					#endif
						
						strlist.push_back(fd.cFileName);
					}
				}
			}
		}
    }

	return strlist;
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//添加客户端脚本变量
void AddJsParam(const std::string name, const std::string value,  WContainerWidget * parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}


void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("拓扑视图");

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", app.root());
	new WText("<div id='view_panel' class='panel_view'>", app.root());

    CTuopList setform(app.root());
	setform.appSelf = &app;
	app.setBodyAttribute("class ='workbody'");

	new WText("</div>", app.root());

	AddJsParam("uistyle", "viewpan", app.root());
	AddJsParam("fullstyle", "true", app.root());
	AddJsParam("bGeneral", "false", app.root());
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", app.root());

    app.exec();
}

//新增的Sort函数

//添加排序数据项(没有用了)
void CTuopList::AddSortData(string strVsdName, int nRows, string strName, string strSort)
{
	WText * pTmpText = new WText(strName, (WContainerWidget*)pSortListTable->elementAt(nRows, 0));	
	WLineEdit * pTmpEdit = new WLineEdit(strSort, (WContainerWidget*)pSortListTable->elementAt(nRows, 1));

	//放到sv_table里去
	SVTableCell ce;
	ce.setType(adText);
	ce.setValue(pTmpText);
	m_svSortList.WriteCell(strVsdName, 0, ce);

	ce.setType(adLineEdit);
	ce.setValue(pTmpEdit);
	m_svSortList.WriteCell(strVsdName, 1, ce);
}

//添加排序Table(没有用了)
void CTuopList::AddSortColum(WTable * pContain)
{	
	new WText(strLoginLabel, pContain->elementAt(0,0));
	new WText(szSortNum, pContain->elementAt(0,1));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}

//显示排序界面
void CTuopList::Sort()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "Sort";
	LogItem.sDesc = szSort;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//m_svSortList.clear();
	////pSortListTable->clear();
	////pSortTable->GetContentTable()->elementAt(0,0)->clear();
	//pSortTable->GeDataTable()->clear();
	////排序界面怎么新构造？ 名称 序号 （隐藏、显示、编辑、保存）？ 初始化时怎么排列呢？---》以序号排吗？

	////根据RecordList添加排序界面数据
	////pSortListTable = new WTable(pSortTable->GetContentTable()->elementAt(0,0));
	////pSortListTable->setStyleClass("t3");
	////AddSortColum(pSortListTable);

	////
	//int i = 1;
	//for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	//{
	//	pSortTable->InitRow(i);
	//	i++;
	//}

	////
	//for(m_pRecordList=RecordList.begin(); m_pRecordList != RecordList.end(); m_pRecordList ++)
	//{
	//	//m_pRecordList->strTuop
	//	//m_pRecordList->strUserName
	//	//m_pRecordList->nSort
	//	char chItem[32]  = {0};	
	//	sprintf(chItem, "%d", m_pRecordList->nSort);
	//	string strSort = chItem;

	//	AddSortData(m_pRecordList->strTuop, m_pRecordList->nSort, m_pRecordList->strUserName, strSort);
	//}

	//////界面隐现	//新增
	////
	//////排序
	////pSort = new WImage("../Images/sort.gif",(WContainerWidget *)pUserTable->m_pGroupOperate->elementAt(0, 5));
	////if (pSort)
 ////   {
 ////       pSort->setStyleClass("imgbutton");
	////	pSort->setToolTip(szSort);
 ////   }

	m_pTopologyListTable->hide();
	pSortTable->show();	

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//界面排序完毕
void CTuopList::SortOk()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "TuopList";
	LogItem.sHitFunc = "SortOk";
	LogItem.sDesc = strSaveSort;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//数据有效性判断  如果编辑过程中 输入无效的序号 怎么处理？---》小于等于零  有重复数字 不连续 等？---》不容易完全判定清楚， 暂时不判定。
	
	//是数字吗？
	//if(!pAlertStop->text().empty())
	//{
	//	nRet = sscanf(pAlertStop->text().c_str(), "%d", &nTmp);
	//	if(nRet == EOF || nRet == 0 || nTmp < 0)
	//	{
	//		errorMsgList.push_back(strAlertStopError);
	//		bError = true;
	//	}
	//	else
	//	{				
	//		sprintf(chItem, "%d", nTmp);
	//		pAlertStop->setText(chItem);
	//	}
	//}

	//写拓扑图的顺序数据到ini
    for(row it = m_svSortList.begin(); it != m_svSortList.end(); it++)
    {
        SVTableCell * pcell = it->second.Cell(1);
        if(pcell)
        {
            // 修改每一项的选择状态
			if (pcell->Type() == adLineEdit)
            {
				//
				int nSort = 0;
				string strSortId = ((WLineEdit*)pcell->Value())->text();
				sscanf(strSortId.c_str(), "%d", &nSort);
				//OutputDebugString(pcell->Row());
				//OutputDebugString(strSortId.c_str());

				//
			#ifdef	 Tuopu
				WriteIniFileInt("sort", pcell->Row(), nSort, "tuopfile.ini");
			#else
				WriteIniFileInt("sort", pcell->Row(), nSort, "maintainfile.ini");
			#endif
            }
        }
    }

	
	//更新拓扑列表的数据
	//RecordList需要重新构造---》刷新函数能解决此问题吗？---》应该能解决
	refresh();

	//界面隐现
	pSortTable->hide();
	m_pTopologyListTable->show();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

int main(int argc, char *argv[])
{

    func p = usermain;
    //WriteRightTpl();
	if (argc == 1) 
    {
        char buf[256];

		WebSession s(buf, false);
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


