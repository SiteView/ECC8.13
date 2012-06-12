/////////////////////////////////////////////////////////////////////////////////////////////////
//
//1、判断指定Xm文件的状态
//2、递规获取连接数据的状态
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

//递归获取组树下的所有monitorid并附菜单项值
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
				
				//根据monitorid获取dyn信息中的状态信息
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

//递归获取组树下的所有monitorid并附菜单项值
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

//根据用户设定的参数获取创建NodeMenu的参数
bool OprGetHyperlinkNodesMenuData(int nNodeType, CString strNodeparam, CTransferData *pCTransferData)
{
	//获取Name Find strMonitor的所有监测器的基础信息
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
		//获取id及父id
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
				//sv_ip方式
				if(!OprEnumEntity(strStdId, pCTransferData))
					return false;
			}
		}
		else
		{
			if(strTemp.Find(strNodeparam) != -1)
			{
				//组、设备再递归取监测器信息
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
						//获取Id为strMonitorId的所有监测器的基础信息
						pCTransferData->m_lstParentId.AddTail(strParentId);
						pCTransferData->m_lstMonitorId.AddTail(strId);

						//						
						strStdInfo = "";
						strStdInfo += GetMonitorPropValue(strStdId, "sv_name");
						strStdInfo += "  ";

						
						//根据monitorid获取dyn信息中的状态信息						
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

//根据用户给shap设定参数从服务器获取监测数据并更新创建菜单等所需的链表
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
			
			//超连接
			if(!strLinkPage.IsEmpty())
			{
				CString strXmlFile;
				
				//if(m_strXmlFile.Find(strLinkPage+".xml" ,0) != -1)
				//{
				//	continue; 
				//}
				
				//判断超连接指向的拓扑图页面是否可访问。。。
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
			
			//根据Ip等查询出最新的状态信息并加入菜单项
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
	m_strXMLFileName = strXMLFile ;//XML文件名初始化
	m_nFileVersion = nVersion ; //文件版本
	m_nState = 1;
}

CXMLParse::~CXMLParse()
{
	SAFERELEASE(pPageList);//释放
	SAFERELEASE(pPagesNode);//释放
	SAFERELEASE(pDoc);//释放
	if (hInstance)
	{
		::FreeLibrary(hInstance);//释放
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

		HRESULT hr = CoInitialize(NULL);//Com初始化
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
			
			//取得所有shape的属性
			GetAllRunningParas(pDoc, pPageNode, cTDL);
			
			//从服务器得所有与shape属性相关的数据
			GetOprMonitorsByMatchStruct(cTDL , 1);

			pos = cTDL.GetHeadPosition();
			while (pos != NULL)	
			{
				delete cTDL.GetNext(pos);
			}
			cTDL.RemoveAll();


			SAFERELEASE(pPageNode);
		}

		//初始正常为1
		m_nState = 1;
		
		//告警为2
		if(bWarning)
		{
			m_nState = 2;
		}

		//错误为3
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
