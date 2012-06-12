#include <iostream>
#include "mainview.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CEccMainView::slots_[] = { WSlot_("EccObjectClick()", false), WSlot_("EccMenuClick()", false), WSlot_("ConfirmDelete()", false), WSlot_("RefreshState()", false), WSlot_() };
WSignal_ CEccMainView::signals_[] = { WSignal_() };

void CEccMainView::buildSlotMap(WSlotMap& result)
{
  WTable::buildSlotMap(result);
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
void CEccMainView::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CEccMainView::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    EccObjectClick();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    EccMenuClick();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ConfirmDelete();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    RefreshState();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CEccMainView::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
