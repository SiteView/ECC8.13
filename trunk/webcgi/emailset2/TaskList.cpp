//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "TaskList.h"
#include <svapi.h>

//////////////////////////////////////////////////////////////////////////////////
// start
CTaskList::CTaskList(WContainerWidget * parent):
WTable(parent)
{ 
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
/*			//添加Resource
			bool bAdd = AddNodeAttrib(ResNode,"IDS_Monday","星期一");
			bAdd = AddNodeAttrib(ResNode,"IDS_Tuesday","星期二");
			bAdd = AddNodeAttrib(ResNode,"IDS_Wednesday","星期三");
			bAdd = AddNodeAttrib(ResNode,"IDS_Thursday","星期四");
			bAdd = AddNodeAttrib(ResNode,"IDS_Friday","星期五");
			bAdd = AddNodeAttrib(ResNode,"IDS_Saturday","星期六");
			bAdd = AddNodeAttrib(ResNode,"IDS_Sunday","星期日");
			bAdd = AddNodeAttrib(ResNode,"IDS_From","从");
			bAdd = AddNodeAttrib(ResNode,"IDS_To","到");
*/
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Enable",m_formText.szEnable);
			FindNodeValue(ResNode,"IDS_Monday",m_formText.szMon);
			FindNodeValue(ResNode,"IDS_Tuesday",m_formText.szThurs);
			FindNodeValue(ResNode,"IDS_Wednesday",m_formText.szWed);
			FindNodeValue(ResNode,"IDS_Thursday",m_formText.szTues);
			FindNodeValue(ResNode,"IDS_Friday",m_formText.szFri);
			FindNodeValue(ResNode,"IDS_Saturday",m_formText.szSat);
			FindNodeValue(ResNode,"IDS_Sunday",m_formText.szSun);
			FindNodeValue(ResNode,"IDS_From",m_formText.szfrom);
			FindNodeValue(ResNode,"IDS_To",m_formText.szTo);
		}
//		SubmitResource(objRes);
		CloseResource(objRes);
	}
    AddItem();
}

void CTaskList::AddItem()
{
	new WText(m_formText.szSun, (WContainerWidget*)elementAt(0,0));
	new WText(m_formText.szMon, (WContainerWidget*)elementAt(1,0));
	new WText(m_formText.szThurs, (WContainerWidget*)elementAt(2,0));
	new WText(m_formText.szWed, (WContainerWidget*)elementAt(3,0));
	new WText(m_formText.szTues, (WContainerWidget*)elementAt(4,0));
	new WText(m_formText.szFri, (WContainerWidget*)elementAt(5,0));
	new WText(m_formText.szSat, (WContainerWidget*)elementAt(6,0));

    WText *pFrom[7], * pTo[7];
    for(int i = 0; i < 7 ; i ++)
    {
        m_pCombo[i] = new WComboBox((WContainerWidget*)elementAt(i, 1));
        m_pCombo[i]->addItem(m_formText.szEnable);
        m_pCombo[i]->addItem(m_formText.szDisable);

        pFrom[i] = new WText(m_formText.szfrom, (WContainerWidget*)elementAt(i, 2));
    
        m_pStart[i] = new WLineEdit("00:00", (WContainerWidget*)elementAt(i, 3));
        m_pStart[i] -> setTextSize(10);

        pTo[i] = new WText(m_formText.szTo, (WContainerWidget*)elementAt(i, 4));
    
        m_pEnd[i] = new WLineEdit("23:59", (WContainerWidget*)elementAt(i, 5)); 
        m_pEnd[i] -> setTextSize(10);
    }
}

const char * CTaskList::GetTaskTime()
{
    return NULL;
}

void CTaskList::Reset()
{
    for(int i = 0; i < 7 ; i ++)
    {
        m_pCombo[i]->setCurrentIndex(0);    
        m_pStart[i] ->setText("00:00");    
        m_pEnd[i]  ->setText("23:59"); 
    }
}
//////////////////////////////////////////////////////////////////////////////////
// end file
