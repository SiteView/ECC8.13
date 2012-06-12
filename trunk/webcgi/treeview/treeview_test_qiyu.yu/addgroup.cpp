/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// addgroup.cpp
// 添加新组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "addgroup.h"
#include "listtable.h"
#include "advanceparam.h"
#include "resstring.h"
#include "rightview.h"
#include "mainview.h"
#include "treeview.h"
#include "basefunc.h"
#include "basedefine.h"
#include "eccobjfunc.h"
#include "debuginfor.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WebSession.h"

#include "../../kennel/svdb/svapi/svapi.h"

#include "../userright/User.h"

#include "../base/OperateLog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccGroupOperate::CEccGroupOperate(WContainerWidget *parent):
CEccBaseTable(parent),
m_pGeneral(NULL),
m_pAdvance(NULL),
m_pName(NULL),
m_pNameErr(NULL),
m_szParentID(""),
m_szEditIndex("")
{
    initForm(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::SaveGroup()
{
    string szName("");

    unsigned long ulStart = GetTickCount();

    if(m_pNameErr)
        m_pNameErr->hide();

    if(!checkName(szName))
    {
        if(m_pNameErr)
            m_pNameErr->show();

        m_pGeneral->showSubTable();

        WebSession::js_af_up = "hiddenbar();";
        return;
    }

    string szOpt("Add new sub Group");

    OBJECT objGroup = INVALID_VALUE;
    if(m_szEditIndex.empty())
        objGroup = CreateGroup();
    else
    {
        szOpt = "Edit Group--->" + m_szEditIndex;
        objGroup = GetGroup(m_szEditIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    }

    if(objGroup != INVALID_VALUE)
    {
        bool AddAttrivSucc = false;
        MAPNODE mainNode = GetGroupMainAttribNode(objGroup);
        if(mainNode != INVALID_VALUE)
        {
            if(AddNodeAttrib(mainNode, svName, szName))
                if(m_pAdvance && m_pAdvance->SaveAdvanceParam(mainNode))
                    AddAttrivSucc = true;
        }

        string szDesc(""), szDepends(""), szCondition("");
        if(m_pAdvance)
        {
            szDesc = m_pAdvance->getDescription();
            szDepends = m_pAdvance->getDepends();
            szCondition = m_pAdvance->getConditon();
        }

        if(AddAttrivSucc && m_szEditIndex.empty())
        {
            if(!IsSVSEID(m_szParentID))
                saveDisableByParent(mainNode, SiteView_ECC_Group, m_szParentID);

            string szRealIndex = AddNewGroup(objGroup, m_szParentID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            // 创建组成功，触发创建成功消息
            if(!szRealIndex.empty())
            {    
                int nIndex = FindIndexByID(szRealIndex);
                nIndex = CEccTreeView::AppendGroup(szRealIndex, szName, szDesc, szDepends, szCondition);
                char szIndex[16] = {0};
                sprintf(szIndex, "%d", nIndex);
                AddNodeAttrib(mainNode, svShowIndex, szIndex);
                
                CEccTreeView::m_SVSEUser.AddUserScopeAllRight(szRealIndex, SiteView_ECC_Group);
            }
        }
        else if(AddAttrivSucc && !m_szEditIndex.empty())
        {
            if(SubmitGroup(objGroup, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
            {
                if(m_pAdvance && m_pAdvance->isDependsChanged())
                {
                    string szQueueName(getConfigTrackQueueName(m_szEditIndex));
                    CreateQueue(szQueueName, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                    if(!PushMessage(szQueueName, "GROUP:UPDATE", m_szEditIndex.c_str(), 
                        static_cast<int>(m_szEditIndex.length()) + 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                        PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
                }
            }
            CEccTreeView::EditGroup(m_szEditIndex, szName, szDesc, szDepends, szCondition);
        }

        CloseGroup(objGroup);
    }

    CEccMainView::m_pRightView->showMainForm();

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccGroupOperate.SaveGroup", szOpt, 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccGroupOperate.SaveGroup", szOpt, 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::Cancel()
{
    CEccMainView::m_pRightView->showMainForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::initForm(bool bHasHelp)
{
    CEccBaseTable::initForm(true);

    if(m_pContent)
    {
        createGeneral();
        createAdvance();
        createOperate();
    }

    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_AddGroup"));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::createAdvance()
{
    int nRow = m_pContent->numRows();

    m_pAdvance = new CEccAdvanceTable(m_pContent->elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::createGeneral()
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
            new WText(SVResString::getResString("IDS_Group_Name"), pSub->elementAt(0, 0));
            new WText("<span class =required>*</span>", pSub->elementAt(0, 0));
            // 对齐方式
            // 组名
            m_pName = new WLineEdit("", pSub->elementAt(0, 1));
            if(m_pName)
                m_pName->setStyleClass("cell_98");


            // 帮助
            WText *pNameHelp = new WText(SVResString::getResString("IDS_Group_Name_Help"), pSub->elementAt(1, 1));            
            if (pNameHelp)
            {
                pSub->elementAt(1, 1)->setStyleClass("table_data_input_des");
                pNameHelp->hide();
                m_lsHelp.push_back(pNameHelp);
            }

            m_pNameErr = new WText(SVResString::getResString("IDS_Group_Name_Error"), pSub->elementAt(2, 1));            
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
void CEccGroupOperate::createOperate()
{
    if(m_pOperate)
    {
        CEccImportButton *pSave = new CEccImportButton(SVResString::getResString("IDS_Save"), SVResString::getResString("IDS_Save_Group_Tip"), 
            "", m_pOperate->elementAt(0, 0));
        if(pSave)
        {
            WObject::connect(pSave, SIGNAL(clicked()), "showbar()", this, SLOT(SaveGroup()),
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::ShowHideHelp()
{
    m_bShowHelp = !m_bShowHelp;

    list<WText*>::iterator it;
    for(it = this->m_lsHelp.begin(); it != m_lsHelp.end(); it++)
    {
        if(m_bShowHelp)
            (*it)->show();
        else
            (*it)->hide();
    }

    if(m_pAdvance)
        m_pAdvance->ShowHideHelp(m_bShowHelp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::ResetData()
{
    if(m_pAdvance)
        m_pAdvance->ResetData();

    if(m_pName)
        m_pName->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::AddGroup(string szParentID)
{
    m_szParentID = szParentID;
    m_szEditIndex = "";

    ResetData();

    // 设置 主标题 显示文字
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_AddGroup"));

    if(m_pAdvance)
        m_pAdvance->setSEID(FindSEID(szParentID));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccGroupOperate::checkName(string &szName)
{
    bool bNoError = false;
    
    if(m_pName)
    {
        szName = m_pName->text();
        szName = strtriml(szName.c_str());
        szName = strtrimr(szName.c_str());

        if(!szName.empty())
            bNoError = true;
    }

    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccGroupOperate::EditGroup(string szCurrentID)
{
    m_szParentID = "";
    m_szEditIndex = szCurrentID;

    ResetData();

    if(m_pAdvance)
        m_pAdvance->setSEID(FindSEID(szCurrentID));

    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(szCurrentID);
    if(pNode)
    {
        const CEccTreeGroup *pGroup = static_cast<CEccTreeGroup*>(const_cast<CEccTreeNode*>(pNode));

        if(m_pName)
            m_pName->setText(pGroup->getName());

        if(m_pAdvance)
        {
            m_pAdvance->setDepends(pGroup->getDependsID());
            m_pAdvance->setDescription(pGroup->getDescription());
            m_pAdvance->setCondition(pGroup->getCondition());
        }

        // 设置 主标题 显示文字
        if(m_pTitle)
            m_pTitle->setText(SVResString::getResString("IDS_Edit_Group_Title"));
    }
    WebSession::js_af_up = "hiddenbar();";
}