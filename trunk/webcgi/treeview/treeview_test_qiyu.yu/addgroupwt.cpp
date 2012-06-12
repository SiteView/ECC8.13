#include <iostream>
#include "addgroup.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CEccGroupOperate::slots_[] = { WSlot_("SaveGroup()", false), WSlot_("Cancel()", false), WSlot_() };
WSignal_ CEccGroupOperate::signals_[] = { WSignal_() };

void CEccGroupOperate::buildSlotMap(WSlotMap& result)
{
  CEccBaseTable::buildSlotMap(result);
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
void CEccGroupOperate::buildSignalMap(WSignalMap& result)
{
  CEccBaseTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CEccGroupOperate::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    SaveGroup();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Cancel();
    return true;
  }
  return CEccBaseTable::triggerSlot(sender, slot, args);
}
bool CEccGroupOperate::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return CEccBaseTable::undoTriggerSlot(slot, args);
}
