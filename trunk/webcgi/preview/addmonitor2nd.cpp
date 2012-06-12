
#include "addmonitor2nd.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WRadioButton"
#include "../../opens/libwt/WLineEdit"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

extern void PrintDebugString(const char * szMsg);
extern void PrintDebugString(const string &szMsg);

extern void AddTaskList(WComboBox * pTask = 0);
extern bool SV_IsNumeric(string &szValue);

#include "../base/basetype.h"
#include "../../base/des.h"
#include "../group/resstring.h"
//#include "../base/OperateLog.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVMonitor::SVMonitor(WContainerWidget *parent, CUser *pUser, string szIDCUser, string szIDCPwd, int nMonitorID):
WTable(parent)
{
    m_bShowHelp = false;                    // ��ʾ/���ذ�����Ϣ
    m_pGeneral = NULL;                      // ��׼���Բ���
    m_pAdv = NULL;                          // �߼�����
    m_pCondition = NULL;                    // 
    m_pContentTable = NULL;                 // ��ֵ��
    m_pSubContent = NULL;                   // �����ݱ�
    m_nMonitorID = 0;                       // �����ģ�� ID

    m_pErrCond = NULL;                      // ����
    m_pWarnCond = NULL;                     // ����
    m_pGoodCond = NULL;                     // ����

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;
    m_pSVUser = pUser;

    //loadStrings();
    setStyleClass("t1");
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createAdvParam
// ˵�� �����߼����Ա�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createAdvParam()
{
    list<SVParamItem*>::iterator lstItem;
    int nRow = m_pSubContent->numRows();
    if(m_pAdv == NULL)
    {
        // �����±�
        m_pAdv = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    }
    if(m_pAdv)
    {
        // ���ñ��� ���߼�������
        m_pAdv->setTitle(SVResString::getResString("IDS_Advance_Option").c_str());

        // �����ӱ�
        WTable *pSub = m_pAdv->createSubTable();
        if(pSub)
        {// �����ӱ�ɹ�
            listItem it;
            // ö��ÿһ������
            for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
            {
                // �Ƿ��и���
                if((*it)->isHasFollow())
                {// �и���ֵ
                    // �õ�����ֵ
                    string szFollow = (*it)->getFollow();
                    if(!szFollow.empty())
                    {
                        listItem ittmp;
                        // ö��ÿ������
                        for(ittmp = m_lsAdvParam.begin(); ittmp != m_lsAdvParam.end(); ittmp ++)
                        {
                            // �Ƿ��Ǹ���ֵ
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                // ���ø���ֵ
                                (*it)->setFollowItem(*ittmp);
                                break;
                            }
                        }
                    }
                }
                // �����ؼ�
                (*it)->CreateControl(pSub);
                // �Ƿ�ʹ�ö�̬����
                if((*it)->isDynamic())
                {
                    m_lsDyn.push_back((*it));
                }
            }
            // �����߼������ļ����������Բ���
            createBaseAdv(pSub);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createBaseParam
// ˵�� �����������Բ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createBaseParam()
{
    list<SVParamItem*>::iterator lstItem;    
    int nRow = m_pSubContent->numRows();
    if(m_pGeneral == NULL)
    {
        // �����±�
        m_pGeneral = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    }
    if(m_pGeneral)
    {
        // ���ñ���
        m_pGeneral->setTitle(SVResString::getResString("IDS_Basic_Option").c_str());
        // �����ӱ�
        WTable *pSub = m_pGeneral->createSubTable();
        if(pSub)
        {// �ɹ������ӱ�
            // ��ʾ�豸����
            createDeviceName(pSub);
            listItem it;
            // ö��ÿ�����Բ���
            for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
            {
                // �Ƿ��и���ֵ
                if((*it)->isHasFollow())
                {// �и���ֵ
                    // �õ�����ֵ
                    string szFollow = (*it)->getFollow();
                    if(!szFollow.empty())
                    {// ����ֵ��Ϊ��
                        listItem ittmp ;
                        // ö��ÿһ�����Բ���
                        for(ittmp = m_lsBaseParam.begin(); ittmp != m_lsBaseParam.end(); ittmp ++)
                        {
                            // �Ƿ�ƥ��
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                // ���ø���ֵ
                                (*it)->setFollowItem((*ittmp));
                                break;
                            }
                        }
                    }
                }
                // �����ؼ�
                (*it)->CreateControl(pSub);
                // �Ƿ�ʹ�ö�̬����
                if((*it)->isDynamic())
                {
                    m_lsDyn.push_back((*it));
                }
            }
            // ���������
            createMonitorName(pSub);
        }        
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createConditionParam
// ˵�� ��ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createConditionParam()
{ 
    // �򿪼����ģ��
    m_objTemplate = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(m_objTemplate != INVALID_VALUE)
    {// �ɹ�
        // �õ������ݱ�ĵ�ǰ����
        int nRow = m_pSubContent->numRows();
        if(m_pCondition == NULL)
        {
            // �����±�
            m_pCondition = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
        }
        if(m_pCondition)
        {
            // ���ñ���
            m_pCondition->setTitle(SVResString::getResString("IDS_Alert_Condition_Title").c_str());
            // �����ӱ�
            WTable * pSub = m_pCondition->createSubTable();
            if(pSub)
            {// �����ӱ�ɹ�
                // �õ�����ֵ�ڵ�
                MAPNODE	objError = GetMTErrorAlertCondition(m_objTemplate);
                // ��ǰ����
                nRow = pSub->numRows(); 
                if(objError != INVALID_VALUE)
                {// 
                    // �����µ�����
                    if(m_pErrCond == NULL)
                        m_pErrCond = new SVConditionParam(pSub->elementAt(nRow, 0));
                    if(m_pErrCond)
                    {
                        m_pErrCond->SetReturnList(m_lsReturn);
                        m_pErrCond->SetMapNode(objError);
                    }
                }

                // ��ǰ������ 1
                nRow ++;
                // ���淧ֵ�ڵ�
                MAPNODE objAlert = GetMTWarningAlertCondition(m_objTemplate);
                if(objAlert != INVALID_VALUE)
                {
                    if(m_pWarnCond == NULL)
                        m_pWarnCond = new SVConditionParam(pSub->elementAt(nRow, 0));
                    if(m_pWarnCond)
                    {
                        m_pWarnCond->SetReturnList(m_lsReturn);
                        m_pWarnCond->SetMapNode(objAlert);
                    }
                }

                nRow ++;
                // ������ֵ�ڵ�
                MAPNODE	objGood = GetMTGoodAlertCondition(m_objTemplate);
                if(objGood != INVALID_VALUE)
                { 
                    if(m_pGoodCond == NULL)
                        m_pGoodCond = new SVConditionParam(pSub->elementAt(nRow, 0));
                    if(m_pGoodCond)
                    {
                        m_pGoodCond->SetReturnList(m_lsReturn);
                        m_pGoodCond->SetMapNode(objGood);
                    }
                }
            }
        }
        // �رռ����ģ��
        CloseMonitorTemplet(m_objTemplate);
    }   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createTitle
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createTitle()
{
    // �õ���ǰ����
    int nRow = numRows();
    // ������
    m_pTitle = new WText(SVResString::getResString("IDS_Add_Title"), (WContainerWidget*)elementAt(nRow, 0));
    // ���õ�ǰ����ʾ��ʽ
    elementAt(nRow, 0)->setStyleClass("t1title");

    // ��������1
    nRow ++;
    // �������ݱ�
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // ���õ�Ԫ���Padding && Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);
        
        // ����������
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t1"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t1"); 
        elementAt(nRow, 0)->setStyleClass("t1");
        elementAt(nRow,0)->setContentAlignment(AlignTop);

        // ���������ݱ�
        nRow = m_pContentTable->numRows();
        m_pSubContent = new WTable(m_pContentTable->elementAt(nRow,0));
        m_pContentTable->elementAt(nRow,0)->setContentAlignment(AlignTop);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumAdvParam
// ˵�� ö�ٸ߼����Բ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumAdvParam()
{
    LISTITEM lsItem;
    // �õ��߼����Բ�����һ���ڵ�
    if( FindMTAdvanceParameterFirst(m_objTemplate, lsItem))
    {
        // ö��ÿ���ڵ�
        MAPNODE objNode;
        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
        {
            SVParamItem *param = new SVParamItem(objNode);
            m_lsAdvParam.push_back(param);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createDeviceName
// ˵�� ��ʾ�豸����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createDeviceName(WTable  * pTable)
{
    // �õ��˱�ĵ�ǰ��
    int nRow = pTable->numRows();
    // ǰ��˵��
    new WText(SVResString::getResString("IDS_Device_Name"), (WContainerWidget*)pTable->elementAt(0, 0));
    pTable->elementAt(0, 0)->setStyleClass("cell_10");
    // �豸����
    m_pDeviceName = new WText("127.0.0.1", (WContainerWidget*)pTable->elementAt(0, 1));
    // ������ʽ
    if(m_pDeviceName)
        m_pDeviceName->setStyleClass("readonly");

    // ����
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(0, 1));
    // �����豸���ư����ı�
    WText * pDeviceHelp = new WText(SVResString::getResString("IDS_Device_Name_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pDeviceHelp)
    {
        pDeviceHelp->hide();
        pDeviceHelp->setStyleClass("helps");
        m_HelpMap[pDeviceHelp] = SVResString::getResString("IDS_Device_Name_Help");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createMonitorName
// ˵�� ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createMonitorName(WTable  * pTable)
{
    int nRow = pTable->numRows();

    // ��������Ʊ��⣨�����
    new WText(SVResString::getResString("IDS_Monitor_Label"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

    // ���������
    m_pMonitorName = new WLineEdit("", (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_pMonitorName)
        m_pMonitorName->setStyleClass("cell_40");

    // ����
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    // ��������ư���
    m_pMonitorHelp = new WText(SVResString::getResString("IDS_Monitor_Label_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_pMonitorHelp)
    {
        m_pMonitorHelp->hide();
        m_pMonitorHelp->setStyleClass("helps");
        m_HelpMap[m_pMonitorHelp] = SVResString::getResString("IDS_Monitor_Label_Help");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumBaseParam
// ˵�� ö�ٱ�׼����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumBaseParam()
{
    LISTITEM lsItem;
    // �õ���һ����׼���Բ���
    if( FindMTParameterFirst(m_objTemplate, lsItem))
    {
        MAPNODE objNode;
        // ö��ÿ������
        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
        {
            SVParamItem *param = new SVParamItem(objNode);
            m_lsBaseParam.push_back(param);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumReturnParam
// ˵�� ö�ٷ���ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::enumReturnParam()
{
    LISTITEM lsItem;
    // ö��ÿһ������ֵ
    if( FindMTReturnFirst(m_objTemplate, lsItem))
    {
        MAPNODE objNode;
        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
        {
            SVReturnItem *reItem = new SVReturnItem(objNode);
            m_lsReturn.push_back(reItem);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createHelp
// ˵�� ����������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createHelp()
{
    // �����ݱ�ǰ��
    int nRow = m_pSubContent->numRows();
    // ���� js �ļ�
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));

    nRow ++;
	// �Ƿ���ʾΪ����汾
    int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
 		//ˢ�¿�Ч��
		WPushButton * pRefresh = new WPushButton(SVResString::getResString("IDS_Refresh"), (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));	
		if(pRefresh)
		{
	        WObject::connect(pRefresh, SIGNAL(clicked()), this, SLOT(ExChange()));	
		    pRefresh->setToolTip(SVResString::getResString("IDS_Refresh_Tip"));
		}

		new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));

		// �������밴ť
	    m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	    if(m_pTranslateBtn)
	    {
            // �� click
		    connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
            // tooltip
		    m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
        }
	    new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	}

    // ������ť��ͼƬ��ť��
    WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    // ��ǰ��Ԫ����뷽ʽ ����
    m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
    if(pHelp)
    {
        // ������ʽ
        pHelp->setStyleClass("imgbutton");
        // tooltip
        pHelp->setToolTip(SVResString::getResString("IDS_Help"));
        // �� click
        WObject::connect(pHelp, SIGNAL(clicked()), this, SLOT(showHelpText()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ExChange
// ˵�� ˢ�¿�Ч��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::ExChange()
{
	char buf[256] = {"0"};
	itoa(m_nMonitorID,buf,10);
	string pMonitorID = buf; 

	WebSession::js_af_up  = "setTimeout(\"location.href ='/fcgi-bin/preview.exe?type=1&preview=";
	WebSession::js_af_up += pMonitorID;
	WebSession::js_af_up += "'\",1250);  ";
	m_pAppSelf->quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Translate
// ˵�� ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::Translate()
{
    string pTranPath = "DeviceMonitorTemplate$monitorid=";
	char buf[256] = {"0"};
	itoa(m_nMonitorID,buf,10);
	pTranPath += buf; 
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += pTranPath;
	WebSession::js_af_up += "')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createBaseAdv
// ˵�� �����߼������еļ����������Բ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::createBaseAdv(WTable *pTable)
{
    int nRow = pTable->numRows();

    // У�����
    new WText(SVResString::getResString("IDS_Check_Error"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // �Ƿ�У�����
    m_AdvList.m_pCheckErr = new WCheckBox("", (WContainerWidget*)pTable->elementAt(nRow, 1));
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    // �Ƿ�У��������
    WText * pCheckErrHelp = new WText(SVResString::getResString("IDS_Check_Err_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pCheckErrHelp)
    {
        pCheckErrHelp->hide();
        pCheckErrHelp->setStyleClass("helps");
        m_HelpMap[pCheckErrHelp] = SVResString::getResString("IDS_Check_Err_Help");
    }
    nRow += 1;

    // ����Ƶ��
    new WText(SVResString::getResString("IDS_Error_Freq"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // У�����Ƶ��
    m_AdvList.m_pMonitorFreq = new WLineEdit((WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pMonitorFreq)
        m_AdvList.m_pMonitorFreq->setStyleClass("cell_10");
    // У�����Ƶ��ʱ�䵥λ
    m_AdvList.m_pTimeUnit = new WComboBox((WContainerWidget*)pTable->elementAt(nRow, 1));    
    if(m_AdvList.m_pTimeUnit)
    {
        m_AdvList.m_pTimeUnit->addItem(SVResString::getResString("IDS_Minute"));
        m_AdvList.m_pTimeUnit->addItem(SVResString::getResString("IDS_Hour"));
    }
    // ������Ƶ�ʰ���
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    m_pFreqHelp = new WText(SVResString::getResString("IDS_Error_Freq_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_pFreqHelp)
    {
        m_pFreqHelp->hide();
        m_pFreqHelp->setStyleClass("helps");
        m_HelpMap[m_pFreqHelp] = SVResString::getResString("IDS_Error_Freq_Help");
    }
    nRow += 1;

    // ����ƻ�
    new WText(SVResString::getResString("IDS_Plan"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // ����ƻ�
    m_AdvList.m_pPlan = new WComboBox((WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pPlan)
    {
        m_AdvList.m_pPlan->setStyleClass("cell_40");
        AddTaskList(m_AdvList.m_pPlan);
    }
    // ����ƻ�����
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    WText * pPlanHelp = new WText(SVResString::getResString("IDS_PlanHelp"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pPlanHelp)
    {
        pPlanHelp->hide();
        pPlanHelp->setStyleClass("helps");
        m_HelpMap[pPlanHelp] = SVResString::getResString("IDS_PlanHelp");
    }
    nRow += 1;

    // ����
    new WText(SVResString::getResString("IDS_Monitor_Desc"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // ������Ϣ
    m_AdvList.m_pDescription = new WTextArea("",(WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pDescription )
        m_AdvList.m_pDescription->setStyleClass("cell_98");

    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    // ������Ϣ����
    WText *pDescHelp = new WText(SVResString::getResString("IDS_Monitor_Desc_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pDescHelp)
    {
        pDescHelp->hide();
        pDescHelp->setStyleClass("helps");
        m_HelpMap[pDescHelp] = SVResString::getResString("IDS_Monitor_Desc_Help");
    }
    nRow += 1;

    // ���������ı�
    new WText(SVResString::getResString("IDS_Report_Desc"), (WContainerWidget*)pTable->elementAt(nRow, 0));
    pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
    pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);

    // ��������
    m_AdvList.m_pReportDesc = new WTextArea("",(WContainerWidget*)pTable->elementAt(nRow, 1));
    if(m_AdvList.m_pReportDesc)
        m_AdvList.m_pReportDesc->setStyleClass("cell_98");
    // ������������
    new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
    WText * pReportHelp = new WText(SVResString::getResString("IDS_Report_Desc_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
    if(pReportHelp)
    {
        pReportHelp->hide();
        pReportHelp->setStyleClass("helps");
        m_HelpMap[pReportHelp] = SVResString::getResString("IDS_Report_Desc_Help");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initForm
// ˵�� ��ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::initForm()
{
    // ��������
    createTitle();
    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        // ��������
        createHelp();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showHelpText
// ˵�� ��ʾ/���ذ�����Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::showHelpText()
{
    m_bShowHelp = !m_bShowHelp;

    list<SVParamItem *>::iterator lstItem;

    //mapitem it;
    listItem it;
    // ö��ÿ���������Բ���
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
    {
        (*it)->m_bError = false;
        (*it)->showHelp(m_bShowHelp);
    }

    // ö�ٸ߼����Բ���
    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
    {
        (*it)->m_bError = false;
        (*it)->showHelp(m_bShowHelp);
    }

    // ����ֵ����
    if(m_pErrCond)
        m_pErrCond->showHelp(m_bShowHelp);

    // ���淧ֵ����
    if(m_pWarnCond)
        m_pWarnCond->showHelp(m_bShowHelp);

    // ������ֵ����
    if(m_pGoodCond)
        m_pGoodCond->showHelp(m_bShowHelp);

    if(m_bShowHelp)
    {
        // ��ʾÿ������
        for(m_helpItem = m_HelpMap.begin(); m_helpItem != m_HelpMap.end(); m_helpItem ++)
        {
            (*(m_helpItem->first)).show();
            (*(m_helpItem->first)).setText(m_helpItem->second);
        }
    }
    else
    {
        // ���ذ���
        for(m_helpItem = m_HelpMap.begin(); m_helpItem != m_HelpMap.end(); m_helpItem ++)
            (*(m_helpItem->first)).hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearBaseParam()
{
    listItem it;
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
    {
        (*it)->resetState();
        if(!(*it)->isDynamic())
            (*it)->setDefaultValue();
        else
            (*it)->clearDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearAdvParam()
{
    listItem it;
    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
    {
        (*it)->resetState();
        if(!(*it)->isDynamic())
            (*it)->setDefaultValue();
        else
            (*it)->clearDynData();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearConditionParam()
{
    OBJECT objMonitor = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE alertnode = GetMTErrorAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE && m_pErrCond)
            m_pErrCond->SetCondition(alertnode);

        alertnode = GetMTWarningAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE && m_pWarnCond)
            m_pWarnCond->SetCondition(alertnode);

        alertnode = GetMTGoodAlertCondition(objMonitor);
        if(alertnode != INVALID_VALUE && m_pGoodCond)
            m_pGoodCond->SetCondition(alertnode);

        CloseMonitorTemplet(objMonitor);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::showMonitorParam(int &nMTID, WApplication * szApp)
{    
    m_bContinueAdd = false;

    m_nMonitorID = nMTID;
	m_pAppSelf = szApp;

    clearData();

    m_objTemplate = GetMonitorTemplet(m_nMonitorID, m_szIDCUser, m_szIDCPwd);
    if(m_objTemplate != INVALID_VALUE)
    {
        MAPNODE objNode = GetMTMainAttribNode(m_objTemplate);
        if(objNode != INVALID_VALUE)
        {
            if(FindNodeValue(objNode, "sv_label", m_szMonitorName))
                m_szMonitorName = SVResString::getResString(m_szMonitorName.c_str());

            m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + m_szMonitorName + SVResString::getResString("IDS_Monitor_Title"));
        }
        enumAdvParam();
        enumBaseParam();
        enumReturnParam();

        CloseMonitorTemplet(m_objTemplate);
    }
    if(m_pSubContent)
    {
        // ����ѡ��
        createBaseParam();
        // ���������󡢾��桢������
        createConditionParam();
        // �߼�ѡ��
        createAdvParam();
    }
    m_szHostName = "127.0.0.1";
    if(m_pDeviceName)
        m_pDeviceName->setText(m_szHostName);

    if(m_pMonitorName)
        m_pMonitorName->setText(m_szMonitorName );// + ":" + szHost);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::clearData()
{
    list<SVParamItem*>::iterator lsItem;


    listItem it;
    for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
        delete (*it);

    for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
        delete (*it);

    list<SVReturnItem*>::iterator lsReItem;
    for(lsReItem = m_lsReturn.begin(); lsReItem != m_lsReturn.end(); lsReItem ++)
        delete (*lsReItem);

    m_lsBaseParam.clear();
    m_lsAdvParam.clear();

    m_lsReturn.clear();
    m_lsDyn.clear();

    if(m_pGeneral)
        m_pGeneral->createSubTable()->clear();
    if(m_pAdv)
        m_pAdv->createSubTable()->clear();
    m_HelpMap.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetAdvParam(OBJECT &objMonitor)
{
    list<SVParamItem*>::iterator lstItem;
    MAPNODE basenode = GetMonitorAdvanceParameterNode(objMonitor);
    if(basenode != INVALID_VALUE)
    {
        listItem it;
        for(it = m_lsAdvParam.begin(); it != m_lsAdvParam.end(); it ++)
        {
            string szValue (""), szName (""), szSaveName ("");;
            (*it)->getName(szName);
            szSaveName = (*it)->getSaveName();
            if(!szSaveName.empty())
                szName = szSaveName;
            if(!(*it)->getAccount().empty())
                szName += "1";
            FindNodeValue(basenode, szName, szValue);
            (*it)->setStringValue(szValue);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetBaseAdvParam(MAPNODE &mainnode)
{
    string szDesc (""), szReportDesc ("");
    string szPlan (""), szCheckErr ("");
    string szErrFreq (""), szErrFreqUnit ("");

    FindNodeValue(mainnode, "sv_description", szDesc);
    FindNodeValue(mainnode, "sv_reportdesc", szReportDesc);
    FindNodeValue(mainnode, "sv_plan", szPlan);
    FindNodeValue(mainnode, "sv_checkerr", szCheckErr);
    FindNodeValue(mainnode, "sv_errfreqsave", szErrFreq);
    FindNodeValue(mainnode, "sv_errfrequint", szErrFreqUnit);

    if(m_AdvList.m_pDescription)
        m_AdvList.m_pDescription->setText(szDesc);

    if(m_AdvList.m_pCheckErr)
    {
        if(szCheckErr == "true")
            m_AdvList.m_pCheckErr->setChecked(true);
        else
            m_AdvList.m_pCheckErr->setChecked(false);;
    }

    if(m_AdvList.m_pMonitorFreq)
        m_AdvList.m_pMonitorFreq->setText(szErrFreq);

    if(m_AdvList.m_pTimeUnit)
    {
        if(szErrFreqUnit == "1")
            m_AdvList.m_pTimeUnit->setCurrentIndexByStr(SVResString::getResString("IDS_Minute"));
        else
            m_AdvList.m_pTimeUnit->setCurrentIndexByStr(SVResString::getResString("IDS_Hour"));
    }

    if(m_AdvList.m_pPlan)
        m_AdvList.m_pPlan->setCurrentIndexByStr(szPlan);

    if(m_AdvList.m_pReportDesc)
        m_AdvList.m_pReportDesc->setText(szReportDesc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetBaseParam(OBJECT &objMonitor)
{
    list<SVParamItem*>::iterator lstItem;
    MAPNODE basenode = GetMonitorParameter(objMonitor);
    if(basenode != INVALID_VALUE)
    {
        listItem it;
        for(it = m_lsBaseParam.begin(); it != m_lsBaseParam.end(); it ++)
        {
            string szValue (""), szName (""), szSaveName ("");;
            (*it)->getName(szName);
            
            szSaveName = (*it)->getSaveName();
            if(!szSaveName.empty())
            {
                szName = szSaveName;
            }

            if(!(*it)->getAccount().empty())
                szName += "1";

            FindNodeValue(basenode, szName, szValue);
             (*it)->setStringValue(szValue);
        }
        SetBaseAdvParam(basenode);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 
// ˵�� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVMonitor::SetConditionParam(OBJECT &objMonitor)
{
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE && m_pErrCond)
        m_pErrCond->SetCondition(alertnode);

    alertnode = GetMonitorWarningAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE && m_pWarnCond)
        m_pWarnCond->SetCondition(alertnode);

    alertnode = GetMonitorGoodAlertCondition(objMonitor);
    if(alertnode != INVALID_VALUE && m_pGoodCond)
        m_pGoodCond->SetCondition(alertnode);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
