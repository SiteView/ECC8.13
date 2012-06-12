#include <iostream>
#include "devicelist.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVEnumDevice::slots_[] = { WSlot_("selAll()", false), WSlot_("selNone()", false), WSlot_("invertSel()", false), WSlot_("delSel()", false), WSlot_("add()", false), WSlot_("editDevice()", false), WSlot_("gotoDevice()", false), WSlot_("changeState()", false), WSlot_("DelSelDevice()", false), WSlot_("testDevice()", false), WSlot_("deleteDevice()", false), WSlot_("enableSelDevice()", false), WSlot_("disableSelDevice()", false), WSlot_("disableDeviceSucc()", false), WSlot_("sortDevices()", false), WSlot_("CopyDevice()", false), WSlot_("PastDevice()", false), WSlot_() };
WSignal_ SVEnumDevice::signals_[] = { WSignal_("AddNewDevice()", false), WSignal_("EditDeviceByID(string)", false), WSignal_("EnterDeviceByID(string)", false), WSignal_("sortDevicesList(int)", false), WSignal_("UpdateDeviceState(string,int)", false), WSignal_("CopyDeviceSucc(string,string)", false), WSignal_("DeleteDeviceSucc(string,string)", false), WSignal_() };

void SVEnumDevice::buildSlotMap(WSlotMap& result)
{
  WContainerWidget::buildSlotMap(result);
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
void SVEnumDevice::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVEnumDevice::AddNewDevice()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void SVEnumDevice::EditDeviceByID(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

void SVEnumDevice::EnterDeviceByID(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 2, args);
}

void SVEnumDevice::sortDevicesList(int arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 3, args);
}

void SVEnumDevice::UpdateDeviceState(string arg0,int arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 4, args);
}

void SVEnumDevice::CopyDeviceSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 5, args);
}

void SVEnumDevice::DeleteDeviceSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 6, args);
}

bool SVEnumDevice::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    selAll();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    selNone();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    invertSel();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    delSel();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    add();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    editDevice();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    gotoDevice();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    changeState();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    DelSelDevice();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    testDevice();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    deleteDevice();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    enableSelDevice();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    disableSelDevice();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    disableDeviceSucc();
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    sortDevices();
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    CopyDevice();
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    PastDevice();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool SVEnumDevice::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
