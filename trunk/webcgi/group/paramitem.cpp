#include "paramitem.h"

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

extern void PrintDebugString(const char * szMsg);
extern void AddTaskList(WComboBox * pTask = 0);

#include "../../opens/boost/regex.hpp"

#include "../../base/des.h"
#include "resstring.h"

bool SV_IsNumeric(string &szValue)
{
    static const boost::regex e("\\d*");
    return regex_match(szValue, e);
}

#ifdef WIN32
#include <windows.h>
#endif

typedef (ListDevice)(const char* szQuery, char* szReturn, int &nSize);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造
SVParamItem::SVParamItem(MAPNODE nodeobj)
{
    m_mainNode = nodeobj;


    m_szFollow = "";
    m_pFollowItem = NULL;
    m_pHelp = NULL;
    m_pActiveX = NULL;
    m_pLabel = NULL;
    m_bShowHelp = false;
    m_bHasParent = false;
    m_bError = false;
    m_bParentFind = false;

    m_szDefaultValue = "";

    if(m_mainNode != INVALID_VALUE)
        enumProperty();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 析构
SVParamItem::~SVParamItem()
{
    if(m_pActiveX)
        delete m_pActiveX;
    if(m_pLabel)
        delete m_pLabel;
    if(m_pHelp)
        delete m_pHelp;

    m_ValueList.clear();
    m_iValueList.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVParamItem::checkComboBox()
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
        showHelp(m_bShowHelp);
        m_bError = false;
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVParamItem::checkTextArea()
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
        showHelp(m_bShowHelp);
        m_bError = false;
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVParamItem::checkTextEdit()
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
        showHelp(m_bShowHelp);
        m_bError = false;
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 校验 值
bool SVParamItem::checkValue()
{
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
// 显示帮助
void SVParamItem::showHelp(bool bShow)
{
    if(m_bError) return;

    m_bShowHelp = bShow;
    if(m_pHelp)
    {
        m_pHelp->setStyleClass("helps");
        m_pHelp->setText(m_szHelp);
        if(bShow)
            m_pHelp->show();
        else
            m_pHelp->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 显示提示
void SVParamItem::showTip()
{
    if(!m_szFollow.empty() && m_pFollowItem != NULL)
    {
        m_pFollowItem->showTip();
        return;
    }
    if(m_pHelp)
    {
        m_bError = true;
        m_pHelp->setStyleClass("errors");
        m_pHelp->setText(m_szTip);
        m_pHelp->show();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举指定属性
void SVParamItem::enumProperty()
{
    FindNodeValue(m_mainNode, "sv_savename", m_szSaveName);
    FindNodeValue(m_mainNode, "sv_name", m_szName);                    // 名称
    if(m_szName == "_OsType")
        enumOS();

    FindNodeValue(m_mainNode, "sv_type", m_szType);                    // 类型
    if(FindNodeValue(m_mainNode, "sv_label", m_szLabel))               // 标签
        m_szLabel = SVResString::getResString(m_szLabel.c_str());

    FindNodeValue(m_mainNode, "sv_allownull", m_szAllowNull);          // 是否允许为空
    if(FindNodeValue(m_mainNode, "sv_tip", m_szTip))                   // 提示
        m_szTip = SVResString::getResString(m_szTip.c_str());

    if(FindNodeValue(m_mainNode, "sv_helptext", m_szHelp))             // 帮助
        m_szHelp = SVResString::getResString(m_szHelp.c_str());

    FindNodeValue(m_mainNode, "sv_style", m_szStyle);
    FindNodeValue(m_mainNode, "sv_run", m_szIsRun);

    FindNodeValue(m_mainNode, "sv_dll", m_szDllName);
    FindNodeValue(m_mainNode, "sv_func", m_szFuncName);
    FindNodeValue(m_mainNode, "sv_value", m_szDefaultValue);           // 缺省值
    FindNodeValue(m_mainNode, "sv_isnumeric", m_szIsNumber);           // 是否为数字
    FindNodeValue(m_mainNode, "sv_follow", m_szFollow);                // 跟随
    FindNodeValue(m_mainNode, "sv_hidden", m_szHidden);
    FindNodeValue(m_mainNode, "sv_isreadonly", m_szIsReadOnly);

    FindNodeValue(m_mainNode, "sv_accountwith", m_szAccount);
    FindNodeValue(m_mainNode, "sv_expressions", m_szExpress);
    FindNodeValue(m_mainNode, "sv_nosort", m_szNoSort);

    string szMax (""), szMin (""), szWidth (""), szSyn ("");
    FindNodeValue(m_mainNode, "sv_max", szMax);                // max
    FindNodeValue(m_mainNode, "sv_min", szMin);                // min   
    FindNodeValue(m_mainNode, "sv_syntitle", szSyn);
    if(szSyn == "true")
        m_bSynTitle = true;
    else
        m_bSynTitle = false;

    if(m_szType.compare(svComboBox) == 0)
    {
        string szCount ("");
        FindNodeValue(m_mainNode, "sv_itemcount", szCount);
        if(!szCount.empty())
        {
            int nCount = atoi(szCount.c_str());
            char szKey1[16] = {0}, szKey2[16] = {0};
            for(int i = 1; i <= nCount; i++)
            {
                sprintf(szKey1, "sv_itemlabel%d", i);
                sprintf(szKey2, "sv_itemvalue%d", i);
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

    //int nPos = m_szDefaultValue.find("\\", 0);
    //while (nPos > 0)
    //{
    //    m_szDefaultValue = m_szDefaultValue.substr(0, nPos ) + "\\" + 
    //        m_szDefaultValue.substr(nPos, m_szDefaultValue.length() - nPos);
    //    nPos += 2;
    //    nPos = m_szDefaultValue.find("\\", nPos);
    //}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建控件
void SVParamItem::CreateControl(WTable *pTable)
{
    if(m_szHidden == "true") return;
    if(pTable != NULL && !m_szType.empty())
    {
        int nRow = pTable->numRows();

        if(m_bHasParent)
        {
            nRow -= 1;
            //m_pLabel = new WText(m_szLabel, (WContainerWidget*)pTable->elementAt(nRow, 0));
            //if(m_szAllowNull != "true")
            //     new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));
        }
        else
        {
            if(!this->m_szLabel.empty())
            {
                m_pLabel = new WText(m_szLabel, (WContainerWidget*)pTable->elementAt(nRow, 0));
                if(!m_szAllowNull.empty() && m_szAllowNull != "true")
                    new WText("<span class =required>*</span>", pTable->elementAt(nRow, 0));
            }
        }

        //if(!m_szType.empty())
        {
            pTable->elementAt(nRow, 0)->setStyleClass("cell_10");
  
            if(m_szType.compare(svTextbox) == 0)
            {
                m_pActiveX = new WLineEdit(m_szDefaultValue, (WContainerWidget*)pTable->elementAt(nRow, 1));
                if(m_pActiveX && m_szIsReadOnly == "true")
                    strcpy(reinterpret_cast<WLineEdit*>(m_pActiveX)->contextmenu_, "READONLY");
            }
            else if (m_szType.compare(svTextArea) == 0)
            {
                m_pActiveX = new WTextArea(m_szDefaultValue, (WContainerWidget*)pTable->elementAt(nRow, 1));
                if(m_pActiveX)
                {
                    ((WTextArea*)m_pActiveX)->setRows(5);
                }
            }
            else if(m_szType.compare(svCheckBox) == 0)
            {
                m_pActiveX = new WCheckBox(m_szDefaultValue,(WContainerWidget*)pTable->elementAt(nRow, 1));
            }
            else if(m_szType.compare(svComboBox) == 0)
            {
                m_pActiveX = new WComboBox((WContainerWidget*)pTable->elementAt(nRow, 1));
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
                m_pActiveX = new WLineEdit(m_szDefaultValue, (WContainerWidget*)pTable->elementAt(nRow, 1));
                ((WLineEdit*)m_pActiveX)->setEchoMode(WLineEdit::EchoMode::Password);
            }
            if(!m_szStyle.empty())// && m_szIsReadOnly != "true")
                m_pActiveX->setStyleClass(m_szStyle);

            //if(m_szHidden == "true")
            //{
            //    m_pActiveX->hide();
            //    m_pLabel->hide();
            //}

            if(!m_szFollow.empty())
            {   // 有跟随值
                new WText("   ",(WContainerWidget*)pTable->elementAt(nRow, 1) );
                return ;
            }
        }

        new WText("<BR>", (WContainerWidget*)pTable->elementAt(nRow, 1));

        // 创建帮助文本
        if(!m_szHelp.empty())
        {
            m_pHelp = new WText(m_szHelp, (WContainerWidget*)pTable->elementAt(nRow, 1));
            if(m_pHelp)
            {
                m_pHelp->hide();                    // 隐藏
                m_pHelp->setStyleClass("helps");    // 设置样式表
            }
        }

        //
        pTable->elementAt(nRow, 0)->setContentAlignment(WTable::AlignLeft | WTable::AlignTop); // AlignTop | AlignLeft
        pTable->elementAt(nRow, 1)->setContentAlignment(WTable::AlignLeft | WTable::AlignTop); // AlignTop | AlignLeft
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 取 string 值
void SVParamItem::getStringValue(string &szValue)
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
void SVParamItem::setStringValue(string &szValue)
{
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
void SVParamItem::setDefaultValue()
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
void SVParamItem::clearDynData()
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
    //m_szValue = "";
}

void SVParamItem::enumDynValue(const string &szQuery, const string &szIndex, const string &szIDCUser, const string &szIDCPwd)
{
    m_ValueList.clear();
    m_iValueList.clear();
    if(m_szType.compare(svComboBox) == 0)
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
    {
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
            string szMsg = "User is " + szIDCUser + " pwd is " + szIDCPwd;
            PrintDebugString(szMsg.c_str());
            bRet = ReadWriteDynQueue(szIndex, m_szDllName, m_szFuncName, pszQueryString, nQuerySize, szReturn, nSize, szIDCUser, szIDCPwd);
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

void SVParamItem::EidtQueryString(const string &szQuery, char* pszQueryString)
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

void SVParamItem::ParserReturnInList(const char * szReturn, list<string> &lsReturn)
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

void SVParamItem::TidyReturnList(list<string> & lsReturn)
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
}

void SVParamItem::AddDynList(WTable * pTable, SVIntTable & svTable)
{
    if(m_szNoSort == "true")
    {
        for(irow it = m_iValueList.begin(); it != m_iValueList.end(); it ++)
        {
            int nRow = pTable->numRows();
            string szValue(""), szLabel("");
            SVTableCell *pcell = (*it).second.Cell(0);
            if(pcell && pcell->Type() == adString && pcell->Value() != NULL)
            {
                szLabel = static_cast<const char*>(pcell->Value());
                if(pcell->Property())
                    szValue = static_cast<const char*>(pcell->Property());

                WText *pLabel = new WText(szLabel, pTable->elementAt(nRow, 1));
                if(pLabel)
                {
                    SVTableCell svCell;
                    svCell.setType(adText);
                    svCell.setValue(pLabel);
                    svCell.setProperty(szValue.c_str());
                    svTable.WriteCell(nRow, 1, svCell);
                }
            }
        }
    }
    else
    {
        listitem it;
        for(it = m_ValueList.begin(); it != m_ValueList.end(); it ++)
        {
            int nRow = pTable->numRows();
            WText *pLabel = new WText(it->first, pTable->elementAt(nRow, 1));
            if(pLabel)
            {
                SVTableCell svCell;
                svCell.setType(adText);
                svCell.setValue(pLabel);
                svCell.setProperty(it->second.c_str());
                svTable.WriteCell(nRow, 1, svCell);
            }
        }
    }
}

const char* SVParamItem::getValueByLabel(string &szLabel)
{
    if(m_szNoSort == "true")
    {
        for(irow it = m_iValueList.begin(); it != m_iValueList.end(); it++)
        {
            SVTableCell *pcell = (*it).second.Cell(0);
            if(pcell && pcell->Type() == adString && pcell->Value() != NULL)
            {
                if(szLabel.compare(static_cast<const char*>(pcell->Value())) == 0 && pcell->Property() != NULL)
                    return static_cast<const char*>(pcell->Property());
            }
        }
    }
    else
    {    
        listitem it = m_ValueList.find(szLabel);
        if(it != m_ValueList.end())           
            return it->second.c_str();
    }
    return "";
}

void SVParamItem::enumOS()
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

void SVParamItem::addNoSortList(string &szText, string &szLabel)
{
    int nSize = m_iValueList.RowCount();

    SVTableCell svcell;
    svcell.setType(adString);
    svcell.setValue(static_cast<const void*>(szLabel.c_str()));
    svcell.setProperty(szText.c_str());
    m_iValueList.WriteCell(nSize, 0, svcell);
}

const char* SVParamItem::getNoSortString()
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

void SVParamItem::setNoSortString(string &szValue)
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
