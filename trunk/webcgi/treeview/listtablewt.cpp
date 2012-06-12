#include <iostream>
#include "listtable.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CEccListTable::slots_[] = { WSlot_("ShowHideSub()", false), WSlot_("SelectAll()", false), WSlot_("SelectNone()", false), WSlot_("InvertSelect()", false), 
    WSlot_("Confirm()", false), WSlot_("AddNew()", false), WSlot_("Copy()", false), WSlot_("Paste()", false), WSlot_("Enable()", false), WSlot_("Disable()", false), WSlot_("DelSelect()", false), WSlot_("RefreshSel()", false), WSlot_("Sort()", false), WSlot_() };
WSignal_ CEccListTable::signals_[] = { WSignal_() };

void CEccListTable::buildSlotMap(WSlotMap& result)
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
void CEccListTable::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CEccListTable::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ShowHideSub();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    SelectAll();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    SelectNone();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    InvertSelect();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    Confirm();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    AddNew();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    Copy();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    Paste();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    Enable();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    Disable();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    DelSelect();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    RefreshSel();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    Sort();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CEccListTable::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
