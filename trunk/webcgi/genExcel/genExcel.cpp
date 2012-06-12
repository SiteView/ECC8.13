/*
*  genExcel.cpp
*
*  Modified on 2007-10-10 By 苏合
*     1、在报表中加入阀值的数据
*
*/
// genExcel.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "genExcel.h"
#include <list>
#include "excelItem.h"
#include "CSpreadSheet.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CgenExcelApp

BEGIN_MESSAGE_MAP(CgenExcelApp, CWinApp)
END_MESSAGE_MAP()


// CgenExcelApp 构造

CgenExcelApp::CgenExcelApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CgenExcelApp 对象

CgenExcelApp theApp;


// CgenExcelApp 初始化

BOOL CgenExcelApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) void run(string name, list<forXLSItem>::iterator xlsListIterator1, list<forXLSItem>::iterator xlsListIterator2)
{
	CSpreadSheet SS(name.c_str(), "运行报告");
	CStringArray headerArray, contentArray;
	headerArray.RemoveAll();
	headerArray.Add("监视器名称");
	headerArray.Add("正常运行时间(%)");
	headerArray.Add("危险(%)");
	headerArray.Add("错误(%)");
	headerArray.Add("测量");
	headerArray.Add("峰值");
	headerArray.Add("平均值");
	headerArray.Add("阀值");
	SS.AddHeaders(headerArray);

	SS.BeginTransaction();
	char buf[30];
	memset(buf, 0, 30);
	for (; xlsListIterator1 != xlsListIterator2; xlsListIterator1++)
	{
		contentArray.RemoveAll();
		contentArray.Add(xlsListIterator1->name.c_str());
		sprintf(buf , "%d", xlsListIterator1->normalRunTime);
		contentArray.Add(buf);

		memset(buf, 0, 30);
		sprintf(buf , "%d", xlsListIterator1->dangerRunTime);
		contentArray.Add(buf);
		memset(buf, 0, 30);
		sprintf(buf , "%d", xlsListIterator1->errorRunTime);
		contentArray.Add(buf);
		memset(buf, 0, 30);
		contentArray.Add(xlsListIterator1->measureName.c_str());
		sprintf(buf, "%0.0f", xlsListIterator1->max);
		contentArray.Add(buf);
		memset(buf, 0, 30);
		sprintf(buf, "%0.0f", xlsListIterator1->avg);
		contentArray.Add(buf);
		contentArray.Add(xlsListIterator1->bound.c_str());

		SS.AddRow(contentArray);		
	}
	SS.Commit();
}
