#include <iostream>
#include "adddevice3rd.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CEccAddDevice3rd::slots_[] = { WSlot_("saveAllSelMonitors()", false), WSlot_("Cancel()", false), WSlot_("EnumDynData()", false), WSlot_("selAllByMonitorType(int)", false), WSlot_() };
WSignal_ CEccAddDevice3rd::signals_[] = { WSignal_() };

void CEccAddDevice3rd::buildSlotMap(WSlotMap& result)
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
void CEccAddDevice3rd::buildSignalMap(WSignalMap& result)
{
  CEccBaseTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CEccAddDevice3rd::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    saveAllSelMonitors();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Cancel();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    EnumDynData();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    selAllByMonitorType(*((int *)args[0]));
    return true;
  }
  return CEccBaseTable::triggerSlot(sender, slot, args);
}
bool CEccAddDevice3rd::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return CEccBaseTable::undoTriggerSlot(slot, args);
}
