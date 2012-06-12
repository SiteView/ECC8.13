// DogSlientInstall.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "dogdriver.h"

HINSTANCE						mlib = NULL;
INSTDRIVER						InstDriver = NULL;
UNINSTALLDRIVER					UninstallDriver= NULL;
int _tmain(int argc, _TCHAR* argv[])
{
	int bInstall;

	bInstall =1;
	if(argc>=2)
	{
		bInstall = atoi( argv[1]);
		
	}

	
	mlib = LoadLibrary(TEXT("RCMicroDogSetup.dll"));
	if(mlib != NULL)
	{
		if(bInstall==1)
		{
			//Get the interface function
			InstDriver = (INSTDRIVER)GetProcAddress(mlib, "InstDriver");
			if(InstDriver )
			{
				int RetCode = InstDriver(INSTALL_ONLY_USB_DOG_DRVIER);
			//	AfxMessageBox("asss");

			}
		}else{
			UninstallDriver = (UNINSTALLDRIVER)GetProcAddress(mlib, "UninstallDriver");
			if(UninstallDriver)
			{
				int RetCode = UninstallDriver(UNINSTALL_ALL_DOG_DRVIER);
			}
		}

		FreeLibrary(mlib);
	}

	return 0;
}

