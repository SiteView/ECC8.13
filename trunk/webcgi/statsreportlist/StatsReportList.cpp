/*************************************************
*  @file StatsReportList.cpp
*  author :		jiang xian
*  Copyright (C) 2005-2006 dragonflow corp.
*
*************************************************/
#include ".\statsreportlist.h"
#include "..\svtable\MainTable.h"
#include "..\svtable\FlexTable.h"
#include "..\svtable\WSVFlexTable.h"
#include "..\svtable\WSVMainTable.h"
#include "..\svtable\WSVButton.h"

#include "svdbapi.h"

#include "WText"
#include "WApplication"
#include "WebSession.h"
#include "WCheckBox"
#include "WSignalMapper"
#include "WLineEdit"
#include "WScrollArea"
#include "WFont"
#include "WPushButton"

#define WTGET

/***********************************************
参数：
	szRepStr：需替换的字符串

功能：
    替换字符串中的一些特殊字符， &-%26
	$-%24,#-%23,空-%20

返回值：
    替换后的字符串
***********************************************/
std::string RepHrefStr(std::string szRepStr)
{
	std::string szValue = szRepStr;

	int nPos = szValue.find("\\", 0);
    while (nPos > 0)
    {
        szValue = szValue.substr(0, nPos ) + "\\" + szValue.substr(nPos);
        nPos += 2;
        nPos = szValue.find("\\", nPos);
    }

    nPos = szValue.find("&", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%26" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find("&", nPos);
    }

    nPos = szValue.find("$", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%24" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find("$", nPos);
    }

    nPos = szValue.find("#", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%23" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find("#", nPos);
    }

    nPos = szValue.find(" ", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "%20" + szValue.substr(nPos + 1);
        nPos += 4;
        nPos = szValue.find(" ", nPos);
    }

	return szValue;
}

/***********************************************
参数：
	szRepStr：需替换的字符串

功能：
    替换字符串中的一些特殊字符， &-%26
	$-%24,#-%23,空-%20

返回值：
    替换后的字符串
***********************************************/
std::string RetRepHrefStr(std::string szRepStr)
{
	std::string szValue = szRepStr;

    int nPos = szValue.find("%26", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "&" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%26", nPos);
    }

    nPos = szValue.find("%24", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + "$" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%24", nPos);
    }

    nPos = szValue.find("%23", 0);
    while (nPos >= 0)
    {
		szValue = szValue.substr(0, nPos ) + "#" + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%23", nPos);
    }

    nPos = szValue.find("%20", 0);
    while (nPos >= 0)
    {
        szValue = szValue.substr(0, nPos ) + " " + szValue.substr(nPos + 3);
        nPos += 1;
        nPos = szValue.find("%20", nPos);
    }

	return szValue;
}

/***************************************************
参数：
	str:需替换的字符串
	old_value:被替换的字符串
	new_value:替换的字符串

功能：
    用new_value替换str中的所有old_value字符串

返回值：
    替换后的字符串
***************************************************/
string& replace_all_distinct(string& str,
							 const string& old_value,
							 const string& new_value)
{
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) {
		if( (pos=str.find(old_value,pos))!=string::npos )
			str.replace(pos,old_value.length(),new_value);
		else break;
	}
	return str;
}

/******************************************************************
参数：
	num：插入报告列表的行数
	pos：在Section中第一个$的位置
	section：报告名
	tempsection：reportgenerate.ini节名格式的指定报告字符串
	keylist：对应报告节下的所有KEY列表
	filename：reportgenerate.ini

功能：
	从reportgenerate.ini文件中取平均、最大、最小值插入列表

返回值：
    插入后下一行的行数
******************************************************************/
int CStatsReportList::InsertListRow(int num, 
									int pos,
									std::string section,
									std::string tempsection,
									std::list<string> keylist,
									std::string filename, bool bAddColumn)
{
	std::list<string>::iterator keyitem;
	std::string keystr;
	std::string keyval;
	int pos1 = 0;
	bool mAddTitle;

	//取对应报告节下的所有键值
	GetIniFileKeys(tempsection, keylist, filename);
			
	std::string starttime ;
	std::string endtime;

	//从组合字符串中分解报告名、开始时间、截止时间
	pos1 = tempsection.find("$", pos+1);
	starttime = tempsection.substr(pos + 1, pos1 - pos - 1);
	pos = tempsection.find("$", pos1 + 1);
	endtime = tempsection.substr(pos1 + 1, pos - pos1 - 1);

	//构造链接选项（开始时间截止时间报告名.html）
	std::string temptime = "<a href=../report/";
	std::string temphtmlname = starttime;
	temphtmlname += endtime;
	temphtmlname += section;
	temphtmlname += ".html";	

	std::string mapstr = section;
	mapstr += "$";
	mapstr += starttime;
	mapstr += "$";
	mapstr += endtime;
	mapstr += "$";

	//替换.html文件中的特殊字符
	replace_all_distinct(temphtmlname, " ", "_");
	replace_all_distinct(temphtmlname, ":", "_");
	replace_all_distinct(temphtmlname, "*", "_");		
	replace_all_distinct(temphtmlname, "/", "_");
	replace_all_distinct(temphtmlname, "\\", "_");
	replace_all_distinct(temphtmlname,"?", "_");
	replace_all_distinct(temphtmlname,  "|", "_");
	replace_all_distinct(temphtmlname,  "<", "_");
	replace_all_distinct(temphtmlname,  ">", "_");
	replace_all_distinct(temphtmlname,  "\"", "_");

	temptime += temphtmlname;
	temptime += ">";
	temptime += starttime;
	temptime += "~";
	temptime += endtime;
	//链接文件名
	temptime += "</a>";	

	OutputDebugString("*****************InsertListRow***********************\n");

	//列表第一列报告删除检查项
	pMonitorListTable->elementAt(num, 0) ->setContentAlignment(AlignTop | AlignCenter);
	WCheckBox * pCheck = new WCheckBox("", (WContainerWidget*)pMonitorListTable->elementAt(num, 0));

	new WImage("/Images/space.gif",pMonitorListTable->elementAt(num,1));

	//列表第二列格式：开始时间~截止时间
	WText *pSection = new WText(temptime, (WContainerWidget*)pMonitorListTable -> elementAt(num, 2));
	pMonitorListTable -> elementAt(num, 2) ->setContentAlignment(AlignTop | AlignCenter);


	_LIST list;
	list.pSelect = pCheck;
	list.pSection = pSection;
	list.szSection = mapstr;
	m_pList.push_back(list);

	std::string defaultret = "error";
	int knum = 3;
	
	//Jansion.zhou 2006-12-29
	//int tablenum = 3;
	//int tablenum1 = 3;

	//Jansion.zhou 2006-12-29
	if (bAddColumn)
	{
		Ttablenum = 3;
		Dtablenum = 3;
	}

	
	std::list<string>::iterator Titlekey;
	//从键值LIST
	for(keyitem = keylist.begin(); keyitem != keylist.end(); keyitem++)
	{
		std::string sval; std::string sval1; std::string sval2;
		keystr = *keyitem;




		std::list<string>::iterator colitem;
		
		//在列表头中查找KEY值
	//	for(colitem = colname1.begin(); colitem != colname1.end(); colitem++)
	//	{
	//		std::string tempstr = *colitem;
						
	//		if(strcmp(tempstr.c_str(),keystr.c_str()) == 0)
	//		{				
				
				//keyval 表头的具体数值
				keyval = GetIniFileString(tempsection, keystr, defaultret, filename);


				//具体数值
				//OutputDebugString("keyval = ");
				//OutputDebugString(keyval.c_str());
				//OutputDebugString("****************************************\n");

				if(strcmp(keyval.c_str(), "error") == 0)
				{
					continue;
				}

								
				char valbuf[256];
				memset(valbuf, 0, 256);
				pos = keyval.find("$", 0);
				sval = keyval.substr(0, pos);						

				pos1 = keyval.find("$", pos + 1);
				sval1 = keyval.substr(pos + 1, pos1 - pos - 1);

				pos = keyval.find("$", pos1 + 1);
				sval2 = keyval.substr(pos1 + 1, pos - pos1 - 1);



				//表头
				pos = keystr.find("$", 0);
				std::string s1 = keystr.substr(0, pos);
				
				//OutputDebugString("S1 = ");
				//OutputDebugString(s1.c_str());
				//OutputDebugString("\n");

				pos1 = keystr.find("$", pos + 1);
				std::string s2 = keystr.substr(pos + 1, pos1 - pos - 1);


				//OutputDebugString("S2 = ");
				//OutputDebugString(s2.c_str());
				//OutputDebugString("\n");

				//Jansion.zhou 2006-12-26
				//s2 = GetLabelResource(s2);
				std::string tstr = s1 + "(" + s2 + ")";

				//OutputDebugString("tstr after = ");
				//OutputDebugString(tstr.c_str());
				//OutputDebugString("\n");


				//Jansion.zhou 2006-12-29
				if (!strAllTitle.empty() && !bAddColumn)
				{
					//bool bSame, bdiffer;

					mAddTitle = true;
					
					//OutputDebugString("Jansion  -- begin --  ATitle = ");
					//OutputDebugString(tstr.c_str());
					//OutputDebugString("\n");

					//std::list<string>::iterator Titlekey;
					for(Titlekey = strAllTitle.begin(); Titlekey != strAllTitle.end(); Titlekey++)
					{

						if(strcmp(tstr.c_str(), Titlekey->c_str()) == 0)
						{
							//strAllTitle.push_back(tstr);
							mAddTitle = false;


							//OutputDebugString("Jansion  -- empty Yes --  AllTitle = ");
							//OutputDebugString(tstr.c_str());
							//OutputDebugString("\n");

							break;
						}
						//else
						//{

						//	//strAllTitle.push_back(tstr);
						//	//mAddTitle = true;

						//	OutputDebugString("Jansion  -- empty No --  AllTitle = ");
						//	OutputDebugString(tstr.c_str());
						//	OutputDebugString("\n");
						//}
					}

					if (mAddTitle)
					{
						strAllTitle.push_back(tstr);

						//OutputDebugString("Jansion  ---  AllTitle = ");
						//OutputDebugString(tstr.c_str());
						//OutputDebugString("\n");

						//mAddTitle = true;


						new WImage("/Images/space.gif",pMonitorListTable->elementAt(0, Ttablenum));
						Ttablenum++;
						
						new WText(tstr, pMonitorListTable->elementAt(0, Ttablenum));	
						pMonitorListTable->elementAt(0, Ttablenum)->tablecellprop_ = 3;
						pMonitorListTable->elementAt(0, Ttablenum)->tablecellprop = " colspan=3 width=300px nowrap";
						pMonitorListTable->elementAt(0, Ttablenum) ->setContentAlignment(AlignTop | AlignCenter);
						pMonitorListTable->elementAt(0, Ttablenum) ->setStyleClass("table_data_grid_header_text_rp");

						pMonitorListTable->elementAt(1, Ttablenum) ->setContentAlignment(AlignTop | AlignCenter);	
						pMonitorListTable->elementAt(1,Dtablenum)->setStyleClass("table_data_grid_space_rp");
						new WImage("/Images/space.gif",pMonitorListTable->elementAt(1,Dtablenum));
						Dtablenum++;

						pMonitorListTable->elementAt(1, Dtablenum)->setStyleClass("table_data_grid_rp_min");
						//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
						new WText(szMinValue, pMonitorListTable->elementAt(1, Dtablenum));
						pMonitorListTable->elementAt(1, Dtablenum)->setContentAlignment(AlignTop | AlignCenter);
						Dtablenum++;

						pMonitorListTable->elementAt(1, Dtablenum)->setStyleClass("table_data_grid_rp_ave");
						//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
						new WText(szAverageValue, pMonitorListTable->elementAt(1, Dtablenum));
						pMonitorListTable->elementAt(1, Dtablenum)->setContentAlignment(AlignTop | AlignCenter);
						Dtablenum++;

						pMonitorListTable->elementAt(1, Dtablenum)->setStyleClass("table_data_grid_rp_max");
						//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
						new WText(szMaxValue, pMonitorListTable->elementAt(1, Dtablenum));
						pMonitorListTable->elementAt(1, Dtablenum)->setContentAlignment(AlignTop | AlignCenter);
						Dtablenum++;

						Ttablenum++;	

					}

				}


				//Janion.zhou 2006-12-29
				if(bAddColumn)
				{
					strAllTitle.push_back(tstr);

					new WImage("/Images/space.gif",pMonitorListTable->elementAt(0, Ttablenum));
					Ttablenum++;
					
					new WText(tstr, pMonitorListTable->elementAt(0, Ttablenum));	
					pMonitorListTable->elementAt(0, Ttablenum)->tablecellprop_ = 3;
					pMonitorListTable->elementAt(0, Ttablenum)->tablecellprop = " colspan=3 width=300px nowrap";
					pMonitorListTable->elementAt(0, Ttablenum) ->setContentAlignment(AlignTop | AlignCenter);
					pMonitorListTable->elementAt(0, Ttablenum) ->setStyleClass("table_data_grid_header_text_rp");


					pMonitorListTable->elementAt(1, Ttablenum) ->setContentAlignment(AlignTop | AlignCenter);	
					pMonitorListTable->elementAt(1,Dtablenum)->setStyleClass("table_data_grid_space_rp");
					new WImage("/Images/space.gif",pMonitorListTable->elementAt(1,Dtablenum));
					Dtablenum++;

					pMonitorListTable->elementAt(1, Dtablenum)->setStyleClass("table_data_grid_rp_min");
					//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
					new WText(szMinValue, pMonitorListTable->elementAt(1, Dtablenum));
					pMonitorListTable->elementAt(1, Dtablenum)->setContentAlignment(AlignTop | AlignCenter);
					Dtablenum++;

					pMonitorListTable->elementAt(1, Dtablenum)->setStyleClass("table_data_grid_rp_ave");
					//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
					new WText(szAverageValue, pMonitorListTable->elementAt(1, Dtablenum));
					pMonitorListTable->elementAt(1, Dtablenum)->setContentAlignment(AlignTop | AlignCenter);
					Dtablenum++;

					pMonitorListTable->elementAt(1, Dtablenum)->setStyleClass("table_data_grid_rp_max");
					//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
					new WText(szMaxValue, pMonitorListTable->elementAt(1, Dtablenum));
					pMonitorListTable->elementAt(1, Dtablenum)->setContentAlignment(AlignTop | AlignCenter);
					Dtablenum++;

					Ttablenum++;	


				}
				



				//Janion.zhou 2006-12-29
				//if(bAddColumn)
				//{
				//	strAllTitle.push_back(tstr);

				//	new WImage("/Images/space.gif",pMonitorListTable->elementAt(0,tablenum));
				//	tablenum++;
				//	
				//	new WText(tstr, pMonitorListTable->elementAt(0,tablenum));	
				//	pMonitorListTable->elementAt(0,tablenum)->tablecellprop_ = 3;
				//	pMonitorListTable->elementAt(0,tablenum)->tablecellprop = " colspan=3 width=300px nowrap";
				//	pMonitorListTable->elementAt(0, tablenum) ->setContentAlignment(AlignTop | AlignCenter);
				//	pMonitorListTable->elementAt(0, tablenum) ->setStyleClass("table_data_grid_header_text_rp");


				//	pMonitorListTable->elementAt(1, tablenum) ->setContentAlignment(AlignTop | AlignCenter);	
				//	pMonitorListTable->elementAt(1,tablenum1)->setStyleClass("table_data_grid_space_rp");
				//	new WImage("/Images/space.gif",pMonitorListTable->elementAt(1,tablenum1));
				//	tablenum1++;

				//	pMonitorListTable->elementAt(1, tablenum1)->setStyleClass("table_data_grid_rp_min");
				//	//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
				//	new WText(szMinValue, pMonitorListTable->elementAt(1, tablenum1));
				//	pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
				//	tablenum1++;

				//	pMonitorListTable->elementAt(1, tablenum1)->setStyleClass("table_data_grid_rp_ave");
				//	//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
				//	new WText(szAverageValue, pMonitorListTable->elementAt(1, tablenum1));
				//	pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
				//	tablenum1++;

				//	pMonitorListTable->elementAt(1, tablenum1)->setStyleClass("table_data_grid_rp_max");
				//	//pMonitorListTable->elementAt(1, tablenum1)->resize(WLength(100,WLength::Pixel),0);
				//	new WText(szMaxValue, pMonitorListTable->elementAt(1, tablenum1));
				//	pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
				//	tablenum1++;

				//	tablenum++;				
				//}
				//

				

				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_space_rp");
				//new WImage("/Images/space.gif",pMonitorListTable->elementAt(num, knum));
				//knum++;

				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_item_text_rp");
				//new WText("&nbsp;", (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				//pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				//knum++;

				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_item_text_rp");
				//new WText("&nbsp;", (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				//pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				//knum++;
				//
				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_item_text_rp");
				//new WText("&nbsp", (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				//pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				//knum++;	




				//显示数据
				int pcolumn = 0;

				for(Titlekey = strAllTitle.begin(); Titlekey != strAllTitle.end(); Titlekey++)
				{
						//OutputDebugString("Jansion  -- begin -  AllTitle = ");
						//OutputDebugString(tstr.c_str());
						//OutputDebugString("\n");
					pcolumn ++;
					if(strcmp(tstr.c_str(), Titlekey->c_str()) == 0)
					{
						
						
						OutputDebugString("Jansion  ---  AllTitle = ");
						OutputDebugString(tstr.c_str());
						OutputDebugString("\n");


						int column = pcolumn * 4;
						//int column = (pcolumn * 4) - 1;
						//pMonitorListTable->elementAt(num, column)->setStyleClass("table_data_grid_space_rp");
						//new WImage("/Images/space.gif",pMonitorListTable->elementAt(num, column));
						//column++;

						pMonitorListTable->elementAt(num, column)->setStyleClass("table_data_grid_item_text_rp");
						new WText(sval, (WContainerWidget*)pMonitorListTable->elementAt(num, column));
						pMonitorListTable->elementAt(num, column)->setContentAlignment(AlignTop | AlignCenter);
						column++;

						pMonitorListTable->elementAt(num, column)->setStyleClass("table_data_grid_item_text_rp");
						new WText(sval1, (WContainerWidget*)pMonitorListTable->elementAt(num, column));
						pMonitorListTable->elementAt(num, column)->setContentAlignment(AlignTop | AlignCenter);
						column++;
						
						pMonitorListTable->elementAt(num, column)->setStyleClass("table_data_grid_item_text_rp");
						new WText(sval2, (WContainerWidget*)pMonitorListTable->elementAt(num, column));
						pMonitorListTable->elementAt(num, column)->setContentAlignment(AlignTop | AlignCenter);


						break;
					}




				}

				//pcolumn = (pcolumn * 4) - 1;
				//pMonitorListTable->elementAt(num, pcolumn)->setStyleClass("table_data_grid_space_rp");
				//new WImage("/Images/space.gif",pMonitorListTable->elementAt(num, pcolumn));
				//pcolumn++;

				//pMonitorListTable->elementAt(num, pcolumn)->setStyleClass("table_data_grid_item_text_rp");
				//new WText(sval, (WContainerWidget*)pMonitorListTable->elementAt(num, pcolumn));
				//pMonitorListTable->elementAt(num, pcolumn)->setContentAlignment(AlignTop | AlignCenter);
				//pcolumn++;

				//pMonitorListTable->elementAt(num, pcolumn)->setStyleClass("table_data_grid_item_text_rp");
				//new WText(sval1, (WContainerWidget*)pMonitorListTable->elementAt(num, pcolumn));
				//pMonitorListTable->elementAt(num, pcolumn)->setContentAlignment(AlignTop | AlignCenter);
				//pcolumn++;
				//
				//pMonitorListTable->elementAt(num, pcolumn)->setStyleClass("table_data_grid_item_text_rp");
				//new WText(sval2, (WContainerWidget*)pMonitorListTable->elementAt(num, pcolumn));
				//pMonitorListTable->elementAt(num, pcolumn)->setContentAlignment(AlignTop | AlignCenter);
				//pcolumn++;	



				//Jansion.zhou 2006-12-29
				////显示数值
				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_space_rp");
				//new WImage("/Images/space.gif",pMonitorListTable->elementAt(num, knum));
				//knum++;

				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_item_text_rp");
				//new WText(sval, (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				//pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				//knum++;

				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_item_text_rp");
				//new WText(sval1, (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				//pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				//knum++;
				//
				//pMonitorListTable->elementAt(num, knum)->setStyleClass("table_data_grid_item_text_rp");
				//new WText(sval2, (WContainerWidget*)pMonitorListTable->elementAt(num, knum));
				//pMonitorListTable->elementAt(num, knum)->setContentAlignment(AlignTop | AlignCenter);
				//knum++;	
				// 2006-12-29

			//}										
		//}
	}
	
	//Jansion.zhou 2006-12-29
	//if(bAddColumn)
	//{
	//	OutputDebugString("*******************0000000000*********************\n");
	//	std::list<string>::iterator Tkey;
	//	for(Tkey = strAllTitle.begin(); Tkey != strAllTitle.end(); Tkey++)
	//	{

	//		keystr = *Tkey;


	//			OutputDebugString("Jansion  ---  AllTitle = ");
	//			OutputDebugString(keystr.c_str());
	//			OutputDebugString("\n");
	//	}
	//}


				int pcolumn = 3;
				for(Titlekey = strAllTitle.begin(); Titlekey != strAllTitle.end(); Titlekey++)
				{

						pMonitorListTable->elementAt(num, pcolumn)->setStyleClass("table_data_grid_space_rp");
						new WImage("/Images/space.gif",pMonitorListTable->elementAt(num, pcolumn));

						pcolumn += 4;

				}




	if((num%2) != 0)
		pMonitorListTable->GetRow(num)->setStyleClass("table_data_grid_item_bg");

	num++;	
	return num;
}
/**************************************************
参数：
	strLabel:

功能：
	根据IDS取资源字符串

返回值：
	如果存在则返回资源字符串

**************************************************/
std::string CStatsReportList::GetLabelResource(
	std::string strLabel)
{
	string strfieldlabel ="";
	if( ResNode != INVALID_VALUE )
			FindNodeValue(ResNode,strLabel,strfieldlabel);
	if(strfieldlabel=="")
			strfieldlabel = strfieldlabel;
	return strfieldlabel;
}

/**************************************************************
参数：

功能：
	构造函数
**************************************************************/
CStatsReportList::CStatsReportList(WContainerWidget *parent ):
WContainerWidget(parent)
{
	//Resource
	objRes=LoadResource("default", "localhost");  
	if( objRes !=INVALID_VALUE )
	{	
		ResNode=GetResourceNode(objRes);
		if( ResNode != INVALID_VALUE )
		{
			FindNodeValue(ResNode,"IDS_Total_Report",strMainTitle);
			FindNodeValue(ResNode,"IDS_Total_Report_List",strTitle);
			FindNodeValue(ResNode,"IDS_Name",strLoginLabel);
			FindNodeValue(ResNode,"IDS_Total_Report_Map",strNameUse);
			FindNodeValue(ResNode,"IDS_Edit_Name",strNameEdit);
			FindNodeValue(ResNode,"IDS_Affirm_Delete_User",strDel);
			FindNodeValue(ResNode,"IDS_Simple_Report_Caption",m_formText.szCaption1);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szTitle);
			FindNodeValue(ResNode,"IDS_Total_Report",m_formText.szMonitorListName);
			FindNodeValue(ResNode,"IDS_State",m_formText.szMonitorListStatus);
			FindNodeValue(ResNode,"IDS_Description",m_formText.szMonitorListDescription);
			FindNodeValue(ResNode,"IDS_Monitor_Name",m_formText.szMonitorListName);
			FindNodeValue(ResNode,"IDS_Time",m_formText.szMonitorListTime);
			FindNodeValue(ResNode,"IDS_Report",szReport);
			FindNodeValue(ResNode,"IDS_Create_Immediately",szCreateImm);
			FindNodeValue(ResNode,"IDS_Max_Value",szMaxValue);
			FindNodeValue(ResNode,"IDS_Average_Value",szAverageValue);
			FindNodeValue(ResNode,"IDS_Min_Value",szMinValue);
			FindNodeValue(ResNode,"IDS_Report_Day",szReportDay);
			FindNodeValue(ResNode,"IDS_Report_Week",szReportWeek);
			FindNodeValue(ResNode,"IDS_Report_Month",szReportMonth);
			FindNodeValue(ResNode,"IDS_Translate",strTranslate);
			FindNodeValue(ResNode,"IDS_Translate_Tip",strTranslateTip);
			FindNodeValue(ResNode,"IDS_Refresh",strRefresh1);
			FindNodeValue(ResNode,"IDS_Refresh_Tip",strRefreshTip1);
			FindNodeValue(ResNode, "IDS_Return", m_formText.szReturn);
			FindNodeValue(ResNode,"IDS_ConfirmCancel",szButNum);
			FindNodeValue(ResNode,"IDS_Affirm",szButMatch);
			FindNodeValue(ResNode,"IDS_DeleteSMSAffirmInfo",szAffirmInfo);
			FindNodeValue(ResNode,"IDS_All_Select",m_formText.szTipSelAll1);
			FindNodeValue(ResNode,"IDS_None_Select",m_formText.szTipSelNone);
			FindNodeValue(ResNode,"IDS_Invert_Select",m_formText.szTipSelInv);
			FindNodeValue(ResNode,"IDS_Delete",m_formText.szTipDel);
			//解决英文版出现中文的问题 苏合 2007-07-17
			FindNodeValue(ResNode,"IDS_Time_Period",szTimePeriod);
			//解决英文版出现中文的问题 苏合 2007-07-17

		}
		
	}

	nListNum = 0;
	ShowMainTable();
}

//析构函数
CStatsReportList::~CStatsReportList(void)
{
	CloseResource(objRes);
}

/*********************************************
参数：

功能：
	初始显示主界面
*********************************************/
void CStatsReportList::ShowMainTable()
{	
	//包含basic.js文件
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);	
	
	char buf_tmp[4096]={0};
	int nSize =4095;
	std::string reportstr;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
 	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif

	//替换字符串中的特殊字符
	std::string repbuf = RetRepHrefStr(buf_tmp);
	memset(buf_tmp, 0, 4096);
	strcpy(buf_tmp, repbuf.c_str());

	//如果QUERY_STRING为空则返回
	if(strcmp(buf_tmp, "") == 0)
	{		
		return;
	}
	else
	{		
		//从QUERY_STRING字符串中取id=后的字符
		std::string fstr = buf_tmp;
		std::string s = fstr.substr(0, 3);
		if(strcmp(s.c_str(), "id=") == 0)
		{
			reportstr = fstr.substr(3, fstr.size() - 3);
		}
	}

	//报告标题栏
	szReport += reportstr;


	new WText("<div id='treeviewPanel' class='panel'>",this);

	m_pMainTable = new WSVMainTable(this,"",false);

	new WText("<div id='view_panel' class='panel_view'>",m_pMainTable->GetContentTable()->elementAt(1,0));
	//m_pMainTable->GetContentTable()->elementAt(1,0)->resize(0, WLength(200, WLength::Pixel));

	m_pMainFlexTable = new WSVFlexTable(m_pMainTable->GetContentTable()->elementAt(1,0),ReportList,szReport);
	m_pMainFlexTable->SetDivId("listpan1");

//	AddJsParam("treeviewPanel", m_pMainFlexTable->formName());
	strListHeights += "200";
	strListHeights += ",";
	strListPans += m_pMainFlexTable->GetDivId();
	strListPans += ",";
	strListTitles +=  m_pMainFlexTable->formName();
	strListTitles += ",";


	//最外层表格
	//WTable * FrameTable = new WTable(m_pMainFlexTable->GetContentTable()->elementAt(0,0));
	
	//reporttitle = new WText(szReport, (WContainerWidget*)FrameTable->elementAt(0, 0));
	//FrameTable->elementAt(0, 0)->setStyleClass("t1title");

	//空表格
	//WTable * blanktable = new WTable((WContainerWidget*)FrameTable->elementAt(1, 0));
	//blanktable->setStyleClass("t3");

	
	//
	//FrameTable->elementAt(0,0)->setStyleClass("table_data_grid");

	pMonitorListTable = new WTable((WContainerWidget*)m_pMainFlexTable->GetContentTable()->elementAt(2,0));
	//Jansion.zhou 2006-12-27
	m_pMainFlexTable->GetContentTable()->elementAt(2, 0)->resize(WLength(2000, WLength::Pixel), 0);
	pMonitorListTable->setCellSpaceing(0);
	pMonitorListTable->setCellSpaceing(0);



	//AddGroupOperate(m_pMainTable->GetContentTable(), 3);

	AddGroupOperate();
	AddColum(NULL);	

	new WText("</div>",m_pMainTable->GetContentTable()->elementAt(1,0));


	new WText("</div>");


	AddJsParam("bGeneral", "false");
	AddJsParam("uistyle", "viewpan");
	AddJsParam("fullstyle", "false");
	new WText("<SCRIPT language='JavaScript' src='/Script.js'></SCRIPT>", this);
}

//添加客户端脚本变量
void CStatsReportList::AddJsParam(const std::string name, 
								  const std::string value)
{  
	std::string strTmp("");
	strTmp += "<SCRIPT language='JavaScript' > var ";
	strTmp += name;
	strTmp += "='";
	strTmp += value;
	strTmp += "';</SCRIPT>";
	new WText(strTmp, this);
}

void CStatsReportList::AddColum(WTable* pContain)
{		
	char buf_tmp[4096]={0};
    int nSize =4095;
#ifdef WTGET
	GetEnvironmentVariable( "QUERY_STRING", buf_tmp,nSize);
#else
 	char * tmpquery;
	tmpquery = getenv( "QUERY_STRING");
	if(tmpquery)
		strcpy(buf_tmp,tmpquery);
#endif
		std::string repbuf = RetRepHrefStr(buf_tmp);
	memset(buf_tmp, 0, 4096);
	strcpy(buf_tmp, repbuf.c_str());

	strRefreshID = buf_tmp;

	if(strcmp(buf_tmp, "") == 0)
	{
		if(strRefresh.empty())
		{
			return;
		}
		
	}
	else
	{		
		std::string fstr = buf_tmp;
		std::string s = fstr.substr(0, 3);
		if(strcmp(s.c_str(), "id=") == 0)
		{
			strRefresh = buf_tmp;
		}

	}

	

	std::list<string> grouplist;

	char outstr[256];	

	if(!strRefresh.empty())
	{
		
		std::string buf1 = strRefresh;
		int pos = buf1.find("=", 0);
		querystr = buf1.substr(pos+1, buf1.size() - pos - 1);

		szReport = "";
		szReport += querystr;
		//reporttitle->setText(szReport);
		
		m_pMainFlexTable->pTitleTxt->setText(szReport);

		std::string defaultret = "error";
		std::string groupright = GetIniFileString(querystr, "GroupRight",  defaultret, "reportset.ini");

		int pos2 = 0;
		int pos1;
				
		while(pos2 >= 0)
		{
			pos1 = pos2;
			pos2 = groupright.find(",", ++pos2 );
			std::string tempstr = groupright.substr(pos1 + 1, pos2 - pos1 - 1);			
			if(!tempstr.empty())
			{
				grouplist.push_back(tempstr);			
			}
		}						
	}

	std::list<string>::iterator item;
	int tablenum = 2;
	int tablenum1 = 2;

	//pGenReportButn = new WPushButton(szCreateImm, pMonitorListTable->elementAt(0, 0));
	//if(pGenReportButn)
	//{
	//	
	//	WObject::connect(pGenReportButn, SIGNAL(clicked()), "showbar();", this, SLOT(FastGenReport())
	//			, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	//}

	//new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)pMonitorListTable->elementAt(0, 0));
	////返回按钮 2006-10-30

	//pReturnBtn = new WPushButton(m_formText.szReturn, (WContainerWidget*)pMonitorListTable->elementAt(0, 0));
	////pMonitorListTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
	//if(pReturnBtn)
	//{
	//	WObject::connect(pReturnBtn, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainReport()),
	//		WObject::ConnectionType::JAVASCRIPTDYNAMIC);
	//}

	pMonitorListTable->elementAt(0, 0)->resize(WLength(30,WLength::Pixel),0);
	pMonitorListTable->elementAt(0, 0)->tablecellprop_=2;
	pMonitorListTable->elementAt(0, 0)->tablecellprop = " nowrap";
	pMonitorListTable->elementAt(0, 0) ->setStyleClass("table_data_grid_header_text_rp");
	pMonitorListTable->elementAt(0, 0)->setContentAlignment(AlignCenter | AlignMiddle);
	WImage *tmp = new WImage("/Images/space.gif", (WContainerWidget *)pMonitorListTable->elementAt(0, 0));
	tmp->resize(WLength(8,WLength::Pixel),WLength(8,WLength::Pixel));
	
	new WImage("/Images/space.gif", (WContainerWidget *)pMonitorListTable->elementAt(0, 1));

	pMonitorListTable->elementAt(0, 2)->resize(WLength(340,WLength::Pixel),0);
	pMonitorListTable->elementAt(0, 2)->tablecellprop_=2;
	pMonitorListTable->elementAt(0, 2)->tablecellprop = " nowrap";
	pMonitorListTable->elementAt(0, 2) ->setStyleClass("table_data_grid_header_text_rp");
	pMonitorListTable->elementAt(0, 2)->setContentAlignment(AlignCenter | AlignMiddle);
	//解决英文版出现中文的问题 苏合 2007-07-17
	//new WText("时间段", (WContainerWidget *)pMonitorListTable->elementAt(0, 2));
	new WText(szTimePeriod, (WContainerWidget *)pMonitorListTable->elementAt(0, 2));
	//解决英文版出现中文的问题 苏合 2007-07-17


	int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{
		pTranslateBtn->show();
		pExChangeBtn->show();
	}
	else
	{
		pTranslateBtn->hide();
		pExChangeBtn->hide();
	}

	std::list<string> agrouplist;
	std::list<string>::iterator agroupitem;

	for(item = grouplist.begin(); item != grouplist.end(); item++)
	{
		std::string str = *item;		

		OBJECT	hGroup = GetGroup(str);
		std::list<string> monitoridlist;
		std::list<string>::iterator monitoridlistitem;
		if(hGroup == INVALID_VALUE)
		{
			hGroup = GetEntity(str);			
			bool bRet = GetSubMonitorsIDByEntity(hGroup, monitoridlist);
			for(monitoridlistitem = monitoridlist.begin();\
				monitoridlistitem != monitoridlist.end(); monitoridlistitem++)
			{
				std::string itemstr = *monitoridlistitem;
				//MonitorColumnSet(itemstr, tablenum, tablenum1);
				//设备下的监测器ID加入到agrouplist列表中，用于判断后续监测器是否已增加过
				agrouplist.push_back(itemstr);
			}
		}
		else
		{
			continue;
		}

		//判断在权限设置中是否已存在监测器ID 10-16
		bool bExist = false;
		for(agroupitem = agrouplist.begin(); agroupitem != agrouplist.end(); agroupitem++)
		{
			std::string temp = *agroupitem;
			if(strcmp(temp.c_str(), str.c_str()) == 0)
			{
				bExist = true;
				break;
			}
		}
		
		//如果不存在则增加
		if(!bExist)
		{
			agrouplist.push_back(str);
			//MonitorColumnSet(str, tablenum, tablenum1);
		}
		
	}

OutputDebugString("--------------- section querystr = ");
OutputDebugString(querystr.c_str());
OutputDebugString("\n");

	//Jansion.zhou  querystr为报告名称
	AddTableContentFromIni(querystr, "reportgenerate.ini",  pMonitorListTable);
	//AddTableContentFromIni(querystr, "reportset.ini",  pMonitorListTable);

	pMonitorListTable->setCellSpaceing(0);
	pMonitorListTable->GetRow(0) ->setStyleClass("table_data_grid_header_rp");	
}

void CStatsReportList::ExChange()
{

	string strRefresh = "setTimeout(\"location.href ='/fcgi-bin/StatsReportList.exe?";
	strRefresh += strRefreshID;
	strRefresh += "'\",1250);  ";

	WebSession::js_af_up = strRefresh;

	appSelf->quit();
}
//
void CStatsReportList::Translate()
{
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "StatsReportListRes";
	WebSession::js_af_up += "')";
}

void CStatsReportList::MonitorColumnSet(std::string str,
										int & tablenum,
										int & tablenum1)
{
		OBJECT hTemplet;
		MAPNODE objNode;

		OBJECT hMon = GetMonitor(str);
		
		MAPNODE node = GetMonitorMainAttribNode(hMon);
		std::string value;
		FindNodeValue(node, "sv_name", value);//需要判断是监测器还是组
		if(value.empty())
		{
						
		}
				
		if( hMon != INVALID_VALUE)
		{			
			//取监测器返回值
			std::string getvalue;
			MAPNODE ma=GetMonitorMainAttribNode(hMon) ;
				
			if ( FindNodeValue( ma,"sv_monitortype",getvalue) )
			{			
				hTemplet = GetMonitorTemplet(atoi(getvalue.c_str()));
				MAPNODE node = GetMTMainAttribNode(hTemplet);
				//FindNodeValue(node, "sv_label", monitorname);
			}

			LISTITEM item;
			bool bRet = FindMTReturnFirst(hTemplet, item);
				
			
			if(bRet)
			{
				std::string fieldlabel;
				std::string fieldname;
				std::string fieldtype;
				
				float maxval;
				float minval;
				float perval;
				float lastval;

				colname.push_back(value);
				//objNode = FindNext(item);
				while( (objNode = FindNext(item)) != INVALID_VALUE )
				{					
					FindNodeValue(objNode, "sv_label", fieldlabel);		
					fieldlabel =GetLabelResource(fieldlabel);
					FindNodeValue(objNode, "sv_type", fieldtype);								
					FindNodeValue(objNode, "sv_name", fieldname);

					//fieldlabel = GetLabelResource(fieldlabel);

					std::string szPrimary;
					FindNodeValue(objNode, "sv_primary", szPrimary);
					if(strcmp(szPrimary.c_str(), "1") == 0)
					{
						std::string tempcol = value;
						tempcol += "$";
						tempcol += fieldlabel;
						tempcol += "$";
						colname1.push_back(tempcol);
						
						std::string tstr = value;
						tstr += "(";
						tstr += fieldlabel;
						tstr += ")";

						new WText(tstr, pMonitorListTable->elementAt(0,tablenum));	
						pMonitorListTable->elementAt(0,tablenum)->tablecellprop_ = 2;
						pMonitorListTable->elementAt(0,tablenum)->tablecellprop = " colspan=3 width=300 ";
						pMonitorListTable->elementAt(0, tablenum) ->setContentAlignment(AlignTop | AlignCenter);

						pMonitorListTable->elementAt(0, tablenum) ->setStyleClass("Statst3left");
						pMonitorListTable->elementAt(1, tablenum) ->setContentAlignment(AlignTop | AlignCenter);

						
						new WText(szMinValue, pMonitorListTable->elementAt(1, tablenum1));
						pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
						tablenum1++;
						new WText(szAverageValue, pMonitorListTable->elementAt(1, tablenum1));
						pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
						tablenum1++;
						new WText(szMaxValue, pMonitorListTable->elementAt(1, tablenum1));
						pMonitorListTable->elementAt(1, tablenum1)->setContentAlignment(AlignTop | AlignCenter);
						
						tablenum1++;
						tablenum++;

					}
				}
			}
			if(hTemplet != INVALID_VALUE)
			{
				CloseMonitorTemplet(hTemplet);
			}
		}
		
		CloseMonitor(hMon);
}

void CStatsReportList::AddTableContentFromIni(std::string section,
											  std::string filename,
											  WTable *pContain)
{
	
	std::list<string> keylist;
	std::list<string>::iterator keyitem;
	std::list<string> sectionlist;
	std::list<string>::iterator sectionitem;
	std::string keystr;
	std::string keyval;
	int pos = 0; int pos1 = 0;
	OutputDebugString("**************empty   empty\n");
	if(section.empty())
	{
		return;
	}


	//Jansion.zhou :Get all StatsReport list data.
	GetIniFileSections(sectionlist, filename);

	int num =2;
	
	bool bNull = true;

OutputDebugString("000000000000000000000000000000000000000000000\n");

	std::list<string>::iterator tempitem;
	for(sectionitem = sectionlist.begin(); sectionitem != sectionlist.end(); sectionitem++)
	{
		std::string tempsection = *sectionitem;


		//OutputDebugString("+++ Alldata = ");
		//OutputDebugString(tempsection.c_str());
		//OutputDebugString("\n");

		pos = tempsection.find("$", 0);
		if(pos < 0)
		{
			OutputDebugString("*******************pos pos pos\n");
			continue;
		}

		std::string substr = tempsection.substr(0, pos);
		
		//OutputDebugString("#### tempsection = ");
		//OutputDebugString(substr.c_str());
		//OutputDebugString("\n");

		
		//比较报告名 是否是属于此报告名的报告.  section is report's name Jansion.zhou 2006-12-28
		if(strcmp(substr.c_str(), section.c_str()) == 0)
		{			
			//属于该报告集

			OutputDebugString("222222222222222222222222222222222\n");
			GetIniFileKeys(tempsection, keylist, filename);
			
			if(bNull)
			{
				num = InsertListRow(num,pos, section, tempsection, keylist, filename, true);
				bNull = false;

			}
			else
			{
				num = InsertListRow(num,pos, section, tempsection, keylist, filename);
			}
			nListNum = num;
			
	
		}
	}
	if(bNull)
	{

		WText * nText = new WText("[----------统计报告列表为空-----------]",\
			(WContainerWidget*)pMonitorListTable -> elementAt(num, 0));
		nText ->decorationStyle().setForegroundColor(Wt::red);
		pMonitorListTable -> elementAt(num, 0) -> setContentAlignment(AlignTop | AlignCenter);
	}
}
//手工生成报告
void CStatsReportList::FastGenReport()
{
	//std::string strOpen = "hiddenbar();OpenTest('";
	////std::string strOpen = "hiddenbar();OpenGenReport('";
	////strOpen += "genstatsreport.exe?";
	////strOpen += querystr;
	////strOpen += "')";
	////	
	////WebSession::js_af_up = strOpen;

	strAllTitle.clear();


	std::string openurl = "hiddenbar();location.href='genstatsreport.exe?";
	openurl += querystr;
	openurl += "'";
	OutputDebugString("----------------CStatsReportList::FastGenReport--------------------\n");
	OutputDebugString(openurl.c_str());
	WebSession::js_af_up = openurl;




	/*
	std::string szdaystarttime; std::string szdayendtime;
	std::string szReportName;

	std::string strCmdLine;
	SECURITY_ATTRIBUTES sa;	
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	
	HANDLE hRead, hWrite;

	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	//si.hStdOutput = hWrite;
	//si.hStdError = hWrite;
	si.wShowWindow =SW_HIDE;
	
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	std::string ret = "error";
	if(!querystr.empty())
	{
		std::string szPeriod = GetIniFileString(querystr, "Period", ret, "reportset.ini");
		svutil::TTime dayendtime = svutil::TTime::GetCurrentTimeEx();
		svutil::TTime daystarttime;

		//是否列出阀值
		std::string szBClicket = GetIniFileString(querystr, "ListClicket", ret, "reportset.ini");
		if(strcmp(szBClicket.c_str(), "error") == 0)
		{

		}

		//是否列出错误
		std::string szBListError = GetIniFileString(querystr, "ListError", ret, "reportset.ini");
		if(strcmp(szBListError.c_str(), "error") == 0)
		{
		}

		//是否列出危险
		std::string szBListDanger = GetIniFileString(querystr, "ListDanger", ret, "reportset.ini");
		if(strcmp(szBListDanger.c_str(), "error") == 0)
		{
		}
		//是否禁止生成报告
		std::string szDeny = GetIniFileString(querystr, "Deny", ret, "reportset.ini");
		if(strcmp(szDeny.c_str(), "error") == 0)
		{
		}

		std::string szStatsResult = GetIniFileString(querystr, "StatusResult", ret, "reportset.ini");

		if(strcmp(szStatsResult.c_str(), "error") == 0)
		{
		}

		std::string szListImage = GetIniFileString(querystr, "Graphic", ret, "reportset.ini");
		if(strcmp(szListImage.c_str(), "error") == 0)
		{
		}

		//if(strcmp(szDeny.c_str(), "Yes") != 0)
		//{
		
			if(strcmp(szPeriod.c_str(), "error") != 0)
			{
				if(strcmp(szPeriod.c_str(), szReportDay.c_str()) == 0)
				{				
					daystarttime = dayendtime - svutil::TTimeSpan(1, 0, 0, 0);				
				}
				else if(strcmp(szPeriod.c_str(), szReportWeek.c_str()) == 0)
				{
					daystarttime = dayendtime - svutil::TTimeSpan(7, 0, 0, 0);
				}
				else if(strcmp(szPeriod.c_str(), szReportMonth.c_str()) == 0)
				{
					if(dayendtime.GetMonth() == 1)
					{
						daystarttime = svutil::TTime(dayendtime.GetYear() - 1, 12, \
							dayendtime.GetDay() , dayendtime.GetHour(), \
							dayendtime.GetMinute(), dayendtime.GetSecond());
					}
					else
					{
						daystarttime = svutil::TTime(dayendtime.GetYear(), \
							dayendtime.GetMonth() - 1, dayendtime.GetDay() , \
							dayendtime.GetHour(), dayendtime.GetMinute(), dayendtime.GetSecond());
					}
					
				}

				//strCmdLine = "C:\\Progra~1\\apache~1\\apache2\\fcgi-bin\\statsreport.exe ";
				std::string szRootPath = GetSiteViewRootPath();
				strCmdLine = szRootPath;
				strCmdLine += "\\fcgi-bin\\statsreport.exe ";
					
				szdaystarttime = daystarttime.Format();
				szdaystarttime = replace_all_distinct(szdaystarttime, " ", "_");
				szdaystarttime = replace_all_distinct(szdaystarttime, ":", "_");
				strCmdLine += szdaystarttime;
				strCmdLine += " ";

				szdayendtime = dayendtime.Format();
				szdayendtime = replace_all_distinct(szdayendtime, " ", "_");
				szdayendtime = replace_all_distinct(szdayendtime, ":", "_");
				strCmdLine += szdayendtime;
				strCmdLine += " ";


				replace_all_distinct(querystr, " ", "%20");
				//replace_all_distinct(querystr, "#", "%23");

				
				strCmdLine += querystr;
				

				strCmdLine += " ";

				szReportName = szdaystarttime;
				szReportName += szdayendtime;
				szReportName += querystr;
				szReportName += ".html";

				replace_all_distinct(szReportName, "*", "_");
				replace_all_distinct(szReportName, "/", "_");
				replace_all_distinct(szReportName, "\\", "_");
				replace_all_distinct(szReportName,"?", "_");
				replace_all_distinct(szReportName,  "|", "_");
				replace_all_distinct(szReportName,  "<", "_");
				replace_all_distinct(szReportName,  ">", "_");
				replace_all_distinct(szReportName,  ":", "_");
				replace_all_distinct(szReportName,  "\"", "_");
				replace_all_distinct(szReportName,  " ", "_");
				replace_all_distinct(szReportName,  "%20", "_");
				replace_all_distinct(szReportName, "#", "_");
				

				strCmdLine += szReportName;
				strCmdLine += " ";
				strCmdLine += szBClicket;
				strCmdLine += " ";
				strCmdLine += szBListError;
				strCmdLine += " ";
				strCmdLine += szBListDanger;
				strCmdLine += " ";
				strCmdLine += szStatsResult;
				strCmdLine += " ";
				strCmdLine += szListImage;

				OutputDebugString("--------------------stats report list cmd output------------------\n");
				OutputDebugString(strCmdLine.c_str());
				OutputDebugString("\n");
				
				//strCmdLine = "C:\\Progra~1\\apache~1\\apache2\\fcgi-bin\\statsreport.exe 2006-8-14_16_16_45 2006-8-15_16_16_45 testcolumnreport 2006-8-14_16_16_452006-8-15_16_16_45testcolumnreport.html";
				//strCmdLine = "C:\\Progra~1\\apache~1\\apache2\\fcgi-bin\\siteviewtool.exe";
				
				if (CreateProcess(NULL,(LPSTR) strCmdLine.c_str(), \
					&sa, &sa, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) 
				{
					
				}
				else
				{
						
				}
				WaitForSingleObject( pi.hProcess, INFINITE );

				// Close process and thread handles. 
				CloseHandle( pi.hProcess );
				CloseHandle( pi.hThread );

				
				

				std::string openurl = "hiddenbar();location.href='../report/";
				openurl += szReportName;
				openurl += "'";

				

				WebSession::js_af_up = openurl;
			
			//}			
			pMonitorListTable->setStyleClass("StatsTable");
			pMonitorListTable->tableprop_ = 2;
			pMonitorListTable->tableprop = "border=1 bordercolorlight=#eeeeee bordercolordark=#ffffff ";
			pMonitorListTable->setCellSpaceing(10);

			std::string tempsection = szReportName;
			tempsection += "$";
			tempsection += szdaystarttime;
			tempsection += "$";
			tempsection += szdayendtime;
			tempsection += "$";


			//std::list<string> keylist;

			//GetIniFileKeys(tempsection, keylist, "reportgenerate.ini");

			//nListNum = InsertListRow(nListNum, szReportName.size(), szReportName, tempsection, keylist, "reportgenerate.ini");			
			//refresh();
		}
	}
	*/
	
			
}

void CStatsReportList::ReturnMainReport()
{
	std::string openurl = "hiddenbar();location.href ='/fcgi-bin/reportset.exe?'";

	WebSession::js_af_up = openurl;
}

void CStatsReportList::refresh()
{
	pMonitorListTable->clear();
	colname1.clear();
	m_pList.clear();
	strAllTitle.clear();
	
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>", this);		
	
	AddColum(NULL);
}


std::list<string>  CStatsReportList::ReadFileName(string path)
{
	WIN32_FIND_DATA fd;
	std::list<string> strlist;

	path += "\\*.*";

    HANDLE fr=::FindFirstFile(path.c_str(),&fd);

    while(::FindNextFile(fr,&fd))
    {
        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{

		}
        else
		{
			std::list<string> keylist;
			std::list<string>::iterator itemkey;
			bool bret = GetIniFileKeys("filename", keylist, "tuopfile.ini");
			if(!bret)
			{
			}

			bool bExist = false;
			for(itemkey = keylist.begin(); itemkey != keylist.end(); itemkey++)
			{
				std::string str = *itemkey;
				if(strcmp(str.c_str(), fd.cFileName) == 0)
				{
					bExist = true;
					break;
				}
			}

			if(bExist)
			{
				std::string defaultret = "error";
				std::string sret = GetIniFileString("filename",\
					fd.cFileName, defaultret, "tuopfile.ini");
				strlist.push_back(sret);
			}
			else
			{
				std::string str1 = fd.cFileName;
				int npos = str1.find(".htm", 0);
				if(npos >= 0)
				{
					WriteIniFileString("filename", fd.cFileName,\
						fd.cFileName, "tuopfile.ini");
					strlist.push_back(fd.cFileName);
				}
			}	
		}
    }
	return strlist;
}


void CStatsReportList::SelAll()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(true);
    }
}

void CStatsReportList::SelNone()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
    {
		m_pListItem->pSelect->setChecked(false);
    }
}
void CStatsReportList::SelInvert()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem ++)
    {
		if(m_pListItem->pSelect->isChecked())
		{
			m_pListItem->pSelect->setChecked(false);
		}
		else
		{
			m_pListItem->pSelect->setChecked(true);
		}
    }
}


void CStatsReportList::BeforeDelList()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem++)
	{
		if (m_pListItem->pSelect->isChecked())
		{   
			if(pHideBut)
			{
				string strDelDes = pHideBut->getEncodeCmd("xclicked()") ;
				if(!strDelDes.empty())
				{
					strDelDes  = "_Delclick('" + szAffirmInfo + "','" + szButNum + "','" + szButMatch + "','" + strDelDes + "');"; 
					WebSession::js_af_up = strDelDes;							
				}					
			}
			break;	
		}
	}
}

void CStatsReportList::DelList()
{
	for(m_pListItem = m_pList.begin(); m_pListItem != m_pList.end(); m_pListItem++)
    {
        
        if (m_pListItem->pSelect->isChecked())
        {   
			DeleteIniFileSection(m_pListItem->szSection, "reportgenerate.ini");
		
        }
    }

	WebSession::js_af_up = "location.reload()";
}

//void CStatsReportList::AddGroupOperate(WTable * pTable, int Rows)
void CStatsReportList::AddGroupOperate()
{
    //m_pGroupOperate = new WTable((WContainerWidget *)pTable->elementAt(Rows, 0));
	m_pGroupOperate = new WTable(m_pMainTable->GetContentTable()->elementAt(2,0));
	m_pGroupOperate->setStyleClass("widthauto");
    if ( m_pGroupOperate )
    {

		//Jansion.zhou 2006-12-29
		WTable *pTbl;
		pTbl = new WTable( (WContainerWidget *)m_pGroupOperate->elementAt(0,0));

		WText *pSelAll= new WText(m_formText.szTipSelAll1, (WContainerWidget *)pTbl->elementAt(0,0));
		pTbl->elementAt(0,0)->setStyleClass("button_link_font");
		pSelAll->setStyleClass("linktext");
		if (pSelAll)
		{
			connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		}

		WText *pSelNone=new WText(m_formText.szTipSelNone, (WContainerWidget *)pTbl->elementAt(0,1));
		pTbl->elementAt(0,1)->setStyleClass("button_link_font");
		pSelNone->setStyleClass("linktext");
		if (pSelNone)
		{
			connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		}

		WText *pSelinvert= new WText(m_formText.szTipSelInv, (WContainerWidget *)pTbl->elementAt(0,2));
		pTbl->elementAt(0,2)->setStyleClass("button_link_font");
		pSelinvert->setStyleClass("linktext");
		if (pSelinvert)
		{
			connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
		}

		
		m_pGroupOperate->elementAt(0,1)->setContentAlignment(AlignCenter);
		m_pGroupOperate->elementAt(0,1)->setStyleClass("textbold");
		WTable *pTable = new WTable((WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
		pTable->setStyleClass("widthauto");
		WSVButton* pDel =  new WSVButton(pTable->elementAt(0, 1), m_formText.szTipDel, "button_bg_del.png", "", false);
		if (pDel)
		{
			connect(pDel, SIGNAL(clicked()), this, SLOT(BeforeDelList()));
		}


		m_pGenButton =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 2), szCreateImm, "button_bg_m_black.png", "", true);
		if (m_pGenButton)
		{
			WObject::connect(m_pGenButton, SIGNAL(clicked()), "showbar();", this, SLOT(FastGenReport())
				, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}

		m_pReturnBtn =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 3), m_formText.szReturn, "button_bg_m.png", "", false);
		if (m_pReturnBtn)
		{
				WObject::connect(m_pReturnBtn, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainReport()),
					WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		}






		//Jansion.zhou 2006-12-29
		//m_pGenButton =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 1), szCreateImm, "button_bg_m_black.png", "", true);
		//if (m_pGenButton)
		//{
		//	WObject::connect(m_pGenButton, SIGNAL(clicked()), "showbar();", this, SLOT(FastGenReport())
		//		, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//}


		//WSVButton* pSelAll =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 3), m_formText.szTipSelAll1, "button_bg_m.png", "", false);
		//if (pSelAll)
		//{
		//	connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
		//}

		//WSVButton* pSelNone =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 5), m_formText.szTipSelNone, "button_bg_m.png", "", false);
		//if (pSelAll)
		//{
		//	connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
		//}


		//WSVButton* pSelinvert =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 7), m_formText.szTipSelInv, "button_bg_m.png", "", false);
		//if (pSelAll)
		//{
		//	connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
		//}

		//WSVButton* pDel =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 9), m_formText.szTipDel, "button_bg_m.png", "", false);
		//if (pSelAll)
		//{
		//	connect(pDel, SIGNAL(clicked()), this, SLOT(BeforeDelList()));
		//}


		//m_pReturnBtn =  new WSVButton((WContainerWidget *)m_pGroupOperate->elementAt(0, 11), m_formText.szReturn, "button_bg_m.png", "", false);
		//if (pSelAll)
		//{
		//		WObject::connect(m_pReturnBtn, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainReport()),
		//			WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//}

		//pGenReportButn = new WPushButton(szCreateImm,(WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
		//if(pGenReportButn)
		//{

		//	WObject::connect(pGenReportButn, SIGNAL(clicked()), "showbar();", this, SLOT(FastGenReport())
		//		, WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//}
		//2006-12-29



   //     WImage * pSelAll = new WImage("../Images/selall.gif", \
			//(WContainerWidget *)m_pGroupOperate->elementAt(0, 1));
   //     if (pSelAll)
   //     {
   //         pSelAll->setStyleClass("imgbutton");
			//pSelAll->setToolTip(m_formText.szTipSelAll1);
			//connect(pSelAll, SIGNAL(clicked()), this, SLOT(SelAll()));
   //     }

   //     WImage * pSelNone = new WImage("../Images/selnone.gif",\
			//(WContainerWidget *)m_pGroupOperate->elementAt(0, 2));
   //     if (pSelAll)
   //     {
   //         pSelNone->setStyleClass("imgbutton");
			//pSelNone->setToolTip(m_formText.szTipSelNone);
			//connect(pSelNone, SIGNAL(clicked()), this, SLOT(SelNone()));
   //     }

   //     WImage * pSelinvert = new WImage("../Images/selinvert.gif",\
			//(WContainerWidget *)m_pGroupOperate->elementAt(0, 3));
   //     if (pSelinvert)
   //     {
   //         pSelinvert->setStyleClass("imgbutton");
			//pSelinvert->setToolTip(m_formText.szTipSelInv);
			//connect(pSelinvert, SIGNAL(clicked()), this, SLOT(SelInvert()));
   //     }

		//WImage * pDel = new WImage("../Images/del.gif", \
		//	(WContainerWidget *)m_pGroupOperate->elementAt(0, 4));		

  //      if (pDel)
  //      {
  //         
		//	pDel->setStyleClass("imgbutton");
		//	pDel->setToolTip(m_formText.szTipDel);
		//	connect(pDel , SIGNAL(clicked()),this, SLOT(BeforeDelList()));
  //      }



		//pReturnBtn = new WPushButton(m_formText.szReturn, (WContainerWidget*)m_pGroupOperate->elementAt(0, 6));
		////pMonitorListTable->elementAt(0, 0)->setContentAlignment(AlignTop | AlignLeft);
		//if(pReturnBtn)
		//{
		//	WObject::connect(pReturnBtn, SIGNAL(clicked()), "showbar();", this, SLOT(ReturnMainReport()),
		//		WObject::ConnectionType::JAVASCRIPTDYNAMIC);
		//}

		pTranslateBtn = new WPushButton(strTranslate, (WContainerWidget *)m_pGroupOperate->elementAt(0, 12));
		connect(pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
		pTranslateBtn->setToolTip(strTranslateTip);
		pTranslateBtn->hide();


		pExChangeBtn = new WPushButton(strRefresh1, (WContainerWidget *)m_pGroupOperate->elementAt(0, 13));
		connect(pExChangeBtn, SIGNAL(clicked()), this, SLOT(ExChange()));	
		pExChangeBtn->setToolTip(strRefreshTip1);
		pExChangeBtn->hide();
		
		//m_pGroupOperate->elementAt(0, 9)->resize(WLength(100,WLength::Percentage),\
		//	WLength(100,WLength::Percentage));
		//m_pGroupOperate->elementAt(0, 9)->setContentAlignment(AlignRight);
    }

	//隐藏按钮
	pHideBut = new WPushButton("hide button",this);
	if(pHideBut)
	{
		pHideBut->setToolTip("Hide Button");
		connect(pHideBut,SIGNAL(clicked()),this,SLOT(DelList()));
		pHideBut->hide();
	}
}


typedef void(*func)(int , char **);

//////////////////////////////////////////////////////////////////////////////////
void usermain(int argc, char * argv[])
{
    WApplication app(argc, argv);
    app.setTitle("统计报告列表");
	
    CStatsReportList setform(app.root());
	setform.appSelf = &app;
    app.exec();
}


int main(int argc, char *argv[])
{
    func p = usermain;
	if (argc == 1) 
    {
        char buf[256];
		
		WebSession s(buf, false);
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


