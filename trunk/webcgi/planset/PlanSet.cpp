//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "planSet.h"

#if WIN32
#endif

extern void PrintDebugString(const char *szErrmsg);

#include "WebSession.h"

#include "../base/OperateLog.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
///////////////////////////////////////////////////
#include "WApplication"
#include "WCheckBox"
#include "WLineEdit"
#include "WImage"
#include "WSVFlexTable.h"
#include "WSVMainTable.h"
#include "WSVButton.h"
//#include "../../base/splitquery.h"
//using namespace SV_Split;

//////////////////////////////////////////////////////////////////////////////////
// start

//CSVPlanSet
CSVPlanSet::CSVPlanSet(WContainerWidget * parent):
WContainerWidget(parent)
{
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Plan",szTitle);
			FindNodeValue(ResNode,"IDS_State",m_FormShowText.szColStatus);
			FindNodeValue(ResNode,"IDS_Name",m_FormShowText.szColName);
			FindNodeValue(ResNode,"IDS_Type",m_FormShowText.szColType);
			FindNodeValue(ResNode,"IDS_Edit",m_FormShowText.szColMod);
			FindNodeValue(ResNode,"IDS_Time_Area",m_FormShowText.szColPlanTypeRel);
			FindNodeValue(ResNode,"IDS_Delete_Task_Affirm",m_FormShowText.szValDel);
			FindNodeValue(ResNode,"IDS_Time_Area_Task_Add",m_FormShowText.szAddRelPlanBut);
			FindNodeValue(ResNode,"IDS_Time_Task_Add",m_FormShowText.szAddAbPlanBut);
			FindNodeValue(ResNode,"IDS_Time_Area_Task_Plan",m_FormShowText.szTitle1);
			FindNodeValue(ResNode,"IDS_Type_Text",m_FormShowText.szTaskType);
			FindNodeValue(ResNode,"IDS_Time_Task_Plan",m_FormShowText.szTitle2);
			FindNodeValue(ResNode,"IDS_All_Select",m_FormShowText.szTipSelAll);
			FindNodeValue(ResNode,"IDS_None_Select",m_FormShowText.szTipNotSelAll);
			FindNodeValue(ResNode,"IDS_Invert_Select",m_FormShowText.szTipInvSel);
			FindNodeValue(ResNode,"IDS_Add",m_FormShowText.szTipAddNew);
			FindNodeValue(ResNode,"IDS_Delete",m_FormShowText.szTipDel);
			FindNodeValue(ResNode,"IDS_Plan_Sep_Null",strSepPlanNull);
			FindNodeValue(ResNode,"IDS_Plan_Abs_Null",strAbsPlanNull);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",m_FormShowText.szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",m_FormShowText.szButMatch);
			FindNodeValue(ResNode,"IDS_EditIntervalPlan",strEditIntervalPlan);
			FindNodeValue(ResNode,"IDS_EditAbPlan",strEditAbPlan);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh);
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);
			FindNodeValue(ResNode,"IDS_Del_Plan",strDelInPlan);
			FindNodeValue(ResNode,"IDS_Del_Ab_Plan",strDelAbPlan);
		}
		CloseResource(objRes);
	}

	hBegin= true;

	
	//IDS_Plan_Sep_Null = "[----------ʱ�������ƻ��б�Ϊ��----------]";
	//IDS_Plan_Abs_Null = "[----------����ʱ������ƻ��б�Ϊ��----------]";

	PlanSetForm();
}


//��ӿͻ��˽ű�����
void CSVPlanSet::AddJsParam(const std::string name, const std::string value)
{  
    std::string strTmp("");
    strTmp += "<SCRIPT language='JavaScript' > var ";
    strTmp += name;
    strTmp += "='";
    strTmp += value;
    strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}


void CSVPlanSet::PlanSetForm()
{
	strListHeights = "";
	strListTitles = "";
	strListPans = "";

	//pMainTable = new WSVMainTable(this, strMainTitle);
	//pUserTable = new WSVFlexTable(pMainTable->elementAt(2,0), Group, strTitle);
	//pMainTable = new WSVMainTable(this, "strMainTitle", false);

	
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	new WText("<div id='view_panel' class='panel_view'>", this);

	pMainTable = new WSVMainTable(this, szTitle, false);
	InitFlexTable(m_FormShowText.szTitle1, m_FormShowText.szTitle2);


	new WText("</div>", this);


	AddJsParam("listheight", strListHeights);
	AddJsParam("listtitle", strListTitles);
	AddJsParam("listpan", strListPans);
	

	AddJsParam("uistyle", "viewpanandlist");
	AddJsParam("fullstyle", "true");
	AddJsParam("bGeneral", "false");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>",this);

}



void CSVPlanSet::InitFlexTable(std::string strTitle1, std::string strTitle2)
{
	ReceiveAddrSetTable = new WSVFlexTable(pMainTable->GetContentTable()->elementAt(1,0), List, strTitle1);

	//new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);
	//WTable * m_pGeneral4 = new WTable(this);
	//WTable * m_pGeneral = new WTable( this );
	//m_pGeneral ->setStyleClass("t2");
    //if ( m_pGeneral )

	ReceiveAddrSetTable->SetDivId("listpan1");
	if(ReceiveAddrSetTable->GetContentTable()!=NULL)
    {
		strListHeights += "200";
		strListHeights += ",";
		strListPans += ReceiveAddrSetTable->GetDivId();
		strListPans += ",";
		strListTitles +=  ReceiveAddrSetTable->dataTitleTable->formName();
		strListTitles += ",";
		
		ReceiveAddrSetTable->AppendColumn("", WLength(5, WLength::Percentage));
		ReceiveAddrSetTable->SetDataRowStyle("table_data_grid_item_img");
		ReceiveAddrSetTable->AppendColumn(m_FormShowText.szColName, WLength(70, WLength::Percentage));
		ReceiveAddrSetTable->SetDataRowStyle("table_data_grid_item_img");
		ReceiveAddrSetTable->AppendColumn(m_FormShowText.szColMod, WLength(25, WLength::Percentage));
		ReceiveAddrSetTable->SetDataRowStyle("table_data_grid_item_text");
		
//older list table header
//		// �б�
//		ContainerReceiveAddrSetTable = new WTable((WContainerWidget *) m_pGeneral->elementAt(1,0));
//		ContainerReceiveAddrSetTable -> setStyleClass("t3");
//		ReceiveAddrSetTable = new WTable((WContainerWidget *) ContainerReceiveAddrSetTable->elementAt(0,0));
//		nullTable = new WTable((WContainerWidget *) ContainerReceiveAddrSetTable->elementAt(1, 0));
//
//		ReceiveAddrSetTable->setStyleClass("t3");
//		ReceiveAddrSetTable->setCellPadding(0);
//		ReceiveAddrSetTable->setCellSpaceing(0);
//		nullTable -> setStyleClass("t8");
//
//		// ��ӱ�ͷ
//		// ȫѡ  clicked �¼����� ���� SelAll
////		new WText(m_FormShowText.szColStatus, (WContainerWidget*)ReceiveAddrSetTable->elementAt(0, 0));
//		new WText("", (WContainerWidget*)ReceiveAddrSetTable->elementAt(0, 0));
//		new WText(m_FormShowText.szColName, (WContainerWidget*)ReceiveAddrSetTable->elementAt(0, 1));
////		new WText(m_FormShowText.szColType, (WContainerWidget*)ReceiveAddrSetTable->elementAt(0, 2));
//		new WText(m_FormShowText.szColMod, (WContainerWidget*)ReceiveAddrSetTable->elementAt(0, 2));
//		ReceiveAddrSetTable->elementAt(0, 0)->setStyleClass("t3title");
//		ReceiveAddrSetTable->elementAt(0, 1)->setStyleClass("t3title");
//		ReceiveAddrSetTable->elementAt(0, 2)->setStyleClass("t3title");
//		ReceiveAddrSetTable->elementAt(0, 3)->setStyleClass("t3title");

		updateRangeSchedule();
	}

	if(ReceiveAddrSetTable->GetActionTable()!=NULL)
	{
		ReceiveAddrSetTable->AddStandardSelLink(m_FormShowText.szTipSelAll , m_FormShowText.szTipNotSelAll, m_FormShowText.szTipInvSel );
		WObject::connect(ReceiveAddrSetTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		WObject::connect(ReceiveAddrSetTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		WObject::connect(ReceiveAddrSetTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));

		WTable *pTbl;
		ReceiveAddrSetTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		ReceiveAddrSetTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");

		pTbl = new WTable(ReceiveAddrSetTable->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");
		WSVButton * DelBtn = new WSVButton(pTbl->elementAt(0,0),m_FormShowText.szTipDel,"button_bg_del.png",m_FormShowText.szTipDel, false);
		connect(DelBtn, SIGNAL(clicked()) ,this, SLOT(BeforeDelPlan()));

		pTbl = new WTable(ReceiveAddrSetTable->GetActionTable()->elementAt(0,2));
		ReceiveAddrSetTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		WSVButton * btn = new WSVButton(ReceiveAddrSetTable->GetActionTable()->elementAt(0,2),m_FormShowText.szAddRelPlanBut,"button_bg_add_black.png",m_FormShowText.szAddRelPlanBut, true);
		connect(btn, SIGNAL(clicked()), this, SLOT(AddPlan()));
	

//
		//ft = new CFlexTable();
		//ft->AddGroupOperate(m_pGeneral,m_FormShowText.szValDel);
		//ft->AddGroupAddBtn(m_pGeneral,m_FormShowText.szAddRelPlanBut);
		//WObject::connect(ft->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		//WObject::connect(ft->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		//WObject::connect(ft->pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
  //      WObject::connect(ft->pDel , SIGNAL(clicked()) ,this, SLOT(BeforeDelPlan()));
		//WObject::connect(ft->pAdd, SIGNAL(clicked()), this, SLOT(AddPlan()));

		connect(&m_signalMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditPlan(const std::string)));
		
		//ReceiveAddrSetTable->SetNullTipInfo(strSepPlanNull);


		ReceiveAddrSetTable->SetNullTipInfo(strSepPlanNull);

		if(m_pListPlan.size() <= 0)
		{
			//OutputDebugString("---------------- NO S ------------------\n");
			//OutputDebugString(("---------------- NO S"+ strSepPlanNull + " ------------------\n").c_str());
			ReceiveAddrSetTable->ShowNullTip();
		}
		else
		{
			//OutputDebugString("---------------- Yes S------------------\n");
			ReceiveAddrSetTable->HideNullTip();
		}

		//���ذ�ť
		pHideBut = new WPushButton("hide button",this);
		if(pHideBut)
		{
			pHideBut->setToolTip("Hide Button");
			connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelPlan()));
			pHideBut->hide();
		}

		//���ذ�ť
		pHideBut1 = new WPushButton("hide button",this);
		if(pHideBut1)
		{
			pHideBut1->setToolTip("Hide Button");
			connect(pHideBut1,SIGNAL(clicked()),this,SLOT(DelPlan1()));
			pHideBut1->hide();
		}
	}


	//WTable * m_pGeneral2 = new WTable(this);
	//WTable * m_pGeneral1 = new WTable( this );
	//m_pGeneral1->setStyleClass("t2");
    //if ( m_pGeneral1 )

	ReceiveAddrSetTable1 = new WSVFlexTable(pMainTable->GetContentTable()->elementAt(2,0), List, strTitle2);
	ReceiveAddrSetTable1->SetDivId("listpan2");

	if(ReceiveAddrSetTable1->GetContentTable()!=NULL)
    {    
		strListHeights += "200";
		strListHeights += ",";
		strListPans += ReceiveAddrSetTable1->GetDivId();
		strListPans += ",";
		strListTitles +=  ReceiveAddrSetTable1->dataTitleTable->formName();
		strListTitles += ",";
		
		ReceiveAddrSetTable1->AppendColumn("",WLength(5,WLength::Percentage));
		ReceiveAddrSetTable1->SetDataRowStyle("table_data_grid_item_img");
		ReceiveAddrSetTable1->AppendColumn(m_FormShowText.szColName,WLength(70,WLength::Percentage));
		ReceiveAddrSetTable1->SetDataRowStyle("table_data_grid_item_img");
		ReceiveAddrSetTable1->AppendColumn(m_FormShowText.szColMod,WLength(25,WLength::Percentage));
		ReceiveAddrSetTable1->SetDataRowStyle("table_data_grid_item_text");



		//updateAbsSc
		updateAbsSchedule();

	}


	if(ReceiveAddrSetTable1->GetActionTable()!=NULL)
	{


		ReceiveAddrSetTable1->AddStandardSelLink(m_FormShowText.szTipSelAll , m_FormShowText.szTipNotSelAll, m_FormShowText.szTipInvSel );
		WObject::connect(ReceiveAddrSetTable1->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll1()));
		WObject::connect(ReceiveAddrSetTable1->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone1()));
		WObject::connect(ReceiveAddrSetTable1->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert1()));


		WTable *pTbl;

		ReceiveAddrSetTable1->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		ReceiveAddrSetTable1->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");

		pTbl = new WTable(ReceiveAddrSetTable1->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");
		WSVButton * BtDel = new WSVButton(pTbl->elementAt(0,0),m_FormShowText.szTipDel,"button_bg_del.png",m_FormShowText.szTipDel, false);
		connect(BtDel, SIGNAL(clicked()) ,this, SLOT(BeforeDelPlan1()));


		pTbl = new WTable(ReceiveAddrSetTable1->GetActionTable()->elementAt(0,2));
		ReceiveAddrSetTable1->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		WSVButton * btn = new WSVButton(ReceiveAddrSetTable1->GetActionTable()->elementAt(0,2),m_FormShowText.szAddAbPlanBut,"button_bg_add_black.png",m_FormShowText.szAddAbPlanBut, true);
		connect(btn, SIGNAL(clicked()), this, SLOT(AddPlan1()));

		//ft1 = new CFlexTable();
		//ft1->AddGroupOperate(m_pGeneral1,m_FormShowText.szValDel);
		//ft1->AddGroupAddBtn(m_pGeneral1 ,m_FormShowText.szAddAbPlanBut);

		//WObject::connect(ft1->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll1()));
		//WObject::connect(ft1->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone1()));
		//WObject::connect(ft1->pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert1()));
		//WObject::connect(ft1->pDel , SIGNAL(clicked()) ,this, SLOT(BeforeDelPlan1()));
		//WObject::connect(ft1->pAdd, SIGNAL(clicked()), this, SLOT(AddPlan1()));

		// m_signalMapper mapped �¼����� ���� EditMail
		connect(&m_signalMapper1, SIGNAL(mapped(const std::string)), this, SLOT(EditPlan1(const std::string)));
		
		
		ReceiveAddrSetTable1->SetNullTipInfo(strAbsPlanNull);

		if(m_pListPlan1.size() <= 0)
		{
			ReceiveAddrSetTable1->ShowNullTip();
			//OutputDebugString("---------------- NO A------------------\n");
		}
		else
		{
			//OutputDebugString("---------------- Yes A------------------\n");
			ReceiveAddrSetTable1->HideNullTip();
		}
	}	

}

void CSVPlanSet::updateRangeSchedule()
{

	//int nNum =ReceiveAddrSetTable->numRows();
	//for(int i=1;i<nNum;i++)
	//{
	//	ReceiveAddrSetTable->deleteRow(1);

	//}
	if(ReceiveAddrSetTable->GeDataTable() != NULL)
		ReceiveAddrSetTable->GeDataTable()->clear();
	
	m_pListPlan.clear();

		std::list<string> tasknamelist;
		std::list<string>::iterator m_pItem;
		GetAllTaskName(tasknamelist);

		bool bRelNull = true;
		int numRow = 1;
		//int numRow = ReceiveAddrSetTable->GeDataTable()->numRows();

		for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem ++)
	    {
			std::string m_pNameStr = *m_pItem;
			
			OBJECT hTask = GetTask(m_pNameStr);
			std::string sValue = GetTaskValue("Type", hTask);						

			if(strcmp(sValue.c_str(), m_FormShowText.szPlanTypeRel.c_str()) == 0)
			{
				bRelNull = false;
				// �õ�������
				//int numRow = ReceiveAddrSetTable->numRows();
	
				PLAN_LIST list;

				ReceiveAddrSetTable->InitRow(numRow);
				WCheckBox * pCheck = new WCheckBox("", ReceiveAddrSetTable->GeDataTable()->elementAt(numRow, 0));
				ReceiveAddrSetTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);
				connect(pCheck,SIGNAL(clicked()),this,SLOT(AdjustRangeDelState()));

				WText *pName = new WText(m_pNameStr, ReceiveAddrSetTable->GeDataTable()->elementAt(numRow , 2));
				ReceiveAddrSetTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);

				WImage *pEdit = new WImage("/Images/edit.gif", ReceiveAddrSetTable->GeDataTable()->elementAt(numRow,4));
				ReceiveAddrSetTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
				// ͼƬ cliecker�¼� ������ map
				connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));


//				// �Ƿ�ѡ��
//				WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)ReceiveAddrSetTable->elementAt(numRow, 0));
//				connect(pCheck,SIGNAL(clicked()),this,SLOT(AdjustRangeDelState()));
//			    
//				
//				// ����
//				WText *pName = new WText(m_pNameStr, (WContainerWidget*)ReceiveAddrSetTable->elementAt(numRow , 1));
//			
////				WText *pType = new WText(m_FormShowText.szColPlanTypeRel, (WContainerWidget*)ReceiveAddrSetTable->elementAt(numRow , 2));
//			 
//				WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)ReceiveAddrSetTable->elementAt(numRow , 2));
//				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
//			    
//				// ͼƬ cliecker�¼� ������ map
//				connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
				
				string szIndex = "" ;
				

				// �õ��������ֵ
				int nIndex = 1;

				// ����
				list.pSelect = pCheck;
				list.pName = pName;
//				list.pType = pType;
				list.pImage = pEdit;
				list.nIndex = nIndex;
				// ׷�ӵ���
				m_pListPlan.push_back(list);

				// ת������ֵΪ�ַ���
				char chIndex[32] = {0};
				sprintf(chIndex, "%d", nIndex);
				m_signalMapper.setMapping(pEdit, pName->text());

				// ����������
				WTableRow * pRow = ReceiveAddrSetTable->GeDataTable()->GetRow(numRow);
				pRow -> property = pName->text(); 
				numRow++;
			}
		}
		


		//ReceiveAddrSetTable->adjustRowStyle("tr1","tr2");

		//if(bRelNull)
		//{
		//	ReceiveAddrSetTable->ShowNullTip();

		//	//WText * nText = new WText(strSepPlanNull, (WContainerWidget*)nullTable1 -> elementAt(0, 0));
		//	//nText ->decorationStyle().setForegroundColor(Wt::red);
		//	//nullTable1 -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
		//}
		//else
		//{
		//	ReceiveAddrSetTable->HideNullTip();
		//}

}
void CSVPlanSet::AdjustAbsDelState()
{
	int nCheck =0;
	for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1 ++)
    {
		if(m_pListItem1->pSelect->isChecked())
		{
			nCheck ++;
			break;
		}
    }
	//if(nCheck>0)
	//{
	//	//ft1->pvDel->hide();
	//	ft1->pDel->show();
	//}else{
	//		ft1->pvDel->show();
	//		ft1->pDel->hide();
	//}
}
void CSVPlanSet::AdjustRangeDelState()
{
	int nCheck =0;
	for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem ++)
    {
		if(m_pListItem->pSelect->isChecked())
		{
			nCheck ++;
			break;
		}
    }
	//if(nCheck>0)
	//{
	//	ft->pvDel->hide();
	//	ft->pDel->show();
	//}else{
	//		ft->pvDel->show();
	//		ft->pDel->hide();
	//}	
}
void CSVPlanSet::updateAbsSchedule()
{
	//int nNum =ReceiveAddrSetTable1->numRows();
	//for(int i=1;i<nNum;i++)
	//{
	//	ReceiveAddrSetTable1->deleteRow(i);
	//

	if(ReceiveAddrSetTable1->GeDataTable() != NULL)
		ReceiveAddrSetTable1->GeDataTable()->clear();

	m_pListPlan1.clear();

	std::list<string> tasknamelist;
		std::list<string>::iterator m_pItem;
		GetAllTaskName(tasknamelist);
		
		bool bAbsNull = true;
		int numRow = 1;
		//int numRow = ReceiveAddrSetTable1->GeDataTable()->numRows();

		for(m_pItem = tasknamelist.begin(); m_pItem != tasknamelist.end(); m_pItem ++)
	    {
			std::string m_pNameStr = *m_pItem;
		
			OBJECT hTask = GetTask(m_pNameStr);
			std::string sValue = GetTaskValue("Type", hTask);
			
			if(strcmp(sValue.c_str(), m_FormShowText.szPlanTypeAb.c_str()) == 0)
			{
				bAbsNull = false;
				// �õ�������
				//int numRow = ReceiveAddrSetTable1->numRows();

				PLAN_LIST list;



				ReceiveAddrSetTable1->InitRow(numRow);
				WCheckBox * pCheck = new WCheckBox("", ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 0));
				ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(AlignCenter);
				connect(pCheck,SIGNAL(clicked()),this,SLOT(AdjustAbsDelState()));

				WText *pName = new WText(m_pNameStr, ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 2));
				ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(AlignCenter);
				WImage *pEdit = new WImage("/Images/edit.gif", ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 4));
				ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(AlignCenter);
				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);    
				// ͼƬ cliecker�¼� ������ map
				connect(pEdit, SIGNAL(clicked()), &m_signalMapper1, SLOT(map()));

//
//				// �Ƿ�ѡ��
//				WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)ReceiveAddrSetTable1->elementAt(numRow, 0));
//				connect(pCheck,SIGNAL(clicked()),this,SLOT(AdjustAbsDelState()));
////				connect 
//			    
//				// ����
//				WText *pName = new WText(m_pNameStr, (WContainerWidget*)ReceiveAddrSetTable1->elementAt(numRow , 1));
//			
////				WText *pType = new WText(m_FormShowText.szPlanTypeAb, (WContainerWidget*)ReceiveAddrSetTable1->elementAt(numRow , 2));
//
//			 
//				WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)ReceiveAddrSetTable1->elementAt(numRow , 2));
//				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
//			    
//				// ͼƬ cliecker�¼� ������ map
//				connect(pEdit, SIGNAL(clicked()), &m_signalMapper1, SLOT(map()));
				
				string szIndex = "" ;


				// �õ��������ֵ
				int nIndex = 1;

				// ����
				list.pSelect = pCheck;
				list.pName = pName;
//				list.pType = pType;
			    list.pImage = pEdit;
				list.nIndex = nIndex;
				// ׷�ӵ���
				m_pListPlan1.push_back(list);

				// ת������ֵΪ�ַ���
				char chIndex[32] = {0};
				sprintf(chIndex, "%d", nIndex);
				m_signalMapper1.setMapping(pEdit, pName->text());

				// ����������
				WTableRow * pRow = ReceiveAddrSetTable1->GeDataTable() -> GetRow(numRow);
				pRow -> property = pName->text();
				numRow++;
			}
		}

		//ReceiveAddrSetTable1->adjustRowStyle("tr1","tr2");
		//
		//if(bAbsNull)
		//{

		//	ReceiveAddrSetTable1->ShowNullTip();

		//	//WText * nText = new WText(strAbsPlanNull, (WContainerWidget*)nullTable1 -> elementAt(0, 0));
		//	//nText ->decorationStyle().setForegroundColor(Wt::red);
		//	//nullTable1 -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
		//}
		//else
		//{
		//	ReceiveAddrSetTable1->HideNullTip();
		//}
}
//////////////////////////////////////////////////////////////////////////////////
// SelAll
// ȫѡ
void CSVPlanSet::SelAll()
{   // �õ��б���ÿһ��
    for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem ++)
    {
        // �޸�ÿһ���ѡ��״̬
		m_pListItem->pSelect->setChecked(true);
    }
	AdjustRangeDelState();
}

void CSVPlanSet::SelNone()
{   // �õ��б���ÿһ��
    for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem ++)
    {
        // �޸�ÿһ���ѡ��״̬
        //m_pListItem->pSelect->setChecked(m_pSelectAll->isChecked());       
		m_pListItem->pSelect->setChecked(false);
    }
	AdjustRangeDelState();
}

void CSVPlanSet::SelInvert()
{
	for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem ++)
    {
        // �޸�ÿһ���ѡ��״̬
        //m_pListItem->pSelect->setChecked(m_pSelectAll->isChecked());       
		if(m_pListItem->pSelect->isChecked())
		{
			m_pListItem->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem->pSelect->setChecked(true);
		}
    }
	AdjustRangeDelState();
}


//////////////////////////////////////////////////////////////////////////////////
// Save
// ����
void CSVPlanSet::Save()
{
   
}

void CSVPlanSet::BeforeDelPlan()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "BeforeDelPlan";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	// �Ƚ��б���ÿһ��
	
	OutputDebugString("----------------AddPlan1------------------\n");
	for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem ++)
	{
		// �ж��Ƿ���ѡ��״̬
		if (m_pListItem->pSelect->isChecked())
		{  
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + m_FormShowText.szValDel + "','" + m_FormShowText.szButNum + "','" + m_FormShowText.szButMatch + "','" + strDelDes + "');"; 
					//OutputDebugString(strDelDes.c_str());
					WebSession::js_af_up = strDelDes;	
				}					
			}
			break;		
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//////////////////////////////////////////////////////////////////////////////////
// DelEmail
// ɾ����ѡ�����
void CSVPlanSet::DelPlan()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "DelPlan";
	LogItem.sDesc = strDelInPlan;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strDelName;
    // �Ƚ��б���ÿһ��
    for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem ++)
    {
        // �ж��Ƿ���ѡ��״̬
        if (m_pListItem->pSelect->isChecked())
        {   
            // �õ�����е���ʵ�к�
			std::string temp = m_pListItem->pName->text();
			DeleteTask(temp);

            int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();
            // ��ǰ��
            list<PLAN_LIST>::iterator pItem = m_pListItem;                     
            // �ص���һ��
            m_pListItem --;

			string strTemp1 = pItem->pName->text();
			strDelName += strTemp1;
			strDelName += "  ";

           // ���б���ɾ����ǰ��
            m_pListPlan.erase(pItem);          
            // �ڱ����ɾ����
            ReceiveAddrSetTable->GeDataTable()->deleteRow(nRow); 									
        }
    }

	//ReceiveAddrSetTable->adjustRowStyle("tr1","tr2");


		if(m_pListPlan.size() <= 0)
		{
			ReceiveAddrSetTable->ShowNullTip();
		}
		else
		{
			ReceiveAddrSetTable->HideNullTip();
		}

	//if(m_pListPlan.size() == 0)
	//{
	//	WText * nText = new WText(strSepPlanNull, (WContainerWidget*)nullTable -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	nullTable -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}
	//
	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_FormShowText.szTipDel,m_FormShowText.szTitle1,strDelName);

 // ����ȫѡΪ��ѡ��״̬
 //   m_pSelectAll->setChecked(false);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//////////////////////////////////////////////////////////////////////////////////
// AddEmail
// ���һ������
void CSVPlanSet::AddPlan()
{

    // �����������ƻ��б����¼�
	//nullTable->clear();
    emit AddNewPlan();
}

//////////////////////////////////////////////////////////////////////////////////
// AddMailList
// ����޸�����ƻ��б�ɹ��¼�������
void CSVPlanSet::AddPlanList(ADD_PLAN_OK plan)
{

    if((strcmp(chgstr.c_str(), "") != 0))
    {// ���������׷�ӵ�������޸ĺ���
		
        EditRow(plan);
        return;
    }
    
    // �õ�������
	int numRow = ReceiveAddrSetTable->GeDataTable()->numRows();

    PLAN_LIST list;

	ReceiveAddrSetTable->InitRow(numRow);

    // �Ƿ�ѡ��
	ReceiveAddrSetTable->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);
    WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)ReceiveAddrSetTable->GeDataTable()->elementAt(numRow, 0));
	connect(pCheck,SIGNAL(clicked()),this,SLOT(AdjustRangeDelState()));
    
    // ����
	ReceiveAddrSetTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
	WText *pName = new WText(plan.szName, (WContainerWidget*)ReceiveAddrSetTable->GeDataTable()->elementAt(numRow , 2));

	ReceiveAddrSetTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);
	WImage *pEdit = new WImage("/Images/edit.gif", (WContainerWidget*)ReceiveAddrSetTable->GeDataTable()->elementAt(numRow , 4));
    pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
    
    // ͼƬ cliecker�¼� ������ map
    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));
	
    string szIndex = "" ;
    

    // �õ��������ֵ
    int nIndex = 1;

    // ����
    list.pSelect = pCheck;
    list.pName = pName;
//    list.pType = pType;
    list.pImage = pEdit;
    list.nIndex = nIndex;
    // ׷�ӵ���
    m_pListPlan.push_back(list);

    // ת������ֵΪ�ַ���
    char chIndex[32] = {0};
    sprintf(chIndex, "%d", nIndex);
    m_signalMapper.setMapping(pEdit, pName->text()); 

    // ����������
	WTableRow * pRow = ReceiveAddrSetTable->GeDataTable() -> GetRow(numRow);
    pRow -> property = pName->text(); 

	ReceiveAddrSetTable->HideNullTip();
}

//////////////////////////////////////////////////////////////////////////////////
// EditRow
// �޸�һ��
void CSVPlanSet::EditRow(ADD_PLAN_OK &planlist)
{
    // �Ƚ���ÿһ��
	//table
    // �õ�������
	int numRow = ReceiveAddrSetTable->GeDataTable()->numRows();  
    for (int i = 1; i < numRow; i++)
    {
        // �����к�ȡһ��
		WTableRow * pRow = ReceiveAddrSetTable->GeDataTable() -> GetRow(i);
        if (strcmp(pRow->property.c_str(), chgstr.c_str()) == 0)
        {	
			pRow->property = planlist.szName;
		}
    }
    for(m_pListItem = m_pListPlan.begin(); m_pListItem != m_pListPlan.end(); m_pListItem++)
    {		
        // �ж�����ֵ�Ƿ�Ϊ���޸���
		if(strcmp(chgstr.c_str(), m_pListItem->pName->text().c_str()) == 0)
        {
            // ���ĸ�������
            // ����
            m_pListItem->pName->setText(planlist.szName);
			chgstr = "";

			m_signalMapper.setMapping(m_pListItem->pImage,planlist.szName); 
			connect(m_pListItem->pImage, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));

			break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
// EditPlan
// �޸��¼�
void CSVPlanSet::EditPlan(const std::string str)
{  
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "EditPlan";
	LogItem.sDesc = strEditIntervalPlan;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

    bool bFind = false;
    ADD_PLAN_OK planlist;
    char chIndex[32] = {0};

    // �õ�������
	int numRow = ReceiveAddrSetTable->GeDataTable()->numRows();  

    // �õ����޸ĵ�������

    for (int i = 1; i < numRow; i++)
    {
        // �����к�ȡһ��
		
        WTableRow * pRow = ReceiveAddrSetTable->GeDataTable() -> GetRow(i);
		
        // �Ƚ�����
        if (strcmp(pRow->property.c_str(), str.c_str()) == 0)
        {			
            char chTmp[10] = {0};
            // ���޸�������
            planlist.nIndex = i;
            // ���޸�������
			planlist.szName = str;
			chgstr = str;
            // ���޸��мƻ������б�
  
            // �ҵ��˴��޸���
            bFind = true;
            break;
        }
    }

    // �ҵ����޸��д����޸��¼�
    if(bFind)
        emit EditPlanList(planlist);
		
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVPlanSet::showPlanList()
{

	//pShow -> show();
	//pHide -> hide();
	ReceiveAddrSetTable -> show();
	//ft->m_pGroupOperate -> show();
}

void CSVPlanSet::hidePlanList()
{

	//pShow -> hide();
	//pHide -> show();
	ReceiveAddrSetTable -> hide();
	//ft->m_pGroupOperate -> hide();
}



//////////////////////////////////////////////////////////////////////////////////
// SelAll
// ȫѡ
void CSVPlanSet::SelAll1()
{   // �õ��б���ÿһ��
    for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1 ++)
    {
        // �޸�ÿһ���ѡ��״̬
        m_pListItem1->pSelect->setChecked(true);
    }
	AdjustAbsDelState();
}

void CSVPlanSet::SelNone1()
{
    for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1 ++)
    {
        // �޸�ÿһ���ѡ��״̬
 		m_pListItem1->pSelect->setChecked(false);
    }
	AdjustAbsDelState();
}

void CSVPlanSet::SelInvert1()
{
	for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1 ++)
    {
        // �޸�ÿһ���ѡ��״̬
 		if(m_pListItem1->pSelect->isChecked())
		{
			m_pListItem1->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem1->pSelect->setChecked(true);
		}
    }
	AdjustAbsDelState();
}


//////////////////////////////////////////////////////////////////////////////////
// Save
// ����
void CSVPlanSet::Save1()
{
   
}
void CSVPlanSet::BeforeDelPlan1()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "BeforeDelPlan1";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1 ++)
	{
		// �ж��Ƿ���ѡ��״̬
		if (m_pListItem1->pSelect->isChecked())
		{   
			if(pHideBut1)
			{
				string strDelDes = pHideBut1->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + m_FormShowText.szValDel + "','" + m_FormShowText.szButNum + "','" + m_FormShowText.szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;		
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//////////////////////////////////////////////////////////////////////////////////
// DelPlan1
// ɾ����ѡ�����
void CSVPlanSet::DelPlan1()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "DelPlan1";
	LogItem.sDesc = strDelAbPlan;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strDelName;
    // �Ƚ��б���ÿһ��
    for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1 ++)
    {
        // �ж��Ƿ���ѡ��״̬
        if (m_pListItem1->pSelect->isChecked())
        {   
            // �õ�����е���ʵ�к�
			std::string temp = m_pListItem1->pName->text();
			DeleteTask(temp);

            int nRow = ((WTableCell*)(m_pListItem1->pSelect->parent()))->row();
            // ��ǰ��
            list<PLAN_LIST>::iterator pItem = m_pListItem1;                
            // �ص���һ��
            m_pListItem1 --;

			string strTemp1 = pItem->pName->text();
			strDelName += strTemp1;
			strDelName += "  ";
 
			// ���б���ɾ����ǰ��
            m_pListPlan1.erase(pItem);          
            // �ڱ����ɾ����
            ReceiveAddrSetTable1->GeDataTable()->deleteRow(nRow);             
        }
    }
	//ReceiveAddrSetTable1->adjustRowStyle("tr1","tr2");
    // ����ȫѡΪ��ѡ��״̬

	if(m_pListPlan1.size() <= 0)
	{
		ReceiveAddrSetTable1->ShowNullTip();
	}
	else
	{
		ReceiveAddrSetTable1->HideNullTip();
	}

	// if(m_pListPlan1.size() == 0)
	//{
	//	WText * nText = new WText(strAbsPlanNull, (WContainerWidget*)nullTable1 -> elementAt(0, 0));
	//	nText ->decorationStyle().setForegroundColor(Wt::red);
	//	nullTable1 -> elementAt(0, 0) -> setContentAlignment(AlignTop | AlignCenter);
	//}

	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_FormShowText.szTipDel,m_FormShowText.szTitle2,strDelName);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//////////////////////////////////////////////////////////////////////////////////
// AddPlan1
// ���һ������
void CSVPlanSet::AddPlan1()
{

    // ����ȫѡΪ��ѡ��״̬

	//m_pSelectAll1->setChecked(false);

    // ��������б����¼�
	//nullTable1 -> clear();
    emit AddNewPlan1();	
}

//////////////////////////////////////////////////////////////////////////////////
// AddPlanList
// ����޸��б�ɹ��¼�������
void CSVPlanSet::AddPlanList1(ADD_PLAN_OK plan)
{

    if((strcmp(chgstr.c_str(), "") != 0))
    {// ���������׷�ӵ�������޸ĺ���
        EditRow1(plan);
        return;
    }
    
    // �õ�������
	int numRow = ReceiveAddrSetTable1->GeDataTable()->numRows();

    PLAN_LIST list;

	ReceiveAddrSetTable1->InitRow(numRow);
    // �Ƿ�ѡ��
    ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);
	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow, 0));
	connect(pCheck,SIGNAL(clicked()),this,SLOT(AdjustAbsDelState()));

    
    // ����
	ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
	WText *pName = new WText(plan.szName, (WContainerWidget*)ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow , 2));
	
	ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);
	WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)ReceiveAddrSetTable1->GeDataTable()->elementAt(numRow , 4));
    pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
    
    // ͼƬ cliecker�¼� ������ map
    connect(pEdit, SIGNAL(clicked()), &m_signalMapper1, SLOT(map()));
	
    string szIndex = "" ;


    // �õ��������ֵ
    int nIndex = 1;

    // ����
    list.pSelect = pCheck;
    list.pName = pName;
//    list.pType = pType;
	list.pImage = pEdit;
    list.nIndex = nIndex;
    // ׷�ӵ��ƻ��б���
    m_pListPlan1.push_back(list);

    // ת������ֵΪ�ַ���
    char chIndex[32] = {0};
    sprintf(chIndex, "%d", nIndex);
    m_signalMapper1.setMapping(pEdit, pName->text()); 

    // ����������
	WTableRow * pRow = ReceiveAddrSetTable1->GeDataTable() -> GetRow(numRow);
    pRow -> property = pName->text(); 

	ReceiveAddrSetTable1->HideNullTip();
}

//////////////////////////////////////////////////////////////////////////////////
// EditRow1
// �޸�һ��
void CSVPlanSet::EditRow1(ADD_PLAN_OK &planlist)
{

	//table
    // �õ�������
	int numRow = ReceiveAddrSetTable1->GeDataTable()->numRows();  
    for (int i = 1; i < numRow; i++)
    {
        // �����к�ȡһ��
        WTableRow * pRow = ReceiveAddrSetTable1->GeDataTable() -> GetRow(i);
        if (strcmp(pRow->property.c_str(), chgstr.c_str()) == 0)
        {
			pRow->property = planlist.szName;
        }
    }
	
    // �Ƚ��б���ÿһ��
    for(m_pListItem1 = m_pListPlan1.begin(); m_pListItem1 != m_pListPlan1.end(); m_pListItem1++)
    {
        // �ж�����ֵ�Ƿ�Ϊ���޸���
        if(strcmp(chgstr.c_str(), m_pListItem1->pName->text().c_str()) == 0)
        {
            // ���ĸ�������
            // ����
            m_pListItem1->pName->setText(planlist.szName);
			// �б�
			chgstr = "";
			
			m_signalMapper1.setMapping(m_pListItem1->pImage,planlist.szName); 
			connect(m_pListItem1->pImage, SIGNAL(clicked()), &m_signalMapper1, SLOT(map()));
                      
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
// EditMail
// �޸��¼�
void CSVPlanSet::EditPlan1(const string str)
{  
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "EditPlan1";
	LogItem.sDesc = strEditAbPlan;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

    bool bFind = false;
    ADD_PLAN_OK planlist;
    char chIndex[32] = {0};

	OutputDebugString(str.c_str());

    // �õ�������
    int numRow = ReceiveAddrSetTable1->GeDataTable()->numRows();  

    // �õ����޸ĵ�������
    for (int i = 1; i < numRow; i++)
    {
        // �����к�ȡһ��
        WTableRow * pRow = ReceiveAddrSetTable1->GeDataTable() -> GetRow(i);
        // �Ƚ�����
        if (strcmp(pRow->property.c_str(), str.c_str()) == 0)
        {
			
            char chTmp[10] = {0};
            // ���޸�������
            planlist.nIndex = i;
            // ���޸�������
			planlist.szName = str;
			chgstr = str;
            // ���޸��мƻ������б�
  
            // �ҵ��˴��޸���
            bFind = true;
            break;
        }
    }
	
    // �ҵ����޸��д����޸ļƻ������б��¼�
    if(bFind)
        emit EditPlanList1(planlist);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void CSVPlanSet::showPlanList1()
{

	//pShow1 -> show();
	//pHide1 -> hide();
	ReceiveAddrSetTable1 -> show();
	//ft1->m_pGroupOperate -> show();
}

void CSVPlanSet::hidePlanList1()
{

	//pShow1 -> hide();
	//pHide1 -> show();
	ReceiveAddrSetTable1 -> hide();
	//ft1->m_pGroupOperate -> hide();
}

//////////////////////////////////////////////////////////////////////////////////
// refresh
// ����ˢ���¼�
void CSVPlanSet::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "PlanSet";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//if(hBegin )
	//	hBegin =false;
	//else
	//{
		//nullTable -> clear();
		//nullTable1 -> clear();
	ReceiveAddrSetTable->GeDataTable()->clear();
	ReceiveAddrSetTable1->GeDataTable()->clear();

	updateAbsSchedule();
	updateRangeSchedule();
	//}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//û��
void CSVPlanSet::AddGroupOperate(WTable * pTable)
{
//    m_pGroupOperate = new WTable((WContainerWidget *)pTable->elementAt( 2, 0));
//
//    if ( m_pGroupOperate )
//    {
//        WImage *pSelAll = new WImage("../Images/selall.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
//        if (pSelAll)
//        {
//            pSelAll->setStyleClass("commonbutton");
//            pSelAll->setToolTip(m_FormShowText.szTipSelAll);
//            WObject::connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
//        }
//
//        WImage *pSelNone = new WImage("../Images/selnone.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
//        if (pSelAll)
//        {
//            pSelNone->setStyleClass("commonbutton");
//            pSelNone->setToolTip(m_FormShowText.szTipNotSelAll);
//            WObject::connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
//        }
//
//        WImage *pSelinvert = new WImage("../Images/selinvert.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
//        if (pSelinvert)
//        {
//            pSelinvert->setStyleClass("commonbutton");
//            pSelinvert->setToolTip(m_FormShowText.szTipInvSel);
//			WObject::connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
//        }
//        
//        
//        
//        WImage *pDel = new WImage("../Images/del.gif", (WContainerWidget *)m_pGroupOperate->elementAt(0, 4));
//        if (pDel)
//        {
//            pDel->setStyleClass("commonbutton");
//            pDel->setToolTip(m_FormShowText.szTipDel);
//			//wangpeng
//			std::string strDelDes;
//			strDelDes  = "_Delclick(\"";
//			strDelDes += m_FormShowText.szValDel;
//			strDelDes +=  "\",";
//			WObject::connect(pDel , SIGNAL(clicked()),  strDelDes.c_str() ,this, SLOT(DelPlan()));
//
//        }
//
//		WPushButton *pAdd = new WPushButton(m_FormShowText.szAddRelPlanBut, (WContainerWidget *)m_pGroupOperate->elementAt(0, 5));
//        if (pAdd)
//        {
//            pAdd->setToolTip(m_FormShowText.szTipAddNew);
//            WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(AddPlan()));
//			m_pGroupOperate->elementAt(0, 5)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
//			m_pGroupOperate->elementAt(0, 5)->setContentAlignment(AlignRight);
//	
////			pAdd->resize(WLength(10,WLength::Pixel),WLength(50,WLength::Pixel));
//			
//        }
//
//    }

}

void CSVPlanSet::AddGroupOperate1(WTable * pTable)
{
  //  m_pGroupOperate1 = new WTable((WContainerWidget *)pTable->elementAt( 2, 0));
  //  if ( m_pGroupOperate )
  //  {
  //      WImage *pSelAll = new WImage("../Images/selall.gif", (WContainerWidget *)m_pGroupOperate1->elementAt(0, 1));
  //      if (pSelAll)
  //      {
  //          pSelAll->setStyleClass("commonbutton");
  //          pSelAll->setToolTip(m_FormShowText.szTipSelAll);
  //          WObject::connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll1()));
  //      }

  //      WImage *pSelNone = new WImage("../Images/selnone.gif", (WContainerWidget *)m_pGroupOperate1->elementAt(0, 2));
  //      if (pSelAll)
  //      {
  //          pSelNone->setStyleClass("commonbutton");
  //          pSelNone->setToolTip(m_FormShowText.szTipNotSelAll);
  //          WObject::connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone1()));
  //      }

  //      WImage *pSelinvert = new WImage("../Images/selinvert.gif", (WContainerWidget *)m_pGroupOperate1->elementAt(0, 3));
  //      if (pSelinvert)
  //      {
  //          pSelinvert->setStyleClass("commonbutton");
  //          pSelinvert->setToolTip(m_FormShowText.szTipInvSel);
		//	WObject::connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert1()));
  //      }
  //      
  //      
  //      
  //      WImage *pDel = new WImage("../Images/del.gif", (WContainerWidget *)m_pGroupOperate1->elementAt(0, 4));
  //      if (pDel)
  //      {
  //          pDel->setStyleClass("commonbutton");
  //          pDel->setToolTip(m_FormShowText.szTipDel);
		//	std::string strDelDes;
		//	strDelDes  = "_Delclick(\"";
		//	strDelDes += m_FormShowText.szValDel;
		//	strDelDes +=  "\",";
		//	WObject::connect(pDel , SIGNAL(clicked()),  strDelDes.c_str() ,this, SLOT(DelPlan1()));

		//	
  //      }
		//WPushButton *pAdd = new WPushButton(m_FormShowText.szAddAbPlanBut, (WContainerWidget *)m_pGroupOperate1->elementAt(0, 5));
  //      if (pAdd)
  //      {
  //          pAdd->setToolTip(m_FormShowText.szTipAddNew);
  //          WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(AddPlan1()));
		//	m_pGroupOperate1->elementAt(0, 5)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));
		//	m_pGroupOperate1->elementAt(0, 5)->setContentAlignment(AlignRight);

  //      }
		//
  //  }

}
void CSVPlanSet::adjustRowStyle()
{
	//ReceiveAddrSetTable->adjustRowStyle("tr1","tr2");
	//ReceiveAddrSetTable1->adjustRowStyle("tr1","tr2");

}

// end
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
// end file
