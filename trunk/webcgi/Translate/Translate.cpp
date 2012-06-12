#include ".\translate.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"
#include "..\svtable\AnswerTable.h"
#include "..\svtable\SVTable.h"
#include "svapi.h"
#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include <WScrollArea>
#include <atlstr.h>
#include <fstream>

//字符串替换函数
void stringReplace(string & strBig, const string & strsrc, const string & strdst) {
	string::size_type pos=0;
	string::size_type srclen=strsrc.size();
	string::size_type dstlen=strdst.size();
	while( (pos=strBig.find(strsrc, pos)) != string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}

CTranslate::CTranslate(WContainerWidget *parent ):WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Name_IDS",strIDSList);
			FindNodeValue(ResNode,"IDS_Edit_Character_Tip",strEditTip);
			FindNodeValue(ResNode,"IDS_Edit_Character",strEditName);
			FindNodeValue(ResNode,"IDS_Translate_Title",strTitle);
		}
		CloseResource(objRes);
	}

/*	strIDSList = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;IDS 名称";
	strEditTip = "编辑当前语言版本的文字";
	strEditName = "编辑文字";
*/
	pEditCell = NULL;
	pTempTable = NULL;
	iRefresh = 0;
	bState = true;

	ShowMainTable();
}

void CTranslate::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);		
	pMainTable = new CAnswerTable(this,strTitle);

	//隐藏帮助按钮
	pMainTable->m_pHelpimg->hide();

	//隐藏保存和取消按钮
	pMainTable->pSave->hide();
	pMainTable->pCancel->hide();

	pUserListTable = new WTable(pMainTable->GetContentTable()->elementAt(2,0));
	pUserListTable ->setStyleClass("t3");

	//添加列
	AddColum(pUserListTable);

	char buf_tmp[4096]={0};
    int nSize =4095;
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
	//char * tmpquery;
	//tmpquery = getenv( "QUERY_STRING");
	//if(tmpquery)
	//	strcpy(buf_tmp,tmpquery);

	if(buf_tmp != NULL)
	{
		std::string buf1 = buf_tmp;
		size_t pos;
		pos = buf1.find("filepath=", 0);
		if(pos != string::npos)
		{
			pos = buf1.find("filepath=DeviceMonitorTemplate$", 0);
			if(pos != string::npos)
			{
				pos = buf1.find("deviceid=", 0);
				if(pos != string::npos)
				{
					strFileName = buf1.substr(pos+9,  buf1.size() - pos - 1);
					AddDeviceList(pUserListTable,strFileName);
				}
				pos = buf1.find("monitorid=", 0);
				if(pos != string::npos)
				{
					strFileName = buf1.substr(pos+10,  buf1.size() - pos - 1);
					AddMonitorList(pUserListTable,strFileName);
				}	
			}
			else
			{
				strFileName = buf1.substr(pos+9,  buf1.size() - pos - 1);
				//添加内容
				AddValue(pUserListTable,strFileName);
			}
		}
	}	

	int nRow;
	nRow = pMainTable->GetContentTable()->numRows();
	pMainTable->GetContentTable()->elementAt(nRow,0)->setStyleClass("t5");

}
////////////////////////////////
void CTranslate::AddDeviceList( WTable* pContain,const string deviceid )
{
	list<string> FileDataList;
	list<string>::iterator FileDataListRecord;
	string newDeviceID = deviceid;
	stringReplace(newDeviceID,"%20"," ");
	string deviceIDS;
	OBJECT DeviceTPL = GetEntityTemplet(newDeviceID);
	if(DeviceTPL == INVALID_VALUE)
	{
		return;
	}
	//设备组
	PAIRLIST entityGroupList;
	PAIRLIST::iterator entityGroupItem;
	if(GetAllEntityGroups(entityGroupList))
	{
		OBJECT entityGroupObj;
		for(entityGroupItem=entityGroupList.begin();entityGroupItem!=entityGroupList.end();entityGroupItem++)
		{
			entityGroupObj = GetEntityGroup(entityGroupItem->name);				
			if(entityGroupObj!=INVALID_VALUE)
			{
				list<string> subEntityList;
				list<string>::iterator subEntityItem;
				if(GetSubEntityTempletIDByEG(subEntityList, entityGroupObj))
				{
					MAPNODE groupNode;
					for(subEntityItem=subEntityList.begin();subEntityItem!=subEntityList.end();subEntityItem++)
					{
						if(newDeviceID == (*subEntityItem))
						{
							groupNode = GetEntityGroupMainAttribNode(entityGroupObj);
							if(groupNode != INVALID_VALUE)
							{
								FindNodeValue(groupNode, "sv_label",deviceIDS);
								FileDataList.push_back(deviceIDS);								
								FindNodeValue(groupNode, "sv_description",deviceIDS);
								FileDataList.push_back(deviceIDS);								
							}
						}
					}
				}
			}
		}
	}

	MAPNODE deviceNode = GetEntityTempletMainAttribNode(DeviceTPL);
	if( deviceNode != INVALID_VALUE )
	{
		//主属性
		FindNodeValue(deviceNode, "sv_label",deviceIDS);
		FileDataList.push_back(deviceIDS);
		FindNodeValue(deviceNode, "sv_description",deviceIDS);
		FileDataList.push_back(deviceIDS);
	}
	//Item
	LISTITEM ParamListItem; 
	PAIRLIST ParamList;
	if(FindETContrlFirst(DeviceTPL, ParamListItem) )
	{
		string itemcount;
		while((deviceNode=::FindNext(ParamListItem))!=INVALID_VALUE )
		{ 
			ParamList.clear();
			if(::EnumNodeAttrib(deviceNode,ParamList))
			{
				FindNodeValue(deviceNode, "sv_label",deviceIDS);
				FileDataList.push_back(deviceIDS);
				FindNodeValue(deviceNode, "sv_helptext",deviceIDS);
				FileDataList.push_back(deviceIDS);
				FindNodeValue(deviceNode, "sv_tip",deviceIDS);
				FileDataList.push_back(deviceIDS);
                if(FindNodeValue(deviceNode, "sv_itemcount",itemcount))
				{
					int iCount = atoi(itemcount.c_str());
					string ParamKey,KeyIndex;
					char buf[256] = {};
					for(int m=1;m<=iCount;m++)
					{
						itoa(m,buf,10);
						KeyIndex = buf;
						ParamKey = "sv_itemlabel" + KeyIndex;
						FindNodeValue(deviceNode, ParamKey,deviceIDS);
						FileDataList.push_back(deviceIDS);
					}
				}				
			}
		}
	}

	
	PAIRLIST LanguList;
    PAIRLIST::iterator LanguListItem;
	bool bGetLangu = GetAllResourceInfo(LanguList);
	bool bShowIds = true;
	int j = 1;
	SVTableCell ce;
	for(LanguListItem = LanguList.begin(); LanguListItem != LanguList.end();LanguListItem++)
	{
		string strLangu = LanguListItem->name;
		//Resource
		OBJECT objRes=LoadResource(strLangu, "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				int i=1;
				for(FileDataListRecord = FileDataList.begin();FileDataListRecord != FileDataList.end();FileDataListRecord++)
				{
					string mValue = *FileDataListRecord;
	
					char buf[256] = {0};
					itoa(i,buf,10);
					string strIndex = buf;
					if(bShowIds)
					{
						//IDS标识列
						new WText("&nbsp;&nbsp;&nbsp;", pContain->elementAt(i,0));		
						WText * m_pEdit = new WText(mValue, pContain->elementAt(i,0));

						ce.setType(adText);
						ce.setValue(m_pEdit);
						m_pList.WriteCell(strIndex,0,ce);

						//行号列
						WText * m_pRowNum = new WText(strIndex, pContain->elementAt(i,iLanguCount + 1));
						m_pRowNum->hide();

						ce.setType(adText);
						ce.setValue(m_pRowNum);
						m_pList.WriteCell(strIndex,iLanguCount + 1,ce);

						//编辑图片列
						WImage * m_pImage = new WImage("../icons/edit.gif", pContain->elementAt(i,iLanguCount + 2));
						m_pImage->setToolTip(strEditTip);
						m_pImage->setStyleClass("helpimg");
					
						connect(&m_userMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditIDSValue(const std::string)));
						m_userMapper.setMapping(m_pImage, mValue); 
						connect(m_pImage, SIGNAL(clicked()), &m_userMapper, SLOT(map()));

						ce.setType(adImage);
						ce.setValue(m_pImage);
						m_pList.WriteCell(strIndex,iLanguCount + 2,ce);	
					}	

					//各种语言列
					string strValue;
					FindNodeValue(ResNode,mValue,strValue);
					WText * m_pTValue = new WText(strValue, pContain->elementAt(i,j));

					ce.setType(adText);
					ce.setValue(m_pTValue);
					m_pList.WriteCell(strIndex,j,ce);		
					
					i++;
				}
			}
		}
		CloseResource(objRes);
		bShowIds = false;
		j++;
	}
	
	//添加一个LineEdit,防止回车转移到其他地址。
	int RowCount = pContain->numRows();
	WLineEdit * m_pTemp = new WLineEdit("",pContain->elementAt(RowCount,0));
	m_pTemp->hide();

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);

	for(int i=1;i<pContain->numRows();i++)
	{
		if(i%2==1)
		{
			pContain->GetRow(i)->setStyleClass("tr1");
		}
		else
		{
			pContain->GetRow(i)->setStyleClass("tr2");
		}
	}
}
//////////////////////////////
void CTranslate::AddMonitorList( WTable* pContain,const string monitorid )
{
	list<string> FileDataList;
	list<string>::iterator FileDataListRecord;
	int MonitorID = atoi(monitorid.c_str());
	OBJECT MonitorObj = GetMonitorTemplet(MonitorID);
	if(MonitorObj==INVALID_VALUE)
	{	
		return;
	}
	MAPNODE MonitorNode;
	string MonitorIDS;
	//主属性
	MonitorNode = GetMTMainAttribNode(MonitorObj);
	if(MonitorNode!=INVALID_VALUE)
	{
		FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
		FileDataList.push_back(MonitorIDS);
		FindNodeValue(MonitorNode, "sv_description",MonitorIDS);
		FileDataList.push_back(MonitorIDS);
	}
	PAIRLIST ParamList;
	LISTITEM ParamItem;
	//参数
	if(FindMTParameterFirst(MonitorObj,ParamItem))
	{
		while((MonitorNode=::FindNext(ParamItem))!=INVALID_VALUE )
		{ 
			ParamList.clear();
			if(::EnumNodeAttrib(MonitorNode,ParamList))
			{	
				FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
				FileDataList.push_back(MonitorIDS);
				FindNodeValue(MonitorNode, "sv_helptext",MonitorIDS);
				FileDataList.push_back(MonitorIDS);				
				FindNodeValue(MonitorNode, "sv_tip",MonitorIDS);
				FileDataList.push_back(MonitorIDS);				
			}
		}
	}
	//错误
	MonitorNode = GetMTErrorAlertCondition(MonitorObj);
	if(MonitorNode!=INVALID_VALUE)
	{
		FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
		FileDataList.push_back(MonitorIDS);
		FindNodeValue(MonitorNode, "sv_helptext",MonitorIDS);
		FileDataList.push_back(MonitorIDS);				
		FindNodeValue(MonitorNode, "sv_tip",MonitorIDS);
		FileDataList.push_back(MonitorIDS);					
	}
	//危险
	MonitorNode = GetMTWarningAlertCondition(MonitorObj);
	if(MonitorNode!=INVALID_VALUE)
	{
		FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
		FileDataList.push_back(MonitorIDS);
		FindNodeValue(MonitorNode, "sv_helptext",MonitorIDS);
		FileDataList.push_back(MonitorIDS);				
		FindNodeValue(MonitorNode, "sv_tip",MonitorIDS);
		FileDataList.push_back(MonitorIDS);					
	}
	//正常
	MonitorNode = GetMTGoodAlertCondition(MonitorObj);
	if(MonitorNode!=INVALID_VALUE)
	{
		FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
		FileDataList.push_back(MonitorIDS);
		FindNodeValue(MonitorNode, "sv_helptext",MonitorIDS);
		FileDataList.push_back(MonitorIDS);				
		FindNodeValue(MonitorNode, "sv_tip",MonitorIDS);
		FileDataList.push_back(MonitorIDS);					
	}

	//高级参数
	if(FindMTAdvanceParameterFirst(MonitorObj,ParamItem))
	{
		while((MonitorNode=::FindNext(ParamItem))!=INVALID_VALUE )
		{ 
			ParamList.clear();
			if(::EnumNodeAttrib(MonitorNode,ParamList))
			{	
				FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
				FileDataList.push_back(MonitorIDS);
				FindNodeValue(MonitorNode, "sv_helptext",MonitorIDS);
				FileDataList.push_back(MonitorIDS);				
				FindNodeValue(MonitorNode, "sv_tip",MonitorIDS);
				FileDataList.push_back(MonitorIDS);				
			}
		}
	}
	//返回值
	if(FindMTReturnFirst(MonitorObj,ParamItem))
	{
		while((MonitorNode=::FindNext(ParamItem))!=INVALID_VALUE )
		{ 
			ParamList.clear();
			if(::EnumNodeAttrib(MonitorNode,ParamList))
			{	
				FindNodeValue(MonitorNode, "sv_label",MonitorIDS);
				FileDataList.push_back(MonitorIDS);
			}
		}
	}

	PAIRLIST LanguList;
    PAIRLIST::iterator LanguListItem;
	bool bGetLangu = GetAllResourceInfo(LanguList);
	bool bShowIds = true;
	int j = 1;
	SVTableCell ce;
	for(LanguListItem = LanguList.begin(); LanguListItem != LanguList.end();LanguListItem++)
	{
		string strLangu = LanguListItem->name;
		//Resource
		OBJECT objRes=LoadResource(strLangu, "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				int i=1;
				for(FileDataListRecord = FileDataList.begin();FileDataListRecord != FileDataList.end();FileDataListRecord++)
				{
					string mValue = *FileDataListRecord;
	
					char buf[256] = {0};
					itoa(i,buf,10);
					string strIndex = buf;
					if(bShowIds)
					{
						//IDS标识列
						new WText("&nbsp;&nbsp;&nbsp;", pContain->elementAt(i,0));		
						WText * m_pEdit = new WText(mValue, pContain->elementAt(i,0));

						ce.setType(adText);
						ce.setValue(m_pEdit);
						m_pList.WriteCell(strIndex,0,ce);

						//行号列
						WText * m_pRowNum = new WText(strIndex, pContain->elementAt(i,iLanguCount + 1));
						m_pRowNum->hide();

						ce.setType(adText);
						ce.setValue(m_pRowNum);
						m_pList.WriteCell(strIndex,iLanguCount + 1,ce);

						//编辑图片列
						WImage * m_pImage = new WImage("../icons/edit.gif", pContain->elementAt(i,iLanguCount + 2));
						m_pImage->setToolTip(strEditTip);
						m_pImage->setStyleClass("helpimg");
					
						connect(&m_userMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditIDSValue(const std::string)));
						m_userMapper.setMapping(m_pImage, mValue); 
						connect(m_pImage, SIGNAL(clicked()), &m_userMapper, SLOT(map()));

						ce.setType(adImage);
						ce.setValue(m_pImage);
						m_pList.WriteCell(strIndex,iLanguCount + 2,ce);	
					}	

					//各种语言列
					string strValue;
					FindNodeValue(ResNode,mValue,strValue);
					WText * m_pTValue = new WText(strValue, pContain->elementAt(i,j));

					ce.setType(adText);
					ce.setValue(m_pTValue);
					m_pList.WriteCell(strIndex,j,ce);		
					
					i++;
				}
			}
		}
		CloseResource(objRes);
		bShowIds = false;
		j++;
	}
	
	//添加一个LineEdit,防止回车转移到其他地址。
	int RowCount = pContain->numRows();
	WLineEdit * m_pTemp = new WLineEdit("",pContain->elementAt(RowCount,0));
	m_pTemp->hide();

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);

	for(int i=1;i<pContain->numRows();i++)
	{
		if(i%2==1)
		{
			pContain->GetRow(i)->setStyleClass("tr1");
		}
		else
		{
			pContain->GetRow(i)->setStyleClass("tr2");
		}
	}
}

//刷新
void CTranslate::refresh()
{
	if(iRefresh != 0)
	{
		m_pList.clear();
		pUserListTable->clear();

		AddColum(pUserListTable);

		char buf_tmp[4096]={0};
		int nSize =4095;
		GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
		//char * tmpquery;
		//tmpquery = getenv( "QUERY_STRING");
		//if(tmpquery)
		//	strcpy(buf_tmp,tmpquery);

		if(buf_tmp != NULL)
		{
			std::string buf1 = buf_tmp;
			size_t pos;
			pos = buf1.find("filepath=", 0);
			if(pos != string::npos)
			{
				pos = buf1.find("filepath=DeviceMonitorTemplate$", 0);
				if(pos != string::npos)
				{
					pos = buf1.find("deviceid=", 0);
					if(pos != string::npos)
					{
						strFileName = buf1.substr(pos+9,  buf1.size() - pos - 1);
						AddDeviceList(pUserListTable,strFileName);
					}
					pos = buf1.find("monitorid=", 0);
					if(pos != string::npos)
					{
						strFileName = buf1.substr(pos+10,  buf1.size() - pos - 1);
						AddMonitorList(pUserListTable,strFileName);
					}	
				}
				else
				{
					strFileName = buf1.substr(pos+9,  buf1.size() - pos - 1);
					//添加内容
					AddValue(pUserListTable,strFileName);
				}
			}
		}	
		bState = false;
	}
	iRefresh = 1;
}

//添加列
void CTranslate::AddColum(WTable* pContain)
{
	new WText(strIDSList, pContain->elementAt(0,0));

	iLanguCount = 0;

	//获取默认语言
	string strOpenFilePath = GetSiteViewRootPath() + "\\data\\svdbconfig.ini";
	CString cPath = "";
	cPath = strOpenFilePath.c_str();
	CString cTemp = "";
	::GetPrivateProfileString("svdb","DefaultLanguage","",cTemp.GetBuffer(MAX_PATH),MAX_PATH,cPath);
	DefaultLangu = (LPCTSTR)cTemp;

	PAIRLIST LanguList;
    PAIRLIST::iterator LanguListItem;
	bool bGetLangu = GetAllResourceInfo(LanguList);
	int j = 1;
	for(LanguListItem = LanguList.begin(); LanguListItem != LanguList.end();LanguListItem++)
	{
		//默认语言所在列号
		if(strcmp(LanguListItem->name.c_str(),DefaultLangu.c_str()) == 0)
		{
			DefaultLanguCol = j;
		}

		new WText(LanguListItem->name, pContain->elementAt(0,j));
		j++;
		iLanguCount += 1;
	}

	new WText(strEditName, pContain->elementAt(0,j+1));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}
}
//添加内容
void CTranslate::AddValue(WTable* pContain,const string filename)
{
	ifstream iFile;
	string strOpenFilePath = GetSiteViewRootPath() + "\\data\\language\\";
	strOpenFilePath += filename;
	strOpenFilePath += ".txt";
	iFile.open(strOpenFilePath.c_str(),ios::in,0);
	string FileData;
	list<string> FileDataList;
	list<string>::iterator FileDataListRecord;
	while(getline(iFile,FileData))
	{
		FileDataList.push_back(FileData);
	}
	iFile.close();
	
	PAIRLIST LanguList;
    PAIRLIST::iterator LanguListItem;
	bool bGetLangu = GetAllResourceInfo(LanguList);
	bool bShowIds = true;
	int j = 1;
	SVTableCell ce;
	for(LanguListItem = LanguList.begin(); LanguListItem != LanguList.end();LanguListItem++)
	{
		string strLangu = LanguListItem->name;
		//Resource
		OBJECT objRes=LoadResource(strLangu, "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				int i=1;
				for(FileDataListRecord = FileDataList.begin();FileDataListRecord != FileDataList.end();FileDataListRecord++)
				{
					string mValue = *FileDataListRecord;
	
					char buf[256] = {0};
					itoa(i,buf,10);
					string strIndex = buf;
					if(bShowIds)
					{
						//IDS标识列
						new WText("&nbsp;&nbsp;&nbsp;", pContain->elementAt(i,0));		
						WText * m_pEdit = new WText(mValue, pContain->elementAt(i,0));

						ce.setType(adText);
						ce.setValue(m_pEdit);
						m_pList.WriteCell(strIndex,0,ce);

						//行号列
						WText * m_pRowNum = new WText(strIndex, pContain->elementAt(i,iLanguCount + 1));
						m_pRowNum->hide();

						ce.setType(adText);
						ce.setValue(m_pRowNum);
						m_pList.WriteCell(strIndex,iLanguCount + 1,ce);

						//编辑图片列
						WImage * m_pImage = new WImage("../icons/edit.gif", pContain->elementAt(i,iLanguCount + 2));
						m_pImage->setToolTip(strEditTip);
						m_pImage->setStyleClass("helpimg");
					
						connect(&m_userMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditIDSValue(const std::string)));
						m_userMapper.setMapping(m_pImage, mValue); 
						connect(m_pImage, SIGNAL(clicked()), &m_userMapper, SLOT(map()));

						ce.setType(adImage);
						ce.setValue(m_pImage);
						m_pList.WriteCell(strIndex,iLanguCount + 2,ce);	
					}	

					//各种语言列
					string strValue;
					FindNodeValue(ResNode,mValue,strValue);
					WText * m_pTValue = new WText(strValue, pContain->elementAt(i,j));

					ce.setType(adText);
					ce.setValue(m_pTValue);
					m_pList.WriteCell(strIndex,j,ce);		
					
					i++;
				}
			}
		}
		CloseResource(objRes);
		bShowIds = false;
		j++;
	}
	
	//添加一个LineEdit,防止回车转移到其他地址。
	int RowCount = pContain->numRows();
	WLineEdit * m_pTemp = new WLineEdit("",pContain->elementAt(RowCount,0));
	m_pTemp->hide();

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);

	for(int i=1;i<pContain->numRows();i++)
	{
		if(i%2==1)
		{
			pContain->GetRow(i)->setStyleClass("tr1");
		}
		else
		{
			pContain->GetRow(i)->setStyleClass("tr2");
		}
	}
}
//编辑按钮处理函数
void CTranslate::EditIDSValue(const std::string strValue)
{
	OutputDebugString("－－－－－－EditIDSValue－－－－－－\n");
	if(bState)
	{
		if(pEditCell != NULL)
		{
			if(((WText*)pEditCell->Value())->isHidden())
			{
				((WText*)pEditCell->Value())->show();
			}
		}
	}

	if(pTempTable != NULL)
	{
		pTempTable->clear();
	}

	strIDSName = strValue;

	int RowNum = 0;
	for(row it = m_pList.begin(); it != m_pList.end(); it++ )
	{
		string IDSName,strIDSValue;
		SVTableCell *pcell = it->second.Cell(0);
		if ( pcell )
		{
			IDSName = ((WText*)pcell->Value())->text() ;	
			//默认语言中的IDS名称的Value
			if(strcmp(strValue.c_str(),IDSName.c_str()) == 0)
			{
				//获取行号，以便定位
                SVTableCell * pcell1 = it->second.Cell(iLanguCount + 1);
				string strRowNum = ((WText*)pcell1->Value())->text() ;
				RowNum = atoi(strRowNum.c_str());

                pEditCell = it->second.Cell(DefaultLanguCol);
				if ( pEditCell )
				{
					strIDSValue = ((WText*)pEditCell->Value())->text() ;

					OutputDebugString(strIDSValue.c_str());

					//隐藏文本
					((WText*)pEditCell->Value())->hide();
					
					//显示Table和LineEdit
					pTempTable = new WTable(pUserListTable->elementAt(RowNum,DefaultLanguCol));

					string strReplaceValue = strIDSValue;
					stringReplace( strReplaceValue, "&nbsp;"," ");
					
					OutputDebugString(strReplaceValue.c_str());

					m_pEditValue = new WLineEdit(strReplaceValue,pTempTable->elementAt(0,0));
					connect(m_pEditValue, SIGNAL(keyWentDown(int)), this, SLOT(EditReturn(int)));
					m_pEditValue->setTextSize(30);
				}
				break;
			}
		}
	}
	bState = true;
}
//回车处理函数
void CTranslate::EditReturn(int keyCode)
{
	if(keyCode == 13)
	{
		string IDSName,strIDSValue;
		IDSName = strIDSName;
		strIDSValue = m_pEditValue->text();

		OutputDebugString(strIDSValue.c_str());
	
		string strReplaceValue = strIDSValue;
		stringReplace( strReplaceValue, " ","&nbsp;");

		//显示文本
		if(pEditCell != NULL)
		{
			((WText*)pEditCell->Value())->setText(strReplaceValue);
			((WText*)pEditCell->Value())->show();
		}

		//隐藏Table和LineEdit
		if(pTempTable != NULL)
		{
			pTempTable->clear();
		}

		OBJECT objRes=LoadResource("default", "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				bool bAdd = AddNodeAttrib(ResNode,IDSName,strReplaceValue);
			}
			SubmitResource(objRes);
			CloseResource(objRes);
		}
	}
}
CTranslate::~CTranslate(void)
{
}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void usermain(int argc, char * argv[])
{
	WApplication app(argc, argv);
	app.setTitle("Translate");
	CTranslate setform(app.root());
	app.setBodyAttribute("class ='workbody'");
	app.exec();
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