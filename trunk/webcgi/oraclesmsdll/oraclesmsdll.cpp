// oraclesmsdll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "oraclesmsdll.h"
#include "Ado.h"
#include "AdoRecordSet.h"
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

// CoraclesmsdllApp

BEGIN_MESSAGE_MAP(CoraclesmsdllApp, CWinApp)
END_MESSAGE_MAP()


// CoraclesmsdllApp ����

CoraclesmsdllApp::CoraclesmsdllApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CoraclesmsdllApp ����

CoraclesmsdllApp theApp;


// CoraclesmsdllApp ��ʼ��

BOOL CoraclesmsdllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
