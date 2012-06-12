#include "pushbutton.h"

#include "../../opens/libwt/WText"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WTableCell"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccButton::CEccButton(string szText, string szToolTip, string szImgPath, WContainerWidget *parent):
WTable(parent)
{
    setStyleClass("button_img_font");

   	new WImage("../Images/space.gif", elementAt(0, 0));
	elementAt(0, 0)->setStyleClass("but_img_bg_l_blue");
    strcpy(elementAt(0, 0)->contextmenu_, "nowrap");

	if(!szImgPath.empty())
        new WImage(szImgPath, elementAt(0, 1));
    else
        new WImage("../Images/button_bg_m.png", elementAt(0, 1));

	m_pButton = new WText(szText, elementAt(0, 2));
	elementAt(0, 2)->setStyleClass("but_img_bg_m_blue");
    strcpy(elementAt(0, 2)->contextmenu_, "nowrap");

    if(m_pButton)
    {
        m_pButton->setStyleClass("button_img_font");
	    if(!szToolTip.empty())
		    m_pButton->setToolTip(szToolTip);
    }

	new WImage("../Images/space.gif", elementAt(0, 3));
	elementAt(0, 3)->setStyleClass("but_img_bg_r_blue");
    strcpy(elementAt(0, 3)->contextmenu_, "nowrap");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置显示文字
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccButton::setText(string szText)
{
    if(m_pButton)
        m_pButton->setText(szText);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置提示信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccButton::setToolTip(const std::string text)
{
    if(m_pButton)
        m_pButton->setToolTip(text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 必要按钮构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccImportButton::CEccImportButton(string szText, string szToolTip, string szImgPath, WContainerWidget *parent):
WTable(parent)
{
    setStyleClass("button_img_font");

   	new WImage("../Images/space.gif", elementAt(0, 0));
	elementAt(0, 0)->setStyleClass("but_img_bg_l_black");
    strcpy(elementAt(0, 0)->contextmenu_, "nowrap");

	if(!szImgPath.empty())
        new WImage(szImgPath, elementAt(0, 1));
    else
        new WImage("../Images/button_bg_m_black.png", elementAt(0, 1));

	m_pButton = new WText(szText, elementAt(0, 2));
	elementAt(0, 2)->setStyleClass("but_img_bg_m_black");
    strcpy(elementAt(0, 3)->contextmenu_, "nowrap");

    if(m_pButton)
    {
        m_pButton->setStyleClass("button_img_font");
	    if(!szToolTip.empty())
		    m_pButton->setToolTip(szToolTip);
    }

	new WImage("../Images/space.gif", elementAt(0, 3));
	elementAt(0, 3)->setStyleClass("but_img_bg_r_black");
    strcpy(elementAt(0, 3)->contextmenu_, "nowrap");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置显示文本
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccImportButton::setText(string szText)
{
    if(m_pButton)
        m_pButton->setText(szText);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置提示文本
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccImportButton::setToolTip(const std::string text)
{
    if(m_pButton)
        m_pButton->setToolTip(text);
}
