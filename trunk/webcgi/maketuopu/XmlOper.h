
#if !defined(AFX_XMLOPER_H__A5468932_BABC_46A5_A29C_B380F72ABAD5__INCLUDED_)
#define AFX_XMLOPER_H__A5468932_BABC_46A5_A29C_B380F72ABAD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
#include "resource.h"
#include "TransferData.h"
#import "C:\\WINDOWS\\system32\\msxml4.dll" named_guids, raw_interfaces_only

CString GetNodeAttribute(MSXML2::IXMLDOMNode * pNode, CString strAttr);
HRESULT SetNodeAttribute(MSXML2::IXMLDOMNode * pNode, CString strAttrName, CString strAttrValue);
HRESULT SetNodeText(MSXML2::IXMLDOMNode * pNode, CString strText);
CString GetNodeText(MSXML2::IXMLDOMNode * pNode);
HRESULT RemoveNode(MSXML2::IXMLDOMNode * pNode);
HRESULT InsertNode(MSXML2::IXMLDOMDocument2 * pDoc, MSXML2::IXMLDOMNode * pParentNode, CString strNodeName, CString strNodeText, const char* szNodeNamespaceURI = NULL, const char* szAttr1Name = NULL, const char* szAttr1Value = NULL);
void InsertHyperlinkNode(MSXML2::IXMLDOMDocument2 *pDoc, MSXML2::IXMLDOMNode *pHyperlinksNode, CStringList& lstStr);
BOOL RetrievePropertyValue(MSXML2::IXMLDOMNode *pShapeNode, const char* szProperty, char * szOut);
BOOL IsHyperlinkNodesExisted(MSXML2::IXMLDOMNode *pShapeNode);
void DeleteHyperlinkNodes(MSXML2::IXMLDOMNode *pShapeNode);
void GetAllRunningParas(MSXML2::IXMLDOMDocument2 *pDoc, MSXML2::IXMLDOMNode *pPageNode, CTransferDataList& cTDL);
string  GetMonitorPropValue(string strId, string strPropName);
bool isDisable(string &szMonitorID);
#endif // !defined(AFX_XMLOPER_H__A5468932_BABC_46A5_A29C_B380F72ABAD5__INCLUDED_)
