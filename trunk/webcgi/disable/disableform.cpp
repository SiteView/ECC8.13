#include "disableform.h"

#include "../../opens/libwt/WebSession.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"

extern void PrintDebugString(const char *szMsg);

extern int getDisableType(const char * szQuery);

extern int getDisableOperate(const char* szQuery);

void getSVID(int nDisableType, const char *szQuery, string &szSVID);

const char sv_disable_end[] = "DISABLE_END";

#define WTGET

SVDisableForm::SVDisableForm(WContainerWidget *parent, int nType, const char* szQueryString):
WTable(parent)
{
    m_pTemporaryDis = NULL;
    m_pTemporary = NULL;
    m_pDisableHelp = NULL;
    m_pHelp = NULL;
    m_pbtnDisable = NULL;
    m_pbtnClose   = NULL;
    m_pEnableMsg = NULL;
    m_nOperate = -1;
    m_pErrTip  = NULL;
    m_pDisTable = NULL;
    m_pConfirm = NULL;
    m_pConfirmTable = NULL;
	m_pConfirmTable = NULL;
	m_pPostion = NULL;
	PopTable = NULL;

    //    m_pHide = NULL;

    m_nDisableType = nType;
    if(szQueryString != NULL)
        m_szQueryString = szQueryString;

    m_szIDCUser = "default";
    m_szIDCPwd  = "localhost";
    m_szQueueName = "";

    m_bShowHelp = false;
    loadString();
    initForm();
}

void SVDisableForm::initForm()
{
/*	setStyleClass("t5"); 
    int nRow = numRows();
    new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", elementAt(nRow, 0));
    nRow ++;
    WTable *pContent = new WTable(elementAt(nRow, 0));
    if(pContent)
    {
        pContent->setCellPadding(0);
        pContent->setCellSpaceing(0);

        WScrollArea *pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(pContent);
        }
        elementAt(nRow, 0)->setStyleClass("t5");
        pContent->setStyleClass("t5");
        nRow = pContent->numRows();
        //WImage * pBusy = new WImage("", pContent->elementAt(nRow,0));
        //nRow ++;
        WTable *pSubContent = new WTable(pContent->elementAt(nRow,0));
        pContent->elementAt(nRow, 0)->setContentAlignment(AlignLeft | AlignTop);
        if(pSubContent)
        {
            nRow = pSubContent->numRows();
            pSubContent->setStyleClass("t8");
            m_pDisTable = new WTable(pSubContent->elementAt(nRow,0));
            if(m_pDisTable)
            {
                m_pDisTable->setStyleClass("t2");
                createTitle();
                createHelp();    
                createButtonGroup();
                createTemporary();
                createEnableMsg();
                createTipMsg();
                createOperate();
            }
            nRow ++;
            m_pConfirmTable = new WTable(pSubContent->elementAt(nRow, 0));
            if(m_pConfirmTable)
            {
                m_pConfirmTable->setStyleClass("t2");
                createConfirm();
            }
			
            nRow ++;
            WTable *pSub = new WTable(pSubContent->elementAt(nRow, 0));
            if(pSub)
            {
                pSub->setStyleClass("t9");
				//new WText("",(WContainerWidget*)pSub->elementAt(0, 0));
	


                m_pbtnCloseWnd = new WPushButton(m_szClose, (WContainerWidget*)pSub->elementAt(0, 0));
                if(m_pbtnCloseWnd)
                    WObject::connect(m_pbtnCloseWnd, SIGNAL(clicked()),  this, SLOT(cancel()));
                //pSub->elementAt(0, 0)->setContentAlignment(AlignTop | AlignRight);
                pSub->elementAt(0, 0)->setContentAlignment(AlignCenter);
            }
        }
    }
	pContent->hide();
*/
	this->clear();
	int nRow = numRows();
	new WText("\n<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", elementAt(nRow, 0));
	nRow ++;
	new WText("<div id='view_panel' class='panel_view'>", elementAt(nRow, 0));
	WTable * pContent = new WTable(elementAt(nRow, 0));
	if(pContent)
	{
		PopTable = new WSPopTable(pContent->elementAt(0, 0), true); 
		if (!PopTable)
		{
			return;
		}
		PopTable->AppendRows("");
		if (PopTable->pHelpImg)
		{
			WObject::connect(PopTable->pHelpImg, SIGNAL(clicked()), this, SLOT(ShowHelp()));
			m_pHelp = PopTable->pHelpImg;
		}
		m_pDisTable = PopTable->GeRowContentTable(0);
		if(m_pDisTable)
		{
			//createTitle();
			m_pTitle = PopTable->pTitleText;
			
			//createHelp();    
			createButtonGroup();
			createTemporary();
			createEnableMsg();
			createTipMsg();
			m_pDisTable = PopTable->GeRowActionTable(0);
			createOperate();
		}

		nRow = numRows();
		m_pConfirmTable = new WTable(pContent->elementAt(1, 0));
		if(m_pConfirmTable)
		{
			createConfirm();
		}
	}
	new WText("</div>", elementAt(nRow, 0));
	AddJsParam("uistyle", "viewpan", elementAt(nRow, 0));
	AddJsParam("fullstyle", "true", elementAt(nRow, 0));
	AddJsParam("bGeneral", "false", elementAt(nRow, 0));
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", elementAt(nRow, 0));

}

//添加客户端脚本变量
void SVDisableForm::AddJsParam(const std::string name, const std::string value, WContainerWidget * parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}

void SVDisableForm::loadString()
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{	
			FindNodeValue(ResNode,"IDS_Disable_Enable_Monitor",m_szTitle);
			FindNodeValue(ResNode,"IDS_Enable_Monitor",m_szEnableTitle);
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Group",m_szGroupEnableMsg);
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Device",m_szDeviceEnableMsg);
			FindNodeValue(ResNode,"IDS_Enable_Monitor_Group",m_szGroupDisableMsg);                                                                
			FindNodeValue(ResNode,"IDS_Enable_Monitor_Device",m_szDeviceDisableMsg);
			FindNodeValue(ResNode,"IDS_Enable_Monitor_If",m_szEnableMsg);
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Father_Group_Device",m_szErrTip);
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Forever",m_szForeverDis);
  			FindNodeValue(ResNode,"IDS_Disable_Monitor_Temp",m_szTemporaryDis);                                                                
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Description",m_szDisableDesc);
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Description_Help",m_szDisableDescHelp);
			FindNodeValue(ResNode,"IDS_From",m_szStart);
			FindNodeValue(ResNode,"IDS_Temp_Disable_Start_Time",m_szStartTimeHelp);                                                                  
			FindNodeValue(ResNode,"IDS_Temp_Disable_Start_Time_Error",m_szStartTimeTip);
			FindNodeValue(ResNode,"IDS_To",m_szEnd);
			FindNodeValue(ResNode,"IDS_Temp_Disable_End_Time",m_szEndTimeHelp);
			FindNodeValue(ResNode,"IDS_Temp_Disable_End_Time_Erro",m_szEndTimeTip);                                                                  
			FindNodeValue(ResNode,"IDS_End_Small_Start_Time",m_szEndTimeError);
			FindNodeValue(ResNode,"IDS_Disable_Monitor",m_szDisable);
			FindNodeValue(ResNode,"IDS_Enable_Monitor",m_szEnable);
			FindNodeValue(ResNode,"IDS_Cancel_Mid_Space",m_szCancel);
			FindNodeValue(ResNode,"IDS_Help",m_szHelpTip);
			FindNodeValue(ResNode,"IDS_Event_Confirm",m_szConfirmTitle);
			FindNodeValue(ResNode,"IDS_Affirm_Mid_Space",m_szConfirm);
			FindNodeValue(ResNode,"IDS_Close_Mid_Space",m_szClose);
			FindNodeValue(ResNode,"IDS_Affirm_Description",m_szConfirmDesc);
			FindNodeValue(ResNode,"IDS_Disable_Monitor_Successful",m_szDisableSucc);
			FindNodeValue(ResNode,"IDS_Event_Affirm_Successful",m_szConfirmSucc);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_Enable",m_szTypeEnable);
			FindNodeValue(ResNode,"IDS_Disable",m_szTypeDisable);
			FindNodeValue(ResNode,"IDS_Group",m_szOGroup);						
			FindNodeValue(ResNode,"IDS_Device",m_szODevice);						
			FindNodeValue(ResNode,"IDS_Monitor_Title",m_szOMonitor);				
			FindNodeValue(ResNode,"IDS_QueryLog",m_szQueryLog);				
			FindNodeValue(ResNode,"IDS_Affirm",strAffirm);
			FindNodeValue(ResNode,"IDS_Cancel1",strCancel);
		}
		CloseResource(objRes);
	}

 /*
	m_szTitle = " 禁止/允许监测"; 
    m_szEnableTitle = "启用监测";

    m_szGroupEnableMsg = "您选择的组目前处于启用状态，是否禁止监测 ？";
    m_szDeviceEnableMsg = "您选择的设备目前处于启用状态，是否禁止监测 ？";
    m_szGroupDisableMsg = "您选择的组目前处于禁止状态，是否启用监测 ？";
    m_szDeviceDisableMsg = "您选择的设备目前处于禁止状态，是否启用监测 ？";

    m_szEnableMsg = "是否启用监测？";

    m_szErrTip    = "因为父组/设备被禁止，所以不能启用监测。";
    m_szForeverDis = "永久禁止监测";
    m_szTemporaryDis = "临时禁止监测";
    m_szDisableDesc = "禁止监测描述";
    m_szDisableDescHelp = "禁止监测描述将显示在所有监测器状态栏中";
    m_szStart = "从";
    m_szStartTimeHelp = "临时禁止起始时间（前边输入框中输入时间，后边输入框输入日期）";
    m_szStartTimeTip = "临时禁止起始时间有误";
    m_szEnd = "到";
    m_szEndTimeHelp = "临时禁止终止时间（前边输入框中输入时间，后边输入框输入日期）";
    m_szEndTimeTip = "临时禁止终止时间有误";

    m_szEndTimeError = "结束时间小于开始时间！";

    m_szDisable = "禁止监测";
    m_szEnable = "启用监测";
    m_szCancel = "&nbsp;取&nbsp;&nbsp;消&nbsp;";

    m_szHelpTip = "帮助";
    m_szConfirmTitle = "事件确认";
    m_szConfirm = "&nbsp;确&nbsp;&nbsp;认&nbsp;";
    m_szClose = "&nbsp;关&nbsp;&nbsp;闭&nbsp;";
    m_szConfirmDesc = "确&nbsp;认&nbsp;描&nbsp;述&nbsp;";


    m_szDisableSucc = "禁止监测成功";
    m_szConfirmSucc = "事件确认操作成功";
*/
    m_szReturn = "";
}

void SVDisableForm::createConfirm()
{
    int nRow = m_pConfirmTable->numRows();
    //new WText(m_szConfirmTitle, m_pConfirmTable->elementAt(nRow, 0));
    //m_pConfirmTable->elementAt(nRow, 0)->setStyleClass("t1title");
    //nRow ++;
	PopTable = new WSPopTable(m_pConfirmTable->elementAt(nRow, 0)); 
	if (!PopTable)
	{
		return;
	}
	PopTable->AppendRows(m_szConfirmTitle);
	 WTable *pSub = PopTable->GeRowContentTable(0);
    if(!pSub)
	{
		return;
	}
        int nSubRow = pSub->numRows();
        new WText(m_szConfirmDesc, pSub->elementAt(nSubRow, 0));        
        m_pConfirm = new WLineEdit("", pSub->elementAt(nSubRow, 1));
        pSub->elementAt(nSubRow, 0)->setStyleClass("pop_table_item");
        pSub->elementAt(nSubRow, 1)->setStyleClass("pop_table_item_inp");
        m_pConfirm->setStyleClass("input_text");
    pSub = PopTable->GeRowActionTable(0);
	PopTable->GeRowActionTable(0)->setStyleClass("widthauto");

    {
		pSub->elementAt( 0, 0)->setStyleClass("padding_2");
		WSPopButton *pViewBtn = new WSPopButton(pSub->elementAt( 0, 0),  m_szQueryLog, "button_bg_m.png", "", false);
		//WPushButton *pViewBtn =  new WPushButton(m_szQueryLog, (WContainerWidget*)pSub->elementAt( 0, 0));
		if(pViewBtn)
		{
			
			connect(pViewBtn, SIGNAL(clicked()),this, SLOT(ViewLog()));
		}
		//WPushButton *pConfirm = new WPushButton(m_szConfirm, pSub->elementAt( 1, 0));
		pSub->elementAt( 0, 1)->setStyleClass("padding_2");
		WSPopButton *pConfirm = new WSPopButton(pSub->elementAt( 0, 1),  m_szConfirm, "button_bg_m.png", "", false);
		if(pConfirm)
			WObject::connect(pConfirm, SIGNAL(clicked()), this, SLOT(eventConfirm()));

    } 
}

void SVDisableForm::ViewLog()
{
	list<string>::iterator lsItem;
	string szMonitorID;
	for(lsItem = m_lsIndex.begin(); lsItem != m_lsIndex.end(); lsItem++)
	{
		szMonitorID = (*lsItem);
		OutputDebugString(szMonitorID.c_str());
		break;
	}
	std::string strJavascript;
	strJavascript = "window.open('/fcgi-bin/showlog.exe?monitorid="+   szMonitorID  +"')";	
	WebSession::js_af_up= strJavascript ;

}

//翻译后刷新
void SVDisableForm::ExChange()
{
	string strNRefresh = "setTimeout(\"location.href ='/fcgi-bin/disable.exe?";
	strNRefresh += strParam;
	strNRefresh += "'\",1250);  ";
	WebSession::js_af_up=strNRefresh;
	appSelf->quit();
}
//翻译
void SVDisableForm::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "disableRes";
	WebSession::js_af_up += "')";
}

void SVDisableForm::createTipMsg()
{
    int nRow = m_pDisTable->numRows();
    //WTable* pSub = new WTable(m_pDisTable->elementAt(nRow, 0));
    //if(pSub)
    {
        //pSub->setStyleClass("t8");
        //nRow = pSub->numRows();
        m_pErrTip = new WText(m_szErrTip, m_pDisTable->elementAt(nRow, 0));
		m_pDisTable->elementAt(nRow, 0)->setStyleClass("pop_table_item_inp");
		strcpy(m_pDisTable->elementAt(nRow, 0)->contextmenu_,"nowrap");
        if(m_pErrTip)
        {
            m_pErrTip->setStyleClass("table_error");
            m_pErrTip->hide();
        }
    }
}

void SVDisableForm::createHelp()
{
    int nRow = m_pDisTable->numRows();
    m_pHelp = new WImage("../Images/help.gif", (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    if(m_pHelp)
    {
        WObject::connect(m_pHelp, SIGNAL(clicked()), this, SLOT(ShowHelp()));
        m_pHelp->setToolTip(m_szHelpTip);
        m_pHelp->setStyleClass("imgbutton");
        //m_pHelp->hide();
    }
    m_pDisTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);    
}

void SVDisableForm::createOperate()
{
    int nRow = m_pDisTable->numRows();
	m_pDisTable->setStyleClass("widthauto");
    //m_pbtnDisable= new WPushButton(m_szDisable, (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
	m_pbtnDisable = new WSPopButton((WContainerWidget*)m_pDisTable->elementAt(nRow, 0), m_szDisable, "button_bg_m.png", "", false);
    if(m_pbtnDisable)
    {
        WObject::connect(m_pbtnDisable, SIGNAL(clicked()), "showbar();", this, SLOT(Disable()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        ///WObject::connect(pDisable, SIGNAL(clicked()),  "window.returnValue='IDOK';window.close();", WObject::ConnectionType::JAVASCRIPT);
    }

    //new WText("&nbsp;&nbsp;", (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));

    /*m_pPostion = new WText("&nbsp;&nbsp;", (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    if(m_pPostion)
        m_pPostion->hide();*/

   //m_pbtnClose = new WPushButton(m_szCancel, (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
	m_pbtnClose = new WSPopButton((WContainerWidget*)m_pDisTable->elementAt(nRow, 1), m_szCancel, "button_bg_m.png", "", false);
    if(m_pbtnClose)
    {
        WObject::connect(m_pbtnClose, SIGNAL(clicked()),  this, SLOT(cancel()));
        m_pbtnClose->hide();
    }

    //m_pPostion = new WText("&nbsp;&nbsp;", (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    //if(m_pPostion)
    //    m_pPostion->hide();
    /*
    m_pHide = new WPushButton(m_szCancel, (WContainerWidget*)elementAt(nRow, 0));
    if(m_pHide)
    {
    string szAlert = "alert('" + m_szEndTimeError + "')";
    WObject::connect(m_pHide, SIGNAL(clicked()),  szAlert.c_str(), WObject::ConnectionType::JAVASCRIPT);
    m_pHide->hide();
    }
    */
    //m_pDisTable->elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignRight);
}

void SVDisableForm::createButtonGroup()
{
	WButtonGroup *pbtnGroup = new WButtonGroup();
	int nRow = m_pDisTable->numRows();
	WTable *m_pButtonGroup = new WTable((WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    if (pbtnGroup)
    {

		m_pSelectType = new WText( "选择类型", (WContainerWidget*)m_pButtonGroup->elementAt(nRow, 0));
		m_pButtonGroup->elementAt(nRow, 0)->setStyleClass("pop_table_item");

		m_pButtonGroup->elementAt(nRow, 1)->setStyleClass("pop_table_item_inp");
        m_pForever = new WRadioButton(m_szForeverDis, (WContainerWidget*)m_pButtonGroup->elementAt(nRow, 1));
        if(m_pForever)
        {
            pbtnGroup->addButton(m_pForever);
            m_pForever->setChecked(); 
            //WObject::connect(m_pForever, SIGNAL(clicked()), this, SLOT(ShowHideTemporary()));
        }
		new WText( "&nbsp;&nbsp;", (WContainerWidget*)m_pButtonGroup->elementAt(nRow, 1));
        //nRow ++;
        m_pTemporaryDis = new WRadioButton(m_szTemporaryDis, (WContainerWidget*)m_pButtonGroup->elementAt(nRow, 1)); 
        if(m_pTemporaryDis)
        {
            pbtnGroup->addButton(m_pTemporaryDis);
            //WObject::connect(m_pTemporaryDis, SIGNAL(clicked()), this, SLOT(ShowHideTemporary()));
        }
    }
}

void SVDisableForm::createEnableMsg()
{
    int nRow = m_pDisTable->numRows();
	m_pDisTable->elementAt(nRow, 0)->setStyleClass("pop_table_item");
    m_pEnableMsg = new WText(m_szEnableMsg, (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    if(m_pEnableMsg)
        m_pEnableMsg->hide();
}

void SVDisableForm::createTemporary()
{
    int nRow = m_pDisTable->numRows();
    m_pTemporary = new WTable((WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    if(m_pTemporary)
    {
        int nSubRow = m_pTemporary->numRows();
        new WText(m_szDisableDesc, (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 0));
		m_pTemporary->elementAt(nSubRow, 0)->setStyleClass("pop_table_item");
       // m_pTemporary->elementAt(nSubRow, 0)->setContentAlignment(AlignTop | AlignLeft);
		//m_pTemporary->elementAt(nSubRow, 0)->resize(WLength( 100, WLength::Pixel),WLength( 0, WLength::Pixel));
       // m_pTemporary->elementAt(nSubRow, 0)->setStyleClass("cell_10");

        TTime ttime1 = TTime::GetCurrentTimeEx();
        TTime ttime2 = ttime1 + TTimeSpan(0, 2, 0, 0);

		m_pTemporary->elementAt(nSubRow, 1)->setStyleClass("pop_table_item_inp");
        m_pDisable = new WLineEdit("", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        if(m_pDisable)
            m_pDisable->setStyleClass("input_text");
        //new WText("<BR>", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
		nSubRow++;
        m_pDisableHelp = new WText(m_szDisableDescHelp, (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        if(m_pDisableHelp)
        {
            m_pTemporary->elementAt(nSubRow, 1)->setStyleClass("table_data_input_des");
            m_pDisableHelp->hide();
        }
        m_pTemporary->elementAt(nSubRow, 1)->setContentAlignment(AlignTop | AlignLeft);

        nSubRow ++;
        new WText(m_szStart, (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 0));
        m_pTemporary->elementAt(nSubRow, 0)->setContentAlignment(AlignTop | AlignLeft);
        m_pTemporary->elementAt(nSubRow, 0)->setStyleClass("pop_table_item");

        m_pStartTime = new WLineEdit("", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
		m_pTemporary->elementAt(nSubRow, 1)->setStyleClass("pop_table_item_inp");
        if(m_pStartTime)
		{
			m_pStartTime->setStyleClass("input_text_pop");
            char chStartTime[12] = {0};
            sprintf(chStartTime, "%d:%d", ttime1.GetHour(), ttime1.GetMinute());
            m_pStartTime->setText(chStartTime);
        }
        new WText("&nbsp;&nbsp;", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        m_pStartDay = new WLineEdit(" ", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        if(m_pStartDay)
        {
			m_pStartDay->setStyleClass("input_text_pop");

            char chStartDay[32] = {0};
            sprintf(chStartDay, "%d-%d-%d", ttime1.GetYear(), ttime1.GetMonth(), ttime1.GetDay());
            m_pStartDay->setText(chStartDay);
        }
        //new WText("<BR>", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
		nSubRow++;
        m_pStartTimeHelp = new WText(m_szStartTimeHelp, (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        if(m_pStartTimeHelp)
        {
            m_pTemporary->elementAt(nSubRow, 1)->setStyleClass("table_data_input_des");
            m_pStartTimeHelp->hide();
        }
        elementAt(nSubRow, 1)->setContentAlignment(AlignTop | AlignLeft);

        nSubRow ++;
        new WText(m_szEnd, (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 0));
        m_pTemporary->elementAt(nSubRow, 0)->setContentAlignment(AlignTop | AlignLeft);
        m_pTemporary->elementAt(nSubRow, 0)->setStyleClass("pop_table_item");

        m_pEndTime = new WLineEdit("", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
		m_pTemporary->elementAt(nSubRow, 1)->setStyleClass("pop_table_item_inp");
        if(m_pEndTime)
        {
			m_pEndTime->setStyleClass("input_text_pop");
            char chEndTime[12] = {0};
            sprintf(chEndTime, "%d:%d", ttime2.GetHour(), ttime2.GetMinute());
            m_pEndTime->setText(chEndTime);
        }
        new WText("&nbsp;&nbsp;", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        m_pEndDay = new WLineEdit(" ", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        //new WText("<BR>", (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
		nSubRow++;
        m_pEndTimeHelp = new WText(m_szEndTimeHelp, (WContainerWidget*)m_pTemporary->elementAt(nSubRow, 1));
        if(m_pEndDay)
        {
			m_pEndDay->setStyleClass("input_text_pop");

            char chEndDay[32] = {0};
            sprintf(chEndDay, "%d-%d-%d", ttime2.GetYear(), ttime2.GetMonth(), ttime2.GetDay());
            m_pEndDay->setText(chEndDay);
        }
        if(m_pEndTimeHelp)
        {
            m_pTemporary->elementAt(nSubRow, 1)->setStyleClass("table_data_input_des");
            m_pEndTimeHelp->hide();
        }
        m_pTemporary->elementAt(nSubRow, 1)->setContentAlignment(AlignTop | AlignLeft);

        //m_pTemporary->hide();
    }
}

void SVDisableForm::createTitle()
{
    int nRow = m_pDisTable->numRows();
    //m_pTitle = new WText(m_szTitle, (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
    //m_pDisTable->elementAt(nRow, 0)->setStyleClass("t1title");

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));

	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
	connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
    pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;",(WContainerWidget*)m_pDisTable->elementAt(nRow, 0));

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget*)m_pDisTable->elementAt(nRow, 0));
	connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}

}

void SVDisableForm::ShowHideTemporary()
{
    //if(m_pTemporaryDis)
    {
        //if(m_pTemporaryDis->isChecked())
        {
            //if(m_pTemporary)
            //    m_pTemporary->show();
            //if(m_pHelp)
            //    m_pHelp->show();

            TTime ttime1 = TTime::GetCurrentTimeEx();
            TTime ttime2 = ttime1 + TTimeSpan(0, 2, 0, 0);
            if(!m_szEndTime.empty() && !m_szStartTime.empty())
            {
                int nYear = 0, nMonth = 0, nDay = 0;
                int nHour = 0, nMinute = 0;
                sscanf(m_szStartTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                ttime1 = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                ttime2 = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
            }
            if(m_pStartTime)
            {
                char chStartTime[12] = {0};
                sprintf(chStartTime, "%02d:%02d", ttime1.GetHour(), ttime1.GetMinute());
                m_pStartTime->setText(chStartTime);
            }
            if(m_pStartDay)
            {
                char chStartDay[32] = {0};
                sprintf(chStartDay, "%04d-%02d-%02d", ttime1.GetYear(), ttime1.GetMonth(), ttime1.GetDay());
                m_pStartDay->setText(chStartDay);
            }
            if(m_pEndTime)
            {
                char chEndTime[12] = {0};
                sprintf(chEndTime, "%02d:%02d", ttime2.GetHour(), ttime2.GetMinute());
                m_pEndTime->setText(chEndTime);
            }
            if(m_pEndDay)
            {
                char chEndDay[32] = {0};
                sprintf(chEndDay, "%04d-%02d-%02d", ttime2.GetYear(), ttime2.GetMonth(), ttime2.GetDay());
                m_pEndDay->setText(chEndDay);
            }
        }
        //else
        //{
        //    //if(m_pTemporary)
        //    //    m_pTemporary->hide();
        //    //if(m_pHelp)
        //    //    m_pHelp->hide();
        //}
    }
}

bool SVDisableForm::checkTime(string &szTime, string &szDay)
{
    bool bError = false;
    int nHours = -1, nMins = -1, nYear = -1, nDay = -1, nMon = -1;
    sscanf(szTime.c_str(), "%d : %d", &nHours, &nMins);
    sscanf(szDay.c_str(), "%d - %d - %d", &nYear, &nMon, &nDay);

    if(nHours < 0 || nHours > 23)
        bError = true;
    if(nMins < 0 || nMins > 59 )
        bError = true; 
    if(nMon < 0 || nMon > 12)
        bError = true;
    if(nMon % 2 == 0)
    {
        if( nMon == 2)
        {
            if(nDay < 0 || nDay > 29)
                bError = true;
        }
        else
        {
            if(nDay < 0 || nDay > 31)
                bError = true;
        }
    }
    else
    {
        if(nDay < 0 || nDay > 31)
            bError = true;
    }

    TTime ttime = TTime::GetCurrentTimeEx();

    if(nYear < ttime.GetYear())
        bError = true;

    return bError;
}

bool SVDisableForm::checkEndTime()
{
    bool bError = false;
    string szEndTime = "", szEndDay = "";

    szEndTime = m_pEndTime->text();
    szEndDay = m_pEndDay->text();
    if(!szEndTime.empty() && !szEndDay.empty())
    {
        bError = checkTime(szEndTime, szEndDay);
    }
    else
        bError = true;

    if(bError)
    {
        if(m_pEndTimeHelp)
        {
            m_pEndTimeHelp->setText(m_szEndTimeTip);
            m_pEndTimeHelp->show();
        }
    }
    else
    {
        int nHours = -1, nMins = -1, nYear = -1, nDay = -1, nMon = -1;
        sscanf(szEndTime.c_str(), "%d : %d", &nHours, &nMins);
        sscanf(szEndDay.c_str(), "%d - %d - %d", &nYear, &nMon, &nDay);
        m_tEnd = TTime(nYear, nMon, nDay, nHours, nMins, 0);
        if(m_bShowHelp)
        {
            if(m_pEndTimeHelp)
                m_pEndTimeHelp->setText(m_szEndTimeHelp);
        }
        else
        {
            if(m_pEndTimeHelp)
                m_pEndTimeHelp->hide();
        }
    }
    return bError;
}

bool SVDisableForm::checkStartTime()
{
    bool bError = false;
    string szStartTime = "", szStartDay = "";

    szStartTime = m_pStartTime->text();
    szStartDay = m_pStartDay->text();
    if(!szStartTime.empty() && !szStartDay.empty())
    {
        bError = checkTime(szStartTime, szStartDay);
    }
    else
        bError = true;

    if(bError)
    {
        if(m_pStartTimeHelp)
        {
            m_pStartTimeHelp->setText(m_szStartTimeTip);
            m_pStartTimeHelp->show();
        } 
    }
    else
    {
        int nHours = -1, nMins = -1, nYear = -1, nDay = -1, nMon = -1;
        sscanf(szStartTime.c_str(), "%d : %d", &nHours, &nMins);
        sscanf(szStartDay.c_str(), "%d - %d - %d", &nYear, &nMon, &nDay);
        m_tStart = TTime(nYear, nMon, nDay, nHours, nMins, 0);
        if(m_bShowHelp)
        {    
            if(m_pStartTimeHelp)
                m_pStartTimeHelp->setText(m_szEndTimeHelp);
        }
        else
        {
            if(m_pStartTimeHelp)
                m_pStartTimeHelp->hide();
        }
    }
    return bError;
}

void SVDisableForm::saveAttribByNode(MAPNODE &node)
{
    string szStartTime = "", szStartDay = "";
    string szEndTime = "", szEndDay = "";
    string szDisableDesc = "";

    szStartTime = m_pStartTime->text();
    szStartDay = m_pStartDay->text();
    szStartTime = szStartDay + "-" + szStartTime;
    szEndTime = m_pEndTime->text();
    szEndDay = m_pEndDay->text();
    szEndTime = szEndDay + "-" +szEndTime;
    szDisableDesc = m_pDisable->text();


    bool bForever = false;
    AddNodeAttrib(node, "sv_disabledesc", szDisableDesc);
    if(m_pForever) bForever = m_pForever->isChecked();
    if(!bForever)
    {
        AddNodeAttrib(node, "sv_disable", "time");
        AddNodeAttrib(node, "sv_starttime", szStartTime);
        //AddNodeAttrib(node, "sv_startday", szStartDay);
        AddNodeAttrib(node, "sv_endtime", szEndTime);
        //AddNodeAttrib(node, "sv_endday", szEndDay);
    }
    else
    {
        AddNodeAttrib(node, "sv_disable", "true");
    }
}

void SVDisableForm::Disable()
{   
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Disable";
	LogItem.sHitFunc = "Disable";
	LogItem.sDesc = strAffirm;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	string szOName("");
    m_lsMonitors.clear();
    //if(m_pbtnClose) m_pbtnClose->setEnabled(false);
    //if(m_pbtnDisable) m_pbtnDisable->setEnabled(false);
    if(m_nOperate == 1 )
    {
        PrintDebugString("enable");
        list<string>::iterator lstItem;

        for(lstItem = m_lsIndex.begin();lstItem != m_lsIndex.end(); lstItem++)
        {
            string szIndex = (*lstItem);
            //PrintDebugString(szIndex.c_str());
            switch(m_nDisableType)
            {
            case sv_group:
                EnableGroup(szIndex);
				m_szOName = m_szOGroup;
                break;
            case sv_device:
                EnableDevice(szIndex);       
				m_szOName = m_szODevice;
                break;
            case sv_monitor:
                //PrintDebugString("enable monitor");
                EnableMonitor(szIndex);
 				m_szOName = m_szOMonitor;
				szOName += m_szDeviceName;
				szOName += ":";
               break;
            }  
			szOName += m_szONameTemp;
			szOName += "  ";
        }
		m_szOType = m_szTypeEnable;
    }
    else
    {

        if(m_pTemporaryDis->isChecked())
        {
            bool bStartErr = checkStartTime();
            bool bEndErr = checkEndTime();
            if(bEndErr || bStartErr)
			{
				WebSession::js_af_up = "hiddenbar()";
				bEnd = true;	
				goto OPEnd;
			}
            if(m_tEnd < m_tStart)
            {
                if(m_pEndTimeHelp)
                {
                    m_pEndTimeHelp->setText(m_szEndTimeError);
                    m_pEndTimeHelp->show();
				}
				WebSession::js_af_up = "hiddenbar()";
				bEnd = true;	
				goto OPEnd;
            }
            else
            {
                if(m_bShowHelp)
                {
                    if(m_pEndTimeHelp)
                        m_pEndTimeHelp->setText(m_szEndTimeHelp);
                }
                else
                {
                    if(m_pEndTimeHelp)
                        m_pEndTimeHelp->hide();
                }
            }
        }

        list<string>::iterator lstItem;
        for(lstItem = m_lsIndex.begin();lstItem != m_lsIndex.end(); lstItem++)
        {
            OBJECT objSV; 
            MAPNODE mainnode = INVALID_VALUE;
            //PrintDebugString(m_szQueryString.c_str());
            string szIndex = (*lstItem);
            //PrintDebugString()
            switch(m_nDisableType)
            {
            case sv_group:
                //PrintDebugString("Open Group!");
                DisableGroup(szIndex);
                objSV = GetGroup(szIndex);
                if(objSV != INVALID_VALUE)
                {   
                    mainnode = GetGroupMainAttribNode(objSV);

                    if(mainnode != INVALID_VALUE)
                        saveAttribByNode(mainnode);
                    SubmitGroup(objSV);
                    CloseGroup(objSV);
                }
				m_szOName = m_szOGroup;
                break;
            case sv_device:
                //PrintDebugString("Open Entity!");
                DisableDevice(szIndex);
                objSV = GetEntity(szIndex);
                if(objSV != INVALID_VALUE)
                {
                    //PrintDebugString("open entity succ");
                    mainnode = GetEntityMainAttribNode(objSV);
                    if(mainnode != INVALID_VALUE)
                        saveAttribByNode(mainnode);
                    SubmitEntity(objSV);
                    CloseEntity(objSV);
                }       
				m_szOName = m_szODevice;
                break;
            case sv_monitor:
                DisableMonitor(szIndex);
				m_szOName = m_szOMonitor;
 				szOName += m_szDeviceName;
				szOName += ":";
               break;
            }
			szOName += m_szONameTemp;
 			szOName += "  ";
       } 
		m_szOType = m_szTypeDisable;
    }

    list<string>::iterator lsItem;
    for(lsItem = m_lsMonitors.begin(); lsItem != m_lsMonitors.end(); lsItem++)
    {
        string szMonitorID = (*lsItem);
        if(!szMonitorID.empty())
        {
            if(m_nOperate == 1)
                SetDYN(szMonitorID, 0, m_szIDCUser, m_szIDCPwd);
            else if(m_pForever->isChecked())
                SetDYN(szMonitorID, 4, m_szIDCUser, m_szIDCPwd);
        }
    }
    if(m_pbtnClose->isHidden())
    {
        m_szReturn = "window.returnValue='IDOK';";
        WebSession::js_af_up = "hiddenbar();showAlertMsg(\""+ m_szDisableSucc + "\");";
    }
    else
        WebSession::js_af_up = "hiddenbar();window.returnValue='IDOK';window.close();";
    //PrintDebugString(WebSession::js_af_up.c_str());
    //appl->quit();

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_szOType,m_szOName,szOName);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void SVDisableForm::ShowHelp()
{
    m_bShowHelp = !m_bShowHelp;
    if(m_bShowHelp)
    {
        if(m_pDisableHelp)
            m_pDisableHelp->show();
        if(m_pStartTimeHelp)
        {
            m_pStartTimeHelp->setText(m_szStartTimeHelp);
            m_pStartTimeHelp->show();
        }
        if(m_pEndTimeHelp)
        {
            m_pEndTimeHelp->setText(m_szEndTimeHelp);
            m_pEndTimeHelp->show();
        }
    }
    else
    {
        if(m_pDisableHelp)
            m_pDisableHelp->hide();
        if(m_pStartTimeHelp)
            m_pStartTimeHelp->hide();
        if(m_pEndTimeHelp)
            m_pEndTimeHelp->hide();
    }
}

void SVDisableForm::refresh()
{
	OutputDebugString("\n--------------------refresh------------------------\n");
	initForm();
    if(m_pErrTip)           m_pErrTip->hide();
    //if(m_pbtnClose)         m_pbtnClose->setEnabled(true);
	if(m_pbtnDisable)       m_pbtnDisable->setEnabled(true);
    if(m_pForever)          m_pForever->setChecked();
    if(m_pTemporaryDis)     m_pTemporaryDis->setUnChecked();
    if(m_pDisable)          m_pDisable->setText("");

    if(!m_szQueueName.empty())
    {
        DeleteQueue(m_szQueueName);
        m_szQueueName = "";
    }

    m_bShowHelp = true;
    m_szReturn = "";
    m_szEndTime = "";
    m_szStartTime = "";
    ShowHideTemporary();
    ShowHelp();

    m_lsMonitors.clear();

    m_nOperate = -1;
    m_lsIndex.clear();

    char szQuery[4096]={0};
    int nSize =4095;
#ifdef WTGET
    GetEnvironmentVariable( "QUERY_STRING", szQuery,nSize);
#else
	char *tmpquery = getenv("QUERY_STRING");
	if(tmpquery)
		strcpy(szQuery,tmpquery);
#endif
	strParam = szQuery;
    if(szQuery)
        m_nDisableType = getDisableType(szQuery);
    if (m_nDisableType >= 0 && m_nDisableType <= 2)
        getSVID(m_nDisableType, szQuery, m_szQueryString);

    PrintDebugString(szQuery);
    m_nOperate = getDisableOperate(szQuery);
    char *pPos= strstr(szQuery, "queuename=");
    if(pPos)
    {
        char szQueue[32] = {0};
        sscanf(pPos, "queuename= %[0-9]", szQueue);
        m_szQueueName = szQueue;
        
        string label;
	    svutil::TTime ct;
	    unsigned int len=0;
        if(!m_szQueueName.empty())
        {
            while(label.compare(sv_disable_end) != 0)
            {
                PrintDebugString("Disable: pop message");
                MQRECORD mrd = PopMessage(m_szQueueName, 5000);
                if(mrd != INVALID_VALUE)
	            {	          
                    if(GetMessageData(mrd, label, ct, NULL, len))
                    {
                        if(label == "SV_INDEX")
                        {
                            char * pszBuffer = new char[len];
                            if(pszBuffer)
                            {
	                            if(::GetMessageData(mrd, label, ct, pszBuffer, len))
                                    m_lsIndex.push_back(pszBuffer);
                                PrintDebugString(pszBuffer);
                                delete []pszBuffer;
                            }
                        }
                    }
                }
	        }
            DeleteQueue(m_szQueueName);
            m_szQueueName = "";
        }
    }
    else
    {
        int nPos = m_szQueryString.find(",");
        if(nPos > 0)
            ParserQueryString(m_szQueryString); 
        else
            m_lsIndex.push_back(m_szQueryString);
    }

    list<string>::iterator lstItem;
    if(m_nOperate == 3 || m_nOperate == 1)
    {
        for(lstItem = m_lsIndex.begin(); lstItem != m_lsIndex.end(); lstItem ++)
        {
            string szIndex = (*lstItem);
			OutputDebugString(szIndex.c_str());
            string szParent = FindParentID(szIndex);
            if(!szParent.empty())
            {
                if(isDisable(szIndex) != 0)
                {
                    PrintDebugString("disable/enable; this is disable");
                    if(isParentDisable(szParent) != 0)
                    {
                        if(m_pForever)          m_pForever->hide();
						if(m_pSelectType)		m_pSelectType->hide();
                        if(m_pTemporaryDis)     m_pTemporaryDis->hide();
                        if(m_pTitle)            m_pTitle->setText(m_szEnableTitle);
                        if(m_pEnableMsg)        m_pEnableMsg->hide();
                        if(m_pErrTip)           m_pErrTip->show();
                        if(m_pbtnDisable)
                        {
							m_pbtnDisable->setText(m_szEnable);
							m_pbtnDisable->setEnabled(false);
                        }
                        return;
                    }
                    PrintDebugString("enable operate");
                    m_nOperate = 1;
                }
                else
                {
                    PrintDebugString("disable operate");
                    m_nOperate = 0;
                    break;
                }
            }
        }

    }
    if(m_pConfirmTable) m_pConfirmTable->hide();
    if(m_pbtnClose)     m_pbtnClose->show();
    //if(m_pPostion)      m_pPostion->show();
    //if(m_pbtnCloseWnd)  m_pbtnCloseWnd->hide();

    if(m_lsIndex.size() <= 1 && m_nDisableType == sv_monitor)
    {
        //判断监测器是否需要确认
        if(showConfirmTable())
        {

            if(m_pConfirmTable) m_pConfirmTable->show();
            if(m_pbtnClose)     m_pbtnClose->hide();
            //if(m_pPostion)      m_pPostion->hide();
            //if(m_pbtnCloseWnd)  m_pbtnCloseWnd->show();
        }
    }

    if(m_nOperate == 1)
    {
        if(m_pTemporary)        m_pTemporary->hide();
        if(m_pForever)          m_pForever->hide();
		if(m_pSelectType)		m_pSelectType->hide();
        if(m_pHelp)             m_pHelp->hide();
        if(m_pTemporaryDis)     m_pTemporaryDis->hide();
		if(m_pbtnDisable)       m_pbtnDisable->setText(m_szEnable);
        if(m_pTitle)            m_pTitle->setText(m_szEnableTitle);
        if(m_pEnableMsg )       m_pEnableMsg->show();
        if(m_pErrTip)           m_pErrTip->hide();
    }
    else
    {
        if(m_pTemporary)    m_pTemporary->show();
        if(m_pHelp)         m_pHelp->show();
        if(m_pForever)          m_pForever->show();
		if(m_pSelectType)		m_pSelectType->show();
        if(m_pTemporaryDis)     m_pTemporaryDis->show();
        if(m_pbtnDisable)       m_pbtnDisable->setText(m_szDisable);
        if(m_pTitle)            m_pTitle->setText(m_szTitle);
        if(m_pEnableMsg)        m_pEnableMsg->hide();

        if(!m_szEndTime.empty() && !m_szStartTime.empty())
            this->m_pTemporaryDis->setChecked(true);
    }

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	/*if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}
	*/
}

void SVDisableForm::DisableGroup(string &szGroupID)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    if(!szGroupID.empty())
    {
        OBJECT group = GetGroup(szGroupID);
        if(group != INVALID_VALUE)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    DisableDevice(szEntityID);      
                }            
            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    DisableGroup(szSubGroupID);      
                }                
            }
            MAPNODE mainnode = GetGroupMainAttribNode(group);
            if(mainnode != INVALID_VALUE)
            {
	            FindNodeValue(mainnode, "sv_name", m_szONameTemp);
                //AddNodeAttrib(mainnode, "sv_disable", "true");
                saveAttribByNode(mainnode);
            }
            SubmitGroup(group);
            CloseGroup(group);
            //DeleteGroup(szIndex, m_szIDCUser, m_szIDCPwd); 
        }  
    }
}

void SVDisableForm::DisableDevice(string &szDeviceID)
{
    list<string> lstMonitors;
    list<string>::iterator lstItem;
    if(!szDeviceID.empty())
    {
        //PrintDebugString(szDeviceID.c_str());
        OBJECT entity = GetEntity(szDeviceID);
        if (entity != INVALID_VALUE)
        {
            if(GetSubMonitorsIDByEntity(entity, lstMonitors))
            {
                for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                {
                    string szMonitorID = (*lstItem).c_str();
                    DisableMonitor(szMonitorID);
                    //DeleteSVMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
                }
            }
            MAPNODE mainnode = GetEntityMainAttribNode(entity);
            if(mainnode != INVALID_VALUE)
            {
	            FindNodeValue(mainnode, "sv_name", m_szONameTemp);
                //AddNodeAttrib(mainnode, "sv_disable", "true");
                saveAttribByNode(mainnode);
            }
        }
        SubmitEntity(entity);
        CloseEntity(entity);
        //DeleteEntity(szIndex, m_szIDCUser, m_szIDCPwd);
    }
}

void SVDisableForm::DisableMonitor(string &szMonitorID)
{
    OBJECT objSV = GetMonitor(szMonitorID);
    if(objSV != INVALID_VALUE)
    {
        MAPNODE mainnode = GetMonitorMainAttribNode(objSV);
        if(mainnode != INVALID_VALUE)
        {
            FindNodeValue(mainnode, "sv_name", m_szONameTemp);
            //AddNodeAttrib(mainnode, "sv_disable", "true");
            saveAttribByNode(mainnode);
        }
        SubmitMonitor(objSV);
        CloseMonitor(objSV);
    }
    m_lsMonitors.push_back(szMonitorID);

	//获取设备的名称
	string szDeviceID("");
	szDeviceID = FindParentID(szMonitorID);
    OBJECT objEntity = GetEntity(szDeviceID);
    if(objEntity != INVALID_VALUE)
    {
        MAPNODE devnode = GetEntityMainAttribNode(objEntity);
        if(devnode != INVALID_VALUE)
        {
            FindNodeValue(devnode, "sv_name", m_szDeviceName);
        }
        CloseEntity(objEntity);
    }
}


void SVDisableForm::EnableGroup(string &szGroupID)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    if(!szGroupID.empty())
    {
        //PrintDebugString(szGroupID.c_str());
        OBJECT group = GetGroup(szGroupID);
        if(group != INVALID_VALUE)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    //PrintDebugString("disable device");
                    EnableDevice(szEntityID);      
                }            
            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    EnableGroup(szSubGroupID);      
                }                
            }
            MAPNODE mainnode = GetGroupMainAttribNode(group);
            if(mainnode != INVALID_VALUE)
			{
	            FindNodeValue(mainnode, "sv_name", m_szONameTemp);

                AddNodeAttrib(mainnode, "sv_disable", "false");
			}
            SubmitGroup(group);
            CloseGroup(group);
            //DeleteGroup(szIndex, m_szIDCUser, m_szIDCPwd); 
        }  
    }
}

void SVDisableForm::EnableDevice(string &szDeviceID)
{
    list<string> lstMonitors;
    list<string>::iterator lstItem;
    if(!szDeviceID.empty())
    {
        //PrintDebugString(szDeviceID.c_str());
        OBJECT entity = GetEntity(szDeviceID);
        if (entity != INVALID_VALUE)
        {
            if(GetSubMonitorsIDByEntity(entity, lstMonitors))
            {
                for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                {
                    string szMonitorID = (*lstItem).c_str();
                    EnableMonitor(szMonitorID);
                    //DeleteSVMonitor(szMonitorID, m_szIDCUser, m_szIDCPwd);
                }
            }
            MAPNODE mainnode = GetEntityMainAttribNode(entity);
            if(mainnode != INVALID_VALUE)
			{
	            FindNodeValue(mainnode, "sv_name", m_szONameTemp);

				AddNodeAttrib(mainnode, "sv_disable", "false");
			}
        }
        SubmitEntity(entity);
        CloseEntity(entity);
        //DeleteEntity(szIndex, m_szIDCUser, m_szIDCPwd);
    }
}

void SVDisableForm::EnableMonitor(string &szMonitorID)
{
    OBJECT objSV = GetMonitor(szMonitorID);
    if(objSV != INVALID_VALUE)
    {
        MAPNODE mainnode = GetMonitorMainAttribNode(objSV);
        if(mainnode != INVALID_VALUE)
		{
            FindNodeValue(mainnode, "sv_name", m_szONameTemp);

			AddNodeAttrib(mainnode, "sv_disable", "false");
		}
        SubmitMonitor(objSV);
        CloseMonitor(objSV);
    }
    m_lsMonitors.push_back(szMonitorID);

	//获取设备的名称
	string szDeviceID("");
	szDeviceID = FindParentID(szMonitorID);
    OBJECT objEntity = GetEntity(szDeviceID);
    if(objEntity != INVALID_VALUE)
    {
        MAPNODE devnode = GetEntityMainAttribNode(objEntity);
        if(devnode != INVALID_VALUE)
        {
            FindNodeValue(devnode, "sv_name", m_szDeviceName);
        }
        CloseEntity(objEntity);
    }
}

int SVDisableForm::isDisable(string szIndex)
{
    int nDisable = 0;
    OBJECT objSV; 
    MAPNODE mainnode = INVALID_VALUE;
    string szDisable = "";
    int nYear = 0, nMonth = 0, nDay = 0;
    int nHour = 0, nMinute = 0;
    switch(m_nDisableType)
    {
    case sv_group:
        objSV = GetGroup(szIndex);
        if(objSV != INVALID_VALUE)
        {   
            mainnode = GetGroupMainAttribNode(objSV);
            if(mainnode != INVALID_VALUE)
            {
                FindNodeValue(mainnode, "sv_disable", szDisable);
                if(szDisable == "true")
                {
                    nDisable = 1;
                }
                else if( szDisable == "time")
                {
                    //if(m_nOperate == 3)
                    {
                        FindNodeValue(mainnode, "sv_endtime", m_szEndTime);
                        FindNodeValue(mainnode, "sv_endtime", m_szStartTime);
                        if(!m_szEndTime.empty())
                        {
                            sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);                        
                            svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                            svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                            if(ttime < ttend)
                                nDisable = 2;
                        }
                    }
                }
            }
            CloseGroup(objSV);
        }
        break;
    case sv_device:
        objSV = GetEntity(szIndex);
        if(objSV != INVALID_VALUE)
        {
            mainnode = GetEntityMainAttribNode(objSV);
            if(mainnode != INVALID_VALUE)
            {
                string szDisable = "";
                FindNodeValue(mainnode, "sv_disable", szDisable);
                if(szDisable == "true")
                {
                    nDisable = 1;
                }
                else if( szDisable == "time")
                {
                    //if(m_nOperate == 3)
                    {
                        FindNodeValue(mainnode, "sv_endtime", m_szEndTime);
                        FindNodeValue(mainnode, "sv_endtime", m_szStartTime);
                        if(!m_szEndTime.empty())
                        {
                            sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);                        
                            svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                            svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                            if(ttime < ttend)
                               nDisable = 2;
                        }
                    }
                }
            }
            CloseEntity(objSV);
        }        
        break;
    case sv_monitor:
        objSV = GetMonitor(szIndex);
        if(objSV != INVALID_VALUE)
        {
            mainnode = GetMonitorMainAttribNode(objSV);
            if(mainnode != INVALID_VALUE)
            {                
                FindNodeValue(mainnode, "sv_disable", szDisable);
                if(szDisable == "true")
                {
                    nDisable = 1;
                }
                else if( szDisable == "time")
                {
                    //if(m_nOperate == 3)
                    {
                        FindNodeValue(mainnode, "sv_endtime", m_szEndTime);
                        FindNodeValue(mainnode, "sv_endtime", m_szStartTime);
                        if(!m_szEndTime.empty())
                        {
                            sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);                        
                            svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                            svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                            if(ttime < ttend)
                                nDisable = 2;
                        }
                    }
                }
            }
            CloseMonitor(objSV);
        }   
        break;
    }

    if(nDisable != 2)
    {
        m_szEndTime = "";
        m_szStartTime = "";
    }

    return nDisable;
}

bool SVDisableForm::isSVSE(string &szIndex)
{
    int nPos = szIndex.find(".");
    if(nPos > 0)
        return false;
    else
        return true;
}

int SVDisableForm::isParentDisable(string &szIndex)
{
    int nDisable = 0;
    OBJECT objSV; 
    MAPNODE mainnode = INVALID_VALUE;
    string szDisable = "";
    int nYear = 0, nMonth = 0, nDay = 0;
    int nHour = 0, nMinute = 0;
    if(!isSVSE(szIndex))
    {
        objSV = GetGroup(szIndex);
        if(objSV != INVALID_VALUE)
        {   
            mainnode = GetEntityMainAttribNode(objSV);
            if(mainnode != INVALID_VALUE)
            {
                PrintDebugString("open group");
                FindNodeValue(mainnode, "sv_disable", szDisable);
                if(szDisable == "true")
                {
                    nDisable = 1;
                }
                else if( szDisable == "time")
                {
                    FindNodeValue(mainnode, "sv_endtime", m_szEndTime);
                    FindNodeValue(mainnode, "sv_endtime", m_szStartTime);
                    if(!m_szEndTime.empty())
                    {
                        sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);                        
                        svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                        svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                        if(ttime < ttend)
                            nDisable =  2;                        
                    }
                }
            }
            CloseGroup(objSV);
        }
        else
        {
            objSV = GetEntity(szIndex);
            if(objSV != INVALID_VALUE)
            {
                mainnode = GetEntityMainAttribNode(objSV);
                if(mainnode != INVALID_VALUE)
                {
                    string szDisable = "";
                    FindNodeValue(mainnode, "sv_disable", szDisable);
                    if(szDisable == "true")
                    {
                        nDisable = 1;
                    }
                    else if( szDisable == "time")
                    {
                        //if(m_nOperate == 3)
                        {
                            FindNodeValue(mainnode, "sv_endtime", m_szEndTime);
                            FindNodeValue(mainnode, "sv_endtime", m_szStartTime);
                            if(!m_szEndTime.empty())
                            {
                                sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);                        
                                svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                                svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                                if(ttime < ttend)
                                nDisable = 2;
                            }
                        }
                    }
                }
                CloseEntity(objSV);
            }
        }
    }
    return nDisable;
}

int SVDisableForm::isEntityDisable(string &szIndex)
{
    int nDisable = 0;
    OBJECT objSV; 
    MAPNODE mainnode = INVALID_VALUE;
    string szDisable = "";
    int nYear = 0, nMonth = 0, nDay = 0;
    int nHour = 0, nMinute = 0;
    objSV = GetEntity(szIndex);
    if(objSV != INVALID_VALUE)
    {   
        FindNodeValue(mainnode, "sv_disable", szDisable);
        if(szDisable == "true")
        {
            nDisable = 1;
        }
        else if( szDisable == "time")
        {
            FindNodeValue(mainnode, "sv_endtime", m_szEndTime);
            FindNodeValue(mainnode, "sv_endtime", m_szStartTime);
            if(!m_szEndTime.empty())
            {
                sscanf(m_szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);                        
                svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                if(ttime < ttend)
                    nDisable = 2;                        
            }
        }
        CloseEntity(objSV);
    }
    return nDisable;
}   

void SVDisableForm::ParserQueryString(string &szQuery)
{
    if(!szQuery.empty())
    {
        m_lsIndex.clear();
        char * token = NULL;
        // duplicate string
        char * cp = strdup(szQuery.c_str());
        if (cp)
        {
            token = strtok(cp , ",;");
            // every field
            while( token != NULL )
            {
                //PrintDebugString(token);
                m_lsIndex.push_back(token);
                // next field
                token = strtok( NULL , ",;");
            }
            free(cp);
        }
    }
}

void SVDisableForm::cancel()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Disable";
	LogItem.sHitFunc = "cancel";
	LogItem.sDesc = strCancel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//appl->quit();
    WebSession::js_af_up = m_szReturn + "window.close();";
    m_szReturn = "";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

void SVDisableForm::eventConfirm()
{
	string strOName;
    list<string>::iterator lsItem;
    for(lsItem = m_lsIndex.begin(); lsItem != m_lsIndex.end(); lsItem++)
    {
        string szMonitorID = (*lsItem);
        SetDYN(szMonitorID, 0, m_szIDCUser, m_szIDCPwd);

		string szDeviceID = FindParentID(szMonitorID);
		//获取设备的名称
		string szDName(""),szMName("");
		OBJECT objEntity = GetEntity(szDeviceID);
		if(objEntity != INVALID_VALUE)
		{
			MAPNODE devnode = GetEntityMainAttribNode(objEntity);
			if(devnode != INVALID_VALUE)
			{
				FindNodeValue(devnode, "sv_name", szDName);
			}
			CloseEntity(objEntity);
		}
		//获取监测器的名称
		OBJECT objSV = GetMonitor(szMonitorID);
		if(objSV != INVALID_VALUE)
		{
			MAPNODE mainnode = GetMonitorMainAttribNode(objSV);
			if(mainnode != INVALID_VALUE)
			{
				FindNodeValue(mainnode, "sv_name", szMName);
			}
			CloseMonitor(objSV);
		}
		strOName += szDName;
		strOName += ":";
		strOName += szMName;
		strOName += "  ";
        break;
    }
	//插记录到UserOperateLog表
	string strUserID = GetWebUserID();	
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_szConfirmTitle,m_szOMonitor,strOName);

    WebSession::js_af_up = "showAlertMsg(\""+ m_szConfirmSucc + "\");";
}

bool SVDisableForm::showConfirmTable()
{
    bool bShow = false;
    list<string>::iterator lsItem;
    for(lsItem = m_lsIndex.begin(); lsItem != m_lsIndex.end(); lsItem++)
    {
        string szIndex = (*lsItem);
        OBJECT objMonitor = GetMonitor(szIndex);
        if(objMonitor != INVALID_VALUE)
        {
            MAPNODE node= GetMonitorAdvanceParameterNode(objMonitor);
            if(node != INVALID_VALUE)
            {
                string szConfirm = "";
                FindNodeValue(node, "_monitorcondition", szConfirm);
                if(!szConfirm.empty() && szConfirm !="3" )
                    bShow = true;
            }
        }
        break;
    }
    return bShow;
}
