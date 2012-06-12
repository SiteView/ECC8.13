/////////////////////////////////////////////////////////////////////////////////////////////////
//
//1���ж�ָ��Xm�ļ���״̬
//2���ݹ��ȡ�������ݵ�״̬
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlOper.h"
#include "XMLParse.h"

#include "../../kennel/svdb/svapi/svapi.h"
#include "../../kennel/svdb/svapi/svdbapi.h"

int m_nState ;
bool bWarning ;
bool bError ;
extern int nIsMainTain;
extern int nIsMainTainLeader;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//�ݹ��ȡ�����µ�����monitorid�����˵���ֵ
bool OprEnumEntity(std::string szIndex, CTransferData *pCTransferData)
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

				//						
				strStdInfo = "";
				strStdInfo += GetMonitorPropValue(strStdId, "sv_name");
				strStdInfo += "  ";
				
				//����monitorid��ȡdyn��Ϣ�е�״̬��Ϣ
				SVDYN dyn;
				if(GetSVDYN(strStdId, dyn))
				{
					if(dyn.m_state == 3 || dyn.m_state == 5)
					{
						bError = true;
						return false;
					}
					
					if(dyn.m_state == 2)
					{
						bWarning = true;
					}
				}
			}
        }
        CloseEntity(objDevice);			
    }     

	return true;
}

//�ݹ��ȡ�����µ�����monitorid�����˵���ֵ
bool OprEnumGroup(std::string szIndex, CTransferData *pCTransferData)
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
					if(!OprEnumEntity((*lstItem), pCTransferData))
						return false;
                }            
            }
            
			if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    if(!OprEnumGroup(szSubGroupID, pCTransferData))
						return false;
                }
            }

            CloseGroup(group);
        }        
    }

	return true;
}

//�����û��趨�Ĳ�����ȡ����NodeMenu�Ĳ���
bool OprGetHyperlinkNodesMenuData(int nNodeType, CString strNodeparam, CTransferData *pCTransferData)
{
	//��ȡName Find strMonitor�����м�����Ļ�����Ϣ
	PAIRLIST retlist;
	std::list<struct sv_pair>::iterator svitem;

	switch(nNodeType)
	{
		case 1:
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

	for(svitem = retlist.begin(); svitem != retlist.end(); svitem++)
	{
		//��ȡid����id
		strId = CString((*svitem).name.c_str());
		strStdId = (*svitem).name;
		
		strParentId = CString(FindParentID((*svitem).name).c_str());
		
		//
		strTemp = CString((*svitem).value.c_str());
		SVDYN dyn;

		if(nNodeType == 1)
		{
			if(!strTemp.IsEmpty() && strTemp == strNodeparam)
			{
				//sv_ip��ʽ
				if(!OprEnumEntity(strStdId, pCTransferData))
					return false;
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
						if(!OprEnumGroup(strStdId, pCTransferData))
							return false;
						break;
					case 3:
						if(!OprEnumEntity(strStdId, pCTransferData))
							return false;
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
							if(dyn.m_state == 3 || dyn.m_state == 5)
							{
								bError = true;
								return false;
							}
							
							if(dyn.m_state == 2)
							{
								bWarning = true;
							}
						}
						break;
					default:
						break;
				}
			}
		}

		strTemp = "";
	}

	return true;
}

//�����û���shap�趨�����ӷ�������ȡ������ݲ����´����˵������������
void GetOprMonitorsByMatchStruct(CTransferDataList& pCTransferDataList , int nVersion02)
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
				
				//if(m_strXmlFile.Find(strLinkPage+".xml" ,0) != -1)
				//{
				//	continue; 
				//}
				
				//�жϳ�����ָ�������ͼҳ���Ƿ�ɷ��ʡ�����
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
				
				//...
				if(nState == 3)
				{
					bError = true;
					return;
				}

				if(nState == 2)
				{
					bWarning = true;
				}

				continue;
			}
			
			//����Ip�Ȳ�ѯ�����µ�״̬��Ϣ������˵���
			if(!strIP.IsEmpty())
			{
				if(!OprGetHyperlinkNodesMenuData(1, strIP, pCTransferData))
					return;
			}
			else if(!strGroup.IsEmpty())
			{
				if(!OprGetHyperlinkNodesMenuData(2, strGroup, pCTransferData))
					return;
			}
			else if(!strEntity.IsEmpty())
			{
				if(!OprGetHyperlinkNodesMenuData(3, strEntity, pCTransferData))
					return;
			}
			else if(!strMonitor.IsEmpty())
			{
				if(!OprGetHyperlinkNodesMenuData(4, strMonitor, pCTransferData))
					return;
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

CXMLParse::CXMLParse(const CString strXMLFile , const int nVersion)
{
	m_strXMLFileName = strXMLFile ;//XML�ļ�����ʼ��
	m_nFileVersion = nVersion ; //�ļ��汾
	m_nState = 1;
}

CXMLParse::~CXMLParse()
{
	SAFERELEASE(pPageList);//�ͷ�
	SAFERELEASE(pPagesNode);//�ͷ�
	SAFERELEASE(pDoc);//�ͷ�
	if (hInstance)
	{
		::FreeLibrary(hInstance);//�ͷ�
	}
	CoUninitialize();//COM
}

BOOL CXMLParse::XmlInit()
{
	try
	{
		m_nState = 1;
		bWarning = false;
		bError = false;

		pDoc = NULL;
		pPagesNode = NULL;
		pPageList = NULL;
		pPageNode = NULL;
		pShapeList = NULL;
		pShapeNode = NULL;	
		hInstance = NULL;	
		pos = NULL;

		VARIANT vURL = {0};
		VARIANT vSave = {0};
		VARIANT varType = {0};
		VARIANT_BOOL vBool = VARIANT_FALSE;
		vURL.vt = VT_BSTR;
		vURL.bstrVal = m_strXMLFileName.AllocSysString();

		POSITION pos = NULL;

		long lLength = 0;
		long lPageCount = 0;
		int i = 0, j = 0;

		HRESULT hr = CoInitialize(NULL);//Com��ʼ��
		CHECKHR(hr);
		
		hr = CoCreateInstance(MSXML2::CLSID_DOMDocument, NULL, 
							CLSCTX_INPROC_SERVER, 
							MSXML2::IID_IXMLDOMDocument2,
							(void**)&pDoc);
		check_valid(hr, pDoc);

		hr = pDoc->put_async(VARIANT_FALSE);
		CHECKHR(hr);
		
		hr = pDoc->load(vURL, &vBool);
		CHECKHR(hr);
	
		if(VARIANT_TRUE != vBool)
		{
			return FALSE;
		}

		//
		hr = pDoc->selectSingleNode(::SysAllocString(L"VisioDocument"), &pPagesNode);
		check_valid(hr, pPagesNode);

		hr = pDoc->selectSingleNode(::SysAllocString(L"VisioDocument/Pages"), &pPagesNode);
		check_valid(hr, pPagesNode);
		
		hr = pPagesNode->selectNodes(::SysAllocString(L".//Page"), &pPageList);
		check_valid(hr, pPageList);
		
		hr = pPageList->get_length(&lPageCount);
		CHECKHR(hr);

		for (int j=0; j<lPageCount; j++) 
		{
			hr = pPageList->get_item(j, &pPageNode);
			check_valid(hr, pPageNode);

			CTransferDataList cTDL;
			
			//ȡ������shape������
			GetAllRunningParas(pDoc, pPageNode, cTDL);
			
			//�ӷ�������������shape������ص�����
			GetOprMonitorsByMatchStruct(cTDL , 1);

			pos = cTDL.GetHeadPosition();
			while (pos != NULL)	
			{
				delete cTDL.GetNext(pos);
			}
			cTDL.RemoveAll();


			SAFERELEASE(pPageNode);
		}

		//��ʼ����Ϊ1
		m_nState = 1;
		
		//�澯Ϊ2
		if(bWarning)
		{
			m_nState = 2;
		}

		//����Ϊ3
		if(bError)
		{
			m_nState = 3;
		}

		return TRUE;
	}
	catch(_com_error &e)
	{
		return FALSE;
	}

CleanUp:
		SAFERELEASE(pPageList);
		SAFERELEASE(pPagesNode);
		SAFERELEASE(pDoc);

		if (hInstance) 
			::FreeLibrary(hInstance);

		CoUninitialize();

	return FALSE;
}

int CXMLParse::GetState()
{
	if(XmlInit())
		return m_nState;
	else
		return 3;
}
