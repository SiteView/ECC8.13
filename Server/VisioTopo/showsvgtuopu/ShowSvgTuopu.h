#pragma once
#include "WContainerWidget"
#include <list>
#include <string>
#include <iostream>
#include <WPushButton>

class WText;
class WTable;
class WImage;
class WTextArea;
class WLineEdit;
class CMainTable;
class WApplication;

using namespace std;

class CShowSvgTuopu :public WContainerWidget
{
	//MOC: W_OBJECT CShowSvgTuopu:WContainerWidget
    W_OBJECT;
public:
	CShowSvgTuopu(WContainerWidget *parent = 0);
	~CShowSvgTuopu(void);

public:
	WApplication*  appSelf;

	virtual void refresh();

public :
	
	WTable * pContainTable;
	int nTotleLine, nPageLine, nCurLine, nStartLine;

	//
	string strPath;
	string querystr;

	string strMainTitle;
	string strPageLine;

	int refreshCount;
};
