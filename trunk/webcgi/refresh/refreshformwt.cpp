#include <iostream>
#include "refreshform.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVRefresh::slots_[] = { WSlot_("clearEnvironment()", false), WSlot_("showresult()", false), WSlot_("getresult()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_() };
WSignal_ SVRefresh::signals_[] = { WSignal_() };

void SVRefresh::buildSlotMap(WSlotMap& result)
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
void SVRefresh::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool SVRefresh::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    clearEnvironment();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showresult();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    getresult();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    ExChange();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVRefresh::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
