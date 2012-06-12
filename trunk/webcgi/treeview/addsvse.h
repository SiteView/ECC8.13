/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�: addsvse.h
// ��ӻ����޸�SE
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

    void EditSVSE(const string &szIndex);               // �༭ SE    
private:// slots
    //MOC: SLOT CEccEidtSVSE::Cancel()
    void Cancel();                                      // ������һ��ҳ��
    //MOC: SLOT CEccEidtSVSE::saveSVSE()
    void saveSVSE();                                    // �����޸�

    virtual         void ShowHideHelp();                // ��ʾ����
private:
    WLineEdit       *m_pName;                           // SE����
    WText           *m_pNameErr;

    CEccListTable   *m_pGeneral;

    virtual void    initForm(bool bHasHelp);            // ��ʼ��ҳ��
    void            createGeneral();
    void            createOperater();

    bool            checkName(string &szName);

    string          m_szEditIndex;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
