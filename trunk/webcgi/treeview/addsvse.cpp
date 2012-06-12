#include "addsvse.h"
#include "rightview.h"
#include "mainview.h"
#include "listtable.h"
#include "basefunc.h"
#include "treeview.h"
#include "debuginfor.h"

#include "../../opens/libwt/Websession.h"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WText"

#include "../base/OperateLog.h"

#include "../userright/User.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccEidtSVSE::CEccEidtSVSE(WContainerWidget *parent):
CEccBaseTable(parent),
m_pName(NULL),
m_pNameErr(NULL),
m_szEditIndex("")
{
    initForm(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::EditSVSE(const string &szIndex)
{
    m_szEditIndex = szIndex;

    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Edit_SE_Title"));
    OBJECT objSE = GetSVSE(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objSE != INVALID_VALUE)
    {
        if(m_pName)
            m_pName->setText(GetSVSELabel(objSE));

        CloseSVSE(objSE);
    }

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::Cancel()
{
    CEccRightView::showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::saveSVSE()
{
    unsigned long ulStart = GetTickCount();
    string szName("");

    if(m_pNameErr)
        m_pNameErr->hide();

    if(!checkName(szName))
    {
        if(m_pNameErr)
            m_pNameErr->show();

        if(m_pGeneral)
            m_pGeneral->showSubTable();

        WebSession::js_af_up = "hiddenbar();";
        return;
    }

    OBJECT objSE = GetSVSE(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objSE != INVALID_VALUE)
    {
        if(PutSVSELabel(objSE, szName))
            if(SubmitSVSE(objSE, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                CEccTreeView::EditSVSE(m_szEditIndex, szName);

        CloseSVSE(objSE);
    }

    CEccRightView::showMainForm();

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccEidtSVSE.saveSVSE", "Edit SVSE " + m_szEditIndex, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccEidtSVSE.saveSVSE", "Edit SVSE " + m_szEditIndex, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::ShowHideHelp()
{
    list<WText*>::iterator it;
    for(it = this->m_lsHelp.begin(); it != m_lsHelp.end(); it++)
    {
        if(m_bShowHelp)
            (*it)->show();
        else
            (*it)->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::initForm(bool bHasForm)
{
    CEccBaseTable::initForm(bHasForm);

    if(m_pContent)
        createGeneral();

    createOperater();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::createGeneral()
{
    int nRow = m_pContent->numRows();

    m_pGeneral = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
    if(m_pGeneral)
    {
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Infor_Title"));
        WTable *pSub = m_pGeneral->getListTable();
        if (pSub)
        {
            // 组名（必添项）显示文字
            new WText(SVResString::getResString("IDS_SE_Label"), pSub->elementAt(0, 0));
            new WText("<span class =required>*</span>", pSub->elementAt(0, 0));
            // 对齐方式
            // 组名
            m_pName = new WLineEdit("", pSub->elementAt(0, 1));
            if(m_pName)
                m_pName->setStyleClass("cell_98");

            // 帮助
            WText *pNameHelp = new WText(SVResString::getResString("IDS_SE_Label_Tip"), pSub->elementAt(1, 1));            
            if (pNameHelp)
            {
                pSub->elementAt(1, 1)->setStyleClass("table_data_input_des");
                pNameHelp->hide();
                m_lsHelp.push_back(pNameHelp);
            }

            m_pNameErr = new WText(SVResString::getResString("IDS_SE_Label_Error"), pSub->elementAt(2, 1));            
            if (m_pNameErr)
            {
                pSub->elementAt(2, 1)->setStyleClass("table_data_input_error");
                m_pNameErr->hide();
            }

            pSub->GetRow(0)->setStyleClass("padding_top");
            pSub->elementAt(0, 0)->setStyleClass("table_list_data_input_text");
            pSub->elementAt(0, 1)->setStyleClass("table_data_text");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccEidtSVSE::checkName(string &szName)
{
    if(m_pName)
    {
        szName = m_pName->text();
        szName = strtriml(szName.c_str());
        szName = strtrimr(szName.c_str());

        if(!szName.empty())
            return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccEidtSVSE::createOperater()
{
    if(m_pOperate)
    {
        CEccImportButton *pSave = new CEccImportButton(SVResString::getResString("IDS_Save"), SVResString::getResString("IDS_Save"), 
            "", m_pOperate->elementAt(0, 0));
        if(pSave)
        {
            WObject::connect(pSave, SIGNAL(clicked()), "showbar()", this, SLOT(saveSVSE()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(0, 1));

        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel"), SVResString::getResString("IDS_Cancel_Current_Edit_Tip"),
            "", m_pOperate->elementAt(0, 2));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), this, SLOT(Cancel()));
        }
    }
}
