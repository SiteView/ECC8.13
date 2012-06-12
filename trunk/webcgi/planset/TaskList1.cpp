//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "TaskList1.h"
#include <svapi.h>

//////////////////////////////////////////////////////////////////////////////////
// start
CTaskList1::CTaskList1(WContainerWidget * parent, WTable * table):
WTable(parent)
{
    AddItem(table);
}


CTaskList1::CTaskList1(WContainerWidget * parent, WSVFlexTable * table,const string helpSun):
WTable(parent)
{
	string szMon,szThurs,szWed,szTues,szFri,szSat,szSun,szDisable,szEnable,szfrom,szTo;
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Disable",szDisable);
			FindNodeValue(ResNode,"IDS_Enable",szEnable);
			FindNodeValue(ResNode,"IDS_Monday",szMon);
			FindNodeValue(ResNode,"IDS_Tuesday",szThurs);
			FindNodeValue(ResNode,"IDS_Wednesday",szWed);
			FindNodeValue(ResNode,"IDS_Thursday",szTues);
			FindNodeValue(ResNode,"IDS_Friday",szFri);
			FindNodeValue(ResNode,"IDS_Saturday",szSat);
			FindNodeValue(ResNode,"IDS_Sunday",szSun);
			FindNodeValue(ResNode,"IDS_From",szfrom);
			FindNodeValue(ResNode,"IDS_To",szTo);
		}
		CloseResource(objRes);
	}

	static std::string DayType[] = {szSun, szMon, szThurs, szWed, szTues, szFri, szSat};

   		WTable *RecList = new WTable(table->AppendRowsContent(0, DayType[0],helpSun, "ERROR"));
		RecList->setStyleClass("widthauto");
		
		WText *pFrom[7], * pTo[7];

		m_pCombo[0] = new WComboBox((WContainerWidget*)RecList->elementAt(0, 1));
		m_pCombo[0]->addItem(szEnable);
		m_pCombo[0]->addItem(szDisable);
		//pFrom[0] = new WText(szfrom, (WContainerWidget*)RecList->elementAt(0, 2));
		new WText("&nbsp;", (WContainerWidget*)RecList->elementAt(0, 2));
		m_pStart[0] = new WLineEdit("00:00", (WContainerWidget*)RecList->elementAt(0, 3));
		m_pStart[0]->resize(WLength(100, WLength::Pixel),WLength(20, WLength::Pixel));
		m_pStart[0]->setStyleClass("input_text");
		//pTo[0] = new WText(szTo, (WContainerWidget*)RecList->elementAt(0, 4));
		//m_pEnd[0] = new WLineEdit("23:59", (WContainerWidget*)RecList->elementAt(0, 5));
		//m_pEnd[0]->setStyleClass("input_text");

		for (int i=1; i<7; i++)
		{
			WTable *RecList = new WTable(table->AppendRowsContent(0, DayType[i], "", ""));
			RecList->setStyleClass("widthauto");
			m_pCombo[i] = new WComboBox((WContainerWidget*)RecList->elementAt(0, 1));
			m_pCombo[i]->addItem(szEnable);
			m_pCombo[i]->addItem(szDisable);
			new WText("&nbsp;", (WContainerWidget *)RecList->elementAt(0, 2));
			//pFrom[i] = new WText(szfrom,(WContainerWidget*) RecList->elementAt(0, 2));
			m_pStart[i] = new WLineEdit("00:00", (WContainerWidget*)RecList->elementAt(0, 3));
			m_pStart[i]->resize(WLength(100, WLength::Pixel),WLength(20, WLength::Pixel));
			m_pStart[i]->setStyleClass("input_text");
			//pTo[i] = new WText(szTo, (WContainerWidget*)RecList->elementAt(0, 4));
			//m_pEnd[i] = new WLineEdit("23:59", (WContainerWidget*)RecList->elementAt(0, 5));
			//m_pEnd[i]->setStyleClass("input_text");
		}
		
}

void CTaskList1::AddItem(WTable * parent)
{
	string szMon,szThurs,szWed,szTues,szFri,szSat,szSun,szDisable,szEnable,szfrom,szTo;
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Disable",szDisable);
			FindNodeValue(ResNode,"IDS_Enable",szEnable);
			FindNodeValue(ResNode,"IDS_Monday",szMon);
			FindNodeValue(ResNode,"IDS_Tuesday",szThurs);
			FindNodeValue(ResNode,"IDS_Wednesday",szWed);
			FindNodeValue(ResNode,"IDS_Thursday",szTues);
			FindNodeValue(ResNode,"IDS_Friday",szFri);
			FindNodeValue(ResNode,"IDS_Saturday",szSat);
			FindNodeValue(ResNode,"IDS_Sunday",szSun);
			FindNodeValue(ResNode,"IDS_From",szfrom);
			FindNodeValue(ResNode,"IDS_To",szTo);
		}
		CloseResource(objRes);
	}
	new WText(szSun, (WContainerWidget*)parent -> elementAt(0+3,0));
	new WText(szMon, (WContainerWidget*)parent -> elementAt(2+3,0));
	new WText(szThurs, (WContainerWidget*)parent -> elementAt(4+3 ,0));
	new WText(szWed, (WContainerWidget*)parent -> elementAt(6+3 ,0));
	new WText(szTues, (WContainerWidget*)parent -> elementAt(8+3 ,0));
	new WText(szFri, (WContainerWidget*)parent -> elementAt(10+3 ,0));
	new WText(szSat, (WContainerWidget*)parent -> elementAt(12+3 ,0));

    WText *pFrom[7], * pTo[7];
    for(int i = 0; i < 7 ; i ++)
    {    
		m_pCombo[i] = new WComboBox((WContainerWidget*)parent -> elementAt(2*i+3 , 1));
        m_pCombo[i]->addItem(szEnable);
        m_pCombo[i]->addItem(szDisable);

        m_pStart[i] = new WLineEdit("", (WContainerWidget*)parent -> elementAt(2*i+3 , 1));
        m_pStart[i] -> setTextSize(60);

    }
}

const char * CTaskList1::GetTaskTime()
{
    return NULL;
}

void CTaskList1::Reset()
{
    for(int i = 0; i < 7 ; i ++)
    {        
		m_pCombo[i] ->setCurrentIndex(0);
        m_pStart[i] ->setText("00:00");        
    }
}
//////////////////////////////////////////////////////////////////////////////////
// end file
