/*
*  genExcel.cpp
*
*  Modified on 2007-10-10 By �պ�
*     1���ڱ����м��뷧ֵ������
*
*/
// genExcel.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CgenExcelApp

BEGIN_MESSAGE_MAP(CgenExcelApp, CWinApp)
END_MESSAGE_MAP()


// CgenExcelApp ����

CgenExcelApp::CgenExcelApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CgenExcelApp ����

CgenExcelApp theApp;


// CgenExcelApp ��ʼ��

BOOL CgenExcelApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) void run(string name, list<forXLSItem>::iterator xlsListIterator1, list<forXLSItem>::iterator xlsListIterator2)
{
	CSpreadSheet SS(name.c_str(), "���б���");
	CStringArray headerArray, contentArray;
	headerArray.RemoveAll();
	headerArray.Add("����������");
	headerArray.Add("��������ʱ��(%)");
	headerArray.Add("Σ��(%)");
	headerArray.Add("����(%)");
	headerArray.Add("����");
	headerArray.Add("��ֵ");
	headerArray.Add("ƽ��ֵ");
	headerArray.Add("��ֵ");
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
