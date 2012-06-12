
#include "statedesc.h"
#include "resstring.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccStateDesc::CEccStateDesc(WContainerWidget *parent):
WTable(parent)
{
    initForm();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccStateDesc::initForm()
{
    new WText(SVResString::getResString("IDS_State_Description") + ":&nbsp;", elementAt(0, 0));
    
    new WImage("../Images/state_grey.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_NO_Date") + ";&nbsp;", elementAt(0, 0));

    new WImage("../Images/state_green.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Normal") + ";&nbsp;", elementAt(0, 0));

    new WImage("../Images/state_yellow.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Warnning") + ";&nbsp;", elementAt(0, 0));

    new WImage("../Images/state_red.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Error") + ";&nbsp;", elementAt(0, 0));

    new WImage("../Images/state_stop.gif", elementAt(0, 0));
    new WText( SVResString::getResString("IDS_Disable"), elementAt(0, 0));

}
