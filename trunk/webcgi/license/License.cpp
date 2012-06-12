#include ".\license.h"
#include "../../kennel/svdb/svapi/svapi.h"
#include "..\svtable\MainTable.h"
#include "../../base/des.h"
#include "../../tools/usbdog/doglib/safedog.h"
#include "websession.h"
#include "WApplication"
#include "WSVMainTable.h"
#include "WSVFlexTable.h"
#include "WCheckBox"
#include "WLineEdit"
#include "WText"
#include "WTable"
#include "WImage"
/////////////////////////////////
#include <atlstr.h>
////////////////////
#include "../../kennel/svdb/libutil/Time.h"
using namespace svutil;

#define OneNetEntitysCount  30

CLicense::CLicense(WContainerWidget *parent ):
WContainerWidget(parent)
{
	refreshCount = 0;

	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_License_MainTitle",strMainTitle);
			FindNodeValue(ResNode,"IDS_License_Title",strTitle);
			FindNodeValue(ResNode,"IDS_Buy_Point_Count",strPointText);
			FindNodeValue(ResNode,"IDS_Enable_Point_Count",strPText);
			FindNodeValue(ResNode,"IDS_Buy_Entity_Count",strEquipText);
			FindNodeValue(ResNode,"IDS_Enable_Entity_Count",strEText);
			FindNodeValue(ResNode,"IDS_Disable_Date",strDataText);
			FindNodeValue(ResNode,"IDS_NO_Limit",strGeneral);
			FindNodeValue(ResNode,"IDS_Year",strYear);
			FindNodeValue(ResNode,"IDS_Month",strMonth);
			FindNodeValue(ResNode,"IDS_Day",strDay);
		}
		CloseResource(objRes);
	}

	ShowMainTable();
}

void CLicense::ShowMainTable()
{
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	

	pMainTable = new WSVMainTable(this, strMainTitle, false);
	
	pUserTable = new WSVFlexTable((WContainerWidget *)pMainTable->GetContentTable()->elementAt(1,0), Blank, strTitle);

	if(pUserTable->GetContentTable()!=NULL)
	{
		pSubTable = new WTable((WContainerWidget *)pUserTable->GetContentTable()->elementAt(1,0));
		if(pSubTable)
		{
			InitTable(pSubTable);
		}
	}

	//翻译
/*	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pMainTable->pTranslateBtn->show();
		connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

		pMainTable->pExChangeBtn->show();
		connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
	}
	else
	{
		pMainTable->pTranslateBtn->hide();
		pMainTable->pExChangeBtn->hide();
	}*/
}
void CLicense::ExChange()
{
	WebSession::js_af_up="setTimeout(\"location.href ='/fcgi-bin/license.exe?'\",1250);  ";
	appSelf->quit();
}
void CLicense::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "licenseRes";
	WebSession::js_af_up += "')";
}



void CLicense::InitTable(WTable * pContain)
{
	OutputDebugString("\n--------InitTable---------\n");
	SafeDog pSafeDog;
	bool IsDogExit=false;
	std::string strCount = "";
	
	if( !pSafeDog.DogOnUsb(IsDogExit) )
	{
		OutputDebugString("\n--------DogOnUsb---------\n");
		if(IsDogExit == true)
		{
			IsDogExit = false;
			if(!pSafeDog.IsShowNodeNum(IsDogExit))
			{
				if(IsDogExit == true)
				{				
					OutputDebugString("\n--------t1---------\n");
					WTable * t1 = new WTable((WContainerWidget*)pContain->elementAt(1 , 0));
					if(t1)
					{
						t1->setStyleClass("table_data_input_rows");
						t1->setCellPadding(0);
						t1->setCellSpaceing(0);

						WImage * pImage1 = new WImage("/Images/license1.gif", (WContainerWidget*)t1->elementAt(1 , 0));
						t1->elementAt(1 , 0)->setStyleClass("width50");

						WText * pT1 = new WText(strPointText,(WContainerWidget*)t1->elementAt(1 , 1));
						strcpy(t1->elementAt(1 , 1)->contextmenu_,"nowrap");		
						t1->elementAt(1 , 1)->setStyleClass("widthbold150");

						strcpy(t1->elementAt(1 , 2)->contextmenu_,"nowrap");		
						pBuyPText = new WText("hgghfgh",(WContainerWidget*)t1->elementAt(1 , 2));
					}
					WTable * t2 = new WTable((WContainerWidget*)pContain->elementAt(2 , 0));
					if(t2)
					{
						t2->setStyleClass("table_data_input_rows");
						t2->setCellPadding(0);
						t2->setCellSpaceing(0);

						WImage * pImage2 = new WImage("/Images/license2.gif", (WContainerWidget*)t2->elementAt(1 , 0));
						t2->elementAt(1 , 0)->setStyleClass("width50");

						WText * pT2 = new WText(strPText,(WContainerWidget*)t2->elementAt(1 , 1));
						strcpy(t2->elementAt(1 , 1)->contextmenu_,"nowrap");		
						t2->elementAt(1 , 1)->setStyleClass("widthbold150");

						pEnablePText = new WText("",(WContainerWidget*)t2->elementAt(1 , 2));
						strcpy(t2->elementAt(1 , 2)->contextmenu_,"nowrap");		
					}
				}
				IsDogExit = false;
			}
			if(!pSafeDog.IsShowDeviceNum(IsDogExit))
			{
				if(IsDogExit == true)
				{				
					OutputDebugString("\n--------t3---------\n");
					WTable * t3 = new WTable((WContainerWidget*)pContain->elementAt(3 , 0));
					if(t3)
					{
						t3->setStyleClass("table_data_input_rows");
						t3->setCellPadding(0);
						t3->setCellSpaceing(0);

						WImage * pImage3 = new WImage("/Images/license3.gif", (WContainerWidget*)t3->elementAt(1, 0));
						t3->elementAt(1 , 0)->setStyleClass("width50");

						WText * pT3 = new WText(strEquipText,(WContainerWidget*)t3->elementAt(1 , 1));
						strcpy(t3->elementAt(1 , 1)->contextmenu_,"nowrap");		
						t3->elementAt(1 , 1)->setStyleClass("widthbold150");

						pBuyEText = new WText("",(WContainerWidget*)t3->elementAt(1 , 2));
						strcpy(t3->elementAt(1 , 2)->contextmenu_,"nowrap");		
					}

					WTable * t4 = new WTable((WContainerWidget*)pContain->elementAt(4 , 0));
					if(t4)
					{
						t4->setStyleClass("table_data_input_rows");
						t4->setCellPadding(0);
						t4->setCellSpaceing(0);

						WImage * pImage4 = new WImage("/Images/license4.gif", (WContainerWidget*)t4->elementAt(1, 0));
						t4->elementAt(1 , 0)->setStyleClass("width50");

						WText * pT4 = new WText(strEText,(WContainerWidget*)t4->elementAt(1 , 1));
						strcpy(t4->elementAt(1 , 1)->contextmenu_,"nowrap");		
						t4->elementAt(1 , 1)->setStyleClass("widthbold150");

						pEnableEText = new WText("",(WContainerWidget*)t4->elementAt(1 , 2));
						strcpy(t4->elementAt(1 , 2)->contextmenu_,"nowrap");		
					}

				}
				IsDogExit = false;
			}
		}	
	}
	else
	{
		OutputDebugString("\n--------GetIniFileInt---------\n");
		int bShow=0;
		bShow =	GetIniFileInt("license", "showpoint", 0,  "general.ini");
		if(bShow==1)
		{
			OutputDebugString("\n--------t1---------\n");
			WTable * t1 = new WTable((WContainerWidget*)pContain->elementAt(1 , 0));
			if(t1)
			{
				t1->setStyleClass("table_data_input_rows");
				t1->setCellPadding(0);
				t1->setCellSpaceing(0);

				WImage * pImage1 = new WImage("/Images/license1.gif", (WContainerWidget*)t1->elementAt(1 , 0));
				t1->elementAt(1 , 0)->setStyleClass("width50");

				WText * pT1 = new WText(strPointText,(WContainerWidget*)t1->elementAt(1 , 1));
				strcpy(t1->elementAt(1 , 1)->contextmenu_,"nowrap");		
				t1->elementAt(1 , 1)->setStyleClass("widthbold150");

				strcpy(t1->elementAt(1 , 2)->contextmenu_,"nowrap");		
				pBuyPText = new WText("hgghfgh",(WContainerWidget*)t1->elementAt(1 , 2));
			}
			WTable * t2 = new WTable((WContainerWidget*)pContain->elementAt(2 , 0));
			if(t2)
			{
				t2->setStyleClass("table_data_input_rows");
				t2->setCellPadding(0);
				t2->setCellSpaceing(0);

				WImage * pImage2 = new WImage("/Images/license2.gif", (WContainerWidget*)t2->elementAt(1 , 0));
				t2->elementAt(1 , 0)->setStyleClass("width50");

				WText * pT2 = new WText(strPText,(WContainerWidget*)t2->elementAt(1 , 1));
				strcpy(t2->elementAt(1 , 1)->contextmenu_,"nowrap");		
				t2->elementAt(1 , 1)->setStyleClass("widthbold150");

				pEnablePText = new WText("",(WContainerWidget*)t2->elementAt(1 , 2));
				strcpy(t2->elementAt(1 , 2)->contextmenu_,"nowrap");		
			}
		}	
		bShow=0;	
		bShow=GetIniFileInt("license", "shownw", 0,  "general.ini");
		if(bShow==1)
		{
			OutputDebugString("\n--------t3---------\n");
			WTable * t3 = new WTable((WContainerWidget*)pContain->elementAt(3 , 0));
			if(t3)
			{
				t3->setStyleClass("table_data_input_rows");
				t3->setCellPadding(0);
				t3->setCellSpaceing(0);

				WImage * pImage3 = new WImage("/Images/license3.gif", (WContainerWidget*)t3->elementAt(1, 0));
				t3->elementAt(1 , 0)->setStyleClass("width50");

				WText * pT3 = new WText(strEquipText,(WContainerWidget*)t3->elementAt(1 , 1));
				strcpy(t3->elementAt(1 , 1)->contextmenu_,"nowrap");		
				t3->elementAt(1 , 1)->setStyleClass("widthbold150");

				pBuyEText = new WText("",(WContainerWidget*)t3->elementAt(1 , 2));
				strcpy(t3->elementAt(1 , 2)->contextmenu_,"nowrap");		
			}

			WTable * t4 = new WTable((WContainerWidget*)pContain->elementAt(4 , 0));
			if(t4)
			{
				t4->setStyleClass("table_data_input_rows");
				t4->setCellPadding(0);
				t4->setCellSpaceing(0);

				WImage * pImage4 = new WImage("/Images/license4.gif", (WContainerWidget*)t4->elementAt(1, 0));
				t4->elementAt(1 , 0)->setStyleClass("width50");

				WText * pT4 = new WText(strEText,(WContainerWidget*)t4->elementAt(1 , 1));
				strcpy(t4->elementAt(1 , 1)->contextmenu_,"nowrap");		
				t4->elementAt(1 , 1)->setStyleClass("widthbold150");

				pEnableEText = new WText("",(WContainerWidget*)t4->elementAt(1 , 2));
				strcpy(t4->elementAt(1 , 2)->contextmenu_,"nowrap");		
			}

		}
		bShow=0;
		bShow=GetIniFileInt("license", "showtime", 0,  "general.ini");
		if(bShow==1)
		{
			OutputDebugString("\n--------t5---------\n");
			WTable * t5 = new WTable((WContainerWidget*)pContain->elementAt(5 , 0));
			if(t5)
			{
				t5->setStyleClass("table_data_input_rows");
				t5->setCellPadding(0);
				t5->setCellSpaceing(0);

				WImage * pImage5 = new WImage("/Images/license5.gif", (WContainerWidget*)t5->elementAt(1 , 0));
				t5->elementAt(1 , 0)->setStyleClass("width50");

				WText * pT5 = new WText(strDataText,(WContainerWidget*)t5->elementAt(1 , 1));
				strcpy(t5->elementAt(1 , 1)->contextmenu_,"nowrap");		
				t5->elementAt(1 , 1)->setStyleClass("widthbold150");

				pDataText = new WText("",(WContainerWidget*)t5->elementAt(1 , 2));
				strcpy(t5->elementAt(1 , 2)->contextmenu_,"nowrap");		
			}

		}
	}
	
	GetData();

	int rowCount = pContain->numRows();
	for(int i=1;i<rowCount;i++)
	{
		pContain->GetRow(i)->setStyleClass("padding_top");
	}

	pContain->setCellPadding(0);
	pContain->setCellSpaceing(0);
}

void CLicense::GetData()
{
	/****************************************
	 *
	 *  如果安装了软件狗,从软件狗里面读数据；
	 *  否则，从general.ini读取数据.
	 *
	 *****************************************/

	OutputDebugString("\n--------GetData---------\n");
	
	GetEnityMonitorsCount(&strENum,&strPNum);

	//软件狗
	SafeDog pSafeDog;
	bool IsDogExit=false;
	std::string strCount = "";
	
	if( !pSafeDog.DogOnUsb(IsDogExit) )
	{
		if(IsDogExit == true)
		{
			IsDogExit = false;
			if(!pSafeDog.IsShowNodeNum(IsDogExit))
			{
				if(IsDogExit == true)
				{				
					if(!pSafeDog.GetNodeNum(strCount))
					{
						if(strCount=="99999")
						{
							strCount=strGeneral;
						}
						if(pBuyPText)
							pBuyPText->setText(strCount);

						char strMonitorsCount[20];
						sprintf( strMonitorsCount,"%d", strPNum);
						if(pEnablePText)
							pEnablePText->setText(strMonitorsCount);
					}
					strCount = "";
				}
				IsDogExit = false;
			}
			if(!pSafeDog.IsShowDeviceNum(IsDogExit))
			{
				if(IsDogExit == true)
				{				
					if(!pSafeDog.GetDeviceNum(strCount))
					{
						if(strCount=="99999")
						{
							strCount=strGeneral;
						}
						if(pBuyEText)
 							pBuyEText->setText(strCount);

						char strCount[20];
						sprintf( strCount,"%d", strENum);
						if(pEnableEText)
							pEnableEText->setText(strCount);
					}
					strCount="";
				}
				IsDogExit = false;
			}
		}
	}
	else
	{
		Des OneDes;
		char strDes1[1024]={0},strDes2[1024]={0},strDes3[1024]={0},strDes4[1024]={0};

		int bShow=0;
		bShow =	GetIniFileInt("license", "showpoint", 0,  "general.ini");
		if(bShow==1)
		{
			strPointNum = GetIniFileString("license", "point", "",  "general.ini");
			if(strPointNum.size()>0)
			{
				if( OneDes.Decrypt(strPointNum.c_str(),strDes1) )
				{
					strPointNum = strDes1;
					if(strPointNum=="99999")
					{
						strPointNum=strGeneral;
					}
					if(pBuyPText)
						pBuyPText->setText(strPointNum);

					char strMonitorsCount[20];
					sprintf( strMonitorsCount,"%d", strPNum);
					if(pEnablePText)
						pEnablePText->setText(strMonitorsCount);
				}
			}
		}
		bShow=0;	
		bShow=GetIniFileInt("license", "shownw", 0,  "general.ini");
		if(bShow==1)
		{
			strEquipNum = GetIniFileString("license", "nw", "",  "general.ini");
			if(strEquipNum.size()>0)
			{
				if( OneDes.Decrypt(strEquipNum.c_str(),strDes2) )
				{
					strEquipNum=strDes2;
					if(strEquipNum=="99999")
					{
						strEquipNum=strGeneral;
					}
					if(pBuyEText)
						pBuyEText->setText(strEquipNum);

					char strCount[20];
					sprintf( strCount,"%d", strENum);
					if(pEnableEText)
						pEnableEText->setText(strCount);
				}
			}
		}
		bShow=0;
		bShow=GetIniFileInt("license", "showtime", 0,  "general.ini");
		if(bShow==1)
		{
			strDataNum = GetIniFileString("license", "starttime", "",  "general.ini");
			if(strDataNum.size()>0)
			{
				if( OneDes.Decrypt(strDataNum.c_str(),strDes3) )
				{
					strDataNum=strDes3;
					if(!strDataNum.empty())
					{
						std::string LastData = GetIniFileString("license", "lasttime", "",  "general.ini");
						if(!LastData.empty())
						{
							if( OneDes.Decrypt(LastData.c_str(),strDes4) )
							{   
								LastData=strDes4;
								TTime timer(atoi(strDataNum.substr(0,4).c_str()),atoi(strDataNum.substr(5,2).c_str()),atoi(strDataNum.substr(8,2).c_str()),0,0,0);
								TTimeSpan AddData(atoi(LastData.c_str()),0,0,0);
								timer += AddData;
								char chStartDay[32] = {0};
								string strFormat = "%d-%d-%d";
								//获取默认语言
								string strOpenFilePath = GetSiteViewRootPath() + "\\data\\svdbconfig.ini";
								CString cPath = "";
								cPath = strOpenFilePath.c_str();
								CString cTemp = "";
								::GetPrivateProfileString("svdb","DefaultLanguage","",cTemp.GetBuffer(MAX_PATH),MAX_PATH,cPath);
								string DefaultLangu = (LPCTSTR)cTemp;
								if(DefaultLangu == "chinese")
								{
									strFormat = "%d";
									strFormat += strYear;
									strFormat += "%d";
									strFormat += strMonth;
									strFormat += "%d";
									strFormat += strDay;								
								}
								sprintf(chStartDay, strFormat.c_str(), timer.GetYear(), timer.GetMonth(), timer.GetDay());
								strDataNum=chStartDay;
								if(pDataText)
									pDataText->setText(strDataNum);
							}
						}
					}
				}
			}
		}
	}
	OutputDebugString("\n--------GetData End---------\n");
}
void CLicense::refresh()
{
	OutputDebugString("\n--------refresh---------\n");
	if( refreshCount != 0)
	{
		if(pSubTable)
		{
			pSubTable->clear();
			InitTable(pSubTable);
		}
		//翻译
/*		int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
		if(bTrans == 1)
		{
			pMainTable->pTranslateBtn->show();
			connect(pMainTable->pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	

			pMainTable->pExChangeBtn->show();
			connect(pMainTable->pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
		}
		else
		{
			pMainTable->pTranslateBtn->hide();
			pMainTable->pExChangeBtn->hide();
		}*/
	}
	refreshCount = 1;
}

void CLicense::GetEnityMonitorsCount(int *iEntityCount,int *iMonitorsCount)
{
	PAIRLIST prList;
	PAIRLIST::iterator OneList;
	std::list<string> prMonitorsList;
	OBJECT objEntityTemplet,objEntity;
	int NetEntitysCount=0, MonitorsCount=0,NetMonitorsCount=0,OneEntitysMonitorsCount=0;
	std::string EntityType;
	if(GetAllEntitysInfo(prList,"sv_devicetype"))
	{
		for(OneList=prList.begin();OneList!=prList.end();OneList++)
		{
			objEntityTemplet = GetEntityTemplet(OneList->value);
			if(objEntityTemplet != INVALID_VALUE)
			{
				if(FindNodeValue(GetEntityTempletMainAttribNode(objEntityTemplet),"sv_network",EntityType))
				{				
					if(EntityType == "true" )	
					{
						OutputDebugString("\n");
						OutputDebugString(OneList->name.c_str());
						objEntity = GetEntity(OneList->name);
						if(objEntity != INVALID_VALUE)
						{
							if( GetSubMonitorsIDByEntity(objEntity,prMonitorsList) )
							{	
								OneEntitysMonitorsCount=0;
								if(prMonitorsList.size() == 0 )
								{
									NetEntitysCount += 1;
								}
								else
								{
									OneEntitysMonitorsCount = (int)prMonitorsList.size();
									NetMonitorsCount += OneEntitysMonitorsCount;
									if(OneEntitysMonitorsCount % OneNetEntitysCount)
									{
										NetEntitysCount +=  OneEntitysMonitorsCount / OneNetEntitysCount + 1;
									}
									else
									{
										NetEntitysCount +=  OneEntitysMonitorsCount / OneNetEntitysCount;
									}
									prMonitorsList.clear();
								}
							}
							CloseEntity(objEntity);
						}
					}
				}
				CloseEntityTemplet(objEntityTemplet);
			}
		}
		prList.clear();
	}
	if(GetAllMonitorsInfo(prList))
	{
		MonitorsCount = (int)prList.size() - NetMonitorsCount;
		prList.clear();
	}
	*iEntityCount = NetEntitysCount;	
	*iMonitorsCount = MonitorsCount;
}

CLicense::~CLicense(void)
{

}

typedef void(*func)(int , char **);
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
	string title;
	OBJECT objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		MAPNODE ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,"IDS_License_MainTitle",title);
		CloseResource(objRes);
	}
    WApplication app(argc, argv);
    app.setTitle(title.c_str());
	app.setBodyAttribute("class ='workbody' ");
    CLicense setform(app.root());
	setform.appSelf = &app;
    app.exec();
}


int main(int argc, char *argv[])
{

    func p = usermain;
	if (argc == 1) 
    {
		WebSession s("25", false);
        s.start(p);
        return 1;
    }
    else
    {
        FCGI_Accept();
        WebSession s("DEBUG", true);
        s.start(p);
        return 1;
    }

    return 0;
}

