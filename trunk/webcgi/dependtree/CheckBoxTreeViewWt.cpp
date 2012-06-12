#include <iostream>
#include "CheckBoxTreeView.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CCheckBoxTreeView::slots_[] = { WSlot_("ListMonitorInDevice()", false), WSlot_("DoApp1()", false), WSlot_("DoAppDec()", false), WSlot_("DoSetAppEnable()", false), WSlot_() };
WSignal_ CCheckBoxTreeView::signals_[] = { WSignal_() };

void CCheckBoxTreeView::buildSlotMap(WSlotMap& result)
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
void CCheckBoxTreeView::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CCheckBoxTreeView::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ListMonitorInDevice();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    DoApp1();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    DoAppDec();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    DoSetAppEnable();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CCheckBoxTreeView::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
