#include <iostream>
#include "advanceparam.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CEccAdvanceTable::slots_[] = { WSlot_("showDepend()", false), WSlot_("changePath()", false), WSlot_("ShowHideSub()", false), WSlot_() };
WSignal_ CEccAdvanceTable::signals_[] = { WSignal_() };

void CEccAdvanceTable::buildSlotMap(WSlotMap& result)
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
void CEccAdvanceTable::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CEccAdvanceTable::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    showDepend();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    changePath();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ShowHideSub();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CEccAdvanceTable::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
