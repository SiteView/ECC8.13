#include "conditionparam.h"
#include "resstring.h"
#include "basedefine.h"
#include "debuginfor.h"
#include "pushbutton.h"

extern bool SV_IsNumeric(string &szValue);

string sv_return_param_type::m_szFloat;
string sv_return_param_type::m_szInt;

typedef list<SVReturnItem*>::iterator ReturnItem;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVConditionParam::SVConditionParam(WContainerWidget *parent,int nConditionType):
WTable(parent)
{
    m_pReturnList = NULL;
    m_pOperateList = NULL;
    m_pParam = NULL;
    m_pLabel = NULL;
    m_pConditionGroup = NULL;
    m_pConditionOR = NULL;
    m_pConditionAND = NULL;

    m_pHelpText = NULL;
    m_pErrText = NULL;
    m_pConditionArea = NULL;

    m_bShowHelp = false;
    m_pOperate = NULL;

    m_nConditionType = nConditionType;
    loadCondition();
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::SetCondition(MAPNODE &alertnode)
{
    string szRelationCount ("");

    // �����ı��ÿ�
    if(m_pConditionArea)
        m_pConditionArea->setText("");

    // ���ð����ı�
    if(m_pHelpText)
        m_pHelpText->setText(m_szHelp);

    // ���ô�����ʾ��Ϣ
    if(m_pErrText)
        m_pErrText->setText(m_szTip);

    // �õ�����
    FindNodeValue(alertnode, svConditionCount, szRelationCount); 
    char szKey [16] = {0};
    string szCondition (""), szReturn (""), szParamValue ("") , szRelation ("");
    int nCount = 0;

    // չʾ����
    if(!szRelationCount.empty())
    {
        nCount = atoi(szRelationCount.c_str());
        for(int i = 1; i <= nCount; i++)
        {
            szRelation = "";
            sprintf(szKey, svRelation, i);
            FindNodeValue(alertnode, szKey, szRelation);
            sprintf(szKey, svParamName, i);
            FindNodeValue(alertnode, szKey, szReturn);
            sprintf(szKey, svOperate, i);
            FindNodeValue(alertnode, szKey, szCondition);
            sprintf(szKey, svParamValue, i);
            FindNodeValue(alertnode, szKey, szParamValue); 
            getParamLabel(szReturn);
            if(m_pConditionArea)
            {
                string szValue("");
                if(!szRelation.empty())
                    szValue = chLeftBracket + szReturn + " " + szCondition + " " + szParamValue + chRightBracket
                    + " " + szRelation + " ";
                else
                    szValue = chLeftBracket + szReturn + " " + szCondition + " " + szParamValue + chRightBracket;

                m_pConditionArea->setText(m_pConditionArea->text() + szValue);
            }
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// У�鵱ǰ��д������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVConditionParam::checkCondition(MAPNODE &alertnode)
{
    bool bNoError = true;
    list<string> lstCondition;
    list<string> lstParam;
    list<string> lstOperate;

    if(m_pErrText)
        m_pErrText->hide();

    string szValue = m_pConditionArea->text();

    if(!szValue.empty())
    {
        unsigned int nResult = getCondition(lstCondition, szValue);
        nResult = getParam(lstParam, szValue);

        if(lstCondition.size() != lstParam.size() - 1)
        {
            bNoError = false;
            showErrorMsg(sv_condition_relation_error);
            return bNoError;
        }

        char szCount[4] = {0}, szKey [32] = {0};
        int nCount = static_cast<int>(lstCondition.size());
        int nIndex = 1;
        string szExpression ("");
        if(nCount >= 1)
        {
            while(lstCondition.size())
            {
                string szConValue = *(lstCondition.begin());
                lstCondition.pop_front();

                string szParamCondition = *(lstParam.begin());
                lstParam.pop_front();
                string szCondition (""), szReturn (""), szParamValue ("");
                int nPos = getOperatePostion(szParamCondition, m_lsCondition, szCondition);

                if(nPos > 0 && !szCondition.empty())
                {
                    szReturn = szParamCondition.substr(0, nPos - 1);
                    szParamValue = szParamCondition.substr(nPos + szCondition.length() + 1, 
                        szParamCondition.length() - (nPos + szCondition.length() + 1));
                    if(! checkParamValue(szReturn, szParamValue))
                    {
                        bNoError = false;
                        break;
                    }
                }
                else
                {
                    showErrorMsg(sv_condition_relation_error);
                    bNoError = false;
                }
                nIndex ++;
            }
        }
        if(bNoError)
        {
            string szParamCondition = *(lstParam.begin());
            lstParam.pop_front();
            string szCondition (""), szReturn (""), szParamValue ("");
            int nPos = getOperatePostion(szParamCondition, m_lsCondition, szCondition);

            if(nPos > 0 && !szCondition.empty())
            {
                szReturn = szParamCondition.substr(0, nPos - 1);
                szParamValue = szParamCondition.substr(nPos + szCondition.length() + 1, 
                    szParamCondition.length() - (nPos + szCondition.length() + 1));
                bNoError = checkParamValue(szReturn, szParamValue);
            }
            else
            {
                showErrorMsg(sv_condition_relation_error);
                bNoError = false;
            } 
        }
    }
    else
    {
        showErrorMsg(sv_condition_is_null);
        bNoError = false;
    }
    if(bNoError)
    {
        showHelp(m_bShowHelp);
    }
    return bNoError ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���浱ǰ��д����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVConditionParam::SaveCondition(MAPNODE &alertnode)
{
    bool bNoError = true;
    list<string> lstCondition;
    list<string> lstParam;
    list<string> lstOperate;

    if(m_pErrText)
        m_pErrText->hide();

    string szValue = m_pConditionArea->text();

    if(!szValue.empty())
    {
        unsigned int nResult = getCondition(lstCondition, szValue);
        nResult = getParam(lstParam, szValue);

        if(lstCondition.size() != lstParam.size() - 1)
        {
            bNoError = false;
            showErrorMsg(sv_condition_relation_error);
            return bNoError;
        }

        char szCount[4] = {0}, szKey [32] = {0};
        int nCount = static_cast<int>(lstCondition.size());
        int nIndex = 1;
        string szExpression ("");
        if(nCount >= 1)
        {
            while(lstCondition.size())
            {
                string szConValue = *(lstCondition.begin());
                lstCondition.pop_front();

                string szParamCondition = *(lstParam.begin());
                lstParam.pop_front();
                string szCondition (""), szReturn (""), szParamValue ("");
                int nPos = getOperatePostion(szParamCondition, m_lsCondition, szCondition);

                if(nPos > 0)
                {
                    szReturn = szParamCondition.substr(0, nPos - 1);
                    szParamValue = szParamCondition.substr(nPos + szCondition.length() + 1, szParamCondition.length() - 
                        (nPos + szCondition.length() + 1));
                }

                if(! checkParamValue(szReturn, szParamValue))
                {
                    bNoError = false;
                    break;
                }
                sprintf(szKey, "%d", nIndex);
                szExpression = szExpression + szKey + "#" + szConValue + "#";
                sprintf(szKey, svRelation, nIndex);
                if((bNoError = AddNodeAttrib(alertnode, szKey, szConValue)))
                {
                    sprintf(szKey, svParamName, nIndex);
                    if((bNoError = AddNodeAttrib(alertnode, szKey, szReturn)))
                    {
                        sprintf(szKey, svOperate, nIndex);
                        if((bNoError = AddNodeAttrib(alertnode, szKey, szCondition)))
                        {
                            sprintf(szKey, svParamValue, nIndex);
                            bNoError = AddNodeAttrib(alertnode, szKey, szParamValue);
                        }
                    }
                }
                if(!bNoError)
                    break;
                nIndex ++;
            }
        }
        if(bNoError)
        {
            string szParamCondition = *(lstParam.begin());
            lstParam.pop_front();
            string szCondition (""), szReturn (""), szParamValue ("");
            int nPos = getOperatePostion(szParamCondition, m_lsCondition, szCondition);

            if(nPos > 0)
            {
                szReturn = szParamCondition.substr(0, nPos - 1);
                szParamValue = szParamCondition.substr(nPos + szCondition.length() + 1, szParamCondition.length() - 
                    (nPos + szCondition.length() + 1));
            }

            if(!checkParamValue(szReturn, szParamValue))
            {
                bNoError = false;
            }
            if(bNoError)
            {
                sprintf(szKey, "%d", nIndex);
                szExpression = szExpression + szKey;
                sprintf(szKey, svParamName, nIndex);
                if((bNoError = AddNodeAttrib(alertnode, szKey, szReturn)))
                {
                    sprintf(szKey, svOperate, nIndex);
                    if((bNoError = AddNodeAttrib(alertnode, szKey, szCondition)))
                    {
                        sprintf(szKey, svParamValue, nIndex);
                        if(bNoError = AddNodeAttrib(alertnode, szKey, szParamValue))
                        {
                            if(bNoError = AddNodeAttrib(alertnode, svExpression, szExpression))
                            {
                                sprintf(szCount, "%d", nCount + 1);
                                bNoError = AddNodeAttrib(alertnode, svConditionCount, szCount);
                            }
                        }
                    }
                }
            }     
        }
    }
    else
    {
        showErrorMsg(sv_condition_is_null);
        bNoError = false;
    }
    return bNoError ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������Ӱ�ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createAddButton(int nRow)
{
    WTable *pSub = new WTable(m_pOperate->elementAt(nRow, 1));
    if(pSub)
    {
        pSub->setStyleClass("widthauto");
        new WText(SVResString::getResString("IDS_Condition"), m_pOperate->elementAt(nRow, 0));

        m_pReturnList = new WComboBox(pSub->elementAt(0, 0));    
        if(m_pReturnList)
        {
            m_pReturnList->setStyleClass("cell_condition");
            list<SVReturnItem*>::iterator lsItem;

            for(lsItem = m_lsReturn.begin(); lsItem != m_lsReturn.end(); lsItem++)
                m_pReturnList->addItem((*lsItem)->getLabel());
        }

        new WText("&nbsp;", pSub->elementAt(0, 1));
        m_pOperateList = new WComboBox(pSub->elementAt(0, 2));
        if(m_pOperateList)
        {
            m_pOperateList->setStyleClass("cell_condition");
            list<string>::iterator lsItem;

            for(lsItem = m_lsCondition.begin(); lsItem != m_lsCondition.end(); lsItem++)
                m_pOperateList->addItem((*lsItem));
        }

        new WText("&nbsp;", pSub->elementAt(0, 3));
        m_pParam = new WLineEdit("", pSub->elementAt(0, 4));
        if(m_pParam)
            m_pParam->setStyleClass("cell_condition");

        new WText("&nbsp;", pSub->elementAt(0, 5));
        CEccButton * pAdd = new CEccButton(SVResString::getResString("IDS_Add"), SVResString::getResString("IDS_Add_Title"),
            "", pSub->elementAt(0, 6));
        if(pAdd)
        {
            WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(addCondition()));
        }
     }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����������ݱ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createAddConidtion()
{
    int nRow = m_pOperate->numRows();
    createAddButton(nRow);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ť��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createButtonGroup()
{
    int nRow = m_pOperate->numRows();

    new WText(SVResString::getResString("IDS_Relation"), m_pOperate->elementAt(nRow, 0));

    // �µİ�ť��
    m_pConditionGroup = new WButtonGroup();

    // ��
    m_pConditionAND = new WRadioButton(SVResString::getResString("IDS_And"), m_pOperate->elementAt(nRow, 1));
    if(m_pConditionAND && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pConditionAND);
        m_pConditionAND->setChecked();
    }

    // ��
    new WText("&nbsp;", m_pOperate->elementAt(nRow, 1));
    m_pConditionOR = new WRadioButton(SVResString::getResString("IDS_Or"), m_pOperate->elementAt(nRow, 1));
    if(m_pConditionOR && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pConditionOR);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createCondition()
{
    int nRow = numRows();
     m_pLabel = new WText(m_szLabel, elementAt(nRow, 0));

    elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    elementAt(nRow, 0)->setStyleClass("table_list_data_input_text");
    GetRow(nRow)->setStyleClass("padding_top");

    string szValue ("");
    if(!m_szDefaultValue.empty())
        szValue = chLeftBracket + m_szDefaultValue + chRightBracket;

    m_pConditionArea = new WTextArea(szValue, elementAt(nRow, 1));

    if(m_pConditionArea)
        m_pConditionArea->setStyleClass(m_szStyle);

    elementAt(nRow, 1)->setStyleClass("table_data_text");

    createShowButton(nRow);
    createHelp(nRow);
    m_pOperate = new WTable(elementAt(nRow,1));
    if(m_pOperate)
    {
        m_pOperate->setStyleClass("conditionset");
        createHideButton();
        createAddConidtion();
        createButtonGroup();
        m_pOperate->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������ذ�ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createHideButton()
{
    int nRow = m_pOperate->numRows();

    WImage  * pClose = new WImage("../Images/tocHide.gif", m_pOperate->elementAt(nRow,1));
    m_pOperate->elementAt(nRow, 1)->setContentAlignment(AlignTop | AlignRight);
    if(pClose)
    {
        pClose->setStyleClass("hand");
        WObject::connect(pClose, SIGNAL(clicked()), this, SLOT(hideAddCondition()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ʾ׷������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createShowButton(int nRow)
{
    WImage * pSet = new WImage("../Images/more.gif", elementAt(nRow,1));
    if(pSet)
    {
        pSet->setStyleClass("hand");
        WObject::connect(pSet, SIGNAL(clicked()), this, SLOT(showAddCondition()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���÷���ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::SetReturnList(list<SVReturnItem*>  &lsReturn)
{
    m_lsReturn.clear();
    list<SVReturnItem*>::iterator lsItem;
    for(lsItem = lsReturn.begin(); lsItem != lsReturn.end(); lsItem++)
        m_lsReturn.push_back((*lsItem));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������ӷ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::loadCondition()
{
    m_lsCondition.push_back("==");
    m_lsCondition.push_back("!=");
    m_lsCondition.push_back(">");
    m_lsCondition.push_back(">=");
    m_lsCondition.push_back("<");
    m_lsCondition.push_back("<=");
    m_lsCondition.push_back("contains");
    m_lsCondition.push_back("!contains");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ö�ٲ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::EnumParam(MAPNODE &mapnode)
{
    FindNodeValue(mapnode, svName, m_szName);                    // ����

    if(FindNodeValue(mapnode, svLabel, m_szLabel))               // ��ǩ
        m_szLabel = SVResString::getResString(m_szLabel.c_str());

    if(FindNodeValue(mapnode, svTip, m_szTip))                   // ��ʾ
        m_szTip = SVResString::getResString(m_szTip.c_str());

    if(FindNodeValue(mapnode, svHelpText, m_szHelp))             // ����
        m_szHelp = SVResString::getResString(m_szHelp.c_str());

    FindNodeValue(mapnode, svStyle, m_szStyle);
    FindNodeValue(mapnode, svValue, m_szDefaultValue);           // ȱʡֵ
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ýڵ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::SetMapNode(MAPNODE &mapnode)
{
    EnumParam(mapnode);

    setDefaultValue();

    SetCondition(mapnode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::showAddCondition()
{   
    if(m_pOperate)
        m_pOperate->show();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::hideAddCondition()
{
    if(m_pOperate)
        m_pOperate->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::addCondition()
{
    if(m_pErrText)
        m_pErrText->hide();

    string szParam = m_pParam->text();
    if(szParam.empty())
        return;
    string szReturn = m_pReturnList->currentText();
    string szOperate = m_pOperateList->currentText();
    string szTemp = szReturn;
    if(!checkParamValue(szTemp, szParam))
        return;

    string szCondition ("");
    if(m_pConditionAND)
    {
        if(m_pConditionAND->isChecked())
            szCondition = " and ";
        else 
            szCondition = " or ";
    }

    if(m_pConditionArea)
    {
        string szValue = m_pConditionArea->text();
        if (szValue.empty())
            szValue = chLeftBracket + szReturn + " " + szOperate + " " + szParam + chRightBracket;
        else
            szValue = szValue + szCondition + chLeftBracket + szReturn + " " + szOperate + " " + szParam + chRightBracket;
        m_pConditionArea->setText(szValue);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::initForm()
{
    createCondition();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::showHelp(bool bShowHelp)
{
    m_bShowHelp = bShowHelp;
    if(m_pHelpText)
    {
        if(bShowHelp )
        {  
            m_pHelpText->show();
        }
        else
        {
            m_pHelpText->hide();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createHelp(int nRow)
{
    if(!m_pHelpText)
        m_pHelpText = new WText(m_szHelp, elementAt(nRow + 1, 1));
    if(m_pHelpText)
    {
        elementAt(nRow  + 1, 1)->setStyleClass("table_data_input_des");
        m_pHelpText->hide();
    }
    
    if(!m_pErrText)
        m_pErrText = new WText(m_szTip, elementAt(nRow + 2, 1));
    if(m_pErrText)
    {
        elementAt(nRow + 2, 1)->setStyleClass("table_data_input_error");
        m_pErrText->hide();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ������Ϣ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::showErrorMsg(int nErrorCode)
{
    if(m_pErrText)
    {
        switch(nErrorCode)
        {
        case sv_condition_is_null:
            m_pErrText->setText(SVResString::getResString("IDS_Alert_Condition_NULL"));
            break;
        case sv_condition_relation_error:
            m_pErrText->setText(SVResString::getResString("IDS_Alert_Condition_Relation_Error"));
            break;
        case sv_condition_matching_error:
            m_pErrText->setText(SVResString::getResString("IDS_Alert_Condition_Return_Param_Error"));
            break;
        case sv_condition_type_error:
            m_pErrText->setText(SVResString::getResString("IDS_Alert_Condition_Param_Error"));
            break;
        }
        m_pErrText->show();
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ָ��������ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVConditionParam::checkParamValue(string &szParam, string &szParamValue)
{
    bool bNoError = false;
    if(szParam.empty() || szParamValue.empty())
    {
        showErrorMsg(sv_condition_type_error);
        return false;
    }
    ReturnItem rtItem;
    for(rtItem = m_lsReturn.begin(); rtItem != m_lsReturn.end(); rtItem ++)
    {
        if((*rtItem)->getLabel() == szParam)
        {
            szParam = (*rtItem)->getName();
            if((*rtItem)->isNumeric())
            {
                if(SV_IsNumeric(szParamValue))
                    bNoError = true;
                else
                    showErrorMsg(sv_condition_type_error);
            }
            else
                bNoError = true;
            break;
        }
    }
    return bNoError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �õ���������ʾ�ı�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::getParamLabel(string &szName)
{
    ReturnItem rtItem;
    for(rtItem = m_lsReturn.begin(); rtItem != m_lsReturn.end(); rtItem ++)
    {
        if((*rtItem)->getName() == szName)
        {
            szName = (*rtItem)->getLabel();
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����Ϊȱʡֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::setDefaultValue()
{
    //showHelp(false);
    if(m_pParam)
        m_pParam->setText("");

    if(m_pLabel)
        m_pLabel->setText(m_szLabel);

    if(m_pConditionArea)
    {
        m_pConditionArea->setStyleClass(m_szStyle);
    }

    if(m_pReturnList)
    {
        m_pReturnList->clear();
        list<SVReturnItem*>::iterator lsItem;

        for(lsItem = m_lsReturn.begin(); lsItem != m_lsReturn.end(); lsItem++)
            m_pReturnList->addItem((*lsItem)->getLabel());

        m_pReturnList->setCurrentIndex(0);
    }

    if(m_pOperateList)
        m_pOperateList->setCurrentIndex(0);

    if(m_pOperate)
        m_pOperate->hide();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file
