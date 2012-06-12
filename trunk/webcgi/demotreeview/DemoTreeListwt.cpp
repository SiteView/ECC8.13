#include <iostream>
#include "DemoTreeList.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ DemoTreeList::slots_[] = { WSlot_("SelNode()", false), WSlot_("RunMenu()", false), WSlot_("MenuItemResponseProc(MENU_RESPONSE)", false), WSlot_("changeSelNode(string)", false), WSlot_("delConfirm()", false), WSlot_("InPhaseView()", false), WSlot_("ExChangeRefresh()", false), WSlot_() };
WSignal_ DemoTreeList::signals_[] = { WSignal_("MenuItemRequest(MENU_REQUEST)", true), WSignal_() };

void DemoTreeList::buildSlotMap(WSlotMap& result)
{
  WContainerWidget::buildSlotMap(result);
  for (int i = 0; slots_[i].good(); ++i)  {
#ifdef WIN32 
	WSlotInstance_ *pw=new WSlotInstance_(this, slots_ + i);	
		std::string strkey=slots_[i].name();	
		WObject::InsertMap(result,strkey,pw);	
#else  
	result[slots_[i].name()] = new WSlotInstance_(this, slots_ + i);
#endif  
	}
}
void DemoTreeList::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void DemoTreeList::MenuItemRequest(MENU_REQUEST arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

bool DemoTreeList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    SelNode();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    RunMenu();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    MenuItemResponseProc(*((MENU_RESPONSE *)args[0]));
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    changeSelNode(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    delConfirm();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    InPhaseView();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    ExChangeRefresh();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool DemoTreeList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
