#include "AnswerTable.h"

#include "svapi.h"

#include <Algorithm>
#include <WText>
#include <WTable>
#include <WImage>
#include <WTableCell>
#include <WScrollArea>
//////////////////////////////////////////////////////////////////////////////////
// start
CAnswerTable::CAnswerTable(WContainerWidget * parent, const std::string strTitle)
:WTable(parent)
{
	bShowHelp = false;
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Save",strSave);
			FindNodeValue(ResNode,"IDS_Save_And_Add",strSaveAndAdd);
			FindNodeValue(ResNode,"IDS_Cancel",strCancel);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Help",strHelp);
		}
		CloseResource(objRes);
	}
/*
	strSave = "保存";
	strSaveAndAdd = "保存并继续添加";
	strCancel = "取消";
*/
	this->setStyleClass("t5");
	this->setCellPadding(0);
	this->setCellSpaceing(0);

	//标题行
	//new WText(strTitle, (WContainerWidget*)this->elementAt(0,0));
	//this->elementAt(0,0)->setStyleClass("t1title");
/*
	//第二行
	this->elementAt(1,0)->setStyleClass("t5");	
	
	//第二行内部表格
	m_pContentTable = new WTable(this->elementAt(1,0));	
	m_pContentTable->setCellPadding(0);
	m_pContentTable->setCellSpaceing(0);
	m_pContentTable->setStyleClass("t5");

	//第二行滚动视图－管理内部表格
	WScrollArea * pScrollArea = new WScrollArea(this->elementAt(1,0));
	pScrollArea->setStyleClass("t5");	
	pScrollArea->setWidget(m_pContentTable);

	//内部表格第一行右边放帮助按钮
	m_pContentTable->elementAt(0, 0)->setContentAlignment(AlignRight);
	
	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)m_pContentTable->elementAt(0, 0));
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pContentTable->elementAt(0, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)m_pContentTable->elementAt(0, 0));
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();
*/
	/*new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pContentTable->elementAt(0, 0));

	m_pHelpimg = new WImage("../Images/help.gif", (WContainerWidget *)m_pContentTable->elementAt(0, 0));	
	m_pHelpimg ->setStyleClass("helpimg");
    m_pHelpimg ->setToolTip(strHelp);
	WObject::connect(m_pHelpimg,SIGNAL(clicked()),this,SLOT(ShowOrHideHelp()));	*/

	//内部表格
	p_ContentTabe = new WSVMainTable(this->elementAt(0,0),strTitle,true);
	//p_ContentOtherTabe = new WSVMainTable(this->elementAt(1,0),"",false);
	p_ContentOtherTabe = new WTable(this->elementAt(1,0));
	
	//内部表格第二行放其他东西....

	//第三行－按钮栏
	this->elementAt(2,0)->setContentAlignment(AlignCenter);
	WTable *pTbl;
	pTbl = new WTable(this->elementAt(3,0));

	pSave = new WSVButton(pTbl->elementAt(0, 1), strSave, "button_bg_m_black.png", strSave, true);
	pCancel = new WSVButton(pTbl->elementAt(0, 2), strCancel, "button_bg_m.png");
	pTbl->elementAt(0, 1)->resize(WLength(20,WLength::Pixel),WLength(0,WLength::Pixel));
	pTbl->elementAt(0, 2)->resize(WLength(20,WLength::Pixel),WLength(0,WLength::Pixel));

	pSaveAndAdd = new WPushButton(strSaveAndAdd, pTbl->elementAt(0, 0));
	new WText("&nbsp;&nbsp;&nbsp;",pTbl->elementAt(0, 0));
	pSaveAndAdd->hide();	
	new WText("&nbsp;&nbsp;&nbsp;",pTbl->elementAt(0,3));
}
/*
void CAnswerTable::ShowOrHideHelp()
{
	if(bShowHelp)
	{
		bShowHelp = false;
		for (unsigned i = 0; i < m_pListHelpText.size(); ++i)
		{
			m_pListHelpText[i]->hide();
		}

	}
	else
	{
		bShowHelp = true;
		for (unsigned i = 0; i < m_pListHelpText.size(); ++i)
		{
			m_pListHelpText[i]->show();
		}
	}
}

void CAnswerTable::ShowErrorMsg(std::list<string> msgList)
{
	for (unsigned j = 0; j < m_pListErrorText.size(); j++)
	{
		m_pListErrorText[j]->hide();
	}			

	std::list<string>::iterator msgitem;
	for(msgitem = msgList.begin(); msgitem != msgList.end(); msgitem ++)	
	{
		for (unsigned j = 0; j < m_pListErrorText.size(); j++)
		{
			if(m_pListErrorText[j]->text() == *msgitem)
			{
				m_pListErrorText[j]->show();
				continue;
			}
		}			
	}
}

void CAnswerTable::HideAllErrorMsg()
{
	for (unsigned j = 0; j < m_pListErrorText.size(); j++)
	{
		m_pListErrorText[j]->hide();
	}			
}

void CAnswerTable::AddHelpText(WTable* childTable,const std::string strHelp, int nRow, int nCol)
{
	WText* pText = new WText(strHelp, childTable->elementAt(nRow, nCol));
	childTable->elementAt(nRow, nCol)->setStyleClass("helps");
	m_pListHelpText.push_back(pText);
	pText->hide();
}

void CAnswerTable::AddErrorText(WTable* childTable,const std::string strHelp, int nRow, int nCol)
{
	WText* pText = new WText(strHelp, childTable->elementAt(nRow, nCol));
	childTable->elementAt(nRow, nCol)->setStyleClass("errors");
	m_pListErrorText.push_back(pText);
	pText->hide();
}
*/