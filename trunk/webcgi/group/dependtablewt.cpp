#include <iostream>
#include "dependtable.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVDependTable::slots_[] = { WSlot_("showDependTree()", false), WSlot_("showSubTable()", false), WSlot_("hideSubTable()", false), WSlot_("changePath()", false), WSlot_("cleardate()", false), WSlot_() };
WSignal_ SVDependTable::signals_[] = { WSignal_() };

void SVDependTable::buildSlotMap(WSlotMap& result)
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
void SVDependTable::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool SVDependTable::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    showDependTree();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showSubTable();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    hideSubTable();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    changePath();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    cleardate();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVDependTable::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
