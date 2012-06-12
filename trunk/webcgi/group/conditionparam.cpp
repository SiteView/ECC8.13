#include "conditionparam.h"
#include "resstring.h"

extern void PrintDebugString(const string & szMsg);

extern bool SV_IsNumeric(string &szValue);

//string sv_condition_error_msg::m_szMatchingErr;
//string sv_condition_error_msg::m_szRelationErr;
//string sv_condition_error_msg::m_szTypeError;
//string sv_condition_error_msg::m_szConditionIsNull;

string sv_return_param_type::m_szFloat;
string sv_return_param_type::m_szInt;

typedef list<SVReturnItem*>::iterator ReturnItem;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    m_pConditionArea = NULL;

    m_bShowHelp = false;
    m_pOperate = NULL;

    m_nConditionType = nConditionType;
    loadCondition();
    initForm();
}

//const string SVConditionParam::GetStringValue()
//{
//    string szCondition ("");
//    if(m_pConditionArea)
//    {
//        szCondition = m_pConditionArea->text();
//    }
//    if(szCondition.empty())
//    {
//        showErrorMsg(sv_condition_is_null);
//    }
//    return szCondition;
//}
//
//void SVConditionParam::resetDefaultValue()
//{   
//    if(m_pConditionArea)
//    {
//        m_szDefaultValue = m_pConditionArea->text();
//    }
//    if(m_szDefaultValue.empty())
//    {
//        showErrorMsg(sv_condition_is_null);
//    }
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::SetCondition(MAPNODE &alertnode)
{
    string szRelationCount ("");

    if(m_pConditionArea)
        m_pConditionArea->setText("");

    FindNodeValue(alertnode, "sv_conditioncount", szRelationCount); 
    char szKey [16] = {0};
    string szCondition (""), szReturn (""), szParamValue ("") , szRelation ("");
    int nCount = 0;
    PrintDebugString("");
    if(!szRelationCount.empty())
    {
        nCount = atoi(szRelationCount.c_str());
        for(int i = 1; i <= nCount; i++)
        {
            szRelation = "";
            sprintf(szKey, "sv_relation%d", i);
            FindNodeValue(alertnode, szKey, szRelation);
            sprintf(szKey, "sv_paramname%d", i);
            FindNodeValue(alertnode, szKey, szReturn);
            sprintf(szKey, "sv_operate%d", i);
            FindNodeValue(alertnode, szKey, szCondition);
            sprintf(szKey, "sv_paramvalue%d", i);
            FindNodeValue(alertnode, szKey, szParamValue); 
            getParamLabel(szReturn);
            if(m_pConditionArea)
            {
                string szValue("");
                if(!szRelation.empty())
                    szValue = chLeftBracket + szReturn + " " + szCondition + " " + szParamValue + chRightBracket + " " + szRelation + " ";
                else
                    szValue = chLeftBracket + szReturn + " " + szCondition + " " + szParamValue + chRightBracket;

                m_pConditionArea->setText(m_pConditionArea->text() + szValue);
            }
        }
    }
}

bool SVConditionParam::checkCondition(MAPNODE &alertnode)
{
    bool bNoError = true;
    list<string> lstCondition;
    list<string> lstParam;
    list<string> lstOperate;

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
                    szParamValue = szParamCondition.substr(nPos + szCondition.length() + 1, szParamCondition.length() - 
                        (nPos + szCondition.length() + 1));
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
                szParamValue = szParamCondition.substr(nPos + szCondition.length() + 1, szParamCondition.length() - 
                    (nPos + szCondition.length() + 1));
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SVConditionParam::SaveCondition(MAPNODE &alertnode)
{
    bool bNoError = true;
    list<string> lstCondition;
    list<string> lstParam;
    list<string> lstOperate;

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
                sprintf(szKey, "sv_relation%d", nIndex);
                if((bNoError = AddNodeAttrib(alertnode, szKey, szConValue)))
                {
                    sprintf(szKey, "sv_paramname%d", nIndex);
                    if((bNoError = AddNodeAttrib(alertnode, szKey, szReturn)))
                    {
                        sprintf(szKey, "sv_operate%d", nIndex);
                        if((bNoError = AddNodeAttrib(alertnode, szKey, szCondition)))
                        {
                            sprintf(szKey, "sv_paramvalue%d", nIndex);
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
                sprintf(szKey, "sv_paramname%d", nIndex);
                if((bNoError = AddNodeAttrib(alertnode, szKey, szReturn)))
                {
                    sprintf(szKey, "sv_operate%d", nIndex);
                    if((bNoError = AddNodeAttrib(alertnode, szKey, szCondition)))
                    {
                        sprintf(szKey, "sv_paramvalue%d", nIndex);
                        if(bNoError = AddNodeAttrib(alertnode, szKey, szParamValue))
                        {
                            if(bNoError = AddNodeAttrib(alertnode, "sv_expression", szExpression))
                            {
                                sprintf(szCount, "%d", nCount + 1);
                                bNoError = AddNodeAttrib(alertnode, "sv_conditioncount", szCount);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createAddButton(int nRow)
{
    WText("  " , (WContainerWidget*) m_pOperate->elementAt(nRow, 1));
    WPushButton * pAdd = new WPushButton(SVResString::getResString("IDS_Add"), (WContainerWidget*) m_pOperate->elementAt(nRow, 1));
    if(pAdd)
    {
        pAdd->setToolTip(SVResString::getResString("IDS_Add_Title"));
        WObject::connect(pAdd, SIGNAL(clicked()), this, SLOT(addCondition()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createAddConidtion()
{
    int nRow = m_pOperate->numRows();
    new WText(SVResString::getResString("IDS_Condition"), (WContainerWidget*) m_pOperate->elementAt(nRow, 0));

    m_pReturnList = new WComboBox((WContainerWidget*) m_pOperate->elementAt(nRow, 1));    
    if(m_pReturnList)
    {
        list<SVReturnItem*>::iterator lsItem;

        for(lsItem = m_lsReturn.begin(); lsItem != m_lsReturn.end(); lsItem++)
            m_pReturnList->addItem((*lsItem)->getLabel());
    }

    new WText("<P>", (WContainerWidget*)elementAt(nRow, 1));
    m_pOperateList = new WComboBox((WContainerWidget*) m_pOperate->elementAt(nRow, 1));
    if(m_pOperateList)
    {
        list<string>::iterator lsItem;

        for(lsItem = m_lsCondition.begin(); lsItem != m_lsCondition.end(); lsItem++)
            m_pOperateList->addItem((*lsItem));
    }

    new WText("<P>", (WContainerWidget*)elementAt(nRow, 1));
    m_pParam = new WLineEdit("", (WContainerWidget*) m_pOperate->elementAt(nRow, 1));

    createAddButton(nRow);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createButtonGroup()
{
    int nRow = m_pOperate->numRows();

    new WText(SVResString::getResString("IDS_Relation"), (WContainerWidget*)m_pOperate->elementAt(nRow, 0));

    m_pConditionGroup = new WButtonGroup();

    m_pConditionAND = new WRadioButton(SVResString::getResString("IDS_And"), (WContainerWidget*)m_pOperate->elementAt(nRow, 1));
    if(m_pConditionAND && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pConditionAND);
        m_pConditionAND->setChecked();
    }

    new WText("<P>", (WContainerWidget*)elementAt(nRow, 0));
    m_pConditionOR = new WRadioButton(SVResString::getResString("IDS_Or"), (WContainerWidget*)m_pOperate->elementAt(nRow, 1));
    if(m_pConditionOR && m_pConditionGroup)
    {
        m_pConditionGroup->addButton(m_pConditionOR);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createCondition()
{
    int nRow = numRows();
    m_pLabel = new WText(m_szLabel, (WContainerWidget*)elementAt(nRow, 0));
    elementAt(nRow, 0)->setContentAlignment(AlignTop | AlignLeft);
    elementAt(nRow, 0)->setStyleClass("cell_10");

    string szValue ("");
    if(!m_szDefaultValue.empty())
        szValue = chLeftBracket + m_szDefaultValue + chRightBracket;

    m_pConditionArea = new WTextArea(szValue, (WContainerWidget*)elementAt(nRow, 1));
    if(m_pConditionArea)
    {
        //if(strcmp(m_szDefaultValue.substr(0, 1).c_str(), &chLeftBracket) == 0 )
        //    m_pConditionArea->setText(m_szDefaultValue);
        m_pConditionArea->setStyleClass(m_szStyle);
    }

    createShowButton(nRow);
    createHelp(nRow);

    m_pOperate = new WTable((WContainerWidget*)elementAt(nRow,1));
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createHideButton()
{
    int nRow = m_pOperate->numRows();

    WImage  * pClose = new WImage("../icons/closewnd.gif", (WContainerWidget*)m_pOperate->elementAt(nRow,1));
    m_pOperate->elementAt(nRow, 1)->setContentAlignment(AlignTop | AlignRight);
    if(pClose)
    {
        pClose->setStyleClass("imgbutton");
        WObject::connect(pClose, SIGNAL(clicked()), this, SLOT(hideAddCondition()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createShowButton(int nRow)
{
    WImage * pSet = new WImage("../icons/set.gif", (WContainerWidget*)elementAt(nRow,1));
    if(pSet)
    {
        pSet->setStyleClass("imgbutton");
        WObject::connect(pSet, SIGNAL(clicked()), this, SLOT(showAddCondition()));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::SetReturnList(list<SVReturnItem*>  &lsReturn)
{
    m_lsReturn.clear();
    list<SVReturnItem*>::iterator lsItem;
    for(lsItem = lsReturn.begin(); lsItem != lsReturn.end(); lsItem++)
        m_lsReturn.push_back((*lsItem));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::EnumParam(MAPNODE &mapnode)
{
    FindNodeValue(mapnode, "sv_name", m_szName);                    // 名称

    if(FindNodeValue(mapnode, "sv_label", m_szLabel))               // 标签
        m_szLabel = SVResString::getResString(m_szLabel.c_str());

    if(FindNodeValue(mapnode, "sv_tip", m_szTip))                   // 提示
        m_szTip = SVResString::getResString(m_szTip.c_str());

    if(FindNodeValue(mapnode, "sv_helptext", m_szHelp))             // 帮助
        m_szHelp = SVResString::getResString(m_szHelp.c_str());

    FindNodeValue(mapnode, "sv_style", m_szStyle);
    FindNodeValue(mapnode, "sv_value", m_szDefaultValue);           // 缺省值
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::SetMapNode(MAPNODE &mapnode)
{
    setStyleClass("t3");
    EnumParam(mapnode);
    setDefaultValue();

    SetCondition(mapnode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::showAddCondition()
{   
    if(m_pOperate)
        m_pOperate->show();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::hideAddCondition()
{
    if(m_pOperate)
        m_pOperate->hide();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::addCondition()
{
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::initForm()
{

//    loadString();
    createCondition();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::showHelp(bool bShowHelp)
{
    m_bShowHelp = bShowHelp;
    if(m_pHelpText)
    {
        m_pHelpText->setStyleClass("helps");
        m_pHelpText->setText(m_szHelp);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::createHelp(int nRow)
{
    WText("<BR>", (WContainerWidget*)elementAt(nRow, 1));
    m_pHelpText = new WText(m_szHelp, (WContainerWidget*)elementAt(nRow, 1));
    if(m_pHelpText)
    {
        m_pHelpText->setStyleClass("helps");
        m_pHelpText->hide();
    }
    WText("<BR>", (WContainerWidget*)elementAt(nRow, 1));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SVConditionParam::loadString()
//{
//	//Resource
//	OBJECT objRes=LoadResource("default", "localhost");  
//	if( objRes !=INVALID_VALUE )
//	{	
//		MAPNODE ResNode=GetResourceNode(objRes);
//		if( ResNode != INVALID_VALUE )
//		{
//			FindNodeValue(ResNode,"IDS_Add",m_szAdd);
//			FindNodeValue(ResNode,"IDS_Add_Title",m_szAddTip);
//			FindNodeValue(ResNode,"IDS_Or",m_szOr);
//			FindNodeValue(ResNode,"IDS_And",m_szAnd);
//			FindNodeValue(ResNode,"IDS_Condition",m_szSet);
//			FindNodeValue(ResNode,"IDS_Relation",m_szCondition);
//		}
//		CloseResource(objRes);
//	}
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVConditionParam::showErrorMsg(int nErrorCode)
{
    if(m_pHelpText)
    {
        switch(nErrorCode)
        {
        case sv_condition_is_null:
            m_pHelpText->setText(SVResString::getResString("IDS_Alert_Condition_NULL"));
            break;
        case sv_condition_relation_error:
            m_pHelpText->setText(SVResString::getResString("IDS_Alert_Condition_Relation_Error"));
            break;
        case sv_condition_matching_error:
            m_pHelpText->setText(SVResString::getResString("IDS_Alert_Condition_Return_Param_Error"));
            break;
        case sv_condition_type_error:
            m_pHelpText->setText(SVResString::getResString("IDS_Alert_Condition_Param_Error"));
            break;
        }
        m_pHelpText->setStyleClass("errors");
        m_pHelpText->show();
    }
}

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

void SVConditionParam::setDefaultValue()
{
    showHelp(false);
    if(m_pParam)
        m_pParam->setText("");

    if(m_pLabel)
        m_pLabel->setText(m_szLabel);

    if(m_pConditionArea)
    {
        m_pConditionArea->setStyleClass(m_szStyle);
        
        //string szValue = chLeftBracket + m_szDefaultValue + chRightBracket;
        //int nPos = static_cast<int>(m_szDefaultValue.find(chLeftBracket));
        //
        //if(nPos >= 0)
        //    m_pConditionArea->setText(m_szDefaultValue);
        //else
        //    m_pConditionArea->setText(szValue);
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
