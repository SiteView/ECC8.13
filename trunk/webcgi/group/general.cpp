#include "general.h"
#include "resstring.h"
#include "showtable.h"

#include "../../kennel/svdb/svapi/svapi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVGeneral::SVGeneral(WContainerWidget *parent):
WContainerWidget(parent)
{
    m_pDescription = NULL;
    //loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVGeneral::loadString()
//{
//	//Resource
//	OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//			FindNodeValue(ResNode,"IDS_General_Infor_Title",m_szGeneralTitle);
//			FindNodeValue(ResNode,"IDS_State",m_szState);
//			FindNodeValue(ResNode,"IDS_Description",m_szDesc);
//			FindNodeValue(ResNode,"IDS_Name",m_szName);
//			FindNodeValue(ResNode,"IDS_Device_Count",m_szDeviceCount);
//			FindNodeValue(ResNode,"IDS_Monitor_Count",m_szMonitorCount);
//			FindNodeValue(ResNode,"IDS_Monitor_Disable_Count",m_szMonitorDisable);
//			FindNodeValue(ResNode,"IDS_Monitor_Error_Count",m_szMonitorError);
//			FindNodeValue(ResNode,"IDS_Monitor_Warn_Count",m_szMonitorWarn);
//		}
//		CloseResource(objRes);
//	}
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGeneral::initForm()
{
    m_pStandard = new SVShowTable(this);
    if(m_pStandard)
    {
        m_pStandard->setTitle(SVResString::getResString("IDS_General_Infor_Title").c_str());
        WTable *pSub = m_pStandard->createSubTable();
        if (pSub)
        {
            new WText(SVResString::getResString("IDS_Name"), (WContainerWidget *)pSub->elementAt(0, 0));
            pSub->elementAt(0, 0)->setStyleClass("cell_10");
            m_pName = new WText("" , (WContainerWidget *)pSub->elementAt(0, 1));
            // ÃèÊö
            new WText(SVResString::getResString("IDS_Description"), (WContainerWidget *)pSub->elementAt(1, 0));
            pSub->elementAt(0, 0)->setStyleClass("cell_10");
            // ÃèÊöÐÅÏ¢
            m_pDescription = new WText("" , (WContainerWidget *)pSub->elementAt(1, 1));  
            // ×´Ì¬
            new WText(SVResString::getResString("IDS_State"), (WContainerWidget *)pSub->elementAt(2, 0));
            // ×´Ì¬ÐÅÏ¢
            m_pStateInfo = new WText("", (WContainerWidget *)pSub->elementAt(2, 1));  
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGeneral::setDescription(string &szDesc)
{
    if(m_pDescription)
        m_pDescription->setText(szDesc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGeneral::setState(string &szState)
{
    if(m_pStateInfo)
        m_pStateInfo->setText(szState);
}

void SVGeneral::setState()
{
    if(m_pStateInfo)
    {
        char szState[512] = {0};
        sprintf(szState, "%s%s%d, %s%d, %s%d, %s%d, %s%d", 
            m_szAdvState.c_str(),
            SVResString::getResString("IDS_Device_Count").c_str(), m_nDeviceCount,
            SVResString::getResString("IDS_Monitor_Count").c_str(), m_nMonitorCount,
            SVResString::getResString("IDS_Monitor_Disable_Count").c_str(), m_nMonitorDisableCount,
            SVResString::getResString("IDS_Monitor_Error_Count").c_str(), m_nMonitorErrCount, 
            SVResString::getResString("IDS_Monitor_Warn_Count").c_str(), m_nMonitorWarnCount);
        m_pStateInfo->setText(szState);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVGeneral::setTitle(string &szGroupName)
{
    if(m_pName)
        m_pName->setText(szGroupName);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
