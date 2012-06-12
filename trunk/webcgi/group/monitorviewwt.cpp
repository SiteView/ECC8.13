#include <iostream>
#include "monitorview.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVMonitorview::slots_[] = { WSlot_("selAll()", false), WSlot_("selNone()", false), WSlot_("invertSel()", false), WSlot_("delSel()", false), WSlot_("delSelMonitor()", false), WSlot_("enableSel()", false), WSlot_("disableSel()", false), WSlot_("addMonitor()", false), WSlot_("editSelMonitor()", false), WSlot_("changeState()", false), WSlot_("BackParent()", false), WSlot_("disableSucc()", false), WSlot_("refreshMonitors()", false), WSlot_("sortMonitors()", false), WSlot_("gotoGroup(const std::string)", false), WSlot_("gotoDevice(const std::string)", false), WSlot_("copySelMonitor()", false), WSlot_("PastMonitor()", false), WSlot_() };
WSignal_ SVMonitorview::signals_[] = { WSignal_("AddNewMonitor(string,string)", false), WSignal_("EditMonitorByID(string)", false), WSignal_("BackDeviceParent(string)", false), WSignal_("sortMonitorsList(int)", false), WSignal_("enterGroup(string)", false), WSignal_("enterDependDevice(string)", false), WSignal_("ChangeDeviceState(string,int)", false), WSignal_("CopyMonitorSucc(string,string)", false), WSignal_() };

void SVMonitorview::buildSlotMap(WSlotMap& result)
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
void SVMonitorview::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVMonitorview::AddNewMonitor(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 0, args);
}

void SVMonitorview::EditMonitorByID(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

void SVMonitorview::BackDeviceParent(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 2, args);
}

void SVMonitorview::sortMonitorsList(int arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 3, args);
}

void SVMonitorview::enterGroup(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 4, args);
}

void SVMonitorview::enterDependDevice(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 5, args);
}

void SVMonitorview::ChangeDeviceState(string arg0,int arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 6, args);
}

void SVMonitorview::CopyMonitorSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 7, args);
}

bool SVMonitorview::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
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
    sender_ = sender;    delSelMonitor();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    enableSel();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    disableSel();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    addMonitor();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    editSelMonitor();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    changeState();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    BackParent();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    disableSucc();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    refreshMonitors();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    sortMonitors();
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    gotoGroup(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    gotoDevice(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    copySelMonitor();
    return true;
  }
  if (slot == slots_ + 17) {
    sender_ = sender;    PastMonitor();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVMonitorview::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
