#include <iostream>
#include "conditionparam.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVConditionParam::slots_[] = { WSlot_("showAddCondition()", false), WSlot_("hideAddCondition()", false), WSlot_("addCondition()", false), WSlot_() };
WSignal_ SVConditionParam::signals_[] = { WSignal_() };

void SVConditionParam::buildSlotMap(WSlotMap& result)
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
void SVConditionParam::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool SVConditionParam::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    showAddCondition();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    hideAddCondition();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    addCondition();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVConditionParam::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
