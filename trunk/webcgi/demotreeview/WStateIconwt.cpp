#include <iostream>
#include "WStateIcon.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ WStateIcon::slots_[] = { WSlot_("showIcon1()", true), WSlot_("showIcon2()", true), WSlot_() };
WSignal_ WStateIcon::signals_[] = { WSignal_() };

void WStateIcon::buildSlotMap(WSlotMap& result)
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
void WStateIcon::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool WStateIcon::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    showIcon1();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showIcon2();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool WStateIcon::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    undoShowIcon1();
    return true;
  }
  if (slot == slots_ + 1) {
    undoShowIcon2();
    return true;
  }
  return WContainerWidget::undoTriggerSlot(slot, args);
}
