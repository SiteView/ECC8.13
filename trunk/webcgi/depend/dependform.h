

#ifndef _SV_DEPEND_TREE_H_
#define _SV_DEPEND_TREE_H_

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WApplication"
#include "../../opens/libwt/WContainerWidget"
#include <string>
#include <list>

using namespace std;

#include "../dependtree/CheckBoxTreeView.h"

class WSPopTable;

class SVDepend : public WContainerWidget
{
    //MOC: W_OBJECT SVDepend:WTable
    W_OBJECT;
public :
    SVDepend(WContainerWidget* parent = NULL);
    virtual void refresh();
public signals:
private slots:
    //MOC: SLOT SVDepend::closeWnd()
    void closeWnd();
    //MOC: SLOT SVDepend::cancel()
    void cancel();
	//MOC: SLOT SVDepend::Translate()
	void Translate();
	//MOC: SLOT SVDepend::ExChange()
	void ExChange();
private:
    void        loadString();
    void        initForm();
    void        createOperate();
    void        showTranslate();

    string      getSEID(const char* pQuery);


	WSPopTable  *m_pMainTable;
	void AddJsParam(const std::string name, const std::string value);

	WTable		*m_pWholeTable;

private:
    string      m_szTitle;
    string      m_szSave;
    string      m_szSaveTip;
    string      m_szClose;
    string      m_szCloseTip;
	std::string strTranslate;
	std::string strTranslateTip;
	std::string strRefresh;
	std::string strRefreshTip;
	string      m_szSEID;


	string		strListHeights;
	string		strListPans;
	string		strListTitles;

	string      strAffirm;
	string      strCancel;
private://WT
    WTable   *  m_pContentTable;
    WTable   *  m_pSubContent;
    WScrollArea * m_pScrollArea;

    CCheckBoxTreeView * m_pDependTree;

	WPushButton * m_pTranslateBtn;
	WPushButton * m_pExChangeBtn;
	
	WText		*m_pdiv1;
	WText		*m_pdiv2;
public://WT
	WApplication *  appSelf;

};

#endif
