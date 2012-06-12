#include <iostream>
#include "addmonitor1st.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVMonitorList::slots_[] = { WSlot_("CancelAdd()", false), WSlot_("MonitorMTClicked(int)", false), WSlot_() };
WSignal_ SVMonitorList::signals_[] = { WSignal_("AddMonitorByType(int,string)", false), WSignal_("Cancel()", false), WSignal_() };

void SVMonitorList::buildSlotMap(WSlotMap& result)
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
void SVMonitorList::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVMonitorList::AddMonitorByType(int arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 0, args);
}

void SVMonitorList::Cancel()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

bool SVMonitorList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    CancelAdd();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    MonitorMTClicked(*((int *)args[0]));
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVMonitorList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
