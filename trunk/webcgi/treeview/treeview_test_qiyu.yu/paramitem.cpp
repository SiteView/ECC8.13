#include "paramitem.h"
#include "basefunc.h"
#include "debuginfor.h"
#include "eccobjfunc.h"
#include "mainview.h"

#include "../../opens/libwt/WTable"
#include "../../opens/libwt/WText"
#include "../../opens/libwt/WTextArea"
#include "../../opens/libwt/WComboBox"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WRadioButton"
#include "../../opens/libwt/WLineEdit"

#include "../../opens/boost/regex.hpp"
#include "../../base/des.h"

#include "resstring.h"

#ifdef WIN32
#include <windows.h>
#endif

typedef (ListDevice)(const char* szQuery, char* szReturn, int &nSize);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
CEccParamItem::CEccParamItem(MAPNODE nodeobj)
{
    m_mainNode          = nodeobj;
    m_szFollow          = "";
    m_pErr              = NULL;
    m_pFollowItem       = NULL;
    m_pHelp             = NULL;
    m_pActiveX          = NULL;
    m_pLabel            = NULL;
    m_bHasParent        = false;
    m_bParentFind       = false;

    m_szDefaultValue    = "";

    if(m_mainNode != INVALID_VALUE)
        enumProperty();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
CEccParamItem::~CEccParamItem()
{
    if(m_pActiveX)
        delete m_pActiveX;
    if(m_pLabel)
        delete m_pLabel;
    if(m_pHelp)
        delete m_pHelp;

    if(m_pErr)
        delete m_pErr;

    m_ValueList.clear();
    m_iValueList.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccParamItem::checkComboBox()
{
    if(((WComboBox*)m_pActiveX)->currentText().empty())
    {
        if(m_szAllowNull == "true" || m_szAllowNull.empty())
            return true;
        else
        {
            showTip();
            return false;
        }
    }
    else
    {
        string szValue ("");
        listitem it = m_ValueList.find(reinterpret_cast<WComboBox*>(m_pActiveX)->currentText());
        if(it != m_ValueList.end())
            szValue = it->second;

        if(m_szIsNumber == "true")
        {
            if(!SV_IsNumeric(szValue))
            {
                showTip();
                return false;
            }
        }
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccParamItem::checkTextArea()
{     
    string szValue = ((WTextArea*)m_pActiveX)->text();
    if(szValue.empty())
    {
        if(m_szAllowNull == "true" || m_szAllowNull.empty())
            return true;
        else
        {
            showTip();
            return false;
        }
    }
    else
    {
        if(m_szIsNumber == "true")
        {
            if(!SV_IsNumeric(szValue))
            {
                showTip();
                return false;
            }
        }        
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccParamItem::checkTextEdit()
{
    string szValue = ((WLineEdit*)m_pActiveX)->text();
    if(szValue.empty())
    {
        if(m_szAllowNull == "true" || m_szAllowNull.empty())
            return true;
        else
        {
            showTip();
            return false;
        }
    }
    else
    {
        if(m_szIsNumber == "true")
        {
            if(!SV_IsNumeric(szValue))
            {
                showTip();
                return false;
            }
        }        
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// У�� ֵ
bool CEccParamItem::checkValue()
{
    hideTip();
    if(m_szHidden == "true" || m_pActiveX == NULL)
        return true;
    if(m_szType.compare(svTextbox) == 0 )
        return checkTextEdit();
    else if(m_szType.compare(svTextArea) == 0)
        return checkTextArea();
    else if(m_szType.compare(svComboBox) == 0)
        return checkComboBox();
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ��ʾ
void CEccParamItem::showTip()
{
    if(!m_szFollow.empty() && m_pFollowItem != NULL)
    {
        m_pFollowItem->showTip();
        return;
    }
    if(m_pErr)
        m_pErr->show();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::showHelp(bool bShow)
{
    if(!m_szFollow.empty() && m_pFollowItem != NULL)
    {
        m_pFollowItem->showHelp(bShow);
        return;
    }

    if(m_pHelp)
    {
        if(bShow)
            m_pHelp->show();
        else
            m_pHelp->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ��ʾ
void CEccParamItem::hideTip()
{
    if(!m_szFollow.empty() && m_pFollowItem != NULL)
    {
        m_pFollowItem->hideTip();
        return;
    }
    if(m_pErr)
        m_pErr->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö��ָ������
void CEccParamItem::enumProperty()
{
    FindNodeValue(m_mainNode, svSaveName, m_szSaveName);
    FindNodeValue(m_mainNode, svName, m_szName);                    // ����
    if(m_szName == "_OsType")
        enumOS();

    FindNodeValue(m_mainNode, svType, m_szType);                    // ����
    if(FindNodeValue(m_mainNode, svLabel, m_szLabel))               // ��ǩ
        m_szLabel = SVResString::getResString(m_szLabel.c_str());

    FindNodeValue(m_mainNode, svAllowNull, m_szAllowNull);          // �Ƿ�����Ϊ��
    if(FindNodeValue(m_mainNode, svTip, m_szTip))                   // ��ʾ
        m_szTip = SVResString::getResString(m_szTip.c_str());

    if(FindNodeValue(m_mainNode, svHelpText, m_szHelp))             // ����
        m_szHelp = SVResString::getResString(m_szHelp.c_str());

    FindNodeValue(m_mainNode, svStyle, m_szStyle);
    FindNodeValue(m_mainNode, svRun, m_szIsRun);

    FindNodeValue(m_mainNode, svDLL, m_szDllName);
    FindNodeValue(m_mainNode, svFunc, m_szFuncName);
    FindNodeValue(m_mainNode, svValue, m_szDefaultValue);           // ȱʡֵ
    FindNodeValue(m_mainNode, svIsNumeric, m_szIsNumber);           // �Ƿ�Ϊ����
    FindNodeValue(m_mainNode, svFollow, m_szFollow);                // ����
    FindNodeValue(m_mainNode, svHidden, m_szHidden);
    FindNodeValue(m_mainNode, svReadOnly, m_szIsReadOnly);

    FindNodeValue(m_mainNode, svAccountWith, m_szAccount);
    FindNodeValue(m_mainNode, svExpressions, m_szExpress);
    FindNodeValue(m_mainNode, svNoSort, m_szNoSort);

    string szMax (""), szMin (""), szWidth (""), szSyn ("");
    FindNodeValue(m_mainNode, svMax, szMax);                // max
    FindNodeValue(m_mainNode, svMin, szMin);                // min   
    FindNodeValue(m_mainNode, svSynTitle, szSyn);
    if(szSyn == "true")
        m_bSynTitle = true;
    else
        m_bSynTitle = false;

    if(m_szType.compare(svComboBox) == 0)
    {
        string szCount ("");
        FindNodeValue(m_mainNode, svItemCount, szCount);
        if(!szCount.empty())
        {
            int nCount = atoi(szCount.c_str());
            char szKey1[16] = {0}, szKey2[16] = {0};
            for(int i = 1; i <= nCount; i++)
            {
                sprintf(szKey1, svItemLable, i);
                sprintf(szKey2, svItemValue, i);
                string szLabel (""), szValue ("");
                if(FindNodeValue(m_mainNode, szKey1, szLabel))
                    szLabel = SVResString::getResString(szLabel.c_str());

                FindNodeValue(m_mainNode, szKey2, szValue);                // 
                if(!szValue.empty() && !szLabel.empty())
                {
                    if(m_szNoSort == "true")
                        addNoSortList(szValue, szLabel);
                    else
                        m_ValueList[szLabel] = szValue;
                }
            }
        }
    }

    if(szWidth.empty())
        m_nWidth = 20;
    else
        m_nWidth = atoi(szWidth.c_str());

    if(szMax.empty())
        m_nMax = -1;
    else
        m_nMax = atoi(szMax.c_str());

    if(szMin.empty())
        m_nMin = -1;
    else
        m_nMin = atoi(szMin.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����ؼ�
void CEccParamItem::CreateControl(WTable *pTable, list<WText*> &lsHelp, bool bShowHelp)
{
    if(m_szHidden == "true") 
        return;

    if(!m_szType.empty())
    {
        int nRow = pTable->numRows();

        if(m_bHasParent)
        {
            nRow -= 1;
        }
        else
        {
            if(!this->m_szLabel.empty())
            {
                m_pLabel = new WText(m_szLabel, pTable->elementAt(nRow, 0));
                if(!m_szAllowNull.empty() && m_szAllowNull != "true")
                    new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));
            }
        }

        if(m_szType.compare(svTextbox) == 0)
        {
            m_pActiveX = new WLineEdit(m_szDefaultValue, pTable->elementAt(nRow, 1));
            if(m_pActiveX && m_szIsReadOnly == "true")
                strcpy(reinterpret_cast<WLineEdit*>(m_pActiveX)->contextmenu_, "READONLY");
        }
        else if (m_szType.compare(svTextArea) == 0)
        {
            m_pActiveX = new WTextArea(m_szDefaultValue, pTable->elementAt(nRow, 1));
            if(m_pActiveX)
            {
                ((WTextArea*)m_pActiveX)->setRows(5);
            }
        }
        else if(m_szType.compare(svCheckBox) == 0)
        {
            m_pActiveX = new WCheckBox(m_szDefaultValue, pTable->elementAt(nRow, 1));
        }
        else if(m_szType.compare(svComboBox) == 0)
        {
            m_pActiveX = new WComboBox(pTable->elementAt(nRow, 1));
            if(m_pActiveX && (m_szDllName.empty() || m_szFuncName.empty()))
            {
                if(m_szNoSort == "true")
                {
                    for(irow it = m_iValueList.begin(); it != m_iValueList.end(); it++)
                    {
                        SVTableCell *pcell = (*it).second.Cell(0);
                        if(pcell && pcell->Type() == adString && pcell->Value() != NULL)
                        {
                            reinterpret_cast<WComboBox*>(m_pActiveX)->addItem(static_cast<const char*>(pcell->Value()));
                        }
                    }
                }
                else
                {
                    listitem it;
                    if(m_ValueList.size() > 0)
                    {
                        for(it = m_ValueList.begin(); it != m_ValueList.end(); it ++)
                            reinterpret_cast<WComboBox*>(m_pActiveX)->addItem(it->first);
                    }
                }
                if(!m_szDefaultValue.empty())
                    reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndexByStr(m_szDefaultValue);
            }
            else
            {
                reinterpret_cast<WComboBox*>(m_pActiveX)->addItem("loading...");
            }
        }
        else if(m_szType.compare(svPassword) == 0)
        {
            m_pActiveX = new WLineEdit(m_szDefaultValue, pTable->elementAt(nRow, 1));
            ((WLineEdit*)m_pActiveX)->setEchoMode(WLineEdit::EchoMode::Password);
        }
        else
        {
            WText *pErr = new WText(m_szName + SVResString::getResString("<%IDS_SNMP_14%>"), pTable->elementAt(nRow, 1));
            if(pErr)
                pErr->setStyleClass("required");
        }

        if(!m_szStyle.empty() && m_pActiveX)
            m_pActiveX->setStyleClass(m_szStyle);

        if(!m_szFollow.empty())
        {   // �и���ֵ
            new WText("&nbsp;", pTable->elementAt(nRow, 1) );
            return ;
        }

        // ���������ı�
        if(!m_szHelp.empty())
        {
            m_pHelp = new WText(m_szHelp, pTable->elementAt(nRow + 1, 1));
            if(m_pHelp)
            {
                if(!bShowHelp)
                    m_pHelp->hide();                    // ����

                pTable->elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des");    // ������ʽ��

                lsHelp.push_back(m_pHelp);
            }
        }

        if(!m_szTip.empty())
        {
            m_pErr = new WText(m_szTip, pTable->elementAt(nRow + 2, 1));
            if(m_pErr)
            {
                m_pErr->hide();
                pTable->elementAt(nRow + 2, 1)->setStyleClass("table_data_input_error");
            }
        }

        // ������Ԫ���뷽ʽΪ���϶���
        pTable->elementAt(nRow, 0)->setContentAlignment(WTable::AlignLeft | WTable::AlignTop);
        pTable->GetRow(nRow)->setStyleClass("padding_top");
        pTable->elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
        pTable->elementAt(nRow, 1)->setStyleClass("table_data_text");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȡ string ֵ
void CEccParamItem::getStringValue(string &szValue)
{
    if(m_szHidden == "true" || m_pActiveX == NULL)
    {
        szValue = m_szDefaultValue;
        return ;
    }

    if(m_szType.compare(svTextbox) == 0)
    {
        szValue =  ((WLineEdit*)m_pActiveX)->text().c_str();
    }
    else if(m_szType.compare(svCheckBox) == 0)
    {
        if(((WCheckBox*)m_pActiveX)->isChecked())
            szValue = "true";
        else
            szValue = "false";
    }
    else if( m_szType.compare(svPassword) == 0)
    {
        szValue =  ((WLineEdit*)m_pActiveX)->text().c_str();
        char szOutput[512] = {0};
        Des des;
        if(des.Encrypt(szValue.c_str(), szOutput))
            szValue = szOutput;
    }
    else if(m_szType.compare(svTextArea) == 0)
    {
        szValue = ((WTextArea*)m_pActiveX)->text();
    }
    else if(m_szType.compare(svComboBox) == 0)
    {
        if(m_szNoSort == "true")
        {
            const char* pszValue = getNoSortString();
            if(pszValue)
                szValue = pszValue;
        }
        else
        {
            listitem it = m_ValueList.find(reinterpret_cast<WComboBox*>(m_pActiveX)->currentText());
            if(it != m_ValueList.end())
                szValue = it->second;
        }
    }
    if(!szValue.empty())
    {
        szValue = strtriml(szValue.c_str());
        szValue = strtrimr(szValue.c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::setStringValue(string &szValue)
{
    m_szValue = szValue;
    if(m_szHidden == "true" || m_pActiveX == NULL || m_bParentFind)
        return;
    if(m_szType.compare(svTextbox) == 0)
    {
        if(szValue.empty() && !m_szDefaultValue.empty())
            ((WLineEdit*)m_pActiveX)->setText(m_szDefaultValue);
        else
            ((WLineEdit*)m_pActiveX)->setText(szValue);
    }
    else if( m_szType.compare(svPassword) == 0)
    {
        if(szValue.empty() && !m_szDefaultValue.empty())
            ((WLineEdit*)m_pActiveX)->setText(m_szDefaultValue);
        else
        {
            char szOutput[512] = {0};
            Des des;
            if(des.Decrypt(szValue.c_str(), szOutput))
                ((WLineEdit*)m_pActiveX)->setText(szOutput);
            else
                ((WLineEdit*)m_pActiveX)->setText(szValue);
        }
    }
    else if(m_szType.compare(svTextArea) == 0)
    {
        if(szValue.empty() && !m_szDefaultValue.empty())
            ((WTextArea*)m_pActiveX)->setText(m_szDefaultValue);
        else
            ((WTextArea*)m_pActiveX)->setText(szValue);
    }
    else if(m_szType.compare(svCheckBox) == 0)
    {
        if(szValue == "true")
            ((WCheckBox*)m_pActiveX)->setChecked(true);
        else
            ((WCheckBox*)m_pActiveX)->setChecked(false);
    }
    else if(m_szType.compare(svComboBox) == 0)
    {
        if(szValue.empty() && !m_szDefaultValue.empty())
        {
            reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndexByStr(m_szDefaultValue);
        }
        else
        {
            if(m_szNoSort == "true")
            {
                setNoSortString(szValue);
            }
            else
            {
                listitem it;
                for(it = m_ValueList.begin(); it != m_ValueList.end(); it ++)
                {
                    if(it->second == szValue)
                    {
                        reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndexByStr(it->first);
                        if(!m_szFollow.empty() && m_pFollowItem != NULL && m_szName == m_pFollowItem->getSaveName())
                        {
                            m_pFollowItem->m_bParentFind = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::resetDynData()
{
    if(m_szHidden != "true")
    {
        if(m_szType.compare(svComboBox) == 0 && m_pActiveX)
        {
            reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndex(0);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::setDefaultValue()
{
    if(m_szHidden != "true" && m_pActiveX)
    {
        if(m_szType.compare(svTextbox) == 0 || m_szType.compare(svPassword) == 0)
        {
            ((WLineEdit*)m_pActiveX)->setText(m_szDefaultValue);
        }
        else if(m_szType.compare(svTextArea) == 0)
        {
            ((WTextArea*)m_pActiveX)->setText(m_szDefaultValue);
        }
        else if(m_szType.compare(svCheckBox) == 0)
        {
            ((WCheckBox*)m_pActiveX)->setChecked(false);
        }
        else if(m_szType.compare(svComboBox) == 0)
        {
            if(!m_szDefaultValue.empty())
                reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndexByStr(m_szDefaultValue);
            else
                reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndex(0);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::clearDynData()
{
    m_ValueList.clear();
    m_iValueList.clear();
    if(m_szType.compare(svComboBox) == 0)
    {
        while(reinterpret_cast<WComboBox*>(m_pActiveX)->count() > 0)
        {
            reinterpret_cast<WComboBox*>(m_pActiveX)->removeItem(0);
        }
        reinterpret_cast<WComboBox*>(m_pActiveX)->addItem("loading...");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::enumDynValue(const string &szQuery, const string &szIndex)
{
    m_ValueList.clear();
    m_iValueList.clear();

    if(m_pActiveX && m_szType.compare(svComboBox) == 0)
    {
        while(reinterpret_cast<WComboBox*>(m_pActiveX)->count() > 0)
        {
            reinterpret_cast<WComboBox*>(m_pActiveX)->removeItem(0);
        }
    }

    bool bRet = false;
    char szReturn [svBufferSize] = {0};
    int nSize = sizeof(szReturn);
    int nQuerySize = static_cast<int>(szQuery.length()) + 2;
    char *pszQueryString = new char[nQuerySize];
    if(pszQueryString)
    {
        memset(pszQueryString, 0 , nQuerySize);
        EidtQueryString(szQuery, pszQueryString);
        if(FindSEID(szIndex) == "1")
        {
#ifdef WIN32
            string szDllName(makeDllName(m_szDllName));
            string szMsg = "Dll Name: " + szDllName + " Function Name: " + m_szFuncName;
            PrintDebugString(szMsg.c_str());
            HINSTANCE hDll = LoadLibrary(szDllName.c_str());
            if (hDll)
            {   OutputDebugString(("\nwait when loading  "+m_szFuncName+"1111111111111111111111111111111111111\n" ).c_str());
                ListDevice* func = (ListDevice*)GetProcAddress(hDll, m_szFuncName.c_str());
                if (func)
                {
                    bRet = (*func)(pszQueryString, szReturn, nSize);
                }
                FreeLibrary(hDll);
            }
#else
#endif
        }
        else
        {
            bRet = ReadWriteDynQueue(szIndex, m_szDllName, m_szFuncName, pszQueryString, nQuerySize, szReturn, nSize);
        }
        if(bRet)
        {
            char *pos = strstr(szReturn, "error");
            if(pos == NULL)
            {
                list<string> lsReturn;
                ParserReturnInList(szReturn, lsReturn);
                TidyReturnList(lsReturn);
            }
            else
            {
                reinterpret_cast<WComboBox*>(m_pActiveX)->addItem(szReturn);
            }
        }  
        delete []pszQueryString;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::EidtQueryString(const string &szQuery, char* pszQueryString)
{    
    if(pszQueryString)
    {
        strcpy(pszQueryString , szQuery.c_str());
        char *pPos = pszQueryString;
        while((*pPos) != '\0' )
        {
            if((*pPos) == '\v')
                (*pPos) = '\0';
            pPos ++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::ParserReturnInList(const char * szReturn, list<string> &lsReturn)
{
    const char * pPos = szReturn;
    int nSize = 0;
    while(*pPos != '\0')
    {
        nSize = static_cast<int>(strlen(pPos));
        lsReturn.push_back(pPos);
        pPos = pPos + nSize + 1;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::TidyReturnList(list<string> & lsReturn)
{
    list<string>::iterator lsItem;
    int nPos = 0;
    for(lsItem = lsReturn.begin(); lsItem != lsReturn.end(); lsItem++)
    {
        if(!(*lsItem).empty())
        {
            nPos = static_cast<int>((*lsItem).find("="));
            if(nPos > 0)
            {
                string szValue (""), szLabel ("");
                szValue = (*lsItem).substr(0, nPos);
                szLabel = (*lsItem).substr(nPos + 1, (*lsItem).length() - nPos);
                if(!szValue.empty() && !szLabel.empty())
                {
                    if(m_szNoSort == "true")
                        addNoSortList(szValue, szLabel);
                    else
                        m_ValueList[szLabel] = szValue;
                }
            }
        }
    }
    if(m_szNoSort == "true")
    {
        for(irow it = m_iValueList.begin(); it != m_iValueList.end(); it++)
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if(pcell && pcell->Type() == adString && pcell->Value() != NULL)
            {
                reinterpret_cast<WComboBox*>(m_pActiveX)->addItem(static_cast<const char*>(pcell->Value()));
            }
        }
    }
    else
    {
        listitem it;
        for(it = m_ValueList.begin(); it != m_ValueList.end(); it++)
            reinterpret_cast<WComboBox*>(m_pActiveX)->addItem(it->first);
    }

    for(listitem it = m_ValueList.begin(); it != m_ValueList.end(); it ++)
    {
        if(it->second == m_szValue)
        {
            m_szValue = it->first;
            break;
        }
    }

    reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndexByStr(m_szValue);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::MakeValueList(list<ecc_value_list> &lsValue)
{
    if(m_szNoSort == "true")
    {
        for(irow it = m_iValueList.begin(); it != m_iValueList.end(); it ++)
        {
            string szValue(""), szLabel("");
            SVTableCell *pcell = (*it).second.Cell(0);
            if(pcell && pcell->Type() == adString && pcell->Value() != NULL)
            {
                szLabel = static_cast<const char*>(pcell->Value());
                if(pcell->Property())
                    szValue = static_cast<const char*>(pcell->Property());
                
                ecc_value_list item(szLabel, szValue);
                lsValue.push_back(item);
            }
        }
    }
    else
    {
        listitem it;
        for(it = m_ValueList.begin(); it != m_ValueList.end(); it ++)
        {
            ecc_value_list item(it->first, it->second);
            lsValue.push_back(item);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::enumOS()
{
    list<string> lsSections;
    list<string>::iterator lsItem;
    m_ValueList.clear();
    m_iValueList.clear();
    if(m_pActiveX && m_szType.compare(svComboBox) == 0)
    {
        while(reinterpret_cast<WComboBox*>(m_pActiveX)->count() > 0)
        {
            reinterpret_cast<WComboBox*>(m_pActiveX)->removeItem(0);
        }
    }

    if(GetIniFileSections(lsSections, "oscmd.ini"))
    {
        for(lsItem = lsSections.begin(); lsItem != lsSections.end(); lsItem ++)
        {
            string szValue (""), szLabel ("");
            szLabel = GetIniFileString((*lsItem), "description", "", "oscmd.ini");
            szValue = GetIniFileString((*lsItem), "name", "", "oscmd.ini");
            if(!szValue.empty() && !szLabel.empty())
            {
                if(m_szNoSort == "true")
                    addNoSortList(szValue, szLabel);
                else
                    m_ValueList[szLabel] = szValue;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::addNoSortList(string &szText, string &szLabel)
{
    int nSize = m_iValueList.RowCount();

    SVTableCell svcell;
    svcell.setType(adString);
    svcell.setValue(static_cast<const void*>(szLabel.c_str()));
    svcell.setProperty(szText.c_str());
    m_iValueList.WriteCell(nSize, 0, svcell);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CEccParamItem::getNoSortString()
{
    int nIndex = reinterpret_cast<WComboBox*>(m_pActiveX)->currentIndex();

    SVTableRow *pRow = m_iValueList.Row(nIndex);
    if(pRow)
    {
        SVTableCell *pCell = pRow->Cell(0);

        if(pCell)
        {
            return static_cast<const char*>(pCell->Property());
        }
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccParamItem::setNoSortString(string &szValue)
{
    for(irow it = m_iValueList.begin(); it != m_iValueList.end(); it++)
    {
        SVTableCell *pcell = (*it).second.Cell(0);
        if(pcell && pcell->Type() == adString && pcell->Property() != NULL)
        {
            if(szValue.compare(pcell->Property()) == 0 && pcell->Value() != NULL)
            {
                reinterpret_cast<WComboBox*>(m_pActiveX)->setCurrentIndexByStr(static_cast<const char*>(pcell->Value()));
                if(!m_szFollow.empty() && m_pFollowItem != NULL && m_szName == m_pFollowItem->getSaveName())
                {
                    m_pFollowItem->m_bParentFind = true;
                }
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//end file
