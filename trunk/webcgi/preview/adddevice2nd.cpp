#include "adddevice2nd.h"
#include "../group/showtable.h"

#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../../base/des.h"
extern void PrintDebugString(const string& szMsg);
extern void PrintDebugString(const char *szMsg);
extern void WriteLogFile(const char *pszFile, const char *pszMsg);

#include "../base/basetype.h"

typedef bool(ListDevice)(const char* szQuery, char* szReturn, int &nSize);

#include "../group/resstring.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDevice::SVDevice(WContainerWidget * parent, CUser *pUser, string szIDCUser, string szIDCPwd, string szDeviceType):
WTable(parent)
{
    m_bShowHelp = false;                            // �Ƿ���ʾ����
    m_pGeneral = NULL;                              // ������Ϣ����
    m_pDeviceTitle = NULL;                          // �߼���Ϣ����
    m_pContentTable = NULL;                         // ���ݱ�
 
    m_pSubContent = NULL;                           // �����ݱ�
    m_pAdvTable = NULL;                             // �߼�������
    m_pSVUser = pUser;                              // ��ǰ�û�Ȩ��

    m_szIDCUser = szIDCUser;
    m_szIDCPwd = szIDCPwd;

    initForm();                                     // ��ʼ��
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumBaseParam
// ˵�� ö���豸ģ���ж���Ļ�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::enumBaseParam()
{
    // ����
    // ���豸ģ��
    OBJECT objDevice = GetEntityTemplet(m_szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// �ɹ�
        LISTITEM lsItem;
        // �õ�ÿ������
        if( FindETContrlFirst(objDevice, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                SVParamItem *param = new SVParamItem(objNode);
                m_lsBasicParam.push_back(param);
            }
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createGeneral
// ˵�� ������ʾ�������Եı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createGeneral()
{
    //�õ���ǰ���ݱ������
    int nRow = m_pSubContent->numRows();
    // �Ƿ��Ѵ����˱�
    if(m_pGeneral == NULL)
        m_pGeneral = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    if(m_pGeneral)
    {// �����ɹ�
        m_pGeneral->show();
        // ���ñ�������
        m_pGeneral->setTitle(SVResString::getResString("IDS_General_Title").c_str());
        list<SVParamItem*>::iterator lstItem;
        // �����ӱ�
        WTable *pSub = m_pGeneral->createSubTable();
        if(pSub)
        {
            // ѭ������ÿ�������еĿؼ�
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // �Ƿ��и���ֵ
                if((*lstItem)->isHasFollow())
                {
                    // �õ�����ֵ && ���ø���ֵ
                    string szFollow = (*lstItem)->getFollow();
                    if(!szFollow.empty())
                    {
                        list<SVParamItem*>::iterator ittmp ;
                        // ö��ÿ������
                        for(ittmp = m_lsBasicParam.begin(); ittmp != m_lsBasicParam.end(); ittmp ++)
                        {
                            // �Ƿ�ƥ��
                            if(strcmp(szFollow.c_str(), (*ittmp)->getName()) == 0)
                            {
                                (*lstItem)->setFollowItem((*ittmp));
                                break;
                            }
                        }
                    }
                }
                // �����ؼ�
                (*lstItem)->CreateControl(pSub);
                // �Ƿ��Ƕ�̬����
                if((*lstItem)->isDynamic())
                {
                    m_lsDyn.push_back((*lstItem));
                }
            }
            
            // �����豸����
            createHostName(pSub);
            // ö��ÿһ������
            for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            {
                // ���������Ƿ���_MachineName�����Ƿ���Ҫ���豸���ƶ�̬��
                if(strcmp((*lstItem)->getName(), "_MachineName") == 0 || (*lstItem)->isSynTitle())
                {
                    // ��̬��
                    if(m_pDeviceTitle != NULL && (*lstItem)->getControl() != NULL)
                    {
                        WInteractWidget* pEdit = (*lstItem)->getControl();
                        string szCmd = "onkeyup='Synchronization(\"" + pEdit->formName() +
                            "\",\"" + m_pDeviceTitle->formName() + "\")'";
                        strcpy(pEdit->contextmenu_, szCmd.c_str());
                    }
                }
                else if(strcmp((*lstItem)->getName(), "_ProtocolType") == 0 && (*lstItem)->getControl() != NULL)
                {// ���⴦��_ProtocolType
                    list<SVParamItem*>::iterator lsItem;
                    for(lsItem = m_lsBasicParam.begin(); lsItem != m_lsBasicParam.end(); lsItem ++)
                    {
                        if(strcmp((*lsItem)->getName(), "_Port") == 0 && (*lstItem)->getControl() != NULL)
                        {
                            string szCmd = "onchange='ChangePort(this.options[this.value].text ,\"" 
                                + (*lsItem)->getControl()->formName() + "\")'";
                            strcpy((*lstItem)->getControl()->contextmenu_, szCmd.c_str());
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createAdv
// ˵�� �����߼�������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createAdv()
{
    // �õ������ݱ�����
    int nRow = m_pSubContent->numRows();
    // �����������߼�������
    if(m_pAdvTable == NULL)
    m_pAdvTable = new SVDependTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));

    if(m_pAdvTable)
    {
        m_pAdvTable->setDescription(string(""));
        m_pAdvTable->resetDepend();
        m_pAdvTable->setCodition(string(""));
        m_pAdvTable->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createTitle
// ˵�� ����������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createTitle()
{
    // �õ���ǰ����
    int nRow = numRows();
    // ������
    m_pTitle = new WText("", (WContainerWidget*)elementAt(nRow, 0));
    // ���ô��е���ʾ��ʽ��
    elementAt(nRow,0)->setStyleClass("t1title");

    // ��һ��
    nRow ++;
    // ����һ���ӱ����ݱ�
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        // ����������
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            // ������ʽ��
            pScrollArea->setStyleClass("t1"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        // ���� ���ݱ� ��ʾ��ʽ
        m_pContentTable->setStyleClass("t1");
        // Cell Padding && Spaceing
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);
        // ���ô��е���ʾ��ʽ��
        elementAt(nRow, 0)->setStyleClass("t1");
        elementAt(nRow, 0)->setContentAlignment(AlignTop);
        
        // �õ����ݱ������
        nRow = m_pContentTable->numRows();
        // �����±������ݱ�
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        // �������ݱ�ǰ�еĶ��뷽ʽ
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� initForm
// ˵�� ��ʼ��ҳ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::initForm()
{
	setStyleClass("t1");
    // ����
    createTitle();

    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        createHelp();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createHelp
// ˵�� ����������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHelp()
{
	int nRow = m_pSubContent->numRows();

	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));

	nRow ++;

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

		//����
		WPushButton * pTranslate = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));	
		if(pTranslate)
		{
	        WObject::connect(pTranslate, SIGNAL(clicked()), this, SLOT(TranslateNew()));	
		    pTranslate->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
		}	

		new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)m_pSubContent->elementAt(nRow, 0));
	}

	// ����
    WImage * pHelp = new WImage("../icons/help.gif", (WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
    m_pSubContent->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
    if(pHelp)
    {
        pHelp->setStyleClass("imgbutton");
        pHelp->setToolTip(SVResString::getResString("IDS_Help"));
        WObject::connect(pHelp, SIGNAL(clicked()), this, SLOT(showHelp()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ExChange
// ˵�� ˢ�¿�Ч��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::ExChange()
{
	WebSession::js_af_up  = "setTimeout(\"location.href ='/fcgi-bin/preview.exe?type=0&preview=";
	WebSession::js_af_up += m_szDeviceType;
	WebSession::js_af_up += "'\",1250);  ";
	m_pAppSelf->quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Translate
// ˵�� ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::TranslateNew()
{
	string pTranPath = "DeviceMonitorTemplate$deviceid=";
	pTranPath += m_szDeviceType;
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += pTranPath;
	WebSession::js_af_up += "')";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� showHelp
// ˵�� ��ʾ�����ذ�����Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::showHelp()
{
    m_bShowHelp = !m_bShowHelp;

    list<SVParamItem *>::iterator lstItem;

    // ö��ÿһ������
    for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
    {
        (*lstItem)->m_bError = false;
        (*lstItem)->showHelp(m_bShowHelp); 
    }

    // �߼����Ա���ʾ/���ذ���
    m_pAdvTable->showHelp(m_bShowHelp);
    //
    if(m_pHostHelp)
    {
        if(m_bShowHelp)
            m_pHostHelp->show();
        else
            m_pHostHelp->hide();

        m_pHostHelp->setText(SVResString::getResString("IDS_Host_Label_Help"));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createHostName
// ˵�� �����豸����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::createHostName(WTable  * pTable)
{
    if(m_pDeviceTitle == NULL)
    {
        // �õ���ǰ����
        int nRow = pTable->numRows();
        // ˵��
        new WText(SVResString::getResString("IDS_Title"), (WContainerWidget*)pTable->elementAt(nRow, 0));
        // ���ӣ���ɫ*����ʶΪ������
        new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));

        // ������Ԫ���뷽ʽΪ���϶���
        pTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
        pTable->elementAt(nRow, 0)->setStyleClass("cell_10");

        // �������������
        m_pDeviceTitle = new WLineEdit("", (WContainerWidget*)pTable->elementAt(nRow, 1));
        if(m_pDeviceTitle)
            m_pDeviceTitle->setStyleClass("Cell_40");

        // ���������ı�
        new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));
        m_pHostHelp = new WText(SVResString::getResString("IDS_Host_Label_Help"), (WContainerWidget*)pTable->elementAt(nRow, 1));
        if(m_pHostHelp)
        {
            m_pHostHelp->hide();
            m_pHostHelp->setStyleClass("helps");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ClearData
// ˵�� ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::ClearData(string &szIndex, WApplication *szApp)
{
	m_pAppSelf = szApp;
    list<SVParamItem *>::iterator lstItem;
    if(!szIndex.empty())
    {// ��������ڱ༭�豸
        m_lsDyn.clear();
        // ɾ����ǰ����������
        for(lstItem = m_lsBasicParam.begin(); lstItem != m_lsBasicParam.end(); lstItem ++)
            delete (SVParamItem*)(*lstItem);
        m_lsBasicParam.clear();
        
        // ����������Ա��е���������
        if(m_pGeneral && m_pGeneral->createSubTable())
            m_pGeneral->createSubTable()->clear();

        m_pHostHelp = NULL;
        m_pDeviceTitle = NULL;

        // ����ʾ������Ϣ
        m_bShowHelp = false;
        // �豸��������
        m_szDeviceType = szIndex;

        // ö�ٻ�������
        enumBaseParam();
        createGeneral();
        createAdv();

        if(m_pSubContent) m_pSubContent->elementAt(0, 0)->show();

    }
    // 
    m_bShowHelp = true;
    showHelp();
    setTitle(m_szDeviceType);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� setTitle
// ˵�� �����豸�������ñ��� 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDevice::setTitle(string &szDeviceType)
{
    // ���豸ģ��
    OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {// �ɹ�
        // ���ڵ�
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szName("");
            // �豸���͵���ʾ����
            if(!FindNodeValue(node, "sv_label", szName))
                FindNodeValue(node, "sv_name", szName);
            else
                szName = SVResString::getResString(szName.c_str());

            m_pTitle->setText(SVResString::getResString("IDS_Add_Title") + " " + szName + " " +SVResString::getResString("IDS_Device"));
        }
        // �ر��豸ģ��
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
