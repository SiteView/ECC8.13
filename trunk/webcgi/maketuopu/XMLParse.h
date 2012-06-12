// XMLParse.h: interface for the CXMLParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLPARSE_H__3D30BF56_D04F_4D56_AEAC_EFC53B7DF018__INCLUDED_)
#define AFX_XMLPARSE_H__3D30BF56_D04F_4D56_AEAC_EFC53B7DF018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TransferData.h"
//#include "../XMLFunction/XMLFunction.h"
//#include "../XMLFunction/alertFunc.h"
//
//#import "C:\\WINNT\\system32\\msxml4.dll" named_guids, raw_interfaces_only
#import "C:\\WINDOWS\\system32\\msxml4.dll" named_guids, raw_interfaces_only

class CXMLParse  
{
public:
	BOOL GetState();
	CXMLParse(const CString strXMLFile , const int nVersion);
	virtual ~CXMLParse();
protected:
	BOOL XmlInit();

private:
	CString m_strXMLFileName; // 文件名
	int m_nFileVersion;       //文件版本

	MSXML2::IXMLDOMDocument2	* pDoc;
	MSXML2::IXMLDOMNode		* pPagesNode;
	MSXML2::IXMLDOMNodeList	* pPageList;
	MSXML2::IXMLDOMNode		* pPageNode;
	MSXML2::IXMLDOMNodeList	* pShapeList;
	MSXML2::IXMLDOMNode		* pShapeNode;	
	HINSTANCE hInstance;	
	POSITION pos;
};

#endif // !defined(AFX_XMLPARSE_H__3D30BF56_D04F_4D56_AEAC_EFC53B7DF018__INCLUDED_)
