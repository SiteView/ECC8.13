//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "EmailSet.h"
#include "MainForm.h"
#include "FlexTable.h"
#include "MainTable.h"
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WSVButton.h"
#include "WLineEdit"
#include "WebSession.h"

#include <WApplication>

#include "../../base/des.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../base/OperateLog.h"


//////////////////////////////////////////////////////////////////////////////////
// start

//////////////////////////////////////////////////////////////////////////////////
//CSVEmailSet
// 构造函数
CSVEmailSet::CSVEmailSet(WContainerWidget * parent):
WContainerWidget(parent)
{
//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_User_Check_Error",m_formText.szErrUser);
			FindNodeValue(ResNode,"IDS_Send_Server_Error",m_formText.szErrSmtp);
			FindNodeValue(ResNode,"IDS_Send_Email_Error",m_formText.szErrMail);
			FindNodeValue(ResNode,"IDS_Backup_Send_Server",m_formText.szBackServer);
			FindNodeValue(ResNode,"IDS_Disable",m_formText.szDisable);
			FindNodeValue(ResNode,"IDS_Enable",m_formText.szEnable);
			FindNodeValue(ResNode,"IDS_Send_Email",m_formText.szFrom);
			FindNodeValue(ResNode,"IDS_Password_Check",m_formText.szPwd);
			FindNodeValue(ResNode,"IDS_Send_Server_SMTP",m_formText.szSMTP);
			FindNodeValue(ResNode,"IDS_User_Check",m_formText.szUser);
			FindNodeValue(ResNode,"IDS_Send_Server_Help",m_formText.szSMTPDes);
			FindNodeValue(ResNode,"IDS_Backup_Send_Server_Help",m_formText.szBackServerDes);
			FindNodeValue(ResNode,"IDS_User_Check_Help",m_formText.szUserDes);
			FindNodeValue(ResNode,"IDS_Password_Check_Help",m_formText.szPwdDes);
			FindNodeValue(ResNode,"IDS_Send_Email_Help",m_formText.szFromDes);
			FindNodeValue(ResNode,"IDS_Receive_Email",m_formText.szTBTitle);
			FindNodeValue(ResNode,"IDS_Receive_Email_Help",m_formText.szTBDiscri);
			FindNodeValue(ResNode,"IDS_Email_Address",m_formText.tbColtitle.szMail);
			FindNodeValue(ResNode,"IDS_Edit",m_formText.tbColtitle.szEdit);
			FindNodeValue(ResNode,"IDS_Name",m_formText.tbColtitle.szName);
			FindNodeValue(ResNode,"IDS_State",m_formText.tbColtitle.szSelAll);
			FindNodeValue(ResNode,"IDS_State",m_formText.tbColtitle.szState);
			FindNodeValue(ResNode,"IDS_Email_Set",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Add_Email",m_formText.szAdd);
			FindNodeValue(ResNode,"IDS_Delete_Email",m_formText.szDel);
			FindNodeValue(ResNode,"IDS_Save_Email",m_formText.szSave);
			FindNodeValue(ResNode,"IDS_Test_Email",m_formText.szTest);
			FindNodeValue(ResNode,"IDS_Address_Set",m_formText.szAdvTitle);
			FindNodeValue(ResNode,"IDS_General_Set",m_formText.szGenTitle);
			FindNodeValue(ResNode,"IDS_Save_Success",m_formText.szSaveSucess);			
			FindNodeValue(ResNode,"IDS_All_Select",strAllSel);
			FindNodeValue(ResNode,"IDS_None_Select",strAllNotSel);
			FindNodeValue(ResNode,"IDS_Invert_Select",strFanSel);
			FindNodeValue(ResNode,"IDS_Delete",strDelete);
			FindNodeValue(ResNode,"IDS_Add",strAddNew);
			FindNodeValue(ResNode,"IDS_AddMail_Title",szAddEmailBut);
			FindNodeValue(ResNode,"IDS_NULL_Email_List",m_formText.szNoEmailSetItem);
			FindNodeValue(ResNode,"IDS_AffirmDeleteEmailAddress",m_formText.szDelAffirmInfo);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",m_formText.szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",m_formText.szButMatch);
			FindNodeValue(ResNode,"IDS_EMAILSET_NULL",szEmailNull);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh1);
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);
		}
		CloseResource(objRes);
	}
  
    EmailSetForm();
    
}

//////////////////////////////////////////////////////////////////////////////////
// EmailSetForm
// 显示 设置 页面
void CSVEmailSet::EmailSetForm()
{
	// 在INI文件中读取每个指定表项的内容
	pMainTable = new WSVMainTable(this,m_formText.szTitle,true);
	if (pMainTable->pHelpImg)
	{
		connect(pMainTable->pHelpImg, SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}
	
	//基础设置表
	m_pSetTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(1,0), Group, m_formText.szGenTitle); 
	InitSetTable();
	
	//邮件地址表
	m_pAddressTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(2,0), List, m_formText.szAdvTitle);
	InitAddressTable();
	
	m_pAddressListTable = m_pAddressTable->GeDataTable();

	//m_signalMapper mapped 事件处理 函数 EditMail
    connect(&m_signalMapper, SIGNAL(mapped(int)), this, SLOT(EditMail(int)));

	//隐藏按钮
	pHideBut = new WPushButton("hide button",this);
	pTranslateBtn = new WPushButton("翻译",this);
	pExChangeBtn = new  WPushButton("刷新",this);

	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelEmail()));
		pHideBut->hide();
	}

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}
	
	AddJsParam("listheight", strListHeights);
	AddJsParam("listtitle", strListTitles);
	AddJsParam("listpan", strListPans);
	
}

void CSVEmailSet::ShowHelp()
{
	if (m_pSetTable)
	{
		m_pSetTable->ShowOrHideHelp();
	}
}

void CSVEmailSet::InitSetTable()
{
	if(m_pSetTable != NULL && m_pSetTable->GetContentTable() != NULL)
	{
		//读取email基础设置值
		string szEmailServer = "", szEmailfrom = "", szUserID = "", szUserPwd = "",
			szBackServer = "" ;
		// SMTP 服务器
		szEmailServer=GetIniFileString("email_config", "server", "",  "email.ini");
		// Email from
		szEmailfrom=GetIniFileString("email_config", "from", "",  "email.ini");
		// 校验用户
		szUserID=GetIniFileString("email_config", "user", "",  "email.ini");
		// 校验密码
		//szUserPwd=GetIniFileString("email_config", "password", "",  "email.ini");
		// 校验密码
		szUserPwd=GetIniFileString("email_config", "password", "",  "email.ini");
		Des mydes;
		char dechar[1024]={0};
		if(szUserPwd.size()>0)
		{
			mydes.Decrypt(szUserPwd.c_str(),dechar);
			szUserPwd = dechar;
		}
		// 备份SMTP服务器
		szBackServer=GetIniFileString("email_config", "backupserver", "",  "email.ini");

		m_pSetTable->AppendRows("");

		pServerIp = new WLineEdit(szEmailServer, m_pSetTable->AppendRowsContent(0,m_formText.szSMTP, m_formText.szSMTPDes, m_formText.szErrSmtp,true));
		pMailFrom = new WLineEdit(szEmailfrom, m_pSetTable->AppendRowsContent(0, m_formText.szFrom, m_formText.szFromDes,  m_formText.szErrMail,true));
		pBackupServer = new WLineEdit(szBackServer, m_pSetTable->AppendRowsContent(0, m_formText.szBackServer, m_formText.szBackServerDes, ""));
		pUser = new WLineEdit(szUserID, m_pSetTable->AppendRowsContent(0, m_formText.szUser,  m_formText.szUserDes,  m_formText.szErrUser,true));
		pPwd = new WLineEdit(szUserPwd, m_pSetTable->AppendRowsContent(0, m_formText.szPwd,  m_formText.szPwdDes,  ""));
		pPwd->setEchoMode(WLineEdit::Password);
		pServerIp->setTextSize(50);		
		pMailFrom->setTextSize(50);
		pBackupServer->setTextSize(50);
		pUser->setTextSize(50);
		pPwd->setTextSize(50);
		pServerIp->setStyleClass("input_text_300");
		pMailFrom->setStyleClass("input_text_300");
		pBackupServer->setStyleClass("input_text_300");
		pUser->setStyleClass("input_text_300");
		pPwd->setStyleClass("input_text_300");

		m_pSetTable->ShowOrHideHelp();
		m_pSetTable->HideAllErrorMsg();
	}

	if(m_pSetTable != NULL && m_pSetTable->GetActionTable()!=NULL)
	{
		WTable *pTbl;

		m_pSetTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pSetTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		pTbl = new WTable(m_pSetTable->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");
		AddGeneralOperate(pTbl);
	}
}

//添加客户端脚本变量
void CSVEmailSet::AddJsParam(const std::string name, const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}


void CSVEmailSet::InitAddressTable()
{	
	//return;
	m_pAddressTable->SetDivId("listpan1");
	if(m_pAddressTable->GetContentTable()!=NULL)
	{
		strListHeights += "300";
		strListHeights += ",";
		strListPans += m_pAddressTable->GetDivId();
		strListPans += ",";
		strListTitles +=  m_pAddressTable->dataTitleTable->formName();
		strListTitles += ",";

		m_pAddressTable->AppendColumn("",WLength(30,WLength::Pixel));
		m_pAddressTable->SetDataRowStyle("table_data_grid_item_img");
		m_pAddressTable->AppendColumn(m_formText.tbColtitle.szName,WLength(180,WLength::Pixel));
		m_pAddressTable->SetDataRowStyle("table_data_grid_item_img");
		m_pAddressTable->AppendColumn(m_formText.tbColtitle.szState,WLength(10,WLength::Percentage));
		m_pAddressTable->SetDataRowStyle("table_data_grid_item_text");
		m_pAddressTable->AppendColumn(m_formText.tbColtitle.szMail,WLength(50,WLength::Percentage));
		m_pAddressTable->SetDataRowStyle("table_data_grid_item_text");
		m_pAddressTable->AppendColumn(m_formText.tbColtitle.szEdit,WLength(80,WLength::Pixel));
		m_pAddressTable->SetDataRowStyle("table_data_grid_item_img");

		ADD_MAIL_OK mail;

		//获取地址列表。。。
		if(GetIniFileSections(keylist, "emailAdress.ini"))
		{
			//初始化地址列表。。。
			int iRow = 1;
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
			{
				mail = ReadMailList(*keyitem);
				InitMailList(mail,iRow);
				iRow++;
			}
		}

		if(m_pListMail.size() <= 0)
		{
			//WText * nText = new WText(m_formText.szNoEmailSetItem, (WContainerWidget*)m_pAddressTable->GetContentTable()->elementAt(0 , 0));
			//nText ->decorationStyle().setForegroundColor(Wt::red);
		}
	}

	if(m_pAddressTable->GetActionTable()!=NULL)
	{
		m_pAddressTable->AddStandardSelLink(strAllSel ,strAllNotSel,strFanSel);
		WTable *pTbl;
		
		m_pAddressTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pAddressTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
		pTbl = new WTable(m_pAddressTable->GetActionTable()->elementAt(0,1));
		pTbl->setStyleClass("widthauto");
		AddAddressOperate(pTbl);

		//添加按钮，需要靠右
		m_pAddressTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
		WSVButton * pAdd = new WSVButton(m_pAddressTable->GetActionTable()->elementAt(0,2),szAddEmailBut, "button_bg_add_black.png", "", true);
		if (pAdd)
		{
			WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(AddEmail()));
		}    
	}

	m_pAddressTable->SetNullTipInfo(szEmailNull);
}
void CSVEmailSet::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "emailsetRes";
	WebSession::js_af_up += "')";
}
void CSVEmailSet::ExChange()
{
	PrintDebugString("------ExChangeEvent------\n");
	emit ExChangeEvent();
}

//删除按钮
void CSVEmailSet::BeforeDelEmail()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "BeforeDelEmail";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

    for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 判断是否是选择状态
        if (m_pListItem->pSelect->isChecked())
        {   
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + m_formText.szDelAffirmInfo + "','" + m_formText.szButNum + "','" + m_formText.szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;
		}
    }


	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
// DelEmailX
// 删除所选择的行
void CSVEmailSet::DelEmail()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "DelEmail";
	LogItem.sDesc = m_formText.szDel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strDeleteEmail;
    // 比较列表中每一项
    for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 判断是否是选择状态
        if (m_pListItem->pSelect->isChecked())
        {   
            // 得到表格中的真实行号
            int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();
            // 当前行
            list<MAIL_LIST>::iterator pItem = m_pListItem;          
			
			//删除ini里的项
			char chItem[32]  = {0};
			sprintf(chItem, "%d", m_pListItem->nIndex);
			string strItem = "Item";
			strItem += chItem;
  
			string strTemp = pItem->pName->text();
			strDeleteEmail += strTemp;
			strDeleteEmail += "  ";
			
			PrintDebugString("DELETE\n");
			PrintDebugString(strItem.c_str());
			PrintDebugString("\n");
		
			DeleteIniFileSection(strItem.c_str(), "emailAdress.ini");
			//mail

            // 回到上一行
            m_pListItem --;
            // 在列表中删除当前行
            m_pListMail.erase(pItem);          
            // 在表格中删除行
			m_pAddressListTable->deleteRow(nRow);    
        }
    }

	//是否还有记录?
	if(m_pListMail.size() <= 0)
	{
		m_pAddressTable->ShowNullTip();
	}else
	{
		m_pAddressTable->HideNullTip();
	}

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strDelete,m_formText.szTitle,strDeleteEmail);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

// AddEmail
// 添加一个新行
void CSVEmailSet::AddEmail()
{
 	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "AddEmail";
	LogItem.sDesc = szAddEmailBut;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	// 触发添加邮件列表项事件
	PrintDebugString("AddNewMail");
    emit AddNewMail();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

// AddMailList
// 添加修改邮件列表成功事件处理函数
void CSVEmailSet::AddMailList(ADD_MAIL_OK mail)
{
    if(mail.nIndex != -1)
    {// 如果不是新追加的项，调用修改函数
        EditRow(mail);
        return;
    }

	PrintDebugString("AddMailList");
	PrintDebugString("\n");

    // 得到总行数
    int numRow = m_pAddressTable->GeDataTable()->numRows();

	m_pAddressTable->InitRow(numRow);

    MAIL_LIST list;

	m_pAddressTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(WWidget::AlignCenter);
    // 是否选择
    WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow, 0));
    
	m_pAddressTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(WWidget::AlignCenter);
    // 名称
	WText *pName = new WText(mail.szName, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow , 2));

	m_pAddressTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(WWidget::AlignCenter);
    // 邮件列表
	WText * pValue = new WText(mail.szMailList, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow , 6));

	m_pAddressTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(WWidget::AlignCenter);
    // 状态
    WText * pState = NULL;
    if(mail.bCheck)
    {
	    pState = new WText(m_formText.szDisable, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow  , 4));
    }
    else
    {
        pState = new WText(m_formText.szEnable, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow  , 4));
    }

	m_pAddressTable->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(WWidget::AlignCenter);
	WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow , 8));
    pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);    
    // 图片 cliecker事件 处理函数 map
    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));


    //得到随机唯一的索引值
    int nIndex = GetOnlyIndex();

	mail.nIndex = nIndex;

	// 设置
    list.pSelect = pCheck;
    list.pName = pName;
    list.pValue = pValue;
    list.pState = pState;
    list.nIndex = mail.nIndex;
    list.bDisable = mail.bCheck;
	list.szDes = mail.szDes;
	list.szSchedule = mail.szSchedule;
	list.szTemplate = mail.szTemplate;

    // 追加到邮件列表中
    m_pListMail.push_back(list);

    // 转换索引值为字符型
    char chIndex[32] = {0};
    sprintf(chIndex, "%d", nIndex);
    m_signalMapper.setMapping(pEdit, nIndex); 

    // 设置行属性
    WTableRow * pRow = m_pAddressListTable->GetRow(numRow);
    pRow -> property = chIndex; 

	PrintDebugString("AddMailList");
	PrintDebugString("\n");
	
	//保存到设置文件
	WriteMailList(mail);

	m_pAddressTable->HideNullTip();
}

//初始化邮件地址列表
void CSVEmailSet::InitMailList(ADD_MAIL_OK mail, int numRow)
{
	m_pAddressTable->InitRow(numRow);

    MAIL_LIST list;


	m_pAddressTable->GeDataTable()->elementAt(numRow, 0)->setContentAlignment(WWidget::AlignCenter);
    // 是否选择
    WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow, 0));
    
	m_pAddressTable->GeDataTable()->elementAt(numRow, 2)->setContentAlignment(WWidget::AlignCenter);
    // 名称
	WText *pName = new WText(mail.szName, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow , 2));

	m_pAddressTable->GeDataTable()->elementAt(numRow, 6)->setContentAlignment(WWidget::AlignCenter);
    // 邮件列表
	WText * pValue = new WText(mail.szMailList, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow , 6));

	m_pAddressTable->GeDataTable()->elementAt(numRow, 4)->setContentAlignment(WWidget::AlignCenter);
    // 状态
    WText * pState = NULL;
    if(!mail.bCheck)
    {
	    pState = new WText(m_formText.szEnable, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow  , 4));
    }
    else
    {
        pState = new WText(m_formText.szDisable, (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow  , 4));
    }

	m_pAddressTable->GeDataTable()->elementAt(numRow, 8)->setContentAlignment(WWidget::AlignCenter);
	WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)m_pAddressTable->GeDataTable()->elementAt(numRow , 8));
    pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
    
    // 图片 cliecker 事件 处理函数 map
    connect(pEdit, SIGNAL(clicked()), &m_signalMapper, SLOT(map()));

    // 得到随机索引值
    //int nIndex = GetOnlyIndex();

	// 设置
    list.pSelect = pCheck;
    list.pName = pName;
    list.pValue = pValue;
    list.pState = pState;
	list.nIndex = mail.nIndex;
    list.bDisable = mail.bCheck;
	list.szDes = mail.szDes;
	list.szSchedule = mail.szSchedule;
	list.szTemplate = mail.szTemplate;

    // 追加到邮件列表中
    m_pListMail.push_back(list);

    // 转换索引值为字符型
    char chIndex[32] = {0};
    sprintf(chIndex, "%d", mail.nIndex);
	PrintDebugString("InitIndex\n");
	PrintDebugString(chIndex);
	PrintDebugString("\n");
    m_signalMapper.setMapping(pEdit, mail.nIndex); 

    // 设置行属性
    WTableRow * pRow = m_pAddressTable->GeDataTable()->GetRow(numRow);
    pRow -> property = chIndex; 
}

//获取唯一的index
int CSVEmailSet::GetOnlyIndex()
{
	int index = 0;
	bool bFind = false;
	while(true)
	{
		index = RandIndex();

		bFind = false;
		for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)	
		{			 
			if(m_pListItem->nIndex == index)
			{
				bFind = true;
				break;
			}
		}
		
		if(bFind)
			continue;
		else
			break;
	}
	
	return index;
}


// EditRow
// 修改一行
void CSVEmailSet::EditRow(ADD_MAIL_OK &maillist)
{ 
	// 比较列表中每一项
    for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 判断索引值是否为待修改项
        if(m_pListItem->nIndex == maillist.nIndex)
        {
            // 更改各项属性
            // 名称
            m_pListItem->pName->setText(maillist.szName);
            // 邮件列表
            m_pListItem->pValue->setText(maillist.szMailList);
              // 属性
            if(maillist.bCheck)
            {
                m_pListItem->pState->setText(m_formText.szDisable);
                m_pListItem->bDisable = true;
            }
            else
            {
                m_pListItem->pState->setText(m_formText.szEnable);
                m_pListItem->bDisable = false;
            }
			
			m_pListItem->szDes = maillist.szDes;
			m_pListItem->szSchedule = maillist.szSchedule;
			m_pListItem->szTemplate = maillist.szTemplate;

            break;
        }
    }

	//保存到设置文件
	WriteMailList(maillist);
}


// EditMail
// 修改事件
void CSVEmailSet::EditMail(int nIndex)
{  
    bool bFind = false;
    ADD_MAIL_OK maillist;
    // 比较列表中每一项
    for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 判断索引值是否为待修改项
        if(m_pListItem->nIndex == nIndex)
        {
            char chTmp[10] = {0};
            // 待修改行索引
            maillist.nIndex = nIndex;
            // 待修改行名称
            maillist.szName = m_pListItem->pName->text();
            // 待修改行邮件列表
            maillist.szMailList = m_pListItem->pValue->text();
            // 待修改行状态
            maillist.bCheck = m_pListItem->bDisable;
			//调度计划
			maillist.szSchedule = m_pListItem->szSchedule;			
			//模板
			maillist.szTemplate = m_pListItem->szTemplate;
			//描述
			maillist.szDes = m_pListItem->szDes;

            bFind = true;

            break;
        }
    }

    // 找到待修改行触发修改邮件列表事件
    if(bFind)
        emit EditMailList(maillist);
}

//添加基础设置的操作按钮组
void CSVEmailSet::AddGeneralOperate(WTable * pTable)
{
	//WTable* m_pGeneralOprOprTable = new WTable((WContainerWidget *)pTable->elementAt( nRow, 1));
	//
	//if(m_pGeneralOprOprTable)
	{
		// 保存功能
		WSVButton *pSaveSet = new WSVButton(pTable->elementAt(0, 0),m_formText.szSave, "button_bg_m_black.png", m_formText.szSave, true);
		WObject::connect(pSaveSet, SIGNAL(clicked()), this, SLOT(Save()));

		// 测试邮件功能
		WSVButton * pTestMail = new WSVButton(pTable->elementAt(0, 1),m_formText.szTest, "button_bg_m.png", m_formText.szTest, false);
		std::string strOpen = "OpenTest('";
		strOpen += "emailtest.exe?";
		strOpen += "')";
		WObject::connect(pTestMail, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	
	}
}

//添加地址列表的操作按钮组
void CSVEmailSet::AddAddressOperate(WTable * pTable)
{
	WTable *m_pAddressOprTable = pTable;

    if(m_pAddressOprTable)
    {
        WText * pSelAll = m_pAddressTable->pSelAll;
        if (pSelAll)
        {
			pSelAll->setToolTip(strAllSel);
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
        }

        WText * pSelNone = m_pAddressTable->pSelNone;
        if (pSelAll)
        {
			pSelNone->setToolTip(strAllNotSel);
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
        }

        WText * pSelinvert = m_pAddressTable->pSelReverse;
        if (pSelinvert)
        {
			pSelinvert->setToolTip(strFanSel);
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
        }

		WSVButton * pDel = new WSVButton(pTable->elementAt(0, 4),strDelete, "button_bg_del.png", "", false);
        if (pDel)
        {
			connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelEmail()));
        } 

		//WImage *pSort = new WImage("../Images/sort.gif", (WContainerWidget *)m_pAddressOprTable->elementAt(0, 6));
        //if (pSort)
        //{
        //    pSort->setStyleClass("commonbutton");
        //    pSort->setToolTip("sort");
        //}
    }
}

// 处理刷新事件
void CSVEmailSet::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh1;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//更新基础参数
    string szEmailServer = "", szEmailfrom = "", szUserID = "", szUserPwd = "",
			szBackServer = "" ;
    // SMTP 服务器
	szEmailServer = GetIniFileString("email_config", "server", "",  "email.ini");
    // Email from
	szEmailfrom = GetIniFileString("email_config", "from", "",  "email.ini");
    // 校验用户
	szUserID = GetIniFileString("email_config", "user", "",  "email.ini");
    // 校验密码
	//szUserPwd = GetIniFileString("email_config", "password", "",  "email.ini");
	// 校验密码
	szUserPwd=GetIniFileString("email_config", "password", "",  "email.ini");
	Des mydes;
	char dechar[1024]={0};
	if(szUserPwd.size()>0)
	{
		mydes.Decrypt(szUserPwd.c_str(),dechar);
		szUserPwd = dechar;
	}
    // 备份SMTP服务器
	szBackServer = GetIniFileString("email_config", "backupserver", "",  "email.ini");

    // 发件服务器
	pServerIp->setText(szEmailServer); 
	// 邮件来源
    pMailFrom->setText(szEmailfrom);
    // 用户
	pUser->setText(szUserID);
    // 密码
	pPwd->setText(szUserPwd);
    // 备份发件服务器
	pBackupServer->setText(szBackServer);

	
	//更新列表
	//清空列表
	if (m_pAddressTable->GeDataTable() != NULL)
	{
		/*
		int nNum = m_pAddressTable->GeDataTable()->numRows();
		for(int i = 1;i < nNum;i++)
		{
			m_pAddressTable->GeDataTable()->deleteRow(1);
		}
		*/
		m_pAddressTable->GeDataTable()->clear();
	}
	
	m_pListMail.clear();
	
	//重新初试化
	ADD_MAIL_OK mail;
	
	//获取地址列表。。。
	if(GetIniFileSections(keylist, "emailAdress.ini"))
	{
		//初始化地址列表。。。
		int iRow  = 1;
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			mail = ReadMailList(*keyitem);
			InitMailList(mail,iRow);
			iRow++;
		}
	}  

	if(m_pListMail.size() <=0)
	{
		m_pAddressTable->ShowNullTip();
	}else
	{
		m_pAddressTable->HideNullTip();
	}

	//翻译
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		this->pTranslateBtn->show();
		connect(this->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		this->pExChangeBtn->show();
		connect(this->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		this->pTranslateBtn->hide();
		this->pExChangeBtn->hide();
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//全选
void CSVEmailSet::SelAll()
{  
	// 得到列表中每一项    
	for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 修改每一项的选择状态
		m_pListItem->pSelect->setChecked(true);
    }
}

//全不选
void CSVEmailSet::SelNone()
{   
	// 得到列表中每一项
	for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 修改每一项的选择状态
		m_pListItem->pSelect->setChecked(false);
    }
}

//反选
void CSVEmailSet::SelInvert()
{
	for(m_pListItem = m_pListMail.begin(); m_pListItem != m_pListMail.end(); m_pListItem ++)
    {
        // 修改每一项的选择状态
		if(m_pListItem->pSelect->isChecked())
		{
			m_pListItem->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem->pSelect->setChecked(true);
		}
    }
}

//保存基础选项的信息
void CSVEmailSet::Save()
{	
 	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "EmailSet";
	LogItem.sHitFunc = "Save";
	LogItem.sDesc = m_formText.szSave;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return;
	}

	SEND_MAIL_PARAM sendParam;
    sendParam.m_szServer = pServerIp -> text();
    sendParam.m_szBackServer = pBackupServer -> text();
    sendParam.m_szFrom = pMailFrom -> text();
    sendParam.m_szUserID = pUser -> text();
	
	string strPwd = pPwd -> text();;
	Des mydes;	
	char enchar[1024]={0};
	if(strPwd.size()>0)
	{
		mydes.Encrypt(strPwd.c_str(),enchar);
		strPwd= enchar;
	}

	sendParam.m_szPwd = strPwd;

	bool bError = false;
	std::list<string> errorMsgList;

    //校验各个必选项并写设置
    //SMTP 服务器
    if(sendParam.m_szServer.empty())
    {
		errorMsgList.push_back(m_formText.szErrSmtp);
		bError = true;
    }
    //校验邮件地址是否正确
    if(!checkEmail())
    {
        errorMsgList.push_back(m_formText.szErrMail);
		bError = true;
    }
    
    //用户名
    if (sendParam.m_szUserID.empty())
    {
        errorMsgList.push_back(m_formText.szErrUser);
		bError = true;
    }
	
	if(bError)
	{
		m_pSetTable->ShowErrorMsg(errorMsgList);
		bEnd = true;	
		goto OPEnd;
	}

	WriteIniFileString("email_config", "server", sendParam.m_szServer.c_str(), "email.ini");
	WriteIniFileString("email_config", "from", sendParam.m_szFrom.c_str(), "email.ini");
	WriteIniFileString("email_config", "user", sendParam.m_szUserID.c_str(), "email.ini");

	//密码
    if (!sendParam.m_szPwd.empty())
	{
        WriteIniFileString("email_config", "password", sendParam.m_szPwd.c_str(), "email.ini");
	}

    //备份SMTP服务器
    if (!sendParam.m_szBackServer.empty())
	{
        WriteIniFileString("email_config", "backupserver", sendParam.m_szBackServer.c_str(), "email.ini");
	}

	//隐藏错误提示信息
	m_pSetTable->HideAllErrorMsg();
    
	//触发保存成功事件
    //emit SaveSuccessful(sendParam);

	//插记录到UserOperateLog表
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),m_formText.tbColtitle.szEdit,m_formText.szTitle);
	
	WebSession::js_af_up = "alert('";
	WebSession::js_af_up += m_formText.szSaveSucess;
	WebSession::js_af_up += "')";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//写ADD_MAIL_OK结构到ini
void CSVEmailSet::WriteMailList(ADD_MAIL_OK mail)
{
	char chItem[32]  = {0};
	sprintf(chItem, "%d", mail.nIndex);
	string strSectionItem = "Item";
	strSectionItem += chItem;
	
	PrintDebugString("WriteMailList\n");
	PrintDebugString(chItem);
	PrintDebugString("\n");

	if(mail.bCheck)
		WriteIniFileInt(strSectionItem, "bCheck", 1, "emailAdress.ini");
	else
		WriteIniFileInt(strSectionItem, "bCheck", 0, "emailAdress.ini");
	WriteIniFileInt(strSectionItem, "nIndex", mail.nIndex, "emailAdress.ini");
	WriteIniFileString(strSectionItem, "Name", mail.szName, "emailAdress.ini");
	WriteIniFileString(strSectionItem, "MailList", mail.szMailList, "emailAdress.ini");
	WriteIniFileString(strSectionItem, "Template", mail.szTemplate, "emailAdress.ini");
	WriteIniFileString(strSectionItem, "Schedule", mail.szSchedule, "emailAdress.ini");
	WriteIniFileString(strSectionItem, "Des", mail.szDes, "emailAdress.ini");
}

//从ini读取ADD_MAIL_OK结构
ADD_MAIL_OK CSVEmailSet::ReadMailList(string strSectionItem)
{
	ADD_MAIL_OK mail;

	if(GetIniFileInt(strSectionItem, "bCheck", 1, "emailAdress.ini") == 1)
		mail.bCheck = true;
	else
		mail.bCheck = false;
	mail.nIndex = GetIniFileInt(strSectionItem, "nIndex", 0, "emailAdress.ini");
	mail.szName = GetIniFileString(strSectionItem, "Name", "" , "emailAdress.ini");
	mail.szMailList = GetIniFileString(strSectionItem, "MailList", "", "emailAdress.ini");
	mail.szTemplate = GetIniFileString(strSectionItem, "Template", "", "emailAdress.ini");
	mail.szSchedule = GetIniFileString(strSectionItem, "Schedule", "", "emailAdress.ini");
	mail.szDes = GetIniFileString(strSectionItem, "Des", "" , "emailAdress.ini");
	
	return mail;
}

//校验邮件地址
bool CSVEmailSet::checkEmail()
{
    string szMailList = pMailFrom->text();

    // 地址为空
    if(szMailList.empty())
        return false;

    char * pTemp1 = NULL, * pTemp2 = NULL;
    
    // 是否包含 @
    pTemp1 = strchr(szMailList.c_str(), '@');
    if (!pTemp1)
        return false;
    
    // @后是否不为 .
    if (*(++pTemp1) == '.')
        return false;
    
    // 是否包含 .
    pTemp2 = strchr(pTemp1, '.');
    if (!pTemp2)
        return false;

    return true;
}

//可能的遗留问题
//1、checkbox的初始化。
//2、标准化增加按钮、列表标题栏、删除、邮件地址唯一性。
//3、error如果重复以导致不能正确提示出错。
//4、检验邮件地址等公用函数的提取。