/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "addgroup.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../base/basetype.h"
#include "resstring.h"
//#include "../base/OperateLog.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char * szMsg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVAddGroup::SVAddGroup(WContainerWidget *parent,CUser * pUser, string szIDCUser, string szIDCPwd):
WTable(parent)
{
    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pTitle = NULL;
    m_pContentTable = NULL;
    m_pSubContent = NULL;
    m_pAdvanced = NULL;
    m_pSave = NULL;
    m_pCancel = NULL;

    m_pSVUser = pUser;

    //loadString();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initForm
// ˵�� ��ʼ��ҳ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::initForm()
{
    setStyleClass("t5");

    addGroupTitle();
    if(m_pSubContent)
    {
        addGroupGeneral();
        addGroupAdv();
    }
    addGroupOperate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� addGroupGeneral
// ˵�� ��ӻ������Ա�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupGeneral()
{
    // �õ������ݱ�����
    int nRow = m_pSubContent->numRows();
    // ����������/��ʾ��
    SVShowTable *pSub = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    if (pSub)
    {
        // ���ñ���
        pSub->setTitle(SVResString::getResString("IDS_General_Title").c_str());
        // �����ӱ�
        m_pGeneral = pSub->createSubTable();
        if (m_pGeneral)
        {
            // �������������ʾ����
            new WText(SVResString::getResString("IDS_Group_Name"), (WContainerWidget*)m_pGeneral->elementAt(0, 0));
            new WText("<span class =required>*</span>", m_pGeneral->elementAt(0, 0));
            // ���뷽ʽ
            m_pGeneral->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
            m_pGeneral->elementAt(0, 0)->setStyleClass("cell_10");
            // ����
            m_pName = new WLineEdit("", (WContainerWidget*)m_pGeneral->elementAt(0, 1));
            if(m_pName)
                m_pName->setStyleClass("cell_98");
            // ����
            new WText("<BR>", (WContainerWidget*)m_pGeneral->elementAt(0, 1));
            m_pNameHelp = new WText(SVResString::getResString("IDS_Group_Name_Help"), (WContainerWidget*)m_pGeneral->elementAt(0, 1));
            if (m_pNameHelp)
            {
                m_pNameHelp->setStyleClass("helps");
                m_pNameHelp->hide();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� addGroupAdv
// ˵�� �����߼����Ա�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupAdv()
{
    // �õ������ݱ�ǰ����
    int nRow = m_pSubContent->numRows();
    // �߼����Բ�����
    m_pAdvanced = new SVDependTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� addGroupOperate
// ˵�� ����������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupOperate()
{
    int nRow = numRows();
    // ���� ��ť
    m_pSave = new WPushButton(SVResString::getResString("IDS_Save"), (WContainerWidget*)elementAt(nRow, 0));
    if (m_pSave)
    {
        // �� click
        WObject::connect(m_pSave, SIGNAL(clicked()), "showbar();", this, SLOT(saveGroup()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        // tooltip
        m_pSave->setToolTip(SVResString::getResString("IDS_Save_Group_Tip"));
    }

    new WText("&nbsp;",this->elementAt(nRow,0));

    // ������һ��
    m_pCancel = new WPushButton(SVResString::getResString("IDS_Cancel"), (WContainerWidget*)elementAt(nRow, 0));
    if (m_pCancel)
    {
        // �� click
        WObject::connect(m_pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(backPreview()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        // tooltip
        m_pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Group_Edit_Tip"));
    }
    // ���ö��뷽ʽ
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� addGroupTitle
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::addGroupTitle()
{
    // �õ���ǰ����
    int nRow = numRows();
    // ����js�ļ�
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));
    
    // ��ǰ������1
	nRow ++;
    // ����������
    m_pTitle = new WText(SVResString::getResString("IDS_Add_Group_Title"), (WContainerWidget*)elementAt(nRow, 0));
    // ��������ʽ
    elementAt(nRow, 0)->setStyleClass("t1title");
    // ��ǰ������1
    nRow ++;
    // �������ݱ�
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // ���õ�Ԫ��� Padding��Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        // ����������
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        // ������ʽ
        m_pContentTable->setStyleClass("t5");           
        elementAt(nRow, 0)->setStyleClass("t7");

        // �õ����ݱ�ǰ��
        nRow = m_pContentTable->numRows();
        // ���������ݱ�
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // ���ݱ�ǰ���䷽ʽ
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
        if(m_pSubContent)
        {
            // �����ݱ� ��ʽ
            m_pSubContent->setStyleClass("t8");
            // �����ݱ�Ԫ����뷽ʽ�����ϣ�
            m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight); 

			// ����
            int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	        if(bTrans == 1)
	        {
                // ���밴ť
	            m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)elementAt(nRow, 0));
	            if(m_pTranslateBtn)
	            {
                    // �� click
		            connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
		            m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
                }
                new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	        }

            // ����
			WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
            if(pHelp)
            {
                // ��ʽ
                pHelp->setStyleClass("imgbutton");
                // tooltip
                pHelp->setToolTip(SVResString::getResString("IDS_Help"));
                // ��click
                WObject::connect(pHelp, SIGNAL(clicked()), "showbar();", this, SLOT(showHelp()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Translate
// ˵�� ������Ӧ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "groupRes";
	WebSession::js_af_up += "')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveGroup
// ˵�� ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::saveGroup()
{
    // ���� ���� ���� �������� 
    string szName(""), szDescription(""), szDepends(""), szCondition("");

    // ����
    bool bError = false;
    // ����
    szName  = m_pName->text();
    szName = strtriml(szName.c_str());
    szName = strtrimr(szName.c_str());
    if ( szName.empty() )
    { // ����Ϊ��
        // ��ʾ������Ϣ
        if(m_pNameHelp)
        {
            m_pNameHelp->setStyleClass("errors");
            m_pNameHelp->setText(SVResString::getResString("IDS_Group_Name_Error"));
            // ��ʾ����
            m_pNameHelp->show();
        }
        // ��ʾ������
        m_pGeneral->show();
        // ��������
        bError = true;
    }
    if(m_pAdvanced)
    {
        m_pAdvanced->getDescription(szDescription);
        m_pAdvanced->getDepend(szDepends);
        m_pAdvanced->getCodition(szCondition);
    }

    // ������������˳�����
    if(bError)
    {
        WebSession::js_af_up = "hiddenbar();";
        return;
    }


    // ������ذ�����Ϣ
    if(!m_bShowHelp)
        m_pNameHelp->hide();
    else
    {
        m_pNameHelp->setText(SVResString::getResString("IDS_Group_Name_Help"));
        m_pNameHelp->setStyleClass("helps");
    }


    //���õײ㺯���������ݣ��ɹ��󷵻���һ��ҳ�沢������ݷ��򷵻���һ��ҳ�档
    OBJECT groupobj = 0;


    // �Ƿ�������µ���
    if(m_szEditIndex.empty())
        groupobj = CreateGroup();
    else
        groupobj = GetGroup(m_szEditIndex, m_szIDCUser, m_szIDCPwd);

    // ����/���� �Ƿ� �ɹ�
    if (groupobj != INVALID_VALUE)
    {
        // �õ�������
        MAPNODE attr = GetGroupMainAttribNode(groupobj);
        // ״̬
        bool bState = false;
        if(attr != INVALID_VALUE)
        { // ������
            if(AddNodeAttrib(attr, "sv_name", szName) && AddNodeAttrib(attr, "sv_description", szDescription) &&
                AddNodeAttrib(attr, "sv_dependson", szDepends) && AddNodeAttrib(attr, "sv_dependscondition", szCondition))
            {
                bState = true;
            }
        }

        // ������Ϣȫ���ɹ����Ǵ����µ���
        if(bState && m_szEditIndex.empty())
        {
            // ��������
            if(!IsSVSEID(m_szParentIndex))
                saveDisableByParent(attr, Tree_GROUP, m_szParentIndex, m_szIDCUser, m_szIDCPwd);
            string szRealIndex = AddNewGroup(groupobj, m_szParentIndex, m_szIDCUser, m_szIDCPwd);

            // ������ɹ������������ɹ���Ϣ
            if(!szRealIndex.empty())
            {    
                int nIndex = FindIndexByID(szRealIndex);
                char szIndex[16] = {0};
                sprintf(szIndex, "%d", nIndex);
                AddNodeAttrib(attr, "sv_index", szIndex);
                if(m_pSVUser && !m_pSVUser->isAdmin())
                    m_pSVUser->AddUserScopeAllRight(szRealIndex, Tree_GROUP);
                emit addGroupName(szName, szRealIndex);
            }
		}
        else if (bState && !m_szEditIndex.empty())
        {// �༭��
            // �༭�ɹ� �����༭�ɹ���Ϣ

            if(SubmitGroup(groupobj, m_szIDCUser, m_szIDCPwd))
            {   
                emit editGroupName(szName,m_szEditIndex);

                if(m_pAdvanced->isDependChange())
                {
                    string szQueueName(getConfigTrackQueueName(m_szEditIndex));
                    CreateQueue(szQueueName, 1, m_szIDCUser, m_szIDCPwd);
                    if(!::PushMessage(szQueueName, "GROUP:UPDATE", m_szEditIndex.c_str(), static_cast<int>(m_szEditIndex.length()) + 1, m_szIDCUser, m_szIDCPwd))
                        PrintDebugString("PushMessage into " + szQueueName + " queue failed!");
                }
           }
        }
        // �ر���
        CloseGroup(groupobj);
    }

    // ������һ��ҳ��
    // �༭��ID Ϊ��
    m_szEditIndex = "";
    emit backMain();    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� backPreview
// ˵�� ������ҳ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::backPreview()
{
    m_szEditIndex = "";
    emit backMain();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showHelp
// ˵�� ��ʾ/���ذ�����Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::showHelp()
{
    m_bShowHelp = ! m_bShowHelp;
    m_pAdvanced->showHelp(m_bShowHelp);
    if (m_bShowHelp)
    {
        if(m_pNameHelp)
        {
            m_pNameHelp->setText(SVResString::getResString("IDS_Group_Name_Help"));
            m_pNameHelp->show();
        }
    }
    else
    {
        if(m_pNameHelp)
            m_pNameHelp->hide();
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� EditGroup
// ˵�� �����������༭��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::EditGroup(string &szIndex)
{
    // ������������
    ResetParam();
	if(m_pSave)
	{
        // ���ñ��水ť��ʾ����
		m_pSave->setText(SVResString::getResString("IDS_Save"));
        // tooltip
		m_pSave->setToolTip(SVResString::getResString("IDS_Save_Group_Tip"));
	}
    m_szEditIndex = szIndex;
    if(m_pAdvanced)
        m_pAdvanced->setUserID(FindSEID(m_szEditIndex));
    if (!m_szEditIndex.empty())
    {
        // ����
        OBJECT groupobj = GetGroup(m_szEditIndex, m_szIDCUser, m_szIDCPwd);
        if(groupobj != INVALID_VALUE)
        {// �ɹ�
            string szName(""), szDesc(""), szCondition(""), szDepends("");
            MAPNODE nodeobj =  GetGroupMainAttribNode(groupobj);
            if(nodeobj != INVALID_VALUE)
            {
                // ������
                FindNodeValue(nodeobj, "sv_name", szName);
                // ����
                FindNodeValue(nodeobj, "sv_description", szDesc);
                // ��������
                FindNodeValue(nodeobj, "sv_dependscondition", szCondition);
                // ����
                FindNodeValue(nodeobj, "sv_dependson", szDepends);
                if(m_pName)
                    m_pName->setText(szName); 
                if(m_pAdvanced)
                {
                    m_pAdvanced->setDescription(szDesc);
                    m_pAdvanced->setDepend(szDepends);
                    m_pAdvanced->setCodition(szCondition);
                }
            }
            // �ر���
            CloseGroup(groupobj);
        }
    }
    // ���� ������ ��ʾ����
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Edit_Group_Title"));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ResetParam
// ˵�� �������в�����ʾ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVAddGroup::ResetParam()
{
    // ���ñ༭
    m_szEditIndex = "";
    // ��������
    if(m_pName)
        m_pName->setText("");
    // ����������
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_Group_Title"));
	if(m_pSave)
	{
        // ���ñ��水ť��ʾ����
		m_pSave->setText(SVResString::getResString("IDS_Add"));
        // tooltip
		m_pSave->setToolTip(SVResString::getResString("IDS_Add_Group_Tip"));
	}
    // ���ø߼�����
    if(m_pAdvanced)
    {
        m_pAdvanced->setDescription(string(""));
        m_pAdvanced->resetDepend();
        m_pAdvanced->setCodition(string(""));
        m_pAdvanced->setUserID(FindSEID(m_szParentIndex));
    }
    // ���ذ���
    m_bShowHelp = true;
    showHelp();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
