/////////////////////////////////////////////////////////////////////////////////////////////////
//
//1������Xml�Ĺ��ߺ�����
//
//2���ӷ�������ȡ���ݲ�����CTransferDataList����ĺ�����
//
//3�������̿��ƺ�����
//		a����*.files\data.xml��ȡ�û��趨��SV_IP��ֵ�� CTransferDataList
//		   ��CTransferData��m_strIP�ȣ���
//		b������CTransferDataList����svapi��ȡ����˵��������������״̬��
//		   ��Ϣ��CTransferData��m_lstParentId��m_lstMonitorId��m_lstStatus��m_lstMenuItemDes�ȣ���
//		c������CTransferDataList����*.files\data.xml�Թ���˵�����ȡ����shap״̬�����lstShap��
//		   lstColor����Ϣ����
//		d����ȡ*.files\vml_*.tpl������lstShap��lstColor���´���vml_*.html�Ըı�ڵ���ɫ�ȡ�
//4����ʱ���õ��Ժ�����õĺ�����
//
//5������ں�����
//	 ���������strDataXmlPath version
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlOper.h"
//#include "Wininet.h"
#include "TransferData.h" 
#include "ChineseCodeLib.h"
#include "XMLParse.h"
//#import "C:\\WINNT\\system32\\msxml4.dll" named_guids, raw_interfaces_only

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"
//#include "../../base/GetInstallPath.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#define MYDEBUG
CString m_strXmlFile;
CString strPageId;
int nIsMainTain;
int nIsMainTainLeader;
//typedef BOOL(GatherData)(CStringList& lstPara, CStringList& lstGroup,CStringList& lstMonitor, CStringList& lstStatus,CStringList& lstInfo);

typedef BOOL(GatherData)(CTransferDataList& cTDL);
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

//CWinApp theApp;

using namespace std;
using namespace MSXML2;
#include <string>
void DebugToFile(const char * szMsg)
{
	FILE * fp = fopen("xmloper.txt", "a+");
	if (fp) {
		fputs(szMsg, fp); 
		fputs("\r\n", fp);
		fclose(fp);
	}
}

//////////////////����Xml�Ĺ��ߺ���////////////////////////////////////////

//��ȡָ��Xml�ڵ��ָ������ֵ
CString GetNodeAttribute(MSXML2::IXMLDOMNode * pNode, CString strAttr)
{
	HRESULT hr;
	MSXML2::IXMLDOMElement * pElement = NULL;	
	VARIANT vValue = {0};
	CString strValue = _T("");

	if (!pNode)
		return strValue;

	hr = pNode->QueryInterface(MSXML2::IID_IXMLDOMElement, (void**)&pElement);
	if (SUCCEEDED(hr)) {
		hr = pElement->getAttribute(strAttr.AllocSysString(), &vValue);
		if (SUCCEEDED(hr)) {
			if (VT_BSTR == vValue.vt) {
				strValue = vValue.bstrVal;
			}
		}		
		SAFERELEASE(pElement);
	}
	return strValue;
}

//�趨ָ��Xml�ڵ��ָ������ֵ
HRESULT SetNodeAttribute(MSXML2::IXMLDOMNode * pNode, CString strAttrName, CString strAttrValue)
{
	HRESULT hr;
	MSXML2::IXMLDOMElement * pElement = NULL;
	VARIANT vValue = {0};
	
	vValue.vt = VT_BSTR;
	vValue.bstrVal = strAttrValue.AllocSysString();

	hr = pNode->QueryInterface(MSXML2::IID_IXMLDOMElement, (void**)&pElement);
	if (SUCCEEDED(hr)) {
		hr = pElement->setAttribute(strAttrName.AllocSysString(), vValue);
		SAFERELEASE(pElement);
	}

	return hr;
}

//�趨ָ��Xml�ڵ��Text
HRESULT SetNodeText(MSXML2::IXMLDOMNode * pNode, CString strText)
{
	HRESULT hr;
	hr = pNode->put_text(strText.AllocSysString());	
	return hr;
}

//��ȡָ��Xml�ڵ��Text
CString GetNodeText(MSXML2::IXMLDOMNode * pNode)
{
	HRESULT hr;	
	BSTR bstrText = NULL;	
	CString strValue = _T("");

	if (!pNode)
		return strValue;

	hr = pNode->get_text(&bstrText);
	if (SUCCEEDED(hr)) {
		if (bstrText)
			strValue = bstrText;
	}

	::SysFreeString(bstrText);	

	return strValue;
}

//ɾ��ָ��Xml�ڵ�
HRESULT RemoveNode(MSXML2::IXMLDOMNode * pNode)
{
	HRESULT hr;
	MSXML2::IXMLDOMNode * pParentNode = NULL;
	hr = pNode->get_parentNode(&pParentNode);
	
	if (SUCCEEDED(hr)) {
		hr = pParentNode->removeChild(pNode, NULL);
		SAFERELEASE(pParentNode);
	}

	return hr;
}

//����Xml�ڵ�
HRESULT InsertNode(MSXML2::IXMLDOMDocument2 * pDoc, MSXML2::IXMLDOMNode * pParentNode, CString strNodeName, CString strNodeText, const char* szNodeNamespaceURI , const char* szAttr1Name, const char* szAttr1Value) 
{
	HRESULT hr;
	MSXML2::IXMLDOMNode * pNewNode = NULL, *p1 = NULL;
	
	VARIANT  after;
	after.vt = VT_EMPTY;

	VARIANT varType = {0};
	varType.vt = VT_I4;													
	varType.lVal = MSXML2::NODE_ELEMENT;

	if (szNodeNamespaceURI) {
		CString strNSURI = szNodeNamespaceURI;
		hr = pDoc->createNode(varType, strNodeName.AllocSysString(), strNSURI.AllocSysString(), &pNewNode);
	}
	else
		hr = pDoc->createNode(varType, strNodeName.AllocSysString(), NULL, &pNewNode);

	if (SUCCEEDED(hr)) {
		if (szAttr1Name && szAttr1Value) {
			SetNodeAttribute(pNewNode, szAttr1Name, szAttr1Value);
		}

		SetNodeText(pNewNode, strNodeText);
		pParentNode->insertBefore(pNewNode, after, &p1);
		//pParentNode->appendChild(pNewNode, NULL);		
		SAFERELEASE(pNewNode);
		SAFERELEASE(p1);
	}
	
	return hr;
}

//����hurl�ڵ�
void InsertHyperlinkNode(MSXML2::IXMLDOMDocument2 *pDoc, MSXML2::IXMLDOMNode *pHyperlinksNode, CStringList& lstStr)
{
	CString strID   = _T("");
	CString strDesc = _T("");
	CString strAddr = _T("");
	CString strStatus = _T("0");

	HRESULT hr;
	MSXML2::IXMLDOMNode * pHyperlinkNode = NULL, * p = NULL;
	
	VARIANT  after;
	after.vt = VT_EMPTY;

	VARIANT varType = {0};
	varType.vt = VT_I4;													
	varType.lVal = MSXML2::NODE_ELEMENT;

	POSITION pos = lstStr.GetHeadPosition();
	while(pos)	{
		CString strTemp = lstStr.GetNext(pos);
				
		//printf("InsertHyperlinkNode = %s start \n", strTemp);
		if(strTemp.Find("ID=") == 0) {
			strID = strTemp.Right(strTemp.GetLength() - strlen("ID="));
		}
		else if(strTemp.Find("DESC=") == 0) {
			strDesc = strTemp.Right(strTemp.GetLength() - strlen("DESC="));
		}
		else if(strTemp.Find("ADDR=") == 0) {
			strAddr = strTemp.Right(strTemp.GetLength() - strlen("ADDR="));
		}
		else if(strTemp.Find("STAT=") == 0) {
			strStatus = strTemp.Right(strTemp.GetLength() - strlen("STAT="));
		}
		else {
		}
	}

	// MUST specify a namespaceUI when a namespace node is created. namespaceUI is provided by parent node, Take care
	hr = pDoc->createNode(varType, ::SysAllocString(L"HLURL:Hyperlink"), ::SysAllocString(L"urn:schemas-microsoft-com:office:visio:dghlinkext"), &pHyperlinkNode);
	if (SUCCEEDED(hr)) {
		SetNodeAttribute(pHyperlinkNode, "ID", strID);

		hr = pHyperlinksNode->appendChild(pHyperlinkNode, NULL);

		InsertNode(pDoc, pHyperlinkNode, "HLURL:Description", strDesc, "urn:schemas-microsoft-com:office:visio:dghlinkext");
		InsertNode(pDoc, pHyperlinkNode, "HLURL:Address", strAddr, "urn:schemas-microsoft-com:office:visio:dghlinkext");
		InsertNode(pDoc, pHyperlinkNode, "HLURL:SubAddress", "", "urn:schemas-microsoft-com:office:visio:dghlinkext");
		//<HLURL:ExtraInfo></HLURL:ExtraInfo>
		InsertNode(pDoc, pHyperlinkNode, "HLURL:ExtraInfo","", "urn:schemas-microsoft-com:office:visio:dghlinkext");
		InsertNode(pDoc, pHyperlinkNode, "HLURL:Default", "", "urn:schemas-microsoft-com:office:visio:dghlinkext");
		InsertNode(pDoc, pHyperlinkNode, "HLURL:AbsoluteURL", strAddr, "urn:schemas-microsoft-com:office:visio:dghlinkext");
		InsertNode(pDoc, pHyperlinkNode, "HLURL:Status", strStatus, "urn:schemas-microsoft-com:office:visio:dghlinkext");
		
		//�Ƿ���ά��ģ�� 
		if(nIsMainTain == 1)
		{
			if(nIsMainTainLeader)
			{
				//������쵼������������
				InsertNode(pDoc, pHyperlinkNode, "HLURL:NewWindow", "0", "urn:schemas-microsoft-com:office:visio:dghlinkext");
			}
			else
			{
				if(strAddr == "#")
				{
					InsertNode(pDoc, pHyperlinkNode, "HLURL:NewWindow", "0", "urn:schemas-microsoft-com:office:visio:dghlinkext");
				}
				else
				{
					InsertNode(pDoc, pHyperlinkNode, "HLURL:NewWindow", "3", "urn:schemas-microsoft-com:office:visio:dghlinkext");			
				}

			}
		}
		else
		{
			if(strAddr == "#")
			{
				InsertNode(pDoc, pHyperlinkNode, "HLURL:NewWindow", "0", "urn:schemas-microsoft-com:office:visio:dghlinkext");
			}
			else
			{
				InsertNode(pDoc, pHyperlinkNode, "HLURL:NewWindow", "3", "urn:schemas-microsoft-com:office:visio:dghlinkext");
			}
		}

		//printf("InsertHyperlinkNode = %s succes \n", strID);
		SAFERELEASE(pHyperlinkNode);
	} 
}

//��ȡshap�ڵ��ָ������ֵ
BOOL RetrievePropertyValue(MSXML2::IXMLDOMNode *pShapeNode, const char* szProperty, char * szOut)
{
	HRESULT hr;
	BOOL bRet = FALSE;	
	MSXML2::IXMLDOMNode * pPropNode = NULL;
	MSXML2::IXMLDOMNode * pValueNode = NULL;
	CString strValue = _T("");
	CString strSelect = _T("");

	strSelect.Format("Prop[@NameU=\"%s\"]", szProperty);

	//Select Prop Node whith NameU=IP
	hr = pShapeNode->selectSingleNode(strSelect.AllocSysString(), &pPropNode);
	check_valid(hr, pPropNode);

	hr = pPropNode->selectSingleNode(::SysAllocString(L"Value"), &pValueNode);
	check_valid(hr, pValueNode);

	strValue = GetNodeText(pValueNode);

	if (!strValue.IsEmpty()) {
		if (!strValue.CompareNoCase("UNKNOWN"))
			goto CleanUp;

		strcpy(szOut, strValue);
		bRet = TRUE;
	}

CleanUp:

	SAFERELEASE(pValueNode);
	SAFERELEASE(pPropNode);

	return bRet;
}

//hurl�ڵ��Ƿ����
BOOL IsHyperlinkNodesExisted(MSXML2::IXMLDOMNode *pShapeNode)
{
	BOOL bRet = FALSE;
	long length = 0;
	HRESULT hr;
	MSXML2::IXMLDOMNodeList * pNodeList = NULL;
	hr = pShapeNode->selectNodes(::SysAllocString(L"Scratch/B/SolutionXML/HLURL:Hyperlinks/HLURL:Hyperlink"), &pNodeList);
	//hr = pShapeNode->selectNodes(::SysAllocString(L"Scratch/B/SolutionXML"), &pNodeList);
	check_valid(hr, pNodeList);

	hr = pNodeList->get_length(&length);
	CHECKHR(hr);

	if (0 != length)
		bRet = TRUE;

CleanUp:
	
	SAFERELEASE(pNodeList);

	return bRet;

}

//ɾ��hurl�ڵ�
void DeleteHyperlinkNodes(MSXML2::IXMLDOMNode *pShapeNode)
{
	long length = 0;
	int i = 0;
	HRESULT hr;
	MSXML2::IXMLDOMNodeList * pNodeList = NULL;
	MSXML2::IXMLDOMNode * pHyperlinkNode = NULL;

	hr = pShapeNode->selectNodes(::SysAllocString(L"Scratch/B/SolutionXML/HLURL:Hyperlinks/HLURL:Hyperlink"), &pNodeList);
	check_valid(hr, pNodeList);

	hr = pNodeList->get_length(&length);
	CHECKHR(hr);

	for (i=0; i<length; i++) {		
		hr = pNodeList->get_item(i, &pHyperlinkNode);
		check_valid(hr, pNodeList);
		
		RemoveNode(pHyperlinkNode);
		SAFERELEASE(pHyperlinkNode);
	}
	
CleanUp:
	SAFERELEASE(pHyperlinkNode);
	SAFERELEASE(pNodeList);	
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////�ӷ�������ȡ���ݲ�����ָ������ĺ���////////////////////////////////////

//����monitorid��ѯMonitor��ָ������ֵ
string  GetMonitorPropValue(string strId, string strPropName)
{
	string strTmp = "";

	//�����id
	OBJECT objMonitor = GetMonitor(strId);
	if(objMonitor != INVALID_VALUE)
    {
        MAPNODE motnitornode = GetMonitorMainAttribNode(objMonitor);
        if(motnitornode != INVALID_VALUE)
        {
			FindNodeValue(motnitornode, strPropName, strTmp);
		}

		CloseMonitor(objMonitor);
	}

	return strTmp;
}

//
bool isDisable(string &szMonitorID)
{
    bool bDisable = false;
    OBJECT objMonitor = GetMonitor(szMonitorID);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
			string szDisable = "";
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true" || szDisable == "time")
                bDisable = true;
        }
        CloseMonitor(objMonitor);
    }
    return bDisable;
}

//�ݹ��ȡ�����µ�����monitorid�����˵���ֵ
void EnumEntity(std::string szIndex, CTransferData *pCTransferData)
{
	OBJECT objDevice = GetEntity(szIndex);
    if(objDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {			
            for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
            {
     			string strStdId = "";
				string strStdInfo = "";
				
				CString strId = "";
				CString strParentId = "";
				CString strStatus = "0";
				CString strInfo = "";

				strStdId  = (*lstItem).c_str();
				
				strId = CString(strStdId.c_str());
				strParentId = CString(FindParentID(strStdId.c_str()).c_str());

				//��ȡIdΪstrMonitorId�����м�����Ļ�����Ϣ
				pCTransferData->m_lstParentId.AddTail(strParentId);
				pCTransferData->m_lstMonitorId.AddTail(strId);

				//						
				strStdInfo = "";
				strStdInfo += GetMonitorPropValue(strStdId, "sv_name");
				strStdInfo += "  ";
				
				//����monitorid��ȡdyn��Ϣ�е�״̬��Ϣ
				SVDYN dyn;
				if(GetSVDYN(strStdId, dyn))
				{
					//if(isDisable(strStdId))
					//{
					//	strStatus.Format("%d", 4);
					//}
					//else
						strStatus.Format("%d", dyn.m_state);

					
					//strStdInfo += dyn.m_displaystr;
					strInfo.Format("%s %s", strStdInfo.c_str(), dyn.m_displaystr);
					/*strInfo = CString(strStdInfo.c_str());*/
				}

				pCTransferData->m_lstMenuItemDes.AddTail(strInfo);
				pCTransferData->m_lstStatus.AddTail(strStatus);
			}
        }
        CloseEntity(objDevice);			
    }     
}

//�ݹ��ȡ�����µ�����monitorid�����˵���ֵ
void EnumGroup(std::string szIndex, CTransferData *pCTransferData)
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
					EnumEntity((*lstItem), pCTransferData);
                }            
            }
            
			if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    EnumGroup(szSubGroupID, pCTransferData);
                }
            }

            CloseGroup(group);
        }        
    }
}

//�����û��趨�Ĳ�����ȡ����NodeMenu�Ĳ���
void GetHyperlinkNodesMenuData(int nNodeType, CString strNodeparam, CTransferData *pCTransferData)
{
	//�Ƿ��ֹ���߼� ����dyn���ȡ��
	//pCTransferData->m_lstParentId.AddTail(strNodeparam);
	//pCTransferData->m_lstMonitorId.AddTail(strNodeparam);	
	//pCTransferData->m_lstMenuItemDes.AddTail(strNodeparam);
	//pCTransferData->m_lstStatus.AddTail("1");
	
	//��ȡName Find strMonitor�����м�����Ļ�����Ϣ
	PAIRLIST retlist;
	std::list<struct sv_pair>::iterator svitem;

	/*GetAllMonitorsInfo(retlist, "sv_monitortype");*/
	switch(nNodeType)
	{
		case 1:
			//GetAllMonitorsInfo(retlist, "sv_ip");
			GetAllEntitysInfo(retlist, "_MachineName");
			break;
		case 2:
			GetAllGroupsInfo(retlist, "sv_name");
			break;
		case 3:
			GetAllEntitysInfo(retlist, "sv_name");
			break;
		case 4:
			GetAllMonitorsInfo(retlist, "sv_name");
			break;
		case 5:
			//app
			break;
		default:
			break;
	}

	
	CString strInfo = "";
	CString strParentId = "";
	CString strStatus = "0";
	CString strId = "";
	CString strTemp = "";
	
	string strStdInfo = "";
	string strStdId = "";
	//string strStdParentId = "";

	for(svitem = retlist.begin(); svitem != retlist.end(); svitem++)
	{
		//��ȡid����id
		strId = CString((*svitem).name.c_str());
		strStdId = (*svitem).name;
		//strStdParentId = FindParentID((*svitem).name);
		strParentId = CString(FindParentID((*svitem).name).c_str());
		
		//
		strTemp = CString((*svitem).value.c_str());
		SVDYN dyn;

		if(nNodeType == 1)
		{
			if(!strTemp.IsEmpty() && strTemp == strNodeparam)
			{
				//sv_ip��ʽ
				////��ȡIdΪstrMonitorId�����м�����Ļ�����Ϣ
				//pCTransferData->m_lstParentId.AddTail(strParentId);
				//pCTransferData->m_lstMonitorId.AddTail(strId);	
				//
				////						
				//strStdInfo = "";
				//strStdInfo += GetMonitorPropValue(strStdId, "sv_name");
				//strStdInfo = "  ";

				////����monitorid��ȡdyn��Ϣ�е�״̬��Ϣ
				//if(GetSVDYN(strStdId, dyn))
				//{
				//	strStatus.Format("%d", dyn.m_state);
				//	
				//	//strStdInfo += dyn.m_displaystr;
				//	strInfo.Format("%s %s", strStdInfo.c_str(), dyn.m_displaystr);
				//	//strInfo = CString(strStdInfo.c_str());
				//}
				//
				//pCTransferData->m_lstMenuItemDes.AddTail(strInfo);
				//pCTransferData->m_lstStatus.AddTail(strStatus);

				EnumEntity(strStdId, pCTransferData);
			}
		}
		else
		{
			if(strTemp.Find(strNodeparam) != -1)
			{
				//�顢�豸�ٵݹ�ȡ�������Ϣ
				switch(nNodeType)
				{
					case 2:
						EnumGroup(strStdId, pCTransferData);
						break;
					case 3:
						EnumEntity(strStdId, pCTransferData);
						break;
					case 4:
						//��ȡIdΪstrMonitorId�����м�����Ļ�����Ϣ
						pCTransferData->m_lstParentId.AddTail(strParentId);
						pCTransferData->m_lstMonitorId.AddTail(strId);

						//						
						strStdInfo = "";
						strStdInfo += GetMonitorPropValue(strStdId, "sv_name");
						strStdInfo += "  ";

						
						//����monitorid��ȡdyn��Ϣ�е�״̬��Ϣ						
						if(GetSVDYN(strStdId, dyn))
						{
							//if(isDisable(strStdId))
							//{
							//	strStatus.Format("%d", 4);
							//}
							//else
								strStatus.Format("%d", dyn.m_state);
							
							//strStdInfo += dyn.m_displaystr;
							strInfo.Format("%s %s", strStdInfo.c_str(), dyn.m_displaystr);
							//strInfo = CString(strStdInfo.c_str());
						}

						pCTransferData->m_lstMenuItemDes.AddTail(strInfo);

						pCTransferData->m_lstStatus.AddTail(strStatus);
						break;
					default:
						break;
				}
			}
		}
		//else if(nNodeType == 2)
		//{
		//	if(strTemp.Find(strNodeparam) != -1)
		//	{
		//		EnumGroup(strStdId, pCTransferData);
		//	}
		//}
		//else if(nNodeType == 3)
		//{
		//	if(strTemp.Find(strNodeparam) != -1)
		//	{
		//		EnumEntity(strStdId, pCTransferData);
		//	}
		//}
		//else
		//{
		//	strTemp = GetMonitorPropValue(strStdParentId, "sv_name");
		//	strTemp += ":";
		//	strTemp += GetMonitorPropValue(strStdId, "sv_name");
		//	
		//	//nNodeType == 4
		//	if(strTemp.Find(strNodeparam) != -1)
		//	{

		//		//��ȡIdΪstrMonitorId�����м�����Ļ�����Ϣ
		//		pCTransferData->m_lstParentId.AddTail(strParentId);
		//		pCTransferData->m_lstMonitorId.AddTail(strId);

		//		//						
		//		strStdInfo = "";
		//		strStdInfo += strTemp;
		//		strStdInfo += "  ";

		//		
		//		//����monitorid��ȡdyn��Ϣ�е�״̬��Ϣ
		//		
		//		if(GetSVDYN(strStdId, dyn))
		//		{
		//			if(isDisable(strStdId))
		//			{
		//				strStatus.Format("%d", 4);
		//			}
		//			else
		//				strStatus.Format("%d", dyn.m_state);
		//			
		//			//strStdInfo += dyn.m_displaystr;
		//			strInfo.Format("%s %s", strStdInfo.c_str(), dyn.m_displaystr);
		//			//strInfo = CString(strStdInfo.c_str());
		//		}

		//		pCTransferData->m_lstMenuItemDes.AddTail(strInfo);

		//		pCTransferData->m_lstStatus.AddTail(strStatus);
		//	}
		//}

		strTemp = "";
	}
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////���̿�����������Visio=>�ṹ=>��̨����=>��ȷ��html��xml����//////////////

//��Visio������data.xml�ļ��л�ȡ�û���shap�趨��SV_IP��ֵ�� ������ָ������
void GetAllRunningParas(MSXML2::IXMLDOMDocument2 *pDoc, MSXML2::IXMLDOMNode *pPageNode, CTransferDataList& cTDL)
{
	HRESULT hr;
	long lLength = 0;
	int i = 0;

	char szValue[512] = {0};	

	MSXML2::IXMLDOMNodeList	* pShapeList	= NULL;
	MSXML2::IXMLDOMNode		* pShapeNode	= NULL;	

	hr = pPageNode->selectNodes(::SysAllocString(L".//Shape"), &pShapeList);
	check_valid(hr, pShapeList);
	
	hr = pShapeList->get_length(&lLength);
	CHECKHR(hr);

	//printf("Shape Count = %d\n", lLength);
	for (i=0; i<lLength; i++) 
	{
		hr = pShapeList->get_item(i, &pShapeNode);
		check_valid(hr, pShapeNode);

		if (!IsHyperlinkNodesExisted(pShapeNode))
		{
			//û��LinkXmlNode, ������Node, ��ʱ����
			//MSXML2::IXMLDOMNode * pNode = CreateSolutionXML(pDoc, pShapeNode);
			//printf("Shape i = %d\n", i);
			continue;
		}	

		CTransferData* pTD = new CTransferData();
		if (!pTD)
			goto CleanUp;

		//�����豸���� ���Ժ�������������һ����ʾ
		if (RetrievePropertyValue(pShapeNode, "SV_Des", szValue)) 
		{
			pTD->m_strDes = szValue;
			//printf("RetrievePropertyValue = %s i = %d\n", szValue, i);
		}

		if (RetrievePropertyValue(pShapeNode, "SV_IP", szValue)) 
		{
			pTD->m_strIP = szValue;
			//printf("RetrievePropertyValue = %s i = %d\n", szValue, i);
		}
		else if (RetrievePropertyValue(pShapeNode, "SV_Link", szValue)) 
		{
			pTD->m_strLinkPage = szValue;
			//printf("RetrievePropertyValue = %s i = %d\n", szValue, i);
		}
		//else if (RetrievePropertyValue(pShapeNode, "SV_App", szValue)) 
		//{
		//	pTD->m_strApp = szValue;
		//}
		else if (RetrievePropertyValue(pShapeNode, "SV_Group", szValue)) 
		{
			pTD->m_strGroup = szValue;
			//printf("RetrievePropertyValue = %s i = %d\n", szValue, i);
		}
		else if (RetrievePropertyValue(pShapeNode, "SV_Entity", szValue)) 
		{
			pTD->m_strEntity = szValue;
			//printf("RetrievePropertyValue = %s i = %d\n", szValue, i);
		}
		else if (RetrievePropertyValue(pShapeNode, "SV_Monitor", szValue)) 
		{
			pTD->m_strMonitor = szValue;
			//printf("RetrievePropertyValue = %s i = %d\n", szValue, i);
		}
		else
		{
			//printf("Shape i = %d\n continue \n", i);
			//continue;
		}

		//pTD->m_lstParentId.AddTail("xxx");
		
		cTDL.AddTail(pTD);

		SAFERELEASE(pShapeNode);
	}

CleanUp:
	SAFERELEASE(pShapeNode);				
	SAFERELEASE(pShapeList);
	
}

//�����û���shap�趨�����ӷ�������ȡ������ݲ����´����˵������������
void GetMonitorsByMatchStrucFromFile2(CTransferDataList& pCTransferDataList , int nVersion02)
{
	try
	{
		int nTransferDataCount = 0;
		nTransferDataCount = pCTransferDataList.GetCount();
		
		int nDisable =0;
		
		for(int j = 0; j < nTransferDataCount; j++)	
		{
			POSITION pos = NULL;
			pos = pCTransferDataList.FindIndex(j);
			
			CTransferData *pCTransferData = NULL;
			
			pCTransferData =pCTransferDataList.GetNext(pos);
			
			CString strIP = pCTransferData->m_strIP;
			CString strApp = pCTransferData->m_strApp;
			CString strGroup = pCTransferData->m_strGroup;
			CString strEntity = pCTransferData->m_strEntity;
			CString strMonitor = pCTransferData->m_strMonitor;
			CString strLinkPage = pCTransferData->m_strLinkPage;

			CString strEachMonitorInfo = _T("");
			CString strKey=_T("");
			char buffer[512]={0};
			
			//������
			if(!strLinkPage.IsEmpty())
			{
				CString strXmlFile;
				if(m_strXmlFile.Find(strLinkPage+".xml" ,0) != -1)
				{
					continue; 
				}
				
				//�жϳ�����ָ�������ͼҳ���Ƿ�ɷ��� �ҵݹ��жϳ�ָ�����Ӷ�Ӧ��ҳ������Ϊʲô״̬��
				if(nVersion02==0)
				{
					if(nIsMainTain == 1)
					{
						if(nIsMainTainLeader == 1)						
						{
							strXmlFile.Format("%s\\htdocs\\maintainleaderlist\\%s.files\\data.xml" , GetSiteViewRootPath().c_str() , 
								strLinkPage , strLinkPage);
						}
						else
						{						
							strXmlFile.Format("%s\\htdocs\\maintainlist\\%s.files\\data.xml" , GetSiteViewRootPath().c_str() , 
								strLinkPage , strLinkPage);
						}
					}
					else
					{
						strXmlFile.Format("%s\\htdocs\\tuoplist\\%s.files\\data.xml" , GetSiteViewRootPath().c_str() , 
							strLinkPage , strLinkPage);					
					}

					//strXmlFile.Format("%s\\htdocs\\tuopu\\%s.files\\data.xml" , "C:\\Program Files\\Apache Group\\apache2" , 
					//	strLinkPage , strLinkPage);					
				}
				else
				{
					if(nIsMainTain == 1)
					{
						if(nIsMainTainLeader == 1)						
						{
							strXmlFile.Format("%s\\htdocs\\maintainleaderlist\\%s.files\\data.xml" , GetSiteViewRootPath().c_str() , 
								strLinkPage , strLinkPage);
						}
						else
						{
							strXmlFile.Format("%s\\htdocs\\maintainlist\\%s.files\\data.xml" , GetSiteViewRootPath().c_str() , 
								strLinkPage , strLinkPage);						
						}
					}
					else
					{
						strXmlFile.Format("%s\\htdocs\\tuoplist\\%s.files\\data.xml" , GetSiteViewRootPath().c_str() , 
							strLinkPage , strLinkPage);					
					}
					
					//strXmlFile.Format("%s\\htdocs\\tuopu\\%s_files\\data.xml" , "C:\\Program Files\\Apache Group\\apache2" , 
					//	strLinkPage , strLinkPage);
				}
				
				//printf(strXmlFile);
				CXMLParse xml(strXmlFile, nVersion02);
				int nState=xml.GetState();
				CString strStatus;
				strStatus.Format("%d" , nState);

				pCTransferData->m_lstParentId.AddTail("3");
				pCTransferData->m_lstMonitorId.AddTail("1");
				pCTransferData->m_lstStatus.AddTail(strStatus);
	
				string strNormal,strWarning,strError;
				OBJECT objRes=LoadResource("default", "localhost");  
				if( objRes !=INVALID_VALUE )
				{	
					MAPNODE ResNode=GetResourceNode(objRes);
					if( ResNode != INVALID_VALUE )
					{
						FindNodeValue(ResNode,"IDS_Normal",strNormal);
						FindNodeValue(ResNode,"IDS_Warning",strWarning);
						FindNodeValue(ResNode,"IDS_Error",strError);
					}
					CloseResource(objRes);
				}

				if(nState == 1)
					pCTransferData->m_lstMenuItemDes.AddTail(strNormal.c_str());
				else if(nState == 2)
					pCTransferData->m_lstMenuItemDes.AddTail(strWarning.c_str());
				else if(nState == 3)
					pCTransferData->m_lstMenuItemDes.AddTail(strError.c_str());
				
				continue;
			}
			
			//����Ip�Ȳ�ѯ�����µ�״̬��Ϣ������˵���
			if(!strIP.IsEmpty())
			{
				GetHyperlinkNodesMenuData(1, strIP, pCTransferData);
			}
			//else if(!strApp.IsEmpty())
			//{
			//	//��ʱ����
			//	//MakeNodeMenu(5, strApp, pCTransferData);
			//}
			else if(!strGroup.IsEmpty())
			{
				GetHyperlinkNodesMenuData(2, strGroup, pCTransferData);
			}
			else if(!strEntity.IsEmpty())
			{
				GetHyperlinkNodesMenuData(3, strEntity, pCTransferData);
			}
			else if(!strMonitor.IsEmpty())
			{
				GetHyperlinkNodesMenuData(4, strMonitor, pCTransferData);
			}		
			else
			{
				continue;
			}
		}
	}
	catch(...)
	{
	
	}
}

//�����û���shap�趨�����ӷ�������ȡ������ݲ����´����˵������������
BOOL GetInformationFromDLL(GatherData * pGatherData, CTransferDataList& cTDL , int nVersion02)
{
#ifdef MYDEBUG
	DWORD dwStart = ::GetTickCount();
#endif
	
	GetMonitorsByMatchStrucFromFile2(cTDL , nVersion02);

#ifdef MYDEBUGDWORD dwEnd = GetTickCount();
	printf("%d\n", dwEnd - dwStart);
#endif 
	return TRUE;
}

//�����û��趨��SV_IP��ֵ ��ϴӷ�������ȡ�Ĳ���������ĵ��������data.xml�Թ���˵�������ڵ���ɫ������
void FormatXML(MSXML2::IXMLDOMDocument2 *pDoc, MSXML2::IXMLDOMNode *pPageNode, CTransferDataList& cTDL, CStringList& lstShape, CStringList& lstColor, CStringList& lstWeight)
{
	//Select collection of Shape
	long lLength = 0;
	int i = 0;

	HRESULT hr;
	MSXML2::IXMLDOMNodeList	* pShapeList	= NULL;
	MSXML2::IXMLDOMNode		* pShapeNode	= NULL;	
	MSXML2::IXMLDOMNode		* pHyperlinksNode	= NULL;
	CTransferData* pTD = NULL;

	//10/26 ��ʱע��
	POSITION pos = cTDL.GetHeadPosition();
	
	hr = pPageNode->selectNodes(::SysAllocString(L".//Shape"), &pShapeList);
	check_valid(hr, pShapeList);
	
	hr = pShapeList->get_length(&lLength);
	CHECKHR(hr);

	//printf("FormatXML Shape Count = %d\n", lLength);

	for (i=0; i<lLength; i++) 
	{
		CString strShapName = _T("");
		CString strItem = _T("");

		int nID = 1;

		hr = pShapeList->get_item(i, &pShapeNode);
		check_valid(hr, pShapeNode);

		//DeleteHyperlinkNodes(pShapeNode);

		if (!IsHyperlinkNodesExisted(pShapeNode))
		{
			//printf("FormatXML Shape i = %d\n", i);
			continue;
		}
		

		//10/26 ��ʱע��
		if (!pos)
			break;
		pTD = cTDL.GetNext(pos);
		
		//POSITION pos = NULL;
		//pos = cTDL.FindIndex(i);
		//pTD = cTDL.GetNext(pos);

		// Delete All Hyperlinks, if possible
		DeleteHyperlinkNodes(pShapeNode);
		
		hr = pShapeNode->selectSingleNode(::SysAllocString(L"Scratch/B/SolutionXML/HLURL:Hyperlinks"), &pHyperlinksNode);
		check_valid(hr, pHyperlinksNode);


		//��ʱ����  ��Խڵ����ת, ��ÿ���ڵ㶼����ɫ״̬
		
		//CString strUrl = GetUrlFromObject(pTD);
		
		// Modify All Hyperlinks
		if (!pTD->m_strIP.IsEmpty()) 
		{
			if (strShapName.IsEmpty())
				strShapName.Format("SV_IP:%s", pTD->m_strIP);			
			
			//�ڵ���ת������
			//CStringList lstHyperInfo;
			//
			//strItem.Format("ID=%d", nID);
			//lstHyperInfo.AddTail(strItem);					
			//
			//strItem.Format("DESC=GoTo %s Group", pTD->m_strIP);
			//lstHyperInfo.AddTail(strItem);
			//
			//strItem.Format("ADDR=/cgi-bin/monitorinfolist.exe?%s", strUrl);
			//lstHyperInfo.AddTail(strItem);
			//
			//InsertHyperlinkNode(pDoc, pHyperlinksNode, lstHyperInfo);
			//nID ++;
		}
		//else if (!pTD->m_strApp.IsEmpty()) 
		//{
		//	if (strShapName.IsEmpty())
		//		strShapName.Format("SV_App:%s", pTD->m_strApp);
		//}
		else if (!pTD->m_strGroup.IsEmpty()) 
		{
			if (strShapName.IsEmpty())
				strShapName.Format("SV_Group:%s", pTD->m_strGroup);
		}
		else if (!pTD->m_strEntity.IsEmpty()) 
		{
			if (strShapName.IsEmpty())
				strShapName.Format("SV_Entity:%s", pTD->m_strEntity);
		}
		else if (!pTD->m_strMonitor.IsEmpty()) 
		{
			if (strShapName.IsEmpty())
				strShapName.Format("SV_Monitor:%s", pTD->m_strMonitor);
		}
		else if (!pTD->m_strLinkPage.IsEmpty()) 
        {
			if (strShapName.IsEmpty())
				strShapName.Format("SV_Link:%s", pTD->m_strLinkPage);
		}
		else
		{
			continue;
		}

		//printf("Make Menu = %s i = %d \n", strShapName, i);

		//�����豸���� ���Ժ�������������һ����ʾ
		if (!pTD->m_strDes.IsEmpty()) 
		{
			//ͳһ�����û�����ı�ʶ
			CStringList lstSvDesHyperInfo;
			
			strItem.Format("ID=%d", 0);
			lstSvDesHyperInfo.AddTail(strItem);

			strItem.Format("DESC=%s", pTD->m_strDes);
			lstSvDesHyperInfo.AddTail(strItem);

			strItem = "ADDR=#";
			lstSvDesHyperInfo.AddTail(strItem);

			strItem.Format("STAT=%d", -100);
			lstSvDesHyperInfo.AddTail(strItem);

			InsertHyperlinkNode(pDoc, pHyperlinksNode, lstSvDesHyperInfo);
		}
		
		//ͳһ�����û�����ı�ʶ
		CStringList lstSvflagHyperInfo;
		
		strItem.Format("ID=%d", 0);
		lstSvflagHyperInfo.AddTail(strItem);

		strItem.Format("DESC=%s", strShapName.Mid(3));
		lstSvflagHyperInfo.AddTail(strItem);

		strItem = "ADDR=#";
		lstSvflagHyperInfo.AddTail(strItem);

		strItem.Format("STAT=%d", -100);
		lstSvflagHyperInfo.AddTail(strItem);

		InsertHyperlinkNode(pDoc, pHyperlinksNode, lstSvflagHyperInfo);

		string strGood,strMend,strRestore;
		OBJECT objRes=LoadResource("default", "localhost");  
		if( objRes !=INVALID_VALUE )
		{	
			MAPNODE ResNode=GetResourceNode(objRes);
			if( ResNode != INVALID_VALUE )
			{
				FindNodeValue(ResNode,"IDS_Normal",strGood);
				FindNodeValue(ResNode,"IDS_Remend",strMend);
				FindNodeValue(ResNode,"IDS_Restore",strRestore);
			}
			CloseResource(objRes);
		}
		
		//�Ƿ���ά��ģ��
		if(nIsMainTain == 1)
		{			
			if(nIsMainTainLeader == 1)
			{				
				//�쵼 
				//����ά�޼��ָ��˵�
				
			}
			else
			{
				//����Ա
				//��ά�޼��ָ��˵�

				//ά�޲˵���
				CStringList lstWeixiuHyperInfo;
				
				strItem.Format("ID=%d", 0);
				lstWeixiuHyperInfo.AddTail(strItem);

				strItem.Format("DESC=%s", strMend);
				lstWeixiuHyperInfo.AddTail(strItem);

				strItem.Format("ADDR=/fcgi-bin/showmaintain.exe?pageid=%s&version=0&svflag=%s&isweixiu=1&usrleader=0&maintain=1", strPageId, strShapName);
				lstWeixiuHyperInfo.AddTail(strItem);

				strItem.Format("STAT=%d", -100);
				lstWeixiuHyperInfo.AddTail(strItem);

				InsertHyperlinkNode(pDoc, pHyperlinksNode, lstWeixiuHyperInfo);

				//��Ϊ�����˵���
				CStringList lstNormalHyperInfo;
				
				strItem.Format("ID=%d", 0);
				lstWeixiuHyperInfo.AddTail(strItem);

				strItem.Format("DESC=%s", strGood);
				lstWeixiuHyperInfo.AddTail(strItem);

				strItem.Format("ADDR=/fcgi-bin/showmaintain.exe?pageid=%s&version=0&svflag=%s&isweixiu=2&usrleader=0&maintain=1", strPageId, strShapName);
				lstWeixiuHyperInfo.AddTail(strItem);

				strItem.Format("STAT=%d", -100);
				lstWeixiuHyperInfo.AddTail(strItem);

				InsertHyperlinkNode(pDoc, pHyperlinksNode, lstWeixiuHyperInfo);


				//�ָ��˵���
				CStringList lstHuifuHyperInfo;
				
				strItem.Format("ID=%d", 0);
				lstHuifuHyperInfo.AddTail(strItem);

				strItem.Format("DESC=%s", strRestore);
				lstHuifuHyperInfo.AddTail(strItem);

				strItem.Format("ADDR=/fcgi-bin/showmaintain.exe?pageid=%s&version=0&svflag=%s&isweixiu=0&usrleader=0&maintain=1", strPageId, strShapName);
				lstHuifuHyperInfo.AddTail(strItem);

				strItem.Format("STAT=%d", -100);
				lstHuifuHyperInfo.AddTail(strItem);

				InsertHyperlinkNode(pDoc, pHyperlinksNode, lstHuifuHyperInfo);
			}
		}
		else
		{
			
		}		

		POSITION posGroup = pTD->m_lstParentId.GetHeadPosition();
		POSITION posMonitor = pTD->m_lstMonitorId.GetHeadPosition();
		POSITION posStatus = pTD->m_lstStatus.GetHeadPosition();
		POSITION posInfor = pTD->m_lstMenuItemDes.GetHeadPosition();

		int nTotalCount = 0, nGoodCount = 0, nWarningCount = 0, nErrorCount = 0, nDisabledCount = 0;

		string strStdPageId = strPageId;
		string strStdShapName = strShapName;

		//�����˵�
		while (posGroup && posMonitor && posStatus && posInfor) 
		{
			CStringList lstHyperInfo;
			
			strItem.Format("ID=%d", nID);
			//printf("ID = %s \n", strItem);
			lstHyperInfo.AddTail(strItem);
			
			
			pTD->m_lstParentId.GetNext(posGroup);

			int nStatus = atoi(pTD->m_lstStatus.GetNext(posStatus));

			if(pTD->m_strLinkPage.IsEmpty())
			{
				strItem.Format("DESC=%s", pTD->m_lstMenuItemDes.GetNext(posInfor));
				lstHyperInfo.AddTail(strItem);

				//С����, ��monitorid�Ϳ����� 
				//strItem.Format("ADDR=/cgi-bin/RecentReport.exe?groupid=%s&monitorid=%s", pTD->m_lstParentId.GetNext(posGroup), pTD->m_lstMonitorId.GetNext(posMonitor));
				
				//�Ƿ���ά��ģ��
				if(nIsMainTain == 1)
				{
					//��ͨ�ڵ�
					//�쵼  ���Shape�ڵ���ά��״̬��ȫ���˵���Ϊ�̣������� ����ԭ��״̬��ʾ �Ҳ˵�������ӵ�С���桡����Ҳ������
					if(nIsMainTainLeader == 1)
					{
						
						strItem.Format("ADDR=#", pTD->m_lstMonitorId.GetNext(posMonitor));

						if(GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "1" || GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "2")
						{
							//��ά��״̬������Ϊ����״̬��ȫ���˵���Ϊ�̣�������
							nStatus = 1;
						}
					}
					else
					{
						strItem.Format("ADDR=/fcgi-bin/simplereport.exe?monitorid=%s", pTD->m_lstMonitorId.GetNext(posMonitor));
					}
				}
				else
				{
					strItem.Format("ADDR=/fcgi-bin/simplereport.exe?monitorid=%s", pTD->m_lstMonitorId.GetNext(posMonitor));
				}
					
				lstHyperInfo.AddTail(strItem);
			}
			else
			{				
				strItem.Format("DESC=GoTo %s Page", pTD->m_strLinkPage);
				lstHyperInfo.AddTail(strItem);
				
				if(nIsMainTain == 1)
				{			
					//���ӽڵ�
					
					//�쵼  ������ӽڵ���ά��״̬����ȫ���˵���Ϊ�̣������� �Ҳ�׼�������������� ����ԭ��״̬��ʾ �ҿ���������������
					//�쵼  ��������ӽڵ㡡 ��������ҳ��Ҫ���Ƿ����ˡ��Ƿ����쵼��Ϣ�ȡ�

					if(nIsMainTainLeader == 1)
					{	
						//strItem.Format("ADDR=#", pTD->m_lstMonitorId.GetNext(posMonitor));
						strItem.Format("ADDR=/fcgi-bin/showmaintain.exe?pageid=%s&version=0&usrleader=1&maintain=1", pTD->m_strLinkPage);

						if(GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "1"  || GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "2")
						{
							//���ӽڵ���ά��״̬��������Ϊ����״̬ ��ȫ���˵���Ϊ�̣������� �Ҳ�׼��������������
							strItem.Format("ADDR=#", pTD->m_strLinkPage);
							nStatus = 1;
						}						
					}
					else
					{
						//strItem.Format("ADDR=/fcgi-bin/simplereport.exe?monitorid=%s", pTD->m_lstMonitorId.GetNext(posMonitor));
						strItem.Format("ADDR=/fcgi-bin/showmaintain.exe?pageid=%s&version=0&usrleader=0&maintain=1", pTD->m_strLinkPage);
					}
				}
				else
				{
					//strItem.Format("ADDR=/fcgi-bin/simplereport.exe?monitorid=%s", pTD->m_lstMonitorId.GetNext(posMonitor));
					strItem.Format("ADDR=/fcgi-bin/showtuopu.exe?pageid=%s&version=0", pTD->m_strLinkPage);
				}			
				
				lstHyperInfo.AddTail(strItem);

				pTD->m_lstMonitorId.GetNext(posMonitor);
				pTD->m_lstMenuItemDes.GetNext(posInfor);
			}
			
			strItem.Format("STAT=%d", nStatus);
			lstHyperInfo.AddTail(strItem);
			
			nTotalCount++;

			switch(nStatus) 
			{
			case 1:
				nGoodCount++;
				break;
			case 2:
				nWarningCount++;
				break;
			case 3:
				nErrorCount++;
				break;
			case 4:
				nDisabledCount++;
				break;
			case 5:
				nErrorCount++;
				break;
			default:
				break;
			}

			InsertHyperlinkNode(pDoc, pHyperlinksNode, lstHyperInfo);
			nID ++;
		}
		
		//nErrorCount = 1;
		//����shap״̬���������ɫ����Ϣ����
		//���ܻ�Ҫ������״̬����ɫ�ȡ�����

		//�Ƿ���ά��ģ�飨Shape�ڵ㣩
		if(nIsMainTain == 1)
		{
			if(nIsMainTainLeader == 1)
			{
				//�쵼  ���Shape�ڵ���ά��״̬�� ��ʾΪΪ��ɫ 
				if(GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "1")
				{
					lstShape.AddTail(strShapName);
					lstColor.AddTail("blue");
					lstWeight.AddTail("3");
				}
				else
				{

					//�쵼  ���Shape�ڵ�����Ϊ����״̬״̬�� ��ʾΪ���� �������ȼ����
					if(GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "2")
					{
						//����Ա ���Shape�ڵ�����Ϊ����״̬�� ��ʾΪ��ɫ �������ȼ���
						nErrorCount = 0;
						nGoodCount = 0;
					}
					
					if(nErrorCount) 
					{
						lstShape.AddTail(strShapName);
						lstColor.AddTail("red");
						lstWeight.AddTail("3");
					}
					else if(nWarningCount) 
					{
						lstShape.AddTail(strShapName);
						lstColor.AddTail("yellow");
						lstWeight.AddTail("3");
					}
					else
					{
						
					}
				}
			}
			else
			{
				
				string strStdPageId = strPageId;
				string strStdShapName = strShapName;

				if(GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "1")
				{
					//����Ա ���Shape�ڵ���ά��״̬�� ��ʾΪ��ɫ �������ȼ����
					lstShape.AddTail(strShapName);
					lstColor.AddTail("blue");
					lstWeight.AddTail("3");
				}
				else if(GetIniFileString(strStdPageId, strStdShapName, "0", "maintain.ini") == "2")
				{
					//����Ա ���Shape�ڵ�����Ϊ����״̬�� ��ʾΪ��ɫ �������ȼ���
					lstShape.AddTail(strShapName);
					lstColor.AddTail("green");
					lstWeight.AddTail("3");
				}
				else if(nErrorCount) 
				{
					lstShape.AddTail(strShapName);
					lstColor.AddTail("red");
					lstWeight.AddTail("3");
				}
				else if(nWarningCount) 
				{
					lstShape.AddTail(strShapName);
					lstColor.AddTail("yellow");
					lstWeight.AddTail("3");
				}
				else
				{
					
				}
			}
		}
		else
		{
			if(nErrorCount) 
			{
				lstShape.AddTail(strShapName);
				lstColor.AddTail("red");
				lstWeight.AddTail("3");
			}
			else if(nWarningCount) 
			{ 
				lstShape.AddTail(strShapName);
				lstColor.AddTail("yellow");
				lstWeight.AddTail("3");
			}
			else
			{
				
			}
		}

		SAFERELEASE(pHyperlinksNode);
		SAFERELEASE(pShapeNode);
	}

CleanUp:
	SAFERELEASE(pShapeList);
}

//�����û��趨�����Լ���������ȡ״ֵ̬�ı�shape�ڵ����ɫ��
void OperaHtm(CString strFileName, CStringList& lstShape, CStringList& lstColor, CStringList& lstWeight)
{
    /*
	if (0 == lstShape.GetCount())
		if (0 == lstColor.GetCount())
			if (0 == lstWeight.GetCount()) {
				CString strHtmFile = _T("");
				strHtmFile = strFileName;
				strHtmFile.Replace(".tpl", ".htm");
				::CopyFile(strFileName, strHtmFile, FALSE);
				return;
			}
*/
	int nFileLength = 0;
	CFile* pFile = NULL;
	TRY	
	{
		pFile = new CFile(strFileName, CFile::modeRead | CFile::shareDenyNone);
		nFileLength = pFile->GetLength();
	}
	CATCH(CFileException, pEx)	
	{
		if (pFile != NULL) 
		{
			pFile->Close();
			delete pFile;
		}

		return;
	}
	END_CATCH

	if (pFile != NULL) 
	{
		pFile->Close();
		delete pFile;
	}

	if (0 == nFileLength)
		return;


	CString strSource = _T("");
	FILE * fp = fopen((LPCTSTR)strFileName, "r");
	if (fp)
	{		
		char * buffer = NULL;
		buffer = (char*)malloc(nFileLength+1);
		if (buffer) 
		{
			memset(buffer, 0, nFileLength+1);
			fread(buffer, sizeof(char), nFileLength+1, fp);
			std::string strOutSource = "";
			CChineseCodeLib::UTF_8ToGB2312(strOutSource, buffer,  nFileLength+1);
			//OutputDebugString(strOutSource.c_str());
			strSource = strOutSource.c_str();

			//strSource.Format("%s", buffer);	
			free(buffer);
		}
		fclose(fp);
	}
	
	//OutputDebugString(strSource);
	if (!strSource.IsEmpty()) {
		POSITION posIP = lstShape.GetHeadPosition();
		POSITION posColor = lstColor.GetHeadPosition();
		POSITION posWeight = lstWeight.GetHeadPosition();

		while (posIP && posColor && posWeight) {
			CString strIP = lstShape.GetNext(posIP);
			CString strColor = lstColor.GetNext(posColor);
			CString strWeight = lstWeight.GetNext(posWeight);

			CString strOld = _T("");
			CString strNew = _T("");
			//type="#VISSHAPE"  strokecolor="192.168.5.123+color" fillcolor="192.168.5.123+color" strokeweight="3pt"
			//strOld.Format("type=\"#VISSHAPE\"  strokecolor=\"%s+color\" fillcolor=\"%s+color\" strokeweight=\"3pt\"", strIP, strIP);
			//strNew.Format("strokecolor=\"%s\" fillcolor=\"%s\" strokeweight=\"%spt\"", strColor, strColor, strWeight);
					
			strOld.Format("fillcolor=\"%s+color\"", strIP);
			strNew.Format("filled=\"f\"  stroked=\"t\" strokecolor=\"%s\" fillcolor=\"%s\" strokeweight=\"%spt\"", strColor, strColor, strWeight);

			//std::string strOutSource = "";
			//LPTSTR p = strSource.GetBuffer(strSource.GetLength());
			//CChineseCodeLib::GB2312ToUTF_8(strOutSource, p, strSource.GetLength());
			//strSource.ReleaseBuffer( );
			//
			//OutputDebugString(strOutSource.c_str());
			//strSource = strOutSource.c_str();
			//OutputDebugString(strSource);
			int a=strSource.Replace(strOld, strNew);
			
			if(a==0)//2002 ����һ���ո�
			{
				//strOld.Format("type=\"#VISSHAPE\" strokecolor=\"%s+color\" fillcolor=\"%s+color\" strokeweight=\"3pt\"", strIP, strIP);
				strOld.Format("fillcolor=\"%s+color\"", strIP);
				strNew.Format("filled=\"f\"  stroked=\"t\" strokecolor=\"%s\" fillcolor=\"%s\" strokeweight=\"%spt\"", strColor, strColor, strWeight);
				strSource.Replace(strOld, strNew);
			}
		}
	}

	CString strHtmFile = _T("");
	strHtmFile = strFileName;
	strHtmFile.Replace(".tpl", ".htm");
	strSource.Replace("href=\"#\"", "href=\"javascript:void(null)\"");
	CString strCurUrl = "";
	
	if(nIsMainTain == 1)
	{
		//if(nIsMainTainLeader == 1)
			strCurUrl.Format("parent.location.replace(\"../../../fcgi-bin/showmaintain.exe?pageid=%s&version=0&usrleader=%d&maintain=%d\")", strPageId, nIsMainTainLeader, nIsMainTain);
	}
	else
		strCurUrl.Format("parent.location.replace(\"../../../fcgi-bin/showtuopu.exe?pageid=%s&version=0\")", strPageId);
	
	strSource.Replace("parent.location.reload()", strCurUrl);//mf:tuopo�Զ�ˢ��
	//OutputDebugString(strSource);
    
	//??
	HANDLE hEvent = ::CreateEvent(NULL, FALSE, TRUE, TEXT("{DragonFlow-AIM-4.0-TUOPU-HTM-Write}"));	
	if (hEvent) {
		::WaitForSingleObject(hEvent, INFINITE);

		fp = fopen(strHtmFile, "w");
		if (fp) {
			fwrite(strSource.GetBuffer(strSource.GetLength()), sizeof(char), strSource.GetLength(), fp);
			fclose(fp);
		}

		::SetEvent(hEvent);
		CloseHandle(hEvent);
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////��ʱ���õ��Ժ�����õĺ���//////////////////////////////////////////////

//��û��д���Ƶ�, �ò�����
MSXML2::IXMLDOMNode * CreateSolutionXML(MSXML2::IXMLDOMDocument2 *pDoc, MSXML2::IXMLDOMNode *pNode, const char* szNodeNamespaceURI = NULL)
{
	HRESULT hr;
	//CHECKHR(hr);
	//check_valid(hr, pNodeList);
	//hr = pNodeList->get_length(&length);

	MSXML2::IXMLDOMNode * solutionXML = NULL;
	pNode->selectSingleNode(::SysAllocString(L"Scratch/B/SolutionXML"), &solutionXML); 
	MSXML2::IXMLDOMNode * tmpNode = NULL;
	if(solutionXML == NULL)
	{
		hr = pNode->selectSingleNode(::SysAllocString(L"Scratch"), &solutionXML);
		if(solutionXML == NULL)
		{
			pDoc->createElement(::SysAllocString(L"Scratch"), (MSXML2::IXMLDOMElement **)&solutionXML);
			pNode->appendChild(solutionXML, NULL); 			
		}
			
		solutionXML->selectSingleNode(::SysAllocString(L"B"), &tmpNode);
		if(tmpNode == NULL)
		{
			pDoc->createElement(::SysAllocString(L"B"), (MSXML2::IXMLDOMElement **)&tmpNode);
			solutionXML->appendChild(tmpNode, NULL); 
			solutionXML = tmpNode;
		}
		else
		{
			solutionXML = tmpNode;
		}

		solutionXML->selectSingleNode(::SysAllocString(L"SolutionXML"), (MSXML2::IXMLDOMNode **)&tmpNode);
		if(tmpNode == NULL)
		{
			pDoc->createElement(::SysAllocString(L"SolutionXML"), (MSXML2::IXMLDOMElement **)&tmpNode);
			solutionXML->appendChild(tmpNode, NULL);
			solutionXML = tmpNode;
		}
		else
		{
			solutionXML = tmpNode;
		}

		//
		MSXML2::IXMLDOMNodeList * pNodeList = NULL;
		solutionXML->selectNodes(::SysAllocString(L"Scratch/B/SolutionXML/HLURL:Hyperlinks/HLURL:Hyperlink"), &pNodeList);
		if(pNodeList == NULL)
		{
			//tmpNode = pDoc->createElement("HLURL", "Hyperlinks", "urn:schemas-microsoft-com:office:visio:dghlinkext");
			VARIANT varType = {0};
			varType.vt = VT_I4;													
			varType.lVal = MSXML2::NODE_ELEMENT;

			// MUST specify a namespaceUI when a namespace node is created. namespaceUI is provided by parent node, Take care
			pDoc->createNode(varType, ::SysAllocString(L"HLURL:Hyperlink"), ::SysAllocString(L"urn:schemas-microsoft-com:office:visio:dghlinkext"), &tmpNode);
			
			solutionXML->appendChild(tmpNode, NULL); 
			solutionXML = tmpNode;
		}
		else
		{
			//solutionXML = tmpNode;
		}

/*		
		solutionXML->selectSingleNode("HLURL:Hyperlinks", nsmgr);
		if(tmpNode == NULL)
		{
			//tmpNode = pDoc->createElement("HLURL", "Hyperlinks", "urn:schemas-microsoft-com:office:visio:dghlinkext");
			solutionXML->appendChild(tmpNode, NULL); 
			solutionXML = tmpNode;
		}
		else
		{
			solutionXML = tmpNode;
		}

*/
	}

CleanUp:
	//SAFERELEASE(pHyperlinkNode);
	//SAFERELEASE(pNodeList);	

	return solutionXML;
}


//��ʱ������
CString GetUrlFromObject(CTransferData* pTD)
{	
	CString strSVIP, strSVHostName, strSVMachine, strSVAlias, strSVTemplate, strSVIndex;
	CString strUrl = _T("");

	strSVIP = pTD->m_strIP;
	
	CString strTemplate = _T("");

	if (!strSVTemplate.IsEmpty()) {
		char buffer[1024] = {0};
		char *s_original, *s_derive;
		CString strTemp = _T("");
		
		strcpy(buffer, strSVTemplate);
		s_original = buffer;

		while (s_derive = strstr(s_original,";")) {
			s_original[s_derive-s_original] = 0;
			
			// TODO:
			strTemp.Format("tplid=%s", s_original);
			
			strTemplate += "&";
			strTemplate += strTemp;
			
			s_derive += 1;
			s_original = s_derive;			
		}
	}

	strUrl.Format("ip=%s&hostname=%s&machine=%s&alias=%s%s&index=%s", strSVIP, strSVHostName, strSVMachine, strSVAlias, strTemplate, strSVIndex);

	return strUrl;
}
///////////////////////////////////////////////////////////////////////////////////////////


//////////////////����ں���///////////////////////////////////////////////////////////////

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
/*
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
*/
	{
		// TODO: code your application's behavior here.	

#ifdef MYDEBUG
		DWORD dwStart = ::GetTickCount();
#endif

		//argc = 3;
		//argv[1] = "C:\\siteview5\\htdocs\\tuopu\\horse_files\\horse.xml";//xml
		//argv[1] = "C:\\siteview5\\htdocs\\tuopu\\horse_files\\horse.xml";//xml
		//argv[1] = "C:\\Program Files\\Apache Group\\apache2\\htdocs\\tuoplist\\11.files\\data.xml";
		//argv[2] = "1";//�汾 0 Ϊ 2003

		//if (argc !=3)
		//	return -1;

		CString strXMLFile = _T("");
		CString strMyPagid = _T("");

		int m_iVersion02=0;


		strXMLFile = argv[1];
		m_strXmlFile = strXMLFile ;
		m_iVersion02=atoi(argv[2]);
		 strMyPagid = argv[3];
		strPageId = strMyPagid;

		//int m_bIsLeader = 0;
		//int m_bIsMaintain = 0;

		if(argc == 6)
		{
			 //m_bIsLeader = atoi(argv[4]);
			 //m_bIsMaintain = atoi(argv[5]);
			nIsMainTain = atoi(argv[4]);
			nIsMainTainLeader = atoi(argv[5]);

			//OutputDebugString("maketuopu");
			//OutputDebugString(argv[4]);
			//OutputDebugString(argv[5]);
			//printf("nIsMainTain = %d", argv[4]);
			//printf("nIsMainTainLeader = %d", argv[5]);
		}


		HRESULT hr;		
		MSXML2::IXMLDOMDocument2	* pDoc		= NULL;
		MSXML2::IXMLDOMNode		* pPagesNode	= NULL;
		MSXML2::IXMLDOMNodeList	* pPageList		= NULL;
		MSXML2::IXMLDOMNode		* pPageNode		= NULL;
		MSXML2::IXMLDOMNodeList	* pShapeList	= NULL;
		MSXML2::IXMLDOMNode		* pShapeNode	= NULL;		

		HINSTANCE hInstance = NULL;	
		GatherData* pGatherData = NULL;//û����
		POSITION pos = NULL;

		long lLength = 0;
		long lPageCount = 0;
		int i = 0, j = 0;
		char szValue [128] = {0};
		
		VARIANT vURL = {0};
		VARIANT vSave = {0};
		VARIANT varType = {0};

		VARIANT_BOOL vBool = VARIANT_FALSE;

//		vURL.vt = VT_BSTR;
//		vURL.bstrVal = strXMLFile.AllocSysString();

		//backup  xml wangpeng
		
		CString strXmlBak;
		strXmlBak=strXMLFile+".bak";
        /*
		DWORD dwAttr = GetFileAttributes(strXmlBak);
		if (dwAttr == 0xffffffff)
		{//������
			::CopyFile(strXMLFile,strXmlBak,FALSE);
		}*/
        ::CopyFile(strXMLFile,strXmlBak,FALSE);
		vURL.vt = VT_BSTR;
		vURL.bstrVal = strXmlBak.AllocSysString();	
	/*
		hInstance = ::LoadLibrary("GetMonitors.dll");
		if (!hInstance)
			goto CleanUp;

		pGatherData = (GatherData*)::GetProcAddress(hInstance, "GetMonitorsByMatchStrucFromFile");
		if (pGatherData==NULL)
			goto CleanUp;
	*/
		hr = CoInitialize(NULL);//Com��ʼ��
		CHECKHR(hr);
		
		hr = CoCreateInstance(MSXML2::CLSID_DOMDocument, NULL, 
							CLSCTX_INPROC_SERVER, 
							MSXML2::IID_IXMLDOMDocument2,
							(void**)&pDoc);
		check_valid(hr, pDoc);

		hr = pDoc->put_async(VARIANT_FALSE);
		CHECKHR(hr);
		
		hr = pDoc->load(vURL, &vBool);
		CHECKHR(hr)

		if (VARIANT_TRUE != vBool)
			goto CleanUp;
		
		//pDoc->selectNodes(::SysAllocString(L""),pPageList);

#ifdef MYDEBUG
		//pDoc->selectNodes(::SysAllocString(L""),&pPageList);
		pDoc->getElementsByTagName(::SysAllocString(L"Page"),&pPageList);
		check_valid(hr, pPageList);

		hr = pPageList->get_length(&lPageCount);
		for (j=0; j<lPageCount; j++) 
		{
			hr = pPageList->get_item(j, &pPageNode);

			check_valid(hr, pPageNode);

			BSTR bstrText = NULL;
			CString strValue = _T("");

			hr = pPageNode->get_nodeName(&bstrText);

			if (SUCCEEDED(hr)) 
			{
				if (bstrText)
					strValue = bstrText;

				printf(strValue+"\r\n");

			}
		}
#else
		hr = pDoc->selectSingleNode(::SysAllocString(L"VisioDocument"), &pPagesNode);
		check_valid(hr, pPagesNode);

		hr = pDoc->selectSingleNode(::SysAllocString(L"VisioDocument/Pages"), &pPagesNode);
		check_valid(hr, pPagesNode);
		
		hr = pPagesNode->selectNodes(::SysAllocString(L".//Page"), &pPageList);
		check_valid(hr, pPageList);
		
		// Select Page Node whith ID=0
		// hr = pPagesNode->selectSingleNode(::SysAllocString(L".//Page[@ID=\"0\"]"), &pPageNode);
		// check_valid(hr, pPageNode);

		hr = pPageList->get_length(&lPageCount);
		CHECKHR(hr);

		for (j=0; j<lPageCount; j++) 
		{
			hr = pPageList->get_item(j, &pPageNode);
			check_valid(hr, pPageNode);

			CTransferDataList cTDL;
			
			//ȡ������shape������
			GetAllRunningParas(pDoc, pPageNode, cTDL);
			
			//�ӷ�������������shape������ص�����
			GetInformationFromDLL(pGatherData, cTDL ,m_iVersion02);

			CStringList lstShape, lstColor, lstWeight;
			//printf("Read Ping Ini File\n");
			//GetStatusFromPingIni(cTDL,strXMLFile);
			
			//����shape��������ݹ���˵����������������ɫ��
			FormatXML(pDoc, pPageNode, cTDL, lstShape, lstColor, lstWeight);

			pos = cTDL.GetHeadPosition();
			while (pos != NULL)	
			{
				delete cTDL.GetNext(pos);
			}
			cTDL.RemoveAll();

			CString strNew = _T("");
			CString strHtmFile = strXMLFile;
			if(m_iVersion02==0)
			{
				//��visio 2003 ִ��
				strNew.Format("vml_%d.tpl", (j+1));
				strHtmFile.Replace("data.xml", strNew);
			}
			else
			{
				//��visio 2002 ִ��
				strNew.Format("_vml_%d.tpl", (j+1));
				strHtmFile.Replace(".xml", strNew);
			}
			
			//���Ľڵ���ɫ���Ե�
			OperaHtm(strHtmFile, lstShape, lstColor, lstWeight);

			SAFERELEASE(pPageNode);

		}

		vSave.vt = VT_BSTR;
		vSave.bstrVal = strXMLFile.AllocSysString(); 
		//::SysAllocString(L"c:\\out.xml");
		hr = pDoc->save(vSave);	
#endif		
		
CleanUp:

		SAFERELEASE(pPageList);
		SAFERELEASE(pPagesNode);
		SAFERELEASE(pDoc);

		if (hInstance) 
			::FreeLibrary(hInstance);

		CoUninitialize();

#ifdef MYDEBUG
		DWORD dwEnd = ::GetTickCount();
		printf("%d\n", dwEnd - dwStart);
#endif
	}

	return nRetCode;
}
