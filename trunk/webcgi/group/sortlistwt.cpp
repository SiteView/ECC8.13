#include <iostream>
#include "sortlist.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVSortList::slots_[] = { WSlot_("UpFloor(const std::string)", false), WSlot_("DownFloor(const std::string)", false), WSlot_("saveList()", false), WSlot_("cancelEdit()", false), WSlot_() };
WSignal_ CSVSortList::signals_[] = { WSignal_("RefreshList()", false), WSignal_("backMainView()", false), WSignal_() };

void CSVSortList::buildSlotMap(WSlotMap& result)
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
void CSVSortList::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVSortList::RefreshList()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void CSVSortList::backMainView()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

bool CSVSortList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    UpFloor(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    DownFloor(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    saveList();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    cancelEdit();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CSVSortList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
