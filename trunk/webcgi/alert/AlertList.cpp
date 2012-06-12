#include <time.h>
#include ".\alertlist.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
#include "../../base/des.h"
//#include "../../base/GetInstallPath.h"
#include "../base/OperateLog.h"

#include "..\svtable\FlexTable.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\AnswerTable.h"

#include "websession.h"
#include <WApplication>
#include <WCheckBox>
#include <WComboBox>
#include <WText>
#include <WLineEdit>
#include <WSelectionBox>
#include <WButtonGroup>
#include <WRadioButton>
#include "WSignalMapper"
#include <WScrollArea>
#include <SVTable.h>
#include <WButtonTab>

#include "..\checkboxtreeview\CheckBoxTreeView.h"
#include "..\checkboxtreeview\WTreeNode.h"
#include "../base/basetype.h"

#include "../../base/splitquery.h"
using namespace SV_Split;

#include "WSVButton.h"

#include "../checkboxtreeview/WStateIcon.h"
//#define WIN32

///////////////////////////////////////////////////////////////////////////////////////////////////

//
const char svPassword[] = "password";
const int  svBufferSize = 1024 * 4;
//
typedef (ListDevice)(const char* szQuery, char* szReturn, int &nSize);
//
map<int, string, less<int> > lsDeviceId;

unsigned int RandIndex()
{
	unsigned int nPort = 0;
	unsigned int nMin  = 0x4000;
	unsigned int nMax  = 0x7FFF;
	srand((unsigned)time( NULL ));
	nPort = rand();
	nPort = nPort | nMin;
	nPort = nPort & nMax;

	return nPort;
}

//
string TrimStdString(string strIn)
{	
	if(!strIn.empty())
	{
		//�᲻�����?
		strIn.erase(strIn.begin(),strIn.begin() + strIn.find_first_not_of(' '));
		strIn.erase(strIn.begin() + strIn.find_last_not_of(' ') + 1,strIn.end());
		return strIn;
	}
	else
		return "";
}

//�ַ����滻
string ReplaceStdString(string strIn, string strFrom, string strTo)
{
	string strTmp = strIn;
	int nPos = strIn.find(strFrom, 0);
	int nLength = strFrom.length();

	if(nPos != -1)
	{
		strTmp = strIn.replace(nPos, nLength, strTo);
	}
	
	return strTmp;
}

//
bool checkEmail(string szMailList)
{
    if(szMailList.empty())
        return false;

    char * pTemp1 = NULL, * pTemp2 = NULL;
    
    pTemp1 = strchr(szMailList.c_str(), '@');
    if (!pTemp1)
        return false;
    
    if (*(++pTemp1) == '.')
        return false;
    
    pTemp2 = strchr(pTemp1, '.');
    if (!pTemp2)
        return false;

    return true;
}

bool checkPhoneNum(string szPhoneList)
{
	std::list<string> listMobile;
	std::list<string>::iterator OneList;
	char chSep = ',';
	SplitString(listMobile, szPhoneList, chSep);
	for(OneList=listMobile.begin();OneList!=listMobile.end();OneList++)
	{
		//		OutputDebugString(OneList->c_str());
		//if(!isNumeric(*OneList) || OneList->size() != 11)
		//	return false;
		//else 
			return true;
	}
	return false;
}

//m_AlertRuleAdd, m_AlertRuleDel, m_AlertRuleEdit, m_alertLogs,
bool GetUserRight(string strRight)
{
	bool bRight = false;
	string strSection = GetWebUserID();
	
	//����Ա��������Ȩ��
	if(GetIniFileInt(strSection, "nAdmin", -1, "user.ini") != -1)
		return true;

	if(GetIniFileInt(strSection, strRight, 0, "user.ini") == 1)
		bRight = true;
	else
		bRight = false;
	return bRight;
	//return true;
}

//
bool ParserToken(list<string >&pTokenList, const char * pQueryString, char *pSVSeps)
{
    char * token = NULL;
    // duplicate string
	char * cp = ::strdup(pQueryString);
    if (cp)
    {
        char * pTmp = cp;
        if (pSVSeps) // using separators
            token = strtok( pTmp , pSVSeps);
        else // using separators
			return false;
            //token = strtok( pTmp, chDefSeps);
        // every field
        while( token != NULL )
        {
            //triml(token);
            //AddListItem(token);
			pTokenList.push_back(token);
            // next field
            if (pSVSeps)
                token = strtok( NULL , pSVSeps);
            else
               return false;
				//token = strtok( NULL, chDefSeps);
        }
        // free memory
        free(cp);
    }
    return true;
}

//����Id�ֽ��pAlertTargetList
void WriteAlertTargerById(string strId, std::list<string> &pAlertTargetList)
{
	bool bAdd = true;
	string strTmp;

	//1.2��1.2.1ͬʱ��pAlertTargetList����鷳�ˣ���Ϊԭ���Ĵ��Եݹ鷽ʽ�洢���鴮��ǰ�� ������ִ������ ����Ͷ��ȡ�ɵķ����� �����-->���������⡣
	list <string>::iterator listitem;
	for(listitem = pAlertTargetList.begin(); listitem != pAlertTargetList.end(); listitem++)
	{
		strTmp = (*listitem);		

		//ȫƥ��
		if(strId == strTmp)
		{
			bAdd = false;
			break;
		}

		basic_string <char>::size_type indexCh2a = strId.find(strTmp.c_str());
		//�ҵ�����ͷƥ�䣨�����磺1.3.1.1��1.1����ƥ�����ַ�Ӧ���ǵ㣨�����磺1.3��1.33��
		if(indexCh2a != -1 && indexCh2a == 0 && strId.at(strTmp.length()) == '.')
		{
			bAdd = false;
			break;
		}
	}
	
	if(bAdd)
		pAlertTargetList.push_back(strId);
}

//
bool IsUserHasAlertRight(string strIndex)
{
	bool bReturn = true;	
	std::list<string> pTempTargetList;	
	list <string>::iterator listitem;

	string strSection = GetWebUserID();
	
	//����Ա��������Ȩ��
	if(GetIniFileInt(strSection, "nAdmin", -1, "user.ini") != -1)
		return true;
	
	//��ȡ�û��ܹ����Target��........
	string strGroupRight = GetIniFileString(strSection, "groupright", "", "user.ini");

	if(strGroupRight == "")
		return false;

	//�����û��ܹ����Target��=========
	std::list<string> pUserTargetList;
	ParserToken(pTempTargetList, strGroupRight.c_str(), ",");

	for(listitem = pTempTargetList.begin(); listitem != pTempTargetList.end(); listitem++)
	{		
		WriteAlertTargerById((*listitem), pUserTargetList);
	}

	//���ݷ�������û��ܹ����Target������hashƥ���+++++++++++
	map<string, int, less<string> > pUserTargetMap;
	string strNewUserTargetList = "";
	for(listitem = pUserTargetList.begin(); listitem != pUserTargetList.end(); listitem++)
	{
		strNewUserTargetList += (*listitem);
		strNewUserTargetList += ",";

		pUserTargetMap[(*listitem)] = 0;
	}


	//��ȡAlert����Target��..........
	string strAlertTarget = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini");
	
	if(strAlertTarget == "")
		return false;
	
	//����Alert����Target��===========
	std::list<string> pAlertTargetList;
	ParserToken(pTempTargetList, strAlertTarget.c_str(), ",");

	for(listitem = pTempTargetList.begin(); listitem != pTempTargetList.end(); listitem++)
	{		
		WriteAlertTargerById((*listitem), pAlertTargetList);
	}

	//��Alert���������Targetlistѭ��ƥ���û��ܹ����Target����map��ȷ���Ƿ���Ȩ�޹���ñ���|||||||||||||||||
	for(listitem = pAlertTargetList.begin(); listitem != pAlertTargetList.end(); listitem++)
	{
		bool bTargetMatch = false;
		string strTmpId = (*listitem);
		string strTmp = "";
		int nPos = 0;
		while(nPos != -1)
		{
			if(pUserTargetMap.find(strTmpId) != pUserTargetMap.end())
			{
				bTargetMatch = true;
				break;
			}
			else
			{			
				nPos = strTmpId.rfind(".");	
				strTmp = strTmpId.substr(0, nPos);
				strTmpId = strTmp;
			}
		}

		if(!bTargetMatch)
		{
			bReturn = false;
			break;
		}
	}

	return bReturn;
}

//
void GetInfoFromDevId(string strDevId, WComboBox * pScriptServer)
{
	string strDeviceType = "";
	string strDeviceValue = "";
	string strItemText = "";
	OBJECT objDevice = GetEntity(strDevId);
	if(objDevice != INVALID_VALUE)
	{
		MAPNODE devMapNode = GetEntityMainAttribNode(objDevice);
		if(devMapNode != INVALID_VALUE)
		{
			if(FindNodeValue(devMapNode,"sv_devicetype", strDeviceType))
			{
				if(strDeviceType == "_win" || strDeviceType == "_unix")
				{
					if(FindNodeValue(devMapNode,"sv_name", strDeviceValue))
					{
						strItemText = strDeviceValue;
					}
					
					strItemText += "(";
					strItemText += strDeviceType;
					strItemText += ")";
					
					pScriptServer->addItem(strItemText.c_str());
					
					//�洢strDevId<-->pScriptServer->index
					lsDeviceId[pScriptServer->count() - 1]=strDevId;
				}
			}
		}

		CloseEntity(objDevice);
	}
}

//�ݹ��ȡ�����µ������豸����ֵ��pScriptServer
void EnumGroup(std::string szIndex, WComboBox * pScriptServer)
{
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    
    if(!szIndex.empty())
    {
        OBJECT group = GetGroup(szIndex);
        if(group != INVALID_VALUE)
        {
    
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
					GetInfoFromDevId((*lstItem), pScriptServer);
                }            
            }
            
			if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    EnumGroup(szSubGroupID, pScriptServer);
                }                
            }

            CloseGroup(group);
        }        
    }
}

//
void InitScriptServer(WComboBox * pScriptServer)
{		
	lsDeviceId.clear();
	pScriptServer->addItem("127.0.0.1");
	lsDeviceId[0] = "127.0.0.1";
	PAIRLIST selist;
	PAIRLIST::iterator iSe;
	GetAllSVSEInfo(selist);
	for(iSe= selist.begin();iSe!=selist.end();iSe++)
	{
		OBJECT root = GetSVSE((*iSe).name);

		list<string> lsGroupID;
		list<string>::iterator lstItem;
		
		if (root != INVALID_VALUE)
		{
			if(GetSubEntitysIDBySE(root, lsGroupID))
			{
				for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
				{
					GetInfoFromDevId((*lstItem), pScriptServer);
				}
			}

			if(GetSubGroupsIDBySE(root, lsGroupID))
			{
				for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
				{
					EnumGroup((*lstItem), pScriptServer);
				}
			}

			CloseSVSE(root);
		}		
	}
}

//
string GetDeviceRunParam(string m_szDeviceIndex)
{
    string m_szQuery = "";
    //OBJECT objDevice = GetEntity(m_szDeviceIndex, m_szIDCUser, m_szIDCPwd);
	OBJECT objDevice = GetEntity(m_szDeviceIndex);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDeviceType = "";
            //list<string> lsDeviceParam;
            map<string, string, less<string> > lsDeviceParam;
            if(FindNodeValue(mainnode, "sv_devicetype", szDeviceType))
            {
                //OBJECT objDevice = GetEntityTemplet(szDeviceType, m_szIDCUser, m_szIDCPwd);
				OBJECT objDevice = GetEntityTemplet(szDeviceType);
                if(objDevice != INVALID_VALUE)
                {
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDevice, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName = "", szRun = "";
                            string szType = "";
                            FindNodeValue(objNode, "sv_name", szName);
                            FindNodeValue(objNode, "sv_run", szRun);
                            FindNodeValue(objNode, "sv_type", szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    CloseEntityTemplet(objDevice);
                }
            }
            //list<string>::iterator lstItem;
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue = "";
                FindNodeValue(mainnode, (lstItem->first), szValue);
                if((lstItem->second).compare(svPassword) == 0)
                {
                    char szOutput[512] = {0};
                    Des des;
                    if(des.Decrypt(szValue.c_str(), szOutput))
                        szValue = szOutput;
                }
                m_szQuery = m_szQuery + (lstItem->first) + "=" + szValue + "\v";
            }
        }
        CloseEntity(objDevice);
    }

	return m_szQuery;
}

//
void EidtQueryString(string &szQuery, char* pszQueryString)
{    
    if(pszQueryString)
    {
        strcpy(pszQueryString , szQuery.c_str());
        char *pPos = pszQueryString;
        while((*pPos) != '\0' )
        {
            if((*pPos) == '\v')
                (*pPos) = '\0';
            pPos ++;
        }
    }
}

//
void ParserReturnInList(const char * szReturn, list<string> &lsReturn)
{
    const char * pPos = szReturn;
    while(*pPos != '\0')
    {
        int nSize =strlen(pPos);
        lsReturn.push_back(pPos);
        pPos = pPos + nSize + 1;
    }
}


//Ϊ���Ticket #112 ��������ECC�ʼ��������ⶨ�����������������롣
//�պ� 2007-08-02

//+++++++++++++++++++++++++++�������ӿ�ʼ  �պ� 2007-08-02+++++++++++++++++++++++++++
//���ݡ��Ƿ�ʹ������ģ�塱�Ƿ�ѡ�������������ʼ�����ģ�塱�Ƿ���Ա༭���Ƿ���Ч
void CAlertList::ShowEdit()
{
	if(pCheckBox->isChecked())
		pAlertEmailTitle->enable();
	else
		pAlertEmailTitle->disable();
}
//+++++++++++++++++++++++++++�������ӽ���  �պ� 2007-08-02+++++++++++++++++++++++++++

/////////////////////////////////////////////////////////////////////////////////////

//����list�Ż�ȡΨһ��index
string CAlertList::GetOnlyIndex(int nList)
{
	string strIndex = "";
	int index = 0;
	while(true)
	{
		index = RandIndex();

		char chItem[32]  = {0};
		sprintf(chItem, "%d", index);
		strIndex = chItem;
	    SVTableRow * pRow = NULL;
		pRow = m_svAlertList.Row(chItem);
		
		if (pRow)
		{
			continue;
		}
		else
			break;
	}
	
	return strIndex;
}

//
CAlertList::CAlertList(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Alert_Rule",strMainTitle);
			FindNodeValue(ResNode,"IDS_Alert_List",strAlertTitle);
			FindNodeValue(ResNode,"IDS_Add_Alert",strAlertAdd);
			FindNodeValue(ResNode,"IDS_Edit",strAlertEditLabel);
			FindNodeValue(ResNode,"IDS_Allown_Alert",strAlertEnable);
			FindNodeValue(ResNode,"IDS_Deny_Alert",strAlertDisable);
			FindNodeValue(ResNode,"IDS_History_Alert",strAlertHistoryLabel);
			FindNodeValue(ResNode,"IDS_Alert_Name",strAlertNameLabel);
			FindNodeValue(ResNode,"IDS_Alert_Type",strAlertDesLabel);
			FindNodeValue(ResNode,"IDS_Delete_Alert",strAlertDel);
			FindNodeValue(ResNode,"IDS_Delete_Alert_Affirm",strIsAlertDel);
			FindNodeValue(ResNode,"IDS_History_Alert",strAlertHistoryTiltle);
			FindNodeValue(ResNode,"IDS_Return",strReturn);
			FindNodeValue(ResNode,"IDS_Forward",strForward);
			FindNodeValue(ResNode,"IDS_Back",strBack);
			FindNodeValue(ResNode,"IDS_Alert_Time",strHTimeLabel);
			FindNodeValue(ResNode,"IDS_Alert_Name",strHAlertNameLabel);
			FindNodeValue(ResNode,"IDS_Device_Name",strHDeveiceNameLabel);
			FindNodeValue(ResNode,"IDS_Monitor_Name",strHMonitorNameLabel);
			FindNodeValue(ResNode,"IDS_Alert_Receiver",strHAlertReceiveLabel);
			FindNodeValue(ResNode,"IDS_Alert_Type",strHAlertTypeLabel);
			FindNodeValue(ResNode,"IDS_Alert_State",strHAlertStateLabel);
			FindNodeValue(ResNode,"IDS_Alert_Check",strAlertSelTitle);
			FindNodeValue(ResNode,"IDS_Alert_Email",strEmail);
			FindNodeValue(ResNode,"IDS_Alert_SMS",strSms);
			FindNodeValue(ResNode,"IDS_Alert_Script1",strScript);
			FindNodeValue(ResNode,"IDS_Alert_Sound1",strSound);
			FindNodeValue(ResNode,"IDS_Edit_Alert",strBaseTitle);
			FindNodeValue(ResNode,"IDS_Alert_Name",strAlertNameTitle);
			FindNodeValue(ResNode,"IDS_Alert_Name_Description",strAlertNameDes);
			FindNodeValue(ResNode,"IDS_Alert_Name_Error",strAlertNameError);
			FindNodeValue(ResNode,"IDS_Alert_Target",strAlertTargetTitle);
			FindNodeValue(ResNode,"IDS_Alert_Target_Description",strAlertTargetDes);
			FindNodeValue(ResNode,"IDS_Alert_Target_Empty",strAlertTargetError);
			FindNodeValue(ResNode,"IDS_Update_Count",strAlertUpgradeTitle);
			FindNodeValue(ResNode,"IDS_Update_Number",strAlertUpgradeError);
			FindNodeValue(ResNode,"IDS_Update_Description",strAlertUpgradeDes);
			FindNodeValue(ResNode,"IDS_Update_Receiver",strAlertUpgradeToTitle);
			FindNodeValue(ResNode,"IDS_Update_Receiver_Description",strAlertUpgradeToDes);
			FindNodeValue(ResNode,"IDS_Update_Receiver_Description1",strAlertUpgradeToDes1);
			FindNodeValue(ResNode,"IDS_Stop_Count",strAlertStopTitle);
			FindNodeValue(ResNode,"IDS_Stop_Number",strAlertStopError);
			FindNodeValue(ResNode,"IDS_Stop_Description",strAlertStopDes);
			FindNodeValue(ResNode,"IDS_Send_Ready",strCondTitle);
			FindNodeValue(ResNode,"IDS_Alert_Event",strEventNameTitle);
			FindNodeValue(ResNode,"IDS_Alert_Event_Type",strEventNameDes);
			FindNodeValue(ResNode,"IDS_Send_Rule",strWhenSetingTitle);
			FindNodeValue(ResNode,"IDS_Send_Ready",strWhenDes);
			FindNodeValue(ResNode,"IDS_Send_Ready_Error",strWhenError);
			FindNodeValue(ResNode,"IDS_Send_Alert_Often",strAlwaysCondTitle);
			FindNodeValue(ResNode,"IDS_Send_Alert_Often1",strAlwaysCond1);
			FindNodeValue(ResNode,"IDS_Send_Alert_Often2",strAlwaysCond2);
			FindNodeValue(ResNode,"IDS_Send_Alert_Description",strOnlyCondTitle);
			FindNodeValue(ResNode,"IDS_Send_Alert_Only1",strOnlyCond1);
			FindNodeValue(ResNode,"IDS_Send_Alert_Only2",strOnlyCond2);
			FindNodeValue(ResNode,"IDS_Send_Alert_Check",strSelectCondTitle);
			FindNodeValue(ResNode,"IDS_Send_Alert_Check1",strSelectCond1);
			FindNodeValue(ResNode,"IDS_Send_Alert_Check2",strSelectCond2);
			FindNodeValue(ResNode,"IDS_Send_Alert_Check3",strSelectCond3);
			FindNodeValue(ResNode,"IDS_Alert_Group",strGroupCondTitle);
			FindNodeValue(ResNode,"IDS_Alert_Group1",strGroupCond1);
			FindNodeValue(ResNode,"IDS_Alert_Email_Paramer",strEmailAlertTitle);
			FindNodeValue(ResNode,"IDS_Alert_Email_Receive_Address",strEmailAdressTitle);
			FindNodeValue(ResNode,"IDS_Alert_Email_Receive_Address_Description",strEmailAdressDes);
			FindNodeValue(ResNode,"IDS_Alert_Email_Receive_Address_Error",strEmailAdressError);
			FindNodeValue(ResNode,"IDS_Edit_Email_Alert_Paramer",strEmailAdressSet);
			FindNodeValue(ResNode,"IDS_Email_Template",strEmailTemplateTitle);
			FindNodeValue(ResNode,"IDS_Email_Template_Description",strEmailTemplateDes);
			FindNodeValue(ResNode,"IDS_Email_Template_Config",strEmailTemplateSet);
			FindNodeValue(ResNode,"IDS_SMS_Alert_Paramer",strSmsAlertTitle);
			FindNodeValue(ResNode,"IDS_Alert_Receive_Phone",strPhoneNumberTitle);
			FindNodeValue(ResNode,"IDS_Alert_Receive_Phone_Description",strPhoneNumberDes);
			FindNodeValue(ResNode,"IDS_Alert_Receive_Phone_Error",strPhoneNumberError);
			FindNodeValue(ResNode,"IDS_Send_Mode",strSendModeTitle);
			FindNodeValue(ResNode,"IDS_Send_ModeWeb",strSendModeWeb);
			FindNodeValue(ResNode,"IDS_Send_ModeCom",strSendModeCom);
			FindNodeValue(ResNode,"IDS_Send_Mode_Description",strSendModeDes);
			FindNodeValue(ResNode,"IDS_SMS_Template",strSmsTemplateTitle);
			FindNodeValue(ResNode,"IDS_SMS_Template_Description",strSmsTemplateDes);
			FindNodeValue(ResNode,"IDS_SMS_Template_Config",strSmsTemplateSet);
			FindNodeValue(ResNode,"IDS_Sound_Alert_Paramer",strSoundAlertTitle);
			FindNodeValue(ResNode,"IDS_Sound_File_Config",strSoundSeting);
			FindNodeValue(ResNode,"IDS_Sound_File_Config_Description",strSoundSetingDes);
			FindNodeValue(ResNode,"IDS_Server_Name",strSoundServerTitle);
			FindNodeValue(ResNode,"IDS_Server_Name_Description",strSoundServerDes);
			FindNodeValue(ResNode,"IDS_Login_Name",strLoginNameTitle);
			FindNodeValue(ResNode,"IDS_Login_Name_Description",strLoginNameDes);
			FindNodeValue(ResNode,"IDS_Login_Password",strLoginPwdTitle);
			FindNodeValue(ResNode,"IDS_Login_Password_Description",strLoginPwdDes);
			FindNodeValue(ResNode,"IDS_Script_Alert_Paramer",strScriptAlertTitle);
			FindNodeValue(ResNode,"IDS_Script_Alert_Server",strScriptServerTitle);
			FindNodeValue(ResNode,"IDS_Script_Alert_Server_Description",strScriptServerDes);
			FindNodeValue(ResNode,"IDS_Script_Alert_Server",strScriptServerSeting);
			FindNodeValue(ResNode,"IDS_Script_Check",strScriptTitle);
			FindNodeValue(ResNode,"IDS_Script_Check_Description",strScriptDes);
			FindNodeValue(ResNode,"IDS_Script_Alert_Server",strScriptSet);
			FindNodeValue(ResNode,"IDS_Paramer_Other",strScriptParamTitle);
			FindNodeValue(ResNode,"IDS_Paramer_Other_Description",strScriptParamDes);
			FindNodeValue(ResNode,"IDS_Enable1",strEnable);
			FindNodeValue(ResNode,"IDS_Disable",strDisable);
			FindNodeValue(ResNode,"IDS_Normal",strNormal);
			FindNodeValue(ResNode,"IDS_Warnning",strWarning);
			FindNodeValue(ResNode,"IDS_Error",strError);
			FindNodeValue(ResNode,"IDS_Other",strOther);
			FindNodeValue(ResNode,"IDS_Alert_Area",strAlertArea);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Ini",strAlertRecordIni);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page",strPage);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Count",strRecordCount);
			FindNodeValue(ResNode,"IDS_Alert_Log_Record_Page_Count",strPageCount);
			FindNodeValue(ResNode,"IDS_Alert_Area_Not_Empty",strAlertAreaNotEmpty);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip);
			FindNodeValue(ResNode,"IDS_No_Sort_Record",strNoSortRecord); 
			FindNodeValue(ResNode,"IDS_Alert_Config_Null",strNoAlertItem); 
			FindNodeValue(ResNode,"IDS_Delete",strTypeDelete); 
			FindNodeValue(ResNode,"IDS_Add_Title",strTypeAdd);
			FindNodeValue(ResNode,"IDS_Enable",strEnableType);
			FindNodeValue(ResNode,"IDS_Disable",strDisableType);			
			FindNodeValue(ResNode,"IDS_UserSelfDefine",strSelfDefine);			
			FindNodeValue(ResNode,"IDS_ConfirmCancel",szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",szButMatch);

			FindNodeValue(ResNode,"IDS_All_Select", szTipSelAll);
			FindNodeValue(ResNode,"IDS_None_Select", szTipNotSelAll);
			FindNodeValue(ResNode,"IDS_Invert_Select", szTipInvSel);
			FindNodeValue(ResNode,"IDS_Delete", szTipDel);

			FindNodeValue(ResNode,"IDS_Save",strSave);
			FindNodeValue(ResNode,"IDS_Save_And_Add",strSaveAndAdd);
			FindNodeValue(ResNode,"IDS_Cancel",strCancel);

			FindNodeValue(ResNode,"IDS_Alert_List_NULL",strAlertNullList);
			FindNodeValue(ResNode,"IDS_Alert_History_List_NULL",strHAlertNullList);
		
			FindNodeValue(ResNode,"IDS_Del_Con",strDelCon);

			FindNodeValue(ResNode,"IDS_Save_Add",strSaveAdd);
			FindNodeValue(ResNode,"IDS_Cancel_Add1",strCancelAdd);
			FindNodeValue(ResNode,"IDS_Refresh_GUI",strRefresh1);

			//Ϊ���Ticket #112 ��������ECC�ʼ��������ⶨ�����������������롣
			//�պ� 2007-08-02

			//+++++++++++++++++++++++++++�������ӿ�ʼ  �պ� 2007-08-02+++++++++++++++++++++++++++
			//��ȡ��Դ
			FindNodeValue(ResNode,"IDS_Email_Subject_Template",strEmailSubjectTemplate);
			FindNodeValue(ResNode,"IDS_Email_Subject_Template_Check",strEmailSubjectTemplateCheck);
			//+++++++++++++++++++++++++++�������ӽ���  �պ� 2007-08-02+++++++++++++++++++++++++++
		}
		CloseResource(objRes);
	}

	nCurPage = 0;
	nTotalPage = 0;
	nPageCount = 30;

	strSendModeSelfDefine = "SelfDefine";
	strEnable = "Enable";
	strGolobalType = "";
	strOldAlertName = "";

	bSaveAndAdd = false;
	bHistoryTable = false;
	//pAlertTargerTree = new CCheckBoxTreeView(0);
		//pAlertTargerTree->InitTree("",false, true, false, "1");
	iType = 0;

	ShowMainTable();
	p_AlertConditionTable = NULL;
	pSubTreeTable = NULL;
}

//
CAlertList::~CAlertList(void)
{

}

//��ʼ��������
void CAlertList::ShowMainTable()
{
	
	/**

	//new WText("<div id='view_panel' class='panel_view'>", this);

	pAlertAddTable = NULL;

	pMainTable = new CMainTable(this, strMainTitle);

	//�����б�
	pAlertTable = new CFlexTable(pMainTable->elementAt(2, 0), strAlertTitle);	
	
	pAlertListTable = new WTable(pAlertTable->GetContentTable()->elementAt(0,0));
	pAlertListTable ->setStyleClass("t3");

	nullTable = new WTable(pAlertTable->GetContentTable()->elementAt(1, 0));
	nullTable ->setStyleClass("t3");

	AddColum(pAlertListTable);

	//
	pAlertTable->AddGroupOperate(pAlertTable->GetContentTable(), strAlertDel);

	
	//new WText("&nbsp&nbsp&nbsp",(WContainerWidget *)(WContainerWidget *)pAlertTable->m_pGroupOperate->elementAt(0, 5));
 //   pEnableAlert = new WText(strAlertEnable, (WContainerWidget *)(WContainerWidget *)pAlertTable->m_pGroupOperate->elementAt(0, 5));
 //   if (pEnableAlert)
 //   {
 //       pEnableAlert->setStyleClass("nullLink");
 //   }

	pEnableAlert = new WImage("../Images/enable.gif", (WContainerWidget *)pAlertTable->m_pGroupOperate->elementAt(0, 5));
	pEnableAlert->setStyleClass("helpimg");
	pEnableAlert->setToolTip(strAlertEnable);
	connect(pEnableAlert, SIGNAL(clicked()), this, SLOT(EnableAlert()));

	//new WText("&nbsp&nbsp&nbsp",(WContainerWidget *)(WContainerWidget *)pAlertTable->m_pGroupOperate->elementAt(0, 6));
 //   pDisableAlert = new WText(strAlertDisable, (WContainerWidget *)(WContainerWidget *)pAlertTable->m_pGroupOperate->elementAt(0, 6));
 //   if (pDisableAlert)
 //   {
 //       pDisableAlert->setStyleClass("nullLink");
 //   }

	pDisableAlert= new WImage("../Images/disable.gif", (WContainerWidget *)pAlertTable->m_pGroupOperate->elementAt(0, 6));
    pDisableAlert->setStyleClass("helpimg");
    pDisableAlert->setToolTip(strAlertDisable);
	connect(pDisableAlert, SIGNAL(clicked()), this, SLOT(DisableAlert()));

	//
	pAlertTable->AddGroupAddBtn(pAlertTable->GetContentTable(), strAlertAdd);

	
	connect(&m_alertMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditAlert(const std::string)));
	//connect(pEmailBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(EmailBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	connect(pAlertTable->pAdd, SIGNAL(clicked()), this, SLOT(AddAlert()));
	connect(pAlertTable->pDel , SIGNAL(clicked()),this, SLOT(BeforeDelAlert()));
	connect(pAlertTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
	connect(pAlertTable->pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
	connect(pAlertTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));

	if(!GetUserRight("m_AlertRuleAdd"))
		pAlertTable->pAdd->hide();
	else
		pAlertTable->pAdd->show();

	if(!GetUserRight("m_AlertRuleDel"))
		pAlertTable->pDel->hide();
	else
		pAlertTable->pDel->show();

	if(!GetUserRight("m_AlertRuleEdit"))
	{
		pDisableAlert->hide();
		pEnableAlert->hide();
	}
	else
	{
		pDisableAlert->show();
		pEnableAlert->show();	
	}
	pAlertTable->pAdd->setStyleClass("wizardbutton");
	//pAlertTable->pAdd->setName("AddRule");
	
	//������־
	connect(&m_historyMapper, SIGNAL(mapped(const std::string)), this, SLOT(AlertHistory(const std::string)));		

	pHistoryTable = new CFlexTable(pMainTable->elementAt(3, 0), strAlertHistoryTiltle);	
	pHistoryTable->InitGroupOperate(pHistoryTable->GetContentTable());	

	pBack = new WImage("../Images/previous.gif", (WContainerWidget *)pHistoryTable->m_pGroupOperate->elementAt(0, 0));
	pBack->setStyleClass("helpimg");
	pBack->setToolTip(strBack);
	connect(pBack, SIGNAL(clicked()), this, SLOT(HistoryBack()));

	pForward = new WImage("../Images/next.gif", (WContainerWidget *)pHistoryTable->m_pGroupOperate->elementAt(0, 1));
	pForward->setStyleClass("helpimg");
	pForward->setToolTip(strForward);
	connect(pForward, SIGNAL(clicked()), this, SLOT(HistoryForward()));

	//pTextTipInfo = new WText("ҳ��0/������0", (WContainerWidget *)pHistoryTable->m_pGroupOperate->elementAt(0, 3));
	WTable * pTable = new WTable((WContainerWidget *)pHistoryTable->m_pGroupOperate->elementAt(0, 2));
	pTable->resize(300, WLength(100,WLength::Percentage));
	pTextTipInfo = new WText(strAlertRecordIni, (WContainerWidget *)pTable->elementAt(0, 1));
	//pHistoryTable->m_pGroupOperate->elementAt(0, 3)->setContentAlignment(AlignLeft);
	//pHistoryTable->m_pGroupOperate->elementAt(0, 3)->resize(300,WLength(100,WLength::Percentage));

	pHistoryTable->AddGroupAddBtn(pHistoryTable->GetContentTable(), strReturn);
	connect(pHistoryTable->pAdd, SIGNAL(clicked()), this, SLOT(HistoryReturnBtn()));

	pHistoryListTable = new WTable(pHistoryTable->GetContentTable()->elementAt(0, 0));
	pHistoryListTable ->setStyleClass("t3");

	nullTable1 = new WTable(pHistoryTable->GetContentTable()->elementAt(1, 0));
	nullTable1 ->setStyleClass("t3");

	AddHistoryColum(pHistoryListTable);

	//����ѡ��
	pAlertSelectTable = new CFlexTable(pMainTable->elementAt(4, 0), strAlertSelTitle);	
	WPushButton * pEmailBtn = new WPushButton(strEmail, (WContainerWidget *)pAlertSelectTable->GetContentTable()->elementAt(0, 0));	
    pEmailBtn->setStyleClass("bg_button");
    pEmailBtn->setToolTip(strEmail);
	//pEmailBtn->setName("EmailBtn");
	connect(pEmailBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(EmailBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	WPushButton * pSmsBtn = new WPushButton(strSms, (WContainerWidget *)pAlertSelectTable->GetContentTable()->elementAt(0, 1));
    pSmsBtn->setStyleClass("bg_button");
    pSmsBtn->setToolTip(strSms);
	//pSmsBtn->setName("SmsBtn");
	connect(pSmsBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(SmsBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	WPushButton * pScriptBtn = new WPushButton(strScript, (WContainerWidget *)pAlertSelectTable->GetContentTable()->elementAt(0, 2));
    pScriptBtn->setStyleClass("bg_button");
    pScriptBtn->setToolTip(strScript);
	//pScriptBtn->setName("ScriptBtn");
	connect(pScriptBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(ScriptBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	WPushButton * pSoundBtn = new WPushButton(strSound, (WContainerWidget *)pAlertSelectTable->GetContentTable()->elementAt(0, 3));
	pSoundBtn->setStyleClass("bg_button");
    pSoundBtn->setToolTip(strSound);
	//pSoundBtn->setName("SoundBtn");
	connect(pSoundBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(SoundBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	connect(pMainTable->pBackBtn, SIGNAL(clicked()), this, SLOT(BackBtn()));
	
	//WPushButton * pSelfDefineBtn = new WPushButton(strSelfDefine, (WContainerWidget *)pAlertSelectTable->GetContentTable()->elementAt(0, 4));
	//pSelfDefineBtn->setStyleClass("bg_button");
	//pSelfDefineBtn->setToolTip(strSelfDefine);
	//connect(pSelfDefineBtn, SIGNAL(clicked()), "showbar();", this, SLOT(SelfDefineBtn()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	//connect(pMainTable->pBackBtn, SIGNAL(clicked()), this, SLOT(BackBtn()));
	

	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState;
	int  nAdmin = -1;
	
	//��ini��ȡ�����б�
	if(GetIniFileSections(keylist, "alert.ini"))
	{
		//��ini��ʼ�������б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			if(IsUserHasAlertRight(*keyitem))
			{
				//��ini������
				strIndex = GetIniFileString((*keyitem), "nIndex", "", "alert.ini");
				strAlertName = GetIniFileString((*keyitem), "AlertName", "", "alert.ini");
				strAlertType = GetIniFileString((*keyitem), "AlertType", "" , "alert.ini");
				strAlertCategory = GetIniFileString((*keyitem), "AlertCategory", "", "alert.ini");
				strAlertState = GetIniFileString((*keyitem), "AlertState", "", "alert.ini");
		
				AddAlertItem(strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState);
			}
		}
	}


	//initAddAlertTable();
	//pAlertAddTable->hide();
	pAlertSelectTable->hide();
	pHistoryTable->hide();
	//pMainTable->hide();
	
	//���ذ�ť
	pHideButton = new WPushButton("hide button",this);
	if(pHideButton)
	{
		pHideButton->setToolTip("Hide Button");
		connect(pHideButton,SIGNAL(clicked()),this,SLOT(DelAlert()));
		pHideButton->hide();
		}
		**/

	//����
	pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)this);
	pTranslateBtn->setToolTip(strTranslateTip);
	pTranslateBtn->hide();

	new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)this);

	pExChangeBtn = new WPushButton(strRefresh, (WContainerWidget *)this);
	pExChangeBtn->setToolTip(strRefreshTip);
	pExChangeBtn->hide();

	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pExChangeBtn->show();
		connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}
	initMaitTable();
}

void CAlertList::AddJsParam(const std::string name, const std::string value, WContainerWidget *parent)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, parent);
}

//init������
void CAlertList::initMaitTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	

	mainTable2 = new WTable(this);	
	mainTable2->hide();
	initAlertSelect();
	AddJsParam("uistyle", "treepan", mainTable2->elementAt(0,0));
	AddJsParam("fullstyle", "true", mainTable2->elementAt(0,0));
	AddJsParam("bGeneral", "false", mainTable2->elementAt(0,0));
	//new WText("<SCRIPT language='JavaScript'>addLoadEvent(_OnLoad())</SCRIPT>", mainTable2->elementAt(0,0));
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", mainTable2->elementAt(0,0));

	

	mainTable = new WTable(this);
	mainTable->hide();

	new WText("<div id='view_panel1' class='panel_view'>", mainTable->elementAt(0,0));
	p_MainTable = new WSVMainTable(mainTable->elementAt(0,0), strMainTitle, false);
	initAlertListTable();
	new WText("</div>" , mainTable->elementAt(0,0));
	AddJsParam("uistyle", "viewpan", mainTable->elementAt(0,0));
	AddJsParam("fullstyle", "true", mainTable->elementAt(0,0));
	AddJsParam("bGeneral", "false", mainTable->elementAt(0,0));
	//new WText("<SCRIPT language='JavaScript'>addLoadEvent(_OnLoad())</SCRIPT>", mainTable->elementAt(0,0));
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", mainTable->elementAt(0,0));

	
	mainTable1 = new WTable(this);
	mainTable1->hide();

	new WText("<div id='view_panel2' class='panel_view'>", mainTable1->elementAt(0,0));
	p_MainTable1 = new WSVMainTable(mainTable1->elementAt(0,0), strMainTitle, false);
	initHistoryTable();
	new WText("</div>" , mainTable1->elementAt(0,0));
	//AddJsParam("listheight", strListHeights, mainTable1->elementAt(0,0));
	//AddJsParam("listtitle", strListTitles, mainTable1->elementAt(0,0));
	//AddJsParam("listpan", strListPans, mainTable1->elementAt(0,0));
	AddJsParam("uistyle", "viewpan", mainTable1->elementAt(0,0));
	AddJsParam("fullstyle", "true", mainTable1->elementAt(0,0));
	AddJsParam("bGeneral", "false", mainTable1->elementAt(0,0));
	//new WText("<SCRIPT language='JavaScript'>addLoadEvent(_OnLoad())</SCRIPT>", mainTable1->elementAt(0,0));
	new WText("<SCRIPT language='JavaScript' src='/Script2.js'></SCRIPT>", mainTable1->elementAt(0,0));

	mainTable->show();
}

//�����б�
void CAlertList::initAlertListTable()
{
	strListHeights = "";
	strListPans = "";
	strListTitles = "";

	p_AlertTable = new WSVFlexTable((WContainerWidget *)p_MainTable->GetContentTable()->elementAt(0,0), List, strAlertTitle);	
	WSVFlexTable *p_AlertListTable = p_AlertTable;
	//p_AlertListTable->SetDivId("listpan1");
	if (p_AlertListTable->GetContentTable())
	{
	/*	strListHeights += "350";
		strListHeights += ",";
		strListPans += p_AlertListTable->GetDivId();
		strListPans += ",";
		strListTitles +=  p_AlertListTable->dataTitleTable->formName();
		strListTitles += ",";*/

		p_AlertListTable->AppendColumn("",WLength(40,WLength::Pixel));
		p_AlertListTable->SetDataRowStyle("table_data_grid_item_img");
		p_AlertListTable->AppendColumn(strAlertNameLabel,WLength(25,WLength::Percentage));
		p_AlertListTable->SetDataRowStyle("table_data_grid_item_text");
		p_AlertListTable->AppendColumn(strAlertDesLabel,WLength(25,WLength::Percentage));
		p_AlertListTable->SetDataRowStyle("table_data_grid_item_text");
		p_AlertListTable->AppendColumn(strHAlertStateLabel,WLength(20,WLength::Percentage));
		p_AlertListTable->SetDataRowStyle("table_data_grid_item_text");
		p_AlertListTable->AppendColumn(strAlertHistoryLabel,WLength(20,WLength::Percentage));
		p_AlertListTable->SetDataRowStyle("table_data_grid_item_img");
		p_AlertListTable->AppendColumn(strAlertEditLabel,WLength(10,WLength::Percentage));
		p_AlertListTable->SetDataRowStyle("table_data_grid_item_img");
	}

	//ȫѡ,��ѡ,ȫ��ѡ
	p_AlertListTable->AddStandardSelLink(szTipSelAll, szTipNotSelAll, szTipInvSel);
	WTable *pTbl;

	p_AlertListTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
	p_AlertListTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
	pTbl = new WTable(p_AlertListTable->GetActionTable()->elementAt(0,1));

	pTbl->setStyleClass("widthauto");

	//ɾ������
	p_Del = new WSVButton(pTbl->elementAt(0,0), szTipDel, "button_bg_del.png", "", false);
	connect(p_Del , SIGNAL(clicked()),this, SLOT(BeforeDelAlert()));
	//��������
	p_EnableAlert = new WSVButton(pTbl->elementAt(0,1), strAlertEnable, "button_bg_start.png", "", false);
	connect(p_EnableAlert, SIGNAL(clicked()), this, SLOT(EnableAlert()));
	//�رձ���
	p_DisableAlert = new WSVButton(pTbl->elementAt(0,2), strAlertDisable, "button_bg_stop.png", "", false);
	connect(p_DisableAlert, SIGNAL(clicked()), this, SLOT(DisableAlert()));

	//���ذ�ť
	pHideButton = new WPushButton("hide button",this);
	if(pHideButton)
	{
		pHideButton->setToolTip("Hide Button");
		connect(pHideButton,SIGNAL(clicked()),this,SLOT(DelAlert()));
		pHideButton->hide();
	}

	p_AlertListTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);
	p_Add = new WSVButton(p_AlertListTable->GetActionTable()->elementAt(0,2), strAlertAdd, "button_bg_add_black.png", strAlertAdd, true);
	//connect(btn, SIGNAL(clicked()), this, SLOT(AddGroup()));
	//connect(btn, SIGNAL(clicked()), "ShowTreeTable(true);" ,this, SLOT(AddGroup()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	//connect(p_Add, SIGNAL(clicked()), this, SLOT(AddAlert()));
	connect( p_Add, SIGNAL(clicked()),"showbar();" ,this, SLOT(AddAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	connect(&m_alertMapper, SIGNAL(mapped(const std::string)), this, SLOT(EditAlert(const std::string)));
	//connect(pEmailBtn, SIGNAL(clicked()), "showbar();" ,this, SLOT(EmailBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	connect(p_AlertListTable->pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
	connect(p_AlertListTable->pSelReverse, SIGNAL(clicked()), this, SLOT(SelInvert()));
	connect(p_AlertListTable->pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
	connect(&m_historyMapper, SIGNAL(mapped(const std::string)), this, SLOT(AlertHistory(const std::string)));	

	if(!GetUserRight("m_AlertRuleAdd"))
		p_Add->hide();
	else
		p_Add->show();

	if(!GetUserRight("m_AlertRuleDel"))
		p_Del->hide();
	else
		p_Del->show();

	if(!GetUserRight("m_AlertRuleEdit"))
	{
		p_DisableAlert->hide();
		p_EnableAlert->hide();
	}
	else
	{
		p_DisableAlert->show();
		p_EnableAlert->show();	
	}
	//svtable + edit user ini
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState;
	int  nAdmin = -1;

	//��ini��ȡ�����б�
	if(GetIniFileSections(keylist, "alert.ini"))
	{
		//��ini��ʼ�������б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			int numRow = 0;
			if(IsUserHasAlertRight(*keyitem))
			{
				std::string section = *keyitem;
				Alert_LIST list;

				//��ini������
				strIndex = GetIniFileString((*keyitem), "nIndex", "", "alert.ini");
				strAlertName = GetIniFileString((*keyitem), "AlertName", "", "alert.ini");
				strAlertType = GetIniFileString((*keyitem), "AlertType", "" , "alert.ini");
				strAlertCategory = GetIniFileString((*keyitem), "AlertCategory", "", "alert.ini");
				strAlertState = GetIniFileString((*keyitem), "AlertState", "", "alert.ini");

				//���ɽ���
				numRow = p_AlertListTable->GeDataTable()->numRows();
				p_AlertListTable->InitRow(numRow);
				char tmp[1024];
				sprintf(tmp,"%d \n",numRow);
				OutputDebugString(tmp);

				//ѡ��
				WCheckBox * pSelect = new WCheckBox("", (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow, 0));
				p_AlertListTable->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);

				//�ı�
				WText * pAlertNameText = new WText(strAlertName, (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 2));
				p_AlertListTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);

				string strDes = "";
				if(strAlertState == strDisable)
					strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
				else
					strDes = strAlertType;
				//OutputDebugString((strIndex+","+strAlertName+","+strAlertType+","+strAlertCategory+","+strAlertState+","+strDisable+"\n").c_str());
				WText * pAlertDesText = new WText(strDes, (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 4));
				p_AlertListTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);

				WText * pAlertCategoryText = new WText(strAlertCategory, (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 6));
				p_AlertListTable->GeDataTable()->elementAt(numRow , 6)->setContentAlignment(AlignCenter);

				WImage *pHistory = new WImage("../Images/historyalert.gif", (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 8));
				p_AlertListTable->GeDataTable()->elementAt(numRow , 8)->setContentAlignment(AlignCenter);
				pHistory->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
				m_historyMapper.setMapping(pHistory, strIndex);
				connect(pHistory, SIGNAL(clicked()), &m_historyMapper, SLOT(map()));

				WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 10));
				p_AlertListTable->GeDataTable()->elementAt(numRow , 10)->setContentAlignment(AlignCenter);
				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
				m_alertMapper.setMapping(pEdit, strIndex); 
				connect(pEdit, SIGNAL(clicked()),"showbar();",  &m_alertMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

				WText * pAlertTypeText = new WText(strAlertType, (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 12));
				pAlertTypeText->hide();
				WText * pAlertStateText = new WText(strAlertState, (WContainerWidget*)p_AlertListTable->GeDataTable()->elementAt(numRow , 14));
				pAlertStateText->hide();


				if(!GetUserRight("m_AlertRuleEdit"))
					pEdit->hide();
				else
					pEdit->show();

				if(!GetUserRight("m_alertLogs"))
					pHistory->hide();
				else
					pHistory->show();

				list.pSelect = pSelect;
				list.pAlertNameText = pAlertNameText;
				list.pAlertDesText = pAlertDesText;
				list.pAlertCategoryText = pAlertCategoryText;
				list.pAlertTypeText = pAlertTypeText;
				list.pAlertStateText = pAlertStateText;
				list.id = section;
				m_pListAlert.push_back(list);
			}
		}
	}
	p_AlertListTable->SetNullTipInfo(strAlertNullList);
	if (m_pListAlert.size() == 0)
	{
		p_AlertListTable->ShowNullTip();
	}
	else
	{
		p_AlertListTable->HideNullTip();
	}
}

void CAlertList::initHistoryTable()
{
	//������־	
	//��ʷ��¼
	p_HistoryTable = new WSVFlexTable( p_MainTable1->GetContentTable()->elementAt(0, 0), List, strAlertHistoryTiltle);

	//p_HistoryTable->SetDivId("listpan2");
	if (p_HistoryTable->GetContentTable())
	{
	/*	strListHeights += "350";
		strListHeights += ",";
		strListPans += p_HistoryTable->GetDivId();
		strListPans += ",";
		strListTitles +=  p_HistoryTable->dataTitleTable->formName();
		strListTitles += ",";*/

		p_HistoryTable->AppendColumn(strHTimeLabel,WLength(25, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
		p_HistoryTable->AppendColumn(strHAlertNameLabel,WLength(12, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
		p_HistoryTable->AppendColumn(strHDeveiceNameLabel,WLength(12, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
		p_HistoryTable->AppendColumn(strHMonitorNameLabel,WLength(12, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
		p_HistoryTable->AppendColumn(strHAlertTypeLabel,WLength(12, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
		p_HistoryTable->AppendColumn(strHAlertReceiveLabel,WLength(15, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
		p_HistoryTable->AppendColumn(strHAlertStateLabel,WLength(12, WLength::Percentage));
		p_HistoryTable->SetDataRowStyle("table_data_grid_item_text");
	}

	//�ϡ��·�ҳ
	//��ǰҳλ��
	p_HistoryTable->AddStandardSelLink(strBack,strForward,"");
	connect(p_HistoryTable->pSelAll, SIGNAL(clicked()), this, SLOT(HistoryBack()));
	connect(p_HistoryTable->pSelNone, SIGNAL(clicked()), this, SLOT(HistoryForward()));
	p_HistoryTable->pSelReverse->setStyleClass("");

	p_HistoryTable->GetActionTable()->elementAt(0,1)->setContentAlignment(AlignCenter);
	p_HistoryTable->GetActionTable()->elementAt(0,1)->setStyleClass("textbold");
	p_HistoryTable->GetActionTable()->elementAt(0,2)->setContentAlignment(AlignRight);

	p_HistoryTable->SetNullTipInfo(strHAlertNullList);

	WSVButton * btn = new WSVButton(p_HistoryTable->GetActionTable()->elementAt(0,2), strReturn,"button_bg_m.png", "", false);
	connect(btn, SIGNAL(clicked()), this, SLOT(HistoryReturnBtn()));
}

void CAlertList::ShowHelp()
{
	p_AlertSelectTable->ShowOrHideHelp();
	p_AlertConditionTable->ShowOrHideHelp();
}

void CAlertList::initAlertSelect()
{
	strListHeights = "";
	strListPans = "";
	strListTitles = "";
	pSubTreeTable = NULL;

	//����ѡ��
	//pMainTable->hide();
	//p_MainTable->GetContentTable()->elementAt(0, 0)->hide();
	//p_MainTable->GetContentTable()->elementAt(1, 0)->hide();

	treeTotleTable = new WSTreeAndPanTable(mainTable2->elementAt(0,0));
	AddJsParam("treeviewPanel", treeTotleTable->formName(), mainTable2->elementAt(0,0));

	//TreeTable
	new WText("<div id='tree_panel' name='tree_panel' class='panel_tree'>", treeTotleTable->elementAt(0, 0));
	pTreeTable = new WTable(treeTotleTable->elementAt(0, 0));
	//new WImage("/Images/tree_data.png", pTreeTable->elementAt(0, 0));
	new WText("</div>", pTreeTable->elementAt(0, 0));


	//DragTable
	AddJsParam("drag_tree", treeTotleTable->elementAt(0, 1)->formName(),mainTable2->elementAt(0,0));

	//PanTable
	new WText("<div id='view_panel' class='panel_view'>", treeTotleTable->elementAt(0, 2));

	p_TreeMainTable = new WSVMainTable(treeTotleTable->elementAt(0, 2), strAlertAdd, true);
	if (p_TreeMainTable->pHelpImg)
	{
		connect(p_TreeMainTable->pHelpImg,SIGNAL(clicked()),this,SLOT(ShowHelp()));
	}
	p_AlertSelectTable = new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(0,0), AlertSel, strAlertSelTitle);
	if(p_AlertSelectTable->GetContentTable() != NULL)
	{
		p_AlertSelectTable->InitTable();
		p_AlertSelectTable->AppendRows();
		pAlertName = new WLineEdit("",p_AlertSelectTable->AppendRowsContent(0,0,1, strAlertNameTitle+"<span class =required>*</span>", strAlertNameDes, strAlertNameError));
		pAlertName->setStyleClass("input_text_400");
		p_AlertSelectTable->AppendRows();

		//ѡ�񱨾�����
		WButtonGroup *p_SelectAltertypeRadio = new WButtonGroup();
		WContainerWidget *tmp = p_AlertSelectTable->AppendRowsContent(1, 0, 1, "ѡ���������", "", "");
		//E-mail����
		p_SelectEMail = new WRadioButton( strEmail, tmp);
		connect(p_SelectEMail, SIGNAL(clicked()), "showbar();" ,this, SLOT(EmailBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
		p_SelectAltertypeRadio->addButton(p_SelectEMail);
		//���ű���
		p_SelectSms = new WRadioButton( strSms, tmp);
		p_SelectAltertypeRadio->addButton(p_SelectSms);
		connect(p_SelectSms, SIGNAL(clicked()), "showbar();" ,this, SLOT(SmsBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//�ű�����
		p_SelectScript = new WRadioButton( strScript,tmp);
		p_SelectAltertypeRadio->addButton(p_SelectScript);
		connect(p_SelectScript, SIGNAL(clicked()), "showbar();" ,this, SLOT(ScriptBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//��������
		p_SelectSound = new WRadioButton( strSound, tmp);
		p_SelectAltertypeRadio->addButton(p_SelectSound);
		connect(p_SelectSound, SIGNAL(clicked()), "showbar();" ,this, SLOT(SoundBtn()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

		//Ĭ��Ϊ�ʼ�����
		p_AlertSelectTable->HideAllErrorMsg();
		p_AlertSelectTable->ShowOrHideHelp();
	}
	new WText("</div>", treeTotleTable->elementAt(0, 2));
}

//
void CAlertList::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/alert.exe?'\",1250);  ";
	appSelf->quit();
}
//
void CAlertList::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "alertRes";
	WebSession::js_af_up += "')";
}

//�ӱ�����־�б����
void CAlertList::AddColum(WTable* pContain)
{
	/*
	new WText(" ", pContain->elementAt(0, 0));
	new WText(strAlertNameLabel, pContain->elementAt(0, 1));
	new WText(strAlertDesLabel, pContain->elementAt(0, 2));
	new WText(strHAlertStateLabel, pContain->elementAt(0, 3));
	new WText(strAlertHistoryLabel, pContain->elementAt(0, 4));
	new WText(strAlertEditLabel, pContain->elementAt(0, 5));	

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}*/
}

//�༭������ť��Ӧ
void CAlertList::EditAlert(const std::string strIndex)
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "EditAlert";
	LogItem.sDesc = strAlertEditLabel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//��ʾ�༭����	
	//���� pAlertAddTable
	/**if(pAlertAddTable != NULL)
	{
		pAlertAddTable->clear();
		delete pAlertAddTable;
		pAlertAddTable = NULL;
	}

	strGenIndex = strIndex;
	bSaveAndAdd = false;
	initEditAlertTable(strIndex);
	
	iType = 0;
	pAlertAddTable->show();

	//�����б����
	pAlertSelectTable->hide();
	pAlertTable->hide();
	pMainTable->hide();
	WebSession::js_af_up = "hiddenbar()";
	**/
	strGenIndex = strIndex;
	bSaveAndAdd = false;
	initEditAlertTable(strIndex);

	iType = 0;
	p_TreeMainTable->pTitleTxt->setText(strBaseTitle);
	mainTable2->show();

	//�����б����
	mainTable->hide();
	WebSession::js_af_up = "window.location.reload(true);";
	WebSession::js_af_up += "hiddenbar();";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//ɾ��������ť��Ӧ
void CAlertList::BeforeDelAlert()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "BeforeDelAlert";
	LogItem.sDesc = strDelCon;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{
		if (m_pListItem->pSelect->isChecked())
		{
			if(pHideButton)
			{
				string strDelDes = pHideButton->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + strIsAlertDel + "','" + szButNum + "','" + szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;
					OutputDebugString("-------------BeforeDelPhone-----------------");
					OutputDebugString(strDelDes.c_str());
				}					
			}
			break;
		}
	}

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//ɾ������
void CAlertList::DelAlert()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "DelAlert";
	LogItem.sDesc = strAlertDel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	string strDeleteAlert;
	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{

		if (m_pListItem->pSelect->isChecked())
		{   

			std::string temp = m_pListItem->id;

			DeleteIniFileSection(temp, "alert.ini");

			int nRow = ((WTableCell*)(m_pListItem->pSelect->parent()))->row();

			list<Alert_LIST>::iterator pItem = m_pListItem;                     

			m_pListItem --;

			string strTemp = pItem->pAlertNameText->text();
			strDeleteAlert += strTemp;
			strDeleteAlert += "  ";

			m_pListAlert.erase(pItem);          

			p_AlertTable->GeDataTable()->deleteRow(nRow); 		

			char buf[256]={0};
			memset(buf,0,256);
			sprintf(buf, "%s,%s,%s", "alert.ini", temp.c_str(), "DELETE");
			if(!::PushMessage("SiteView70-Alert","IniChange",buf,strlen(buf)+1))
			{
				OutputDebugString("Push data failed");
				/*return;*/
			}
		}
	}

	if (m_pListAlert.size() == 0)
	{
		p_AlertTable->ShowNullTip();
	}
	else
	{
		p_AlertTable->HideNullTip();
	}

	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strTypeDelete,strMainTitle,strDeleteAlert);

/*
	if(pAlertListTable != NULL)
	{
		pAlertListTable->hide();
	}
*/
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//���ӱ�����ť��Ӧ
void CAlertList::AddAlert()
{	
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "AddAlert";
	LogItem.sDesc = strAlertAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	/*
	ClearValue();
	//���� pAlertAddTable
	if(pAlertAddTable != NULL)
	{
		pAlertAddTable->clear();
		delete pAlertAddTable;
		pAlertAddTable = NULL;
	}

	//pAlertAddTable->hide();
	pAlertTable->hide();
	pAlertSelectTable->show();	
	pMainTable->ShowBackBtn();
	/*pMainTable->hide();*/
	/*bSaveAndAdd = false;*/
	ClearValue();

	//pAlertAddTable->hide();

	pAlertName->setText("");
	p_TreeMainTable->pTitleTxt->setText(strAlertAdd);
	p_SelectEMail->enable();
	p_SelectSms->enable();
	p_SelectScript->enable();
	p_SelectSound->enable();
	//p_SelectEMail->setChecked();
	EmailBtn();
	mainTable->hide();
	mainTable2->show();
	//p_MainTable->GetContentTable()->elementAt(0,0)->hide();
	//p_MainTable->GetContentTable()->elementAt(2,0)->show();

	/*pMainTable->hide();*/
	WebSession::js_af_up = "window.location.reload(true);";
	WebSession::js_af_up += "hiddenbar();";
	
	//pAlertAddTable->show();		
	//pAlertAddTable->HideAllErrorMsg();
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//ˢ�±����б�״̬
void CAlertList::RefreshAlertState(string strIndex, string strAlertState)
{/*
	string strAlertType, strAlertCategory;
	SVTableRow * pRow = m_svAlertList.Row(strIndex);
    if(pRow)
    {
        //�ı䱨��״̬
		SVTableCell * pAlertStateCell = pRow->Cell(5);
        if (pAlertStateCell)
        {
            if (pAlertStateCell->Type() == adText)
			{
				((WText *)pAlertStateCell->Value())->setText(strAlertState);	
			}
        }

        //���ɱ������
		SVTableCell * pAlertTypeCell = pRow->Cell(3);
        if (pAlertTypeCell)
        {
            if (pAlertTypeCell->Type() == adText)
			{
				strAlertType = ((WText *)pAlertTypeCell->Value())->text();
			}
        }
		
        SVTableCell * pAlertCategoryCell = pRow->Cell(4);
        if (pAlertCategoryCell)
        {
            if (pAlertCategoryCell->Type() == adText)
			{
				strAlertCategory = ((WText *)pAlertCategoryCell->Value())->text();
			}
        }
		
        SVTableCell * pAlertDesCell = pRow->Cell(2);
        if (pAlertDesCell)
        {
            if (pAlertDesCell->Type() == adText)
			{
				string strDes = "";
				if(strAlertState == strDisable)
					strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
				else
					strDes = strAlertType;
				((WText *)pAlertDesCell->Value())->setText(strDes);	
			}
        }
	}		*/
}

//��������ť��Ӧ
void CAlertList::EnableAlert()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "EnableAlert";
	LogItem.sDesc = strAlertEnable;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{

		if (m_pListItem->pSelect->isChecked())
		{   

			std::string strIndex = m_pListItem->id;

			//ini���ݸ��¡���
			WriteIniFileString(strIndex, "AlertState", strEnable, "alert.ini");		
			string tmp = GetIniFileString(strIndex, "AlertState", "", "alert.ini");	
			//OutputDebugString((strEnable+","+tmp+"-----enablealert------\n").c_str());
			list<Alert_LIST>::iterator pItem = m_pListItem;       
			
			std::string strDes = "";
			std::string strAlertType = GetIniFileString(strIndex, "AlertType", "" , "alert.ini");
			strDes = strAlertType;
			pItem->pAlertDesText->setText(strDes);

			char buf[256]={0};
			memset(buf,0,256);
			sprintf(buf, "%s,%s,%s", "alert.ini", strIndex.c_str(), "EDIT");

			if(!::PushMessage("SiteView70-Alert","IniChange",buf,strlen(buf)+1))
			{
				OutputDebugString("Push data failed");
			}
		}
	}

	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strEnableType,strMainTitle,strEnableAlert);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//��ֹ������ť��Ӧ
void CAlertList::DisableAlert()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "DisableAlert";
	LogItem.sDesc = strAlertDisable;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{

		if (m_pListItem->pSelect->isChecked())
		{   

			std::string strIndex = m_pListItem->id;

			//ini���ݸ��¡���
			WriteIniFileString(strIndex, "AlertState", strDisable, "alert.ini");	

			list<Alert_LIST>::iterator pItem = m_pListItem;       

			std::string strAlertType = GetIniFileString(strIndex, "AlertType", "" , "alert.ini");
			string strDes = "";
			strDes = strAlertType + " <span class =required>("  + strDisable + ")</span>";
			pItem->pAlertDesText->setText(strDes);

			char buf[256]={0};
			memset(buf,0,256);
			sprintf(buf, "%s,%s,%s", "alert.ini", strIndex.c_str(), "EDIT");

			if(!::PushMessage("SiteView70-Alert","IniChange",buf,strlen(buf)+1))
			{
				OutputDebugString("Push data failed");
			}
		}
	}
	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strDisableType,strMainTitle,strDisableAlert);

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//���水ť��Ӧ
bool CAlertList::SaveAlert()
{
	bool bEnd = false;
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "SaveAlert";
	LogItem.sDesc = strSaveAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

OPEnd:
	if(bEnd)
	{
		DWORD dcalEnd=GetTickCount();
		InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd -dcalBegin);
		return false;
	}

	bool bAdd = false;
	OutputDebugString("���뱣��,");
	//������
	bool bError = false;
	std::list<string> errorMsgList;

	p_AlertSelectTable->HideAllErrorMsg();
	p_AlertConditionTable->HideAllErrorMsg();

	int nAlertType = GetIntFromAlertType(strGolobalType);
   
	//AlertName
	if(pAlertName->text().empty())
    {
		errorMsgList.push_back(strAlertNameError);
		bError = true;
    }
	else
	{
		if(bAdd)
		{
			if(IsAlertNameExist(pAlertName->text()))
			{
				errorMsgList.push_back(strAlertNameError);
				bError = true;		
			}
		}
		else
		{
			if(pAlertName->text() != strOldAlertName)
			{
				if(IsAlertNameExist(pAlertName->text()))
				{
					errorMsgList.push_back(strAlertNameError);
					bError = true;		
				}				
			}
		}
	}
	
  // AlertTarget
  //  if(pEditLogin->text().empty())
  //  {
  //      errorMsgList.push_back(strLoginError);
		//bError = true;
  //  }
	int nTmp = 0;
	int nRet = 0;
	char chItem[32]  = {0};
 
	//������(���� �༭һ��)
	switch(nAlertType)
	{
		case 1:
			//email����
			if(pEmailAdress->currentText() == "")
			{
				errorMsgList.push_back(strEmailAdressError);
				bError = true;
			}
			
			if(pEmailAdress->currentText() == strOther)
			{
				if(pOtherAdress->text() == "")
				{
					errorMsgList.push_back(strEmailAdressError);
					bError = true;			

				}			
				else if(!checkEmail(pOtherAdress->text()))
				{
					errorMsgList.push_back(strEmailAdressError);
					bError = true;			
				}
				else
				{
				
				}
			}
			
			
			//����Ϊ����
			if(!pAlertUpgrade->text().empty())
			{
				nRet = sscanf(pAlertUpgrade->text().c_str(), "%d", &nTmp);
				if(nRet == EOF || nRet == 0 || nTmp < 0)
				{
					errorMsgList.push_back(strAlertUpgradeError);
					bError = true;
				}
				else
				{				
					sprintf(chItem, "%d", nTmp);
					pAlertUpgrade->setText(chItem);
				}
			}

			if(!pAlertStop->text().empty())
			{
				nRet = sscanf(pAlertStop->text().c_str(), "%d", &nTmp);
				if(nRet == EOF || nRet == 0 || nTmp < 0)
				{
					errorMsgList.push_back(strAlertStopError);
					bError = true;
				}
				else
				{				
					sprintf(chItem, "%d", nTmp);
					pAlertStop->setText(chItem);
				}
			}

			break;
		case 2:
			//���ű���
			if(pSmsNumber->currentText() == "")
			{
				errorMsgList.push_back(strPhoneNumberError);
				bError = true;
			}
			
			if(pSmsNumber->currentText() == strOther)
			{
				if(pOtherNumber->text() == "")
				{
					errorMsgList.push_back(strPhoneNumberError);
					bError = true;	
				}
				else if(!checkPhoneNum(pOtherNumber->text()))
				{
					errorMsgList.push_back(strPhoneNumberError);
					bError = true;
				}
			}

			//����Ϊ����
			if(!pAlertUpgrade->text().empty())
			{
				nRet = sscanf(pAlertUpgrade->text().c_str(), "%d", &nTmp);
				if(nRet == EOF || nRet == 0 || nTmp < 0)
				{
					errorMsgList.push_back(strAlertUpgradeError);
					bError = true;
				}
				else
				{				
					sprintf(chItem, "%d", nTmp);
					pAlertUpgrade->setText(chItem);
				}
			}

			if(!pAlertStop->text().empty())
			{
				nRet = sscanf(pAlertStop->text().c_str(), "%d", &nTmp);
				if(nRet == EOF || nRet == 0 || nTmp < 0)
				{
					errorMsgList.push_back(strAlertStopError);
					bError = true;
				}
				else
				{				
					sprintf(chItem, "%d", nTmp);
					pAlertStop->setText(chItem);
				}
			}
			break;
		case 3:
			//�ű�����

			break;
		case 4:
			//��������
			
			break;
		default:

			break;
	}
	
	//��������
	int nCond = GetIntFromAlertCond();
	switch(nCond)
	{
		case 1:
			//Always
			nRet = sscanf(pAlwaysTimes->text().c_str(), "%d", &nTmp);
			if(nRet == EOF || nRet == 0 || nTmp < 1)
			{
				errorMsgList.push_back(strWhenError);
				bError = true;
			}
			else
			{				
				sprintf(chItem, "%d", nTmp);
				pAlwaysTimes->setText(chItem);
			}
			break;
		case 2:
			//Only			
			nRet = sscanf(pOnlyTimes->text().c_str(), "%d", &nTmp);
			if(nRet == EOF || nRet == 0 || nTmp < 1)
			{
				errorMsgList.push_back(strWhenError);
				bError = true;
			}
			else
			{				
				sprintf(chItem, "%d", nTmp);
				pOnlyTimes->setText(chItem);
			}
			break;
		case 3:
			//Select
			nRet = sscanf(pSelTimes1->text().c_str(), "%d", &nTmp);
			if(nRet == EOF || nRet == 0 || nTmp < 1)
			{
				errorMsgList.push_back(strWhenError);
				bError = true;
			}
			else
			{				
				sprintf(chItem, "%d", nTmp);
				pSelTimes1->setText(chItem);
			}


			nRet = sscanf(pSelTimes2->text().c_str(), "%d", &nTmp);
			if(nRet == EOF || nRet == 0 || nTmp < 1)
			{
				errorMsgList.push_back(strWhenError);
				bError = true;
			}
			else
			{				
				sprintf(chItem, "%d", nTmp);
				pSelTimes2->setText(chItem);
			}

			break;
		default:
			break;
	}
	OutputDebugString(chItem);
	OutputDebugString("�жϽ���\n");
	//�д��󷵻�
	if(bError)
	{
		p_AlertSelectTable->ShowErrorMsg(errorMsgList);
		p_AlertConditionTable->ShowErrorMsg(errorMsgList);
		WebSession::js_af_up = "hiddenbar()";
		bEnd = true;	
		goto OPEnd;
	}

	GetAlertTargetList();
	strAlertTargerList = ",";
	std::string strUnAlertTargetList;
	strUnAlertTargetList=",";
	for( list<std::string >::iterator _listitem = pUnpAlertTargetList.begin(); _listitem != pUnpAlertTargetList.end(); _listitem ++)
	{
		strUnAlertTargetList+=_listitem->c_str();
		strUnAlertTargetList+=",";
	}

	for( list<std::string >::iterator _listitem = pAlertTargetList.begin(); _listitem != pAlertTargetList.end(); _listitem ++)
	{  	
		std::string strTmp;
		strTmp=",";
		strTmp+=_listitem->c_str();
		strTmp+=".";

//		OutputDebugString(strTmp.c_str());

		int nIndex;
		nIndex=strUnAlertTargetList.find(strTmp,0);
		if(nIndex <0)
		{
		
			strAlertTargerList +=_listitem->c_str();
			strAlertTargerList +=",";
		}
	}
	if(pAlertTargetList.empty())
	{
		WebSession::js_af_up += "hiddenbar();";
		WebSession::js_af_up += "alert('";
		WebSession::js_af_up += strAlertAreaNotEmpty;
		WebSession::js_af_up += "')";

		bEnd = true;	
		goto OPEnd;
	}
	//��������(���� �༭һ��)
	if(strGenIndex == "-1")
	{
		strGenIndex = GetOnlyIndex(0);
		bAdd = true;
	}
	else
	{
		bAdd = false;
	}

	//���ݴ洢����
	WriteIniFileString(strGenIndex, "nIndex", strGenIndex, "alert.ini");
	WriteIniFileString(strGenIndex, "AlertTarget", strAlertTargerList, "alert.ini");

	WriteIniFileString(strGenIndex, "AlertName", TrimStdString(pAlertName->text()), "alert.ini");
	//WriteIniFileString(strAlertName, "Target", pEditUserName->text().c_str(), "alert.ini");
	WriteIniFileString(strGenIndex, "AlertType", strGolobalType, "alert.ini");
	WriteIniFileString(strGenIndex, "AlertCategory", pEventName->currentText(), "alert.ini");	
	WriteIniFileString(strGenIndex, "AlertState", "", "alert.ini");
	
	//��������(���� �༭һ��)
	int iCheck = 0;
	if (pCheckBox->isChecked()) iCheck=1;
	else iCheck=0;

	switch(nAlertType)
	{
		case 1:
			//email����
			//Ϊ���Ticket #112 ��������ECC�ʼ��������ⶨ�����������������롣
			//�պ� 2007-08-02

			//+++++++++++++++++++++++++++�������ӿ�ʼ  �պ� 2007-08-02+++++++++++++++++++++++++++
			//���������ñ��浽��alert.ini�������ļ���
			WriteIniFileInt(strGenIndex, "isCheck", iCheck, "alert.ini");
			WriteIniFileString(strGenIndex, "EmailTitle", pAlertEmailTitle->text(), "alert.ini");
			//+++++++++++++++++++++++++++�������ӽ���  �պ� 2007-08-02+++++++++++++++++++++++++++
			WriteIniFileString(strGenIndex, "EmailAdress", pEmailAdress->currentText(), "alert.ini");
			WriteIniFileString(strGenIndex, "OtherAdress", TrimStdString(pOtherAdress->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "EmailTemplate", pEmailTemplate->currentText(), "alert.ini");

			WriteIniFileString(strGenIndex, "Upgrade", TrimStdString(pAlertUpgrade->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "UpgradeTo", TrimStdString(pAlertUpgradeTo->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "Stop", TrimStdString(pAlertStop->text()), "alert.ini");

			break;
		case 2:
			//���ű���
			WriteIniFileString(strGenIndex, "SmsNumber", pSmsNumber->currentText(), "alert.ini");
			WriteIniFileString(strGenIndex, "OtherNumber", TrimStdString(pOtherNumber->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "SmsSendMode", pSmsSendMode->currentText(), "alert.ini");
			WriteIniFileString(strGenIndex, "SmsTemplate", pSmsTemplate->currentText(), "alert.ini");

			WriteIniFileString(strGenIndex, "Upgrade", TrimStdString(pAlertUpgrade->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "UpgradeTo", TrimStdString(pAlertUpgradeTo->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "Stop", TrimStdString(pAlertStop->text()), "alert.ini");

			break;
		case 3:
			//�ű�����
			WriteIniFileString(strGenIndex, "ScriptServer", TrimStdString(pScriptServer->currentText()), "alert.ini");
			WriteIniFileString(strGenIndex, "ScriptServerId", strScriptServerId, "alert.ini");
			WriteIniFileString(strGenIndex, "ScriptFile", pScriptFile->currentText(), "alert.ini");
			WriteIniFileString(strGenIndex, "ScriptParam", TrimStdString(pScriptParam->text()), "alert.ini");
			break;
		case 4:
			//��������
			WriteIniFileString(strGenIndex, "Server", TrimStdString(pServer->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "LoginName", TrimStdString(pLoginName->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "LoginPwd", TrimStdString(pLoginPwd->text()), "alert.ini");			
			break;
		default:
			break;
	}

	//��������	
	WriteIniFileInt(strGenIndex, "AlertCond", nCond, "alert.ini");

	WriteIniFileString(strGenIndex, "AlwaysTimes", "1", "alert.ini");
	WriteIniFileString(strGenIndex, "OnlyTimes", "1", "alert.ini");
	WriteIniFileString(strGenIndex, "SelTimes1", "2", "alert.ini");
	WriteIniFileString(strGenIndex, "SelTimes2", "3", "alert.ini");
	switch(nCond)
	{
		case 1:
			//Always
			WriteIniFileString(strGenIndex, "AlwaysTimes", TrimStdString(pAlwaysTimes->text()), "alert.ini");
			break;
		case 2:
			//Only
			WriteIniFileString(strGenIndex, "OnlyTimes", TrimStdString(pOnlyTimes->text()), "alert.ini");
			break;
		case 3:
			//Select
			WriteIniFileString(strGenIndex, "SelTimes1", TrimStdString(pSelTimes1->text()), "alert.ini");
			WriteIniFileString(strGenIndex, "SelTimes2", TrimStdString(pSelTimes2->text()), "alert.ini");
			break;
		default:
			break;
	}
	OutputDebugString("add list param\n");

	mainTable->show();
	mainTable2->hide();

	if(bAdd)
	{
		//1�������б���
		//
		if(m_svAlertList.RowCount() <= 0)
		{
			//pAlertListTable->deleteRow(1);
			//new WText(strNoAlertItem, (WContainerWidget*)pAlertListTable->elementAt(1 , 1));
		}

		AddAlertItem(strGenIndex, TrimStdString(pAlertName->text()).c_str(), strGolobalType, pEventName->currentText().c_str(), strEnable);
		WriteIniFileString(strGenIndex, "AlertState", strEnable, "alert.ini");
	}
	else
	{
		//2���༭�б���
		EditAlertItem(strGenIndex, TrimStdString(pAlertName->text()).c_str(), strGolobalType, pEventName->currentText().c_str());
	}
	OutputDebugString("add list param over\n");

	//���¼��UserOperateLog��
	TTime mNowTime = TTime::GetCurrentTimeEx();
	OperateLog m_pOperateLog;
	string strOType;
	if(bAdd)
	{
		strOType = strTypeAdd;
	}
	else
	{
		strOType = strAlertEditLabel;
	}
	m_pOperateLog.InsertOperateRecord("UserOperateLog",strUserID,mNowTime.Format(),strOType,strMainTitle,pAlertName->text());
	OutputDebugString("���뱣�潻������1\n");
	//���ر༭����

	if(pAlertAddTable != NULL)
	{
		/*pAlertAddTable->hide();*/
		//pAlertAddTable->clear();
		//delete pAlertAddTable;
		//pAlertAddTable = NULL;
	}
	OutputDebugString("���뱣�潻������2\n");
	//��ʾ�б����	
	//if(!bSaveAndAdd)
	{
		/*pHistoryTable->hide();
		pAlertSelectTable->hide();
		pAlertTable->show();
		pMainTable->ShowHelpBtn();
		pMainTable->show();*/
	}
	OutputDebugString("���뱣�潻������3\n");
	char buf[256]={0};
	memset(buf,0,256);
	if(bAdd)
		sprintf(buf, "%s,%s,%s", "alert.ini", strGenIndex.c_str(), "ADD");
	else
		sprintf(buf, "%s,%s,%s", "alert.ini", strGenIndex.c_str(), "EDIT");

	if(!::PushMessage("SiteView70-Alert","IniChange",buf,strlen(buf)+1))
	{
		OutputDebugString("Push data failed");
		/*return;*/
	}

	bSaveAndAdd = false;
	
	if (m_pListAlert.size() == 0)
	{
		p_AlertTable->ShowNullTip();
	}
	else
	{
		p_AlertTable->HideNullTip();
	}

	//��Ϊ���ӵ���������������֤֮��ᵼ�����ӵ���û�����ӵ��б���ӣ�������̫�õĽ�����������ᵼ���ٶ����⣮����
	//refresh();
	WebSession::js_af_up = "window.location.reload(true);";
	WebSession::js_af_up += "hiddenbar();";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
	
	return true;
}
//���沢��Ӱ�ť����Ӧ
void CAlertList::SaveAndAddAlert()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "SaveAndAddAlert";
	LogItem.sDesc = strSaveAndAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//����SaveAndAddAlert������󣿡�������
	bSaveAndAdd = true;
	//���汨��
	if(SaveAlert())
	{
		mainTable2->show();
		mainTable->hide();
		/*
		pMainTable->show();*/
		//��ת������ѡ����棨����ٷ��ر���List�����ľ�����Ӧ����ˣ� ���򱣳֣�
		bSaveAndAdd = true;
		AddAlert();
	}	

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}
//ȡ����ť��Ӧ
void CAlertList::CancelAlert()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "CancelAlert";
	LogItem.sDesc = strCancelAdd;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	mainTable->show();
	mainTable2->hide();
	bSaveAndAdd = false;
	WebSession::js_af_up = "window.location.reload(true);";
	WebSession::js_af_up += "hiddenbar()";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//��ձ༭�û�����
void CAlertList::ClearValue()
{
	strOldAlertName = "";
	strGolobalType = "";
	strGenIndex = "-1";
}

//���ɱ༭�û�����

void CAlertList::initAddAlertTable(int nAlertType,int iType)
{
	char  tmp[100];
	int currentRow = 1;
	OutputDebugString("����---------------------\n");
	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);
	
	if (p_AlertConditionTable)
	{
		//���
		delete p_AlertConditionTable;
		p_AlertConditionTable = NULL;
	}

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	p_AlertSelectTable->HideAllErrorMsg();
	
	if (!bSaveAndAdd)
	{
		delete pSubTreeTable;
		pSubTreeTable = NULL;
	
		bSaveAndAdd = true;

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	//�����
	//pTreeTable->elementAt(0,0)->resize(WLength(200,WLength::Pixel),WLength(100,WLength::Percentage));	
	pSubTreeTable = new WTable((WContainerWidget *)pTreeTable->elementAt(0,0));	
	pSubTreeTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	pSubTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	pSubTreeTable->setCellPadding(0);	
	pSubTreeTable->setCellSpaceing(0);	

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);	

	//label
	WTable * pUpTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	pUpTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	pUpTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	new WText("&nbsp", (WContainerWidget *)pUpTable->elementAt(0,0));//strAlertArea

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	//tree
	WTable* pDownTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	pDownTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	pDownTable->elementAt(0,0)->setVerticalAlignment(AlignTop);

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	pAlertTargerTree = new CCheckBoxTreeView((WContainerWidget *)pDownTable->elementAt(0,0));


	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	string strSection = GetWebUserID();
	pAlertTargerTree->InitTree("",false, true, false, strSection);

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);
	//}

	//if(!bSaveAndAdd)
	//{
		strAlertTargerList = "";
		pAlertTargetList.clear();
	}
	else
	{
		//SetAlertTargetCheck();
	}

	switch(nAlertType)
	{
	case 0:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strBaseTitle);
		break;
	case 1:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strEmail);
		break;
	case 2:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strSms);

		break;
	case 3:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strScript);

		break;
	case 4:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strSound);

		break;
	case 5:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strSelfDefine);
		break;
	default:
		p_AlertConditionTable =  new WSVFlexTable(p_TreeMainTable->GetContentTable()->elementAt(1,0), Group,strBaseTitle);	
		break;
	}

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	if (!p_AlertConditionTable->GetContentTable() )
	{
		return;
	}
	//������Ϣ
	p_AlertConditionTable->AppendRows("������Ϣ");
	/*if(!bSaveAndAdd)
	{
		strAlertTargerList = "";
		pAlertTargetList.clear();
	}
	else
	{
		//strAlertTargerList = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini");
		SetAlertTargetCheck();
	}*/

	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	WPushButton * pSelServerBtn;
	std::string strOpen;
	//
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strTmp;
	WTable *pDepentTbl;

	//Ĭ�϶���ѡ
	p_SelectEMail->setUnChecked();
	p_SelectScript->setUnChecked();
	p_SelectSms->setUnChecked();
	p_SelectSound->setUnChecked();

	switch(nAlertType)
	{
	case 1:

		//email����
		p_SelectEMail->setChecked(true);
		pDepentTbl = new WTable(p_AlertConditionTable->AppendRowsContent( 0, strEmailAdressTitle+"<span class =required>*</span>", strEmailAdressDes, strEmailAdressError));

		pEmailAdress = new WSelectionBox(pDepentTbl->elementAt(0, 0));
		pEmailAdress->setVerticalSize(4);
		pEmailAdress->setCurrentIndex(0);
		pOtherAdress = new WLineEdit(pDepentTbl->elementAt(0, 0));	
		pOtherAdress->setStyleClass("input_text_400");
		
		//emailģ��
		pEmailTemplate = new WComboBox(p_AlertConditionTable->AppendRowsContent( 0 , strEmailTemplateTitle, strEmailTemplateDes, ""));
		pEmailTemplate->setStyleClass("input_text");

		//��EmailAdress.ini��ʼ��pEmailAdress
		if(GetIniFileSections(keylist, "emailAdress.ini"))
		{				
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				//��ini������
				strTmp = GetIniFileString((*keyitem), "Name", "", "emailAdress.ini");
				//
				if(GetIniFileInt((*keyitem), "bCheck", 0, "emailAdress.ini") == 1)
				{
					strTmp += "(";
					strTmp += strDisable;
					strTmp += ")";
				}
				pEmailAdress->addItem(strTmp.c_str());
			}
		}
		pEmailAdress->addItem(strOther);
		pEmailAdress->setCurrentIndexByStr(strOther);
		//��TXTTemplate.ini��ʼ��pEmailTemplate()
		if(GetIniFileKeys("Email", keylist, "TXTTemplate.ini"))
		{
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				//��ini������
				//strTmp = GetIniFileString("Email", (*keyitem), "", "TXTTemplate.ini");
				//pEmailTemplate->addItem(strTmp.c_str());
				pEmailTemplate->addItem((*keyitem));
			}
		}

		//Ϊ���Ticket #112 ��������ECC�ʼ��������ⶨ�����������������롣
		//�պ� 2007-08-02

		//+++++++++++++++++++++++++++�������ӿ�ʼ  �պ� 2007-08-02+++++++++++++++++++++++++++
		pCheckBox = new WCheckBox(strEmailSubjectTemplateCheck, p_AlertConditionTable->AppendRowsContent(0, "", "", ""));
		connect(pCheckBox,SIGNAL(clicked()),this,SLOT(ShowEdit()));      //Ϊ����¼�����Ӧ����
		pCheckBox->setChecked(false);
		pAlertEmailTitle = new WLineEdit("", p_AlertConditionTable->AppendRowsContent( 0, strEmailSubjectTemplate, "", ""));
		pAlertEmailTitle->setStyleClass("input_text_400");              //���ñ༭�������ҳ�еķ��
		pAlertEmailTitle->disable();
		//+++++++++++++++++++++++++++�������ӽ���  �պ� 2007-08-02+++++++++++++++++++++++++++

		//�������� ���������� ֹͣ����
		pAlertUpgrade = new WLineEdit("0", p_AlertConditionTable->AppendRowsContent( 0, strAlertUpgradeTitle, strAlertUpgradeDes, strAlertUpgradeError));
		pAlertUpgrade->setStyleClass("input_text");

		pAlertUpgradeTo = new WLineEdit("", p_AlertConditionTable->AppendRowsContent( 0, strAlertUpgradeToTitle, strAlertUpgradeToDes, ""));
		pAlertUpgradeTo->setStyleClass("input_text_400");

		pAlertStop = new WLineEdit("0", p_AlertConditionTable->AppendRowsContent( 0, strAlertStopTitle, strAlertStopDes, strAlertStopError));
		pAlertStop->setStyleClass("input_text");

		break;
	case 2:
		//���ű���
		p_SelectSms->setChecked();
		pDepentTbl = new WTable(p_AlertConditionTable->AppendRowsContent( 0, strPhoneNumberTitle+"<span class =required>*</span>", strPhoneNumberDes, strPhoneNumberError));
		pSmsNumber = new WSelectionBox(pDepentTbl->elementAt(0,0));
		pOtherNumber = new WLineEdit(pDepentTbl->elementAt(0,0));
		pOtherNumber->setStyleClass("input_text_400");

		//���ͷ�ʽ
		pSmsSendMode = new WComboBox(p_AlertConditionTable->AppendRowsContent( 0, strSendModeTitle+"<span class =required>*</span>", strSendModeDes, ""));
		pSmsSendMode->setStyleClass("input_text");
		pSmsSendMode->addItem(strSendModeWeb);
		pSmsSendMode->addItem(strSendModeCom);
		pSmsSendMode->addItem(strSendModeSelfDefine);

		//��interfacedll.ini��ȡ���dll������ŷ��ͷ�ʽ
		if(GetIniFileSections(keylist, "interfacedll.ini"))
		{
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				pSmsSendMode->addItem((*keyitem));
			}			
		}

		pSmsTemplate = new WComboBox(p_AlertConditionTable->AppendRowsContent( 0, strSmsTemplateTitle+"<span class =required>*</span>", strSmsTemplateDes, ""));
		pSmsTemplate->setStyleClass("input_text");

		//��smsphoneset.ini��ʼ��pSmsNumber
		if(GetIniFileSections(keylist, "smsphoneset.ini"))
		{
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				//��ini������
				strTmp = GetIniFileString((*keyitem), "Name", "", "smsphoneset.ini");
				if(GetIniFileString((*keyitem), "Status", "", "smsphoneset.ini") == "No")
				{
					strTmp += "(";
					strTmp += strDisable;
					strTmp += ")";
				}
				pSmsNumber->addItem(strTmp.c_str());
			}
		}
		pSmsNumber->addItem(strOther);
		pSmsNumber->setCurrentIndexByStr(strOther);

		//��TXTTemplate.ini��ʼ��pSmsTemplate
		if(GetIniFileKeys("SMS", keylist, "TXTTemplate.ini"))
		{				
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				//��ini������
				//strTmp = GetIniFileString("SMS", (*keyitem), "", "TXTTemplate.ini");
				//pSmsTemplate->addItem(strTmp.c_str());
				pSmsTemplate->addItem((*keyitem));
			}
		}

		//�������� ���������� ֹͣ����
		pAlertUpgrade = new WLineEdit("0", p_AlertConditionTable->AppendRowsContent( 0, strAlertUpgradeTitle, strAlertUpgradeDes, strAlertUpgradeError));
		pAlertUpgrade->setStyleClass("input_text");

		pAlertUpgradeTo = new WLineEdit("", p_AlertConditionTable->AppendRowsContent( 0, strAlertUpgradeToTitle, strAlertUpgradeToDes, ""));
		pAlertUpgradeTo->setStyleClass("input_text_400");

		pAlertStop = new WLineEdit("0", p_AlertConditionTable->AppendRowsContent( 0, strAlertStopTitle, strAlertStopDes, strAlertStopError));
		pAlertStop->setStyleClass("input_text");

		break;
	case 3:
		//�ű�����
		p_SelectScript->setChecked(true);
		pScriptServer = new WComboBox(p_AlertConditionTable->AppendRowsContent( 0, strScriptServerTitle, strScriptServerDes, ""));
		pScriptServer->setStyleClass("input_text");

		InitScriptServer(pScriptServer);

		//�ű�������ѡ�����仯
		connect(pScriptServer, SIGNAL(changed()), this, SLOT(SelSeverChanged()));

		pScriptServer->setCurrentIndex(0);
		strScriptServerId = lsDeviceId[0];		

		pScriptFile = new WComboBox(p_AlertConditionTable->AppendRowsContent( 0, strScriptTitle, strScriptDes, ""));
		pScriptFile->setStyleClass("input_text");

		GetScriptFileFromServer();

		pScriptFile->setCurrentIndex(0);

		pScriptParam = new WLineEdit(p_AlertConditionTable->AppendRowsContent( 0, strScriptParamTitle, strScriptParamDes, ""));
		pScriptParam->setStyleClass("input_text_400");

		break;
	case 4:
		//��������
		p_SelectSound->setChecked(true);
		pServer = new WLineEdit("127.0.0.1", p_AlertConditionTable->AppendRowsContent( 0, strSoundServerTitle, strSoundServerDes, ""));
		pServer->setStyleClass("input_text");

		pLoginName = new WLineEdit("administrator", p_AlertConditionTable->AppendRowsContent( 0, strLoginNameTitle, strLoginNameDes, ""));
		pLoginName->setStyleClass("input_text");

		pLoginPwd = new WLineEdit("", p_AlertConditionTable->AppendRowsContent(0, strLoginPwdTitle, strLoginPwdDes, ""));
		pLoginPwd->setStyleClass("input_text");
		pLoginPwd->setEchoMode(WLineEdit::Password);
		break;
	case 5:

		break;
	default:
		break;
	}


	sprintf(tmp,"%d ------------\n",currentRow++);
	OutputDebugString(tmp);

	//��������
	p_AlertConditionTable->AppendRows(strCondTitle);

	pEventName = new WComboBox(p_AlertConditionTable->AppendRowsContent( 1, strEventNameTitle, strEventNameDes, ""));
	pEventName->addItem(strError);
	pEventName->addItem(strWarning);
	pEventName->addItem(strNormal);
	pEventName->setCurrentIndex(0);
	pEventName->setStyleClass("input_text");

	WButtonGroup * 
		group = new WButtonGroup();
	
	WTable *tmpTable = new WTable(p_AlertConditionTable->AppendRowsContent( 1, "", strWhenDes, strWhenError));
	pAlwaysCond = new WRadioButton(strAlwaysCondTitle, tmpTable->elementAt(0, 0));	
	new WText(strAlwaysCond1, tmpTable->elementAt(1, 0));
	pAlwaysTimes = new WLineEdit("1", tmpTable->elementAt(1, 0));
	pAlwaysTimes->setStyleClass("input_text_alertmode");
	new WText(strAlwaysCond2, tmpTable->elementAt(1, 0));

	pOnlyCond = new WRadioButton(strOnlyCondTitle, tmpTable->elementAt(2, 0));	
	new WText(strOnlyCond1, tmpTable->elementAt(3, 0));
	pOnlyTimes = new WLineEdit("1", tmpTable->elementAt(3, 0));
	pOnlyTimes->setStyleClass("input_text_alertmode");
	new WText(strOnlyCond2, tmpTable->elementAt(3, 0));

	pSelectCond = new WRadioButton(strSelectCondTitle, tmpTable->elementAt(4, 0));	
	new WText(strSelectCond1, tmpTable->elementAt(5, 0));
	pSelTimes1 = new WLineEdit("2", tmpTable->elementAt(5, 0));
	pSelTimes1->setStyleClass("input_text_alertmode");
	new WText(strSelectCond2, tmpTable->elementAt(5, 0));
	pSelTimes2 = new WLineEdit("3", tmpTable->elementAt(5, 0));
	pSelTimes2->setStyleClass("input_text_alertmode");
	new WText(strSelectCond3, tmpTable->elementAt(5, 0));
	pAlwaysCond->setUnChecked();
	pOnlyCond->setUnChecked();
	pSelectCond->setChecked();

	//pGroupCond = new WRadioButton(strGroupCond, pAlertConditionTable->GetContentTable()->elementAt(7, 0));		
	group->addButton(pAlwaysCond);
	group->addButton(pOnlyCond);
	group->addButton(pSelectCond);

	//commonbuttoncommonbuttoncommonbutton//���100%���
	if(p_AlertConditionTable->GetActionTable()!=NULL)
	{
		//pFlexTable->AddStandardSelLink("ȫѡ" ,"ȫ��ѡ","��ѡ" );

		WTable *pTbl;

		pTbl = new WTable(p_AlertConditionTable->GetActionTable()->elementAt(0, 1));

		WSVButton * p_SaveAndAdd = new WSVButton(pTbl->elementAt(0,0), strSaveAndAdd, "button_bg_m.png", "", false);

		WSVButton * p_Save = new WSVButton(pTbl->elementAt(0, 1), strSave, "button_bg_m_black.png", "", true);	

		WSVButton *p_Cancel = new WSVButton(pTbl->elementAt(0, 2), strCancel, "button_bg_m.png", "", false);

		pTbl = new WTable(p_AlertConditionTable->GetActionTable()->elementAt(0,2));

		connect( p_Save, SIGNAL(clicked()), "showbar();" ,this, SLOT(SaveAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
		connect( p_Cancel, SIGNAL(clicked()), "showbar();" ,this, SLOT(CancelAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		connect( p_SaveAndAdd, SIGNAL(clicked()),"showbar();" ,this, SLOT(SaveAndAddAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	}


	//new WText("</div>", treeTotleTable->elementAt(0, 2));

	//���水ť
	p_AlertConditionTable->HideAllErrorMsg();
	p_AlertConditionTable->ShowOrHideHelp();



	/**	
	switch(iType)
	{
	case 0:
	pAlertAddTable = new CAnswerTable(this, strBaseTitle);
	break;
	case 1:
	pAlertAddTable = new CAnswerTable(this, strEmail );
	break;
	case 2:
	pAlertAddTable = new CAnswerTable(this, strSms );
	break;
	case 3:
	pAlertAddTable = new CAnswerTable(this, strScript );
	break;
	case 4:
	pAlertAddTable = new CAnswerTable(this, strSound );
	break;
	case 5:
	pAlertAddTable = new CAnswerTable(this, strSelfDefine );
	break;
	default:
	pAlertAddTable = new CAnswerTable(this, strBaseTitle);
	break;
	}

	pAlertAddTable->pSaveAndAdd->show();
	//connect..
	pAlertAddTable->setCellPadding(0);
	pAlertAddTable->setCellSpaceing(0);

	//���
	WTable * pFrameTable = new WTable(pAlertAddTable->GetContentTable() ->elementAt(2,0));
	pFrameTable->setCellPadding(0);	
	pFrameTable->setCellSpaceing(0);
	pFrameTable ->setStyleClass("t6");
	pFrameTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	pFrameTable->elementAt(0, 1)->setContentAlignment(AlignTop | AlignLeft);
	pFrameTable->elementAt(0, 2)->setContentAlignment(AlignTop | AlignLeft);


	//0,0
	//�����
	pFrameTable->elementAt(0,0)->resize(WLength(200,WLength::Pixel),WLength(100,WLength::Percentage));	
	WTable * pSubTreeTable = new WTable((WContainerWidget *)pFrameTable->elementAt(0,0));	
	pSubTreeTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	pSubTreeTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	pSubTreeTable->setCellPadding(0);	
	pSubTreeTable->setCellSpaceing(0);
	pSubTreeTable->setStyleClass("t62");			

	//label
	WTable * pUpTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	pUpTable->elementAt(0,0)->setContentAlignment(AlignTop | AlignLeft);
	pUpTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	new WText(strAlertArea, (WContainerWidget *)pUpTable->elementAt(0,0));

	//tree
	WTable* pDownTable = new WTable((WContainerWidget *)pSubTreeTable->elementAt(0,0));
	pDownTable->setStyleClass("t1");
	pDownTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	pDownTable->elementAt(0,0)->setVerticalAlignment(AlignTop);
	pAlertTargerTree = new CCheckBoxTreeView((WContainerWidget *)pDownTable->elementAt(0,0));

	string strSection = GetWebUserID();
	pAlertTargerTree->InitTree("",false, true, false, strSection);


	//0,1
	//�м���϶��ķָ���
	//WImage *spaceImg =new WImage("../Images/space.gif");
	//pFrameTable ->elementAt(0,1)->addWidget(spaceImg);
	//�м����϶�
	std::string strContext;
	//strContext+="style=\"WIDTH:1px;CURSOR: w-resize\" ";
	strContext+="style=\"WIDTH:3px\" ";
	strContext+=" onmousedown='_canResize=true;this.setCapture(true)'";
	strContext+="  onmouseup='this.releaseCapture();_canResize=false;'";
	sprintf(pFrameTable ->elementAt(0,1)->contextmenu_,"%s", strContext.c_str());	

	//0,2
	pFrameTable->elementAt(0, 2)->resize(WLength(100,WLength::Percentage),WLength(100,WLength::Percentage));	
	WTable * pBaseFrameTable = new WTable((WContainerWidget *)pFrameTable ->elementAt(0,2));
	pBaseFrameTable->setStyleClass("t1");

	//�ұ�
	switch(iType)
	{
	case 0:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strBaseTitle);	
	break;
	case 1:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strEmail);	
	break;
	case 2:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strSms);	
	break;
	case 3:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strScript);	
	break;
	case 4:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strSound);	
	break;
	case 5:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strSelfDefine);
	break;
	default:
	pAlertBaseTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(0,0), strBaseTitle);	
	break;
	}

	//	pAlertBaseTable = new CFlexTable((WContainerWidget *)pFrameTable ->elementAt(0,2), strBaseTitle);	
	//pAlertBaseTable = new CFlexTable(pAlertAddTable->GetContentTable()->elementAt(1,0), strBaseTitle);
	pAlertBaseTable->setCellPadding(0);
	pAlertBaseTable->setCellSpaceing(0);

	pAlertBaseTable->GetContentTable()->setCellSpaceing(0);
	pAlertBaseTable->GetContentTable()->setCellPadding(0);
	//��������
	//WTable * pTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(0, 0));	
	//pTable->elementAt(0, 0)->setStyleClass("t3left");
	new WText(strAlertNameTitle, pAlertBaseTable->GetContentTable()->elementAt(0, 0));	
	new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(0, 0));
	pAlertName = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(0, 1));
	//pAlertName->setName("AlertName");
	pAlertName->setStyleClass("cell_40");
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertNameError, 1, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertNameDes, 2, 1);

	//pTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(3, 0));	
	//AlertTarget�������	
	//new WText(strAlertTargetTitle, pAlertBaseTable->GetContentTable()->elementAt(3, 0));
	//pAertTargrt = new CCheckBoxTreeView(pAlertBaseTable->GetContentTable()->elementAt(3, 1));
	//pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertTargetError, 4, 1);
	//pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertTargetDes, 5, 1);
	if(!bSaveAndAdd)
	{
	strAlertTargerList = "";
	pAlertTargetList.clear();
	}
	else
	{
	//strAlertTargerList = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini");
	SetAlertTargetCheck();
	}

	WPushButton * pSelServerBtn;
	std::string strOpen;
	//
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strTmp;

	switch(nAlertType)
	{
	case 1:

	//email����
	pEmailAdressLabel = new WText(strEmailAdressTitle, pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	//pEmailAdressLabel = new WText("�����ʼ����յ�ַ", pAlertBaseTable->GetContentTable()->elementAt(6, 0));

	pEmailAdress = new WSelectionBox(pAlertBaseTable->GetContentTable()->elementAt(6, 1));		


	pEmailAdress->setVerticalSize(4);
	pEmailAdress->setCurrentIndex(0);
	pOtherAdress = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(6, 1));
	pOtherAdress->setTextSize(75);		
	//pOtherAdress->setName("OtherAdress");
	//		pOtherAdress->setStyleClass("cell_98");
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strEmailAdressError, 8, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strEmailAdressDes, 9, 1);	

	pEmailTemplateLabel = new WText(strEmailTemplateTitle, pAlertBaseTable->GetContentTable()->elementAt(10, 0));
	**/	
	/*new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(10, 0));*/
	/**			pEmailTemplate = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(10, 1));
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strEmailTemplateDes, 11, 1);


	//��EmailAdress.ini��ʼ��pEmailAdress
	if(GetIniFileSections(keylist, "emailAdress.ini"))
	{				
	for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
	{
	//��ini������
	strTmp = GetIniFileString((*keyitem), "Name", "", "emailAdress.ini");
	//
	if(GetIniFileInt((*keyitem), "bCheck", 0, "emailAdress.ini") == 1)
	{
	strTmp += "(";
	strTmp += strDisable;
	strTmp += ")";
	}
	pEmailAdress->addItem(strTmp.c_str());
	}
	}
	pEmailAdress->addItem(strOther);
	pEmailAdress->setCurrentIndexByStr(strOther);
	//��TXTTemplate.ini��ʼ��pEmailTemplate()
	if(GetIniFileKeys("Email", keylist, "TXTTemplate.ini"))
	{
	for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
	{
	//��ini������
	//strTmp = GetIniFileString("Email", (*keyitem), "", "TXTTemplate.ini");
	//pEmailTemplate->addItem(strTmp.c_str());
	pEmailTemplate->addItem((*keyitem));
	}
	}

	//�������� ���������� ֹͣ����
	new WText(strAlertUpgradeTitle, pAlertBaseTable->GetContentTable()->elementAt(12, 0));
	pAlertUpgrade = new WLineEdit("0", pAlertBaseTable->GetContentTable()->elementAt(12, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertUpgradeError, 13, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertUpgradeDes, 14, 1);

	new WText(strAlertUpgradeToTitle, pAlertBaseTable->GetContentTable()->elementAt(15, 0));
	pAlertUpgradeTo = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(15, 1));
	pAlertUpgradeTo->setStyleClass("cell_98");		
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertUpgradeToDes, 16, 1);

	new WText(strAlertStopTitle, pAlertBaseTable->GetContentTable()->elementAt(17, 0));
	pAlertStop = new WLineEdit("0", pAlertBaseTable->GetContentTable()->elementAt(17, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertStopError, 18, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertStopDes, 19, 1);

	break;
	case 2:
	//���ű���
	pSmsNumberLabel = new WText(strPhoneNumberTitle, pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	pSmsNumber = new WSelectionBox(pAlertBaseTable->GetContentTable()->elementAt(6, 1));
	pSmsNumber->setVerticalSize(4);
	pOtherNumber = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(7, 1));
	pOtherNumber->setStyleClass("cell_98");
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strPhoneNumberError, 8, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strPhoneNumberDes, 9, 1);	

	//���ͷ�ʽ
	new WText(strSendModeTitle, pAlertBaseTable->GetContentTable()->elementAt(10, 0));
	new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(10, 0));
	pSmsSendMode = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(10, 1));
	pSmsSendMode->addItem(strSendModeWeb);
	pSmsSendMode->addItem(strSendModeCom);
	pSmsSendMode->addItem(strSendModeSelfDefine);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strSendModeDes, 11, 1);	

	pSmsTemplateLabel = new WText(strSmsTemplateTitle, pAlertBaseTable->GetContentTable()->elementAt(12, 0));
	new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(12, 0));
	pSmsTemplate = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(12, 1));
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strSmsTemplateDes, 13, 1);

	//��smsphoneset.ini��ʼ��pSmsNumber
	if(GetIniFileSections(keylist, "smsphoneset.ini"))
	{
	for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
	{
	//��ini������
	strTmp = GetIniFileString((*keyitem), "Name", "", "smsphoneset.ini");
	if(GetIniFileString((*keyitem), "Status", "", "smsphoneset.ini") == "No")
	{
	strTmp += "(";
	strTmp += strDisable;
	strTmp += ")";
	}
	pSmsNumber->addItem(strTmp.c_str());
	}
	}
	pSmsNumber->addItem(strOther);
	pSmsNumber->setCurrentIndexByStr(strOther);

	//��TXTTemplate.ini��ʼ��pSmsTemplate
	if(GetIniFileKeys("SMS", keylist, "TXTTemplate.ini"))
	{				
	for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
	{
	//��ini������
	//strTmp = GetIniFileString("SMS", (*keyitem), "", "TXTTemplate.ini");
	//pSmsTemplate->addItem(strTmp.c_str());
	pSmsTemplate->addItem((*keyitem));
	}
	}

	//�������� ���������� ֹͣ����
	new WText(strAlertUpgradeTitle, pAlertBaseTable->GetContentTable()->elementAt(14, 0));
	pAlertUpgrade = new WLineEdit("0", pAlertBaseTable->GetContentTable()->elementAt(14, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertUpgradeError, 15, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertUpgradeDes, 16, 1);

	new WText(strAlertUpgradeToTitle, pAlertBaseTable->GetContentTable()->elementAt(17, 0));
	pAlertUpgradeTo = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(17, 1));
	pAlertUpgradeTo->setStyleClass("cell_98");
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertUpgradeToDes1, 18, 1);

	new WText(strAlertStopTitle, pAlertBaseTable->GetContentTable()->elementAt(19, 0));
	pAlertStop = new WLineEdit("0", pAlertBaseTable->GetContentTable()->elementAt(19, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertStopError, 20, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertStopDes, 21, 1);

	break;
	case 3:
	//�ű�����
	pServerTextLabel = new WText(strScriptServerTitle, pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	//new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(6, 0));

	pScriptServer = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(6, 1));

	InitScriptServer(pScriptServer);

	//�ű�������ѡ�����仯
	connect(pScriptServer, SIGNAL(changed()), this, SLOT(SelSeverChanged()));

	pScriptServer->setCurrentIndex(0);
	strScriptServerId = lsDeviceId[0];		

	//pScriptServer = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(6, 1));
	//pScriptServer->setText("127.0.0.1");
	//pScriptServer->disable();
	**/
	/*		
	pSelServerBtn = new WPushButton("��" + strScriptServerDes + "��", pAlertBaseTable->GetContentTable()->elementAt(6, 1));
	pSelServerBtn->setStyleClass("bg_button");
	strOpen = "OpenTest('";
	strOpen += "emailtest.exe?";
	strOpen += "')";
	WObject::connect(pSelServerBtn, SIGNAL(clicked()),  strOpen.c_str(), WObject::ConnectionType::JAVASCRIPT);	
	*/
	//pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strScriptServerError, 10, 1);
	/**		pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptServerDes, 7, 1);

	pScriptFileLabel = new WText(strScriptTitle, pAlertBaseTable->GetContentTable()->elementAt(8, 0));
	//new WText("<span class =required>*</span>", pAlertBaseTable->GetContentTable()->elementAt(8, 0));
	pScriptFile = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(8, 1));

	GetScriptFileFromServer();

	pScriptFile->setCurrentIndex(0);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptDes, 9, 1);

	pScriptParamLabel = new WText(strScriptParamTitle, pAlertBaseTable->GetContentTable()->elementAt(10, 0));
	pScriptParam = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(10, 1));
	pScriptParam->setStyleClass("cell_98");
	//pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strScriptParamError, 13, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptParamDes, 11, 1);

	break;
	case 4:
	//��������
	pServerLabel = new WText(strSoundServerTitle, pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	pServer = new WLineEdit("127.0.0.1", pAlertBaseTable->GetContentTable()->elementAt(6, 1));
	pServer->setStyleClass("cell_40");
	//pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strSoundServerError, 7, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strSoundServerDes, 8, 1);

	pLoginNameLabel = new WText(strLoginNameTitle, pAlertBaseTable->GetContentTable()->elementAt(9, 0));
	pLoginName = new WLineEdit("administrator", pAlertBaseTable->GetContentTable()->elementAt(9, 1));
	pLoginName->setStyleClass("cell_40");
	//pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strLoginNameError,	10, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strLoginNameDes, 11, 1);

	pLoginPwdLabel = new WText(strLoginPwdTitle, pAlertBaseTable->GetContentTable()->elementAt(12, 0));
	pLoginPwd = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(12, 1));
	pLoginPwd->setStyleClass("cell_40");
	pLoginPwd->setEchoMode(WLineEdit::Password);
	//pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strLoginPwdError, 13, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strLoginPwdDes, 14, 1);		
	break;
	case 5:

	break;
	default:
	break;
	}


	//��������
	//pAlertConditionTable = new CFlexTable(pAlertAddTable->GetContentTable()->elementAt(2,0), strCondTitle);
	pAlertConditionTable = new CFlexTable((WContainerWidget *)pBaseFrameTable ->elementAt(1,0), strCondTitle);

	pAlertConditionTable->setCellPadding(0);
	pAlertConditionTable->setCellSpaceing(0);

	new WText(strEventNameTitle, pAlertConditionTable->GetContentTable()->elementAt(0, 0));
	pEventName = new WComboBox(pAlertConditionTable->GetContentTable()->elementAt(0, 1));
	pEventName->addItem(strError);
	pEventName->addItem(strWarning);
	pEventName->addItem(strNormal);
	pEventName->setCurrentIndex(0);
	pAlertAddTable->AddHelpText(pAlertConditionTable->GetContentTable(), strEventNameDes, 1, 1);

	WButtonGroup * group = new WButtonGroup();

	pAlwaysCond = new WRadioButton(strAlwaysCondTitle, pAlertConditionTable->GetContentTable()->elementAt(2, 0));	
	new WText(strAlwaysCond1, pAlertConditionTable->GetContentTable()->elementAt(3, 1));
	pAlwaysTimes = new WLineEdit("1", pAlertConditionTable->GetContentTable()->elementAt(3, 1));
	new WText(strAlwaysCond2, pAlertConditionTable->GetContentTable()->elementAt(3, 1));

	pOnlyCond = new WRadioButton(strOnlyCondTitle, pAlertConditionTable->GetContentTable()->elementAt(4, 0));	
	new WText(strOnlyCond1, pAlertConditionTable->GetContentTable()->elementAt(5, 1));
	pOnlyTimes = new WLineEdit("1", pAlertConditionTable->GetContentTable()->elementAt(5, 1));
	new WText(strOnlyCond2, pAlertConditionTable->GetContentTable()->elementAt(5, 1));

	pSelectCond = new WRadioButton(strSelectCondTitle, pAlertConditionTable->GetContentTable()->elementAt(6, 0));	
	new WText(strSelectCond1, pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	pSelTimes1 = new WLineEdit("2", pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	new WText(strSelectCond2, pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	pSelTimes2 = new WLineEdit("3", pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	new WText(strSelectCond3, pAlertConditionTable->GetContentTable()->elementAt(7, 1));	
	pAlwaysCond->setUnChecked();
	pOnlyCond->setUnChecked();
	pSelectCond->setChecked();

	//pGroupCond = new WRadioButton(strGroupCond, pAlertConditionTable->GetContentTable()->elementAt(7, 0));		
	group->addButton(pAlwaysCond);
	group->addButton(pOnlyCond);
	group->addButton(pSelectCond);
	//group->addButton(pGroupCond);

	pAlertAddTable->AddErrorText(pAlertConditionTable->GetContentTable(), strWhenError, 8, 1);
	pAlertAddTable->AddHelpText(pAlertConditionTable->GetContentTable(), strWhenDes, 9, 1);

	//commonbuttoncommonbuttoncommonbutton//���100%���
	int nRow;
	nRow = pAlertAddTable->GetContentTable()->numRows();
	pAlertAddTable->GetContentTable()->elementAt(nRow,0)->setStyleClass("t5");

	//���水ť
	pAlertAddTable->HideAllErrorMsg();	

	//connect(pAlertAddTable->pSave, SIGNAL(clicked()),this, SLOT(SaveAlert()));	
	//connect(pAlertAddTable->pCancel, SIGNAL(clicked()),this, SLOT(CancelAlert()));
	//connect(pAlertAddTable->pSaveAndAdd, SIGNAL(clicked()),this, SLOT(SaveAndAddAlert()));
	connect(pAlertAddTable->pSave, SIGNAL(clicked()), "showbar();" ,this, SLOT(SaveAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);	
	connect(pAlertAddTable->pCancel, SIGNAL(clicked()), "showbar();" ,this, SLOT(CancelAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	connect(pAlertAddTable->pSaveAndAdd, SIGNAL(clicked()),"showbar();" ,this, SLOT(SaveAndAddAlert()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	//����
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
	pAlertAddTable->pTranslateBtn->show();
	connect(pAlertAddTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

	pAlertAddTable->pExChangeBtn->show();
	connect(pAlertAddTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
	pAlertAddTable->pTranslateBtn->hide();
	pAlertAddTable->pExChangeBtn->hide();
	}
	**/
}

//�ű�������ѡ��
void CAlertList::SelSeverChanged()
{
	GetScriptFileFromServer();
}

//
void CAlertList::GetScriptFileFromServer()
{
	pScriptFile->clear();
	strScriptServerId = lsDeviceId[pScriptServer->currentIndex()];

	std::list<string> keylist;
	std::list<string>::iterator keyitem;

	if(pScriptServer->currentText().find("(_win)") != -1 || pScriptServer->currentText() == "127.0.0.1")
	{
		//windows
		
		//��TXTTemplate.ini��ʼ��pScriptFile
		if(GetIniFileKeys("Scripts", keylist, "TXTTemplate.ini"))
		{
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)
			{
				//��ini������
				pScriptFile->addItem((*keyitem));
			}
		}	

		if(pScriptServer->currentText() == "127.0.0.1")
		{
			string strScriptPath = GetSiteViewRootPath() + "\\cscripts";
			//OutputDebugString(strScriptPath.c_str());
			//���ָ���ķ������Ǳ���
			std::list<string>  fileList = GetScriptFileFromDirectory(strScriptPath);
			for(keyitem = fileList.begin(); keyitem != fileList.end(); keyitem ++)
			{
				pScriptFile->addItem((*keyitem));
			}
		}
	}
	else
	{
		//unix

#ifdef WIN32
		HINSTANCE hdll = LoadLibrary("Monitor.dll");
		if (hdll)
		{
			ListDevice* func = (ListDevice*)::GetProcAddress(hdll,"SCRIPTS");
			if (func)
			{
				string szQuery = GetDeviceRunParam(lsDeviceId[pScriptServer->currentIndex()]);
				char szReturn [svBufferSize] = {0};
				int nSize = sizeof(szReturn);
				//int nSize = szQuery.length();
				char *pszQueryString = new char[szQuery.length()];
				if(pszQueryString)
				{					
					OutputDebugString(szQuery.c_str());
					EidtQueryString(szQuery, pszQueryString);
					OutputDebugString("SelSeverChanged");
					OutputDebugString(pszQueryString);
					if((*func)(pszQueryString, szReturn, nSize))
					{
						
						list<string> lsReturn;
						std::list<string>::iterator lsReturnItem;
						ParserReturnInList(szReturn, lsReturn);
						
						OutputDebugString(szReturn);
						//
						for(lsReturnItem = lsReturn.begin(); lsReturnItem != lsReturn.end(); lsReturnItem ++)
						{
							//��ini������
							pScriptFile->addItem((*lsReturnItem));
						}

					}
					delete []pszQueryString;
				}
			}
			FreeLibrary(hdll);
		}
#else

#endif		
		
	}
}

//
std::list<string>  CAlertList::GetScriptFileFromDirectory(string path)
{
	WIN32_FIND_DATA fd;
	std::list<string> strlist;
	path += "\\*.*";
    HANDLE fr=::FindFirstFile(path.c_str(),&fd);
    while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//
		}
        else
		{
			std::string str1 = fd.cFileName;
			int npos = str1.find(".vbs", 0);
			if(npos >= 0)
			{
				strlist.push_back(fd.cFileName);
			}
		}
    }

	return strlist;
}
//��ʾ�༭�û�����
void CAlertList::initEditAlertTable(string strIndex)
{
	//��ȡ��������
	std::string strAlertType;
	std::string strAlertName;
	std::string strAlertCategory;
	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{
		if(m_pListItem->id == strIndex)
		{
			strAlertNameCond = strIndex;
			strAlertType = m_pListItem->pAlertTypeText->text();
			OutputDebugString("-----------AlertNameText---------\n");
			OutputDebugString(m_pListItem->pAlertNameText->text().c_str());
			strAlertName = m_pListItem->pAlertNameText->text();
			strAlertCategory = m_pListItem->pAlertCategoryText->text();
		}
	}
	//��ʼ������
	strGolobalType = strAlertType;
	OutputDebugString((strAlertType+"\n").c_str());
	int nAlertType = GetIntFromAlertType(strAlertType);	
	initAddAlertTable(nAlertType);
	pEventName->setCurrentIndexByStr(strAlertCategory);
	strOldAlertName = strAlertName;
	pAlertName->setText(strAlertName);

	//��ȡ��������Ŀ��
	strAlertTargerList = GetIniFileString(strIndex, "AlertTarget", "", "alert.ini");
	SetAlertTargetCheck();
	
	//��m_svAlertList��ֵ

	//��ini��ֵ
	
	//
	//pAertTargrt

	//��������	
	string strEmailAdressValue, strOtherAdressValue, strEmailTemplateValue;
	string strSmsNumberValue, strOtherNumberValue, strSmsSendMode, strSmsTemplateValue;	
	string strServerTextValue, strScriptFileValue, strScriptParamValue, strScriptTmp;
	string strServerValue, strLoginNameValue, strLoginPwdValue;
	string strAlertUpgradeValue, strAlertUpgradeToValue, strAlertStopValue;
	//Ϊ���Ticket #112 ��������ECC�ʼ��������ⶨ�����������������롣
	//�պ� 2007-08-02

	//+++++++++++++++++++++++++++�������ӿ�ʼ  �պ� 2007-08-02+++++++++++++++++++++++++++
	int isTitleCheck;
	string strAlertEmailTitle;
	//+++++++++++++++++++++++++++�������ӽ���  �պ� 2007-08-02+++++++++++++++++++++++++++
	p_SelectEMail->disable();
	p_SelectSms->disable();
	p_SelectScript->disable();
	p_SelectSound->disable();
	switch(nAlertType)
	{
		case 1:
			//email����
			p_SelectEMail->setChecked();

			//Ϊ���Ticket #112 ��������ECC�ʼ��������ⶨ�����������������롣
			//�պ� 2007-08-02

			//+++++++++++++++++++++++++++�������ӿ�ʼ  �պ� 2007-08-02+++++++++++++++++++++++++++
			//��ȡ�����ļ���Ϣ��������ҳ����ʾ
			isTitleCheck = GetIniFileInt(strIndex, "isCheck", 0,  "alert.ini");
			if(isTitleCheck == 1)
			{
				pCheckBox->setChecked(true);
				pAlertEmailTitle->enable();
			}
			else
			{
				pCheckBox->setChecked(false);
				pAlertEmailTitle->disable();
			}

			strAlertEmailTitle = GetIniFileString(strIndex, "EmailTitle", "", "alert.ini");
			pAlertEmailTitle->setText(strAlertEmailTitle);			
			//+++++++++++++++++++++++++++�������ӽ���  �պ� 2007-08-02+++++++++++++++++++++++++++

			strEmailAdressValue = GetIniFileString(strIndex, "EmailAdress", "", "alert.ini");
			strOtherAdressValue = GetIniFileString(strIndex, "OtherAdress", "", "alert.ini");
			strEmailTemplateValue = GetIniFileString(strIndex, "EmailTemplate", "", "alert.ini");
			
			pEmailAdress->setCurrentIndexByStr(strEmailAdressValue);
			pOtherAdress->setText(strOtherAdressValue);
			pEmailTemplate->setCurrentIndexByStr(strEmailTemplateValue);

			strAlertUpgradeValue = GetIniFileString(strIndex, "Upgrade", "", "alert.ini");
			strAlertUpgradeToValue = GetIniFileString(strIndex, "UpgradeTo", "", "alert.ini");
			strAlertStopValue = GetIniFileString(strIndex, "Stop", "", "alert.ini");

			pAlertUpgrade->setText(strAlertUpgradeValue);
			pAlertUpgradeTo->setText(strAlertUpgradeToValue);
			pAlertStop->setText(strAlertStopValue);

			break;
		case 2:
			//���ű���
			p_SelectSms->setChecked();

			strSmsNumberValue = GetIniFileString(strIndex, "SmsNumber", "", "alert.ini");
			strOtherNumberValue = GetIniFileString(strIndex, "OtherNumber", "", "alert.ini");
			strSmsSendMode = GetIniFileString(strIndex, "SmsSendMode", "", "alert.ini");
			strSmsTemplateValue = GetIniFileString(strIndex, "SmsTemplate", "", "alert.ini");

			pSmsNumber->setCurrentIndexByStr(strSmsNumberValue);
			pOtherNumber->setText(strOtherNumberValue);
			pSmsSendMode->setCurrentIndexByStr(strSmsSendMode);
			pSmsTemplate->setCurrentIndexByStr(strSmsTemplateValue);

			strAlertUpgradeValue = GetIniFileString(strIndex, "Upgrade", "", "alert.ini");
			strAlertUpgradeToValue = GetIniFileString(strIndex, "UpgradeTo", "", "alert.ini");
			strAlertStopValue = GetIniFileString(strIndex, "Stop", "", "alert.ini");

			pAlertUpgrade->setText(strAlertUpgradeValue);
			pAlertUpgradeTo->setText(strAlertUpgradeToValue);
			pAlertStop->setText(strAlertStopValue);

			break;
		case 3:
			//�ű�����
			p_SelectScript->setChecked();

			strServerTextValue = GetIniFileString(strIndex, "ScriptServer", "", "alert.ini");
			strScriptFileValue = GetIniFileString(strIndex, "ScriptFile", "", "alert.ini");
			strScriptParamValue = GetIniFileString(strIndex, "ScriptParam", "", "alert.ini");
			
			pScriptServer->setCurrentIndexByStr(strServerTextValue);
			GetScriptFileFromServer();
			pScriptFile->setCurrentIndexByStr(strScriptFileValue);
			strScriptServerId = GetIniFileString(strIndex, "ScriptServerId", "", "alert.ini");
			//if(strServerTextValue == "")
			//	pScriptServer->setText("127.0.0.1");
			//else
			//	pScriptServer->setText(strServerTextValue);
			//OutputDebugString(strScriptParamValue.c_str());
			//strScriptTmp = ReplaceStdString(strScriptParamValue, "\\\\", "\\\\\\");
			pScriptParam->setText(strScriptParamValue);
			//refresh();
			//pScriptParam->hide();
			//pScriptParam->show();
			//pScriptParam->refresh();
			break;
		case 4:
			//��������
			p_SelectSound->setChecked();

			strServerValue = GetIniFileString(strIndex, "Server", "", "alert.ini");
			strLoginNameValue = GetIniFileString(strIndex, "LoginName", "", "alert.ini");
			strLoginPwdValue = GetIniFileString(strIndex, "LoginPwd", "", "alert.ini");
			
			pServer->setText(strServerValue);
			pLoginName->setText(strLoginNameValue);
			pLoginPwd->setText(strLoginPwdValue);
			break;
		default:
			break;
	}

	//��������
	int nCond = GetIniFileInt(strIndex, "AlertCond", 0, "alert.ini");
	if(nCond == 1)
	{
		pAlwaysCond->setChecked();
		pOnlyCond->setUnChecked();
		pSelectCond->setUnChecked();
	}
	else if(nCond == 2)
	{
		pOnlyCond->setChecked();
		pAlwaysCond->setUnChecked();
		pSelectCond->setUnChecked();
	}
	else if(nCond == 3)
	{
		pSelectCond->setChecked();
		pAlwaysCond->setUnChecked();
		pOnlyCond->setUnChecked();
	}
	else
	{
		pSelectCond->setChecked();
		pAlwaysCond->setUnChecked();
		pOnlyCond->setUnChecked();		
	}

	string strAlwaysTimesValue = GetIniFileString(strIndex, "AlwaysTimes", "", "alert.ini");
	string strOnlyTimesValue = GetIniFileString(strIndex, "OnlyTimes", "", "alert.ini");
	string strSelTimes1Value = GetIniFileString(strIndex, "SelTimes1", "", "alert.ini");
	string strSelTimes2Value = GetIniFileString(strIndex, "SelTimes2", "", "alert.ini");

	pAlwaysTimes->setText(strAlwaysTimesValue);
	pOnlyTimes->setText(strOnlyTimesValue);
	pSelTimes1->setText(strSelTimes1Value);
	pSelTimes2->setText(strSelTimes2Value);
}

//��ʾ������Alert����
void CAlertList::ShowAlertParam(int nAlertType,int iType)
{
	initAddAlertTable(nAlertType,iType);
}

//���������б�
void CAlertList::AddAlertItem(string strIndex, string strAlertName, string strAlertType, string strAlertCategory, string strAlertState)
{
	/*//���ɽ���
	int numRow = pAlertListTable->numRows();
	
	//ѡ��
	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)pAlertListTable->elementAt(numRow, 0));
	
	//�ı�
	WText * pAlertNameText = new WText(strAlertName, (WContainerWidget*)pAlertListTable->elementAt(numRow , 1));
	
	string strDes = "";
	if(strAlertState == strDisable)
		strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
	else
		strDes = strAlertType;

	WText * pAlertDesText = new WText(strDes, (WContainerWidget*)pAlertListTable->elementAt(numRow , 2));
	WText * pAlertCategoryText = new WText(strAlertCategory, (WContainerWidget*)pAlertListTable->elementAt(numRow , 3));

	WImage *pHistory = new WImage("../Images/historyalert.gif", (WContainerWidget*)pAlertListTable->elementAt(numRow , 4));
	pHistory->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
	m_historyMapper.setMapping(pHistory, strIndex);
	connect(pHistory, SIGNAL(clicked()), &m_historyMapper, SLOT(map()));
	
	WImage *pEdit = new WImage("../Images/edit.gif", (WContainerWidget*)pAlertListTable->elementAt(numRow , 5));
	pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	m_alertMapper.setMapping(pEdit, strIndex); 
	connect(pEdit, SIGNAL(clicked()),"showbar();",  &m_alertMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	
	WText * pAlertTypeText = new WText(strAlertType, (WContainerWidget*)pAlertListTable->elementAt(numRow , 6));
	pAlertTypeText->hide();
	WText * pAlertStateText = new WText(strAlertState, (WContainerWidget*)pAlertListTable->elementAt(numRow , 7));
	pAlertStateText->hide();

	pAlertListTable->adjustRowStyle("tr1","tr2"); 

	if(!GetUserRight("m_AlertRuleEdit"))
		pEdit->hide();
	else
		pEdit->show();

	if(!GetUserRight("m_alertLogs"))
		pHistory->hide();
	else
		pHistory->show();

	//��֯���ݵ��ڴ��б���
	SVTableCell ce;
	ce.setType(adCheckBox);
	ce.setValue(pCheck);
	m_svAlertList.WriteCell(strIndex, 0, ce);

	ce.setType(adText);
	ce.setValue(pAlertNameText);
	m_svAlertList.WriteCell(strIndex, 1, ce);

	ce.setType(adText);
	ce.setValue(pAlertDesText);
	m_svAlertList.WriteCell(strIndex, 2, ce);

	ce.setType(adText);
	ce.setValue(pAlertTypeText);
	m_svAlertList.WriteCell(strIndex, 3, ce);

	ce.setType(adText);
	ce.setValue(pAlertCategoryText);
	m_svAlertList.WriteCell(strIndex, 4, ce);

	ce.setType(adText);
	ce.setValue(pAlertStateText);
	m_svAlertList.WriteCell(strIndex, 5, ce);*/
	Alert_LIST list;
	int numRow = p_AlertTable->GeDataTable()->numRows();
	p_AlertTable->InitRow(numRow);


	//ѡ��
	WCheckBox * pSelect = new WCheckBox("", (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow, 0));
	p_AlertTable->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);

	//�ı�
	WText * pAlertNameText = new WText(strAlertName, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 2));
	p_AlertTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);

	string strDes = "";
	if(strAlertState == strDisable)
		strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
	else
		strDes = strAlertType;

	WText * pAlertDesText = new WText(strDes, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 4));
	p_AlertTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);

	WText * pAlertCategoryText = new WText(strAlertCategory, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 6));
	p_AlertTable->GeDataTable()->elementAt(numRow , 6)->setContentAlignment(AlignCenter);

	WImage *pHistory = new WImage("../Images/historyalert.gif", (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 8));
	p_AlertTable->GeDataTable()->elementAt(numRow , 8)->setContentAlignment(AlignCenter);
	pHistory->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
	m_historyMapper.setMapping(pHistory, strIndex);
	connect(pHistory, SIGNAL(clicked()), &m_historyMapper, SLOT(map()));

	WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 10));
	p_AlertTable->GeDataTable()->elementAt(numRow , 10)->setContentAlignment(AlignCenter);
	pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
	m_alertMapper.setMapping(pEdit, strIndex); 
	connect(pEdit, SIGNAL(clicked()),"showbar();",  &m_alertMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

	WText * pAlertTypeText = new WText(strAlertType, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 12));
	pAlertTypeText->hide();
	WText * pAlertStateText = new WText(strAlertState, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 14));
	pAlertStateText->hide();

	if(!GetUserRight("m_AlertRuleEdit"))
		pEdit->hide();
	else
		pEdit->show();

	if(!GetUserRight("m_alertLogs"))
		pHistory->hide();
	else
		pHistory->show();


	list.pSelect = pSelect;
	list.pAlertNameText = pAlertNameText;
	list.pAlertDesText = pAlertDesText;
	list.pAlertCategoryText = pAlertCategoryText;
	list.pAlertTypeText = pAlertTypeText;
	list.pAlertStateText = pAlertStateText;
	list.id = strIndex;
	m_pListAlert.push_back(list);
}

//�޸ı����б�
void CAlertList::EditAlertItem(string strIndex, string strAlertName, string strAlertType, string strAlertCategory)
{
	string strAlertState;
	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{

		if (m_pListItem->id == strIndex)
		{   
			m_pListItem->pAlertNameText->setText(strAlertName);
			string strDes = "";
			strAlertState = m_pListItem->pAlertStateText->text();
			if(strAlertState == strDisable)
				strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
			else
				strDes = strAlertType;
			m_pListItem->pAlertCategoryText->setText(strAlertCategory);
			break;
		}
	}
	WriteIniFileString(strIndex, "AlertState", strAlertState, "alert.ini");
	/*string strAlertState;
	SVTableRow * pRow = m_svAlertList.Row(strIndex);
    if(pRow)
    {
        SVTableCell * pAlertStateCell = pRow->Cell(5);
        if (pAlertStateCell)
        {
            if (pAlertStateCell->Type() == adText)
			{
				strAlertState = ((WText *)pAlertStateCell->Value())->text();
			}
        }

		WriteIniFileString(strIndex, "AlertState", strAlertState, "alert.ini");

		SVTableCell * pAlertNameCell = pRow->Cell(1);
        if (pAlertNameCell)
        {
            if (pAlertNameCell->Type() == adText)
			{
                 ((WText *)pAlertNameCell->Value())->setText(strAlertName);				 
			}
        }

        SVTableCell * pAlertDesCell = pRow->Cell(2);
        if (pAlertDesCell)
        {
            if (pAlertDesCell->Type() == adText)
			{
				string strDes = "";
				if(strAlertState == strDisable)
					strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
				else
					strDes = strAlertType;
				//string strDes = strAlertType + " " + strAlertCategory + " ("  + strAlertState + ") ";
				((WText *)pAlertDesCell->Value())->setText(strDes);	
			}
        }

        SVTableCell * pAlertTypeCell = pRow->Cell(3);
        if (pAlertTypeCell)
        {
            if (pAlertTypeCell->Type() == adText)
			{
				((WText *)pAlertTypeCell->Value())->setText(strAlertType);
			}
        }		
        SVTableCell * pAlertCategoryCell = pRow->Cell(4);
        if (pAlertCategoryCell)
        {
            if (pAlertCategoryCell->Type() == adText)
			{
				((WText *)pAlertCategoryCell->Value())->setText(strAlertCategory);
			}
        }
	}	*/
}

//Email������ť��Ӧ
void CAlertList::EmailBtn()
{
	iType = 1;
//	strGolobalType = "E-mail����";
	strGolobalType = "EmailAlert";
	ShowAlertParam(1,iType);;
	
	WebSession::js_af_up = "hiddenbar()";
}

//���ű�����ť��Ӧ
void CAlertList::SmsBtn()
{
	iType = 2;
//	strGolobalType = "���ű���";
	strGolobalType = "SmsAlert";
	ShowAlertParam(2,iType);

	WebSession::js_af_up = "hiddenbar()";
}

//�ű�������ť��Ӧ
void CAlertList::ScriptBtn()
{
	iType = 3;
//	strGolobalType = "�ű�����";
	strGolobalType = "ScriptAlert";
	ShowAlertParam(3,iType);

	WebSession::js_af_up = "hiddenbar()";
}

//����������ť��Ӧ
void CAlertList::SoundBtn()
{
	iType = 4;
//	strGolobalType = "��������";
	strGolobalType = "SoundAlert";
	ShowAlertParam(4,iType);

	WebSession::js_af_up = "hiddenbar()";
}

void CAlertList::SelfDefineBtn()
{
	iType = 5;
	//	strGolobalType = "�Զ��屨��";
	strGolobalType = "SelfDefineAlert";
	ShowAlertParam(5,iType);

	WebSession::js_af_up = "hiddenbar()";
}

//���ذ�ť��Ӧ
void CAlertList::BackBtn()
{
	p_MainTable->GetContentTable()->elementAt(0,0)->hide();
	p_MainTable->GetContentTable()->elementAt(2,0)->show();
}
//ѡ��ȫ����ť��Ӧ
void CAlertList::SelAll()
{
    /*for(row it = m_svAlertList.begin(); it != m_svAlertList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
            // �޸�ÿһ���ѡ��״̬
			if (pcell->Type() == adCheckBox)
            {
                ((WCheckBox*)pcell->Value())->setChecked(true);
            }
        }
    }*/

	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(true);
	}
}


//ȫ����ѡ��ť��Ӧ
void CAlertList::SelNone()
{
   /* for(row it = m_svAlertList.begin(); it != m_svAlertList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
            // �޸�ÿһ���ѡ��״̬
			if (pcell->Type() == adCheckBox)
            {
                ((WCheckBox*)pcell->Value())->setChecked(false);
            }
        }
    }*/
	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{
		m_pListItem->pSelect->setChecked(false);
	}
}

//��ѡ��ť��Ӧ
void CAlertList::SelInvert()
{
    /*for(row it = m_svAlertList.begin(); it != m_svAlertList.end(); it++ )
    {
        SVTableCell *pcell = it->second.Cell(0);
        if ( pcell )
        {
             // �޸�ÿһ���ѡ��״̬
			if (pcell->Type() == adCheckBox)
            {
                if(((WCheckBox*)pcell->Value())->isChecked())
					((WCheckBox*)pcell->Value())->setChecked(false);
				else				
					((WCheckBox*)pcell->Value())->setChecked(true);
            }
        }
    }*/

	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{
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

//��������ˢ��
void CAlertList::refresh()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "refresh";
	LogItem.sDesc = strRefresh1;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	OutputDebugString("----------refresh------------\n");

	//nullTable->clear();
	//�����б�
	if(p_HistoryTable)
	{
	//�����ʾ����
	m_AlertLogList.erase(m_AlertLogList.begin(), m_AlertLogList.end());

	//����TableName �� AlertName AlertTime��Ĭ��Ϊ��ǰʱ��ǰ24Сʱ���ڣ� AlertType��ѯ�����������ļ�¼
	QueryRecordSet("alertlogs");

	//������ҳ����
	if(m_AlertLogList.size() % nPageCount  > 0)
	{
	nTotalPage = m_AlertLogList.size() / nPageCount + 1;
	bDivide = false;
	}
	else
	{
	nTotalPage = m_AlertLogList.size() / nPageCount;
	bDivide = true;
	}		

	if(nTotalPage > 0)
	nCurPage = 1;
	else
	nCurPage = 0;


	//��ʾָ����¼ҳ	
	RefreshList();

	}
	if(p_AlertTable)
	{
		if(p_Add)
			{
				if(!GetUserRight("m_AlertRuleAdd"))
					p_Add->hide();
				else
					p_Add->show();
			}

		if (p_Del)
			{
				if(!GetUserRight("m_AlertRuleDel"))
					p_Del->hide();
				else
					p_Del->show();
			}

		if(!GetUserRight("m_AlertRuleEdit"))
		{
			if(p_DisableAlert) p_DisableAlert->hide();
			if(p_EnableAlert) p_EnableAlert->hide();
		}
		else
		{
			if(p_DisableAlert) p_DisableAlert->show();
			if(p_EnableAlert) p_EnableAlert->show();	
		}

	//����б�
	//int nNum = pAlertListTable->numRows();
	//for(int i = 1;i < nNum; i++)
	//{
	//pAlertListTable->deleteRow(1);
	//}
	p_AlertTable->GeDataTable()->clear();
	m_pListAlert.clear();

	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState;
	int  nAdmin = -1;

	//��ini��ȡ�����б�
	if(GetIniFileSections(keylist, "alert.ini"))
	{
		//��ini��ʼ�������б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			int numRow = 0;
			if(IsUserHasAlertRight(*keyitem))
			{
				std::string section = *keyitem;
				Alert_LIST list;

				//��ini������
				strIndex = GetIniFileString((*keyitem), "nIndex", "", "alert.ini");
				strAlertName = GetIniFileString((*keyitem), "AlertName", "", "alert.ini");
				strAlertType = GetIniFileString((*keyitem), "AlertType", "" , "alert.ini");
				strAlertCategory = GetIniFileString((*keyitem), "AlertCategory", "", "alert.ini");
				strAlertState = GetIniFileString((*keyitem), "AlertState", "", "alert.ini");

				//���ɽ���
				numRow = p_AlertTable->GeDataTable()->numRows();
				p_AlertTable->InitRow(numRow);
				char tmp[1024];
				sprintf(tmp,"%d \n",numRow);
				OutputDebugString(tmp);

				//ѡ��
				WCheckBox * pSelect = new WCheckBox("", (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow, 0));
				p_AlertTable->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);

				//�ı�
				WText * pAlertNameText = new WText(strAlertName, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 2));
				p_AlertTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);

				string strDes = "";
				if(strAlertState == strDisable)
					strDes = strAlertType + " <span class =required>("  + strAlertState + ")</span>";
				else
					strDes = strAlertType;
				OutputDebugString((strIndex+","+strAlertName+","+strAlertType+","+strAlertCategory+","+strAlertState+","+strDisable+"\n").c_str());
				WText * pAlertDesText = new WText(strDes, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 4));
				p_AlertTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);

				WText * pAlertCategoryText = new WText(strAlertCategory, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 6));
				p_AlertTable->GeDataTable()->elementAt(numRow , 6)->setContentAlignment(AlignCenter);

				WImage *pHistory = new WImage("../Images/historyalert.gif", (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 8));
				p_AlertTable->GeDataTable()->elementAt(numRow , 8)->setContentAlignment(AlignCenter);
				pHistory->decorationStyle().setCursor(WCssDecorationStyle::Pointer);
				m_historyMapper.setMapping(pHistory, strIndex);
				connect(pHistory, SIGNAL(clicked()), &m_historyMapper, SLOT(map()));

				WImage *pEdit = new WImage("/images/edit.gif", (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 10));
				p_AlertTable->GeDataTable()->elementAt(numRow , 10)->setContentAlignment(AlignCenter);
				pEdit->decorationStyle().setCursor(WCssDecorationStyle::Pointer);   
				m_alertMapper.setMapping(pEdit, strIndex); 
				connect(pEdit, SIGNAL(clicked()),"showbar();",  &m_alertMapper, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);

				WText * pAlertTypeText = new WText(strAlertType, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 12));
				pAlertTypeText->hide();
				WText * pAlertStateText = new WText(strAlertState, (WContainerWidget*)p_AlertTable->GeDataTable()->elementAt(numRow , 14));
				pAlertStateText->hide();


				if(!GetUserRight("m_AlertRuleEdit"))
					pEdit->hide();
				else
					pEdit->show();

				if(!GetUserRight("m_alertLogs"))
					pHistory->hide();
				else
					pHistory->show();

				list.pSelect = pSelect;
				list.pAlertNameText = pAlertNameText;
				list.pAlertDesText = pAlertDesText;
				list.pAlertCategoryText = pAlertCategoryText;
				list.pAlertTypeText = pAlertTypeText;
				list.pAlertStateText = pAlertStateText;
				list.id = section;
				m_pListAlert.push_back(list);
			}
		}
	}

		if(m_pListAlert.size() <= 0)
		{
			p_AlertTable->ShowNullTip();
		}
		else
		{
			p_AlertTable->HideNullTip();
		}
	}
	//����
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
	/**
	//nullTable->clear();
	//�����б�
	if(bHistoryTable)
	{
		//�����ʾ����
		m_AlertLogList.erase(m_AlertLogList.begin(), m_AlertLogList.end());

		//����TableName �� AlertName AlertTime��Ĭ��Ϊ��ǰʱ��ǰ24Сʱ���ڣ� AlertType��ѯ�����������ļ�¼
		QueryRecordSet("alertlogs");

		//������ҳ����
		if(m_AlertLogList.size() % nPageCount  > 0)
		{
			nTotalPage = m_AlertLogList.size() / nPageCount + 1;
			bDivide = false;
		}
		else
		{
			nTotalPage = m_AlertLogList.size() / nPageCount;
			bDivide = true;
		}		
		
		if(nTotalPage > 0)
			nCurPage = 1;
		else
			nCurPage = 0;


		//��ʾָ����¼ҳ	
		RefreshList();
	
	}
	else
	{
		if(!GetUserRight("m_AlertRuleAdd"))
			pAlertTable->pAdd->hide();
		else
			pAlertTable->pAdd->show();

		if(!GetUserRight("m_AlertRuleDel"))
			pAlertTable->pDel->hide();
		else
			pAlertTable->pDel->show();

		if(!GetUserRight("m_AlertRuleEdit"))
		{
			pDisableAlert->hide();
			pEnableAlert->hide();
		}
		else
		{
			pDisableAlert->show();
			pEnableAlert->show();		
		}
		pAlertTable->pAdd->setStyleClass("wizardbutton");

		//����б�
		int nNum = pAlertListTable->numRows();
		for(int i = 1;i < nNum; i++)
		{
			pAlertListTable->deleteRow(1);
		}
		
		m_svAlertList.clear();

		//svtable + edit user ini
		std::list<string> keylist;
		std::list<string>::iterator keyitem;
		string strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState;
		int  nAdmin = -1;
		
		//��ini��ȡ�����б�
		if(GetIniFileSections(keylist, "alert.ini"))
		{
			//��ini��ʼ�������б�
			for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
			{
				if(IsUserHasAlertRight(*keyitem))
				{
					//��ini������
					strIndex = GetIniFileString((*keyitem), "nIndex", "", "alert.ini");
					strAlertName = GetIniFileString((*keyitem), "AlertName", "", "alert.ini");
					strAlertType = GetIniFileString((*keyitem), "AlertType", "" , "alert.ini");
					strAlertCategory = GetIniFileString((*keyitem), "AlertCategory", "", "alert.ini");
					strAlertState = GetIniFileString((*keyitem), "AlertState", "", "alert.ini");

					AddAlertItem(strIndex, strAlertName, strAlertType, strAlertCategory, strAlertState);
				}
			}
		}

		if(m_svAlertList.RowCount() <= 0)
		{
			WText * nText = new WText(strNoAlertItem, (WContainerWidget*)nullTable->elementAt(0 ,0));
			nText ->decorationStyle().setForegroundColor(Wt::red);
			nullTable->elementAt(0 , 0) -> setContentAlignment(AlignTop | AlignCenter);
		}
	}

	//����
	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pMainTable->pTranslateBtn->show();
		connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pMainTable->pExChangeBtn->show();
		connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	

		if(pAlertAddTable)
		{
			pAlertAddTable->pTranslateBtn->show();
			connect(pAlertAddTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

			pAlertAddTable->pExChangeBtn->show();
			connect(pAlertAddTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
		}
	}
	else
	{
		pMainTable->pTranslateBtn->hide();
		pMainTable->pExChangeBtn->hide();

		if(pAlertAddTable)
		{
			pAlertAddTable->pTranslateBtn->hide();
			pAlertAddTable->pExChangeBtn->hide();
		}
	}
	**/
	
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//��AlertType��ȡint
int CAlertList::GetIntFromAlertType(string strType)
{
	int nType = 0;
	if(strType == "EmailAlert")
		nType = 1;
	else if(strType == "SmsAlert")
		nType = 2;
	else if(strType == "ScriptAlert")
		nType = 3;
	else if(strType == "SoundAlert")
		nType = 4;
	else if(strType == "SelfDefine")
		nType = 5;
	else
		nType = 0;
	

/*	if(strType == "E-mail����")
		nType = 1;
	else if(strType == "���ű���")
		nType = 2;
	else if(strType == "�ű�����")
		nType = 3;
	else if(strType == "��������")
		nType = 4;
	else
		nType = 0;
*/
	return nType;
}

//��Alert��ȡCond
int CAlertList::GetIntFromAlertCond()
{	
	int nCond = 0;
	if(pAlwaysCond->isChecked())
		nCond = 1;
	else if(pOnlyCond->isChecked())
		nCond = 2;
	else if(pSelectCond->isChecked())
		nCond = 3;
	else
		nCond = 0;

	return nCond;
}

//�ɵ���ʾ������Alert����
void CAlertList::ShowAlertParamOld(int nAlertType)
{
/*
	//��������Alert��������
	
	//	
	pEmailAdress->hide();
	pOtherAdress->hide();
	pEmailTemplate->hide();
	pEmailAdressLabel->hide();
	pEmailTemplateLabel->hide();

	//	
	pSmsNumber->hide();
	pOtherNumber->hide();
	pSmsTemplate->hide();
	pSmsNumberLabel->hide();
	pSmsTemplateLabel->hide();

	//	
	pServerText->hide();
	pScriptFile->hide();
	pScriptParam->hide();
	pServerTextLabel->hide();
	pScriptFileLabel->hide();
	pScriptParamLabel->hide();

	//	
	//WComboBox * pSoundFile;
	pServer->hide();
	pLoginName->hide();
	pLoginPwd->hide();
	pServerLabel->hide();
	pLoginNameLabel->hide();
	pLoginPwdLabel->hide();
	
	//pEmailTable��������ʽ...
	pScriptTable->hide();
	pSoundTable->hide();

	//����nAlertType��Ŀ¼�ȶ�ȡCombox��List��ѡ��ֵ����ʼ��

	//����nAlertType��m_svAlertList��ȡ���ݣ����߸���alertid��alert.ini������Ӧ��ֵ��
	//....

	//����nAlertType��ʾAlert�����༭����
	switch(nAlertType)
	{
		case 1:
			pEmailAdress->show();
			pOtherAdress->show();
			pEmailTemplate->show();
			pEmailAdressLabel->show();
			pEmailTemplateLabel->show();
			break;

		case 2:
			pSmsNumber->show();
			pOtherNumber->show();
			pSmsTemplate->show();
			pSmsNumberLabel->show();
			pSmsTemplateLabel->show();
			break;

		case 3:
			pServerText->show();
			pScriptFile->show();
			pScriptParam->show();
			pServerTextLabel->show();
			pScriptFileLabel->show();
			pScriptParamLabel->show();
			break;

		case 4:
			pServer->show();
			pLoginName->show();
			pLoginPwd->show();
			pServerLabel->show();
			pLoginNameLabel->show();
			pLoginPwdLabel->show();
			break;

		default:
			break;
	}
*/
}

//�ɵ����ɱ༭�û�����
void CAlertList::initAddAlertTableOld()
{
/*
//	if(pAlertAddTable == NULL)
		pAlertAddTable = new CAnswerTable(this, "�����༭");	
//	else
	{
		//pAlertAddTable->m_pListHelpText.clear();
		//pAlertAddTable->m_pListErrorText.clear();	
		
		//for(int i = 0; i < pAlertAddTable->numRows(); i++)
		//	pAlertAddTable->deleteRow(i);
	}

	pAlertAddTable->setCellPadding(0);
	pAlertAddTable->setCellSpaceing(0);

	pAlertBaseTable = new CFlexTable(pAlertAddTable->GetContentTable()->elementAt(1,0), strBaseTitle);
	pAlertBaseTable->setCellPadding(0);
	pAlertBaseTable->setCellSpaceing(0);
	
	pAlertBaseTable->GetContentTable()->setCellSpaceing(0);
	pAlertBaseTable->GetContentTable()->setCellPadding(0);
	//��������
	//WTable * pTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(0, 0));	
	//pTable->elementAt(0, 0)->setStyleClass("t3left");
	new WText(strAlertName, pAlertBaseTable->GetContentTable()->elementAt(0, 0));	
	pAlertName = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(0, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertNameDes, 1, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertNameError, 2, 1);

	//��������
	//pTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(3, 0));	
	new WText(strAlertTarget, pAlertBaseTable->GetContentTable()->elementAt(3, 0));
	pAertTargrt = new CCheckBoxTreeView(pAlertBaseTable->GetContentTable()->elementAt(3, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strAlertTargetError, 4, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strAlertTargetDes, 5, 1);

	//email����
	//pEmailTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	//pEmailTable->elementAt(0, 0)->setStyleClass("t3left");
	
	pEmailAdressLabel = new WText(strEmailAdress, pAlertBaseTable->GetContentTable()->elementAt(6, 0));
	pEmailAdress = new WSelectionBox(pAlertBaseTable->GetContentTable()->elementAt(6, 1));
	pEmailAdress->addItem("email1");
	pEmailAdress->addItem("email2");
	pEmailAdress->addItem("email3");
	pEmailAdress->addItem("����");
	pEmailAdress->setVerticalSize(4);
	pOtherAdress = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(7, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strEmailAdressError, 8, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strEmailAdressDes, 9, 1);	
		
	pEmailTemplateLabel = new WText(strEmailTemplate, pAlertBaseTable->GetContentTable()->elementAt(10, 0));
	pEmailTemplate = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(10, 1));
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strEmailTemplateDes, 11, 1);
	
	//���ű���
	//pSmsTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(7, 0));
	//pSmsTable->elementAt(0, 0)->setStyleClass("t3left");
	pSmsNumberLabel = new WText(strPhoneNumber, pAlertBaseTable->GetContentTable()->elementAt(12, 0));
	pSmsNumber = new WSelectionBox(pAlertBaseTable->GetContentTable()->elementAt(12, 1));
	pSmsNumber->addItem("sms1");
	pSmsNumber->addItem("sms2");
	pSmsNumber->addItem("sms3");
	pSmsNumber->addItem("����");
	pSmsNumber->setVerticalSize(4);
	pOtherNumber = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(13, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strPhoneNumberError, 14, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strPhoneNumberDes, 15, 1);	
		
	pSmsTemplateLabel = new WText(strSmsTemplate, pAlertBaseTable->GetContentTable()->elementAt(16, 0));
	pSmsTemplate = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(16, 1));
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strSmsTemplateDes, 17, 1);

	//�ű�����
	//pScriptTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(8, 0));
	//pScriptTable->elementAt(0, 0)->setStyleClass("t3left");
	pScriptFileLabel = new WText(strScript, pAlertBaseTable->GetContentTable()->elementAt(18, 0));
	pScriptFile = new WComboBox(pAlertBaseTable->GetContentTable()->elementAt(18, 1));
	pScriptFile->addItem("script1");
	pScriptFile->addItem("script2");
	pScriptFile->addItem("script3");
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptDes, 19, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptDes, 20, 1);

	pServerTextLabel = new WText(strScriptServer, pAlertBaseTable->GetContentTable()->elementAt(21, 0));
	pServerText = new WText(pAlertBaseTable->GetContentTable()->elementAt(21, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strScriptServerError, 22, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptServerDes, 23, 1);
	
	pScriptParamLabel = new WText(strScriptParam, pAlertBaseTable->GetContentTable()->elementAt(24, 0));
	pScriptParam = new WLineEdit(pAlertBaseTable->GetContentTable()->elementAt(24, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strScriptParamError, 25, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strScriptParamDes, 26, 1);

	//��������
	//pSoundTable = new WTable(pAlertBaseTable->GetContentTable()->elementAt(9, 0));
	//pSoundTable->elementAt(0, 0)->setStyleClass("t3left");
	pServerLabel = new WText(strSoundServer, pAlertBaseTable->GetContentTable()->elementAt(27, 0));
	pServer = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(27, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strSoundServerError, 28, 1);
	//pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strSoundServerDes, 28, 1);

	pLoginNameLabel = new WText(strLoginName, pAlertBaseTable->GetContentTable()->elementAt(29, 0));
	pLoginName = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(29, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strLoginNameError, 30, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strLoginNameDes, 31, 1);

	pLoginPwdLabel = new WText(strLoginPwd, pAlertBaseTable->GetContentTable()->elementAt(32, 0));
	pLoginPwd = new WLineEdit("", pAlertBaseTable->GetContentTable()->elementAt(32, 1));
	pAlertAddTable->AddErrorText(pAlertBaseTable->GetContentTable(), strLoginPwdError, 33, 1);
	pAlertAddTable->AddHelpText(pAlertBaseTable->GetContentTable(), strLoginPwdDes, 34, 1);

	//pSoundFile = new WComboBox(pSoundTable->elementAt(0, 1));
	//pSoundFile->addItem("script1");
	//pSoundFile->addItem("script2");
	//pSoundFile->addItem("script3");	

	//��������
	pAlertConditionTable = new CFlexTable(pAlertAddTable->GetContentTable()->elementAt(2,0), strCondTitle);
	pAlertConditionTable->setCellPadding(0);
	pAlertConditionTable->setCellSpaceing(0);
	
	new WText(strEventName, pAlertConditionTable->GetContentTable()->elementAt(0, 0));
	pEventName = new WComboBox(pAlertConditionTable->GetContentTable()->elementAt(0, 1));
	pEventName->addItem("����");
	pEventName->addItem("����");
	pEventName->addItem("�澯");
	pAlertAddTable->AddHelpText(pAlertConditionTable->GetContentTable(), strEventNameDes, 1, 1);

	WButtonGroup * group = new WButtonGroup();
	
	pAlwaysCond = new WRadioButton(strAlwaysCond, pAlertConditionTable->GetContentTable()->elementAt(2, 0));	
	new WText(strAlwaysCond1, pAlertConditionTable->GetContentTable()->elementAt(3, 1));
	pAlwaysTimes = new WLineEdit("", pAlertConditionTable->GetContentTable()->elementAt(3, 1));
	new WText(strAlwaysCond2, pAlertConditionTable->GetContentTable()->elementAt(3, 1));
	
	pOnlyCond = new WRadioButton(strOnlyCond, pAlertConditionTable->GetContentTable()->elementAt(4, 0));	
	new WText(strOnlyCond1, pAlertConditionTable->GetContentTable()->elementAt(5, 1));
	pOnlyTimes = new WLineEdit("", pAlertConditionTable->GetContentTable()->elementAt(5, 1));
	new WText(strOnlyCond2, pAlertConditionTable->GetContentTable()->elementAt(5, 1));
	
	pSelectCond = new WRadioButton(strSelectCond, pAlertConditionTable->GetContentTable()->elementAt(6, 0));	
	new WText(strSelectCond1, pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	pSelTimes1 = new WLineEdit("", pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	new WText(strSelectCond2, pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	pSelTimes2 = new WLineEdit("", pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	new WText(strSelectCond3, pAlertConditionTable->GetContentTable()->elementAt(7, 1));
	
	//pGroupCond = new WRadioButton(strGroupCond, pAlertConditionTable->GetContentTable()->elementAt(7, 0));		
	group->addButton(pAlwaysCond);
	group->addButton(pOnlyCond);
	group->addButton(pSelectCond);
	//group->addButton(pGroupCond);
	
	pAlertAddTable->AddHelpText(pAlertConditionTable->GetContentTable(), strWhenDes, 8, 1);
	pAlertAddTable->AddErrorText(pAlertConditionTable->GetContentTable(), strWhenError, 9, 1);

	//���100%���
	int nRow;
	nRow = pAlertAddTable->GetContentTable()->numRows();
	pAlertAddTable->GetContentTable()->elementAt(nRow,0)->setStyleClass("t5");

	//���水ť
	pAlertAddTable->HideAllErrorMsg();	
	connect(pAlertAddTable->pSave, SIGNAL(clicked()),this, SLOT(SaveAlert()));	
	connect(pAlertAddTable->pCancel, SIGNAL(clicked()),this, SLOT(CancelAlert()));
*/
}

//�жϱ��������Ƿ��ظ�
bool CAlertList::IsAlertNameExist(string strName)
{
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	string strAlertName;

	bool bExist = false;
	//��ini��ȡ�û��б�
	if(GetIniFileSections(keylist, "alert.ini"))
	{
		//��ini��ʼ���û��б�
		for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem ++)	
		{
			//��ini������
			
			strAlertName = GetIniFileString((*keyitem), "AlertName", "", "alert.ini");
			if(strName == strAlertName)
			{
				bExist = true;
				break;
			}
		}
	}

	return bExist;	
}

//�ӽ����ȡѡ�еĽڵ��б�
void CAlertList::GetTreeChecked(WTreeNode * pNode,  std::list<string > &pAlertTargerList,std::list<string > & pUnpAlertTargetList_)
{
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			if(pNode->treeCheckBox_->isChecked())
			{
				pAlertTargerList.push_back(pNode->strId);
				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetTreeChecked(pNode->childNodes()[i],pAlertTargerList,pUnpAlertTargetList_);
			}else{

				pUnpAlertTargetList_.push_back(pNode->strId);

				for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetTreeChecked(pNode->childNodes()[i],pAlertTargerList,pUnpAlertTargetList_);
			}
		}else{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					GetTreeChecked(pNode->childNodes()[i],pAlertTargerList,pUnpAlertTargetList_);
		}
	}
	return;

}
//��ȡѡ�еĽڵ��б�AlertTarget����
void CAlertList::GetAlertTargetList()
{
	pAlertTargetList.clear();
	pUnpAlertTargetList.clear();
	if(pAlertTargerTree->treeroot!=NULL)
	{
		GetTreeChecked(pAlertTargerTree->treeroot, pAlertTargetList,pUnpAlertTargetList);
	}

}
//����ָ���ַ�����ʼ������CheckBox
void CAlertList::SetTreeChecked(WTreeNode * pNode,  std::string  strAlertTargerList,bool bPCheck)
{
	std::string  strSelId;
	if(pNode!=NULL)
	{
		if(pNode->treeCheckBox_!=NULL)
		{
			strSelId=","+ pNode->strId+",";

			int iPos=strAlertTargerList.find(strSelId);
			if(iPos>=0||bPCheck)
			{
				pNode->treeCheckBox_->setChecked();
			}
			else 
			{
				if(pNode->nTreeType==Tree_DEVICE)
				{
					strSelId=","+ pNode->strId;
					iPos =strAlertTargerList.find(strSelId);
					if(iPos>=0)
						pAlertTargerTree->AddMontiorInDevice(pNode);
				}
			}
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					SetTreeChecked(pNode->childNodes()[i], strAlertTargerList, pNode->treeCheckBox_->isChecked());
			
		}
		else
		{
			for (unsigned i = 0; i < pNode->childNodes().size(); ++i)
					SetTreeChecked(pNode->childNodes()[i], strAlertTargerList, pNode->treeCheckBox_->isChecked());
		}
	}

	return;
}
//����AlertTarget����ʼ������CheckBox
void CAlertList::SetAlertTargetCheck()
{
	if(pAlertTargerTree->treeroot!=NULL)
        	SetTreeChecked(pAlertTargerTree->treeroot, strAlertTargerList);
}

///////////////////////////////////������־���/////////////////////////////////////

//����־�б����
void CAlertList::AddHistoryColum(WTable* pContain)
{
	/*new WText(strHTimeLabel, pContain->elementAt(0, 0));
	new WText(strHAlertNameLabel, pContain->elementAt(0, 1));
	new WText(strHDeveiceNameLabel, pContain->elementAt(0, 2));
	new WText(strHMonitorNameLabel, pContain->elementAt(0, 3));
	new WText(strHAlertTypeLabel, pContain->elementAt(0, 4));
	new WText(strHAlertReceiveLabel, pContain->elementAt(0, 5));
	new WText(strHAlertStateLabel, pContain->elementAt(0, 6));

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
	for(int i=0; i<pContain->numColumns();i++)
	{
		pContain->elementAt(0,i)->setStyleClass("t3title");
	}*/
}

//
void CAlertList::AddListItem(string strAlertTime, string strAlertName, string strDeveiceName, 
	string strMonitorName, string strAlertReceive, string strAlertType, string strAlertState)
{
	int numRow = p_HistoryTable->GeDataTable()->numRows();
	p_HistoryTable->InitRow(numRow);
	//OutputDebugString("AddListItem\n");
	new WText(strAlertTime, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 0));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 0)->setContentAlignment(AlignCenter);
	new WText(strAlertName, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 2));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 2)->setContentAlignment(AlignCenter);
	new WText(strDeveiceName, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 4));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 4)->setContentAlignment(AlignCenter);
	new WText(strMonitorName, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 6));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 6)->setContentAlignment(AlignCenter);
	new WText(strAlertType, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 8));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 8)->setContentAlignment(AlignCenter);
	new WText(strAlertReceive, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 10));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 10)->setContentAlignment(AlignCenter);
	new WText(strAlertState, (WContainerWidget*)p_HistoryTable->GeDataTable()->elementAt(numRow , 12));
	p_HistoryTable->GeDataTable()->elementAt(numRow , 12)->setContentAlignment(AlignCenter);
	OutputDebugString("AddListItem1\n");
}

//������־
void CAlertList::AlertHistory(const std::string strIndex)
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "AlertHistory";
	LogItem.sDesc = strAlertHistoryLabel;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//����strIndex��ȡ��ѯ�������������

	//�����ʾ����
	m_AlertLogList.erase(m_AlertLogList.begin(), m_AlertLogList.end());

	strAlertNameCond = "";
	strAlertTypeCond = "";

	for(m_pListItem = m_pListAlert.begin(); m_pListItem != m_pListAlert.end(); m_pListItem ++)
	{
		if(m_pListItem->id == strIndex)
		{
			strAlertNameCond = strIndex;
			strAlertTypeCond = m_pListItem->pAlertDesText->text();
		}
	}

	//����TableName �� AlertName AlertTime��Ĭ��Ϊ��ǰʱ��ǰ24Сʱ���ڣ� AlertType��ѯ�����������ļ�¼
	QueryRecordSet("alertlogs");

	//������ҳ����
	if(m_AlertLogList.size() % nPageCount  > 0)
	{
		nTotalPage = m_AlertLogList.size() / nPageCount + 1;
		bDivide = false;
	}
	else
	{
		nTotalPage = m_AlertLogList.size() / nPageCount;
		bDivide = true;
	}		
	
	if(nTotalPage > 0)
		nCurPage = 1;
	else
		nCurPage = 0;


	//p_MainTable->GetContentTable()->elementAt(0,0)->show();
	//p_MainTable->GetContentTable()->elementAt(1,0)->show();

	//p_HistoryTable->show();
	mainTable->hide();
	mainTable1->show();
	//p_AlertTable->hide();

	//��ʾָ����¼ҳ	
	RefreshList();

	if(m_AlertLogList.size() <= 0)
	{
		p_HistoryTable->ShowNullTip();
	}
	else
	{
		p_HistoryTable->HideNullTip();
	}
	//pHistoryTable
	//�����ݲ���pHistoryListTable
	bHistoryTable = true;
	WebSession::js_af_up = "window.location.reload(true);";
	//WebSession::js_af_up += "hiddenbar();";
	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//��ʷ��־��ǰ
void CAlertList::HistoryForward()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "HistoryForward";
	LogItem.sDesc = strForward;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	nCurPage++;
	
	if(nCurPage >= nTotalPage)
		nCurPage = nTotalPage;
	//
	RefreshList();

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//��ʷ��־����
void CAlertList::HistoryBack()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "HistoryBack";
	LogItem.sDesc = strBack;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	nCurPage--;

	//
	if(nCurPage < 1)
		nCurPage = 1;

	//
	RefreshList();	

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//���ر�����־
void CAlertList::HistoryReturnBtn()
{
	string strUserID = GetWebUserID();

	HitLog LogItem;
	LogItem.sUserName = strUserID;
	LogItem.sHitPro = "Alert";
	LogItem.sHitFunc = "HistoryReturnBtn";
	LogItem.sDesc = strReturn;

	DWORD dcalBegin=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 0, 0);

	//

	//��ʾ�б����	
	//p_AlertTable->show();
	mainTable->show();
	mainTable1->hide();
	//p_HistoryTable->hide();
	bHistoryTable = false;
	WebSession::js_af_up = "window.location.reload(true);";
	//WebSession::js_af_up += "hiddenbar();";

	DWORD dcalEnd1=GetTickCount();
	InsertHitRecord(LogItem.sUserName, LogItem.sHitPro, LogItem.sHitFunc, LogItem.sDesc, 1, dcalEnd1 - dcalBegin);
}

//
string CAlertList::GetAlertTypeStrFormInt(int nType)
{
	string strType = "";
	switch(nType)
	{
		case 0:
			strType = "All";
			break;
		case 1:
			strType = "EmailAlert";
			break;
		case 2:
			strType = "SmsAlert";
			break;
		case 3:
			strType = "ScriptAlert";
			break;
		case 4:
			strType = "SoundAlert";
			break;
		default:
			break;
	}

	return strType;
}

//
string CAlertList::GetAlertStatuStrFormInt(int nStatu)
{
	string strStatu = "";
	switch(nStatu)
	{
		case 1:
			strStatu = "Sucess";
			break;
		case 0:
			strStatu = "Fail";
			break;
		default:
			break;
	}

	return strStatu;
}

//��ѯ����ƥ��
bool CAlertList::IsCondMatch(int nCond, string strCondValue)
{
	bool bMatch = false;
	switch(nCond)
	{
		case 1:
			//AlertRuleName
			if(strAlertNameCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue ==strAlertNameCond)
				{
					bMatch = true;
				}
			}
			break;
		case 2:
			//AlertReceive
			bMatch = true;
			break;
		case 3:
			//AlertTime
			bMatch = true;
			break;
		case 4:
			//AlertType
			if(strAlertTypeCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue.find(strAlertTypeCond) != -1)
				{
					bMatch = true;
				}

				if(strAlertTypeCond == "All")
				{
					bMatch = true;
				}
			}
			break;
		case 5:
			//AlertIndex
			if(strAlertNameCond.empty())
			{
				bMatch = true;
			}
			else
			{
				if(strCondValue ==strAlertNameCond)
				{
					bMatch = true;
				}
			}
			break;
		default:
			break;
	}

	return bMatch;
}

//��ѯ����
void CAlertList::QueryRecordSet(string strTableName)
{
	TTimeSpan ts(0,24,0,0);
	RECORDSET rds=::QueryRecords(strTableName,ts);	
	if(rds==INVALID_VALUE)
	{
		OutputDebugString("Query failed");
		return ;
	}

	LISTITEM item;
	if(!::FindRecordFirst(rds,item))
	{
		//puts("Find list failed");
		return;
	}

	RECORD rdobj;
	while((rdobj=::FindNextRecord(item))!=INVALID_VALUE)
	{
		TTime ctm;

		int state=0;
		int nRecordType = 0;
		int nRecordValue = 0;
		float fRecordValue = 0.0;
		string strRecordValue = "";

		string strQAlertName = "";
		string strQMonitorName = "";
		string strQEnitityName = "";
		string strQAlertReceive = "";
		string strQAlertTime = "";
		string strQAlertType = "";
		string strQAlertStatu = "";

		//��ȡ��־����
		if(!::GetRecordValueByField(rdobj, "_AlertIndex", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertRuleName string failed");
			continue;
		}
		else
		{
			if(!IsCondMatch(5, strRecordValue))
			{
				continue;
			}

			//strQAlertIndex = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_AlertRuleName", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertRuleName string failed");
			continue;
		}
		else
		{
			//if(!IsCondMatch(1, strRecordValue))
			//{
			//	continue;
			//}

			strQAlertName = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_AlertTime", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertTime string failed");
			continue;
		}
		else
		{
			strQAlertTime = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_DeviceName", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record EntityName string failed");
			return ;
		}
		else
		{
			strQEnitityName = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_MonitorName", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record MonitorName string failed");
			continue;
		}
		else
		{
			strQMonitorName = strRecordValue;
		}

		if(!::GetRecordValueByField(rdobj, "_AlertReceive", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertReceive string failed");
			continue;
		}
		else
		{
			strQAlertReceive = strRecordValue;
		}

		//nRecordValue
		if(!::GetRecordValueByField(rdobj, "_AlertType", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertType string failed");
			continue;
		}
		else
		{
			strQAlertType = GetAlertTypeStrFormInt(nRecordValue);

			if(!IsCondMatch(4, strQAlertType))
			{
				continue;
			}			
		}

		//fRecordValue
		if(!::GetRecordValueByField(rdobj, "_AlertStatus", state, nRecordType, nRecordValue, fRecordValue, strRecordValue))
		{
			//puts("Get record AlertStatus string failed");
			continue;
		}
		else
		{
			strQAlertStatu = GetAlertStatuStrFormInt(nRecordValue);
		}
		
		//OutputDebugString("\nAlertTime:");
		//OutputDebugString(strQAlertTime.c_str());
		//OutputDebugString("\nAlertName:");
		//OutputDebugString(strQAlertName.c_str());

		//
		AlertLogItem * item = new AlertLogItem();
	
		item->strAlertName = strQAlertName;
		item->strMonitorName = strQMonitorName;
		item->strEnitityName = strQEnitityName;
		item->strAlertReceive = strQAlertReceive;
		item->strAlertTime = strQAlertTime;
		item->strAlertType = strQAlertType;
		item->strAlertStatu = strQAlertStatu;

		m_AlertLogList.push_back(item);		
	}

	::ReleaseRecordList(item);
	::CloseRecordSet(rds);	
}

//
void CAlertList::RefreshList()
{
	p_HistoryTable->GeDataTable()->clear();

	char tmpchar[10] = {0};
	string strTipInfo = strPage;	
	sprintf(tmpchar, "%d", nCurPage);
	strTipInfo += tmpchar;
	strTipInfo += strPageCount;
	sprintf(tmpchar, "%d", nTotalPage);
	strTipInfo += tmpchar;
	//strTipInfo += "  ҳ������";
	//sprintf(tmpchar, "%d", nPageCount);
	//strTipInfo += tmpchar;
	strTipInfo += strRecordCount;
	sprintf(tmpchar, "%d", m_AlertLogList.size());
	strTipInfo += tmpchar;
	OutputDebugString((strTipInfo+"----\n").c_str());
	p_HistoryTable->pSelReverse->setText(strTipInfo);
	((WText *)((WTableCell*)(p_HistoryTable->pSelReverse->parent()))->parent())->setText("");

	if(m_AlertLogList.size() <= 0)
	{
		return;
	}

	int index = 0;
	int nPage = 0;
	list<AlertLogItem *> ::iterator item;
	for(item = m_AlertLogList.begin(); item != m_AlertLogList.end(); item ++)		
	{
		nPage = index / nPageCount;
		nPage += 1;
		if(!bDivide && nCurPage == nTotalPage)
		{
			if(nPage == nTotalPage)
			{
				AddListItem((*item)->strAlertTime, (*item)->strAlertName, (*item)->strEnitityName, (*item)->strMonitorName, 
					(*item)->strAlertReceive, (*item)->strAlertType, (*item)->strAlertStatu);					
			}
		}
		else if(nPage == nCurPage)
		{
				AddListItem((*item)->strAlertTime, (*item)->strAlertName, (*item)->strEnitityName, (*item)->strMonitorName, 
					(*item)->strAlertReceive, (*item)->strAlertType, (*item)->strAlertStatu);
		}
		else
		{

		}

		index ++;
	}
}

//////////////////////////////////////////////////////////////////////////////////

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void alertmain(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("AlertForm");
    CAlertList alertform(app.root());
	alertform.appSelf = &app;
	app.setBodyAttribute(" class='workbody' ");
    app.exec();
}

//
int main(int argc, char *argv[])
{
    func p = alertmain;

	if (argc == 1) 
    {
        char buf[256];

		WebSession s(buf, false);
        s.start(p);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }

    return 0;
}