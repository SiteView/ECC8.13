
#include "statedesc.h"
#include "resstring.h"

CSVStateDesc::CSVStateDesc(WContainerWidget *parent):
WTable(parent)
{
    //loadString();
    initForm();
}

//void CSVStateDesc::loadString()
//{
//    OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//	        FindNodeValue(ResNode, "IDS_Error",             m_szErrDesc);
//	        FindNodeValue(ResNode, "IDS_Normal",            m_szNormalDesc);
//	        FindNodeValue(ResNode, "IDS_State_Description", m_szStatesDesc);
//	        FindNodeValue(ResNode, "IDS_Warnning",      m_szWarnningDesc);
//	        FindNodeValue(ResNode, "IDS_NO_Date",       m_szNoDataDesc);
//	        FindNodeValue(ResNode, "IDS_Disable",       m_szDisableDesc);
//		}
//		CloseResource(objRes);
//	}
//}

void CSVStateDesc::initForm()
{
    new WText(SVResString::getResString("IDS_State_Description") + ":&nbsp;", elementAt(0, 0));
    
    new WImage("../icons/nodata.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_NO_Date") + ";&nbsp;", elementAt(0, 0));

    new WImage("../icons/normal.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Normal") + ";&nbsp;", elementAt(0, 0));

    new WImage("../icons/warnning.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Warnning") + ";&nbsp;", elementAt(0, 0));

    new WImage("../icons/error.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Error") + ";&nbsp;", elementAt(0, 0));

    new WImage("../icons/disablemonitor.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Disable"), elementAt(0, 0));

}
