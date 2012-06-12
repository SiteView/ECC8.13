#include <iostream>
#include "batchadd.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVBatchAdd::slots_[] = { WSlot_("savemonitor()", false), WSlot_("cancel()", false), WSlot_("selall()", false), WSlot_() };
WSignal_ SVBatchAdd::signals_[] = { WSignal_("backPreview()", false), WSignal_("AddMonitorSucc(string,string)", false), WSignal_() };

void SVBatchAdd::buildSlotMap(WSlotMap& result)
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
void SVBatchAdd::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVBatchAdd::backPreview()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void SVBatchAdd::AddMonitorSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 1, args);
}

bool SVBatchAdd::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    savemonitor();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    cancel();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    selall();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVBatchAdd::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
