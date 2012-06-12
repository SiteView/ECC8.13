/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件: addsvse.h
// 添加或者修改SE
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SiteView_Ecc_ADD_SVSE_H_
#define _SiteView_Ecc_ADD_SVSE_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ecctable.h"

class WLineEdit;

class CEccListTable;
class CEccImportButton;
class CEccButton;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEccEidtSVSE : public CEccBaseTable
{
    //MOC: W_OBJECT CEccEidtSVSE:WTable
    W_OBJECT;
public:
    CEccEidtSVSE(WContainerWidget * parent = NULL);

    void EditSVSE(const string &szIndex);               // 编辑 SE    
private:// slots
    //MOC: SLOT CEccEidtSVSE::Cancel()
    void Cancel();                                      // 返回上一级页面
    //MOC: SLOT CEccEidtSVSE::saveSVSE()
    void saveSVSE();                                    // 保存修改

    virtual         void ShowHideHelp();                // 显示帮助
private:
    WLineEdit       *m_pName;                           // SE名称
    WText           *m_pNameErr;

    CEccListTable   *m_pGeneral;

    virtual void    initForm(bool bHasHelp);            // 初始化页面
    void            createGeneral();
    void            createOperater();

    bool            checkName(string &szName);

    string          m_szEditIndex;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
