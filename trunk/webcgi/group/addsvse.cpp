#include "addsvse.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "resstring.h"

extern void PrintDebugString(const string &szMsg);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVAddSE::SVAddSE(WContainerWidget *parent, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szIDCUser = szIDCUser;
    m_szIDCPwd  = szIDCPwd;

    m_pGeneral = NULL;
    m_pName = NULL;
    //m_pHost = NULL;
    m_pNameHelp = NULL;
    m_pTitle = NULL;
    //m_pDescription = NULL;

    m_bShowHelp = false;

    m_pContentTable = NULL;
    m_pSubContent = NULL;

    //m_pHostHelp = NULL;
    //m_pDescriptionHelp = NULL;


    m_pSave = NULL;
    m_pCancel = NULL;

//    loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVAddSE::loadString()
//{
//	//Resource
//	OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//			FindNodeValue(ResNode,"IDS_SE_Label",m_szName);
//			FindNodeValue(ResNode,"IDS_SE_Label_Tip",m_szNameHelp);
//			FindNodeValue(ResNode,"IDS_SE_Label_Error",m_szNameTip);
//			FindNodeValue(ResNode,"IDS_Basic_Option",m_szMainTitle);
//			FindNodeValue(ResNode,"IDS_Add_SE_Title",m_szTitle);
//			FindNodeValue(ResNode,"IDS_Save",m_szSaveTip);
//			FindNodeValue(ResNode,"IDS_Cancel",m_szBackTip);
//			FindNodeValue(ResNode,"IDS_Help",m_szHelpTip);
//			FindNodeValue(ResNode,"IDS_Edit_SE_Title",m_szEditTitle);
//			FindNodeValue(ResNode,"IDS_Host_Name",m_szHost);
//			FindNodeValue(ResNode,"IDS_Host_Name_Tip",m_szHostHelp);
//			FindNodeValue(ResNode,"IDS_Host_Name_Error",m_szHostTip);
//			FindNodeValue(ResNode,"IDS_Advance_Option",m_szAdvTitle);
//			FindNodeValue(ResNode,"IDS_Description",m_szDescription);
//			FindNodeValue(ResNode,"IDS_Desc_Help",m_szDescriptionHelp);
//			FindNodeValue(ResNode,"IDS_Save",m_szSave);
//			FindNodeValue(ResNode,"IDS_Cancel",m_szBack);
//		}
//		CloseResource(objRes);
//	}
//}

void SVAddSE::initForm()
{
    setStyleClass("t5");
    addTitle();

    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        addGeneral();
        //addAdvance();
    }

    addOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVAddSE::addAdvance()
//{ 
//    int nRow = m_pSubContent->numRows();
//    SVShowTable * pTable = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow,0));
//    if(pTable)
//    {
//        pTable->setTitle(SVResString::getResString("IDS_Advance_Option").c_str());
//        WTable * pSub = pTable->createSubTable();
//        if(pSub)
//        {
//            // ±íÍ·£¨ÃèÊö£©
//            new WText(SVResString::getResString("IDS_Description"), (WContainerWidget*)pSub->elementAt(0, 0));            
//            pSub->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
//            pSub->elementAt(0, 0)->setStyleClass("cell_10");
//
//            // ÃèÊö
//            m_pDescription = new WTextArea("", (WContainerWidget*)pSub->elementAt(0, 1)); 
//            if(m_pDescription)
//            {   
//                m_pDescription->setStyleClass("cell_98");           
//                m_pDescription->setRows(5);
//            }
//            //»»ÐÐ
//            new WText("<BR>", (WContainerWidget*)pSub->elementAt(0, 1));
//            // ÃèÊö°ïÖú
//            m_pDescriptionHelp = new WText(SVResString::getResString("IDS_Desc_Help"), (WContainerWidget*)pSub->elementAt(0, 1));
//            if (m_pDescriptionHelp)
//            {
//                // ÑùÊ½±í
//                m_pDescriptionHelp->setStyleClass("helps"); 
//                // Òþ²Ø
//                m_pDescriptionHelp->hide();
//            }
//        }
//    }
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::addTitle()
{
    int nRow = numRows();

    m_pTitle = new WText(SVResString::getResString("IDS_Add_SE_Title"), (WContainerWidget*)elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("t1title");

    nRow ++;
    m_pContentTable = new WTable((WContainerWidget*)elementAt(nRow, 0));
    if(m_pContentTable)
    {
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t5");           
        elementAt(nRow, 0)->setStyleClass("t7");

        nRow = m_pContentTable->numRows();
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
        if(m_pSubContent)
        {
            int nRow =  m_pSubContent->numRows();   
            m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight); 

            WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
            if(pHelp)
            {
                pHelp->setStyleClass("imgbutton");
                pHelp->setToolTip(SVResString::getResString("IDS_Help"));
                WObject::connect(pHelp, SIGNAL(clicked()), "showbar();", this, SLOT(showHelp()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            }
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::addGeneral()
{
    int nRow = m_pSubContent->numRows();
    SVShowTable * pTable = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow,0));
    if(pTable)
    {
        pTable->setTitle(SVResString::getResString("IDS_Basic_Option").c_str());
        WTable * pSub = pTable->createSubTable();
        if(pSub)
        {
            int nRow = pSub->numRows();

            //new WText(SVResString::getResString("IDS_Host_Name"), (WContainerWidget*)pSub->elementAt(nRow,0));
            //pSub->elementAt(nRow,0)->setStyleClass("cell_10");

            //m_pHost = new WLineEdit("", pSub->elementAt(nRow,1));
            //if(m_pHost)
            //    m_pHost->setStyleClass("cell_98");
            //new WText("<BR>", (WContainerWidget*)pSub->elementAt(nRow,1));
            //m_pHostHelp = new WText(SVResString::getResString("IDS_Host_Name_Tip"), (WContainerWidget*)pSub->elementAt(nRow,1));
            //if(m_pHostHelp)
            //{
            //    m_pHostHelp->setStyleClass("helps");
            //    m_pHostHelp->hide();
            //}

            //nRow ++;
            new WText(SVResString::getResString("IDS_SE_Label"), (WContainerWidget*)pSub->elementAt(nRow,0));
            pSub->elementAt(nRow,0)->setStyleClass("cell_10");
            m_pName = new WLineEdit("", pSub->elementAt(nRow,1));
            if(m_pName)
                m_pName->setStyleClass("cell_98");
            new WText("<BR>", (WContainerWidget*)pSub->elementAt(nRow,1));
            m_pNameHelp = new WText(SVResString::getResString("IDS_SE_Label_Tip"), (WContainerWidget*)pSub->elementAt(nRow,1));
            if(m_pNameHelp)
            {
                m_pNameHelp->setStyleClass("helps");
                m_pNameHelp->hide();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::addOperate()
{
    int nRow = numRows();
    m_pSave = new WPushButton(SVResString::getResString("IDS_Save"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pSave)
    {
        m_pSave->setToolTip(SVResString::getResString("IDS_Save"));
        WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(saveSVSE()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }

    new WText("   ", (WContainerWidget*)elementAt(nRow, 0));

    m_pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
    if(m_pCancel)
    {
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel"));
        WObject::connect(m_pCancel, SIGNAL(clicked()), this, SLOT(backPreview()));
    }

    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::AddSVSE()
{
    resetData();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::EditSVSE(string &szIndex)
{
    if(szIndex.empty())
        return;
    resetData();

    m_szEditIndex = szIndex;
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Edit_SE_Title"));
    OBJECT objSE = GetSVSE(m_szEditIndex, m_szIDCUser, m_szIDCPwd);
    if(objSE != INVALID_VALUE)
    {
        if(m_pName)
            m_pName->setText(GetSVSELabel(objSE));
        CloseSVSE(objSE);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::resetData()
{
    m_szEditIndex = "";
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_SE_Title"));
    //if(m_pHost)
    //    m_pHost->setText("");
    if(m_pName)
        m_pName->setText("");
    //if(m_pDescription)
    //    m_pDescription->setText("");
    m_bShowHelp = true;
    showHelp();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::saveSVSE()
{
    string szLabel (""), szHost (""), szDescription ("");
    if(m_pName)
        szLabel = m_pName->text();
    if(szLabel.empty())
    {
        if(m_pNameHelp)
        {
            m_pNameHelp->setStyleClass("errors");
            m_pNameHelp->setText(SVResString::getResString("IDS_SE_Label_Error"));
            m_pNameHelp->show();
        }
        WebSession::js_af_up = "hiddenbar()";
        return;
    }

    OBJECT objSE;
    if(m_szEditIndex.empty())
        objSE = CreateSVSE(szLabel);
    else
        objSE = GetSVSE(m_szEditIndex, m_szIDCUser, m_szIDCPwd);

    if(objSE != INVALID_VALUE)
    {
        if(PutSVSELabel(objSE,szLabel))
        {
            if(m_szEditIndex.empty())
            {
                string szRealID = AddNewSVSE(objSE, m_szIDCUser, m_szIDCPwd);
                emit AddSVSESucc(szLabel,szRealID);
            }
            else
            {
                if(SubmitSVSE(objSE, m_szIDCUser, m_szIDCPwd))
                    emit EditSVSESucc(szLabel, m_szEditIndex);
            }
        }
        CloseSVSE(objSE);
    }
    backPreview();
    WebSession::js_af_up = "hiddenbar()";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::showHelp()
{
    m_bShowHelp = !m_bShowHelp;
    if(m_bShowHelp)
    {
        //if(m_pHostHelp)
        //{
        //    m_pHostHelp->setText(SVResString::getResString("IDS_Host_Name_Tip"));
        //    m_pHostHelp->show();
        //}
        if(m_pNameHelp)
        {
            m_pNameHelp->setText(SVResString::getResString("IDS_SE_Label_Tip"));
            m_pNameHelp->show();
        }
        //if(m_pDescriptionHelp)
        //{
        //    m_pDescriptionHelp->setText(SVResString::getResString("IDS_Desc_Help"));
        //    m_pDescriptionHelp->show();
        //}
    }
    else
    {
        //if(m_pHostHelp)
        //    m_pHostHelp->hide();
        if(m_pNameHelp)
            m_pNameHelp->hide();
        //if(m_pDescriptionHelp)
        //    m_pDescriptionHelp->hide();
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddSE::backPreview()
{
    m_szEditIndex = "";
    emit backSVSEView();
}
