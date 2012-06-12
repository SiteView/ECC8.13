#include <iostream>
#include "adddevice2nd.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CEccAddDevice2nd::slots_[] = { WSlot_("Forward()", false), WSlot_("SaveDevice()", false), WSlot_("Cancel()", false), WSlot_("TestDevice()", false), WSlot_("EnumDynData()", false), WSlot_() };
WSignal_ CEccAddDevice2nd::signals_[] = { WSignal_() };

void CEccAddDevice2nd::buildSlotMap(WSlotMap& result)
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
void CEccAddDevice2nd::buildSignalMap(WSignalMap& result)
{
  CEccBaseTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CEccAddDevice2nd::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Forward();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    SaveDevice();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Cancel();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    TestDevice();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    EnumDynData();
    return true;
  }
  return CEccBaseTable::triggerSlot(sender, slot, args);
}
bool CEccAddDevice2nd::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return CEccBaseTable::undoTriggerSlot(slot, args);
}
