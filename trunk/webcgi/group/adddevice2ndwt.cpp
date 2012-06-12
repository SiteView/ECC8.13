#include <iostream>
#include "adddevice2nd.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVDevice::slots_[] = { WSlot_("Cancel()", false), WSlot_("Save()", false), WSlot_("Preview()", false), WSlot_("showHelp()", false), WSlot_("testDevice()", false), WSlot_("listDynParam()", false), WSlot_("listDynData()", false), WSlot_("enterDevice()", false), WSlot_("saveAllSelMonitors()", false), WSlot_("selAllByMonitorType(int)", false), WSlot_() };
WSignal_ SVDevice::signals_[] = { WSignal_("backMain()", false), WSignal_("backPreview()", false), WSignal_("AddDeviceSucc(string,string)", false), WSignal_("EditDeviceSucc(string,string)", false), WSignal_("EnterNewDevice(string)", false), WSignal_() };

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

void SVDevice::backMain()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void SVDevice::backPreview()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

void SVDevice::AddDeviceSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 2, args);
}

void SVDevice::EditDeviceSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 3, args);
}

void SVDevice::EnterNewDevice(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 4, args);
}

bool SVDevice::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Cancel();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Preview();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    showHelp();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    testDevice();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    listDynParam();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    listDynData();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    enterDevice();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    saveAllSelMonitors();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    selAllByMonitorType(*((int *)args[0]));
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVDevice::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
