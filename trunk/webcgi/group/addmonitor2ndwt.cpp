#include <iostream>
#include "addmonitor2nd.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVMonitor::slots_[] = { WSlot_("Preview()", false), WSlot_("showHelpText()", false), WSlot_("SaveMonitor()", false), WSlot_("Cancel()", false), WSlot_("setDefaultAlert()", false), WSlot_("ContinueAdd()", false), WSlot_("BatchAddMonitor()", false), WSlot_("listDynParam()", false), WSlot_("Translate()", false), WSlot_() };
WSignal_ SVMonitor::signals_[] = { WSignal_("CancelAddMonitor()", false), WSignal_("BackPreview()", false), WSignal_("AddMonitorSucc(string,string)", false), WSignal_("EditMonitorSucc(string,string)", false), WSignal_("BatchAddNew()", false), WSignal_() };

void SVMonitor::buildSlotMap(WSlotMap& result)
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
void SVMonitor::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVMonitor::CancelAddMonitor()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void SVMonitor::BackPreview()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

void SVMonitor::AddMonitorSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 2, args);
}

void SVMonitor::EditMonitorSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 3, args);
}

void SVMonitor::BatchAddNew()
{
  void **args = 0;
  triggerSignal(signals_ + 4, args);
}

bool SVMonitor::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Preview();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showHelpText();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    SaveMonitor();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    Cancel();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    setDefaultAlert();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    ContinueAdd();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    BatchAddMonitor();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    listDynParam();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    Translate();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVMonitor::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
