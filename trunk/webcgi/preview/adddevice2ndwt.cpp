#include <iostream>
#include "adddevice2nd.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVDevice::slots_[] = { WSlot_("showHelp()", false), WSlot_("TranslateNew()", false), WSlot_("ExChange()", false), WSlot_() };
WSignal_ SVDevice::signals_[] = { WSignal_() };

void SVDevice::buildSlotMap(WSlotMap& result)
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
void SVDevice::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool SVDevice::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    showHelp();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    TranslateNew();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ExChange();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVDevice::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
