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

class CShowLog :public WContainerWidget
{
	//MOC: W_OBJECT CShowLog:WContainerWidget
    W_OBJECT;
public:
	CShowLog(WContainerWidget *parent = 0);
	~CShowLog(void);

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
