// db2_7.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "db2_7.h"

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

// Cdb2_7App

BEGIN_MESSAGE_MAP(Cdb2_7App, CWinApp)
END_MESSAGE_MAP()


// Cdb2_7App ����

Cdb2_7App::Cdb2_7App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cdb2_7App ����

Cdb2_7App theApp;


// Cdb2_7App ��ʼ��

BOOL Cdb2_7App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
