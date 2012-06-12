#include <iostream>
#include "MenuTable.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CMenuTable::slots_[] = { WSlot_("ShowTable()", false), WSlot_("HideTable()", false), WSlot_("ShowOrHideTable()", false), WSlot_() };
WSignal_ CMenuTable::signals_[] = { WSignal_() };

void CMenuTable::buildSlotMap(WSlotMap& result)
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
void CMenuTable::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CMenuTable::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ShowTable();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    HideTable();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ShowOrHideTable();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CMenuTable::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
