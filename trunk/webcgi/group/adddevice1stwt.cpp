#include <iostream>
#include "adddevice1st.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVDeviceList::slots_[] = { WSlot_("addDevice(const std::string)", false), WSlot_("cancel()", false), WSlot_("Translate()", false), WSlot_() };
WSignal_ SVDeviceList::signals_[] = { WSignal_("backPreview()", false), WSignal_("AddNewDevice(string)", false), WSignal_() };

void SVDeviceList::buildSlotMap(WSlotMap& result)
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
void SVDeviceList::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVDeviceList::backPreview()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void SVDeviceList::AddNewDevice(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

bool SVDeviceList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    addDevice(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    cancel();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Translate();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVDeviceList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
